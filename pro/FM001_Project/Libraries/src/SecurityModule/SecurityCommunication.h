/*******************************************************************************
Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     SecurityCommunication.h
Version:       V1
Author:        jiangzs
Date:          2014-3-31
Description:   安全通信头文件
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

#ifndef	__SecurityCommunication_H
#define	__SecurityCommunication_H

#define	CLen_S_BufMaxLen					196
/*其他宏*/
#define		C_Duration_Alway		0xFFFF



/************  以下是安全模块返回参数定义************************************/
#define		C_MacLen					4				/*Mac长度*/
#define		C_PPNumOff					4				/*抄读钱包文件中购电次数偏移*/
#define		C_CustomerNumOff			(4 + 4)			/*抄读钱包文件中客户编号偏移*/
#define		C_MacOff					(4 + 4 + 6)		/*抄读钱包文件中Mac偏移*/

#define		C_HaveOpenAnAccount			0x68			/*处于开户状态*/
#define		C_HaveNoOpenAnAccount		0x00			/*处于未开户状态*/
#define		C_Judge_Method				0x01			/*判断方法*/
#define		C_Set_Method				0x02			/*设置方法*/
#define		C_O_LOpenAnAccount			1				/*本地开户状态在02FE0501中的偏移*/
#define		C_O_ROpenAnAccount			0				/*远程开户状态在02FE0501中的偏移*/


#define		C_Judge_Method_R 			0x01			/*为判断远程开户状态*/
#define		C_Set_Method_R 				0x02			/*为处理远程开户状态*/
#define		C_Judge_Method_L 			0x10			/*为判断本地开户状态*/
#define		C_Set_Method_L 				0x11			/*为处理本地开户状态*/


/************ 身份认证相关 ********************************************************/
#define		CDI_Auth					0x070000FF	/*身份认证数据标识码*/

#define		CL_Auth_CiphertextK1		8			/*密文1长度*/
#define		CL_Auth_Rand1				8			/*随机数长度*/
#define		CL_Auth_Dis_factor			8
#define		CL_Auth_Rand1_SoftCam		16

#define		CLen_Rand2					4
#define		CLen_ESAMNo					8			/*ESAM序列号长度*/
#define		CLen_AuthPTime				2

#define		C_Auth_O_CiphertextK1		0			/*身份认证报文中密文1的偏移*/
#define		C_Auth_O_Rand1				CL_Auth_CiphertextK1
													/*8: 身份认证报文中随机数1偏移*/
#define		C_Auth_O_Dis_factor			(C_Auth_O_Rand1 + CL_Auth_Rand1)
													/*16: 身份认证报文中分散因子偏移*/
#define		C_Authentication_Len		24			
													/*24: 身份认证下发数据长度*/
#define		C_R_Authentication_Len		14
													/*14: 身份认证返回数据长度*/
#define		C_R_Auth_O_Rand2			0			/*响应数据中随机数2偏移*/
#define		C_R_Auth_O_ESAMNo			CLen_Rand2	/*响应数据中ESAM序列号的偏移*/
#define		C_R_Auth_O_AuthPTime		(C_R_Auth_O_ESAMNo + CLen_ESAMNo)
													/*响应数据中身份认证有效时长偏移*/
/***********身份认证失效相关***************************************************/
#define		CDI_Auth_Invaliad			0x07000201	/*身份认证失效数据标识码*/
#define		CDI_Auth_InvaliadFF			0x070002FF	/*身份认证失效数据标识码*/

//CLCustomer_Num
//CLChargeBal_Hex_Cent
#define		CL_PurchasingE_Num			0x04			/*购电次数的数据长度*/
//CLKey_State

#define		C_AInvR_O_CustomerNo		0x00			/*客户编码的偏移*/
#define		C_AInvR_O_ChargeB_B			CLCustomer_Num	
														/*剩余金额的偏移*/
#define		C_AInvR_O_PE_Num			(C_AInvR_O_ChargeB_B + CLChargeBal_Hex_Cent)
														/*购电次数的偏移*/
#define		C_AInvR_O_Key_State			(C_AInvR_O_PE_Num + CL_PurchasingE_Num)
														/*密钥状态的偏移*/
/************* 设置身份认证有效时长相关************************************/
#define		CDI_CPTime					0x070001FF		/*设置身份认证有效时长标识码*/
#define		C_CPTime_O					0x00			/*身份认证有效时长偏移*/
#define		C_CPTime_O_Mac				CLen_AuthPTime	/*Mac的偏移*/
/************* 红外认证请求相关************************************************/
#define		CDI_IRCReq					0xF1000B00		/*红外认证请求标识码*/
#define		CL_Rand1					8
#define		CDI_IRCReq_645				0x078003FF		/*645红外认证请求标识码*/


#define		CL_RIRCReq_Rand2			8				/*红外认证请求中随机数2的长度*/
#define		CL_IRReq_Response			(CLMeter_Num_645 + CLen_ESAMNo + CL_Auth_CiphertextK1 + CL_RIRCReq_Rand2) /*698兼容645表号8字节改为6字节*/
														/*红外认证请求响应长度*/
#define		C_RIRCReq_O_M_Num			0				/*红外认证请求应答报文中表号偏移*/
#define		C_RIRCReq_O_ESAMNo			(C_RIRCReq_O_M_Num + CLMeter_Num)
														/*红外认证请求应答报文中ESAMNo偏移*/
#define		C_RIRCReq_O_RandK1			(C_RIRCReq_O_ESAMNo + CLen_ESAMNo)
														/*红外认证请求应答报文中K1 偏移*/
#define		C_RIRCReq_O_Rand2			(C_RIRCReq_O_RandK1 + CL_Auth_CiphertextK1)
														/*红外认证请求应答报文中Rand2 偏移*/
//698兼容645协议中,645协议红外请求报文偏移
#define		C_RIRCReq_O_M_Num_645		0				/*红外认证请求应答报文中表号偏移*/
#define		C_RIRCReq_O_ESAMNo_645		(C_RIRCReq_O_M_Num + CLMeter_Num_645)
														/*红外认证请求应答报文中ESAMNo偏移*/
#define		C_RIRCReq_O_RandK1_645		(C_RIRCReq_O_ESAMNo_645 + CLen_ESAMNo)
														/*红外认证请求应答报文中K1 偏移*/
#define		C_RIRCReq_O_Rand2_645		(C_RIRCReq_O_RandK1_645 + CL_Auth_CiphertextK1)
														/*红外认证请求应答报文中Rand2 偏移*/
/************* 红外认证相关*******************************************************/
#define		CDI_IR_ExtAuth				0xF1000C00		/*红外认证数据标识码*/
#define		CL_Auth_CiphertextK2		8				/*随机数2加密后的长度*/
#define		CDI_IR_ExtAuth_645			0x070003FF		/*645红外认证数据标识码*/

///************* 密钥更新相关*******************************************************///
#define		C_Max_KeyNum				CLTemp_Key_StateFF		/*最多密钥条数*/
#define		C_Default_KeyNum			20						/*国网现在是20条密钥*/
#define		CDI_UpdataKey				0x070301FF				/*密钥更新命令标识码*/

#define		CMsg_ReUpdataKey			0x68			/*重新进行密钥更新标志*/
#define		CMsg_Null					00				/*空消息标志*/

#define		C_MaxKeyNum					4				/*一次Mac 验证最多4条密钥*/
#define		CL_KeyInfo					4				/*密钥信息长度为4*/
#define		CL_Key						32				/*密钥长度*/

#define		CL_KeyWithInfo_1			36
#define		CL_KeyWithInfo_2			72
#define		CL_KeyWithInfo_3			108
#define		CL_KeyWithInfo_4			144

#define		C_UpKey_O_1					0				/*第1条密钥偏移地址,以下类似*/
#define		C_UpKey_O_2					(C_UpKey_O_1 + CL_KeyWithInfo_1)


#define		CUpKey_O_Mac_1				(C_UpKey_O_1 + CL_KeyWithInfo_1)



#define		C_UpKey_O_KeyNum_1			35				/*第1条密钥总条数的偏移地址，以下类似*/


#define		C_UpKey_O_KeyNo_1			33				/*第1条密钥的编号,以下类似*/

#define		CInfo_TestKey				0				/*在密钥信息中状态表示为测试密钥*/
#define		CInfo_OfficialKey			1				/*在密钥信息中状态表示为正式密钥*/

#define		C_UpKey_O_KeyState_1		32				/* 第1条密钥的状态，以下类似*/
#define		C_UpKey_O_Key_1				0				/*第1条密钥位置*/

/************* 状态查询相关*******************************************************/
#define		CDI_GetStatus				0x078102FF		/*状态查询*/
#define		CDI_GetStatus01				0x07810201


#define		CL_GetStatusR				26

#define		C_GetS_O_ChgBlHC			0				/*依次定义剩余金额/Mac/购电次数/客户编号/密钥状态偏移*/
#define		C_GetS_O_ChgBlHC_Mac		(C_GetS_O_ChgBlHC + CLChargeBal_Hex_Cent)
#define		C_GetS_O_PC_Num				(C_GetS_O_ChgBlHC_Mac + C_MacLen)
#define		C_GetS_O_PC_Num_Mac			(C_GetS_O_PC_Num + CL_PurchasingE_Num)
#define		C_GetS_O_C_Num				(C_GetS_O_PC_Num_Mac + C_MacLen)
#define		C_GetS_O_Key_State			(C_GetS_O_C_Num + CLCustomer_Num)

/************* 数据回抄相关*******************************************************/
/*以下为回抄标识的偏移。分别为读的长度，相对地址，文件标识，目录*/
#define		CDI_GetData					0x078001FF
#define		CDI_GetData01				0x07800101
#define		C_DExc_O_Ld					0		
#define		C_DExc_O_Offset				2
#define		C_DExc_O_FileNo				4
#define		C_DExc_O_Dir				6

#define		CL_FileDataCode				8		/*文件标识的长度*/

//响应数据的偏移
#define		C_DExcR_O_FDC				0		/*响应数据文件标识*/
#define		C_DExcR_O_Data				(C_DExcR_O_FDC + CL_FileDataCode)
												/*抄读其他文件数据开始偏移*/

#define		C_DExcR_O_ChgBlHC			(C_DExcR_O_FDC + CL_FileDataCode)
												/*回抄钱包文件时剩余金额开始的偏移*/
#define		C_DExcR_O_PC_Num			(C_DExcR_O_ChgBlHC + CLChargeBal_Hex_Cent + C_MacLen)
												/*回抄钱包文件时购电次数开始的偏移*/
/************* 明文密文写ESAM文件相关*******************************************************/
#define		C_WESAM_O_FileNo			0
#define		CL_FileNO					1
#define		C_WESAM_O_Offset			(C_WESAM_O_FileNo + CL_FileNO)
#define		CL_Offset					2
#define		C_WESAM_O_Data				(C_WESAM_O_Offset + CL_Offset)


/***********软件比对***************************************************************/
#define		CDI_CMPSoft					0x078002FF
#define		CL_SoftwareCampare_Data		0x40

/***********明文带Mac写ESAM信息文件*******************************************/
#define		CDI_WR_PlainTextMAC			0x070004FF

/***********密文带Mac写ESAM信息文件*******************************************/
#define		CDI_WR_CipherTextMAC		0x070005FF

/***********远程钱包初始化验证***********************************************/
#define		CDI_Init_Money				0x070103FF
#define		C_Init_MoneyDataLen			16					/*初始化钱包的有效数据长度*/
//以下为输入参数的数据偏移
#define		C_InitM_O_ChgBlHC			0					/*剩余金额+Mac1开始的偏移*/
#define		C_InitM_O_PC_Num			8					/*购电次数+Mac2开始的偏移*/

/***********远程开户及充值****************************************************/
#define		CDI_ROpenAnAccount			0x070101FF			/*远程开户*/
#define		CDI_RChgBL					0x070102FF			/*远程充值*/

#define		C_OpenChgBL_Len				(CLChargeBal_Hex_Cent + CL_PurchasingE_Num + C_MacLen + CLCustomer_Num + C_MacLen)
/*以下为2条命令的数据偏移(格式相同)*/
#define		C_ROAACB_O_ChgBlHC			0					/*充值金额*/
#define		C_ROAACB_O_PC_Num			4					/*购电次数*/
#define		C_ROAACB_O_Mac1				8
#define		C_ROAACB_O_CNum				12					/*客户编号*/

/************以下为文件名称定义*************************************************/
#define	C_F_MainDir			0xDF01
#define	C_F_MF				0x3F00
/*ESAM中文件号*/
#define	C_F_MasterKey		0						/*主控密钥文件*/
#define	C_F_MeterNO			1						/*表号文件*/
#define	C_F_Purse			1						/*钱包文件*/
#define	C_F_SafeID			3						/*安全标识文件*/
#define	C_F_ParmInf			4						/*参数信息文件标识码*/
#define	C_F_ElePrice		5						/*当前电价文件标识码*/
#define	C_F_ElePriceBak		6						/*备用套电价文件标识码*/
#define	C_F_OpInfo			7						/*运行信息文件*/


#define	C_F_LKeyState		5						/*本地密钥状态文件*/

#define	C_F_ParmUpdata_1	0x09					/*参数更新文件1*/
#define	C_F_ParmUpdata_2	0x10
#define	C_F_ParmUpdata_3	0x11
#define	C_F_ParmUpdata_4	0x12
#define	C_F_ParmUpdata_5	0x13

#define	C_F_ReturnFile		0x0C					/*退费文件，解密用*/

#define	C_F_MeterClear		0x14					/*清零文件*/
#define	C_F_D_E_Clear		0x17					/*需清、事件清零文件*/
#define	C_F_RemoteCtr		0x08					/*远程控制命令*/

//698兼容645，文件定义
#define	C_F_RemoteCtr_Dou645		0x82			/*远程控制命令*/
#define	C_F_MeterClear_Dou645		0x84			/*清零文件*/
#define	C_F_D_E_Clear_Dou645		0x85			/*需清、事件清零文件*/

/************以下为和卡相关的定义**********************************************/
/*********插卡过程中液晶主屏幕的提示**************************************/
#define		CType_RemainMoney		1				/*插卡液晶显示剩余电量*/
#define		CType_IC_Err			2				/*插卡液晶提示Err*/
#define		CCDsp_Duration_Alway	0xFFFF			/*插卡显示时间常显*/
#define		CCDsp_Duration_10s		0x000A
#define		CCDsp_Duration_10sL		0x0A			/*10s低位*/
#define		CCDsp_Duration_10sH		0x00

#define		CCDsp_Duration_60s		60				/*持续60s*/

/**********卡处理过程中错误代码***********************************************/
#define		C_IC_VLOW_ERR			1			/*表计电压过低176V(80%Un)*/
#define		C_IC_ESAM_RDWR_ERR		2			/*操作ESAM错误*/
#define		C_IC_ESAM_RST_ERR		3			/*ESAM复位错误*/
#define		C_IC_IC_RST_ERR			4			/*卡片复位错误:反插卡或插铁片*/
#define		C_IC_AUTH_ERR			5			/*身份认证错误(通信成功但密文不匹配)*/
#define		C_IC_EXAUTH_ERR			6			/*外部身份认证错误(通信成功但认证不通过)*/
#define		C_IC_NOFX_ERR			7			/*未发行的卡片(读卡片时返回6B00)*/
#define		C_IC_TYPE_ERR			8			/*卡类型错误*/
#define		C_IC_KER_ERR			9			/*卡片操作未授权：密钥状态不为公钥是插参数预制卡*/
#define		C_IC_MAC_ERR			10			/*MAC校验错误(6988)*/
#define		C_IC_ID_ERR				11			/*表号不一致*/
#define		C_IC_HUHAO_ERR			12			/*客户编号不一致*/
#define		C_IC_SERIAL_ERR			13			/*卡序号不一致*/
#define		C_IC_FORMAT_ERR			14			/*卡片文件格式不合法*/
#define		C_IC_NOOPEN_ERR			15			/*购电卡插入未开户电表*/
#define		C_IC_NOOPEN2_ERR		16			/*补卡插入未开户电表*/
#define		C_IC_TIMES_ERR			17			/*购电次数错误*/
#define		C_IC_NONULL_ERR			18			/*用户卡返写信息文件不为空*/
#define		C_IC_NOIN_ERR			19			/*操作卡片通讯错误(读写卡片失败)*/
#define		C_IC_PREIC_ERR			20			/*提前拔卡*/
#define		C_IC_OVERMAX_ERR		21			/*剩余金额超囤积*/

/*********异常插卡记录中长度及偏移*****************************************/
#define		CL_CardNo				CL_UserCardNo		/*卡序列号长度*/
#define		CL_CE_ErrStatus			1					/*错误信息字*/
#define		CL_7816Header			5					/*7816命令头长度*/
#define		CL_7816_SW				2					/*7816响应长度*/
#define		CL_PPNum_BCD_2			2


#define		CO_CE_Clcok				0x00										/*发生时刻*/
#define		CO_CE_CardNo			(CO_CE_Clcok + CLDate_Time)					/*卡序列号*/
#define		CO_CE_ErrStatus			(CO_CE_CardNo + CL_CardNo)					/*错误信息字*/
#define		CO_CE_7816Header		(CO_CE_ErrStatus + CL_CE_ErrStatus)			/*错误时异常7816命令头*/
#define		CO_CE_ErrSW1_2			(CO_CE_7816Header + CL_7816Header)			/*错误响应*/
/*#define		CO_CE_PNum				(CO_CE_ErrSW1_2+CL_7816_SW)	*/			/*购电次数*/
/*#define		CO_CE_RMoney			(CO_CE_PNum+CL_PPNum_BCD_2)	*/			/*剩余金额*/
/*#define		CO_CE_PAEnergy			(CO_CE_RMoney+CLChargeBal_BCD)*/		/*正向有功*/
/*#define		CO_CE_NAEnergy			(CO_CE_PAEnergy+CLPos_Ac_Tol_En_0)*/	/*反向有功*/

/*********参数/用户卡预制卡指令文件中的宏******************************/
#define		C_FC_INS				0x01			/*参数预置卡指令文件/用户卡中参数信息文件*/
													/*指令文件长度去除前4字节和后2字节*/
#define		CL_PresetCardCMD		26				/*参数预置卡指令文件数据长度*/
#define		CL_UserCardCMD			39				/*用户卡指令文件数据长度*/

#define		C_UserCardCommand		1				/*用户卡指令*/
#define		C_PresetCardCommand		6				/*参数预置卡指令*/
#define		C_OpenCard				1				/*用户卡类型为开户卡*/
#define		C_PPCard				2				/*用户卡类型为购电卡*/
#define		C_SupplementCard		3				/*用户卡类型为补卡*/

#define		CL_INS_Len				2				/*指令文件文件长度*/


#define	CLRatio_Curr_Tran_Esam		3				/*电压电流互感器变比与698不一致*/
#define	CLRatio_Vol_Tran_Esam		3
#define	CLChange_Ladder_Esam		5				/*切换时间与698不一致*/
#define	CLChange_Rate_Esam			5
#define	CLMeter_Num_Esam			6


#define		CO_INS_Start			0x00								/*起始字节68*/
#define		CO_INS_CMD				(CO_INS_Start + 1)					/*命令码*/
#define		CO_INS_Len				(CO_INS_CMD + 1)					/*长度*/
/*保留1字节*/
#define		CO_INS_UpdataPFlag		(CO_INS_Len + CL_INS_Len + 1)		/*参数更新标志*/
/*保留4字节*/
#define		CO_INS_ChgRate			(CO_INS_UpdataPFlag + 1 + 4)		/* 2套费率电价切换时间*/

#define		CO_INS_Bak_3			(CO_INS_ChgRate + 5)				/*第3处保留*/
#define		CO_INS_AlarmM1			(CO_INS_Bak_3 + 1)					/*报警金额1*/
#define		CO_INS_AlarmM2			(CO_INS_AlarmM1 + CLAlam1_Money)
#define		CO_INS_Ratio_CT			(CO_INS_AlarmM2 + CLAlam2_Money)	/*电流互感器变比*/
#define		CO_INS_Ratio_VT			(CO_INS_Ratio_CT + CLRatio_Curr_Tran_Esam)

/*以上，参数预置卡和用户卡数据项一致。以下分别为参数预置卡/用户卡最后几个数据项。
参数预置卡最后数据项*/
#define		CO_INS_PreSetC_CS		(CO_INS_Ratio_VT + CLRatio_Vol_Tran_Esam)	/*参数预置卡cs*/
#define		CO_INS_PreSetC_End		(CO_INS_PreSetC_CS + 1)						/*参数预置卡结束码*/
/*用户卡最后数据项*/
#define		CO_INS_UseC_MeterNum	(CO_INS_Ratio_VT + CLRatio_Vol_Tran_Esam)	/*表号*/
#define		CO_INS_UseC_CustNum		(CO_INS_UseC_MeterNum + 6)					/*客户编号*/
#define		CO_INS_UseC_Type		(CO_INS_UseC_CustNum + CLCustomer_Num)		/*用户卡类型*/
#define		CO_INS_UseC_CS			(CO_INS_UseC_Type + 1)						/*用户卡CS*/
#define		CO_INS_UseC_End			(CO_INS_UseC_CS + 1)						/*用户卡结束码*/
/*备注1:当更新备用费率电价时，应同时更新2套切换时间
备注2:当更新备用阶梯电价时，应同时更新2套切换时间
备注3:当更新其他标志时，指报警金额 1、报警金额 2、电流互感器变比、电压互感器变比，*/

/**********参数预置卡中的钱包文件******************************************/
#define	C_FC_MoneyInPSC					0x02				/*参数预置卡中钱包文件*/

#define	C_FC_Price_InPSC_InUse			0x03				/*参数预置卡中当前套电价文件*/
#define	C_FC_PriceBak_InPSC_InUse		0x04				/*参数预置卡中备用套电价文件*/


#define		CO_PSCM_PPMoney				00					/*预置金额偏移*/
#define		CO_PSCM_PPNum				(CO_PSCM_PPMoney + CL_PurchasingE_Num)	/*购电次数偏移*/
/**********用户卡中的钱包文件*************************************************/
#define		C_FC_MoneyInUseCard			0x02
#define		CO_UC_PPMoney				00					/*购电金额偏移*/
/**********用户卡中的返写文件*************************************************/
#define		C_FC_WRBackInUseCard		0x05
///*********参数更新相关的宏*****************************************************///
//参数更新标志
#define		C_UPType_CurRate			0x01								/*更新当前费率电价*/
#define		C_UPType_BakRate			0x02								/*更新备用套费率电价*/
#define		C_UPType_CurLadder			0x04								/*更新当前套阶梯电价*/
#define		C_UPType_BakLadder			0x08								/*更新备用套阶梯电价*/
#define		C_UPType_Other				0x80								/*更新其他标志*/
#define		C_UPType_ChgRateClock		0x20								/*两套费率电价切换时间*/
/*#define		C_UPType_ChgLadderClock	0x40*/								/*两套阶梯切换时间*/

/*6类参数长度及格式*/
/*	C_UPType_Other	1字节备用报警金额1、2+电压、电流互感器变比+MAC   共19个字节*/
/*	C_UPType_CurRate 	4字节(68 CMD Len1 Len2)当前费率电价+Mac，共136*/
/*	C_UPType_BakRate	4字节(68 CMD Len1 Len2)备用费率电价+Mac，共136*/
/*	C_UPType_ChgRateClock		2套费率电价切换时间+Mac，共9字节*/
/*	C_UPType_CurLadder	当前套电价+Mac，共68字节*/
/*	C_UPType_BakLadder		备用套电价+切换时间+Mac，共73字节*/
#define		CL_UPType_CurRate		136								/*更新当前费率电价*/
#define		CL_UPType_BakRate		136								/*更新备用套费率电价*/
#define		CL_UPType_CurLadder		68								/*更新当前套阶梯电价*/
#define		CL_UPType_BakLadder		73								/*更新备用套阶梯电价*/
#define		CL_UPType_Other			19								/*更新其他标志*/
#define		CL_UPType_ChgRateClock	9								/*两套费率电价切换时间*/
/*#define		CL_UPType_ChgRateladderClock	9	*/				/*两套阶梯电价切换时间*/
/*更新其他参数时，各项偏移*/
#define		CO_UPOther_Alam1		1								/*其他参数中报警金额1*/
#define		CO_UPOther_Alam2		(CO_UPOther_Alam1 + CLAlam1_Money)
#define		CO_UPOther_Ratio_CT		(CO_UPOther_Alam2 + CLAlam2_Money)	/*电流互感器变比*/
#define		CO_UPOther_Ratio_VT		(CO_UPOther_Ratio_CT + 3)

/*更新备用套阶梯时，最后一个切换时间的偏移*/
/*6个阶梯值(4字节)+7个阶梯电价(4字节)+4个年阶梯(3字节)*/
#define		CO_UPLadderChgClock		(6 * 4 + 7 * 4 + 4 * 3)
/*更新费率电价时，有效数据从第4字节开始*/
#define		CO_UPRate				4

/*********变量类型及变量定义**************************************************/
typedef	struct
{
	uchar8	Header[CL_7816Header];					/*小端模式*/
	ushort16	SW1_2;
}Str7816HeaderSW;
extern Str7816HeaderSW	GV_7816CMD;		

typedef	struct
{
	uchar8	CardType;										/*卡片类型*/
	uchar8	UserCardType;									/*用户卡类型*/
	uchar8	UpdateFlag;										/*参数更新标志*/
	uchar8	UserCardNull;									/*返写文件是否为空标志=C_OK:Null,C_Error为非空*/
	uchar8	CardNoEqualFlag;								/*卡号一致标志。*/
	ushort16	PreMoneyClock;								/*购电前剩余金额显示起始时刻*/
	ulong32	PPMoney;										/*购电金额或钱包初始化时预置金额*/
	ulong32	PPNum;											/*购电次数*/
	uchar8	UPType_CurRate[CL_UPType_CurRate];				/*当前套电价*/
	uchar8	UPType_BakRate[CL_UPType_BakRate];				/*备用套电价*/
	uchar8	UPType_CurLadder[CL_UPType_CurLadder];			/*当前阶梯*/
	uchar8	UPType_BakLadder[CL_UPType_BakLadder];			/*备用套阶梯*/
	uchar8	UPType_Other[CL_UPType_Other];					/*其他参数*/
	uchar8	UPType_ChgRateClock[CL_UPType_ChgRateClock];	/*费率切换时间*/
/*	uchar8	UPType_ChgLadderClock[CL_UPType_ChgRateladderClock];*/	/*阶梯切换时间	*/
	uchar8	UPType_CustNum[CLCustomer_Num+C_MacLen];		/*客户编号*/
	
	uchar8	IC_File[CLen_S_BufMaxLen];						/*卡片文件读出内容暂存。*/
															/*临时缓冲，根据情况定*/
	uchar8	IC_ErrEvent[CLAbnorC_Note_1];					/*异常插卡事件记录。小端模式*/
}StrCardParse;										
/*备注1:以上结构体中除IC_File之外，其他所有数据均符合小端模式
IC_File根据情况定,见具体的函数注释。*/

typedef struct
{
	uchar8		V_ucClientNum[8];		/* 客户编号*/
	uchar8		V_ucOpenFlag;			/* 0开户；1充值；2退费*/
	ulong32		V_ulMoney;				/* 购电金额/预置金额(a钱包初始化命令)*/
	ulong32		V_ulBuyMoneyTime;		/* 购电次数*/
	uchar8		V_CanRecharge;
}MoneyClient_Type;
extern MoneyClient_Type	MoneyClient_Table;					/*暂存需要写数据层变量*/

typedef struct
{
	ulong32 Money;				/* 购电前金额*/
	ulong32 TouzhiMoney;		/* 购电前透支金额*/
	ulong32 Num;				/* 购电前累计次数*/
}BuyMoneyRecord_Type;
extern BuyMoneyRecord_Type	BuyMoneyRecord_Table;			/*暂存购电记录变量*/

typedef struct
{
	ushort16 FreezeTimer;		/*瞬时冻结定时器*/
	ushort16 V_CRC16;	
}Str_FreezeTimerTable;
extern Str_FreezeTimerTable FreezeTimerTable;

/**************StrCardParse变量缩写********************************************/
/*IC_File中如果暂存参数预置卡钱包文件缩写
格式为预置金额+Mac1+购电次数+Mac2，为大端格式暂存*/
#define		IC_InitM_PPMoney	&pStr_CardParse->IC_File[C_InitM_O_ChgBlHC]	
#define		IC_InitM_PPNum		&pStr_CardParse->IC_File[C_InitM_O_PC_Num]
/*IC_File中钱包文件的缩写*/
/*格式为预置金额+购电次数+Mac，大端*/
#define		IC_PPMoney			&pStr_CardParse->IC_File[0]
#define		IC_PPNum			&pStr_CardParse->IC_File[4]
#define		IC_PPMac			&pStr_CardParse->IC_File[8]
/*IC_File中如果暂存指令文件时缩写*/
#define		IC_INS_Start		pStr_CardParse->IC_File[CO_INS_Start]
#define		IC_INS_CMD			pStr_CardParse->IC_File[CO_INS_CMD]	
#define		IC_INS_Len			&pStr_CardParse->IC_File[CO_INS_Len]	
#define		IC_INS_UpdataPFlag	pStr_CardParse->IC_File[CO_INS_UpdataPFlag]	
#define		IC_INS_ChgRate		&pStr_CardParse->IC_File[CO_INS_ChgRate]
#define		IC_INS_AlarmM1		&pStr_CardParse->IC_File[CO_INS_AlarmM1]
#define		IC_INS_AlarmM2		&pStr_CardParse->IC_File[CO_INS_AlarmM2]	
#define		IC_INS_Ratio_CT		&pStr_CardParse->IC_File[CO_INS_Ratio_CT]	
#define		IC_INS_Ratio_VT		&pStr_CardParse->IC_File[CO_INS_Ratio_VT]

#define		IC_INS_PreSetC_CS	pStr_CardParse->IC_File[CO_INS_PreSetC_CS]	
#define		IC_INS_PreSetC_End	pStr_CardParse->IC_File[CO_INS_PreSetC_End]	

#define		IC_INS_UseC_MeterNum	&pStr_CardParse->IC_File[CO_INS_UseC_MeterNum]
#define		IC_INS_UseC_CustNum		&pStr_CardParse->IC_File[CO_INS_UseC_CustNum]	
#define		IC_INS_UseC_Type		pStr_CardParse->IC_File[CO_INS_UseC_Type]	
#define		IC_INS_UseC_CS			pStr_CardParse->IC_File[CO_INS_UseC_CS]	
#define		IC_INS_UseC_End			pStr_CardParse->IC_File[CO_INS_UseC_End]

/*异常插卡记录的缩写*/
#define		IC_ErrStatus		pStr_CardParse->IC_ErrEvent[CO_CE_ErrStatus]
#define		IC_CardNo			&(pStr_CardParse->IC_ErrEvent[CO_CE_CardNo])
#define		IC_Err7816Header	&(pStr_CardParse->IC_ErrEvent[CO_CE_7816Header])
#define		IC_ErrSW1_2			&(pStr_CardParse->IC_ErrEvent[CO_CE_ErrSW1_2])
	

#define Plain_MAC 	0x11 		/*明文+mac加密*/
#define Secret 		0xA6 		/*密文*/
#define Secret_MAC 	0xa7 		/*密文+mac加密*/

#define Master_Address 	0xA0 	/*主站地址*/
#define Termal_Address 	0x00	/*终端地址*/

/*********** 以下为对外接口函数***********************************************/

/*安全认证*/
extern	ushort16	InF_S_Authentication(uchar8 *pV_ucData, uchar8 *pV_ucLen);	
/*身份认证失效*/
extern	ushort16  InF_S_Certification_Invaliad(uchar8 *pV_ucData,uchar8 *pV_ucLen);
/*身份认证失效时间*/
extern	ushort16	InF_S_WriteCertificationTime(uchar8	*pV_ucData);
/*红外认证请求*/
extern	ushort16  InF_S_IRCertification_Request(uchar8 *pV_ucData,uchar8 *pLen,uchar8 BufMaxLen);
/*红外认证*/
extern	ushort16  InF_S_IRCertification_Instruction(uchar8 *pV_ucData);
/*密钥Mac验证*/
extern	ushort16  InF_S_Key_V_Mac(uchar8 *pV_ucData,uchar8 DataLen,uchar8 *pV_ucMsgReupdataKey,uchar8 *pV_ucKeyNum);
/*密钥下装*/
extern	ushort16  InF_S_Key_Update (uchar8 *pV_ucData, uchar8 KeyNO);
/*密钥状态更新*/
extern	ushort16  InF_S_UpdateState (void);
/*读取ESAM中密钥状态*/
extern	ushort16  InF_S_ReadKeyStateInESAM(uchar8 *pV_ucData,uchar8 *pV_ucDataLen);
/*状态查询*/
extern	ushort16  InF_S_GetStatus(uchar8 *pV_ucData, uchar8 *pV_ucLen);
/*数据回抄*/
extern	ushort16  InF_S_DataExcerption(uchar8 *pV_ucData,uchar8 *pV_ucDataLen);
/*判断是否为1类参数*/
extern	uchar8	InF_S_Is_ParmPlainTextMAC(ulong32	V_ulDI,	uchar8 	*pV_ucDataLen);
/* 1类参数Mac验证及ESAM对应参数写*/
extern	ushort16  InF_S_WritePara_PlainTextMAC(ulong32 V_ulDI,uchar8 *pV_ucData,uchar8 V_ucDataLen);
extern	ushort16  InF_S_WriteCustermerNumMAC(ulong32 V_ulDI,uchar8 *pV_ucData,uchar8 V_ucDataLen);

/* 2类参数解密*/
extern	ushort16  InF_S_WritePara_CipherTextMAC(ulong32 V_ucDI,uchar8 *pV_ucData,uchar8 *pV_ucLength);
/*清零类*/
extern	ushort16  InF_S_MeterClear( uchar8 *pV_ucData,uchar8 *pV_ucLength);
extern	ushort16  InF_S_DemandClear( uchar8 *pV_ucData,uchar8 *pV_ucLength);
extern	ushort16  InF_S_EventClear( uchar8 *pV_ucData,uchar8 *pV_ucLength);
/*明文带Mac写ESAM*/
extern	ushort16	InF_S_WriteESAMPara_PlainTextMAC(uchar8 *pV_ucData,uchar8 V_Length);
/*密文带Mac写ESAM*/
extern	ushort16  InF_S_WriteESAMPara_CipherTextMAC (uchar8 *pV_ucData,uchar8 V_Length);
/*获取数据层密钥总条数*/
extern	uchar8	InF_Get_Key_Tol_Num(void);
/*远程负荷开关控制*/
extern	ushort16  InF_S_ControlCommand( uchar8 *pV_ucData,uchar8 *pV_ucLength);
/*写远程退费文件，返回明文退费金额+Mac*/
extern	ushort16	InF_S_WR_ReturnFile(uchar8 *pV_ucData,uchar8 V_ucLength);
extern	ushort16	InF_S_OPMoneyFile_Return(uchar8 *pV_ucData);
/***************以下函数为安全模块提供的本地表接口函数*********************/
/*远程初始化钱包*/
extern	ushort16	InF_S_InitMoney(uchar8 V_ucSrcMsg,uchar8 *pV_ucData);
/*获取ESAM中购电次数*/
#if (_DEBUG_LX)
extern	ushort16	InF_S_GetPPNum(ulong32	*pV_ulPPNum);
#endif
/*对ESAM钱包文件进行充值Mac验证及充值操作*/
extern	ushort16	InF_S_Purchase(uchar8	*pV_ucData);


/***************以下函数为安全模块提供的卡处理接口函数*********************/

/*对卡进行冷复位*/
extern	uchar8	InF_S_ColdRestCard(uchar8	*pV_ucCardNo);
/*文件选择*/
extern	uchar8	InF_S_SelectFile(uchar8 V_ucCH, ushort16 V_usFileName);
/*不带Mac读二进制文件*/
extern	uchar8	InF_SC_RDBinFileNoMac(uchar8 V_ucCH,uchar8 V_ucFileNo,uchar8 V_ucParmOffset,ushort16 V_usParmLen,uchar8 *pV_ucData);
/*判断文件格式*/
extern	uchar8	InF_SC_Judge_CardFile(uchar8	*pV_ucFile);
/*本地外部认证*/
extern	uchar8	InF_SC_L_Auth(uchar8 *pV_ucIC_CardNo);
/*让ESAM产生4字节随机数*/
extern	uchar8	InF_SC_GenerateRandToCalMac(uchar8	V_ucCH, uchar8 V_ucLength);
/*带Mac获取参数预置卡/用户卡钱包文件*/
extern	uchar8	InF_SC_Get_MFile_Card(StrCardParse	*pStr_CardParse);
/*带Mac读写参数卡(ESAM)一类参数。该类参数数据颠倒。*/
extern	uchar8	InF_SC_Backup_With_Mac(uchar8	V_ucType, uchar8 *pV_ucData);
extern	uchar8	InF_SC_BackupW_With_Mac(uchar8 	V_ucType, uchar8 *pV_ucData);
extern	void	InF_BackupData_Reversal(uchar8 	V_ucType, uchar8 *pV_ucData);

/*外部认证*/
extern	uchar8	InF_SC_CardExtAuth(uchar8	*pV_ucCardNo);
/*表号判断*/
extern	uchar8	InF_SC_Meter_Num_OK(uchar8	*pV_ucMeterNum);
/*返写文件为空判断*/
extern	uchar8	InF_SC_Is_UserCardNull(uchar8	*pV_ucFlag);
/*带Mac读取用户卡中的客户编号*/
extern	uchar8	InF_SC_GetCustNumWithMac_UseCard(uchar8 *pV_ucCustNum);
extern	void		Updata_ESAM_OpParm(uchar8	V_ucMsgNum);
extern	uchar8	InF_SC_WR_UCReturnFile(uchar8 *pV_ucCardNo);
/***************以下函数为通信模块提供的，供卡处理模块调用函数********/
/*刷新状态字3中开户状态*/
extern	void		InF_UpdateAccountStateInMeterStatus3(void);
/*写上1次购电记录*/
extern	void		InF_WRPre1PowerPurchaseRecord(ulong32 V_ulBuyMoney,uchar8 C_SafeFlag,uchar8 Flag);
/*处理远程、本地开户标志*/
extern	uchar8	InF_DealWith_L_R_OAAFlag(uchar8	Method,uchar8	Value);
/*比较数据层的客户编号*/
extern	uchar8	InF_Compare_CustomerNum(uchar8		*pCustomerNum);
extern	ushort16		InF_V_CustomerNumWithEsam(uchar8		*pCustomerNum);
extern	uchar8	Is_AllOfficialKey(void);

/*判断购电次数,充值金额*/
#define	C_PC_Num_Equal				0xFE			/* 购电次数相等*/
#define	C_Can_EPurchase 			0xFD			/*购电次数差1，金额没有超囤积*/
#define	C_MeterPC_Num_Large			0xFC			/*表内购电次数大。*/
extern	ushort16		InF_Judge_ChgBal_PC_Num(ulong32	V_ChgBal,ulong32 V_PC_Num);
/*完成充值动作*/
extern	void		InF_PurchaseDL(ulong32	PPMoney,uchar8	V_SafeFlag);


#define C_CardStatusOK		0x0001		/*插卡成功*/
#define C_CardStatusERR		0x0002		/*插卡失败*/
#define	C_CardStatusUnknow	0x0000		/*未知*/
extern	void InF_WriteCardStatus(ushort16 V_usCardFlay);
extern	uchar8 Is_AllOfficialKey(void);
extern	void Comm_SendMsgToDisp(uchar8 DispSign,uchar8	DispMode,ushort16 Duration);
#define C_ReadESAM_698	0x00
#define C_ActionESAM_698	0x01


/*ESAM动作宏定义*/
#define	C_ReadEsam_698   	0	/*读esam属性*/
#define	C_ActionEsam_698   	1	/*操作esam*/


#define		C_demand					254		/*最大需量类型*/
#define		C_demand_Com				253		/*组合无功最大需量类型,有符号*/

/*应用连接返回错误类型宏定义*/
#define     C_PasswordErr_DAR			1	/* 密码错误*/
#define     C_SymmDecodeErr_DAR			2	/* 对称解密错误 */
#define     C_DissymmDecodeErr_DAR		3	/* 非对称解密错误 */
#define     C_SignErr_DAR				4	/* 签名错误 */
#define     C_VersionErr_DAR			5	/* 协议版本不匹配*/
#define     C_ESAMCommFault_DAR			6	/* ESAM通信故障*/

#define		C_StateOfOfficialKey		CInfo_OfficialKey
#define		C_StateOfTestKey			CInfo_TestKey

#define	C_SPTNumAdd					0x01			/*SPT数加*/
#define	C_JudgeSPTVariable			0x02			/*SPT判断*/
#define	C_InitSPTVariable			0x03			/*初始化SPT变量*/

//#define	C_Init_TimerExceed10min	0x01			/*初始化的方法*/
#define		C_Set_TimerExceed10min	0x02			/*设置方法*/
#define		C_Dec_TimerExceed10min	0x03			/*扣减1的方法*/
#define		C_Sub_TimerExceed10min	0x04			/*扣减指定值的方法*/

#define	C_IRAuthTime_L	30
#define	C_IRAuthTime_H	0x00				/*红外认证30分钟*/

#define C_Remain_termal   0xF1001502		/*自扩终端剩余时间*/
/*#define C_Remain_termal_Item   0xA4*/		/*自扩*/

#define	C_SID_P1P2_01		0x01	/*更新主战会话时效门限*/
#define	C_SID_P1P2_04		0x04	/*更新终端会话时效门限*/
#define	C_SID_P1P2_05		0x05	/*更新终端地址*/
#define	C_SID_P1P2_06		0x06	/*更新终端广播计数器*/
#define	C_SID_P1P2_07		0x07	/*更新身份认证启用标志*/


extern  uchar8  INF_S_ActionEsam_698(ulong32 V_ulOAD, uchar8 *pV_ucDataBuf, ushort16 *pV_usDataLen, uchar8 *pV_ucDataOutBuf, ushort16 *pV_usDataOutLen,uchar8 V_ucClientAddr);
extern	uchar8 	InF_S_Authentication_698(uchar8 *pV_ucData, ushort16* V_usLen,uchar8 V_ucClientAddr);

extern	uchar8  INF_S_Encrypt_698(uchar8 *pV_ucAPDU, ushort16 *pV_usLen, uchar8 V_ucSecurityMode, uchar8 V_ucEncryptMode, uchar8 *pV_ucRN_Data, uchar8 *pV_ucMAC_Data, uchar8 V_ucClientAddr);
extern	uchar8	INF_S_Decrypt_698(uchar8 *pV_ucAPDU, ushort16 *pV_usLen, uchar8 V_ucSecurityMode, uchar8 *pV_ucSID_Data);

extern uchar8	InF_JudgeKeyStatus(void);
extern uchar8	Is_Buf_AllZero(uchar8	*pData,uchar8	DataLen);
extern uchar8	Comm_DealwithSPTVariable(uchar8 method);
extern void		DealWith_IR_Auth_Timer(uchar8 Method,uchar8 *pVTimer);
extern void DataReversed(ulong32 V_ulReversedMethod, uchar8 *pV_ucData, uchar8 V_ucR_ItemNum);
extern	void	DealWith_ID_Auth_T_Timer(uchar8 Method,uchar8 *pVTimer);
#endif

