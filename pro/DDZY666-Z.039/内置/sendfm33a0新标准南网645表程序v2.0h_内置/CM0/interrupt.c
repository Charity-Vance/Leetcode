#include "ex_var.h"
#include "ex_func.h"
#include "FM32L0XX.h"  
#include <string.h>
#include <stdio.h>


void HardFault_Handler(void) 
{
	RAMREG3 = 0x55;		//上电清零、休眠唤醒时置0xaa
	
	Clear_W_Wdt();
	PMU->LPMCFG = 2;
	__WFI();
	while(1);
}  

//WWDT中断服务程序,最高优先级
void WWDT_IRQHandler(void)         
{
	WWDT->WWDTIF = 0x01;//清中断标志
	Clear_W_Wdt();
} 

//定时时间4000us,
void ETIMER2_IRQHandler(void)
{
	unsigned char Ch;
	unsigned int i;

	ETIMER2->ETxIF = 0x03;//清中断标志
	
	if( VectorTimer == 0 ) VectorTimer  = ms_timer_delay;
	if( VectorTimer == 1 ) run_readrtc_flag = 1;	//允许读时钟
	if( (VectorTimer == 50) || (((VectorTimer == 20)||(VectorTimer == 80))&&display_rtc_flag) ) {run_display_flag = 1;}//允许刷新显示
	if( VectorTimer == 100 )
	{
		run_relaychk_flag = 1;	//允许继电器检测
		RELAYCTRLON;		//打开控制电平
	}
	VectorTimer--;
	
	DisKeySamp<<=1;
	if(DISKEY_N)  DisKeySamp++;	//显示按键去抖判断
	
	//ADC处理
	if((Adcctrl.Status & B0000_0011)&&(ANAC->ADCIF&1))
	{	
		ADCResultArr.Buffer[ADCResultArr.ReadCount&0x1F] = ANAC->ADCDATA&0x000007FF;
		ADCResultArr.ReadCount++;

		//转换64次取后面32次以保证转换数据准确性
		if(ADCResultArr.ReadCount >= 64)		
		{
			if ( Adcctrl.Status == B0000_0001 ) 
			{
				Adcctrl.Status = B0001_0000;//电池adc结束
			}
			else
			{
				Adcctrl.Status = B0010_0000;//温度adc结束
			}
		}
	}
	
	if ( Shiduanctrl.Timer != 0 ) //时段投切输出脉冲
	{
		Shiduanctrl.Timer--;
	}
	if( (Shiduanctrl.Timer == 0) && (Outputtype==0x02) ) SHIDUANCTRL_OFF;
		
	if( Relay_Mode != 0x55 )//内置继电器
	{
		if ( Relayctrl.Timer != 0 ) 
		{
			Relayctrl.Timer--;
		}
		if( Relayctrl.Timer == 0 ) {RELAYOFF1; __NOP(); RELAYOFF2;}//磁保持继电器无效
	}
	else
	{
		if(Mode.Feature1&0x01)//脉冲方式
		{
			if ( Relayctrl.Timer != 0 ) 
			{
				Relayctrl.Timer--;
			}
			if( relay_status_flag && (Relayctrl.Timer == 0) ) {RELAYOFF3;}//
		}
		else Relayctrl.Timer = 0;
	}
	
	if ( Resetworking_Timer != 0 ) 
	{
		Resetworking_Timer--;
	}
	if( Resetworking_Timer == 0 )
	{
		PLC_RST1;
	}

	if( Plusefiltertimer && (Plusefiltertimer <= Def_Plusefiltertimer) && (ACTIVEP_P))//脉冲毫秒去抖判断
	{
		Plusefiltertimer--;//电量脉冲定时器减1
		if( Plusefiltertimer == 0 ) 
		{
			Decimal.Add++;	//脉冲增量
		}
	}
	else Plusefiltertimer = 0;
	
	if( Plusefiltertimer2 && (Plusefiltertimer2 <= Def_Plusefiltertimer2) && (REACTIVEP_P))//无功脉冲毫秒去抖判断
	{
		Plusefiltertimer2--;//电量脉冲定时器减1
		if( Plusefiltertimer2 == 0 ) 
		{
			Decimal.Add_Rp++;//无功脉冲增量
		}
	}
	else Plusefiltertimer2 = 0;
		
	for ( Ch=0; Ch<CHNum; Ch++ )
	{
		if(Uart[Ch].Overtime_Timer != 0)
		{
			Uart[Ch].Overtime_Timer--;
			if( Uart[Ch].Overtime_Timer == 0 ) 
			{
				if( Ch == CHHW ) 
				{	
					UART_common->UARTIE &= (~UART_TX_IE5);	//关闭TXIEx
					UART_common->UARTIE |= UART_RX_IE5;	//打开RXIEx
//					RXSTA0 &= B1111_0001;
//					{RXSTA0 = 0;RXSTA0 = B0101_0000;}//复位接收FIFO
				}
				if( Ch == CHBLE ) 
				{	
					UART_common->UARTIE &= (~UART_TX_IE1);	//关闭TXIEx
					UART_common->UARTIE |= UART_RX_IE1;	//打开RXIEx
//					RXSTA1 &= B1111_0001;
//					{RXSTA1 = 0;RXSTA1 = B0101_0000;}//复位接收FIFO
				}
				if( Ch == CH485 ) 
				{	
					UART_common->UARTIE &= (~UART_TX_IE2);	//关闭TXIEx
					UART_common->UARTIE |= UART_RX_IE2;	//打开RXIEx
//					RXSTA1 &= B1111_0001;
//					{RXSTA1 = 0;RXSTA1 = B0101_0000;}//复位接收FIFO		
					R485CTRLR;		//允许接收				
				}
				if( Ch == CHZB ) 
				{	
//					UART_common->UARTIE &= (~UART_TX_IE0);	//关闭TXIEx
					UART_common->UARTIE |= UART_RX_IE0;	//打开RXIEx
//					RXSTA2 &= B1111_0001;
//					{RXSTA2 = 0;RXSTA2 = B0101_0000;}//复位接收FIFO
				}
				Uart[Ch].Step = 0x00;
				Uart[Ch].Flag = 0x00;
				Uart[Ch].Response_Timer = 0x00;
			}
		}
		
		if( (Ch == CHZB) && Uart[Ch].S_Overtime_Timer ) Uart[Ch].S_Overtime_Timer--;//发送超时(载波专用)
		else Uart[Ch].S_Overtime_Timer = 0;
		
		if( Uart[Ch].RptTimer ) Uart[Ch].RptTimer--;
				
	}
	for ( Ch=0; Ch<CHNum; Ch++ )
	{
		if(Uart[Ch].Response_Timer != 0)
		{
			Uart[Ch].Response_Timer--;
			if( Uart[Ch].Response_Timer == 0 ) 
			{
				if ( Uart[Ch].Flag & B0000_1000 )
				{	
					if( Ch == CHHW )  			//允许中断发送数据
					{	
						UART5->TXREG  = 0xfe;		//发送0xfe
						UART_common->UARTIE &= (~UART_RX_IE5);	//关闭RXIEx
						UART_common->UARTIE |= UART_TX_IE5;	//打开TXIEx
					}
					if( Ch == CHBLE )  			//允许中断发送数据
					{	
						UART1->TXREG  = 0xfe;		//发送0xfe
						UART_common->UARTIE &= (~UART_RX_IE1);	//关闭RXIEx
						UART_common->UARTIE |= UART_TX_IE1;	//打开TXIEx
					}
					if( Ch == CH485 ) 
					{	
						R485CTRLS;		//允许发送
						UART2->TXREG  = 0xfe;		//发送0xfe
						UART_common->UARTIE &= (~UART_RX_IE2);	//关闭RXIEx
						UART_common->UARTIE |= UART_TX_IE2;	//打开TXIEx
					}
					if( Ch == CHZB ) 
					{	
						UART0->TXREG  = 0xfe;		//发送0xfe
//						UART_common->UARTIE &= (~UART_RX_IE0);	//关闭RXIEx
						UART_common->UARTIE |= UART_RX_IE0;	//打开RXIEx
						UART_common->UARTIE |= UART_TX_IE0;	//打开TXIEx
					}
					
					Uart[Ch].TxLen  = 1;//开始发送数据
					Uart[Ch].Total_Tx = Uart[Ch].Buf[9]+16;
					if( Ch != CHZB ) Uart[Ch].Overtime_Timer = txtimeout_max;//发送超时
					else
					{
						Uart[Ch].S_Overtime_Timer= txtimeout_max;//发送超时(载波专用)
						Uart[Ch].Step = 0x00;
						Uart[Ch].Flag &= ~B0000_1111;//其他通道在发送超时结束的时候清除
					}
				}
				else
				{
					Uart[Ch].Response_Timer++;//继续等待
				}
			}
		}			
	}
	
	if( Compile_Polar_485 == 0x55 )	//兼容无极性485
	{
		if( (Uart[CH485].Response_Timer == 0)&&(Uart[CH485].Overtime_Timer == 0)&&((UART_common->UARTIF&UART_RX_IF2)==0x00) )
		{
			Uart1KeySamp<<=1;
			if(RX485_P)  Uart1KeySamp++;		//保证总线空闲时判断,兼容无极性485
			
			if( Uart1KeySamp == 0xff ) //高电平 正极性
			{
				if( UART2->RTXCON != B0000_0000 )	UART2->RTXCON = B0000_0000;//正极性 接收数据不取反,发送数据不取反
			}
			else if( Uart1KeySamp == 0x00 )
			{
				if( UART2->RTXCON != B0000_0011 )	UART2->RTXCON = B0000_0011;//反极性 接收数据取反,发送数据取反		
			}	 
		} 
		else Uart1KeySamp = 0x55;
	}
	else
	{
		if( UART2->RTXCON != B0000_0000 )	UART2->RTXCON = B0000_0000;//正极性 接收数据不取反,发送数据不取反
	}
	
	if( (SVDCHKPLOW) && (Relayctrl.Timer == 0) ) 
	{	
		for(i=0; i<0x700; i++)		//约2.5ms @8MHz&3级优化
		{
			if( !(SVDCHKPLOW) ) break;
		}		
		if( i==0x700 ) //掉电
		{
			LCDLEDOFF;//关闭背光(省电)
			RELAYLEDOFF;//关闭继电器指示灯(省电)
			
			for(i=0; i<0x700; i++)		//约2.5ms @8MHz&3级优化
			{
				if( !(SVDCHKPLOW) ) break;
			}	
			if( i==0x700 ) //掉电
			{
				if( (ANAC->SVDCFG & ANAC_SVDCFG_SVDLVL_SVS) == ANAC_SVDCFG_SVDLVL_SVS )
				{
					Powerd_Flag = 0x12345678;		//置停电标志
					NVIC_DisableIRQ(RTC_IRQn);
					NVIC_DisableIRQ(ETIMER2_IRQn);
					NVIC_DisableIRQ(ETIMER4_IRQn);
					NVIC_DisableIRQ(UART5_IRQn);
					NVIC_DisableIRQ(UART2_IRQn);
					NVIC_DisableIRQ(UART1_IRQn);
					NVIC_DisableIRQ(UART0_IRQn);
					NVIC_DisableIRQ(BT1_IRQn);
					NVIC_DisableIRQ(BT2_IRQn);
//					__disable_irq();//EA = 0;		//关掉全局中断
				}
				else reg_veri_flag = 1;
			}
		}
	}			
}


void ETIMER4_IRQHandler(void)
{
	ETIMER4->ETxIF = 0x03;				//清中断标志
	
	if ( Plusevalidtimer != 0 ) 	//软件点脉冲灯处理
	{
		Plusevalidtimer--;
	}

	if ( Plusevalidtimer == 0 )
	{
		if ( (Outputtype == 3) || (Outputtype == 6) ) CFOUT_OFF;
			
		ETIMER4->ETxCR = 0x00000000;  //禁止ET4启动
	}
}

void BT1_IRQHandler(void)
{
	uint08 Temp_IF;
	
	Temp_IF = BTIMER1->BTxIF;
	if( Temp_IF&B0000_1000 ) //比较匹配中断
	{
//		if( Temp_IF )
		{
//			if((Emu_Data.I1.B32) && (energy_rst_flag == 0))
			{
				Plusefiltertimer = Def_Plusefiltertimer;		//启动毫秒脉冲去抖
				if( Plusefiltertimer == 0 ) 
				{
					Decimal.Add++;	//脉冲增量
				}
				
				if( Outputtype == 6 )
				{
					CFOUT_ON;
					Plusevalidtimer = Def_Plusevalidtimer;	//启动延时
					ETIMER4->ETxIVR	= 0xffff-0x7d00;
					ETIMER4->ETxCR |= 0x00000080;   //启动定时器
				}
			}
			
			BTIMER1->BTxIF = 0xFF;
		}
	}
}

void BT2_IRQHandler(void)
{
	uint08 Temp_IF;
	
	Temp_IF = BTIMER2->BTxIF;
	if( Temp_IF&B0000_1000 ) //比较匹配中断
	{
//		if((Emu_Data.I1.B32) && (energy_rst_flag == 0))
		{
			Plusefiltertimer2 = Def_Plusefiltertimer2;		//启动毫秒脉冲去抖(无功)
			if( Plusefiltertimer2 == 0 ) 
			{
				Decimal.Add_Rp++;//无功脉冲增量
			}
			
			if( Outputtype == 3 )
			{
				CFOUT_ON;
				Plusevalidtimer = Def_Plusevalidtimer;	//启动延时
				ETIMER4->ETxIVR	= 0xffff-0x7d00;
				ETIMER4->ETxCR |= 0x00000080;   //启动定时器
			}
		}
		
		BTIMER2->BTxIF = 0xFF;
	}
}

void UART5_IRQHandler(void)
{
	uint08 Temp;
	uint32 Temp_IF; 
	
	Temp_IF = (UART_common->UARTIF&UART_common->UARTIE); //任何对寄存器的操作都会导致其清零, 必须先缓存
	
	if( (Temp_IF & UART_RX_IF5)  ) //Receive
	{
		Temp = UART5->RXREG; //从UART数据寄存器中取接收数据
		Judge_645_Frame( CHHW, Temp );
	}
	
	if( (Temp_IF & UART_TX_IF5) ) //Transmit
	{
		Tx_645_Frame( CHHW );
		UART_common->UARTIF = UART_TX_IF5;	//clr UARTX.txif
	}
	UART_common->UARTIF &= ((~UART_common->UARTIE) &(UART_TX_IF5|UART_RX_IF5));
}

void UART2_IRQHandler(void)
{
	uint08 Temp;
	uint32 Temp_IF; 
	
	Temp_IF = (UART_common->UARTIF&UART_common->UARTIE); //任何对寄存器的操作都会导致其清零, 必须先缓存

	if( (Temp_IF & UART_RX_IF2) ) //Receive
	{
		Temp = UART2->RXREG; //从UARTX数据寄存器中取接收数据	
		Judge_645_Frame( CH485, Temp );
	}

	if( (Temp_IF & UART_TX_IF2) ) //Transmit
	{
		Tx_645_Frame( CH485 );
		UART_common->UARTIF = UART_TX_IF2;	//clr UARTX.txif
	}
	UART_common->UARTIF &= ((~UART_common->UARTIE) &(UART_TX_IF2|UART_RX_IF2));
}

void UART1_IRQHandler(void)
{
	uint08 Temp;
	uint32 Temp_IF; 
	
	Temp_IF = (UART_common->UARTIF&UART_common->UARTIE); //任何对寄存器的操作都会导致其清零, 必须先缓存

	if( (Temp_IF & UART_RX_IF1) ) //Receive
	{
		Temp = UART1->RXREG; //从UARTX数据寄存器中取接收数据	
		Judge_645_Frame( CHBLE, Temp );
	}

	if( (Temp_IF & UART_TX_IF1) ) //Transmit
	{
		Tx_645_Frame( CHBLE );
		UART_common->UARTIF = UART_TX_IF1;	//clr UARTX.txif
	}
	UART_common->UARTIF &= ((~UART_common->UARTIE) &(UART_TX_IF1|UART_RX_IF1));
}
	
void UART0_IRQHandler(void)
{
	uint08 Temp;
	uint32 Temp_IF; 
	
	Temp_IF = (UART_common->UARTIF&UART_common->UARTIE); //任何对寄存器的操作都会导致其清零, 必须先缓存

	if( (Temp_IF & UART_RX_IF0) ) //Receive
	{
		Temp = UART0->RXREG; //从UARTX数据寄存器中取接收数据
		Judge_645_Frame( CHZB, Temp );
	}

	if( (Temp_IF & UART_TX_IF0) ) //Transmit
	{
		Tx_645_Frame( CHZB );
		UART_common->UARTIF = UART_TX_IF0;	//clr UARTX.txif
	}
	
	UART_common->UARTIF &= ((~UART_common->UARTIE) &(UART_TX_IF0|UART_RX_IF0));
}
	
	
void FDET_IRQHandler(void)
{
	ANAC->FDETIE = 0;	
	ANAC->FDETIF = 1;//清XTLF停振标志
}

	
void RTC_IRQHandler(void)
{
//	if( RTC->RTCIE & RTC_RTCIE_HOUR_IE_ENABLE ) //rtc
//	if( RTCIE&B0000_0100 ) //rtc
//	{
//		if( (PCON&B0000_1100)==0 ) EA = 0;	//关掉全局中断(sleep唤醒)
//		else {RTCIF &= B1111_1110; RTCTMRIF = 0;}	//仅清除秒中断标志
//	}
//	else if( RTCIF&RTCIE ) //rtc
	{		
		if( below_60u_flag == 0 ) //掉电事件结束开始计时
		{
			if( Meter_Run_Timer1 < Mode.Report_Timer ) Meter_Run_Timer1++;//电表上电运行时间1(电表上电时间不足1小时,则掉电后不进行掉电发生上报) 
			if( Meter_Run_Timer2 < Mode.Report_Timer ) Meter_Run_Timer2++;//电表上电运行时间2(电表上电时间不足1小时,则掉电后不进行掉电结束上报)
		}
		if( Meter_Run_Timer3 < 60 ) Meter_Run_Timer3++; //上报状态字延时加1s
		Meter_Run_Timer4++; //上电总运行时间加1s
		
		if( Display.Timer != 0 ) Display.Timer--;
		
		if( Successled.Timer != 0 ) Successled.Timer--;//通讯符号延时定时器减1
		
		if( Keyclose_timer!= 0 ) Keyclose_timer--;//按键闭合继电器定时器减1
		
		Adcctrl.Timer++;
		
	#if( NEWCLOCKADJ == 0 ) //旧标准时钟调校	
		if( Adcctrl.Timer == 5 )//启动电池adc 
	#else
		if( (Adcctrl.Timer == 5) && (Adcctrl.Status == 0) )//启动电池adc 
	#endif
		{
			ADC_ChannelSel(ANAC_ADCCON_ADC_VANA_EN_Voltage);	//测电压
			ADC_SetTrim(const_adc_TrimB);			
			BUF4TST_BypassDisable();//外部输入
			BUF4TST_Enable();	//电压			
			BUF4TST_ChannelSel(ANAC_ANATESTSEL_BUF4TST_SEL_AN5);//输入通道选择	
			ADC_ITDisable();
			ADC_Enable();			
			Adcctrl.Status= B0000_0001;
		}

	#if( NEWCLOCKADJ == 0 ) //旧标准时钟调校
		if( Adcctrl.Timer == 10 )//启动温度adc 
		{
			Adcctrl.Timer = 0;
	#else			
		if( ((Adcctrl.Timer%2) == 0) && (Adcctrl.Status == 0) )//启动温度adc 		
		{
			if( Adcctrl.Timer >= 10 ) Adcctrl.Timer = 0;
	#endif		
			ADC_ChannelSel(ANAC_ADCCON_ADC_VANA_EN_Temp);	//测温	
			ADC_SetTrim(const_adc_TrimT);
			BUF4TST_BypassEn();	//内部输入
			BUF4TST_Disable();	//内部电压	
			ADC_ITDisable();
			ADC_Enable();			
			
			Adcctrl.Status= B0000_0010;
		}	
		
//		if( Display_Space_Timer != 0 ) //红外遥控唤醒延时
//		{
//			Display_Space_Timer--;	
//			if( Display_Space_Timer==0 ) Lcdled = Hw_Lcdled_Timer;//启动背光定时器
//		}
		
				
		Lcdled_Control();	//背光控制
			
		RTC->RTCIF = 0xFFFF;	//清除所有rtc标志
	}
}
	
void SVD_IRQHandler(void)
{
//	if( (ANAC->SVDCFG&ANAC_SVDCFG_SVDMOD_INTERVAL) == 0 ) //LVIF=1, 发生欠压报警中断
	{
		ANAC->SVDSIF = 0x00000003;
		ANAC->SVDCFG &= ((~ANAC_SVDCFG_PRIE_Msk)|(~ANAC_SVDCFG_PFIE_Msk));//软件清除 "电压变化中断标志位"	
	}
}


void NMI_Handler(void)
{
	if( PMU->IOWKFLAG&BIT7 )
	{
		PMU->IOWKFLAG = PMU->IOWKFLAG;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
uint08 Uart_RXErr_Proc( uint08 Ch )
{
	uint08 status = 0;
	
	if( Ch == CHHW ) 
	{		
		if( UART5->RXSTA & B0000_1110 ) 
		{
			status = 0xaa;
			UART5->RXSTA &= (~B0000_1110);			
		}
	}
	if( Ch == CHBLE ) 
	{		
		if( UART1->RXSTA & B0000_1110 ) 
		{
			status = 0xaa;
			UART1->RXSTA &= (~B0000_1110);			
		}
	}
	if( Ch == CH485 ) 
	{	
		if( UART2->RXSTA & B0000_1110 ) 
		{
			status = 0xaa;
			UART2->RXSTA &= (~B0000_1110);
		}
	}
	if( Ch == CHZB ) 
	{	
		if( UART0->RXSTA & B0000_1110 ) 
		{
			status = 0xaa;
			UART0->RXSTA &= (~B0000_1110);
		}
	}

	return status;
}

void Uart_IE_Disable_Proc( uint08 Ch )
{
	if( Ch == CHHW ) 
	{	
		UART_common->UARTIE &= (~(UART_RX_IE5|UART_TX_IE5));	//关闭中断
		UART_common->UARTIF = UART_RX_IE5|UART_TX_IE5;		//清中断标志
	}
	if( Ch == CHBLE ) 
	{	
		UART_common->UARTIE &= (~(UART_RX_IE1|UART_TX_IE1));	//关闭中断
		UART_common->UARTIF = UART_RX_IE1|UART_TX_IE1;		//清中断标志
	}
	if( Ch == CH485 ) 
	{	
		UART_common->UARTIE &= (~(UART_RX_IE2|UART_TX_IE2));	//关闭中断
		UART_common->UARTIF = UART_RX_IE2|UART_TX_IE2;		//清中断标志
	}
	if( Ch == CHZB ) 
	{	
		UART_common->UARTIE &= (~(UART_RX_IE0));		//关闭接收中断
		UART_common->UARTIF = UART_RX_IE0;			//清接收中断标志
	}
}

uint08 Judge_MeterId(uint08 CH)
{
	uint08 i, Temp08;
	
	if( (CH==CHBLE) && (Uart[CH].Step==2) )	//蓝牙地址判断A2/A3
	{		
		if( (Uart[CH].Buf[3]==0xFF) || (Uart[CH].Buf[3]==0xFE) || (Uart[CH].Buf[3]==0xFD) )
		{
			if( (Uart[CH].Buf[5]==0xEE) && (Uart[CH].Buf[6]==0xEE) )
			{
				Uart[CH].Step = 0x03; 			//等待接收CMD
				return 0;
			}
		}
		return 0x55;
	}
	
	if( (CH==CHBLE) && (Uart[CH].Step==7)	)	//透传数据处理
	{
		if( Uart[CH].Buf[8] != 0x11 )		//控制码必须为0x11
		{
			return 0xaa;
		}
		
		Temp08 = Uart[CH].Buf[9];
		memcpy(Uart[CH].Buf, Uart[CH].Buf+10, Temp08);
		
		for( i=0; i<Temp08; i++ )
		{
			Uart[CH].Buf[ i ] -= 0x33;
		}
		
		for(i=0; i<Temp08; i++)
		{
			if( Uart[CH].Buf[i] != 0xFE ) break;
		}
		if( i ) memcpy(Uart[CH].Buf, Uart[CH].Buf+i, Uart[CH].Total_Len-i);
		
		if( (Uart[CH].Buf[0] != 0x68) || (Uart[CH].Buf[7] != 0x68) ) return 0xaa;
	}
	
	//通讯地址判断
	for( i=0; i<6; i++ )
	{
		if( Uart[CH].Buf[ 1+i ] != 0x99 )  break;//表示接收部分错误
	}
	if( i == 6 ) 
	{
		Uart[CH].Flag = B0000_0001;//广播表号标志
		Uart[CH].Step = 0x03; //等待接收CMD
		return 0;
	}
	
	for( i=0; i<6; i++ )
	{
		if( Uart[CH].Buf[ 1+i ] != 0xaa )  break;//表示接收部分错误
	}	
	if( i == 6 ) 
	{
		Uart[CH].Flag = B0000_0010;//全aa表号标志
		Uart[CH].Step = 0x03; //等待接收CMD
		return 0;
	}
	
	for( i=0; i<6; i++ )
	{	
		if( (Uart[CH].Buf[ 1+i ] != Comm_Addr.Comm_Id[ 5-i ]) )
		{
			for( ; i<6; i++ )
			{
				if( Uart[CH].Buf[ 1+i ] != 0xaa ) break;//表示接收部分错误
			}
			if( i == 6 ) Uart[CH].Flag = B0000_0010;//置索位地址标志
			break;
		}
	}
	if( i == 6 )  
	{
		Uart[CH].Step = 0x03; //等待接收CMD
		return 0;
	}
	
	return 0x55;
}

void Judge_645_Frame( uint08 CH, uint08 RcvData ) //using 1 //接收处理
{
	unsigned char i, n, m, status=0;
	
	Uart[CH].Overtime_Timer = txtimeout_max;//接收超时
			
	switch( Uart[CH].Step )
	{
		case 0x00: //等待接收0x68
				if( RcvData == 0x68 )
				{
					Uart[CH].Step = 0x01; //等待接收id.
					Uart[CH].Len = 0;
				}
				else
				{
					status = 0xaa;	//表示接收错误		
				}
				break;
			
		case 0x01: //等待接收id.
				if ( (Uart[CH].Len) >= 6 )
				{
					Uart[CH].Step = 0x02; //等待接收第二个0x68
				}
				break;
	
		case 0x02: //等待接收第二个0x68
				if( RcvData == 0x68 )
				{
					if( CH == 0 )
					{
						Lcdled = Hw_Lcdled_Timer;//启动背光定时器
						LCDLEDON;
					}
					
					Uart[CH].Flag = 0x00;//通讯标志清零
					
					status = Judge_MeterId(CH);
				}
				else status = 0x55;
				break;
	
		case 0x03: //等待接收cmd.
				Uart[CH].Step = 0x04; //等待接收LEN
				break;
	
		case 0x04: //等待接收len
				if( RcvData == 0x00 )
				{
					Uart[CH].Total_Len = RcvData;
					Uart[CH].Step = 0x06; //接收cs
				}
				else 
				{
					if( RcvData <= (urx_buf_size-12) )
					{
						Uart[CH].Total_Len = RcvData;
						Uart[CH].Step = 0x05; //等待接收DATA
					}
					else
					{
						status = 0xaa;	//表示接收错误
					}
				}
				break;
	
		case 0x05: //等待接收DATA
				if( Uart[CH].Len == ( Uart[CH].Total_Len + 0x09) ) //帧数据域溢出
				{
					Uart[CH].Step = 0x06; //等待接收cs.								
				}
				
				if( Uart[CH].Len > ( Uart[CH].Total_Len + 0x09) ) //帧数据域溢出
				{
					status = 0xaa; //表示接收错误									
				}
				
				break;
	
		case 0x06: //等待接收cs.
				Uart[CH].Step = 0x07; //等待接收0x16
				break;
	
		case 0x07: //等待接收0x16
				if( RcvData == 0x16 )
				{
					Uart_IE_Disable_Proc( CH );
					
					if( CH == CHBLE )
					{
						memcpy(Ble_Buf, Uart[CH].Buf, 8);		//暂存命令头
						
						if( (Uart[CH].Buf[3] == 0xFE)||(Uart[CH].Buf[3] == 0xFD) )//透传数据处理
						{
							if( Judge_MeterId(CH) )
							{
								status = 0xaa;	//表示接收错误;
								break;
							}
						}
					}
					
					Uart[CH].Step = 0x08;//字节接收正确
					Uart[CH].Overtime_Timer = 0x00;//清接收超时
					Uart[CH].Response_Timer = framedelay_mx;//置响应超时
					Uart[CH].Flag |= B0000_0100;//置整帧数据接收完成标志
                                	
					if( CH == CHZB ) display_zaibo_flag = 1;
					else display_zaibo_flag = 0;
					
					if( CH == CHBLE ) display_ble_flag = 1;
					else display_ble_flag = 0; 
				}
				else
				{
					status = 0xaa;	//表示接收错误
				}
				break;
	
		default: 
				status = 0xaa;	//表示接收错误
				break;
		
	}

	if( status == 0x00 )	//字节接收正确
	{
		Uart[CH].Buf[Uart[CH].Len] = RcvData;
		Uart[CH].Len++;
	}
	
	if( status == 0x55 )	//表号错误或者第二个68h错误,需要重新找68h
	{
		status = 0xaa;//接收错误
		
//		if(CH)
		{
			Uart[CH].Buf[Uart[CH].Len] = RcvData;
			Uart[CH].Len++;
			for( n=1; n<Uart[CH].Len; n++ )
			{
				if( Uart[CH].Buf[n] == 0x68 )
				{
					
					i = n;
					for( m=0; m<(Uart[CH].Len-n); m++ )
					{
						Uart[CH].Buf[m] = Uart[CH].Buf[i];
						i++;
					}
					Uart[CH].Len -= n;
					Uart[CH].Step = 0x01;
					if ( Uart[CH].Len ==0x07 ) Uart[CH].Step = 0x02;
					status = 0x00;//接收纠错成功
					break;
					       
				}					
			}
		}
	}	
	
	if( Uart_RXErr_Proc( CH ) == 0xaa ) //判断是否有线路错误
	{
		status = 0xaa;
		if( CH == CHHW )
	   {
//		if ( Display_Space_Timer==0 ) 
//		{
//			for( i=0; i<20; i++ )//去抖150us
//			{
//				if( RXHW_P ) break;
//			}
//			if( i==20 ) Display_Space_Timer = 2;//启动2s去抖时间	
//		}
	   }
	}
		
	if( status == 0xaa )	//接收错误
	{
		Uart[CH].Step = 0x00;
		Uart[CH].Overtime_Timer = txtimeout_max/5;
	}
}


void Tx_645_Frame( uint08 Ch )	//using 1	//数据发送
{
	uint08 Temp08;
	
	if( Uart[Ch].TxLen >= Uart[Ch].Total_Tx )
	{
		if( (Ch==CHBLE) && (Ble_Reset==0x55) ) {Ble_Reset=0xAA; reg_veri_flag = 1;} //复位蓝牙模块
		if( UpdateBps ) {UpdateBps = 0; reg_veri_flag = 1;} //通过寄存器校验完成bps修改
		
		if( Ch != CHZB ) Uart[Ch].Overtime_Timer = 2;//通过超时控制复位通讯
		else  Uart[Ch].S_Overtime_Timer= 0;//发送超时(载波专用)
	}
	else
	{
		if( Uart[Ch].TxLen < 4 ) Temp08 = 0xfe;
		else Temp08 = Uart[Ch].TxBuf[Uart[Ch].TxLen-4];		
		if( Ch == CHHW ) 
		{	
			UART5->TXREG = Temp08;
		}
		else if( Ch == CHBLE ) 
		{	
			UART1->TXREG = Temp08;
		}
		else if( Ch == CH485 ) 
		{	
			UART2->TXREG = Temp08;
		}
		else if( Ch == CHZB ) 
		{	
			UART0->TXREG = Temp08;
		}
		
		Uart[Ch].TxLen++;
		if( Ch != CHZB ) Uart[Ch].Overtime_Timer = txtimeout_max;//发送超时
		else Uart[Ch].S_Overtime_Timer= txtimeout_max;//发送超时(载波专用)
	}
}

void Lcdled_Control()	//using 1	//背光控制
{
	if( Lcdled != 0 ) Lcdled--;
	
	if( Lcdled || Opendelaytimer || relay_delay_flag || relay_commu_alarm_flag || 
		((low_voltage_flag||Bat_Delay_Timer) && (Mode.Plc&0x02)) || (dl_back_flag && (Mode.Plc&0x01)) )
	{
		LCDLEDON;
	}
	else if( relay_status_flag && relay_commu_disable_close_flag )	//新增处于合闸允许点亮背光（2021）
	{
		LCDLEDON;
	}
	else if( relay_status_flag && (relay_commu_disable_close_flag ==0) && relay_commu_open_flag )	//新增通讯拉闸点亮背光
	{
		LCDLEDON;
	}
	else if( (Relay_Mode!=0x55) && (relay_status_flag==0) && relay_error && (relay_commu_close2_flag==0) ) //新增合闸失败点亮背光(内置继电器)(除保电解除)
	{
		LCDLEDON;
	}
	else if( (Relay_Mode==0x55) && (relay_status_flag==0) && (comm_relaystatus_flag == 1) && (relay_success_flag==0) )//新增合闸延时过程点亮背光(外置继电器)
	{
		LCDLEDON;
	}
	else
	{
		LCDLEDOFF;
	}
	
	
	if( Init_Led_Timer != 0 ) Init_Led_Timer--;	//led指示灯定时器减1
	
	if( Init_Led_Timer )
	{
		RELAYLEDON;
	}
	else if( relay_commu_disable_close_flag )      //1s闪烁跳闸指示灯
	{
		if( Sclock.Clockbackup[0] & B0000_0001 ) RELAYLEDON;
		else RELAYLEDOFF;	
	}
	else if( (Relay_Mode==0x55) && (relay_cleardl_flag==0) && (relay_status_flag==0) && (comm_relaystatus_flag == 1) && (relay_success_flag==0) )
	{
		if( Sclock.Clockbackup[0] & B0000_0001 ) RELAYLEDON;
		else RELAYLEDOFF;	
	}
	else if( real_relaystatus_flag )
	{
		RELAYLEDON;
	}
	else
	{
		RELAYLEDOFF;
	}		
}


unsigned char Judge_Io_Status()	//检测电源异常io口状态
{	
	unsigned int i;
	
	i =0;
	Do_DelayStart();	//2ms延时判断
	{
		if( RELAYTEST_P ){
      			i = 1;
      			break;
		}
	}While_DelayUsEnd(125);	//125*16=2ms,@512K
	
	if( SVDCHKPLOW )
	{	
		if( i == 0 )	return 0x55;	//低电平持续2ms则认为电源异常(继续欠压)
	}
	
	return 0;
}


void PowerError_Check()		//电源异常检测
{
	unsigned int i;
	unsigned char j;
	
	for(j=0;j<10;j++)
	{
		Clear_Wdt();
		
		RAMREG11 = 0x00;
		
		if( RELAYTEST_N )	
		{
			RAMREG11 = Judge_Io_Status();	
		}
			
		if( (RELAYTEST_P) && (RAMREG11 == 0x00) )
		{
			i = 0;		
			Do_DelayStart();
			{
				if( RELAYTEST_N )
				{
				  i = 1;
				  break;
				}
			}While_DelayMsEnd(1.5);	//1.5*16=24ms,@512K
			if(i != 0)  RAMREG11 = Judge_Io_Status();
		}
		
		if( RAMREG11 == 0 ) break;
	}
}


void SCover_Check( void )
{
	unsigned int i;

	if( (Cover.Status == 0) && (COVKEY_P) ) //
	{
		for( i=0; i<160; i++ )
		{
			if( COVKEY_N ) break;
		}
		if( i == 160 ) //开盖
		{
			if( Cover_Space_Timer )	return;		//开盖延时未到
			
			Cover.Status = 1;
			RAMREG12 = 0xaa;
			memcpy( RAMBUF, Sclock.Clockbackup, 6 );//保存开盖发生时间(秒分时日月年)
		}
	}
	else if( (Cover.Status) && (COVKEY_N) )
	{
		for( i=0; i<160; i++ )
		{
			if( COVKEY_P ) break;
		}
		if( i == 160 ) //合盖
		{
			if( Cover_Space_Timer )	return;		//开盖延时未到
			
			Cover.Status = 0;
			if( RAMREG12 == 0xaa ) RAMREG12 = 0xbb;
			else RAMREG12 = 0x55;
			memcpy( RAMBUF+6, Sclock.Clockbackup, 6 );//保存开盖结束时间(秒分时日月年)
			if( RAMREG2 ) RAMREG2--;		//停电开盖次数减1
		}
	}
	
	Cover_Space_Timer = def_coverdelaytimer;//开盖延时时间
}


//mode=1写脉冲尾数和事件标志,mode=0脉冲尾数和事件标志清零
//每小时/设置时间/清零/掉电时写数据ee
void Wr_Powerdown_Data( unsigned char mode )	//写掉电相关数据到数据ee
{
	unsigned char  Buf[ee_powerdown_lenth+2];
	
	memset( Buf, 0x00, ee_powerdown_lenth );
	
	//ee_power_down_page: 掉电时间(7)+脉冲增量(2)+事件标志(1)+失压事件(8)+低电压事件(2)+高电压事件(2)+上报次数(1)+同步标志(3)+负荷记录指针(40+2)+crc(2)，共62+2字节
	memcpy( Buf, Sclock.Clockbackup, 7 );//时钟

	if( mode )
	{
		Buf[7] = Decimal.Add;//保存有功脉冲增量
		Buf[8] = Decimal.Add_Rp;//保存无功脉冲增量
		
		if( below_60u_flag==0 ) Buf[9] |= 0x80;//掉电事件起始记录
		if( relay_error ) Buf[9] |= 0x40;//负荷开关异常结束记录
		if( load_over_flag ) Buf[9] |= 0x20;//记录电流过载事件(结束)
		if( cal_err_flag ) Buf[9] |= 0x10;//计量芯片故障结束记录
		if( nline_err_flag ) Buf[9] |= 0x08; //零线电流异常结束记录
		if( lost_v_flag )//记录失压事件(结束)
		{
			Buf[9] |= 0x04;//记录失压事件(结束)
			memcpy( Buf+10, &Lost_Aver_I, 4 );
			memcpy( Buf+14, &Lost_V_Timer, 4 );
		}
		if( Current_Over_Count41 )
		{
			Buf[9] |= 0x02;
			memcpy( Buf+18, &Current_Over_Count41, 2 );//保存低电压事件临时累计时间
		}
		if( Current_Over_Count51 )
		{
			Buf[9] |= 0x01;
			memcpy( Buf+20, &Current_Over_Count51, 2 );//保存高电压事件临时累计时间
		}
		
		Buf[22] = ReportList[0]&B0011_0000; //保存 主动上报次数(掉电上报除外)
		
		Buf[23] = MvFlash.Obj;
		if( 0x55 == MvFlash.Dir ) Buf[23] |= 0x40; //bit6
		if( 0xAA == MvFlash.Dir ) Buf[23] |= 0x80; //bit7
		Short2Byte( MvFlash.Offset, Buf+24 );
	}
	
	memcpy( Buf+26, Load.Point, ee_loadpoint_lenth+2 );//保存负荷记录指针(带crc)
	
	I2C_Write_Eeprom( ee_power_down_page, 0x00, Buf, ee_powerdown_lenth);//写掉电数据到数据ee
}

//总累计时间处理
//掉电及唤醒时，计算总累计时间并更新到EE，计算后，RAM数据清零，重新累计
//Store=0：只读；Store=1：存储
void Save_Keep_Timer( unsigned char Store )
{
	unsigned char i;
	uint32 Temp32;
	
	if( Store && (ChkBufZero( (uint08*)&Keeptime.Times[0], ee_illegalcardnum_len )==0) ) return;	//全0则无需保存
	
	I2C_Read_Eeprom( ee_illegalcardnum_page, ee_illegalcardnum_inpage, Eeprom.Buffer, ee_illegalcardnum_len );
	
	for( i=0; i<ee_illegalcardnum_len/4; i++ ) 
	{
		Exchange((uint08*)(&Temp32), (Eeprom.Buffer+i*4), 4);
		Temp32 += Keeptime.Times[i];
		Exchange((Eeprom.Buffer+i*4), (uint08*)(&Temp32), 4);
	}
	
	if( Store)
	{
		I2C_Write_Eeprom( ee_illegalcardnum_page, ee_illegalcardnum_inpage, Eeprom.Buffer, ee_illegalcardnum_len );
		memset( (uint08*)(&Keeptime.Times[0]), 0x00, ee_illegalcardnum_len );
	}
}

//通讯抄读相关累计时间
void Get_Keep_Timer(unsigned char Ch, unsigned char *AckBuf)
{
	Save_Keep_Timer(0);
	
	Hex2Bcd( Eeprom.Buffer+Ch*4, AckBuf, 4 );
	Inverse(AckBuf, 4);
}

void Store_Data(uint08 status)
{
	unsigned char i;
	
	CloseEsam();
	Disable_Pulse();//关闭脉冲(省电)
	if( Relay_Mode != 0x55 )//内置继电器
	{
		{RELAYOFF1; __NOP(); RELAYOFF2;}//磁保持继电器无效
	}
	LCDLEDOFF;//关闭背光(省电)
	RELAYLEDOFF;//关闭继电器指示灯(省电)
	BLEPOWEROFF;//关闭蓝牙(省电)
	if( status )//初始化调用Sleep()则不保存数据,防止电池上电反复保存数据(兼容电池外置方案)
	{
		if( Decimal.Status&B0001_0000 ) I2C_Write_Eeprom( ee_fwdl_page, ee_fwdl_inpage, Fwdl.Pluse[0].B08, ee_fwdl_lenth+2 );
		if( Decimal.Status&B0010_0000 ) I2C_Write_Eeprom( ee_bkdl_page, ee_bkdl_inpage, Bkdl.Pluse[0].B08, ee_bkdl_lenth+2 );
		for(i=0; i<4; i++)
		{
			if( Decimal.Status&(1<<i) ) I2C_Write_Eeprom( ee_rpdl_page+2*i, ee_rpdl_inpage, Rpdl[i].Pluse[0].B08, ee_rpdl_lenth+2 );
		}
		
		Read_Sysclock();//读时钟
		Wr_Powerdown_Data(1);//写掉电相关数据到数据ee
		
		I2C_Write_Eeprom( ee_monthvolrun_page, ee_monthvolrun_inpage, VolStatus[0].Total.B08, ee_monthvolrun_lenth );//保存日和月电压合格率运行状态
		
		real_relaystatus_flag = (relay_status_flag^relay_error);
		System_St_Bk = (System_Status&0x3f);//保存状态字
		if( Cover.Status ) System_St_Bk |= 0x80;//保存开盖状态
		I2C_Write_Eeprom( ee_reportdata_page, 0, &System_St_Bk, ee_reportdata_lenth);//保存事件上报数据防止掉电
		
		Save_Keep_Timer(1);//保存相关累计时间
		
		for( i=0; i<max_casecount; i++ )
		{
			if( Load.Point[5*i+3] )	break;
		}
	
		if( i < max_casecount )
			I2C_Write_Eeprom( ee_ploadrec_page, 0, LoadBuf, ee_ploadrec_lenth );
		
		//停电主动上报处理
		RAMREG13 = 0;
		if( below_60u_flag==0 )
		{
			ReportList[0] = 0;
			ReportList[1] = 0;
			Note_Run_Event( ee_powerdownn_inpage ); //掉电事件起始记录
				
			if( ReportList[0]&B0000_0011 ) RAMREG13 = def_powerdown_timer;//启动停电上报总时间
		}
		Meter_Run_Timer1 = 0;//清电表上电运行时间1
				
		if( Mode.Report[4]&(1<<5) )		//停电结束的主动上报
		{
			if( Meter_Run_Timer2 < Mode.Report_Timer ) Meter_Run_Timer2 = 0;//清电表上电运行时间2
		}
		else Meter_Run_Timer2 = 0;//清电表上电运行时间2
			
		//继续掉电前的上报
		if( below_60u_flag && (ReportList[0]&B0000_0011) ) RAMREG13 = ReportList[0]&B0000_0011;
				
		if( (Mode.Feature1&0x0c)!=0x08 )//主动上报未开启,不上报
		{
			ReportList[0] = 0;
			ReportList[1] = 0;
			Meter_Run_Timer1 = 0;//清电表上电运行时间1
			Meter_Run_Timer2 = 0;//清电表上电运行时间2
			RAMREG13 = 0;
		}
	}
	
	RAMREG0 = 0x00;//表示未小时唤醒
	RAMREG1 = Bcd_To_Hex(Sclock.Clockbackup[1]);//停电时的分钟数
	RAMREG2 = 1;//开盖1次限制
	RAMREG3 = 0;//清缓升缓降标志字节
//	RAMREG4 = 0;//跨过整点标志
	
//	RAMREG5 = 0;//跨年结算次数
//	RAMREG6 = 0;//跨结算日次数
//	RAMREG7 = 0;//年结算跨第一结算日次数
//	RAMREG8 = 0;//月结算跨第一结算日次数
	
//	RAMREG9 = 0;//冻结状态字
	
	RAMREG10 = 0;//开盖处理中
	RAMREG11 = 0;//电源异常状态
	RAMREG12 = 0;//开盖状态
	
	RAMREG14 = 120;//停电2h关闭显示
	RAMREG15 = 10;//允许按键唤醒10次
	
	memset( Emu_Data.U.B08, 0x00, 36 );//电压电流功率功率因数清零
	Emu_Data.Cosa.B32 = 0x1000;
	System_Status1 = 0;//清电表状态字1
}

void Lcd_Disp_Off()//配置lcd黑屏显示
{			 	
	Lcd_LCDEN_Off();	//关闭lcd显示
}

void Lcd_Disp_On()//配置lcd停电显示
{
	Veri_Disp(0);
	Lcd_LCDEN_On();		//打开lcd显示
}


void Close_And_ClearIRQ(IRQn_Type IRQn)
{
	NVIC_DisableIRQ(IRQn);
	NVIC_ClearPendingIRQ(IRQn);	
}

void Configure_Register_Sleep()//sleep前配置寄存器
{

//	GPIO14CFG = B0100_0000;//RXHW, RXD0
//	GPIO32CFG = B0100_0000;//PLCA
//	GPIO33CFG = B0100_0000;//PLCRST	
//	GPIO35CFG = B0100_0000;//PLCEVT
//	GPIO36CFG = B0100_0000;//RX3,	RXD2
//	GPIO41CFG = B0100_0000;//SAMIO,	ESAM的IO口
//	GPIO42CFG = B0100_0000;//ICIO, 	CARD的IO口

//	EXIN1DFCTL = 0;
//	EXIN2DFCTL = 0;	
	
	Close_None_GPIO();
	
//	GPIOA->ODR &= (~(GPIO_Pin_6|GPIO_Pin_7));
	GPIOB->ODR &= (~(GPIO_Pin_0));
	GPIOB->ODR &= (~(GPIO_Pin_2));
	GPIOC->ODR &= (~(GPIO_Pin_4));
//	GPIOD->ODR &= ;
//	GPIOE->ODR &= ;
//	GPIOF->ODR &= (~(GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5));
	GPIOG->ODR &= (~GPIO_Pin_3);	
	
	AnalogIO( GPIOA, GPIO_Pin_0 );		//PA0; //COM0
	AnalogIO( GPIOA, GPIO_Pin_1 );		//PA1; //COM1
	AnalogIO( GPIOA, GPIO_Pin_2 );		//PA2; //COM2
	AnalogIO( GPIOA, GPIO_Pin_3 );		//PA3; //COM3
	AnalogIO( GPIOA, GPIO_Pin_4 );		//PA4; //COM4
	AnalogIO( GPIOA, GPIO_Pin_5 );		//PA5; //COM5
	AnalogIO( GPIOA, GPIO_Pin_6 );		//PA6;//SEG0
	AnalogIO( GPIOA, GPIO_Pin_7 );		//PA7;//SEG1	
	AnalogIO( GPIOA, GPIO_Pin_8 );		//PA8;//SEG2
	CloseeIO( GPIOA, GPIO_Pin_9 );		//PA9;//QF_CF
	AnalogIO( GPIOA, GPIO_Pin_10 );		//PA10;//SEG3
	AnalogIO( GPIOA, GPIO_Pin_11 );		//PA11;//SEG4
	AnalogIO( GPIOA, GPIO_Pin_12 );		//PA12;//SEG5
	AnalogIO( GPIOA, GPIO_Pin_13 );		//PA13;//SEG6
	AltFunIO( GPIOA, GPIO_Pin_14, 1 );	//PA14;//SCL
	AltFunIO( GPIOA, GPIO_Pin_15, 1 );	//PA15;//SDA
	
	OutputIO( GPIOB, GPIO_Pin_0, 0 );	//PB0;//BLE-RXD
	CloseeIO( GPIOB, GPIO_Pin_1 );		//PB1;//BLE-TXD
	OutputIO( GPIOB, GPIO_Pin_2, 0 );	//PB2;//RX485, RXD2
	CloseeIO( GPIOB, GPIO_Pin_3 );		//PB3;//TX485, TXD2
	CloseeIO( GPIOB, GPIO_Pin_4 );		//PB4;//ACTIVEP
	InputtIO( GPIOB, GPIO_Pin_5, 0 );	//PB5;//TAIL
	CloseeIO( GPIOB, GPIO_Pin_6 );		//PB6;//PULSELED
	CloseeIO( GPIOB, GPIO_Pin_7 );		//PB7;//VBLE
	AnalogIO( GPIOB, GPIO_Pin_8 );		//PB8;//SEG7
	AnalogIO( GPIOB, GPIO_Pin_9 );		//PB9;//SEG8
	AnalogIO( GPIOB, GPIO_Pin_10 );		//PB10;//SEG9
//	CloseeIO( GPIOB, GPIO_Pin_11 );		//PB11;//RelayCtrl//EE_V@电池外置	
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	CloseeIO( GPIOB, GPIO_Pin_12 );		//PB12;//RelayTest
	AnalogIO( GPIOB, GPIO_Pin_13 );		//PB13;//SEG10
	AnalogIO( GPIOB, GPIO_Pin_14 );		//PB14;//SEG11
	AnalogIO( GPIOB, GPIO_Pin_15 );		//PB15;//SEG12
	
	AnalogIO( GPIOC, GPIO_Pin_2 );		//PC2;//SEG13
	AnalogIO( GPIOC, GPIO_Pin_3 );		//PC3;//SEG14
	OutputIO( GPIOC, GPIO_Pin_4, 0 );	//PC4;//RXHW, RXD5
	CloseeIO( GPIOC, GPIO_Pin_5 );		//PC5;//TXHW, TXD5
	AnalogIO( GPIOC, GPIO_Pin_6 );		//PC6;//SEG15
	AnalogIO( GPIOC, GPIO_Pin_7 );		//PC7;//SEG16
	AnalogIO( GPIOC, GPIO_Pin_8 );		//PC8;//SEG17
	AnalogIO( GPIOC, GPIO_Pin_9 );		//PC9;//SEG18
	AnalogIO( GPIOC, GPIO_Pin_10 );		//PC10;//SEG19
	AnalogIO( GPIOC, GPIO_Pin_11 );		//PC11;//SEG20
	AnalogIO( GPIOC, GPIO_Pin_12 );		//PC12;//SEG21
	AnalogIO( GPIOC, GPIO_Pin_13 );		//PC13;//SEG22
	AnalogIO( GPIOC, GPIO_Pin_14 );		//PC14;//SEG23
	AnalogIO( GPIOC, GPIO_Pin_15 );		//PC15;//SEG24
	
	CloseeIO( GPIOD, GPIO_Pin_0 );		//PD0;//METERIC_RX RXD4
	CloseeIO( GPIOD, GPIO_Pin_1 );		//PD1;//METERIC_TX TXD4
	AnalogIO( GPIOD, GPIO_Pin_2 );		//PD2;//SEG25
	AnalogIO( GPIOD, GPIO_Pin_3 );		//PD3;//SEG26
	if( Relay_Mode == 0x55 )	//外置继电器
	{
		CloseeIO( GPIOD, GPIO_Pin_4 );		//PD4;//RelayOn, 继电器控制脚
		CloseeIO( GPIOD, GPIO_Pin_5 );		//PD5;//RelayOff,继电器控制脚 
	}
	InputtIO( GPIOD, GPIO_Pin_6, 1 );	//PD6;//DISPKEY,带上拉
	CloseeIO( GPIOD, GPIO_Pin_7 );		//PD7;//EsamVcc
	
	CloseeIO( GPIOE, GPIO_Pin_2 );		//PE2;//LCDLED	
	CloseeIO( GPIOE, GPIO_Pin_3 );		//PE3;//485Ctrl
	CloseeIO( GPIOE, GPIO_Pin_4 );		//PE4;//VFLASH
	CloseeIO( GPIOE, GPIO_Pin_5 );		//PE5;//PLCEVT(OD输出)
		
	CloseeIO( GPIOF, GPIO_Pin_3 );		//PF3;//RXZB RXD0 
	CloseeIO( GPIOF, GPIO_Pin_4 );		//PF4;//TXZB TXD0 
	CloseeIO( GPIOF, GPIO_Pin_5 );		//PF5;//PLCRST
	if(Extbattery == 0x55) AnalogIO( GPIOF, GPIO_Pin_6 );		//P6;//VBATCHK
	else CloseeIO( GPIOF, GPIO_Pin_6 );	//PF6;//VBATCHK
		
	CloseeIO( GPIOF, GPIO_Pin_12 );		//PF12;//F_CS
	CloseeIO( GPIOF, GPIO_Pin_13 );		//PF13;//F_CLK
	CloseeIO( GPIOF, GPIO_Pin_14 );		//PF14;//F_DI	
	CloseeIO( GPIOF, GPIO_Pin_15 );		//PF15;//F_DO

	CloseeIO( GPIOG, GPIO_Pin_2 );		//PG2;//ESAMCLK
	CloseeIO( GPIOG, GPIO_Pin_3 );		//PG3;//ESAMIO
	CloseeIO( GPIOG, GPIO_Pin_6 );		//PG6;//TM输出
	CloseeIO( GPIOG, GPIO_Pin_7 );		//PG7;//ESAMRST
	CloseeIO( GPIOG, GPIO_Pin_8 );		//PG8;//SWDTCK/LEDRelay
	CloseeIO( GPIOG, GPIO_Pin_9 );		//PG9;//SWDTDO/COM_RQ	

	ANAC->ADCCON   = 0; //不使能ADC
	RCC->PLLCON	  &= (~RCC_PLLCON_PLLEN_ON); //关闭锁相环
	BUF4TST_Disable();
	
	Disable_I2C_IO();//关闭数据ee电源

	Lcd_Disp_Off();//配置lcd黑屏显示
	Stop_Disptimer = 0;//停电显示时间清零
	Display.Number = 0;
	Display.Status = 0;//清按键显示相关标志
	
	//初始化停电显示参数
	Display_Para.S_Number = Def_SleepDisplayPara_table[0]; 
	Display_Para.Loop_Time = Def_SleepDisplayPara_table[1]; 
	Display_Para.K_Number = Def_SleepDisplayPara_table[4];
	//初始化停电显示内容
	memset( &Item[0].Display[0], 0x01, ee_displayitem_lenth );
	memcpy( &Item[0].Display[0], Def_Sleepdisp_table, sizeof(Def_Sleepdisp_table) );//默认停电循环显示
	memset( &Item[1].Display[0], 0x01, ee_displayitem_lenth );
	memcpy( &Item[1].Display[0], Def_Sleepdisp_table, sizeof(Def_Sleepdisp_table) );//默认停电按键显示

	//需要打开的唤醒中断
	if( (PowerDetCnt1 < 4)&&(PowerDetCnt2 < 8) )//允许进行电源异常检测
	{
		PowerDetCnt0 = 3;
	}
	else
	{
		PowerDetCnt0 = 0;
	}
	RTC->RTCIE = RTC_RTCIE_SEC_IE_ENABLE;		//秒中断时钟打开
	NVIC_DisableIRQ(RTC_IRQn);
	NVIC_SetPriority(RTC_IRQn,2);
	NVIC_EnableIRQ(RTC_IRQn);		
	
	GPIO_common->EXTI0_SEL	= BIT27|BIT11;		//PB5,开盖按键,沿跳变
	GPIO_common->EXTI1_SEL	= BIT28|BIT13;		//PD6,显示按键,下降沿
	GPIO_common->EXTI0IF	= 0x000000FF;		//清标志位
	GPIO_common->EXTI1IF	= 0x000000FF;		//清标志位
	NVIC_DisableIRQ(GPIO_IRQn);
	NVIC_SetPriority(GPIO_IRQn,2);
	NVIC_EnableIRQ(GPIO_IRQn);
	GPIO_common->PINWKEN = BIT7;	//使能PD6的NWKUP7功能
	
	//关闭非唤醒中断
//	Close_And_ClearIRQ(GPIO_IRQn);
	Close_And_ClearIRQ(ETIMER2_IRQn);
	Close_And_ClearIRQ(ETIMER4_IRQn);
	Close_And_ClearIRQ(UART5_IRQn);
	Close_And_ClearIRQ(UART2_IRQn);
	Close_And_ClearIRQ(UART1_IRQn);
	Close_And_ClearIRQ(UART0_IRQn);
	Close_And_ClearIRQ(BT1_IRQn);
	Close_And_ClearIRQ(BT2_IRQn);
	Close_And_ClearIRQ(WWDT_IRQn);
}


void Calculate_Min(unsigned char Result)//停电分钟计算处理
{
	unsigned char i;
	if( Result == 0 ) return;//非法返回
	if( Result > 60 ) return;//非法返回
	i = Result;//i范围0~60min
	if( Progkey.Timer >= i )//编程延时减60
	{
		Progkey.Timer -= i;
	}
	else	
	{
		Progkey.Timer = 0;
	}

	if(low_voltage_flag) 
	Keeptime.Times[2] += i;//累计电池欠压时间
	Keeptime.Times[3] += i;//累计掉电累计时间
	Keeptime.Times[4] += i;	//累计电池工作时间	

}

//////////////////////////////////////////////////////////////////////
void Pd_Adc_Calculate( unsigned char Type )	//0x55:停电电源(法拉电容+电池电压)测量,0xaa:电池电压测量,其他:停电温度adc测量
{
	unsigned char i;
	
	ADCResultArr.ReadCount = 0;
				
	if( Type == 0xaa ) return;	//电池电压测量（南网即使在没有电池的情况下仍然支持按键显示和开盖检测）
	
	if( Type == 0x55 )//停电电源(法拉电容+电池电压)测量
	{
		//电源测量(根据显示电压调整液晶显示)          
		ADC_ChannelSel(ANAC_ADCCON_ADC_VANA_EN_Voltage);	//测电压
		ADC_SetTrim(const_adc_TrimB);			
		BUF4TST_BypassEn();	//测电源电压必须使能
		BUF4TST_Enable();	//输入通道buff使能			
		BUF4TST_ChannelSel(ANAC_ANATESTSEL_BUF4TST_SEL_VDD50);//选择电源电压	
		
		Adcctrl.Status = B0001_0000;//电源adc结束	
		
	}
	else if( Type == 0xaa )
	{
		//电池电压测量(电池欠压则关闭电源检测,按键显示和开盖检测)
		ADC_ChannelSel(ANAC_ADCCON_ADC_VANA_EN_Voltage);	//测电压
		ADC_SetTrim(const_adc_TrimB);			
		BUF4TST_BypassDisable();//外部输入
		BUF4TST_Enable();	//电压			
		BUF4TST_ChannelSel(ANAC_ANATESTSEL_BUF4TST_SEL_AN5);//输入通道选择	
		
		Adcctrl.Status = B0001_0000;//电源adc结束
	}
	else
	{
		//温度adc测量
		ADC_ChannelSel(ANAC_ADCCON_ADC_VANA_EN_Temp);	//测温	
		ADC_SetTrim(const_adc_TrimT);
		BUF4TST_BypassEn();	//内部输入
		BUF4TST_Disable();	//内部电压
			
		Adcctrl.Status = B0010_0000;//温度adc结束	
	}
	
	
	ADC_ITDisable();
	ADC_Enable();	
	
	TicksDelayUs(250);	//250*16=4000US,@512K
	ADCResultArr.Buffer[ADCResultArr.ReadCount&0x1F] = ANAC->ADCDATA&0x000007FF;
	TicksDelayUs(250);	//250*16=4000US,@512K
	//转换32次取后面32次以保证转换数据准确性
	for( i=0; i<32; i++ )
	{
		ADCResultArr.Buffer[ADCResultArr.ReadCount&0x1F] = ANAC->ADCDATA&0x000007FF;
		ADCResultArr.ReadCount++;
	}
	
	BUF4TST_Disable();	//关闭buffer,可以降低10uA左右的功耗
	ADC_Disable();
	Adc_Proc();					
	
	if( Type == 0x55 )//停电电源(法拉电容+电池电压)测量
	{
		union B16_B08_2 Temp16;
		
		Fun_Para.Voltage_P = Fun_Para.Voltage_B;
		
		//计算停电超级电容电压
		RAMBUF[12] = 0x55;
		Exchange( Temp16.B08, (unsigned char *)&Fun_Para.Voltage_P, 2 ); 
		Bcd2Hex_LS( Temp16.B08, Temp16.B08, 2 );
		Temp16.B16 = Temp16.B16/2 + 60 ;//加上二极管电压
		Hex2Bcd_SS( Temp16.B08, RAMBUF+13, 2 );
		RAMBUF[15] = 0x55;
	}
	else if( Type == 0xaa )//电池电压测量
	{
		if( Fun_Para.Voltage_B <= 0x250 )	//电池欠压则关闭电源检测,按键显示和开盖检测
		{
			PowerDetCnt0 = 0;		//停止电源异常检测
			RAMREG10 = 0;			//停止开盖检测
			Stop_Disptimer= 0;		//停止显示
			RAMREG14 = 0;
			RAMREG15 = 0;
		}	
	}
}


void Reset()	//唤醒复位
{	
	Enable_I2C_IO();
	Read_Sysclock();//读时钟
	
	if( RAMREG0 == 0x55 )
	{
		Calculate_Min(Bcd_To_Hex(Sclock.Clockbackup[1]));//已小时唤醒
	}
	else	
	{	
		Calculate_Min(((Bcd_To_Hex(Sclock.Clockbackup[1])-RAMREG1)+60)%60);//未小时唤醒
	}

	Save_Keep_Timer(1);
	
	System_St_Bk = System_Status; //备份系统状态字	
	RAMREG3 = 0xaa;

//	Powerd_Flag = 0x87654321;//如果产生wwdt复位则不是hardfalut产生
//	while(1)
//	{
//		WWDT->WWDTCON = 0xac;//清wwdt
//	}
	
	RCC->SOFTRST = 0x5C5CAABB;	//软复位,从头开始运行
 	while(1);
}

//SlpMode	0=sleep  1=deepsleep
//CVSMode	0=off	 1=on
//RamRMode	0=on*ALL 1=on*16k
void DeviceSleepCFG( unsigned char SlpMode, unsigned char CVSMode ,unsigned char RamRMode ) 
{
//	unsigned int i;
	Clear_Wdt();
	
//	ANAC->ANATESTSEL = ANAC_ANATESTSEL_BUF4TST_EN_DISABLE;
//	RCC->PLLCON &= (~RCC_PLLCON_PLLEN_ON);
//	RCC->PLLCON |= (RCC_PLLCON_PLLEN_OFF);		
//	RCC->RCHFCON &= ~BIT0;//close rchf
//	RCC->SYSRCCSEL |= BIT31;//close rclp
//	RCC->SYSRCCSEL &= ~BIT25;//stop ex pin inter
//	RCC->SYSRCCSEL &= ~BIT26;//after wake clk=8m
//	PMU->LPMCFG &= (~BIT19);//close xtlf
	
	//===================
	if( SlpMode == 0 )//sleep
	{	
		PMU->LPMCFG &= (~BIT9);// sleep mode
	}
	else //( SlpMode == 1 )//deepsleep
	{
		PMU->LPMCFG &= (~BIT9);// sleep mode			
		PMU->LPMCFG |= (BIT9);// deepsleep mode
	}

	//==================
	if( CVSMode )
	{
		PMU->LPMCFG &= (~BIT8);
		PMU->LPMCFG |= BIT8;//使能内核电压降低1.2
	}
	else
	{
		PMU->LPMCFG &= (~BIT8);
	}
	//=================================

//	WTCFG = 0x0C;//B0000_0000;//唤醒等待时间		
	
	//=================================
	if( RamRMode == 0 )
	{
		PMU->LPMCFG &= (~BIT10);//RAM数据保持			
	}
	else
	{
		PMU->LPMCFG |= BIT10;//RAM仅保持低16K数据
	}
	
	SCB->SCR = 0;						//SLEEP
	
	PMU->LPMCFG = (PMU->LPMCFG&0xfffffffc)|BIT1;		//SLEEP
}

void Sleep( uint08 status )
{
	unsigned int i;

	//在进入sleep前再次进行去抖
	Do_DelayStart();		//约4ms
	{
		if( !(SVDCHKPLOW) || ((ANAC->SVDCFG & ANAC_SVDCFG_SVDLVL_SVS) != ANAC_SVDCFG_SVDLVL_SVS) )
		{
			reg_veri_flag = 1; 
			Powerd_Flag= 0; 
			NVIC_EnableIRQ(RTC_IRQn);
			NVIC_EnableIRQ(ETIMER2_IRQn);
			NVIC_EnableIRQ(ETIMER4_IRQn);
			NVIC_EnableIRQ(UART5_IRQn);
			NVIC_EnableIRQ(UART2_IRQn);
			NVIC_EnableIRQ(UART1_IRQn);
			NVIC_EnableIRQ(UART0_IRQn);
			NVIC_EnableIRQ(BT1_IRQn);
			NVIC_EnableIRQ(BT2_IRQn);
			return;		//返回主程序EA = 1;
		}
	}While_DelayMsEnd(4*clkmode);	
	
	Clear_Wdt();
	Store_Data(status);
	__disable_irq();
	Configure_Register_Sleep();
	
	i=0;
	Do_DelayStart();
	{
		if( (SVDCHKPLOW) && ((ANAC->SVDCFG & ANAC_SVDCFG_SVDLVL_SVS) == ANAC_SVDCFG_SVDLVL_SVS) ) {i = 1; break;}
	}While_DelayMsEnd(1*clkmode);
	if( i==0 ) Reset();		//电压恢复则无需进入sleep直接Reset上电
	
	//下电复位需要打开~~
	ANAC->BORCON = SleepBorCfg;
	ANAC->PDRCON = SleepPdrCfg;		
	RCC->XTLFIPW = rtcosccfg;
	GPIO_common->EXTI0IF	= 0x000000FF;		//清按键中断标志位
	GPIO_common->EXTI1IF	= 0x000000FF;		//清标志位
	
	for( ; ; )
	{			
		Clear_Wdt();
		
		RTC->RTCIF = RTC_RTCIF_SEC_IF_ENABLE;	//仅清除秒中断标志
		NVIC_ClearPendingIRQ(RTC_IRQn);
		NVIC_ClearPendingIRQ(GPIO_IRQn);

		if( LCD_SOFF )
		{
			DeviceSleepCFG(1,0,0);//deepsleep + RAM保持
		}
		else
		{
			DeviceSleepCFG(0,0,0);//sleep + RAM保持
		}
		
		ANAC->SVDCON &= ~ANAC_SVDCON_SVDEN_ENABLE;//低压检测电路关闭
		
//		if( SVDCHKPLOW )//发生欠压
		{
//			__enable_irq();//EA = 1;			//打开全局中断
			__WFI();
//			__disable_irq();//EA = 0;			//关掉全局中断
		}
		
		Clear_Wdt();
		
		ANAC->SVDCFG  = ANAC_SVDCFG_SVDLVL_SVS+ANAC_SVDCFG_DFEN_ENABLE;
		ANAC->SVDCON |= ANAC_SVDCON_SVDEN_ENABLE;//低压检测电路使能
		
		if( !(SVDCHKPLOW) )	//sleep前再次去抖,1ms
 		{ 			
	 		i=0;
			Do_DelayStart();
			{
				if( (SVDCHKPLOW) ) {i = 1; break;}
			}While_DelayUsEnd(100);	//100*16=1600us,@512K
			if( i==0 ) Reset();
 		}
 		
		if( RAMREG13 && (RTC->RTCIF & RTC_RTCIF_SEC_IF_ENABLE) )
		{
			RAMREG13--;			
//			if( (RAMREG13%10) == 0 ) //表在检测到掉电后每10秒发一次,发送3次,不接受应答
			{
				//停电上报期间主频8M
				RCC->SYSRCCSEL &= ~RCC_SYSRCCSEL_AHBPRES_16; 
				
				//上报启动
//				AltFunIO( GPIOF, GPIO_Pin_3, 0 );	//PF3;//RXZB RXD0 
				AltFunIO( GPIOF, GPIO_Pin_4, 1 );	//PF4;//TXZB TXD0 (OD输出)
//				AltFunIO( GPIOF, GPIO_Pin_4, 0 );	//PF4;//TXZB TXD0
				
				UART_common->UARTIE = UART_TX_IE0;	//打开接收中断和发送中断
				UART_common->UARTIF = UART_TX_IE0;	//清接收和发送中断标志
				
				Uart[CHZB].Overtime_Timer = 0;	
				Uart[CHZB].Step = 0x00;
				Uart[CHZB].Flag = 0x00;
				Uart[CHZB].Response_Timer = 0x00;
				Uart[CHZB].Len = 0;			
				
				Uart[CHZB].S_Overtime_Timer = 0;
				Uart[CHZB].RptTimer = 0;
								
				NVIC_ClearPendingIRQ(UART0_IRQn);
				NVIC_DisableIRQ(UART0_IRQn);
				NVIC_SetPriority(UART0_IRQn,2);
				NVIC_EnableIRQ(UART0_IRQn);		//打开uart0中断
				
				NVIC_DisableIRQ(WWDT_IRQn);
				NVIC_SetPriority(WWDT_IRQn,1);
				NVIC_EnableIRQ(WWDT_IRQn);		//打开wwdt中断(必须否则会wwdt复位)
				
				NVIC_DisableIRQ(RTC_IRQn);		//关闭rtc中断
				NVIC_DisableIRQ(GPIO_IRQn);		//关闭gpio中断(必须否则会iwdt复位)	
				{Powerd_Flag=0;__enable_irq();}		//清停电标志(EA_ON),同时打开中断
				
				//主动上报
				progenable = 1;				//停电采用明文方式主动上报
				ReportEvent(1);
				
				//600ms发送超时控制
				Do_DelayStart();
				{
					Clear_Wdt();
					if( Uart[CHZB].S_Overtime_Timer == 0 ) break;
				}While_DelayMsEnd( 600 );	
				
				//上报结束
//				CloseeIO( GPIOF, GPIO_Pin_3 );		//PF3;//RXZB RXD0 
				CloseeIO( GPIOF, GPIO_Pin_4 );		//PF4;//TXZB TXD0 (OD输出)
				
				NVIC_DisableIRQ(UART0_IRQn);		//关闭uart0中断
				NVIC_DisableIRQ(WWDT_IRQn);		//关闭wwdt中断
				
				{__disable_irq();Powerd_Flag = 0x12345678;} //关闭全局中断,置停电标志(EA_OFF)
				NVIC_EnableIRQ(RTC_IRQn);		//打开rtc中断
				NVIC_EnableIRQ(GPIO_IRQn);		//打开gpio中断	
				
				//主频调整为512k
				RCC->SYSRCCSEL |= RCC_SYSRCCSEL_AHBPRES_16;
			}
		} 		
 		
 		if ( RTC->RTCIF & RTC_RTCIF_HOUR_IF_ENABLE )//1小时唤醒(仅进行温度补偿)
		{			
			RTC->RTCIF = RTC_RTCIF_HOUR_IF_ENABLE;	//清小时变化标志
			
			if( RAMREG0 == 0x55 )
			{
				Calculate_Min(60);//已小时唤醒
			}
			else
			{
				Calculate_Min((60-RAMREG1));//第一次小时唤醒
				RAMREG0 = 0x55;
			}
				
			//停电温度补偿
			Pd_Adc_Calculate(0x00);//温度Adc计算处理
		}
		
		if ( RTC->RTCIF & RTC_RTCIF_MIN_IF_ENABLE )//1分钟唤醒(仅进行温度补偿)
		{			
			RTC->RTCIF = RTC_RTCIF_MIN_IF_ENABLE;	//清分钟变化标志	
			
			//按键有效时间判断
			if(RAMREG14) RAMREG14--;
			if(RAMREG14 == 0)	//停电2h关闭显示
			{
				RAMREG15 = 0;	//清允许唤醒次数
			}
		}
		
		Clear_Wdt();

		if( GPIO_common->EXTI0IF & BIT5 )//开盖
		{
			GPIO_common->EXTI0IF	= BIT5;		//清按键中断标志位
				
			if( RAMREG2 )//开盖次数限制
			{
				RAMREG10 = 0x55;
				Cover_Space_Timer = def_coverdelaytimer;
			}						
			if(Extbattery == 0x55) Pd_Adc_Calculate(0xaa);  //电池电压测量:电池欠压不支持开盖和按键唤醒					
		}
		if( GPIO_common->EXTI1IF & BIT6 )//显示按键
		{
			GPIO_common->EXTI1IF	= BIT6;		//清按键中断标志位
				
			if( RAMREG15 || Stop_Disptimer ) 
			{
				Displaykey_Process();//显示按键处理
				if( Stop_Disptimer==0 ) 
				{
					Display.Timer = Display_Para.Loop_Time;//第1次循环显示,第2次按键停显30s
					Display.Status &= B1111_1110;//清按键显示标志
					Stop_Disptimer = default_keydisplaytimer/2;//30s
					
					if(Extbattery == 0x55) Pd_Adc_Calculate(0x55);  //停电电源(法拉电容+电池电压)测量
				}
//				else
//				{
//					Stop_Disptimer = default_keydisplaytimer/2;//30s
//				}
					
				if(Extbattery == 0x55) Pd_Adc_Calculate(0xaa);  //电池电压测量:电池欠压不支持开盖和按键唤醒
				if( Stop_Disptimer )
				{
					RCC->SYSRCCSEL &= ~RCC_SYSRCCSEL_AHBPRES_16;
					Lcd_Display();			//刷新显示
					RCC->SYSRCCSEL |= RCC_SYSRCCSEL_AHBPRES_16;
					Lcd_Disp_On();			//打开lcd显示
					display_rtc_flag = 1;
				}
			}
		}
		
		if ( RTC->RTCIF & RTC_RTCIF_SEC_IF_ENABLE )//1s唤醒
		{					
			RTC->RTCIF = RTC_RTCIF_SEC_IF_ENABLE;
			
			if( PowerDetCnt0 >= 3 )
			{
				PowerDetCnt0++;
				
				if(Extbattery == 0x55) Pd_Adc_Calculate(0xaa);  //电池电压测量:电池欠压不支持电源异常检测
				
				if( PowerDetCnt0 >= 5 )
				{
					InputtIO( GPIOB, GPIO_Pin_12, 0 );	//PB9;//RelayTest
					OutputIO( GPIOB, GPIO_Pin_11, 0 );	//PB8;//RelayCtrl//EE_V@电池外置
					RELAYCTRLON;	
					
					__NOP();__NOP();
					PowerError_Check();//电源异常检测(合闸才判断)
					if( RAMREG11 != 0x55 ) PowerDetCnt0 = 0;
					else
					{
						PowerDetCnt0 = 0;
						RAMREG11 = 0xaa;//只有记录发生时才在上电后做结束时间
					}
				
					if(PowerDetCnt0 == 0)
					{
						CloseeIO( GPIOB, GPIO_Pin_12 );
//						CloseeIO( GPIOB, GPIO_Pin_11 );
						RELAYCTRLOFF;						
					}
				}
				else
				{
					Read_Sysclock();//读时钟
				}
			}
			
			if( RAMREG10 == 0x55 )
			{
				if( Cover_Space_Timer )
				{
					Cover_Space_Timer--;
					if( Cover_Space_Timer == 0 ) Read_Sysclock();//读时钟
				}
								 
				SCover_Check();//开盖检测
				if( Cover_Space_Timer == def_coverdelaytimer )  //未检测到开盖或已做记录完毕 
				{
					RAMREG10 = 0;
				}			
				if( RAMREG2 == 0 ) GPIO_common->EXTI0_SEL |= BIT26;//开盖,DISABLE
			}
			
			if( Stop_Disptimer ) 
			{
				Stop_Disptimer--;
				if( (Extbattery == 0x55)&&((Stop_Disptimer&B0000_0011)== 0) ) Pd_Adc_Calculate(0xaa);  //电池电压测量:电池欠压不支持开盖和按键唤醒(显示期间4s检测电池电压以节约功耗)
				if( Stop_Disptimer ) 
				{
					if( Display.Timer ) Display.Timer--;
				
					if( Display.Timer==0 ) display_rtc_flag = 1;
					if( display_rtc_flag )
					{
						if(Extbattery == 0x55) Pd_Adc_Calculate(0x55);  //停电电源(法拉电容+电池电压)测量(解决超级电容故障第一次按键显示效果问题)
						Lcd_Display();			//刷新显示
						Lcd_Disp_On();			//打开lcd显示
					}
				}
				else
				{
					if(RAMREG15) RAMREG15--;	//按键唤醒次数减1
				}	
			}
		}
		
		if( Stop_Disptimer == 0 ) 
		{
			if( (RAMREG15 == 0) || (RAMREG14 == 0) ) 
			{
				GPIO_common->EXTI1_SEL	|= BIT29;	//PD6,显示按键,不使能
				GPIO_common->EXTI1IF	= 0x000000FF;	//清标志位
				GPIO_common->PINWKEN = 0;
			}
			
			Lcd_Disp_Off();//配置lcd黑屏显示
			Display.Number = 0 ;	//从头开始显示
			Disable_I2C_IO();//关闭数据ee电源
		}	
		
		if ( RTC->RTCIF & RTC_RTCIF_DATE_IF_ENABLE )//1天唤醒
		{
			RTC->RTCIF = RTC_RTCIF_DATE_IF_ENABLE;	//清除小时变化以外的标志
			Clr_Zero_Data();//清零点清零数据
		}	
	}
}
