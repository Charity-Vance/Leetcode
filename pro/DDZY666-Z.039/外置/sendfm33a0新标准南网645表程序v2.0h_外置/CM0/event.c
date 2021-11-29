#include "ex_func.h"
#include "ex_var.h" 
#include "FM32L0XX.h"  
#include <string.h>


const struct HisEvent_STR ecode   EventTable[EventNum]=
{
	0x3001,	ee_cleardl_note_page,		ee_cleardlnote_inpage,		ee_cleardlnote_lenth,		3*8+1,	//电表清零
	0x3003,	ee_clearevent_note_page,	ee_cleareventknote_inpage,	ee_cleareventnote_lenth,	3*8+3,	//事件清零
	0x0311,	ee_powerdown_note_page,		ee_powerdownnote_inpage,	ee_powerdownnote_lenth,		2*8+7, 	//掉电记录++
	0x3004,	ee_setclock_note_page,		ee_setclocknote_inpage,		ee_setclocknote_lenth,		3*8+4,	//设置时钟
	0x300d,	ee_opencover_note_page,		ee_opencovernote_inpage,	ee_opencovernote_lenth,		1*8+2,	//开表盖
	0x1901, ee_maxi_note_page, 		ee_maxinote_inpage,		ee_maxinote_lenth,      	2*8+4,	//过流
	0x1d00,	ee_openrelay_note_page,		ee_openrelaynote_inpage,	ee_openrelaynote_lenth,		1*8+6,	//拉闸           
	0x1e00,	ee_closerelay_note_page,	ee_closerelaynote_inpage,	ee_closerelaynote_lenth,	1*8+7,	//合闸         
	0x3000,	ee_program_note_page,		ee_programnote_inpage,		ee_programnote_lenth,		3*8+0,	//编程记录
	0x3006,	ee_shiqurecord_page,		70,				ee_shiqurecord_lenth,		3*8+6,	//时区表编程
	0x3005,	ee_shiduanrecord_page,		70,				ee_shiduanrecord_lenth,		3*8+5,	//时段表编程
	0x300c,	ee_jieshuanrecord_page,		ee_jieshuanrecord_inpage,	ee_jieshuanrecord_lenth,	4*8+4,	//结算日编程
	0x3012, ee_keysetrecord_page, 		ee_keysetrecord_inpage, 	ee_keysetrecord_len,		4*8+7,	//密钥更新编程     
	0x3009,	ee_combstatusrecord_page,	ee_combstatusrecord_inpage,	ee_combstatusrecord_lenth,	4*8+1,	//有功组合方式编程
	0x300a,	ee_rp1combstatusrecord_page,	ee_rp1combstatusrecord_inpage,	ee_rp1combstatusrecord_lenth,	4*8+2,	//无功组合方式1编程
	0x300b,	ee_rp2combstatusrecord_page,	ee_rp2combstatusrecord_inpage,	ee_rp2combstatusrecord_lenth,	4*8+3,	//无功组合方式2编程
	0x3600,	ee_relayerr_note_page,		ee_relayerrnote_inpage,		ee_relayerrnote_lenth,		0*8+0,	//负荷开关误动作记录
	0x3700,	ee_powererr_note_page,		ee_powererrnote_inpage,		ee_powererrnote_lenth,		1*8+5,	//电源异常记录
	0x3007, ee_week_note_page,		ee_week_note_inpage,		ee_week_note_len,		3*8+7,	//周休日编程
	0x2200,	ee_batterlow_note_page,		ee_batterlownote_inpage,	ee_batterlownote_len,		0*8+3,	//电池欠压
	0x3010,	ee_jtpricerecord_page,		ee_jtpricerecord_inpage,	ee_jtpricerecord_len,		4*8+6,	//阶梯表编程
	0x3050,	ee_clockerrrecord_page,		ee_clockerrrecord_inpage,	ee_clockerrrecord_len,		0*8+7,	//时钟故障记录
	0x4e00,	ee_calerr_note_page,		ee_calerrnote_inpage,		ee_calerrnote_len,		0xff,	//计量芯片故障记录--
	0x3051,	ee_gbsetclock_note_page,	ee_gbsetclocknote_inpage,	ee_gbsetclocknote_lenth,	0xff,	//广播校时--
	0xbd0b, ee_nlineerrrecord_page,     	ee_nlineerrrecord_inpage,   	ee_nlineerrrecord_len,  	0xff,   //零线电流异常--
	
	0x1001,	ee_lostv_note_page,		ee_lostvnote_inpage,		ee_lostvnote_len,		2*8+0,	//失压记录
	0xbd07,	ee_lowerv_note_page,		ee_lowervnote_inpage,		ee_lowervnote_len,		2*8+2,	//低电压事件记录--
	0xbd04,	ee_highv_note_page,		ee_highvnote_inpage,		ee_highvnote_len,		2*8+1,	//高电压事件记录--
	0x5400,	ee_batchange_note_page,		ee_batchangenote_inpage,	ee_batchangenote_len,		0xff,	//电池更换记录--
	0x5101,	ee_commerr_note_page,		ee_commerrnote_inpage,		ee_commerrnote_len,		0xff,	//通讯模块异常--
	0x5201,	ee_commchange_note_page,	ee_commchangenote_inpage,	ee_commchangenote_len,		0xff,	//通讯模块更换--
	0x7004,	ee_poweroff_note_page,		ee_poweroffnote_inpage,		ee_poweroffnote_lenth,		0xff, 	//掉电上报记录
	0x7005,	ee_poweron_note_page,		ee_poweronnote_inpage,		ee_poweronnote_lenth,		0xff, 	//上电上报记录
	0x7000,	ee_dayvolpass_note_page,	ee_dayvolpassnote_inpage,	ee_dayvolpassnote_len,		0xff,	//日电压合格率
	0x1000, ee_monvolpass_note_page,     	ee_monvolpassnote_inpage,   	ee_monvolpassnote_len,  	0xff,   //月电压合格率
	0xc002,	ee_powerdown_month_page,	ee_powerdownmonth_inpage,	ee_powerdownmonth_lenth,	0xff,	//月停电统计
	0xc003, ee_powerdown_year_page,     	ee_powerdownyear_inpage,   	ee_powerdownyear_lenth,  	0xff,   //年停电统计
};


void Exchange(unsigned char *BufA, unsigned char *BufB, unsigned char Len )
{
	unsigned char n;
	for( n=0; n<Len; n++ )
	{
		BufA[n] = BufB[Len-1-n];//交换数据
	}
}

void Inverse( unsigned char *Buf, unsigned char Len )
{
	unsigned char i, Temp08;
	
	for( i=0; i<Len/2; i++ )
	{
		Temp08 = Buf[i];
		Buf[i] = Buf[Len-1-i];
		Buf[Len-1-i] = Temp08;//交换数据
	}
}


//void Number_Add1_Direct(unsigned char *BufA) //其他加1
//{	
//	unsigned char  BufB[4];
//	union B32_B08 Add;
//	
//	if ( ( BufA[0]==0xff) || (BufA[1]==0xff) || (BufA[2]==0xff) )
//	{
//		BufA[0] = 0;//非法数据清零
//		BufA[1] = 0;
//		BufA[2] = 0;
//	}
//	BufB[0] = 0;
//	BufB[1] = BufA[2];
//	BufB[2] = BufA[1];
//	BufB[3] = BufA[0];	//低字节在前变成高字节在前
//	Int2Byte( 1, Add.B08 );	//增量(高节在前)
//	Add_Bcd( BufB, Add.B08, 4 );
//	BufA[0] = BufB[3];	//高字节在前变成低字节在前
//	BufA[1] = BufB[2];
//	BufA[2] = BufB[1];
//}


void Number_Add1(unsigned char Offset)	//事件记录次数加1
{
//	与指针处理合并无需单独累加
	if( (Offset!=ee_openrelayn_inpage)&&(Offset!=ee_closerelayn_inpage) )	//拉合闸在成功以后上报
	{
		if( (Offset!=ee_clearn_inpage) || (Key_Status==1) )	//私钥下允许清零上报
		{
			Set_Reportdata(EventTable[Offset-ee_clearn_inpage].offset2);	//进行事件上报
		}
	}	
}


unsigned char Read_Event_Number( unsigned char *BufA, unsigned char Offset )
{
	unsigned char Buf[ee_eventpoint_lenth+2];
	
	ReadE2WithBackup( ee_event_point_page+2*((Offset-1)/12), ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );
	Hex2Bcd_SS( Buf+5*((Offset-1)%12)+0, BufA,  3 );//低字节之前,BCD码
	
	return ((Offset-ee_clearn_inpage)*3);
}


const uint16 code MaxRecNum[] = {
	0, max_timingfreeze_p, 3, 2, 2, 2, 2, //NULL,定时,瞬时,约定冻结1~4
	max_ploadrec_p, max_hourfreeze_p, max_dayfreeze_p, max_histroy_p, max_histroy_p, 0, //分钟,小时,日,月,结算日,预留
	max_eventrecord_p, max_eventrecord_p, max_eventrecord_p, max_eventrecord_p,	//清零~
	max_eventrecord_p, max_eventrecord_p, max_eventrecord_p, max_eventrecord_p, max_eventrecord_p, //开盖~
	2, 2, max_eventrecord_p, 2,     //时区表编程,时段表,结算日编程,密钥更新           
	max_eventrecord_p, max_eventrecord_p, max_eventrecord_p, max_eventrecord_p, max_eventrecord_p,//组合方式编程
	2, max_eventrecord_p, 2, max_eventrecord_p,	//周休日编程,电池欠压,阶梯表编程,时钟故障
	max_eventrecord_p, max_gbsetclock_p, max_eventrecord_p, //计量芯片故障记录,广播校时,零线异常
	max_eventrecord_p, max_eventrecord_p, max_eventrecord_p, //失压记录,低电压事件记录,高电压事件记录
	max_eventrecord_p, max_eventrecord_p, max_eventrecord_p,max_eventrecord_p,max_eventrecord_p, //电池更换记录,通讯模块异常记录,通讯模块更换记录,掉电上报记录,上电上报记录
	max_dayvolpass_p, max_monvolpass_p, max_powerdownmonth_p, max_powerdownyear_p //日电压合格率,月电压合格率,月停电统计,年停电统计
};
	
	
unsigned char Read_Event_Point( unsigned char Inpage )
{
	unsigned long Result;
	unsigned char Buf[ee_eventpoint_lenth+2];
	unsigned char Page, Ptr;

	Page = ee_event_point_page+2*((Inpage-1)/12);
	Ptr = 5*((Inpage-1)%12);
	
	ReadE2WithBackup( Page, ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );
	Result = 0;
	memcpy( (uint08*)(&Result), Buf+Ptr, 3 );
	if( Result ) Result--;
	
	return ( Result%MaxRecNum[Inpage] );
}


unsigned char Write_Event_Point( unsigned char Inpage )	
{
	unsigned long Result;
	unsigned char Buf[ee_eventpoint_lenth+2];
	unsigned char Page, Ptr;
	
	Page = ee_event_point_page+2*((Inpage-1)/12);
	Ptr = 5*((Inpage-1)%12);
	
	ReadE2WithBackup( Page, ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );
	Result = 0;
	memcpy( (uint08*)(&Result), Buf+Ptr+3, 2 );
	if( IsFlashRec(Inpage) ) 
	{
		SynEe.Enable = 1; //启动一次同步EE
		Result++;
	}
	else if( Result < MaxRecNum[Inpage] ) 
		Result++; //累加有效次数
	memcpy( Buf+Ptr+3, (uint08*)(&Result), 2 );

	Result = 0;
	memcpy( (uint08*)(&Result), Buf+Ptr, 3 );
	Result++; //累加记录总次数
	memcpy( Buf+Ptr, (uint08*)(&Result), 3 );
	WriteE2WithBackup( Page, ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );

	Result--;
	if( IsFlashRec(Inpage) ) Result = 0;
	return ( Result%MaxRecNum[Inpage] );
}


unsigned char RdRecTimes( unsigned char Inpage )//返回有效指针
{
	unsigned long Result;
	
	//有效次数
	Result = GetValtimes( Inpage, 0 );
	if( Result > MaxRecNum[Inpage] ) Result = MaxRecNum[Inpage];
	
	return ( Result );
}

void ClrRecTimes( unsigned char Inpage, unsigned char mode )//清有效指针
{
	unsigned char Temp1;
	unsigned char Buf[ee_eventpoint_lenth+2];
	
	if( mode == 1 )//清零(单个事件清零)
	{
		ReadE2WithBackup( ee_event_point_page+2*((Inpage-1)/12), ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );
		memset( Buf+5*((Inpage-1)%12), 0, 5 );
		WriteE2WithBackup( ee_event_point_page+2*((Inpage-1)/12), ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );
		Clr_Reportdata(Inpage);	//清单项上报状态字和新增次数(有事件记录类)
	}
	else if(mode == 0x55)//事件全清
	{
		{Report_Data[0] = 0;Clr_Reportnum(0);}	//清上报状态字和新增次数
		{Report_Data[1] = 0;Clr_Reportnum(1);}	//清上报状态字和新增次数
		for( Temp1=ee_clearn_inpage+2; Temp1<ee_eventpoint_lenth; Temp1++ )
		{
			Clr_Reportdata(Temp1);	//清上报状态字和新增次数(有事件记录类)
		}
		
		Reset_Rep_Timer = 0;

		ReadE2WithBackup( ee_event_point_page+2, ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );
		memset( Buf+10, 0, sizeof(Buf)-10 ); //保留电表清零、事件清零的指针
		WriteE2WithBackup( ee_event_point_page+2, ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );
		
		memset( Buf, 0, sizeof(Buf) );
		WriteE2WithBackup( ee_event_point_page+4, ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );
		WriteE2WithBackup( ee_event_point_page+6, ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );
		WriteE2WithBackup( ee_event_point_page+8, ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );
	}
	else if(mode == 0xaa)//电表清零
	{
		ReadE2WithBackup( ee_event_point_page+2, ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );
		memset( Buf+5, 0, sizeof(Buf)-5 ); //保留电表清零的指针
		WriteE2WithBackup( ee_event_point_page+2, ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );
		
		memset( Buf, 0, sizeof(Buf) );
		WriteE2WithBackup( ee_event_point_page+0, ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );
		WriteE2WithBackup( ee_event_point_page+4, ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );
		WriteE2WithBackup( ee_event_point_page+6, ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );
		WriteE2WithBackup( ee_event_point_page+8, ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );
	}
	else if(mode == 0xff)//出厂全清
	{
		memset( Buf, 0, sizeof(Buf) );
		for( Temp1=0; Temp1<8; Temp1++ )
		{
			I2C_Write_Eeprom( ee_event_point_page+Temp1, ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );
		}
	}
	else
	{
		return;
	}
	
	if( mode != 1 )
	{
		System_Status &= (~0x3e);//清已经上报标志,清零后重新上报
		
		//允许重新上报
		Clear_Wdt();
		Cover.Status = 0;	//开盖则重新产生开盖记录
		Init_Metererrstatus();	//清零继电器故障状态
		first_prog_flag = 0;
		{EmuErrCnt = 0;cal_err_flag=0;}//计量故障则重新产生
		
		{Nline_Err_Count = 0;nline_err_flag = 0;Clr_Otherdata(0);}//零线电流异常
		{load_over_flag = 0;Current_Over_Count2 = 0;Clr_Otherdata(1);}//过流持续时间		
		{low_voltage_flag = 0;Bat_Delay_Timer = 0;Clr_Otherdata(2);} //电池欠压总累计时间(4)
		{below_60u_flag = 0;Voltage_Low_Count = 0;Clr_Otherdata(3);} //掉电总累计时间(4)
		{lost_v_flag = 0;Current_Over_Count3 = 0;Clr_Otherdata(5);Lost_Aver_I=0;Lost_V_Timer=0;}//失压持续时间
		{lower_v_flag = 0;Current_Over_Count4 = 0;lower_v_event_flag = 0;Current_Over_Count41 = 0;Clr_Otherdata(6);}//低电压持续时间
		{high_v_flag = 0;Current_Over_Count5 = 0;high_v_event_flag = 0;Current_Over_Count51 = 0;Clr_Otherdata(7);}//高电压持续时间
		{commmodule_failed_flag = 0;if(Mod_Comm_Timer1==0&&Mod_Comm_Timer2==0) Mod_Comm_Timer1 = Mod_Comm_Timer_delay1;}//通信模块异常	
		{commmodule_open_flag = 0;commmodule_start_flag = 0;}//通信模块更换
		Store_Meterstatus();	
		Clr_Otherdata(4); //电池工作时间
		
		{InitVolSts(0);} //清当前日电压合格率数据
		{InitVolSts(1);} //清当前月电压合格率数据
		{Clr_Otherdata(8);Clr_Otherdata(9);}//月停电统计数据
		{Clr_Otherdata(10);Clr_Otherdata(11);}//年停电统计数据
	}
	else
	{
		if( Inpage == ee_covern_inpage ) Cover.Status = 0;	//开盖则重新产生开盖记录
		else if( Inpage == ee_relayerrn_inpage ) Init_Metererrstatus();//清零继电器故障状态
		else if( Inpage == ee_programn_inpage ) first_prog_flag = 0;//编程记录
		else if( Inpage == ee_calerrn_inpage ) {EmuErrCnt = 0;cal_err_flag=0;}//计量故障则重新产生
		else if( Inpage == ee_nlineerrn_inpage ) {Nline_Err_Count = 0;nline_err_flag = 0;Clr_Otherdata(0);}//零线电流异常
		else if( Inpage == ee_maxi_inpage ) {load_over_flag = 0;Current_Over_Count2 = 0;Clr_Otherdata(1);}//过流持续时间		
		else if( Inpage == ee_batterlow_inpage ) {low_voltage_flag = 0;Bat_Delay_Timer = 0;Clr_Otherdata(2);Store_Meterstatus();} //电池欠压总累计时间(4)
		else if( Inpage == ee_powerdownn_inpage ) {below_60u_flag = 0;Voltage_Low_Count = 0;Clr_Otherdata(3);} //掉电总累计时间(4)
		else if( Inpage == ee_lostvn_inpage ) {lost_v_flag = 0;Current_Over_Count3 = 0;Clr_Otherdata(5);Lost_Aver_I=0;Lost_V_Timer=0;}//失压持续时间	
		else if( Inpage == ee_lowervn_inpage ) {lower_v_flag = 0;Current_Over_Count4 = 0;lower_v_event_flag = 0;Current_Over_Count41 = 0;Clr_Otherdata(6);Store_Meterstatus();}//低电压持续时间
		else if( Inpage == ee_highvn_inpage ) {high_v_flag = 0;Current_Over_Count5 = 0;high_v_event_flag = 0;Current_Over_Count51 = 0;Clr_Otherdata(7);Store_Meterstatus();}//高电压持续时间
		else if( Inpage == ee_commerrn_inpage ) {commmodule_failed_flag = 0;if(Mod_Comm_Timer1==0&&Mod_Comm_Timer2==0) Mod_Comm_Timer1 = Mod_Comm_Timer_delay1;Store_Meterstatus();}//置通信模块异常
		else if( Inpage == ee_commchangen_inpage ) {commmodule_open_flag = 0;commmodule_start_flag = 0;Store_Meterstatus();}//通信模块更换
		
		else if( Inpage == ee_dayvolpassn_inpage ) {InitVolSts(0);} //清当前日电压合格率数据
		else if( Inpage == ee_monvolpassn_inpage ) {InitVolSts(1);} //清当前月电压合格率数据
		else if( Inpage == ee_monpowerdownn_inpage ) {Clr_Otherdata(8);Clr_Otherdata(9);}//月停电统计数据
		else if( Inpage == ee_yearpowerdownn_inpage ) {Clr_Otherdata(10);Clr_Otherdata(11);}//年停电统计数据
	}
}

unsigned char Event_Record( unsigned char Inpage )
{
	unsigned char i, result, ptr, offset, len;
	unsigned int  page;
	
	ptr = (Inpage&0x7F);
	if( ptr < ee_clearn_inpage ) return 0x00;
	
	page   = EventTable[ptr-ee_clearn_inpage].page;
	offset = EventTable[ptr-ee_clearn_inpage].offset;
	len    = EventTable[ptr-ee_clearn_inpage].len;
	
	if( (Inpage&0x80) == 0x00 ) //事件记录为单次记录
	{
		if( (ptr != ee_setclockn_inpage) && (ptr != ee_gbsclockn_inpage) ) //设置时钟和广播校时不在此函数记录发生时刻
		{
			memcpy( Eeprom.Buffer, Sclock.Clockbackup, 6 ); 
		}
		
		Number_Add1(ptr);
		
		result = Write_Event_Point(ptr);
	}
	else	//事件记录分成开始和结束两次
	{
		result = Read_Event_Point(ptr);
		I2C_Read_Eeprom( page+result, offset, Eeprom.Buffer, len );	//时间

		if( RdRecTimes( ptr ) ) //次数为0不允许记录
		{
			if (ptr == ee_programn_inpage)
			{
				for( i=0; i<4*9; i++ )
				{
					Eeprom.Buffer[49-i] = Eeprom.Buffer[45-i];
				}
				memcpy( Eeprom.Buffer+10, Eeprom.Buffer+50, 4 );	//数据标识(4)
			}
			else
			{
				memcpy( Eeprom.Buffer+6, Sclock.Clockbackup, 6 );
				
				if( (ptr != ee_powererrn_inpage) && (ptr != ee_lowervn_inpage) && (ptr != ee_highvn_inpage) )//除电源异常/低电压/高电压事件以外,其他需要记录结束时刻电量
				{
					if( ptr == ee_powerdownn_inpage )	//掉电
					{
						union B32_B08 Temp32;
						memcpy( Temp32.B08, Eeprom.Buffer+44, 3 );//保存发生时刻前3分钟的平均电流
						DltoEepromBuf( len-16-3 );
						Comp_RpdltoEepromBuf( len-8-3 );
						memcpy( Eeprom.Buffer+44, Temp32.B08, 3 );//恢复发生时刻前3分钟的平均电流
					}
					else if( ptr == ee_covern_inpage || ptr == ee_clockerrn_inpage || ptr == ee_nlineerrn_inpage )//开盖、时钟故障、零线异常
					{
						DltoEepromBuf( len-24 );
						Four_RpdltoEepromBuf( len-16 );
					}
					else if( ptr == ee_maxi_inpage )	//过流
					{
						DltoEepromBuf( len-16 );
						Comp_RpdltoEepromBuf( len-8 );
					}
					else if( ptr == ee_lostvn_inpage )	//失压
					{
						DltoEepromBuf( len-16-4 );
						Comp_RpdltoEepromBuf( len-8-4 );
						
						Calculate_Ah( Eeprom.Buffer+len-4 );//计算安时数
						{Lost_Aver_I=0;Lost_V_Timer=0;}						
					}
					else
					{
						DltoEepromBuf( len-8 ); //负荷开关误动作开始和结束记录/时钟故障/计量故障/电池更换/通信模块异常/通信模块变更
					}
				}
				else if( ptr == ee_lowervn_inpage ||  ptr == ee_highvn_inpage ) //低电压/高电压事件
				{
					memcpy( Eeprom.Buffer+14, Emu_Data.Uav.B08, 2 );	//电压xxx.x
					Eeprom.Buffer[6] = 0x00; //高电压事件和低电压事件的结束时间为下1年的1月1日0点0分
					Eeprom.Buffer[7] = 0x00;
					Eeprom.Buffer[8] = 0x00;
					Eeprom.Buffer[9] = 0x01;
					Eeprom.Buffer[10]= 0x01;
					Eeprom.Buffer[11]= Hex_To_Bcd(Bcd_To_Hex(Eeprom.Buffer[5])+1);
				}
			}
		}
	}
	
	if( ptr == ee_gbsclockn_inpage ) //广播校时
		I2C_Write_Eeprom( page+result/3, (result%3)*len, Eeprom.Buffer, len );
	else
		I2C_Write_Eeprom( page+result, offset, Eeprom.Buffer, len );
	
	return (result);
}


void Read_Uip_Data( unsigned char st )	//读电压电流功率功率因数(用于记录)
{
	memcpy( Eeprom.Buffer+st+0,  Emu_Data.U.B08, 2 );	//电压xxx.x
	memcpy( Eeprom.Buffer+st+2,  Emu_Data.I1.B08, 3 );	//电流xxx.xxx
	if( dl_back_flag ) Eeprom.Buffer[st+4] |= 0x80;
	memcpy( Eeprom.Buffer+st+5,  Emu_Data.P1.B08, 3 );	//有功功率xx.xxxx
	if( dl_back_flag ) Eeprom.Buffer[st+7] |= 0x80;
	memcpy( Eeprom.Buffer+st+8,  Emu_Data.Q1.B08, 3 );	//无功功率xx.xxxx
	if( dl_back_flag2 ) Eeprom.Buffer[st+10] |= 0x80;
	memcpy( Eeprom.Buffer+st+11,  Emu_Data.Cosa.B08, 2 );	//功率因数x.xxx
	if( dl_back_flag ) Eeprom.Buffer[st+12] |= 0x80;
}


void DltoEepromBuf( unsigned char st ) //准备有功总电量
{
	memcpy( Eeprom.Buffer+st+0,  Fwdl.Pluse[0].B08, 4 );	//正向总电量(脉冲数)
	memcpy( Eeprom.Buffer+st+4,  Bkdl.Pluse[0].B08, 4 );	//反向总电量(脉冲数)
}

void Comp_RpdltoEepromBuf( unsigned char st )	//准备组合无功总电量
{
	unsigned char i;
	unsigned char Buf[max_dl_lenth*4];
	union B64_B08_2 Temp64;
	
	for(i=0; i<4; i++) //四象限无功
	{
		memcpy( Buf+max_dl_lenth*i, Rpdl[i].Pluse[0].B08, max_dl_lenth );//四象限无功总电量(脉冲数)
	}
	
	CalZhuhe( Buf, Temp64.B08, Mode.Rpcomp[0], 0xff );	//组合无功总电量1(脉冲数)
	memcpy( Eeprom.Buffer+st, Temp64.B08, 4 );		//组合无功总电量1(脉冲数)
	CalZhuhe( Buf, Temp64.B08, Mode.Rpcomp[1], 0xff );	//组合无功总电量2(脉冲数)
	memcpy( Eeprom.Buffer+st+4, Temp64.B08, 4 );		//组合无功总电量2(脉冲数)
}

void Four_RpdltoEepromBuf( unsigned char st )	//准备四象限无功总电量
{
	unsigned char i;
	
	for(i=0; i<4; i++) //四象限无功
	{
		memcpy( Eeprom.Buffer+st+4*i, Rpdl[i].Pluse[0].B08, 4 );	//四象限无功总电量(脉冲数)
	}
}


void Note_Relay_Event()//记录断开闭合继电器事件
{
	I2C_Read_Eeprom( ee_operatorcode_page, ee_operatorcode_inpage, Eeprom.Buffer+6, 4 );//读4字节操作者代码

	DltoEepromBuf( 10 );
	Four_RpdltoEepromBuf( 18 );
	
	if( relay_status_flag == 0 ) //合闸记录
	{
		Event_Record(ee_closerelayn_inpage);
	}
	else
	{
		Event_Record(ee_openrelayn_inpage);
	}
	
	if( Def_Relay_ActL != Def_Relay_Det )
	{
		if(PowerDetCnt0 <= 2)//如果电压低于0.8Un继电器发生动作,此时因无法进入继电器检测,则继电器实际状态默认为命令状态
		{
			real_relaystatus_flag = relay_status_flag;
			comm_relaystatus_flag = real_relaystatus_flag;//刷新继电器实际状态(通讯bit4专用)
		}
	}
}


//负荷开关误动作开始和结束记录/零线电流不平衡/掉电记录/开盖记录/过流记录/时钟故障/计量故障/电源异常/通信模块异常/通信模块变更
void Note_Run_Event( unsigned char Type )	//记录运行事件记录
{
	unsigned char Buf[6], Temp08;
	
	if( (Type&0x80) ==  0x00 )	//开始记录
	{
		memset( Eeprom.Buffer, 0, 64 );

		if( Type == ee_relayerrn_inpage )	//负荷开关异常
		{
			if( (Relay_Mode == 0x55) && (relay_status_flag == 0) && (relay_success_flag==0) ) return;	//外置继电器表合闸成功才做负荷开关误动作记录和上报
			
			if( relay_failed_flag ) return;		//故障期间只做一次记录
			else
			{
				relay_failed_flag = 1;		//置继电器错误标志
				Store_Meterstatus();
			}
			
			Eeprom.Buffer[12] = real_relaystatus_flag;	//继电器状态
			DltoEepromBuf( 13 );
		}
		else if( Type == ee_lowervn_inpage ||  Type == ee_highvn_inpage ) //低电压/高电压事件
		{
			memcpy( Eeprom.Buffer+12, Emu_Data.Uav.B08, 2 );	//电压xxx.x
		}
		else if( Type == ee_commerrn_inpage )	//通信模块异常
		{
			memcpy( Eeprom.Buffer+12, Esam_Para.Zb_Id, 6 );	//模块ID6
			DltoEepromBuf( 18 );
		}
		else	//掉电记录/开盖记录/过流记录/时钟故障/计量故障/电源异常/电池更换/通信模块变更
		{
			DltoEepromBuf( 12 );
			
			if( Type == ee_powerdownn_inpage )	//掉电
			{
				Comp_RpdltoEepromBuf( 20 );
				if( Emu_Data.Iav[2].B32 == 0xffffffff ) memset( Eeprom.Buffer+44, 0xff, 3 );
				else
				{
					union B32_B08_2 Temp32[4];
			
					Bcd2Hex_SS( Emu_Data.Iav[0].B08, Temp32[0].B08, 4 );
					Bcd2Hex_SS( Emu_Data.Iav[1].B08, Temp32[1].B08, 4 );
					Bcd2Hex_SS( Emu_Data.Iav[2].B08, Temp32[2].B08, 4 );
					Temp32[3].B32 = (Temp32[0].B32+Temp32[1].B32+Temp32[2].B32)/3;
					Hex2Bcd_SS( Temp32[3].B08, Temp32[3].B08, 4 );
					memcpy( Eeprom.Buffer+44, Temp32[3].B08, 3 );//前3分钟的平均电流
				}
				Keeptime.Times[8]++;	//月停电累计次数加1
 		 		Keeptime.Times[10]++;	//年停电累计次数加1
			}
			else if( Type == ee_covern_inpage || Type == ee_clockerrn_inpage || Type == ee_nlineerrn_inpage )//开盖、时钟故障、零线异常
			{
				Four_RpdltoEepromBuf( 20 );
			}
			else if( Type == ee_maxi_inpage || Type == ee_lostvn_inpage  ) //过流、失压
			{
				Comp_RpdltoEepromBuf( 20 );
				Read_Uip_Data( 28 );		//读电压电流功率功率因数(用于记录)
			}
		}
	}
	else
	{
		if((Type&0x7F) == ee_relayerrn_inpage )	//负荷开关异常
		{
			if( relay_failed_flag == 0 ) return;		//故障期间只做一次记录
			
			Temp08 = Read_Event_Point( ee_relayerrn_inpage );
			I2C_Read_Eeprom( ee_relayerr_note_page+Temp08, ee_relayerrnote_inpage+6, Buf, 6 );
			if( ChkBufZero(Buf,6) ) return;			//结束时间非0表示已经记录过
		}
	}
	
	Event_Record( Type );
}


unsigned int Read_Load_Point( unsigned char Inpage )
{
	unsigned long result=0;
	
	memcpy( (uint08*)(&result), Load.Point+5*Inpage+0, 3 );

	if( result >= max_ploadrec_p ) return 0;	//数据非法
	return ( result );
}


unsigned int Write_Load_Point( unsigned char Inpage )	
{
	unsigned long result=0;
	
	SynEe.Enable = 1; //启动一次同步EE
	
	//同步记录数+1
	memcpy( (uint08*)(&result), Load.Point+5*Inpage+3, 2 );
	result++;
	memcpy( Load.Point+5*Inpage+3, (uint08*)(&result), 2 );

	//总记录数+1
	result = 0;
	memcpy( (uint08*)(&result), Load.Point+5*Inpage, 3 );
	result++;
	memcpy( Load.Point+5*Inpage, (uint08*)(&result), 3 );

	Load.Crc16.B16 = Crc_16Bits( Load.Point, ee_loadpoint_lenth ); //CRC计算

	result--;
	return ( result%max_ploadrec_p );
}


//该函数输出当前时间针对2000年1月1日0点0分的分钟数差值
//每月其始的相对天数
const uint16 code gui_MonthBeginDay[12] = {0, 31, 59, 90,120, 151, 181, 212, 243, 273, 304, 334};
uint16 CalcAbsDay(unsigned char * psTm)
{//以2000年1月1日为基准到现在的所有天数,因此时间不能在2000年之前(其实2000年用00表示,百年以上都略去)
	uint08 ucYear = Bcd_To_Hex(psTm[4]);        //年转换成Hex
	uint08 ucMonth = Bcd_To_Hex(psTm[3])-1;      //月转换成Hex
	uint08 ucDay = Bcd_To_Hex(psTm[2]) - 1;      //日转换成Hex
	if((ucYear & 0x03) == 0)                            //判断是否过了闰年的2月
	{
	    if(ucMonth >= 2)
	        ucDay++;                                    //再加一天
	}
	else
	{
	    ucDay++;                                        //非闰年加上00年闰月多出来的一天
	}
	//year >> 2,是加上过去的整4年的闰年的一天
	return ( (uint16)ucYear*365 + gui_MonthBeginDay[ucMonth] + (ucDay + (ucYear>>2)) );
}
uint16 CalcAbsMin(unsigned char* psTm)
{
	//以当日00时00分00秒为基准秒
	uint08 ucMin = Bcd_To_Hex(psTm[0]);       //分转换成Hex
	uint08 ucHour = Bcd_To_Hex(psTm[1]);        //时转换成Hex
	return ( (uint16)ucHour*60 + ucMin );
}
//[0]分[1]时[2]日[3]月[4]年
unsigned long int CalcTime(unsigned char* psTm)
{
    	uint16 Temp16a,Temp16b;
    	Temp16a = CalcAbsDay(psTm);
    	Temp16b = CalcAbsMin(psTm);
   	return( (unsigned long int)Temp16a*1440 + Temp16b );
}

const uint08 code LoadOffset[max_casecount] = { ee_ploadrec1_inpage, ee_ploadrec2_inpage, ee_ploadrec3_inpage, ee_ploadrec4_inpage, ee_ploadrec5_inpage, ee_ploadrec6_inpage };	//5类数据页类偏移量
const uint08 code LoadLen[max_casecount] = { ee_ploadrec1_len, ee_ploadrec2_len, ee_ploadrec3_len, ee_ploadrec4_len, ee_ploadrec5_len, ee_ploadrec6_len };	//5类数据页数据长度

void Load_Judge()		//负荷记录判断
{
	unsigned char i, Temp08;
	unsigned int Result;
	unsigned long int Temp32;

	if( EA_OFF || clock_error ) return;//掉电或者时钟错误不处理

	run_loadchk_flag = 0;
	run_timezone_flag = 1;

//	if( (Cmp_Clock( Display_Para.Lstarttimer, 5 ) != 0x01) )//负荷记录起始时间<=当前时间
	{
		Temp32 = CalcTime( Sclock.Clockbackup+1 );
//		Exchange( Eeprom.Buffer, Display_Para.Lstarttimer, 5 );//变成低字节在前
//		Temp32 -= CalcTime( Eeprom.Buffer );//计算当前时间和启动时间的分钟差

		for(i=0; i<max_casecount; i++)
		{
			if( Temp32%Bcd_To_Hex((Display_Para.Lspacetimer[i].B08[1])) == 0 )
			{
				if( i < 5 )
					Temp08 = Week_Holiday.Freeze[0].B08[1]>>i;
				else
					Temp08 = Week_Holiday.Freeze[0].B08[0]>>(i-5);

				if( Temp08&1 )
				{
					Clear_Wdt();

					memcpy( Eeprom.Buffer, Sclock.Clockbackup+1, 5 );	//复制时间
					switch( i )
					{
						case 0: //时间(5)+电压(2)+电流(3)
							memcpy( Eeprom.Buffer+5+0, Emu_Data.U.B08,  2 );	//电压xxx.x
							memcpy( Eeprom.Buffer+5+2, Emu_Data.I1.B08, 3 );	//电流xxx.xxx
							if( dl_back_flag ) Eeprom.Buffer[5+4] |= 0x80;
							break;

						case 1: //时间(5)+有功功率(3)+无功功率(3)
							memcpy( Eeprom.Buffer+5+0,  Emu_Data.Pav.B08, 3 );	//一分钟平均有功功率xx.xxxx
							if( dl_back_flag ) Eeprom.Buffer[5+2] |= 0x80;
							memcpy( Eeprom.Buffer+5+3,  Emu_Data.Qav.B08, 3 );	//一分钟平均无功功率xx.xxxx
							if( dl_back_flag2 ) Eeprom.Buffer[5+5] |= 0x80;
							break;

						case 2: //时间(5)+功率因数(2)
							memcpy( Eeprom.Buffer+5,  Emu_Data.Cosa.B08, 2 ); //功率因数x.xxx
							if( dl_back_flag ) Eeprom.Buffer[5+1] |= 0x80;
							break;

						case 3: //时间(5)+正反向有功总电量(8)+组合无功(8)
							DltoEepromBuf( 5 );
							Comp_RpdltoEepromBuf( 5+8 );
							break;

						case 4: //时间(5)+四象限无功总电量(16)
							Four_RpdltoEepromBuf( 5 );	//读四象限无功
							break;

						case 5: //时间(5)+组合有功费率1~4电量
							Cal_Comb( 0, 1, 0, Eeprom.Buffer+ 5 );
							Cal_Comb( 0, 2, 0, Eeprom.Buffer+10 );
							Cal_Comb( 0, 3, 0, Eeprom.Buffer+15 );
							Cal_Comb( 0, 4, 0, Eeprom.Buffer+20 );
							break;

						default:
							break;
					}

					Result = Write_Load_Point(i);
					memcpy( LoadBuf+LoadOffset[i], Eeprom.Buffer, LoadLen[i] );
					SynEeprom(); //同步分钟冻结到Flash
				}
			}
		}

		if( Sclock.Clockbackup[1]==0 )
		{
			Wr_Powerdown_Data(0);//写掉电相关数据到数据ee(每小时写一次)
			Save_Keep_Timer(1);//保存相关累计时间
		}
	}
}

unsigned int CalStAddr( unsigned int RecTimes, unsigned int Addr )
{
	if( Addr < (RecTimes-1) )	Addr += max_ploadrec_p;
	Addr -= (RecTimes-1);	//最早记录块地址
	return Addr;
}


unsigned int CalRecTimes( unsigned int StAddr, unsigned int EndAddr )
{
	unsigned int Temp16;

	if( StAddr <= EndAddr ) Temp16 = EndAddr-StAddr+1;
	else Temp16 = max_ploadrec_p+EndAddr-StAddr+1;

	return Temp16;
}

//------------------------- 负荷记录 抄读和清除 ----------------------------
FindInf FindSpecPos( unsigned char Obj, unsigned char Case, unsigned char *Clock, RecStore *RtRec )
{
	unsigned char i, Result, Temp08;
	unsigned int Addr, RecTimes;
	unsigned int StAddr, EndAddr;
	unsigned int QStAddr, QEndAddr;
	FindInf  RtValue = { 0xFF, 0x00 };
	RtFlash  RtAddr;

	RecTimes = RtRec->ValPoint;
	StAddr  = 1; //上1次
	EndAddr = RecTimes;  //上N次

	QStAddr = StAddr;
	QEndAddr = EndAddr;

	//首先根据有效记录数算出二分后的地址
	Temp08 = 1;
	for( i=0; i<18; i++ )	//max_ploadrec_p条最多分成13次
	{
		//  计算二分之一处地址
		Addr = (QStAddr+QEndAddr)/2;
		RtAddr = GetRecAddr( Obj, Case, Addr, RtRec );
		if( 0 == RtAddr.DataPage ) return RtValue;

		Result = Cmp_Bcd_Inv( Clock, RtAddr.Clk, 6 );
		if( Result == 0 ) break; //给定时间 == 当前时间

		if( (Temp08 == 0) || (RecTimes == 1) )
		{
			if( Result == 1 ) //给定时间 > 当前时间
			{
				if( Addr == StAddr )
				{
					Result = 0xFF;
					break;
				}

				Addr -= 1;
			}

			break;
		}

		if( RecTimes == 2 )
		{
			Temp08--;	//还需再判断一次
			if( Result == 1 ) //给定时间 > 当前时间
			{
				if( Addr == StAddr )
				{
					Result = 0xFF;
					break;
				}
				Addr -= 1;
			}
			else if( Result == 2 ) //给定时间 < 当前时间
			{
				if( Addr == EndAddr ) break;
				Addr += 1;
			}
		}

		if( Result == 1 ) //给定时间 > 当前时间
		{
			QEndAddr = Addr;
		}
		else //给定时间 > 当前时间
		{
			QStAddr = Addr;
		}

		RecTimes = QEndAddr-QStAddr+1;
	}

	RtValue.Result = Result;
	RtValue.Addr = Addr;

	return RtValue;
}


void ClearPloadRec( unsigned char *Clock )
{
	unsigned char i, k, Flag=0, Result;
	unsigned long RecTimes, Temp32;
	RtFlash  Rec;
	FindInf  RtValue = { 0xFF, 0x00 };
	unsigned char Buf[ee_eventpoint_lenth+2];
	unsigned char Obj = ee_minuten_inpage;

	memset( RdLoadPara, 0x00, sizeof(RdLoadPara) );	//只要删除负荷记录就取消负荷记录的后续帧读取

	SynFlashRec(1); //全部同步FLASH

	//分钟冻结
	k = 0;
	for( i=0; i<max_casecount; i++, k++ ) //找到各类的最早记录起始地址
	{
		RecStore RtRec = GetRecNum( Obj, i ); //记录存储参数准备

		RecTimes = RtRec.ValPoint; //每个类的有效记录数
		if( RecTimes )
		{
			RtValue = FindSpecPos( Obj, i, Clock, &RtRec ); //返回值=上N次
			if( 0 == RtValue.Result ) //时间相同，保留此记录
			{
				if( 1 == RecTimes )
				{
					continue;
				}
				else
				{
					RtValue.Addr--;
				}
			}
			else if( 0xFF == RtValue.Result )
			{
				continue;
			}

			if( RtValue.Addr <= RecTimes )
			{
				Rec = GetRecAddr( Obj, i, RtValue.Addr, &RtRec ); //读取上n次记录的存储地址
				if( 0 == Rec.DataPage )
				{
					continue;
				}

				//存储在Flash中对象才做Flash回退
				SynFlash.HisRec[k].Page = Rec.AppPage;
				SynFlash.HisRec[k].Len	= Rec.AppPos; //需要保留的字节数

				//回退有效次数
				Temp32 = RtRec.ValPoint;
				if( Temp32 > RtValue.Addr ) Temp32 -= RtValue.Addr;
				else Temp32 = 0;

				//回退记录总次数
				if( Temp32 ) //有效次数为0，要求记录序号为0
				{
					Temp32 = RtRec.CurPoint-RtValue.Addr;
				}
				memcpy( Load.Point+5*i, (uint08*)(&Temp32), 3 );
				Load.Crc16.B16 = Crc_16Bits( Load.Point, ee_loadpoint_lenth ); //CRC计算

				Result = I2C_Read_Eeprom( ee_validnum_page, ee_validnum_inpage, Buf, ee_validnum_len ); //读取“有效记录起始值”
				if( Result ) return; //读取失败 or CRC校验错

				//回退有效次数页
				memset( Buf+6*i, 0, 6 );
				if( Temp32 )
				{
					if( RtRec.ValPoint > RtValue.Addr )
						Temp32 = RtRec.CurPoint-RtRec.ValPoint;
					else
						Temp32 = RtRec.CurPoint-RtValue.Addr;
					memcpy( Buf+6*i+3, (uint08*)(&Temp32), 3 );
				}

				I2C_Write_Eeprom( ee_validnum_page, ee_validnum_inpage, Buf, ee_validnum_len ); //存储“有效记录起始值”

				Flag = 1; //同步到EE
			}
		}
	}

	if( Flag )
	{
		I2C_Write_Eeprom( ee_synflash_page, ee_synflash_inpage, (uint08*)SynFlash.HisRec, ee_synflash_len );
	}
}


unsigned char ReadLoadRec( unsigned char Ch, unsigned char *InBuf, unsigned char *OutBuf )
//InBuf[0]: 0x11读数据; 0x12:读后续帧
//05给定数据标示; 0A给定时间
//InBuf[2~5]:DI0~DI3
//InBuf[6]: NN或SN
//InBuf[7~10]:mmhhDDMMYY, 给定时间时有效
{
	unsigned char i, t, Result, Spec; //00:未从E2读取; FF:从E2中读取
	unsigned char RdBuf[64];
	struct
	{
		union B16_B08_2  Addr[2];	//[0~3]最早记录块; [4~7]最近记录块
		union B16_B08_2  RecTimes;
	} RdStr;
	unsigned char offset, len, n, num, Temp08, Glen;
	union B16_B08_2 Temp16;
	unsigned char BkClock[6], FirstVal[8]; //期望时间
	unsigned long TmpA;
	unsigned char Obj;
	RecStore RtRec;
	RtFlash  RtAddr;
	FindInf  RtValue;
	//负荷记录相关参数列表              电压 电流 有功功率 无功功率 功率因数 总电量 四象限 需量 谐波 基波 预留 组合1~4 组合5~8
	const unsigned char CaseTab[13] = { 0,   0,   1,       1,       2,       3,     4,     0,   0,   0,   0,   5,      6 };
	const unsigned char PosTab [13] = { 5,   7,   5,       8,       5,       5,     5,     5,   5,   5,   5,   5,      5 };
	const unsigned char LenTab [13] = { 2,   3,   3,       3,       2,       4,     4,     0,   0,   0,   0,   5,      5 };
	const unsigned char NumTab [13] = { 3,   3,   4,       4,       4,       4,     4,     0,   0,   0,   0,   4,      4 };

	Temp08 = 0;
	switch( InBuf[3] )
	{
		case 0x01: //电压
		case 0x02: //电流
			if( (InBuf[2] == 1) || (InBuf[2] == 0xFF) )
				Temp08 = 1;
			break;

		case 0x03: //有功功率
		case 0x04: //无功功率
		case 0x05: //功率因数
			if( (InBuf[2] == 0) || (InBuf[2] == 0xFF) )
				Temp08 = 1;
			break;

		case 0x06: //有功总电能+无功总电能
			if( (InBuf[4] == 0x11) && (InBuf[2] > 2) && (InBuf[2] != 0xFF) ) break;
		case 0x07: //四象限无功
		case 0x0C: //组合有功1~4
//		case 0x0D: //组合有功5~8
			if( ((InBuf[2] >= 1) && (InBuf[2] <= 4)) || (InBuf[2] == 0xFF) )
				Temp08 = 1;
			break;

		default:
			break;
	}

	if( Temp08 == 0 )
	{
		OutBuf[0] = 0xFF;
		OutBuf[1] = 0x02;	//数据标识错, 无请求数据
		return 2;
	}

	i  = CaseTab[InBuf[3]-1]; //第i类
	len = LenTab[InBuf[3]-1]; //单个对象数据长度
	offset = PosTab[InBuf[3]-1]; //记录中偏移量
	num = 1; //单个对象
	if( InBuf[2] == 0xFF ) //数据块中对象个数
	{
		num = NumTab[InBuf[3]-1];
		if( (InBuf[4] == 0x11) && (InBuf[3] == 0x06) )
			num -= 2;
	}
	else if( InBuf[2] )
		offset += (InBuf[2]-1)*len; //记录中偏移量

	Spec = Bcd_To_Hex(Display_Para.Lspacetimer[i].B08[1]); //负荷记录间隔

	Obj = ee_minuten_inpage;
	RtRec = GetRecNum( Obj, i ); //记录存储参数准备
	RdStr.RecTimes.B16 = RtRec.ValPoint;
	if( RdStr.RecTimes.B16 == 0x00 ) return 0x00;

	//Addr: 对应类的块地址 [0~1]: 最早记录; [2~3]: 最近记录
	//RecTimes: 对应类的剩余有效记录数
	//RdLoadPara: 数据标识(4)+剩余记录块数(1)+后续帧序号(1)+起始地址(4)+剩余有效记录数(2)+给定时间(5)+上一次电量(16)
	if( InBuf[0] == 0x12 ) //读取后续帧
	{
		if( RdLoadPara[Ch][4] == 0 ) return 0x00; //无后续帧

		Result = Cmp_Data( RdLoadPara[Ch], InBuf+2, 4 );
		if( Result != 3 ) return 0x00; //数据标识错

		if( InBuf[6] != RdLoadPara[Ch][5] ) return 0x00; //帧序号错误

		memcpy( RdStr.Addr[0].B08, RdLoadPara[Ch]+6, 6 );
		memcpy( BkClock+1, RdLoadPara[Ch]+12, 5 );

		t = 0x00;
	}
	else if( InBuf[0] == 0x11 ) //读负荷记录
	{
		memset( RdLoadPara[Ch], 0x00, sizeof(RdLoadPara[Ch]) ); //删除历史抄读记录, 重新记录

		RdLoadPara[Ch][4] = Bcd_To_Hex(InBuf[6]);	//抄读的记录块数
		if( RdLoadPara[Ch][4] == 0x00 ) return 0x00; //抄读次数大于零

		RtAddr = GetRecAddr( Obj, i, RtRec.ValPoint, &RtRec );  //最早记录块
		memcpy( FirstVal+1, RtAddr.Clk+1, 5 );

		//从给定时间开始，第一个负荷记录时间
		memcpy( BkClock+1, InBuf+7, 5 );
		Result = CalcTime(BkClock+1)%Spec;
		if( Result )
		{
			Result = Spec-Result;
			Add_Min_Clock( BkClock, Result );
		}

		if( Cmp_Bcd_Inv( FirstVal+1, BkClock+1, 5 ) == 1 ) //最早记录时间大于给定时间(0-A=B; 1:A>B; 2:A<B)
		{
			TmpA = CalcTime(FirstVal+1)/Spec-CalcTime(BkClock+1)/Spec;

			if( TmpA >= RdLoadPara[Ch][4] ) return 0x00;
			if( (TmpA==0) && (RdLoadPara[Ch][4]==1) ) return 0x00;

			RdLoadPara[Ch][4] -= TmpA;	//扣除跨过的块数

			//从最早记录开始，第一个负荷记录时间
			memcpy( BkClock+1, FirstVal+1, 5 );
			Result = CalcTime(BkClock+1)%Spec;
			if( Result )
			{
				Result = Spec-Result;
				Add_Min_Clock( BkClock, Result );
			}
		}

		if( Cmp_Bcd_Inv(BkClock+1, Sclock.Clockbackup+1, 5) == 1 ) return 0x00; //给定时间大于当前时间，无记录
		if( EA_OFF ) return 0x00;	//掉电不处理

		BkClock[0] = 0; //秒
		RtValue = FindSpecPos( Obj, i, BkClock, &RtRec );
		RdStr.Addr[0].B16 = RtValue.Addr;
		if( RtValue.Result == 0xFF ) RdStr.RecTimes.B16 = 0x00; //抄读时间大于所有记录时间，记录有效次数清零
		else RdStr.RecTimes.B16 = RtValue.Addr;

		if( len >= 4 ) //抄读电量时，需要确定上一次的电量用于填充冻结遗漏点
		{
			if( RtValue.Result == 0xFF ) //抄读时间大于记录时间
				Temp16.B16 = RdStr.Addr[0].B16;
			else //抄读时间小于返回的地址所指向的记录时间
				Temp16.B16 = RdStr.Addr[0].B16+1;

			RtAddr = GetRecAddr( Obj, i, Temp16.B16, &RtRec );
			Temp08 = Flash_Rd_Bottom( RtAddr.AppPage, RtAddr.AppPos, RdBuf, RtRec.TotLen ); //从Flash中读取
			if( Temp08 ) return 0x00;
			memcpy( RdLoadPara[Ch]+17, RdBuf+offset, num*len ); //补上一次电量
		}

		t = 5;
		memcpy( OutBuf+1, BkClock+1, 5 );
	}
	else return 0x00;

	if( RdStr.RecTimes.B16 ) 	//存在记录时，确保从E2中读取
		memset( RdBuf, 0x00, 5 );
	else //没有记录时, 确保不读取E2数据
		memset( RdBuf, 0x99, 5 );

	Glen = len;
	if( (InBuf[4] == 0x11) && (len == 4) ) //高精度
		Glen += 1;

	OutBuf[0] = 0x00;
	while( RdLoadPara[Ch][4] )
	{
		Clear_Wdt();

		if( EA_OFF ) return 0x00;	//掉电不处理

		if( Cmp_Bcd_Inv(BkClock+1, Sclock.Clockbackup+1, 5) == 1 )
		{
			RdLoadPara[Ch][4] = 0;
			break;
		}

		//----- 预估此时间点的所有记录能否放在此帧中------
		if( InBuf[0] == 0x11 ) Result = 4;	//数据标识
		else Result = 5; //数据标识+序号

		if( t+num*Glen > 200-Result )
		{
			//保留当前最小时间和抄读到第几个记录, 读取后续帧要使用, 达到最大帧长度, 结束查询.
			//RdLoadPara: 数据标识(4)+剩余记录块数(1)+后续帧序号(1)+起始地址(4)+剩余有效记录数(2)+给定时间(5)+上一次电量(16)
			memcpy( RdLoadPara[Ch]+0, InBuf+2, 4 );
			RdLoadPara[Ch][5]++;	//后续帧序号
			memcpy( RdLoadPara[Ch]+ 6, RdStr.Addr[0].B08, 6 ); //地址(4)+剩余记录数(2)
			memcpy( RdLoadPara[Ch]+12, BkClock+1, 5 ); //给定时间
			break;
		}

		Result = Cmp_Bcd_Inv( RdBuf, BkClock+1, 5 ); //0-A=B; 1:A>B; 2:A<B
		if( Result == 2 ) //E2中有数据且需要填充
		{
			while( RdStr.RecTimes.B16 )
			{
				Clear_Wdt();
				if( EA_OFF ) return 0x00;	//掉电不处理

				RtAddr = GetRecAddr( Obj, i, RdStr.Addr[0].B16, &RtRec );
				Temp08 = Flash_Rd_Bottom( RtAddr.AppPage, RtAddr.AppPos, RdBuf, RtRec.TotLen ); //从Flash中读取
				if( Temp08 ) return 0x00;

				Result = Cmp_Bcd_Inv( RdBuf, BkClock+1, 5 ); //0-A=B; 1:A>B; 2:A<B
				if( Result != 1 ) //记录时间小于等于期待时间
				{
					RdStr.RecTimes.B16--;
					RdStr.Addr[0].B16--;
				}

				if( Result != 2 ) break; //记录时间大于等于期待时间，跳出查询
				if( len >= 4 ) memcpy( RdLoadPara[Ch]+17, RdBuf+offset, num*len ); //补上一次电量
			}
		}

		if( len < 4 )
		{
			memset( OutBuf+1+t, 0xFF, num*len );
			if( Result == 0 )
				memcpy( OutBuf+1+t, RdBuf+offset, len );
			t += num*len;
		}
		else
		{
			if( Result == 0 )
				memcpy( RdLoadPara[Ch]+17, RdBuf+offset, num*len ); //补上一次电量

			for( n=0; n<num; n++ )
			{
				Temp08 = 1; //正向 or 反向
				if( ((InBuf[3] == 0x06) && ((n == 2)||(n == 3)||(InBuf[2] == 3)||(InBuf[2] == 4))) 
				 ||  (InBuf[3] >= 0x0C) )
					Temp08 = 0; //组合

				memcpy( OutBuf+1+t, RdLoadPara[Ch]+17+n*len, len );
				if( Glen == 4 )
				{
					Hex2Bcd_Dl( OutBuf+1+t, Temp08 );//电量转换BCD码
				}
				else
				{
					if( (Temp08 == 0) && (OutBuf[1+t+4]&0x80) )
						memset( OutBuf+1+t+len, 0xFF, 8-len );
					else
						memset( OutBuf+1+t+len, 0x00, 8-len );
					Hex2Bcd_Dl_G( OutBuf+1+t, Temp08 ); //电量转换BCD码(高精度)
					if( (Temp08 == 0) && (OutBuf[1+t+7]&0x80) ) OutBuf[1+t+4] |= 0x80;	//组合电量<0，最高位置1
				}

				t += Glen;
			}
		}

		RdLoadPara[Ch][4]--;
		Add_Min_Clock( BkClock, Spec );
	}

	if( InBuf[0] == 0x12 ) OutBuf[++t] = InBuf[6];

	return (++t);
}
