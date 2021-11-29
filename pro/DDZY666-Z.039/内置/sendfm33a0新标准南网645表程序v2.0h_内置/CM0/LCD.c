
#include "ex_func.h"
#include "ex_var.h"
#include "FM32L0XX.h"  
#include <string.h>

#define		disp_dangqian   DispBuf[7] |= BIT25	//��ǰ
#define		disp_shang			DispBuf[5] |= BIT0	//��
#define		disp_1					DispBuf[7] |= BIT26	//��N��L1��1x
#define		disp_yue				DispBuf[7] |= BIT24	//��
#define		disp_zuhe				DispBuf[7] |= BIT23	//���
#define		disp_zheng			DispBuf[5] |= BIT2	//����
#define		disp_fan				DispBuf[5] |= BIT4	//����
#define		disp_xiang      DispBuf[5] |= BIT5	//��
#define		disp_wu					DispBuf[5] |= BIT10	//��
#define		disp_you				DispBuf[7] |= BIT22	//��
#define		disp_gong				DispBuf[7] |= BIT21	//��
#define		disp_wu1				DispBuf[4] |= BIT11	//�޹�1����
#define		disp_wu2				DispBuf[7] |= BIT10	//�޹�2����
#define		disp_wu4				disp_wu1; DispBuf[4] |= BIT12 	//�޹�4����
#define		disp_zong       DispBuf[5] |= BIT12	//��
#define		disp_yong       DispBuf[5] |= BIT11	//��
#define		disp_dliang  		DispBuf[7] |= BIT20	//����

#define		disp_jian				DispBuf[5] |= BIT21 //��
#define		disp_feng				DispBuf[5] |= BIT20	//��
#define		disp_ping				DispBuf[4] |= BIT21	//ƽ
#define		disp_gu 				DispBuf[4] |= BIT20	//��
#define		disp_cos				DispBuf[6] |= BIT28	//����
#define		disp_jieti	    DispBuf[7] |= BIT14	//����
#define		disp_feilv			DispBuf[7] |= BIT13	//���� --
#define		disp_12         DispBuf[7] |= BIT3	//����P1��1x
#define		disp_dot1				DispBuf[3] |= BIT26	//1λС��P6
#define		disp_dot2       DispBuf[0] |= BIT31	//2λС��P5
#define		disp_dot3       DispBuf[6] |= BIT11	//3λС��P4
#define		disp_dot4       DispBuf[0] |= BIT11	//4λС��P3
#define		disp_dot22      DispBuf[7] |= BIT0 	//ʱ���P7
#define		disp_dot44      DispBuf[3] |= BIT31	//ʱ���P8

#define		disp_shi        DispBuf[4] |= BIT5	//ʱ
#define		disp_tjian      DispBuf[4] |= BIT10	//��
#define		disp_duan       DispBuf[7] |= BIT12	//��
#define		disp_biao       DispBuf[7] |= BIT11	//��
#define		disp_hu         DispBuf[7] |= BIT9	//��
#define		disp_hao        DispBuf[7] |= BIT8	//��
#define		disp_const			DispBuf[4] |= BIT31	//����

#define		disp_L   				DispBuf[3] |= BIT21	//L
#define		disp_neg        DispBuf[2] |= BIT21	//����L6
#define		disp_N					DispBuf[1] |= BIT21	//N
#define		disp_kw         DispBuf[5] |= BIT31	//KW
#define		disp_h          DispBuf[7] |= BIT18	//h1
#define		disp_v					DispBuf[4] |= BIT26	//v
#define		disp_a					DispBuf[5] |= BIT26	//A
#define		disp_kvar				DispBuf[2] |= BIT15	//kvar
#define		disp_h2					DispBuf[7] |= BIT19	//h2

#define		disp_fanxiang   DispBuf[0] |= BIT21	//����(ָʾ)T1
#define		disp_ble		    DispBuf[0] |= BIT20	//����ͨѶT2
#define		disp_baterry    DispBuf[6] |= BIT7	//���T3
#define		disp_prog       DispBuf[0] |= BIT0	//���T4
#define		disp_lock       DispBuf[0] |= BIT2	//��T5
#define		disp_zbcomm			DispBuf[0] |= BIT4	//�ز�ͨ��T6
#define		disp_comm				DispBuf[0] |= BIT5	//ͨ��T7
#define		disp_key				DispBuf[6] |= BIT4	//��Կ����(����)T8
#define		disp_pbuy       DispBuf[6] |= BIT14	//�빺��
#define		disp_relayoff   DispBuf[6] |= BIT3	//��բ
#define		disp_ladder1    DispBuf[6] |= BIT2	//��1�׽���T9
#define		disp_ladder2    DispBuf[6] |= BIT1	//��2�׽���T10
#define		disp_ladder     DispBuf[6] |= BIT0	//����T11 LX
#define		disp_shiduan1   DispBuf[2] |= BIT26	//ʱ�α�1
#define		disp_shiduan2   DispBuf[3] |= BIT17	//ʱ�α�2 T13
#define		disp_T   				DispBuf[3] |= BIT15	//T T14
#define		disp_13					DispBuf[2] |= BIT17	//����1x P2

unsigned char  LCD_Table( unsigned char  Show )
{
	const unsigned char code_value[] = 
//	{ 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 
//	  0x6f, 0x50, 0x40, 0x38, 0x00, 0x79, 0x71, 0x76, 0x38 };
	{0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f,0x6f,//0~9
	 0x50, 0x40, 0x38, 0x76, 0x79, 0x71};//r,-,L,H,E,F
//	0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};//A,B,C,D,E,F
	if( Show < 0x12 )
	{
		return ( code_value[Show] );
	}
	else
	{
		return (0x3f);
	}
}

void LCD_Num_Data( unsigned char Num,   unsigned char Show)
{
	unsigned char Result;

	Result = LCD_Table( Show & 0x0f );

	switch( Num )
	{
		case 0x0B:
		//------------ ��1��"8"�ַ� ----------
		if( (Result&0x01) == 0x01 ) {	DispBuf[7] |= BIT27;}	//1A
		if( (Result&0x02) == 0x02 ) {	DispBuf[4] |= BIT0 ;}	//1B
		if( (Result&0x04) == 0x04 ) {	DispBuf[3] |= BIT0 ;}	//1C
		if( (Result&0x08) == 0x08 ) {	DispBuf[7] |= BIT7 ;}	//1D
		if( (Result&0x10) == 0x10 ) {	DispBuf[7] |= BIT6 ;}	//1E
		if( (Result&0x20) == 0x20 ) {	DispBuf[7] |= BIT16;}	//1F
		if( (Result&0x40) == 0x40 ) {	DispBuf[7] |= BIT17;}	//1G
		break;

		//------------ ��2��"8"�ַ� ----------
		case 0x0C:
		if( (Result&0x01) == 0x01 ) {	DispBuf[5] |= BIT3 ;}	//2A
		if( (Result&0x02) == 0x02 ) {	DispBuf[4] |= BIT4 ;}	//2B
		if( (Result&0x04) == 0x04 ) {	DispBuf[3] |= BIT4 ;}	//2C
		if( (Result&0x08) == 0x08 ) {	DispBuf[3] |= BIT3 ;}	//2D
		if( (Result&0x10) == 0x10 ) {	DispBuf[3] |= BIT2 ;}	//2E
		if( (Result&0x20) == 0x20 ) {	DispBuf[4] |= BIT2 ;}	//2F
		if( (Result&0x40) == 0x40 ) {	DispBuf[4] |= BIT3 ;}	//2G	  
		break;
	
		//------------ ��3��"8"�ַ� ----------
		case 0x01:
		if( (Result&0x01) == 0x01 ) {	DispBuf[7] |= BIT15;}	//3A
		if( (Result&0x02) == 0x02 ) {	DispBuf[7] |= BIT5 ;}	//3B
		if( (Result&0x04) == 0x04 ) {	DispBuf[6] |= BIT27;}	//3C
		if( (Result&0x08) == 0x08 ) {	DispBuf[6] |= BIT17;}	//3D
		if( (Result&0x10) == 0x10 ) {	DispBuf[1] |= BIT20;}	//3E
		if( (Result&0x20) == 0x20 ) {	DispBuf[3] |= BIT20;}	//3F
		if( (Result&0x40) == 0x40 ) {	DispBuf[2] |= BIT20;}	//3G	
		break;	
		
		//------------ ��4��"8"�ַ� ----------
		case 0x02:
		if( (Result&0x01) == 0x01 ) {	DispBuf[6] |= BIT29;}	//4A
		if( (Result&0x02) == 0x02 ) {	DispBuf[2] |= BIT0 ;}	//4B
		if( (Result&0x04) == 0x04 ) {	DispBuf[1] |= BIT0 ;}	//4C
		if( (Result&0x08) == 0x08 ) {	DispBuf[6] |= BIT9 ;}	//4D
		if( (Result&0x10) == 0x10 ) {	DispBuf[6] |= BIT8 ;}	//4E
		if( (Result&0x20) == 0x20 ) {	DispBuf[6] |= BIT18;}	//4F
		if( (Result&0x40) == 0x40 ) {	DispBuf[6] |= BIT19;}	//4G	
		break;

		//------------ ��5��"8"�ַ� ----------
		case 0x03:
		if( (Result&0x01) == 0x01 ) {	DispBuf[7] |= BIT4 ;}	//5A	  
		if( (Result&0x02) == 0x02 ) {	DispBuf[6] |= BIT25;}	//5B	  
		if( (Result&0x04) == 0x04 ) {	DispBuf[6] |= BIT15;}	//5C		  
		if( (Result&0x08) == 0x08 ) {	DispBuf[6] |= BIT5 ;}	//5D		  
		if( (Result&0x10) == 0x10 ) {	DispBuf[6] |= BIT6 ;}	//5E	  
		if( (Result&0x20) == 0x20 ) {	DispBuf[6] |= BIT26;}	//5F		  
		if( (Result&0x40) == 0x40 ) {	DispBuf[6] |= BIT16;}	//5G
		break;	
	
		//------------ ��6��"8"�ַ� ----------
		case 0x04:
		if( (Result&0x01) == 0x01 ) {	DispBuf[2] |= BIT3 ;}	//6A	  
		if( (Result&0x02) == 0x02 ) {	DispBuf[2] |= BIT4 ;}	//6B	  
		if( (Result&0x04) == 0x04 ) {	DispBuf[1] |= BIT4 ;}	//6C		  
		if( (Result&0x08) == 0x08 ) {	DispBuf[0] |= BIT3 ;}	//6D		  
		if( (Result&0x10) == 0x10 ) {	DispBuf[1] |= BIT2 ;}	//6E	  
		if( (Result&0x20) == 0x20 ) {	DispBuf[2] |= BIT2 ;}	//6F		  
		if( (Result&0x40) == 0x40 ) {	DispBuf[1] |= BIT3 ;}	//6G
		break;
		
		//------------ ��7��"8"�ַ� ----------
		case 0x05:
		if( (Result&0x01) == 0x01 ) {	DispBuf[3] |=  BIT10;}	//7A
		if( (Result&0x02) == 0x02 ) {	DispBuf[2] |=  BIT10;}	//7B
		if( (Result&0x04) == 0x04 ) {	DispBuf[1] |=  BIT10;}	//7C
		if( (Result&0x08) == 0x08 ) {	DispBuf[0] |=  BIT10;}	//7D
		if( (Result&0x10) == 0x10 ) {	DispBuf[1] |=  BIT5 ;}	//7E
		if( (Result&0x20) == 0x20 ) {	DispBuf[3] |=  BIT5 ;}	//7F
		if( (Result&0x40) == 0x40 ) {	DispBuf[2] |=  BIT5 ;}	//7G
		break;
	
		//------------ ��8��"8"�ַ� ----------
		case 0x06:
		if( (Result&0x01) == 0x01 ) {	DispBuf[7] |=  BIT1 ;}	//8A
		if( (Result&0x02) == 0x02 ) {	DispBuf[6] |=  BIT22;}	//8B
		if( (Result&0x04) == 0x04 ) {	DispBuf[6] |=  BIT12;}	//8C
		if( (Result&0x08) == 0x08 ) {	DispBuf[6] |=  BIT13;}	//8D
		if( (Result&0x10) == 0x10 ) {	DispBuf[6] |=  BIT24;}	//8E
		if( (Result&0x20) == 0x20 ) {	DispBuf[7] |=  BIT2 ;}	//8F
		if( (Result&0x40) == 0x40 ) {	DispBuf[6] |=  BIT23;}	//8G
		break;
		
		//------------ ��9��"8"�ַ� ----------
		case 0x07:
		if( (Result&0x01) == 0x01 ) {	DispBuf[3] |=  BIT12;}	//9A
		if( (Result&0x02) == 0x02 ) {	DispBuf[2] |=  BIT12;}	//9B
		if( (Result&0x04) == 0x04 ) {	DispBuf[1] |=  BIT12;}	//9C
		if( (Result&0x08) == 0x08 ) {	DispBuf[0] |=  BIT12;}	//9D
		if( (Result&0x10) == 0x10 ) {	DispBuf[1] |=  BIT11;}	//9E
		if( (Result&0x20) == 0x20 ) {	DispBuf[3] |=  BIT11;}	//9F
		if( (Result&0x40) == 0x40 ) {	DispBuf[2] |=  BIT11;}	//9G	
		break;
		
		//------------ ��10��"8"�ַ� ----------
		case 0x08:
		if( (Result&0x01) == 0x01 ) {	DispBuf[6] |=  BIT30;}	//10A
		if( (Result&0x02) == 0x02 ) {	DispBuf[2] |=  BIT31;}	//10B
		if( (Result&0x04) == 0x04 ) {	DispBuf[1] |=  BIT31;}	//10C
		if( (Result&0x08) == 0x08 ) {	DispBuf[6] |=  BIT10;}	//10D
		if( (Result&0x10) == 0x10 ) {	DispBuf[6] |=  BIT21;}	//10E
		if( (Result&0x20) == 0x20 ) {	DispBuf[6] |=  BIT31;}	//10F
		if( (Result&0x40) == 0x40 ) {	DispBuf[6] |=  BIT20;}	//10G	
		break;
		
		//------------ ��11��"8"�ַ� ----------
		case 0x09:
		if( (Result&0x01) == 0x01 ) {	DispBuf[5] |=  BIT27;}	//11A
		if( (Result&0x02) == 0x02 ) {	DispBuf[4] |=  BIT27;}	//11B
		if( (Result&0x04) == 0x04 ) {	DispBuf[3] |=  BIT27;}	//11C
		if( (Result&0x08) == 0x08 ) {	DispBuf[2] |=  BIT30;}	//11D
		if( (Result&0x10) == 0x10 ) {	DispBuf[3] |=  BIT30;}	//11E
		if( (Result&0x20) == 0x20 ) {	DispBuf[5] |=  BIT30;}	//11F
		if( (Result&0x40) == 0x40 ) {	DispBuf[4] |=  BIT30;}	//11G	
		break;
		
		//------------ ��12��"8"�ַ� ----------
		case 0x0A:
		if( (Result&0x01) == 0x01 ) {	DispBuf[5] |=  BIT16;}	//12A
		if( (Result&0x02) == 0x02 ) {	DispBuf[5] |=  BIT15;}	//12B
		if( (Result&0x04) == 0x04 ) {	DispBuf[4] |=  BIT15;}	//12C
		if( (Result&0x08) == 0x08 ) {	DispBuf[3] |=  BIT16;}	//12D
		if( (Result&0x10) == 0x10 ) {	DispBuf[4] |=  BIT17;}	//12E
		if( (Result&0x20) == 0x20 ) {	DispBuf[5] |=  BIT17;}	//12F
		if( (Result&0x40) == 0x40 ) {	DispBuf[4] |=  BIT16;}	//12G	
		break;
		
		//------------ ��13��"8"�ַ� ----------
		case 0xD:
		if( (Result&0x01) == 0x01 ) {	DispBuf[2] |=  BIT27;}	//13A
		if( (Result&0x02) == 0x02 ) {	DispBuf[1] |=  BIT26;}	//13B
		if( (Result&0x04) == 0x04 ) {	DispBuf[0] |=  BIT26;}	//13C
		if( (Result&0x08) == 0x08 ) {	DispBuf[0] |=  BIT27;}	//13D
		if( (Result&0x10) == 0x10 ) {	DispBuf[0] |=  BIT30;}	//13E
		if( (Result&0x20) == 0x20 ) {	DispBuf[1] |=  BIT30;}	//13F
		if( (Result&0x40) == 0x40 ) {	DispBuf[1] |=  BIT27;}	//13G	
		break;
		
		//------------ ��14��"8"�ַ� ----------
		case 0x0E:
		if( (Result&0x01) == 0x01 ) {	DispBuf[2] |=  BIT16;}	//14A
		if( (Result&0x02) == 0x02 ) {	DispBuf[1] |=  BIT15;}	//14B
		if( (Result&0x04) == 0x04 ) {	DispBuf[0] |=  BIT15;}	//14C
		if( (Result&0x08) == 0x08 ) {	DispBuf[0] |=  BIT16;}	//14D
		if( (Result&0x10) == 0x10 ) {	DispBuf[0] |=  BIT17;}	//14E
		if( (Result&0x20) == 0x20 ) {	DispBuf[1] |=  BIT17;}	//14F
		if( (Result&0x40) == 0x40 ) {	DispBuf[1] |=  BIT16;}	//14G	
		break;
		
	default:
		break;
	}
}

void Lcd_Disp_Zedl(uint08 month, uint08 feilv )
{
	if(feilv == 0)
	{
		disp_zong;			//��
	}
	else
	{
		disp_feilv;			//����
		if(feilv > 9)
		{
			disp_12;
			feilv -= 10;
		}
		LCD_Num_Data( 12, feilv);
	}	
	
	if(month == 0)
	{
		disp_dangqian;			//��ǰ
	}
	else
	{
		disp_shang;			//��
		disp_yue;			//��
		
		if(month > 9)
		{
			disp_1;
			month -= 10;
		}
		LCD_Num_Data( 11, month);
	}
}


void Lcd_Show_ZF( void )
{
	if(dl_back_flag) disp_fan;
	else disp_zheng;
	disp_xiang;
}

unsigned char Lcd_Show_N( unsigned char start, unsigned char len, unsigned char *Show)
{
	unsigned char i, k, dotnum=0, Lcddot = 0;

	i = 0;
	if(start & 0xf0 )	//��С������ʾ�Ĵ���
	{
		dotnum = (start & 0xf0)>>4;	//start�߰��ֽ�ΪС��λ����F��ʾ��ʾ����
		if(dotnum == 0x0f) dotnum = Display_Para.Dl_Dot;
		if(dotnum == 0x0e) dotnum = Display_Para.P_Dot;
		start &= 0x0f;
	
		switch(dotnum)
		{
			case 0x01:	disp_dot1;	break;
			case 0x02:	disp_dot2;	break;
			case 0x03:	disp_dot3;	break;
			case 0x04:	disp_dot4;	break;
			default:			break;
		}
		disp_0_flag = 1;
	}
	if( disp_0_flag )//���㴦��
	{		
		for(i=0; i<(10-start-dotnum); i++)	
		{
			if((i%2) == 0)	//�жϸ߰��ֽ�
			{
				if(((Show[i/2]>>4)&0x0F) != 0) break;
			}
			else						//�жϵͰ��ֽ�
			{
				if(((Show[i/2]>>0)&0x0F) != 0) break;
			}
			
			Lcddot++;
		}
	}
	
	for( k=i; k<len*2; k++ )//��ʾ����
	{
		if(k%2)	//��ʾ�Ͱ��ֽ�
		{
			LCD_Num_Data( start+k, (Show[k/2]>>0)&0x0F);
		}
		else		//��ʾ�߰��ֽ�
		{
			LCD_Num_Data( start+k, (Show[k/2]>>4)&0x0F);
		}
	}
	
	return( Lcddot );
}

//����С��λ���Ĵ���(0~4λС������)
void Disp_Dl_G_Dot(unsigned char *Ee_Buf, unsigned char i)
{
	uint08 Temp08;
	union B64_B08_2 Temp64;
	
	if( i < 3 ) //���,����,����
	{
		disp_you;									//�й�
		disp_gong;
		disp_dliang;            	//����
		disp_kw;                	//KW
		disp_h;                 	//h
	}
	else	//����޹�1/2,��һ�����޹�����~���������޹�����
	{
		disp_wu;									//�޹�
		disp_gong;
		disp_dliang;            	//����
		disp_kvar;                //kvar
		disp_h2;                 	//h
		
		if( i < 5 )		//����޹�1/2
		{
			disp_zuhe;
			i+=2;
		}
		
		switch(i-4)	//�޹�����
		{
			case 1:	disp_wu1; break;
			case 2:	disp_wu2; break;
			case 3:	disp_wu1; disp_wu2; break;
			case 4:	disp_wu4; break;
			default:break;
		}
	}
	
	Temp08 = Display_Para.Dl_Dot;  //����
		
	//�߾��ȵ�������Ӧ��ʾXXXX XXXX XXXX.XXXX
	//���������ݳ�����ʾ��Χʱ���ҽ��н�λ��ʾ,����赽ֻʣ��λС��
//	if( Ee_Buf[5]&0x0f ) Display_Para.Dl_Dot_Auto = 1;
//	else if( (Ee_Buf[4]&0xf0) && ((Display_Para.Dl_Dot_Auto>2)||(Display_Para.Dl_Dot_Auto==0)) ) Display_Para.Dl_Dot_Auto = 2;
//	else if( (Ee_Buf[4]&0x0f) && ((Display_Para.Dl_Dot_Auto>3)||(Display_Para.Dl_Dot_Auto==0)) ) Display_Para.Dl_Dot_Auto = 3;
	
	if( Ee_Buf[5]&0x0f ) Display_Para.Dl_Dot_Auto = 3;//����8��8,����10��8
		
	//���������ݳ�����ʾ��Χʱ,���������λ,�����еĵ�������ͬʱ��λ��ʾ,������ʷ������ܡ��¼���¼�е���
	if( Display_Para.Dl_Dot_Auto && (Display_Para.Dl_Dot_Auto<Display_Para.Dl_Dot) ) Display_Para.Dl_Dot = Display_Para.Dl_Dot_Auto;
	
	memcpy( Temp64.B08, Ee_Buf, 8 );
	Temp64.B64 >>= 4*(4-Display_Para.Dl_Dot);
	Inverse( Temp64.B08, 8 );	//��ɸ��ֽ���ǰ
	
	Lcd_Show_N( 0xf1, 5, Temp64.B08+3 );
	Display_Para.Dl_Dot = Temp08;	//�ָ�
}

//����С��λ���Ĵ���(0~4λС������)
void Disp_Pw_Dot(unsigned char *Ee_Buf)
{
	Int2Byte( (Byte2uInt(Ee_Buf)>>((4-Display_Para.P_Dot)*4)), Ee_Buf );

//	Lcd_Show_ZF();
	Lcd_Show_N( 0xe3, 4, Ee_Buf);
}

void Disp_Time_Dot( unsigned char Type )
{
	if(Type == 0)
	{
		disp_dot2;
		disp_dot4;
	}
	else
	{
		disp_dot2;
		disp_dot4;
		disp_dot22;
		disp_dot44;
	}
}


void Lcd_Display( void )
{
	uint08 i,j, Temp08,flash;
	uint08 Ee_Buf[64];
	uint16 Disp_cnt;
	
	memset(DispBuf, 0x00, 40);	//����ʾ������
	memset(Ee_Buf, 0x00, 64);	//����ʾ������(������ʾ��Ҫ)
	
	Disp_cnt = 0;
	display_rtc_flag=0;
	disp_0_flag = 0;
	
	if(Display.Timer == 0) 
	{		
		Display.Timer = Display_Para.Loop_Time;//����ѭ����ʾʱ��
		
		if( Display.Status & B0000_0001 )	//���Խ���
		{
			Display.Status &= B1111_1110;	//�尴����ʾ��־
			Display.Number = 0;
		}
		
		Display.Number++;
		if(Display.Number > Display_Para.S_Number) Display.Number = 0;
		
		freeze_display_flag = 0;	//������յ�����ʾ��־
	}
	
	if(Display.Number == 0) Display.Number = 1;
	if( Display.Number == 0xfc )
	{
		Disp_cnt = Ext_Disp_Cnt;
	}
	else if( Display.Number == 0xff )
	{
		Disp_cnt = 200; 		//ȫ��
	}
	else
	{
		j = (Display.Number-1)%sizeof(Item[0].Display);
		if(!(Display.Status&B0000_0001)) 
		{					
			Disp_cnt = Item[0].Display[j];//ѭ��
		}
		else
		{							
			Disp_cnt = Item[1].Display[j];//����
		}
	}

	if( (EA_OFF) && (Stop_Disptimer==0) && (Display.Number != 0xff)) Disp_cnt = 0x201;	//ͣ�糤�Ե�ǰ��ϵ���
		
	switch( Disp_cnt )
	{
//--------------ѭ����ʾ����Ԥ��
			case 0:
				Display.Number++;
				return;
				
//--------------ȫ��
			case 200:
				memset( DispBuf, 0xff, 40 );
				break;		
				
//--------------�����ۼ��õ���
//--------------��1���ۼ��õ���
			case 201:
			case 202:
				i = Disp_cnt-201;
				if(i== 0)	disp_dangqian;
				else	disp_shang;
//				disp_zong;
				disp_yong;
				disp_yue;
				Cal_Comb_Usedl( 0x01, i, Ee_Buf );	//Ԥ��4+�߾��ȵ���8�ֽ�
					
				if( Ee_Buf[4+7]&B1000_0000)
				{
					Ee_Buf[4+7] &= B0111_1111;
					disp_neg;
				}
						
				Disp_Dl_G_Dot(Ee_Buf+4, 0); //xxxxxxxxxxxx.xxxx
				LCD_Num_Data( 11, 1);
				break;

//--------------485ͨ�Ų�����				
			case 203:
				Temp08 = Mode.Bps[0]&B0111_1110;
				Ee_Buf[0] = 0;
				Ee_Buf[2] = 0;
				if( Temp08 == B0000_0100 ) Ee_Buf[1] = 0x12;
				else if( Temp08 == B0001_0000 ) Ee_Buf[1] = 0x48;
				else if( Temp08 == B0010_0000 ) Ee_Buf[1] = 0x96;
				else if( Temp08 == B0100_0000 ) {Ee_Buf[0] = 0x01;Ee_Buf[1] = 0x92;}
				else Ee_Buf[1] = 0x24;
				disp_0_flag = 1;
				Lcd_Show_N( 5, 3, Ee_Buf);
				break;
				
//--------------��ѹ
			case 204:
				disp_v;
				Exchange( Ee_Buf, Emu_Data.U.B08, 4 );//��ɸ��ֽ���ǰ
				Lcd_Show_N( 0x13, 4, Ee_Buf);				
				break;

//--------------����
			case 205:
				disp_L;
				disp_a;
				Lcd_Show_ZF();
				Exchange( Ee_Buf, Emu_Data.I1.B08, 4 );//��ɸ��ֽ���ǰ
				Lcd_Show_N( 0x33, 4, Ee_Buf);		
				break;

//--------------����
			case 206:
			case 207:
				disp_kw;	
				Lcd_Show_ZF();
				Exchange( Ee_Buf, Emu_Data.P1.B08, 4 );//��ɸ��ֽ���ǰ
				Disp_Pw_Dot(Ee_Buf);
				break;	
				
//--------------Ƶ��
			case 230:
				Exchange( Ee_Buf, Emu_Data.Freq.B08, 4 );//��ɸ��ֽ���ǰ
				Lcd_Show_N( 0x23, 4, Ee_Buf);	
				break;					
				
//--------------�޹�����
			case 231:
			case 232:
				disp_kvar;
				if(dl_back_flag2) disp_fan;
				else disp_zheng;
				disp_xiang;
				Exchange( Ee_Buf, Emu_Data.Q1.B08, 4 );//��ɸ��ֽ���ǰ
				Disp_Pw_Dot(Ee_Buf);
				break;				

//--------------��������
			case 208:
			case 209:
				disp_cos;
				Lcd_Show_ZF();
				Exchange( Ee_Buf, Emu_Data.Cosa.B08, 4 );//��ɸ��ֽ���ǰ
				Lcd_Show_N( 0x33, 4, Ee_Buf);					
				break;

//--------------���ߵ���
			case 210:
				disp_N;
				disp_a;
				if(dln_back_flag) disp_fan;
				else disp_zheng;
				disp_xiang;
				Exchange( Ee_Buf, Emu_Data.I2.B08, 4 );//��ɸ��ֽ���ǰ
				Lcd_Show_N( 0x33, 4, Ee_Buf);				
				break;

//--------------����
			case 211:
				disp_const;
				memcpy( Ee_Buf, Meter.Const.B08+1, 3 );
				disp_0_flag = 1;
				Lcd_Show_N( 5, 3, Ee_Buf);	
				break;
				
//--------------��һ������
			case 212:
			case 213:
			case 214:
				disp_dot2;
				I2C_Read_Eeprom(ee_histroyparameter_page, ee_histroyparameter_inpage+(Disp_cnt-212)*2, &Ee_Buf[1], 2);

				Ee_Buf[0] = Ee_Buf[2];
				Lcd_Show_N( 7, 2, Ee_Buf);
				break;					
				
//--------------���Ÿ�4λ
			case 216:
				disp_hu;
				disp_hao;
				Lcd_Show_N( 7, 2, Esam_Para.User_Id);				
				break;
				
//--------------���ŵ�8λ
			case 215:
				disp_hu;
				disp_hao;
				Lcd_Show_N( 3, 4, Esam_Para.User_Id+2);	
				break;
				
//--------------��Ÿ�4λ
			case 218:
				disp_biao;
				disp_hao;
				Lcd_Show_N( 7, 2, Esam_Para.Meter_Id);				
				break;
				
//--------------��ŵ�8λ
			case 217:
				disp_biao;
				disp_hao;
				Lcd_Show_N( 3, 4, Esam_Para.Meter_Id+2);	
				break;
				
//--------------ͨѶ��ַ��4λ
			case 220:
//				disp_biao;
//				disp_hao;
				Lcd_Show_N( 7, 2, Comm_Addr.Comm_Id);				
				break;
				
//--------------ͨѶ��ַ��8λ
			case 219:
//				disp_biao;
//				disp_hao;
				Lcd_Show_N( 3, 4, Comm_Addr.Comm_Id+2);	
				break;					

//--------------ʱ��
//--------------����
			case 222:
				display_rtc_flag = 1;
			case 221:			
				i = Disp_cnt - 221;
				Disp_Time_Dot(i);
				disp_dangqian;
				disp_shi;
				disp_tjian;
				Read_Rtc(Ee_Buf);
				Inverse( Ee_Buf, 7 );
				Lcd_Show_N( 5, 3, Ee_Buf+i*4);	
				if( Disp_cnt == 221 ) {LCD_Num_Data( 3, 0x02);LCD_Num_Data( 4, 0x00);}
				break;

//--------------���һ�α������
//--------------���һ�α��ʱ��
			case 223:
			case 224:
				i = Disp_cnt-223;
				Disp_Time_Dot(i);
				disp_shi;
				disp_tjian;
				if( RdRecTimes(ee_programn_inpage) )
				{
					Temp08 = Read_Event_Point( ee_programn_inpage );
					I2C_Read_Eeprom( ee_program_note_page+Temp08, ee_programnote_inpage+3*(1-i), Ee_Buf, 3 );
				}
				else memset(Ee_Buf, 0x00, 3);
				Inverse(Ee_Buf,3);//�����ֽ�˳�� 				
				Lcd_Show_N( 5, 3, Ee_Buf );
				if( Disp_cnt == 223 )
				{
					if( ChkBufZero(Ee_Buf,3)==0 ) LCD_Num_Data( 3, 0x00);	
					else LCD_Num_Data( 3, 0x02);
					LCD_Num_Data( 4, 0x00);
				}
				break;				
								
//--------------���һ����������
//--------------���һ������ʱ��				
			case 225:			
			case 226:
				i = Disp_cnt-225;
				Disp_Time_Dot(i);
				disp_shi;
				disp_tjian;
				if( RdRecTimes(ee_clearn_inpage) )
				{
					Temp08 = Read_Event_Point( ee_clearn_inpage );
					I2C_Read_Eeprom( ee_cleardl_note_page+Temp08, ee_cleardlnote_inpage+3*(1-i), Ee_Buf, 3 );
				}
				else memset(Ee_Buf, 0x00, 3);
				Inverse(Ee_Buf,3);//�����ֽ�˳�� 				
				Lcd_Show_N( 5, 3, Ee_Buf );
				if( Disp_cnt == 225 )
				{
					if( ChkBufZero(Ee_Buf,3)==0 ) LCD_Num_Data( 3, 0x00);	
					else LCD_Num_Data( 3, 0x02);
					LCD_Num_Data( 4, 0x00);
				}
				break;
				
//--------------��ǰ������ۼ��õ���
//--------------��1 ������ۼ��õ���
			case 227:			
			case 228:
				i = Disp_cnt-227;
				if( i == 0)	disp_dangqian;
				else	disp_shang;
//				disp_zong;
				disp_yong;
				Cal_Comb_Usedl( 0x02, i, Ee_Buf );	//ʱ��4+�߾��ȵ���8�ֽ�
					
				if( Ee_Buf[4+7]&B1000_0000)
				{
					Ee_Buf[4+7] &= B0111_1111;
					disp_neg;
				}
						
				Disp_Dl_G_Dot(Ee_Buf+4, 0); //xxxxxxxxxxxx.xxxx	
				LCD_Num_Data( 11, 1);
				break;	

//--------------���,����,����,����޹�1/2,��һ�����޹�����~���������޹�����
			default:	//��ͨ������ʾ,�߾��ȵ�����ʾ(0x800)
				if( ((Disp_cnt <= 0x200+max_disploop*9) && (Disp_cnt > 0x200)) || ((Disp_cnt <= 0x800+max_disploop*9) && (Disp_cnt > 0x800)) )	
				{
					uint16 Disp_cnt2;
					
					if( Disp_cnt < 0x800 ) Disp_cnt2 = Disp_cnt - 0x200;
					else Disp_cnt2 = Disp_cnt - 0x800;
									
					Temp08 = (Disp_cnt2-1)/max_disploop;	//���,����,����,����޹�1/2,��һ�����޹�����~���������޹�����
					i = (Disp_cnt2-1-max_disploop*Temp08)/(max_feilvcount+1);	//0:��ǰ; 1~12����
					j = (Disp_cnt2-1)%(max_feilvcount+1);		//0,1~12����
					Lcd_Disp_Zedl(i, j);
						
					if( (i==0) || (freeze_display_flag==0) )	
					{
						Cal_Comb( Temp08, j, i, Ee_Buf );	//��ȡ�������
						
						if( i && (freeze_display_flag==0) )
						{
							freeze_display_flag = 1; 	//�ý����յ�������ʾ��־
							memcpy( FreezeBuf, Ee_Buf, 8 );//���ݽ����յ�����ʾ����
						}
					}
					else	//�жϽ����յ�������ʾ��־
					{					
						memcpy( Ee_Buf, FreezeBuf, 8 );
					}
					
					if( Temp08==0 || Temp08==3 || Temp08==4 )
						Hex2Bcd_Dl_G( Ee_Buf, 0 );	//������תBCD����(�߾���)(���)
					else
						Hex2Bcd_Dl_G( Ee_Buf, 1 );	//������תBCD����(�߾���)
						
					if( (Ee_Buf[7]&B1000_0000) && (Temp08==0 || Temp08==3 || Temp08==4) )
					{
						Ee_Buf[7] &= B0111_1111;
						disp_neg;
					}
					if( Temp08 == 1 )
					{
						disp_zheng;
						disp_xiang;
					}
					if ( Temp08 == 2 )
					{
						disp_fan;
						disp_xiang;
					}
							
					Disp_Dl_G_Dot(Ee_Buf, Temp08); //xxxxxxxxxxxx.xxxx	
				}
				else if( (Disp_cnt <= 241) && (Disp_cnt >= 233) ) //��ǰ��ϵ���(�߾���)~��ǰ��ϵ��������޹�����(�߾���)
				{
					Temp08 = Disp_cnt-233;	//���,����,����,����޹�1/2,��һ�����޹�����~���������޹�����
					i = 0;		//0:��ǰ; 1~12����
					j = 0;		//0,1~12����
					Lcd_Disp_Zedl(i, j);
						
					Cal_Comb( Temp08, j, i, Ee_Buf );	//��ȡ�������
					
					if( Temp08==0 || Temp08==3 || Temp08==4 )
						Hex2Bcd_Dl_G( Ee_Buf, 0 );	//������תBCD����(�߾���)(���)
					else
						Hex2Bcd_Dl_G( Ee_Buf, 1 );	//������תBCD����(�߾���)
						
					if( (Ee_Buf[7]&B1000_0000) && (Temp08==0 || Temp08==3 || Temp08==4) )
					{
						Ee_Buf[7] &= B0111_1111;
						disp_neg;
					}
					if( Temp08 == 1 )
					{
						disp_zheng;
						disp_xiang;
					}
					if ( Temp08 == 2 )
					{
						disp_fan;
						disp_xiang;
					}
							
					Disp_Dl_G_Dot(Ee_Buf, Temp08); //xxxxxxxxxxxx.xxxx	
				}
				else
				{
					Display.Number++;
					return;
				}	
								
				break;
	}
	
	if( EA_ON )
	{
		//��ǰ����
		switch(Tariff.Current)
		{
			case 0: disp_jian; break;
			case 1: disp_feng; break;
			case 2: disp_ping; break;
			case 3: disp_gu; break;
			default:
				disp_T;
				Temp08 = Tariff.Current+1;
				if(Temp08 > 9)
				{
					disp_13;
					Temp08 -= 10;
				}
				LCD_Num_Data( 14, Temp08);
				break;
		}		
		
		flash = 0;
		if(Sclock.Clockmain[0]%2) flash = 1;
		if( relay_commu_alarm_flag && flash ) disp_pbuy; //�빺��(��˸��ʾ)
		
		if(Tariff.Current_Ladder != 0xff)
		{
			//��ǰ����
			disp_ladder;
			LCD_Num_Data( 13, Tariff.Current_Ladder+1);
				
			disp_ladder1;	//��1�׽��ݱ�
			
			//��ǰ���ݱ��
			if(Tariff.Status & B0000_0001) disp_ladder2;	//��2�׽��ݱ�
		}

		//��ǰʱ�α��
		if(Tariff.Status & B0000_0100) disp_shiduan2;	//��2��ʱ�α�
		else disp_shiduan1;
		
		//״̬��ʾ
		if( dl_back_flag ) disp_fanxiang;		//����
		
		if( (low_voltage_flag || Bat_Delay_Timer) ) disp_baterry;		//���
		
		if( progenable ) 
		{
			 if( flash ) disp_prog; 		//���ڱ����Ч, ��˸��ʾ����̡�
		}
		else if( IR_EnTimer ) disp_prog;		//���

		if( relay_status_flag && (relay_commu_disable_close_flag ==0) && (relay_commu_open_flag) ) disp_relayoff;//��բ
//		if( relay_status_flag && (relay_commu_disable_close_flag ==0) && (relay_commu_open_flag) )  disp_pbuy; //�빺�磨2021��
		
		if( Opendelaytimer || relay_delay_flag ) 
		{
			if(Sclock.Clockmain[0]%2)
			{
				disp_relayoff;			//ͨѶ��բ��ʱ����˸��ʾ����բ��
			}
		}
		
		if( Successled.Timer ) 
		{
			if(display_zaibo_flag) disp_zbcomm;	//�ز�ͨѶ
			else if(display_ble_flag) disp_ble;	//����ͨѶ
			else disp_comm;	//ͨѶ
		}
		
		if( Disp_cnt == 200 ) DISP->LCDBIAS   = Fulllcdbias;	//����ȫ���Ҷ�
		else DISP->LCDBIAS   = Runlcdbias;		
	}
//	else
//	{
//		if( (Disp_cnt != 205) && (Disp_cnt != 210) )	//ͣ����ʾLN(�����ߵ��������ߵ���)
//		{
//			disp_L;
//			disp_N;
//		}
//	}
	
	if( Key_Status != 1 ) disp_key;				//��Կ״̬(����)
	
	if( (Password_Err[0]>=Defpassworderrcnt) || hangup_comm_flag )
	{
		disp_lock;					//����������
 	}

 	//ˢ����ʾ
	DISP->DISPDATA0 = DispBuf[0];
	DISP->DISPDATA1 = DispBuf[1];
	DISP->DISPDATA2 = DispBuf[2];
	DISP->DISPDATA3 = DispBuf[3];
	DISP->DISPDATA4 = DispBuf[4];
	DISP->DISPDATA5 = DispBuf[5];
	DISP->DISPDATA6 = DispBuf[6];
	DISP->DISPDATA7 = DispBuf[7];
	DISP->DISPDATA8 = DispBuf[8];
	DISP->DISPDATA9 = DispBuf[9];	

 	run_display_flag = 0;
}

void Lcd_LCDEN_On(void)
{
	DISP->DISPCTRL |= BIT6;
}

void Lcd_LCDEN_Off(void)
{
	DISP->DISPCTRL &= (~BIT6);
}
