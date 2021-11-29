//RTC function
#include "ex_var.h"
#include "ex_func.h"
#include <string.h>
#include "FM32L0XX.h"  
#include "Cpu_card.h"


int32 Byte2Int(uint08* byte)
{
	return (int32)(byte[3]+((uint32)byte[2]<<8) + ((uint32)byte[1]<<16) +((uint32)byte[0]<<24)) ;
}
int16 Byte2Short(uint08* byte)
{
	return (int16)(byte[1])+((uint16)byte[0]<<8);
}
uint32 Byte2uInt(uint08* byte)
{
	return byte[3]+((uint32)byte[2]<<8) + ((uint32)byte[1]<<16) +((uint32)byte[0]<<24) ;
}
uint16 Byte2uShort(uint08* byte)
{
	return byte[1]+((uint16)byte[0]<<8);
}
void Int2Byte(uint32 datatemp,uint08* Buff)
{
	Buff[3] = datatemp ;
	Buff[2] = (datatemp>>8) ;
	Buff[1] = (datatemp>>16) ;
	Buff[0] = (datatemp>>24) ;
}
void Short2Byte(uint16 datatemp,uint08* Buff)
{
	Buff[1] = datatemp ;
	Buff[0] = (datatemp>>8) ;
}

/*============================================================================*
	������	unsigned char Add_Bcd_1(unsigned char n,unsigned char m,unsigned char *carry)
	���ܣ�	���ֽڵ�BCD��ӷ���
	������	m����������
			n������������
  ����ֵ:	n���������Ľ��������һ���ֽڽ�λ��־������carry��
*============================================================================*/	
unsigned char Add_Bcd_1(unsigned char n,unsigned char m,unsigned char *carry)	
{
	unsigned char i,j,w;
	m=m+(*carry);
	*carry=0;
	j=n&0x0f;
	i=m&0x0f;
	i+=j;
	w=0;
	if(i>9)
	{
		w=0x01;
		i-=10;
	}
	j=n;
	j>>=4;		
	m>>=4;
	j=j+m+w;
	if(j>0x09)
	{
		j-=10;
		j<<=4;
		n=j+i;
		*carry=1;
		return(n);
	}
	j<<=4;
	n=j+i;
	*carry=0;
	return(n);
}

/*============================================================================*
	������	void Add_Bcd( unsigned char *BufA, unsigned char *BufB, unsigned char Len )
	���ܣ�	Len�ֽ�BCD��ӷ�
	������	*BufA ������    *BufB ����  *BufA=*BufA+*BufB
	        ����һ���ֽڽ�λ��־������bf_carry��
  ����ֵ:	��
*============================================================================*/	
void Add_Bcd( unsigned char *BufA, unsigned char *BufB, unsigned char Len )
{
	unsigned char i;
	unsigned char bf_carry;
	bf_carry=0;
	for(i=(Len-1);i<Len;i--)
	{
		BufA[i]=Add_Bcd_1(BufA[i],BufB[i],&bf_carry);
	}
	return;
}

/*============================================================================*
	������	unsigned char Bcdsub_4(unsigned char *,unsigned char *,unsigned char *)
	���ܣ�	4�ֽ�BCD�����
	������	*BufB ����  *BufA ������    *sub=*BufA-*BufB
	        ����һ���ֽڽ�λ��־������bf_carry��
  ����ֵ:	��
*============================================================================*/	
void Sub_Bcd( unsigned char *BufA, unsigned char *BufB, unsigned char Len )
{
	unsigned char i,j,k;
	unsigned char bf_carry;
	bf_carry=0;
	for(i=(Len-1);i<Len;i--)
	{
		j=BufB[i]+bf_carry;
		k=0;
		if(j<BufB[i])
			k=1;									
		bf_carry=0;
		if((BufA[i]&0x0f)<(j&0x0f))
		{
			if(BufA[i]<j)
			{
				BufA[i]=0x9a-j+BufA[i];			//0xa0-6;
	           		bf_carry=1;
	        	}
			else
				BufA[i]=BufA[i]-j-6;
		}
		else
		{
			if(BufA[i]<j)
			{
				BufA[i]=0xa0-j+BufA[i];
	            		bf_carry=1;
	        	}
			else
				BufA[i]=BufA[i]-j;
		}
		if(k)
			bf_carry=1;		//����k=1ʱ�����������λ
	}
	return;
}
/*============================================================================*
	������	void Hex2Bcd( unsigned char *Hexop, unsigned char *BCDopt, unsigned char Len );
	���ܣ�	���ֽ�HEXת��BCD
	������	*Hexop  HEX ��ʼֵΪ��ת���ĸ��ֽڵ�ַ�� 
			*BCDopt  BCD ��ʼֵΪ��ת���ĸ��ֽڵ�ַ�� 
			Len  ���ȣ����4���ֽ�
  ����ֵ:	��
*============================================================================*/	
void Hex2Bcd( unsigned char *Hexop, unsigned char *BCDopt, unsigned char Len )
{	
	unsigned char i,m;
	unsigned long long hex_temp;
	unsigned char code temp1[8]={0,8,16,24,32,40,48,56};
	
	if(Len>8)
		return;
	hex_temp=0;
	for(i=0;i<Len;i++)
	{
		hex_temp+=(unsigned long long)((unsigned long long)Hexop[i]<<temp1[Len-1-i]);		
	}
	
	for(i=0; i<Len;i++)
	{
		m = (unsigned char)(hex_temp % 100);
		BCDopt[Len-1-i]=Hex_To_Bcd(m);							//ת��ΪBCD��ʽ
		hex_temp/=100;
	}
	return;
}
void Hex2Bcd_SS( unsigned char *Hexop, unsigned char *BCDopt, unsigned char Len )		//С��Hex���С��BCD
{	
	uint8_t Buff[8];
	
	Exchange(Buff,Hexop,Len);
	Hex2Bcd(Buff,BCDopt,Len);
	Inverse(BCDopt,Len);
	return;
}
//void Hex2Bcd_LS( unsigned char *Hexop, unsigned char *BCDopt, unsigned char Len )		//���Hex���С��BCD
//{	
//	Hex2Bcd( Hexop, BCDopt, Len );
//	Inverse( BCDopt, Len );
//	return;
//}
/*==========================================================================*/
/*============================================================================*
	������	void Bcd2Hex( uint08 *BCDopt, uint08 *HEXopt, uint08 Len );
	���ܣ�	���ֽ�BCDת��HEX
	������	*BCDopt  BCD ��ʼֵΪ��ת���ĸ��ֽڵ�ַ�� 
			*HEXopt  HEX ��ʼֵΪ��ת���ĸ��ֽڵ�ַ��
			Len  ���ȣ����4���ֽ�
  ����ֵ:	��
*============================================================================*/	
void Bcd2Hex( unsigned char *BCDopt, unsigned char *HEXopt, unsigned char Len )
{	
	unsigned long long hex_temp;
	unsigned long long code temp0[8]={1,100,10000,1000000,100000000,10000000000,1000000000000,100000000000000};	
	unsigned char code temp1[8]={0,8,16,24,32,40,48,56};
	unsigned char i;
	if(Len>8)
		return;
	hex_temp=0;
	for(i=0;i<Len;i++)
	{
		hex_temp+=(unsigned long long)(Bcd_To_Hex(BCDopt[Len-1-i]))*temp0[i];		
	}
	for(i=0;i<Len;i++)
	{
		HEXopt[Len-1-i]=(unsigned char)(hex_temp>>temp1[i]);
	}	
	return;
}
void Bcd2Hex_LS( unsigned char *BCDopt, unsigned char *HEXopt, unsigned char Len )		//���Bcd���С��Hex
{	
	Bcd2Hex( BCDopt, HEXopt, Len );
	Inverse( HEXopt, Len );
	return;
}
void Bcd2Hex_SS( unsigned char *BCDopt, unsigned char *HEXopt, unsigned char Len )		//С��Hex���С��BCD
{	
	uint8_t Buff[8];
	
	Exchange(Buff,BCDopt,Len);
	Bcd2Hex( Buff, HEXopt, Len );
	Inverse( HEXopt, Len );
	return;
}
//============================================================================
unsigned char Hex_To_Bcd( unsigned char value )
{
	return ( ((value/10)<<4)+(value%10) );
}

unsigned char Bcd_To_Hex( unsigned char value )
{
	return ( ((value&0xF0)>>4)*10+(value&0x0F) );
}

//============================================================================
unsigned char ChkBufZero( unsigned char *Buf,unsigned char Len )
{
	unsigned char i;
	
	for( i=0; i<Len; i++ )
	{
		if( Buf[i] )	return(1);	//��0
	}
	
	return(0);	//ȫ0
}


//���ֽ���ǰ�����ݱȽ�
unsigned char Cmp_Data( unsigned char *BufA, unsigned char *BufB, unsigned char Len )
{
	unsigned char i;

	for( i=0; i<Len; i++ )
	{
		if( BufA[i] > BufB[i] )
		{
			return 1; //A>B
		}
		else
		{
			if( BufA[i] < BufB[i] )
			{
				return 2; //A<B
			}
		}
	}

	return 3; //A=B
}

//���ֽ���ǰ�����ݱȽ�
unsigned char Cmp_Bcd_Inv( uint08 *BcdA, uint08 *BcdB, uint08 Len )
//return: 0-A=B; 1:A>B; 2:A<B
{
	unsigned char i;

	for( i=0; i<Len; i++ )
	{
		if( BcdA[Len-1-i] > BcdB[Len-1-i] )
		{
			return 1; //A > B
		}
		else
		{
			if( BcdA[Len-1-i] < BcdB[Len-1-i] )
			{
				return 2; //A < B
			}
		}
	}

	return 0; //A==B
}

//============================================================================
//����Ϊ��ʼ�ֽڵ�ʱ�ӱȽϳ���
unsigned char Cmp_Clock( unsigned char *Buf, unsigned char Len )
{
	unsigned char i;
	
	for( i=0; i<Len; i++ )
	{
		if( Buf[ i ] > Sclock.Clockbackup[ Len-i ] )
		{
			return 1; //���ڵ�ǰʱ��
		}
		else
		{
			if( Buf[ i ] < Sclock.Clockbackup[ Len-i ] )
			{
				return 2; //С�ڵ�ǰʱ��
			}
		}
	}

	return 3; //���
}

const uint08 code MaxDays []={0x31,0x28,0x31,0x30,0x31,0x30,0x31,0x31,0x30,0x31,0x30,0x31};
uint08 Judge_Clock( uint08 Start, uint08 *Ck, uint08 Len )//�����м�
{
	unsigned char  i, j, k=0;
	const uint08 code Max[]={ 0x59,0x59,0x23,0x6,0x31,0x12,0x99 }, code Min[]={ 0x00,0x00,0x00,0x00,0x01,0x01,0x00 };

	if( (Len&0x80) == 0 ) k = 1;	//����
		
	for( i=0; i<(Len&0x07f); i++ )
	{
		j=i+Start;
		if((j>=3)&&(Len&0x80))	j++;
		
		if( (Ck[i] > Max[j]) || (Ck[i] < Min[j]) ) return 1;//�Ϸ��Լ�����
		if( IsBCD(Ck[i]) ) return 1;	//BCD�������		  
		
		if( (j == 4) && ((Start+(Len&0x07f)) > (4+k)) ) //Day
		{
			if( (Ck[i+1] == 0x02) && ((Start+(Len&0x07f)) > (5+k)) ) //Month
			{
				if( (Bcd_To_Hex(Ck[i+2])&0x03) == 0 ) //����Year
				{
					if( Ck[i] > 0x29 ) return 1;
				}
				else
				{
					if( Ck[i] > 0x28 ) return 1;
				}
			}
			else
			{
				if( Ck[i] > MaxDays[Bcd_To_Hex(Ck[i+1])-1] ) return 1;
			}
		}
	}
	return 0;//��ȷ
}


unsigned char JudgeClockNoWeek( uint08 Start, uint08 *Ck, uint08 Len )
{
	return(Judge_Clock( Start, Ck, Len+0x80 ));
}


unsigned char Read_Rtc( unsigned char *RTC_Buf )
{
	unsigned char i, n, Result;
	unsigned char BufA[7], BufB[7];

	for( n=0; n<3; n++ )
	{
		BufA[0] = RTC->BCDSEC;
		BufA[1] = RTC->BCDMIN;
		BufA[2] = RTC->BCDHOUR;
		BufA[3] = RTC->BCDWEEK;
		BufA[4] = RTC->BCDDATE;
		BufA[5] = RTC->BCDMONTH;
		BufA[6] = RTC->BCDYEAR;

		BufB[0] = RTC->BCDSEC;
		BufB[1] = RTC->BCDMIN;
		BufB[2] = RTC->BCDHOUR;
		BufB[3] = RTC->BCDWEEK;
		BufB[4] = RTC->BCDDATE;
		BufB[5] = RTC->BCDMONTH;
		BufB[6] = RTC->BCDYEAR;

		for( i=0; i<7; i++ ) //�ȶ�����ʱ���Ƿ�һ��
		{
			if( BufA[i] != BufB[i] ) break;
		}

		if( i == 7 ) //����һ��, ��ʾ��ȡ�ɹ�
		{
			Result = Judge_Clock( 0, BufA, 7 ); //�ж�ʱ���Ƿ�Ϸ�
			if( Result == 0 ) //ʱ�ӺϷ�
			{
				for( i=0; i<7; i++ )
				{
					RTC_Buf[i] = BufA[i];
				}
			
				return 0;
			}
		}
	}
	
	for( i=0; i<7; i++ )
	{
		RTC_Buf[i] = BufA[i];//��ʹ����ҲҪ����ʱ��
	}
	return 1;
}

#define RTC_WRITR_PROTECT_WORD  						((uint32_t)0x53535353)
#define RTC_WRITR_UNPROTECT_WORD  						((uint32_t)0xACACACAC)
unsigned char Set_Rtc( unsigned char Start, unsigned char *Ck, unsigned char Len )
{
	unsigned char i, n, Result;
	unsigned char BufB[7];
	
	if( Start || (Len!=7) ) return 1; //��ڲ����Ƿ�

	Result = Judge_Clock( Start, Ck, Len );
	if( Result == 1 )
	{
		return 1;
	}

//	if( Len < 7 )
//	{
//		Result = Read_Rtc( BufA );
//		if( Result == 1 )
//		{
//			return 1;
//		}
//	}
//
//	for( i=0; i<Len; i++ )
//	{
//		BufA[ Start+i ] = Ck[i];
//	}

	for( n=0; n<3; n++ )
	{
		RTC->RTCWE = RTC_WRITR_UNPROTECT_WORD;
		
		RTC->BCDSEC 	= Ck[0];
		RTC->BCDMIN 	= Ck[1];
		RTC->BCDHOUR	= Ck[2];
		RTC->BCDWEEK	= Ck[3];
		RTC->BCDDATE	= Ck[4];
		RTC->BCDMONTH	= Ck[5];
		RTC->BCDYEAR	= Ck[6];
		
		RTC->RTCWE = RTC_WRITR_PROTECT_WORD;

//		I2c_Wait_5ms();//RTC��һ��5�ĵ��˲����ڴ�֮ǰ��ʱ�ӻ�ȡ������
//		if( (RTCSTAT&1) == 1 )  //���سɹ�
		{
			Result = Read_Rtc( BufB );
			if( Result == 0 ) //��ȡ�ɹ�
			{
				for( i=0; i<7; i++ )
				{
					if( Ck[i] != BufB[i] ) break;
				}

				if( i == 7 ) //��ǰֵ������ֵ���, ���óɹ�
				{
					return 0; //���óɹ�
				}
			}
		}
	}

	return 1; //����ʧ��
}


void Syn_Clock( void )	//ͬ�����ͱ���ʱ��
{
	Sclock.Clockbackup[0] = Sclock.Clockmain[0];//�����м��ŵ����
	Sclock.Clockbackup[1] = Sclock.Clockmain[1];
	Sclock.Clockbackup[2] = Sclock.Clockmain[2];
	Sclock.Clockbackup[3] = Sclock.Clockmain[4];
	Sclock.Clockbackup[4] = Sclock.Clockmain[5];
	Sclock.Clockbackup[5] = Sclock.Clockmain[6];
	Sclock.Clockbackup[6] = Sclock.Clockmain[3];
}


void Read_Sysclock( void )
{
	unsigned char Result,Buf[10];
	#if(1 == CHINT_Mode)
	uint32 V_ulDataBuf;
	#endif

	run_readrtc_flag = 0;	//��ˢ��ʱ�ӱ�־ 
	
	Result = Read_Rtc( Sclock.Clockmain );//��ʱ��
	if( Result == 1 )
	{
		I2c_Wait_5ms(); 	//��ʱ
		Result = Read_Rtc( Sclock.Clockmain );//�ٶ�ʱ��
		if( Result == 1 )
		{
			if( EA_OFF ) return;		//�ϵ���ߵ���ʱ�Ӵ�����ֱ�ӷ���
			if( clock_error == 0 ) 
			{
				clock_error = 1;//��ʱ�Ӵ����־
				memcpy( Buf, Sclock.Clockbackup, 3 );
				Buf[3] = Sclock.Clockbackup[6];
				memcpy( Buf+4, Sclock.Clockbackup+3, 3 );
				Set_Rtc( 0, Buf, 7 );//��ram����ȷ��ʱ��д��rtc
				
//				Syn_Clock();//ͬ�����ͱ���ʱ��	
				if( ChkLastclockerrRcdTime() != 1 ) Note_Run_Event(ee_clockerrn_inpage); //ʱ�ӹ��Ͽ�ʼ��¼(ʱ�ӷǷ�)
				return;
			}
		}
	}
	if( Result == 0 )
	{
		if( clock_error )
		{
			clock_error = 0;//��ʱ�Ӵ����־
			Syn_Clock();//ͬ�����ͱ���ʱ��	
//			Note_Run_Event(ee_clockerrn_inpage|0x80);		//ʱ�ӹ��Ͻ�����¼(ʱ�ӺϷ�)
			return;
		}
	}
		
	if( EA_ON )
	{	
		if ( Sclock.Clockbackup[0] != Sclock.Clockmain[0] )//��ı�
		{
			read_back_flag = 1;//ÿ���һ��7051�ķ����־
			read_uip_flag1 = 1;
			
//			if( Sclock.Clockmain[0]&B0000_0001 ) read_uip_flag1 =1;		//ÿ�뽻���ȡI1,I2,U (80ms)
			if( Sclock.Clockmain[0] == 0x05 ) fwdl_veri_flag = 1;		//�������У��
			if( Sclock.Clockmain[0] == 0x10 ) bkdl_veri_flag = 1;		//�������У��
			if( Sclock.Clockmain[0] == 0x15 ) rpdl_veri_flag = 1;		//�޹�����У��
			if( Sclock.Clockmain[0] == 0x20 ) mode_veri_flag = 1;		//����ģʽ��У��
			if( Sclock.Clockmain[0] == 0x25 ) reg_veri_flag = 1;		//�Ĵ���У��
			if( Sclock.Clockmain[0] == 0x30 ) addr_veri_flag = 1;		//ͨѶ��ַУ��
			if( Sclock.Clockmain[0] == 0x35 ) disppm_veri_flag = 1;		//��ʾ����У��
			if( Sclock.Clockmain[0] == 0x40 ) dispitem_veri_flag = 1;	//��ʾ��ĿУ��
			
			if( Sclock.Clockmain[0] == 0x42) init_7051_flag1 = 1;		//��ʼ���Ĵ���
			if( Sclock.Clockmain[0] == 0x46) check_7051_flag1 = 1;		//У��У��Ĵ���
			if( Sclock.Clockmain[0] == 0x55) temperpara_veri_flag = 1;	//�¶�ϵ��У��
			
			//ESAM�ϵ縴λ
			if(Esam_Timer) 
			{
				Esam_Timer--;
				if(Esam_Timer == 0) 
				{
					if((identity_prog_flag == 0) && (identity_ir_flag == 0))
					{
						EsamReset();//��ȫ��֤��̱�־ʧЧ
					}
					UpdateEsamKey(); //������Կ��ESAM
				}
			}
//			else
//			{
//				U7816CTRL0 &= B1101_1111;	//�ر�u7816CLK
//			}
			
			//�ر��ز���λ���¼��ϱ�����
			if( ChkBufZero( Report_Data, 5 ) && ((Mode.Feature1&0x0c)!=0x08) ) //�����ϱ�δ����,��EVENOUT��Ч
			{
				EVENOUTON;		//�¼��ϱ�
			}
			else
			{
				EVENOUTOFF;		//���¼��ϱ������
			}
			
			//�����֤ʱЧ
			if( Identitytimer != 0 )
			{
				Identitytimer--;
	
				if( Identitytimer == 0 )
				{
					Clear_Rand_Gene();
					FailKey();	//������Կʧ�ܴ���
				}	
			}
			
			//��բ��ʱʱ��
			if( Opendelaytimer != 0 ) //�̵�����բ��ʱ
			{
				Opendelaytimer--;
				if( Opendelaytimer == 0 ) run_alarm_flag = 1;	//��ʱ���ñ�־
			}
						
			Judge_Relay_Delay();	//�������ʱ��բ�ж�
		 	if( relay_delay_flag )
		 	{
		 		CurrentTimer--; //�������ʱ��բ��ʱ����1
		 		if( CurrentTimer == 0 ) run_alarm_flag = 1;	//��ʱ���ñ�־
		 	}
			
			//������֤ʱЧ
			if( IR_EnTimer )
			{
				IR_EnTimer--;
				if( IR_EnTimer == 0 ) identity_ir_flag = 0;	//����������־
			}
			
			//�ϱ��Զ���λʱ��
			if( Reset_Rep_Timer )
			{
				Reset_Rep_Timer--;	//�ϱ���λ��ʱ����1
				
				if( Reset_Rep_Timer == 0 )
				{
					Xor_Data( Report_Data, Report_Data2, 5 );//����30min���µ��ϱ�
					memset( Report_Data2, 0x00, 5 );//�ϱ�״̬�ֱ�������
					for( Result=0; Result<5; Result++ ) Clr_Reportnum(Result);//���������ϱ�����
				}
			}			
			
//			//Ԥ��բ��ʱ
//			if( CloseDelayTimer != 0 )	//Ԥ��բ��ʱ��ʱ��
//		 	{
//		 		CloseDelayTimer--;
//		 		if( CloseDelayTimer == 0 )
//		 		{
//		 			Last_Timer = 0;	//��Ԥ��բ��ʱʱ��
//		 			run_alarm_flag = 1;	//��ʱ���ñ�־
//		 		}
//		 	}
		 	
		 	//����ʱesam��Դ�ر�
		 	if( EsamPowerOff_Ctrl == 0x55 )
			{
				if((identity_prog_flag == 0) && (identity_ir_flag == 0))
				{
					CloseEsam();//�ͷ�ESAM
				}
			}
			
			//����ʱflash��Դ�ر�
		 	if( FlashPowerOff_Ctrl == 0x55 )
		 	{
			 	if( FlashTimer )
				{
					FlashTimer--;
					if( FlashTimer == 0 )
					{
						if( FLASHVCC_N ) CloseFlash();	//�ر�flash��Դ
					}
				}
			}
		 				
			//��ʱ8Mʱ�ӵ�У����(����uartר��)
			if( Adj_Clk_Timer_S )
			{
				Adj_Clk_Timer_S--;	//��ʱ8Mʱ�ӵ�У��ʱ����1s
				if( Adj_Clk_Timer_S == 0 )  Clk_Adj_Proc();//�����ⲿ��32K�����������ڲ�8M��ƫ��
			}
			if( Adj_Clk_Timer_S == 0 ) Adj_Clk_Timer_S = Adjclk_timer_delay_s;

			//��չ����
			if( (Key_Status == 1)&&(esam_error==0) ) Progkey.Timer = 0;	//˽Կ�±�̽�ֹ
			if( Progkey.Timer )
			{
				progenable = 1;	//���ʹ��
			}
			else
			{
				progenable = 0;	//��̽�ֹ
			}
			
			if( (ANAC->FDETIF)&BIT0 )	//xtlf����ͣ��
			{
				ANAC->FDETIF = ANAC->FDETIF;//��XTLFͣ���־
				Result = I2C_Read_Eeprom( ee_xtlfstop_time_page, ee_xtlfstoptime_inpage, Buf, ee_xtlfstoptime_lenth );
				if( (Result || (ChkBufZero(Buf,ee_xtlfstoptime_lenth)==0)) && (clock_error==0) ) //�ж��Ƿ�����¼
				{
					//��¼����ͣ��ķ���ʱ��
					I2C_Write_Eeprom( ee_xtlfstop_time_page, ee_xtlfstoptime_inpage, Sclock.Clockbackup, ee_xtlfstoptime_lenth );
				}
			}
			
			//������ʱ��ʱ����1
			if( Cover_Space_Timer != 0 ) Cover_Space_Timer--;	
			
			//ͨ��ģ�������ʱ��ʱ����1
			if( Commmodule_Space_Timer != 0 ) Commmodule_Space_Timer--; 

			if( Relay_Space_Timer != 0 ) //�ϵ���ʱ�����̵���
			{
				Relay_Space_Timer--;
				if( Relay_Space_Timer==0 ){ relay_direct_flag = 1; run_alarm_flag = 1; }
			}			
		}
		if ( Sclock.Clockbackup[0] > Sclock.Clockmain[0] )//���Ӹı�
		{
		 	if( Sclock.Clockmain[1]&B0000_0001 )
			{
				GetKeyStatus();//����ǰ��Կ״̬(2minһ��)
			}
		 	
		 	if( relay_error || (Sclock.Clockmain[1]==0x30) ) relay_direct_flag = 1;

		 	if( nline_err_flag ) 
		 	{
		 		Keeptime.Times[0]++; 	//���ߵ�����ƽ�����ʱ���1����
		 	}		 	
 		 	if( load_over_flag ) 
 		 	{
 		 		Keeptime.Times[1]++; 	//���������ܳ���ʱ���1����
 		 	}
 		 	if( low_voltage_flag )  
 		 	{
 		 		Keeptime.Times[2]++;	//���Ƿѹ����ʱ���1����
 		 	}
 		 	if( below_60u_flag )  
 		 	{
 		 		Keeptime.Times[3]++;	//�����ܳ���ʱ���1����
 		 		Keeptime.Times[9]++;	//��ͣ���ۼ�ʱ���1����
 		 		Keeptime.Times[11]++;	//��ͣ���ۼ�ʱ���1����
 		 	}
 		 	if( lost_v_flag ) 
 		 	{
 		 		Keeptime.Times[5]++; 	//ʧѹ�ܳ���ʱ���1����
 		 		Lost_V_Timer++;		//�˴�ʧѹ�ۼ�ʱ��
 		 	} 
 		 	
 		 	if( lower_v_flag )
 		 	{
 		 		if( lower_v_event_flag  ) 
	 		 	{
	 		 		Keeptime.Times[6]++; 	//�͵�ѹ����ʱ���1����
	 		 	} 
	 		 	else
	 		 	{
	 		 		Current_Over_Count41++;	//�͵�ѹ��ʱ����ʱ���1����
	 		 	}
 		 	}
 		 	if( high_v_flag )
 		 	{
 		 		if( high_v_event_flag ) 
	 		 	{
	 		 		Keeptime.Times[7]++; 	//�ߵ�ѹ����ʱ���1����
	 		 	} 
	 		 	else
	 		 	{
	 		 		Current_Over_Count51++;	//�ߵ�ѹ��ʱ����ʱ���1����
	 		 	} 		
 		 	}
			
		 	//��ʱ8Mʱ�ӵ�У����
			if( Sclock.Clockmain[1]==0x00 )
			{
				if( Adj_Clk_Timer )
				{
					Adj_Clk_Timer--;	//��ʱ8Mʱ�ӵ�У��ʱ����1h
					if( Adj_Clk_Timer == 0 )  Clk_Adj_Proc();//�����ⲿ��32K�����������ڲ�8M��ƫ��
				}
				if( Adj_Clk_Timer == 0 ) Adj_Clk_Timer = Adjclk_timer_delay;				
			}
			
			//�ز�������Э�̹���
			if( Zb_Comm_Timer )
			{
				if( Zb_Comm_Timer > Zb_Comm_Timer_delay ) Zb_Comm_Timer = 0;
				else Zb_Comm_Timer--;	//�ز�ͨѶ�����ʻָ���ʱ����1min
				
				if( Zb_Comm_Timer == 0 )
				{
					reg_veri_flag = 1;	//�üĴ���У���־
				}
			}
			
			//ͨ��ģ�鳬ʱ��ʱ��
			if( Mod_Comm_Timer1 )
			{
				if( Mod_Comm_Timer1 > Mod_Comm_Timer_delay1 ) Mod_Comm_Timer1 = 0;
				else Mod_Comm_Timer1--;	//�ز�ͨѶ�����ʻָ���ʱ����1min
				
				if( Mod_Comm_Timer1 == 0 )
				{
					//36Сʱû���ز�ͨ��,��λ�ز�,����5minͨ��ģ���쳣��ʱ��ʱ��
					if( (Mode.Plc&0x80) )
					{
						Resetworking_Timer = resetworking_timer_delay;//������λ����
						PLC_RST0;		//��λ�ز�(�����)
					}
					Mod_Comm_Timer2 = Mod_Comm_Timer_delay2; //��λ5min��û��ͨ������Ϊͨ��ģ���쳣
				}
			}
			else if( Mod_Comm_Timer2 )//ͨ��ģ���쳣��ʱ�ж�
			{
				Mod_Comm_Timer2--;
				if( Mod_Comm_Timer2 == 0 )
				{
					if( (commmodule_failed_flag==0) && (commmodule_open_flag==0) ) //ͨ��ģ����뵫��ͨѶ��ʱ
					{
						commmodule_failed_flag = 1;		//��ͨ��ģ���쳣��־
						Store_Meterstatus();
						memcpy( Buf, Sclock.Clockbackup, 7 );
						Syn_Clock();
						Note_Run_Event(ee_commerrn_inpage);	//��¼ͨ��ģ���쳣��ʼ
						memcpy( Sclock.Clockbackup, Buf, 7 );
					}
				}
			}
		 	
		 	if( Ble_RstTimer )
		 	{
		 		Ble_RstTimer--;
		 		if( Ble_RstTimer == 0 )
		 		{
		 			Ble_Step = 1;				//��ѯ��������
		 			Ble_Init();
		 			Ble_RstTimer = Zb_Comm_Timer_delay;
		 		}
		 	}
		 	
		 	if( (Ble_Step == 1) && (Ble_RstTimer == (Zb_Comm_Timer_delay-1)) )	//1����δ�յ�����Ӧ��
	 		{
	 			Ble_Rst();
	 		}
		 		
			if( Progkey.Timer ) Progkey.Timer --;//�����ʱ��1
			
			#if(1 == CHINT_Mode)	
			V_ulDataBuf = Byte2uInt(Ijtimer_Para.Ijtimer.B08);
			if( V_ulDataBuf != 0 ) //��I_J�̽Ӷ�ʱ��
			{
				V_ulDataBuf--;
				Int2Byte(V_ulDataBuf,Ijtimer_Para.Ijtimer.B08);
				I2C_Write_Eeprom(ee_softij_page, ee_softij_inpage, Ijtimer_Para.Ijtimer.B08, 4);	//��Ч�ڼ䣬ÿ���ӱ���һ��
			}	
			#endif	
		}
	}
	
	if ( Sclock.Clockbackup[0] > Sclock.Clockmain[0] )//���Ӹı�(��ֹ����㸽�����ֻ�������)
	{
		run_freeze_flag = 1;	//����ͽ����ж�
		
		if(( Sclock.Clockmain[1]== 0x00)&&( Sclock.Clockmain[2]== 0x00))	//ÿ��00:00һ��
		{
			Outputtype = 0;
			reg_veri_flag = 1;	//Ĭ�����������
			Clr_Zero_Data();	//��������������
		}	
	}	
		
	Syn_Clock();//ͬ�����ͱ���ʱ��	 
}
