#include "ex_func.h"
#include "ex_var.h"
#include "FM32L0XX.h"  
#include <string.h>


void Calculate_Overflow( unsigned char *Buf, unsigned char Num )//��ϵ����߽紦��
{
	union B64_B08_2 Temp64;
	
	memset( Temp64.B08, 0x00, 8 );
	memcpy( Temp64.B08, Buf, Num );
	
	//��ϵ����߽紦��
	if( Temp64.B64 > 7999999999 )	//���: ����й�������޹�����ֵ��Χ��Ϊ��0.0000��799999.9999
	{
		Temp64.B64 -= 8000000000;	//�Դˣ�Ҫ���ڵ��Ｋ��ֵʱ���й��㴦��
		if( Temp64.B64 > 7999999999 )
		{
			Temp64.B64 -= 8000000000;
			if( Temp64.B64 > 7999999999 ) Temp64.B64 -= 8000000000;
		}
	}
	
	memcpy( Buf, Temp64.B08, Num );
}

void Calculate_Dl_G( unsigned char *Buf )//�������ʾֵ(�߾���8�ֽ�)
{
	union S64_B08_2 Temp64;
	
	//����������ת���ɸ߾��ȵ���(��λ0.0001kwh)
	memcpy( Temp64.B08, Buf, 8 );
	Temp64.S64 = (Temp64.S64*100/Meter.Const_H); 	//������ת���ɸ߾��ȵ���
	
	memcpy( Buf, Temp64.B08, 8 );
}

//������߷���(����4�ֽ�������)
void Hex2Bcd_Dl( unsigned char *Buf, unsigned char Di )//������תBCD����
{
	unsigned char Temp08=0;
	union B32_B08_2 Temp32;
	union B64_B08_2 Temp64;
	
	memcpy( Temp32.B08, Buf, 4 );
	
	if( Di==0 ) //������޹�������Ч
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
			
		Calculate_Overflow( Temp64.B08, 8 );//��ϵ����߽紦��
		Hex2Bcd_SS( Temp64.B08, Temp64.B08, 8 );
		memcpy( Buf, Temp64.B08+1, 4 );
		if( Temp08 ) Buf[3] |= 0x80;	//��ϵ���<0�����λ��1
	}
	else	//����
	{
		Temp32.B32 /= Meter.Const_H;
		Hex2Bcd_SS( Temp32.B08, Buf, 4 );
	}
}

//Di=0Ϊ���,����Ϊ������߷���(����8�ֽ�������)
void Hex2Bcd_Dl_G( unsigned char *Buf, unsigned char Di )//������תBCD����(�߾���)
{
	unsigned char Temp08=0;
	union B64_B08_2 Temp64;
	
	memcpy( Temp64.B08, Buf, 8 );
	
	Calculate_Dl_G( Temp64.B08 );//�߾��ȵ���(HEX��)
	
	if( Di==0 ) //���
	{	
		if( (signed long long)(Temp64.B64) < 0 )
		{
			Temp08 = 1;
			Temp64.B64 = (signed long long)(Temp64.B64)*(-1.0);
		}
		Calculate_Overflow( Temp64.B08, 8 );//��ϵ����߽紦��
		Hex2Bcd_SS( Temp64.B08, Buf, 8 );
		if( Temp08 ) Buf[7] |= 0x80;	//��ϵ���<0�����λ��1
	}
	else	//����
	{
		Hex2Bcd_SS( Temp64.B08, Buf, 8 );
	}
}

void Calc_Pwr_Proc()	//����������ۼƴ���ͽ���
{
	unsigned char i, j;
	unsigned int Page;	
	unsigned char Inpage;
	unsigned long int *Ptr32;
	
	if( EA_OFF ) return;//���粻����,����ֱ�ӷ���
	
	if( Decimal.Add_Rp ) //�޹�����
	{
		//�������޹�����
		if( Decimal.Add_Rp && (Decimal.Add_Rp <=(maxtimes*Meter.Const_H)) )
		{			
			if( (dl_back_flag == 0) && (dl_back_flag2 == 0) ) i=0;//��һ�����޹�
			else if( (dl_back_flag == 1) && (dl_back_flag2 == 0) ) i=1;//�ڶ������޹�
			else if( (dl_back_flag == 1) && (dl_back_flag2 == 1) ) i=2;//���������޹�
			else i=3;//���������޹�
			
			if( Rpdl_Verify(i)==0 )//�޹�����У��
			{
				Ptr32 = &(Rpdl[i].Pluse[0].B32);
				Page = ee_rpdl_page+2*i;
				Inpage = ee_rpdl_inpage;
				Decimal.Status |= (1<<i);		//���޹������ı��־
				
				{START_CRITICAL() 
				ENTER_CRITICAL();
				j = Decimal.Add_Rp;
				Decimal.Add_Rp = 0x00;	
				EXIT_CRITICAL();}
				
				for( ; j>0; j-- )
				{
					if( Ptr32[0]>=0x7fffffff ) continue;	//��������������ֵ
					else Ptr32[0] += 1;
					if( (Tariff.Current+1) > max_feilvcount ) Ptr32[1] += 1;
					else Ptr32[Tariff.Current+1] += 1;
					
					Crc_16Bits_Add2( (unsigned char *)&Ptr32[0], ee_rpdl_lenth );	//���¼���crc
						
					if( (Ptr32[0]%(Meter.Const_H*100))==0 )	//�й���������������
					{
						WriteE2WithBackup( Page, Inpage, (unsigned char *)&Ptr32[0], ee_rpdl_lenth );
						Decimal.Status &= ~(1<<i);	//���޹������ı��־
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
	
	if( Decimal.Add ) //�й�����
	{
		if( Decimal.Add > (maxtimes*Meter.Const_H) ){Decimal.Add = 0x00;return;}	//���������쳣
		
		if( dl_back_flag == 0 ) 
		{
			if( Fwdl_Verify() ) {Decimal.Add = 0x00;return;}			//�������У��
			Ptr32 = &(Fwdl.Pluse[0].B32);
			Page = ee_fwdl_page;
			Inpage = ee_fwdl_inpage;
		}
		else
		{
			if( Bkdl_Verify() ) {Decimal.Add = 0x00;return;}			//�������У��
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
			if( Ptr32[0]>=0xffffffff ) continue;	//��������������ֵ
			else Ptr32[0] += 1;
			if( (Tariff.Current+1) > max_feilvcount ) Ptr32[1] += 1;
			else Ptr32[Tariff.Current+1] += 1;
			Ptr32[max_feilvcount+1] += 1;//�����õ�������(������)
			
			//�й������޹�����ı�
			if( dl_back_flag == 0 ) Decimal.Status |= B0001_0000;	//����������ı��־
			else Decimal.Status |= B0010_0000;	//�÷�������ı��־
				
			Crc_16Bits_Add2( (unsigned char *)&Ptr32[0], ee_fwdl_lenth );	//���¼���crc
				
			if( (Ptr32[0]%(Meter.Const_H*100))==0 )	//�й���������������
			{
				WriteE2WithBackup( Page, Inpage, (unsigned char *)&Ptr32[0], ee_fwdl_lenth );
				if( dl_back_flag == 0 ) Decimal.Status &= (~B0001_0000);
				else Decimal.Status &= (~B0010_0000);
			}
			
			run_price_flag = 1;	//�÷��ʽ����жϱ�־
		}
	}
}


//offset=0��������,offset=3���������
//offset=1�½���,offset=4���½���
//offset=2�����,offset=5�������,offset=6�����ʱ������
void Process_Usedl( unsigned char offset )
{
	unsigned char i, len;
	unsigned char  Buf[ee_histroyusedl_lenth+8];
	
	memcpy( Buf, Sclock.Clockbackup+2, 4 );//����ʱ��
	Cal_Comb( 0, 0, 0, Buf+4 );	//���㵱ǰ��ϵ���	
//	Inverse( Buf+4, 4 );
	
	if( offset<3 ) 
	{				
		I2C_Read_Eeprom( ee_pre1_histroyusedl_page+offset, 0x00, Buf+8, ee_histroyusedl_lenth );//����1~6�ܵ���������1�ܵ���
		if( offset != 2 ) memcpy( Buf, Buf+4, ee_histroyusedl_lenth+4 ); //�����ս�����½������豣��ʱ��
	}
	else if( offset<6 )
	{
		offset -= 3;
		memset( Buf, 0x00, ee_histroyusedl_lenth );		//����1~7�ܵ���������1~2�ܵ���
	}
	else
	{
		offset = 2;
		memset( Buf, 0x00, 4 );			//ʱ������
	
		for( i=1; i<7; i++ )
		{
			memcpy( Buf+8*i, Buf, 8 );	//��1~6����ת��
		}
	}
	
	if( offset<2 )	len= ee_histroyusedl_lenth;
	else	len= ee_yhistroyusedl_lenth;

	I2C_Write_Eeprom( ee_pre1_histroyusedl_page+offset, 0x00, Buf, len );//��1~4�ܵ���ת��	
	
	Wr_Pretime_Hisfreeze();	//д��һ�ν���ʱ��
}


//type=0�����,��ת��,���õ���
//type=1�����,��ת��,�����õ���
//type=2�½���,��ת��,���õ���
void Freeze_Usedl( unsigned char type )//���㴦��
{
	Clear_Wdt();
	
	if( type == 0 )
	{
		Process_Usedl( 2 );	//��1��������ܵ���ת��
	}
	else
	{
		Process_Usedl( 1 );	//��1�½������ܵ���ת��
	}
	
	if( type == 1 )	return;//�����,��ת��,�����õ���
	
	if( Fwdl_Verify() ) return;	//�������У��
	memset( Fwdl.UPluse.B08, 0x00, 4 );//�����õ�������
//	Fw.UPluse.B32 = Fw.Pluse[0].B32%Meter.Const_H;//�������õ�������(������)
	Crc_16Bits_Add2( Fwdl.Pluse[0].B08, ee_fwdl_lenth ); //CRC����
	WriteE2WithBackup( ee_fwdl_page, ee_fwdl_inpage, Fwdl.Pluse[0].B08, ee_fwdl_lenth );
	
	if( Bkdl_Verify() ) return;	//�������У��
	memset( Bkdl.UPluse.B08, 0x00, 4 );//�����õ�������
//	Bk.UPluse.B32 = Bk.Pluse[0].B32%Meter.Const_H;//�������õ�������(������)
	Crc_16Bits_Add2( Bkdl.Pluse[0].B08, ee_bkdl_lenth ); //CRC����
	WriteE2WithBackup( ee_bkdl_page, ee_bkdl_inpage, Bkdl.Pluse[0].B08, ee_bkdl_lenth );
}


//���ᱣ��������,���ֽ���ǰ
void Freeze_Dl(unsigned int page, unsigned char offset)
{
	unsigned char Result, i;

	Clear_Wdt();

	memcpy( Eeprom.Buffer, Sclock.Clockbackup+1, 5 );
	
	memcpy( Eeprom.Buffer+5,  Fwdl.Pluse[0].B08, max_dl_lenth );
	memcpy( Eeprom.Buffer+5+max_dl_lenth, Bkdl.Pluse[0].B08, max_dl_lenth );
		
	for(i=0; i<4; i++) //�������޹�
	{
		memcpy( Eeprom.Buffer+5+max_dl_lenth*(2+i), Rpdl[i].Pluse[0].B08, max_dl_lenth );
	}
	
	if( page==ee_histroy_dl_page ) 		
	{
		memcpy( Eeprom.Buffer+ee_histroydl_lenth-3, &Mode.Comp_B, 1 );//�й������
		memcpy( Eeprom.Buffer+ee_histroydl_lenth-2, Mode.Rpcomp, 2 );//�޹������1��2
		
		Process_Usedl(0);//��1�������ܵ���ת��
		
		freeze_display_flag = 0; //������յ�������ʾ��־(������ת�����������Ҫˢ��)
	}
	else
	{
		memcpy( Eeprom.Buffer+ee_freezedl_lenth-8,  Emu_Data.P1.B08, 3 );//�й�����
		memcpy( Eeprom.Buffer+ee_freezedl_lenth-5,  Emu_Data.Q1.B08, 3 );//�޹�����
		if( dl_back_flag ) Eeprom.Buffer[ee_freezedl_lenth-6] |= 0x80;//�����й�����bit7��1
		if( dl_back_flag2 ) Eeprom.Buffer[ee_freezedl_lenth-3] |= 0x80;//�����޹�����bit7��1
		
		memcpy( Eeprom.Buffer+ee_freezedl_lenth-2, Mode.Rpcomp, 2 );//�޹������1��2
	}
	
	Result = Write_Event_Point(offset);
	
	I2C_Write_Eeprom( page+3*Result+0, 0x00, Eeprom.Buffer, 128 );	//����ʱ��+��������
	I2C_Write_Eeprom( page+3*Result+1, 0x00, Eeprom.Buffer+128, 128 );	//��������
	I2C_Write_Eeprom( page+3*Result+2, 0x00, Eeprom.Buffer+256, ee_freezedl_lenth-256 );	//��������
	SynEeprom(); //ͬ�����ᵽFlash
	
	if( page==ee_dayfreezedl_page ) //�յ�ѹ�ϸ��ʼ�¼ת��
	{
		//�յ�ѹ�ϸ��ʼ�¼
		CalLoad( Eeprom.Buffer, 0 );
		Result = Write_Event_Point(ee_dayvolpassn_inpage);
		I2C_Write_Eeprom( ee_dayvolpass_note_page+Result/4, ee_dayvolpassnote_inpage+(Result%4)*ee_dayvolpassnote_len, Eeprom.Buffer, ee_dayvolpassnote_len );
		InitVolSts( 0 ); //�����Ӧ�ĵ�ѹ�ϸ���
		
		Wr_Pretime_Dayfreeze();	//д��һ���ն���ʱ��
	}		
	if( page==ee_monthfreeze_page ) //�µ�ѹ�ϸ��ʼ�¼ת��
	{
		//�µ�ѹ�ϸ��ʼ�¼
		CalLoad( Eeprom.Buffer, 1 );
		Result = Write_Event_Point(ee_monvolpassn_inpage);
		I2C_Write_Eeprom( ee_monvolpass_note_page+Result/4, ee_monvolpassnote_inpage+(Result%4)*ee_monvolpassnote_len, Eeprom.Buffer, ee_monvolpassnote_len );
		InitVolSts( 1 ); //�����Ӧ�ĵ�ѹ�ϸ���
	}		
}

void Hour_Freeze_Dl(unsigned int page,unsigned char offset)//���㶳����߰�㶳��
{
	unsigned char Result,inpage;
	
	memcpy( Eeprom.Buffer, Sclock.Clockbackup+1, 5 );
	DltoEepromBuf( 5 );
	Result = Write_Event_Point(offset);
	inpage = ee_hourfreezedl_inpage+(Result%4)*13;
	I2C_Write_Eeprom( page+(Result>>2), inpage, Eeprom.Buffer, ee_hourfreezedl_lenth );
	SynEeprom(); //ͬ�����ᵽFlash
}


//status=0��ʾͣ�����,status=1��ʾ�ϵ����
//RAMREG5����������,RAMREG6������մ���,RAMREG7�������һ�����մ���,RAMREG8�½�����һ�����մ���,�ϵ粹��ʹ��
//Ic_Comm_RxBuf��Ϊ����ʱ����ʱ������
void Histroy_Freeze_Dl(unsigned char status)//����������ᴦ��
{
	unsigned char Result=0;
	unsigned char  Buf[10];
	
//	if( BDMODE )//���طѿص��ܱ�
//	{
		//�������
		Result = Year_Ladder_Judge(status); //����������жϺ����ݺϷ����ж�
		
		if( (Price.Ladder_Mode == 0x55) && (Sclock.Clockbackup[3] <= 0x28) &&
			( (Cmp_Data( Price.Year_Ladder+0, Sclock.Clockbackup+2, 3 ) == 0x03) 
			|| (Cmp_Data( Price.Year_Ladder+3, Sclock.Clockbackup+2, 3 ) == 0x03)
			|| (Cmp_Data( Price.Year_Ladder+6, Sclock.Clockbackup+2, 3 ) == 0x03)
			|| (Cmp_Data( Price.Year_Ladder+9, Sclock.Clockbackup+2, 3 ) == 0x03)
			|| (Cmp_Data( Price.Year_Ladder+12, Sclock.Clockbackup+2, 3 ) == 0x03)
			|| (Cmp_Data( Price.Year_Ladder+15, Sclock.Clockbackup+2, 3 ) == 0x03) )	)//ʱ�������
		{
		  	if( (Result!=0x55)&&(Result!=0x5a) )
		  	{
		  		if( status ) Freeze_Usedl(0);//�����,���õ���ת�������
		  		else
		  		{
		  			if( RAMREG5 < 7 ) RAMREG5++;	//֧����1~��6���õ���
		  			memcpy( Ic_Comm_RxBuf+60, Ic_Comm_RxBuf+60+4, 24 );//��λ��ʷͣ�������ʱ��
					memcpy( Ic_Comm_RxBuf+60+24, Sclock.Clockbackup+2, 4 );//���浱ǰͣ�������ʱ��(ʱ������)
		  		}
		  	}
		}
//	}
//	else
//	{
//		Price.Ladder_Mode = 0x00;	//��֧�������
//	}
	
	//�������ж�
	ReadE2WithBackup( ee_histroyparameter_page, ee_histroyparameter_inpage, Buf, ee_histroyparameter_lenth );
	if( ((Buf[0]== Sclock.Clockbackup[2]) && (Buf[1]== Sclock.Clockbackup[3])) ||
	    ((Buf[2]== Sclock.Clockbackup[2]) && (Buf[3]== Sclock.Clockbackup[3])) ||
	    ((Buf[4]== Sclock.Clockbackup[2]) && (Buf[5]== Sclock.Clockbackup[3])) ) 
	{
		//�������ж�
		if( (Result!=0x5a)&&(Result!=0xaa) )
		{
			if( status ) Freeze_Dl(ee_histroy_dl_page,ee_histroyf_inpage);
			else
			{
				if( RAMREG6 < 12+12 ) RAMREG6++;
				memcpy( Ic_Comm_RxBuf+100, Ic_Comm_RxBuf+100+4, 92 );//��λ��ʷͣ�綳��ʱ��
				memcpy( Ic_Comm_RxBuf+100+92, Sclock.Clockbackup+2, 4 );//���浱ǰͣ�綳��ʱ��(ʱ������)
			}
		}
		
		//��һ�������ж�
		if((Buf[0]== Sclock.Clockbackup[2]) && (Buf[1]== Sclock.Clockbackup[3]))
		{
			//�������һ������
			if( Price.Ladder_Mode == 0x55 )
			{
				if( Result!=0x5a)
				{
					if( status ) Freeze_Usedl(1);//�����,��ת��
					else
					{
						if( RAMREG7 < 12+12 ) RAMREG7++;
					}
				}
			}
			else//�½�����һ������
			{
				if( Result!=0xaa)
				{
					if( status ) Freeze_Usedl(2);//�½���,���õ���ת�������
					else
					{
						if( RAMREG8 < 12+12 ) RAMREG8++;
					}
				}			
			}
		}	
	}
}


void Freeze_Judge()	//����ͽ����ж�
{
	unsigned char i;
	unsigned char  Result,Buf[20];
	
	run_freeze_flag = 0;
	run_loadchk_flag = 1;
	
	I2C_Read_Eeprom44( ee_freezeparameter_page, Buf, ee_freezeparameter_lenth );
		
	if( EA_ON && ((Cmp_Clock( Buf, 5 ) != 0x01)) )//���㶳����ʼʱ��<=��ǰʱ��
	{
		Result = Sclock.Clockbackup[1];
		if( (Result == 0) || ((Result == 0x30)&&(Buf[5] == 0x30)) )
		{
			Hour_Freeze_Dl(ee_hourfreezedl_page,ee_hourf_inpage);//���㶳��
		}
	}
	
	if( EA_ON && (Cmp_Clock( Buf+6, 2 ) == 0x03) ) 
	{
		Freeze_Dl(ee_dayfreezedl_page,ee_dayf_inpage); //�ն���ʱ��=��ǰʱ��,�ն���
	}
        
	for(i=0; i<3; i++)
	{
		if(Buf[8+i]== 0x99) Buf[8+i] = Sclock.Clockbackup[4-i];
	}
	if( EA_ON && ((Cmp_Clock( Buf+8, 4 ) == 0x03)) ) 
	{
		Freeze_Dl(ee_timingfreeze_dl_page,ee_timingf_inpage); //��ʱ����
	}
	
	if( (0x00== Sclock.Clockbackup[1]) && (0x00== Sclock.Clockbackup[2]) && (0x01== Sclock.Clockbackup[3]) )
	{
		Freeze_Dl( ee_monthfreeze_page, ee_monthn_inpage );//�¶���
		
		if( 0x01== Sclock.Clockbackup[4] )	//1��1��00:00
		{
			month_change_flag = 1;
			year_change_flag = 1;
			year_change_flag2 = 1;
		}
		else
		{
			month_change_flag = 1;
		}
		Freeze_Pddata();	//�����������
	}	
		
	if( Sclock.Clockbackup[1]== 0x00 )//���ӵ���0
	{
		Histroy_Freeze_Dl(1);//����������ᴦ��
	}				
}


void Pd_Hourfreeze_Judge()	//�ϵ����㶳��Ͷ�ʱ���Ჹ���жϴ���
{
	unsigned int  i;
	unsigned char result;
	unsigned char Buf[ee_freezeparameter_lenth+2], BufA[6], BufB[ee_powerdown_lenth+2], BufC[7];
	
	if(clock_error) return;	//��ǰʱ��Ƿ�
	
	if( I2C_Read_Eeprom( ee_power_down_page, 0x00, BufB, ee_powerdown_lenth )  ) return;//������ʱ��(��ʱ������)
	if( JudgeClockNoWeek( 1, BufB+1, 5 ) ) return;	//ʱ��Ƿ�
	memcpy( BufC, BufB, 7 );//����ԭ����ʱ��
	
	memcpy( BufA, Sclock.Clockbackup, 6 );//��ǰʱ��(���ʱ������)
	
	result = Cmp_Bcd_Inv( BufA+1, BufB+1, 5 );//�ȽϷ�ʱ������5�ֽ�
	if( result != 1 ) return;//A=B����A<B,����
		
	I2C_Read_Eeprom44( ee_freezeparameter_page, Buf, ee_freezeparameter_lenth );
	
	BufB[0] = 0;//��
	if( BufB[1] >= 0x30 ) BufB[1] = 0x30;//����
	else BufB[1] = 0;//����
	for( i=0; i<0x5fff; i++ )	//�ͣ�粻����1��
	{
		Clear_Wdt();
		Add_Min_Clock( BufB, 30 ); //��30���Ӵ���
		
		result = Cmp_Bcd_Inv( BufA+1, BufB+1, 5 );//�ȽϷ�ʱ������5�ֽ�
		if( result == 2 ) break;//A<B,����
		
		memcpy( Sclock.Clockbackup+1, BufB+1, 5 );//���µ�ǰʱ��(��ͣ��ʱ��)
		if( Cmp_Clock( Buf, 5 ) != 0x01 )//���㶳����ʼʱ��<=��ǰʱ��
		{
			result = Sclock.Clockbackup[1];
			if( (result == 0) || ((result == 0x30)&&(Buf[5] == 0x30)) )
			{
				Hour_Freeze_Dl(ee_hourfreezedl_page,ee_hourf_inpage);//���㶳��(��ͣ����һ��������)
				break;
			}
		}
	}
	
	memcpy( BufB, BufC, 7 );//����ʱ��
	BufB[0] = 0;//��
	for(i=0; i<4; i++)
	{
		if( Buf[11-i] != 0x99 ) 
			BufB[1+i] = Buf[11-i];
	}
	
	result = Cmp_Bcd_Inv( BufB+1, BufC+1, 5 );//�ȽϷ�ʱ������5�ֽ�
	if( result ) //����ʱ�� ������ ����ʱ�䣬����ʱ���1
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

		result = Cmp_Bcd_Inv( BufA, BufB, 6 );//���ʱ������
		if( result == 1 ) //��ǰʱ�� > ����ʱ��
		{
			memcpy( Sclock.Clockbackup+1, BufB+1, 5 );//���µ�ǰʱ��(��ͣ��ʱ��)
			Freeze_Dl(ee_timingfreeze_dl_page,ee_timingf_inpage); //��ʱ����(��ͣ����һ��������)
		}
	}
	
	//�����ն��Ჹ��(��ͣ����һ��������)
	memcpy( BufB, BufC, 7 );//����ʱ��
	BufB[0] = 0;//��
	BufB[1] = Buf[7];//�ն����
	BufB[2] = Buf[6];//�ն���ʱ
	
	result = Cmp_Bcd_Inv( BufB+1, BufC+1, 5 );//�ȽϷ�ʱ������5�ֽ�
	if( result ) //����ʱ�� ������ ����ʱ�䣬����ʱ���1
	{
		if( result == 2 )//B < C
		{
			AddNClock( 3, BufB, 1 );
		}

		result = Cmp_Bcd_Inv( BufA, BufB, 6 );//���ʱ������
		if( result == 1 ) //��ǰʱ�� > ����ʱ��
		{
			memcpy( Sclock.Clockbackup+1, BufB+1, 5 );//���µ�ǰʱ��(��ͣ��ʱ��)
			Freeze_Dl(ee_dayfreezedl_page,ee_dayf_inpage); //�ն��Ჹ��(��ͣ����һ��������)
		}
	}
	
	Syn_Clock();	//ͬ��ʱ��
}


void Pd_Calculate_Judge()	//ͣ��ͳ��ʱ������жϴ���	
{
	unsigned int  i;
	unsigned char result, flag;
	unsigned char Buf[8], BufA[6], BufB[ee_powerdown_lenth+2], BufC[7], BufD[6];
	union B32_B08_2 Temp32;
	
	if(clock_error) return;	//��ǰʱ��Ƿ�
	
	if( I2C_Read_Eeprom( ee_power_down_page, 0x00, BufB, ee_powerdown_lenth )  ) return;//������ʱ��(��ʱ������)
	if( JudgeClockNoWeek( 1, BufB+1, 5 ) ) return;	//ʱ��Ƿ�
	memcpy( BufC, BufB, 7 );//����ԭ����ʱ��
	
	memcpy( BufA, Sclock.Clockbackup, 6 );//��ǰʱ��(���ʱ������)
	
	//�������¼
	if( ChkPdRcdTime() == 1 ) return;	//������¼������ͳ��
	
	//��ͣ��ͳ�Ʋ��洦��
	flag = 0;
	memcpy( BufD, BufC, 6 );//����ʱ��
	memcpy( BufB, BufC, 6 );//����ʱ��
	BufB[0] = 0;//��
	BufB[1] = 0;//��
	BufB[2] = 0;//ʱ
	BufB[3] = 1;//��
	for( i=0; i<=36+1; i++ )
	{
		Clear_Wdt();
		AddNClock( 4, BufB, 1 );	//MM
		
		result = Cmp_Bcd_Inv( BufA, BufB, 6 );//���ʱ������
		if( result == 1 ) //��ǰʱ�� > ��ʱ��
		{
			//ͳ����ʷ����
			if( flag == 0 )
			{
				Get_Keep_Timer(8, Buf);//����ͣ���ۼƴ���
				Get_Keep_Timer(9, Buf+4);//����ͣ���ۼ�ʱ��(���ڴ���Ϊ0�ۼ�ʱ����ֵ�����)
				Bcd2Hex_SS( Buf+4, Temp32.B08, 4 );
				Temp32.B32 += (CalcTime( BufB+1 )- CalcTime( BufD+1 ));
				Hex2Bcd_SS( Temp32.B08, Buf+4, 4 );
				result = Write_Event_Point(ee_monpowerdownn_inpage);
				I2C_Write_Eeprom( ee_powerdown_month_page+result/8, (result%8)*8, Buf, ee_powerdownmonth_lenth );
				{Clr_Otherdata(8);Clr_Otherdata(9);}//��ͣ��ͳ������
			}
			else
			{
				memset( Buf, 0x00, 4 );//��ͣ���ۼƴ���Ϊ0
				Temp32.B32 = CalcTime( BufB+1 )- CalcTime( BufD+1 );
				Hex2Bcd_SS( Temp32.B08, Buf+4, 4 );
				result = Write_Event_Point(ee_monpowerdownn_inpage);
				I2C_Write_Eeprom( ee_powerdown_month_page+result/8, (result%8)*8, Buf, ee_powerdownmonth_lenth );
			}
			
			memcpy( BufD, BufB, 6 );//��ʱ��
			flag = 1;//����  
		}
		else
		{
			//ͳ�Ƶ�ǰ����
			Keeptime.Times[9] = CalcTime( BufA+1 )- CalcTime( BufD+1 );
			break;
		}
	}
	
	//��ͣ��ͳ�Ʋ��洦��
	flag = 0;
	memcpy( BufD, BufC, 6 );//����ʱ��
	memcpy( BufB, BufC, 6 );//����ʱ��
	BufB[0] = 0;//��
	BufB[1] = 0;//��
	BufB[2] = 0;//ʱ
	BufB[3] = 1;//��
	BufB[4] = 1;//��
	for( i=0; i<=3+1; i++ )
	{
		Clear_Wdt();
		AddNClock( 5, BufB, 1 );	//YY
		
		result = Cmp_Bcd_Inv( BufA, BufB, 6 );//���ʱ������
		if( result == 1 ) //��ǰʱ�� > ��ʱ��
		{
			//ͳ����ʷ����
			if( flag == 0 )
			{
				Get_Keep_Timer(10, Buf);//����ͣ���ۼƴ���
				Get_Keep_Timer(11, Buf+4);//����ͣ���ۼ�ʱ��(���ڴ���Ϊ0�ۼ�ʱ����ֵ�����)
				Bcd2Hex_SS( Buf+4, Temp32.B08, 4 );
				Temp32.B32 += (CalcTime( BufB+1 )- CalcTime( BufD+1 ));
				Hex2Bcd_SS( Temp32.B08, Buf+4, 4 );
				result = Write_Event_Point(ee_yearpowerdownn_inpage);
				I2C_Write_Eeprom( ee_powerdown_year_page, (result%8)*8, Buf, ee_powerdownyear_lenth );
				{Clr_Otherdata(10);Clr_Otherdata(11);}//��ͣ��ͳ������
			}
			else
			{
				memset( Buf, 0x00, 4 );//��ͣ���ۼƴ���Ϊ0
				Temp32.B32 = CalcTime( BufB+1 )- CalcTime( BufD+1 );
				Hex2Bcd_SS( Temp32.B08, Buf+4, 4 );
				result = Write_Event_Point(ee_yearpowerdownn_inpage);
				I2C_Write_Eeprom( ee_powerdown_year_page, (result%8)*8, Buf, ee_powerdownyear_lenth );
			}
			
			memcpy( BufD, BufB, 6 );//��ʱ��
			flag = 1;//����  
		}
		else
		{
			//ͳ�Ƶ�ǰ����
			Keeptime.Times[11] = CalcTime( BufA+1 )- CalcTime( BufD+1 );
			break;
		}
	}
}


void Pd_Histroyfreeze_Judge()	//�ϵ�����ղ����жϴ���
{
	unsigned int  i;
	unsigned char result;
	unsigned char Buf[5],BufA[5],BufB[10];
	
	if(clock_error) return;	//��ǰʱ��Ƿ�
	
	I2C_Read_Eeprom( ee_pre_history_page, ee_prehistory_inpage, BufB+1, ee_prehistory_lenth );//����һ�ν���ʱ��(��ʱ������)
	if( JudgeClockNoWeek( 1, BufB+1, 5 ) ) return;	//ʱ��Ƿ�
	
	memcpy( BufA, Sclock.Clockbackup+1, 5 );//��ǰʱ��(��ʱ������)
	
	result = Cmp_Bcd_Inv( BufA, BufB+1, 5 );//�ȽϷ�ʱ������5�ֽ�
	if( result != 1 ) return;//A=B����A<B,����
	
	RAMREG5 = 0;//����������
	RAMREG6 = 0;//������մ���
	RAMREG7 = 0;//�������һ�����մ���
	RAMREG8 = 0;//�½�����һ�����մ���
	
	BufB[0] = 0;//��
	BufB[1] = 0;//����
	for( i=0; i<0x6fff; i++ )	//�ͣ�粻����3��
	{
		Clear_Wdt();
		Add_Min_Clock( BufB, 60 ); //��60���Ӵ���
		
		result = Cmp_Bcd_Inv( BufA, BufB+1, 5 );//�ȽϷ�ʱ������5�ֽ�
		if( result == 2 ) break;//A<B,����
		else if( (result == 0) && run_freeze_flag ){run_freeze_flag = 0;run_loadchk_flag = 1;}
		
		memcpy( Sclock.Clockbackup+1, BufB+1, 5 );//���µ�ǰʱ��(���ܴ��ڽ��ݵ������)
		Histroy_Freeze_Dl(0);	//����������ᴦ��(��Ҫ��֤��������crc�Ѿ���ȷ)
	}
	memcpy( Sclock.Clockbackup+1, BufA, 5 );//�ָ���ǰʱ��(��ʱ������)
	run_timezone_flag = 1;
	
	//�����ᴦ��
	if( ((RAMREG5 > 0)&&(RAMREG5 < 8)) || ((RAMREG7 > 0)&&(RAMREG7 < 13+12)) )
	{
		memcpy( Buf, Sclock.Clockbackup+2, 4 );//���浱ǰʱ��(ʱ������)
		for( i=0; i<RAMREG5; i++ )
		{	
			memcpy( Sclock.Clockbackup+2, Ic_Comm_RxBuf+60+28-(RAMREG5-i)*4, 4 );//����ʱ��
			Freeze_Usedl(0);//�����,���õ���ת�������
		}
		memcpy( Sclock.Clockbackup+2, Buf, 4 );//�ָ���ǰʱ��(ʱ������)		
	
		for( i=0; i<RAMREG7; i++ )
		{	
			Freeze_Usedl(1);//�����,��ת��
		}
	}
	
	if( (RAMREG8 > 0) && (RAMREG8 < 13+12) )
	{
		for( i=0; i<RAMREG8; i++ )
		{	
			Freeze_Usedl(2);//�½���,���õ���ת�������
		}
	}
	
	if( (RAMREG6 > 0) && (RAMREG6 < 13+12) )
	{
		memcpy( Buf, Sclock.Clockbackup+2, 4 );//���浱ǰʱ��(ʱ������)
		for( i=((RAMREG6 < 13) ? 0 : (RAMREG6-12)); i<RAMREG6; i++ )	//�����ĵ�Ҫ��12��
		{	
			Clear_Wdt();
			memcpy( Sclock.Clockbackup+2, Ic_Comm_RxBuf+100+96-(RAMREG6-i)*4, 4 );//����ʱ��			
			Freeze_Dl(ee_histroy_dl_page,ee_histroyf_inpage); //���㶳��
		}
		memcpy( Sclock.Clockbackup+2, Buf, 4 );//�ָ���ǰʱ��(ʱ������)
	}
	
	if( RAMREG5||RAMREG6||RAMREG7||RAMREG8 ) Wr_Pretime_Hisfreeze();	//д��һ�ν���ʱ��
}


//void Init_Dayfreeze_Judge()	//�ն��Ჹ���ж�
//{
//	unsigned char i, n, k,result,result1,result2;
//	unsigned char Buf[50],BufA[6],BufB[6],BufC[6];
//	const unsigned char code days[] = { 0, 0x31, 0x28, 0x31, 0x30, 0x31, 0x30, 0x31, 0x31, 0x30, 0x31, 0x30, 0x31 };
//	
//	if(clock_error) return;	//��ǰʱ��Ƿ�
//	
//	I2C_Read_Eeprom( ee_pre_dayfreeze_page, ee_predayfreeze_inpage, BufB, ee_predayfreeze_lenth );//����һ���ն���ʱ��(��ʱ������)
//	if( JudgeClockNoWeek( 1, BufB, 5 ) ) return;	//ʱ��Ƿ�
//											
//	memcpy( BufA, Sclock.Clockbackup+1, 5 );//��ǰʱ��(��ʱ������)
//	
//	result = Cmp_Bcd_Inv( BufA, BufB, 5 );//�ȽϷ�ʱ������5�ֽ�
//	if( result != 1 ) return;//A=B����A<B,����
//	
//	I2C_Read_Eeprom44( ee_freezeparameter_page, Buf, ee_freezeparameter_lenth );//���ն���ʱ��
//
//	//���ÿ���ն���ʱ��
//	memcpy( BufC, BufA, 5 );//��ǰʱ��
//	BufC[0] = Buf[7];//�ն����
//	BufC[1] = Buf[6];//�ն���ʱ
//	
//	n = 0;
//	for( i=0; i<8; i++ )
//	{
//		result1 = Cmp_Bcd_Inv( BufB, BufC, 5 );
//		result2 = Cmp_Bcd_Inv( BufA, BufC, 5 );
//		
//		//BufB<BufC<=BufA��
//		if((result1==2)&&(result2!=2))
//		{
//			n++;//���ն��������1
//			memcpy( Buf+n*5, BufC, 5 );//����ʱ��
//		}
//		
//		//����ʱ���1��
//		if( BufC[2] == 0x01 )//�Ƚϵ�ǰ���Ƿ�Ϊ1
//		{
//			if( BufC[3] == 0x01 )
//			{
//				BufC[4] = Hex_To_Bcd(Bcd_To_Hex(BufC[4])-1);//���1
//				BufC[3] = 0x12;//12��
//				BufC[2] = 0x31;//31��
//			}
//			else
//			{
//				BufC[3] = Hex_To_Bcd(Bcd_To_Hex(BufC[3])-1);//�¼�1
//				//�����ж�
//				k = days[Bcd_To_Hex(BufC[3])];
//				if( (BufC[3] == 0x02) && ((Bcd_To_Hex(BufC[4])%4)==0 ) ) k++;	//����
//				BufC[2] = k;//�����
//			}	
//		}
//		else
//		{
//			BufC[2] = Hex_To_Bcd(Bcd_To_Hex(BufC[2])-1);//�ռ�1
//		}
//	}
//	
//	if( n > 7 ) n = 7;
//	
//	if( n )
//	{
//		memcpy( Buf, Sclock.Clockbackup+1, 5 );//���浱ǰʱ��(��ʱ������)
//		
//		for(i=0; i<n; i++)
//		{
//			memcpy( Sclock.Clockbackup+1, Buf+(n-i)*5, 5 );//����ʱ��
//			Freeze_Dl(ee_dayfreezedl_page,ee_dayf_inpage); //�ն��Ჹ��
//		}
//	
//		memcpy( Sclock.Clockbackup+1, Buf, 5 );//�ָ���ǰʱ��(��ʱ������)
//	}
//}

void Wr_Pretime_Hisfreeze()//����д/����д/Уʱд
{	
	unsigned char Buf[ee_prehistory_lenth+2];
	
	I2C_Read_Eeprom( ee_pre_history_page, ee_prehistory_inpage, Buf, ee_prehistory_lenth );//����һ�ν���ʱ��
	if( Cmp_Bcd_Inv( Buf,  Sclock.Clockbackup+1, 5 )==0 ) return;	//ʱ�����ֱ�ӷ���
	I2C_Write_Eeprom( ee_pre_history_page, ee_prehistory_inpage, Sclock.Clockbackup+1, ee_prehistory_lenth );//д��һ�ν���ʱ��
}

void Wr_Pretime_Dayfreeze()//�ն���д/����д/Уʱд/�����ն���ʱ��д
{
//	I2C_Write_Eeprom( ee_pre_dayfreeze_page, ee_predayfreeze_inpage, Sclock.Clockbackup+1, ee_predayfreeze_lenth );//д��һ���ն���ʱ��
}

void Freeze_Pddata()		//����ͣ��ͳ������
{
	unsigned char Result, Buf[8];
	
	if( month_change_flag || year_change_flag )
	{
		if( month_change_flag )
		{
			month_change_flag = 0;
			
			Get_Keep_Timer(8, Buf);//����ͣ���ۼƴ���
			Get_Keep_Timer(9, Buf+4);//����ͣ���ۼ�ʱ��
			Result = Write_Event_Point(ee_monpowerdownn_inpage);
			I2C_Write_Eeprom( ee_powerdown_month_page+Result/8, (Result%8)*8, Buf, ee_powerdownmonth_lenth );
			{Clr_Otherdata(8);Clr_Otherdata(9);}//��ͣ��ͳ������
		}
		
		if( year_change_flag )
		{
			year_change_flag = 0;
			
			Get_Keep_Timer(10, Buf);//����ͣ���ۼƴ���
			Get_Keep_Timer(11, Buf+4);//����ͣ���ۼ�ʱ��
			Result = Write_Event_Point(ee_yearpowerdownn_inpage);
			I2C_Write_Eeprom( ee_powerdown_year_page, (Result%8)*8, Buf, ee_powerdownyear_lenth );
			{Clr_Otherdata(10);Clr_Otherdata(11);}//��ͣ��ͳ������
		}
	}
	
	if( year_change_flag2 )
	{
		year_change_flag2 = 0;
		
		//�͵�ѹ�¼��͸ߵ�ѹ�¼����괦��
		if( lower_v_event_flag )
		{
//			Get_Keep_Timer(6, Buf+4);	//���͵�ѹ�ۼ�ʱ��:����4�ֽ�ʱ��(Buf[4]~Buf[7])
//			Result = Read_Event_Point(ee_lowervn_inpage);
//			I2C_Write_Eeprom( ee_lowerv_note_page+Result, ee_lowervnote_inpage+8, Buf+4, 4 );//����͵�ѹ�ۼ�ʱ��(һ��)
//			{lower_v_flag = 0;Current_Over_Count4 = 0;lower_v_event_flag = 0;Current_Over_Count41 = 0;Clr_Otherdata(6);Store_Meterstatus();}//�͵�ѹ����ʱ��
			Note_Run_Event(ee_lowervn_inpage|0x80);//��¼�͵�ѹ�¼�(����)
			{lower_v_flag = 0;Current_Over_Count4 = 0;lower_v_event_flag = 0;Current_Over_Count41 = 0;Store_Meterstatus();}//�͵�ѹ����ʱ��	
		}
		else
		{
			Current_Over_Count41 = 0;
		}
			
		if( high_v_event_flag )
		{
//			Get_Keep_Timer(7, Buf+4);	//���ߵ�ѹ�ۼ�ʱ��:����4�ֽ�ʱ��(Buf[4]~Buf[7])
//			Result = Read_Event_Point(ee_highvn_inpage);
//			I2C_Write_Eeprom( ee_highv_note_page+Result, ee_highvnote_inpage+8, Buf+4, 4 );//����ߵ�ѹ�ۼ�ʱ��(һ��)
//			{high_v_flag = 0;Current_Over_Count5 = 0;high_v_event_flag = 0;Current_Over_Count51 = 0;Clr_Otherdata(7);Store_Meterstatus();}//�ߵ�ѹ����ʱ��
			Note_Run_Event(ee_highvn_inpage|0x80);//��¼�ߵ�ѹ�¼�(����)
			{high_v_flag = 0;Current_Over_Count5 = 0;high_v_event_flag = 0;Current_Over_Count51 = 0;Store_Meterstatus();}//�ߵ�ѹ����ʱ��
		}
		else
		{
			Current_Over_Count51 = 0;
		}
	}
}


uint32		Uav_Temp_Day;	//����1��ƽ����ѹ �ۼ�ֵ
//Mode = 0:������յĵ�ѹ�ϸ������ݣ�1��������µĵ�ѹ�ϸ�������
void InitVolSts( unsigned char Mode )
{
	memset( VolStatus[Mode&0x01].Total.B08, 0x00, ee_monthvolrun_lenth/2 ); //�����Ӧ�ĵ�ѹ�ϸ���
	I2C_Write_Eeprom( ee_monthvolrun_page, ee_monthvolrun_inpage, VolStatus[0].Total.B08, ee_monthvolrun_lenth );
	
	if( Mode == 0 )	Uav_Temp_Day = 0;
}


//��ѹ�ϸ������д�����
void VolPassRate( void )
{
	union B16_B08_2 Temp16;
	unsigned char Mode;
	
	Temp16.B08[0] = Emu_Data.U.B08[0];
	Temp16.B08[1] = Emu_Data.U.B08[1];

	for( Mode=0; Mode<2; Mode++ ) //�պ���
	{
		if( VolStatus[Mode].Total.B32 < (VolStatus[Mode].HighTime.B32+VolStatus[Mode].LowTime.B32) )
		{
			InitVolSts(Mode);	//�����Ӧ�ĵ�ѹ�ϸ���
		}
		
//		//����ƽ����ѹ
//		VolStatus[Mode].AverVol.B16 = Emu_Data.Uav.B32; //ʹ��ǰ1���ӵ�ƽ����ѹ
		
		if( (Temp16.B16 > Byte2Short(VolLimit.ChkMaxVol.B08)) || (Temp16.B16 < Byte2Short(VolLimit.ChkMinVol.B08)) ) continue; //��ѹ���ڿ������޻��ѹС�ڿ������޲��ۼӿ���ʱ��
	
		if( Sclock.Clockbackup[0] == 0x00 )
		{
			VolStatus[Mode].Total.B32++;
			
			if( Temp16.B16 > Byte2Short(VolLimit.MaxVolLmt.B08) ) //��ǰ��ѹ > ��ѹ����ֵ, ������ʱ���1
			{
				VolStatus[Mode].HighTime.B32++;
			}
			else if( Temp16.B16 < Byte2Short(VolLimit.MinVolLmt.B08) )	//��ǰ��ѹ < ��ѹ����ֵ, ������ʱ���1
			{
				VolStatus[Mode].LowTime.B32++;
			}
		}
		
		if( (Temp16.B16 == Byte2Short(VolLimit.ChkMaxVol.B08)) || (Temp16.B16 == Byte2Short(VolLimit.ChkMinVol.B08)) ) continue; //��ѹ���ڿ������޻��ѹ���ڿ������޲�ˢ����ʷ����
	
		if( Temp16.B16 > VolStatus[Mode].MaxVol.B16 )	//��ǰ��ѹ > ��ʷ����ѹ, ������ʷ����ѹΪ��ǰ��ѹ
		{
			if( (VolStatus[Mode].MaxMoment[2+Mode] == Sclock.Clockbackup[3+Mode]) || (VolStatus[Mode].MaxMoment[2+Mode] == 0) ) //���������/��
			{
				VolStatus[Mode].MaxVol.B16 = Temp16.B16;
				memcpy( VolStatus[Mode].MaxMoment, Sclock.Clockbackup+1, 4 );
			}
			else continue;
		}
		
		if( (Temp16.B16 < VolStatus[Mode].MinVol.B16) || (VolStatus[Mode].MinVol.B16 == 0) )	//��ǰ��ѹ < ��ʷ��С��ѹ, ������ʷ��С��ѹΪ��ǰ��ѹ
		{
			if( (VolStatus[Mode].MinMoment[2+Mode] == Sclock.Clockbackup[3+Mode]) || (VolStatus[Mode].MinMoment[2+Mode] == 0) ) //���������/��
			{
				VolStatus[Mode].MinVol.B16 = Temp16.B16;
				memcpy( VolStatus[Mode].MinMoment, Sclock.Clockbackup+1, 4 );
			}
			else continue;
		}
		
		//����ƽ����ѹ
		if( Mode == 0 ) //������ƽ����ѹ
		{
			union B32_B08_2 S1_Temp;	
			
			if( (Uav_Temp_Day == 0) && VolStatus[Mode].AverVol_Cnt.B32 && VolStatus[Mode].AverVol.B16 ) //�ϵ�ָ�
			{
				 S1_Temp.B32 = VolStatus[Mode].AverVol.B16;
				 Bcd2Hex_SS( S1_Temp.B08, S1_Temp.B08, 4 );
				 Uav_Temp_Day = S1_Temp.B32*VolStatus[Mode].AverVol_Cnt.B32;
			}
			
			Bcd2Hex_SS( Emu_Data.U.B08, S1_Temp.B08, 4 );
			Uav_Temp_Day += S1_Temp.B32;	//�ۼ�1��ƽ����ѹֵ
			VolStatus[Mode].AverVol_Cnt.B32++;
			
			S1_Temp.B32 = Uav_Temp_Day/VolStatus[Mode].AverVol_Cnt.B32;		//������ƽ����ѹ
			Hex2Bcd_SS(S1_Temp.B08, S1_Temp.B08, 4);
			memcpy( VolStatus[Mode].AverVol.B08, S1_Temp.B08, 2);
		}
	}
}

//Mode = 0:�����յ�ѹ�ϸ������ݣ�1�������µ�ѹ�ϸ�������
void CalLoad( unsigned char *Buf, unsigned char Mode )
{
	union B32_B08_2 Rate, Temp32, Total, High, Low;

	Mode &= 0x01;
	if( VolStatus[Mode].Total.B32 < (VolStatus[Mode].HighTime.B32+VolStatus[Mode].LowTime.B32) )
	{
		InitVolSts(Mode);	//�����Ӧ�ĵ�ѹ�ϸ���
	}
	
	//��ѹ�ϸ��ʼ�¼
	Total.B32 = VolStatus[Mode].Total.B32;
	High.B32  = VolStatus[Mode].HighTime.B32;
	Low.B32   = VolStatus[Mode].LowTime.B32;

	Hex2Bcd_SS( Total.B08, Temp32.B08, 4 );
	memcpy( Buf, Temp32.B08, 3 );	//��ѹ���ʱ��	3	XXXXXX	��
	
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
	memcpy( Buf+3, Temp32.B08, 3 );	//��ѹ�ϸ���	3	XXXX.XX	%
	
	Hex2Bcd_SS( Rate.B08, Temp32.B08, 4 );
	memcpy( Buf+6, Temp32.B08, 3 );	//��ѹ������	3	XXXX.XX	%
	
	Hex2Bcd_SS( High.B08, Temp32.B08, 4 );
	memcpy( Buf+9, Temp32.B08, 3 );	//��ѹ������ʱ��	3	XXXXXX	��

	Hex2Bcd_SS( Low.B08, Temp32.B08, 4 );
	memcpy( Buf+12, Temp32.B08, 3 );//��ѹ������ʱ��	3	XXXXXX	��
	
	memcpy( Buf+15, VolStatus[Mode].MaxVol.B08, 2 );	//��ߵ�ѹ	XXX.X	2	V
	memcpy( Buf+17, VolStatus[Mode].MaxMoment, 4 );

	memcpy( Buf+21, VolStatus[Mode].MinVol.B08, 2 );	//��͵�ѹ	XXX.X	2	V
	memcpy( Buf+23, VolStatus[Mode].MinMoment, 4 );
	
	memcpy( Buf+27, VolStatus[Mode].AverVol.B08, 2 );	//ƽ����ѹ	XXX.X	2	V
}


void Judge_Relay_Delay()	//�������ʱ��բ�ж�
{
//	if( Relay_Mode != 0x55 )//���ü̵���
	{
		if( over_xxx_flag && CurrentTimer )//��բʱ����������ֵ��ʱ��բ
		{
			if( relay_commu_open_flag && (Opendelaytimer == 0x00)  ) relay_delay_flag = 1;//�ô������ʱ��բ��־
			else
			{
				CurrentTimer = Calculate_Timer(1);
				relay_delay_flag = 0;	//��������ʱ��բ��־
			}
		}
		else relay_delay_flag = 0;	//��������ʱ��բ��־
	}
//	else	relay_delay_flag = 0;	//��������ʱ��բ��־
}				


void Closerelay1()               //�պϼ̵���
{
	if( Relay_Mode != 0x55 )//���ü̵���
	{
		Relayctrl.Timer = Relaytimer_Delay_N;
		RELAYOFF2;
		__NOP();
		__NOP();
		RELAYON1;
	}
	else
	{
		if(Mode.Feature1&0x01)//���巽ʽ
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
	if( Relay_Mode != 0x55 )//���ü̵���
	{
		Relayctrl.Timer = Relaytimer_Delay_N;
		RELAYOFF1;
		__NOP();
		__NOP();
		RELAYON2;
	}
	else
	{
		if(Mode.Feature1&0x01)//���巽ʽ
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

void Init_Metererrstatus()	//����̵�������״̬
{
	relay_error = 0;
	Relayerror_Count  = 0;
	Relayerror_Count1 = Defrelayerrorcnt_s;//��ֵ��ʼ����
	Relayerror_Count2 = Defrelayerrorcnt_s;//��ֵ��ʼ����
	relay_failed_flag = 0;	//��̵��������־(�ϱ�)
	Store_Meterstatus();
}


void Closerelay()               //�պϼ̵���(��д״̬��)
{
	if( (relay_status_flag == 0) && (relay_direct_flag == 0) ) return;
	
	Closerelay1();
	if( relay_status_flag == 1 )
	{
		if( relay_error ) Note_Run_Event(ee_relayerrn_inpage|0x80);	//���ɿ����쳣������¼
		relay_status_flag = 0;
		relay_success_flag = 0;	//��̵����ɹ���־
		relay_success2_flag = 0;
		Init_Metererrstatus();	//����̵�������״̬
		Note_Relay_Event();//����բ��¼
	}
	Relay_Space_Timer = 0;	
}


void Openrelay()                //�Ͽ��̵���(��д״̬��)	
{
	if( relay_status_flag && (relay_direct_flag ==0 ) )  return;
	
	Judge_Relay_Delay();	//�������ʱ��բ�ж�
	if( relay_delay_flag ) return;	//�������ʱ��բ
	
	Openrelay1();
	if( relay_status_flag == 0 ) 
	{
		if( relay_commu_open_flag )
		{
			Opendelaytimer = 0x00;	//�Ѿ���բ������բ��ʱ
		}
		
		if( relay_error ) Note_Run_Event(ee_relayerrn_inpage|0x80);	//���ɿ����쳣������¼
		relay_status_flag = 1;
		relay_success_flag = 0;	//��̵����ɹ���־
		relay_success2_flag = 0;
		if( Relay_Mode == 0x55 ) relay_cleardl_flag = 0; //�����ñ�������־
		Init_Metererrstatus();	//����̵�������״̬
		Note_Relay_Event();//����բ��¼
	}
	Relay_Space_Timer = 0;
}


void Mt_Alarmstatus_Judge()	//�����״̬�ж�
{
	Esam_Para_Verify();	//�������1,2�Ȳ���(ESAMһ�ಿ�ֲ���)У��

	if( EA_ON && ( below_70u_flag == 0 ) )
	{
		//�̵�������
		if ( relay_commu_disable_close_flag )//������պϼ̵���(ֻ�в忨�ſ�������)
		{
			Openrelay();
		}
		else if ( relay_commu_close_flag )//�������ȼ����
		{
			Closerelay();
		}
		else if( (relay_commu_open_flag && (Opendelaytimer == 0x00)) )//ͨѶ�Ͽ��̵������ȼ���֮
		{
			Openrelay();
		}
		else//���������̵����պ�
		{
			Closerelay();
		}
		
		relay_direct_flag = 0;//��̵���ֱ�Ӷ�����־
	}
	
	run_alarm_flag = 0;		

}
