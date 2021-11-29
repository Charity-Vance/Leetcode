#include "ex_func.h"
#include "ex_var.h"
#include "FM32L0XX.h"  
#include "System_FM32L0XX.h"
#include <string.h>


void Enable_Closerelay()//�����պϼ̵������߲忨�պϼ̵���
{	
	if( relay_commu_disable_close_flag )
	{
		relay_commu_disable_close_flag = 0;
		Store_Meterstatus();
	}
}


void Store_Meterstatus()//������״̬�ֽ�
{
	run_alarm_flag = 1;
	I2C_Write_Eeprom44( ee_meterstatus1_page, &Meter_Status, ee_meterstatus1_lenth);
}


void Displaykey_Process()
{
	Lcdled = lcdled_timer_delay; //�������ⶨʱ��
	
	if( !(SVDCHKPLOW) ) {__NOP();__NOP();LCDLEDON;}//δ����Ƿѹ��������
	Init_Led_Timer = 0;
	Display.Timer = default_keydisplaytimer;
	
	if (Display.Status & B0000_0001 ) 
	{
		{__NOP();__NOP();Display.Number++;}
		if (Display.Number > Display_Para.K_Number) {__NOP();__NOP();Display.Number = 1;}
		freeze_display_flag = 0;	//������յ�����ʾ��־
	}
	else
	{
		Display.Number = 1;
		Display.Status |= B0000_0001;//�ð�����ʾ��־
	}
	Display.Status |= B1000_0000;
	run_display_flag = 1;	//��ˢ����ʾ��־
}


void Displaykey_Check()
{
	if( (!(Display.Status & B1000_0000)) ) 
	{
		if( DisKeySamp==0xff )
		{
			Displaykey_Process();
			Keyclose_timer = 3;//����3s�����պϼ̵�����ʱ��
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
			{__NOP();__NOP();Enable_Closerelay();}	//�����պϼ̵���
		}
	}
}


void Cover_Check( void )
{
	unsigned int i;

	if( (Cover.Status == 0) && (COVKEY_P) ) //
	{
		i = 0;
		Do_DelayStart();			//3ms��ʱ�ж�
		{
			if( COVKEY_N )
			{
				{__NOP();__NOP();i = 1;}
				break;
			}
		}While_DelayMsEnd(3*clkmode);
		if( i == 0 ) //����
		{
			if( Cover_Space_Timer )	return;		//������ʱδ��
			
			Cover.Status = 1;
			Note_Run_Event(ee_covern_inpage);	//��¼�����¼���¼
		}
	}
	else if( (Cover.Status) && (COVKEY_N) )
	{
		i = 0;
		Do_DelayStart();
		{
			if( COVKEY_P ) 
			{
				{__NOP();__NOP();i= 1;}//��ʱʱ���ڿ���
				break;
			}
		} While_DelayMsEnd(3*clkmode);
		if( i == 0 ) //�ϸ�
		{
			if( Cover_Space_Timer )	return;		//������ʱδ��
			
			Cover.Status = 0;
			Note_Run_Event(ee_covern_inpage|0x80);	//��¼�ϸ��¼���¼
		}
	}
	
	Cover_Space_Timer = def_coverdelaytimer;//������ʱʱ��
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
		if( i == 0 ) //�ɸߵ�����Ϊͨ��ģ���������(��ģ���Ѿ�����)
		{
			commmodule_start_flag = 1;	//��ͨ��ģ������״�������־
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
		if( i == 0 ) //�ɵ͵�����Ϊͨ��ģ���������
		{
			if( Commmodule_Space_Timer )	return;	
			
			commmodule_open_flag = 1;
			Store_Meterstatus();
			
			memset( Buf, 0xff, 6 );		//ģ�������Ĭ��ģ��id��ȫ0xff(ͨѶ����ģ��id�򷵻�ԭģ��id����)
			UpdateSysPara( 0x40+18, Buf, 6 ); //����ģ��id
			
			if( commmodule_start_flag==0 )	return;	
			
			Note_Run_Event(ee_commchangen_inpage);	//��¼ͨ��ģ�������¼
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
		if( i == 0 ) //�ɸߵ�����Ϊͨ��ģ���������
		{
			if( Commmodule_Space_Timer )	return;
			
			commmodule_open_flag = 0;
			Store_Meterstatus();
			
			//��λ�ز�,����5minͨ��ģ���쳣��ʱ��ʱ��
			if( (Mode.Plc&0x80) )
			{
				Resetworking_Timer = resetworking_timer_delay;//������λ����
				PLC_RST0;		//��λ�ز�(�����)
			}
			Mod_Comm_Timer1 = 0;
			Mod_Comm_Timer2 = Mod_Comm_Timer_delay2; //��λ5min��û��ͨ������Ϊͨ��ģ���쳣
			
			if( commmodule_start_flag==0 )	return;	
			
			Note_Run_Event(ee_commchangen_inpage|0x80);	//��¼ͨ��ģ�������¼
		}
	}
	
	Commmodule_Space_Timer = 0x03;
}


void Relaystatus_Check() //�̵���״̬���(���巽ʽ,�Ͽ��ߵ�ƽ)
{
//#if(RELAYON == 1)	
	unsigned char flag;
	unsigned int i;

	run_relaychk_flag = 0;	//��̵���״̬����־
	
	if( Relay_Space_Timer || (PowerDetCnt0 < 4) || ( EA_OFF ) )
	{
		if( relay_error ) {__NOP();__NOP();Relayerror_Count = Defrelayerrorcount_r;}
		else {__NOP();__NOP();Relayerror_Count = 0;}
		return; 
	}
	
	if( Relayctrl.Timer ) {__NOP();__NOP();return;} 
	
	i = 0;
	Do_DelayStart();				//25msȥ���ж�
	{
		if( RELAYTEST_N ) { __NOP();__NOP();i=1; break; }
	}  While_DelayMsEnd(25*clkmode);
	
	flag = 0;
	if( (Relay_Mode != 0x55) || ((Relay_Mode == 0x55)&&(relay_cleardl_flag==0)) ) 
	{
		{__NOP();__NOP(); flag=1; }
	}
	
	if( ((relay_status_flag==1) && ((power_zero_flag==0) || (i != 0))) //����Ϊ�Ͽ�,�����й��ʻ��߷���ͨ
	    ||  ( (relay_status_flag==0) && (power_zero_flag==1) && (i == 0) && (flag==1) ) ) //�̵�������Ϊ�պ�,����û�й��ʺ�û�з���ͨ
	{		
		if( relay_status_flag ) {__NOP();__NOP();comm_relaystatus_flag = 0;}//ˢ�¼̵���ʵ��״̬(ͨѶbit4ר��)
		else {__NOP();__NOP();comm_relaystatus_flag = 1;}
		if( Relayerror_Count1 < Defrelayerrorcount ) {__NOP();__NOP();Relayerror_Count1++;}
		else
		{
			if( relay_status_flag ) {__NOP();__NOP();real_relaystatus_flag = 0;}//ˢ�¼̵���ʵ��״̬
			else {__NOP();__NOP();real_relaystatus_flag = 1;}
		}
		Relayerror_Count2 = 0;
		
		if( relay_error ) {__NOP();__NOP();return;}
		
		if( Relayerror_Count < Defrelayerrorcount_r )
		{
			{__NOP();__NOP();Relayerror_Count++;}	//�̵�����������������1
		}
		else
		{
			{__NOP();__NOP();Note_Run_Event(ee_relayerrn_inpage);}	//���ɿ����쳣��ʼ��¼
			relay_error = 1;//�ü̵�������
		}
	}
	else
	{
		comm_relaystatus_flag = relay_status_flag;	//ˢ�¼̵���ʵ��״̬(ͨѶbit4ר��)
		if( Relayerror_Count2 < Defrelayerrorcount ) {__NOP();__NOP();Relayerror_Count2++;}
		else
		{
			real_relaystatus_flag = relay_status_flag;	//ˢ�¼̵���ʵ��״̬
		
			if( relay_success_flag == 0 )
			{
				relay_success_flag = 1;				//�ü̵��������ɹ���־
				Store_Meterstatus();
				
				if( relay_status_flag )
				{
					if( RdRecTimes( ee_openrelayn_inpage ) )  {__NOP();__NOP();Set_Reportdata(1*8+6);}//������բ�ɹ��ϱ�
				}
				else
				{
					if( RdRecTimes( ee_closerelayn_inpage ) )  {__NOP();__NOP();Set_Reportdata(1*8+7);}//���к�բ�ɹ��ϱ�
				}
			}
		}
		Relayerror_Count1 = 0;
		
		if( Relayerror_Count )	//�̵������������
		{
			{__NOP();__NOP();Relayerror_Count--;}
		}
		else
		{		
			if( relay_error ) {__NOP();__NOP();Note_Run_Event(ee_relayerrn_inpage|0x80);}	//���ɿ����쳣������¼
			relay_error = 0;
		}
	}
//#else
//	comm_relaystatus_flag = 0;
//	real_relaystatus_flag = 0;
//	relay_error = 0;
//#endif	
}
