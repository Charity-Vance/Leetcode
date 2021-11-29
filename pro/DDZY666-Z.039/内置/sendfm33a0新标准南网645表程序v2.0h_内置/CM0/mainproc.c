#include "variable4.h"
#include "ex_func.h"
#include "ex_var.h"
#include "FM32L0XX.h"  
#include <string.h>
#include <stdio.h>


//;================================================================
//;����
//;================================================================
void Comm_Event_Proc( void )
{
	unsigned char i;
		
	Calc_Pwr_Proc();		//����������ۼƴ���ͽ���
	
	for( i=0; i<CHNum; i++ )
	{	
		if( 0 == Uart[i].S_Overtime_Timer )
		{
			if(Uart[i].Flag&B0000_0100)
			{
				{__NOP();__NOP();Uart_Proc(i);}	//ͨѶ����
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
		
		SynFlashRec(0); //ͬ��FLASH
	}
		
	if( EA_OFF )			//����Ƿѹ(��ȥ������)
	{	
		{__NOP();__NOP();Sleep(1);}		//����sleep
	}
}


void Vector_Event_Proc( void )
{
	if( run_alarm_flag )
	{
		{__NOP();__NOP();Mt_Alarmstatus_Judge();}	//�����״̬�ж�
	}	
	
//	if( BDMODE ) //����ģʽ
	{
		if( run_price_flag && (run_freeze_flag==0) )
		{
			{__NOP();__NOP();Year_Ladder_Judge(1);}	//����������жϺ����ݺϷ����ж�
			Price_Judge();	//���ʽ��ݵ���ж�
		}
	}
	if( run_timezone_flag )
	{
		{__NOP();__NOP();Timezone_Judge();}	//ʱ��ʱ�η����ж�
	}
	
	if( run_loadchk_flag )
	{
		{__NOP();__NOP();Load_Judge();}		//���ɼ�¼�ж�
	}
	
	if( run_freeze_flag )
	{
		{__NOP();__NOP();Freeze_Judge();}	//����ͽ����ж�
	}		
	
	if( run_readrtc_flag )
	{
		{__NOP();__NOP();Read_Sysclock();}	//��ʱ��
	}
	
	if( run_display_flag )
	{			
		{__NOP();__NOP();Lcd_Display();}	//ˢ����ʾ
	}
	
	if( run_relaychk_flag )
	{
		{__NOP();__NOP();Relaystatus_Check();}	//�̵������
	}	
	
	Cover_Check();		//���Ǽ��
	Commmodule_Check();	//ͨ��ģ����	
	Displaykey_Check();	//��ʾ�������		
}


void Sclock_Event_Proc( void )
{
	unsigned char i;
	
	if( fwdl_veri_flag )
	{
		{__NOP();__NOP();Fwdl_Verify();}		//�������У��
	}	
	
	if( bkdl_veri_flag )
	{
		{__NOP();__NOP();Bkdl_Verify();}		//�������У��
	}
	
	if( rpdl_veri_flag )
	{
		for(i=0; i<4; i++)
		{__NOP();__NOP();Rpdl_Verify(i);}		//�޹�����У��
	}
	
	if( mode_veri_flag )
	{
		{__NOP();__NOP();Mode_Verify();}		//����ģʽ��У��
	}
				
	if( reg_veri_flag )
	{
		{__NOP();__NOP();Veri_Sys_Reg();}		//�Ĵ���У��
	}
	
	if( addr_veri_flag )
	{
		{__NOP();__NOP();Commaddr_Verify();}		//ͨѶ��ַУ��	
	}
	
	if( disppm_veri_flag )
	{
		{__NOP();__NOP();Display_Para_Verify();}	//��ʾ����У��
	}
	
	if( dispitem_veri_flag )
	{
		{__NOP();__NOP();Displayitem_Verify();}		//��ʾ��ĿУ��
	}
	
	if( temperpara_veri_flag )
	{
		{__NOP();__NOP();Temperpara_Verify();}		//�¶�ϵ��У��	
	}
}


void Energy_Event_Proc( void )
{
	if( check_7051_flag1 )
	{
		{__NOP();__NOP();ATT7051_Check();}	//У��һ��7051���̼Ĵ���
	}
	else if( read_back_flag )
	{
		{__NOP();__NOP();Read_UIP();}		//��˲ʱUIPֵ
		Judge_Uip_Data();			//UIP�����ж�
	}
}
			


int main( void )
{
	Init_System();				//ϵͳ��ʼ��
	
	for( ; ; )
	{
		Clear_Wdt();
		Init_Arm0();
		__enable_irq();
		
		Adc_Proc();			//��غ��¶�adc����
		
		Vector_Event_Proc();		//time0ʱ�괦��
		Comm_Event_Proc();		//ͨѶ�����͵�Դ����
		
		Sclock_Event_Proc();		//rtcʱ�괦��
		Comm_Event_Proc();		//ͨѶ�����͵�Դ����
		
		Energy_Event_Proc();		//��������
		Comm_Event_Proc();		//ͨѶ�����͵�Դ����
		
//		Card_Proc();			//IC������
//		Comm_Event_Proc();		//ͨѶ�����͵�Դ����
	}
}


