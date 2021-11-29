#include "ex_var.h"
#include "ex_func.h"
#include <string.h>
#include "FM32L0XX.h"  
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Cpu_card.h"

extern int __heap_limit;


#define	MAXREGION	14		//��ʱ�������ֵ, ����
#define	MAXSIDUANTB	8		//ʱ�α������ֵ, ����
#define	MAXSIDUAN	max_shiduancount//ʱ�������ֵ, ����
#define	MAXHOLIDAY	max_maxholiday	//�������������ֵ, ����
#define SCREENNUM	99		//���طѿر�

//��ַ��Χ:PROGRAMSTA1~PROGRAMEND1
#define PROGRAMSTA1	0x000000	//����ռ�1��ʼ��ַ
#ifdef __A03
#define PROGRAMEND1	0x02FFFF	//����ռ�1������ַ
#define PROGRAMPROZ	0x02F800	//���򱣻�����ʼ��ַ
#endif
#ifdef __A04
#define PROGRAMEND1	0x03FFFF	//����ռ�1������ַ
#define PROGRAMPROZ	0x03F800	//���򱣻�����ʼ��ַ
#endif
#ifdef __A05
#define PROGRAMEND1	0x05FFFF	//����ռ�1������ַ
#define PROGRAMPROZ	0x05F800	//���򱣻�����ʼ��ַ
#endif
#ifdef __A06
#define PROGRAMEND1	0x07FFFF	//����ռ�1������ַ
#define PROGRAMPROZ	0x07F800	//���򱣻�����ʼ��ַ
#endif

#define	KEYTYPE1	0x97
#define	KEYTYPE2	0x96

extern unsigned char UpdataRefer_ToEe_WithMac(void);
extern unsigned char ReadBinWithMac( uint08 CH, uint08 P1, uint08 P2, uint08 Len );
extern unsigned char Authorization( unsigned char *Buf, unsigned char Len );
extern unsigned char Auth_In_Out( unsigned char INS, unsigned char CH, unsigned char P2, unsigned char *BufA );
extern unsigned char CardTxRxFrame( unsigned char CH, uint08 Lc, uint08 Le );
extern void RxTxCommhead( uint08 inc, uint08 com, uint08 P1, uint08 P2, uint08 len);
extern uint16 CalcAbsDay(unsigned char * psTm);
extern uint16 CalcAbsMin(unsigned char * psTm);
extern unsigned char ChkPdRcdTime(void);
extern unsigned char FlashID_Comm( unsigned char *Buf );


#ifdef __DEBUG
void Send2Uart( unsigned char *Buf, unsigned int Len )
 {
 	unsigned int i;
 
 	R485CTRLS;
 	for( i=0; i<Len; i++ )
 	{
//		UART5->TXREG = Buf[i]; Clear_Wdt(); while( (UART_common->UARTIF&UART_TX_IF5) == 0 );
 		UART2->TXREG = Buf[i]; Clear_Wdt(); while( (UART_common->UARTIF&UART_TX_IF2) == 0 );
 	}
 	R485CTRLR;
 }
#endif

void LoopExchange( unsigned char *Drc, unsigned char *Src, unsigned char Times, unsigned char Spec )
{
	unsigned char i, k;
	
	for( i=0,k=0; i<Times; i++, k+=Spec ) Exchange( Drc+k, Src+k, Spec );
}

void LoopInverse( unsigned char *Inv, unsigned char Times, unsigned char Spec )
{
	unsigned char i;

	for( i=0; i<Times; i++ ) Inverse( Inv+i*Spec, Spec );
}

uint08 IsBCD( uint08 Value )
{
	if( ((Value&0xF0)<=0x90) && ((Value&0x0F)<=0x09) )
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

unsigned char IsMultiBcd( unsigned char *Buf, unsigned char Len )
//return: 0: BCD; 1: no BCD
{
	unsigned char i;
	
	for( i=0; i<Len; i++ )
	{
		if( IsBCD(Buf[i]) != 0x00 )		return 1;
	}
	
	return 0;
}


void Xor_Data( unsigned char *BufA, unsigned char *BufB, unsigned char Num )
{
	unsigned char i;

	for( i=0; i<Num; i++ )
	{
		BufA[i] ^= BufB[i];
	}
}


void Calculate_Program_Cs( unsigned char *Buf )//��������ۼӺ�	NNNNNNNN	4
{
	unsigned long int ecode *Code_Flash_Char;
	union B32_B08_2 Temp32;
		
	Temp32.B32 = 0;
	
	if( progenable )	//����ģʽ�Ż����
	{
		Clear_Wdt();
		for( Code_Flash_Char=(unsigned long int ecode *)PROGRAMSTA1; Code_Flash_Char<(unsigned long int ecode *)(PROGRAMEND1+1); Code_Flash_Char++ )	//4M��ִ��ʱ��Լ280ms
		{
			Temp32.B32 += *Code_Flash_Char;
		}
	}
	Inverse( Temp32.B08, 4 );
	Hex2Bcd( Temp32.B08, Buf, 4 );	//ת����bcd��,������ʾ
}


//Offset��0~3,�ֱ�Ϊ��բ��ʱ,�������բ��ʱ,������֤ʱ��,�ϱ��Զ���λʱ��
/*BCD��ķ��Ӷ�ʱ��ת����hex���붨ʱ����
offset��
		0��ͨѶ��բ��ʱ			2�ֽڣ�min
		1���������բ��ʱ		2�ֽڣ�min�������ޣ�
		2��������֤ʱ��			1�ֽڣ�min
		3���ϱ��Զ���λʱ��	1�ֽڣ�min
 0xff��Զ�������֤ʱЧ 2�ֽڣ�min
*/
unsigned long int Calculate_Timer(unsigned char Offset)
{
	unsigned char len;
	union B32_B08 Temp32;
	
	Temp32.B08[0] = 0;
	Temp32.B08[1] = 0;
	Temp32.B08[2] = 0;
	
	if( Offset == 0xff )
	{
		Bcd2Hex( Esam_Para.Identity_Delay.B08, Temp32.B08+2, 2 );	//���������֤ʱЧ
	}
	else
	{
		if( Offset < 2)
		{
			Offset = Offset*2;	//0,2
			len = 2;
		}
		else
		{
			Offset = Offset+2;	//4,5
			len = 1;
		}	
		Bcd2Hex( Mode.Exp_Timer+Offset, Temp32.B08+4-len, len );
	}
	
	return( Byte2uInt(Temp32.B08)*60 );//��ʱʱ�����ת������
}

	
void Clr_Commu_Relaydata()
{
	Opendelaytimer = 0;
	relay_commu_open_flag = 0;	//��ͨѶ��բ��־
	relay_commu_disable_close_flag = 0;
	relay_commu_close2_flag = 0;	//�屣������־
}


void Clr_Reportnum( unsigned char i ) //�����ϱ���������
{
	unsigned char Temp08;
	
	for( Temp08=0; Temp08<8; Temp08++ )//�����ϱ�״̬�������ϱ���������
	{
		if( (Report_Data[i]&(1<<Temp08))==0 ) Report_Num[i*8+Temp08] = 0;
	}
}

void Clr_Reportdata( unsigned char i ) //���ϱ�״̬�ֺ���������(���¼���¼��)
{
	unsigned char Temp08;
	
	Temp08 = EventTable[i-ee_clearn_inpage].offset2;
	if( Temp08 != 0xff )
	{	
		Report_Data[Temp08/8] &= ~(1<<(Temp08%8));	//���ϱ�״̬��
		Report_Num[Temp08] = 0;	//����������
	}
}

//��λ�ϱ�״̬�ֺ�����������1
void Set_Reportdata( unsigned char Offset ) 
{
	unsigned char byt,bt,i,j;
	
	if( Offset == 0xff ) return;
	
	byt = Offset/8;
	bt = Offset%8;
	
	//�����ϱ�ģʽ��
	if( (byt==2)&&(bt==7) )
	{
		i = 4; j = 5; //������ʱ���ô�A�����
	}
	else if( (byt==2)&&(bt==2) )
	{
		i = 3; j = 5; //�͵�ѹ��ʱ���ô�A��Ƿѹ
	}
	else if( (byt==2)&&(bt==1) )
	{
		i = 3; j = 4; //�ߵ�ѹ��ʱ���ô�A���ѹ
	}
	else
	{
		if( byt<3 )   i = byt;	//����ģʽ��
		else  i = byt+3;
		j = bt;
	}
	
	if( Mode.Report[i]&(1<<j) )	//�ж�ģʽ���Ƿ���λ
	{
		if( i == 4 && j == 5 )
		{
			if( below_60u_flag==0 ) //�����¼���ʼ(������below_60u_flag=1)
			{
				if( Meter_Run_Timer1 < Mode.Report_Timer ) return;//����ϵ�ʱ�䲻��1Сʱ,�����󲻽��е��緢���ϱ�
				
				ReportList[0] &= B1111_0000;
				ReportList[0] |= B0000_0011; //�ط�3�� ���緢��
				return;
			}
			else
			{
//				if( Meter_Run_Timer2 < Mode.Report_Timer ) return;//����ϵ�ʱ�䲻��1Сʱ,���ϵ�󲻽��е�������ϱ�
				
				ReportList[0] &= B1111_0000;
				ReportList[0] |= B0000_1100; //�ط�3�� �������
			}
				
		}
		else
		{
			ReportList[0] |= B0011_0000; //�ط�3�� �ϱ�״̬	
		}	
		
		Report_Data[byt] |= (1<<bt);	//��λ�ϱ�״̬��
		i = byt*8+bt;
		if( (i>=1)&&(i<=5)&&(i!=3) ) Report_Num[i] = 0xff;	//�޷����������ݱ�ʶ���¼���FF
		else if( Report_Num[i] < 0xff ) Report_Num[i]++;	//����������1
	}
}

//׼�������ϱ�״̬�ֺ���������
unsigned char Ready_Reportdata( unsigned char *Buf )
{
	unsigned char i,n;
	
//	Reset_Rep_Timer = Calculate_Timer(3);		//������λ�ϱ�״̬�ֶ�ʱ��
	memcpy( Report_Data2, Report_Data, 5 );		//�����ϱ�״̬��
	
	Buf[0] = 0x00;
	memcpy( Buf+1, Report_Data, 3 );
	memset( Buf+4, 0x00, 7 );
	Buf[11] = Report_Data[3];
	Buf[12] = Report_Data[4];
	Buf[13] = 0xAA;
	
	//����Ӧ����ϱ�״̬��
	if( Buf[3]&B1000_0000 ) {Buf[3]&=B0111_1111; Buf[9]|=B0010_0000;}//������ʱ���ô�A����� 
	if( Buf[3]&B0000_0100 ) {Buf[3]&=~B0000_0100; Buf[4]|=B0010_0000;}//�͵�ѹ��ʱ���ô�A��Ƿѹ 
	if( Buf[3]&B0000_0010 ) {Buf[3]&=~B0000_0010; Buf[4]|=B0001_0000;}//�ߵ�ѹ��ʱ���ô�A���ѹ 
		
	for( i=0,n=0; i<40; i++ )
	{
		Buf[14+n] = Report_Num[i];
		if( Report_Num[i] ) n++;
	}
	Buf[14+n] = 0xAA;
	return(15+n);
}


//�������������
void Clr_Zero_Data()
{
	already_setclock_flag = 0;//��㲥Уʱ��־
	hangup_comm_flag = 0;//������־
	Mac_Err_Times = 0;//mac�����������
	G_Clockerr_Times = 0;//�����Ĺ㲥Уʱ��¼���ϴ���
	Password_Err[0] = 0;//������������
	Password_Err[1] = 0;
}


//type=0�����ߵ�����ƽ�����ʱ��,type=1��������ʱ��
void Clr_Otherdata( unsigned char Type )
{
//	���ߵ�����ƽ�����ʱ��(4)+��������ʱ��(4)+���Ƿѹ���ۼ�ʱ��(4)+�������ۼ�ʱ��(4)+��ع���ʱ��(4)+ʧѹ����ʱ��(4)+�͵�ѹʱ��(4)+�ߵ�ѹʱ��(4) 
	if( Type >= ee_illegalcardnum_len/4 ) return;
	
	Save_Keep_Timer(0);
	
	Keeptime.Times[Type] = 0x00;
	memset(Eeprom.Buffer+Type*4, 0x00, 4);
	
	I2C_Write_Eeprom( ee_illegalcardnum_page, ee_illegalcardnum_inpage, Eeprom.Buffer, ee_illegalcardnum_len );
	memset( (uint08*)(&Keeptime.Times[0]), 0x00, ee_illegalcardnum_len );
}


unsigned char ClockAddOne( unsigned char *Clock, unsigned char Max, unsigned char Def )
{
	unsigned char Temp08;
	
	Temp08 = Bcd_To_Hex( *Clock ); //ʱ
	if( Temp08 < Max )
	{
		*Clock = Hex_To_Bcd( Temp08+1 ); //
		return 0;
	}
	else
	{
		*Clock = Def;
		return 1;
	}
}

unsigned char Add_Min_Clock( unsigned char *Clock, unsigned char Min )
//Clock: ssmmhhDDMMYY
{
	unsigned char Temp08, MaxDay;
	unsigned int  Year;
	unsigned char code Days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	Temp08 = Bcd_To_Hex(Clock[1]); //mm
	if( (Temp08+Min) < 60 )
	{
		Clock[1] = Hex_To_Bcd( Temp08+Min );
	}
	else
	{
		Clock[1] = Hex_To_Bcd( (Temp08+Min)-60 );
		Temp08 = ClockAddOne( Clock+2, 23, 0 );	//hour
		if( Temp08 )
		{
			Temp08 = Bcd_To_Hex(Clock[4]);
			MaxDay = Days[ Temp08-1 ];
			if( Temp08 == 2 )
			{
				Year = Bcd_To_Hex( Clock[5] );
				if( (Year&0x03) == 0 )	MaxDay++;	//����
			}

			Temp08 = ClockAddOne( Clock+3, MaxDay, 1 );	//day
			if( Temp08 )
			{
				Temp08 = ClockAddOne( Clock+4, 12, 1 );	//month
				if( Temp08 ) ClockAddOne( Clock+5, 99, 0 );	//year
			}
		}
	}
	
	return 0;
}

int16 Get_RTCTop_Proc( int16 Temp16 )	//�����Уֵ����
{
	int16 i;
	float Rtcadj;
		
	Rtcadj = Temp16 * 5.0 / 432.0 + Rtcadj_Offset2;	//�˴���λ��Ϊppm
	
	Rtcadj = Rtcadj * 100.0;
	
	if( Rtcadj >= 0 )
	{
		i = Rtcadj + 0.5;
	}
	else
	{
		i = Rtcadj - 0.5;
	}
	return i;
}


//�����ж�
unsigned char Veri_Psw( uint08 *Buf )
//Buf[0]:Ȩ��[1]~[3]:��������
//����ֵ: 0:��ȷ; 1/2:����
{
	unsigned char i, I2C_Buf[6];

	i = Buf[0];
	
	if( (i != 3) && (i != 4) ) return (1);
	
	i -= 3; //0,1
	
	if( Password_Err[i] >= Defpassworderrcnt ) return (1);
	
	ReadE2WithBackup( ee_password_page, ee_password_inpage+i*6, I2C_Buf, ee_password_lenth );

	if( Cmp_Bcd_Inv( I2C_Buf, Buf, 4 ) == 0 )	//0-A=B; 1:A>B; 2:A<B
	{
		Password_Err[i] = 0;
		return (0);
	}
	else
	{
		Password_Err[i]++;
		return (1);
	}
}


//��ͬ�Ķ����Ӧ�̶���ģʽ�֣�����ģʽ���ǿ����õģ��û��ڶ���ģʽ����δѡ����������ͣ�
//���೭��ʱӦ�����쳣Ӧ�𣬴�����Ϣ��Bit1 λ�á�1�������������󡱡�
//���ݿ鳭��������ʱ������������AAH �Թ���
unsigned short ReadFreezedRec( uint08 Type, uint08 Sn, uint08 No, uint08 *AckBuf )
//Type: ��¼����; No: �ϼ���; Sn:������
//return: 0:��ȡʧ��; 1:��ȡ�����ݳ���
{
	unsigned char n, ptrmax, style, fill=0xff;
	unsigned char ptr, mode;
	unsigned int  len;
	unsigned char i, Buf[ee_freezedl_lenth];
	unsigned short k; 
	unsigned char Obj, result;
	RecStore RtRec;
	RtFlash  RtAddr;
	
	AckBuf[0] = 0x00;

	switch( Type )
	{
		case 0x00:	//��ʱ����, 60��
			ptr = ee_timingf_inpage;
			mode = Week_Holiday.Freeze[1].B08[1];
			break;

		case 0x01:	//˲ʱ����, 3��
			ptr = ee_immedf_inpage;
			mode = Week_Holiday.Freeze[2].B08[1];
			break;
		
		case 0x02:	//Լ������, ʱ�����л�, 2��
			ptr = ee_agreesqf_inpage;
			mode = Week_Holiday.Freeze[3].B08[1];
			break;
		
		case 0x03:	//Լ������, ��ʱ�α��л�, 2��
			ptr = ee_agreesdf_inpage;
			mode = Week_Holiday.Freeze[3].B08[1];
			break;

		case 0x04:	//���㶳��: ����ʱ��+�����й��ܵ���+�����й��ܵ���, 254��, ���㶳��ʱ����Ĭ��Ϊ60���ӡ�
			ptr = ee_hourf_inpage;
			mode = Week_Holiday.Freeze[4].B08[1];
			break;
			
		case 0x06:	//�ն���, 254��
			ptr = ee_dayf_inpage;
			mode = Week_Holiday.Freeze[5].B08[1];
			break;
		
		case 0x07:	//Լ������, �����л�, 2��
			ptr = ee_agreejtf_inpage;
			mode = Week_Holiday.Freeze[3].B08[1];
			break;
			
		case 0x0A:	//Լ������, ����ʱ���л�, 2��
			ptr = ee_jtsqswith_inpage;
			mode = Week_Holiday.Freeze[3].B08[1];
			break;
			
		case 0x0C:	//�¶���, 24��
			ptr = ee_monthn_inpage;
			mode = Week_Holiday.Freeze[6].B08[1];
			break;
			
		default:
			return 0;
	}

	Obj = ptr;
	RtRec = GetRecNum( Obj, 0 ); //��¼�洢����׼��
	ptrmax = RtRec.ValPoint;

	if( (No==0) || (No > RtRec.Depth) ) return 0;	//��������
	
	if( Type == 0x04 ) //���㶳��
	{
		len = ee_hourfreezedl_lenth;
		style = 4;	//ƫ�Ƶ�ַ�ͳ���
	}
	else
	{
		len = ee_freezedl_lenth;
		style = max_dl_lenth;	//ƫ�Ƶ�ַ�ͳ���
	}
	
	if( ptrmax < No )	memset( Buf, 0x00, len );
	else 
	{	
		RtAddr = GetRecAddr( Obj, 0, No, &RtRec );
		if( IsFlashRec(Obj) )
		{
			result = Flash_Rd_Bottom( RtAddr.AppPage, RtAddr.AppPos, Buf, RtRec.TotLen ); //��Flash�ж�ȡ
		}
		else
		{
			result = I2C_Read_Bottom( RtAddr.DataPage+0, 0, Buf, 128 );	//����ʱ��+��������
			if( result == 0 )
			result = I2C_Read_Bottom( RtAddr.DataPage+1, 0, Buf+128, 128 );	//��������
			if( result == 0 )
			result = I2C_Read_Bottom( RtAddr.DataPage+2, 0, Buf+256, ee_freezedl_lenth-256 );	//��������
		}
		if( result ) return 0;
	}
		
	k = 0x01;
	switch( Sn )
	{
		case 0xFF:
		case 0x00: //����ʱ��:YYMMDDhhmm
			memcpy( AckBuf+k, Buf, 5 );
			k += 5;
			if( Sn == 0x00 ) break;
			AckBuf[k++] = 0xAA;
			
		default: 
			for( n=0; n<2; n++ )
			{
				if( (Sn == (n+1) || (Sn == 0xFF)) )	//�����й��ܵ���, �����й��ܵ���
				{
					if( mode & (n+1) )
					{
						for( i=0; i<(style/4); i++ ) 
						{
							Hex2Bcd_Dl( Buf+5+n*style+4*i, 1 );//������תBCD����
						}
						memcpy( AckBuf+k, Buf+5+n*style, style );
						if( style == 4 ) k += style;
						else k += (Bcd_To_Hex(Feik.Num[3])+1)*4;
					}

					if( Sn == (n+1) ) break;
					AckBuf[k++] = 0xAA;
				}
			}
			
			if( Type == 0x04 ) break;	//���㶳��
			
			for( n=2; n<8; n++ )
			{
				if( (Sn == (n+1) || (Sn == 0xFF)) )	//����޹�1~2��������, ��һ~�������޹���������
				{
					if( mode & (1<< ((n<4) ? n : 4 )) )
					{
						if( n == 2 || n == 3 )
						{
							//��������޹�
							for( i=0; i<(Bcd_To_Hex(Feik.Num[3])+1); i++ )
							{
								CalZhuhe( Buf+5+style*2+4*i, AckBuf+k, Buf[len-4+n], 0xff );//����޹�
								Hex2Bcd_Dl( AckBuf+k, 0 );//������תBCD����
								k += 4;
							}						
						}
						else
						{
							//�����������޹�
							for( i=0; i<(style/4); i++ ) 
							{
								Hex2Bcd_Dl( Buf+5+style*(2+n-4)+4*i, 1 );//������תBCD����
							}
							memcpy( AckBuf+k, Buf+5+style*(2+n-4), style );
							k += (Bcd_To_Hex(Feik.Num[3])+1)*4;
						}
					}

					if( Sn == (n+1) ) break;
					AckBuf[k++] = 0xAA;
				}
			}
			
			//�����й��������, �����й��������
			if( Sn == 0xFF )
			{
				memset( AckBuf+k, 0xAA, 2 );
				k += 2;
			}
			
			//��������: ���й�����
			if( (Sn == 0x10) || (Sn == 0xFF) )
			{
				if( mode & 0x80 )
				{
					memcpy( AckBuf+k+0, Buf+len-8, 3 );	//���й�����
					memcpy( AckBuf+k+3, Buf+len-8, 3 );	//A ���й�����
					if( ptrmax < No ) fill = 0x00;
					memset( AckBuf+k+6, fill, 6 );		//��������
					
					memcpy( AckBuf+k+12, Buf+len-5, 3 );	//���޹�����
					memcpy( AckBuf+k+15, Buf+len-5, 3 );	//A ���޹�����
					if( ptrmax < No ) fill = 0x00;
					memset( AckBuf+k+18, fill, 6 );		//��������
					
					k += 24;
				}

				if( Sn == 0x10 ) break;
				AckBuf[k++] = 0xAA;
			}
			break;
	}

	return (k-1);
}


//ͨѶ����߾���,�����ʽ����̶�Ϊ����(4)+����4(4)+����޹�1(4)+����޹�2(4)
void Comm_Calculate_Comp_Rp( unsigned char *Inbuf, unsigned char num, unsigned char mode )//ͨѶ���������������
{		
	uint08 i,Buf[70];
	union B32_B08_2 Temp32;
	union B64_B08_2 Temp64;
	
	if( num%4 ) return;
	
	memcpy( Buf, Inbuf, 70 );  
	
	for(i=0; i<num; i++)
	{
		if( ((i%4) == 2) || ((i%4) == 3) ) //����޹�1+����޹�2
		{
			uint08 Temp08;
			
			Temp08=0;
			memcpy( Temp32.B08, Buf+4*i, 4 );  //����4�ֽ�������
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
			if( Temp08 ) Temp64.B08[4] |= 0x80;	//��ϵ���<0�����λ��1
		}
		else
		{
			memcpy( Temp32.B08, Buf+4*i, 4 );  //����4�ֽ�������
			Temp64.B64 = (signed long long)Temp32.B32*100/Meter.Const_H;
			Hex2Bcd_SS( Temp64.B08, Temp64.B08, 8 );
		}
		
		if( (mode&0x80)==0 ) memcpy( Inbuf+4*i, Temp64.B08+1, 4 );	//��ͨ����(3+1)
		else memcpy( Inbuf+5*i,  Temp64.B08, 5 );	//�߾���(3+2)
	}
}

//hex������ת����bcd�ĵ���,��ͨ����4�ֽڱ��4�ֽ�,�߾���4�ֽڱ��5�ֽ�
void Comm_Calculate_Dl( unsigned char *Inbuf, unsigned char num, unsigned char mode )//ͨѶ���������������
{		
	uint08 i,Buf[70];
	union B32_B08_2 Temp32;
	union B64_B08_2 Temp64;
	
	memcpy( Buf, Inbuf, 70 );  
	
	for(i=0; i<num; i++)
	{
		memcpy( Temp32.B08, Buf+4*i, 4 );  //����4�ֽ�������
		Temp64.B64 = (signed long long)Temp32.B32*100/Meter.Const_H;
		Hex2Bcd_SS( Temp64.B08, Temp64.B08, 8 );
		
		if( (mode&0x80)==0 ) memcpy( Inbuf+4*i, Temp64.B08+1, 4 );	//��ͨ����(3+1)
		else memcpy( Inbuf+5*i,  Temp64.B08, 5 );	//�߾���(3+2)
	}
}


void Calculate_Ah( unsigned char *Inbuf )//���㰲ʱ��
{	
	union B32_B08_2 Temp32;
						
	Temp32.B32 = Lost_Aver_I*(Lost_V_Timer/60.0)/10;
	Hex2Bcd_SS( Temp32.B08, Temp32.B08, 4 );
	memcpy( Inbuf, Temp32.B08, 4 );	//���㰲ʱ��
}

unsigned char BitValue( unsigned char *InBuf, unsigned char Pos )
{
	return ( (InBuf[Pos/8]>>(Pos%8))&1 );
}

uint08 Find_EventTable( unsigned char *DI );

uint16 Rd_Relay_Buy_Rec( unsigned char *DI, unsigned char *AckBuf )
{
	unsigned char i, n, result, inpage, offset=0x00, ptr, len=0, total_len, rec_len, ptrmax, Temp08;
	unsigned short k=0;
	unsigned int  page;
	union B16_B08 Temp16;
	unsigned char Buf[128];

	unsigned char code Tab_Reley[]={6,4,4,4,4,4,4,4};
	unsigned char code Tab_Maxi[]= {6,4,4,4,4,4,4,4,4,2,3,3,3,2,4,4,4,4,2,3,3,3,2,4,4,4,4,2,3,3,3,2,6,4,4,4,4,4,4,4,4};
	unsigned char code Tab_PwrDn[]={6,4,4,4,4,4,4,4,4, 4,4,4,4,4,4,4,4,6,4,4,4,4,4,4,4,4};
	
	const uint08 code MaxiOffset1[8] = { 0,  6, 22, 38, 49, 109, 109+6, 109+22 };
	const uint08 code MaxiOffset2[8] = { 0, 12, 12, 28, 39, 6, 41, 41 };
//	const uint08 code MaxiLenth  [8] = { 6, 16,  0, 11,  2, 6, 16,  0 };
	const uint08 code MaxiLenth  [8] = { 6, 16, 16, 11,  2, 6, 16, 16 };	//ͬʱ֧��A��
	
	unsigned char code PwrDnOffset1[6] = { 0, 6,22,70,70+6,70+22 };
	unsigned char code PwrDnOffset2[6] = { 0,12,12, 6, 28, 28 };
//	unsigned char code PwrDnLen[6]     = { 6, 16, 0, 6, 16,  0 };
	unsigned char code PwrDnLen[6]     = { 6, 16, 16, 6, 16, 16 };	//ͬʱ֧��A��
	
//	unsigned char code MaxiSup [7] = { B0001_1111, B0011_1110, B0000_0000, B0000_0000, B0001_1111, B0000_0000, B0000_0000 };
//	unsigned char code PwrDnSup[5] = { B0001_1111, B0000_0000, B0011_1110, B0000_0000, B0000_0000 };
	unsigned char code MaxiSup [7] = { B1111_1111, B0011_1111, B0000_0000, B0000_0000, B1111_1111, B0000_0001, B0000_0000 }; //ͬʱ֧��A��
	unsigned char code PwrDnSup[5] = { B1111_1111, B0000_0001, B1111_1110, B0000_0011, B0000_0000 }; //ͬʱ֧��A��
	
	//����ʧѹ
	unsigned char code Tab_Lostv[]= {6,4,4,4,4,4,4,4,4,2,3,3,3,2,4,4,4,4,2,3,3,3,2,4,4,4,4,2,3,3,3,2,4,4,4,4,6,4,4,4,4,4,4,4,4};
	const uint08 code LostvOffset1[8] = { 0,  6, 22, 38, 125-16, 125, 125+6, 125+22 };
	const uint08 code LostvOffset2[8] = { 0, 12, 12, 28, 57, 6, 41, 41 };
	const uint08 code LostvLenth  [8] = { 6, 16, 16, 13, 8, 6, 16, 16 };	//ͬʱ֧��A��
	unsigned char code LostvSup [7] = { B1111_1111, B0011_1111, B0000_0000, B0000_0000, B1111_0011, B0001_1111, B0000_0000 }; //ͬʱ֧��A��	
	//�߾���(0x83����)
	//����ʧѹ
	unsigned char code Tab_Lostv_G[]= {6,5,5,5,5,5,5,5,5,2,3,3,3,2,5,5,5,5,2,3,3,3,2,5,5,5,5,2,3,3,3,2,4,4,4,4,6,5,5,5,5,5,5,5,5};
	const uint08 code LostvOffset1_G[8] = { 0,  6, 26, 46, 141-16, 141, 141+6, 141+26 };
	const uint08 code LostvOffset2_G[8] = { 0, 12, 12, 32, 65, 6, 45, 45 };
	const uint08 code LostvLenth_G  [8] = { 6, 20, 20, 13, 8, 6, 20, 20 };	//ͬʱ֧��A��
	
	unsigned char code Tab_Maxi_G[]= {6,5,5,5,5,5,5,5,5,2,3,3,3,2,5,5,5,5,2,3,3,3,2,5,5,5,5,2,3,3,3,2,6,5,5,5,5,5,5,5,5};
	const uint08 code MaxiOffset1_G[8] = { 0,  6, 26, 46, 57, 125, 125+6, 125+26 };
	const uint08 code MaxiOffset2_G[8] = { 0, 12, 12, 32, 43, 6, 45, 45 };
	const uint08 code MaxiLenth_G  [8] = { 6, 20, 20, 11,  2, 6, 20, 20 };	//ͬʱ֧��A��
	
	unsigned char code Tab_PwrDn_G[]={6,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6,5,5,5,5,5,5,5,5};
	unsigned char code PwrDnOffset1_G[6] = { 0, 6,26,86,86+6,86+26 };
	unsigned char code PwrDnOffset2_G[6] = { 0,12,12, 6, 32, 32 };
	unsigned char code PwrDnLen_G[6]     = { 6, 20, 20, 6, 20,  20 }; //ͬʱ֧��A��
	
	unsigned char code Tab_Reley_G[]={6,4,5,5,5,5,5,5};
	

	AckBuf[0] = 0x00;	//ȱʡ�������ݳ�����0x00

	if( (DI[1] == 0xFF) && (DI[0] == 0xFF) ) return 0;

	Buf[2] = DI[2];
	Buf[3] = DI[3]&0x7f;
	i = Find_EventTable(Buf+2);		//�ж��Ƿ��ҵ��Ϸ����ݱ�ʶ
	if( i == EventNum )	return 0;

	page = EventTable[i].page;
	inpage = EventTable[i].offset;
	rec_len = EventTable[i].len;
	ptr = i+ee_clearn_inpage;
	
	switch( ptr )
	{
		case ee_powerdownn_inpage: //�����¼
			if( DI[3]&0x80 ) //�߾���
			{
				total_len = 140+32;
				len = 140+32;
			}
			else
			{
				total_len = 140;
				len = 140;
			}

			if( DI[1] != 0xFF )
			{
				if( DI[1] == 0 )
				{
					if( DI[0] == 0x0c )//���������ۼ�ʱ��
					{
						Get_Keep_Timer(3, AckBuf+1);
						AckBuf[0] = 3;
						return AckBuf[0];
					}
				}
				else
				{
					if( (DI[1] > 0x22) || (BitValue(PwrDnSup, DI[1]-1) == 0) ) return 0;
					
					if( DI[3]&0x80 ) //�߾���
					{
						len = Tab_PwrDn_G[DI[1]-1];
						offset += Cal_ChkSum( Tab_PwrDn_G, (DI[1]-1) );
					}
					else
					{
						len = Tab_PwrDn[DI[1]-1];
						offset += Cal_ChkSum( Tab_PwrDn, (DI[1]-1) );
					}
				}
			}
			break;
			
		case ee_lostvn_inpage:	//ʧѹ
			if( DI[3]&0x80 ) //�߾���
			{
				total_len = 179+16+32;
				len = 179+16+32;
			}
			else
			{
				total_len = 179+16;
				len = 179+16;
			}			
			
			if( DI[1] != 0xFF )
			{
				if( DI[1] == 0 )
				{
					if( DI[0] == 2 )//��ʧѹ�ۼ�ʱ��
					{
						Get_Keep_Timer(5, AckBuf+1);
						AckBuf[0] = 3;
						return AckBuf[0];
					}
				}
				else
				{
					if( (DI[1] > 0x35) || (BitValue(LostvSup, DI[1]-1) == 0) ) return 0;
					
					if( DI[3]&0x80 ) //�߾���
					{
						len = Tab_Lostv_G[DI[1]-1];
						offset += Cal_ChkSum( Tab_Lostv_G, (DI[1]-1) );
					}
					else
					{
						len = Tab_Lostv[DI[1]-1];
						offset += Cal_ChkSum( Tab_Lostv, (DI[1]-1) );
					}
				}
			}
			break;
		
		case ee_maxi_inpage:	//����	
			if( DI[3]&0x80 ) //�߾���
			{
				total_len = 179+32;
				len = 179+32;
			}
			else
			{
				total_len = 179;
				len = 179;
			}			
			
			if( DI[1] != 0xFF )
			{
				if( DI[1] == 0 )
				{
					if( DI[0] == 2 )//�������ۼ�ʱ��
					{
						Get_Keep_Timer(1, AckBuf+1);
						AckBuf[0] = 3;
						return AckBuf[0];
					}
				}
				else
				{
					if( (DI[1] > 0x31) || (BitValue(MaxiSup, DI[1]-1) == 0) ) return 0;
					
					if( DI[3]&0x80 ) //�߾���
					{
						len = Tab_Maxi_G[DI[1]-1];
						offset += Cal_ChkSum( Tab_Maxi_G, (DI[1]-1) );
					}
					else
					{
						len = Tab_Maxi[DI[1]-1];
						offset += Cal_ChkSum( Tab_Maxi, (DI[1]-1) );
					}
				}
			}
			break;

		case ee_batterlow_inpage:	//���Ƿѹ��¼
			if( DI[1] == 0 )
			{
				if( DI[0] == 0 ) //���Ƿѹ���ۼ�ʱ��
				{
					Get_Keep_Timer(2, AckBuf+1);
					AckBuf[0] = 3;
					return AckBuf[0];
				}
				else if( DI[0] <= 0x0A ) //���Ƿѹ��¼
				{
					if( DI[3]&0x80 ) //�߾���
					{
						total_len = 70+16;
						len = 70+16;
					}
					else
					{
						total_len = 70;
						len = 70;
					}
				}
			}
			break;

		case ee_openrelayn_inpage:	//��բ����
		case ee_closerelayn_inpage:	//��բ����
			if( DI[3]&0x80 ) //�߾���
			{
				total_len = 34+6;
				len = 34+6;
			}
			else
			{
				total_len = 34;
				len = 34;
			}

			if( DI[1] != 0xFF )
			{
				if( DI[1] > 8 ) return 0;

				if( DI[1] )
				{
					if( DI[3]&0x80 ) //�߾���
					{
						len = Tab_Reley_G[DI[1]-1];
						offset += Cal_ChkSum( Tab_Reley_G, (DI[1]-1) );
					}
					else
					{
						len = Tab_Reley[DI[1]-1];
						offset += Cal_ChkSum( Tab_Reley, (DI[1]-1) );
					}
				}
			}
			break;

		default:
			return 0;
	}

	if( len == 0 ) return 0;

	if( (ptr != ee_batterlow_inpage) && (DI[1] == 0) )
	{
		if( ((ptr == ee_powerdownn_inpage) && (DI[0] == 0)) || //�����¼
			((ptr != ee_powerdownn_inpage) && (DI[0] == 1)))	 //������¼
		{
			Read_Event_Number( AckBuf+1, ptr );
			AckBuf[0] = 3;
		}

		return AckBuf[0];
	}
					
	if( (DI[0]) && (DI[0]<=max_eventrecord_p) )	//��1~10��
	{
		Temp16.B08[0] = DI[0]-1;
		Temp16.B08[1] = DI[0];
	}
	else if( DI[0] == 0xFF )
	{
		Temp16.B08[0] = 0;
		Temp16.B08[1] = max_eventrecord_p;
	}
	else
	{
		return 0;
	}

	ptrmax = RdRecTimes(ptr);//������Чָ��
	Temp08 = Read_Event_Point( ptr );
	
	k = 0x01;
	for( n=Temp16.B08[0]; n<Temp16.B08[1]; n++ )
	{
		result = Temp08;
		if( result < n ) result += max_eventrecord_p;
		result -= n;

		if( ptrmax < n+1 ) memset( Ic_Comm_TxBuf, 0x00, total_len );
		else
		{
			memset( Ic_Comm_TxBuf, 0xFF, total_len );
			I2C_Read_Eeprom( page+result, inpage, Buf, rec_len );//���洢������ee�����Ч����
			if( ptr == ee_lostvn_inpage || ptr == ee_maxi_inpage )	//ʧѹ/������������֡����
			{
				if( ptr == ee_lostvn_inpage && lost_v_flag && (n==0) )//��һ��ʧѹ��¼(��ʱ�������ۼ���)
				{
					Calculate_Ah( Buf+57 );//���㰲ʱ��
				}
				memcpy( Buf+100, Buf+12+16, 13 ); //���淢��ʱ�̵�ѹ�������ʼ�����(13)
				memcpy( Buf+12+16, Buf+12+16+13, 16 );//ǰ�ƽ����������й�(8)+����޹�(8)
				Comm_Calculate_Comp_Rp( Buf+12, 8, DI[3] );
				if( DI[3]&0x80 ) //�߾���
				{	//�߾������ݸ�:��������ʱ��(6)+����ʱ��(6)+����ʱ�������й�(10)+����޹�(10)+����ʱ�̵�ѹ�������ʼ�����(13)+�����������й�(10)+����޹�(10)		
					if( ptr == ee_lostvn_inpage )
					{
						memcpy( Buf+65, Buf+57, 4 ); //�����ܰ�ʱ��
						memcpy( Buf+69, Buf+57, 4 ); //����A�లʱ��
					}
					memcpy( Buf+80, Buf+12+20, 20 ); //��������������й�(10)+����޹�(10)
					memcpy( Buf+12+20, Buf+100, 13 ); //�ָ�����ʱ�̵�ѹ�������ʼ�����(13)
					memcpy( Buf+12+20+13, Buf+80, 20 ); //�ָ������������й�(10)+����޹�(10)
					if( ptr == ee_lostvn_inpage )
					for( i=0; i<8; i++ ) memcpy( Ic_Comm_TxBuf+LostvOffset1_G[i], Buf+LostvOffset2_G[i], LostvLenth_G[i] );//����ʱ��
					else
					for( i=0; i<8; i++ ) memcpy( Ic_Comm_TxBuf+MaxiOffset1_G[i], Buf+MaxiOffset2_G[i], MaxiLenth_G[i] );//����ʱ��
				}
				else //��ͨ����
				{
					if( ptr == ee_lostvn_inpage )
					{
//						memcpy( Buf+57, Buf+57, 4 ); //�����ܰ�ʱ��
						memcpy( Buf+61, Buf+57, 4 ); //����A�లʱ��
					}
					memcpy( Buf+80, Buf+12+16, 16 ); //��������������й�(8)+����޹�(8)
					memcpy( Buf+12+16, Buf+100, 13 ); //�ָ�����ʱ�̵�ѹ�������ʼ�����(13)
					memcpy( Buf+12+16+13, Buf+80, 16 ); //�ָ������������й�(10)+����޹�(10)
					if( ptr == ee_lostvn_inpage )
					for( i=0; i<8; i++ ) memcpy( Ic_Comm_TxBuf+LostvOffset1[i], Buf+LostvOffset2[i], LostvLenth[i] );//����ʱ��
					else
					for( i=0; i<8; i++ ) memcpy( Ic_Comm_TxBuf+MaxiOffset1[i], Buf+MaxiOffset2[i], MaxiLenth[i] );//����ʱ��
				}
			}
			else if( ptr == ee_powerdownn_inpage )	//������������֡����
			{
				Comm_Calculate_Comp_Rp( Buf+12, 8, DI[3] ); 
				if( DI[3]&0x80 ) //�߾���
				{	//�߾������ݸ�:���緢��ʱ��(6)+����ʱ��(6)+����ʱ�������й�(10)+����޹�(10)+�����������й�(10)+����޹�(10)		
					for( i=0; i<6; i++ ) memcpy( Ic_Comm_TxBuf+PwrDnOffset1_G[i], Buf+PwrDnOffset2_G[i], PwrDnLen_G[i] );//����ʱ��
				}
				else //��ͨ����
				{
					for( i=0; i<6; i++ ) memcpy( Ic_Comm_TxBuf+PwrDnOffset1[i], Buf+PwrDnOffset2[i], PwrDnLen[i] );//����ʱ��
				}
			}
			else if( ptr == ee_batterlow_inpage )	//���Ƿѹ
			{
				Comm_Calculate_Comp_Rp( Buf+6, 4, DI[3] );
				if( DI[3]&0x80 ) //�߾���
				{
					memcpy( Ic_Comm_TxBuf+ 0, Buf+0, 6+10+10 );//����ʱ��+���������+����޹�1��2
					memcpy( Ic_Comm_TxBuf+26, Buf+6, 10+10 );//���������+����޹�1��2(A��) ͬʱ֧��A��
				}
				else //��ͨ����
				{
					memcpy( Ic_Comm_TxBuf+ 0, Buf+0, 6+8+8 );//����ʱ��+���������+����޹�1��2
					memcpy( Ic_Comm_TxBuf+22, Buf+6,  8+8 );//���������+����޹�1��2(A��)	ͬʱ֧��A��
				}
			}
			else //����բ
			{
				Comm_Calculate_Dl( Buf+10, 6, DI[3] );
				if( DI[3]&0x80 ) //�߾���
				{
					memcpy( Ic_Comm_TxBuf, Buf, 6+4+10+20 );//����ʱ��+���������+�������޹�
				}
				else //��ͨ����
				{
					memcpy( Ic_Comm_TxBuf, Buf, rec_len );
				}
			}
		}
		
		memcpy( AckBuf+k, Ic_Comm_TxBuf+offset, len );
		k += len;
	}
	
	return k-1;
}

uint08 Find_EventTable( unsigned char *DI )
{
	unsigned char  i;
	union B16_B08_2 Temp16;
	
	Temp16.B08[0] = DI[0];
	Temp16.B08[1] = DI[1];
	
	for( i=0; i<EventNum; i++ )
	{
		if( Temp16.B16 == EventTable[i].DI21 )	break;
	}

	if( i >= EventNum ) return EventNum;
	
	return i;
}

uint16 RdHisEvent( unsigned char *DI, unsigned char SN, uint08 *AckBuf )
//return 0: success; other: failure.
{
	unsigned char i, n, TmpPtr, ptrmax, MaxEvent = max_eventrecord_p;
	unsigned short k=0;
	unsigned char offset, ptr, ptr2, len, result;
	unsigned int  page, TmpP1, TmpP2;
	unsigned char Buf[64], TmpBuf[5], ReadPtr[16];
	union B32_B08 Temp32;

	AckBuf[0] = 0x00;

	i = Find_EventTable(DI+1);		//�ж��Ƿ��ҵ��Ϸ����ݱ�ʶ
	if( i == EventNum )	return 0;
	if( i == ee_powerdownn_inpage-ee_clearn_inpage ) return 0;	//�Ƿ����ݱ�ʶ
	if( i == ee_poweroffn_inpage-ee_clearn_inpage || i==ee_poweronn_inpage-ee_clearn_inpage ) //�����ϱ��¼����ϵ��ϱ��¼�������¼�ͬԴ
	{
		ptr2 = i+ee_clearn_inpage; //��ʱ��������ϱ��¼����ϵ��ϱ��¼�
		i = ee_powerdownn_inpage-ee_clearn_inpage;
	}

	page = EventTable[i].page;
	offset = EventTable[i].offset;
	len = EventTable[i].len;
	ptr = i+ee_clearn_inpage;

	if(	ptr == ee_lostvn_inpage		||
		ptr == ee_maxi_inpage		||
		ptr == ee_openrelayn_inpage ||
		ptr == ee_closerelayn_inpage||
		ptr == ee_batterlow_inpage	) return 0;	//�Ƿ����ݱ�ʶ
		
//	if( (DI[3]&0x80) && 	//��֧�ֵĸ߾���ֱ�ӷ��ش���
//		(ptr == ee_dayvolpassn_inpage || ptr == ee_monvolpassn_inpage || ptr == ee_monpowerdownn_inpage || ptr == ee_yearpowerdownn_inpage) ) 
//						return 0;	//�Ƿ����ݱ�ʶ
	
	if( len > 0x00 )
	{	
		if( DI[0] == 0x00 )	//�ܴ���
		{
			Read_Event_Number( AckBuf+1, ptr );
			k = 3;
			
			if( (ptr == ee_powerdownn_inpage) && (ptr2 == ee_poweronn_inpage) ) //�����ϱ��¼����ϵ��ϱ��¼�������¼�ͬԴ
			{
				if( ChkPdRcdTime() == 0 ) //�������ʱ��Ϊ0(���µ��ϵ��ϱ�)
				{
					uint32 Number=0;
					
					memcpy( (uint08*)&Number, AckBuf+1, 3 );
					if( Number ) Number--;	//�ϵ��ϱ��¼���1
					memcpy( AckBuf+1, (uint08*)&Number, 3 );
				}
			}
			
			if( ptr == ee_lowervn_inpage )//�͵�ѹ�¼�
			{
				Get_Keep_Timer(6, AckBuf+1+3);
				k = 6;
			}	
			else if( ptr == ee_highvn_inpage )//�ߵ�ѹ�¼�
			{
				Get_Keep_Timer(7, AckBuf+1+3);
				k = 6;
			}
		}
		else	//�¼���¼
		{
//			if( ptr == ee_keysetn_inpage ) MaxEvent = 2;	//��Կ���¼�¼ֻ��2��
//			if( ptr == ee_shiqun_inpage ) MaxEvent = 2;	//ʱ����̼�¼ֻ��2��
//			if( ptr == ee_shiduann_inpage ) MaxEvent = 2;	//ʱ�α�̼�¼ֻ��2��
//			if( ptr == ee_weekdayn_inpage ) MaxEvent = 2;	//�����ձ�̼�¼ֻ��2��
//			if( ptr == ee_jtpricen_inpage ) MaxEvent = 2;	//���ݱ��̼�¼ֻ��2��
//			if( ptr == ee_gbsclockn_inpage ) MaxEvent = max_gbsetclock_p;	//�㲥Уʱ
//			if( ptr == ee_dayvolpassn_inpage ) MaxEvent = max_dayvolpass_p;	//�յ�ѹ�ϸ���
//			if( ptr == ee_monvolpassn_inpage ) MaxEvent = max_monvolpass_p;	//�µ�ѹ�ϸ���
			MaxEvent = MaxRecNum[ptr];
			if( DI[0] > MaxEvent ) return 0;	//��������
			
			ptrmax = RdRecTimes(ptr);//������Чָ��
			result = Read_Event_Point( ptr );
			
			TmpPtr = result;	//������һ���¼���¼ָ��
			
			if( result < (DI[0]-1) ) result += MaxEvent;			
			result -= (DI[0]-1);
			
			if( (ptr == ee_powerdownn_inpage) && (ptr2 == ee_poweronn_inpage) ) //�����ϱ��¼����ϵ��ϱ��¼�������¼�ͬԴ
			{
				if( ChkPdRcdTime() == 0 ) //�������ʱ��Ϊ0(���µ��ϵ��ϱ�)
				{
					if( result < 1 ) result += MaxEvent;	//������һ��
					result -= 1;
					if( ptrmax ) ptrmax--;	//��Чָ���1
				}
			}
			
			if( ptr == ee_gbsclockn_inpage )//�㲥Уʱ
				I2C_Read_Eeprom( page+result/3, offset+(result%3)*len, Buf, len );
			else if( ptr == ee_dayvolpassn_inpage || ptr == ee_monvolpassn_inpage )//�յ�ѹ�ϸ���/�µ�ѹ�ϸ���
				I2C_Read_Eeprom( page+result/4, offset+(result%4)*len, Buf, len );	
			else
				I2C_Read_Eeprom( page+result, offset, Buf, len );
			
//			if( ptr == ee_lowervn_inpage && lower_v_event_flag && DI[0]==1 )//�͵�ѹ�¼������ۼ���
//			{
//				Get_Keep_Timer(6, Buf+len-4);	//���͵�ѹ�ۼ�ʱ��:����4�ֽ�ʱ��(Buf[len-4]~Buf[len-1])
//			}	
//			else if( ptr == ee_highvn_inpage && high_v_event_flag && DI[0]==1 )//�ߵ�ѹ�¼������ۼ���
//			{
//				Get_Keep_Timer(7, Buf+len-4);	//���ߵ�ѹ�ۼ�ʱ��:����4�ֽ�ʱ��(Buf[len-4]~Buf[len-1])
//			}
			
			memcpy( AckBuf+1, Buf, len );		

			switch( DI[1]+(DI[2]<<8) )
			{
				case 0x3001:	//�������
					k = 106;	//���÷������ݵĳ���
					memset( AckBuf+1+18+16, 0xFF, 88-16 );
					break;
				
				case 0x3005:	//ʱ�α���
				case 0x3006:	//ʱ������
					//��(Buf�еڼ������ֽڵ�ֵ)Ϊ"ָ����ָ���ReadPtr�Ķ�Ӧ�ֽ�"��д�뼸��
					I2C_Read_Eeprom( page+TmpPtr, 70, TmpBuf, 5 );	//��ȡ��1����ʱ�α��̼�¼ҳ����ʷ��¼
					
					memset( ReadPtr, 0xFF, 16 );
	
					for( n=0; n<DI[0]; n++ )
					{
						if( TmpPtr%2 )	ReadPtr[ (TmpBuf[TmpPtr/2]&0xF0)>>4 ] = TmpPtr;
						else			ReadPtr[ (TmpBuf[TmpPtr/2]&0x0F)    ] = TmpPtr;
	
						if( TmpPtr ) TmpPtr--;
						else	TmpPtr = MaxEvent-1;
					}

					if( DI[1] == 0x05 )
					{
						TmpP1 = ee_shiduantable1_1_page;
						TmpP2 = ee_shiduanrecord_page;
						Temp32.B08[2] = 15;	//����ҳ
					}
					else
					{
						TmpP1 = ee_shiqu1_page;
						TmpP2 = ee_shiqurecord_page;
						Temp32.B08[2] = 1;	//����ҳ
					}
					
					memcpy( AckBuf+1, Buf+5, 10 );	//����ʱ��+�����ߴ���
					k = 10;	//���ػ�������ַָ��

					for( n=0; n<=Temp32.B08[2]; n++, k+=len )
					{
						if( ReadPtr[n] == 0xFF )
						{
							page = TmpP1+n;
							offset = 0;
						}
						else
						{
							page = TmpP2+ReadPtr[n];
							offset = 70+15;
						}

						len = 42;	//Ĭ�϶�ȡ�ĳ���
						I2C_Read_Eeprom( page, offset, AckBuf+1+k, len );	//��ǰʱ�α�
					}
					break;
					
				case 0x3010:	//���ݱ��
					k = 10;	//���ػ�������ַָ��
						
					for( n=0; n<8; n++ )
					{
						if( n < 2 )
							I2C_Read_Eeprom( ee_jtpricerecord2_page+result*4+n, 0, AckBuf+1+k, ee_jtpricerecord2_len );
						else if( n == 4 || n == 5 ) 
							I2C_Read_Eeprom( ee_jtpricerecord2_page+result*4+n-2, 0, AckBuf+1+k, ee_jtpricerecord2_len );
						else
							memset( AckBuf+1+k, 0xff, ee_jtpricerecord2_len );
						k += ee_jtpricerecord2_len;
					}
					break;
					
				default:
					k = len;	//���÷������ݵĳ���
					break;
			}
			
			//hex������ת����bcd�ĵ���,��ͨ����4�ֽڱ��4�ֽ�,�߾���4�ֽڱ��5�ֽ�
			if( ptr == ee_gbsclockn_inpage ) //�㲥Уʱ��¼ 8+16
			{
				Comm_Calculate_Dl( AckBuf+1+12, 6, DI[3] );
				if( DI[3]==0x83 ) k += 6;
			}
			else if( ptr == ee_clearn_inpage ) //������� 8+16
			{
				Comm_Calculate_Dl( AckBuf+1+10, 6, DI[3] );
				if( DI[3]==0x83 ) {k = 130; memset( AckBuf+1+40, 0xFF, 90 );}
			}
			else if( ptr == ee_covern_inpage || ptr == ee_clockerrn_inpage || ptr == ee_nlineerrn_inpage ) //�����/ʱ�ӹ���/���ߵ����쳣 8+16+8+16
			{
				Comm_Calculate_Dl( AckBuf+1+12, 12, DI[3] );
				if( DI[3]==0x83 ) k += 12;
			}
			else if( ptr == ee_setclockn_inpage ) //����ʱ�� 8+16
			{
				Comm_Calculate_Dl( AckBuf+1+16, 6, DI[3] );
				if( DI[3]==0x83 ) k += 6;
			}
			else if( ptr == ee_commerrn_inpage) //ͨ��ģ���쳣 8+8
			{
				Comm_Calculate_Dl( AckBuf+1+18, 4, DI[3] );
				if( DI[3]==0x83 ) k += 4;
			}
			else if( ptr == ee_relayerrn_inpage ) //���ɿ������� 8+8
			{
				Comm_Calculate_Dl( AckBuf+1+13, 4, DI[3] );
				if( DI[3]==0x83 ) k += 4;
			}
			else if( ptr == ee_batchangen_inpage || ptr == ee_calerrn_inpage || ptr == ee_commchangen_inpage ) //ʱ�ӵ�ظ���/��������/ͨ��ģ���� 8+8
			{
				Comm_Calculate_Dl( AckBuf+1+12, 4, DI[3] );
				if( DI[3]==0x83 ) k += 4;
			}
			else if( ptr == ee_batterlow_inpage ) //���Ƿѹ 8+8
			{
				Comm_Calculate_Dl( AckBuf+1+6, 4, DI[3] );
				if( DI[3]==0x83 ) k += 4;
			}
			else if( ptr == ee_powererrn_inpage ) //��Դ�쳣 8
			{
				Comm_Calculate_Dl( AckBuf+1+12, 2, DI[3] );
				if( DI[3]==0x83 ) k += 2;
			}
			else if( ptr == ee_powerdownn_inpage ) //�����ϱ��¼����ϵ��ϱ��¼�������¼�ͬԴ
			{
				if( ptr2 == ee_poweroffn_inpage  ) //�����ϱ� 8+8
				{
					k = ee_poweroffnote_lenth;
					memcpy(AckBuf+1+6, AckBuf+1+12, 16 );//����ʱ�̵���
					Comm_Calculate_Comp_Rp( AckBuf+1+6, 4, DI[3] );
					if( DI[3]==0x83 )
					{
						memcpy( AckBuf+1+6+20, AckBuf+1+44, 3 );//����ʱ��ǰ3���ӵ�ƽ������
						k += 4;
						memset( AckBuf+1+6+20+3, 0xff, 6 ); //����ʱ��ǰ3���ӵ�ƽ������(B/C��)
						k += 6;
					}
					else
					{	
						memcpy( AckBuf+1+6+16, AckBuf+1+44, 3 );//����ʱ��ǰ3���ӵ�ƽ������
						memset( AckBuf+1+6+16+3, 0xff, 6 ); //����ʱ��ǰ3���ӵ�ƽ������(B/C��)
						k += 6;
					}
				}
				else if( ptr2 == ee_poweronn_inpage) //�ϵ��ϱ� 8+8
				{
					k = ee_poweronnote_lenth;
					memcpy(AckBuf+1, AckBuf+1+6, 6 ); //����ʱ��
					memcpy(AckBuf+1+6, AckBuf+1+12+16, 16 );//����ʱ�̵���
					Comm_Calculate_Comp_Rp( AckBuf+1+6, 4, DI[3] );
					if( DI[3]==0x83 ) k += 4;
				}
			}
			
			if( ptrmax < DI[0] )	memset( AckBuf+1, 0x00, k );
//			if( ((DI[1]+(DI[2]<<8) == 0x3005) || (DI[1]+(DI[2]<<8) == 0x3010)) && SN  )	AckBuf[ ++AckBuf[0] ] = SN;
		}
	}
	
	return k;	//��ȡ�ɹ�
}

//��ϵ������㺯��, ÿ�μ���1��
//��������޹�: Offset = 0xff
void CalZhuhe( const unsigned char *ZhuBuf, unsigned char *RtBuf, unsigned char Mode, unsigned char Offset )
//ZhuBufҪ������������ͷ�����ܼ��ƽ�ȵ�����
//RtBuf�Ƿ��������������8�ֽڡ�
{
	signed long long Zhen;
	union B32_B08_2 Temp32;
	unsigned char i;
	
	Zhen = 0x00;

	if( Offset<=1 )	//�й�
	{
		switch( Mode&B0000_0011 ) //�й�����
		{
			case 0x01:
			case 0x02:
				memcpy( Temp32.B08, (uint08*)ZhuBuf, 4 );
				if( (Mode&B0000_0011) == 0x01 )
				{
					Zhen += Temp32.B32;
				}
				else
				{
					Zhen -= Temp32.B32;
				}
				break;
				
			default:
				break;
		}
	
		switch( Mode&B0000_1100 ) //�й�����
		{
			case 0x04:
			case 0x08:
				if( Offset == 0 )
				{
					memcpy( Temp32.B08, (uint08*)ZhuBuf+max_dl_lenth, 4 );
				}
				else
				{
					memcpy( Temp32.B08, (uint08*)ZhuBuf+4, 4 );
				}
				if( (Mode&B0000_1100) == 0x04 )
				{
					Zhen += Temp32.B32;
				}
				else
				{
					Zhen -= Temp32.B32;
				}
				break;
				
			default:
				break;
		}
	}
	else
	{
		//��������޹�1��2
		for(i=0; i<4; i++)
		{
			switch( (Mode>>2*i)&B0000_0011) //��1~4�����޹�
			{
				case 0x01:
				case 0x02:
					memcpy( Temp32.B08, (uint08*)ZhuBuf+max_dl_lenth*i, 4 );
					if( ((Mode>>2*i)&B0000_0011) == 0x01 )
					{
						Zhen += Temp32.B32;
					}
					else
					{
						Zhen -= Temp32.B32;
					}
					break;
				
				default:
					break;
			}
		}
	}

	memcpy( RtBuf, (uint08*)&Zhen, 8 );	//RtBuf�Ƿ��������������8�ֽڡ�
}


unsigned char Cal_Comb( unsigned char DI2, unsigned char DI1, unsigned char DI0, unsigned char *ReturnBuf )
//DI2: 0:���; 1:����; 2:����; 9:����ʱ��
//DI1: 0:��(����ʱ��); 1~4:1~4����; FF:����
//DI0: 0:��ǰ; 1~12:1~12������; FF:����(��13��)
//ReturnBuf: ���ݾ�Ϊ����
//��ǰ����,�õ���,����������Ը��ֽ���ǰ������ee
{
	unsigned char i, k, n, result, ptrmax;
	unsigned char Buf[ee_histroydl_lenth];
	union B32_B08 Temp32;
	unsigned char Obj;
	RecStore RtRec;
	RtFlash  RtAddr;

	if( DI2 > 0x09 ) return 0x00;
	
	if( (DI1 == 0xFF) && (DI0 == 0xFF) ) return 0x00;	//���߲���ͬʱΪFF��
	
	if( (DI1 > Bcd_To_Hex(Feik.Num[3])) && (DI1 != 0xFF) ) return 0x00;
	
	if( DI0 == 0xFF ) 
	{
		Temp32.B08[0] = 0;
		Temp32.B08[1] = max_histroy_p+1;
	}
	else
	{
		Temp32.B08[0] = DI0;
		Temp32.B08[1] = DI0+1;
	}
	
	if( DI1 == 0xFF ) 
	{
		Temp32.B08[2] = 0;
		Temp32.B08[3] = Bcd_To_Hex(Feik.Num[3])+1;
	}
	else
	{
		Temp32.B08[2] = DI1;
		Temp32.B08[3] = DI1+1;
	}
		
	if( DI0 ) //�ǵ�ǰ����
	{
		Obj = ee_histroyf_inpage;
		RtRec = GetRecNum( Obj, 0 ); //��¼�洢����׼��
		ptrmax = RtRec.ValPoint;
	}

	k = 0x00;
	for( n=Temp32.B08[0]; n<Temp32.B08[1]; n++ )	//DI0: 0~12,FF
	{
		if( n == 0x00 )	//��ǰ
		{
			if( DI2 != 0x09 )
			{
				memcpy( Buf, Fwdl.Pluse[0].B08, max_dl_lenth ); //����������
				memcpy( Buf+max_dl_lenth, Bkdl.Pluse[0].B08, max_dl_lenth ); //����������
				for(i=0; i<4; i++) //�������޹�����
				{
					memcpy( Buf+max_dl_lenth*(2+i), Rpdl[i].Pluse[0].B08, max_dl_lenth );
				}
			}
		}
		else if( n <= max_histroy_p )	//1~24������
		{
			RtAddr = GetRecAddr( Obj, 0, n, &RtRec );

			if( DI2 != 0x09 )
			{
				if( ptrmax >= n )
				{
					result = Flash_Rd_Bottom( RtAddr.AppPage, RtAddr.AppPos+5, Buf, RtRec.TotLen-5 ); //��Flash�ж�ȡ
					if( result ) return 0x00;
				}
				else
				{
					memset( Buf, 0x00, ee_histroydl_lenth-5 );
				}				
			}
			else	//����ʱ��
			{
				if( ptrmax >= n )
				{
					result = Flash_Rd_Bottom( RtAddr.AppPage, RtAddr.AppPos+1, ReturnBuf+k, 4 ); //��Flash�ж�ȡ
					if( result ) return 0x00;
				}
				else
				{
					memset( ReturnBuf+k, 0x00, 4 );
				}
				
				k += 4;
			}
		}
		else return 0x00;

		if( DI2 != 0x09 )
		{
			for( i=Temp32.B08[2]; i<Temp32.B08[3]; i++, k+= 8 )	//������
			{
				if( DI2 == 0x00 )	//���
				{
					if( n == 0x00 )	//��ǰ
						result = Mode.Comp_B;
					else
						result = Buf[ee_histroydl_lenth-3-5];
					
					CalZhuhe( Buf+i*4, ReturnBuf+k, result, 0 );	//��������й�
				}
				else if( DI2 == 0x01 || DI2 == 0x02 )	//������� or �������
				{
					memset( ReturnBuf+k, 0x00, 8 );
					memcpy( ReturnBuf+k, Buf+max_dl_lenth*(DI2-1)+i*4, 4 );
				}
				
				else if( DI2 == 0x03 || DI2 == 0x04 )	//����޹�1������޹�2
				{
					if( n == 0x00 )	//��ǰ
						result = Mode.Rpcomp[DI2-3];
					else
						result = Buf[ee_histroydl_lenth-2-5+(DI2-0x03)];
					
					CalZhuhe( Buf+max_dl_lenth*2+i*4, ReturnBuf+k, result, 0xff );//��������޹�
				}
				else 	//�������޹�
				{
					memset( ReturnBuf+k, 0x00, 8 );
					memcpy( ReturnBuf+k, Buf+max_dl_lenth*(2+(DI2-5))+i*4, 4 );
				}
			}
		}
	}

	return (k);
}



void Cal_Comb_Usedl( unsigned char DI2, unsigned char DI0, unsigned char *ReturnBuf )
//DI2: 0:���������õ���;1:���õ���;2:���õ���
//DI0: 0:��ǰ; 1:��1
//ReturnBuf: ʱ��4/Ԥ��4+�߾��ȵ���8�ֽ�
{
	unsigned char result;
	unsigned char Buf[ee_histroyusedl_lenth+8];
	
	if( DI2 == 2 )
	{
		//׼������
		memcpy( Buf, Sclock.Clockbackup+2, 4 );//����ʱ��
		Cal_Comb( 0, 0, 0, Buf+4 );	//���㵱ǰ��ϵ���	

		I2C_Read_Eeprom( ee_pre1_histroyusedl_page+DI2, 0, Buf+8, ee_histroyusedl_lenth );
		
		memcpy( ReturnBuf+4, Buf+8*DI0+4, 4);
		memcpy( ReturnBuf+8, Buf+8*DI0+4+8, 4);
	}
	else
	{
		//׼������
		Cal_Comb( 0, 0, 0, Buf );	//���㵱ǰ��ϵ���(���������õ��������õ���)	

		I2C_Read_Eeprom( ee_pre1_histroyusedl_page+DI2, 0, Buf+4, ee_histroyusedl_lenth );
	
		memcpy( ReturnBuf+4, Buf+4*DI0, 4);
		memcpy( ReturnBuf+8, Buf+4*DI0+4, 4);
	}
	
	//�����õ���
	if( ReturnBuf[4+3]&0x80 )	result = 0x02;
	else result = 0x01;
	if( ReturnBuf[4+3]&0x80 )
	{
		union B32_B08_2 Temp32;
		memcpy( Temp32.B08, ReturnBuf+4, 4 );
		Temp32.B32 = ~Temp32.B32+1;
		memcpy( ReturnBuf+4, Temp32.B08, 4 );
	}

	if( ReturnBuf[8+3]&0x80 )	result |= 0x04;
	else result |= 0x08;
	if( ReturnBuf[8+3]&0x80 )
	{
		union B32_B08_2 Temp32;
		memcpy( Temp32.B08, ReturnBuf+8, 4 );
		Temp32.B32 = ~Temp32.B32+1;
		memcpy( ReturnBuf+8, Temp32.B08, 4 );
	}
		
	CalZhuhe( ReturnBuf+4, ReturnBuf+4, result, 0x01 );
		
	//Ӧ������
	Hex2Bcd_Dl_G( ReturnBuf+4, 0 );	//������תBCD����(�߾���)(���)
		
	if( DI2 == 0x02 ) //���õ���
	{	
		memcpy( ReturnBuf, Buf+8*DI0, 4 );	//����ʱ��
			
		if( (Price.Ladder_Mode == 0x00) && (DI0 == 0x00) )
		{
			memset( ReturnBuf, 0x00, 4+8 );//�½���,��ǰ��������Ϊ0	
		}
	}
}


uint08 RdHisPd( unsigned char *DI, uint08 *AckBuf )
//return 0: success; other: failure.
{
	unsigned char ptrmax, MaxEvent;
	unsigned char ptr, len, result, Buf[16];
	unsigned int  page;

	AckBuf[0] = 0x00;

	if( DI[1] == 0x02 ) //�¶����������
	{
		if( DI[0] > 0x24 ) return 1;
		page = ee_powerdown_month_page;
		len = ee_powerdownmonth_lenth;
		ptr = ee_monpowerdownn_inpage;
		MaxEvent = max_powerdownmonth_p;
	}
	else //�궳���������
	{
		if( DI[0] > 0x03 ) return 1;
		page = ee_powerdown_year_page;
		len = ee_powerdownyear_lenth;
		ptr = ee_yearpowerdownn_inpage;
		MaxEvent = max_powerdownyear_p;
	}
			
	AckBuf[0] = 6;
	if( DI[0] == 0 ) //����ǰ
	{
		if( DI[1] == 0x02 )
		{
			Get_Keep_Timer(8, Buf);		//����ͣ���ۼƴ���
			Get_Keep_Timer(9, Buf+4);	//����ͣ���ۼ�ʱ��
		}
		else
		{
			Get_Keep_Timer(10, Buf);	//����ͣ���ۼƴ���
			Get_Keep_Timer(11, Buf+4);	//����ͣ���ۼ�ʱ��
		}
	}
	else
	{
		ptrmax = RdRecTimes(ptr);//������Чָ��
		result = Read_Event_Point( ptr );
		
		if( ptrmax < DI[0] ) {memset( AckBuf+1, 0x00, AckBuf[0] );return 0x00;}
		
		if( result < (DI[0]-1) ) result += MaxEvent;
		result -= (DI[0]-1);
		I2C_Read_Eeprom( page+result/8, (result%8)*8, Buf, len ); //����n��
	}
	
	memcpy( AckBuf+1, Buf+0, 3 );
	memcpy( AckBuf+4, Buf+4, 3 );
	
	return 0x00;	//��ȡ�ɹ�
}


//��̼�¼��˵�����Ӱ��±�̿��ص������̿��أ��ҶԵ��ܱ���б�̲�����
//��¼Ϊһ�α�̼�¼����¼��̵����10 �����ݱ�ʶ����̽���ʱ�̡�
//��̼�¼����ʱ�̣�1.�����˳����ģʽ; 2.�����Чʱ�����; 3.�����֤ʧЧ; 4.�����֤��Чʱ�����
//����4���������Ҫ����New_Program_Rec = 0;
void ProgramRecord( unsigned char *Dix, unsigned char *Opt )
{
	if( first_prog_flag == 0 )	//��Ҫ��������һ����̼�¼
	{
		first_prog_flag = 1;	//�������α�̼�¼
		memcpy( Eeprom.Buffer+6, Opt, 4 );			//�����ߴ���(4)
		memcpy( Eeprom.Buffer+10, Dix, 4 );			//���ݱ�ʶ(4)
		memset( Eeprom.Buffer+14, 0xFF, 36 );			//����Ĳ�0xFF(4*9)
		Event_Record(ee_programn_inpage);
	}
	else
	{
		memcpy( Eeprom.Buffer+50, Dix, 4 );			//���ݱ�ʶ(4)
		Event_Record(ee_programn_inpage|0x80);
	}
}


unsigned char UpdateSysPara( unsigned char Start, unsigned char *Para, unsigned char Len )
{
	unsigned char result, Temp08, Inpage;
	unsigned int Page;
	unsigned char Buf[64];
	unsigned char  *ptr;
	
	switch( Start&0xE0 )
	{
		case 0x00:
			Page = ee_displaypara_page;
			Inpage = ee_displaypara_inpage;
			Temp08 = ee_displaypara_lenth;
			ptr =  &Display_Para.S_Number;
			disppm_veri_flag = 1;
			break;
			
		case 0x40:
			Page = ee_esampara_page;
			Inpage = ee_esampara_inpage;
			Temp08 = ee_esampara_lenth;
			ptr = Esam_Para.Current_Ratio;
			break;

		case 0x60:
			Page = ee_weekholiday_page;
			Inpage = ee_weekholiday_inpage;
			Temp08 = ee_weekholiday_lenth;
			ptr = &Week_Holiday.Status;
			run_timezone_flag = 1;
			Tariff.Crc16.B08[0] += 1;
			break;
			
		case 0x80:
			Page = ee_featureword_page;
			Inpage = ee_featureword_inpage;
			Temp08 = ee_featureword_lenth;
			ptr =  Mode.Bps;
			mode_veri_flag = 1;
			break;
			
		case 0xA0:
			Page = ee_vollimit_page;
			Inpage = ee_vollimit_inpage;
			Temp08 = ee_vollimit_lenth;
			ptr =  VolLimit.MaxVolLmt.B08;
			addr_veri_flag = 1;
			break;	
			
		case 0xC0:
			Page = ee_starttimer_page;
			Inpage = ee_starttimer_inpage;
			Temp08 = ee_starttimer_lenth;
			ptr = Starttime.Shiqu;
			run_timezone_flag = 1;
			break;
			
		default:
			return 1;
	}
	
	//����RAM��E2�еĿͻ����
	ReadE2WithBackup( Page, Inpage, Buf, Temp08 );
	Exchange( Buf+(Start&0x1F), Para, Len );	//���ݵ���
	result = WriteE2WithBackup( Page, Inpage, Buf, Temp08 );
	if( result ) return 1;
	
	memcpy( ptr, Buf, Temp08+2 );	//����RAM
	return 0;
}


unsigned char JudgeSwitch( unsigned char *Buf, unsigned char Inv )
{
	unsigned char i, result;

	if( ChkBufZero(Buf,5)==0 ) return 2;//�Ϸ�����ʱ��(ȫ0x00)
	
	for( i=0; i<5; i++ )
	{
		if( Buf[i] != 0x99 ) break;
	}
	
	if( i < 5 )
	{
		if( Inv ==1 )	Inverse( Buf, 5 );
		result = JudgeClockNoWeek( 1, Buf, 5 );
		if( Inv ==1 )	Inverse( Buf, 5 );
		return (result); //����
	}
	else
	{
		return 3;		//�Ϸ�����ʱ��(ȫ0x99)
	}
}

void JudgeSwitch2( unsigned char offset )//�ж�����ʱ���Ƿ�Ϊȫ99,�������Ĭ�ϵ�һ��
{
	I2C_Read_Eeprom44( ee_changecontrol_page, Eeprom.Buffer, ee_changecontrol_lenth);//�����������ֽ�
	if( Eeprom.Buffer[ offset ] != 0xFF )
	{
		Eeprom.Buffer[ offset ] = 0xFF;
		I2C_Write_Eeprom44( ee_changecontrol_page, Eeprom.Buffer, ee_changecontrol_lenth ); //д���������ֽ�
		Tariff.Crc16.B08[0] += 1;
		
		//����Լ������
		Freeze_Dl(ee_appointfreeze1_page+6*offset,3+offset);
	}
}

//ʱ��/ʱ�α��̼�¼
unsigned int ShiquRecord( unsigned char *InDi, unsigned char *InOpt )
{
	unsigned char i, n, Temp08, Ptr;
	union B16_B08_2 AddrA, AddrB;
	unsigned char Buf[64];
	
	if( InDi[0] == 0x00 )	//ʱ����
	{
		Ptr = ee_shiqun_inpage;
		AddrA.B16 = ee_shiqurecord_page;
		AddrB.B16 = ee_shiqu1_page;
	}
	else	//��ʱ�α�
	{
		Ptr = ee_shiduann_inpage;
		AddrA.B16 = ee_shiduanrecord_page;
		AddrB.B16 = ee_shiduantable1_1_page;
	}
		
	//��ʷ��¼(5,ÿ�ֽڴ���2��)+����ʱ�̣�6��+�����ߴ��루4��+ ʱ������ǰ�ڼ��׵�1~14 ʱ�������ݣ�3*14��
	//��ʷ��¼(5,ÿ�ֽڴ���2��)+����ʱ�̣�6��+�����ߴ��루4��+ ʱ�α���ǰ�ڼ��׵ڼ� ��ʱ�α����ݣ�3*14��
	Number_Add1( Ptr );	//ʱ��/ʱ���޸��ܴ���+1(3)
	
	Temp08 = Read_Event_Point( Ptr );
	I2C_Read_Eeprom( AddrA.B16+Temp08, 70, Buf, 5 );	//��ʷ��¼(5,ÿ�ֽڴ���2��)
	
	//i��Χʱ��0��1,ʱ��0��15
	if( InDi[2] == 1 )	i = 0;
	else
	{
		if( InDi[0] == 0 )	i = 1;	//ʱ����
		else i = 8;	//��ʱ�α�
	}
	if( InDi[0] ) i += (InDi[0]-1);			//����õ���i�����޸�

	Temp08 = Write_Event_Point( Ptr );	//����ָ��+1

	n = Temp08/2;
	if( Temp08%2 )	//��ʷ��¼(5,ÿ�ֽڴ���2��)
		Buf[n] = (Buf[n]&0x0F)+(i<<4);		//��¼��Ӧ�ֽڵĸ�4λ
	else
		Buf[n] = (Buf[n]&0xF0)+i;			//��¼��Ӧ�ֽڵĵ�4λ
	
	memcpy( Buf+5, Sclock.Clockbackup, 6 );	//����ʱ��(6)
	memcpy( Buf+11, InOpt, 4 );				//�����ߴ���(4)
	I2C_Read_Eeprom( AddrB.B16+i, 0x00, Buf+15, 42 );	//���ǰ ʱ����orʱ�ε�i��(42)
	
	I2C_Write_Eeprom( AddrA.B16+Temp08, 70, Buf, ee_shiduanrecord_lenth );	//ʱ����
	
	return (AddrB.B16+i);
}


void JTRecord( unsigned char *InOpt )
{
	unsigned char i, Temp08;
	unsigned char Buf[ee_ladder_lenth+2];
	
	//--- ���ݱ�̼�¼ ---
	memcpy( Eeprom.Buffer+6, InOpt, 4 );			//�����ߴ���(4)
	Temp08 = Event_Record( ee_jtpricen_inpage );

	for( i=0; i<4; i++ )
	{
		if( i < 2 ) I2C_Read_Eeprom( ee_ladder1_page+i, 0, Buf, ee_ladder_lenth);
		else I2C_Read_Eeprom( ee_ladder2_page+i-2, 0, Buf, ee_ladder_lenth);
		LoopInverse( Buf, 13, 4 );
		I2C_Write_Eeprom( ee_jtpricerecord2_page+4*Temp08+i, 0x00, Buf, ee_jtpricerecord2_len );
	}
	//--- ���ݱ�̼�¼ end ---
}


unsigned char Set_Comm_Rate( unsigned char Ch, unsigned char Rate )
{
	switch( Ch )
	{
		case 0x01:	//�����ͺ����ڲ�����������	NN  1
			if( Rate == 0x04 )	//1200bps
			{
				return 0;
			}
			break;
						
//		case 0x02:	//�Ӵ�ʽ�����ڲ�����������    NN  1
//			Temp08 = 0x00;
//			break;
			
		case 0x03:	//ͨ�ſ�1 ������������          NN  1
			if( (Rate == 0x04) || (Rate == 0x08) || (Rate == 0x10) || (Rate == 0x20) || (Rate == 0x40) )	//1200, 2400, 4800, 9600, 19200
			{
				UpdateBps = 1;	//�����ʸı��־(��Լ������λ)
				return(UpdateSysPara( 0x80+0, &Rate, 1 ));
			}
			break;
			
//		case 0x04:	//ͨ�ſ�2 ������������          NN  1
//			if( (Rate == 0x20) || (Rate == 0x40) || (Rate == 0x01) )	//9600��19200��115200
//			{
//				UpdateBps = 1;	//�����ʸı��־(��Լ������λ)
//				return(UpdateSysPara( 0x80+31, &Rate, 1 ));
//			}
//			break;

		case 0x05:	//ͨ�ſ�3 ������������          NN  1
//			if( (Rate == 0x04) || (Rate == 0x08) || (Rate == 0x10) || (Rate == 0x20) || (Rate == 0x40) || (Rate == 0x80) )	//1200, 2400, 4800, 9600, 19200, 38400
			if( (Rate == 0x04) || (Rate == 0x08) || (Rate == 0x10) || (Rate == 0x20) || (Rate == 0x40) )	//1200, 2400, 4800, 9600, 19200
			{
				UpdateBps = 1;	//�����ʸı��־(��Լ������λ)
				return(UpdateSysPara( 0x80+30, &Rate, 1 ));
			}
			break;
			
		case 0x85:	//ͨ�ſ�3 ������������          NN  1	Э�����
//			if( (Rate == 0x04) || (Rate == 0x08) || (Rate == 0x10) || (Rate == 0x20) || (Rate == 0x40) || (Rate == 0x80) )	//1200, 2400, 4800, 9600, 19200, 38400
			if( (Rate == 0x08) || (Rate == 0x10) || (Rate == 0x20) || (Rate == 0x40) )	//2400, 4800, 9600, 19200
			{
				UpdateBps = 1;	//�����ʸı��־(��Լ������λ)
				Zb_Comm_Timer = Zb_Comm_Timer_delay;	//�����ز�ͨѶ�����ʻָ���ʱ��
//				return(UpdateSysPara( 0x80+30, &Rate, 1 ));
				Mode.Zbbps_Ram = Rate;
				return 0;
			}
			break;											

		default:
			break;
	}
	
	return 1;
}


//ͨ����ʾ�����ݱ�ʶ�����ȷ����Ӧ��������
unsigned short GetLcdNo( unsigned char *LcdSn )
{
	unsigned char n, Temp08, Sn;
	unsigned short result;
	union B32_B08 Temp32;
	
	memcpy( Temp32.B08, LcdSn, 4 );
	Sn = LcdSn[4];

	//���,����,����,����޹�1/2,��һ�����޹�����~���������޹�����
	if( (Temp32.B08[3] == 0x00) 
	 && (Temp32.B08[2] <= 0x08) 
	 && (Temp32.B08[1] <= max_feilvcount) 
	 && (Temp32.B08[0] <= 0x0C) )
	{
		Temp08 = 0;		//��������0
		result = 0x200; 	//��ͨ����
		result += ((Temp32.B08[2]&0x0f)*max_disploop+1)+Temp32.B08[1]+Temp32.B08[0]*(max_feilvcount+1);
	}
	else if( (Temp32.B08[3] == 0x00) 
//	 && ((Temp32.B08[2] >= 0x70)&&(Temp32.B08[2] <= 0x78))
	 && ((Temp32.B08[2] >= 0x60)&&(Temp32.B08[2] <= 0x68))//�߾�����ʾ����
	 && (Temp32.B08[1] <= max_feilvcount) 
	 && (Temp32.B08[0] <= 0x0C) )
	{
		if( Temp32.B08[2] == 0x68 )  Temp32.B08[2] = 0x70;//�߾�����ʾ����
		else Temp32.B08[2] += 0x11;
		
		Temp08 = 0;		//��������0
		result = 0x800; 	//�߾��ȵ���
		Temp32.B08[2]-=0x70;	//�߾��ȵ���
		result += ((Temp32.B08[2]&0x0f)*max_disploop+1)+Temp32.B08[1]+Temp32.B08[0]*(max_feilvcount+1);
	}	
	//------ ������ʾ��Ŀ����Ŵ�200��ʼ--------
	else
	{
		for( n=0; n<disp_num; n++ )
		{
			if( Byte2uInt(Temp32.B08) == disp_table[n] ) break;
		}
		
		if( n >= disp_num ) return 0x00;	//��ʾ��Ŀ����

		switch( n )	//ȷ��������
		{
			case 15:	//����
			case 17:	//���
			case 19:	//��ַ
			case 23:	//������ں�ʱ��
			case 25:	//�������ں�ʱ��
				Temp08 = 1;		//��������1
				break;
				
			case 0:	//ȫ��
				if( Sn != 0xFF ) 	return 0x00;	//��ʾ��Ŀ����

				Sn = 0x00;
				Temp08 = 0;		//��������0
				break;
				
			default:
				Temp08 = 0;		//��������0
				break;
		}
		
		result = 200+n+Sn;		//��ʾ���ΪHEX
	}

	if( Sn > Temp08 )		
		return 0x00;	//��ʾ��Ŵ�
	else
		return (result);
}

unsigned char JudgeEndClock()	//��ֹʱ��Ϸ��Ժ���Ч���ж�
{
	if( JudgeClockNoWeek( 0, Ic_Comm_RxBuf+2, 6 ) || (Cmp_Bcd_Inv( Ic_Comm_RxBuf+2, Sclock.Clockbackup, 6 )==2) )return 0x04; //����
	else return 0x00; //�ɹ�
}

unsigned char Decrypt( unsigned char Ch, unsigned char File, unsigned char Len )
{
	unsigned char result, TmpLen;

	if( Ch < CHNum )
	{
		if( Len != 0x02 )	
		{
			TmpLen = 16;
			memcpy( Uart[Ch].Buf+22+16, Uart[Ch].Buf+18,  4 );
		}
		else TmpLen = Uart[Ch].Buf[9]-12-4;
	
		result = Update_ESAM_Bin_Mac( File, 0x00, Uart[Ch].Buf+22, TmpLen );
	}
	else
	{
		result = WriteBinWithMac( ESAM, File, 0x00, 16+4 );
	}
	if( result ) return IC_MAC_ERR;	//

	result = ReadBinFile( ESAM, File, 0x00, Len );
	if( result ) return IC_ESAM_RDWR_ERR;
	
	if( Len == 0x02 )
	{
		result = ReadBinFile( ESAM, File, 0x01, Ic_Comm_RxBuf[1]+1 );
		if( result ) return IC_ESAM_RDWR_ERR;
	}
	else
	{
		//1A00 091104100301 9000
		Inverse( Ic_Comm_RxBuf+2, 6 );
		
		result = JudgeEndClock();	//�жϽ���ʱ��
		if( result ) return IC_FORMAT_ERR; //����
	}

	return 0x00;
}


//0��ʾ�޼�¼,1��ʾ�з����޽���,2��¼����
unsigned char ChkLastclockerrRcdTime( void )
{
	unsigned char result;
	unsigned char Buf[12];
	
   	if( RdRecTimes(ee_clockerrn_inpage) )
	{
		result = Read_Event_Point(ee_clockerrn_inpage);
		I2C_Read_Eeprom( ee_clockerrrecord_page+result, ee_clockerrrecord_inpage, Buf, 12 );	//ʱ��  
		if( ChkBufZero(Buf+6,6) == 0 ) return 1;   //��ʾ�з����޽���
		else return 2;//��¼����
	}
	else  return 0;  //��ʾ�޼�¼   
}


void CommSetRtc_Adj()
{	
	unsigned char Buf[8];
	
	memcpy( Buf, Sclock.Clockbackup, 6 );	//����Уʱǰʱ��
	
	Read_Rtc( Sclock.Clockmain );//��ʱ��
	Syn_Clock();	//ͬ��ʱ��
	
	if( Cmp_Bcd_Inv( Buf, Sclock.Clockbackup, 6 ) == 1 )
	{
		ClearPloadRec( Sclock.Clockbackup );
	}
	
	if( Cmp_Data( Buf+3, Sclock.Clockbackup+3, 3 ) != 3 )	//���ڷ����仯
	{
		unsigned char Result;
		
		Clr_Zero_Data();	//���������������
		
		//�յ�ѹ�ϸ��ʼ�¼
		CalLoad( Eeprom.Buffer, 0 );
		Result = Write_Event_Point(ee_dayvolpassn_inpage);
		I2C_Write_Eeprom( ee_dayvolpass_note_page+Result/4, ee_dayvolpassnote_inpage+(Result%4)*ee_dayvolpassnote_len, Eeprom.Buffer, ee_dayvolpassnote_len );
		InitVolSts( 0 ); //�����Ӧ�ĵ�ѹ�ϸ���
		
		if( Buf[5] != Sclock.Clockbackup[5] ) //��ı�
		{
			month_change_flag = 1;
			year_change_flag = 1;
			year_change_flag2 = 1;
		}
		else if( Buf[4] != Sclock.Clockbackup[4] ) //�¸ı�
		{
			month_change_flag = 1;
		}
		if( month_change_flag ) //�µ�ѹ�ϸ��ʼ�¼ת��
		{
			//�µ�ѹ�ϸ��ʼ�¼
			CalLoad( Eeprom.Buffer, 1 );
			Result = Write_Event_Point(ee_monvolpassn_inpage);
			I2C_Write_Eeprom( ee_monvolpass_note_page+Result/4, ee_monvolpassnote_inpage+(Result%4)*ee_monvolpassnote_len, Eeprom.Buffer, ee_monvolpassnote_len );
			InitVolSts( 1 ); //�����Ӧ�ĵ�ѹ�ϸ���
		}	
		Freeze_Pddata();	//�����������		
	}
	
	run_timezone_flag = 1;
	Tariff.Crc16.B08[0] += 1;
	RefreshPrice();
	run_readrtc_flag = 1;
	
	Wr_Powerdown_Data(0);//д����������ݵ�����ee
	Wr_Pretime_Hisfreeze();	//д��һ�ν���ʱ��
	Wr_Pretime_Dayfreeze();	//д��һ���ն���ʱ��
	
	if( ChkLastclockerrRcdTime() == 1 ) Note_Run_Event(ee_clockerrn_inpage|0x80); //ʱ�ӹ��Ͻ�����¼(ʱ�ӺϷ�)
}


unsigned char CommSetRtc( unsigned char Ch, unsigned char Start, unsigned char Len )
{
	unsigned char result;
	unsigned char Buf[8];
	
	result = Judge_Clock( Start, &Uart[Ch].Buf[22], Len ); //�ж������Ƿ�Ϸ�
	if( result != 0 ) return 1; //����ֵ����
	
	if( clock_error )
	{
		Buf[0] = 0x00;	//ss
		Buf[1] = 0x00;	//mm
		Buf[2] = 0x00;	//hh
		Buf[3] = 0x05;	//WW
		Buf[4] = 0x01;	//DD
		Buf[5] = 0x01;	//MM
		Buf[6] = 0x10;	//YY
	}
	else
	{
		Read_Rtc( Buf );//��ʱ��
	}
	
	memcpy( Buf+Start, Uart[Ch].Buf+22, Len );
	
	Buf[3] = (CalcAbsDay(Buf+2)+6)%7;	//������,��ʽΪ��+��+ʱ+��+��+��+��,��ʼ��ַ��,���տ�ʼ����

	result = Set_Rtc( 0, Buf, 7 ); //
	if( result != 0 ) return 2; //����RTCʧ��
	
	memcpy( Uart[Ch].Buf+18+4, Sclock.Clockbackup, 6 );	//Уʱǰʱ��(6)(��ʱ����)
	
	CommSetRtc_Adj();	//����ʱ�ӵ����������
	
	memcpy( Eeprom.Buffer, Uart[Ch].Buf+18, 4 );		//�����ߴ���(4)
	memcpy( Eeprom.Buffer+4, Uart[Ch].Buf+18+4, 6 );	//Уʱǰʱ��(6)
	memcpy( Eeprom.Buffer+10, Sclock.Clockbackup, 6 );	//Уʱ��ʱ��(6)
	DltoEepromBuf( 16 );					//���������+�������
	Four_RpdltoEepromBuf( 16+8 );				//���������޹�
	Event_Record( ee_setclockn_inpage );
	
	return 0;
}


unsigned char Judge_Min_Space( unsigned char *bufA )
{				
	unsigned char result,Temp08;
	unsigned char Buf[16];
	
	memcpy( Buf+0, bufA, 6 ); //��Ҫ�жϵ�ʱ��
	memcpy( Buf+6, Sclock.Clockbackup, 6 ); //��ǰʱ��
	
	Temp08 = Cmp_Bcd_Inv( Buf+0, Buf+6, 6 ); 
	switch( Temp08 )
	{
		case 0x01: //ʱ�� > ��ǰʱ��
			Add_Min_Clock( Buf+6, 10 ); //�Ե�ǰʱ������5���Ӵ���
			break;
			
		case 0x02: //ʱ�� < ��ǰʱ��
			Add_Min_Clock( Buf+0, 10 ); //��ʱ������5���Ӵ���
			break;
			
		default:
			break;
	}
	
	if( Temp08 )
	{
		result = Cmp_Bcd_Inv( Buf+0, Buf+6, 6 );
		if( result == Temp08 ) //����5min����
		{
			return 1;	//����5min����
		}
	}
	
	return 0;
}


unsigned char  Cal_ChkSum(unsigned char *Buf,unsigned char Len)
{
	unsigned char i,csdata=0;
	
	for(i=0;i<Len;i++)
	{
		csdata+= Buf[i];
	}
	return(csdata);
}


unsigned char Yc_Auth(unsigned char Ch, unsigned char *OutBuf)
{
	if( Clear_Rand_Gene() ) return 1;	//Esam Reset

	LoopInverse( Uart[Ch].Buf+18, 3, 8 ); //����1+�����1+��ɢ����

	if( Uart[Ch].Buf[34] || Uart[Ch].Buf[35] ) return 1;
	if( Cmp_Meter_Id(Uart[Ch].Buf+36) ) return 1;

	if( Authorization( Uart[Ch].Buf+18, 4 ) ) return 8; //�����֤ʧ��

	memcpy( PcRand,  Uart[Ch].Buf+26, 8 );	//�����, 8bytes 
	memcpy( PcRst8B, Uart[Ch].Buf+34, 8 );	//��ɢ����, 8bytes

	first_prog_flag = 0;	//���״α�̱�־

	//������Ϣ: �����2+ESAM���к�
	Exchange( OutBuf+1, EsamRand, 4 );	//�����2, 4bytes
	Exchange( OutBuf+5, EsamRst8B, 8 );	//ESAM���к�, 8bytes
	return 0;
}

//��֤ͨ���������Ķ����ָ��ִ����Ӧ����
/*Ch:
	0x14���û���Զ��ģʽ�µĺ�բ����޲����ߴ��룬�����
	0x24~0x26��Զ���ն˵ĺ�բ����в����ߴ��룬�����
	0x20~0x22��96��Զ�̿��Ƽ̵�������в����ߴ��룬�����
	0x00~0x02��03��Զ�̿��Ƽ̵�������в����ߴ��룬�޽���
*/
unsigned char Relay_Ctrl(unsigned char Ch)
{
	unsigned char Temp08;
	
	if(Ch >= 0x10) //��03�����룬��������Ҫ����
	{
		Temp08 = Decrypt( Ch&0x0f, 0x87, 0x08 );
		if( Temp08 ) return(Temp08);
	}
	
	//��֤ͨ���������Ķ����ָ��ִ����Ӧ����
	Temp08 = 0x00;
	switch( Ic_Comm_RxBuf[0] )	//N1
	{
		case 0x1A:	//������բ
			if(relay_commu_close_flag == 1) {Temp08 = 0x04;break;}
			relay_commu_open_flag = 1;
			
			if( relay_status_flag )
			{
				Opendelaytimer = 0;	//�Ѿ���բ�˾Ͳ�Ҫ�ٵ���ʱ
			}
			else Opendelaytimer = Calculate_Timer(0);
			
			if( over_xxx_flag && (CurrentTimer || (relay_status_flag==0)) ) CurrentTimer = Calculate_Timer(1); //���ڴ������ʱ��բ����������
			
			relay_commu_disable_close_flag = 0;
			relay_commu_close2_flag = 0;	//�屣������־
					
			break;

		case 0x1B:	//�����բ����
			if(relay_commu_close_flag == 1) break;
			if(relay_commu_open_flag == 0)	break;

			Clr_Commu_Relaydata();
			if(Relay_Mode != 0x55)
			{
				if( relay_status_flag == 1 )
				{
					relay_commu_disable_close_flag = 1;
				}
			}
			break;
			
		case 0x1C:	//ֱ�Ӻ�բ��
			Clr_Commu_Relaydata();
			Enable_Closerelay();
			break;

		case 0x2A:	//��������
			relay_commu_alarm_flag = 1;
			Temp08 = 0xff;
			break;

		case 0x2B:	//�����������
			relay_commu_alarm_flag = 0;
			Temp08 = 0xff;
			break;

		case 0x3A:	//�����磬
			relay_commu_close_flag = 1;
			Clr_Commu_Relaydata();
			if(Relay_Mode != 0x55)//���ü̵���
			{
				if( relay_status_flag == 1 )
				{
					relay_commu_disable_close_flag = 1;//�忨���ܱպϼ̵���
				}
			}
			break;

		case 0x3B:	//����������
			if( relay_commu_close_flag ) relay_commu_close2_flag = 1;//�ñ�������־
			relay_commu_close_flag = 0;
			Temp08 = 0xff;
			break;

		default:
			Temp08 = 0x04;
			break;
	}

	if( Temp08 == 0x04 ) return(IC_FORMAT_ERR);
	else
	{
		if( (Temp08 != 0xff) && (Ch != 0x14) ) I2C_Write_Eeprom(ee_operatorcode_page, ee_operatorcode_inpage, &Uart[Ch&0x03].Buf[14], 4);//�����ߴ���д����ee
		
		if( Ic_Comm_RxBuf[0] == 0x1B || Ic_Comm_RxBuf[0] == 0x1C || Ic_Comm_RxBuf[0] == 0x3A )
		{
			if( Relay_Mode == 0x55 ) relay_cleardl_flag = 0; //�����ñ�������־
		}
				
		Store_Meterstatus();	//������״̬�ֽ�
		
		return 0;
	}
}

//��ȡǮ���ļ���
//Type = 1������¼�ļ�
//Type = 2����MAC��ȡǮ���ļ�
unsigned char Get_Money_File(unsigned char Type, unsigned char *OutBuf)
{
	unsigned char i, K;
		
	for(i=0; i<2; i++)
	{
		K = i*2+1;
		if(Type == 1) { if( ReadRecFile(K) ) return 1; }
		else { if( ReadBinWithMac( ESAM+0x10, K, 0x14, 4+4) ) return 1; }
		LoopExchange( OutBuf+i*(Type*4), Ic_Comm_RxBuf, Type, 4 );
	}

	return 0;
}

void MacExchange( unsigned char *Drc, unsigned char *Src, unsigned char Len )
{
	Exchange( Drc, Src, Len );
	Exchange( Drc+Len, Src+Len, 4 );
}

//Զ�������֤/�����ն������֤��Ч�ж�
unsigned char Comm_Auth_Judge( void )
{
	if( identity_prog_flag ) return 1;
	else return 0;
}

//�޸�������ز�������λ����ģ��
void Ble_Rst_Judge(uint08 Ch)
{
	if( Ch == CHBLE ) Ble_Reset = 0x55;	//Ӧ����ٸ�λ
	else
	{
		Ble_Reset = 0xAA;
		reg_veri_flag = 1;
	}
}

void Uart_Proc( unsigned char Ch )
{
	unsigned char i, n=0, Temp08=0, result, Err_DI=0, Auth=0, Remain = 0x00;
	unsigned short k=0;
	unsigned int  MeterClear = 0;
	unsigned char OutBuf[1024];
	unsigned char Buf[70],ChangeBuf[32];
	unsigned char ecode *Code_Flash_Char;
	unsigned char *Ptr;
	union B16_B08_2 Temp16;
	union B32_B08_2 Temp32,DI07,DI08;
	union B32_B08_2 OptID;
	unsigned char  Loop=0, Times=0;
	unsigned short Len=0;
	
	if( EA_OFF ) return;//���粻����,����ֱ�ӷ���
	
	Uart[Ch].Flag &= ~(B0000_0100);
	
	Adj_Clk_Timer = Adjclk_timer_delay;	//����������ʱ8Mʱ�ӵ�У����
	
	if( Ch==CHZB )
	{
		if( Zb_Comm_Timer ) Zb_Comm_Timer = Zb_Comm_Timer_delay;	//���������ز�ͨѶ�����ʻָ���ʱ��
		
		Mod_Comm_Timer1 = Mod_Comm_Timer_delay1;	//����ͨ��ģ�鳬ʱ��ʱ��
		Mod_Comm_Timer2 = 0;				//ͨ��ģ���쳣��ʱ��ʱ������
		if( commmodule_failed_flag )
	 	{
	 		commmodule_failed_flag = 0;		//��ͨ���쳣��־
	 		Store_Meterstatus();
	 		Note_Run_Event(ee_commerrn_inpage|0x80);//ͨ���쳣�¼�����
	 	}
	 }
	 
	ble_inter_flag = 0;
	if( Ch==CHBLE ) 
	{
		if( Uart[Ch].Buf[3] == 0xFF )  ble_inter_flag = 1;//�����ڲ�����
			
		if( Ble_Step == 1 ) Ble_Step = 0;
		Ble_RstTimer = Zb_Comm_Timer_delay;	//����������λ��ʱ��
	}
	
	if( (Uart[Ch].Buf[8]&B1000_0000) && !ble_inter_flag )	//ͨѶbit7=1���������������Ӧ
	{
		Uart[Ch].Overtime_Timer = 2;
		return;
	}

	result=Cal_ChkSum(Uart[Ch].Buf,Uart[Ch].Buf[9]+10);
		
	for( i=0; i<Uart[Ch].Buf[9]; i++ )
	{
		Uart[Ch].Buf[ 10+i ] -= 0x33;
	} 	
	
	if( Uart[Ch].Buf[10+i] != result )
	{
		Uart[Ch].Overtime_Timer = 2;
		return;
	}
	
	memcpy( DI07.B08, Uart[Ch].Buf+10 ,4 );
	
	memcpy( OptID.B08, Uart[Ch].Buf+14 ,4 );
	
	if( (Ch == CHHW) && (progenable==0) )	//����ͨ�ſ�
	{
		Temp08 = 0xFF;	//Ĭ�ϲ�������
			
		if( (Uart[Ch].Buf[8] >= 0x11 && Uart[Ch].Buf[8] <= 0x13) || (Uart[Ch].Buf[8] == 0x1f) )
		{
			Temp08 = 0x00;
		}
		else if( Uart[Ch].Buf[8] == 0x1c )
		{
			Temp08 = 0x00;
		}
		
		if( Temp08 )	//��������
		{
			Uart[Ch].Buf[8] |= 0x40; //����1�ֽ�04����
		}
	}
	
	if( (Ch == CHBLE) && (progenable==0) && (Ble_Buf[3]!=0xFF) )	//����ͨ�ſ�
	{
		if( IR_EnTimer == 0 )	//������֤ʧЧ
		{
			Temp08 = 0xFF;	//Ĭ�ϲ�������
			
			if( (Uart[Ch].Buf[8] == 0x03) && ((DI07.B32 == 0x078003FF) || (DI07.B32 == 0x070003FF)) )	//������֤���󡢺�����֤����
			{	
				Temp08 = 0x00;
			}
			else if( Uart[Ch].Buf[8] == 0x11 )
			{
				switch( DI07.B32 )
				{
					case 0x04000101:	//��ǰ����
					case 0x04000102:	//��ǰʱ��
					case 0x0400010C:	//��ǰʱ��
					case 0x02010100:	//��ѹ
					case 0x0201ff00:	//��ѹ��A�ࣩ
					case 0x02020100:	//����
					case 0x0202ff00:	//������A�ࣩ
					case 0x02800001:	//���ߵ���
					case 0x02800002:	//Ƶ��
					case 0x02800003:	//һ����ƽ���й�����
					case 0x02800025:	//һ����ƽ���޹�����
					case 0x02030000:	//�й����ʣ��ܣ�
					case 0x02030100:	//�й����ʣ�A�ࣩ
					case 0x0203ff00:	//�й����ʣ����ϣ�
					case 0x02040000:	//�޹����ʣ��ܣ�
					case 0x02040100:	//�޹����ʣ�A�ࣩ
					case 0x0204ff00:	//�޹����ʣ����ϣ�
					case 0x02060000:	//�����������ܣ�
					case 0x02060100:	//����������A�ࣩ
					case 0x0206ff00:	//�������������ϣ�
					case 0x0290FF00:	//���ʼ���
					case 0x04000401:	//ͨ�ŵ�ַ--
					case 0x04000402:	//���
					case 0x0400040e:	//����
					case 0x02800086:	//��ǰ����
					case 0x000B0000:	//��ǰ�����õ���
					case 0x00D0FF00:	//��������
						Temp08 = 0x00;
						break;
						
					default: 
						if( (DI07.B08[3]==0) && (((DI07.B08[2]&0x0f)<=8)||((DI07.B08[2]>=0x15)&&(DI07.B08[2]<=0x1C))) && ((DI07.B08[1]<=Bcd_To_Hex(Feik.Num[3]))||(DI07.B08[1]==0xFF)) && (DI07.B08[0]==0) )
						{
							Temp08 = 0x00;
						}
						else if( (DI07.B08[3]==0) && (((DI07.B08[2]==0x0b)||DI07.B08[2]==0x0c)||(DI07.B08[2]==0x50)) && (DI07.B08[1]==0) && (DI07.B08[0]<=max_histroy_p) ) //��ǰ/1~24�¶��õ���
						{
							Temp08 = 0x00;
						}
						else if( (Uart[Ch].Buf[9] == 0x11)||(Uart[Ch].Buf[9] == 0x07) ) 
						{
							Temp08 = 0x00;	//У��
						}
						else if( DI07.B32 == 0x0E800009 ) 
						{
							Temp08 = 0x00;	//�˳�����У��
						}
						break;
				}
			}
			else if( Uart[Ch].Buf[8] == 0x60 )
			{
				Temp08 = 0x00;
			}
			else if( (Uart[Ch].Buf[8] == 0x12) || (Uart[Ch].Buf[8] == 0x13) || (Uart[Ch].Buf[8] == 0x1f) )
			{
				Temp08 = 0x00;
			}
			
			if( Temp08 )	//��������
			{
				if( (Uart[Ch].Buf[8] == 0x03) ) DI07.B08[3] = 0xff;//����2�ֽڴ���
				else Uart[Ch].Buf[8] |= 0x40; //����1�ֽ�04����
			}
		}
	}
	
	Successled.Timer = 5+1;	//���5s

	k = 0x00;
	OutBuf[0] = 0x00;
	switch( Uart[Ch].Buf[8] ) //cmd
	{
		case 0x03:	//��ȫ��֤
			if( (Uart[Ch].Flag&B0000_0001) ||
			((Uart[Ch].Flag&B0000_0010)&&(Byte2uInt(DI07.B08)!=0xFF018007)&&(Byte2uInt(DI07.B08)!=0xFF028007)&&(Byte2uInt(DI07.B08)!=0xFF028107)&&(Byte2uInt(DI07.B08)!=0xFF038007)) )
			{
				OutBuf[ k++ ] = 0xFF;	//Operation result.
				OutBuf[ k++ ] = 0x01;
				OutBuf[ k++ ] = 0x00;
				break;
			}
			
			//ע3������Ȩ��04����ͨ�����ĵķ�ʽ�������ݴ��䣬��Ҫ����������֤��ͬʱҪ�б�̼���ϡ�
			//ע4������Ȩ��99����ͨ������+MAC�ķ�ʽ�������ݴ��䣬����Ҫ����������֤��Ҳ����Ҫ��̼����ʹ�á�
			//ע5������Ȩ��98����ͨ������+MAC�ķ�ʽ�������ݴ��䣬����Ҫ����������֤��Ҳ����Ҫ��̼����ʹ�á�

			//--------------------------- ��ȫ��֤������Ϣ�� SERR ---------------------------------------------
			//Bit7 | Bit6       | Bit5         | Bit4           | Bit3         | Bit2          | Bit1     | Bit0     |
			//���� | ���糬�ڻ� | ��ֵ�������� | �ͻ���Ų�ƥ�� | �����֤ʧ�� | ESAM ��֤ʧ�� | �ظ���ֵ | �������� |
			//Bit15 Bit14 Bit13 Bit12 Bit11 Bit10 Bit9 Bit8
			//���� ���� ���� ���� ����������������	
			//ע 1��0 ��������Ӧ��������1 ������Ӧ��������
			//ע2���������ѳ�ֵ�����ȳ�ֵָ���г�ֵ����С1 ʱ��Ϊ������ֵ����ֵ��ɺ�����ѳ�ֵ������1����
			//�����ѳ�ֵ�����ͳ�ֵָ���г�ֵ�������ʱ���ó�ֵ����ɣ���ֵ����Ϊ�ظ���ֵ��������������
			//���⣬Ϊ��ֵ��������
			//ע3�������֤ʧ�ܺ������֤��ʱͳ��Ϊ�����֤ʧ�ܣ���Ҫ���½��������֤��

			//68H A0 �� A5 68H 03H L DIO �� DI3 C0 �� C3 N1 �� Nm CS 16H
			switch( DI07.B08[3] )
			{
				case 0x07:	//
					switch( DI07.B08[2] )
					{
						case 0x00:	//�����ָ֤��
							switch( DI07.B08[1] )
							{
								case 0x00:	//�����֤
									switch( DI07.B08[0] )
									{
//										case 0x01:	//����1, 8bytes	[18]~[25]
//										case 0x02:  //�����1, 8bytes	[26]~[33]
//										case 0x03:  //��ɢ����, 8bytes	[34]~[41]
										case 0xFF:  //�����ָ֤��: ����1+�����1+��ɢ����
											//68+���+68+03+20+FF000007+�����ߴ���+����1(8)+�����1(8)+��ɢ����(8)+CS+16
											result = Yc_Auth(Ch, OutBuf);
											if( result )
											{
												k = 0x00;
												OutBuf[ k++ ] = 0xFF;
												OutBuf[ k++ ] = result;	//�����֤ʧ��
												OutBuf[ k++ ] = 0x00;
												break;
											}
											
											Identitytimer = Calculate_Timer(0xff);//���������֤ʱЧ
											identity_prog_flag = 1;	//��λ ��ȫ��֤��̱�־
																			
											k = 13;
											break;

										default:
											break;
									}
									break;
									
								case 0x01:	//�����֤ʱЧ����
									switch( DI07.B08[0] )
									{
//										case 0x01:	//�����֤��Чʱ��(����), 2bytes, BCD
//										case 0x02:	//MAC, 4bytes
										case 0xFF:
											//68+���+68+03+0E+FF010007+�����ߴ���+2�ֽ���֤ʱЧʱ��+MAC+CS+16
											//1.��û�����ð�ȫ��֤ʱЧ����ǰ��Ĭ��Ϊ5���ӡ�
										
											//��Կ��Ϣ�ļ�1 0005 ���� �����֤+MAC
											//�����޸����04d68200+LC+��ɢ����+����+MAC��LC Ϊ��ɢ���ӣ�������MAC ���ܳ��ȣ�����1�ֽڵ�ʮ����������
											if( hangup_comm_flag )
											{
												k = 0x00;  
												OutBuf[ k++ ] = 0xFF;	//Operation result.
												OutBuf[ k++ ] = 0x00;
												OutBuf[ k++ ] = 0x01;	//Զ�̰�ȫ��֤��ס״̬λ
												break;
											}
											
											if( !identity_prog_flag )
											{		
												k = 0x00;
												OutBuf[ k++ ] = 0xFF;
												OutBuf[ k++ ] = 0x08;	//�����֤ʧ��
												OutBuf[ k++ ] = 0x00;
												break;
											}
											
											if( (Uart[Ch].Buf[18]==0x00) && (Uart[Ch].Buf[19]== 0x00) )	//��ȫ��֤ʱЧ����д��0����д��0�򷵻�ʧ�ܡ�
											{
												break;
											}
											
											if( IsMultiBcd( Uart[Ch].Buf+18, 2 ) ) break;

											result = Update_ESAM_Bin_Mac( 0x81, 0x2B, &Uart[Ch].Buf[18], 2 );
											if( result != 0x00 ) 
											{
												k = 0x00;
												OutBuf[ k++ ] = 0xFF;
												OutBuf[ k++ ] = 0x04;	//ESAM��֤ʧ��
												OutBuf[ k++ ] = 0x00;
												break;
											}
											
											result = UpdateSysPara( 0x40+24, Uart[Ch].Buf+18, 2 ); //����XRAM, E2PROM
											if( result ) break;
											
											Identitytimer = Calculate_Timer(0xff);//���������֤ʱЧ

											ProgramRecord( DI07.B08, OptID.B08 );
											
											//��ȷ��68+���+68+83+04+FF010007+CS+16
											k = 1;
											break;
											
										default:
											break;
									}
									break;
									
								case 0x02:	//�����֤ʧЧ
									switch( DI07.B08[0] )
									{
										case 0xFF:
											if( !identity_prog_flag )
											{		
												k = 0x00;
												OutBuf[ k++ ] = 0xFF;
												OutBuf[ k++ ] = 0x08;	//�����֤ʧ��
												OutBuf[ k++ ] = 0x00;
												break;
											}
											
											//�ͻ����
											result = ReadBinFile( ESAM, 0x81, 36, 6 );
											if( result != 0x00 ) break;

											Exchange( OutBuf+1, Ic_Comm_RxBuf, 6 );
											
											result = Get_Money_File(1, OutBuf+7);	//��ȡǮ���ļ�
											if( result != 0x00 ) break;
						
											//��Կ��Ϣ
											GetKey( OutBuf+15 );
										
											//�����֤ʧЧ
											Clear_Rand_Gene();
											
											k = 19;
											break;
											
										default:
											break;
									}
									break;
									
								case 0x03:	//������֤����, ������֤�ɹ���30��������Ч, �����������֤���
									switch( DI07.B08[0] )
									{
										case 0xFF:
											if( (Ch!=CHBLE) &&(progenable==0) ) break; //ֻ��������ͨ�ſ�
											if( identity_ir_flag == 0 ) break; //û�к�������
											
											//�����2����
											//������֤�ɹ���30��������Ч��
											Inverse( Uart[Ch].Buf+18, 8 );	//����2

											result = Auth_In_Out(0x82, ESAM, 0x10, Uart[Ch].Buf+18 );//��Ƭ���ⲿ��֤
											if( result )
											{
												{IR_EnTimer = 0;identity_ir_flag = 0;}
												k = 0x00;
												OutBuf[ k++ ] = 0xFF;
												OutBuf[ k++ ] = 0x04;	//ESAM��֤ʧ��
												OutBuf[ k++ ] = 0x00;
												break;
											}				
											
											IR_EnTimer = Calculate_Timer(2);
											
											k = 1;
											break;
											
										default:
											break;
									}
									break;
									
								case 0x04:	//����д��Ϣ�ļ�
								case 0x05:	//����д��Ϣ�ļ�
									//68+���+68+03+L+FF050007+�����ߴ���+�ļ����+ƫ�Ƶ�ַ+����(����)+MAC+CS+16
									if(DI07.B08[0] != 0xff) break;
									if( Uart[Ch].Buf[9] <= 15 ) break;//���ݳ��ȱ������15
										
									if( hangup_comm_flag )
									{
										k = 0x00;  
										OutBuf[ k++ ] = 0xFF;	//Operation result.
										OutBuf[ k++ ] = 0x00;
										OutBuf[ k++ ] = 0x01;	//Զ�̰�ȫ��֤��ס״̬λ
										break;
									}
									
									if( !identity_prog_flag )
									{		
										k = 0x00;
										OutBuf[ k++ ] = 0xFF;
										OutBuf[ k++ ] = 0x08;	//�����֤ʧ��
										OutBuf[ k++ ] = 0x00;
										break;
									}
																		
									result = SelectFile( ESAM, 0x00, Uart[Ch].Buf[18] );//ѡ���ļ�(���ģ�18��1A,1B,1C; ����:0B,15)
									if(result) break;
										
									result = Update_ESAM_Bin_Mac(Uart[Ch].Buf[20], Uart[Ch].Buf[19], Uart[Ch].Buf+21, Uart[Ch].Buf[9]-15 );
									if(result)
									{
										k = 0x00;
										OutBuf[ k++ ] = 0xFF;
										OutBuf[ k++ ] = 0x04;	//ESAM��֤ʧ��
										OutBuf[ k++ ] = 0x00;
										break;
									}
									
									ProgramRecord( DI07.B08, OptID.B08 );
									
									k = 1;
									break;	
									
								default:
									break;
							}
							break;
						
						case 0x03:	//��Կ��������
							if( (DI07.B08[1] != 0x01) || (DI07.B08[0] != 0xFF) )
							{
								break;
							}

							if( hangup_comm_flag )
							{
								k = 0x00;  
								OutBuf[ k++ ] = 0xFF;	//Operation result.
								OutBuf[ k++ ] = 0x00;
								OutBuf[ k++ ] = 0x01;	//Զ�̰�ȫ��֤��ס״̬λ
								break;
							}  
							
							if( !identity_prog_flag )
							{		
								k = 0x00;
								OutBuf[ k++ ] = 0xFF;
								OutBuf[ k++ ] = 0x08;	//�����֤ʧ��
								OutBuf[ k++ ] = 0x00;
								break;
							}
							
							result = UpdateEepromKey( Ch );
							if( result ) //���Ӧ����Ӧ����վӦ������Կ��װ����
							{
//								FailKey();	//������Կʧ�ܴ���
								k = 0x00;
								OutBuf[ k++ ] = 0xFF;
								OutBuf[ k++ ] = result;
								OutBuf[ k++ ] = 0x00;
							}
							else
							{
								MeterClear = 0xaa55;
								
								k = 1;
							}
							break;
							
						case 0x80:	//���ݻس�
							switch( DI07.B08[1] )
							{
								case 0x01:	//
									switch( DI07.B08[0] )
									{
										case 0xFF:	//���ݻس���ʶ, 8�ֽ�,
											//���ص�����: 8+Le+4�ֽ�, [7:0]���ݻس���ʶ; [7+Le:8]���ص�����; [8+Le+3:8+Le]MAC
						
											//���ݻس������ȡ�ļ����ķ�ʽ��
											//81,��ȡʣ����͹��������
											//�س�ʣ���04b2010C11+4 �ֽ������+04d681000A+8 �ֽڷ�ɢ���ӣ�
											//�س����������04b2030C11+4 �ֽ������+04d681040A+8 �ֽڷ�ɢ���ӡ�
											//82��85����ȡ��ӦESAM �������ļ����ݣ�
											//04b082��83��84��85��+ p2(ƫ�Ƶ�ַ)��11+4 �ֽ������1+04d683+00+LC+8 �ֽڷ�ɢ���ӡ�
											//LC ����Ҫ��ȡ���������ݣ�MAC+��ɢ���ӵ��ܳ��ȣ�����1 �ֽڵ�ʮ����������

											if( (!identity_prog_flag)&&(!progenable) )
											{		
												k = 0x00;
												OutBuf[ k++ ] = 0xFF;
												OutBuf[ k++ ] = 0x08;	//�����֤ʧ��
												OutBuf[ k++ ] = 0x00;
												break;
											}
											
											//����Ŀ¼ѡ��ESAM
											if( (Uart[Ch].Buf[25] != 0xDF) || (Uart[Ch].Buf[24] != 0x01) ) break;

//											result = SelectFile( ESAM, 0xDF, 0x01 );
//											if( result != 0x00 ) break;	//

											if( Uart[Ch].Buf[22] != 0x02 )	//��Ǯ���ļ�����������ļ�
											{
												if( Uart[Ch].Buf[18] > 200 ) break;	//645�涨��ȡ�ַ�������200��
												
												//���ͣ�04b082(83,84,86)+p2+11+S4+04D686+P2+LC+8�ֽڷ�ɢ����
												//���أ�61 XX
												//���ͣ�00C0000008
												//���أ�Data+MAC
												
												if( Uart[Ch].Buf[22] == 0x06 ) UpdataRunFile();//���������ļ�
												
												result = ReadBinWithMac( ESAM+0x10, (Uart[Ch].Buf[22]|0x80), Uart[Ch].Buf[20], Uart[Ch].Buf[18]+4 );
												if( result != 0x00 ) break;
												
												MacExchange( OutBuf+9, Ic_Comm_RxBuf, Uart[Ch].Buf[18] );
												
												k = Uart[Ch].Buf[18]+13;
												memcpy( OutBuf+1, Uart[Ch].Buf+18, 8 );
												
											}
											
											else	//��ȡʣ����͹������
											{
												//ʣ����(ESAM ��), 4bytes.
												//���������ESAM �ڣ�, 4bytes.
												result = Get_Money_File(2, OutBuf+9);
												if( result != 0x00 ) break;
	
												//����״̬��Ϣ:
												k = 25;
												memcpy( OutBuf+1, Uart[Ch].Buf+18, 8 );
											}
											break;
											
										default:
											break;
									}
									break;
									
								case 0x02:	//���ݱȶ�
									switch( DI07.B08[0] )
									{
										case 0xFF:
											if( !identity_prog_flag )
											{		
												k = 0x00;
												OutBuf[ k++ ] = 0xFF;
												OutBuf[ k++ ] = 0x08;	//�����֤ʧ��
												OutBuf[ k++ ] = 0x00;
												break;
											}
											
											//�ж�cpu���
											if( Uart[Ch].Buf[18] != 0x00 ) break;
											if( (Uart[Ch].Buf[28]==0) || (Uart[Ch].Buf[28]>4) ) break;//�ȶ����ݳ���������1--4
											
											Temp08 = Uart[Ch].Buf[28];
											Clear_Wdt();
											
											//�жϵ�ַ�Ƿ��쳣��׼������
											for( i=0; i<2; i++ )
											{
												if( i== 0 ) {Temp16.B16 = 16; Ptr = ChangeBuf;}	//�ȶ�����
												else {Temp16.B16 = 256*Temp08; Ptr = OutBuf;}	//�ȶ�����
												
												Temp32.B32 = 0;
												memcpy( Temp32.B08, Uart[Ch].Buf+20+4*i, 4);	//�ȶ�������ʼ��ַ
												Code_Flash_Char = (unsigned char ecode *)Temp32.B32;
												if( (Temp32.B32 > PROGRAMEND1) || Uart[Ch].Buf[23] || Uart[Ch].Buf[27] )
												{
													break;		//��ַ�쳣
												}
												
												if( (Temp32.B32+Temp16.B16 > (PROGRAMEND1+1)) )	//������ַ��0x80
												{
												  	memset( Ptr, 0x00, Temp16.B16);
												  	memcpy( Ptr, Code_Flash_Char, PROGRAMEND1+1-Temp32.B32 );
												   	Ptr[PROGRAMEND1+1-Temp32.B32] = 0x80;
												}
												else if( (Temp32.B32 < (PROGRAMPROZ)) && (Temp32.B32+Temp16.B16 > (PROGRAMPROZ)) )	//����������ַ��0x80
												{
												   	memset( Ptr, 0x00, Temp16.B16);
												  	memcpy( Ptr, Code_Flash_Char, PROGRAMPROZ-Temp32.B32 );
												   	Ptr[PROGRAMPROZ-Temp32.B32] = 0x80;
												}
												else
												{
													memcpy( Ptr, Code_Flash_Char, Temp16.B16 );
												}
											}
											
											if( i != 2 )
											{
												k = 0x00;
												OutBuf[ k++ ] = 0xFF;
												OutBuf[ k++ ] = 0x80;	//��ַ�쳣
												OutBuf[ k++ ] = 0x00;
												break;
											}
                									
											//��ROM����,��������
											Xor_Data( ChangeBuf, ChangeBuf+8, 8 );//�õ��ȶ�����
											result = Auth_In_Out(0xfa, ESAM, Uart[Ch].Buf[19], ChangeBuf );//�����ȶ���Կ
											if( result ) break;
											
											for( i=1; i<(4*Temp08); i++ )
											{
												Xor_Data( OutBuf, OutBuf+64*i, 64 );//�õ�data1
											}
											result = Cal_Mac_Pro(0x00, OutBuf, 64); //ESAM����data1(������Ҫ���볤��)
											if( result ) break;
											
											Exchange(OutBuf+1, Ic_Comm_RxBuf, 64);	//����ȡ��,���ؼ�������
											
											k = 65;
											OutBuf[0] = 0x00;
											break;
											
										default:
											break;
									}
									break;

								case 0x03:	//������֤����
									switch( DI07.B08[0] )
									{
										case 0xFF:	//�����1, 8�ֽ�,
											if( (Ch!=CHBLE)&&(progenable==0) ) break; //ֻ��������ͨ�ſ�
										
											//������Ϣ: ���(8)+ESAM���к�(8)+�����1����(8)+�����2(8)
											result = Clear_Rand_Gene(); //Esam Reset
											if( result != 0x00 ) break;	

											Buf[16] = 0x00;
											Buf[17] = 0x00;
											memcpy( Buf+18, Esam_Para.Meter_Id, 6 );
											Exchange( Buf+8, Uart[Ch].Buf+18, 8 );	//�����1
											result = Authorization( Buf, 8 );
											if( result ) break;
											
											//������Ϣ: ��� ESAM���к� �����1���� �����2
											Exchange( OutBuf+1, Esam_Para.Meter_Id, 6 );//���, 6bytes
											Exchange( OutBuf+7, EsamRst8B, 8 );	//ESAM���к�, 8bytes
											Exchange( OutBuf+15, Buf, 8 );	//�����1����, 8bytes
											Exchange( OutBuf+23, EsamRand, 8 );	//�����2, 8bytes
											
											identity_ir_flag = 1;	//�ú��������־

											k = 31;
											break;
											
										default:
											break;
									}
									break;									
									
								default:
									break;
							}
							break;
							
						case 0x81:	//״̬��ѯ
							switch( DI07.B08[1] )
							{
								case 0x02:
									switch( DI07.B08[0] )
									{
										case 0xFF:
											if( !identity_prog_flag )
											{		
												k = 0x00;
												OutBuf[ k++ ] = 0xFF;
												OutBuf[ k++ ] = 0x08;	//�����֤ʧ��
												OutBuf[ k++ ] = 0x00;
												break;
											}
											
											//������Ϣ: ʣ���ESAM �ڣ�+ MAC + ���������ESAM �ڣ�+ MAC + �ͻ���� + ��Կ��Ϣ
											result = Get_Money_File(2, OutBuf+1);
											if( result != 0x00 ) break;
						
											//�ͻ����,	6bytes
											result = ReadBinFile( ESAM, 0x81, 36, 6 );
											if( result != 0x00 ) break;

											Exchange( OutBuf+17, Ic_Comm_RxBuf, 6 );
						
											//��Կ��Ϣ, 4bytes.							
											GetKey( OutBuf+23 );
											
											//����״̬��Ϣ:
											k = 27;
											break;
										
										default:
											break;
									}
									break;

								default:
									break;
							}
							break;
							
						default:
							break;
					}
				
				default:
				break;
			}
			
			if( k == 0x00 )
			{
				//����68+���+68+C3+02+SERR+CS+16
				OutBuf[ k++ ] = 0xFF;	//Operation result.
				OutBuf[ k++ ] = 0x01;
				OutBuf[ k++ ] = 0x00;
			}
			break;
			
		//=====================================================================================	
		case 0x06: //�����ϱ���Ӧ����
 			if(  (Uart[Ch].Flag & B0000_0011) || //��֧��ͨ�ŵ�ַΪ�㲥��ȫAA
 				(Ch != CHZB) ||  (Uart[Ch].Buf[9] < 4) || (((ReportList[0]&B0011_1100) == 0)&&(Uart[CHZB].RptTimer == 0)) )
 			{
				Uart[Ch].Overtime_Timer = 2;
				return;
 			}
	
			Report_Response( DI07 );	//�ϱ���Ӧ����
			
			Uart[Ch].Overtime_Timer = 2;
			return;

		//====================================================================================
		case 0x14: //д�α���
			if( ((Uart[Ch].Flag & B0000_0011)==0)&&(Byte2uInt(DI07.B08) == 0x03150004)&&(Reset_Rep_Timer) )//��λ�����ϱ�״̬��
 			{
 				if( Uart[Ch].Buf[9] != 24 ) break;
 				
 				//�����ϱ�״̬��
				if( (Uart[Ch].Buf[22+2]&B1000_0000)==0 ) Uart[Ch].Buf[22+2] |= B1000_0000;//������ʱ���ô�A�����
				if( (Uart[Ch].Buf[22+8]&B0010_0000)==0 ) Uart[Ch].Buf[22+2] &= B0111_1111;
				if( (Uart[Ch].Buf[22+2]&B0000_0100)==0 ) Uart[Ch].Buf[22+2] |= B0000_0100;//�͵�ѹ��ʱ���ô�A��Ƿѹ
				if( (Uart[Ch].Buf[22+3]&B0010_0000)==0 ) Uart[Ch].Buf[22+2] &= ~B0000_0100;
				if( (Uart[Ch].Buf[22+2]&B0000_0010)==0 ) Uart[Ch].Buf[22+2] |= B0000_0010;//�ߵ�ѹ��ʱ���ô�A���ѹ
				if( (Uart[Ch].Buf[22+3]&B0001_0000)==0 ) Uart[Ch].Buf[22+2] &= ~B0000_0010;
 				
 				for( i=0,n=0; i<5; i++,n++ )
				{
					Temp08 = (Report_Data[i]^Report_Data2[i]);
					if( Temp08 && ((Temp08&Uart[Ch].Buf[22+n]) != Temp08) )  break;//����30min���µ��ϱ�,����ͨѶ��λ�����ϱ�	
					if( i==2 ) n = 9;
				}
				if( i < 5 )
				{
					k = 2;
 					OutBuf[0] = 0xFF;	//Operation result.
 					OutBuf[1] = 0x04;	//Error: bit2�������/δ��Ȩ
					break;//����30min���µ��ϱ�,����ͨѶ��λ�����ϱ�
				}
 				
 				for( i=0,n=0; i<5; i++,n++ )
				{
					Report_Data[i] &= Uart[Ch].Buf[22+n];//��λ�ϱ�״̬��
					if( i==2 ) n = 9;
					
					Clr_Reportnum(i);	//�����ϱ���������
					Reset_Rep_Timer = 0;
				}
 				k = 1;
				break;
 			}
 			if( ((Uart[Ch].Flag & B0000_0011)==0) &&(Byte2uInt(DI07.B08) == 0x0f040004)&&(Uart[Ch].Buf[14] == 0x03)&&(Veri_Psw( Uart[Ch].Buf+14 )==0) )//���ܱ�λ����Ϣ
 			{
 				Temp16.B08[0] = ee_meterpos_page;//���ܱ�λ����Ϣ
				Temp16.B08[1] = ee_meterpos_inpage;
				Temp08 = 11;
										
				if( Uart[Ch].Buf[9] != (Temp08+12) ) break;//���ݳ��ȴ���
				I2C_Write_Eeprom( Temp16.B08[0], Temp16.B08[1], Uart[Ch].Buf+22, Temp08 );
				
				ProgramRecord( DI07.B08, Uart[Ch].Buf+18 );
				
				k = 1;
				break;
 			}
 			
 			if(  (Uart[Ch].Flag & B0000_0011) || //��֧��ͨ�ŵ�ַΪ�㲥��ȫAA
 				( DI07.B08[3] != 0x04 ) ||	//�û��Բ�֧��д��������������
 				( Uart[Ch].Buf[14] == 0x04 ) ||	//��֧��04������
 				((Uart[Ch].Buf[14] == 0x03 ) && (!progenable)) || //03������̽�ֹ
 				((Uart[Ch].Buf[14] != 0x03 ) && (hangup_comm_flag || (!identity_prog_flag))) )	//98��99�������ù��ܹ���, ��ȫ��֤ʧЧ
 			{
 				k = 2;
 				OutBuf[0] = 0xFF;	//Operation result.
 				OutBuf[1] = 0x04;	//Error: bit2�������/δ��Ȩ
 				break;
 			}
			
			if( Uart[Ch].Buf[9] <= 12 ) break;//���ݳ��ȱ������12

			memcpy( OptID.B08, Uart[Ch].Buf+18 ,4 );

			Auth = Uart[Ch].Buf[14];
			switch( Auth ) //����Ȩ��
			{
				case KEYTYPE2:
				
					//ͨ������+MAC�ķ�ʽ�������ݴ��䣬����Ҫ����������֤��Ҳ����Ҫ��̼����ʹ�á�
					//68+���+68+14+L+DI0-DI3+99(98)000000+�����ߴ���+��������+MAC����MAC�Ĳ������ģ�+CS+16
					//��MACдESAM:		04D682(83,84)+P2+LC+����+MAC
					//���뵽ESAM�Ĳ��������ļ������ܣ��ļ���=DI07.B08[2]%5;
					//������д��ESAM: 	04D689(90,91,92)+00+14+����(��MAC)
					if( Uart[Ch].Buf[9] <= 16 ) break;//���ݳ��ȱ������16

					Temp08 = Hex_To_Bcd(88+(DI07.B08[2]%5));
					result = Decrypt( Ch, Temp08, 0x02 );
					if( result )
					{
						k = 0x00; 
						OutBuf[ k++ ] = 0xFF;
						OutBuf[ k++ ] = 0x04;
						break;
					}
					
					//Ic_Comm_RxBuf[0]:���ݳ���; [1]~[4]:���ݱ�ʶ; [5]~[n]:
					//�ȶ����������ݱ�ʶ
					for( i=0; i<4; i++ )
					{
						if( Ic_Comm_RxBuf[4-i] != DI07.B08[i] ) break;
					}
					
					if( i < 4 ) break;
				
					//�޳����ݳ��Ⱥ�DI������UART.Buf��.
					Uart[Ch].Buf[9] = 8+Ic_Comm_RxBuf[0];	//
					
					Exchange( Uart[Ch].Buf+22, Ic_Comm_RxBuf+5, Ic_Comm_RxBuf[0]-4 );
					
				case 0x03:	//������չ����
					switch( DI07.B08[2] )
					{
						case 0x00:
							switch( DI07.B08[1] )
							{
								case 0x01:
									switch( DI07.B08[0] )
									{
										case 0x01:	//���ڼ�����(����0����������)	YYMMDDWW  	4	����������	
										case 0x02:	//ʱ��                          hhmmss    	3	ʱ����      
										case 0x0C:	//���ڡ�����(����0����������)��ʱ��	YYMMDDWWhhmmss	7 ����������ʱ����
											if( DI07.B08[0] == 0x01 )
											{
												Temp16.B08[0] = 3;
												Temp16.B08[1] = 4;
											}
											else if( DI07.B08[0] == 0x02 )
											{
												Temp16.B08[0] = 0;
												Temp16.B08[1] = 3;
											}
											else
											{
												Temp16.B08[0] = 0;
												Temp16.B08[1] = 7;
											}
																									
											result = CommSetRtc( Ch, Temp16.B08[0], Temp16.B08[1] );
											if( result ) break;

											k = 1;
											break;
	
//										case 0x05:	//У��������                  XXXX      	2	����        
//											break;

										case 0x0A:	//���׽���ʱ���л�ʱ��		YYMMDDhhmm 	5	������ʱ��
										case 0x06:	//����ʱ�����л�ʱ��            YYMMDDhhmm	5	������ʱ��
										case 0x07:	//������ʱ���л�ʱ��            YYMMDDhhmm	5	������ʱ��
											//����ʱ�����л�ʱ�䣨5����������ʱ�α��л�ʱ�䣨5�������׷��ʵ���л�ʱ�䣨5�������׽����л�ʱ�䣨5����crc��2��
											Temp08 = JudgeSwitch( Uart[Ch].Buf+22, 0 );
											if( Temp08==1 ) break;
												
											if( DI07.B08[0] == 0x0A ) result = UpdateSysPara( 0xC0+5*2, Uart[Ch].Buf+22, 5 );
											else result = UpdateSysPara( 0xC0+5*(DI07.B08[0]-6), Uart[Ch].Buf+22, 5 );
											if( result ) break;
											
											if( (Temp08==3)&&(DI07.B08[0]<=0x07) ) JudgeSwitch2(DI07.B08[0]-6);//��ת�����ֽ�,������ʱ��ͽ���Լ������
											
											k = 1;
											break;
											
										default:
											Err_DI = 1;	//���ݱ�ʶ��
											break;
									}
									break;
									
								case 0x02:
									//��ʱ������1������ʱ�α�����1������ʱ���� ��1������������1����������������1��+г������������1��+��������1������Կ����1����crc��2��
									Temp32.B08[0] = 0x00;	//��Сֵ
									Temp32.B08[1] = 0x00;	//���ֵ
									Temp32.B08[2] = 0x00;	//����������
									switch( DI07.B08[0] )
									{
										case 0x01:	//��ʱ����p��14            	NN      1	��
											Temp32.B08[0] = 1;			//��Сֵ
											Temp32.B08[1] = MAXREGION;	//���ֵ
											Temp32.B08[2] = 0x10;		//����������: ��ʱ������(Bit4)
											break;

										case 0x02:	//��ʱ�α���q��8           	NN      1	��	
											Temp32.B08[0] = 1;			//��Сֵ
											Temp32.B08[1] = MAXSIDUANTB;//���ֵ
											break;

										case 0x03:	//��ʱ����(ÿ���л���)m��14	NN      1	��
											Temp32.B08[0] = 1;			//��Сֵ
											Temp32.B08[1] = MAXSIDUAN;	//���ֵ
											Temp32.B08[2] = 0x20;		//����������: ��ʱ������(Bit5)
											break;

										case 0x04:	//������k��63              	NN      1	��	
											Temp32.B08[1] = max_feilvcount;		//���ֵ
											Temp32.B08[2] = 0x40;		//����������: ��������(Bit6)
											break;

										case 0x05:	//����������n��254         	NNNN	2	��
											if( Uart[Ch].Buf[23] ) break;
											Temp32.B08[1] = MAXHOLIDAY;	//���ֵ
											break;
//
//										case 0x06:	//г����������             	NN  	1	��	
//											break;

										case 0x07:	//������			NN	1	��
											Temp32.B08[1] = 6;			//���ֵ
											RefreshPrice();
											break;
											
										case 0x08:	//��Կ������			HH 	1	��
											Temp32.B08[1] = MAX_PSW_NUM;	//���ֵ
											break;
										
										default:
											Err_DI = 1;	//���ݱ�ʶ��
											break;	
									}
									
									if( Temp32.B08[1] == 0x00 ) break;	//����ʧ��

									if( DI07.B08[0] != 0x08 )
									{
										if( IsBCD(Uart[Ch].Buf[22]) ) break;
										Temp08 = Bcd_To_Hex( Uart[Ch].Buf[22] );
									}
									else Temp08 = Uart[Ch].Buf[22];		//��Կ��������Ϊhex��

									if( (Temp08>=Temp32.B08[0]) && (Temp08 <= Temp32.B08[1]) )
									{
										ReadE2WithBackup( ee_feik_number_page, ee_feiknumber_inpage, Buf, ee_feiknumber_lenth );
										Buf[DI07.B08[0]-1] = Uart[Ch].Buf[22];
										result = WriteE2WithBackup( ee_feik_number_page, ee_feiknumber_inpage, Buf, ee_feiknumber_lenth );
										if( result != 0x00 ) break; //error
										
										run_timezone_flag = 1;
										Tariff.Crc16.B08[0] += 1;
										Feik.Crc16.B08[0] += 1;
									
										if( DI07.B08[0] == 8 )
										{
											Feik.Num[7] = Uart[Ch].Buf[22];
											GetKeyStatus();
										}

										k = 1;
									}
									else if( Temp32.B08[2] && (Temp08 > Temp32.B08[1]) )
									{
										k = 2;
										OutBuf[0] = 0xFF;
										OutBuf[1] = Temp32.B08[2]; 	//������Ϣ��ERR
									}
									break;
									
								case 0x03:	  
									//ѭ������(1)��ѭ��ʱ��(1)������С��λ��(1)������λ��(1)����������(1)��������(1)+ ��բ��ʱʱ��(2)��crc(2)
									Temp32.B08[0] = 0x00;	//��Сֵ
									Temp32.B08[1] = 0x00;	//���ֵ
									switch( DI07.B08[0] )
									{
										case 0x01:	//�Զ�ѭ����ʾ����            	NN      1   ��
										case 0x05:	//����ѭ����ʾ����            	NN      1   ��  	
											Temp32.B08[0] = 1;	//��Сֵ
											Temp32.B08[1] = SCREENNUM;	//���ֵ
											break;
											
										case 0x02:	//ÿ����ʾʱ��                	NN      1   ��
											Temp32.B08[0] = 5;	//��Сֵ
											Temp32.B08[1] = 20;	//���ֵ
											break;
                                	
										case 0x03:	//��ʾ����С��λ��            	NN      1   λ  
											Temp32.B08[1] = 4;	//���ֵ
											break;
                                	
										case 0x04:	//��ʾ���ʣ����������С��λ��	NN      1   λ  
											Temp32.B08[1] = 4;	//���ֵ
											break;
										
										case 0x08:	//�ϵ�ȫ��ʱ��	NN	1	λ
											Temp32.B08[0] = 5;	//��Сֵ
											Temp32.B08[1] = 30;	//���ֵ
											break;
											
										default:
											Err_DI = 1;	//���ݱ�ʶ��
											break;
									}
									
									if( Temp32.B08[1] == 0x00 ) break;

									if( IsBCD(Uart[Ch].Buf[22]) ) break;
									Temp08 = Bcd_To_Hex( Uart[Ch].Buf[22] );
									
									if( (Temp08 >= Temp32.B08[0]) && (Temp08 <= Temp32.B08[1]) )
									{
										result = UpdateSysPara( DI07.B08[0]-1, &Temp08, 1 );
										if( result != 0x00 ) break;
	                                		                                	
										k = 1;
									}
									break;

								case 0x04:	  
									switch( DI07.B08[0] )
									{
										case 0x01:	//ͨ�ŵ�ַ                     	NNNNNNNNNNNN	6
											memset( Buf, 0x99, 6 );
											if( Cmp_Data( Buf, Uart[Ch].Buf+22, 6 ) ==3 ) break;	//��ֹ����ȫ9
											if( IsMultiBcd( Uart[Ch].Buf+22, 6 ) )	break;
											
											Exchange( Buf, Uart[Ch].Buf+22, 6 );
																						
											result = WriteE2WithBackup( ee_commaddr_page, ee_commaddr_inpage, Buf, ee_commaddr_lenth );
											if( result != 0x00 ) break;
												
											if( Cmp_Data(Comm_Addr.Comm_Id, Buf, 6) != 3 ) Ble_Rst_Judge(Ch);
											
											memcpy( Comm_Addr.Comm_Id, Buf, 8 );
	
											k = 1;
											break;

										case 0x0B:  	//����ͺţ�ASCII �룩         XX��XX      	10 	
										case 0x0C:	//�������ڣ�ASCII �룩          XX��XX      	10 	
											if( Auth != 3 )
											{
												k = 2;
												OutBuf[0] = 0xFF; //���
												OutBuf[1] = 0x04; //Error: bit4�������/δ��Ȩ
												break;
											}
										case 0x03:	//�ʲ�������루ASCII �룩     	NN��NN      	32
										case 0x0F:	//���ܱ�λ����Ϣ				11
											if(DI07.B08[0] == 0x0c) 
											{
												Temp16.B08[0] = ee_meterdate_page;//��������
												Temp16.B08[1] = ee_meterdate_inpage;
												Temp08 = 10;
											}
											else if(DI07.B08[0] == 0x0B)
											{
												Temp16.B08[0] = ee_matertype_page; //����ͺ�
												Temp16.B08[1] = ee_matertype_inpage;
												Temp08 = ee_matertype_lenth;
											}
											else if(DI07.B08[0] == 0x03) 
											{
												Temp16.B08[0] = ee_zichannum_page;//�ʲ�������
												Temp16.B08[1] = ee_zichannum_inpage;
												Temp08 = 32;
											}
											else
											{
												Temp16.B08[0] = ee_meterpos_page;//���ܱ�λ����Ϣ
												Temp16.B08[1] = ee_meterpos_inpage;
												Temp08 = 11;
												
												if( Auth == KEYTYPE2 )
												{
													Inverse( Uart[Ch].Buf+22, 11 );
													Inverse( Uart[Ch].Buf+22+0, 4 );	//XXXX.XXXX	4	����
													Inverse( Uart[Ch].Buf+22+4, 4 );	//XXXX.XXXX	4	γ��
													Inverse( Uart[Ch].Buf+22+8, 3 );	//XXXX.XX	3	�߶�
												}
											}
											if( Uart[Ch].Buf[9] != (Temp08+12) ) break;//���ݳ��ȴ���
											I2C_Write_Eeprom( Temp16.B08[0], Temp16.B08[1], Uart[Ch].Buf+22, Temp08 );
											k = 1;
											break;
										
										default:
											Err_DI = 1;	//���ݱ�ʶ��
											break;                                      		
									}
									break;

								case 0x06:	  
									switch( DI07.B08[0] )
									{
										case 0x01:  //�й���Ϸ�ʽ������  	NN	1
											//�����������֣�5�����й���Ϸ�ʽ������1(1)����������ģʽ��(6)���������������1(1) +�ϱ�ģʽ��(6)+crc��2��
											i = Mode.Comp_B;	//�ݴ���ǰ����
											
											result = UpdateSysPara( 0x80+1, Uart[Ch].Buf+22, 1 );
											if( result != 0x00 ) break;
												
											//--------- �й���Ϸ�ʽ��� ------------
											memcpy( Eeprom.Buffer+6, OptID.B08, 4 );	//�����ߴ���(4)
											Eeprom.Buffer[10] = i;		//���ǰ���õ�����(1)
											Event_Record( ee_combn_inpage );
											
											k = 1;
											break;
											
										case 0x02:  //�޹���Ϸ�ʽ1 ������  NN	1	
											i = Mode.Rpcomp[0];	//�ݴ���ǰ����
											
											result = UpdateSysPara( 0x80+28, Uart[Ch].Buf+22, 1 );
											if( result != 0x00 ) break;
												
											//--------- �й���Ϸ�ʽ��� ------------
											memcpy( Eeprom.Buffer+6, OptID.B08, 4 );	//�����ߴ���(4)
											Eeprom.Buffer[10] = i;		//���ǰ���õ�����(1)
											Event_Record( ee_rp1combn_inpage );
											
											k = 1;
											break;
											
										case 0x03:  //�޹���Ϸ�ʽ2 ������  NN	1	
											i = Mode.Rpcomp[1];	//�ݴ���ǰ����
											
											result = UpdateSysPara( 0x80+29, Uart[Ch].Buf+22, 1 );
											if( result != 0x00 ) break;
												
											//--------- �й���Ϸ�ʽ��� ------------
											memcpy( Eeprom.Buffer+6, OptID.B08, 4 );	//�����ߴ���(4)
											Eeprom.Buffer[10] = i;		//���ǰ���õ�����(1)
											Event_Record( ee_rp2combn_inpage );
											
											k = 1;
											break;
											
										default:
											Err_DI = 1;	//���ݱ�ʶ��
											break;
									}
									break;
									
								case 0x07:	  
									switch( DI07.B08[0] )
									{
										case 0x01:	//�����ͺ����ڲ�����������	NN  1
//										case 0x02:	//�Ӵ�ʽ�����ڲ�����������    NN  1
										case 0x03:	//ͨ�ſ�1 ������������          NN  1
//										case 0x04:	//ͨ�ſ�2 ������������          NN  1
										case 0x05:	//ͨ�ſ�3 ������������          NN  1
											Temp08 = Set_Comm_Rate( DI07.B08[0], Uart[Ch].Buf[22] );
											if( Temp08 )
											{
												k = 2;
												OutBuf[0] = 0xff;
												OutBuf[1] = 0x08;
											}
											else
											{
												k = 1;
											}
											break;
	
										default:
											Err_DI = 1;	//���ݱ�ʶ��
											break;
									}
									break;
																		
								case 0x08:
									switch( DI07.B08[0] )
									{
										case 0x02:	//�����ղ��õ���ʱ�α��    NN	1
											if( (Uart[Ch].Buf[22] == 0x00) || (Uart[Ch].Buf[22] > MAXSIDUANTB) )	break;	//ֻ����1~8����ʱ�α��
											i = Week_Holiday.Shiduan_N;	//�ݴ���ǰ����
											
										case 0x01:	//������������		NN		1										
											result = UpdateSysPara( 0x60+DI07.B08[0]-1, Uart[Ch].Buf+22, 1 );
											if( result != 0x00 ) break;

											if( DI07.B08[0] == 0x02 )
											{
												//--------- �����ձ�� ------------
												memcpy( Eeprom.Buffer+6, OptID.B08, 4 );	//�����ߴ���(4)
												Eeprom.Buffer[10] = i;		//���ǰ���õ�����(1)
												Event_Record( ee_weekdayn_inpage );
											}
											
											k = 1;
											break;
										
										default:
											Err_DI = 1;	//���ݱ�ʶ��
											break;
									}
									break;

								case 0x09:
								case 0x19:	
									switch( DI07.B08[0] )
									{
										case 0x01:	//���ɼ�¼ģʽ��	NN	1/2													
										case 0x02:	//��ʱ��������ģʽ��	NN	1/2
										case 0x03:	//˲ʱ��������ģʽ��	NN	1/2
										case 0x04:	//Լ����������ģʽ��    NN	1/2
										case 0x05:	//���㶳������ģʽ��    NN	1/2
										case 0x06:	//�ն�������ģʽ��      NN	1/2
										case 0x07:	//�¶�������ģʽ��      NN	1/2
											//�����������֣�5�����й���Ϸ�ʽ������1(1)����������ģʽ��(6)���������������1(1) +�ϱ�ģʽ��(6)+crc��2��
											if( DI07.B08[1] == 0x09 )
											{
												if( Uart[Ch].Buf[9] != 13 ) break;//���ݳ��ȴ���
												Uart[Ch].Buf[23] = 0;
											}
											else
											{
												if( Uart[Ch].Buf[9] != 14 ) break;//���ݳ��ȴ���
											}
																						
											if( DI07.B08[0] == 0x05 )
											{
												if( Uart[Ch].Buf[22]&B1111_1100 ) break;
//												if( Uart[Ch].Buf[22]&B0110_0000 ) break;
												if( Uart[Ch].Buf[23] ) break;
											}
											if( DI07.B08[0] == 0x01 )
											{
												if( Uart[Ch].Buf[22]&B1110_0000 ) break;
												if( Uart[Ch].Buf[23]&B1111_1100 ) break;
											}
											else
											{
												if( Uart[Ch].Buf[22]&B0110_0000 ) break;
												if( Uart[Ch].Buf[23] ) break;
											}
											
											result = UpdateSysPara( 0x60+2+(DI07.B08[0]-1)*2, Uart[Ch].Buf+22, 2 );
											if( result != 0x00 ) break;
	
											k = 1;
											break;
	
										default:
											Err_DI = 1;	//���ݱ�ʶ��
											break;
									}
									break;
									
								case 0x0A:
									switch( DI07.B08[0] )
									{
										case 0x01:	//���ɼ�¼��ʼʱ��		MMDDhhmm	4
											result = JudgeClockNoWeek( 1, Uart[Ch].Buf+22, 4 );
											if( result != 0 ) break; //����
											
											result = UpdateSysPara( 9, Uart[Ch].Buf+22, 4 );
											if( result != 0x00 ) break;
											
											k = 1;
											break;
												
										case 0x02:	//��1 �ฺ�ɼ�¼���ʱ��    NNNN	2
										case 0x03:	//��2 �ฺ�ɼ�¼���ʱ��    NNNN	2
										case 0x04:	//��3 �ฺ�ɼ�¼���ʱ��    NNNN	2
										case 0x05:	//��4 �ฺ�ɼ�¼���ʱ��    NNNN	2
										case 0x06:	//��5 �ฺ�ɼ�¼���ʱ��    NNNN	2
										case 0x11:	//����й�����1~ 4���ܸ��ɼ�¼���ʱ��    NNNN	2
										case 0x12:	//����й�����5~ 8���ܸ��ɼ�¼���ʱ��    NNNN	2
//										case 0x13:	//����й�����9~12���ܸ��ɼ�¼���ʱ��    NNNN	2
											if( IsMultiBcd( Uart[Ch].Buf+22, 2 ) )	break;
											if( ((Uart[Ch].Buf[22] == 0) || (Uart[Ch].Buf[22]>0x30)) || Uart[Ch].Buf[23] ) break;
											
											if( DI07.B08[0]>=0x11 ) DI07.B08[0] -= 0x0A;
											result = UpdateSysPara( 13+2*(DI07.B08[0]-2), Uart[Ch].Buf+22, 2 );
											if( DI07.B08[0]>=0x07 ) DI07.B08[0] += 0x0A;
											if( result != 0x00 ) break;
										
											k = 1;
											break;

										default:
											Err_DI = 1;	//���ݱ�ʶ��
											break;
									}
									break;
																	
								case 0x0B:
									switch( DI07.B08[0] )
									{
										case 0x01:	//ÿ�µ�1 ������	DDhh	2	��ʱ
										case 0x02:	//ÿ�µ�2 ������    DDhh	2	��ʱ
										case 0x03:	//ÿ�µ�3 ������    DDhh	2	��ʱ
											if( (Uart[Ch].Buf[22] != 0x99) || (Uart[Ch].Buf[23] != 0x99) )
											{
												result = JudgeClockNoWeek( 2, Uart[Ch].Buf+22, 2 );
												if( result != 0 ) break; //����
	
												if( Uart[Ch].Buf[23] > 0x28 )	break;	//ֻ����1~28�յ�����ʱ��
											}
											
											ReadE2WithBackup( ee_histroyparameter_page, ee_histroyparameter_inpage, Buf, ee_histroyparameter_lenth );
											
											memcpy( ChangeBuf, Buf, ee_histroyparameter_lenth );

											Buf[2*(DI07.B08[0]-1)+0] = Uart[Ch].Buf[22];
											Buf[2*(DI07.B08[0]-1)+1] = Uart[Ch].Buf[23];

											result = WriteE2WithBackup( ee_histroyparameter_page, ee_histroyparameter_inpage, Buf, ee_histroyparameter_lenth );
											if( result != 0x00 ) break;
											
											if( (DI07.B08[0] == 0x01)	//���õ�һ������
											 && ((ChangeBuf[0]!=Uart[Ch].Buf[22]) || (ChangeBuf[1]!=Uart[Ch].Buf[23])) )//��һ�����շ����ı�
											{
												if( Price.Ladder_Mode == 0x55 )
													Freeze_Usedl(1);//�����,��ת��,�����õ���
												else
													Freeze_Usedl(2);//�½���,���õ���ת�������
												Freeze_Dl(ee_histroy_dl_page,ee_histroyf_inpage);
												
												run_price_flag = 1;
											}

											//---- �����ձ�̼�¼ ----
											memcpy( Eeprom.Buffer+6, OptID.B08, 4 );	//�����ߴ���(4)
											memcpy( Eeprom.Buffer+10, ChangeBuf, 6 );	//�����ձ��ǰÿ�µ�1~3����������(6)
											
											Event_Record( ee_jieshuann_inpage );
											
											k = 1;
											break;

										default:
											Err_DI = 1;	//���ݱ�ʶ��
											break;
									}
									break;
								
								case 0x0C:	//0����Կ~9����Կ��03�����룬04������		
									if( ((DI07.B08[0] == 0x04) || (DI07.B08[0] == 0x05)) && ((DI07.B08[0]-1) == Uart[Ch].Buf[22]) )
									{
										WriteE2WithBackup( ee_password_page, ee_password_inpage+(DI07.B08[0]-4)*6, Uart[Ch].Buf+22, ee_password_lenth );
										k = 1;
									}
									else
									{
										k = 2;
										OutBuf[0] = 0xFF; //���
										OutBuf[1] = 0x04; //Error: bit2�������/δ��Ȩ
									}		
									break;
									
								case 0x0E:
									switch( DI07.B08[0] )
									{
										case 0x03:	//��ѹ����ֵ	NNN.N	2	V
										case 0x04:	//��ѹ����ֵ	NNN.N	2	V
											if( IsMultiBcd(Uart[Ch].Buf+22, 2) ) break;	//�Ƿ�����
											
											result = UpdateSysPara( 0xA0+(DI07.B08[0]-3)*2, Uart[Ch].Buf+22, 2 );
											if( result != 0x00 ) break;
											
											k = 1;
											break;
											
										default:
											Err_DI = 1;	//���ݱ�ʶ��
											break;
									}
									break;	
								
								case 0x11:
									switch( DI07.B08[0] )
									{
										case 0x01:	//�������������1	NN	1
											//�����������֣�5�����й���Ϸ�ʽ������1(1)����������ģʽ��(6)���������������1(1) +�ϱ�ģʽ��(6)+crc��2��
											result = UpdateSysPara( 0x80+8, Uart[Ch].Buf+22, 1 );
											if( result != 0x00 ) break;
	
											k = 1;
											break;
											
										case 0x04:	//�����ϱ�ģʽ��	NNNNNNNNNNNNNNNN	8
											//�����������֣�5�����й���Ϸ�ʽ������1(1)����������ģʽ��(5)���������������1(1)���ϱ�ģʽ��(6) + crc��2��
											if( Uart[Ch].Buf[9] != 20 ) break;//���ݳ��ȴ���
											Inverse( Uart[Ch].Buf+22, 8 );	//���ݵ���(���ֽ���ǰ��ɸ��ֽ���ǰ,��������ֱ�ɵ��ֽ���ǰ)
											result = UpdateSysPara( 0x80+9, Uart[Ch].Buf+22, 8 );
											if( result != 0x00 ) break;
	
											k = 1;
											break;
											
										default:
											Err_DI = 1;	//���ݱ�ʶ��
											break;
									}
									break;
																
								case 0x12:
									I2C_Read_Eeprom44( ee_freezeparameter_page, Buf, ee_freezeparameter_lenth );
									
									Temp08 = 0x00;	//Ĭ��ʧ��
									switch( DI07.B08[0] )
									{
										case 0x01:	//���㶳����ʼʱ��	YYMMDDhhmm	5	������ʱ�֣�Ĭ����ֵΪȫ�㣬����ֵӦ������ֵ����ֵ��
//											if( (Uart[Ch].Buf[22]!=0x00) && (Uart[Ch].Buf[22]!=0x30) )
//											{
//												break;	//����
//											}

											result = JudgeClockNoWeek( 1, &Uart[Ch].Buf[22], 5 );
											if( result != 0 ) break; //����
																						
											Exchange( Buf, Uart[Ch].Buf+22, 5 );
											Temp08 = 0x01;
											break;
											
										case 0x02:  //���㶳��ʱ����	NN          1	����, ����Ϊ30��60���ӣ�Ĭ��Ϊ60���ӡ�
											if( (Uart[Ch].Buf[22]!=0x30)&&(Uart[Ch].Buf[22]!=0x60) ) break;
											
											Buf[5] = Uart[Ch].Buf[22];
											Temp08 = 0x01;
											break;
											
										case 0x03:  //�ն���ʱ��      	hhmm        2	ʱ��      
											result = JudgeClockNoWeek( 1, &Uart[Ch].Buf[22], 2 );
											if( result != 0 ) break; //����
											
											Wr_Pretime_Dayfreeze();	//д��һ���ն���ʱ��
											
											Buf[6] = Uart[Ch].Buf[23];
											Buf[7] = Uart[Ch].Buf[22];
											Temp08 = 0x01;
											break;
											
										default:
											Err_DI = 1;	//���ݱ�ʶ��
											break;
									}

									if( Temp08 )
									{
										result = I2C_Write_Eeprom44( ee_freezeparameter_page, Buf, ee_freezeparameter_lenth );
										if( result != 0x00 ) break;
										
										k = 1;
									}
									break;
									
//								case 0x13:	
//									switch( DI07.B08[0] )
//									{
//										case 0x01:	//����ͨ�����߼��ź�ǿ��ָʾ	NN	1	
//											break;
//											
//										default:
//											break;
//									}
//									break;
									
								case 0x14:
									switch( DI07.B08[0] )
									{
										case 0x01:	//��բ��ʱʱ�䣨NNNN Ϊ��բǰ�澯ʱ�䣩	NNNN	2
										case 0x02:	//�̵�����բ���Ƶ�������ֵ	XXX.XXX	3
										case 0x03:	//�̵�����ʱ��բʱ��	XXXX	2
//										case 0x04:	//������֤ʱЧ	XXXX	1
										case 0x05:	//�ϱ���λʱ��	XXXX	1
										case 0x06:	//������֤ʱЧ  XX 1
											if( DI07.B08[0] == 0x02 )
											{
												Temp16.B08[0] = 0;	//ƫ�Ƶ�ַ0
												Temp16.B08[1] = 3;	//�ֽ���
											}
											else if( DI07.B08[0] >= 0x04 )
											{
												Temp16.B08[0] = (DI07.B08[0]&1)+0x07;//ƫ�Ƶ�ַ7,8
												Temp16.B08[1] = 1;
												if( Uart[Ch].Buf[22] == 0 ) break;
											}
											else
											{
												Temp16.B08[0] = DI07.B08[0]+2;//ƫ�Ƶ�ַ3,5	
												Temp16.B08[1] = 2;	
//												if( (DI07.B08[0] == 0x03) && (Uart[Ch].Buf[22] == 0) && (Uart[Ch].Buf[23] == 0) ) break;
											}
											
											if( IsMultiBcd( Uart[Ch].Buf+22, Temp16.B08[1] ) ) break;
											
											result = UpdateSysPara( 0x80+17+Temp16.B08[0], Uart[Ch].Buf+22, Temp16.B08[1] );
											if( result != 0x00 ) break;						
											
											if( Opendelaytimer && (DI07.B08[0]==0x01) ) Opendelaytimer = Calculate_Timer(0)+2;
//											if( Relay_Mode != 0x55 )//���ü̵���
											{
												if( CurrentTimer && (DI07.B08[0]==0x03) ) CurrentTimer = Calculate_Timer(1);
											}
											if( IR_EnTimer && ((DI07.B08[0]==0x04)||(DI07.B08[0]==0x06)) ) IR_EnTimer = Calculate_Timer(2);
											if( Reset_Rep_Timer && (DI07.B08[0]==0x05) ) Reset_Rep_Timer = Calculate_Timer(3);
											
											k = 1;
											break;		
											
										case 0x08:	//�����ӻ�MAC��ַ��HEX��ʽ��		
											if( Auth == KEYTYPE2 )
											{
												Inverse( Uart[Ch].Buf+22, 18 );
												Inverse( Uart[Ch].Buf+22, 6 );
												Inverse( Uart[Ch].Buf+28, 6 );
												Inverse( Uart[Ch].Buf+34, 6 );
											}
											I2C_Write_Eeprom(ee_bleslamac_page, ee_bleslamac_inpage, Uart[Ch].Buf+22, ee_bleslamac_lenth);
											
//											Ble_Rst_Judge(Ch);
											
											k = 1;
											break;
											
										case 0x09:	//��������
											if( Auth == KEYTYPE2 )
											{
												Inverse( Uart[Ch].Buf+22, Uart[Ch].Buf[9]-12 );
												for(i=0; i<5; i++)
												{
													Inverse( Uart[Ch].Buf+25+2*i, 2 );
												}
											}
												
											I2C_Write_Eeprom(ee_blerefer_page, ee_blerefer_inpage, Uart[Ch].Buf+22, ee_blerefer_lenth);
											
											if( (Uart[Ch].Buf[23]<=3) || (Uart[Ch].Buf[23]==6) || (Uart[Ch].Buf[23]==255) )
											{
												if( Uart[Ch].Buf[23] == 255 ) Uart[Ch].Buf[23] = 0;
												Outputtype = Uart[Ch].Buf[23];
												reg_veri_flag = 1;
											}
											else break;

											k = 1;
											break;	
											
										case 0x0A:	//�����㲥ʱ�� 40~100ms BCD
											if( IsMultiBcd(Uart[Ch].Buf+22, 2) ) break;	//�Ƿ�����
											Bcd2Hex_SS(Uart[Ch].Buf+22, Uart[Ch].Buf+24, 2);
											if( (Uart[Ch].Buf[24] < 40) || (Uart[Ch].Buf[24] > 100) || Uart[Ch].Buf[25] ) break;
											I2C_Write_Eeprom(ee_blerefer_page, ee_blegbtime_inpage, Uart[Ch].Buf+22, ee_blegbtime_lenth);
											
											k = 1;
											break;	
											
										case 0xee:	//�̵�����բ����ʽ	XX	1
											result = UpdateSysPara( 0x80+26, Uart[Ch].Buf+22, 1 );
											if( result != 0x00 ) break;

											k = 1;
											break;	
										
										default:
											Err_DI = 1;	//���ݱ�ʶ��
											break;
									}
									break;
								case 0x17:
									switch( DI07.B08[0] )
									{
										case 0x01:	//�۵緽	NNNNNNNN	4
										case 0x02:	//���緽	NNNNNNNN	4
										case 0x03:	//�õ�����		NNNNNNNNNNNNNNNN	8
										case 0x04:	//��Ӧ����ʱ�ε��	NNNNNNNNNNNNNNNN	8
										case 0xFF:	//����
											if( DI07.B08[0] == 0x01 || DI07.B08[0] == 0x02 )
											{
												Temp16.B08[0] = 0+(DI07.B08[0]-1)*4;	//ƫ�Ƶ�ַ
												Temp16.B08[1] = 4;	//�ֽ���
											}
											else if( DI07.B08[0] == 0x03 || DI07.B08[0] == 0x04 )
											{
												Temp16.B08[0] = 8+(DI07.B08[0]-3)*8;
												Temp16.B08[1] = 8;
											}
											else
											{
												Temp16.B08[0] = 0;
												Temp16.B08[1] = ee_buymessage_lenth;
												
												if( Auth == KEYTYPE2 )
												{
													Inverse( Uart[Ch].Buf+22, ee_buymessage_lenth );
													Inverse( Uart[Ch].Buf+22+0, 4 );
													Inverse( Uart[Ch].Buf+22+4, 4 );
													Inverse( Uart[Ch].Buf+22+8, 8 );
													Inverse( Uart[Ch].Buf+22+16, 8 );
												}
											}
											
											I2C_Write_Eeprom( ee_buymessage_page, ee_buymessage_inpage+Temp16.B08[0], Uart[Ch].Buf+22, Temp16.B08[1] );
											k = 1;
											break;
										default:
											Err_DI = 1;	//���ݱ�ʶ��
											break;
									}
									break;

								default:
									Err_DI = 1;	//���ݱ�ʶ��
									break;
							}
							break;
							
						case 0x07:	//��ǰ�׽���ʱ���������׽���ʱ����
//							if( !BDMODE ) { Err_DI = 1;	break; }
						case 0x01:	//��һ��ʱ�������ʱ�α�����
						case 0x02:	//�ڶ���ʱ�������ʱ�α�����
							//ʱ������ʱ����1~14�������裬ʱ��������14��ʱ�������һ�����㡣
							//��ʱ�α�ĸ�����1~8�������裬û�в��㹦�ܡ�
							//��ʱ�α���ʱ����1~14���������裬
							//�·�����ʱ�����ж��趨��ʱ������ʱ������ֻ�����а����˶��ٸ���
							//��ʱ������1������ʱ�α�����1������ʱ���� ��1������������1����������������1��+г������������1��+��������1������Կ����1����crc��2��
							if( (DI07.B08[1]!=0x00) || (DI07.B08[0]>MAXSIDUANTB) || 
							   ((DI07.B08[2]==0x07) && (DI07.B08[0]>0x01)) )//����ʱ����ǰ�ͱ����׾���������
							{
								Err_DI = 1;	//���ݱ�ʶ��
								break;
							}

							if( DI07.B08[2] == 0x07 ) DI07.B08[0] += 0x09;  //�������������������
							if( DI07.B08[0] == 0x00 )	//��һ��ʱ��������, ��1~14ʱ����ʼ���ڼ���ʱ�α��(14*3), MMDDNN
							{
								Temp32.B08[0] = 3;	//ʱ����ʼλ��
								Temp32.B08[1] = MAXSIDUANTB;	//��ʱ�α�����ֵ
								Temp32.B08[2] = MAXREGION;	//���ʱ����Ŀ
								Temp32.B08[3] = ee_shiqu_lenth;
							}
							else if( DI07.B08[0] <= 0x08 )	//��������8����ʱ�α�, ÿ����ʱ�α�̶�Ϊ14��ʱ��
							{
								Temp32.B08[0] = 1;	//ʱ����ʼλ��
								Temp32.B08[1] = max_feilvcount;	//���ʺ���ֵ
								Temp32.B08[2] = MAXSIDUAN;	//�����ʱ����Ŀ
								Temp32.B08[3] = ee_shiduantable_lenth;
							}
							else
							{
								Temp32.B08[0] = 3;	//ʱ����ʼλ��
								Temp32.B08[1] = 4;	//���ݱ�������ֵ
								Temp32.B08[2] = 4;	//������ʱ����Ŀ
								Temp32.B08[3] = ee_jtshiqu_len;
							}
						
							//ʱ��ʱ��˳���ж�: Ҫ����ʱ����������
							Temp08 = (Uart[Ch].Buf[9]-12)/3;	//
							if( ((Uart[Ch].Buf[9]-12)%3) || (Temp08==0) ) break; //���ݳ��ȴ���, �˳� 
								
							if( Temp08 > Temp32.B08[2] )
							{
								k = 2;
								OutBuf[0] = 0xFF;
								if( DI07.B08[0]==0 ) OutBuf[1] = 0x10;//ʱ������(Bit4)
								else if( DI07.B08[0] <= 0x08 ) OutBuf[1] = 0x20;//ʱ������(Bit5)
								else OutBuf[1] = 0x01;
								break;
							}							
							
							if( Auth == KEYTYPE2 )
							{
								Inverse( Uart[Ch].Buf+22, (Uart[Ch].Buf[9]-12) );
								
								for( i=0; i<Temp08; i++ )
								{
									Inverse( Uart[Ch].Buf+22+3*i, 3 );
								}
							}

							memcpy( Buf, Uart[Ch].Buf+22, Uart[Ch].Buf[9]-12 );
							Sequence( Buf, Temp08 );

							//ʱ��˳���ж�: Ҫ����ʱ����������
							n = Temp08*3;	//Ϊ���ж���ʱ��15���Ӽ������, ��"��1��+�̶�ֵ"����"���1��"�ĺ��档
							Buf[n+0] = Buf[0];	//��ʱ�α�� or ���ʺ�
							Buf[n+1] = Buf[1];	//�� or ��
							Buf[n+2] = Hex_To_Bcd(Bcd_To_Hex(Buf[2])+24);	//�� or ʱ
							
							for( i=0, n=0; i<Temp08; i++, n+=3 ) //ʱ�����������һֱ��ͬ
							{
								if( (Buf[0+n]==0) || (Bcd_To_Hex(Buf[0+n])>Temp32.B08[1]) || (IsBCD(Buf[0+n])) )	//��ʱ�α��or���ʺ��Ƿ�Ϸ�
								{
									if( DI07.B08[0] && (DI07.B08[0]<=0x08) )
									{
										k = 2;
										OutBuf[0] = 0xFF;
										OutBuf[1] = 0x40;//��������(Bit6)
									}
									break;
								}
							
								result = JudgeClockNoWeek( Temp32.B08[0], Buf+1+n, 2 );	//minute+hour
								if( result != 0 ) break; //����
									
								result = Cmp_Bcd_Inv( Buf+1+n, Buf+4+n, 2 );
								if( result == 0x00 )	//A == B
								{
									if( Buf[3+n] != Buf[0+n] ) break;
								}
								else if( result == 0x02 ) //A < B
								{
									if( DI07.B08[0] && (DI07.B08[0]<=0x08))	//��ʱ�α�����Сʱ�μ����ӦС��15����
									{
										if( (CalcAbsMin(Buf+4+n)-CalcAbsMin(Buf+1+n)) < 15 ) break;
									}
								}
								else //A > B
								{
									break;	//��������
								}
							}
							
							if( i < Temp08 )	break;	//��������

							for( i=(Temp08); i<Temp32.B08[2]; i++ )	//���ݲ���, �����һ������
							{
								memcpy( Uart[Ch].Buf+22+3*i, Uart[Ch].Buf+22+3*(Temp08-1), 3 );
							}

							if( DI07.B08[0] <= 0x08 )
							{
								Temp16.B16 = ShiquRecord( DI07.B08, OptID.B08 );	//�¼���¼
								I2C_Write_Eeprom( Temp16.B16, 0x00, Uart[Ch].Buf+22, Temp32.B08[3] );	//��̺� ʱ����orʱ�ε�i��(42)
							}
							else
							{
								Temp16.B16 = ee_jtshiqu1_page+DI07.B08[0]-0x09;
								I2C_Write_Eeprom( Temp16.B16, ee_jtshiqu_inpage, Uart[Ch].Buf+22, Temp32.B08[3] );	//��̺� ʱ����orʱ�ε�i��(42)
							}		
			
							if( DI07.B08[2] == 0x07 ) DI07.B08[0] -= 0x09;  //�������������������
							
							run_timezone_flag = 1;
							Tariff.Crc16.B08[0] += 1;
							RefreshPrice();

							k = 1;												
							break;

						case 0x03:	//��n �����������ڼ���ʱ�α��
							switch( DI07.B08[1] ) 
							{
								case 0x00:
									if( (DI07.B08[0]>=1) && (DI07.B08[0]<=MAXHOLIDAY) )	//�������գ�1~14, YYMMDDNN, 4
									{
										if( (Uart[Ch].Buf[22]==0) || (Uart[Ch].Buf[22]>MAXSIDUANTB) ) break;	//��ʱ�α��: 1~8

										result = Judge_Clock( 4, &Uart[Ch].Buf[23], 3 ); //�ж������Ƿ�Ϸ�
										if( result != 0 ) break;
										
										Temp16.B08[0] = (DI07.B08[0]-1)/15;
										Temp16.B08[1] = ((DI07.B08[0]-1)%15)*4;
										
										result = I2C_Write_Eeprom( ee_holiday_page+Temp16.B08[0], Temp16.B08[1], Uart[Ch].Buf+22, 4 );
										if( result != 0x00 ) break;
										
										run_timezone_flag = 1;
										Tariff.Crc16.B08[0] += 1;
										
										k = 1;
									}
									else
									{
										Err_DI = 1;	//���ݱ�ʶ��
									}
									break;
									
								default:
									Err_DI = 1;	//���ݱ�ʶ��
									break;
							}
							break;

						case 0x04:
							switch( DI07.B08[1] )
							{
								case 0x01:	//�Զ�ѭ��
								case 0x02:	//����ѭ��
									//ѭ������(1)��ѭ��ʱ��(1)������С��λ��(1)������λ��(1)����������(1)��������(1)+ ��բ��ʱʱ��(2)��crc(2)
									if( Auth == KEYTYPE2 )
									{
										Temp08 = Uart[Ch].Buf[22];
										memcpy( Uart[Ch].Buf+22, Uart[Ch].Buf+23, 4);
										Uart[Ch].Buf[26] = Temp08;
									}
														
									if( (DI07.B08[0]) && (DI07.B08[0]<=SCREENNUM) )
									{
										Temp16.B16 = GetLcdNo( Uart[Ch].Buf+22 );
										if( Temp16.B16 == 0x00 ) break;	//��ʾ��Ŀ���� or ��ʾ��Ŵ�
																				
										n = (DI07.B08[1]-1)%2;
										i = (DI07.B08[0]-1)/31;
										if( i != 3 ) Temp08 = ee_displayitem_lenth;
										else Temp08 = ee_displayitem_lenth1;
										
										I2C_Read_Eeprom( ee_loop_displayitem_page+2*i+n, 0x00, Buf, Temp08 );
										Buf[((DI07.B08[0]-1)%31)*2+0] = Temp16.B08[0];
										Buf[((DI07.B08[0]-1)%31)*2+1] = Temp16.B08[1];
										result = I2C_Write_Eeprom( ee_loop_displayitem_page+2*i+n, 0x00, Buf, Temp08 );
										if( result != 0x00 ) break;
										
										Item[n].Crc16.B08[0] += 1;
										dispitem_veri_flag = 1;
										
										k = 1;
									}
									else
									{
										Err_DI = 1;	//���ݱ�ʶ��
									}
									break;
								
								default:
									Err_DI = 1;	//���ݱ�ʶ��
									break;
							}
							break;
							
						case 0x09:
							switch( DI07.B08[1] )
							{
								case 0x01:
									if( DI07.B08[0]==1 || DI07.B08[0]==2 )//ʧѹ�¼���ѹ��������/ʧѹ�¼���ѹ�ָ����� NNN.N	2	V
									{		
										if( IsMultiBcd( Uart[Ch].Buf+22, 2) )	break;
										result = UpdateSysPara( 0xA8+(DI07.B08[0]-1)*2, Uart[Ch].Buf+22, 2 );
									}
									else if( DI07.B08[0]==3 )//ʧѹ�¼�������������	NN.NNNN	3	A
									{
										if( IsMultiBcd( Uart[Ch].Buf+22, 3) ) break;
										Uart[Ch].Buf[25] = 0;
										result = UpdateSysPara( 0xA0+12, Uart[Ch].Buf+22, 4 );
									}
									else if( DI07.B08[0]==4 )//ʧѹ�¼���ʱ�ж�ʱ��	NN	1	S
									{
										if( IsMultiBcd( Uart[Ch].Buf+22, 1) || (Uart[Ch].Buf[22] < 10) ) break;
										result = UpdateSysPara( 0xA0+16, Uart[Ch].Buf+22, 1 );
									}
									else
									{
										Err_DI = 1;	//���ݱ�ʶ��
										break;
									}
										
									if( result != 0x00 ) break;
											
									k = 1;
									break;
								
								case 0x08:
									if( DI07.B08[0]==1 )//�����¼�������������	NNN.N	2	A
									{		
										if( IsMultiBcd( Uart[Ch].Buf+22, 2) )	break;
										result = UpdateSysPara( 0x60+17, Uart[Ch].Buf+22, 2 );
									}
									else if( DI07.B08[0]==2 )//�����¼��ж���ʱʱ��	NN	1	S
									{
											
										if( IsMultiBcd( Uart[Ch].Buf+22, 1) || (Uart[Ch].Buf[22] < 10) ) break;
										result = UpdateSysPara( 0x60+19, Uart[Ch].Buf+22, 1 );
									}
									else
									{
										Err_DI = 1;	//���ݱ�ʶ��
										break;
									}
										
									if( result != 0x00 ) break;
											
									k = 1;
									break;
									
								case 0x0C:
									switch( DI07.B08[0] )
									{
										case 0x01:	//�ϸ��ʵ�ѹ��������ֵ	NNN.N	2	V
										case 0x02:	//�ϸ��ʵ�ѹ��������ֵ	NNN.N	2	V
											if( IsMultiBcd(Uart[Ch].Buf+22, 2) ) break;	//�Ƿ�����
											
											result = UpdateSysPara( 0xA4+(DI07.B08[0]-1)*2, Uart[Ch].Buf+22, 2 );
											if( result != 0x00 ) break;
											
											k = 1;
											break;
											
										default:
											Err_DI = 1;	//���ݱ�ʶ��
											break;
									}
									break;
									
								case 0x12: 
									switch( DI07.B08[0] )
									{
										case 0x01:	//�͵�ѹ�¼���ѹ��������	NNN.N	2	V
											if( IsMultiBcd(Uart[Ch].Buf+22, 2) ) break;	//�Ƿ�����
											result = UpdateSysPara( 0xA0+17, Uart[Ch].Buf+22, 2 );
											if( result != 0x00 ) break;
											
											k = 1;
											break;
										
										case 0x02:	//�͵�ѹ�¼���ʱ�ж�ʱ��	NNNN	2	MIN
											if( IsMultiBcd( Uart[Ch].Buf+22, 1)  ) break;
											result = UpdateSysPara( 0xA0+19, Uart[Ch].Buf+22, 2 );
											if( result != 0x00 ) break;
											
											k = 1;
											break;
											
										default:
											Err_DI = 1;	//���ݱ�ʶ��
											break;
									}
									break;	
									
								case 0x11: 
									switch( DI07.B08[0] )
									{
										case 0x01:	//�ߵ�ѹ�¼���ѹ��������	NNN.N	2	V
											if( IsMultiBcd(Uart[Ch].Buf+22, 2) ) break;	//�Ƿ�����
											result = UpdateSysPara( 0xA0+21, Uart[Ch].Buf+22, 2 );
											if( result != 0x00 ) break;
											
											k = 1;
											break;
										
										case 0x02:	//�ߵ�ѹ�¼���ʱ�ж�ʱ��	NNNN	2	MIN
											if( IsMultiBcd( Uart[Ch].Buf+22, 1)  ) break;
											result = UpdateSysPara( 0xA0+23, Uart[Ch].Buf+22, 2 );
											if( result != 0x00 ) break;
											
											k = 1;
											break;
											
										default:
											Err_DI = 1;	//���ݱ�ʶ��
											break;
									}
									break;									
									
								case 0x3f:
									switch( DI07.B08[0] )
									{
										case 0x01:	//���ߵ�����ƽ������������	NN.NNNN	3	A
											if( IsMultiBcd(Uart[Ch].Buf+22, 3) ) break;	//�Ƿ�����
											Uart[Ch].Buf[25] = 0;
											result = UpdateSysPara( 0x60+20, Uart[Ch].Buf+22, 4 );
											if( result != 0x00 ) break;
											
											k = 1;
											break;
										
										case 0x02:	//���ߵ�����ƽ����ֵ      long-unsigned����λ��%�����㣺-2��
											if( IsMultiBcd(Uart[Ch].Buf+22, 2) ) break;	//�Ƿ�����
											result = UpdateSysPara( 0x60+24, Uart[Ch].Buf+22, 2 );
											if( result != 0x00 ) break;
											
											k = 1;
											break;
											
										case 0x03:	//���ߵ�����ƽ��ʱ�ж�ʱ��        NN	1	S
											if( IsMultiBcd( Uart[Ch].Buf+22, 1) || (Uart[Ch].Buf[22] < 10) ) break;
											result = UpdateSysPara( 0x60+26, Uart[Ch].Buf+22, 1 );
											if( result != 0x00 ) break;
											
											k = 1;
											break;
											
										default:
											Err_DI = 1;	//���ݱ�ʶ��
											break;
									}
									break;	
									
								case 0x40:	
									switch( DI07.B08[0] )
									{
										case 0x01:	//���������ж���ʱ	NN	1	S
											if( IsMultiBcd( Uart[Ch].Buf+22, 1) || (Uart[Ch].Buf[22] < 10) ) break;
											result = UpdateSysPara( 0xA0+25, Uart[Ch].Buf+22, 1 ); //����XRAM, E2PROM
											if( result ) break;
											k = 1;
											break;			
										default:
											Err_DI = 1;	//���ݱ�ʶ��
											break;
									}
									break;	
									
								case 0x43:	
									switch( DI07.B08[0] )
									{
										case 0x01:	//ͣ���¼��ж���ʱ	NN	1	S
											if( IsMultiBcd( Uart[Ch].Buf+22, 1) || (Uart[Ch].Buf[22] < 3) || (Uart[Ch].Buf[22] > 0x60) ) break;
											result = UpdateSysPara( 0x80+6, Uart[Ch].Buf+22, 1 );
											if( result != 0x00 ) break;
											
											k = 1;
											break;			
											
										default:
											Err_DI = 1;	//���ݱ�ʶ��
											break;
									}
									break;			
									
								case 0x51:	
									switch( DI07.B08[0] )
									{
										case 0x01:	//�����ϱ��ϵ�ʱ��	NN	1	MIN
											if( IsMultiBcd( Uart[Ch].Buf+22, 1) ) break;
											result = UpdateSysPara( 0x80+7, Uart[Ch].Buf+22, 1 );
											if( result != 0x00 ) break;
											
											k = 1;
											break;			
											
										default:
											Err_DI = 1;	//���ݱ�ʶ��
											break;
									}
									break;	
									
								default:
									Err_DI = 1;	//���ݱ�ʶ��
									break;
							}
							break;	
							
						case 0x80:    // :p		
							switch( DI07.B08[1] )
							{
								case 0x00:
									switch( DI07.B08[0] )
									{
										case 0x01:	//��������汾��(ASCII ��)	NN��NN	32
										case 0x02:	//����Ӳ���汾��(ASCII ��)	NN��NN	32
										case 0x03:	//���ұ���(ASCII ��)		NN��NN	32
										case 0x04:	//���������			NN��NN	8
											if( Auth != 3 )
											{
												k = 2;
												OutBuf[0] = 0xFF; //���
												OutBuf[1] = 0x04; //Error: bit4�������/δ��Ȩ
												break;
											}
											Temp08 = 32;//32�ֽ�
											if(DI07.B08[0] == 0x01)
											{
												Temp16.B08[0] = ee_softver_page;	//���������
												Temp16.B08[1] = ee_softver_inpage;
											}
											else if(DI07.B08[0] == 0x02)
											{
												Temp16.B08[0] = ee_hardver_page;	//Ӳ��������
												Temp16.B08[1] = ee_hardver_inpage;
											}
											else if(DI07.B08[0] == 0x03)
											{
												Temp16.B08[0] = ee_factorynum_page;	//���ұ��
												Temp16.B08[1] = ee_factorynum_inpage;
											}
											else
											{
												Temp16.B08[0] = ee_softbk_page; 	//���������
												Temp16.B08[1] = ee_softbk_inpage;
												Temp08 = 8;//8�ֽ�
											}
											if( Uart[Ch].Buf[9] != (Temp08+12) ) break;//���ݳ��ȴ���
											I2C_Write_Eeprom( Temp16.B08[0], Temp16.B08[1], Uart[Ch].Buf+22, Temp08 );
											k = 1;
											break;
																						
										default:
											Err_DI = 1;	//���ݱ�ʶ��
											break;
									}
									break;
									
								default:
									Err_DI = 1;	//���ݱ�ʶ��
									break;
							}
							break;		
							
						default:
							Err_DI = 1;	//���ݱ�ʶ��
							break;
					}
					break;

				case KEYTYPE1:	//ͨ������+MAC�ķ�ʽ�������ݴ��䣬����Ҫ����������֤��Ҳ����Ҫ��̼����ʹ�á�
//					if( (Byte2uInt(DI07.B08) != 0x02040004) && 
//					   (((BDMODE)&&(Byte2uInt(DI07.B08) == 0x0E040004)) || 
//					    ((!BDMODE)&&(Byte2uInt(DI07.B08) != 0x0E040004))) )//�κ�ģʽ��֧�ֱ������, �ͻ��������ģʽ
//					{
//						Err_DI = 1;	//Error: bit2�������/δ��Ȩ
//						break;
//					}

					switch( DI07.B08[3] )
					{
						case 0x04:
							switch( DI07.B08[2] )
							{
								case 0x00:
									Temp32.B08[0] = 0x00;
									Temp32.B08[3] = 0x81;	//д��ESAM���ļ���
									
									switch( DI07.B08[1])
									{
										case 0x01:
											switch( DI07.B08[0] )
											{
//												case 0x08:	//���׷��ʵ���л�ʱ��			YYMMDDhhmm	5	������ʱ��
//													//����ʱ�����л�ʱ�䣨5����������ʱ�α��л�ʱ�䣨5�������׷��ʵ���л�ʱ�䣨5�������׽����л�ʱ�䣨5����crc��2��
//													result = JudgeSwitch( Uart[Ch].Buf+22, 0 );
//													if( result==1 ) break;
//													
//													Temp32.B08[0] = 5;	//���ݳ���
//													Temp32.B08[1] = 10;	//82�ļ���ƫ����
//													Temp32.B08[2] = 0xC0+10;	//E2��ҳ��ƫ����
//													break;

												case 0x09:	//���׽����л�ʱ��		YYMMDDhhmm	5	������ʱ��
													//����ʱ�����л�ʱ�䣨5����������ʱ�α��л�ʱ�䣨5�������׷��ʵ���л�ʱ�䣨5�������׽����л�ʱ�䣨5����crc��2��
													result = JudgeSwitch( Uart[Ch].Buf+22, 0 );
													if( result==1 ) break;

													Temp32.B08[0] = 5;	//���ݳ���
													Temp32.B08[1] = 192;//84�ļ���ƫ����
													Temp32.B08[2] = 0xC0+15;	//E2��ҳ��ƫ����
													Temp32.B08[3] = 0x84;	//д��ESAM���ļ���
													break;
												
												default:
													Err_DI = 1;	//���ݱ�ʶ��
													break;
											}
											break;

										//�������1��ֵ(4)���������2��ֵ(4)+���������(6)�����(6)+�ͻ����(6)+�翨����(1)+�����֤ʱЧ(2)
										case 0x03:
											switch( DI07.B08[0] )
											{
												case 0x06:	//�������������              	NNNNNN	3       break;
													Temp32.B08[0] = 3;	//���ݳ���
													Temp32.B08[1] = 24;	//82�ļ���ƫ����
													Temp32.B08[2] = 0x40+0;	//E2��ҳ��ƫ����
													break;
																										
												case 0x07:	//��ѹ���������              	NNNNNN	3	    break;
													Temp32.B08[0] = 3;	//���ݳ���
													Temp32.B08[1] = 27;	//82�ļ���ƫ����
													Temp32.B08[2] = 0x40+3;	//E2��ҳ��ƫ����
													break;
												
												default:
													Err_DI = 1;	//���ݱ�ʶ��
													break;
											}
											break;
		
										case 0x04:
											switch( DI07.B08[0] )
											{
												case 0x02:	//���		NNNNNNNNNNNN	6
													if( Key_Status!=0 ){Err_DI = 1;break;}//��Կ��������

													Temp32.B08[0] = 6;	//���ݳ���
													Temp32.B08[1] = 30;	//82�ļ���ƫ����
													Temp32.B08[2] = 0x40+6;	//E2��ҳ��ƫ����
													break;
																										
												case 0x0E:	//�ͻ����	NNNNNNNNNNNN	6
													if( Key_Status!=0 ){Err_DI = 1;break;}//��Կ��������
													
													Temp32.B08[0] = 6;	//���ݳ���
													Temp32.B08[1] = 36;	//82�ļ���ƫ����
													Temp32.B08[2] = 0x40+12;//E2��ҳ��ƫ����
													break;
																							
												default:
													Err_DI = 1;	//���ݱ�ʶ��
													break;
											}
											break;
											
//										case 0x10:
//											switch( DI07.B08[0] )
//											{
//												case 0x01:  //�������1 ��ֵ	XXXXXX.XX	4	Ԫ
//													Temp32.B08[0] = 4;	//���ݳ���
//													Temp32.B08[1] = 16;	//82�ļ���ƫ����
//													Temp32.B08[2] = 0x40+0;	//E2��ҳ��ƫ����
//													break;
//													
//												case 0x02:  //�������2 ��ֵ	XXXXXX.XX	4	Ԫ
//													Temp32.B08[0] = 4;	//���ݳ���
//													Temp32.B08[1] = 20;	//82�ļ���ƫ����
//													Temp32.B08[2] = 0x40+4;	//E2��ҳ��ƫ����
//													break;
//		
//												default:
//													Err_DI = 1;	//���ݱ�ʶ��
//													break;
//											}
//											break;
											
										default:
											Err_DI = 1;	//���ݱ�ʶ��
											break;
									}
					
									if( Temp32.B08[0] )
									{
										if( IsMultiBcd( Uart[Ch].Buf+22, Temp32.B08[0] ) )	break;
	
										result = Update_ESAM_Bin_Mac( Temp32.B08[3], Temp32.B08[1], Uart[Ch].Buf+22, Temp32.B08[0] );
										if( result != 0x00 )	//�����������MAC У����ǲ��ô�����Ϣ��ERR ��bit2�������/δ��Ȩ����λ���������쳣Ӧ��֡��Ӧ��
										{
											k = 0x00; 
											OutBuf[ k++ ] = 0xFF;
											OutBuf[ k++ ] = 0x04;	//�����/δ��Ȩ
											break;
										}
										
										result = UpdateSysPara( Temp32.B08[2], Uart[Ch].Buf+22, Temp32.B08[0] ); //����XRAM, E2PROM
										if( result ) break;
										
										run_price_flag = 1;

										k = 1;
									}
									break;
									
								case 0x06:	//���ñ����׽���ֵ+���ݵ��+�������
									if( (DI07.B08[1] < 0x0a) || (DI07.B08[1] > 0x0b) || (DI07.B08[0] != 0xFF) ) { Err_DI = 1;	break; } //���ݱ�ʶ��

									if( Uart[Ch].Buf[9] != 70+16 ) break;	//6*4+7*4+4*3=64
									if( IsMultiBcd( Uart[Ch].Buf+22, 70 ) )	break;

									for( i=0; i<13; i++ ) Inverse( Uart[Ch].Buf+22+4*i, 4 );
									for( i=0; i< 6; i++ ) Inverse( Uart[Ch].Buf+74+3*i, 3 );

									memcpy( Buf, Uart[Ch].Buf+22, 70 );	//�洢���������
									
									if( DI07.B08[1] < 0x0c )
									{
										Inverse( Uart[Ch].Buf+22, 70 );	//Ϊ�˷���MACУ�麯���ĸ�ʽ
										
										result = Update_ESAM_Bin_Mac( 0x84, 0x04+12*4+(DI07.B08[1]-0x0a)*70, Uart[Ch].Buf+22, 70 );
										if( result != 0x00 )	//�����������MAC У����ǲ��ô�����Ϣ��ERR ��bit2�������/δ��Ȩ����λ���������쳣Ӧ��֡��Ӧ��
										{
											k = 0x00; 
											OutBuf[ k++ ] = 0xFF;
											OutBuf[ k++ ] = 0x04;	//�����/δ��Ȩ
											break;
										}
									}

									JTRecord( OptID.B08 );	//���ݱ�̼�¼
							
									for( i=0; i< 6; i++ ) Inverse( Buf+52+3*i, 3 );

									WriteE2WithJieti( DI07.B08[1]-0x06, Buf );
									
									RefreshPrice();
									
									k = 1;
									break;	
									
								default:
									Err_DI = 1;	//���ݱ�ʶ��
									break;
							}
							break;
							
						default:
							Err_DI = 1;	//���ݱ�ʶ��
							break;
					}
					break;
				
				default:
					Err_DI = 1;	//Error: bit2�������/δ��Ȩ
					break;
			}

			if( Err_DI )	//�û��Բ�֧��д�������������̣������쳣Ӧ��֡����������Ϣ��Bit2��1�����������/δ��Ȩ����
			{
				k = 2;
				OutBuf[0] = 0xFF;	//Operation result.
				OutBuf[1] = 0x04;	//Error: bit2�������/δ��Ȩ
				break;
			}
						
			if( k && (OutBuf[0] == 0x00) )
			{
				ProgramRecord( DI07.B08, OptID.B08 );
			}
			break;

		//=====================================================================================
		case 0x11:	//��ȡ
			//����������̼�¼����
			
			if( (Uart[Ch].Buf[9] == 0x09) && (Byte2uInt(DI07.B08) == 0x00030404) )//Һ���鿴
			{
				Temp16.B16 = GetLcdNo( Uart[Ch].Buf+14 );
				if( Temp16.B16 == 0x00 )	break;//��ʾ��Ŀ���� or ��ʾ��Ŵ�
				
				Ext_Disp_Cnt = Temp16.B16;
				Display.Timer = 10;
				Display.Status &= B1111_1110;	//����ѭ��״̬
				freeze_display_flag = 0;	//������յ�����ʾ��־
								
				Display.Number  = 0xfc;//Һ���鿴��ʾ
				Lcdled = 10;//��������
				if( Ext_Disp_Cnt == 200 )Init_Led_Timer = 10;//ȫ����ʾ����led��
				
				k = 6;
				memcpy( OutBuf+1, Uart[Ch].Buf+14, 5 );
				break;
			}
			
			if( Uart[Ch].Flag&B0000_0001 ) break; //ͨѶ��ַȫ99   ��֧��
			
			if( ((Uart[Ch].Buf[9] == 0x0A) || (Uart[Ch].Buf[9] == 0x05)) && (DI07.B08[3] == 0x06) )
			{
				if( (((DI07.B08[2] == 0x10) || (DI07.B08[2] == 0x11)) && (DI07.B08[1] && (DI07.B08[1] <= 0x08)))
				||  (( DI07.B08[2] == 0x10) && ((DI07.B08[1] == 0x0C) || (DI07.B08[1] == 0x0D))) )
				{
					if( Uart[Ch].Buf[9] != 0x0A ) break;
					if( IsMultiBcd( Uart[Ch].Buf+14, Uart[Ch].Buf[9]-0x04 ) ) break;
					if( JudgeClockNoWeek( 1, Uart[Ch].Buf+15, 5 ) )break;
				
					k = ReadLoadRec( Ch, Uart[Ch].Buf+8, OutBuf );
					if( k == 0 ) {RdLoadPara[Ch][4] = 0; k++;}
					else if(RdLoadPara[Ch][4]) Remain = 1;
					break;
				}
			}
			else if( (Uart[Ch].Buf[9] == 0x11)||((Uart[Ch].Buf[9] == 0x07) && (Uart[Ch].Buf[10] == 0x01)))//У�����
			{
				if(progenable)
				{
					if( DI07.B08[0] != 0x01)
					{							
						Inverse( Uart[Ch].Buf+12, 3 );
						Inverse( Uart[Ch].Buf+16, 3 );
						Inverse( Uart[Ch].Buf+19, 4 );
						Uart[Ch].Buf[11] = 0;
						Uart[Ch].Buf[15] = 0;
					}
					
					Check_Err_Pro(Ch, DI07.B08[0]);	//����У
						
					Uart[Ch].Overtime_Timer = 2;	//����Ӧ���ֽڷ���
					return;
				}
			}
			else if( Uart[Ch].Buf[9] == 0x04 )
			{
				Times = 1;
			}
			else if( DI07.B32 == 0x0E800009 )
			{
				Uart[Ch].Buf[9] = 4;	//��������У��
				Times = 1;
			}
			else if( (DI07.B08[1] == 0xEE) && (DI07.B08[2] == 0xEE) && (DI07.B08[3] == 0xEE) ) //����������ϳ���(EEEEEENN)
			{
				Times = Bcd_To_Hex(DI07.B08[0]);
				if( IsBCD(DI07.B08[0]) || (Times == 0) || (Times > 20) ) break;
				if( Uart[Ch].Buf[9] != 5*Times+3 ) break;
			}
			else if( ble_inter_flag ) 
			{
				Times = 1;
			}
			else break;
		
		for( Loop=0; Loop<Times; Loop++ )
		{
			if( (Uart[Ch].Buf[9] != 0x04) && !ble_inter_flag ) //����������ϳ���(EEEEEENN)
			{
				Clear_Wdt();
				memcpy( DI07.B08, Uart[Ch].Buf+14+Loop*5, 4 );
				memcpy( DI08.B08, Uart[Ch].Buf+14+Loop*5, 4 );//����
				
				k = 0;
				OutBuf[0] = 0x00;
			}
					
			switch( DI07.B08[3] )
			{
				case 0x00:	//��ǰ�ͽ����� ��������
					switch( DI07.B08[2] )
					{
						case 0x68:	//���(�߾�����)
						case 0x60:	//����(�߾�����)
						case 0x61:	//����(�߾�����)
						case 0x62:	//����޹�1(�߾�����)
						case 0x63:	//����޹�2(�߾�����)
						case 0x64:	//��һ�����޹�(�߾�����)
						case 0x65:	//�ڶ������޹�(�߾�����)
						case 0x66:	//���������޹�(�߾�����)
						case 0x67:	//���������޹�(�߾�����)
							if( DI07.B08[2] == 0x68 )  DI07.B08[2] = 0x70;
							else DI07.B08[2] += 0x11;
						case 0x15:	//����(A��)
						case 0x16:	//����(A��)
						case 0x17:	//����޹�1(A��)
						case 0x18:	//����޹�2(A��)
						case 0x19:	//��һ�����޹�(A��)
						case 0x1A:	//�ڶ������޹�(A��)
						case 0x1B:	//���������޹�(A��)
						case 0x1C:	//���������޹�(A��)
							if( (DI07.B08[2]>=0x15)&&(DI07.B08[2]<=0x1C) ) DI07.B08[2] -= 0x14;				
						case 0x00:	//���
						case 0x01:	//����
						case 0x02:	//����
						case 0x03:	//����޹�1
						case 0x04:	//����޹�2
						case 0x05:	//��һ�����޹�
						case 0x06:	//�ڶ������޹�
						case 0x07:	//���������޹�
						case 0x08:	//���������޹�
						case 0x70:	//���(�߾�����)
						case 0x71:	//����(�߾�����)
						case 0x72:	//����(�߾�����)
						case 0x73:	//����޹�1(�߾�����)
						case 0x74:	//����޹�2(�߾�����)
						case 0x75:	//��һ�����޹�(�߾�����)
						case 0x76:	//�ڶ������޹�(�߾�����)
						case 0x77:	//���������޹�(�߾�����)
						case 0x78:	//���������޹�(�߾�����)
							//�������: ��ʱ����ʱ��(5)+�����й��ܵ���(5*4)+�����й��ܵ���(5*4)+��ʱ�����������(3)
							result = Cal_Comb( DI07.B08[2]&0x0f, DI07.B08[1], DI07.B08[0], OutBuf+1 );
							if( (result == 0x00) || (result > 25*8) ) break;	//��������ݱ�ʶ
							
							//645ͨ��:��Ҫ���ص���
							for( i=0; i<result/8; i++ )
							{
								if( (DI07.B08[2]&0x0f)==0 || (DI07.B08[2]&0x0f)==3 || (DI07.B08[2]&0x0f)==4 )
								{
									Hex2Bcd_Dl_G( OutBuf+1+8*i, 0 );	//������תBCD����(�߾���)(���)
									if( OutBuf[1+8*i+7] ) OutBuf[1+8*i+4] |= 0x80;	//��ϵ���<0�����λ��1
								}
								else
									Hex2Bcd_Dl_G( OutBuf+1+8*i, 1 );	//������תBCD����(�߾���)
								
								if( DI07.B08[2]&0xf0 ) //�߾���
									memcpy( OutBuf+1+5*i, OutBuf+1+(8*i+0), 5 );	//xxxxxxxxxxxx.xxxx���xxxxxx.xxxx
								else
									memcpy( OutBuf+1+4*i, OutBuf+1+(8*i+1), 4 );	//xxxxxxxxxxxx.xxxx���xxxxxx.xx
							}
							
							if( DI07.B08[2]&0xf0 )	//�߾���
								k = 0x01+result/8*5;
							else 
								k = 0x01+result/8*4;
							break;
						
						case 0x0B:	//��ǰ/��1���������õ���
						case 0x0C:	//��ǰ/��1�¶��õ���
							if( DI07.B08[0] > max_histroy_p ) break;
						case 0x0D:	//��ǰ/��1~6����õ���
							if( (DI07.B08[1] != 0x00) || ((DI07.B08[2] == 0x0D)&&(DI07.B08[0] > 0x06)) ) break;
//							if( (!BDMODE) && (DI07.B08[2] == 0x0D) ) break;

							Cal_Comb_Usedl( DI07.B08[2]-0x0B, DI07.B08[0], OutBuf+1 );//ʱ��4/Ԥ��4+�߾��ȵ���8�ֽ�
							
							if( OutBuf[5+7] ) OutBuf[5+4] |= 0x80;	//��ϵ���<0�����λ��1	
							
							if( DI07.B08[2] == 0x0D )
							{
								k = 9;
								memcpy( OutBuf+5, OutBuf+5+1, 4 );//xxxxxxxxxxxx.xxxx���xxxxxx.xx
							}
							else
							{
								k = 5;
								memcpy( OutBuf+1, OutBuf+5+1, 4 );//xxxxxxxxxxxx.xxxx���xxxxxx.xx
							}
							break;
							
						case 0x50:	//��ǰ/��1~12�¶��õ���	�߾���
							if( (DI07.B08[1] != 0x00) || (DI07.B08[0] > max_histroy_p) ) break;
							
							Cal_Comb_Usedl( 0x01, DI07.B08[0], OutBuf+1 );//ʱ��4/Ԥ��4+�߾��ȵ���8�ֽ�
							
							if( OutBuf[5+7] ) OutBuf[5+4] |= 0x80;	//��ϵ���<0�����λ��1	
							
							k = 6;
							memcpy( OutBuf+1, OutBuf+5, 5 );//xxxxxxxxxxxx.xxxx���xxxxxx.xxxx
							break;
							
						case 0xD0:	//��������
							if( (DI07.B08[1] != 0xFF) || (DI07.B08[0] != 0x00) ) break;
							
							memset( OutBuf+1, 0xff, 56 );
							DltoEepromBuf(0);//��ǰ��������
							Comp_RpdltoEepromBuf(8);//��ǰ����޹�1/2��
							Comm_Calculate_Comp_Rp( Eeprom.Buffer, 4, 0x00 );
												
							Four_RpdltoEepromBuf(16);//��ǰ�������޹���
							Comm_Calculate_Dl( Eeprom.Buffer+16, 4, 0x00 );
							
							memcpy( OutBuf+1, Eeprom.Buffer, 32 );
							memcpy( OutBuf+1+32, Eeprom.Buffer, 8 );//��ǰ������A��
							
							k = 1+56;
							break;							
							
						case 0xFE:	//����ʱ��
							if( (DI07.B08[1] != 0x00) || (DI07.B08[0] == 0) || ((DI07.B08[0]>max_histroy_p)&&(DI07.B08[0]!=0xFF)) ) break;
							
							result = Cal_Comb( 0x09, 0x00, DI07.B08[0], OutBuf+1 );	//���ؽ���ʱ��
							
							k = 0x01+result;
							break;
						
						default:
							break;
					}
					break;
				
				case 0x02:	//�������ݱ�ʶ
					if( DI07.B08[2] == 0x90 && DI07.B08[1] == 0xff && DI07.B08[0] == 0x00 ) //��������
					{
						memset( OutBuf+1, 0xff, 72 );
						memcpy( OutBuf+1, 		Emu_Data.U.B08, 2 );//A���ѹ
						memcpy( OutBuf+1+6, 		Emu_Data.I1.B08, 3 );//A�����
						if( dl_back_flag ) OutBuf[1+6+2] |= 0x80;
						memcpy( OutBuf+1+6+9, 		Emu_Data.I2.B08, 3 );//���ߵ���
						if( dln_back_flag ) OutBuf[1+6+9+2] |= 0x80;
						memcpy( OutBuf+1+6+12, 		Emu_Data.Freq.B08, 2 );//Ƶ��
						memcpy( OutBuf+1+6+12+2, 	Emu_Data.P1.B08, 3 );//�й�����
						if( dl_back_flag ) OutBuf[1+6+12+2+2] |= 0x80;
						memcpy( OutBuf+1+6+12+2+3, 	Emu_Data.P1.B08, 3 );//A���й�����
						if( dl_back_flag ) OutBuf[1+6+12+2+3+2] |= 0x80;
						memcpy( OutBuf+1+6+12+2+12, 	Emu_Data.Pav.B08, 3 );//һ����ƽ���й�����
						if( dl_back_flag ) OutBuf[1+6+12+2+12+2] |= 0x80;
						memcpy( OutBuf+1+6+12+2+15, 	Emu_Data.Q1.B08, 3 );//�޹�����
						if( dl_back_flag2 ) OutBuf[1+6+12+2+15+2] |= 0x80;
						memcpy( OutBuf+1+6+12+2+15+3, 	Emu_Data.Q1.B08, 3 );//A���޹�����
						if( dl_back_flag2 ) OutBuf[1+6+12+2+15+3+2] |= 0x80;
						memcpy( OutBuf+1+6+12+2+15+12, 	Emu_Data.Qav.B08, 3 );//һ�����޹�ƽ������
						if( dl_back_flag2 ) OutBuf[1+6+12+2+15+12+2] |= 0x80;
						memcpy( OutBuf+1+6+12+2+30, 	Emu_Data.Cosa.B08, 2 );//��������
						if( dl_back_flag ) OutBuf[1+6+12+2+30+2] |= 0x80;
						memcpy( OutBuf+1+6+12+2+30+2, 	Emu_Data.Cosa.B08, 2 );//A�๦������
						if( dl_back_flag ) OutBuf[1+6+12+2+30+2+2] |= 0x80;
						memcpy( OutBuf+1+6+12+2+30+14+6,&Fun_Para.Voltage_B, 2 );//ʱ�ӵ�ص�ѹ
						
						k = 1+72;
						break;
					}
					
					if( DI07.B08[2] == 0x80 )
					{
						if( DI07.B08[1] != 0x00 ) break;

//						if( (!BDMODE) && ( (DI07.B08[0] == 0x0b) || (DI07.B08[0]==0x20) || (DI07.B08[0]==0x21))) break;	//Զ��ģʽ��֧�ֳ������ز���
							
						switch( DI07.B08[0] )
						{
							case 0x01:	//���ߵ���	XXX.XXX	3	A
								Temp08 = 3;
								Temp32.B32 = Emu_Data.I2.B32;
								if((dln_back_flag) && (Emu_Data.I2.B32)) Temp32.B08[2] |= 0x80;
								break;
							
							case 0x02:	//����Ƶ��	XX.XX	2	Hz
								Temp08 = 2;
								Temp32.B32 = Emu_Data.Freq.B32;
								break;
								
							case 0x03:	//һ�����й���ƽ������	XX.XXXX	3	kW
								Temp08 = 3;
								Temp32.B32 = Emu_Data.Pav.B32;
								if( dl_back_flag )	Temp32.B08[2] |= 0x80;
								break;
								
							case 0x07:	//�����¶�	XXX.X	2	��
								Temp08 = 2;
								Temp32.B32 = Fun_Para.Temper_M;
								break;
								
							case 0x08:	//ʱ�ӵ�ص�ѹ(�ڲ�)	XX.XX	2	V
							case 0x09:
								Temp08 = 2;
								Temp32.B32 = Fun_Para.Voltage_B;
								break;
								
//							case 0x09:	//ͣ�糭���ص�ѹ (�ⲿ)	XX.XX	2	V
//								break;
								
							case 0x0A:	//�ڲ���ع���ʱ��	XXXXXXXX	4	��
								Temp08 = 4;
								Get_Keep_Timer(4, Temp32.B08);
								break;
								
							case 0xFA:	//���Ƿѹ����(�ڲ���չ)	XXXXXX		3	��
								Temp08 = 3;
								Read_Event_Number( Temp32.B08, ee_batterlow_inpage );
								break;	
							
							case 0x0B:	//��ǰ���ݵ��	XXXX.XXXX	4	Ԫ/kWh
								Temp08 = 4;
								Exchange(Temp32.B08, Price.Current_L.B08, 4);
								break;
						
							case 0x0E:	//���ߵ���		XXX.XXX 3 A
								Temp08 = 3;
								Temp32.B32 = Emu_Data.I1.B32;
								if( dl_back_flag )	Temp32.B08[2] |= 0x80;
								break;
								
							case 0x0F:	//�����й�����	XX.XXXX 3 kW
								Temp08 = 3;
								Temp32.B32 = Emu_Data.P1.B32;
								if( dl_back_flag )	Temp32.B08[2] |= 0x80;
								break;
								
							case 0x10:	//���߹�������	X.XXX 2
								Temp08 = 2;
								Temp32.B32 = Emu_Data.Cosa.B32;
								if( dl_back_flag )	Temp32.B08[1] |= 0x80;
								break;
							
							case 0x20:	//��ǰ���
								Temp08 = 4;
								Exchange(Temp32.B08, Price.Current.B08, 4);								
								break;
								
//							case 0x21:	//��ǰ���ʵ��
//								Temp08 = 4;
//								Exchange(Temp32.B08, Price.Current_F.B08, 4);
//								break;

							case 0x25:	//һ�����޹���ƽ������	XX.XXXX	3	kar
								Temp08 = 3;
								Temp32.B32 = Emu_Data.Qav.B32;
								if( dl_back_flag2 )	Temp32.B08[2] |= 0x80;
								break;
								
							case 0x31:	//�ϵ�����ʱ��	NNNNNNNN	4	��
								Temp08 = 4;
								Temp32.B32 = Meter_Run_Timer4/60;
								Hex2Bcd_SS( Temp32.B08, Temp32.B08, 4 );
								break;	
						
							case 0x32:	//��ǰ����
								Temp08 = 1;
								if( (dl_back_flag == 0) && (dl_back_flag2 == 0) ) Temp32.B32=1;
								else if( (dl_back_flag == 1) && (dl_back_flag2 == 0) ) Temp32.B32=2;
								else if( (dl_back_flag == 1) && (dl_back_flag2 == 1) ) Temp32.B32=3;
								else Temp32.B32=4;
								break;		

							case 0x86:	//��ǰ����
								Temp08 = 1;
								if(Tariff.Current_Ladder != 0xff)
									Temp32.B32 = Tariff.Current_Ladder+1;
								else
									Temp32.B32 = 0x00;								
								break;
								
							case 0x22:	//�����֤ʱЧʣ��ʱ��	XXXX 	2	����
//							case 0x23:	//������֤ʱЧʣ��ʱ��	XXXX 	1  	����
							case 0x83:	//������֤ʣ��ʱ�� 1 ����
								if( DI07.B08[0] == 0x22 )
								{
									Temp32.B32 = Identitytimer;
									Temp08 = 2;
								}
								else
								{
									Temp32.B32 = IR_EnTimer;
									Temp08 = 1;
								}
								
								Temp32.B32 = (Temp32.B32+59)/60;
								Hex2Bcd_SS( Temp32.B08, Temp32.B08, 4 );
								break;
								
							default:
								Temp08 = 0x00;
								break;
						}
						
						if( Temp08 )
						{	
							memcpy( OutBuf+1, Temp32.B08, 4 );
							k = 1+Temp08;
						}
					}
					else if( DI07.B08[2] == 0x81 )//���������豸��Ϣ
					{
						if( DI07.B08[1] != 0x01 ) break;
							
						switch(DI07.B08[0])
						{
							case 0x01:
							case 0x02:
							case 0x03:
							case 0x04:
							case 0x05:
								memcpy(OutBuf+1, &Ble_Connect[DI07.B08[0]-1].Ble_Mac, 6);
								
								k = 7;
								break;
								
							case 0xFF:
								for(i=0; i<5; i++)
								{
									memcpy(OutBuf+1+6*i, &Ble_Connect[i].Ble_Mac, 6);
								}
								
								k = 31;
								break;
								
							default:
								break;
						}
						break;
					}
					else
					{
						if( DI07.B08[0] != 0x00 ) break;
						
						Temp08 = 0x00;
						switch( DI07.B08[2] )
						{
							case 0x01:	//A���ѹ	XXX.X	2
							case 0x02:	//A�����	XXX.XXX	3
								if( (DI07.B08[1] == 0x01) || (DI07.B08[1] == 0xFF) )
								{
									if( DI07.B08[2] == 0x01 ) Temp08 = 2;
									else Temp08 = 3;
								}
								break;

							case 0x03:	//˲ʱ���й�����	XX.XXXX	3
							case 0x04:	//˲ʱ���޹�����	XX.XXXX	3
							case 0x05:	//˲ʱ�����ڹ���	XX.XXXX	3
							case 0x06:	//�ܹ�������		X.XXX	2
								if( (DI07.B08[1] <= 0x01) || (DI07.B08[1] == 0xFF) )
								{
									if( DI07.B08[2] == 0x06 ) Temp08 = 2;
									else Temp08 = 3;
								}
								break;
								
							default:
								break;
						}
						
						if( Temp08 )
						{
							if( DI07.B08[2] == 0x04 ) //˲ʱ���޹�����
							{
								memcpy( OutBuf+1, Emu_Data.Q1.B08, 4 );
											
								if( dl_back_flag2 ) OutBuf[Temp08] |= 0x80;
							}
							else
							{
								memcpy( OutBuf+1, Emu_Data.U.B08+(DI07.B08[2]-1)*4, 4 );
								
								if( dl_back_flag && (
								(DI07.B08[2]==0x02) ||
								(DI07.B08[2]==0x03) ||
								(DI07.B08[2]==0x06) ) )	OutBuf[Temp08] |= 0x80;
							}
							
							k = 1+(Temp08);
							if( DI07.B08[1] == 0xFF )
							{
								if(DI07.B08[2] >= 0x03 )
								{
									memcpy( OutBuf+k, OutBuf+1, (Temp08) );
									k += Temp08;
								}

								memset( OutBuf+k, 0xFF, 2*(Temp08) );
								k += 2*(Temp08);
							}
						}
					}
					break;
					
				case 0x03:	//�¼���¼���ݱ�ʶ
				case 0x03+0x80:	//�¼���¼���ݱ�ʶ				
					if( ((DI07.B08[3]&0x7f) == 0x03) && ((DI07.B08[2] == 0x70)||(DI07.B08[2] == 0x10)) && (DI07.B08[1] == 0x01) ) DI07.B08[1] = 0x00; //ͬʱ֧��A��
					if( ((DI07.B08[3]&0x7f) == 0x03) && (DI07.B08[2] == 0x70) && (DI07.B08[1] == 0x00) && (DI07.B08[0] == 0x00) )
					{
						k = 1+ee_dayvolpassnote_len;
						CalLoad( OutBuf+1, 0 );	//���㵱ǰ�յ�ѹ�ϸ���
						break;
					}
					else if( ((DI07.B08[3]&0x7f) == 0x03) && (DI07.B08[2] == 0x10) && (DI07.B08[1] == 0x00) && (DI07.B08[0] == 0x00) )
					{
						k = 1+ee_monvolpassnote_len;
						CalLoad( OutBuf+1, 1 );	//���㵱ǰ�µ�ѹ�ϸ���
						break;
					}
					else if( ((DI07.B08[3]&0x7f) == 0x03) && ((DI07.B08[1] == 0x02) || (DI07.B08[1] == 0x03)) && (DI07.B08[2] == 0xc0) )
					{
						
						RdHisPd( DI07.B08, OutBuf );//��ͣ��ͳ������
						if( OutBuf[0] == 0x00 ) break;
						
						k = OutBuf[0]+1;
						OutBuf[0] = 0x00;
						break;
					}
					
					k = RdHisEvent( DI07.B08, 0, OutBuf );
					if( k )
					{			
						k += 1;
						OutBuf[0] = 0x00;
						break;
					}
					else if( (DI07.B08[2] != 0x11) && (DI07.B08[2] != 0x33) ) break;
					
				case 0x10:	//ʧѹ��¼
				case 0x19:	//������¼
				case 0x1D:	//��բ��¼����բ��¼
				case 0x1E:	//��բ��¼
				case 0x22:	//���Ƿѹ��¼
				case 0x10+0x80:	//ʧѹ��¼
				case 0x19+0x80:	//������¼
				case 0x1D+0x80:	//��բ��¼����բ��¼
				case 0x1E+0x80:	//��բ��¼
				case 0x22+0x80:	//���Ƿѹ��¼
					k = Rd_Relay_Buy_Rec( DI07.B08, OutBuf );
					if( k == 0x00 ) break;
					
					k += 1;
					OutBuf[0] = 0x00;	//���
					break;

				case 0x04:	//�α������ݱ�ʶ
					switch( DI07.B08[2] )
					{
						case 0x00:	
							switch( DI07.B08[1] ) 
							{
								case 0x01:	
									switch( DI07.B08[0] )
									{
										case 0x01:	//���ڼ�����(����0����������)	YYMMDDWW  	4	����������	
											k = 5;
											OutBuf[1] = Sclock.Clockmain[3];
											OutBuf[2] = Sclock.Clockmain[4];
											OutBuf[3] = Sclock.Clockmain[5];
											OutBuf[4] = Sclock.Clockmain[6];
											break;
											
										case 0x02:	//ʱ��                          hhmmss    	3	ʱ����      
											k = 4;
											OutBuf[1] = Sclock.Clockmain[0];
											OutBuf[2] = Sclock.Clockmain[1];
											OutBuf[3] = Sclock.Clockmain[2];
											break;
											
										case 0x05:	//У��������                  XXXX      	2	����        
											k = 3;
											OutBuf[1] = Hex_To_Bcd(Def_Plusevalidtimer*4);
											OutBuf[2] = 0x00;
											break;
											
										case 0x0A:	//���׽���ʱ���л�ʱ��		YYMMDDhhmm 	5
										case 0x06:	//����ʱ�����л�ʱ��            YYMMDDhhmm	5	������ʱ��, ���ģ�MAC
										case 0x07:	//������ʱ���л�ʱ��            YYMMDDhhmm	5	������ʱ��, ���ģ�MAC
										case 0x09:	//���׽����л�ʱ��		YYMMDDhhmm	5	������ʱ��, ���ģ�MAC
											k = 6;
											if( DI07.B08[0] == 0x0A ) Exchange( OutBuf+1, Starttime.LadSQ, 5 );
											else Exchange( OutBuf+1, Starttime.Shiqu+5*(DI07.B08[0]-0x06), 5 );
											break;
											
										case 0x0C:	//���ڡ�����(����0����������)��ʱ��	YYMMDDWWhhmmss	7 ����������ʱ����
											k = 8;
											memcpy( OutBuf+1, Sclock.Clockmain, 7 );
											break;
											
										case 0x0D:	//���ܱ�����MAC��ַ(HEX��)
											Bcd2Hex_LS(Comm_Addr.Comm_Id, OutBuf+1, 6);
											OutBuf[6]  = 0xC0;
											
											k = 7;
											break;
											
										default:
											break;
									}										
									break;
									
								case 0x02:	  
									//��ʱ������1������ʱ�α�����1������ʱ���� ��1������������1����������������1��+г������������1��+��������1������Կ����1����crc��2��
									if( (DI07.B08[0]) && (DI07.B08[0]<=ee_feiknumber_lenth) )
									{
//										if( (!BDMODE) && (DI07.B08[0] == 0x07) ) break;
											
										k = 2;
										OutBuf[1] = Feik.Num[DI07.B08[0]-1];
										if( DI07.B08[0] == 5 )	//����������
										{
											OutBuf[2] = 0x00;
											k += 1;
										}
									}
									else if( DI07.B08[0]==0x09 ) //��ǰ��ʱ�α�
									{
										k = ee_shiduantable_lenth+1;
										memcpy( OutBuf+1, Tariff.Table, ee_shiduantable_lenth );
									}
									break;
									
								case 0x03:
									switch( DI07.B08[0] )
									{
										case 0x01:	//�Զ�ѭ����ʾ����            	NN      1   ��	
										case 0x02:	//ÿ����ʾʱ��					NN		1	��	
										case 0x03:	//��ʾ����С��λ��				NN		1	λ	
										case 0x04:	//��ʾ���ʣ����������С��λ��	NN      1   λ  
										case 0x05:	//����ѭ����ʾ����            	NN      1   ��  
										case 0x08:	//�ϵ�ȫ��ʱ��	NN	1	λ
//											if( DI07.B08[0] == 0x08 ) Temp32.B08[2] = 0x05;
//											else Temp32.B08[2] = DI07.B08[0]-1;
											
											k = 2;
											OutBuf[1] = Hex_To_Bcd(*(&Display_Para.S_Number+DI07.B08[0]-1));
											break;
											
										case 0x06:	//�������������              	NNNNNN	3       break;
										case 0x07:	//��ѹ���������              	NNNNNN	3	    break;
											//�������1��ֵ(4)���������2��ֵ(4)+���������(6)�����(6)+�ͻ����(6)+�翨����(1)+�����֤ʱЧ(2)
											k = 4;
											Exchange( OutBuf+1, Esam_Para.Current_Ratio+3*(DI07.B08[0]-6), 3 );
											break;

										default:	
											break;
									}
									break;
									
								case 0x04:	  
									switch( DI07.B08[0] )
									{
										case 0x01:	//ͨ�ŵ�ַ                     	NNNNNNNNNNNN	6
											k = 7;
											Exchange( OutBuf+1, Comm_Addr.Comm_Id, 6 );
											break;

										case 0x02:	//���                         	NNNNNNNNNNNN	6
											k = 7;
											Exchange( OutBuf+1, Esam_Para.Meter_Id, 6 );
											break;
											
										case 0x04:	//���ѹ��ASCII �룩         XXXXXXXXXXXX	6	
										case 0x05:	//�����/����������ASCII �룩XXXXXXXXXXXX	6
										case 0x06:	//��������ASCII �룩         XXXXXXXXXXXX	6
										case 0x07:	//�й�׼ȷ�ȵȼ���ASCII �룩   XXXXXXXX   	4
										case 0x08:	//�޹�׼ȷ�ȵȼ���ASCII �룩   XXXXXXXX   	4
//										case 0x0B:	//����ͺţ�ASCII �룩         XX��XX      	10 
										case 0x0D:	//Э��汾�ţ�ASCII �룩        XX��XX      	16
										case 0x16: 	//��С������ASCII �룩         XXXXXXXXXXXX	6
										case 0x17: 	//ת�۵�����ASCII �룩         XXXXXXXXXXXX	6
											k = 6;
											if(DI07.B08[0] == 0x04) Code_Flash_Char = (uint08*)RatedVolt;
											else if(DI07.B08[0] == 0x05) Code_Flash_Char = (uint08*)RatedCurr;
											else if(DI07.B08[0] == 0x06) Code_Flash_Char = (uint08*)MaxCurr;
											else if(DI07.B08[0] == 0x07) {k=4; Code_Flash_Char = (uint08*)ActiveClass;}
											else if(DI07.B08[0] == 0x08) {k=4; Code_Flash_Char = (uint08*)ReActiveClass;}
//											else if(DI07.B08[0] == 0x0B) {k=10;Code_Flash_Char = (uint08*)MaterType;}
											else if(DI07.B08[0] == 0x16) Code_Flash_Char = (uint08*)MinCurr;
											else if(DI07.B08[0] == 0x17) Code_Flash_Char = (uint08*)TrtCurr;
											else {k=16;Code_Flash_Char = (uint08*)ProtocolVer;}
											Exchange( OutBuf+1, Code_Flash_Char, k );	
											k++;
											break; 
										
										case 0x0B:	//����ͺţ�ASCII �룩         XX��XX      	10 
											if(DI07.B08[0] == 0x0B)
											{
												Code_Flash_Char = (uint08*)MaterType;
												Temp16.B08[0] = ee_matertype_page; //����ͺ�
												Temp16.B08[1] = ee_matertype_inpage;
												Temp08 = ee_matertype_lenth;
											}
											result = I2C_Read_Eeprom( Temp16.B08[0], Temp16.B08[1], OutBuf+1, Temp08 );
																						
											for( i=0; i<Temp08; i++ )	//���ȫ��Ϊ0xff�����Ĭ�ϵ�ֵ
											{
												if( OutBuf[1+i] != 0xff ) break;
											}
											
											if( result || (i==Temp08) )
											{
												Exchange( OutBuf+1, Code_Flash_Char, Temp08 );  
											}
											k = Temp08+1;
											break; 
										
										case 0x0C:	//�������ڣ�ASCII �룩         XX��XX      	10
										case 0x03:	//�ʲ�������루ASCII �룩     NN��NN      	32
										case 0x0F:	//���ܱ�λ����Ϣ				11
											if(DI07.B08[0] == 0x0c) 
											{
												Temp16.B08[0] = ee_meterdate_page;//��������
												Temp16.B08[1] = ee_meterdate_inpage;
												Temp08 = 10;
											}
											else if(DI07.B08[0] == 0x03) 
											{
												Temp16.B08[0] = ee_zichannum_page;//�ʲ�������
												Temp16.B08[1] = ee_zichannum_inpage;
												Temp08 = 32;
											}
											else
											{
												Temp16.B08[0] = ee_meterpos_page;//���ܱ�λ����Ϣ
												Temp16.B08[1] = ee_meterpos_inpage;
												Temp08 = 11;
											}
											I2C_Read_Eeprom( Temp16.B08[0], Temp16.B08[1], OutBuf+1, Temp08 );
											k = Temp08+1;
											break; 	  											          	

										case 0x09:	//����й�����                  XXXXXX      	3	imp/kWh
											k = 4;
											Exchange( OutBuf+1, Meter.Const.B08+1, 3 );//ת���ɵ��ֽ���ǰ
											break;
											
										case 0x0A:	//����޹�����                  XXXXXX      	3   	imp/kvarh   
											k = 4;
											Exchange( OutBuf+1, Meter.Const.B08+1, 3 );//ת���ɵ��ֽ���ǰ
											break;
											
										case 0x0E:	//�ͻ����						NNNNNNNNNN		6
											k = 7;
											Exchange( OutBuf+1, Esam_Para.User_Id, 6 );
											break;

										default:	break;                                      		
									}
									break;
									
								case 0x05:	  
									switch( DI07.B08[0] )
									{
										case 0xFF:	//�������״̬�ֿ�	XXXX	14	
										case 0x01:	//�������״̬��1   XXXX	2
											//[0].B16	�������״̬��1					
											//bit15:	ʱ�ӹ���
											//bit14:	͸֧״̬
											//bit13:	�洢������
											//bit12:	�ڲ��������Ԥ����
											//bit09:	ESAM��
											//bit08:	���ƻ�·����
											//bit07:	reserved.
											//bit06:	�ѿ�ģʽ״̬  (0���أ�1Զ��)
											//bit05:	�޹����ʷ���	(0 ����1 ����)
											//bit04:	�й����ʷ���	(0 ����1 ����)
											//bit03:	ͣ�糭����	(0 ������1 Ƿѹ)
											//bit02:	ʱ�ӵ��		(0 ������1 Ƿѹ)    
											//bit01:	�������㷽ʽ	(0 ���1 ����)
											//bit00:	������Ԫ�쳣
											Temp16.B16 = 0x00;
											
											if( clock_error || (ChkLastclockerrRcdTime() == 1) )	//bit15:	ʱ�ӹ���  
											{
												Temp16.B08[0] |= B1000_0000;
											}
											
//											if( remainder_tick_flag )	//bit14:	͸֧״̬
//											{
//												Temp16.B08[0] |= B0100_0000;
//											}

											if( eeprom_error_flag )	//bit13:	�洢������
											{
												Temp16.B08[0] |= B0010_0000;
											}
											
											if( esam_error )	//bit09:	ESAM ״̬		(0 ������1 ����)
											{
												Temp16.B08[0] |= B0000_0010;
											}
											
											if( relay_error )	//bit08:	���ƻ�·����
											{
												Temp16.B08[0] |= B0000_0001;
											}
											
//											if( !BDMODE )		//bit06:	�ѿ�ģʽ״̬(0 ���أ�1 Զ��)
											{
												Temp16.B08[1] |= B0100_0000;
											}
																							
											if( dl_back_flag2 )			//�޹����ʷ���(0 ����1 ����)
											{
												Temp16.B08[1] |= B0010_0000;
											}
											
											if( dl_back_flag )			//�й����ʷ���(0 ����1 ����)
											{
												Temp16.B08[1] |= B0001_0000;
											}

											if( low_voltage_flag || Bat_Delay_Timer )//ͣ�糭����(0 ������1 Ƿѹ)+ʱ�ӵ��(0 ������1 Ƿѹ)
											{
												Temp16.B08[1] |= B0000_1100;
											}
											
											if( cal_err_flag )			//������Ԫ�쳣
											{
												Temp16.B08[1] |= B0000_0001;
											}

											k = 0x00;
											OutBuf[ k++ ] = 0x00;
											OutBuf[ k++ ] = Temp16.B08[1];
											OutBuf[ k++ ] = Temp16.B08[0];

											if( DI07.B08[0] == 0x01 )
											{
												break;
											}
											
										case 0x02:	//�������״̬��2	XXXX	2	
											Temp16.B16 = 0x00;
											if( dl_back_flag )	//bit0��A ���й����ʷ���( 0 ����1 ���� )
											{
												Temp16.B08[1] |= B0000_0001;
											}
											if( dl_back_flag2 )	//bit4��A ���޹����ʷ���( 0 ����1 ���� )
											{
												Temp16.B08[1] |= B0001_0000;
											}
											
											if( DI07.B08[0] == 0xFF )
											{
												OutBuf[ k++ ] = Temp16.B08[1];
												OutBuf[ k++ ] = Temp16.B08[0];
											}
											else
											{
												k = 3;
												OutBuf[1] = Temp16.B08[1];
												OutBuf[2] = Temp16.B08[0];
												break;
											}
											
										case 0x03:	//�������״̬��3	XXXX	2	
											//[2].B16	�������״̬��3(������)
											//bit15:	����
											//bit14:	����
											//bit13:	�����֤״̬(0ʧЧ��1��Ч)
											//bit12:	����״̬	(0�Ǳ���,1����)
											//bit11:	��ǰ����	(0��ǰ�׽��ݣ�1�����׽���)
											//bit10:	��ǰ���ݱ�(0��1�Ž��ݱ�1��2�Ž��ݱ�)
											//bit9~8:	���ܱ�����, 		(00 ��Ԥ���ѱ�,01 ������Ԥ���ѱ�,10 �����Ԥ���ѱ�)	
											//bit7:		Ԥ��բ����״̬		(0 �ޣ�1 ��)
											//bit6:		�̵�������״̬		(0 ͨ��1 ��)
											//bit5:		��ǰ����ʱ��		(0 ��һ�ף�1 �ڶ���)
											//bit4:		�̵���״̬			(0 ͨ��1 ��)
											//bit3:		������֤			(0 ʱЧ��1 ��Ч)
											//bit2~1:	���緽ʽ			(00 ����Դ��01 ������Դ��10 ��ع���)
											//bit0:		��ǰ����ʱ��		(0 ��һ�ף�1 �ڶ���)
											Temp16.B16 = 0x00;
											
											if( Comm_Auth_Judge() )			//bit13:	�����֤״̬
											{
												Temp16.B08[0] |= B0010_0000;
											}
											
											if( relay_commu_close_flag )		//bit12:	����״̬
											{
												Temp16.B08[0] |= B0001_0000;
											}
											
//											if( BDMODE )
											{
												if( Tariff.CurLad_N )	
												{
													Temp16.B08[0] |= B0000_0100;	//bit10: ��ǰ���ݱ� (0��1�Ž��ݱ�,1��2�Ž��ݱ�)
												}
												
//												Temp16.B08[0] |= B0000_0010;	//bit9~8�������Ԥ���ѱ�
											}

											if( relay_commu_alarm_flag )		//bit7��Ԥ��բ����״̬
											{
												Temp16.B08[1] |= B1000_0000;
											}

											if( relay_commu_open_flag )		//bit6���̵�������״̬
											{
												Temp16.B08[1] |= B0100_0000;
											}

											if( Tariff.Status&B0000_1000 )		//bit5����ǰ����ʱ��
											{
												Temp16.B08[1] |= B0010_0000;
											}

											if( comm_relaystatus_flag )		//bit4���̵���״̬
											{
												Temp16.B08[1] |= B0001_0000;
											}

											if( IR_EnTimer )			//bit3��������֤/�������
											{
												Temp16.B08[1] |= B0000_1000;
											}

											if( Tariff.Status&B0000_0100 )		//bit0����ǰ����ʱ��
											{
												Temp16.B08[1] |= B0000_0001;
											}

											if( DI07.B08[0] == 0xFF )
											{
												OutBuf[ k++ ] = Temp16.B08[1];
												OutBuf[ k++ ] = Temp16.B08[0];
											}
											else
											{
												k = 3;
												OutBuf[1] = Temp16.B08[1];
												OutBuf[2] = Temp16.B08[0];
												break;
											}

										case 0x04:	//�������״̬��4   XXXX	2	
											Temp16.B16 = 0x00;
											if( load_over_flag )	//bit4��A �����
											{
												Temp16.B08[1] |= B0001_0000;
											}
											
											if( lost_v_flag )	//bit0��A ��ʧѹ
											{
												Temp16.B08[1] |= B0000_0001;
											}
											
											if( DI07.B08[0] == 0xFF )
											{
												OutBuf[ k++ ] = Temp16.B08[1];
												OutBuf[ k++ ] = Temp16.B08[0];
											}
											else
											{
												k = 3;
												OutBuf[1] = Temp16.B08[1];
												OutBuf[2] = Temp16.B08[0];
												break;
											}			
											
										case 0x05:	//�������״̬��5   XXXX	2	
										case 0x06:	//�������״̬��6   XXXX	2	
											Temp16.B16 = 0x00;
											if( DI07.B08[0] == 0xFF )
											{
												for( i=0; i<2; i++ )
												{
													OutBuf[ k++ ] = 0x00;
													OutBuf[ k++ ] = 0x00;
												}
											}
											else
											{
												k = 3;
												OutBuf[1] = Temp16.B08[1];
												OutBuf[2] = Temp16.B08[0];
												break;
											}
											
										case 0x07:	//�������״̬��7   XXXX	2	���������״̬��
											//bit10:	�����
											Temp16.B16 = 0x00;
											if( Cover.Status )	//bit9:	�����
											{
												Temp16.B08[0] |= B0000_0010;
											}
											if( below_60u_flag )	//bit5:	����
											{
												Temp16.B08[1] |= B0010_0000;
											}
											
											if( DI07.B08[0] == 0xFF )
											{
												OutBuf[ k++ ] = Temp16.B08[1];
												OutBuf[ k++ ] = Temp16.B08[0];
											}
											else
											{
												k = 3;
												OutBuf[1] = Temp16.B08[1];
												OutBuf[2] = Temp16.B08[0];
												break;
											}
											
										case 0x08:	//��Կ״̬��	XXXXXXX		4
											if( DI07.B08[0] == 0xFF )
											{
												GetKey( OutBuf+k );
												k += 4;
											}
											else
											{
												GetKey( OutBuf+1 );
												k = 5;
											}
											break;
											
										default:	
											break;
									}
									break;
									
								case 0x06:	  
									switch( DI07.B08[0] )
									{
										case 0x01:  //�й���Ϸ�ʽ������  	NN	1	
											//�����������֣�5�����й���Ϸ�ʽ������1(1)����������ģʽ��(6)���������������1(1) +�ϱ�ģʽ��(6)+crc��2��
											k = 2;
											OutBuf[1] = Mode.Comp_B;
											break;
											
										case 0x02:  //�޹���Ϸ�ʽ1 ������  NN	1
											k = 2;
											OutBuf[1] = Mode.Rpcomp[0];	
											break;
											
										case 0x03: //�޹���Ϸ�ʽ2 ������  NN	1	
											k = 2;
											OutBuf[1] = Mode.Rpcomp[1];	
											break;
											
										default:	
											break;
									}
									break;
									
								case 0x07:	  
									switch( DI07.B08[0] )
									{
										case 0x01:	//�����ͺ����ڲ�����������	NN  1
//										case 0x02:	//�Ӵ�ʽ�����ڲ�����������    NN  1											
										case 0x03:	//ͨ�ſ�1 ������������          NN  1
//										case 0x04:	//ͨ�ſ�2 ������������          NN  1
										case 0x05:	//ͨ�ſ�3 ������������          NN  1
										case 0xfd:	//ͨ�ſ�3 ������������          NN  1 (��ǰ)
											//�����������֣�5�����й���Ϸ�ʽ������1(1)����������ģʽ��(6)���������������1(1) +�ϱ�ģʽ��(6)+crc��2��
											k = 2;
											if( DI07.B08[0] == 3 ) OutBuf[1] = Mode.Bps[0];
//											else if( DI07.B08[0] == 4 ) OutBuf[1] = Mode.blebps;
											else if( DI07.B08[0] == 5 ) OutBuf[1] = Mode.Zbbps; //ȱʡֵ
											else if( DI07.B08[0] == 0xfd ) OutBuf[1] = Zbbps; //��ǰ
											else OutBuf[1] = DI07.B08[0]+0x03;
											break;

										default:
											break;
									}
									break;
									
								case 0x08:	
									switch( DI07.B08[0] )
									{
										case 0x01:	//������������          	NN	1
											k = 2;
											OutBuf[1] = Week_Holiday.Status;
											break;
											
										case 0x02:	//��������õ���ʱ�α��	NN	1
											k = 2;
											OutBuf[1] = Week_Holiday.Shiduan_N;
											break;
										
										default:
											break;
									}
									break;

								case 0x0A:
									switch( DI07.B08[0] )
									{
										case 0x01:	//���ɼ�¼��ʼʱ��		MMDDhhmm	4
											k = 5;
											Exchange( OutBuf+1, Display_Para.Lstarttimer+1, 4 );
											break;
												
										case 0x02:	//��1 �ฺ�ɼ�¼���ʱ��    NNNN	2
										case 0x03:	//��2 �ฺ�ɼ�¼���ʱ��    NNNN	2
										case 0x04:	//��3 �ฺ�ɼ�¼���ʱ��    NNNN	2
										case 0x05:	//��4 �ฺ�ɼ�¼���ʱ��    NNNN	2
										case 0x06:	//��5 �ฺ�ɼ�¼���ʱ��    NNNN	2
										case 0x11:	//����й�����1~ 4���ܸ��ɼ�¼���ʱ��    NNNN	2
										case 0x12:	//����й�����5~ 8���ܸ��ɼ�¼���ʱ��    NNNN	2
//										case 0x13:	//����й�����9~12���ܸ��ɼ�¼���ʱ��    NNNN	2
											k = 3;
											if( DI07.B08[0]>=0x11 ) DI07.B08[0] -= 0x0A;
											Exchange( OutBuf+1, Display_Para.Lspacetimer[DI07.B08[0]-2].B08, 2 );
											break;

										default:
											break;
									}
									break;
								case 0x09:
								case 0x19:	
									//�����������֣�5�����й���Ϸ�ʽ������1(1)����������ģʽ��(6)���������������1(1) +�ϱ�ģʽ��(6)+crc��2��
									switch( DI07.B08[0] )
									{
										case 0x01:	//���ɼ�¼ģʽ��	NN	1/2								
										case 0x02:	//��ʱ��������ģʽ��	NN	1/2
										case 0x03:	//˲ʱ��������ģʽ��	NN	1/2
										case 0x04:	//Լ����������ģʽ��    NN	1/2
										case 0x05:	//���㶳������ģʽ��    NN	1/2
										case 0x06:	//�ն�������ģʽ��      NN	1/2
										case 0x07:	//�¶�������ģʽ��      NN	1/2
											k = 2;
											OutBuf[1] = Week_Holiday.Freeze[DI07.B08[0]-1].B08[1];
											if( DI07.B08[1] == 0x19 )
											{
												k = 3;
												OutBuf[2] = Week_Holiday.Freeze[DI07.B08[0]-1].B08[0];
											}
											break;
											
										default:
											break;
									}
									break;
									
								case 0x0B:	
									switch( DI07.B08[0] )
									{
										case 0x01:	//ÿ�µ�1 ������	DDhh	2	��ʱ
										case 0x02:	//ÿ�µ�2 ������    DDhh	2	��ʱ
										case 0x03:	//ÿ�µ�3 ������    DDhh	2	��ʱ
											ReadE2WithBackup( ee_histroyparameter_page, ee_histroyparameter_inpage, Buf, ee_histroyparameter_lenth );

											k = 3;
											OutBuf[1] = Buf[2*(DI07.B08[0]-1)+0];
											OutBuf[2] = Buf[2*(DI07.B08[0]-1)+1];
											break;

										default:
											break;
									}
									break;
								
								case 0x0C:	//0����Կ~9����Կ��02�����룬04������
//									if( DI07.B08[0] && (DI07.B08[0]<=0x0A) )
//									{
										k = 2;
										OutBuf[0] = 0xFF; //���
										OutBuf[1] = 0x04; //Error: bit2�������/δ��Ȩ
//									}
									break;
									
								case 0x0E:
									switch( DI07.B08[0] )
									{
										case 0x03:	//��ѹ����ֵ	NNN.N	2	V
										case 0x04:	//��ѹ����ֵ	NNN.N	2	V
											k = 3;
											Exchange( OutBuf+1, VolLimit.MaxVolLmt.B08+(DI07.B08[0]-3)*2, 2 );
											break;
											
										default:
											break;
									}
									break;	
									
								case 0x11:
									switch( DI07.B08[0] )
									{
										case 0x01:	//�������������1	NN	1
											//�����������֣�5�����й���Ϸ�ʽ������1(1)����������ģʽ��(6)���������������1(1) +�ϱ�ģʽ��(6)+crc��2��
											k = 2;
											OutBuf[1] = Mode.Feature1;
											break;
											
										case 0x04:	//�����ϱ�ģʽ��	NNNNNNNNNNNNNNNN	8
											//�����������֣�5�����й���Ϸ�ʽ������1(1)����������ģʽ��(5)���������������1(1)���ϱ�ģʽ��(6) + crc��2��
											k = 9;
											memcpy( OutBuf+1, Mode.Report, 8 );
											break;
											
										default:
											break;
									}
									break;
								
								case 0x12:
									switch( DI07.B08[0] )
									{
										case 0x01:	//���㶳����ʼʱ��	YYMMDDhhmm	5	������ʱ��
											Temp16.B08[0] = 5;	//����
											Temp16.B08[1] = 0;	//ƫ����
											break;
											
										case 0x02:  //���㶳��ʱ����	NN          1	����      
											Temp16.B08[0] = 1;	//����
											Temp16.B08[1] = 5;	//ƫ����
											break;
											
										case 0x03:  //�ն���ʱ��      	hhmm        2	ʱ��      
											Temp16.B08[0] = 2;	//����
											Temp16.B08[1] = 6;	//ƫ����
											break;
											
										case 0x04:	//��ʱ����ʱ��	4	MMDDhhmm
											Temp16.B08[0] = 4;	//����
											Temp16.B08[1] = 8;	//ƫ����
											break;
																						
										default:
											Temp16.B08[0] = 0;	//����
											break;
									}
									
									if( Temp16.B08[0] )
									{
										I2C_Read_Eeprom44( ee_freezeparameter_page, Buf, ee_freezeparameter_lenth );
										
										k = Temp16.B08[0]+1;
										Exchange( OutBuf+1, Buf+Temp16.B08[1], Temp16.B08[0] );
									}
									break;

//								case 0x13:	
//									switch( DI07.B08[0] )
//									{
//										case 0x01:	//����ͨ�����߼��ź�ǿ��ָʾ	NN	1	
//											break;
//											
//										default:
//											break;
//									}
//									break;
									
								case 0x14:
									switch( DI07.B08[0] )
									{
										case 0x01:	//��բ��ʱʱ�䣨NNNN Ϊ��բǰ�澯ʱ�䣩	NNNN	2
										case 0x02:	//�̵�����բ���Ƶ�������ֵ	XXX.XXX	3
										case 0x03:	//�̵�����ʱ��բʱ��	XXXX	2
//										case 0x04:	//������֤ʱЧ	XXXX	1
										case 0x05:	//�ϱ���λʱ��	XXXX	1
										case 0x06:	//������֤ʱЧ XX 1
											if( DI07.B08[0] == 0x02 )
											{
												Temp16.B08[0] = 0;	//ƫ�Ƶ�ַ0
												Temp16.B08[1] = 3;	//�ֽ���
											}
											else if( DI07.B08[0] >= 0x04 )
											{
												Temp16.B08[0] = (DI07.B08[0]&1)+0x07;//ƫ�Ƶ�ַ7,8
												Temp16.B08[1] = 1;
											}
											else
											{
												Temp16.B08[0] = DI07.B08[0]+2;//ƫ�Ƶ�ַ3,5	
												Temp16.B08[1] = 2;	
											}

											k = Temp16.B08[1]+1;
											Exchange( OutBuf+1, Mode.Limit_I+Temp16.B08[0], Temp16.B08[1] );	
											break;	
											
										case 0x08:	//�����ӻ�1//2/3 MAC��ַ��HEX��ʽ��
											I2C_Read_Eeprom(ee_bleslamac_page, ee_bleslamac_inpage, OutBuf+1, ee_bleslamac_lenth);
											
											k = 19;
											break;
											
										case 0x09:	//����������Ϣ
											I2C_Read_Eeprom(ee_blerefer_page, ee_blerefer_inpage, OutBuf+1, ee_blerefer_lenth);
											
											k = 14;
											break;
											
										case 0x0A:	//�����㲥ʱ��
											I2C_Read_Eeprom(ee_blerefer_page, ee_blegbtime_inpage, OutBuf+1, ee_blegbtime_lenth);
											
											k = 2+1;
											break;
											
										case 0x0b:	//����ģ��ID	XXXXXXXXXXXX	6
											k = 7;
//											I2C_Read_Eeprom( ee_zbid_bk_page, ee_zbid_bk_inpage, OutBuf+1, ee_zbid_bk_lenth ); //��ԭ�ز�id����(ͨѶ����ר��)
											memcpy( OutBuf+1, Esam_Para.Zb_Id, 6 );
											break;	
										
										case 0xee:	//�̵�����բ����ʽ	XX	1
											k = 2;
											OutBuf[1] = Mode.Wz_Clocerelay;
											break;		
											
										default:
											break;
									}
									break;
									
								case 0x15:
									switch( DI07.B08[0] )
									{
										case 0x01:	 //�����ϱ�״̬��	NNNNNNNNNNNNNNNNNNNNNNNN	12+N
											k = Ready_Reportdata( OutBuf );
											Reset_Rep_Timer = Calculate_Timer(3);		//������λ�ϱ�״̬�ֶ�ʱ��
											break;
											
//										case 0x02:	 //�忨״̬��	NNNN	2	
//											k = 3;
//											OutBuf[1] = InsertCardSta;
//											OutBuf[2] = 0x00;
//											InsertCardSta = 0;	//��忨״̬��Ϊδ֪
//											break;
											
										default:
											break;
									}
									break;
									
								case 0x17:
									switch( DI07.B08[0] )
									{
										case 0x01:	//�۵緽	NNNNNNNN	4
										case 0x02:	//���緽	NNNNNNNN	4
										case 0x03:	//�õ�����		NNNNNNNNNNNNNNNN	8
										case 0x04:	//��Ӧ����ʱ�ε��	NNNNNNNNNNNNNNNN	8
										case 0xFF:	//����
											if( DI07.B08[0] == 0x01 || DI07.B08[0] == 0x02 )
											{
												Temp16.B08[0] = 0+(DI07.B08[0]-1)*4;	//ƫ�Ƶ�ַ
												Temp16.B08[1] = 4;	//�ֽ���
											}
											else if( DI07.B08[0] == 0x03 || DI07.B08[0] == 0x04 )
											{
												Temp16.B08[0] = 8+(DI07.B08[0]-3)*8;
												Temp16.B08[1] = 8;
											}
											else
											{
												Temp16.B08[0] = 0;
												Temp16.B08[1] = ee_buymessage_lenth;
											}
											
											I2C_Read_Eeprom( ee_buymessage_page, ee_buymessage_inpage+Temp16.B08[0], OutBuf+1, Temp16.B08[1] );
											k = Temp16.B08[1]+1;
											break;
											
										default:
											break;
									}
									break;	

								default:
									break;
							}
							break;

						case 0x01:	//��һ��ʱ�������ʱ�α�����
						case 0x02:	//�ڶ���ʱ�������ʱ�α�����
							//��ʱ������1������ʱ�α�����1������ʱ���� ��1������������1����������������1��+г������������1��+��������1������Կ����1����crc��2��
							if( DI07.B08[2] == 0x01 )
							{
								Temp16.B08[0] = ee_shiqu1_page;
								Temp16.B08[1] = ee_shiduantable1_1_page;
							}
							else
							{
								Temp16.B08[0] = ee_shiqu2_page;
								Temp16.B08[1] = ee_shiduantable2_1_page;
							}

							switch( DI07.B08[1] )
							{
								case 0x00:
									switch( DI07.B08[0] )
									{
										case 0x00:	//��һ��ʱ��������, ��1~14ʱ����ʼ���ڼ���ʱ�α��(14*3), MMDDNN
											Temp32.B08[0] = Bcd_To_Hex(Feik.Num[0]);	//�趨��"��ʱ����"
											if( Temp32.B08[0] > MAXREGION )
											{
												Temp32.B08[0] = MAXREGION;
											}

											I2C_Read_Eeprom( Temp16.B08[0], 0x00, Buf, ee_shiqu_lenth );
											
											k = Temp32.B08[0]*3+1;
											memcpy( OutBuf+1, Buf, k-1 );
											break;
											
										default:
//											Temp32.B08[0] = Bcd_To_Hex(Feik.Num[1]);	//�趨��"��ʱ�α���"
//											if( Temp32.B08[0] > MAXSIDUANTB )
//											{
//												Temp32.B08[0] = MAXSIDUANTB;
//											}
				
											Temp32.B08[1] = Bcd_To_Hex(Feik.Num[2]);	//�趨��"��ʱ����"
											if( Temp32.B08[1] > MAXSIDUAN )
											{
												Temp32.B08[1] = MAXSIDUAN;
											}
				
											if( DI07.B08[0] <= MAXSIDUANTB )	//��ȡ����ʱ�α�Ų��ܳ����趨��"��ʱ�α���"
											{
												I2C_Read_Eeprom( Temp16.B08[1]+(DI07.B08[0]-1), 0x00, Buf, ee_shiduantable_lenth );
	
												k = Temp32.B08[1]*3+1;
												memcpy( OutBuf+1, Buf, k-1 );
											}
											break;
									}
									break;
									
								default:
									break;
							}
							break;

						case 0x07:	//��ǰ�׽���ʱ���������׽���ʱ����
//							if( !BDMODE ) break; //Զ��ģʽ
								
							if( (DI07.B08[1]!=0x00) || (DI07.B08[0]>0x01) ) break; //����ʱ�����ܳ���2��

							I2C_Read_Eeprom( ee_jtshiqu1_page+DI07.B08[0], ee_jtshiqu_inpage, OutBuf+1, ee_jtshiqu_len );
							
							k = 12+1;
							break;
							
						case 0x03:	//��n �����������ڼ���ʱ�α��
//							ReadE2WithBackup( ee_feik_number_page, ee_feiknumber_inpage, Buf, ee_feiknumber_lenth );

							switch( DI07.B08[1] ) 
							{
								case 0x00:
//									Temp32.B08[0] = Bcd_To_Hex(Buf[4]);	//�趨��"��ʱ����"
//									if( Temp32.B08[0] > 14 )	//�������գ�1~14, YYMMDDNN, 4
//									{
//										Temp32.B08[0] = 14;
//									}
//		
//									if( (DI07.B08[0]) && (DI07.B08[0] <= Temp32.B08[0]) )	//��ȡ�Ĺ������ղ��ܳ����趨��"����������"
									if( (DI07.B08[0]) && (DI07.B08[0] <= MAXHOLIDAY) )		//��ȡ�Ĺ������ղ��ܳ����趨��"����������"
									{
										Temp16.B08[0] = (DI07.B08[0]-1)/15;
										Temp16.B08[1] = ((DI07.B08[0]-1)%15)*4;
										
										result = I2C_Read_Eeprom( ee_holiday_page+Temp16.B08[0], Temp16.B08[1], OutBuf+1, 4 );
										if( result != 0x00 ) break;
											
										k = 5;
									}
									break;
									
								default:
									break;
							}
							break;							
							
						case 0x04:
							switch( DI07.B08[1] )
							{
								case 0x01:	//�Զ�ѭ��
								case 0x02:	//����ѭ��
									//ѭ������(1)��ѭ��ʱ��(1)������С��λ��(1)������λ��(1)����������(1)��������(1)+ ��բ��ʱʱ��(2)��crc(2)
									if( (DI07.B08[0]) && (DI07.B08[0]<=SCREENNUM) )
									{
										n = (DI07.B08[1]-1)%2;
										i = (DI07.B08[0]-1)/31;
										if( i != 3 ) Temp08 = ee_displayitem_lenth;
										else Temp08 = ee_displayitem_lenth1;
										
										I2C_Read_Eeprom( ee_loop_displayitem_page+2*i+n, 0x00, Buf, Temp08 );
										Temp16.B08[0] = Buf[((DI07.B08[0]-1)%31)*2+0];
										Temp16.B08[1] = Buf[((DI07.B08[0]-1)%31)*2+1];
										
										//���,����,����,����޹�1/2,��һ�����޹�����~���������޹�����
										if( (Temp16.B16 <= 0x200+max_disploop*9) && (Temp16.B16 > 0x200) )
										{
											Temp16.B16 -= 0x200;
																							
											k = 6;
											OutBuf[3] = (Temp16.B16-1)/max_disploop;
											OutBuf[1] = (Temp16.B16-1-max_disploop*OutBuf[3])/(max_feilvcount+1);//0:��ǰ; 1~12����
											OutBuf[2] = (Temp16.B16-1)%(max_feilvcount+1);
											OutBuf[4] = 0x00;
											OutBuf[5] = 0x00;
										}
										else if( (Temp16.B16 <= 0x800+max_disploop*9) && (Temp16.B16 > 0x800) )
										{
											Temp16.B16 -= 0x800;
																							
											k = 6;
											OutBuf[3] = (Temp16.B16-1)/max_disploop;
											OutBuf[1] = (Temp16.B16-1-max_disploop*OutBuf[3])/(max_feilvcount+1);//0:��ǰ; 1~12����
											OutBuf[2] = (Temp16.B16-1)%(max_feilvcount+1);
											OutBuf[3]+= 0x70;	//�߾���	
											OutBuf[4] = 0x00;
											OutBuf[5] = 0x00;
											
											if( OutBuf[3] == 0x70 )  OutBuf[3] = 0x68;//�߾�����ʾ����
											else OutBuf[3] -= 0x11;
										}
										//------ ������ʾ��Ŀ����Ŵ�200��ʼ--------
										else if( Temp16.B16 >= 200 )
										{
											result = Temp16.B16- 200;
											Temp08 = disp_num;	//disp_table�����ܼ���ʾ��Ŀ��
											if( result < Temp08 )
											{
												Temp32.B32 = disp_table[result];
												for( n=0; n<=result; n++ )
												{
													if( Temp32.B32 != disp_table[result-n] ) break;
												}
												
												if( result == 0 )
													result = 0xff;		//ȫ����ʾ
												else
													result = n-1;
											}
											else
											{
												Temp32.B32 = 0;
												result = 0;
											}

											k = 6;
											Exchange( OutBuf+1, Temp32.B08, 4 );
											OutBuf[5] = result;
										}
									}
									break;
								
								default:
									break;
							}
							break;

						case 0x06:	//��ǰ�׵�1�Ž��ݱ�~�����׵�1�Ž��ݱ�
//							if( !BDMODE ) break; //Զ��ģʽ
								
							//��һ�׵�1~n ����ֵ		NNNNNN.NN	4	kWh
							if( ((DI07.B08[1] != 0x06)&&(DI07.B08[1] != 0x07)&&(DI07.B08[1] != 0x0a)&&(DI07.B08[1] != 0x0b)) || (DI07.B08[0]!=0xFF) ) break;

							k = 71;
							ReadE2WithJieti( DI07.B08[1]-0x06, OutBuf+1 );//����ǰ���߱����׽��ݵ���/���/�����ʱ��
							for( i=0; i<13; i++ ) Inverse( OutBuf+1+4*i, 4 );
//							for( i=0; i< 6; i++ ) Inverse( OutBuf+1+52+3*i, 3 );
							break;

						case 0x09:
							switch( DI07.B08[1] )
							{
								case 0x01:
									switch( DI07.B08[0] )
									{
										case 0x01:	//ʧѹ�¼���ѹ�������� NNN.N	2	V
										case 0x02:	//ʧѹ�¼���ѹ�ָ����� NNN.N	2	V	
											k = 3;
											Exchange( OutBuf+1, VolLimit.Lost_V_Min.B08+(DI07.B08[0]-1)*2, 2 );					
											break;
											
										case 0x03:	//ʧѹ�¼�������������	NN.NNNN	3	A
											k = 4;
											Exchange( OutBuf+1, VolLimit.Lost_V_I.B08+1, 3 );	
											break;	
											
										case 0x04:	//ʧѹ�¼���ʱ�ж�ʱ��	NN	1	S
											k = 2;
											OutBuf[1] = VolLimit.Lost_V_Period;
											break;
											
										default:
											break;
									}
									break;
								
								case 0x08:
									switch( DI07.B08[0] )
									{
										case 0x01:	//�����¼�������������	NNN.N	2	A
											k = 3;
											OutBuf[1] = Week_Holiday.Max_I.B08[1];
											OutBuf[2] = Week_Holiday.Max_I.B08[0];						
											break;
											
										case 0x02:	//�����¼��ж���ʱʱ��	NN	1	S
											k = 2;
											OutBuf[1] = Week_Holiday.Max_I_Period;
											break;
											
										default:
											break;
									}
									break;
									
								case 0x0c:
									switch( DI07.B08[0] )
									{
										case 0x01:	//�ϸ��ʵ�ѹ��������ֵ	NNN.N	2	V
										case 0x02:	//�ϸ��ʵ�ѹ��������ֵ	NNN.N	2	V
											k = 3;
											Exchange( OutBuf+1, VolLimit.ChkMaxVol.B08+(DI07.B08[0]-1)*2, 2 );
											break;
											
										default:
											break;
									}
									break;	
									
								case 0x12:
									switch( DI07.B08[0] )
									{
										case 0x01:	//�͵�ѹ�¼���ѹ�������� NNN.N	2	V
											k = 3;
											Exchange( OutBuf+1, VolLimit.Lower_V.B08, 2 );					
											break;
										
										case 0x02:	//�͵�ѹ�¼���ʱ�ж�ʱ��	NNNN	2	MIN
											k = 3;
											Exchange( OutBuf+1, VolLimit.Lower_V_Period.B08, 2 );	
											break;
											
										default:
											break;
									}
									break;
									
								case 0x11: 
									switch( DI07.B08[0] )
									{
										case 0x01:	//�ߵ�ѹ�¼���ѹ�������� NNN.N	2	V
											k = 3;
											Exchange( OutBuf+1, VolLimit.High_V.B08, 2 );					
											break;
										
										case 0x02:	//�ߵ�ѹ�¼���ʱ�ж�ʱ��	NNNN	2	MIN
											k = 3;
											Exchange( OutBuf+1, VolLimit.High_V_Period.B08, 2 );	
											break;
											
										default:
											break;
									}
									break;	
									
								case 0x3f:
									switch( DI07.B08[0] )
									{	
										case 0x01:	//���ߵ�����ƽ������������	NN.NNNN	3	A
											k = 4;
											Exchange( OutBuf+1, Week_Holiday.NLine_I.B08+1, 3 );
											break;
										
										case 0x02:	//���ߵ�����ƽ����ֵ      long-unsigned����λ��%�����㣺-2��
											k = 3;
											Exchange( OutBuf+1, Week_Holiday.NLine_Limit.B08, 2 );	
											break;
											
										case 0x03:	//���ߵ�����ƽ��ʱ�ж�ʱ��        NN	1	S
											k = 2;
											OutBuf[1] = Week_Holiday.NLine_Period;
											break;
									}		
									break;	
									
								case 0x40:
									switch( DI07.B08[0] )
									{	
										case 0x01:	//���������ж���ʱ	NN	1	S
											k = 2;
											OutBuf[1] = VolLimit.Cal_Err_Period;	
											break;	
									}		
									break;
									
								case 0x43:
									switch( DI07.B08[0] )
									{	
										case 0x01:	//ͣ���¼��ж���ʱ	NN	1	S
											k = 2;
											OutBuf[1] = Mode.Powerd_Period;
											break;	
									}		
									break;	
									
								case 0x51:
									switch( DI07.B08[0] )
									{	
										case 0x01:	//�����ϱ��ϵ�ʱ��	NN	1	MIN
											k = 2;
											OutBuf[1] = Mode.Report_Period;
											break;	
									}		
									break;		

								default:
									break;
							}
							break;		

						case 0x80:
							switch( DI07.B08[1] )
							{
								case 0x00:
									switch( DI07.B08[0] )
									{
										case 0x01:	//��������汾��(ASCII ��)	NN��NN	32
										case 0x02:	//����Ӳ���汾��(ASCII ��)	NN��NN	32
										case 0x03:	//���ұ��(ASCII ��)		NN��NN	32
										case 0x04:	//���������			NN��NN	8	
											Temp08 = 32;//32�ֽ�
											if(DI07.B08[0] == 0x01)
											{
												Temp16.B08[0] = ee_softver_page;	//����汾��
												Temp16.B08[1] = ee_softver_inpage;
												Code_Flash_Char = (uint08*)SoftwareVer1;
											}
											else if(DI07.B08[0] == 0x02)
											{
												Temp16.B08[0] = ee_hardver_page;	//Ӳ���汾��
												Temp16.B08[1] = ee_hardver_inpage;
												Code_Flash_Char = (uint08*)HardwareVer1;
											}
											else if(DI07.B08[0] == 0x03)
											{
												Temp16.B08[0] = ee_factorynum_page;	//���ұ��
												Temp16.B08[1] = ee_factorynum_inpage;
												Code_Flash_Char = (uint08*)FactoryNum;
											}
											else
											{
												Temp16.B08[0] = ee_softbk_page; 	//���������
												Temp16.B08[1] = ee_softbk_inpage;
												Code_Flash_Char = (uint08*)Softbk;
												Temp08 = 8;//8�ֽ�
											}
											result = I2C_Read_Eeprom( Temp16.B08[0], Temp16.B08[1], OutBuf+1, Temp08 );
																						
											for( i=0; i<Temp08; i++ )	//���ȫ��Ϊ0xff�����Ĭ�ϵ�ֵ
											{
												if( OutBuf[1+i] != 0xff ) break;
											}
											
											if( result || (i==Temp08) )
											{
												Exchange( OutBuf+1, Code_Flash_Char, Temp08 );	
											}		  
											k = Temp08+1;
											break; 
										#if(1 == CHINT_Mode)
										case 0x10://��̩�ڲ��汾��										
											memcpy( OutBuf+1, &C_ucSoftVerForFactory[0], 8 );//���ذ汾��Ϣ									
											k = 9;
											OutBuf[0] = 0x00;
											break;	
										#endif														
												
												
										default:
											break;
									}
									break;
								
								default:
									break;
							}
							break;
						
						default: break;
					}
					break;
				
				case 0x05:	//��������
//					if( DI07.B08[2] > 7 ) break;
						
					k = ReadFreezedRec( DI07.B08[2], DI07.B08[1], DI07.B08[0], OutBuf );
					if( k == 0x00 ) break;
					
					k += 1;
					OutBuf[0] = 0x00;	//���
					break;
					
				case 0x0E:	//�����ڲ�Э��0x0E8000xx
					if( (DI07.B08[2] != 0x80) || (DI07.B08[1] != 0x00) ) break;
						
					switch( DI07.B08[0] )
					{
						case 0x01:	//��ȡ���ò���
							memset(OutBuf+1, 0, 25);
							Bcd2Hex_LS(Comm_Addr.Comm_Id, OutBuf+1, 6);
							OutBuf[6]  = 0xC0;
							
							I2C_Read_Eeprom(ee_bleslamac_page, ee_bleslamac_inpage, OutBuf+7, ee_bleslamac_lenth);//�ӻ�MAC��ַ
							I2C_Read_Eeprom(ee_blerefer_page, ee_blerefer_inpage, OutBuf+25, 1);//Tx_Power
							
							k = 25+1;
							break;
							
						case 0x02:	//�����ϱ�����״̬������Ӧ��
							for(i=0; i<5; i++)
							{
								if( (Ble_Connect[i].Ble_A2==Uart[Ch].Buf[14]) && (Ble_Connect[i].Ble_A3==Uart[Ch].Buf[15]) &&
										(Cmp_Bcd_Inv(Ble_Connect[i].Ble_Mac, Uart[Ch].Buf+17, 6) == 0) )	//�б������豸
								{
									if( Uart[Ch].Buf[16] == 0 )	//�Ͽ�����
									{
										memset(&Ble_Connect[i].Ble_A2, 0, 9);	//�������Ϣ
										memcpy(&Ble_Connect[i].Ble_A2, &Ble_Connect[i+1].Ble_A2, (4-i)*9);
										memset(&Ble_Connect[4].Ble_A2, 0, 9);	//�������Ϣ
									}
									break;
								}
								else if( Ble_Connect[i].Ble_A2 == 0 )
								{
									memcpy(&Ble_Connect[i].Ble_A2, Uart[Ch].Buf+14, 9);	//�����豸����״̬
									break;
								}
							}

//							Temp08 = 0xff;
//							for(i=0; i<5; i++)
//							{
//								if( Cmp_Bcd_Inv(Ble_Connect[i].Ble_Mac, Uart[Ch].Buf+17, 6) == 0 )	//�б����и��豸
//								{
//									Temp08 = 0xee;
//									if( Uart[Ch].Buf[16] == 0 )
//										memset(&Ble_Connect[i].Ble_A2, 0, 9);	//�ѶϿ����������Ϣ
//									else 
//										memcpy(&Ble_Connect[i].Ble_A2, Uart[Ch].Buf+14, 9);	//�����ӣ������豸������Ϣ
//									break;
//								}
//								else if( (Ble_Connect[i].Ble_A2 == 0) && Uart[Ch].Buf[16] )
//								{
//									if( Temp08  == 0xff ) Temp08 = i;
//								}
//							}
//							if( Temp08 < 5 )
//								memcpy(&Ble_Connect[Temp08].Ble_A2, Uart[Ch].Buf+14, 9);	//���������豸�������豸������Ϣ
							
							Uart[Ch].Overtime_Timer = 2;
							return;
							
						case 0x09:	//����/�˳������춨У��
							k = 1;
							break;
							
						default:
							break;	
						
					}
					
					break;
			
				default: break;
			}

			if( (Uart[Ch].Buf[9] != 0x04) && !ble_inter_flag ) //����������ϳ���(EEEEEENN)
			{
				if( (k == 0) || (OutBuf[0] == 0xFF) || ((4+k-1) > 190) ) k = 1;

				if( (Loop+1) < Times ) OutBuf[ k++ ] = 0xBB;
				
				if( ((3+k+Len+5) > sizeof(Uart[Ch].FrmBuf)) ) 
				{
					k = 0;
					Len = 0;
					break;
				}

				if( (Loop+1) < Times )
					Uart[Ch].FrmBuf[ Len++ ] = k+2; //����
				else
					Uart[Ch].FrmBuf[ Len++ ] = k+3; //����
				memcpy( Uart[Ch].FrmBuf+Len, DI08.B08, 4 ); //�ָ�
				Len += 4;
			}
			else
			{
				if( (k == 2) && (OutBuf[0] == 0xFF) ) break;
			}
			
			if( k == 0x00 )
			{
				OutBuf[ k++ ] = 0xFF;
				OutBuf[ k++ ] = 0x02;	//������Ϣ��ERR������������
				break;
			}

			memcpy( Uart[Ch].FrmBuf+Len, OutBuf+1, (k-1) );
			Len += (k-1);
		}

		if( Len )
		{
			Uart[Ch].FrmLen = Len;
			if( Uart[Ch].FrmLen <= 196 )
			{
				OutBuf[0] = Uart[Ch].FrmLen;
				Uart[Ch].Sn = 0;
				Uart[Ch].FrmLen = 0;
				Uart[Ch].FrmOffset = 0;
				memset( Uart[Ch].DI, 0, 4 );
			}
			else
			{
				OutBuf[0] = 196;
				Uart[Ch].Sn = 1;
				Uart[Ch].FrmLen -= 196;
				Uart[Ch].FrmOffset = 196;
				memcpy( Uart[Ch].DI, Uart[Ch].Buf+10, 4 );
				Remain = 1;
			}

			memcpy( OutBuf+1, Uart[Ch].FrmBuf, OutBuf[0] );
			
			k = OutBuf[0]+1;
			OutBuf[0] = 0x00;	//���
		}
		break;
				
		case 0x12:	//��ȡ����֡
			if( Uart[Ch].Flag&B0000_0001 ) break; //ͨѶ��ַȫ99   ��֧��
			if( Uart[Ch].Buf[9] != 0x05 ) break;	//Len error
			
			switch( DI07.B08[3] )
			{
				case 0x06:	//���ɼ�¼
					if( (((DI07.B08[2] == 0x10) || (DI07.B08[2] == 0x11)) && (DI07.B08[1] && (DI07.B08[1] <= 0x08)))
					||  (( DI07.B08[2] == 0x10) && ((DI07.B08[1] == 0x0C) || (DI07.B08[1] == 0x0D))) )
					{
						k = ReadLoadRec( Ch, Uart[Ch].Buf+8, OutBuf );
						if( k == 0 ) RdLoadPara[Ch][4] = 0;
						else if(RdLoadPara[Ch][4]) Remain = 1;
					}
					break;
					
				default:
					if( Uart[Ch].FrmLen == 0 ) break; //�޺���֡
					if( Cmp_Data(DI07.B08, Uart[Ch].DI, 4) != 3 ) break; //���ݱ�ʶ�������˳�
					if( Uart[Ch].Buf[14] != Uart[Ch].Sn ) break; //֡��Ų������˳�
					
					if( Uart[Ch].FrmLen <= 195 )
						OutBuf[0] = Uart[Ch].FrmLen;
					else
						OutBuf[0] = 195;
					Uart[Ch].FrmLen -= OutBuf[0];

					memcpy( OutBuf+1, Uart[Ch].FrmBuf+Uart[Ch].FrmOffset, OutBuf[0] ); //��䷵������

					if( Uart[Ch].FrmLen == 0 )
					{
						Uart[Ch].Sn = 0;
						Uart[Ch].FrmLen = 0;
						Uart[Ch].FrmOffset = 0;
						memset( Uart[Ch].DI, 0, 4 );
					}
					else
					{
						Uart[Ch].Sn += 1;
						Uart[Ch].FrmOffset += OutBuf[0];
						Remain = 1;
					}
					
					OutBuf[++OutBuf[0]] = Uart[Ch].Buf[14]; //֡���
					
					k = OutBuf[0]+1;
					OutBuf[0] = 0x00;
					break;
			}
			
			if( (k ==0) && ((Mode.Feature1&0x04)==0x04) && ChkBufZero( Report_Data, 5 ) )
			{
				Int2Byte( 0x01150004, DI07.B08 );
				
				//�����ϱ�״̬��	NNNNNNNNNNNNNNNNNNNNNNNN	12+N
				k = Ready_Reportdata( OutBuf );
				Reset_Rep_Timer = Calculate_Timer(3);		//������λ�ϱ�״̬�ֶ�ʱ��
				OutBuf[k++] = Uart[Ch].Buf[14];//����֡���
				memcpy( Uart[Ch].Buf+10, DI07.B08, 4 );//�����µı�ʶ
			}
			
			if( k == 0x00 )
			{
				OutBuf[ k++ ] = 0xFF;
				OutBuf[ k++ ] = 0x02;	//������Ϣ��ERR������������
			}
			break;

		case 0x13:	//��ͨ�ŵ�ַ, ��ַ�������ȫAAH
			//����������̼�¼����
			memset( Buf, 0xaa, 6 );
			if( (Cmp_Data( Buf, Uart[Ch].Buf+1, 6 ) !=3)	//��ȫaa	
				|| (Uart[Ch].Buf[9] != 0x00) )
			{
				Uart[Ch].Overtime_Timer = 2;
				return;
			}

			k = 7;
			Exchange( OutBuf+1, Comm_Addr.Comm_Id, 6 );
			break;

		case 0x15:	//дͨ�ŵ�ַ, ��ַ�������ȫAAH
			//����������̼�¼����
			if( ((Uart[Ch].Flag&B0000_0010) != B0000_0010)	//��ַ�������ȫAAH
				|| (!progenable) 							//��̰�����Ч,24hour��̽�ֹ��Ч
				|| (Uart[Ch].Buf[9] != 0x06) )				//���ݳ��Ȳ��Ϸ�
			{
				Uart[Ch].Overtime_Timer = 2;
				return;
			}
			
			Exchange( Buf, Uart[Ch].Buf+10, 6 );

			result = WriteE2WithBackup( ee_commaddr_page, ee_commaddr_inpage, Buf, ee_commaddr_lenth );	//д��E2PROM
			if( result )
			{
				Uart[Ch].Overtime_Timer = 2;
				return;
			}

			if( Cmp_Data(Comm_Addr.Comm_Id, Buf, 6) != 3 ) Ble_Rst_Judge(Ch);
				
			memcpy( Comm_Addr.Comm_Id, Buf, 8 );

			k = 1;
			break;

		case 0x08:	//�㲥Уʱ
			//����������̼�¼����
			if( ((Uart[Ch].Flag&B0000_0010) == B0000_0010) || (Uart[Ch].Buf[9] != 0x06) || ((Ch==CHBLE) && (Uart[Ch].Flag&B0000_0011)) ) //��֧����λ
			{
				Uart[Ch].Overtime_Timer = 2;
				return;
			}

			result = JudgeClockNoWeek( 0, &Uart[Ch].Buf[10], 6 );
			if( result != 0 ) //
			{
				break; //����
			}
			
			if( already_setclock_flag == 1 ) break; //������Уʱ, ��������Уʱ

			if( !clock_error )	//ϵͳʱ����ȷ
			{
				//----- ��������00:00:00�ġ�5min�ڹ㲥Уʱ------
				Buf[0] = 0x00;
				Buf[1] = 0x10;
				Buf[2] = 0x00;
				Temp08 = Cmp_Bcd_Inv( Buf, Sclock.Clockbackup, 3 );
				if( Temp08 == 1 ) break;	//��ǰʱ��С��00:05:00
	
				Buf[0] = 0x00;
				Buf[1] = 0x50;
				Buf[2] = 0x23;
				Temp08 = Cmp_Bcd_Inv( Buf, Sclock.Clockbackup, 3 );
				if( Temp08 == 2 ) break;	//��ǰʱ�����23:55:00
				
				//----- ������㲥Уʱ����5min����------
				result = Judge_Min_Space( Uart[Ch].Buf+10 );
				if( result  == 1 )//������㲥Уʱ����10min
				{
					if( G_Clockerr_Times == 0 )
					{
						if( ChkLastclockerrRcdTime() != 1 ) Note_Run_Event(ee_clockerrn_inpage); //ʱ�ӹ��Ͽ�ʼ��¼(ʱ�ӷǷ�)
						G_Clockerr_Times = 1;	//�����Ĺ㲥Уʱ���ϱ�־
					}
						
					k = 2; 
					OutBuf[0] = 0xFF;
					OutBuf[1] = 0x04;	//Error: bit2�������/δ��Ȩ
					break;
				}
				
				//------ �������ڽ����յġ�5min�ڹ㲥Уʱ -------
				ReadE2WithBackup( ee_histroyparameter_page, ee_histroyparameter_inpage, Buf, ee_histroyparameter_lenth );	//������ʱ��: ��ʱ
				for( i=0; i<9; i++ )
				{
					Buf[6] = 0x00; //����ʱ��
					Buf[7] = 0x00;
					if( i < 3 )
					{
						memcpy( Buf+8, Buf+2*i, 2 ); //Hour+Day
						Buf[10] = Sclock.Clockbackup[4];
					}
					else
					{
//						if( !BDMODE ) continue; //Զ��ģʽ
						memcpy( Buf+8, Price.Year_Ladder+3*(i-3), 3 );//Hour+Day+Month
					}
					Buf[11] = Sclock.Clockbackup[5];
					
					result = Judge_Min_Space( Buf+6 );
					if( result == 0 ) break;	//�������ڽ����յġ�5min�ڹ㲥Уʱ
				}

				if( result == 0 ) break;
			}

			memcpy( Buf+0, Uart[Ch].Buf+10, 3 );

			if( clock_error ) { Buf[3] = 0x00; }
			else { Buf[3] = Sclock.Clockbackup[6]; }

			memcpy( Buf+4, Uart[Ch].Buf+13, 3 );
			
			Buf[3] = (CalcAbsDay(Buf+2)+6)%7;	//������,��ʽΪ��+��+ʱ+��+��+��+��,��ʼ��ַ��,���տ�ʼ����

			result = Set_Rtc( 0, Buf, 7 );
			if( result != 0x00 ) break; //����ʱ��ʧ��

			already_setclock_flag = 1; //
			
			memcpy( Uart[Ch].Buf+10+6, Sclock.Clockbackup, 6 );	//Уʱǰʱ��(6)(��ʱ����)
			
			CommSetRtc_Adj();	//����ʱ�ӵ����������
			
			memcpy( Eeprom.Buffer, Uart[Ch].Buf+10+6, 6 );		//Уʱǰʱ��(6)
			memcpy( Eeprom.Buffer+6, Sclock.Clockbackup, 6 );	//Уʱ��ʱ��(6)
			DltoEepromBuf( 12 );					//���������+�������(8)
			Four_RpdltoEepromBuf( 12+8 );				//���������޹�(16)
			Event_Record( ee_gbsclockn_inpage );			//���㲥Уʱ��¼

			k = 1;
			break;

		case 0x16:	//��������
			//68+���+68+16+04+mmhhDDMM+CS+16
			if( Uart[Ch].Buf[9] != 0x04 )	//�����򳤶ȴ���
			{
				Uart[Ch].Overtime_Timer = 2;
				return;
			}

			Temp08 = 0x00; //����ʱ����99H�ĸ���
			for( n=0; n<4; n++ )
			{
				if( Uart[Ch].Buf[10+n] == 0x99 )
				{
					Temp08++;
				}
				else
				{
					if( Temp08 || JudgeClockNoWeek(1+n, &Uart[Ch].Buf[10+n], 1) ) //ǰһ�ֽ�Ϊ99H���ֽ�����, �򶳽�ʱ�����
					{
						break;
					}
				}
			}
			
			if( n < 4 )
			{
				break;
			}

			switch( Temp08 )
			{
				case 0x00:	//mmhhDDMM, ��ͨ����
				case 0x01:	//99DDhhmm��ʾ����Ϊ���ڶ�ʱ����
					if( Uart[Ch].Buf[12] > 0x28 )  break;		//ֻ����1~28�ն���
				case 0x02:	//9999hhmm��ʾ����Ϊ���ڶ�ʱ����
				case 0x03:	//999999mm��ʾ��СʱΪ���ڶ�ʱ����
					//���㶳����ʼʱ��(5)�����㶳��ʱ����(1)���ն���ʱ��(2)+ ��ʱ����ʱ��(4)+ crc��2��
					I2C_Read_Eeprom44( ee_freezeparameter_page, Buf, ee_freezeparameter_lenth );

					Exchange( Buf+8, Uart[Ch].Buf+10, 4 );

					result = I2C_Write_Eeprom44( ee_freezeparameter_page, Buf, ee_freezeparameter_lenth );
					if( result != 0x00 ) break;

					k = 1;
					break;
					
				case 0x04:	//99999999Ϊ˲ʱ����
					//˲ʱ����ʱ��(5)+˲ʱ���������й���������(5*4)+˲ʱ���ᷴ���й���������(5*4)+˲ʱ�����������(3)
					Freeze_Dl( ee_realtimefreeze1_page, ee_immedf_inpage );

					k = 1;
					break;
					
				default:
					break;
			}
			break;
			
		case 0x17:	//����ͨ������, ������
			//����������̼�¼����

			//Bit7   Bit6     Bit5    Bit4    Bit3    Bit2    Bit1   Bit0
			//38400bps 19200bps 9600bps 4800bps 2400bps 1200bps 600bps ����
			
			if( Uart[Ch].Flag&B0000_0011 )
			{
				k = 2; 
				OutBuf[0] = 0xFF;
				OutBuf[1] = 0x04;	//Error: bit2�������/δ��Ȩ
				break;
			}
			
			if( Uart[Ch].Buf[9] != 0x01 ) //�����򳤶Ȳ�Ϊ1, ����
			{
				Uart[Ch].Overtime_Timer = 2;
				return;
			}
			
			//0x01:�����ͺ����ڲ�����������//0x03/0x04/0x05:ͨ�ſ�1/2/3 ������������
			Temp08 = Ch*2+1;
			if( Ch == CHBLE) Temp08 = 4; 
			Temp08 = Set_Comm_Rate( Temp08, Uart[Ch].Buf[10] );
			if( Temp08 )
			{
				k = 2;
				OutBuf[0] = 0xFF;
				OutBuf[1] = 0x08;	//������Ϣ��ERR��ͨ�����ʲ��ܸ���(Bit3)
			}
			else
			{
				k = 2;
				OutBuf[1] = Uart[Ch].Buf[10];	//���ĺ�����
			}
			break;

		case 0x19:	//�����������
			k = 2;
			OutBuf[0] = 0xFF;	//Operation result.
			OutBuf[1] = 0x04; //Error: bit2�������/δ��Ȩ
			break;
			
		case 0x1A:	//�������, ��յ��ܱ��ڵ����������������¼���¼��������, �����������¼����ʱ�̺�����ǰ�ĵ�����
		case 0x1B:	//�¼�����, ��յ��ܱ��ڴ洢��ȫ���¼���¼����
			//������������̼����ʹ�á�����ִ��ʱ���ܱ�Ӧ��֤��������¼���¼������������Զ�������¼�����Ӧ����
			//����������̼�¼����
			if( !(Uart[Ch].Flag & B0000_0011) && progenable && (Uart[Ch].Buf[10] == 0x03) )//����ģʽ����ֱ������
			{
				Ic_Comm_RxBuf[0] = Uart[Ch].Buf[8];
				Exchange( Ic_Comm_RxBuf+8, Uart[Ch].Buf+18, 4 );	//�¼������ʶ
			}
			else
			{
				if( (Uart[Ch].Flag & B0000_0011) || (Uart[Ch].Buf[10] != KEYTYPE2) || (identity_prog_flag == 0) || hangup_comm_flag )	//��ȫ��֤��̱�־ ʧЧ
				{
					k = 2;
					OutBuf[0] = 0xFF; //���
					OutBuf[1] = 0x04; //Error: bit2�������/δ��Ȩ
					break;	//�������ܱ�ֻ֧��98��Զ�̿���
				}
				
				if( (Key_Status == 1) && (Uart[Ch].Buf[8] == 0x1A) ) //���ܱ��������ֻ�����ڲ�����Կ״̬��ִ��
				{
					k = 2;
					OutBuf[0] = 0xFF; //���
					OutBuf[1] = 0x04; //Error: bit2�������/δ��Ȩ
					break;	//�������ܱ�ֻ֧��98��Զ�̿���
				}
				
				if( Uart[Ch].Buf[8] == 0x1A ) //�������
					result = Decrypt( Ch, 0x93, 0x08 );
				else
					result = Decrypt( Ch, 0x93, 0x0c );
				if( result )
				{
					k = 0x00; 
					OutBuf[ k++ ] = 0xFF;
					OutBuf[ k++ ] = 0x04;
					break;
				}
				
				if( Uart[Ch].Buf[8] != Ic_Comm_RxBuf[0] ) break;
			}

			k = 2;
			OutBuf[0] = 0xFF; //���
			OutBuf[1] = 0x04; //Error: bit2�������/δ��Ȩ
			
			//��֤ͨ���������Ķ����ָ��ִ����Ӧ����
			if( Ic_Comm_RxBuf[0] == 0x1A )
			{
				MeterClear = 0x55aa;	//�������
			}
			if( Ic_Comm_RxBuf[0] == 0x1B )
			{
				Inverse( Ic_Comm_RxBuf+8, 4 );	//�¼������ʶ����
				memcpy( DI07.B08, Ic_Comm_RxBuf+8, 4 );	//�¼������ʶ

				if( DI07.B08[0] != 0xFF ) break;
				if( ((DI07.B08[3]&0x7f) == 0x03) && ((DI07.B08[2] == 0x70) || (DI07.B08[2] == 0x10)) && (DI07.B08[1] == 0x01) ) DI07.B08[1] = 0x00;//֧���¼���A���ѹ�ϸ���
//				if( ((DI07.B08[3]&0x7f) == 0x03) && ((DI07.B08[2] == 0x70) || (DI07.B08[2] == 0x10)) && (DI07.B08[1] <= 0x01) )break;//��֧���¼����ѹ�ϸ���
//				if( ((DI07.B08[3]&0x7f) == 0x03) && ((DI07.B08[1] == 0x02) || (DI07.B08[1] == 0x03)) && (DI07.B08[2] == 0xc0) )break;//��֧���¼���ͣ��ͳ��
				
				if( Byte2uInt(DI07.B08) == 0xFFFFFFFF ) ClrRecTimes( 0, 0x55 );//�嶳����¼���Чָ��(���������)
				else
				{
					DI07.B08[3] &= ~0x80;	//֧�ָ߾��ȱ�ʶ����
					if( (DI07.B08[3] == 0x10) || (DI07.B08[3] == 0x19) ||(DI07.B08[3] == 0x1D)||(DI07.B08[3] == 0x1E)||(DI07.B08[3] == 0x22)||
					   ((DI07.B08[3] == 0x03)&&((DI07.B08[2] == 0x11)||(DI07.B08[2] == 0x33))))	//����բ���⴦��
					{
						if( DI07.B08[3] == 0x22 )
						{
							if( DI07.B08[1] != 0x00 ) break;
						}
						else
						{
							if( DI07.B08[1] != 0xFF ) break;
						}
						
						i = Find_EventTable(DI07.B08+2);		//�ж��Ƿ��ҵ��Ϸ����ݱ�ʶ
					}
					else if( DI07.B08[3] == 0x03 )
					{
						i = Find_EventTable(DI07.B08+1);		//�ж��Ƿ��ҵ��Ϸ����ݱ�ʶ
					}
					else break;

					if( i != EventNum )
					{				
						i += ee_clearn_inpage;
						if( i < ee_powerdownn_inpage ) break; 
						if( i == ee_poweroffn_inpage || i==ee_poweronn_inpage ) i = ee_powerdownn_inpage; //�����ϱ��¼����ϵ��ϱ��¼�������¼�ͬԴ
						
						ClrRecTimes( i, 0x01 );
					}
					else
					{
						break;
					}
				}
					
				//�¼������¼
				//�洢��������ʱ���򣬵��ֽ���ǰ�����ֽ��ں�
				memcpy( Eeprom.Buffer+6, Uart[Ch].Buf+14, 4 );	//�����ߴ���(4)
				memcpy( Eeprom.Buffer+10, Ic_Comm_RxBuf+8, 4 ); 	//�¼��������ݱ�ʶ��(4)
				Event_Record( ee_cleareventn_inpage );
			}
			k = 1;
			OutBuf[0] = 0x00;
			break;

		case 0x1C:	//����բ������������	
			if( Uart[Ch].Buf[10] != KEYTYPE2 )	//�ж��Ƿ�Ϊ96������
			{
				if( (Uart[Ch].Flag & B0000_0011) || (Uart[Ch].Buf[9] != 16) || (Uart[Ch].Buf[10] != 0x03) ||
				    (!progenable && (((Uart[Ch].Buf[18] != 0x1b) && (Uart[Ch].Buf[18] != 0x1c)) || Veri_Psw( Uart[Ch].Buf+10 ))) )//����ģʽ����ֱ������բ�������ĺ�բ����/ֱ�Ӻ�բ
				{
					k = 2;
					OutBuf[0] = 0xFF; //���
					OutBuf[1] = 0x04; //Error: bit2�������/δ��Ȩ
					break;
				}
				else
				{
					memcpy( Ic_Comm_RxBuf,  Uart[Ch].Buf+18, 8 );//����2�ֽ����ݺ�6�ֽ���Ч��ֹʱ��
					result = JudgeEndClock();
					if(result)
					{
						k = 2;
						OutBuf[0] = 0xFF; //���
						OutBuf[1] = 0x04; //Error: bit2�������/δ��Ȩ
						break;
					}
					Temp08 = Ch;
				}
			}
			else
			{
				if( (Uart[Ch].Flag & B0000_0011) || (Ch == CHHW) || ((Ch == CHBLE) && (progenable==0)&&(IR_EnTimer == 0)) || (identity_prog_flag == 0) || hangup_comm_flag )	//��ȫ��֤��̱�־ ʧЧ
				{
					k = 2;
					OutBuf[0] = 0xFF; //���
					OutBuf[1] = 0x04; //Error: bit2�������/δ��Ȩ
					break;	//�������ܱ�ֻ֧��98��Զ�̿���
				}
                        	
				//P0��P2��Ч, ��Ч��֤
				//��N1~Nmд��ESAM�Ŀ��������ļ����н���, ���ܳɹ����Խ��ܺ��Ӧ�����������������ִ����Ӧ�Ŀ��Ʋ�����
				//Զ�̿������80fb060010+���ģ�
				//��ȡԶ�̿�����������ģ�00C00000��LC��Ҫ��ȡ���������ݳ��ȣ�Ϊ1 �ֽڵ�ʮ������������
				//68+���+68+1C+1C+98000000+00000000+����+cs+16
				//������д��ESAM 08�ļ�����: 04D6880014+����
				//N1Ϊ�����������ͣ�1AH������բ��1BH�����բ����2AH��������2BH�����������3AH�����磬3BH����������
				//N2������
				//N3��N8����������Ч��ֹʱ�䣬���ݸ�ʽΪssmmhhDDMMYY�������ǰʱ���Ѿ��������ʱ��ʱ�����������Ϊ��Ч������ִ��
				
				Temp08 = Ch+0x20;
			}
			
			//��֤ͨ���������Ķ����ָ��ִ����Ӧ����
			result = Relay_Ctrl(Temp08);
			if(result)
			{
				k = 2;
				OutBuf[0] = 0xFF; //���
				OutBuf[1] = 0x04; //Error: bit2�������/δ��Ȩ
			}
			else k = 1;
			
			break;
			
		case 0x1D:	//�๦�ܶ��������������, �����̼���Ϻ�������֤, ���ܱ���ʹ�ù����У������������ϵ����ʱ�����ܶ��ӵ�ǰ��������źž��ָ������ź������
			if( Uart[Ch].Buf[9] != 0x01 )	//�����򳤶ȴ���
			{
				Uart[Ch].Overtime_Timer = 2;
				return;
			}
			
			switch( Uart[Ch].Buf[10] )
			{
				case 0x00:	//ʱ��������
				case 0x02:	//ʱ��Ͷ��
				case 0x03:	//�޹�����
				case 0x06:	//�й�����
					Outputtype = Uart[Ch].Buf[10];
					reg_veri_flag = 1;
					k = 2;
					OutBuf[1] = Uart[Ch].Buf[10];
					break;
					
				default:
					break;
			}
			break;
			
		//--------------------- ��չ������ -------------------------------
		#if(0 == CHINT_Mode)
		case 0x1E://��չ����			
			if( Uart[Ch].Buf[ 10 ] == 5 )//��չ��������ee
			{
				Temp16.B08[0] = Uart[Ch].Buf[ 11 ];		//Di1
				Temp16.B08[1] = Uart[Ch].Buf[ 12 ];		//Di2
				
				Temp08 = 68;
				if( (Uart[Ch].Buf[ 9 ] == 5) && progenable )	//������֧�ָ�������Ƿ���ַ�����ܻḴλ��
				{					
					Temp32.B08[0] = Uart[Ch].Buf[ 11 ];		//Di1
					Temp32.B08[1] = Uart[Ch].Buf[ 12 ];		//Di2
					Temp32.B08[2] = Uart[Ch].Buf[ 13 ];
					Temp32.B08[3] = Uart[Ch].Buf[ 14 ];
					
					if( Uart[Ch].Buf[ 14 ] == 0x00 )//��ʾ��չ��flash(0x00000000~0x00080000)
					{
						if(Temp32.B32 + 64>PROGRAMEND1)
						{
							break;
						}
					}
					else if( Uart[Ch].Buf[ 14 ] == 0x20 )	//��ʾ��չ��ram(0x20000000~0x20010000)
					{
						if((Temp32.B32 + 64)>(int)&__heap_limit)
						{
							break;
						}	
					}
					else if( (Uart[Ch].Buf[ 14 ] == 0x40 ) && (Uart[Ch].Buf[ 13] == 0x00 ) )//��ʾ��չ���Ĵ���AHB(0x40000000~0x40008000)
					{
						if( (Temp32.B32 + 64)>0x40008000 )
						{
							break;
						}
					}
					else if( (Uart[Ch].Buf[ 14 ] == 0x40 ) && (Uart[Ch].Buf[ 13] == 0x01 ) )//��ʾ��չ���Ĵ���APB(0x40010000~0x40018000)
					{
						if( (Temp32.B32 + 64)>0x40018000 )
						{
							break;
						}
					}
					else if( Uart[Ch].Buf[ 14 ] == 0xe0 )	//��ʾ��չ��ppb(0xe0000000~0xe0100000)
					{
						if((Temp32.B32 + 64)>0xe0100000)
						{
							break;
						}
					}
					else
					{
						break;
					}
					
					memcpy( Uart[Ch].Buf+14, (unsigned char near *)Temp32.B32, 64 );
				}
				else if( Uart[Ch].Buf[ 13 ] == 0x81 ) //��ʾ��չ��ȡ�ⲿFLASH
				{
					if( Flash_Rd_Bottom( Temp16.B16/64, (Temp16.B16%64)*64, Uart[Ch].Buf+14, 64 ) )
					{
						memset( Uart[Ch].Buf+14, 0x55, 64 );
					}
				}
				else if( Temp16.B16==0xeeee )
				{
					memset(Uart[Ch].Buf+14, 0x00, 14);
					if( Relay_Mode != 0x55 ) memcpy( Uart[Ch].Buf+14, "YC-NZ-", 6 );
					else memcpy( Uart[Ch].Buf+14, "YC-WZ-", 6 );					
					memcpy( Uart[Ch].Buf+14+8, Verdate, 24 );//���ذ汾��Ϣ
					Uart[Ch].Buf[14+32] = 0xaa;
					Uart[Ch].Buf[14+33] = clkmode;		//1��ƵΪ8M��ʱ��,2��ƵΪ4M��ʱ��
					Uart[Ch].Buf[14+34] = *(uint08*)0x1FFFFC0E;//0x04 ����404
					Uart[Ch].Buf[14+35] = Correction_Mode;	//0x55-������ѹ��������,����-�ر�(Ŀǰ��rn8209c֧��)
					Uart[Ch].Buf[14+36] = 0xaa;
					Uart[Ch].Buf[14+37] = 0xaa;
				}
				else if( Temp16.B16==0xfefe )
				{
					memset( Uart[Ch].Buf+14, 0x00, 64 );
					memcpy( Uart[Ch].Buf+14, (uint08*)0x1FFFFC10, 9 );
					
				}
				else if( Temp16.B16<0x400 )
				{
					if( Temp16.B16 < 0x100 ) Temp08 = Uart[Ch].Buf[13];
					else Temp08 = 128+4;
					I2C_Read_Bottom( Temp16.B16, 0, Uart[Ch].Buf+14, Temp08 );
					if( Temp16.B16 < 0x100 ) Temp08 = 68;
					
					if((Temp16.B16==0x0022)||(Temp16.B16==0x0023))	//����Ŀǰ��У�����
					{
						for(Temp16.B16=0;Temp16.B16<(Uart[Ch].Buf[13]/4);Temp16.B16++)
						{
							Inverse(Uart[Ch].Buf+14+(Temp16.B16<<2),4);
						}
					}
					if(Temp16.B16==0x002a)
					{
						memcpy(Uart[Ch].Buf+14, (uint08*)(&RTC_RT.TAdc), ee_ptatvalue_lenth);				
					}
					if(Temp16.B16==0x002b)
					{
						memcpy(Uart[Ch].Buf+14, (uint08*)(&RTC_RT.TVal), ee_ptatvalue_lenth);				
					}
				}
				else
				{
					break;
				}
				
				Uart[Ch].Buf[ 9 ] = Temp08;
				Uart[Ch].Buf[ Temp08+11 ] = 0x16;
				
				memcpy( Uart[Ch].TxBuf, Uart[Ch].Buf, Uart[Ch].Buf[9]+12 );
				Uart[Ch].Transfer = 1;
				Uart[Ch].Flag |= B0000_1000;//��Լ�������׼���������ݱ�־
				return;
			}
			break;		
		#endif
			
		#if(1 == CHINT_Mode)		
		case 0x1E://��չ����			
			if((Uart[Ch].Buf[10] == 0xff) && (Uart[Ch].Buf[11] == 0xff) && (Uart[Ch].Buf[12] == 0xff) && (Uart[Ch].Buf[13] == 0xff))
			{
				if((Uart[Ch].Buf[ 9 ] == 0x09) && (Uart[Ch].Buf[ 14 ] == 0x1A))			//дI_J�̽�ʱ��
				{					
					for( i=0; i<4; i++ ) //���ݱ�ʶ
					{
						Temp32.B08[i] = Uart[Ch].Buf[ 18-i ];
					}					
					if(COVKEY_N)///*�ϸ�״̬������������I_J��Чʱ��*///
					{
						if(Byte2uInt(Temp32.B08) != 0) break;
					}
					
					if( Key_Status == 1) break;	///*��̩CHINT ���� ˽Կ����������*///
						
					if(Byte2uInt(Temp32.B08) > 0xa8c0) break;	//��������720Сʱ
					
					memcpy( Ijtimer_Para.Ijtimer.B08,Temp32.B08, 4 );

					I2C_Write_Eeprom(ee_softij_page, ee_softij_inpage, Ijtimer_Para.Ijtimer.B08, 4);	
					
					k = 1;
					OutBuf[0] = 0x00;
					break;
				}
				else if((Uart[Ch].Buf[ 9 ] == 0x09) && (Uart[Ch].Buf[ 14 ] == 0x1B))			///*����I_Jʱ��*///
				{
					
					I2C_Read_Eeprom( ee_softij_page, ee_softij_inpage, Uart[Ch].Buf+15, 4);
					k = 10;
					OutBuf[0] = 0x00;
					memcpy(&OutBuf[1], &Uart[Ch].Buf[10], 5 );
					Exchange( &OutBuf[6], &Uart[Ch].Buf[15], 4 );
					break;
				}
				else if( (Uart[Ch].Buf[ 9 ] == 0x0a) && (Uart[Ch].Buf[ 19 ] <= 64) &&( Uart[Ch].Buf[14] < 0x03 ) )	//��ȡRAM��EE����
				{
					memcpy(&OutBuf[1], &Uart[Ch].Buf[10], 4);
					
					Temp16.B08[1] = Uart[Ch].Buf[ 15 ];		//���ֽ�
					Temp16.B08[0] = Uart[Ch].Buf[ 16 ];		//���ֽ�
					Temp32.B08[3] = Uart[Ch].Buf[ 15 ];		//Di1
					Temp32.B08[2] = Uart[Ch].Buf[ 16 ];		//Di2
					Temp32.B08[1] = Uart[Ch].Buf[ 17 ];
					Temp32.B08[0] = Uart[Ch].Buf[ 18 ];
					
					/* ��RAM */
					if(Uart[Ch].Buf[14]==0x00)
					{																
//						memcpy(&OutBuf[5], (uint08 xdata *)(Byte2uInt(Temp32.B08)), Uart[Ch].Buf[ 19 ]);
						memcpy(&OutBuf[5], (uint08 *)(Byte2uInt(Temp32.B08)), Uart[Ch].Buf[ 19 ]);
				
						k = Uart[Ch].Buf[ 19 ] + 5;
						OutBuf[0] = 0x00;
					}
					/* ��E2 */
					else if(Uart[Ch].Buf[14]==0x01)
					{												
						if( Byte2uShort(Temp16.B08) < 0x0400 )/*����ַ*/
						{							
//							I2C_Read_Eeprom ( Temp16.B16, 0, &OutBuf[5], Uart[Ch].Buf[19]);
							I2C_Read_Bottom( Byte2uShort(Temp16.B08), 0, &OutBuf[5], Uart[Ch].Buf[19]);											
							k = Uart[Ch].Buf[ 19 ] + 5;
							OutBuf[0] = 0x00;							
						}
					}
					/*��ROM*/
					else if(Uart[Ch].Buf[14]==0x02)
					{	
						memcpy(&OutBuf[5], (unsigned char ecode *)Byte2uInt(Temp32.B08), Uart[Ch].Buf[19] );
						k = Uart[Ch].Buf[ 19 ] + 5;
						OutBuf[0] = 0x00;	
					}
						
				}
//				else if((Uart[Ch].Buf[ 9 ] == 0x09) && (Uart[Ch].Buf[ 14 ] == 0x3B))	///*��̩CHINT ���� д���ɿ������û�����*///
//				{
//					
//					if(Byte2uInt(Ijtimer_Para.Ijtimer.B08) == 0)	///*��I_J��Ч����������*///
//					{
//						k = 2;
//						OutBuf[0] = 0xFF; //���
//						OutBuf[1] = 0x04; //Error: bit4�������/δ��Ȩ
//						break;
//					}			
//
//					result = I2C_Write_Eeprom( ee_Relay_Mode_page, ee_Relay_Mode_inpage, Uart[Ch].Buf+15, ee_Relay_Mode_lenth );
//					if( result != 0x00 ) break;
//					Relay_Mode = Uart[Ch].Buf[15];
//						
//					k = 1;
//					OutBuf[0] = 0x00;
//					break;
//				}
			}
			
			break;
		#endif  ///*�Ͻ�#if(1 == CHINT_Mode)*///

		case 0x1F://��չ����	
			if( (Ch == CHZB) && (Uart[Ch].Buf[ 9 ] == 11) && (Byte2uInt(Uart[Ch].Buf+10) == 0x05070004 ) ) //�ز�������Э��
			{	
				if( Uart[Ch].Flag&B0000_0011 )
				{
					k = 2; 
					OutBuf[0] = 0xFF;
					OutBuf[1] = 0x04;	//Error: bit2�������/δ��Ȩ
					break;
				}
				
				Temp08 = Set_Comm_Rate( 0x85, Uart[Ch].Buf[20] ); //�ز�������Э��
				if( Temp08 )
				{
					k = 2;
					OutBuf[0] = 0xFF;
					OutBuf[1] = 0x08;	//������Ϣ��ERR��ͨ�����ʲ��ܸ���(Bit3)
					break;
				}
							
				if( Cmp_Data( Esam_Para.Zb_Id, Uart[Ch].Buf+14, 6 ) != 3 )
				{
					memcpy( Buf, Esam_Para.Zb_Id, 6 );
					memset( Buf+6, 0xff, 6 );
					
					Inverse( Uart[Ch].Buf+14, 6 );	//��֤д������ee���ֽ���ǰ
					UpdateSysPara( 0x40+18, Uart[Ch].Buf+14, 6 ); //����ģ��id
					
//					I2C_Write_Eeprom( ee_zbid_bk_page, ee_zbid_bk_inpage, Esam_Para.Zb_Id, ee_zbid_bk_lenth ); //дԭ�ز�id����(ͨѶ����ר��)
										
					if( Cmp_Data( Buf, Buf+6, 6 ) != 3 ) //ԭ���ͨ��ID��ȫff
					{
						//�����ĵ���Ҫ��¼ģ�������¼
						Note_Run_Event(ee_commchangen_inpage);	//��¼ͨ��ģ�������¼
						
						commmodule_open_flag = 0;
						Store_Meterstatus();
						
						Note_Run_Event(ee_commchangen_inpage|0x80);	//��¼ͨ��ģ�������¼
					}
				}
				
				k = 1;
				break;
			}
			
			#if(0 == CHINT_Mode)
			if( (Ch == CHZB) && (Uart[Ch].Buf[ 10 ]!=0xAF) ) break;	//�������֧���ز�ͨ��
			#endif
			
			
			switch( Uart[Ch].Buf[ 10 ] )
			{
				case 0x13:	//��ʼ��ָ��
					if( (Ch == CHHW) || (Ch == CHBLE) || (!progenable) || ((Cover.Status == 0)&&((Fwdl.Pluse[0].B32>=10000*Meter.Const_H)||(Bkdl.Pluse[0].B32>=10000*Meter.Const_H))) )
					{
						k = 2;
						OutBuf[0] = 0xFF; //���
						OutBuf[1] = 0x04; //Error: bit4�������/δ��Ȩ
						break;
					}
					
					if( (Uart[Ch].Buf[11] == 0x14)&&(Uart[Ch].Buf[12] == 0x54)&&(Uart[Ch].Buf[13] == 0x80) )
					{
						MeterClear = 0x88bb;
						
//						Clear_Meter( Ch, Uart[Ch].Buf+10 );
//						Factory_Init();
						
						k = 1;
					}
					break;
					
				case 0x0f:	//�����̿��ؿ���ָ��
					#if(1 == CHINT_Mode)	
					if(Byte2uInt(Ijtimer_Para.Ijtimer.B08) == 0)	//��I_J��Ч����������
					{
						break;
					}
					#endif		
					
					if( Uart[Ch].Buf[9] != 0x03 ) break;//���ݳ��ȴ���
					
					if( Uart[Ch].Buf[11] == 0xaa )
					{
						Progkey.Timer = 0;	//�����̽�ֹ
					}
					else if(  Uart[Ch].Buf[11] == 0x55 )
					{
						if( (Key_Status==1) && (esam_error==0) ) break;	//����esam�������˽Կ����������
						else	
							Progkey.Timer = Uart[Ch].Buf[12];	//������ʹ��
					}
					else if( Uart[Ch].Buf[11] == 0xee ) //����ʼ������ִ��״̬
					{
						k = 9;
						I2C_Read_Eeprom( ee_factoryinit_page, ee_factoryinit_inpage, OutBuf+1, ee_factoryinit_len );
						Inverse( OutBuf+1, 2 );
						
						OutBuf[3] = 0x00; //���������ܶ�
						if( FlashID_Comm( Buf ) ) OutBuf[3] = 0xff;	//��flash����ʧ��
						else
						{
							if( Buf[2] == 0x15 ) OutBuf[3] = 0x16;
							else if( Buf[2] == 0x16 ) OutBuf[3] = 0x32;
							else if( Buf[2] == 0x17 ) OutBuf[3] = 0x64;
							else if( Buf[2] == 0x18 ) OutBuf[3] = 0x28; //128M
							else if( Buf[2] == 0x19 ) OutBuf[3] = 0x56; //256M	
						}
						break;
					}
					else
					{
						break;		//�Ƿ�����
					}
					
					k = 1;
					break;	
			
				case 0x03:
					//�����¶����ߵĲ���˵����
					//0 �����¶�б��΢�� //1 �����¶�б��΢��
					//2 ���¾�������΢���������޵����κ���ϵ����x*0.0001
					//3 ���¾�������΢���������޵����κ���ϵ����x*0.0001
					//4 ���¶����Уֵ����ֵ
					//9 ����25+��������΢��������25+�޵����κ���ϵ����x*0.0004 krh
					//10����25-��������΢��������25-�޵����κ���ϵ����x*0.0004 krl
					//9 ���¶����Уֵ����ֵ(ppm)(�µ�У)
					//10���¶����Уֵ����ֵ(ppm)(�µ�У)
					#if(1 == CHINT_Mode)
					if(Ijtimer_Para.Ijtimer.B32 == 0)	//��I_J��Ч������
					{
						k = 2;
						OutBuf[0] = 0xFF; //���
						OutBuf[1] = 0x04; //Error: bit4�������/δ��Ȩ
						break;
					}	
					#endif
					if( (Ch == CHHW) || (Ch == CHBLE) ) break;//��ֹ�������
					if( Uart[Ch].Buf[9] != 0x0a ) break;//���ݳ��ȴ���
					if( (Wr_Ext_Number == 50)&&(!progenable) ) break;
					else if ( Wr_Ext_Number > 50 ) Wr_Ext_Number = 25;
					else Wr_Ext_Number++;
					
					Temperpara_Verify();	//�¶�ϵ��У��
					memcpy( Buf, Tpara.Offset, ee_temperature_lenth );//�����¶�ϵ��
					
					if( Uart[Ch].Buf[19] == 0x00 )//ȫ������
					{
						memcpy( Buf+2, Uart[Ch].Buf+16, 3 );
					}
					else if( Uart[Ch].Buf[19] == 0x55 )//���¸����¶�ϵ��
					{
						Buf[2]=Uart[Ch].Buf[16];
					}
					else if( Uart[Ch].Buf[19] == 0x5a )//���µ����¶�ϵ��
					{
						Buf[3]=Uart[Ch].Buf[17];
					}
					else if( Uart[Ch].Buf[19] == 0xaa )//���µ�Уֵ
					{
						Buf[4]=Uart[Ch].Buf[18];
					}
					else if( Uart[Ch].Buf[19] == 0x05 )//���¸����¶�ϵ��krh
					{
						Buf[9]=Uart[Ch].Buf[18];
					}
					else if( Uart[Ch].Buf[19] == 0x50 )//���µ����¶�ϵ��krl
					{
						Buf[10]=Uart[Ch].Buf[18];
					}									
					else	break;
//					if( (Buf[4]&0x7f) > 8 ) break;	//��Уֵ������ΧΪ0~8
//					if( (Buf[9]&0x7f) > 50 ) break;	//��Уֵ������ΧΪ0.0000~0.005(0~50)
//					if( (Buf[10]&0x7f) > 50 ) break;//��Уֵ������ΧΪ0.0000~0.005(0~50)
					result = WriteE2WithBackup( ee_temperature_page, ee_temperature_inpage, Buf, ee_temperature_lenth );
					if( result ) break;
					memcpy( Tpara.Offset, Buf, ee_temperature_lenth );//����ram�¶�ϵ��
					Crc_16Bits_Add2(Tpara.Offset, ee_temperature_lenth ); //CRC����
					RTC_RT.TempFlag = 0xff;//���²������
					Adcctrl.Timer=8;//���������¶�adc
					k = 1;
					break;
					
				case 0x04://���¶�ADC������
					k = 9;
					if( const_tx_flag == 0x3cc3 ) OutBuf[1] = 0xc3;	//0xc3��ʾ�¶ȵ�У��
					else	OutBuf[1] = (uint08)(const_tx_flag&0xff);	
					OutBuf[2] = Tpara.RtcTMode;	//��RTC��������ģʽ��0x55:����ģʽ��0xAA���²���ֵģʽ����������ͨģʽ
					
					if( RTC->ADSIGN&BIT0 )//��УֵС��0
					{
						Temp16.B16 = (uint16)((int16)RTC->ADJUST*-1);
					}
					else
					{
						Temp16.B16 = RTC->ADJUST;
					}
					OutBuf[3] = Temp16.B16;
					OutBuf[4] = Temp16.B16>>8;	//ʵ�ʲ���ֵ
					OutBuf[5] = Temperature_Adc;	//���¶�ADC����
					OutBuf[6] = Temperature_Adc>>8;
					OutBuf[7] = Fun_Para.Temper_M;	//�����¶�
					OutBuf[8] = Fun_Para.Temper_M>>8;
					break;

				case 0x07://����RTC��������ģʽ��0x55:����ģʽ��0xAA���²���ֵģʽ����������ͨģʽ
//				case 0x0a://д���¶����Уֵ��ͨ�ŵ�ʱ����
				case 0xa9://�ر��¶Ȳ�����ͨ�ŵ�ʱ����׼������ʱ����
				case 0xaa://д���¶����Уֵ��ͨ�ŵ�ʱ����(�·�2�ֽ��ռ�ʱ���,-10.0��~10.0��,����)
				case 0x0b://�����¶�ADC΢��
					//5 �����¶�ADC΢��
					//6 ���¶����УֵL��ͨ�ŵ�ʱ����
					//7 ���¶����УֵH��ͨ�ŵ�ʱ����
					//8 RTC��������ģʽ��0x55:����ģʽ��0xAA���²���ֵģʽ����������ͨģʽ
					#if(1 == CHINT_Mode)
					if(Ijtimer_Para.Ijtimer.B32 == 0)	//��I_J��Ч������
					{
						k = 2;
						OutBuf[0] = 0xFF; //���
						OutBuf[1] = 0x04; //Error: bit4�������/δ��Ȩ
						break;
					}	
					#endif
					
					if( (Ch == CHHW) || (Ch == CHBLE) || (!progenable)  ) break;//��ֹ�������,��̽�ֹ

					Temperpara_Verify();	//�¶�ϵ��У��
					memcpy( Buf, Tpara.Offset, ee_temperature_lenth );//�����¶�ϵ��
					if( Uart[Ch].Buf[ 10 ] == 0x07 )
					{
						if( (Uart[Ch].Buf[9] != 0x02)) break;//���ݳ��ȴ���,��̽�ֹ
						Buf[8] = Uart[Ch].Buf[11];
						RtcStopProcFlag = 0x00;//��RTC�¶Ȳ�������
					}
//					else if( Uart[Ch].Buf[ 10 ] == 0x0a )
//					{
//						if( (Uart[Ch].Buf[9] != 0x02)||(const_tx_flag == 0x3cc3) ) break;	//�ձ�̵�У��
//						Buf[5] = Uart[Ch].Buf[11];	
//					}
					else if( Uart[Ch].Buf[ 10 ] == 0xa9 )//�ر��¶Ȳ�����ͨ�ŵ�ʱ����׼������ʱ����
					{
						if( (Uart[Ch].Buf[9] != 0x01)||(const_tx_flag == 0x3cc3) ) break;	//�ձ�̵�У��
						if( (Tpara.RtcTMode == 0x55)||(Tpara.RtcTMode == 0xAA) ) break;//��ֹ�ر�rtc����
						RtcStopProcFlag = 0x55;//�ر�RTC�¶Ȳ�������
						Adcctrl.Timer=8;//���������¶�adc
						k = 1;
						break;
					}
					else if( Uart[Ch].Buf[ 10 ] == 0xaa )//(�·�2�ֽ��ռ�ʱ���,����)
					{
						if( (Uart[Ch].Buf[9] != 0x03)||(const_tx_flag == 0x3cc3)||(RtcStopProcFlag!=0x55)) break;	//�ձ�̵�У��
						
						Temp16.B08[0] = Uart[Ch].Buf[ 11 ];
						Temp16.B08[1] = Uart[Ch].Buf[ 12 ];
						if( ((int16)Temp16.B16 > 10000) || ((int16)Temp16.B16 < -10000) ) break;	//���ơ�10.000��
						Temp16.B16 = Get_RTCTop_Proc( Temp16.B16 );	//���㶥���Уֵ
						Buf[6] = Temp16.B08[0];
						Buf[7] = Temp16.B08[1];
						RtcStopProcFlag = 0x00;//��RTC�¶Ȳ�������
						Buf[4] = 0;//��΢��ֵ
						if( Buf[1] == 0 ) Buf[1] = 0x80;
					}
					else	////5 �����¶�ADC΢��
					{
						if( (Uart[Ch].Buf[9] != 0x02)||((Uart[Ch].Buf[11]&0x7F)>50) ) break;//�������������Χ
						Buf[5] = Uart[Ch].Buf[11];	
					}
					result = WriteE2WithBackup( ee_temperature_page, ee_temperature_inpage, Buf, ee_temperature_lenth );
					if( result ) break;	
					
					if( (Uart[Ch].Buf[ 10 ]&0x0f) == 0x0a )//д���¶����Уֵʱʱ���¼
					{
						I2C_Read_Eeprom( ee_rtcadj_time_page, ee_rtcadjtime_inpage, Buf, ee_rtcadjtime_lenth );
						Buf[0]++;//д���¶����Уֵ������1
						memcpy( Buf+1, Sclock.Clockbackup, 7 );//д���¶����Уֵʱʱ��
						memcpy( Buf+8, &Fun_Para.Temper_M, 2 );//д���¶����Уֵʱ�¶�
						Buf[7] = Uart[Ch].Buf[ 10 ];//ͨѶ��ʶ
						I2C_Write_Eeprom( ee_rtcadj_time_page, ee_rtcadjtime_inpage, Buf, ee_rtcadjtime_lenth );		
					}
					
					Tpara.Crc16.B08[0] += 1;
					temperpara_veri_flag = 1;
					RTC_RT.TempFlag = 0xff;//���²������
					Adcctrl.Timer=8;//���������¶�adc
					k = 1;
					break;

				case 0x06://�޸Ķ����Уֵ��ƫ����	NNNN	2
//				case 0x06://�·��ռ�ʱԭʼ���		NNNN	2	(�µ�У)	
					#if(1 == CHINT_Mode)
					if(Ijtimer_Para.Ijtimer.B32 == 0)	//��I_J��Ч������
					{
						k = 2;
						OutBuf[0] = 0xFF; //���
						OutBuf[1] = 0x04; //Error: bit4�������/δ��Ȩ
						break;
					}	
					#endif
					
					if( (Ch == CHHW) || (Ch == CHBLE) ) break;//��ֹ�������
 					if( (Uart[Ch].Buf[9] != 0x03)||(!progenable) ) break;//���ݳ��ȴ���,��̽�ֹ
 					if( Tpara.RtcTMode!=0x55 ) break;//���ڲ���ģʽ����Ч
					
					Temp16.B08[0] = Uart[Ch].Buf[11];
					Temp16.B08[1] = Uart[Ch].Buf[12];
				#if( NEWCLOCKADJ == 0 ) //�ɱ�׼ʱ�ӵ�У
					if( (((int16)Temp16.B16)<-200)||(((int16)Temp16.B16))>200 ) break;//�����Уֵ��ƫ��������λΪ������С������0.238��0.119
				#endif
					RTC_RT.TestTrim = (int16)Temp16.B16;
					RTC_RT.TempFlag = 0xff;//���²������
					Adcctrl.Timer=8;//���������¶�adc
					k = 1;
					break;
					
				case 0x08://���ò���ֵ����
					#if(1 == CHINT_Mode)
					if(Ijtimer_Para.Ijtimer.B32 == 0)	//��I_J��Ч������
					{
						k = 2;
						OutBuf[0] = 0xFF; //���
						OutBuf[1] = 0x04; //Error: bit4�������/δ��Ȩ
						break;
					}	
					#endif
					
					if( (Ch == CHHW) || (Ch == CHBLE) ) break;//��ֹ�������
 					if( (Uart[Ch].Buf[9] != 85)||(!progenable) ) break;//���ݳ��ȴ���,��̽�ֹ
 					if( (Tpara.RtcTMode!=0x55) && (Tpara.RtcTMode!=0xAA) ) break;//���ڲ���ģʽ����Ч
					
				#if( NEWCLOCKADJ == 0 ) //�ɱ�׼ʱ�ӵ�У
					if( const_C_Mode != 0x55 ) break;//���ڲ���ģʽ����Ч

					//�����¶��Զ��ж�д�����ݵĵ�ַ
					//Temp16.B16 = Page
					//i = offset				
					//Temp08 = Len
					if( RTC_RT.TempFlag == 0 )//���²��
					{
						Temp16.B16 = ee_ptatvalue_page;
						i = ee_ptatvalue_inpage;
						Temp08 = ee_ptatvalue_lenth;
					}
					else if( RTC_RT.TempFlag == 1 )//���²��
					{
						Temp16.B16 = ee_ptatvalue_lt_page;
						i = ee_ptatvalue_lt_inpage;
						Temp08 = ee_ptatvalue_lt_lenth;
						
						Crc_16Bits_Add2(Uart[Ch].Buf+11, Temp08);
						Crc_16Bits_Add2(Uart[Ch].Buf+11+42, Temp08);
						Temp08 = Temp08+2;//����CRC��2�ֽ�
					}
					else if( RTC_RT.TempFlag == 2 )//���²��
					{
						Temp16.B16 = ee_ptatvalue_ht_page;
						i = ee_ptatvalue_ht_inpage;
						Temp08 = ee_ptatvalue_ht_lenth;
						
						Crc_16Bits_Add2(Uart[Ch].Buf+11, Temp08);
						Crc_16Bits_Add2(Uart[Ch].Buf+11+42, Temp08);
						Temp08 = Temp08+2;
					}
					else
					{
						break;
					}
			
//					result = I2C_Write_Eeprom( ee_ptatvalue_page, ee_ptatvalue_inpage, Uart[Ch].Buf+11, ee_ptatvalue_lenth );
//					result |= I2C_Write_Eeprom( ee_trimvalue_page, ee_trimvalue_inpage, Uart[Ch].Buf+11+42, ee_trimvalue_lenth );
					result = I2C_Write_Eeprom( Temp16.B16, i, Uart[Ch].Buf+11, Temp08 );
					result |= I2C_Write_Eeprom( Temp16.B16+1, i, Uart[Ch].Buf+11+42, Temp08 );
			
					if( result != 0x00 ) break;
				
//					I2C_Read_Eeprom( ee_ptatvalue_page, ee_ptatvalue_inpage, (uint08*)(&RTC_RT.TAdc), ee_ptatvalue_lenth );
//					I2C_Read_Eeprom( ee_trimvalue_page, ee_trimvalue_inpage, (uint08*)(&RTC_RT.TVal), ee_trimvalue_lenth );
				#else
					//�����¶��Զ��ж�д�����ݵĵ�ַ
					Temp16.B16 = ee_ptatvalue_page;
					i = ee_ptatvalue_inpage;
					Temp08 = ee_ptatvalue_lenth;
					
					result = I2C_Write_Eeprom( Temp16.B16, i, Uart[Ch].Buf+11, Temp08 );
					result |= I2C_Write_Eeprom( Temp16.B16+1, i, Uart[Ch].Buf+11+42, Temp08 );
			
					if( result != 0x00 ) break;
				#endif
					Fill_RTC_RT_TAdc();
					Fill_RTC_RT_TVal();
				
					Temperpara_Verify();	//�¶�ϵ��У��
					memcpy( Buf, Tpara.Offset, ee_temperature_lenth );//�����¶�ϵ��
					Buf[8] = 0xAA;//�·����ݺ��Զ�������ģʽ
					result = WriteE2WithBackup( ee_temperature_page, ee_temperature_inpage, Buf, ee_temperature_lenth );
					if( result ) break;	
					Tpara.Crc16.B08[0] += 1;
					temperpara_veri_flag = 1;
					RTC_RT.TempFlag = 0xff;//���²������
					Adcctrl.Timer=8;//���������¶�adc
					k = 1;
					break;
				
				case 0x09://�����¶����Уֵ��ͨ�ŵ�ʱ����
					k = 5;
					if( const_tx_flag == 0x3cc3 ) OutBuf[1] = 0xc3;	//0xc3��ʾ�¶ȵ�У��
					else	OutBuf[1] = (uint08)(const_tx_flag&0xff);	
					OutBuf[2] = Tpara.Offset[5];	//�����¶�ADC΢��
					OutBuf[3] = Tpara.Offset[6];	//���¶����УֵL
					OutBuf[4] = Tpara.Offset[7];	//���¶����УֵH
					break;
					
				case 0x14://ͣ�糬�����ݵ�ѹ	NNNNNNNN	4
					k = 5;
					memcpy( OutBuf+1, RAMBUF+12, 4 );
					break;	

				case 0x15://�����ۼӺ�	NNNNNNNN	4
					k = 5;
					Calculate_Program_Cs( OutBuf+1 );
					Inverse( OutBuf+1, 4 );
					break;
				
				case 0x16://�ز���λģʽ��(��չ)	NN	1
					k = 2;
					OutBuf[1] = Mode.Plc;
					break;
				
				case 0x17://�ز���λģʽ��(��չ)	NN	1
					if( Uart[Ch].Buf[9] != 0x02 ) break;//���ݳ��ȴ���
					if( Wr_Ext_Number == 50 ) break;
					else if ( Wr_Ext_Number > 50 ) Wr_Ext_Number = 25;
					else Wr_Ext_Number++;
					
					if( Uart[Ch].Buf[11] != Mode.Plc )//�����ı��д����ee
					{
						result = UpdateSysPara( 0x80+27, Uart[Ch].Buf+11, 1 );
						if( result != 0x00 ) break;
					}						
					k = 1;
					break;	
				
				case 0xAF:	//�����ز��������ַ�������¼���Ϣ
					if( (Uart[Ch].Flag&B0000_0001) && (Uart[Ch].Buf[9] == 0x02) && (Uart[Ch].Buf[11] == 0x02) )	//�㲥, Len=2
					{
						Uart[Ch].Flag &= B1111_1110;
						
						k = 9;
						OutBuf[1] = 0xAF;
						OutBuf[2] = 0x02;
						Exchange( OutBuf+3, Comm_Addr.Comm_Id, 6 );
					}
					break;
				
				default:
					break;
			}
			break;			
		
		#if(1 == CHINT_Mode)			
		case 0x2E:	///*��̩CHINT ����	������оƬ�Ĵ���*///
			if(Byte2uInt(Ijtimer_Para.Ijtimer.B08) == 0 )
			{
				k = 2;
				OutBuf[0] = 0xFF; //���
				OutBuf[1] = 0x04; //Error: bit4�������/δ��Ȩ
				break;
			}
			
			result = CommReadCalData(Ch);			
			if(result) break;
			
			k = 9;
			OutBuf[0] = 0x00;	
			OutBuf[8]= 0x00;		
			memcpy(&OutBuf[1], &Uart[Ch].Buf[10],4);						
			Exchange(&OutBuf[5], &Uart[Ch].Buf[21],3 );	
			break;
			
		case 0x2F:	///*��̩CHINT ����	д����оƬ�Ĵ���*///
			if(Byte2uInt(Ijtimer_Para.Ijtimer.B08) == 0 )
			{
				k = 2;
				OutBuf[0] = 0xFF; //���
				OutBuf[1] = 0x04; //Error: bit4�������/δ��Ȩ
				break;
			}
			
			result = CommWriteCalData(Ch);
			if(result) break;				
						
			k = 1;
			OutBuf[0] = 0x00;
			break;
		#endif		
		
		case 0x60:	//������оƬ�Ĵ���	
			if(Uart[Ch].Buf[10] < 0xf0)//��ȡ����оƬ�Ĵ���ֵ
			{
				memset(&Uart[Ch].Buf[11], 0x00, 4);
				result = Comm_Read_Reg(&Uart[Ch].Buf[10]);
				if(result) break;
			}
			else if(Uart[Ch].Buf[10] < 0xf5)//��ȡU��I1��I2��P��Fϵ��
			{
				result = Uart[Ch].Buf[10] - 0xf0;
				if( result == 2 ) result = 3;				//Ϊ�˼���֮ǰ��У�����
				else if(result == 3 ) result = 2;
				Exchange( Uart[Ch].Buf+11, Emu_Para.rate[result].B08, 4 );
			}
			else break;	//�Ƿ�����
			
			k = 6;
			memcpy(&OutBuf[1], &Uart[Ch].Buf[10], 5 );
			break;
			
		case 0x61:	//д����оƬ�Ĵ���			
			if(!progenable)
			{
				k = 2;
				OutBuf[0] = 0xFF; //���
				OutBuf[1] = 0x04; //Error: bit4�������/δ��Ȩ
				break;
			}
			
			if(Uart[Ch].Buf[10] < 0xf0)//д�Ĵ���
			{
				result = Comm_Write_Reg(&Uart[Ch].Buf[10]);
				if(result) break;
			}
			else if(Uart[Ch].Buf[10] < 0xf5)//дU��I1��I2��P��Fϵ��
			{
				result = Uart[Ch].Buf[10] - 0xf0;
				if( result == 2 ) result = 3;
				else if(result == 3 ) result = 2;
				Exchange( Emu_Para.rate[result].B08, Uart[Ch].Buf+11, 4 );
				WriteE2WithBackup( ee_emupara_page, ee_emupara_inpage, Emu_Para.rate[0].B08, ee_emupara_lenth );
			}
			else if(Uart[Ch].Buf[10] == 0xff)//У���ʼ������
			{
				for(i=0; i<4; i++)
				{
					if(Uart[Ch].Buf[11+i] != 0xff) break;
				}
				if(i != 4) break;
				
				Comm_Write_Reg(&Uart[Ch].Buf[10]);
			}
			else break;	//�Ƿ����� 
			
			k = 1;
			break;
			
		case 0x91:	//����Ӧ��֡
			if( DI07.B32 == 0x0E800006 )	//Ӧ�𴮿ڲ�����ѡ��
			{
				Ble_Step = 0;
				reg_veri_flag = 1;
			}
			
			if( DI07.B32 == 0x0E800003 )	//Ӧ������
			{
				Ble_Step = 0;
			}
			
//			if( DI07.B32 == 0x0E80000A )	//Ӧ����Լ��ܷ�ʽ
//			{
//				Ble_Step = 0;
//			}
			
			Uart[Ch].Overtime_Timer = 2;
			return;
			
		default:
			k = 2;
			OutBuf[0] = 0xFF;	//Operation result.
			if( Uart[Ch].Buf[8]&0x40 )	//����ͨ�ſ�
				OutBuf[1] = 0x04; 	//Error: bit4�������/δ��Ȩ
			else
				OutBuf[1] = 0x02;	//���ݱ�ʶ��, ����������
			break;
	}

	if( Uart[Ch].Flag&B0000_0001 )	//��ַΪ�㲥��ַ, ��Ӧ��
	{
		Uart[Ch].Overtime_Timer = 2;
		return;
	}
	
	Temp08 = 0;
	if( k == 0x00 ) //������Ӧ��֡
	{
		k=2;
		OutBuf[1]=1;	   //������Ϣ��ERR����������(Bit0)
		Uart[Ch].Buf[8]|=0x40;		//����֡
	}
	else
	{
		if(OutBuf[0] == 0x00)	 //ȷ��֡
		{ 	   
		   if((Uart[Ch].Buf[8]==0x03)||(Uart[Ch].Buf[8]==0x11)||(Uart[Ch].Buf[8]==0x12))
		   	Temp08 += 4;
		   	   
		   if((Remain)||
		      (((Uart[Ch].Buf[8] == 0x11) || (Uart[Ch].Buf[8] == 0x12)) && (Byte2uInt(DI07.B08) != 0x01150004) && ((Mode.Feature1&0x04)==0x04)
  			   && ChkBufZero( Report_Data, 5 ))
		     )
		   {
		   		if( ble_inter_flag == 0 ) Uart[Ch].Buf[8]|=0x20;		 //����֡
		   }
		}
		else
		{
//		  	if( Uart[Ch].Buf[8] == 0x03 )	//��ȫ��֤
//		  	{
//				if(hangup_comm_flag)	OutBuf[2] |= 0x01;	//Զ�̰�ȫ��֤��ס״̬λ
//		  	}
		  	Uart[Ch].Buf[8]|=0x40;		//����֡
		}
	}
	
	Uart[Ch].Buf[8]|=0x80;		   //Ӧ��֡
	Uart[Ch].Buf[9]=(k-1+Temp08); //len
	memcpy( Uart[Ch].Buf+10+Temp08, OutBuf+1, k );	//��������

//	Uart[Ch].Buf[7] = 0x68;
//	Uart[Ch].Buf[0] = 0x68;
	Exchange( Uart[Ch].Buf+1, Comm_Addr.Comm_Id, 6 );
	for( i=0; i<Uart[Ch].Buf[9]; i++ )
	{
		Uart[Ch].Buf[10+i] += 0x33;
	}	
	Uart[Ch].Buf[i+10]=Cal_ChkSum(Uart[Ch].Buf,Uart[Ch].Buf[9]+10);
	Uart[Ch].Buf[i+11]=0x16;
	
	//����ͨѶ
	if( Ch == CHBLE )
	{
		if( !ble_inter_flag )	//����͸������װһ��
		{
			Temp08 = Uart[Ch].Buf[9]+12;
			for(i=0; i<Temp08; i++)
			{
				Uart[Ch].Buf[Temp08-1-i+10] = Uart[Ch].Buf[Temp08-1-i];
			}
			
			Uart[Ch].Buf[8] = 0x11;
			Uart[Ch].Buf[9] = Temp08;
			
			for( i=0; i<Uart[Ch].Buf[9]; i++ )
			{
				Uart[Ch].Buf[10+i] += 0x33;
			}
		}
		
		memcpy(Uart[Ch].Buf, Ble_Buf, 8);
		Ble_CF++;
		Uart[Ch].Buf[1] = Ble_CF;
		Uart[Ch].Buf[2] = Ble_CF>>8;
		
		Uart[Ch].Buf[i+10]=Cal_ChkSum(Uart[Ch].Buf,Uart[Ch].Buf[9]+10);
		Uart[Ch].Buf[i+11]=0x16;
	}

	memcpy( Uart[Ch].TxBuf, Uart[Ch].Buf, Uart[Ch].Buf[9]+12 );
	Uart[Ch].Transfer = 1;
	Uart[Ch].Flag |= B0000_1000;//��Լ�������׼���������ݱ�־
	
	if( MeterClear == 0x55aa )	//����
	{
		Clear_Meter( Ch, OptID.B08 );	//0x1a�����������Ǯ����ʼ������
	}
	else if( MeterClear == 0x88bb )	//����ʼ��
	{
		//��λ��ʼ����ʼ
		OutBuf[0] = 0x33;
		OutBuf[1] = 0xcc;
		memcpy( OutBuf+2, Sclock.Clockbackup, 6 );
		I2C_Write_Eeprom( ee_factoryinit_page, ee_factoryinit_inpage, OutBuf, ee_factoryinit_len );
		
		Clear_Meter( Ch, OptID.B08 );
		Factory_Init();
		
		//��λ��ʼ���ɹ�
		OutBuf[0] = 0x55;
		OutBuf[1] = 0xaa;
		memcpy( OutBuf+2, Sclock.Clockbackup, 6 );
		I2C_Write_Eeprom( ee_factoryinit_page, ee_factoryinit_inpage, OutBuf, ee_factoryinit_len );
	}
	else if( MeterClear == 0xaa55 )	//��Կ����
	{
		UpdateEsamKey();
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
//�ϱ���Ӧ�����ز�ͨ����
void Report_Response( union B32_B08_2 DI07 )
{
	unsigned char i;
	
	if( (Byte2uInt(DI07.B08)==0x01057003) && (ReportList[1]&B0000_1100) )
	{
		if( 0x55 == BkupReport[0] ) //�����¼�
		{
			Clr_Reportdata(ee_powerdownn_inpage);	//�嵥���ϱ�״̬�ֺ���������(���¼���¼��)
					
			if( (ReportList[0]&B0000_1100) != B0000_1100 ) ReportList[0] &= B1111_0011;
			ReportList[1] &= B1111_0011;
			BkupReport[0] = 0;
			
			if( (ReportList[1] ==0) ) Uart[CHZB].RptTimer = 0; //����ϱ����ݻ�δȷ�ϣ������ȴ�; ���ȫ��ȷ�������㶨ʱ��
		}
	}
	else if( (Byte2uInt(DI07.B08)==0x01150004) && (ReportList[1]&B0011_0000) && (Uart[CHZB].Buf[9]==16) )
	{
		if( 0xaa == BkupReport[0] ) //�ϱ�״̬
		{
			unsigned char Buf[5];
			if( Uart[CHZB].Buf[14+2]&B1000_0000 ) Uart[CHZB].Buf[14+2] &= B0111_1111;
			if( Uart[CHZB].Buf[14+8]&B0010_0000 ) Uart[CHZB].Buf[14+2] |= B1000_0000;//������ʱ���ô�A�����
			if( Uart[CHZB].Buf[14+2]&B0000_0100 ) Uart[CHZB].Buf[14+2] &= ~B0000_0100;
			if( Uart[CHZB].Buf[14+3]&B0010_0000 ) Uart[CHZB].Buf[14+2] |= B0000_0100;//�͵�ѹ��ʱ���ô�A��Ƿѹ
			if( Uart[CHZB].Buf[14+2]&B0000_0010 ) Uart[CHZB].Buf[14+2] &= ~B0000_0010;
			if( Uart[CHZB].Buf[14+3]&B0001_0000 ) Uart[CHZB].Buf[14+2] |= B0000_0010;//�ߵ�ѹ��ʱ���ô�A���ѹ
			Buf[0] = Report_Data2[0]&Uart[CHZB].Buf[14+0];
			Buf[1] = Report_Data2[1]&Uart[CHZB].Buf[14+1];
			Buf[2] = Report_Data2[2]&Uart[CHZB].Buf[14+2];
			Buf[3] = Report_Data2[3]&Uart[CHZB].Buf[14+10];
			Buf[4] = Report_Data2[4]&Uart[CHZB].Buf[14+11];
			Xor_Data( Report_Data, Buf, 5 );//�����ڼ��µ��ϱ�
			Xor_Data( Report_Data2, Buf, 5 );//�ϱ�״̬�ֱ�������
			for( i=0; i<5; i++ ) Clr_Reportnum(i);//���������ϱ�����
			if( ChkBufZero( Report_Data2, 5 ) ) return;//��0,ȷ��ʧ�ܼ����ϱ�
			
//			Xor_Data( Report_Data, Report_Data2, 5 );//�����ڼ��µ��ϱ�
//			memset( Report_Data2, 0x00, 5 );//�ϱ�״̬�ֱ�������
//			for( i=0; i<5; i++ ) Clr_Reportnum(i);//���������ϱ�����
					
			if( (ReportList[0]&B0011_0000) != B0011_0000 ) ReportList[0] &= B1100_1111;
			ReportList[1] &= B1100_1111;
			BkupReport[0] = 0;
			
			if( (ReportList[1] ==0) ) Uart[CHZB].RptTimer = 0; //����ϱ����ݻ�δȷ�ϣ������ȴ�; ���ȫ��ȷ�������㶨ʱ��	
		}
	}
}


//�¼������ϱ�
unsigned char ReportEvent( uint08 repmode )
{
	unsigned char n;

	if( repmode == 0 )
	{
		if( EA_OFF ) return 0;
		if( Relay_Space_Timer ) return 0;
	}

	if( (Mode.Feature1&0x0c)!=0x08 ) ReportList[0] = 0; //�����ϱ�δ����,���ϱ�
	if( 0 == ReportList[0] ) return 0;
	
	for( n=0; n<6; n+=2 )
	{
		unsigned char Ch = CHZB;
		
		if( ReportList[0]&(3<<n) ) //�ط�����1~3
		{
			ReportProc( Ch, n );
			break;
		}
	}
	
	return 0;
}


//�¼������ϱ�����
unsigned char ReportProc( unsigned char Ch, unsigned char Type )
//4-ͨ���¼�
{
	unsigned char i, k, Buf[256];
	
	if( Type == 0 || Type == 2 ) //�����¼�
	{
		if( Type == 0 ) Int2Byte( 0x01047003, Buf );
		else Int2Byte( 0x01057003, Buf );
		k = RdHisEvent( Buf, 0, Buf+10 );
		if( k == 0x00 )
		{
			if( Type == 0 ) ReportList[0] &= B1111_1100;
			else ReportList[0] &= B1111_0011;
			Uart[Ch].RptTimer = 0;
			return 0;
		}
		
		//׼�������¼
		memcpy( Buf+4, Buf+10+1, k ); //��������
		
	}
	else
	{
		if( Meter_Run_Timer3 < 60 ) return 0; //�ϱ�״̬����ʱ1min
		
		Ready_Reportdata( Buf+3 );	//�����ϱ�״̬��	NNNNNNNNNNNNNNNNNNNNNNNN	12+N
		if( ChkBufZero(Buf+3+1,12) == 0 )
		{
			ReportList[0] &= B0000_1111;
			Uart[Ch].RptTimer = 0;
			return 0;
		}
		
		//׼�������ϱ�״̬��
		Int2Byte( 0x01150004, Buf );
		k = 12;
	}
	
	if( Uart[Ch].Overtime_Timer ) return 0;//���ճ�ʱ�����ڼ䲻�ϱ�
	if( Uart[Ch].Response_Timer ) return 0;//������ɴ����ڼ䲻�ϱ�
	if( Uart[Ch].S_Overtime_Timer ) return 0;
	Uart[Ch].S_Overtime_Timer= txtimeout_max*10;//���ͳ�ʱ(�ز�ר��),��ֹ698�Ľ�����ɴ����ֹ�������ͻ
	
	ReportList[1] = 0;
	BkupReport[0] = 0;
	if( Type == 0 || Type == 2 ) //�����¼�
	{
		if( Type == 0 )
		{
			if( ReportList[0]&B0000_0011 ) ReportList[0] -= B0000_0001;
				
			//�����ϱ�֡�ж���OAD
//			ReportList[1] |= B0000_0011;	//��֧�ֵ����ϱ��Ľ���
//			BkupReport[0] = 0x55;	
			Meter_Run_Timer1 = 0;	
		}
		else
		{
			if( ReportList[0]&B0000_1100 ) ReportList[0] -= B0000_0100;
				
			//�����ϱ�֡�ж���OAD
			ReportList[1] |= B0000_1100;	
			BkupReport[0] = 0x55;
			if( (ReportList[0]&B0000_1100) == B0000_1000 )
			Meter_Run_Timer2 = 0;
		}		
	}
	else
	{
		//�����ϱ�֡�ж���OAD
		ReportList[1] |= B0011_0000;
		if( ReportList[0]&B0011_0000 ) ReportList[0] -= B0001_0000;
		BkupReport[0] = 0xaa;
	}
	
	if( Type == 0 )  Uart[Ch].RptTimer = 25*10; //�ط����ڣ�25*4.096ms*10 = 1s	�����ϱ�
	else Uart[Ch].RptTimer = 123*20; //�ط����ڣ�123*4.096ms*20 = 10s

	Uart[Ch].TxBuf[8]  = 0x86;		//����֡
	Uart[Ch].TxBuf[9]  = (k+4);		//len
	Uart[Ch].TxBuf[10] = Buf[0]; 
	Uart[Ch].TxBuf[11] = Buf[1]; 
	Uart[Ch].TxBuf[12] = Buf[2];
	Uart[Ch].TxBuf[13] = Buf[3];
	memcpy( Uart[Ch].TxBuf+14, Buf+4, k );	//��������

	Uart[Ch].TxBuf[7] = 0x68;
	Uart[Ch].TxBuf[0] = 0x68;
	Exchange( Uart[Ch].TxBuf+1, Comm_Addr.Comm_Id, 6 );
	for( i=0; i<Uart[Ch].TxBuf[9]; i++ )
	{
		Uart[Ch].TxBuf[10+i] += 0x33;
	}	
	Uart[Ch].TxBuf[i+10]=Cal_ChkSum(Uart[Ch].TxBuf,Uart[Ch].TxBuf[9]+10);
	Uart[Ch].TxBuf[i+11]=0x16;
	
	Uart[Ch].TxLen  = 1;//��ʼ��������
	Uart[Ch].Total_Tx = Uart[Ch].TxBuf[9]+16;
	Uart[Ch].Transfer = 0;
	UART0->TXREG = 0xfe; //�ز�����0xfe
	return 0;
}

//����CS
void Ble_Frame_Cs( uint08 Ch )
{
	uint08 i;
	
	for( i=0; i<Uart[Ch].Buf[9]; i++ )
	{
		Uart[Ch].Buf[10+i] += 0x33;
	}	
	Uart[Ch].Buf[i+10]=Cal_ChkSum(Uart[Ch].Buf,Uart[Ch].Buf[9]+10);
	Uart[Ch].Buf[i+11]=0x16;
}

//��ѯ����
void Ble_Chk_Heart(uint08 Ch)
{
	uint08 const_comm[16] = { 0x68, 0x00, 0x00, 0xFF, 0xFF, 0xEE, 0xEE, 0x68, 0x11, 0x04, 
														0x03, 0x00, 0x80, 0x0E, 
														0x00, 0x16 };

	memcpy( Uart[Ch].Buf, &const_comm, sizeof(const_comm) );
	
	Ble_Frame_Cs(Ch);
}

//������Լ��ܷ�ʽ
void Ble_Cfg_Mode(uint08 Ch)
{
	uint08 const_comm[36] = { 0x68, 0x00, 0x00, 0xFF, 0xFF, 0xEE, 0xEE, 0x68, 0x11, 0x18, 
														0x0A, 0x00, 0x80, 0x0E, 
														0x00, 0x00, 0x00, 0x00, 0x00,
														0x00, 0x00, 0x00, 0x00, 0x00,
														0x00, 0x00, 0x00, 0x00, 0x00,
														0x00, 0x00, 0x00, 0x00, 0x00,
														0x00, 0x16 };

	memcpy( Uart[Ch].Buf, &const_comm, sizeof(const_comm) );
	
	Ble_Frame_Cs(Ch);
}

////���ڲ�����ѡ��
//void Ble_Cfg_Bps(uint08 Ch)
//{
//	uint08 const_comm[17] = { 0x68, 0x00, 0x00, 0xFF, 0xFF, 0xEE, 0xEE, 0x68, 0x11, 0x05, 
//														0x06, 0x00, 0x80, 0x0E, 0x00, 0x00, 0x16 };

//	memcpy( Uart[Ch].Buf, &const_comm, sizeof(const_comm) );
//	
//	if( Mode.blebps == 0x40 ) Uart[Ch].Buf[14] = 4;		//19200
//	else if( Mode.blebps == 0x20 ) Uart[Ch].Buf[14] = 5;	//9600
//	else Uart[Ch].Buf[14] = 1;											//115200
//	
//	Ble_Frame_Cs(Ch);
//}

void Ble_Rst(void)
{
	uint08 i;
	
	Delay_Initial(2);
	BLEPOWEROFF;
	Delay_Initial(4);
	BLEPOWERON;
	
	Ble_Step = 0;	
	
	for(i=0; i<5; i++)
	{
		memset(&Ble_Connect[i].Ble_A2, 0x00, 9);
	}
}

//������ʼ��
void Ble_Init(void)
{	
	uint08 Ch, Temp08=0;
	
	Ch = CHBLE;
	
	if( Uart[Ch].Response_Timer || Uart[Ch].Overtime_Timer ) return;
		
	switch(Ble_Step)
	{
//		case 0:	//���ڲ�����ѡ��
//			if( Mode.blebps != 0x01 ) Ble_Cfg_Bps(Ch);
//			else Temp08 = 0xff;
//			break;

		case 1:	//��ѯ����
			Ble_Chk_Heart(Ch);
			break;
			
//		case 2:	//������Լ��ܷ�ʽ
//			Ble_Cfg_Mode(Ch);	
//			break;
		
		default: 
			Temp08 = 0xff;
			break;
	}
	
	if( Temp08 == 0 ) 
	{
		memcpy( Uart[Ch].TxBuf, Uart[Ch].Buf, Uart[Ch].Buf[9]+12 );
		Uart[Ch].Transfer = 1;

		Uart[Ch].Flag |= B0000_1000;	//��Լ�������׼���������ݱ�־
		Uart[Ch].Response_Timer = 2; //����Ӧ��ʱ
	}
}
