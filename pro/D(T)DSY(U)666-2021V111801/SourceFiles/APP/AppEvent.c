///*######################################################################*///
///* 头文件包含  *///
#include "..\SourceFiles\PUB\Include.h"

///*######################################################################*///
///* 函数声明 *///
void Hal_EraseFlashSector(INT16U adr, INT8U dat, INT8U sta);
INT8U Hal_ReadEEPROM(INT8U  *Dst, INT16U Src, INT16U Len);
INT8U Hal_WriteEEPROM(INT16U Dst, INT8U  *Src, INT16U Len);

static void ApiEvent_RecTotalNum_Add(uchar8 V_ucEventType);
void ApiEvent_WriteRecord(uchar8 v_ucEventType);
uchar8 ReadEventRecordData(ulong32 V_ulProgDIx,uchar8 *DataPoint,uchar8 *PtrDataLen);

///*######################################################################*///
//			 		//事件结构体// 
static const GStr_EventParaData code GT_EventParaData[]={
	{0x3001,CAddr_Cleardl_Note	,CAddr_Cleardl_Note_Lenth },//清零
	{0x0333,CAddr_SelfMoney_Note ,CAddr_SelfMoney_Lenth	  },//购电
    {0x3000,CAddr_Program_Note	, CAddr_Program_Note_Lenth},//编程
   	{0x3400,CAddr_RejectMoney_Note,CAddr_RejectMoney_Lenth},//退费
	{0x1D00,CAddr_OpenRelay_Note	,CAddr_E2OpenRelay_Lenth},//拉闸
	{0x1E00,CAddr_CloseRelay_Note	,CAddr_E2CloseRelay_Lenth},//合闸	
};
uchar8 xdata GA_ucEventRecordBuff[60];///事件记录缓存
uchar8 xdata GA_ucDICode[4];///编程数据标识
uchar8 xdata GA_ucOperCode[4];///操作者代码
uchar8 xdata GA_ucRelayOperCode[4];///拉合闸操作者代码


const uchar8 code GT_ucBuyMoneyRecOffset[] = {0,2,6,10,14};
const uchar8 code GT_ucBuyMoneyRecLen[] =    {5,2,4, 4, 4, 4};
///*######################################################################*///
///* 函数 *///
///******************************************************************************///
///*Function：	 EventRecTotalNum_Add                                           *///
///*Description：事件记录总次数累加处理                                 	    *///
///*					                                                        *///
///*Output     :	操作成功													*///
///*Return     :	正常返回00H，异常返回01H									*///
///*Others     :																*///
///*History    :	 															*///
///******************************************************************************///
void ApiEvent_RecTotalNum_Add(uchar8 V_ucEventType)
{
	 uchar8 v_ucTempData[4];
	 if((V_ucEventType>=C_Clear)&&(V_ucEventType<=C_CloseRelay))
	 {
	 	if(GStr_EventNumPiont.uc_Num[V_ucEventType]==0x00)//有效指针次数等于0//
		{  	//总次数归零//		
			LibPub_MemSetBytes(&GStr_EventRecordNum.ucEventTimes[V_ucEventType][0],0x00,4);
		}
		//总次数加1//
		LibPub_MemSetBytes(v_ucTempData,0x00,4);
		v_ucTempData[3]=1;
		LibPub_NBtyesBcdAdd(&GStr_EventRecordNum.ucEventTimes[V_ucEventType][0],v_ucTempData,4);
		//总次数写入E2//
		LibPub_WriteDataToE2prom(LIB_E2P_EventNum, 0, (uchar8*)&GStr_EventRecordNum.ucEventTimes[0][0] );
		GStr_EventRecordNum.usCRC16=LibPub_CRC16_CCITT((uchar8*)&GStr_EventRecordNum.ucEventTimes[0][0],GStr_EventRecordNum_TypeLEN-2);	
	
	 }
}

///******************************************************************************///
///*Function   :	写事件记录													*///
///*Description:	电表清零、事件清零、分项事件清零							*///
///*Output     :	操作成功													*///
///*Return     :	正常返回00H，异常返回01H									*///
///*Others     :																*///
///*History    :	 															*///
///******************************************************************************///
void ApiEvent_WriteRecord(uchar8 v_ucEventType)
{
	ushort16 V_usE2addrPage,V_usE2addrPage1;
	uchar8 i;
	uchar8 xdata V_ucTempData[512];
	uchar8	V_ucTemp1;
	
	ApiPwOn_EventPointCheck();///事件指针次数效验
	
	V_usE2addrPage = GT_EventParaData[v_ucEventType].V_usEventAddr;
	V_usE2addrPage1 = GT_EventParaData[v_ucEventType].V_usEventAddr+0x0100;
	///具体类EE地址等于第一个事件的地址
	GStr_Flag.ucWrE2promSafeByte|=C_SafeByte_Step1;
	if((C_Program==v_ucEventType)&&(0==(GStr_Flag.ucRunState2&F_RUN_FirstProgFlag )))///非首次编程
	{
		GStr_Flag.ucWrE2promSafeByte|=C_SafeByte_Step2;
		Hal_ReadEEPROM(&V_ucTempData[0],V_usE2addrPage,512);
		LibPub_MemCopyBytes(&V_ucTempData[GStr_EventValidPiont.uc_Point[v_ucEventType]*GT_EventParaData[v_ucEventType].V_ucEventLenth], &GA_ucEventRecordBuff[0],GT_EventParaData[v_ucEventType].V_ucEventLenth);
		if(C_Equal !=LibPub_CompareData(&GA_ucEventRecordBuff[0], &GA_ucOperCode[0], 4, CMP_MODE_HIGHT))
		{
			LibPub_MemCopyBytes(&GA_ucOperCode[0], &GA_ucEventRecordBuff[0],4);
			LibPub_MemCopyBytes(&GA_ucDICode[0], &GA_ucEventRecordBuff[4],4);	
			LibPub_MemSetBytes(&GA_ucEventRecordBuff[8], 0xFF, 36);	///其他数据标识补FF	
			
			ApiEvent_RecTotalNum_Add(v_ucEventType);///操作者代码不同，增加一次编程记录
						///* 计数指针次数累加 *///
			if( GStr_EventNumPiont.uc_Num[v_ucEventType] < C_EventMaxNum )
			{
				GStr_EventNumPiont.uc_Num[v_ucEventType]++;
			}
			///* 计数指针次数防非法 *///
			if( GStr_EventNumPiont.uc_Num[v_ucEventType] > C_EventMaxNum )
			{
			   GStr_EventNumPiont.uc_Num[v_ucEventType] = 1;
			}
			///* 事件指针累加 *///
			GStr_EventValidPiont.uc_Point[v_ucEventType]++;
			if( GStr_EventValidPiont.uc_Point[v_ucEventType] >= C_EventMaxNum )
			{
			   GStr_EventValidPiont.uc_Point[v_ucEventType] = 0;
			} 
			GStr_EventValidPiont.usCRC16=LibPub_CRC16_CCITT( GStr_EventValidPiont.uc_Point, 4);
			LibPub_WriteDataToE2prom(LIB_E2P_EventValidPiont, 0, GStr_EventValidPiont.uc_Point );//循环指针写EE
			
			GStr_EventNumPiont.usCRC16=LibPub_CRC16_CCITT( GStr_EventNumPiont.uc_Num, 4);///有效指针写EE
			LibPub_WriteDataToE2prom(LIB_E2P_EventNumPiont, 0, GStr_EventNumPiont.uc_Num );
		}
		else
		{
			for( i=0; i<36; i++ )
			{
				GA_ucEventRecordBuff[43-i] = GA_ucEventRecordBuff[39-i];
			}///操作者代码与首次相同
			LibPub_MemCopyBytes( &GA_ucDICode[0], &GA_ucEventRecordBuff[4] ,4);	///本次编程的数据标识
		}
		GStr_Flag.ucWrE2promSafeByte|=C_SafeByte_Step3;
		LibPub_MemCopyBytes(&GA_ucEventRecordBuff[0],&V_ucTempData[GStr_EventValidPiont.uc_Point[v_ucEventType]*GT_EventParaData[v_ucEventType].V_ucEventLenth],GT_EventParaData[v_ucEventType].V_ucEventLenth);
		Hal_EraseFlashSector(V_usE2addrPage, 0x00, FLASH_RW_ENABLE);///擦除编程记录所在的扇区上半部分
		Hal_EraseFlashSector(V_usE2addrPage1, 0x00, FLASH_RW_ENABLE);///擦除编程记录所在的扇区下半部分
		Hal_WriteEEPROM(V_usE2addrPage, V_ucTempData, 512);
		GStr_Flag.ucWrE2promSafeByte=C_SafeByte_Step0;	
	}
	else
	{
		///* 事件总次数累加 *///
		ApiEvent_RecTotalNum_Add(v_ucEventType);
		
		GStr_Flag.ucWrE2promSafeByte|=C_SafeByte_Step2;
		Hal_ReadEEPROM(V_ucTempData,V_usE2addrPage,512);
		LibPub_MemCopyBytes(&V_ucTempData[GStr_EventValidPiont.uc_Point[v_ucEventType]*GT_EventParaData[v_ucEventType].V_ucEventLenth], &GA_ucEventRecordBuff[0],GT_EventParaData[v_ucEventType].V_ucEventLenth);
		switch( v_ucEventType )
		{
			case C_Clear: ///清零
		    {
				LibPub_MemCopyBytes(&GA_ucOperCode[0],&GA_ucEventRecordBuff[0],4);//操作者代码//
				LibPub_MemExchangeBytes(&GStr_AVAIL.ucbeforeFwEnergy[0],&GA_ucEventRecordBuff[4],4);
				LibPub_MemExchangeBytes(&GStr_AVAIL.ucbeforeBkEnergy[0],&GA_ucEventRecordBuff[8],4); 
			}break;
			case C_BuyMoney: //购电
			{
				LibPub_MemCopyBytes( &GStr_PRICE.ucPurchaseTimes[2], &GA_ucEventRecordBuff[0],2);		         ///* 购电后总次数 *///
				LibPub_MemCopyBytes( &GStr_AVAIL.ucRechangeMoney[0], &GA_ucEventRecordBuff[2 ],4);				///* 购电金额 *///
				LibPub_MemCopyBytes( &GStr_AVAIL.ucBuybeforeMoney[0], &GA_ucEventRecordBuff[6],4); 		        ///* 购电前剩余金额 *///
				LibPub_MemCopyBytes( &GStr_Money.ucaRemainMoney[0], &GA_ucEventRecordBuff[10],4); 		       ///* 购电后剩余金额 *///
				LibPub_MemCopyBytes( &GStr_PRICE.ucaPurchaseMoneyAll[0], &GA_ucEventRecordBuff[14],4); 	            ///* 购电后累计购电金额 *///
			}break;
			case C_Program:///编程  首次编程
			{
				LibPub_MemCopyBytes(&GA_ucOperCode[0], &GA_ucEventRecordBuff[0],4);
				LibPub_MemCopyBytes(&GA_ucDICode[0], &GA_ucEventRecordBuff[4],4);	
				LibPub_MemSetBytes(&GA_ucEventRecordBuff[8], 0xFF, 36);	///其他数据标识补FF				
				GStr_Flag.ucRunState2&=~F_RUN_FirstProgFlag;///清首次编程	
			}break;
			case C_RejectMoney:///退费
			{
				LibPub_MemExchangeBytes( &GStr_PRICE.ucPurchaseTimes[2], &GA_ucEventRecordBuff[0],2);			///* 退费前购电次数 *///
				LibPub_MemExchangeBytes( &GStr_AVAIL.ucRechangeMoney[0], &GA_ucEventRecordBuff[2 ],4);				///* 退费金额 *///
				LibPub_MemExchangeBytes( &GStr_AVAIL.ucBuybeforeMoney[0], &GA_ucEventRecordBuff[6],4); 				///* 退费前剩余金额 *///
				LibPub_MemExchangeBytes( &GStr_Money.ucaRemainMoney[0], &GA_ucEventRecordBuff[10],4); 			///* 退费后剩余金额 *///
			}break;
			case C_OpenRelay:///拉闸
			case C_CloseRelay:///合闸
			{
				LibPub_MemCopyBytes(&GA_ucRelayOperCode[0],&GA_ucEventRecordBuff[0],4);//操作者代码//
				LibPub_MemExchangeBytes( &GStr_Energy.ucaFw_Energy[0], &GA_ucEventRecordBuff[4],4); ///* 正向有功电能 *///
				LibPub_MemExchangeBytes( &GStr_Energy.ucaBk_Energy[0], &GA_ucEventRecordBuff[8],4);	///* 反向有功电能*///
				LibPub_MemSetBytes(GA_ucRelayOperCode,0xFF,4);///操作者代码默认为全FF
			}break;
			
//			{
//				LibPub_MemCopyBytes(&GA_ucRelayOperCode[0],&GA_ucEventRecordBuff[0],4);//操作者代码//
//				LibPub_MemExchangeBytes( &GStr_Energy.ucaFw_Energy[0], &GA_ucEventRecordBuff[4],4); ///* 正向有功电能 *///
//				LibPub_MemExchangeBytes( &GStr_Energy.ucaBk_Energy[0], &GA_ucEventRecordBuff[8],4);	///* 反向有功电能*///
//				LibPub_MemSetBytes(GA_ucRelayOperCode,0xFF,4);///操作者代码默认为全FF
//			}break;
			
			default:return;	
		}
		///* 计数指针次数累加 *///
		if( GStr_EventNumPiont.uc_Num[v_ucEventType] < C_EventMaxNum )
		{
			GStr_EventNumPiont.uc_Num[v_ucEventType]++;
		}
		///* 计数指针次数防非法 *///
		if( GStr_EventNumPiont.uc_Num[v_ucEventType] > C_EventMaxNum )
		{
		   GStr_EventNumPiont.uc_Num[v_ucEventType] = 1;
		}
		///* 事件指针累加 *///
		GStr_EventValidPiont.uc_Point[v_ucEventType]++;
		if( GStr_EventValidPiont.uc_Point[v_ucEventType] >= C_EventMaxNum )
		{
		   GStr_EventValidPiont.uc_Point[v_ucEventType] = 0;
		} 
	    GStr_EventValidPiont.usCRC16=LibPub_CRC16_CCITT( GStr_EventValidPiont.uc_Point, 4);
		LibPub_WriteDataToE2prom(LIB_E2P_EventValidPiont, 0, GStr_EventValidPiont.uc_Point );//循环指针写EE
		
		GStr_EventNumPiont.usCRC16=LibPub_CRC16_CCITT( GStr_EventNumPiont.uc_Num, 4);///有效指针写EE
		LibPub_WriteDataToE2prom(LIB_E2P_EventNumPiont, 0, GStr_EventNumPiont.uc_Num );
		
		///*  做事件记录 *///
		GStr_Flag.ucWrE2promSafeByte|=C_SafeByte_Step3;
		V_ucTemp1 = GStr_EventValidPiont.uc_Point[v_ucEventType]*GT_EventParaData[v_ucEventType].V_ucEventLenth;
		LibPub_MemCopyBytes( &GA_ucEventRecordBuff[0],  &V_ucTempData[V_ucTemp1],  GT_EventParaData[v_ucEventType].V_ucEventLenth  );
		//LibPub_MemCopyBytes(&GA_ucEventRecordBuff[0],&V_ucTempData[GStr_EventValidPiont.uc_Point[v_ucEventType]*GT_EventParaData[v_ucEventType].V_ucEventLenth],GT_EventParaData[v_ucEventType].V_ucEventLenth);
		Hal_EraseFlashSector(V_usE2addrPage, 0x00, FLASH_RW_ENABLE);///擦除编程记录所在的扇区上半部分
		Hal_EraseFlashSector(V_usE2addrPage1, 0x00, FLASH_RW_ENABLE);///擦除编程记录所在的扇区下半部分
		Hal_WriteEEPROM(V_usE2addrPage, V_ucTempData, 512);
		GStr_Flag.ucWrE2promSafeByte=C_SafeByte_Step0;
	

		
   } 	 
}

///*=====================================================================================*///
///*Copyright：   杭州正泰仪表科技有限公司                                               *///
///*File name:     ReadEventRecordData		                                             *///
///*Author:        		                                                                 *///
///*Version:       		                                                                 *///
///*Date:         			                                                             *///
///*Description: 事件处理函数*////                                                       *///
///*调用条件：															                 *///
///*Input:																				 *///
///*Input:V_ucFrameSN，帧序号，为0表示无后续帧，为1表示后续第一帧，为2表示后续第2帧...   *///
///*Author:                                                                              *///
///*Modification:                                                                        *///
///===================================================================================== *///
uchar8 ReadEventRecordData(ulong32 V_ulProgDIx,uchar8 *DataPoint,uchar8 *PtrDataLen)
{
 	uchar8   i;
 	uchar8 	 V_ucEventType;
 	ushort16 V_ucEventAddress;
	uchar8   V_ucEventOffset;
	uchar8   V_EventLen;
 	uchar8   V_ucDI[4];                                             
 	ushort16 V_usDI2DI1;
 	uchar8	 V_ucLenJudge;	///*拉合闸事件判断DI3DI2*///                                               
 	uchar8   V_ucErrorType;
	uchar8   V_ucTempData[512];
	ulong32  V_ulTempData;

 	V_ucErrorType = 0x00;
 	V_ucDI[0] = (uchar8)(V_ulProgDIx);
 	V_ucDI[1] = (uchar8)(V_ulProgDIx >> 8);
 	V_ucDI[2] = (uchar8)(V_ulProgDIx >> 16);
 	V_ucDI[3] = (uchar8)(V_ulProgDIx >> 24);
	
 	ApiPwOn_EventPointCheck();///事件指针次数效验

	
	
 	if(( (V_ucDI[3]==0x03)&&(V_ucDI[1]!=0x00)&&(V_ucDI[2]==0x33))||((V_ucDI[3]==0x1D)||(V_ucDI[3]==0x1E)))
 	{
 	   V_ucLenJudge=0x01; ///* 购电
 	}
 	else
 	{
 	   V_ucLenJudge=0x00;
 	}
 	V_usDI2DI1 = V_ucDI[2+V_ucLenJudge];
 	V_usDI2DI1 = (V_usDI2DI1 << 8) | V_ucDI[1+V_ucLenJudge];

 	for( V_ucEventType=0; V_ucEventType<C_EventValidPoint_Lenth; V_ucEventType++)      ///*查询表格，找到是哪种事件类型*///
 	{
 		if(GT_EventParaData[V_ucEventType].V_usEventID == V_usDI2DI1)
 		{
 			break;
 		}
 	}
 	if((V_ucEventType>(C_EventValidPoint_Lenth-1)))///*查不到事件类型*///
 	{
 		V_ucErrorType = 0x02;
 		return V_ucErrorType;
 	}
 
 	///* 读事件记录总次数*///
 	if((V_ucDI[0]==0x00)||(V_ulProgDIx==0X1D000001)||(V_ulProgDIx==0X1E000001))	  
 	{
		LibPub_MemExchangeBytes( &GStr_EventRecordNum.ucEventTimes[V_ucEventType][1], DataPoint, 0x03);///*读事件次数 *///
 		*PtrDataLen = 0x03;
 		return C_OK;
 	}
 	

 	///* 要读的条数超过最大条数，则返回无请求数据 *///
	if( V_ucDI[0] >C_EventMaxNum )///**///
	{
		return(0x02);	///* 无请求数据 *///
	}
	
	V_ulTempData=LibPub_Buffer4ToUlong32(&GStr_EventRecordNum.ucEventTimes[V_ucEventType][0]);
	///* 如果要读的条数大于已记录的条数，则回全零 *///
 	if(( V_ucDI[0] > GStr_EventNumPiont.uc_Num[V_ucEventType] )	||(V_ucDI[0] > V_ulTempData))
 	{///大于有效次数或者大于总次数
 	   	*PtrDataLen=GT_EventParaData[V_ucEventType].V_ucEventLenth;
 	   	if( V_ucEventType == C_Clear )  ///清零
 	   	{
 		   *PtrDataLen = 106;
 	   	}
 	   	else if( V_ucEventType == C_Program)//编程
 		{
 			*PtrDataLen = 50;
 		}
 		else if(V_ucEventType == C_RejectMoney)///退费
 		{
 			*PtrDataLen = 20;
 		}
		else if((V_ucEventType == C_OpenRelay)||(V_ucEventType == C_CloseRelay))///拉闸\合闸
		{
			for( i = 1; i < 9; i++)
			{
				if( i==V_ucDI[1]) break;
			}
			if( i<9)
			{
				if(1==i)
				{
					*PtrDataLen=6;///时间
				}
				else
				{
					*PtrDataLen=4;///其他数据都是4个字节
				}
			}
			else
			{
				V_ucErrorType = 0x02;
				return V_ucErrorType;
			} 
		}
		else if (V_ucEventType == C_BuyMoney)///购电
		{  
			for( i = 1; i < 7; i++)
			{
				if( i==V_ucDI[1]) break;
			}
			if( i<7)
			{
				*PtrDataLen = GT_ucBuyMoneyRecLen[i-1]; 
				// CopyData( DataPoint+GT_ucBuyMoneyRecOffset[i-1], DataPoint, *PtrDataLen);  
			}
			else
			{
				V_ucErrorType = 0x02;
				return V_ucErrorType;
			} 
		}
 		LibPub_MemSetBytes( DataPoint,0x00, *PtrDataLen);
 		return C_OK;
 	}
 	else
 	{
		V_ucEventAddress = GT_EventParaData[V_ucEventType].V_usEventAddr;///事件记录所在的类EE块地址
		V_ucEventOffset=(C_EventMaxNum + GStr_EventValidPiont.uc_Point[V_ucEventType] +1 - V_ucDI[0])% C_EventMaxNum;
		//要抄读的事件指针
		V_EventLen = GT_EventParaData[V_ucEventType].V_ucEventLenth; 
 	}

 	///*3) 根据指针读出事件记录数据内容*///
    Hal_ReadEEPROM(V_ucTempData,V_ucEventAddress,512);
	LibPub_MemCopyBytes(&V_ucTempData[V_ucEventOffset*V_EventLen], GA_ucEventRecordBuff,V_EventLen);
	
 	switch(V_ucEventType)
 	{
 		case C_Program:	///* 编程 *///时间没有保存
 		{
			LibPub_MemCopyBytes( GA_ucEventRecordBuff,DataPoint+6, V_EventLen);
			LibPub_MemSetBytes( DataPoint,0xFF, 6);//时间回全FF
			*PtrDataLen	= V_EventLen+6;
		}break;
		case C_RejectMoney:///退费，时间5字节
		{
			LibPub_MemCopyBytes( GA_ucEventRecordBuff,DataPoint+5, V_EventLen);
			LibPub_MemSetBytes( DataPoint,0xFF, 5);//时间回全FF
			*PtrDataLen	= V_EventLen+5;
		}break;
		case C_Clear:///清零
		{
			LibPub_MemCopyBytes( GA_ucEventRecordBuff,DataPoint+6, V_EventLen);
			LibPub_MemSetBytes( DataPoint,0xFF, 6);//时间回全FF
			LibPub_MemSetBytes( DataPoint+18,0xFF, 88);//时间回全FF
			*PtrDataLen=106;
		}break;
		case C_OpenRelay:///拉闸
		case C_CloseRelay:///合闸	
		{
			for( i = 1; i < 9; i++)
			{
				if( i==V_ucDI[1]) break;
			}
			if( i<9)
			{
				if(1==i)
				{
					*PtrDataLen=6;///时间
					LibPub_MemSetBytes( DataPoint,0xFF, *PtrDataLen);///拉合闸时间为全FF
				}
				else if(i>=5)
				{
					*PtrDataLen=4;///其他数据都是4个字节
					LibPub_MemSetBytes( DataPoint,0xFF, *PtrDataLen);///拉合闸时间为全FF
				}
				else
				{
					*PtrDataLen=4;///其他数据都是4个字节
					LibPub_MemCopyBytes(&GA_ucEventRecordBuff[(4*(i-2))],DataPoint, *PtrDataLen);
				}
			}
			else
			{
				V_ucErrorType = 0x02;
			}
		}break;
//		case C_CloseRelay:///合闸
//		{
//			LibPub_MemCopyBytes( GA_ucEventRecordBuff,DataPoint+6, V_EventLen);
//			LibPub_MemSetBytes( DataPoint,0xFF, 6);//时间回全FF
//			LibPub_MemSetBytes( DataPoint+18,0xFF, 16);//无效数据回全FF
//		}break;
		case C_BuyMoney://购电
		{
			for( i = 1; i < 7; i++)
			{
				if( i==V_ucDI[1]) break;
			}
			if( i<7)
			{
				*PtrDataLen = GT_ucBuyMoneyRecLen[i-1]; 
				if(1==i)
				{
					LibPub_MemSetBytes( DataPoint,0xFF, *PtrDataLen);////购电时间为全FF
				}
				else
				{
					LibPub_MemExchangeBytes(& GA_ucEventRecordBuff[GT_ucBuyMoneyRecOffset[i-2]],DataPoint, *PtrDataLen);
				}
			}
			else
			{
				V_ucErrorType = 0x02;
			}
		}break;

 		default:
 			V_ucErrorType = 0x02;
 	   		break;
 	}
  	return 	V_ucErrorType;
}
