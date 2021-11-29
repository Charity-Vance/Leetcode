/****************************************************************************************
Copyright:	ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:	DataProcess.c
Version:	V1
Date:		2021-10-20
Description:数据层文件
Function List:
****************************************************************************************
History1:	第1次修改
内容1.	Date:20211002
		Author:MYM、WJQ、GG
		Modification:
		**********************************************
内容2.	Date:
		Author:
		Modification:
		********************************************************************************
History2:	第2次修改
内容1.	Date:
		Author:
		Modification:
		**********************************************
内容2.	Date:
		Author:
		Modification:
****************************************************************************************/

#include "Public.h"
#include "DataProcess.h"
#include "Communication.h"
#include "fm33A0xx_flash.h"

extern ConectRequest_Type	Com_Conect;
/**********************************************************************************
函数原型：uchar8 SF_EraseFlashAndWriteEmptySign(ulong32 V_FlashAddr)
功能描述：擦除V_FlashAddrFlash，然后写该页Flash最后4个字节为空标志0x68，只有为4个68才认为该页Flash为空
输入参数：ulong32V_FlashAddr：需擦除Flash地址；
输出参数：无；
返回参数：C_OK、C_SafeFlagError
功能说明：
调用机制：
备     注：内部判断安全标志
**********************************************************************************/
uchar8 SF_EraseFlashAndWriteEmptySign(ulong32 V_FlashAddr)
{
	uchar8 V_Flash_Empty[4], V_i;

	V_FlashAddr = V_FlashAddr & 0xFFFFF000;			/*页地址*/

	for(V_i = 0; V_i < C_Flash_EmptyNum; V_i++)
	{
		V_Flash_Empty[V_i] = C_Flash_Empty68;		/*写Flash为空标志，0x68*/
	}

	InF_FlashChipSelect();
	if(C_W_SafeFlag != GV_D_SafeFlag)				/*安全标志错*/
	{
		InF_FlashChipDeselect();					/*关闭CS*/
		GV_D_SafeFlag = C_Clear_SafeFlag;
		return C_SafeFlagError;
	}
	InF_EraseFlash(V_FlashAddr);

	V_FlashAddr = V_FlashAddr + C_OneFlashPage - C_Flash_EmptyNum;	/*最后4个字节Flash地址*/
	InF_FlashChipSelect();
	if(C_W_SafeFlag != GV_D_SafeFlag)		/*安全标志错*/
	{
		InF_FlashChipDeselect();		/*关闭CS*/
		GV_D_SafeFlag = C_Clear_SafeFlag;
		return C_SafeFlagError;
	}
	InF_WriteFlash(V_FlashAddr, &V_Flash_Empty[0], C_Flash_EmptyNum);
	return C_OK;
}
/***********************************************************************************
函数原型：void InF_ReadE2_Flash_Data(uchar8 *PV_Data, uchar8 V_Len, uchar8 V_Sign, ulong32 V_Addr);
功能描述：调试用，读底层E2、Flash地址具体数据；后增加读RAM数据
输入参数：
		uchar8*PV_Data:读数据缓存；
		uchar8V_Len：读数据长度；
		uchar8V_Sign：读E2、Flash标志，01：读E2；02：读Flash；
		ulong32V_Addr：读E2、Flash地址；
输出参数：无
返回参数：无；
功能说明：
调用机制：
备     注：
**********************************************************************************/
#if (C_NiuDebugReadData)
void InF_ReadE2_Flash_Data(uchar8 *PV_Data, uchar8 V_Len, uchar8 V_Sign, ulong32 V_Addr)
{
	ushort16 V_E2Addr;

	V_E2Addr = (ushort16)V_Addr;

	switch(V_Sign)
	{
			case	C_ReadRamFlay:		/*读RAM*/
			{
				SF_Re_RAM_Data((uchar8 *)V_Addr, V_Len, PV_Data, 0, 0);		/*0,0核对该函数入口定义*/
				break;
			}
			case	C_ReadFlashFlay:	/*读Flash*/
			{
				InF_ReadFlash(V_Addr, PV_Data, V_Len);
				break;
			}
			case	C_ReadE2Flay:		/*读E2*/
			{
				InF_ReadE2(V_E2Addr, PV_Data, V_Len);
				break;
			}
			case	C_ReadFRAMFlay:		/*读铁电*/
			{
				InF_ReadFRAM(V_E2Addr, PV_Data, V_Len);
				break;
			}
//			case	C_ReadMCUFlay:		/*读MCU*/
//			{
//				InF_ReadMCU(V_Addr, PV_Data, V_Len);
//				break;
//			}
			default:
				break;
	}
}
#endif

/**********************************************************************************
函数原型：uchar8 InF_Write_RecMeterData(uchar8 Msg_Num, uchar8 *P_Data, uchar8 V_Data_Length,
										uchar8 V_W_Safe_Flag, uchar8 V_Data_Num);
功能描述：写数据层校表数据接口函数
输入参数：
		uchar8 Msg_Num：消息号，用于判断是否有写权限；
		uchar8 *P_Data：数据所放缓存；
		uchar8 V_Data_Length：所写数据长度；
		uchar8 V_W_Safe_Flag：宏定义，当写安全标志；
		uchar8 V_Data_Num：写校表数据序号，与校表数据存W2地址偏移一一对应，数据层内部判断最大值，序号超返回C_NoAccess；
输出参数：无
返回参数：C_OK、C_IICError、C_DataLenError、C_SafeFlagError、C_NoAccess；
功能说明：
调用机制：
备     注：写数据层时调用，注意安全标志
**********************************************************************************/
uchar8 InF_Write_RecMeterData(uchar8 Msg_Num, uchar8 *P_Data, uchar8 V_Data_Length, uchar8 V_W_Safe_Flag, uchar8 V_Data_Num)
{
	ushort16 V_3TableE2Addr;
	uchar8 V_Return_Flag;

	GV_D_SafeFlag = C_Clear_SafeFlag;

	if(V_W_Safe_Flag != C_W_SafeFlag)
	{
		return C_SafeFlagError;
	}

	if(C_Msg_Communication != Msg_Num)
	{
		return C_NoAccess;
	}

	if(C_MeterICE2ResLen != V_Data_Length)
	{
		return C_DataLenError;
	}

	GV_D_SafeFlag = GV_D_SafeFlag | C_W_SafeFlag_1;
	if(V_Data_Num >= C_MeterICDataNum_T)
	{
		return C_DataLenError;
	}

	GV_D_SafeFlag = GV_D_SafeFlag | C_W_SafeFlag_2;
	V_3TableE2Addr = E2Addr_MeterIC_St + V_Data_Num * (C_MeterICE2ResLen + C_CRCLen2);		/*要操作E2地址*/
	if(V_3TableE2Addr > (E2Addr_MeterIC_End - C_MeterICE2ResLen - C_CRCLen2))				/*E2地址错误*/
	{
		return C_DataLenError;
	}

	GV_D_SafeFlag = GV_D_SafeFlag | C_W_SafeFlag_3;
	V_Return_Flag = SF_WriteE2Three(V_3TableE2Addr, C_MeterICE2ResLen, P_Data);				/*写E2三处*/
	GV_D_SafeFlag = C_Clear_SafeFlag;

	return V_Return_Flag;
}

/*********************************************************************************
函数原型：ushort16 SF_GetEventDataLen(ushort16 V_TB_E2BakeUp1Addr, ushort16 V_TBLen_E2BakeUp1Addr,
										ulong32 PStr_4aTableAddr1, uchar8 V_Str_4aTableLen)
功能描述：获取事件OAD列表对应数据长度
输入参数：
		ushort16 V_TB_E2BakeUp1Addr：可变关联列表E2地址；
		ushort16 V_TBLen_E2BakeUp1Addr：可变关联列表个数E2地址；
		ulong32 PStr_4aTableAddr1：固定关联列表4级表；
		uchar8 V_Str_4aTableLen：固定关联列表4级表结构体个数；
		uchar8 V_Type:
		//#defineC_TolTabDataLenSign1	固定、关联OAD列表，对应数据总长度
		//#defineC_FixTabDataLenSign2	固定OAD列表，对应数据总长度
		//#defineC_TabDataLenSign3		可变OAD列表，对应数据总长度
输出参数：无
返回参数：ushort16：数据长度，当E2读不出或异常时，返回全FF或0；
功能说明：
调用机制：
备     注：
*********************************************************************************/
ushort16 SF_GetEventDataLen(ushort16 V_TB_E2BakeUp1Addr, ushort16 V_TBLen_E2BakeUp1Addr, ulong32 PStr_4aTableAddr1, uchar8 V_Str_4aTableLen)
{
	ushort16 V_OADOrder16, V_Data_Length1, V_Data_Length2;
	uchar8 V_Return_Flag;
	uchar8 PV_Data[C_698Event_OADTabLen];
	uchar8 V_Data_Num, V_i;
	Str_4aTable *PStr_4aTableAddr = NULL;

	V_Data_Length1 = 0;
	if(0xFFFFFFFF == PStr_4aTableAddr1)
	{
		return V_Data_Length1;
	}

	PStr_4aTableAddr = (Str_4aTable *)(PStr_4aTableAddr1);

	/*可变列表*/
	V_Return_Flag = SF_ReadE2Three(V_TBLen_E2BakeUp1Addr, CLVariableAssociatedOADNum, &V_Data_Num);
	if(C_OK != V_Return_Flag)
	{
		return V_Data_Length1;
	}

	if(C_698Event_OADTabDataType * V_Data_Num > C_698Event_OADTabLen)	/*正常不存在，写数据时也会判断长度*/
	{
		return V_Data_Length1;
	}

	if(0 != V_Data_Num)
	{
		V_Return_Flag = SF_ReadE2Three(V_TB_E2BakeUp1Addr, (C_698Event_OADTabDataType * V_Data_Num), PV_Data);
		if(C_OK != V_Return_Flag)
		{
			return V_Data_Length1;
		}

		for(V_i = 0; V_i < V_Data_Num; V_i++)
		{
			PF_Buffer2ToUshort16(&PV_Data[C_698Event_OADTabDataType * V_i], &V_OADOrder16);
			V_OADOrder16 &= 0x1FFF;
			if(V_OADOrder16 >= Str_FrozenConvert_Table_Len)
			{
				return 0;	/*异常*/
			}

			V_Data_Length1 = V_Data_Length1 + Str_FrozenConvert_Table[V_OADOrder16].V_uc645Length;
		}
	}

	/*固定列表*/
	V_Data_Length2 = 0;
	for(V_i = 0; V_i < V_Str_4aTableLen; V_i++)
	{
		V_Data_Length2 += (PStr_4aTableAddr[V_i].V_DataLen & C_EventOutSign);
	}

	return (V_Data_Length1 + V_Data_Length2);
}

/*********************************************************************************
函数原型：uchar8 SF_WriteFlash_DataEventTable(uchar8 *P_Data, ushort16 V_Data_Length,
			Str_3dEventTable *P_Str_3dEventTableAddr, ulong32 V_Data_Id, ushort16 V_3dTable_Line, uchar8 V_Type)
功能描述：写Flash数据,698事件记录，DI0为1表示发生数据，DI为2表示结束数据
输入参数：
		uchar8 *P_Data:写数据缓存；
		ushort16 V_Data_Length：写数据具体长度；
		Str_3dEventTable *P_Str_3dEventTableAddr：对应4级表格首地址；
		ulong32 V_Data_Id：DI0-DI3数据标识；
		ushort16 V_3dTable_Line：要操作3d级表格行号；
		uchar8 V_Type:数据存储类型
输出参数：无
返回参数：C_OK、C_SafeFlagError、C_SPIError,C_IICError，C_NoAccess，C_DataLenError；
功能说明：
调用机制：
备     注：写Flash数据，内部没有跨页操作
*********************************************************************************/
/*#define C_TempRAM_Max 512		临时缓存，事件最大长度*/
uchar8 SF_WriteFlash_DataEventTable(uchar8 *P_Data, ushort16 V_Data_Length, Str_3dEventTable *P_Str_3dEventTableAddr,
									ulong32 V_Data_Id, ushort16 V_3dTable_Line, uchar8 V_Type)
{
	uchar8 P_Dgree[CLAll_Loss_Vol_Degree];
	ushort16 V_E2Addr;
	ulong32 V_Dgree;
	Str_3dEventTable VStr_3dEventTableAddr;
	ulong32 P_FlashAddr1[2];
	uchar8 V_Return_Flag;
	uchar8 V_EvenSign;
	ushort16 V_Data_TolLength;

	if(V_3dTable_Line >= Str_3dTable_Flash_Len)
	{
		return C_AbnormalError;		/*正常不存在*/
	}

	VStr_3dEventTableAddr = P_Str_3dEventTableAddr[V_3dTable_Line];
	V_EvenSign = (uchar8)(V_Data_Id & 0x000000FF);		/*取DI0*/
	if((1 != V_EvenSign) && (2 != V_EvenSign))			/*1发生数据，2结束数据*/
	{
		return C_NoAccess;
	}

	V_E2Addr = VStr_3dEventTableAddr.V_Num_E2BakeUp1Addr;		/*取Flash记录次数E2地址*/

	V_Return_Flag = SF_ReadE2Three(V_E2Addr, CLAll_Loss_Vol_Degree, &P_Dgree[0]);
	if( (C_OK != V_Return_Flag) && (C_CrcErr_DataZero != V_Return_Flag) )
	{
		return V_Return_Flag;
	}

	PF_Buffer4ToUlong32(&P_Dgree[0], &V_Dgree,4);
	GV_D_SafeFlag = C_W_SafeFlag_2 | GV_D_SafeFlag;				/*置安全标志*/

	if(1 == V_EvenSign)		/*约定写发生，DI0为1*/
	{
		V_Dgree = V_Dgree + 1;
	}

	/*获取列表对应数据长度*/
	V_Data_TolLength = SF_GetEventDataLen(VStr_3dEventTableAddr.V_TB_E2BakeUp1Addr, VStr_3dEventTableAddr.V_TBLen_E2BakeUp1Addr,
											VStr_3dEventTableAddr.PStr_4aTableAddr, VStr_3dEventTableAddr.V_Str_4aTableLen);
	if((0==V_Data_TolLength)||(0xFFFF==V_Data_TolLength))
	{
		GV_D_SafeFlag=C_Clear_SafeFlag;
		return C_DataLenError;
	}

	if(V_Data_TolLength!=V_Data_Length)
	{
		GV_D_SafeFlag=C_Clear_SafeFlag;
		return C_DataLenError;
	}

	SF_GetFlashAddr(V_Dgree,VStr_3dEventTableAddr.V_StaFlashAddr,V_Data_TolLength,VStr_3dEventTableAddr.V_EndFlashAddr,&P_FlashAddr1[0]);
	GV_D_SafeFlag=C_W_SafeFlag_3|GV_D_SafeFlag; 	/*置安全标志*/
	/*读要写入Flash，然后覆盖判断写入*/
	P_FlashAddr1[0]=P_FlashAddr1[0]+P_FlashAddr1[1];
	if(P_FlashAddr1[0]>C_Flash_Max_Addr)	/*Flash地址错误，理论不存在 */
	{
		GV_D_SafeFlag=C_Clear_SafeFlag;
		return C_AbnormalError;
	}

	if(C_W_SafeFlag!=GV_D_SafeFlag)
	{
		return C_SafeFlagError;
	}

	V_Return_Flag=SF_WriteFlash(P_FlashAddr1[0],&P_Data[0],V_Data_TolLength,V_EvenSign);
	if(C_OK!=V_Return_Flag)
	{
		GV_D_SafeFlag=C_Clear_SafeFlag;
		return V_Return_Flag;
	}

	PF_Ulong32ToBuffer4(&P_Dgree[0],&V_Dgree,4);
	if(1==V_EvenSign)	/*约定写发生，DI0为1*/
	{
		V_Return_Flag=SF_WriteE2Three(V_E2Addr,CLAll_Loss_Vol_Degree,&P_Dgree[0]);	/*写E2记录次数*/
	}
	GV_D_SafeFlag=C_Clear_SafeFlag;
	return V_Return_Flag;
}

/*********************************************************************************
函数原型：uchar8 SF_WR_E21CRC_Data698(ushort16 V_E2Addr, ushort16 V_DataLen, uchar8 *P_Data)
功能描述：写E21处数据,带CRC
输入参数：
		ushort16V_E2Addr：写入数据E2地址；
		ushort16V_DataLen：要写入数据长度
		uchar8*P_Data：要写入数据缓存
输出参数：无
返回参数：C_OK、C_SafeFlagError、C_IICError；
功能说明：
调用机制：
备     注：写入不读比较
*********************************************************************************/
uchar8 SF_WR_E21CRC_Data698(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data)
{
	uchar8 V_Return_Flag;
	uchar8 P_CRC[2];
	ushort16 V_CRC16;

	GV_D_SafeFlag=C_W_SafeFlag_2|GV_D_SafeFlag;	/*置安全标志*/

	V_CRC16=PF_Cal_CRC(&P_Data[0],V_DataLen);	/*计算CRC*/
	PF_Ushort16ToBuffer2(&P_CRC[0],&V_CRC16);

	GV_D_SafeFlag=C_W_SafeFlag_3|GV_D_SafeFlag;	/*置安全标志*/

	if(C_W_SafeFlag!=GV_D_SafeFlag)
	{
		return C_SafeFlagError;
	}

	InF_E2WPEnable();
	if(C_W_SafeFlag!=GV_D_SafeFlag)		/*安全标志错*/
	{
		InF_E2WPDisable();	/*关闭WP*/
		GV_D_SafeFlag=C_Clear_SafeFlag;
		return C_SafeFlagError;
	}
	V_Return_Flag=InF_WriteE2(V_E2Addr,P_Data,V_DataLen);
	InF_E2WPEnable();
	V_Return_Flag=InF_WriteE2((V_E2Addr+V_DataLen),&P_CRC[0],2);	/*写CRC*/

	return V_Return_Flag;
}

/*********************************************************************************
函数原型：uchar8 InF_Write_Data(uchar8 Msg_Num, ulong32 V_Data_Id, uchar8 *P_Data, ushort16 V_Data_Length, uchar8 V_W_Safe_Flag);
功能描述：写数据层接口函数
输入参数：
		uchar8 Msg_Num:消息号，用于判断是否有写权限；
		ulong32 V_Data_Id：数据标识码；
		uchar8 *P_Data：数据所放缓存；
		ushort16 V_Data_Length：所写数据长度；
		uchar8 V_W_Safe_Flag：宏定义，当写安全标志；
输出参数：无
返回参数：C_OK、C_IICError、C_SPIError、C_DataLenError、C_IDError、C_SafeFlagError、C_NoAccess；
功能说明：
调用机制：
备     注：写数据层时调用，注意安全标志
*********************************************************************************/
uchar8 InF_Write_Data(uchar8 Msg_Num,ulong32 V_Data_Id,uchar8 *P_Data,ushort16 V_Data_Length,uchar8 V_W_Safe_Flag)
{
	uchar8 V_Return_Flag,V_WR_Mes;
	ushort16 V_Line,V_3TableE2Addr;
	Str_2Table *PStr_2TableAddr;
	Str_3aTable *PStr_3aTableAddr;
	uchar8 *P_3TableRamAddr;
	Str_3cTable *P_Str_3cTableAddr;
	uchar8 V_DI[4];
	ushort16 V_DataLen;
	Str_3dEventTable *P_Str_3dEventTableAddr;

	GV_D_SafeFlag = C_W_SafeFlag_1; 	/*置安全标志,第一次赋值，采用直接赋值的方式，避免之前有错误的位*/

	PF_Ulong32ToBuffer4(&V_DI[0],&V_Data_Id,4);

	V_DataLen=V_Data_Length;

	if(V_W_Safe_Flag!=C_W_SafeFlag)
	{
		return C_SafeFlagError;
	}

	if( (V_Data_Id&0xFFFF0000) == 0xFF860000)	/*自扩对象处理*/
	{
		V_Return_Flag = SF_Deal_FF86(V_Data_Id, P_Data, V_Data_Length);

		return V_Return_Flag;
	}

	if(0x50==V_DI[3])	/*******698写冻结数据********/
	{
		V_Return_Flag=SF_Write698FreezeData(V_DI[2],Msg_Num,P_Data,V_Data_Length);
		return V_Return_Flag;
	}

	/******************************以下为通用数据操作**********************************************/
	V_Return_Flag=SF_Find1Table_Data(V_DI[3],&V_Line);
	if(V_Return_Flag!=C_OK)
	{
		 return V_Return_Flag;
	}

	V_WR_Mes=C_WR_Data&Msg_Num;		/*写操作*/

	if(0x04==V_DI[3])				/*参变量查2级分表，特殊处理。增加变量操作效率*/
	{
		V_Return_Flag=SF_Find2Table_DIParamChild(V_DI[2],&V_Line);
		if(V_Return_Flag!=C_OK)
		{
			return V_Return_Flag;
		}

		PStr_2TableAddr=(Str_2Table *)(Str_2Table_DIParamChild[V_Line].PStr_2TableParamChildAddr);	/*DI2对应的2级表地址*/
		V_Return_Flag=SF_Find2Table_Data(V_WR_Mes,V_Data_Id,&V_Data_Length,PStr_2TableAddr,&V_Line,Str_2Table_DIParamChild[V_Line].V_Str_2TableLen);
	}
	else
	{
		PStr_2TableAddr=(Str_2Table * )(Str_1Table_DI3[V_Line].PStr_2TableAddr);	/*DI3对应的2级表地址*/
		V_Return_Flag=SF_Find2Table_Data(V_WR_Mes,V_Data_Id,&V_Data_Length,PStr_2TableAddr,&V_Line,Str_1Table_DI3[V_Line].V_Str_2TableLen);
	}

	if(V_Return_Flag!=C_OK)
	{
		return V_Return_Flag;
	}

	switch(PStr_2TableAddr[V_Line].V_DT_Type)   /*DI2-DI0对应2级表具体的行号，不同数据处理方式*/
	{
		case DT_Ref_E23_RAMCRC:                   /*①E2三处CRC备份及RAM带CRC(写该类数据时，先写RAM，接着更新E2数据)*/
		case DT_Ref_E23_RAMCRC_DI0:               /*19：E2三处RAM带CRC，数据长度类型一样(同一DI3-DI1)，列表格时只列DI0最大值(不包括DI0=0，DI0=0要单列)，程序内部处理，*/
		                                          /*数据地址及DI判断是否正确，如类似组合状态字，列表格时，对应数据存储地址，为最低DI0对应数据存储地址，注意*/
		case DT_W_Ref_E23_RAMCRC_Te:              /*26:写E2 RAM数据，写入时模块一起写入，数据层内部单独处理，分开写，如当前套费率电价数据块*/
		case DT_Ref_E23_RAMCRC_DI0_2:             /*28：E2三处RAM带CRC，数据长度类型一样(同一DI3-DI1)，列表格时只列DI0最大值(不包括DI0=0，1,DI0=0,1要单列)，程序内部处理，*/
		{                                           /*数据地址及DI判断是否正确，如类似全失压电流该类参数设置，列表格时，对应数据存储地址(电压异常判断电压地址)，为最低DI0对应数据存储地址，注意*/
			PStr_3aTableAddr=(Str_3aTable *)PStr_2TableAddr[V_Line].PStr_3TableAddr;   /*取3级表地址*/
			if((V_Data_Id&0xFFFFFF00)==(CL_Free_OADTab&0xFFFFFF00))/*冻结OAD序号表,写数据不判断数据长度，但判断写数据长度不能大于最大长度*/
			{
				V_Return_Flag=SF_WR_E23_RAM_Data698(&PStr_3aTableAddr[PStr_2TableAddr[V_Line].V_LineNum],V_Data_Length,P_Data,PStr_2TableAddr[V_Line].V_DT_Type,V_DI[0]);
			}
			else
			{
				V_Return_Flag=SF_WR_E23_RAM_Data(PStr_3aTableAddr,PStr_2TableAddr[V_Line].V_LineNum,V_Data_Length,P_Data,PStr_2TableAddr[V_Line].V_DT_Type,V_DI[0]);
			}
		}break;

		case DT_Ti_E23_RAMCRC:                    /*②E2三处CRC备份及RAM带CRC(写该类数据时，只写RAM，定时写E2，主要是当前电量该类数据)。注意：目前698软件可靠性用于写铁电及RAM三处 */
		{
			PStr_3aTableAddr=(Str_3aTable *)PStr_2TableAddr[V_Line].PStr_3TableAddr;   /*取3级表地址*/
			V_Return_Flag=SF_WR_E23_RAM_EnergyData(PStr_3aTableAddr,PStr_2TableAddr[V_Line].V_LineNum,V_Data_Length,P_Data,PStr_2TableAddr[V_Line].V_DT_Type,V_DI[0]);
		}break;

		case DT_E23:                              /*③E2三处CRC备份*/
		case DT_E23_Clear:                              /*③E2三处CRC备份*/
		case DT_E23_Hex:                          /*⑧E2三处CRC备份，数据存储格式为hex格式(主要是累计次数，在通讯读该数据时，转换为BCD格式)*/
#if 0
		case DT_E23_En:                           /*16：电量类数据，满足6+2与6+4数据长度时，该数据需单独处理，数据长度(读、写)及所读数据，根据是否是6+4(类似显示),或6+2(类似通信)，进行特殊处理*/
		                                          /*(列表645数据长度为6+2，当采用6+4读数据时，返回数据长度调整，取E2地址调整，如上1结算周期内组合有功累计用电量),写数据时，数据长度判断调整；*/
		case DT_E23_En_Clear:                           /*16：电量类数据，满足6+2与6+4数据长度时，该数据需单独处理，数据长度(读、写)及所读数据，根据是否是6+4(类似显示),或6+2(类似通信)，进行特殊处理*/
		                                          /*(列表645数据长度为6+2，当采用6+4读数据时，返回数据长度调整，取E2地址调整，如上1结算周期内组合有功累计用电量),写数据时，数据长度判断调整；*/
#endif
		case DT_E23_DI0:                          /*20：E2三处，E2地址顺序列，数据长度类型一样(同一DI3-DI1)，列表格时只列DI0最大值(不包括DI0=0，DI0=0要单列)，程序内部处理，*/
		                                         /*数据地址及DI判断是否正确，如类似结算日、密码，列表格时，对应数据存储地址，为最低DI0对应数据存储地址，注意*/
		case DT_E23_OADTab:                       /*38:存E2三处，判断数据长度时，需读取该关联列表OAD个数*/
		{
			if(DT_E23_OADTab==PStr_2TableAddr[V_Line].V_DT_Type)
			{
				Str_3eTable *PStr_3eTable_2E2=NULL;

				PStr_3eTable_2E2=(Str_3eTable *)(PStr_2TableAddr[V_Line].PStr_3TableAddr);

				if(PStr_2TableAddr[V_Line].V_LineNum>=Str_3eTable_Flash_Len)
				{
					return C_DataLenError;
				}

				V_3TableE2Addr=PStr_3eTable_2E2[PStr_2TableAddr[V_Line].V_LineNum].V_E2BakeUp1Addr_OADTab;
			}
			else
			{
				V_3TableE2Addr=(ushort16)PStr_2TableAddr[V_Line].PStr_3TableAddr;   /*取3级表E2地址*/
			}

			if(DT_E23_DI0==PStr_2TableAddr[V_Line].V_DT_Type)    /*E2地址调整*/
			{
				if(0==V_DI[0])
				{
					return C_IDError;              /*正常不存在*/
				}

				V_3TableE2Addr=V_3TableE2Addr+(V_DI[0]-1)*(V_DataLen+C_CRCLen2);
				if(V_3TableE2Addr>E2_Max_Addr)
				{
					return C_IDError;              /*正常不存在*/
				}
			}

			V_Return_Flag=SF_WR_E23_Data(V_3TableE2Addr,V_Data_Length,P_Data);
		}break;

		case DT_Flash_DI04:                       /*④Flash，带次数数据，DI0低4位表示次数，高4位表示不同标识码(查询4级表用)*/
		case DT_Flash_Tol_DI0_DI1:                /*⑨Flash，带次数数据，整个DI0表示次数，DI1表示分项标识码(查询4级表用)*/
#if 0
		case DT_Flash_Tol_DI0_DI2:                /*11： Flash，带次数数据，整个DI0表示次数，DI2表示分项标识码(查询4级表用，主要是电量、需量，ABC三相数据)*/
		case DT_Flash_Tol_DI0_SettEn:              /*12：Flash，带次数数据，整个DI0表示次数，利用DI2、DI1计算分项偏移地址(代替查询4级表，主要是结算电量读，除ABC三相数据外)。*/
		case DT_Flash_Tol_DI0_SettDe:              /*13：Flash，带次数数据，整个DI0表示次数，利用DI2、DI1计算分项偏移地址(代替查询4级表，主要是结算需量读，除ABC三相数据外)。*/
		case DT_Flash_Tol_DI0_W_Sett_En:           /*14：Flash，带次数数据，整个DI0表示次数。结算模块写数据时一起写数据层，数据层内部，结算电量及结算日时间分开存储，该标识码只支持写*/
#endif
		case DT_Flash_Tol_DI0:                    /*15： Flash，带次数数据，整个DI0表示次数。没有分项标识码。*/
		case DT_Flash_Tol_DI0_DI1Max:             /*27： Flash，带次数数据，整个DI0表示次数，列表2级表时只列上1次DI1最大值(不采用查找4级表的方式)，在查找数据DI及DI数据存放偏移地址时，*/
		{                                      /*OffsetAddr程序采用计算方式处理,目前只有校表记录采用该方式,除发生时刻DI1=0外*/
			P_Str_3cTableAddr=(Str_3cTable *)PStr_2TableAddr[V_Line].PStr_3TableAddr;
			V_Return_Flag=SF_WriteFlash_Data(P_Data,V_Data_Length,P_Str_3cTableAddr,V_Data_Id,PStr_2TableAddr[V_Line].V_LineNum,PStr_2TableAddr[V_Line].V_DT_Type);
		}break;

		case DT_Flash_698EventTab:		/*37:带OAD关联列表事件记录，存Flash*/
		{
			P_Str_3dEventTableAddr=(Str_3dEventTable *)PStr_2TableAddr[V_Line].PStr_3TableAddr;
			V_Return_Flag=SF_WriteFlash_DataEventTable(P_Data,V_Data_Length,P_Str_3dEventTableAddr,V_Data_Id,PStr_2TableAddr[V_Line].V_LineNum,PStr_2TableAddr[V_Line].V_DT_Type);
		}break;

		case DT_E21:                              /*⑤E2一处*/
#if 0
		case DT_E21_En:                           /*17：电量类数据，满足6+2与6+4数据长度时，该数据需单独处理，数据长度(读、写)及所读数据，根据是否是6+4(类似显示),或6+2(类似通信)，进行特殊处理,主要针对存E2 1处数据*/
			                                        /*(列表645数据长度为6+2，当采用6+4读数据时，返回数据长度调整，取E2地址调整，如上1--4次年结算日结算时间及结算周期组合有功总累计用电量*/
#endif
		case DT_E21_DI0:                          /*22：E2一处，数据长度类型一样(同一DI3-DI1)，列表格时只列DI0最大值(不包括DI0=0，DI0=0要单列)，程序内部处理，*/
			                                        /*数据地址及DI判断是否正确，如类似第1-254公共假日日期及日时段表号，列表格时，对应数据存储地址，为最低DI0对应数据存储地址，注意*/
		{
			V_3TableE2Addr=(ushort16)PStr_2TableAddr[V_Line].PStr_3TableAddr;   /*取3级表E2地址*/
			/*if((DT_E21_DI0==PStr_2TableAddr[V_Line].V_DT_Type)
				||(DT_E21_DI0_ReadDegree==PStr_2TableAddr[V_Line].V_DT_Type))*/    /*E2地址调整*/
			if( DT_E21_DI0 == PStr_2TableAddr[V_Line].V_DT_Type )
			{
				if(0==V_DI[0])
				{
					return C_IDError;              /*正常不存在*/
				}

				V_3TableE2Addr=V_3TableE2Addr+(V_DI[0]-1)*V_DataLen;
				if(V_3TableE2Addr>E2_Max_Addr)
				{
					return C_IDError;              /*正常不存在*/
				}
			}

			V_Return_Flag=SF_WR_E21_Data(V_3TableE2Addr,V_Data_Length,P_Data);
		}break;

		case DT_RAM:                              /*⑥RAM不带CRC*/
		case DT_RAM_Time_Data:                    /*⑩RAM不带CRC，读数据时先判断掉电标志。*/
		case DT_RAM_DI0:	                        /*18：数据存RAM不带CRC，且数据长度、类型一样(同一DI3-DI1)，列表格时只列DI0最大值(,同一类型，不包括DI0=0，DI0=0要单列)，程序内部处理，*/
		                                          /*数据地址及DI判断是否正确，如类似电表运行状态字1-7，列表格时，对应数据存储地址，为最低DI0对应数据存储地址，注意*/
#if 0
		case DT_RAM_DI1_0:                        /*23：数据存RAM不带CRC，且数据长度、类型一样(同一DI3-DI2、DI0)，列表格时只列DI1最大值(,同一类型,包括DI1=0，计算数据偏移地址时，要考虑)，*/
			                                        /*程序内部处理，数据地址及DI判断是否正确，如类似参数瞬时功率，列表格时，对应数据存储地址，为最低DI1对应数据存储地址，注意*/
		case DT_RAM_DI1:	                        /*24：数据存RAM不带CRC，且数据长度、类型一样(同一DI3-DI2、DI0)，列表格时只列DI1最大值(,同一类型，不包括DI1=0)，程序内部处理，*/
#endif
		{                                      /*数据地址及DI判断是否正确，如类似电压数据，列表格时，对应数据存储地址，为最低DI1对应数据存储地址，注意*/
			P_3TableRamAddr=(uchar8 *)PStr_2TableAddr[V_Line].PStr_3TableAddr;

			if(DT_RAM_DI0==PStr_2TableAddr[V_Line].V_DT_Type)
			{
				if(0==V_DI[0])
				{
					return C_IDError;		/*正常不存在*/
				}
				P_3TableRamAddr=P_3TableRamAddr+(V_DI[0]-1)*V_DataLen;
			}
#if 0
			if(DT_RAM_DI1_0==PStr_2TableAddr[V_Line].V_DT_Type)
			{
				P_3TableRamAddr=P_3TableRamAddr+V_DI[1]*V_DataLen;
			}

			if(DT_RAM_DI1==PStr_2TableAddr[V_Line].V_DT_Type)
			{
				if(0==V_DI[1])
				{
					return C_IDError;		/*正常不存在*/
				}
				P_3TableRamAddr=P_3TableRamAddr+(V_DI[1]-1)*V_DataLen;
			}
#endif
			GV_D_SafeFlag=C_W_SafeFlag_2|GV_D_SafeFlag;		/*置安全标志*/
			V_Return_Flag=SF_WR_RAM_Data(P_3TableRamAddr,V_Data_Length,P_Data,PStr_2TableAddr[V_Line].V_DT_Type,Msg_Num);
		}break;

		case DT_RAMCRC:                           /*⑦RAM带CRC*/
		{
			P_3TableRamAddr=(uchar8 *)PStr_2TableAddr[V_Line].PStr_3TableAddr;
			GV_D_SafeFlag=C_W_SafeFlag_2|GV_D_SafeFlag;		/*置安全标志*/
			V_Return_Flag=SF_WR_RAMCRC_Data(P_3TableRamAddr,V_Data_Length,P_Data);
		}break;

		case DT_E21CRC_DI0:			/*21：E2一处带CRC，数据长度类型一样(同一DI3-DI1)，列表格时只列DI0最大值(不包括DI0=0，DI0=0要单列)，程序内部处理，*/
									/*数据地址及DI判断是否正确，如类似自动循显显示第1-99屏显示代码，列表格时，对应数据存储地址，为最低DI0对应数据存储地址，注意*/
		case DT_E21CRC_MaxLen:		/*40：E2一处带CRC，写入时判断不超过最大数据长度*/
		{
			V_3TableE2Addr=(ushort16)PStr_2TableAddr[V_Line].PStr_3TableAddr;		/*取3级表E2地址*/

			if(DT_E21CRC_DI0==PStr_2TableAddr[V_Line].V_DT_Type)		/*E2地址调整*/
			{
				if(0==V_DI[0])
				{
					return C_IDError;	/*正常不存在*/
				}

				V_3TableE2Addr=V_3TableE2Addr+(V_DI[0]-1)*(V_DataLen+C_CRCLen2);

				if(V_3TableE2Addr>E2_Max_Addr)
				{
					return C_IDError;	/*正常不存在*/
				}
			}

			/*写数据长度大于255，不进行写入、读出判断。直接写不读出，不然数据层缓存太大*/
			if(DT_E21CRC_MaxLen==PStr_2TableAddr[V_Line].V_DT_Type)
			{
				V_Return_Flag=SF_WR_E21CRC_Data698(V_3TableE2Addr,V_Data_Length,P_Data);
			}
			else
			{
				V_Return_Flag=SF_WR_E21CRC_Data(V_3TableE2Addr,V_Data_Length,P_Data);
			}
		}break;

		case DT_FRAM1CRC:		/*42：铁电一处带CRC*/
		{
			V_3TableE2Addr=(ushort16)PStr_2TableAddr[V_Line].PStr_3TableAddr;		/*取3级表铁电地址*/
			V_Return_Flag=SF_WR_FRAM1CRC_Data(V_3TableE2Addr,V_DataLen,P_Data);
		}break;

		default:
			return C_IDError;		/*查找错误*/
	}

	GV_D_SafeFlag=C_Clear_SafeFlag;		/*清安全标志*/

	return V_Return_Flag;
}

/*********************************************************************************
函数原型：uchar8 SF_Find2Table_DIParamChild(uchar8 V_Data_Id2, ushort16 *P_Line)
功能描述：2级分表查询函数,得到DI2对应的2级表行号
输入参数：
		uchar8 V_Data_Id2：数据标识码DI2；
输出参数：
		ushort16 *P_Line：查找2级表对应行号；
返回参数：C_OK、C_IDError；
功能说明：
调用机制：
备注：
*********************************************************************************/
uchar8 SF_Find2Table_DIParamChild(uchar8 V_Data_Id2, ushort16 *P_Line)
{
	ushort16 V_Line;

	for(V_Line=0;V_Line<Str_2Table_DIParamChild_Len;V_Line++)
	{
		if(V_Data_Id2==Str_2Table_DIParamChild[V_Line].V_DI2)
		{
			break;
		}
	}

	if(V_Line==Str_2Table_DIParamChild_Len)
	{
		return C_IDError;
	}
	else
	{
		*P_Line=V_Line;
		return C_OK;
	}
}

/*********************************************************************************
函数原型：uchar8 SF_Find1Table_Data(uchar8 V_Data_Id3, ushort16 *P_Line)
功能描述：1级表查询函数,得到DI3对应的1级表行号
输入参数：
		uchar8V_Data_Id3：数据标识码DI3；
输出参数：
		ushort16*P_Line：查找1级表对应行号；
返回参数：C_OK、C_IDError；
功能说明：
调用机制：
备     注：
*********************************************************************************/
uchar8 SF_Find1Table_Data(uchar8 V_Data_Id3, ushort16 *P_Line)
{
	ushort16 V_Line;

	for(V_Line=0;V_Line<Str_1Table_DI3_Len;V_Line++)
	{
		if(V_Data_Id3==Str_1Table_DI3[V_Line].V_DI3)
		{
			break;
		}
	}

	if(V_Line==Str_1Table_DI3_Len)
	{
		return C_IDError;
	}
	else
	{
		*P_Line=V_Line;
		return C_OK;
	}
}

/*********************************************************************************
函数原型：ushort16 SF_GetOADTabNum(Str_2Table V_Str_2Table)
功能描述：获取关联列表OAD长度,内部已经*2
输入参数：
		Str_2TableV_Str_2Table:关联列表所在2级表结构体
输出参数：无
返回参数：返回相应关联OAD列表长度，异常为FFFF
功能说明：
调用机制：
备     注：内部关联OAD个数*关联OAD列表格式
*********************************************************************************/
ushort16 SF_GetOADTabNum(Str_2Table V_Str_2Table)
{
	Str_3eTable *PStr_3eTable_2E2=NULL;
	uchar8 V_Return_Flag,V_Data;
	ushort16 V_Data_Length=0xFFFF;

	PStr_3eTable_2E2=(Str_3eTable *)(V_Str_2Table.PStr_3TableAddr);

	if(V_Str_2Table.V_LineNum>=Str_3eTable_Flash_Len)	/*正常不存在*/
	{
		return V_Data_Length;
	}

	V_Return_Flag=SF_ReadE2Three(PStr_3eTable_2E2[V_Str_2Table.V_LineNum].V_E2BakeUp1Addr_OADTabLen,CLAll_Loss_Vol_OADTabLen,&V_Data);
	if(C_OK==V_Return_Flag)
	{
		V_Data_Length=V_Data*C_698Event_OADTabDataType;
	}
	return	V_Data_Length;
}

/*********************************************************************************
函数原型：uchar8 SF_Find2Table_Data(uchar8 V_WR_Mes, ulong32 V_Data_Id, ushort16 *P_Data_Length,
									Str_2Table *PStr_2Table, ushort16 *P_Line, ushort16 V_MaxLine)
功能描述：2级表查询函数，得到DI2-DI0对应的2级表行号
输入参数：
		uchar8 V_WR_Mes:消息号及读写标志,当读数据为类似显示模块时(电量类数据长度为6+4)，则调用该函数前，入口进行特殊处理为显示消息读；
		ulong32 V_Data_Id：数据标识码DI2~DI0；
		ushort16 *P_Data_Length：写数据时，表示所写数据长度；读数据时，所读数据长度，作为输入参数时，该参数值为模块所读
		数据缓存长度最大值，用于数据层判断，所读数据长度，是否溢出，如溢出则返回数据长度错误。
		Str_2Table *PStr_2Table：1级表查询中对应2级表结构体地址；
		ushort16 V_MaxLine:对应2级表结构体数组长度
输出参数：
		ushort16 *P_Line：查找2级表对应行号；
		ushort16 *P_Data_Length：返回实际读数据长度；
返回参数：C_OK、C_IDError、C_DataLenError、C_NoAccess；
功能说明：
调用机制：
备     注：内部判断数据长度及读写操作
*********************************************************************************/
uchar8 SF_Find2Table_Data(uchar8 V_WR_Mes,ulong32 V_Data_Id,ushort16 *P_Data_Length,Str_2Table *PStr_2Table,ushort16 *P_Line,ushort16 V_MaxLine)
{
	ushort16 V_Line, V_Data_Length, V_Data_LengthTemp;
	uchar8 V_i;

	for(V_Line = 0; V_Line < V_MaxLine; V_Line++)
	{
		if(V_Data_Id == PStr_2Table[V_Line].V_DI)
		{
			break;
		}
		else
		{
			if(DT_Flash_DI04==PStr_2Table[V_Line].V_DT_Type)	/*Flash，带次数数据，DI0低4位表示次数，高4位表示不同标识码(查询4级表用)*/
			{
				if(0x00000000==(V_Data_Id&0x0000000F))		/*次数不为0*/
				{
					continue;
				}
				if((V_Data_Id&0xFFFFFFF0)==(PStr_2Table[V_Line].V_DI&0xFFFFFFF0))	/*DI0低4位不比较*/
				{
					break;
				}
			}
			else
			{
				if( (DT_Flash_Tol_DI0_DI1==PStr_2Table[V_Line].V_DT_Type)/*||(DT_Flash_Tol_DI0_DI2==PStr_2Table[V_Line].V_DT_Type)
					|| (DT_Flash_Tol_DI0_SettEn==PStr_2Table[V_Line].V_DT_Type)||(DT_Flash_Tol_DI0_SettDe==PStr_2Table[V_Line].V_DT_Type)
					|| (DT_Flash_Tol_DI0_W_Sett_En==PStr_2Table[V_Line].V_DT_Type)||(DT_R_Flash_Tol_DI0_DI2_En==PStr_2Table[V_Line].V_DT_Type)*/
					|| (DT_Flash_Tol_DI0==PStr_2Table[V_Line].V_DT_Type) )	/*DI0表示次数*/
				{
					if(0x00000000==(V_Data_Id&0x000000FF))		/*次数不为0*/
					{
						continue;
					}

					if((V_Data_Id&0xFFFFFF00)==(PStr_2Table[V_Line].V_DI&0xFFFFFF00))	/*DI0不比较*/
					{
						break;
					}
				}
				else
				{
					if( (DT_RAM_DI0==PStr_2Table[V_Line].V_DT_Type)||(DT_Ref_E23_RAMCRC_DI0==PStr_2Table[V_Line].V_DT_Type)
						|| (DT_E23_DI0==PStr_2Table[V_Line].V_DT_Type)||(DT_E21CRC_DI0==PStr_2Table[V_Line].V_DT_Type)
						|| (DT_E21_DI0==PStr_2Table[V_Line].V_DT_Type)||(DT_Ref_E23_RAMCRC_DI0_2==PStr_2Table[V_Line].V_DT_Type)
						/*||(DT_E21_DI0_ReadDegree==PStr_2Table[V_Line].V_DT_Type)*/ /*只列DI0最大值，且DI0不为0*/
						)
					{
						if((V_Data_Id&0xFFFFFF00)==(PStr_2Table[V_Line].V_DI&0xFFFFFF00))	/*DI0不比较*/
						{
							if((0x00000000!=(V_Data_Id&0x000000FF))	/*DI0不为零，且≤最大值*/
								&&((V_Data_Id&0x000000FF)<=(PStr_2Table[V_Line].V_DI&0x000000FF)))
							{
								break;
							}
						}
					}
					else
					{
#if 0
						if(DT_RAM_DI1_0==PStr_2Table[V_Line].V_DT_Type)    /*只列DI1最大值，DI1可以为0*/
						{
							if((V_Data_Id&0xFFFF00FF)==(PStr_2Table[V_Line].V_DI&0xFFFF00FF))/*DI1不比较*/
							{
								if((V_Data_Id&0x0000FF00)<=(PStr_2Table[V_Line].V_DI&0x0000FF00))/*DI1＜=最大值*/
								{
									break;
								}
							}
						}
						else
						{

							if(DT_RAM_DI1==PStr_2Table[V_Line].V_DT_Type)    /*只列DI1最大值，且DI1不为0*/
							{
								if((V_Data_Id&0xFFFF00FF)==(PStr_2Table[V_Line].V_DI&0xFFFF00FF))/*DI1不比较*/
								{
									if(((V_Data_Id&0x0000FF00)<=(PStr_2Table[V_Line].V_DI&0x0000FF00))
										&&(0x00000000!=(V_Data_Id&0x0000FF00)))/*DI1＜=最大值,且DI1不为0*/
									{
										break;
									}
								}
							}
							else
							{
#endif
								if(DT_Flash_Tol_DI0_DI1Max==PStr_2Table[V_Line].V_DT_Type) /*只列DI1最大值，且DI1不为0,DI0表示次数且不为零*/
								{
									if((V_Data_Id&0xFFFF0000)==(PStr_2Table[V_Line].V_DI&0xFFFF0000))	/*DI0、DI1不比较*/
									{
										if(0x00000000==(V_Data_Id&0x000000FF))		/*次数不为0*/
										{
											continue;
										}

										if(((V_Data_Id&0x0000FF00)<=(PStr_2Table[V_Line].V_DI&0x0000FF00))
											&&(0x00000000!=(V_Data_Id&0x0000FF00)))		/*DI1＜=最大值,且DI1不为0*/
										{
											break;
										}
									}
								}
								else
								{
									if(DT_Flash_698EventTab==PStr_2Table[V_Line].V_DT_Type)/*不判断DI 0，次数，698事件发生及结束*/
									{
										if((V_Data_Id&0xFFFFFF00)==(PStr_2Table[V_Line].V_DI&0xFFFFFF00))
										{
											break;
										}
									}
								}
#if 0
							}
						}
#endif
					}
				}
			}
		}
	}

	if(V_Line==V_MaxLine)
	{
		return C_IDError;
	}
	else
	{
		if(V_WR_Mes&0x80)	/*读数据*/
		{
			if(PStr_2Table[V_Line].V_WR_MesAuth&0x80)/*所读数据是否支持读*/
			{
#if 0
				if(C_Msg_Display!=(V_WR_Mes&0x7F))                   /*判断是否为类似显示模块读，电量类--特殊数据--长度需单独处理,不支持显示类，数据块读*/
				{
					V_Data_Length=PStr_2Table[V_Line].V_DataLen;
				}
				else
				{
					switch(PStr_2Table[V_Line].V_DT_Type)
					{
						case DT_Flash_Tol_DI0_SettEn:
						case DT_E23_En:
						case DT_E23_En_Clear:
						case DT_E21_En:
						case DT_R_Flash_Tol_DI0_DI2_En:
						{
							V_Data_Length=PStr_2Table[V_Line].V_DataLen+1;
						}break;

						default:
						{
							V_Data_Length=PStr_2Table[V_Line].V_DataLen;
						}break;
					}
				}
#endif
				V_Data_Length=PStr_2Table[V_Line].V_DataLen;

				if(DT_Flash_698EventTab==PStr_2Table[V_Line].V_DT_Type)		/*数据长度需计算*/
				{
					Str_3dEventTable *P_Str_3dEventTableAddr=NULL;
					ushort16 V_3dEventTableLine;

					P_Str_3dEventTableAddr=(Str_3dEventTable *)PStr_2Table[V_Line].PStr_3TableAddr;

					if(PStr_2Table[V_Line].V_LineNum>=Str_3dTable_Flash_Len)
					{
						return C_DataLenError;
					}

					V_3dEventTableLine=PStr_2Table[V_Line].V_LineNum;
					V_Data_Length=SF_GetEventDataLen(P_Str_3dEventTableAddr[V_3dEventTableLine].V_TB_E2BakeUp1Addr,P_Str_3dEventTableAddr[V_3dEventTableLine].V_TBLen_E2BakeUp1Addr,P_Str_3dEventTableAddr[V_3dEventTableLine].PStr_4aTableAddr,P_Str_3dEventTableAddr[V_3dEventTableLine].V_Str_4aTableLen);
					if((0==V_Data_Length)||(0xFFFF==V_Data_Length))
					{
						return C_DataLenError;
					}
				}
				/*判断所读数据是否溢出*/
				if(V_Data_Length<=(*P_Data_Length))/*冻结OAD序号表,读数据也判断数据长度，缓存大于最大数据长度*/
				{
					*P_Line=V_Line;

					if(DT_E23_OADTab==PStr_2Table[V_Line].V_DT_Type)      /*38存E2三处，判断数据长度时，需读取该关联列表OAD个数*/
					{
						V_Data_LengthTemp=SF_GetOADTabNum(PStr_2Table[V_Line]);/*获取关联列表OAD个数,内部已经*2*/
						if(V_Data_LengthTemp>V_Data_Length)/*正常不存在*/
						{
							*P_Data_Length=V_Data_LengthTemp;
							return C_DataLenError;
						}
						else
						{
							V_Data_Length=V_Data_LengthTemp;
						}
					}

					*P_Data_Length=V_Data_Length;	/*返回所读数据长度*/
					return C_OK;
				}
				else	/*数据溢出*/
				{
					*P_Data_Length=V_Data_Length;	/*返回所读数据实际长度，根据蒋工要求20140629*/
					return C_DataLenError;
				}
			}
			else
			{
				return C_NoAccess;
			}
		}
		else	/*写数据*/
		{
			if(0x00==(V_WR_Mes&0x7F))	/*消息号全零，不支持写操作*/
			{
				return C_NoAccess;
			}

			*P_Line=V_Line;
#if 0
			switch(PStr_2Table[V_Line].V_DT_Type)          /*电量特殊类数据，数据长度调整*/
			{
				case DT_Flash_Tol_DI0_SettEn:
				case DT_E23_En:                /*目前寄存器汇总，只有该类数据支持写*/
				case DT_E23_En_Clear:
				case DT_E21_En:
				case DT_R_Flash_Tol_DI0_DI2_En:
				{
					V_Data_Length=PStr_2Table[V_Line].V_DataLen+1;
				}break;

				default:
				{
					V_Data_Length=PStr_2Table[V_Line].V_DataLen;
				}break;
			}
#endif
			V_Data_Length=PStr_2Table[V_Line].V_DataLen;

			if(((V_Data_Id&0xFFFFFF00)==(CL_Free_OADTab&0xFFFFFF00))
				||(DT_E23_OADTab==PStr_2Table[V_Line].V_DT_Type)
				||(DT_E21CRC_MaxLen==PStr_2Table[V_Line].V_DT_Type))/*冻结、事件OAD序号表,写数据不判断数据长度，但判断写数据长度不能大于最大长度*/
			{
				if((*P_Data_Length)>V_Data_Length)
				{
					return C_DataLenError;
				}
			}
			else	/*其他数据，正常判断数据长度*/
			{
				if(DT_Flash_698EventTab!=PStr_2Table[V_Line].V_DT_Type)/*698事件记录带关联OAD列表，写事件记录不判断数据长度。在具体写Flash操作时判断长度，避免复杂重复判断*/
				{
					if(V_Data_Length!=(*P_Data_Length))		/*写数据长度错*/
					{
						return C_DataLenError;
					}
				}
			}

			if(C_WR_All==PStr_2Table[V_Line].V_WR_MesAuth)
			{
				return C_OK;
			}
			else
			{
				if((V_WR_Mes&0x7F)==(PStr_2Table[V_Line].V_WR_MesAuth&0x7F))/*判断写权限,分项消息*/
				{
					return C_OK;
				}
				else
				{
					if(((PStr_2Table[V_Line].V_WR_MesAuth&0x7F)>=C_Com_Msg_Star)
						&&((PStr_2Table[V_Line].V_WR_MesAuth&0x7F)<(C_Com_Msg_Star+C_Com_Msg_Len_Max)))/*组合消息判断*/
					{
						V_i=(PStr_2Table[V_Line].V_WR_MesAuth&0x7F)-C_Com_Msg_Star;  /*组合消息表格行号*/

						for(V_Line=0;V_Line<C_Com_Msg_Len;V_Line++)              /*组合消息内分项消息判断*/
						{
							if((V_WR_Mes&0x7F)==GP_Com_Msg[V_i][V_Line])
							{
								break;
							}
						}

						if(C_Com_Msg_Len==V_Line)
						{
							return C_NoAccess;
						}
						else
						{
							return C_OK;
						}
					}
					else
					{
						return C_NoAccess;
					}
				}
			}
		}
	}
}

/*********************************************************************************
函数原型：uchar8 SF_GetMinFreezeTolNum(uchar8 *P_Data, ushort16 V_DataLen, ushort16 *PV_Cyc16)
功能描述：获取分钟冻结总方案数，及对应的各方案周期
输入参数：
		uchar8 *P_Data：分钟冻结关联列表；
		ushort16 V_DataLen：分钟冻结关联列表长度
输出参数：
		ushort16 *PV_Cyc16：输出不同方案对应的冻结周期，与方案一一对应，第1个周期就是方案0，依次类推
返回参数：方案1-8，异常FF；
功能说明：
调用机制：
备     注：周期不同则认为不同方案
*********************************************************************************/
uchar8 SF_GetMinFreezeTolNum(uchar8 *P_Data, ushort16 V_DataLen, ushort16 *PV_Cyc16)
{
	uchar8 V_i, V_j, V_k, V_Num = 0xFF;
	ushort16 V_OADOrder16;

	V_j = V_DataLen / C_698Free_OADTabDataType;			/*OAD列表个数*/
	PF_Buffer2ToUshort16(&P_Data[2], &PV_Cyc16[0]);		/*冻结周期*/
	V_Num = 1;

	for(V_i=1;V_i<V_j;V_i++)
	{
		PF_Buffer2ToUshort16(&P_Data[C_698Free_OADTabDataType*V_i+2],&V_OADOrder16);
		for(V_k=0;V_k<V_Num;V_k++)
		{
			if(V_OADOrder16==PV_Cyc16[V_k])				/*判断是否已经有周期相等*/
			{
				break;
			}
		}

		if(V_k>=V_Num)			/*新方案*/
		{
			V_Num+=1;
			if(V_Num>8)
			{
				return 0xFF;	/*异常*/
			}
			PV_Cyc16[V_Num-1]=V_OADOrder16;
		}
	}

	if(V_Num>8)
	{
		V_Num=0xFF;				/*异常*/
	}

	return V_Num;
}

/*********************************************************************************
函数原型：uchar8 SF_GetStr_698FreezeDataTableOrder(ulong32 V_Data_Id_OAD)
功能描述：获取某类冻结数据在Str_698FreezeDataTable中序号，
输入参数：ulong32 V_Data_Id_OAD：某类冻结标识码；
输出参数：无
返回参数：要查找的某类冻结在Str_698FreezeDataTable表格中序号，异常返回FF
功能说明：
调用机制：
备     注：
*********************************************************************************/
uchar8 SF_GetStr_698FreezeDataTableOrder(ulong32 V_Data_Id_OAD)
{
	uchar8 V_DI[4], V_i;

	PF_Ulong32ToBuffer4(&V_DI[0], &V_Data_Id_OAD, 4);

	for(V_i=0;V_i<Str_698FreezeDataTable_Len;V_i++)
	{
		if(V_DI[2]==Str_698FreezeDataTable[V_i].V_DI2)
		{
			break;
		}
	}

	if(V_i<Str_698FreezeDataTable_Len)
	{
		return V_i;
	}
	else
	{
		return 0xFF;
	}
}

/*********************************************************************************
函数原型：uchar8 SF_MinFreezeDefProDistr(uchar8 Vu_MinPro)
功能描述：分钟冻结默认存储地址分配。均分8种方案
输入参数：uchar8 Vu_MinPro：分钟冻结方案数，内部判断合法性1--8之间，不合理则按8种方案分配
输出参数：无
返回参数：C_OK、C_SafeFlagError、C_IICError、C_DataLenError；
功能说明：
调用机制：
备     注：内部判断安全标志
*********************************************************************************/
uchar8 SF_MinFreezeDefProDistr(uchar8 Vu_MinPro)
{
	ushort16 V_ProNum,V_i;
	uchar8 V_Return_Flag=C_Error;
	ulong32 V_StaFlashAddr,V_EndFlashAddr;
	uchar8 Vu_FlashAddr[64];	/*冻结起始、结束地址。每类冻结方案格式为起始地址+结束地址。8种方案同一CRC*/
	uchar8 V_Order;

	memset(&Vu_FlashAddr[0],0xFF,64);

	if((0==Vu_MinPro)||(Vu_MinPro>8))
	{
		Vu_MinPro=8;	/*异常则按8种分配*/
	}

	V_ProNum=MinFreezeFlashTol/Vu_MinPro;	/*方案均分*/
	V_Order=SF_GetStr_698FreezeDataTableOrder(C_RelatedOAD_Min);	/*获取某类冻结数据在Str_698FreezeDataTable中序号*/
	if(V_Order == 0xFF)
	{
		return C_OtherErr_DAR;
	}
	V_StaFlashAddr=Str_698FreezeDataTable[V_Order].V_StaFlashAddr;

	for(V_i=0;V_i<(Vu_MinPro-1);V_i++)	/*剩余空间全部分配最后一种方案*/
	{
		if((V_StaFlashAddr>Str_698FreezeDataTable[V_Order].V_EndFlashAddr)||(V_StaFlashAddr>C_Flash_Max_Addr))	/*异常*/
		{
			return	V_Return_Flag;
		}
		V_EndFlashAddr=V_StaFlashAddr+(V_ProNum-1)*C_OneFlashPage;
		if((V_EndFlashAddr>Str_698FreezeDataTable[V_Order].V_EndFlashAddr)||(V_EndFlashAddr>C_Flash_Max_Addr))	/*异常,正常不存在*/
		{
			return	V_Return_Flag;
		}
		PF_Ulong32ToBuffer4(&Vu_FlashAddr[V_i*8],&V_StaFlashAddr,4);
		PF_Ulong32ToBuffer4(&Vu_FlashAddr[V_i*8+4],&V_EndFlashAddr,4);
		V_StaFlashAddr=V_EndFlashAddr+C_OneFlashPage;
	}
	V_EndFlashAddr=Str_698FreezeDataTable[V_Order].V_EndFlashAddr;	/*最后一种分配方案*/
	PF_Ulong32ToBuffer4(&Vu_FlashAddr[V_i*8],&V_StaFlashAddr,4);
	PF_Ulong32ToBuffer4(&Vu_FlashAddr[V_i*8+4],&V_EndFlashAddr,4);

	V_Return_Flag=SF_WriteE2Three(E2Addr_Min_Free_FlashAddr_Allo,64,&Vu_FlashAddr[0]);	/*写分配地址*/
	return V_Return_Flag;
}

/*********************************************************************************
函数原型：ushort16 SF_GetFreezeSaveDeep(uchar8 V_DI2Temp)
功能描述：获取某类冻结，存储深度
输入参数：uchar8 V_DI2Temp:某类冻结。当为分钟冻结时，高3位表示不同方案号
输出参数：无
返回参数：ushort16 V_Data_Deep：该类冻结深度；
功能说明：
调用机制：
备     注：异常返回0。在获取冻结数据长度函数基础上更改
*********************************************************************************/
ushort16 SF_GetFreezeSaveDeep( uchar8 V_DI2Temp )
{
	ushort16 V_Data_Deep;
	uchar8 P_DataOAD_NumTab[C_698Free_OADTabLen];
	uchar8 P_OADTabLen_T[CLI_Free_OADTabLen_T];
	ushort16 V_Order,V_OADTabLen_T,V_OADOrder16,V_i;
	uchar8 V_Return_Flag,V_DI2;
	Str_3aTable V_Str_3aTable;

	V_Data_Deep=0;
	V_DI2=(V_DI2Temp&0x1F);		/*去除方案号*/
	for(V_i=0;V_i<Str_698FreezeDataTable_Len;V_i++)
	{
		if(V_DI2==Str_698FreezeDataTable[V_i].V_DI2)
		{
			break;
		}
	}

	if(V_i<Str_698FreezeDataTable_Len)
	{
		V_Order=Str_698FreezeDataTable[V_i].V_LineNumLen_T;		/*698冻结长度、周期数据项所在Str_3aTable行号*/
		if(V_Order>=Str_3aTable_E23RAM_Len)
		{
			return V_Data_Deep;		/*异常*/
		}

		V_Str_3aTable=Str_3aTable_E23RAM[V_Order];
		V_Return_Flag=SF_Re_E23_RAM_Data698(&V_Str_3aTable,CLI_Free_OADTabLen_T,&P_OADTabLen_T[0]);
		if(C_OK==V_Return_Flag)
		{
			/*序号表每个OAD序号C_698Free_OADTabDataType个字节,目前6字节。2字节序号+2字节冻结周期+2字节存储深度*/
			V_OADTabLen_T=P_OADTabLen_T[0];
			V_OADTabLen_T=V_OADTabLen_T*C_698Free_OADTabDataType;
			if(V_OADTabLen_T>C_698Free_OADTabLen)		/*数据长度安全性判断*/
			{
				return V_Data_Deep;		/*异常*/
			}

			V_Order=Str_698FreezeDataTable[V_i].V_LineNumTab;	/*698冻结序号表所在Str_3aTable行号*/
			if(V_Order>=Str_3aTable_E23RAM_Len)
			{
				return V_Data_Deep;		/*异常*/
			}

			V_Str_3aTable=Str_3aTable_E23RAM[V_Order];
			V_Return_Flag=SF_Re_E23_RAM_Data698(&V_Str_3aTable,V_OADTabLen_T,&P_DataOAD_NumTab[0]);		/*获取冻结关联列表*/
			if(C_OK!=V_Return_Flag)
			{
				return V_Data_Deep;		/*异常*/
			}

			if(V_DI2==(uchar8)((C_RelatedOAD_Min&0x00FF0000)>>16))		/*分钟冻结*/
			{
				/*获取分钟冻结方案号，对应的OAD关联列表及关联OAD个数*/
				V_OADTabLen_T=SF_GetMinFreezeNum_OADTab((V_DI2Temp>>5),&P_DataOAD_NumTab[0],V_OADTabLen_T);
				if(0xFFFF==V_OADTabLen_T)
				{
					return V_Data_Deep;		/*异常*/
				}
			}
			else
			{
				V_OADTabLen_T=V_OADTabLen_T/C_698Free_OADTabDataType;
			}

			V_Data_Deep=0;
			for(V_i=0;V_i<V_OADTabLen_T;V_i++)
			{
				PF_Buffer2ToUshort16(&P_DataOAD_NumTab[C_698Free_OADTabDataType*V_i+4],&V_OADOrder16);		/*关联列表存储格式：2字节序号+2字节冻结周期+2字节存储深度*/
				if(V_OADOrder16>V_Data_Deep)
				{
					V_Data_Deep=V_OADOrder16;		/*取最大存储空间深度*/
				}
			}
		}
	}
	return V_Data_Deep;
}
/*********************************************************************************
函数原型：uchar8 SF_MinFreezeProDistr(uchar8 *P_Data, ushort16 V_DataLen)
功能描述：根据分钟冻结关联列表，进行存储空间分配
输入参数：
		uchar8 *P_Data：分钟冻结关联列表；
		ushort16 V_DataLen：分钟冻结关联列表长度
输出参数：无
返回参数：C_OK、C_SafeFlagError、C_IICError、C_DataLenError；
功能说明：
调用机制：
备     注：内部判断安全标志，冻结周期一致，则认为是同一方案
*********************************************************************************/
uchar8 SF_MinFreezeProDistr(uchar8 *P_Data, ushort16 V_DataLen)
{
	uchar8 Vu_TolNum,V_Return_Flag=C_Error;
	ulong32 V_StaFlashAddr,V_EndFlashAddr;
	uchar8 Vu_FlashAddr[64]={0xFF};/*冻结起始、结束地址。每类冻结方案格式为起始地址+结束地址。8种方案同一CRC*/
	uchar8 V_Order,V_i,V_DI2;
	ushort16 V_Data_Length,V_Data_Num,V_FlashPage;
	ushort16 V_Cyc16[8]={0xFFFF};
	ushort16 V_Data_Deep;

	if(V_DataLen==0)/*没有关联列表,分配默认空间*/
	{
		V_Return_Flag=SF_MinFreezeDefProDistr(8);
		return V_Return_Flag;
	}

	Vu_TolNum=SF_GetMinFreezeTolNum(&P_Data[0],V_DataLen,&V_Cyc16[0]);/*获取分钟冻结总方案数*/
	if(Vu_TolNum>8)/*最大8种方案*/
	{
		return	V_Return_Flag;
	}

	V_Order=SF_GetStr_698FreezeDataTableOrder(C_RelatedOAD_Min);/*获取某类冻结数据在Str_698FreezeDataTable中序号*/
	if(V_Order == 0xFF)
	{
		return C_OtherErr_DAR;
	}

	V_StaFlashAddr=Str_698FreezeDataTable[V_Order].V_StaFlashAddr;
	V_DI2=(uchar8)((C_RelatedOAD_Min&0x00FF0000)>>16);
	for(V_i=0;V_i<Vu_TolNum;V_i++)
	{
		if((V_StaFlashAddr>Str_698FreezeDataTable[V_Order].V_EndFlashAddr)||(V_StaFlashAddr>C_Flash_Max_Addr))/*异常*/
		{
			V_Return_Flag=SF_MinFreezeDefProDistr(Vu_TolNum);/*异常设置为默认分配空间*/
			return V_Return_Flag;
		}

		V_DI2 &= 0x1F;
		V_DI2 |= (V_i<<5);/*高3位表示不同的方案号*/
		V_Data_Length=SF_JudgeWriteDataLen(V_DI2);/*获取不同方案存储数据长度*/
		if(0==V_Data_Length)/*异常判断*/
		{
			return	V_Return_Flag;
		}

		V_Data_Num=(C_OneFlash_PageNum-C_LoadProfile_RevMode)/V_Data_Length;/*每页可存储条数*/
		V_Data_Deep=SF_GetFreezeSaveDeep(V_DI2);/*获取不同方案存储深度*/
		if(0==V_Data_Deep)
		{
			V_Data_Deep=C_MinFreezeNeedNum;
		}

		V_FlashPage=V_Data_Deep/V_Data_Num+1+2;/*该类冻结需要存储页数，+1整数页，+2巡航用*/
		V_EndFlashAddr=V_StaFlashAddr+(V_FlashPage-1)*C_OneFlashPage;
		if((V_EndFlashAddr>Str_698FreezeDataTable[V_Order].V_EndFlashAddr)||(V_EndFlashAddr>C_Flash_Max_Addr))/*异常*/
		{
			V_Return_Flag=SF_MinFreezeDefProDistr(Vu_TolNum);/*异常设置为默认分配空间*/
			return V_Return_Flag;
		}

		PF_Ulong32ToBuffer4(&Vu_FlashAddr[V_i*8],&V_StaFlashAddr,4);
		PF_Ulong32ToBuffer4(&Vu_FlashAddr[V_i*8+4],&V_EndFlashAddr,4);
		V_StaFlashAddr=V_EndFlashAddr+C_OneFlashPage;
	}

	V_Return_Flag=SF_WriteE2Three(E2Addr_Min_Free_FlashAddr_Allo,64,&Vu_FlashAddr[0]);/*写分配地址*/
	return V_Return_Flag;
}

/*********************************************************************************
函数原型：uchar8 SF_WR_E23_RAM_Data698(Str_3aTable *PStr_3aTable_E23RAM, ushort16 V_DataLen,
										uchar8 *P_Data, uchar8 V_DT_Type, uchar8 V_DI)
功能描述：写E2三处及RAM数据。仅是698OAD序号表的写，计算RAM、E2地址时，根据固定表格长度判断
输入参数：
		Str_3aTable *PStr_3aTable_E23RAM:要操作3a级表结构体元素地址；
		ushort16 V_DataLen：要写入数据长度
		uchar8 *P_Data：要写入数据缓存
输出参数：无
返回参数：C_OK、C_SafeFlagError、C_IICError、C_DataLenError；
功能说明：
调用机制：
备     注：698数据写，内部数据长度不做判断(在查询2级表时，会判断数据长度)。也不进行读比较，因为写入数据长度太长，大于255
*********************************************************************************/
uchar8 SF_WR_E23_RAM_Data698(Str_3aTable *PStr_3aTable_E23RAM, ushort16 V_DataLen, uchar8 *P_Data, uchar8 V_DT_Type, uchar8 V_DI)
{
	ushort16 V_CRC16,V_i,V_Len;
	uchar8 P_CRC[2];
	ushort16 V_E2Addr;
	uchar8 * P_RamAddr=NULL;
	uchar8 V_Return_Flag;

	GV_D_SafeFlag=C_W_SafeFlag_2|GV_D_SafeFlag;		/*置安全标志*/
	V_Len=V_DataLen;
	P_RamAddr=(*PStr_3aTable_E23RAM).V_RamAddr;
	V_E2Addr=(*PStr_3aTable_E23RAM).V_E2BakeUp1Addr;
	V_CRC16=PF_Cal_CRC(&P_Data[0],V_Len);		/*计算CRC*/

	GV_D_SafeFlag=C_W_SafeFlag_3|GV_D_SafeFlag;		/*置安全标志*/
	PF_Ushort16ToBuffer2(&P_CRC[0],&V_CRC16);
	V_Len=V_Len+C_CRCLen2;		/*增加CRC*/

	if(DT_Ref_E23_RAMCRC_DI0==V_DT_Type)		/*地址调整*/
	{
		if(V_DI<1)
		{
			return C_AbnormalError;
		}

		P_RamAddr=P_RamAddr+(V_DI-1)*(C_698Free_OADTabLen+C_CRCLen2);		/*698 OAD序号表固定长度*/
		V_E2Addr=V_E2Addr+(V_DI-1)*(C_698Free_OADTabLen+C_CRCLen2);
	}

	if(C_W_SafeFlag!=GV_D_SafeFlag)
	{
		return C_SafeFlagError;
	}
	else
	{
		for(V_i=0;V_i<V_DataLen;V_i++)		/*RAM 赋值*/
		{
			*(P_RamAddr+V_i)= *(P_Data+V_i);
		}
	}

	P_RamAddr[V_DataLen]=P_CRC[0];
	P_RamAddr[V_DataLen+1]=P_CRC[1];

	V_Return_Flag=SF_WriteE2Three698(V_E2Addr,(V_Len-2),&P_Data[0]);		/*写E2三处数据*/

	if(V_DI==(uchar8)(CMin_Free_OADTab&0x000000FF))		/*判断是否分钟冻结OAD关联列表，#define CMin_Free_OADTab   0x04FE1002       *//*分钟冻结OAD序号表*/
	{	/*进行存储空间分配*/
		V_Return_Flag=SF_MinFreezeProDistr(&P_Data[0],V_DataLen);
	}

	GV_D_SafeFlag=C_Clear_SafeFlag;
	return V_Return_Flag;
}
/*********************************************************************************
函数原型：uchar8 SF_WR_E23_RAM_EnergyData(Str_3aTable *PStr_3aTable_E23RAM, ushort16 V_DataLen,
											uchar8 *P_Data, uchar8 V_DT_Type, uchar8 V_DI)
功能描述：写E2三处及RAM数据.该部分只进行当前电能数据更新处理
输入参数：
		Str_3aTable*PStr_3aTable_E23RAM:要操作3a级表结构体地址；
		ushort16V_3aTable_Line：要操作3a级表格行号；
		ushort16V_DataLen：要写入数据长度
		uchar8*P_Data：要写入数据缓存
		uchar8V_DT_Type：要写入数据类型
		uchar8V_DI:用于计算数据绝对地址
输出参数：无
返回参数：C_OK、C_SafeFlagError、C_IICError、C_DataLenError；
功能说明：
调用机制：
备     注：只进行当前电能处理
*********************************************************************************/
uchar8 SF_WR_E23_RAM_EnergyData(Str_3aTable *PStr_3aTable_E23RAM,ushort16 V_3aTable_Line,ushort16 V_DataLen,uchar8 *P_Data,uchar8 V_DT_Type,uchar8 V_DI)
{
	ushort16 V_CRC16,V_i;
	uchar8 P_CRC[2],V_Len;
	uchar8 PV_Data[C_RAM_Max];
	ushort16 V_E2Addr;
	uchar8 * P_RamAddr=NULL;
	uchar8 V_Return_Flag;
	ulong64 V_RamEnData,V_E2EnData;
	uchar8 V_Return_Flag1=C_Error;
	long64 V_EnDataAdd;

	GV_D_SafeFlag=C_W_SafeFlag_2|GV_D_SafeFlag;	/*置安全标志*/

	if(V_3aTable_Line>=Str_3aTable_E23RAM_Len)	/*正常不存在*/
	{
		return C_AbnormalError;
	}

	if((C_RAM_Max<(V_DataLen+2))||(V_DataLen!=C_CurrDataLen5))	/*本处只有当前电能类数据，5字节*/
	{
		if(_DEBUG)
		{
			/**/
		}
		return C_DataLenError;
	}

	V_Len=(uchar8)V_DataLen;

	P_RamAddr=PStr_3aTable_E23RAM[V_3aTable_Line].V_RamAddr;
	V_E2Addr=PStr_3aTable_E23RAM[V_3aTable_Line].V_E2BakeUp1Addr;
	V_Return_Flag=SF_ReadFRAMThree(V_E2Addr,V_DataLen,PV_Data);
	if(C_OK==V_Return_Flag)
	{
		PF_Buffer8ToUlong64(&PV_Data[0],&V_E2EnData,C_CurrDataLen5);
		PF_Buffer8ToUlong64(&P_Data[0],&V_RamEnData,C_CurrDataLen5);

		V_EnDataAdd=V_RamEnData-V_E2EnData;

		if(0==V_EnDataAdd)	/*增量为0*/
		{
			return	C_OK;
		}
		else	/*电能增量合理性判断*/
		{
			switch(V_E2Addr)
			{
				case	E2Addr_SC_Com_Ac_Tol_En_Pul_0:	/*当前结算周期内用电量，可能会写数据为0.结算后，本处只判断增量的合理性*/
				case	E2Addr_M_Com_Ac_Tol_En_Pul_0:
				case	E2Addr_Y_Com_Ac_Tol_En_Pul_0:
				{
					if(V_EnDataAdd<C_RAMRefE2En_MaxPluse)
					{
						V_Return_Flag1=C_OK;
					}
				}break;

				case	E2Addr_ChargeBal_Hex_Deal:	/*当前剩余金额，写入数据小于原来存储数据*/
				{
					if(V_DI==(uchar8)(CChargeBal_Hex_Full&0x000000FF))	/*充值时，当前剩余金额，不判断数据的合理性*/
					{
						V_Return_Flag1=C_OK;
					}
					else	/*正常扣减判断数据的合理性*/
					{
						if(V_EnDataAdd<0)
						{
							V_Return_Flag1=C_OK;
						}
					}
				}break;

				case	E2Addr_OverDraft_Hex_Deal:	/*当前透支金额，写入数据大于原来存储数据*/
				{
					if(V_DI==(uchar8)(COverDraft_Hex_Full&0x000000FF))	/*充值时，当前透支金额，不判断数据的合理性*/
					{
						V_Return_Flag1=C_OK;
					}
					else	/*正常扣减判断数据的合理性*/
					{
						if(V_EnDataAdd>0)
						{
							V_Return_Flag1=C_OK;
						}
					}
				}break;

				default:	/*其他电能数据，大于零，同时小于增量*/
				{
					if((V_EnDataAdd>0)&&(V_EnDataAdd<C_RAMRefE2En_MaxPluse))
					{
						V_Return_Flag1=C_OK;
					}
				}break;
			}

			GV_D_SafeFlag=C_W_SafeFlag_3|GV_D_SafeFlag;	/*置安全标志*/

			if(C_OK==V_Return_Flag1)	/*写入电能合理，更新铁电数据*/
			{
				PF_CopyDataBytes(P_Data,&PV_Data[0],V_Len);
				V_Return_Flag=SF_WriteFRAMThree(V_E2Addr,V_Len,&PV_Data[0]);

				if(C_OK==V_Return_Flag)	/*更新RAM数据*/
				{
					V_CRC16=PF_Cal_CRC(&PV_Data[0],V_Len);
					PF_Ushort16ToBuffer2(&P_CRC[0],&V_CRC16);

					PV_Data[V_Len]=P_CRC[0];
					PV_Data[V_Len+1]=P_CRC[1];
					V_Len=V_Len+C_CRCLen2;

					if(C_W_SafeFlag!=GV_D_SafeFlag)
					{
						return C_SafeFlagError;
					}
					else
					{
						for(V_i=0;V_i<V_Len;V_i++)	/*RAM赋值*/
						{
							*(P_RamAddr+V_i) = *(PV_Data+V_i);
						}
					}
				}
			}
		}
	}
	return V_Return_Flag;
}
/*********************************************************************************
函数原型：uchar8 SF_WR_E23_RAM_Data(Str_3aTable *PStr_3aTable_E23RAM, ushort16 V_DataLen, uchar8 *P_Data,
									uchar8 V_DT_Type, uchar8V_DI)
功能描述：写E2三处及RAM数据
输入参数：
		Str_3aTable *PStr_3aTable_E23RAM:要操作3a级表结构体地址；
		ushort16 V_3aTable_Line：要操作3a级表格行号；
		ushort16 V_DataLen：要写入数据长度
		uchar8 *P_Data：要写入数据缓存
		uchar8 V_DT_Type：要写入数据类型
		uchar8 V_DI:用于计算数据绝对地址
输出参数：无
返回参数：C_OK、C_SafeFlagError、C_IICError、C_DataLenError；
功能说明：
调用机制：
备     注：
*********************************************************************************/
uchar8 SF_WR_E23_RAM_Data(Str_3aTable * PStr_3aTable_E23RAM,ushort16 V_3aTable_Line,ushort16 V_DataLen,uchar8 *P_Data,uchar8 V_DT_Type,uchar8 V_DI)
{
	ushort16 V_CRC16,V_i;
	uchar8 P_CRC[C_CRCLen2],V_Len;
	uchar8 PV_Data[C_RAM_Max];
	ushort16 V_E2Addr;
	uchar8 * P_RamAddr=NULL;
	uchar8 V_Return_Flag;
	uchar8 V_j;

	GV_D_SafeFlag=C_W_SafeFlag_2|GV_D_SafeFlag;		/*置安全标志*/

	if(V_3aTable_Line>=Str_3aTable_E23RAM_Len)		/*正常不存在*/
	{
		return C_AbnormalError;
	}

	if((C_RAM_Max<(V_DataLen+C_CRCLen2))||(V_DataLen>255))
	{
		if(_DEBUG)
		{
			/**/
		}
		return C_DataLenError;
	}

	V_Len=(uchar8)V_DataLen;
	P_RamAddr=PStr_3aTable_E23RAM[V_3aTable_Line].V_RamAddr;
	V_E2Addr=PStr_3aTable_E23RAM[V_3aTable_Line].V_E2BakeUp1Addr;

	if(DT_W_Ref_E23_RAMCRC_Te==V_DT_Type)		/*费率电价写单独处理*/
	{
		V_Len=(uchar8)V_DataLen;
		V_Len=V_Len/C_MaxRatesNum;		/*按照最大的电能个数分开存储，数据截取*/

		for(V_j=0;V_j<C_MaxRatesNum;V_j++)
		{
			P_RamAddr=PStr_3aTable_E23RAM[V_3aTable_Line].V_RamAddr;
			V_E2Addr=PStr_3aTable_E23RAM[V_3aTable_Line].V_E2BakeUp1Addr;

			PF_CopyDataBytes(&P_Data[V_j*V_Len],&PV_Data[0],V_Len);
			V_CRC16=PF_Cal_CRC(&PV_Data[0],V_Len);		/*计算CRC*/
			GV_D_SafeFlag=C_W_SafeFlag_3|GV_D_SafeFlag;		/*置安全标志*/
			PF_Ushort16ToBuffer2(&P_CRC[0],&V_CRC16);
			PV_Data[V_Len]=P_CRC[0];
			PV_Data[V_Len+1]=P_CRC[1];
			V_Len=V_Len+C_CRCLen2;

			P_RamAddr=P_RamAddr+V_j*V_Len;		/*调整E2、RAM地址*/
			V_E2Addr=V_E2Addr+V_j*V_Len;

			if(C_W_SafeFlag!=GV_D_SafeFlag)
			{
				return C_SafeFlagError;
			}
			else
			{
				for(V_i=0;V_i<V_Len;V_i++)		/*RAM 赋值*/
				{
					*(P_RamAddr+V_i)= *(PV_Data+V_i);
				}

				V_Return_Flag=SF_WriteE2Three(V_E2Addr,(V_Len-C_CRCLen2),&PV_Data[0]);		/*写E2数据*/
			}

			V_Len -= C_CRCLen2;
		}

		GV_D_SafeFlag=C_Clear_SafeFlag;
		return V_Return_Flag;
	}
	else
	{
		PF_CopyDataBytes(P_Data,&PV_Data[0],V_Len);
		V_CRC16=PF_Cal_CRC(&PV_Data[0],V_Len);		/*计算CRC*/
		GV_D_SafeFlag=C_W_SafeFlag_3|GV_D_SafeFlag;		/*置安全标志*/
		PF_Ushort16ToBuffer2(&P_CRC[0],&V_CRC16);

		PV_Data[V_Len] = P_CRC[0];
		PV_Data[V_Len+1] = P_CRC[1];
		V_Len = V_Len + C_CRCLen2;

		if(DT_Ref_E23_RAMCRC_DI0 == V_DT_Type)		/*地址调整*/
		{
			if(V_DI<1)
			{
				return C_AbnormalError;
			}

			P_RamAddr = P_RamAddr+(V_DI-1)*V_Len;
			V_E2Addr = V_E2Addr+(V_DI-1)*V_Len;
		}

		if(DT_Ref_E23_RAMCRC_DI0_2 == V_DT_Type)		/*04FE0202类参数，从DI0=2开始计算*/
		{
			if(V_DI<2)
			{
				return C_AbnormalError;
			}

			P_RamAddr=P_RamAddr+(V_DI-2)*V_Len;
			V_E2Addr=V_E2Addr+(V_DI-2)*V_Len;
		}

		if(C_W_SafeFlag!=GV_D_SafeFlag)
		{
			return C_SafeFlagError;
		}
		else
		{
			for(V_i=0;V_i<V_Len;V_i++)		/*RAM 赋值*/
			{
				*(P_RamAddr+V_i)= *(PV_Data+V_i);
			}
		}

		if((DT_Ref_E23_RAMCRC==V_DT_Type)
			||(DT_Ref_E23_RAMCRC_DI0==V_DT_Type)
			||(DT_Ref_E23_RAMCRC_DI0_2==V_DT_Type))		/*更新E2备份数据*/
		{
			V_Return_Flag=SF_WriteE2Three(V_E2Addr,(V_Len-C_CRCLen2),&PV_Data[0]);
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return V_Return_Flag;
		}
		else
		{
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return C_OK;
		}
	}
}
/*********************************************************************************
函数原型：uchar8 SF_WR_E23_Data(ushort16 V_E2Addr, ushort16 V_DataLen, uchar8 *P_Data)
功能描述：写E2三处数据
输入参数：
		ushort16V_E2Addr：写入数据E2地址；
		ushort16V_DataLen：要写入数据长度
		uchar8*P_Data：要写入数据缓存
输出参数：无
返回参数：C_OK、C_SafeFlagError、C_IICError；
功能说明：
调用机制：
备     注：
*********************************************************************************/
uchar8 SF_WR_E23_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data)
{
	uchar8 V_Return_Flag;

	GV_D_SafeFlag=C_W_SafeFlag_2|GV_D_SafeFlag;		/*置安全标志*/
	GV_D_SafeFlag=C_W_SafeFlag_3|GV_D_SafeFlag;		/*置安全标志*/

	V_Return_Flag=SF_WriteE2Three(V_E2Addr,(uchar8)V_DataLen,P_Data);
	GV_D_SafeFlag=C_Clear_SafeFlag;

	return V_Return_Flag;
}
/*********************************************************************************
函数原型：uchar8 SF_WriteFRAMThree(ushort16 V_E2Addr, uchar8 V_DataLen, uchar8 *P_Data)
功能描述：写铁电三处数据，直接操作铁电,内部计算CRC
输入参数：
		ushort16 V_E2Addr：写入数据铁电地址；
		uchar8 V_DataLen：要写入数据长度,不包括CRC长度
		uchar8 *P_Data：要写入数据缓存
输出参数：无
返回参数：C_OK、C_SafeFlagError、C_IICError；
功能说明：
调用机制：
备     注：内部判断安全标志，外部调用前要满足安全标志，否则写不成功
*********************************************************************************/
uchar8 SF_WriteFRAMThree(ushort16 V_E2Addr,uchar8 V_DataLen,uchar8 *P_Data)
{
	uchar8 V_i;
	uchar8 PV_Data[C_RAM_Max];
	uchar8 PV_RData[C_RAM_Max];  /*用于读比较*/
	uchar8 V_Len,P_CRC[C_CRCLen2];
	ushort16 V_CRC16;

	if(C_RAM_Max<(V_DataLen+C_CRCLen2))
	{
		if(_DEBUG)
		{
			/**/
		}
		return C_DataLenError;
	}

	PF_CopyDataBytes(P_Data,&PV_Data[0],V_DataLen);
	V_CRC16=PF_Cal_CRC(&PV_Data[0],V_DataLen);		/*计算CRC*/
	PF_Ushort16ToBuffer2(&P_CRC[0],&V_CRC16);
	PV_Data[V_DataLen]=P_CRC[0];
	PV_Data[V_DataLen+1]=P_CRC[1];
	V_Len=V_DataLen+C_CRCLen2;

	if(C_W_SafeFlag!=GV_D_SafeFlag)
	{
		return C_SafeFlagError;
	}
	else
	{
		InF_FRAMWPEnable();		/*开启E2 WP*/

		if(C_W_SafeFlag!=GV_D_SafeFlag)		/*安全标志错*/
		{
			InF_FRAMWPDisable();		/*关闭WP*/
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return C_SafeFlagError;
		}

		InF_WriteFRAM(V_E2Addr,&PV_Data[0],(ushort16)V_Len);
		InF_ReadFRAM(V_E2Addr,&PV_RData[0],(ushort16)V_Len);

		for(V_i=0;V_i<V_Len;V_i++)		/*读比较*/
		{
			if(*(PV_Data+V_i)!=*(PV_RData+V_i))
			{
				break;
			}
		}

		if(V_i!=V_Len)		/*写E2错误*/
		{
			return C_IICError;
		}

		InF_FRAMWPEnable();		/*写E2备份2*/

		if(C_W_SafeFlag!=GV_D_SafeFlag)		/*安全标志错*/
		{
			InF_FRAMWPDisable();		/*关闭WP*/
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return C_SafeFlagError;
		}

		InF_WriteFRAM(V_E2Addr+FRAM_BackUp2_Space,&PV_Data[0],(ushort16)V_Len);
		InF_ReadFRAM(V_E2Addr+FRAM_BackUp2_Space,&PV_RData[0],(ushort16)V_Len);

		for(V_i=0;V_i<V_Len;V_i++)		/*读比较*/
		{
			if(*(PV_Data+V_i)!=*(PV_RData+V_i))
			{
				break;
			}
		}

		if(V_i!=V_Len)		/*写E2错误*/
		{
			return C_IICError;
		}

		InF_FRAMWPEnable();		/*写E2备份3*/

		if(C_W_SafeFlag!=GV_D_SafeFlag)		/*安全标志错*/
		{
			InF_FRAMWPDisable();		/*关闭WP*/
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return C_SafeFlagError;
		}

		InF_WriteFRAM(V_E2Addr+FRAM_BackUp3_Space,&PV_Data[0],(ushort16)V_Len);
		InF_ReadFRAM(V_E2Addr+FRAM_BackUp3_Space,&PV_RData[0],(ushort16)V_Len);

		for(V_i=0;V_i<V_Len;V_i++)		/*读比较*/
		{
			if(*(PV_Data+V_i)!=*(PV_RData+V_i))
			{
				break;
			}
		}

		if(V_i!=V_Len)		/*写E2错误*/
		{
			return C_IICError;
		}
	}

	return C_OK;
}

/*********************************************************************************
函数原型：uchar8 SF_WriteE2Three(ushort16 V_E2Addr,uchar8 V_DataLen,uchar8 *P_Data)
功能描述：写E2三处数据，直接操作E2,内部计算CRC
输入参数：
		ushort16 V_E2Addr：写入数据E2地址；
		uchar8 V_DataLen：要写入数据长度,不包括CRC长度
		uchar8 *P_Data：要写入数据缓存
输出参数：无
返回参数：C_OK、C_SafeFlagError、C_IICError；
功能说明：
调用机制：
备     注：内部判断安全标志，外部调用前要满足安全标志，否则写不成功
*********************************************************************************/
uchar8 SF_WriteE2Three(ushort16 V_E2Addr,uchar8 V_DataLen,uchar8 *P_Data)
{
	uchar8 V_i;
	uchar8 PV_Data[C_RAM_Max];
	uchar8 PV_RData[C_RAM_Max];		/*用于读比较*/
	uchar8 V_Len,P_CRC[C_CRCLen2];
	ushort16 V_CRC16;

	if(C_RAM_Max<(V_DataLen+C_CRCLen2))
	{
		if(_DEBUG)
		{
			/**/
		}
		return C_DataLenError;
	}

	PF_CopyDataBytes(P_Data,&PV_Data[0],V_DataLen);
	V_CRC16=PF_Cal_CRC(&PV_Data[0],V_DataLen);		/*计算CRC*/
	PF_Ushort16ToBuffer2(&P_CRC[0],&V_CRC16);
	PV_Data[V_DataLen]=P_CRC[0];
	PV_Data[V_DataLen+1]=P_CRC[1];
	V_Len=V_DataLen+C_CRCLen2;

	if(C_W_SafeFlag!=GV_D_SafeFlag)
	{
		return C_SafeFlagError;
	}
	else
	{
		InF_E2WPEnable();		/*开启E2 WP*/

		if(C_W_SafeFlag!=GV_D_SafeFlag)		/*安全标志错*/
		{
			InF_E2WPDisable();		/*关闭WP*/
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return C_SafeFlagError;
		}

		InF_WriteE2(V_E2Addr,&PV_Data[0],(ushort16)V_Len);
		InF_ReadE2(V_E2Addr,&PV_RData[0],(ushort16)V_Len);

		for(V_i=0;V_i<V_Len;V_i++)		/*读比较*/
		{
			if(*(PV_Data+V_i)!=*(PV_RData+V_i))
			{
				break;
			}
		}

		if(V_i!=V_Len)		/*写E2错误*/
		{
			return C_IICError;
		}

		InF_E2WPEnable();		/*写E2备份2*/

		if(C_W_SafeFlag!=GV_D_SafeFlag)		/*安全标志错*/
		{
			InF_E2WPDisable();		/*关闭WP*/
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return C_SafeFlagError;
		}

		InF_WriteE2(V_E2Addr+E2_BackUp2_Space,&PV_Data[0],(ushort16)V_Len);
		InF_ReadE2(V_E2Addr+E2_BackUp2_Space,&PV_RData[0],(ushort16)V_Len);

		for(V_i=0;V_i<V_Len;V_i++)		/*读比较*/
		{
			if(*(PV_Data+V_i)!=*(PV_RData+V_i))
			{
				break;
			}
		}

		if(V_i!=V_Len)		/*写E2错误*/
		{
			return C_IICError;
		}

		InF_E2WPEnable();		/*写E2备份3*/

		if(C_W_SafeFlag!=GV_D_SafeFlag)		/*安全标志错*/
		{
			InF_E2WPDisable();		/*关闭WP*/
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return C_SafeFlagError;
		}

		InF_WriteE2(V_E2Addr+E2_BackUp3_Space,&PV_Data[0],(ushort16)V_Len);
		InF_ReadE2(V_E2Addr+E2_BackUp3_Space,&PV_RData[0],(ushort16)V_Len);

		for(V_i=0;V_i<V_Len;V_i++)		/*读比较*/
		{
			if(*(PV_Data+V_i)!=*(PV_RData+V_i))
			{
				break;
			}
		}

		if(V_i!=V_Len)		/*写E2错误*/
		{
			return C_IICError;
		}
	}

	return C_OK;
}

/*********************************************************************************
函数原型：uchar8 SF_WriteE2Three698(ushort16 V_E2Addr, ushort16 V_DataLen, uchar8 *P_Data)
功能描述：写E2三处数据，直接操作E2,内部计算CRC
输入参数：
		ushort16 V_E2Addr：写入数据E2地址；
		uchar8 V_DataLen：要写入数据长度,不包括CRC长度
		uchar8 *P_Data：要写入数据缓存
输出参数：无
返回参数：C_OK、C_SafeFlagError、C_IICError；
功能说明：
调用机制：
备     注：内部判断安全标志，外部调用前要满足安全标志，否则写不成功.写入数据长度大于255，不进行写入读出判断
*********************************************************************************/
uchar8 SF_WriteE2Three698(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data)
{
	uchar8 V_Return_Flag;
	uchar8 P_CRC[C_CRCLen2];
	ushort16 V_CRC16,V_Len;

	V_CRC16=PF_Cal_CRC(&P_Data[0],V_DataLen);		/*计算CRC*/
	PF_Ushort16ToBuffer2(&P_CRC[0],&V_CRC16);

	V_Len=V_DataLen;

	if(C_W_SafeFlag!=GV_D_SafeFlag)
	{
		return C_SafeFlagError;
	}
	else
	{
		InF_E2WPEnable();		/*开启E2 WP*/

		if(C_W_SafeFlag!=GV_D_SafeFlag)		/*安全标志错*/
		{
			InF_E2WPDisable();		/*关闭WP*/
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return C_SafeFlagError;
		}

		V_Return_Flag=InF_WriteE2(V_E2Addr,&P_Data[0],V_Len);

		InF_E2WPEnable();
		V_Return_Flag=InF_WriteE2((V_E2Addr+V_Len),&P_CRC[0],C_CRCLen2);		/*CRC单独写*/

		InF_E2WPEnable();		/*写E2备份2*/

		if(C_W_SafeFlag!=GV_D_SafeFlag)		/*安全标志错*/
		{
			InF_E2WPDisable();		/*关闭WP*/
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return C_SafeFlagError;
		}

		V_Return_Flag=InF_WriteE2(V_E2Addr+E2_BackUp2_Space,&P_Data[0],V_Len);

		InF_E2WPEnable();
		V_Return_Flag=InF_WriteE2(V_E2Addr+E2_BackUp2_Space+V_Len,&P_CRC[0],C_CRCLen2);

		InF_E2WPEnable();		/*写E2备份3*/

		if(C_W_SafeFlag!=GV_D_SafeFlag)		/*安全标志错*/
		{
			InF_E2WPDisable();		/*关闭WP*/
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return C_SafeFlagError;
		}

		V_Return_Flag=InF_WriteE2(V_E2Addr+E2_BackUp3_Space,&P_Data[0],V_Len);

		InF_E2WPEnable();
		V_Return_Flag=InF_WriteE2(V_E2Addr+E2_BackUp3_Space+V_Len,&P_CRC[0],C_CRCLen2);

		return V_Return_Flag;
	}
}

/*********************************************************************************
函数原型：uchar8 SF_WriteFlash_Data(uchar8 *P_Data,ushort16 V_Data_Length,Str_3cTable *PStr_3cTable,
									ulong32 V_Data_Id, ushort16 V_3cTable_Line, uchar8 V_Type)
功能描述：写Flash数据,只有上1次，才允许写，否则返回无权限,通过DI0低4位判断
输入参数：
		uchar8 *P_Data:写数据缓存；
		uchar8 V_Data_Length：写数据具体长度；
		Str_3cTable *PStr_3cTable：对应3级表格首地址；
		ulong32 V_Data_Id：DI0-DI3数据标识；
		ushort16 V_3cTable_Line：要操作3c级表格行号；
		uchar8 V_Type:数据存储类型
输出参数：无
返回参数：C_OK、C_SafeFlagError、C_SPIError,C_IICError，C_NoAccess，C_DataLenError；
功能说明：
调用机制：
备     注：写Flash数据，内部没有跨页操作.记录发生次数3字节，目前只用校表记录
*********************************************************************************/
uchar8 SF_WriteFlash_Data(uchar8 *P_Data,ushort16 V_Data_Length,Str_3cTable *PStr_3cTable,ulong32 V_Data_Id,ushort16 V_3cTable_Line,uchar8 V_Type)
{
	uchar8 P_Dgree[CLAll_Loss_Vol_Degree];
	ushort16 V_E2Addr,V_OffAddr;
	ulong32 V_Dgree;
	Str_4Table *PStr_4TableAddr=NULL;
	ulong32 P_FlashAddr1[2];
//	ulong32 P_FlashAddr2[2];
	uchar8 V_Return_Flag;
	uchar8 V_ucDataLen_RW;		/*山东双协议，增加区分时区时段编程记录，次数为4字节*/

	if(V_3cTable_Line>=Str_3cTable_Flash_Len)
	{
		return C_AbnormalError;		/*正常不存在*/
	}

	V_Dgree=(V_Data_Id&0x0000000F);		/*取DI低4位*/
	if(0x00000001!=V_Dgree)		/*根据写数据层要求，只有上1次，才允许写*/
	{
		return C_NoAccess;
	}

	V_OffAddr=0xFFFF;		/*先赋值错误*/

	V_E2Addr=PStr_3cTable[V_3cTable_Line].V_Num_E2BakeUp1Addr;		/*取Flash记录次数E2地址*/

	V_ucDataLen_RW = 4;
	V_Return_Flag=SF_ReadE2Three(V_E2Addr,V_ucDataLen_RW,&P_Dgree[0]);

#if 0
	/*山东双协议，增加时区时段编程记录，次数为4字节,实际协议645是3字节，698是4字节，存储均为4字节*/
	if(((V_Data_Id & 0xFFFFFF00) == CProgPT_Degree)		/*时段表0x033005C1、0x033005D1、0x033005E1、0x033005F1*/
		|| ((V_Data_Id & 0xFFFFFF00) == CProgTZ_CurrentPart_Degree))		/*时区表0x0330F601*/
	{
		V_ucDataLen_RW = 4;
		V_Return_Flag=SF_ReadE2Three(V_E2Addr,V_ucDataLen_RW,&P_Dgree[0]);
	}
	else
	{
		V_ucDataLen_RW = 3;
		V_Return_Flag=SF_ReadE2Three(V_E2Addr,V_ucDataLen_RW,&P_Dgree[0]);
		P_Dgree[3]=0;
	}
#endif

	if((C_OK!=V_Return_Flag)&&(C_CrcErr_DataZero!=V_Return_Flag))
	{
		return V_Return_Flag;
	}

	PF_Buffer4ToUlong32(&P_Dgree[0],&V_Dgree,4);
	GV_D_SafeFlag=C_W_SafeFlag_2|GV_D_SafeFlag;		/*置安全标志*/

	PStr_4TableAddr=(Str_4Table *)(PStr_3cTable[V_3cTable_Line].PStr_4TableAddr);		/*取4级表地址*/
	if(0xFFFFFFFF==((ulong32)PStr_4TableAddr))		/*次数+1判断,4级表不分级*/
	{
		V_Dgree=V_Dgree+1;
	}
	else
	{
		V_OffAddr=SF_GetOffAddr(PStr_4TableAddr,V_Data_Id,V_Type,PStr_3cTable[V_3cTable_Line].V_Str_4TableLen);		/*取偏移地址*/
		if(0==V_OffAddr)		/*偏移地址为0,本次记录首次写入，次数调整*/
		{
			V_Dgree=V_Dgree+1;
		}
		else
		{
			if(0xFFFF==V_OffAddr)		/*查找出错*/
			{
				if(_DEBUG)
				{
					/**/
				}
				return C_AbnormalError;		/*正常理论情况下，不会出现*/
			}
		}
	}

	GV_D_SafeFlag=C_W_SafeFlag_3|GV_D_SafeFlag;		/*置安全标志*/
#if 0
	if(DT_Flash_Tol_DI0_W_Sett_En==V_Type)		/*14：Flash，带次数数据，整个DI0表示次数。结算模块写数据时一起写数据层，数据层内部，结算电量及结算日时间分开存储*/
	{	/*结算电量*/
		SF_GetFlashAddr(V_Dgree,PStr_3cTable[V_3cTable_Line].V_StaFlashAddr,SettEn_Data_Len,PStr_3cTable[V_3cTable_Line].V_EndFlashAddr,&P_FlashAddr1[0]);
		SF_GetFlashAddr(V_Dgree,FlashStAddr_SettTime,SettTime_Data_Len,FlashEndAddr_SettTime,&P_FlashAddr2[0]);		/*结算日结算时间*/
	}
	else
	{
#endif
		SF_GetFlashAddr(V_Dgree,PStr_3cTable[V_3cTable_Line].V_StaFlashAddr,PStr_3cTable[V_3cTable_Line].V_DataToalLen,PStr_3cTable[V_3cTable_Line].V_EndFlashAddr,&P_FlashAddr1[0]);
		PStr_4TableAddr=(Str_4Table *)(PStr_3cTable[V_3cTable_Line].PStr_4TableAddr);		/*取4级表地址*/
		if(0xFFFFFFFF!=((ulong32)PStr_4TableAddr))
		{
			V_OffAddr=SF_GetOffAddr(PStr_4TableAddr,V_Data_Id,V_Type,PStr_3cTable[V_3cTable_Line].V_Str_4TableLen);		/*取偏移地址*/
			if(0xFFFF==V_OffAddr)		/*查找出错*/
			{
				if(_DEBUG)
				{
					/**/
				}
				return C_AbnormalError;		/*正常理论情况下，不会出现*/
			}
			P_FlashAddr1[1]=P_FlashAddr1[1]+(ulong32)V_OffAddr;		/*页内地址*/
		}
#if 0
	}
#endif
	P_FlashAddr1[0]=P_FlashAddr1[0]+P_FlashAddr1[1];		/*写入数据绝对地址*/
	if(P_FlashAddr1[0]>C_Flash_Max_Addr)		/*Flash地址错误，理论不存在 */
	{
		return C_AbnormalError;
	}

	if(C_W_SafeFlag!=GV_D_SafeFlag)
	{
		return C_SafeFlagError;
	}
#if 0
	if(DT_Flash_Tol_DI0_W_Sett_En==V_Type)
	{
		V_Return_Flag=SF_WriteFlash(P_FlashAddr1[0],(P_Data+SettTime_Data_Len),SettEn_Data_Len,1);		/*结算电能*/
		if(C_OK!=V_Return_Flag)
		{
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return V_Return_Flag;
		}

		P_FlashAddr2[0]=P_FlashAddr2[0]+P_FlashAddr2[1];		/*结算日结算时间绝对地址*/
		V_Return_Flag=SF_WriteFlash(P_FlashAddr2[0],P_Data,SettTime_Data_Len,1);
	}
	else
	{
		V_Return_Flag=SF_WriteFlash(P_FlashAddr1[0],P_Data,V_Data_Length,1);
	}
#endif

	V_Return_Flag=SF_WriteFlash(P_FlashAddr1[0],P_Data,V_Data_Length,1);

	if(C_OK!=V_Return_Flag)
	{
		GV_D_SafeFlag=C_Clear_SafeFlag;
		return V_Return_Flag;
	}

	PF_Ulong32ToBuffer4(&P_Dgree[0],&V_Dgree,4);
	if(0xFFFFFFFF==((ulong32)PStr_4TableAddr))
	{
		V_Return_Flag=SF_WriteE2Three(V_E2Addr,V_ucDataLen_RW,&P_Dgree[0]);		/*写E2记录次数*/
	}
	else
	{
		if(0==V_OffAddr)
		{
			V_Return_Flag=SF_WriteE2Three(V_E2Addr,V_ucDataLen_RW,&P_Dgree[0]);
		}
	}

	GV_D_SafeFlag=C_Clear_SafeFlag;
	return V_Return_Flag;
}

/*********************************************************************************
函数原型：uchar8 SF_ReadE2Three_698(ushort16 V_E2Addr, ushort16 V_DataLen, uchar8 *P_Data)
功能描述：读E2三处数据,内部判断CRC.698读数据长度为ushort16
输入参数：
		ushort16 V_E2Addr：读数据E2地址；
		ushort16 V_DataLen：读数据长度
		uchar8 *P_Data：读数据缓存(不包括CRC)
输出参数：无
返回参数：C_OK、C_IICError、C_CRCError、C_CrcErr_DataZero；
功能说明：
调用机制：
备     注：读数据不正确，也返回所读数据
*********************************************************************************/
uchar8 SF_ReadE2Three_698(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data)
{
	uchar8 PV_CRC1[C_CRCLen2],PV_CRC2[C_CRCLen2];
	uchar8 V_ReCRC,V_Return_Flag;
	ushort16 V_CRC16;

	V_Return_Flag=InF_ReadE2(V_E2Addr,&P_Data[0],V_DataLen);     /*读E2第1处*/
	V_Return_Flag=InF_ReadE2((V_E2Addr+V_DataLen),&PV_CRC1[0],C_CRCLen2);     /*读E2第1处CRC*/

	V_CRC16=PF_Cal_CRC(&P_Data[0],V_DataLen);
	PF_Ushort16ToBuffer2(&PV_CRC2[0],&V_CRC16);
	V_ReCRC=C_OK;

	if((PV_CRC1[0]!=PV_CRC2[0])||(PV_CRC1[1]!=PV_CRC2[1]))
	{
		V_ReCRC=C_CRCError;
	}

	if(C_CRCError==V_ReCRC)
	{
		V_Return_Flag=InF_ReadE2(V_E2Addr+E2_BackUp2_Space,&P_Data[0],V_DataLen);     /*读E2第1处*/
		V_Return_Flag=InF_ReadE2((V_E2Addr+V_DataLen+E2_BackUp2_Space),&PV_CRC1[0],C_CRCLen2);     /*读E2第1处CRC*/

		V_CRC16=PF_Cal_CRC(&P_Data[0],V_DataLen);
		PF_Ushort16ToBuffer2(&PV_CRC2[0],&V_CRC16);

		if((PV_CRC1[0]!=PV_CRC2[0])||(PV_CRC1[1]!=PV_CRC2[1]))
		{
			V_ReCRC=C_CRCError;
		}

		if(C_CRCError==V_ReCRC)
		{
			V_Return_Flag=InF_ReadE2(V_E2Addr+E2_BackUp3_Space,&P_Data[0],V_DataLen);     /*读E2第1处*/
			V_Return_Flag=InF_ReadE2((V_E2Addr+V_DataLen+E2_BackUp3_Space),&PV_CRC1[0],C_CRCLen2);     /*读E2第1处CRC*/

			V_CRC16=PF_Cal_CRC(&P_Data[0],V_DataLen);
			PF_Ushort16ToBuffer2(&PV_CRC2[0],&V_CRC16);

			if((PV_CRC1[0]!=PV_CRC2[0])||(PV_CRC1[1]!=PV_CRC2[1]))
			{
				V_ReCRC=C_CRCError;
			}
		}
	}

	if(C_OK!=V_Return_Flag)
	{
		return V_Return_Flag;    /*C_IICError*/
	}
	else
	{
		if(C_OK!=V_ReCRC)
		{
			return V_ReCRC;      /*可能返回C_CrcErr_DataZero*/
		}
		else
		{
			return C_OK;
		}
	}
}

/*********************************************************************************
函数原型：uchar8 SF_ReadE2Three_698_AndCRC(ushort16 V_E2Addr, ushort16 V_DataLen, uchar8 *P_Data)
功能描述：读E2三处数据,包括CRC.698读数据长度为ushort16
输入参数：
		ushort16 V_E2Addr：读数据E2地址；
		ushort16 V_DataLen：读数据长度（不包含CRC长度）
		uchar8 *P_Data：读数据缓存，包括CRC
输出参数：无
返回参数：C_OK、C_IICError、C_CRCError、C_CrcErr_DataZero；
功能说明：
调用机制：
备     注：读数据不正确，也返回所读数据。注意该函数与SF_ReadE2Three_698区别
SF_ReadE2Three_698:返回数据不包含CRC，SF_ReadE2Three_698_AndCRC：返回数据包含CRC；
*********************************************************************************/
uchar8 SF_ReadE2Three_698_AndCRC(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data)
{
	uchar8 V_ReCRC = C_CRCError,V_Return_Flag = C_OtherErr_DAR;

	V_Return_Flag=InF_ReadE2(V_E2Addr,&P_Data[0],(V_DataLen+C_CRCLen2));     /*读E2第1处，带CRC*/

	V_ReCRC=PF_Check_CRC(&P_Data[0],(V_DataLen+C_CRCLen2));

	if( (C_OK != V_ReCRC) || (C_OK != V_Return_Flag) )
	{
		V_Return_Flag=InF_ReadE2((V_E2Addr+E2_BackUp2_Space),&P_Data[0],(V_DataLen+C_CRCLen2));     /*读E2第2处*/

		V_ReCRC=PF_Check_CRC(&P_Data[0],(V_DataLen+C_CRCLen2));

		if( (C_OK != V_ReCRC) || (C_OK != V_Return_Flag) )
		{
			V_Return_Flag=InF_ReadE2((V_E2Addr+E2_BackUp3_Space),&P_Data[0],(V_DataLen+C_CRCLen2));     /*读E2第3处*/
			V_ReCRC=PF_Check_CRC(&P_Data[0],(V_DataLen+C_CRCLen2));
		}
		else
		{
			;
		}
	}
	else
	{
		;
	}

	if(C_OK!=V_Return_Flag)
	{
		return V_Return_Flag;    /*C_IICError*/
	}
	else
	{
		if(C_OK!=V_ReCRC)
		{
			return V_ReCRC;
		}
		else
		{
			return C_OK;
		}
	}
}
/*********************************************************************************
函数原型：uchar8 SF_ReadFRAMThree_AndCRC(ushort16 V_E2Addr, uchar8 V_DataLen, uchar8 *P_Data)
功能描述：读铁电三处数据,包括CRC
输入参数：
		ushort16 V_E2Addr：读数据铁电地址；
		uchar8 V_DataLen：读数据长度（不包含CRC长度）
		uchar8 *P_Data：读数据缓存，包括CRC
输出参数：
无
返回参数：C_OK、C_IICError、C_CRCError、C_CrcErr_DataZero；
功能说明：
调用机制：
备     注：读数据不正确，也返回所读数据。注意该函数与SF_ReadFRAMThree区别
SF_ReadFRAMThree:返回数据不包含CRC，SF_ReadFRAMThree_AndCRC：返回数据包含CRC；
*********************************************************************************/
uchar8 SF_ReadFRAMThree_AndCRC(ushort16 V_E2Addr,uchar8 V_DataLen,uchar8 *P_Data)
{
	uchar8 V_ReCRC = C_CRCError,V_Return_Flag = C_OtherErr_DAR;

	V_Return_Flag=InF_ReadFRAM(V_E2Addr,&P_Data[0],(ushort16)(V_DataLen+C_CRCLen2));		/*读铁电第1处*/

	V_ReCRC=PF_Check_CRC(&P_Data[0],(ushort16)(V_DataLen+C_CRCLen2));

	if( (C_OK != V_ReCRC) || (C_OK != V_Return_Flag) )
	{
		V_Return_Flag=InF_ReadFRAM((V_E2Addr+FRAM_BackUp2_Space),&P_Data[0],(ushort16)(V_DataLen+C_CRCLen2));		/*读E2第2处*/
		V_ReCRC=PF_Check_CRC(&P_Data[0],(ushort16)(V_DataLen+C_CRCLen2));

		if( (C_OK != V_ReCRC) || (C_OK != V_Return_Flag) )
		{
			V_Return_Flag=InF_ReadFRAM((V_E2Addr+FRAM_BackUp3_Space),&P_Data[0],(ushort16)(V_DataLen+C_CRCLen2));		/*读E2第3处*/
			V_ReCRC=PF_Check_CRC(&P_Data[0],(ushort16)(V_DataLen+C_CRCLen2));
		}
		else
		{
			;
		}
	}
	else
	{
		;
	}

	if(C_OK!=V_Return_Flag)
	{
		return  V_Return_Flag;		/*C_IICError*/
	}
	else
	{
		if(C_OK!=V_ReCRC)
		{
			return V_ReCRC;
		}
		else
		{
			return C_OK;
		}
	}
}
/*********************************************************************************
函数原型：uchar8 SF_ReadFRAMThree(ushort16 V_E2Addr,uchar8 V_DataLen,uchar8 *P_Data)
功能描述：读铁电三处数据,内部判断CRC
输入参数：
		ushort16V_E2Addr：读数据铁电地址；
		uchar8V_DataLen：读数据长度
		uchar8*P_Data：读数据缓存(不包括CRC)
输出参数：无
返回参数：C_OK、C_IICError、C_CRCError、C_CrcErr_DataZero；
功能说明：
调用机制：
备     注：读数据不正确，也返回所读数据
*********************************************************************************/
uchar8 SF_ReadFRAMThree(ushort16 V_E2Addr,uchar8 V_DataLen,uchar8 *P_Data)
{
	uchar8 PV_Data[C_RAM_Max];
	uchar8 V_ReCRC = C_CRCError,V_Return_Flag = C_OtherErr_DAR;

	if((V_DataLen+C_CRCLen2)<=C_RAM_Max)
	{
		V_Return_Flag=InF_ReadFRAM(V_E2Addr,&PV_Data[0],(ushort16)(V_DataLen+C_CRCLen2));     /*读铁电第1处*/
		V_ReCRC=PF_Check_CRC(&PV_Data[0],(ushort16)(V_DataLen+C_CRCLen2));
		if( (C_OK != V_ReCRC)||(C_OK != V_Return_Flag) )
		{
			V_Return_Flag=InF_ReadFRAM((V_E2Addr+FRAM_BackUp2_Space),&PV_Data[0],(ushort16)(V_DataLen+C_CRCLen2));     /*读铁电第2处*/
			V_ReCRC=PF_Check_CRC(&PV_Data[0],(ushort16)(V_DataLen+C_CRCLen2));

			if( (C_OK != V_ReCRC)||(C_OK != V_Return_Flag) )
			{
				V_Return_Flag=InF_ReadFRAM((V_E2Addr+FRAM_BackUp3_Space),&PV_Data[0],(ushort16)(V_DataLen+C_CRCLen2));     /*读铁电第3处*/
				V_ReCRC=PF_Check_CRC(&PV_Data[0],(ushort16)(V_DataLen+C_CRCLen2));
			}
			else
			{
				;
			}
		}
		else
		{
			;
		}
		PF_CopyDataBytes(&PV_Data[0],P_Data,V_DataLen);
	}
	else
	{
		;
	}

	if(C_OK!=V_Return_Flag)
	{
		return  V_Return_Flag;		/*C_IICError*/
	}
	else
	{
		if(C_OK!=V_ReCRC)
		{
			return V_ReCRC;		/*可能返回C_CrcErr_DataZero*/
		}
		else
		{
			return C_OK;
		}
	}
}
/*********************************************************************************
函数原型：uchar8 SF_ReadE2Three_AndCRC(ushort16 V_E2Addr, uchar8 V_DataLen, uchar8 *P_Data)
功能描述：读E2三处数据,包括CRC
输入参数：
		ushort16V_E2Addr：读数据E2地址；
		uchar8V_DataLen：读数据长度（不包含CRC长度）
		uchar8*P_Data：读数据缓存，包括CRC
输出参数：无
返回参数：C_OK、C_IICError、C_CRCError、C_CrcErr_DataZero；
功能说明：
调用机制：
备     注：读数据不正确，也返回所读数据。注意该函数与SF_ReadE2Three区别
SF_ReadE2Three:返回数据不包含CRC，SF_ReadE2Three_AndCRC：返回数据包含CRC；
*********************************************************************************/
uchar8 SF_ReadE2Three_AndCRC(ushort16 V_E2Addr,uchar8 V_DataLen,uchar8 *P_Data)
{
	uchar8 V_ReCRC = C_CRCError,V_Return_Flag = C_OtherErr_DAR;

	if((V_DataLen+C_CRCLen2)<=C_RAM_Max)
	{
		V_Return_Flag=InF_ReadE2(V_E2Addr,&P_Data[0],(ushort16)(V_DataLen+C_CRCLen2));		/*读E2第1处*/
		V_ReCRC=PF_Check_CRC(&P_Data[0],(ushort16)(V_DataLen+C_CRCLen2));

		if( (C_OK != V_ReCRC)||(C_OK != V_Return_Flag) )
		{
			V_Return_Flag=InF_ReadE2((V_E2Addr+E2_BackUp2_Space),&P_Data[0],(ushort16)(V_DataLen+C_CRCLen2));		/*读E2第2处*/
			V_ReCRC=PF_Check_CRC(&P_Data[0],(ushort16)(V_DataLen+C_CRCLen2));

			if( (C_OK != V_ReCRC)||(C_OK != V_Return_Flag) )
			{
				V_Return_Flag=InF_ReadE2((V_E2Addr+E2_BackUp3_Space),&P_Data[0],(ushort16)(V_DataLen+C_CRCLen2));		/*读E2第3处*/
				V_ReCRC=PF_Check_CRC(&P_Data[0],(ushort16)(V_DataLen+C_CRCLen2));
			}
		}
	}

	if(C_OK!=V_Return_Flag)
	{
		return  V_Return_Flag;		/*C_IICError*/
	}
	else
	{
		if(C_OK!=V_ReCRC)
		{
			return V_ReCRC;
		}
		else
		{
			return C_OK;
		}
	}
}
/*********************************************************************************
函数原型：uchar8 SF_ReadE2Three(ushort16 V_E2Addr,uchar8 V_DataLen,uchar8 *P_Data)
功能描述：读E2三处数据,内部判断CRC
输入参数：
		ushort16 V_E2Addr：读数据E2地址；
		uchar8 V_DataLen：读数据长度
		uchar8 *P_Data：读数据缓存(不包括CRC)
输出参数：无
返回参数：C_OK、C_IICError、C_CRCError、C_CrcErr_DataZero；
功能说明：
调用机制：
备     注：读数据不正确，也返回所读数据
*********************************************************************************/
uchar8 SF_ReadE2Three(ushort16 V_E2Addr,uchar8 V_DataLen,uchar8 *P_Data)
{
	uchar8 PV_Data[C_RAM_Max];
	uchar8 V_ReCRC,V_Return_Flag = C_Error;

	if((V_DataLen+C_CRCLen2)<=C_RAM_Max)
	{
		V_Return_Flag=InF_ReadE2(V_E2Addr,&PV_Data[0],(ushort16)(V_DataLen+C_CRCLen2));		/*读E2第1处*/

		V_ReCRC=PF_Check_CRC(&PV_Data[0],(ushort16)(V_DataLen+C_CRCLen2));

		if(C_CRCError==V_ReCRC)
		{
			V_Return_Flag=InF_ReadE2(V_E2Addr+E2_BackUp2_Space,&PV_Data[0],(ushort16)(V_DataLen+C_CRCLen2));		/*读E2第2处*/

			V_ReCRC=PF_Check_CRC(&PV_Data[0],(ushort16)(V_DataLen+C_CRCLen2));

			if(C_CRCError==V_ReCRC)
			{
				V_Return_Flag=InF_ReadE2(V_E2Addr+E2_BackUp3_Space,&PV_Data[0],(ushort16)(V_DataLen+C_CRCLen2));		/*读E2第3处*/

				V_ReCRC=PF_Check_CRC(&PV_Data[0],(ushort16)(V_DataLen+C_CRCLen2));
			}
		}

		PF_CopyDataBytes(&PV_Data[0],P_Data,V_DataLen);
	}

	if(C_OK!=V_Return_Flag)
	{
		return  V_Return_Flag;		/*C_IICError*/
	}
	else
	{
		if(C_OK!=V_ReCRC)
		{
			return V_ReCRC;		/*可能返回C_CrcErr_DataZero*/
		}
		else
		{
			return C_OK;
		}
	}
}
/*********************************************************************************
函数原型：ushort16 SF_GetOffAddr(Str_4Table *PStr_4TableAddr,ulong32 V_Data_Id,uchar8 V_Type,uchar8 V_4Table_Len)
功能描述：查找4级表取偏移地址
输入参数：
		Str_4Table*PStr_4TableAddr：4级表地址；
		ulong32V_Data_Id：数据标识查4级表用
		uchar8V_Type:数据存储特征
		uchar8V_4Table_Len:4级表结构体数据长度
输出参数：无
返回参数：ushort16：偏移地址，当偏移地址为0xFFFF时，则查找错误输出debug，方便调试用；
功能说明：
调用机制：
备     注：内部根据不同数据存储类型，查4级表
*********************************************************************************/
ushort16 SF_GetOffAddr(Str_4Table *PStr_4TableAddr,ulong32 V_Data_Id,uchar8 V_Type,uchar8 V_4Table_Len)
{
	uchar8 V_i;
	uchar8 V_DI[4];
	ushort16 V_OffLen;

	V_OffLen=0xFFFF;
	PF_Ulong32ToBuffer4(&V_DI[0],&V_Data_Id,4);

	switch(V_Type)
	{
		case DT_Flash_DI04:		/*④Flash，带次数数据，DI0低4位表示次数，高4位表示不同标识码(查询4级表用)*/
		{
			for(V_i=0;V_i<V_4Table_Len;V_i++)
			{
				if((V_DI[0]&0xF0)==(PStr_4TableAddr[V_i].V_DI&0xF0))		/*比较高4位*/
				{
					break;
				}
			}
		}break;

		case DT_Flash_Tol_DI0_DI1:		/*⑨Flash，带次数数据，整个DI0表示次数，DI1表示分项标识码(查询4级表用)*/
		{
			for(V_i=0;V_i<V_4Table_Len;V_i++)
			{
				if(V_DI[1]==PStr_4TableAddr[V_i].V_DI)		/*比较DI1*/
				{
					break;
				}
			}
		}break;
#if 0
		case DT_Flash_Tol_DI0_DI2:				/*11： Flash，带次数数据，整个DI0表示次数，DI2表示分项标识码(查询4级表用，主要是电量、需量，ABC三相数据)*/
		case DT_Flash_Tol_DI0_W_Sett_En:		/*14：Flash，带次数数据，整个DI0表示次数。结算模块写数据时一起写数据层，数据层内部，结算电量及结算日时间分开存储，该标识码只支持写*/
		case DT_R_Flash_Tol_DI0_DI2_En:			/*25： Flash，带次数数据，整个DI0表示次数，DI2表示分项标识码(查询4级表用，电量的ABC三相数据读)，*/
												/*同时数据长度及所读数据，根据是否是6+4(类似显示),或6+2(类似通信)，进行特殊处理*/
		{
			for(V_i=0;V_i<V_4Table_Len;V_i++)
			{
				if(V_DI[2]==PStr_4TableAddr[V_i].V_DI)		/*比较DI2*/
				{
					break;
				}
			}
		}break;
#endif
		case DT_Flash_Tol_DI0_DI1Max:		/*27： Flash，带次数数据，整个DI0表示次数，列表2级表时只列上1次DI1最大值(不采用查找4级表的方式)，在查找数据DI及DI数据存放偏移地址时，*/
											/*OffsetAddr程序采用计算方式处理,目前只有校表记录采用该方式,除发生时刻DI1=0外*/
		{
			if(0x00==V_DI[1])		/*正常不存在*/
			{
				return 0xFFFF;
			}
			else
			{
				V_OffLen=(V_DI[1]-1)*CLRec_Meter_Bef1_Data_254+6;		/*校表数据，计算偏移地址*/
				return  V_OffLen;
			}
		}break;

		default:
			return 0xFFFF;		/*查找错误*/
	}

	if(V_i<V_4Table_Len)
	{
		return PStr_4TableAddr[V_i].V_OffAddr;
	}
	else
	{
		return 0xFFFF;
	}
}

/*********************************************************************************
函数原型：void SF_GetFlashAddr(ulong32 V_NumE2,ulong32 V_StartFlashAddr，ushort16 V_NoteDataLength,
								ulong32 V_EndFlashAddr,ulong32 *P_ReturnFlashAddr)
功能描述：计算当前数据保存页地址及页内地址
输入参数：
		ulong32 V_NumE2：数据存储总次数，hex格式；
		ulong32 V_StartFlashAddr：数据存储物理首地址；
		ushort16 V_NoteDataLength：本条记录块总数据长度(非分项数据长度)；
		ulong32 V_EndFlashAddr：数据存放结束页地址；
输出参数：
		ulong32 *P_ReturnFlashAddr:用于存放返回页地址及页内地址；P_ReturnFlashAddr[0]:页地址；P_ReturnFlashAddr[1]:页内地址；
返回参数：无
功能说明：
调用机制：
备     注：内部判断次数是否为零，正常理论情况下，不能为零
*********************************************************************************/
void SF_GetFlashAddr(ulong32 V_NumE2,ulong32 V_StartFlashAddr,ushort16 V_NoteDataLength,ulong32 V_EndFlashAddr,ulong32 *P_ReturnFlashAddr)
{
	ushort16 V_Page_Agree;
	ulong32 V_Flash_Page;
	uchar8 V_Flash_PageNum;

	P_ReturnFlashAddr[0]=0xFFFFFFFF;
	P_ReturnFlashAddr[1]=0xFFFFFFFF;

	if(0==V_NoteDataLength)
	{
		return;		/*正常不存在*/
	}

	V_Page_Agree=(ushort16)(C_OneFlash_PageNum/V_NoteDataLength);  /*每页可记录数据次数*/
	V_Flash_Page=V_EndFlashAddr-V_StartFlashAddr;                  /*该记录Flash存储页总数-1*/
	V_Flash_PageNum=(uchar8)(V_Flash_Page/C_OneFlashPage)+1;       /*该记录Flash存储页总数,C_OneFlashPage:0x00001000*/
	if(0==V_NumE2)
	{
		return;
	}

	P_ReturnFlashAddr[0]=(((V_NumE2-1)/V_Page_Agree)%V_Flash_PageNum)*C_OneFlashPage+V_StartFlashAddr;
	P_ReturnFlashAddr[1]=((V_NumE2-1)%V_Page_Agree)*V_NoteDataLength;
}
/*********************************************************************************
函数原型：uchar8 SF_WriteFlash(ulong32 V_FlashAddr,uchar8 *P_Data,ushort16 V_Data_Length)
功能描述：写Flash具体操作,当写入地址为每页首地址时，则先判断所写入Flash块是否为空(00)，如不为空，擦除后再写入。当该页为空时，
最后4个字节写为FF(用于该Flash是否为空判断，在Flash驱动底层程序中添加，写数据时，先把要写入数据按位取反，然后写Flash)
输入参数：
		ulong32 V_FlashAddr：写入数据Flash地址；
		uchar8 *P_Data：写入数据缓存；
		ushort16 V_Data_Length：写入数据长度；
		uchar8 V_EvenSign：写Flash数据时，是否需要判断跨页。主要是写事件记录结束数据，不需要判断跨页。2：不需要判断跨页，为空擦除判断；
							1：需要判断跨页，Flash是否为空判断；
输出参数：无；
返回参数：C_OK、C_SPIError
功能说明：
调用机制：
备     注：注意Flash底层数据，为取反后数据，0、1相反.内部判断安全标志
*********************************************************************************/
uchar8 SF_WriteFlash(ulong32 V_FlashAddr,uchar8 *P_Data,ushort16 V_Data_Length,uchar8 V_EvenSign)
{
	uchar8 V_FlashZero[C_Flash_EmptyNum],V_i;
	ulong32 V_Flash_Page;
	ulong32 V_Flash_PageEmptyAddr;
	uchar8 V_j;
	uchar8 V_Return_Flag;

	V_FlashZero[3]=0x55;           /*非零数据*/
	V_Flash_Page=0x55;
	V_j=4;/*检查Flash是否为空4次，如4次不能擦出成功，则退出返回C_SPIError错误*/

	V_Flash_Page=V_FlashAddr%C_OneFlashPage;   /*判断写入数据Flash地址是否为每页首地址*/
	if((0==V_Flash_Page)&&(V_EvenSign!=2))  /*需判断数据是否为空.698写结束事件记录时，组织结束数据，把发生数据全部置零的方式,底层写FF没有影响，事件记录数据一起写数据层(包括发生、结束)。*/
	{																				/*事件记录模块先写发生，后写结束。写发生标志V_EvenSign定义为1，写结束定义为2。所以写结束数据时，不判断数据是否为空，正常先写发生时，已经判断过。*/
		while(V_j--)
		{
			V_Flash_PageEmptyAddr=V_FlashAddr+C_OneFlashPage-C_Flash_EmptyNum;    /*最后4个字节Flash地址*/
			InF_FlashChipSelect();
			InF_ReadFlash(V_Flash_PageEmptyAddr,&V_FlashZero[0],C_Flash_EmptyNum);

			for(V_i=0;V_i<C_Flash_EmptyNum;V_i++)  /*判断Flash页是否为空,读出数据为全0，则为空(注意Flash驱动底层反)*/
			{
				if(C_Flash_Empty68!=V_FlashZero[V_i])
				{
					break;
				}
			}

			if(V_i<C_Flash_EmptyNum)       /*当前页Flash不为空，擦除写68为空标志*/
			{
				V_Return_Flag=SF_EraseFlashAndWriteEmptySign(V_FlashAddr);
				if(C_OK!=V_Return_Flag)
				{
					GV_D_SafeFlag=C_Clear_SafeFlag;
					return V_Return_Flag;
				}
			}
			else/*当前页为空*/
			{
				break;
			}
		}

		if(0==V_j)/*4次Flash擦除都失败,返回失败操作*/
		{
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return C_SPIError;
		}
	}

	InF_FlashChipSelect();

	if(C_W_SafeFlag!=GV_D_SafeFlag)  /*安全标志错*/
	{
		InF_FlashChipDeselect();            /*关闭CS*/
		GV_D_SafeFlag=C_Clear_SafeFlag;
		return C_SafeFlagError;
	}

	InF_WriteFlash(V_FlashAddr,P_Data,V_Data_Length);

	V_FlashAddr=V_FlashAddr&0xFFFFF000;
	V_Flash_PageEmptyAddr=V_FlashAddr+C_OneFlashPage-C_Flash_EmptyNum;    /*最后4个字节Flash地址*/
	InF_FlashChipSelect();
	InF_ReadFlash(V_Flash_PageEmptyAddr,&V_FlashZero[0],C_Flash_EmptyNum);

	for(V_i=0;V_i<C_Flash_EmptyNum;V_i++)  /*判断4个字节是否为不为空标志*/
	{
		if(C_Flash_NoEmpty!=V_FlashZero[V_i])
		{
			break;
		}
	}

	if(V_i<C_Flash_EmptyNum)       /*当前页Flash不为空标志，没有置*/
	{
		for(V_i=0;V_i<C_Flash_EmptyNum;V_i++)
		{
			V_FlashZero[V_i]=C_Flash_NoEmpty;     /*写Flash不为空数据，0xFF*/
		}

		InF_FlashChipSelect();
		if(C_W_SafeFlag!=GV_D_SafeFlag)  /*安全标志错*/
		{
			InF_FlashChipDeselect();            /*关闭CS*/
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return C_SafeFlagError;
		}

		InF_WriteFlash(V_Flash_PageEmptyAddr,&V_FlashZero[0],C_Flash_EmptyNum);
	}

	return C_OK;
}

/*********************************************************************************
函数原型：uchar8 SF_WR_FRAM1CRC_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data)
功能描述：写铁电1处数据,带CRC
输入参数：
		ushort16V_E2Addr：写入数据铁电地址；
		ushort16V_DataLen：要写入数据长度
		uchar8*P_Data：要写入数据缓存
输出参数：无
返回参数：C_OK、C_SafeFlagError、C_IICError；
功能说明：
调用机制：
备     注：
*********************************************************************************/
uchar8 SF_WR_FRAM1CRC_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data)
{
	uchar8 V_i;
	uchar8 PV_Data[C_RAM_Max];
	uchar8 PV_RData[C_RAM_Max];  /*用于读比较*/
	uchar8 V_Return_Flag;
	uchar8 V_Len,P_CRC[C_CRCLen2];
	ushort16 V_CRC16;

	GV_D_SafeFlag=C_W_SafeFlag_2|GV_D_SafeFlag; /*置安全标志*/

	if((C_RAM_Max<(V_DataLen+C_CRCLen2))||(V_DataLen>255))
	{
		if(_DEBUG)
		{
			/**/
		}
		return C_DataLenError;
	}

	V_Len=(uchar8)V_DataLen;
	PF_CopyDataBytes(P_Data,&PV_Data[0],V_Len);
	V_CRC16=PF_Cal_CRC(&PV_Data[0],V_Len);          /*计算CRC*/
	PF_Ushort16ToBuffer2(&P_CRC[0],&V_CRC16);

	GV_D_SafeFlag=C_W_SafeFlag_3|GV_D_SafeFlag; /*置安全标志*/

	PV_Data[V_Len]=P_CRC[0];
	PV_Data[V_Len+1]=P_CRC[1];

	V_Len=(uchar8)V_DataLen+C_CRCLen2;

	if(C_W_SafeFlag!=GV_D_SafeFlag)
	{
		return C_SafeFlagError;
	}

	InF_FRAMWPEnable();

	if(C_W_SafeFlag!=GV_D_SafeFlag)  /*安全标志错*/
	{
		InF_FRAMWPDisable();            /*关闭WP*/
		GV_D_SafeFlag=C_Clear_SafeFlag;
		return C_SafeFlagError;
	}

	V_Return_Flag=InF_WriteFRAM(V_E2Addr,&PV_Data[0],(ushort16)V_Len);

	InF_ReadFRAM(V_E2Addr,&PV_RData[0],(ushort16)V_Len);

	for(V_i=0;V_i<V_Len;V_i++)                      /*读比较*/
	{
		if(*(PV_Data+V_i)!=*(PV_RData+V_i))
		{
			break;
		}
	}

	if(V_i!=V_Len)                                 /*写E2错误*/
	{
		InF_FRAMWPEnable();                                    /*开启E2 WP*/

		if(C_W_SafeFlag!=GV_D_SafeFlag)  /*安全标志错*/
		{
			InF_FRAMWPDisable();            /*关闭WP*/
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return C_SafeFlagError;
		}

		V_Return_Flag=InF_WriteFRAM(V_E2Addr,&PV_Data[0],(ushort16)V_Len);
	}

	return V_Return_Flag;
}

/*********************************************************************************
函数原型：uchar8 SF_WR_E21CRC_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data)
功能描述：写E21处数据,带CRC
输入参数：
		ushort16 V_E2Addr：写入数据E2地址；
		ushort16 V_DataLen：要写入数据长度
		uchar8 *P_Data：要写入数据缓存
输出参数：无
返回参数：C_OK、C_SafeFlagError、C_IICError；
功能说明：
调用机制：
备注：
*********************************************************************************/
uchar8 SF_WR_E21CRC_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data)
{
	uchar8 V_i;
	uchar8 PV_Data[C_RAM_Max];
	uchar8 PV_RData[C_RAM_Max];  /*用于读比较*/
	uchar8 V_Return_Flag;
	uchar8 V_Len,P_CRC[C_CRCLen2];
	ushort16 V_CRC16;

	GV_D_SafeFlag=C_W_SafeFlag_2|GV_D_SafeFlag; /*置安全标志*/

	if((C_RAM_Max<(V_DataLen+C_CRCLen2))||(V_DataLen>255))
	{
		if(_DEBUG)
		{
			/**/
		}
		return C_DataLenError;
	}

	V_Len=(uchar8)V_DataLen;
	PF_CopyDataBytes(P_Data,&PV_Data[0],V_Len);
	V_CRC16=PF_Cal_CRC(&PV_Data[0],V_Len);          /*计算CRC*/
	PF_Ushort16ToBuffer2(&P_CRC[0],&V_CRC16);

	GV_D_SafeFlag=C_W_SafeFlag_3|GV_D_SafeFlag; /*置安全标志*/

	PV_Data[V_Len]=P_CRC[0];
	PV_Data[V_Len+1]=P_CRC[1];

	V_Len=(uchar8)V_DataLen+C_CRCLen2;

	if(C_W_SafeFlag!=GV_D_SafeFlag)
	{
		return C_SafeFlagError;
	}

	InF_E2WPEnable();

	if(C_W_SafeFlag!=GV_D_SafeFlag)  /*安全标志错*/
	{
		InF_E2WPDisable();            /*关闭WP*/
		GV_D_SafeFlag=C_Clear_SafeFlag;
		return C_SafeFlagError;
	}

	V_Return_Flag=InF_WriteE2(V_E2Addr,&PV_Data[0],(ushort16)V_Len);

	InF_ReadE2(V_E2Addr,&PV_RData[0],(ushort16)V_Len);

	for(V_i=0;V_i<V_Len;V_i++)                      /*读比较*/
	{
		if(*(PV_Data+V_i)!=*(PV_RData+V_i))
		{
			break;
		}
	}

	if(V_i!=V_Len)                                 /*写E2错误*/
	{
		InF_E2WPEnable();                                    /*开启E2 WP*/

		if(C_W_SafeFlag!=GV_D_SafeFlag)  /*安全标志错*/
		{
			InF_E2WPDisable();            /*关闭WP*/
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return C_SafeFlagError;
		}

		V_Return_Flag=InF_WriteE2(V_E2Addr,&PV_Data[0],(ushort16)V_Len);
	}

	return V_Return_Flag;
}

/*********************************************************************************
函数原型：uchar8 SF_WR_E21_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data)
功能描述：写E21处数据
输入参数：
		ushort16 V_E2Addr：写入数据E2地址；
		ushort16 V_DataLen：要写入数据长度
		uchar8 *P_Data：要写入数据缓存
输出参数：无
返回参数：C_OK、C_SafeFlagError、C_IICError；
功能说明：
调用机制：
备     注：
*********************************************************************************/
uchar8 SF_WR_E21_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data)
{
	uchar8 V_Return_Flag;

	GV_D_SafeFlag=C_W_SafeFlag_2|GV_D_SafeFlag; /*置安全标志*/
	GV_D_SafeFlag=C_W_SafeFlag_3|GV_D_SafeFlag; /*置安全标志*/

	if(C_W_SafeFlag!=GV_D_SafeFlag)
	{
		return C_SafeFlagError;	                                    /*开启E2 WP*/
	}

	InF_E2WPEnable();

	if(C_W_SafeFlag!=GV_D_SafeFlag)  /*安全标志错*/
	{
		InF_E2WPDisable();            /*关闭WP*/
		GV_D_SafeFlag=C_Clear_SafeFlag;
		return C_SafeFlagError;
	}

	V_Return_Flag=InF_WriteE2(V_E2Addr,P_Data,V_DataLen);

	return V_Return_Flag;
}
/*********************************************************************************
函数原型：uchar8 SF_WR_RAM_Data(uchar8 *P_RamAddr,ushort16 V_DataLen,uchar8 *P_Data,uchar8 V_DT_Type,uchar8 Msg_Num)
功能描述：写RAM数据，不带CRC
输入参数：
		uchar8 *P_RamAddr：写入数据RAM地址；
		ushort16 V_DataLen：要写入数据长度
		uchar8 *P_Data：要写入数据缓存
		uchar8 V_DT_Type：要写入数据类型，用于判断是否写时间，掉时钟写接口函数
输出参数：无
返回参数：C_OK、C_SafeFlagError；
功能说明：
调用机制：
备     注：
*********************************************************************************/
uchar8 SF_WR_RAM_Data(uchar8 *P_RamAddr,ushort16 V_DataLen,uchar8 *P_Data,uchar8 V_DT_Type,uchar8 Msg_Num)
{
	ushort16 V_i;
	uchar8 V_Return_Flag, V_Temp[CLDate_Week_Time] = {0};

	V_Return_Flag=C_OK;

	GV_D_SafeFlag=C_W_SafeFlag_3|GV_D_SafeFlag; /*置安全标志*/

	if(C_W_SafeFlag!=GV_D_SafeFlag)
	{
		return C_SafeFlagError;
	}

	for(V_i=0;V_i<V_DataLen;V_i++)
	{
		*(P_RamAddr+V_i)=*(P_Data+V_i);
	}

	if(DT_RAM_Time_Data==V_DT_Type)
	{
		if(C_Msg_Communication==Msg_Num)  /*只有通信写时间，才刷新硬件RTC*/
		{
			/*将日期时间Data_Time_s转换为YYMMDDWWHHMMSS*/
			PF_Data_Time_s_HEXtoData_Week_Time_BCD(P_Data, &V_Temp[0]);
			V_Return_Flag=InF_WriteRTC(&V_Temp[0],CLDate_Week_Time);
		}
	}

	return V_Return_Flag;
}
/*********************************************************************************
函数原型：uchar8 SF_WR_RAMCRC_Data(uchar8 *P_RamAddr,ushort16 V_DataLen,uchar8 *P_Data)
功能描述：写RAM数据，内部计算CRC
输入参数：
		uchar8*P_RamAddr：待入数据RAM地址；
		ushort16V_DataLen：要写入数据长度，不包括CRC长度
		uchar8*P_Data：写入数据缓存
输出参数：无
返回参数：C_OK、C_SafeFlagError；
功能说明：
调用机制：
备     注：
*********************************************************************************/
uchar8 SF_WR_RAMCRC_Data(uchar8 * P_RamAddr,ushort16 V_DataLen,uchar8 * P_Data)
{
	ushort16 V_i,V_CRC16;
	uchar8 P_CRC[C_CRCLen2];

	V_CRC16=PF_Cal_CRC(P_Data,V_DataLen);          /*计算CRC*/
	GV_D_SafeFlag=C_W_SafeFlag_3|GV_D_SafeFlag;      /*置安全标志*/
	PF_Ushort16ToBuffer2(&P_CRC[0],&V_CRC16);

	if(C_W_SafeFlag!=GV_D_SafeFlag)
	{
		return C_SafeFlagError;
	}

	for(V_i=0;V_i<V_DataLen;V_i++)
	{
		*(P_RamAddr+V_i)=*(P_Data+V_i);
	}

	*(P_RamAddr+V_DataLen)=P_CRC[0];
	*(P_RamAddr+V_DataLen+1)=P_CRC[1];

	return C_OK;
}
/*********************************************************************************
函数原型：uchar8 InF_Read_RecMeterData(uchar8 V_Data_Num,uchar8 *P_Data,uchar8 *P_Data_Length)
功能描述：读数据层校表参数接口函数
输入参数：
		uchar8 V_Data_Num：读校表数据序号，与校表数据存W2地址偏移一一对应，数据层内部判断最大值，序号超返回C_NoAccess
		uchar8 *P_Data：数据所放缓存；
		uchar8 *P_Data_Length：作为输入参数时，该参数值为模块所读数据缓存长度最大值，用于数据层判断，所读数据长度，
		是否溢出，如溢出则返回数据长度错误。当作为输出参数时，数据层返回所读取数据长度。
输出参数：
		uchar8 *P_Data_Length：数据层返回所读取数据长度。
返回参数：C_OK、C_IICError、C_DataLenError、C_NoAccess、C_CRCError、C_CrcErr_DataZero；
功能说明：
调用机制：
备     注：注意数据长度，
*********************************************************************************/
uchar8 InF_Read_RecMeterData(uchar8 V_Data_Num,uchar8 *P_Data,uchar8 *P_Data_Length)
{
	ushort16 V_3TableE2Addr;
	uchar8 V_Return_Flag;

	if(C_MeterICE2ResLen>(*P_Data_Length))               /*读数据长度*/
	{
		return C_DataLenError;
	}
	else
	{
		*P_Data_Length=C_MeterICE2ResLen;
	}

	if(V_Data_Num>=C_MeterICDataNum_T)
	{
		return C_NoAccess;
	}

	V_3TableE2Addr=E2Addr_MeterIC_St+V_Data_Num*(C_MeterICE2ResLen+C_CRCLen2);   /*要操作E2地址*/
	if(V_3TableE2Addr>(E2Addr_MeterIC_End-C_MeterICE2ResLen-C_CRCLen2))         /*E2地址错误*/
	{
		return C_DataLenError;
	}

	V_Return_Flag=SF_ReadE2Three(V_3TableE2Addr,C_MeterICE2ResLen,P_Data);   /*读E2三处*/
	return V_Return_Flag;
}

/*********************************************************************************
函数原型：uchar8 SF_Read_E21CRC_Data698(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data)
功能描述：读E21处数据，
输入参数：
ushort16 V_E2Addr：读数据E2地址；
ushort16 V_DataLen：读数据长度
输出参数：
uchar8 *P_Data：读数据缓存
返回参数：C_OK、C_IICError、C_CRCError、C_CrcErr_DataZero；
功能说明：
调用机制：
备     注：直接借用输入缓存
*********************************************************************************/
uchar8 SF_Read_E21CRC_Data698(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 * P_Data)
{
	uchar8 V_Return_Flag;
	uchar8 V_ReCRC;

	V_Return_Flag=InF_ReadE2(V_E2Addr,&P_Data[0],(V_DataLen+C_CRCLen2));
	V_ReCRC=PF_Check_CRC(&P_Data[0],(V_DataLen+C_CRCLen2));

	if(C_OK!=V_Return_Flag)
	{
		return  V_Return_Flag;    /*C_IICError*/
	}
	else
	{
		if(C_OK!=V_ReCRC)
		{
			return V_ReCRC;      /*可能返回C_CrcErr_DataZero*/
		}
		else
		{
			return C_OK;
		}
	}
}

/*********************************************************************************
函数原型：uchar8 InF_ReadOADTab_Data(ulong32 V_Data_Id,uchar8 *P_Data,ushort16 *P_Data_Length)
功能描述：读数据层OAD序号表(包含冻结、事件记录)，单独处理，因为冻结关联列表数据长度可能大于255。通用读最大数据长度为255
输入参数：
ulong32 V_Data_Id：数据标识码；
uchar8 *P_Data：数据所放缓存；
ushort16 *P_Data_Length：作为输入参数时，读数据缓存大小
输出参数：ushort16 *P_Data_Length：数据层返回所读取数据实际长度。
返回参数：C_OK、C_IICError、C_SPIError、C_DataLenError、C_IDError、C_NoAccess、C_CRCError、C_CrcErr_DataZero；
功能说明：增加读安全模式参数属性3；
调用机制：
备     注：读关联列表时，数据层内部根据该关联列表对应的OAD个数，自己计算读取的关联列表长度（为兼容原来程序，读冻结关联OAD还是采用读固定输入数据长度）
*********************************************************************************/
uchar8 InF_ReadOADTab_Data(ulong32 V_Data_Id,uchar8 *P_Data,ushort16 *P_Data_Length)
{
	uchar8 V_Return_Flag,V_DI[4];
	ulong32 V_DI32;
	Str_3aTable V_Str_3aTable;
	ushort16 V_Data_Length, V_usDataEncode;

	if((*P_Data_Length)==0)/*没有关联列表，也可能会读*/
	{
		return C_OK;
	}

	if((CI_Free_OADTab&0xFFFFFF00)==(V_Data_Id&0xFFFFFF00))/*读冻结序号表*/
	{
		if((*P_Data_Length)>C_698Free_OADTabLen)/*正常不存在*/
		{
			return C_DataLenError;
		}

		V_DI32=V_Data_Id;
		PF_Ulong32ToBuffer4(&V_DI[0],&V_DI32,4);

		if(V_DI[0]==0)
		{
			return C_IDError;
		}

		V_DI[1]=V_DI[0]-1;
		V_DI[1]+=233;			/*233,Str_3aTable_E23RAM表格中冻结表格I_Free_OADTab  起始偏移*/
		V_Str_3aTable=Str_3aTable_E23RAM[V_DI[1]];
		V_Return_Flag=SF_Re_E23_RAM_Data698(&V_Str_3aTable,*P_Data_Length,P_Data);
	}
	else
	{
		if((CSafeModeParaNat3&0xFFFFFF00)==(V_Data_Id&0xFFFFFF00))/*读安全模式参数,属性3*/
		{
			V_Return_Flag=SF_Read_E21CRC_Data698(E2Addr_SafeModeParaNat3,*P_Data_Length,P_Data);
		}
		else/*读其他关联列表,借用通用读*/
		{
			if(*P_Data_Length>255)
			{
				V_Data_Length=255;
			}
			else
			{
				V_Data_Length=*P_Data_Length;
			}

			V_Return_Flag = InF_Read_Data(V_Data_Id, P_Data, &V_Data_Length, &V_usDataEncode);
			*P_Data_Length = V_Data_Length;
		}
	}

	return V_Return_Flag;
}
/*********************************************************************************
函数原型：uchar8 SF_ReadCurrentTab_Data(ulong32 V_Data_Id,uchar8 *P_Data,uchar8 *P_Data_Length)
功能描述：读数据层事件当前记录表
输入参数：
		ulong32 V_Data_Id：数据标识码；
		uchar8 *P_Data ：数据所放缓存；
		uchar8 *P_Data_Length：作为输入参数时，该参数值为模块所读数据缓存长度最大值，用于数据层判断，所读数据长度，
		是否溢出，如溢出则返回数据长度错误。当作为输出参数时，数据层返回所读取数据长度。
输出参数：uchar8 *P_Data_Length：数据层返回所读取数据长度。
返回参数：C_OK、C_IICError、C_SPIError、C_DataLenError、C_IDError、C_NoAccess、C_CRCError、C_CrcErr_DataZero；
功能说明：
调用机制：
备     注：该部分主要是没有累计时间的事件记录，有累计时间的记录，直接读事件记录模块
*********************************************************************************/
uchar8 SF_ReadCurrentTab_Data(ulong32 V_Data_Id, uchar8 *P_Data, ushort16 *P_Data_Length)
{
	uchar8 V_Return_Flag,V_Source[4],V_Line;
	ulong32 V_Gree,P_FlashAddr1[2];
	ushort16 V_DataLen;

	V_Return_Flag=C_OK;

	switch(V_Data_Id)
	{
		case CProgReC_Current:     /*组合无功编程记录 需特殊处理发生源*/
		{
			V_Return_Flag=SF_ReadE2Three(E2Addr_ProgReC1_Degree,CLProgReC_Degree,&V_Source[0]);
			PF_Buffer4ToUlong32(&V_Source[0],&V_Gree,CLProgReC_Degree);
			if((C_OK==V_Return_Flag)&&(V_Gree>0))
			{
				V_DataLen=SF_GetEventDataLen(E2Addr_ProgReC_OADTab,E2Addr_ProgReC_OADTabLen,((ulong32)&Str_4aTable_AllLossVol[0]),Str_4aTable_AllLossVol_Len);
				if((0==V_DataLen)||(0xFFFF==V_DataLen))
				{
					V_Return_Flag=C_DataLenError;
				}
				else
				{
					SF_GetFlashAddr(V_Gree,FlashStAddr_ProgReC1,V_DataLen,FlashEndAddr_ProgReC1,&P_FlashAddr1[0]);   /*获取上1次当前数据Flash页地址及页内地址*/
					P_FlashAddr1[0]+=P_FlashAddr1[1];
					if(P_FlashAddr1[0]<C_Flash_Max_Addr)
					{
						InF_FlashChipSelect();
						InF_ReadFlash((P_FlashAddr1[0]+CLEventNum+CLEventHPTime+CLEventEndTime),&V_Source[0],CLProgReC_Source);    /*读记录发生源*/
					}
				}
			}

			switch(V_Data_Id&0x000000FF)
			{
				case 0:/*集合记录*/
				{
					if(* P_Data_Length<CLProgReC_Current)
					{
						V_Return_Flag=C_DataLenError;
					}
					else
					{
						*P_Data_Length=CLProgReC_Current;

						for(V_Line=0;V_Line<CLProgReC_Source;V_Line++)/*发生源*/
						{
							P_Data[V_Line]=V_Source[V_Line];
						}

						V_Line=CLProgReC_Degree;
						PF_HextoBCDBytes(&V_Gree,&P_Data[CLProgReC_Source],&V_Line);
						memset(&P_Data[CLProgReC_Degree+CLProgReC_Source], C_NotSupportAOD_Data, (CLProgReC - CLProgReC_Degree));
					}
				}break;

				case 1:/*发生源*/
				{
					if(* P_Data_Length<CLProgReC_Source)
					{
						V_Return_Flag=C_DataLenError;
					}
					else
					{
						*P_Data_Length=CLProgReC_Source;

						for(V_Line=0;V_Line<CLProgReC_Source;V_Line++)
						{
							P_Data[V_Line]=V_Source[V_Line];
						}

						V_Return_Flag=C_OK;
					}
				}break;

				case 2:/*发生次数、累计时间*/
				{
					if(* P_Data_Length<CLProgReC)
					{
						V_Return_Flag=C_DataLenError;
					}
					else
					{
						*P_Data_Length=CLProgReC;
						V_Line=CLProgReC_Degree;
						PF_HextoBCDBytes(&V_Gree,P_Data,&V_Line);

						for(V_Line=0;V_Line<(CLProgReC-CLProgReC_Degree);V_Line++)
						{
							P_Data[CLProgReC_Degree+V_Line]=C_NotSupportAOD_Data;
						}
					}
				}break;

				default:
				{
					V_Return_Flag=C_AbnormalError;
				}break;
			}
		}break;

		default:/*发生源通用读取*/
		{
			for(V_Line=0;V_Line<GCStr_EventCurrentTab_Len;V_Line++)
			{
				if((V_Data_Id&0xFFFFFF00)==(GCStr_EventCurrentTab[V_Line].V_OAD&0xFFFFFF00))
				{
					break;
				}
			}

			if(V_Line>=GCStr_EventCurrentTab_Len)
			{
				V_Return_Flag=C_IDError;
			}
			else
			{
				switch(V_Data_Id&0x000000FF)
				{
					case 0:/*集合记录*/
					{
						if(* P_Data_Length<CLTol_Clear_Current)
						{
							V_Return_Flag=C_DataLenError;
						}
						else
						{
							*P_Data_Length=CLTol_Clear_Current;

							for(V_Line=0;V_Line<CLTol_Clear_Source;V_Line++)
							{
								P_Data[V_Line]=C_NotSupportAOD_Data;/*发生源也为空*/
							}

							V_Return_Flag=SF_ReadE2Three(GCStr_EventCurrentTab[V_Line].V_Num_E2BakeUp1Addr,CLTol_Clear_Degree,&P_Data[CLTol_Clear_Source]);
							PF_Buffer4ToUlong32(&P_Data[CLTol_Clear_Source],&V_Gree,CLTol_Clear_Degree);

							V_Line=CLTol_Clear_Degree;
							PF_HextoBCDBytes(&V_Gree,&P_Data[CLTol_Clear_Source],&V_Line);

							for(V_Line=0;V_Line<(CLTol_Clear-CLTol_Clear_Degree);V_Line++)/*累计时间*/
							{
								P_Data[CLTol_Clear_Source+CLTol_Clear_Degree+V_Line]=C_NotSupportAOD_Data;
							}
						}
					}break;

					case 1:/*发生源*/
					{
						if(* P_Data_Length<CLTol_Clear_Source)
						{
							V_Return_Flag=C_DataLenError;
						}
						else
						{
							*P_Data_Length=CLTol_Clear_Source;

							for(V_Line=0;V_Line<CLTol_Clear_Source;V_Line++)
							{
								P_Data[V_Line]=C_NotSupportAOD_Data;
							}

							V_Return_Flag=C_OK;
						}
					}break;

					case 2:/*发生次数、累计时间*/
					{
						if(* P_Data_Length<CLTol_Clear)
						{
							V_Return_Flag=C_DataLenError;
						}
						else
						{
							*P_Data_Length=CLTol_Clear;
							V_Return_Flag=SF_ReadE2Three(GCStr_EventCurrentTab[V_Line].V_Num_E2BakeUp1Addr,CLTol_Clear_Degree,P_Data);
							PF_Buffer4ToUlong32(P_Data,&V_Gree,CLTol_Clear_Degree);

							V_Line=CLTol_Clear_Degree;
							PF_HextoBCDBytes(&V_Gree,P_Data,&V_Line);

							for(V_Line=0;V_Line<(CLTol_Clear-CLTol_Clear_Degree);V_Line++)
							{
								P_Data[CLTol_Clear_Degree+V_Line]=C_NotSupportAOD_Data;
							}
						}
					}break;

					default:
					{
						V_Return_Flag=C_AbnormalError;
					}break;
				}
			}
		}break;
	}
	return V_Return_Flag;
}


/*********************************************************************************
函数原型：uchar8 InF_Read_Data(ulong32 V_ulData_Id, uchar8 *pV_ucData, ushort16 *pV_usData_Length, ushort16 *pV_usDataEncode)
功能描述：读数据层接口函数,该函数只是一个“帽子”，实际为uchar8SF_Read_Data
输入参数：
		ulong32 V_ulData_Id： 数据标识码
		uchar8 *pV_ucData：数据所放缓存；
		uchar8 *pV_usData_Length：作为输入参数时，该参数值为模块所读数据缓存长度最大值，用于数据层判断，所读数据长度，
		是否溢出，如溢出则返回数据长度错误。当作为输出参数时，数据层返回所读取数据长度。
输出参数：uchar8 *pV_usData_Length：数据层返回所读取数据长度，读取出错的情况下数据长度返回0
		*pV_ucData为数据层读取返回数据，当数据读取出错的情况下
返回参数：C_OK、C_IICError、C_SPIError、C_DataLenError、C_IDError、C_NoAccess、C_CRCError、C_CrcErr_DataZero；
功能说明：
调用机制：
备     注：注意数据长度，通用读数据接口函数，数据长度为默认645长度，如电量类6+2，如读6+4则为InF_Read_Data_For_Dis接口函数
*********************************************************************************/
uchar8 InF_Read_Data(ulong32 V_ulData_Id, uchar8 *pV_ucData, ushort16 *pV_usData_Length, ushort16 *pV_usDataEncode)
{
	uchar8 V_Return_Flag;
	uchar8 V_MesNum;

	if(SF_Read_698SpecialData(V_ulData_Id, pV_ucData, pV_usData_Length, pV_usDataEncode) == C_OK)
	{
		return C_OK;
	}

	V_MesNum = C_Read_Data;
	V_Return_Flag = SF_Read_Data(V_ulData_Id, pV_ucData, pV_usData_Length, V_MesNum, pV_usDataEncode);

	return V_Return_Flag;
}
/*********************************************************************************
函数原型：uchar8 SF_Read_698SpecialData(ulong32 V_ulData_Id, uchar8 *pV_ucData, ushort16 *pV_usData_Length, ushort16 *pV_usDataEncode)
功能描述：读数据层接口函数,该函数为通用读及显示读，共同调用。即显示读数据层及通用读数据层，为该函数带了个“帽子”
输入参数：
		ulong32 V_ulData_Id ：数据标识码；
		uchar8 *pV_ucData ：数据所放缓存；
		uchar8 *pV_usData_Length ：作为输入参数时，该参数值为模块所读数据缓存长度最大值，用于数据层判断，所读数据长度，
		是否溢出，如溢出则返回数据长度错误。当作为输出参数时，数据层返回所读取数据长度。
输出参数：ushort16*P_Data_Length：数据层返回所读取数据长度。
返回参数：C_OK、C_IICError、C_SPIError、C_DataLenError、C_IDError、C_NoAccess、C_CRCError、C_CrcErr_DataZero；
功能说明：
调用机制：
备     注：注意数据长度.698分标识码特殊数据读取。
*********************************************************************************/
uchar8 SF_Read_698SpecialData(ulong32 V_ulData_Id, uchar8 *pV_ucData, ushort16 *pV_usData_Length, ushort16 *pV_usDataEncode)
{
	uchar8 V_Dataoff, V_Return_Flag, V_MesNum = C_Read_Data;
	uchar8 V_DataBuff[60] = {0};
	ushort16 V_usLen = sizeof(V_DataBuff);
	ushort16 V_usCRC_C, V_usCRC_F;


	V_Dataoff = (uchar8)V_ulData_Id;

	if( ( (V_ulData_Id & 0xFFFFFF00) == CFirst_TZone_Data) || ( (V_ulData_Id & 0xFFFFFF00) == CSec_TZone_Data) )
	{
		if( (V_Dataoff == 0)||(V_Dataoff > 14) )
		{
			return C_IDError;
		}

		if(*pV_usData_Length < 3)
		{
			return C_DataLenError;
		}

		if( (V_ulData_Id & 0xFFFFFF00) == CFirst_TZone_Data)
		{
			V_ulData_Id = CFirst_TZone_Data;
		}
		else
		{
			V_ulData_Id = CSec_TZone_Data;
		}

		V_Return_Flag = SF_Read_Data(V_ulData_Id, V_DataBuff, &V_usLen, V_MesNum, pV_usDataEncode);

		if(V_Return_Flag == C_OK)
		{
			PF_CopyDataBytes( &V_DataBuff[ (V_Dataoff - 1)*3 ], pV_ucData, 3);
			*pV_usData_Length = 3;
		}
	}
	else if( (V_ulData_Id & 0xFFFFFF00) == CMeter_Position)
	{
		if( (V_Dataoff == 0) || ( V_Dataoff > 3 ) )
		{
			return C_IDError;
		}

		if(*pV_usData_Length < 4)
		{
			return C_DataLenError;
		}

		/*V_ulData_Id = CMeter_Position;*/
		V_Return_Flag = SF_Read_Data(CMeter_Position, V_DataBuff, &V_usLen, V_MesNum, pV_usDataEncode);

		if(V_Return_Flag == C_OK)
		{
			PF_CopyDataBytes( &V_DataBuff[ (V_Dataoff - 1) * 4], pV_ucData, 4);
			*pV_usData_Length = 4;
		}
	}
	else if( V_ulData_Id == 0xFF860200)	/*自扩对象处理：读取软件版本特征*/
	{
		V_usCRC_C = PF_Cal_CRC_698( (uchar8 *)C_Software_Featurcode, C_FeaturCode_Len );
		V_usCRC_F = PF_Buffer2ToLong16_698( (uchar8 *)(C_Software_Featurcode + C_FeaturCode_Len) );

		if( V_usCRC_F == V_usCRC_C)
		{
			memcpy(pV_ucData, (uchar8 *)C_EnterBootFlag, C_EnterBootFlag_Len);		/*这里仅仅为了调用一下，让C_EnterBootFlag不要被优化掉*/
			memcpy(pV_ucData, (uchar8 *)C_Software_Featurcode, C_FeaturCode_Len);
			(*pV_usData_Length) = C_FeaturCode_Len;
			V_Return_Flag = C_OK;
		}
		else
		{
			V_Return_Flag = C_Error;
		}
	}
	else
	{
		return C_IDError;
	}

	if(V_Return_Flag != C_OK)
	{
		(*pV_usData_Length) = 0;
	}
	return V_Return_Flag;
}
/*********************************************************************************
函数原型：uchar8 SF_JudgeEventAgreeIsYes(uchar8 V_DI0,ushort16 V_E2AgreeAddr)
功能描述：判断事件记录所读次数DI0，是否≤事件记录目前存储次数。当所读次数≤记录次数，则返回OK，其余返回异常
输入参数：
		uchar8 V_DI0：数据标识码DI0，即所读记录次数；
		ushort16 V_E2AgreeAddr：事件记录次数，所存E2地址；
返回参数：C_OK、C_IICError、C_SPIError、C_DataLenError、C_IDError、C_NoAccess、C_CRCError、C_CrcErr_DataZero；
功能说明：
调用机制：
备     注：
*********************************************************************************/
uchar8 SF_JudgeEventAgreeIsYes(uchar8 V_DI0,ushort16 V_E2AgreeAddr)
{
	uchar8 V_Return_Flag;
	uchar8 P_Dgree[CLAll_Loss_Vol_Degree];
	ulong32 V_Dgree;

	V_Return_Flag=SF_ReadE2Three(V_E2AgreeAddr,CLAll_Loss_Vol_Degree,&P_Dgree[0]);

	if(C_OK!=V_Return_Flag)
	{
		return	V_Return_Flag;
	}

	PF_Buffer4ToUlong32(&P_Dgree[0],&V_Dgree,CLAll_Loss_Vol_Degree);

	if((0==V_DI0)||(V_DI0>V_Dgree))
	{
		return C_NoData;
	}
	else
	{
		return C_OK;
	}
}

/*********************************************************************************
函数原型：uchar8 SF_Read_Data( ulong32 V_ulData_Id, uchar8 *pV_ucData, ushort16 *pV_usData_Length, uchar8 V_MesNum, ushort16 *pV_usDataEncode)
功能描述：读数据层接口函数,该函数为通用读及显示读，共同调用。即显示读数据层及通用读数据层，为该函数带了个“帽子”
输入参数：
		ulong32  V_ulData_Id ：数据标识码；
		uchar8 *pV_ucData ：数据所放缓存；
		uchar8 *pV_usData_Length ：作为输入参数时，该参数值为模块所读数据缓存长度最大值，用于数据层判断，所读数据长度，
		是否溢出，如溢出则返回数据长度错误。当作为输出参数时，数据层返回所读取数据长度。
		uchar8 V_MesNum :读数据消息号，用于区分是通用读，还是显示读。当为通用读时消息号为0，显示读时为显示Num号
输出参数：ushort16 *pV_usData_Length：数据层返回所读取数据长度。
返回参数：C_OK、C_IICError、C_SPIError、C_DataLenError、C_IDError、C_NoAccess、C_CRCError、C_CrcErr_DataZero；
功能说明：
调用机制：
备     注：注意数据长度
*********************************************************************************/
uchar8 SF_Read_Data(ulong32 V_ulData_Id, uchar8 *pV_ucData, ushort16 *pV_usData_Length, uchar8 V_MesNum, ushort16 *pV_usDataEncode)
{
	uchar8 V_Return_Flag, V_WR_Mes, V_DI[4];
	ushort16 V_Line, V_3TableE2Addr;
	ushort16 V_DataLen;
	Str_2Table *PStr_2TableAddr = NULL;
	Str_3aTable *PStr_3aTableAddr = NULL;
	uchar8 *P_3TableRamAddr = NULL;
	Str_3eTable *PStr_3eTable_2E2 = NULL;

	PF_Ulong32ToBuffer4(&V_DI[0], &V_ulData_Id, 4);
	V_DataLen = (ushort16)(*pV_usData_Length);

	if( (CI_Free_OADTab & 0xFFFFFF00)==(V_ulData_Id & 0xFFFFFF00) )		/*读冻结序号表，数据长度问题。在该部分不支持，需调用InF_ReadOADTab_Data*/
	{
		(*pV_usData_Length) = 0;
		return C_IDError;
	}
#if _DEBUGFY /*不再存RAM，改为使用宏定义,拼接时去掉*/
	/****计量芯片读出的脉冲最大阀值,hex格式，目前电能模块用(防飞走),特殊处理****/
	if(CPluse_Most__Lim == V_ulData_Id)
	{
		if( (*pV_usData_Length) < CLPluse_Most__Lim)		/*数据长度判断*/
		{
			(*pV_usData_Length) = 0;
			return C_DataLenError;
		}
		else
		{
			*pV_usData_Length = CLPluse_Most__Lim;
			PF_CopyDataBytes( (uchar8 *)(&GV_C_Pluse_Most__Lim[0]), pV_ucData ,CLPluse_Most__Lim);
			return C_OK;
		}
	}
#endif
	/******************************读事件记录当前记录表***class 07******************************/
	if( 0x30000700 == (V_ulData_Id & 0xF000FF00) )
	{
		V_Return_Flag = SF_ReadCurrentTab_Data(V_ulData_Id, pV_ucData, pV_usData_Length);
		if( V_Return_Flag != C_OK)
		{
			(*pV_usData_Length) = 0;
		}
		return V_Return_Flag;
	}

	/*********************************以下为读通用数据*****************************************/
	V_Return_Flag = SF_Find1Table_Data(V_DI[3], &V_Line);                        /*查找1级表*/
	if(V_Return_Flag!=C_OK)
	{
		(*pV_usData_Length) = 0;
		return V_Return_Flag;
	}

	V_WR_Mes = V_MesNum;
	if(0x04 == V_DI[3])/*参变量查2级分表，特殊处理。增加变量操作效率*/
	{
		V_Return_Flag = SF_Find2Table_DIParamChild(V_DI[2], &V_Line);
		if(V_Return_Flag != C_OK)
		{
			(*pV_usData_Length) = 0;
			return V_Return_Flag;
		}

		PStr_2TableAddr = (Str_2Table *)(Str_2Table_DIParamChild[V_Line].PStr_2TableParamChildAddr);		/*DI2对应的2级表地址*/
		V_Return_Flag = SF_Find2Table_Data(V_WR_Mes, V_ulData_Id, &V_DataLen, PStr_2TableAddr, &V_Line, Str_2Table_DIParamChild[V_Line].V_Str_2TableLen);
	}
	else
	{
		PStr_2TableAddr=(Str_2Table * )(Str_1Table_DI3[V_Line].PStr_2TableAddr);		/*DI3对应的2级表地址*/
		V_Return_Flag=SF_Find2Table_Data(V_WR_Mes, V_ulData_Id, &V_DataLen, PStr_2TableAddr, &V_Line, Str_1Table_DI3[V_Line].V_Str_2TableLen);
	}

	*pV_usData_Length = (V_DataLen);

	if(V_Return_Flag != C_OK)
	{
		(*pV_usData_Length) = 0;
		return V_Return_Flag;
	}
	else
	{
		if(0 == (*pV_usData_Length) )/*所读数据长度为零，目前只有关联OAD序号表可能会出现该情况(没有OAD序号表，个数长度为0)*/
		{
			return V_Return_Flag;
		}
	}

	switch(PStr_2TableAddr[V_Line].V_DT_Type)   /*DI2-DI0对应2级表具体的行号，不同数据处理方式*/
	{
		case DT_Ref_E23_RAMCRC:                   /*①E2三处CRC备份及RAM带CRC(写该类数据时，先写RAM，接着更新E2数据)*/
		case DT_Ti_E23_RAMCRC:                    /*②E2三处CRC备份及RAM带CRC(写该类数据时，只写RAM，定时写E2，主要是当前电量该类数据) */
		case DT_Ref_E23_RAMCRC_DI0:               /*19：E2三处RAM带CRC，数据长度类型一样(同一DI3-DI1)，列表格时只列DI0最大值(不包括DI0=0，DI0=0要单列)，程序内部处理，*/
		                                          /*数据地址及DI判断是否正确，如类似组合状态字，列表格时，对应数据存储地址，为最低DI0对应数据存储地址，注意*/
		case DT_Ref_E23_RAMCRC_DI0_2:             /*28：E2三处RAM带CRC，数据长度类型一样(同一DI3-DI1)，列表格时只列DI0最大值(不包括DI0=0，1,DI0=0,1要单列)，程序内部处理，*/
		                                           /*数据地址及DI判断是否正确，如类似全失压电流该类参数设置，列表格时，对应数据存储地址(电压异常判断电压地址)，为最低DI0对应数据存储地址，注意*/
		case DT_R_Ref_E23_RAMCRC_Lad:  				    /*39:写E2 RAM数据，阶梯表写入时支持集合写，读数据时支持分开读，数据层内部单独处理*/
		{
			PStr_3aTableAddr = (Str_3aTable *)PStr_2TableAddr[V_Line].PStr_3TableAddr;   /*取3级表地址*/

			if(DT_Ref_E23_RAMCRC_DI0 == PStr_2TableAddr[V_Line].V_DT_Type)
			{
				if(0==V_DI[0])
				{
					(*pV_usData_Length) = 0;
					return C_AbnormalError;              /*正常不存在*/
				}
			}

			if( (V_ulData_Id & 0xFFFFFF00) == (CL_Free_OADTab & 0xFFFFFF00) )	/*冻结OAD序号表,写数据不判断数据长度，但判断写数据长度不能大于最大长度*/
			{
				V_Return_Flag = SF_Re_E23_RAM_Data698(&PStr_3aTableAddr[PStr_2TableAddr[V_Line].V_LineNum], V_DataLen, pV_ucData);
			}
			else
			{
				V_Return_Flag = SF_Re_E23_RAM_Data(PStr_3aTableAddr, PStr_2TableAddr[V_Line].V_LineNum, V_DataLen, pV_ucData, PStr_2TableAddr[V_Line].V_DT_Type, V_DI[0], V_ulData_Id);
			}

			if(CComm_Address == V_ulData_Id)/*通信地址特殊处理，没有设置，默认为全0*/
			{
				uchar8 V_i;
				if(C_OK != V_Return_Flag)/*读失败*/
				{
					for(V_i = 0; V_i < CLComm_Address; V_i++)
					{
						pV_ucData[V_i] = 0x00;
					}
					V_Return_Flag = C_OK;
				}
			}
		}break;

		case DT_E23:                              /*③E2三处CRC备份*/
		case DT_E23_Clear:                              /*③E2三处CRC备份*/
		case DT_E23_Hex:                          /*⑧E2三处CRC备份，数据存储格式为hex格式(主要是累计次数，在通讯读该数据时，转换为BCD格式)*/
#if 0
		case DT_E23_En:                           /*16：电量类数据，满足6+2与6+4数据长度时，该数据需单独处理，数据长度(读、写)及所读数据，根据是否是6+4(类似显示),或6+2(类似通信)，进行特殊处理*/
		                                    /*(列表645数据长度为6+2，当采用6+4读数据时，返回数据长度调整，取E2地址调整，如上1结算周期内组合有功累计用电量),写数据时，数据长度判断调整；*/
		case DT_E23_En_Clear:                           /*16：电量类数据，满足6+2与6+4数据长度时，该数据需单独处理，数据长度(读、写)及所读数据，根据是否是6+4(类似显示),或6+2(类似通信)，进行特殊处理*/
		                                    /*(列表645数据长度为6+2，当采用6+4读数据时，返回数据长度调整，取E2地址调整，如上1结算周期内组合有功累计用电量),写数据时，数据长度判断调整；*/
#endif
		case DT_E23_DI0:                          /*20：E2三处，E2地址顺序列，数据长度类型一样(同一DI3-DI1)，列表格时只列DI0最大值(不包括DI0=0，DI0=0要单列)，程序内部处理，*/
		                                  /*数据地址及DI判断是否正确，如类似结算日、密码，列表格时，对应数据存储地址，为最低DI0对应数据存储地址，注意*/
		case DT_E23_OADTab:               /*38:存E2三处，判断数据长度时，需读取该关联列表OAD个数*/
		{
			if(DT_E23_OADTab==PStr_2TableAddr[V_Line].V_DT_Type)
			{
				PStr_3eTable_2E2 = (Str_3eTable *)(PStr_2TableAddr[V_Line].PStr_3TableAddr);

				if(PStr_2TableAddr[V_Line].V_LineNum>=Str_3eTable_Flash_Len)
				{
					(*pV_usData_Length) = 0;
					return C_DataLenError;
				}

				V_3TableE2Addr=PStr_3eTable_2E2[PStr_2TableAddr[V_Line].V_LineNum].V_E2BakeUp1Addr_OADTab;
			}
			else
			{
				V_3TableE2Addr=(ushort16)PStr_2TableAddr[V_Line].PStr_3TableAddr;   /*取3级表E2地址*/
			}

			if(DT_E23_DI0==PStr_2TableAddr[V_Line].V_DT_Type)    /*E2地址调整*/
			{
				if(0==V_DI[0])
				{
					(*pV_usData_Length) = 0;
					return C_AbnormalError;              /*正常不存在*/
				}

				V_3TableE2Addr=V_3TableE2Addr+(V_DI[0]-1)*(V_DataLen+C_CRCLen2);
				if(V_3TableE2Addr>E2_Max_Addr)
				{
					(*pV_usData_Length) = 0;
					return C_AbnormalError;              /*正常不存在*/
				}
			}

			V_Return_Flag=SF_Re_E23_Data(V_3TableE2Addr, V_DataLen, pV_ucData, PStr_2TableAddr[V_Line].V_DT_Type, V_WR_Mes);

			if(CComm_Address == V_ulData_Id)/*通信地址特殊处理，没有设置，默认为全0*/
			{
				uchar8 V_i;
				if(C_OK != V_Return_Flag)/*读失败*/
				{
					for(V_i = 0; V_i < CLComm_Address; V_i++)
					{
						pV_ucData[V_i] = 0x00;
					}
					V_Return_Flag = C_OK;
				}
			}
		}break;

		case DT_Flash_DI04:                       /*④Flash，带次数数据，DI0低4位表示次数，高4位表示不同标识码(查询4级表用)*/
		case DT_Flash_Tol_DI0_DI1:                /*⑨Flash，带次数数据，整个DI0表示次数，DI1表示分项标识码(查询4级表用)*/
#if 0
		case DT_Flash_Tol_DI0_DI2:                /*11： Flash，带次数数据，整个DI0表示次数，DI2表示分项标识码(查询4级表用，主要是电量、需量，ABC三相数据)*/
		case DT_Flash_Tol_DI0_SettEn:             /*12：Flash，带次数数据，整个DI0表示次数，利用DI2、DI1计算分项偏移地址(代替查询4级表，主要是结算电量读，除ABC三相数据外)。*/
		case DT_Flash_Tol_DI0_SettDe:             /*13：Flash，带次数数据，整个DI0表示次数，利用DI2、DI1计算分项偏移地址(代替查询4级表，主要是结算需量读，除ABC三相数据外)。*/
		case DT_Flash_Tol_DI0:                    /*15： Flash，带次数数据，整个DI0表示次数。没有分项标识码。*/
		case DT_R_Flash_Tol_DI0_DI2_En:           /*25： Flash，带次数数据，整个DI0表示次数，DI2表示分项标识码(查询4级表用，电量的ABC三相数据读)，*/
		                                          /*同时数据长度及所读数据，根据是否是6+4(类似显示),或6+2(类似通信)，进行特殊处理*/
#endif
		case DT_Flash_Tol_DI0_DI1Max:             /*27： Flash，带次数数据，整个DI0表示次数，列表2级表时只列上1次DI1最大值(不采用查找4级表的方式)，在查找数据DI及DI数据存放偏移地址时，*/
		                                      /*OffsetAddr程序采用计算方式处理,目前只有校表记录采用该方式,除发生时刻DI1=0外*/
		case DT_Flash_698EventTab:     						/*37:带OAD关联列表事件记录，存Flash*/
		{
			V_Return_Flag = SF_ReadFlash_Data(pV_ucData, V_DataLen, PStr_2TableAddr[V_Line].PStr_3TableAddr, V_ulData_Id, PStr_2TableAddr[V_Line].V_LineNum, PStr_2TableAddr[V_Line].V_DT_Type, V_WR_Mes);
		}break;

		case DT_E21:                              /*⑤E2一处*/
#if 0
		case DT_E21_En:                           /*17：电量类数据，满足6+2与6+4数据长度时，该数据需单独处理，数据长度(读、写)及所读数据，根据是否是6+4(类似显示),或6+2(类似通信)，进行特殊处理,主要针对存E2 1处数据*/
		                                          /*(列表645数据长度为6+2，当采用6+4读数据时，返回数据长度调整，取E2地址调整，如上1--4次年结算日结算时间及结算周期组合有功总累计用电量*/
#endif
		case DT_E21_DI0:                          /*22：E2一处，数据长度类型一样(同一DI3-DI1)，列表格时只列DI0最大值(不包括DI0=0，DI0=0要单列)，程序内部处理，*/
		{                                        /*数据地址及DI判断是否正确，如类似第1-254公共假日日期及日时段表号，列表格时，对应数据存储地址，为最低DI0对应数据存储地址，注意*/
			V_3TableE2Addr=(ushort16)PStr_2TableAddr[V_Line].PStr_3TableAddr;   /*取3级表E2地址*/
#if 0
			if((DT_E21_DI0==PStr_2TableAddr[V_Line].V_DT_Type)
				||(DT_E21_DI0_ReadDegree==PStr_2TableAddr[V_Line].V_DT_Type))    /*E2地址调整*/
#endif
			if( DT_E21_DI0 == PStr_2TableAddr[V_Line].V_DT_Type )
			{
				if(0==V_DI[0])
				{
					(*pV_usData_Length) = 0;
					return C_AbnormalError;              /*正常不存在*/
				}

				V_3TableE2Addr=V_3TableE2Addr+(V_DI[0]-1)*V_DataLen;
				if(V_3TableE2Addr>E2_Max_Addr)
				{
					(*pV_usData_Length) = 0;
					return C_AbnormalError;              /*正常不存在*/
				}
			}

			V_Return_Flag = SF_ReadE21(V_3TableE2Addr, V_DataLen, pV_ucData, PStr_2TableAddr[V_Line].V_DT_Type, V_WR_Mes);
		}break;

		case DT_RAM:                              /*⑥RAM不带CRC*/
		case DT_RAM_Time_Data:                    /*⑩RAM不带CRC，读数据时先判断掉电标志。*/
		case DT_RAM_DI0:	                        /*18：数据存RAM不带CRC，且数据长度、类型一样(同一DI3-DI1)，列表格时只列DI0最大值(,同一类型，不包括DI0=0，DI0=0要单列)，程序内部处理，*/
		                                          /*数据地址及DI判断是否正确，如类似电表运行状态字1-7，列表格时，对应数据存储地址，为最低DI0对应数据存储地址，注意*/
#if 0
		case DT_RAM_DI1_0:                        /*23：数据存RAM不带CRC，且数据长度、类型一样(同一DI3-DI2、DI0)，列表格时只列DI1最大值(,同一类型,包括DI1=0，计算数据偏移地址时，要考虑)，*/
		                                        /*程序内部处理，数据地址及DI判断是否正确，如类似参数瞬时功率，列表格时，对应数据存储地址，为最低DI1对应数据存储地址，注意*/
		case DT_RAM_DI1:	                        /*24：数据存RAM不带CRC，且数据长度、类型一样(同一DI3-DI2、DI0)，列表格时只列DI1最大值(,同一类型，不包括DI1=0)，程序内部处理，*/
#endif
		{                                      /*数据地址及DI判断是否正确，如类似电压数据，列表格时，对应数据存储地址，为最低DI1对应数据存储地址，注意*/
			P_3TableRamAddr=(uchar8 *)PStr_2TableAddr[V_Line].PStr_3TableAddr;

			if(DT_RAM_DI0==PStr_2TableAddr[V_Line].V_DT_Type)
			{
				if(0==V_DI[0])
				{
					(*pV_usData_Length) = 0;
					return C_AbnormalError;              /*正常不存在*/
				}
				P_3TableRamAddr=P_3TableRamAddr+(V_DI[0]-1)*V_DataLen;
			}
#if 0
			if(DT_RAM_DI1_0==PStr_2TableAddr[V_Line].V_DT_Type)
			{
				P_3TableRamAddr=P_3TableRamAddr+V_DI[1]*V_DataLen;
			}

			if(DT_RAM_DI1==PStr_2TableAddr[V_Line].V_DT_Type)
			{
				if(0==V_DI[1])
				{
					(*pV_usData_Length) = 0;
					return C_AbnormalError;              /*正常不存在*/
				}
				P_3TableRamAddr=P_3TableRamAddr+(V_DI[1]-1)*V_DataLen;
			}
#endif
			V_Return_Flag=SF_Re_RAM_Data(P_3TableRamAddr, V_DataLen, pV_ucData, PStr_2TableAddr[V_Line].V_DT_Type, V_DI[0]);
		}break;

		case DT_RAMCRC:                           /*⑦RAM带CRC*/
		{
			P_3TableRamAddr=(uchar8 *)PStr_2TableAddr[V_Line].PStr_3TableAddr;
			V_Return_Flag = SF_Re_RAMCRC_Data(P_3TableRamAddr, V_DataLen, pV_ucData);
		}break;

		case DT_E21CRC_DI0:                       /*21：E2一处带CRC，数据长度类型一样(同一DI3-DI1)，列表格时只列DI0最大值(不包括DI0=0，DI0=0要单列)，程序内部处理，*/
		{                                        /*数据地址及DI判断是否正确，如类似自动循显显示第1-99屏显示代码，列表格时，对应数据存储地址，为最低DI0对应数据存储地址，注意*/
			V_3TableE2Addr=(ushort16)PStr_2TableAddr[V_Line].PStr_3TableAddr;   /*取3级表E2地址*/

			if(DT_E21CRC_DI0==PStr_2TableAddr[V_Line].V_DT_Type)    /*E2地址调整*/
			{
				if(0==V_DI[0])
				{
					(*pV_usData_Length) = 0;
					return C_AbnormalError;              /*正常不存在*/
				}

				V_3TableE2Addr=V_3TableE2Addr+(V_DI[0]-1)*(V_DataLen+C_CRCLen2);
				if(V_3TableE2Addr>E2_Max_Addr)
				{
					(*pV_usData_Length) = 0;
					return C_AbnormalError;              /*正常不存在*/
				}
			}

			V_Return_Flag = SF_Read_E21CRC_Data(V_3TableE2Addr, V_DataLen, pV_ucData);
		}break;

		case DT_FRAM1CRC:                       /*42：铁电一处带CRC*/
		{
			V_3TableE2Addr = (ushort16)PStr_2TableAddr[V_Line].PStr_3TableAddr;   /*取3级表铁电地址*/
			V_Return_Flag = SF_Read_FRAM1CRC_Data(V_3TableE2Addr, V_DataLen, pV_ucData);
		}break;

		default:
			return C_IDError;  /*查找错误*/
	}
	if(V_Return_Flag != C_OK)
	{
		(*pV_usData_Length) = 0;
	}
	return V_Return_Flag;
}

/*********************************************************************************
函数原型：uchar8 SF_Re_E23_RAM_Data698(Str_3aTable *PStr_3aTable_E23RAM,ushort16 V_DataLen,uchar8 *P_Data)
功能描述：读E2三处及RAM数据,数据层内部读698数据用
输入参数：
		Str_3aTable *PStr_3aTable_E23RAM:要操作3a级表结构体元素地址；
		ushort16 V_DataLen：要读数据长度
输出参数：
		uchar8 *P_Data：读数据缓存
返回参数：C_OK、C_IICError、C_CRCError、C_CrcErr_DataZero,C_DataLenError；
功能说明：
调用机制：
备注：
*********************************************************************************/
uchar8 SF_Re_E23_RAM_Data698(Str_3aTable *PStr_3aTable_E23RAM,ushort16 V_DataLen,uchar8 *P_Data)
{
	ushort16 V_i,V_CRC_Flag,V_Len;
	ushort16 V_E2Addr;
	uchar8 *P_RamAddr=NULL;
	uchar8 V_Return_Flag;

	if(V_DataLen==0)/*主要是关联列表，假如没有关联列表，也返回ok。主要是数据层取关联列表用，正常别的模块读数据层，在刚开始就返回了。*/
	{
		return C_OK;
	}

	V_Len=V_DataLen+C_CRCLen2;	                /*增加CRC*/
	P_RamAddr=(* PStr_3aTable_E23RAM).V_RamAddr;
	V_E2Addr=(* PStr_3aTable_E23RAM).V_E2BakeUp1Addr;
	V_CRC_Flag=PF_Check_CRC(&P_RamAddr[0],V_Len);/*取RAM数据*/

	V_Len=V_Len-C_CRCLen2;                                /*去掉CRC*/

	if(C_OK==V_CRC_Flag)
	{
		PF_CopyDataBytes_698(&P_RamAddr[0],P_Data,V_Len);
		return C_OK;
	}
	else
	{
		if(C_CrcErr_DataZero==V_CRC_Flag)        /*CRC错误但数据为全零*/
		{
			for(V_i=0;V_i<V_Len;V_i++)
			{
				if(0!=P_RamAddr[V_i])
				{
					break;
				}
			}

			if(V_i==V_Len)                        /*数据正确*/
			{
				PF_CopyDataBytes_698(&P_RamAddr[0],P_Data,V_Len);
				return C_CrcErr_DataZero;         /*返回CRC错误，但数据为全零*/
			}
		}
	}

	V_Len=V_DataLen;
	V_Return_Flag=SF_ReadE2Three_698_AndCRC(V_E2Addr,V_Len,&P_RamAddr[0]);/*返回数据带CRC*/
	PF_CopyDataBytes_698(&P_RamAddr[0],P_Data,V_Len);

	return V_Return_Flag;
}

/*********************************************************************************
函数原型：uchar8 SF_Re_E23_RAM_Data(Str_3aTable *PStr_3aTable_E23RAM,ushort16 V_3aTable_Line,ushort16 V_DataLen,
									uchar8 *P_Data,uchar8 V_DT_Type,uchar8 V_DI,ulong32 V_Data_Id)
功能描述：读E2三处及RAM数据
输入参数：
		Str_3aTable *PStr_3aTable_E23RAM:要操作3a级表结构体地址；
		ushort16 V_3aTable_Line：要操作3a级表格行号；
		ushort16 V_DataLen：要读数据长度
		uchar8 V_DT_Type:数据类型
		uchar8 V_DI:输入DI，用于计算E2、RAM绝对地址
		ulong32 V_Data_Id：DI0-DI3数据标识；
输出参数：uchar8 *P_Data：读数据缓存
返回参数：C_OK、C_IICError、C_CRCError、C_CrcErr_DataZero,C_DataLenError；
功能说明：
调用机制：
备     注：内部包含铁电操作
*********************************************************************************/
uchar8 SF_Re_E23_RAM_Data(Str_3aTable *PStr_3aTable_E23RAM,ushort16 V_3aTable_Line,ushort16 V_DataLen,uchar8 * P_Data,uchar8 V_DT_Type,uchar8 V_DI,ulong32 V_Data_Id)
{
	ushort16 V_i,V_CRC_Flag,V_Len;
	uchar8 PV_Data[C_RAM_Max];
	ushort16 V_E2Addr;
	uchar8 *P_RamAddr=NULL;
	uchar8 V_Return_Flag;
	uchar8 V_Return_Flag1;

	if(V_3aTable_Line>=Str_3aTable_E23RAM_Len)   /*正常不存在*/
	{
		return C_AbnormalError;
	}

	if((C_RAM_Max<(V_DataLen+C_CRCLen2))||(V_DataLen>255))
	{
		if(_DEBUG)
		{
			/**/
		}
		return C_DataLenError;
	}

	V_Len=V_DataLen+C_CRCLen2;	                /*增加CRC*/

	P_RamAddr=PStr_3aTable_E23RAM[V_3aTable_Line].V_RamAddr;
	V_E2Addr=PStr_3aTable_E23RAM[V_3aTable_Line].V_E2BakeUp1Addr;

	if(DT_Ref_E23_RAMCRC_DI0==V_DT_Type)    /*E2、RAM地址调整*/
	{
		if(V_DI<1)
		{
			return C_AbnormalError;
		}

		V_E2Addr=V_E2Addr+(V_DI-1)*(V_DataLen+C_CRCLen2);
		P_RamAddr=P_RamAddr+(V_DI-1)*(V_DataLen+C_CRCLen2);
	}

	if(DT_Ref_E23_RAMCRC_DI0_2==V_DT_Type)  /*04FE0202类参数，从DI0=2开始计算*/
	{
		if(V_DI<2)
		{
			return C_AbnormalError;
		}

		P_RamAddr=P_RamAddr+(V_DI-2)*V_Len;
		V_E2Addr=V_E2Addr+(V_DI-2)*V_Len;
	}

	if(DT_R_Ref_E23_RAMCRC_Lad==V_DT_Type)  /*39:写E2 RAM数据，阶梯表写入时支持集合写，读数据时支持分开读，数据层内部单独处理*/
	{
		V_Len=CLCurrent_Ladder_Table+C_CRCLen2;	                /*增加CRC*/
	}

	for(V_i=0;V_i<V_Len;V_i++)                    /*取RAM数据*/
	{
		PV_Data[V_i]=*(P_RamAddr+V_i);
	}

	V_CRC_Flag=PF_Check_CRC(&PV_Data[0],V_Len);

	/*****************剩余金额特殊处理，剩余金额CRC正常计算，数据全零包含CRC，认为数据错误,20160517********************/
	if(CChargeBal_Hex_Full == V_Data_Id)
	{
		V_Return_Flag1=SF_AllDataZero_Judge(&PV_Data[0],V_Len);/*数据是否为全零判断，包含CRC*/
		if(C_OK==V_Return_Flag1)
		{
			V_CRC_Flag=C_CRCError;/*剩余金额数据全零(包含CRC)，正常不存在(总清时，剩余金额CRC设置为正确)，则认为RAM数据异常。*/
		}
	}

	V_Len=V_Len-C_CRCLen2;                                /*去掉CRC*/
	if(C_OK==V_CRC_Flag)
	{
		if(DT_R_Ref_E23_RAMCRC_Lad==V_DT_Type) /*39:写E2 RAM数据，阶梯表写入时支持集合写，读数据时支持分开读，数据层内部单独处理*/
		{
			switch(V_Data_Id)
			{
				case CCurrent_Ladder_Table_LadNum:
				case CBackUp_Ladder_Table_LadNum:			/*阶梯值*/
				{
					PF_CopyDataBytes(&PV_Data[0],P_Data,(uchar8)V_DataLen);
				}break;

				case CCurrent_Ladder_Table_LadPri:
				case CBackUp_Ladder_Table_LadPri:			/*阶梯电价*/
				{
					if((CLCurrent_Ladder_Table_LadNum+V_DataLen) < C_RAM_Max)
					{
						PF_CopyDataBytes(&PV_Data[CLCurrent_Ladder_Table_LadNum],P_Data,(uchar8)V_DataLen);
					}
				}break;

				case CCurrent_Ladder_Table_LadSett:
				case CBackUp_Ladder_Table_LadSett:			/*阶梯结算日*/
				{
					if((CLCurrent_Ladder_Table_LadNum+CLCurrent_Ladder_Table_LadPri+V_DataLen) < C_RAM_Max)
					{
						PF_CopyDataBytes(&PV_Data[CLCurrent_Ladder_Table_LadNum+CLCurrent_Ladder_Table_LadPri],P_Data,(uchar8)V_DataLen);
					}
				}break;

				default:/*正常不存在*/
					return C_DataLenError;
			}
		}
		else
		{
			PF_CopyDataBytes(&PV_Data[0],P_Data,(uchar8)V_Len);
		}
		return C_OK;
	}
	else
	{
		if(C_CrcErr_DataZero==V_CRC_Flag)        /*CRC错误但数据为全零*/
		{
			for(V_i=0;V_i<V_Len;V_i++)
			{
				if(0!=PV_Data[V_i])
				{
					break;
				}
			}

			if(V_i==V_Len)                        /*数据正确*/
			{
				if(DT_R_Ref_E23_RAMCRC_Lad==V_DT_Type)
				{
					V_Len=V_DataLen;
				}

				PF_CopyDataBytes(&PV_Data[0],P_Data,(uchar8)V_Len);
				return C_CrcErr_DataZero;         /*返回CRC错误，但数据为全零*/
			}
		}
	}

	if(DT_R_Ref_E23_RAMCRC_Lad==V_DT_Type)  /*39:写E2 RAM数据，阶梯表写入时支持集合写，读数据时支持分开读，数据层内部单独处理*/
	{
		V_Len=CLCurrent_Ladder_Table;
	}
	else
	{
		V_Len=V_DataLen;
	}

	if(V_DT_Type==DT_Ti_E23_RAMCRC)/*铁电数据*/
	{
		V_Return_Flag=SF_ReadFRAMThree_AndCRC(V_E2Addr,(uchar8)V_Len,&PV_Data[0]);/*获取数据包含CRC*/
	}
	else/*E2数据*/
	{
		V_Return_Flag=SF_ReadE2Three_AndCRC(V_E2Addr,(uchar8)V_Len,&PV_Data[0]);/*获取数据包含CRC*/
	}

	if(C_OK==V_Return_Flag)  /*7.24*/
	{
		if(DT_R_Ref_E23_RAMCRC_Lad==V_DT_Type)  /*39:写E2 RAM数据，阶梯表写入时支持集合写，读数据时支持分开读，数据层内部单独处理*/
		{
			V_Len=CLCurrent_Ladder_Table+C_CRCLen2;
		}
		else
		{
			V_Len=V_DataLen+C_CRCLen2;
		}

		for(V_i=0;V_i<V_Len;V_i++)     /*RAM 赋值*/
		{
			*(P_RamAddr+V_i)=PV_Data[V_i];
		}
	}

	V_Len=V_DataLen;

	if(DT_R_Ref_E23_RAMCRC_Lad==V_DT_Type) /*39:写E2 RAM数据，阶梯表写入时支持集合写，读数据时支持分开读，数据层内部单独处理*/
	{
		switch(V_Data_Id)
		{
			case CCurrent_Ladder_Table_LadNum:
			case CBackUp_Ladder_Table_LadNum:			/*阶梯值*/
			{
				PF_CopyDataBytes(&PV_Data[0],P_Data,(uchar8)V_DataLen);
			}break;

			case CCurrent_Ladder_Table_LadPri:
			case CBackUp_Ladder_Table_LadPri:			/*阶梯电价*/
			{
				if((CLCurrent_Ladder_Table_LadNum+V_DataLen)<C_RAM_Max)
				{
					PF_CopyDataBytes(&PV_Data[CLCurrent_Ladder_Table_LadNum],P_Data,(uchar8)V_DataLen);
				}
			}break;

			case CCurrent_Ladder_Table_LadSett:
			case CBackUp_Ladder_Table_LadSett:			/*阶梯结算日*/
			{
				if((CLCurrent_Ladder_Table_LadNum+CLCurrent_Ladder_Table_LadPri+V_DataLen)<C_RAM_Max)
				{
					PF_CopyDataBytes(&PV_Data[CLCurrent_Ladder_Table_LadNum+CLCurrent_Ladder_Table_LadPri],P_Data,(uchar8)V_DataLen);
				}
			}break;

			default:/*正常不存在*/
				return C_DataLenError;
		}
	}
	else
	{
		PF_CopyDataBytes(&PV_Data[0],P_Data,(uchar8)V_Len);
	}

	return V_Return_Flag;
}
/*********************************************************************************
函数原型：uchar8 SF_Read_FRAM1CRC_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data)
功能描述：读铁电1处数据，根据Type数据存储类型，判断数据格式
输入参数：
		ushort16 V_E2Addr：读数据铁电地址；
		ushort16 V_DataLen：读数据长度
输出参数：uchar8 *P_Data：读数据缓存
返回参数：C_OK、C_IICError、C_CRCError、C_CrcErr_DataZero；
功能说明：
调用机制：
备     注：
*********************************************************************************/
uchar8 SF_Read_FRAM1CRC_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data)
{
	uchar8 V_Len;
	uchar8 PV_Data[C_RAM_Max];
	uchar8 V_Return_Flag;
	uchar8 V_ReCRC;

	if((C_RAM_Max<(V_DataLen+C_CRCLen2))||(V_DataLen>255))
	{
		if(_DEBUG)
		{
			/**/
		}
		return C_DataLenError;
	}

	V_Len=(uchar8)V_DataLen+C_CRCLen2;

	V_Return_Flag=InF_ReadFRAM(V_E2Addr,&PV_Data[0],(ushort16)V_Len);
	V_ReCRC=PF_Check_CRC(&PV_Data[0],(ushort16)V_Len);

	V_Len=V_Len-C_CRCLen2;
	PF_CopyDataBytes(&PV_Data[0],P_Data,V_Len);

	if(C_OK!=V_Return_Flag)
	{
		return  V_Return_Flag;    /*C_IICError*/
	}
	else
	{
		if(C_OK!=V_ReCRC)
		{
			return V_ReCRC;      /*可能返回C_CrcErr_DataZero*/
		}
		else
		{
			return C_OK;
		}
	}
}

/*********************************************************************************
函数原型：uchar8 SF_Read_E21CRC_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data)
功能描述：读E21处数据，根据Type数据存储类型，判断数据格式
输入参数：
		ushort16 V_E2Addr：读数据E2地址；
		ushort16 V_DataLen：读数据长度
输出参数：uchar8 *P_Data：读数据缓存
返回参数：C_OK、C_IICError、C_CRCError、C_CrcErr_DataZero；
功能说明：
调用机制：
备     注：
*********************************************************************************/
uchar8 SF_Read_E21CRC_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data)
{
	uchar8 V_Len;
	uchar8 PV_Data[C_RAM_Max];
	uchar8 V_Return_Flag;
	uchar8 V_ReCRC;

	if((C_RAM_Max<(V_DataLen+C_CRCLen2))||(V_DataLen>255))
	{
		if(_DEBUG)
		{
		  /**/
		}
		return C_DataLenError;
	}

	V_Len=(uchar8)V_DataLen+C_CRCLen2;
	V_Return_Flag=InF_ReadE2(V_E2Addr,&PV_Data[0],(ushort16)V_Len);
	V_ReCRC=PF_Check_CRC(&PV_Data[0],(ushort16)V_Len);

	V_Len=V_Len-C_CRCLen2;
	PF_CopyDataBytes(&PV_Data[0],P_Data,V_Len);

	if(C_OK!=V_Return_Flag)
	{
		return V_Return_Flag;    /*C_IICError*/
	}
	else
	{
		if(C_OK!=V_ReCRC)
		{
			return V_ReCRC;      /*可能返回C_CrcErr_DataZero*/
		}
		else
		{
			return C_OK;
		}
	}
}

/*********************************************************************************
函数原型：uchar8 SF_Re_E23_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data,uchar8 V_DT_Type,uchar8 V_WR_Mes)
功能描述：读E2三处数据，根据Type数据存储类型，判断数据格式
输入参数：
		ushort16 V_E2Addr：读数据E2地址；
		ushort16 V_DataLen：读数据长度
		uchar8 V_DT_Type：数据类型
		uchar8 V_WR_Mes:读数据消息号，用于区分是通用读，还是显示读。当为通用读时消息号为0，显示读时为显示Num号
输出参数：uchar8 *P_Data：读数据缓存
返回参数：C_OK、C_IICError、C_CRCError、C_CrcErr_DataZero；
功能说明：
调用机制：
备     注：显示读电量类数据数据长度已经为6+4，其他模块读电量类数据为6+2，数据长度需特殊处理
*********************************************************************************/
uchar8 SF_Re_E23_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data,uchar8 V_DT_Type,uchar8 V_WR_Mes)
{
	ushort16 V_Len;
	uchar8 PV_Data[C_RAM_Max];
	uchar8 V_Return_Flag;
	ulong32 V_Hex;

	if(C_RAM_Max<V_DataLen)
	{
		if(_DEBUG)
		{
			/**/
		}
		return C_DataLenError;
	}
#if 0
	if((C_Msg_Display!=(V_WR_Mes&0x7F))&&((DT_E23_En==V_DT_Type)||(DT_E23_En_Clear==V_DT_Type))) /*通信读(显示读电量类数据长度已+1)，电量类--特殊数据--长度需单独处理,不支持显示类，数据块读*/

	{
		V_Len=V_DataLen+1;                   /*645数据长度+1*/
	}
	else
	{
		V_Len=V_DataLen;
	}
#endif

	V_Len=V_DataLen;

	V_Return_Flag=SF_ReadE2Three(V_E2Addr,(uchar8)V_Len,&PV_Data[0]);

	if(DT_E23_Hex==V_DT_Type)             /*读次数转BCD格式*/
	{
		V_Len=CLAll_Loss_Vol_Degree;

		if(V_E2Addr == E2Addr_Program_Degree_645) /*645编程事件特殊处理*/
		{
			PV_Data[3]=0;
		}

		PF_Buffer4ToUlong32(&PV_Data[0],&V_Hex,(uchar8)V_Len);
		/*PF_HextoBCDBytes(&V_Hex,&PV_Data[0],(uchar8 *)(&V_Len));*/	/*次数不需要进行hex-bcd转换*/
	}

	V_Len=V_DataLen;
#if 0
	if((C_Msg_Display!=(V_WR_Mes&0x7F))&&((DT_E23_En==V_DT_Type)||(DT_E23_En_Clear==V_DT_Type)))  /*判断是否为类似显示模块读，电量类--特殊数据--长度需单独处理,不支持显示类，数据块读*/
	{
		PF_CopyDataBytes(&PV_Data[1],P_Data,(uchar8)V_Len);            /*读6+2数据*/
	}
	else
	{
		PF_CopyDataBytes(&PV_Data[0],P_Data,(uchar8)V_Len);
	}
#endif

	PF_CopyDataBytes(&PV_Data[0],P_Data,(uchar8)V_Len);

	return V_Return_Flag;
}

/*********************************************************************************
函数原型：uchar8 SF_ReadE21(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data,uchar8 V_DT_Type,uchar8 V_WR_Mes)
功能描述：读E21处数据，根据Type数据存储类型，判断数据格式
输入参数：
		ushort16 V_E2Addr：读数据E2地址；
		ushort16 V_DataLen：读数据长度
		uchar8 V_DT_Type：数据类型
		uchar8 V_WR_Mes:读数据消息号，用于区分是通用读，还是显示读。当为通用读时消息号为0，显示读时为显示Num号
输出参数：
		uchar8 *P_Data：读数据缓存
返回参数：C_OK、C_IICError、C_CRCError、C_CrcErr_DataZero；
功能说明：
调用机制：
备     注：显示读电量类数据数据长度已经为6+4，其他模块读电量类数据为6+2，数据长度需特殊处理
*********************************************************************************/
uchar8 SF_ReadE21(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 *P_Data,uchar8 V_DT_Type,uchar8 V_WR_Mes)
{
	ushort16 V_Len;
	uchar8 PV_Data[C_RAM_Max];
	uchar8 V_Return_Flag;
#if 0		/*原来645数据长度比698数据长度小1字节，数据层按照645长度存储（如切换时间、节假日参数没有20），这里加1字节判断是为了能顺利通过长度合法性判断*/
	if( ( C_RAM_Max < (V_DataLen + 1) ) || ( V_DataLen > 255 ) )
#endif
	if( ( C_RAM_Max < V_DataLen ) || ( V_DataLen > 255 ) )
	{
		if(_DEBUG)
		{
			/**/
		}
		return C_DataLenError;
	}

#if 0	/*此处698已不使用*/
	if((C_Msg_Display!=(V_WR_Mes&0x7F))&&(DT_E21_En==V_DT_Type))                   /*判断是否为类似显示模块读，电量类--特殊数据--长度需单独处理,不支持显示类，数据块读*/
	{
		V_Len=V_DataLen+1;                   /*645数据长度+1*/
	}
	else
	{
		V_Len=V_DataLen;
	}
#endif

	V_Len=V_DataLen;
	V_Return_Flag=InF_ReadE2(V_E2Addr,&PV_Data[0],V_Len);

#if 0	/*此处698已不使用*/
	if((C_Msg_Display!=(V_WR_Mes&0x7F))&&(DT_E21_En==V_DT_Type))   /*通信读，数据调整*/
	{
		for(V_i=0;V_i<V_DataLen;V_i++)
		{
			if(V_i>=4)   /*调整6+2,主要是年结算用电量*/
			{
				PV_Data[V_i]=PV_Data[V_i+1];
			}
		}
	}
#endif

	V_Len=V_DataLen;
	PF_CopyDataBytes(&PV_Data[0],P_Data,(uchar8)V_Len);

	return V_Return_Flag;
}
/*********************************************************************************
函数原型：uchar8 SF_ReadFlash_Data(uchar8 *P_Data,ushort16 V_Data_Length,ulong32 Str_3TableAddr,ulong32 V_Data_Id,
									ushort16 V_3cTable_Line,uchar8 V_Type,uchar8 V_WR_Mes)
功能描述：读Flash数据
输入参数：
		uchar8 V_Data_Length：读数据具体长度；
		ulong32 Str_3TableAddr：对应3级表格首地址；
		ulong32 V_Data_Id：DI0-DI3数据标识；
		ushort16 V_3cTable_Line：要操作3c级表格行号；
		uchar8 V_Type:数据存储类型
		uchar8 V_MesNum:读数据消息号，用于区分是通用读，还是显示读。当为通用读时消息号为0，显示读时为显示Num号
输出参数：uchar8 *P_Data:读数据缓存；
返回参数：C_OK、C_SPIError,C_IICError、C_IDError、C_NoAccess；
功能说明：
调用机制：
备     注：
*********************************************************************************/
uchar8 SF_ReadFlash_Data(uchar8 *P_Data,ushort16 V_Data_Length,ulong32 Str_3TableAddr,ulong32 V_Data_Id,ushort16 V_3cTable_Line,uchar8 V_Type,uchar8 V_WR_Mes)
{
	uchar8 P_Dgree[CLAll_Loss_Vol_Degree];
	ushort16 V_E2Addr,V_OffAddr;
	ulong32 V_Dgree;
	Str_4Table *PStr_4TableAddr=NULL;
	ulong32 P_FlashAddr1[2];
	uchar8 V_Return_Flag,V_DI[4];
	ushort16 V_i;

	Str_3cTable Str_3cTableAddr;
	Str_3cTable *PStr_3cTableAddr=NULL;

	Str_3dEventTable Str_3dEventTableAddr;
	Str_3dEventTable *PStr_3dEventTableAddr=NULL;

	if(DT_Flash_698EventTab!=V_Type)	/*双协议之645事件记录*/
	{
		if(V_3cTable_Line>=Str_3cTable_Flash_Len)
		{
			return C_AbnormalError;/*正常不存在*/
		}

		PStr_3cTableAddr=(Str_3cTable *)Str_3TableAddr;
		Str_3cTableAddr=PStr_3cTableAddr[V_3cTable_Line];
		V_E2Addr=Str_3cTableAddr.V_Num_E2BakeUp1Addr;    /*取Flash记录次数E2地址*/
	}
	else	/*698事件记录*/
	{
		if(V_3cTable_Line>=Str_3dTable_Flash_Len)
		{
			return C_AbnormalError;/*正常不存在*/
		}

		PStr_3dEventTableAddr=(Str_3dEventTable *)Str_3TableAddr;
		Str_3dEventTableAddr=PStr_3dEventTableAddr[V_3cTable_Line];
		V_E2Addr=Str_3dEventTableAddr.V_Num_E2BakeUp1Addr;    /*取Flash记录次数E2地址*/
	}

	V_OffAddr=0x0000;
#if 0
	if((V_Data_Id&0xFFFF0000)==(CRec_Meter_Degree&0xFFFF0000))		/*校表记录，发生次数*/
	{
		V_Return_Flag=SF_ReadE2Three(V_E2Addr,3,&P_Dgree[0]);
		P_Dgree[3]=0;
	}
	else
	{
		if(V_E2Addr == E2Addr_Program_Degree_645)
		{
			V_Return_Flag=SF_ReadE2Three(V_E2Addr,CLProgram_Degree_645,&P_Dgree[0]);
			P_Dgree[3]=0;
		}
		else
		{
#endif
			V_Return_Flag=SF_ReadE2Three(V_E2Addr,CLAll_Loss_Vol_Degree,&P_Dgree[0]);
#if 0
		}
	}
#endif
	if(C_OK!=V_Return_Flag)
	{
		return V_Return_Flag;
	}

	PF_Buffer4ToUlong32(&P_Dgree[0],&V_Dgree,CLAll_Loss_Vol_Degree);

	PF_Ulong32ToBuffer4(&V_DI[0],&V_Data_Id,4);

	if(DT_Flash_DI04==V_Type)    /*④Flash，带次数数据，DI0低4位表示次数，高4位表示不同标识码(查询4级表用)*/
	{
		V_DI[0]=V_DI[0]&0x0F;
	}

	if(0==V_DI[0])               /*抄读次数≤当前记录总次数，且抄读次数＞0*/
	{
		return C_IDError;
	}

	if(V_DI[0]>V_Dgree)          /*抄读数据返回全零*/
	{
		for(V_i=0;V_i<V_Data_Length;V_i++)
		{
			*(P_Data+V_i)=0x00;
		}
		return C_OK;
	}

	V_Dgree=V_Dgree-V_DI[0]+1;      /*读上N次数据，即查找当前(n-N+1)次地址*/

	if(DT_Flash_698EventTab!=V_Type)
	{
		SF_GetFlashAddr(V_Dgree,Str_3cTableAddr.V_StaFlashAddr,Str_3cTableAddr.V_DataToalLen,Str_3cTableAddr.V_EndFlashAddr,&P_FlashAddr1[0]);   /*获取当前数据Flash页地址及页内地址*/
	}
	else/*在2级表查询中，已计算带关联OAD列表事件长度*/
	{
		SF_GetFlashAddr(V_Dgree,Str_3dEventTableAddr.V_StaFlashAddr,V_Data_Length,Str_3dEventTableAddr.V_EndFlashAddr,&P_FlashAddr1[0]);   /*获取当前数据Flash页地址及页内地址*/
	}

	if(DT_Flash_698EventTab!=V_Type)
	{
		PStr_4TableAddr=(Str_4Table *)(Str_3cTableAddr.PStr_4TableAddr);          /*取4级表地址*/
		if(0xFFFFFFFF!=((ulong32)PStr_4TableAddr))                             /*分项标识码*/
		{
			V_OffAddr=SF_GetOffAddr(PStr_4TableAddr,V_Data_Id,V_Type,Str_3cTableAddr.V_Str_4TableLen);         /*查4级表，取分项偏移地址*/
			if(0xFFFF==V_OffAddr)   /*查找出错*/
			{
				return C_AbnormalError;    /*正常理论情况下，不会出现*/
			}
		}
	}

	P_FlashAddr1[0]=P_FlashAddr1[0]+P_FlashAddr1[1]+V_OffAddr;                /*取数据Flash绝对地址*/
	if(P_FlashAddr1[0]>C_Flash_Max_Addr)	                                    /*Flash地址错误，理论不存在*/
	{
		return C_AbnormalError;
	}

	if(C_Msg_Display==(V_WR_Mes&0x7F))
	{
		InF_FlashChipSelect();
		InF_ReadFlash(P_FlashAddr1[0],P_Data,V_Data_Length);
	}
	else
	{
		InF_FlashChipSelect();
		InF_ReadFlash(P_FlashAddr1[0],P_Data,V_Data_Length);
	}
	return V_Return_Flag;
}
/*********************************************************************************
函数原型：uchar8 SF_Re_RAM_Data(uchar8 *P_RamAddr,ushort16 V_DataLen,uchar8 *P_Data,uchar8 V_DT_Type,uchar8 V_DI0)
功能描述：读RAM数据，不带CRC
输入参数：
		uchar8 *P_RamAddr：读数据RAM地址；
		ushort16 V_DataLen：读数据长度
		uchar8 V_DT_Type：读数据类型
		uchar8 V_DI0:数据标示DI0，用于读时间格式区别判断
输出参数：uchar8 *P_Data：读数据缓存
返回参数：C_OK；
功能说明：
调用机制：
备     注：
*********************************************************************************/
uchar8 SF_Re_RAM_Data(uchar8 *P_RamAddr,ushort16 V_DataLen,uchar8 *P_Data,uchar8 V_DT_Type,uchar8 V_DI0)
{
	ushort16 V_i;
	uchar8 V_PowerState;
	uchar8 V_Temp[CLDate_Week_Time];	/*ssmmhhwwDDMMYY格式*/

	if(DT_RAM_Time_Data==V_DT_Type)          /*⑩RAM不带CRC，读数据时先判断掉电标志。*/
	{
		/*增加掉电判断,有电，直接读内部RAM时间，没电读调度时钟接口函数，刷新数据层*/
		V_PowerState=InF_ReadPowerState();     /*获取当前状态*/
		if(C_PowerOn!=V_PowerState)
		{
			InF_ReadRTC(V_Temp, CLDate_Week_Time);
			PF_Data_Week_Time_BCDtoData_Time_s_HEX(V_Temp, GV_Date_Time);
		}

		switch(V_DI0)
		{
			case 0x01:    /*YYMMDDWW反*/
			{
				P_Data[0]=PF_Cal_Week_698(&GV_Date_Time[3]);/*YYMMDD反，计算周次*/

				for(V_i=1;V_i<V_DataLen;V_i++)
				{
					*(P_Data+V_i)=GV_Date_Time[V_i+2];
				}
			}break;

			case 0x02:    /*hhmmss反*/
			case 0x00:    /*YYYYMMDDhhmmss反*/
			case 0xFD:    /*YYMMDDhhmmss反*/
			{
				for(V_i=0;V_i<V_DataLen;V_i++)
				{
					*(P_Data+V_i)=GV_Date_Time[V_i];
				}
			}break;

			default:
				return C_IDError;
		}
	}
	else
	{
		for(V_i=0;V_i<V_DataLen;V_i++)
		{
			*(P_Data+V_i)=*(P_RamAddr+V_i);
		}
	}

	return C_OK;
}
/*********************************************************************************
函数原型：uchar8 SF_Re_RAMCRC_Data(uchar8 *P_RamAddr,ushort16 V_DataLen,uchar8 *P_Data)
功能描述：读RAM数据，带CRC
输入参数：
		uchar8 *P_RamAddr：读数据RAM地址；
		ushort16 V_DataLen：读数据长度
输出参数：uchar8 *P_Data：读数据缓存
返回参数：C_OK、C_CRCError、C_CrcErr_DataZero；
功能说明：
调用机制：
备     注：C_CrcErr_DataZero时，内部判断数据是否为全零，不为全零则返回C_CRCError。不管数据对错，都返回数据
*********************************************************************************/
uchar8 SF_Re_RAMCRC_Data(uchar8 *P_RamAddr,ushort16 V_DataLen,uchar8 *P_Data)
{
	ushort16 V_i,V_Len;
	uchar8 V_CRC_Flag;
	uchar8 PV_Data[C_RAM_Max];

	if((C_RAM_Max<(V_DataLen+C_CRCLen2))||(V_DataLen>255))
	{
		return C_DataLenError;
	}

	V_Len=V_DataLen+C_CRCLen2;                            /*增加CRC*/

	for(V_i=0;V_i<V_Len;V_i++)
	{
		PV_Data[V_i]=*(P_RamAddr+V_i);
	}

	V_CRC_Flag=PF_Check_CRC(&PV_Data[0],V_Len);

	V_Len=V_Len-C_CRCLen2;                                /*去掉CRC*/
	PF_CopyDataBytes(&PV_Data[0],P_Data,(uchar8)V_Len);

	if(C_OK==V_CRC_Flag)
	{
		return C_OK;
	}
	else
	{
		if(C_CrcErr_DataZero==V_CRC_Flag)        /*CRC错误但数据为全零*/
		{
			for(V_i=0;V_i<V_Len;V_i++)
			{
				if(0!=PV_Data[V_i])
				{
					break;
				}
			}

			if(V_i==V_Len)                        /*数据正确*/
			{
				return C_CrcErr_DataZero;         /*返回CRC错误，但数据为全零*/
			}
			else
			{
				return C_CRCError;
			}
		}
		else
		{
			return C_CRCError;
		}
	}
}
/*********************************************************************************
函数原型：uchar8 SF_GetMinFreezePro_E2andFlashAddr(uchar8 V_ProNum,ulong32* P_FlashStAddr_LoadProfile,
			ulong32* P_FlashEndAddr_LoadProfile,ushort16* P_E2Addr_LoadP_Flash_Ear,ushort16* P_E2Addr_LoadP_Flash_Late)
功能描述：获取分钟冻结方案号对应的记录块，起始、结束地址
输入参数：uchar8 V_ProNum:方案号0--7
输出参数：
		ulong32* P_FlashStAddr_LoadProfile:返回该冻结方案，起始地址
		ulong32* P_FlashEndAddr_LoadProfile:返回该冻结方案，结束地址
		ushort16* P_E2Addr_LoadP_Flash_Ear:返回最早1次记录Flash地址，存E2地址
		ushort16* P_E2Addr_LoadP_Flash_Late:最近1次记录Flash地址，存E2地址
返回参数：C_OK、C_SPIError、C_DataLenError、C_NoAccess、C_Error(数据格式错)、C_SafeFlagError、C_IICError；
功能说明：
调用机制：
备     注：
*********************************************************************************/
uchar8 SF_GetMinFreezePro_E2andFlashAddr(uchar8 V_ProNum,ulong32 *P_FlashStAddr_LoadProfile,ulong32 *P_FlashEndAddr_LoadProfile,ushort16 *P_E2Addr_LoadP_Flash_Ear,ushort16 *P_E2Addr_LoadP_Flash_Late)
{
	uchar8 V_Return_Flag=C_Error;
	uchar8 Vu_FlashAddr[64]={0xFF};

	if(V_ProNum>7)	/*方案号*/
	{
		return V_Return_Flag;
	}

	V_Return_Flag=SF_ReadE2Three(E2Addr_Min_Free_FlashAddr_Allo,64,&Vu_FlashAddr[0]);	/*获取不同方案分配起始、结束地址*/
	if(C_OK==V_Return_Flag)
	{
		PF_Buffer4ToUlong32(&Vu_FlashAddr[V_ProNum*8],P_FlashStAddr_LoadProfile,4);
		PF_Buffer4ToUlong32(&Vu_FlashAddr[V_ProNum*8+4],P_FlashEndAddr_LoadProfile,4);
	}
	*P_E2Addr_LoadP_Flash_Ear=E2Addr_Min_Free_Flash_Ear1+V_ProNum*12;
	*P_E2Addr_LoadP_Flash_Late=*P_E2Addr_LoadP_Flash_Ear+6;
	return V_Return_Flag;
}
/*********************************************************************************
函数原型：uchar8 SF_Write698FreezeData(uchar8 V_DI2,uchar8 Message_Num,uchar8 *P_Data,ushort16 V_Data_Length)
功能描述：写冻结记录
输入参数：
		uchar8 V_DI2:DI2表示某类冻结数据；分钟冻结高3位表示方案号
		uchar8 Msg_Num:消息号，用于判断是否有写权限；
		uchar8 *P_Data：数据所放缓存；
		ushort16 V_Data_Length：所写数据长度；
输出参数：无
返回参数：C_OK、C_SPIError、C_DataLenError、C_NoAccess、C_Error(数据格式错)、C_SafeFlagError、C_IICError；
功能说明：
调用机制：
备     注：注意写入数据长度
*********************************************************************************/
uchar8 SF_Write698FreezeData(uchar8 V_DI2Temp, uchar8 Message_Num, uchar8 *P_Data, ushort16 V_Data_Length)
{
	uchar8 V_i,V_Mode;
	ulong32 V_WR_FlashAddr[2];
	uchar8 V_Return_Flag;
	uchar8 V_FlashAddr8[4],V_DI2;
	ulong32 V_FlashAddrEar;
	ushort16 V_Len;
	ushort16 V_E2Addr_LoadP_Flash_Late,V_E2Addr_LoadP_Flash_Ear;
	ulong32 V_FlashStAddr_LoadProfile,V_FlashEndAddr_LoadProfile;
	ulong32 V_Flash_Page;

	GV_D_SafeFlag=C_Clear_SafeFlag;

	V_DI2=(V_DI2Temp&0x1F);		/*去除方案号*/

	if(C_Msg_Freeze!=Message_Num)
	{
		return C_NoAccess;
	}

	GV_D_SafeFlag=C_W_SafeFlag_1|GV_D_SafeFlag;

	V_Len=SF_JudgeWriteDataLen(V_DI2Temp);	                     /*计算写入数据总长度*/
	if((V_Data_Length!=V_Len)||(0==V_Len))
	{
		return C_DataLenError;
	}

	GV_D_SafeFlag=C_W_SafeFlag_2|GV_D_SafeFlag;

	for(V_i=0;V_i<Str_698FreezeDataTable_Len;V_i++)
	{
		if(V_DI2==Str_698FreezeDataTable[V_i].V_DI2)
		{
			break;
		}
	}

	if(V_i>=Str_698FreezeDataTable_Len)
	{
		return C_Error;
	}

	V_E2Addr_LoadP_Flash_Late=Str_698FreezeDataTable[V_i].V_E2AddrLate;
	V_E2Addr_LoadP_Flash_Ear=Str_698FreezeDataTable[V_i].V_E2AddrEar;
	V_FlashStAddr_LoadProfile=Str_698FreezeDataTable[V_i].V_StaFlashAddr;
	V_FlashEndAddr_LoadProfile=Str_698FreezeDataTable[V_i].V_EndFlashAddr;

	if(V_DI2==(uchar8)((C_RelatedOAD_Min&0x00FF0000)>>16))/*分钟冻结,根据方案号获取上述E2及Flash地址*/
	{
		V_Return_Flag=SF_GetMinFreezePro_E2andFlashAddr((V_DI2Temp>>5),&V_FlashStAddr_LoadProfile,&V_FlashEndAddr_LoadProfile,&V_E2Addr_LoadP_Flash_Ear,&V_E2Addr_LoadP_Flash_Late);/*根据分钟冻结方案号，获取该方案最近、最早记录E2地址及该方案起始、结束Flash地址*/
		if(C_OK!=V_Return_Flag)
		{
			return V_Return_Flag;
		}
	}

	GV_D_SafeFlag=C_W_SafeFlag_3|GV_D_SafeFlag;

	SF_GetCurrLoadProfileFlashAddr(V_Len,&V_WR_FlashAddr[0],V_E2Addr_LoadP_Flash_Late,V_E2Addr_LoadP_Flash_Ear,V_FlashStAddr_LoadProfile,V_FlashEndAddr_LoadProfile);     /*计算当前要写入数据Flash地址,目前修改为冻结记录地址V_WR_FlashAddr[1]*/
	if(V_WR_FlashAddr[1]==0xFFFFFFFF)/*异常*/
	{
		GV_D_SafeFlag=C_Clear_SafeFlag;
		return C_Error;
	}

	if(C_W_SafeFlag!=GV_D_SafeFlag)
	{
		GV_D_SafeFlag=C_Clear_SafeFlag;
		return C_SafeFlagError;
	}

	V_Flash_Page=V_WR_FlashAddr[0]%C_OneFlashPage;            /*判断写入数据Flash地址是否为每页首地址,是否跨页*/
	if(0==V_Flash_Page)/*该页Flash第一次写入，写68记录标志*/
	{
		V_Mode=C_Flash_Empty68;
		V_Return_Flag=SF_WriteFlash(V_WR_FlashAddr[0],&V_Mode,1,1);               /**写入记录模式字*/
		if(C_OK!=V_Return_Flag)
		{
			GV_D_SafeFlag=C_Clear_SafeFlag;
			return V_Return_Flag;
		}
	}

	V_Return_Flag=SF_WriteFlash(V_WR_FlashAddr[1],&P_Data[0],V_Len,1);       /**写入记录数据*/
	if(C_OK!=V_Return_Flag)
	{
		GV_D_SafeFlag=C_Clear_SafeFlag;
		return V_Return_Flag;
	}

	V_Flash_Page=(V_WR_FlashAddr[0]%C_OneFlashPage);            /*判断写入数据Flash地址是否为每页首地址,是否跨页*/

	V_Return_Flag = SF_ReadE2Three(V_E2Addr_LoadP_Flash_Ear,4,&V_FlashAddr8[0]);         /*取最早1条记录Flash地址*/
	if(C_OK!=V_Return_Flag)
	{
		GV_D_SafeFlag=C_Clear_SafeFlag;
		return V_Return_Flag;
	}

	PF_Buffer4ToUlong32(&V_FlashAddr8[0],&V_FlashAddrEar,4);

	if((V_FlashStAddr_LoadProfile==V_WR_FlashAddr[0])&&(V_FlashStAddr_LoadProfile==V_FlashAddrEar))            /*负荷记录Flash首页*/
	{
		PF_Ulong32ToBuffer4(&V_FlashAddr8[0],&V_WR_FlashAddr[1],4);   /*最早记录第1次写入*/
		V_Return_Flag=SF_WriteE2Three(V_E2Addr_LoadP_Flash_Ear,4,&V_FlashAddr8[0]);   /*调整最早记录Flash地址存E2*/
	}

	if(0==V_Flash_Page)   /*跨页，调整最近记录Flash*/
	{
		PF_Ulong32ToBuffer4(&V_FlashAddr8[0],&V_WR_FlashAddr[0],4);
		V_Return_Flag=SF_WriteE2Three(V_E2Addr_LoadP_Flash_Late,4,&V_FlashAddr8[0]);   /*调整最近记录Flash地址存E2*/
		SF_EarlistLoadProfileFlashAddrAdjust(V_E2Addr_LoadP_Flash_Late,V_E2Addr_LoadP_Flash_Ear,V_FlashStAddr_LoadProfile,V_FlashEndAddr_LoadProfile);                 /*Flash记录，最早记录页调整函数*/
	}

	GV_D_SafeFlag=C_Clear_SafeFlag;
	return V_Return_Flag;
}
/*********************************************************************************
函数原型：ushort16 SF_GetMinFreezeNum_OADTab(uchar8 V_ProNum,uchar8 *P_DataOAD_NumTab,ushort16 V_OADTabLen_T)
功能描述：获取分钟冻结方案号对应的OAD关联列表
输入参数：
		*uchar8 V_ProNum:分钟冻结某类方案号0--7
		uchar8 *P_DataOAD_NumTab:输入为分钟冻结OAD关联列表
		ushort16 V_OADTabLen_T:分钟冻结OAD关联列表总长度
输出参数：uchar8 *P_DataOAD_NumTab:输出为分钟冻结方案号对应的OAD关联列表；
返回参数：分钟冻结方案号对应的关联列表OAD个数，异常返回0xFFFF
功能说明：
调用机制：
备     注：
*********************************************************************************/
ushort16 SF_GetMinFreezeNum_OADTab(uchar8 V_ProNum,uchar8 *P_Data,ushort16 V_DataLen)
{
	ushort16 V_MinOADTabLen_T=0xFFFF;
	uchar8 V_j,V_k,V_m,V_Num;
	ushort16 V_Cyc16[8]={0xFFFF},V_OADOrder16;

	if(V_ProNum>7)
	{
		return V_MinOADTabLen_T;
	}

	V_Num=SF_GetMinFreezeTolNum(P_Data,V_DataLen,&V_Cyc16[0]);/*获取总方案数及对应的不同方案周期*/
	if(V_Num>8)/*异常*/
	{
		return V_MinOADTabLen_T;
	}

	V_j=V_DataLen/C_698Free_OADTabDataType;/*OAD列表个数*/

	V_m=0;
	for(V_k=0;V_k<V_j;V_k++)
	{
		PF_Buffer2ToUshort16(&P_Data[C_698Free_OADTabDataType*V_k+2],&V_OADOrder16);/*获取后续OAD周期*/
		if(V_Cyc16[V_ProNum]==V_OADOrder16)/*周期相等,则认为相同方案*/
		{
			PF_CopyDataBytes(&P_Data[C_698Free_OADTabDataType*V_k],&P_Data[C_698Free_OADTabDataType*V_m],C_698Free_OADTabDataType);
			V_m++;
		}
	}

	V_MinOADTabLen_T=V_m;

	return V_MinOADTabLen_T;
}

/*********************************************************************************
函数原型：ushort16 SF_JudgeWriteDataLen(uchar8 V_DI2)
功能描述：根据某类冻结，结合该冻OAD结序号表，计算整个记录块数据长度(包括记录序号)
输入参数：uchar8 V_DI2:某类冻结；当为分钟冻结时，高3位表示不同方案号
输出参数：ushort16 V_Data_Length：该类冻结数据长度；
返回参数：无；
功能说明：
调用机制：
备     注：异常返回0
*********************************************************************************/
ushort16 SF_JudgeWriteDataLen(uchar8 V_DI2Temp)
{
	ushort16 V_Data_Length;
	uchar8 P_DataOAD_NumTab[C_698Free_OADTabLen];
	uchar8 P_OADTabLen_T[CLI_Free_OADTabLen_T];
	ushort16 V_Order,V_OADTabLen_T,V_OADOrder16,V_i;
	uchar8 V_Return_Flag,V_DI2;
	Str_3aTable V_Str_3aTable;

	V_Data_Length=0;
	V_DI2=(V_DI2Temp&0x1F);/*去除方案号*/

	for(V_i=0;V_i<Str_698FreezeDataTable_Len;V_i++)
	{
		if(V_DI2==Str_698FreezeDataTable[V_i].V_DI2)
		{
			break;
		}
	}

	if(V_i<Str_698FreezeDataTable_Len)
	{
		V_Order=Str_698FreezeDataTable[V_i].V_LineNumLen_T;/*698冻结长度、周期数据项所在Str_3aTable行号*/
		if(V_Order >= Str_3aTable_E23RAM_Len)
		{
			return V_Data_Length;/*异常*/
		}

		V_Str_3aTable=Str_3aTable_E23RAM[V_Order];
		V_Return_Flag=SF_Re_E23_RAM_Data698(&V_Str_3aTable,CLI_Free_OADTabLen_T,&P_OADTabLen_T[0]);
		if(C_OK==V_Return_Flag)
		{
			V_OADTabLen_T=P_OADTabLen_T[0];
			V_OADTabLen_T=V_OADTabLen_T*C_698Free_OADTabDataType;/*序号表每个OAD序号C_698Free_OADTabDataType个字节,目前6字节。2字节序号+2字节冻结周期+2字节存储深度*/
			if(V_OADTabLen_T >= C_698Free_OADTabLen)		/*数据长度安全性判断*/
			{
				return V_Data_Length;	/*异常*/
			}

			V_Order=Str_698FreezeDataTable[V_i].V_LineNumTab;/*698冻结序号表所在Str_3aTable行号*/
			if(V_Order >= Str_3aTable_E23RAM_Len)
			{
				return V_Data_Length;	/*异常*/
			}

			V_Str_3aTable=Str_3aTable_E23RAM[V_Order];
			V_Return_Flag=SF_Re_E23_RAM_Data698(&V_Str_3aTable,V_OADTabLen_T,&P_DataOAD_NumTab[0]);
			if(C_OK!=V_Return_Flag)
			{
				return V_Data_Length;	/*异常*/
			}

			if(V_DI2==(uchar8)((C_RelatedOAD_Min&0x00FF0000)>>16))/*分钟冻结*/
			{
				V_OADTabLen_T=SF_GetMinFreezeNum_OADTab((V_DI2Temp>>5),&P_DataOAD_NumTab[0],V_OADTabLen_T);/*获取分钟冻结方案号，对应的OAD关联列表及关联OAD个数*/
				if(0xFFFF==V_OADTabLen_T)
				{
					return V_Data_Length;	/*异常*/
				}
			}
			else
			{
				V_OADTabLen_T=V_OADTabLen_T/C_698Free_OADTabDataType;
			}

			V_Data_Length=C_698FreeData_SequenceLen4+C_698FreeData_DateLen6;/*698冻结数据序号长度+6 YMDhms*/
			for(V_i=0;V_i<V_OADTabLen_T;V_i++)
			{
				PF_Buffer2ToUshort16(&P_DataOAD_NumTab[C_698Free_OADTabDataType*V_i],&V_OADOrder16);
				V_OADOrder16 &= 0x1FFF;
				if(V_OADOrder16 >= Str_FrozenConvert_Table_Len)
				{
					return 0;	/*异常*/
				}
				V_Data_Length=V_Data_Length+Str_FrozenConvert_Table[V_OADOrder16].V_uc645Length;
			}
		}
	}

	return V_Data_Length;
}

/*********************************************************************************
函数原型：void SF_GetCurrLoadProfileFlashAddr(ushort16 V_Len,ulong32 *V_W_FlashAddr,ushort16 V_E2Addr_LoadP_Flash_Late,
					ushort16 V_E2Addr_LoadP_Flash_Ear,ulong32 V_FlashStAddr_LoadProfile,ulong32 V_FlashEndAddr_LoadProfile)
功能描述：计算当前要写入Flash数据地址
输入参数：
		ushort16 V_Len：要写入负荷记录块长度；
		ushort16 V_E2Addr_LoadP_Flash_Late:要操作记录最近1次记录Flash地址，存E2地址
		ushort16 V_E2Addr_LoadP_Flash_Ear:要操作记录最早1次记录Flash地址，存E2地址
		ulong32 V_FlashStAddr_LoadProfile:要操作记录Flash起始地址
		ulong32 V_FlashEndAddr_LoadProfile:要操作记录Flash结束地址
输出参数：
ulong32 *V_W_FlashAddr：当前要写入记录数据Flash地址，V_W_FlashAddr[1]：为记录数据地址，V_W_FlashAddr[0]：当该页为第1次写入时，
		V_W_FlashAddr[0]：为该页地址，非第一次写入时，则同V_W_FlashAddr[1]，

返回参数：无；
功能说明：
调用机制：
备     注：当V_W_FlashAddr[0]：为全FF时，说明操作异常
*********************************************************************************/
void SF_GetCurrLoadProfileFlashAddr(ushort16 V_Len,ulong32 *V_W_FlashAddr,ushort16 V_E2Addr_LoadP_Flash_Late,ushort16 V_E2Addr_LoadP_Flash_Ear,ulong32 V_FlashStAddr_LoadProfile,ulong32 V_FlashEndAddr_LoadProfile)
{
	uchar8 V_i;
	ulong32 V_FlashAddr32,V_FlashAddr;
	uchar8 V_FlashAddr8[4];
	uchar8 V_Mode[C_LoadProfile_RevMode],V_Date[C_698FreeData_DateLen6];
	uchar8 V_ucReturn;
	ulong32 V_FlashAddr32Temp;

	V_W_FlashAddr[1]=0xFFFFFFFF;
	V_W_FlashAddr[0]=0xFFFFFFFF;

	V_ucReturn = SF_ReadE2Three(V_E2Addr_LoadP_Flash_Late,4,&V_FlashAddr8[0]);        /*取最近1条记录Flash页地址*/
	if(V_ucReturn != C_OK)
	{
		return;
	}

	PF_Buffer4ToUlong32(&V_FlashAddr8[0],&V_FlashAddr32,4);
	V_FlashAddr32&=0xFFFFF000;             /*页地址转化，增加容错性*/

	V_ucReturn = SF_ReadE2Three(V_E2Addr_LoadP_Flash_Ear,4,&V_FlashAddr8[0]);        /*取最早1条记录Flash页地址*/
	if(V_ucReturn != C_OK)
	{
		return;
	}

	PF_Buffer4ToUlong32(&V_FlashAddr8[0],&V_FlashAddr,4);

	if((V_FlashStAddr_LoadProfile==V_FlashAddr)&&(V_FlashAddr32==V_FlashAddr)) /*第1次记录*/
	{
		V_W_FlashAddr[0]=V_FlashStAddr_LoadProfile;
		V_W_FlashAddr[1]=V_FlashStAddr_LoadProfile+C_LoadProfile_RevMode;
		return;
	}

	InF_FlashChipSelect();
	InF_ReadFlash(V_FlashAddr32,&V_Mode[0],C_LoadProfile_RevMode);     /*取页首是否有时间调整标志*/
	if(0x68!=V_Mode[C_LoadProfile_RevMode-1]) /*该页有记录写该标志为68，该页记录时间有调整，则写非68标志（同时把无效记录6字节YMDhms写为FF，即底层写0），说明该页记录时间有调整,取下1页*/
	{
		if(V_FlashEndAddr_LoadProfile==V_FlashAddr32)                      /*当前页为记录最后1页,调整为首页*/
		{
			V_W_FlashAddr[0]=V_FlashStAddr_LoadProfile;
			V_W_FlashAddr[1]=V_W_FlashAddr[0]+C_LoadProfile_RevMode;
			return;
		}
		else
		{
			V_W_FlashAddr[0]=V_FlashAddr32+C_OneFlashPage;                /*调整为下1页*/
			V_W_FlashAddr[1]=V_W_FlashAddr[0]+C_LoadProfile_RevMode;
			return;
		}
	}

	V_FlashAddr32Temp=C_LoadProfile_RevMode;      /*最近1条记录该页第1条记录地址*/

	while(V_FlashAddr32Temp<=C_OneFlash_PageNum)/*判断剩余空间是否满足*/
	{
		InF_FlashChipSelect();
		InF_ReadFlash((V_FlashAddr32Temp+V_FlashAddr32),&V_Date[0],C_698FreeData_DateLen6);     /*读取每条记录前6个字节，正常记录为YMDhms*/
		for(V_i=0;V_i<C_698FreeData_DateLen6;V_i++)
		{
			if(0x00!=V_Date[V_i])/*有记录数据*/
			{
				break;
			}
		}

		if(V_i<C_698FreeData_DateLen6)/*有记录数据*/
		{
			V_FlashAddr32Temp=V_FlashAddr32Temp+V_Len;/*取下条记录地址*/
		}
		else/*空记录*/
		{
			if((V_FlashAddr32Temp+V_Len)<=C_OneFlash_PageNum)
			{
				V_W_FlashAddr[1]=V_FlashAddr32Temp+V_FlashAddr32;
				V_W_FlashAddr[0]=V_W_FlashAddr[1];
				return;
			}
			else
			{
				break;
			}
		}
	}

	if(V_FlashEndAddr_LoadProfile==V_FlashAddr32)/*剩余空间不满足，调整为下1页，当前页为负荷记录最后1页,调整为首页*/
	{
		V_W_FlashAddr[0]=V_FlashStAddr_LoadProfile;
		V_W_FlashAddr[1]=V_W_FlashAddr[0]+C_LoadProfile_RevMode;
		return;
	}
	else
	{
		V_W_FlashAddr[0]=V_FlashAddr32+C_OneFlashPage;                /*调整为下1页*/
		V_W_FlashAddr[1]=V_W_FlashAddr[0]+C_LoadProfile_RevMode;
		return;
	}
}

/*********************************************************************************
函数原型：void SF_EarlistLoadProfileFlashAddrAdjust(ushort16 V_E2Addr_LoadP_Flash_Late,ushort16 V_E2Addr_LoadP_Flash_Ear,
													ulong32 V_FlashStAddr_LoadProfile,ulong32 V_FlashEndAddr_LoadProfile);
功能描述：调整最早负荷记录Flash页地址
输入参数：
ushort16 V_E2Addr_LoadP_Flash_Late:要操作记录最近1次记录Flash地址，存E2地址
ushort16 V_E2Addr_LoadP_Flash_Ear:要操作记录最早1次记录Flash地址，存E2地址
ulong32 V_FlashStAddr_LoadProfile:要操作记录Flash起始地址
ulong32 V_FlashEndAddr_LoadProfile:要操作记录Flash结束地址
输出参数：无
返回参数：无；
功能说明：
调用机制：
备     注：调用前，已有安全标志。在巡航程序中，负荷记录可以直接判断擦除
*********************************************************************************/
void SF_EarlistLoadProfileFlashAddrAdjust(ushort16 V_E2Addr_LoadP_Flash_Late,ushort16 V_E2Addr_LoadP_Flash_Ear,ulong32 V_FlashStAddr_LoadProfile,ulong32 V_FlashEndAddr_LoadProfile)
{
	ulong32 V_FlashAddrLate,V_FlashAddrEar,V_FlashAddr;
	uchar8 V_FlashAddr8[4];
	uchar8 V_ucReturn;

	V_ucReturn = SF_ReadE2Three(V_E2Addr_LoadP_Flash_Late,4,&V_FlashAddr8[0]);        /*取最近1条记录Flash页地址*/
	if(V_ucReturn != C_OK)
	{
		return;
	}

	PF_Buffer4ToUlong32(&V_FlashAddr8[0],&V_FlashAddrLate,4);
	V_FlashAddrLate&=0xFFFFF000;             /*页地址转化，增加容错性*/

	V_ucReturn = SF_ReadE2Three(V_E2Addr_LoadP_Flash_Ear,4,&V_FlashAddr8[0]);         /*取最早1条记录Flash地址*/
	if(V_ucReturn != C_OK)
	{
		return;
	}

	PF_Buffer4ToUlong32(&V_FlashAddr8[0],&V_FlashAddrEar,4);
	if(V_FlashEndAddr_LoadProfile==V_FlashAddrLate)
	{
		if(V_FlashStAddr_LoadProfile==(V_FlashAddrEar-C_LoadProfile_RevMode))    /*Flash绝对地址*/                    /*调整最早记录Flash地址*/
		{
			V_FlashAddrEar=V_FlashAddrEar+C_OneFlashPage;
			PF_Ulong32ToBuffer4(&V_FlashAddr8[0],&V_FlashAddrEar,4);
			SF_WriteE2Three(V_E2Addr_LoadP_Flash_Ear,4,&V_FlashAddr8[0]);   /*调整最早记录Flash地址存E2*/
		}
	}
	else
	{
		V_FlashAddr=V_FlashAddrEar-V_FlashAddrLate-C_LoadProfile_RevMode;
		if(C_OneFlashPage==V_FlashAddr)                                 /*正常相差1页，1个循环*/
		{
			if(V_FlashEndAddr_LoadProfile==(V_FlashAddrEar-C_LoadProfile_RevMode))                      /*当前页为记录最后1页,调整为首页*/
			{
				V_FlashAddrEar=V_FlashStAddr_LoadProfile+C_LoadProfile_RevMode;      /*Flash绝对地址*/
			}
			else
			{
				V_FlashAddrEar=V_FlashAddrEar+C_OneFlashPage;      /*调整为下1页，Flash绝对地址*/
			}

			PF_Ulong32ToBuffer4(&V_FlashAddr8[0],&V_FlashAddrEar,4);
			SF_WriteE2Three(V_E2Addr_LoadP_Flash_Ear,4,&V_FlashAddr8[0]);   /*调整最早记录Flash地址存E2*/
		}
	}
}
#if 0
/*********************************************************************************
函数原型：uchar8 InF_Read_Data_For_Dis(ulong32 V_ulData_Id, uchar8 *pV_ucData, ushort16 *pV_usData_Length)
功能描述：读数据层接口函数,专供类似显示模块，如读电量为6+4，通用读数据接口函数，数据长度为默认645长度，6+2；
输入参数：
ulong32 V_ulData_Id ：数据标识码；
uchar8 *pV_ucData ：数据所放缓存；
uchar8 *pV_usData_Length ：作为输入参数时，该参数值为模块所读数据缓存长度最大值，用于数据层判断，所读数据长度，
是否溢出，如溢出则返回数据长度错误。当作为输出参数时，数据层返回所读取数据长度。
输出参数：
ushort16 *pV_usData_Length ：数据层返回所读取数据长度。
uchar8 *pV_ucData:所读数据输出缓存
返回参数：C_OK、C_IICError、C_SPIError、C_DataLenError、C_IDError、C_NoAccess、C_CRCError、C_CrcErr_DataZero；
功能说明：
调用机制：
备     注：注意数据长度,与通用InF_Read_Data函数相比，只有结算电量不同，显示结算电量为4位小数
*********************************************************************************/
uchar8 InF_Read_Data_For_Dis(ulong32 V_ulData_Id, uchar8 *pV_ucData, ushort16 *pV_usData_Length)
{
	uchar8 V_Return_Flag;
	uchar8 V_MesNum;
	ushort16 V_usDataEncode;

	if(SF_Read_698SpecialData(V_ulData_Id, pV_ucData, pV_usData_Length, &V_usDataEncode) == C_OK)
	{
		return C_OK;
	}

	V_MesNum = (C_Read_Data|C_Msg_Display);        /*类似显示读*/
	V_Return_Flag = SF_Read_Data(V_ulData_Id, pV_ucData, pV_usData_Length, V_MesNum, &V_usDataEncode);

	return V_Return_Flag;
}
#endif
/*********************************************************************************
函数原型：void SF_EEAndRAMCheckAndRecover(ushort16 V_E2BakeUp1Addr,uchar8 *V_RamAddr)
功能描述:重要数据：RAM和EE数据CRC校验，RAM数据CRC不正确或与EE数据不一致时，用EE数据恢复RAM
输入参数：V_usE2BakeUp1Addr：EE地址；
P_ucRamAddr:RAM地址
V_ucDataLen:数据长度
输出参数：无
返回参数：无
功能说明：
调用机制：SF_ImportantDataCheckAndRecover调用1）上电初始化2）数据层巡航5s
备     注：重要数据项包括：脉冲常数.
*********************************************************************************/
void SF_EEAndRAMCheckAndRecover(ushort16 V_usE2BakeUp1Addr, uchar8 *P_ucRamAddr, uchar8 V_ucDataLen)
{
	uchar8 V_ucE2DataFlag, V_ucRamDataFlag, V_ucComDataFlag;
	uchar8 PV_E2Data[30];

	if((V_ucDataLen+C_CRCLen2)>30)
	{
		return;
	}

	V_ucE2DataFlag = SF_ReadE2Three_AndCRC(V_usE2BakeUp1Addr, V_ucDataLen, PV_E2Data);
	V_ucRamDataFlag = PF_Check_CRC(P_ucRamAddr, (V_ucDataLen + C_CRCLen2));/*判断RAM CRC*/

	if(V_ucRamDataFlag != C_OK)
	{
		if(V_ucE2DataFlag == C_OK)/*EE数据覆盖RAM*/
		{
			PF_CopyDataBytes(PV_E2Data,P_ucRamAddr,(V_ucDataLen + C_CRCLen2));
		}/*else,EE数据CRC不正确，不处理*/
	}
	else
	{
		if(V_ucE2DataFlag == C_OK)
		{
			V_ucComDataFlag = PF_Campare_Data(P_ucRamAddr,PV_E2Data,V_ucDataLen);
			if(V_ucComDataFlag != C_Equal)
			{
				PF_CopyDataBytes(PV_E2Data,P_ucRamAddr,(V_ucDataLen + C_CRCLen2));
			}/*else,EE数据和RAM数据相同，不处理*/
		}/*else,EE数据CRC不正确，不处理*/
	}
}
/**********************************************************************************
函数原型：void SF_ImportantDataCheckAndRecover(void)
功能描述:重要数据校验及恢复
输入参数：无
输出参数：无
返回参数：无
功能说明：
调用机制：1）上电初始化2）数据层巡航5s
备     注：重要数据项包括：脉冲常数
**********************************************************************************/
void SF_ImportantDataCheckAndRecover(void)
{
	/*脉冲常数*/
	SF_EEAndRAMCheckAndRecover(E2Addr_Pulse_Constant, GV_Pulse_Constant, CLPulse_Constant);
}
/*********************************************************************************
函数原型：void InF_PowerOn_CurrEnergyDeal(void)
功能描述：上电电量处理接口函数,调度调用。数据判断以铁电数据为准
输入参数：无
输出参数：无
返回参数：无
功能说明：
调用机制：调度上电时，电源稳定后调用
备注：读出铁电电量，与RAM判断是否相等，不相等(铁电是实时存储，正常RAM与铁电电能数据相等)，
判断电量是否合理，然后写，每次判断一个电量，判断增量的合理性。
其中剩余金额，透支金额只判断金额大小的合理性，没有判断限值
后考虑上电的安全性，该函数不做RAM更新铁电处理，在20min函数中再做更新E2处理
(目前当前电能直接更新RAM、铁电，不用做20min电能保存处理)，
本处只做当RAM数据CRC不正确或数据异常时，由E2更新RAM.在E2CRC错误时，RAMCRC正确也不更新E2
*********************************************************************************/
void InF_PowerOn_CurrEnergyDeal(void)
{
	uchar8 V_E2DataFlag,V_RamDataFlag,V_i,V_j;
	uchar8 PV_E2Data[C_CurrDataLen5];
	ulong64 V_RamEnData,V_E2EnData;
	ushort16 V_CRC16;
	uchar8 PV_CRC8[C_CRCLen2];
	long64 V_EnDataAdd;
	uchar8 V_DataType;

	GV_D_SafeFlag=C_Clear_SafeFlag;
	V_E2DataFlag=C_CRCError;
	V_RamDataFlag=C_CRCError;

	GV_D_SafeFlag=GV_D_SafeFlag|C_W_SafeFlag_1;

	V_j=C_CurrDataLen5+C_CRCLen2;
	for(V_i=0;V_i<C_CurrEnergy_Len;V_i++)
	{
		V_E2DataFlag=SF_ReadFRAMThree((E2Addr_CurrEnergy_St+V_j*V_i),C_CurrDataLen5,&PV_E2Data[0]);   /*读E2数据,内部判断CRC*/
		V_RamDataFlag=PF_Check_CRC(&GV_CurrEnergyData[V_i][0],(C_CRCLen2+C_CurrDataLen5));          /*判断RAM CRC*/
		if((C_OK==V_RamDataFlag)||(C_CrcErr_DataZero==V_RamDataFlag))
		{
			PF_Buffer8ToUlong64(&GV_CurrEnergyData[V_i][0],&V_RamEnData,C_CurrDataLen5);
		}

		GV_D_SafeFlag=GV_D_SafeFlag|C_W_SafeFlag_2;

		if((C_OK==V_E2DataFlag)||(C_CrcErr_DataZero==V_E2DataFlag))
		{
			PF_Buffer8ToUlong64(&PV_E2Data[0],&V_E2EnData,C_CurrDataLen5);
		}

		GV_D_SafeFlag=GV_D_SafeFlag|C_W_SafeFlag_3;

		if((C_OK==V_E2DataFlag)||(C_CrcErr_DataZero==V_E2DataFlag))   /*E2数据正确*/
		{
			if((C_OK==V_RamDataFlag)||(C_CrcErr_DataZero==V_RamDataFlag))    /*判断电量增量的合理性*/
			{
				V_EnDataAdd=V_RamEnData-V_E2EnData;                           /*电量增量*/
				if(0==V_EnDataAdd)
				{
					continue;                             /*跳出本层循环*/
				}
				else     /*更新数据*/
				{
					if(V_i == C_ChargeBal_offset_InGV)   /*剩余金额,正常E2>=RAM。铁电==RAM数据。CRC数据全零，也认为错误单独判断*/
					{
						V_DataType=SF_AllDataZero_Judge(&GV_CurrEnergyData[V_i][0],(C_CurrDataLen5+C_CRCLen2));/*数据是否为全零判断，包含CRC*/
						if((V_EnDataAdd!=0)||(C_OK==V_DataType))       /*RAM数据异常*/
						{
							V_RamEnData=V_E2EnData;                  /*E2更新RAM电量*/

							if(C_W_SafeFlag!=GV_D_SafeFlag)
							{
								return;
							}

							PF_Ulong64ToBuffer8(&GV_CurrEnergyData[V_i][0],&V_RamEnData,C_CurrDataLen5);
							V_CRC16=PF_Cal_CRC(&GV_CurrEnergyData[V_i][0],C_CurrDataLen5);          /*计算CRC*/
							PF_Ushort16ToBuffer2(&PV_CRC8[0],&V_CRC16);
							GV_CurrEnergyData[V_i][C_CurrDataLen5]=PV_CRC8[0];
							GV_CurrEnergyData[V_i][C_CurrDataLen5+1]=PV_CRC8[1];
						}
					}
					else                           /*电量类数据比较*/
					{
						if(V_RamEnData!=V_E2EnData) /*RAM、铁电电能数据实时刷新，正常RAM与铁电电能数据相等*/
						{
							V_RamEnData=V_E2EnData;                  /*E2更新RAM电量*/

							if(C_W_SafeFlag!=GV_D_SafeFlag)
							{
								return;
							}

							PF_Ulong64ToBuffer8(&GV_CurrEnergyData[V_i][0],&V_RamEnData,C_CurrDataLen5);
							V_CRC16=PF_Cal_CRC(&GV_CurrEnergyData[V_i][0],C_CurrDataLen5);          /*计算CRC*/
							PF_Ushort16ToBuffer2(&PV_CRC8[0],&V_CRC16);
							GV_CurrEnergyData[V_i][C_CurrDataLen5]=PV_CRC8[0];
							GV_CurrEnergyData[V_i][C_CurrDataLen5+1]=PV_CRC8[1];
						}
					}
				}
			}
			else                 /*RAM CRC错误，E2更新RAM*/
			{
				V_RamEnData=V_E2EnData;                  /*E2更新RAM电量*/

				if(C_W_SafeFlag!=GV_D_SafeFlag)
				{
					return;
				}

				PF_Ulong64ToBuffer8(&GV_CurrEnergyData[V_i][0],&V_RamEnData,C_CurrDataLen5);
				V_CRC16=PF_Cal_CRC(&GV_CurrEnergyData[V_i][0],C_CurrDataLen5);          /*计算CRC*/
				PF_Ushort16ToBuffer2(&PV_CRC8[0],&V_CRC16);
				GV_CurrEnergyData[V_i][C_CurrDataLen5]=PV_CRC8[0];
				GV_CurrEnergyData[V_i][C_CurrDataLen5+1]=PV_CRC8[1];
			}
		}
		else                 /*E2数据错误*/
		{
			continue;
		}
	}

	SF_Deal_UpdataFlag(C_Updata_Init, PV_E2Data, 0);		/*初始化变量*/

	GV_D_SafeFlag=C_Clear_SafeFlag;
	/*重要数据定时校验*/
	SF_ImportantDataCheckAndRecover();
}
/*********************************************************************************
函数原型：void InF_ChangeTime_LoadProfileCover(void)
功能描述：修改时间负荷记录覆盖接口函数,通信调用。目前用于冻结数据覆盖，包含分钟、小时、日、月冻结，内部处理
输入参数：无
输出参数：无
返回参数：无
功能说明：
调用机制：往前修改时间时，通信调用该接口函数
备     注：
*********************************************************************************/
void InF_ChangeTime_LoadProfileCover(void)
{
	ulong32 V_FlashAddrLate,V_FlashAddrEar;
	uchar8 V_FlashAddr8[4],V_Return_Flag,V_i,V_j;
	uchar8 V_Data_TimeSys[C_698FreeData_DateLen6],V_Data_TimeNote[C_698FreeData_DateLen6];
	ulong32 V_FlashAddr,C_FlashStAddr_LoadProfile,C_FlashEndAddr_LoadProfile;
	ushort16 V_E2Addr_LoadP_Flash_Late,V_E2Addr_LoadP_Flash_Ear;
	uchar8 V_DI2,V_ProNum,V_m = 0xFF;

	V_DI2=(uchar8)((C_RelatedOAD_Min&0x00FF0000)>>16);

	V_ProNum=InF_GetMinFreezeTolNum();/*获取分钟冻结总方案数*/
	if(V_ProNum>8)/*1-8*/
	{
		V_ProNum=0;
	}

	for(V_i=0;V_i<(C_698FixTimeFreeze+V_ProNum);V_i++)/*循环冻结记录，只有年、月、日、时、分覆盖，注意表格顺序*/
	{
		GV_D_SafeFlag=C_Clear_SafeFlag;

		if(V_i<C_698FixTimeFreeze)
		{
			V_E2Addr_LoadP_Flash_Late=Str_698FreezeDataTable[V_i].V_E2AddrLate;
			V_E2Addr_LoadP_Flash_Ear=Str_698FreezeDataTable[V_i].V_E2AddrEar;
			C_FlashStAddr_LoadProfile=Str_698FreezeDataTable[V_i].V_StaFlashAddr;
			if(V_DI2==Str_698FreezeDataTable[V_i].V_DI2)/*分钟冻结*/
			{
				V_m=V_i;
				continue;
			}
		}
		else/*分钟冻结处理*/
		{
			V_Return_Flag=SF_GetMinFreezePro_E2andFlashAddr((V_i-C_698FixTimeFreeze),&C_FlashStAddr_LoadProfile,&C_FlashEndAddr_LoadProfile,&V_E2Addr_LoadP_Flash_Ear,&V_E2Addr_LoadP_Flash_Late);/*根据分钟冻结方案号，获取该方案最近、最早记录E2地址及该方案起始、结束Flash地址*/
			if(C_OK!=V_Return_Flag)
			{
				continue;
			}
		}

		V_Return_Flag=SF_ReadE2Three(V_E2Addr_LoadP_Flash_Late,4,&V_FlashAddr8[0]);        /*取最近1条记录Flash页地址*/
		PF_Buffer4ToUlong32(&V_FlashAddr8[0],&V_FlashAddrLate,4);
		V_FlashAddrLate&=0xFFFFF000;             /*页地址转化，增加容错性*/

		V_Return_Flag=SF_ReadE2Three(V_E2Addr_LoadP_Flash_Ear,4,&V_FlashAddr8[0]);         /*取最早1条记录Flash地址*/
		PF_Buffer4ToUlong32(&V_FlashAddr8[0],&V_FlashAddrEar,4);
		if(C_OK!=V_Return_Flag)
		{
			continue;
		}

		GV_D_SafeFlag|=C_W_SafeFlag_1;

		for(V_j=0;V_j<C_698FreeData_DateLen6;V_j++)            /*取系统当前时间日期,YYYYMMDDhhmmss*/
		{
			V_Data_TimeSys[V_j]=GV_Date_Time[V_j];     /*去掉YY*/
		}

		if(C_FlashStAddr_LoadProfile==V_FlashAddrEar)  /*该类冻结，没有记录数据*/
		{
			GV_D_SafeFlag=C_Clear_SafeFlag;
			continue;
		}

		if(V_i>=C_698FixTimeFreeze)/*分钟冻结记录*/
		{
			V_FlashAddr=SF_GetFixedLoadModeNoteFlashAddr((V_i-C_698FixTimeFreeze),V_m,V_FlashAddrLate);/*获取某页Flash记录，最后1个记录对应的Flash地址*/
		}
		else
		{
			V_FlashAddr=SF_GetFixedLoadModeNoteFlashAddr(0,V_i,V_FlashAddrLate);/*获取某页Flash记录，最后1个记录对应的Flash地址，方案号固定0，其他冻结没有关系*/
		}

		if(0xFFFFFFFF==V_FlashAddr)
		{
			GV_D_SafeFlag=C_Clear_SafeFlag;
			continue;	/*查询下一类记录*/
		}

		GV_D_SafeFlag|=C_W_SafeFlag_2;
		InF_FlashChipSelect();
		InF_ReadFlash(V_FlashAddr,&V_Data_TimeNote[0],C_698FreeData_DateLen6);

		V_Return_Flag=PF_Campare_Data(&V_Data_TimeNote[0],&V_Data_TimeSys[0],C_698FreeData_DateLen6);
		if(C_GreaterThan!=V_Return_Flag)  /*≤，时间往后改往后*/
		{
			GV_D_SafeFlag=C_Clear_SafeFlag;
			continue;/*查询下一类记录*/
		}

		GV_D_SafeFlag|=C_W_SafeFlag_3; /*置安全标志*/

		if(C_FlashStAddr_LoadProfile==V_FlashAddrEar)  /*没有记录数据*/
		{
			GV_D_SafeFlag=C_Clear_SafeFlag;
			continue;
		}
		else                                                       /*判断最早记录块时间*/
		{
			InF_FlashChipSelect();
			InF_ReadFlash(V_FlashAddrEar,&V_Data_TimeNote[0],C_698FreeData_DateLen6);    /*读最早记录时间*/

			V_Return_Flag=PF_Campare_Data(&V_Data_TimeSys[0],&V_Data_TimeNote[0],C_698FreeData_DateLen6);  /*比较时间大小*/
			if(C_Equal==V_Return_Flag)                              /*等于最早记录块时间*/
			{
				V_FlashAddrLate=V_FlashAddrEar-C_LoadProfile_RevMode;  /*最早记录Flash页地址*/
				PF_Ulong32ToBuffer4(&V_FlashAddr8[0],&V_FlashAddrLate,4);
				SF_WriteE2Three(V_E2Addr_LoadP_Flash_Late,4,&V_FlashAddr8[0]);/*更新E2最近1次记录Flash页地址*/

				if(V_i>=C_698FixTimeFreeze)/*分钟冻结记录*/
				{
					SF_ChageTime_ChageFlashNote((V_FlashAddrLate+C_LoadProfile_RevMode),V_m,(V_i-C_698FixTimeFreeze));      /*从第2个记录块开始无效,更新Flash记录模式字及记录*/
				}
				else
				{
					SF_ChageTime_ChageFlashNote((V_FlashAddrLate+C_LoadProfile_RevMode),V_i,0);
				}
			}
			else
			{
				if(C_LessThan==V_Return_Flag)    /*V_Data_TimeSys<V_Data_TimeNote早于最早记录时间,Flash记录调整为初始状态*/
				{
					V_FlashAddrLate=C_FlashStAddr_LoadProfile;
					PF_Ulong32ToBuffer4(&V_FlashAddr8[0],&V_FlashAddrLate,4);
					SF_WriteE2Three(V_E2Addr_LoadP_Flash_Late,4,&V_FlashAddr8[0]);
					V_FlashAddrEar=C_FlashStAddr_LoadProfile;
					PF_Ulong32ToBuffer4(&V_FlashAddr8[0],&V_FlashAddrEar,4);
					SF_WriteE2Three(V_E2Addr_LoadP_Flash_Ear,4,&V_FlashAddr8[0]);
				}
				else                             /*二分法查找*/
				{
					if(V_i>=C_698FixTimeFreeze)/*分钟冻结记录*/
					{
						V_FlashAddrLate=SF_LoadDichotomyFlashData((V_i-C_698FixTimeFreeze),V_m,&V_Data_TimeSys[0],V_FlashAddrEar,V_FlashAddrLate,C_LoadDichotomyFindBefore);
					}
					else
					{
						V_FlashAddrLate=SF_LoadDichotomyFlashData(0,V_i,&V_Data_TimeSys[0],V_FlashAddrEar,V_FlashAddrLate,C_LoadDichotomyFindBefore);
					}

					if(0xFFFFFFFF==V_FlashAddrLate)  /*非法错误或查找不到時間調整記錄數據即不用调整*/
					{
						GV_D_SafeFlag=C_Clear_SafeFlag;
						continue;
					}

					V_FlashAddr=V_FlashAddrLate&0xFFFFF000;
					PF_Ulong32ToBuffer4(&V_FlashAddr8[0],&V_FlashAddr,4);
					SF_WriteE2Three(V_E2Addr_LoadP_Flash_Late,4,&V_FlashAddr8[0]);

					if(V_i>=C_698FixTimeFreeze)/*分钟冻结记录*/
					{
						SF_ChageTime_ChageFlashNote(V_FlashAddrLate,V_m,(V_i-C_698FixTimeFreeze));
					}
					else
					{
						SF_ChageTime_ChageFlashNote(V_FlashAddrLate,V_i,0);
					}
				}
			}
		}
	}

	GV_D_SafeFlag=C_Clear_SafeFlag;
}
/*********************************************************************************
函数原型：void SF_ChageTime_ChageFlashNote(ulong32 V_FlashAddr,uchar8 V_Order,uchar8 V_ProNum)
功能描述：修改时间更改Flash记录，增加修改时间标志及记录时间YMDhm修改为FF，底层为全0。
输入参数：uchar8 V_Order：某类冻结数据在Str_698FreezeDataTable中序号；
		ulong32 V_FlashAddr:要操作Flash记录绝对地址；下一条记录为无效数据
		uchar8 V_ProNum：分钟冻结用方案号
输出参数：无
返回参数：无
功能说明：
调用机制：
备     注：主流程已置安全标志
*********************************************************************************/
void SF_ChageTime_ChageFlashNote(ulong32 V_FlashAddr,uchar8 V_Order,uchar8 V_ProNum)
{
	uchar8 V_i,V_DI2,P_Data[C_698FreeData_DateLen6],V_DI2Temp;
	ulong32 V_FlashAddr32;
	ushort16 V_DataLen,V_DataLenOff;

	if(V_Order>=Str_698FreezeDataTable_Len)/*异常判断*/
	{
		return;
	}

	V_DI2=Str_698FreezeDataTable[V_Order].V_DI2;

	V_DI2Temp=(V_DI2&0x1F);
	V_DI2Temp |= (V_ProNum<<5);
	V_DataLen=SF_JudgeWriteDataLen(V_DI2Temp);
	if(V_DataLen==0)/*异常判断*/
	{
		return;
	}

	V_DataLenOff=(ushort16)(V_FlashAddr%C_OneFlashPage);/*页内地址偏移*/
	V_DataLenOff+=2*V_DataLen;/*确保下一条有效*/
	if(V_DataLenOff<=C_OneFlash_PageNum)
	{
		V_FlashAddr32=V_FlashAddr&0xFFFFF000;/*页地址*/
		P_Data[0]=C_Flash_NoEmpty;
		if(GV_D_SafeFlag==C_W_SafeFlag)
		{
			InF_FlashChipSelect();
			InF_WriteFlash(V_FlashAddr32,&P_Data[0],1);/*写1字节时间调整标志，应用层写FF，底层为00*/

			V_FlashAddr32=V_FlashAddr+V_DataLen;
			for(V_i=0;V_i<C_698FreeData_DateLen6;V_i++)
			{
				P_Data[V_i]=C_Flash_NoEmpty;
			}
			InF_FlashChipSelect();
			InF_WriteFlash(V_FlashAddr32,&P_Data[0],C_698FreeData_DateLen6);/*写下1条YMDhms为，应用层写FF，底层为00*/
		}
	}
}

/*********************************************************************************
函数原型：ulong32 SF_GetFixedLoadModeNoteFlashAddr(uchar8 V_ProNum,uchar8 V_Order,ulong32 V_FindFlashAddr)
功能描述：查找某页Flash最后1条有效记录的具体地址
输入参数：uchar8 V_ProNum：分钟冻结用方案号
		uchar8 V_Order：某类冻结数据在Str_698FreezeDataTable中序号；
		ulong32 V_FindFlashAddr：需要查找Flash记录页地址；
输出参数：无
返回参数：ulong32 返回该记录块在该页Flash记录中的具体地址,当数据非法时返回0xFFFFFFFF；
功能说明：
调用机制：
备     注：
*********************************************************************************/
ulong32 SF_GetFixedLoadModeNoteFlashAddr(uchar8 V_ProNum,uchar8 V_Order,ulong32 V_FindFlashAddr)
{
	uchar8 V_i,V_FlashAddr8[4],V_ucReturn,V_DI2,V_Sign;
	ushort16 V_E2Addr_LoadP_Flash_Late,V_DataLen,V_Len,V_NumTemp;
	uchar8 P_Data[C_698FreeData_DateLen6],P_Sign[C_LoadProfile_RevMode];
	ulong32 V_FlashAddr32,V_FlashAddrLate;
	uchar8 V_DI2Temp;

	V_FlashAddr32=0xFFFFFFFF;

	if(V_Order>=Str_698FreezeDataTable_Len)/*异常判断*/
	{
		return V_FlashAddr32;
	}

	V_E2Addr_LoadP_Flash_Late=Str_698FreezeDataTable[V_Order].V_E2AddrLate;
	V_DI2=(uchar8)((C_RelatedOAD_Min&0x00FF0000)>>16);
	if(V_DI2==Str_698FreezeDataTable[V_Order].V_DI2)/*分钟冻结*/
	{
		V_E2Addr_LoadP_Flash_Late=E2Addr_Min_Free_Flash_Ear1+V_ProNum*12+6;/*最近、最早记录Flash存E2地址*/
	}

	V_ucReturn = SF_ReadE2Three(V_E2Addr_LoadP_Flash_Late,4,&V_FlashAddr8[0]);        /*取最近1条记录Flash页地址*/
	if(V_ucReturn != C_OK)
	{
		return V_FlashAddr32;
	}

	PF_Buffer4ToUlong32(&V_FlashAddr8[0],&V_FlashAddrLate,4);
	V_FlashAddrLate&=0xFFFFF000;             /*页地址转化，增加容错性*/

	V_DI2=Str_698FreezeDataTable[V_Order].V_DI2;
	V_DI2Temp=(V_DI2&0x1F);
	V_DI2Temp |= (V_ProNum<<5);
	V_DataLen=SF_JudgeWriteDataLen(V_DI2Temp);
	if(V_DataLen==0)/*异常判断*/
	{
		return V_FlashAddr32;
	}

	V_FlashAddr32=V_FindFlashAddr+C_LoadProfile_RevMode;
	V_Sign=0;
	if(V_FindFlashAddr==V_FlashAddrLate)/*最近页*/
	{
		for(V_Len=0;V_Len<(C_OneFlash_PageNum-C_LoadProfile_RevMode-C_698FreeData_DateLen6);)
		{
			InF_FlashChipSelect();
			InF_ReadFlash(V_FlashAddr32,&P_Data[0],C_698FreeData_DateLen6);    /*YMDhms*/

			for(V_i=0;V_i<C_698FreeData_DateLen6;V_i++)
			{
				if(C_Flash_Empty!=P_Data[V_i])/*判断数据是否为全零，即底层为FF，没有写入数据*/
				{
					break;
				}
			}

			if(V_i>=C_698FreeData_DateLen6)/*数据全零*/
			{
				V_Sign=C_Flash_Empty68;
			}

			for(V_i=0;V_i<C_698FreeData_DateLen6;V_i++)
			{
				if(C_Flash_NoEmpty!=P_Data[V_i])/*判断数据是否为全FF，即底层为00，说明有时间调整*/
				{
					break;
				}
			}

			if(V_i>=C_698FreeData_DateLen6)/*数据全FF*/
			{
				V_Sign=C_Flash_Empty68;
			}

			if(C_Flash_Empty68==V_Sign)
			{
				break;
			}

			V_Len+=V_DataLen;
			V_FlashAddr32+=V_DataLen;
		}

		V_FlashAddr32-=V_DataLen;
	}
	else
	{
		InF_FlashChipSelect();
		InF_ReadFlash((V_FlashAddr32-C_LoadProfile_RevMode),&P_Sign[0],C_LoadProfile_RevMode);    /*读修改时间标志字*/
		if(0x68==P_Sign[0])/*该页有记录写该标志为68，该页记录时间有调整，则写非68标志（同时把无效记录5字节YMDhm写为FF，即底层写0），说明该页记录时间有调整,取下1页*/
		{
			V_NumTemp=(C_OneFlash_PageNum-C_LoadProfile_RevMode)/V_DataLen;/*每页记录条数*/
			V_FlashAddr32+=(V_NumTemp-1)*V_DataLen;
		}
		else/*有时间调整*/
		{
			for(V_Len=0;V_Len<(C_OneFlash_PageNum-C_LoadProfile_RevMode-C_698FreeData_DateLen6);)
			{
				InF_FlashChipSelect();
				InF_ReadFlash(V_FlashAddr32,&P_Data[0],C_698FreeData_DateLen6);    /*YMDhms*/

				for(V_i=0;V_i<C_698FreeData_DateLen6;V_i++)
				{
					if(C_Flash_NoEmpty!=P_Data[V_i])/*判断数据是否为全FF，即底层为00，说明有时间调整*/
					{
						break;
					}
				}

				if(V_i>=C_698FreeData_DateLen6)/*数据全FF*/
				{
					V_Sign=C_Flash_Empty68;
				}

				if(C_Flash_Empty68==V_Sign)
				{
					break;
				}

				V_Len+=V_DataLen;
				V_FlashAddr32+=V_DataLen;
			}

			V_FlashAddr32-=V_DataLen;
		}
	}

	return V_FlashAddr32;
}
/*********************************************************************************
函数原型：ulong32 SF_FindOneFlashPageGiveTimeFlashAddr(uchar8 V_ProNum, uchar8 V_Order, ulong32 V_FindFlashAddr,
														uchar8 *P_FixTime, uchar8 V_LoadDichotomyFindWay)
功能描述：查找1页Flash记录(包括首、尾记录)，返回满足给定时间的Flash记录模式字地址，记录时间早于等于给定时间
输入参数：
		uchar8 V_ProNum：分钟冻结用方案号
		uchar8 V_Order：某类冻结数据在Str_698FreezeDataTable中序号；
		uchar8 *P_FixTime：需要查找的固定数间；
		ulong32 V_FindFlashAddr：需要查找Flash页地址；
		uchar8 V_LoadDichotomyFindWay：2分法查找方式，；
		C_LoadDichotomyFindBefore 0x55表示2分法，时间往前查找，主要用于时间往前调整
		C_LoadDichotomyFindAfter 0xAA表示2分法，时间往后查找，主要用于抄读负荷记录给定时间
输出参数：无
返回参数：
		ulong32 返回满足给定时间的Flash记录地址,当数据非法时返回0xFFFFFFFF；
功能说明：
调用机制：
备     注：
*********************************************************************************/
ulong32 SF_FindOneFlashPageGiveTimeFlashAddr(uchar8 V_ProNum,uchar8 V_Order,ulong32 V_FindFlashAddr,uchar8 *P_FixTime,uchar8 V_LoadDichotomyFindWay)
{
	uchar8 V_i;
	ulong32 V_FlashAddr;
	uchar8 V_EarNoteTime[C_698FreeData_DateLen6],V_LateNoteTime[C_698FreeData_DateLen6];
	uchar8 V_CompareSign,V_DI2,V_Sign;
	ushort16 V_DataLen,V_Len;
	uchar8 V_DI2Temp;

	V_FindFlashAddr=V_FindFlashAddr&0xFFFFF000; /*页地址转化，增加容错性*/
	V_FlashAddr=0xFFFFFFFF;
	V_FlashAddr=SF_GetFixedLoadModeNoteFlashAddr(V_ProNum,V_Order,V_FindFlashAddr);/*获取某页Flash记录，最后1条有效记录对应的Flash地址*/
	if(0xFFFFFFFF==V_FlashAddr)
	{
		return V_FlashAddr;
	}

	InF_FlashChipSelect();
	InF_ReadFlash((V_FindFlashAddr+C_LoadProfile_RevMode),&V_EarNoteTime[0],C_698FreeData_DateLen6);

	InF_FlashChipSelect();
	InF_ReadFlash(V_FlashAddr,&V_LateNoteTime[0],C_698FreeData_DateLen6);

	/***************************先判最早、最近一次****************************/
	V_CompareSign=PF_Campare_Data(&V_EarNoteTime[0],P_FixTime,C_698FreeData_DateLen6);
	if(C_Equal==V_CompareSign)
	{
		return (V_FindFlashAddr+C_LoadProfile_RevMode);  /*第1条记录*/
	}
	else
	{
		if(C_GreaterThan==V_CompareSign)/*早于该Flash记录最早时间*/
		{
			if(C_LoadDichotomyFindAfter==V_LoadDichotomyFindWay)  /*表示2分法，时间往前查找，主要用于抄读负荷记录给定时间*/
			{
				return (V_FindFlashAddr+C_LoadProfile_RevMode);  /*第1条记录*/
			}    /*往前查找调用该函数前已处理*/
			else
			{
				return 0xFFFFFFFF;
			}
		}
	}

	V_CompareSign=PF_Campare_Data(&V_LateNoteTime[0],P_FixTime,C_698FreeData_DateLen6);
	if(C_Equal==V_CompareSign)
	{
		return V_FlashAddr;
	}
	else
	{
		if(C_LessThan==V_CompareSign)/*晚于该Flash记录最近时间*/
		{
			if(C_LoadDichotomyFindAfter==V_LoadDichotomyFindWay)  /*表示2分法，时间往后查找，主要用于抄读负荷记录给定时间*/
			{
				return 0xFFFFFFFF;
			}
			else   /*往前查找*/
			{
				return V_FlashAddr;
			}
		}
	}

	V_DI2=Str_698FreezeDataTable[V_Order].V_DI2;
	V_DI2Temp=(V_DI2&0x1F);
	V_DI2Temp |= (V_ProNum<<5);
	V_DataLen=SF_JudgeWriteDataLen(V_DI2Temp);
	if(V_DataLen==0)/*异常判断*/
	{
		return 0xFFFFFFFF;
	}

	V_FlashAddr=V_FindFlashAddr+C_LoadProfile_RevMode+V_DataLen;
	/************两者中间****找时间相等***********/
	V_Sign=0;
	for(V_Len=V_DataLen;V_Len<=(C_OneFlash_PageNum-C_LoadProfile_RevMode-V_DataLen);)
	{
		InF_FlashChipSelect();
		InF_ReadFlash(V_FlashAddr,&V_EarNoteTime[0],C_698FreeData_DateLen6);    /*YMDhms*/

		V_CompareSign=PF_Campare_Data(&V_EarNoteTime[0],P_FixTime,C_698FreeData_DateLen6);
		if((C_GreaterThan==V_CompareSign)||(C_Equal==V_CompareSign))   /*记录时间晚于或等于固定时间*/
		{
			break;
		}

		for(V_i=0;V_i<C_698FreeData_DateLen6;V_i++)
		{
			if(C_Flash_Empty!=V_EarNoteTime[V_i])/*判断数据是否为全零，即底层为FF，没有写入数据*/
			{
				break;
			}
		}

		if(V_i>=C_698FreeData_DateLen6)/*数据全零*/
		{
			V_Sign=C_Flash_Empty68;
		}

		for(V_i=0;V_i<C_698FreeData_DateLen6;V_i++)
		{
			if(C_Flash_NoEmpty!=V_EarNoteTime[V_i])/*判断数据是否为全FF，即底层为00，说明有时间调整*/
			{
				break;
			}
		}

		if(V_i>=C_698FreeData_DateLen6)/*数据全FF*/
		{
			V_Sign=C_Flash_Empty68;
		}

		if(C_Flash_Empty68==V_Sign)
		{
			break;
		}

		V_Len+=V_DataLen;
		V_FlashAddr+=V_DataLen;
	}

	if((V_Len>(C_OneFlash_PageNum-C_LoadProfile_RevMode-V_DataLen))||(C_Flash_Empty68==V_Sign))
	{
		return 0xFFFFFFFF;  /*数据不存在*/
	}
	else
	{
		if(C_Equal==V_CompareSign)
		{
			return V_FlashAddr;
		}
		else
		{
			if(C_LoadDichotomyFindBefore==V_LoadDichotomyFindWay)  /*表示2分法，时间往前查找*/
			{
				return (V_FlashAddr-V_DataLen);   /*前1块记录*/
			}
			else/*表示2分法，时间往后查找，主要用于抄读负荷记录给定时间*/
			{
				return V_FlashAddr;
			}
		}
	}
}
/*********************************************************************************
函数原型：ulong32 SF_LoadDichotomyFixedFlashData(uchar8 V_ProNum,uchar8 V_Order,uchar8 *P_FixTime,ulong32 V_FlashAddrEar,
												ulong32 V_FlashAddrLate,uchar8 V_LoadDichotomyFindWay)
功能描述：采用2分法,查找计算某固定Flash块，满足时间条件的记录模式字地址,即有效的最近1条记录模式字地址,记录时间早于等于给定时间
输入参数：
		uchar8 V_ProNum：分钟冻结用方案号
		uchar8 V_Order：某类冻结数据在Str_698FreezeDataTable中序号；
		uchar8 *P_FixTime：需要查找的固定数间；
		ulong32 V_FlashAddrEar：查询块Flash起始页地址,非绝对地址；
		ulong32 V_FlashAddrLate：查询块Flash结束页地址；V_FlashAddrEar<V_FlashAddrLate
		uchar8 V_LoadDichotomyFindWay：2分法查找方式，；
		C_LoadDichotomyFindBefore 0x55表示2分法，时间往前查找，主要用于时间往前调整
		C_LoadDichotomyFindAfter 0xAA表示2分法，时间往后查找，主要用于抄读负荷记录给定时间
输出参数：无
返回参数：
		ulong32 返回记录数据模式字Flash地址,当数据非法时返回0xFFFFFFFF；
功能说明：
调用机制：
备     注：
*********************************************************************************/
ulong32 SF_LoadDichotomyFixedFlashData(uchar8 V_ProNum,uchar8 V_Order,uchar8 *P_FixTime,ulong32 V_FlashAddrEar,ulong32 V_FlashAddrLate,uchar8 V_LoadDichotomyFindWay)
{
	ulong32 V_FlashAddr;
	uchar8 V_EarNoteTime[C_698FreeData_DateLen6],V_LateNoteTime[C_698FreeData_DateLen6];
	uchar8 V_CompareSign;
	ulong32 V_FlashAddrMin,V_FlashAddrMax,V_FlashAddrMid;

	V_FlashAddr=0xFFFFFFFF;

	V_FlashAddr=SF_GetFixedLoadModeNoteFlashAddr(V_ProNum,V_Order,V_FlashAddrLate);/*获取最近页Flash记录，最后1个有效记录对应的Flash地址*/
	if(0xFFFFFFFF==V_FlashAddr)
	{
		return V_FlashAddr;
	}

	InF_FlashChipSelect();
	InF_ReadFlash((V_FlashAddrEar+C_LoadProfile_RevMode),&V_EarNoteTime[0],C_698FreeData_DateLen6); /*获取最早记录页，第1条记录时间*/

	InF_FlashChipSelect();
	InF_ReadFlash(V_FlashAddr,&V_LateNoteTime[0],C_698FreeData_DateLen6); /*获取最近记录页，最后1条记录时间*/

	/*****************先判最早第1块、最近最后1块****************************/
	V_CompareSign=PF_Campare_Data(&V_EarNoteTime[0],P_FixTime,C_698FreeData_DateLen6);
	if(C_Equal==V_CompareSign)
	{
		return (V_FlashAddrEar+C_LoadProfile_RevMode);
	}
	else
	{
		if(C_GreaterThan==V_CompareSign)/*早于该Flash记录最早时间*/
		{
			if(C_LoadDichotomyFindAfter==V_LoadDichotomyFindWay)  /*时间往后查找，主要用于抄读负荷记录给定时间*/
			{
				return (V_FlashAddrEar+C_LoadProfile_RevMode);
			}    /*往前查找调用该函数前已处理*/
			else
			{
				return 0xFFFFFFFF;
			}
		}
	}

	V_CompareSign=PF_Campare_Data(&V_LateNoteTime[0],P_FixTime,C_698FreeData_DateLen6);
	if(C_Equal==V_CompareSign)
	{
		return V_FlashAddr;  /*负荷记录模式字地址*/
	}
	else
	{
		if(C_LessThan==V_CompareSign)/*晚于该Flash记录最近时间*/
		{
			if(C_LoadDichotomyFindAfter==V_LoadDichotomyFindWay)  /*表示2分法，时间往后查找，主要用于抄读负荷记录给定时间*/
			{
				return 0xFFFFFFFF;
			}
			else   /*往前查找*/
			{
				return V_FlashAddr;
			}
		}
	}

	/************两者中间****多页Flash记录,2分法***********/
	V_FlashAddrMin=V_FlashAddrEar;
	V_FlashAddrMax=V_FlashAddrLate;

	while(V_FlashAddrMin<=V_FlashAddrMax)  /*2分法,V_FlashAddrMin...V_FlashAddrMid...V_FlashAddrMax*/
	{
		V_FlashAddrMid=(V_FlashAddrMin+V_FlashAddrMax)/2;
		V_FlashAddrMid=V_FlashAddrMid-V_FlashAddrMid%C_OneFlashPage;  /*2分法页地址*/

		V_FlashAddrMid=SF_GetFixedLoadModeNoteFlashAddr(V_ProNum,V_Order,V_FlashAddrMid);/*获取该页Flash记录，最后1个固定模式字记录对应的Flash地址*/
		if(0xFFFFFFFF==V_FlashAddrMid)
		{
			return 0xFFFFFFFF;
		}

		V_FlashAddr=V_FlashAddrMid;
		InF_FlashChipSelect();
		InF_ReadFlash(V_FlashAddrMid,&V_EarNoteTime[0],C_698FreeData_DateLen6); /*获取中间Flash页，最后1条负荷记录时间*/

		V_CompareSign=PF_Campare_Data(&V_EarNoteTime[0],P_FixTime,C_698FreeData_DateLen6);
		if(C_Equal==V_CompareSign)
		{
			return (V_FlashAddrMid);
		}
		else  /*V_FlashAddrMin...V_FlashAddrMid...V_FlashAddrMax*/
		{
			if(C_LessThan==V_CompareSign)/*晚于该Flash记录最后1块记录时间，则取(V_FlashAddrMid+C_OneFlashPage)下1页...V_FlashAddrMax*/
			{
				V_FlashAddrMid=V_FlashAddrMid-V_FlashAddrMid%C_OneFlashPage;  /*页地址*/
				V_FlashAddrMin=V_FlashAddrMid+C_OneFlashPage;

				if(C_LoadDichotomyFindBefore==V_LoadDichotomyFindWay)  /*表示2分法，时间往前查找;往后查SF_FindOneFlashPageGiveTimeFlashAddr中处理*/
				{
					InF_FlashChipSelect();
					InF_ReadFlash((V_FlashAddrMin+C_LoadProfile_RevMode),&V_EarNoteTime[0],C_698FreeData_DateLen6);  /*读下1页最早记录时间*/

					V_CompareSign=PF_Campare_Data(&V_EarNoteTime[0],P_FixTime,C_698FreeData_DateLen6);
					if(C_GreaterThan==V_CompareSign)  /*早于该Flash记录最近时间*/
					{
						return V_FlashAddr;   /*返回前页最后查找记录模式字Flash地址*/
					}
				}
			}
			else  /*早于该Flash记录最后1块记录时间，则取V_FlashAddrMin...V_FlashAddrMid该页*/
			{
				V_FlashAddrMid=V_FlashAddrMid-V_FlashAddrMid%C_OneFlashPage;  /*页地址*/
				V_FlashAddrMax=V_FlashAddrMid;
			}
			/**********************2分法，查找到最后两页*********************/
			if((C_OneFlashPage==(V_FlashAddrMax-V_FlashAddrMin))||(V_FlashAddrMax==V_FlashAddrMin))
			{
				if(C_LoadDichotomyFindAfter==V_LoadDichotomyFindWay)  /*时间往后查找，主要用于抄读负荷记录给定时间*/
				{
					V_FlashAddr=SF_FindOneFlashPageGiveTimeFlashAddr(V_ProNum,V_Order,V_FlashAddrMin,P_FixTime,V_LoadDichotomyFindWay);  /*查找1页Flash记录(包括首、尾记录)，返回  */
					if((0xFFFFFFFF==V_FlashAddr)&&(V_FlashAddrMax!=V_FlashAddrMin))  /*查找另外1页*/
					{
						V_FlashAddr=SF_FindOneFlashPageGiveTimeFlashAddr(V_ProNum,V_Order,V_FlashAddrMax,P_FixTime,V_LoadDichotomyFindWay);
					}
				}
				else           /*往前查找*/
				{
					V_FlashAddr=SF_FindOneFlashPageGiveTimeFlashAddr(V_ProNum,V_Order,V_FlashAddrMax,P_FixTime,V_LoadDichotomyFindWay);  /*查找1页Flash记录(包括首、尾记录)，返回  */
					if((0xFFFFFFFF==V_FlashAddr)&&(V_FlashAddrMax!=V_FlashAddrMin))  /*查找另外1页*/
					{
						V_FlashAddr=SF_FindOneFlashPageGiveTimeFlashAddr(V_ProNum,V_Order,V_FlashAddrMin,P_FixTime,V_LoadDichotomyFindWay);
					}
				}
				return V_FlashAddr;
			}
		}
	}
	return V_FlashAddr;
}
/*********************************************************************************
函数原型：ulong32 SF_AbsFindOneFlashPageGiveTimeFlashAddr(uchar8 V_ProNum,uchar8 V_Order,ulong32 V_FindFlashAddr,
														uchar8 *P_FixTime,uchar8 V_LoadDichotomyFindWay)
功能描述：查找1页Flash记录(包括首、尾记录)，返回满足给定时间的Flash记录模式字地址，记录时间早于等于给定时间
输入参数：
		uchar8 V_ProNum：分钟冻结用方案号
		uchar8 V_Order：某类冻结数据在Str_698FreezeDataTable中序号；
		uchar8 *P_FixTime：需要查找的固定数间；
		ulong32 V_FindFlashAddr：需要查找Flash记录上一条绝对地址(跨页的话则为该页第1条记录地址)；
		uchar8 V_LoadDichotomyFindWay：2分法查找方式，；
		C_LoadDichotomyFindBefore 0x55表示2分法，时间往前查找，主要用于时间往前调整
		C_LoadDichotomyFindAfter 0xAA表示2分法，时间往后查找，主要用于抄读负荷记录给定时间
输出参数：无
返回参数：
		ulong32 返回满足给定时间的Flash记录地址,当数据非法时返回0xFFFFFFFF；
功能说明：
调用机制：
备     注：该函数内部只支持C_LoadDichotomyFindAfter0xAA时间往后查找
*********************************************************************************/
ulong32 SF_AbsFindOneFlashPageGiveTimeFlashAddr(uchar8 V_ProNum,uchar8 V_Order,ulong32 V_FindFlashAddr,uchar8 *P_FixTime,uchar8 V_LoadDichotomyFindWay)
{
	uchar8 V_i;
	ulong32 V_FlashAddr,V_FlashAddrEnd;
	uchar8 V_EarNoteTime[C_698FreeData_DateLen6];
	uchar8 V_CompareSign,V_DI2,V_Sign;
	ushort16 V_DataLen;
	uchar8 V_DI2Temp;

	V_FlashAddrEnd=V_FindFlashAddr&0xFFFFF000; /*页地址转化，增加容错性*/
	V_FlashAddr=V_FindFlashAddr;

	V_DI2=Str_698FreezeDataTable[V_Order].V_DI2;
	V_DI2Temp=(V_DI2&0x1F);
	V_DI2Temp |= (V_ProNum<<5);
	V_DataLen=SF_JudgeWriteDataLen(V_DI2Temp);
	if(V_DataLen==0)/*异常判断*/
	{
		return 0xFFFFFFFF;
	}

	V_FlashAddrEnd=V_FlashAddrEnd+C_OneFlashPage-C_Flash_EmptyNum-C_698FreeData_DateLen6;

	/************两者中间****找时间相等***********/
	V_Sign=0;
	for(;V_FlashAddr<V_FlashAddrEnd;)
	{
		InF_FlashChipSelect();
		InF_ReadFlash(V_FlashAddr,&V_EarNoteTime[0],C_698FreeData_DateLen6);    /*YMDhms*/

		V_CompareSign=PF_Campare_Data(&V_EarNoteTime[0],P_FixTime,C_698FreeData_DateLen6);
		if((C_GreaterThan==V_CompareSign)||(C_Equal==V_CompareSign))   /*记录时间晚于或等于固定时间*/
		{
			break;
		}

		for(V_i=0;V_i<C_698FreeData_DateLen6;V_i++)
		{
			if(C_Flash_Empty!=V_EarNoteTime[V_i])/*判断数据是否为全零，即底层为FF，没有写入数据*/
			{
				break;
			}
		}

		if(V_i>=C_698FreeData_DateLen6)/*数据全零*/
		{
			V_Sign=C_Flash_Empty68;
		}

		for(V_i=0;V_i<C_698FreeData_DateLen6;V_i++)
		{
			if(C_Flash_NoEmpty!=V_EarNoteTime[V_i])/*判断数据是否为全FF，即底层为00，s说明有时间调整*/
			{
				break;
			}
		}

		if(V_i>=C_698FreeData_DateLen6)/*数据全FF*/
		{
			V_Sign=C_Flash_Empty68;
		}

		if(C_Flash_Empty68==V_Sign)
		{
			break;
		}

		V_FlashAddr+=V_DataLen;
	}

	if((V_FlashAddr>=V_FlashAddrEnd)||(C_Flash_Empty68==V_Sign))
	{
		return 0xFFFFFFFF;  /*数据不存在*/
	}
	else
	{
		return V_FlashAddr;
	}
}
/*********************************************************************************
函数原型：ulong32 SF_TraversalSearchFixedFlashData(uchar8 V_ProNum, uchar8 V_Order, uchar8 *P_FixTime, ulong32 V_FlashAddrEar,
													ulong32 V_FlashAddrLate, uchar8 V_LoadDichotomyFindWay)
功能描述：遍历查找,查找计算某固定Flash块，满足时间条件的记录模式字地址,即有效的最近1条记录模式字地址,记录时间早于等于给定时间
输入参数：uchar8 V_ProNum：分钟冻结用方案号
		uchar8 V_Order：某类冻结数据在Str_698FreezeDataTable中序号；
		uchar8 *P_FixTime：需要查找的固定数间；
		ulong32 V_FlashAddrEar：查询块Flash起始页上一条记录绝对地址；
		ulong32 V_FlashAddrLate：查询块Flash结束页地址；V_FlashAddrEar<V_FlashAddrLate
		uchar8 V_LoadDichotomyFindWay：2分法查找方式；目前没有用
		C_LoadDichotomyFindBefore 0x55表示2分法，时间往前查找，主要用于时间往前调整
		C_LoadDichotomyFindAfter 0xAA表示2分法，时间往后查找，主要用于抄读负荷记录给定时间
输出参数：无
返回参数：ulong32 返回记录数据模式字Flash地址,当数据非法时，返回全0xFFFFFFFF；
功能说明：
调用机制：
备     注：
*********************************************************************************/
ulong32 SF_TraversalSearchFixedFlashData(uchar8 V_ProNum,uchar8 V_Order,uchar8 *P_FixTime,ulong32 V_FlashAddrEar,ulong32 V_FlashAddrLate,uchar8 V_LoadDichotomyFindWay)
{
	ulong32 V_FlashAddr;
	uchar8 V_LateNoteTime[C_698FreeData_DateLen6];
	uchar8 V_CompareSign;
	ulong32 V_FlashAddrTemp;

	V_FlashAddr=0xFFFFFFFF;
	V_FlashAddrTemp=V_FlashAddrEar&0xFFFFF000;
	for(;V_FlashAddrTemp<=V_FlashAddrLate;)
	{
		if((GV_ReadLoadFlashAddr32&0xFFFFF000)!=V_FlashAddrTemp)/*初始值或跨页判断，避免时间调整，查找时间长。重复查找*/
		{
			V_FlashAddr=SF_GetFixedLoadModeNoteFlashAddr(V_ProNum,V_Order,V_FlashAddrTemp);/*获取最近页Flash记录，最后1个有效记录对应的Flash地址*/
			GV_ReadLoadFlashAddr32=V_FlashAddr;
		}
		else
		{
			V_FlashAddr=GV_ReadLoadFlashAddr32;
		}

		if(0xFFFFFFFF==V_FlashAddr)
		{
			return V_FlashAddr;
		}

		InF_FlashChipSelect();
		InF_ReadFlash(V_FlashAddr,&V_LateNoteTime[0],C_698FreeData_DateLen6); /*获取最近记录页，最后1条记录时间*/

		V_CompareSign=PF_Campare_Data(&V_LateNoteTime[0],P_FixTime,C_698FreeData_DateLen6);
		if(C_Equal==V_CompareSign)
		{
			return V_FlashAddr;  /*负荷记录模式字地址*/
		}
		else
		{
			if(C_GreaterThan==V_CompareSign)/*晚于该Flash记录最近时间*/
			{
				break;
			}
			else
			{
				V_FlashAddrTemp+=C_OneFlashPage;
			}
		}
	}

	if(V_FlashAddrTemp<=V_FlashAddrLate)/*查找到满足记录时间的记录页地址*/
	{
		if(V_FlashAddrTemp==(V_FlashAddrEar&0xFFFFF000))/*同一页*/
		{
			V_FlashAddrTemp=V_FlashAddrEar;
		}
		else
		{
			V_FlashAddrTemp+=C_LoadProfile_RevMode;/*下页记录第1条地址*/
		}
		V_FlashAddr=SF_AbsFindOneFlashPageGiveTimeFlashAddr(V_ProNum,V_Order,V_FlashAddrTemp,P_FixTime,V_LoadDichotomyFindWay);  /*查找1页Flash记录(包括首、尾记录)，返回  */
	}
	else
	{
		return 0xFFFFFFFF;
	}

	return V_FlashAddr;
}
/*********************************************************************************
函数原型：ulong32 SF_TraversalSearchFlashData(ulong32 C_FlashStAddr_LoadProfile,ulong32 C_FlashEndAddr_LoadProfile,
uchar8 V_ProNum,uchar8 V_Order,uchar8 *P_FixTime,ulong32 V_FlashAddrEar,ulong32 V_FlashAddrLate,uchar8 V_LoadDichotomyFindWay)
功能描述：遍历查找满足当前时间Flash地址，该Flash地址为Flash中满足条件的记录模式字地址,即有效的最近1条记录模式字地址
输入参数：
		ulong32 C_FlashStAddr_LoadProfile：该冻结记录分配空间起始地址；
		ulong32 C_FlashEndAddr_LoadProfile：该冻结记录分配空间结束地址；
		uchar8 V_ProNum：分钟冻结用方案号
		uchar8 V_Order：某类冻结数据在Str_698FreezeDataTable中序号
		uchar8 *P_FixTime：需要查找的固定数间；
		ulong32 V_FlashAddrEar：查询块Flash上一条记录地址；
		ulong32 V_FlashAddrLate：查询块Flash结束页地址；
		uchar8 V_LoadDichotomyFindWay：2分法查找方式，；在该方案中没有判断，都是往后查
		C_LoadDichotomyFindBefore 0x55表示2分法，时间往前查找，主要用于时间往前调整
		C_LoadDichotomyFindAfter 0xAA表示2分法，时间往后查找，主要用于抄读负荷记录给定时间
输出参数：无
返回参数：ulong32 返回记录数据模式字Flash地址(698为满足时间要求的记录地址),当数据非法时返回0xFFFFFFFF；
功能说明：
调用机制：
备     注：FlashST---Ear...Late---FlashEnd;Ear...Late---FlashEnd;FlashST...Late---Ear...FlashEnd;
		其中---表示无效数据，考虑同一页
*********************************************************************************/
ulong32 SF_TraversalSearchFlashData(ulong32 C_FlashStAddr_LoadProfile,ulong32 C_FlashEndAddr_LoadProfile,uchar8 V_ProNum,uchar8 V_Order,uchar8 *P_FixTime,ulong32 V_FlashAddrEar,ulong32 V_FlashAddrLate,uchar8 V_LoadDichotomyFindWay)
{
	ulong32 V_FlashAddrFind;

	V_FlashAddrFind=0xFFFFFFFF;
	if((V_FlashAddrLate<C_FlashStAddr_LoadProfile)||(V_FlashAddrLate>(C_FlashEndAddr_LoadProfile+C_OneFlashPage))
		||(V_FlashAddrEar<C_FlashStAddr_LoadProfile)||(V_FlashAddrEar>(C_FlashEndAddr_LoadProfile+C_OneFlashPage)))/*理论不存在*/
	{
		return V_FlashAddrFind;
	}

	if(V_FlashAddrLate>=(V_FlashAddrEar&0xFFFFF000))/*FlashST---Ear...Late---FlashEnd; Ear...Late---FlashEnd;*/
	{
		V_FlashAddrFind=SF_TraversalSearchFixedFlashData(V_ProNum,V_Order,P_FixTime,V_FlashAddrEar,V_FlashAddrLate,V_LoadDichotomyFindWay);
	}
	else/* FlashST...Late---Ear...FlashEnd*/
	{
		V_FlashAddrFind=SF_TraversalSearchFixedFlashData(V_ProNum,V_Order,P_FixTime,V_FlashAddrEar,C_FlashEndAddr_LoadProfile,V_LoadDichotomyFindWay);/*Ear...FlashEnd*/
		if(0xFFFFFFFF==V_FlashAddrFind)
		{
			V_FlashAddrFind=SF_TraversalSearchFixedFlashData(V_ProNum,V_Order,P_FixTime,(C_FlashStAddr_LoadProfile+C_LoadProfile_RevMode),V_FlashAddrLate,V_LoadDichotomyFindWay);/* FlashST...Late*/
		}
	}

	return V_FlashAddrFind;
}

/*********************************************************************************
函数原型：ulong32 SF_LoadDichotomyFlashData(uchar8 V_ProNum,uchar8 V_Order,uchar8 *P_FixTime,ulong32 V_FlashAddrEar,
											ulong32 V_FlashAddrLate,uchar8 V_LoadDichotomyFindWay)
功能描述：采用2分法,计算满足当前时间Flash地址，该Flash地址为Flash中满足条件的记录模式字地址,即有效的最近1条记录模式字地址
输入参数：uchar8 V_ProNum：分钟冻结用方案号
		uchar8 V_Order：某类冻结数据在Str_698FreezeDataTable中序号
		uchar8 *P_FixTime：需要查找的固定数间；
		ulong32 V_FlashAddrEar：查询块Flash起始页地址，绝对地址即第1条记录地址；
		ulong32 V_FlashAddrLate：查询块Flash结束页地址；
		uchar8 V_LoadDichotomyFindWay：2分法查找方式，；
		C_LoadDichotomyFindBefore 0x55表示2分法，时间往前查找，主要用于时间往前调整
		C_LoadDichotomyFindAfter 0xAA表示2分法，时间往后查找，主要用于抄读负荷记录给定时间
输出参数：无
返回参数：ulong32 返回记录数据模式字Flash地址(698为满足时间要求的记录地址),当数据非法时返回0xFFFFFFFF；
功能说明：调用该函数查询前，记录快的头和尾已经判断处理过
调用机制：
备     注：FlashST---Ear...Late---FlashEnd;Ear...Late---FlashEnd;FlashST...Late---Ear...FlashEnd;
		其中---表示无效数据，考虑同一页
*********************************************************************************/
ulong32 SF_LoadDichotomyFlashData(uchar8 V_ProNum,uchar8 V_Order,uchar8 *P_FixTime,ulong32 V_FlashAddrEar,ulong32 V_FlashAddrLate,uchar8 V_LoadDichotomyFindWay)
{
	ulong32 V_FlashAddrFind;
	uchar8 V_EarNoteTime[C_698FreeData_DateLen6],V_CompareSign;
	ushort16 V_E2Addr_LoadP_Flash_Late,V_E2Addr_LoadP_Flash_Ear;
	ulong32 C_FlashStAddr_LoadProfile,C_FlashEndAddr_LoadProfile;
	uchar8 V_DI2,V_Return_Flag;

	C_FlashStAddr_LoadProfile=Str_698FreezeDataTable[V_Order].V_StaFlashAddr;
	C_FlashEndAddr_LoadProfile=Str_698FreezeDataTable[V_Order].V_EndFlashAddr;

	V_DI2=(uchar8)((C_RelatedOAD_Min&0x00FF0000)>>16);
	if(V_DI2==Str_698FreezeDataTable[V_Order].V_DI2)/*分钟冻结*/
	{
		V_Return_Flag=SF_GetMinFreezePro_E2andFlashAddr(V_ProNum,&C_FlashStAddr_LoadProfile,&C_FlashEndAddr_LoadProfile,&V_E2Addr_LoadP_Flash_Ear,&V_E2Addr_LoadP_Flash_Late);/*根据分钟冻结方案号，获取该方案最近、最早记录E2地址及该方案起始、结束Flash地址*/
		if(C_OK!=V_Return_Flag)
		{
			return 0xFFFFFFFF;
		}
	}

	V_FlashAddrFind=0xFFFFFFFF;
	if((V_FlashAddrLate<C_FlashStAddr_LoadProfile)||(V_FlashAddrLate>(C_FlashEndAddr_LoadProfile+C_OneFlashPage))
		||(V_FlashAddrEar<C_FlashStAddr_LoadProfile)||(V_FlashAddrEar>(C_FlashEndAddr_LoadProfile+C_OneFlashPage)))  /*理论不存在*/
	{
		return V_FlashAddrFind;
	}

	if((V_FlashAddrLate/C_OneFlashPage)==(V_FlashAddrEar/C_OneFlashPage))	/*同一页Flash*/
	{
		if(C_LoadDichotomyFindBefore==V_LoadDichotomyFindWay)  /*表示2分法，时间往前查找;往后查SF_FindOneFlashPageGiveTimeFlashAddr中处理*/
		{
			InF_FlashChipSelect();
			InF_ReadFlash((V_FlashAddrEar+C_LoadStartSignLength),&V_EarNoteTime[0],C_698FreeData_DateLen6);  /*读最早记录时间*/

			V_CompareSign=PF_Campare_Data(&V_EarNoteTime[0],P_FixTime,C_698FreeData_DateLen6);
			if(C_GreaterThan==V_CompareSign)  /*早于最早记录时间*/
			{
				return 0xFFFFFFFF;   /*返回无数据*/
			}
		}

		V_FlashAddrFind=SF_FindOneFlashPageGiveTimeFlashAddr(V_ProNum,V_Order,V_FlashAddrLate,P_FixTime,V_LoadDichotomyFindWay);/*查找1页Flash记录，满足给定时间的Flash记录模式字地址，记录时间早于等于给定时间*/
	}
	else	/*多页Flash*/
	{
		if(V_FlashAddrLate>V_FlashAddrEar)/*FlashST---Ear...Late---FlashEnd; Ear...Late---FlashEnd;*/
		{
			V_FlashAddrFind=SF_LoadDichotomyFixedFlashData(V_ProNum,V_Order,P_FixTime,(V_FlashAddrEar-C_LoadProfile_RevMode),V_FlashAddrLate,V_LoadDichotomyFindWay);
		}
		else   /* FlashST...Late---Ear...FlashEnd*/
		{
			if(C_LoadDichotomyFindBefore==V_LoadDichotomyFindWay)
			{
				V_FlashAddrFind=SF_LoadDichotomyFixedFlashData(V_ProNum,V_Order,P_FixTime,C_FlashStAddr_LoadProfile,V_FlashAddrLate,V_LoadDichotomyFindWay);/* FlashST...Late*/
				if(0xFFFFFFFF==V_FlashAddrFind)
				{
					V_FlashAddrFind=SF_LoadDichotomyFixedFlashData(V_ProNum,V_Order,P_FixTime,(V_FlashAddrEar-C_LoadProfile_RevMode),C_FlashEndAddr_LoadProfile,V_LoadDichotomyFindWay);/*Ear...FlashEnd*/
				}
			}
			else
			{
				V_FlashAddrFind=SF_LoadDichotomyFixedFlashData(V_ProNum,V_Order,P_FixTime,(V_FlashAddrEar-C_LoadProfile_RevMode),C_FlashEndAddr_LoadProfile,V_LoadDichotomyFindWay);/*Ear...FlashEnd*/
				if(0xFFFFFFFF==V_FlashAddrFind)
				{
					V_FlashAddrFind=SF_LoadDichotomyFixedFlashData(V_ProNum,V_Order,P_FixTime,C_FlashStAddr_LoadProfile,V_FlashAddrLate,V_LoadDichotomyFindWay);/* FlashST...Late*/
				}
			}
		}
	}

	return V_FlashAddrFind;
}

/*********************************************************************************
函数原型：ulong32 SF_GetFlashAddrLateRecodTolNum(ushort16 *V_NumTempTol,ushort16 V_DataLen,ulong32 V_FlashAddrLate)
功能描述：最近记录页，所记录冻结数据条数
输入参数：ushort16 *V_NumTempTol：作为输入参数时，表示还剩余的条数；作为输出参数表示通过本次查找后，剩余的条数
		ushort16 V_DataLen：每条记录数据长度
		ulong32 V_FlashAddrLate：最近记录Flash页地址
输出参数：ushort16 *V_NumTempTol
返回参数：当次数满足条件时，返回满足条件的Flash地址，此时*V_NumTempTol为0。当不满足条件时，返回全FF
功能说明：
调用机制：
备     注：该函数通过查找得到次数
*********************************************************************************/
ulong32 SF_GetFlashAddrLateRecodTolNum(ushort16 *V_NumTempTol,ushort16 V_DataLen,ulong32 V_FlashAddrLate)
{
	ulong32 V_FlashAddr32;
	ushort16 V_Len,V_NumTemp;
	uchar8 P_Data[C_698FreeData_DateLen6],V_Sign,V_i;

	V_FlashAddr32=0xFFFFFFFF;

	if((*V_NumTempTol)==0)/*正常不存在*/
	{
		return V_FlashAddr32;
	}

	V_FlashAddr32=V_FlashAddrLate&0xFFFFF000; /*页地址转化，增加容错性*/
	V_FlashAddr32=V_FlashAddr32+C_LoadProfile_RevMode;

	V_Sign=0;
	V_NumTemp=0;
	for(V_Len=0;V_Len<(C_OneFlash_PageNum-C_LoadProfile_RevMode-C_698FreeData_DateLen6);)
	{
		InF_FlashChipSelect();
		InF_ReadFlash(V_FlashAddr32,&P_Data[0],C_698FreeData_DateLen6);    /*YMDhms*/

		for(V_i=0;V_i<C_698FreeData_DateLen6;V_i++)
		{
			if(C_Flash_Empty!=P_Data[V_i])/*判断数据是否为全零，即底层为FF，没有写入数据*/
			{
				break;
			}
		}

		if(V_i>=C_698FreeData_DateLen6)/*数据全零*/
		{
			V_Sign=C_Flash_Empty68;
		}

		for(V_i=0;V_i<C_698FreeData_DateLen6;V_i++)
		{
			if(C_Flash_NoEmpty!=P_Data[V_i])/*判断数据是否为全FF，即底层为00，说明有时间调整*/
			{
				break;
			}
		}

		if(V_i>=C_698FreeData_DateLen6)/*数据全FF*/
		{
			V_Sign=C_Flash_Empty68;
		}

		if(C_Flash_Empty68!=V_Sign)
		{
			V_NumTemp+=1;/*次数+1*/
		}
		else
		{
			break;
		}

		V_Len+=V_DataLen;
		V_FlashAddr32+=V_DataLen;
	}

	if((*V_NumTempTol)<=V_NumTemp)/*次数满足要求*/
	{
		V_FlashAddr32=V_FlashAddr32-(* V_NumTempTol)*V_DataLen;
		*V_NumTempTol=0;
	}
	else
	{
		*V_NumTempTol-=V_NumTemp;
		V_FlashAddr32=0xFFFFFFFF;
	}
	return V_FlashAddr32;
}
/*********************************************************************************
函数原型：ulong32 SF_GetFlashAddrRecodTolNum(ushort16 *V_NumTempTol,ushort16 V_DataLen,ulong32 V_FlashAddr)
功能描述：某页FLash，所记录冻结数据条数
输入参数：ushort16 *V_NumTempTol：作为输入参数时，表示还剩余的条数；作为输出参数表示通过本次查找后，剩余的条数
		ushort16 V_DataLen：每条记录数据长度
		ulong32 V_FlashAddr：需处理的Flash页地址
输出参数：ushort16 *V_NumTempTol
返回参数：当次数满足条件时，返回满足条件的Flash地址，此时*V_NumTempTol为0。当不满足条件时，返回全FF
功能说明：
调用机制：
备     注：该函数主要通过计算得到次数
***********************************************************************************/
ulong32 SF_GetFlashAddrRecodTolNum(ushort16 *V_NumTempTol,ushort16 V_DataLen,ulong32 V_FlashAddr)
{
	ulong32 V_FlashAddr32;
	ushort16 V_Len,V_NumTemp;
	uchar8 P_Data[C_698FreeData_DateLen6],V_Sign,V_i;
	uchar8 P_Sign[C_LoadProfile_RevMode];

	V_FlashAddr32=0xFFFFFFFF;

	if((*V_NumTempTol)==0)/*正常不存在*/
	{
		return V_FlashAddr32;
	}

	V_FlashAddr32=V_FlashAddr&0xFFFFF000; /*页地址转化，增加容错性*/
	V_FlashAddr32=V_FlashAddr32+C_LoadProfile_RevMode;

	V_Sign=0;
	V_NumTemp=0;

	InF_FlashChipSelect();
	InF_ReadFlash((V_FlashAddr32-C_LoadProfile_RevMode),&P_Sign[0],C_LoadProfile_RevMode);    /*读修改时间标志字*/

	if(0x68==P_Sign[0])/*该页有记录写该标志为68，该页记录时间有调整，则写非68标志（同时把无效记录5字节YMDhm写为FF，即底层写0），说明该页记录时间有调整,取下1页*/
	{
		V_NumTemp=(C_OneFlash_PageNum-C_LoadProfile_RevMode)/V_DataLen;/*每页记录条数*/
		V_FlashAddr32+=V_NumTemp*V_DataLen;
	}
	else/*有时间调整*/
	{
		for(V_Len=0;V_Len<(C_OneFlash_PageNum-C_LoadProfile_RevMode-C_698FreeData_DateLen6);)
		{
			InF_FlashChipSelect();
			InF_ReadFlash(V_FlashAddr32,&P_Data[0],C_698FreeData_DateLen6);    /*YMDhms*/

			for(V_i=0;V_i<C_698FreeData_DateLen6;V_i++)
			{
				if(C_Flash_NoEmpty!=P_Data[V_i])/*判断数据是否为全FF，即底层为00，s说明有时间调整*/
				{
					break;
				}
			}

			if(V_i>=C_698FreeData_DateLen6)/*数据全FF*/
			{
				V_Sign=C_Flash_Empty68;
			}

			if(C_Flash_Empty68!=V_Sign)
			{
				V_NumTemp+=1;/*次数+1*/
			}
			else
			{
				break;
			}

			V_Len+=V_DataLen;
			V_FlashAddr32+=V_DataLen;
		}
	}

	if((*V_NumTempTol)<=V_NumTemp)/*次数满足要求*/
	{
		V_FlashAddr32=V_FlashAddr32-(* V_NumTempTol)*V_DataLen;
		*V_NumTempTol=0;
	}
	else
	{
		*V_NumTempTol-=V_NumTemp;
		V_FlashAddr32=0xFFFFFFFF;
	}

	return V_FlashAddr32;
}
/*********************************************************************************
函数原型：ulong32 SF_GetFlashAddrSatisfyNum(uchar8 V_ProNum,uchar8 V_Order,ushort16 V_Num)
功能描述：获取满足次数的某类冻结数据Flash地址
输入参数：uchar8 V_ProNum：分钟冻结用方案号。非分钟冻结，该入口方案号为全零
		uchar8 V_Order：某类冻结数据在Str_698FreezeDataTable中序号
		ushort16 V_Num：抄读次数
输出参数：无
返回参数：ulong32满足次数要求的Flash地址，异常为0xFFFFFFFF
功能说明：
调用机制：
备     注：FlashST---Ear...Late---FlashEnd(时间调整会出现);Ear...Late---FlashEnd;FlashST...Late---Ear...FlashEnd
*********************************************************************************/
ulong32 SF_GetFlashAddrSatisfyNum(uchar8 V_ProNum,uchar8 V_Order,ushort16 V_Num)
{
	ushort16 V_E2Addr_LoadP_Flash_Late,V_E2Addr_LoadP_Flash_Ear,V_DataLen,V_NumTempTol;
	ulong32 V_FlashStAddr_LoadProfile,V_FlashEndAddr_LoadProfile,V_FlashAddr32Temp,V_FlashAddr32;
	uchar8 V_DI2,V_ucReturn,V_FlashAddr8[4];
	ulong32 V_FlashAddrLate,V_FlashAddrEar;
	uchar8 V_DI2Temp;

	V_FlashAddr32Temp=0xFFFFFFFF;

	if(V_Order>=Str_698FreezeDataTable_Len)/*异常判断*/
	{
		return V_FlashAddr32Temp;
	}

	V_E2Addr_LoadP_Flash_Late=Str_698FreezeDataTable[V_Order].V_E2AddrLate;
	V_E2Addr_LoadP_Flash_Ear=Str_698FreezeDataTable[V_Order].V_E2AddrEar;
	V_FlashStAddr_LoadProfile=Str_698FreezeDataTable[V_Order].V_StaFlashAddr;
	V_FlashEndAddr_LoadProfile=Str_698FreezeDataTable[V_Order].V_EndFlashAddr;
	V_DI2=Str_698FreezeDataTable[V_Order].V_DI2;
	V_DI2Temp=(uchar8)((C_RelatedOAD_Min&0x00FF0000)>>16);

	if(V_DI2Temp==V_DI2)/*分钟冻结*/
	{
		V_ucReturn=SF_GetMinFreezePro_E2andFlashAddr(V_ProNum,&V_FlashStAddr_LoadProfile,&V_FlashEndAddr_LoadProfile,&V_E2Addr_LoadP_Flash_Ear,&V_E2Addr_LoadP_Flash_Late);/*根据分钟冻结方案号，获取该方案最近、最早记录E2地址及该方案起始、结束Flash地址*/
		if(C_OK!=V_ucReturn)
		{
			return V_FlashAddr32Temp;
		}
	}

	V_DI2Temp=(V_DI2&0x1F);/*增加方案号，非分钟冻结该方案号，入口为0*/
	V_DI2Temp |= (V_ProNum<<5);
	V_DataLen=SF_JudgeWriteDataLen(V_DI2Temp);
	if(0==V_DataLen)/*异常判断*/
	{
		return V_FlashAddr32Temp;
	}

	V_ucReturn = SF_ReadE2Three(V_E2Addr_LoadP_Flash_Late,4,&V_FlashAddr8[0]);        /*取最近1条记录Flash页地址*/
	if(V_ucReturn != C_OK)
	{
		return V_FlashAddr32Temp;
	}

	PF_Buffer4ToUlong32(&V_FlashAddr8[0],&V_FlashAddrLate,4);
	V_FlashAddrLate&=0xFFFFF000;             /*页地址转化，增加容错性*/

	V_ucReturn = SF_ReadE2Three(V_E2Addr_LoadP_Flash_Ear,4,&V_FlashAddr8[0]);         /*取最早1条记录Flash地址*/
	if(V_ucReturn != C_OK)
	{
		return	V_FlashAddr32Temp;
	}

	PF_Buffer4ToUlong32(&V_FlashAddr8[0],&V_FlashAddrEar,4);

	if(V_FlashAddrEar==V_FlashAddrLate)/*没有冻结数据*/
	{
		return	V_FlashAddr32Temp;
	}

	V_NumTempTol=V_Num;

	if(V_FlashAddrLate>=(V_FlashAddrEar-C_LoadProfile_RevMode))/*FlashST---Ear...Late---FlashEnd; Ear...Late---FlashEnd;*/
	{
		V_FlashAddr32=V_FlashAddrLate;
		while(V_FlashAddr32>=(V_FlashAddrEar-C_LoadProfile_RevMode))
		{
			if(V_FlashAddr32==V_FlashAddrLate)
			{
				V_FlashAddr32Temp=SF_GetFlashAddrLateRecodTolNum(&V_NumTempTol,V_DataLen,V_FlashAddr32);
			}
			else
			{
				V_FlashAddr32Temp=SF_GetFlashAddrRecodTolNum(&V_NumTempTol,V_DataLen,V_FlashAddr32);
			}

			if((0==V_NumTempTol)&&(0xFFFFFFFF!=V_FlashAddr32Temp))/*找到满足次数数据项*/
			{
				break;
			}

			if(V_FlashAddr32>=C_OneFlashPage)/*增加V_FlashAddr32地址为零判断，查找到头*/
			{
				V_FlashAddr32=V_FlashAddr32-C_OneFlashPage;
			}
			else
			{
				break;
			}
		}
	}
	else /*FlashST...Late---Ear...FlashEnd*/
	{
		V_FlashAddr32=V_FlashAddrLate;
		while(V_FlashAddr32>=V_FlashStAddr_LoadProfile)
		{
			if(V_FlashAddr32==V_FlashAddrLate)
			{
				V_FlashAddr32Temp=SF_GetFlashAddrLateRecodTolNum(&V_NumTempTol,V_DataLen,V_FlashAddr32);
			}
			else
			{
				V_FlashAddr32Temp=SF_GetFlashAddrRecodTolNum(&V_NumTempTol,V_DataLen,V_FlashAddr32);
			}

			if((0==V_NumTempTol)&&(0xFFFFFFFF!=V_FlashAddr32Temp))/*找到满足次数数据项*/
			{
				break;
			}

			if(V_FlashAddr32>=C_OneFlashPage)/*增加V_FlashAddr32地址为零判断，查找到头*/
			{
				V_FlashAddr32=V_FlashAddr32-C_OneFlashPage;
			}
			else
			{
				break;
			}
		}

		if((0!=V_NumTempTol)&&(0xFFFFFFFF==V_FlashAddr32Temp))/*没有找到满足次数数据项*/
		{
			V_FlashAddr32=V_FlashEndAddr_LoadProfile;
			while(V_FlashAddr32>=(V_FlashAddrEar-C_LoadProfile_RevMode))
			{
				V_FlashAddr32Temp=SF_GetFlashAddrRecodTolNum(&V_NumTempTol,V_DataLen,V_FlashAddr32);

				if((0==V_NumTempTol)&&(0xFFFFFFFF!=V_FlashAddr32Temp))/*找到满足次数数据项*/
				{
					break;
				}

				if(V_FlashAddr32>=C_OneFlashPage)/*增加V_FlashAddr32地址为零判断，查找到头*/
				{
					V_FlashAddr32=V_FlashAddr32-C_OneFlashPage;
				}
				else
				{
					break;
				}
			}
		}
	}
	return V_FlashAddr32Temp;
}
/*******************************************************************************
函数原型：uchar8 SF_GetFrozenDataLen(ushort16 V_ucLineNum)
功能描述：获取冻结数据的长度
输入参数：V_ucLineNum：Str_FrozenConvert_Table[]的行号
输出参数：数据的长度
返回参数：
调用位置：
备     注：查表 Str_FrozenConvert_Table，找到数据的长度
		费率电能根据设置的费率数应答
*******************************************************************************/
uchar8 SF_GetFrozenDataLen(ushort16 V_ucLineNum)
{
	uchar8 V_ucDataLen, V_ucNum;

	V_ucNum = InF_RateNumChangeToHex();
	if(Str_FrozenConvert_Table[V_ucLineNum].V_uc698RateNumMethod == C_NeedRateNum_FF)
	{
		V_ucNum += 1;/*总+费率，比费率数多一个*/
		V_ucDataLen = V_ucNum * (Str_FrozenConvert_Table[V_ucLineNum + 1].V_uc645Length); /*表格Str_FrozenConvert_Table顺序关联，数据块 ，总，费率，所以用分项的数据长度计算*/
	}
	else if(Str_FrozenConvert_Table[V_ucLineNum].V_uc698RateNumMethod == C_NeedRateNumPrice_FF)
	{
		V_ucDataLen = V_ucNum * (Str_FrozenConvert_Table[V_ucLineNum + 1].V_uc645Length); /*表格Str_FrozenConvert_Table顺序关联，数据块 ，总，费率，所以用分项的数据长度计算*/
	}
	else
	{
		V_ucDataLen = Str_FrozenConvert_Table[V_ucLineNum].V_uc645Length; /*表格Str_FrozenConvert_Table自身长度*/
	}
	return V_ucDataLen;
}
/*******************************************************************************
函数原型：uchar8 SF_FrozenData_JudgeRateNum(ushort16 V_ucLineNum, ulong32 V_ulOAD)
功能描述：判断单独读取的费率电能、需量费率电价等数据费率有没有超过设置的费率数
输入参数：V_ucLineNum：Str_FrozenConvert_Table[]的行号;V_ulOAD:读取的ROAD
输出参数：
返回参数：超过费率数C_Error,没有超过C_OK
调用位置：
备    注：
*******************************************************************************/
uchar8 SF_FrozenData_JudgeRateNum(ushort16 V_ucLineNum, ulong32 V_ulOAD)
{
	uchar8 V_ucNum, V_ucReturn = C_OK;
	uchar8 V_ucData[4];

	PF_Ulong32ToBuffer4(V_ucData, &V_ulOAD, 4);

	V_ucNum = InF_RateNumChangeToHex();

	if(Str_FrozenConvert_Table[V_ucLineNum].V_uc698RateNumMethod == C_NeedRateNum)
	{
		V_ucNum += 1;				/*总+费率，比费率数多一个*/
		if(V_ucData[0] > V_ucNum)	/*DI0为索引*/
		{
			V_ucReturn = C_Error;
		}
	}
	else if(Str_FrozenConvert_Table[V_ucLineNum].V_uc698RateNumMethod == C_NeedRateNumPrice)
	{
		if(V_ucData[0] > V_ucNum)
		{
			V_ucReturn = C_Error;
		}
	}
	else
	{
		V_ucReturn = C_OK;
	}

	return V_ucReturn;
}
/*******************************************************************************
函数原型：uchar8 SF_OrganData(ulong32 *P_Data_Id_OAD,uchar8 V_ProNum,uchar8 V_i,ushort16 *P_TotalLen,ushort16 *P_Length,
						ulong32 V_FindFlashAddr,uchar8 *P_Data,ushort16 V_DataLen,uchar8 *pV_FreezeTimeBuf,uchar8 V_Mode)
功能描述：根据OAD序号表，组织所超度数据。不支持的OAD返回1字节C_NotSupportAOD_DataBB 0xBB，
		与模块写记录时，读数据层读不到返回0xAA C_NotSupportAOD_Data作区分
输入参数：uchar8 V_ProNum：分钟冻结用方案号
		uchar8 V_Order：某类冻结数据在Str_698FreezeDataTable中序号
		ulong32 *P_Data_Id_OAD：某类冻结数据在Str_698FreezeDataTable中序号。关联属性对应OAD顺序，当查找OAD为FFFFFFFF则表示，该条记录读取记录OAD结束
		uchar8 V_Order：某类冻结数据在Str_698FreezeDataTable中序号
		ushort16 *P_TotalLen：作为输入为已组织数据总长度，输出包含本次组织数据长度后的总长度
		ushort16 *P_Length：作为输入为剩余缓存长度，输出包含本次组织数据长度后剩余缓存总长度
		ulong32 V_FindFlashAddr：所读记录数据Flash地址;
		uchar8 *P_Data：所读记录数据存放缓存,字节采用读数据带过来的缓存;
		ushort16 V_DataLen:该条冻结记录总长度，行读用。
输出参数：uchar8 *pV_FreezeTimeBuf：返回最近n条，冻结时间，通信读后续帧判断用；
返回参数：C_OK、C_IICError、C_Error、C_DataLenError、C_IDError、C_NoData
调用位置：
备     注：内部返回值注意C_NotSupportAOD_DataBB、C_NotSupportAOD_DataCC
*******************************************************************************/
uchar8 SF_OrganData(ulong32 * P_Data_Id_OAD,uchar8 V_ProNum,uchar8 V_i,ushort16 * P_TotalLen,ushort16 * P_Length,ulong32 V_FindFlashAddr,uchar8 * P_Data,ushort16 V_DataLen,uchar8 * pV_FreezeTimeBuf,uchar8 V_Mode)
{
	ushort16 V_Data_Length,V_Data_LengthOff,V_Data_LengthOffnei;
	uchar8 P_DataOAD_NumTab[C_698Free_OADTabLen];
	uchar8 P_OADTabLen_T[CLI_Free_OADTabLen_T];
	ushort16 V_Order,V_OADTabLen_T,V_OADOrder16,V_j,V_k,V_EventSign;
	uchar8 V_Return_Flag,V_ucAAFlag=0;
	Str_3aTable V_Str_3aTable;
	ulong32 V_FlashAddr;
	ushort16 V_TotalLen;
	ushort16 V_Length;
	uchar8 V_Date1[C_698FreeData_DateLen6];
	uchar8 V_ucFrozenConver645Len;
	uchar8 V_ucRateNumJudge = C_RateNumOK;
	uchar8 V_ucEnergy02Flag = 0;
	ulong32 V_ulSaveOAD;
	uchar8 V_ucEnergyNum;
	uchar8 V_uci, V_ucEnergyChgeLen = 0, V_ucResultEnergyChgeLen = 0;
	uchar8 V_DI2Temp;
	uchar8 V_OADNum = 0, V_NullNum = 0, V_NullNumCC = 0, V_ucAAFlagTemp;
	uchar8 V_TimeNum = 0;   /*查找OAD中，包含的冻结时间及序号的个数*/
	ushort16 V_jTemp = 0;
	uchar8 V_DataLenTemp, V_Data_LengthOffTemp = 0, i;
	ulong64 V_ulEnergyData = 0;

	V_TotalLen = *P_TotalLen;
	V_Length = *P_Length;

	if(V_i >= Str_698FreezeDataTable_Len)   /*异常判断*/
	{
		return C_Error;
	}

	V_Order = Str_698FreezeDataTable[V_i].V_LineNumLen_T;       /*698冻结长度、周期数据项所在Str_3aTable行号*/
	if(V_Order >= Str_3aTable_E23RAM_Len)
	{
		return C_Error;        /*异常*/
	}

	V_Data_Length = 0;
	V_Str_3aTable = Str_3aTable_E23RAM[V_Order];

	V_Return_Flag = SF_Re_E23_RAM_Data698(&V_Str_3aTable, CLI_Free_OADTabLen_T, &P_OADTabLen_T[0]);
	if(C_OK == V_Return_Flag)
	{
		V_OADTabLen_T = P_OADTabLen_T[0];
		V_OADTabLen_T = V_OADTabLen_T * C_698Free_OADTabDataType;    /*序号表每个OAD序号C_698Free_OADTabDataType个字节,目前6字节。2字节序号+2字节冻结周期+2字节存储深度*/
		if(V_OADTabLen_T > C_698Free_OADTabLen)                      /*数据长度安全性判断*/
		{
			return C_Error;    /*异常*/
		}

		V_Order = Str_698FreezeDataTable[V_i].V_LineNumTab;          /*698冻结序号表所在Str_3aTable行号*/
		if(V_Order >= Str_3aTable_E23RAM_Len)
		{
			return 	C_Error;    /*异常*/
		}

		V_Str_3aTable = Str_3aTable_E23RAM[V_Order];
		V_Return_Flag = SF_Re_E23_RAM_Data698(&V_Str_3aTable, V_OADTabLen_T, &P_DataOAD_NumTab[0]);
		if(C_OK != V_Return_Flag)
		{
			return C_Error;    /*异常*/
		}

		V_DI2Temp = (uchar8)((C_RelatedOAD_Min & 0x00FF0000) >> 16);    /*分钟冻结*/
		if(V_DI2Temp == (Str_698FreezeDataTable[V_i].V_DI2))
		{
			V_OADTabLen_T = SF_GetMinFreezeNum_OADTab(V_ProNum,&P_DataOAD_NumTab[0],V_OADTabLen_T);     /*获取分钟冻结方案号，对应的OAD关联列表及关联OAD个数*/
			if(0xFFFF == V_OADTabLen_T)
			{
				return C_Error;    /*异常*/
			}
		}
		else
		{
			V_OADTabLen_T = V_OADTabLen_T / C_698Free_OADTabDataType;           /*序号表每个OAD序号C_698Free_OADTabDataType个字节,目前6字节。2字节序号+2字节冻结周期+2字节存储深度*/
		}

		V_Data_Length = 0;					/*修改不固定返回日期+序号*/
		V_Data_LengthOff = V_Data_Length;   /*记录数据偏移*/

		while( 0xFFFFFFFF != (*P_Data_Id_OAD) )
		{
			/*查询冻结时间及序号。区分分钟冻结及其他冻结*/
			V_jTemp = 0;
			V_ucAAFlagTemp = 0x55;
            V_Data_LengthOffTemp = 0;
            switch( *P_Data_Id_OAD )
            {
                case CFreeTime:     /*冻结时间*/
                {
                    V_ucAAFlagTemp = 0xAA;
                    V_DataLenTemp = C_698FreeData_DateLen6;
                    V_TimeNum++;

                }break;
                case CFreeNum:      /*冻结序号*/
                {
                    V_ucAAFlagTemp = 0xAA;
                    V_DataLenTemp = C_698FreeData_SequenceLen4;
                    V_TimeNum++;
                    V_Data_LengthOffTemp = C_698FreeData_DateLen6;      /*冻结记录存储格式为时间日期+序号*/

                }break;
                default:
                {
                    V_jTemp = 2;
                }break;

            }

            if( V_ucAAFlagTemp == 0xAA )
            {
                if( (*P_Length) >= V_DataLenTemp )
                {
                    V_FlashAddr = V_FindFlashAddr + V_Data_LengthOffTemp;
                    InF_FlashChipSelect();
                    InF_ReadFlash(V_FlashAddr, &P_Data[V_Data_Length], V_DataLenTemp);    /*读记录数据*/
                    (*P_Length) -= V_DataLenTemp;
                    V_Data_Length += V_DataLenTemp;
                    V_ucAAFlag = 0x68;
                }
                else
                {
                    return 	C_DataLenError;
                }
            }

			/*查询关联列表*/
			V_j = 0;
			if ( ( V_ucAAFlagTemp !=0xAA ) && ( V_OADTabLen_T <= C_FreezeMAXRelatedOAD ) )   /*冻结时间、序号，查不到，接着查询关联列表*/
			{
				V_Data_LengthOff = (C_698FreeData_SequenceLen4 + C_698FreeData_DateLen6);
				V_ucAAFlag = 0;

				for(    ; V_j < V_OADTabLen_T; V_j++)
				{
					PF_Buffer2ToUshort16(&P_DataOAD_NumTab[C_698Free_OADTabDataType * V_j], &V_OADOrder16);
					V_EventSign = (V_OADOrder16 & 0xE000);    /*根据698 OAD，DI1高3位表示不同属性，与设计方式有关*/
					V_OADOrder16 &= 0x1FFF;
					if(V_OADOrder16 >= Str_FrozenConvert_Table_Len)
					{
						return 	C_Error;    /*异常，正常不存在*/
					}

                    V_ucEnergy02Flag = 0;
                    if ( ( (*P_Data_Id_OAD) & 0xFF000F00 ) == 0x00000200 )    /*读取的是02属性电能*/
                    {
                        V_ucEnergy02Flag = C_ReadRelated02Energy;

                        if( ( ( Str_FrozenConvert_Table[V_OADOrder16].V_ulOAD ) & 0x00000F00 ) == 0x00000400 )  /*存储的是04属性电能*/
                        {
                            V_ucEnergy02Flag |= C_SaveRelated04Energy;
                            V_ulSaveOAD = (Str_FrozenConvert_Table[V_OADOrder16].V_ulOAD & 0xFFFF00FF) | 0x00000200;
                            if ( ( *P_Data_Id_OAD ) == ( V_ulSaveOAD | V_EventSign ) )
                            {
                                V_ucEnergy02Flag |= C_EnergyPlanSame;
                            }
                        }
                    }   /*else初始化已赋值0*/

					if ( ( (*P_Data_Id_OAD) == ( Str_FrozenConvert_Table[V_OADOrder16].V_ulOAD | V_EventSign ) )         /*单独OAD相等*/
                      || ( V_ucEnergy02Flag == ( C_ReadRelated02Energy | C_SaveRelated04Energy | C_EnergyPlanSame ) ) )  /*存04属性电能，用02属性读*/
					{
                        if( SF_FrozenData_JudgeRateNum(V_OADOrder16, *P_Data_Id_OAD) == C_Error )
                        {
                            V_ucRateNumJudge = C_RateNumError;
                            break;
                        }  /*费率数未超正常应答*/

                        V_ucFrozenConver645Len = SF_GetFrozenDataLen(V_OADOrder16);
						if( (*P_Length) >= V_ucFrozenConver645Len )
						{
                            V_FlashAddr = V_FindFlashAddr + V_Data_LengthOff;
							InF_FlashChipSelect();
							InF_ReadFlash(V_FlashAddr, &P_Data[V_Data_Length], V_ucFrozenConver645Len);    /*读记录数据*/
                            /*读02属性电能，存储为4为小数电能，数据转换*/
                            if( V_ucEnergy02Flag == ( C_ReadRelated02Energy | C_SaveRelated04Energy | C_EnergyPlanSame ) )  /*存04属性电能，用02属性读*/
                            {
                                V_ucEnergyNum = V_ucFrozenConver645Len / C_AccurateEnergyCommLen;
                                V_ucEnergyChgeLen = 0;
                                V_ucResultEnergyChgeLen = 0;
                                for(V_uci = 0; V_uci < V_ucEnergyNum; V_uci++)
                                {
									V_ulEnergyData = 0;
									if( (P_Data[V_Data_Length + V_ucEnergyChgeLen] & 0x80) == 0x80)
									{
										for(i = C_AccurateEnergyCommLen; i < 8; i++)
										{
											V_ulEnergyData <<= 8;
											V_ulEnergyData |= 0xFF;
										}
										for(i = 0; i < C_AccurateEnergyCommLen; i++)
										{
											V_ulEnergyData <<= 8;
											V_ulEnergyData |= P_Data[V_Data_Length + V_ucEnergyChgeLen + i];
										}
										V_ulEnergyData = (~V_ulEnergyData) + 1;
									}
									else
									{
										for(i = 0; i < C_AccurateEnergyCommLen; i++)
										{
											V_ulEnergyData <<= 8;
											V_ulEnergyData |= P_Data[V_Data_Length + V_ucEnergyChgeLen + i];
										}
									}
									V_ulEnergyData /= 100;
									if( (P_Data[V_Data_Length + V_ucEnergyChgeLen] & 0x80) == 0x80)
									{
										V_ulEnergyData = (~V_ulEnergyData) + 1;
									}
									PF_Ulong64ToBuffer8_698(&P_Data[V_Data_Length + V_ucResultEnergyChgeLen], &V_ulEnergyData, C_EnergyCommLen);
                                    /*memcpy( &P_Data[V_Data_Length + V_ucResultEnergyChgeLen], &P_Data[V_Data_Length + 1 + V_ucEnergyChgeLen], C_EnergyCommLen);*/
                                    V_ucEnergyChgeLen += C_AccurateEnergyCommLen;
                                    V_ucResultEnergyChgeLen += C_EnergyCommLen;
                                }
                                V_ucFrozenConver645Len = V_ucResultEnergyChgeLen;
                            }

							(*P_Length) -= V_ucFrozenConver645Len;
							V_Data_Length += V_ucFrozenConver645Len;
							V_ucAAFlag = 0x68;
							break;
						}
						else
						{
							return 	C_DataLenError;
						}
					}
					else
					{
						if( C_array == Str_FrozenConvert_Table[V_OADOrder16].V_uc698Type )    /*数组格式OAD,查询是否为分OAD*/
						{
							V_Data_LengthOffnei = 0;

							for( V_k = 0;    ; V_k++ )
							{
								if( ( V_OADOrder16 + V_k + 1 ) >= Str_FrozenConvert_Table_Len )
								{
									return 	C_Error;        /*异常，正常不存在*/
								}

								if ( ( Str_FrozenConvert_Table[V_OADOrder16 + V_k + 1].V_ulOAD & 0xFFFFFF00 )
                                  == ( Str_FrozenConvert_Table[V_OADOrder16].V_ulOAD & 0xFFFFFF00 ) )
								{
                                    V_ucEnergy02Flag = 0;
                                    if ( ( (*P_Data_Id_OAD) & 0xFF000F00 ) == 0x00000200 )    /*读取的是02属性电能*/
                                    {
                                        V_ucEnergy02Flag = C_ReadRelated02Energy;

                                        if( ( ( Str_FrozenConvert_Table[V_OADOrder16 + V_k + 1].V_ulOAD ) & 0x00000F00 ) == 0x00000400 )  /*存储的是04属性电能*/
                                        {
                                            V_ucEnergy02Flag |= C_SaveRelated04Energy;
                                            V_ulSaveOAD = ( Str_FrozenConvert_Table[V_OADOrder16 + V_k + 1].V_ulOAD & 0xFFFF00FF ) | 0x00000200;
                                            if ( ( *P_Data_Id_OAD ) == ( V_ulSaveOAD | V_EventSign ) )    /*方案是否相同*/
                                            {
                                                V_ucEnergy02Flag |= C_EnergyPlanSame;
                                            }
                                        }
                                    }   /*else初始化已赋值0*/

									if ( ( (*P_Data_Id_OAD) == ( Str_FrozenConvert_Table[V_OADOrder16 + V_k + 1].V_ulOAD | V_EventSign ) )
                                      || ( V_ucEnergy02Flag == ( C_ReadRelated02Energy | C_SaveRelated04Energy | C_EnergyPlanSame ) ) )
									{
                                        if( SF_FrozenData_JudgeRateNum((V_OADOrder16 + V_k + 1), *P_Data_Id_OAD) == C_Error )
                                        {
                                             V_ucRateNumJudge = C_RateNumError;
                                             break;
                                        }    /*费率数未超正常应答*/

                                        V_ucFrozenConver645Len = SF_GetFrozenDataLen(V_OADOrder16 + V_k + 1);
										if( (*P_Length) >= V_ucFrozenConver645Len )
										{
											V_FlashAddr = V_FindFlashAddr + V_Data_LengthOff + V_Data_LengthOffnei;
											InF_FlashChipSelect();
											InF_ReadFlash(V_FlashAddr,&P_Data[V_Data_Length], V_ucFrozenConver645Len);    /*读记录数据*/

                                            /*读02属性电能，存储为4为小数电能，数据转换*/
                                            if( V_ucEnergy02Flag == ( C_ReadRelated02Energy | C_SaveRelated04Energy | C_EnergyPlanSame ) )  /*存04属性电能，用02属性读*/
                                            {
												V_ucEnergyNum = V_ucFrozenConver645Len / C_AccurateEnergyCommLen;
												V_ucEnergyChgeLen = 0;
												V_ucResultEnergyChgeLen = 0;
												for(V_uci = 0; V_uci < V_ucEnergyNum; V_uci++)
												{
													V_ulEnergyData = 0;
													if( (P_Data[V_Data_Length + V_ucEnergyChgeLen] & 0x80) == 0x80)
													{
														for(i = C_AccurateEnergyCommLen; i < 8; i++)
														{
															V_ulEnergyData <<= 8;
															V_ulEnergyData |= 0xFF;
														}
														for(i = 0; i < C_AccurateEnergyCommLen; i++)
														{
															V_ulEnergyData <<= 8;
															V_ulEnergyData |= P_Data[V_Data_Length + V_ucEnergyChgeLen + i];
														}
														V_ulEnergyData = (~V_ulEnergyData) + 1;
													}
													else
													{
														for(i = 0; i < C_AccurateEnergyCommLen; i++)
														{
															V_ulEnergyData <<= 8;
															V_ulEnergyData |= P_Data[V_Data_Length + V_ucEnergyChgeLen + i];
														}
													}
													V_ulEnergyData /= 100;
													if( (P_Data[V_Data_Length + V_ucEnergyChgeLen] & 0x80) == 0x80)
													{
														V_ulEnergyData = (~V_ulEnergyData) + 1;
													}
													PF_Ulong64ToBuffer8_698(&P_Data[V_Data_Length + V_ucResultEnergyChgeLen], &V_ulEnergyData, C_EnergyCommLen);
													/*memcpy( &P_Data[V_Data_Length + V_ucResultEnergyChgeLen], &P_Data[V_Data_Length + 1 + V_ucEnergyChgeLen], C_EnergyCommLen);*/
													V_ucEnergyChgeLen += C_AccurateEnergyCommLen;
													V_ucResultEnergyChgeLen += C_EnergyCommLen;
												}
#if 0		/*原来BCD码直接移位*/
                                                V_ucEnergyNum = V_ucFrozenConver645Len / C_AccurateEnergyCommLen;
                                                V_ucEnergyChgeLen = 0;
                                                V_ucResultEnergyChgeLen = 0;
                                                for(V_uci = 0; V_uci < V_ucEnergyNum; V_uci++)
                                                {
                                                    memcpy( &P_Data[V_Data_Length + V_ucResultEnergyChgeLen], &P_Data[V_Data_Length + 1 + V_ucEnergyChgeLen], C_EnergyCommLen);
                                                    V_ucEnergyChgeLen += C_AccurateEnergyCommLen;
                                                    V_ucResultEnergyChgeLen += C_EnergyCommLen;
                                                }
#endif
                                                V_ucFrozenConver645Len = V_ucResultEnergyChgeLen;
                                            }

											(*P_Length) -= V_ucFrozenConver645Len;
											V_Data_Length += V_ucFrozenConver645Len;
											V_ucAAFlag = 0x68;
											break;
										}
										else
										{
											return 	C_DataLenError;
										}
									}
									else
									{
										V_Data_LengthOffnei+=Str_FrozenConvert_Table[V_OADOrder16+V_k+1].V_uc645Length;
									}
								}
								else
								{
									break;
								}
							}
							if(V_ucAAFlag == 0x68)
							{
								break;
							}
						}
					}
					V_Data_LengthOff += Str_FrozenConvert_Table[V_OADOrder16].V_uc645Length;          /*数据偏移*/
				}
			}

			V_jTemp += V_j;

			if( ( V_jTemp >= ( V_OADTabLen_T + 2 ) ) || ( V_ucRateNumJudge == C_RateNumError ) )    /*不存在补1字节0*/
			{
				if( V_ucAAFlag != 0x68 )
				{
					if((* P_Length) >= 1)
					{
						P_Data[V_Data_Length] = C_NotSupportAOD_DataBB;    /*读记录数据*/
						(*P_Length) -= 1;
						V_Data_Length += 1;
						V_NullNum++;
						V_NullNumCC++;
					}
					else
					{
						return 	C_DataLenError;
					}
				}
			}
			P_Data_Id_OAD++;
			V_OADNum++;
		}

		if(V_DI2Temp == (Str_698FreezeDataTable[V_i].V_DI2))    /*判断分钟冻结*/
		{
			V_OADNum -= V_TimeNum;    /*假如有冻结日期、序号，则去除该OAD判断有效性*/
		}

		if(V_NullNumCC >= V_OADNum)   /*所有的列选OAD全部查不到，外面判断用*/
		{
            if( (V_DI2Temp == (Str_698FreezeDataTable[V_i].V_DI2) ) && (0 != V_TimeNum))    /*分钟冻结且所读OAD中包含日期或序号+其他关联列表中不存在OAD.其他冻结外面的if判断不成立*/
            {
                V_Return_Flag = C_OK;
                (*P_TotalLen) += V_Data_Length;
                InF_FlashChipSelect();
                InF_ReadFlash(V_FindFlashAddr, &V_Date1[0], C_698FreeData_DateLen6);        /*读记录数据*/
                InF_WriteFreezeTimeToBufer(pV_FreezeTimeBuf, &V_Date1[0], V_Mode);
            }
            else
            {
                V_Return_Flag = C_NotSupportAOD_DataCC;
                *P_TotalLen = V_TotalLen;
                *P_Length = V_Length;
            }
            return V_Return_Flag;
		}
		else
		{
			if(V_NullNum >= V_OADNum)   /*不会出现不同周期数据，技术规范规定。没有有效的OAD数据*/
			{
                V_Return_Flag = C_NotSupportAOD_DataBB;
                *P_TotalLen = V_TotalLen;
                *P_Length = V_Length;
                return V_Return_Flag;
			}
		}
	}
	else
	{
		return V_Return_Flag;
	}

	InF_FlashChipSelect();
	InF_ReadFlash(V_FindFlashAddr,&V_Date1[0], C_698FreeData_DateLen6);    /*读记录数据*/
	InF_WriteFreezeTimeToBufer(pV_FreezeTimeBuf, &V_Date1[0], V_Mode);
	(*P_TotalLen) += V_Data_Length;
	return C_OK;
}
/*********************************************************************************
函数原型：uchar8 SF_Find2EventTable_Data(ulong32 V_Data_Id,Str_2Table *PStr_2Table,ushort16 *P_Line,ushort16 V_MaxLine)
功能描述：2级表查询函数，得到DI2-DI0对应的2级表行号
输入参数：ulong32 V_Data_Id：数据标识码DI2~DI0；
		Str_2Table *PStr_2Table：1级表查询中对应2级表结构体地址；
		ushort16 V_MaxLine:对应2级表结构体数组长度
输出参数：ushort16 *P_Line：查找2级表对应行号；
返回参数：C_OK、C_IDError、C_DataLenError、C_NoAccess；
功能说明：
调用机制：
备     注：
*********************************************************************************/
uchar8 SF_Find2EventTable_Data(ulong32 V_Data_Id,Str_2Table *PStr_2Table,ushort16 *P_Line,ushort16 V_MaxLine)
{
	ushort16 V_Line;

	for(V_Line=0;V_Line<V_MaxLine;V_Line++)
	{
		if(V_Data_Id==PStr_2Table[V_Line].V_DI)
		{
			break;
		}
		else
		{
			if(DT_Flash_DI04==PStr_2Table[V_Line].V_DT_Type)/*Flash，带次数数据，DI0低4位表示次数，高4位表示不同标识码(查询4级表用)*/
			{
				if(0x00000000==(V_Data_Id&0x0000000F))  /*次数不为0*/
				{
					continue;
				}

				if((V_Data_Id&0xFFFFFFF0)==(PStr_2Table[V_Line].V_DI&0xFFFFFFF0)) /*DI0低4位不比较*/
				{
					break;
				}
			}
			else
			{
				if( (DT_Flash_Tol_DI0_DI1==PStr_2Table[V_Line].V_DT_Type)/*||(DT_Flash_Tol_DI0_DI2==PStr_2Table[V_Line].V_DT_Type)
					|| (DT_Flash_Tol_DI0_SettEn==PStr_2Table[V_Line].V_DT_Type)||(DT_Flash_Tol_DI0_SettDe==PStr_2Table[V_Line].V_DT_Type)
					|| (DT_Flash_Tol_DI0_W_Sett_En==PStr_2Table[V_Line].V_DT_Type)||(DT_R_Flash_Tol_DI0_DI2_En==PStr_2Table[V_Line].V_DT_Type)*/
					|| (DT_Flash_Tol_DI0==PStr_2Table[V_Line].V_DT_Type) )  /*DI0表示次数*/
				{
					if(0x00000000==(V_Data_Id&0x000000FF))  /*次数不为0*/
					{
						continue;
					}

					if((V_Data_Id&0xFFFFFF00)==(PStr_2Table[V_Line].V_DI&0xFFFFFF00)) /*DI0不比较*/
					{
						break;
					}
				}
				else
				{
					if((DT_RAM_DI0==PStr_2Table[V_Line].V_DT_Type)||(DT_Ref_E23_RAMCRC_DI0==PStr_2Table[V_Line].V_DT_Type)
						||(DT_E23_DI0==PStr_2Table[V_Line].V_DT_Type)||(DT_E21CRC_DI0==PStr_2Table[V_Line].V_DT_Type)
						||(DT_E21_DI0==PStr_2Table[V_Line].V_DT_Type)||(DT_Ref_E23_RAMCRC_DI0_2==PStr_2Table[V_Line].V_DT_Type))  /*只列DI0最大值，且DI0不为0*/
					{
						if((V_Data_Id&0xFFFFFF00)==(PStr_2Table[V_Line].V_DI&0xFFFFFF00))/*DI0不比较*/
						{
							if((0x00000000!=(V_Data_Id&0x000000FF))                    /*DI0不为零，且≤最大值*/
								&&((V_Data_Id&0x000000FF)<=(PStr_2Table[V_Line].V_DI&0x000000FF)))
							{
								break;
							}
						}
					}
					else
					{
#if 0
						if(DT_RAM_DI1_0==PStr_2Table[V_Line].V_DT_Type)    /*只列DI1最大值，DI1可以为0*/
						{
							if((V_Data_Id&0xFFFF00FF)==(PStr_2Table[V_Line].V_DI&0xFFFF00FF))/*DI1不比较*/
							{
								if((V_Data_Id&0x0000FF00)<=(PStr_2Table[V_Line].V_DI&0x0000FF00))/*DI1＜=最大值*/
								{
									break;
								}
							}
						}
						else
						{

							if(DT_RAM_DI1==PStr_2Table[V_Line].V_DT_Type)    /*只列DI1最大值，且DI1不为0*/
							{
								if((V_Data_Id&0xFFFF00FF)==(PStr_2Table[V_Line].V_DI&0xFFFF00FF))/*DI1不比较*/
								{
									if(((V_Data_Id&0x0000FF00)<=(PStr_2Table[V_Line].V_DI&0x0000FF00))
										&&(0x00000000!=(V_Data_Id&0x0000FF00)))/*DI1＜=最大值,且DI1不为0*/
									{
										break;
									}
								}
							}
							else
							{
#endif
								if(DT_Flash_Tol_DI0_DI1Max==PStr_2Table[V_Line].V_DT_Type) /*只列DI1最大值，且DI1不为0,DI0表示次数且不为零*/
								{
									if((V_Data_Id&0xFFFF0000)==(PStr_2Table[V_Line].V_DI&0xFFFF0000))/*DI0、DI1不比较*/
									{
										if(0x00000000==(V_Data_Id&0x000000FF))  /*次数不为0*/
										{
											continue;
										}

										if(((V_Data_Id&0x0000FF00)<=(PStr_2Table[V_Line].V_DI&0x0000FF00))
											&&(0x00000000!=(V_Data_Id&0x0000FF00)))/*DI1＜=最大值,且DI1不为0*/
										{
											break;
										}
									}
								}
								else
								{	/*不判断DI 0，次数，698事件发生及结束*/
									if(DT_Flash_698EventTab==PStr_2Table[V_Line].V_DT_Type)
									{
										if((V_Data_Id&0xFFFFFF00)==(PStr_2Table[V_Line].V_DI&0xFFFFFF00))
										{
											break;
										}
									}
								}
#if 0
							}
						}
#endif
					}
				}
			}
		}
	}

	if(V_Line==V_MaxLine)
	{
		return C_IDError;
	}
	else
	{
		*P_Line=V_Line;
		return C_OK;
	}
}
/*********************************************************************************
函数原型：uchar8 SF_OrganEventData(ulong32 *P_Data_Id_OAD,ulong32 P_Str_3EventTableAddr,ushort16 *P_TotalLen,
					ushort16 *P_Length,ulong32 V_FindFlashAddr,uchar8 *P_Data,uchar8 V_DT_Type,ushort16 V_3EventTableLen)
功能描述：根据OAD序号表，组织所超度数据。不支持的OAD返回1字节C_NotSupportAOD_Data
输入参数：ulong32 *P_Data_Id_OAD：抄读关联OAD列表。关联属性对应OAD顺序，当查找OAD为FFFFFFFF则表示，该条记录读取记录OAD结束
		ulong32 P_Str_3EventTableAddr：3级表首地址
		ushort16 *P_TotalLen：作为输入为已组织数据总长度，输出包含本次组织数据长度后的总长度（该总长度为完整条数数据总长度）
		ushort16 *P_Length：作为输入为剩余缓存长度，输出包含本次组织数据长度后剩余缓存总长度
		ulong32 V_FindFlashAddr：所读记录数据Flash地址;
		uchar8 *P_Data：所读记录数据存放缓存,直接采用读数据带过来的缓存;
		uchar8 V_DT_Type：数据类型用于区分什么4级表;
		ushort16 V_3EventTableLen:3级表具体行
输出参数：无
返回参数：C_OK、C_IICError、C_Error、C_DataLenError、C_IDError、C_NoData
功能说明：
调用机制：
备     注：
*********************************************************************************/
uchar8 SF_OrganEventData(ulong32 *P_Data_Id_OAD, ulong32 P_Str_3EventTableAddr, ushort16 *P_TotalLen, ushort16 *P_Length, ulong32 V_FindFlashAddr, uchar8 *P_Data, uchar8 V_DT_Type, ushort16 V_3EventTableLen)
{
	ushort16 V_Data_Length, V_Data_LengthOff, V_Data_LengthOffnei;
	uchar8 P_DataOAD_NumTab[C_698Event_OADTabLen];
	uchar8 P_OADTabLen_T[CLI_Free_OADTabLen_T];
	ushort16 V_OADTabLen_T, V_OADOrder16, V_k, V_EventSign;
	uchar8 V_Return_Flag, V_j, V_ucAAFlag=0;
	ulong32 V_FlashAddr;
	Str_4aTable * PStr_4aTable=NULL;
	uchar8 V_Sign = 0;
	Str_3dEventTable *P_Str_3dEventTableAddr=NULL;
	Str_3cTable *P_Str_3cTable_Flash=NULL;
	uchar8 V_Str_4aTableLen;
	Str_3dEventTable V_Str_3dEventTableAddr;
	Str_3cTable  V_Str_3cTable_Flash;
    uchar8 V_ucRateNumJudge, V_ucFrozenConver645Len;
    uchar8 V_DataTemp[ProgCrc_O + C_CRCLen2] = {0};
    ulong32 V_ulOAD;
    uchar8 V_ucDataFlag;

	V_Data_Length = 0;
	if(DT_Flash_698EventTab==V_DT_Type)     /*有关联列表*/
	{
		P_Str_3dEventTableAddr = (Str_3dEventTable *)P_Str_3EventTableAddr;
		V_Str_3dEventTableAddr = P_Str_3dEventTableAddr[V_3EventTableLen];

		V_Return_Flag = SF_ReadE2Three(V_Str_3dEventTableAddr.V_TBLen_E2BakeUp1Addr, 1, &P_OADTabLen_T[0]);
		if(C_OK == V_Return_Flag)
		{
			V_Sign |= C_W_SafeFlag_1;
			V_OADTabLen_T = P_OADTabLen_T[0] * C_698Event_OADTabDataType;   /*序号表每个OAD序号两个字节*/
			if(V_OADTabLen_T>C_698Event_OADTabLen)  /*数据长度安全性判断*/
			{
				return 	C_Error;    /*异常*/
			}
			V_Return_Flag = SF_ReadE2Three(V_Str_3dEventTableAddr.V_TB_E2BakeUp1Addr, V_OADTabLen_T, P_DataOAD_NumTab);
			if(C_OK == V_Return_Flag)
			{
				V_Sign |= C_W_SafeFlag_2;
			}
			if(0 != V_OADTabLen_T)    /*有关联列表*/
			{
				V_Sign |= C_W_SafeFlag_3;
			}
		}

		if(0xFFFFFFFF == V_Str_3dEventTableAddr.PStr_4aTableAddr)   /*没有4级分表，在外面已处理，该函数只处理有分级表数据*/
		{
			return C_Error;
		}
		PStr_4aTable = (Str_4aTable *)(V_Str_3dEventTableAddr.PStr_4aTableAddr);
		V_Str_4aTableLen = V_Str_3dEventTableAddr.V_Str_4aTableLen;
	}
	else
	{
		P_Str_3cTable_Flash = (Str_3cTable *)P_Str_3EventTableAddr;
		V_Str_3cTable_Flash = P_Str_3cTable_Flash[V_3EventTableLen];
		PStr_4aTable = (Str_4aTable *)(V_Str_3cTable_Flash.PStr_4TableAddr);
		V_Str_4aTableLen = V_Str_3cTable_Flash.V_Str_4TableLen;
	}

    V_ulOAD = P_Data_Id_OAD[0];
	P_Data_Id_OAD++;

	while(0xFFFFFFFF != (*P_Data_Id_OAD) )
	{
		V_Data_LengthOff = 0;
		V_ucAAFlag = 0;

		for( V_j = 0; V_j < V_Str_4aTableLen; V_j++)
		{
			if( PStr_4aTable[V_j].V_OAD == *P_Data_Id_OAD )
			{
				if( (*P_Length) >= (PStr_4aTable[V_j].V_DataLen & C_EventOutSign))
				{
					if(0xFFFFFFFF == V_FindFlashAddr)   /*抄读次数超*/
					{
                        memset(&P_Data[V_Data_Length], 0x00, (PStr_4aTable[V_j].V_DataLen & C_EventOutSign));
					}
					else
					{
						V_FlashAddr = V_FindFlashAddr + V_Data_LengthOff;
						InF_FlashChipSelect();
						InF_ReadFlash(V_FlashAddr, &P_Data[V_Data_Length], (PStr_4aTable[V_j].V_DataLen & C_EventOutSign));    /*读记录数据*/
					}

                    if( V_ulOAD == CProgram_Note_1)
                    {
                        V_ucDataFlag = InF_RD_ProgRecordReg(CProgram_Note_1, V_DataTemp);
                        if(V_ucDataFlag == C_OK)
                        {
                            if( *P_Data_Id_OAD == CProgOADGather )
                            {
                                memcpy(&P_Data[V_Data_Length], &V_DataTemp[ProgDI_O], (PStr_4aTable[V_j].V_DataLen & C_EventOutSign));
                            }
                            else if( *P_Data_Id_OAD == CEventEndTime )
                            {
                                memcpy(&P_Data[V_Data_Length], &V_DataTemp[ProgEndTime], (PStr_4aTable[V_j].V_DataLen & C_EventOutSign));
                            }
                            else
                            {
                                ; /*else不需要替换数据*/
                            }
                        }   /*else不需要替换数据*/
                    }

					(*P_Length) -= (PStr_4aTable[V_j].V_DataLen & C_EventOutSign);
					V_Data_Length += (PStr_4aTable[V_j].V_DataLen & C_EventOutSign);

					V_ucAAFlag = 0x68;
					break;
				}
				else
				{
					return 	C_DataLenError;
				}
			}
			else
			{
				V_Data_LengthOff += (PStr_4aTable[V_j].V_DataLen & C_EventOutSign);
			}
		}
		if( V_ucAAFlag == 0x68 )        /*已经查找到，查找下一个*/
		{
			P_Data_Id_OAD++;
			continue;
		}

		if( V_Sign == C_W_SafeFlag )    /*有关联列表*/
		{
			for( V_j = 0; V_j < P_OADTabLen_T[0]; V_j++)
			{
				PF_Buffer2ToUshort16(&P_DataOAD_NumTab[C_698Event_OADTabDataType * V_j], &V_OADOrder16);
				V_EventSign=(V_OADOrder16 & 0xE000);    /*事件发生、结束标志，与设计方式有关*/
				V_OADOrder16 &= 0x1FFF;
				if(V_OADOrder16 >= Str_FrozenConvert_Table_Len)
				{
					return 	C_Error;        /*异常，正常不存在*/
				}

				if( (*P_Data_Id_OAD) == (Str_FrozenConvert_Table[V_OADOrder16].V_ulOAD|V_EventSign))   /*单独OAD相等*/
				{
                    if( SF_FrozenData_JudgeRateNum(V_OADOrder16, *P_Data_Id_OAD) == C_Error )
                    {
                        V_ucRateNumJudge = C_RateNumError;
                        break;
                    }   /*费率数未超正常应答*/

                    V_ucFrozenConver645Len = SF_GetFrozenDataLen(V_OADOrder16);

					if( (* P_Length) >= V_ucFrozenConver645Len )
					{
						if( 0xFFFFFFFF == V_FindFlashAddr )     /*抄读次数超*/
						{
                            memset(&P_Data[V_Data_Length], 0x00, V_ucFrozenConver645Len);
						}
						else
						{
							V_FlashAddr = V_FindFlashAddr + V_Data_LengthOff;
							InF_FlashChipSelect();
							InF_ReadFlash(V_FlashAddr, &P_Data[V_Data_Length], V_ucFrozenConver645Len);    /*读记录数据*/
						}

						(* P_Length) -= V_ucFrozenConver645Len;
						V_Data_Length += V_ucFrozenConver645Len;
						V_ucAAFlag = 0x68;
						break;
					}
					else
					{
						return 	C_DataLenError;
					}
				}
				else
				{
					if(C_array == Str_FrozenConvert_Table[V_OADOrder16].V_uc698Type)        /*数组格式OAD,查询是否为分OAD*/
					{
						V_Data_LengthOffnei = 0;

						for(V_k = 0;    ; V_k++)
						{
							if((V_OADOrder16 + V_k + 1) >= Str_FrozenConvert_Table_Len)
							{
								return 	C_Error;    /*异常，正常不存在*/
							}

							if ( ( Str_FrozenConvert_Table[V_OADOrder16 + V_k + 1].V_ulOAD & 0xFFFFFF00)
                              == ( Str_FrozenConvert_Table[V_OADOrder16].V_ulOAD & 0xFFFFFF00))
							{
								if( (*P_Data_Id_OAD) == ( Str_FrozenConvert_Table[V_OADOrder16 + V_k + 1].V_ulOAD | V_EventSign ) )
								{
                                    if(SF_FrozenData_JudgeRateNum((V_OADOrder16 + V_k + 1), *P_Data_Id_OAD) == C_Error)
                                    {
                                         V_ucRateNumJudge = C_RateNumError;
                                         break;
                                     }  /*费率数未超正常应答*/

                                    V_ucFrozenConver645Len = SF_GetFrozenDataLen(V_OADOrder16 + V_k + 1);

									if( (*P_Length) >= V_ucFrozenConver645Len )
									{
										if(0xFFFFFFFF == V_FindFlashAddr)   /*抄读次数大于记录次数*/
										{
                                            memset(&P_Data[V_Data_Length], 0x00, V_ucFrozenConver645Len);
										}
										else
										{
											V_FlashAddr=V_FindFlashAddr+V_Data_LengthOff + V_Data_LengthOffnei;
											InF_FlashChipSelect();
											InF_ReadFlash(V_FlashAddr, &P_Data[V_Data_Length], V_ucFrozenConver645Len);    /*读记录数据*/
										}

										(* P_Length) -= V_ucFrozenConver645Len;
										V_Data_Length += V_ucFrozenConver645Len;
										V_ucAAFlag = 0x68;
										break;
									}
									else
									{
										return 	C_DataLenError;
									}
								}
								else
								{
									V_Data_LengthOffnei += Str_FrozenConvert_Table[V_OADOrder16+V_k+1].V_uc645Length;
								}
							}
							else
							{
								break;
							}
						}
						if(V_ucAAFlag == 0x68)
						{
							break;
						}
					}
				}
				V_Data_LengthOff += Str_FrozenConvert_Table[V_OADOrder16].V_uc645Length;    /*数据偏移*/
			}
			if(V_ucAAFlag == 0x68)      /*已经查找到，查找下一个*/
			{
				P_Data_Id_OAD++;
				continue;
			}
		}

		if((V_ucAAFlag != 0x68) || (V_ucRateNumJudge == C_RateNumError))    /*不存在补1字节C_NotSupportAOD_Data*/
		{
			if((* P_Length) >= 1)
			{
				P_Data[V_Data_Length] = C_NotSupportAOD_DataBB;    /*读记录数据*/
				(* P_Length) -= 1;
				V_Data_Length += 1;
			}
			else
			{
				return 	C_DataLenError;
			}
		}
		P_Data_Id_OAD++;
	}

	(*P_TotalLen) += V_Data_Length;
	return C_OK;
}

/*********************************************************************************
函数原型：void SF_Initial_GVStrNextEventData(void)
功能描述：初始化GV_Str_NextLoadTime结构体，CRC异常，错误
输入参数：无
输出参数：无
返回参数：无
功能说明：
调用机制：
备     注：
*********************************************************************************/
void SF_Initial_GVStrNextLoadTime(void)
{
	GV_FreezeLastNum[0]=0xFF;
	GV_FreezeLastNum[1]=0xFF;
	GV_FreezeLastNum[2]=0xFF;
}

/*********************************************************************************
函数原型：void SF_Initial_GVStrNextEventData(void)
功能描述：初始化GV_Str_NextEvent结构体，CRC异常，错误
输入参数：无
输出参数：无
返回参数：无
功能说明：
调用机制：
备     注：
*********************************************************************************/
void SF_Initial_GVStrNextEventData(void)
{
	GV_Str_NextEvent.PV_Str_2Table=NULL;
	GV_Str_NextEvent.V_NextSign=0;
	GV_Str_NextEvent.V_LastNum=0;
	GV_Str_NextEvent.V_CRC16=0xFFFF;	/*初始化CRC错误*/

	SF_Initial_GVStrNextLoadTime();
}

/******************************************************************************************************************************************************************
函数原型：uchar8  InF_ReadEventData(ulong32 * P_Data_Id_OAD,uchar8 * P_FixTime,uchar8 * P_Data,uchar8 * V_NextSign,
								ushort16 * P_Data_Length,uchar8 V_timeFlash)
功能描述：读事件记录接口函数，包括方法1、2、9，方法2为起始、结束期间数据，周期为0，返回数据根据传入的OAD顺序，
输入参数：ulong32 *P_Data_Id_OAD：数据标识OAD；第一个OAD表示读取冻结类型，
		例如300D0201，表示读取全失压事件，最低1字节00表示表示按日期读取，非00表示读取上XX次记录，此时*P_FixTime、V_BlockNum无效.
		后续OAD顺序为关联属性对应OAD顺序，当查找OAD为FFFFFFFF则表示，该条记录读取记录OAD结束(包含固定列表)。
		uchar8 *P_FixTime：给定时间记录块，12个字节。按时间区间抄读，前6个字节表示起始时间，后6个字节表示结束时间，时间格式ssmmhhDDMMYY
		按固定时间抄读时，前6个字节与后6个字节相同。当时间区间读需后续帧时，前6个字节为下一块记录时间。
		uchar8 *V_NextSign：作为输入参数后续帧标识，Bit5--Bit4表示是否为后续帧抄读。当为1时表示为后续帧抄读，非1时表示是首次抄读。
		ushort16 *V_Length：读数据缓存区最大长度；
		uchar8 V_timeFlash:表示根据时间抄读事件记录时，是根据发生时间、还是结束时间。AA表示结束时间，其他数据为发生时间
输出参数：uchar8 *P_FixTime：作为输出参数时，当有后续帧时，返回下一个记录块记录时间(前6个字节)。
		ushort16 *V_Length：所读数据实际长度；
		uchar8 *P_Data：读数据存放缓存；
		uchar8 *V_NextSign：作为输出参数后续帧标识，
		Bit5-Bit4表示是否为后续帧抄读。当为1时表示为后续帧抄读，非1时表示是首次抄读。
		Bit0-Bit3表示抄读返回数据包含的事件记录条数(最多10条).
		Bit7-Bit6:表示按固定时间或区间抄读数据，返回数据是否包含最近1条记录
		1：表示返回数据包含最近1条记录，0：表示返回数据不包含最近1条记录。部分事件记录最近1次需读事件记录接口函数
		(如安时数，发生期间数据层数据为0)。正常固定时间或区间抄读，最近1条记录数据为返回数据的最后1条，时间从前往后查。
返回参数：C_OK、C_IICError、C_SPIError、C_DataLenError、C_IDError、C_NoData、C_Error
调用位置：
备     注：当按固定时间抄读时，返回数据为相等时间点数据。
		按时间区间抄读时，第1个时间点数据为起始时间往后的最近1个时间点数据，
		修改时间：按固定时间抄读时，返回最近1次满足时间要求的数据。
		按区间抄读，返回最早区间的数据(假如修改时间有多个区间的话)。
		显示缓存开大
***********************************************************************************************************************************************/
uchar8 InF_ReadEventData(ulong32 *P_Data_Id_OAD, uchar8 *P_FixTime, uchar8 *P_Data, uchar8 *V_NextSign, ushort16 *P_Data_Length, uchar8 V_timeFlash)
{
	uchar8 V_Return_Flag, V_DI[4], V_NextEvent[8], V_LastNum;
	ushort16 V_Line, V_DataEventTolLen, V_E2Addr, V_TotalLen;
	Str_2Table *PStr_2TableAddr=NULL;
	Str_2Table *PStr_2TableAddr1=NULL;

	uchar8 P_Dgree[CLAll_Loss_Vol_Degree], V_Num, V_NumMax, V_CompareSign, V_CompareSign1, V_NextSign1 = C_NoNextSign;
	ulong32 V_Dgree, V_Temp32, P_FlashAddr1[2];

	Str_3cTable Str_3cTableAddr;
	Str_3cTable *PStr_3cTableAddr = NULL;

	Str_3dEventTable Str_3dEventTableAddr;
	Str_3dEventTable *PStr_3dEventTableAddr = NULL;
	ushort16 V_CRC16;
	ushort16 V_3dEventTableLine;
	uchar8 V_698Event_MaxNum;  /*最大记录次数*/
	uchar8 V_Num1;
	uchar8 V_CompareSign2;

	V_Temp32=(ulong32)GV_Str_NextEvent.PV_Str_2Table;
	PF_Ulong32ToBuffer4(&V_NextEvent[0], &V_Temp32, 4);
	V_NextEvent[4] = GV_Str_NextEvent.V_NextSign;
	V_NextEvent[5] = GV_Str_NextEvent.V_LastNum;
	V_CRC16 = GV_Str_NextEvent.V_CRC16;

	PF_Ushort16ToBuffer2(&V_NextEvent[6], &V_CRC16);

	V_Return_Flag = PF_Check_CRC(&V_NextEvent[0], 8);    			/*后续帧抄读全局变量*/

	PF_Ulong32ToBuffer4(&V_DI[0], &P_Data_Id_OAD[0], 4);
    if ( ( V_Return_Flag == C_OK )
      && ( GV_Str_NextEvent.V_NextSign == C_NextSign )
      && ( GV_Str_NextEvent.V_LastNum < C_698Event_MaxNum )
      && ( C_NextSign == ((*V_NextSign) & C_NextSign_Judge ) ) )	/*后续帧抄读*/
    {
        PStr_2TableAddr1 = GV_Str_NextEvent.PV_Str_2Table;
        V_LastNum = GV_Str_NextEvent.V_LastNum;          			/*上n次记录，该变量出口赋值时会判断GV_Str_NextEvent.V_LastNum需≥1*/
    }
    else															/*非后续帧或全局变量判断错误，则重新查找操作*/
    {
        SF_Initial_GVStrNextEventData();			 				/*初始化CRC错误,没有后续帧*/

        V_LastNum = V_DI[0];										/*区间读为0*/

        V_Return_Flag = SF_Find1Table_Data(V_DI[3], &V_Line);		/*查找1级表*/

        if(V_Return_Flag != C_OK)
        {
             return V_Return_Flag;
        }

        PStr_2TableAddr = (Str_2Table * )(Str_1Table_DI3[V_Line].PStr_2TableAddr);         /*DI3对应的2级表地址*/

        V_Return_Flag = SF_Find2EventTable_Data(P_Data_Id_OAD[0], PStr_2TableAddr,&V_Line, Str_1Table_DI3[V_Line].V_Str_2TableLen);

        if(V_Return_Flag!=C_OK)
        {
             return V_Return_Flag;
        }

        PStr_2TableAddr1 = &PStr_2TableAddr[V_Line];
    }

    if(DT_Flash_698EventTab == PStr_2TableAddr1->V_DT_Type)     /*数据长度需计算*/
    {
        PStr_3dEventTableAddr = (Str_3dEventTable *)(PStr_2TableAddr1->PStr_3TableAddr);

        if(PStr_2TableAddr1->V_LineNum >= Str_3dTable_Flash_Len)
        {
            return C_DataLenError;
        }
        V_3dEventTableLine = PStr_2TableAddr1->V_LineNum;
        V_DataEventTolLen = SF_GetEventDataLen(PStr_3dEventTableAddr[V_3dEventTableLine].V_TB_E2BakeUp1Addr, PStr_3dEventTableAddr[V_3dEventTableLine].V_TBLen_E2BakeUp1Addr, PStr_3dEventTableAddr[V_3dEventTableLine].PStr_4aTableAddr, PStr_3dEventTableAddr[V_3dEventTableLine].V_Str_4aTableLen);        /*3C表格固定关联列表，数据长度固定*/

        if ( ( 0 == V_DataEventTolLen ) || ( 0xFFFF == V_DataEventTolLen ) )
        {
            return C_DataLenError;
        }

        Str_3dEventTableAddr = PStr_3dEventTableAddr[V_3dEventTableLine];
        V_E2Addr = Str_3dEventTableAddr.V_Num_E2BakeUp1Addr;    /*取Flash记录次数E2地址*/
    }
    else
    {
        V_DataEventTolLen = PStr_2TableAddr1->V_DataLen;
        if(PStr_2TableAddr1->V_LineNum >= Str_3cTable_Flash_Len)
        {
            return C_AbnormalError;    /*正常不存在*/
        }
        PStr_3cTableAddr = (Str_3cTable *)(PStr_2TableAddr1->PStr_3TableAddr);
        Str_3cTableAddr = PStr_3cTableAddr[PStr_2TableAddr1->V_LineNum];
        V_E2Addr = Str_3cTableAddr.V_Num_E2BakeUp1Addr;    /*取Flash记录次数E2地址*/
    }

    V_Return_Flag = SF_ReadE2Three(V_E2Addr, CLAll_Loss_Vol_Degree, &P_Dgree[0]);
    if(C_OK != V_Return_Flag)
    {
        return C_IICError;
    }

    PF_Buffer4ToUlong32(&P_Dgree[0], &V_Dgree, CLAll_Loss_Vol_Degree);

    if ( ( 0 == V_Dgree ) || ( V_LastNum > V_Dgree ) )  /*区间读为0,没有记录数据统一返回C_NoData*/
    {
        * V_NextSign = 0;
        SF_Initial_GVStrNextEventData();			/*初始化CRC错误,没有后续帧*/
        return C_NoData;
    }

    if( 0xAA == V_timeFlash )     /*假如是以结束时间抄读数据，判断该事件是否有结束时间，假如没有，则返回C_NoData*/
    {
        if(C_OK == InF_JudgeNoEndTimeEvent(P_Data_Id_OAD[0]) )
        {
            SF_Initial_GVStrNextEventData();	   /*初始化CRC错误,没有后续帧*/
            return C_NoData;
        }
    }

    if ( ( P_Data_Id_OAD[0] & 0xFFFFFF00 ) == (CProgKD_Note_1 & 0xFFFFFF00))					/*密钥更新*/
    {
        V_698Event_MaxNum = C_698Key_UpdateEvent_MaxNum;										/*密钥更新2次*/
    }
    else if ( ( ( P_Data_Id_OAD[0] & 0xFFFFFF00 ) == ( CBroadcastTime_Note_1 & 0xFFFFFF00 ) )	/*广播校时*/
           || ( ( P_Data_Id_OAD[0] & 0xFFFFFF00 ) == ( CPow_Down_Note_1 & 0xFFFFFF00 ) ) )		/*掉电记录*/
    {
        V_698Event_MaxNum = C_698Event_MaxNum100;												/*广播校时和掉电100次*/
    }
    else
    {
        V_698Event_MaxNum = C_698Event_MaxNum;													/*其他事件记录10次*/
    }

    if( 0 == V_DI[0] )      /*按时间抄读数据*/
    {
        V_CompareSign = PF_Campare_Data(&P_FixTime[0],&P_FixTime[CLDate_Time],CLDate_Time);
        if(C_GreaterThan == V_CompareSign)
        {
            return C_NoData;    /*正常不存在*/
        }

        if(V_Dgree > V_698Event_MaxNum)     /*记录次数大于C_698Event_MaxNum则采用，上C_698Event_MaxNum遍历查找*/
        {
            V_NumMax = V_698Event_MaxNum;
        }
        else
        {
            V_NumMax = V_Dgree;
        }

        V_Num1 = V_NumMax;
        if ( ( V_LastNum < V_NumMax ) && ( 0 != V_LastNum ) )    /*后续帧抄读*/
        {
            V_Num1 = V_LastNum;
        }

        *V_NextSign = 0;
        V_TotalLen = 0;
        V_Return_Flag = C_NoData;       /*先设置为没有数据*/

        if(C_Equal == V_CompareSign)    /*固定时间抄读*/
        {
            V_Num = 1;
            SF_Initial_GVStrNextEventData();			/*初始化CRC错误,没有后续帧*/

            for(    ; V_Num <= V_NumMax; V_Num++)      /*从最近1次查起，从后往前查。取最近时间点*/
            {
                V_Temp32 = V_Dgree - V_Num + 1;          /*读上N次数据，即查找当前(n-N+1)次地址*/

                if(DT_Flash_698EventTab != PStr_2TableAddr1->V_DT_Type)
                {
                      SF_GetFlashAddr(V_Temp32,Str_3cTableAddr.V_StaFlashAddr, V_DataEventTolLen, Str_3cTableAddr.V_EndFlashAddr, &P_FlashAddr1[0]);   /*获取当前数据Flash页地址及页内地址*/
                }
                else
                {
                      SF_GetFlashAddr(V_Temp32,Str_3dEventTableAddr.V_StaFlashAddr, V_DataEventTolLen, Str_3dEventTableAddr.V_EndFlashAddr, &P_FlashAddr1[0]);   /*获取当前数据Flash页地址及页内地址*/
                }

                P_FlashAddr1[0] += P_FlashAddr1[1];

                if(P_FlashAddr1[0] > C_Flash_Max_Addr)
                {
                    return C_Error;     /*正常不存在*/
                }

                InF_FlashChipSelect();
                if(V_timeFlash == 0xAA)  /*根据结束时间查找*/
                {
                    InF_ReadFlash((P_FlashAddr1[0] + CLAll_Loss_Vol_Degree + CLEventHPTime), &V_NextEvent[0], CLDate_Time);    /*读记录数据日期时间*/
                }
                else        /*其余为发生时间查找*/
                {
                    InF_ReadFlash((P_FlashAddr1[0] + CLAll_Loss_Vol_Degree), &V_NextEvent[0], CLDate_Time);    /*读记录数据日期时间*/
                }

                V_CompareSign1 = PF_Campare_Data(&V_NextEvent[0], &P_FixTime[0], CLDate_Time);
                if(C_Equal != V_CompareSign1)
                {
                    continue;
                }
                else
                {
                    if(0xFFFFFFFF == P_Data_Id_OAD[1])    /*整行抄读*/
                    {
                        if(V_DataEventTolLen > (* P_Data_Length))
                        {
                            return C_DataLenError;
                        }
                        InF_FlashChipSelect();
                        InF_ReadFlash(P_FlashAddr1[0], P_Data, V_DataEventTolLen);      /*获取记录数据*/
                        V_Return_Flag = C_OK;
                        V_TotalLen = V_DataEventTolLen;
                    }
                    else
                    {
                        V_Return_Flag = SF_OrganEventData(&P_Data_Id_OAD[0], PStr_2TableAddr1->PStr_3TableAddr, &V_TotalLen,P_Data_Length, P_FlashAddr1[0], P_Data,PStr_2TableAddr1->V_DT_Type, PStr_2TableAddr1->V_LineNum);    /*组织记录数据*/
                    }
                    break;
                }
            }
            if(C_OK == V_Return_Flag)
            {
                *V_NextSign += 1;
                if(1 == V_Num)    /*最近1次记录*/
                {
                    *V_NextSign |= C_NextSign_Last;
                }
                *P_Data_Length = V_TotalLen;
            }
            return V_Return_Flag;
        }
        else    /*区间抄读*/
        {

#if 0
            for(    ; V_Num <= V_NumMax; V_Num++)    /*从最近1次查起，从后往前查。取最近时间点*/
#endif

            for(    ; V_Num1 > 0; V_Num1--)          /*从最早次查起，从前往后查找。*/
            {
                V_Temp32 = V_Dgree - V_Num1 + 1;     /*读上N次数据，即查找当前(n-N+1)次地址*/

                if(DT_Flash_698EventTab != PStr_2TableAddr1->V_DT_Type)
                {
                      SF_GetFlashAddr(V_Temp32, Str_3cTableAddr.V_StaFlashAddr, V_DataEventTolLen, Str_3cTableAddr.V_EndFlashAddr, &P_FlashAddr1[0]);   /*获取当前数据Flash页地址及页内地址*/
                }
                else
                {
                      SF_GetFlashAddr(V_Temp32,Str_3dEventTableAddr.V_StaFlashAddr, V_DataEventTolLen, Str_3dEventTableAddr.V_EndFlashAddr, &P_FlashAddr1[0]);   /*获取当前数据Flash页地址及页内地址*/
                }
                P_FlashAddr1[0] += P_FlashAddr1[1];

                if(P_FlashAddr1[0] > C_Flash_Max_Addr)
                {
                    SF_Initial_GVStrNextEventData();			/*初始化CRC错误,没有后续帧*/
                    return C_Error;         /*正常不存在*/
                }

                InF_FlashChipSelect();

                if(V_timeFlash == 0xAA)   /*根据结束时间查找*/
                {
                    InF_ReadFlash((P_FlashAddr1[0] + CLAll_Loss_Vol_Degree + CLEventHPTime), &V_NextEvent[0], CLDate_Time);    /*读记录数据日期时间*/
                }
                else        /*其余为发生时间查找*/
                {
                    InF_ReadFlash((P_FlashAddr1[0] + CLAll_Loss_Vol_Degree), &V_NextEvent[0], CLDate_Time);    /*读记录数据日期时间*/
                }

                V_CompareSign2 = PF_Campare_Data(&V_NextEvent[0], &P_FixTime[CLDate_Time], CLDate_Time);    /*比较截止时间*/
                V_CompareSign1 = PF_Campare_Data(&V_NextEvent[0], &P_FixTime[0], CLDate_Time);    /*起始时间*/

                if ( ( C_LessThan == V_CompareSign2 )
                  && ( C_LessThan != V_CompareSign1 ) )     /*有效数据，前闭后开*/
                {
                    if( 0xFFFFFFFF == P_Data_Id_OAD[1] )    /*整行抄读，第1条长度，正常该是满足要求*/
                    {
                        if( V_DataEventTolLen > (* P_Data_Length) )
                        {
                            V_NextSign1 = C_NextSign;        /*后续帧*/
                            V_Return_Flag=C_DataLenError;
                            break;
                        }
                        *P_Data_Length -= V_DataEventTolLen;
                        InF_FlashChipSelect();
                        InF_ReadFlash(P_FlashAddr1[0], &P_Data[V_TotalLen], V_DataEventTolLen);   /*获取记录数据*/

                        V_TotalLen += V_DataEventTolLen;
                        V_Return_Flag = C_OK;
                    }
                    else
                    {
                        V_Return_Flag = SF_OrganEventData(&P_Data_Id_OAD[0], PStr_2TableAddr1->PStr_3TableAddr, &V_TotalLen, P_Data_Length,P_FlashAddr1[0], &P_Data[V_TotalLen], PStr_2TableAddr1->V_DT_Type, PStr_2TableAddr1->V_LineNum);         /*组织记录数据*/
                        if(C_OK != V_Return_Flag)
                        {
                            if(C_DataLenError == V_Return_Flag)     /*长度不足*/
                            {
                                V_NextSign1 = C_NextSign;           /*后续帧*/
                            }
                            else
                            {
                                V_NextSign1 = C_NoNextSign;
                            }
                            break;
                        }
                    }
                    if(C_OK == V_Return_Flag)
                    {
                        if( 1 == V_Num1 )   /*最近1次记录*/
                        {
                            *V_NextSign |= C_NextSign_Last;
                        }
                        *V_NextSign += 1;
                    }
                }

            }
            *P_Data_Length = V_TotalLen;
            *V_NextSign |= V_NextSign1;         /*后续帧操作*/

            if(C_OK!=V_Return_Flag)
            {
                if(C_NextSign == V_NextSign1)   /*有后续帧*/
                {
                    GV_Str_NextEvent.PV_Str_2Table = PStr_2TableAddr1;    /*全局变量操作*/
                    GV_Str_NextEvent.V_NextSign = C_NextSign;
                    GV_Str_NextEvent.V_LastNum = V_Num1;
                    V_Temp32 = (ulong32)GV_Str_NextEvent.PV_Str_2Table;
                    PF_Ulong32ToBuffer4(&V_NextEvent[0], &V_Temp32, 4);
                    V_NextEvent[4] = GV_Str_NextEvent.V_NextSign;
                    V_NextEvent[5] = GV_Str_NextEvent.V_LastNum;
                    GV_Str_NextEvent.V_CRC16 = PF_Cal_CRC(&V_NextEvent[0], 6);
                }
            }

            if(C_NextSign != V_NextSign1)   /*没有后续帧*/
            {
                SF_Initial_GVStrNextEventData();			/*初始化CRC错误,没有后续帧*/
            }

            if(0 != V_TotalLen)             /*有记录数据*/
            {
                return C_OK;
            }
            else
            {
                return C_NoData;
            }
        }
    }
    else    /*按次数抄读数据*/
    {
        if(V_DI[0] > V_698Event_MaxNum)	      /*抄读最大次数限制,上面统一赋值*/
        {
            return C_NoData;
        }

        V_Temp32 = V_Dgree - V_DI[0] + 1;      /*读上N次数据，即查找当前(n-N+1)次地址，开始已经判断DI与V_Dgree大小*/

        if(DT_Flash_698EventTab != PStr_2TableAddr1->V_DT_Type)
        {
              SF_GetFlashAddr(V_Temp32, Str_3cTableAddr.V_StaFlashAddr, V_DataEventTolLen, Str_3cTableAddr.V_EndFlashAddr, &P_FlashAddr1[0]);   /*获取当前数据Flash页地址及页内地址*/
        }
        else
        {
              SF_GetFlashAddr(V_Temp32, Str_3dEventTableAddr.V_StaFlashAddr, V_DataEventTolLen, Str_3dEventTableAddr.V_EndFlashAddr, &P_FlashAddr1[0]);   /*获取当前数据Flash页地址及页内地址*/
        }

        if(P_FlashAddr1[0] > C_Flash_Max_Addr)
        {
            return C_Error;         /*正常不存在*/
        }

        P_FlashAddr1[0] += P_FlashAddr1[1];
        if( 0xFFFFFFFF == P_Data_Id_OAD[1] )   /*整行抄读*/
        {
            if(V_DataEventTolLen>(* P_Data_Length))
            {
                return C_DataLenError;
            }
            InF_FlashChipSelect();
            InF_ReadFlash(P_FlashAddr1[0],P_Data,V_DataEventTolLen);    /*获取记录数据*/
            V_TotalLen=V_DataEventTolLen;
            V_Return_Flag=C_OK;
        }
        else
        {
            V_TotalLen = 0;
            V_Return_Flag = SF_OrganEventData(&P_Data_Id_OAD[0], PStr_2TableAddr1->PStr_3TableAddr, &V_TotalLen, P_Data_Length, P_FlashAddr1[0], P_Data, PStr_2TableAddr1->V_DT_Type, PStr_2TableAddr1->V_LineNum);     /*组织记录数据*/
        }

        *P_Data_Length = V_TotalLen;
        (*V_NextSign) = 1;
        if(0x01 == V_DI[0])    /*当前记录*/
        {
            *V_NextSign |= C_NextSign_Last;
        }
        SF_Initial_GVStrNextEventData();			/*初始化CRC错误,没有后续帧*/
        return V_Return_Flag;
    }
}
/*********************************************************************************
函数原型：uchar8 SF_GetFreezeIntervalTime(ulong32 V_Data_Id_OAD,uchar8 *P_StarTime,uchar8 *P_EndTime,ulong32 *P_SubTime)
功能描述：根据不同类冻结，计算P_EndTime、P_StarTime相差时间，年、月、日、时、分，同时判断下级时间属性是否相等(如分钟冻结，则判断秒是否相等)。
输入参数：ulong32 V_Data_Id_OAD：某类冻结OAD
uchar8 *P_StarTime：输入参数，为起始时间，格式为ssmmhhDDMMYY
uchar8 *P_EndTime：输入参数，为起始时间，格式为ssmmhhDDMMYY
输出参数：ulong32 *P_SubTime：P_EndTime、P_StarTime相差时间，数据格式为hex码；异常值为FFFFFFFF，
返回参数：C_Equal,C_GreaterThan或C_LessThan
功能说明：
调用机制：
备     注：P_EndTime必须大于P_StarTime
*********************************************************************************/
uchar8 SF_GetFreezeIntervalTime(ulong32 V_Data_Id_OAD,uchar8 *P_StarTime,uchar8 *P_EndTime,ulong32 *P_SubTime)
{
	uchar8 V_Return_Flag;
	uchar8 V_Return_Flag1;
	ulong32 V_ultemp;

	V_Return_Flag=PF_Campare_Data(P_StarTime,P_EndTime,CLDate_Time);
	if(C_LessThan!=V_Return_Flag)
	{
		*P_SubTime=0xFFFFFFFF;/*正常不存在，P_EndTime必须大于P_StarTime*/
		return V_Return_Flag;
	}

	V_Return_Flag=C_LessThan;
	switch(V_Data_Id_OAD&0x00FF0000)
	{
		case(C_RelatedOAD_Min&0x00FF0000):   /*分钟冻结*/
		{
			if(P_StarTime[0]==P_EndTime[0])/*秒相等*/
			{
				V_Return_Flag=C_Equal;
			}
			V_Return_Flag1=PF_TimeSub_Min_698(P_StarTime,P_EndTime,P_SubTime);
			if(C_TIMEERR==V_Return_Flag1)
			{
				*P_SubTime=0xFFFFFFFF;
			}
		}break;

		case(C_RelatedOAD_Hour&0x00FF0000):   /*小时冻结*/
		{
			if( (P_StarTime[1] == P_EndTime[1] ) && ( P_StarTime[2] == P_EndTime[2] ) )/*分钟、秒相等*/
			{
				V_Return_Flag=C_Equal;
			}
			V_Return_Flag1=PF_TimeSub_Hour_698(P_StarTime,P_EndTime,P_SubTime);
			if(C_TIMEERR==V_Return_Flag1)
			{
				*P_SubTime=0xFFFFFFFF;
			}
		}break;

		case(C_RelatedOAD_Day&0x00FF0000):   /*日冻结*/
		{
			V_Return_Flag=PF_Campare_Data(&P_StarTime[1],&P_EndTime[1],3);/*判断时分秒*/

			V_Return_Flag1=PF_TimeSub_Day_698(P_StarTime,P_EndTime,&V_ultemp);
			if(C_TIMEERR == V_Return_Flag1)
			{
				*P_SubTime = 0xFFFFFFFF;
			}
			else
			{
				*P_SubTime = V_ultemp;
			}
		}break;

		case(C_RelatedOAD_Month&0x00FF0000):   /*月冻结*/
		{
			V_Return_Flag=PF_Campare_Data(P_StarTime,P_EndTime,4);/*判断天时分秒*/
			uchar8 V_tempYear;
			ushort16 V_tempHex1,V_tempHex2;

			//V_tempHex1 = PF_BCDtoHexOneByte(P_EndTime[5]);
			//V_tempHex2 = PF_BCDtoHexOneByte(P_StarTime[5]);
			PF_Buffer2ToUshort16(&P_EndTime[5], &V_tempHex1);
			PF_Buffer2ToUshort16(&P_StarTime[5], &V_tempHex2);

			V_tempYear = V_tempHex1-V_tempHex2;		/*年，上面以判断时间大小，不可能出现小于*/
			*P_SubTime = V_tempYear*12;

			//V_tempHex1 = PF_BCDtoHexOneByte(P_EndTime[4]);
			//V_tempHex2 = PF_BCDtoHexOneByte(P_StarTime[4]);

			//*P_SubTime=*P_SubTime+V_tempHex1-V_tempHex2;/*月*/
			*P_SubTime = *P_SubTime + P_EndTime[4] - P_StarTime[4];/*月*/
			if(C_GreaterThan==V_Return_Flag)
			{
				*P_SubTime-=1;
			}

			V_Return_Flag1=PF_DataTimeActive_698(P_StarTime, C_DT_Start_ss, CLDate_Time);
			if((C_OK!=V_Return_Flag1)||(C_OK!=PF_DataTimeActive_698(P_EndTime, C_DT_Start_ss, CLDate_Time)))
			{
				*P_SubTime=0xFFFFFFFF;
			}
		}break;

//		case(C_RelatedOAD_Year&0x00FF0000):/*年冻结*/
//		{
//			V_Return_Flag=PF_Campare_Data(P_StarTime,P_EndTime,5);/*判断月天时分秒*/
//			uchar8 V_tempYear;
//			uchar8 V_tempHex1,V_tempHex2;
//
//			V_tempHex1=(P_EndTime[5]>>4)*10+(P_EndTime[5]&0x0F) ;/* 转换为16进制*/
//			V_tempHex2=(P_StarTime[5]>>4)*10+(P_StarTime[5]&0x0F) ;/* 转换为16进制*/
//
//			V_tempYear=V_tempHex1-V_tempHex2;/*年，上面以判断时间大小，不可能出现小于*/
//			*P_SubTime=V_tempYear;
//
//			if(C_GreaterThan==V_Return_Flag)
//			{
//				*P_SubTime-=1;
//			}
//
//			V_Return_Flag1=PF_DataTimeActive(P_StarTime,C_DT_Start_ss,6);
//			if((C_OK!=V_Return_Flag1)||(C_OK!=PF_DataTimeActive(P_EndTime,C_DT_Start_ss,6)))
//			{
//				* P_SubTime=0xFFFFFFFF;
//			}
//		}
//		break;

		default:
			*P_SubTime=0xFFFFFFFF;
	}
	return V_Return_Flag;
}

/*********************************************************************************
函数原型：uchar8 SF_GetFreezeStartTime(ulong32 V_Data_Id_OAD,uchar8 *P_StarTime,ushort16 V_IntervalTime)
功能描述：根据某冻结、起始时间、间隔时间，得到后续时间
输入参数：ulong32 V_Data_Id_OAD：某类冻结OAD
		uchar8 *P_StarTime：作为输入参数，为起始时间，格式为mmhhDDMMYY
		ushort16 V_IntervalTime：间隔周期，hex格式，单位根据某类冻结定义；
输出参数：uchar8 *P_StarTime：作为输出参数，为＋间隔后起始时间，格式为mmhhDDMMYY
返回参数：C_OK,C_Error(年超2099年,或触发类冻结)
功能说明：
调用机制：
备     注：
*********************************************************************************/
/*用于判断月份天数*/
/*const uchar8 C_MonthNum1[12]={31,28,31,30,31,30,31,31,30,31,30,31};*/

uchar8 SF_GetFreezeStartTime(ulong32 V_Data_Id_OAD, uchar8 *P_ucSourceTime, ulong32 V_ulAddMins)
{
#if 1
	uchar8 V_Return_Flag = C_OK, V_ucDay;
	ulong32 V_ulSec_Temp = 0;
	uchar8 V_ucTimeBuff[CLDate_Time] = {0};
	ushort16 V_usYear;


	if( (C_RelatedOAD_Min & 0x00FF0000) == (V_Data_Id_OAD & 0x00FF0000) )		/*分钟冻结*/
	{
		memcpy(&V_ucTimeBuff[C_DT_Start_mm], &P_ucSourceTime[C_DT_Start_mm], (CLDate_Time - C_DT_Start_mm) );
		V_ulSec_Temp = PF_DateTime_to_Second(P_ucSourceTime);
		V_ulSec_Temp += V_ulAddMins*60;
	}
	else if( (C_RelatedOAD_Hour & 0x00FF0000) == (V_Data_Id_OAD & 0x00FF0000) )	/*小时冻结*/
	{
		memcpy(&V_ucTimeBuff[C_DT_Start_hh], &P_ucSourceTime[C_DT_Start_hh], (CLDate_Time - C_DT_Start_hh) );
		V_ulSec_Temp = PF_DateTime_to_Second(P_ucSourceTime);
		V_ulSec_Temp += V_ulAddMins*60*60;
	}
	else if( (C_RelatedOAD_Day & 0x00FF0000) == (V_Data_Id_OAD & 0x00FF0000) )	/*日冻结*/
	{
		memcpy(&V_ucTimeBuff[C_DT_Start_DD], &P_ucSourceTime[C_DT_Start_DD], (CLDate_Time - C_DT_Start_DD) );
		V_ulSec_Temp = PF_DateTime_to_Second(P_ucSourceTime);
		V_ulSec_Temp += V_ulAddMins*60*60*24;
	}
	else if( (C_RelatedOAD_Month & 0x00FF0000) == (V_Data_Id_OAD & 0x00FF0000) )	/*月冻结*/
	{
		memcpy(&V_ucTimeBuff[C_DT_Start_MM], &P_ucSourceTime[C_DT_Start_MM], (CLDate_Time - C_DT_Start_MM) );
		V_ucDay = PF_BCDtoHexOneByte(Day[V_ucTimeBuff[C_DT_Start_MM] ] );
		if(V_ucTimeBuff[C_DT_Start_MM] == 2)
		{
			PF_Buffer2ToUshort16(&P_ucSourceTime[C_DT_Start_NN], &V_usYear);
			if(PF_Is_Leap_Year(V_usYear) == 1)
			{
				V_ucDay += 1;
			}
		}
		V_ulSec_Temp = PF_DateTime_to_Second(P_ucSourceTime);
		V_ulSec_Temp += V_ulAddMins*60*60*24*V_ucDay;
	}
	else
	{
		V_Return_Flag = C_Error;
	}

	if(V_Return_Flag == C_OK)
	{
		PF_Second_to_dateTime(V_ulSec_Temp, P_ucSourceTime);
	}
	return V_Return_Flag;
#endif
#if 0
	uchar8 V_Return_Flag = C_OK;
	uchar8 V_ucTemp = 0, V_ucMthTemp = 0;
	uchar8 V_ucTimeBuff[CLDate_Time] = {0};
	ulong32 V_ulCalTemp = 0,V_ulTemp = 0,V_ulYearTemp = 0;
	ulong64 V_ulCalTemp64 = 0;
	uchar8 V_ucDataBuff[8] = {0};
	uchar8 i = 0,V_ucMonCycle = 0;
	ushort16 V_usDayCal = 0,V_usMonCal = 0,V_usYearCal = 0, V_usTemp = 0;

	V_ucTimeBuff[C_DT_Start_ss] = P_ucSourceTime[C_DT_Start_ss]; /*赋值秒*/

	switch(V_Data_Id_OAD & 0x00FF0000)
	{
		case(C_RelatedOAD_Min & 0x00FF0000):	/*分钟冻结*/
		{
			V_ucTemp = P_ucSourceTime[C_DT_Start_mm];

			V_ulCalTemp64 = V_ulAddMins + V_ucTemp;	/*从分钟开始累加*/
			if(V_ulCalTemp64 > 0x0100000000)
			{
				V_ulCalTemp64 = 0x00000000FFFFFFFF;
			}

			PF_Ulong64ToBuffer8(V_ucDataBuff, &V_ulCalTemp64, 8);
			PF_Buffer4ToUlong32(V_ucDataBuff, &V_ulCalTemp, 4);

			V_ulTemp = V_ulCalTemp % 60;
			PF_Ulong32ToBuffer4(&V_ucTemp, &V_ulTemp, 1);
			V_ucTimeBuff[C_DT_Start_mm] = V_ucTemp;	/*赋值分钟*/

			V_ulAddMins = V_ulCalTemp / 60;
		}	/*此处不需要break，因为要继续计算小时、日、月、年*/

		case(C_RelatedOAD_Hour & 0x00FF0000):	/*小时冻结*/
		{
			if( (V_Data_Id_OAD & 0x00FF0000) == (C_RelatedOAD_Hour & 0x00FF0000) )	/*如是小时冻结，分钟不处理*/
			{
				V_ucTimeBuff[C_DT_Start_mm] = P_ucSourceTime[C_DT_Start_mm];
			}

			V_ucTemp = P_ucSourceTime[C_DT_Start_hh];

			V_ulAddMins += V_ucTemp;	/*累加小时*/
			V_ulTemp = V_ulAddMins % 24;
			PF_Ulong32ToBuffer4(&V_ucTemp, &V_ulTemp, 1);
			V_ucTimeBuff[C_DT_Start_hh] = V_ucTemp;	/*赋值小时*/

			V_ulAddMins = V_ulAddMins / 24;
		}	/*此处不需要break，因为要继续计算日、月、年*/

		case(C_RelatedOAD_Day & 0x00FF0000):	/*日冻结*/
		{
			if( (V_Data_Id_OAD & 0x00FF0000) == (C_RelatedOAD_Day & 0x00FF0000) )	/*如是日冻结，分钟、小时不处理*/
			{
				V_ucTimeBuff[0] = P_ucSourceTime[0];
				V_ucTimeBuff[1] = P_ucSourceTime[1];
				V_ucTimeBuff[2] = P_ucSourceTime[2];
			}

			V_ucTemp = P_ucSourceTime[C_DT_Start_DD];
			V_ulAddMins += V_ucTemp;	/*累加天*/

			if(P_ucSourceTime[C_DT_Start_MM] == 2)	/*2月需判断闰年*/
			{
				PF_Buffer2ToUshort16(&P_ucSourceTime[C_DT_Start_NN], &V_usTemp);	/*计算出当前年,默认为20XX年*/
				V_ulYearTemp = (ulong32)V_usTemp;

				if( ( (V_ulYearTemp % 4) == 0 ) )	/*20XX年只要被4整除就是闰年*/
				{
					V_ucMthTemp = 29;
				}
				else
				{
					V_ucMthTemp = 28;
				}
			}
			else
			{
				V_ucMthTemp = C_MonthNum[P_ucSourceTime[C_DT_Start_MM] - 1];
			}

			if(V_ulAddMins > V_ucMthTemp)
			{
				V_ucMonCycle = V_ucTemp;

				for( i = 1; ; i ++ )
				{
					if( (V_ucMonCycle + (i-1) - 1) == C_MonTwoOffset)	/*2月*/
					{
						PF_Buffer2ToUshort16(&P_ucSourceTime[C_DT_Start_NN], &V_usTemp);	/*计算出当前年,默认为20XX年*/

						V_ulYearTemp = (ulong32)V_usTemp;	/*计算出当前年,默认为20XX年*/

						if( ( (V_ulYearTemp % 4) == 0 ) )	/*20XX年只要被4整除就是闰年*/
						{
							V_usDayCal += 29;
						}
						else
						{
							V_usDayCal += 28;
						}
					}
					else
					{
						V_usDayCal += C_MonthNum[V_ucMonCycle + (i-1) - 1];
					}

					if(V_usDayCal >= V_ulAddMins )
					{
						V_usMonCal += i;	/*月进位*/
						break;
					}

					if( (V_ucMonCycle + (i-1) - 1) == C_NovOffset)
					{
						V_usYearCal ++;		/*年进位*/
						i = 0;
						V_ucMonCycle = 1;	/*从1月重新开始计算*/
					}

					if( (V_usMonCal >= C_MonMaxLim) || (V_usYearCal >= C_YearMaxLim) )	/*防止死循环*/
					{
						break;
					}
				}

				V_ulTemp = V_ulAddMins - (V_usDayCal - C_MonthNum[V_ucMonCycle + (i-1) - 1]);	/*当前天*/

				if(V_usYearCal >= 1)
				{
					V_ulAddMins = (12 - V_ucTemp) + ( (V_usYearCal - 1) * 12 ) + V_usMonCal;
				}
				else
				{
					V_ulAddMins = V_usMonCal - 1;	/*月进位时，由于i从1循环，多加了1*/
				}
			}
			else
			{
				V_ulTemp = V_ulAddMins;
				V_ulAddMins = 0;
			}

			V_ucTimeBuff[C_DT_Start_DD] = V_ucTemp;	/*赋值天*/
		}	/*此处不需要break，因为要继续计算月、年*/

		case(C_RelatedOAD_Month & 0x00FF0000):		/*月冻结*/
		{
			if( (V_Data_Id_OAD & 0x00FF0000) == (C_RelatedOAD_Month & 0x00FF0000) )	/*如是月冻结，日、分钟、小时不处理*/
			{
				V_ucTimeBuff[0] = P_ucSourceTime[0];
				V_ucTimeBuff[1] = P_ucSourceTime[1];
				V_ucTimeBuff[2] = P_ucSourceTime[2];
			}

			V_ucTemp = P_ucSourceTime[C_DT_Start_MM];

			V_ulAddMins += V_ucTemp;	/*累加月*/
			if( 0 == (V_ulAddMins % 12) )	/*当前月整倍数*/
			{
				V_ulTemp = 12;
				if(V_ulAddMins >= 12)	/*年进位*/
				{
					V_ulAddMins = (V_ulAddMins / 12) - 1;
				}
				else
				{
					V_ulAddMins /= 12;
				}
			}
			else
			{
				V_ulTemp = V_ulAddMins % 12;
				V_ulAddMins /= 12;
			}

			PF_Ulong32ToBuffer4(&V_ucTemp, &V_ulTemp, 1);
			V_ucTimeBuff[C_DT_Start_MM] = V_ucTemp;	/*赋值月*/
		}	/*此处不需要break，因为要继续计算年*/

		case(C_RelatedOAD_Year & 0x00FF0000):	/*年冻结*/
		{
			if( (V_Data_Id_OAD & 0x00FF0000) == (C_RelatedOAD_Year & 0x00FF0000) )	/*如是年冻结，月、日、分钟、小时不处理*/
			{
				V_ucTimeBuff[0] = P_ucSourceTime[0];
				V_ucTimeBuff[1] = P_ucSourceTime[1];
				V_ucTimeBuff[2] = P_ucSourceTime[2];
				V_ucTimeBuff[3] = P_ucSourceTime[3];
				V_ucTimeBuff[4] = P_ucSourceTime[4];
			}

			PF_Buffer2ToUshort16(&P_ucSourceTime[C_DT_Start_NN], &V_usTemp);	/*计算出当前年,默认为20XX年*/

			V_usTemp += (ushort16)V_ulAddMins;
			if(V_usTemp > 2099)	/*按异常处理，BCD为99年*/
			{
				V_Return_Flag = C_Error;
			}

			PF_Ushort16ToBuffer2(&V_ucTimeBuff[C_DT_Start_NN], &V_usTemp);	/*赋值年*/
		}break;

		default:
		{
			V_Return_Flag = C_Error;
		}break;
	}

	PF_CopyDataBytes(V_ucTimeBuff, P_ucSourceTime, CLDate_Time);	/*将累加后时间传给目标地址*/

	return V_Return_Flag;
#endif
}
/*********************************************************************************
函数原型：ulong32 SF_JudgeFreezeFlashAddrValid(ulong32 V_FindFlashAddr)
功能描述：判断冻结数据Flash地址是否有效，根据冻结数据存储特征，如有修改日期则冻结数据前5字节日期修改为全FF(底层为全0)，则认为地址无效
输入参数：ulong32 V_FindFlashAddr：需判断Flash记录地址
输出参数：无
返回参数：ulong32如有效则返回V_FindFlashAddr，无效返回全FF
功能说明：
调用机制：
备     注：如有时间调整，则该记录5字节日期修改为
*********************************************************************************/
ulong32 SF_JudgeFreezeFlashAddrValid(ulong32 V_FindFlashAddr)
{
	uchar8 V_FindTime[C_698FreeData_DateLen6],V_i,V_Return_Flag;

	InF_FlashChipSelect();
	InF_ReadFlash(V_FindFlashAddr,&V_FindTime[0],C_698FreeData_DateLen6);    /*读记录数据日期时间*/

	for(V_i=0;V_i<C_698FreeData_DateLen6;V_i++)
	{
		if(C_Flash_NoEmpty!=V_FindTime[V_i])/*判断数据是否为全FF，即底层为00，说明有时间调整*/
		{
			break;
		}
	}

	if(V_i>=C_698FreeData_DateLen6)/*数据全FF*/
	{
		return 0xFFFFFFFF;
	}
	else
	{
		V_Return_Flag=PF_DataTimeActive_698(&V_FindTime[0],C_DT_Start_ss,C_698FreeData_DateLen6);/*判断时间合法性，去除底层没有记录数据，即全00数据*/
		if(C_OK==V_Return_Flag)
		{
			return V_FindFlashAddr;
		}
		else
		{
			return 0xFFFFFFFF;
		}
	}
}
/*********************************************************************************
函数原型：ulong32 SF_FindNextFreezeFlashAddr(uchar8 V_ProNum,uchar8 V_Order,ulong32 V_FindFlashAddr,
											ulong32 V_FlashAddrLate,ulong32 V_FlashAddrEar,ushort16 V_DataLen)
功能描述：获取下条冻结记录的Flash地址，
输入参数：uchar8 V_ProNum：分钟冻结用方案号
		uchar8 V_Order：Str_698FreezeDataTable冻结序号
		ulong32 V_FindFlashAddr：上条冻结记录地址
		ulong32 V_FlashAddrLate：最近记录Flash页地址
		ulong32 V_FlashAddrEar；最早1条负荷记录地址，绝对地址，即该页第1条记录地址
		ushort16 V_DataLen：该条冻结记录数据总长度
输出参数：无
返回参数：ulong32下条冻结记录Flash地址，异常返回全FF
功能说明：
调用机制：
备     注：FlashST---Ear...Late---FlashEnd;Ear...Late---FlashEnd;FlashST...Late---Ear...FlashEnd;
		其中---表示无效数据，考虑同一页
*********************************************************************************/
ulong32 SF_FindNextFreezeFlashAddr(uchar8 V_ProNum,uchar8 V_Order,ulong32 V_FindFlashAddr,ulong32 V_FlashAddrLate,ulong32 V_FlashAddrEar,ushort16 V_DataLen)
{
	uchar8 V_FindTime[C_698FreeData_DateLen6],V_i;
	ushort16 V_OffLen;
	ulong32 V_FlashAddr,V_Return_Flag;

	V_FlashAddr=0xFFFFFFFF;
	if((V_FlashAddrLate&0xFFFFF000)==(V_FlashAddrEar&0xFFFFF000))/*同一页*/
	{
		V_FindFlashAddr+=V_DataLen;/*下条记录地址*/
		if((V_FindFlashAddr<(V_FlashAddrLate+C_OneFlashPage))&&(V_FindFlashAddr>V_FlashAddrEar))/*Flash合理性判断*/
		{
			V_FlashAddr=SF_JudgeFreezeFlashAddrValid(V_FindFlashAddr);
		}
		else
		{
			V_FlashAddr=0xFFFFFFFF;
		}
	}
	else
	{
		if(V_FlashAddrLate>V_FlashAddrEar)/*FlashST---Ear...Late---FlashEnd; Ear...Late---FlashEnd;*/
		{
			V_OffLen=V_FindFlashAddr%C_OneFlashPage;/*页内偏移，不包含上条记录数据长度，*/
			V_OffLen+=(2*V_DataLen);									/* +2*V_DataLen包括上条记录长度及本条需要查找的记录长度*/

			if(V_OffLen<=C_OneFlash_PageNum)/*没有跨页*/
			{
				V_FlashAddr=V_FindFlashAddr+V_DataLen;

				InF_FlashChipSelect();
				InF_ReadFlash(V_FlashAddr,&V_FindTime[0],C_698FreeData_DateLen6);    /*读记录数据日期时间*/

				for(V_i=0;V_i<C_698FreeData_DateLen6;V_i++)
				{
					if(C_Flash_NoEmpty!=V_FindTime[V_i])/*判断数据是否为全FF，即底层为00，说明有时间调整*/
					{
						break;
					}
				}

				if(V_i>=C_698FreeData_DateLen6)/*数据全FF,取下页记录数据地址*/
				{
					V_FlashAddr=(V_FindFlashAddr&0xFFFFF000)+C_OneFlashPage+C_LoadProfile_RevMode;
					if(V_FlashAddr>(V_FlashAddrLate+C_OneFlashPage))
					{
						V_FlashAddr=0xFFFFFFFF;
					}
					else
					{
						V_FlashAddr=SF_JudgeFreezeFlashAddrValid(V_FlashAddr);
					}
				}
			}
			else
			{
				V_FlashAddr=(V_FindFlashAddr&0xFFFFF000)+C_OneFlashPage+C_LoadProfile_RevMode;
				if(V_FlashAddr>(V_FlashAddrLate+C_OneFlashPage))
				{
					V_FlashAddr=0xFFFFFFFF;
				}
				else
				{
					V_FlashAddr=SF_JudgeFreezeFlashAddrValid(V_FlashAddr);
				}
			}
		}
		else/*FlashST...Late---Ear...FlashEnd;*/
		{
			ulong32 V_StaFlashAddr,V_EndFlashAddr;
			uchar8 V_DI2;

			V_StaFlashAddr=Str_698FreezeDataTable[V_Order].V_StaFlashAddr;
			V_EndFlashAddr=Str_698FreezeDataTable[V_Order].V_EndFlashAddr;

			V_DI2=(uchar8)((C_RelatedOAD_Min&0x00FF0000)>>16);
			if(V_DI2==Str_698FreezeDataTable[V_Order].V_DI2)/*分钟冻结*/
			{
				ushort16 V_E2Addr_LoadP_Flash_Ear,V_E2Addr_LoadP_Flash_Late;
				V_Return_Flag=SF_GetMinFreezePro_E2andFlashAddr(V_ProNum,&V_StaFlashAddr,&V_EndFlashAddr,&V_E2Addr_LoadP_Flash_Ear,&V_E2Addr_LoadP_Flash_Late);/*根据分钟冻结方案号，获取该方案最近、最早记录E2地址及该方案起始、结束Flash地址*/
				if(C_OK!=V_Return_Flag)
				{
					return 0xFFFFFFFF;
				}
			}

			if((V_FindFlashAddr>=V_FlashAddrEar)&&(V_FindFlashAddr<(V_EndFlashAddr+C_OneFlashPage)))/*Ear...FlashEnd*/
			{
				V_OffLen=V_FindFlashAddr%C_OneFlashPage;/*页内偏移，不包含上条记录数据长度，*/
				V_OffLen+=(2*V_DataLen);									/* +2*V_DataLen包括上条记录长度及本条需要查找的记录长度*/

				if(V_OffLen<=C_OneFlash_PageNum)/*没有跨页*/
				{
					V_FlashAddr=V_FindFlashAddr+V_DataLen;

					InF_FlashChipSelect();
					InF_ReadFlash(V_FlashAddr,&V_FindTime[0],C_698FreeData_DateLen6);    /*读记录数据日期时间*/

					for(V_i=0;V_i<C_698FreeData_DateLen6;V_i++)
					{
						if(C_Flash_NoEmpty!=V_FindTime[V_i])/*判断数据是否为全FF，即底层为00，说明有时间调整*/
						{
							break;
						}
					}

					if(V_i>=C_698FreeData_DateLen6)/*数据全FF,取下页记录数据地址*/
					{
						V_FlashAddr=(V_FindFlashAddr&0xFFFFF000)+C_OneFlashPage+C_LoadProfile_RevMode;
						if(V_FlashAddr>(V_EndFlashAddr+C_OneFlashPage))
						{
							V_FlashAddr=V_StaFlashAddr+C_LoadProfile_RevMode;/*首页地址*/
						}
						V_FlashAddr=SF_JudgeFreezeFlashAddrValid(V_FlashAddr);
					}
				}
				else
				{
					V_FlashAddr=(V_FindFlashAddr&0xFFFFF000)+C_OneFlashPage+C_LoadProfile_RevMode;
					if(V_FlashAddr>(V_EndFlashAddr+C_OneFlashPage))
					{
						V_FlashAddr=V_StaFlashAddr+C_LoadProfile_RevMode;
					}

					V_FlashAddr=SF_JudgeFreezeFlashAddrValid(V_FlashAddr);
				}
			}
			else/*FlashST...Late*/
			{
				V_OffLen=V_FindFlashAddr%C_OneFlashPage;/*页内偏移，不包含上条记录数据长度，*/
				V_OffLen+=(2*V_DataLen);									/* +2*V_DataLen包括上条记录长度及本条需要查找的记录长度*/

				if(V_OffLen<=C_OneFlash_PageNum)/*没有跨页*/
				{
					V_FlashAddr=V_FindFlashAddr+V_DataLen;

					InF_FlashChipSelect();
					InF_ReadFlash(V_FlashAddr,&V_FindTime[0],C_698FreeData_DateLen6);    /*读记录数据日期时间*/

					for(V_i=0;V_i<C_698FreeData_DateLen6;V_i++)
					{
						if(C_Flash_NoEmpty!=V_FindTime[V_i])/*判断数据是否为全FF，即底层为00，说明有时间调整*/
						{
							break;
						}
					}

					if(V_i>=C_698FreeData_DateLen6)/*数据全FF,取下页记录数据地址*/
					{
						V_FlashAddr=(V_FindFlashAddr&0xFFFFF000)+C_OneFlashPage+C_LoadProfile_RevMode;
						if(V_FlashAddr>(V_FlashAddrLate+C_OneFlashPage))
						{
							V_FlashAddr=0xFFFFFFFF;
						}
						else
						{
							V_FlashAddr=SF_JudgeFreezeFlashAddrValid(V_FlashAddr);
						}
					}
				}
				else
				{
					V_FlashAddr=(V_FindFlashAddr&0xFFFFF000)+C_OneFlashPage+C_LoadProfile_RevMode;
					if(V_FlashAddr>(V_FlashAddrLate+C_OneFlashPage))
					{
						V_FlashAddr=0xFFFFFFFF;
					}
					else
					{
						V_FlashAddr=SF_JudgeFreezeFlashAddrValid(V_FlashAddr);
					}
				}
			}
		}
	}

	if(0xFFFFFFFF!=V_FlashAddr)
	{
		InF_FlashChipSelect();
		InF_ReadFlash(V_FlashAddr,&V_FindTime[0],C_698FreeData_DateLen6);    /*读记录数据日期时间*/
		V_Return_Flag=PF_DataTimeActive_698(&V_FindTime[0],C_DT_Start_ss,C_698FreeData_DateLen6);/*判断时间合法性，去除底层没有记录数据，即全00数据*/
		if(C_OK!=V_Return_Flag)
		{
			V_FlashAddr=0xFFFFFFFF;
		}
	}

	return V_FlashAddr;
}
/*********************************************************************************
函数原型：uchar8 SF_JudgeFreezeProjectAgree(uchar8 V_i)
功能描述：判断该类冻结中，冻结方案是否一致
输入参数：uchar8 V_i：不同冻结方案序号；数据标识OAD；
输出参数：无
返回参数：C_OK(冻结方案一致)、C_Error
功能说明：
调用机制：
备     注：
*********************************************************************************/
uchar8 SF_JudgeFreezeProjectAgree(uchar8 V_i)
{
	uchar8 P_DataOAD_NumTab[C_698Free_OADTabLen];
	uchar8 P_OADTabLen_T[CLI_Free_OADTabLen_T];
	ushort16 V_Order,V_OADTabLen_T,V_OADOrder16,V_j,V_Mode;
	uchar8 V_Return_Flag,V_Return_Flag1=C_Error;
	Str_3aTable V_Str_3aTable;

	if(V_i>=Str_698FreezeDataTable_Len)/*异常判断*/
	{
		return V_Return_Flag1;
	}

	V_Order=Str_698FreezeDataTable[V_i].V_LineNumLen_T;/*698冻结长度、周期数据项所在Str_3aTable行号*/
	if(V_Order >= Str_3aTable_E23RAM_Len)
	{
		return 	V_Return_Flag1;/*异常*/
	}

	V_Str_3aTable=Str_3aTable_E23RAM[V_Order];
	V_Return_Flag=SF_Re_E23_RAM_Data698(&V_Str_3aTable,CLI_Free_OADTabLen_T,&P_OADTabLen_T[0]);
	if(C_OK==V_Return_Flag)
	{
		V_OADTabLen_T=P_OADTabLen_T[0];
		V_OADTabLen_T=V_OADTabLen_T*C_698Free_OADTabDataType;/*序号表每个OAD序号C_698Free_OADTabDataType个字节,目前6字节。2字节序号+2字节冻结周期+2字节存储深度*/
		if(V_OADTabLen_T>C_698Free_OADTabLen)/*数据长度安全性判断*/
		{
			return 	V_Return_Flag1;		/*异常*/
		}

		V_Order=Str_698FreezeDataTable[V_i].V_LineNumTab;/*698冻结序号表所在Str_3aTable行号*/
		if(V_Order >= Str_3aTable_E23RAM_Len)
		{
			return 	V_Return_Flag1;		/*异常*/
		}

		V_Str_3aTable=Str_3aTable_E23RAM[V_Order];
		V_Return_Flag=SF_Re_E23_RAM_Data698(&V_Str_3aTable,V_OADTabLen_T,&P_DataOAD_NumTab[0]);
		if(C_OK!=V_Return_Flag)
		{
			return 	V_Return_Flag1;		/*异常*/
		}

		V_OADTabLen_T=V_OADTabLen_T/C_698Free_OADTabDataType;
		PF_Buffer2ToUshort16(&P_DataOAD_NumTab[2],&V_OADOrder16);/*冻结周期*/
		V_Mode=V_OADOrder16;					/*取不同冻结模式方案*/
		for(V_j=1;V_j<V_OADTabLen_T;V_j++)
		{
			PF_Buffer2ToUshort16(&P_DataOAD_NumTab[C_698Free_OADTabDataType*V_j+2],&V_OADOrder16);
			if(V_Mode!=V_OADOrder16)
			{
				break;
			}
		}

		if(V_j>=V_OADTabLen_T)/*冻结模式相同*/
		{
			V_Return_Flag1=C_OK;
		}
	}

	return V_Return_Flag1;
}
/******************************************************************************************
函数原型：uchar8 SF_JudgeReadCycSame(uchar8 V_ProNum,uchar8 V_i,ushort16 V_IntervalTime,ushort16 *P_usFreezCyc))
功能描述：判断抄读周期与冻结周期是否一致
输入参数：uchar8 V_ProNum：分钟冻结用方案号
		uchar8 V_i：不同冻结方案序号；数据标识OAD；
		ushort16 V_IntervalTime：抄读周期；
输出参数：无
返回参数：0xAA返回冻结周期一致、0x55不一致
功能说明：
调用机制：1）获取冻结周期2）判断周期与间隔是否一致
备     注：
*********************************************************************************/
uchar8 SF_JudgeReadCycSame(uchar8 V_ProNum,uchar8 V_i,ushort16 V_IntervalTime)
{
	uchar8 P_DataOAD_NumTab[C_698Free_OADTabLen];
	uchar8 P_OADTabLen_T[CLI_Free_OADTabLen_T];
	ushort16 V_Order,V_OADTabLen_T,V_OADCyc16;
	uchar8 V_Return_Flag,V_Return_Flag1=0x55;
	Str_3aTable V_Str_3aTable;
	uchar8 V_DI;

	if(V_i>=Str_698FreezeDataTable_Len)/*异常判断*/
	{
		return	V_Return_Flag1;
	}

	V_Order=Str_698FreezeDataTable[V_i].V_LineNumLen_T;/*698冻结长度、周期数据项所在Str_3aTable行号*/
	if(V_Order >= Str_3aTable_E23RAM_Len)
	{
		return 	V_Return_Flag1;/*异常*/
	}

	V_Str_3aTable=Str_3aTable_E23RAM[V_Order];
	V_Return_Flag=SF_Re_E23_RAM_Data698(&V_Str_3aTable,CLI_Free_OADTabLen_T,&P_OADTabLen_T[0]);
	if(C_OK==V_Return_Flag)
	{
		V_OADTabLen_T=P_OADTabLen_T[0];
		V_OADTabLen_T=V_OADTabLen_T*C_698Free_OADTabDataType;/*序号表每个OAD序号C_698Free_OADTabDataType个字节,目前6字节。2字节序号+2字节冻结周期+2字节存储深度*/
		if(V_OADTabLen_T>=C_698Free_OADTabLen)/*数据长度安全性判断*/
		{
			return 	V_Return_Flag1;/*异常*/
		}
		V_Order=Str_698FreezeDataTable[V_i].V_LineNumTab;/*698冻结序号表所在Str_3aTable行号*/
		if(V_Order >= Str_3aTable_E23RAM_Len)
		{
			return 	V_Return_Flag1;/*异常*/
		}
		V_Str_3aTable=Str_3aTable_E23RAM[V_Order];
		V_Return_Flag=SF_Re_E23_RAM_Data698(&V_Str_3aTable,V_OADTabLen_T,&P_DataOAD_NumTab[0]);
		if(C_OK!=V_Return_Flag)
		{
			return 	V_Return_Flag1;/*异常*/
		}
		V_DI=(uchar8)(C_RelatedOAD_Min>>16);
		if(Str_698FreezeDataTable[V_i].V_DI2==V_DI)/*判断分钟冻结*/
		{
			V_OADTabLen_T=SF_GetMinFreezeNum_OADTab(V_ProNum,&P_DataOAD_NumTab[0],V_OADTabLen_T);/*获取分钟冻结方案号，对应的OAD关联列表及关联OAD个数*/
			if(0xFFFF==V_OADTabLen_T)
			{
				return 	V_Return_Flag1;/*异常*/
			}
		}

		PF_Buffer2ToUshort16(&P_DataOAD_NumTab[2],&V_OADCyc16);
		if(V_OADCyc16==V_IntervalTime)					/*冻结周期判断*/
		{
			V_Return_Flag1=0xAA;
		}
	}

	return V_Return_Flag1;
}
/*********************************************************************************
函数原型：uchar8 SF_GetTolMinFreeze_OADTab(uchar8 *P_DataOAD_NumTab,ushort16 *V_Length)
功能描述*获取分钟冻结总OAD关联列表。
输入参数：uchar8 *V_Length：读数据缓存区最大长度；
输出参数：uchar8 *P_DataOAD_NumTab：方案号对应的OAD关联列表数据.
		uchar8 *V_Length：所读数据实际长度；
返回参数：C_OK,C_Error
功能说明：
调用机制：
备     注：
*********************************************************************************/
uchar8 SF_GetTolMinFreeze_OADTab(uchar8 *P_DataOAD_NumTab,ushort16 *V_Length)
{
	uchar8 P_OADTabLen_T[CLI_Free_OADTabLen_T];
	ushort16 V_Order,V_OADTabLen_T;
	uchar8 V_Return_Flag=C_Error;
	Str_3aTable V_Str_3aTable;
	uchar8 V_i;

	if(*V_Length<C_698Free_OADTabLen)/*缓存根据最大判断*/
	{
		return V_Return_Flag;
	}

	V_i=SF_GetStr_698FreezeDataTableOrder(C_RelatedOAD_Min);/*获取某类冻结数据在Str_698FreezeDataTable中序号*/
	if(V_i>=Str_698FreezeDataTable_Len)/*异常判断*/
	{
		return V_Return_Flag;
	}

	V_Order=Str_698FreezeDataTable[V_i].V_LineNumLen_T;/*698冻结长度、周期数据项所在Str_3aTable行号*/
	if(V_Order >= Str_3aTable_E23RAM_Len)
	{
		return V_Return_Flag;/*异常*/
	}

	V_Str_3aTable=Str_3aTable_E23RAM[V_Order];
	V_Return_Flag=SF_Re_E23_RAM_Data698(&V_Str_3aTable,CLI_Free_OADTabLen_T,&P_OADTabLen_T[0]);
	if(C_OK==V_Return_Flag)
	{
		V_OADTabLen_T=P_OADTabLen_T[0];
		V_OADTabLen_T=V_OADTabLen_T*C_698Free_OADTabDataType;/*序号表每个OAD序号C_698Free_OADTabDataType个字节,目前6字节。2字节序号+2字节冻结周期+2字节存储深度*/
		if(V_OADTabLen_T>C_698Free_OADTabLen)/*数据长度安全性判断*/
		{
			return C_Error;/*异常*/
		}

		V_Order=Str_698FreezeDataTable[V_i].V_LineNumTab;/*698冻结序号表所在Str_3aTable行号*/
		if(V_Order >= Str_3aTable_E23RAM_Len)
		{
			return C_Error;/*异常*/
		}

		V_Str_3aTable=Str_3aTable_E23RAM[V_Order];
		V_Return_Flag=SF_Re_E23_RAM_Data698(&V_Str_3aTable,V_OADTabLen_T,&P_DataOAD_NumTab[0]);
		if(C_OK!=V_Return_Flag)
		{
			return C_Error;/*异常*/
		}

		*V_Length=V_OADTabLen_T;
	}

	return V_Return_Flag;
}
/*********************************************************************************
函数原型：uchar8 InF_GetMinFreezeTolNum(void)
功能描述：获取分钟冻结总方案数，
输入参数：无
输出参数：无；
返回参数：方案总数1---8，异常FF
功能说明：
调用机制：
备     注：根据分钟OAD列表得到方案总数，不同冻结周期认为是不同方案
*********************************************************************************/
uchar8 InF_GetMinFreezeTolNum(void)
{
	uchar8 P_DataOAD_NumTab[C_698Free_OADTabLen];
	ushort16 V_OADTabLen_T=C_698Free_OADTabLen;
	uchar8 V_Return_Flag;
	uchar8 V_ProNum=0xFF;
	ushort16 V_Cyc16[8]={0xFFFF};

	V_Return_Flag=SF_GetTolMinFreeze_OADTab(P_DataOAD_NumTab,&V_OADTabLen_T);
	if(C_OK==V_Return_Flag)
	{
		V_ProNum=SF_GetMinFreezeTolNum(&P_DataOAD_NumTab[0],V_OADTabLen_T,&V_Cyc16[0]);
	}
	return V_ProNum;
}

/*********************************************************************************
函数原型：uchar8 InF_GetMinFreezeNum_OADTab(uchar8 V_ProNum,uchar8 *P_DataOAD_NumTab,ushort16 *P_Length)
功能描述：获取分钟冻结方案号对应的OAD关联列表。
输入参数：uchar8 V_ProNum：分钟冻结方案号(从0开始)，不能超过总方案数-1,0--7
		uchar8 *P_Length：读数据缓存区最大长度；
输出参数：uchar8 *P_DataOAD_NumTab：方案号对应的OAD关联列表数据.
		uchar8 *P_Length：所读数据实际长度；
返回参数：C_OK,C_Error
功能说明：
调用机制：
备     注：分钟冻结方案号从0开始，不能超过总方案数。函数内部会判断方案号的合理性
*********************************************************************************/
uchar8 InF_GetMinFreezeNum_OADTab(uchar8 V_ProNum,uchar8 *P_DataOAD_NumTab,ushort16 *P_Length)
{
	ushort16 V_OADTabLen_T;
	uchar8 V_Return_Flag=C_Error;

	if(V_ProNum>7)/*0--7*/
	{
		return V_Return_Flag;
	}

	if(*P_Length<C_698Free_OADTabLen)/*缓存根据最大判断*/
	{
		return V_Return_Flag;
	}

	V_Return_Flag=SF_GetTolMinFreeze_OADTab(P_DataOAD_NumTab,P_Length);/*获取分钟冻结总关联列表*/
	if(C_OK==V_Return_Flag)
	{
		V_OADTabLen_T=SF_GetMinFreezeNum_OADTab(V_ProNum,&P_DataOAD_NumTab[0],*P_Length);/*获取分钟冻结方案号，对应的OAD关联列表及关联OAD个数*/
		if(0xFFFF==V_OADTabLen_T)/*异常*/
		{
			V_Return_Flag=C_Error;
		}
		else
		{
			*P_Length=V_OADTabLen_T*C_698Free_OADTabDataType;
		}
	}

	return V_Return_Flag;
}
/*******************************************************************************
函数原型：ulong32 SF_FindMinFreezeFirstVolidOAD(ulong32 *P_Data_Id_OAD)
功能描述：根据分钟冻结OAD关联列表，查找第1个有效的OAD
输入参数：ulong32 *P_Data_Id_OAD：OAD缓存
输出参数：ReturnFlag：698错误类型
返回参数：ulong32存在的OAD，假如不存在返回0xFFFFFFFF,异常返回0xFFFFFFFE
调用位置：
备     注：
*******************************************************************************/
ulong32 SF_FindMinFreezeFirstVolidOAD(ulong32 *P_Data_Id_OAD)
{
	uchar8 P_DataOAD_NumTab[C_698Free_OADTabLen];
	uchar8 P_OADTabLen_T[CLI_Free_OADTabLen_T];
	ushort16 V_Order,V_OADTabLen_T,V_OADOrder16,V_j,V_k,V_EventSign;
	uchar8 V_Return_Flag,V_ucAAFlag=0;
	Str_3aTable V_Str_3aTable;
	ulong32 V_OADNum = 0xFFFFFFFF;
	uchar8 V_i;
	ulong32 V_ulOAD;

	V_i=SF_GetStr_698FreezeDataTableOrder(C_RelatedOAD_Min);/*获取某类冻结数据在Str_698FreezeDataTable中序号*/
	if(V_i>=Str_698FreezeDataTable_Len)/*异常判断*/
	{
		return	V_OADNum;
	}

	V_Order=Str_698FreezeDataTable[V_i].V_LineNumLen_T;/*698冻结长度、周期数据项所在Str_3aTable行号*/
	if(V_Order >= Str_3aTable_E23RAM_Len)
	{
		return 	V_OADNum;/*异常*/
	}

	V_Str_3aTable=Str_3aTable_E23RAM[V_Order];
	V_Return_Flag=SF_Re_E23_RAM_Data698(&V_Str_3aTable,CLI_Free_OADTabLen_T,&P_OADTabLen_T[0]);
	if(C_OK==V_Return_Flag)
	{
		V_OADTabLen_T=P_OADTabLen_T[0];
		V_OADTabLen_T=V_OADTabLen_T*C_698Free_OADTabDataType;/*序号表每个OAD序号C_698Free_OADTabDataType个字节,目前6字节。2字节序号+2字节冻结周期+2字节存储深度*/
		if(V_OADTabLen_T>C_698Free_OADTabLen)/*数据长度安全性判断*/
		{
			return 	V_OADNum;/*异常*/
		}
		V_Order=Str_698FreezeDataTable[V_i].V_LineNumTab;/*698冻结序号表所在Str_3aTable行号*/
		if(V_Order >= Str_3aTable_E23RAM_Len)
		{
			return 	V_OADNum;/*异常*/
		}
		V_Str_3aTable=Str_3aTable_E23RAM[V_Order];
		V_Return_Flag=SF_Re_E23_RAM_Data698(&V_Str_3aTable,V_OADTabLen_T,&P_DataOAD_NumTab[0]);
		if(C_OK!=V_Return_Flag)
		{
			return 	V_OADNum;/*异常*/
		}
		V_OADTabLen_T=V_OADTabLen_T/C_698Free_OADTabDataType;	/*序号表每个OAD序号C_698Free_OADTabDataType个字节,目前6字节。2字节序号+2字节冻结周期+2字节存储深度*/

		while(0xFFFFFFFF!=(*P_Data_Id_OAD))
		{
			/*查询关联列表*/
			V_j=0;
			V_ucAAFlag = 0;
			for(;V_j<V_OADTabLen_T;V_j++)
			{
				PF_Buffer2ToUshort16(&P_DataOAD_NumTab[C_698Free_OADTabDataType*V_j],&V_OADOrder16);
				V_EventSign=(V_OADOrder16&0xE000);/*根据698 OAD，DI1高3位表示不同属性，与设计方式有关*/
				V_OADOrder16 &= 0x1FFF;
				if(V_OADOrder16 >= Str_FrozenConvert_Table_Len)
				{
					return 	V_OADNum;/*异常，正常不存在*/
				}
                if( ( (*P_Data_Id_OAD) & 0xFF000000 ) == 0x00000000 )		/*电能类*/
                {
                    if( ( (*P_Data_Id_OAD) & 0x00000F00 ) == 0x00000400 )	/*高精度电能*/
                    {
                        V_ulOAD = ( ( (*P_Data_Id_OAD) & 0xFFFFF0FF ) | 0x00000200 );
                    }
                    else if( ( (*P_Data_Id_OAD) & 0x00000F00 ) == 0x00000200 )
                    {
                        V_ulOAD = ( ( (*P_Data_Id_OAD) & 0xFFFFF0FF ) | 0x00000400 );
                    }
                    else
                    {
                        V_ulOAD = (*P_Data_Id_OAD);
                    }
                }
                else
                {
                    V_ulOAD = (*P_Data_Id_OAD);
                }
				if( ( (*P_Data_Id_OAD) == ( Str_FrozenConvert_Table[V_OADOrder16].V_ulOAD | V_EventSign ) )			/*单独OAD相等*/
                 || ( V_ulOAD == ( Str_FrozenConvert_Table[V_OADOrder16].V_ulOAD | V_EventSign ) ) )
				{
					V_ucAAFlag = 0x68;
					break;
				}
				else
				{
					if(C_array==Str_FrozenConvert_Table[V_OADOrder16].V_uc698Type)/*数组格式OAD,查询是否为分OAD*/
					{
						for(V_k=0;;V_k++)
						{
							if((Str_FrozenConvert_Table[V_OADOrder16+V_k+1].V_ulOAD&0xFFFFFF00)==
							   (Str_FrozenConvert_Table[V_OADOrder16].V_ulOAD&0xFFFFFF00))
							{
								if( ( (* P_Data_Id_OAD) == ( Str_FrozenConvert_Table[V_OADOrder16 + V_k + 1].V_ulOAD | V_EventSign ) )
                                 || ( V_ulOAD == ( Str_FrozenConvert_Table[V_OADOrder16 + V_k + 1].V_ulOAD | V_EventSign ) ) )
								{
									V_ucAAFlag = 0x68;
									break;
								}
							}
							else
							{
								break;
							}
						}
						if(V_ucAAFlag == 0x68)
						{
							break;
						}
					}
				}
			}
			if(V_ucAAFlag == 0x68)/*存在OAD*/
			{
				V_OADNum=*P_Data_Id_OAD;
				break;
			}
			P_Data_Id_OAD++;
		}
	}
	return V_OADNum;
}
/*******************************************************************************
函数原型：uchar8 SF_GetMinFreezeProNum(ulong32 V_Data_Id_OAD, uchar8 *pV_Cycle)
功能描述：判断该OAD为分钟冻结的方案号，0-7
输入参数：ulong32 V_Data_Id_OAD：分钟冻结，需要读取的列OAD
输出参数：
返回参数：方案号0-7，异常为0xFF；所查OAD不存在返回0xFE
调用位置：
备     注：
*******************************************************************************/
uchar8 SF_GetMinFreezeProNum(ulong32 V_Data_Id_OAD, uchar8 *pV_Cycle)
{
	uchar8 V_ProNum=0xFF;
	uchar8 P_DataOAD_NumTab[C_698Free_OADTabLen];
	uchar8 P_OADTabLen_T[CLI_Free_OADTabLen_T];
	ushort16 V_Order,V_OADTabLen_T,V_OADOrder16,V_i,V_k,V_EventSign;
	uchar8 V_Return_Flag;
	Str_3aTable V_Str_3aTable;
	ulong32 V_ulOAD;

	V_i=SF_GetStr_698FreezeDataTableOrder(C_RelatedOAD_Min);/*获取某类冻结数据在Str_698FreezeDataTable中序号*/
	if(V_i<Str_698FreezeDataTable_Len)
	{
		V_Order=Str_698FreezeDataTable[V_i].V_LineNumLen_T;/*698冻结长度、周期数据项所在Str_3aTable行号*/
		if(V_Order >= Str_3aTable_E23RAM_Len)
		{
			return 	V_ProNum;/*异常*/
		}
		V_Str_3aTable=Str_3aTable_E23RAM[V_Order];
		V_Return_Flag=SF_Re_E23_RAM_Data698(&V_Str_3aTable,CLI_Free_OADTabLen_T,&P_OADTabLen_T[0]);
		if(C_OK==V_Return_Flag)
		{
			V_OADTabLen_T=P_OADTabLen_T[0];
			V_OADTabLen_T=V_OADTabLen_T*C_698Free_OADTabDataType;/*序号表每个OAD序号C_698Free_OADTabDataType个字节,目前6字节。2字节序号+2字节冻结周期+2字节存储深度*/
			if(V_OADTabLen_T>C_698Free_OADTabLen)/*数据长度安全性判断*/
			{
				return V_ProNum;/*异常*/
			}
			V_Order=Str_698FreezeDataTable[V_i].V_LineNumTab;/*698冻结序号表所在Str_3aTable行号*/
			if(V_Order >= Str_3aTable_E23RAM_Len)
			{
				return V_ProNum;/*异常*/
			}
			V_Str_3aTable=Str_3aTable_E23RAM[V_Order];
			V_Return_Flag=SF_Re_E23_RAM_Data698(&V_Str_3aTable,V_OADTabLen_T,&P_DataOAD_NumTab[0]);
			if(C_OK!=V_Return_Flag)
			{
				return V_ProNum;/*异常*/
			}

			V_OADTabLen_T=V_OADTabLen_T/C_698Free_OADTabDataType;
			uchar8 V_SignTemp=0x55;
			for(V_i=0;V_i<V_OADTabLen_T;V_i++)
			{
				PF_Buffer2ToUshort16(&P_DataOAD_NumTab[C_698Free_OADTabDataType*V_i],&V_OADOrder16);
				V_EventSign=(V_OADOrder16&0xE000);					/*根据698 OAD，DI1高3位表示不同属性，与设计方式有关*/
				V_OADOrder16 &= 0x1FFF;
				if(V_OADOrder16>=Str_FrozenConvert_Table_Len)
				{
					return 	V_ProNum;								/*异常*/
				}
				/************************************************************************************/
				/*因为费控流程增加*/
				/*抄读冻结电能，采用方法2，列选冻结时间和电能，电能不是冻结列表中的数据，但与冻结数据同周期，应答为冻结时间+NULL。*/
                if((V_Data_Id_OAD & 0xFF000000) == 0x00000000)		/*电能类*/
                {
                    if((V_Data_Id_OAD & 0x00000F00) == 0x00000400)	/*高精度电能*/
                    {
                        V_ulOAD = ((V_Data_Id_OAD & 0xFFFFF0FF)| 0x00000200);
                    }
                    else if((V_Data_Id_OAD & 0x00000F00) == 0x00000200)
                    {
                        V_ulOAD = ((V_Data_Id_OAD & 0xFFFFF0FF)| 0x00000400);
                    }
                    else
                    {
                        V_ulOAD = V_Data_Id_OAD;
                    }
                }
                else
                {
                    V_ulOAD = V_Data_Id_OAD;
                }
				/************************************************************************************/
				if( ( V_Data_Id_OAD == ( Str_FrozenConvert_Table[V_OADOrder16].V_ulOAD | V_EventSign ) )	/*单独OAD相等*/
                 || ( V_ulOAD == ( Str_FrozenConvert_Table[V_OADOrder16].V_ulOAD | V_EventSign ) ) )
				{
					V_SignTemp=0xAA;
					break;
				}
				else
				{
					if(C_array==Str_FrozenConvert_Table[V_OADOrder16].V_uc698Type)				/*数组格式OAD,查询是否为分OAD*/
					{
						for(V_k=0;;V_k++)
						{
							if((Str_FrozenConvert_Table[V_OADOrder16+V_k+1].V_ulOAD&0xFFFFFF00)
								 ==(Str_FrozenConvert_Table[V_OADOrder16].V_ulOAD&0xFFFFFF00))
							{
								if((V_Data_Id_OAD ==(Str_FrozenConvert_Table[V_OADOrder16+V_k+1].V_ulOAD|V_EventSign))
                                   || (V_ulOAD ==(Str_FrozenConvert_Table[V_OADOrder16+V_k+1].V_ulOAD|V_EventSign)))
								{
									V_SignTemp=0xAA;
									break;
								}
							}
							else
							{
								break;
							}
						}
						if(V_SignTemp==0xAA)
						{
							break;
						}
					}
				}
			}
			if((V_SignTemp==0xAA)&&(V_i<V_OADTabLen_T))	/*查找到满足OAD*/
			{
				ushort16 V_Cyc16[8]={0xFFFF};
				V_k=SF_GetMinFreezeTolNum(&P_DataOAD_NumTab[0],(V_OADTabLen_T*C_698Free_OADTabDataType),&V_Cyc16[0]);/*获取分钟冻结方案号及不同的冻结周期*/
				if((V_k<9)&&(V_k>0))/*方案总数1--8*/
				{
					PF_Buffer2ToUshort16(&P_DataOAD_NumTab[C_698Free_OADTabDataType*V_i+2],&V_OADOrder16);/*冻结周期*/
					while(V_k)
					{
						if(V_Cyc16[V_k-1]==V_OADOrder16)/*周期相等*/
						{
							break;
						}
						V_k--;
					}
					if(V_k>0)
					{
						V_ProNum=V_k-1;
					}
				}
			}
			else
			{
				V_ProNum=0xFE;/*OAD关联列表不存在*/
			}
		}
	}
    *pV_Cycle = V_OADOrder16;
	return V_ProNum;
}
/*******************************************************************************
函数原型：uchar8   SF_GetMinFreezePro_E2Addr(ulong32 V_Data_Id_OAD, ushort16 *P_E2Addr_LoadP_Flash_Ear, ushort16 *P_E2Addr_LoadP_Flash_Late)
功能描述：获取分钟冻结某类方案对应记录，最早、最近Flash存E2地址
输入参数：ulong32 V_Data_Id_OAD：分钟冻结，需要读取的列OAD
输出参数：ushort16 *P_E2Addr_LoadP_Flash_Ear:返回该冻结方案，最早Flash记录存E2地址
		ushort16 *P_E2Addr_LoadP_Flash_Late:返回该冻结方案，最近Flash记录存E2地址
返回参数：C_OK、C_SPIError、C_DataLenError、C_NoAccess、C_Error(数据格式错)、C_SafeFlagError、C_IICError；
调用位置：
备    注：
*******************************************************************************/
uchar8 SF_GetMinFreezePro_E2Addr(ulong32 V_Data_Id_OAD, ushort16 *P_E2Addr_LoadP_Flash_Ear, ushort16 *P_E2Addr_LoadP_Flash_Late)
{
	uchar8 V_ProNum, V_Return_Flag = C_Error, V_Cycle = 15;

	V_ProNum = SF_GetMinFreezeProNum(V_Data_Id_OAD, &V_Cycle);		/*获取分钟冻结方案号，异常返回0xFF,不存在OAD返回0xFE*/
	if(V_ProNum < 8)	/*8种方案，方案号0--7*/
	{
		*P_E2Addr_LoadP_Flash_Ear = E2Addr_Min_Free_Flash_Ear1 + V_ProNum * 12;
		*P_E2Addr_LoadP_Flash_Late = *P_E2Addr_LoadP_Flash_Ear + 6;
		V_Return_Flag = C_OK;
	}
	return V_Return_Flag;
}
/*********************************************************************************
函数原型：void InF_WriteFreezeData(uchar8 V_Num)
功能描述：通信模块调用，用于通信写还未编码的次数
输入参数：uchar8 V_Num：抄读数据层冻结数据返回条数-通信能编码的条数
输出参数：无
返回参数：无
功能说明：用于通信返写，没有编码的条数(数据层冻结数据返回条数-通信能编码的条数)，用于非周期冻结，时间不覆盖
调用机制：
备     注：该函数内部会判断写入次数不能大于非周期性冻结最大次数，如超过则不更新数据层内部全局次数GV_FreezeLastNum
		该函数增加原因：通信抄读非周期冻结时，假如数据层返回5条数据(数据层内部GV_FreezeLastNum会记录已经查找到多少条)，实际通信编码4条。
		通信读后续帧时，就会出现数据层已经返回而通信没有编码数据，会读不到。
*********************************************************************************/
void InF_WriteFreezeData(uchar8 V_Num)
{
	ushort16 V_CRC16;

	if(V_Num>C_NextLoadTime_MaxNum)/*非周期最大次数*/
	{
		return;
	}
	if(C_OK==PF_Check_CRC(&GV_FreezeLastNum[0],3))
	{
		GV_FreezeLastNum[0] += V_Num;
		V_CRC16=PF_Cal_CRC(&GV_FreezeLastNum[0],1);/*保存上次查找到第几次*/
		PF_Ushort16ToBuffer2(&GV_FreezeLastNum[1],&V_CRC16);
	}
}
/*******************************************************************************
函数原型：uchar8  InF_ReadFreezeData(ulong32 * P_Data_Id_OAD,uchar8 * P_FixTime,uchar8 * P_Data,ushort16 * V_BlockNum,
									ushort16 * V_Length,ushort16 V_IntervalTime,uchar8 * pV_FreezeTimeBuf,uchar8 V_Mode)
功能描述：读冻结数据接口函数，通信调用，返回数据根据传入的OAD顺序
输入参数：ulong32 *P_Data_Id_OAD：数据标识OAD；第一个OAD表示读取冻结类型，例如50000200，表示读取瞬时冻结，最低2字节00表示表示按日期读取，
					非00表示读取上XX次记录，此时* P_FixTime、V_IntervalTime、V_BlockNum无效.
					后续OAD顺序为关联属性对应OAD顺序，当查找OAD为FFFFFFFF则表示，该条记录读取记录OAD结束
		uchar8 *P_FixTime：给定时间记录块，12个字节。按时间区间抄读，前6个字节表示起始时间，后6个字节表示结束时间，时间格式ssmmhhDDMMYY
							按固定时间抄读时，只有前6个字节有效。当时间区间读需后续帧时，前6个字节为下一块记录时间。
		ushort16 *V_BlockNum：输入参数，目前按固定时间抄读，数据为1；按时间区间抄读，该数据为非1；
		uchar8 *V_Length：读数据缓存区最大长度；
		ushort16 V_IntervalTime：间隔时间，16进制形式，单位分钟
输出参数：uchar8 *P_FixTime：作为输出参数时，当有后续帧时，返回下一个记录块记录时间(前6个字节)(记录不覆盖这种，类似结算日冻结，后续帧不返回下帧时间)，方便通讯模块读后续帧用。
		ushort16 *V_BlockNum：目前周期抄读用，bit0-1表示是否有后续帧，当有后续帧返回非0数(目前固定为2)，无后续帧返回0,当有后续帧返回非0数，无后续帧返回0
							bit2--15：表示本次抄读返回记录的数据块数
		uchar8 *V_Length：所读数据实际长度；
		uchar8 *P_Data：读数据存放缓存；
		uchar8 *pV_FreezeTimeBuf：返回最近n条，冻结时间，通信读后续帧判断用；
返回参数：C_OK、C_IICError、C_SPIError、C_DataLenError、C_IDError、C_NoData、C_Error
调用位置：
备     注：当按固定时间抄读时，返回数据为相等时间点数据。按时间区间抄读时，第1个时间点数据为起始时间往后的最近1个时间点数据,
		后续时间点数据为满足条件的第1个时间+间隔周期，相等时间点数据
*******************************************************************************/
uchar8 InF_ReadFreezeData(ulong32 *P_Data_Id_OAD,uchar8 *P_FixTime,uchar8 *P_Data,ushort16 *V_BlockNum,ushort16 *V_Length,ushort16 V_IntervalTime,uchar8 *pV_FreezeTimeBuf,uchar8 V_Mode)
{
	uchar8 V_DI[4],V_Return_Flag;
	uchar8 V_FlashAddr8[4];
	ulong32 V_FlashAddrLate,V_FlashAddrEar,V_FindFlashAddr,V_FlashAddr32;
	ushort16 V_TotalLen,V_Num;
	uchar8 V_Order;
	ushort16 V_E2Addr_LoadP_Flash_Late,V_E2Addr_LoadP_Flash_Ear;
	uchar8 V_StarTime[C_698FreeData_DateLen6],V_FindTime[C_698FreeData_DateLen6],V_CompareSign,V_CompareSign_STEnd;
	uchar8 V_ucCompareFlag;
	ushort16 V_usCountCycle=0;
	uchar8 V_ucJudgeCycleBuf[C_698FreeData_DateLen6];
	uchar8 V_AddLen, V_Cycle = 15;

	if(V_Mode == C_645Mode)
	{
		V_AddLen = 5;
	}
	else
	{
		V_AddLen = 0;
	}

	GV_ReadLoadFlashAddr32=0xFFFFFFFF;/*每次抄读都重新初始化该变量。主要用于修改时间覆盖用，避免重复查找，提高遍历查询抄读效率*/
	PF_Ulong32ToBuffer4(&V_DI[0],&P_Data_Id_OAD[0],4);
	if((C_RelatedOAD_Immid&0xFF000000)!=(P_Data_Id_OAD[0]&0xFF000000))/*非冻结记录*/
	{
		return C_IDError;
	}

	if((P_Data_Id_OAD[0]&0xFFFF0000)==(C_RelatedOAD_Min&0xFFFF0000))/*分钟冻结*/
	{
		ulong32 *P_Data_Id_OADTemp=&P_Data_Id_OAD[1];
		uchar8 V_temp=0x55;
		while(*P_Data_Id_OADTemp!=0xFFFFFFFF)/*循环判断OAD列表*/
		{
			if((*P_Data_Id_OADTemp!=CFreeTime)&&(*P_Data_Id_OADTemp!=CFreeNum))/*分钟冻结不允许，单独读时间或序号*/
			{
				V_temp=0xAA;
				break;
			}
			P_Data_Id_OADTemp++;
		}
		if(V_temp==0x55)
		{
			return C_RWForbid_DAR;
		}
	}

	V_Order=SF_GetStr_698FreezeDataTableOrder(P_Data_Id_OAD[0]);/*获取某类冻结数据在Str_698FreezeDataTable中序号*/
	if(0xFF==V_Order)
	{
		return C_IDError;
	}
	if((*V_Length)==0)
	{
		return C_DataLenError;
	}

	V_E2Addr_LoadP_Flash_Late=Str_698FreezeDataTable[V_Order].V_E2AddrLate;
	V_E2Addr_LoadP_Flash_Ear=Str_698FreezeDataTable[V_Order].V_E2AddrEar;

	ulong32 V_VolidOADTemp = 0xFFFFFFFF;
	if((P_Data_Id_OAD[0]&0xFFFF0000)==(C_RelatedOAD_Min&0xFFFF0000))/*分钟冻结*/
	{
		V_VolidOADTemp=SF_FindMinFreezeFirstVolidOAD(&P_Data_Id_OAD[1]);/*根据关联列表查找第一个有效的AOD，即关联列表中存在的OAD。*/
		if(0xFFFFFFFF==V_VolidOADTemp)
		{
			return C_NoData;
		}

		V_Return_Flag=SF_GetMinFreezePro_E2Addr(V_VolidOADTemp,&V_E2Addr_LoadP_Flash_Ear,&V_E2Addr_LoadP_Flash_Late);/*根据该所读OAD判断方案号，获取分钟冻结，某方案对应的最早、最近记录存E2地址*/
		if(C_OK!=V_Return_Flag)
		{
			return V_Return_Flag;
		}
	}

	V_Return_Flag = SF_ReadE2Three(V_E2Addr_LoadP_Flash_Late,4,&V_FlashAddr8[0]);        /*取最近1条记录Flash页地址*/
	if(V_Return_Flag != C_OK)
	{
		return	V_Return_Flag;
	}

	PF_Buffer4ToUlong32(&V_FlashAddr8[0],&V_FlashAddrLate,4);
	V_FlashAddrLate&=0xFFFFF000;             /*页地址转化，增加容错性*/

	V_Return_Flag = SF_ReadE2Three(V_E2Addr_LoadP_Flash_Ear,4,&V_FlashAddr8[0]);        /*取最早1条记录Flash页地址*/
	if(V_Return_Flag != C_OK)
	{
		return	V_Return_Flag;
	}

	PF_Buffer4ToUlong32(&V_FlashAddr8[0],&V_FlashAddrEar,4);

	if(V_FlashAddrEar==V_FlashAddrLate)	/*没有记录数据*/
	{
		return	C_NoData;
	}

	ushort16 V_DataLen;/*每条冻结记录数据长度*/
	uchar8 V_ProNum = 0,V_DI2Temp;
	V_DI2Temp=V_DI[2];
	if((P_Data_Id_OAD[0]&0xFFFF0000)==(C_RelatedOAD_Min&0xFFFF0000))/*分钟冻结*/
	{
		V_ProNum = SF_GetMinFreezeProNum(V_VolidOADTemp, &V_Cycle);			/*获取分钟冻结方案号，异常返回0xFF*/
		if(V_ProNum>8)/*方案号0--7*/
		{
			return C_NoData;
		}
		else
		{
			V_DI2Temp=(V_DI[2]&0x1F);/*增加方案号*/
			V_DI2Temp |= (V_ProNum<<5);
		}
	}

	V_DataLen=SF_JudgeWriteDataLen(V_DI2Temp);
	if(0==V_DataLen)/*异常判断*/
	{
		return	C_Error;
	}

	V_TotalLen=0;   /*读N块负荷记录时，用于记录总数据长度*/
	V_Num=V_DI[0];
	uchar8 V_MaxNum;

	switch((*P_Data_Id_OAD&0xFFFF0000))
	{
		case	(C_RelatedOAD_Immid&0xFFFF0000):   /*冻结时间不覆盖*/
			V_MaxNum=C_FreezeImmid_MaxNum;
			break;
		case	(C_RelatedOAD_Settle&0xFFFF0000):
			V_MaxNum=C_NextLoadTime_MaxNum;
			break;
		case	(C_RelatedOAD_YSettle&0xFFFF0000):
			V_MaxNum=C_YSettleFreeze_MaxNum;
			break;
		case	(C_RelatedOAD_TimeZone&0xFFFF0000):
		case	(C_RelatedOAD_TimeRegion&0xFFFF0000):
		case	(C_RelatedOAD_RateTalbe&0xFFFF0000):
		case	(C_RelatedOAD_StepTable&0xFFFF0000):
			V_MaxNum=C_FreezeTimeZone_MaxNum;
			break;
		default:
			V_MaxNum=0xFF;
	}

	if(0xFF!=V_MaxNum)/*非周期性冻结*/
	{
		if(V_Num>V_MaxNum)/*非周期性冻结最大次数限制*/
		{
			return C_NoData;
		}
	}

	if(0==V_Num)/*按时间抄读数据*/
	{
		switch((*P_Data_Id_OAD&0xFFFF0000))
		{
			case	(C_RelatedOAD_Immid&0xFFFF0000):   /*冻结时间不覆盖*/
			case	(C_RelatedOAD_Settle&0xFFFF0000):
			case	(C_RelatedOAD_TimeZone&0xFFFF0000):
			case	(C_RelatedOAD_TimeRegion&0xFFFF0000):
			case	(C_RelatedOAD_RateTalbe&0xFFFF0000):
			case	(C_RelatedOAD_StepTable&0xFFFF0000):
			case	(C_RelatedOAD_YSettle&0xFFFF0000):
			{
				uchar8 V_Num2,V_Num1;

				V_Num1=1;/*默认从上1开始*/
				V_Num2=V_MaxNum;
				if(((*V_BlockNum)&C_FreezeNextSignFlag)==C_FreezeNextSign)/*有后续帧*/
				{
					if(C_OK==PF_Check_CRC(&GV_FreezeLastNum[0],3))
					{
						if(GV_FreezeLastNum[0]<=V_MaxNum)/*正常不存在*/
						{
							V_Num2=GV_FreezeLastNum[0];/*后续帧*/
						}
					}
				}
				else
				{
					SF_Initial_GVStrNextLoadTime();/*初始化后续帧全局变量*/
				}

				if((*V_BlockNum) == 1)/*读固定时间,时间必须相等*/
				{
					V_Return_Flag = C_NoData;
					for(;V_Num1<=V_MaxNum;V_Num1++)/*从最近查找*/
					{
						V_FindFlashAddr=SF_GetFlashAddrSatisfyNum(0,V_Order,V_Num1);/*获取满足次数要求的记录Flash地址,非周期冻结方案号置0*/
						if(0xFFFFFFFF==V_FindFlashAddr)/*正常不存在*/
						{
							break;
						}
						else
						{
							InF_FlashChipSelect();
							InF_ReadFlash(V_FindFlashAddr,&V_FindTime[0],C_698FreeData_DateLen6);    /*读记录数据日期时间,判断起始时间*/
							V_CompareSign=PF_Campare_Data(&V_FindTime[0],&P_FixTime[0],C_698FreeData_DateLen6);
							if(C_Equal==V_CompareSign)
							{
								V_Return_Flag=SF_OrganData(&P_Data_Id_OAD[1],0,V_Order,&V_TotalLen,V_Length,V_FindFlashAddr,P_Data,V_DataLen,pV_FreezeTimeBuf,V_Mode);	/*组织数据*/
								break;
							}
						}
					}

					if(C_OK==V_Return_Flag)
					{
						(*V_BlockNum) = 1;
						(*V_BlockNum)<<=2;
						*V_Length=V_TotalLen;
					}
					else
					{
						if((V_Return_Flag==C_NotSupportAOD_DataBB)||(V_Return_Flag==C_NotSupportAOD_DataCC))
						{
							V_Return_Flag=C_NoData;
						}
					}

					SF_Initial_GVStrNextLoadTime();/*初始化后续帧全局变量*/
					return V_Return_Flag;
				}
				else/*区间查找,非冻结周期数据是遍历查找*/
				{
					uchar8 V_CompareSign1;
					V_Return_Flag=C_NoData;
					(*V_BlockNum) =0;
					for(;V_Num2>0;V_Num2--)/*从最早查*/
					{
						V_FindFlashAddr=SF_GetFlashAddrSatisfyNum(0,V_Order,V_Num2);/*获取满足次数要求的记录Flash地址*/
						if(0xFFFFFFFF==V_FindFlashAddr)/*没有满足次数要求记录*/
						{
							continue;/*正常从前往后查，肯定能查到满足次数要求数据。*/
						}
						else
						{
							InF_FlashChipSelect();
							InF_ReadFlash(V_FindFlashAddr,&V_FindTime[0],C_698FreeData_DateLen6);    /*读记录数据日期时间,判断起始时间*/
							V_CompareSign=PF_Campare_Data(&V_FindTime[0],&P_FixTime[0],C_698FreeData_DateLen6);
							V_CompareSign1=PF_Campare_Data(&V_FindTime[0],&P_FixTime[C_698FreeData_DateLen6],C_698FreeData_DateLen6);
							if((C_LessThan!=V_CompareSign)&&(C_LessThan==V_CompareSign1))/*有效数据*/
							{
								V_Return_Flag=SF_OrganData(&P_Data_Id_OAD[1],0,V_Order,&V_TotalLen,V_Length,V_FindFlashAddr,&P_Data[V_TotalLen],V_DataLen,pV_FreezeTimeBuf,V_Mode);/*组织数据*/
								if(C_OK!=V_Return_Flag)
								{
									break;
								}
								else
								{
									(*V_BlockNum)++;
								}
							}
						}
					}

					*V_Length=V_TotalLen;
					(*V_BlockNum)<<=2;
					if((C_DataLenError==V_Return_Flag)&&(V_TotalLen!=0))/*后续帧*/
					{
						ushort16 V_CRC16;
						GV_FreezeLastNum[0]=V_Num2;
						V_CRC16=PF_Cal_CRC(&GV_FreezeLastNum[0],1);/*保存上次查找到第几次*/
						PF_Ushort16ToBuffer2(&GV_FreezeLastNum[1],&V_CRC16);
						(*V_BlockNum)|=0x0002;
						V_Return_Flag=C_OK;
					}
					else/*无后续帧*/
					{
						if((V_Return_Flag==C_NotSupportAOD_DataBB)||(V_Return_Flag==C_NotSupportAOD_DataCC))
						{
							V_Return_Flag=C_NoData;
						}
						SF_Initial_GVStrNextLoadTime();
					}

					return V_Return_Flag;
				}
			}break;

			default:  /*时间覆盖冻结数据抄读*/
			{
				PF_CopyDataBytes(&P_FixTime[0],&V_StarTime[0],C_698FreeData_DateLen6);

				/****************************第1个有效数据点查找***************************/
				V_FlashAddr32=V_FlashAddrEar;
				if(V_Mode == C_698EarLoadMode)
				{
					InF_ReadE2_Flash_Data(P_FixTime,C_698FreeData_DateLen6,C_ReadFlashFlay,V_FlashAddrEar);
					return V_Mode;
				}
				else if(V_Mode == C_698AheadTimeMode)
				{
					V_FindFlashAddr=SF_LoadDichotomyFlashData(V_ProNum,V_Order,&V_StarTime[0],V_FlashAddr32,V_FlashAddrLate,C_LoadDichotomyFindBefore);/*根据2分法查找满足时间要求的负荷记录*/
					if(V_FindFlashAddr==0xFFFFFFFF)
					{
						return C_NoData;
					}

					InF_FlashChipSelect();
					InF_ReadFlash(V_FindFlashAddr,&V_StarTime[0],C_698FreeData_DateLen6);    /*读记录数据日期时间,判断起始时间*/

					V_Return_Flag=SF_OrganData(&P_Data_Id_OAD[1],V_ProNum,V_Order,&V_TotalLen,V_Length,V_FindFlashAddr,P_Data+V_AddLen,V_DataLen,pV_FreezeTimeBuf,V_Mode);/*组织数据*/
					if(C_NotSupportAOD_DataCC==V_Return_Flag)/*抄读的所有列选OAD，在关联列表中都没有。主要用于周期冻结抄读，避免循环查找时间过长*/
					{
						return C_NoData;
					}

					memcpy(pV_FreezeTimeBuf,V_StarTime,6);

					return V_Mode;
				}

				V_FindFlashAddr=SF_LoadDichotomyFlashData(V_ProNum,V_Order,&V_StarTime[0],V_FlashAddr32,V_FlashAddrLate,C_LoadDichotomyFindAfter);/*根据2分法查找满足时间要求的负荷记录*/
				if(V_FindFlashAddr==0xFFFFFFFF)
				{
					return C_NoData;
				}

				InF_FlashChipSelect();
				InF_ReadFlash(V_FindFlashAddr,&V_StarTime[0],C_698FreeData_DateLen6);    /*读记录数据日期时间,判断起始时间*/
				V_Return_Flag=SF_OrganData(&P_Data_Id_OAD[1],V_ProNum,V_Order,&V_TotalLen,V_Length,V_FindFlashAddr,P_Data+V_AddLen,V_DataLen,pV_FreezeTimeBuf,V_Mode);/*组织数据*/
				if(V_Mode == C_645Mode)
				{
					memcpy(P_Data,pV_FreezeTimeBuf+2,5);
				}

				if(C_NotSupportAOD_DataCC==V_Return_Flag)/*抄读的所有列选OAD，在关联列表中都没有。主要用于周期冻结抄读，避免循环查找时间过长*/
				{
					return C_NoData;
				}

				if(C_OK!=V_Return_Flag)
				{
					if(V_Return_Flag==C_NotSupportAOD_DataBB)/*如果是BB，无校数据.循环查找第1个有效记录数据。时间是否满足，在下面判断。*/
					{
						ushort16 V_j=0;

						while(1)/*查找第一个有效记录点*/
						{
							if(V_j>120)
							{
								return C_NoData;/*安全性判断正常不存在，1min与其他比较大的存储间隔周期时，会查找时间较长，*/
							}

							V_FindFlashAddr=SF_FindNextFreezeFlashAddr(V_ProNum,V_Order,V_FindFlashAddr,V_FlashAddrLate,V_FlashAddrEar,V_DataLen);/*查找满足条件的下条记录地址*/
							if(V_FindFlashAddr==0xFFFFFFFF)
							{
								return C_NoData;
							}

							InF_FlashChipSelect();
							InF_ReadFlash(V_FindFlashAddr,&V_StarTime[0],C_698FreeData_DateLen6);    /*读记录数据日期时间,判断起始时间*/
							V_Return_Flag=SF_OrganData(&P_Data_Id_OAD[1],V_ProNum,V_Order,&V_TotalLen,V_Length,V_FindFlashAddr,P_Data,V_DataLen,pV_FreezeTimeBuf,V_Mode);/*组织数据*/

							if(C_OK==V_Return_Flag)/*有效数据*/
							{
								break;
							}
							else
							{
								if(V_Return_Flag!=C_NotSupportAOD_DataBB)/*如果是BB，无校数据*/
								{
									return V_Return_Flag;/*异常*/
								}
							}

							V_j++;
						}
					}
					else
					{
						return V_Return_Flag;/*异常*/
					}
				}
				/*****************上面已经查找到有效记录点，时间是否满足，在下面判断****************/
				PF_CopyDataBytes(&V_StarTime[0],&V_FindTime[0],C_698FreeData_DateLen6);
				V_CompareSign=PF_Campare_Data(&V_FindTime[0],&P_FixTime[0],C_698FreeData_DateLen6);/*比较起始时间*/

				if((*V_BlockNum)==1)/*读固定时间,时间必须相等*/
				{
						if(V_Return_Flag==C_NotSupportAOD_DataBB)/*正常不可能出现该情况*/
						{
							return C_NoData;
						}
						else
						{
							(* V_BlockNum) = 1;
							(* V_BlockNum)<<=2;
							*V_Length=V_TotalLen;
							return C_OK;
						}
				}
				else/*按时间区间抄读*/
				{
					V_CompareSign_STEnd=PF_Campare_Data(&V_FindTime[0],&P_FixTime[C_698FreeData_DateLen6],C_698FreeData_DateLen6);/*判断结束时间，秒开始判断*/

					(*V_BlockNum) =0;
					GV_ReadRecordNum=0;
					if((C_LessThan==V_CompareSign)||(C_LessThan!=V_CompareSign_STEnd))/*按区间抄读，第1个点时间，必须满足≥需抄读时间,且小于截止时间（不包含=）。区间抄读*/
					{
						return C_NoData;
					}
					else
					{
						uchar8 V_Read_Flag=0x55,V_Break120=0x55;
						V_Read_Flag=SF_JudgeReadCycSame(V_ProNum,V_Order,V_IntervalTime);/*判断抄读周期与冻结周期是否一致*/
						if((V_IntervalTime==0)||(V_IntervalTime==1)||(V_Read_Flag==0xAA))/*遍历查找*/
						{
							while(1)
							{
								if(V_Return_Flag!=C_NotSupportAOD_DataBB)/*有效数据*/
								{
									(*V_BlockNum)++;
								}

								GV_ReadRecordNum++;
								V_FindFlashAddr=SF_FindNextFreezeFlashAddr(V_ProNum,V_Order,V_FindFlashAddr,V_FlashAddrLate,V_FlashAddrEar,V_DataLen);/*查找满足条件的下条记录地址*/
								if(0xFFFFFFFF==V_FindFlashAddr)
								{
									V_Break120=0xAA;/*非超120次break*/
									break;
								}

								InF_FlashChipSelect();
								InF_ReadFlash(V_FindFlashAddr,&V_FindTime[0],C_698FreeData_DateLen6);    /*读记录数据日期时间*/
								V_CompareSign=PF_Campare_Data(&V_FindTime[0],&P_FixTime[C_698FreeData_DateLen6],C_698FreeData_DateLen6);
								if((C_GreaterThan==V_CompareSign)||(C_Equal==V_CompareSign))/*超过截止时间,无后续帧*/
								{
									V_Break120=0xAA;/*非超120次break*/
									break;
								}

								if((*V_BlockNum)>126)/*防止抄读时间过长，＞1024条(区间抄读时间较短，该部分修改为1024)，则按后续帧处理*/
								{
									V_Break120=0xBB;
									break;
								}

								V_Return_Flag=SF_OrganData(&P_Data_Id_OAD[1],V_ProNum,V_Order,&V_TotalLen,V_Length,V_FindFlashAddr,&P_Data[V_TotalLen+V_AddLen],V_DataLen,pV_FreezeTimeBuf,V_Mode);/*组织数据*/
								if((C_OK!=V_Return_Flag)&&(V_Return_Flag!=C_NotSupportAOD_DataBB))
								{
									break;
								}
							}
						}
						else/*区间时间*/
						{
							V_FlashAddr32=V_FindFlashAddr;/*上1条记录地址*/
							if(V_Return_Flag!=C_NotSupportAOD_DataBB)
							{
								(* V_BlockNum)++;
								GV_ReadRecordNum++;
							}

							uchar8 V_tempTime[C_698FreeData_DateLen6];
							ulong32 V_SubTime=0xFFFFFFFF;
							ulong32 V_IntervalNum;
							uchar8 V_UnderTimeJudge;

							PF_CopyDataBytes(&V_FindTime[0],&V_tempTime[0],C_698FreeData_DateLen6);/*有效起始时间*/

							ulong32 C_FlashStAddr_LoadProfileTemp,C_FlashEndAddr_LoadProfileTemp;
							if((P_Data_Id_OAD[0]&0xFFFF0000)==(C_RelatedOAD_Min&0xFFFF0000))/*分钟冻结*/
							{
								ushort16 V_E2Addr_LoadP_Flash_EarTemp,V_E2Addr_LoadP_Flash_LateTemp;
								SF_GetMinFreezePro_E2andFlashAddr(V_ProNum,&C_FlashStAddr_LoadProfileTemp,&C_FlashEndAddr_LoadProfileTemp,&V_E2Addr_LoadP_Flash_EarTemp,&V_E2Addr_LoadP_Flash_LateTemp);/*根据分钟冻结方案号，获取该方案最近、最早记录E2地址及该方案起始、结束Flash地址*/
							}
							else
							{
								C_FlashStAddr_LoadProfileTemp=Str_698FreezeDataTable[V_Order].V_StaFlashAddr;
								C_FlashEndAddr_LoadProfileTemp=Str_698FreezeDataTable[V_Order].V_EndFlashAddr;
							}

							PF_CopyDataBytes(&V_FindTime[0],&V_ucJudgeCycleBuf[0],C_698FreeData_DateLen6);/*第1个有效起始时间*/

							while(1)/*第1个点上面已取*/
							{
								/*增加间隔周期，进行起始、结束时间判断*/
								PF_CopyDataBytes(&V_FindTime[0],&V_StarTime[0],C_698FreeData_DateLen6);/*从有效的时间点开始*/
								V_Return_Flag=SF_GetFreezeStartTime(P_Data_Id_OAD[0],&V_StarTime[0],V_IntervalTime);/*根据间隔，某类冻结，获取起始时间*/
								if(C_OK!=V_Return_Flag)/*正常不存在，除非是动作触发类冻结，类似结算日、切换冻结*/
								{
									V_Break120=0xAA;/*非超120次break*/
									break;
								}

								V_ucCompareFlag = PF_Campare_Data(&V_StarTime[0],&V_ucJudgeCycleBuf[0],C_698FreeData_DateLen6);
								if(V_ucCompareFlag == C_LessThan) /*防止时间查找错误*/
								{
									V_Break120=0xAA;/*非超120次break*/
									break;
								}

								V_FindFlashAddr=SF_TraversalSearchFlashData(C_FlashStAddr_LoadProfileTemp,C_FlashEndAddr_LoadProfileTemp,V_ProNum,V_Order,&V_StarTime[0],V_FlashAddr32,V_FlashAddrLate,C_LoadDichotomyFindAfter);/*根据遍历查找满足时间要求的负荷记录*/
								if(V_FindFlashAddr==0xFFFFFFFF)
								{
									V_Break120=0xAA;/*非超120次break*/
									break;
								}

								InF_FlashChipSelect();
								InF_ReadFlash(V_FindFlashAddr,&V_FindTime[0],C_698FreeData_DateLen6);    /*读记录数据日期时间*/

								V_CompareSign_STEnd=PF_Campare_Data(&V_FindTime[0],&P_FixTime[C_698FreeData_DateLen6],C_698FreeData_DateLen6);
								if((C_GreaterThan==V_CompareSign_STEnd)||(C_Equal==V_CompareSign_STEnd))/*超过截止时间,无后续帧*/
								{
									V_Break120=0xAA;/*非超120次break*/
									break;
								}

								V_UnderTimeJudge=SF_GetFreezeIntervalTime(P_Data_Id_OAD[0],&V_tempTime[0],&V_FindTime[0],&V_SubTime);/*某类冻结，查找记录时间与有效记录时间，间隔*/
								if(V_SubTime==0xFFFFFFFF)/*正常不存在*/
								{
									V_Break120=0xAA;/*非超120次break*/
									break;
								}

								if((0==(V_SubTime%V_IntervalTime))&&(V_UnderTimeJudge==C_Equal))/*可以整除且下级时间完全相等，则满足周期查找条件*/
								{
									PF_CopyDataBytes(&V_FindTime[0],&V_tempTime[0],C_698FreeData_DateLen6);/*有效起始时间*/
									V_usCountCycle = 0;
									if((* V_BlockNum)>69)/*防止抄读时间过长，＞120条，则按后续帧处理*/
									{
										V_Break120=0xBB;
										break;
									}

									V_Return_Flag=SF_OrganData(&P_Data_Id_OAD[1],V_ProNum,V_Order,&V_TotalLen,V_Length,V_FindFlashAddr,&P_Data[V_TotalLen + V_AddLen],V_DataLen,pV_FreezeTimeBuf,V_Mode);/*组织数据*/
									if((C_OK!=V_Return_Flag)&&(V_Return_Flag!=C_NotSupportAOD_DataBB))/*同上判断*/
									{
										break;
									}
									else if(V_Return_Flag!=C_NotSupportAOD_DataBB)/*有效数据*/
									{
										(*V_BlockNum)++;
										GV_ReadRecordNum++;
									}
								}
								else/*更改起始时间，查找记录时间的，最近上一个周期记录时间点*/
								{
									V_IntervalNum=V_SubTime/V_IntervalTime;
									V_IntervalNum=V_IntervalNum*V_IntervalTime;/*整周期个数*/
									PF_CopyDataBytes(&V_FindTime[0],&V_ucJudgeCycleBuf[0],C_698FreeData_DateLen6);
									PF_CopyDataBytes(&V_tempTime[0],&V_FindTime[0],C_698FreeData_DateLen6);/*有效起始时间*/
									SF_GetFreezeStartTime(P_Data_Id_OAD[0],&V_FindTime[0],V_IntervalNum);/*根据间隔，某类冻结，获取起始时间。从下一个周期点起始，开始查找*/
									V_usCountCycle++;
								}

								V_FlashAddr32=V_FindFlashAddr;/*上1条记录地址*/

								if(V_usCountCycle > C_CycleTimes) /*方法2查询1500条仍然没有有效点*/
								{
									V_Break120=0xAA;/*非超120次break*/
									break;
								}
							}
						}

						*V_Length=V_TotalLen;
						(*V_BlockNum)<<=2;/*记录次数*/
						if(V_TotalLen!=0)/*有数据*/
						{
							if((C_DataLenError==V_Return_Flag)||(V_Break120==0xBB))/*后续帧*/
							{
								PF_CopyDataBytes(&V_FindTime[0],&P_FixTime[0],C_698FreeData_DateLen6);
								(* V_BlockNum)|=0x0002;
							}
							V_Return_Flag=C_OK;
						}
						else
						{
							if(C_NotSupportAOD_DataBB==V_Return_Flag)
							{
								V_Return_Flag=C_NoData;
							}
						}
						return V_Return_Flag;
					}
				}
			}
		}
	}
	else    /*按次数抄读数据*/
	{
		ushort16 V_j=0;
		ushort16 V_k,V_tempLen,V_i=0;
		V_k = V_Num;
		switch((*P_Data_Id_OAD&0xFFFF0000))/*区分分钟冻结，可能会有不同方案*/
		{
			case (C_RelatedOAD_Min&0x00000000):   /*运行不到，目前分钟冻结分多钟方案，不用区分分钟冻结*/
			{
				break;
			}
			default:/*其他冻结目前不存在，不同冻结方案问题*/
			{
				if(V_k==0)/*正常不存在*/
				{
					return C_NoData;
				}
				else
				{
					V_i=V_k-1;/*只有同1冻结方案才可以，即只要冻结，则是有效数据。*/
				}
				break;
			}
		}

		V_tempLen=* V_Length;
		while(1) /*主要是分钟冻结,其他冻结所有OAD周期相同，当前查找次数即使有效数据*/
		{
			V_j++;
			V_FindFlashAddr=SF_GetFlashAddrSatisfyNum(V_ProNum,V_Order,V_Num);/*获取满足次数要求的记录Flash地址*/
			if((0xFFFFFFFF==V_FindFlashAddr)||(V_j>121))/*V_j>121,最多查找120次*/
			{
				return C_NoData;
			}

			V_TotalLen=0;
			*V_Length=V_tempLen;/*次数抄读每次有效条数1条*/
			V_Return_Flag=SF_OrganData(&P_Data_Id_OAD[1],V_ProNum,V_Order,&V_TotalLen,V_Length,V_FindFlashAddr,P_Data,V_DataLen,pV_FreezeTimeBuf,V_Mode);/*组织记录数据*/
			if(C_NotSupportAOD_DataCC==V_Return_Flag)/*抄读的所有列选OAD，在关联列表中都没有。主要用于周期冻结抄读，避免循环查找时间过长*/
			{
				return C_NoData;
			}

			if(V_Return_Flag!=C_NotSupportAOD_DataBB)
			{
				V_i++;	/*有效数据记录次数*/
				if(V_k==V_i)
				{
					break;
				}
			}

			V_Num++;
		}

		(*V_BlockNum) = 1;
		(*V_BlockNum)<<=2;
		*V_Length=V_TotalLen;

		return V_Return_Flag;
	}
}
/*********************************************************************************
函数原型：uchar8 SF_GetCurrentFlashPageModeNum(ulong32 V_FlashAddr)
功能描述：获取当前Flash记录页中有效的负荷记录条数
输入参数：ulong32 V_FlashAddr：需要查找的Flash记录页地址；
输出参数：无
返回参数：uchar8实际记录有效条数或FF异常，正常不为FF
功能说明：
调用机制：
备     注：
*********************************************************************************/
uchar8 SF_GetCurrentFlashPageModeNum(ulong32 V_FlashAddr)
{
	uchar8 V_i=0xFF;
	uchar8 V_Mode1[C_LoadProfile_RevMode];

	if(V_FlashAddr%C_OneFlashPage)/*非页地址*/
	{
		return V_i;
	}

	InF_FlashChipSelect();
	InF_ReadFlash(V_FlashAddr,&V_Mode1[0],C_LoadProfile_RevMode);

	for(V_i=0;V_i<C_LoadProfile_RevMode;V_i++)
	{
		if((C_Flash_NoEmpty==V_Mode1[V_i])||(C_Flash_Empty==V_Mode1[V_i]))  /*底层为全0，说明负荷记录时间调整过,该V_I无效 或底层没有记录*/
		{
			break;
		}
	}

	if(0x00==V_i)/*正常不存在*/
	{
		V_i=0xFF;
	}

	return V_i;
}
/*********************************************************************************
函数原型：uchar8 SF_GetSatisfyFlashPageAndModeOffSet698(ulong32 V_FlashSTAddr,ulong32 V_FlashEndAddr,ulong32 *V_FindFlashPageAddr,
														ushort16 V_BlockNum,ushort16 *V_BlockTolNum)
功能描述*获取满足记录条数要求的负荷记录Flash页地址及模式字偏移。注意函数从后，往前查找
输入参数：ulong32 V_FlashSTAddr：需要查找的Flash记录起始页地址；
		ulong32 V_FlashEndAddr：需要查找的Flash记录结束页地址；
		ushort16 V_BlockNum：需要读上第几次记录
		ushort16 *V_BlockTolNum：目前已经查找的记录总条数
输出参数：ulong32 *V_FindFlashPageAddr：满足条件的负荷记录页地址；
		ushort16 *V_BlockTolNum：目前已经查找的记录总条数
返回参数：uchar8 满足条件的模式字偏移或FF没有请求数据
功能说明：
调用机制：
备     注：
*********************************************************************************/
uchar8 SF_GetSatisfyFlashPageAndModeOffSet698(ulong32 V_FlashSTAddr,ulong32 V_FlashEndAddr,ulong32 *V_FindFlashPageAddr,ushort16 V_BlockNum,ushort16 *V_BlockTolNum)
{
	ushort16 V_ModeTNum;
	uchar8 V_ModeNum;
	ulong32 V_FlashAddr;

	V_FlashSTAddr&=0xFFFFF000;             /*页地址转化，增加容错性*/
	V_FlashEndAddr&=0xFFFFF000;
	V_FlashAddr=V_FlashEndAddr;
	if(V_FlashSTAddr>V_FlashEndAddr)
	{
		V_FlashAddr=V_FlashSTAddr;
		V_FlashSTAddr=V_FlashEndAddr;
		V_FlashEndAddr=V_FlashAddr;
	}

	V_ModeTNum=*V_BlockTolNum;
	for(V_FlashAddr=V_FlashEndAddr;V_FlashAddr>=V_FlashSTAddr;)/*从后往前查*/
	{
		V_ModeNum=SF_GetCurrentFlashPageModeNum(V_FlashAddr);
		if(0xFF==V_ModeNum)
		{
			return 0xFF;
		}

		V_ModeTNum+=V_ModeNum;
		if(V_ModeTNum>=V_BlockNum)
		{
			break;
		}
		else
		{
			V_FlashAddr-=C_OneFlashPage;
		}
	}

	*V_BlockTolNum=V_ModeTNum;/*目前已查询记录总条数*/
	if(V_FlashAddr<V_FlashSTAddr)/*没有满足次数要求*/
	{
		return 0xFF;
	}
	else
	{
		V_ModeNum=V_ModeTNum-V_BlockNum;/*满足条件当前记录条数模式字偏移*/
		*V_FindFlashPageAddr=V_FlashAddr;/*满足记录条数的Flash页地址*/
	}

	if(V_ModeNum>=C_LoadProfile_RevMode)/*正常不存在*/
	{
		return 0xFF;
	}
	else
	{
		return V_ModeNum;
	}
}

/*********************************************************************************
函数原型：uchar8 InF_ReadLaterFreezeNum(ulong32 V_Data_Id,uchar8 *P_Data,uchar8 *V_Length)
功能描述：读某类冻结记录，最近一次记录序号，冻结模块调用
输入参数：ulong32 V_Data_Id：数据标识，即某类冻结OAD；DI2高3位表示分钟冻结方案号
		uchar8 *V_Length：读数据缓存区最大长度；
输出参数：uchar8 *V_Length：所读数据实际长度；
		uchar8 *P_Data：读数据存放缓存，没有记录时返回数据0；
返回参数：C_OK、C_IICError、C_SPIError、C_DataLenError、C_IDError、C_NoData
功能说明：
调用机制：
备     注：
*********************************************************************************/
uchar8 InF_ReadLaterFreezeNum(ulong32 V_Data_Id1,uchar8 *P_Data,uchar8 *V_Length)
{
	uchar8 V_DI[4],V_Return_Flag;
	uchar8 V_FlashAddr8[4];
	ulong32 V_FlashAddrLate,V_FlashAddrEar,C_FlashStAddr_LoadProfile,V_FindFlashAddr;
	uchar8 V_i,V_Order,V_ProNum;
	ushort16 V_E2Addr_LoadP_Flash_Late,V_E2Addr_LoadP_Flash_Ear;
	ulong32 V_Data_Id,C_FlashEndAddr_LoadProfile;

	V_ProNum=(uchar8)((V_Data_Id1&0x00E00000)>>21);/*获取分钟冻结方案号*/
	V_Data_Id=(V_Data_Id1&0xFF1FFFFF);/*去除分钟方案冻结号*/
	PF_Ulong32ToBuffer4(&V_DI[0],&V_Data_Id,4);
	if((C_RelatedOAD_Immid&0xFF000000)!=(V_Data_Id&0xFF000000))/*非冻结记录*/
	{
		return C_IDError;
	}

	if(*V_Length<4)
	{
		return C_DataLenError;
	}

	V_Order=SF_GetStr_698FreezeDataTableOrder(V_Data_Id);/*获取某类冻结数据在Str_698FreezeDataTable中序号*/
	if(0xFF==V_Order)
	{
		return C_IDError;
	}

	V_E2Addr_LoadP_Flash_Late=Str_698FreezeDataTable[V_Order].V_E2AddrLate;
	V_E2Addr_LoadP_Flash_Ear=Str_698FreezeDataTable[V_Order].V_E2AddrEar;
	C_FlashStAddr_LoadProfile=Str_698FreezeDataTable[V_Order].V_StaFlashAddr;

	if(V_Data_Id==C_RelatedOAD_Min)/*分钟冻结*/
	{
		V_Return_Flag=SF_GetMinFreezePro_E2andFlashAddr(V_ProNum,&C_FlashStAddr_LoadProfile,&C_FlashEndAddr_LoadProfile,&V_E2Addr_LoadP_Flash_Ear,&V_E2Addr_LoadP_Flash_Late);/*根据分钟冻结方案号，获取该方案最近、最早记录E2地址及该方案起始、结束Flash地址*/
		if(C_OK!=V_Return_Flag)
		{
			return C_Error;
		}
	}

	V_Return_Flag=SF_ReadE2Three(V_E2Addr_LoadP_Flash_Late,4,&V_FlashAddr8[0]);        /*取最近1条记录Flash页地址*/
	PF_Buffer4ToUlong32(&V_FlashAddr8[0],&V_FlashAddrLate,4);
	V_FlashAddrLate&=0xFFFFF000;             /*页地址转化，增加容错性*/

	if(C_OK!=V_Return_Flag)
	{
		return V_Return_Flag;
	}

	V_Return_Flag=SF_ReadE2Three(V_E2Addr_LoadP_Flash_Ear,4,&V_FlashAddr8[0]);         /*取最早1条记录Flash地址*/
	PF_Buffer4ToUlong32(&V_FlashAddr8[0],&V_FlashAddrEar,4);

	if(C_OK!=V_Return_Flag)
	{
		return V_Return_Flag;
	}

	if((V_FlashAddrLate==V_FlashAddrEar)&&(V_FlashAddrLate==C_FlashStAddr_LoadProfile))  /*没有记录数据，返回次数为0*/
	{
		for(V_i=0;V_i<4;V_i++)
		{
			P_Data[V_i]=0;
		}
		*V_Length=4;
		return C_OK;
	}

	V_FindFlashAddr=SF_GetFixedLoadModeNoteFlashAddr(V_ProNum,V_Order,V_FlashAddrLate);
	if(0xFFFFFFFF!=V_FindFlashAddr)
	{
		InF_FlashChipSelect();
		InF_ReadFlash((V_FindFlashAddr+C_698FreeData_DateLen6),&P_Data[0],4);
		PF_Buffer4ToUlong32(&P_Data[0], &C_FlashEndAddr_LoadProfile, 4);		/*从flash读取的记录序号*/
		C_FlashEndAddr_LoadProfile += 1;
		PF_Ulong32ToBuffer4(&P_Data[0], &C_FlashEndAddr_LoadProfile, 4);		/*记录序号加1*/
		*V_Length=4;
	}

	return C_OK;
}

/*********************************************************************************
函数原型：uchar8 InF_Total_Clear(uchar8 Msg_Num,uchar8 V_CurrentState,uchar8 C_Safe_Flag)
功能描述：电表总清,通信调用
输入参数：uchar8 Msg_Num：调用消息号；
		uchar8 V_CurrentState：电能表当前状态，厂内、厂外；
		取值：C_FactoryInType0x01，厂内；C_FactoryOutType0x02，厂外
		uchar8 C_Safe_Flag：C_ClearMeterSafeFlag0x86总清安全标志；
输出参数：无
返回参数：C_OK、C_IICError、C_SPIError、C_NoAccess、C_SafeFlagError
功能说明：
调用机制：
备     注：清零，不清校表数据。只有InF_RecMeterNote_Clear清校表数据，通信校表清零调用。
*********************************************************************************/
uchar8 InF_Total_Clear(uchar8 Msg_Num,uchar8 V_CurrentState,uchar8 C_Safe_Flag )
{
	uchar8 V_Return_Flag,V_i;

	GV_D_ClearSafeFlag=C_Clear_SafeFlag;
	GV_D_ClearSafeFlag=GV_D_ClearSafeFlag|C_DataClearMeterSafeFlag_1;
	GV_D_SafeFlag=GV_D_SafeFlag|C_ClearMeterSafeFlag_1;

	if(C_Msg_Communication!=Msg_Num)
	{
		return C_NoAccess;
	}

	GV_D_ClearSafeFlag=GV_D_ClearSafeFlag|C_DataClearMeterSafeFlag_2;
	GV_D_SafeFlag=GV_D_SafeFlag|C_ClearMeterSafeFlag_2;

	if(C_ClearMeterSafeFlag!=C_Safe_Flag)
	{
		GV_D_ClearSafeFlag=C_Clear_SafeFlag;
		return C_SafeFlagError;
	}

	GV_D_ClearSafeFlag=GV_D_ClearSafeFlag|C_DataClearMeterSafeFlag_3;
	GV_D_SafeFlag=GV_D_SafeFlag|C_ClearMeterSafeFlag_3;

	if(C_DataClearMeterSafeFlag==GV_D_ClearSafeFlag)  /*各清零内部分别判断安全标志*/
	{

		V_Return_Flag=SF_Clear_Engry(GV_D_SafeFlag);  /*清零，不成功，不进行下步操作*/
		if(C_OK!=V_Return_Flag)
		{
			GV_D_ClearSafeFlag=C_Clear_SafeFlag;
			return V_Return_Flag;
		}

		V_Return_Flag = SF_Clear_Parm(GV_D_SafeFlag);                           /*清零，不成功，不进行下步操作*/
        if(C_OK != V_Return_Flag)
		{
			GV_D_ClearSafeFlag = C_Clear_SafeFlag;
			return V_Return_Flag;
		}
		V_Return_Flag = SF_Clear_Custom(GV_D_SafeFlag);                         /*清零，不成功，不进行下步操作*/
		if(C_OK != V_Return_Flag)
		{
			GV_D_ClearSafeFlag = C_Clear_SafeFlag;
			return V_Return_Flag;
			}

		V_Return_Flag=InF_Demand_Clear(C_Msg_Communication,C_W_SafeFlag);/*借用通信调用需量清零接口函数*/
		if(C_OK!=V_Return_Flag)
		{
			GV_D_ClearSafeFlag=C_Clear_SafeFlag;
			return V_Return_Flag;
		}

		V_Return_Flag=SF_Clear_Freeze(GV_D_SafeFlag,0xFF);
		if(C_OK!=V_Return_Flag)
		{
			GV_D_ClearSafeFlag=C_Clear_SafeFlag;
			return V_Return_Flag;
		}

		V_Return_Flag=SF_Clear_Event(GV_D_SafeFlag);
		if(C_OK!=V_Return_Flag)
		{
			GV_D_ClearSafeFlag=C_Clear_SafeFlag;
			return V_Return_Flag;
		}

		V_Return_Flag=SF_Clear_Other(GV_D_SafeFlag);
		if(C_OK!=V_Return_Flag)
		{
			GV_D_ClearSafeFlag=C_Clear_SafeFlag;
			return V_Return_Flag;
		}

		if(C_FactoryInType==V_CurrentState)
		{
			uchar8 V_Buff[CLTol_Clear_Degree];

			memset(&V_Buff[0],0x00,CLTol_Clear_Degree);		/*初始化为全零*/
			V_Return_Flag=SF_WriteE2Three(E2Addr_Tol_Clear_Degree,CLTol_Clear_Degree,&V_Buff[0]);	/*清电表清零总次数*/

			memset(&V_Buff[0],0x00,CLBatt_Work_Time);	/*初始化为全零*/
			V_Return_Flag=SF_WriteE2Three(E2Addr_Batt_Work_Time,CLBatt_Work_Time,&V_Buff[0]); /*清内部电池工作时间，根据20141104会议纪要，厂内清厂外不清*/
		}

		/*清负荷记录次数*/
		ushort16	V_usDataCRC;

		for(V_i=0;V_i<CLLoadWriteNum;V_i++)
		{
			GV_LoadWriteNum[V_i]=0;
		}

		V_usDataCRC = PF_Cal_CRC(GV_LoadWriteNum,CLLoadWriteNum);
		PF_Ushort16ToBuffer2(&GV_LoadWriteNum[CLLoadWriteNum],&V_usDataCRC);

		GV_D_SafeFlag=C_Clear_SafeFlag;

		GV_D_ClearSafeFlag=C_Clear_SafeFlag;

		return V_Return_Flag;
	}
	else
	{
		GV_D_SafeFlag=C_Clear_SafeFlag;
		GV_D_ClearSafeFlag=C_Clear_SafeFlag;
		return C_SafeFlagError;
	}
}

/*******************************************************************************
函数原型：void InF_Clear_Engry_BorrowPoint( )
功能描述：清电能借位位数
输入参数：无
输出参数：无
返回参数：无
调用位置：电能清零后
备    注：清RAM、E2中数据
*******************************************************************************/
void InF_Clear_Engry_BorrowPoint( )
{
	ushort16 V_usCRC16;

	GV_DisplayBorrowPoint[0] = 0;

	V_usCRC16 = PF_Cal_CRC(&GV_DisplayBorrowPoint[0], CLDisplayBorrowPoint);
	PF_Ushort16ToBuffer2(&GV_DisplayBorrowPoint[CLDisplayBorrowPoint], &V_usCRC16);

	GV_DisplayBorrowPoint_RecFlag[0] = 0;

	V_usCRC16 = PF_Cal_CRC(&GV_DisplayBorrowPoint_RecFlag[0], CLDisplayBorrowPoint_RecFlag);
	PF_Ushort16ToBuffer2(&GV_DisplayBorrowPoint_RecFlag[CLDisplayBorrowPoint_RecFlag], &V_usCRC16);
}
/*******************************************************************************
函数原型：uchar8 SF_Clear_Engry(uchar8 V_D_SafeFlag)
功能描述：清电能类数据，内部判断安全标志
输入参数：uchar8 V_D_SafeFlag:清零安全标志，C_ClearMeterSafeFlag，0x86
输出参数：无
返回参数：C_OK、C_IICError、C_SafeFlagError
调用位置：该函数由InF_RelayAct接口函数调用
备    注：清铁电、E2中电能数据
*******************************************************************************/
uchar8 SF_Clear_Engry(uchar8 V_D_SafeFlag)
{
	uchar8   V_Return_Flag = C_OtherErr_DAR;
	ushort16 V_CRC16, V_j, V_E2Addr;
	uchar8   V_Buff[10];
	uchar8   *P_RamAddr = NULL;
	uchar8   V_DataLen;

	if(C_ClearMeterSafeFlag != V_D_SafeFlag)
	{
		return C_NoAccess;
	}

	memset(&V_Buff[0], 0x00, 10);       /*初始化为全零*/

	/*清铁电三处数据，包括当前电量类，铁电地址放一起*/
	for(V_j = 0; V_j < Str_2Table_DIEn_Len; V_j++)
	{

		if((Str_2Table_DIEn[V_j].V_DT_Type) & NeedClearDataSign)    /*需清零数据*/
		{
			memset(&V_Buff[0], 0x00, 10);               /*初始化为全零*/

			if(Str_2Table_DIEn[V_j].V_DataLen > 8)
			{
				return C_Error;     /*正常不存在*/
			}

			V_DataLen = (uchar8)(Str_2Table_DIEn[V_j].V_DataLen);

			switch(Str_2Table_DIEn[V_j].V_DT_Type)
			{
				case	DT_Ti_E23_RAMCRC:
				{
					if(Str_2Table_DIEn[V_j].V_LineNum > Str_3aTable_E23RAM_Len)
					{
						return C_Error;     /*正常不存在*/
					}

					if(V_DataLen <= 8)
					{
						V_E2Addr = Str_3aTable_E23RAM[Str_2Table_DIEn[V_j].V_LineNum].V_E2BakeUp1Addr;
						P_RamAddr = Str_3aTable_E23RAM[Str_2Table_DIEn[V_j].V_LineNum].V_RamAddr;
						V_Return_Flag = SF_WriteFRAMThree(V_E2Addr, V_DataLen, &V_Buff[0]);
						if(C_OK == V_Return_Flag)
						{
							V_CRC16 = PF_Cal_CRC(&V_Buff[0], V_DataLen);
							PF_Ushort16ToBuffer2(&V_Buff[V_DataLen], &V_CRC16);
							PF_CopyDataBytes(&V_Buff[0], P_RamAddr, (V_DataLen + C_CRCLen2));
						}
					}
					else
					{
						return C_Error;     /*正常不存在*/
					}
				}break;
#if 0
				case	DT_E23_En_Clear:
#endif
				case	DT_E23_Clear:
				{
					V_E2Addr = (ushort16)Str_2Table_DIEn[V_j].PStr_3TableAddr;
#if 0
					if( Str_2Table_DIEn[V_j].V_DT_Type == DT_E23_En_Clear )     /*表格数据长度与数据存储实际长度不同,存储数据长度多1字节*/
					{
						V_DataLen += 1;
					}
#endif
					V_Return_Flag = SF_WriteE2Three(V_E2Addr, V_DataLen, &V_Buff[0]);
				}break;

				default:
				{
					break;
				}
			}
		}
	}

	/*清E2 1处数据,年结算日结算时间及年结算周期组合有功总累计用电量*/
	if(C_OK == V_Return_Flag)    /*E2清零不成功，不进行下步操作*/
	{
		uchar8 V_Buff1[CLY_Com_Ac_En_FF];

		memset(&V_Buff1[0], 0x00, CLY_Com_Ac_En_FF);  /*初始化为全零*/

		InF_E2WPEnable();
		if(C_W_SafeFlag != GV_D_SafeFlag)             /*安全标志错*/
		{
			InF_E2WPDisable();        /*关闭WP*/
			GV_D_SafeFlag = C_Clear_SafeFlag;
			return C_SafeFlagError;
		}

		V_Return_Flag = InF_WriteE2(E2Addr_Y_Com_Ac_Tol_En_St, &V_Buff1[0], CLY_Com_Ac_En_FF);

		InF_Clear_Engry_BorrowPoint( );
	}

	/*后增累计购电金额*/
	if(C_OK == V_Return_Flag)
	{
		uchar8 V_temp[CLBuyCurr_TMoney];              /*后增累计购电金额*/
		memset(&V_temp[0], 0x00, CLBuyCurr_TMoney);   /*初始化为全零*/
		V_Return_Flag = SF_WriteE2Three(E2Addr_BuyCurr_TMoney, CLBuyCurr_TMoney, &V_temp[0]);
	}

	return V_Return_Flag;
}


/*******************************************************************************
函数原型：uchar8 SF_Clear_Parm(uchar8 V_D_SafeFlag)
功能描述：清参变量类数据，内部判断安全标志
输入参数：uchar8 V_D_SafeFlag：清零安全标志，C_ClearMeterSafeFlag，0x68
输出参数：RAM地址：GV_CurrEnergyData[45/46/43/44]和FRAM地址：651/658/637/644
返回参数：C_NoAccess、C_Error、C_OK、C_IICError
调用位置：该函数目前仅由InF_Total_Clear接口函数调用
备    注：该函数根据SF_Clear_Engry函数修改，wjq211108
*******************************************************************************/
uchar8 SF_Clear_Parm(uchar8 V_D_SafeFlag)
{
    uchar8 V_ucBuff[10], V_ucj, V_ucDataLen, V_ucReturn_Flag = C_OtherErr_DAR;
    uchar8 *p_ucRamAddr = NULL;
    ushort16 V_usE2Addr, V_usCRC16;

    if(C_ClearMeterSafeFlag != V_D_SafeFlag)                                    /*判断安全标志*/
    {
        return C_NoAccess;
    }

    memset(&V_ucBuff[0], 0x00, 10);                                             /*初始化为全零*/

    for(V_ucj = 0; V_ucj < Str_2Table_DIEvent20_Len; V_ucj++)                   /*循环遍历参变量类表格对象，目前实际只遍历4次*/
    {
        if((Str_2Table_DIEvent20[V_ucj].V_DT_Type) & NeedClearDataSign)         /*对象需清零*/
        {
            memset(&V_ucBuff[0], 0x00, 10);
            if(Str_2Table_DIEvent20[V_ucj].V_DataLen > 8)                       /*缓存数组大小限制*/
            {
                return C_Error;                                                 /*正常不存在*/
            }

            V_ucDataLen = (uchar8)(Str_2Table_DIEvent20[V_ucj].V_DataLen);      /*取对象长度*/

			switch(Str_2Table_DIEvent20[V_ucj].V_DT_Type)
			{
                case DT_Ti_E23_RAMCRC:
                {
                    if(Str_2Table_DIEvent20[V_ucj].V_LineNum > Str_3aTable_E23RAM_Len)
					{
						return C_Error;                                         /*正常不存在*/
					}

					if(V_ucDataLen <= 8)
					{
						V_usE2Addr = Str_3aTable_E23RAM[Str_2Table_DIEvent20[V_ucj].V_LineNum].V_E2BakeUp1Addr;
						p_ucRamAddr = Str_3aTable_E23RAM[Str_2Table_DIEvent20[V_ucj].V_LineNum].V_RamAddr;
						V_ucReturn_Flag = SF_WriteFRAMThree(V_usE2Addr, V_ucDataLen, &V_ucBuff[0]);
                        /*注意：当前未处理表格中间某个对象写E2失败的情况211108*/
						if(C_OK == V_ucReturn_Flag)
						{
							V_usCRC16 = PF_Cal_CRC(&V_ucBuff[0], V_ucDataLen);
							PF_Ushort16ToBuffer2(&V_ucBuff[V_ucDataLen], &V_usCRC16);
							PF_CopyDataBytes(&V_ucBuff[0], p_ucRamAddr, (V_ucDataLen + C_CRCLen2));
						}
					}
					else
					{
                        return C_Error;                                         /*正常不存在*/
					}
				} break;

                /*注意：下面的分支暂未使用，后续根据需求需再次调试确认211108*/
#if 0
				case DT_E23_En_Clear:
#endif
				case DT_E23_Clear:
				{
					V_usE2Addr = (ushort16)Str_2Table_DIEvent20[V_ucj].PStr_3TableAddr;
#if 0
					if(Str_2Table_DIEvent20[V_ucj].V_DT_Type == DT_E23_En_Clear)/*表格数据长度与数据存储实际长度不同,存储数据长度多1字节*/
					{
						V_ucDataLen += 1;
					}
#endif
					V_ucReturn_Flag = SF_WriteE2Three(V_usE2Addr, V_ucDataLen, &V_ucBuff[0]);
				} break;

				default:
				{
					break;
				}
			}
        }

        if(Str_2Table_DIEvent20[V_ucj].V_DI == CY_Com_Ac_Tol_En_0)
        {
            break;                                                              /*提高函数执行效率*/
        }
    }

    return V_ucReturn_Flag;
}
/*******************************************************************************
函数原型：uchar8 SF_Clear_Custom(uchar8 V_D_SafeFlag)
功能描述：清自扩类数据，内部判断安全标志
输入参数：uchar8 V_D_SafeFlag：清零安全标志，C_ClearMeterSafeFlag，0x68
输出参数：E2地址：651/658/637/644
返回参数：C_NoAccess、C_Error、C_OK、C_IICError
调用位置：该函数目前仅由InF_Total_Clear接口函数调用
备    注：该函数根据SF_Clear_Engry函数修改，wjq211108
*******************************************************************************/
uchar8 SF_Clear_Custom(uchar8 V_D_SafeFlag)
{
    uchar8 V_ucBuff[10], V_ucj, V_ucDataLen, V_ucReturn_Flag = C_OtherErr_DAR;
    uchar8 *p_ucRamAddr = NULL;
    ushort16 V_usE2Addr, V_usCRC16;

    if(C_ClearMeterSafeFlag != V_D_SafeFlag)
    {
        return C_NoAccess;
    }

    memset(&V_ucBuff[0], 0x00, 10);                                             /*初始化为全零*/

    for(V_ucj = 0; V_ucj < Str_2Table_DIParameterFF_Len; V_ucj++)               /*循环遍历自扩类表格对象，目前实际只遍历4次*/
    {
        if((Str_2Table_DIParameterFF[V_ucj].V_DT_Type) & NeedClearDataSign)     /*对象需清零*/
        {
            memset(&V_ucBuff[0], 0x00, 10);
            if(Str_2Table_DIParameterFF[V_ucj].V_DataLen > 8)                   /*缓存数组大小限制*/
            {
                return C_Error;                                                 /*正常不存在*/
            }

            V_ucDataLen = (uchar8)(Str_2Table_DIParameterFF[V_ucj].V_DataLen);

			switch(Str_2Table_DIParameterFF[V_ucj].V_DT_Type)
			{
                /*注意：下面的分支暂未使用，后续根据需求需再次调试确认211108*/
                case DT_Ti_E23_RAMCRC:
                {
                    if(Str_2Table_DIParameterFF[V_ucj].V_LineNum > Str_3aTable_E23RAM_Len)
					{
						return C_Error;                                         /*正常不存在*/
					}

					if(V_ucDataLen <= 8)
					{
						V_usE2Addr = Str_3aTable_E23RAM[Str_2Table_DIParameterFF[V_ucj].V_LineNum].V_E2BakeUp1Addr;
						p_ucRamAddr = Str_3aTable_E23RAM[Str_2Table_DIParameterFF[V_ucj].V_LineNum].V_RamAddr;
						V_ucReturn_Flag = SF_WriteFRAMThree(V_usE2Addr, V_ucDataLen, &V_ucBuff[0]);
						if(C_OK == V_ucReturn_Flag)
						{
							V_usCRC16 = PF_Cal_CRC(&V_ucBuff[0], V_ucDataLen);
							PF_Ushort16ToBuffer2(&V_ucBuff[V_ucDataLen], &V_usCRC16);
							PF_CopyDataBytes(&V_ucBuff[0], p_ucRamAddr, (V_ucDataLen + C_CRCLen2));
						}
					}
					else
					{
                        return C_Error;                                         /*正常不存在*/
					}
				} break;
                /*注意：下面第一个条件暂未使用，后续根据需求需再次调试确认211108*/
#if 0
                case DT_E23_En_Clear:
#endif
				case DT_E23_Clear:
				{
					V_usE2Addr = (ushort16)Str_2Table_DIParameterFF[V_ucj].PStr_3TableAddr;
#if 0
					if(Str_2Table_DIParameterFF[V_ucj].V_DT_Type == DT_E23_En_Clear)/*表格数据长度与数据存储实际长度不同,存储数据长度多1字节*/
					{
						V_ucDataLen += 1;
					}
#endif
					/*注意：当前未处理表格中间某个对象写E2失败的情况211108*/
					V_ucReturn_Flag = SF_WriteE2Three(V_usE2Addr, V_ucDataLen, &V_ucBuff[0]);
				} break;

				default:
				{
					break;
				}
			}
        }

        if(Str_2Table_DIParameterFF[V_ucj].V_DI == CM_Rev_Ac_Tol_En_Pul_1)
        {
            break;                                                              /*提高函数执行效率*/
        }
    }

    return V_ucReturn_Flag;
}

/*********************************************************************************
函数原型：uchar8 SF_Clear_Event(uchar8 V_D_SafeFlag)
功能描述：总清事件类数据，内部判断安全标志
输入参数：uchar8 V_D_SafeFlag:清零安全标志，C_ClearMeterSafeFlag，0x86
输出参数：无
返回参数：C_OK、C_IICError、C_SafeFlagError
功能说明：
调用机制：
备     注：
*********************************************************************************/
uchar8 SF_Clear_Event(uchar8 V_D_SafeFlag)
{
	uchar8 V_Return_Flag;
	uchar8 V_Buff[CLEven_Clear_Degree];

	if(C_ClearMeterSafeFlag!=V_D_SafeFlag)
	{
		return C_SafeFlagError;
	}

	V_Return_Flag=InF_EventNote_Clear(C_Msg_Communication,0xFFFFFFFF,C_W_SafeFlag);	/*事件总清零，借用提供通信事件清零接口函数*/
	if(C_OK!=V_Return_Flag)
	{
		return V_Return_Flag;
	}

	memset(&V_Buff[0],0x00,CLEven_Clear_Degree);	/*初始化为全零*/
	V_Return_Flag=SF_WriteE2Three(E2Addr_Even_Clear_Degree,CLEven_Clear_Degree,&V_Buff[0]);	/*清事件清零记录*/

	return V_Return_Flag;
}
/*********************************************************************************
函数原型：uchar8 SF_Clear_MinFreeze(uchar8 V_D_SafeFlag)
功能描述：清分钟冻结类数据，内部判断安全标志
输入参数：uchar8 V_D_SafeFlag:清零安全标志，C_ClearMeterSafeFlag，0x86
输出参数：无
返回参数：C_OK、C_IICError、C_SafeFlagError
功能说明：
调用机制：
备     注：698冻结数据清零，E2存储最近、最早Flash地址，都调整为Flash记录首页地址,
		有记录时，V_E2AddrEar最早1条记录首地址(绝对地址，前面为标志字)；V_E2AddrLate为最近1条记录页地址
		假如分配Flash起始、结束地址读失败（没有设置关联列表，则没有分配地址），则采用默认平均分配。
*********************************************************************************/
uchar8 SF_Clear_MinFreeze(uchar8 V_D_SafeFlag)
{
	uchar8 V_ProNum,V_Return_Flag,V_i;
	uchar8 Vu_FlashAddr[64]={0xFF};

	if(C_ClearMeterSafeFlag!=V_D_SafeFlag)
	{
		return C_SafeFlagError;
	}

	V_ProNum=InF_GetMinFreezeTolNum();	/*获取分钟冻结总方案数,1--8*/
	if(V_ProNum>8)	/*没有设置过关联列表，总清该部分异常*/
	{
		V_ProNum=8;	/*默认为8种方案，下面会用到*/
		V_Return_Flag=SF_MinFreezeDefProDistr(8);
		if(C_OK!=V_Return_Flag)
		{
			return V_Return_Flag;
		}
	}

	V_Return_Flag=SF_ReadE2Three(E2Addr_Min_Free_FlashAddr_Allo,64,&Vu_FlashAddr[0]);	/*获取不同方案分配起始、结束地址*/
	if(C_OK!=V_Return_Flag)	/*调用默认分配地址，没有设置过关联列表，总清*/
	{
		V_Return_Flag=SF_MinFreezeDefProDistr(8);
		if(C_OK!=V_Return_Flag)
		{
			return V_Return_Flag;
		}
		V_Return_Flag=SF_ReadE2Three(E2Addr_Min_Free_FlashAddr_Allo,64,&Vu_FlashAddr[0]);	/*获取不同方案分配起始、结束地址*/
	}

	if(C_OK==V_Return_Flag)
	{
		for(V_i=0;V_i<V_ProNum;V_i++)
		{
			V_Return_Flag=SF_WriteE2Three((E2Addr_Min_Free_Flash_Ear1+V_i*12),4,&Vu_FlashAddr[V_i*8]);	/*12\6\8,结合E2存储方式	，设置为最早记录地址，即无记录数据*/
			V_Return_Flag=SF_WriteE2Three((E2Addr_Min_Free_Flash_Ear1+V_i*12+6),4,&Vu_FlashAddr[V_i*8]);
		}
	}

	return V_Return_Flag;
}
/*********************************************************************************
函数原型：uchar8 SF_Clear_Freeze(uchar8 V_D_SafeFlag)
功能描述：清冻结类数据，内部判断安全标志
输入参数：uchar8 V_D_SafeFlag:清零安全标志，C_ClearMeterSafeFlag，0x86
输出参数：无
返回参数：C_OK、C_IICError、C_SafeFlagError
功能说明：
调用机制：
备     注：698冻结数据清零，E2存储最近、最早Flash地址，都调整为Flash记录首页地址,
		有记录时，V_E2AddrEar最早1条记录首地址(绝对地址，前面为标志字)；V_E2AddrLate为最近1条记录页地址
*********************************************************************************/
uchar8 SF_Clear_Freeze(uchar8 V_D_SafeFlag,uchar8 V_OIB)
{
	uchar8 V_Return_Flag=C_Error,V_i;
	uchar8 P_Data[4];
	ulong32 V_FlashAddr;

	if(C_ClearMeterSafeFlag!=V_D_SafeFlag)
	{
		return C_SafeFlagError;
	}

	GV_D_SafeFlag = V_D_SafeFlag;

	if(V_OIB == 0xFF)
	{
		for(V_i=0;V_i<Str_698FreezeDataTable_Len;V_i++)
		{

			V_FlashAddr=Str_698FreezeDataTable[V_i].V_StaFlashAddr;
			PF_Ulong32ToBuffer4(&P_Data[0],& V_FlashAddr,4);
			V_Return_Flag=SF_WriteE2Three(Str_698FreezeDataTable[V_i].V_E2AddrEar,4,&P_Data[0]);
			V_Return_Flag=SF_WriteE2Three(Str_698FreezeDataTable[V_i].V_E2AddrLate,4,&P_Data[0]);
		}

		V_Return_Flag=SF_Clear_MinFreeze(GV_D_SafeFlag);/*清分钟冻结*/
	}
	else
	{
		uchar8 V_DI2Temp;

		V_DI2Temp=(uchar8)((C_RelatedOAD_Min&0x00FF0000)>>16);

		for(V_i=0;V_i<Str_698FreezeDataTable_Len;V_i++)
		{

			if(V_OIB == Str_698FreezeDataTable[V_i].V_DI2)
			{
				if(V_OIB==V_DI2Temp)/*分钟冻结*/
				{
					V_Return_Flag=SF_Clear_MinFreeze(GV_D_SafeFlag);/*清分钟冻结*/
				}
				else
				{
					V_FlashAddr=Str_698FreezeDataTable[V_i].V_StaFlashAddr;
					PF_Ulong32ToBuffer4(&P_Data[0],& V_FlashAddr,4);
					V_Return_Flag=SF_WriteE2Three(Str_698FreezeDataTable[V_i].V_E2AddrEar,4,&P_Data[0]);
					V_Return_Flag=SF_WriteE2Three(Str_698FreezeDataTable[V_i].V_E2AddrLate,4,&P_Data[0]);
				}
				break;
			}
		}
	}

	return V_Return_Flag;
}
/*********************************************************************************
函数原型：uchar8 SF_Clear_Other(uchar8 V_D_SafeFlag)
功能描述：清其它类数据，内部判断安全标志
输入参数：uchar8 V_D_SafeFlag:清零安全标志，C_ClearMeterSafeFlag，0x86
输出参数：无
返回参数：C_OK、C_IICError、C_SafeFlagError
功能说明：
调用机制：
备     注：
*********************************************************************************/
uchar8 SF_Clear_Other(uchar8 V_D_SafeFlag)
{
	uchar8 V_i=C_OK;
	ushort16 V_j,V_CRC16;

	if(C_ClearMeterSafeFlag!=V_D_SafeFlag)
	{
		return C_SafeFlagError;
	}
	else
	{
		/*清当前电压合格率相关数据，清1相，其余全清*/
		for(V_i=0;V_i<4;V_i++)
		{
			for(V_j=0;V_j<CLVol_Per_Pass_M;V_j++)
			{
				GV_CurrMVolPerPass[V_i][V_j]=0x00;
			}

			V_CRC16=PF_Cal_CRC(&GV_CurrMVolPerPass[V_i][0],CLVol_Per_Pass_M);
			PF_Ushort16ToBuffer2(&GV_CurrMVolPerPass[V_i][CLVol_Per_Pass_M],&V_CRC16);
		}

		for(V_i=0;V_i<CLVol_PassTime_M;V_i++)		/*清电压合格时间，自扩*/
		{
			GV_Voltage_PassTime[V_i]=0x00;
		}
		V_CRC16=PF_Cal_CRC(&GV_Voltage_PassTime[0],CLVol_PassTime_M);
		PF_Ushort16ToBuffer2(&GV_Voltage_PassTime[CLVol_PassTime_M],&V_CRC16);

		for(V_i=0;V_i<CLCurrMon_Vol_Pass_Time;V_i++)		/*清本月总电压合格时间，02800024*/
		{
			GV_CurrMon_Vol_Pass_Time[V_i]=0x00;
		}

		for(V_i=0;V_i<4;V_i++)		/*清日电压合格率相关数据，清1相，其余全清*/
		{
			for(V_j=0;V_j<CLVol_Per_Pass_D;V_j++)
			{
				GV_CurrDVolPerPass[V_i][V_j]=0x00;
			}
			V_CRC16=PF_Cal_CRC(&GV_CurrDVolPerPass[V_i][0],CLVol_Per_Pass_D);
			PF_Ushort16ToBuffer2(&GV_CurrDVolPerPass[V_i][CLVol_Per_Pass_D],&V_CRC16);
		}

#if 0
		for(V_i=0;V_i<CLVol_PassTime_D;V_i++)	/*清日电压合格时间，自扩*/
		{
			GV_Voltage_PassTime_D[V_i]=0x00;
		}
		V_CRC16=PF_Cal_CRC(&GV_Voltage_PassTime_D[0],CLVol_PassTime_D);
		PF_Ushort16ToBuffer2(&GV_Voltage_PassTime_D[CLVol_PassTime_D],&V_CRC16);
#endif
		return C_OK;
	}
}
/*********************************************************************************
函数原型：uchar8 InF_EventNote_Clear(uchar8 Msg_Num,ulong32 V_Data_Id,uchar8 C_Safe_Flag)
功能描述：事件记录清零，通信调用
输入参数：uchar8 Msg_Num：调用消息号；
		ulong32 V_Data_Id：数据标识
		uchar8 C_Safe_Flag：总清安全标志，取值为C_ClearMeterSafeFlag=0x86；
输出参数：无
返回参数：C_OK、C_IICError、C_NoAccess、C_SafeFlagError,C_IDError
功能说明：
调用机制：
备     注：
*********************************************************************************/
uchar8 InF_EventNote_Clear(uchar8 Msg_Num,ulong32 V_Data_Id,uchar8 C_Safe_Flag)
{
	uchar8 V_Return_Flag,V_DI,V_i;
	uchar8 V_ClearSign,V_DataLen;
	ushort16 V_j,V_E2Addr;
	uchar8 V_Buff[40];

	memset(&V_Buff[0],0x00,40);		/*初始化为全零*/

	if(C_Msg_Communication!=Msg_Num)
	{
		return C_NoAccess;
	}

	if(C_W_SafeFlag!=C_Safe_Flag)
	{
		return C_SafeFlagError;
	}
	else
	{
		V_ClearSign=C_ClearMeterSafeFlag;
		GV_D_SafeFlag=C_ClearMeterSafeFlag;
	}

	V_DI=(uchar8)V_Data_Id;
	if(0xFF!=V_DI)
	{
		return C_IDError;
	}

	if(0xFFFFFFFF==V_Data_Id)
	{
		if(C_ClearMeterSafeFlag==V_ClearSign)
		{
			for(V_j=0;V_j<(Str_EvenTableE2_Len-2);V_j++)	/*总清,不包含事件清零记录,校表记录清零*/
			{

				memset(&V_Buff[0],0x00,40);		/*初始化为全零*/

				if((Str_EvenTableE2[V_j].V_DI)!=(CSoft_I_J_Prog_Degree|EventDI))	/*去除软I_J记录*/
				{
					V_E2Addr=Str_EvenTableE2[V_j].V_E2AddrEnd-Str_EvenTableE2[V_j].V_E2AddrSt;
					V_DataLen=CLBuyCurr_Degree+C_CRCLen2;	/*累计时间及次数都是4字节,如非4字节，需更改该部分代码*/
					if(V_E2Addr==V_DataLen)
					{
						V_E2Addr=Str_EvenTableE2[V_j].V_E2AddrSt;
						V_Return_Flag=SF_WriteE2Three(V_E2Addr,CLBuyCurr_Degree,&V_Buff[0]);
					}
					else
					{
						if(V_E2Addr==(2*V_DataLen))/*累计时间及次数都是4字节,如非4字节，需更改该部分代码*/
						{
							V_E2Addr=Str_EvenTableE2[V_j].V_E2AddrSt;
							V_Return_Flag=SF_WriteE2Three(V_E2Addr,CLBuyCurr_Degree,&V_Buff[0]);
							V_E2Addr+=V_DataLen;
							V_Return_Flag=SF_WriteE2Three(V_E2Addr,CLBuyCurr_Degree,&V_Buff[0]);
						}
						else
						{
							return C_Error;/*正常不存在*/
						}
					}
				}

				if(C_OK!=V_Return_Flag)
				{
					return V_Return_Flag;
				}
			}

			/***********************软IJ********************************/
			V_Return_Flag=SF_WriteE2Three(E2Addr_Soft_I_J_Prog_1,CLSoft_I_J_Prog_1,&V_Buff[0]);
			V_Return_Flag=SF_WriteE2Three(E2Addr_Soft_I_J_Prog_2,CLSoft_I_J_Prog_2,&V_Buff[0]);

			V_Return_Flag=SF_WriteE2Three(E2Addr_ProgReC1,CLProgReC1_Degree,&V_Buff[0]);	/*清组合无功1、组合无功2总次数*/
			V_Return_Flag=SF_WriteE2Three(E2Addr_ProgReC2,CLProgReC2_Degree,&V_Buff[0]);

			/*山东双协议增加，645时段表编程记录、时区表编程记录清零*/
			V_Return_Flag=SF_WriteE2Three(E2Addr_ProgPT_CurrentPart_Degree,CLProgPT_CurrentPart_Degree,&V_Buff[0]);
			V_Return_Flag=SF_WriteE2Three(E2Addr_ProgTZ_CurrentPart_Degree,CLProgTZ_CurrentPart_Degree,&V_Buff[0]);
			V_Return_Flag=SF_WriteE2Three(E2Addr_Program_Degree_645,CLProgram_Degree_645,&V_Buff[0]);	/*645编程记录*/

			return V_Return_Flag;
		}
		else
		{
			return C_SafeFlagError;
		}
	}

	for(V_i=0;V_i<Str_EvenTableE2_Len;V_i++)	/*分项事件清零*/
	{
		if(V_Data_Id==Str_EvenTableE2[V_i].V_DI)
		{
			break;
		}
	}

	if(Str_EvenTableE2_Len==V_i)
	{
		 return C_IDError;
	}

	memset(&V_Buff[0],0x00,40);		/*初始化为全零*/

	V_E2Addr=Str_EvenTableE2[V_i].V_E2AddrEnd-Str_EvenTableE2[V_i].V_E2AddrSt;
	V_DataLen=CLBuyCurr_Degree+C_CRCLen2;		/*累计时间及次数都是4字节,如非4字节，需更改该部分代码*/
	if(V_E2Addr==V_DataLen)
	{
		V_E2Addr=Str_EvenTableE2[V_i].V_E2AddrSt;
		V_Return_Flag=SF_WriteE2Three(V_E2Addr,CLBuyCurr_Degree,&V_Buff[0]);
	}
	else
	{
		if(V_E2Addr==(2*V_DataLen))		/*累计时间及次数都是4字节,如非4字节，需更改该部分代码*/
		{
			V_E2Addr=Str_EvenTableE2[V_i].V_E2AddrSt;
			V_Return_Flag=SF_WriteE2Three(V_E2Addr,CLBuyCurr_Degree,&V_Buff[0]);
			V_E2Addr+=V_DataLen;
			V_Return_Flag=SF_WriteE2Three(V_E2Addr,CLBuyCurr_Degree,&V_Buff[0]);
		}
		else
		{
			return C_Error;		/*正常不存在*/
		}
	}

	if(V_Data_Id==(CProgReC_Degree|EventDI))	/*组合无功*/
	{
		V_Return_Flag=SF_WriteE2Three(E2Addr_ProgReC1,CLProgReC1_Degree,&V_Buff[0]);	/*清组合无功1、组合无功2总次数*/
		V_Return_Flag=SF_WriteE2Three(E2Addr_ProgReC2,CLProgReC2_Degree,&V_Buff[0]);
	}

	/*山东双协议增加，698中时段/时区表编程记录删除，同时删除645存储的事件记录*/
	memset(&V_Buff[0],0x00,40);/*初始化为全零*/

	if(V_Data_Id==(CProgPT_Degree|EventDI))
	{
		V_Return_Flag=SF_WriteE2Three(E2Addr_ProgPT_CurrentPart_Degree,CLProgPT_CurrentPart_Degree,&V_Buff[0]);
	}

	if(V_Data_Id==(CProgTZ_Degree|EventDI))
	{
		V_Return_Flag=SF_WriteE2Three(E2Addr_ProgTZ_CurrentPart_Degree,CLProgTZ_CurrentPart_Degree,&V_Buff[0]);
	}

	if(V_Data_Id==(CProgram_Degree|EventDI))/*645编程记录*/
	{
		V_Return_Flag=SF_WriteE2Three(E2Addr_Program_Degree_645,CLProgram_Degree_645,&V_Buff[0]);
	}

	return V_Return_Flag;
}

/*********************************************************************************
函数原型：uchar8 InF_EventNumFind(ulong32 V_Data_Id)
功能描述：根据数据标示返回事件记录号，供事件记录、通信模块用
输入参数：ulong32 V_Data_Id：数据标识
输出参数：无
返回参数：uchar8：EventNum,C_IDError
功能说明：事件记录模块，用于获取Num号；通信模块用于判断标识码是否正确
调用机制：
备     注：
*********************************************************************************/
uchar8 InF_EventNumFind(ulong32 V_Data_Id)
{
	uchar8 V_i,V_DI;

	V_DI=(uchar8)V_Data_Id;
	if(0xFF!=V_DI)
	{
		return C_IDError;
	}

	for(V_i=0;V_i<Str_EvenTableE2_Len;V_i++)
	{
		if(V_Data_Id==Str_EvenTableE2[V_i].V_DI)
		{
			break;
		}
	}

	if(Str_EvenTableE2_Len==V_i)
	{
		return C_IDError;
	}
	else
	{
		return Str_EvenTableE2[V_i].V_EventNum;
	}
}
/*********************************************************************************
函数原型：uchar8 InF_RecMeterNote_Clear(uchar8 Msg_Num,uchar8 C_Safe_Flag)
功能描述：通信调用,清校表记录，数据层内部清校表记录次数指针
输入参数：uchar8 Msg_Num：调用消息号；
		uchar8 C_Safe_Flag：总清安全标志，0x68；
输出参数：无
返回参数：C_OK、C_IICError、C_NoAccess、C_SafeFlagError
功能说明：
调用机制：
备     注：
*********************************************************************************/
uchar8 InF_RecMeterNote_Clear(uchar8 Msg_Num,uchar8 C_Safe_Flag)
{
	uchar8 V_Return_Flag;
	uchar8 V_Buff[3];

	memset(&V_Buff[0],0x00,3);/*初始化为全零*/

	if(C_Msg_Communication!=Msg_Num)
	{
		return C_NoAccess;
	}

	if(C_W_SafeFlag!=C_Safe_Flag)
	{
		return C_SafeFlagError;
	}

	GV_D_SafeFlag=C_Safe_Flag;
	V_Return_Flag=SF_WriteE2Three(E2Addr_Rec_Meter_Degree,3,&V_Buff[0]);

	GV_D_SafeFlag=C_Clear_SafeFlag;

	return V_Return_Flag;
}

/*********************************************************************************
函数原型：uchar8 InF_Demand_Clear(uchar8 Msg_Num,uchar8 C_Safe_Flag)
功能描述：需量清零,通信、结算调用
输入参数：uchar8 Msg_Num：调用消息号；
		uchar8 C_Safe_Flag：总清安全标志，0x68；
输出参数：无
返回参数：C_OK、C_IICError、C_NoAccess、C_SafeFlagError
功能说明：
调用机制：
备     注：
*********************************************************************************/
uchar8 InF_Demand_Clear(uchar8 Msg_Num, uchar8 C_Safe_Flag)
{
	uchar8 V_Return_Flag = C_OtherErr_DAR,V_i;
	ushort16 V_j,V_E2Addr;
	uchar8 V_Buff[CLRev_Ac_Tol_De_0];
	uchar8 V_DataLen;

	memset(&V_Buff[0],0x00,CLRev_Ac_Tol_De_0);/*初始化为全零*/

	if((C_Msg_Communication!=Msg_Num)&&(C_Msg_SettleAccounts!=Msg_Num))
	{
		return C_NoAccess;
	}

	if(C_W_SafeFlag!=C_Safe_Flag)
	{
		return C_SafeFlagError;
	}

	GV_D_SafeFlag=C_ClearMeterSafeFlag;

	/*结算消息，通信都只清当前需量、参数中当前有、无功需量及视在需量，总清时才清结算需量*/
	if(C_W_SafeFlag==C_Safe_Flag)
	{
		for(V_j=0;V_j<(Str_2Table_DIDe10_Len);V_j++)/*清当前需量*/
		{

			memset(&V_Buff[0],0x00,CLRev_Ac_Tol_De_0);/*初始化为全零*/

			if((Str_2Table_DIDe10[V_j].V_DT_Type)&NeedClearDataSign)/*需清零数据*/
			{
				if(Str_2Table_DIDe10[V_j].V_DataLen>CLRev_Ac_Tol_De_0)
				{
					return C_Error;/*正常不存在*/
				}

				V_DataLen=(uchar8)(Str_2Table_DIDe10[V_j].V_DataLen);
				V_E2Addr=(ushort16)Str_2Table_DIDe10[V_j].PStr_3TableAddr;
				V_Return_Flag=SF_WriteE2Three(V_E2Addr,V_DataLen,&V_Buff[0]);
			}

			if(C_OK!=V_Return_Flag)
			{
				return V_Return_Flag;
			}
		}

		for(V_i=0;V_i<CLCurr_AcDemand;V_i++)
		{
			GV_Curr_AcDemand[V_i]=0;	/*当前有功需量*/
			GV_Curr_ReDemand[V_i]=0;	/*当前无功需量*/
		}
	}
	else
	{
		return C_SafeFlagError;
	}

	return V_Return_Flag;
}
/*********************************************************************************
函数原型：void Data_CruiseCheck_Message(Str_Msg_Parameter *P_Msg_Parameter)
功能描述：数据层巡航程序，调度每5s触发，不用带参数.定时20min(根据调度5s累加)，RAM当前电量更新E2，更新ESAM透支、剩余金额。
		同时巡检Flash是否为空，每次巡检一个；另外检查，当前电量RAM数据，CRC是否正常，不正常E2更新RAM，每次检查1个
输入参数：Str_Msg_Parameter *P_Msg_Parameter:消息参数结构体
输出参数：无
返回参数：无
功能说明：
调用机制：
备     注：目前当前电能存铁电，不用定时20min保存。本部分检查RAM电能还是存在
*********************************************************************************/
void Data_CruiseCheck_Message(Str_Msg_Parameter *P_Msg_Parameter)
{
	ulong32 V_FlashAddr;
	uchar8 V_FlashZero[C_Flash_EmptyNum],V_i;
	uchar8 V_Return_Flag;
	uchar8 V_DataLen;
	uchar8 Vuc_Buff_FramEnergy[C_CurrDataLen5+C_CRCLen2];
	ushort16 Vus_EneryE2Addr;

	V_DataLen=C_CurrDataLen5+C_CRCLen2;      /*铁电中当前电量数据长度*/

	GV_D_SafeFlag=C_Clear_SafeFlag;                 /*巡检安全标志清零*/
	GV_D_ClearSafeFlag=C_Clear_SafeFlag;

	if(C_PowerOn!=(*P_Msg_Parameter).PowerFlag)      /*掉电直接退出*/
	{
		return;
	}

	GV_D_SafeFlag|=C_W_SafeFlag_1;

	if(C_Msg_Dispatch!=(*P_Msg_Parameter).SourceAddr)
	{
		GV_D_SafeFlag=C_Clear_SafeFlag;                 /*巡检安全标志清零*/
		return;
	}

	GV_D_SafeFlag|=C_W_SafeFlag_2;

	if(GV_CruiseCheck_RAMNum<C_CurrEnergy_Len)      /*巡检当前电量RAM CRC*/
	{
		Vus_EneryE2Addr=GV_CruiseCheck_RAMNum*V_DataLen;
		Vus_EneryE2Addr=Vus_EneryE2Addr+E2Addr_CurrEnergy_St;
		V_Return_Flag=SF_ReadFRAMThree_AndCRC(Vus_EneryE2Addr,C_CurrDataLen5,&Vuc_Buff_FramEnergy[0]);   /*读铁电当前电能数据包括CRC*/
		if(C_OK == V_Return_Flag)
		{
			if(C_Equal != PF_Campare_Data(&Vuc_Buff_FramEnergy[0],&GV_CurrEnergyData[GV_CruiseCheck_RAMNum][0],(C_CurrDataLen5+C_CRCLen2)))
			{
				PF_CopyDataBytes(&Vuc_Buff_FramEnergy[0],&GV_CurrEnergyData[GV_CruiseCheck_RAMNum][0],(C_CurrDataLen5+C_CRCLen2));/*包括CRC*/
			}
		}

		GV_CruiseCheck_RAMNum++;
	}
	else
	{
		GV_CruiseCheck_RAMNum=0;
	}

	GV_D_SafeFlag|=C_W_SafeFlag_3;

	GV_20min_Num++;
	if(GV_20min_Num>=C_GV_20min_Num)
	{
		GV_20min_Num=0;
		SF_UpdateE2CurrEnergy();
	}

	/*重要数据定时校验*/
	SF_ImportantDataCheckAndRecover();

	if(GV_CruiseCheck_FlashNum<(Str_3cTable_Flash_Len+Str_3dTable_Flash_Len))           /*巡检Flash表格*/
	{
		V_FlashAddr=SF_FindEvenFlashPage();

		GV_CruiseCheck_FlashNum++;

		if(0xFFFFFFFF==V_FlashAddr)                               /*当前页记录次数不满足擦除条件,奇偶记录大于12次，本次查询结束*/
		{
			GV_D_SafeFlag=C_Clear_SafeFlag;                 /*巡检安全标志清零*/
			return;
		}
	}
	else                                                        /*最后巡检负荷记录,698修改为冻结数据*/
	{
		V_FlashAddr=SF_FindLoadProfileFlashPage();   /*记录跨页调整时，已经更改E2中记录模式字，该处不用处理，函数内部GV_CruiseCheck_FlashNum赋初值*/
		if(0xFFFFFFFF==V_FlashAddr)
		{
			GV_D_SafeFlag=C_Clear_SafeFlag;                 /*巡检安全标志清零*/
			return;
		}
	}

	V_FlashAddr=V_FlashAddr+C_OneFlashPage-C_Flash_EmptyNum;    /*最后4个字节Flash地址*/
	if(V_FlashAddr>=C_Flash_Max_Addr)                           /*理论不存在*/
	{
		GV_CruiseCheck_FlashNum=0;/*Flash巡航4级表，*/
		GV_D_SafeFlag=C_Clear_SafeFlag;                 /*巡检安全标志清零*/
		return;
	}

	InF_FlashChipSelect();
	InF_ReadFlash(V_FlashAddr,&V_FlashZero[0],C_Flash_EmptyNum);
	for(V_i=0;V_i<C_Flash_EmptyNum;V_i++)  /*判断Flash页是否为空,空标志68*/
	{
		if(C_Flash_Empty68!=V_FlashZero[V_i])
		{
			break;
		}
	}

	if(V_i<C_Flash_EmptyNum)       /*当前页Flash不为空*/
	{
		SF_EraseFlashAndWriteEmptySign(V_FlashAddr);
	}

	GV_D_SafeFlag=C_Clear_SafeFlag;                 /*巡检安全标志清零*/
}

/*********************************************************************************
函数原型：void SF_UpdateE2CurrEnergy(void)
功能描述：定时刷新E2电能，ESAM数据,目前是20min。在巡检程序中会校对RAMCRC，在该部分不判断CRC。
		同时对电表运行状态字1、3电表类型进行刷新
输入参数：无
输出参数：无
返回参数：无
功能说明：
调用机制：
备     注：内部判断电量增量的合理性，采用先读出判断是否相等，再写入的方式。
		其中剩余金额，透支金额只判断金额大小的合理性，没有判断限值.主流程已置安全标志
		后更改该函数为外部函数调用，由通信调用配合InF_RAMDataRecoverFromE2，防止电能数据异常，
		更新程序前，采用恢复命令，调用该函数保存电量。
*********************************************************************************/
void SF_UpdateE2CurrEnergy(void)
{
	uchar8 PV_E2Data[C_CurrDataLen5];
	uchar8 V_E2DataFlag;
	uchar8 C_Meter_Work_State3, V_StateBuff;
	ushort16 V_usDataLen, V_usDataEncode;

	if(C_Meter_Type == C_L_SmartMeter)
	{
		C_Meter_Work_State3 = 0x02;
	}
	else
	{
		C_Meter_Work_State3 = 0x00;
	}

	GV_Meter_Work_State[2][1] = GV_Meter_Work_State[2][1] & 0xF0;					/*电表运行状态字3*/
	GV_Meter_Work_State[2][1] = GV_Meter_Work_State[2][1] | C_Meter_Work_State3;

	V_StateBuff = (uchar8)(C_Meter_Work_State1);
	GV_Meter_Work_State[0][0] = GV_Meter_Work_State[0][0] & V_StateBuff;			/*电表运行状态字1*/
	V_StateBuff = (uchar8)(C_Meter_Work_State1 >> 8);
	GV_Meter_Work_State[0][1] = GV_Meter_Work_State[0][1] & V_StateBuff;

	V_StateBuff = (uchar8)(C_Meter_Work_State2);
	GV_Meter_Work_State[1][0] = GV_Meter_Work_State[1][0] & V_StateBuff;			/*电表运行状态字2*/
	V_StateBuff = (uchar8)(C_Meter_Work_State2 >> 8);
	GV_Meter_Work_State[1][1] = GV_Meter_Work_State[1][1] & V_StateBuff;

	V_StateBuff = (uchar8)(C_Meter_Work_State4);
	GV_Meter_Work_State[3][0] = GV_Meter_Work_State[3][0] & V_StateBuff;			/*电表运行状态字4*/
	V_StateBuff = (uchar8)(C_Meter_Work_State4>>8);
	GV_Meter_Work_State[3][1] = GV_Meter_Work_State[3][1] & V_StateBuff;

	V_StateBuff = (uchar8)(C_Meter_Work_State5);
	GV_Meter_Work_State[4][0] = GV_Meter_Work_State[4][0] & V_StateBuff;			/*电表运行状态字5*/
	V_StateBuff = (uchar8)(C_Meter_Work_State5 >> 8);
	GV_Meter_Work_State[4][1] = GV_Meter_Work_State[4][1] & V_StateBuff;

	V_StateBuff = (uchar8)(C_Meter_Work_State6);
	GV_Meter_Work_State[5][0] = GV_Meter_Work_State[5][0] & V_StateBuff;			/*电表运行状态字6*/
	V_StateBuff = (uchar8)(C_Meter_Work_State6 >> 8);
	GV_Meter_Work_State[5][1] = GV_Meter_Work_State[5][1] & V_StateBuff;

	V_StateBuff = (uchar8)(C_Meter_Work_State7);
	GV_Meter_Work_State[6][0] = GV_Meter_Work_State[6][0] & V_StateBuff;			/*电表运行状态字7*/
	V_StateBuff = (uchar8)(C_Meter_Work_State7 >> 8);
	GV_Meter_Work_State[6][1] = GV_Meter_Work_State[6][1] & V_StateBuff;

	V_StateBuff = C_HardError;
	GV_HardError_State[0] = GV_HardError_State[0] & V_StateBuff;

	/*******************更新ESAM剩余金额，蒋工接口函数*****************************/
	V_usDataLen = CLChargeBal_Hex_Cent;
	V_E2DataFlag = InF_GetData_ObjectManage(CChargeBal_Hex_Cent, &PV_E2Data[0], &V_usDataLen, &V_usDataEncode);		/*读电能模块接口函数，获取当前剩余金额hex格式*/
	if( C_OK == V_E2DataFlag )     						/*读数据正常*/
	{
		if( C_W_SafeFlag == GV_D_SafeFlag )
		{
			if( C_OK == InF_IS_UpdateMInEsamTimer() )	/*判断是否可以刷新ESAM，不在15min范围内，才能刷新*/
			{                                    		/*bbb标准规定：更新ESAM钱包文件间隔时间不应小于15min*/
				InF_S_UpdataChargeBalInESAM( &PV_E2Data[0] );
			}
		}
	}

	if(C_ESAMPower == C_ESAMPower_Close)				/*上电关ESAM电源，只送样用，正常生产不启用。*/
	{
		if( (Com_Conect.ConectOverTime==0)
			&& (Com_Conect.ConectOverTime_termal == 0)
			&& (JudgeTimerExceed10min(&IR_AuthT) != C_TimerEnable)
			&& (JudgeTimerExceed10min(&ID_AuthT_T) != C_TimerEnable) )
		{
			InF_Deactivation_7816_Esam();				/*停活ESAM*/
		}
	}
}
/*********************************************************************************
函数原型：ulong32 SF_FindEvenFlashPage(void)
功能描述：查找需巡检的Flash页
输入参数：无
输出参数：无
返回参数：ulong32：需巡检的Flash页地址，当奇偶记录次数不满12次时，返回全FF
功能说明：
调用机制：
备     注：
*********************************************************************************/
ulong32 SF_FindEvenFlashPage(void)
{
	uchar8 P_Dgree[CLAll_Loss_Vol_Degree];
	Str_3cTable PStr_3cTable_Flash;
	ulong32 V_Dgree,V_FlashAddr;
	uchar8 V_Flash_Page,V_Flash_PageNum;
	ushort16 V_FlashPrePageNum,V_Page_Agree;
	Str_3dEventTable PStr_3dTable_Flash;
	uchar8 V_Num;
	ushort16 V_Num_E2BakeUp1Addr,V_DataToalLen;
	ulong32 V_StaFlashAddr,V_EndFlashAddr;

	if(GV_CruiseCheck_FlashNum>=Str_3cTable_Flash_Len)  /*正常是3d表格*/
	{
		V_Num=GV_CruiseCheck_FlashNum-Str_3cTable_Flash_Len;
		if(V_Num>=Str_3dTable_Flash_Len)/*正常不存在*/
		{
			GV_CruiseCheck_FlashNum=0;/*Flash巡航*/
			return 0xFFFFFFFF;
		}
		else/*4d表格*/
		{
			PStr_3dTable_Flash=Str_3d698EventTable_Flash[V_Num];
			V_Num_E2BakeUp1Addr=PStr_3dTable_Flash.V_Num_E2BakeUp1Addr;
			V_StaFlashAddr=PStr_3dTable_Flash.V_StaFlashAddr;
			V_EndFlashAddr=PStr_3dTable_Flash.V_EndFlashAddr;
			V_DataToalLen=SF_GetEventDataLen(PStr_3dTable_Flash.V_TB_E2BakeUp1Addr,PStr_3dTable_Flash.V_TBLen_E2BakeUp1Addr,PStr_3dTable_Flash.PStr_4aTableAddr,PStr_3dTable_Flash.V_Str_4aTableLen);/*获取记录数据长度*/
			if((0==V_DataToalLen)||(0xFFFF==V_DataToalLen))/*异常情况*/
			{
				return	0xFFFFFFFF;
			}
		}
	}
	else
	{
		PStr_3cTable_Flash=Str_3cTable_Flash[GV_CruiseCheck_FlashNum];
		V_Num_E2BakeUp1Addr=PStr_3cTable_Flash.V_Num_E2BakeUp1Addr;
		V_StaFlashAddr=PStr_3cTable_Flash.V_StaFlashAddr;
		V_EndFlashAddr=PStr_3cTable_Flash.V_EndFlashAddr;
		V_DataToalLen=PStr_3cTable_Flash.V_DataToalLen;
	}

	if(SF_ReadE2Three(V_Num_E2BakeUp1Addr,CLAll_Loss_Vol_Degree,&P_Dgree[0]) != C_OK)
	{
		return 0xFFFFFFFF;
	}

	if(V_Num_E2BakeUp1Addr == E2Addr_Program_Degree_645)
	{
		P_Dgree[3] =0;
	}
	PF_Buffer4ToUlong32(&P_Dgree[0],&V_Dgree,4);

	if(0==V_Dgree)                  /*当前记录次数为0，则返回Flash记录地址首页*/
	{
		return V_StaFlashAddr;
	}
	else
	{
		if((0==V_DataToalLen)||(0xFFFF==V_DataToalLen))/*异常情况*/
		{
			return	0xFFFFFFFF;
		}

		V_Flash_Page=(uchar8)((V_EndFlashAddr-V_StaFlashAddr)/C_OneFlashPage);  /*取Flash记录页*/
		V_FlashPrePageNum=(ushort16)(V_Dgree%(C_OneFlash_PageNum/V_DataToalLen));                            /*奇偶页Flash保存，当前页记录次数*/

		if(1==V_Flash_Page)        /*奇偶页*/
		{
			if((0!=V_FlashPrePageNum)&&(V_FlashPrePageNum<C_FlashEvenOEEPageNum))   /*当前页记录不满12次，不查询，擦除下一页,取零整数页已经擦除，本次没有包含*/
			{
				return 0xFFFFFFFF;
			}
		}

		V_Page_Agree=(ushort16)(C_OneFlash_PageNum/V_DataToalLen);  /*每页可记录数据次数*/
		V_Flash_PageNum=V_Flash_Page+1;                   /*该记录Flash存储页总数,C_OneFlashPage:0x00001000*/
		V_FlashAddr=(((V_Dgree-1)/V_Page_Agree)%V_Flash_PageNum)*C_OneFlashPage+V_StaFlashAddr;  /*当前记录次数，Flash页地址*/
		if(V_FlashAddr==V_EndFlashAddr)          /*Flash记录尾页*/
		{
			V_FlashAddr=V_StaFlashAddr;          /*返回首页地址*/
			return V_FlashAddr;
		}
		else
		{
			return (V_FlashAddr+C_OneFlashPage);	                    /*返回下页地址*/
		}
	}
}
/*********************************************************************************
函数原型：ulong32 SF_FindLoadProfileFlashPage(void)
功能描述：查找负荷记录需巡检的Flash页
输入参数：无
输出参数：无
返回参数：ulong32：需巡检的Flash页地址
功能说明：
调用机制：
备     注：目前修改为冻结记录
*********************************************************************************/
ulong32 SF_FindLoadProfileFlashPage(void)
{
	ulong32 V_FlashAddrLate,V_FlashAddrEar;
	uchar8 V_FlashAddr8[4];
	uchar8 V_i;
	ushort16 V_E2Addr_LoadP_Flash_Late,V_E2Addr_LoadP_Flash_Ear;
	ulong32 V_FlashStAddr_LoadProfile,V_FlashEndAddr_LoadProfile;
	uchar8 V_ProNum,V_DI2,V_Return_Flag;

	V_ProNum=InF_GetMinFreezeTolNum();/*获取分钟冻结总方案数,1--8*/
	if(V_ProNum>8)
	{
		V_ProNum=0;
	}

	V_DI2=(uchar8)((C_RelatedOAD_Min&0x00FF0000)>>16);
	if(GV_CruiseCheck_FlashNum<(Str_3cTable_Flash_Len+Str_3dTable_Flash_Len))/*正常不存在*/
	{
		return 0xFFFFFFFF;
	}

	V_i=GV_CruiseCheck_FlashNum-(Str_3cTable_Flash_Len+Str_3dTable_Flash_Len);
	if(V_i>=(Str_698FreezeDataTable_Len+V_ProNum))/*正常不会运行到，只是安全性判断*/
	{
		GV_CruiseCheck_FlashNum=0;/*Flash巡航4级表*/
		return 0xFFFFFFFF;
	}
	else
	{
		GV_CruiseCheck_FlashNum++;
		if(GV_CruiseCheck_FlashNum>=(Str_3cTable_Flash_Len+Str_698FreezeDataTable_Len+V_ProNum+Str_3dTable_Flash_Len))/*增加分钟冻结不同方案*/
		{
			GV_CruiseCheck_FlashNum=0;/*Flash巡航4级表*/
		}

		if(V_i<Str_698FreezeDataTable_Len)/*除分钟冻结外其他冻结类*/
		{
			V_E2Addr_LoadP_Flash_Late=Str_698FreezeDataTable[V_i].V_E2AddrLate;
			V_E2Addr_LoadP_Flash_Ear=Str_698FreezeDataTable[V_i].V_E2AddrEar;
			V_FlashStAddr_LoadProfile=Str_698FreezeDataTable[V_i].V_StaFlashAddr;
			V_FlashEndAddr_LoadProfile=Str_698FreezeDataTable[V_i].V_EndFlashAddr;
			if(V_DI2==Str_698FreezeDataTable[V_i].V_DI2)/*分钟冻结	*/
			{
				return 0xFFFFFFFF;
			}
		}
		else/*分钟冻结方案*/
		{
			V_Return_Flag=SF_GetMinFreezePro_E2andFlashAddr((V_i-Str_698FreezeDataTable_Len),&V_FlashStAddr_LoadProfile,&V_FlashEndAddr_LoadProfile,&V_E2Addr_LoadP_Flash_Ear,&V_E2Addr_LoadP_Flash_Late);/*根据分钟冻结方案号，获取该方案最近、最早记录E2地址及该方案起始、结束Flash地址*/
			if(C_OK!=V_Return_Flag)
			{
				return 0xFFFFFFFF;
			}
		}

		if(SF_ReadE2Three(V_E2Addr_LoadP_Flash_Late,4,&V_FlashAddr8[0]) != C_OK)        /*取最近1条记录Flash页地址*/
		{
			return 0xFFFFFFFF;
		}
		PF_Buffer4ToUlong32(&V_FlashAddr8[0],&V_FlashAddrLate,4);
		V_FlashAddrLate&=0xFFFFF000;             /*页地址转化，增加容错性*/

		SF_ReadE2Three(V_E2Addr_LoadP_Flash_Ear,4,&V_FlashAddr8[0]);         /*取最早1条记录Flash地址*/
		PF_Buffer4ToUlong32(&V_FlashAddr8[0],&V_FlashAddrEar,4);

		if((V_FlashStAddr_LoadProfile==V_FlashAddrEar)                       /*没有负荷记录数据，绝对地址*/
			||(V_FlashEndAddr_LoadProfile==V_FlashAddrLate))                   /*负荷记录最后1页*/
		{
			return V_FlashStAddr_LoadProfile;
		}
		else
		{
			return (V_FlashAddrLate+C_OneFlashPage);
		}
	}
}

/*********************************************************************************
函数原型：void InF_Initial_Data(void)
功能描述：初始化数据层参数，调度调用.包括数据层写固定值参数
输入参数：无
输出参数：无
返回参数：无
功能说明：
调用机制：
备     注：
*********************************************************************************/
void InF_Initial_Data(void)
{
	uchar8 C_Meter_Work_State3;
	uchar8 V_StateBuff;

	GV_D_SafeFlag=C_Clear_SafeFlag;
	GV_20min_Num=C_GV_19min_50s_Num;/*上电初始化为19min50s，10s后(巡航程序中20min定时)调用SF_UpdateE2CurrEnergy，主要用于刷新ESAM钱包文件*/
	GV_CruiseCheck_FlashNum=0;/*Flash巡航4级表*/
	GV_CruiseCheck_RAMNum=0;
	GV_D_ClearSafeFlag=C_Clear_SafeFlag;


	GV_D_SafeFlag=C_Clear_SafeFlag;

	/*电表运行状态字3,电表型号 初始化，Bit0 、Bit1;状态字1：bit1*/
	if(C_Meter_Type==C_L_SmartMeter)
	{
		C_Meter_Work_State3=0x02;
	}
	else
	{
		C_Meter_Work_State3=0x00;
	}

	GV_Meter_Work_State[2][1]=GV_Meter_Work_State[2][1]&0xF0;                  /*电表运行状态字3*/
	GV_Meter_Work_State[2][1]=GV_Meter_Work_State[2][1]|C_Meter_Work_State3;

	V_StateBuff=(uchar8)(C_Meter_Work_State1);
	GV_Meter_Work_State[0][0]=GV_Meter_Work_State[0][0]&V_StateBuff;                  /*电表运行状态字1*/
	V_StateBuff=(uchar8)(C_Meter_Work_State1>>8);
	GV_Meter_Work_State[0][1]=GV_Meter_Work_State[0][1]&V_StateBuff;

	V_StateBuff=(uchar8)(C_Meter_Work_State2);
	GV_Meter_Work_State[1][0]=GV_Meter_Work_State[1][0]&V_StateBuff;                  /*电表运行状态字2*/
	V_StateBuff=(uchar8)(C_Meter_Work_State2>>8);
	GV_Meter_Work_State[1][1]=GV_Meter_Work_State[1][1]&V_StateBuff;

	V_StateBuff=(uchar8)(C_Meter_Work_State4);
	GV_Meter_Work_State[3][0]=GV_Meter_Work_State[3][0]&V_StateBuff;                  /*电表运行状态字4*/
	V_StateBuff=(uchar8)(C_Meter_Work_State4>>8);
	GV_Meter_Work_State[3][1]=GV_Meter_Work_State[3][1]&V_StateBuff;

	V_StateBuff=(uchar8)(C_Meter_Work_State5);
	GV_Meter_Work_State[4][0]=GV_Meter_Work_State[4][0]&V_StateBuff;                  /*电表运行状态字5*/
	V_StateBuff=(uchar8)(C_Meter_Work_State5>>8);
	GV_Meter_Work_State[4][1]=GV_Meter_Work_State[4][1]&V_StateBuff;

	V_StateBuff=(uchar8)(C_Meter_Work_State6);
	GV_Meter_Work_State[5][0]=GV_Meter_Work_State[5][0]&V_StateBuff;                  /*电表运行状态字6*/
	V_StateBuff=(uchar8)(C_Meter_Work_State6>>8);
	GV_Meter_Work_State[5][1]=GV_Meter_Work_State[5][1]&V_StateBuff;

	V_StateBuff=(uchar8)(C_Meter_Work_State7);
	GV_Meter_Work_State[6][0]=GV_Meter_Work_State[6][0]&V_StateBuff;                  /*电表运行状态字7*/
	V_StateBuff=(uchar8)(C_Meter_Work_State7>>8);
	GV_Meter_Work_State[6][1]=GV_Meter_Work_State[6][1]&V_StateBuff;

	V_StateBuff=C_HardError;
	GV_HardError_State[0]=GV_HardError_State[0]&V_StateBuff;

	GV_ReadLoadFlashAddr32=0xFFFFFFFF;     /*14规范负荷记录模块，连续抄读用*/
	GV_ReadLoadFlashAddr32Ear=0xFFFFFFFF;
	GV_ReadLoadFlashAddr32Late=0xFFFFFFFF;
	GV_SecLoadModeNum=0xFF;

	SF_Initial_GVStrNextEventData();			/*初始化CRC错误，抄读事件记录后续帧用*/
}
/*********************************************************************************
函数原型：void InF_RAMDataRecoverFromE2(void)
功能描述：针对RAM带CRCE2三处类型数据(全局变量Str_3aTable_E23RAM中数据)，根据E2数据对RAM数据进行恢复。
输入参数：无
输出参数：无
返回参数：无
功能说明：
调用机制：
备     注：主要是增加全局变量时，重新编译，RAM数据可能会乱(RAM地址串，看CMP编译文件可以看出，但CRC正确)。
		该函数用于采用E2数据，重新更新RAM数据,不包括电量数据。
		由通信模块触发调用.降本项目采用数据全0，则认为CRC错误，不需要数据恢复。
*********************************************************************************/
void InF_RAMDataRecoverFromE2(void)
{
	ushort16 V_i;
	uchar8 V_j;
	uchar8 V_Return_Flag,V_DataNum;
	ushort16 V_E2Addr,V_DataLen;
	uchar8 *P_RamAddr=NULL;
	Str_3aTable V_Str_3aTable;
	uchar8 P_OADTabLen_T[CLI_Free_OADTabLen_T];
	ushort16 V_OADTabLen_T;

	for(V_i=95;V_i<Str_3aTable_E23RAM_Len;V_i++)/*注意该部分操作与Str_3aTable_E23RAM表格一一对应,去除冻结关联列表*/
	{
		if((V_i>=233)&&(V_i<=243))/*去除冻结关联列表OADTab*/
		{
			continue;
		}

		P_RamAddr=Str_3aTable_E23RAM[V_i].V_RamAddr;
		V_E2Addr=Str_3aTable_E23RAM[V_i].V_E2BakeUp1Addr;
		V_DataLen=Str_3aTable_E23RAM[V_i].V_DataLen;
		V_DataNum=Str_3aTable_E23RAM[V_i].V_DataNum;

		for(V_j=0;V_j<V_DataNum;V_j++)
		{
			P_RamAddr=Str_3aTable_E23RAM[V_i].V_RamAddr;
			V_E2Addr=Str_3aTable_E23RAM[V_i].V_E2BakeUp1Addr;

			V_E2Addr=V_E2Addr+V_j*(V_DataLen+C_CRCLen2);
			P_RamAddr=P_RamAddr+V_j*(V_DataLen+C_CRCLen2);

			V_Return_Flag=SF_ReadE2Three_698_AndCRC(V_E2Addr,V_DataLen,P_RamAddr);
		}
	}

	/******************OAD序号表数据恢复*************************/
	for(V_i=0;V_i<11;V_i++)
	{
		V_Str_3aTable=Str_3aTable_E23RAM[V_i+221];/*Free_OADTabLen_T,序号表长度*/
		V_Return_Flag=SF_Re_E23_RAM_Data698(&V_Str_3aTable,CLI_Free_OADTabLen_T,&P_OADTabLen_T[0]);
		if(C_OK==V_Return_Flag)
		{
			V_OADTabLen_T=P_OADTabLen_T[0];
			V_OADTabLen_T=V_OADTabLen_T*C_698Free_OADTabDataType;/*序号表每个OAD序号C_698Free_OADTabDataType个字节,目前6字节。2字节序号+2字节冻结周期+2字节存储深度*/
			if(V_OADTabLen_T>C_698Free_OADTabLen)/*数据长度安全性判断*/
			{
				return;/*异常*/
			}

			V_DataLen=V_OADTabLen_T;
			V_DataNum=Str_3aTable_E23RAM[V_i+233].V_DataNum;
			for(V_j=0;V_j<V_DataNum;V_j++)
			{
				P_RamAddr=Str_3aTable_E23RAM[V_i+233].V_RamAddr;
				V_E2Addr=Str_3aTable_E23RAM[V_i+233].V_E2BakeUp1Addr;

				V_E2Addr=V_E2Addr+V_j*(C_698Free_OADTabLen+C_CRCLen2);
				P_RamAddr=P_RamAddr+V_j*(C_698Free_OADTabLen+C_CRCLen2);

				V_Return_Flag=SF_ReadE2Three_698_AndCRC(V_E2Addr,V_DataLen,P_RamAddr);/*所读数据长度根据实际数据长度*/
			}
		}
	}
}
/*********************************************************************************
函数原型：uchar8 SF_AllDataZero_Judge(uchar8 *P_Data,uchar8 V_DataLen)
功能描述：判断数据是否为全零
输入参数：uchar8 *P_Data:待判断数据，uchar8 V_DataLen：待判断数据长度
输出参数：无
返回参数：uchar8：C_OK:待判断数据为全0，C_Error：待判断数据不为全0
功能说明：
调用机制：
备     注：
*********************************************************************************/
uchar8 SF_AllDataZero_Judge(uchar8 *P_Data, uchar8 V_DataLen)
{
	uchar8 V_i;
	uchar8 V_Return_Flag;

	V_Return_Flag=C_OK;
	for(V_i=0;V_i<V_DataLen;V_i++)
	{
		if(P_Data[V_i]!=0)
		{
			break;
		}
	}
	if(V_i<V_DataLen)
	{
		V_Return_Flag=C_Error;
	}

	return V_Return_Flag;
}

uchar8 InF_ReadLoadData(ulong32 V_Data_Id,uchar8 *P_FixTime,uchar8 *P_Data,uchar8 *V_BlockNum,uchar8 *V_Length,uchar8 V_ReadSign)
{
	return C_OK;
}
uchar8 InF_ReadLastTimeLoadData(ulong32 V_Data_Id,uchar8 *P_FixTime,uchar8 *P_Data,uchar8 *V_BlockNum,uchar8 *V_Length)
{
	return C_OK;
}
/*********************************************************************************
函数原型：void InF_Get_Comm_Address(uchar8 *pV_ucComm_Address,uchar8 V_ucAddr_Type)
功能描述：获取通信地址
输入参数：pV_ucComm_Address保存通信地址缓存首地址，缓存最小为通信地址长度相等
		V_ucAddr_Type为地址类型：0x00单播地址，0x10通配地址，0x20组地址，0x30广播地址
输出参数：*pV_ucComm_Address通信地址
返回参数：无
功能说明：
调用机制：在通信解析进行通信地址判断的时候，快速获取通信地址用
*********************************************************************************/
void InF_Get_Comm_Address(uchar8 *pV_ucComm_Address,uchar8 V_ucAddr_Type)
{
	uchar8 i;

//	if(V_ucAddr_Type == 0x80)	/*组播，数据层目前没有组播地址，暂时不做处理*/
//	{
//		for(i=0;i<CLComm_Address;i++)
//		{
//			pV_ucComm_Address[i] = GV_MulticastAddr[i];
//		}
//	}
//	else
	if(V_ucAddr_Type == 0xC0)	/*广播*/
	{
		for(i=0;i<CLComm_Address;i++)
		{
			pV_ucComm_Address[i] = 0xAA;
		}
	}
	else
	{
		for(i=0;i<CLComm_Address;i++)
		{
			pV_ucComm_Address[i] = GV_Comm_Address[i];
		}
	}
}
/*********************************************************************************
函数原型：void InF_Check_Comm_Address(void)
功能描述：校验RAM中的通信地址是否正确
输入参数：
输出参数：无
返回参数：
功能说明：
调用机制：在通信定时任务中定时调用
*********************************************************************************/
void InF_Check_Comm_Address(void)
{
	ushort16 V_usLen = CLComm_Address, V_usDataEncode;
	uchar8 V_ucDataTemp[8] = {0};

//	if(V_ucAddr_Type == 0x80)	//组播，数据层目前没有组播地址，暂时不做处理
//	{
//		if(PF_Check_CRC(GV_MulticastAddr,CLComm_Address+2) != C_OK)
//		{
//			InF_Read_Data(CMulticastAddr,GV_MulticastAddr,&V_ucLen);
//		}
//	}
//	else
	{
		if(PF_Check_CRC(GV_Comm_Address, (CLComm_Address + C_CRCLen2) ) != C_OK)
		{
			InF_Read_Data(CComm_Address, GV_Comm_Address, &V_usLen, &V_usDataEncode);
		}
		else if(PF_Campare_Data(V_ucDataTemp, GV_Comm_Address, (CLComm_Address + C_CRCLen2) ) == C_OK)
		{
			memset(GV_Comm_Address, 0xFF, (CLComm_Address + C_CRCLen2) );		/*通信地址及CRC为全0，则重新从EE读取通信地址*/
			InF_Read_Data(CComm_Address, GV_Comm_Address, &V_usLen, &V_usDataEncode);
		}
	}
}
/**************复旦微RTC调校接口函数********************/
/*********************************************************************************
函数原型：uchar8 InF_ReadE2ThreeRTC(unsignedchar Page,unsignedchar Inpage,unsignedchar *P_Data,unsignedchar V_DataLen)
功能描述：读E2三处数据,内部判断CRC
输入参数：unsignedchar Page，unsignedchar Inpage：对应复旦微读E2命令，地址转换；
		uchar8 V_DataLen：读数据长度
		uchar8 *P_Data：读数据缓存(不包括CRC)
输出参数：无
返回参数：C_OK、C_IICError、C_CRCError、C_CrcErr_DataZero；
功能说明：
调用机制：
备     注：读数据不正确，也返回所读数据
*********************************************************************************/
uchar8 InF_ReadE2ThreeRTC(ushort16 Page ,ushort16 Inpage, unsigned char *P_Data, unsigned char V_DataLen )
{
	uchar8 V_Read_Flag;
	ushort16 V_E2Addr;

	V_Read_Flag=C_OK;
	if((Page==ee_temperature_page)&&(Inpage==ee_temperature_inpage))/*复旦微RTC调校固定地址判断,温度补偿系数存储*/
	{
		V_E2Addr=E2Addr_temperatureAddr;
	}
	else
	{
		if((Page==ee_ptatvalue_page)&&(Inpage==ee_ptatvalue_inpage))/*常温查表,ADC*/
		{
			V_E2Addr=E2Addr_ptatvalueAddr;
		}
		else
		{
			if((Page==ee_ptatvalue_lt_page)&&(Inpage==ee_ptatvalue_lt_inpage))/*低温查表,ADC*/
			{
				V_E2Addr=E2Addr_ptatvalue_ltAddr;
			}
			else
			{
				if((Page==ee_ptatvalue_ht_page)&&(Inpage==ee_ptatvalue_ht_inpage))/*高温查表,ADC*/
				{
					V_E2Addr=E2Addr_ptatvalue_htAddr;
				}
				else
				{
					if((Page==ee_trimvalue_page)&&(Inpage==ee_trimvalue_inpage))/*常温查表,补偿值*/
					{
						V_E2Addr=E2Addr_trimvalueAddr;
					}
					else
					{
						if((Page==ee_trimvalue_lt_page)&&(Inpage==ee_trimvalue_lt_inpage))/*低温查表,补偿值*/
						{
							V_E2Addr=E2Addr_trimvalue_ltAddr;
						}
						else
						{
							if((Page==ee_trimvalue_ht_page)&&(Inpage==ee_trimvalue_ht_inpage))/*高温查表,补偿值*/
							{
								V_E2Addr=E2Addr_trimvalue_htAddr;
							}
							else
							{
								if((Page==ee_rtcadj_time_page)&&(Inpage==ee_rtcadjtime_inpage))/*写常温顶点调校值时时间记录页地址(始终不清)*/
								{
									V_E2Addr=E2Addr_rtcadj_timeAddr;
								}
								else
								{
									V_Read_Flag=C_Error;
								}
							}
						}
					}
				}
			}
		}
	}

	if (V_Read_Flag!=C_Error)
	{
		V_Read_Flag=SF_ReadE2Three(V_E2Addr,V_DataLen,P_Data);
	}

	return V_Read_Flag;
}

uchar8 Verify_para(unsigned char Page ,unsigned char Inpage, unsigned char *Buf, unsigned char Len )/*一托二数据校验函数*/
{
	if( PF_Check_CRC( Buf, (Len + C_CRCLen2) ) == C_OK ) return 0;	/*ram参数crc正确*/

	if( InF_ReadE2ThreeRTC( Page, Inpage, Buf, Len ) == C_OK )
	{
		return 0;/*已经从数据ee主恢复*/
	}
	else
	{
		return 1;
	}
}

/*********************************************************************************
函数原型：uchar8 InF_WriteE2ThreeRTC(unsigned int Page,uint08 inpage,uint08 *Buf,uint08 Len)
功能描述：写E2三处数据
输入参数：unsigned char Page，unsigned char Inpage：对应复旦微读E2命令，地址转换；
		uchar8 V_DataLen：要写入数据长度
		uchar8 *P_Data：要写入数据缓存
输出参数：无
返回参数：C_OK、C_SafeFlagError、C_IICError；
功能说明：
调用机制：
备     注：
***********************************************************************************/
uchar8 InF_WriteE2ThreeRTC(ushort16 Page, ushort16 Inpage, uchar8 *P_Data, uchar8 V_DataLen )
{
	uchar8 V_Read_Flag;
	ushort16 V_E2Addr;

	V_Read_Flag=C_OK;
	if((Page==ee_temperature_page)&&(Inpage==ee_temperature_inpage))/*复旦微RTC调校固定地址判断,温度补偿系数存储*/
	{
		V_E2Addr=E2Addr_temperatureAddr;
	}
	else
	{
		if((Page==ee_ptatvalue_page)&&(Inpage==ee_ptatvalue_inpage))/*常温查表,ADC*/
		{
			V_E2Addr=E2Addr_ptatvalueAddr;
		}
		else
		{
			if((Page==ee_ptatvalue_lt_page)&&(Inpage==ee_ptatvalue_lt_inpage))/*低温查表,ADC*/
			{
				V_E2Addr=E2Addr_ptatvalue_ltAddr;
			}
			else
			{
				if((Page==ee_ptatvalue_ht_page)&&(Inpage==ee_ptatvalue_ht_inpage))/*高温查表,ADC*/
				{
					V_E2Addr=E2Addr_ptatvalue_htAddr;
				}
				else
				{
					if((Page==ee_trimvalue_page)&&(Inpage==ee_trimvalue_inpage))/*常温查表,补偿值*/
					{
						V_E2Addr=E2Addr_trimvalueAddr;
					}
					else
					{
						if((Page==ee_trimvalue_lt_page)&&(Inpage==ee_trimvalue_lt_inpage))/*低温查表,补偿值*/
						{
							V_E2Addr=E2Addr_trimvalue_ltAddr;
						}
						else
						{
							if((Page==ee_trimvalue_ht_page)&&(Inpage==ee_trimvalue_ht_inpage))/*高温查表,补偿值*/
							{
								V_E2Addr=E2Addr_trimvalue_htAddr;
							}
							else
							{
								if((Page==ee_rtcadj_time_page)&&(Inpage==ee_rtcadjtime_inpage))/*写常温顶点调校值时时间记录页地址(始终不清)*/
								{
									V_E2Addr=E2Addr_rtcadj_timeAddr;
								}
								else
								{
									V_Read_Flag=C_Error;
								}
							}
						}
					}
				}
			}
		}
	}

	if (V_Read_Flag!=C_Error)
	{
		GV_D_SafeFlag|=C_W_SafeFlag_1; /*置安全标志*/
		V_Read_Flag=SF_WR_E23_Data(V_E2Addr,V_DataLen,P_Data);
	}

	return V_Read_Flag;
}

/****************************************************************************
*函数原型 	SF_EraseCodeFlash_Sector
*函数功能	擦除codeflash的一个扇区
*输入参数	V_ulAddInSector待擦除扇区首地址
*输出参数 	无
*返回参数	无
*全局变量
*函数备注	这里不再判定地址、长度等的合法性，在调用该函数前已经进行了合法性判定
****************************************************************************/
void SF_EraseCodeFlash_Sector(ulong32 V_ulAddInSector)
{
	InF_Enable_Flash_CLK();
	FLASH_Erase_Sector(V_ulAddInSector);	/*擦除地址所在的扇区，共512字节*/
	InF_Disable_Flash_CLK();				/*Flash擦写控制器时钟使能，用完就关*/
}

/****************************************************************************
*函数原型 	SF_WriteCodeFlash
*函数功能	写数据到codeflash
*输入参数	V_CodeFlashAdd待写入codeflash地址，pV_ucDataIn待写入数据缓存物理地址的最低字节
*			V_usDataInLen需要写入数据长度
*输出参数 	无
*返回参数	无
*全局变量
*函数备注	这里不再判定地址、长度等的合法性，在调用该函数前已经进行了合法性判定
****************************************************************************/
void SF_WriteCodeFlash(ulong32 V_ulCodeFlashAdd, uchar8 *pV_ucDataIn, ushort16 V_usDataInLen)
{
	InF_Enable_Flash_CLK();
	FLASH_Prog_ByteString(V_ulCodeFlashAdd, pV_ucDataIn, V_usDataInLen);	/*连续写数据到codeflash*/
	InF_Disable_Flash_CLK();												/*Flash擦写控制器时钟使能，用完就关*/
}
#if 0
/****************************************************************************
*函数原型 	SF_EraseCodeFlash_Block
*函数功能	擦除codeflash的一个block
*输入参数	V_ulAddInBlock待擦除块首地址
*输出参数 	无
*返回参数	无
*全局变量
*函数备注	这里不再判定地址、长度等的合法性，在调用该函数前已经进行了合法性判定
****************************************************************************/
void SF_EraseCodeFlash_Block(ulong32 V_ulAddInBlock)
{
	InF_Enable_Flash_CLK();
	FLASH_Erase_Block(V_ulAddInBlock);	/*擦除地址所在的扇区，共512*16字节*/
	InF_Disable_Flash_CLK();			/*Flash擦写控制器时钟使能，用完就关*/
}
#endif
/****************************************************************************
*函数原型 	SF_Write_UpdataFlag
*函数功能	写升级标志到codeflash
*输入参数	pV_ucData为升级标志缓存数据缓存首地址，V_usLength为数据长度
*输出参数 	无
*返回参数	无
*全局变量
*函数备注	这里不再判定地址、长度等的合法性，在调用该函数前已经进行了合法性判定
****************************************************************************/
uchar8 SF_Write_UpdataFlag(uchar8 * pV_ucData, ushort16 V_usLength)
{
	uchar8 V_ucReturn = C_Error;
	uchar8 V_ucSafedArea_Data[C_SafedArea_Size];
	ushort16 V_usCRC_C = 0;
	ulong32 V_ulSafeArea_Addr;

	V_ulSafeArea_Addr = C_SafedArea_StardAddr;

	memcpy(V_ucSafedArea_Data, (uchar8 *)V_ulSafeArea_Addr, C_SafedArea_Size);		/*首先保存codeflash数据到临时缓存*/

	memcpy(&V_ucSafedArea_Data[C_EnterBootFlag_Offset], pV_ucData, V_usLength);		/*更新升级标志到临时缓存*/

	V_usCRC_C = PF_Cal_CRC_698(&V_ucSafedArea_Data[C_EnterBootFlag_Offset], V_usLength);		/*CRC16*/
	PF_Ushort16ToBuffer2(&V_ucSafedArea_Data[C_EnterBootFlag_Offset + V_usLength], &V_usCRC_C);

	if(PF_Campare_Data_698(V_ucSafedArea_Data, (uchar8 *)V_ulSafeArea_Addr, C_EnterBootFlag_Offset) != C_Equal)		/**/
	{
		memcpy(V_ucSafedArea_Data, (uchar8 *)V_ulSafeArea_Addr, C_EnterBootFlag_Offset);
	}

	if(PF_Campare_Data_698(&V_ucSafedArea_Data[C_EnterBootFlag_Offset + V_usLength + 2],
		( (uchar8 *)(V_ulSafeArea_Addr + C_EnterBootFlag_Offset + V_usLength + 2) ),
		(C_SafedArea_Size - (C_EnterBootFlag_Offset + V_usLength + 2) ) ) != C_Equal)
	{
		memcpy(&V_ucSafedArea_Data[C_EnterBootFlag_Offset + V_usLength + 2],
		( (uchar8 *)V_ulSafeArea_Addr + C_EnterBootFlag_Offset + V_usLength + 2),
		(C_SafedArea_Size - (C_EnterBootFlag_Offset + V_usLength + 2) ) );
	}

	/******************擦除保护区，同时写入新的数据**********************/
	if( GV_D_SafeFlag == C_W_SafeFlag)
	{
		SF_EraseCodeFlash_Sector(V_ulSafeArea_Addr);
		SF_WriteCodeFlash(V_ulSafeArea_Addr, V_ucSafedArea_Data, C_SafedArea_Size);
	}
	if(PF_Campare_Data_698(V_ucSafedArea_Data, (uchar8 *)V_ulSafeArea_Addr, (ushort16)C_SafedArea_Size) == C_Equal)		/*比对写入前后数据是否一致*/
	{
		V_ucReturn = C_OK;
	}

	return V_ucReturn;
}

const uchar8 C_EnterBootloader_Flag[8] = {0x68, 0x86, 0x9A, 0xDB, 0x00, 0x00, 0x00, 0x00};	/*固定进入升级复位标志*/
/****************************************************************************
*函数原型 	SF_Deal_FF86
*函数功能	处理自扩对象
*输入参数	V_Data_Id为OAD，P_Data为数据缓存首地址，V_Data_Length为数据长度
*输出参数 	无
*返回参数	无
*全局变量
*函数备注	这里不再判定地址、长度等的合法性，在调用该函数前已经进行了合法性判定
****************************************************************************/
uchar8 SF_Deal_FF86(ulong32 V_Data_Id,uchar8 * P_Data,ushort16 V_Data_Length)
{
	uchar8 V_ucReturn = C_Error, V_ucActionNO = 0;
	uchar8 V_ucDataTemp[C_3DES_DataLen + C_CRCLen2],i;

	if(V_Data_Length == C_3DES_DataLen)
	{
		V_ucActionNO = (uchar8)(V_Data_Id >> 8);

		for(i = 0; i < C_3DES_DataLen; i++)									/*将数据颠倒一下，在通信中进行统一处理时把高低字节进行了颠倒*/
		{
			V_ucDataTemp[i] = P_Data[C_3DES_DataLen - i - 1];
		}

		PF_3DES_Decode(V_ucDataTemp, V_ucDataTemp, (uchar8 *)C_3DES_Key1, (uchar8 *)C_3DES_Key2, (uchar8 *)C_3DES_Key3);	/*解密数据*/

		if(V_ucActionNO == 128)												/*判定认证是否正确*/
		{
			if(PF_Campare_Data(V_ucDataTemp, (uchar8 *)C_3DES_FixedData, C_3DES_DataLen) == C_Equal)
			{
				V_ucReturn = SF_Deal_UpdataFlag( (uchar8)C_Enter_UpdataFlag, V_ucDataTemp, V_Data_Length);	/*更新升级流程状态字*/
			}
			else
			{
				SF_Deal_UpdataFlag( (uchar8)C_Updata_Init, V_ucDataTemp, V_Data_Length);					/*出错，初始化升级流程状态字*/
			}
		}
		else if(V_ucActionNO == 129)										/*写启动升级标志到codeflash*/
		{
			GV_D_SafeFlag |= C_W_SafeFlag_2;
			V_ucReturn = SF_Deal_UpdataFlag( (uchar8)C_WriteFlag_OK, V_ucDataTemp, V_Data_Length);		/*更新升级流程状态字*/
		}
		else if(V_ucActionNO == 130)										/*判定进入升级标志是否正确*/
		{
			GV_D_SafeFlag |= C_W_SafeFlag_2;
			if(PF_Campare_Data(V_ucDataTemp, (uchar8 *)C_EnterBootloader_Flag, C_3DES_DataLen) == C_Equal)
			{
				V_ucReturn = SF_Deal_UpdataFlag( (uchar8)C_ResetFlag_OK, V_ucDataTemp, V_Data_Length);
			}
			else
			{
				SF_Deal_UpdataFlag( (uchar8)C_Updata_Init, V_ucDataTemp, V_Data_Length);					/*出错，初始化升级流程状态字*/
			}
		}
		else
		{
			;
		}
	}
	else
	{
		SF_Deal_UpdataFlag( (uchar8)C_Updata_Init, V_ucDataTemp, V_Data_Length);							/*出错，初始化升级流程状态字*/
		V_ucReturn = C_DataLenError;
	}
	GV_D_SafeFlag = 0;
	return V_ucReturn;
}


/****************************************************************************
*函数原型 	SF_Deal_UpdataFlag
*函数功能	处理升级流程状态字
*输入参数	V_ucOperationFlag: C_Clear_Status清标志，C_Start_UpdataMode进入升级模式，
*			C_Version_OK版本正确
*输出参数 	无
*返回参数	C_OK表示CRC正确
*			C_Error表示CRC不对，这种情况下不进行应答，做非法帧处理，直接复位串口
*全局变量
*函数备注：如果校验CRC出错，则直接将标志清零
****************************************************************************/
uchar8 SF_Deal_UpdataFlag(uchar8 V_ucOperationFlag, uchar8 *pV_ucData, ushort16 V_usDataIn_Len)
{
	uchar8 V_ucReturn = C_CRCError;
	ushort16 V_usCRC16_C, V_usCRC16_F;
	ulong32 V_ulControlFlag = 0;

	V_usCRC16_C = PF_Cal_CRC_698(&SStr_UpdataFlag.ControlFlag[0], (C_Str_UpdataFlag_Len - C_CRCLen2) );	/*CRC16*/
	V_usCRC16_F = PF_Buffer2ToLong16_698(&SStr_UpdataFlag.ucCRC[0]);							/*计算CRC*/
	if(V_usCRC16_C == V_usCRC16_F)
	{
		switch(V_ucOperationFlag)
		{
			case C_Enter_UpdataFlag:
			{
				V_ulControlFlag = C_UpdataFlag_OKFlag;											/*取标志*/
				PF_Ulong32ToBuffer4_698(&SStr_UpdataFlag.ControlFlag[0], &V_ulControlFlag, 4);
				SStr_UpdataFlag.FlowFlag = C_Enter_UpdataFlag;
				SStr_UpdataFlag.OverTimer = C_OverTimer_10s;
				V_ucReturn = C_OK;
				break;
			}
			case C_WriteFlag_OK:
			{
				GV_D_SafeFlag |= C_W_SafeFlag_3;
				V_ulControlFlag = PF_Buffer4ToUlong32_698(&SStr_UpdataFlag.ControlFlag[0]);		/*取标志*/
				if( (V_ulControlFlag == C_UpdataFlag_OKFlag) && (SStr_UpdataFlag.FlowFlag == C_Enter_UpdataFlag) )
				{
					V_ucReturn = SF_Write_UpdataFlag(pV_ucData, V_usDataIn_Len);				/*更新codeflash中的升级标志*/
					if(V_ucReturn == C_OK)
					{
						SStr_UpdataFlag.FlowFlag = C_WriteFlag_OK;
						SStr_UpdataFlag.OverTimer = C_OverTimer_10s;
					}
					else
					{
						memset(&SStr_UpdataFlag.ControlFlag[0], 0, 4);
						SStr_UpdataFlag.FlowFlag = C_Updata_Init;
						SStr_UpdataFlag.OverTimer = 0;
						V_ucReturn = C_Error;													/*写标志失败*/
					}
				}
				else
				{
					memset(&SStr_UpdataFlag.ControlFlag[0], 0, 4);
					SStr_UpdataFlag.FlowFlag = C_Updata_Init;
					SStr_UpdataFlag.OverTimer = 0;
					V_ucReturn = C_Error;						/*未进入升级模式*/
				}
				break;
			}
			case C_ResetFlag_OK:
			{
				GV_D_SafeFlag |= C_W_SafeFlag_3;
				V_ulControlFlag = PF_Buffer4ToUlong32_698(&SStr_UpdataFlag.ControlFlag[0]);		/*取标志*/
				if( (V_ulControlFlag == C_UpdataFlag_OKFlag) && (SStr_UpdataFlag.FlowFlag == C_WriteFlag_OK)
					&&(GV_D_SafeFlag == C_W_SafeFlag) )			/*安全标志判定*/
				{
					SStr_UpdataFlag.FlowFlag = C_ResetFlag_OK;
					SStr_UpdataFlag.OverTimer = C_OverTimer_2s;
					V_ucReturn = C_OK;
				}
				else
				{
					memset(&SStr_UpdataFlag.ControlFlag[0], 0, 4);
					SStr_UpdataFlag.FlowFlag = C_Updata_Init;
					SStr_UpdataFlag.OverTimer = 0;
					V_ucReturn = C_Error;						/*未进入升级模式*/
				}
				break;
			}
			case C_TimerDecrease:
			{
				V_ulControlFlag = PF_Buffer4ToUlong32_698(&SStr_UpdataFlag.ControlFlag[0]);		/*取标志*/
				if(V_ulControlFlag == C_UpdataFlag_OKFlag)
				{
					if(SStr_UpdataFlag.OverTimer > 0)
					{
						SStr_UpdataFlag.OverTimer--;
						if(SStr_UpdataFlag.OverTimer == 0)
						{
							if(SStr_UpdataFlag.FlowFlag == C_ResetFlag_OK)
							{
								InF_Reset_MCU();					/*立即复位*/
							}
							else									/*超过定时器时间则将状态恢复至初始状态*/
							{
								memset(&SStr_UpdataFlag.ControlFlag[0], 0, 4);
								SStr_UpdataFlag.FlowFlag = C_Updata_Init;
								SStr_UpdataFlag.OverTimer = 0;
								V_ucReturn = C_OK;
							}
						}
					}
				}
				else
				{
					memset(&SStr_UpdataFlag.ControlFlag[0], 0, 4);
					SStr_UpdataFlag.FlowFlag = C_Updata_Init;
					SStr_UpdataFlag.OverTimer = 0;
					V_ucReturn = C_Error;						/*未进入升级模式*/
				}
				break;
			}
			default:	/*清零*/
			{
				memset(&SStr_UpdataFlag.ControlFlag[0], 0, 4);
				SStr_UpdataFlag.FlowFlag = C_Updata_Init;
				SStr_UpdataFlag.OverTimer = 0;
				V_ucReturn = C_OK;
				break;
			}
		}
	}

	/************************************************/
	V_usCRC16_C = PF_Cal_CRC_698(&SStr_UpdataFlag.ControlFlag[0], (C_Str_UpdataFlag_Len - C_CRCLen2) );		/*CRC16*/
	PF_Ushort16ToBuffer2_698(&SStr_UpdataFlag.ucCRC[0], &V_usCRC16_C);

	return V_ucReturn;
}

/****************************************************************************
*函数原型 	DataProcess_External_Message
*函数功能	处理升级定时任务，每秒钟调用一次
*输入参数	P_Msg_Parameter指向消息参数结构体地址
*			消息号：C_Msg_DataProcess_External
*输出参数 	无
*返回参数	无
*全局变量
*函数备注：	该函数采用基于5ms定时的1000ms，而不是RTC的秒变化消息
****************************************************************************/
void  DataProcess_External_Message(Str_Msg_Parameter * P_Msg_Parameter)
{
	uchar8 V_ucTemp[2];

	memcpy(V_ucTemp, (uchar8 *)C_Software_Featurcode, 2);
	SF_Deal_UpdataFlag(C_TimerDecrease, V_ucTemp, 0);
}

/**********************************************************************************
函数原型： uchar8 InF_GetData_ObjectManage(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf,
					ushort16 *pV_usDataLen, uchar8 *pV_ucDataEncode)
功能描述： 该函数为对象管理层提供的读取普通属性的接口函数

输入参数：其中V_ulOAD为对象管理层支持的OAD
			目前包括协议要求支持OAD及自扩OAD，自扩OAD按照最新的扩展规则，最高字节为FF
			pV_ucDataBuf为待读取数据存放缓存首地址
			*pV_usDataLen输入为缓存最大长度，当读取数据长度超给定缓存长度时返回错误
			pV_ucDataEncode用于存放该属性对应编码类型的缓存首地址，对于普通属性通常只有1个编码

输出参数： 	*pV_ucDataBuf为读取的缓存数据，该缓存数据即使应答错误也可能被改掉（为了减少临时变量
				数据层直接借用了输入缓存）
			*pV_usDataLen为实际读取数据长度，读取出错时该长度数据层赋值0
			*pV_ucDataEncode为该属性对应的内部编码，每个编码直接反应其对应的698编码方式

返回参数： 	返回C_OK表示数据读取成功，此时可以直接用*pV_ucDataBuf缓存中对应*pV_usDataLen字节
				长度的数据
			返回其他表示具体错误类型，缓存中数据不可用

调用机制：	模块读取其他模块管理数据时调用，若读取模块内部管理数据直接调用数据层数据接口
备    注：
**********************************************************************************/
uchar8 InF_GetData_ObjectManage(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, ushort16 *pV_usDataEncode)
{
	uchar8 V_ucReturn = C_Error;

	if( ( (V_ulOAD & 0xFF000000) == 0x00000000)				/*当前电能*/
		|| (V_ulOAD == CChargeBal_Hex_Cent)					/*剩余金额*/
		|| (V_ulOAD == COverDraft_Hex_Cent)					/*透支金额*/
		|| (V_ulOAD == CM_Com_Ac_Tol_En_0)					/*月度用电量*/
		|| (V_ulOAD == CY_Com_Ac_Tol_En_0)					/*结算用电量*/
		)
	{
		V_ucReturn = InF_Get_EnergyModule(V_ulOAD, pV_ucDataBuf, pV_usDataLen, pV_usDataEncode);
	}
	else if( (V_ulOAD & 0xFF000000) == 0x10000000)
	{
		V_ucReturn = InF_Get_DemandModule(V_ulOAD, pV_ucDataBuf, pV_usDataLen, pV_usDataEncode);
	}
	else if( ( (V_ulOAD & 0xFFFF0000) == 0x20010000 )		/*电流*/
			|| ( (V_ulOAD & 0xFFFF0000) == 0x20070000 )		/*一分钟平均有功功率*/
			|| ( (V_ulOAD & 0xFFFF0000) == 0x20080000 )		/*一分钟平均无功功率*/
			)
	{
		V_ucReturn = InF_Get_MeterICModule(V_ulOAD, pV_ucDataBuf, pV_usDataLen, pV_usDataEncode);
	}
	else if( ( (V_ulOAD & 0xFFFF0000) == 0xF1000000)		/*ESAM接口类*/
			|| (V_ulOAD == CPurchasePowTime)				/*购电次数*/
			)
	{
		V_ucReturn = InF_Get_SafeModule(V_ulOAD, pV_ucDataBuf, pV_usDataLen, pV_usDataEncode);
	}
	else if( ( (V_ulOAD & 0xFFFF0000) == 0xF2050000 )
			|| ( (V_ulOAD & 0xFFFF0000) == 0x80000000 )
			|| ( (V_ulOAD & 0xFFFF0000) == 0x80010000 )
			)
	{
		V_ucReturn = InF_Get_RelayModule(V_ulOAD, pV_ucDataBuf, pV_usDataLen, pV_usDataEncode);
	}
	else
	{
		V_ucReturn = InF_Read_Data(V_ulOAD, pV_ucDataBuf, pV_usDataLen, pV_usDataEncode);
	}

	return V_ucReturn;
}

/**********************************************************************************
函数原型： uchar8 InF_SetData_ObjectManage(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf,
					ushort16 V_usDataLen, uchar8 *pV_ucDataEncode)
功能描述：写数据层接口函数
输入参数：
		uchar8 V_usMsg_Num:消息号，用于判断是否有写权限；
		ulong32 V_ulOAD：数据标识码；
		uchar8 *pV_ucDataBuf：数据所放缓存；
		ushort16 V_usDataLen：所写数据长度；
		uchar8 V_W_Safe_Flag：宏定义，当写安全标志；

输出参数：无

返回参数：C_OK、C_IICError、C_SPIError、C_DataLenError、C_IDError、C_SafeFlagError、C_NoAccess；

调用机制：

备     注：写数据层时调用，注意安全标志
**********************************************************************************/
uchar8 InF_SetData_ObjectManage(uchar8 V_usMsg_Num, ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 V_usDataLen, uchar8 V_W_Safe_Flag)
{
	uchar8 V_ucReturn = C_Error;

	V_ucReturn = InF_Write_Data(V_usMsg_Num, V_ulOAD, pV_ucDataBuf, V_usDataLen, V_W_Safe_Flag);

	return V_ucReturn;
}

/**********************************************************************************
函数原型： InF_GetData_Record_DataBase(Str_Read_T *pStr_Read, uchar8 *pV_ucDataBuf,
					ushort16 *pV_usDataLen, Str_SuppInfo *pStr_SuppInfo)

功能描述： 该函数为数据层提供的读取记录型数据的接口函数，支持方法1、2、9读取，具体读取方式
			根据入口参数中pStr_Read->pV_ucRST输入方法决定

输入参数：其中pStr_Read为记录型数据参数结构体地址，其他包括读取记录OAD、关联OAD及读取方法
			pV_ucDataBuf为待读取数据存放缓存首地址
			*pV_usDataLen输入为缓存最大长度，当读取数据长度超给定缓存长度时返回错误
			pV_ucSupplementaryInformation为返回附加数据信息缓存首地址
			*pV_usSIDataLen输入为附加数据最大缓存

输出参数： 	*pV_ucDataBuf为读取的缓存数据，该缓存数据即使应答错误也可能被改掉（为了减少临时变量
				数据层直接借用了输入缓存）
			*pV_usDataLen为实际读取数据长度，读取出错时该长度数据层赋值0
			*pV_ucDataEncode为该属性对应的内部编码，每个编码直接反应其对应的698编码方式

返回参数： 	返回C_OK表示数据读取成功，此时可以直接用*pV_ucDataBuf缓存中对应*pV_usDataLen字节
				长度的数据
			返回其他表示具体错误类型，缓存中数据不可用

调用机制：	模块读取其他模块管理数据时调用，若读取模块内部管理数据直接调用数据层数据接口
备    注：
**********************************************************************************/
uchar8 InF_GetData_Record_DataBase(Str_Read_T *pStr_Read, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, Str_SuppInfo *pStr_SuppInfo)
{
	uchar8 V_ucReturn = C_Error, V_timeFlash, V_NextSign, V_ucMode = C_698Mode;
	ushort16 V_usBlockNum = 1, V_usIntervalTime = 0;
	ulong32 V_ulOAD_RST;

	if( (pStr_Read->pV_ucRST[C_RST_Method_O] == 1)
		|| (pStr_Read->pV_ucRST[C_RST_Method_O] == 2) )
	{
		PF_Buffer4ToUlong32( &pStr_Read->pV_ucRST[C_RST_OADOrNum_O], &V_ulOAD_RST, 4);
		if( ( (V_ulOAD_RST == CFreeTime ) && ( (pStr_Read->pV_ulROAD[0] & 0xFF000000) == 0x50000000) )
			|| ( (V_ulOAD_RST == CEventHPTime ) && ( (pStr_Read->pV_ulROAD[0] & 0xFF000000) == 0x30000000) ) )
		{
			V_timeFlash = 0x00;
		}
		else if( V_ulOAD_RST == CEventEndTime )
		{
			V_timeFlash = 0xAA;
		}
		else
		{
			return V_ucReturn;
		}
		if(pStr_Read->pV_ucRST[C_RST_Method_O] == 2)		/*取读取间隔*/
		{
			PF_Buffer2ToUshort16(&pStr_Read->pV_ucRST[C_RST_TIInter_O], &V_usIntervalTime);
			V_usBlockNum = 0;
		}
	}
	else if(pStr_Read->pV_ucRST[C_RST_Method_O] == 9)
	{
		pStr_Read->pV_ulROAD[0] = ( (pStr_Read->pV_ulROAD[0]&0xFFFFFF00) | pStr_Read->pV_ucRST[C_RST_OADOrNum_O]);		/*读取上N此记录*/
	}
	else
	{
		return V_ucReturn;
	}
	if( (pStr_Read->pV_ulROAD[0] & 0xFF000000) == 0x30000000)			/*读取事件记录*/
	{
		V_ucReturn = InF_ReadEventData(pStr_Read->pV_ulROAD, &pStr_Read->pV_ucRST[C_RST_Timer1_O], pV_ucDataBuf, &V_NextSign,  pV_usDataLen, V_timeFlash);
	}
	else if( (pStr_Read->pV_ulROAD[0] & 0xFF000000) == 0x50000000)		/*读取冻结记录*/
	{
		V_ucReturn = InF_ReadFreezeData(pStr_Read->pV_ulROAD, &pStr_Read->pV_ucRST[C_RST_Timer1_O], pV_ucDataBuf, &V_usBlockNum, pV_usDataLen, V_usIntervalTime, (uchar8 *)pStr_SuppInfo->pV_usEncode, V_ucMode);
	}
	else
	{
		V_ucReturn = C_ObjectUndefine_DAR;
	}

	if(V_ucReturn == C_OK)
	{
		if( (pStr_Read->pV_ulROAD[0] & 0xFF000000) == 0x30000000)
		{
			pStr_SuppInfo->V_ucNxtFrame = ( (V_NextSign >> 4) & 0x03);		/*后续帧标志*/
			pStr_SuppInfo->V_ucFrameNum = ( V_NextSign & 0x0F);				/*记录条数*/
			pStr_SuppInfo->V_ucLastFlag = ( (V_NextSign >> 6) & 0x03);		/*是否包含最近一条*/
		}
		else
		{
			pStr_SuppInfo->V_ucNxtFrame = ( (uchar8)(V_usBlockNum  & 0x03) );		/*后续帧标志*/
			pStr_SuppInfo->V_ucFrameNum = ( (uchar8)(V_usBlockNum >> 2) );			/*记录条数*/
		}
	}
	return V_ucReturn;
}


/**********************************************************************************
函数原型： InF_GetData_Record(Str_Read_T *pStr_Read, uchar8 *pV_ucDataBuf,
					ushort16 *pV_usDataLen, Str_SuppInfo *pStr_SuppInfo)

功能描述： 该函数为数据层提供的读取记录型数据的接口函数，支持方法1、2、9读取，具体读取方式
			根据入口参数中pStr_Read->pV_ucRST输入方法决定

输入参数：其中pStr_Read为记录型数据参数结构体地址，其他包括读取记录OAD、关联OAD及读取方法
			pV_ucDataBuf为待读取数据存放缓存首地址
			*pV_usDataLen输入为缓存最大长度，当读取数据长度超给定缓存长度时返回错误
			pV_ucSupplementaryInformation为返回附加数据信息缓存首地址
			*pV_usSIDataLen输入为附加数据最大缓存

输出参数： 	*pV_ucDataBuf为读取的缓存数据，该缓存数据即使应答错误也可能被改掉（为了减少临时变量
				数据层直接借用了输入缓存）
			*pV_usDataLen为实际读取数据长度，读取出错时该长度数据层赋值0
			*pV_ucDataEncode为该属性对应的内部编码，每个编码直接反应其对应的698编码方式

返回参数： 	返回C_OK表示数据读取成功，此时可以直接用*pV_ucDataBuf缓存中对应*pV_usDataLen字节
				长度的数据
			返回其他表示具体错误类型，缓存中数据不可用

调用机制：	模块读取其他模块管理数据时调用，若读取模块内部管理数据直接调用数据层数据接口
备    注：
**********************************************************************************/
uchar8 InF_GetData_Record(Str_Read_T *pStr_Read, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, Str_SuppInfo *pStr_SuppInfo)
{
	uchar8 V_ucReturn;

	if( (pStr_Read->pV_ulROAD[0] & 0xFF000000) == 0x30000000)			/*读取事件记录*/
	{
		V_ucReturn = InF_Get_EventModule(pStr_Read, pV_ucDataBuf, pV_usDataLen, pStr_SuppInfo);
	}
	else if( (pStr_Read->pV_ulROAD[0] & 0xFF000000) == 0x50000000)		/*读取冻结记录*/
	{
		V_ucReturn = InF_GetData_Record_DataBase(pStr_Read, pV_ucDataBuf, pV_usDataLen, pStr_SuppInfo);
	}
	else
	{
		V_ucReturn = C_ObjectUndefine_DAR;
	}

	return V_ucReturn;
}




