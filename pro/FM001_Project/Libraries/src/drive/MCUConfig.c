
///*****************************************************************************************///
///*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     MCUConfig.c
///*Version:       V1
///*Date:          2017-9-18
///*Description:   系统配置文件：MCU配置、监控等
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


#include "Public.h"
#include "MCUConfig.h"
#include "IO.h"
#include "fm32l0xx_rcc.h"
#include "fm32l0xx_anac.h"
#include "fm32l0xx_iwdg.h"
#include "FM33A0XX.h"
#include "fm33a0xx_conf.h"
#include "Timer.h"




///*******************************************************************************///
///*=============================================================================*///
///*                         System Clock Configuration                          *///
///*=============================================================================*///
///*        System Clock source          | PLL(Fosc)                              *///
///*-----------------------------------------------------------------------------*///
///*        SYSCLK                       | 22.020096MHz                          *///
///*-----------------------------------------------------------------------------*///
///*-----------------------------------------------------------------------------*///
///*        Fosc Frequency               | 32.768kHz                             *///
///*-----------------------------------------------------------------------------*///
///*        PLL DIV                      | 2                                     *///
///*-----------------------------------------------------------------------------*///
///*        C_PLL                      	 | 100                                    *///
///*-----------------------------------------------------------------------------*///
///*        VDD                          | 3.3 V                                 *///
///*-----------------------------------------------------------------------------*///
///*        Vcore                        | 2.0 V (Range 1)                       *///
///*-----------------------------------------------------------------------------*///
///*-----------------------------------------------------------------------------*///
///*******************************************************************************///
/*******************************************************************************
功能描述：	软件延时若干毫秒
输入参数：	uchar8 mSec:		延时时间
返回参数：
函数说明：以8M(上电初始化) HRC系统时钟为基准,实际延时约为1us
*******************************************************************************/
void DF_Delay_HRCmS(ushort16 mSec) 
{
	while (mSec--)		///*
	{
			__NOP();
			__NOP();
			__NOP();
			__NOP();
			__NOP();
			__NOP();
			__NOP();
//			__NOP();	
//			__NOP();
//			__NOP();				
	}
}
/*******************************************************************************
功能描述：	切换到内部低频RCLP  32k
输入参数：
返回参数：
函数说明：	内部判断当前工作频率及电源情况。冷上电需延时500ms
*******************************************************************************/
void DF_SwitchTo_FOSC(void)
{
//		uchar8 V_i;

//		if(((RCC->SYSRCCSEL&RCC_SYSRCCSEL)!=RCC_SYSRCCSEL_RCLP)||
//	 		 ((RCC->RCLPCON&RCC_RCLPCON_RCLP)!=RCC_RCLPCON_RCLP_EN_B_ON))	///*切换系统时钟为内置低频
//	 	{
//			RCC->RCLPCON &= (~RCC_RCLPCON_RCLP);
//			RCC->RCLPCON |= RCC_RCLPCON_RCLP;///*LPRC开启
//			DF_Delay_HRCmS(1000);
//			
//			RCC->SYSRCCSEL &= (~RCC_SYSRCCSEL);
//			RCC->SYSRCCSEL |= RCC_SYSRCCSEL;
			
			///********外设时钟控制寄存器1 设置********///

//	 	}		
//	 	RCC->RCHFCON	&=	(~RCC_RCHFCON_RCHFEN_ON);///*关闭 RCHF，内部高频
//	 	RCC->PLLCON	&=	(~RCC_PLLCON_PLLEN_ON);	///*关闭pll
}
/* rchf常温校准值载入(芯片复位后自动载入8M的校准值) */
//ClkMode 1 = 8M
//ClkMode 2 = 16M
//ClkMode 3 = 24M
//ClkMode 4 = 32M
void RCC_Init_RCHF_Trim( uchar8 ClkMode )
{
	ulong32 Temp32;
	
	if( ClkMode == 1 )	//8M
	{
		Temp32 = const_rchf_Trim8;
	}
	else if( ClkMode == 2 )//16M
	{
		Temp32 = const_rchf_Trim16;
	}
	else if( ClkMode == 3 )//24M
	{
		Temp32 = const_rchf_Trim24;
	}
	else if( ClkMode == 4 )//32M
	{
		Temp32 = const_rchf_Trim32;
	}
	else//默认8M
	{
		Temp32 = const_rchf_Trim8;
	}
	
	if( ((Temp32>>16)&0x0000FFFF) == ((~Temp32)&0x0000FFFF) )	//正反码校验判断
	{
		RCC->RCHFTRIM = Temp32&0x0000007F;
	}	
	else
	{
		RCC->RCHFTRIM = 0x00000040;
	}
}
/*******************************************************************************
功能描述：	切换到HRC时钟
输入参数：
返回参数：
函数说明：	
*******************************************************************************/
void DF_SwitchTo_Fhrc(void)
{
//		uchar8 V_i;
		if((RCC->RCHFCON&RCC_RCHFCON_RCHFEN_ON)!=RCC_RCHFCON_RCHFEN_ON)
		{
			RCC->RCHFCON |= RCC_RCHFCON_RCHFEN_ON;														//*使能HRC
			DF_Delay_HRCmS(1000);
		}					
		RCC->RCHFCON	=	(RCC_RCHFCON_FSEL_16M|RCC_RCHFCON_RCHFEN_ON);			//*16M	
		DF_Delay_HRCmS(1000);
		if(RCC->SYSCLKSEL!=0x00000000)
		{
			RCC->SYSCLKSEL=0x00000000;///*APB、AHB不分频，切换为RCHF
			DF_Delay_HRCmS(1000);
		}
}
/*******************************************************************************
功能描述：	切换到PLL时钟
输入参数：
返回参数：
函数说明：	16.384MHz,开启时需要延时3ms,如之前没有开启Flf(Fosc)则需延时500ms
*******************************************************************************/
void DF_SwitchTo_Fpll(void)
{
//	uchar8	V_i;
//	
//	if ((RCC->PLLCON != (RCC_PLLCON_PLLDB32768|RCC_PLLCON_PLLEN_ON|RCC_PLLCON_PLLINSEL_XTLF|RCC_PLLCON_PLLOSEL0))	///*使能PLL
//	|| ((RCC->SYSCLKSEL&RCC_SYSRCCSEL)!=RCC_SYSRCCSEL_PLL))		///*系统时钟源选择
//	{
//		RCC->XTLFIPW = RCC_XTLFIPW_250NA;///*XTLF工作电流选择		
////			SwitchOn_BackLight();///test niu
//			DF_Delay_HRCmS(3000);///*实测3.7ms
////			SwitchOff_BackLight();///test niu
//		RCC->PLLCON = (RCC_PLLCON_PLLDB32768|RCC_PLLCON_PLLEN_ON|RCC_PLLCON_PLLINSEL_XTLF|RCC_PLLCON_PLLOSEL0);
//		
//		DF_Delay_HRCmS(3000);///*实测3.7ms
//		RCC->SYSCLKSEL &= (~RCC_SYSRCCSEL);
//		RCC->SYSCLKSEL |= RCC_SYSRCCSEL_PLL;
//	}
}
///***********************************************************************************///
///*Function：Sleep系统时钟配置*///
///*Description：切换到外置低频32.768*///
///*Input：*///
///*Output：*///
///*Calls：*///
///*Called By：*///
///*Influence：*///
///*Tips：*///
///*Others：*///
///***********************************************************************************///
void InF_SystemClockInSleepOSC(void)
{
////	HT_CMU->CLKCTRL0 &= ~0x0380;									///*关闭HRC_DET,PLL_DET,LF_DET
//
//	DF_SwitchTo_FOSC();///*切换到内置低频
}
///***********************************************************************************///
///*Function：Sleep系统时钟配置*///
///*Description：切换到HRC 2.75MHz*///
///*Input：*///
///*Output：*///
///*Calls：*///
///*Called By：*///
///*Influence：*///
///*Tips：*///
///*Others：*///
///***********************************************************************************///
void InF_SystemClockInSleepHRC(void)
{
////	HT_CMU->CLKCTRL0 &= ~0x0380;									///*关闭HRC_DET,PLL_DET,LF_DET
//
//	DF_SwitchTo_Fhrc();///*切换到HRC  8M内部高频
}
///*RCHF 校准寄存器配置 
void RCHF_Adj_EtimxCfg(void)
{
	RCHF_RecTimerClock_EN;
	RCHF_RecTimer->ETxCR = C_TIM_CR1_CLEAR;				///*控制寄存器清零*///
	RCHF_RecTimer->ETxINSEL = 0x00000004;				 ///*输入信号选择控制，1:APBCLK;2:XTLF*///
	RCHF_RecTimer->ETxPESCALE1 = 0;			///*预分频寄存器，1分频*///  
	RCHF_RecTimer->ETxPESCALE2 = 127;			///*预分频寄存器，128分频*/// 
	RCHF_RecTimer->ETxIE &= C_TIM_UIE_DIS;	///*中断禁止*///          
	RCHF_RecTimer->ETxIF |= C_TimerStatus_RESET;	///*清中断标志*///  
	RCHF_RecTimer->ETxCR = 0x00000244;		///*捕捉模式*///
	NVIC_DisableIRQ(RCHF_RecTimer_Interrupt);
}
///*xtlf的32768Hz时钟作为参考源;使用xtlf的32768Hz时钟配合定时器校准内部RCHF
///*	环境温度每变化5℃调用一次
///*本函数仅适用于APB不分频的情况
///*ClkMode 1 = 8M
///*ClkMode 2 = 16M
///*ClkMode 3 = 24M
///*ClkMode 4 = 32M
void RCHF_Adj_Proc(void)
{
	volatile ushort16 Temp16,us16_delay;
	uchar8 n,m,tempbyte,TrimBuf;	
	float DIVclkmode = 1.0;
	
	//FDETO	停振检测模块输出
	//1：XTLF未停振
	//0：XTLF停振
	if((ANAC->FDETIF&0x00000040)==0x00000000)///*XTLF 停振检测,停振
	{
		//使用测试参数		
		RCC_Init_RCHF_Trim(2);
		return;
	}
	
	RCHF_Adj_EtimxCfg();
	RCHF_RecTimer->ETxPESCALE1 = 1;			///*预分频寄存器，2分频*///  
	DIVclkmode		= 1.0;
		
	for( m=0; m<6; m++ )
	{			
		RCHF_RecTimer_START;	//启动定时器
		
		for( n=0; n<2; n++ ) //理论上判断需要3.906ms = 128/32768 s。取第2次数据认为较稳定
		{		
			Temp16 = 0;
			for(us16_delay=0;us16_delay<5000;us16_delay++)///*扑捉32.768 128分频1个周期计数值。理论计算31250 = 16/2 M*128/32768
			{
				InF_Delay_2us();
				if(RCHF_RecTimer->ETxIF & C_TimerStatus_CAPIF_RESET)///等待捕捉中断标志
				{
					Temp16 = 1; 
					break;
				}				
			}
			RCHF_RecTimer->ETxIF |= C_TimerStatus_CAPIF_RESET;		//清除捕捉中断标志
		}	
		RCHF_RecTimer_STOP;	//关闭定时器
		if( Temp16 == 0 ) 
		{
			continue;
		}			
		Temp16 = (ushort16)(RCHF_RecTimer->ETxIVR&0x0000FFFF);		//读取捕捉值
			
		if( (Temp16>(31250-120)/DIVclkmode)&&(Temp16<(31250+120)/DIVclkmode) ) //return;//修正到理想值直接返回
		{
			break;
		}
		else
		{
			TrimBuf = (uchar8)(RCC->RCHFTRIM & 0x0000007F);	//读取RCHF校准值
			if( Temp16 > 31250/DIVclkmode )	//31250 = 8M*128/32768; 156.25 = (15625*2/4*2M)*40k
			{
				Temp16 -= 31250/DIVclkmode;
				tempbyte = (uchar8)((float)Temp16/(156.25/DIVclkmode)+0.5);
				
				if( tempbyte > 0x20 ) 
				{
					tempbyte = 0x20;
				}
				
				if( TrimBuf >= tempbyte )
				{
					RCC->RCHFTRIM = (0x0000007F&(TrimBuf - tempbyte));//更新RCHF校准值
				}
				else
				{
					RCC->RCHFTRIM = 0x00;//更新RCHF校准值
				}			
			}
			else
			{
				Temp16 = (ushort16)(31250/DIVclkmode-Temp16);
				tempbyte = (uchar8)((float)Temp16/(156.25/DIVclkmode)+0.5);
				
				if( tempbyte > 0x20 ) 
				{
					tempbyte = 0x20;
				}
				
				if( (TrimBuf + tempbyte) <= 0x7F)
				{
					RCC->RCHFTRIM = (0x0000007F&(TrimBuf + tempbyte));//更新RCHF校准值
				}
				else
				{
					RCC->RCHFTRIM = 0x7F;//更新RCHF校准值
				}
			}
			
			if( m == 5 )				//未找到理想值,采用最后2次的值取平均
			{
				TrimBuf += (uchar8)(RCC->RCHFTRIM & 0x0000007F);
				RCC->RCHFTRIM = (uchar8)(TrimBuf/2.0+0.5);				
			}
		}
	}
}
///***********************************************************************************///
///*Function：有电时候的系统时钟配置*///
///*Description：上电系统默认为RCHF 8M，切换系统时钟为16M*///
///*Input：*///
///*Output：*///
///*Calls：*///
///*Called By：*///
///*Influence：*///
///*Tips：*///
///*Others：*///
///***********************************************************************************///
void InF_SystemClockInPowerOn(void)
{
	DF_SwitchTo_Fhrc();///*切换到RCHF  16MHz 。正常由RCHF 8M切换
	if(!(RCC->PERCLKCON1&RCC_PERRCCCON1_DCUCKEN_ON))
	{
		RCC->PERCLKCON1|=RCC_PERRCCCON1_DCUCKEN_ON;
	}			
	if(!(RCC->PERCLKCON1&RCC_PERRCCCON1_SCUCKEN_ON))
	{
		RCC->PERCLKCON1|=RCC_PERRCCCON1_SCUCKEN_ON;
	}	
	if(!(RCC->PERCLKCON1&RCC_PERRCCCON1_PMURCCEN_ON))
	{
		RCC->PERCLKCON1|=RCC_PERRCCCON1_PMURCCEN_ON;
	}		
	if(!(RCC->PERCLKCON1&RCC_PERRCCCON1_PDCCKEN_ON))
	{
		RCC->PERCLKCON1|=RCC_PERRCCCON1_PDCCKEN_ON;
	}
	if(!(RCC->PERCLKCON1&RCC_PERRCCCON1_EXTICKEN0_ON))
	{
		RCC->PERCLKCON1|=RCC_PERRCCCON1_EXTICKEN0_ON;
	}	
			
	ANAC->BORCON = (ANAC_BORCFG_OFF_BOR_DISABLE|ANAC_BORCFG_BOR_PDRCFG_1_7v);///*开启BOR，掉电复位电压为1.7V
	ANAC->PDRCON = (ANAC_PDRCFG_PDREN_ENABLE|ANAC_PDRCFG_PDRCFG_1_5v);
	if(RCC->XTLFIPW!=RCC_XTLFIPW_450NA)
	{
		RCC->XTLFIPW = RCC_XTLFIPW_450NA;///*XTLF工作电流选择	
	}	
	RCC_Init_RCHF_Trim(2); ///*16M,RCHF补偿调校值，载入补偿寄存器
}
///***********************************************************************************///
///*Function：有电时候的系统监控*///
///*Description：*///
///*Input：*///
///*Output：*///
///*Calls：*///
///*Called By：*///
///*Influence：*///
///*Tips：*///
///*Others：*///
///*Author:nfz*///
///***********************************************************************************///
void InF_SystemMonitor(void)
{
	ulong32 V_Data;						///*用于读->修改->写*///
	
	///*首先检测输入口线的状态*///
	///*******************************************************///
	///*上翻键*///
	V_Data = IO_KEYUP->MODER;
	if( (V_Data&KEYUP_ANALOG_MODE) != (KEYUP_ANALOG_MODE&KEYUP_IN_MODE) )
	{
		V_Data &= KEYUP_IN_MODE;
		IO_KEYUP->MODER = V_Data;
	}
	
	V_Data = IO_KEYUP->INEN;
	if((V_Data&KEYUP_IN_On)!=KEYUP_IN_On)
	{
		V_Data |= KEYUP_IN_On;
		IO_KEYUP->INEN = V_Data;
	}
		
	V_Data = IO_KEYUP->PUPDR;
	if( (V_Data&KEYUP_PULLUP) != KEYUP_PULLUP )
	{
		V_Data |= KEYUP_PULLUP;
		IO_KEYUP->PUPDR = V_Data;
	}
	///*******************************************************///
	///*下翻键*///
	V_Data = IO_KEYDOWN->MODER;
	if( (V_Data&KEYDOWN_ANALOG_MODE) != (KEYDOWN_ANALOG_MODE&KEYDOWN_IN_MODE) )
	{
		V_Data &= KEYDOWN_IN_MODE;
		IO_KEYDOWN->MODER = V_Data;
	}
	V_Data = IO_KEYDOWN->INEN;
	if((V_Data&KEYDOWN_IN_On)!=KEYDOWN_IN_On)
	{
		V_Data |= KEYDOWN_IN_On;
		IO_KEYDOWN->INEN = V_Data;
	}
	V_Data = IO_KEYDOWN->PUPDR;
	if( (V_Data&KEYDOWN_PULLUP) != KEYDOWN_PULLUP )
	{
		V_Data |= KEYDOWN_PULLUP;
		IO_KEYDOWN->PUPDR = V_Data;
	}
	///*******************************************************///
	///*编程键*///
//	V_Data = IO_KEYPRG->MODER;
//	if( (V_Data&KEYPRG_ANALOG_MODE) != (KEYPRG_ANALOG_MODE&KEYPRG_IN_MODE) )
//	{
//		V_Data &= KEYPRG_IN_MODE;
//		IO_KEYPRG->MODER = V_Data;
//	}
//	V_Data = IO_KEYPRG->INEN;
//	if((V_Data&KEYPRG_IN_On)!=KEYPRG_IN_On)
//	{
//		V_Data |= KEYPRG_IN_On;
//		IO_KEYPRG->INEN = V_Data;
//	}
//	V_Data = IO_KEYPRG->PUPDR;
//	if( (V_Data&KEYPRG_PULLUP) != KEYPRG_PULLUP )
//	{
//		V_Data |= KEYPRG_PULLUP;
//		IO_KEYPRG->PUPDR = V_Data;
//	}
	///*******************************************************///
	///*开盖键*///
	V_Data = IO_KEYOPENCOVER->MODER;
	if( (V_Data&KEYOPENCOVER_ANALOG_MODE) != (KEYOPENCOVER_ANALOG_MODE&KEYOPENCOVER_IN_MODE) )
	{
		V_Data &= KEYOPENCOVER_IN_MODE;
		IO_KEYOPENCOVER->MODER = V_Data;
	}
	V_Data = IO_KEYOPENCOVER->INEN;
	if((V_Data&KEYOPENCOVER_IN_On)!=KEYOPENCOVER_IN_On)
	{
		V_Data |= KEYOPENCOVER_IN_On;
		IO_KEYOPENCOVER->INEN = V_Data;
	}	
	V_Data = IO_KEYOPENCOVER->PUPDR;
	if( (V_Data&KEYOPENCOVER_PULLUP) != KEYOPENCOVER_PULLUP )
	{
		V_Data |= KEYOPENCOVER_PULLUP;
		IO_KEYOPENCOVER->PUPDR = V_Data;
	}
	///*******************************************************///
	///*开端钮盖键*///
	V_Data = IO_KEYOPENTERMINAL->MODER;
	if( (V_Data&KEYOPENTERMINAL_ANALOG_MODE) != (KEYOPENTERMINAL_ANALOG_MODE&KEYOPENTERMINAL_IN_MODE) )
	{
		V_Data &= KEYOPENTERMINAL_IN_MODE;
		IO_KEYOPENTERMINAL->MODER = V_Data;
	}
	V_Data = IO_KEYOPENTERMINAL->INEN;
	if((V_Data&KEYOPENTERMINAL_IN_On)!=KEYOPENTERMINAL_IN_On)
	{
		V_Data |= KEYOPENTERMINAL_IN_On;
		IO_KEYOPENTERMINAL->INEN = V_Data;
	}	
	V_Data = IO_KEYOPENTERMINAL->PUPDR;
	if( (V_Data&KEYOPENTERMINAL_PULLUP) != KEYOPENTERMINAL_PULLUP )
	{
		V_Data |= KEYOPENTERMINAL_PULLUP;
		IO_KEYOPENTERMINAL->PUPDR = V_Data;
	}
	///*******************************************************///
	///*辅助电源*///
	if(C_L_SmartMeter!=C_Meter_Type)///*本地表蜂鸣器与远程智能表辅助电源检测口线冲突
	{
		V_Data = IO_CHECKAUPOWER->MODER;
		if( (V_Data&CHECKAUPOWER_ANALOG_MODE) != (CHECKAUPOWER_ANALOG_MODE&CHECKAUPOWER_IN_MODE) )
		{
			V_Data &= CHECKAUPOWER_IN_MODE;
			IO_CHECKAUPOWER->MODER = V_Data;
		}
		V_Data = IO_CHECKAUPOWER->INEN;
		if((V_Data&CHECKAUPOWER_IN_On)!=CHECKAUPOWER_IN_On)
		{
			V_Data |= CHECKAUPOWER_IN_On;
			IO_CHECKAUPOWER->INEN = V_Data;
		}	
		V_Data = IO_CHECKAUPOWER->PUPDR;
		if(  (V_Data&CHECKAUPOWER_PULLUP) != CHECKAUPOWER_PULLUP  )
		{
			V_Data |= CHECKAUPOWER_PULLUP;
			IO_CHECKAUPOWER->PUPDR = V_Data;
		}		
	}
	///*******************************************************///
	///*磁场检测*///
	V_Data = IO_MAGNETICRIGHT->MODER;
	if( (V_Data&MAGNETICRIGHT_ANALOG_MODE) != (MAGNETICRIGHT_ANALOG_MODE&MAGNETICRIGHT_IN_MODE) )
	{
		V_Data &= MAGNETICRIGHT_IN_MODE;
		IO_MAGNETICRIGHT->MODER = V_Data;
	}
	V_Data = IO_MAGNETICRIGHT->INEN;
	if((V_Data&MAGNETICRIGHT_IN_On)!=MAGNETICRIGHT_IN_On)
	{
		V_Data |= MAGNETICRIGHT_IN_On;
		IO_MAGNETICRIGHT->INEN = V_Data;
	}	
	V_Data = IO_MAGNETICRIGHT->PUPDR;
	if( (V_Data&MAGNETICRIGHT_PULLUP) != MAGNETICRIGHT_PULLUP )
	{
		V_Data |= MAGNETICRIGHT_PULLUP;
		IO_MAGNETICRIGHT->PUPDR = V_Data;
	}
	
	V_Data = IO_MAGNETICRIGHTUP->MODER;
	if( (V_Data&MAGNETICRIGHTUP_ANALOG_MODE) != (MAGNETICRIGHTUP_ANALOG_MODE&MAGNETICRIGHTUP_IN_MODE) )
	{
		V_Data &= MAGNETICRIGHTUP_IN_MODE;
		IO_MAGNETICRIGHTUP->MODER = V_Data;
	}
	V_Data = IO_MAGNETICRIGHTUP->INEN;
	if((V_Data&MAGNETICRIGHTUP_IN_On)!=MAGNETICRIGHTUP_IN_On)
	{
		V_Data |= MAGNETICRIGHTUP_IN_On;
		IO_MAGNETICRIGHTUP->INEN = V_Data;
	}	
	V_Data = IO_MAGNETICRIGHTUP->PUPDR;
	if( (V_Data&MAGNETICRIGHTUP_PULLUP) != MAGNETICRIGHTUP_PULLUP)
	{
		V_Data |= MAGNETICRIGHTUP_PULLUP;
		IO_MAGNETICRIGHTUP->PUPDR = V_Data;
	}
	
	V_Data = IO_MAGNETICLEFT->MODER;
	if( (V_Data&MAGNETICLEFT_ANALOG_MODE) != (MAGNETICLEFT_ANALOG_MODE&MAGNETICLEFT_IN_MODE) )
	{
		V_Data &= MAGNETICLEFT_IN_MODE;
		IO_MAGNETICLEFT->MODER = V_Data;
	}
	V_Data = IO_MAGNETICLEFT->INEN; 
	if((V_Data&MAGNETICLEFT_IN_On)!=MAGNETICLEFT_IN_On)
	{
		V_Data |= MAGNETICLEFT_IN_On;
		IO_MAGNETICLEFT->INEN = V_Data;
	}		
	V_Data = IO_MAGNETICLEFT->PUPDR;
	if( (V_Data&MAGNETICLEFT_PULLUP) != MAGNETICLEFT_PULLUP )
	{
		V_Data |= MAGNETICLEFT_PULLUP;
		IO_MAGNETICLEFT->PUPDR = V_Data;
	}
	
	V_Data = IO_MAGNETICLEFTUP->MODER;
	if( (V_Data&MAGNETICLEFTUP_ANALOG_MODE) != (MAGNETICLEFTUP_ANALOG_MODE&MAGNETICLEFTUP_IN_MODE) )
	{
		V_Data &= MAGNETICLEFTUP_IN_MODE;
		IO_MAGNETICLEFTUP->MODER = V_Data;
	}
	V_Data = IO_MAGNETICLEFTUP->INEN;
	if((V_Data&MAGNETICLEFTUP_IN_On)!=MAGNETICLEFTUP_IN_On)
	{
		V_Data |= MAGNETICLEFTUP_IN_On;
		IO_MAGNETICLEFTUP->INEN = V_Data;
	}		
	V_Data = IO_MAGNETICLEFTUP->PUPDR;
	if( (V_Data&MAGNETICLEFTUP_PULLUP) != MAGNETICLEFTUP_PULLUP)
	{
		V_Data |= MAGNETICLEFTUP_PULLUP;
		IO_MAGNETICLEFTUP->PUPDR = V_Data;
	}
	///*******************************************************///
	///*计量芯片中断请求口线*///
//	V_Data = IO_EMETERIRQ->MODER;
//	if( (V_Data&EMETERIRQ_ANALOG_MODE) != (EMETERIRQ_ANALOG_MODE&EMETERIRQ_IN_MODE) )
//	{
//		V_Data &= EMETERIRQ_IN_MODE;
//		IO_EMETERIRQ->MODER = V_Data;
//	}
//	V_Data = IO_EMETERIRQ->INEN;
//	if((V_Data&EMETERIRQ_INOn)!=EMETERIRQ_INOn)
//	{
//		V_Data |= EMETERIRQ_INOn;
//		IO_EMETERIRQ->INEN = V_Data;
//	}	
//	V_Data = IO_EMETERIRQ->PUPDR;
//	if( (V_Data&EMETERIRQ_PULLUP) != EMETERIRQ_PULLUP )
//	{
//		V_Data |= EMETERIRQ_PULLUP;
//		IO_EMETERIRQ->PUPDR = V_Data;
//	}
	///*******************************************************///
	///*继电器检测口线*///
	V_Data = IO_RELAYSTATUS->MODER;
	if( (V_Data&RELAYSTATUS_ANALOG_MODE) != (RELAYSTATUS_ANALOG_MODE&RELAYSTATUS_IN_MODE) )
	{
		V_Data &= RELAYSTATUS_IN_MODE;
		IO_RELAYSTATUS->MODER = V_Data;
	}
	V_Data = IO_RELAYSTATUS->INEN;
	if((V_Data&RELAYSTATUS_IN_On)!=RELAYSTATUS_IN_On)
	{
		V_Data |= RELAYSTATUS_IN_On;
		IO_RELAYSTATUS->INEN = V_Data;
	}		
	V_Data = IO_RELAYSTATUS->PUPDR;
	if( (V_Data&(~RELAYSTATUS_NOPUPD)) != (RELAYSTATUS_SELECT&RELAYSTATUS_NOPUPD) )
	{
		V_Data &= RELAYSTATUS_NOPUPD;
		IO_RELAYSTATUS->PUPDR = V_Data;
	}
	///*******************************************************///
	///*模块发送状态检测口线*///
	V_Data = IO_MODULESTATUS->MODER;
	if( (V_Data&MODULESTATUS_ANALOG_MODE) != (MODULESTATUS_ANALOG_MODE&MODULESTATUS_IN_MODE) )
	{
		V_Data &= MODULESTATUS_IN_MODE;
		IO_MODULESTATUS->MODER = V_Data;
	}
	V_Data = IO_MODULESTATUS->INEN;
	if((V_Data&MODULESTATUS_IN_On)!=MODULESTATUS_IN_On)
	{
		V_Data |= MODULESTATUS_IN_On;
		IO_MODULESTATUS->INEN = V_Data;
	}		
	V_Data = IO_MODULESTATUS->PUPDR;
	if( (V_Data&(~MODULESTATUS_NOPUPD)) != (MODULESTATUS_SELECT&MODULESTATUS_NOPUPD) )
	{
		V_Data &= MODULESTATUS_NOPUPD;
		IO_MODULESTATUS->PUPDR = V_Data;
	}
	///*******************************************************///
	///*插卡状态检测口线*///
	V_Data = IO_CARDSTATUS->MODER;
	if( (V_Data&CARDSTATUS_ANALOG_MODE) != (CARDSTATUS_ANALOG_MODE&CARDSTATUS_IN_MODE) )
	{
		V_Data &= CARDSTATUS_IN_MODE;
		IO_CARDSTATUS->MODER = V_Data;
	}
	V_Data = IO_CARDSTATUS->INEN;
	if((V_Data&CARDSTATUS_IN_On)!=CARDSTATUS_IN_On)
	{
		V_Data |= CARDSTATUS_IN_On;
		IO_CARDSTATUS->INEN = V_Data;
	}	
	V_Data = IO_CARDSTATUS->PUPDR;
	if( (V_Data&(~CARDSTATUS_NOPUPD)) != (CARDSTATUS_SELECT&CARDSTATUS_NOPUPD) )
	{
		V_Data &= CARDSTATUS_NOPUPD;
		IO_CARDSTATUS->PUPDR = V_Data;
	}	
	///*******************************************************///
	///*TOUT输出口操作
//	V_Data = IO_MCUSECOND->MODER;
//	if((V_Data & MCUSECOND_ANALOG_MODE)!= MCUSECOND_SELECT_AF)
//	{
//		V_Data &= MCUSECOND_IN_MODE;
//		V_Data |= MCUSECOND_SELECT_AF; 
//		IO_MCUSECOND->MODER = V_Data;
//	}	
//	V_Data = IO_MCUSECOND_COMMON->FOUTSEL;
//	if((V_Data & GPIO_FOUTSEL)!=GPIO_FOUTSEL_RTCTM)
//	{
//		V_Data &= (~GPIO_FOUTSEL);
//		V_Data |= GPIO_FOUTSEL_RTCTM;
//		IO_MCUSECOND_COMMON->FOUTSEL = V_Data;
//	}
	///***************掉电检测口线******************///
	V_Data = IO_POWERDOWN->MODER;
	if( (V_Data&POWERDOWN_Ana_MODE) != POWERDOWN_Ana_MODE )
	{
		V_Data &= POWERDOWN_IN_MODE;
		V_Data |= POWERDOWN_Ana_MODE;
		IO_POWERDOWN->MODER = V_Data;
	}
}



///***************************************************************///
///*Function：void InF_WatchDog_Init(void)*///
///*Description：看门狗初始化*///
///*Calls：*///
///*Called By：*///
///*Input：*///
///*Output：*///
///*Return：*///
///*Others：*///
///***************************************************************///
void InF_WatchDog_Init(void)
{
	RCC->PERCLKCON1 |= RCC_PERRCCCON1_IWDTCKEN_ON;///*时钟使能
	FeedWatchDog();
	IWDT->IWDTCFG &= (~IWDT_IWDTOVP);
	IWDT->IWDTCFG |= IWDT_IWDTOVP_8s;///*8s
	if((IWDT->IWDTCFG&IWDT_IWDTOVP) != IWDT_IWDTOVP_8s)
	{
		IWDT->IWDTCFG &= (~IWDT_IWDTOVP);
		IWDT->IWDTCFG |= IWDT_IWDTOVP_8s;///*8s			
	}
}


///***********************************************************************************///
///*函数说明：上电操作不使用的寄存器配置一遍：配置为复位值*///
///***********************************************************************************///
void DF_ReloadRegister(void)
{
//	ulong32 V_databuf;

	///*电源管理*///
	if(PMU->LPMCFG != 0x00060000)
	{
		PMU->LPMCFG = 0x00060000;
	}
	if(PMU->WKDLYCON != 0x00000001)
	{
		PMU->WKDLYCON = 0x00000001;
	}
	if(PMU->WKPFLAG != 0x00000000)
	{
		PMU->WKPFLAG = 0x000001FF;
	}
	if(PMU->LPREIE != 0x00000000)
	{
		PMU->LPREIE = 0x00000000;
	}
	if(PMU->LPREIF != 0x00000000)
	{
		PMU->LPREIF = 0x00000003;
	}

	///*HardFault*///
	if(SCU->HDFFLAG != 0x00000000)
	{
		SCU->HDFFLAG |= 0x0000007F;
	}
	
	///*Flash*///
//	if( 0 == _DEBUG )///*正式模式,OPTBYTE寄存器配置
//	{
//		NVMIF->RCFGUS=0x0000000A;///*ACLOCK、DBRDP使能
//	}
//	else 
//	{
//		NVMIF->RCFGUS=0x0000000F;
//	}
	if(FLASH->FLSRDCON != 0x00000000)
	{
		FLASH->FLSRDCON = 0x00000000;
	}

	NVIC_DisableIRQ(NVMIF_IRQn);
	
	if(NVMIF->EPCON != 0x00000000)
	{
		NVMIF->EPCON |= 0x00000300;
	}
	
	if (NVMIF->FLSIF!=0x00000000) 
	{
		NVMIF->FLSIF=0x00000703;
	}
	///*Reset*///
	if(0 == _DEBUG)///*正式模式
	{
		RCC->RSTCFG=0x00000000;
	}
	else 
	{
		RCC->RSTCFG=0x00000003;///*EMC复位
	}
	WWDT->WWDTCON=0x000000AC;	///*禁止WWDT
	if (WWDT->WWDTIE!=0x00000000) ///*WWDT中断禁止
	{
		WWDT->WWDTIE=0x00000000;
	}
	if (WWDT->WWDTIF!=0x00000000) ///*中断标志清零
	{
		WWDT->WWDTIF=0x00000001;
	}	
	NVIC_DisableIRQ(WWDT_IRQn);
	///*Clock*///	
	if (ANAC->FDETIE!=0x00000000) ///*低频检测报警中断禁止
	{
		ANAC->FDETIE=0x00000000;
	}	
	ANAC->FDETIF|=0x00000001;///*清中断标志
	if(RCC->RCLPCON!=0)///*
	{
		RCC->RCLPCON=0;
	}		
	if(RCC->PERCLKCON1!=0x80000058)///*基本控制时钟初始化
	{
		RCC->PERCLKCON1=0x80000058;
	}	
	if(RCC->PERCLKCON2!=0x00060000)
	{
		RCC->PERCLKCON2=0x00060000;
	}
	if(RCC->PERCLKCON3!=0x00000000)
	{
		RCC->PERCLKCON3=0x00000000;
	}	
	if(RCC->PERCLKCON4!=0x00000000)
	{
		RCC->PERCLKCON4=0x00000000;
	}		
	if(RCC->MPRIL!=0x00000001) 
	{
		RCC->MPRIL=0x00000001;
	}
	///*电源电压检测*///
	if(ANAC->SVDCFG!=0x00000008) 
	{
		ANAC->SVDCFG=0x00000008;
	}	
	if(ANAC->SVDCON!=0x00000000) 
	{
		ANAC->SVDCON=0x00000000;
	}	
	ANAC->SVDSIF|=(ANAC_SVDSIF_PRF_ENABLE|ANAC_SVDSIF_PFF_ENABLE);///*标志清零		
	NVIC_DisableIRQ(SVD_IRQn);
	///*AES*///
	if(AES->AESCR!=0x00000000) 
	{
		AES->AESCR=0x00000180;
	}
	NVIC_DisableIRQ(AES_IRQn);
	///*TRNG*///
	if(TRNG->CRCCON!=0x00000000) 
	{
		TRNG->CRCCON=0x00000000;
	}	
	if(TRNG->RNGIF!=0x00000000) 
	{
		TRNG->RNGIF|=0x00000001;
	}		
	NVIC_DisableIRQ(TRNG_IRQn);
	///*模拟比较器*///
	if(ANAC->COMP1CR!=0x00000000) 
	{
		ANAC->COMP1CR &= 0xFFFFFFFE;
	}	
	if(ANAC->COMP2CR!=0x00000000) 
	{
		ANAC->COMP2CR &= 0xFFFFFFFE;
	}				
	if(ANAC->COMPICR!=0x00000040) 
	{
		ANAC->COMPICR = 0x00000040;
	}	
	if(ANAC->COMPIF!=0x00000040) 
	{
		ANAC->COMPIF |= 0x00000003;
	}	
	NVIC_DisableIRQ(COMP_IRQn);
	///*I2C*///
	if(I2C->I2CCTRL!=0x00006000) 
	{
		I2C->I2CCTRL &= 0xFFFFFFFE;
	}	
	if(I2C->I2CIR!=0x00000000)
	{
		I2C->I2CIR=0x00000001;
	}
	if(I2C->I2CERR!=0x00000000)
	{
		I2C->I2CERR=0x00000007;
	}	
	NVIC_DisableIRQ(I2C_IRQn);	
	///*UART*///	
	if(UART->UARTIE!=0x00000000)
	{
		UART->UARTIE=0x00000000;
	}	
	if(UART0->RXSTA!=0x00000000)
	{
		UART0->RXSTA=0x00000000;
	}	
	if(UART0->TXSTA!=0x00000002)
	{
		UART0->TXSTA &= 0xFFFFFF87;
	}	
	if(UART0->RTXCON!=0x00000000)
	{
		UART0->RTXCON=0x00000000;
	}	
	if(UART1->RXSTA!=0x00000000)
	{
		UART1->RXSTA=0x00000000;
	}	
	if(UART1->TXSTA!=0x00000002)
	{
		UART1->TXSTA &= 0xFFFFFF87;
	}			
	if(UART1->RTXCON!=0x00000000)
	{
		UART1->RTXCON=0x00000000;
	}	
	if(UART2->RXSTA!=0x00000000)
	{
		UART2->RXSTA=0x00000000;
	}	
	if(UART2->TXSTA!=0x00000002)
	{
		UART2->TXSTA &= 0xFFFFFF87;
	}	
	if(UART2->RTXCON!=0x00000000)
	{
		UART2->RTXCON=0x00000000;
	}	
	if(UART3->RXSTA!=0x00000000)
	{
		UART3->RXSTA=0x00000000;
	}	
	if(UART3->TXSTA!=0x00000002)
	{
		UART3->TXSTA &= 0xFFFFFF87;
	}			
	if(UART3->RTXCON!=0x00000000)
	{
		UART3->RTXCON=0x00000000;
	}	
	if(UART4->RXSTA!=0x00000000)
	{
		UART4->RXSTA=0x00000000;
	}	
	if(UART4->TXSTA!=0x00000002)
	{
		UART4->TXSTA &= 0xFFFFFF87;
	}	
	if(UART4->RTXCON!=0x00000000)
	{
		UART4->RTXCON=0x00000000;
	}	
	if(UART5->RXSTA!=0x00000000)
	{
		UART5->RXSTA=0x00000000;
	}	
	if(UART5->TXSTA!=0x00000002)
	{
		UART5->TXSTA &= 0xFFFFFF87;
	}	
	if(UART5->RTXCON!=0x00000000)
	{
		UART5->RTXCON=0x00000000;
	}
	NVIC_DisableIRQ(UART0_IRQn);
	NVIC_DisableIRQ(UART1_IRQn);
	NVIC_DisableIRQ(UART2_IRQn);
	NVIC_DisableIRQ(UART3_IRQn);
	NVIC_DisableIRQ(UART4_IRQn);
	NVIC_DisableIRQ(UART5_IRQn);		
	///*HSPI*///
	if(HSPI->SPICR1!=0x00000100)
	{
		HSPI->SPICR1=0x00000100;
	}		
	HSPI->SPICR2=0x00000054;
	if(HSPI->SPICR3!=0x00000000)
	{
		HSPI->SPICR3|=0x0000000F;///*清除标志
	}	
	if(HSPI->SPIIE!=0x00000000)
	{
		HSPI->SPIIE=0x00000000;
	}	
	if(HSPI->SPIIF!=0x00000002)
	{
		HSPI->SPIIF|=0x00000018;
	}		
	NVIC_DisableIRQ(HSPI_IRQn);
	///*SPI*///
	if(SPI1->SPICR1!=0x00000100)
	{
		SPI1->SPICR1=0x00000100;
	}		
	SPI1->SPICR2=0x00000054;
	if(SPI1->SPICR3!=0x00000000)
	{
		SPI1->SPICR3|=0x0000000F;
	}		
	if(SPI1->SPIIE!=0x00000000)
	{
		SPI1->SPIIE=0x00000000;
	}	
	if(SPI1->SPIIF!=0x00000002)
	{
		SPI1->SPIIF|=0x00000018;
	}			
	if(SPI2->SPICR1!=0x00000100)
	{
		SPI2->SPICR1=0x00000100;
	}		
	SPI2->SPICR2=0x00000054;
	if(SPI2->SPICR3!=0x00000000)
	{
		SPI2->SPICR3|=0x0000000F;
	}		
	if(SPI2->SPIIE!=0x00000000)
	{
		SPI2->SPIIE=0x00000000;
	}	
	if(SPI2->SPIIF!=0x00000002)
	{
		SPI2->SPIIF|=0x00000018;
	}		
	NVIC_DisableIRQ(SPI1_IRQn);
	NVIC_DisableIRQ(SPI2_IRQn);

	///*7816*///
	if (U78160->U7816CTRL != 0x00000000)
	{
		U78160->U7816CTRL=0x00000000;
	}	
	if (U78160->U7816IE != 0x00000000)
	{
		U78160->U7816IE=0x00000000;
	}		
	if (U78160->U7816IF != 0x00000002)
	{
		U78160->U7816IF=0x00000002;
	}		
	if (U78160->U7816ERR != 0x00000000)
	{
		U78160->U7816ERR|=0x0000000F;
	}		
	if (U78161->U7816CTRL != 0x00000000)
	{
		U78161->U7816CTRL=0x00000000;
	}	
	if (U78161->U7816IE != 0x00000000)
	{
		U78161->U7816IE=0x00000000;
	}		
	if (U78161->U7816IF != 0x00000002)
	{
		U78161->U7816IF=0x00000002;
	}		
	if (U78161->U7816ERR != 0x00000000)
	{
		U78161->U7816ERR|=0x0000000F;
	}		
	NVIC_DisableIRQ(U78161_IRQn);
	NVIC_DisableIRQ(U78160_IRQn);		
	///*DMA*///
	if (DMA->GLOBALCTRL != 0x00000000)
	{
		DMA->GLOBALCTRL=0x00000000;
	}		
	if (DMA->CH0CTRL != 0x00000000)
	{
		DMA->CH0CTRL=0x00000000;
	}		
	if (DMA->CH1CTRL != 0x00000000)
	{
		DMA->CH1CTRL=0x00000000;
	}		
	if (DMA->CH2CTRL != 0x00000000)
	{
		DMA->CH2CTRL=0x00000000;
	}		
	if (DMA->CH3CTRL != 0x00000000)
	{
		DMA->CH3CTRL=0x00000000;
	}	
	if (DMA->CH4CTRL != 0x00000000)
	{
		DMA->CH4CTRL=0x00000000;
	}	
	if (DMA->CH5CTRL != 0x00000000)
	{
		DMA->CH5CTRL=0x00000000;
	}	
	if (DMA->CH6CTRL != 0x00000000)
	{
		DMA->CH6CTRL=0x00000000;
	}	
	if (DMA->CH7CTRL != 0x00000000)
	{
		DMA->CH7CTRL=0x00000000;
	}	
	if (DMA->CHSTATUS != 0x00000000)
	{
		DMA->CHSTATUS=0x0000FFFF;
	}			
	NVIC_DisableIRQ(DMA_IRQn);
	///*CRC*///
	if (CRC->FLSCRCEN != 0x00000000)
	{
		CRC->FLSCRCEN=0x00000000;
	}	
	///*ETIME*///
	if (ETIM1->ETxCR != 0x00000000)
	{
		ETIM1->ETxCR=0x00000000;
	}	
	if (ETIM1->ETxIE != 0x00000000)
	{
		ETIM1->ETxIE=0x00000000;
	}		
	if (ETIM2->ETxCR != 0x00000000)
	{
		ETIM2->ETxCR=0x00000000;
	}	
	if (ETIM2->ETxIE != 0x00000000)
	{
		ETIM2->ETxIE=0x00000000;
	}	
	if (ETIM3->ETxCR != 0x00000000)
	{
		ETIM3->ETxCR=0x00000000;
	}	
	if (ETIM3->ETxIE != 0x00000000)
	{
		ETIM3->ETxIE=0x00000000;
	}	
	if (ETIM4->ETxCR != 0x00000000)
	{
		ETIM4->ETxCR=0x00000000;
	}	
	if (ETIM4->ETxIE != 0x00000000)
	{
		ETIM4->ETxIE=0x00000000;
	}	
	NVIC_DisableIRQ(ETIM4_IRQn);
	NVIC_DisableIRQ(ETIM2_IRQn);
	NVIC_DisableIRQ(ETIM3_IRQn);
	NVIC_DisableIRQ(ETIM1_IRQn);
	///*BTIME*///
	if (BTIM1->BTCR1 != 0x00000000)
	{
		BTIM1->BTCR1=0x00000000;
	}	
	if (BTIM1->BTCR2 != 0x00000000)
	{
		BTIM1->BTCR2=0x00000000;
	}	
	if (BTIM1->BTCFG1 != 0x00000000)
	{
		BTIM1->BTCFG1=0x00000000;
	}		
	if (BTIM1->BTCFG2 != 0x00000000)
	{
		BTIM1->BTCFG2=0x00000000;
	}	
	if (BTIM1->BTIE != 0x00000000)
	{
		BTIM1->BTIE=0x00000000;
	}		
	if (BTIM2->BTCR1 != 0x00000000)
	{
		BTIM2->BTCR1=0x00000000;
	}	
	if (BTIM2->BTCR2 != 0x00000000)
	{
		BTIM2->BTCR2=0x00000000;
	}	
	if (BTIM2->BTCFG1 != 0x00000000)
	{
		BTIM2->BTCFG1=0x00000000;
	}		
	if (BTIM2->BTCFG2 != 0x00000000)
	{
		BTIM2->BTCFG2=0x00000000;
	}	
	if (BTIM2->BTIE != 0x00000000)
	{
		BTIM2->BTIE=0x00000000;
	}		
	NVIC_DisableIRQ(BTIM1_IRQn);
	NVIC_DisableIRQ(BTIM2_IRQn);
	///*LPTIME*///
	if (LPTIM->LPTIE != 0x00000000)
	{
		LPTIM->LPTIE=0x00000000;
	}	
	if (LPTIM->LPTIF != 0x00000000)
	{
		LPTIM->LPTIF|=0x00000007;
	}				
	if (LPTIM->LPTCTRL != 0x00000000)
	{
		LPTIM->LPTCTRL=0x00000000;
	}	
	NVIC_DisableIRQ(LPTIM_IRQn);
	///*RTC*///
	if (RTC->RTCIE != 0x00000000)
	{
		RTC->RTCIE=0x00000000; 
	}	
	if (RTC->RTCIF != 0x00000000)
	{
		RTC->RTCIF|=0x00001FFF;
	}		
	if (RTC->STAMPEN != 0x00000000)
	{
		RTC->STAMPEN=0x00000000;
	}						
	NVIC_DisableIRQ(RTC_IRQn);				
	///*LCD*///
	if (LCD->DISPCTRL != 0x00000000)
	{
		LCD->DISPCTRL=0x00000000;
	}	
	if (LCD->LCDTEST != 0x00000000)
	{
		LCD->LCDTEST=0x00000000;
	}		
	if (LCD->DISPIE != 0x00000000)
	{
		LCD->DISPIE=0x00000000;
	}
	if (LCD->DISPIF != 0x00000000)
	{
		LCD->DISPIF=0x00000000;
	}	
	if (LCD->COM_EN != 0x00000000)
	{
		LCD->COM_EN&=0xFFFFFFF0;
	}
	if (LCD->SEG_EN0 != 0x00000000)
	{
		LCD->SEG_EN0=0x00000000;
	}
	if (LCD->SEG_EN1 != 0x00000000)
	{
		LCD->SEG_EN1=0x00000000;
	}
	if (LCD->LCDBSTCON != 0x00000040)
	{
		LCD->SEG_EN1=0x00000040;
	}
	NVIC_DisableIRQ(LCD_IRQn);
	///*ADC*///			
	if (ANAC->ADCCON != 0x00000000)
	{
		ANAC->ADCCON=0x00000000;
	}	
	if (ANAC->ADCIF != 0x00000000)
	{
		ANAC->ADCIF|=0x00000001;
	}					
	NVIC_DisableIRQ(ADC_IRQn);
	///*IO*///
	if (GPIO->EXTI0_SEL != 0xFFFF0000)
	{
		GPIO->EXTI0_SEL = 0xFFFF0000;
	}					
	if (GPIO->EXTI1_SEL != 0xFFFF0000)
	{
		GPIO->EXTI1_SEL = 0xFFFF0000;
	}	
	if (GPIO->EXTI2_SEL != 0xFFFF0000)
	{
		GPIO->EXTI2_SEL = 0xFFFF0000;
	}	
	if (GPIO->EXTI0IF != 0x00000000)
	{
		GPIO->EXTI0IF |= 0x000000FF;
	}	
	if (GPIO->EXTI1IF != 0x00000000)
	{
		GPIO->EXTI1IF |= 0x000000FF;
	}
	if (GPIO->EXTI2IF != 0x00000000)
	{
		GPIO->EXTI2IF |= 0x000000FF;
	}		
	if (GPIO->HDSEL != 0x00000000)
	{
		GPIO->HDSEL = 0x00000000;
	}	
	if (GPIO->IODF != 0x00000000)
	{
		GPIO->IODF = 0x00000000;
	}	
	if (GPIO->PINWKEN != 0x00000000)
	{
		GPIO->PINWKEN = 0x00000000;
	}					
	NVIC_DisableIRQ(GPIO_IRQn);	
	///*STK*///
	SysTick->CTRL = 0;
	SysTick->LOAD = 0;
	SysTick->VAL = 0;
	NVIC_DisableIRQ(SysTick_IRQn);	
}

/*******************************************************************************
功能描述：	没有应用中断服务程序
*******************************************************************************/
void WWDT_IRQHandler(void)
{
	WWDT->WWDTIF|=0x00000001;
	NVIC_DisableIRQ(WWDT_IRQn);
} 
void FLASH_IRQHandler(void)
{
	NVMIF->FLSIF|=0x00000703;
	NVIC_DisableIRQ(NVMIF_IRQn);
} 
void FDET_IRQHandler(void)
{
	ANAC->FDETIF|=0x00000001;///*清中断标志
	NVIC_DisableIRQ(FDET_IRQn);
}
void ADC_IRQHandler(void)
{
	ANAC->ADCIF|=0x00000001;
	NVIC_DisableIRQ(ADC_IRQn);
}
void HSPI_IRQHandler(void)
{
	HSPI->SPIIF|=0x00000018;
	NVIC_DisableIRQ(HSPI_IRQn);
}
void SPI1_IRQHandler(void)
{
	SPI1->SPIIF|=0x00000018;
	NVIC_DisableIRQ(SPI1_IRQn);
}
void SPI2_IRQHandler(void)
{
	SPI2->SPIIF|=0x00000018;
	NVIC_DisableIRQ(SPI2_IRQn);
}
void UART2_IRQHandler(void)
{
	UART->UARTIF=0x00000030;
	NVIC_DisableIRQ(UART2_IRQn);
}
void UART3_IRQHandler(void)
{
	UART->UARTIF =0x000000C0;
	NVIC_DisableIRQ(UART3_IRQn);
}
//void UART5_IRQHandler(void)
//{
//	UART->UARTIF|=0x00000C00;
//	NVIC_DisableIRQ(UART5_IRQn);
//}
void U78160_IRQHandler(void)
{
	U78160->U7816ERR|=0x0000000F;
	NVIC_DisableIRQ(U78160_IRQn);
}
void U78161_IRQHandler(void)
{
	U78161->U7816ERR|=0x0000000F;
	NVIC_DisableIRQ(U78161_IRQn);
}
void I2C_IRQHandler(void)
{
	I2C->I2CERR|=0x00000007;
	NVIC_DisableIRQ(I2C_IRQn);
}
void LCD_IRQHandler(void)
{
	LCD->DISPIF|=0x00000003;
	NVIC_DisableIRQ(LCD_IRQn);
}
void AES_IRQHandler(void)
{
	AES->AESIF|=0x00000007;
	NVIC_DisableIRQ(AES_IRQn);
}
void DMA_IRQHandler(void)
{
	DMA->CHSTATUS=0x0000FFFF;
	NVIC_DisableIRQ(DMA_IRQn);
}
void TRNG_IRQHandler(void)
{
	TRNG->RNGIF|=0x00000001;
	NVIC_DisableIRQ(TRNG_IRQn);
}
void COMP_IRQHandler(void)
{
	ANAC->COMPIF |= 0x00000003;
	NVIC_DisableIRQ(COMP_IRQn);
}
void RTC_IRQHandler(void)
{
	if (RTC->RTCIF != 0x00000000)
	{
		RTC->RTCIF|=0x00001FFF;
	}
}


void HardFault_Handler(void)
{
	///*发生硬件故障,直接复位单片机*////
	while(1);		///*根据矩泉推荐此处采用看门狗复位*///
}
///***********************************************************************************///
///*函数原型：void InF_ReadMCU(ulong32 V_Addr,uchar8  * PV_Data,uchar8 V_Len)                            						*///
///*功能描述：读MCU相关信息                                                                             													*///
///*输入参数：                                                                                                                    *///
///    uchar8  * PV_Data:读数据缓存；                                                                                             *///
///    uchar8  V_Len：读数据长度；                                                                                                *///                                                                  										*///
///    ulong32 V_Addr：自扩标识码                                                                                          				*///
///*输出参数：无                                                                                                                  *///
///*返回参数：无；                                                                                                                *///
///*功能说明：                                                                                                                    *///
///*调用机制：                                                                                                                    *///
///*备    注：                                                                                                                    *///
///***********************************************************************************///  
void InF_ReadMCU(ulong32 V_Addr,uchar8  * PV_Data,uchar8 V_Len)
{
//	switch(V_Addr)
//	{
//		case	CMCU_Version_Num:
//		{
//				PV_Data[0]=(uchar8)HT_CMU->CHIPID;
//				PV_Data[1]=(uchar8)(HT_CMU->CHIPID>>8);
//				break;
//		}
//		default:
//			break;
//	}
}

/****************************************************************************
*函数原型 	InF_Enable_Flash_CLK
*函数功能	使能codeflash时钟
*输入参数	
*输出参数 	无
*返回参数	无
*全局变量 	
*函数备注	
****************************************************************************/
void InF_Enable_Flash_CLK(void)	
{
	RCC->PERCLKCON2 |= RCC_PERRCCCON2_FLSCKE_ON;
}

/****************************************************************************
*函数原型 	InF_Disable_Flash_CLK
*函数功能	关闭codeflash时钟
*输入参数	
*输出参数 	无
*返回参数	无
*全局变量 	
*函数备注	
****************************************************************************/
void InF_Disable_Flash_CLK(void)	
{
	RCC->PERCLKCON2 &= (~RCC_PERRCCCON2_FLSCKE_ON);
}

/****************************************************************************
*函数原型 	InF_Reset_MCU
*函数功能	复位
*输入参数	
*输出参数 	无
*返回参数	无
*全局变量 	
*函数备注	
****************************************************************************/
void InF_Reset_MCU(void)	
{
	RCC->SOFTRST = 0x5C5CAABB;
}

