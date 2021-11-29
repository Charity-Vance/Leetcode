
///*****************************************************************************************///
///*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     IO.c
///*Version:       V1
///*Date:          2014-3-12
///*Description:   串口配置
///*Function List: 
///*****************************************************************************************///
///*History1:      第1次修改
///*内容1. Date:
///*   	   Author:
///*       Modification:
		///***********************************************///
///*内容2. Date:
///*   	   Author:
///*       Modification:
		///*********************************************************************************///
///*History2:      第2次修改
///*内容1. Date:
///*   	   Author:
///*       Modification:
		///***********************************************///
///*内容2. Date:
///*   	   Author:
///*       Modification:
///*****************************************************************************************///

#include "IO.h"
#include "CardDrive.h"
#include "EEPROMDrive.h"
#include "FRAMDrive.h"
//#include "EsamDrive.h"
#include "FlashDrive.h"
#include "LCDDrive.h"
//#include "MeterICDrive.h"
#include "RTCDrive.h"
#include "uart.h"
#include "Public.h"

//static ulong32 SV_ulTemp_GPIO;	///*该变量用于所有寄存器的读->修改->写*///



typedef struct
{
	ulong32 portregister;		///*port口寄存器*///
	ulong32 inputmode;			///*输入模式*///
	ulong32 outputmode;			///*输出模式*///
	ulong32 outputtype;			///*输出类型:开漏或推挽*///
	ulong32 outvalue;			///*输出值:高/低*///
}Str_NCIO_Type;

///********macro pcb板号********///
//#define	C_Pcb1512			0x01			///*0.2S表的主板板号，无费控功能*///
//#define	C_Pcb1595       	0x02            ///*智能表的主板板号，有费控功能：本地和远程都有*///
///*下面的表格定义了板子上悬空口线,用于统一配置:配置为开漏输出高,并关闭上下拉*///
//#if	( C_PcbVersion == C_Pcb1512 )		/*0.2S表*///
//const Str_NCIO_Type Table_NCIO[]=
//{/*寄存器地址,输入模式,  输出模式,   推挽输出, 无上下拉,  输出低电平
//	{GPIOA_BASE,BIT7INMODE, BIT7OUTMODE, BIT7OUTPP, BIT7NOPUPD, BIT7RESET},		/*GPIOA.7*///
//	{GPIOB_BASE,BIT8INMODE, BIT8OUTMODE, BIT8OUTPP, BIT8NOPUPD, BIT8RESET},		/*GPIOB.8*///
//	{GPIOB_BASE,BIT9INMODE, BIT9OUTMODE, BIT9OUTPP, BIT9NOPUPD, BIT9RESET},		/*GPIOB.9*///
//	{GPIOB_BASE,BIT10INMODE,BIT10OUTMODE,BIT10OUTPP,BIT10NOPUPD,BIT10RESET},	/*GPIOB.10*///
//	{GPIOC_BASE,BIT0INMODE, BIT0OUTMODE, BIT0OUTPP, BIT0NOPUPD, BIT0RESET},		/*GPIOC.0*///
//	{GPIOC_BASE,BIT1INMODE, BIT1OUTMODE, BIT1OUTPP, BIT1NOPUPD, BIT1RESET},		/*GPIOC.1*///
//	{GPIOC_BASE,BIT12INMODE,BIT12OUTMODE,BIT12OUTPP,BIT12NOPUPD,BIT12RESET},	/*GPIOC.12*///
//	{GPIOC_BASE,BIT13INMODE,BIT13OUTMODE,BIT13OUTPP,BIT13NOPUPD,BIT13RESET},	/*GPIOC.13*///
//	{GPIOC_BASE,BIT14INMODE,BIT14OUTMODE,BIT14OUTPP,BIT14NOPUPD,BIT14RESET},	/*GPIOC.14*///
//	{GPIOC_BASE,BIT15INMODE,BIT15OUTMODE,BIT15OUTPP,BIT15NOPUPD,BIT15RESET},	/*GPIOC.15*///
//	{GPIOD_BASE,BIT2INMODE, BIT2OUTMODE, BIT2OUTPP, BIT2NOPUPD, BIT2RESET}		/*GPIOD.2*///
//};
//#else
const Str_NCIO_Type Table_NCIO[]=
{
//	#if	( C_Meter_Type != C_L_SmartMeter )
//	{GPIOF_BASE,BIT3INMODE, BIT3OUTMODE, BIT3OUTOD,BIT3SET},		///*GPIOF.3*///
//	{GPIOF_BASE,BIT4INMODE, BIT4OUTMODE, BIT4OUTOD,BIT4SET},		///*GPIOF.4*///
//	{GPIOF_BASE,BIT5INMODE, BIT5OUTMODE, BIT5OUTOD,BIT5SET},		///*GPIOF.5*///
//	{GPIOF_BASE,BIT6INMODE, BIT6OUTMODE, BIT6OUTOD,BIT6SET},		///*GPIOF.6*///
//	{GPIOF_BASE,BIT7INMODE, BIT7OUTMODE, BIT7OUTOD,BIT7SET},		///*GPIOF.7*///
//	{GPIOF_BASE,BIT9INMODE, BIT9OUTMODE, BIT9OUTOD,BIT9SET},		///*GPIOF.9*///
//	{GPIOA_BASE,BIT0INMODE, BIT0OUTMODE, BIT0OUTOD,BIT0SET},		///*GPIOa.0*///
//	{GPIOC_BASE,BIT1INMODE, BIT1OUTMODE, BIT1OUTOD,BIT1SET},		///*GPIOC.1*///
//	{GPIOC_BASE,BIT2INMODE, BIT2OUTMODE, BIT2OUTOD,BIT2SET},		///*GPIOC.2*///
//	#endif
//	{GPIOA_BASE,BIT15INMODE, BIT15OUTMODE, BIT15OUTOD,BIT15SET},		///*GPIOa.15*///
//	{GPIOB_BASE,BIT1INMODE, BIT1OUTMODE, BIT1OUTOD,BIT1SET},		///*GPIOB.1*///
//	{GPIOB_BASE,BIT2INMODE, BIT2OUTMODE, BIT2OUTOD,BIT2SET},		///*GPIOB.2*///
	{GPIOE_BASE,BIT2INMODE, BIT2OUTMODE, BIT2OUTOD,BIT2SET},		///*GPIOE.2*///
	{GPIOE_BASE,BIT6INMODE, BIT6OUTMODE, BIT6OUTOD,BIT6SET},		///*GPIOE.6*///
	{GPIOE_BASE,BIT7INMODE, BIT7OUTMODE, BIT7OUTOD,BIT7SET},		///*GPIOE.7*///
	{GPIOG_BASE,BIT4INMODE, BIT4OUTMODE, BIT4OUTOD,BIT4SET},		///*GPIOG.4*///
	{GPIOG_BASE,BIT7INMODE, BIT7OUTMODE, BIT7OUTOD,BIT7SET},		///*GPIOG.7*///
	{GPIOG_BASE,BIT3INMODE, BIT3OUTMODE, BIT3OUTOD,BIT3SET},		///*GPIOG.3*///
	{GPIOD_BASE,BIT2INMODE, BIT2OUTMODE, BIT2OUTOD,BIT2SET},		///*GPIOD.2*///
	{GPIOD_BASE,BIT3INMODE, BIT3OUTMODE, BIT3OUTOD,BIT3SET},		///*GPIOD.3*///
	{GPIOD_BASE,BIT4INMODE, BIT4OUTMODE, BIT4OUTOD,BIT4SET},		///*GPIOD.4*///
	{GPIOD_BASE,BIT5INMODE, BIT5OUTMODE, BIT5OUTOD,BIT5SET},		///*GPIOD.5*///
	{GPIOD_BASE,BIT6INMODE, BIT6OUTMODE, BIT6OUTOD,BIT6SET},		///*GPIOD.6*///
	{GPIOD_BASE,BIT7INMODE, BIT7OUTMODE, BIT7OUTOD,BIT7SET},		///*GPIOD.7*///
	{GPIOD_BASE,BIT8INMODE, BIT8OUTMODE, BIT8OUTOD,BIT8SET},		///*GPIOD.8*///
	{GPIOF_BASE,BIT1INMODE, BIT1OUTMODE, BIT1OUTOD,BIT1SET},		///*GPIOF.1*///
	{GPIOF_BASE,BIT2INMODE, BIT2OUTMODE, BIT2OUTOD,BIT2SET},		///*GPIOF.2*///
	{GPIOC_BASE,BIT15INMODE, BIT15OUTMODE, BIT15OUTOD,BIT15SET},		///*GPIOC.15*///
//	{GPIOE_BASE,BIT9INMODE, BIT9OUTMODE, BIT9OUTOD,BIT9SET},		///*GPIOE.9*///
};
//#endif

#define C_Table_NCIO_Len  (sizeof(Table_NCIO)/sizeof(Str_NCIO_Type))
///**************************************************************************************///
///*函数原型：void DF_InternalRelayHold(void)                                           *///
///*功能描述：底层内置继电器保持函数                  		                            *///
///*输入参数：无                                                                        *///
///*输出参数：无                                                                        *///
///*返回参数：无                                                                        *///
///*调用位置：5ms处理接口函数                                                           *///
///*功能说明：1）5ms接口函数在SV_InternalRelayActTime计时器使能的情况下进行倒计时到0时，*///
///*          调用该函数（如果这个计时器未使能，直接清零）。    	                    *///
///**************************************************************************************///
void DF_InternalRelayHold(void)
{
	Hold_InternalRelay();
}

/////**************************************************************************************///
/////*函数原型：void DF_ExternalRelayHold(void)                                           *///
/////*功能描述：底层外置继电器保持驱动函数                                                *///
/////*输入参数：无                                                                        *///
/////*输出参数：无                                                                        *///
/////*返回参数：无                                                                        *///
/////*调用位置：5ms处理接口函数                                                           *///
/////*功能说明：1）5ms接口函数在SV_ExternalRelayActTime计时器使能的情况下进行倒计时到0时，*///
/////*          调用该函数（如果这个计时器未使能，直接清零）。							*///
/////**************************************************************************************///
//void DF_ExternalRelayHold(void)
//{
//	
//}

///**************************************************************************************///
///*函数原型：uchar8 DF_RelayControl(uchar8 C_Act)										*///
///*功能描述：底层继电器驱动函数                                                        *///
///*输入参数：C_On，表示继电器闭合；C_Off，表示继电器断开。                             *///
///*输出参数：无                                                                        *///
///*返回参数：C_Ok，正确执行；C_Error，入口错误                                         *///
///*调用位置：该函数由InF_RelayAct接口函数调用                                          *///
///*备    注：1）调用该驱动函数时，只需要明确是继电器闭合还是断开                       *///
///*          2）在该驱动函数中，不分内置还是外置（因为内置负荷开关驱动I/O口线和        *///
///*             外置负荷开关I/O驱动口线是独立的，相互不影响），都进行动作。            *///
///**************************************************************************************///
uchar8 DF_RelayControl(uchar8 C_Act)
{
	uchar8 V_ucTemp = C_Error;	///*返回值置为错误：入口参数错误时才返回错误，只要入口参数正确就返回正确*///
	
	switch( C_Act )
	{
		///********************************************************///
		case C_On:									///*继电器闭合*///
		{
			SwitchOn_InternalRelay();
			SwitchOn_ExternalRelay();
			V_ucTemp = C_OK;
			break;
		}
		///********************************************************///
		case C_Off:									///*继电器断开*///
		{
			SwitchOff_InternalRelay();
			SwitchOff_ExternalRelay();
			V_ucTemp = C_OK;
			break;
		}
		///********************************************************///
		default:
			;
			break;
		///********************************************************///
	}
	
	return V_ucTemp;
}

///**************************************************************************************///
///*函数原型：uchar8 DF_GetKsyUpStatus_LowPower(void)*///
///*功能描述：低功耗下读取上翻键口线状态*///
///*输入参数：无*///
///*输出参数：无*///
///*返回参数：C_Valid，表示上翻键按下；C_Invalid，表示上翻键未按下*///
///**************************************************************************************///
uchar8 DF_GetKsyUpStatus_LowPower(void)
{
	if( IO_POWERDOWN->IDR & POWERDOWN_SELECT )
	{
		return C_Valid;		///*为高表示有电*///
	}
	else
	{
		return C_Invalid;	///*为低表示掉电*///
	}
}
///***********************************************************************************///
///**************************************************************************************///
///*函数原型：uchar8 DF_GetIOStatus_MainPower(void)										*///
///*功能描述：读取电源检测口线状态                                                      *///
///*输入参数：无											                            *///
///*输出参数：无                                                                        *///
///*返回参数：C_Valid，表示有电；C_Invalid，表示掉电                                    *///
///**************************************************************************************///
//uchar8 DF_GetIOStatus_MainPower(void)
//{
//	if( IO_POWERDOWN->IDR & POWERDOWN_SELECT )
//	{
//		return C_Valid;		///*为高表示有电*///
//	}
//	else
//	{
//		return C_Invalid;	///*为低表示掉电*///
//	}
//}
///***********************************************************************************///
///*Function：读取外部输入口线的状态
///*Description：所有用到的口线状态都读取并返回
///*Input：IOName
///*Output：无
///*Return：C_Valid、C_Invalid、C_Error
///*											C_Valid			C_Invalid		C_Error*///
///*C_KeyUp          	上翻键          		按下    		未按                   *///
///*C_KeyDown        	下翻键                  按下            未按                   *///
///*C_KeyPrg         	编程键                  按下            未按                   *///
///*C_KeyOpenCover   	开表盖                  合盖            开盖                   *///
///*C_KeyOpenTerminal	开端尾盖                合盖            开盖                   *///
///*C_CheckAuPower   	辅助电源检测            掉电            未掉电                 *///
///*C_CheckMainPower 	主电源检测              掉电            未掉电                 *///
///*C_Magnetic       	磁场检测                有磁场          无磁场                 *///
///*C_MeterICIRQ     	计量芯片IRQ中断         有中断          无中断                 *///
///*C_RelayStatus    	继电器状态检测          继电器通        断开                   *///
///*C_ModuleStatus   	模块发送状态指示        模块发送        未发送                 *///
///*C_CardStatus     	插卡状态检测            有插卡          无插卡                 *///
///*C_ExternalRelayStatus   外置继电器状态检测  电平低          电平高                 *///
///*Calls：
///*Called By：
///*Influence：该函数在中断里调用，不能在主流程中调用
///*Tips：该函数在电能表有电的时候调用，部分口线使用了上拉，这些上拉没有关闭，低功耗下几个使用上拉的口线用另外的函数
///*Others：
///***********************************************************************************///
uchar8 DF_GetIOStatus(uchar8 IOName)
{
	uchar8	V_ucReturn = C_Error;		///*返回值初始为“错误”*///
	switch( IOName )
	{
		///*******************************************************///
		case C_KeyUp:
		{
			//SET_KEYUP_INPUT();
			if( READ_KEYUP == KEYUP_SELECT )
			{
				V_ucReturn = C_Invalid;				///*口线为高表示按键未按下*///
			}
			else
			{
				V_ucReturn = C_Valid;
			}
			break;
		}
		///*******************************************************///
		case C_KeyDown:
		{
			//SET_KEYDOWN_INPUT();
			if( READ_KEYDOWN == KEYDOWN_SELECT )
			{
				V_ucReturn = C_Invalid;				///*口线为高表示按键未按下*///
			}
			else
			{
				V_ucReturn = C_Valid;
			}
			break;
		}
		///*******************************************************///
//		case C_KeyPrg:
//		{
//			//SET_KEYPRG_INPUT();
//			if( READ_KEYPRG == KEYPRG_SELECT )
//			{
//				V_ucReturn = C_Invalid;				///*口线为高表示按键未按下*///
//			}
//			else
//			{
//				V_ucReturn = C_Valid;
//			}
//			break;
//		}
		///*******************************************************///
		case C_KeyOpenCover:
		{
			//SET_KEYOPENCOVER_INPUT();
			if( READ_KEYOPENCOVER == KEYOPENCOVER_SELECT )
			{
				V_ucReturn = C_Valid;				///*口线为高表示处于合盖状态*///
			}
			else
			{
				V_ucReturn = C_Invalid;				///*口线为低表示处于开盖状态*///
			}
			break;
		}
		///*******************************************************///
		case C_KeyOpenTerminal:
		{
			//SET_KEYOPENTERMINAL_INPUT();
			if( READ_KEYOPENTERMINAL == KEYOPENTERMINAL_SELECT )
			{
				V_ucReturn = C_Valid;				///*口线为高表示处于合盖状态*///
			}
			else
			{
				V_ucReturn = C_Invalid;				///*口线为低表示处于开盖状态*///
			}
			break;
		}
		///*******************************************************///
		case C_CheckAuPower:
		{
			//SET_CHECKAUPOWER_INPUT();
			if( READ_CHECKAUPOWER == CHECKAUPOWER_SELECT )
			{
				V_ucReturn = C_Invalid;				///*口线为高表示辅助电源未掉电*///
			}
			else
			{
				V_ucReturn = C_Valid;				///*口线为低表示掉电*///
			}
			break;
		}
		///*******************************************************///
		case C_Magnetic:
		{
			//SET_MAGNETICRIGHT_INPUT();
			//SET_MAGNETICRIGHTUP_INPUT();
			//SET_MAGNETICLEFT_INPUT();
			//SET_MAGNETICLEFTUP_INPUT();
			if( 
				(READ_MAGNETICRIGHT == MAGNETICRIGHT_SELECT )
				&&(READ_MAGNETICRIGHTUP == MAGNETICRIGHTUP_SELECT )
				&&(READ_MAGNETICLEFT == MAGNETICLEFT_SELECT )
				&&(READ_MAGNETICLEFTUP == MAGNETICLEFTUP_SELECT ) 
				)
			{
				V_ucReturn = C_Invalid;				///*口线全部为高表示无磁场干扰*///
			}
			else
			{
				V_ucReturn = C_Valid;				///*任一口线为低表示有磁场干扰*///
			}
			break;
		}
		///*******************************************************///
//		case C_MeterICIRQ:
//		{
//			//SET_EMETERIRQ_INPUT();
//			if( READ_EMETERIRQ == EMETERIRQ_SELECT )
//			{
//				V_ucReturn = C_Invalid;				///*口线为高表示无中断请求*///
//			}
//			else
//			{
//				V_ucReturn = C_Valid;
//			}
//			break;
//		}
		///*******************************************************///
		case C_RelayStatus:
		{
			//SET_RELAYSTATUS_INPUT();
			if( READ_RELAYSTATUS == RELAYSTATUS_SELECT )
			{
				V_ucReturn = C_Valid;				///*口线为高表示继电器导通*///
			}
			else
			{
				V_ucReturn = C_Invalid;
			}
			break;
		}
		///*******************************************************///
		case C_ExternalRelayStatus:
		{
			if( READ_EXTERNALRELAYSTATUS == EXTERNALRELAYSTATUS_SELECT )
			{
				V_ucReturn = C_Valid;				
			}
			else
			{
				V_ucReturn = C_Invalid;         /* 20规范的外置继电器反馈是20ms的工频周波信号，无工频信号表示断 */
			}
			break;
		}       
		///*******************************************************///
		case C_ModuleStatus:
		{
			//SET_MODULESTATUS_INPUT();
			if( READ_MODULESTATUS == MODULESTATUS_SELECT )
			{
				V_ucReturn = C_Valid;				///*口线为高表示模块处于发送状态*///
			}
			else
			{
				V_ucReturn = C_Invalid;				///*口线为低表示模块处于不发送状态*///
			}
			break;
		}
		///*******************************************************///
		case C_CardStatus:
		{
			//SET_CARDSTATUS_INPUT();
			if(( READ_CARDSTATUS == CARDSTATUS_SELECT )&&( SF_Shut_RealTimeData() == C_OK ))
			{
				V_ucReturn = C_Valid;				///*口线为高表示有插卡,且闭锁时间到,才算插入有效卡片*///
			}
			else
			{
				V_ucReturn = C_Invalid;				///*口线为低表示无插卡*///
			}
			break;
		}
		///*******************************************************///
		default:
			;
		break;
		///*******************************************************///
		
	}
	return V_ucReturn;
}

///***********************************************************************************///
///*功能描述：多功能口选择秒脉冲输出*///
///***********************************************************************************///
void DF_MultiFunction_SelectSecondPulse(void)
{
	Select_SecondPulseOut();
}

///***********************************************************************************///
///*功能描述：多功能口选择需量脉冲输出*///
///***********************************************************************************///
void DF_MultiFunction_SelectDemandPulse(void)
{
	Select_DemandPulseOut();
}

///***********************************************************************************///
///*功能描述：多功能口选择需量脉冲输出*///
///***********************************************************************************///
void DF_MultiFunction_SelectRatePulse(void)
{
	Select_RatePulseOut();
}

///***********************************************************************************///
///*功能描述：多功能口关闭输出功能，即多功能口处于空闲状态，不发任何脉冲*///
///***********************************************************************************///
void DF_MultiFunction_Close(void)
{
	Close_MultiFunctionOut();
}

///***********************************************************************************///
///*功能描述：多功能口输出秒脉冲*///
///***********************************************************************************///
void DF_MultiFunction_OutputSecondPulse(void)
{
	MultiFunction_OutputSecondPulse();
}

///***********************************************************************************///
///*功能描述：多功能口输出需量脉冲*///
///***********************************************************************************///
void DF_MultiFunction_OutputDemandPulse(void)
{
	MultiFunction_OutputDemandPulse();
}

///***********************************************************************************///
///*功能描述：多功能口输出时段投切脉冲*///
///***********************************************************************************///
void DF_MultiFunction_OutputRatePulse(void)
{
	MultiFunction_OutputRatePulse();
}



///***********************************************************************************///
///*函数说明：计量芯片电源处理				    									 *///
///***********************************************************************************///
void DF_SwitchOn_EMeterIcPower(void)
{
	SwitchOn_MeterICPower();
}
void DF_SwitchOff_EMeterIcPower(void)
{
	SwitchOff_MeterICPower();
}
///***********************************************************************************///
///*函数说明：LCD电源处理				    									 *///
///***********************************************************************************///
void DF_SwitchOn_LCDPower(void)
{
	SwitchOn_LCDPower();
}
void DF_SwitchOff_LCDPower(void)
{
	SwitchOff_LCDPower();
}
///***********************************************************************************///
///*函数说明：Flash及红外电源处理				    									 *///
///***********************************************************************************///
void DF_SwitchOn_FlashPower(void)
{
	SwitchOn_FlashPower();
}
void DF_SwitchOff_FlashPower(void)
{
	SwitchOff_FlashPower();
}

///***********************************************************************************///
///*函数说明：超级电容充电控制处理			    									 *///
///***********************************************************************************///
void DF_SwitchOn_SuperCapCharge(void)
{
	SuperCapCharge_En();
}
void DF_SwitchOff_SuperCapCharge(void)
{
	SuperCapCharge_Dis();
}

///***********************************************************************************///
///*函数说明：超级电容供电控制				    									 *///
///***********************************************************************************///
void DF_SwitchOn_SuperCapPower(void)
{
	SwitchOn_SuperCapPower();
}
void DF_SwitchOff_SuperCapPower(void)
{
	SwitchOff_SuperCapPower();
}

///***********************************************************************************///
///*函数说明：6V电池防钝化处理				    									 *///
///***********************************************************************************///
void DF_SwitchOn_PreventBlunt(void)
{
//	SwitchOn_PreventBlunt();
}
void DF_SwitchOff_PreventBlunt(void)
{
//	SwitchOff_PreventBlunt();
}

/********************************************************************************
函数原型：void DF_SwitchOn_WakeUpPower(void)
         void DF_SwitchOff_WakeUpPower(void)
功能描述：6V电池供电控制：停电唤醒电源
输入参数：无
输出参数：无
调用位置：低功耗
备    注：
*********************************************************************************/
void DF_SwitchOn_WakeUpPower(void)
{
    SwitchOn_WakeUpPower();
}

void DF_SwitchOff_WakeUpPower(void)
{
	SwitchOff_WakeUpPower();
}
/********************************************************************************
函数说明：void DF_SwitchOn_WakeUpPower_NoBatter(void)	
         void DF_SwitchOff_WakeUpPower_NoBatter(void)
功能描述：6V电池供电控制：停电唤醒电源,没有停抄电池时
输入参数：无
输出参数：无
调用位置：低功耗
备    注：
*********************************************************************************/
void DF_SwitchOn_WakeUpPower_NoBatter(void)
{
    SwitchOn_WakeUpPower_NoBatter();
}

void DF_SwitchOff_WakeUpPower_NoBatter(void)
{
	SwitchOff_WakeUpPower_NoBatter();
}
///***********************************************************************************///
///*函数说明：主动上报控制：On表示有主动上报，Off表示无主动上报						 *///
///***********************************************************************************///
void DF_SwitchOn_EventOut(void)
{
	EventOut_EN();
}
void DF_SwitchOff_EventOut(void)
{
	EventOut_DIS();
}

///***********************************************************************************///
///*函数说明：模块设置控制															 *///
///***********************************************************************************///
void DF_SwitchOn_ModuleSet(void)
{
	ModuleSet_EN();
}
void DF_SwitchOff_ModuleSet(void)
{
	ModuleSet_DIS();
}

///***********************************************************************************///
///*函数说明：模块复位控制															 *///
///***********************************************************************************///
void DF_SwitchOn_ModuleEn(void)
{
	Module_EN();
}
void DF_SwitchOff_ModuleEn(void)
{
	Module_Reset();
}

///***********************************************************************************///
///*函数说明：红外接收电源控制															 *///
///***********************************************************************************///
void DF_SwitchOn_InfrarxPower(void)
{
	SwitchOn_InfrarxPower();
}
void DF_SwitchOff_InfrarxPower(void)
{
	SwitchOff_InfrarxPower();
}

///***********************************************************************************///
///*函数说明：辅助电源口线设置															 *///
///***********************************************************************************///
void DF_CHECKAUPOWER_INPUT(void)
{
	if(C_L_SmartMeter!=C_Meter_Type)///*本地表蜂鸣器与远程智能表辅助电源检测口线冲突
	{
		SET_CHECKAUPOWER_INPUT();
	}
}
///***********************************************************************************///
///*函数说明：蜂鸣器控制						 *///
///***********************************************************************************///
void DF_SwitchOn_Beeper(void)
{
	if(C_L_SmartMeter==C_Meter_Type)///*本地费控蜂鸣器
	{
		SwitchOn_Beep();
	}	
}
void DF_SwitchOff_Beeper(void)
{
	if(C_L_SmartMeter==C_Meter_Type)///*本地费控蜂鸣器
	{
		SwitchOff_Beep();
	}	
}
void DF_ReversePhase_Beeper(void)			///*蜂鸣器状态取反*///
{
	ulong32 IO_State;
	IO_State=IO_BEEP->ODR;
	if(C_L_SmartMeter==C_Meter_Type)///*本地费控蜂鸣器
	{
		if(IO_State&BEEPSET)
		{
			IO_BEEP->BSRR = BEEPRESET;
		}
		else
		{
			IO_BEEP->BSETH = BEEPSET;
		}		
	}
///	Switch_ReversePhaseBeeper();
}

///***********************************************************************************///
///*函数说明：关闭拉闸指示灯:用于掉电中断里关拉闸指示灯						 *///
///***********************************************************************************///
void DF_SwitchOff_TripLed(void)
{
	SwitchOff_TripLed();
}


///***********************************************************************************///
///*函数原型：void DF_ConfigPowerDownInterrupt)    									 *///
///*功能描述：有电期间掉电检测中断口线的配置       									 *///
///*输入参数：无                                 									 *///
///*输出参数：无                                 									 *///
///*返回参数：无                                 									 *///
///*功能说明：                                   									 *///
///*调用机制：                                   									 *///
///*备    注：                                   									 *///
///***********************************************************************************///
void DF_ConfigPowerDownInterrupt(void)
{
	ulong32 SV_ulTemp_GPIO;
	///***********掉电检测中断控制*************///
	if((ANAC->SVDCON&ANAC_SVDCON_SVDEN_ENABLE)==ANAC_SVDCON_SVDEN_ENABLE)
	{
		ANAC->SVDCON &= (~ANAC_SVDCON_SVDEN_ENABLE);
	}
	SV_ulTemp_GPIO = IO_POWERDOWN->MODER;
	SV_ulTemp_GPIO &= POWERDOWN_IN_MODE;
	SV_ulTemp_GPIO |= POWERDOWN_Ana_MODE;
	IO_POWERDOWN->MODER = SV_ulTemp_GPIO;
	IO_POWERDOWN->INEN |= POWERDOWN_INOn;
	IO_POWERDOWN->PUPDR &= POWERDOWN_NOPUPD;
//	if(!(ANAC->SVDCFG&ANAC_SVDCFG_DFEN_ENABLE))
//	{
//		ANAC->SVDCFG|=ANAC_SVDCFG_DFEN_ENABLE;
//	}
//	if(ANAC->SVDCFG&ANAC_SVDCFG_SVDMOD_INTERVAL)
//	{
//		ANAC->SVDCFG&=(~ANAC_SVDCFG_SVDMOD_INTERVAL);
//	}	
//	if((ANAC->SVDCFG & ANAC_SVDCFG_SVDLVL_SVS)!=ANAC_SVDCFG_SVDLVL_SVS)
//	{
//		ANAC->SVDCFG|=ANAC_SVDCFG_SVDLVL_SVS;
//	}
//	if((ANAC->SVDCFG & ANAC_SVDCFG_PRIE_PFIE_ENABLE)!=ANAC_SVDCFG_PFIE_ENABLE)
//	{
//		ANAC->SVDCFG &= (~ANAC_SVDCFG_PRIE_PFIE_ENABLE);
//		ANAC->SVDCFG|=ANAC_SVDCFG_PFIE_ENABLE;
//	}	
	if(ANAC->SVDCFG !=	0x000002f8)
	{
		ANAC->SVDCFG = 0x000002f8;
	}

	if((ANAC->SVDSIF&0x00000003)!=0)///*清中断标志
	{
		ANAC->SVDSIF|=0x00000003;
	}		
	
	NVIC_EnableIRQ(PowerDown_IRQn);							///*掉电中断使能*///
	ANAC->SVDCON |= ANAC_SVDCON_SVDEN_ENABLE;
}

///***********************************************************************************///
///*函数原型：void DF_ConfigNCIO(void)*///
///*功能描述：上电后对于悬空的IO的配置*///
///*          所有悬空的口线,在上电后只配置一次:推挽输出低电平,并关闭上下拉*///
///***********************************************************************************///
void DF_ConfigNCIO(void)
{
	uchar8 i;
	ulong32 buff;	/*用于读->修改->写*///
	
	for(i=0;i<C_Table_NCIO_Len;i++)
	{
		buff = ((GPIOx_Type *)Table_NCIO[i].portregister)->MODER;		/*输出*///
		buff &= Table_NCIO[i].inputmode;
		buff |= Table_NCIO[i].outputmode;
		((GPIOx_Type *)Table_NCIO[i].portregister)->MODER = buff;
		
		buff = ((GPIOx_Type *)Table_NCIO[i].portregister)->OTYPER;	/*开漏*///
		buff |= Table_NCIO[i].outputtype;
		((GPIOx_Type *)Table_NCIO[i].portregister)->OTYPER = buff;
		
		((GPIOx_Type *)Table_NCIO[i].portregister)->BSETH = Table_NCIO[i].outvalue;	/*输出高*///
	}
}

///***********************************************************************************///
///*函数原型：void InF_ConfigIOInPowerON(void)    									 *///
///*功能描述：上电后主调度、停电唤醒后IO的配置   									 *///
///*输入参数：无                                 									 *///
///*输出参数：无                                 									 *///
///*返回参数：无                                 									 *///
///*功能说明：                                   									 *///
///*调用机制：                                   									 *///
///*备    注：                                   									 *///
///***********************************************************************************///
void InF_ConfigIOInPowerON(void)
{
	///*首先将系统时钟配置给port口*///
	if(!(RCC->PERCLKCON1&RCC_PERRCCCON1_PDCCKEN_ON))
	{
		RCC->PERCLKCON1|=RCC_PERRCCCON1_PDCCKEN_ON;
	}
//	IOPACLKENABLE;
//	IOPBCLKENABLE;
//	IOPCCLKENABLE;
//	IOPDCLKENABLE;
//	IOPECLKENABLE;
//	IOPHCLKENABLE;
//	
//	EXTI->EMR = 0x00000000;
//	EXTI->IMR = 0x00000000;
//	EXTI->RTSR = 0x00000000;
//	EXTI->FTSR = 0x00000000;
	///*上电所有口线全部配置一下*///
	DF_SwitchOff_Beeper();
	InF_InitE2();
	InF_InitFRAM();
	LCD_IO_Init;
	Flash_IO_Init;
	InF_Deactivation_7816_Card();
	SET_CARDSTATUS_INPUT();
	InF_Deactivation_7816_Esam();
	SwitchOn_ExternalRelay();
	Hold_InternalRelay();
	SwitchOff_WarnOut();
	SET_KEYUP_INPUT();
	SET_KEYDOWN_INPUT();
	
//	SET_KEYPRG_INPUT();
//	RTC_IO_Init;
	
	SET_KEYOPENCOVER_INPUT();
	SET_KEYOPENTERMINAL_INPUT();
	DF_CHECKAUPOWER_INPUT();
	SET_MAGNETICRIGHT_INPUT();
	SET_MAGNETICRIGHTUP_INPUT();
	SET_MAGNETICLEFT_INPUT();
	SET_MAGNETICLEFTUP_INPUT();
	SET_RELAYSTATUS_INPUT();
	SET_EXTERNALRELRELAYSTATUS_INPUT();
	SET_MODULESTATUS_INPUT();
	SwitchOff_BackLight();
	SwitchOff_TripLed();
	SwitchOff_SuperCapPower();
	DF_SwitchOn_FlashPower();
//	SwitchOff_WakeUpPower();///*检测到有电后再关闭,包括Flash电源
	//SET_EMETERIRQ_INPUT();	
//	SwitchOff_PreventBlunt();
	Switchon_RELAYFILT();//继电器检测数字滤波

	SuperCapCharge_Dis();	
	SF_InfraModulatedSignalConfig();	
	DF_Switch_CardPower(C_Off);
	DF_Switch_CardSck(C_Off);
	DF_Switch_CardEn(C_Off);
	DF_SwitchOff_LCDPower();	
	DF_ConfigNCIO();		///*配置悬空的IO*///	
//	SwitchOn_BackLight();
//       uchar8 i;
//       for(i=0;i<200;i++)
//        {
//           __NOP();
//           __NOP();
//           __NOP();
 //          __NOP();  
 //       }
    /*目前没有用到，口线开漏输出高*/	
    SwitchOff_MODULE_PWCTL_PowerOff();
    
	DF_ConfigPowerDownInterrupt();
//	SwitchOff_BackLight();
	
	InF_JTagEnable();	///*将J-Tag口线配置为使能*///
}

///************************************************************************///
///*函数原型:void InF_JTagEnable(void)
///*函数功能:将J-Tag口线配置为使能
///*调用时机:上电初始化调用一次，停电唤醒调用一次
///************************************************************************///
void InF_JTagEnable( void )
{
//	ulong32	i;
//	i = GPIOA->MODER;
//	i &= 0x03ffffff;
//	i |= 0xa8000000;
//	GPIOA->MODER = i;
//	
//	i = GPIOA->PUPDR;
//	i &= 0x03ffffff;
//	i |= 0x64000000;
//	GPIOA->PUPDR = i;
//	
//	i = GPIOA->AFRH;
//	i &= 0x000fffff;
//	GPIOA->AFRH = i;
//	///****************************************************************///
//	i = GPIOB->MODER;
//	i &= 0xfffffc3f;
//	i |= 0x00000280;
//	GPIOB->MODER = i;
//	
//	i = GPIOB->PUPDR;
//	i &= 0xfffffc3f;
//	i |= 0x00000100;
//	GPIOB->PUPDR = i;
//	
//	i = GPIOB->OSPEEDR;
//	i |= 0x000000c0;
//	GPIOB->OSPEEDR = i;
//	
//	i = GPIOB->AFRL;
//	i &= 0xfff00fff;
//	GPIOB->AFRL = i;
}
