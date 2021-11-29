#include "ex_func.h"
#include "ex_var.h"
#include "FM32L0XX.h"  
#include <string.h>



void RefreshPrice( void )
{
	run_price_flag = 1;
	Price.Crc16a.B08[0] += 1;
}


//offset=0ʱ��,offset=1ʱ��,offset=2����ʱ��,offset=3����
void Changecontrol_Process(unsigned char offset)//��ת�����ֽ�,������ʱ��ͽ���Լ������
{
	unsigned char i;
	
	Clear_Wdt();
	
	if( offset < 2 )
	{
		//��ת������
		I2C_Read_Eeprom44( ee_changecontrol_page, Eeprom.Buffer, ee_changecontrol_lenth);//�����������ֽ�
		if (Eeprom.Buffer[offset] == 0x55)
		{
			Eeprom.Buffer[offset]=0xff;
		}
		else
		{	
			Eeprom.Buffer[offset]=0x55;
		}
		
		I2C_Write_Eeprom44( ee_changecontrol_page, Eeprom.Buffer, ee_changecontrol_lenth);
	}
	else if( offset == 3 )
	{	
		for( i=0; i<4; i++ )
		{
			ReadE2WithJieti ( 4+i, Price.Ladder_Dl[0].B08 );//�������׽��ݵ���/���/�����ʱ�串�ǵ�ǰ
			WriteE2WithJieti( i, Price.Ladder_Dl[0].B08 );
		}
		RefreshPrice();
	} 
	else if( offset == 2 )
	{
		I2C_Read_Eeprom ( ee_jtshiqu2_page, ee_jtshiqu_inpage, Eeprom.Buffer, ee_jtshiqu_len ); //�����ݽ���ʱ�����ǵ�ǰ
		I2C_Write_Eeprom( ee_jtshiqu1_page, ee_jtshiqu_inpage, Eeprom.Buffer, ee_jtshiqu_len );
		RefreshPrice();
	}
	else return;
	
	//������ʱ��
	memset( Starttime.Shiqu+offset*5, 0x00, 5 );	
	WriteE2WithBackup(ee_starttimer_page, ee_starttimer_inpage, Starttime.Shiqu, ee_starttimer_lenth);
	
	//����Լ������
	Freeze_Dl(ee_appointfreeze1_page+6*offset,3+offset);
}


unsigned char FindSQ( unsigned char Num )
{
	unsigned char i, k, n;

	Sequence( Eeprom.Buffer, Num );//ʱ�α�����
	
	for( i=0, k=0, n=0; i<Num; i++ )
	{
		if( (n != 0xff) && (Cmp_Bcd_Inv(Eeprom.Buffer+k+1,Sclock.Clockbackup+3,2) == 1) )
		{
			if( i == 0 ) n = 0xff; //С�ڵ�һʱ��,��Ϊ���ʱ��
			else break;
		}

		k += 3;
		if( ChkBufZero(Eeprom.Buffer+k+1, 2) == 0 ) break; //������+��Ϊ��,��Ч
	}
	
	return (Eeprom.Buffer[k-3]);//�õ�ʱ�α��
}


void Config_Shiduan_Process()//�ҵ���ǰʱ���õ���ǰʱ�α�
{
	unsigned char i,t,n,k,page;
	unsigned char Buf[16];
	
	I2C_Read_Eeprom44( ee_changecontrol_page, Buf+7, ee_changecontrol_lenth);//�����������ֽ�
	if( Buf[7] != 0x55 ) page = ee_shiqu1_page;//��һ��Ϊ��ǰʱ��
	else page = ee_shiqu2_page;//�ڶ���Ϊ��ǰʱ��
	if ( I2C_Read_Eeprom( page, 0, Eeprom.Buffer, ee_shiqu_lenth )!= 0x00)
	{
		I2C_Read_Eeprom( page, 0, Eeprom.Buffer, ee_shiqu_lenth);
	}
	//ʱ���ж�(ʱ�α��+��+��)
	t = Bcd_To_Hex(Feik.Num[0]);
	if( (t == 0) || (t > 14) ) t = 1;
	n = FindSQ(t);	//�õ�ʱ�α��
	
	if( Buf[8] != 0x55 ) page = ee_shiduantable1_1_page;//��һ��Ϊ��ǰʱ�α�
	else page = ee_shiduantable2_1_page;//�ڶ���Ϊ��ǰʱ�α�

	//�������ж�
	if( Sclock.Clockmain[3] <= 6 )//����ǷǷ����ܾͲ��ж�������
	{
		if( ((Week_Holiday.Status>>Sclock.Clockmain[3]) & B0000_0001)==0 )//0������Ϣ,1������
		{
			n = Week_Holiday.Shiduan_N;
		}
	}
	//�ڼ����ж�
	t = Bcd_To_Hex(Feik.Num[4]);
	if( t <= max_maxholiday )//���֧��60���ڼ���
	{
		for( i=0; i<t; i++ )
		{
			if( (i%15) == 0 )
			{
				k = 0;
				if( I2C_Read_Eeprom( ee_holiday_page+(i/15), 0x00, Eeprom.Buffer, ee_holiday_lenth ) )
				{
					I2C_Read_Eeprom( ee_holiday_page+(i/15), 0x00, Eeprom.Buffer, ee_holiday_lenth );//�ٶ�һ��
				}
			}
			
			if( Cmp_Data( Eeprom.Buffer+1+k, Sclock.Clockbackup+3, 3 ) == 3 ) //�Ƚ�������
			{
				n = Eeprom.Buffer[k];
				break;
			}

			k += 4;
		}
	}
	if( (n == 0)||(n > 8) ) n=1; 
	else if( n > Feik.Num[1] )  n=1; 	//��ʱ�α�Ŵ�����ʱ������Ĭ��Ϊ1
	n--;
	Tariff.Current_N = n;
	I2C_Read_Eeprom( page+n, 0x00, Tariff.Table, ee_shiduantable_lenth);	
}


//���ݽ���ʱ����ȷ�����ݱ�
void Config_ShiQuLad_Proc( void )
{
	unsigned char n;

	I2C_Read_Eeprom ( ee_jtshiqu1_page, ee_jtshiqu_inpage, Eeprom.Buffer, ee_jtshiqu_len ); //������ʱ����
	
	//ʱ���ж�(���ݱ��+��+��)
	n = FindSQ(4);	//�õ����ݱ��
	
	//����ǰ���ݱ�
	if( (n == 0) || (n > 2) ) n = 1;
	n--;
	Tariff.CurLad_N = n;
	ReadE2WithJieti( Tariff.CurLad_N, Price.Ladder_Dl[0].B08 ); //����ǰ�׽��ݵ���/���/�������
}


void Sequence( unsigned char *Buf, unsigned char Num )//����+����+Сʱ
{
	unsigned char i, n;
	unsigned char BufB[3];

	if( Num < 2 ) return;
	
	for( n=0; n<Num-1; n++ )
	{
		for (i=0; i<Num-1-n; i++)
		{
			if ( Cmp_Bcd_Inv( Buf+i*3+1, Buf+(i+1)*3+1, 2 ) == 0x01 ) //ǰ���� > ������
			{
				memcpy( BufB, Buf+i*3, 3 );//��������
				memcpy( Buf+i*3, Buf+(i+1)*3, 3 );//��������
				memcpy( Buf+(i+1)*3, BufB, 3 );//��������
			}
		}
	}
}
	

void Timezone_Judge()	//ʱ��ʱ�η����ж�
{
	unsigned char i,t,Result,Status=0;
	unsigned char BufA[42];

	feik_Num_Verify();
	if( run_timezone_flag && ( EA_OFF ) ) return;
	Starttimer_Verify();//����ʱ��У��
	if( run_timezone_flag && ( EA_OFF ) ) return;
	Week_Holiday_Verify();//�����ղ���У��
	
	run_timezone_flag = 0;
//	if( BDMODE ) //����ģʽ
		run_price_flag = 1;
//	else
//		run_alarm_flag = 1;

	//����ʱ���ж�
	if( !clock_error ) 
	{
		if((Cmp_Clock( Starttime.Shiqu, 5 ) != 0x01) && ChkBufZero( Starttime.Shiqu, 5 ))
		{
			Changecontrol_Process(0);//��ת�����ֽ�,������ʱ��ͽ���Լ������
			Status = 0x01;//�����ж�ʱ�α�
		}
		if((Cmp_Clock( Starttime.Shiduan, 5 ) != 0x01) && ChkBufZero( Starttime.Shiduan, 5 ))
		{
			Changecontrol_Process(1);//��ת�����ֽ�,������ʱ��ͽ���Լ������
			Status = 0x01;//�����ж�ʱ�α�
		}
	}
	//ʱ��У��
	if( Status == 0x01 || Sclock.Clockbackup[1]==0 )//����ʱ�䵽����ÿСʱ
	{	
		Config_Shiduan_Process();//�ҵ���ǰʱ���õ���ǰʱ�α�
	}
	else if( Crc_Check( Tariff.Table, ee_shiduantable_lenth+2 ) ) 
	{
		Config_Shiduan_Process();//�ҵ���ǰʱ���õ���ǰʱ�α�
	}
	//�����ж�(����+����+Сʱ)
	t = Bcd_To_Hex(Feik.Num[2]);
	if ( (t == 0) || (t > max_shiduancount) ) t=1;
	memcpy( BufA, Tariff.Table, 42 );//����ʱ�α�
	Sequence( BufA, t );//ʱ�α�����
	t = t*3;//ʱ����*3
	for (i=0; i<t; i++)
	{
		if ( ((BufA[i+2] > Sclock.Clockbackup[2])) 
			|| ((BufA[i+2] == Sclock.Clockbackup[2]) 
			&& (BufA[i+1] > Sclock.Clockbackup[1])) ) 
		{
			if( i == 0 ) i=t;//С�ڵ�һʱ��,��Ϊ���ʱ��
			i = i - 3;
			break;
		}
//		if ( (i >=3) && (BufA[i]==0) && (BufA[i+1]==0) )
//		{
//			i = i - 1;//����ʱ�η��Ӻ�Сʱ��Ϊ0,��Ч
//			break;
//		}
		i++;
		i++;	
	}
	if( i == t ) i = i - 3; //���һ��ʱ��(��ע�����һ��ʱ������Ϊ0)
	if( (BufA[i]==0) || (Bcd_To_Hex(BufA[i])>Bcd_To_Hex(Feik.Num[3])) ) Tariff.Current = 0;	//�Ƿ�Ĭ��Ϊ�����
	else Tariff.Current = Bcd_To_Hex(BufA[i])-1;
	Result = i/3;//�õ���ǰʱ�κ�
	if(Result != Tariff.Period_N) 
	{
		if( Outputtype==0x02 )
		{
			Shiduanctrl.Timer = shiduanctrl_timer_delay;
			SHIDUANCTRL_ON;//
		}
	}
	Tariff.Period_N = Result;//���µ�ǰʱ�κ�	
	
	//����״̬��
	Tariff.Status &= B0000_0011;
	I2C_Read_Eeprom44( ee_changecontrol_page, Eeprom.Buffer, ee_changecontrol_lenth);//�����������ֽ�
	if ( Eeprom.Buffer[0] == 0x55 ) Tariff.Status |= B0000_1000;//��ǰʱ��
	if ( Eeprom.Buffer[1] == 0x55 ) Tariff.Status |= B0000_0100;//��ǰʱ�α�
}


unsigned char JudgeYearClock( unsigned char *YearLadder )//�ж�������պϷ���(�������ֻ����1��12����ĳ�µ�1����28���ڵ�����ʱ��)
{
	unsigned char i;
	
	for (i=0; i<6; i++)
	{
		if( JudgeClockNoWeek( 2, YearLadder+3*i, 3 ) == 0 )
		{
			if( YearLadder[1+3*i] <= 0x28 )  return 0;//��ȷ
		}
	}
	
	return 1;//����
}


unsigned char Freeze_Change_Judge( unsigned char Change )//���㷽ʽ�任�жϼ�����
{
	unsigned char status;
	
	if(Change&0x80) status = 0;//Ϊ1��ʾ�����е���,Ϊ0��ʾ��ʼ������
	else status = 1;
	Change &= 0x7f;
	
	if( JudgeYearClock( Price.Year_Ladder ) == 0 )
	{
		if( Price.Ladder_Mode == 0x00 )
		{
			//�½��㵽�����
			if( status ) Freeze_Usedl(2);//�½���,���õ���ת�������
			else
			{
				if( RAMREG8 < 12+12 ) RAMREG8++;
			}
			
			if( status ) Freeze_Dl(ee_histroy_dl_page,ee_histroyf_inpage);
			else
			{
				if( RAMREG6 < 12+12 ) RAMREG6++;
				memcpy( Ic_Comm_RxBuf+100, Ic_Comm_RxBuf+100+4, 92 );//��λ��ʷͣ�綳��ʱ��
				memcpy( Ic_Comm_RxBuf+100+92, Sclock.Clockbackup+2, 4 );//���浱ǰͣ�綳��ʱ��(ʱ������)
			}
				
			Price.Ladder_Mode = 0x55;//�����ģʽ	
			Process_Usedl(6);//�������õ�����0��ʼ	
			return 0x5a;	//���ڷ�ֹ�ظ��������õ������½���				
		}
		else if( Change == 1 ) 	//������ոı�
		{
			//������л��������
			if( status ) Freeze_Usedl(0);//�����,���õ���ת�������
	  		else
	  		{
	  			if( RAMREG5 < 7 ) RAMREG5++;	//֧����1~��4���õ���
	  			memcpy( Ic_Comm_RxBuf+60, Ic_Comm_RxBuf+60+4, 24 );//��λ��ʷͣ�������ʱ��
				memcpy( Ic_Comm_RxBuf+60+24, Sclock.Clockbackup+2, 4 );//���浱ǰͣ�������ʱ��(ʱ������)
	  		}
			return 0x55;	//���ڷ�ֹ�ظ��������õ���
		}
	}
	else
	{
		if( Price.Ladder_Mode == 0x55 )
		{
			//����㵽�½���
			if( status ) Freeze_Usedl(0);//�����,���õ���ת�������
	  		else
	  		{
	  			if( RAMREG5 < 7 ) RAMREG5++;	//֧����1~��4���õ���
	  			memcpy( Ic_Comm_RxBuf+60, Ic_Comm_RxBuf+60+4, 24 );//��λ��ʷͣ�������ʱ��
				memcpy( Ic_Comm_RxBuf+60+24, Sclock.Clockbackup+2, 4 );//���浱ǰͣ�������ʱ��(ʱ������)
	  		}
	  		Price.Ladder_Mode = 0x00;//�½���ģʽ
			if( status ) Freeze_Usedl(1);//�����,��ת��
			else
			{
				if( RAMREG7 < 12+12 ) RAMREG7++;
			}
					
			if( status ) Freeze_Dl(ee_histroy_dl_page,ee_histroyf_inpage);
			else
			{
				if( RAMREG6 < 12+12 ) RAMREG6++;
				memcpy( Ic_Comm_RxBuf+100, Ic_Comm_RxBuf+100+4, 92 );//��λ��ʷͣ�綳��ʱ��
				memcpy( Ic_Comm_RxBuf+100+92, Sclock.Clockbackup+2, 4 );//���浱ǰͣ�綳��ʱ��(ʱ������)
			}
			
			return 0xaa;	//���ڷ�ֹ�ظ��������õ���
		}
//		else
//		{
//			//�½����л����½���
//			Freeze_Usedl(2);//�½���,���õ���ת�������
//			Freeze_Dl(ee_histroy_dl_page,ee_histroyf_inpage);			
//		}
	}
	
	return 0x00;
}

void Ladderdata_Check()
{
	if( Crc_Check( Price.Ladder_Dl[0].B08, ee_ladder_lenth+2 ) ) 
	{
		Config_ShiQuLad_Proc();//�ҵ���ǰʱ���õ���ǰ���ݱ�
	}
}	


unsigned char Year_Ladder_Judge(unsigned char status)//����������жϺ����ݺϷ����ж�
{
	unsigned char Buf[ee_curyearjs_len+2];
	
	ReadE2WithBackup( ee_curyearjs_page, ee_curyearjs_inpage, Buf, ee_curyearjs_len );
	
	if( JudgeYearClock( Buf ) == 0 ) Price.Ladder_Mode = 0x55;//�����ģʽ
	else  Price.Ladder_Mode = 0x00;//�½���ģʽ
	
	//��������ʱ���ж�
	if( !clock_error )
	{
		//����ʱ������ʱ���ж�
		if((Cmp_Clock( Starttime.LadSQ, 5 ) != 0x01) && ChkBufZero( Starttime.LadSQ, 5 ))
		{
			Changecontrol_Process(2);//��ת�����ֽ�,������ʱ��ͽ���Լ������
		}

		if((Cmp_Clock( Starttime.Ladder, 5 ) != 0x01) && ChkBufZero( Starttime.Ladder, 5 ))
		{
			Changecontrol_Process(3);//��ת�����ֽ�,������ʱ��ͽ���Լ������			
		}
	}

	//���ݱ�У��
	if( Sclock.Clockbackup[1]==0 )//����ʱ�䵽����ÿСʱ
	{	
		Config_ShiQuLad_Proc();//�ҵ���ǰʱ���õ���ǰ���ݱ�
	}
	else 
	{
		Ladderdata_Check();
	}
		
	//�µ�������պ͵�ǰ��������б仯����ת��Ͷ���
	if( Cmp_Data(Price.Year_Ladder, Buf, ee_curyearjs_len) != 3 )  
	{
		WriteE2WithBackup( ee_curyearjs_page, ee_curyearjs_inpage, Price.Year_Ladder, ee_curyearjs_len );
		
		if( status )	return Freeze_Change_Judge(1);	//������ոı�
		else 	return Freeze_Change_Judge(0x81);	//(��ʼ������)������ոı�
	}
	else
	{
		if( status )	return( Freeze_Change_Judge(0) );//��������ʱ�䵽,���㷽ʽ�任�жϼ�����,�������δ�ı�
		else 	return( Freeze_Change_Judge(0x80) );//(��ʼ������)��������ʱ�䵽,���㷽ʽ�任�жϼ�����,�������δ�ı�
	}
}


void Price_Judge()	//���ʽ��ݵ���ж�
{
	unsigned char i,t;
	unsigned char BufA[8];
	unsigned long int Ratio;
	union B32_B08_2 Temp32A,Temp32B;

	run_price_flag = 0;
	run_alarm_flag = 1;
	
	//��������У��
	Ladderdata_Check();
	
//	//��������ʱ���ж�
//	if( !clock_error )
//	{
//		if((Cmp_Clock( Starttime.Rate, 5 ) != 0x01) && ChkBufZero( Starttime.Rate, 5 ))
//		{
//			Changecontrol_Process(2);//��ת�����ֽ�,������ʱ��ͽ���Լ������
//		}
//	}
//	//���ʵ�۱�У��
//	if( Crc_Check( Price.Tariff[0].B08, ee_tariffprice_lenth+2 ) ) 
//	{
//		I2C_Read_Eeprom( ee_tariffprice1_page, 0, Price.Tariff[0].B08, ee_tariffprice_lenth);//����ǰ���ʵ��
//	}
	
	//�жϵ�ǰ����
//	t = Feik.Num[6];//������(1~6),������Ϊ0���޽��ݹ���
	t = 6;//6�����ݵ���
	for (i=0; i<5; i++)
	{
		if ( Byte2uInt(Price.Ladder_Dl[5-i].B08) == Byte2uInt(Price.Ladder_Dl[4-i].B08) ) t--;//��ͬ��������1
		else break;
	}
	
	if( (t > 0) && ( Byte2uInt( Price.Ladder_Dl[t-1].B08 ) == 0) ) t--;//�����ݵ���Ϊ0,���������1
	
	if( t == 0 )	//�жϽ��ݵ����Ƿ�Ϊȫ0
	{
		Tariff.Current_Ladder = 0xff;//�޽���
		memset( Price.Current_L.B08, 0x00, 4);//��ǰ���ݵ��Ĭ��Ϊ0
	}
	else
	{
		Temp32A.B32 = 0;
		Temp32B.B32 = 0;	
//		memcpy( Temp32A.B08, Fwdl.UPluse.B08, 4 );//�����õ���(������)
//		memcpy( Temp32B.B08, Bkdl.UPluse.B08, 4 );//�����õ���(������)
		if( Mode.Comp_B&B0000_0001 ) memcpy( Temp32A.B08, Fwdl.UPluse.B08, 4 );//�����õ���(������)
		if( Mode.Comp_B&B0000_0100 ) memcpy( Temp32B.B08, Bkdl.UPluse.B08, 4 );//�����õ���(������)
//		Temp32A.B32 -= Temp32A.B32%Meter.Const_H;//С��0.01kwh�������õ����ļ���Ϳ۷�
//		Temp32B.B32 -= Temp32B.B32%Meter.Const_H;//С��0.01kwh�������õ����ļ���Ϳ۷�
		Temp32A.B32 += Temp32B.B32;	//�����õ���+�����õ���=���õ���(������)
		Temp32A.B32 /= Meter.Const_H;
		Hex2Bcd_SS( Temp32A.B08, Temp32A.B08, 4 );
//		memcpy( BufA, Fwdl.Usedl.B08, 4 );	//�����õ���
//		Add_Bcd( BufA, Bkdl.Usedl.B08, 4 );	//�����õ���+�����õ���=���õ���
		for (i=0; i<t; i++)
		{
			if ( Temp32A.B32 < Byte2uInt(Price.Ladder_Dl[i].B08) ) //A<B
			{
				break;//�ҵ�
			}
		}//i�ķ�Χ0~6
		Tariff.Current_Ladder = i;//��ǰ����
		memcpy( Price.Current_L.B08, Price.Ladder[i].B08, 4);//���ݵ��
	}
		
	//������
//	memcpy( Price.Current_F.B08, Price.Tariff[Tariff.Current&B0000_0011].B08, 4);//���ʵ��
	memcpy( Price.Current.B08, Price.Current_L.B08, 4);//���㵱ǰ���=���ݵ��+���ʵ��
//	Add_Bcd( Price.Current.B08, Price.Current_F.B08, 4 );
			
	//������
	BufA[0] = 0;
	BufA[4] = 0;
	Bcd2Hex( Esam_Para.Current_Ratio, BufA+1, 3 );//�������
	Bcd2Hex( Esam_Para.Voltage_Ratio, BufA+5, 3 );//��ѹ���
	Ratio = Byte2uInt( BufA )* Byte2uInt( BufA+4 );//�������hex*��ѹ���hex
	if ( (Ratio==0) || (Ratio>=10000) ) Ratio = 1;	
		
	//������Ա�ȵĽ��ݵ�ۺͷ��ʵ��
	Bcd2Hex( Price.Current.B08, BufA, 4 );//��ǰ���hex
	Int2Byte( (Byte2uInt(BufA)*Ratio), BufA);//���*��ǰ���(hex)
	Hex2Bcd( BufA, Price.Current_X.B08, 4 );//���*��ǰ���(bcd)
	
	//����״̬��
	Tariff.Status &= B0000_1100;
//	if( JudgeSwitch( Starttime.Rate,1) == 0 )  Tariff.Status |= B0000_0010;//����ʱ��Ϸ�,��ʾ��2�׷��ʵ��
	if( JudgeSwitch( Starttime.Ladder,1) == 0 ) Tariff.Status |= B0000_0001;//����ʱ��Ϸ�,��ʾ��2�׽��ݵ��
}


//Ch=0,1,2,3����ǰ��,��������CRC
//Ch=4,5,6,7��������
void ReadE2WithJieti( uint08 Ch, uint08 *Buf )	//�����ݵ���/���/�������/CRC
{
	I2C_Read_Eeprom( ee_ladder1_page+Ch, 0, Buf, ee_ladder_lenth+2 );
}
		

void WriteE2WithJieti( uint08 Ch, uint08 *Buf )	//д���ݵ���/���/�������
{
	Crc_16Bits_Add2( Buf, ee_ladder_lenth ); //CRC����
	I2C_Write_Eeprom( ee_ladder1_page+Ch, 0, Buf, ee_ladder_lenth+2 );//��дһ��
}
