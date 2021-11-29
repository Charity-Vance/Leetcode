#include "ex_var.h"
#include "ex_func.h"
#include "FM32L0XX.h"  
#include <string.h>

#define		CRC_PAGE			0x42		//CRCУ�����ҳ
#define 	Devi_Addr1 			0xa0		//device addr
#define 	PAGE_SIZE 			64		//page size
#define 	SSP_TBIT 			8		//36us


unsigned char I2c_Send_Bit( unsigned char x_byte ) 
{
	unsigned char i;

	I2C->I2CCON = (x_byte*256) | 0x00000001;

	for( i=0; i<2*SSP_TBIT; i++ )
	{
		if( (I2C->I2CIR&0x01) == 0x01 ) break;
	}

	if( i < 2*SSP_TBIT )
	{
		I2C->I2CIR |= 0x01; //clr int flag

		i = I2C->I2CSTA; //clr flag through reading SSPSTA.
		
		return 0; //ok
	}
	else
	{
		return 1; //failure.
	}
}


unsigned char I2c_Send_Byte( unsigned char x_byte ) 
{
	unsigned int i;

	I2C->I2CBUF = x_byte;

	for( i=0; i<18*SSP_TBIT; i++ )
	{
		if( (I2C->I2CIR&0x01) == 0x01 ) break; //�жϱ�־��λʱ����ѭ��
	}
	
	if( i < 18*SSP_TBIT )
	{
		I2C->I2CIR |= 0x01; //clr int flag

		if( (I2C->I2CSTA&0x02) == 0x02 ) //�ӻ���Ӧ��
		{
			return 2; //ʧ��
		}
		else
		{
			return 0; //�ɹ�
		}
	}
	else
	{
		return 1; //failure.
	}
}


unsigned char I2c_Receive_Byte( unsigned char *x_byte ) 
{
	unsigned int i;

	I2C->I2CCON = I2C_I2CCON_I2CEN_ENABLE | I2C_I2CCON_RCEN_ENABLE;	//i2c en, rcen

	for( i=0; i<18*SSP_TBIT; i++ )
	{
		if( (I2C->I2CIR&0x01) == 0x01 ) break; //�жϱ�־��λ, ����ѭ��
	}

	if( i < 18*SSP_TBIT )
	{
		*x_byte = I2C->I2CBUF;

		I2C->I2CIR |= 0x01; //clr int flag

		return 0;
	}
	else
	{
		return 1; //failure.
	}
}



unsigned char Sendaddr( unsigned int Page, unsigned char offset, unsigned char Opt ) 
{
	unsigned char result, Devi_Addr;
	unsigned short Addr;
	
	Devi_Addr = Devi_Addr1;

	if( Page < 0x100 )
	{
		Addr = Page*PAGE_SIZE+offset;
	}
	else
	{
		Addr = 0x100*PAGE_SIZE+(Page-0x100)*128+offset;
	}

	//-------------- reset i2c -------------
	I2C->I2CCON = 0x00006000;
	for(result=0x00; result<0x03; result++ );
	
	//-------------- start bit -------------
	result = I2c_Send_Bit( B0110_0001 );//������ʼλ
	if( result != 0 ) return 1; //failure.

	//-------------- device addr -------------
	result = I2c_Send_Byte( Devi_Addr ); //����������ַ
	if( result != 0 ) return 2; //failure.

	//--------------- data addr --------------
	result = I2c_Send_Byte( Addr>>8 ); //�������ݵ�ַ��8λ
	if( result != 0 ) return 3; //failure.

	result = I2c_Send_Byte( Addr>>0 ); //�������ݵ�ַ��8λ
	if( result != 0 ) return 3; //failure.

	if( Opt == 1 ) //������
	{
		result = I2c_Send_Bit( B0110_0010 ); //��������ʼλ
		if( result != 0 ) return 5; //failure.
		
		result = I2c_Send_Byte( Devi_Addr|1 ); //����������ַ,��ȡ
		if( result != 0 ) return 5; //failure.
	}
		
	return 0; //ok
}
  

unsigned char Wait_for_end( unsigned int Page )
{
	unsigned char result, Devi_Addr;

	Devi_Addr = Devi_Addr1;
	
	Do_DelayStart(); //��Ҫ5ms���ڲ�д����, ѭ��һ������ʱ��: 42��Delay()��
	{
		I2c_Send_Bit( B0110_0001 );	//������ʼλ

		result = I2c_Send_Byte( Devi_Addr ); //����������ַ

		I2c_Send_Bit( B0110_0100 ); //����ֹͣλ

		if( result == 0 ) return 0; //���õ�ַ�ɹ�, д���ڽ���
    
	}While_DelayMsEnd(5*clkmode);

	return 1; //���õ�ַʧ��
}


uint08  ReadE2WithBackup( unsigned int Page, uint08 inpage, uint08 *Buf, uint08 Len )
{
	if( I2C_Read_Eeprom( Page, inpage, Buf, Len ) )
	{
		if( I2C_Read_Eeprom( Page+1, inpage, Buf, Len ) ) return 1;
	}
	
	return 0;
}

uint08 WriteE2WithBackup( unsigned int Page, uint08 inpage, uint08 *Buf, uint08 Len )
{
	if( I2C_Write_Eeprom( Page, inpage, Buf, Len ) ) 
	{
		if( I2C_Write_Eeprom( Page, inpage, Buf, Len ) ) return 1;	//ʧ����дһ��
	}
	
	I2C_Write_Eeprom( Page+1, inpage, Buf, Len );
	 
	return 0;
}

uint08  I2C_Read_Eeprom44( unsigned int Page, uint08 *Buf, uint08 Len )
{
	if( I2C_Read_Eeprom( Page, 44, Buf, Len ) )
	{
		 if( I2C_Read_Eeprom( Page, 44, Buf, Len ) ) return 1;	//ʧ���ٶ�һ��
	}
	
	return 0;
}

uint08  I2C_Write_Eeprom44( unsigned int Page, uint08 *Buf, uint08 Len )
{	
	if( I2C_Write_Eeprom( Page, 44, Buf, Len ) )
	{
		if( I2C_Write_Eeprom( Page, 44, Buf, Len ) ) return 1;	//ʧ����дһ��
	}
	
	return 0;
}

unsigned char I2C_Write_Bottom(unsigned int Page, unsigned char offset, unsigned char *Buf, unsigned char h)
{
	unsigned char k, n, status;
	
	for( k=0; k<3; k++ )//ÿ�����д3�� 
	{                                   	
		status = 0;
		if( Sendaddr( Page, offset, 0 ) ) status = 1; //д��ʧ��
		else 
		{
			for( n=0; n<h; n++ )
			{
				//����һ���ֽ�
				if( I2c_Send_Byte( Buf[n] ) ) {status = 1; break;} //д��ʧ��
			}
		}
		//����ֹͣλ
		if( I2c_Send_Bit( B0110_0100 ) ) status = 1;
		
		if( status == 0 ) {Wait_for_end(Page); break;}//д��ȷ
	}
	
	return( status );
}

unsigned char I2C_Read_Bottom(unsigned int Page, unsigned char offset, unsigned char *Buf, unsigned char h)
{
	unsigned char k, n, status;
	
	for( k=0; k<3; k++ )//ÿ������3��
	{
		status = 0;
		if( Sendaddr( Page, offset, 1 ) ) status = 1; //д��ʧ��
		else 
		{
			for( n=0; n<h; n++ )
			{
				//����һ���ֽ�
				if( I2c_Receive_Byte( Buf+n ) ) {status = 1; break;} 
        		
				if( n < (h-1) )	I2C->I2CSTA = B0000_0000;
				else		I2C->I2CSTA = B0000_0001;
				
				{
					//���� ACK
					if( I2c_Send_Bit( B0111_0000) )  {I2C->I2CSTA = B0000_0000;status = 1; break;}	//ʧ��
					I2C->I2CSTA = B0000_0000;
				}
			}
		}
		//����ֹͣλ
		if( I2c_Send_Bit( B0110_0100 ) ) status = 1;	//ʧ��
		
		if( status == 0 ) break;//����ȷ
	}
	
	return( status );
}

unsigned char I2C_Write_Eeprom( unsigned int Page, unsigned char offset, unsigned char *IIC_Buf, unsigned char Len )
{
	unsigned char h, i;
	unsigned char BufA[128],BufB[128];
	
	if( Page >= 0x280 ) return 1; //��ַ��� 
	if( Len == 0 ) return 1; //�ռ����


	h = Len;
	memcpy( BufA, IIC_Buf, Len );
	if( Page < CRC_PAGE ) 
	{
		Crc_16Bits_Add2( BufA, Len );			//����crc
		h = h + 2;					//���ȼ�2�ֽ�crc 
	}
	if( ((offset+h)>PAGE_SIZE) && (Page < 0x100) ) return 1; //�ռ����

	
	Enable_I2C_IO();	//��EE��Դ
	for( i=0; i<2; i++ )//���д2��
	{                              	
    	if( I2C_Write_Bottom( Page, offset, BufA, h ) )continue;//�����������д
		
		if( I2C_Read_Bottom( Page, offset, BufB, h ) )continue;//����������ζ�
		
		if( Cmp_Data( BufA, BufB, h )==3 ) return 0;	//��дһ�³ɹ�����
	}
	return 2; //fail
}


unsigned char I2C_Read_Eeprom( unsigned int Page, unsigned char offset, unsigned char *IIC_Buf, unsigned char Len ) 
{ 
	unsigned char h, i;
	unsigned char BufA[128];

	if( Len == 0 ) return 1; //�ռ����
	
	if( Page >= 0x280 ) return 1; //��ַ��� 
		
	h = Len;
	if( Page < CRC_PAGE ) h = h + 2;	//���ȼ�2�ֽ�crc 

	
	if( ((offset+h)>PAGE_SIZE) && (Page < 0x100) ) return 1; //�ռ����

	Enable_I2C_IO();	//��EE��Դ
	for( i=0; i<2; i++ )//����2��
	{
		if( I2C_Read_Bottom( Page, offset, IIC_Buf, h ) )continue;//����������ζ�
		
		if( I2C_Read_Bottom( Page, offset, BufA, h ) )continue;//����������ζ�
				
		if( Cmp_Data( IIC_Buf, BufA, h )!=3 ) continue;//�Ƚϲ�һ�´���
		
		if( Page >= CRC_PAGE ) return 0;//���ɹ�
		
		if( Crc_16Bits( IIC_Buf, h ) == 0 ) return 0;//���ɹ�
	}
	 return 2; //fail
} 


#define	SPIFCS0		GPIO_ResetBits(GPIOF, GPIO_Pin_15)  //Flash CS=0
#define	SPIFCS1		GPIO_SetBits  (GPIOF, GPIO_Pin_15)  //Flash CS=1
#define SPIFCR1     HSPI->SPICR1   //SPI���ƼĴ���1
#define SPIFCR2     HSPI->SPICR2   //SPI���ƼĴ���2
#define SPIFCR3     HSPI->SPICR3   //SPI���ƼĴ���3
#define SPIFIE      HSPI->SPIIE    //SPI�жϿ��ƼĴ���
#define SPIFDR_W    HSPI->SPITXF   //SPI���ͻ���Ĵ���
#define SPIFDR_R    HSPI->SPIRXF   //SPI���ջ���Ĵ���
#define SPIFSR      HSPI->SPISTA   //SPI�жϱ�־�Ĵ���


void CloseFlash( void )
{
	FLASHPOWEROFF;
	
	CloseeIO( GPIOF, GPIO_Pin_15 );	//PF15;//F_CS		
	CloseeIO( GPIOF, GPIO_Pin_14 );	//PF14;//F_CLK		
	CloseeIO( GPIOF, GPIO_Pin_13 );	//PF13;//F_DI		
	CloseeIO( GPIOF, GPIO_Pin_12 );	//PF12;//F_DO
	SPIFCS0;
}

void OpenFlash( void )
{
	if( FLASHVCC_P )
	{
		FLASHPOWERON;
		
		SPIFCS1;
		OutputIO( GPIOF, GPIO_Pin_15, 0 );	//PF15;//F_CS		
		AltFunIO( GPIOF, GPIO_Pin_14, 0 );	//PF14;//F_CLK		
		AltFunIO( GPIOF, GPIO_Pin_13, 0 );	//PF13;//F_DI		
		AltFunIO( GPIOF, GPIO_Pin_12, 0 );	//PF12;//F_DO
		
		Delay_Initial(3);	//��ʱ15ms	
	}
	FlashTimer = 3;		//����falsh��Դ��Ч��ʱ�붨ʱ��
	
	SPIFCR1 = 0x1D8; //��ģʽ,��1�������ز���,�½���д����bit3��bps:Fm/8(HSPI)
	SPIFCR2 = 0x22;
	SPIFSR = SPIFSR;
	SPIFCR2 |= B0000_0001;  	//SPIʹ��
}


unsigned char SPI_Tx_Byte( unsigned char x_byte ) 
{
	unsigned char i;

	if( SPIFSR & B0000_0001 ) i = SPIFDR_R ;//�����ռĴ�������ձ�־
	SPIFDR_W = x_byte;	//д����
	
	for( i=0; i<250; i++ )
	{
		if( SPIFSR & B0000_0001 ) return 0;	//��ʱ2ms��ѯSPI���������־��1~4MHz��
	}
	
	return 1;
}


unsigned char SPI_Rx_Byte( unsigned char *x_byte ) 
{
	unsigned char i;

	if( SPIFSR & B0000_0001 ) i = SPIFDR_R ;//�����ռĴ�������ձ�־
	SPIFDR_W = 0;	//���Ĺ���Ҫ����д�������CLK����
	
	for( i=0; i<250; i++ )
	{
		if( SPIFSR & B0000_0001 ) //��ʱ2ms��ѯSPI���������־��1~4MHz��
		{
			*x_byte = SPIFDR_R;
			return 0;
		}
	}
	
	return 1;
}


unsigned char Flash_RdSR1( unsigned char *AckSR )
{
	unsigned char status;
	
	SPIFCS1;
	SPIFCS0;
	
	status = SPI_Tx_Byte(0x05);
	if( status == 0 )
		status = SPI_Rx_Byte(AckSR);
	
	SPIFCS1;
	
	if( status ) return 1;
	else return 0;
}


unsigned char Flash_WREN( void )
{
	unsigned char status, i;
	
	SPIFCS1;
	SPIFCS0;
	status = SPI_Tx_Byte(0x06);
	SPIFCS1;
	if( status ) return 1;
	
	if( Flash_RdSR1(&i) ) return 2;
	if( !(i&B0000_0010) ) return 3;
	
	return 0;
}


unsigned char FlashID( void )
{
	unsigned char status, Buf[3];
	
	SPIFCS1;
	SPIFCS0;
	
	memset( Buf, 0, sizeof(Buf) );
	
	status = SPI_Tx_Byte(0x9F);
	if( !status )
		status = SPI_Rx_Byte( Buf+0 ); //���ұ��
	if( !status )
		status = SPI_Rx_Byte( Buf+1 ); //�������
	if( !status )
		status = SPI_Rx_Byte( Buf+2 ); //�����ܶ�
	
	SPIFCS1;
	
	if( status || (Buf[0] == 0x00) || (Buf[0] == 0xFF) ) return 1;
	else return 0;	
}

unsigned char FlashID_Comm( unsigned char *Buf ) //ͨѶ��flash����
{
	unsigned char status;
	
	OpenFlash();
	
	SPIFCS1;
	SPIFCS0;
	
	memset( Buf, 0, 0x03 );
	
	status = SPI_Tx_Byte(0x9F);
	if( !status )
		status = SPI_Rx_Byte( Buf+0 ); //���ұ��
	if( !status )
		status = SPI_Rx_Byte( Buf+1 ); //�������
	if( !status )
		status = SPI_Rx_Byte( Buf+2 ); //�����ܶ�
	
	SPIFCS1;
	
	if( status || (Buf[0] == 0x00) || (Buf[0] == 0xFF) ) return 1;
	else return 0;	
}


//Page: ������ַ(�ڼ�������); offset: ������ƫ����; Opt: ��������������
unsigned char Flashaddr( unsigned long Page, unsigned short offset, unsigned char Opt ) 
{
	unsigned char status=0;
	union B32_B08_2 Addr;
	unsigned char i;
	
	for( i=0; i<10; i++ )
	{
		Clear_Wdt();
		status = FlashID();	//ͨ����ȡ����ID���ж�Ӳ���Ƿ�����
		if( status==0 ) break;
		Delay_Initial(1);	//��ʱ5ms
	}
	if( status ) return status;
	
	SPIFCS1;

	if( (Opt == 0x02)   //ҳд
	 || (Opt == 0x20)   //������
	 || (Opt == 0x52) ) //���
		status = Flash_WREN();
	
	if( !status )
		SPIFCS0;
	
	if( !status ) 
		if( SPI_Tx_Byte(Opt) ) status = 1;
	
	if( !status ) 
		Addr.B32 = Page*SECTOR_SIZE+offset;
	
	if( !status ) 
		if( SPI_Tx_Byte(Addr.B08[2]) ) status = 1;
	if( !status ) 
		if( SPI_Tx_Byte(Addr.B08[1]) ) status = 1;
	if( !status ) 
		if( SPI_Tx_Byte(Addr.B08[0]) ) status = 1;
	
	if( status )
		SPIFCS1;
	
	return status;
}


unsigned char Flash_Write_Cycle( unsigned short Cycle )
{
	unsigned char status=0, Temp08;
	
	SPIFCS1;

	Do_DelayStart(); //��Ҫ5ms���ڲ�д����, ѭ��һ������ʱ��: 42��Delay()��
	{
		if( Flash_RdSR1(&Temp08) ) status = 1;
		
		if( !status )
			if( !(Temp08&B0000_0001) ) break;
		
		Clear_Wdt();
		
	}While_DelayMsEnd(Cycle*clkmode);

	if( status == 0 )  status = FlashID();	//ͨ����ȡ����ID���ж�Ӳ���Ƿ�����
	
	return status;
}


unsigned char Flash_Sector_Erase( unsigned long Page )
{
	unsigned char status=0;

	OpenFlash();
	
	Delay_Initial(2);	//��ʱ10ms

	if( !status ) 
		if( Flashaddr( Page, 0, 0x20 ) ) status = 1;

	if( !status )
	{
		Delay_Initial(2);	//��ʱ10ms
		status = Flash_Write_Cycle(600); //600ms
	}
	
	SPIFCS1;
	
	return (status);
}


unsigned char Flash_Rd_Bottom( unsigned long Page, unsigned short offset, unsigned char *RtBuf, unsigned short Len )
{
	unsigned short n;
	unsigned char  k, status;

	OpenFlash();

	for( k=0; k<3; k++ )//ÿ������3��
	{
		status = Flashaddr( Page, offset, 3 );
		if( !status )
		{
			for( n=0; n<Len; n++ )
			{
				status = SPI_Rx_Byte( RtBuf+n );
				if( status ) break;
			}
		}
		
		SPIFCS1;
		if( status == 0 ) break;//����ȷ
	}
	
	return( status );
}


//ҳд����������д��ķ�Χ������ҳ��Χ
unsigned char Flash_Page_Write( unsigned long Page, unsigned short offset, unsigned char *InBuf, unsigned short Len )
{
	unsigned short n;
	unsigned char status, Temp08;
	
	if( Len && ((offset/FPAGE_SIZE) != ((offset+Len-1)/FPAGE_SIZE)) ) return 1; //д�����ݱ�����ͬһ��ҳ
	
	//ִ������д��
	OpenFlash();
	
	status = Flashaddr( Page, offset, 2 );
	for( n=0; n<Len; n++ )
	{
		if( status ) break;
		status = SPI_Tx_Byte( InBuf[n] );
	}
	Temp08 = Flash_Write_Cycle(10); //10ms
	if( status || Temp08 ) return 4;
	
	//��ȡ������д�����ݽ��бȶԣ���ͬ��ɹ�
	status = Flashaddr( Page, offset, 3 );
	if( status ) return 5;
	
	for( n=0; n<Len; n++ )
	{
		if( SPI_Rx_Byte( &Temp08 ) ) break;
		if( Temp08 != InBuf[n] ) break;
	}
	
	SPIFCS1;
	
	if( n < Len ) return 6;
	
	return 0; //д��ɹ�
}


//FLASHд����������д�뷶Χ����������
//***ע�������offset=0������£���¼�����������ڵ������ᱻ����***
unsigned char Flash_Write_Bottom( unsigned long Page, unsigned short offset, unsigned char *InBuf, unsigned short Len )
{
	unsigned short i, k, n;
	unsigned char  status=0;
	unsigned long  Addr;
	unsigned long  WrAddr;
	unsigned short WrOffset, WrLen;
	unsigned char  Temp08;
	
	Addr = Page*SECTOR_SIZE+offset;
	if( (InBuf == 0) || (Len > SECTOR_SIZE) 
	|| (Len && ((Addr/SECTOR_SIZE) != ((Addr+Len-1)/SECTOR_SIZE))) ) return 1;

//	if( (offset == 0) && (Page >= FL_REC_ADDR) ) //��¼��������������������ʼ��ַд��ʱ������ִ����������
	if( offset == 0 ) //����������ʼ��ַд��ʱ������ִ����������
	{
		status = Flash_Sector_Erase( Page );
		if(status)
		{
			Delay_Initial(10);	//��ʱ50ms
			status = Flash_Sector_Erase( Page );
		}   
		if( status ) return 1;
	}
	
	if( Len == 0 ) return 0;
	
	OpenFlash();
	
	status = Flashaddr( Page, offset, 3 );
	if( status ) return 1;
	
	WrAddr = Page;
	WrOffset = offset;
	WrLen = Len;
	
	k = 0x00;  //��ʼ������ͬ
	i = Len-1; //����������ͬ
	for( n=0; n<Len; n++ )
	{
		status = SPI_Rx_Byte( &Temp08 );
		if( status ) return 2;
		
		if( Temp08 == InBuf[n] ) 
		{
			if( k == n ) k++; //ͳ�ƴ�Offset��ʼ��ͬ�����ݵĸ�����������ͬ�ģ�����ͳ��
		}
		else
		{
			i = n; //ͳ��InBuf��Flash���������һ����ͬ��λ�ã���λ��֮������ݲ���д�룬����Ч��
		}
	}
	
	WrOffset += k;
	WrLen -= (k+Len-1-i); //���洢β����ͬ������
	
	SPIFCS1;
	
	if( 0 == WrLen ) return 0; //д������ԭ����һ�£���ͬ�ٴ�д�룬���سɹ�
	
	i = k; //InBuf�е�ƫ����
	do
	{
		if( (WrOffset/FPAGE_SIZE) == ((WrOffset+WrLen-1)/FPAGE_SIZE) ) //���β�֧�ֿ�ҳ, ��ִ�д��
			n = WrLen;
		else
			n = FPAGE_SIZE-(WrOffset%FPAGE_SIZE);
		
		status = Flash_Page_Write( WrAddr, WrOffset, InBuf+i, n );
		if( status ) return 3;
		
		i += n;
		WrLen -= n;
		WrOffset += n;
	}while( WrLen );
	
	return 0; //�ɹ�
}


unsigned char IsFlashRec( unsigned char Obj )
{
	if((Obj == ee_minuten_inpage )  //���ɼ�¼
	|| (Obj == ee_timingf_inpage )  //��ʱ����
	|| (Obj == ee_dayf_inpage    )  //�ն���
	|| (Obj == ee_monthn_inpage  )  //�¶���
	|| (Obj == ee_histroyf_inpage)  //�����ն���
	|| (Obj == ee_hourf_inpage   )) //���㶳��
		return 1;

	return 0;
}


//Ϊ��ȡ��¼��׼��Flash�Ĵ洢��ز���
RecStore GetRecNum( unsigned char Obj, unsigned char Case )
{
	unsigned short TmpLen;
	unsigned char Result, Buf[64];
	RecStore RtRec;
	
	memset( (uint08*)(&RtRec), 0, sizeof(RtRec) );

	if( Obj == ee_minuten_inpage ) //���Ӷ���
		RtRec.TotLen = LoadLen[Case];
	else if( Obj == ee_hourf_inpage ) //���㶳��
		RtRec.TotLen = ee_hourfreezedl_lenth;
	else
		RtRec.TotLen = ee_freezedl_lenth;
	RtRec.Depth = MaxRecNum[Obj];

	if( IsFlashRec(Obj) )
	{
		TmpLen = SECTOR_SIZE/RtRec.TotLen;
		RtRec.MaxDepth = ((RtRec.Depth+TmpLen-1)/TmpLen)*TmpLen+TmpLen; //���ɴ洢��¼����
	}
	else
	{
		RtRec.MaxDepth = MaxRecNum[Obj];
	}

	if( Obj == ee_minuten_inpage ) //���Ӷ���
	{
		memcpy( (uint08*)(&RtRec.CurPoint), Load.Point+5*Case+0, 3 );
	}
	else
	{
		ReadE2WithBackup( ee_event_point_page+2*((Obj-1)/12), ee_eventpoint_inpage, Buf, ee_eventpoint_lenth );
		memcpy( (uint08*)(&RtRec.CurPoint), Buf+5*((Obj-1)%12)+0, 3 );
		memcpy( (uint08*)(&RtRec.ValPoint), Buf+5*((Obj-1)%12)+3, 2 );
	}

	if( IsFlashRec(Obj) )
	{
		unsigned long TempF=0;
		
		if( Obj == ee_minuten_inpage ) //���Ӷ���
		{
			Result = I2C_Read_Eeprom( ee_validnum_page, ee_validnum_inpage, Buf, ee_validnum_len ); //���Ӷ�����Ч����ҳ
			if( Result ) return RtRec; //��ȡʧ�� or CRCУ���
			
			memcpy( (uint08*)(&TempF), Buf+3+6*Case, 3 );
		}

		TempF = RtRec.CurPoint-TempF;
		if( TempF > RtRec.Depth ) 
			RtRec.ValPoint = RtRec.Depth;
		else
			RtRec.ValPoint = TempF; //��¼��Ч����
	}
	
	return RtRec;
}


//ȡ�ü�¼����Ч����
unsigned short GetValtimes( unsigned char Obj, unsigned char Case )
{
	RecStore RtRec = GetRecNum( Obj, Case );
	
	return RtRec.ValPoint;
}


const unsigned long Ee_Addr[13] = { 
	0,                       //Ԥ��
	ee_timingfreeze_dl_page, //��ʱ����
	ee_realtimefreeze1_page, //˲ʱ����
	ee_appointfreeze1_page,  //Լ������, ʱ�����л�
	ee_appointfreeze2_page,  //Լ������, ��ʱ�α��л�
	ee_appointfreeze3_page,  //Լ������, ����ʱ���л�
	ee_appointfreeze4_page,  //Լ������, �����л�
	ee_ploadrec_page,        //���Ӷ���
	ee_hourfreezedl_page,    //���㶳��
	ee_dayfreezedl_page,     //�ն���
	ee_monthfreeze_page,     //�¶���
	ee_histroy_dl_page,      //�����ն���
	0                        //�����(Ԥ��)
};


const unsigned long Fl_Addr[13] = { 
	0,               //Ԥ��
	FL_TIMING_ADDR,  //��ʱ����
	0,               //˲ʱ����
	0,               //Լ������, ʱ�����л�
	0,               //Լ������, ��ʱ�α��л�
	0,               //Լ������, ����ʱ���л�
	0,               //Լ������, �����л�
	FL_LOADREC_ADDR, //���Ӷ���
	FL_HOUR_ADDR,    //���㶳��
	FL_DAY_ADDR,     //�ն���
	FL_MONTH_ADDR,   //�¶���
	FL_HISTORY_ADDR, //�����ն���
	0                //�����(Ԥ��)
};


//ȡ�ø�����ŵļ�¼�洢��ַ
//���룺���󣬷����ţ���NN����¼���洢��ַ
//���أ��ɹ�or��������
RtFlash GetRecAddr( unsigned char Obj, unsigned char Case, unsigned short Sn, const RecStore *RtRec )
{
	unsigned char status;
	unsigned char BkObj;
	unsigned long RecPtr, RecPage, Offset;
	RtFlash  RtAddr;
	
	memset( (uint08*)(&RtAddr), 0, sizeof(RtAddr) ); //���㣬��������ʱ��+����ʱ��
	
	BkObj = Obj;
	Obj &= 0x3F; //ȥ�����bit
	
	if( (Obj > ee_clearn_inpage+EventNum) || (Case >= max_casecount) || (Sn == 0) ) return RtAddr;
	if( (0 == RtRec->TotLen) || (Sn > RtRec->ValPoint) ) return RtAddr; //��ȡ�ķ�Χ�����Ѵ洢�ķ�Χ
	
	RecPtr = RtRec->CurPoint;
	if( RecPtr ) RecPtr -= 1;
	RecPtr %= RtRec->MaxDepth;
	if( RecPtr < (Sn-1) )	RecPtr += RtRec->MaxDepth;
	RecPtr -= (Sn-1);

	//��¼����ַ+ƫ��+����
	if( Obj < ee_clearn_inpage )   //������
	{
		RecPage = Ee_Addr[Obj];
		Offset  = 0;
		
		if( IsFlashRec(Obj) )
		{
			if( Sn <= 1 )
			{
				unsigned long EEptr;
				
				EEptr = RtRec->CurPoint;
				if( EEptr ) EEptr -= 1;
				EEptr %= 1;
				if( EEptr < (Sn-1) ) EEptr += 1;
				EEptr -= (Sn-1);
				
				RecPage += 3*EEptr;
				if( ee_minuten_inpage == Obj )  //���Ӷ���
					Offset = LoadOffset[Case];
			}
		}
		else //˲ʱ���ᡢ�л����ᡢ���ݽ��㶳��
		{
			RecPage += 3*RecPtr;
		}
	}
	else
	{
		RecPage = EventTable[Obj-ee_clearn_inpage].page+RecPtr;
		Offset  = EventTable[Obj-ee_clearn_inpage].offset;
	}
	
	RtAddr.DataPage = RecPage; //��������ʱ��RecPageΪ����ֵ
	RtAddr.Offset   = Offset ;

	if( IsFlashRec(Obj) )
	{
		RtAddr.AppPage = RecPtr/(SECTOR_SIZE/RtRec->TotLen)+Fl_Addr[Obj];
		RtAddr.AppPos = (RecPtr%(SECTOR_SIZE/RtRec->TotLen))*RtRec->TotLen;

		if( ee_minuten_inpage == Obj )  //���Ӷ���
		{
			unsigned char i;
			unsigned long TmpLen, Num=0;
			
			for( i=0; i<Case; i++ )  //�ۼ���Ҫ��������
			{
				TmpLen = LoadLen[i];
				if( 0 == TmpLen ) continue;
			
				TmpLen = SECTOR_SIZE/TmpLen;
				Num += (RtRec->Depth+TmpLen-1)/TmpLen+1;
			}
			
			RtAddr.AppPage += Num;
		}
		
		status = Flash_Rd_Bottom( RtAddr.AppPage, RtAddr.AppPos, RtAddr.Clk+1, 5 );
		if( status ) return RtAddr; //��ȡʧ��
	}
	else
	{
		if( Obj < ee_clearn_inpage )   //������
			status = I2C_Read_Eeprom( RtAddr.DataPage, RtAddr.Offset, RtAddr.Clk+1, 5 );
		else
			status = I2C_Read_Eeprom( RtAddr.DataPage, RtAddr.Offset, RtAddr.Clk+0, 6 );
		if( status ) return RtAddr; //��ȡʧ��
	}
	
	return RtAddr;
}


//ʱ�����FLASH���ݸ���
unsigned char SynFlashRec( unsigned char RecNum )
//RecNum(���·���): 0=��ǰ�����һҳ; 1=ȫ������
{
	unsigned short k, n;
	unsigned short Len;
	unsigned char status, Buf[FPAGE_SIZE];
		
	if( 0 == MvFlash.Dir )
	{
		if( 0 == ChkBufZero((uint08*)SynFlash.HisRec, ee_synflash_len+2) ) return 0;	//�������ݾ�Ϊ0,��Ϊ�޸���

		if( Crc_16Bits( (uint08*)SynFlash.HisRec, ee_synflash_len+2 ) )
		{
			status = I2C_Read_Eeprom( ee_synflash_page, ee_synflash_inpage, (uint08*)SynFlash.HisRec, ee_synflash_len );
			if( status ) return 1; //��ȡ���󣬲�����
		}
	}

	n = 0;
	do
	{
		if( 0 == MvFlash.Dir )
		{
			if( 0 == SynFlash.HisRec[n].Page ) 
			{
				n++;
				continue;
			}
			
			MvFlash.Dir = 0x55;
			MvFlash.Obj = n;
			MvFlash.Offset = 0;
		}
		
		if( MvFlash.Dir )
		{
			MvFlash.Page = SynFlash.HisRec[MvFlash.Obj].Page;
			MvFlash.Len  = SynFlash.HisRec[MvFlash.Obj].Len;
			
			if( MvFlash.Offset >= MvFlash.Len )
			{
				Len = 0;
			}
			else
			{
				Len = MvFlash.Len-MvFlash.Offset;
				
				do
				{
					if( EA_OFF ) return 1;	//���粻����,����ֱ�ӷ���
					
					if( (MvFlash.Offset/FPAGE_SIZE) == ((MvFlash.Offset+Len-1)/FPAGE_SIZE) ) //���β�֧�ֿ�ҳ, ��ִ�д��
						k = Len;
					else
						k = FPAGE_SIZE-(MvFlash.Offset%FPAGE_SIZE);
					
					if( 0x55 == MvFlash.Dir ) //�ӵ�ǰ�����޸���
					{
						status = Flash_Rd_Bottom( MvFlash.Page, MvFlash.Offset, Buf, k );
						if( status == 0 )
						status = Flash_Write_Bottom( FL_OLD_ADDR, MvFlash.Offset, Buf, k );
					}
					else if( 0xAA == MvFlash.Dir ) //���޸�������ǰ��
					{
						status = Flash_Rd_Bottom( FL_OLD_ADDR, MvFlash.Offset, Buf, k );
						if( 0 == status )
						status = Flash_Write_Bottom( MvFlash.Page, MvFlash.Offset, Buf, k );
					}
					
					Len -= k;
					MvFlash.Offset += k;
				} while( Len && RecNum	);
			}

			if( 0 == Len )
			{
				MvFlash.Offset = 0;
				if( 0x55 == MvFlash.Dir ) //�ӵ�ǰ��ͬ�����޸���
				{
					MvFlash.Dir = 0xAA; //���޸���ͬ������ǰ��
				}
				else
				{
					SynFlash.HisRec[MvFlash.Obj].Page = 0;
					SynFlash.HisRec[MvFlash.Obj].Len  = 0;
					I2C_Write_Eeprom( ee_synflash_page, ee_synflash_inpage, (uint08*)SynFlash.HisRec, ee_synflash_len );
					
					MvFlash.Dir = 0;
					MvFlash.Obj = 0;
					MvFlash.Page = 0;
					MvFlash.Len  = 0;
				}
			}
		}
		
		if( 0 == RecNum ) break; //����һ�Σ�����һҳ
	} while( n < max_casecount ); 
	
	return 0;
}


//���Ӷ���+�ն���+�¶����EEPROMͬ����FLASH��
void SynEeprom( void )
{
	unsigned char i, n, Obj, result;
	unsigned char Buf[512], Point[64];
	const unsigned char SynObj[6] = { ee_minuten_inpage, ee_hourf_inpage, ee_timingf_inpage, ee_dayf_inpage, ee_monthn_inpage, ee_histroyf_inpage };

	if( 0 == SynEe.Enable ) return;
	SynEe.Enable = 0; //���ͬ��EE��־

	for( n=0; n<sizeof(SynObj); n++ )
	{
		Obj = SynObj[n];
		for( i=0; i<max_casecount; i++ )
		{
			unsigned short No = 0;

			if( EA_OFF ) return;	//���粻����,����ֱ�ӷ���
			
			if( ee_minuten_inpage == Obj )  //���Ӷ���
			{
				memcpy( (uint08*)(&No), Load.Point+5*i+3, 2 ); //��ͬ����¼����
			}
			else //�ն��ᡢ�¶���
			{
				if( i ) break; //ֻ֧�ַ���0
				ReadE2WithBackup( ee_event_point_page+2*((Obj-1)/12), ee_eventpoint_inpage, Point, ee_eventpoint_lenth );
				memcpy( (uint08*)(&No), Point+5*((Obj-1)%12)+3, 2 );
			}
			
			if( No > 1 ) No = 1;
			if( No )
			{
				RtFlash  RtAddr;
				RecStore RtRec = GetRecNum( Obj, i ); //��¼�洢����׼��

				//ȡ�ñ�����¼�Ĵ洢��������ַ��ƫ����������
				RtAddr = GetRecAddr( Obj, i, No, &RtRec );
				
				if( ee_minuten_inpage == Obj )  //���Ӷ���
				{
					result = 0;
					memcpy( Buf, LoadBuf+LoadOffset[i], LoadLen[i] );
				}
				else if( ee_hourf_inpage == Obj )//���㶳��
				{
					result = I2C_Read_Bottom( Ee_Addr[Obj]+0, 0, Buf, ee_hourfreezedl_lenth );	//����ʱ��+��������
				}
				else
				{
					result = I2C_Read_Bottom( Ee_Addr[Obj]+0, 0, Buf, 128 );	//����ʱ��+��������
					if( result == 0 )
					result = I2C_Read_Bottom( Ee_Addr[Obj]+1, 0, Buf+128, 128 );	//��������
					if( result == 0 )
					result = I2C_Read_Bottom( Ee_Addr[Obj]+2, 0, Buf+256, ee_freezedl_lenth-256 );	//��������
				}
				
				if( EA_OFF ) return;	//���粻����,����ֱ�ӷ���
				
				No--;
				
				if( 0 == result )
				{
					if( SynEe.Page != RtAddr.AppPage ) //������ҳд��ʱ�����������ҳ��������
					{
						SynEe.Page = RtAddr.AppPage; //���µ�ǰҳ
						SynEe.RpTimes = Def_Erase_Times; //���ò�������
					}
					
					result = Flash_Write_Bottom( RtAddr.AppPage, RtAddr.AppPos, Buf, RtRec.TotLen ); //д��Flash��
					if( result && SynEe.RpTimes ) //д��ʧ�ܺ�����ǰ���������ݻ���EE�У����������������д��
					{
						unsigned short Num;
						
						SynEe.RpTimes--;
						
						Num = No+1+RtAddr.AppPos/RtRec.TotLen;
						if( (Num <= RtRec.ValPoint) && (Num <= 1) )
							No = Num;
					}
				}
				
				if( ee_minuten_inpage == Obj )  //���Ӷ���
				{
					memcpy( Load.Point+5*i+3, (uint08*)(&No), 2 );
					Load.Crc16.B16 = Crc_16Bits( Load.Point, ee_loadpoint_lenth ); //CRC����
				}
				else
				{
					memcpy( Point+5*((Obj-1)%12)+3, (uint08*)(&No), 2 );
					WriteE2WithBackup( ee_event_point_page+2*((Obj-1)/12), ee_eventpoint_inpage, Point, ee_eventpoint_lenth );
				}
			}
		}
	}
}
