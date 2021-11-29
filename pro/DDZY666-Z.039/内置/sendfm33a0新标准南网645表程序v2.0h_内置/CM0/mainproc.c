#include "variable4.h"
#include "ex_func.h"
#include "ex_var.h"
#include "FM32L0XX.h"  
#include <string.h>
#include <stdio.h>


//;================================================================
//;主程
//;================================================================
void Comm_Event_Proc( void )
{
	unsigned char i;
		
	Calc_Pwr_Proc();		//正反向电量累计处理和金额处理
	
	for( i=0; i<CHNum; i++ )
	{	
		if( 0 == Uart[i].S_Overtime_Timer )
		{
			if(Uart[i].Flag&B0000_0100)
			{
				{__NOP();__NOP();Uart_Proc(i);}	//通讯处理
				Clear_Wdt();
				break;
			}
		}
		
		if( (0 == Uart[i].RptTimer      ) 
		 && (0 == Uart[i].S_Overtime_Timer	) 
		 && (0 == Uart[i].Response_Timer) )
		{
			if( CHZB == i ) ReportEvent(0);
		}
		
		SynFlashRec(0); //同步FLASH
	}
		
	if( EA_OFF )			//发生欠压(起去抖作用)
	{	
		{__NOP();__NOP();Sleep(1);}		//进入sleep
	}
}


void Vector_Event_Proc( void )
{
	if( run_alarm_flag )
	{
		{__NOP();__NOP();Mt_Alarmstatus_Judge();}	//电表报警状态判断
	}	
	
//	if( BDMODE ) //本地模式
	{
		if( run_price_flag && (run_freeze_flag==0) )
		{
			{__NOP();__NOP();Year_Ladder_Judge(1);}	//年阶梯启动判断和数据合法性判断
			Price_Judge();	//费率阶梯电价判断
		}
	}
	if( run_timezone_flag )
	{
		{__NOP();__NOP();Timezone_Judge();}	//时区时段费率判断
	}
	
	if( run_loadchk_flag )
	{
		{__NOP();__NOP();Load_Judge();}		//负荷记录判断
	}
	
	if( run_freeze_flag )
	{
		{__NOP();__NOP();Freeze_Judge();}	//冻结和结算判断
	}		
	
	if( run_readrtc_flag )
	{
		{__NOP();__NOP();Read_Sysclock();}	//读时钟
	}
	
	if( run_display_flag )
	{			
		{__NOP();__NOP();Lcd_Display();}	//刷新显示
	}
	
	if( run_relaychk_flag )
	{
		{__NOP();__NOP();Relaystatus_Check();}	//继电器检测
	}	
	
	Cover_Check();		//开盖检测
	Commmodule_Check();	//通信模块检测	
	Displaykey_Check();	//显示按键检测		
}


void Sclock_Event_Proc( void )
{
	unsigned char i;
	
	if( fwdl_veri_flag )
	{
		{__NOP();__NOP();Fwdl_Verify();}		//正向电量校验
	}	
	
	if( bkdl_veri_flag )
	{
		{__NOP();__NOP();Bkdl_Verify();}		//反向电量校验
	}
	
	if( rpdl_veri_flag )
	{
		for(i=0; i<4; i++)
		{__NOP();__NOP();Rpdl_Verify(i);}		//无功电量校验
	}
	
	if( mode_veri_flag )
	{
		{__NOP();__NOP();Mode_Verify();}		//特征模式字校验
	}
				
	if( reg_veri_flag )
	{
		{__NOP();__NOP();Veri_Sys_Reg();}		//寄存器校验
	}
	
	if( addr_veri_flag )
	{
		{__NOP();__NOP();Commaddr_Verify();}		//通讯地址校验	
	}
	
	if( disppm_veri_flag )
	{
		{__NOP();__NOP();Display_Para_Verify();}	//显示参数校验
	}
	
	if( dispitem_veri_flag )
	{
		{__NOP();__NOP();Displayitem_Verify();}		//显示项目校验
	}
	
	if( temperpara_veri_flag )
	{
		{__NOP();__NOP();Temperpara_Verify();}		//温度系数校验	
	}
}


void Energy_Event_Proc( void )
{
	if( check_7051_flag1 )
	{
		{__NOP();__NOP();ATT7051_Check();}	//校验一次7051调教寄存器
	}
	else if( read_back_flag )
	{
		{__NOP();__NOP();Read_UIP();}		//读瞬时UIP值
		Judge_Uip_Data();			//UIP数据判断
	}
}
			


int main( void )
{
	Init_System();				//系统初始化
	
	for( ; ; )
	{
		Clear_Wdt();
		Init_Arm0();
		__enable_irq();
		
		Adc_Proc();			//电池和温度adc处理
		
		Vector_Event_Proc();		//time0时标处理
		Comm_Event_Proc();		//通讯电量和电源处理
		
		Sclock_Event_Proc();		//rtc时标处理
		Comm_Event_Proc();		//通讯电量和电源处理
		
		Energy_Event_Proc();		//计量处理
		Comm_Event_Proc();		//通讯电量和电源处理
		
//		Card_Proc();			//IC卡处理
//		Comm_Event_Proc();		//通讯电量和电源处理
	}
}


