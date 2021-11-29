#include "ex_func.h"
#include "ex_var.h" 
#include "FM32L0XX.h"  
#include <string.h>


const struct HisEvent_STR ecode   EventTable[EventNum]=
{
	0x3001,	ee_cleardl_note_page,		ee_cleardlnote_inpage,		ee_cleardlnote_lenth,		3*8+1,	//�������
	0x3003,	ee_clearevent_note_page,	ee_cleareventknote_inpage,	ee_cleareventnote_lenth,	3*8+3,	//�¼�����
	0x0311,	ee_powerdown_note_page,		ee_powerdownnote_inpage,	ee_powerdownnote_lenth,		2*8+7, 	//�����¼++
	0x3004,	ee_setclock_note_page,		ee_setclocknote_inpage,		ee_setclocknote_lenth,		3*8+4,	//����ʱ��
	0x300d,	ee_opencover_note_page,		ee_opencovernote_inpage,	ee_opencovernote_lenth,		1*8+2,	//�����
	0x1901, ee_maxi_note_page, 		ee_maxinote_inpage,		ee_maxinote_lenth,      	2*8+4,	//����
	0x1d00,	ee_openrelay_note_page,		ee_openrelaynote_inpage,	ee_openrelaynote_lenth,		1*8+6,	//��բ           
	0x1e00,	ee_closerelay_note_page,	ee_closerelaynote_inpage,	ee_closerelaynote_lenth,	1*8+7,	//��բ         
	0x3000,	ee_program_note_page,		ee_programnote_inpage,		ee_programnote_lenth,		3*8+0,	//��̼�¼
	0x3006,	ee_shiqurecord_page,		70,				ee_shiqurecord_lenth,		3*8+6,	//ʱ������
	0x3005,	ee_shiduanrecord_page,		70,				ee_shiduanrecord_lenth,		3*8+5,	//ʱ�α���
	0x300c,	ee_jieshuanrecord_page,		ee_jieshuanrecord_inpage,	ee_jieshuanrecord_lenth,	4*8+4,	//�����ձ��
	0x3012, ee_keysetrecord_page, 		ee_keysetrecord_inpage, 	ee_keysetrecord_len,		4*8+7,	//��Կ���±��     
	0x3009,	ee_combstatusrecord_page,	ee_combstatusrecord_inpage,	ee_combstatusrecord_lenth,	4*8+1,	//�й���Ϸ�ʽ���
	0x300a,	ee_rp1combstatusrecord_page,	ee_rp1combstatusrecord_inpage,	ee_rp1combstatusrecord_lenth,	4*8+2,	//�޹���Ϸ�ʽ1���
	0x300b,	ee_rp2combstatusrecord_page,	ee_rp2combstatusrecord_inpage,	ee_rp2combstatusrecord_lenth,	4*8+3,	//�޹���Ϸ�ʽ2���
	0x3600,	ee_relayerr_note_page,		ee_relayerrnote_inpage,		ee_relayerrnote_lenth,		0*8+0,	//���ɿ���������¼
	0x3700,	ee_powererr_note_page,		ee_powererrnote_inpage,		ee_powererrnote_lenth,		1*8+5,	//��Դ�쳣��¼
	0x3007, ee_week_note_page,		ee_week_note_inpage,		ee_week_note_len,		3*8+7,	//�����ձ��
	0x2200,	ee_batterlow_note_page,		ee_batterlownote_inpage,	ee_batterlownote_len,		0*8+3,	//���Ƿѹ
	0x3010,	ee_jtpricerecord_page,		ee_jtpricerecord_inpage,	ee_jtpricerecord_len,		4*8+6,	//���ݱ���
	0x3050,	ee_clockerrrecord_page,		ee_clockerrrecord_inpage,	ee_clockerrrecord_len,		0*8+7,	//ʱ�ӹ��ϼ�¼
	0x4e00,	ee_calerr_note_page,		ee_calerrnote_inpage,		ee_calerrnote_len,		0xff,	//����оƬ���ϼ�¼--
	0x3051,	ee_gbsetclock_note_page,	ee_gbsetclocknote_inpage,	ee_gbsetclocknote_lenth,	0xff,	//�㲥Уʱ--
	0xbd0b, ee_nlineerrrecord_page,     	ee_nlineerrrecord_inpage,   	ee_nlineerrrecord_len,  	0xff,   //���ߵ����쳣--
	
	0x1001,	ee_lostv_note_page,		ee_lostvnote_inpage,		ee_lostvnote_len,		2*8+0,	//ʧѹ��¼
	0xbd07,	ee_lowerv_note_page,		ee_lowervnote_inpage,		ee_lowervnote_len,		2*8+2,	//�͵�ѹ�¼���¼--
	0xbd04,	ee_highv_note_page,		ee_highvnote_inpage,		ee_highvnote_len,		2*8+1,	//�ߵ�ѹ�¼���¼--
	0x5400,	ee_batchange_note_page,		ee_batchangenote_inpage,	ee_batchangenote_len,		0xff,	//��ظ�����¼--
	0x5101,	ee_commerr_note_page,		ee_commerrnote_inpage,		ee_commerrnote_len,		0xff,	//ͨѶģ���쳣--
	0x5201,	ee_commchange_note_page,	ee_commchangenote_inpage,	ee_commchangenote_len,		0xff,	//ͨѶģ�����--
	0x7004,	ee_poweroff_note_page,		ee_poweroffnote_inpage,		ee_poweroffnote_lenth,		0xff, 	//�����ϱ���¼
	0x7005,	ee_poweron_note_page,		ee_poweronnote_inpage,		ee_poweronnote_lenth,		0xff, 	//�ϵ��ϱ���¼
	0x7000,	ee_dayvolpass_note_page,	ee_dayvolpassnote_inpage,	ee_dayvolpassnote_len,		0xff,	//�յ�ѹ�ϸ���
	0x1000, ee_monvolpass_note_page,     	ee_monvolpassnote_inpage,   	ee_monvolpassnote_len,  	0xff,   //�µ�ѹ�ϸ���
	0xc002,	ee_powerdown_month_page,	ee_powerdownmonth_inpage,	ee_powerdownmonth_lenth,	0xff,	//��ͣ��ͳ��
	0xc003, ee_powerdown_year_page,     	ee_powerdownyear_inpage,   	ee_powerdownyear_lenth,  	0xff,   //��ͣ��ͳ��
};


void Exchange(unsigned char *BufA, unsigned char *BufB, unsigned char Len )
{
	unsigned char n;
	for( n=0; n<Len; n++ )
	{
		BufA[n] = BufB[Len-1-n];//��������
	}
}

void Inverse( unsigned char *Buf, unsigned char Len )
{
	unsigned char i, Temp08;
	
	for( i=0; i<Len/2; i++ )
	{
		Temp08 = Buf[i];
		Buf[i] = Buf[Len-1-i];
		Buf[Len-1-i] = Temp08;//��������
	}
}


//void Number_Add1_Direct(unsigned char *BufA) //������1
//{	
//	unsigned char  BufB[4];
//	union B32_B08 Add;
//	
//	if ( ( BufA[0]==0xff) || (BufA[1]==0xff) || (BufA[2]==0xff) )
//	{
//		BufA[0] = 0;//�Ƿ���������
//		BufA[1] = 0;
//		BufA[2] = 0;
//	}
//	BufB[0] = 0;
//	BufB[1] = BufA[2];
//	BufB[2] = BufA[1];
//	BufB[3] = BufA[0];	//���ֽ���ǰ��ɸ��ֽ���ǰ
//	Int2Byte( 1, Add.B08 );	//����(�߽���ǰ)
//	Add_Bcd( BufB, Add.B08, 4 );
//	BufA[0] = BufB[3];	//���ֽ���ǰ��ɵ��ֽ���ǰ
//	BufA[1] = BufB[2];
//	BufA[2] = BufB[1];
//}


void Number_Add1(unsigned char Offset)	//�¼���¼������1
{
//	��ָ�봦��ϲ����赥���ۼ�
	if( (Offset!=ee_openrelayn_inpage)&&(Offset!=ee_closerelayn_inpage) )	//����բ�ڳɹ��Ժ��ϱ�
	{
		if( (Offset!=ee_clearn_inpage) || (Key_Status==1) )	//˽Կ�����������ϱ�
		{
			Set_Reportdata(EventTable[Offset-ee_clearn_inpage].offset2);	//�����¼��ϱ�
		}
	}	
}


unsigned char Read_Event_Number( unsigned char *BufA, unsigned char Offset )
{
	unsigned char Buf[ee_eventpoint_lenth+2];
	
	ReadE2WithBackup( ee_event_point_page+2*((Offset-1)/12), ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );
	Hex2Bcd_SS( Buf+5*((Offset-1)%12)+0, BufA,  3 );//���ֽ�֮ǰ,BCD��
	
	return ((Offset-ee_clearn_inpage)*3);
}


const uint16 code MaxRecNum[] = {
	0, max_timingfreeze_p, 3, 2, 2, 2, 2, //NULL,��ʱ,˲ʱ,Լ������1~4
	max_ploadrec_p, max_hourfreeze_p, max_dayfreeze_p, max_histroy_p, max_histroy_p, 0, //����,Сʱ,��,��,������,Ԥ��
	max_eventrecord_p, max_eventrecord_p, max_eventrecord_p, max_eventrecord_p,	//����~
	max_eventrecord_p, max_eventrecord_p, max_eventrecord_p, max_eventrecord_p, max_eventrecord_p, //����~
	2, 2, max_eventrecord_p, 2,     //ʱ������,ʱ�α�,�����ձ��,��Կ����           
	max_eventrecord_p, max_eventrecord_p, max_eventrecord_p, max_eventrecord_p, max_eventrecord_p,//��Ϸ�ʽ���
	2, max_eventrecord_p, 2, max_eventrecord_p,	//�����ձ��,���Ƿѹ,���ݱ���,ʱ�ӹ���
	max_eventrecord_p, max_gbsetclock_p, max_eventrecord_p, //����оƬ���ϼ�¼,�㲥Уʱ,�����쳣
	max_eventrecord_p, max_eventrecord_p, max_eventrecord_p, //ʧѹ��¼,�͵�ѹ�¼���¼,�ߵ�ѹ�¼���¼
	max_eventrecord_p, max_eventrecord_p, max_eventrecord_p,max_eventrecord_p,max_eventrecord_p, //��ظ�����¼,ͨѶģ���쳣��¼,ͨѶģ�������¼,�����ϱ���¼,�ϵ��ϱ���¼
	max_dayvolpass_p, max_monvolpass_p, max_powerdownmonth_p, max_powerdownyear_p //�յ�ѹ�ϸ���,�µ�ѹ�ϸ���,��ͣ��ͳ��,��ͣ��ͳ��
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
		SynEe.Enable = 1; //����һ��ͬ��EE
		Result++;
	}
	else if( Result < MaxRecNum[Inpage] ) 
		Result++; //�ۼ���Ч����
	memcpy( Buf+Ptr+3, (uint08*)(&Result), 2 );

	Result = 0;
	memcpy( (uint08*)(&Result), Buf+Ptr, 3 );
	Result++; //�ۼӼ�¼�ܴ���
	memcpy( Buf+Ptr, (uint08*)(&Result), 3 );
	WriteE2WithBackup( Page, ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );

	Result--;
	if( IsFlashRec(Inpage) ) Result = 0;
	return ( Result%MaxRecNum[Inpage] );
}


unsigned char RdRecTimes( unsigned char Inpage )//������Чָ��
{
	unsigned long Result;
	
	//��Ч����
	Result = GetValtimes( Inpage, 0 );
	if( Result > MaxRecNum[Inpage] ) Result = MaxRecNum[Inpage];
	
	return ( Result );
}

void ClrRecTimes( unsigned char Inpage, unsigned char mode )//����Чָ��
{
	unsigned char Temp1;
	unsigned char Buf[ee_eventpoint_lenth+2];
	
	if( mode == 1 )//����(�����¼�����)
	{
		ReadE2WithBackup( ee_event_point_page+2*((Inpage-1)/12), ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );
		memset( Buf+5*((Inpage-1)%12), 0, 5 );
		WriteE2WithBackup( ee_event_point_page+2*((Inpage-1)/12), ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );
		Clr_Reportdata(Inpage);	//�嵥���ϱ�״̬�ֺ���������(���¼���¼��)
	}
	else if(mode == 0x55)//�¼�ȫ��
	{
		{Report_Data[0] = 0;Clr_Reportnum(0);}	//���ϱ�״̬�ֺ���������
		{Report_Data[1] = 0;Clr_Reportnum(1);}	//���ϱ�״̬�ֺ���������
		for( Temp1=ee_clearn_inpage+2; Temp1<ee_eventpoint_lenth; Temp1++ )
		{
			Clr_Reportdata(Temp1);	//���ϱ�״̬�ֺ���������(���¼���¼��)
		}
		
		Reset_Rep_Timer = 0;

		ReadE2WithBackup( ee_event_point_page+2, ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );
		memset( Buf+10, 0, sizeof(Buf)-10 ); //����������㡢�¼������ָ��
		WriteE2WithBackup( ee_event_point_page+2, ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );
		
		memset( Buf, 0, sizeof(Buf) );
		WriteE2WithBackup( ee_event_point_page+4, ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );
		WriteE2WithBackup( ee_event_point_page+6, ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );
		WriteE2WithBackup( ee_event_point_page+8, ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );
	}
	else if(mode == 0xaa)//�������
	{
		ReadE2WithBackup( ee_event_point_page+2, ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );
		memset( Buf+5, 0, sizeof(Buf)-5 ); //������������ָ��
		WriteE2WithBackup( ee_event_point_page+2, ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );
		
		memset( Buf, 0, sizeof(Buf) );
		WriteE2WithBackup( ee_event_point_page+0, ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );
		WriteE2WithBackup( ee_event_point_page+4, ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );
		WriteE2WithBackup( ee_event_point_page+6, ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );
		WriteE2WithBackup( ee_event_point_page+8, ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );
	}
	else if(mode == 0xff)//����ȫ��
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
		System_Status &= (~0x3e);//���Ѿ��ϱ���־,����������ϱ�
		
		//���������ϱ�
		Clear_Wdt();
		Cover.Status = 0;	//���������²������Ǽ�¼
		Init_Metererrstatus();	//����̵�������״̬
		first_prog_flag = 0;
		{EmuErrCnt = 0;cal_err_flag=0;}//�������������²���
		
		{Nline_Err_Count = 0;nline_err_flag = 0;Clr_Otherdata(0);}//���ߵ����쳣
		{load_over_flag = 0;Current_Over_Count2 = 0;Clr_Otherdata(1);}//��������ʱ��		
		{low_voltage_flag = 0;Bat_Delay_Timer = 0;Clr_Otherdata(2);} //���Ƿѹ���ۼ�ʱ��(4)
		{below_60u_flag = 0;Voltage_Low_Count = 0;Clr_Otherdata(3);} //�������ۼ�ʱ��(4)
		{lost_v_flag = 0;Current_Over_Count3 = 0;Clr_Otherdata(5);Lost_Aver_I=0;Lost_V_Timer=0;}//ʧѹ����ʱ��
		{lower_v_flag = 0;Current_Over_Count4 = 0;lower_v_event_flag = 0;Current_Over_Count41 = 0;Clr_Otherdata(6);}//�͵�ѹ����ʱ��
		{high_v_flag = 0;Current_Over_Count5 = 0;high_v_event_flag = 0;Current_Over_Count51 = 0;Clr_Otherdata(7);}//�ߵ�ѹ����ʱ��
		{commmodule_failed_flag = 0;if(Mod_Comm_Timer1==0&&Mod_Comm_Timer2==0) Mod_Comm_Timer1 = Mod_Comm_Timer_delay1;}//ͨ��ģ���쳣	
		{commmodule_open_flag = 0;commmodule_start_flag = 0;}//ͨ��ģ�����
		Store_Meterstatus();	
		Clr_Otherdata(4); //��ع���ʱ��
		
		{InitVolSts(0);} //�嵱ǰ�յ�ѹ�ϸ�������
		{InitVolSts(1);} //�嵱ǰ�µ�ѹ�ϸ�������
		{Clr_Otherdata(8);Clr_Otherdata(9);}//��ͣ��ͳ������
		{Clr_Otherdata(10);Clr_Otherdata(11);}//��ͣ��ͳ������
	}
	else
	{
		if( Inpage == ee_covern_inpage ) Cover.Status = 0;	//���������²������Ǽ�¼
		else if( Inpage == ee_relayerrn_inpage ) Init_Metererrstatus();//����̵�������״̬
		else if( Inpage == ee_programn_inpage ) first_prog_flag = 0;//��̼�¼
		else if( Inpage == ee_calerrn_inpage ) {EmuErrCnt = 0;cal_err_flag=0;}//�������������²���
		else if( Inpage == ee_nlineerrn_inpage ) {Nline_Err_Count = 0;nline_err_flag = 0;Clr_Otherdata(0);}//���ߵ����쳣
		else if( Inpage == ee_maxi_inpage ) {load_over_flag = 0;Current_Over_Count2 = 0;Clr_Otherdata(1);}//��������ʱ��		
		else if( Inpage == ee_batterlow_inpage ) {low_voltage_flag = 0;Bat_Delay_Timer = 0;Clr_Otherdata(2);Store_Meterstatus();} //���Ƿѹ���ۼ�ʱ��(4)
		else if( Inpage == ee_powerdownn_inpage ) {below_60u_flag = 0;Voltage_Low_Count = 0;Clr_Otherdata(3);} //�������ۼ�ʱ��(4)
		else if( Inpage == ee_lostvn_inpage ) {lost_v_flag = 0;Current_Over_Count3 = 0;Clr_Otherdata(5);Lost_Aver_I=0;Lost_V_Timer=0;}//ʧѹ����ʱ��	
		else if( Inpage == ee_lowervn_inpage ) {lower_v_flag = 0;Current_Over_Count4 = 0;lower_v_event_flag = 0;Current_Over_Count41 = 0;Clr_Otherdata(6);Store_Meterstatus();}//�͵�ѹ����ʱ��
		else if( Inpage == ee_highvn_inpage ) {high_v_flag = 0;Current_Over_Count5 = 0;high_v_event_flag = 0;Current_Over_Count51 = 0;Clr_Otherdata(7);Store_Meterstatus();}//�ߵ�ѹ����ʱ��
		else if( Inpage == ee_commerrn_inpage ) {commmodule_failed_flag = 0;if(Mod_Comm_Timer1==0&&Mod_Comm_Timer2==0) Mod_Comm_Timer1 = Mod_Comm_Timer_delay1;Store_Meterstatus();}//��ͨ��ģ���쳣
		else if( Inpage == ee_commchangen_inpage ) {commmodule_open_flag = 0;commmodule_start_flag = 0;Store_Meterstatus();}//ͨ��ģ�����
		
		else if( Inpage == ee_dayvolpassn_inpage ) {InitVolSts(0);} //�嵱ǰ�յ�ѹ�ϸ�������
		else if( Inpage == ee_monvolpassn_inpage ) {InitVolSts(1);} //�嵱ǰ�µ�ѹ�ϸ�������
		else if( Inpage == ee_monpowerdownn_inpage ) {Clr_Otherdata(8);Clr_Otherdata(9);}//��ͣ��ͳ������
		else if( Inpage == ee_yearpowerdownn_inpage ) {Clr_Otherdata(10);Clr_Otherdata(11);}//��ͣ��ͳ������
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
	
	if( (Inpage&0x80) == 0x00 ) //�¼���¼Ϊ���μ�¼
	{
		if( (ptr != ee_setclockn_inpage) && (ptr != ee_gbsclockn_inpage) ) //����ʱ�Ӻ͹㲥Уʱ���ڴ˺�����¼����ʱ��
		{
			memcpy( Eeprom.Buffer, Sclock.Clockbackup, 6 ); 
		}
		
		Number_Add1(ptr);
		
		result = Write_Event_Point(ptr);
	}
	else	//�¼���¼�ֳɿ�ʼ�ͽ�������
	{
		result = Read_Event_Point(ptr);
		I2C_Read_Eeprom( page+result, offset, Eeprom.Buffer, len );	//ʱ��

		if( RdRecTimes( ptr ) ) //����Ϊ0�������¼
		{
			if (ptr == ee_programn_inpage)
			{
				for( i=0; i<4*9; i++ )
				{
					Eeprom.Buffer[49-i] = Eeprom.Buffer[45-i];
				}
				memcpy( Eeprom.Buffer+10, Eeprom.Buffer+50, 4 );	//���ݱ�ʶ(4)
			}
			else
			{
				memcpy( Eeprom.Buffer+6, Sclock.Clockbackup, 6 );
				
				if( (ptr != ee_powererrn_inpage) && (ptr != ee_lowervn_inpage) && (ptr != ee_highvn_inpage) )//����Դ�쳣/�͵�ѹ/�ߵ�ѹ�¼�����,������Ҫ��¼����ʱ�̵���
				{
					if( ptr == ee_powerdownn_inpage )	//����
					{
						union B32_B08 Temp32;
						memcpy( Temp32.B08, Eeprom.Buffer+44, 3 );//���淢��ʱ��ǰ3���ӵ�ƽ������
						DltoEepromBuf( len-16-3 );
						Comp_RpdltoEepromBuf( len-8-3 );
						memcpy( Eeprom.Buffer+44, Temp32.B08, 3 );//�ָ�����ʱ��ǰ3���ӵ�ƽ������
					}
					else if( ptr == ee_covern_inpage || ptr == ee_clockerrn_inpage || ptr == ee_nlineerrn_inpage )//���ǡ�ʱ�ӹ��ϡ������쳣
					{
						DltoEepromBuf( len-24 );
						Four_RpdltoEepromBuf( len-16 );
					}
					else if( ptr == ee_maxi_inpage )	//����
					{
						DltoEepromBuf( len-16 );
						Comp_RpdltoEepromBuf( len-8 );
					}
					else if( ptr == ee_lostvn_inpage )	//ʧѹ
					{
						DltoEepromBuf( len-16-4 );
						Comp_RpdltoEepromBuf( len-8-4 );
						
						Calculate_Ah( Eeprom.Buffer+len-4 );//���㰲ʱ��
						{Lost_Aver_I=0;Lost_V_Timer=0;}						
					}
					else
					{
						DltoEepromBuf( len-8 ); //���ɿ���������ʼ�ͽ�����¼/ʱ�ӹ���/��������/��ظ���/ͨ��ģ���쳣/ͨ��ģ����
					}
				}
				else if( ptr == ee_lowervn_inpage ||  ptr == ee_highvn_inpage ) //�͵�ѹ/�ߵ�ѹ�¼�
				{
					memcpy( Eeprom.Buffer+14, Emu_Data.Uav.B08, 2 );	//��ѹxxx.x
					Eeprom.Buffer[6] = 0x00; //�ߵ�ѹ�¼��͵͵�ѹ�¼��Ľ���ʱ��Ϊ��1���1��1��0��0��
					Eeprom.Buffer[7] = 0x00;
					Eeprom.Buffer[8] = 0x00;
					Eeprom.Buffer[9] = 0x01;
					Eeprom.Buffer[10]= 0x01;
					Eeprom.Buffer[11]= Hex_To_Bcd(Bcd_To_Hex(Eeprom.Buffer[5])+1);
				}
			}
		}
	}
	
	if( ptr == ee_gbsclockn_inpage ) //�㲥Уʱ
		I2C_Write_Eeprom( page+result/3, (result%3)*len, Eeprom.Buffer, len );
	else
		I2C_Write_Eeprom( page+result, offset, Eeprom.Buffer, len );
	
	return (result);
}


void Read_Uip_Data( unsigned char st )	//����ѹ�������ʹ�������(���ڼ�¼)
{
	memcpy( Eeprom.Buffer+st+0,  Emu_Data.U.B08, 2 );	//��ѹxxx.x
	memcpy( Eeprom.Buffer+st+2,  Emu_Data.I1.B08, 3 );	//����xxx.xxx
	if( dl_back_flag ) Eeprom.Buffer[st+4] |= 0x80;
	memcpy( Eeprom.Buffer+st+5,  Emu_Data.P1.B08, 3 );	//�й�����xx.xxxx
	if( dl_back_flag ) Eeprom.Buffer[st+7] |= 0x80;
	memcpy( Eeprom.Buffer+st+8,  Emu_Data.Q1.B08, 3 );	//�޹�����xx.xxxx
	if( dl_back_flag2 ) Eeprom.Buffer[st+10] |= 0x80;
	memcpy( Eeprom.Buffer+st+11,  Emu_Data.Cosa.B08, 2 );	//��������x.xxx
	if( dl_back_flag ) Eeprom.Buffer[st+12] |= 0x80;
}


void DltoEepromBuf( unsigned char st ) //׼���й��ܵ���
{
	memcpy( Eeprom.Buffer+st+0,  Fwdl.Pluse[0].B08, 4 );	//�����ܵ���(������)
	memcpy( Eeprom.Buffer+st+4,  Bkdl.Pluse[0].B08, 4 );	//�����ܵ���(������)
}

void Comp_RpdltoEepromBuf( unsigned char st )	//׼������޹��ܵ���
{
	unsigned char i;
	unsigned char Buf[max_dl_lenth*4];
	union B64_B08_2 Temp64;
	
	for(i=0; i<4; i++) //�������޹�
	{
		memcpy( Buf+max_dl_lenth*i, Rpdl[i].Pluse[0].B08, max_dl_lenth );//�������޹��ܵ���(������)
	}
	
	CalZhuhe( Buf, Temp64.B08, Mode.Rpcomp[0], 0xff );	//����޹��ܵ���1(������)
	memcpy( Eeprom.Buffer+st, Temp64.B08, 4 );		//����޹��ܵ���1(������)
	CalZhuhe( Buf, Temp64.B08, Mode.Rpcomp[1], 0xff );	//����޹��ܵ���2(������)
	memcpy( Eeprom.Buffer+st+4, Temp64.B08, 4 );		//����޹��ܵ���2(������)
}

void Four_RpdltoEepromBuf( unsigned char st )	//׼���������޹��ܵ���
{
	unsigned char i;
	
	for(i=0; i<4; i++) //�������޹�
	{
		memcpy( Eeprom.Buffer+st+4*i, Rpdl[i].Pluse[0].B08, 4 );	//�������޹��ܵ���(������)
	}
}


void Note_Relay_Event()//��¼�Ͽ��պϼ̵����¼�
{
	I2C_Read_Eeprom( ee_operatorcode_page, ee_operatorcode_inpage, Eeprom.Buffer+6, 4 );//��4�ֽڲ����ߴ���

	DltoEepromBuf( 10 );
	Four_RpdltoEepromBuf( 18 );
	
	if( relay_status_flag == 0 ) //��բ��¼
	{
		Event_Record(ee_closerelayn_inpage);
	}
	else
	{
		Event_Record(ee_openrelayn_inpage);
	}
	
	if( Def_Relay_ActL != Def_Relay_Det )
	{
		if(PowerDetCnt0 <= 2)//�����ѹ����0.8Un�̵�����������,��ʱ���޷�����̵������,��̵���ʵ��״̬Ĭ��Ϊ����״̬
		{
			real_relaystatus_flag = relay_status_flag;
			comm_relaystatus_flag = real_relaystatus_flag;//ˢ�¼̵���ʵ��״̬(ͨѶbit4ר��)
		}
	}
}


//���ɿ���������ʼ�ͽ�����¼/���ߵ�����ƽ��/�����¼/���Ǽ�¼/������¼/ʱ�ӹ���/��������/��Դ�쳣/ͨ��ģ���쳣/ͨ��ģ����
void Note_Run_Event( unsigned char Type )	//��¼�����¼���¼
{
	unsigned char Buf[6], Temp08;
	
	if( (Type&0x80) ==  0x00 )	//��ʼ��¼
	{
		memset( Eeprom.Buffer, 0, 64 );

		if( Type == ee_relayerrn_inpage )	//���ɿ����쳣
		{
			if( (Relay_Mode == 0x55) && (relay_status_flag == 0) && (relay_success_flag==0) ) return;	//���ü̵������բ�ɹ��������ɿ���������¼���ϱ�
			
			if( relay_failed_flag ) return;		//�����ڼ�ֻ��һ�μ�¼
			else
			{
				relay_failed_flag = 1;		//�ü̵��������־
				Store_Meterstatus();
			}
			
			Eeprom.Buffer[12] = real_relaystatus_flag;	//�̵���״̬
			DltoEepromBuf( 13 );
		}
		else if( Type == ee_lowervn_inpage ||  Type == ee_highvn_inpage ) //�͵�ѹ/�ߵ�ѹ�¼�
		{
			memcpy( Eeprom.Buffer+12, Emu_Data.Uav.B08, 2 );	//��ѹxxx.x
		}
		else if( Type == ee_commerrn_inpage )	//ͨ��ģ���쳣
		{
			memcpy( Eeprom.Buffer+12, Esam_Para.Zb_Id, 6 );	//ģ��ID6
			DltoEepromBuf( 18 );
		}
		else	//�����¼/���Ǽ�¼/������¼/ʱ�ӹ���/��������/��Դ�쳣/��ظ���/ͨ��ģ����
		{
			DltoEepromBuf( 12 );
			
			if( Type == ee_powerdownn_inpage )	//����
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
					memcpy( Eeprom.Buffer+44, Temp32[3].B08, 3 );//ǰ3���ӵ�ƽ������
				}
				Keeptime.Times[8]++;	//��ͣ���ۼƴ�����1
 		 		Keeptime.Times[10]++;	//��ͣ���ۼƴ�����1
			}
			else if( Type == ee_covern_inpage || Type == ee_clockerrn_inpage || Type == ee_nlineerrn_inpage )//���ǡ�ʱ�ӹ��ϡ������쳣
			{
				Four_RpdltoEepromBuf( 20 );
			}
			else if( Type == ee_maxi_inpage || Type == ee_lostvn_inpage  ) //������ʧѹ
			{
				Comp_RpdltoEepromBuf( 20 );
				Read_Uip_Data( 28 );		//����ѹ�������ʹ�������(���ڼ�¼)
			}
		}
	}
	else
	{
		if((Type&0x7F) == ee_relayerrn_inpage )	//���ɿ����쳣
		{
			if( relay_failed_flag == 0 ) return;		//�����ڼ�ֻ��һ�μ�¼
			
			Temp08 = Read_Event_Point( ee_relayerrn_inpage );
			I2C_Read_Eeprom( ee_relayerr_note_page+Temp08, ee_relayerrnote_inpage+6, Buf, 6 );
			if( ChkBufZero(Buf,6) ) return;			//����ʱ���0��ʾ�Ѿ���¼��
		}
	}
	
	Event_Record( Type );
}


unsigned int Read_Load_Point( unsigned char Inpage )
{
	unsigned long result=0;
	
	memcpy( (uint08*)(&result), Load.Point+5*Inpage+0, 3 );

	if( result >= max_ploadrec_p ) return 0;	//���ݷǷ�
	return ( result );
}


unsigned int Write_Load_Point( unsigned char Inpage )	
{
	unsigned long result=0;
	
	SynEe.Enable = 1; //����һ��ͬ��EE
	
	//ͬ����¼��+1
	memcpy( (uint08*)(&result), Load.Point+5*Inpage+3, 2 );
	result++;
	memcpy( Load.Point+5*Inpage+3, (uint08*)(&result), 2 );

	//�ܼ�¼��+1
	result = 0;
	memcpy( (uint08*)(&result), Load.Point+5*Inpage, 3 );
	result++;
	memcpy( Load.Point+5*Inpage, (uint08*)(&result), 3 );

	Load.Crc16.B16 = Crc_16Bits( Load.Point, ee_loadpoint_lenth ); //CRC����

	result--;
	return ( result%max_ploadrec_p );
}


//�ú��������ǰʱ�����2000��1��1��0��0�ֵķ�������ֵ
//ÿ����ʼ���������
const uint16 code gui_MonthBeginDay[12] = {0, 31, 59, 90,120, 151, 181, 212, 243, 273, 304, 334};
uint16 CalcAbsDay(unsigned char * psTm)
{//��2000��1��1��Ϊ��׼�����ڵ���������,���ʱ�䲻����2000��֮ǰ(��ʵ2000����00��ʾ,�������϶���ȥ)
	uint08 ucYear = Bcd_To_Hex(psTm[4]);        //��ת����Hex
	uint08 ucMonth = Bcd_To_Hex(psTm[3])-1;      //��ת����Hex
	uint08 ucDay = Bcd_To_Hex(psTm[2]) - 1;      //��ת����Hex
	if((ucYear & 0x03) == 0)                            //�ж��Ƿ���������2��
	{
	    if(ucMonth >= 2)
	        ucDay++;                                    //�ټ�һ��
	}
	else
	{
	    ucDay++;                                        //���������00�����¶������һ��
	}
	//year >> 2,�Ǽ��Ϲ�ȥ����4��������һ��
	return ( (uint16)ucYear*365 + gui_MonthBeginDay[ucMonth] + (ucDay + (ucYear>>2)) );
}
uint16 CalcAbsMin(unsigned char* psTm)
{
	//�Ե���00ʱ00��00��Ϊ��׼��
	uint08 ucMin = Bcd_To_Hex(psTm[0]);       //��ת����Hex
	uint08 ucHour = Bcd_To_Hex(psTm[1]);        //ʱת����Hex
	return ( (uint16)ucHour*60 + ucMin );
}
//[0]��[1]ʱ[2]��[3]��[4]��
unsigned long int CalcTime(unsigned char* psTm)
{
    	uint16 Temp16a,Temp16b;
    	Temp16a = CalcAbsDay(psTm);
    	Temp16b = CalcAbsMin(psTm);
   	return( (unsigned long int)Temp16a*1440 + Temp16b );
}

const uint08 code LoadOffset[max_casecount] = { ee_ploadrec1_inpage, ee_ploadrec2_inpage, ee_ploadrec3_inpage, ee_ploadrec4_inpage, ee_ploadrec5_inpage, ee_ploadrec6_inpage };	//5������ҳ��ƫ����
const uint08 code LoadLen[max_casecount] = { ee_ploadrec1_len, ee_ploadrec2_len, ee_ploadrec3_len, ee_ploadrec4_len, ee_ploadrec5_len, ee_ploadrec6_len };	//5������ҳ���ݳ���

void Load_Judge()		//���ɼ�¼�ж�
{
	unsigned char i, Temp08;
	unsigned int Result;
	unsigned long int Temp32;

	if( EA_OFF || clock_error ) return;//�������ʱ�Ӵ��󲻴���

	run_loadchk_flag = 0;
	run_timezone_flag = 1;

//	if( (Cmp_Clock( Display_Para.Lstarttimer, 5 ) != 0x01) )//���ɼ�¼��ʼʱ��<=��ǰʱ��
	{
		Temp32 = CalcTime( Sclock.Clockbackup+1 );
//		Exchange( Eeprom.Buffer, Display_Para.Lstarttimer, 5 );//��ɵ��ֽ���ǰ
//		Temp32 -= CalcTime( Eeprom.Buffer );//���㵱ǰʱ�������ʱ��ķ��Ӳ�

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

					memcpy( Eeprom.Buffer, Sclock.Clockbackup+1, 5 );	//����ʱ��
					switch( i )
					{
						case 0: //ʱ��(5)+��ѹ(2)+����(3)
							memcpy( Eeprom.Buffer+5+0, Emu_Data.U.B08,  2 );	//��ѹxxx.x
							memcpy( Eeprom.Buffer+5+2, Emu_Data.I1.B08, 3 );	//����xxx.xxx
							if( dl_back_flag ) Eeprom.Buffer[5+4] |= 0x80;
							break;

						case 1: //ʱ��(5)+�й�����(3)+�޹�����(3)
							memcpy( Eeprom.Buffer+5+0,  Emu_Data.Pav.B08, 3 );	//һ����ƽ���й�����xx.xxxx
							if( dl_back_flag ) Eeprom.Buffer[5+2] |= 0x80;
							memcpy( Eeprom.Buffer+5+3,  Emu_Data.Qav.B08, 3 );	//һ����ƽ���޹�����xx.xxxx
							if( dl_back_flag2 ) Eeprom.Buffer[5+5] |= 0x80;
							break;

						case 2: //ʱ��(5)+��������(2)
							memcpy( Eeprom.Buffer+5,  Emu_Data.Cosa.B08, 2 ); //��������x.xxx
							if( dl_back_flag ) Eeprom.Buffer[5+1] |= 0x80;
							break;

						case 3: //ʱ��(5)+�������й��ܵ���(8)+����޹�(8)
							DltoEepromBuf( 5 );
							Comp_RpdltoEepromBuf( 5+8 );
							break;

						case 4: //ʱ��(5)+�������޹��ܵ���(16)
							Four_RpdltoEepromBuf( 5 );	//���������޹�
							break;

						case 5: //ʱ��(5)+����й�����1~4����
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
					SynEeprom(); //ͬ�����Ӷ��ᵽFlash
				}
			}
		}

		if( Sclock.Clockbackup[1]==0 )
		{
			Wr_Powerdown_Data(0);//д����������ݵ�����ee(ÿСʱдһ��)
			Save_Keep_Timer(1);//��������ۼ�ʱ��
		}
	}
}

unsigned int CalStAddr( unsigned int RecTimes, unsigned int Addr )
{
	if( Addr < (RecTimes-1) )	Addr += max_ploadrec_p;
	Addr -= (RecTimes-1);	//�����¼���ַ
	return Addr;
}


unsigned int CalRecTimes( unsigned int StAddr, unsigned int EndAddr )
{
	unsigned int Temp16;

	if( StAddr <= EndAddr ) Temp16 = EndAddr-StAddr+1;
	else Temp16 = max_ploadrec_p+EndAddr-StAddr+1;

	return Temp16;
}

//------------------------- ���ɼ�¼ ��������� ----------------------------
FindInf FindSpecPos( unsigned char Obj, unsigned char Case, unsigned char *Clock, RecStore *RtRec )
{
	unsigned char i, Result, Temp08;
	unsigned int Addr, RecTimes;
	unsigned int StAddr, EndAddr;
	unsigned int QStAddr, QEndAddr;
	FindInf  RtValue = { 0xFF, 0x00 };
	RtFlash  RtAddr;

	RecTimes = RtRec->ValPoint;
	StAddr  = 1; //��1��
	EndAddr = RecTimes;  //��N��

	QStAddr = StAddr;
	QEndAddr = EndAddr;

	//���ȸ�����Ч��¼��������ֺ�ĵ�ַ
	Temp08 = 1;
	for( i=0; i<18; i++ )	//max_ploadrec_p�����ֳ�13��
	{
		//  �������֮һ����ַ
		Addr = (QStAddr+QEndAddr)/2;
		RtAddr = GetRecAddr( Obj, Case, Addr, RtRec );
		if( 0 == RtAddr.DataPage ) return RtValue;

		Result = Cmp_Bcd_Inv( Clock, RtAddr.Clk, 6 );
		if( Result == 0 ) break; //����ʱ�� == ��ǰʱ��

		if( (Temp08 == 0) || (RecTimes == 1) )
		{
			if( Result == 1 ) //����ʱ�� > ��ǰʱ��
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
			Temp08--;	//�������ж�һ��
			if( Result == 1 ) //����ʱ�� > ��ǰʱ��
			{
				if( Addr == StAddr )
				{
					Result = 0xFF;
					break;
				}
				Addr -= 1;
			}
			else if( Result == 2 ) //����ʱ�� < ��ǰʱ��
			{
				if( Addr == EndAddr ) break;
				Addr += 1;
			}
		}

		if( Result == 1 ) //����ʱ�� > ��ǰʱ��
		{
			QEndAddr = Addr;
		}
		else //����ʱ�� > ��ǰʱ��
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

	memset( RdLoadPara, 0x00, sizeof(RdLoadPara) );	//ֻҪɾ�����ɼ�¼��ȡ�����ɼ�¼�ĺ���֡��ȡ

	SynFlashRec(1); //ȫ��ͬ��FLASH

	//���Ӷ���
	k = 0;
	for( i=0; i<max_casecount; i++, k++ ) //�ҵ�����������¼��ʼ��ַ
	{
		RecStore RtRec = GetRecNum( Obj, i ); //��¼�洢����׼��

		RecTimes = RtRec.ValPoint; //ÿ�������Ч��¼��
		if( RecTimes )
		{
			RtValue = FindSpecPos( Obj, i, Clock, &RtRec ); //����ֵ=��N��
			if( 0 == RtValue.Result ) //ʱ����ͬ�������˼�¼
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
				Rec = GetRecAddr( Obj, i, RtValue.Addr, &RtRec ); //��ȡ��n�μ�¼�Ĵ洢��ַ
				if( 0 == Rec.DataPage )
				{
					continue;
				}

				//�洢��Flash�ж������Flash����
				SynFlash.HisRec[k].Page = Rec.AppPage;
				SynFlash.HisRec[k].Len	= Rec.AppPos; //��Ҫ�������ֽ���

				//������Ч����
				Temp32 = RtRec.ValPoint;
				if( Temp32 > RtValue.Addr ) Temp32 -= RtValue.Addr;
				else Temp32 = 0;

				//���˼�¼�ܴ���
				if( Temp32 ) //��Ч����Ϊ0��Ҫ���¼���Ϊ0
				{
					Temp32 = RtRec.CurPoint-RtValue.Addr;
				}
				memcpy( Load.Point+5*i, (uint08*)(&Temp32), 3 );
				Load.Crc16.B16 = Crc_16Bits( Load.Point, ee_loadpoint_lenth ); //CRC����

				Result = I2C_Read_Eeprom( ee_validnum_page, ee_validnum_inpage, Buf, ee_validnum_len ); //��ȡ����Ч��¼��ʼֵ��
				if( Result ) return; //��ȡʧ�� or CRCУ���

				//������Ч����ҳ
				memset( Buf+6*i, 0, 6 );
				if( Temp32 )
				{
					if( RtRec.ValPoint > RtValue.Addr )
						Temp32 = RtRec.CurPoint-RtRec.ValPoint;
					else
						Temp32 = RtRec.CurPoint-RtValue.Addr;
					memcpy( Buf+6*i+3, (uint08*)(&Temp32), 3 );
				}

				I2C_Write_Eeprom( ee_validnum_page, ee_validnum_inpage, Buf, ee_validnum_len ); //�洢����Ч��¼��ʼֵ��

				Flag = 1; //ͬ����EE
			}
		}
	}

	if( Flag )
	{
		I2C_Write_Eeprom( ee_synflash_page, ee_synflash_inpage, (uint08*)SynFlash.HisRec, ee_synflash_len );
	}
}


unsigned char ReadLoadRec( unsigned char Ch, unsigned char *InBuf, unsigned char *OutBuf )
//InBuf[0]: 0x11������; 0x12:������֡
//05�������ݱ�ʾ; 0A����ʱ��
//InBuf[2~5]:DI0~DI3
//InBuf[6]: NN��SN
//InBuf[7~10]:mmhhDDMMYY, ����ʱ��ʱ��Ч
{
	unsigned char i, t, Result, Spec; //00:δ��E2��ȡ; FF:��E2�ж�ȡ
	unsigned char RdBuf[64];
	struct
	{
		union B16_B08_2  Addr[2];	//[0~3]�����¼��; [4~7]�����¼��
		union B16_B08_2  RecTimes;
	} RdStr;
	unsigned char offset, len, n, num, Temp08, Glen;
	union B16_B08_2 Temp16;
	unsigned char BkClock[6], FirstVal[8]; //����ʱ��
	unsigned long TmpA;
	unsigned char Obj;
	RecStore RtRec;
	RtFlash  RtAddr;
	FindInf  RtValue;
	//���ɼ�¼��ز����б�              ��ѹ ���� �й����� �޹����� �������� �ܵ��� ������ ���� г�� ���� Ԥ�� ���1~4 ���5~8
	const unsigned char CaseTab[13] = { 0,   0,   1,       1,       2,       3,     4,     0,   0,   0,   0,   5,      6 };
	const unsigned char PosTab [13] = { 5,   7,   5,       8,       5,       5,     5,     5,   5,   5,   5,   5,      5 };
	const unsigned char LenTab [13] = { 2,   3,   3,       3,       2,       4,     4,     0,   0,   0,   0,   5,      5 };
	const unsigned char NumTab [13] = { 3,   3,   4,       4,       4,       4,     4,     0,   0,   0,   0,   4,      4 };

	Temp08 = 0;
	switch( InBuf[3] )
	{
		case 0x01: //��ѹ
		case 0x02: //����
			if( (InBuf[2] == 1) || (InBuf[2] == 0xFF) )
				Temp08 = 1;
			break;

		case 0x03: //�й�����
		case 0x04: //�޹�����
		case 0x05: //��������
			if( (InBuf[2] == 0) || (InBuf[2] == 0xFF) )
				Temp08 = 1;
			break;

		case 0x06: //�й��ܵ���+�޹��ܵ���
			if( (InBuf[4] == 0x11) && (InBuf[2] > 2) && (InBuf[2] != 0xFF) ) break;
		case 0x07: //�������޹�
		case 0x0C: //����й�1~4
//		case 0x0D: //����й�5~8
			if( ((InBuf[2] >= 1) && (InBuf[2] <= 4)) || (InBuf[2] == 0xFF) )
				Temp08 = 1;
			break;

		default:
			break;
	}

	if( Temp08 == 0 )
	{
		OutBuf[0] = 0xFF;
		OutBuf[1] = 0x02;	//���ݱ�ʶ��, ����������
		return 2;
	}

	i  = CaseTab[InBuf[3]-1]; //��i��
	len = LenTab[InBuf[3]-1]; //�����������ݳ���
	offset = PosTab[InBuf[3]-1]; //��¼��ƫ����
	num = 1; //��������
	if( InBuf[2] == 0xFF ) //���ݿ��ж������
	{
		num = NumTab[InBuf[3]-1];
		if( (InBuf[4] == 0x11) && (InBuf[3] == 0x06) )
			num -= 2;
	}
	else if( InBuf[2] )
		offset += (InBuf[2]-1)*len; //��¼��ƫ����

	Spec = Bcd_To_Hex(Display_Para.Lspacetimer[i].B08[1]); //���ɼ�¼���

	Obj = ee_minuten_inpage;
	RtRec = GetRecNum( Obj, i ); //��¼�洢����׼��
	RdStr.RecTimes.B16 = RtRec.ValPoint;
	if( RdStr.RecTimes.B16 == 0x00 ) return 0x00;

	//Addr: ��Ӧ��Ŀ��ַ [0~1]: �����¼; [2~3]: �����¼
	//RecTimes: ��Ӧ���ʣ����Ч��¼��
	//RdLoadPara: ���ݱ�ʶ(4)+ʣ���¼����(1)+����֡���(1)+��ʼ��ַ(4)+ʣ����Ч��¼��(2)+����ʱ��(5)+��һ�ε���(16)
	if( InBuf[0] == 0x12 ) //��ȡ����֡
	{
		if( RdLoadPara[Ch][4] == 0 ) return 0x00; //�޺���֡

		Result = Cmp_Data( RdLoadPara[Ch], InBuf+2, 4 );
		if( Result != 3 ) return 0x00; //���ݱ�ʶ��

		if( InBuf[6] != RdLoadPara[Ch][5] ) return 0x00; //֡��Ŵ���

		memcpy( RdStr.Addr[0].B08, RdLoadPara[Ch]+6, 6 );
		memcpy( BkClock+1, RdLoadPara[Ch]+12, 5 );

		t = 0x00;
	}
	else if( InBuf[0] == 0x11 ) //�����ɼ�¼
	{
		memset( RdLoadPara[Ch], 0x00, sizeof(RdLoadPara[Ch]) ); //ɾ����ʷ������¼, ���¼�¼

		RdLoadPara[Ch][4] = Bcd_To_Hex(InBuf[6]);	//�����ļ�¼����
		if( RdLoadPara[Ch][4] == 0x00 ) return 0x00; //��������������

		RtAddr = GetRecAddr( Obj, i, RtRec.ValPoint, &RtRec );  //�����¼��
		memcpy( FirstVal+1, RtAddr.Clk+1, 5 );

		//�Ӹ���ʱ�俪ʼ����һ�����ɼ�¼ʱ��
		memcpy( BkClock+1, InBuf+7, 5 );
		Result = CalcTime(BkClock+1)%Spec;
		if( Result )
		{
			Result = Spec-Result;
			Add_Min_Clock( BkClock, Result );
		}

		if( Cmp_Bcd_Inv( FirstVal+1, BkClock+1, 5 ) == 1 ) //�����¼ʱ����ڸ���ʱ��(0-A=B; 1:A>B; 2:A<B)
		{
			TmpA = CalcTime(FirstVal+1)/Spec-CalcTime(BkClock+1)/Spec;

			if( TmpA >= RdLoadPara[Ch][4] ) return 0x00;
			if( (TmpA==0) && (RdLoadPara[Ch][4]==1) ) return 0x00;

			RdLoadPara[Ch][4] -= TmpA;	//�۳�����Ŀ���

			//�������¼��ʼ����һ�����ɼ�¼ʱ��
			memcpy( BkClock+1, FirstVal+1, 5 );
			Result = CalcTime(BkClock+1)%Spec;
			if( Result )
			{
				Result = Spec-Result;
				Add_Min_Clock( BkClock, Result );
			}
		}

		if( Cmp_Bcd_Inv(BkClock+1, Sclock.Clockbackup+1, 5) == 1 ) return 0x00; //����ʱ����ڵ�ǰʱ�䣬�޼�¼
		if( EA_OFF ) return 0x00;	//���粻����

		BkClock[0] = 0; //��
		RtValue = FindSpecPos( Obj, i, BkClock, &RtRec );
		RdStr.Addr[0].B16 = RtValue.Addr;
		if( RtValue.Result == 0xFF ) RdStr.RecTimes.B16 = 0x00; //����ʱ��������м�¼ʱ�䣬��¼��Ч��������
		else RdStr.RecTimes.B16 = RtValue.Addr;

		if( len >= 4 ) //��������ʱ����Ҫȷ����һ�εĵ���������䶳����©��
		{
			if( RtValue.Result == 0xFF ) //����ʱ����ڼ�¼ʱ��
				Temp16.B16 = RdStr.Addr[0].B16;
			else //����ʱ��С�ڷ��صĵ�ַ��ָ��ļ�¼ʱ��
				Temp16.B16 = RdStr.Addr[0].B16+1;

			RtAddr = GetRecAddr( Obj, i, Temp16.B16, &RtRec );
			Temp08 = Flash_Rd_Bottom( RtAddr.AppPage, RtAddr.AppPos, RdBuf, RtRec.TotLen ); //��Flash�ж�ȡ
			if( Temp08 ) return 0x00;
			memcpy( RdLoadPara[Ch]+17, RdBuf+offset, num*len ); //����һ�ε���
		}

		t = 5;
		memcpy( OutBuf+1, BkClock+1, 5 );
	}
	else return 0x00;

	if( RdStr.RecTimes.B16 ) 	//���ڼ�¼ʱ��ȷ����E2�ж�ȡ
		memset( RdBuf, 0x00, 5 );
	else //û�м�¼ʱ, ȷ������ȡE2����
		memset( RdBuf, 0x99, 5 );

	Glen = len;
	if( (InBuf[4] == 0x11) && (len == 4) ) //�߾���
		Glen += 1;

	OutBuf[0] = 0x00;
	while( RdLoadPara[Ch][4] )
	{
		Clear_Wdt();

		if( EA_OFF ) return 0x00;	//���粻����

		if( Cmp_Bcd_Inv(BkClock+1, Sclock.Clockbackup+1, 5) == 1 )
		{
			RdLoadPara[Ch][4] = 0;
			break;
		}

		//----- Ԥ����ʱ�������м�¼�ܷ���ڴ�֡��------
		if( InBuf[0] == 0x11 ) Result = 4;	//���ݱ�ʶ
		else Result = 5; //���ݱ�ʶ+���

		if( t+num*Glen > 200-Result )
		{
			//������ǰ��Сʱ��ͳ������ڼ�����¼, ��ȡ����֡Ҫʹ��, �ﵽ���֡����, ������ѯ.
			//RdLoadPara: ���ݱ�ʶ(4)+ʣ���¼����(1)+����֡���(1)+��ʼ��ַ(4)+ʣ����Ч��¼��(2)+����ʱ��(5)+��һ�ε���(16)
			memcpy( RdLoadPara[Ch]+0, InBuf+2, 4 );
			RdLoadPara[Ch][5]++;	//����֡���
			memcpy( RdLoadPara[Ch]+ 6, RdStr.Addr[0].B08, 6 ); //��ַ(4)+ʣ���¼��(2)
			memcpy( RdLoadPara[Ch]+12, BkClock+1, 5 ); //����ʱ��
			break;
		}

		Result = Cmp_Bcd_Inv( RdBuf, BkClock+1, 5 ); //0-A=B; 1:A>B; 2:A<B
		if( Result == 2 ) //E2������������Ҫ���
		{
			while( RdStr.RecTimes.B16 )
			{
				Clear_Wdt();
				if( EA_OFF ) return 0x00;	//���粻����

				RtAddr = GetRecAddr( Obj, i, RdStr.Addr[0].B16, &RtRec );
				Temp08 = Flash_Rd_Bottom( RtAddr.AppPage, RtAddr.AppPos, RdBuf, RtRec.TotLen ); //��Flash�ж�ȡ
				if( Temp08 ) return 0x00;

				Result = Cmp_Bcd_Inv( RdBuf, BkClock+1, 5 ); //0-A=B; 1:A>B; 2:A<B
				if( Result != 1 ) //��¼ʱ��С�ڵ����ڴ�ʱ��
				{
					RdStr.RecTimes.B16--;
					RdStr.Addr[0].B16--;
				}

				if( Result != 2 ) break; //��¼ʱ����ڵ����ڴ�ʱ�䣬������ѯ
				if( len >= 4 ) memcpy( RdLoadPara[Ch]+17, RdBuf+offset, num*len ); //����һ�ε���
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
				memcpy( RdLoadPara[Ch]+17, RdBuf+offset, num*len ); //����һ�ε���

			for( n=0; n<num; n++ )
			{
				Temp08 = 1; //���� or ����
				if( ((InBuf[3] == 0x06) && ((n == 2)||(n == 3)||(InBuf[2] == 3)||(InBuf[2] == 4))) 
				 ||  (InBuf[3] >= 0x0C) )
					Temp08 = 0; //���

				memcpy( OutBuf+1+t, RdLoadPara[Ch]+17+n*len, len );
				if( Glen == 4 )
				{
					Hex2Bcd_Dl( OutBuf+1+t, Temp08 );//����ת��BCD��
				}
				else
				{
					if( (Temp08 == 0) && (OutBuf[1+t+4]&0x80) )
						memset( OutBuf+1+t+len, 0xFF, 8-len );
					else
						memset( OutBuf+1+t+len, 0x00, 8-len );
					Hex2Bcd_Dl_G( OutBuf+1+t, Temp08 ); //����ת��BCD��(�߾���)
					if( (Temp08 == 0) && (OutBuf[1+t+7]&0x80) ) OutBuf[1+t+4] |= 0x80;	//��ϵ���<0�����λ��1
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
