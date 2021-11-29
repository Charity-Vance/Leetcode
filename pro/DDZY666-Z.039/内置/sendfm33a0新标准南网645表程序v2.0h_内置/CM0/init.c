#include "ex_func.h"
#include "ex_var.h"
#include "FM32L0XX.h"  
#include <string.h>


void Init_Pad_Io(void)
{	
	GPIOB->ODR = BIT6|BIT7|BIT11;		//6.PULSELED, 7.VBLE 11.relayctrl=1/EEVCC
	GPIOD->ODR = BIT7;				//7.关ESAMVCC
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
	if( EA_OFF && (WWDT->WWDTCNT > 1024/2) )  {__NOP();__NOP();WWDT->WWDTCON = 0xac;}//清wwdt
}

void WWDT_Init(void)
{
	WWDT->WWDTCFG = 0x07;	//pclk*4096*1024 (512ms @8M)
	WWDT->WWDTCON = 0x5a;	//启动wwdt
}


void Clear_W_Wdt()
{
	WWDT->WWDTCON = 0xac;//清wwdt
}

//uint08 Call_Get_PRIMASK( void )
//{
//	uint32 Result;
//	Result = __get_PRIMASK();
//	return (uint08)Result;
//}

void I2c_Wait_5ms( void ) //延时5ms
{
	TicksDelayMs(5*clkmode,NULL);
}


void Delay_Initial(unsigned char Num) //延时Num*5ms(最长延时最好小于800ms)
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


void Clear_Nv_Ram()//清startup里未清除的部分ram
{
	memset( (uint08 near*)(0x20000000), 0x00, ((uint32)(&Fwdl)-0x20000000) );	//截止于剩余金额处
}


void Nvram_Judge()	//掉电不清除ram合法性判断
{
	if( (Password_Err[0]>Defpassworderrcnt) || (Password_Err[1]>Defpassworderrcnt) || (Mac_Err_Times > 200) ) Clear_Nv_Ram();//清startup里未清除的部分ram
}


void Note_Reset_Number()	//记录上电复位和wdt复位次数,如何是上电复位清ram
{	
	unsigned char i;
	
	for( i=0; i<20; i++ ) I2c_Wait_5ms();	//延时100ms
		
	if( I2C_Read_Eeprom44( ee_meterstatus1_page, Eeprom.Buffer, ee_meterstatus1_lenth)==0 )//读电表状态字到ram成功
	{
		Meter_Status  = Eeprom.Buffer[0];
		Meter_Status1 = Eeprom.Buffer[1];
		Meter_Status2 = Eeprom.Buffer[2];
	}
	
	if( RCC->RSTFLAG & (BIT9|BIT8) )//上电复位下电复位
	{	
		I2C_Read_Eeprom44( ee_wdt_page, Eeprom.Buffer,ee_wdt_lenth );//上电复位次数加1
		if( RCC->RSTFLAG & BIT9 )
		{
			if( Eeprom.Buffer[7] < 255 ) Eeprom.Buffer[7]++;
		}
		if( RCC->RSTFLAG & BIT8 )
		{
			if( Eeprom.Buffer[6] < 255 ) Eeprom.Buffer[6]++;
		}
		I2C_Write_Eeprom44( ee_wdt_page, Eeprom.Buffer, ee_wdt_lenth );

		Clear_Nv_Ram();//清startup里未清除的部分ram
		memset( (uint08 near*)(0x20000000), 0x00, ((uint32)(&RAMBUF[32])-0x20000000) );	//清startup里所有的数据包括电量
		
		if( I2C_Read_Eeprom( ee_reportdata_page, 0, Eeprom.Buffer, ee_reportdata_lenth)==0 )//读事件上报数据
		{
			if( Eeprom.Buffer[0] != 0xff )//防止出现非法数据
			{
				System_Status = (Eeprom.Buffer[0]&0x3f);//恢复标志
				if( Eeprom.Buffer[0]&0x80 ) Cover.Status = 1;//恢复开盖状态
				memcpy( Report_Data, Eeprom.Buffer+1, ee_reportdata_lenth-1 );
			}
		}		
		below_60u_flag = 1;	//任何复位不支持更新当前记录的上电结束时间(除上下电复位)
	}
	if ( RCC->RSTFLAG & (BIT4|BIT2) )//iwdt, wwdt
	{	
		I2C_Read_Eeprom44( ee_wdt_page, Eeprom.Buffer, ee_wdt_lenth );
		if( RCC->RSTFLAG & BIT4 )
		{
			if( Eeprom.Buffer[3] < 255 ) Eeprom.Buffer[3]++;
		}
		if( (RCC->RSTFLAG & BIT2) && (RAMREG3 != 0xaa) )//休眠唤醒的wwdt复位,复位次数不加1
		{
			if( Eeprom.Buffer[2] < 255 ) Eeprom.Buffer[2]++;
		}
		I2C_Write_Eeprom44( ee_wdt_page, Eeprom.Buffer, ee_wdt_lenth );	
//		Clear_Nv_Ram();//清startup里未清除的部分ram

		if( RAMREG3 == 0x55 )//hardfault引起的看门狗复位
		{
			I2C_Read_Eeprom( ee_hardfault_page, ee_hardfault_inpage, Eeprom.Buffer, ee_hardfault_lenth );//HardFault_Flag引起wwdt复位次数加1
			Read_Rtc( Eeprom.Buffer );//读当前时间(周在中间)
			if( Eeprom.Buffer[7] < 255 )  Eeprom.Buffer[7]++;//累计次数加1
			I2C_Write_Eeprom( ee_hardfault_page, ee_hardfault_inpage, Eeprom.Buffer, ee_hardfault_lenth );
		}
	}	
	
	if ( RCC->RSTFLAG & 0x00010C63 )//其他复位标志计数
	{	
		I2C_Read_Eeprom44( ee_wdt_page, Eeprom.Buffer, ee_wdt_lenth );
		if( RCC->RSTFLAG & BIT16 )	//模式诊断复位
		{
			if( Eeprom.Buffer[10] < 255 ) Eeprom.Buffer[10]++; 
		}	
		if( RCC->RSTFLAG & BIT11 )	//NRST复位	
		{
			if( Eeprom.Buffer[9] < 255 ) Eeprom.Buffer[9]++; 
		}	
		if( RCC->RSTFLAG & BIT10 )	//TESTN复位	
		{
			if( Eeprom.Buffer[8] < 255 ) Eeprom.Buffer[8]++; 
		}	
		if( RCC->RSTFLAG & BIT6 )	//EMC复位	
		{
			if( Eeprom.Buffer[5] < 255 ) Eeprom.Buffer[5]++; 
		}
		if( RCC->RSTFLAG & BIT5 )	//软件复位	
		{
			if( Eeprom.Buffer[4] < 255 ) Eeprom.Buffer[4]++; 
		}
		if( RCC->RSTFLAG & BIT1 )	//CPU锁定复位	
		{
			if( Eeprom.Buffer[1] < 255 ) Eeprom.Buffer[1]++; 
		}	
		if( RCC->RSTFLAG & BIT0 )	//NVIC复位	
		{
			if( Eeprom.Buffer[0] < 255 ) Eeprom.Buffer[0]++; 
		}			
		I2C_Write_Eeprom44( ee_wdt_page, Eeprom.Buffer, ee_wdt_lenth );
	}
		
	if ( RAMREG3 == 0xaa )//上电唤醒或者通过缓升缓降初始化
	{		
		Nvram_Judge();//掉电不清除ram合法性判断
		System_Status = System_St_Bk; //恢复标志
		ANAC->SVDSIF = 0x00000003;
		below_60u_flag = 1;	//任何复位不支持更新当前记录的上电结束时间
	}	
	else if( (RCC->RSTFLAG&0x00010F77) == 0 )//异常
	{
		I2C_Read_Eeprom44( ee_wdt_page, Eeprom.Buffer, ee_wdt_lenth );//异常复位次数加1
		if( Eeprom.Buffer[11] < 255 ) Eeprom.Buffer[11]++; 
		I2C_Write_Eeprom44( ee_wdt_page, Eeprom.Buffer, ee_wdt_lenth );
		Clear_Nv_Ram();//清startup里未清除的部分ram
	}
	
	RCC->RSTFLAG = 0x00010F77;//清复位标志
	
	RAMREG3 = 0;//缓升缓降标志字节
	RAMREG13 = 0;//清停电上报运行时间
	Nvram_Judge();//掉电不清除ram合法性判断
	
	#if(1 == CHINT_Mode)
	if( I2C_Read_Eeprom(ee_softij_page, ee_softij_inpage, Ijtimer_Para.Ijtimer.B08, 4) != 0)	//上电读取软件I_J定时值
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
	
	if( ((Temp32>>16)&0x0000FFFF) == ((~Temp32)&0x0000FFFF) )	//正反码校验判断
	{
		RCC->RCHFTRIM = Temp32&0x0000007F;
	}	
	else
	{
		RCC->RCHFTRIM = 0x00000040;
	}
}


//xtlf的32768Hz时钟作为参考源
//本函数仅适用于APB不分频的情况
void Clk_Adj_Proc( void )
{
	uint16 Temp16;
	unsigned char n,m,i,tempbyte,TrimBuf;	
	float DIVclkmode = 1.0;
	
	if( ((ANAC->FDETIF)&BIT6) == 0)//xtlf停振
	{
		//使用测试参数		
		Init_RCHF_Trim();
		return;
	}
			
	ETIMER1->ETxCR    = 0x00000044;		//ET1~~ , 捕捉模式,周期捕捉,上沿清零，连续捕捉，上升沿捕捉
										//计数源Fcpu、捕捉源xtlf
	ETIMER1->ETxINSEL = 0x00000008;		//计数源Group1信号=apbclk(Fcpu),捕捉源Group2信号=xtlf
	
	ETIMER1->ETxPESCALE2 = 127;//捕捉源128分频

	ETIMER1->ETxIE  = 0x00000000;		//禁止ET1中断
	ETIMER1->ETxIF |= 0x00000007;		//bit0：溢出中断 bit1：捕捉中断；
	
	i = clkmode - 1;	
//	for(i=0;i<4;i++)
	{		
		switch(i)
		{
			case 0://8
				ETIMER1->ETxPESCALE1 = 0;//计数源1分频
				DIVclkmode		= 1.0;
				break;
			
			case 1://16/2
				ETIMER1->ETxPESCALE1 = 1;//计数源2分频
				DIVclkmode		= 1.0;
				break;
			
//			case 2://24/4
//				ETIMER1->ETxPESCALE1 = 3;//计数源4分频
//				DIVclkmode		= 8.0/6.0;
//				break;
//			
//			case 3://32/4
//				ETIMER1->ETxPESCALE1 = 3;//计数源4分频
//				DIVclkmode		= 1.0;
//				break;	
			
			default:
				ETIMER1->ETxPESCALE1 = 0;//计数源不分频
				DIVclkmode		= 1.0;
				break;		
		}
		
		for( m=0; m<6; m++ )
		{
			Clear_Wdt();
			
			ETIMER1->ETxCR |= 0x00000080;	//启动ET
			
			for( n=0; n<2; n++ ) //理论上判断需要3.906ms = 128/32768 s
			{		
				Temp16 = 0;
				Do_DelayStart();
				{
					if( ETIMER1->ETxIF & 0x00000002 ) {Temp16 = 1; break;}
				}While_DelayMsEnd(7.5*clkmode);		//7.5ms
				ETIMER1->ETxIF |= 0x00000002;
			}	
			ETIMER1->ETxCR &= (~0x00000080); 	//关闭定时器
			if( Temp16 == 0 ) continue;
				
			Temp16 = ETIMER1->ETxIVR;
				
			if( (Temp16>(31250-120)/DIVclkmode)&&(Temp16<(31250+120)/DIVclkmode) ) //return;//修正到理想值直接返回
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
				
				if( m == 5 )				//未找到理想值,采用最后2次的值取平均
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
//	IE   = B0001_0010;	//使能TIME0中断,使能串口(被外设占用)中断
//	IPH  = B0000_0000;	//无优先级
//	IPL  = B0000_0000;	//无优先级
//	
//	AIE  = B0000_0111;	//使能附加中断0/1/2（被芯片各种外设占用）
//	AIPH = B0000_0000;	//无优先级
//	AIPL = B0000_0000;	//无优先级
//	
//	TMOD = B0000_0001;	//16bit定时,定时时间2731*1.5us=4096us
////	TL0  = 0x55;		//65536-2731=0XF555,@8M
////	TH0  = 0xF5;
//	TR0  = 1;		//启动time0
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
//	if( JudgeClockNoWeek(0, Clock, 6) )	return 1;	//无效的起始时间
	
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
				for( n=0; n<12*99; n++ )	//每次调用此函数，最大可增加的天数是255
				{
					//本月剩余天数和未增加天数比较
					MaxDay = Days[ (HexClock[4]-1) ];
					if( HexClock[4] == 2 )
					{
						Year = HexClock[5] + 2000;
						if( (Year%4==0&&Year%100!=0) || (Year%400==0) ) MaxDay++;	//闰年
					}
					
					if( (MaxDay-HexClock[3]) >= Num )	//本月剩余天数 大于 未增加天数, 则不用切换月
					{
						HexClock[3] += Num;
						Num = 0x00;
						break;
					}
					
					if( Num )
					{
						Num -= (MaxDay-HexClock[3]+1);	//再减1是为了修正月切换后,日数据为1。

						HexClock[3] = 0x01;	//日数据为1号
						HexClock[4]++;	//月份增加
						if( HexClock[4] > 12 ) 
						{
							HexClock[4] = 0x01;	//超过12个月则切换到下一年的一月份
							HexClock[5]++;	//年切换到下一年
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


void Powerd_Data_Process()	//时钟错误用掉电时间恢复和尾数恢复
{
	unsigned char  i, Buf[ee_powerdown_lenth+2];
	unsigned char  BufA[ee_powerdownnote_lenth];
	
	if( I2C_Read_Eeprom( ee_monthvolrun_page, ee_monthvolrun_inpage, Eeprom.Buffer, ee_monthvolrun_lenth )== 0 )//读日和月电压合格率运行状态
	{
		memcpy( VolStatus[0].Total.B08, Eeprom.Buffer, ee_monthvolrun_lenth );
	}
	
	Pd_Hourfreeze_Judge();	//上电整点冻结和定时冻结补存判断处理(需要停电时间)
	
	if( I2C_Read_Eeprom( ee_power_down_page, 0x00, Buf, ee_powerdown_lenth ) == 0 )
	{
		Decimal.Add = Buf[7];//恢复有功脉冲增量
		Decimal.Add_Rp = Buf[8];//恢复无功脉冲增量
		ReportList[0] = Buf[22]&B0011_0000; //恢复主动上报次数
		
		if( clock_error == 0 )
		{
			if( Cmp_Bcd_Inv(Sclock.Clockbackup, Buf, 6)==2 ) clock_error = 1;//上电时间小于掉电时间
			else
			{
				Buf[7] = Buf[5];//保存掉电年
				Buf[5] = Hex_To_Bcd(Bcd_To_Hex(Buf[5])+3);	//掉电时间加n年(n=3)
				if( Cmp_Bcd_Inv(Sclock.Clockbackup, Buf, 6)==1 ) clock_error = 1;//上电时间大于掉电时间加n年	
				Buf[5] = Buf[7];//掉电年恢复
			}
			
			if( clock_error )
			{
//				Syn_Clock();//同步主和备份时钟	
				memcpy( Sclock.Clockbackup, Buf, 6 );		//时钟故障发生时间是掉电时间(同故障结束时间)
				if( ChkLastclockerrRcdTime() != 1 ) Note_Run_Event(ee_clockerrn_inpage); //时钟故障开始记录(时钟非法)
			}
		}
		
		if( clock_error )
		{
			memcpy( BufA, Buf, 3 );//秒分时
			memcpy( BufA+4, Buf+3, 3 );//日月年
			BufA[3] = (CalcAbsDay(BufA+2)+6)%7;	//计算周,格式为秒+分+时+周+日+月+年,起始地址周,从日开始计算
			Set_Rtc( 0, BufA, 7 );//周在中间
			Read_Sysclock();	//读时钟
		}
		
		//事件补存处理
//		if( Buf[9] != 0xff )//防止出现非法数据
		{
//			ReportList[0] = Buf[22]&B0011_0000; //恢复主动上报次数
			
			if( RAMREG11 == 0xaa )//补记电源异常记录
			{
				memcpy( Sclock.Clockbackup, Buf, 6 );//电源异常发生时间			
				AddNClock( 0, Sclock.Clockbackup, 1 );
				Note_Run_Event(ee_powererrn_inpage);		//电源异常开始记录
				
				Syn_Clock();	//同步时钟
				Note_Run_Event(ee_powererrn_inpage|0x80);	//电源异常结束记录
			}
			RAMREG11 = 0;
			
			if( RAMREG12 )//补记开盖事件记录
			{
				memcpy( Sclock.Clockbackup, RAMBUF, 6 );//开盖发生时间
				if( (RAMREG12 == 0xaa) || (RAMREG12 == 0xbb)  )	//记录开盖发生
				{	
					Note_Run_Event(ee_covern_inpage);	//记录开盖事件记录
				}
				
				memcpy( Sclock.Clockbackup, RAMBUF+6, 6 );//开盖结束时间	
				if( (RAMREG12 == 0x55) || (RAMREG12 == 0xbb) )//记录开盖结束
				{
					Note_Run_Event(ee_covern_inpage|0x80);	//记录合盖事件记录
				}
				
				Syn_Clock();	//同步时钟
			}
			RAMREG12 = 0;
			
			memcpy( Sclock.Clockbackup, Buf, 7 );//使用掉电时间完成事件记录
			if( Buf[9]&0x80 )
			{
				if( ChkPdRcdTime() == 1 )//上一次掉电有结束时间才开新的掉电记录
				{
					Note_Run_Event( ee_powerdownn_inpage ); //掉电事件起始记录
				}     
			}
			if( Buf[9]&0x40 ) relay_error = 1;	//负荷开关异常结束记录
			if( Buf[9]&0x20 ) Note_Run_Event(ee_maxi_inpage|0x80);	//记录电流过载事件(结束)
			if( Buf[9]&0x10 ) Note_Run_Event(ee_calerrn_inpage|0x80); //计量芯片故障结束记录
			if( Buf[9]&0x08 ) Note_Run_Event(ee_nlineerrn_inpage|0x80); //零线电流异常结束记录
			if( Buf[9]&0x04 ) //记录失压事件(结束)
			{
				memcpy( &Lost_Aver_I, Buf+10, 4 );
				memcpy( &Lost_V_Timer, Buf+14, 4 );
				Note_Run_Event(ee_lostvn_inpage|0x80); //记录失压事件(结束)
			}
			if( Buf[9]&0x02 )
			{
				memcpy( &Current_Over_Count41, Buf+18, 2 );//恢复低电压事件临时累计时间
			}
			if( Buf[9]&0x01 )
			{
				memcpy( &Current_Over_Count51, Buf+20, 2 );//恢复高电压事件临时累计时间
			}
			
			MvFlash.Obj = Buf[23]&0x3F;
			MvFlash.Dir = 0x00;
			if( Buf[23]&0x40 ) MvFlash.Dir = 0x55;
			if( Buf[23]&0x80 ) MvFlash.Dir = 0xAA;
			MvFlash.Offset = Byte2uShort(Buf+24);

			SynFlash.Crc16++; //加载时间回退参数到RAM
			I2C_Read_Eeprom( ee_synflash_page, ee_synflash_inpage, (uint08*)SynFlash.HisRec, ee_synflash_len );
			
			Syn_Clock();	//同步时钟
		}
		
		Pd_Calculate_Judge();	//停电统计处理
		
		Wr_Powerdown_Data(0);//写掉电相关数据到数据ee(主要目的清脉冲尾数和相关标志)
		
		//月改变处理和年改变处理
		if( Buf[5] != Sclock.Clockbackup[5] ) //年改变
		{
			year_change_flag2 = 1;
		}
		if( Buf[4] != Sclock.Clockbackup[4] || year_change_flag2 ) //月改变
		{
			//掉电时间后面的一个月
			{Sclock.Clockbackup[0]=0;Sclock.Clockbackup[1]=0;Sclock.Clockbackup[2]=0;Sclock.Clockbackup[3]=0x01;}
			if( Buf[4]<0x12 )
			{
				Sclock.Clockbackup[4]=Hex_To_Bcd(Bcd_To_Hex(Buf[4])+1);//月
				Sclock.Clockbackup[5]=Buf[5];//年
			}
			else
			{
				Sclock.Clockbackup[4]=0x01;//月
				Sclock.Clockbackup[5]=Hex_To_Bcd(Bcd_To_Hex(Buf[5])+1);//年
			}
			Freeze_Dl( ee_monthfreeze_page, ee_monthn_inpage );//月冻结（补一次）
			Syn_Clock();	//同步时钟
		}
		Freeze_Pddata();	//冻结掉电数据		
	}
		
	run_loadchk_flag = 0;	//防止上电误触发负荷记录
	if( Crc_Check( Load.Point, ee_loadpoint_lenth+2 ) )	//ram负荷记录指针错误
	{
		memcpy( Load.Point, Buf+26, ee_loadpoint_lenth+2 );//读负荷记录指针到ram
	}
	
	//上电刷新负荷记录的RAM区，方便掉电时保存
	for( i=0; i<max_casecount; i++ )
	{
		if( Load.Point[5*i+3] )	break;
	}
	
	if( i < max_casecount )
		I2C_Read_Eeprom( ee_ploadrec_page, 0, LoadBuf, ee_ploadrec_lenth );
}


void Init_Relay( void )
{	
	if( Relay_Mode != 0x55 )//内置继电器
	{
		{RELAYOFF1; __NOP(); RELAYOFF2;}//磁保持继电器无效
	}
	else
	{
		if(Mode.Feature1&0x01)//脉冲方式
		{
			RELAYOFF3;
		}
		else
		{
			if(relay_status_flag==0)RELAYOFF3;//继电器闭合
			else RELAYON3;//继电器断开
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
	I2C->I2CERR = 0x00000007;	//清I2C错误标志

	if( (RCC->RSTFLAG == 0x00000004) && (Wwdt_Lcd_Ctrl == 0x55) && (HardFault_Flag==0x11223344) )//仅仅wwdt复位
	{		
		HardFault_Flag = 0;
		RCC->RSTFLAG = 0x00000004;//清复位标志
		Enable_I2C_IO();
		Close_None_GPIO();
		Veri_Sys_Reg();
		
		RAMREG3 = 0;//缓升缓降标志字节
		Nvram_Judge();//掉电不清除ram合法性判断
				
		I2C_Read_Eeprom( ee_hardfault_page, ee_hardfault_inpage, Eeprom.Buffer, ee_hardfault_lenth );//HardFault_Flag引起wwdt复位次数加1
		Read_Rtc( Eeprom.Buffer );//读当前时间(周在中间)
		if( Eeprom.Buffer[7] < 255 )  Eeprom.Buffer[7]++;//累计次数加1
		I2C_Write_Eeprom( ee_hardfault_page, ee_hardfault_inpage, Eeprom.Buffer, ee_hardfault_lenth );
		Uart[CHHW].Overtime_Timer = txtimeout_max;
		Uart[CHBLE].Overtime_Timer = txtimeout_max;
		Uart[CH485].Overtime_Timer = txtimeout_max;
		Uart[CHZB].Overtime_Timer = txtimeout_max;
		
		{Powerd_Flag = 0;__enable_irq();WWDT_Init();}//打开中断并且启动wwdt
		return;
	}
		
	Veri_Clk_Gen();
	Enable_I2C_IO();
	I2c_Wait_5ms();		//PR1SEN置位前需先使能PLL,并等待足够时间（>2ms）确保PLL锁定
	
	Init_Pad_Io();
	CloseFlash();
	Disable_Pulse();	//关闭计量
	Veri_Pad();
	Close_None_GPIO();		
	Veri_Sys_Reg();
	MeterIC_RST0();		//复位计量芯片
	CloseEsam();		//ESAM所有IO为低电平

	if( !(SVDCHKPLOW) )//未发生欠压
	{
		RELAYLEDON;		//跳闸灯和报警灯亮一下
		LCDLEDON;
	}
        
	Display_Para_Verify();	//显示数据校验
	Displayitem_Verify();	//显示项目校验
	Display.Number=0xff;
	Display.Timer = Display_Para.A_Time;//上电全显
	Init_Led_Timer = Display_Para.A_Time;//拉闸灯	
	Lcdled = Display_Para.A_Time;//点亮背光
	Lcd_Display();		//上电全显
	DISP->LCDBIAS   = Fulllcdbias;	//设置全屏灰度
	Lcd_LCDEN_On();		//打开lcd正常显示
	
	Note_Reset_Number();	//记录上电复位和wdt复位次数
	Resetworking_Timer = resetworking_timer_delay;//启动复位脉冲
	PLC_RST0;		//复位载波(输出低)
	Mod_Comm_Timer1 = 0;
	Mod_Comm_Timer2 = Mod_Comm_Timer_delay2; //启动5min通信模块异常延时定时器

	Mode_Verify();		//特征模式字校验
	Init_Relay();		//上电继电器处理	
	Veri_Uart_All();	//通讯波特率校验
	Commaddr_Verify();	//通讯地址校验
	
	Read_Sysclock();	//读时钟
	Fwdl_Verify();		//正向电量校验
	Bkdl_Verify();		//反向电量校验
	for(i=0; i<4; i++)
	Rpdl_Verify(i);		//无功电量校验
	Mt_Alarmstatus_Judge();	//电表报警状态判断
	Temperpara_Verify();	//温度系数校验	
	
	Clear_Wdt();
	Timezone_Judge();	//时区时段费率判断
	GetKeyStatus();		//读当前密钥状态
	
	if( !(SVDCHKPLOW) )//未发生欠压
	{
		Enable_Led_IO();
		RELAYLEDON;		//跳闸灯和报警灯亮一下
		LCDLEDON;
	}
	Adcctrl.Timer=3;	//保证很快启动电池电压和温度adc
	RTC_RT.TempFlag = 0xff;//更新查表数据
	Temperature_Hex = 0x7f;	//温度变化5度以上自动时钟调校(延时2s后调用)
	Init_RCHF_Trim();	//校准值配置(16M必须手动)
	below_60u_flag = 1;
	Voltage_Low_Count = Deflowvoltagecount_s;
	PowerDetCnt2 = Def_Powerdetcnt2;//上电3s内掉电，不做电源异常检测

	RTC->RTCIF = RTC_RTCIF_SEC_IF_ENABLE;	//仅清除秒中断标志
	NVIC_ClearPendingIRQ(RTC_IRQn);
	NVIC_DisableIRQ(BT1_IRQn);
	NVIC_DisableIRQ(BT2_IRQn);
	{Powerd_Flag = 0;__enable_irq();WWDT_Init();}//打开中断并且启动wwdt
	Delay_Initial(100);	//延时500ms
	if( EA_OFF ) Sleep(0);	//进入sleep

	MeterIC_RST1();		//计量芯片使能(保证足够延时后才处理计量芯片)
	Powerd_Data_Process();	//掉电数据处理
//	Init_Dayfreeze_Judge();	//上电7天日冻结补存
	Pd_Histroyfreeze_Judge();//上电结算日补存判断处理
	Timezone_Judge();	//时区时段费率判断
	Year_Ladder_Judge(1);	//年阶梯启动判断和数据合法性判断
	Price_Judge();		//费率阶梯电价判断
	Calc_Pwr_Proc();	//正反向电量累计处理和金额处理
	Init_Meter_Chip();	//初始化计量芯片
	Enable_Pulse(); //打开计量
	NVIC_ClearPendingIRQ(BT1_IRQn);
	NVIC_EnableIRQ(BT1_IRQn);	
	NVIC_ClearPendingIRQ(BT2_IRQn);
	NVIC_EnableIRQ(BT2_IRQn);
	if( esam_error ) EsamReset();	
	
	BLEPOWERON;		//打开蓝牙电源
	Ble_RstTimer = 5;	//延时5分钟查询蓝牙心跳
	
	Clear_Wdt();
	SynEe.Enable = 1; 	//启动一次同步EE
	SynEeprom(); 		//同步冻结到Flash
	
	Esam_Timer = 4;		//上电4秒后复位ESAM(等待电源更加稳定)
	Relay_Space_Timer = 2;	//启动2秒上电延时控制继电器定时器
	PowerDetCnt0 = 2;	//检测电源从2开始计数
	comm_relaystatus_flag = real_relaystatus_flag;//刷新继电器实际状态(通讯bit4专用)
	Commmodule_Space_Timer = 0x03;//启动模块更换去抖延时
	Veri_Sys_Reg();		//保证复用口线恢复正常
}


#if( NEWCLOCKADJ == 0 ) //旧标准时钟调校
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

float GetRtcRTrimVal( float AverADCf )//根据adc数据查表差值
{
	float Rtcadj = 0;
	float Fk;
	uint08 i;

	for(i=1; i<=20; i++)//温度区间判断
	{
		if(AverADCf < RTC_RT.TAdc.PTAT_Value[i])
		{
			break;
		}
	}

	//补偿值计算
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
	for(i=1;i<31;i++) //去掉最大值和最小值
	{
		temp +=	ADCResultArr.Buffer[i];
	}

  	if ( Type == 0 ) //PTAT 采集 
	{
		temp = temp/30.0;//获取平均值
		adctemp=0;	
		adcpcs=0;
		for(i=1;i<31;i++) //查找出Buffer[i]中高于ADC平均值的数
		{
			if( (ADCResultArr.Buffer[i]-temp)>6 || (temp-ADCResultArr.Buffer[i])>6 )
			{
				adctemp+=ADCResultArr.Buffer[i]; //将大于平均ADC值的Buffer[i]累加
				adcpcs=adcpcs+1;//记录大于平均ADC值的Buffer[i]的个数
			}
		}	
			
		if(adcpcs>1) //如果Buffer[i]的个数超过2个值，则返回的ADC值为0,不日记时不补偿
		{
			return 0; //出现异常数据返回0
		}
		else
		{
			TempADC=(temp*30.0-adctemp)/(30.0-adcpcs*1.0);
			return (TempADC);
		}				
	}
	else
	{
		return (temp/30.0); //测电池电压通道
	}
}
#endif

void Adc_Proc()		//电池和温度adc处理
{
	unsigned char i;
	signed char j;
 	float T25ADC,AverADCf;
 	float Fa,Fb,T,T25,Rtcadj,TopF_Rtc_Adj;
 	unsigned short Temp16;
 	unsigned char Result;
	signed char BufC[ee_temperature_lenth+2];
	
#if( NEWCLOCKADJ == 0 ) //旧标准时钟调校	
	if ( Adcctrl.Status == B0010_0000 )//温度adc数据处理,用于温度补偿
	{		
		Adcctrl.Status = 0;
		ADCResultArr.ReadCount = 0;
		AverADCf = GetADCResult();
		Temperature_Adc = (unsigned short)(AverADCf + 0.5);	//保存当前温度adc用于通讯抄读
		
		//0 高温温度斜率微调（暂不支持）
		//1 低温温度斜率微调（暂不支持）
		//2 高温晶体曲线微调（高温修调二次函数系数）x*0.0001 kh
		//3 低温晶体曲线微调（低温修调二次函数系数）x*0.0001 kl
		//4 常温顶点调校值修正值(±1.27ppm)	
		//5 常温温度ADC微调
		//6 常温顶点调校值L（通信调时钟误差）±327.68ppm
		//7 常温顶点调校值H（通信调时钟误差）
		//8 RTC补偿工作模式，0x55:测试模式，0xAA常温查表插值模式，其他：普通模式
		//9 常温25+晶体曲线微调（常温25+修调二次函数系数）x*0.0002 krh
		//10常温25-晶体曲线微调（常温25-修调二次函数系数）x*0.0002 krl
		memcpy( BufC, Tpara.Offset, ee_temperature_lenth );//复制温度系数				
		for( i=0; i<6; i++ ) //特殊输入转换成有符号数
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
			//使用温度定标数据
//			T25ADC = (const_adc_Test+(short)BufC[5]) - (const_temp_TestA+(float)(const_temp_TestB/0x80)*0.5-const_xtl_top)*const_TmpsH;//计算高低温曲线转折点的ADC值
			if( EA_OFF )
			{
//				T = T + const_T_OffsetSlp;
				T25ADC = (const_adc_Test+(short)BufC[5]) - (const_temp_TestA+(float)(const_temp_TestB/0x80)*0.5-const_xtl_top)*const_TmpsH - const_T_OffsetSlp*const_TmpsH;//计算高低温曲线转折点的ADC值
			}
			else
			{
//				T = T + const_T_OffsetRun;				
				T25ADC = (const_adc_Test+(short)BufC[5]) - (const_temp_TestA+(float)(const_temp_TestB/0x80)*0.5-const_xtl_top)*const_TmpsH - const_T_OffsetRun*const_TmpsH;//计算高低温曲线转折点的ADC值
			}		
		}
		else
		{
			//调试临时使用
			T25ADC = 1470 + (25 - const_xtl_top)*const_TmpsH;//调试用，后续需替换为温度定标数据
		}
		
		if( (SleepPtatOffsetCfg == 0x55)&&(EA_OFF) )//停电温度补偿启用3v offset
		{
			if( const_ptat_Offset3V <= 10 )
				T25ADC -= const_ptat_Offset3V;
			else
				T25ADC -= 5;
		}		
		
		T25 = const_xtl_top;
		if( const_tx_flag != 0x3cc3 )//通信校准时钟误差
		{
			TopF_Rtc_Adj = ((int16)((uint08)BufC[6]|((uint08)BufC[7]<<8)))/100.0;//缩小100倍
		}
		else			//调校仪校准时钟误差
		{
			TopF_Rtc_Adj = const_rtc_adj_top/100.0;//缩小100倍
		}		
					
		if( AverADCf > T25ADC )	//高温
 			Fa = const_TmpsH+0.05*BufC[0];
 		else
 			Fa = const_TmpsL+0.05*BufC[1];

		T = (AverADCf - T25ADC)/Fa + T25;

		//查表温度范围标志判断 0=常温，1=低温，2=高温
		if( T < 0 )
		{
			Result = 1;//低温查表
		}
		else if( T > 50 )
		{
			Result = 2;//高温查表
		}
		else
		{
			Result = 0;//常温查表
		}
		
		if( const_C_Mode != 0x55 )
		{
			RTC_RT.TempFlag = 0;
			RTC_RT.CFixTrim = TopF_Rtc_Adj;
		}
		else if( ((Tpara.RtcTMode == 0xAA)||(Tpara.RtcTMode == 0x55)) && (RTC_RT.TempFlag != Result) )//改变后重新校验温补参数
		{
			RTC_RT.TempFlag = Result;

			Fill_RTC_RT_TAdc();
			Fill_RTC_RT_TVal();
			
			if( RTC_RT.TempFlag == 0 )//常温查表
			{
				RTC_RT.CFixTrim = TopF_Rtc_Adj;
			}
			else if( RTC_RT.TempFlag == 1 )//低温查表
			{
				Fa = const_KL +0.0001*BufC[3];
				RTC_RT.CFixTrim = TopF_Rtc_Adj + (-1.0)*Fa*(const_T_CL-const_xtl_top)*(const_T_CL-const_xtl_top);//低温查表中心温度误差计算，ppm
			}
			else if( RTC_RT.TempFlag == 2 )//高温查表
			{
				Fa = const_KH +0.0001*BufC[2];
				RTC_RT.CFixTrim = TopF_Rtc_Adj + (-1.0)*Fa*(const_T_CH-const_xtl_top)*(const_T_CH-const_xtl_top);//高温查表中心温度误差计算，ppm
			}
		}
		
		if( (Tpara.RtcTMode == 0xAA)||(Tpara.RtcTMode == 0x55) )//常温查表插值模式,禁止krh，krl微调功能
		{
			BufC[9] = 0;
			BufC[10] = 0;	
		}		
 		if( AverADCf > T25ADC )	//高温
		{
			//避免kh，kl微调对常温产生影响
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
		
		Rtcadj_Offset = Fa*(T-const_xtl_top)*(T-const_xtl_top);//顶点误差计算，ppm
		Rtcadj_Offset2 = Fb*(T-const_xtl_top)*(T-const_xtl_top);//顶点误差计算，ppm，调校用
		
		//常温查表插值模式
		if( (Tpara.RtcTMode == 0xAA)&&( (AverADCf>RTC_RT.TAdc.PTAT_Value[0]) && (AverADCf<RTC_RT.TAdc.PTAT_Value[20]) ))//进入查表区域 
		{
			Rtcadj = GetRtcRTrimVal( AverADCf );
			//调整量*调整补偿 = 调整的ppm数
			Rtcadj = Rtcadj*0.23842;	//最小调整量为0.238ppm
			if( (const_mark404 == 0x0404)&&(RTC_Trim_Ctrl == 0x55) )
			{
				Rtcadj = Rtcadj/2.0;	//最小调整量为0.119ppm
			}
			Rtcadj = Rtcadj + ((short)BufC[4])/100.0 + RTC_RT.CFixTrim;
		}
		else if( (Tpara.RtcTMode == 0x55)&&progenable ) // 测试模式,使用固定调校值
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
		else if( (RtcStopProcFlag == 0x55)&&progenable )//通信校准时钟关闭补偿调顶点
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
			Rtcadj = Rtcadj*8.388608;//转换为调校值,0.119
		}
		else
		{
			Rtcadj = Rtcadj*4.194304;//转换为调校值,0.238
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
		
		if( T >= 0x00 )//计算当前温度
		{
			Temp16 = (unsigned short)(T*10);
			Hex2Bcd_SS( (unsigned char *)&Temp16, (unsigned char *)&Fun_Para.Temper_M, 2 );
		}
		else 
		{
			Temp16 = (unsigned short)(-T*10);
			Hex2Bcd_SS( (unsigned char *)&Temp16, (unsigned char *)&Fun_Para.Temper_M, 2 );
 			Fun_Para.Temper_M |= 0x8000;//最高位置1,表示负的温度			
		}

		if( EA_ON )//温度变化一定度数进行一次RC调校
		{
			j = (signed char)(T);

			if( Temperature_Hex > j )
			{
				if( (Temperature_Hex - j) >=5 )
				{
					Clk_Adj_Proc();	//根据外部的32K晶体来调整内部8M的偏差
					Temperature_Hex = j;
				}
			}
			else
			{
				if( (j - Temperature_Hex) >=5 )
				{
					Clk_Adj_Proc();	//根据外部的32K晶体来调整内部8M的偏差
					Temperature_Hex = j;
				}	
			}
		}
	}

	if ( Adcctrl.Status == B0001_0000 )//电池adc处理
	{	
		Adcctrl.Status = 0;
		ADCResultArr.ReadCount = 0;	
	
		if( (const_adc_Slope > 2000) && (const_adc_Slope < 2400) )
		{
			//使用成测数据	
			Fun_Para.Voltage_B = (GetADCResult()*(float)(const_adc_Slope/10000.0)+(float)const_adc_Offset/1000.0)*2+constF_Volt;		
		}
		else
		{
			//调试临时使用
			Fun_Para.Voltage_B = ((GetADCResult()-10)*0.2174)*2+constF_Volt;	
		}

		Hex2Bcd_SS( (unsigned char *)&Fun_Para.Voltage_B, (unsigned char *)&Fun_Para.Voltage_B, 2 );
		
#else
	static float  RTCadj_Mod=0;
	if ( Adcctrl.Status == B0010_0000 )//温度adc数据处理,用于温度补偿
	{		
		Adcctrl.Status = 0;	//为满足ADC采样算法，先采集ADC值再将状态标志位清0
		ADCResultArr.ReadCount = 0;
		AverADCf = GetADCResult(0);

		if(AverADCf <= const_adc_Min) //判断ADC是否异常,不再进行温度补偿
		{
			return;
		}
		
		Temperature_Adc =(unsigned short)(AverADCf*10); //保存当前温度adc用于通讯抄读,显示1位小数,提高拟合精度  上位机需要做数据处理/10  
		
		//0 高温温度斜率微调（暂不支持）
		//1 低温温度斜率微调（暂不支持）
		//2 高温晶体曲线微调（高温修调二次函数系数）x*0.0001 kh
		//3 低温晶体曲线微调（低温修调二次函数系数）x*0.0001 kl
		//4 常温顶点调校值修正值(±1.27ppm)	
		//5 常温温度ADC微调
		//6 常温顶点调校值L（通信调时钟误差）±327.68ppm
		//7 常温顶点调校值H（通信调时钟误差）
		//8 RTC补偿工作模式，0x55:测试模式，0xAA常温查表插值模式，其他：普通模式
		//9 高温顶点调校值修正值(ppm)
		//10低温顶点调校值修正值(ppm)
		memcpy( BufC, Tpara.Offset, ee_temperature_lenth );//复制温度系数				
		for( i=0; i<6; i++ ) //特殊输入转换成有符号数
		{
			Result = (unsigned char)(BufC[i]);
			if( Result&0x80 ) BufC[i] = ((~Result)|0x80)+1;
		}
		Result = (unsigned char)(BufC[9]);
		if( Result&0x80 ) BufC[9] = ((~Result)|0x80)+1;
		Result = (unsigned char)(BufC[10]);
		if( Result&0x80 ) BufC[10] = ((~Result)|0x80)+1;
	
//**********************根据温度定标值计算25℃对应的ADC值****************************	//			
		if( const_temp_TestA == 0x1E )//使用温度定标数据
		{			
			if( EA_OFF )
			{
				T25ADC = (const_adc_Test+(short)BufC[5]) - (const_temp_TestA+(float)(const_temp_TestB/0x80)*0.5-const_xtl_top)*const_TmpsH - const_T_OffsetSlp*const_TmpsH;//计算高低温曲线转折点的ADC值
			}
			else
			{		
				T25ADC = (const_adc_Test+(short)BufC[5]) - (const_temp_TestA+(float)(const_temp_TestB/0x80)*0.5-const_xtl_top)*const_TmpsH - const_T_OffsetRun*const_TmpsH;//计算高低温曲线转折点的ADC值
			}		
		}
		else //调试临时使用，芯片未进行温度定标
		{
			
			T25ADC = 1470 + (25 - const_xtl_top)*const_TmpsH;//调试用，后续需替换为温度定标数据
		}
		
		if( (SleepPtatOffsetCfg == 0x55)&&(EA_OFF) )//停电温度补偿启用3v offset
		{
			if( const_ptat_Offset3V <= 10 )
				T25ADC -= const_ptat_Offset3V;
			else
				T25ADC -= 5;
		}

		
//**********************485通讯日计时调校或编程器调校****************************	//	
		T25 = const_xtl_top;
		if( const_tx_flag != 0x3cc3 )//通信校准时钟误差
		{
			TopF_Rtc_Adj = ((int16)((uint08)BufC[6]|((uint08)BufC[7]<<8)))/100.0;//缩小100倍
		}
		else			//调校仪校准时钟误差，芯片如果使用编程器调校后就不能进行485调校
		{
			TopF_Rtc_Adj = const_rtc_adj_top/100.0;//缩小100倍
		}		
		
/**************************计算当前表内温度，并判断当前模式******************************************/				
		T = (AverADCf - T25ADC)/const_TmpsH + T25;
		
/**************************普通模式下 KH和KL修正*****************************************/			
 		if( AverADCf > T25ADC )	//高温 //避免kh，kl微调对常温产生影响
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
		
		Rtcadj_Offset = Fa*(T-const_xtl_top)*(T-const_xtl_top);//顶点误差计算，ppm
		Rtcadj_Offset2 = Fb*(T-const_xtl_top)*(T-const_xtl_top);//顶点误差计算，ppm，调校用
		
/**************************使用ADC拟合晶体误差补偿参数*****************************************/	
		if( Tpara.RtcTMode == 0xAA)//进入查表区域 
		{
			float K_3;//温度补偿三阶经验系数
			float K_2;//温度补偿二阶经验系数
			float K_1;//温度补偿一阶经验系数
			float K_0;//温度补偿零阶经验系数
			
			K_3 = (float)((float)RTC_RT.TAdc.PTAT_Value[0]/1000+(float)RTC_RT.TAdc.PTAT_Value[1]/10000000 + (float)RTC_RT.TAdc.PTAT_Value[2]/100000000000);		//3次系数					
			K_2 = (float)((float)RTC_RT.TAdc.PTAT_Value[3]/1000+(float)RTC_RT.TAdc.PTAT_Value[4]/10000000 + (float)RTC_RT.TAdc.PTAT_Value[5]/100000000000);		//2次系数		
			K_1 = (float)((float)RTC_RT.TAdc.PTAT_Value[6]/1000+(float)RTC_RT.TAdc.PTAT_Value[7]/10000000 + (float)RTC_RT.TAdc.PTAT_Value[8]/100000000000);		//1次系数				
			K_0 = (float)(((float)RTC_RT.TAdc.PTAT_Value[9])*10+((float)RTC_RT.TAdc.PTAT_Value[10])/1000 + ((float)RTC_RT.TAdc.PTAT_Value[11])/10000000);				//0次系数	
		
			 if((RTC_RT.TAdc.PTAT_Value[16] & BIT0)==0X01)
			 {
				 K_3 = - K_3; //系数取反
			 }
			 if((RTC_RT.TAdc.PTAT_Value[16] & BIT1)==0X02)
			 {
				 K_2 = - K_2; //系数取反
			 }			

			 if((RTC_RT.TAdc.PTAT_Value[16] & BIT2)==0X04)
			 {
				 K_1 = - K_1; //系数取反
			 }				 

			 if((RTC_RT.TAdc.PTAT_Value[16] & BIT3)==0X08)
			 {
				 K_0 = - K_0; //系数取反
			 }		
		 			
						
			 if(RTC_RT.TVal.Trim_Value[0] ==1)//经过高温恢复天数(用户根据自己硬件设置经验天数)+年+月+日+ 偏移值*0.01(用户根据电表实际偏移值设置)
			 {
				 unsigned char Dtemperature;
							
				 Dtemperature=((RTC->BCDYEAR/16*10+RTC->BCDYEAR%16)-(RTC_RT.TVal.Trim_Value[2]))*365 + ((RTC->BCDMONTH/16*10+RTC->BCDMONTH%16)-(RTC_RT.TVal.Trim_Value[3]))*30 + (RTC->BCDDATE/16*10+RTC->BCDDATE%16)-(RTC_RT.TVal.Trim_Value[4]);
				 if(Dtemperature<RTC_RT.TVal.Trim_Value[1])//当经过高温后,只需补偿在常温下误差即可
				 {
					Rtcadj  =  (K_3*AverADCf*AverADCf*AverADCf/1000000 + K_2*AverADCf*AverADCf/100 + K_1*10*AverADCf + K_0)+(RTC_RT.TVal.Trim_Value[5]*0.01);//经过高温误差会偏大，故需要减去偏大值	
				 }
				 else
				 {
					Rtcadj  =  K_3*AverADCf*AverADCf*AverADCf/1000000 + K_2*AverADCf*AverADCf/100 + K_1*10*AverADCf + K_0;	
				 }
			 }
			 else //没有经过高温
			 {
				Rtcadj  =  K_3*AverADCf*AverADCf*AverADCf/1000000 + K_2*AverADCf*AverADCf/100 + K_1*10*AverADCf + K_0;	
			 } 
			
		}
		
		else if( Tpara.RtcTMode == 0x55) // 测试模式下发原始误差值，验证下发的误差值是否正确
		{			
			Rtcadj = (float)RTC_RT.TestTrim/100; //原始误差以放大100倍的形式进行下发。
		}		
		else if( (RtcStopProcFlag == 0x55)&&progenable )//通信校准时钟关闭补偿调顶点
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

/**************************高低温误差单独微调****************************************/		
		if( T < -15 )
		{
			Rtcadj = Rtcadj+((short)BufC[10])/100.0;//低温修正
		}
		else if( T > 45 )
		{
			Rtcadj = Rtcadj+((short)BufC[9])/100.0;//高温修正
		}
		else
		{
			Rtcadj = Rtcadj+((short)BufC[4])/100.0;//常温修正
		}	
	
/**************************将上面Rtcadj(单位PPM)转换成调校值**************************************/				
		if( (RTC_Trim_Ctrl == 0x55)&&(const_mark404 == 0x0404) )
		{
			Rtcadj = Rtcadj*8.388608;//转换为调校值,0.119
		}
		else
		{
			Rtcadj = Rtcadj*4.194304;//转换为调校值,0.238
		}

/**************************RTC补偿 调校值余数RtcADJ_Offset累加到1后RTC->ADJUST增加1*************************************/				
		if( Rtcadj >= 0 ) 
		{	
			RTC->ADSIGN = 0x00;			
			RTCadj_Mod =RTCadj_Mod+(Rtcadj-((uint32)(Rtcadj)));	//	求出转换为调校值的余数		
			if(RTCadj_Mod>=1)//判断RTC补偿值小数位累加积累到1，例如RTC->ADJUST =10.21 只能写10   0.21会被舍弃，通过累加的余数满足1后RTC->ADJUST补偿值多加上1
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
			if(RTCadj_Mod >=1)//判断RTC补偿值小数位累加积累到1，例如RTC->ADJUST =10.21 只能写10   0.21会被舍弃，通过累加的余数满足1后RTC->ADJUST补偿值多加上1
			{
				RTC->ADJUST = ((uint32)(Rtcadj)*(-1.0))+1;		
				RTCadj_Mod	=RTCadj_Mod-1;
			}else
			{
				RTC->ADJUST = (uint32)(Rtcadj)*(-1.0);			
			}							
		}           	
		
		if( T >= 0x00 )//计算当前温度
		{
			Temp16 = (unsigned short)(T*10);
			Hex2Bcd_SS( (unsigned char *)&Temp16, (unsigned char *)&Fun_Para.Temper_M, 2 );
		}
		else 
		{
			Temp16 = (unsigned short)(-T*10);
			Hex2Bcd_SS( (unsigned char *)&Temp16, (unsigned char *)&Fun_Para.Temper_M, 2 );
 			Fun_Para.Temper_M |= 0x8000;//最高位置1,表示负的温度			
		}

		if( EA_ON )//温度变化一定度数进行一次RC调校
		{
			j = (signed char)(T);

			if( Temperature_Hex > j )
			{
				if( (Temperature_Hex - j) >=5 )
				{
					Clk_Adj_Proc();	//根据外部的32K晶体来调整内部8M的偏差
					Temperature_Hex = j;
				}
			}
			else
			{
				if( (j - Temperature_Hex) >=5 )
				{
					Clk_Adj_Proc();	//根据外部的32K晶体来调整内部8M的偏差
					Temperature_Hex = j;
				}	
			}
		}
	}

	if ( Adcctrl.Status == B0001_0000 )//电池adc处理
	{	
		Adcctrl.Status = 0;
		ADCResultArr.ReadCount = 0;	
	
		if( (const_adc_Slope > 2000) && (const_adc_Slope < 2400) )
		{
			//使用成测数据	
			Fun_Para.Voltage_B = (GetADCResult(1)*(float)(const_adc_Slope/10000.0)+(float)const_adc_Offset/1000.0)*2+constF_Volt;		
		}
		else
		{
			//调试临时使用
			Fun_Para.Voltage_B = ((GetADCResult(1)-10)*0.2174)*2+constF_Volt;	
		}

		Hex2Bcd_SS( (unsigned char *)&Fun_Para.Voltage_B, (unsigned char *)&Fun_Para.Voltage_B, 2 );
#endif		
		if( EA_OFF ) return;
		
		if( Fun_Para.Voltage_B < Def_Vthreshold )	//电池低于欠压阀值，且延时60s后做电池欠压记录
		{
			if( low_voltage_flag == 0 )
			{
				if( Bat_Delay_Timer < 0x05 ) 	//每10秒处理一次
					Bat_Delay_Timer += 0x01;
				else
				{
					low_voltage_flag = 1; //电池低压标志
					change_batt_flag = 1; //允许电池更换标志
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
				if( Bat_Change_Timer==0 ) Bat_Change_Timer = 0x02; //每10秒处理一次
				if( Bat_Change_Timer  )
				{
//					if( Bat_Change_Timer == 0x03 ) //提前30s记录发生
//					{
//						if( RdRecTimes(ee_batchangen_inpage) )
//						{
//							unsigned char  Temp08, BufA[ee_batchangenote_len];
//							
//							Temp08 = Read_Event_Point(ee_batchangen_inpage);
//							I2C_Read_Eeprom( ee_batchange_note_page+Temp08, ee_batchangenote_inpage, BufA, ee_batchangenote_len );	//时间  
//							Temp08 =ChkBufZero(BufA+6,6);
//							if( Temp08 == 1 )	//上一次电池更换有结束时间才开新的电池更换记录
//							{
//								Note_Run_Event( ee_batchangen_inpage ); //电池更换发生事件    
//							}   
//						}
//						else  Note_Run_Event( ee_batchangen_inpage ); //电池更换发生事件              
//					}
					
					Bat_Change_Timer --;
					if( Bat_Change_Timer == 0x00 )
					{
						Note_Run_Event( ee_batchangen_inpage ); //电池更换发生事件  
						change_batt_flag = 0;
						Store_Meterstatus();
						Note_Run_Event( ee_batchangen_inpage|0x80 );	//电池更换结束事件
					}
				}
			}
		}
		
		
		if( constF_Volt && (Fun_Para.Voltage_B>0x368) )  Fun_Para.Voltage_B = 0x368; //果最终电池电压超过3.68就强制为3.68
		if( Fun_Para.Voltage_B < 0x80 ) Fun_Para.Voltage_B = 0; //电压低于0.8V强制归零
	}
}
