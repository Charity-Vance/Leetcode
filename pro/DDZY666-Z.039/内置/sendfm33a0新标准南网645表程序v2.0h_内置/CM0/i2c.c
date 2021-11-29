#include "ex_var.h"
#include "ex_func.h"
#include "FM32L0XX.h"  
#include <string.h>

#define		CRC_PAGE			0x42		//CRC校验结束页
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
		if( (I2C->I2CIR&0x01) == 0x01 ) break; //中断标志置位时跳出循环
	}
	
	if( i < 18*SSP_TBIT )
	{
		I2C->I2CIR |= 0x01; //clr int flag

		if( (I2C->I2CSTA&0x02) == 0x02 ) //从机无应答
		{
			return 2; //失败
		}
		else
		{
			return 0; //成功
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
		if( (I2C->I2CIR&0x01) == 0x01 ) break; //中断标志置位, 跳出循环
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
	result = I2c_Send_Bit( B0110_0001 );//发送起始位
	if( result != 0 ) return 1; //failure.

	//-------------- device addr -------------
	result = I2c_Send_Byte( Devi_Addr ); //发送器件地址
	if( result != 0 ) return 2; //failure.

	//--------------- data addr --------------
	result = I2c_Send_Byte( Addr>>8 ); //发送数据地址高8位
	if( result != 0 ) return 3; //failure.

	result = I2c_Send_Byte( Addr>>0 ); //发送数据地址低8位
	if( result != 0 ) return 3; //failure.

	if( Opt == 1 ) //读操作
	{
		result = I2c_Send_Bit( B0110_0010 ); //发送重起始位
		if( result != 0 ) return 5; //failure.
		
		result = I2c_Send_Byte( Devi_Addr|1 ); //发送器件地址,读取
		if( result != 0 ) return 5; //failure.
	}
		
	return 0; //ok
}
  

unsigned char Wait_for_end( unsigned int Page )
{
	unsigned char result, Devi_Addr;

	Devi_Addr = Devi_Addr1;
	
	Do_DelayStart(); //需要5ms的内部写周期, 循环一次所需时间: 42个Delay()。
	{
		I2c_Send_Bit( B0110_0001 );	//发送起始位

		result = I2c_Send_Byte( Devi_Addr ); //发送器件地址

		I2c_Send_Bit( B0110_0100 ); //发送停止位

		if( result == 0 ) return 0; //设置地址成功, 写周期结束
    
	}While_DelayMsEnd(5*clkmode);

	return 1; //设置地址失败
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
		if( I2C_Write_Eeprom( Page, inpage, Buf, Len ) ) return 1;	//失败再写一次
	}
	
	I2C_Write_Eeprom( Page+1, inpage, Buf, Len );
	 
	return 0;
}

uint08  I2C_Read_Eeprom44( unsigned int Page, uint08 *Buf, uint08 Len )
{
	if( I2C_Read_Eeprom( Page, 44, Buf, Len ) )
	{
		 if( I2C_Read_Eeprom( Page, 44, Buf, Len ) ) return 1;	//失败再读一次
	}
	
	return 0;
}

uint08  I2C_Write_Eeprom44( unsigned int Page, uint08 *Buf, uint08 Len )
{	
	if( I2C_Write_Eeprom( Page, 44, Buf, Len ) )
	{
		if( I2C_Write_Eeprom( Page, 44, Buf, Len ) ) return 1;	//失败再写一次
	}
	
	return 0;
}

unsigned char I2C_Write_Bottom(unsigned int Page, unsigned char offset, unsigned char *Buf, unsigned char h)
{
	unsigned char k, n, status;
	
	for( k=0; k<3; k++ )//每遍最多写3次 
	{                                   	
		status = 0;
		if( Sendaddr( Page, offset, 0 ) ) status = 1; //写入失败
		else 
		{
			for( n=0; n<h; n++ )
			{
				//发送一个字节
				if( I2c_Send_Byte( Buf[n] ) ) {status = 1; break;} //写入失败
			}
		}
		//发送停止位
		if( I2c_Send_Bit( B0110_0100 ) ) status = 1;
		
		if( status == 0 ) {Wait_for_end(Page); break;}//写正确
	}
	
	return( status );
}

unsigned char I2C_Read_Bottom(unsigned int Page, unsigned char offset, unsigned char *Buf, unsigned char h)
{
	unsigned char k, n, status;
	
	for( k=0; k<3; k++ )//每遍最多读3次
	{
		status = 0;
		if( Sendaddr( Page, offset, 1 ) ) status = 1; //写入失败
		else 
		{
			for( n=0; n<h; n++ )
			{
				//接收一个字节
				if( I2c_Receive_Byte( Buf+n ) ) {status = 1; break;} 
        		
				if( n < (h-1) )	I2C->I2CSTA = B0000_0000;
				else		I2C->I2CSTA = B0000_0001;
				
				{
					//发送 ACK
					if( I2c_Send_Bit( B0111_0000) )  {I2C->I2CSTA = B0000_0000;status = 1; break;}	//失败
					I2C->I2CSTA = B0000_0000;
				}
			}
		}
		//发送停止位
		if( I2c_Send_Bit( B0110_0100 ) ) status = 1;	//失败
		
		if( status == 0 ) break;//读正确
	}
	
	return( status );
}

unsigned char I2C_Write_Eeprom( unsigned int Page, unsigned char offset, unsigned char *IIC_Buf, unsigned char Len )
{
	unsigned char h, i;
	unsigned char BufA[128],BufB[128];
	
	if( Page >= 0x280 ) return 1; //地址溢出 
	if( Len == 0 ) return 1; //空间溢出


	h = Len;
	memcpy( BufA, IIC_Buf, Len );
	if( Page < CRC_PAGE ) 
	{
		Crc_16Bits_Add2( BufA, Len );			//计算crc
		h = h + 2;					//长度加2字节crc 
	}
	if( ((offset+h)>PAGE_SIZE) && (Page < 0x100) ) return 1; //空间溢出

	
	Enable_I2C_IO();	//打开EE电源
	for( i=0; i<2; i++ )//最多写2遍
	{                              	
    	if( I2C_Write_Bottom( Page, offset, BufA, h ) )continue;//错误结束本次写
		
		if( I2C_Read_Bottom( Page, offset, BufB, h ) )continue;//错误结束本次读
		
		if( Cmp_Data( BufA, BufB, h )==3 ) return 0;	//读写一致成功返回
	}
	return 2; //fail
}


unsigned char I2C_Read_Eeprom( unsigned int Page, unsigned char offset, unsigned char *IIC_Buf, unsigned char Len ) 
{ 
	unsigned char h, i;
	unsigned char BufA[128];

	if( Len == 0 ) return 1; //空间溢出
	
	if( Page >= 0x280 ) return 1; //地址溢出 
		
	h = Len;
	if( Page < CRC_PAGE ) h = h + 2;	//长度加2字节crc 

	
	if( ((offset+h)>PAGE_SIZE) && (Page < 0x100) ) return 1; //空间溢出

	Enable_I2C_IO();	//打开EE电源
	for( i=0; i<2; i++ )//最多读2遍
	{
		if( I2C_Read_Bottom( Page, offset, IIC_Buf, h ) )continue;//错误结束本次读
		
		if( I2C_Read_Bottom( Page, offset, BufA, h ) )continue;//错误结束本次读
				
		if( Cmp_Data( IIC_Buf, BufA, h )!=3 ) continue;//比较不一致错误
		
		if( Page >= CRC_PAGE ) return 0;//读成功
		
		if( Crc_16Bits( IIC_Buf, h ) == 0 ) return 0;//读成功
	}
	 return 2; //fail
} 


#define	SPIFCS0		GPIO_ResetBits(GPIOF, GPIO_Pin_15)  //Flash CS=0
#define	SPIFCS1		GPIO_SetBits  (GPIOF, GPIO_Pin_15)  //Flash CS=1
#define SPIFCR1     HSPI->SPICR1   //SPI控制寄存器1
#define SPIFCR2     HSPI->SPICR2   //SPI控制寄存器2
#define SPIFCR3     HSPI->SPICR3   //SPI控制寄存器3
#define SPIFIE      HSPI->SPIIE    //SPI中断控制寄存器
#define SPIFDR_W    HSPI->SPITXF   //SPI发送缓存寄存器
#define SPIFDR_R    HSPI->SPIRXF   //SPI接收缓存寄存器
#define SPIFSR      HSPI->SPISTA   //SPI中断标志寄存器


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
		
		Delay_Initial(3);	//延时15ms	
	}
	FlashTimer = 3;		//启动falsh电源有效延时秒定时器
	
	SPIFCR1 = 0x1D8; //主模式,第1个上升沿采样,下降沿写数据bit3，bps:Fm/8(HSPI)
	SPIFCR2 = 0x22;
	SPIFSR = SPIFSR;
	SPIFCR2 |= B0000_0001;  	//SPI使能
}


unsigned char SPI_Tx_Byte( unsigned char x_byte ) 
{
	unsigned char i;

	if( SPIFSR & B0000_0001 ) i = SPIFDR_R ;//读接收寄存器清接收标志
	SPIFDR_W = x_byte;	//写数据
	
	for( i=0; i<250; i++ )
	{
		if( SPIFSR & B0000_0001 ) return 0;	//延时2ms查询SPI传输结束标志（1~4MHz）
	}
	
	return 1;
}


unsigned char SPI_Rx_Byte( unsigned char *x_byte ) 
{
	unsigned char i;

	if( SPIFSR & B0000_0001 ) i = SPIFDR_R ;//读接收寄存器清接收标志
	SPIFDR_W = 0;	//读的过程要发送写命令才有CLK波形
	
	for( i=0; i<250; i++ )
	{
		if( SPIFSR & B0000_0001 ) //延时2ms查询SPI传输结束标志（1~4MHz）
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
		status = SPI_Rx_Byte( Buf+0 ); //厂家编号
	if( !status )
		status = SPI_Rx_Byte( Buf+1 ); //器件编号
	if( !status )
		status = SPI_Rx_Byte( Buf+2 ); //器件密度
	
	SPIFCS1;
	
	if( status || (Buf[0] == 0x00) || (Buf[0] == 0xFF) ) return 1;
	else return 0;	
}

unsigned char FlashID_Comm( unsigned char *Buf ) //通讯读flash容量
{
	unsigned char status;
	
	OpenFlash();
	
	SPIFCS1;
	SPIFCS0;
	
	memset( Buf, 0, 0x03 );
	
	status = SPI_Tx_Byte(0x9F);
	if( !status )
		status = SPI_Rx_Byte( Buf+0 ); //厂家编号
	if( !status )
		status = SPI_Rx_Byte( Buf+1 ); //器件编号
	if( !status )
		status = SPI_Rx_Byte( Buf+2 ); //器件密度
	
	SPIFCS1;
	
	if( status || (Buf[0] == 0x00) || (Buf[0] == 0xFF) ) return 1;
	else return 0;	
}


//Page: 扇区地址(第几个扇区); offset: 扇区内偏移量; Opt: 操作扇区命令码
unsigned char Flashaddr( unsigned long Page, unsigned short offset, unsigned char Opt ) 
{
	unsigned char status=0;
	union B32_B08_2 Addr;
	unsigned char i;
	
	for( i=0; i<10; i++ )
	{
		Clear_Wdt();
		status = FlashID();	//通过读取厂家ID来判断硬件是否正常
		if( status==0 ) break;
		Delay_Initial(1);	//延时5ms
	}
	if( status ) return status;
	
	SPIFCS1;

	if( (Opt == 0x02)   //页写
	 || (Opt == 0x20)   //扇区擦
	 || (Opt == 0x52) ) //块擦
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

	Do_DelayStart(); //需要5ms的内部写周期, 循环一次所需时间: 42个Delay()。
	{
		if( Flash_RdSR1(&Temp08) ) status = 1;
		
		if( !status )
			if( !(Temp08&B0000_0001) ) break;
		
		Clear_Wdt();
		
	}While_DelayMsEnd(Cycle*clkmode);

	if( status == 0 )  status = FlashID();	//通过读取厂家ID来判断硬件是否正常
	
	return status;
}


unsigned char Flash_Sector_Erase( unsigned long Page )
{
	unsigned char status=0;

	OpenFlash();
	
	Delay_Initial(2);	//延时10ms

	if( !status ) 
		if( Flashaddr( Page, 0, 0x20 ) ) status = 1;

	if( !status )
	{
		Delay_Initial(2);	//延时10ms
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

	for( k=0; k<3; k++ )//每遍最多读3次
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
		if( status == 0 ) break;//读正确
	}
	
	return( status );
}


//页写函数，限制写入的范围不超过页范围
unsigned char Flash_Page_Write( unsigned long Page, unsigned short offset, unsigned char *InBuf, unsigned short Len )
{
	unsigned short n;
	unsigned char status, Temp08;
	
	if( Len && ((offset/FPAGE_SIZE) != ((offset+Len-1)/FPAGE_SIZE)) ) return 1; //写入数据必须在同一个页
	
	//执行数据写入
	OpenFlash();
	
	status = Flashaddr( Page, offset, 2 );
	for( n=0; n<Len; n++ )
	{
		if( status ) break;
		status = SPI_Tx_Byte( InBuf[n] );
	}
	Temp08 = Flash_Write_Cycle(10); //10ms
	if( status || Temp08 ) return 4;
	
	//读取数据与写入数据进行比对，相同则成功
	status = Flashaddr( Page, offset, 3 );
	if( status ) return 5;
	
	for( n=0; n<Len; n++ )
	{
		if( SPI_Rx_Byte( &Temp08 ) ) break;
		if( Temp08 != InBuf[n] ) break;
	}
	
	SPIFCS1;
	
	if( n < Len ) return 6;
	
	return 0; //写入成功
}


//FLASH写函数，限制写入范围不超过扇区
//***注意事项：在offset=0的情况下，记录区域数据所在的扇区会被擦除***
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

//	if( (offset == 0) && (Page >= FL_REC_ADDR) ) //记录区的扇区，从扇区的起始地址写入时，需先执行扇区擦除
	if( offset == 0 ) //从扇区的起始地址写入时，需先执行扇区擦除
	{
		status = Flash_Sector_Erase( Page );
		if(status)
		{
			Delay_Initial(10);	//延时50ms
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
	
	k = 0x00;  //开始部分相同
	i = Len-1; //结束部分相同
	for( n=0; n<Len; n++ )
	{
		status = SPI_Rx_Byte( &Temp08 );
		if( status ) return 2;
		
		if( Temp08 == InBuf[n] ) 
		{
			if( k == n ) k++; //统计从Offset开始相同的数据的个数，遇到不同的，不再统计
		}
		else
		{
			i = n; //统计InBuf和Flash中数据最后一个不同的位置，此位置之后的数据不再写入，提升效率
		}
	}
	
	WrOffset += k;
	WrLen -= (k+Len-1-i); //不存储尾部相同的数据
	
	SPIFCS1;
	
	if( 0 == WrLen ) return 0; //写入数和原数据一致，不同再次写入，返回成功
	
	i = k; //InBuf中的偏移量
	do
	{
		if( (WrOffset/FPAGE_SIZE) == ((WrOffset+WrLen-1)/FPAGE_SIZE) ) //单次不支持跨页, 需分次写入
			n = WrLen;
		else
			n = FPAGE_SIZE-(WrOffset%FPAGE_SIZE);
		
		status = Flash_Page_Write( WrAddr, WrOffset, InBuf+i, n );
		if( status ) return 3;
		
		i += n;
		WrLen -= n;
		WrOffset += n;
	}while( WrLen );
	
	return 0; //成功
}


unsigned char IsFlashRec( unsigned char Obj )
{
	if((Obj == ee_minuten_inpage )  //负荷记录
	|| (Obj == ee_timingf_inpage )  //定时冻结
	|| (Obj == ee_dayf_inpage    )  //日冻结
	|| (Obj == ee_monthn_inpage  )  //月冻结
	|| (Obj == ee_histroyf_inpage)  //结算日冻结
	|| (Obj == ee_hourf_inpage   )) //整点冻结
		return 1;

	return 0;
}


//为读取记录，准备Flash的存储相关参数
RecStore GetRecNum( unsigned char Obj, unsigned char Case )
{
	unsigned short TmpLen;
	unsigned char Result, Buf[64];
	RecStore RtRec;
	
	memset( (uint08*)(&RtRec), 0, sizeof(RtRec) );

	if( Obj == ee_minuten_inpage ) //分钟冻结
		RtRec.TotLen = LoadLen[Case];
	else if( Obj == ee_hourf_inpage ) //整点冻结
		RtRec.TotLen = ee_hourfreezedl_lenth;
	else
		RtRec.TotLen = ee_freezedl_lenth;
	RtRec.Depth = MaxRecNum[Obj];

	if( IsFlashRec(Obj) )
	{
		TmpLen = SECTOR_SIZE/RtRec.TotLen;
		RtRec.MaxDepth = ((RtRec.Depth+TmpLen-1)/TmpLen)*TmpLen+TmpLen; //最大可存储记录条数
	}
	else
	{
		RtRec.MaxDepth = MaxRecNum[Obj];
	}

	if( Obj == ee_minuten_inpage ) //分钟冻结
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
		
		if( Obj == ee_minuten_inpage ) //分钟冻结
		{
			Result = I2C_Read_Eeprom( ee_validnum_page, ee_validnum_inpage, Buf, ee_validnum_len ); //分钟冻结有效次数页
			if( Result ) return RtRec; //读取失败 or CRC校验错
			
			memcpy( (uint08*)(&TempF), Buf+3+6*Case, 3 );
		}

		TempF = RtRec.CurPoint-TempF;
		if( TempF > RtRec.Depth ) 
			RtRec.ValPoint = RtRec.Depth;
		else
			RtRec.ValPoint = TempF; //记录有效条数
	}
	
	return RtRec;
}


//取得记录的有效次数
unsigned short GetValtimes( unsigned char Obj, unsigned char Case )
{
	RecStore RtRec = GetRecNum( Obj, Case );
	
	return RtRec.ValPoint;
}


const unsigned long Ee_Addr[13] = { 
	0,                       //预留
	ee_timingfreeze_dl_page, //定时冻结
	ee_realtimefreeze1_page, //瞬时冻结
	ee_appointfreeze1_page,  //约定冻结, 时区表切换
	ee_appointfreeze2_page,  //约定冻结, 日时段表切换
	ee_appointfreeze3_page,  //约定冻结, 阶梯时区切换
	ee_appointfreeze4_page,  //约定冻结, 阶梯切换
	ee_ploadrec_page,        //分钟冻结
	ee_hourfreezedl_page,    //整点冻结
	ee_dayfreezedl_page,     //日冻结
	ee_monthfreeze_page,     //月冻结
	ee_histroy_dl_page,      //结算日冻结
	0                        //年结算(预留)
};


const unsigned long Fl_Addr[13] = { 
	0,               //预留
	FL_TIMING_ADDR,  //定时冻结
	0,               //瞬时冻结
	0,               //约定冻结, 时区表切换
	0,               //约定冻结, 日时段表切换
	0,               //约定冻结, 阶梯时区切换
	0,               //约定冻结, 阶梯切换
	FL_LOADREC_ADDR, //分钟冻结
	FL_HOUR_ADDR,    //整点冻结
	FL_DAY_ADDR,     //日冻结
	FL_MONTH_ADDR,   //月冻结
	FL_HISTORY_ADDR, //结算日冻结
	0                //年结算(预留)
};


//取得给定序号的记录存储地址
//输入：对象，方案号，上NN条记录，存储地址
//返回：成功or错误类型
RtFlash GetRecAddr( unsigned char Obj, unsigned char Case, unsigned short Sn, const RecStore *RtRec )
{
	unsigned char status;
	unsigned char BkObj;
	unsigned long RecPtr, RecPage, Offset;
	RtFlash  RtAddr;
	
	memset( (uint08*)(&RtAddr), 0, sizeof(RtAddr) ); //清零，包括发生时间+结束时间
	
	BkObj = Obj;
	Obj &= 0x3F; //去掉最高bit
	
	if( (Obj > ee_clearn_inpage+EventNum) || (Case >= max_casecount) || (Sn == 0) ) return RtAddr;
	if( (0 == RtRec->TotLen) || (Sn > RtRec->ValPoint) ) return RtAddr; //读取的范围超过已存储的范围
	
	RecPtr = RtRec->CurPoint;
	if( RecPtr ) RecPtr -= 1;
	RecPtr %= RtRec->MaxDepth;
	if( RecPtr < (Sn-1) )	RecPtr += RtRec->MaxDepth;
	RecPtr -= (Sn-1);

	//记录：地址+偏移+长度
	if( Obj < ee_clearn_inpage )   //冻结类
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
				if( ee_minuten_inpage == Obj )  //分钟冻结
					Offset = LoadOffset[Case];
			}
		}
		else //瞬时冻结、切换冻结、阶梯结算冻结
		{
			RecPage += 3*RecPtr;
		}
	}
	else
	{
		RecPage = EventTable[Obj-ee_clearn_inpage].page+RecPtr;
		Offset  = EventTable[Obj-ee_clearn_inpage].offset;
	}
	
	RtAddr.DataPage = RecPage; //正常返回时，RecPage为非零值
	RtAddr.Offset   = Offset ;

	if( IsFlashRec(Obj) )
	{
		RtAddr.AppPage = RecPtr/(SECTOR_SIZE/RtRec->TotLen)+Fl_Addr[Obj];
		RtAddr.AppPos = (RecPtr%(SECTOR_SIZE/RtRec->TotLen))*RtRec->TotLen;

		if( ee_minuten_inpage == Obj )  //分钟冻结
		{
			unsigned char i;
			unsigned long TmpLen, Num=0;
			
			for( i=0; i<Case; i++ )  //累计需要的扇区数
			{
				TmpLen = LoadLen[i];
				if( 0 == TmpLen ) continue;
			
				TmpLen = SECTOR_SIZE/TmpLen;
				Num += (RtRec->Depth+TmpLen-1)/TmpLen+1;
			}
			
			RtAddr.AppPage += Num;
		}
		
		status = Flash_Rd_Bottom( RtAddr.AppPage, RtAddr.AppPos, RtAddr.Clk+1, 5 );
		if( status ) return RtAddr; //读取失败
	}
	else
	{
		if( Obj < ee_clearn_inpage )   //冻结类
			status = I2C_Read_Eeprom( RtAddr.DataPage, RtAddr.Offset, RtAddr.Clk+1, 5 );
		else
			status = I2C_Read_Eeprom( RtAddr.DataPage, RtAddr.Offset, RtAddr.Clk+0, 6 );
		if( status ) return RtAddr; //读取失败
	}
	
	return RtAddr;
}


//时间回退FLASH数据更新
unsigned char SynFlashRec( unsigned char RecNum )
//RecNum(更新方案): 0=当前对象的一页; 1=全部对象
{
	unsigned short k, n;
	unsigned short Len;
	unsigned char status, Buf[FPAGE_SIZE];
		
	if( 0 == MvFlash.Dir )
	{
		if( 0 == ChkBufZero((uint08*)SynFlash.HisRec, ee_synflash_len+2) ) return 0;	//所有数据均为0,认为无更新

		if( Crc_16Bits( (uint08*)SynFlash.HisRec, ee_synflash_len+2 ) )
		{
			status = I2C_Read_Eeprom( ee_synflash_page, ee_synflash_inpage, (uint08*)SynFlash.HisRec, ee_synflash_len );
			if( status ) return 1; //读取错误，不更新
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
					if( EA_OFF ) return 1;	//掉电不处理,程序直接返回
					
					if( (MvFlash.Offset/FPAGE_SIZE) == ((MvFlash.Offset+Len-1)/FPAGE_SIZE) ) //单次不支持跨页, 需分次写入
						k = Len;
					else
						k = FPAGE_SIZE-(MvFlash.Offset%FPAGE_SIZE);
					
					if( 0x55 == MvFlash.Dir ) //从当前区到修改区
					{
						status = Flash_Rd_Bottom( MvFlash.Page, MvFlash.Offset, Buf, k );
						if( status == 0 )
						status = Flash_Write_Bottom( FL_OLD_ADDR, MvFlash.Offset, Buf, k );
					}
					else if( 0xAA == MvFlash.Dir ) //从修改区到当前区
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
				if( 0x55 == MvFlash.Dir ) //从当前区同步到修改区
				{
					MvFlash.Dir = 0xAA; //从修改区同步到当前区
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
		
		if( 0 == RecNum ) break; //调用一次，搬运一页
	} while( n < max_casecount ); 
	
	return 0;
}


//分钟冻结+日冻结+月冻结从EEPROM同步到FLASH中
void SynEeprom( void )
{
	unsigned char i, n, Obj, result;
	unsigned char Buf[512], Point[64];
	const unsigned char SynObj[6] = { ee_minuten_inpage, ee_hourf_inpage, ee_timingf_inpage, ee_dayf_inpage, ee_monthn_inpage, ee_histroyf_inpage };

	if( 0 == SynEe.Enable ) return;
	SynEe.Enable = 0; //清除同步EE标志

	for( n=0; n<sizeof(SynObj); n++ )
	{
		Obj = SynObj[n];
		for( i=0; i<max_casecount; i++ )
		{
			unsigned short No = 0;

			if( EA_OFF ) return;	//掉电不处理,程序直接返回
			
			if( ee_minuten_inpage == Obj )  //分钟冻结
			{
				memcpy( (uint08*)(&No), Load.Point+5*i+3, 2 ); //待同步记录条数
			}
			else //日冻结、月冻结
			{
				if( i ) break; //只支持方案0
				ReadE2WithBackup( ee_event_point_page+2*((Obj-1)/12), ee_eventpoint_inpage, Point, ee_eventpoint_lenth );
				memcpy( (uint08*)(&No), Point+5*((Obj-1)%12)+3, 2 );
			}
			
			if( No > 1 ) No = 1;
			if( No )
			{
				RtFlash  RtAddr;
				RecStore RtRec = GetRecNum( Obj, i ); //记录存储参数准备

				//取得本条记录的存储参数：地址，偏移量，长度
				RtAddr = GetRecAddr( Obj, i, No, &RtRec );
				
				if( ee_minuten_inpage == Obj )  //分钟冻结
				{
					result = 0;
					memcpy( Buf, LoadBuf+LoadOffset[i], LoadLen[i] );
				}
				else if( ee_hourf_inpage == Obj )//整点冻结
				{
					result = I2C_Read_Bottom( Ee_Addr[Obj]+0, 0, Buf, ee_hourfreezedl_lenth );	//冻结时间+冻结数据
				}
				else
				{
					result = I2C_Read_Bottom( Ee_Addr[Obj]+0, 0, Buf, 128 );	//冻结时间+冻结数据
					if( result == 0 )
					result = I2C_Read_Bottom( Ee_Addr[Obj]+1, 0, Buf+128, 128 );	//冻结数据
					if( result == 0 )
					result = I2C_Read_Bottom( Ee_Addr[Obj]+2, 0, Buf+256, ee_freezedl_lenth-256 );	//冻结数据
				}
				
				if( EA_OFF ) return;	//掉电不处理,程序直接返回
				
				No--;
				
				if( 0 == result )
				{
					if( SynEe.Page != RtAddr.AppPage ) //发生换页写入时，重置允许此页擦除次数
					{
						SynEe.Page = RtAddr.AppPage; //更新当前页
						SynEe.RpTimes = Def_Erase_Times; //重置擦除次数
					}
					
					result = Flash_Write_Bottom( RtAddr.AppPage, RtAddr.AppPos, Buf, RtRec.TotLen ); //写入Flash区
					if( result && SynEe.RpTimes ) //写入失败后，若当前扇区的数据还在EE中，则擦除扇区，重新写入
					{
						unsigned short Num;
						
						SynEe.RpTimes--;
						
						Num = No+1+RtAddr.AppPos/RtRec.TotLen;
						if( (Num <= RtRec.ValPoint) && (Num <= 1) )
							No = Num;
					}
				}
				
				if( ee_minuten_inpage == Obj )  //分钟冻结
				{
					memcpy( Load.Point+5*i+3, (uint08*)(&No), 2 );
					Load.Crc16.B16 = Crc_16Bits( Load.Point, ee_loadpoint_lenth ); //CRC计算
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
