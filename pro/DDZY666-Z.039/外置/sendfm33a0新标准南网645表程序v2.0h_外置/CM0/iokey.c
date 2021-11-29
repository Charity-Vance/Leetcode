#include "ex_func.h"
#include "ex_var.h"
#include "FM32L0XX.h"  
#include "System_FM32L0XX.h"
#include <string.h>


void Enable_Closerelay()//按键闭合继电器或者插卡闭合继电器
{	
	if( relay_commu_disable_close_flag )
	{
		relay_commu_disable_close_flag = 0;
		Store_Meterstatus();
	}
}


void Store_Meterstatus()//保存电表状态字节
{
	run_alarm_flag = 1;
	I2C_Write_Eeprom44( ee_meterstatus1_page, &Meter_Status, ee_meterstatus1_lenth);
}


void Displaykey_Process()
{
	Lcdled = lcdled_timer_delay; //启动背光定时器
	
	if( !(SVDCHKPLOW) ) {__NOP();__NOP();LCDLEDON;}//未发生欠压点亮背光
	Init_Led_Timer = 0;
	Display.Timer = default_keydisplaytimer;
	
	if (Display.Status & B0000_0001 ) 
	{
		{__NOP();__NOP();Display.Number++;}
		if (Display.Number > Display_Para.K_Number) {__NOP();__NOP();Display.Number = 1;}
		freeze_display_flag = 0;	//清结算日电量显示标志
	}
	else
	{
		Display.Number = 1;
		Display.Status |= B0000_0001;//置按键显示标志
	}
	Display.Status |= B1000_0000;
	run_display_flag = 1;	//置刷新显示标志
}


void Displaykey_Check()
{
	if( (!(Display.Status & B1000_0000)) ) 
	{
		if( DisKeySamp==0xff )
		{
			Displaykey_Process();
			Keyclose_timer = 3;//启动3s按键闭合继电器定时器
			DisKeySamp=0x0f;
		}
	}
	else
	{
		if( DisKeySamp==0x00 )
		{
			{__NOP();__NOP();Display.Status &= B0111_1111;}
			Keyclose_timer = 0;
		}
		
		if( (DisKeySamp==0xff)&&(Keyclose_timer == 0) )
		{
			{__NOP();__NOP();Enable_Closerelay();}	//按键闭合继电器
		}
	}
}


void Cover_Check( void )
{
	unsigned int i;

	if( (Cover.Status == 0) && (COVKEY_P) ) //
	{
		i = 0;
		Do_DelayStart();			//3ms延时判断
		{
			if( COVKEY_N )
			{
				{__NOP();__NOP();i = 1;}
				break;
			}
		}While_DelayMsEnd(3*clkmode);
		if( i == 0 ) //开盖
		{
			if( Cover_Space_Timer )	return;		//开盖延时未到
			
			Cover.Status = 1;
			Note_Run_Event(ee_covern_inpage);	//记录开盖事件记录
		}
	}
	else if( (Cover.Status) && (COVKEY_N) )
	{
		i = 0;
		Do_DelayStart();
		{
			if( COVKEY_P ) 
			{
				{__NOP();__NOP();i= 1;}//超时时间内开盖
				break;
			}
		} While_DelayMsEnd(3*clkmode);
		if( i == 0 ) //合盖
		{
			if( Cover_Space_Timer )	return;		//开盖延时未到
			
			Cover.Status = 0;
			Note_Run_Event(ee_covern_inpage|0x80);	//记录合盖事件记录
		}
	}
	
	Cover_Space_Timer = def_coverdelaytimer;//开盖延时时间
}


extern unsigned char UpdateSysPara( unsigned char Start, unsigned char *Para, unsigned char Len );
void Commmodule_Check( void )
{
	unsigned char i, Buf[6];

	if( (commmodule_start_flag==0) && (COMMMODULE_N) )
	{
		i = 0;
		Do_DelayStart();
		{
			if( COMMMODULE_P ) 
			{
				{__NOP();__NOP();i= 1;}
				break;
			}
		} While_DelayMsEnd(3*clkmode);
		if( i == 0 ) //由高到低认为通信模块更换结束(即模块已经插入)
		{
			commmodule_start_flag = 1;	//置通信模块更换首次启动标志
			Store_Meterstatus();
		}
	}
	
	if( (commmodule_open_flag == 0) && (COMMMODULE_P) ) 
	{
		i = 0;
		Do_DelayStart();
		{
			if( COMMMODULE_N )
			{
				{__NOP();__NOP();i = 1;}
				break;
			}
		}While_DelayMsEnd(3*clkmode);
		if( i == 0 ) //由低到高认为通信模块更换发生
		{
			if( Commmodule_Space_Timer )	return;	
			
			commmodule_open_flag = 1;
			Store_Meterstatus();
			
			memset( Buf, 0xff, 6 );		//模块拔走则默认模块id成全0xff(通讯抄读模块id则返回原模块id备份)
			UpdateSysPara( 0x40+18, Buf, 6 ); //更新模块id
			
			if( commmodule_start_flag==0 )	return;	
			
			Note_Run_Event(ee_commchangen_inpage);	//记录通信模块更换记录
		}
	}
	else if( (commmodule_open_flag) && (COMMMODULE_N) )
	{
		i = 0;
		Do_DelayStart();
		{
			if( COMMMODULE_P ) 
			{
				{__NOP();__NOP();i= 1;}
				break;
			}
		} While_DelayMsEnd(3*clkmode);
		if( i == 0 ) //由高到低认为通信模块更换结束
		{
			if( Commmodule_Space_Timer )	return;
			
			commmodule_open_flag = 0;
			Store_Meterstatus();
			
			//复位载波,启动5min通信模块异常延时定时器
			if( (Mode.Plc&0x80) )
			{
				Resetworking_Timer = resetworking_timer_delay;//启动复位脉冲
				PLC_RST0;		//复位载波(输出低)
			}
			Mod_Comm_Timer1 = 0;
			Mod_Comm_Timer2 = Mod_Comm_Timer_delay2; //复位5min后没有通信则认为通信模块异常
			
			if( commmodule_start_flag==0 )	return;	
			
			Note_Run_Event(ee_commchangen_inpage|0x80);	//记录通信模块更换记录
		}
	}
	
	Commmodule_Space_Timer = 0x03;
}


void Relaystatus_Check() //继电器状态检测(脉冲方式,断开高电平)
{
//#if(RELAYON == 1)	
	unsigned char flag;
	unsigned int i;

	run_relaychk_flag = 0;	//清继电器状态检测标志
	
	if( Relay_Space_Timer || (PowerDetCnt0 < 4) || ( EA_OFF ) )
	{
		if( relay_error ) {__NOP();__NOP();Relayerror_Count = Defrelayerrorcount_r;}
		else {__NOP();__NOP();Relayerror_Count = 0;}
		return; 
	}
	
	if( Relayctrl.Timer ) {__NOP();__NOP();return;} 
	
	i = 0;
	Do_DelayStart();				//25ms去抖判断
	{
		if( RELAYTEST_N ) { __NOP();__NOP();i=1; break; }
	}  While_DelayMsEnd(25*clkmode);
	
	flag = 0;
	if( (Relay_Mode != 0x55) || ((Relay_Mode == 0x55)&&(relay_cleardl_flag==0)) ) 
	{
		{__NOP();__NOP(); flag=1; }
	}
	
	if( ((relay_status_flag==1) && ((power_zero_flag==0) || (i != 0))) //命令为断开,但是有功率或者反馈通
	    ||  ( (relay_status_flag==0) && (power_zero_flag==1) && (i == 0) && (flag==1) ) ) //继电器命令为闭合,但是没有功率和没有反馈通
	{		
		if( relay_status_flag ) {__NOP();__NOP();comm_relaystatus_flag = 0;}//刷新继电器实际状态(通讯bit4专用)
		else {__NOP();__NOP();comm_relaystatus_flag = 1;}
		if( Relayerror_Count1 < Defrelayerrorcount ) {__NOP();__NOP();Relayerror_Count1++;}
		else
		{
			if( relay_status_flag ) {__NOP();__NOP();real_relaystatus_flag = 0;}//刷新继电器实际状态
			else {__NOP();__NOP();real_relaystatus_flag = 1;}
		}
		Relayerror_Count2 = 0;
		
		if( relay_error ) {__NOP();__NOP();return;}
		
		if( Relayerror_Count < Defrelayerrorcount_r )
		{
			{__NOP();__NOP();Relayerror_Count++;}	//继电器错误错误计数器加1
		}
		else
		{
			{__NOP();__NOP();Note_Run_Event(ee_relayerrn_inpage);}	//负荷开关异常开始记录
			relay_error = 1;//置继电器错误
		}
	}
	else
	{
		comm_relaystatus_flag = relay_status_flag;	//刷新继电器实际状态(通讯bit4专用)
		if( Relayerror_Count2 < Defrelayerrorcount ) {__NOP();__NOP();Relayerror_Count2++;}
		else
		{
			real_relaystatus_flag = relay_status_flag;	//刷新继电器实际状态
		
			if( relay_success_flag == 0 )
			{
				relay_success_flag = 1;				//置继电器操作成功标志
				Store_Meterstatus();
				
				if( relay_status_flag )
				{
					if( RdRecTimes( ee_openrelayn_inpage ) )  {__NOP();__NOP();Set_Reportdata(1*8+6);}//进行拉闸成功上报
				}
				else
				{
					if( RdRecTimes( ee_closerelayn_inpage ) )  {__NOP();__NOP();Set_Reportdata(1*8+7);}//进行合闸成功上报
				}
			}
		}
		Relayerror_Count1 = 0;
		
		if( Relayerror_Count )	//继电器错误计数器
		{
			{__NOP();__NOP();Relayerror_Count--;}
		}
		else
		{		
			if( relay_error ) {__NOP();__NOP();Note_Run_Event(ee_relayerrn_inpage|0x80);}	//负荷开关异常结束记录
			relay_error = 0;
		}
	}
//#else
//	comm_relaystatus_flag = 0;
//	real_relaystatus_flag = 0;
//	relay_error = 0;
//#endif	
}
