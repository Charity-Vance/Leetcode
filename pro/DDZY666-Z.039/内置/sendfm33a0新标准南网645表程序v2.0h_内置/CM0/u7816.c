#include "ex_var.h"
#include "ex_func.h"
#include "FM32L0XX.h"  
#include <string.h>
#include "Cpu_card.h"


void Delay_Netu( unsigned char Num )	//Num*1etu
{
	//unsigned int i;
	TicksDelayUs(93*Num*clkmode);
	//for(i=0; i<Num*50; i++);		//1etu=93us(4M),或者1etu=186us(2M)
}

//复位响应数据时间为400/f~40000/f即100us~10ms
//返回值: 1为下降沿; 0为无变化
unsigned char Judge_Edge( unsigned char CH )
{
	unsigned int i;

	Delay_Netu(1);

	for( i=0x00; i<100; i++ ) 	//约10ms(4M),或者20ms(2M)
	{
//		if( CH == ESAM )
//		{
//			if( (U7816SECONDSTATUS0&B0000_0001) == 1 ) //正在接收
//			{
//				return 1;
//			}
//		}
//		else
		{
			if( (U7816SECONDSTATUS0&B0000_0001) == 1 ) //正在接收
			{
				return 1;
			}
		}
		Delay_Netu(1);
	}
		
	return 0;
}

//最长时间应为9600etu,目前为9600etu,1etu=93us
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
	
	for( i=0x00; i<10000; i++ ) 	//约900ms(4M),或者1800ms(2M)
	{
		Clear_Wdt();
		Delay_Netu(1);
		
//		if( CH == ESAM )
//		{
//			if( U7816PRIMARYSTATUS0&B0000_0001 ) //RX_FLAG已经置位
//			{
//				*Data = U7816RXBUF0;
//                	
//				return 1; //成功
//			}
//                	
//			if( U7816PRIMARYSTATUS0&B0000_0100 ) //ERROR_FLAG已经置位
//			{
////				switch( U7816ERRSTATUS ) //所有标志位: 硬件置位，写0清零
////				{
////					case B0000_0001: //接收溢出错误标志位
////						break;
//                	
////					case B0000_0010: //接收帧格式错误标志位
////						break;
//                	
////					case B0000_0100: //接收数据奇偶校验错误标志位
////						break;
//                	
////					case B0000_1000: //发送数据奇偶校验错误标志位
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
			
			if( U7816PRIMARYSTATUS0&B0000_0001 ) //RX_FLAG已经置位
			{
				*Data = U7816RXBUF0;
                	
				return 1; //成功
			}
                	
			if( U7816PRIMARYSTATUS0&B0000_0100 ) //ERROR_FLAG已经置位
			{
//				switch( U7816ERRSTATUS ) //所有标志位: 硬件置位，写0清零
//				{
//					case B0000_0001: //接收溢出错误标志位
//						break;
                	
//					case B0000_0010: //接收帧格式错误标志位
//						break;
                	
//					case B0000_0100: //接收数据奇偶校验错误标志位
//						break;
                	
//					case B0000_1000: //发送数据奇偶校验错误标志位
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
//		Delay_Netu(2);							//延时1个etu,保证从设备稳定工作
//		U7816TXBUF0 = Data;
//	}
//	else
	{
		U7816CTRL0 = DEF_USART0CTRL|DEF_USART0TX_EN|DEF_USART0CLK_EN;	//U7816_0
		Delay_Netu(2);							//延时1个etu,保证从设备稳定工作
		U7816TXBUF0 = Data;
	}
	
	for( i=0x00; i<400; i++ ) 	//约39ms(4M),或者78ms(2M)
	{
		Clear_Wdt();
		Delay_Netu(1);
		
//		if( CH == ESAM )
//		{
//			if( U7816PRIMARYSTATUS0&B0000_0010 )	//TX_FLAG置位
//			{
//				return 0; //成功
//			}
//                	
//			if( U7816PRIMARYSTATUS0&B0000_0100)	//ERROR_FLAG置位
//			{
////				switch( U7816ERRSTATUS ) //所有标志位: 硬件置位，写0清零
////				{
////					case B0000_0001: //接收溢出错误标志位
////						break;
//                	
////					case B0000_0010: //接收帧格式错误标志位
////						break;
//                	
////					case B0000_0100: //接收数据奇偶校验错误标志位
////						break;
//                	
////					case B0000_1000: //发送数据奇偶校验错误标志位
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
			if( U7816PRIMARYSTATUS0&B0000_0010 )	//TX_FLAG置位
			{
				return 0; //成功
			}
                	
			if( U7816PRIMARYSTATUS0&B0000_0100)	//ERROR_FLAG置位
			{
//				switch( U7816ERRSTATUS ) //所有标志位: 硬件置位，写0清零
//				{
//					case B0000_0001: //接收溢出错误标志位
//						break;
                	
//					case B0000_0010: //接收帧格式错误标志位
//						break;
                	
//					case B0000_0100: //接收数据奇偶校验错误标志位
//						break;
                	
//					case B0000_1000: //发送数据奇偶校验错误标志位
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
		Set_Reportdata(0*8+1);//置esam错误上报标志
	}
	
	esam_error = 1;
}

//command-response pairs
unsigned char CardTxRxFrame( unsigned char CH, uint08 Lc, uint08 Le )
{
	uint08 k, result, Temp_Data, Temp_SW1, Temp_SW2, Proc_Byte;

	Ic_Comm_RxPtr = 0x00;
	memset( Ic_Comm_RxBuf, 0x00, u7816_buf_size );
	Delay_Netu(10);	//再延时10个etu
	Err_Sw12[0] = 0;
	Err_Sw12[1] = 0;
	
//	if(CH == CARD)
//	{
//		result = RF_TxRxFrame(Lc, Le);
//		return (result);
//	}
	
	for( k=0; k<5; k++ )	//send command header (5bytes)
	{
		result = Snd_7816_Byte( CH, Ic_Comm_TxBuf[ k ] );	//;取待发送数据
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
				if( CH == ESAM ) Delay_Netu(16);	//接收到INS后与发送数据之间至少延时16个etu
				
				for( ; k<(Lc+5); )
				{
					result = Snd_7816_Byte( CH, Ic_Comm_TxBuf[ k++ ] ); //;取待发送数据
					if( result == 1 ) { return 3; }	//send failure.
				}
			}
			else
			{
				//;过程字节在之前已接收，只增加2个状态字节即可。
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
//				result = Snd_7816_Byte( CH, Ic_Comm_TxBuf[ k++ ] ); //;取待发送数据
//				if( result == 1 ) { return 5;}	//send failure.
//			}
//			else
//			{
//				//;过程字节在之前已接收，只增加2个状态字节即可。
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

//触点激活&冷复位
//检测到卡插入后, RST置低电平, VCC上电, 延时一段时间, IO设置为输入态, CLK输出时钟信号(T0时刻)
//在T0后40000~45000个CLK内, 将RST置为高电平(T1时刻), 在T1后的400~40000个CLK内, 复位应答应该开始, 
//若IC卡的复位应答没有在此时间段内开始, 终端将启动释放时序.若收到复位应答, 但不符合协议规范, 则需要热复位
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
		
		TicksDelayMs(100*clkmode,isPowerOff);		//延时100ms
		if(isPowerOff())return 2;
		
		U7816CTRL0 = DEF_USART0CTRL|DEF_USART0TX_EN|DEF_USART0RX_EN|DEF_USART0CLK_EN;	//U7816_1
		
		//----------------------------------------------------------------------------------------------
		Result = U7816RXBUF0; //RX启动后, 会产生rx_flag=1, 必须通过读取RXBUF来清除此标志.

		U7816ERRSTATUS0 = 0x0F;    //这三个寄存器的清零顺序很重要, 不能颠倒
		U7816SECONDSTATUS0 = 0x00;
		U7816PRIMARYSTATUS0 = 0x00;
//	}
//	else
//	{
//		U7816CTRL0 = DEF_USART0CTRL|DEF_USART0TX_EN|DEF_USART0RX_EN|DEF_USART0CLK_EN;;	//U7816_0
//		
//		//----------------------------------------------------------------------------------------------
//		Result = U7816RXBUF0; //RX启动后, 会产生rx_flag=1, 必须通过读取RXBUF来清除此标志.
//
//		U7816ERRSTATUS0 = 0x0F;    //这三个寄存器的清零顺序很重要, 不能颠倒
//		U7816SECONDSTATUS0 = 0x00;
//		U7816PRIMARYSTATUS0 = 0x00;
//		
//	}

	TicksDelayMs(5*clkmode,isPowerOff);			//等待RST时间,至少400周期,即100us
	if(isPowerOff())return 2;
	
	//-------- T1时刻, RST输出高电平 --------

	RST_ESAM_H;		//set PGIO4.3
	
	Result = Judge_Edge( CH ); 		//40000个CLK内查看IO口的电平沿变化
	if( Result == 0 ) //IO口没有出现下降沿
	{
		//if(CH == ESAM) Esam_Err_Report();
		return 2;	//异常: 40000个CLK中没有收到起始位
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

//ESAM复位
unsigned char EsamReset( void )
{
#if(ESAMON == 1)	
	unsigned char i;
	
	for(i=0; i<3; i++)
	{
		if( EA_OFF ) return(1);		//掉电不处理,程序直接返回
		
		if(ColdReset( ESAM )) 
		{
			CloseEsam();		//释放ESAM
			Delay_Initial(40);	//延时200ms		
		}
		else
		{
			esam_error = 0;
			memcpy( EsamRst8B, Ic_Comm_RxBuf+5, 8 ); //ESAM序列号, 8bytes.
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

//禁止ESAM工作
void CloseEsam( void )
{	
	RST_ESAM_L;	
	U7816CTRL0 = DEF_USART0CTRL;
	ESAMPOWEROFF;
	CloseeIO(GPIOG, GPIO_Pin_2);	//ESAMCLK
	CloseeIO(GPIOG, GPIO_Pin_3);	//ESAMIO
	CloseeIO(GPIOG, GPIO_Pin_7);	//ESAMRST
}


//复位ESAM
unsigned char Clear_Rand_Gene( void )
{
	unsigned char result;
	
	Identitytimer = 0x00;
	identity_prog_flag = 0;	//清除 安全认证编程标志
	first_prog_flag = 0;//清首次编程标志

	memset( PcRand,  0x00, 8 );
	memset( PcRst8B, 0x00, 8 );

	result = EsamReset();

	return (result);
}

//底层通讯
void RxTxCommhead( uint08 inc, uint08 com, uint08 P1, uint08 P2, uint08 len)
{
	Ic_Comm_TxBuf[ 0] = inc;
	Ic_Comm_TxBuf[ 1] = com;
	Ic_Comm_TxBuf[ 2] = P1;
	Ic_Comm_TxBuf[ 3] = P2;
	Ic_Comm_TxBuf[ 4] = len;
}

//读二进制文件
unsigned char ReadBinFile( unsigned char CH, unsigned char P1, unsigned char P2, unsigned char Len )
{
	unsigned char Result;

	RxTxCommhead(0, 0xb0, P1, P2, Len);
	
	Result = CardTxRxFrame( CH, 0x00, Len );
	
	return (Result);
}

//更新二进制文件
unsigned char UpdateBinFile( uint08 CH, uint08 P1, uint08 P2, uint08 Len )
{
	unsigned char Result;

	RxTxCommhead(0, 0xD6, P1, P2, Len);
	
	memcpy(&Ic_Comm_TxBuf[5], Ic_Comm_RxBuf, Len);
				
	Result = CardTxRxFrame( CH, Len, 0x00 ); //CARD Com
	
	return (Result);
}

//读记录文件
unsigned char ReadRecFile( unsigned char P1 )
{
	unsigned char Result;

	RxTxCommhead(0, 0xb2, P1, 0x14, 0x04);
	
	Result = CardTxRxFrame( ESAM, 0x00, 0x04 );

	return (Result);
}

//取响应数据
unsigned char Read_Kx( unsigned char CH, unsigned char Len )
{
	unsigned char result;

	RxTxCommhead(0, 0xC0, 0, 0, Len);
	
	result = CardTxRxFrame( CH, 0x00, Len ); //Esam Com

	return (result);
}

//取随机数
unsigned char ReadRandom( unsigned char CH, unsigned char Len )
{
	unsigned char result;
	
	RxTxCommhead(0, 0x84, 0, 0, Len);
	
	result = CardTxRxFrame( CH, 0x00, Len );
	
	if( result == 0 )
	{
		if(CH == ESAM)	//取ESAM随机数
		{
			memcpy(EsamRand, Ic_Comm_RxBuf, Len);
		}
//		else		//取卡片随机数
//		{
//			memcpy(CardRand, Ic_Comm_RxBuf, Len);
//		}
	}
	
	return (result);
}

//加密，内部和外部认证命令
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

	RxTxCommhead(0x80, 0xfa, 1, P2, Len);		//程序对比：MAC计算
	memcpy(&Ic_Comm_TxBuf[5],BufA, Len);	

	Result = CardTxRxFrame( ESAM, Len, 0x00 ); 	//CARD Com
	if(Result) return 1;
	
	Result = Read_Kx( ESAM, 64 );			//取ESAM加密结果
	return (Result);
}


//由带MAC抄读命令中的M2选组
const uint08 code ConstIns[12] =
	{ 
		0x04, 0xd6, 0x86,	//正常带MAC读卡(0x86为带MAC读ESAM用)
		0x84, 0x32, 0x01,	//用户卡读钱包文件
		0x04, 0xdc, 0x01,	//预制卡读剩余金额
		0x04, 0xdc, 0x03,	//预制卡读购电次数
	};


//=====带MAC读取二进制文件
//Le：带MAC读命令的数据长度
unsigned char ReadBinWithMac( uint08 CH, uint08 P1, uint08 P2, uint08 Le )
{
	unsigned char result, Temp, Type;
	
	RxTxCommhead(0x04, 0xB0, P1, P2, 0x11);
	Clear_Wdt();
	
	Type = (CH&B1111_0000)>>4;
	if( (CH&B0000_1111) == CARD )	//对CARD操作
	{
		Ic_Comm_TxBuf[4] = 9;
		memcpy(Ic_Comm_TxBuf+5, EsamRand, 4);//对卡片操作，取ESAM随机数
		
		memcpy( Ic_Comm_TxBuf+9, ConstIns+Type*3, 3 );
		if( Type == 0 )
		{
			Ic_Comm_TxBuf[11] = P1;	//带MAC读卡片参数，文件号和偏移地址同ESAM
			if( P1==0x85 ) Ic_Comm_TxBuf[11] = 0x87;//合闸复电命令
			Ic_Comm_TxBuf[12] = P2;
		}
		else
		{
			Ic_Comm_TxBuf[12] = 0x14;
		}
		Temp = Le;	//卡片直接返回数据，不需取数
	}
	else//对ESAM操作
	{
//		if( Comm_Auth_Judge() )//远程带mac读
			memcpy(Ic_Comm_TxBuf+5, PcRand, 4);
//		else
//			memcpy(Ic_Comm_TxBuf+5, CardRand, 4);

		memcpy( Ic_Comm_TxBuf+9, ConstIns, 3 );
		
		Ic_Comm_TxBuf[12] = P2;
		if( P1<0x04 )
		{
			Ic_Comm_TxBuf[ 1] = 0xB2;	//带MAC读钱包，命令字0xB2
			Ic_Comm_TxBuf[12] = 0x00;
		}
		
//		if(CH == ESAM)
//			memcpy(Ic_Comm_TxBuf+14, CardRst8B, 8);
//		else
			memcpy(Ic_Comm_TxBuf+14, PcRst8B, 8);
		
		Temp = 0;
	}
	Ic_Comm_TxBuf[13] = Le;
	if(CH == ESAM+0x10) Ic_Comm_TxBuf[13] += 8;	//数据回抄和状态查询需+8字节
	
	CH &= B0000_0001;
	result = CardTxRxFrame( CH, Ic_Comm_TxBuf[4], Temp );//返回data+MAC
	if( result ) return (result);
	
	if(CH == ESAM)
	{
		result = Read_Kx(ESAM, Le ); //返回data+MAC
	}

	return ( result );
}

//======带MAC更新二进制文件
unsigned char WriteBinWithMac( uint08 CH, unsigned char P1, unsigned char P2, unsigned char Len )
{
	unsigned char  Result;

	RxTxCommhead(0x04, 0xd6, P1, P2, Len);
	if(CH>1) Ic_Comm_TxBuf[1] = 0xdc;		//带MAC写钱包文件
	if(Len == 4) Ic_Comm_TxBuf[ 0 ] = 0;//CLA 不带MAC
	CH &= B0000_0001;

	memcpy(&Ic_Comm_TxBuf[5], Ic_Comm_RxBuf, Len);

	Result = CardTxRxFrame( CH, Len, 0x00 ); //CARD Com

	if( Result )
	{
		if( (Err_Sw12[0] == 0x69) && (Err_Sw12[1] == 0x88) ) return(IC_MAC_ERR);//MAC校验错误(6988)
		else if(CH == ESAM) return(IC_ESAM_RDWR_ERR);
		else return(IC_NOIN_ERR);
	}
	return(Result);
}


unsigned char Authorization( unsigned char *Buf, unsigned char Len )
{
	unsigned char Result;

	//电能表对ESAM操作命令详解：
	//a）密钥分散命令：80fa000108+8字节分散因子；
	//;Esam encryp random data.
	Result = Auth_In_Out(0xfa, ESAM, 0x03, Buf+16 );
	if( Result != 0x00 )	return 1;
	
	//b）加密随机数命令：80fa000008+随机数；
	Result = Auth_In_Out(0xfa, ESAM, 0x00, Buf+8 );
	if( Result != 0x00 )	return 1;
	
	//c）取密文命令：00c0000008；
	//比较密文1和密文2, 两者不相等则报警, 相等则继续下面操作
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

	//取随机数2：0084000004
	//;Read random in ESAM
	Result = ReadRandom( ESAM, Len );
	return ( Result );
}


//选择文件
unsigned char SelectFile( unsigned char CH, unsigned char F1, unsigned char F2 )
{
	unsigned char Result;
	
	RxTxCommhead(0,0xa4, 0, 0, 2);	
	Ic_Comm_TxBuf[ 5 ] = F1;	//DATA0
	Ic_Comm_TxBuf[ 6 ] = F2;	//DATA1
	
	Result = CardTxRxFrame( CH, 0x02, 8 );	//返回8字节
	
	return (Result);
}


//判断卡片数据格式
unsigned char JudgeFile(unsigned char Len)
{
	unsigned char Csdata;

	Csdata = Cal_ChkSum(Ic_Comm_RxBuf+1, Len+3);
	if( (Ic_Comm_RxBuf[0] != 0x68) || (Ic_Comm_RxBuf[Len+4] != Csdata) || (Ic_Comm_RxBuf[Len+5] != 0x16) ) return 1;//帧格式错误: 68H/CS/16H
	return 0;
}


//比较表号是否相同
unsigned char Cmp_Meter_Id(unsigned char *Buf)
{
	if ( Cmp_Data( Esam_Para.Meter_Id, Buf, 6) != 3 ) return 1;
	return 0;
}


//下面是远程费控的程序
//MAC校验结果处理函数
//累计MAC失败100次挂起
void Mac_Err_Proc( void )
{
	if(Mac_Err_Times < 200) Mac_Err_Times++;
	if(Mac_Err_Times >= 200)
	{
		Mac_Err_Times = 0x00;	//清零
		hangup_comm_flag = 1;	//要求电能表远程设置参数功能挂起
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
		Mac_Err_Proc();	//mac错误次数加1
	}
	
	return (result);
}


//同步更新esam运行信息文件
void UpdataRunFile(void)
{
	unsigned char Buf[60];
	
	ReadBinFile( ESAM, 0x86, 0, 50 );	//读全部06文件
	memcpy( Buf, Ic_Comm_RxBuf, 50 );	//06文件数据备份
	
	Ic_Comm_RxBuf[0] = 0x68;
	Ic_Comm_RxBuf[1] = 0x11;							//用户卡返写
	Ic_Comm_RxBuf[2] = 0x00;
	Ic_Comm_RxBuf[3] = 0x2c;
	
//	Bcd2Hex( Money.Remain, Ic_Comm_RxBuf+23, 4);		//剩余金额
//	memcpy( Ic_Comm_RxBuf+27, Money.Buy_Times.B08, 4 );	//购电次数
//	memcpy( Ic_Comm_RxBuf+31, Money.Tick, 4 );					//透支(BCD)	
//	
//	Save_Keep_Timer(0);
//	Hex2Bcd( Eeprom.Buffer+1, Ic_Comm_RxBuf+39, 3 ); 	//非法卡交互次数 3 BCD
		
	memcpy( Ic_Comm_RxBuf+5, Esam_Para.Current_Ratio,18 );//变比1+变比2+表号+客户编号
//	Ic_Comm_RxBuf[47] = Display_Para.MeterCtrl;	//电表模式字
	
	if( (Cmp_Data( Ic_Comm_RxBuf, Buf, 48) != 3) )
	{
		Exchange( Ic_Comm_RxBuf+42, Sclock.Clockbackup+1, 5 );//分时日月年
		//更新CS
		Ic_Comm_RxBuf[48] = Cal_ChkSum(Ic_Comm_RxBuf+1, 47);
		Ic_Comm_RxBuf[49] = 0x16;
		
		UpdateBinFile(ESAM, 0x86, 0, 50 );
	}
}

unsigned char GetPswBit( unsigned char *InBuf )
{
	unsigned char i, n, Temp08;

	Temp08 = Feik.Num[7];
	if( Temp08 > MAX_PSW_NUM ) Temp08 = MAX_PSW_NUM;	//密钥总条数非法默认

	for( i=0; i<Temp08; i++ )	//表内允许设置的密钥总条数.
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

//读密钥状态字
void GetKey( unsigned char *KeyStatus )
{
	I2C_Read_Eeprom44( ee_keystatus_page, KeyStatus, ee_keystatus_lenth );
}

//写密钥状态字
void SetKey( unsigned char *KeyStatus )
{
	I2C_Write_Eeprom44( ee_keystatus_page, KeyStatus, ee_keystatus_lenth );
	GetKeyStatus();
}

//读当前密钥状态
void GetKeyStatus()
{
#if(ESAMON == 1)	
	unsigned char Buf[32];
	
	GetKey( Buf ); //读密钥状态
	Key_Status = GetPswBit( Buf );
#else
	Key_Status = 0;//默认公钥
#endif	
}


unsigned char GetSetBitNum( unsigned char *InBuf )
{
	unsigned char i, k, n;

	for( i=0, k=0; i<MAX_PSW_NUM; i++ )	//统计已下载的密钥总条数
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
	
	//FramePswNum:  命令帧中包含的密钥条数.
	//MeterPswNum:  表内允许设置的密钥总条数.
	//SettedPswNum: 已下载的密钥总条数(不包含重复更新的密钥)
	FramePswNum = (Uart[Ch].Buf[9]-8-4)/36;
	if( (FramePswNum==0) || (FramePswNum>4) || ((Uart[Ch].Buf[9]-8-4)%36) ) return 1;

	MeterPswNum = Feik.Num[7];
	if( MeterPswNum > MAX_PSW_NUM ) MeterPswNum = MAX_PSW_NUM;	//密钥总条数非法默认

	//ee_keystatus_page: 
	//密钥状态字(4)  : 符合国网规定的“密钥状态字”。
	//密钥状态(1)    : (预留)
	//更新状态(1)    : 密钥更新的过程状态 (00启动写E2PROM, 55启动写ESAM, AA更新完成).
	//更新到E2PROM(4): 按照国网规定的“密钥状态字”格式，每更新一条到E2PROM 对应bit置1.
	//更新到ESAM(4)  : 按照国网规定的“密钥状态字”格式，每更新一条到ESAM 对应bit置1.(预留)
	//新密钥状态字(4): 按照国网规定的“密钥状态字”格式，0为公钥，1为私钥。
	//ee_keystatus1_page:
	//操作者代码(4)  : 更新记录中的操作者代码是电表收到第一条密钥更新命令中的操作者代码.
	//密钥更新的总条数(1) HH
	//更新前密钥状态字(4):
	GetKey( ChangeBuf );
	if( ChangeBuf[5] == 0x55 )return 0; //更新状态: 00已启动更新E2PROM; 55已启动更新ESAM; AA已更新结算.
	if( ChangeBuf[5] != 0x00 ) //结束更新密钥
	{
//		ChangeBuf[4] &= 0x3F;	//清除Bit7和Bit6。
		ChangeBuf[5] = 0x00;	//只有更新结束才允许新一轮的更新。
		memset( ChangeBuf+6, 0x00, 12 ); //清空更新的标志位。
		
		memcpy( Eeprom.Buffer, Uart[Ch].Buf+14, 4 );	//操作者代码
		Eeprom.Buffer[4] = MeterPswNum;	//密钥更新的总条数(1) HH
		memcpy( Eeprom.Buffer+5, ChangeBuf, 4 );	//更新前的密钥状态字
		I2C_Write_Eeprom( ee_keystatus1_page, ee_keystatus1_inpage, Eeprom.Buffer, ee_keystatus1_lenth ); 
	}

	memcpy( Buf, Uart[Ch].Buf+18, 36 );
//	for( i=1; i<FramePswNum; i++ ) Xor_Data( Buf, Uart[Ch].Buf+18+i*36, 36 );

	//有效的密钥条数
	for( i=0, k=0; i<FramePswNum; i++, k+=36 )
	{
		if(i) Xor_Data( Buf, Uart[Ch].Buf+18+k, 36 );
		
		//密钥总条数+预留+密钥编号+密钥状态
		if((Uart[Ch].Buf[18+32+k] > 0x01) //密钥状态标志位（00-测试状态，01-正式状态）
		 ||(Uart[Ch].Buf[18+32+k] != Uart[Ch].Buf[18+32+0]) ) return 1; //错误应答: 报文出现密钥状态标志位不一致
		if( Uart[Ch].Buf[18+33+k] >= MeterPswNum ) return 1;	//密钥编号超限.
		if( Uart[Ch].Buf[18+35+k] != MeterPswNum ) return 1;	//错误应答: 报文中的密钥总条数与参数表中密钥总条数不一致.

		ChangeBuf[6+Uart[Ch].Buf[18+33+k]/8] |= (1<<(Uart[Ch].Buf[18+33+k]%8));	//记录下载密钥情况.
		
		if( Uart[Ch].Buf[18+32+k] )
			ChangeBuf[14+Uart[Ch].Buf[18+33+k]/8] |= (1<<(Uart[Ch].Buf[18+33+k]%8));
		else
			ChangeBuf[14+Uart[Ch].Buf[18+33+k]/8] &= ~(1<<(Uart[Ch].Buf[18+33+k]%8));
	}

//	memset( Buf+36, 0x00, 8 );
//	if( (Uart[Ch].Buf[18+32+0]&0x7F) == 0x00 )	Buf[36] = 0x01; //密钥恢复时固定为01
//	else	Exchange( Buf+36, Esam_Para.Meter_Id, 6 );	//密钥下装时取表号
	Exchange( Buf+36, Esam_Para.Meter_Id, 6 );	//密钥下装时取表号
	Buf[42] = 0x00;
	Buf[43] = 0x00;
	memcpy( Buf+44, Uart[Ch].Buf+10+Uart[Ch].Buf[9]-4, 4 ); //MAC
	
	result = Update_ESAM_Bin_Mac( 0x95, 0x00, Buf, 44 );	//
	if( result != 0x00 ) return 4;	//当传输的数据MAC 校验错是采用错误信息字ERR 中bit2（密码错/未授权）置位，并按照异常应答帧响应。
	
	SettedPswNum = GetSetBitNum( ChangeBuf+6 ); //统计已下载的密钥总条数
	if( SettedPswNum == MeterPswNum ) //更新的密钥条数达到总条数
	{
		result = GetPswBit( ChangeBuf+14 );
		if( result != 0xFF ) 	//判断密钥状态是否一致
		{
			ChangeBuf[5] = 0x55; //设置启动更新ESAM标志
		}
	}
	else if( SettedPswNum > MeterPswNum ) return 1;	//错误应答：下载的有效密钥条数>表内密钥总条数

	for( i=0, k=0; i<FramePswNum; i++, k+=36 )
	{
		Inverse( Uart[Ch].Buf+18+k, 32 );	//只倒序密钥
		I2C_Write_Eeprom( ee_keydata_1_page+Uart[Ch].Buf[18+33+k]/2, 32*(Uart[Ch].Buf[18+33+k]%2), Uart[Ch].Buf+18+k, 32 );
	}

	SetKey( ChangeBuf ); //首先记录下密钥写入E2PROM的情况.

	return 0;
}


//检测是否有密钥需更新到ESAM，有则更新。
unsigned char UpdateEsamKey( void )
//函数返回: 当前电表密钥状态
{
	unsigned char i, k, n, result, key, Bkmain;
	unsigned char TmpBuf[32];
	
	GetKey( TmpBuf );
	if( TmpBuf[5] == 0x55 ) //更新状态: 00已启动更新E2PROM; 55已启动更新ESAM; AA已更新结算.
	{
		key = GetPswBit( TmpBuf+14 );
		for( i=0; i<MAX_PSW_NUM; i++ )
		{
			
			if( (i%8) == 0 ) k = 1;
			else k <<= 1;
			
			if( (TmpBuf[6+i/8]&k)  )
			{
				//启动更新ESAM指令
				for( n=0; n<3; n++ )
				{
					if( i == 0x00 )
						RxTxCommhead(0x84, 0xd4, 1, 0x00, 0x20); //主控密钥密文
					else
						RxTxCommhead(0x84, 0xd4, 1, 0xff, 0x20); //其他密钥密文

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
					
					if( ( i == 0 )&&( result == 0 ) ) Bkmain = TmpBuf[0]; 	//成功更新主控密钥
				}
				else
				{
					if( EA_OFF ) return 0x00; 	//更新过程中出现停电,上电从密钥编号为0的密钥开始对ESAM重新进行密钥更新
					break;				//更新失败,不再对本条密钥之后的密钥进行更新
				}
			}
		}
		
//		if( i == MAX_PSW_NUM )
//		{			
			key = GetPswBit( TmpBuf);
			
			if( key == 0xFF )	
			{
				if( (Bkmain & 0x01) == 0 ) TmpBuf[0] &= 0xFE;		//更新失败,恢复主控状态
				else TmpBuf[0] |= 1;
			}
			
			TmpBuf[5] = 0xAA;	//全部更新完毕
//		}

		for( n=0; n<3; n++ )
		{
			Exchange( Ic_Comm_RxBuf, TmpBuf, 4 );//复制4字节密钥状态
			result = UpdateBinFile( ESAM, 0x85, 0x00, 4 );	//写esam的05文件
			if( result == 0x00 ) break;
			if( EA_OFF ) return 0x00; 
		}
		
		SetKey( TmpBuf ); //首先记录下密钥写入E2PROM的情况.
		
		//--- 密钥更新记录 ---
		I2C_Read_Eeprom( ee_keystatus1_page, ee_keystatus1_inpage, Eeprom.Buffer+6, ee_keystatus1_lenth ); 
		Event_Record( ee_keysetn_inpage );
		//--- 密钥更新记录 end---
	}

	return 0x00;
}


void FailKey( void )
{
	unsigned char Buf[64];

	GetKey( Buf );
	if( Buf[5] != 0xAA )
	{
		memset( Buf+4, 0x00, ee_keystatus_lenth-4 ); //清空更新的标志位。
		Buf[5] = 0xAA;
		SetKey( Buf );
	}
}


//电表清零
void Clear_Meter( unsigned char Ch, unsigned char *Opt )
{
	unsigned char i;
	
	Clear_Wdt();
		
	ClrRecTimes( 0, 0xaa );//清冻结和事件有效指针(除清零记录)
	
	//状态字,密码相关和负荷记录指针清零
	memset( &System_St_Bk, 0x00, ee_reportdata_lenth );
	memset( Load.Point, 0x00, sizeof(Load) );
	memset( Eeprom.Buffer, 0, 64 );
	I2C_Write_Eeprom( ee_validnum_page, ee_validnum_inpage, Eeprom.Buffer, ee_validnum_len ); //清除分钟冻结有效次数页
	
	//清零点清零数据
	Clr_Zero_Data();
	
	//电表清零时要清除远程拉闸、远程报警状态，不清除保电状态
	if( Relay_Mode == 0x55 )//外置继电器
	{
		relay_cleardl_flag = 1;	//置外置表清零标志
	}
	relay_commu_alarm_flag = 0;
	
	Clr_Commu_Relaydata();
	Store_Meterstatus();
	
	//清结算用电量/上月用电量/上1~4年用电量
	Process_Usedl(3);
	Process_Usedl(4);
	Process_Usedl(5);

	//记录清电表事件
	//清零事件记录：发生时刻(6)+操作者代码(4)+电表清零前正向有功(4)+电表清零前反向(4)	
	//存储各项数据时倒序，低字节在前，高字节在后
		
	memcpy( Eeprom.Buffer+6, Opt, 4 );	//操作者代码(4),远程清零
	
	DltoEepromBuf( 10 );
	Four_RpdltoEepromBuf( 18 );
	Event_Record( ee_clearn_inpage );

	//清 XRAM和E2电量
	Veri_Btmr1_Pcount(1);		//清脉冲尾数
	Veri_Btmr2_Pcount(1);		//清脉冲尾数
	
	memset( Fwdl.Pluse[0].B08, 0x00, ee_fwdl_lenth+2 );		//清正向电量
	WriteE2WithBackup( ee_fwdl_page, ee_fwdl_inpage, Fwdl.Pluse[0].B08, ee_fwdl_lenth );

	memset( Bkdl.Pluse[0].B08, 0x00, ee_bkdl_lenth+2 );		//清反向电量
	WriteE2WithBackup( ee_bkdl_page, ee_bkdl_inpage, Bkdl.Pluse[0].B08, ee_bkdl_lenth );
	
	for(i=0; i<4; i++)
	{
		memset( Rpdl[i].Pluse[0].B08, 0x00, ee_rpdl_lenth+2 );	//清四象限无功电量
		WriteE2WithBackup( ee_rpdl_page+2*i, ee_rpdl_inpage, Rpdl[i].Pluse[0].B08, ee_rpdl_lenth );
	}
	
	//清显示结算日电量缓冲区和冻结通讯缓冲区
	memset( FreezeBuf, 0x00, sizeof(FreezeBuf) );
//	memset( Freeze_Commbuf, 0x00, sizeof(Freeze_Commbuf) );
	Display_Para.Dl_Dot_Auto = 0;	//清电量自适应显示小数位数
	run_price_flag = 1;		//电量清零重新判断阶梯值
	
	Mt_Alarmstatus_Judge();
	if( relay_status_flag ) ClrRecTimes( ee_openrelayn_inpage, 0x01 );//清拉闸记录
	else ClrRecTimes( ee_closerelayn_inpage, 0x01 );//清合闸记录
	
	Wr_Powerdown_Data(0);//写掉电相关数据到数据ee
	Wr_Pretime_Hisfreeze();	//写上一次结算时间
	Wr_Pretime_Dayfreeze();	//写上一次日冻结时间
	
#if(1 == CHINT_Mode)
	if( progenable )/*厂内模式下全部清零*/
	{
		ClrRecTimes( 0, 0xff );//清冻结和事件有效指针(包括清零记录)
	}
#endif
}

void Factory_Init( void )
{
	unsigned char i, len;
	unsigned char Buf[72];
	
	//清有效指针页
	ClrRecTimes( 0, 0xff );//清冻结和事件有效指针
	
	//初始化软件备案号和生产日期
	Exchange( Buf, (uint08*)Softbk, ee_softbk_lenth );	
	I2C_Write_Eeprom( ee_softbk_page, ee_softbk_inpage, Buf, ee_softbk_lenth );
	Exchange( Buf, (uint08*)Facdate, ee_meterdate_lenth );	
	I2C_Write_Eeprom( ee_meterdate_page, ee_meterdate_inpage, Buf, ee_meterdate_lenth );
	
	//晶振停振, 复位次数, hardfault复位时间和次数页
	Clear_Wdt();
	memset( Buf, 0x00, 64 );
	for( i=0; i<3; i++ )
	{
		I2C_Write_Eeprom44( ee_xtlfstop_time_page+i, Buf, 18 );
	}
	Wr_Ext_Number = 0;//清扩展命令允许写ee次数
	
	memset( (uint08*)SynFlash.HisRec, 0, ee_synflash_len );
	I2C_Write_Eeprom( ee_synflash_page, ee_synflash_inpage, (uint08*)SynFlash.HisRec, ee_synflash_len );
	
	relay_commu_close_flag = 0;//默认保电解除状态
	Store_Meterstatus();
	
	//初始化电能表位置信息
	I2C_Write_Eeprom( ee_meterpos_page, ee_meterpos_inpage, Buf, ee_meterpos_lenth );	
		
	//第1~60公共假日日期及日时段表号: 00000000
	for( i=0; i<4; i++ )
	{
		I2C_Write_Eeprom( ee_holiday_page+i, 0x00, Buf, ee_holiday_lenth );
	}
	
	//清蓝牙参数
	I2C_Write_Eeprom(ee_bleslamac_page, ee_bleslamac_inpage, Buf, ee_bleslamac_lenth);
	I2C_Write_Eeprom(ee_blerefer_page, ee_blerefer_inpage, Buf, ee_blerefer_lenth);
	Buf[0] = 0x40;//蓝牙广播时间
	I2C_Write_Eeprom(ee_blerefer_page, ee_blegbtime_inpage, Buf, ee_blegbtime_lenth);
	
	//密码初始化
	WriteE2WithBackup( ee_password_page, ee_password_inpage, (uint08*)Def_Password3_table, ee_password_lenth );
	WriteE2WithBackup( ee_password_page, ee_password4_inpage, (uint08*)Def_Password4_table, ee_password_lenth );
		
	//变比,表号等(双备份)
	ReadE2WithBackup( ee_esampara_page, ee_esampara_inpage, Buf, ee_esampara_lenth );
	if( IsMultiBcd( Buf, 6 ) )//非法数据
	{
		memset( Buf, 0x00, 6 );	//变比(6)
		Buf[2] = 0x01;//电流变比1
		Buf[5] = 0x01;//电压变比1
	}
//	memset( Buf+6, 0x00, 6 );	//表号(6),表号不初始化
//	Buf[11] = 0x01;//表号0x000000000001
	memset( Buf+12, 0x00, 6 );	//客户编号(6)
	memset( Buf+18, 0xff, 6 );	//模块id(6)
	Buf[24] = Defaultauthtimer>>8;//身份认证有效时长
	Buf[25] = Defaultauthtimer;
	WriteE2WithBackup( ee_esampara_page, ee_esampara_inpage, Buf, ee_esampara_lenth );
	memcpy( Esam_Para.Current_Ratio, Buf, ee_esampara_lenth+2 );
//	I2C_Write_Eeprom( ee_zbid_bk_page, ee_zbid_bk_inpage, Buf+18, ee_zbid_bk_lenth ); //写原载波id备份(通讯抄读专用)
	
	//显示参数(双备份)
	WriteE2WithBackup( ee_displaypara_page, ee_displaypara_inpage, (uint08*)Def_DisplayPara_table, ee_displaypara_lenth );
	memcpy( &Display_Para.S_Number, Def_DisplayPara_table, ee_displaypara_lenth );
	
	//切换时间(双备份)
	memset( Starttime.Shiqu, Defaultstartup, ee_starttimer_lenth );
	WriteE2WithBackup( ee_starttimer_page, ee_starttimer_inpage, Starttime.Shiqu, ee_starttimer_lenth );
	memset( Buf, 0xff, ee_changecontrol_lenth );	//时区时段均使用第一套
	I2C_Write_Eeprom44( ee_changecontrol_page, Buf, ee_changecontrol_lenth );
	run_timezone_flag = 1;
	
	//特征模式字(双备份)
//	memcpy( Buf, Def_featureword_table, ee_featureword_lenth );
////	Buf[0] = Mode.Bps[0]; //保留BPS
//	if( Extbattery == 0x55 ) Buf[ee_featureword_lenth-2] &= B1111_1101; //外置表欠压关闭背光
	WriteE2WithBackup( ee_featureword_page, ee_featureword_inpage, (uint08*)Def_featureword_table, ee_featureword_lenth );
	memcpy( Mode.Bps, Def_featureword_table, ee_featureword_lenth );
	mode_veri_flag = 1;	
	reg_veri_flag = 1;
			
	//周休日和负荷参数(双备份)
	WriteE2WithBackup( ee_weekholiday_page, ee_weekholiday_inpage, (uint08*)Def_weekloadpara_table, ee_weekholiday_lenth );
	memcpy( &Week_Holiday.Status, Def_weekloadpara_table, ee_weekholiday_lenth );
	
	//费控数
	WriteE2WithBackup( ee_feik_number_page, ee_feiknumber_inpage, (uint08*)Def_feik_table, ee_feiknumber_lenth );
	memcpy( Feik.Num, Def_feik_table, ee_feiknumber_lenth );

	//结算日
	WriteE2WithBackup( ee_histroyparameter_page, ee_histroyparameter_inpage, (uint08*)Def_histroyparameter_table, ee_histroyparameter_lenth );
	
	//冻结参数
	I2C_Write_Eeprom44( ee_freezeparameter_page, (uint08*)Def_freezeparameter_table, ee_freezeparameter_lenth );
	
	//电压合格率等相关参数
	memcpy( VolLimit.MaxVolLmt.B08, Def_vollmtpara_table, ee_vollimit_lenth );
	WriteE2WithBackup( ee_vollimit_page, ee_vollimit_inpage, VolLimit.MaxVolLmt.B08, ee_vollimit_lenth );

	Clear_Wdt();
		
	//第一套，第二套时区表数据
	I2C_Write_Eeprom( ee_shiqu1_page, 0x00, (uint08*)Def_sqb_table1, ee_shiqu_lenth );
	I2C_Write_Eeprom( ee_shiqu2_page, 0x00, (uint08*)Def_sqb_table2, ee_shiqu_lenth );
	
	//第一套，第二套 所有8个日时段表
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
	
	//自动循环显示项目列表
	for( i=0; i<31; i++ ){Buf[i*2+0] = 0x01; Buf[i*2+1] = 0x02;} //512+1(0x201)表示普通组合电量  1024+1(0x401)表示高精度组合电量
	for( i=0; i<4; i++ )
	{
		if( i != 3 ) len = ee_displayitem_lenth;
		else len = ee_displayitem_lenth1;
		I2C_Write_Eeprom( ee_loop_displayitem_page+2*i, 0x00, Buf, len ); //循环显示序号
		I2C_Write_Eeprom( ee_loop_displayitem_page+2*i+1, 0x00, Buf, len ); //按键显示序号
	}
	
	I2C_Write_Eeprom( ee_loop_displayitem_page, 0x00, (unsigned char*)Def_Autodisp_table, ee_displayitem_lenth );//初始化循环显示序号
	I2C_Write_Eeprom( ee_key_displayitem_page, 0x00, (unsigned char*)Def_Keydisp_table, ee_displayitem_lenth );//初始化按键显示序号
	I2C_Write_Eeprom( ee_key_displayitem_page+2, 0x00, (unsigned char*)Def_Keydisp_table+ee_displayitem_lenth, ee_displayitem_lenth );//初始化按键显示序号
	
	for( i=0; i<2; i++ ) Item[i].Crc16.B08[0] += 1;
	dispitem_veri_flag = 1;
	
	//当前/备用套阶梯时区表
	I2C_Write_Eeprom( ee_jtshiqu1_page, ee_jtshiqu_inpage, (uint08*)Def_jtshiqu_table, ee_jtshiqu_len );
	I2C_Write_Eeprom( ee_jtshiqu2_page, ee_jtshiqu_inpage, (uint08*)Def_jtshiqu_table2, ee_jtshiqu_len );

	//当前/备用套阶梯表
	Clear_Wdt();
	memset(Buf, 0x00, 72);
	if( Crc_Check( Price.Ladder_Dl[0].B08, ee_ladder_lenth+2 ) ) 
	{
		for(i=0; i<8; i++) I2C_Write_Eeprom( ee_ladder1_page+i, 0, Buf, ee_ladder_lenth+2 );
	}
	
	//初始化温度系数
	Temperpara_Verify();	//校验数据合法性
	WriteE2WithBackup( ee_temperature_page, ee_temperature_inpage, Tpara.Offset, ee_temperature_lenth); 
	
//	(*( void (*)( ) )0xFF0000) ();	//软复位
										
}
