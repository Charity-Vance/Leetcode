/*******************************************************************************
Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     Card.c
Version:       V1
Author:        jiangzs
Date:          2014-3-31
Description:   卡处理文件
---------------------------------------------------------------------------------
History1:      第1次修改
内容1. Date:   20211021
   	   Author: lx
       Modification:
	   ---------------------------------------------------------------------------
内容2. Date:
   	   Author:
       Modification:
----------------------------------------------------------------------------------
History2:      第2次修改
内容1. Date:
   	   Author:
       Modification:
	   ---------------------------------------------------------------------------
内容2. Date:
   	   Author:
       Modification:
******************************************************************************/


#include    "Card.h"
#include    "Timer.h"



/*******************************************************************************
函数原型：uchar8	InF_Card_Message(Str_Msg_Parameter * pStr_Msg_Parameter)
功能描述：卡处理消息解析函数
输入参数：*pStr_Msg_Parameter:			消息结构体		
输出参数：无
返回参数：C_OK/C_Error
调用位置：
备    注：
*******************************************************************************/
uchar8	InF_Card_Message(Str_Msg_Parameter *pStr_Msg_Parameter)
{
	uchar8	*pV_ucParm;
	
	/*如果调度发过来是停电，那么直接退出，返回C_OK	*/
	if(pStr_Msg_Parameter->PowerFlag == C_PowerFalling)
	{
		return(C_OK);
	}
	
	/*判断消息处理的入口是否正确*/
	pV_ucParm = pStr_Msg_Parameter->Parameter;
	if(*pV_ucParm == Pt_CardFlag)
	{
		SV_IC_SafeFlag = 0;
		MF_Card_Message();
		return(C_OK);
	}
	else
	{
		SV_IC_SafeFlag = 0;
		return(C_Error);
	}
	
}


/*******************************************************************************
函数原型：void		MF_Card_Message(void)
功能描述：卡处理消息解析函数
输入参数：无
输出参数：无
返回参数：无
调用位置：
备    注：完成卡分类及处理；异常插卡事件记录；本函数完成安全规范附录A.1.2 a/b/h/i步骤
*******************************************************************************/
void	MF_Card_Message(void)
{
	StrCardParse	pStr_CardParse;	
	ushort16		V_usTemp16 = 0;
	
	pStr_CardParse.PreMoneyClock = 0;				/*默认购电前剩余金额不显示*/
	
	/*	InF_SwithPeripherals(C_TripLed,C_On);*/  /*test*/

	SV_IC_SafeFlag = SV_IC_SafeFlag | C_W_SafeFlag_1;
	/*判断是否为本地表。不为本地表，直接退出*/
	if(C_Meter_Type != C_L_SmartMeter)
	{
		SV_IC_SafeFlag =0;
		return;
	}	
	/*判断是否真正有卡*/
	if(InF_GetPeripheralStatus(C_CardStatus) != C_Valid)
	{
		SV_IC_SafeFlag =0;
		
		return;
	}
	/*对于异常插卡事件记录变量初始化*/
	MF_Init_IC_ErrEvent(&pStr_CardParse);

	/*MF_Card_SendMsgToDisp(C_HoardingSign,C_NotDisplay,CCDsp_Duration_Alway);	*/ /*首先取消，囤积显示，避免上次10s内，插卡囤积异常显示*/

	/*判断电源是否正常*/
	if (InF_JudgeVolage_Relay() == C_VoltageOk)				/*电压正常*/
	{
		/*不显示读卡中*/
		/*MF_Card_SendMsgToDisp(C_ReadCardSign,C_AlwaysDisplay,CCDsp_Duration_Alway);*/	/*显示读卡*/
		/*MF_Card_SendMsgToDisp(C_DoingSign,C_AlwaysDisplay,CCDsp_Duration_Alway);*/		/*显示中*/
		MF_Card_SendMsgToDisp(C_FailSign, C_NotDisplay, CCDsp_Duration_Alway);				/*不显示失败*/
		MF_Card_SendMsgToDisp(C_SuccessSign, C_NotDisplay, CCDsp_Duration_Alway);			/*不显示成功*/
		/*点亮背光60s，复旦微在判电压之前就执行。*/ 
        /*SF_ReadDispBuff(GV_ucDispArray); */                                         		/*读取液晶状态*/
        MF_Card_SendMsgToDisp(C_BackLED, C_AlwaysDisplay, CCDsp_Duration_60s);
		InF_OprateTimer(C_StartTimer, 10000);			/*启动10s定时，作为插卡过程中定时使用*/

		pStr_CardParse.IC_ErrEvent[CO_CE_ErrStatus] = MF_Card_Esam_Proc(&pStr_CardParse);
				
		/*卡片停活*/
		InF_Deactivation_7816_Card();

		MF_Card_SendICMsg();			/*插任意卡，都发布继电器合闸允许消息*/

	}
	else	/*电压过低*/
	{

		pStr_CardParse.IC_ErrEvent[CO_CE_ErrStatus] = C_IC_VLOW_ERR;
		MF_Card_SendICMsg();			/*低电压也发布插卡消息，方便电压恢复后合闸*/
	}
	
	/*异常插卡记录、液晶主屏显示*/	
	if(pStr_CardParse.IC_ErrEvent[CO_CE_ErrStatus] != C_OK)	/*卡处理过程有错误*/
	{
		MF_Write_IC_ErrEvent(&pStr_CardParse);				/*写异常插卡事件记录*/
		
		/*MF_Card_SendMsgToDisp(C_ReadCardSign, C_AlwaysDisplay, CCDsp_Duration_10s);*/	/*读卡10s*/
		/*MF_Card_SendMsgToDisp(C_DoingSign, C_NotDisplay, CCDsp_Duration_Alway);*/		/*取消中*/
		MF_Card_SendMsgToDisp(C_SuccessSign, C_NotDisplay, CCDsp_Duration_Alway);			/*取消成功*/
		MF_Card_SendMsgToDisp(C_FailSign, C_AlwaysDisplay, CCDsp_Duration_10s);			/*错误10s*/
		InF_BeeperOut(C_TwinkleDisplay, 750, 250);			/*蜂鸣器短响125ms间隔3次,总时间750，周期250*/
		MF_Card_LCDView(CType_IC_Err, &pStr_CardParse);		/*提示Err-XX*/
		V_usTemp16 = InF_OprateTimer(C_GetTimer, 0);
		/*将背光精确定时*/
		V_usTemp16 = CCDsp_Duration_60s - ( (10000 - V_usTemp16) / 1000);
		MF_Card_SendMsgToDisp(C_BackLED, C_AlwaysDisplay, V_usTemp16);
		InF_WriteCardStatus(C_CardStatusERR);
	}
	else	/*一切正常，显示购电后的剩余金额*/
	{
		/*MF_Card_SendMsgToDisp(C_ReadCardSign,C_AlwaysDisplay,CCDsp_Duration_10s);*/	/*读卡10s*/
		/*MF_Card_SendMsgToDisp(C_DoingSign,C_NotDisplay,CCDsp_Duration_Alway);*/		/*取消中*/
		MF_Card_SendMsgToDisp(C_FailSign, C_NotDisplay, CCDsp_Duration_Alway);		    /*取消失败*/
		MF_Card_SendMsgToDisp(C_SuccessSign, C_AlwaysDisplay, CCDsp_Duration_10s);		/*成功10s*/

		InF_BeeperOut(C_AlwaysDisplay, 650, 0);		/*蜂鸣器长响650ms*/
		if(pStr_CardParse.PreMoneyClock != 0)			/*购电前剩余金额显示时刻重新定时了，获取精确的2s定时*/
		{
			do
			{
				V_usTemp16 = InF_OprateTimer(C_GetTimer, 0);
				if( (pStr_CardParse.PreMoneyClock - V_usTemp16) >= 2000)
				{
					break;							/*购电前剩余金额显示延时2s到了*/
				}
			}while(V_usTemp16 != 0);
		}
		MF_Card_LCDView(CType_RemainMoney, &pStr_CardParse);
		/*将背光精确定时*/
		V_usTemp16 = CCDsp_Duration_60s - ( (10000 - V_usTemp16) / 1000);
		MF_Card_SendMsgToDisp(C_BackLED, C_AlwaysDisplay, V_usTemp16);
		InF_WriteCardStatus(C_CardStatusOK);
	}
	SV_IC_SafeFlag = 0;
	
	/*	InF_SwithPeripherals(C_TripLed, C_On);*/	/*test*/
}


/*******************************************************************************
函数原型：	uchar8		MF_Card_Esam_Proc(StrCardParse	*pStr_CardParse)
功能描述：	卡片处理
输入参数：	*pStr_CardParse				:卡处理通用结构体
输出参数：	*pStr_CardParse				:卡处理通用结构体
返回参数：	C_OK/插卡过程错误码，如C_IC_KER_ERR等定义
调用位置：
备    注：	本流程主要参考安全规范附录A.1.2-c/d/e/f/g步骤
			注意如果不是操作卡片或ESAM过程中发生错误，命令头和SW为全0(经测试，复旦微也这么做)
			复旦微在C_IC_ESAM_RDWR_ERR/C_IC_NOFX_ERR/C_IC_MAC_ERR/C_IC_NOIN_ERR/C_IC_EXAUTH_ERR
			这几种情况下记录错误命令头
*******************************************************************************/
uchar8		MF_Card_Esam_Proc(StrCardParse		*pStr_CardParse)
{
	uchar8	V_ucReturnData;

	/*首先对卡片进行复位*/
	if(InF_S_ColdRestCard(IC_CardNo) != C_OK)
	{
		return(C_IC_IC_RST_ERR);
	}
	
	/*其次对ESAM进行复位*/
	/*断开应用链接,冷复位ESAM*/
	V_ucReturnData = INF_RELEASE_Service_Deal_Card();
	if(V_ucReturnData != C_OK)
	{
		return(C_IC_ESAM_RST_ERR);
	}
	
	/*停止远程身份认证有效，进行远程编程记录编制。*/
	INF_StopCommProgState();
	
	/*选择卡3F00,DF01 --复旦微仅执行选择DF01*/
	V_ucReturnData = InF_S_SelectFile(C_Card, C_F_MF);
	if(V_ucReturnData != C_OK)
	{
		/*return(V_ReturnData);*/
		return(C_IC_IC_RST_ERR);	/*跑费控安全流程(用户卡攻击测试)修改*/
	}
	V_ucReturnData = InF_S_SelectFile(C_Card, C_F_MainDir);
	if(V_ucReturnData != C_OK)
	{
		/*return(V_ReturnData);*/
		return(C_IC_IC_RST_ERR);	/*跑费控安全流程(用户卡攻击测试)修改*/
	}

	#if 0
	/*选择ESAM3F00 --本步骤复旦微不执行*/
	V_ReturnData = InF_S_SelectFile(C_ESAM,C_F_MF);
	if(V_ReturnData != C_OK)
	{
		return(V_ReturnData);
	}
	#endif	

	/*test 防止出现err-35错误,卡返回FF68*/
	InF_Delay_us(1000);
	
	/*获取指令文件中卡片类型及有效数据长度*/
	V_ucReturnData = InF_SC_RDBinFileNoMac(C_Card, C_FC_INS, CO_INS_Start, 4, pStr_CardParse->IC_File);
	if(V_ucReturnData != C_OK)	/*错误*/
	{
		if(GV_7816CMD.SW1_2 == C_Security_ParameterError)	/*6B00，复旦微认为是无效卡片*/
		{
			return C_IC_NOFX_ERR;	/*未发行卡片*/
		}
		else	/*其他错误，认为是读写卡片失败*/
		{
			return C_IC_NOIN_ERR;	/*操作卡片通讯错误(读写卡片失败)*/
		}
	}
	else	/*正确。*/
	{
		pStr_CardParse->CardType = IC_INS_CMD;	/*保存卡片类型*/
		
		if(IC_INS_CMD == C_UserCardCommand) 	/*用户卡*/
		{
			InF_Card_DispDynamicSign();	/*显示----------*/
			V_ucReturnData = MF_UserCard_Esam_Proc(pStr_CardParse);
		}
		else if(IC_INS_CMD == C_PresetCardCommand)	/*参数预置卡*/
		{		
			InF_Card_DispDynamicSign();	/*显示----------*/
			V_ucReturnData = MF_PreSetCard_Esam_Proc(pStr_CardParse);
		}
		else	/*卡片类型错误*/
		{
			V_ucReturnData = C_IC_TYPE_ERR;
		}
		
		return(V_ucReturnData);
	}
}


/*******************************************************************************
函数原型：uchar8		MF_PreSetCard_Esam_Proc(StrCardParse	*pStr_CardParse)
功能描述：完成参数预置卡的处理
输入参数：*pStr_CardParse				:卡处理通用结构体
输出参数：*pStr_CardParse				:卡处理通用结构体
返回参数：C_OK/插卡过程错误码，如C_IC_KER_ERR等定义
调用位置：
备    注：主要参考安全规范附录A.1.3
*******************************************************************************/
uchar8		MF_PreSetCard_Esam_Proc(StrCardParse	*pStr_CardParse)
{
	uchar8		V_ucReturnData;
	ushort16	V_usTemp16;
	uchar8		V_ucbuf[10], V_ucFlag;
	
	/*参数预置卡要求所有密钥必须是公钥。
	A.1.3中要求复旦微也是在身份认证前判断*/
	if(InF_JudgeKeyStatus() != C_StateOfTestKey)	/*所有的全部为正式密钥*/
	{
		return(C_IC_KER_ERR);
	}

	/*身份认证*/
	V_ucReturnData = InF_SC_L_Auth(IC_CardNo);
	if( V_ucReturnData != C_OK)
	{
		return(V_ucReturnData);
	}

	SV_IC_SafeFlag = SV_IC_SafeFlag | C_W_SafeFlag_2;
	/*再读取指令文件并判断*/
	V_ucReturnData = InF_SC_RDBinFileNoMac(C_Card, C_FC_INS, 0, (CL_PresetCardCMD + 6), pStr_CardParse->IC_File);
	if(V_ucReturnData != C_OK)	/*读不出,前面判断过6B00，这里不判断了*/
	{
		return(V_ucReturnData);
	}

	if(InF_SC_Judge_CardFile(pStr_CardParse->IC_File) != C_OK)	/*卡片文件格式不对*/
	{
		return(C_IC_FORMAT_ERR);
	}

	/*保存参数更新标志。*/
	pStr_CardParse->UpdateFlag = IC_INS_UpdataPFlag;
	/*让ESAM产生Rand1-4，用于Mac计算*/
	V_ucReturnData = InF_SC_GenerateRandToCalMac(C_ESAM, C_Length_4);
	if(V_ucReturnData != C_OK)
	{
		return(V_ucReturnData);			/*这里实际上可不判。*/
	}

	/*读钱包文件中预置金额,698参数预制卡的钱包文件中没有购电次数*/
	V_ucReturnData = InF_SC_Get_MFile_Card(pStr_CardParse);
	if(V_ucReturnData != C_OK)
	{
		return(V_ucReturnData);	
	}

	#if 0
	if(pStr_CardParse->PPNum != 0)	/*参数预置卡中购电次数如果不为0，就报错!*/
	{
		return(C_IC_TIMES_ERR);
	}
	#endif

	if(pStr_CardParse->PPMoney > 99999999)	/*预置金额不能大于99999999分，但不判断超囤积*/
	{
		return(C_IC_OVERMAX_ERR);			/*实际不可能，这里为防止程序错乱。*/
	}
	
	/*充值并金额Mac验证*/
	V_usTemp16 = InF_S_InitMoney(C_Msg_Card, pStr_CardParse->IC_File);
	if(V_usTemp16 != C_OK)
	{
		if(V_usTemp16 == C_SERR_ESAM_VF)	/*复旦微这里没有Mac错误*/
		{
			return(C_IC_MAC_ERR);
		}
		else
		{
			return(C_IC_NOIN_ERR);
		}
	}

	/*钱包初始化成功，可以对电能表进行初始化操作(在参数更新完成后进行)*/
	SV_IC_SafeFlag = SV_IC_SafeFlag | C_W_SafeFlag_3;
	
    memset(V_ucbuf, 0, CL_UserCardNo);
	InF_Write_Data(C_Msg_Card, C_UserCardNo, V_ucbuf, CL_UserCardNo, SV_IC_SafeFlag);	/*清卡号，取消用户卡关联*/

	InF_DealWith_L_R_OAAFlag(C_Set_Method_R, C_HaveNoOpenAnAccount);					/*清2个开户状态*/

	InF_DealWith_L_R_OAAFlag(C_Set_Method_L, C_HaveNoOpenAnAccount);

	InF_UpdateAccountStateInMeterStatus3();												/*刷新状态字3中开户状态*/

	/*总清需要触发的消息,后经讨论，发广播命令*/
	V_ucbuf[0] = Pt_MeterClear;
	MF_Card_SendMsg(V_ucbuf, (Pt_MeterClear_Len + 1), C_Msg_BroadcastAddress);
	
	/*根据参数更新标志，进行所有参数读取，
	mac验证，写数据层及编程事件，主动上报*/
	V_ucReturnData = MF_IC_UpdateParm(pStr_CardParse);
	if(V_ucReturnData != C_OK)
	{
		return(V_ucReturnData);
	}

	InF_S_GetMeterNum_ReworkDL();	/*插参数预制卡会更新客户编号为0，直接同步客户编号*/

	/*对数据层进行初始化，并写清零记录
	清零主动上报-由于插参数预置卡是在公钥状态，是不会上报的。*/
	SV_Comm_Parse_Local.SafeControlFlag = C_W_SafeFlag;
	INF_WrClearAllRecord(IC_CardNo, SV_IC_SafeFlag);

	/*数据层充值购电记录*/
	/*InF_MoneyToPurchase_Init(pStr_CardParse->PPMoney,SV_IC_SafeFlag);*/

	/*写最近一次购电记录
	初始化钱包写购电记录，其中购电前剩余金额写成0
	购电金额为本次预置金额。购电总金额，由于总清，
	上1次购电金额读出来为0，
	所以可以采用上1次记录中购电总金额+本次购电金额*/
	V_ucFlag = C_Money_Init;
	InF_WRPre1PowerPurchaseRecord(pStr_CardParse->PPMoney, SV_IC_SafeFlag, V_ucFlag);

	return(C_OK);
}


/*******************************************************************************
函数原型：uchar8		MF_UserCard_Esam_Proc(StrCardParse	*pStr_CardParse)
功能描述：完成用户卡的处理
输入参数：*pStr_CardParse				:卡处理通用结构体
输出参数：*pStr_CardParse				:卡处理通用结构体
返回参数：C_OK/插卡过程错误码，如C_IC_KER_ERR等定义
调用位置：
备    注：主要参考安全规范附录A.1.4
*******************************************************************************/
uchar8		MF_UserCard_Esam_Proc(StrCardParse	*pStr_CardParse)
{
	uchar8		V_ucReturnData;
	ushort16	V_usDataLen;
	uchar8		V_ucbuf[10];
	uchar8		V_ucErrStatus;
	ushort16	V_usDataCode;

/*用户卡要求所有的密钥为私钥--0514-62
	V_ReturnData = Is_AllOfficialKey();*/
	if(InF_JudgeKeyStatus() != C_StateOfOfficialKey)
	{
		return(C_IC_KER_ERR);
	}
	
/*执行ESAM和数据层剩余金额的同步*/
	V_usDataLen = CLChargeBal_Hex_Cent;
	if( InF_GetData_ObjectManage(CChargeBal_Hex_Cent, V_ucbuf, &V_usDataLen, &V_usDataCode) == C_OK )
	{
		InF_S_UpdataChargeBalInESAM(V_ucbuf);
	}
	
	/*身份认证*/
	V_ucReturnData = InF_SC_L_Auth(IC_CardNo);
	if( V_ucReturnData != C_OK)
	{
		return(V_ucReturnData);
	}
	SV_IC_SafeFlag = SV_IC_SafeFlag | C_W_SafeFlag_2;
	
	/*读取指令文件并判断*/
	V_ucReturnData = InF_SC_RDBinFileNoMac(C_Card, C_FC_INS, 0, (CL_UserCardCMD + 6), pStr_CardParse->IC_File);
	if(V_ucReturnData != C_OK)	/*读不出,前面判断过6B00，这里不判断了*/
	{
		return(V_ucReturnData);
	}
	if(InF_SC_Judge_CardFile(pStr_CardParse->IC_File) != C_OK)		/*卡片文件格式不对*/
	{
		return(C_IC_FORMAT_ERR);
	}
	/*保存参数更新标志。表号暂存IC_File中*/
	pStr_CardParse->UpdateFlag = IC_INS_UpdataPFlag;
	pStr_CardParse->UserCardType = IC_INS_UseC_Type;
	
	/*外部认证*/
	V_ucReturnData = InF_SC_CardExtAuth(IC_CardNo);
	if( V_ucReturnData!= C_OK)
	{
		return(V_ucReturnData);
	}
	
	/*让ESAM产生Rand1-4，用于Mac计算*/
	V_ucReturnData = InF_SC_GenerateRandToCalMac(C_ESAM, C_Length_4);
	if(V_ucReturnData != C_OK)
	{
		return(V_ucReturnData);			/*这里实际上可不判。*/
	}
	
	/*判断表号是否相等。到这里，IC_File不保存了。*/
	if(InF_SC_Meter_Num_OK(IC_INS_UseC_MeterNum) != C_OK)
	{
		return(C_IC_ID_ERR);
	}
	
	/*读取用户卡钱包文件,带Mac 的文件放置在IC_File中,及PPMoney PPNum中*/
	V_ucReturnData = InF_SC_Get_MFile_Card(pStr_CardParse);
	if(V_ucReturnData != C_OK)
	{
		return(V_ucReturnData);
	}
	SV_IC_SafeFlag = SV_IC_SafeFlag | C_W_SafeFlag_3;
	
	/*根据用户卡类型，分别调用开户卡，购电卡，补卡*/
	switch(pStr_CardParse->UserCardType)
	{
		case		C_OpenCard:					/*开户卡*/
		case		C_PPCard:					/*购电卡*/
		case		C_SupplementCard:			/*补卡-目前三个处理流程统一成一种。*/
			V_ucReturnData = MF_OPS_Card_Esam_Proc(pStr_CardParse, &V_ucErrStatus);
			if(V_ucReturnData != C_OK)			/*不用返写*/
			{
				return(V_ucErrStatus);
			}
			else
			{
				break;
			}
		default:
			return(C_IC_TYPE_ERR);
	}
	
	/*更新ESAM运行文件，同时返写用户卡*/
	Updata_ESAM_OpParm(C_Msg_Card);
	
	/*让卡产生计算Mac的随机数。原随机数已失效*/
	V_ucReturnData = InF_SC_GenerateRandToCalMac(C_Card, C_Length_4);
	if(V_ucReturnData != C_OK)
	{
		return(V_ucReturnData);
	}
	
	/*返写*/
	V_ucReturnData = InF_SC_WR_UCReturnFile(IC_CardNo);
	if(V_ucReturnData != C_OK)
	{
		return(V_ucReturnData);
	}
	else
	{
		return(V_ucErrStatus);
	}	
}


/*******************************************************************************
函数原型：	uchar8	MF_OPS_Card_Esam_Proc(StrCardParse	*pStr_CardParse, uchar8 *pV_ucIC_ErrStatus)
功能描述：	开户卡、购电卡、补卡操作流程
输入参数：	pStr_CardParse			:插卡处理中通用结构体	(PPMoney、PPNum、IC_File中为钱包文件和带Mac的数)
输出参数： 	*pStr_CardParse			:卡处理通用结构体
			*pIC_ErrStatus			:插卡错误代码。如C_IC_NOIN_ERR
返回参数：	C_OK允许返写/C_Error不允许返写
调用位置：
备    注：	主要参考A.1.5 A.1.6 A.1.7,返写退回到用户卡主流程中处理
			有些情况是返回OK，但错误代码还是有的。例如开户卡
			返写文件不为空。
*******************************************************************************/
uchar8	MF_OPS_Card_Esam_Proc(StrCardParse	*pStr_CardParse, uchar8 *pV_ucIC_ErrStatus)
{
	uchar8		V_ucReturnData;
	ushort16	V_usReturnData16;
	ushort16	V_usPPNumFlag;
	
	/*返写文件是否为空的判断-复旦微。*/
	*pV_ucIC_ErrStatus = C_OK;
	V_ucReturnData = InF_SC_Is_UserCardNull(&pStr_CardParse->UserCardNull);
	if(V_ucReturnData != C_OK)
	{
		*pV_ucIC_ErrStatus = V_ucReturnData;
		return(C_Error);
	}
	
	/*读钱包文件--前面已经读过。复旦微是在这里读的。
	带Mac读取客户编码*/
	V_ucReturnData = InF_SC_GetCustNumWithMac_UseCard(pStr_CardParse->UPType_CustNum);
	if(V_ucReturnData != C_OK)
	{
		*pV_ucIC_ErrStatus = V_ucReturnData;
		return(C_Error);
	}
	
	/*开户状态及卡片序号、客户编号一致性判断*/
	V_ucReturnData = MF_Judge_OpenStutusAndCustNumCardNo(pStr_CardParse);
	if(V_ucReturnData != C_OK)
	{
		*pV_ucIC_ErrStatus = V_ucReturnData;
		return(C_Error);
	}
	
	/*对于开户卡，充值次数只能为0或1*/
	if( (pStr_CardParse->UserCardType == C_OpenCard) && (pStr_CardParse->PPNum > 1) )
	{
		*pV_ucIC_ErrStatus = C_IC_TIMES_ERR;
		return(C_Error);
	}
	
	/*完成充值金额及购电次数的判断*/
	V_usPPNumFlag = InF_Judge_ChgBal_PC_Num(pStr_CardParse->PPMoney, pStr_CardParse->PPNum);
	switch(V_usPPNumFlag)
	{
		case		C_SERR_RechargeHoarding:			/*购电次数差1，但超囤积或溢出*/
			if(pStr_CardParse->UserCardNull != C_OK)	/*反写文件不为空,购电次数差1，超囤积，*/
			{
				*pV_ucIC_ErrStatus = C_IC_NONULL_ERR;
				return(C_OK);							/*这种情况允许返写，错误号为返写不为空*/
			}
			/*超囤积不返写*/
			*pV_ucIC_ErrStatus = C_IC_OVERMAX_ERR;
			/*显示超囤积*/
			MF_Card_SendMsgToDisp(C_HoardingSign, C_AlwaysDisplay, CCDsp_Duration_10s);
			
			return(C_Error);
		case		C_MeterPC_Num_Large:				/*表内购电次数大。*/
			/*对于开户卡和补卡，进行开户动作，不充值，返回正确。
			注意这里是用不着更新客户编号的。*/
			if( (pStr_CardParse->UserCardType == C_OpenCard) || (pStr_CardParse->UserCardType == C_SupplementCard) )
			{
				MF_Finish_L_Open(pStr_CardParse);
			}
			
			return(C_OK);
		case		C_SERR_RechargeNumErr:				/*大于表内购电次数2及2以上*/
			/*写异常插卡记录需返写文件。*/
			*pV_ucIC_ErrStatus = C_IC_TIMES_ERR;
			
			return(C_OK); 
		case		C_PC_Num_Equal:						/*购电次数相等*/
		case		C_Can_EPurchase:					/*可以充值,表明充值次数卡大1*/
			break;				
		case		C_SERR_OtherErr:					/*这里应该是不可能的，如果发生，当做ESAM操作错误*/
		default:
			*pV_ucIC_ErrStatus = C_IC_ESAM_RDWR_ERR;	/*但插卡异常记录中7816Header SW没有*/
			return(C_Error);
			
	}
	
	/*到这里，处于购电次数相等或可充值2种情况*/
	if(pStr_CardParse->UserCardNull == C_OK)			/*返写文件为空*/
	{
		if(pStr_CardParse->UserCardType == C_OpenCard)	/*这里参考了0514-39，只要是开户卡，允许开户，都进行客户编号设置*/
		{
			/*如果是开户卡，可以购电，则进行客户编号验证，并更新
			客户编号Mac验证-复旦微仅在远程开户和充值时才进行客户编号Mac验证。*/	
			/*698新增写钱包文件和运行信息文件的客户编号*/
			V_usReturnData16 = InF_S_WriteCustermerNumMAC(CCustomer_Num, pStr_CardParse->UPType_CustNum, (CLCustomer_Num + C_MacLen) );

			if(V_usReturnData16 != C_OK)
			{
				if(V_usReturnData16 == C_SERR_ESAM_VF)
				{
					*pV_ucIC_ErrStatus = C_IC_MAC_ERR;
				}
				else
				{
					*pV_ucIC_ErrStatus = C_IC_ESAM_RDWR_ERR;
				}
				return(C_Error);
			}
						
			InF_Write_Data(C_Msg_Card, CCustomer_Num, pStr_CardParse->UPType_CustNum, CLCustomer_Num, SV_IC_SafeFlag);
		}
	
		if(V_usPPNumFlag == C_Can_EPurchase)
		{
			/*允许充值，首先进行充值Mac验证*/
			V_usReturnData16 = InF_S_Purchase(pStr_CardParse->IC_File);
			if(V_usReturnData16 != C_OK)
			{
				*pV_ucIC_ErrStatus = C_IC_MAC_ERR;
				return(C_Error);
			}
			/*显示充值前的剩余金额2s*/
			MF_Card_LCDView(CType_RemainMoney, pStr_CardParse);
			pStr_CardParse->PreMoneyClock = InF_OprateTimer(C_GetTimer, 2000);
			/*进行数据层充值，并进行购电记录*/
			InF_PurchaseDL(pStr_CardParse->PPMoney, SV_IC_SafeFlag);
		}
		
		/*更新参数*/
		V_ucReturnData = MF_IC_UpdateParm(pStr_CardParse);
		if(V_ucReturnData!=C_OK)		/*更新参数失败，也不进行返写*/
		{
			*pV_ucIC_ErrStatus = V_ucReturnData;
			return(C_Error);
		}
		/*如果是开户卡或补卡，进行开户动作*/
		if( (pStr_CardParse->UserCardType == C_OpenCard) || (pStr_CardParse->UserCardType == C_SupplementCard) )
		{
			MF_Finish_L_Open(pStr_CardParse);		/*理论上补卡不应该置开户标志，仅记录卡号。*/
												/*但前面如果补卡插入未开户电能表中，会报错退出。*/
												/*因此没有问题。*/
		}
		return(C_OK);
	}
	else
	{
		/*返写文件不为空*/
		if( (V_usPPNumFlag == C_PC_Num_Equal) && (pStr_CardParse->CardNoEqualFlag != C_Equal) )
		{
			/*返写不为空，购电次数相等,卡号不同的用户卡不用返写，返回错误*/
			if( (pStr_CardParse->UserCardType == C_OpenCard) || (pStr_CardParse->UserCardType == C_SupplementCard) )
			{
				*pV_ucIC_ErrStatus = C_IC_SERIAL_ERR;
				return(C_Error);
			}
		}
		
		/*购电卡卡号不等，早就退出流程了。
		规范中对所有卡，返写文件不为空，需返写文件
		对于开户卡，这种情况没有说写错误标志，购电和补卡需写错误标志。
		这里不作区别，统统写错误标志退出。20141027返写不为空，仅在购电次数差值为1时返回这个错误。根据复旦微流程*/
		if(V_usPPNumFlag == C_Can_EPurchase)
		{
			*pV_ucIC_ErrStatus = C_IC_NONULL_ERR;
		}
		
		return(C_OK);
	}
}

/*******************************************************************************
函数原型：void		MF_Finish_L_Open(StrCardParse	*pStr_CardParse)
功能描述：完成本地开户动作:保存卡号，且写本地开户状态
输入参数：pStr_CardParse中IC_CardNo		:卡号	
输出参数：无
返回参数：无
调用位置：
备    注：
*******************************************************************************/
void		MF_Finish_L_Open(StrCardParse	*pStr_CardParse)
{
	InF_Write_Data(C_Card, C_UserCardNo, IC_CardNo, CL_UserCardNo, SV_IC_SafeFlag);
	
	if( (pStr_CardParse->CardType == C_UserCardCommand) && (pStr_CardParse->UserCardType == C_OpenCard))		/*只有用户卡的开户卡才更新本地开户状态*/
	{
		InF_DealWith_L_R_OAAFlag(C_Set_Method_L, C_HaveOpenAnAccount);
	}
}


/*******************************************************************************
函数原型：	uchar8		MF_Judge_OpenStutusAndCustNumCardNo(StrCardParse	*pStr_CardParse)
功能描述：	判断开户状态及客户编号和卡号
输入参数：	pStr_CardParse->CardType		:卡片类型
			pStr_CardParse->UserCardType		:用户卡类型
			pStr_CardParse->UPType_CustNum	:客户编号
输出参数：	pStr_CardParse->CardNoEqualFlag	:卡号相等标志。取值C_Equal、C_GreaterThan等
返回参数：	C_OK/C_IC_HUHAO_ERR/C_IC_SERIAL_ERR/C_IC_NOOPEN_ERR/C_IC_NOOPEN2_ERR/C_IC_TYPE_ERR
调用位置：
备    注：	1、远程或本地一个已开户，则
				a、判断客户编号是否一致。一致到下一步，否则返回客户编号错
				b、记录卡号一致标志，如果是购电卡，一致返回正确，否则返回错误；
						其他卡返回正确
			2、未开户，
				a、如果是购电卡或补卡，则返回错误。
				b、开户卡，置卡号不一致标志，返回正确
*******************************************************************************/
uchar8		MF_Judge_OpenStutusAndCustNumCardNo(StrCardParse *pStr_CardParse)
{
	uchar8		V_ucValue = C_HaveOpenAnAccount;
	uchar8		V_ucbuf[8];
	ushort16	V_usDataEnCode,V_usLen;
	
	if( (InF_DealWith_L_R_OAAFlag(C_Judge_Method_L, V_ucValue) == C_HaveOpenAnAccount)
		|| (InF_DealWith_L_R_OAAFlag(C_Judge_Method_R, V_ucValue) == C_HaveOpenAnAccount) )			/*已开户，首先比对客户编号*/
	{
		V_usLen = CLCustomer_Num;
		if(InF_Read_Data(CCustomer_Num, V_ucbuf, &V_usLen, &V_usDataEnCode) != C_OK)				/*读不出，认为不相等*/
		{
			return(C_IC_HUHAO_ERR);
		}
		if(PF_Campare_Data(V_ucbuf, pStr_CardParse->UPType_CustNum, CLCustomer_Num) != C_Equal)		/*不相等*/
		{
			return(C_IC_HUHAO_ERR);
		}
		/*置卡号比较标志*/
		V_usLen = CL_UserCardNo;
		if(InF_Read_Data(C_UserCardNo, V_ucbuf, &V_usLen, &V_usDataEnCode) == C_OK)
		{
			pStr_CardParse->CardNoEqualFlag = PF_Campare_Data(V_ucbuf, IC_CardNo, CL_UserCardNo);
		}
		else
		{
			pStr_CardParse->CardNoEqualFlag = C_GreaterThan;
		}
		
		if(pStr_CardParse->UserCardType == C_PPCard)	/*购电卡要比较卡编号是否相等*/
		{
			if(pStr_CardParse->CardNoEqualFlag == C_Equal)
			{
				return(C_OK);
			}
			else
			{
				return(C_IC_SERIAL_ERR);
			}
		}
		else	/*对于补卡和开户卡，仅需要客户编号相等*/
		{
			return(C_OK);
		}
	}
	else		/*未开户-仅允许开户卡插入*/
	{
		switch(pStr_CardParse->UserCardType)
		{
			case		C_OpenCard:
				pStr_CardParse->CardNoEqualFlag = C_GreaterThan;
				return(C_OK);
				
			case		C_PPCard:
				return(C_IC_NOOPEN_ERR);		/*错误类型:购电卡插入未开户表*/

			case		C_SupplementCard:
				return(C_IC_NOOPEN2_ERR);		/*错误类型:补卡插入未开户表*/

			default:
				return(C_IC_TYPE_ERR);
		}
	}
}



/*******************************************************************************
函数原型：void	MF_TimeConvert(uchar8	*V_ucTime)
功能描述：5字节BCD转7字节data_time_s
输入参数：V_ucTime 待转换的5字节BCD时间
输出参数：V_ucTime 转换后的7字节data_time_s
返回参数：
调用位置：
备    注：	
*******************************************************************************/
void	MF_TimeConvert(uchar8	*V_ucTime)
{
	ulong32 V_ulHexBuffer;

	/*由于卡切换时间5个字节，需要转换*/
	if(PF_Is_Buf_AllFixedData(&V_ucTime[1], 0x00, 5) == C_OK)			/*全0*/
	{
		V_ucTime[0] = 0xFF; /*补秒*/				
		V_ucTime[6] = 0;	/*补年*/
	}
	else if(PF_Is_Buf_AllFixedData(&V_ucTime[1], 0xFF, 5) == C_OK)		/*全ff*/
	{
		V_ucTime[0] = 0xFF; /*补秒*/				
		V_ucTime[6] = 0xFF; /*补年*/
	}
	else if(PF_Is_Buf_AllFixedData(&V_ucTime[1], 0x99, 5) == C_OK)		/*全99*/
	{			
		V_ucTime[0] = 0xFF; /*补秒*/
		memset(&V_ucTime[1], 0x63, 6);	/*99转换成0x63写到数据层*/
	}
	else
	{			
		V_ucTime[0] = 0xFF; 			/*补秒*/
		V_ucTime[6] = 0x20; 			/*补年*/
		
		V_ucTime [1] = PF_BCDtoHexOneByte(V_ucTime[1]);
		V_ucTime [2] = PF_BCDtoHexOneByte(V_ucTime[2]);
		V_ucTime [3] = PF_BCDtoHexOneByte(V_ucTime[3]);
		V_ucTime [4] = PF_BCDtoHexOneByte(V_ucTime[4]);
		
		PF_BCDtoHexBytes(&V_ucTime[5], &V_ulHexBuffer, 2);
		PF_Ulong32ToBuffer4(&V_ucTime [5], &V_ulHexBuffer, 2);
	}
}

/*******************************************************************************
函数原型：	uchar8	MF_IC_UpdateParm(StrCardParse	*pStr_CardParse)
功能描述：	插卡过程中更新参数(卡中备份数据，ESAM验证并写数据层，写对应数据记录
输入参数：	pStr_CardParse->CardType		:卡片类型
			pStr_CardParse->UserCardType		:用户卡类型
			pStr_CardParse->UpdateFlag		:更新标志
输出参数：	无
返回参数：	C_OK/C_IC_MAC_ERR/C_IC_ESAM_RDWR_ERR/C_IC_NOIN_ERR
调用位置：
备    注：	1、复旦微没有对参数合法性进行判断，这里也不判断
			2、参数预置卡不进行编程相关记录
			3、购电卡和补卡，只能更新备用套，不能更新当前套。
			4、安全规范7.8要求，必须根据参数更新标志，将数据全部读出后
				再进行ESAM验证操作。这样即使提前拔卡，也能保证数据要么全部写
				要么全部不写
			5、插用户参数更新时，需要判断购电次数和返写文件是否为空。
				外部执行
*******************************************************************************/
uchar8	MF_IC_UpdateParm(StrCardParse	*pStr_CardParse)
{
	uchar8			V_ucReturnData;
	Str_Comm_645	Str_645Frame;
	uchar8			V_ucTime[7];
	uchar8			V_ucDI[4];
	uchar8			V_ucCode[4];
	uchar8			V_ucNum,i;
	ulong32			V_ulHexBuffer;
	uchar8			V_ucTempbuffer[CLCurrent_Ladder_Table];
	uchar8			V_ucDataTemp[3];
	
	/*购电卡和补卡，只能更新备用套，不能更新当前套。*/
	if( (pStr_CardParse->CardType == C_UserCardCommand) 
		&& ( (pStr_CardParse->UserCardType == C_PPCard) || (pStr_CardParse->UserCardType == C_SupplementCard) ) )
	{
		pStr_CardParse->UpdateFlag = pStr_CardParse->UpdateFlag & (~C_UPType_CurRate);
		pStr_CardParse->UpdateFlag = pStr_CardParse->UpdateFlag & (~C_UPType_CurLadder);
		pStr_CardParse->UpdateFlag = pStr_CardParse->UpdateFlag & (~C_UPType_Other);
	}
		
	/*根据UpdateFlag进行参数读取和Mac验证，写数据层
	进行待更新参数的数据从ESAM备份到内存。*/
	if( (pStr_CardParse->UpdateFlag & C_UPType_CurRate) != 0)		/*更新当前套费率电价标志为1*/
	{
		V_ucReturnData = InF_SC_Backup_With_Mac(C_UPType_CurRate, pStr_CardParse->UPType_CurRate);
		if(V_ucReturnData != C_OK) 
		{
			return(V_ucReturnData);
		}
	}

	if( (pStr_CardParse->UpdateFlag & C_UPType_BakRate) != 0)		/*更新备用套费率电价标志为1*/
	{
		V_ucReturnData = InF_SC_Backup_With_Mac(C_UPType_BakRate, pStr_CardParse->UPType_BakRate);
		if(V_ucReturnData != C_OK) 
		{
			return(V_ucReturnData);
		}

		V_ucReturnData = InF_SC_Backup_With_Mac(C_UPType_ChgRateClock, pStr_CardParse->UPType_ChgRateClock);
		if(V_ucReturnData != C_OK) 
		{
			return(V_ucReturnData);
		}
	}

	if( (pStr_CardParse->UpdateFlag & C_UPType_CurLadder) != 0)		/*更新当前套阶梯标志为1*/
	{
		V_ucReturnData = InF_SC_Backup_With_Mac(C_UPType_CurLadder, pStr_CardParse->UPType_CurLadder);
		if(V_ucReturnData != C_OK) 
		{
			return(V_ucReturnData);
		}
	}
 
	if( (pStr_CardParse->UpdateFlag & C_UPType_BakLadder) != 0)		/*更新备用套阶梯标志为1*/
	{
		V_ucReturnData = InF_SC_Backup_With_Mac(C_UPType_BakLadder, pStr_CardParse->UPType_BakLadder);
		if(V_ucReturnData != C_OK)
		{
			return(V_ucReturnData);
		}
	}

	if( (pStr_CardParse->UpdateFlag & C_UPType_Other) != 0)			/*更新其他参数标志为1*/
	{
		V_ucReturnData = InF_SC_Backup_With_Mac(C_UPType_Other, pStr_CardParse->UPType_Other);
		if(V_ucReturnData != C_OK) 
		{
			return(V_ucReturnData);
		}
	}

/*卡上全部待更新参数读取完毕，进行Mac验证。*/
	if( (pStr_CardParse->UpdateFlag & C_UPType_CurRate) != 0)		/*更新当前套费率电价标志为1*/
	{
		V_ucReturnData = InF_SC_BackupW_With_Mac(C_UPType_CurRate, pStr_CardParse->UPType_CurRate);
		if(V_ucReturnData != C_OK) 
		{
			return(V_ucReturnData);
		}
	}

	if((pStr_CardParse->UpdateFlag & C_UPType_BakRate) != 0)	/*更新备用套费率电价标志为1*/
	{
		V_ucReturnData = InF_SC_BackupW_With_Mac(C_UPType_BakRate, pStr_CardParse->UPType_BakRate);
		if(V_ucReturnData != C_OK) 
		{
			return(V_ucReturnData);
		}

		V_ucReturnData = InF_SC_BackupW_With_Mac(C_UPType_ChgRateClock, pStr_CardParse->UPType_ChgRateClock);
		if(V_ucReturnData != C_OK)
		{
			return(V_ucReturnData);
		}
	}

	if((pStr_CardParse->UpdateFlag & C_UPType_CurLadder) != 0)	/*更新当前套阶梯标志为1*/
	{
		V_ucReturnData = InF_SC_BackupW_With_Mac(C_UPType_CurLadder, pStr_CardParse->UPType_CurLadder);
		if(V_ucReturnData != C_OK) 
		{
			return(V_ucReturnData);
		}
	}

	if((pStr_CardParse->UpdateFlag & C_UPType_BakLadder) != 0)	/*更新备用套阶梯标志为1*/
	{
		V_ucReturnData = InF_SC_BackupW_With_Mac(C_UPType_BakLadder, pStr_CardParse->UPType_BakLadder);
		if(V_ucReturnData != C_OK) 
		{	
			return(V_ucReturnData);
		}
	}

	if((pStr_CardParse->UpdateFlag & C_UPType_Other) != 0)		/*更新其他标志为1*/
	{
		V_ucReturnData = InF_SC_BackupW_With_Mac(C_UPType_Other, pStr_CardParse->UPType_Other);
		if(V_ucReturnData != C_OK) 
		{
			return(V_ucReturnData);
		}
	}

/*ESAM验证全部正确后，进行写数据层动作。*/

/*首先进行数据项颠倒。*/
	InF_BackupData_Reversal(C_UPType_CurRate, pStr_CardParse->UPType_CurRate);
	InF_BackupData_Reversal(C_UPType_BakRate, pStr_CardParse->UPType_BakRate);	
	InF_BackupData_Reversal(C_UPType_ChgRateClock, pStr_CardParse->UPType_ChgRateClock);
	InF_BackupData_Reversal(C_UPType_CurLadder, pStr_CardParse->UPType_CurLadder);
	InF_BackupData_Reversal(C_UPType_BakLadder, pStr_CardParse->UPType_BakLadder);
	InF_BackupData_Reversal(C_UPType_Other, pStr_CardParse->UPType_Other);

/*写数据层*/
	if( (pStr_CardParse->UpdateFlag & C_UPType_CurRate) != 0)		/*更新当前套费率电价标志为1*/
	{
		Str_645Frame.DI = CCurrent_RateFF_Price;
		Str_645Frame.DataLen = CLCurrent_RateFF_Price + C_Data_OFS_14;

		/*以下数据格式转换，12个费率 BCD转hex格式*/
		V_ucNum = CLCurrent_RateFF_Price / CLCurrent_Rate1_Price;
		for(i = 0; i < V_ucNum; i++)	/*数据大小端已经翻转过了*/
		{
			PF_BCDtoHexBytes(&pStr_CardParse->UPType_CurRate[CO_UPRate + i * CLCurrent_Rate1_Price], &V_ulHexBuffer, CLCurrent_Rate1_Price);
			PF_Ulong32ToBuffer4(&Str_645Frame.Data[C_Data_OFS_14 + i * CLCurrent_Rate1_Price], &V_ulHexBuffer, CLCurrent_Rate1_Price);
		}
		/*PF_CopyDataBytes(&pStr_CardParse->UPType_CurRate[CO_UPRate], &V_645Frame.Data[C_Data_OFS_14], CLCurrent_RateFF_Price);	*/		

		SV_Comm_Parse_Local.RecFlag = C_CommRecFlagForInt_Ok;			
		SV_Comm_Parse_Local.SafeControlFlag = C_W_SafeFlag;
		Have_IPEvent_Prog_698(CProgTPara_Note_1, CProgTPara_Degree, &Str_645Frame);

#if 0		
		if(pStr_CardParse->CardType == C_UserCardCommand)	/*如果是用户卡进行费率表编程事件记录。参数预置卡不进行编程记录*/
		{
			INF_WrRateProgRecord(IC_CardNo,SV_IC_SafeFlag);
			Inf_EventReport_HP(C_ProgTParaEventNo,C_Happen_EventReport);  
		}
		InF_Write_Data(C_Msg_Card,CCurrent_RateFF_Price,&pStr_CardParse->UPType_CurRate[CO_UPRate],CLCurrent_RateFF_Price,SV_IC_SafeFlag);
		InF_ActiveReportSetting(C_Times_ReworkRatesCharge);		/*费率表编程主动上报处理*/
#endif

	}

	if((pStr_CardParse->UpdateFlag & C_UPType_BakRate) != 0)	/*更新备用套费率电价标志为1*/
	{
		Str_645Frame.DI = CBackUp_RateFF_Price;
		Str_645Frame.DataLen = CLBackUp_RateFF_Price + C_Data_OFS_14;

		/*以下数据格式转换，12个费率 BCD转hex格式*/
		V_ucNum = CLBackUp_RateFF_Price / CLBackUp_Rate1_Price;
		for(i = 0; i < V_ucNum; i++)
		{
			PF_BCDtoHexBytes(&pStr_CardParse->UPType_BakRate[CO_UPRate + i * CLBackUp_Rate1_Price], &V_ulHexBuffer, CLBackUp_Rate1_Price);
			PF_Ulong32ToBuffer4(&Str_645Frame.Data[C_Data_OFS_14 + i * CLBackUp_Rate1_Price], &V_ulHexBuffer, CLBackUp_Rate1_Price);
		}

		/*PF_CopyDataBytes(&pStr_CardParse->UPType_BakRate[CO_UPRate], &V_645Frame.Data[C_Data_OFS_14], CLBackUp_RateFF_Price );*/			

		SV_Comm_Parse_Local.RecFlag = C_CommRecFlagForInt_Ok;			
		SV_Comm_Parse_Local.SafeControlFlag = C_W_SafeFlag;
		Have_IPEvent_Prog_698(CProgTPara_Note_1, CProgTPara_Degree, &Str_645Frame);

		#if 0
		if(pStr_CardParse->CardType == C_UserCardCommand)	/*如果是用户卡进行费率表编程事件记录。参数预置卡不进行编程记录*/
		{
			INF_WrRateProgRecord(IC_CardNo,SV_IC_SafeFlag);
			Inf_EventReport_HP(C_ProgTParaEventNo,C_Happen_EventReport);
		}
		InF_Write_Data(C_Msg_Card,CBackUp_RateFF_Price,&pStr_CardParse->UPType_BakRate[CO_UPRate],CLBackUp_RateFF_Price,SV_IC_SafeFlag);
		#endif

		/*由于卡切换时间5个字节，需要转换*/
		PF_CopyDataBytes(pStr_CardParse->UPType_ChgRateClock, &V_ucTime[1], 5);
		MF_TimeConvert(V_ucTime);
		InF_Write_Data(C_Msg_Card, CChange_Rate, V_ucTime, CLChange_Rate, SV_IC_SafeFlag);
/*		InF_ActiveReportSetting(C_Times_ReworkRatesCharge);	*/	/*费率表编程主动上报处理*/
	}	

	if((pStr_CardParse->UpdateFlag & C_UPType_CurLadder) != 0)	/*更新当前套阶梯标志为1*/
	{
		Str_645Frame.DI = CCurrent_Ladder_Table;
		Str_645Frame.DataLen = CLCurrent_Ladder_Table + C_Data_OFS_14;

		/*数据转换 :13个4字节BCD转4字节hex，4个月日时*/				
		PF_CopyDataBytes(pStr_CardParse->UPType_CurLadder, V_ucTempbuffer, CLCurrent_Ladder_Table);			

		V_ucNum = 6 + 7;	/*6个阶梯+7个阶梯电价*/	
		for(i = 0; i < V_ucNum; i++)
		{		
			PF_BCDtoHexBytes(&V_ucTempbuffer[4 * i], &V_ulHexBuffer, 4);
			PF_Ulong32ToBuffer4(&V_ucTempbuffer[4 * i], &V_ulHexBuffer, 4);
		}

		/*月、日、时转换成*/
		V_ucNum = 4;	/*4个结算日*/	
		for(i = 0; i < V_ucNum; i++)	/*内部再翻转一次*/
		{
			memcpy(V_ucDataTemp, &V_ucTempbuffer[4 * 13 + i * 3], 3);
			if(V_ucDataTemp[2] != 0xFF)
			{
				V_ucTempbuffer[4 * 13 + i * 3] = PF_BCDtoHexOneByte(V_ucDataTemp[2]);
			}
			else
			{
				V_ucTempbuffer[4 * 13 + i * 3] = 0xFF;
			}
			
			if(V_ucDataTemp[1] != 0xFF)
			{
				V_ucTempbuffer[4 * 13 + i * 3 + 1] = PF_BCDtoHexOneByte(V_ucDataTemp[1]);
			}
			else
			{
				V_ucTempbuffer[4 * 13 + i * 3 + 1] = 0xFF;
			}
			
			if(V_ucTempbuffer[0] != 0xFF)
			{
				V_ucTempbuffer[4 * 13 + i * 3 + 2] = PF_BCDtoHexOneByte(V_ucDataTemp[0]);
			}
			else
			{
				V_ucTempbuffer[4 * 13 + i * 3 + 2] = 0xFF;
			}	
		}
		
		PF_CopyDataBytes(V_ucTempbuffer, &Str_645Frame.Data[C_Data_OFS_14], CLCurrent_Ladder_Table);
		SV_Comm_Parse_Local.RecFlag = C_CommRecFlagForInt_Ok;			
		SV_Comm_Parse_Local.SafeControlFlag = C_W_SafeFlag;
		Have_IPEvent_Prog_698(CProgLad_Note_1, CProgLad_Degree, &Str_645Frame);

		#if 0			
		if(pStr_CardParse->CardType == C_UserCardCommand)	/*如果是用户卡进行阶梯表编程事件记录。参数预置卡不进行编程记录*/
		{
			INF_WrStepProgRecord(IC_CardNo,SV_IC_SafeFlag);
			Inf_EventReport_HP(C_ProgLadEventNo,C_Happen_EventReport);
			MF_Card_SendMsgToSettlement();		/*更新当前套阶梯表参数发消息给结算模块，判断年结算日是否变化，变化则进行年结算*/
		}
		InF_Write_Data(C_Msg_Card,CCurrent_Ladder_Table,pStr_CardParse->UPType_CurLadder,CLCurrent_Ladder_Table,SV_IC_SafeFlag);
		InF_ActiveReportSetting(C_Times_ReworkStepPara);			/*阶梯表编程主动上报处理*/
		#endif
	}

	if( (pStr_CardParse->UpdateFlag & C_UPType_BakLadder) != 0)		/*更新备用套阶梯标志为1*/
	{
		Str_645Frame.DI = CBackUp_Ladder_Table;
		Str_645Frame.DataLen = CLBackUp_Ladder_Table + C_Data_OFS_14;

		/*数据转换 :13个4字节BCD转4字节hex，4个月日时*/
		PF_CopyDataBytes(pStr_CardParse->UPType_BakLadder, V_ucTempbuffer, CLCurrent_Ladder_Table);

		V_ucNum = 6 + 7;	/*6个阶梯和7个阶梯电价*/	
		for(i = 0; i < V_ucNum; i++)
		{		
			PF_BCDtoHexBytes(&V_ucTempbuffer[4 * i], &V_ulHexBuffer, 4);
			PF_Ulong32ToBuffer4(&V_ucTempbuffer[4 * i], &V_ulHexBuffer, 4);
		}

		/*月、日、时转换成*/
		V_ucNum = 4;	/*4个结算日*/	
		for(i = 0; i < V_ucNum; i++)
		{
			memcpy(V_ucDataTemp, &V_ucTempbuffer[4 * 13 + i * 3], 3);
			if(V_ucDataTemp[2] != 0xFF)
			{
				V_ucTempbuffer[4 * 13 + i * 3] = PF_BCDtoHexOneByte(V_ucDataTemp[2]);
			}
			else
			{
				V_ucTempbuffer[4 * 13 + i * 3] = 0xFF;
			}
			
			if(V_ucDataTemp[1] != 0xFF)
			{
				V_ucTempbuffer[4 * 13 + i * 3 + 1] = PF_BCDtoHexOneByte(V_ucDataTemp[1]);
			}
			else
			{
				V_ucTempbuffer[4 * 13 + i * 3 + 1] = 0xFF;
			}
			
			if(V_ucTempbuffer[0] != 0xFF)
			{
				V_ucTempbuffer[4 * 13 + i * 3 + 2] = PF_BCDtoHexOneByte(V_ucDataTemp[0]);
			}
			else
			{
				V_ucTempbuffer[4 * 13 + i * 3 + 2] = 0xFF;
			}	
		}

		PF_CopyDataBytes(V_ucTempbuffer, &Str_645Frame.Data[C_Data_OFS_14], CLBackUp_Ladder_Table );
		SV_Comm_Parse_Local.RecFlag = C_CommRecFlagForInt_Ok;
		SV_Comm_Parse_Local.SafeControlFlag = C_W_SafeFlag;
		Have_IPEvent_Prog_698(CProgLad_Note_1, CProgLad_Degree, &Str_645Frame);

		#if 0
		if(pStr_CardParse->CardType == C_UserCardCommand)/*如果是用户卡进行阶梯表编程事件记录。参数预置卡不进行编程记录*/
		{
			INF_WrStepProgRecord(IC_CardNo,SV_IC_SafeFlag);
            Inf_EventReport_HP(C_ProgLadEventNo,C_Happen_EventReport);
		}
		InF_Write_Data(C_Msg_Card,CBackUp_Ladder_Table,pStr_CardParse->UPType_BakLadder,CLBackUp_Ladder_Table,SV_IC_SafeFlag);
		#endif
		
		/*由于卡切换时间5个字节，需要转换*/
		PF_CopyDataBytes(&pStr_CardParse->UPType_BakLadder[CO_UPLadderChgClock], &V_ucTime[1], 5);
		MF_TimeConvert(V_ucTime);
		
		InF_Write_Data(C_Msg_Card, CChange_Ladder, V_ucTime, CLChange_Ladder, SV_IC_SafeFlag);

/*			InF_ActiveReportSetting(C_Times_ReworkStepPara);	*/		/*阶梯表编程主动上报处理*/
	}

	if( (pStr_CardParse->UpdateFlag & C_UPType_Other) != 0)	/*更新其他标志为1*/
	{
		/*报警金额1 需要4字节BCD转4字节hex*/
		PF_BCDtoHexBytes(&pStr_CardParse->UPType_Other[CO_UPOther_Alam1], &V_ulHexBuffer, CLAlam1_Money);
		PF_Ulong32ToBuffer4(V_ucTempbuffer, &V_ulHexBuffer, CLAlam1_Money);
		InF_Write_Data(C_Msg_Card, CAlam1_Money, V_ucTempbuffer, CLAlam1_Money, SV_IC_SafeFlag);

		/*报警金额2 需要4字节BCD转4字节hex*/
		PF_BCDtoHexBytes(&pStr_CardParse->UPType_Other[CO_UPOther_Alam2], &V_ulHexBuffer, CLAlam2_Money);
		PF_Ulong32ToBuffer4(V_ucTempbuffer, &V_ulHexBuffer, CLAlam2_Money);
		InF_Write_Data(C_Msg_Card, CAlam2_Money, V_ucTempbuffer, CLAlam2_Money, SV_IC_SafeFlag);

		/*电流变比,需要3字节BCD转4字节hex*/
		PF_CopyDataBytes(&pStr_CardParse->UPType_Other[CO_UPOther_Ratio_CT], &V_ucTempbuffer[0], CLRatio_Curr_Tran_Esam);	
		V_ucTempbuffer[3] = 0;	/*补高位*/
		PF_BCDtoHexBytes(&V_ucTempbuffer[0], &V_ulHexBuffer, CLRatio_Curr_Tran);
		PF_Ulong32ToBuffer4(&V_ucTempbuffer[0], &V_ulHexBuffer, CLRatio_Curr_Tran);		
		InF_Write_Data(C_Msg_Card, CRatio_Curr_Tran, V_ucTempbuffer, CLRatio_Curr_Tran, SV_IC_SafeFlag);

		/*电压变比,需要3字节BCD转4字节hex*/
		PF_CopyDataBytes(&pStr_CardParse->UPType_Other[CO_UPOther_Ratio_VT], &V_ucTempbuffer[0], CLRatio_Vol_Tran_Esam);
		V_ucTempbuffer[3] = 0;	/*补高位*/
		PF_BCDtoHexBytes(&V_ucTempbuffer[0], &V_ulHexBuffer, CLRatio_Vol_Tran);
		PF_Ulong32ToBuffer4(&V_ucTempbuffer[0], &V_ulHexBuffer, CLRatio_Vol_Tran);
		InF_Write_Data(C_Msg_Card, CRatio_Vol_Tran, V_ucTempbuffer, CLRatio_Vol_Tran, SV_IC_SafeFlag);
	
		/*发消息给电脑模块，进行告警、预跳闸、透支、立即拉闸等判断*/
		MF_Card_SendMsgForUpdataParm(C_ReworkWarningPara, C_Msg_EnergyMetering);
	}

	/*发消息给费率模块，进行费率表、阶梯表切换判断，这里不管是否更新都发，多判断一次没有关系*/
	MF_Card_SendMsgForUpdataParm(C_ReMultiRatesParm, C_Msg_Deal_MultiRates);

	/*写总编程记录*/
	if( (pStr_CardParse->CardType == C_UserCardCommand) 
		&& ( (pStr_CardParse->UpdateFlag & (C_UPType_Other|C_UPType_BakLadder|C_UPType_CurLadder|C_UPType_BakRate|C_UPType_CurRate) ) != 0) )
	{
		V_ucDI[0] = pStr_CardParse->UpdateFlag;
		V_ucDI[1] = pStr_CardParse->CardType;
		V_ucDI[2] = 0x98;
		V_ucDI[3] = 0x99;
		INF_Append_ProgRecordDI(V_ucCode,V_ucDI,&SV_Comm_Parse.ProgRecord,C_ACTION_Request);
		
		#if 0
		if(pStr_CardParse->UpdateFlag &C_UPType_BakRate)	/*更新备用套费率电价*/
		{			
			V_ulDI = CBackUp_RateFF_Price;
			PF_Ulong32ToBuffer4(V_ucDI, &V_ulDI, 4);
			INF_Append_ProgRecordDI(V_ucCode,V_ucDI,&SV_Comm_Parse.ProgRecord);
		}

		if(pStr_CardParse->UpdateFlag &C_UPType_BakLadder)	/*更新备用套阶梯电价*/
		{			
			V_ulDI = CBackUp_Ladder_Table;
			PF_Ulong32ToBuffer4(V_ucDI, &V_ulDI, 4);
			INF_Append_ProgRecordDI(V_ucCode,V_ucDI,&SV_Comm_Parse.ProgRecord);
		}
		
		if(pStr_CardParse->UpdateFlag &C_UPType_Other)	/*更新其他参数*/
		{
			/*报警金额1*/
			V_ulDI = CAlam1_Money;
			PF_Ulong32ToBuffer4(V_ucDI, &V_ulDI, 4);
			INF_Append_ProgRecordDI(V_ucCode,V_ucDI,&SV_Comm_Parse.ProgRecord);

			/*报警金额2*/
			V_ulDI = CRatio_Curr_Tran;
			PF_Ulong32ToBuffer4(V_ucDI, &V_ulDI, 4);
			INF_Append_ProgRecordDI(V_ucCode,V_ucDI,&SV_Comm_Parse.ProgRecord);

			/*电压互感器变比*/
			V_ulDI = CRatio_Vol_Tran;
			PF_Ulong32ToBuffer4(V_ucDI, &V_ulDI, 4);
			INF_Append_ProgRecordDI(V_ucCode,V_ucDI,&SV_Comm_Parse.ProgRecord);
			/*电流互感器变比*/
			V_ulDI = CBackUp_RateFF_Price;
			PF_Ulong32ToBuffer4(V_ucDI, &V_ulDI, 4);
			INF_Append_ProgRecordDI(V_ucCode,V_ucDI,&SV_Comm_Parse.ProgRecord);
		
		}
		#endif

		/*写结束*/
		INF_StopCommProgState();
	}

	return(C_OK);
}


/*******************************************************************************
函数原型：	MF_Card_SendMsg(uchar8	 *pStr_MsgParmData, uchar8 V_ucLen, uchar8 V_ucDestAddress)
功能描述：	卡消息发布消息
输入参数：	*pMsgParmData			:参数域首地址
			Len						:参数域长度包括PT
			DestAddress				:目的地址
输出参数：	无
返回参数：
调用位置：
备    注：
*******************************************************************************/
void		MF_Card_SendMsg(uchar8	 *pStr_MsgParmData, uchar8 V_ucLen, uchar8 V_ucDestAddress)
{
	Str_Msg_Parameter	Str_MsgParm;
	
	Str_MsgParm.SourceAddr = C_Msg_Card;
	Str_MsgParm.Parameter = pStr_MsgParmData;
	Str_MsgParm.Length = V_ucLen;

	Str_MsgParm.DerictAddr = V_ucDestAddress;

	InF_WriteMessege(&Str_MsgParm);
}

/*******************************************************************************
函数原型：void		MF_Card_SendICMsg(void)
功能描述：发布插卡消息
输入参数：无
输出参数：无
返回参数：
调用位置：
备    注：发布插卡消息
*******************************************************************************/
void		MF_Card_SendICMsg(void)
{
	Str_Msg_Parameter	Str_MsgParm;
	uchar8				V_ucbuf;
	
	V_ucbuf = Pt_CardFlag;
	Str_MsgParm.SourceAddr = C_Msg_Card;
	Str_MsgParm.Parameter = &V_ucbuf;
	Str_MsgParm.Length = Pt_CardFlag_Len + 1;

	Str_MsgParm.DerictAddr = C_Msg_Deal_RelayStatus;

	InF_WriteMessege(&Str_MsgParm);
}


/*******************************************************************************
函数原型：	void		MF_Card_SendMsgToDisp(uchar8 V_ucDispSign, uchar8 V_ucDispMode, ushort16 V_usDuration)
功能描述：	完成让显示模块处理一个字符
输入参数：	V_ucDispSign:	显示符号
			V_ucDispMode：	显示模式
			V_usDuration：	显示时间
输出参数：	无
返回参数：	无
调用位置：
备    注：
*******************************************************************************/
void		MF_Card_SendMsgToDisp(uchar8 V_ucDispSign, uchar8 V_ucDispMode, ushort16 V_usDuration)
{
	Str_Msg_Parameter	Str_MsgParm;
	uchar8				V_ucbuf[4];
	
	Str_MsgParm.DerictAddr = C_Msg_Display;
	Str_MsgParm.SourceAddr = C_Msg_Card;
	V_ucbuf[0] = Pt_DisplayStatus;
	V_ucbuf[1] = V_ucDispSign | V_ucDispMode;
	PF_Ushort16ToBuffer2(&V_ucbuf[2], &V_usDuration);
	Str_MsgParm.Parameter = V_ucbuf;
	Str_MsgParm.Length = Pt_DisplayStatus_Len + 1;

	InF_Display_Message(&Str_MsgParm);
}


/*******************************************************************************
函数原型：	void		MF_Card_LCDView(uchar8	 V_ucType, StrCardParse	*pStr_CardParse)
功能描述：	插卡过程液晶主屏幕的显示
输入参数：	V_ucType				:显示类型。取值CType_RemainMoney/CType_IC_Err
			pStr_CardParse->IC_ErrEvent[CO_CE_ErrStatus]:	错误信息字
			仅在Type = CType_IC_Err时起作用
输出参数：
返回参数：
调用位置：
备    注：	注意这里卡处理当做调度，直接调用显示模块进行显示处理
*******************************************************************************/
void		MF_Card_LCDView(uchar8	 V_ucType, StrCardParse	*pStr_CardParse)
{
	Str_Msg_Parameter	Str_MsgParm;
	uchar8				V_ucbuf[12];
	uchar8				V_ucIc_Err_Reg;
	
	Str_MsgParm.DerictAddr = C_Msg_Display;
	Str_MsgParm.SourceAddr = C_Msg_Card;
	Str_MsgParm.Parameter = V_ucbuf;
	
	if(V_ucType == CType_RemainMoney)		/*主屏幕显示，采用液晶查看方式，持续时间由显示模块固定为10s*/
	{
		V_ucbuf[0] = Pt_DisplayID;
		if(MF_IsOverDraft_Zero() == C_OK)	/*透支全0，显示剩余*/
		{
			V_ucbuf[1] = 0x01;	
            V_ucbuf[2] = 0x02;
	        V_ucbuf[3] = 0x2C;
	        V_ucbuf[4] = 0x20;
			V_ucbuf[5] = 0xff;	
            V_ucbuf[6] = 0xff;
	        V_ucbuf[7] = 0xff;
	        V_ucbuf[8] = 0xff;				
	        V_ucbuf[9] = 0x00;
		}
		else								/*透支不为0，显示透支*/
		{
			V_ucbuf[1] = 0x00;	
            V_ucbuf[2] = 0x02;
	        V_ucbuf[3] = 0x2D;
	        V_ucbuf[4] = 0x20;
			V_ucbuf[5] = 0xff;	
            V_ucbuf[6] = 0xff;
	        V_ucbuf[7] = 0xff;
	        V_ucbuf[8] = 0xff;				
	        V_ucbuf[9] = 0x00;
		}
		V_ucbuf[10] = CCDsp_Duration_10sL;
		V_ucbuf[11] = CCDsp_Duration_10sH;

		Str_MsgParm.Length = Pt_DisplayID_Len + 1;
	}
	else	/*主屏幕显示错误信息字，采用字符显示类似方式,持续时间也设置成10s*/
	{
		V_ucbuf[0] = Pt_ERRXXDisplay;		/*错误显示*/
		V_ucIc_Err_Reg = pStr_CardParse->IC_ErrEvent[CO_CE_ErrStatus];
		if(V_ucIc_Err_Reg == C_OK)
		{
			return;
		}
		/*置错误代码*/
		if(V_ucIc_Err_Reg < 4) 
		{
			V_ucbuf[1] = 0x31;
		}
		else if(V_ucIc_Err_Reg < 11) 
		{
			V_ucbuf[1] = 0x32;
		}
		else if(V_ucIc_Err_Reg < 14) 
		{
			V_ucbuf[1] = 0x33;
		}
		else if(V_ucIc_Err_Reg < 19) 
		{
			V_ucbuf[1] = 0x34;
		}
		else if(V_ucIc_Err_Reg < 21) 
		{
			V_ucbuf[1] = 0x35;
		}
		else 
		{
			V_ucbuf[1] = 0x36;
		}
		V_ucbuf[2] = CCDsp_Duration_10sL;
		V_ucbuf[3] = CCDsp_Duration_10sH;
		Str_MsgParm.Length = Pt_ERRXXDisplay_Len + 1;
	}
	
	InF_Display_Message(&Str_MsgParm);
}


/*******************************************************************************
函数原型：uchar8	MF_IsOverDraft_Zero(void)
功能描述：判断透支金额是否为全0
输入参数：无
输出参数：无
返回参数：C_OK:全零/C_Error不是全零
调用位置：
备    注：
*******************************************************************************/
uchar8	MF_IsOverDraft_Zero(void)
{
	ushort16	V_usDataLen;
	uchar8		V_ucbuf[CLOverDraft_Hex_Cent],V_ucReturnData;
	ulong32		V_ulOverDraft_BCD;
	ushort16	V_usDataEnCode;
	

	V_usDataLen = CLOverDraft_Hex_Cent;
	V_ucReturnData = InF_GetData_ObjectManage(COverDraft_Hex_Cent, V_ucbuf, &V_usDataLen, &V_usDataEnCode);
	if(V_ucReturnData != C_OK)
	{
		return C_Error;
	}

	PF_Buffer4ToUlong32(V_ucbuf, &V_ulOverDraft_BCD, CLOverDraft_Hex_Cent);
	
	if(V_ulOverDraft_BCD == 0)
	{
		return(C_OK);
	}
	else
	{
		return(C_Error);
	}
}


/*******************************************************************************
函数原型：void		MF_WRPre1ErrCardRecord(StrCardParse	*pStr_CardParse)
功能描述：写最近一次异常插卡记录
输入参数：StrCardParse	*pStr_CardParse
输出参数：无
返回参数：无
调用位置：插卡异常
备    注：事件单元不是标准事件单元
*******************************************************************************/
void		MF_WRPre1ErrCardRecord(StrCardParse	*pStr_CardParse)
{
	uchar8		V_ucDataBuff[300] = {0}, V_ucTemp[4];
	uchar8		V_ucLength;
	ushort16 	V_usOffset = 0, V_usResidualLength, V_usRelateoff;
	uchar8		V_ucEvent_Flag;
	ulong32		V_ulTemp = 0;
	ushort16	V_usDataEnCode, V_usLen;
	
	V_usLen = CLAbnorC_Degree;
	InF_Read_Data(CAbnorC_Degree, V_ucDataBuff, &V_usLen, &V_usDataEnCode);		/*赋事件序号*/
	/*PF_BCDAddBytes(V_ucDataBuff, (uchar8 *)V_AddOneMin, V_ucDataBuff, P_Data_Length);*/	/*累计时间加1*/
	V_usOffset += 4;
	
	V_usLen = CLDate_Week_Time;
	InF_Read_Data(CDate_Time, &V_ucDataBuff[V_usOffset], &V_usLen, &V_usDataEnCode);		/*赋事件发生时间，结束时间为00000000000000*/
	V_usOffset += 7;
	V_usOffset += 7;
	V_usOffset += 1;	/*发生源赋空*/
	V_usOffset += 1;	/*事件上报状态赋空*/

	/*卡序列号*/
	PF_CopyDataBytes(IC_CardNo, &V_ucDataBuff[V_usOffset], CL_CardNo);
	V_usOffset += CL_CardNo;
	
	/*插卡错误信息字*/
	PF_CopyDataBytes(&IC_ErrStatus, &V_ucDataBuff[V_usOffset], CL_CE_ErrStatus);	
	V_usOffset += CL_CE_ErrStatus;
	
	/*插卡操作命令头*/
	PF_CopyDataBytes(IC_Err7816Header, &V_ucDataBuff[V_usOffset], CL_7816Header);
	V_usOffset += CL_7816Header;
	
	/*插卡错误响应状态*/
	PF_CopyDataBytes(IC_ErrSW1_2, &V_ucDataBuff[V_usOffset], CL_7816_SW);
	V_usOffset += CL_7816_SW;
	V_usResidualLength = 300 - V_usOffset;		/*剩余buff长度*/
	V_ucEvent_Flag = 0x01;
	V_usRelateoff = V_usOffset;	/*保存上一次的事件头偏移地址，便于写恢复用*/

	if(Inf_GetRecordData(&V_ucDataBuff[V_usOffset], &V_usResidualLength, CAbnorC_OADTab, V_ucEvent_Flag) == C_OK)	/*获取关联OAD数据*/	
	{
		V_usOffset += V_usResidualLength;			/*数据总长度*/
	}
	InF_Write_Data(C_Msg_Card, CAbnorC_Note_1, V_ucDataBuff, V_usOffset, C_W_SafeFlag);	/*写异常插卡事件记录*/

	/*写恢复*/
	V_usResidualLength = 300 - V_usRelateoff;
	if(Inf_GetRecordData(&V_ucDataBuff[V_usRelateoff], &V_usResidualLength, CAbnorC_OADTab, 0x02) == C_OK)	/*取结束数据*/
	{
		V_usOffset += V_usResidualLength;			/*数据总长度*/
	}
	InF_Write_Data(C_Msg_Card, (CAbnorC_Note_1 + 1), V_ucDataBuff, V_usRelateoff, C_W_SafeFlag);

	Inf_EventReport_HP(C_AbnorCEventNo, C_Happen_EventReport);	

}

/*******************************************************************************
函数原型：void		MF_Write_IC_ErrEvent(StrCardParse	*pStr_CardParse)
功能描述：异常插卡事件记录及非法插卡总次数
输入参数：*pStr_CardParse->IC_ErrEvent		:异常插卡记录		
输出参数：无
返回参数：无
调用位置：
备    注：
*******************************************************************************/
void		MF_Write_IC_ErrEvent(StrCardParse *pStr_CardParse)
{
	uchar8		V_ucLawlessC_Degree[CLLawlessC_Degree + 1];
	ushort16	V_usDataLen;
	ulong32		V_ulNum = 1;
	ushort16	V_usDataEnCode;
	
	/*判断是否提前拔卡	*/
	if( (InF_GetPeripheralStatus(C_CardStatus) != C_Valid) && (IC_ErrStatus == C_IC_NOIN_ERR) )	/*如果插卡信号为无效，且卡通信错误，判断为提前拔卡*/
	{
		IC_ErrStatus = C_IC_PREIC_ERR;
	}
	
	/*写7816操作命令头和SW，不是以下错误，在初始化中已清零。*/
	if( (IC_ErrStatus == C_IC_ESAM_RDWR_ERR) /*沿用复旦微的做法*/
		|| (IC_ErrStatus == C_IC_NOFX_ERR)
		|| (IC_ErrStatus == C_IC_MAC_ERR) 
		|| (IC_ErrStatus == C_IC_NOIN_ERR)
		|| (IC_ErrStatus == C_IC_EXAUTH_ERR) )
	{
		/*目前操作卡片通信错误，底层返回FFxx,增加判断当错误为FFXX时，记录操作响应为0000*/
		if( (C_Security_Null) == (GV_7816CMD.SW1_2 & (C_Security_Null) ) )
		{
			GV_7816CMD.SW1_2 = 0;
		}
		PF_CopyDataBytes(GV_7816CMD.Header, IC_Err7816Header, CL_7816Header);	/*操作命令头*/
		PF_Ushort16ToBuffer2(IC_ErrSW1_2, &GV_7816CMD.SW1_2);					/*错误响应状态SW*/
	}
		
	/*写异常插卡记录		*/
	MF_WRPre1ErrCardRecord(pStr_CardParse);

	/*写非法插卡总次数*/
	if( (IC_ErrStatus == C_IC_IC_RST_ERR) || (IC_ErrStatus == C_IC_AUTH_ERR) || (IC_ErrStatus == C_IC_MAC_ERR) )	/*以上三种情况算非法插卡bbb-255 3.22*/
	{
		V_usDataLen = CLLawlessC_Degree;
		if(InF_Read_Data(CLawlessC_Degree, V_ucLawlessC_Degree, &V_usDataLen, &V_usDataEnCode) != C_OK)
		{
			V_ulNum = 1;			
		}
		else
		{
			/*PF_BCDAddBytes(LawlessC_Degree, buf, LawlessC_Degree, CLLawlessC_Degree);*/
		
			PF_Buffer4ToUlong32(V_ucLawlessC_Degree, &V_ulNum, 4);
			V_ulNum += 1;
		}
		
		PF_Ulong32ToBuffer4(V_ucLawlessC_Degree, &V_ulNum, 4);
		
		InF_Write_Data(C_Msg_Card, CLawlessC_Degree, V_ucLawlessC_Degree, CLLawlessC_Degree, C_W_SafeFlag);
	}
}


/*******************************************************************************
函数原型：	void		MF_Init_IC_ErrEvent(StrCardParse	*pStr_CardParse)
功能描述：	初始化异常插卡记录变量
输入参数：	*pStr_CardParse->IC_ErrEvent		:异常插卡记录的指针
输出参数：	*pStr_CardParse->IC_ErrEvent		:异常插卡记录
返回参数：	无
调用位置：
备    注：	插卡记录中完成:
			时刻、购电总次数、剩余金额、当前正、反向有功写
			卡序列号、错误信息字、操作命令头、错误响应的初始化
*******************************************************************************/
void	MF_Init_IC_ErrEvent(StrCardParse	*pStr_CardParse)
{
	uchar8		i;
	ushort16	V_usDataEnCode, V_usLen;

	
	for(i = 0; i < CLAbnorC_Note_1; i++)
	{
		pStr_CardParse->IC_ErrEvent[i] = 0;
	}
	
/*	pStr_CardParse->IC_ErrEvent[CO_CE_ErrStatus] = C_OK;*/
	
	/*读时钟,反正插卡过程中不刷新时钟*/
	V_usLen = CLDate_Time;
	InF_Read_Data(CDate_Time, &(pStr_CardParse->IC_ErrEvent[CO_CE_Clcok]), &V_usLen, &V_usDataEnCode);
	
	/*卡序列号初始化成0xFF*/
	for(i = 0; i < CL_CardNo; i++)
	{
        pStr_CardParse->IC_ErrEvent[CO_CE_CardNo + i] = 0xFF;
	}

}


/*******************************************************************************
函数原型：	void		MF_Card_SendMsgForUpdataParm(uchar8 V_ucParmType,uchar8 V_ucDestMsg)
功能描述：	发送参数更新消息
输入参数：	V_ucParmType	:更新的参数类型。
			取值		: C_ReWorkTime			时间更改
						: C_ReDemand_Cycle		需量周期更改
						: C_ReMultiRatesParm	时段费率等参数修改
						: C_ReSettle_Day1		第1结算日修改
输出参数：无
返回参数：无
调用位置：
备    注：
*******************************************************************************/
void		MF_Card_SendMsgForUpdataParm(uchar8 V_ucParmType, uchar8 V_ucDestMsg)
{
	Str_Msg_Parameter	Str_MsgParm;
	uchar8				V_ucbuf[2];
	
	Str_MsgParm.DerictAddr = V_ucDestMsg;
	Str_MsgParm.SourceAddr = C_Msg_Card;
	Str_MsgParm.Parameter = V_ucbuf;
	Str_MsgParm.Length = Pt_ParaMetersChange_Len + 1;
	V_ucbuf[0] = Pt_ParaMetersChange;
	V_ucbuf[1] = V_ucParmType;
	InF_WriteMessege(&Str_MsgParm);	
}


/*******************************************************************************
函数原型：void InF_WriteCardStatus(ushort16 V_usCardFlay)
功能描述：将卡状态字写数据层
输入参数：插卡状态字 C_CardStatusOK/C_CardStatusERR/C_CardStatusUnknow
输出参数：无
返回参数：无
调用位置：
备    注：
*******************************************************************************/
void InF_WriteCardStatus(ushort16 V_usCardFlay)
{
	uchar8	V_ucbuf[5];

	PF_Ushort16ToBuffer2(V_ucbuf, &V_usCardFlay);
	
	InF_Write_Data(C_Msg_Card, CInset_Card_State, V_ucbuf, CLInset_Card_State, C_W_SafeFlag);
}


/*******************************************************************************
函数原型：void		MF_Card_SendMsgToSettlement(void)
功能描述：修改当前套参数发送参数更新消息给结算模块
输入参数：无
输出参数：无
返回参数：无
调用位置：
备    注：
*******************************************************************************/
void		MF_Card_SendMsgToSettlement(void)
{
	Str_Msg_Parameter	Str_MsgParm;
	uchar8				V_ucbuf[5];
	
	Str_MsgParm.DerictAddr = C_Msg_SettleAccounts;		/*目的地址为结算模块*/
	Str_MsgParm.SourceAddr = C_Msg_Card;
	Str_MsgParm.Parameter = V_ucbuf;
	Str_MsgParm.Length = Pt_YearCheckDayChange_Len + 1;
	V_ucbuf[0] = Pt_YearCheckDayChange;					/*修改年结算日消息*/
	InF_WriteMessege(&Str_MsgParm);	
}



