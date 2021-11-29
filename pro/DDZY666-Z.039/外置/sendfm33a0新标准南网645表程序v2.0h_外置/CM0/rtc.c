//RTC function
#include "ex_var.h"
#include "ex_func.h"
#include <string.h>
#include "FM32L0XX.h"  
#include "Cpu_card.h"


int32 Byte2Int(uint08* byte)
{
	return (int32)(byte[3]+((uint32)byte[2]<<8) + ((uint32)byte[1]<<16) +((uint32)byte[0]<<24)) ;
}
int16 Byte2Short(uint08* byte)
{
	return (int16)(byte[1])+((uint16)byte[0]<<8);
}
uint32 Byte2uInt(uint08* byte)
{
	return byte[3]+((uint32)byte[2]<<8) + ((uint32)byte[1]<<16) +((uint32)byte[0]<<24) ;
}
uint16 Byte2uShort(uint08* byte)
{
	return byte[1]+((uint16)byte[0]<<8);
}
void Int2Byte(uint32 datatemp,uint08* Buff)
{
	Buff[3] = datatemp ;
	Buff[2] = (datatemp>>8) ;
	Buff[1] = (datatemp>>16) ;
	Buff[0] = (datatemp>>24) ;
}
void Short2Byte(uint16 datatemp,uint08* Buff)
{
	Buff[1] = datatemp ;
	Buff[0] = (datatemp>>8) ;
}

/*============================================================================*
	函数：	unsigned char Add_Bcd_1(unsigned char n,unsigned char m,unsigned char *carry)
	功能：	单字节的BCD码加法。
	参数：	m——加数；
			n——被加数。
  返回值:	n——加完后的结果。向上一高字节进位标志放在了carry中
*============================================================================*/	
unsigned char Add_Bcd_1(unsigned char n,unsigned char m,unsigned char *carry)	
{
	unsigned char i,j,w;
	m=m+(*carry);
	*carry=0;
	j=n&0x0f;
	i=m&0x0f;
	i+=j;
	w=0;
	if(i>9)
	{
		w=0x01;
		i-=10;
	}
	j=n;
	j>>=4;		
	m>>=4;
	j=j+m+w;
	if(j>0x09)
	{
		j-=10;
		j<<=4;
		n=j+i;
		*carry=1;
		return(n);
	}
	j<<=4;
	n=j+i;
	*carry=0;
	return(n);
}

/*============================================================================*
	函数：	void Add_Bcd( unsigned char *BufA, unsigned char *BufB, unsigned char Len )
	功能：	Len字节BCD码加法
	参数：	*BufA 被加数    *BufB 加数  *BufA=*BufA+*BufB
	        向上一高字节进位标志放在了bf_carry中
  返回值:	无
*============================================================================*/	
void Add_Bcd( unsigned char *BufA, unsigned char *BufB, unsigned char Len )
{
	unsigned char i;
	unsigned char bf_carry;
	bf_carry=0;
	for(i=(Len-1);i<Len;i--)
	{
		BufA[i]=Add_Bcd_1(BufA[i],BufB[i],&bf_carry);
	}
	return;
}

/*============================================================================*
	函数：	unsigned char Bcdsub_4(unsigned char *,unsigned char *,unsigned char *)
	功能：	4字节BCD码减法
	参数：	*BufB 减数  *BufA 被减数    *sub=*BufA-*BufB
	        向上一高字节进位标志放在了bf_carry中
  返回值:	无
*============================================================================*/	
void Sub_Bcd( unsigned char *BufA, unsigned char *BufB, unsigned char Len )
{
	unsigned char i,j,k;
	unsigned char bf_carry;
	bf_carry=0;
	for(i=(Len-1);i<Len;i--)
	{
		j=BufB[i]+bf_carry;
		k=0;
		if(j<BufB[i])
			k=1;									
		bf_carry=0;
		if((BufA[i]&0x0f)<(j&0x0f))
		{
			if(BufA[i]<j)
			{
				BufA[i]=0x9a-j+BufA[i];			//0xa0-6;
	           		bf_carry=1;
	        	}
			else
				BufA[i]=BufA[i]-j-6;
		}
		else
		{
			if(BufA[i]<j)
			{
				BufA[i]=0xa0-j+BufA[i];
	            		bf_carry=1;
	        	}
			else
				BufA[i]=BufA[i]-j;
		}
		if(k)
			bf_carry=1;		//由于k=1时，不会产生借位
	}
	return;
}
/*============================================================================*
	函数：	void Hex2Bcd( unsigned char *Hexop, unsigned char *BCDopt, unsigned char Len );
	功能：	多字节HEX转换BCD
	参数：	*Hexop  HEX 初始值为待转化的高字节地址； 
			*BCDopt  BCD 初始值为待转化的高字节地址； 
			Len  长度，最大4个字节
  返回值:	无
*============================================================================*/	
void Hex2Bcd( unsigned char *Hexop, unsigned char *BCDopt, unsigned char Len )
{	
	unsigned char i,m;
	unsigned long long hex_temp;
	unsigned char code temp1[8]={0,8,16,24,32,40,48,56};
	
	if(Len>8)
		return;
	hex_temp=0;
	for(i=0;i<Len;i++)
	{
		hex_temp+=(unsigned long long)((unsigned long long)Hexop[i]<<temp1[Len-1-i]);		
	}
	
	for(i=0; i<Len;i++)
	{
		m = (unsigned char)(hex_temp % 100);
		BCDopt[Len-1-i]=Hex_To_Bcd(m);							//转换为BCD格式
		hex_temp/=100;
	}
	return;
}
void Hex2Bcd_SS( unsigned char *Hexop, unsigned char *BCDopt, unsigned char Len )		//小端Hex变成小端BCD
{	
	uint8_t Buff[8];
	
	Exchange(Buff,Hexop,Len);
	Hex2Bcd(Buff,BCDopt,Len);
	Inverse(BCDopt,Len);
	return;
}
//void Hex2Bcd_LS( unsigned char *Hexop, unsigned char *BCDopt, unsigned char Len )		//大端Hex变成小端BCD
//{	
//	Hex2Bcd( Hexop, BCDopt, Len );
//	Inverse( BCDopt, Len );
//	return;
//}
/*==========================================================================*/
/*============================================================================*
	函数：	void Bcd2Hex( uint08 *BCDopt, uint08 *HEXopt, uint08 Len );
	功能：	多字节BCD转换HEX
	参数：	*BCDopt  BCD 初始值为待转化的高字节地址； 
			*HEXopt  HEX 初始值为待转化的高字节地址；
			Len  长度，最大4个字节
  返回值:	无
*============================================================================*/	
void Bcd2Hex( unsigned char *BCDopt, unsigned char *HEXopt, unsigned char Len )
{	
	unsigned long long hex_temp;
	unsigned long long code temp0[8]={1,100,10000,1000000,100000000,10000000000,1000000000000,100000000000000};	
	unsigned char code temp1[8]={0,8,16,24,32,40,48,56};
	unsigned char i;
	if(Len>8)
		return;
	hex_temp=0;
	for(i=0;i<Len;i++)
	{
		hex_temp+=(unsigned long long)(Bcd_To_Hex(BCDopt[Len-1-i]))*temp0[i];		
	}
	for(i=0;i<Len;i++)
	{
		HEXopt[Len-1-i]=(unsigned char)(hex_temp>>temp1[i]);
	}	
	return;
}
void Bcd2Hex_LS( unsigned char *BCDopt, unsigned char *HEXopt, unsigned char Len )		//大端Bcd变成小端Hex
{	
	Bcd2Hex( BCDopt, HEXopt, Len );
	Inverse( HEXopt, Len );
	return;
}
void Bcd2Hex_SS( unsigned char *BCDopt, unsigned char *HEXopt, unsigned char Len )		//小端Hex变成小端BCD
{	
	uint8_t Buff[8];
	
	Exchange(Buff,BCDopt,Len);
	Bcd2Hex( Buff, HEXopt, Len );
	Inverse( HEXopt, Len );
	return;
}
//============================================================================
unsigned char Hex_To_Bcd( unsigned char value )
{
	return ( ((value/10)<<4)+(value%10) );
}

unsigned char Bcd_To_Hex( unsigned char value )
{
	return ( ((value&0xF0)>>4)*10+(value&0x0F) );
}

//============================================================================
unsigned char ChkBufZero( unsigned char *Buf,unsigned char Len )
{
	unsigned char i;
	
	for( i=0; i<Len; i++ )
	{
		if( Buf[i] )	return(1);	//非0
	}
	
	return(0);	//全0
}


//高字节在前的数据比较
unsigned char Cmp_Data( unsigned char *BufA, unsigned char *BufB, unsigned char Len )
{
	unsigned char i;

	for( i=0; i<Len; i++ )
	{
		if( BufA[i] > BufB[i] )
		{
			return 1; //A>B
		}
		else
		{
			if( BufA[i] < BufB[i] )
			{
				return 2; //A<B
			}
		}
	}

	return 3; //A=B
}

//低字节在前的数据比较
unsigned char Cmp_Bcd_Inv( uint08 *BcdA, uint08 *BcdB, uint08 Len )
//return: 0-A=B; 1:A>B; 2:A<B
{
	unsigned char i;

	for( i=0; i<Len; i++ )
	{
		if( BcdA[Len-1-i] > BcdB[Len-1-i] )
		{
			return 1; //A > B
		}
		else
		{
			if( BcdA[Len-1-i] < BcdB[Len-1-i] )
			{
				return 2; //A < B
			}
		}
	}

	return 0; //A==B
}

//============================================================================
//分钟为起始字节的时钟比较程序
unsigned char Cmp_Clock( unsigned char *Buf, unsigned char Len )
{
	unsigned char i;
	
	for( i=0; i<Len; i++ )
	{
		if( Buf[ i ] > Sclock.Clockbackup[ Len-i ] )
		{
			return 1; //大于当前时间
		}
		else
		{
			if( Buf[ i ] < Sclock.Clockbackup[ Len-i ] )
			{
				return 2; //小于当前时间
			}
		}
	}

	return 3; //相等
}

const uint08 code MaxDays []={0x31,0x28,0x31,0x30,0x31,0x30,0x31,0x31,0x30,0x31,0x30,0x31};
uint08 Judge_Clock( uint08 Start, uint08 *Ck, uint08 Len )//周在中间
{
	unsigned char  i, j, k=0;
	const uint08 code Max[]={ 0x59,0x59,0x23,0x6,0x31,0x12,0x99 }, code Min[]={ 0x00,0x00,0x00,0x00,0x01,0x01,0x00 };

	if( (Len&0x80) == 0 ) k = 1;	//有周
		
	for( i=0; i<(Len&0x07f); i++ )
	{
		j=i+Start;
		if((j>=3)&&(Len&0x80))	j++;
		
		if( (Ck[i] > Max[j]) || (Ck[i] < Min[j]) ) return 1;//合法性检查错误
		if( IsBCD(Ck[i]) ) return 1;	//BCD码检查错误		  
		
		if( (j == 4) && ((Start+(Len&0x07f)) > (4+k)) ) //Day
		{
			if( (Ck[i+1] == 0x02) && ((Start+(Len&0x07f)) > (5+k)) ) //Month
			{
				if( (Bcd_To_Hex(Ck[i+2])&0x03) == 0 ) //闰年Year
				{
					if( Ck[i] > 0x29 ) return 1;
				}
				else
				{
					if( Ck[i] > 0x28 ) return 1;
				}
			}
			else
			{
				if( Ck[i] > MaxDays[Bcd_To_Hex(Ck[i+1])-1] ) return 1;
			}
		}
	}
	return 0;//正确
}


unsigned char JudgeClockNoWeek( uint08 Start, uint08 *Ck, uint08 Len )
{
	return(Judge_Clock( Start, Ck, Len+0x80 ));
}


unsigned char Read_Rtc( unsigned char *RTC_Buf )
{
	unsigned char i, n, Result;
	unsigned char BufA[7], BufB[7];

	for( n=0; n<3; n++ )
	{
		BufA[0] = RTC->BCDSEC;
		BufA[1] = RTC->BCDMIN;
		BufA[2] = RTC->BCDHOUR;
		BufA[3] = RTC->BCDWEEK;
		BufA[4] = RTC->BCDDATE;
		BufA[5] = RTC->BCDMONTH;
		BufA[6] = RTC->BCDYEAR;

		BufB[0] = RTC->BCDSEC;
		BufB[1] = RTC->BCDMIN;
		BufB[2] = RTC->BCDHOUR;
		BufB[3] = RTC->BCDWEEK;
		BufB[4] = RTC->BCDDATE;
		BufB[5] = RTC->BCDMONTH;
		BufB[6] = RTC->BCDYEAR;

		for( i=0; i<7; i++ ) //比对两次时钟是否一致
		{
			if( BufA[i] != BufB[i] ) break;
		}

		if( i == 7 ) //两者一致, 表示读取成功
		{
			Result = Judge_Clock( 0, BufA, 7 ); //判断时钟是否合法
			if( Result == 0 ) //时钟合法
			{
				for( i=0; i<7; i++ )
				{
					RTC_Buf[i] = BufA[i];
				}
			
				return 0;
			}
		}
	}
	
	for( i=0; i<7; i++ )
	{
		RTC_Buf[i] = BufA[i];//即使错误也要更新时钟
	}
	return 1;
}

#define RTC_WRITR_PROTECT_WORD  						((uint32_t)0x53535353)
#define RTC_WRITR_UNPROTECT_WORD  						((uint32_t)0xACACACAC)
unsigned char Set_Rtc( unsigned char Start, unsigned char *Ck, unsigned char Len )
{
	unsigned char i, n, Result;
	unsigned char BufB[7];
	
	if( Start || (Len!=7) ) return 1; //入口参数非法

	Result = Judge_Clock( Start, Ck, Len );
	if( Result == 1 )
	{
		return 1;
	}

//	if( Len < 7 )
//	{
//		Result = Read_Rtc( BufA );
//		if( Result == 1 )
//		{
//			return 1;
//		}
//	}
//
//	for( i=0; i<Len; i++ )
//	{
//		BufA[ Start+i ] = Ck[i];
//	}

	for( n=0; n<3; n++ )
	{
		RTC->RTCWE = RTC_WRITR_UNPROTECT_WORD;
		
		RTC->BCDSEC 	= Ck[0];
		RTC->BCDMIN 	= Ck[1];
		RTC->BCDHOUR	= Ck[2];
		RTC->BCDWEEK	= Ck[3];
		RTC->BCDDATE	= Ck[4];
		RTC->BCDMONTH	= Ck[5];
		RTC->BCDYEAR	= Ck[6];
		
		RTC->RTCWE = RTC_WRITR_PROTECT_WORD;

//		I2c_Wait_5ms();//RTC有一个5拍的滤波，在此之前读时钟会取消置数
//		if( (RTCSTAT&1) == 1 )  //加载成功
		{
			Result = Read_Rtc( BufB );
			if( Result == 0 ) //读取成功
			{
				for( i=0; i<7; i++ )
				{
					if( Ck[i] != BufB[i] ) break;
				}

				if( i == 7 ) //当前值和设置值相等, 设置成功
				{
					return 0; //设置成功
				}
			}
		}
	}

	return 1; //设置失败
}


void Syn_Clock( void )	//同步主和备份时钟
{
	Sclock.Clockbackup[0] = Sclock.Clockmain[0];//周由中间存放到最后
	Sclock.Clockbackup[1] = Sclock.Clockmain[1];
	Sclock.Clockbackup[2] = Sclock.Clockmain[2];
	Sclock.Clockbackup[3] = Sclock.Clockmain[4];
	Sclock.Clockbackup[4] = Sclock.Clockmain[5];
	Sclock.Clockbackup[5] = Sclock.Clockmain[6];
	Sclock.Clockbackup[6] = Sclock.Clockmain[3];
}


void Read_Sysclock( void )
{
	unsigned char Result,Buf[10];
	#if(1 == CHINT_Mode)
	uint32 V_ulDataBuf;
	#endif

	run_readrtc_flag = 0;	//清刷新时钟标志 
	
	Result = Read_Rtc( Sclock.Clockmain );//读时钟
	if( Result == 1 )
	{
		I2c_Wait_5ms(); 	//延时
		Result = Read_Rtc( Sclock.Clockmain );//再读时钟
		if( Result == 1 )
		{
			if( EA_OFF ) return;		//上电或者掉电时钟错误则直接返回
			if( clock_error == 0 ) 
			{
				clock_error = 1;//置时钟错误标志
				memcpy( Buf, Sclock.Clockbackup, 3 );
				Buf[3] = Sclock.Clockbackup[6];
				memcpy( Buf+4, Sclock.Clockbackup+3, 3 );
				Set_Rtc( 0, Buf, 7 );//把ram里正确的时钟写回rtc
				
//				Syn_Clock();//同步主和备份时钟	
				if( ChkLastclockerrRcdTime() != 1 ) Note_Run_Event(ee_clockerrn_inpage); //时钟故障开始记录(时钟非法)
				return;
			}
		}
	}
	if( Result == 0 )
	{
		if( clock_error )
		{
			clock_error = 0;//清时钟错误标志
			Syn_Clock();//同步主和备份时钟	
//			Note_Run_Event(ee_clockerrn_inpage|0x80);		//时钟故障结束记录(时钟合法)
			return;
		}
	}
		
	if( EA_ON )
	{	
		if ( Sclock.Clockbackup[0] != Sclock.Clockmain[0] )//秒改变
		{
			read_back_flag = 1;//每秒读一次7051的反向标志
			read_uip_flag1 = 1;
			
//			if( Sclock.Clockmain[0]&B0000_0001 ) read_uip_flag1 =1;		//每秒交替读取I1,I2,U (80ms)
			if( Sclock.Clockmain[0] == 0x05 ) fwdl_veri_flag = 1;		//正向电量校验
			if( Sclock.Clockmain[0] == 0x10 ) bkdl_veri_flag = 1;		//反向电量校验
			if( Sclock.Clockmain[0] == 0x15 ) rpdl_veri_flag = 1;		//无功电量校验
			if( Sclock.Clockmain[0] == 0x20 ) mode_veri_flag = 1;		//特征模式字校验
			if( Sclock.Clockmain[0] == 0x25 ) reg_veri_flag = 1;		//寄存器校验
			if( Sclock.Clockmain[0] == 0x30 ) addr_veri_flag = 1;		//通讯地址校验
			if( Sclock.Clockmain[0] == 0x35 ) disppm_veri_flag = 1;		//显示参数校验
			if( Sclock.Clockmain[0] == 0x40 ) dispitem_veri_flag = 1;	//显示项目校验
			
			if( Sclock.Clockmain[0] == 0x42) init_7051_flag1 = 1;		//初始化寄存器
			if( Sclock.Clockmain[0] == 0x46) check_7051_flag1 = 1;		//校验校表寄存器
			if( Sclock.Clockmain[0] == 0x55) temperpara_veri_flag = 1;	//温度系数校验
			
			//ESAM上电复位
			if(Esam_Timer) 
			{
				Esam_Timer--;
				if(Esam_Timer == 0) 
				{
					if((identity_prog_flag == 0) && (identity_ir_flag == 0))
					{
						EsamReset();//安全认证编程标志失效
					}
					UpdateEsamKey(); //更新密钥到ESAM
				}
			}
//			else
//			{
//				U7816CTRL0 &= B1101_1111;	//关闭u7816CLK
//			}
			
			//关闭载波复位和事件上报功能
			if( ChkBufZero( Report_Data, 5 ) && ((Mode.Feature1&0x0c)!=0x08) ) //主动上报未开启,则EVENOUT有效
			{
				EVENOUTON;		//事件上报
			}
			else
			{
				EVENOUTOFF;		//无事件上报输出低
			}
			
			//身份认证时效
			if( Identitytimer != 0 )
			{
				Identitytimer--;
	
				if( Identitytimer == 0 )
				{
					Clear_Rand_Gene();
					FailKey();	//更新密钥失败处理
				}	
			}
			
			//跳闸延时时间
			if( Opendelaytimer != 0 ) //继电器跳闸延时
			{
				Opendelaytimer--;
				if( Opendelaytimer == 0 ) run_alarm_flag = 1;	//延时到置标志
			}
						
			Judge_Relay_Delay();	//大电流延时跳闸判断
		 	if( relay_delay_flag )
		 	{
		 		CurrentTimer--; //大电流延时拉闸定时器减1
		 		if( CurrentTimer == 0 ) run_alarm_flag = 1;	//延时到置标志
		 	}
			
			//红外认证时效
			if( IR_EnTimer )
			{
				IR_EnTimer--;
				if( IR_EnTimer == 0 ) identity_ir_flag = 0;	//清红外请求标志
			}
			
			//上报自动复位时间
			if( Reset_Rep_Timer )
			{
				Reset_Rep_Timer--;	//上报复位定时器减1
				
				if( Reset_Rep_Timer == 0 )
				{
					Xor_Data( Report_Data, Report_Data2, 5 );//保留30min内新的上报
					memset( Report_Data2, 0x00, 5 );//上报状态字备份清零
					for( Result=0; Result<5; Result++ ) Clr_Reportnum(Result);//清零新增上报次数
				}
			}			
			
//			//预跳闸延时
//			if( CloseDelayTimer != 0 )	//预跳闸延时定时器
//		 	{
//		 		CloseDelayTimer--;
//		 		if( CloseDelayTimer == 0 )
//		 		{
//		 			Last_Timer = 0;	//清预跳闸延时时间
//		 			run_alarm_flag = 1;	//延时到置标志
//		 		}
//		 	}
		 	
		 	//空闲时esam电源关闭
		 	if( EsamPowerOff_Ctrl == 0x55 )
			{
				if((identity_prog_flag == 0) && (identity_ir_flag == 0))
				{
					CloseEsam();//释放ESAM
				}
			}
			
			//空闲时flash电源关闭
		 	if( FlashPowerOff_Ctrl == 0x55 )
		 	{
			 	if( FlashTimer )
				{
					FlashTimer--;
					if( FlashTimer == 0 )
					{
						if( FLASHVCC_N ) CloseFlash();	//关闭flash电源
					}
				}
			}
		 				
			//定时8M时钟调校功能(计量uart专用)
			if( Adj_Clk_Timer_S )
			{
				Adj_Clk_Timer_S--;	//定时8M时钟调校定时器减1s
				if( Adj_Clk_Timer_S == 0 )  Clk_Adj_Proc();//根据外部的32K晶体来调整内部8M的偏差
			}
			if( Adj_Clk_Timer_S == 0 ) Adj_Clk_Timer_S = Adjclk_timer_delay_s;

			//扩展功能
			if( (Key_Status == 1)&&(esam_error==0) ) Progkey.Timer = 0;	//私钥下编程禁止
			if( Progkey.Timer )
			{
				progenable = 1;	//编程使能
			}
			else
			{
				progenable = 0;	//编程禁止
			}
			
			if( (ANAC->FDETIF)&BIT0 )	//xtlf发生停振
			{
				ANAC->FDETIF = ANAC->FDETIF;//清XTLF停振标志
				Result = I2C_Read_Eeprom( ee_xtlfstop_time_page, ee_xtlfstoptime_inpage, Buf, ee_xtlfstoptime_lenth );
				if( (Result || (ChkBufZero(Buf,ee_xtlfstoptime_lenth)==0)) && (clock_error==0) ) //判断是否发生记录
				{
					//记录晶振停振的发生时刻
					I2C_Write_Eeprom( ee_xtlfstop_time_page, ee_xtlfstoptime_inpage, Sclock.Clockbackup, ee_xtlfstoptime_lenth );
				}
			}
			
			//开盖延时定时器减1
			if( Cover_Space_Timer != 0 ) Cover_Space_Timer--;	
			
			//通信模块更换延时定时器减1
			if( Commmodule_Space_Timer != 0 ) Commmodule_Space_Timer--; 

			if( Relay_Space_Timer != 0 ) //上电延时动作继电器
			{
				Relay_Space_Timer--;
				if( Relay_Space_Timer==0 ){ relay_direct_flag = 1; run_alarm_flag = 1; }
			}			
		}
		if ( Sclock.Clockbackup[0] > Sclock.Clockmain[0] )//分钟改变
		{
		 	if( Sclock.Clockmain[1]&B0000_0001 )
			{
				GetKeyStatus();//读当前密钥状态(2min一次)
			}
		 	
		 	if( relay_error || (Sclock.Clockmain[1]==0x30) ) relay_direct_flag = 1;

		 	if( nline_err_flag ) 
		 	{
		 		Keeptime.Times[0]++; 	//零线电流不平衡持续时间加1分钟
		 	}		 	
 		 	if( load_over_flag ) 
 		 	{
 		 		Keeptime.Times[1]++; 	//电流过载总持续时间加1分钟
 		 	}
 		 	if( low_voltage_flag )  
 		 	{
 		 		Keeptime.Times[2]++;	//电池欠压持续时间加1分钟
 		 	}
 		 	if( below_60u_flag )  
 		 	{
 		 		Keeptime.Times[3]++;	//掉电总持续时间加1分钟
 		 		Keeptime.Times[9]++;	//月停电累计时间加1分钟
 		 		Keeptime.Times[11]++;	//年停电累计时间加1分钟
 		 	}
 		 	if( lost_v_flag ) 
 		 	{
 		 		Keeptime.Times[5]++; 	//失压总持续时间加1分钟
 		 		Lost_V_Timer++;		//此次失压累计时间
 		 	} 
 		 	
 		 	if( lower_v_flag )
 		 	{
 		 		if( lower_v_event_flag  ) 
	 		 	{
	 		 		Keeptime.Times[6]++; 	//低电压持续时间加1分钟
	 		 	} 
	 		 	else
	 		 	{
	 		 		Current_Over_Count41++;	//低电压临时持续时间加1分钟
	 		 	}
 		 	}
 		 	if( high_v_flag )
 		 	{
 		 		if( high_v_event_flag ) 
	 		 	{
	 		 		Keeptime.Times[7]++; 	//高电压持续时间加1分钟
	 		 	} 
	 		 	else
	 		 	{
	 		 		Current_Over_Count51++;	//高电压临时持续时间加1分钟
	 		 	} 		
 		 	}
			
		 	//定时8M时钟调校功能
			if( Sclock.Clockmain[1]==0x00 )
			{
				if( Adj_Clk_Timer )
				{
					Adj_Clk_Timer--;	//定时8M时钟调校定时器减1h
					if( Adj_Clk_Timer == 0 )  Clk_Adj_Proc();//根据外部的32K晶体来调整内部8M的偏差
				}
				if( Adj_Clk_Timer == 0 ) Adj_Clk_Timer = Adjclk_timer_delay;				
			}
			
			//载波波特率协商功能
			if( Zb_Comm_Timer )
			{
				if( Zb_Comm_Timer > Zb_Comm_Timer_delay ) Zb_Comm_Timer = 0;
				else Zb_Comm_Timer--;	//载波通讯波特率恢复定时器减1min
				
				if( Zb_Comm_Timer == 0 )
				{
					reg_veri_flag = 1;	//置寄存器校验标志
				}
			}
			
			//通信模块超时定时器
			if( Mod_Comm_Timer1 )
			{
				if( Mod_Comm_Timer1 > Mod_Comm_Timer_delay1 ) Mod_Comm_Timer1 = 0;
				else Mod_Comm_Timer1--;	//载波通讯波特率恢复定时器减1min
				
				if( Mod_Comm_Timer1 == 0 )
				{
					//36小时没有载波通信,则复位载波,启动5min通信模块异常延时定时器
					if( (Mode.Plc&0x80) )
					{
						Resetworking_Timer = resetworking_timer_delay;//启动复位脉冲
						PLC_RST0;		//复位载波(输出低)
					}
					Mod_Comm_Timer2 = Mod_Comm_Timer_delay2; //复位5min后没有通信则认为通信模块异常
				}
			}
			else if( Mod_Comm_Timer2 )//通信模块异常延时判断
			{
				Mod_Comm_Timer2--;
				if( Mod_Comm_Timer2 == 0 )
				{
					if( (commmodule_failed_flag==0) && (commmodule_open_flag==0) ) //通信模块插入但是通讯超时
					{
						commmodule_failed_flag = 1;		//置通信模块异常标志
						Store_Meterstatus();
						memcpy( Buf, Sclock.Clockbackup, 7 );
						Syn_Clock();
						Note_Run_Event(ee_commerrn_inpage);	//记录通信模块异常开始
						memcpy( Sclock.Clockbackup, Buf, 7 );
					}
				}
			}
		 	
		 	if( Ble_RstTimer )
		 	{
		 		Ble_RstTimer--;
		 		if( Ble_RstTimer == 0 )
		 		{
		 			Ble_Step = 1;				//查询蓝牙心跳
		 			Ble_Init();
		 			Ble_RstTimer = Zb_Comm_Timer_delay;
		 		}
		 	}
		 	
		 	if( (Ble_Step == 1) && (Ble_RstTimer == (Zb_Comm_Timer_delay-1)) )	//1分钟未收到心跳应答
	 		{
	 			Ble_Rst();
	 		}
		 		
			if( Progkey.Timer ) Progkey.Timer --;//编程延时减1
			
			#if(1 == CHINT_Mode)	
			V_ulDataBuf = Byte2uInt(Ijtimer_Para.Ijtimer.B08);
			if( V_ulDataBuf != 0 ) //软I_J短接定时器
			{
				V_ulDataBuf--;
				Int2Byte(V_ulDataBuf,Ijtimer_Para.Ijtimer.B08);
				I2C_Write_Eeprom(ee_softij_page, ee_softij_inpage, Ijtimer_Para.Ijtimer.B08, 4);	//有效期间，每分钟保存一次
			}	
			#endif	
		}
	}
	
	if ( Sclock.Clockbackup[0] > Sclock.Clockmain[0] )//分钟改变(防止在零点附近出现缓升缓降)
	{
		run_freeze_flag = 1;	//冻结和结算判断
		
		if(( Sclock.Clockmain[1]== 0x00)&&( Sclock.Clockmain[2]== 0x00))	//每天00:00一次
		{
			Outputtype = 0;
			reg_veri_flag = 1;	//默认秒脉冲输出
			Clr_Zero_Data();	//零点清零相关数据
		}	
	}	
		
	Syn_Clock();//同步主和备份时钟	 
}
