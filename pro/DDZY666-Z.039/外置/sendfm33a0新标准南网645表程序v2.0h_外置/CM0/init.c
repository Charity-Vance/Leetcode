#include "ex_func.h"
#include "ex_var.h"
#include "FM32L0XX.h"  
#include <string.h>


void Init_Pad_Io(void)
{	
	GPIOB->ODR = BIT6|BIT7|BIT11;		//6.PULSELED, 7.VBLE 11.relayctrl=1/EEVCC
	GPIOD->ODR = BIT7;				//7.��ESAMVCC
	GPIOE->ODR = BIT2|BIT4;		//2.LCDLED=1 4.VFLASH
	GPIOF->ODR = BIT5;				//5.PLCRST=1
	GPIOG->ODR = BIT8;				//8.LEDRELAY
}

void IWDT_Init(uint32_t period)
{
	RCC->PERRCCCON1 |= RCC_PERRCCCON1_IWDTCKEN_ON;

	IWDT->IWDTCFG &= ~IWDT_IWDTOVP_Msk;
	IWDT->IWDTCFG |= period;	
}

int isPowerOff(void)
{
	return EA_OFF;
}

void Clear_Wdt()
{
	IWDT->IWDTSERV = WDTSERV_key;
	if( EA_OFF && (WWDT->WWDTCNT > 1024/2) )  {__NOP();__NOP();WWDT->WWDTCON = 0xac;}//��wwdt
}

void WWDT_Init(void)
{
	WWDT->WWDTCFG = 0x07;	//pclk*4096*1024 (512ms @8M)
	WWDT->WWDTCON = 0x5a;	//����wwdt
}


void Clear_W_Wdt()
{
	WWDT->WWDTCON = 0xac;//��wwdt
}

//uint08 Call_Get_PRIMASK( void )
//{
//	uint32 Result;
//	Result = __get_PRIMASK();
//	return (uint08)Result;
//}

void I2c_Wait_5ms( void ) //��ʱ5ms
{
	TicksDelayMs(5*clkmode,NULL);
}


void Delay_Initial(unsigned char Num) //��ʱNum*5ms(���ʱ���С��800ms)
{
	unsigned char i;
	
	Clear_Wdt();
	for( i=0; i<Num; i++ )
	{
		I2c_Wait_5ms();
		if( EA_OFF ) break;
	}
	Clear_Wdt();
}


void Clear_Nv_Ram()//��startup��δ����Ĳ���ram
{
	memset( (uint08 near*)(0x20000000), 0x00, ((uint32)(&Fwdl)-0x20000000) );	//��ֹ��ʣ���
}


void Nvram_Judge()	//���粻���ram�Ϸ����ж�
{
	if( (Password_Err[0]>Defpassworderrcnt) || (Password_Err[1]>Defpassworderrcnt) || (Mac_Err_Times > 200) ) Clear_Nv_Ram();//��startup��δ����Ĳ���ram
}


void Note_Reset_Number()	//��¼�ϵ縴λ��wdt��λ����,������ϵ縴λ��ram
{	
	unsigned char i;
	
	for( i=0; i<20; i++ ) I2c_Wait_5ms();	//��ʱ100ms
		
	if( I2C_Read_Eeprom44( ee_meterstatus1_page, Eeprom.Buffer, ee_meterstatus1_lenth)==0 )//�����״̬�ֵ�ram�ɹ�
	{
		Meter_Status  = Eeprom.Buffer[0];
		Meter_Status1 = Eeprom.Buffer[1];
		Meter_Status2 = Eeprom.Buffer[2];
	}
	
	if( RCC->RSTFLAG & (BIT9|BIT8) )//�ϵ縴λ�µ縴λ
	{	
		I2C_Read_Eeprom44( ee_wdt_page, Eeprom.Buffer,ee_wdt_lenth );//�ϵ縴λ������1
		if( RCC->RSTFLAG & BIT9 )
		{
			if( Eeprom.Buffer[7] < 255 ) Eeprom.Buffer[7]++;
		}
		if( RCC->RSTFLAG & BIT8 )
		{
			if( Eeprom.Buffer[6] < 255 ) Eeprom.Buffer[6]++;
		}
		I2C_Write_Eeprom44( ee_wdt_page, Eeprom.Buffer, ee_wdt_lenth );

		Clear_Nv_Ram();//��startup��δ����Ĳ���ram
		memset( (uint08 near*)(0x20000000), 0x00, ((uint32)(&RAMBUF[32])-0x20000000) );	//��startup�����е����ݰ�������
		
		if( I2C_Read_Eeprom( ee_reportdata_page, 0, Eeprom.Buffer, ee_reportdata_lenth)==0 )//���¼��ϱ�����
		{
			if( Eeprom.Buffer[0] != 0xff )//��ֹ���ַǷ�����
			{
				System_Status = (Eeprom.Buffer[0]&0x3f);//�ָ���־
				if( Eeprom.Buffer[0]&0x80 ) Cover.Status = 1;//�ָ�����״̬
				memcpy( Report_Data, Eeprom.Buffer+1, ee_reportdata_lenth-1 );
			}
		}		
		below_60u_flag = 1;	//�κθ�λ��֧�ָ��µ�ǰ��¼���ϵ����ʱ��(�����µ縴λ)
	}
	if ( RCC->RSTFLAG & (BIT4|BIT2) )//iwdt, wwdt
	{	
		I2C_Read_Eeprom44( ee_wdt_page, Eeprom.Buffer, ee_wdt_lenth );
		if( RCC->RSTFLAG & BIT4 )
		{
			if( Eeprom.Buffer[3] < 255 ) Eeprom.Buffer[3]++;
		}
		if( (RCC->RSTFLAG & BIT2) && (RAMREG3 != 0xaa) )//���߻��ѵ�wwdt��λ,��λ��������1
		{
			if( Eeprom.Buffer[2] < 255 ) Eeprom.Buffer[2]++;
		}
		I2C_Write_Eeprom44( ee_wdt_page, Eeprom.Buffer, ee_wdt_lenth );	
//		Clear_Nv_Ram();//��startup��δ����Ĳ���ram

		if( RAMREG3 == 0x55 )//hardfault����Ŀ��Ź���λ
		{
			I2C_Read_Eeprom( ee_hardfault_page, ee_hardfault_inpage, Eeprom.Buffer, ee_hardfault_lenth );//HardFault_Flag����wwdt��λ������1
			Read_Rtc( Eeprom.Buffer );//����ǰʱ��(�����м�)
			if( Eeprom.Buffer[7] < 255 )  Eeprom.Buffer[7]++;//�ۼƴ�����1
			I2C_Write_Eeprom( ee_hardfault_page, ee_hardfault_inpage, Eeprom.Buffer, ee_hardfault_lenth );
		}
	}	
	
	if ( RCC->RSTFLAG & 0x00010C63 )//������λ��־����
	{	
		I2C_Read_Eeprom44( ee_wdt_page, Eeprom.Buffer, ee_wdt_lenth );
		if( RCC->RSTFLAG & BIT16 )	//ģʽ��ϸ�λ
		{
			if( Eeprom.Buffer[10] < 255 ) Eeprom.Buffer[10]++; 
		}	
		if( RCC->RSTFLAG & BIT11 )	//NRST��λ	
		{
			if( Eeprom.Buffer[9] < 255 ) Eeprom.Buffer[9]++; 
		}	
		if( RCC->RSTFLAG & BIT10 )	//TESTN��λ	
		{
			if( Eeprom.Buffer[8] < 255 ) Eeprom.Buffer[8]++; 
		}	
		if( RCC->RSTFLAG & BIT6 )	//EMC��λ	
		{
			if( Eeprom.Buffer[5] < 255 ) Eeprom.Buffer[5]++; 
		}
		if( RCC->RSTFLAG & BIT5 )	//�����λ	
		{
			if( Eeprom.Buffer[4] < 255 ) Eeprom.Buffer[4]++; 
		}
		if( RCC->RSTFLAG & BIT1 )	//CPU������λ	
		{
			if( Eeprom.Buffer[1] < 255 ) Eeprom.Buffer[1]++; 
		}	
		if( RCC->RSTFLAG & BIT0 )	//NVIC��λ	
		{
			if( Eeprom.Buffer[0] < 255 ) Eeprom.Buffer[0]++; 
		}			
		I2C_Write_Eeprom44( ee_wdt_page, Eeprom.Buffer, ee_wdt_lenth );
	}
		
	if ( RAMREG3 == 0xaa )//�ϵ绽�ѻ���ͨ������������ʼ��
	{		
		Nvram_Judge();//���粻���ram�Ϸ����ж�
		System_Status = System_St_Bk; //�ָ���־
		ANAC->SVDSIF = 0x00000003;
		below_60u_flag = 1;	//�κθ�λ��֧�ָ��µ�ǰ��¼���ϵ����ʱ��
	}	
	else if( (RCC->RSTFLAG&0x00010F77) == 0 )//�쳣
	{
		I2C_Read_Eeprom44( ee_wdt_page, Eeprom.Buffer, ee_wdt_lenth );//�쳣��λ������1
		if( Eeprom.Buffer[11] < 255 ) Eeprom.Buffer[11]++; 
		I2C_Write_Eeprom44( ee_wdt_page, Eeprom.Buffer, ee_wdt_lenth );
		Clear_Nv_Ram();//��startup��δ����Ĳ���ram
	}
	
	RCC->RSTFLAG = 0x00010F77;//�帴λ��־
	
	RAMREG3 = 0;//����������־�ֽ�
	RAMREG13 = 0;//��ͣ���ϱ�����ʱ��
	Nvram_Judge();//���粻���ram�Ϸ����ж�
	
	#if(1 == CHINT_Mode)
	if( I2C_Read_Eeprom(ee_softij_page, ee_softij_inpage, Ijtimer_Para.Ijtimer.B08, 4) != 0)	//�ϵ��ȡ���I_J��ʱֵ
	{
		I2C_Read_Eeprom(ee_softij_page, ee_softij_inpage, Ijtimer_Para.Ijtimer.B08, 4);
	}
	if(Byte2uInt(Ijtimer_Para.Ijtimer.B08) > 0xa8c0)
	{
		memset( Ijtimer_Para.Ijtimer.B08, 0x00, 4 );
	}
	#endif
}


void Init_RCHF_Trim( void )
{
	uint32 Temp32;
	
	if( clkmode == 0x02 )//16M
	{
		Temp32 = const_rchf_Trim16;
	}
	else	//8M
	{
		Temp32 = const_rchf_Trim8;
	}
	
	if( ((Temp32>>16)&0x0000FFFF) == ((~Temp32)&0x0000FFFF) )	//������У���ж�
	{
		RCC->RCHFTRIM = Temp32&0x0000007F;
	}	
	else
	{
		RCC->RCHFTRIM = 0x00000040;
	}
}


//xtlf��32768Hzʱ����Ϊ�ο�Դ
//��������������APB����Ƶ�����
void Clk_Adj_Proc( void )
{
	uint16 Temp16;
	unsigned char n,m,i,tempbyte,TrimBuf;	
	float DIVclkmode = 1.0;
	
	if( ((ANAC->FDETIF)&BIT6) == 0)//xtlfͣ��
	{
		//ʹ�ò��Բ���		
		Init_RCHF_Trim();
		return;
	}
			
	ETIMER1->ETxCR    = 0x00000044;		//ET1~~ , ��׽ģʽ,���ڲ�׽,�������㣬������׽�������ز�׽
										//����ԴFcpu����׽Դxtlf
	ETIMER1->ETxINSEL = 0x00000008;		//����ԴGroup1�ź�=apbclk(Fcpu),��׽ԴGroup2�ź�=xtlf
	
	ETIMER1->ETxPESCALE2 = 127;//��׽Դ128��Ƶ

	ETIMER1->ETxIE  = 0x00000000;		//��ֹET1�ж�
	ETIMER1->ETxIF |= 0x00000007;		//bit0������ж� bit1����׽�жϣ�
	
	i = clkmode - 1;	
//	for(i=0;i<4;i++)
	{		
		switch(i)
		{
			case 0://8
				ETIMER1->ETxPESCALE1 = 0;//����Դ1��Ƶ
				DIVclkmode		= 1.0;
				break;
			
			case 1://16/2
				ETIMER1->ETxPESCALE1 = 1;//����Դ2��Ƶ
				DIVclkmode		= 1.0;
				break;
			
//			case 2://24/4
//				ETIMER1->ETxPESCALE1 = 3;//����Դ4��Ƶ
//				DIVclkmode		= 8.0/6.0;
//				break;
//			
//			case 3://32/4
//				ETIMER1->ETxPESCALE1 = 3;//����Դ4��Ƶ
//				DIVclkmode		= 1.0;
//				break;	
			
			default:
				ETIMER1->ETxPESCALE1 = 0;//����Դ����Ƶ
				DIVclkmode		= 1.0;
				break;		
		}
		
		for( m=0; m<6; m++ )
		{
			Clear_Wdt();
			
			ETIMER1->ETxCR |= 0x00000080;	//����ET
			
			for( n=0; n<2; n++ ) //�������ж���Ҫ3.906ms = 128/32768 s
			{		
				Temp16 = 0;
				Do_DelayStart();
				{
					if( ETIMER1->ETxIF & 0x00000002 ) {Temp16 = 1; break;}
				}While_DelayMsEnd(7.5*clkmode);		//7.5ms
				ETIMER1->ETxIF |= 0x00000002;
			}	
			ETIMER1->ETxCR &= (~0x00000080); 	//�رն�ʱ��
			if( Temp16 == 0 ) continue;
				
			Temp16 = ETIMER1->ETxIVR;
				
			if( (Temp16>(31250-120)/DIVclkmode)&&(Temp16<(31250+120)/DIVclkmode) ) //return;//����������ֱֵ�ӷ���
			{
				break;
			}
			else
			{
				TrimBuf = RCC->RCHFTRIM;
				if( Temp16 > 31250/DIVclkmode )	//31250 = 8M*128/32768; 156.25 = (15625*2/4*2M)*40k
				{
					Temp16 -= 31250/DIVclkmode;
					tempbyte = (float)Temp16/(156.25/DIVclkmode)+0.5;
					
					if( tempbyte > 0x20 ) tempbyte = 0x20;
					
					if( RCC->RCHFTRIM >= tempbyte )
					{
						RCC->RCHFTRIM -= tempbyte;
					}
					else
					{
						RCC->RCHFTRIM = 0x00;
					}			
				}
				else
				{
					Temp16 = 31250/DIVclkmode-Temp16;
					tempbyte = (float)Temp16/(156.25/DIVclkmode)+0.5;
					
					if( tempbyte > 0x20 ) tempbyte = 0x20;
					
					if( (RCC->RCHFTRIM+tempbyte)<=0x7F)
					{
						RCC->RCHFTRIM += tempbyte;
					}
					else
					{
						RCC->RCHFTRIM = 0x7F;
					}			
				}
				
				if( m == 5 )				//δ�ҵ�����ֵ,�������2�ε�ֵȡƽ��
				{
					TrimBuf += RCC->RCHFTRIM;
					RCC->RCHFTRIM = TrimBuf/2.0+0.5;				
				}
			}
		}
	}
}

void Init_Arm0()
{
//	IE   = B0001_0010;	//ʹ��TIME0�ж�,ʹ�ܴ���(������ռ��)�ж�
//	IPH  = B0000_0000;	//�����ȼ�
//	IPL  = B0000_0000;	//�����ȼ�
//	
//	AIE  = B0000_0111;	//ʹ�ܸ����ж�0/1/2����оƬ��������ռ�ã�
//	AIPH = B0000_0000;	//�����ȼ�
//	AIPL = B0000_0000;	//�����ȼ�
//	
//	TMOD = B0000_0001;	//16bit��ʱ,��ʱʱ��2731*1.5us=4096us
////	TL0  = 0x55;		//65536-2731=0XF555,@8M
////	TH0  = 0xF5;
//	TR0  = 1;		//����time0
}

unsigned char AddNClock( unsigned char Start, unsigned char *Clock, unsigned int Num )
//Clock: ssmmhhDDMMYY
{
	unsigned int i, n, MaxDay;
	unsigned int Year;
	unsigned char code Days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	unsigned char HexClock[8];

	if( Num == 0 ) 	return 0;
	if( Start > 5 ) return 1;
//	if( JudgeClockNoWeek(0, Clock, 6) )	return 1;	//��Ч����ʼʱ��
	
	for( i=0; i<6; i++ )
	{
		HexClock[i] = Bcd_To_Hex( Clock[i] );
	}
	
	switch( Start )
	{
		case 0x00:	//ss(0~59)
			i = (HexClock[0]+Num)/60;
			HexClock[0] = (HexClock[0]+Num)%60;
			Num = i;
			
		case 0x01:	//mm(0~59)
			if( Num )
			{
				i = (HexClock[1]+Num)/60;
				HexClock[1] = (HexClock[1]+Num)%60;
				Num = i;
			}
			
		case 0x02:	//hh(0~23)
			if( Num )
			{
				i = (HexClock[2]+Num)/24;
				HexClock[2] = (HexClock[2]+Num)%24;
				Num = i;
			}
			
		case 0x03:	//DD(0~28,29,30,31)
			if( Num )
			{
				for( n=0; n<12*99; n++ )	//ÿ�ε��ô˺������������ӵ�������255
				{
					//����ʣ��������δ���������Ƚ�
					MaxDay = Days[ (HexClock[4]-1) ];
					if( HexClock[4] == 2 )
					{
						Year = HexClock[5] + 2000;
						if( (Year%4==0&&Year%100!=0) || (Year%400==0) ) MaxDay++;	//����
					}
					
					if( (MaxDay-HexClock[3]) >= Num )	//����ʣ������ ���� δ��������, �����л���
					{
						HexClock[3] += Num;
						Num = 0x00;
						break;
					}
					
					if( Num )
					{
						Num -= (MaxDay-HexClock[3]+1);	//�ټ�1��Ϊ���������л���,������Ϊ1��

						HexClock[3] = 0x01;	//������Ϊ1��
						HexClock[4]++;	//�·�����
						if( HexClock[4] > 12 ) 
						{
							HexClock[4] = 0x01;	//����12�������л�����һ���һ�·�
							HexClock[5]++;	//���л�����һ��
						}
					}
				}
			}
			
		case 0x04:	//MM(1~12)
			if( Num )
			{
				i = (HexClock[4]+Num-1)/12;
				HexClock[4] = (HexClock[4]+Num-1)%12;
				HexClock[4]++;
				Num = i;
			}
			
		case 0x05:	//YY(0~99)
			if( Num )
			{
				i = (HexClock[5]+Num)/100;
				HexClock[5] = (HexClock[5]+Num)%100;
				Num = i;
			}

		default:
			break;					
	}

	for( i=0; i<6; i++ )
	{
		Clock[i] = Hex_To_Bcd( HexClock[i] );
	}
	
	return 0;
}


void Powerd_Data_Process()	//ʱ�Ӵ����õ���ʱ��ָ���β���ָ�
{
	unsigned char  i, Buf[ee_powerdown_lenth+2];
	unsigned char  BufA[ee_powerdownnote_lenth];
	
	if( I2C_Read_Eeprom( ee_monthvolrun_page, ee_monthvolrun_inpage, Eeprom.Buffer, ee_monthvolrun_lenth )== 0 )//���պ��µ�ѹ�ϸ�������״̬
	{
		memcpy( VolStatus[0].Total.B08, Eeprom.Buffer, ee_monthvolrun_lenth );
	}
	
	Pd_Hourfreeze_Judge();	//�ϵ����㶳��Ͷ�ʱ���Ჹ���жϴ���(��Ҫͣ��ʱ��)
	
	if( I2C_Read_Eeprom( ee_power_down_page, 0x00, Buf, ee_powerdown_lenth ) == 0 )
	{
		Decimal.Add = Buf[7];//�ָ��й���������
		Decimal.Add_Rp = Buf[8];//�ָ��޹���������
		ReportList[0] = Buf[22]&B0011_0000; //�ָ������ϱ�����
		
		if( clock_error == 0 )
		{
			if( Cmp_Bcd_Inv(Sclock.Clockbackup, Buf, 6)==2 ) clock_error = 1;//�ϵ�ʱ��С�ڵ���ʱ��
			else
			{
				Buf[7] = Buf[5];//���������
				Buf[5] = Hex_To_Bcd(Bcd_To_Hex(Buf[5])+3);	//����ʱ���n��(n=3)
				if( Cmp_Bcd_Inv(Sclock.Clockbackup, Buf, 6)==1 ) clock_error = 1;//�ϵ�ʱ����ڵ���ʱ���n��	
				Buf[5] = Buf[7];//������ָ�
			}
			
			if( clock_error )
			{
//				Syn_Clock();//ͬ�����ͱ���ʱ��	
				memcpy( Sclock.Clockbackup, Buf, 6 );		//ʱ�ӹ��Ϸ���ʱ���ǵ���ʱ��(ͬ���Ͻ���ʱ��)
				if( ChkLastclockerrRcdTime() != 1 ) Note_Run_Event(ee_clockerrn_inpage); //ʱ�ӹ��Ͽ�ʼ��¼(ʱ�ӷǷ�)
			}
		}
		
		if( clock_error )
		{
			memcpy( BufA, Buf, 3 );//���ʱ
			memcpy( BufA+4, Buf+3, 3 );//������
			BufA[3] = (CalcAbsDay(BufA+2)+6)%7;	//������,��ʽΪ��+��+ʱ+��+��+��+��,��ʼ��ַ��,���տ�ʼ����
			Set_Rtc( 0, BufA, 7 );//�����м�
			Read_Sysclock();	//��ʱ��
		}
		
		//�¼����洦��
//		if( Buf[9] != 0xff )//��ֹ���ַǷ�����
		{
//			ReportList[0] = Buf[22]&B0011_0000; //�ָ������ϱ�����
			
			if( RAMREG11 == 0xaa )//���ǵ�Դ�쳣��¼
			{
				memcpy( Sclock.Clockbackup, Buf, 6 );//��Դ�쳣����ʱ��			
				AddNClock( 0, Sclock.Clockbackup, 1 );
				Note_Run_Event(ee_powererrn_inpage);		//��Դ�쳣��ʼ��¼
				
				Syn_Clock();	//ͬ��ʱ��
				Note_Run_Event(ee_powererrn_inpage|0x80);	//��Դ�쳣������¼
			}
			RAMREG11 = 0;
			
			if( RAMREG12 )//���ǿ����¼���¼
			{
				memcpy( Sclock.Clockbackup, RAMBUF, 6 );//���Ƿ���ʱ��
				if( (RAMREG12 == 0xaa) || (RAMREG12 == 0xbb)  )	//��¼���Ƿ���
				{	
					Note_Run_Event(ee_covern_inpage);	//��¼�����¼���¼
				}
				
				memcpy( Sclock.Clockbackup, RAMBUF+6, 6 );//���ǽ���ʱ��	
				if( (RAMREG12 == 0x55) || (RAMREG12 == 0xbb) )//��¼���ǽ���
				{
					Note_Run_Event(ee_covern_inpage|0x80);	//��¼�ϸ��¼���¼
				}
				
				Syn_Clock();	//ͬ��ʱ��
			}
			RAMREG12 = 0;
			
			memcpy( Sclock.Clockbackup, Buf, 7 );//ʹ�õ���ʱ������¼���¼
			if( Buf[9]&0x80 )
			{
				if( ChkPdRcdTime() == 1 )//��һ�ε����н���ʱ��ſ��µĵ����¼
				{
					Note_Run_Event( ee_powerdownn_inpage ); //�����¼���ʼ��¼
				}     
			}
			if( Buf[9]&0x40 ) relay_error = 1;	//���ɿ����쳣������¼
			if( Buf[9]&0x20 ) Note_Run_Event(ee_maxi_inpage|0x80);	//��¼���������¼�(����)
			if( Buf[9]&0x10 ) Note_Run_Event(ee_calerrn_inpage|0x80); //����оƬ���Ͻ�����¼
			if( Buf[9]&0x08 ) Note_Run_Event(ee_nlineerrn_inpage|0x80); //���ߵ����쳣������¼
			if( Buf[9]&0x04 ) //��¼ʧѹ�¼�(����)
			{
				memcpy( &Lost_Aver_I, Buf+10, 4 );
				memcpy( &Lost_V_Timer, Buf+14, 4 );
				Note_Run_Event(ee_lostvn_inpage|0x80); //��¼ʧѹ�¼�(����)
			}
			if( Buf[9]&0x02 )
			{
				memcpy( &Current_Over_Count41, Buf+18, 2 );//�ָ��͵�ѹ�¼���ʱ�ۼ�ʱ��
			}
			if( Buf[9]&0x01 )
			{
				memcpy( &Current_Over_Count51, Buf+20, 2 );//�ָ��ߵ�ѹ�¼���ʱ�ۼ�ʱ��
			}
			
			MvFlash.Obj = Buf[23]&0x3F;
			MvFlash.Dir = 0x00;
			if( Buf[23]&0x40 ) MvFlash.Dir = 0x55;
			if( Buf[23]&0x80 ) MvFlash.Dir = 0xAA;
			MvFlash.Offset = Byte2uShort(Buf+24);

			SynFlash.Crc16++; //����ʱ����˲�����RAM
			I2C_Read_Eeprom( ee_synflash_page, ee_synflash_inpage, (uint08*)SynFlash.HisRec, ee_synflash_len );
			
			Syn_Clock();	//ͬ��ʱ��
		}
		
		Pd_Calculate_Judge();	//ͣ��ͳ�ƴ���
		
		Wr_Powerdown_Data(0);//д����������ݵ�����ee(��ҪĿ��������β������ر�־)
		
		//�¸ı䴦�����ı䴦��
		if( Buf[5] != Sclock.Clockbackup[5] ) //��ı�
		{
			year_change_flag2 = 1;
		}
		if( Buf[4] != Sclock.Clockbackup[4] || year_change_flag2 ) //�¸ı�
		{
			//����ʱ������һ����
			{Sclock.Clockbackup[0]=0;Sclock.Clockbackup[1]=0;Sclock.Clockbackup[2]=0;Sclock.Clockbackup[3]=0x01;}
			if( Buf[4]<0x12 )
			{
				Sclock.Clockbackup[4]=Hex_To_Bcd(Bcd_To_Hex(Buf[4])+1);//��
				Sclock.Clockbackup[5]=Buf[5];//��
			}
			else
			{
				Sclock.Clockbackup[4]=0x01;//��
				Sclock.Clockbackup[5]=Hex_To_Bcd(Bcd_To_Hex(Buf[5])+1);//��
			}
			Freeze_Dl( ee_monthfreeze_page, ee_monthn_inpage );//�¶��ᣨ��һ�Σ�
			Syn_Clock();	//ͬ��ʱ��
		}
		Freeze_Pddata();	//�����������		
	}
		
	run_loadchk_flag = 0;	//��ֹ�ϵ��󴥷����ɼ�¼
	if( Crc_Check( Load.Point, ee_loadpoint_lenth+2 ) )	//ram���ɼ�¼ָ�����
	{
		memcpy( Load.Point, Buf+26, ee_loadpoint_lenth+2 );//�����ɼ�¼ָ�뵽ram
	}
	
	//�ϵ�ˢ�¸��ɼ�¼��RAM�����������ʱ����
	for( i=0; i<max_casecount; i++ )
	{
		if( Load.Point[5*i+3] )	break;
	}
	
	if( i < max_casecount )
		I2C_Read_Eeprom( ee_ploadrec_page, 0, LoadBuf, ee_ploadrec_lenth );
}


void Init_Relay( void )
{	
	if( Relay_Mode != 0x55 )//���ü̵���
	{
		{RELAYOFF1; __NOP(); RELAYOFF2;}//�ű��̵ּ�����Ч
	}
	else
	{
		if(Mode.Feature1&0x01)//���巽ʽ
		{
			RELAYOFF3;
		}
		else
		{
			if(relay_status_flag==0)RELAYOFF3;//�̵����պ�
			else RELAYON3;//�̵����Ͽ�
		}
	}
}


void Init_System( void )
{	
	unsigned char i;
	uint32 Temp32;
		
	{__disable_irq();Powerd_Flag = 0x12345678;}
	IWDT_Init(runwdtcon);
	Clear_Wdt();
	Init_Arm0();
	Temp32 = I2C->I2CBUF;
	I2C->I2CERR = 0x00000007;	//��I2C�����־

	if( (RCC->RSTFLAG == 0x00000004) && (Wwdt_Lcd_Ctrl == 0x55) && (HardFault_Flag==0x11223344) )//����wwdt��λ
	{		
		HardFault_Flag = 0;
		RCC->RSTFLAG = 0x00000004;//�帴λ��־
		Enable_I2C_IO();
		Close_None_GPIO();
		Veri_Sys_Reg();
		
		RAMREG3 = 0;//����������־�ֽ�
		Nvram_Judge();//���粻���ram�Ϸ����ж�
				
		I2C_Read_Eeprom( ee_hardfault_page, ee_hardfault_inpage, Eeprom.Buffer, ee_hardfault_lenth );//HardFault_Flag����wwdt��λ������1
		Read_Rtc( Eeprom.Buffer );//����ǰʱ��(�����м�)
		if( Eeprom.Buffer[7] < 255 )  Eeprom.Buffer[7]++;//�ۼƴ�����1
		I2C_Write_Eeprom( ee_hardfault_page, ee_hardfault_inpage, Eeprom.Buffer, ee_hardfault_lenth );
		Uart[CHHW].Overtime_Timer = txtimeout_max;
		Uart[CHBLE].Overtime_Timer = txtimeout_max;
		Uart[CH485].Overtime_Timer = txtimeout_max;
		Uart[CHZB].Overtime_Timer = txtimeout_max;
		
		{Powerd_Flag = 0;__enable_irq();WWDT_Init();}//���жϲ�������wwdt
		return;
	}
		
	Veri_Clk_Gen();
	Enable_I2C_IO();
	I2c_Wait_5ms();		//PR1SEN��λǰ����ʹ��PLL,���ȴ��㹻ʱ�䣨>2ms��ȷ��PLL����
	
	Init_Pad_Io();
	CloseFlash();
	Disable_Pulse();	//�رռ���
	Veri_Pad();
	Close_None_GPIO();		
	Veri_Sys_Reg();
	MeterIC_RST0();		//��λ����оƬ
	CloseEsam();		//ESAM����IOΪ�͵�ƽ

	if( !(SVDCHKPLOW) )//δ����Ƿѹ
	{
		RELAYLEDON;		//��բ�ƺͱ�������һ��
		LCDLEDON;
	}
        
	Display_Para_Verify();	//��ʾ����У��
	Displayitem_Verify();	//��ʾ��ĿУ��
	Display.Number=0xff;
	Display.Timer = Display_Para.A_Time;//�ϵ�ȫ��
	Init_Led_Timer = Display_Para.A_Time;//��բ��	
	Lcdled = Display_Para.A_Time;//��������
	Lcd_Display();		//�ϵ�ȫ��
	DISP->LCDBIAS   = Fulllcdbias;	//����ȫ���Ҷ�
	Lcd_LCDEN_On();		//��lcd������ʾ
	
	Note_Reset_Number();	//��¼�ϵ縴λ��wdt��λ����
	Resetworking_Timer = resetworking_timer_delay;//������λ����
	PLC_RST0;		//��λ�ز�(�����)
	Mod_Comm_Timer1 = 0;
	Mod_Comm_Timer2 = Mod_Comm_Timer_delay2; //����5minͨ��ģ���쳣��ʱ��ʱ��

	Mode_Verify();		//����ģʽ��У��
	Init_Relay();		//�ϵ�̵�������	
	Veri_Uart_All();	//ͨѶ������У��
	Commaddr_Verify();	//ͨѶ��ַУ��
	
	Read_Sysclock();	//��ʱ��
	Fwdl_Verify();		//�������У��
	Bkdl_Verify();		//�������У��
	for(i=0; i<4; i++)
	Rpdl_Verify(i);		//�޹�����У��
	Mt_Alarmstatus_Judge();	//�����״̬�ж�
	Temperpara_Verify();	//�¶�ϵ��У��	
	
	Clear_Wdt();
	Timezone_Judge();	//ʱ��ʱ�η����ж�
	GetKeyStatus();		//����ǰ��Կ״̬
	
	if( !(SVDCHKPLOW) )//δ����Ƿѹ
	{
		Enable_Led_IO();
		RELAYLEDON;		//��բ�ƺͱ�������һ��
		LCDLEDON;
	}
	Adcctrl.Timer=3;	//��֤�ܿ�������ص�ѹ���¶�adc
	RTC_RT.TempFlag = 0xff;//���²������
	Temperature_Hex = 0x7f;	//�¶ȱ仯5�������Զ�ʱ�ӵ�У(��ʱ2s�����)
	Init_RCHF_Trim();	//У׼ֵ����(16M�����ֶ�)
	below_60u_flag = 1;
	Voltage_Low_Count = Deflowvoltagecount_s;
	PowerDetCnt2 = Def_Powerdetcnt2;//�ϵ�3s�ڵ��磬������Դ�쳣���

	RTC->RTCIF = RTC_RTCIF_SEC_IF_ENABLE;	//��������жϱ�־
	NVIC_ClearPendingIRQ(RTC_IRQn);
	NVIC_DisableIRQ(BT1_IRQn);
	NVIC_DisableIRQ(BT2_IRQn);
	{Powerd_Flag = 0;__enable_irq();WWDT_Init();}//���жϲ�������wwdt
	Delay_Initial(100);	//��ʱ500ms
	if( EA_OFF ) Sleep(0);	//����sleep

	MeterIC_RST1();		//����оƬʹ��(��֤�㹻��ʱ��Ŵ������оƬ)
	Powerd_Data_Process();	//�������ݴ���
//	Init_Dayfreeze_Judge();	//�ϵ�7���ն��Ჹ��
	Pd_Histroyfreeze_Judge();//�ϵ�����ղ����жϴ���
	Timezone_Judge();	//ʱ��ʱ�η����ж�
	Year_Ladder_Judge(1);	//����������жϺ����ݺϷ����ж�
	Price_Judge();		//���ʽ��ݵ���ж�
	Calc_Pwr_Proc();	//����������ۼƴ���ͽ���
	Init_Meter_Chip();	//��ʼ������оƬ
	Enable_Pulse(); //�򿪼���
	NVIC_ClearPendingIRQ(BT1_IRQn);
	NVIC_EnableIRQ(BT1_IRQn);	
	NVIC_ClearPendingIRQ(BT2_IRQn);
	NVIC_EnableIRQ(BT2_IRQn);
	if( esam_error ) EsamReset();	
	
	BLEPOWERON;		//��������Դ
	Ble_RstTimer = 5;	//��ʱ5���Ӳ�ѯ��������
	
	Clear_Wdt();
	SynEe.Enable = 1; 	//����һ��ͬ��EE
	SynEeprom(); 		//ͬ�����ᵽFlash
	
	Esam_Timer = 4;		//�ϵ�4���λESAM(�ȴ���Դ�����ȶ�)
	Relay_Space_Timer = 2;	//����2���ϵ���ʱ���Ƽ̵�����ʱ��
	PowerDetCnt0 = 2;	//����Դ��2��ʼ����
	comm_relaystatus_flag = real_relaystatus_flag;//ˢ�¼̵���ʵ��״̬(ͨѶbit4ר��)
	Commmodule_Space_Timer = 0x03;//����ģ�����ȥ����ʱ
	Veri_Sys_Reg();		//��֤���ÿ��߻ָ�����
}


#if( NEWCLOCKADJ == 0 ) //�ɱ�׼ʱ�ӵ�У
float GetADCResult(void) 
{
	unsigned short i,j,temp;
	for(i=0;i<3;i++) //BubbleADC
	{
		for(j=i+1;j<4;j++) 
		if(ADCResultArr.Buffer[i]>ADCResultArr.Buffer[j]) 
		{
			temp=ADCResultArr.Buffer[i];
			ADCResultArr.Buffer[i]=ADCResultArr.Buffer[j];
			ADCResultArr.Buffer[j]=temp;
		} 
	}

	temp = 0;
	for(i=1;i<3;i++)
	{
		temp +=	ADCResultArr.Buffer[i];
	}

	return (temp/2.0);
}

float GetRtcRTrimVal( float AverADCf )//����adc���ݲ���ֵ
{
	float Rtcadj = 0;
	float Fk;
	uint08 i;

	for(i=1; i<=20; i++)//�¶������ж�
	{
		if(AverADCf < RTC_RT.TAdc.PTAT_Value[i])
		{
			break;
		}
	}

	//����ֵ����
	Fk = (float)(((float)RTC_RT.TVal.Trim_Value[i-1] - (float)RTC_RT.TVal.Trim_Value[i])/((float)RTC_RT.TAdc.PTAT_Value[i-1] - (float)RTC_RT.TAdc.PTAT_Value[i]));

	Rtcadj = Fk*((AverADCf - (float)RTC_RT.TAdc.PTAT_Value[i-1])) + (float)RTC_RT.TVal.Trim_Value[i-1];

	return Rtcadj;
}

#else
extern const uint16 ecode const_adc_Min;
float GetADCResult( unsigned char Type ) 
{
	unsigned short i,j,adcpcs;
	float TempADC,temp,adctemp;
	
	for(i=0;i<31;i++) //BubbleADC
	{
		for(j=i+1;j<32;j++) 
		if(ADCResultArr.Buffer[i]>ADCResultArr.Buffer[j]) 
		{
			temp=ADCResultArr.Buffer[i];
			ADCResultArr.Buffer[i]=ADCResultArr.Buffer[j];
			ADCResultArr.Buffer[j]=temp;
		} 
	}

	temp = 0;
	for(i=1;i<31;i++) //ȥ�����ֵ����Сֵ
	{
		temp +=	ADCResultArr.Buffer[i];
	}

  	if ( Type == 0 ) //PTAT �ɼ� 
	{
		temp = temp/30.0;//��ȡƽ��ֵ
		adctemp=0;	
		adcpcs=0;
		for(i=1;i<31;i++) //���ҳ�Buffer[i]�и���ADCƽ��ֵ����
		{
			if( (ADCResultArr.Buffer[i]-temp)>6 || (temp-ADCResultArr.Buffer[i])>6 )
			{
				adctemp+=ADCResultArr.Buffer[i]; //������ƽ��ADCֵ��Buffer[i]�ۼ�
				adcpcs=adcpcs+1;//��¼����ƽ��ADCֵ��Buffer[i]�ĸ���
			}
		}	
			
		if(adcpcs>1) //���Buffer[i]�ĸ�������2��ֵ���򷵻ص�ADCֵΪ0,���ռ�ʱ������
		{
			return 0; //�����쳣���ݷ���0
		}
		else
		{
			TempADC=(temp*30.0-adctemp)/(30.0-adcpcs*1.0);
			return (TempADC);
		}				
	}
	else
	{
		return (temp/30.0); //���ص�ѹͨ��
	}
}
#endif

void Adc_Proc()		//��غ��¶�adc����
{
	unsigned char i;
	signed char j;
 	float T25ADC,AverADCf;
 	float Fa,Fb,T,T25,Rtcadj,TopF_Rtc_Adj;
 	unsigned short Temp16;
 	unsigned char Result;
	signed char BufC[ee_temperature_lenth+2];
	
#if( NEWCLOCKADJ == 0 ) //�ɱ�׼ʱ�ӵ�У	
	if ( Adcctrl.Status == B0010_0000 )//�¶�adc���ݴ���,�����¶Ȳ���
	{		
		Adcctrl.Status = 0;
		ADCResultArr.ReadCount = 0;
		AverADCf = GetADCResult();
		Temperature_Adc = (unsigned short)(AverADCf + 0.5);	//���浱ǰ�¶�adc����ͨѶ����
		
		//0 �����¶�б��΢�����ݲ�֧�֣�
		//1 �����¶�б��΢�����ݲ�֧�֣�
		//2 ���¾�������΢���������޵����κ���ϵ����x*0.0001 kh
		//3 ���¾�������΢���������޵����κ���ϵ����x*0.0001 kl
		//4 ���¶����Уֵ����ֵ(��1.27ppm)	
		//5 �����¶�ADC΢��
		//6 ���¶����УֵL��ͨ�ŵ�ʱ������327.68ppm
		//7 ���¶����УֵH��ͨ�ŵ�ʱ����
		//8 RTC��������ģʽ��0x55:����ģʽ��0xAA���²���ֵģʽ����������ͨģʽ
		//9 ����25+��������΢��������25+�޵����κ���ϵ����x*0.0002 krh
		//10����25-��������΢��������25-�޵����κ���ϵ����x*0.0002 krl
		memcpy( BufC, Tpara.Offset, ee_temperature_lenth );//�����¶�ϵ��				
		for( i=0; i<6; i++ ) //��������ת�����з�����
		{
			Result = (unsigned char)(BufC[i]);
			if( Result&0x80 ) BufC[i] = ((~Result)|0x80)+1;
		}
		Result = (unsigned char)(BufC[9]);
		if( Result&0x80 ) BufC[9] = ((~Result)|0x80)+1;
		Result = (unsigned char)(BufC[10]);
		if( Result&0x80 ) BufC[10] = ((~Result)|0x80)+1;
		
		if( const_temp_TestA == 0x1E )
		{
			//ʹ���¶ȶ�������
//			T25ADC = (const_adc_Test+(short)BufC[5]) - (const_temp_TestA+(float)(const_temp_TestB/0x80)*0.5-const_xtl_top)*const_TmpsH;//����ߵ�������ת�۵��ADCֵ
			if( EA_OFF )
			{
//				T = T + const_T_OffsetSlp;
				T25ADC = (const_adc_Test+(short)BufC[5]) - (const_temp_TestA+(float)(const_temp_TestB/0x80)*0.5-const_xtl_top)*const_TmpsH - const_T_OffsetSlp*const_TmpsH;//����ߵ�������ת�۵��ADCֵ
			}
			else
			{
//				T = T + const_T_OffsetRun;				
				T25ADC = (const_adc_Test+(short)BufC[5]) - (const_temp_TestA+(float)(const_temp_TestB/0x80)*0.5-const_xtl_top)*const_TmpsH - const_T_OffsetRun*const_TmpsH;//����ߵ�������ת�۵��ADCֵ
			}		
		}
		else
		{
			//������ʱʹ��
			T25ADC = 1470 + (25 - const_xtl_top)*const_TmpsH;//�����ã��������滻Ϊ�¶ȶ�������
		}
		
		if( (SleepPtatOffsetCfg == 0x55)&&(EA_OFF) )//ͣ���¶Ȳ�������3v offset
		{
			if( const_ptat_Offset3V <= 10 )
				T25ADC -= const_ptat_Offset3V;
			else
				T25ADC -= 5;
		}		
		
		T25 = const_xtl_top;
		if( const_tx_flag != 0x3cc3 )//ͨ��У׼ʱ�����
		{
			TopF_Rtc_Adj = ((int16)((uint08)BufC[6]|((uint08)BufC[7]<<8)))/100.0;//��С100��
		}
		else			//��У��У׼ʱ�����
		{
			TopF_Rtc_Adj = const_rtc_adj_top/100.0;//��С100��
		}		
					
		if( AverADCf > T25ADC )	//����
 			Fa = const_TmpsH+0.05*BufC[0];
 		else
 			Fa = const_TmpsL+0.05*BufC[1];

		T = (AverADCf - T25ADC)/Fa + T25;

		//����¶ȷ�Χ��־�ж� 0=���£�1=���£�2=����
		if( T < 0 )
		{
			Result = 1;//���²��
		}
		else if( T > 50 )
		{
			Result = 2;//���²��
		}
		else
		{
			Result = 0;//���²��
		}
		
		if( const_C_Mode != 0x55 )
		{
			RTC_RT.TempFlag = 0;
			RTC_RT.CFixTrim = TopF_Rtc_Adj;
		}
		else if( ((Tpara.RtcTMode == 0xAA)||(Tpara.RtcTMode == 0x55)) && (RTC_RT.TempFlag != Result) )//�ı������У���²�����
		{
			RTC_RT.TempFlag = Result;

			Fill_RTC_RT_TAdc();
			Fill_RTC_RT_TVal();
			
			if( RTC_RT.TempFlag == 0 )//���²��
			{
				RTC_RT.CFixTrim = TopF_Rtc_Adj;
			}
			else if( RTC_RT.TempFlag == 1 )//���²��
			{
				Fa = const_KL +0.0001*BufC[3];
				RTC_RT.CFixTrim = TopF_Rtc_Adj + (-1.0)*Fa*(const_T_CL-const_xtl_top)*(const_T_CL-const_xtl_top);//���²�������¶������㣬ppm
			}
			else if( RTC_RT.TempFlag == 2 )//���²��
			{
				Fa = const_KH +0.0001*BufC[2];
				RTC_RT.CFixTrim = TopF_Rtc_Adj + (-1.0)*Fa*(const_T_CH-const_xtl_top)*(const_T_CH-const_xtl_top);//���²�������¶������㣬ppm
			}
		}
		
		if( (Tpara.RtcTMode == 0xAA)||(Tpara.RtcTMode == 0x55) )//���²���ֵģʽ,��ֹkrh��krl΢������
		{
			BufC[9] = 0;
			BufC[10] = 0;	
		}		
 		if( AverADCf > T25ADC )	//����
		{
			//����kh��kl΢���Գ��²���Ӱ��
			if(AverADCf > (T25ADC+const_KHKL_TrimRange)) Fa = const_KH +0.0001*BufC[2];
			else Fa = const_KH +0.0004*BufC[9];
			Fb = const_KH;
		}
 		else
		{
 			if(AverADCf < (T25ADC-const_KHKL_TrimRange)) Fa = const_KL +0.0001*BufC[3];	
			else Fa = const_KL +0.0004*BufC[10];	
			Fb = const_KL;
		}
		
		Rtcadj_Offset = Fa*(T-const_xtl_top)*(T-const_xtl_top);//���������㣬ppm
		Rtcadj_Offset2 = Fb*(T-const_xtl_top)*(T-const_xtl_top);//���������㣬ppm����У��
		
		//���²���ֵģʽ
		if( (Tpara.RtcTMode == 0xAA)&&( (AverADCf>RTC_RT.TAdc.PTAT_Value[0]) && (AverADCf<RTC_RT.TAdc.PTAT_Value[20]) ))//���������� 
		{
			Rtcadj = GetRtcRTrimVal( AverADCf );
			//������*�������� = ������ppm��
			Rtcadj = Rtcadj*0.23842;	//��С������Ϊ0.238ppm
			if( (const_mark404 == 0x0404)&&(RTC_Trim_Ctrl == 0x55) )
			{
				Rtcadj = Rtcadj/2.0;	//��С������Ϊ0.119ppm
			}
			Rtcadj = Rtcadj + ((short)BufC[4])/100.0 + RTC_RT.CFixTrim;
		}
		else if( (Tpara.RtcTMode == 0x55)&&progenable ) // ����ģʽ,ʹ�ù̶���Уֵ
		{
			if( (const_mark404 == 0x0404)&&(RTC_Trim_Ctrl == 0x55) )
			{
				Rtcadj = ((short)BufC[4])/100.0 + RTC_RT.CFixTrim + RTC_RT.TestTrim*0.11921;
			}
			else
			{
				Rtcadj = ((short)BufC[4])/100.0 + RTC_RT.CFixTrim + RTC_RT.TestTrim*0.23842;
			}
		}
		else if( (RtcStopProcFlag == 0x55)&&progenable )//ͨ��У׼ʱ�ӹرղ���������
		{
			Rtcadj = 0x00;
		}
		else if( (const_TopNoTrim == 0x55)&&(AverADCf < (T25ADC+const_TopNTRange))&&(AverADCf > (T25ADC-const_TopNTRange)) )
		{
			Rtcadj = ((short)BufC[4])/100.0+TopF_Rtc_Adj;
		}
		else
		{
			Rtcadj = ((short)BufC[4])/100.0+TopF_Rtc_Adj-Rtcadj_Offset;
		}
		
		if( (RTC_Trim_Ctrl == 0x55)&&(const_mark404 == 0x0404) )
		{
			Rtcadj = Rtcadj*8.388608;//ת��Ϊ��Уֵ,0.119
		}
		else
		{
			Rtcadj = Rtcadj*4.194304;//ת��Ϊ��Уֵ,0.238
		}
		
		if( Rtcadj >= 0 ) 
		{
			RTC->ADJUST = (uint32)(Rtcadj+0.5);	
			RTC->ADSIGN = 0x00;
		}			
		else              
		{
			RTC->ADJUST = (uint32)((Rtcadj-0.5)*-1.0);
			RTC->ADSIGN = 0x01;
		}           	
		
		if( T >= 0x00 )//���㵱ǰ�¶�
		{
			Temp16 = (unsigned short)(T*10);
			Hex2Bcd_SS( (unsigned char *)&Temp16, (unsigned char *)&Fun_Para.Temper_M, 2 );
		}
		else 
		{
			Temp16 = (unsigned short)(-T*10);
			Hex2Bcd_SS( (unsigned char *)&Temp16, (unsigned char *)&Fun_Para.Temper_M, 2 );
 			Fun_Para.Temper_M |= 0x8000;//���λ��1,��ʾ�����¶�			
		}

		if( EA_ON )//�¶ȱ仯һ����������һ��RC��У
		{
			j = (signed char)(T);

			if( Temperature_Hex > j )
			{
				if( (Temperature_Hex - j) >=5 )
				{
					Clk_Adj_Proc();	//�����ⲿ��32K�����������ڲ�8M��ƫ��
					Temperature_Hex = j;
				}
			}
			else
			{
				if( (j - Temperature_Hex) >=5 )
				{
					Clk_Adj_Proc();	//�����ⲿ��32K�����������ڲ�8M��ƫ��
					Temperature_Hex = j;
				}	
			}
		}
	}

	if ( Adcctrl.Status == B0001_0000 )//���adc����
	{	
		Adcctrl.Status = 0;
		ADCResultArr.ReadCount = 0;	
	
		if( (const_adc_Slope > 2000) && (const_adc_Slope < 2400) )
		{
			//ʹ�óɲ�����	
			Fun_Para.Voltage_B = (GetADCResult()*(float)(const_adc_Slope/10000.0)+(float)const_adc_Offset/1000.0)*2+constF_Volt;		
		}
		else
		{
			//������ʱʹ��
			Fun_Para.Voltage_B = ((GetADCResult()-10)*0.2174)*2+constF_Volt;	
		}

		Hex2Bcd_SS( (unsigned char *)&Fun_Para.Voltage_B, (unsigned char *)&Fun_Para.Voltage_B, 2 );
		
#else
	static float  RTCadj_Mod=0;
	if ( Adcctrl.Status == B0010_0000 )//�¶�adc���ݴ���,�����¶Ȳ���
	{		
		Adcctrl.Status = 0;	//Ϊ����ADC�����㷨���Ȳɼ�ADCֵ�ٽ�״̬��־λ��0
		ADCResultArr.ReadCount = 0;
		AverADCf = GetADCResult(0);

		if(AverADCf <= const_adc_Min) //�ж�ADC�Ƿ��쳣,���ٽ����¶Ȳ���
		{
			return;
		}
		
		Temperature_Adc =(unsigned short)(AverADCf*10); //���浱ǰ�¶�adc����ͨѶ����,��ʾ1λС��,�����Ͼ���  ��λ����Ҫ�����ݴ���/10  
		
		//0 �����¶�б��΢�����ݲ�֧�֣�
		//1 �����¶�б��΢�����ݲ�֧�֣�
		//2 ���¾�������΢���������޵����κ���ϵ����x*0.0001 kh
		//3 ���¾�������΢���������޵����κ���ϵ����x*0.0001 kl
		//4 ���¶����Уֵ����ֵ(��1.27ppm)	
		//5 �����¶�ADC΢��
		//6 ���¶����УֵL��ͨ�ŵ�ʱ������327.68ppm
		//7 ���¶����УֵH��ͨ�ŵ�ʱ����
		//8 RTC��������ģʽ��0x55:����ģʽ��0xAA���²���ֵģʽ����������ͨģʽ
		//9 ���¶����Уֵ����ֵ(ppm)
		//10���¶����Уֵ����ֵ(ppm)
		memcpy( BufC, Tpara.Offset, ee_temperature_lenth );//�����¶�ϵ��				
		for( i=0; i<6; i++ ) //��������ת�����з�����
		{
			Result = (unsigned char)(BufC[i]);
			if( Result&0x80 ) BufC[i] = ((~Result)|0x80)+1;
		}
		Result = (unsigned char)(BufC[9]);
		if( Result&0x80 ) BufC[9] = ((~Result)|0x80)+1;
		Result = (unsigned char)(BufC[10]);
		if( Result&0x80 ) BufC[10] = ((~Result)|0x80)+1;
	
//**********************�����¶ȶ���ֵ����25���Ӧ��ADCֵ****************************	//			
		if( const_temp_TestA == 0x1E )//ʹ���¶ȶ�������
		{			
			if( EA_OFF )
			{
				T25ADC = (const_adc_Test+(short)BufC[5]) - (const_temp_TestA+(float)(const_temp_TestB/0x80)*0.5-const_xtl_top)*const_TmpsH - const_T_OffsetSlp*const_TmpsH;//����ߵ�������ת�۵��ADCֵ
			}
			else
			{		
				T25ADC = (const_adc_Test+(short)BufC[5]) - (const_temp_TestA+(float)(const_temp_TestB/0x80)*0.5-const_xtl_top)*const_TmpsH - const_T_OffsetRun*const_TmpsH;//����ߵ�������ת�۵��ADCֵ
			}		
		}
		else //������ʱʹ�ã�оƬδ�����¶ȶ���
		{
			
			T25ADC = 1470 + (25 - const_xtl_top)*const_TmpsH;//�����ã��������滻Ϊ�¶ȶ�������
		}
		
		if( (SleepPtatOffsetCfg == 0x55)&&(EA_OFF) )//ͣ���¶Ȳ�������3v offset
		{
			if( const_ptat_Offset3V <= 10 )
				T25ADC -= const_ptat_Offset3V;
			else
				T25ADC -= 5;
		}

		
//**********************485ͨѶ�ռ�ʱ��У��������У****************************	//	
		T25 = const_xtl_top;
		if( const_tx_flag != 0x3cc3 )//ͨ��У׼ʱ�����
		{
			TopF_Rtc_Adj = ((int16)((uint08)BufC[6]|((uint08)BufC[7]<<8)))/100.0;//��С100��
		}
		else			//��У��У׼ʱ����оƬ���ʹ�ñ������У��Ͳ��ܽ���485��У
		{
			TopF_Rtc_Adj = const_rtc_adj_top/100.0;//��С100��
		}		
		
/**************************���㵱ǰ�����¶ȣ����жϵ�ǰģʽ******************************************/				
		T = (AverADCf - T25ADC)/const_TmpsH + T25;
		
/**************************��ͨģʽ�� KH��KL����*****************************************/			
 		if( AverADCf > T25ADC )	//���� //����kh��kl΢���Գ��²���Ӱ��
		{			
			if(AverADCf > (T25ADC+const_KHKL_TrimRange)) Fa = const_KH +0.0001*BufC[2];
			else Fa = const_KH ;
			Fb = const_KH;
		}
 		else
		{
 			if(AverADCf < (T25ADC-const_KHKL_TrimRange)) Fa = const_KL +0.0001*BufC[3];	
			else Fa = const_KL;	
			Fb = const_KL;
		}
		
		Rtcadj_Offset = Fa*(T-const_xtl_top)*(T-const_xtl_top);//���������㣬ppm
		Rtcadj_Offset2 = Fb*(T-const_xtl_top)*(T-const_xtl_top);//���������㣬ppm����У��
		
/**************************ʹ��ADC��Ͼ�����������*****************************************/	
		if( Tpara.RtcTMode == 0xAA)//���������� 
		{
			float K_3;//�¶Ȳ������׾���ϵ��
			float K_2;//�¶Ȳ������׾���ϵ��
			float K_1;//�¶Ȳ���һ�׾���ϵ��
			float K_0;//�¶Ȳ�����׾���ϵ��
			
			K_3 = (float)((float)RTC_RT.TAdc.PTAT_Value[0]/1000+(float)RTC_RT.TAdc.PTAT_Value[1]/10000000 + (float)RTC_RT.TAdc.PTAT_Value[2]/100000000000);		//3��ϵ��					
			K_2 = (float)((float)RTC_RT.TAdc.PTAT_Value[3]/1000+(float)RTC_RT.TAdc.PTAT_Value[4]/10000000 + (float)RTC_RT.TAdc.PTAT_Value[5]/100000000000);		//2��ϵ��		
			K_1 = (float)((float)RTC_RT.TAdc.PTAT_Value[6]/1000+(float)RTC_RT.TAdc.PTAT_Value[7]/10000000 + (float)RTC_RT.TAdc.PTAT_Value[8]/100000000000);		//1��ϵ��				
			K_0 = (float)(((float)RTC_RT.TAdc.PTAT_Value[9])*10+((float)RTC_RT.TAdc.PTAT_Value[10])/1000 + ((float)RTC_RT.TAdc.PTAT_Value[11])/10000000);				//0��ϵ��	
		
			 if((RTC_RT.TAdc.PTAT_Value[16] & BIT0)==0X01)
			 {
				 K_3 = - K_3; //ϵ��ȡ��
			 }
			 if((RTC_RT.TAdc.PTAT_Value[16] & BIT1)==0X02)
			 {
				 K_2 = - K_2; //ϵ��ȡ��
			 }			

			 if((RTC_RT.TAdc.PTAT_Value[16] & BIT2)==0X04)
			 {
				 K_1 = - K_1; //ϵ��ȡ��
			 }				 

			 if((RTC_RT.TAdc.PTAT_Value[16] & BIT3)==0X08)
			 {
				 K_0 = - K_0; //ϵ��ȡ��
			 }		
		 			
						
			 if(RTC_RT.TVal.Trim_Value[0] ==1)//�������»ָ�����(�û������Լ�Ӳ�����þ�������)+��+��+��+ ƫ��ֵ*0.01(�û����ݵ��ʵ��ƫ��ֵ����)
			 {
				 unsigned char Dtemperature;
							
				 Dtemperature=((RTC->BCDYEAR/16*10+RTC->BCDYEAR%16)-(RTC_RT.TVal.Trim_Value[2]))*365 + ((RTC->BCDMONTH/16*10+RTC->BCDMONTH%16)-(RTC_RT.TVal.Trim_Value[3]))*30 + (RTC->BCDDATE/16*10+RTC->BCDDATE%16)-(RTC_RT.TVal.Trim_Value[4]);
				 if(Dtemperature<RTC_RT.TVal.Trim_Value[1])//���������º�,ֻ�貹���ڳ���������
				 {
					Rtcadj  =  (K_3*AverADCf*AverADCf*AverADCf/1000000 + K_2*AverADCf*AverADCf/100 + K_1*10*AverADCf + K_0)+(RTC_RT.TVal.Trim_Value[5]*0.01);//������������ƫ�󣬹���Ҫ��ȥƫ��ֵ	
				 }
				 else
				 {
					Rtcadj  =  K_3*AverADCf*AverADCf*AverADCf/1000000 + K_2*AverADCf*AverADCf/100 + K_1*10*AverADCf + K_0;	
				 }
			 }
			 else //û�о�������
			 {
				Rtcadj  =  K_3*AverADCf*AverADCf*AverADCf/1000000 + K_2*AverADCf*AverADCf/100 + K_1*10*AverADCf + K_0;	
			 } 
			
		}
		
		else if( Tpara.RtcTMode == 0x55) // ����ģʽ�·�ԭʼ���ֵ����֤�·������ֵ�Ƿ���ȷ
		{			
			Rtcadj = (float)RTC_RT.TestTrim/100; //ԭʼ����ԷŴ�100������ʽ�����·���
		}		
		else if( (RtcStopProcFlag == 0x55)&&progenable )//ͨ��У׼ʱ�ӹرղ���������
		{
			Rtcadj = 0x00;
		}else if( (const_TopNoTrim == 0x55)&&(AverADCf < (T25ADC+const_TopNTRange))&&(AverADCf > (T25ADC-const_TopNTRange)) )
		{
			Rtcadj = TopF_Rtc_Adj;
		}		
		else
		{
			Rtcadj = TopF_Rtc_Adj-Rtcadj_Offset;
		}

/**************************�ߵ�������΢��****************************************/		
		if( T < -15 )
		{
			Rtcadj = Rtcadj+((short)BufC[10])/100.0;//��������
		}
		else if( T > 45 )
		{
			Rtcadj = Rtcadj+((short)BufC[9])/100.0;//��������
		}
		else
		{
			Rtcadj = Rtcadj+((short)BufC[4])/100.0;//��������
		}	
	
/**************************������Rtcadj(��λPPM)ת���ɵ�Уֵ**************************************/				
		if( (RTC_Trim_Ctrl == 0x55)&&(const_mark404 == 0x0404) )
		{
			Rtcadj = Rtcadj*8.388608;//ת��Ϊ��Уֵ,0.119
		}
		else
		{
			Rtcadj = Rtcadj*4.194304;//ת��Ϊ��Уֵ,0.238
		}

/**************************RTC���� ��Уֵ����RtcADJ_Offset�ۼӵ�1��RTC->ADJUST����1*************************************/				
		if( Rtcadj >= 0 ) 
		{	
			RTC->ADSIGN = 0x00;			
			RTCadj_Mod =RTCadj_Mod+(Rtcadj-((uint32)(Rtcadj)));	//	���ת��Ϊ��Уֵ������		
			if(RTCadj_Mod>=1)//�ж�RTC����ֵС��λ�ۼӻ��۵�1������RTC->ADJUST =10.21 ֻ��д10   0.21�ᱻ������ͨ���ۼӵ���������1��RTC->ADJUST����ֵ�����1
			{
				RTC->ADJUST = (uint32)(Rtcadj)+1;		
				RTCadj_Mod	=RTCadj_Mod-1;
			}else
			{
				RTC->ADJUST = (uint32)(Rtcadj);			
			}
		
		}			
		else              
		{
			RTC->ADSIGN = 0x01;		
			RTCadj_Mod =RTCadj_Mod+((Rtcadj)*(-1.0)-(uint32)((Rtcadj)*(-1.0)));				
			if(RTCadj_Mod >=1)//�ж�RTC����ֵС��λ�ۼӻ��۵�1������RTC->ADJUST =10.21 ֻ��д10   0.21�ᱻ������ͨ���ۼӵ���������1��RTC->ADJUST����ֵ�����1
			{
				RTC->ADJUST = ((uint32)(Rtcadj)*(-1.0))+1;		
				RTCadj_Mod	=RTCadj_Mod-1;
			}else
			{
				RTC->ADJUST = (uint32)(Rtcadj)*(-1.0);			
			}							
		}           	
		
		if( T >= 0x00 )//���㵱ǰ�¶�
		{
			Temp16 = (unsigned short)(T*10);
			Hex2Bcd_SS( (unsigned char *)&Temp16, (unsigned char *)&Fun_Para.Temper_M, 2 );
		}
		else 
		{
			Temp16 = (unsigned short)(-T*10);
			Hex2Bcd_SS( (unsigned char *)&Temp16, (unsigned char *)&Fun_Para.Temper_M, 2 );
 			Fun_Para.Temper_M |= 0x8000;//���λ��1,��ʾ�����¶�			
		}

		if( EA_ON )//�¶ȱ仯һ����������һ��RC��У
		{
			j = (signed char)(T);

			if( Temperature_Hex > j )
			{
				if( (Temperature_Hex - j) >=5 )
				{
					Clk_Adj_Proc();	//�����ⲿ��32K�����������ڲ�8M��ƫ��
					Temperature_Hex = j;
				}
			}
			else
			{
				if( (j - Temperature_Hex) >=5 )
				{
					Clk_Adj_Proc();	//�����ⲿ��32K�����������ڲ�8M��ƫ��
					Temperature_Hex = j;
				}	
			}
		}
	}

	if ( Adcctrl.Status == B0001_0000 )//���adc����
	{	
		Adcctrl.Status = 0;
		ADCResultArr.ReadCount = 0;	
	
		if( (const_adc_Slope > 2000) && (const_adc_Slope < 2400) )
		{
			//ʹ�óɲ�����	
			Fun_Para.Voltage_B = (GetADCResult(1)*(float)(const_adc_Slope/10000.0)+(float)const_adc_Offset/1000.0)*2+constF_Volt;		
		}
		else
		{
			//������ʱʹ��
			Fun_Para.Voltage_B = ((GetADCResult(1)-10)*0.2174)*2+constF_Volt;	
		}

		Hex2Bcd_SS( (unsigned char *)&Fun_Para.Voltage_B, (unsigned char *)&Fun_Para.Voltage_B, 2 );
#endif		
		if( EA_OFF ) return;
		
		if( Fun_Para.Voltage_B < Def_Vthreshold )	//��ص���Ƿѹ��ֵ������ʱ60s�������Ƿѹ��¼
		{
			if( low_voltage_flag == 0 )
			{
				if( Bat_Delay_Timer < 0x05 ) 	//ÿ10�봦��һ��
					Bat_Delay_Timer += 0x01;
				else
				{
					low_voltage_flag = 1; //��ص�ѹ��־
					change_batt_flag = 1; //�����ظ�����־
					Store_Meterstatus();
					DltoEepromBuf( 6 );
					Comp_RpdltoEepromBuf( 14 );
					Event_Record( ee_batterlow_inpage );
				}
			}
		}
		else
		{
			Bat_Delay_Timer = 0;
			if( low_voltage_flag )
			{
				low_voltage_flag = 0;
				Store_Meterstatus();
			}
		}
		
		if( (Fun_Para.Voltage_B > Def_Vthreshold_H) && change_batt_flag )
		{
			if( change_batt_flag )
			{
				if( Bat_Change_Timer==0 ) Bat_Change_Timer = 0x02; //ÿ10�봦��һ��
				if( Bat_Change_Timer  )
				{
//					if( Bat_Change_Timer == 0x03 ) //��ǰ30s��¼����
//					{
//						if( RdRecTimes(ee_batchangen_inpage) )
//						{
//							unsigned char  Temp08, BufA[ee_batchangenote_len];
//							
//							Temp08 = Read_Event_Point(ee_batchangen_inpage);
//							I2C_Read_Eeprom( ee_batchange_note_page+Temp08, ee_batchangenote_inpage, BufA, ee_batchangenote_len );	//ʱ��  
//							Temp08 =ChkBufZero(BufA+6,6);
//							if( Temp08 == 1 )	//��һ�ε�ظ����н���ʱ��ſ��µĵ�ظ�����¼
//							{
//								Note_Run_Event( ee_batchangen_inpage ); //��ظ��������¼�    
//							}   
//						}
//						else  Note_Run_Event( ee_batchangen_inpage ); //��ظ��������¼�              
//					}
					
					Bat_Change_Timer --;
					if( Bat_Change_Timer == 0x00 )
					{
						Note_Run_Event( ee_batchangen_inpage ); //��ظ��������¼�  
						change_batt_flag = 0;
						Store_Meterstatus();
						Note_Run_Event( ee_batchangen_inpage|0x80 );	//��ظ��������¼�
					}
				}
			}
		}
		
		
		if( constF_Volt && (Fun_Para.Voltage_B>0x368) )  Fun_Para.Voltage_B = 0x368; //�����յ�ص�ѹ����3.68��ǿ��Ϊ3.68
		if( Fun_Para.Voltage_B < 0x80 ) Fun_Para.Voltage_B = 0; //��ѹ����0.8Vǿ�ƹ���
	}
}
