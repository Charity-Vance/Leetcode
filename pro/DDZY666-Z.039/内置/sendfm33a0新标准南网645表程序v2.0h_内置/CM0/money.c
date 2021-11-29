#include "ex_func.h"
#include "ex_var.h"
#include "FM32L0XX.h"  
#include <string.h>


void Calculate_Overflow( unsigned char *Buf, unsigned char Num )//组合电量边界处理
{
	union B64_B08_2 Temp64;
	
	memset( Temp64.B08, 0x00, 8 );
	memcpy( Temp64.B08, Buf, Num );
	
	//组合电量边界处理
	if( Temp64.B64 > 7999999999 )	//组合: 组合有功、组合无功的数值范围变为：0.0000～799999.9999
	{
		Temp64.B64 -= 8000000000;	//对此，要求在到达极限值时进行归零处理。
		if( Temp64.B64 > 7999999999 )
		{
			Temp64.B64 -= 8000000000;
			if( Temp64.B64 > 7999999999 ) Temp64.B64 -= 8000000000;
		}
	}
	
	memcpy( Buf, Temp64.B08, Num );
}

void Calculate_Dl_G( unsigned char *Buf )//计算电量示值(高精度8字节)
{
	union S64_B08_2 Temp64;
	
	//电量脉冲数转换成高精度电量(单位0.0001kwh)
	memcpy( Temp64.B08, Buf, 8 );
	Temp64.S64 = (Temp64.S64*100/Meter.Const_H); 	//脉冲数转换成高精度电量
	
	memcpy( Buf, Temp64.B08, 8 );
}

//正向或者反向(输入4字节脉冲数)
void Hex2Bcd_Dl( unsigned char *Buf, unsigned char Di )//脉冲数转BCD电量
{
	unsigned char Temp08=0;
	union B32_B08_2 Temp32;
	union B64_B08_2 Temp64;
	
	memcpy( Temp32.B08, Buf, 4 );
	
	if( Di==0 ) //仅组合无功计算有效
	{	
		if( (signed long )(Temp32.B32) < 0 )
		{
			Temp08 = 1;
			Temp64.B64 = (signed long long)((signed long)Temp32.B32*(-1.0))*100/Meter.Const_H;
		}
		else
		{
			Temp64.B64 = (signed long long)((signed long)Temp32.B32*( 1.0))*100/Meter.Const_H;
		}
			
		Calculate_Overflow( Temp64.B08, 8 );//组合电量边界处理
		Hex2Bcd_SS( Temp64.B08, Temp64.B08, 8 );
		memcpy( Buf, Temp64.B08+1, 4 );
		if( Temp08 ) Buf[3] |= 0x80;	//组合电量<0，最高位置1
	}
	else	//其他
	{
		Temp32.B32 /= Meter.Const_H;
		Hex2Bcd_SS( Temp32.B08, Buf, 4 );
	}
}

//Di=0为组合,其他为正向或者反向(输入8字节脉冲数)
void Hex2Bcd_Dl_G( unsigned char *Buf, unsigned char Di )//脉冲数转BCD电量(高精度)
{
	unsigned char Temp08=0;
	union B64_B08_2 Temp64;
	
	memcpy( Temp64.B08, Buf, 8 );
	
	Calculate_Dl_G( Temp64.B08 );//高精度电量(HEX码)
	
	if( Di==0 ) //组合
	{	
		if( (signed long long)(Temp64.B64) < 0 )
		{
			Temp08 = 1;
			Temp64.B64 = (signed long long)(Temp64.B64)*(-1.0);
		}
		Calculate_Overflow( Temp64.B08, 8 );//组合电量边界处理
		Hex2Bcd_SS( Temp64.B08, Buf, 8 );
		if( Temp08 ) Buf[7] |= 0x80;	//组合电量<0，最高位置1
	}
	else	//其他
	{
		Hex2Bcd_SS( Temp64.B08, Buf, 8 );
	}
}

void Calc_Pwr_Proc()	//正反向电量累计处理和金额处理
{
	unsigned char i, j;
	unsigned int Page;	
	unsigned char Inpage;
	unsigned long int *Ptr32;
	
	if( EA_OFF ) return;//掉电不处理,程序直接返回
	
	if( Decimal.Add_Rp ) //无功计算
	{
		//四象限无功计量
		if( Decimal.Add_Rp && (Decimal.Add_Rp <=(maxtimes*Meter.Const_H)) )
		{			
			if( (dl_back_flag == 0) && (dl_back_flag2 == 0) ) i=0;//第一象限无功
			else if( (dl_back_flag == 1) && (dl_back_flag2 == 0) ) i=1;//第二象限无功
			else if( (dl_back_flag == 1) && (dl_back_flag2 == 1) ) i=2;//第三象限无功
			else i=3;//第四象限无功
			
			if( Rpdl_Verify(i)==0 )//无功电量校验
			{
				Ptr32 = &(Rpdl[i].Pluse[0].B32);
				Page = ee_rpdl_page+2*i;
				Inpage = ee_rpdl_inpage;
				Decimal.Status |= (1<<i);		//置无功电量改变标志
				
				{START_CRITICAL() 
				ENTER_CRITICAL();
				j = Decimal.Add_Rp;
				Decimal.Add_Rp = 0x00;	
				EXIT_CRITICAL();}
				
				for( ; j>0; j-- )
				{
					if( Ptr32[0]>=0x7fffffff ) continue;	//超过脉冲计量最大值
					else Ptr32[0] += 1;
					if( (Tariff.Current+1) > max_feilvcount ) Ptr32[1] += 1;
					else Ptr32[Tariff.Current+1] += 1;
					
					Crc_16Bits_Add2( (unsigned char *)&Ptr32[0], ee_rpdl_lenth );	//重新计算crc
						
					if( (Ptr32[0]%(Meter.Const_H*100))==0 )	//有功总脉冲数到整度
					{
						WriteE2WithBackup( Page, Inpage, (unsigned char *)&Ptr32[0], ee_rpdl_lenth );
						Decimal.Status &= ~(1<<i);	//清无功电量改变标志
					}
				}
			}
			else
			{
				Decimal.Add_Rp = 0x00;
			}
		}
		else if( Decimal.Add_Rp > (maxtimes*Meter.Const_H) )
		{
			Decimal.Add_Rp = 0x00;
		}
	}
	
	if( Decimal.Add ) //有功计量
	{
		if( Decimal.Add > (maxtimes*Meter.Const_H) ){Decimal.Add = 0x00;return;}	//电量增量异常
		
		if( dl_back_flag == 0 ) 
		{
			if( Fwdl_Verify() ) {Decimal.Add = 0x00;return;}			//正向电量校验
			Ptr32 = &(Fwdl.Pluse[0].B32);
			Page = ee_fwdl_page;
			Inpage = ee_fwdl_inpage;
		}
		else
		{
			if( Bkdl_Verify() ) {Decimal.Add = 0x00;return;}			//反向电量校验
			Ptr32 = &(Bkdl.Pluse[0].B32);
			Page = ee_bkdl_page;
			Inpage = ee_bkdl_inpage;
		}
		
		{START_CRITICAL() 
		ENTER_CRITICAL();
		j = Decimal.Add;
		Decimal.Add = 0x00;	
		EXIT_CRITICAL();}
		
		for( ; j>0; j-- )
		{
			if( Ptr32[0]>=0xffffffff ) continue;	//超过脉冲计量最大值
			else Ptr32[0] += 1;
			if( (Tariff.Current+1) > max_feilvcount ) Ptr32[1] += 1;
			else Ptr32[Tariff.Current+1] += 1;
			Ptr32[max_feilvcount+1] += 1;//本月用电量增加(脉冲数)
			
			//有功或者无功脉冲改变
			if( dl_back_flag == 0 ) Decimal.Status |= B0001_0000;	//置正向脉冲改变标志
			else Decimal.Status |= B0010_0000;	//置反向脉冲改变标志
				
			Crc_16Bits_Add2( (unsigned char *)&Ptr32[0], ee_fwdl_lenth );	//重新计算crc
				
			if( (Ptr32[0]%(Meter.Const_H*100))==0 )	//有功总脉冲数到整度
			{
				WriteE2WithBackup( Page, Inpage, (unsigned char *)&Ptr32[0], ee_fwdl_lenth );
				if( dl_back_flag == 0 ) Decimal.Status &= (~B0001_0000);
				else Decimal.Status &= (~B0010_0000);
			}
			
			run_price_flag = 1;	//置费率阶梯判断标志
		}
	}
}


//offset=0结算周期,offset=3清结算周期
//offset=1月结算,offset=4清月结算
//offset=2年结算,offset=5清年结算,offset=6年结算时间清零
void Process_Usedl( unsigned char offset )
{
	unsigned char i, len;
	unsigned char  Buf[ee_histroyusedl_lenth+8];
	
	memcpy( Buf, Sclock.Clockbackup+2, 4 );//复制时间
	Cal_Comb( 0, 0, 0, Buf+4 );	//计算当前组合电量	
//	Inverse( Buf+4, 4 );
	
	if( offset<3 ) 
	{				
		I2C_Read_Eeprom( ee_pre1_histroyusedl_page+offset, 0x00, Buf+8, ee_histroyusedl_lenth );//读上1~6总电量或者上1总电量
		if( offset != 2 ) memcpy( Buf, Buf+4, ee_histroyusedl_lenth+4 ); //结算日结算和月结算无需保存时间
	}
	else if( offset<6 )
	{
		offset -= 3;
		memset( Buf, 0x00, ee_histroyusedl_lenth );		//清上1~7总电量或者上1~2总电量
	}
	else
	{
		offset = 2;
		memset( Buf, 0x00, 4 );			//时间清零
	
		for( i=1; i<7; i++ )
		{
			memcpy( Buf+8*i, Buf, 8 );	//上1~6电量转存
		}
	}
	
	if( offset<2 )	len= ee_histroyusedl_lenth;
	else	len= ee_yhistroyusedl_lenth;

	I2C_Write_Eeprom( ee_pre1_histroyusedl_page+offset, 0x00, Buf, len );//上1~4总电量转存	
	
	Wr_Pretime_Hisfreeze();	//写上一次结算时间
}


//type=0年结算,年转存,清用电量
//type=1年结算,月转存,不清用电量
//type=2月结算,月转存,清用电量
void Freeze_Usedl( unsigned char type )//结算处理
{
	Clear_Wdt();
	
	if( type == 0 )
	{
		Process_Usedl( 2 );	//上1年结算日总电量转存
	}
	else
	{
		Process_Usedl( 1 );	//上1月结算日总电量转存
	}
	
	if( type == 1 )	return;//年结算,月转存,不清用电量
	
	if( Fwdl_Verify() ) return;	//正向电量校验
	memset( Fwdl.UPluse.B08, 0x00, 4 );//正向用电量清零
//	Fw.UPluse.B32 = Fw.Pluse[0].B32%Meter.Const_H;//正向月用电量清零(脉冲数)
	Crc_16Bits_Add2( Fwdl.Pluse[0].B08, ee_fwdl_lenth ); //CRC计算
	WriteE2WithBackup( ee_fwdl_page, ee_fwdl_inpage, Fwdl.Pluse[0].B08, ee_fwdl_lenth );
	
	if( Bkdl_Verify() ) return;	//反向电量校验
	memset( Bkdl.UPluse.B08, 0x00, 4 );//反向用电量清零
//	Bk.UPluse.B32 = Bk.Pluse[0].B32%Meter.Const_H;//反向月用电量清零(脉冲数)
	Crc_16Bits_Add2( Bkdl.Pluse[0].B08, ee_bkdl_lenth ); //CRC计算
	WriteE2WithBackup( ee_bkdl_page, ee_bkdl_inpage, Bkdl.Pluse[0].B08, ee_bkdl_lenth );
}


//冻结保存脉冲数,低字节在前
void Freeze_Dl(unsigned int page, unsigned char offset)
{
	unsigned char Result, i;

	Clear_Wdt();

	memcpy( Eeprom.Buffer, Sclock.Clockbackup+1, 5 );
	
	memcpy( Eeprom.Buffer+5,  Fwdl.Pluse[0].B08, max_dl_lenth );
	memcpy( Eeprom.Buffer+5+max_dl_lenth, Bkdl.Pluse[0].B08, max_dl_lenth );
		
	for(i=0; i<4; i++) //四象限无功
	{
		memcpy( Eeprom.Buffer+5+max_dl_lenth*(2+i), Rpdl[i].Pluse[0].B08, max_dl_lenth );
	}
	
	if( page==ee_histroy_dl_page ) 		
	{
		memcpy( Eeprom.Buffer+ee_histroydl_lenth-3, &Mode.Comp_B, 1 );//有功组合字
		memcpy( Eeprom.Buffer+ee_histroydl_lenth-2, Mode.Rpcomp, 2 );//无功组合字1和2
		
		Process_Usedl(0);//上1结算日总电量转存
		
		freeze_display_flag = 0; //清结算日电量已显示标志(结算日转存或者清零需要刷新)
	}
	else
	{
		memcpy( Eeprom.Buffer+ee_freezedl_lenth-8,  Emu_Data.P1.B08, 3 );//有功功率
		memcpy( Eeprom.Buffer+ee_freezedl_lenth-5,  Emu_Data.Q1.B08, 3 );//无功功率
		if( dl_back_flag ) Eeprom.Buffer[ee_freezedl_lenth-6] |= 0x80;//反向有功功率bit7置1
		if( dl_back_flag2 ) Eeprom.Buffer[ee_freezedl_lenth-3] |= 0x80;//反向无功功率bit7置1
		
		memcpy( Eeprom.Buffer+ee_freezedl_lenth-2, Mode.Rpcomp, 2 );//无功组合字1和2
	}
	
	Result = Write_Event_Point(offset);
	
	I2C_Write_Eeprom( page+3*Result+0, 0x00, Eeprom.Buffer, 128 );	//冻结时间+冻结数据
	I2C_Write_Eeprom( page+3*Result+1, 0x00, Eeprom.Buffer+128, 128 );	//冻结数据
	I2C_Write_Eeprom( page+3*Result+2, 0x00, Eeprom.Buffer+256, ee_freezedl_lenth-256 );	//冻结数据
	SynEeprom(); //同步冻结到Flash
	
	if( page==ee_dayfreezedl_page ) //日电压合格率记录转存
	{
		//日电压合格率记录
		CalLoad( Eeprom.Buffer, 0 );
		Result = Write_Event_Point(ee_dayvolpassn_inpage);
		I2C_Write_Eeprom( ee_dayvolpass_note_page+Result/4, ee_dayvolpassnote_inpage+(Result%4)*ee_dayvolpassnote_len, Eeprom.Buffer, ee_dayvolpassnote_len );
		InitVolSts( 0 ); //清除对应的电压合格率
		
		Wr_Pretime_Dayfreeze();	//写上一次日冻结时间
	}		
	if( page==ee_monthfreeze_page ) //月电压合格率记录转存
	{
		//月电压合格率记录
		CalLoad( Eeprom.Buffer, 1 );
		Result = Write_Event_Point(ee_monvolpassn_inpage);
		I2C_Write_Eeprom( ee_monvolpass_note_page+Result/4, ee_monvolpassnote_inpage+(Result%4)*ee_monvolpassnote_len, Eeprom.Buffer, ee_monvolpassnote_len );
		InitVolSts( 1 ); //清除对应的电压合格率
	}		
}

void Hour_Freeze_Dl(unsigned int page,unsigned char offset)//整点冻结或者半点冻结
{
	unsigned char Result,inpage;
	
	memcpy( Eeprom.Buffer, Sclock.Clockbackup+1, 5 );
	DltoEepromBuf( 5 );
	Result = Write_Event_Point(offset);
	inpage = ee_hourfreezedl_inpage+(Result%4)*13;
	I2C_Write_Eeprom( page+(Result>>2), inpage, Eeprom.Buffer, ee_hourfreezedl_lenth );
	SynEeprom(); //同步冻结到Flash
}


//status=0表示停电调用,status=1表示上电调用
//RAMREG5跨年结算次数,RAMREG6跨结算日次数,RAMREG7年结算跨第一结算日次数,RAMREG8月结算跨第一结算日次数,上电补存使用
//Ic_Comm_RxBuf作为结算时间临时数据区
void Histroy_Freeze_Dl(unsigned char status)//结算电量冻结处理
{
	unsigned char Result=0;
	unsigned char  Buf[10];
	
//	if( BDMODE )//本地费控电能表
//	{
		//年结算判
		Result = Year_Ladder_Judge(status); //年阶梯启动判断和数据合法性判断
		
		if( (Price.Ladder_Mode == 0x55) && (Sclock.Clockbackup[3] <= 0x28) &&
			( (Cmp_Data( Price.Year_Ladder+0, Sclock.Clockbackup+2, 3 ) == 0x03) 
			|| (Cmp_Data( Price.Year_Ladder+3, Sclock.Clockbackup+2, 3 ) == 0x03)
			|| (Cmp_Data( Price.Year_Ladder+6, Sclock.Clockbackup+2, 3 ) == 0x03)
			|| (Cmp_Data( Price.Year_Ladder+9, Sclock.Clockbackup+2, 3 ) == 0x03)
			|| (Cmp_Data( Price.Year_Ladder+12, Sclock.Clockbackup+2, 3 ) == 0x03)
			|| (Cmp_Data( Price.Year_Ladder+15, Sclock.Clockbackup+2, 3 ) == 0x03) )	)//时日月相等
		{
		  	if( (Result!=0x55)&&(Result!=0x5a) )
		  	{
		  		if( status ) Freeze_Usedl(0);//年结算,年用电量转存和清零
		  		else
		  		{
		  			if( RAMREG5 < 7 ) RAMREG5++;	//支持上1~上6年用电量
		  			memcpy( Ic_Comm_RxBuf+60, Ic_Comm_RxBuf+60+4, 24 );//移位历史停电年结算时间
					memcpy( Ic_Comm_RxBuf+60+24, Sclock.Clockbackup+2, 4 );//保存当前停电年结算时间(时日月年)
		  		}
		  	}
		}
//	}
//	else
//	{
//		Price.Ladder_Mode = 0x00;	//不支持年阶梯
//	}
	
	//结算日判断
	ReadE2WithBackup( ee_histroyparameter_page, ee_histroyparameter_inpage, Buf, ee_histroyparameter_lenth );
	if( ((Buf[0]== Sclock.Clockbackup[2]) && (Buf[1]== Sclock.Clockbackup[3])) ||
	    ((Buf[2]== Sclock.Clockbackup[2]) && (Buf[3]== Sclock.Clockbackup[3])) ||
	    ((Buf[4]== Sclock.Clockbackup[2]) && (Buf[5]== Sclock.Clockbackup[3])) ) 
	{
		//结算日判断
		if( (Result!=0x5a)&&(Result!=0xaa) )
		{
			if( status ) Freeze_Dl(ee_histroy_dl_page,ee_histroyf_inpage);
			else
			{
				if( RAMREG6 < 12+12 ) RAMREG6++;
				memcpy( Ic_Comm_RxBuf+100, Ic_Comm_RxBuf+100+4, 92 );//移位历史停电冻结时间
				memcpy( Ic_Comm_RxBuf+100+92, Sclock.Clockbackup+2, 4 );//保存当前停电冻结时间(时日月年)
			}
		}
		
		//第一结算日判断
		if((Buf[0]== Sclock.Clockbackup[2]) && (Buf[1]== Sclock.Clockbackup[3]))
		{
			//年结算跨第一结算日
			if( Price.Ladder_Mode == 0x55 )
			{
				if( Result!=0x5a)
				{
					if( status ) Freeze_Usedl(1);//年结算,月转存
					else
					{
						if( RAMREG7 < 12+12 ) RAMREG7++;
					}
				}
			}
			else//月结算跨第一结算日
			{
				if( Result!=0xaa)
				{
					if( status ) Freeze_Usedl(2);//月结算,月用电量转存和清零
					else
					{
						if( RAMREG8 < 12+12 ) RAMREG8++;
					}
				}			
			}
		}	
	}
}


void Freeze_Judge()	//冻结和结算判断
{
	unsigned char i;
	unsigned char  Result,Buf[20];
	
	run_freeze_flag = 0;
	run_loadchk_flag = 1;
	
	I2C_Read_Eeprom44( ee_freezeparameter_page, Buf, ee_freezeparameter_lenth );
		
	if( EA_ON && ((Cmp_Clock( Buf, 5 ) != 0x01)) )//整点冻结起始时间<=当前时间
	{
		Result = Sclock.Clockbackup[1];
		if( (Result == 0) || ((Result == 0x30)&&(Buf[5] == 0x30)) )
		{
			Hour_Freeze_Dl(ee_hourfreezedl_page,ee_hourf_inpage);//整点冻结
		}
	}
	
	if( EA_ON && (Cmp_Clock( Buf+6, 2 ) == 0x03) ) 
	{
		Freeze_Dl(ee_dayfreezedl_page,ee_dayf_inpage); //日冻结时间=当前时间,日冻结
	}
        
	for(i=0; i<3; i++)
	{
		if(Buf[8+i]== 0x99) Buf[8+i] = Sclock.Clockbackup[4-i];
	}
	if( EA_ON && ((Cmp_Clock( Buf+8, 4 ) == 0x03)) ) 
	{
		Freeze_Dl(ee_timingfreeze_dl_page,ee_timingf_inpage); //定时冻结
	}
	
	if( (0x00== Sclock.Clockbackup[1]) && (0x00== Sclock.Clockbackup[2]) && (0x01== Sclock.Clockbackup[3]) )
	{
		Freeze_Dl( ee_monthfreeze_page, ee_monthn_inpage );//月冻结
		
		if( 0x01== Sclock.Clockbackup[4] )	//1月1日00:00
		{
			month_change_flag = 1;
			year_change_flag = 1;
			year_change_flag2 = 1;
		}
		else
		{
			month_change_flag = 1;
		}
		Freeze_Pddata();	//冻结掉电数据
	}	
		
	if( Sclock.Clockbackup[1]== 0x00 )//分钟等于0
	{
		Histroy_Freeze_Dl(1);//结算电量冻结处理
	}				
}


void Pd_Hourfreeze_Judge()	//上电整点冻结和定时冻结补存判断处理
{
	unsigned int  i;
	unsigned char result;
	unsigned char Buf[ee_freezeparameter_lenth+2], BufA[6], BufB[ee_powerdown_lenth+2], BufC[7];
	
	if(clock_error) return;	//当前时间非法
	
	if( I2C_Read_Eeprom( ee_power_down_page, 0x00, BufB, ee_powerdown_lenth )  ) return;//读掉电时间(分时日月年)
	if( JudgeClockNoWeek( 1, BufB+1, 5 ) ) return;	//时间非法
	memcpy( BufC, BufB, 7 );//备份原掉电时间
	
	memcpy( BufA, Sclock.Clockbackup, 6 );//当前时间(秒分时日月年)
	
	result = Cmp_Bcd_Inv( BufA+1, BufB+1, 5 );//比较分时日月年5字节
	if( result != 1 ) return;//A=B或者A<B,返回
		
	I2C_Read_Eeprom44( ee_freezeparameter_page, Buf, ee_freezeparameter_lenth );
	
	BufB[0] = 0;//秒
	if( BufB[1] >= 0x30 ) BufB[1] = 0x30;//分钟
	else BufB[1] = 0;//分钟
	for( i=0; i<0x5fff; i++ )	//最长停电不少于1年
	{
		Clear_Wdt();
		Add_Min_Clock( BufB, 30 ); //加30分钟处理
		
		result = Cmp_Bcd_Inv( BufA+1, BufB+1, 5 );//比较分时日月年5字节
		if( result == 2 ) break;//A<B,返回
		
		memcpy( Sclock.Clockbackup+1, BufB+1, 5 );//更新当前时间(新停电时间)
		if( Cmp_Clock( Buf, 5 ) != 0x01 )//整点冻结起始时间<=当前时间
		{
			result = Sclock.Clockbackup[1];
			if( (result == 0) || ((result == 0x30)&&(Buf[5] == 0x30)) )
			{
				Hour_Freeze_Dl(ee_hourfreezedl_page,ee_hourf_inpage);//整点冻结(补停电下一个点数据)
				break;
			}
		}
	}
	
	memcpy( BufB, BufC, 7 );//掉电时间
	BufB[0] = 0;//秒
	for(i=0; i<4; i++)
	{
		if( Buf[11-i] != 0x99 ) 
			BufB[1+i] = Buf[11-i];
	}
	
	result = Cmp_Bcd_Inv( BufB+1, BufC+1, 5 );//比较分时日月年5字节
	if( result ) //冻结时间 不等于 掉电时间，冻结时间加1
	{
		if( result == 2 )
		{
			if( Buf[10] == 0x99 ) //hh
				AddNClock( 2, BufB, 1 );
			else if( Buf[9] == 0x99 ) //DD
				AddNClock( 3, BufB, 1 );
			else if( Buf[8] == 0x99 ) //MM
				AddNClock( 4, BufB, 1 );
		}

		result = Cmp_Bcd_Inv( BufA, BufB, 6 );//秒分时日月年
		if( result == 1 ) //当前时间 > 冻结时间
		{
			memcpy( Sclock.Clockbackup+1, BufB+1, 5 );//更新当前时间(新停电时间)
			Freeze_Dl(ee_timingfreeze_dl_page,ee_timingf_inpage); //定时冻结(补停电下一个点数据)
		}
	}
	
	//新增日冻结补存(补停电下一个点数据)
	memcpy( BufB, BufC, 7 );//掉电时间
	BufB[0] = 0;//秒
	BufB[1] = Buf[7];//日冻结分
	BufB[2] = Buf[6];//日冻结时
	
	result = Cmp_Bcd_Inv( BufB+1, BufC+1, 5 );//比较分时日月年5字节
	if( result ) //冻结时间 不等于 掉电时间，冻结时间加1
	{
		if( result == 2 )//B < C
		{
			AddNClock( 3, BufB, 1 );
		}

		result = Cmp_Bcd_Inv( BufA, BufB, 6 );//秒分时日月年
		if( result == 1 ) //当前时间 > 冻结时间
		{
			memcpy( Sclock.Clockbackup+1, BufB+1, 5 );//更新当前时间(新停电时间)
			Freeze_Dl(ee_dayfreezedl_page,ee_dayf_inpage); //日冻结补存(补停电下一个点数据)
		}
	}
	
	Syn_Clock();	//同步时钟
}


void Pd_Calculate_Judge()	//停电统计时间计算判断处理	
{
	unsigned int  i;
	unsigned char result, flag;
	unsigned char Buf[8], BufA[6], BufB[ee_powerdown_lenth+2], BufC[7], BufD[6];
	union B32_B08_2 Temp32;
	
	if(clock_error) return;	//当前时间非法
	
	if( I2C_Read_Eeprom( ee_power_down_page, 0x00, BufB, ee_powerdown_lenth )  ) return;//读掉电时间(分时日月年)
	if( JudgeClockNoWeek( 1, BufB+1, 5 ) ) return;	//时间非法
	memcpy( BufC, BufB, 7 );//备份原掉电时间
	
	memcpy( BufA, Sclock.Clockbackup, 6 );//当前时间(秒分时日月年)
	
	//读掉电记录
	if( ChkPdRcdTime() == 1 ) return;	//结束记录完整则不统计
	
	//月停电统计补存处理
	flag = 0;
	memcpy( BufD, BufC, 6 );//掉电时间
	memcpy( BufB, BufC, 6 );//掉电时间
	BufB[0] = 0;//秒
	BufB[1] = 0;//分
	BufB[2] = 0;//时
	BufB[3] = 1;//日
	for( i=0; i<=36+1; i++ )
	{
		Clear_Wdt();
		AddNClock( 4, BufB, 1 );	//MM
		
		result = Cmp_Bcd_Inv( BufA, BufB, 6 );//秒分时日月年
		if( result == 1 ) //当前时间 > 新时间
		{
			//统计历史数据
			if( flag == 0 )
			{
				Get_Keep_Timer(8, Buf);//读月停电累计次数
				Get_Keep_Timer(9, Buf+4);//读月停电累计时间(存在次数为0累计时间有值的情况)
				Bcd2Hex_SS( Buf+4, Temp32.B08, 4 );
				Temp32.B32 += (CalcTime( BufB+1 )- CalcTime( BufD+1 ));
				Hex2Bcd_SS( Temp32.B08, Buf+4, 4 );
				result = Write_Event_Point(ee_monpowerdownn_inpage);
				I2C_Write_Eeprom( ee_powerdown_month_page+result/8, (result%8)*8, Buf, ee_powerdownmonth_lenth );
				{Clr_Otherdata(8);Clr_Otherdata(9);}//月停电统计数据
			}
			else
			{
				memset( Buf, 0x00, 4 );//月停电累计次数为0
				Temp32.B32 = CalcTime( BufB+1 )- CalcTime( BufD+1 );
				Hex2Bcd_SS( Temp32.B08, Buf+4, 4 );
				result = Write_Event_Point(ee_monpowerdownn_inpage);
				I2C_Write_Eeprom( ee_powerdown_month_page+result/8, (result%8)*8, Buf, ee_powerdownmonth_lenth );
			}
			
			memcpy( BufD, BufB, 6 );//新时间
			flag = 1;//跨月  
		}
		else
		{
			//统计当前数据
			Keeptime.Times[9] = CalcTime( BufA+1 )- CalcTime( BufD+1 );
			break;
		}
	}
	
	//年停电统计补存处理
	flag = 0;
	memcpy( BufD, BufC, 6 );//掉电时间
	memcpy( BufB, BufC, 6 );//掉电时间
	BufB[0] = 0;//秒
	BufB[1] = 0;//分
	BufB[2] = 0;//时
	BufB[3] = 1;//日
	BufB[4] = 1;//月
	for( i=0; i<=3+1; i++ )
	{
		Clear_Wdt();
		AddNClock( 5, BufB, 1 );	//YY
		
		result = Cmp_Bcd_Inv( BufA, BufB, 6 );//秒分时日月年
		if( result == 1 ) //当前时间 > 新时间
		{
			//统计历史数据
			if( flag == 0 )
			{
				Get_Keep_Timer(10, Buf);//读年停电累计次数
				Get_Keep_Timer(11, Buf+4);//读年停电累计时间(存在次数为0累计时间有值的情况)
				Bcd2Hex_SS( Buf+4, Temp32.B08, 4 );
				Temp32.B32 += (CalcTime( BufB+1 )- CalcTime( BufD+1 ));
				Hex2Bcd_SS( Temp32.B08, Buf+4, 4 );
				result = Write_Event_Point(ee_yearpowerdownn_inpage);
				I2C_Write_Eeprom( ee_powerdown_year_page, (result%8)*8, Buf, ee_powerdownyear_lenth );
				{Clr_Otherdata(10);Clr_Otherdata(11);}//年停电统计数据
			}
			else
			{
				memset( Buf, 0x00, 4 );//年停电累计次数为0
				Temp32.B32 = CalcTime( BufB+1 )- CalcTime( BufD+1 );
				Hex2Bcd_SS( Temp32.B08, Buf+4, 4 );
				result = Write_Event_Point(ee_yearpowerdownn_inpage);
				I2C_Write_Eeprom( ee_powerdown_year_page, (result%8)*8, Buf, ee_powerdownyear_lenth );
			}
			
			memcpy( BufD, BufB, 6 );//新时间
			flag = 1;//跨年  
		}
		else
		{
			//统计当前数据
			Keeptime.Times[11] = CalcTime( BufA+1 )- CalcTime( BufD+1 );
			break;
		}
	}
}


void Pd_Histroyfreeze_Judge()	//上电结算日补存判断处理
{
	unsigned int  i;
	unsigned char result;
	unsigned char Buf[5],BufA[5],BufB[10];
	
	if(clock_error) return;	//当前时间非法
	
	I2C_Read_Eeprom( ee_pre_history_page, ee_prehistory_inpage, BufB+1, ee_prehistory_lenth );//读上一次结算时间(分时日月年)
	if( JudgeClockNoWeek( 1, BufB+1, 5 ) ) return;	//时间非法
	
	memcpy( BufA, Sclock.Clockbackup+1, 5 );//当前时间(分时日月年)
	
	result = Cmp_Bcd_Inv( BufA, BufB+1, 5 );//比较分时日月年5字节
	if( result != 1 ) return;//A=B或者A<B,返回
	
	RAMREG5 = 0;//跨年结算次数
	RAMREG6 = 0;//跨结算日次数
	RAMREG7 = 0;//年结算跨第一结算日次数
	RAMREG8 = 0;//月结算跨第一结算日次数
	
	BufB[0] = 0;//秒
	BufB[1] = 0;//分钟
	for( i=0; i<0x6fff; i++ )	//最长停电不少于3年
	{
		Clear_Wdt();
		Add_Min_Clock( BufB, 60 ); //加60分钟处理
		
		result = Cmp_Bcd_Inv( BufA, BufB+1, 5 );//比较分时日月年5字节
		if( result == 2 ) break;//A<B,返回
		else if( (result == 0) && run_freeze_flag ){run_freeze_flag = 0;run_loadchk_flag = 1;}
		
		memcpy( Sclock.Clockbackup+1, BufB+1, 5 );//更新当前时间(可能存在阶梯电价启动)
		Histroy_Freeze_Dl(0);	//结算电量冻结处理(需要保证阶梯数据crc已经正确)
	}
	memcpy( Sclock.Clockbackup+1, BufA, 5 );//恢复当前时间(分时日月年)
	run_timezone_flag = 1;
	
	//补冻结处理
	if( ((RAMREG5 > 0)&&(RAMREG5 < 8)) || ((RAMREG7 > 0)&&(RAMREG7 < 13+12)) )
	{
		memcpy( Buf, Sclock.Clockbackup+2, 4 );//保存当前时间(时日月年)
		for( i=0; i<RAMREG5; i++ )
		{	
			memcpy( Sclock.Clockbackup+2, Ic_Comm_RxBuf+60+28-(RAMREG5-i)*4, 4 );//冻结时间
			Freeze_Usedl(0);//年结算,年用电量转存和清零
		}
		memcpy( Sclock.Clockbackup+2, Buf, 4 );//恢复当前时间(时日月年)		
	
		for( i=0; i<RAMREG7; i++ )
		{	
			Freeze_Usedl(1);//年结算,月转存
		}
	}
	
	if( (RAMREG8 > 0) && (RAMREG8 < 13+12) )
	{
		for( i=0; i<RAMREG8; i++ )
		{	
			Freeze_Usedl(2);//月结算,月用电量转存和清零
		}
	}
	
	if( (RAMREG6 > 0) && (RAMREG6 < 13+12) )
	{
		memcpy( Buf, Sclock.Clockbackup+2, 4 );//保存当前时间(时日月年)
		for( i=((RAMREG6 < 13) ? 0 : (RAMREG6-12)); i<RAMREG6; i++ )	//南网文档要求补12次
		{	
			Clear_Wdt();
			memcpy( Sclock.Clockbackup+2, Ic_Comm_RxBuf+100+96-(RAMREG6-i)*4, 4 );//冻结时间			
			Freeze_Dl(ee_histroy_dl_page,ee_histroyf_inpage); //结算冻结
		}
		memcpy( Sclock.Clockbackup+2, Buf, 4 );//恢复当前时间(时日月年)
	}
	
	if( RAMREG5||RAMREG6||RAMREG7||RAMREG8 ) Wr_Pretime_Hisfreeze();	//写上一次结算时间
}


//void Init_Dayfreeze_Judge()	//日冻结补存判断
//{
//	unsigned char i, n, k,result,result1,result2;
//	unsigned char Buf[50],BufA[6],BufB[6],BufC[6];
//	const unsigned char code days[] = { 0, 0x31, 0x28, 0x31, 0x30, 0x31, 0x30, 0x31, 0x31, 0x30, 0x31, 0x30, 0x31 };
//	
//	if(clock_error) return;	//当前时间非法
//	
//	I2C_Read_Eeprom( ee_pre_dayfreeze_page, ee_predayfreeze_inpage, BufB, ee_predayfreeze_lenth );//读上一次日冻结时间(分时日月年)
//	if( JudgeClockNoWeek( 1, BufB, 5 ) ) return;	//时间非法
//											
//	memcpy( BufA, Sclock.Clockbackup+1, 5 );//当前时间(分时日月年)
//	
//	result = Cmp_Bcd_Inv( BufA, BufB, 5 );//比较分时日月年5字节
//	if( result != 1 ) return;//A=B或者A<B,返回
//	
//	I2C_Read_Eeprom44( ee_freezeparameter_page, Buf, ee_freezeparameter_lenth );//读日冻结时间
//
//	//组成每次日冻结时间
//	memcpy( BufC, BufA, 5 );//当前时间
//	BufC[0] = Buf[7];//日冻结分
//	BufC[1] = Buf[6];//日冻结时
//	
//	n = 0;
//	for( i=0; i<8; i++ )
//	{
//		result1 = Cmp_Bcd_Inv( BufB, BufC, 5 );
//		result2 = Cmp_Bcd_Inv( BufA, BufC, 5 );
//		
//		//BufB<BufC<=BufA补
//		if((result1==2)&&(result2!=2))
//		{
//			n++;//跨日冻结次数加1
//			memcpy( Buf+n*5, BufC, 5 );//冻结时间
//		}
//		
//		//冻结时间加1日
//		if( BufC[2] == 0x01 )//比较当前日是否为1
//		{
//			if( BufC[3] == 0x01 )
//			{
//				BufC[4] = Hex_To_Bcd(Bcd_To_Hex(BufC[4])-1);//年减1
//				BufC[3] = 0x12;//12月
//				BufC[2] = 0x31;//31日
//			}
//			else
//			{
//				BufC[3] = Hex_To_Bcd(Bcd_To_Hex(BufC[3])-1);//月减1
//				//闰年判断
//				k = days[Bcd_To_Hex(BufC[3])];
//				if( (BufC[3] == 0x02) && ((Bcd_To_Hex(BufC[4])%4)==0 ) ) k++;	//闰年
//				BufC[2] = k;//最大日
//			}	
//		}
//		else
//		{
//			BufC[2] = Hex_To_Bcd(Bcd_To_Hex(BufC[2])-1);//日减1
//		}
//	}
//	
//	if( n > 7 ) n = 7;
//	
//	if( n )
//	{
//		memcpy( Buf, Sclock.Clockbackup+1, 5 );//保存当前时间(分时日月年)
//		
//		for(i=0; i<n; i++)
//		{
//			memcpy( Sclock.Clockbackup+1, Buf+(n-i)*5, 5 );//冻结时间
//			Freeze_Dl(ee_dayfreezedl_page,ee_dayf_inpage); //日冻结补存
//		}
//	
//		memcpy( Sclock.Clockbackup+1, Buf, 5 );//恢复当前时间(分时日月年)
//	}
//}

void Wr_Pretime_Hisfreeze()//结算写/清零写/校时写
{	
	unsigned char Buf[ee_prehistory_lenth+2];
	
	I2C_Read_Eeprom( ee_pre_history_page, ee_prehistory_inpage, Buf, ee_prehistory_lenth );//读上一次结算时间
	if( Cmp_Bcd_Inv( Buf,  Sclock.Clockbackup+1, 5 )==0 ) return;	//时间相等直接返回
	I2C_Write_Eeprom( ee_pre_history_page, ee_prehistory_inpage, Sclock.Clockbackup+1, ee_prehistory_lenth );//写上一次结算时间
}

void Wr_Pretime_Dayfreeze()//日冻结写/清零写/校时写/设置日冻结时间写
{
//	I2C_Write_Eeprom( ee_pre_dayfreeze_page, ee_predayfreeze_inpage, Sclock.Clockbackup+1, ee_predayfreeze_lenth );//写上一次日冻结时间
}

void Freeze_Pddata()		//保存停电统计数据
{
	unsigned char Result, Buf[8];
	
	if( month_change_flag || year_change_flag )
	{
		if( month_change_flag )
		{
			month_change_flag = 0;
			
			Get_Keep_Timer(8, Buf);//读月停电累计次数
			Get_Keep_Timer(9, Buf+4);//读月停电累计时间
			Result = Write_Event_Point(ee_monpowerdownn_inpage);
			I2C_Write_Eeprom( ee_powerdown_month_page+Result/8, (Result%8)*8, Buf, ee_powerdownmonth_lenth );
			{Clr_Otherdata(8);Clr_Otherdata(9);}//月停电统计数据
		}
		
		if( year_change_flag )
		{
			year_change_flag = 0;
			
			Get_Keep_Timer(10, Buf);//读年停电累计次数
			Get_Keep_Timer(11, Buf+4);//读年停电累计时间
			Result = Write_Event_Point(ee_yearpowerdownn_inpage);
			I2C_Write_Eeprom( ee_powerdown_year_page, (Result%8)*8, Buf, ee_powerdownyear_lenth );
			{Clr_Otherdata(10);Clr_Otherdata(11);}//年停电统计数据
		}
	}
	
	if( year_change_flag2 )
	{
		year_change_flag2 = 0;
		
		//低电压事件和高电压事件跨年处理
		if( lower_v_event_flag )
		{
//			Get_Keep_Timer(6, Buf+4);	//读低电压累计时间:返回4字节时间(Buf[4]~Buf[7])
//			Result = Read_Event_Point(ee_lowervn_inpage);
//			I2C_Write_Eeprom( ee_lowerv_note_page+Result, ee_lowervnote_inpage+8, Buf+4, 4 );//保存低电压累计时间(一年)
//			{lower_v_flag = 0;Current_Over_Count4 = 0;lower_v_event_flag = 0;Current_Over_Count41 = 0;Clr_Otherdata(6);Store_Meterstatus();}//低电压持续时间
			Note_Run_Event(ee_lowervn_inpage|0x80);//记录低电压事件(结束)
			{lower_v_flag = 0;Current_Over_Count4 = 0;lower_v_event_flag = 0;Current_Over_Count41 = 0;Store_Meterstatus();}//低电压持续时间	
		}
		else
		{
			Current_Over_Count41 = 0;
		}
			
		if( high_v_event_flag )
		{
//			Get_Keep_Timer(7, Buf+4);	//读高电压累计时间:返回4字节时间(Buf[4]~Buf[7])
//			Result = Read_Event_Point(ee_highvn_inpage);
//			I2C_Write_Eeprom( ee_highv_note_page+Result, ee_highvnote_inpage+8, Buf+4, 4 );//保存高电压累计时间(一年)
//			{high_v_flag = 0;Current_Over_Count5 = 0;high_v_event_flag = 0;Current_Over_Count51 = 0;Clr_Otherdata(7);Store_Meterstatus();}//高电压持续时间
			Note_Run_Event(ee_highvn_inpage|0x80);//记录高电压事件(结束)
			{high_v_flag = 0;Current_Over_Count5 = 0;high_v_event_flag = 0;Current_Over_Count51 = 0;Store_Meterstatus();}//高电压持续时间
		}
		else
		{
			Current_Over_Count51 = 0;
		}
	}
}


uint32		Uav_Temp_Day;	//计算1天平均电压 累计值
//Mode = 0:清除当日的电压合格率数据；1：清除当月的电压合格率数据
void InitVolSts( unsigned char Mode )
{
	memset( VolStatus[Mode&0x01].Total.B08, 0x00, ee_monthvolrun_lenth/2 ); //清除对应的电压合格率
	I2C_Write_Eeprom( ee_monthvolrun_page, ee_monthvolrun_inpage, VolStatus[0].Total.B08, ee_monthvolrun_lenth );
	
	if( Mode == 0 )	Uav_Temp_Day = 0;
}


//电压合格率运行处理函数
void VolPassRate( void )
{
	union B16_B08_2 Temp16;
	unsigned char Mode;
	
	Temp16.B08[0] = Emu_Data.U.B08[0];
	Temp16.B08[1] = Emu_Data.U.B08[1];

	for( Mode=0; Mode<2; Mode++ ) //日和月
	{
		if( VolStatus[Mode].Total.B32 < (VolStatus[Mode].HighTime.B32+VolStatus[Mode].LowTime.B32) )
		{
			InitVolSts(Mode);	//清除对应的电压合格率
		}
		
//		//计算平均电压
//		VolStatus[Mode].AverVol.B16 = Emu_Data.Uav.B32; //使用前1分钟的平均电压
		
		if( (Temp16.B16 > Byte2Short(VolLimit.ChkMaxVol.B08)) || (Temp16.B16 < Byte2Short(VolLimit.ChkMinVol.B08)) ) continue; //电压大于考核上限或电压小于考核下限不累加考核时间
	
		if( Sclock.Clockbackup[0] == 0x00 )
		{
			VolStatus[Mode].Total.B32++;
			
			if( Temp16.B16 > Byte2Short(VolLimit.MaxVolLmt.B08) ) //当前电压 > 电压上限值, 超上限时间加1
			{
				VolStatus[Mode].HighTime.B32++;
			}
			else if( Temp16.B16 < Byte2Short(VolLimit.MinVolLmt.B08) )	//当前电压 < 电压下限值, 超下限时间加1
			{
				VolStatus[Mode].LowTime.B32++;
			}
		}
		
		if( (Temp16.B16 == Byte2Short(VolLimit.ChkMaxVol.B08)) || (Temp16.B16 == Byte2Short(VolLimit.ChkMinVol.B08)) ) continue; //电压等于考核上限或电压等于考核下限不刷新历史数据
	
		if( Temp16.B16 > VolStatus[Mode].MaxVol.B16 )	//当前电压 > 历史最大电压, 更新历史最大电压为当前电压
		{
			if( (VolStatus[Mode].MaxMoment[2+Mode] == Sclock.Clockbackup[3+Mode]) || (VolStatus[Mode].MaxMoment[2+Mode] == 0) ) //不允许跨天/月
			{
				VolStatus[Mode].MaxVol.B16 = Temp16.B16;
				memcpy( VolStatus[Mode].MaxMoment, Sclock.Clockbackup+1, 4 );
			}
			else continue;
		}
		
		if( (Temp16.B16 < VolStatus[Mode].MinVol.B16) || (VolStatus[Mode].MinVol.B16 == 0) )	//当前电压 < 历史最小电压, 更新历史最小电压为当前电压
		{
			if( (VolStatus[Mode].MinMoment[2+Mode] == Sclock.Clockbackup[3+Mode]) || (VolStatus[Mode].MinMoment[2+Mode] == 0) ) //不允许跨天/月
			{
				VolStatus[Mode].MinVol.B16 = Temp16.B16;
				memcpy( VolStatus[Mode].MinMoment, Sclock.Clockbackup+1, 4 );
			}
			else continue;
		}
		
		//计算平均电压
		if( Mode == 0 ) //计算日平均电压
		{
			union B32_B08_2 S1_Temp;	
			
			if( (Uav_Temp_Day == 0) && VolStatus[Mode].AverVol_Cnt.B32 && VolStatus[Mode].AverVol.B16 ) //上电恢复
			{
				 S1_Temp.B32 = VolStatus[Mode].AverVol.B16;
				 Bcd2Hex_SS( S1_Temp.B08, S1_Temp.B08, 4 );
				 Uav_Temp_Day = S1_Temp.B32*VolStatus[Mode].AverVol_Cnt.B32;
			}
			
			Bcd2Hex_SS( Emu_Data.U.B08, S1_Temp.B08, 4 );
			Uav_Temp_Day += S1_Temp.B32;	//累计1天平均电压值
			VolStatus[Mode].AverVol_Cnt.B32++;
			
			S1_Temp.B32 = Uav_Temp_Day/VolStatus[Mode].AverVol_Cnt.B32;		//计算日平均电压
			Hex2Bcd_SS(S1_Temp.B08, S1_Temp.B08, 4);
			memcpy( VolStatus[Mode].AverVol.B08, S1_Temp.B08, 2);
		}
	}
}

//Mode = 0:计算日电压合格率数据；1：计算月电压合格率数据
void CalLoad( unsigned char *Buf, unsigned char Mode )
{
	union B32_B08_2 Rate, Temp32, Total, High, Low;

	Mode &= 0x01;
	if( VolStatus[Mode].Total.B32 < (VolStatus[Mode].HighTime.B32+VolStatus[Mode].LowTime.B32) )
	{
		InitVolSts(Mode);	//清除对应的电压合格率
	}
	
	//电压合格率记录
	Total.B32 = VolStatus[Mode].Total.B32;
	High.B32  = VolStatus[Mode].HighTime.B32;
	Low.B32   = VolStatus[Mode].LowTime.B32;

	Hex2Bcd_SS( Total.B08, Temp32.B08, 4 );
	memcpy( Buf, Temp32.B08, 3 );	//电压监测时间	3	XXXXXX	分
	
	if( Total.B32 )
	{
		Rate.B32 = (High.B32+Low.B32)*10000L/Total.B32;
		Temp32.B32 = 10000L-Rate.B32;
	}
	else
	{
		Rate.B32 = 0x00;
		Temp32.B32 = 0x00;
	}
	
	Hex2Bcd_SS( Temp32.B08, Temp32.B08, 4 );
	memcpy( Buf+3, Temp32.B08, 3 );	//电压合格率	3	XXXX.XX	%
	
	Hex2Bcd_SS( Rate.B08, Temp32.B08, 4 );
	memcpy( Buf+6, Temp32.B08, 3 );	//电压超限率	3	XXXX.XX	%
	
	Hex2Bcd_SS( High.B08, Temp32.B08, 4 );
	memcpy( Buf+9, Temp32.B08, 3 );	//电压超上限时间	3	XXXXXX	分

	Hex2Bcd_SS( Low.B08, Temp32.B08, 4 );
	memcpy( Buf+12, Temp32.B08, 3 );//电压超下限时间	3	XXXXXX	分
	
	memcpy( Buf+15, VolStatus[Mode].MaxVol.B08, 2 );	//最高电压	XXX.X	2	V
	memcpy( Buf+17, VolStatus[Mode].MaxMoment, 4 );

	memcpy( Buf+21, VolStatus[Mode].MinVol.B08, 2 );	//最低电压	XXX.X	2	V
	memcpy( Buf+23, VolStatus[Mode].MinMoment, 4 );
	
	memcpy( Buf+27, VolStatus[Mode].AverVol.B08, 2 );	//平均电压	XXX.X	2	V
}


void Judge_Relay_Delay()	//大电流延时跳闸判断
{
//	if( Relay_Mode != 0x55 )//内置继电器
	{
		if( over_xxx_flag && CurrentTimer )//拉闸时电流大于限值延时跳闸
		{
			if( relay_commu_open_flag && (Opendelaytimer == 0x00)  ) relay_delay_flag = 1;//置大电流延时跳闸标志
			else
			{
				CurrentTimer = Calculate_Timer(1);
				relay_delay_flag = 0;	//清大电流延时跳闸标志
			}
		}
		else relay_delay_flag = 0;	//清大电流延时跳闸标志
	}
//	else	relay_delay_flag = 0;	//清大电流延时跳闸标志
}				


void Closerelay1()               //闭合继电器
{
	if( Relay_Mode != 0x55 )//内置继电器
	{
		Relayctrl.Timer = Relaytimer_Delay_N;
		RELAYOFF2;
		__NOP();
		__NOP();
		RELAYON1;
	}
	else
	{
		if(Mode.Feature1&0x01)//脉冲方式
		{
			Relayctrl.Timer = 0;
			RELAYOFF3;
		}
		else
		{
			RELAYOFF3;
		}
	}
}

void Openrelay1()
{
	if( Relay_Mode != 0x55 )//内置继电器
	{
		Relayctrl.Timer = Relaytimer_Delay_N;
		RELAYOFF1;
		__NOP();
		__NOP();
		RELAYON2;
	}
	else
	{
		if(Mode.Feature1&0x01)//脉冲方式
		{
			Relayctrl.Timer = Relaytimer_Delay_W;
			RELAYON3;	
		}
		else
		{
			RELAYON3;
		}
	}
}

void Init_Metererrstatus()	//清零继电器故障状态
{
	relay_error = 0;
	Relayerror_Count  = 0;
	Relayerror_Count1 = Defrelayerrorcnt_s;//赋值起始次数
	Relayerror_Count2 = Defrelayerrorcnt_s;//赋值起始次数
	relay_failed_flag = 0;	//清继电器错误标志(上报)
	Store_Meterstatus();
}


void Closerelay()               //闭合继电器(带写状态字)
{
	if( (relay_status_flag == 0) && (relay_direct_flag == 0) ) return;
	
	Closerelay1();
	if( relay_status_flag == 1 )
	{
		if( relay_error ) Note_Run_Event(ee_relayerrn_inpage|0x80);	//负荷开关异常结束记录
		relay_status_flag = 0;
		relay_success_flag = 0;	//清继电器成功标志
		relay_success2_flag = 0;
		Init_Metererrstatus();	//清零继电器故障状态
		Note_Relay_Event();//做合闸记录
	}
	Relay_Space_Timer = 0;	
}


void Openrelay()                //断开继电器(带写状态字)	
{
	if( relay_status_flag && (relay_direct_flag ==0 ) )  return;
	
	Judge_Relay_Delay();	//大电流延时跳闸判断
	if( relay_delay_flag ) return;	//大电流延时拉闸
	
	Openrelay1();
	if( relay_status_flag == 0 ) 
	{
		if( relay_commu_open_flag )
		{
			Opendelaytimer = 0x00;	//已经拉闸则清拉闸延时
		}
		
		if( relay_error ) Note_Run_Event(ee_relayerrn_inpage|0x80);	//负荷开关异常结束记录
		relay_status_flag = 1;
		relay_success_flag = 0;	//清继电器成功标志
		relay_success2_flag = 0;
		if( Relay_Mode == 0x55 ) relay_cleardl_flag = 0; //清外置表刚清零标志
		Init_Metererrstatus();	//清零继电器故障状态
		Note_Relay_Event();//做拉闸记录
	}
	Relay_Space_Timer = 0;
}


void Mt_Alarmstatus_Judge()	//电表报警状态判断
{
	Esam_Para_Verify();	//报警金额1,2等参数(ESAM一类部分参数)校验

	if( EA_ON && ( below_70u_flag == 0 ) )
	{
		//继电器控制
		if ( relay_commu_disable_close_flag )//不允许闭合继电器(只有插卡才可以清零)
		{
			Openrelay();
		}
		else if ( relay_commu_close_flag )//保电优先级最高
		{
			Closerelay();
		}
		else if( (relay_commu_open_flag && (Opendelaytimer == 0x00)) )//通讯断开继电器优先级次之
		{
			Openrelay();
		}
		else//电量决定继电器闭合
		{
			Closerelay();
		}
		
		relay_direct_flag = 0;//清继电器直接动作标志
	}
	
	run_alarm_flag = 0;		

}
