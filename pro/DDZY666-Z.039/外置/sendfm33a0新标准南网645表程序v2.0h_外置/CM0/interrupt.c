#include "ex_var.h"
#include "ex_func.h"
#include "FM32L0XX.h"  
#include <string.h>
#include <stdio.h>


void HardFault_Handler(void) 
{
	RAMREG3 = 0x55;		//�ϵ����㡢���߻���ʱ��0xaa
	
	Clear_W_Wdt();
	PMU->LPMCFG = 2;
	__WFI();
	while(1);
}  

//WWDT�жϷ������,������ȼ�
void WWDT_IRQHandler(void)         
{
	WWDT->WWDTIF = 0x01;//���жϱ�־
	Clear_W_Wdt();
} 

//��ʱʱ��4000us,
void ETIMER2_IRQHandler(void)
{
	unsigned char Ch;
	unsigned int i;

	ETIMER2->ETxIF = 0x03;//���жϱ�־
	
	if( VectorTimer == 0 ) VectorTimer  = ms_timer_delay;
	if( VectorTimer == 1 ) run_readrtc_flag = 1;	//�����ʱ��
	if( (VectorTimer == 50) || (((VectorTimer == 20)||(VectorTimer == 80))&&display_rtc_flag) ) {run_display_flag = 1;}//����ˢ����ʾ
	if( VectorTimer == 100 )
	{
		run_relaychk_flag = 1;	//����̵������
		RELAYCTRLON;		//�򿪿��Ƶ�ƽ
	}
	VectorTimer--;
	
	DisKeySamp<<=1;
	if(DISKEY_N)  DisKeySamp++;	//��ʾ����ȥ���ж�
	
	//ADC����
	if((Adcctrl.Status & B0000_0011)&&(ANAC->ADCIF&1))
	{	
		ADCResultArr.Buffer[ADCResultArr.ReadCount&0x1F] = ANAC->ADCDATA&0x000007FF;
		ADCResultArr.ReadCount++;

		//ת��64��ȡ����32���Ա�֤ת������׼ȷ��
		if(ADCResultArr.ReadCount >= 64)		
		{
			if ( Adcctrl.Status == B0000_0001 ) 
			{
				Adcctrl.Status = B0001_0000;//���adc����
			}
			else
			{
				Adcctrl.Status = B0010_0000;//�¶�adc����
			}
		}
	}
	
	if ( Shiduanctrl.Timer != 0 ) //ʱ��Ͷ���������
	{
		Shiduanctrl.Timer--;
	}
	if( (Shiduanctrl.Timer == 0) && (Outputtype==0x02) ) SHIDUANCTRL_OFF;
		
	if( Relay_Mode != 0x55 )//���ü̵���
	{
		if ( Relayctrl.Timer != 0 ) 
		{
			Relayctrl.Timer--;
		}
		if( Relayctrl.Timer == 0 ) {RELAYOFF1; __NOP(); RELAYOFF2;}//�ű��̵ּ�����Ч
	}
	else
	{
		if(Mode.Feature1&0x01)//���巽ʽ
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

	if( Plusefiltertimer && (Plusefiltertimer <= Def_Plusefiltertimer) && (ACTIVEP_P))//�������ȥ���ж�
	{
		Plusefiltertimer--;//�������嶨ʱ����1
		if( Plusefiltertimer == 0 ) 
		{
			Decimal.Add++;	//��������
		}
	}
	else Plusefiltertimer = 0;
	
	if( Plusefiltertimer2 && (Plusefiltertimer2 <= Def_Plusefiltertimer2) && (REACTIVEP_P))//�޹��������ȥ���ж�
	{
		Plusefiltertimer2--;//�������嶨ʱ����1
		if( Plusefiltertimer2 == 0 ) 
		{
			Decimal.Add_Rp++;//�޹���������
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
					UART_common->UARTIE &= (~UART_TX_IE5);	//�ر�TXIEx
					UART_common->UARTIE |= UART_RX_IE5;	//��RXIEx
//					RXSTA0 &= B1111_0001;
//					{RXSTA0 = 0;RXSTA0 = B0101_0000;}//��λ����FIFO
				}
				if( Ch == CHBLE ) 
				{	
					UART_common->UARTIE &= (~UART_TX_IE1);	//�ر�TXIEx
					UART_common->UARTIE |= UART_RX_IE1;	//��RXIEx
//					RXSTA1 &= B1111_0001;
//					{RXSTA1 = 0;RXSTA1 = B0101_0000;}//��λ����FIFO
				}
				if( Ch == CH485 ) 
				{	
					UART_common->UARTIE &= (~UART_TX_IE2);	//�ر�TXIEx
					UART_common->UARTIE |= UART_RX_IE2;	//��RXIEx
//					RXSTA1 &= B1111_0001;
//					{RXSTA1 = 0;RXSTA1 = B0101_0000;}//��λ����FIFO		
					R485CTRLR;		//�������				
				}
				if( Ch == CHZB ) 
				{	
//					UART_common->UARTIE &= (~UART_TX_IE0);	//�ر�TXIEx
					UART_common->UARTIE |= UART_RX_IE0;	//��RXIEx
//					RXSTA2 &= B1111_0001;
//					{RXSTA2 = 0;RXSTA2 = B0101_0000;}//��λ����FIFO
				}
				Uart[Ch].Step = 0x00;
				Uart[Ch].Flag = 0x00;
				Uart[Ch].Response_Timer = 0x00;
			}
		}
		
		if( (Ch == CHZB) && Uart[Ch].S_Overtime_Timer ) Uart[Ch].S_Overtime_Timer--;//���ͳ�ʱ(�ز�ר��)
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
					if( Ch == CHHW )  			//�����жϷ�������
					{	
						UART5->TXREG  = 0xfe;		//����0xfe
						UART_common->UARTIE &= (~UART_RX_IE5);	//�ر�RXIEx
						UART_common->UARTIE |= UART_TX_IE5;	//��TXIEx
					}
					if( Ch == CHBLE )  			//�����жϷ�������
					{	
						UART1->TXREG  = 0xfe;		//����0xfe
						UART_common->UARTIE &= (~UART_RX_IE1);	//�ر�RXIEx
						UART_common->UARTIE |= UART_TX_IE1;	//��TXIEx
					}
					if( Ch == CH485 ) 
					{	
						R485CTRLS;		//������
						UART2->TXREG  = 0xfe;		//����0xfe
						UART_common->UARTIE &= (~UART_RX_IE2);	//�ر�RXIEx
						UART_common->UARTIE |= UART_TX_IE2;	//��TXIEx
					}
					if( Ch == CHZB ) 
					{	
						UART0->TXREG  = 0xfe;		//����0xfe
//						UART_common->UARTIE &= (~UART_RX_IE0);	//�ر�RXIEx
						UART_common->UARTIE |= UART_RX_IE0;	//��RXIEx
						UART_common->UARTIE |= UART_TX_IE0;	//��TXIEx
					}
					
					Uart[Ch].TxLen  = 1;//��ʼ��������
					Uart[Ch].Total_Tx = Uart[Ch].Buf[9]+16;
					if( Ch != CHZB ) Uart[Ch].Overtime_Timer = txtimeout_max;//���ͳ�ʱ
					else
					{
						Uart[Ch].S_Overtime_Timer= txtimeout_max;//���ͳ�ʱ(�ز�ר��)
						Uart[Ch].Step = 0x00;
						Uart[Ch].Flag &= ~B0000_1111;//����ͨ���ڷ��ͳ�ʱ������ʱ�����
					}
				}
				else
				{
					Uart[Ch].Response_Timer++;//�����ȴ�
				}
			}
		}			
	}
	
	if( Compile_Polar_485 == 0x55 )	//�����޼���485
	{
		if( (Uart[CH485].Response_Timer == 0)&&(Uart[CH485].Overtime_Timer == 0)&&((UART_common->UARTIF&UART_RX_IF2)==0x00) )
		{
			Uart1KeySamp<<=1;
			if(RX485_P)  Uart1KeySamp++;		//��֤���߿���ʱ�ж�,�����޼���485
			
			if( Uart1KeySamp == 0xff ) //�ߵ�ƽ ������
			{
				if( UART2->RTXCON != B0000_0000 )	UART2->RTXCON = B0000_0000;//������ �������ݲ�ȡ��,�������ݲ�ȡ��
			}
			else if( Uart1KeySamp == 0x00 )
			{
				if( UART2->RTXCON != B0000_0011 )	UART2->RTXCON = B0000_0011;//������ ��������ȡ��,��������ȡ��		
			}	 
		} 
		else Uart1KeySamp = 0x55;
	}
	else
	{
		if( UART2->RTXCON != B0000_0000 )	UART2->RTXCON = B0000_0000;//������ �������ݲ�ȡ��,�������ݲ�ȡ��
	}
	
	if( (SVDCHKPLOW) && (Relayctrl.Timer == 0) ) 
	{	
		for(i=0; i<0x700; i++)		//Լ2.5ms @8MHz&3���Ż�
		{
			if( !(SVDCHKPLOW) ) break;
		}		
		if( i==0x700 ) //����
		{
			LCDLEDOFF;//�رձ���(ʡ��)
			RELAYLEDOFF;//�رռ̵���ָʾ��(ʡ��)
			
			for(i=0; i<0x700; i++)		//Լ2.5ms @8MHz&3���Ż�
			{
				if( !(SVDCHKPLOW) ) break;
			}	
			if( i==0x700 ) //����
			{
				if( (ANAC->SVDCFG & ANAC_SVDCFG_SVDLVL_SVS) == ANAC_SVDCFG_SVDLVL_SVS )
				{
					Powerd_Flag = 0x12345678;		//��ͣ���־
					NVIC_DisableIRQ(RTC_IRQn);
					NVIC_DisableIRQ(ETIMER2_IRQn);
					NVIC_DisableIRQ(ETIMER4_IRQn);
					NVIC_DisableIRQ(UART5_IRQn);
					NVIC_DisableIRQ(UART2_IRQn);
					NVIC_DisableIRQ(UART1_IRQn);
					NVIC_DisableIRQ(UART0_IRQn);
					NVIC_DisableIRQ(BT1_IRQn);
					NVIC_DisableIRQ(BT2_IRQn);
//					__disable_irq();//EA = 0;		//�ص�ȫ���ж�
				}
				else reg_veri_flag = 1;
			}
		}
	}			
}


void ETIMER4_IRQHandler(void)
{
	ETIMER4->ETxIF = 0x03;				//���жϱ�־
	
	if ( Plusevalidtimer != 0 ) 	//���������ƴ���
	{
		Plusevalidtimer--;
	}

	if ( Plusevalidtimer == 0 )
	{
		if ( (Outputtype == 3) || (Outputtype == 6) ) CFOUT_OFF;
			
		ETIMER4->ETxCR = 0x00000000;  //��ֹET4����
	}
}

void BT1_IRQHandler(void)
{
	uint08 Temp_IF;
	
	Temp_IF = BTIMER1->BTxIF;
	if( Temp_IF&B0000_1000 ) //�Ƚ�ƥ���ж�
	{
//		if( Temp_IF )
		{
//			if((Emu_Data.I1.B32) && (energy_rst_flag == 0))
			{
				Plusefiltertimer = Def_Plusefiltertimer;		//������������ȥ��
				if( Plusefiltertimer == 0 ) 
				{
					Decimal.Add++;	//��������
				}
				
				if( Outputtype == 6 )
				{
					CFOUT_ON;
					Plusevalidtimer = Def_Plusevalidtimer;	//������ʱ
					ETIMER4->ETxIVR	= 0xffff-0x7d00;
					ETIMER4->ETxCR |= 0x00000080;   //������ʱ��
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
	if( Temp_IF&B0000_1000 ) //�Ƚ�ƥ���ж�
	{
//		if((Emu_Data.I1.B32) && (energy_rst_flag == 0))
		{
			Plusefiltertimer2 = Def_Plusefiltertimer2;		//������������ȥ��(�޹�)
			if( Plusefiltertimer2 == 0 ) 
			{
				Decimal.Add_Rp++;//�޹���������
			}
			
			if( Outputtype == 3 )
			{
				CFOUT_ON;
				Plusevalidtimer = Def_Plusevalidtimer;	//������ʱ
				ETIMER4->ETxIVR	= 0xffff-0x7d00;
				ETIMER4->ETxCR |= 0x00000080;   //������ʱ��
			}
		}
		
		BTIMER2->BTxIF = 0xFF;
	}
}

void UART5_IRQHandler(void)
{
	uint08 Temp;
	uint32 Temp_IF; 
	
	Temp_IF = (UART_common->UARTIF&UART_common->UARTIE); //�κζԼĴ����Ĳ������ᵼ��������, �����Ȼ���
	
	if( (Temp_IF & UART_RX_IF5)  ) //Receive
	{
		Temp = UART5->RXREG; //��UART���ݼĴ�����ȡ��������
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
	
	Temp_IF = (UART_common->UARTIF&UART_common->UARTIE); //�κζԼĴ����Ĳ������ᵼ��������, �����Ȼ���

	if( (Temp_IF & UART_RX_IF2) ) //Receive
	{
		Temp = UART2->RXREG; //��UARTX���ݼĴ�����ȡ��������	
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
	
	Temp_IF = (UART_common->UARTIF&UART_common->UARTIE); //�κζԼĴ����Ĳ������ᵼ��������, �����Ȼ���

	if( (Temp_IF & UART_RX_IF1) ) //Receive
	{
		Temp = UART1->RXREG; //��UARTX���ݼĴ�����ȡ��������	
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
	
	Temp_IF = (UART_common->UARTIF&UART_common->UARTIE); //�κζԼĴ����Ĳ������ᵼ��������, �����Ȼ���

	if( (Temp_IF & UART_RX_IF0) ) //Receive
	{
		Temp = UART0->RXREG; //��UARTX���ݼĴ�����ȡ��������
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
	ANAC->FDETIF = 1;//��XTLFͣ���־
}

	
void RTC_IRQHandler(void)
{
//	if( RTC->RTCIE & RTC_RTCIE_HOUR_IE_ENABLE ) //rtc
//	if( RTCIE&B0000_0100 ) //rtc
//	{
//		if( (PCON&B0000_1100)==0 ) EA = 0;	//�ص�ȫ���ж�(sleep����)
//		else {RTCIF &= B1111_1110; RTCTMRIF = 0;}	//��������жϱ�־
//	}
//	else if( RTCIF&RTCIE ) //rtc
	{		
		if( below_60u_flag == 0 ) //�����¼�������ʼ��ʱ
		{
			if( Meter_Run_Timer1 < Mode.Report_Timer ) Meter_Run_Timer1++;//����ϵ�����ʱ��1(����ϵ�ʱ�䲻��1Сʱ,�����󲻽��е��緢���ϱ�) 
			if( Meter_Run_Timer2 < Mode.Report_Timer ) Meter_Run_Timer2++;//����ϵ�����ʱ��2(����ϵ�ʱ�䲻��1Сʱ,�����󲻽��е�������ϱ�)
		}
		if( Meter_Run_Timer3 < 60 ) Meter_Run_Timer3++; //�ϱ�״̬����ʱ��1s
		Meter_Run_Timer4++; //�ϵ�������ʱ���1s
		
		if( Display.Timer != 0 ) Display.Timer--;
		
		if( Successled.Timer != 0 ) Successled.Timer--;//ͨѶ������ʱ��ʱ����1
		
		if( Keyclose_timer!= 0 ) Keyclose_timer--;//�����պϼ̵�����ʱ����1
		
		Adcctrl.Timer++;
		
	#if( NEWCLOCKADJ == 0 ) //�ɱ�׼ʱ�ӵ�У	
		if( Adcctrl.Timer == 5 )//�������adc 
	#else
		if( (Adcctrl.Timer == 5) && (Adcctrl.Status == 0) )//�������adc 
	#endif
		{
			ADC_ChannelSel(ANAC_ADCCON_ADC_VANA_EN_Voltage);	//���ѹ
			ADC_SetTrim(const_adc_TrimB);			
			BUF4TST_BypassDisable();//�ⲿ����
			BUF4TST_Enable();	//��ѹ			
			BUF4TST_ChannelSel(ANAC_ANATESTSEL_BUF4TST_SEL_AN5);//����ͨ��ѡ��	
			ADC_ITDisable();
			ADC_Enable();			
			Adcctrl.Status= B0000_0001;
		}

	#if( NEWCLOCKADJ == 0 ) //�ɱ�׼ʱ�ӵ�У
		if( Adcctrl.Timer == 10 )//�����¶�adc 
		{
			Adcctrl.Timer = 0;
	#else			
		if( ((Adcctrl.Timer%2) == 0) && (Adcctrl.Status == 0) )//�����¶�adc 		
		{
			if( Adcctrl.Timer >= 10 ) Adcctrl.Timer = 0;
	#endif		
			ADC_ChannelSel(ANAC_ADCCON_ADC_VANA_EN_Temp);	//����	
			ADC_SetTrim(const_adc_TrimT);
			BUF4TST_BypassEn();	//�ڲ�����
			BUF4TST_Disable();	//�ڲ���ѹ	
			ADC_ITDisable();
			ADC_Enable();			
			
			Adcctrl.Status= B0000_0010;
		}	
		
//		if( Display_Space_Timer != 0 ) //����ң�ػ�����ʱ
//		{
//			Display_Space_Timer--;	
//			if( Display_Space_Timer==0 ) Lcdled = Hw_Lcdled_Timer;//�������ⶨʱ��
//		}
		
				
		Lcdled_Control();	//�������
			
		RTC->RTCIF = 0xFFFF;	//�������rtc��־
	}
}
	
void SVD_IRQHandler(void)
{
//	if( (ANAC->SVDCFG&ANAC_SVDCFG_SVDMOD_INTERVAL) == 0 ) //LVIF=1, ����Ƿѹ�����ж�
	{
		ANAC->SVDSIF = 0x00000003;
		ANAC->SVDCFG &= ((~ANAC_SVDCFG_PRIE_Msk)|(~ANAC_SVDCFG_PFIE_Msk));//������ "��ѹ�仯�жϱ�־λ"	
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
		UART_common->UARTIE &= (~(UART_RX_IE5|UART_TX_IE5));	//�ر��ж�
		UART_common->UARTIF = UART_RX_IE5|UART_TX_IE5;		//���жϱ�־
	}
	if( Ch == CHBLE ) 
	{	
		UART_common->UARTIE &= (~(UART_RX_IE1|UART_TX_IE1));	//�ر��ж�
		UART_common->UARTIF = UART_RX_IE1|UART_TX_IE1;		//���жϱ�־
	}
	if( Ch == CH485 ) 
	{	
		UART_common->UARTIE &= (~(UART_RX_IE2|UART_TX_IE2));	//�ر��ж�
		UART_common->UARTIF = UART_RX_IE2|UART_TX_IE2;		//���жϱ�־
	}
	if( Ch == CHZB ) 
	{	
		UART_common->UARTIE &= (~(UART_RX_IE0));		//�رս����ж�
		UART_common->UARTIF = UART_RX_IE0;			//������жϱ�־
	}
}

uint08 Judge_MeterId(uint08 CH)
{
	uint08 i, Temp08;
	
	if( (CH==CHBLE) && (Uart[CH].Step==2) )	//������ַ�ж�A2/A3
	{		
		if( (Uart[CH].Buf[3]==0xFF) || (Uart[CH].Buf[3]==0xFE) || (Uart[CH].Buf[3]==0xFD) )
		{
			if( (Uart[CH].Buf[5]==0xEE) && (Uart[CH].Buf[6]==0xEE) )
			{
				Uart[CH].Step = 0x03; 			//�ȴ�����CMD
				return 0;
			}
		}
		return 0x55;
	}
	
	if( (CH==CHBLE) && (Uart[CH].Step==7)	)	//͸�����ݴ���
	{
		if( Uart[CH].Buf[8] != 0x11 )		//���������Ϊ0x11
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
	
	//ͨѶ��ַ�ж�
	for( i=0; i<6; i++ )
	{
		if( Uart[CH].Buf[ 1+i ] != 0x99 )  break;//��ʾ���ղ��ִ���
	}
	if( i == 6 ) 
	{
		Uart[CH].Flag = B0000_0001;//�㲥��ű�־
		Uart[CH].Step = 0x03; //�ȴ�����CMD
		return 0;
	}
	
	for( i=0; i<6; i++ )
	{
		if( Uart[CH].Buf[ 1+i ] != 0xaa )  break;//��ʾ���ղ��ִ���
	}	
	if( i == 6 ) 
	{
		Uart[CH].Flag = B0000_0010;//ȫaa��ű�־
		Uart[CH].Step = 0x03; //�ȴ�����CMD
		return 0;
	}
	
	for( i=0; i<6; i++ )
	{	
		if( (Uart[CH].Buf[ 1+i ] != Comm_Addr.Comm_Id[ 5-i ]) )
		{
			for( ; i<6; i++ )
			{
				if( Uart[CH].Buf[ 1+i ] != 0xaa ) break;//��ʾ���ղ��ִ���
			}
			if( i == 6 ) Uart[CH].Flag = B0000_0010;//����λ��ַ��־
			break;
		}
	}
	if( i == 6 )  
	{
		Uart[CH].Step = 0x03; //�ȴ�����CMD
		return 0;
	}
	
	return 0x55;
}

void Judge_645_Frame( uint08 CH, uint08 RcvData ) //using 1 //���մ���
{
	unsigned char i, n, m, status=0;
	
	Uart[CH].Overtime_Timer = txtimeout_max;//���ճ�ʱ
			
	switch( Uart[CH].Step )
	{
		case 0x00: //�ȴ�����0x68
				if( RcvData == 0x68 )
				{
					Uart[CH].Step = 0x01; //�ȴ�����id.
					Uart[CH].Len = 0;
				}
				else
				{
					status = 0xaa;	//��ʾ���մ���		
				}
				break;
			
		case 0x01: //�ȴ�����id.
				if ( (Uart[CH].Len) >= 6 )
				{
					Uart[CH].Step = 0x02; //�ȴ����յڶ���0x68
				}
				break;
	
		case 0x02: //�ȴ����յڶ���0x68
				if( RcvData == 0x68 )
				{
					if( CH == 0 )
					{
						Lcdled = Hw_Lcdled_Timer;//�������ⶨʱ��
						LCDLEDON;
					}
					
					Uart[CH].Flag = 0x00;//ͨѶ��־����
					
					status = Judge_MeterId(CH);
				}
				else status = 0x55;
				break;
	
		case 0x03: //�ȴ�����cmd.
				Uart[CH].Step = 0x04; //�ȴ�����LEN
				break;
	
		case 0x04: //�ȴ�����len
				if( RcvData == 0x00 )
				{
					Uart[CH].Total_Len = RcvData;
					Uart[CH].Step = 0x06; //����cs
				}
				else 
				{
					if( RcvData <= (urx_buf_size-12) )
					{
						Uart[CH].Total_Len = RcvData;
						Uart[CH].Step = 0x05; //�ȴ�����DATA
					}
					else
					{
						status = 0xaa;	//��ʾ���մ���
					}
				}
				break;
	
		case 0x05: //�ȴ�����DATA
				if( Uart[CH].Len == ( Uart[CH].Total_Len + 0x09) ) //֡���������
				{
					Uart[CH].Step = 0x06; //�ȴ�����cs.								
				}
				
				if( Uart[CH].Len > ( Uart[CH].Total_Len + 0x09) ) //֡���������
				{
					status = 0xaa; //��ʾ���մ���									
				}
				
				break;
	
		case 0x06: //�ȴ�����cs.
				Uart[CH].Step = 0x07; //�ȴ�����0x16
				break;
	
		case 0x07: //�ȴ�����0x16
				if( RcvData == 0x16 )
				{
					Uart_IE_Disable_Proc( CH );
					
					if( CH == CHBLE )
					{
						memcpy(Ble_Buf, Uart[CH].Buf, 8);		//�ݴ�����ͷ
						
						if( (Uart[CH].Buf[3] == 0xFE)||(Uart[CH].Buf[3] == 0xFD) )//͸�����ݴ���
						{
							if( Judge_MeterId(CH) )
							{
								status = 0xaa;	//��ʾ���մ���;
								break;
							}
						}
					}
					
					Uart[CH].Step = 0x08;//�ֽڽ�����ȷ
					Uart[CH].Overtime_Timer = 0x00;//����ճ�ʱ
					Uart[CH].Response_Timer = framedelay_mx;//����Ӧ��ʱ
					Uart[CH].Flag |= B0000_0100;//����֡���ݽ�����ɱ�־
                                	
					if( CH == CHZB ) display_zaibo_flag = 1;
					else display_zaibo_flag = 0;
					
					if( CH == CHBLE ) display_ble_flag = 1;
					else display_ble_flag = 0; 
				}
				else
				{
					status = 0xaa;	//��ʾ���մ���
				}
				break;
	
		default: 
				status = 0xaa;	//��ʾ���մ���
				break;
		
	}

	if( status == 0x00 )	//�ֽڽ�����ȷ
	{
		Uart[CH].Buf[Uart[CH].Len] = RcvData;
		Uart[CH].Len++;
	}
	
	if( status == 0x55 )	//��Ŵ�����ߵڶ���68h����,��Ҫ������68h
	{
		status = 0xaa;//���մ���
		
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
					status = 0x00;//���վ���ɹ�
					break;
					       
				}					
			}
		}
	}	
	
	if( Uart_RXErr_Proc( CH ) == 0xaa ) //�ж��Ƿ�����·����
	{
		status = 0xaa;
		if( CH == CHHW )
	   {
//		if ( Display_Space_Timer==0 ) 
//		{
//			for( i=0; i<20; i++ )//ȥ��150us
//			{
//				if( RXHW_P ) break;
//			}
//			if( i==20 ) Display_Space_Timer = 2;//����2sȥ��ʱ��	
//		}
	   }
	}
		
	if( status == 0xaa )	//���մ���
	{
		Uart[CH].Step = 0x00;
		Uart[CH].Overtime_Timer = txtimeout_max/5;
	}
}


void Tx_645_Frame( uint08 Ch )	//using 1	//���ݷ���
{
	uint08 Temp08;
	
	if( Uart[Ch].TxLen >= Uart[Ch].Total_Tx )
	{
		if( (Ch==CHBLE) && (Ble_Reset==0x55) ) {Ble_Reset=0xAA; reg_veri_flag = 1;} //��λ����ģ��
		if( UpdateBps ) {UpdateBps = 0; reg_veri_flag = 1;} //ͨ���Ĵ���У�����bps�޸�
		
		if( Ch != CHZB ) Uart[Ch].Overtime_Timer = 2;//ͨ����ʱ���Ƹ�λͨѶ
		else  Uart[Ch].S_Overtime_Timer= 0;//���ͳ�ʱ(�ز�ר��)
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
		if( Ch != CHZB ) Uart[Ch].Overtime_Timer = txtimeout_max;//���ͳ�ʱ
		else Uart[Ch].S_Overtime_Timer= txtimeout_max;//���ͳ�ʱ(�ز�ר��)
	}
}

void Lcdled_Control()	//using 1	//�������
{
	if( Lcdled != 0 ) Lcdled--;
	
	if( Lcdled || Opendelaytimer || relay_delay_flag || relay_commu_alarm_flag || 
		((low_voltage_flag||Bat_Delay_Timer) && (Mode.Plc&0x02)) || (dl_back_flag && (Mode.Plc&0x01)) )
	{
		LCDLEDON;
	}
	else if( relay_status_flag && relay_commu_disable_close_flag )	//�������ں�բ����������⣨2021��
	{
		LCDLEDON;
	}
	else if( relay_status_flag && (relay_commu_disable_close_flag ==0) && relay_commu_open_flag )	//����ͨѶ��բ��������
	{
		LCDLEDON;
	}
	else if( (Relay_Mode!=0x55) && (relay_status_flag==0) && relay_error && (relay_commu_close2_flag==0) ) //������բʧ�ܵ�������(���ü̵���)(��������)
	{
		LCDLEDON;
	}
	else if( (Relay_Mode==0x55) && (relay_status_flag==0) && (comm_relaystatus_flag == 1) && (relay_success_flag==0) )//������բ��ʱ���̵�������(���ü̵���)
	{
		LCDLEDON;
	}
	else
	{
		LCDLEDOFF;
	}
	
	
	if( Init_Led_Timer != 0 ) Init_Led_Timer--;	//ledָʾ�ƶ�ʱ����1
	
	if( Init_Led_Timer )
	{
		RELAYLEDON;
	}
	else if( relay_commu_disable_close_flag )      //1s��˸��բָʾ��
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


unsigned char Judge_Io_Status()	//����Դ�쳣io��״̬
{	
	unsigned int i;
	
	i =0;
	Do_DelayStart();	//2ms��ʱ�ж�
	{
		if( RELAYTEST_P ){
      			i = 1;
      			break;
		}
	}While_DelayUsEnd(125);	//125*16=2ms,@512K
	
	if( SVDCHKPLOW )
	{	
		if( i == 0 )	return 0x55;	//�͵�ƽ����2ms����Ϊ��Դ�쳣(����Ƿѹ)
	}
	
	return 0;
}


void PowerError_Check()		//��Դ�쳣���
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
		if( i == 160 ) //����
		{
			if( Cover_Space_Timer )	return;		//������ʱδ��
			
			Cover.Status = 1;
			RAMREG12 = 0xaa;
			memcpy( RAMBUF, Sclock.Clockbackup, 6 );//���濪�Ƿ���ʱ��(���ʱ������)
		}
	}
	else if( (Cover.Status) && (COVKEY_N) )
	{
		for( i=0; i<160; i++ )
		{
			if( COVKEY_P ) break;
		}
		if( i == 160 ) //�ϸ�
		{
			if( Cover_Space_Timer )	return;		//������ʱδ��
			
			Cover.Status = 0;
			if( RAMREG12 == 0xaa ) RAMREG12 = 0xbb;
			else RAMREG12 = 0x55;
			memcpy( RAMBUF+6, Sclock.Clockbackup, 6 );//���濪�ǽ���ʱ��(���ʱ������)
			if( RAMREG2 ) RAMREG2--;		//ͣ�翪�Ǵ�����1
		}
	}
	
	Cover_Space_Timer = def_coverdelaytimer;//������ʱʱ��
}


//mode=1д����β�����¼���־,mode=0����β�����¼���־����
//ÿСʱ/����ʱ��/����/����ʱд����ee
void Wr_Powerdown_Data( unsigned char mode )	//д����������ݵ�����ee
{
	unsigned char  Buf[ee_powerdown_lenth+2];
	
	memset( Buf, 0x00, ee_powerdown_lenth );
	
	//ee_power_down_page: ����ʱ��(7)+��������(2)+�¼���־(1)+ʧѹ�¼�(8)+�͵�ѹ�¼�(2)+�ߵ�ѹ�¼�(2)+�ϱ�����(1)+ͬ����־(3)+���ɼ�¼ָ��(40+2)+crc(2)����62+2�ֽ�
	memcpy( Buf, Sclock.Clockbackup, 7 );//ʱ��

	if( mode )
	{
		Buf[7] = Decimal.Add;//�����й���������
		Buf[8] = Decimal.Add_Rp;//�����޹���������
		
		if( below_60u_flag==0 ) Buf[9] |= 0x80;//�����¼���ʼ��¼
		if( relay_error ) Buf[9] |= 0x40;//���ɿ����쳣������¼
		if( load_over_flag ) Buf[9] |= 0x20;//��¼���������¼�(����)
		if( cal_err_flag ) Buf[9] |= 0x10;//����оƬ���Ͻ�����¼
		if( nline_err_flag ) Buf[9] |= 0x08; //���ߵ����쳣������¼
		if( lost_v_flag )//��¼ʧѹ�¼�(����)
		{
			Buf[9] |= 0x04;//��¼ʧѹ�¼�(����)
			memcpy( Buf+10, &Lost_Aver_I, 4 );
			memcpy( Buf+14, &Lost_V_Timer, 4 );
		}
		if( Current_Over_Count41 )
		{
			Buf[9] |= 0x02;
			memcpy( Buf+18, &Current_Over_Count41, 2 );//����͵�ѹ�¼���ʱ�ۼ�ʱ��
		}
		if( Current_Over_Count51 )
		{
			Buf[9] |= 0x01;
			memcpy( Buf+20, &Current_Over_Count51, 2 );//����ߵ�ѹ�¼���ʱ�ۼ�ʱ��
		}
		
		Buf[22] = ReportList[0]&B0011_0000; //���� �����ϱ�����(�����ϱ�����)
		
		Buf[23] = MvFlash.Obj;
		if( 0x55 == MvFlash.Dir ) Buf[23] |= 0x40; //bit6
		if( 0xAA == MvFlash.Dir ) Buf[23] |= 0x80; //bit7
		Short2Byte( MvFlash.Offset, Buf+24 );
	}
	
	memcpy( Buf+26, Load.Point, ee_loadpoint_lenth+2 );//���渺�ɼ�¼ָ��(��crc)
	
	I2C_Write_Eeprom( ee_power_down_page, 0x00, Buf, ee_powerdown_lenth);//д�������ݵ�����ee
}

//���ۼ�ʱ�䴦��
//���缰����ʱ���������ۼ�ʱ�䲢���µ�EE�������RAM�������㣬�����ۼ�
//Store=0��ֻ����Store=1���洢
void Save_Keep_Timer( unsigned char Store )
{
	unsigned char i;
	uint32 Temp32;
	
	if( Store && (ChkBufZero( (uint08*)&Keeptime.Times[0], ee_illegalcardnum_len )==0) ) return;	//ȫ0�����豣��
	
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

//ͨѶ��������ۼ�ʱ��
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
	Disable_Pulse();//�ر�����(ʡ��)
	if( Relay_Mode != 0x55 )//���ü̵���
	{
		{RELAYOFF1; __NOP(); RELAYOFF2;}//�ű��̵ּ�����Ч
	}
	LCDLEDOFF;//�رձ���(ʡ��)
	RELAYLEDOFF;//�رռ̵���ָʾ��(ʡ��)
	BLEPOWEROFF;//�ر�����(ʡ��)
	if( status )//��ʼ������Sleep()�򲻱�������,��ֹ����ϵ練����������(���ݵ�����÷���)
	{
		if( Decimal.Status&B0001_0000 ) I2C_Write_Eeprom( ee_fwdl_page, ee_fwdl_inpage, Fwdl.Pluse[0].B08, ee_fwdl_lenth+2 );
		if( Decimal.Status&B0010_0000 ) I2C_Write_Eeprom( ee_bkdl_page, ee_bkdl_inpage, Bkdl.Pluse[0].B08, ee_bkdl_lenth+2 );
		for(i=0; i<4; i++)
		{
			if( Decimal.Status&(1<<i) ) I2C_Write_Eeprom( ee_rpdl_page+2*i, ee_rpdl_inpage, Rpdl[i].Pluse[0].B08, ee_rpdl_lenth+2 );
		}
		
		Read_Sysclock();//��ʱ��
		Wr_Powerdown_Data(1);//д����������ݵ�����ee
		
		I2C_Write_Eeprom( ee_monthvolrun_page, ee_monthvolrun_inpage, VolStatus[0].Total.B08, ee_monthvolrun_lenth );//�����պ��µ�ѹ�ϸ�������״̬
		
		real_relaystatus_flag = (relay_status_flag^relay_error);
		System_St_Bk = (System_Status&0x3f);//����״̬��
		if( Cover.Status ) System_St_Bk |= 0x80;//���濪��״̬
		I2C_Write_Eeprom( ee_reportdata_page, 0, &System_St_Bk, ee_reportdata_lenth);//�����¼��ϱ����ݷ�ֹ����
		
		Save_Keep_Timer(1);//��������ۼ�ʱ��
		
		for( i=0; i<max_casecount; i++ )
		{
			if( Load.Point[5*i+3] )	break;
		}
	
		if( i < max_casecount )
			I2C_Write_Eeprom( ee_ploadrec_page, 0, LoadBuf, ee_ploadrec_lenth );
		
		//ͣ�������ϱ�����
		RAMREG13 = 0;
		if( below_60u_flag==0 )
		{
			ReportList[0] = 0;
			ReportList[1] = 0;
			Note_Run_Event( ee_powerdownn_inpage ); //�����¼���ʼ��¼
				
			if( ReportList[0]&B0000_0011 ) RAMREG13 = def_powerdown_timer;//����ͣ���ϱ���ʱ��
		}
		Meter_Run_Timer1 = 0;//�����ϵ�����ʱ��1
				
		if( Mode.Report[4]&(1<<5) )		//ͣ������������ϱ�
		{
			if( Meter_Run_Timer2 < Mode.Report_Timer ) Meter_Run_Timer2 = 0;//�����ϵ�����ʱ��2
		}
		else Meter_Run_Timer2 = 0;//�����ϵ�����ʱ��2
			
		//��������ǰ���ϱ�
		if( below_60u_flag && (ReportList[0]&B0000_0011) ) RAMREG13 = ReportList[0]&B0000_0011;
				
		if( (Mode.Feature1&0x0c)!=0x08 )//�����ϱ�δ����,���ϱ�
		{
			ReportList[0] = 0;
			ReportList[1] = 0;
			Meter_Run_Timer1 = 0;//�����ϵ�����ʱ��1
			Meter_Run_Timer2 = 0;//�����ϵ�����ʱ��2
			RAMREG13 = 0;
		}
	}
	
	RAMREG0 = 0x00;//��ʾδСʱ����
	RAMREG1 = Bcd_To_Hex(Sclock.Clockbackup[1]);//ͣ��ʱ�ķ�����
	RAMREG2 = 1;//����1������
	RAMREG3 = 0;//�建��������־�ֽ�
//	RAMREG4 = 0;//��������־
	
//	RAMREG5 = 0;//����������
//	RAMREG6 = 0;//������մ���
//	RAMREG7 = 0;//�������һ�����մ���
//	RAMREG8 = 0;//�½�����һ�����մ���
	
//	RAMREG9 = 0;//����״̬��
	
	RAMREG10 = 0;//���Ǵ�����
	RAMREG11 = 0;//��Դ�쳣״̬
	RAMREG12 = 0;//����״̬
	
	RAMREG14 = 120;//ͣ��2h�ر���ʾ
	RAMREG15 = 10;//����������10��
	
	memset( Emu_Data.U.B08, 0x00, 36 );//��ѹ�������ʹ�����������
	Emu_Data.Cosa.B32 = 0x1000;
	System_Status1 = 0;//����״̬��1
}

void Lcd_Disp_Off()//����lcd������ʾ
{			 	
	Lcd_LCDEN_Off();	//�ر�lcd��ʾ
}

void Lcd_Disp_On()//����lcdͣ����ʾ
{
	Veri_Disp(0);
	Lcd_LCDEN_On();		//��lcd��ʾ
}


void Close_And_ClearIRQ(IRQn_Type IRQn)
{
	NVIC_DisableIRQ(IRQn);
	NVIC_ClearPendingIRQ(IRQn);	
}

void Configure_Register_Sleep()//sleepǰ���üĴ���
{

//	GPIO14CFG = B0100_0000;//RXHW, RXD0
//	GPIO32CFG = B0100_0000;//PLCA
//	GPIO33CFG = B0100_0000;//PLCRST	
//	GPIO35CFG = B0100_0000;//PLCEVT
//	GPIO36CFG = B0100_0000;//RX3,	RXD2
//	GPIO41CFG = B0100_0000;//SAMIO,	ESAM��IO��
//	GPIO42CFG = B0100_0000;//ICIO, 	CARD��IO��

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
//	CloseeIO( GPIOB, GPIO_Pin_11 );		//PB11;//RelayCtrl//EE_V@�������	
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
	if( Relay_Mode == 0x55 )	//���ü̵���
	{
		CloseeIO( GPIOD, GPIO_Pin_4 );		//PD4;//RelayOn, �̵������ƽ�
		CloseeIO( GPIOD, GPIO_Pin_5 );		//PD5;//RelayOff,�̵������ƽ� 
	}
	InputtIO( GPIOD, GPIO_Pin_6, 1 );	//PD6;//DISPKEY,������
	CloseeIO( GPIOD, GPIO_Pin_7 );		//PD7;//EsamVcc
	
	CloseeIO( GPIOE, GPIO_Pin_2 );		//PE2;//LCDLED	
	CloseeIO( GPIOE, GPIO_Pin_3 );		//PE3;//485Ctrl
	CloseeIO( GPIOE, GPIO_Pin_4 );		//PE4;//VFLASH
	CloseeIO( GPIOE, GPIO_Pin_5 );		//PE5;//PLCEVT(OD���)
		
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
	CloseeIO( GPIOG, GPIO_Pin_6 );		//PG6;//TM���
	CloseeIO( GPIOG, GPIO_Pin_7 );		//PG7;//ESAMRST
	CloseeIO( GPIOG, GPIO_Pin_8 );		//PG8;//SWDTCK/LEDRelay
	CloseeIO( GPIOG, GPIO_Pin_9 );		//PG9;//SWDTDO/COM_RQ	

	ANAC->ADCCON   = 0; //��ʹ��ADC
	RCC->PLLCON	  &= (~RCC_PLLCON_PLLEN_ON); //�ر����໷
	BUF4TST_Disable();
	
	Disable_I2C_IO();//�ر�����ee��Դ

	Lcd_Disp_Off();//����lcd������ʾ
	Stop_Disptimer = 0;//ͣ����ʾʱ������
	Display.Number = 0;
	Display.Status = 0;//�尴����ʾ��ر�־
	
	//��ʼ��ͣ����ʾ����
	Display_Para.S_Number = Def_SleepDisplayPara_table[0]; 
	Display_Para.Loop_Time = Def_SleepDisplayPara_table[1]; 
	Display_Para.K_Number = Def_SleepDisplayPara_table[4];
	//��ʼ��ͣ����ʾ����
	memset( &Item[0].Display[0], 0x01, ee_displayitem_lenth );
	memcpy( &Item[0].Display[0], Def_Sleepdisp_table, sizeof(Def_Sleepdisp_table) );//Ĭ��ͣ��ѭ����ʾ
	memset( &Item[1].Display[0], 0x01, ee_displayitem_lenth );
	memcpy( &Item[1].Display[0], Def_Sleepdisp_table, sizeof(Def_Sleepdisp_table) );//Ĭ��ͣ�簴����ʾ

	//��Ҫ�򿪵Ļ����ж�
	if( (PowerDetCnt1 < 4)&&(PowerDetCnt2 < 8) )//������е�Դ�쳣���
	{
		PowerDetCnt0 = 3;
	}
	else
	{
		PowerDetCnt0 = 0;
	}
	RTC->RTCIE = RTC_RTCIE_SEC_IE_ENABLE;		//���ж�ʱ�Ӵ�
	NVIC_DisableIRQ(RTC_IRQn);
	NVIC_SetPriority(RTC_IRQn,2);
	NVIC_EnableIRQ(RTC_IRQn);		
	
	GPIO_common->EXTI0_SEL	= BIT27|BIT11;		//PB5,���ǰ���,������
	GPIO_common->EXTI1_SEL	= BIT28|BIT13;		//PD6,��ʾ����,�½���
	GPIO_common->EXTI0IF	= 0x000000FF;		//���־λ
	GPIO_common->EXTI1IF	= 0x000000FF;		//���־λ
	NVIC_DisableIRQ(GPIO_IRQn);
	NVIC_SetPriority(GPIO_IRQn,2);
	NVIC_EnableIRQ(GPIO_IRQn);
	GPIO_common->PINWKEN = BIT7;	//ʹ��PD6��NWKUP7����
	
	//�رշǻ����ж�
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


void Calculate_Min(unsigned char Result)//ͣ����Ӽ��㴦��
{
	unsigned char i;
	if( Result == 0 ) return;//�Ƿ�����
	if( Result > 60 ) return;//�Ƿ�����
	i = Result;//i��Χ0~60min
	if( Progkey.Timer >= i )//�����ʱ��60
	{
		Progkey.Timer -= i;
	}
	else	
	{
		Progkey.Timer = 0;
	}

	if(low_voltage_flag) 
	Keeptime.Times[2] += i;//�ۼƵ��Ƿѹʱ��
	Keeptime.Times[3] += i;//�ۼƵ����ۼ�ʱ��
	Keeptime.Times[4] += i;	//�ۼƵ�ع���ʱ��	

}

//////////////////////////////////////////////////////////////////////
void Pd_Adc_Calculate( unsigned char Type )	//0x55:ͣ���Դ(��������+��ص�ѹ)����,0xaa:��ص�ѹ����,����:ͣ���¶�adc����
{
	unsigned char i;
	
	ADCResultArr.ReadCount = 0;
				
	if( Type == 0xaa ) return;	//��ص�ѹ������������ʹ��û�е�ص��������Ȼ֧�ְ�����ʾ�Ϳ��Ǽ�⣩
	
	if( Type == 0x55 )//ͣ���Դ(��������+��ص�ѹ)����
	{
		//��Դ����(������ʾ��ѹ����Һ����ʾ)          
		ADC_ChannelSel(ANAC_ADCCON_ADC_VANA_EN_Voltage);	//���ѹ
		ADC_SetTrim(const_adc_TrimB);			
		BUF4TST_BypassEn();	//���Դ��ѹ����ʹ��
		BUF4TST_Enable();	//����ͨ��buffʹ��			
		BUF4TST_ChannelSel(ANAC_ANATESTSEL_BUF4TST_SEL_VDD50);//ѡ���Դ��ѹ	
		
		Adcctrl.Status = B0001_0000;//��Դadc����	
		
	}
	else if( Type == 0xaa )
	{
		//��ص�ѹ����(���Ƿѹ��رյ�Դ���,������ʾ�Ϳ��Ǽ��)
		ADC_ChannelSel(ANAC_ADCCON_ADC_VANA_EN_Voltage);	//���ѹ
		ADC_SetTrim(const_adc_TrimB);			
		BUF4TST_BypassDisable();//�ⲿ����
		BUF4TST_Enable();	//��ѹ			
		BUF4TST_ChannelSel(ANAC_ANATESTSEL_BUF4TST_SEL_AN5);//����ͨ��ѡ��	
		
		Adcctrl.Status = B0001_0000;//��Դadc����
	}
	else
	{
		//�¶�adc����
		ADC_ChannelSel(ANAC_ADCCON_ADC_VANA_EN_Temp);	//����	
		ADC_SetTrim(const_adc_TrimT);
		BUF4TST_BypassEn();	//�ڲ�����
		BUF4TST_Disable();	//�ڲ���ѹ
			
		Adcctrl.Status = B0010_0000;//�¶�adc����	
	}
	
	
	ADC_ITDisable();
	ADC_Enable();	
	
	TicksDelayUs(250);	//250*16=4000US,@512K
	ADCResultArr.Buffer[ADCResultArr.ReadCount&0x1F] = ANAC->ADCDATA&0x000007FF;
	TicksDelayUs(250);	//250*16=4000US,@512K
	//ת��32��ȡ����32���Ա�֤ת������׼ȷ��
	for( i=0; i<32; i++ )
	{
		ADCResultArr.Buffer[ADCResultArr.ReadCount&0x1F] = ANAC->ADCDATA&0x000007FF;
		ADCResultArr.ReadCount++;
	}
	
	BUF4TST_Disable();	//�ر�buffer,���Խ���10uA���ҵĹ���
	ADC_Disable();
	Adc_Proc();					
	
	if( Type == 0x55 )//ͣ���Դ(��������+��ص�ѹ)����
	{
		union B16_B08_2 Temp16;
		
		Fun_Para.Voltage_P = Fun_Para.Voltage_B;
		
		//����ͣ�糬�����ݵ�ѹ
		RAMBUF[12] = 0x55;
		Exchange( Temp16.B08, (unsigned char *)&Fun_Para.Voltage_P, 2 ); 
		Bcd2Hex_LS( Temp16.B08, Temp16.B08, 2 );
		Temp16.B16 = Temp16.B16/2 + 60 ;//���϶����ܵ�ѹ
		Hex2Bcd_SS( Temp16.B08, RAMBUF+13, 2 );
		RAMBUF[15] = 0x55;
	}
	else if( Type == 0xaa )//��ص�ѹ����
	{
		if( Fun_Para.Voltage_B <= 0x250 )	//���Ƿѹ��رյ�Դ���,������ʾ�Ϳ��Ǽ��
		{
			PowerDetCnt0 = 0;		//ֹͣ��Դ�쳣���
			RAMREG10 = 0;			//ֹͣ���Ǽ��
			Stop_Disptimer= 0;		//ֹͣ��ʾ
			RAMREG14 = 0;
			RAMREG15 = 0;
		}	
	}
}


void Reset()	//���Ѹ�λ
{	
	Enable_I2C_IO();
	Read_Sysclock();//��ʱ��
	
	if( RAMREG0 == 0x55 )
	{
		Calculate_Min(Bcd_To_Hex(Sclock.Clockbackup[1]));//��Сʱ����
	}
	else	
	{	
		Calculate_Min(((Bcd_To_Hex(Sclock.Clockbackup[1])-RAMREG1)+60)%60);//δСʱ����
	}

	Save_Keep_Timer(1);
	
	System_St_Bk = System_Status; //����ϵͳ״̬��	
	RAMREG3 = 0xaa;

//	Powerd_Flag = 0x87654321;//�������wwdt��λ����hardfalut����
//	while(1)
//	{
//		WWDT->WWDTCON = 0xac;//��wwdt
//	}
	
	RCC->SOFTRST = 0x5C5CAABB;	//��λ,��ͷ��ʼ����
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
		PMU->LPMCFG |= BIT8;//ʹ���ں˵�ѹ����1.2
	}
	else
	{
		PMU->LPMCFG &= (~BIT8);
	}
	//=================================

//	WTCFG = 0x0C;//B0000_0000;//���ѵȴ�ʱ��		
	
	//=================================
	if( RamRMode == 0 )
	{
		PMU->LPMCFG &= (~BIT10);//RAM���ݱ���			
	}
	else
	{
		PMU->LPMCFG |= BIT10;//RAM�����ֵ�16K����
	}
	
	SCB->SCR = 0;						//SLEEP
	
	PMU->LPMCFG = (PMU->LPMCFG&0xfffffffc)|BIT1;		//SLEEP
}

void Sleep( uint08 status )
{
	unsigned int i;

	//�ڽ���sleepǰ�ٴν���ȥ��
	Do_DelayStart();		//Լ4ms
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
			return;		//����������EA = 1;
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
	if( i==0 ) Reset();		//��ѹ�ָ����������sleepֱ��Reset�ϵ�
	
	//�µ縴λ��Ҫ��~~
	ANAC->BORCON = SleepBorCfg;
	ANAC->PDRCON = SleepPdrCfg;		
	RCC->XTLFIPW = rtcosccfg;
	GPIO_common->EXTI0IF	= 0x000000FF;		//�尴���жϱ�־λ
	GPIO_common->EXTI1IF	= 0x000000FF;		//���־λ
	
	for( ; ; )
	{			
		Clear_Wdt();
		
		RTC->RTCIF = RTC_RTCIF_SEC_IF_ENABLE;	//��������жϱ�־
		NVIC_ClearPendingIRQ(RTC_IRQn);
		NVIC_ClearPendingIRQ(GPIO_IRQn);

		if( LCD_SOFF )
		{
			DeviceSleepCFG(1,0,0);//deepsleep + RAM����
		}
		else
		{
			DeviceSleepCFG(0,0,0);//sleep + RAM����
		}
		
		ANAC->SVDCON &= ~ANAC_SVDCON_SVDEN_ENABLE;//��ѹ����·�ر�
		
//		if( SVDCHKPLOW )//����Ƿѹ
		{
//			__enable_irq();//EA = 1;			//��ȫ���ж�
			__WFI();
//			__disable_irq();//EA = 0;			//�ص�ȫ���ж�
		}
		
		Clear_Wdt();
		
		ANAC->SVDCFG  = ANAC_SVDCFG_SVDLVL_SVS+ANAC_SVDCFG_DFEN_ENABLE;
		ANAC->SVDCON |= ANAC_SVDCON_SVDEN_ENABLE;//��ѹ����·ʹ��
		
		if( !(SVDCHKPLOW) )	//sleepǰ�ٴ�ȥ��,1ms
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
//			if( (RAMREG13%10) == 0 ) //���ڼ�⵽�����ÿ10�뷢һ��,����3��,������Ӧ��
			{
				//ͣ���ϱ��ڼ���Ƶ8M
				RCC->SYSRCCSEL &= ~RCC_SYSRCCSEL_AHBPRES_16; 
				
				//�ϱ�����
//				AltFunIO( GPIOF, GPIO_Pin_3, 0 );	//PF3;//RXZB RXD0 
				AltFunIO( GPIOF, GPIO_Pin_4, 1 );	//PF4;//TXZB TXD0 (OD���)
//				AltFunIO( GPIOF, GPIO_Pin_4, 0 );	//PF4;//TXZB TXD0
				
				UART_common->UARTIE = UART_TX_IE0;	//�򿪽����жϺͷ����ж�
				UART_common->UARTIF = UART_TX_IE0;	//����պͷ����жϱ�־
				
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
				NVIC_EnableIRQ(UART0_IRQn);		//��uart0�ж�
				
				NVIC_DisableIRQ(WWDT_IRQn);
				NVIC_SetPriority(WWDT_IRQn,1);
				NVIC_EnableIRQ(WWDT_IRQn);		//��wwdt�ж�(��������wwdt��λ)
				
				NVIC_DisableIRQ(RTC_IRQn);		//�ر�rtc�ж�
				NVIC_DisableIRQ(GPIO_IRQn);		//�ر�gpio�ж�(��������iwdt��λ)	
				{Powerd_Flag=0;__enable_irq();}		//��ͣ���־(EA_ON),ͬʱ���ж�
				
				//�����ϱ�
				progenable = 1;				//ͣ��������ķ�ʽ�����ϱ�
				ReportEvent(1);
				
				//600ms���ͳ�ʱ����
				Do_DelayStart();
				{
					Clear_Wdt();
					if( Uart[CHZB].S_Overtime_Timer == 0 ) break;
				}While_DelayMsEnd( 600 );	
				
				//�ϱ�����
//				CloseeIO( GPIOF, GPIO_Pin_3 );		//PF3;//RXZB RXD0 
				CloseeIO( GPIOF, GPIO_Pin_4 );		//PF4;//TXZB TXD0 (OD���)
				
				NVIC_DisableIRQ(UART0_IRQn);		//�ر�uart0�ж�
				NVIC_DisableIRQ(WWDT_IRQn);		//�ر�wwdt�ж�
				
				{__disable_irq();Powerd_Flag = 0x12345678;} //�ر�ȫ���ж�,��ͣ���־(EA_OFF)
				NVIC_EnableIRQ(RTC_IRQn);		//��rtc�ж�
				NVIC_EnableIRQ(GPIO_IRQn);		//��gpio�ж�	
				
				//��Ƶ����Ϊ512k
				RCC->SYSRCCSEL |= RCC_SYSRCCSEL_AHBPRES_16;
			}
		} 		
 		
 		if ( RTC->RTCIF & RTC_RTCIF_HOUR_IF_ENABLE )//1Сʱ����(�������¶Ȳ���)
		{			
			RTC->RTCIF = RTC_RTCIF_HOUR_IF_ENABLE;	//��Сʱ�仯��־
			
			if( RAMREG0 == 0x55 )
			{
				Calculate_Min(60);//��Сʱ����
			}
			else
			{
				Calculate_Min((60-RAMREG1));//��һ��Сʱ����
				RAMREG0 = 0x55;
			}
				
			//ͣ���¶Ȳ���
			Pd_Adc_Calculate(0x00);//�¶�Adc���㴦��
		}
		
		if ( RTC->RTCIF & RTC_RTCIF_MIN_IF_ENABLE )//1���ӻ���(�������¶Ȳ���)
		{			
			RTC->RTCIF = RTC_RTCIF_MIN_IF_ENABLE;	//����ӱ仯��־	
			
			//������Чʱ���ж�
			if(RAMREG14) RAMREG14--;
			if(RAMREG14 == 0)	//ͣ��2h�ر���ʾ
			{
				RAMREG15 = 0;	//�������Ѵ���
			}
		}
		
		Clear_Wdt();

		if( GPIO_common->EXTI0IF & BIT5 )//����
		{
			GPIO_common->EXTI0IF	= BIT5;		//�尴���жϱ�־λ
				
			if( RAMREG2 )//���Ǵ�������
			{
				RAMREG10 = 0x55;
				Cover_Space_Timer = def_coverdelaytimer;
			}						
			if(Extbattery == 0x55) Pd_Adc_Calculate(0xaa);  //��ص�ѹ����:���Ƿѹ��֧�ֿ��ǺͰ�������					
		}
		if( GPIO_common->EXTI1IF & BIT6 )//��ʾ����
		{
			GPIO_common->EXTI1IF	= BIT6;		//�尴���жϱ�־λ
				
			if( RAMREG15 || Stop_Disptimer ) 
			{
				Displaykey_Process();//��ʾ��������
				if( Stop_Disptimer==0 ) 
				{
					Display.Timer = Display_Para.Loop_Time;//��1��ѭ����ʾ,��2�ΰ���ͣ��30s
					Display.Status &= B1111_1110;//�尴����ʾ��־
					Stop_Disptimer = default_keydisplaytimer/2;//30s
					
					if(Extbattery == 0x55) Pd_Adc_Calculate(0x55);  //ͣ���Դ(��������+��ص�ѹ)����
				}
//				else
//				{
//					Stop_Disptimer = default_keydisplaytimer/2;//30s
//				}
					
				if(Extbattery == 0x55) Pd_Adc_Calculate(0xaa);  //��ص�ѹ����:���Ƿѹ��֧�ֿ��ǺͰ�������
				if( Stop_Disptimer )
				{
					RCC->SYSRCCSEL &= ~RCC_SYSRCCSEL_AHBPRES_16;
					Lcd_Display();			//ˢ����ʾ
					RCC->SYSRCCSEL |= RCC_SYSRCCSEL_AHBPRES_16;
					Lcd_Disp_On();			//��lcd��ʾ
					display_rtc_flag = 1;
				}
			}
		}
		
		if ( RTC->RTCIF & RTC_RTCIF_SEC_IF_ENABLE )//1s����
		{					
			RTC->RTCIF = RTC_RTCIF_SEC_IF_ENABLE;
			
			if( PowerDetCnt0 >= 3 )
			{
				PowerDetCnt0++;
				
				if(Extbattery == 0x55) Pd_Adc_Calculate(0xaa);  //��ص�ѹ����:���Ƿѹ��֧�ֵ�Դ�쳣���
				
				if( PowerDetCnt0 >= 5 )
				{
					InputtIO( GPIOB, GPIO_Pin_12, 0 );	//PB9;//RelayTest
					OutputIO( GPIOB, GPIO_Pin_11, 0 );	//PB8;//RelayCtrl//EE_V@�������
					RELAYCTRLON;	
					
					__NOP();__NOP();
					PowerError_Check();//��Դ�쳣���(��բ���ж�)
					if( RAMREG11 != 0x55 ) PowerDetCnt0 = 0;
					else
					{
						PowerDetCnt0 = 0;
						RAMREG11 = 0xaa;//ֻ�м�¼����ʱ�����ϵ��������ʱ��
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
					Read_Sysclock();//��ʱ��
				}
			}
			
			if( RAMREG10 == 0x55 )
			{
				if( Cover_Space_Timer )
				{
					Cover_Space_Timer--;
					if( Cover_Space_Timer == 0 ) Read_Sysclock();//��ʱ��
				}
								 
				SCover_Check();//���Ǽ��
				if( Cover_Space_Timer == def_coverdelaytimer )  //δ��⵽���ǻ�������¼��� 
				{
					RAMREG10 = 0;
				}			
				if( RAMREG2 == 0 ) GPIO_common->EXTI0_SEL |= BIT26;//����,DISABLE
			}
			
			if( Stop_Disptimer ) 
			{
				Stop_Disptimer--;
				if( (Extbattery == 0x55)&&((Stop_Disptimer&B0000_0011)== 0) ) Pd_Adc_Calculate(0xaa);  //��ص�ѹ����:���Ƿѹ��֧�ֿ��ǺͰ�������(��ʾ�ڼ�4s����ص�ѹ�Խ�Լ����)
				if( Stop_Disptimer ) 
				{
					if( Display.Timer ) Display.Timer--;
				
					if( Display.Timer==0 ) display_rtc_flag = 1;
					if( display_rtc_flag )
					{
						if(Extbattery == 0x55) Pd_Adc_Calculate(0x55);  //ͣ���Դ(��������+��ص�ѹ)����(����������ݹ��ϵ�һ�ΰ�����ʾЧ������)
						Lcd_Display();			//ˢ����ʾ
						Lcd_Disp_On();			//��lcd��ʾ
					}
				}
				else
				{
					if(RAMREG15) RAMREG15--;	//�������Ѵ�����1
				}	
			}
		}
		
		if( Stop_Disptimer == 0 ) 
		{
			if( (RAMREG15 == 0) || (RAMREG14 == 0) ) 
			{
				GPIO_common->EXTI1_SEL	|= BIT29;	//PD6,��ʾ����,��ʹ��
				GPIO_common->EXTI1IF	= 0x000000FF;	//���־λ
				GPIO_common->PINWKEN = 0;
			}
			
			Lcd_Disp_Off();//����lcd������ʾ
			Display.Number = 0 ;	//��ͷ��ʼ��ʾ
			Disable_I2C_IO();//�ر�����ee��Դ
		}	
		
		if ( RTC->RTCIF & RTC_RTCIF_DATE_IF_ENABLE )//1�컽��
		{
			RTC->RTCIF = RTC_RTCIF_DATE_IF_ENABLE;	//���Сʱ�仯����ı�־
			Clr_Zero_Data();//�������������
		}	
	}
}
