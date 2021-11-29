#include "ex_var.h"
#include "ex_func.h"
#include "FM32L0XX.h"  
#include <string.h>
#include "Cpu_card.h"


void Delay_Netu( unsigned char Num )	//Num*1etu
{
	//unsigned int i;
	TicksDelayUs(93*Num*clkmode);
	//for(i=0; i<Num*50; i++);		//1etu=93us(4M),����1etu=186us(2M)
}

//��λ��Ӧ����ʱ��Ϊ400/f~40000/f��100us~10ms
//����ֵ: 1Ϊ�½���; 0Ϊ�ޱ仯
unsigned char Judge_Edge( unsigned char CH )
{
	unsigned int i;

	Delay_Netu(1);

	for( i=0x00; i<100; i++ ) 	//Լ10ms(4M),����20ms(2M)
	{
//		if( CH == ESAM )
//		{
//			if( (U7816SECONDSTATUS0&B0000_0001) == 1 ) //���ڽ���
//			{
//				return 1;
//			}
//		}
//		else
		{
			if( (U7816SECONDSTATUS0&B0000_0001) == 1 ) //���ڽ���
			{
				return 1;
			}
		}
		Delay_Netu(1);
	}
		
	return 0;
}

//�ʱ��ӦΪ9600etu,ĿǰΪ9600etu,1etu=93us
unsigned char Get_7816_Char( unsigned char CH, unsigned char *Data )
{
	unsigned long int i;

//	if( CH == ESAM )
//	{
//		U7816CTRL0 = DEF_USART0CTRL|DEF_USART0TX_EN|DEF_USART0RX_EN|DEF_USART0CLK_EN;	//U7816_1
//	}
//	else
	{
		U7816CTRL0 = DEF_USART0CTRL|DEF_USART0TX_EN|DEF_USART0RX_EN|DEF_USART0CLK_EN;	//U7816_0
	}
	
	for( i=0x00; i<10000; i++ ) 	//Լ900ms(4M),����1800ms(2M)
	{
		Clear_Wdt();
		Delay_Netu(1);
		
//		if( CH == ESAM )
//		{
//			if( U7816PRIMARYSTATUS0&B0000_0001 ) //RX_FLAG�Ѿ���λ
//			{
//				*Data = U7816RXBUF0;
//                	
//				return 1; //�ɹ�
//			}
//                	
//			if( U7816PRIMARYSTATUS0&B0000_0100 ) //ERROR_FLAG�Ѿ���λ
//			{
////				switch( U7816ERRSTATUS ) //���б�־λ: Ӳ����λ��д0����
////				{
////					case B0000_0001: //������������־λ
////						break;
//                	
////					case B0000_0010: //����֡��ʽ�����־λ
////						break;
//                	
////					case B0000_0100: //����������żУ������־λ
////						break;
//                	
////					case B0000_1000: //����������żУ������־λ
////						break;
//                	
////					default:
////						break;
////				}
//                	
//				U7816ERRSTATUS0 &= 0xFFFF; //clear error flag.
//                	
//				return 2; //error
//			}
//		}
//		else
		{
			
			if( U7816PRIMARYSTATUS0&B0000_0001 ) //RX_FLAG�Ѿ���λ
			{
				*Data = U7816RXBUF0;
                	
				return 1; //�ɹ�
			}
                	
			if( U7816PRIMARYSTATUS0&B0000_0100 ) //ERROR_FLAG�Ѿ���λ
			{
//				switch( U7816ERRSTATUS ) //���б�־λ: Ӳ����λ��д0����
//				{
//					case B0000_0001: //������������־λ
//						break;
                	
//					case B0000_0010: //����֡��ʽ�����־λ
//						break;
                	
//					case B0000_0100: //����������żУ������־λ
//						break;
                	
//					case B0000_1000: //����������żУ������־λ
//						break;
                	
//					default:
//						break;
//				}
                	
				U7816ERRSTATUS0 &= 0xFFFF; //clear error flag.
                	
				return 2; //error
			}
		}
		
		if( EA_OFF ) return 3;
	}
	
	return 3;
}

unsigned char Snd_7816_Byte( unsigned char CH, unsigned char Data )
{
	unsigned int i;

//	if( CH == ESAM )
//	{
//		U7816CTRL0 = DEF_USART0CTRL|DEF_USART0TX_EN|DEF_USART0CLK_EN;	//U7816_1
//		Delay_Netu(2);							//��ʱ1��etu,��֤���豸�ȶ�����
//		U7816TXBUF0 = Data;
//	}
//	else
	{
		U7816CTRL0 = DEF_USART0CTRL|DEF_USART0TX_EN|DEF_USART0CLK_EN;	//U7816_0
		Delay_Netu(2);							//��ʱ1��etu,��֤���豸�ȶ�����
		U7816TXBUF0 = Data;
	}
	
	for( i=0x00; i<400; i++ ) 	//Լ39ms(4M),����78ms(2M)
	{
		Clear_Wdt();
		Delay_Netu(1);
		
//		if( CH == ESAM )
//		{
//			if( U7816PRIMARYSTATUS0&B0000_0010 )	//TX_FLAG��λ
//			{
//				return 0; //�ɹ�
//			}
//                	
//			if( U7816PRIMARYSTATUS0&B0000_0100)	//ERROR_FLAG��λ
//			{
////				switch( U7816ERRSTATUS ) //���б�־λ: Ӳ����λ��д0����
////				{
////					case B0000_0001: //������������־λ
////						break;
//                	
////					case B0000_0010: //����֡��ʽ�����־λ
////						break;
//                	
////					case B0000_0100: //����������żУ������־λ
////						break;
//                	
////					case B0000_1000: //����������żУ������־λ
////						break;
//                	
////					default:
////						break;
////				}
//                	
//				U7816ERRSTATUS0 = U7816ERRSTATUS0; //clear error flag.
//                	
//				return 1; //error
//			}
//		}
//		else
		{
			if( U7816PRIMARYSTATUS0&B0000_0010 )	//TX_FLAG��λ
			{
				return 0; //�ɹ�
			}
                	
			if( U7816PRIMARYSTATUS0&B0000_0100)	//ERROR_FLAG��λ
			{
//				switch( U7816ERRSTATUS ) //���б�־λ: Ӳ����λ��д0����
//				{
//					case B0000_0001: //������������־λ
//						break;
                	
//					case B0000_0010: //����֡��ʽ�����־λ
//						break;
                	
//					case B0000_0100: //����������żУ������־λ
//						break;
                	
//					case B0000_1000: //����������żУ������־λ
//						break;
                	
//					default:
//						break;
//				}
                	
				U7816ERRSTATUS0 = U7816ERRSTATUS0; //clear error flag.
                	
				return 1; //error
			}
		}
		
		if( EA_OFF ) return 1;
	}
	
	return 1;
}

void Esam_Err_Report()
{
	if( esam_error==0 )
	{
		Set_Reportdata(0*8+1);//��esam�����ϱ���־
	}
	
	esam_error = 1;
}

//command-response pairs
unsigned char CardTxRxFrame( unsigned char CH, uint08 Lc, uint08 Le )
{
	uint08 k, result, Temp_Data, Temp_SW1, Temp_SW2, Proc_Byte;

	Ic_Comm_RxPtr = 0x00;
	memset( Ic_Comm_RxBuf, 0x00, u7816_buf_size );
	Delay_Netu(10);	//����ʱ10��etu
	Err_Sw12[0] = 0;
	Err_Sw12[1] = 0;
	
//	if(CH == CARD)
//	{
//		result = RF_TxRxFrame(Lc, Le);
//		return (result);
//	}
	
	for( k=0; k<5; k++ )	//send command header (5bytes)
	{
		result = Snd_7816_Byte( CH, Ic_Comm_TxBuf[ k ] );	//;ȡ����������
		if( result == 1 ) { return 1; } //send failure.
	}

	for( ;; )
	{
		result = Get_7816_Char( CH, &Proc_Byte ); //receive procedure byte.
		if( result != 1 ) { return 2; } //receive failure.

		if( Proc_Byte == 0x60 ) //Null byte
		{
			//do nothing. continue to receive.
		}
		else if( Proc_Byte == Ic_Comm_TxBuf[1] ) //procedure byte = INS
		{
			if( k < (Lc+5) )	//send remaining data, then wait for procedure byte.
			{
				if( CH == ESAM ) Delay_Netu(16);	//���յ�INS���뷢������֮��������ʱ16��etu
				
				for( ; k<(Lc+5); )
				{
					result = Snd_7816_Byte( CH, Ic_Comm_TxBuf[ k++ ] ); //;ȡ����������
					if( result == 1 ) { return 3; }	//send failure.
				}
			}
			else
			{
				//;�����ֽ���֮ǰ�ѽ��գ�ֻ����2��״̬�ֽڼ��ɡ�
				for( Ic_Comm_RxPtr=0x00; Ic_Comm_RxPtr<Le; Ic_Comm_RxPtr++ )
				{
					result = Get_7816_Char( CH, &Temp_Data );
					if( result != 1 )	{ return 4; }	//;Receive fail
			
					Ic_Comm_RxBuf[ Ic_Comm_RxPtr ] = Temp_Data;
				}
			}
		}
//		else if( Proc_Byte == (Ic_Comm_TxBuf[1]^0xFF) ) //procedure byte = (INS XOR FFH)
//		{
//			if( k < (Lc+5) )	//send next one data, then wait for procedure byte.
//			{
//				result = Snd_7816_Byte( CH, Ic_Comm_TxBuf[ k++ ] ); //;ȡ����������
//				if( result == 1 ) { return 5;}	//send failure.
//			}
//			else
//			{
//				//;�����ֽ���֮ǰ�ѽ��գ�ֻ����2��״̬�ֽڼ��ɡ�
//				for( Ic_Comm_RxPtr=0x00; Ic_Comm_RxPtr<( Le+2 ); Ic_Comm_RxPtr++ )
//				{
//					result = Get_7816_Char( CH, &Temp_Data );
//					if( result != 1 )	{	return 6;	}	//;Receive fail
//			
//					Ic_Comm_RxBuf[ Ic_Comm_RxPtr ] = Temp_Data;
//				}
//
//				return 0;
//			}
//		}
		else	//other proc byte.
		{
			Temp_SW1 = ( Proc_Byte & 0xF0 );
			
			if( (Temp_SW1 == 0x60) || (Temp_SW1 == 0x90) ) //procedure byte = 6X or 9X (ex. 60H)	
			{
				result = Get_7816_Char( CH, &Temp_SW2 ); //receive sw2.
				if( result != 1 ) { return 7; } //receive failure.
		
				// 61H: send get response command, P3<=XX
				// 6CH: send last command again, P3 = XX;
				// other 6X or 9X, this communication is over.

				//'9000' command normally completed
				//'6E00' CLA not supported
				//'6D00' CLA supported, but INS not programmed or invalid
				//'6B00' CLA INS supported, but P1 P2 incorrect
				//'6700' CLA INS P1 P2 supported, but P3 incorrect
				//'6F00' command not supported and no precise diagnosis given
		
				Ic_Comm_RxBuf[ Ic_Comm_RxPtr++ ] = Proc_Byte;
				Ic_Comm_RxBuf[ Ic_Comm_RxPtr++ ] = Temp_SW2;
				Err_Sw12[0] = Proc_Byte;
				Err_Sw12[1] = Temp_SW2;
				
				if( (Proc_Byte == 0x6A) && (Temp_SW2 == 0x81)&& (CH == ESAM) ) Esam_Err_Report();
				
				if( (Proc_Byte == 0x61) || ((Proc_Byte == 0x90)&&(Temp_SW2 == 0x00)) )
					return 0;
				else
					return 8;
			}
			else
			{
				return 8;
			}
		}
	}

//	return 9;
}

//���㼤��&�临λ
//��⵽�������, RST�õ͵�ƽ, VCC�ϵ�, ��ʱһ��ʱ��, IO����Ϊ����̬, CLK���ʱ���ź�(T0ʱ��)
//��T0��40000~45000��CLK��, ��RST��Ϊ�ߵ�ƽ(T1ʱ��), ��T1���400~40000��CLK��, ��λӦ��Ӧ�ÿ�ʼ, 
//��IC���ĸ�λӦ��û���ڴ�ʱ����ڿ�ʼ, �ն˽������ͷ�ʱ��.���յ���λӦ��, ��������Э��淶, ����Ҫ�ȸ�λ
unsigned char ColdReset( unsigned char CH )
{
	unsigned char n, Result, Temp_ATR;	// T0, TD1, TD2;
	
//	if( CH == ESAM )
//	{
		ESAMPOWERON;
		AltFunIO( GPIOG, GPIO_Pin_2, 0 );	//ESAMCLK
		AltFunIO( GPIOG, GPIO_Pin_3, 0 );	//ESAMIO
		OutputIO( GPIOG, GPIO_Pin_7, 0 );	//ESAMRST
		
		RST_ESAM_L;	
		
		TicksDelayMs(100*clkmode,isPowerOff);		//��ʱ100ms
		if(isPowerOff())return 2;
		
		U7816CTRL0 = DEF_USART0CTRL|DEF_USART0TX_EN|DEF_USART0RX_EN|DEF_USART0CLK_EN;	//U7816_1
		
		//----------------------------------------------------------------------------------------------
		Result = U7816RXBUF0; //RX������, �����rx_flag=1, ����ͨ����ȡRXBUF������˱�־.

		U7816ERRSTATUS0 = 0x0F;    //�������Ĵ���������˳�����Ҫ, ���ܵߵ�
		U7816SECONDSTATUS0 = 0x00;
		U7816PRIMARYSTATUS0 = 0x00;
//	}
//	else
//	{
//		U7816CTRL0 = DEF_USART0CTRL|DEF_USART0TX_EN|DEF_USART0RX_EN|DEF_USART0CLK_EN;;	//U7816_0
//		
//		//----------------------------------------------------------------------------------------------
//		Result = U7816RXBUF0; //RX������, �����rx_flag=1, ����ͨ����ȡRXBUF������˱�־.
//
//		U7816ERRSTATUS0 = 0x0F;    //�������Ĵ���������˳�����Ҫ, ���ܵߵ�
//		U7816SECONDSTATUS0 = 0x00;
//		U7816PRIMARYSTATUS0 = 0x00;
//		
//	}

	TicksDelayMs(5*clkmode,isPowerOff);			//�ȴ�RSTʱ��,����400����,��100us
	if(isPowerOff())return 2;
	
	//-------- T1ʱ��, RST����ߵ�ƽ --------

	RST_ESAM_H;		//set PGIO4.3
	
	Result = Judge_Edge( CH ); 		//40000��CLK�ڲ鿴IO�ڵĵ�ƽ�ر仯
	if( Result == 0 ) //IO��û�г����½���
	{
		//if(CH == ESAM) Esam_Err_Report();
		return 2;	//�쳣: 40000��CLK��û���յ���ʼλ
	}
	
	for(n=0; n<13; n++)
	{
		Result = Get_7816_Char( CH, &Temp_ATR ); //receive TS.
		if( Result != 1 )
		{ 
			//if(CH == ESAM) Esam_Err_Report();
			return 3; 
		}
		Ic_Comm_RxBuf[ n ] = Temp_ATR;
	}
	
	if((Ic_Comm_RxBuf[0] != 0x3b) || (Ic_Comm_RxBuf[1] != 0x69))
	{
		//if(CH == ESAM)	Esam_Err_Report();
		return 3; 
	}
//	if(CH == ESAM) esam_error = 0;	
	return 0;
}

//ESAM��λ
unsigned char EsamReset( void )
{
#if(ESAMON == 1)	
	unsigned char i;
	
	for(i=0; i<3; i++)
	{
		if( EA_OFF ) return(1);		//���粻����,����ֱ�ӷ���
		
		if(ColdReset( ESAM )) 
		{
			CloseEsam();		//�ͷ�ESAM
			Delay_Initial(40);	//��ʱ200ms		
		}
		else
		{
			esam_error = 0;
			memcpy( EsamRst8B, Ic_Comm_RxBuf+5, 8 ); //ESAM���к�, 8bytes.
			return(0);
		}
	}
	Esam_Err_Report();
	return(1);
#else
	esam_error = 0;
	return(0);
#endif	
}

//��ֹESAM����
void CloseEsam( void )
{	
	RST_ESAM_L;	
	U7816CTRL0 = DEF_USART0CTRL;
	ESAMPOWEROFF;
	CloseeIO(GPIOG, GPIO_Pin_2);	//ESAMCLK
	CloseeIO(GPIOG, GPIO_Pin_3);	//ESAMIO
	CloseeIO(GPIOG, GPIO_Pin_7);	//ESAMRST
}


//��λESAM
unsigned char Clear_Rand_Gene( void )
{
	unsigned char result;
	
	Identitytimer = 0x00;
	identity_prog_flag = 0;	//��� ��ȫ��֤��̱�־
	first_prog_flag = 0;//���״α�̱�־

	memset( PcRand,  0x00, 8 );
	memset( PcRst8B, 0x00, 8 );

	result = EsamReset();

	return (result);
}

//�ײ�ͨѶ
void RxTxCommhead( uint08 inc, uint08 com, uint08 P1, uint08 P2, uint08 len)
{
	Ic_Comm_TxBuf[ 0] = inc;
	Ic_Comm_TxBuf[ 1] = com;
	Ic_Comm_TxBuf[ 2] = P1;
	Ic_Comm_TxBuf[ 3] = P2;
	Ic_Comm_TxBuf[ 4] = len;
}

//���������ļ�
unsigned char ReadBinFile( unsigned char CH, unsigned char P1, unsigned char P2, unsigned char Len )
{
	unsigned char Result;

	RxTxCommhead(0, 0xb0, P1, P2, Len);
	
	Result = CardTxRxFrame( CH, 0x00, Len );
	
	return (Result);
}

//���¶������ļ�
unsigned char UpdateBinFile( uint08 CH, uint08 P1, uint08 P2, uint08 Len )
{
	unsigned char Result;

	RxTxCommhead(0, 0xD6, P1, P2, Len);
	
	memcpy(&Ic_Comm_TxBuf[5], Ic_Comm_RxBuf, Len);
				
	Result = CardTxRxFrame( CH, Len, 0x00 ); //CARD Com
	
	return (Result);
}

//����¼�ļ�
unsigned char ReadRecFile( unsigned char P1 )
{
	unsigned char Result;

	RxTxCommhead(0, 0xb2, P1, 0x14, 0x04);
	
	Result = CardTxRxFrame( ESAM, 0x00, 0x04 );

	return (Result);
}

//ȡ��Ӧ����
unsigned char Read_Kx( unsigned char CH, unsigned char Len )
{
	unsigned char result;

	RxTxCommhead(0, 0xC0, 0, 0, Len);
	
	result = CardTxRxFrame( CH, 0x00, Len ); //Esam Com

	return (result);
}

//ȡ�����
unsigned char ReadRandom( unsigned char CH, unsigned char Len )
{
	unsigned char result;
	
	RxTxCommhead(0, 0x84, 0, 0, Len);
	
	result = CardTxRxFrame( CH, 0x00, Len );
	
	if( result == 0 )
	{
		if(CH == ESAM)	//ȡESAM�����
		{
			memcpy(EsamRand, Ic_Comm_RxBuf, Len);
		}
//		else		//ȡ��Ƭ�����
//		{
//			memcpy(CardRand, Ic_Comm_RxBuf, Len);
//		}
	}
	
	return (result);
}

//���ܣ��ڲ����ⲿ��֤����
unsigned char Auth_In_Out( unsigned char INS, unsigned char CH, unsigned char P2, unsigned char *BufA )
{
	unsigned char Result;

	if(INS == 0xfa)
	{
		RxTxCommhead(0x80, INS, 0, P2, 0x08);
	}
	else
	{
		RxTxCommhead(0, INS, 0, P2, 0x08);
	}

	memcpy(&Ic_Comm_TxBuf[5],BufA, 8);	

	Result = CardTxRxFrame( CH, 0x08, 0x00 ); //CARD Com

	return (Result);
}

unsigned char Cal_Mac_Pro(unsigned char P2, unsigned char *BufA , unsigned char Len)
{
	unsigned char Result;

	RxTxCommhead(0x80, 0xfa, 1, P2, Len);		//����Աȣ�MAC����
	memcpy(&Ic_Comm_TxBuf[5],BufA, Len);	

	Result = CardTxRxFrame( ESAM, Len, 0x00 ); 	//CARD Com
	if(Result) return 1;
	
	Result = Read_Kx( ESAM, 64 );			//ȡESAM���ܽ��
	return (Result);
}


//�ɴ�MAC���������е�M2ѡ��
const uint08 code ConstIns[12] =
	{ 
		0x04, 0xd6, 0x86,	//������MAC����(0x86Ϊ��MAC��ESAM��)
		0x84, 0x32, 0x01,	//�û�����Ǯ���ļ�
		0x04, 0xdc, 0x01,	//Ԥ�ƿ���ʣ����
		0x04, 0xdc, 0x03,	//Ԥ�ƿ����������
	};


//=====��MAC��ȡ�������ļ�
//Le����MAC����������ݳ���
unsigned char ReadBinWithMac( uint08 CH, uint08 P1, uint08 P2, uint08 Le )
{
	unsigned char result, Temp, Type;
	
	RxTxCommhead(0x04, 0xB0, P1, P2, 0x11);
	Clear_Wdt();
	
	Type = (CH&B1111_0000)>>4;
	if( (CH&B0000_1111) == CARD )	//��CARD����
	{
		Ic_Comm_TxBuf[4] = 9;
		memcpy(Ic_Comm_TxBuf+5, EsamRand, 4);//�Կ�Ƭ������ȡESAM�����
		
		memcpy( Ic_Comm_TxBuf+9, ConstIns+Type*3, 3 );
		if( Type == 0 )
		{
			Ic_Comm_TxBuf[11] = P1;	//��MAC����Ƭ�������ļ��ź�ƫ�Ƶ�ַͬESAM
			if( P1==0x85 ) Ic_Comm_TxBuf[11] = 0x87;//��բ��������
			Ic_Comm_TxBuf[12] = P2;
		}
		else
		{
			Ic_Comm_TxBuf[12] = 0x14;
		}
		Temp = Le;	//��Ƭֱ�ӷ������ݣ�����ȡ��
	}
	else//��ESAM����
	{
//		if( Comm_Auth_Judge() )//Զ�̴�mac��
			memcpy(Ic_Comm_TxBuf+5, PcRand, 4);
//		else
//			memcpy(Ic_Comm_TxBuf+5, CardRand, 4);

		memcpy( Ic_Comm_TxBuf+9, ConstIns, 3 );
		
		Ic_Comm_TxBuf[12] = P2;
		if( P1<0x04 )
		{
			Ic_Comm_TxBuf[ 1] = 0xB2;	//��MAC��Ǯ����������0xB2
			Ic_Comm_TxBuf[12] = 0x00;
		}
		
//		if(CH == ESAM)
//			memcpy(Ic_Comm_TxBuf+14, CardRst8B, 8);
//		else
			memcpy(Ic_Comm_TxBuf+14, PcRst8B, 8);
		
		Temp = 0;
	}
	Ic_Comm_TxBuf[13] = Le;
	if(CH == ESAM+0x10) Ic_Comm_TxBuf[13] += 8;	//���ݻس���״̬��ѯ��+8�ֽ�
	
	CH &= B0000_0001;
	result = CardTxRxFrame( CH, Ic_Comm_TxBuf[4], Temp );//����data+MAC
	if( result ) return (result);
	
	if(CH == ESAM)
	{
		result = Read_Kx(ESAM, Le ); //����data+MAC
	}

	return ( result );
}

//======��MAC���¶������ļ�
unsigned char WriteBinWithMac( uint08 CH, unsigned char P1, unsigned char P2, unsigned char Len )
{
	unsigned char  Result;

	RxTxCommhead(0x04, 0xd6, P1, P2, Len);
	if(CH>1) Ic_Comm_TxBuf[1] = 0xdc;		//��MACдǮ���ļ�
	if(Len == 4) Ic_Comm_TxBuf[ 0 ] = 0;//CLA ����MAC
	CH &= B0000_0001;

	memcpy(&Ic_Comm_TxBuf[5], Ic_Comm_RxBuf, Len);

	Result = CardTxRxFrame( CH, Len, 0x00 ); //CARD Com

	if( Result )
	{
		if( (Err_Sw12[0] == 0x69) && (Err_Sw12[1] == 0x88) ) return(IC_MAC_ERR);//MACУ�����(6988)
		else if(CH == ESAM) return(IC_ESAM_RDWR_ERR);
		else return(IC_NOIN_ERR);
	}
	return(Result);
}


unsigned char Authorization( unsigned char *Buf, unsigned char Len )
{
	unsigned char Result;

	//���ܱ��ESAM����������⣺
	//a����Կ��ɢ���80fa000108+8�ֽڷ�ɢ���ӣ�
	//;Esam encryp random data.
	Result = Auth_In_Out(0xfa, ESAM, 0x03, Buf+16 );
	if( Result != 0x00 )	return 1;
	
	//b��������������80fa000008+�������
	Result = Auth_In_Out(0xfa, ESAM, 0x00, Buf+8 );
	if( Result != 0x00 )	return 1;
	
	//c��ȡ�������00c0000008��
	//�Ƚ�����1������2, ���߲�����򱨾�, ���������������
	//;Read K2 from Esam
	Result = Read_Kx( ESAM, 0x08 );
	if( Result != 0x00 )	return 1;
	
	if( Len == 4 )
	{
		if( Cmp_Data(Buf, Ic_Comm_RxBuf, 8) != 3 ) return 1;//Reset failure.
	}
	else
	{
		memcpy( Buf, Ic_Comm_RxBuf, 8 );
	}

	//ȡ�����2��0084000004
	//;Read random in ESAM
	Result = ReadRandom( ESAM, Len );
	return ( Result );
}


//ѡ���ļ�
unsigned char SelectFile( unsigned char CH, unsigned char F1, unsigned char F2 )
{
	unsigned char Result;
	
	RxTxCommhead(0,0xa4, 0, 0, 2);	
	Ic_Comm_TxBuf[ 5 ] = F1;	//DATA0
	Ic_Comm_TxBuf[ 6 ] = F2;	//DATA1
	
	Result = CardTxRxFrame( CH, 0x02, 8 );	//����8�ֽ�
	
	return (Result);
}


//�жϿ�Ƭ���ݸ�ʽ
unsigned char JudgeFile(unsigned char Len)
{
	unsigned char Csdata;

	Csdata = Cal_ChkSum(Ic_Comm_RxBuf+1, Len+3);
	if( (Ic_Comm_RxBuf[0] != 0x68) || (Ic_Comm_RxBuf[Len+4] != Csdata) || (Ic_Comm_RxBuf[Len+5] != 0x16) ) return 1;//֡��ʽ����: 68H/CS/16H
	return 0;
}


//�Ƚϱ���Ƿ���ͬ
unsigned char Cmp_Meter_Id(unsigned char *Buf)
{
	if ( Cmp_Data( Esam_Para.Meter_Id, Buf, 6) != 3 ) return 1;
	return 0;
}


//������Զ�̷ѿصĳ���
//MACУ����������
//�ۼ�MACʧ��100�ι���
void Mac_Err_Proc( void )
{
	if(Mac_Err_Times < 200) Mac_Err_Times++;
	if(Mac_Err_Times >= 200)
	{
		Mac_Err_Times = 0x00;	//����
		hangup_comm_flag = 1;	//Ҫ����ܱ�Զ�����ò������ܹ���
	}
}

unsigned char Update_ESAM_Bin_Mac( unsigned char P1, unsigned char P2, unsigned char *Buf, unsigned char Len )
{
	unsigned char result;
	
	Exchange( Ic_Comm_RxBuf, Buf, Len );
	Exchange( Ic_Comm_RxBuf+Len, Buf+Len, 4 );

	result = WriteBinWithMac( ESAM, P1, P2, Len+4 );
	if( result )
	{
		Mac_Err_Proc();	//mac���������1
	}
	
	return (result);
}


//ͬ������esam������Ϣ�ļ�
void UpdataRunFile(void)
{
	unsigned char Buf[60];
	
	ReadBinFile( ESAM, 0x86, 0, 50 );	//��ȫ��06�ļ�
	memcpy( Buf, Ic_Comm_RxBuf, 50 );	//06�ļ����ݱ���
	
	Ic_Comm_RxBuf[0] = 0x68;
	Ic_Comm_RxBuf[1] = 0x11;							//�û�����д
	Ic_Comm_RxBuf[2] = 0x00;
	Ic_Comm_RxBuf[3] = 0x2c;
	
//	Bcd2Hex( Money.Remain, Ic_Comm_RxBuf+23, 4);		//ʣ����
//	memcpy( Ic_Comm_RxBuf+27, Money.Buy_Times.B08, 4 );	//�������
//	memcpy( Ic_Comm_RxBuf+31, Money.Tick, 4 );					//͸֧(BCD)	
//	
//	Save_Keep_Timer(0);
//	Hex2Bcd( Eeprom.Buffer+1, Ic_Comm_RxBuf+39, 3 ); 	//�Ƿ����������� 3 BCD
		
	memcpy( Ic_Comm_RxBuf+5, Esam_Para.Current_Ratio,18 );//���1+���2+���+�ͻ����
//	Ic_Comm_RxBuf[47] = Display_Para.MeterCtrl;	//���ģʽ��
	
	if( (Cmp_Data( Ic_Comm_RxBuf, Buf, 48) != 3) )
	{
		Exchange( Ic_Comm_RxBuf+42, Sclock.Clockbackup+1, 5 );//��ʱ������
		//����CS
		Ic_Comm_RxBuf[48] = Cal_ChkSum(Ic_Comm_RxBuf+1, 47);
		Ic_Comm_RxBuf[49] = 0x16;
		
		UpdateBinFile(ESAM, 0x86, 0, 50 );
	}
}

unsigned char GetPswBit( unsigned char *InBuf )
{
	unsigned char i, n, Temp08;

	Temp08 = Feik.Num[7];
	if( Temp08 > MAX_PSW_NUM ) Temp08 = MAX_PSW_NUM;	//��Կ�������Ƿ�Ĭ��

	for( i=0; i<Temp08; i++ )	//�����������õ���Կ������.
	{
		if( (i%8) == 0 ) n = 1;
		else n <<= 1;
		
		if( InBuf[0]&1 )
		{
			if( (InBuf[i/8]&n) == 0x00 ) return 0xFF;
		}
		else
		{
			if( InBuf[i/8]&n ) return 0xFF;
		}
	}
	
	return (InBuf[0]&1);
}

//����Կ״̬��
void GetKey( unsigned char *KeyStatus )
{
	I2C_Read_Eeprom44( ee_keystatus_page, KeyStatus, ee_keystatus_lenth );
}

//д��Կ״̬��
void SetKey( unsigned char *KeyStatus )
{
	I2C_Write_Eeprom44( ee_keystatus_page, KeyStatus, ee_keystatus_lenth );
	GetKeyStatus();
}

//����ǰ��Կ״̬
void GetKeyStatus()
{
#if(ESAMON == 1)	
	unsigned char Buf[32];
	
	GetKey( Buf ); //����Կ״̬
	Key_Status = GetPswBit( Buf );
#else
	Key_Status = 0;//Ĭ�Ϲ�Կ
#endif	
}


unsigned char GetSetBitNum( unsigned char *InBuf )
{
	unsigned char i, k, n;

	for( i=0, k=0; i<MAX_PSW_NUM; i++ )	//ͳ�������ص���Կ������
	{
		if( (i%8) == 0 ) n = 1;
		else n <<= 1;
		if( InBuf[i/8] & n ) k++;
	}
	
	return (k);
}


unsigned char UpdateEepromKey( unsigned char Ch )
{
	unsigned char i, k, result;
	unsigned char Buf[64], ChangeBuf[32];
	unsigned char FramePswNum, MeterPswNum, SettedPswNum;

	if( Uart[Ch].Buf[9] <= 12 ) return 1;
	
	//FramePswNum:  ����֡�а�������Կ����.
	//MeterPswNum:  �����������õ���Կ������.
	//SettedPswNum: �����ص���Կ������(�������ظ����µ���Կ)
	FramePswNum = (Uart[Ch].Buf[9]-8-4)/36;
	if( (FramePswNum==0) || (FramePswNum>4) || ((Uart[Ch].Buf[9]-8-4)%36) ) return 1;

	MeterPswNum = Feik.Num[7];
	if( MeterPswNum > MAX_PSW_NUM ) MeterPswNum = MAX_PSW_NUM;	//��Կ�������Ƿ�Ĭ��

	//ee_keystatus_page: 
	//��Կ״̬��(4)  : ���Ϲ����涨�ġ���Կ״̬�֡���
	//��Կ״̬(1)    : (Ԥ��)
	//����״̬(1)    : ��Կ���µĹ���״̬ (00����дE2PROM, 55����дESAM, AA�������).
	//���µ�E2PROM(4): ���չ����涨�ġ���Կ״̬�֡���ʽ��ÿ����һ����E2PROM ��Ӧbit��1.
	//���µ�ESAM(4)  : ���չ����涨�ġ���Կ״̬�֡���ʽ��ÿ����һ����ESAM ��Ӧbit��1.(Ԥ��)
	//����Կ״̬��(4): ���չ����涨�ġ���Կ״̬�֡���ʽ��0Ϊ��Կ��1Ϊ˽Կ��
	//ee_keystatus1_page:
	//�����ߴ���(4)  : ���¼�¼�еĲ����ߴ����ǵ���յ���һ����Կ���������еĲ����ߴ���.
	//��Կ���µ�������(1) HH
	//����ǰ��Կ״̬��(4):
	GetKey( ChangeBuf );
	if( ChangeBuf[5] == 0x55 )return 0; //����״̬: 00����������E2PROM; 55����������ESAM; AA�Ѹ��½���.
	if( ChangeBuf[5] != 0x00 ) //����������Կ
	{
//		ChangeBuf[4] &= 0x3F;	//���Bit7��Bit6��
		ChangeBuf[5] = 0x00;	//ֻ�и��½�����������һ�ֵĸ��¡�
		memset( ChangeBuf+6, 0x00, 12 ); //��ո��µı�־λ��
		
		memcpy( Eeprom.Buffer, Uart[Ch].Buf+14, 4 );	//�����ߴ���
		Eeprom.Buffer[4] = MeterPswNum;	//��Կ���µ�������(1) HH
		memcpy( Eeprom.Buffer+5, ChangeBuf, 4 );	//����ǰ����Կ״̬��
		I2C_Write_Eeprom( ee_keystatus1_page, ee_keystatus1_inpage, Eeprom.Buffer, ee_keystatus1_lenth ); 
	}

	memcpy( Buf, Uart[Ch].Buf+18, 36 );
//	for( i=1; i<FramePswNum; i++ ) Xor_Data( Buf, Uart[Ch].Buf+18+i*36, 36 );

	//��Ч����Կ����
	for( i=0, k=0; i<FramePswNum; i++, k+=36 )
	{
		if(i) Xor_Data( Buf, Uart[Ch].Buf+18+k, 36 );
		
		//��Կ������+Ԥ��+��Կ���+��Կ״̬
		if((Uart[Ch].Buf[18+32+k] > 0x01) //��Կ״̬��־λ��00-����״̬��01-��ʽ״̬��
		 ||(Uart[Ch].Buf[18+32+k] != Uart[Ch].Buf[18+32+0]) ) return 1; //����Ӧ��: ���ĳ�����Կ״̬��־λ��һ��
		if( Uart[Ch].Buf[18+33+k] >= MeterPswNum ) return 1;	//��Կ��ų���.
		if( Uart[Ch].Buf[18+35+k] != MeterPswNum ) return 1;	//����Ӧ��: �����е���Կ�����������������Կ��������һ��.

		ChangeBuf[6+Uart[Ch].Buf[18+33+k]/8] |= (1<<(Uart[Ch].Buf[18+33+k]%8));	//��¼������Կ���.
		
		if( Uart[Ch].Buf[18+32+k] )
			ChangeBuf[14+Uart[Ch].Buf[18+33+k]/8] |= (1<<(Uart[Ch].Buf[18+33+k]%8));
		else
			ChangeBuf[14+Uart[Ch].Buf[18+33+k]/8] &= ~(1<<(Uart[Ch].Buf[18+33+k]%8));
	}

//	memset( Buf+36, 0x00, 8 );
//	if( (Uart[Ch].Buf[18+32+0]&0x7F) == 0x00 )	Buf[36] = 0x01; //��Կ�ָ�ʱ�̶�Ϊ01
//	else	Exchange( Buf+36, Esam_Para.Meter_Id, 6 );	//��Կ��װʱȡ���
	Exchange( Buf+36, Esam_Para.Meter_Id, 6 );	//��Կ��װʱȡ���
	Buf[42] = 0x00;
	Buf[43] = 0x00;
	memcpy( Buf+44, Uart[Ch].Buf+10+Uart[Ch].Buf[9]-4, 4 ); //MAC
	
	result = Update_ESAM_Bin_Mac( 0x95, 0x00, Buf, 44 );	//
	if( result != 0x00 ) return 4;	//�����������MAC У����ǲ��ô�����Ϣ��ERR ��bit2�������/δ��Ȩ����λ���������쳣Ӧ��֡��Ӧ��
	
	SettedPswNum = GetSetBitNum( ChangeBuf+6 ); //ͳ�������ص���Կ������
	if( SettedPswNum == MeterPswNum ) //���µ���Կ�����ﵽ������
	{
		result = GetPswBit( ChangeBuf+14 );
		if( result != 0xFF ) 	//�ж���Կ״̬�Ƿ�һ��
		{
			ChangeBuf[5] = 0x55; //������������ESAM��־
		}
	}
	else if( SettedPswNum > MeterPswNum ) return 1;	//����Ӧ�����ص���Ч��Կ����>������Կ������

	for( i=0, k=0; i<FramePswNum; i++, k+=36 )
	{
		Inverse( Uart[Ch].Buf+18+k, 32 );	//ֻ������Կ
		I2C_Write_Eeprom( ee_keydata_1_page+Uart[Ch].Buf[18+33+k]/2, 32*(Uart[Ch].Buf[18+33+k]%2), Uart[Ch].Buf+18+k, 32 );
	}

	SetKey( ChangeBuf ); //���ȼ�¼����Կд��E2PROM�����.

	return 0;
}


//����Ƿ�����Կ����µ�ESAM��������¡�
unsigned char UpdateEsamKey( void )
//��������: ��ǰ�����Կ״̬
{
	unsigned char i, k, n, result, key, Bkmain;
	unsigned char TmpBuf[32];
	
	GetKey( TmpBuf );
	if( TmpBuf[5] == 0x55 ) //����״̬: 00����������E2PROM; 55����������ESAM; AA�Ѹ��½���.
	{
		key = GetPswBit( TmpBuf+14 );
		for( i=0; i<MAX_PSW_NUM; i++ )
		{
			
			if( (i%8) == 0 ) k = 1;
			else k <<= 1;
			
			if( (TmpBuf[6+i/8]&k)  )
			{
				//��������ESAMָ��
				for( n=0; n<3; n++ )
				{
					if( i == 0x00 )
						RxTxCommhead(0x84, 0xd4, 1, 0x00, 0x20); //������Կ����
					else
						RxTxCommhead(0x84, 0xd4, 1, 0xff, 0x20); //������Կ����

					result = I2C_Read_Eeprom( ee_keydata_1_page+i/2, 32*(i%2), Ic_Comm_TxBuf+5, 0x20 );
					if( result ) continue;
					
					result = CardTxRxFrame( ESAM, 0x20, 0x00 );
					if( result == 0x00 ) break;
				}
				
				if( ( i == 0 )||( result == 0 ) )
				{
					if( i == 0 ) Bkmain = TmpBuf[0]; 
					
					if( key == 0 ) TmpBuf[i/8] &= (~k);
					else TmpBuf[i/8] |= k;
					
					if( ( i == 0 )&&( result == 0 ) ) Bkmain = TmpBuf[0]; 	//�ɹ�����������Կ
				}
				else
				{
					if( EA_OFF ) return 0x00; 	//���¹����г���ͣ��,�ϵ����Կ���Ϊ0����Կ��ʼ��ESAM���½�����Կ����
					break;				//����ʧ��,���ٶԱ�����Կ֮�����Կ���и���
				}
			}
		}
		
//		if( i == MAX_PSW_NUM )
//		{			
			key = GetPswBit( TmpBuf);
			
			if( key == 0xFF )	
			{
				if( (Bkmain & 0x01) == 0 ) TmpBuf[0] &= 0xFE;		//����ʧ��,�ָ�����״̬
				else TmpBuf[0] |= 1;
			}
			
			TmpBuf[5] = 0xAA;	//ȫ���������
//		}

		for( n=0; n<3; n++ )
		{
			Exchange( Ic_Comm_RxBuf, TmpBuf, 4 );//����4�ֽ���Կ״̬
			result = UpdateBinFile( ESAM, 0x85, 0x00, 4 );	//дesam��05�ļ�
			if( result == 0x00 ) break;
			if( EA_OFF ) return 0x00; 
		}
		
		SetKey( TmpBuf ); //���ȼ�¼����Կд��E2PROM�����.
		
		//--- ��Կ���¼�¼ ---
		I2C_Read_Eeprom( ee_keystatus1_page, ee_keystatus1_inpage, Eeprom.Buffer+6, ee_keystatus1_lenth ); 
		Event_Record( ee_keysetn_inpage );
		//--- ��Կ���¼�¼ end---
	}

	return 0x00;
}


void FailKey( void )
{
	unsigned char Buf[64];

	GetKey( Buf );
	if( Buf[5] != 0xAA )
	{
		memset( Buf+4, 0x00, ee_keystatus_lenth-4 ); //��ո��µı�־λ��
		Buf[5] = 0xAA;
		SetKey( Buf );
	}
}


//�������
void Clear_Meter( unsigned char Ch, unsigned char *Opt )
{
	unsigned char i;
	
	Clear_Wdt();
		
	ClrRecTimes( 0, 0xaa );//�嶳����¼���Чָ��(�������¼)
	
	//״̬��,������غ͸��ɼ�¼ָ������
	memset( &System_St_Bk, 0x00, ee_reportdata_lenth );
	memset( Load.Point, 0x00, sizeof(Load) );
	memset( Eeprom.Buffer, 0, 64 );
	I2C_Write_Eeprom( ee_validnum_page, ee_validnum_inpage, Eeprom.Buffer, ee_validnum_len ); //������Ӷ�����Ч����ҳ
	
	//�������������
	Clr_Zero_Data();
	
	//�������ʱҪ���Զ����բ��Զ�̱���״̬�����������״̬
	if( Relay_Mode == 0x55 )//���ü̵���
	{
		relay_cleardl_flag = 1;	//�����ñ������־
	}
	relay_commu_alarm_flag = 0;
	
	Clr_Commu_Relaydata();
	Store_Meterstatus();
	
	//������õ���/�����õ���/��1~4���õ���
	Process_Usedl(3);
	Process_Usedl(4);
	Process_Usedl(5);

	//��¼�����¼�
	//�����¼���¼������ʱ��(6)+�����ߴ���(4)+�������ǰ�����й�(4)+�������ǰ����(4)	
	//�洢��������ʱ���򣬵��ֽ���ǰ�����ֽ��ں�
		
	memcpy( Eeprom.Buffer+6, Opt, 4 );	//�����ߴ���(4),Զ������
	
	DltoEepromBuf( 10 );
	Four_RpdltoEepromBuf( 18 );
	Event_Record( ee_clearn_inpage );

	//�� XRAM��E2����
	Veri_Btmr1_Pcount(1);		//������β��
	Veri_Btmr2_Pcount(1);		//������β��
	
	memset( Fwdl.Pluse[0].B08, 0x00, ee_fwdl_lenth+2 );		//���������
	WriteE2WithBackup( ee_fwdl_page, ee_fwdl_inpage, Fwdl.Pluse[0].B08, ee_fwdl_lenth );

	memset( Bkdl.Pluse[0].B08, 0x00, ee_bkdl_lenth+2 );		//�巴�����
	WriteE2WithBackup( ee_bkdl_page, ee_bkdl_inpage, Bkdl.Pluse[0].B08, ee_bkdl_lenth );
	
	for(i=0; i<4; i++)
	{
		memset( Rpdl[i].Pluse[0].B08, 0x00, ee_rpdl_lenth+2 );	//���������޹�����
		WriteE2WithBackup( ee_rpdl_page+2*i, ee_rpdl_inpage, Rpdl[i].Pluse[0].B08, ee_rpdl_lenth );
	}
	
	//����ʾ�����յ����������Ͷ���ͨѶ������
	memset( FreezeBuf, 0x00, sizeof(FreezeBuf) );
//	memset( Freeze_Commbuf, 0x00, sizeof(Freeze_Commbuf) );
	Display_Para.Dl_Dot_Auto = 0;	//���������Ӧ��ʾС��λ��
	run_price_flag = 1;		//�������������жϽ���ֵ
	
	Mt_Alarmstatus_Judge();
	if( relay_status_flag ) ClrRecTimes( ee_openrelayn_inpage, 0x01 );//����բ��¼
	else ClrRecTimes( ee_closerelayn_inpage, 0x01 );//���բ��¼
	
	Wr_Powerdown_Data(0);//д����������ݵ�����ee
	Wr_Pretime_Hisfreeze();	//д��һ�ν���ʱ��
	Wr_Pretime_Dayfreeze();	//д��һ���ն���ʱ��
	
#if(1 == CHINT_Mode)
	if( progenable )/*����ģʽ��ȫ������*/
	{
		ClrRecTimes( 0, 0xff );//�嶳����¼���Чָ��(���������¼)
	}
#endif
}

void Factory_Init( void )
{
	unsigned char i, len;
	unsigned char Buf[72];
	
	//����Чָ��ҳ
	ClrRecTimes( 0, 0xff );//�嶳����¼���Чָ��
	
	//��ʼ����������ź���������
	Exchange( Buf, (uint08*)Softbk, ee_softbk_lenth );	
	I2C_Write_Eeprom( ee_softbk_page, ee_softbk_inpage, Buf, ee_softbk_lenth );
	Exchange( Buf, (uint08*)Facdate, ee_meterdate_lenth );	
	I2C_Write_Eeprom( ee_meterdate_page, ee_meterdate_inpage, Buf, ee_meterdate_lenth );
	
	//����ͣ��, ��λ����, hardfault��λʱ��ʹ���ҳ
	Clear_Wdt();
	memset( Buf, 0x00, 64 );
	for( i=0; i<3; i++ )
	{
		I2C_Write_Eeprom44( ee_xtlfstop_time_page+i, Buf, 18 );
	}
	Wr_Ext_Number = 0;//����չ��������дee����
	
	memset( (uint08*)SynFlash.HisRec, 0, ee_synflash_len );
	I2C_Write_Eeprom( ee_synflash_page, ee_synflash_inpage, (uint08*)SynFlash.HisRec, ee_synflash_len );
	
	relay_commu_close_flag = 0;//Ĭ�ϱ�����״̬
	Store_Meterstatus();
	
	//��ʼ�����ܱ�λ����Ϣ
	I2C_Write_Eeprom( ee_meterpos_page, ee_meterpos_inpage, Buf, ee_meterpos_lenth );	
		
	//��1~60�����������ڼ���ʱ�α��: 00000000
	for( i=0; i<4; i++ )
	{
		I2C_Write_Eeprom( ee_holiday_page+i, 0x00, Buf, ee_holiday_lenth );
	}
	
	//����������
	I2C_Write_Eeprom(ee_bleslamac_page, ee_bleslamac_inpage, Buf, ee_bleslamac_lenth);
	I2C_Write_Eeprom(ee_blerefer_page, ee_blerefer_inpage, Buf, ee_blerefer_lenth);
	Buf[0] = 0x40;//�����㲥ʱ��
	I2C_Write_Eeprom(ee_blerefer_page, ee_blegbtime_inpage, Buf, ee_blegbtime_lenth);
	
	//�����ʼ��
	WriteE2WithBackup( ee_password_page, ee_password_inpage, (uint08*)Def_Password3_table, ee_password_lenth );
	WriteE2WithBackup( ee_password_page, ee_password4_inpage, (uint08*)Def_Password4_table, ee_password_lenth );
		
	//���,��ŵ�(˫����)
	ReadE2WithBackup( ee_esampara_page, ee_esampara_inpage, Buf, ee_esampara_lenth );
	if( IsMultiBcd( Buf, 6 ) )//�Ƿ�����
	{
		memset( Buf, 0x00, 6 );	//���(6)
		Buf[2] = 0x01;//�������1
		Buf[5] = 0x01;//��ѹ���1
	}
//	memset( Buf+6, 0x00, 6 );	//���(6),��Ų���ʼ��
//	Buf[11] = 0x01;//���0x000000000001
	memset( Buf+12, 0x00, 6 );	//�ͻ����(6)
	memset( Buf+18, 0xff, 6 );	//ģ��id(6)
	Buf[24] = Defaultauthtimer>>8;//�����֤��Чʱ��
	Buf[25] = Defaultauthtimer;
	WriteE2WithBackup( ee_esampara_page, ee_esampara_inpage, Buf, ee_esampara_lenth );
	memcpy( Esam_Para.Current_Ratio, Buf, ee_esampara_lenth+2 );
//	I2C_Write_Eeprom( ee_zbid_bk_page, ee_zbid_bk_inpage, Buf+18, ee_zbid_bk_lenth ); //дԭ�ز�id����(ͨѶ����ר��)
	
	//��ʾ����(˫����)
	WriteE2WithBackup( ee_displaypara_page, ee_displaypara_inpage, (uint08*)Def_DisplayPara_table, ee_displaypara_lenth );
	memcpy( &Display_Para.S_Number, Def_DisplayPara_table, ee_displaypara_lenth );
	
	//�л�ʱ��(˫����)
	memset( Starttime.Shiqu, Defaultstartup, ee_starttimer_lenth );
	WriteE2WithBackup( ee_starttimer_page, ee_starttimer_inpage, Starttime.Shiqu, ee_starttimer_lenth );
	memset( Buf, 0xff, ee_changecontrol_lenth );	//ʱ��ʱ�ξ�ʹ�õ�һ��
	I2C_Write_Eeprom44( ee_changecontrol_page, Buf, ee_changecontrol_lenth );
	run_timezone_flag = 1;
	
	//����ģʽ��(˫����)
//	memcpy( Buf, Def_featureword_table, ee_featureword_lenth );
////	Buf[0] = Mode.Bps[0]; //����BPS
//	if( Extbattery == 0x55 ) Buf[ee_featureword_lenth-2] &= B1111_1101; //���ñ�Ƿѹ�رձ���
	WriteE2WithBackup( ee_featureword_page, ee_featureword_inpage, (uint08*)Def_featureword_table, ee_featureword_lenth );
	memcpy( Mode.Bps, Def_featureword_table, ee_featureword_lenth );
	mode_veri_flag = 1;	
	reg_veri_flag = 1;
			
	//�����պ͸��ɲ���(˫����)
	WriteE2WithBackup( ee_weekholiday_page, ee_weekholiday_inpage, (uint08*)Def_weekloadpara_table, ee_weekholiday_lenth );
	memcpy( &Week_Holiday.Status, Def_weekloadpara_table, ee_weekholiday_lenth );
	
	//�ѿ���
	WriteE2WithBackup( ee_feik_number_page, ee_feiknumber_inpage, (uint08*)Def_feik_table, ee_feiknumber_lenth );
	memcpy( Feik.Num, Def_feik_table, ee_feiknumber_lenth );

	//������
	WriteE2WithBackup( ee_histroyparameter_page, ee_histroyparameter_inpage, (uint08*)Def_histroyparameter_table, ee_histroyparameter_lenth );
	
	//�������
	I2C_Write_Eeprom44( ee_freezeparameter_page, (uint08*)Def_freezeparameter_table, ee_freezeparameter_lenth );
	
	//��ѹ�ϸ��ʵ���ز���
	memcpy( VolLimit.MaxVolLmt.B08, Def_vollmtpara_table, ee_vollimit_lenth );
	WriteE2WithBackup( ee_vollimit_page, ee_vollimit_inpage, VolLimit.MaxVolLmt.B08, ee_vollimit_lenth );

	Clear_Wdt();
		
	//��һ�ף��ڶ���ʱ��������
	I2C_Write_Eeprom( ee_shiqu1_page, 0x00, (uint08*)Def_sqb_table1, ee_shiqu_lenth );
	I2C_Write_Eeprom( ee_shiqu2_page, 0x00, (uint08*)Def_sqb_table2, ee_shiqu_lenth );
	
	//��һ�ף��ڶ��� ����8����ʱ�α�
	I2C_Write_Eeprom( ee_shiduantable1_1_page, 0x00, (uint08*)Def_sdb_table1, ee_shiduantable_lenth );
	for( i=1; i<8; i++ )
	{
		I2C_Write_Eeprom( ee_shiduantable1_1_page+i, 0x00, (uint08*)Def_sdb_table2, ee_shiduantable_lenth );
	}
	
	I2C_Write_Eeprom( ee_shiduantable2_1_page, 0x00, (uint08*)Def_sdb_table2, ee_shiduantable_lenth );
	for( i=1; i<8; i++ )
	{
		I2C_Write_Eeprom( ee_shiduantable2_1_page+i, 0x00, (uint08*)Def_sdb_table1, ee_shiduantable_lenth );
	}
	
	Tariff.Crc16.B08[0] += 1;
	
	//�Զ�ѭ����ʾ��Ŀ�б�
	for( i=0; i<31; i++ ){Buf[i*2+0] = 0x01; Buf[i*2+1] = 0x02;} //512+1(0x201)��ʾ��ͨ��ϵ���  1024+1(0x401)��ʾ�߾�����ϵ���
	for( i=0; i<4; i++ )
	{
		if( i != 3 ) len = ee_displayitem_lenth;
		else len = ee_displayitem_lenth1;
		I2C_Write_Eeprom( ee_loop_displayitem_page+2*i, 0x00, Buf, len ); //ѭ����ʾ���
		I2C_Write_Eeprom( ee_loop_displayitem_page+2*i+1, 0x00, Buf, len ); //������ʾ���
	}
	
	I2C_Write_Eeprom( ee_loop_displayitem_page, 0x00, (unsigned char*)Def_Autodisp_table, ee_displayitem_lenth );//��ʼ��ѭ����ʾ���
	I2C_Write_Eeprom( ee_key_displayitem_page, 0x00, (unsigned char*)Def_Keydisp_table, ee_displayitem_lenth );//��ʼ��������ʾ���
	I2C_Write_Eeprom( ee_key_displayitem_page+2, 0x00, (unsigned char*)Def_Keydisp_table+ee_displayitem_lenth, ee_displayitem_lenth );//��ʼ��������ʾ���
	
	for( i=0; i<2; i++ ) Item[i].Crc16.B08[0] += 1;
	dispitem_veri_flag = 1;
	
	//��ǰ/�����׽���ʱ����
	I2C_Write_Eeprom( ee_jtshiqu1_page, ee_jtshiqu_inpage, (uint08*)Def_jtshiqu_table, ee_jtshiqu_len );
	I2C_Write_Eeprom( ee_jtshiqu2_page, ee_jtshiqu_inpage, (uint08*)Def_jtshiqu_table2, ee_jtshiqu_len );

	//��ǰ/�����׽��ݱ�
	Clear_Wdt();
	memset(Buf, 0x00, 72);
	if( Crc_Check( Price.Ladder_Dl[0].B08, ee_ladder_lenth+2 ) ) 
	{
		for(i=0; i<8; i++) I2C_Write_Eeprom( ee_ladder1_page+i, 0, Buf, ee_ladder_lenth+2 );
	}
	
	//��ʼ���¶�ϵ��
	Temperpara_Verify();	//У�����ݺϷ���
	WriteE2WithBackup( ee_temperature_page, ee_temperature_inpage, Tpara.Offset, ee_temperature_lenth); 
	
//	(*( void (*)( ) )0xFF0000) ();	//��λ
										
}
