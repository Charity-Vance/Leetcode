#include "ex_var.h"
#include "ex_func.h"
#include <string.h>
#include "FM32L0XX.h"  
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Cpu_card.h"

extern int __heap_limit;


#define	MAXREGION	14		//年时区数最大值, 可设
#define	MAXSIDUANTB	8		//时段表数最大值, 可设
#define	MAXSIDUAN	max_shiduancount//时段数最大值, 可设
#define	MAXHOLIDAY	max_maxholiday	//公共假日数最大值, 可设
#define SCREENNUM	99		//本地费控表

//地址范围:PROGRAMSTA1~PROGRAMEND1
#define PROGRAMSTA1	0x000000	//程序空间1起始地址
#ifdef __A03
#define PROGRAMEND1	0x02FFFF	//程序空间1结束地址
#define PROGRAMPROZ	0x02F800	//程序保护区起始地址
#endif
#ifdef __A04
#define PROGRAMEND1	0x03FFFF	//程序空间1结束地址
#define PROGRAMPROZ	0x03F800	//程序保护区起始地址
#endif
#ifdef __A05
#define PROGRAMEND1	0x05FFFF	//程序空间1结束地址
#define PROGRAMPROZ	0x05F800	//程序保护区起始地址
#endif
#ifdef __A06
#define PROGRAMEND1	0x07FFFF	//程序空间1结束地址
#define PROGRAMPROZ	0x07F800	//程序保护区起始地址
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


void Calculate_Program_Cs( unsigned char *Buf )//计算程序累加和	NNNNNNNN	4
{
	unsigned long int ecode *Code_Flash_Char;
	union B32_B08_2 Temp32;
		
	Temp32.B32 = 0;
	
	if( progenable )	//厂内模式才会计算
	{
		Clear_Wdt();
		for( Code_Flash_Char=(unsigned long int ecode *)PROGRAMSTA1; Code_Flash_Char<(unsigned long int ecode *)(PROGRAMEND1+1); Code_Flash_Char++ )	//4M下执行时间约280ms
		{
			Temp32.B32 += *Code_Flash_Char;
		}
	}
	Inverse( Temp32.B08, 4 );
	Hex2Bcd( Temp32.B08, Buf, 4 );	//转换成bcd码,方便显示
}


//Offset从0~3,分别为拉闸延时,大电流拉闸延时,红外认证时间,上报自动复位时间
/*BCD码的分钟定时，转换到hex的秒定时计算
offset：
		0：通讯拉闸延时			2字节，min
		1：大电流拉闸延时		2字节，min（南网无）
		2：红外认证时间			1字节，min
		3：上报自动复位时间	1字节，min
 0xff：远程身份认证时效 2字节，min
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
		Bcd2Hex( Esam_Para.Identity_Delay.B08, Temp32.B08+2, 2 );	//计算身份认证时效
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
	
	return( Byte2uInt(Temp32.B08)*60 );//延时时间分钟转换成秒
}

	
void Clr_Commu_Relaydata()
{
	Opendelaytimer = 0;
	relay_commu_open_flag = 0;	//清通讯拉闸标志
	relay_commu_disable_close_flag = 0;
	relay_commu_close2_flag = 0;	//清保电解除标志
}


void Clr_Reportnum( unsigned char i ) //清零上报新增次数
{
	unsigned char Temp08;
	
	for( Temp08=0; Temp08<8; Temp08++ )//根据上报状态字清零上报新增次数
	{
		if( (Report_Data[i]&(1<<Temp08))==0 ) Report_Num[i*8+Temp08] = 0;
	}
}

void Clr_Reportdata( unsigned char i ) //清上报状态字和新增次数(有事件记录类)
{
	unsigned char Temp08;
	
	Temp08 = EventTable[i-ee_clearn_inpage].offset2;
	if( Temp08 != 0xff )
	{	
		Report_Data[Temp08/8] &= ~(1<<(Temp08%8));	//清上报状态字
		Report_Num[Temp08] = 0;	//清新增次数
	}
}

//置位上报状态字和新增次数加1
void Set_Reportdata( unsigned char Offset ) 
{
	unsigned char byt,bt,i,j;
	
	if( Offset == 0xff ) return;
	
	byt = Offset/8;
	bt = Offset%8;
	
	//修正上报模式字
	if( (byt==2)&&(bt==7) )
	{
		i = 4; j = 5; //掉电临时借用存A相断相
	}
	else if( (byt==2)&&(bt==2) )
	{
		i = 3; j = 5; //低电压临时借用存A相欠压
	}
	else if( (byt==2)&&(bt==1) )
	{
		i = 3; j = 4; //高电压临时借用存A相过压
	}
	else
	{
		if( byt<3 )   i = byt;	//修正模式字
		else  i = byt+3;
		j = bt;
	}
	
	if( Mode.Report[i]&(1<<j) )	//判断模式字是否置位
	{
		if( i == 4 && j == 5 )
		{
			if( below_60u_flag==0 ) //掉电事件开始(处理完below_60u_flag=1)
			{
				if( Meter_Run_Timer1 < Mode.Report_Timer ) return;//电表上电时间不足1小时,则掉电后不进行掉电发生上报
				
				ReportList[0] &= B1111_0000;
				ReportList[0] |= B0000_0011; //重发3次 掉电发生
				return;
			}
			else
			{
//				if( Meter_Run_Timer2 < Mode.Report_Timer ) return;//电表上电时间不足1小时,则上电后不进行掉电结束上报
				
				ReportList[0] &= B1111_0000;
				ReportList[0] |= B0000_1100; //重发3次 掉电结束
			}
				
		}
		else
		{
			ReportList[0] |= B0011_0000; //重发3次 上报状态	
		}	
		
		Report_Data[byt] |= (1<<bt);	//置位上报状态字
		i = byt*8+bt;
		if( (i>=1)&&(i<=5)&&(i!=3) ) Report_Num[i] = 0xff;	//无发生次数数据标识的事件传FF
		else if( Report_Num[i] < 0xff ) Report_Num[i]++;	//新增次数加1
	}
}

//准备主动上报状态字和新增次数
unsigned char Ready_Reportdata( unsigned char *Buf )
{
	unsigned char i,n;
	
//	Reset_Rep_Timer = Calculate_Timer(3);		//启动复位上报状态字定时器
	memcpy( Report_Data2, Report_Data, 5 );		//备份上报状态字
	
	Buf[0] = 0x00;
	memcpy( Buf+1, Report_Data, 3 );
	memset( Buf+4, 0x00, 7 );
	Buf[11] = Report_Data[3];
	Buf[12] = Report_Data[4];
	Buf[13] = 0xAA;
	
	//修正应答的上报状态字
	if( Buf[3]&B1000_0000 ) {Buf[3]&=B0111_1111; Buf[9]|=B0010_0000;}//掉电临时借用存A相断相 
	if( Buf[3]&B0000_0100 ) {Buf[3]&=~B0000_0100; Buf[4]|=B0010_0000;}//低电压临时借用存A相欠压 
	if( Buf[3]&B0000_0010 ) {Buf[3]&=~B0000_0010; Buf[4]|=B0001_0000;}//高电压临时借用存A相过压 
		
	for( i=0,n=0; i<40; i++ )
	{
		Buf[14+n] = Report_Num[i];
		if( Report_Num[i] ) n++;
	}
	Buf[14+n] = 0xAA;
	return(15+n);
}


//清零点清零数据
void Clr_Zero_Data()
{
	already_setclock_flag = 0;//清广播校时标志
	hangup_comm_flag = 0;//清挂起标志
	Mac_Err_Times = 0;//mac错误次数清零
	G_Clockerr_Times = 0;//清明文广播校时记录故障次数
	Password_Err[0] = 0;//清密码错误次数
	Password_Err[1] = 0;
}


//type=0清零线电流不平衡持续时间,type=1过流持续时间
void Clr_Otherdata( unsigned char Type )
{
//	零线电流不平衡持续时间(4)+过流持续时间(4)+电池欠压总累计时间(4)+掉电总累计时间(4)+电池工作时间(4)+失压持续时间(4)+低电压时间(4)+高电压时间(4) 
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
	
	Temp08 = Bcd_To_Hex( *Clock ); //时
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
				if( (Year&0x03) == 0 )	MaxDay++;	//闰年
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

int16 Get_RTCTop_Proc( int16 Temp16 )	//顶点调校值折算
{
	int16 i;
	float Rtcadj;
		
	Rtcadj = Temp16 * 5.0 / 432.0 + Rtcadj_Offset2;	//此处单位均为ppm
	
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


//密码判断
unsigned char Veri_Psw( uint08 *Buf )
//Buf[0]:权限[1]~[3]:倒序密码
//返回值: 0:正确; 1/2:错误
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


//不同的冻结对应固定的模式字，冻结模式字是可设置的，用户在冻结模式字中未选择的数据类型，
//单相抄读时应返回异常应答，错误信息字Bit1 位置“1”“无数据请求”。
//数据块抄读，传输时以两个连续的AAH 略过。
unsigned short ReadFreezedRec( uint08 Type, uint08 Sn, uint08 No, uint08 *AckBuf )
//Type: 记录类型; No: 上几次; Sn:数据项
//return: 0:读取失败; 1:读取的数据长度
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
		case 0x00:	//定时冻结, 60次
			ptr = ee_timingf_inpage;
			mode = Week_Holiday.Freeze[1].B08[1];
			break;

		case 0x01:	//瞬时冻结, 3次
			ptr = ee_immedf_inpage;
			mode = Week_Holiday.Freeze[2].B08[1];
			break;
		
		case 0x02:	//约定冻结, 时区表切换, 2次
			ptr = ee_agreesqf_inpage;
			mode = Week_Holiday.Freeze[3].B08[1];
			break;
		
		case 0x03:	//约定冻结, 日时段表切换, 2次
			ptr = ee_agreesdf_inpage;
			mode = Week_Holiday.Freeze[3].B08[1];
			break;

		case 0x04:	//整点冻结: 冻结时间+正向有功总电能+反向有功总电能, 254次, 整点冻结时间间隔默认为60分钟。
			ptr = ee_hourf_inpage;
			mode = Week_Holiday.Freeze[4].B08[1];
			break;
			
		case 0x06:	//日冻结, 254次
			ptr = ee_dayf_inpage;
			mode = Week_Holiday.Freeze[5].B08[1];
			break;
		
		case 0x07:	//约定冻结, 阶梯切换, 2次
			ptr = ee_agreejtf_inpage;
			mode = Week_Holiday.Freeze[3].B08[1];
			break;
			
		case 0x0A:	//约定冻结, 阶梯时区切换, 2次
			ptr = ee_jtsqswith_inpage;
			mode = Week_Holiday.Freeze[3].B08[1];
			break;
			
		case 0x0C:	//月冻结, 24次
			ptr = ee_monthn_inpage;
			mode = Week_Holiday.Freeze[6].B08[1];
			break;
			
		default:
			return 0;
	}

	Obj = ptr;
	RtRec = GetRecNum( Obj, 0 ); //记录存储参数准备
	ptrmax = RtRec.ValPoint;

	if( (No==0) || (No > RtRec.Depth) ) return 0;	//次数超限
	
	if( Type == 0x04 ) //整点冻结
	{
		len = ee_hourfreezedl_lenth;
		style = 4;	//偏移地址和长度
	}
	else
	{
		len = ee_freezedl_lenth;
		style = max_dl_lenth;	//偏移地址和长度
	}
	
	if( ptrmax < No )	memset( Buf, 0x00, len );
	else 
	{	
		RtAddr = GetRecAddr( Obj, 0, No, &RtRec );
		if( IsFlashRec(Obj) )
		{
			result = Flash_Rd_Bottom( RtAddr.AppPage, RtAddr.AppPos, Buf, RtRec.TotLen ); //从Flash中读取
		}
		else
		{
			result = I2C_Read_Bottom( RtAddr.DataPage+0, 0, Buf, 128 );	//冻结时间+冻结数据
			if( result == 0 )
			result = I2C_Read_Bottom( RtAddr.DataPage+1, 0, Buf+128, 128 );	//冻结数据
			if( result == 0 )
			result = I2C_Read_Bottom( RtAddr.DataPage+2, 0, Buf+256, ee_freezedl_lenth-256 );	//冻结数据
		}
		if( result ) return 0;
	}
		
	k = 0x01;
	switch( Sn )
	{
		case 0xFF:
		case 0x00: //冻结时间:YYMMDDhhmm
			memcpy( AckBuf+k, Buf, 5 );
			k += 5;
			if( Sn == 0x00 ) break;
			AckBuf[k++] = 0xAA;
			
		default: 
			for( n=0; n<2; n++ )
			{
				if( (Sn == (n+1) || (Sn == 0xFF)) )	//正向有功总电能, 反向有功总电能
				{
					if( mode & (n+1) )
					{
						for( i=0; i<(style/4); i++ ) 
						{
							Hex2Bcd_Dl( Buf+5+n*style+4*i, 1 );//脉冲数转BCD电量
						}
						memcpy( AckBuf+k, Buf+5+n*style, style );
						if( style == 4 ) k += style;
						else k += (Bcd_To_Hex(Feik.Num[3])+1)*4;
					}

					if( Sn == (n+1) ) break;
					AckBuf[k++] = 0xAA;
				}
			}
			
			if( Type == 0x04 ) break;	//整点冻结
			
			for( n=2; n<8; n++ )
			{
				if( (Sn == (n+1) || (Sn == 0xFF)) )	//组合无功1~2电能数据, 第一~四象限无功电能数据
				{
					if( mode & (1<< ((n<4) ? n : 4 )) )
					{
						if( n == 2 || n == 3 )
						{
							//计算组合无功
							for( i=0; i<(Bcd_To_Hex(Feik.Num[3])+1); i++ )
							{
								CalZhuhe( Buf+5+style*2+4*i, AckBuf+k, Buf[len-4+n], 0xff );//组合无功
								Hex2Bcd_Dl( AckBuf+k, 0 );//脉冲数转BCD电量
								k += 4;
							}						
						}
						else
						{
							//复制四象限无功
							for( i=0; i<(style/4); i++ ) 
							{
								Hex2Bcd_Dl( Buf+5+style*(2+n-4)+4*i, 1 );//脉冲数转BCD电量
							}
							memcpy( AckBuf+k, Buf+5+style*(2+n-4), style );
							k += (Bcd_To_Hex(Feik.Num[3])+1)*4;
						}
					}

					if( Sn == (n+1) ) break;
					AckBuf[k++] = 0xAA;
				}
			}
			
			//正向有功最大需量, 反向有功最大需量
			if( Sn == 0xFF )
			{
				memset( AckBuf+k, 0xAA, 2 );
				k += 2;
			}
			
			//变量数据: 总有功功率
			if( (Sn == 0x10) || (Sn == 0xFF) )
			{
				if( mode & 0x80 )
				{
					memcpy( AckBuf+k+0, Buf+len-8, 3 );	//总有功功率
					memcpy( AckBuf+k+3, Buf+len-8, 3 );	//A 相有功功率
					if( ptrmax < No ) fill = 0x00;
					memset( AckBuf+k+6, fill, 6 );		//其他功率
					
					memcpy( AckBuf+k+12, Buf+len-5, 3 );	//总无功功率
					memcpy( AckBuf+k+15, Buf+len-5, 3 );	//A 相无功功率
					if( ptrmax < No ) fill = 0x00;
					memset( AckBuf+k+18, fill, 6 );		//其他功率
					
					k += 24;
				}

				if( Sn == 0x10 ) break;
				AckBuf[k++] = 0xAA;
			}
			break;
	}

	return (k-1);
}


//通讯计算高精度,输入格式必须固定为正向(4)+反向4(4)+组合无功1(4)+组合无功2(4)
void Comm_Calculate_Comp_Rp( unsigned char *Inbuf, unsigned char num, unsigned char mode )//通讯由脉冲数计算电量
{		
	uint08 i,Buf[70];
	union B32_B08_2 Temp32;
	union B64_B08_2 Temp64;
	
	if( num%4 ) return;
	
	memcpy( Buf, Inbuf, 70 );  
	
	for(i=0; i<num; i++)
	{
		if( ((i%4) == 2) || ((i%4) == 3) ) //组合无功1+组合无功2
		{
			uint08 Temp08;
			
			Temp08=0;
			memcpy( Temp32.B08, Buf+4*i, 4 );  //复制4字节脉冲数
			if( (signed long )(Temp32.B32) < 0 )
			{
				Temp08 = 1;
				Temp64.B64 = (signed long long)((signed long)Temp32.B32*(-1.0))*100/Meter.Const_H;
			}
			else
			{
				Temp64.B64 = (signed long long)((signed long)Temp32.B32*( 1.0))*100/Meter.Const_H;
			}
			
			Calculate_Overflow( Temp64.B08, 8 );//组合电量边界处理
			Hex2Bcd_SS( Temp64.B08, Temp64.B08, 8 );
			if( Temp08 ) Temp64.B08[4] |= 0x80;	//组合电量<0，最高位置1
		}
		else
		{
			memcpy( Temp32.B08, Buf+4*i, 4 );  //复制4字节脉冲数
			Temp64.B64 = (signed long long)Temp32.B32*100/Meter.Const_H;
			Hex2Bcd_SS( Temp64.B08, Temp64.B08, 8 );
		}
		
		if( (mode&0x80)==0 ) memcpy( Inbuf+4*i, Temp64.B08+1, 4 );	//普通精度(3+1)
		else memcpy( Inbuf+5*i,  Temp64.B08, 5 );	//高精度(3+2)
	}
}

//hex脉冲数转换成bcd的电量,普通精度4字节变成4字节,高精度4字节变成5字节
void Comm_Calculate_Dl( unsigned char *Inbuf, unsigned char num, unsigned char mode )//通讯由脉冲数计算电量
{		
	uint08 i,Buf[70];
	union B32_B08_2 Temp32;
	union B64_B08_2 Temp64;
	
	memcpy( Buf, Inbuf, 70 );  
	
	for(i=0; i<num; i++)
	{
		memcpy( Temp32.B08, Buf+4*i, 4 );  //复制4字节脉冲数
		Temp64.B64 = (signed long long)Temp32.B32*100/Meter.Const_H;
		Hex2Bcd_SS( Temp64.B08, Temp64.B08, 8 );
		
		if( (mode&0x80)==0 ) memcpy( Inbuf+4*i, Temp64.B08+1, 4 );	//普通精度(3+1)
		else memcpy( Inbuf+5*i,  Temp64.B08, 5 );	//高精度(3+2)
	}
}


void Calculate_Ah( unsigned char *Inbuf )//计算安时数
{	
	union B32_B08_2 Temp32;
						
	Temp32.B32 = Lost_Aver_I*(Lost_V_Timer/60.0)/10;
	Hex2Bcd_SS( Temp32.B08, Temp32.B08, 4 );
	memcpy( Inbuf, Temp32.B08, 4 );	//计算安时数
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
	const uint08 code MaxiLenth  [8] = { 6, 16, 16, 11,  2, 6, 16, 16 };	//同时支持A相
	
	unsigned char code PwrDnOffset1[6] = { 0, 6,22,70,70+6,70+22 };
	unsigned char code PwrDnOffset2[6] = { 0,12,12, 6, 28, 28 };
//	unsigned char code PwrDnLen[6]     = { 6, 16, 0, 6, 16,  0 };
	unsigned char code PwrDnLen[6]     = { 6, 16, 16, 6, 16, 16 };	//同时支持A相
	
//	unsigned char code MaxiSup [7] = { B0001_1111, B0011_1110, B0000_0000, B0000_0000, B0001_1111, B0000_0000, B0000_0000 };
//	unsigned char code PwrDnSup[5] = { B0001_1111, B0000_0000, B0011_1110, B0000_0000, B0000_0000 };
	unsigned char code MaxiSup [7] = { B1111_1111, B0011_1111, B0000_0000, B0000_0000, B1111_1111, B0000_0001, B0000_0000 }; //同时支持A相
	unsigned char code PwrDnSup[5] = { B1111_1111, B0000_0001, B1111_1110, B0000_0011, B0000_0000 }; //同时支持A相
	
	//新增失压
	unsigned char code Tab_Lostv[]= {6,4,4,4,4,4,4,4,4,2,3,3,3,2,4,4,4,4,2,3,3,3,2,4,4,4,4,2,3,3,3,2,4,4,4,4,6,4,4,4,4,4,4,4,4};
	const uint08 code LostvOffset1[8] = { 0,  6, 22, 38, 125-16, 125, 125+6, 125+22 };
	const uint08 code LostvOffset2[8] = { 0, 12, 12, 28, 57, 6, 41, 41 };
	const uint08 code LostvLenth  [8] = { 6, 16, 16, 13, 8, 6, 16, 16 };	//同时支持A相
	unsigned char code LostvSup [7] = { B1111_1111, B0011_1111, B0000_0000, B0000_0000, B1111_0011, B0001_1111, B0000_0000 }; //同时支持A相	
	//高精度(0x83抄读)
	//新增失压
	unsigned char code Tab_Lostv_G[]= {6,5,5,5,5,5,5,5,5,2,3,3,3,2,5,5,5,5,2,3,3,3,2,5,5,5,5,2,3,3,3,2,4,4,4,4,6,5,5,5,5,5,5,5,5};
	const uint08 code LostvOffset1_G[8] = { 0,  6, 26, 46, 141-16, 141, 141+6, 141+26 };
	const uint08 code LostvOffset2_G[8] = { 0, 12, 12, 32, 65, 6, 45, 45 };
	const uint08 code LostvLenth_G  [8] = { 6, 20, 20, 13, 8, 6, 20, 20 };	//同时支持A相
	
	unsigned char code Tab_Maxi_G[]= {6,5,5,5,5,5,5,5,5,2,3,3,3,2,5,5,5,5,2,3,3,3,2,5,5,5,5,2,3,3,3,2,6,5,5,5,5,5,5,5,5};
	const uint08 code MaxiOffset1_G[8] = { 0,  6, 26, 46, 57, 125, 125+6, 125+26 };
	const uint08 code MaxiOffset2_G[8] = { 0, 12, 12, 32, 43, 6, 45, 45 };
	const uint08 code MaxiLenth_G  [8] = { 6, 20, 20, 11,  2, 6, 20, 20 };	//同时支持A相
	
	unsigned char code Tab_PwrDn_G[]={6,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6,5,5,5,5,5,5,5,5};
	unsigned char code PwrDnOffset1_G[6] = { 0, 6,26,86,86+6,86+26 };
	unsigned char code PwrDnOffset2_G[6] = { 0,12,12, 6, 32, 32 };
	unsigned char code PwrDnLen_G[6]     = { 6, 20, 20, 6, 20,  20 }; //同时支持A相
	
	unsigned char code Tab_Reley_G[]={6,4,5,5,5,5,5,5};
	

	AckBuf[0] = 0x00;	//缺省返回数据长度是0x00

	if( (DI[1] == 0xFF) && (DI[0] == 0xFF) ) return 0;

	Buf[2] = DI[2];
	Buf[3] = DI[3]&0x7f;
	i = Find_EventTable(Buf+2);		//判断是否找到合法数据标识
	if( i == EventNum )	return 0;

	page = EventTable[i].page;
	inpage = EventTable[i].offset;
	rec_len = EventTable[i].len;
	ptr = i+ee_clearn_inpage;
	
	switch( ptr )
	{
		case ee_powerdownn_inpage: //掉电记录
			if( DI[3]&0x80 ) //高精度
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
					if( DI[0] == 0x0c )//读掉电总累计时间
					{
						Get_Keep_Timer(3, AckBuf+1);
						AckBuf[0] = 3;
						return AckBuf[0];
					}
				}
				else
				{
					if( (DI[1] > 0x22) || (BitValue(PwrDnSup, DI[1]-1) == 0) ) return 0;
					
					if( DI[3]&0x80 ) //高精度
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
			
		case ee_lostvn_inpage:	//失压
			if( DI[3]&0x80 ) //高精度
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
					if( DI[0] == 2 )//读失压累计时间
					{
						Get_Keep_Timer(5, AckBuf+1);
						AckBuf[0] = 3;
						return AckBuf[0];
					}
				}
				else
				{
					if( (DI[1] > 0x35) || (BitValue(LostvSup, DI[1]-1) == 0) ) return 0;
					
					if( DI[3]&0x80 ) //高精度
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
		
		case ee_maxi_inpage:	//过流	
			if( DI[3]&0x80 ) //高精度
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
					if( DI[0] == 2 )//读过流累计时间
					{
						Get_Keep_Timer(1, AckBuf+1);
						AckBuf[0] = 3;
						return AckBuf[0];
					}
				}
				else
				{
					if( (DI[1] > 0x31) || (BitValue(MaxiSup, DI[1]-1) == 0) ) return 0;
					
					if( DI[3]&0x80 ) //高精度
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

		case ee_batterlow_inpage:	//电池欠压记录
			if( DI[1] == 0 )
			{
				if( DI[0] == 0 ) //电池欠压总累计时间
				{
					Get_Keep_Timer(2, AckBuf+1);
					AckBuf[0] = 3;
					return AckBuf[0];
				}
				else if( DI[0] <= 0x0A ) //电池欠压记录
				{
					if( DI[3]&0x80 ) //高精度
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

		case ee_openrelayn_inpage:	//跳闸次数
		case ee_closerelayn_inpage:	//合闸次数
			if( DI[3]&0x80 ) //高精度
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
					if( DI[3]&0x80 ) //高精度
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
		if( ((ptr == ee_powerdownn_inpage) && (DI[0] == 0)) || //掉电记录
			((ptr != ee_powerdownn_inpage) && (DI[0] == 1)))	 //其他记录
		{
			Read_Event_Number( AckBuf+1, ptr );
			AckBuf[0] = 3;
		}

		return AckBuf[0];
	}
					
	if( (DI[0]) && (DI[0]<=max_eventrecord_p) )	//上1~10次
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

	ptrmax = RdRecTimes(ptr);//返回有效指针
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
			I2C_Read_Eeprom( page+result, inpage, Buf, rec_len );//读存储在数据ee里的有效数据
			if( ptr == ee_lostvn_inpage || ptr == ee_maxi_inpage )	//失压/过流则重新组帧数据
			{
				if( ptr == ee_lostvn_inpage && lost_v_flag && (n==0) )//上一次失压记录(安时数还在累计中)
				{
					Calculate_Ah( Buf+57 );//计算安时数
				}
				memcpy( Buf+100, Buf+12+16, 13 ); //保存发生时刻电压电流功率及因数(13)
				memcpy( Buf+12+16, Buf+12+16+13, 16 );//前移结束正反向有功(8)+组合无功(8)
				Comm_Calculate_Comp_Rp( Buf+12, 8, DI[3] );
				if( DI[3]&0x80 ) //高精度
				{	//高精度数据格:过流发生时刻(6)+结束时刻(6)+发生时正反向有功(10)+组合无功(10)+发生时刻电压电流功率及因数(13)+结束正反向有功(10)+组合无功(10)		
					if( ptr == ee_lostvn_inpage )
					{
						memcpy( Buf+65, Buf+57, 4 ); //保存总安时数
						memcpy( Buf+69, Buf+57, 4 ); //保存A相安时数
					}
					memcpy( Buf+80, Buf+12+20, 20 ); //保存结束正反向有功(10)+组合无功(10)
					memcpy( Buf+12+20, Buf+100, 13 ); //恢复发生时刻电压电流功率及因数(13)
					memcpy( Buf+12+20+13, Buf+80, 20 ); //恢复结束正反向有功(10)+组合无功(10)
					if( ptr == ee_lostvn_inpage )
					for( i=0; i<8; i++ ) memcpy( Ic_Comm_TxBuf+LostvOffset1_G[i], Buf+LostvOffset2_G[i], LostvLenth_G[i] );//发生时刻
					else
					for( i=0; i<8; i++ ) memcpy( Ic_Comm_TxBuf+MaxiOffset1_G[i], Buf+MaxiOffset2_G[i], MaxiLenth_G[i] );//发生时刻
				}
				else //普通精度
				{
					if( ptr == ee_lostvn_inpage )
					{
//						memcpy( Buf+57, Buf+57, 4 ); //保存总安时数
						memcpy( Buf+61, Buf+57, 4 ); //保存A相安时数
					}
					memcpy( Buf+80, Buf+12+16, 16 ); //保存结束正反向有功(8)+组合无功(8)
					memcpy( Buf+12+16, Buf+100, 13 ); //恢复发生时刻电压电流功率及因数(13)
					memcpy( Buf+12+16+13, Buf+80, 16 ); //恢复结束正反向有功(10)+组合无功(10)
					if( ptr == ee_lostvn_inpage )
					for( i=0; i<8; i++ ) memcpy( Ic_Comm_TxBuf+LostvOffset1[i], Buf+LostvOffset2[i], LostvLenth[i] );//发生时刻
					else
					for( i=0; i<8; i++ ) memcpy( Ic_Comm_TxBuf+MaxiOffset1[i], Buf+MaxiOffset2[i], MaxiLenth[i] );//发生时刻
				}
			}
			else if( ptr == ee_powerdownn_inpage )	//掉电则重新组帧数据
			{
				Comm_Calculate_Comp_Rp( Buf+12, 8, DI[3] ); 
				if( DI[3]&0x80 ) //高精度
				{	//高精度数据格:掉电发生时刻(6)+结束时刻(6)+发生时正反向有功(10)+组合无功(10)+结束正反向有功(10)+组合无功(10)		
					for( i=0; i<6; i++ ) memcpy( Ic_Comm_TxBuf+PwrDnOffset1_G[i], Buf+PwrDnOffset2_G[i], PwrDnLen_G[i] );//发生时刻
				}
				else //普通精度
				{
					for( i=0; i<6; i++ ) memcpy( Ic_Comm_TxBuf+PwrDnOffset1[i], Buf+PwrDnOffset2[i], PwrDnLen[i] );//发生时刻
				}
			}
			else if( ptr == ee_batterlow_inpage )	//电池欠压
			{
				Comm_Calculate_Comp_Rp( Buf+6, 4, DI[3] );
				if( DI[3]&0x80 ) //高精度
				{
					memcpy( Ic_Comm_TxBuf+ 0, Buf+0, 6+10+10 );//发生时刻+正反向电量+组合无功1和2
					memcpy( Ic_Comm_TxBuf+26, Buf+6, 10+10 );//正反向电量+组合无功1和2(A相) 同时支持A相
				}
				else //普通精度
				{
					memcpy( Ic_Comm_TxBuf+ 0, Buf+0, 6+8+8 );//发生时刻+正反向电量+组合无功1和2
					memcpy( Ic_Comm_TxBuf+22, Buf+6,  8+8 );//正反向电量+组合无功1和2(A相)	同时支持A相
				}
			}
			else //拉合闸
			{
				Comm_Calculate_Dl( Buf+10, 6, DI[3] );
				if( DI[3]&0x80 ) //高精度
				{
					memcpy( Ic_Comm_TxBuf, Buf, 6+4+10+20 );//发生时刻+正反向电量+四象限无功
				}
				else //普通精度
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

	i = Find_EventTable(DI+1);		//判断是否找到合法数据标识
	if( i == EventNum )	return 0;
	if( i == ee_powerdownn_inpage-ee_clearn_inpage ) return 0;	//非法数据标识
	if( i == ee_poweroffn_inpage-ee_clearn_inpage || i==ee_poweronn_inpage-ee_clearn_inpage ) //掉电上报事件和上电上报事件与掉电事件同源
	{
		ptr2 = i+ee_clearn_inpage; //暂时保存掉电上报事件和上电上报事件
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
		ptr == ee_batterlow_inpage	) return 0;	//非法数据标识
		
//	if( (DI[3]&0x80) && 	//不支持的高精度直接返回错误
//		(ptr == ee_dayvolpassn_inpage || ptr == ee_monvolpassn_inpage || ptr == ee_monpowerdownn_inpage || ptr == ee_yearpowerdownn_inpage) ) 
//						return 0;	//非法数据标识
	
	if( len > 0x00 )
	{	
		if( DI[0] == 0x00 )	//总次数
		{
			Read_Event_Number( AckBuf+1, ptr );
			k = 3;
			
			if( (ptr == ee_powerdownn_inpage) && (ptr2 == ee_poweronn_inpage) ) //掉电上报事件和上电上报事件与掉电事件同源
			{
				if( ChkPdRcdTime() == 0 ) //掉电结束时间为0(无新的上电上报)
				{
					uint32 Number=0;
					
					memcpy( (uint08*)&Number, AckBuf+1, 3 );
					if( Number ) Number--;	//上电上报事件减1
					memcpy( AckBuf+1, (uint08*)&Number, 3 );
				}
			}
			
			if( ptr == ee_lowervn_inpage )//低电压事件
			{
				Get_Keep_Timer(6, AckBuf+1+3);
				k = 6;
			}	
			else if( ptr == ee_highvn_inpage )//高电压事件
			{
				Get_Keep_Timer(7, AckBuf+1+3);
				k = 6;
			}
		}
		else	//事件记录
		{
//			if( ptr == ee_keysetn_inpage ) MaxEvent = 2;	//密钥更新记录只有2条
//			if( ptr == ee_shiqun_inpage ) MaxEvent = 2;	//时区编程记录只有2条
//			if( ptr == ee_shiduann_inpage ) MaxEvent = 2;	//时段编程记录只有2条
//			if( ptr == ee_weekdayn_inpage ) MaxEvent = 2;	//周休日编程记录只有2条
//			if( ptr == ee_jtpricen_inpage ) MaxEvent = 2;	//阶梯表编程记录只有2条
//			if( ptr == ee_gbsclockn_inpage ) MaxEvent = max_gbsetclock_p;	//广播校时
//			if( ptr == ee_dayvolpassn_inpage ) MaxEvent = max_dayvolpass_p;	//日电压合格率
//			if( ptr == ee_monvolpassn_inpage ) MaxEvent = max_monvolpass_p;	//月电压合格率
			MaxEvent = MaxRecNum[ptr];
			if( DI[0] > MaxEvent ) return 0;	//次数超限
			
			ptrmax = RdRecTimes(ptr);//返回有效指针
			result = Read_Event_Point( ptr );
			
			TmpPtr = result;	//备份上一次事件记录指针
			
			if( result < (DI[0]-1) ) result += MaxEvent;			
			result -= (DI[0]-1);
			
			if( (ptr == ee_powerdownn_inpage) && (ptr2 == ee_poweronn_inpage) ) //掉电上报事件和上电上报事件与掉电事件同源
			{
				if( ChkPdRcdTime() == 0 ) //掉电结束时间为0(无新的上电上报)
				{
					if( result < 1 ) result += MaxEvent;	//再找上一条
					result -= 1;
					if( ptrmax ) ptrmax--;	//有效指针减1
				}
			}
			
			if( ptr == ee_gbsclockn_inpage )//广播校时
				I2C_Read_Eeprom( page+result/3, offset+(result%3)*len, Buf, len );
			else if( ptr == ee_dayvolpassn_inpage || ptr == ee_monvolpassn_inpage )//日电压合格率/月电压合格率
				I2C_Read_Eeprom( page+result/4, offset+(result%4)*len, Buf, len );	
			else
				I2C_Read_Eeprom( page+result, offset, Buf, len );
			
//			if( ptr == ee_lowervn_inpage && lower_v_event_flag && DI[0]==1 )//低电压事件还在累计中
//			{
//				Get_Keep_Timer(6, Buf+len-4);	//读低电压累计时间:返回4字节时间(Buf[len-4]~Buf[len-1])
//			}	
//			else if( ptr == ee_highvn_inpage && high_v_event_flag && DI[0]==1 )//高电压事件还在累计中
//			{
//				Get_Keep_Timer(7, Buf+len-4);	//读高电压累计时间:返回4字节时间(Buf[len-4]~Buf[len-1])
//			}
			
			memcpy( AckBuf+1, Buf, len );		

			switch( DI[1]+(DI[2]<<8) )
			{
				case 0x3001:	//电表清零
					k = 106;	//设置返回数据的长度
					memset( AckBuf+1+18+16, 0xFF, 88-16 );
					break;
				
				case 0x3005:	//时段表编程
				case 0x3006:	//时区表编程
					//以(Buf中第几个半字节的值)为"指针所指向的ReadPtr的对应字节"中写入几。
					I2C_Read_Eeprom( page+TmpPtr, 70, TmpBuf, 5 );	//读取上1次日时段表编程记录页内历史记录
					
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
						Temp32.B08[2] = 15;	//结束页
					}
					else
					{
						TmpP1 = ee_shiqu1_page;
						TmpP2 = ee_shiqurecord_page;
						Temp32.B08[2] = 1;	//结束页
					}
					
					memcpy( AckBuf+1, Buf+5, 10 );	//发生时间+操作者代码
					k = 10;	//返回缓冲器地址指针

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

						len = 42;	//默认读取的长度
						I2C_Read_Eeprom( page, offset, AckBuf+1+k, len );	//当前时段表。
					}
					break;
					
				case 0x3010:	//阶梯编程
					k = 10;	//返回缓冲器地址指针
						
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
					k = len;	//设置返回数据的长度
					break;
			}
			
			//hex脉冲数转换成bcd的电量,普通精度4字节变成4字节,高精度4字节变成5字节
			if( ptr == ee_gbsclockn_inpage ) //广播校时记录 8+16
			{
				Comm_Calculate_Dl( AckBuf+1+12, 6, DI[3] );
				if( DI[3]==0x83 ) k += 6;
			}
			else if( ptr == ee_clearn_inpage ) //电表清零 8+16
			{
				Comm_Calculate_Dl( AckBuf+1+10, 6, DI[3] );
				if( DI[3]==0x83 ) {k = 130; memset( AckBuf+1+40, 0xFF, 90 );}
			}
			else if( ptr == ee_covern_inpage || ptr == ee_clockerrn_inpage || ptr == ee_nlineerrn_inpage ) //开表盖/时钟故障/零线电流异常 8+16+8+16
			{
				Comm_Calculate_Dl( AckBuf+1+12, 12, DI[3] );
				if( DI[3]==0x83 ) k += 12;
			}
			else if( ptr == ee_setclockn_inpage ) //设置时钟 8+16
			{
				Comm_Calculate_Dl( AckBuf+1+16, 6, DI[3] );
				if( DI[3]==0x83 ) k += 6;
			}
			else if( ptr == ee_commerrn_inpage) //通信模块异常 8+8
			{
				Comm_Calculate_Dl( AckBuf+1+18, 4, DI[3] );
				if( DI[3]==0x83 ) k += 4;
			}
			else if( ptr == ee_relayerrn_inpage ) //负荷开关误动作 8+8
			{
				Comm_Calculate_Dl( AckBuf+1+13, 4, DI[3] );
				if( DI[3]==0x83 ) k += 4;
			}
			else if( ptr == ee_batchangen_inpage || ptr == ee_calerrn_inpage || ptr == ee_commchangen_inpage ) //时钟电池更换/计量故障/通信模块变更 8+8
			{
				Comm_Calculate_Dl( AckBuf+1+12, 4, DI[3] );
				if( DI[3]==0x83 ) k += 4;
			}
			else if( ptr == ee_batterlow_inpage ) //电池欠压 8+8
			{
				Comm_Calculate_Dl( AckBuf+1+6, 4, DI[3] );
				if( DI[3]==0x83 ) k += 4;
			}
			else if( ptr == ee_powererrn_inpage ) //电源异常 8
			{
				Comm_Calculate_Dl( AckBuf+1+12, 2, DI[3] );
				if( DI[3]==0x83 ) k += 2;
			}
			else if( ptr == ee_powerdownn_inpage ) //掉电上报事件和上电上报事件与掉电事件同源
			{
				if( ptr2 == ee_poweroffn_inpage  ) //掉电上报 8+8
				{
					k = ee_poweroffnote_lenth;
					memcpy(AckBuf+1+6, AckBuf+1+12, 16 );//发生时刻电量
					Comm_Calculate_Comp_Rp( AckBuf+1+6, 4, DI[3] );
					if( DI[3]==0x83 )
					{
						memcpy( AckBuf+1+6+20, AckBuf+1+44, 3 );//发生时刻前3分钟的平均电流
						k += 4;
						memset( AckBuf+1+6+20+3, 0xff, 6 ); //发生时刻前3分钟的平均电流(B/C相)
						k += 6;
					}
					else
					{	
						memcpy( AckBuf+1+6+16, AckBuf+1+44, 3 );//发生时刻前3分钟的平均电流
						memset( AckBuf+1+6+16+3, 0xff, 6 ); //发生时刻前3分钟的平均电流(B/C相)
						k += 6;
					}
				}
				else if( ptr2 == ee_poweronn_inpage) //上电上报 8+8
				{
					k = ee_poweronnote_lenth;
					memcpy(AckBuf+1, AckBuf+1+6, 6 ); //结束时间
					memcpy(AckBuf+1+6, AckBuf+1+12+16, 16 );//结束时刻电量
					Comm_Calculate_Comp_Rp( AckBuf+1+6, 4, DI[3] );
					if( DI[3]==0x83 ) k += 4;
				}
			}
			
			if( ptrmax < DI[0] )	memset( AckBuf+1, 0x00, k );
//			if( ((DI[1]+(DI[2]<<8) == 0x3005) || (DI[1]+(DI[2]<<8) == 0x3010)) && SN  )	AckBuf[ ++AckBuf[0] ] = SN;
		}
	}
	
	return k;	//读取成功
}

//组合电量计算函数, 每次计算1组
//计算组合无功: Offset = 0xff
void CalZhuhe( const unsigned char *ZhuBuf, unsigned char *RtBuf, unsigned char Mode, unsigned char Offset )
//ZhuBuf要求必须包含正向和反向的总尖峰平谷电量。
//RtBuf是返回组合脉冲数，8字节。
{
	signed long long Zhen;
	union B32_B08_2 Temp32;
	unsigned char i;
	
	Zhen = 0x00;

	if( Offset<=1 )	//有功
	{
		switch( Mode&B0000_0011 ) //有功正向
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
	
		switch( Mode&B0000_1100 ) //有功反向
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
		//计算组合无功1和2
		for(i=0; i<4; i++)
		{
			switch( (Mode>>2*i)&B0000_0011) //第1~4象限无功
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

	memcpy( RtBuf, (uint08*)&Zhen, 8 );	//RtBuf是返回组合脉冲数，8字节。
}


unsigned char Cal_Comb( unsigned char DI2, unsigned char DI1, unsigned char DI0, unsigned char *ReturnBuf )
//DI2: 0:组合; 1:正向; 2:反向; 9:结算时间
//DI1: 0:总(结算时间); 1~4:1~4费率; FF:所有
//DI0: 0:当前; 1~12:1~12结算日; FF:所有(除13外)
//ReturnBuf: 数据均为反序
//当前电量,用电量,结算电量均以高字节在前存数据ee
{
	unsigned char i, k, n, result, ptrmax;
	unsigned char Buf[ee_histroydl_lenth];
	union B32_B08 Temp32;
	unsigned char Obj;
	RecStore RtRec;
	RtFlash  RtAddr;

	if( DI2 > 0x09 ) return 0x00;
	
	if( (DI1 == 0xFF) && (DI0 == 0xFF) ) return 0x00;	//两者不能同时为FF。
	
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
		
	if( DI0 ) //非当前数据
	{
		Obj = ee_histroyf_inpage;
		RtRec = GetRecNum( Obj, 0 ); //记录存储参数准备
		ptrmax = RtRec.ValPoint;
	}

	k = 0x00;
	for( n=Temp32.B08[0]; n<Temp32.B08[1]; n++ )	//DI0: 0~12,FF
	{
		if( n == 0x00 )	//当前
		{
			if( DI2 != 0x09 )
			{
				memcpy( Buf, Fwdl.Pluse[0].B08, max_dl_lenth ); //正向脉冲数
				memcpy( Buf+max_dl_lenth, Bkdl.Pluse[0].B08, max_dl_lenth ); //反向脉冲数
				for(i=0; i<4; i++) //四象限无功脉冲
				{
					memcpy( Buf+max_dl_lenth*(2+i), Rpdl[i].Pluse[0].B08, max_dl_lenth );
				}
			}
		}
		else if( n <= max_histroy_p )	//1~24结算日
		{
			RtAddr = GetRecAddr( Obj, 0, n, &RtRec );

			if( DI2 != 0x09 )
			{
				if( ptrmax >= n )
				{
					result = Flash_Rd_Bottom( RtAddr.AppPage, RtAddr.AppPos+5, Buf, RtRec.TotLen-5 ); //从Flash中读取
					if( result ) return 0x00;
				}
				else
				{
					memset( Buf, 0x00, ee_histroydl_lenth-5 );
				}				
			}
			else	//结算时间
			{
				if( ptrmax >= n )
				{
					result = Flash_Rd_Bottom( RtAddr.AppPage, RtAddr.AppPos+1, ReturnBuf+k, 4 ); //从Flash中读取
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
			for( i=Temp32.B08[2]; i<Temp32.B08[3]; i++, k+= 8 )	//脉冲数
			{
				if( DI2 == 0x00 )	//组合
				{
					if( n == 0x00 )	//当前
						result = Mode.Comp_B;
					else
						result = Buf[ee_histroydl_lenth-3-5];
					
					CalZhuhe( Buf+i*4, ReturnBuf+k, result, 0 );	//计算组合有功
				}
				else if( DI2 == 0x01 || DI2 == 0x02 )	//正向电量 or 反向电量
				{
					memset( ReturnBuf+k, 0x00, 8 );
					memcpy( ReturnBuf+k, Buf+max_dl_lenth*(DI2-1)+i*4, 4 );
				}
				
				else if( DI2 == 0x03 || DI2 == 0x04 )	//组合无功1和组合无功2
				{
					if( n == 0x00 )	//当前
						result = Mode.Rpcomp[DI2-3];
					else
						result = Buf[ee_histroydl_lenth-2-5+(DI2-0x03)];
					
					CalZhuhe( Buf+max_dl_lenth*2+i*4, ReturnBuf+k, result, 0xff );//计算组合无功
				}
				else 	//四象限无功
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
//DI2: 0:结算周期用电量;1:月用电量;2:年用电量
//DI0: 0:当前; 1:上1
//ReturnBuf: 时间4/预留4+高精度电量8字节
{
	unsigned char result;
	unsigned char Buf[ee_histroyusedl_lenth+8];
	
	if( DI2 == 2 )
	{
		//准备数据
		memcpy( Buf, Sclock.Clockbackup+2, 4 );//复制时间
		Cal_Comb( 0, 0, 0, Buf+4 );	//计算当前组合电量	

		I2C_Read_Eeprom( ee_pre1_histroyusedl_page+DI2, 0, Buf+8, ee_histroyusedl_lenth );
		
		memcpy( ReturnBuf+4, Buf+8*DI0+4, 4);
		memcpy( ReturnBuf+8, Buf+8*DI0+4+8, 4);
	}
	else
	{
		//准备数据
		Cal_Comb( 0, 0, 0, Buf );	//计算当前组合电量(结算周期用电量和月用电量)	

		I2C_Read_Eeprom( ee_pre1_histroyusedl_page+DI2, 0, Buf+4, ee_histroyusedl_lenth );
	
		memcpy( ReturnBuf+4, Buf+4*DI0, 4);
		memcpy( ReturnBuf+8, Buf+4*DI0+4, 4);
	}
	
	//计算用电量
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
		
	//应答数据
	Hex2Bcd_Dl_G( ReturnBuf+4, 0 );	//脉冲数转BCD电量(高精度)(组合)
		
	if( DI2 == 0x02 ) //年用电量
	{	
		memcpy( ReturnBuf, Buf+8*DI0, 4 );	//结算时间
			
		if( (Price.Ladder_Mode == 0x00) && (DI0 == 0x00) )
		{
			memset( ReturnBuf, 0x00, 4+8 );//月阶梯,当前年结算电量为0	
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

	if( DI[1] == 0x02 ) //月冻结掉电数据
	{
		if( DI[0] > 0x24 ) return 1;
		page = ee_powerdown_month_page;
		len = ee_powerdownmonth_lenth;
		ptr = ee_monpowerdownn_inpage;
		MaxEvent = max_powerdownmonth_p;
	}
	else //年冻结掉电数据
	{
		if( DI[0] > 0x03 ) return 1;
		page = ee_powerdown_year_page;
		len = ee_powerdownyear_lenth;
		ptr = ee_yearpowerdownn_inpage;
		MaxEvent = max_powerdownyear_p;
	}
			
	AckBuf[0] = 6;
	if( DI[0] == 0 ) //读当前
	{
		if( DI[1] == 0x02 )
		{
			Get_Keep_Timer(8, Buf);		//读月停电累计次数
			Get_Keep_Timer(9, Buf+4);	//读月停电累计时间
		}
		else
		{
			Get_Keep_Timer(10, Buf);	//读年停电累计次数
			Get_Keep_Timer(11, Buf+4);	//读年停电累计时间
		}
	}
	else
	{
		ptrmax = RdRecTimes(ptr);//返回有效指针
		result = Read_Event_Point( ptr );
		
		if( ptrmax < DI[0] ) {memset( AckBuf+1, 0x00, AckBuf[0] );return 0x00;}
		
		if( result < (DI[0]-1) ) result += MaxEvent;
		result -= (DI[0]-1);
		I2C_Read_Eeprom( page+result/8, (result%8)*8, Buf, len ); //读上n月
	}
	
	memcpy( AckBuf+1, Buf+0, 3 );
	memcpy( AckBuf+4, Buf+4, 3 );
	
	return 0x00;	//读取成功
}


//编程记录的说明：从按下编程开关到弹起编程开关，且对电能表进行编程操作，
//记录为一次编程记录，记录编程的最后10 个数据标识及编程结束时刻。
//编程记录结束时刻：1.按键退出编程模式; 2.编程有效时间结束; 3.身份认证失效; 4.身份认证有效时间结束
//以上4种情况下需要设置New_Program_Rec = 0;
void ProgramRecord( unsigned char *Dix, unsigned char *Opt )
{
	if( first_prog_flag == 0 )	//需要重新增加一条编程记录
	{
		first_prog_flag = 1;	//继续本次编程记录
		memcpy( Eeprom.Buffer+6, Opt, 4 );			//操作者代码(4)
		memcpy( Eeprom.Buffer+10, Dix, 4 );			//数据标识(4)
		memset( Eeprom.Buffer+14, 0xFF, 36 );			//不足的补0xFF(4*9)
		Event_Record(ee_programn_inpage);
	}
	else
	{
		memcpy( Eeprom.Buffer+50, Dix, 4 );			//数据标识(4)
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
	
	//更新RAM和E2中的客户编号
	ReadE2WithBackup( Page, Inpage, Buf, Temp08 );
	Exchange( Buf+(Start&0x1F), Para, Len );	//数据倒序
	result = WriteE2WithBackup( Page, Inpage, Buf, Temp08 );
	if( result ) return 1;
	
	memcpy( ptr, Buf, Temp08+2 );	//更新RAM
	return 0;
}


unsigned char JudgeSwitch( unsigned char *Buf, unsigned char Inv )
{
	unsigned char i, result;

	if( ChkBufZero(Buf,5)==0 ) return 2;//合法特殊时间(全0x00)
	
	for( i=0; i<5; i++ )
	{
		if( Buf[i] != 0x99 ) break;
	}
	
	if( i < 5 )
	{
		if( Inv ==1 )	Inverse( Buf, 5 );
		result = JudgeClockNoWeek( 1, Buf, 5 );
		if( Inv ==1 )	Inverse( Buf, 5 );
		return (result); //错误
	}
	else
	{
		return 3;		//合法特殊时间(全0x99)
	}
}

void JudgeSwitch2( unsigned char offset )//判断启动时间是否为全99,如果是则默认第一套
{
	I2C_Read_Eeprom44( ee_changecontrol_page, Eeprom.Buffer, ee_changecontrol_lenth);//读启动控制字节
	if( Eeprom.Buffer[ offset ] != 0xFF )
	{
		Eeprom.Buffer[ offset ] = 0xFF;
		I2C_Write_Eeprom44( ee_changecontrol_page, Eeprom.Buffer, ee_changecontrol_lenth ); //写启动控制字节
		Tariff.Crc16.B08[0] += 1;
		
		//进行约定冻结
		Freeze_Dl(ee_appointfreeze1_page+6*offset,3+offset);
	}
}

//时区/时段表编程记录
unsigned int ShiquRecord( unsigned char *InDi, unsigned char *InOpt )
{
	unsigned char i, n, Temp08, Ptr;
	union B16_B08_2 AddrA, AddrB;
	unsigned char Buf[64];
	
	if( InDi[0] == 0x00 )	//时区表
	{
		Ptr = ee_shiqun_inpage;
		AddrA.B16 = ee_shiqurecord_page;
		AddrB.B16 = ee_shiqu1_page;
	}
	else	//日时段表
	{
		Ptr = ee_shiduann_inpage;
		AddrA.B16 = ee_shiduanrecord_page;
		AddrB.B16 = ee_shiduantable1_1_page;
	}
		
	//历史记录(5,每字节代表2次)+发生时刻（6）+操作者代码（4）+ 时区表编程前第几套第1~14 时区表数据（3*14）
	//历史记录(5,每字节代表2次)+发生时刻（6）+操作者代码（4）+ 时段表编程前第几套第几 日时段表数据（3*14）
	Number_Add1( Ptr );	//时区/时段修改总次数+1(3)
	
	Temp08 = Read_Event_Point( Ptr );
	I2C_Read_Eeprom( AddrA.B16+Temp08, 70, Buf, 5 );	//历史记录(5,每字节代表2次)
	
	//i范围时区0～1,时段0～15
	if( InDi[2] == 1 )	i = 0;
	else
	{
		if( InDi[0] == 0 )	i = 1;	//时区表
		else i = 8;	//日时段表
	}
	if( InDi[0] ) i += (InDi[0]-1);			//计算得到第i个表被修改

	Temp08 = Write_Event_Point( Ptr );	//计算指针+1

	n = Temp08/2;
	if( Temp08%2 )	//历史记录(5,每字节代表2次)
		Buf[n] = (Buf[n]&0x0F)+(i<<4);		//记录对应字节的高4位
	else
		Buf[n] = (Buf[n]&0xF0)+i;			//记录对应字节的低4位
	
	memcpy( Buf+5, Sclock.Clockbackup, 6 );	//发生时刻(6)
	memcpy( Buf+11, InOpt, 4 );				//操作者代码(4)
	I2C_Read_Eeprom( AddrB.B16+i, 0x00, Buf+15, 42 );	//编程前 时区表or时段第i表(42)
	
	I2C_Write_Eeprom( AddrA.B16+Temp08, 70, Buf, ee_shiduanrecord_lenth );	//时区表
	
	return (AddrB.B16+i);
}


void JTRecord( unsigned char *InOpt )
{
	unsigned char i, Temp08;
	unsigned char Buf[ee_ladder_lenth+2];
	
	//--- 阶梯编程记录 ---
	memcpy( Eeprom.Buffer+6, InOpt, 4 );			//操作者代码(4)
	Temp08 = Event_Record( ee_jtpricen_inpage );

	for( i=0; i<4; i++ )
	{
		if( i < 2 ) I2C_Read_Eeprom( ee_ladder1_page+i, 0, Buf, ee_ladder_lenth);
		else I2C_Read_Eeprom( ee_ladder2_page+i-2, 0, Buf, ee_ladder_lenth);
		LoopInverse( Buf, 13, 4 );
		I2C_Write_Eeprom( ee_jtpricerecord2_page+4*Temp08+i, 0x00, Buf, ee_jtpricerecord2_len );
	}
	//--- 阶梯编程记录 end ---
}


unsigned char Set_Comm_Rate( unsigned char Ch, unsigned char Rate )
{
	switch( Ch )
	{
		case 0x01:	//调制型红外光口波特率特征字	NN  1
			if( Rate == 0x04 )	//1200bps
			{
				return 0;
			}
			break;
						
//		case 0x02:	//接触式红外光口波特率特征字    NN  1
//			Temp08 = 0x00;
//			break;
			
		case 0x03:	//通信口1 波特率特征字          NN  1
			if( (Rate == 0x04) || (Rate == 0x08) || (Rate == 0x10) || (Rate == 0x20) || (Rate == 0x40) )	//1200, 2400, 4800, 9600, 19200
			{
				UpdateBps = 1;	//波特率改变标志(规约处理置位)
				return(UpdateSysPara( 0x80+0, &Rate, 1 ));
			}
			break;
			
//		case 0x04:	//通信口2 波特率特征字          NN  1
//			if( (Rate == 0x20) || (Rate == 0x40) || (Rate == 0x01) )	//9600，19200，115200
//			{
//				UpdateBps = 1;	//波特率改变标志(规约处理置位)
//				return(UpdateSysPara( 0x80+31, &Rate, 1 ));
//			}
//			break;

		case 0x05:	//通信口3 波特率特征字          NN  1
//			if( (Rate == 0x04) || (Rate == 0x08) || (Rate == 0x10) || (Rate == 0x20) || (Rate == 0x40) || (Rate == 0x80) )	//1200, 2400, 4800, 9600, 19200, 38400
			if( (Rate == 0x04) || (Rate == 0x08) || (Rate == 0x10) || (Rate == 0x20) || (Rate == 0x40) )	//1200, 2400, 4800, 9600, 19200
			{
				UpdateBps = 1;	//波特率改变标志(规约处理置位)
				return(UpdateSysPara( 0x80+30, &Rate, 1 ));
			}
			break;
			
		case 0x85:	//通信口3 波特率特征字          NN  1	协商入口
//			if( (Rate == 0x04) || (Rate == 0x08) || (Rate == 0x10) || (Rate == 0x20) || (Rate == 0x40) || (Rate == 0x80) )	//1200, 2400, 4800, 9600, 19200, 38400
			if( (Rate == 0x08) || (Rate == 0x10) || (Rate == 0x20) || (Rate == 0x40) )	//2400, 4800, 9600, 19200
			{
				UpdateBps = 1;	//波特率改变标志(规约处理置位)
				Zb_Comm_Timer = Zb_Comm_Timer_delay;	//启动载波通讯波特率恢复定时器
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


//通过显示的数据标识和序号确定对应的屏编码
unsigned short GetLcdNo( unsigned char *LcdSn )
{
	unsigned char n, Temp08, Sn;
	unsigned short result;
	union B32_B08 Temp32;
	
	memcpy( Temp32.B08, LcdSn, 4 );
	Sn = LcdSn[4];

	//组合,正向,反向,组合无功1/2,第一象限无功电量~第四象限无功电量
	if( (Temp32.B08[3] == 0x00) 
	 && (Temp32.B08[2] <= 0x08) 
	 && (Temp32.B08[1] <= max_feilvcount) 
	 && (Temp32.B08[0] <= 0x0C) )
	{
		Temp08 = 0;		//最大序号是0
		result = 0x200; 	//普通电量
		result += ((Temp32.B08[2]&0x0f)*max_disploop+1)+Temp32.B08[1]+Temp32.B08[0]*(max_feilvcount+1);
	}
	else if( (Temp32.B08[3] == 0x00) 
//	 && ((Temp32.B08[2] >= 0x70)&&(Temp32.B08[2] <= 0x78))
	 && ((Temp32.B08[2] >= 0x60)&&(Temp32.B08[2] <= 0x68))//高精度显示修正
	 && (Temp32.B08[1] <= max_feilvcount) 
	 && (Temp32.B08[0] <= 0x0C) )
	{
		if( Temp32.B08[2] == 0x68 )  Temp32.B08[2] = 0x70;//高精度显示修正
		else Temp32.B08[2] += 0x11;
		
		Temp08 = 0;		//最大序号是0
		result = 0x800; 	//高精度电量
		Temp32.B08[2]-=0x70;	//高精度电量
		result += ((Temp32.B08[2]&0x0f)*max_disploop+1)+Temp32.B08[1]+Temp32.B08[0]*(max_feilvcount+1);
	}	
	//------ 其他显示项目，序号从200开始--------
	else
	{
		for( n=0; n<disp_num; n++ )
		{
			if( Byte2uInt(Temp32.B08) == disp_table[n] ) break;
		}
		
		if( n >= disp_num ) return 0x00;	//显示项目错误

		switch( n )	//确定最大序号
		{
			case 15:	//户号
			case 17:	//表号
			case 19:	//地址
			case 23:	//编程日期和时间
			case 25:	//清零日期和时间
				Temp08 = 1;		//最大序号是1
				break;
				
			case 0:	//全屏
				if( Sn != 0xFF ) 	return 0x00;	//显示项目错误

				Sn = 0x00;
				Temp08 = 0;		//最大序号是0
				break;
				
			default:
				Temp08 = 0;		//最大序号是0
				break;
		}
		
		result = 200+n+Sn;		//显示序号为HEX
	}

	if( Sn > Temp08 )		
		return 0x00;	//显示序号错
	else
		return (result);
}

unsigned char JudgeEndClock()	//截止时间合法性和有效性判断
{
	if( JudgeClockNoWeek( 0, Ic_Comm_RxBuf+2, 6 ) || (Cmp_Bcd_Inv( Ic_Comm_RxBuf+2, Sclock.Clockbackup, 6 )==2) )return 0x04; //错误
	else return 0x00; //成功
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
		
		result = JudgeEndClock();	//判断截至时间
		if( result ) return IC_FORMAT_ERR; //错误
	}

	return 0x00;
}


//0表示无记录,1表示有发生无结束,2记录完整
unsigned char ChkLastclockerrRcdTime( void )
{
	unsigned char result;
	unsigned char Buf[12];
	
   	if( RdRecTimes(ee_clockerrn_inpage) )
	{
		result = Read_Event_Point(ee_clockerrn_inpage);
		I2C_Read_Eeprom( ee_clockerrrecord_page+result, ee_clockerrrecord_inpage, Buf, 12 );	//时间  
		if( ChkBufZero(Buf+6,6) == 0 ) return 1;   //表示有发生无结束
		else return 2;//记录完整
	}
	else  return 0;  //表示无记录   
}


void CommSetRtc_Adj()
{	
	unsigned char Buf[8];
	
	memcpy( Buf, Sclock.Clockbackup, 6 );	//备份校时前时钟
	
	Read_Rtc( Sclock.Clockmain );//读时钟
	Syn_Clock();	//同步时钟
	
	if( Cmp_Bcd_Inv( Buf, Sclock.Clockbackup, 6 ) == 1 )
	{
		ClearPloadRec( Sclock.Clockbackup );
	}
	
	if( Cmp_Data( Buf+3, Sclock.Clockbackup+3, 3 ) != 3 )	//日期发生变化
	{
		unsigned char Result;
		
		Clr_Zero_Data();	//跨天清零相关数据
		
		//日电压合格率记录
		CalLoad( Eeprom.Buffer, 0 );
		Result = Write_Event_Point(ee_dayvolpassn_inpage);
		I2C_Write_Eeprom( ee_dayvolpass_note_page+Result/4, ee_dayvolpassnote_inpage+(Result%4)*ee_dayvolpassnote_len, Eeprom.Buffer, ee_dayvolpassnote_len );
		InitVolSts( 0 ); //清除对应的电压合格率
		
		if( Buf[5] != Sclock.Clockbackup[5] ) //年改变
		{
			month_change_flag = 1;
			year_change_flag = 1;
			year_change_flag2 = 1;
		}
		else if( Buf[4] != Sclock.Clockbackup[4] ) //月改变
		{
			month_change_flag = 1;
		}
		if( month_change_flag ) //月电压合格率记录转存
		{
			//月电压合格率记录
			CalLoad( Eeprom.Buffer, 1 );
			Result = Write_Event_Point(ee_monvolpassn_inpage);
			I2C_Write_Eeprom( ee_monvolpass_note_page+Result/4, ee_monvolpassnote_inpage+(Result%4)*ee_monvolpassnote_len, Eeprom.Buffer, ee_monvolpassnote_len );
			InitVolSts( 1 ); //清除对应的电压合格率
		}	
		Freeze_Pddata();	//冻结掉电数据		
	}
	
	run_timezone_flag = 1;
	Tariff.Crc16.B08[0] += 1;
	RefreshPrice();
	run_readrtc_flag = 1;
	
	Wr_Powerdown_Data(0);//写掉电相关数据到数据ee
	Wr_Pretime_Hisfreeze();	//写上一次结算时间
	Wr_Pretime_Dayfreeze();	//写上一次日冻结时间
	
	if( ChkLastclockerrRcdTime() == 1 ) Note_Run_Event(ee_clockerrn_inpage|0x80); //时钟故障结束记录(时钟合法)
}


unsigned char CommSetRtc( unsigned char Ch, unsigned char Start, unsigned char Len )
{
	unsigned char result;
	unsigned char Buf[8];
	
	result = Judge_Clock( Start, &Uart[Ch].Buf[22], Len ); //判断数据是否合法
	if( result != 0 ) return 1; //设置值错误
	
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
		Read_Rtc( Buf );//读时钟
	}
	
	memcpy( Buf+Start, Uart[Ch].Buf+22, Len );
	
	Buf[3] = (CalcAbsDay(Buf+2)+6)%7;	//计算周,格式为秒+分+时+周+日+月+年,起始地址周,从日开始计算

	result = Set_Rtc( 0, Buf, 7 ); //
	if( result != 0 ) return 2; //设置RTC失败
	
	memcpy( Uart[Ch].Buf+18+4, Sclock.Clockbackup, 6 );	//校时前时间(6)(临时保存)
	
	CommSetRtc_Adj();	//设置时钟调整相关数据
	
	memcpy( Eeprom.Buffer, Uart[Ch].Buf+18, 4 );		//操作者代码(4)
	memcpy( Eeprom.Buffer+4, Uart[Ch].Buf+18+4, 6 );	//校时前时间(6)
	memcpy( Eeprom.Buffer+10, Sclock.Clockbackup, 6 );	//校时后时间(6)
	DltoEepromBuf( 16 );					//读正向电量+反向电量
	Four_RpdltoEepromBuf( 16+8 );				//读四象限无功
	Event_Record( ee_setclockn_inpage );
	
	return 0;
}


unsigned char Judge_Min_Space( unsigned char *bufA )
{				
	unsigned char result,Temp08;
	unsigned char Buf[16];
	
	memcpy( Buf+0, bufA, 6 ); //需要判断的时间
	memcpy( Buf+6, Sclock.Clockbackup, 6 ); //当前时间
	
	Temp08 = Cmp_Bcd_Inv( Buf+0, Buf+6, 6 ); 
	switch( Temp08 )
	{
		case 0x01: //时间 > 当前时间
			Add_Min_Clock( Buf+6, 10 ); //对当前时间做加5分钟处理
			break;
			
		case 0x02: //时间 < 当前时间
			Add_Min_Clock( Buf+0, 10 ); //对时间做加5分钟处理
			break;
			
		default:
			break;
	}
	
	if( Temp08 )
	{
		result = Cmp_Bcd_Inv( Buf+0, Buf+6, 6 );
		if( result == Temp08 ) //超过5min限制
		{
			return 1;	//超过5min限制
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

	LoopInverse( Uart[Ch].Buf+18, 3, 8 ); //密文1+随机数1+分散因子

	if( Uart[Ch].Buf[34] || Uart[Ch].Buf[35] ) return 1;
	if( Cmp_Meter_Id(Uart[Ch].Buf+36) ) return 1;

	if( Authorization( Uart[Ch].Buf+18, 4 ) ) return 8; //身份认证失败

	memcpy( PcRand,  Uart[Ch].Buf+26, 8 );	//随机数, 8bytes 
	memcpy( PcRst8B, Uart[Ch].Buf+34, 8 );	//分散因子, 8bytes

	first_prog_flag = 0;	//清首次编程标志

	//返回信息: 随机数2+ESAM序列号
	Exchange( OutBuf+1, EsamRand, 4 );	//随机数2, 4bytes
	Exchange( OutBuf+5, EsamRst8B, 8 );	//ESAM序列号, 8bytes
	return 0;
}

//验证通过后按照明文定义的指令执行相应操作
/*Ch:
	0x14：用户卡远程模式下的合闸命令，无操作者代码，需解密
	0x24~0x26：远程终端的合闸命令，有操作者代码，需解密
	0x20~0x22：96级远程控制继电器命令，有操作者代码，需解密
	0x00~0x02：03级远程控制继电器命令，有操作者代码，无解密
*/
unsigned char Relay_Ctrl(unsigned char Ch)
{
	unsigned char Temp08;
	
	if(Ch >= 0x10) //除03级密码，其它都需要解密
	{
		Temp08 = Decrypt( Ch&0x0f, 0x87, 0x08 );
		if( Temp08 ) return(Temp08);
	}
	
	//验证通过后按照明文定义的指令执行相应操作
	Temp08 = 0x00;
	switch( Ic_Comm_RxBuf[0] )	//N1
	{
		case 0x1A:	//代表跳闸
			if(relay_commu_close_flag == 1) {Temp08 = 0x04;break;}
			relay_commu_open_flag = 1;
			
			if( relay_status_flag )
			{
				Opendelaytimer = 0;	//已经跳闸了就不要再等延时
			}
			else Opendelaytimer = Calculate_Timer(0);
			
			if( over_xxx_flag && (CurrentTimer || (relay_status_flag==0)) ) CurrentTimer = Calculate_Timer(1); //处于大电流延时拉闸则重新启动
			
			relay_commu_disable_close_flag = 0;
			relay_commu_close2_flag = 0;	//清保电解除标志
					
			break;

		case 0x1B:	//代表合闸允许
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
			
		case 0x1C:	//直接合闸，
			Clr_Commu_Relaydata();
			Enable_Closerelay();
			break;

		case 0x2A:	//代表报警，
			relay_commu_alarm_flag = 1;
			Temp08 = 0xff;
			break;

		case 0x2B:	//代表报警解除，
			relay_commu_alarm_flag = 0;
			Temp08 = 0xff;
			break;

		case 0x3A:	//代表保电，
			relay_commu_close_flag = 1;
			Clr_Commu_Relaydata();
			if(Relay_Mode != 0x55)//内置继电器
			{
				if( relay_status_flag == 1 )
				{
					relay_commu_disable_close_flag = 1;//插卡才能闭合继电器
				}
			}
			break;

		case 0x3B:	//代表保电解除。
			if( relay_commu_close_flag ) relay_commu_close2_flag = 1;//置保电解除标志
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
		if( (Temp08 != 0xff) && (Ch != 0x14) ) I2C_Write_Eeprom(ee_operatorcode_page, ee_operatorcode_inpage, &Uart[Ch&0x03].Buf[14], 4);//操作者代码写数据ee
		
		if( Ic_Comm_RxBuf[0] == 0x1B || Ic_Comm_RxBuf[0] == 0x1C || Ic_Comm_RxBuf[0] == 0x3A )
		{
			if( Relay_Mode == 0x55 ) relay_cleardl_flag = 0; //清外置表刚清零标志
		}
				
		Store_Meterstatus();	//保存电表状态字节
		
		return 0;
	}
}

//读取钱包文件：
//Type = 1：读记录文件
//Type = 2：带MAC读取钱包文件
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

//远程身份认证/交互终端身份认证有效判断
unsigned char Comm_Auth_Judge( void )
{
	if( identity_prog_flag ) return 1;
	else return 0;
}

//修改蓝牙相关参数，复位蓝牙模块
void Ble_Rst_Judge(uint08 Ch)
{
	if( Ch == CHBLE ) Ble_Reset = 0x55;	//应答后再复位
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
	
	if( EA_OFF ) return;//掉电不处理,程序直接返回
	
	Uart[Ch].Flag &= ~(B0000_0100);
	
	Adj_Clk_Timer = Adjclk_timer_delay;	//重新启动定时8M时钟调校功能
	
	if( Ch==CHZB )
	{
		if( Zb_Comm_Timer ) Zb_Comm_Timer = Zb_Comm_Timer_delay;	//继续启动载波通讯波特率恢复定时器
		
		Mod_Comm_Timer1 = Mod_Comm_Timer_delay1;	//启动通信模块超时定时器
		Mod_Comm_Timer2 = 0;				//通信模块异常延时定时器清零
		if( commmodule_failed_flag )
	 	{
	 		commmodule_failed_flag = 0;		//清通信异常标志
	 		Store_Meterstatus();
	 		Note_Run_Event(ee_commerrn_inpage|0x80);//通信异常事件结束
	 	}
	 }
	 
	ble_inter_flag = 0;
	if( Ch==CHBLE ) 
	{
		if( Uart[Ch].Buf[3] == 0xFF )  ble_inter_flag = 1;//蓝牙内部命令
			
		if( Ble_Step == 1 ) Ble_Step = 0;
		Ble_RstTimer = Zb_Comm_Timer_delay;	//启动蓝牙复位定时器
	}
	
	if( (Uart[Ch].Buf[8]&B1000_0000) && !ble_inter_flag )	//通讯bit7=1的命令码电表均不响应
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
	
	if( (Ch == CHHW) && (progenable==0) )	//红外通信口
	{
		Temp08 = 0xFF;	//默认不允许抄读
			
		if( (Uart[Ch].Buf[8] >= 0x11 && Uart[Ch].Buf[8] <= 0x13) || (Uart[Ch].Buf[8] == 0x1f) )
		{
			Temp08 = 0x00;
		}
		else if( Uart[Ch].Buf[8] == 0x1c )
		{
			Temp08 = 0x00;
		}
		
		if( Temp08 )	//不允许抄读
		{
			Uart[Ch].Buf[8] |= 0x40; //返回1字节04错误
		}
	}
	
	if( (Ch == CHBLE) && (progenable==0) && (Ble_Buf[3]!=0xFF) )	//蓝牙通信口
	{
		if( IR_EnTimer == 0 )	//红外认证失效
		{
			Temp08 = 0xFF;	//默认不允许抄读
			
			if( (Uart[Ch].Buf[8] == 0x03) && ((DI07.B32 == 0x078003FF) || (DI07.B32 == 0x070003FF)) )	//红外认证请求、红外认证除外
			{	
				Temp08 = 0x00;
			}
			else if( Uart[Ch].Buf[8] == 0x11 )
			{
				switch( DI07.B32 )
				{
					case 0x04000101:	//当前日期
					case 0x04000102:	//当前时间
					case 0x0400010C:	//当前时钟
					case 0x02010100:	//电压
					case 0x0201ff00:	//电压（A相）
					case 0x02020100:	//电流
					case 0x0202ff00:	//电流（A相）
					case 0x02800001:	//零线电流
					case 0x02800002:	//频率
					case 0x02800003:	//一分钟平均有功功率
					case 0x02800025:	//一分钟平均无功功率
					case 0x02030000:	//有功功率（总）
					case 0x02030100:	//有功功率（A相）
					case 0x0203ff00:	//有功功率（集合）
					case 0x02040000:	//无功功率（总）
					case 0x02040100:	//无功功率（A相）
					case 0x0204ff00:	//无功功率（集合）
					case 0x02060000:	//功率因数（总）
					case 0x02060100:	//功率因数（A相）
					case 0x0206ff00:	//功率因数（集合）
					case 0x0290FF00:	//功率集合
					case 0x04000401:	//通信地址--
					case 0x04000402:	//表号
					case 0x0400040e:	//户号
					case 0x02800086:	//当前阶梯
					case 0x000B0000:	//当前结算用电量
					case 0x00D0FF00:	//电量集合
						Temp08 = 0x00;
						break;
						
					default: 
						if( (DI07.B08[3]==0) && (((DI07.B08[2]&0x0f)<=8)||((DI07.B08[2]>=0x15)&&(DI07.B08[2]<=0x1C))) && ((DI07.B08[1]<=Bcd_To_Hex(Feik.Num[3]))||(DI07.B08[1]==0xFF)) && (DI07.B08[0]==0) )
						{
							Temp08 = 0x00;
						}
						else if( (DI07.B08[3]==0) && (((DI07.B08[2]==0x0b)||DI07.B08[2]==0x0c)||(DI07.B08[2]==0x50)) && (DI07.B08[1]==0) && (DI07.B08[0]<=max_histroy_p) ) //当前/1~24月度用电量
						{
							Temp08 = 0x00;
						}
						else if( (Uart[Ch].Buf[9] == 0x11)||(Uart[Ch].Buf[9] == 0x07) ) 
						{
							Temp08 = 0x00;	//校表
						}
						else if( DI07.B32 == 0x0E800009 ) 
						{
							Temp08 = 0x00;	//退出蓝牙校表
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
			
			if( Temp08 )	//不允许抄读
			{
				if( (Uart[Ch].Buf[8] == 0x03) ) DI07.B08[3] = 0xff;//返回2字节错误
				else Uart[Ch].Buf[8] |= 0x40; //返回1字节04错误
			}
		}
	}
	
	Successled.Timer = 5+1;	//点灯5s

	k = 0x00;
	OutBuf[0] = 0x00;
	switch( Uart[Ch].Buf[8] ) //cmd
	{
		case 0x03:	//安全认证
			if( (Uart[Ch].Flag&B0000_0001) ||
			((Uart[Ch].Flag&B0000_0010)&&(Byte2uInt(DI07.B08)!=0xFF018007)&&(Byte2uInt(DI07.B08)!=0xFF028007)&&(Byte2uInt(DI07.B08)!=0xFF028107)&&(Byte2uInt(DI07.B08)!=0xFF038007)) )
			{
				OutBuf[ k++ ] = 0xFF;	//Operation result.
				OutBuf[ k++ ] = 0x01;
				OutBuf[ k++ ] = 0x00;
				break;
			}
			
			//注3：密码权限04代表通过明文的方式进行数据传输，需要进行密码验证，同时要有编程键配合。
			//注4：密码权限99代表通过明文+MAC的方式进行数据传输，不需要进行密码验证，也不需要编程键配合使用。
			//注5：密码权限98代表通过密文+MAC的方式进行数据传输，不需要进行密码验证，也不需要编程键配合使用。

			//--------------------------- 安全认证错误信息字 SERR ---------------------------------------------
			//Bit7 | Bit6       | Bit5         | Bit4           | Bit3         | Bit2          | Bit1     | Bit0     |
			//保留 | 购电超囤积 | 充值次数错误 | 客户编号不匹配 | 身份认证失败 | ESAM 验证失败 | 重复充值 | 其它错误 |
			//Bit15 Bit14 Bit13 Bit12 Bit11 Bit10 Bit9 Bit8
			//保留 保留 保留 保留 保留保留保留保留	
			//注 1：0 代表无相应错误发生，1 代表相应错误发生。
			//注2：当表内已充值次数比充值指令中充值次数小1 时，为正常充值。充值完成后表内已充值次数加1；当
			//表内已充值次数和充值指令中充值次数相等时，该充值已完成，充值错误为重复充值。除以上两种情
			//况外，为充值次数错误。
			//注3：身份认证失败和身份认证超时统称为身份认证失败，需要重新进行身份认证。

			//68H A0 … A5 68H 03H L DIO … DI3 C0 … C3 N1 … Nm CS 16H
			switch( DI07.B08[3] )
			{
				case 0x07:	//
					switch( DI07.B08[2] )
					{
						case 0x00:	//身份认证指令
							switch( DI07.B08[1] )
							{
								case 0x00:	//身份认证
									switch( DI07.B08[0] )
									{
//										case 0x01:	//密文1, 8bytes	[18]~[25]
//										case 0x02:  //随机数1, 8bytes	[26]~[33]
//										case 0x03:  //分散因子, 8bytes	[34]~[41]
										case 0xFF:  //身份认证指令: 密文1+随机数1+分散因子
											//68+表号+68+03+20+FF000007+操作者代码+密文1(8)+随机数1(8)+分散因子(8)+CS+16
											result = Yc_Auth(Ch, OutBuf);
											if( result )
											{
												k = 0x00;
												OutBuf[ k++ ] = 0xFF;
												OutBuf[ k++ ] = result;	//身份认证失败
												OutBuf[ k++ ] = 0x00;
												break;
											}
											
											Identitytimer = Calculate_Timer(0xff);//计算身份认证时效
											identity_prog_flag = 1;	//置位 安全认证编程标志
																			
											k = 13;
											break;

										default:
											break;
									}
									break;
									
								case 0x01:	//身份认证时效设置
									switch( DI07.B08[0] )
									{
//										case 0x01:	//身份认证有效时长(分钟), 2bytes, BCD
//										case 0x02:	//MAC, 4bytes
										case 0xFF:
											//68+表号+68+03+0E+FF010007+操作者代码+2字节认证时效时间+MAC+CS+16
											//1.在没有设置安全认证时效参数前，默认为5分钟。
										
											//密钥信息文件1 0005 自由 身份认证+MAC
											//参数修改命令：04d68200+LC+分散因子+参数+MAC；LC 为分散因子＋参数＋MAC 的总长度，它是1字节的十六进制数。
											if( hangup_comm_flag )
											{
												k = 0x00;  
												OutBuf[ k++ ] = 0xFF;	//Operation result.
												OutBuf[ k++ ] = 0x00;
												OutBuf[ k++ ] = 0x01;	//远程安全认证锁住状态位
												break;
											}
											
											if( !identity_prog_flag )
											{		
												k = 0x00;
												OutBuf[ k++ ] = 0xFF;
												OutBuf[ k++ ] = 0x08;	//身份认证失败
												OutBuf[ k++ ] = 0x00;
												break;
											}
											
											if( (Uart[Ch].Buf[18]==0x00) && (Uart[Ch].Buf[19]== 0x00) )	//安全认证时效不能写入0，若写入0则返回失败。
											{
												break;
											}
											
											if( IsMultiBcd( Uart[Ch].Buf+18, 2 ) ) break;

											result = Update_ESAM_Bin_Mac( 0x81, 0x2B, &Uart[Ch].Buf[18], 2 );
											if( result != 0x00 ) 
											{
												k = 0x00;
												OutBuf[ k++ ] = 0xFF;
												OutBuf[ k++ ] = 0x04;	//ESAM验证失败
												OutBuf[ k++ ] = 0x00;
												break;
											}
											
											result = UpdateSysPara( 0x40+24, Uart[Ch].Buf+18, 2 ); //更新XRAM, E2PROM
											if( result ) break;
											
											Identitytimer = Calculate_Timer(0xff);//计算身份认证时效

											ProgramRecord( DI07.B08, OptID.B08 );
											
											//正确：68+表号+68+83+04+FF010007+CS+16
											k = 1;
											break;
											
										default:
											break;
									}
									break;
									
								case 0x02:	//身份认证失效
									switch( DI07.B08[0] )
									{
										case 0xFF:
											if( !identity_prog_flag )
											{		
												k = 0x00;
												OutBuf[ k++ ] = 0xFF;
												OutBuf[ k++ ] = 0x08;	//身份认证失败
												OutBuf[ k++ ] = 0x00;
												break;
											}
											
											//客户编号
											result = ReadBinFile( ESAM, 0x81, 36, 6 );
											if( result != 0x00 ) break;

											Exchange( OutBuf+1, Ic_Comm_RxBuf, 6 );
											
											result = Get_Money_File(1, OutBuf+7);	//读取钱包文件
											if( result != 0x00 ) break;
						
											//密钥信息
											GetKey( OutBuf+15 );
										
											//身份认证失效
											Clear_Rand_Gene();
											
											k = 19;
											break;
											
										default:
											break;
									}
									break;
									
								case 0x03:	//红外认证命令, 红外认证成功后30分钟内有效, 该先于身份认证完成
									switch( DI07.B08[0] )
									{
										case 0xFF:
											if( (Ch!=CHBLE) &&(progenable==0) ) break; //只允许蓝牙通信口
											if( identity_ir_flag == 0 ) break; //没有红外请求
											
											//随机数2密文
											//红外认证成功后30分钟内有效。
											Inverse( Uart[Ch].Buf+18, 8 );	//密文2

											result = Auth_In_Out(0x82, ESAM, 0x10, Uart[Ch].Buf+18 );//卡片做外部认证
											if( result )
											{
												{IR_EnTimer = 0;identity_ir_flag = 0;}
												k = 0x00;
												OutBuf[ k++ ] = 0xFF;
												OutBuf[ k++ ] = 0x04;	//ESAM验证失败
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
									
								case 0x04:	//明文写信息文件
								case 0x05:	//密文写信息文件
									//68+表号+68+03+L+FF050007+操作者代码+文件编号+偏移地址+明文(密文)+MAC+CS+16
									if(DI07.B08[0] != 0xff) break;
									if( Uart[Ch].Buf[9] <= 15 ) break;//数据长度必须大于15
										
									if( hangup_comm_flag )
									{
										k = 0x00;  
										OutBuf[ k++ ] = 0xFF;	//Operation result.
										OutBuf[ k++ ] = 0x00;
										OutBuf[ k++ ] = 0x01;	//远程安全认证锁住状态位
										break;
									}
									
									if( !identity_prog_flag )
									{		
										k = 0x00;
										OutBuf[ k++ ] = 0xFF;
										OutBuf[ k++ ] = 0x08;	//身份认证失败
										OutBuf[ k++ ] = 0x00;
										break;
									}
																		
									result = SelectFile( ESAM, 0x00, Uart[Ch].Buf[18] );//选择文件(明文：18，1A,1B,1C; 密文:0B,15)
									if(result) break;
										
									result = Update_ESAM_Bin_Mac(Uart[Ch].Buf[20], Uart[Ch].Buf[19], Uart[Ch].Buf+21, Uart[Ch].Buf[9]-15 );
									if(result)
									{
										k = 0x00;
										OutBuf[ k++ ] = 0xFF;
										OutBuf[ k++ ] = 0x04;	//ESAM验证失败
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
						
						case 0x03:	//密钥更新命令
							if( (DI07.B08[1] != 0x01) || (DI07.B08[0] != 0xFF) )
							{
								break;
							}

							if( hangup_comm_flag )
							{
								k = 0x00;  
								OutBuf[ k++ ] = 0xFF;	//Operation result.
								OutBuf[ k++ ] = 0x00;
								OutBuf[ k++ ] = 0x01;	//远程安全认证锁住状态位
								break;
							}  
							
							if( !identity_prog_flag )
							{		
								k = 0x00;
								OutBuf[ k++ ] = 0xFF;
								OutBuf[ k++ ] = 0x08;	//身份认证失败
								OutBuf[ k++ ] = 0x00;
								break;
							}
							
							result = UpdateEepromKey( Ch );
							if( result ) //电表应错误应答，主站应启动密钥重装流程
							{
//								FailKey();	//更新密钥失败处理
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
							
						case 0x80:	//数据回抄
							switch( DI07.B08[1] )
							{
								case 0x01:	//
									switch( DI07.B08[0] )
									{
										case 0xFF:	//数据回抄标识, 8字节,
											//返回的数据: 8+Le+4字节, [7:0]数据回抄标识; [7+Le:8]返回的数据; [8+Le+3:8+Le]MAC
						
											//数据回抄命令：采取文件名的方式：
											//81,读取剩余金额和购电次数：
											//回抄剩余金额：04b2010C11+4 字节随机数+04d681000A+8 字节分散因子；
											//回抄购电次数：04b2030C11+4 字节随机数+04d681040A+8 字节分散因子。
											//82—85，读取相应ESAM 二进制文件数据：
											//04b082（83，84，85）+ p2(偏移地址)＋11+4 字节随机数1+04d683+00+LC+8 字节分散因子。
											//LC 是所要读取的明文数据＋MAC+分散因子的总长度，它是1 字节的十六进制数。

											if( (!identity_prog_flag)&&(!progenable) )
											{		
												k = 0x00;
												OutBuf[ k++ ] = 0xFF;
												OutBuf[ k++ ] = 0x08;	//身份认证失败
												OutBuf[ k++ ] = 0x00;
												break;
											}
											
											//发送目录选择到ESAM
											if( (Uart[Ch].Buf[25] != 0xDF) || (Uart[Ch].Buf[24] != 0x01) ) break;

//											result = SelectFile( ESAM, 0xDF, 0x01 );
//											if( result != 0x00 ) break;	//

											if( Uart[Ch].Buf[22] != 0x02 )	//除钱包文件以外的其它文件
											{
												if( Uart[Ch].Buf[18] > 200 ) break;	//645规定读取字符不超过200个
												
												//发送：04b082(83,84,86)+p2+11+S4+04D686+P2+LC+8字节分散因子
												//返回：61 XX
												//发送：00C0000008
												//返回：Data+MAC
												
												if( Uart[Ch].Buf[22] == 0x06 ) UpdataRunFile();//更新运行文件
												
												result = ReadBinWithMac( ESAM+0x10, (Uart[Ch].Buf[22]|0x80), Uart[Ch].Buf[20], Uart[Ch].Buf[18]+4 );
												if( result != 0x00 ) break;
												
												MacExchange( OutBuf+9, Ic_Comm_RxBuf, Uart[Ch].Buf[18] );
												
												k = Uart[Ch].Buf[18]+13;
												memcpy( OutBuf+1, Uart[Ch].Buf+18, 8 );
												
											}
											
											else	//读取剩余金额和购电次数
											{
												//剩余金额(ESAM 内), 4bytes.
												//购电次数（ESAM 内）, 4bytes.
												result = Get_Money_File(2, OutBuf+9);
												if( result != 0x00 ) break;
	
												//返回状态信息:
												k = 25;
												memcpy( OutBuf+1, Uart[Ch].Buf+18, 8 );
											}
											break;
											
										default:
											break;
									}
									break;
									
								case 0x02:	//数据比对
									switch( DI07.B08[0] )
									{
										case 0xFF:
											if( !identity_prog_flag )
											{		
												k = 0x00;
												OutBuf[ k++ ] = 0xFF;
												OutBuf[ k++ ] = 0x08;	//身份认证失败
												OutBuf[ k++ ] = 0x00;
												break;
											}
											
											//判断cpu编号
											if( Uart[Ch].Buf[18] != 0x00 ) break;
											if( (Uart[Ch].Buf[28]==0) || (Uart[Ch].Buf[28]>4) ) break;//比对数据长度特征量1--4
											
											Temp08 = Uart[Ch].Buf[28];
											Clear_Wdt();
											
											//判断地址是否异常和准备数据
											for( i=0; i<2; i++ )
											{
												if( i== 0 ) {Temp16.B16 = 16; Ptr = ChangeBuf;}	//比对因子
												else {Temp16.B16 = 256*Temp08; Ptr = OutBuf;}	//比对数据
												
												Temp32.B32 = 0;
												memcpy( Temp32.B08, Uart[Ch].Buf+20+4*i, 4);	//比对因子起始地址
												Code_Flash_Char = (unsigned char ecode *)Temp32.B32;
												if( (Temp32.B32 > PROGRAMEND1) || Uart[Ch].Buf[23] || Uart[Ch].Buf[27] )
												{
													break;		//地址异常
												}
												
												if( (Temp32.B32+Temp16.B16 > (PROGRAMEND1+1)) )	//结束地址补0x80
												{
												  	memset( Ptr, 0x00, Temp16.B16);
												  	memcpy( Ptr, Code_Flash_Char, PROGRAMEND1+1-Temp32.B32 );
												   	Ptr[PROGRAMEND1+1-Temp32.B32] = 0x80;
												}
												else if( (Temp32.B32 < (PROGRAMPROZ)) && (Temp32.B32+Temp16.B16 > (PROGRAMPROZ)) )	//到保护区地址补0x80
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
												OutBuf[ k++ ] = 0x80;	//地址异常
												OutBuf[ k++ ] = 0x00;
												break;
											}
                									
											//读ROM数据,计算密文
											Xor_Data( ChangeBuf, ChangeBuf+8, 8 );//得到比对因子
											result = Auth_In_Out(0xfa, ESAM, Uart[Ch].Buf[19], ChangeBuf );//生产比对密钥
											if( result ) break;
											
											for( i=1; i<(4*Temp08); i++ )
											{
												Xor_Data( OutBuf, OutBuf+64*i, 64 );//得到data1
											}
											result = Cal_Mac_Pro(0x00, OutBuf, 64); //ESAM加密data1(可能需要输入长度)
											if( result ) break;
											
											Exchange(OutBuf+1, Ic_Comm_RxBuf, 64);	//数据取反,返回加密数据
											
											k = 65;
											OutBuf[0] = 0x00;
											break;
											
										default:
											break;
									}
									break;

								case 0x03:	//红外认证请求
									switch( DI07.B08[0] )
									{
										case 0xFF:	//随机数1, 8字节,
											if( (Ch!=CHBLE)&&(progenable==0) ) break; //只允许蓝牙通信口
										
											//返回信息: 表号(8)+ESAM序列号(8)+随机数1密文(8)+随机数2(8)
											result = Clear_Rand_Gene(); //Esam Reset
											if( result != 0x00 ) break;	

											Buf[16] = 0x00;
											Buf[17] = 0x00;
											memcpy( Buf+18, Esam_Para.Meter_Id, 6 );
											Exchange( Buf+8, Uart[Ch].Buf+18, 8 );	//随机数1
											result = Authorization( Buf, 8 );
											if( result ) break;
											
											//返回信息: 表号 ESAM序列号 随机数1密文 随机数2
											Exchange( OutBuf+1, Esam_Para.Meter_Id, 6 );//表号, 6bytes
											Exchange( OutBuf+7, EsamRst8B, 8 );	//ESAM序列号, 8bytes
											Exchange( OutBuf+15, Buf, 8 );	//随机数1密文, 8bytes
											Exchange( OutBuf+23, EsamRand, 8 );	//随机数2, 8bytes
											
											identity_ir_flag = 1;	//置红外请求标志

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
							
						case 0x81:	//状态查询
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
												OutBuf[ k++ ] = 0x08;	//身份认证失败
												OutBuf[ k++ ] = 0x00;
												break;
											}
											
											//返回信息: 剩余金额（ESAM 内）+ MAC + 购电次数（ESAM 内）+ MAC + 客户编号 + 密钥信息
											result = Get_Money_File(2, OutBuf+1);
											if( result != 0x00 ) break;
						
											//客户编号,	6bytes
											result = ReadBinFile( ESAM, 0x81, 36, 6 );
											if( result != 0x00 ) break;

											Exchange( OutBuf+17, Ic_Comm_RxBuf, 6 );
						
											//密钥信息, 4bytes.							
											GetKey( OutBuf+23 );
											
											//返回状态信息:
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
				//错误：68+表号+68+C3+02+SERR+CS+16
				OutBuf[ k++ ] = 0xFF;	//Operation result.
				OutBuf[ k++ ] = 0x01;
				OutBuf[ k++ ] = 0x00;
			}
			break;
			
		//=====================================================================================	
		case 0x06: //主动上报响应命令
 			if(  (Uart[Ch].Flag & B0000_0011) || //不支持通信地址为广播和全AA
 				(Ch != CHZB) ||  (Uart[Ch].Buf[9] < 4) || (((ReportList[0]&B0011_1100) == 0)&&(Uart[CHZB].RptTimer == 0)) )
 			{
				Uart[Ch].Overtime_Timer = 2;
				return;
 			}
	
			Report_Response( DI07 );	//上报响应处理
			
			Uart[Ch].Overtime_Timer = 2;
			return;

		//====================================================================================
		case 0x14: //写参变量
			if( ((Uart[Ch].Flag & B0000_0011)==0)&&(Byte2uInt(DI07.B08) == 0x03150004)&&(Reset_Rep_Timer) )//复位主动上报状态字
 			{
 				if( Uart[Ch].Buf[9] != 24 ) break;
 				
 				//修正上报状态字
				if( (Uart[Ch].Buf[22+2]&B1000_0000)==0 ) Uart[Ch].Buf[22+2] |= B1000_0000;//掉电临时借用存A相断相
				if( (Uart[Ch].Buf[22+8]&B0010_0000)==0 ) Uart[Ch].Buf[22+2] &= B0111_1111;
				if( (Uart[Ch].Buf[22+2]&B0000_0100)==0 ) Uart[Ch].Buf[22+2] |= B0000_0100;//低电压临时借用存A相欠压
				if( (Uart[Ch].Buf[22+3]&B0010_0000)==0 ) Uart[Ch].Buf[22+2] &= ~B0000_0100;
				if( (Uart[Ch].Buf[22+2]&B0000_0010)==0 ) Uart[Ch].Buf[22+2] |= B0000_0010;//高电压临时借用存A相过压
				if( (Uart[Ch].Buf[22+3]&B0001_0000)==0 ) Uart[Ch].Buf[22+2] &= ~B0000_0010;
 				
 				for( i=0,n=0; i<5; i++,n++ )
				{
					Temp08 = (Report_Data[i]^Report_Data2[i]);
					if( Temp08 && ((Temp08&Uart[Ch].Buf[22+n]) != Temp08) )  break;//存在30min内新的上报,并且通讯复位新增上报	
					if( i==2 ) n = 9;
				}
				if( i < 5 )
				{
					k = 2;
 					OutBuf[0] = 0xFF;	//Operation result.
 					OutBuf[1] = 0x04;	//Error: bit2密码错误/未授权
					break;//存在30min内新的上报,并且通讯复位新增上报
				}
 				
 				for( i=0,n=0; i<5; i++,n++ )
				{
					Report_Data[i] &= Uart[Ch].Buf[22+n];//复位上报状态字
					if( i==2 ) n = 9;
					
					Clr_Reportnum(i);	//清零上报新增次数
					Reset_Rep_Timer = 0;
				}
 				k = 1;
				break;
 			}
 			if( ((Uart[Ch].Flag & B0000_0011)==0) &&(Byte2uInt(DI07.B08) == 0x0f040004)&&(Uart[Ch].Buf[14] == 0x03)&&(Veri_Psw( Uart[Ch].Buf+14 )==0) )//电能表位置信息
 			{
 				Temp16.B08[0] = ee_meterpos_page;//电能表位置信息
				Temp16.B08[1] = ee_meterpos_inpage;
				Temp08 = 11;
										
				if( Uart[Ch].Buf[9] != (Temp08+12) ) break;//数据长度错误
				I2C_Write_Eeprom( Temp16.B08[0], Temp16.B08[1], Uart[Ch].Buf+22, Temp08 );
				
				ProgramRecord( DI07.B08, Uart[Ch].Buf+18 );
				
				k = 1;
				break;
 			}
 			
 			if(  (Uart[Ch].Flag & B0000_0011) || //不支持通信地址为广播和全AA
 				( DI07.B08[3] != 0x04 ) ||	//用户对不支持写操作的数据项编程
 				( Uart[Ch].Buf[14] == 0x04 ) ||	//不支持04级密码
 				((Uart[Ch].Buf[14] == 0x03 ) && (!progenable)) || //03级：编程禁止
 				((Uart[Ch].Buf[14] != 0x03 ) && (hangup_comm_flag || (!identity_prog_flag))) )	//98或99级：设置功能挂起, 安全认证失效
 			{
 				k = 2;
 				OutBuf[0] = 0xFF;	//Operation result.
 				OutBuf[1] = 0x04;	//Error: bit2密码错误/未授权
 				break;
 			}
			
			if( Uart[Ch].Buf[9] <= 12 ) break;//数据长度必须大于12

			memcpy( OptID.B08, Uart[Ch].Buf+18 ,4 );

			Auth = Uart[Ch].Buf[14];
			switch( Auth ) //密码权限
			{
				case KEYTYPE2:
				
					//通过密文+MAC的方式进行数据传输，不需要进行密码验证，也不需要编程键配合使用。
					//68+表号+68+14+L+DI0-DI3+99(98)000000+操作者代码+参数明文+MAC（带MAC的参数密文）+CS+16
					//带MAC写ESAM:		04D682(83,84)+P2+LC+参数+MAC
					//输入到ESAM的参数更新文件来解密，文件号=DI07.B08[2]%5;
					//将密文写入ESAM: 	04D689(90,91,92)+00+14+密文(带MAC)
					if( Uart[Ch].Buf[9] <= 16 ) break;//数据长度必须大于16

					Temp08 = Hex_To_Bcd(88+(DI07.B08[2]%5));
					result = Decrypt( Ch, Temp08, 0x02 );
					if( result )
					{
						k = 0x00; 
						OutBuf[ k++ ] = 0xFF;
						OutBuf[ k++ ] = 0x04;
						break;
					}
					
					//Ic_Comm_RxBuf[0]:数据长度; [1]~[4]:数据标识; [5]~[n]:
					//比对数据中数据标识
					for( i=0; i<4; i++ )
					{
						if( Ic_Comm_RxBuf[4-i] != DI07.B08[i] ) break;
					}
					
					if( i < 4 ) break;
				
					//剔除数据长度和DI后填入UART.Buf中.
					Uart[Ch].Buf[9] = 8+Ic_Comm_RxBuf[0];	//
					
					Exchange( Uart[Ch].Buf+22, Ic_Comm_RxBuf+5, Ic_Comm_RxBuf[0]-4 );
					
				case 0x03:	//厂内扩展命令
					switch( DI07.B08[2] )
					{
						case 0x00:
							switch( DI07.B08[1] )
							{
								case 0x01:
									switch( DI07.B08[0] )
									{
										case 0x01:	//日期及星期(其中0代表星期天)	YYMMDDWW  	4	年月日星期	
										case 0x02:	//时间                          hhmmss    	3	时分秒      
										case 0x0C:	//日期、星期(其中0代表星期天)及时间	YYMMDDWWhhmmss	7 年月日星期时分秒
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
	
//										case 0x05:	//校表脉冲宽度                  XXXX      	2	毫秒        
//											break;

										case 0x0A:	//两套阶梯时区切换时间		YYMMDDhhmm 	5	年月日时分
										case 0x06:	//两套时区表切换时间            YYMMDDhhmm	5	年月日时分
										case 0x07:	//两套日时段切换时间            YYMMDDhhmm	5	年月日时分
											//两套时区表切换时间（5）＋两套日时段表切换时间（5）＋两套费率电价切换时间（5）＋两套阶梯切换时间（5）＋crc（2）
											Temp08 = JudgeSwitch( Uart[Ch].Buf+22, 0 );
											if( Temp08==1 ) break;
												
											if( DI07.B08[0] == 0x0A ) result = UpdateSysPara( 0xC0+5*2, Uart[Ch].Buf+22, 5 );
											else result = UpdateSysPara( 0xC0+5*(DI07.B08[0]-6), Uart[Ch].Buf+22, 5 );
											if( result ) break;
											
											if( (Temp08==3)&&(DI07.B08[0]<=0x07) ) JudgeSwitch2(DI07.B08[0]-6);//翻转控制字节,清启动时间和进行约定冻结
											
											k = 1;
											break;
											
										default:
											Err_DI = 1;	//数据标识错
											break;
									}
									break;
									
								case 0x02:
									//年时区数（1）＋日时段表数（1）＋日时段数 （1）＋费率数（1）＋公共假日数（1）+谐波分析次数（1）+阶梯数（1）＋密钥数（1）＋crc（2）
									Temp32.B08[0] = 0x00;	//最小值
									Temp32.B08[1] = 0x00;	//最大值
									Temp32.B08[2] = 0x00;	//超过报错字
									switch( DI07.B08[0] )
									{
										case 0x01:	//年时区数p≤14            	NN      1	个
											Temp32.B08[0] = 1;			//最小值
											Temp32.B08[1] = MAXREGION;	//最大值
											Temp32.B08[2] = 0x10;		//超过报错字: 年时区数超(Bit4)
											break;

										case 0x02:	//日时段表数q≤8           	NN      1	个	
											Temp32.B08[0] = 1;			//最小值
											Temp32.B08[1] = MAXSIDUANTB;//最大值
											break;

										case 0x03:	//日时段数(每日切换数)m≤14	NN      1	个
											Temp32.B08[0] = 1;			//最小值
											Temp32.B08[1] = MAXSIDUAN;	//最大值
											Temp32.B08[2] = 0x20;		//超过报错字: 日时段数超(Bit5)
											break;

										case 0x04:	//费率数k≤63              	NN      1	个	
											Temp32.B08[1] = max_feilvcount;		//最大值
											Temp32.B08[2] = 0x40;		//超过报错字: 费率数超(Bit6)
											break;

										case 0x05:	//公共假日数n≤254         	NNNN	2	个
											if( Uart[Ch].Buf[23] ) break;
											Temp32.B08[1] = MAXHOLIDAY;	//最大值
											break;
//
//										case 0x06:	//谐波分析次数             	NN  	1	次	
//											break;

										case 0x07:	//阶梯数			NN	1	个
											Temp32.B08[1] = 6;			//最大值
											RefreshPrice();
											break;
											
										case 0x08:	//密钥总条数			HH 	1	个
											Temp32.B08[1] = MAX_PSW_NUM;	//最大值
											break;
										
										default:
											Err_DI = 1;	//数据标识错
											break;	
									}
									
									if( Temp32.B08[1] == 0x00 ) break;	//配置失败

									if( DI07.B08[0] != 0x08 )
									{
										if( IsBCD(Uart[Ch].Buf[22]) ) break;
										Temp08 = Bcd_To_Hex( Uart[Ch].Buf[22] );
									}
									else Temp08 = Uart[Ch].Buf[22];		//密钥条数设置为hex码

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
										OutBuf[1] = Temp32.B08[2]; 	//错误信息字ERR
									}
									break;
									
								case 0x03:	  
									//循显屏数(1)＋循显时间(1)＋电能小数位数(1)＋功率位数(1)＋键显屏数(1)＋波特率(1)+ 跳闸延时时间(2)＋crc(2)
									Temp32.B08[0] = 0x00;	//最小值
									Temp32.B08[1] = 0x00;	//最大值
									switch( DI07.B08[0] )
									{
										case 0x01:	//自动循环显示屏数            	NN      1   个
										case 0x05:	//按键循环显示屏数            	NN      1   个  	
											Temp32.B08[0] = 1;	//最小值
											Temp32.B08[1] = SCREENNUM;	//最大值
											break;
											
										case 0x02:	//每屏显示时间                	NN      1   秒
											Temp32.B08[0] = 5;	//最小值
											Temp32.B08[1] = 20;	//最大值
											break;
                                	
										case 0x03:	//显示电能小数位数            	NN      1   位  
											Temp32.B08[1] = 4;	//最大值
											break;
                                	
										case 0x04:	//显示功率（最大需量）小数位数	NN      1   位  
											Temp32.B08[1] = 4;	//最大值
											break;
										
										case 0x08:	//上电全显时间	NN	1	位
											Temp32.B08[0] = 5;	//最小值
											Temp32.B08[1] = 30;	//最大值
											break;
											
										default:
											Err_DI = 1;	//数据标识错
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
										case 0x01:	//通信地址                     	NNNNNNNNNNNN	6
											memset( Buf, 0x99, 6 );
											if( Cmp_Data( Buf, Uart[Ch].Buf+22, 6 ) ==3 ) break;	//禁止设置全9
											if( IsMultiBcd( Uart[Ch].Buf+22, 6 ) )	break;
											
											Exchange( Buf, Uart[Ch].Buf+22, 6 );
																						
											result = WriteE2WithBackup( ee_commaddr_page, ee_commaddr_inpage, Buf, ee_commaddr_lenth );
											if( result != 0x00 ) break;
												
											if( Cmp_Data(Comm_Addr.Comm_Id, Buf, 6) != 3 ) Ble_Rst_Judge(Ch);
											
											memcpy( Comm_Addr.Comm_Id, Buf, 8 );
	
											k = 1;
											break;

										case 0x0B:  	//电表型号（ASCII 码）         XX…XX      	10 	
										case 0x0C:	//生产日期（ASCII 码）          XX…XX      	10 	
											if( Auth != 3 )
											{
												k = 2;
												OutBuf[0] = 0xFF; //结果
												OutBuf[1] = 0x04; //Error: bit4密码错误/未授权
												break;
											}
										case 0x03:	//资产管理编码（ASCII 码）     	NN…NN      	32
										case 0x0F:	//电能表位置信息				11
											if(DI07.B08[0] == 0x0c) 
											{
												Temp16.B08[0] = ee_meterdate_page;//生产日期
												Temp16.B08[1] = ee_meterdate_inpage;
												Temp08 = 10;
											}
											else if(DI07.B08[0] == 0x0B)
											{
												Temp16.B08[0] = ee_matertype_page; //电表型号
												Temp16.B08[1] = ee_matertype_inpage;
												Temp08 = ee_matertype_lenth;
											}
											else if(DI07.B08[0] == 0x03) 
											{
												Temp16.B08[0] = ee_zichannum_page;//资产管理编号
												Temp16.B08[1] = ee_zichannum_inpage;
												Temp08 = 32;
											}
											else
											{
												Temp16.B08[0] = ee_meterpos_page;//电能表位置信息
												Temp16.B08[1] = ee_meterpos_inpage;
												Temp08 = 11;
												
												if( Auth == KEYTYPE2 )
												{
													Inverse( Uart[Ch].Buf+22, 11 );
													Inverse( Uart[Ch].Buf+22+0, 4 );	//XXXX.XXXX	4	经度
													Inverse( Uart[Ch].Buf+22+4, 4 );	//XXXX.XXXX	4	纬度
													Inverse( Uart[Ch].Buf+22+8, 3 );	//XXXX.XX	3	高度
												}
											}
											if( Uart[Ch].Buf[9] != (Temp08+12) ) break;//数据长度错误
											I2C_Write_Eeprom( Temp16.B08[0], Temp16.B08[1], Uart[Ch].Buf+22, Temp08 );
											k = 1;
											break;
										
										default:
											Err_DI = 1;	//数据标识错
											break;                                      		
									}
									break;

								case 0x06:	  
									switch( DI07.B08[0] )
									{
										case 0x01:  //有功组合方式特征字  	NN	1
											//波特率特征字（5）＋有功组合方式特征字1(1)＋冻结数据模式字(6)＋电表运行特征字1(1) +上报模式字(6)+crc（2）
											i = Mode.Comp_B;	//暂存编程前数据
											
											result = UpdateSysPara( 0x80+1, Uart[Ch].Buf+22, 1 );
											if( result != 0x00 ) break;
												
											//--------- 有功组合方式编程 ------------
											memcpy( Eeprom.Buffer+6, OptID.B08, 4 );	//操作者代码(4)
											Eeprom.Buffer[10] = i;		//编程前采用的数据(1)
											Event_Record( ee_combn_inpage );
											
											k = 1;
											break;
											
										case 0x02:  //无功组合方式1 特征字  NN	1	
											i = Mode.Rpcomp[0];	//暂存编程前数据
											
											result = UpdateSysPara( 0x80+28, Uart[Ch].Buf+22, 1 );
											if( result != 0x00 ) break;
												
											//--------- 有功组合方式编程 ------------
											memcpy( Eeprom.Buffer+6, OptID.B08, 4 );	//操作者代码(4)
											Eeprom.Buffer[10] = i;		//编程前采用的数据(1)
											Event_Record( ee_rp1combn_inpage );
											
											k = 1;
											break;
											
										case 0x03:  //无功组合方式2 特征字  NN	1	
											i = Mode.Rpcomp[1];	//暂存编程前数据
											
											result = UpdateSysPara( 0x80+29, Uart[Ch].Buf+22, 1 );
											if( result != 0x00 ) break;
												
											//--------- 有功组合方式编程 ------------
											memcpy( Eeprom.Buffer+6, OptID.B08, 4 );	//操作者代码(4)
											Eeprom.Buffer[10] = i;		//编程前采用的数据(1)
											Event_Record( ee_rp2combn_inpage );
											
											k = 1;
											break;
											
										default:
											Err_DI = 1;	//数据标识错
											break;
									}
									break;
									
								case 0x07:	  
									switch( DI07.B08[0] )
									{
										case 0x01:	//调制型红外光口波特率特征字	NN  1
//										case 0x02:	//接触式红外光口波特率特征字    NN  1
										case 0x03:	//通信口1 波特率特征字          NN  1
//										case 0x04:	//通信口2 波特率特征字          NN  1
										case 0x05:	//通信口3 波特率特征字          NN  1
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
											Err_DI = 1;	//数据标识错
											break;
									}
									break;
																		
								case 0x08:
									switch( DI07.B08[0] )
									{
										case 0x02:	//周休日采用的日时段表号    NN	1
											if( (Uart[Ch].Buf[22] == 0x00) || (Uart[Ch].Buf[22] > MAXSIDUANTB) )	break;	//只能是1~8的日时段表号
											i = Week_Holiday.Shiduan_N;	//暂存编程前数据
											
										case 0x01:	//周休日特征字		NN		1										
											result = UpdateSysPara( 0x60+DI07.B08[0]-1, Uart[Ch].Buf+22, 1 );
											if( result != 0x00 ) break;

											if( DI07.B08[0] == 0x02 )
											{
												//--------- 周休日编程 ------------
												memcpy( Eeprom.Buffer+6, OptID.B08, 4 );	//操作者代码(4)
												Eeprom.Buffer[10] = i;		//编程前采用的数据(1)
												Event_Record( ee_weekdayn_inpage );
											}
											
											k = 1;
											break;
										
										default:
											Err_DI = 1;	//数据标识错
											break;
									}
									break;

								case 0x09:
								case 0x19:	
									switch( DI07.B08[0] )
									{
										case 0x01:	//负荷记录模式字	NN	1/2													
										case 0x02:	//定时冻结数据模式字	NN	1/2
										case 0x03:	//瞬时冻结数据模式字	NN	1/2
										case 0x04:	//约定冻结数据模式字    NN	1/2
										case 0x05:	//整点冻结数据模式字    NN	1/2
										case 0x06:	//日冻结数据模式字      NN	1/2
										case 0x07:	//月冻结数据模式字      NN	1/2
											//波特率特征字（5）＋有功组合方式特征字1(1)＋冻结数据模式字(6)＋电表运行特征字1(1) +上报模式字(6)+crc（2）
											if( DI07.B08[1] == 0x09 )
											{
												if( Uart[Ch].Buf[9] != 13 ) break;//数据长度错误
												Uart[Ch].Buf[23] = 0;
											}
											else
											{
												if( Uart[Ch].Buf[9] != 14 ) break;//数据长度错误
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
											Err_DI = 1;	//数据标识错
											break;
									}
									break;
									
								case 0x0A:
									switch( DI07.B08[0] )
									{
										case 0x01:	//负荷记录起始时间		MMDDhhmm	4
											result = JudgeClockNoWeek( 1, Uart[Ch].Buf+22, 4 );
											if( result != 0 ) break; //错误
											
											result = UpdateSysPara( 9, Uart[Ch].Buf+22, 4 );
											if( result != 0x00 ) break;
											
											k = 1;
											break;
												
										case 0x02:	//第1 类负荷记录间隔时间    NNNN	2
										case 0x03:	//第2 类负荷记录间隔时间    NNNN	2
										case 0x04:	//第3 类负荷记录间隔时间    NNNN	2
										case 0x05:	//第4 类负荷记录间隔时间    NNNN	2
										case 0x06:	//第5 类负荷记录间隔时间    NNNN	2
										case 0x11:	//组合有功费率1~ 4电能负荷记录间隔时间    NNNN	2
										case 0x12:	//组合有功费率5~ 8电能负荷记录间隔时间    NNNN	2
//										case 0x13:	//组合有功费率9~12电能负荷记录间隔时间    NNNN	2
											if( IsMultiBcd( Uart[Ch].Buf+22, 2 ) )	break;
											if( ((Uart[Ch].Buf[22] == 0) || (Uart[Ch].Buf[22]>0x30)) || Uart[Ch].Buf[23] ) break;
											
											if( DI07.B08[0]>=0x11 ) DI07.B08[0] -= 0x0A;
											result = UpdateSysPara( 13+2*(DI07.B08[0]-2), Uart[Ch].Buf+22, 2 );
											if( DI07.B08[0]>=0x07 ) DI07.B08[0] += 0x0A;
											if( result != 0x00 ) break;
										
											k = 1;
											break;

										default:
											Err_DI = 1;	//数据标识错
											break;
									}
									break;
																	
								case 0x0B:
									switch( DI07.B08[0] )
									{
										case 0x01:	//每月第1 结算日	DDhh	2	日时
										case 0x02:	//每月第2 结算日    DDhh	2	日时
										case 0x03:	//每月第3 结算日    DDhh	2	日时
											if( (Uart[Ch].Buf[22] != 0x99) || (Uart[Ch].Buf[23] != 0x99) )
											{
												result = JudgeClockNoWeek( 2, Uart[Ch].Buf+22, 2 );
												if( result != 0 ) break; //错误
	
												if( Uart[Ch].Buf[23] > 0x28 )	break;	//只能是1~28日的整点时刻
											}
											
											ReadE2WithBackup( ee_histroyparameter_page, ee_histroyparameter_inpage, Buf, ee_histroyparameter_lenth );
											
											memcpy( ChangeBuf, Buf, ee_histroyparameter_lenth );

											Buf[2*(DI07.B08[0]-1)+0] = Uart[Ch].Buf[22];
											Buf[2*(DI07.B08[0]-1)+1] = Uart[Ch].Buf[23];

											result = WriteE2WithBackup( ee_histroyparameter_page, ee_histroyparameter_inpage, Buf, ee_histroyparameter_lenth );
											if( result != 0x00 ) break;
											
											if( (DI07.B08[0] == 0x01)	//设置第一结算日
											 && ((ChangeBuf[0]!=Uart[Ch].Buf[22]) || (ChangeBuf[1]!=Uart[Ch].Buf[23])) )//第一结算日发生改变
											{
												if( Price.Ladder_Mode == 0x55 )
													Freeze_Usedl(1);//年结算,月转存,不清用电量
												else
													Freeze_Usedl(2);//月结算,月用电量转存和清零
												Freeze_Dl(ee_histroy_dl_page,ee_histroyf_inpage);
												
												run_price_flag = 1;
											}

											//---- 结算日编程记录 ----
											memcpy( Eeprom.Buffer+6, OptID.B08, 4 );	//操作者代码(4)
											memcpy( Eeprom.Buffer+10, ChangeBuf, 6 );	//结算日编程前每月第1~3结算日数据(6)
											
											Event_Record( ee_jieshuann_inpage );
											
											k = 1;
											break;

										default:
											Err_DI = 1;	//数据标识错
											break;
									}
									break;
								
								case 0x0C:	//0级密钥~9级密钥：03级密码，04级密码		
									if( ((DI07.B08[0] == 0x04) || (DI07.B08[0] == 0x05)) && ((DI07.B08[0]-1) == Uart[Ch].Buf[22]) )
									{
										WriteE2WithBackup( ee_password_page, ee_password_inpage+(DI07.B08[0]-4)*6, Uart[Ch].Buf+22, ee_password_lenth );
										k = 1;
									}
									else
									{
										k = 2;
										OutBuf[0] = 0xFF; //结果
										OutBuf[1] = 0x04; //Error: bit2密码错误/未授权
									}		
									break;
									
								case 0x0E:
									switch( DI07.B08[0] )
									{
										case 0x03:	//电压上限值	NNN.N	2	V
										case 0x04:	//电压下限值	NNN.N	2	V
											if( IsMultiBcd(Uart[Ch].Buf+22, 2) ) break;	//非法数据
											
											result = UpdateSysPara( 0xA0+(DI07.B08[0]-3)*2, Uart[Ch].Buf+22, 2 );
											if( result != 0x00 ) break;
											
											k = 1;
											break;
											
										default:
											Err_DI = 1;	//数据标识错
											break;
									}
									break;	
								
								case 0x11:
									switch( DI07.B08[0] )
									{
										case 0x01:	//电表运行特征字1	NN	1
											//波特率特征字（5）＋有功组合方式特征字1(1)＋冻结数据模式字(6)＋电表运行特征字1(1) +上报模式字(6)+crc（2）
											result = UpdateSysPara( 0x80+8, Uart[Ch].Buf+22, 1 );
											if( result != 0x00 ) break;
	
											k = 1;
											break;
											
										case 0x04:	//主动上报模式字	NNNNNNNNNNNNNNNN	8
											//波特率特征字（5）＋有功组合方式特征字1(1)＋冻结数据模式字(5)＋电表运行特征字1(1)＋上报模式字(6) + crc（2）
											if( Uart[Ch].Buf[9] != 20 ) break;//数据长度错误
											Inverse( Uart[Ch].Buf+22, 8 );	//数据倒序(低字节在前变成高字节在前,下面程序又变成低字节在前)
											result = UpdateSysPara( 0x80+9, Uart[Ch].Buf+22, 8 );
											if( result != 0x00 ) break;
	
											k = 1;
											break;
											
										default:
											Err_DI = 1;	//数据标识错
											break;
									}
									break;
																
								case 0x12:
									I2C_Read_Eeprom44( ee_freezeparameter_page, Buf, ee_freezeparameter_lenth );
									
									Temp08 = 0x00;	//默认失败
									switch( DI07.B08[0] )
									{
										case 0x01:	//整点冻结起始时间	YYMMDDhhmm	5	年月日时分，默认数值为全零，设置值应是整点值或半点值。
//											if( (Uart[Ch].Buf[22]!=0x00) && (Uart[Ch].Buf[22]!=0x30) )
//											{
//												break;	//错误
//											}

											result = JudgeClockNoWeek( 1, &Uart[Ch].Buf[22], 5 );
											if( result != 0 ) break; //错误
																						
											Exchange( Buf, Uart[Ch].Buf+22, 5 );
											Temp08 = 0x01;
											break;
											
										case 0x02:  //整点冻结时间间隔	NN          1	分钟, 设置为30、60分钟，默认为60分钟。
											if( (Uart[Ch].Buf[22]!=0x30)&&(Uart[Ch].Buf[22]!=0x60) ) break;
											
											Buf[5] = Uart[Ch].Buf[22];
											Temp08 = 0x01;
											break;
											
										case 0x03:  //日冻结时间      	hhmm        2	时分      
											result = JudgeClockNoWeek( 1, &Uart[Ch].Buf[22], 2 );
											if( result != 0 ) break; //错误
											
											Wr_Pretime_Dayfreeze();	//写上一次日冻结时间
											
											Buf[6] = Uart[Ch].Buf[23];
											Buf[7] = Uart[Ch].Buf[22];
											Temp08 = 0x01;
											break;
											
										default:
											Err_DI = 1;	//数据标识错
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
//										case 0x01:	//无线通信在线及信号强弱指示	NN	1	
//											break;
//											
//										default:
//											break;
//									}
//									break;
									
								case 0x14:
									switch( DI07.B08[0] )
									{
										case 0x01:	//跳闸延时时间（NNNN 为跳闸前告警时间）	NNNN	2
										case 0x02:	//继电器拉闸控制电流门限值	XXX.XXX	3
										case 0x03:	//继电器延时拉闸时间	XXXX	2
//										case 0x04:	//红外认证时效	XXXX	1
										case 0x05:	//上报复位时间	XXXX	1
										case 0x06:	//蓝牙认证时效  XX 1
											if( DI07.B08[0] == 0x02 )
											{
												Temp16.B08[0] = 0;	//偏移地址0
												Temp16.B08[1] = 3;	//字节数
											}
											else if( DI07.B08[0] >= 0x04 )
											{
												Temp16.B08[0] = (DI07.B08[0]&1)+0x07;//偏移地址7,8
												Temp16.B08[1] = 1;
												if( Uart[Ch].Buf[22] == 0 ) break;
											}
											else
											{
												Temp16.B08[0] = DI07.B08[0]+2;//偏移地址3,5	
												Temp16.B08[1] = 2;	
//												if( (DI07.B08[0] == 0x03) && (Uart[Ch].Buf[22] == 0) && (Uart[Ch].Buf[23] == 0) ) break;
											}
											
											if( IsMultiBcd( Uart[Ch].Buf+22, Temp16.B08[1] ) ) break;
											
											result = UpdateSysPara( 0x80+17+Temp16.B08[0], Uart[Ch].Buf+22, Temp16.B08[1] );
											if( result != 0x00 ) break;						
											
											if( Opendelaytimer && (DI07.B08[0]==0x01) ) Opendelaytimer = Calculate_Timer(0)+2;
//											if( Relay_Mode != 0x55 )//内置继电器
											{
												if( CurrentTimer && (DI07.B08[0]==0x03) ) CurrentTimer = Calculate_Timer(1);
											}
											if( IR_EnTimer && ((DI07.B08[0]==0x04)||(DI07.B08[0]==0x06)) ) IR_EnTimer = Calculate_Timer(2);
											if( Reset_Rep_Timer && (DI07.B08[0]==0x05) ) Reset_Rep_Timer = Calculate_Timer(3);
											
											k = 1;
											break;		
											
										case 0x08:	//蓝牙从机MAC地址（HEX格式）		
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
											
										case 0x09:	//蓝牙参数
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
											
										case 0x0A:	//蓝牙广播时间 40~100ms BCD
											if( IsMultiBcd(Uart[Ch].Buf+22, 2) ) break;	//非法数据
											Bcd2Hex_SS(Uart[Ch].Buf+22, Uart[Ch].Buf+24, 2);
											if( (Uart[Ch].Buf[24] < 40) || (Uart[Ch].Buf[24] > 100) || Uart[Ch].Buf[25] ) break;
											I2C_Write_Eeprom(ee_blerefer_page, ee_blegbtime_inpage, Uart[Ch].Buf+22, ee_blegbtime_lenth);
											
											k = 1;
											break;	
											
										case 0xee:	//继电器合闸允许方式	XX	1
											result = UpdateSysPara( 0x80+26, Uart[Ch].Buf+22, 1 );
											if( result != 0x00 ) break;

											k = 1;
											break;	
										
										default:
											Err_DI = 1;	//数据标识错
											break;
									}
									break;
								case 0x17:
									switch( DI07.B08[0] )
									{
										case 0x01:	//售电方	NNNNNNNN	4
										case 0x02:	//购电方	NNNNNNNN	4
										case 0x03:	//用电容量		NNNNNNNNNNNNNNNN	8
										case 0x04:	//对应费率时段电价	NNNNNNNNNNNNNNNN	8
										case 0xFF:	//集合
											if( DI07.B08[0] == 0x01 || DI07.B08[0] == 0x02 )
											{
												Temp16.B08[0] = 0+(DI07.B08[0]-1)*4;	//偏移地址
												Temp16.B08[1] = 4;	//字节数
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
											Err_DI = 1;	//数据标识错
											break;
									}
									break;

								default:
									Err_DI = 1;	//数据标识错
									break;
							}
							break;
							
						case 0x07:	//当前套阶梯时区表，备用套阶梯时区表
//							if( !BDMODE ) { Err_DI = 1;	break; }
						case 0x01:	//第一套时区表和日时段表数据
						case 0x02:	//第二套时区表和日时段表数据
							//时区表内时区数1~14个，可设，时区数不足14个时，用最后一个补足。
							//日时段表的个数是1~8个，可设，没有补足功能。
							//日时段表内时段数1~14个，不可设，
							//下发设置时，不判断设定的时区数和时段数，只管其中包含了多少个。
							//年时区数（1）＋日时段表数（1）＋日时段数 （1）＋费率数（1）＋公共假日数（1）+谐波分析次数（1）+阶梯数（1）＋密钥数（1）＋crc（2）
							if( (DI07.B08[1]!=0x00) || (DI07.B08[0]>MAXSIDUANTB) || 
							   ((DI07.B08[2]==0x07) && (DI07.B08[0]>0x01)) )//阶梯时区表当前和备用套均可以设置
							{
								Err_DI = 1;	//数据标识错
								break;
							}

							if( DI07.B08[2] == 0x07 ) DI07.B08[0] += 0x09;  //便于软件区分数据类型
							if( DI07.B08[0] == 0x00 )	//第一套时区表数据, 第1~14时区起始日期及日时段表号(14*3), MMDDNN
							{
								Temp32.B08[0] = 3;	//时间起始位置
								Temp32.B08[1] = MAXSIDUANTB;	//日时段表表号限值
								Temp32.B08[2] = MAXREGION;	//最大时区数目
								Temp32.B08[3] = ee_shiqu_lenth;
							}
							else if( DI07.B08[0] <= 0x08 )	//最多可设置8个日时段表, 每个日时段表固定为14个时段
							{
								Temp32.B08[0] = 1;	//时间起始位置
								Temp32.B08[1] = max_feilvcount;	//费率号限值
								Temp32.B08[2] = MAXSIDUAN;	//最大日时段数目
								Temp32.B08[3] = ee_shiduantable_lenth;
							}
							else
							{
								Temp32.B08[0] = 3;	//时间起始位置
								Temp32.B08[1] = 4;	//阶梯表张数限值
								Temp32.B08[2] = 4;	//最大阶梯时区数目
								Temp32.B08[3] = ee_jtshiqu_len;
							}
						
							//时区时间顺序判断: 要求按照时间升序排列
							Temp08 = (Uart[Ch].Buf[9]-12)/3;	//
							if( ((Uart[Ch].Buf[9]-12)%3) || (Temp08==0) ) break; //数据长度错误, 退出 
								
							if( Temp08 > Temp32.B08[2] )
							{
								k = 2;
								OutBuf[0] = 0xFF;
								if( DI07.B08[0]==0 ) OutBuf[1] = 0x10;//时区数超(Bit4)
								else if( DI07.B08[0] <= 0x08 ) OutBuf[1] = 0x20;//时段数超(Bit5)
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

							//时间顺序判断: 要求按照时间升序排列
							n = Temp08*3;	//为了判断日时段15分钟间隔方便, 将"第1组+固定值"存入"最后1组"的后面。
							Buf[n+0] = Buf[0];	//日时段表号 or 费率号
							Buf[n+1] = Buf[1];	//日 or 分
							Buf[n+2] = Hex_To_Bcd(Bcd_To_Hex(Buf[2])+24);	//月 or 时
							
							for( i=0, n=0; i<Temp08; i++, n+=3 ) //时间是升序或者一直相同
							{
								if( (Buf[0+n]==0) || (Bcd_To_Hex(Buf[0+n])>Temp32.B08[1]) || (IsBCD(Buf[0+n])) )	//日时段表号or费率号是否合法
								{
									if( DI07.B08[0] && (DI07.B08[0]<=0x08) )
									{
										k = 2;
										OutBuf[0] = 0xFF;
										OutBuf[1] = 0x40;//费率数超(Bit6)
									}
									break;
								}
							
								result = JudgeClockNoWeek( Temp32.B08[0], Buf+1+n, 2 );	//minute+hour
								if( result != 0 ) break; //错误
									
								result = Cmp_Bcd_Inv( Buf+1+n, Buf+4+n, 2 );
								if( result == 0x00 )	//A == B
								{
									if( Buf[3+n] != Buf[0+n] ) break;
								}
								else if( result == 0x02 ) //A < B
								{
									if( DI07.B08[0] && (DI07.B08[0]<=0x08))	//日时段表中最小时段间隔不应小于15分钟
									{
										if( (CalcAbsMin(Buf+4+n)-CalcAbsMin(Buf+1+n)) < 15 ) break;
									}
								}
								else //A > B
								{
									break;	//数据有误
								}
							}
							
							if( i < Temp08 )	break;	//数据有误

							for( i=(Temp08); i<Temp32.B08[2]; i++ )	//数据不足, 补最后一组数据
							{
								memcpy( Uart[Ch].Buf+22+3*i, Uart[Ch].Buf+22+3*(Temp08-1), 3 );
							}

							if( DI07.B08[0] <= 0x08 )
							{
								Temp16.B16 = ShiquRecord( DI07.B08, OptID.B08 );	//事件记录
								I2C_Write_Eeprom( Temp16.B16, 0x00, Uart[Ch].Buf+22, Temp32.B08[3] );	//编程后 时区表or时段第i表(42)
							}
							else
							{
								Temp16.B16 = ee_jtshiqu1_page+DI07.B08[0]-0x09;
								I2C_Write_Eeprom( Temp16.B16, ee_jtshiqu_inpage, Uart[Ch].Buf+22, Temp32.B08[3] );	//编程后 时区表or时段第i表(42)
							}		
			
							if( DI07.B08[2] == 0x07 ) DI07.B08[0] -= 0x09;  //便于软件区分数据类型
							
							run_timezone_flag = 1;
							Tariff.Crc16.B08[0] += 1;
							RefreshPrice();

							k = 1;												
							break;

						case 0x03:	//第n 公共假日日期及日时段表号
							switch( DI07.B08[1] ) 
							{
								case 0x00:
									if( (DI07.B08[0]>=1) && (DI07.B08[0]<=MAXHOLIDAY) )	//公共假日：1~14, YYMMDDNN, 4
									{
										if( (Uart[Ch].Buf[22]==0) || (Uart[Ch].Buf[22]>MAXSIDUANTB) ) break;	//日时段表号: 1~8

										result = Judge_Clock( 4, &Uart[Ch].Buf[23], 3 ); //判断数据是否合法
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
										Err_DI = 1;	//数据标识错
									}
									break;
									
								default:
									Err_DI = 1;	//数据标识错
									break;
							}
							break;

						case 0x04:
							switch( DI07.B08[1] )
							{
								case 0x01:	//自动循显
								case 0x02:	//按键循显
									//循显屏数(1)＋循显时间(1)＋电能小数位数(1)＋功率位数(1)＋键显屏数(1)＋波特率(1)+ 跳闸延时时间(2)＋crc(2)
									if( Auth == KEYTYPE2 )
									{
										Temp08 = Uart[Ch].Buf[22];
										memcpy( Uart[Ch].Buf+22, Uart[Ch].Buf+23, 4);
										Uart[Ch].Buf[26] = Temp08;
									}
														
									if( (DI07.B08[0]) && (DI07.B08[0]<=SCREENNUM) )
									{
										Temp16.B16 = GetLcdNo( Uart[Ch].Buf+22 );
										if( Temp16.B16 == 0x00 ) break;	//显示项目错误 or 显示序号错
																				
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
										Err_DI = 1;	//数据标识错
									}
									break;
								
								default:
									Err_DI = 1;	//数据标识错
									break;
							}
							break;
							
						case 0x09:
							switch( DI07.B08[1] )
							{
								case 0x01:
									if( DI07.B08[0]==1 || DI07.B08[0]==2 )//失压事件电压触发上限/失压事件电压恢复下限 NNN.N	2	V
									{		
										if( IsMultiBcd( Uart[Ch].Buf+22, 2) )	break;
										result = UpdateSysPara( 0xA8+(DI07.B08[0]-1)*2, Uart[Ch].Buf+22, 2 );
									}
									else if( DI07.B08[0]==3 )//失压事件电流触发下限	NN.NNNN	3	A
									{
										if( IsMultiBcd( Uart[Ch].Buf+22, 3) ) break;
										Uart[Ch].Buf[25] = 0;
										result = UpdateSysPara( 0xA0+12, Uart[Ch].Buf+22, 4 );
									}
									else if( DI07.B08[0]==4 )//失压事件延时判定时间	NN	1	S
									{
										if( IsMultiBcd( Uart[Ch].Buf+22, 1) || (Uart[Ch].Buf[22] < 10) ) break;
										result = UpdateSysPara( 0xA0+16, Uart[Ch].Buf+22, 1 );
									}
									else
									{
										Err_DI = 1;	//数据标识错
										break;
									}
										
									if( result != 0x00 ) break;
											
									k = 1;
									break;
								
								case 0x08:
									if( DI07.B08[0]==1 )//过流事件电流触发下限	NNN.N	2	A
									{		
										if( IsMultiBcd( Uart[Ch].Buf+22, 2) )	break;
										result = UpdateSysPara( 0x60+17, Uart[Ch].Buf+22, 2 );
									}
									else if( DI07.B08[0]==2 )//过流事件判定延时时间	NN	1	S
									{
											
										if( IsMultiBcd( Uart[Ch].Buf+22, 1) || (Uart[Ch].Buf[22] < 10) ) break;
										result = UpdateSysPara( 0x60+19, Uart[Ch].Buf+22, 1 );
									}
									else
									{
										Err_DI = 1;	//数据标识错
										break;
									}
										
									if( result != 0x00 ) break;
											
									k = 1;
									break;
									
								case 0x0C:
									switch( DI07.B08[0] )
									{
										case 0x01:	//合格率电压考核上限值	NNN.N	2	V
										case 0x02:	//合格率电压考核下限值	NNN.N	2	V
											if( IsMultiBcd(Uart[Ch].Buf+22, 2) ) break;	//非法数据
											
											result = UpdateSysPara( 0xA4+(DI07.B08[0]-1)*2, Uart[Ch].Buf+22, 2 );
											if( result != 0x00 ) break;
											
											k = 1;
											break;
											
										default:
											Err_DI = 1;	//数据标识错
											break;
									}
									break;
									
								case 0x12: 
									switch( DI07.B08[0] )
									{
										case 0x01:	//低电压事件电压触发上限	NNN.N	2	V
											if( IsMultiBcd(Uart[Ch].Buf+22, 2) ) break;	//非法数据
											result = UpdateSysPara( 0xA0+17, Uart[Ch].Buf+22, 2 );
											if( result != 0x00 ) break;
											
											k = 1;
											break;
										
										case 0x02:	//低电压事件延时判定时间	NNNN	2	MIN
											if( IsMultiBcd( Uart[Ch].Buf+22, 1)  ) break;
											result = UpdateSysPara( 0xA0+19, Uart[Ch].Buf+22, 2 );
											if( result != 0x00 ) break;
											
											k = 1;
											break;
											
										default:
											Err_DI = 1;	//数据标识错
											break;
									}
									break;	
									
								case 0x11: 
									switch( DI07.B08[0] )
									{
										case 0x01:	//高电压事件电压触发上限	NNN.N	2	V
											if( IsMultiBcd(Uart[Ch].Buf+22, 2) ) break;	//非法数据
											result = UpdateSysPara( 0xA0+21, Uart[Ch].Buf+22, 2 );
											if( result != 0x00 ) break;
											
											k = 1;
											break;
										
										case 0x02:	//高电压事件延时判定时间	NNNN	2	MIN
											if( IsMultiBcd( Uart[Ch].Buf+22, 1)  ) break;
											result = UpdateSysPara( 0xA0+23, Uart[Ch].Buf+22, 2 );
											if( result != 0x00 ) break;
											
											k = 1;
											break;
											
										default:
											Err_DI = 1;	//数据标识错
											break;
									}
									break;									
									
								case 0x3f:
									switch( DI07.B08[0] )
									{
										case 0x01:	//零线电流不平电流触发下限	NN.NNNN	3	A
											if( IsMultiBcd(Uart[Ch].Buf+22, 3) ) break;	//非法数据
											Uart[Ch].Buf[25] = 0;
											result = UpdateSysPara( 0x60+20, Uart[Ch].Buf+22, 4 );
											if( result != 0x00 ) break;
											
											k = 1;
											break;
										
										case 0x02:	//零线电流不平衡限值      long-unsigned（单位：%，换算：-2）
											if( IsMultiBcd(Uart[Ch].Buf+22, 2) ) break;	//非法数据
											result = UpdateSysPara( 0x60+24, Uart[Ch].Buf+22, 2 );
											if( result != 0x00 ) break;
											
											k = 1;
											break;
											
										case 0x03:	//零线电流不平延时判定时间        NN	1	S
											if( IsMultiBcd( Uart[Ch].Buf+22, 1) || (Uart[Ch].Buf[22] < 10) ) break;
											result = UpdateSysPara( 0x60+26, Uart[Ch].Buf+22, 1 );
											if( result != 0x00 ) break;
											
											k = 1;
											break;
											
										default:
											Err_DI = 1;	//数据标识错
											break;
									}
									break;	
									
								case 0x40:	
									switch( DI07.B08[0] )
									{
										case 0x01:	//计量故障判定延时	NN	1	S
											if( IsMultiBcd( Uart[Ch].Buf+22, 1) || (Uart[Ch].Buf[22] < 10) ) break;
											result = UpdateSysPara( 0xA0+25, Uart[Ch].Buf+22, 1 ); //更新XRAM, E2PROM
											if( result ) break;
											k = 1;
											break;			
										default:
											Err_DI = 1;	//数据标识错
											break;
									}
									break;	
									
								case 0x43:	
									switch( DI07.B08[0] )
									{
										case 0x01:	//停电事件判断延时	NN	1	S
											if( IsMultiBcd( Uart[Ch].Buf+22, 1) || (Uart[Ch].Buf[22] < 3) || (Uart[Ch].Buf[22] > 0x60) ) break;
											result = UpdateSysPara( 0x80+6, Uart[Ch].Buf+22, 1 );
											if( result != 0x00 ) break;
											
											k = 1;
											break;			
											
										default:
											Err_DI = 1;	//数据标识错
											break;
									}
									break;			
									
								case 0x51:	
									switch( DI07.B08[0] )
									{
										case 0x01:	//主动上报上电时限	NN	1	MIN
											if( IsMultiBcd( Uart[Ch].Buf+22, 1) ) break;
											result = UpdateSysPara( 0x80+7, Uart[Ch].Buf+22, 1 );
											if( result != 0x00 ) break;
											
											k = 1;
											break;			
											
										default:
											Err_DI = 1;	//数据标识错
											break;
									}
									break;	
									
								default:
									Err_DI = 1;	//数据标识错
									break;
							}
							break;	
							
						case 0x80:    // :p		
							switch( DI07.B08[1] )
							{
								case 0x00:
									switch( DI07.B08[0] )
									{
										case 0x01:	//厂家软件版本号(ASCII 码)	NN…NN	32
										case 0x02:	//厂家硬件版本号(ASCII 码)	NN…NN	32
										case 0x03:	//厂家编码(ASCII 码)		NN…NN	32
										case 0x04:	//软件备案号			NN…NN	8
											if( Auth != 3 )
											{
												k = 2;
												OutBuf[0] = 0xFF; //结果
												OutBuf[1] = 0x04; //Error: bit4密码错误/未授权
												break;
											}
											Temp08 = 32;//32字节
											if(DI07.B08[0] == 0x01)
											{
												Temp16.B08[0] = ee_softver_page;	//软件备案号
												Temp16.B08[1] = ee_softver_inpage;
											}
											else if(DI07.B08[0] == 0x02)
											{
												Temp16.B08[0] = ee_hardver_page;	//硬件备案号
												Temp16.B08[1] = ee_hardver_inpage;
											}
											else if(DI07.B08[0] == 0x03)
											{
												Temp16.B08[0] = ee_factorynum_page;	//厂家编号
												Temp16.B08[1] = ee_factorynum_inpage;
											}
											else
											{
												Temp16.B08[0] = ee_softbk_page; 	//软件备案号
												Temp16.B08[1] = ee_softbk_inpage;
												Temp08 = 8;//8字节
											}
											if( Uart[Ch].Buf[9] != (Temp08+12) ) break;//数据长度错误
											I2C_Write_Eeprom( Temp16.B08[0], Temp16.B08[1], Uart[Ch].Buf+22, Temp08 );
											k = 1;
											break;
																						
										default:
											Err_DI = 1;	//数据标识错
											break;
									}
									break;
									
								default:
									Err_DI = 1;	//数据标识错
									break;
							}
							break;		
							
						default:
							Err_DI = 1;	//数据标识错
							break;
					}
					break;

				case KEYTYPE1:	//通过明文+MAC的方式进行数据传输，不需要进行密码验证，也不需要编程键配合使用。
//					if( (Byte2uInt(DI07.B08) != 0x02040004) && 
//					   (((BDMODE)&&(Byte2uInt(DI07.B08) == 0x0E040004)) || 
//					    ((!BDMODE)&&(Byte2uInt(DI07.B08) != 0x0E040004))) )//任何模式都支持表号设置, 客户编号区分模式
//					{
//						Err_DI = 1;	//Error: bit2密码错误/未授权
//						break;
//					}

					switch( DI07.B08[3] )
					{
						case 0x04:
							switch( DI07.B08[2] )
							{
								case 0x00:
									Temp32.B08[0] = 0x00;
									Temp32.B08[3] = 0x81;	//写入ESAM的文件号
									
									switch( DI07.B08[1])
									{
										case 0x01:
											switch( DI07.B08[0] )
											{
//												case 0x08:	//两套费率电价切换时间			YYMMDDhhmm	5	年月日时分
//													//两套时区表切换时间（5）＋两套日时段表切换时间（5）＋两套费率电价切换时间（5）＋两套阶梯切换时间（5）＋crc（2）
//													result = JudgeSwitch( Uart[Ch].Buf+22, 0 );
//													if( result==1 ) break;
//													
//													Temp32.B08[0] = 5;	//数据长度
//													Temp32.B08[1] = 10;	//82文件中偏移量
//													Temp32.B08[2] = 0xC0+10;	//E2中页内偏移量
//													break;

												case 0x09:	//两套阶梯切换时间		YYMMDDhhmm	5	年月日时分
													//两套时区表切换时间（5）＋两套日时段表切换时间（5）＋两套费率电价切换时间（5）＋两套阶梯切换时间（5）＋crc（2）
													result = JudgeSwitch( Uart[Ch].Buf+22, 0 );
													if( result==1 ) break;

													Temp32.B08[0] = 5;	//数据长度
													Temp32.B08[1] = 192;//84文件中偏移量
													Temp32.B08[2] = 0xC0+15;	//E2中页内偏移量
													Temp32.B08[3] = 0x84;	//写入ESAM的文件号
													break;
												
												default:
													Err_DI = 1;	//数据标识错
													break;
											}
											break;

										//报警金额1限值(4)＋报警金额2限值(4)+互感器变比(6)＋表号(6)+客户编号(6)+电卡类型(1)+身份认证时效(2)
										case 0x03:
											switch( DI07.B08[0] )
											{
												case 0x06:	//电流互感器变比              	NNNNNN	3       break;
													Temp32.B08[0] = 3;	//数据长度
													Temp32.B08[1] = 24;	//82文件中偏移量
													Temp32.B08[2] = 0x40+0;	//E2中页内偏移量
													break;
																										
												case 0x07:	//电压互感器变比              	NNNNNN	3	    break;
													Temp32.B08[0] = 3;	//数据长度
													Temp32.B08[1] = 27;	//82文件中偏移量
													Temp32.B08[2] = 0x40+3;	//E2中页内偏移量
													break;
												
												default:
													Err_DI = 1;	//数据标识错
													break;
											}
											break;
		
										case 0x04:
											switch( DI07.B08[0] )
											{
												case 0x02:	//表号		NNNNNNNNNNNN	6
													if( Key_Status!=0 ){Err_DI = 1;break;}//公钥允许设置

													Temp32.B08[0] = 6;	//数据长度
													Temp32.B08[1] = 30;	//82文件中偏移量
													Temp32.B08[2] = 0x40+6;	//E2中页内偏移量
													break;
																										
												case 0x0E:	//客户编号	NNNNNNNNNNNN	6
													if( Key_Status!=0 ){Err_DI = 1;break;}//公钥允许设置
													
													Temp32.B08[0] = 6;	//数据长度
													Temp32.B08[1] = 36;	//82文件中偏移量
													Temp32.B08[2] = 0x40+12;//E2中页内偏移量
													break;
																							
												default:
													Err_DI = 1;	//数据标识错
													break;
											}
											break;
											
//										case 0x10:
//											switch( DI07.B08[0] )
//											{
//												case 0x01:  //报警金额1 限值	XXXXXX.XX	4	元
//													Temp32.B08[0] = 4;	//数据长度
//													Temp32.B08[1] = 16;	//82文件中偏移量
//													Temp32.B08[2] = 0x40+0;	//E2中页内偏移量
//													break;
//													
//												case 0x02:  //报警金额2 限值	XXXXXX.XX	4	元
//													Temp32.B08[0] = 4;	//数据长度
//													Temp32.B08[1] = 20;	//82文件中偏移量
//													Temp32.B08[2] = 0x40+4;	//E2中页内偏移量
//													break;
//		
//												default:
//													Err_DI = 1;	//数据标识错
//													break;
//											}
//											break;
											
										default:
											Err_DI = 1;	//数据标识错
											break;
									}
					
									if( Temp32.B08[0] )
									{
										if( IsMultiBcd( Uart[Ch].Buf+22, Temp32.B08[0] ) )	break;
	
										result = Update_ESAM_Bin_Mac( Temp32.B08[3], Temp32.B08[1], Uart[Ch].Buf+22, Temp32.B08[0] );
										if( result != 0x00 )	//当传输的数据MAC 校验错是采用错误信息字ERR 中bit2（密码错/未授权）置位，并按照异常应答帧响应。
										{
											k = 0x00; 
											OutBuf[ k++ ] = 0xFF;
											OutBuf[ k++ ] = 0x04;	//密码错/未授权
											break;
										}
										
										result = UpdateSysPara( Temp32.B08[2], Uart[Ch].Buf+22, Temp32.B08[0] ); //更新XRAM, E2PROM
										if( result ) break;
										
										run_price_flag = 1;

										k = 1;
									}
									break;
									
								case 0x06:	//设置备用套阶梯值+阶梯电价+年结算日
									if( (DI07.B08[1] < 0x0a) || (DI07.B08[1] > 0x0b) || (DI07.B08[0] != 0xFF) ) { Err_DI = 1;	break; } //数据标识错

									if( Uart[Ch].Buf[9] != 70+16 ) break;	//6*4+7*4+4*3=64
									if( IsMultiBcd( Uart[Ch].Buf+22, 70 ) )	break;

									for( i=0; i<13; i++ ) Inverse( Uart[Ch].Buf+22+4*i, 4 );
									for( i=0; i< 6; i++ ) Inverse( Uart[Ch].Buf+74+3*i, 3 );

									memcpy( Buf, Uart[Ch].Buf+22, 70 );	//存储正序的数据
									
									if( DI07.B08[1] < 0x0c )
									{
										Inverse( Uart[Ch].Buf+22, 70 );	//为了符合MAC校验函数的格式
										
										result = Update_ESAM_Bin_Mac( 0x84, 0x04+12*4+(DI07.B08[1]-0x0a)*70, Uart[Ch].Buf+22, 70 );
										if( result != 0x00 )	//当传输的数据MAC 校验错是采用错误信息字ERR 中bit2（密码错/未授权）置位，并按照异常应答帧响应。
										{
											k = 0x00; 
											OutBuf[ k++ ] = 0xFF;
											OutBuf[ k++ ] = 0x04;	//密码错/未授权
											break;
										}
									}

									JTRecord( OptID.B08 );	//阶梯编程记录
							
									for( i=0; i< 6; i++ ) Inverse( Buf+52+3*i, 3 );

									WriteE2WithJieti( DI07.B08[1]-0x06, Buf );
									
									RefreshPrice();
									
									k = 1;
									break;	
									
								default:
									Err_DI = 1;	//数据标识错
									break;
							}
							break;
							
						default:
							Err_DI = 1;	//数据标识错
							break;
					}
					break;
				
				default:
					Err_DI = 1;	//Error: bit2密码错误/未授权
					break;
			}

			if( Err_DI )	//用户对不支持写操作的数据项编程，返回异常应答帧，将错误信息字Bit2置1，即“密码错/未授权”。
			{
				k = 2;
				OutBuf[0] = 0xFF;	//Operation result.
				OutBuf[1] = 0x04;	//Error: bit2密码错误/未授权
				break;
			}
						
			if( k && (OutBuf[0] == 0x00) )
			{
				ProgramRecord( DI07.B08, OptID.B08 );
			}
			break;

		//=====================================================================================
		case 0x11:	//读取
			//……不做编程记录……
			
			if( (Uart[Ch].Buf[9] == 0x09) && (Byte2uInt(DI07.B08) == 0x00030404) )//液晶查看
			{
				Temp16.B16 = GetLcdNo( Uart[Ch].Buf+14 );
				if( Temp16.B16 == 0x00 )	break;//显示项目错误 or 显示序号错
				
				Ext_Disp_Cnt = Temp16.B16;
				Display.Timer = 10;
				Display.Status &= B1111_1110;	//进入循显状态
				freeze_display_flag = 0;	//清结算日电量显示标志
								
				Display.Number  = 0xfc;//液晶查看显示
				Lcdled = 10;//点亮背光
				if( Ext_Disp_Cnt == 200 )Init_Led_Timer = 10;//全显显示点亮led灯
				
				k = 6;
				memcpy( OutBuf+1, Uart[Ch].Buf+14, 5 );
				break;
			}
			
			if( Uart[Ch].Flag&B0000_0001 ) break; //通讯地址全99   不支持
			
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
			else if( (Uart[Ch].Buf[9] == 0x11)||((Uart[Ch].Buf[9] == 0x07) && (Uart[Ch].Buf[10] == 0x01)))//校表操作
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
					
					Check_Err_Pro(Ch, DI07.B08[0]);	//误差调校
						
					Uart[Ch].Overtime_Timer = 2;	//无需应答字节返回
					return;
				}
			}
			else if( Uart[Ch].Buf[9] == 0x04 )
			{
				Times = 1;
			}
			else if( DI07.B32 == 0x0E800009 )
			{
				Uart[Ch].Buf[9] = 4;	//进入蓝牙校表
				Times = 1;
			}
			else if( (DI07.B08[1] == 0xEE) && (DI07.B08[2] == 0xEE) && (DI07.B08[3] == 0xEE) ) //多数据项组合抄读(EEEEEENN)
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
			if( (Uart[Ch].Buf[9] != 0x04) && !ble_inter_flag ) //多数据项组合抄读(EEEEEENN)
			{
				Clear_Wdt();
				memcpy( DI07.B08, Uart[Ch].Buf+14+Loop*5, 4 );
				memcpy( DI08.B08, Uart[Ch].Buf+14+Loop*5, 4 );//备份
				
				k = 0;
				OutBuf[0] = 0x00;
			}
					
			switch( DI07.B08[3] )
			{
				case 0x00:	//当前和结算日 电量数据
					switch( DI07.B08[2] )
					{
						case 0x68:	//组合(高精度总)
						case 0x60:	//正向(高精度总)
						case 0x61:	//反向(高精度总)
						case 0x62:	//组合无功1(高精度总)
						case 0x63:	//组合无功2(高精度总)
						case 0x64:	//第一象限无功(高精度总)
						case 0x65:	//第二象限无功(高精度总)
						case 0x66:	//第三象限无功(高精度总)
						case 0x67:	//第四象限无功(高精度总)
							if( DI07.B08[2] == 0x68 )  DI07.B08[2] = 0x70;
							else DI07.B08[2] += 0x11;
						case 0x15:	//正向(A相)
						case 0x16:	//反向(A相)
						case 0x17:	//组合无功1(A相)
						case 0x18:	//组合无功2(A相)
						case 0x19:	//第一象限无功(A相)
						case 0x1A:	//第二象限无功(A相)
						case 0x1B:	//第三象限无功(A相)
						case 0x1C:	//第四象限无功(A相)
							if( (DI07.B08[2]>=0x15)&&(DI07.B08[2]<=0x1C) ) DI07.B08[2] -= 0x14;				
						case 0x00:	//组合
						case 0x01:	//正向
						case 0x02:	//反向
						case 0x03:	//组合无功1
						case 0x04:	//组合无功2
						case 0x05:	//第一象限无功
						case 0x06:	//第二象限无功
						case 0x07:	//第三象限无功
						case 0x08:	//第四象限无功
						case 0x70:	//组合(高精度总)
						case 0x71:	//正向(高精度总)
						case 0x72:	//反向(高精度总)
						case 0x73:	//组合无功1(高精度总)
						case 0x74:	//组合无功2(高精度总)
						case 0x75:	//第一象限无功(高精度总)
						case 0x76:	//第二象限无功(高精度总)
						case 0x77:	//第三象限无功(高精度总)
						case 0x78:	//第四象限无功(高精度总)
							//结算电量: 定时冻结时间(5)+正向有功总电能(5*4)+反向有功总电能(5*4)+定时冻结变量数据(3)
							result = Cal_Comb( DI07.B08[2]&0x0f, DI07.B08[1], DI07.B08[0], OutBuf+1 );
							if( (result == 0x00) || (result > 25*8) ) break;	//错误的数据标识
							
							//645通道:需要返回电量
							for( i=0; i<result/8; i++ )
							{
								if( (DI07.B08[2]&0x0f)==0 || (DI07.B08[2]&0x0f)==3 || (DI07.B08[2]&0x0f)==4 )
								{
									Hex2Bcd_Dl_G( OutBuf+1+8*i, 0 );	//脉冲数转BCD电量(高精度)(组合)
									if( OutBuf[1+8*i+7] ) OutBuf[1+8*i+4] |= 0x80;	//组合电量<0，最高位置1
								}
								else
									Hex2Bcd_Dl_G( OutBuf+1+8*i, 1 );	//脉冲数转BCD电量(高精度)
								
								if( DI07.B08[2]&0xf0 ) //高精度
									memcpy( OutBuf+1+5*i, OutBuf+1+(8*i+0), 5 );	//xxxxxxxxxxxx.xxxx变成xxxxxx.xxxx
								else
									memcpy( OutBuf+1+4*i, OutBuf+1+(8*i+1), 4 );	//xxxxxxxxxxxx.xxxx变成xxxxxx.xx
							}
							
							if( DI07.B08[2]&0xf0 )	//高精度
								k = 0x01+result/8*5;
							else 
								k = 0x01+result/8*4;
							break;
						
						case 0x0B:	//当前/上1结算周期用电量
						case 0x0C:	//当前/上1月度用电量
							if( DI07.B08[0] > max_histroy_p ) break;
						case 0x0D:	//当前/上1~6年度用电量
							if( (DI07.B08[1] != 0x00) || ((DI07.B08[2] == 0x0D)&&(DI07.B08[0] > 0x06)) ) break;
//							if( (!BDMODE) && (DI07.B08[2] == 0x0D) ) break;

							Cal_Comb_Usedl( DI07.B08[2]-0x0B, DI07.B08[0], OutBuf+1 );//时间4/预留4+高精度电量8字节
							
							if( OutBuf[5+7] ) OutBuf[5+4] |= 0x80;	//组合电量<0，最高位置1	
							
							if( DI07.B08[2] == 0x0D )
							{
								k = 9;
								memcpy( OutBuf+5, OutBuf+5+1, 4 );//xxxxxxxxxxxx.xxxx变成xxxxxx.xx
							}
							else
							{
								k = 5;
								memcpy( OutBuf+1, OutBuf+5+1, 4 );//xxxxxxxxxxxx.xxxx变成xxxxxx.xx
							}
							break;
							
						case 0x50:	//当前/上1~12月度用电量	高精度
							if( (DI07.B08[1] != 0x00) || (DI07.B08[0] > max_histroy_p) ) break;
							
							Cal_Comb_Usedl( 0x01, DI07.B08[0], OutBuf+1 );//时间4/预留4+高精度电量8字节
							
							if( OutBuf[5+7] ) OutBuf[5+4] |= 0x80;	//组合电量<0，最高位置1	
							
							k = 6;
							memcpy( OutBuf+1, OutBuf+5, 5 );//xxxxxxxxxxxx.xxxx变成xxxxxx.xxxx
							break;
							
						case 0xD0:	//电量集合
							if( (DI07.B08[1] != 0xFF) || (DI07.B08[0] != 0x00) ) break;
							
							memset( OutBuf+1, 0xff, 56 );
							DltoEepromBuf(0);//当前正反向总
							Comp_RpdltoEepromBuf(8);//当前组合无功1/2总
							Comm_Calculate_Comp_Rp( Eeprom.Buffer, 4, 0x00 );
												
							Four_RpdltoEepromBuf(16);//当前四象限无功总
							Comm_Calculate_Dl( Eeprom.Buffer+16, 4, 0x00 );
							
							memcpy( OutBuf+1, Eeprom.Buffer, 32 );
							memcpy( OutBuf+1+32, Eeprom.Buffer, 8 );//当前正反向A相
							
							k = 1+56;
							break;							
							
						case 0xFE:	//结算时间
							if( (DI07.B08[1] != 0x00) || (DI07.B08[0] == 0) || ((DI07.B08[0]>max_histroy_p)&&(DI07.B08[0]!=0xFF)) ) break;
							
							result = Cal_Comb( 0x09, 0x00, DI07.B08[0], OutBuf+1 );	//返回结算时间
							
							k = 0x01+result;
							break;
						
						default:
							break;
					}
					break;
				
				case 0x02:	//变量数据标识
					if( DI07.B08[2] == 0x90 && DI07.B08[1] == 0xff && DI07.B08[0] == 0x00 ) //变量集合
					{
						memset( OutBuf+1, 0xff, 72 );
						memcpy( OutBuf+1, 		Emu_Data.U.B08, 2 );//A相电压
						memcpy( OutBuf+1+6, 		Emu_Data.I1.B08, 3 );//A相电流
						if( dl_back_flag ) OutBuf[1+6+2] |= 0x80;
						memcpy( OutBuf+1+6+9, 		Emu_Data.I2.B08, 3 );//零线电流
						if( dln_back_flag ) OutBuf[1+6+9+2] |= 0x80;
						memcpy( OutBuf+1+6+12, 		Emu_Data.Freq.B08, 2 );//频率
						memcpy( OutBuf+1+6+12+2, 	Emu_Data.P1.B08, 3 );//有功功率
						if( dl_back_flag ) OutBuf[1+6+12+2+2] |= 0x80;
						memcpy( OutBuf+1+6+12+2+3, 	Emu_Data.P1.B08, 3 );//A相有功功率
						if( dl_back_flag ) OutBuf[1+6+12+2+3+2] |= 0x80;
						memcpy( OutBuf+1+6+12+2+12, 	Emu_Data.Pav.B08, 3 );//一分钟平均有功功率
						if( dl_back_flag ) OutBuf[1+6+12+2+12+2] |= 0x80;
						memcpy( OutBuf+1+6+12+2+15, 	Emu_Data.Q1.B08, 3 );//无功功率
						if( dl_back_flag2 ) OutBuf[1+6+12+2+15+2] |= 0x80;
						memcpy( OutBuf+1+6+12+2+15+3, 	Emu_Data.Q1.B08, 3 );//A相无功功率
						if( dl_back_flag2 ) OutBuf[1+6+12+2+15+3+2] |= 0x80;
						memcpy( OutBuf+1+6+12+2+15+12, 	Emu_Data.Qav.B08, 3 );//一分钟无功平均功率
						if( dl_back_flag2 ) OutBuf[1+6+12+2+15+12+2] |= 0x80;
						memcpy( OutBuf+1+6+12+2+30, 	Emu_Data.Cosa.B08, 2 );//功率因数
						if( dl_back_flag ) OutBuf[1+6+12+2+30+2] |= 0x80;
						memcpy( OutBuf+1+6+12+2+30+2, 	Emu_Data.Cosa.B08, 2 );//A相功率因数
						if( dl_back_flag ) OutBuf[1+6+12+2+30+2+2] |= 0x80;
						memcpy( OutBuf+1+6+12+2+30+14+6,&Fun_Para.Voltage_B, 2 );//时钟电池电压
						
						k = 1+72;
						break;
					}
					
					if( DI07.B08[2] == 0x80 )
					{
						if( DI07.B08[1] != 0x00 ) break;

//						if( (!BDMODE) && ( (DI07.B08[0] == 0x0b) || (DI07.B08[0]==0x20) || (DI07.B08[0]==0x21))) break;	//远程模式不支持抄读本地参数
							
						switch( DI07.B08[0] )
						{
							case 0x01:	//零线电流	XXX.XXX	3	A
								Temp08 = 3;
								Temp32.B32 = Emu_Data.I2.B32;
								if((dln_back_flag) && (Emu_Data.I2.B32)) Temp32.B08[2] |= 0x80;
								break;
							
							case 0x02:	//电网频率	XX.XX	2	Hz
								Temp08 = 2;
								Temp32.B32 = Emu_Data.Freq.B32;
								break;
								
							case 0x03:	//一分钟有功总平均功率	XX.XXXX	3	kW
								Temp08 = 3;
								Temp32.B32 = Emu_Data.Pav.B32;
								if( dl_back_flag )	Temp32.B08[2] |= 0x80;
								break;
								
							case 0x07:	//表内温度	XXX.X	2	℃
								Temp08 = 2;
								Temp32.B32 = Fun_Para.Temper_M;
								break;
								
							case 0x08:	//时钟电池电压(内部)	XX.XX	2	V
							case 0x09:
								Temp08 = 2;
								Temp32.B32 = Fun_Para.Voltage_B;
								break;
								
//							case 0x09:	//停电抄表电池电压 (外部)	XX.XX	2	V
//								break;
								
							case 0x0A:	//内部电池工作时间	XXXXXXXX	4	分
								Temp08 = 4;
								Get_Keep_Timer(4, Temp32.B08);
								break;
								
							case 0xFA:	//电池欠压次数(内部扩展)	XXXXXX		3	次
								Temp08 = 3;
								Read_Event_Number( Temp32.B08, ee_batterlow_inpage );
								break;	
							
							case 0x0B:	//当前阶梯电价	XXXX.XXXX	4	元/kWh
								Temp08 = 4;
								Exchange(Temp32.B08, Price.Current_L.B08, 4);
								break;
						
							case 0x0E:	//火线电流		XXX.XXX 3 A
								Temp08 = 3;
								Temp32.B32 = Emu_Data.I1.B32;
								if( dl_back_flag )	Temp32.B08[2] |= 0x80;
								break;
								
							case 0x0F:	//火线有功功率	XX.XXXX 3 kW
								Temp08 = 3;
								Temp32.B32 = Emu_Data.P1.B32;
								if( dl_back_flag )	Temp32.B08[2] |= 0x80;
								break;
								
							case 0x10:	//火线功率因数	X.XXX 2
								Temp08 = 2;
								Temp32.B32 = Emu_Data.Cosa.B32;
								if( dl_back_flag )	Temp32.B08[1] |= 0x80;
								break;
							
							case 0x20:	//当前电价
								Temp08 = 4;
								Exchange(Temp32.B08, Price.Current.B08, 4);								
								break;
								
//							case 0x21:	//当前费率电价
//								Temp08 = 4;
//								Exchange(Temp32.B08, Price.Current_F.B08, 4);
//								break;

							case 0x25:	//一分钟无功总平均功率	XX.XXXX	3	kar
								Temp08 = 3;
								Temp32.B32 = Emu_Data.Qav.B32;
								if( dl_back_flag2 )	Temp32.B08[2] |= 0x80;
								break;
								
							case 0x31:	//上电运行时间	NNNNNNNN	4	分
								Temp08 = 4;
								Temp32.B32 = Meter_Run_Timer4/60;
								Hex2Bcd_SS( Temp32.B08, Temp32.B08, 4 );
								break;	
						
							case 0x32:	//当前象限
								Temp08 = 1;
								if( (dl_back_flag == 0) && (dl_back_flag2 == 0) ) Temp32.B32=1;
								else if( (dl_back_flag == 1) && (dl_back_flag2 == 0) ) Temp32.B32=2;
								else if( (dl_back_flag == 1) && (dl_back_flag2 == 1) ) Temp32.B32=3;
								else Temp32.B32=4;
								break;		

							case 0x86:	//当前阶梯
								Temp08 = 1;
								if(Tariff.Current_Ladder != 0xff)
									Temp32.B32 = Tariff.Current_Ladder+1;
								else
									Temp32.B32 = 0x00;								
								break;
								
							case 0x22:	//身份认证时效剩余时间	XXXX 	2	分钟
//							case 0x23:	//红外认证时效剩余时间	XXXX 	1  	分钟
							case 0x83:	//蓝牙认证剩余时间 1 分钟
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
					else if( DI07.B08[2] == 0x81 )//蓝牙连接设备信息
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
							case 0x01:	//A相电压	XXX.X	2
							case 0x02:	//A相电流	XXX.XXX	3
								if( (DI07.B08[1] == 0x01) || (DI07.B08[1] == 0xFF) )
								{
									if( DI07.B08[2] == 0x01 ) Temp08 = 2;
									else Temp08 = 3;
								}
								break;

							case 0x03:	//瞬时总有功功率	XX.XXXX	3
							case 0x04:	//瞬时总无功功率	XX.XXXX	3
							case 0x05:	//瞬时总视在功率	XX.XXXX	3
							case 0x06:	//总功率因数		X.XXX	2
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
							if( DI07.B08[2] == 0x04 ) //瞬时总无功功率
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
					
				case 0x03:	//事件记录数据标识
				case 0x03+0x80:	//事件记录数据标识				
					if( ((DI07.B08[3]&0x7f) == 0x03) && ((DI07.B08[2] == 0x70)||(DI07.B08[2] == 0x10)) && (DI07.B08[1] == 0x01) ) DI07.B08[1] = 0x00; //同时支持A相
					if( ((DI07.B08[3]&0x7f) == 0x03) && (DI07.B08[2] == 0x70) && (DI07.B08[1] == 0x00) && (DI07.B08[0] == 0x00) )
					{
						k = 1+ee_dayvolpassnote_len;
						CalLoad( OutBuf+1, 0 );	//计算当前日电压合格率
						break;
					}
					else if( ((DI07.B08[3]&0x7f) == 0x03) && (DI07.B08[2] == 0x10) && (DI07.B08[1] == 0x00) && (DI07.B08[0] == 0x00) )
					{
						k = 1+ee_monvolpassnote_len;
						CalLoad( OutBuf+1, 1 );	//计算当前月电压合格率
						break;
					}
					else if( ((DI07.B08[3]&0x7f) == 0x03) && ((DI07.B08[1] == 0x02) || (DI07.B08[1] == 0x03)) && (DI07.B08[2] == 0xc0) )
					{
						
						RdHisPd( DI07.B08, OutBuf );//读停电统计数据
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
					
				case 0x10:	//失压记录
				case 0x19:	//过流记录
				case 0x1D:	//拉闸记录，跳闸记录
				case 0x1E:	//合闸记录
				case 0x22:	//电池欠压记录
				case 0x10+0x80:	//失压记录
				case 0x19+0x80:	//过流记录
				case 0x1D+0x80:	//拉闸记录，跳闸记录
				case 0x1E+0x80:	//合闸记录
				case 0x22+0x80:	//电池欠压记录
					k = Rd_Relay_Buy_Rec( DI07.B08, OutBuf );
					if( k == 0x00 ) break;
					
					k += 1;
					OutBuf[0] = 0x00;	//结果
					break;

				case 0x04:	//参变量数据标识
					switch( DI07.B08[2] )
					{
						case 0x00:	
							switch( DI07.B08[1] ) 
							{
								case 0x01:	
									switch( DI07.B08[0] )
									{
										case 0x01:	//日期及星期(其中0代表星期天)	YYMMDDWW  	4	年月日星期	
											k = 5;
											OutBuf[1] = Sclock.Clockmain[3];
											OutBuf[2] = Sclock.Clockmain[4];
											OutBuf[3] = Sclock.Clockmain[5];
											OutBuf[4] = Sclock.Clockmain[6];
											break;
											
										case 0x02:	//时间                          hhmmss    	3	时分秒      
											k = 4;
											OutBuf[1] = Sclock.Clockmain[0];
											OutBuf[2] = Sclock.Clockmain[1];
											OutBuf[3] = Sclock.Clockmain[2];
											break;
											
										case 0x05:	//校表脉冲宽度                  XXXX      	2	毫秒        
											k = 3;
											OutBuf[1] = Hex_To_Bcd(Def_Plusevalidtimer*4);
											OutBuf[2] = 0x00;
											break;
											
										case 0x0A:	//两套阶梯时区切换时间		YYMMDDhhmm 	5
										case 0x06:	//两套时区表切换时间            YYMMDDhhmm	5	年月日时分, 密文＋MAC
										case 0x07:	//两套日时段切换时间            YYMMDDhhmm	5	年月日时分, 密文＋MAC
										case 0x09:	//两套阶梯切换时间		YYMMDDhhmm	5	年月日时分, 密文＋MAC
											k = 6;
											if( DI07.B08[0] == 0x0A ) Exchange( OutBuf+1, Starttime.LadSQ, 5 );
											else Exchange( OutBuf+1, Starttime.Shiqu+5*(DI07.B08[0]-0x06), 5 );
											break;
											
										case 0x0C:	//日期、星期(其中0代表星期天)及时间	YYMMDDWWhhmmss	7 年月日星期时分秒
											k = 8;
											memcpy( OutBuf+1, Sclock.Clockmain, 7 );
											break;
											
										case 0x0D:	//电能表蓝牙MAC地址(HEX码)
											Bcd2Hex_LS(Comm_Addr.Comm_Id, OutBuf+1, 6);
											OutBuf[6]  = 0xC0;
											
											k = 7;
											break;
											
										default:
											break;
									}										
									break;
									
								case 0x02:	  
									//年时区数（1）＋日时段表数（1）＋日时段数 （1）＋费率数（1）＋公共假日数（1）+谐波分析次数（1）+阶梯数（1）＋密钥数（1）＋crc（2）
									if( (DI07.B08[0]) && (DI07.B08[0]<=ee_feiknumber_lenth) )
									{
//										if( (!BDMODE) && (DI07.B08[0] == 0x07) ) break;
											
										k = 2;
										OutBuf[1] = Feik.Num[DI07.B08[0]-1];
										if( DI07.B08[0] == 5 )	//公共假日数
										{
											OutBuf[2] = 0x00;
											k += 1;
										}
									}
									else if( DI07.B08[0]==0x09 ) //当前日时段表
									{
										k = ee_shiduantable_lenth+1;
										memcpy( OutBuf+1, Tariff.Table, ee_shiduantable_lenth );
									}
									break;
									
								case 0x03:
									switch( DI07.B08[0] )
									{
										case 0x01:	//自动循环显示屏数            	NN      1   个	
										case 0x02:	//每屏显示时间					NN		1	秒	
										case 0x03:	//显示电能小数位数				NN		1	位	
										case 0x04:	//显示功率（最大需量）小数位数	NN      1   位  
										case 0x05:	//按键循环显示屏数            	NN      1   个  
										case 0x08:	//上电全显时间	NN	1	位
//											if( DI07.B08[0] == 0x08 ) Temp32.B08[2] = 0x05;
//											else Temp32.B08[2] = DI07.B08[0]-1;
											
											k = 2;
											OutBuf[1] = Hex_To_Bcd(*(&Display_Para.S_Number+DI07.B08[0]-1));
											break;
											
										case 0x06:	//电流互感器变比              	NNNNNN	3       break;
										case 0x07:	//电压互感器变比              	NNNNNN	3	    break;
											//报警金额1限值(4)＋报警金额2限值(4)+互感器变比(6)＋表号(6)+客户编号(6)+电卡类型(1)+身份认证时效(2)
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
										case 0x01:	//通信地址                     	NNNNNNNNNNNN	6
											k = 7;
											Exchange( OutBuf+1, Comm_Addr.Comm_Id, 6 );
											break;

										case 0x02:	//表号                         	NNNNNNNNNNNN	6
											k = 7;
											Exchange( OutBuf+1, Esam_Para.Meter_Id, 6 );
											break;
											
										case 0x04:	//额定电压（ASCII 码）         XXXXXXXXXXXX	6	
										case 0x05:	//额定电流/基本电流（ASCII 码）XXXXXXXXXXXX	6
										case 0x06:	//最大电流（ASCII 码）         XXXXXXXXXXXX	6
										case 0x07:	//有功准确度等级（ASCII 码）   XXXXXXXX   	4
										case 0x08:	//无功准确度等级（ASCII 码）   XXXXXXXX   	4
//										case 0x0B:	//电表型号（ASCII 码）         XX…XX      	10 
										case 0x0D:	//协议版本号（ASCII 码）        XX…XX      	16
										case 0x16: 	//最小电流（ASCII 码）         XXXXXXXXXXXX	6
										case 0x17: 	//转折电流（ASCII 码）         XXXXXXXXXXXX	6
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
										
										case 0x0B:	//电表型号（ASCII 码）         XX…XX      	10 
											if(DI07.B08[0] == 0x0B)
											{
												Code_Flash_Char = (uint08*)MaterType;
												Temp16.B08[0] = ee_matertype_page; //电表型号
												Temp16.B08[1] = ee_matertype_inpage;
												Temp08 = ee_matertype_lenth;
											}
											result = I2C_Read_Eeprom( Temp16.B08[0], Temp16.B08[1], OutBuf+1, Temp08 );
																						
											for( i=0; i<Temp08; i++ )	//如果全部为0xff则采用默认的值
											{
												if( OutBuf[1+i] != 0xff ) break;
											}
											
											if( result || (i==Temp08) )
											{
												Exchange( OutBuf+1, Code_Flash_Char, Temp08 );  
											}
											k = Temp08+1;
											break; 
										
										case 0x0C:	//生产日期（ASCII 码）         XX…XX      	10
										case 0x03:	//资产管理编码（ASCII 码）     NN…NN      	32
										case 0x0F:	//电能表位置信息				11
											if(DI07.B08[0] == 0x0c) 
											{
												Temp16.B08[0] = ee_meterdate_page;//生产日期
												Temp16.B08[1] = ee_meterdate_inpage;
												Temp08 = 10;
											}
											else if(DI07.B08[0] == 0x03) 
											{
												Temp16.B08[0] = ee_zichannum_page;//资产管理编号
												Temp16.B08[1] = ee_zichannum_inpage;
												Temp08 = 32;
											}
											else
											{
												Temp16.B08[0] = ee_meterpos_page;//电能表位置信息
												Temp16.B08[1] = ee_meterpos_inpage;
												Temp08 = 11;
											}
											I2C_Read_Eeprom( Temp16.B08[0], Temp16.B08[1], OutBuf+1, Temp08 );
											k = Temp08+1;
											break; 	  											          	

										case 0x09:	//电表有功常数                  XXXXXX      	3	imp/kWh
											k = 4;
											Exchange( OutBuf+1, Meter.Const.B08+1, 3 );//转换成低字节在前
											break;
											
										case 0x0A:	//电表无功常数                  XXXXXX      	3   	imp/kvarh   
											k = 4;
											Exchange( OutBuf+1, Meter.Const.B08+1, 3 );//转换成低字节在前
											break;
											
										case 0x0E:	//客户编号						NNNNNNNNNN		6
											k = 7;
											Exchange( OutBuf+1, Esam_Para.User_Id, 6 );
											break;

										default:	break;                                      		
									}
									break;
									
								case 0x05:	  
									switch( DI07.B08[0] )
									{
										case 0xFF:	//电表运行状态字块	XXXX	14	
										case 0x01:	//电表运行状态字1   XXXX	2
											//[0].B16	电表运行状态字1					
											//bit15:	时钟故障
											//bit14:	透支状态
											//bit13:	存储器故障
											//bit12:	内部程序错误（预留）
											//bit09:	ESAM错
											//bit08:	控制回路错误
											//bit07:	reserved.
											//bit06:	费控模式状态  (0本地，1远程)
											//bit05:	无功功率方向	(0 正向、1 反向)
											//bit04:	有功功率方向	(0 正向、1 反向)
											//bit03:	停电抄表电池	(0 正常，1 欠压)
											//bit02:	时钟电池		(0 正常，1 欠压)    
											//bit01:	需量积算方式	(0 滑差，1 区间)
											//bit00:	计量单元异常
											Temp16.B16 = 0x00;
											
											if( clock_error || (ChkLastclockerrRcdTime() == 1) )	//bit15:	时钟故障  
											{
												Temp16.B08[0] |= B1000_0000;
											}
											
//											if( remainder_tick_flag )	//bit14:	透支状态
//											{
//												Temp16.B08[0] |= B0100_0000;
//											}

											if( eeprom_error_flag )	//bit13:	存储器故障
											{
												Temp16.B08[0] |= B0010_0000;
											}
											
											if( esam_error )	//bit09:	ESAM 状态		(0 正常，1 故障)
											{
												Temp16.B08[0] |= B0000_0010;
											}
											
											if( relay_error )	//bit08:	控制回路错误
											{
												Temp16.B08[0] |= B0000_0001;
											}
											
//											if( !BDMODE )		//bit06:	费控模式状态(0 本地，1 远程)
											{
												Temp16.B08[1] |= B0100_0000;
											}
																							
											if( dl_back_flag2 )			//无功功率方向(0 正向、1 反向)
											{
												Temp16.B08[1] |= B0010_0000;
											}
											
											if( dl_back_flag )			//有功功率方向(0 正向、1 反向)
											{
												Temp16.B08[1] |= B0001_0000;
											}

											if( low_voltage_flag || Bat_Delay_Timer )//停电抄表电池(0 正常，1 欠压)+时钟电池(0 正常，1 欠压)
											{
												Temp16.B08[1] |= B0000_1100;
											}
											
											if( cal_err_flag )			//计量单元异常
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
											
										case 0x02:	//电表运行状态字2	XXXX	2	
											Temp16.B16 = 0x00;
											if( dl_back_flag )	//bit0：A 相有功功率方向( 0 正向，1 反向 )
											{
												Temp16.B08[1] |= B0000_0001;
											}
											if( dl_back_flag2 )	//bit4：A 相无功功率方向( 0 正向，1 反向 )
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
											
										case 0x03:	//电表运行状态字3	XXXX	2	
											//[2].B16	电表运行状态字3(操作类)
											//bit15:	保留
											//bit14:	保留
											//bit13:	身份认证状态(0失效，1有效)
											//bit12:	保电状态	(0非保电,1保电)
											//bit11:	当前阶梯	(0当前套阶梯，1备用套阶梯)
											//bit10:	当前阶梯表(0第1张阶梯表，1第2张阶梯表)
											//bit9~8:	电能表类型, 		(00 非预付费表,01 电量型预付费表,10 电费型预付费表)	
											//bit7:		预跳闸报警状态		(0 无，1 有)
											//bit6:		继电器命令状态		(0 通，1 断)
											//bit5:		当前运行时区		(0 第一套，1 第二套)
											//bit4:		继电器状态			(0 通，1 断)
											//bit3:		蓝牙认证			(0 时效，1 有效)
											//bit2~1:	供电方式			(00 主电源，01 辅助电源，10 电池供电)
											//bit0:		当前运行时段		(0 第一套，1 第二套)
											Temp16.B16 = 0x00;
											
											if( Comm_Auth_Judge() )			//bit13:	身份认证状态
											{
												Temp16.B08[0] |= B0010_0000;
											}
											
											if( relay_commu_close_flag )		//bit12:	保电状态
											{
												Temp16.B08[0] |= B0001_0000;
											}
											
//											if( BDMODE )
											{
												if( Tariff.CurLad_N )	
												{
													Temp16.B08[0] |= B0000_0100;	//bit10: 当前阶梯表 (0第1张阶梯表,1第2张阶梯表)
												}
												
//												Temp16.B08[0] |= B0000_0010;	//bit9~8：电费型预付费表
											}

											if( relay_commu_alarm_flag )		//bit7：预跳闸报警状态
											{
												Temp16.B08[1] |= B1000_0000;
											}

											if( relay_commu_open_flag )		//bit6：继电器命令状态
											{
												Temp16.B08[1] |= B0100_0000;
											}

											if( Tariff.Status&B0000_1000 )		//bit5：当前运行时区
											{
												Temp16.B08[1] |= B0010_0000;
											}

											if( comm_relaystatus_flag )		//bit4：继电器状态
											{
												Temp16.B08[1] |= B0001_0000;
											}

											if( IR_EnTimer )			//bit3：蓝牙认证/编程允许
											{
												Temp16.B08[1] |= B0000_1000;
											}

											if( Tariff.Status&B0000_0100 )		//bit0：当前运行时段
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

										case 0x04:	//电表运行状态字4   XXXX	2	
											Temp16.B16 = 0x00;
											if( load_over_flag )	//bit4：A 相过流
											{
												Temp16.B08[1] |= B0001_0000;
											}
											
											if( lost_v_flag )	//bit0：A 相失压
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
											
										case 0x05:	//电表运行状态字5   XXXX	2	
										case 0x06:	//电表运行状态字6   XXXX	2	
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
											
										case 0x07:	//电表运行状态字7   XXXX	2	（合相故障状态）
											//bit10:	开表盖
											Temp16.B16 = 0x00;
											if( Cover.Status )	//bit9:	开表盖
											{
												Temp16.B08[0] |= B0000_0010;
											}
											if( below_60u_flag )	//bit5:	掉电
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
											
										case 0x08:	//密钥状态字	XXXXXXX		4
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
										case 0x01:  //有功组合方式特征字  	NN	1	
											//波特率特征字（5）＋有功组合方式特征字1(1)＋冻结数据模式字(6)＋电表运行特征字1(1) +上报模式字(6)+crc（2）
											k = 2;
											OutBuf[1] = Mode.Comp_B;
											break;
											
										case 0x02:  //无功组合方式1 特征字  NN	1
											k = 2;
											OutBuf[1] = Mode.Rpcomp[0];	
											break;
											
										case 0x03: //无功组合方式2 特征字  NN	1	
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
										case 0x01:	//调制型红外光口波特率特征字	NN  1
//										case 0x02:	//接触式红外光口波特率特征字    NN  1											
										case 0x03:	//通信口1 波特率特征字          NN  1
//										case 0x04:	//通信口2 波特率特征字          NN  1
										case 0x05:	//通信口3 波特率特征字          NN  1
										case 0xfd:	//通信口3 波特率特征字          NN  1 (当前)
											//波特率特征字（5）＋有功组合方式特征字1(1)＋冻结数据模式字(6)＋电表运行特征字1(1) +上报模式字(6)+crc（2）
											k = 2;
											if( DI07.B08[0] == 3 ) OutBuf[1] = Mode.Bps[0];
//											else if( DI07.B08[0] == 4 ) OutBuf[1] = Mode.blebps;
											else if( DI07.B08[0] == 5 ) OutBuf[1] = Mode.Zbbps; //缺省值
											else if( DI07.B08[0] == 0xfd ) OutBuf[1] = Zbbps; //当前
											else OutBuf[1] = DI07.B08[0]+0x03;
											break;

										default:
											break;
									}
									break;
									
								case 0x08:	
									switch( DI07.B08[0] )
									{
										case 0x01:	//周休日特征字          	NN	1
											k = 2;
											OutBuf[1] = Week_Holiday.Status;
											break;
											
										case 0x02:	//周休日釆用的日时段表号	NN	1
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
										case 0x01:	//负荷记录起始时间		MMDDhhmm	4
											k = 5;
											Exchange( OutBuf+1, Display_Para.Lstarttimer+1, 4 );
											break;
												
										case 0x02:	//第1 类负荷记录间隔时间    NNNN	2
										case 0x03:	//第2 类负荷记录间隔时间    NNNN	2
										case 0x04:	//第3 类负荷记录间隔时间    NNNN	2
										case 0x05:	//第4 类负荷记录间隔时间    NNNN	2
										case 0x06:	//第5 类负荷记录间隔时间    NNNN	2
										case 0x11:	//组合有功费率1~ 4电能负荷记录间隔时间    NNNN	2
										case 0x12:	//组合有功费率5~ 8电能负荷记录间隔时间    NNNN	2
//										case 0x13:	//组合有功费率9~12电能负荷记录间隔时间    NNNN	2
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
									//波特率特征字（5）＋有功组合方式特征字1(1)＋冻结数据模式字(6)＋电表运行特征字1(1) +上报模式字(6)+crc（2）
									switch( DI07.B08[0] )
									{
										case 0x01:	//负荷记录模式字	NN	1/2								
										case 0x02:	//定时冻结数据模式字	NN	1/2
										case 0x03:	//瞬时冻结数据模式字	NN	1/2
										case 0x04:	//约定冻结数据模式字    NN	1/2
										case 0x05:	//整点冻结数据模式字    NN	1/2
										case 0x06:	//日冻结数据模式字      NN	1/2
										case 0x07:	//月冻结数据模式字      NN	1/2
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
										case 0x01:	//每月第1 结算日	DDhh	2	日时
										case 0x02:	//每月第2 结算日    DDhh	2	日时
										case 0x03:	//每月第3 结算日    DDhh	2	日时
											ReadE2WithBackup( ee_histroyparameter_page, ee_histroyparameter_inpage, Buf, ee_histroyparameter_lenth );

											k = 3;
											OutBuf[1] = Buf[2*(DI07.B08[0]-1)+0];
											OutBuf[2] = Buf[2*(DI07.B08[0]-1)+1];
											break;

										default:
											break;
									}
									break;
								
								case 0x0C:	//0级密钥~9级密钥：02级密码，04级密码
//									if( DI07.B08[0] && (DI07.B08[0]<=0x0A) )
//									{
										k = 2;
										OutBuf[0] = 0xFF; //结果
										OutBuf[1] = 0x04; //Error: bit2密码错误/未授权
//									}
									break;
									
								case 0x0E:
									switch( DI07.B08[0] )
									{
										case 0x03:	//电压上限值	NNN.N	2	V
										case 0x04:	//电压下限值	NNN.N	2	V
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
										case 0x01:	//电表运行特征字1	NN	1
											//波特率特征字（5）＋有功组合方式特征字1(1)＋冻结数据模式字(6)＋电表运行特征字1(1) +上报模式字(6)+crc（2）
											k = 2;
											OutBuf[1] = Mode.Feature1;
											break;
											
										case 0x04:	//主动上报模式字	NNNNNNNNNNNNNNNN	8
											//波特率特征字（5）＋有功组合方式特征字1(1)＋冻结数据模式字(5)＋电表运行特征字1(1)＋上报模式字(6) + crc（2）
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
										case 0x01:	//整点冻结起始时间	YYMMDDhhmm	5	年月日时分
											Temp16.B08[0] = 5;	//长度
											Temp16.B08[1] = 0;	//偏移量
											break;
											
										case 0x02:  //整点冻结时间间隔	NN          1	分钟      
											Temp16.B08[0] = 1;	//长度
											Temp16.B08[1] = 5;	//偏移量
											break;
											
										case 0x03:  //日冻结时间      	hhmm        2	时分      
											Temp16.B08[0] = 2;	//长度
											Temp16.B08[1] = 6;	//偏移量
											break;
											
										case 0x04:	//定时冻结时间	4	MMDDhhmm
											Temp16.B08[0] = 4;	//长度
											Temp16.B08[1] = 8;	//偏移量
											break;
																						
										default:
											Temp16.B08[0] = 0;	//长度
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
//										case 0x01:	//无线通信在线及信号强弱指示	NN	1	
//											break;
//											
//										default:
//											break;
//									}
//									break;
									
								case 0x14:
									switch( DI07.B08[0] )
									{
										case 0x01:	//跳闸延时时间（NNNN 为跳闸前告警时间）	NNNN	2
										case 0x02:	//继电器拉闸控制电流门限值	XXX.XXX	3
										case 0x03:	//继电器延时拉闸时间	XXXX	2
//										case 0x04:	//红外认证时效	XXXX	1
										case 0x05:	//上报复位时间	XXXX	1
										case 0x06:	//蓝牙认证时效 XX 1
											if( DI07.B08[0] == 0x02 )
											{
												Temp16.B08[0] = 0;	//偏移地址0
												Temp16.B08[1] = 3;	//字节数
											}
											else if( DI07.B08[0] >= 0x04 )
											{
												Temp16.B08[0] = (DI07.B08[0]&1)+0x07;//偏移地址7,8
												Temp16.B08[1] = 1;
											}
											else
											{
												Temp16.B08[0] = DI07.B08[0]+2;//偏移地址3,5	
												Temp16.B08[1] = 2;	
											}

											k = Temp16.B08[1]+1;
											Exchange( OutBuf+1, Mode.Limit_I+Temp16.B08[0], Temp16.B08[1] );	
											break;	
											
										case 0x08:	//蓝牙从机1//2/3 MAC地址（HEX格式）
											I2C_Read_Eeprom(ee_bleslamac_page, ee_bleslamac_inpage, OutBuf+1, ee_bleslamac_lenth);
											
											k = 19;
											break;
											
										case 0x09:	//蓝牙参数信息
											I2C_Read_Eeprom(ee_blerefer_page, ee_blerefer_inpage, OutBuf+1, ee_blerefer_lenth);
											
											k = 14;
											break;
											
										case 0x0A:	//蓝牙广播时间
											I2C_Read_Eeprom(ee_blerefer_page, ee_blegbtime_inpage, OutBuf+1, ee_blegbtime_lenth);
											
											k = 2+1;
											break;
											
										case 0x0b:	//上行模块ID	XXXXXXXXXXXX	6
											k = 7;
//											I2C_Read_Eeprom( ee_zbid_bk_page, ee_zbid_bk_inpage, OutBuf+1, ee_zbid_bk_lenth ); //读原载波id备份(通讯抄读专用)
											memcpy( OutBuf+1, Esam_Para.Zb_Id, 6 );
											break;	
										
										case 0xee:	//继电器合闸允许方式	XX	1
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
										case 0x01:	 //主动上报状态字	NNNNNNNNNNNNNNNNNNNNNNNN	12+N
											k = Ready_Reportdata( OutBuf );
											Reset_Rep_Timer = Calculate_Timer(3);		//启动复位上报状态字定时器
											break;
											
//										case 0x02:	 //插卡状态字	NNNN	2	
//											k = 3;
//											OutBuf[1] = InsertCardSta;
//											OutBuf[2] = 0x00;
//											InsertCardSta = 0;	//清插卡状态字为未知
//											break;
											
										default:
											break;
									}
									break;
									
								case 0x17:
									switch( DI07.B08[0] )
									{
										case 0x01:	//售电方	NNNNNNNN	4
										case 0x02:	//购电方	NNNNNNNN	4
										case 0x03:	//用电容量		NNNNNNNNNNNNNNNN	8
										case 0x04:	//对应费率时段电价	NNNNNNNNNNNNNNNN	8
										case 0xFF:	//集合
											if( DI07.B08[0] == 0x01 || DI07.B08[0] == 0x02 )
											{
												Temp16.B08[0] = 0+(DI07.B08[0]-1)*4;	//偏移地址
												Temp16.B08[1] = 4;	//字节数
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

						case 0x01:	//第一套时区表和日时段表数据
						case 0x02:	//第二套时区表和日时段表数据
							//年时区数（1）＋日时段表数（1）＋日时段数 （1）＋费率数（1）＋公共假日数（1）+谐波分析次数（1）+阶梯数（1）＋密钥数（1）＋crc（2）
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
										case 0x00:	//第一套时区表数据, 第1~14时区起始日期及日时段表号(14*3), MMDDNN
											Temp32.B08[0] = Bcd_To_Hex(Feik.Num[0]);	//设定的"年时区数"
											if( Temp32.B08[0] > MAXREGION )
											{
												Temp32.B08[0] = MAXREGION;
											}

											I2C_Read_Eeprom( Temp16.B08[0], 0x00, Buf, ee_shiqu_lenth );
											
											k = Temp32.B08[0]*3+1;
											memcpy( OutBuf+1, Buf, k-1 );
											break;
											
										default:
//											Temp32.B08[0] = Bcd_To_Hex(Feik.Num[1]);	//设定的"日时段表数"
//											if( Temp32.B08[0] > MAXSIDUANTB )
//											{
//												Temp32.B08[0] = MAXSIDUANTB;
//											}
				
											Temp32.B08[1] = Bcd_To_Hex(Feik.Num[2]);	//设定的"日时段数"
											if( Temp32.B08[1] > MAXSIDUAN )
											{
												Temp32.B08[1] = MAXSIDUAN;
											}
				
											if( DI07.B08[0] <= MAXSIDUANTB )	//读取的日时段表号不能超过设定的"日时段表数"
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

						case 0x07:	//当前套阶梯时区表，备用套阶梯时区表
//							if( !BDMODE ) break; //远程模式
								
							if( (DI07.B08[1]!=0x00) || (DI07.B08[0]>0x01) ) break; //阶梯时区表不能超过2个

							I2C_Read_Eeprom( ee_jtshiqu1_page+DI07.B08[0], ee_jtshiqu_inpage, OutBuf+1, ee_jtshiqu_len );
							
							k = 12+1;
							break;
							
						case 0x03:	//第n 公共假日日期及日时段表号
//							ReadE2WithBackup( ee_feik_number_page, ee_feiknumber_inpage, Buf, ee_feiknumber_lenth );

							switch( DI07.B08[1] ) 
							{
								case 0x00:
//									Temp32.B08[0] = Bcd_To_Hex(Buf[4]);	//设定的"日时段数"
//									if( Temp32.B08[0] > 14 )	//公共假日：1~14, YYMMDDNN, 4
//									{
//										Temp32.B08[0] = 14;
//									}
//		
//									if( (DI07.B08[0]) && (DI07.B08[0] <= Temp32.B08[0]) )	//读取的公共假日不能超过设定的"公共假日数"
									if( (DI07.B08[0]) && (DI07.B08[0] <= MAXHOLIDAY) )		//读取的公共假日不能超过设定的"公共假日数"
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
								case 0x01:	//自动循显
								case 0x02:	//按键循显
									//循显屏数(1)＋循显时间(1)＋电能小数位数(1)＋功率位数(1)＋键显屏数(1)＋波特率(1)+ 跳闸延时时间(2)＋crc(2)
									if( (DI07.B08[0]) && (DI07.B08[0]<=SCREENNUM) )
									{
										n = (DI07.B08[1]-1)%2;
										i = (DI07.B08[0]-1)/31;
										if( i != 3 ) Temp08 = ee_displayitem_lenth;
										else Temp08 = ee_displayitem_lenth1;
										
										I2C_Read_Eeprom( ee_loop_displayitem_page+2*i+n, 0x00, Buf, Temp08 );
										Temp16.B08[0] = Buf[((DI07.B08[0]-1)%31)*2+0];
										Temp16.B08[1] = Buf[((DI07.B08[0]-1)%31)*2+1];
										
										//组合,正向,反向,组合无功1/2,第一象限无功电量~第四象限无功电量
										if( (Temp16.B16 <= 0x200+max_disploop*9) && (Temp16.B16 > 0x200) )
										{
											Temp16.B16 -= 0x200;
																							
											k = 6;
											OutBuf[3] = (Temp16.B16-1)/max_disploop;
											OutBuf[1] = (Temp16.B16-1-max_disploop*OutBuf[3])/(max_feilvcount+1);//0:当前; 1~12结算
											OutBuf[2] = (Temp16.B16-1)%(max_feilvcount+1);
											OutBuf[4] = 0x00;
											OutBuf[5] = 0x00;
										}
										else if( (Temp16.B16 <= 0x800+max_disploop*9) && (Temp16.B16 > 0x800) )
										{
											Temp16.B16 -= 0x800;
																							
											k = 6;
											OutBuf[3] = (Temp16.B16-1)/max_disploop;
											OutBuf[1] = (Temp16.B16-1-max_disploop*OutBuf[3])/(max_feilvcount+1);//0:当前; 1~12结算
											OutBuf[2] = (Temp16.B16-1)%(max_feilvcount+1);
											OutBuf[3]+= 0x70;	//高精度	
											OutBuf[4] = 0x00;
											OutBuf[5] = 0x00;
											
											if( OutBuf[3] == 0x70 )  OutBuf[3] = 0x68;//高精度显示修正
											else OutBuf[3] -= 0x11;
										}
										//------ 其他显示项目，序号从200开始--------
										else if( Temp16.B16 >= 200 )
										{
											result = Temp16.B16- 200;
											Temp08 = disp_num;	//disp_table表中总计显示项目数
											if( result < Temp08 )
											{
												Temp32.B32 = disp_table[result];
												for( n=0; n<=result; n++ )
												{
													if( Temp32.B32 != disp_table[result-n] ) break;
												}
												
												if( result == 0 )
													result = 0xff;		//全屏显示
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

						case 0x06:	//当前套第1张阶梯表~备用套第1张阶梯表
//							if( !BDMODE ) break; //远程模式
								
							//第一套第1~n 阶梯值		NNNNNN.NN	4	kWh
							if( ((DI07.B08[1] != 0x06)&&(DI07.B08[1] != 0x07)&&(DI07.B08[1] != 0x0a)&&(DI07.B08[1] != 0x0b)) || (DI07.B08[0]!=0xFF) ) break;

							k = 71;
							ReadE2WithJieti( DI07.B08[1]-0x06, OutBuf+1 );//读当前或者备用套阶梯电量/电价/年结算时间
							for( i=0; i<13; i++ ) Inverse( OutBuf+1+4*i, 4 );
//							for( i=0; i< 6; i++ ) Inverse( OutBuf+1+52+3*i, 3 );
							break;

						case 0x09:
							switch( DI07.B08[1] )
							{
								case 0x01:
									switch( DI07.B08[0] )
									{
										case 0x01:	//失压事件电压触发上限 NNN.N	2	V
										case 0x02:	//失压事件电压恢复下限 NNN.N	2	V	
											k = 3;
											Exchange( OutBuf+1, VolLimit.Lost_V_Min.B08+(DI07.B08[0]-1)*2, 2 );					
											break;
											
										case 0x03:	//失压事件电流触发下限	NN.NNNN	3	A
											k = 4;
											Exchange( OutBuf+1, VolLimit.Lost_V_I.B08+1, 3 );	
											break;	
											
										case 0x04:	//失压事件延时判定时间	NN	1	S
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
										case 0x01:	//过流事件电流触发下限	NNN.N	2	A
											k = 3;
											OutBuf[1] = Week_Holiday.Max_I.B08[1];
											OutBuf[2] = Week_Holiday.Max_I.B08[0];						
											break;
											
										case 0x02:	//过流事件判定延时时间	NN	1	S
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
										case 0x01:	//合格率电压考核上限值	NNN.N	2	V
										case 0x02:	//合格率电压考核下限值	NNN.N	2	V
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
										case 0x01:	//低电压事件电压触发上限 NNN.N	2	V
											k = 3;
											Exchange( OutBuf+1, VolLimit.Lower_V.B08, 2 );					
											break;
										
										case 0x02:	//低电压事件延时判定时间	NNNN	2	MIN
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
										case 0x01:	//高电压事件电压触发上限 NNN.N	2	V
											k = 3;
											Exchange( OutBuf+1, VolLimit.High_V.B08, 2 );					
											break;
										
										case 0x02:	//高电压事件延时判定时间	NNNN	2	MIN
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
										case 0x01:	//零线电流不平电流触发下限	NN.NNNN	3	A
											k = 4;
											Exchange( OutBuf+1, Week_Holiday.NLine_I.B08+1, 3 );
											break;
										
										case 0x02:	//零线电流不平衡限值      long-unsigned（单位：%，换算：-2）
											k = 3;
											Exchange( OutBuf+1, Week_Holiday.NLine_Limit.B08, 2 );	
											break;
											
										case 0x03:	//零线电流不平延时判定时间        NN	1	S
											k = 2;
											OutBuf[1] = Week_Holiday.NLine_Period;
											break;
									}		
									break;	
									
								case 0x40:
									switch( DI07.B08[0] )
									{	
										case 0x01:	//计量故障判定延时	NN	1	S
											k = 2;
											OutBuf[1] = VolLimit.Cal_Err_Period;	
											break;	
									}		
									break;
									
								case 0x43:
									switch( DI07.B08[0] )
									{	
										case 0x01:	//停电事件判断延时	NN	1	S
											k = 2;
											OutBuf[1] = Mode.Powerd_Period;
											break;	
									}		
									break;	
									
								case 0x51:
									switch( DI07.B08[0] )
									{	
										case 0x01:	//主动上报上电时限	NN	1	MIN
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
										case 0x01:	//厂家软件版本号(ASCII 码)	NN…NN	32
										case 0x02:	//厂家硬件版本号(ASCII 码)	NN…NN	32
										case 0x03:	//厂家编号(ASCII 码)		NN…NN	32
										case 0x04:	//软件备案号			NN…NN	8	
											Temp08 = 32;//32字节
											if(DI07.B08[0] == 0x01)
											{
												Temp16.B08[0] = ee_softver_page;	//软件版本号
												Temp16.B08[1] = ee_softver_inpage;
												Code_Flash_Char = (uint08*)SoftwareVer1;
											}
											else if(DI07.B08[0] == 0x02)
											{
												Temp16.B08[0] = ee_hardver_page;	//硬件版本号
												Temp16.B08[1] = ee_hardver_inpage;
												Code_Flash_Char = (uint08*)HardwareVer1;
											}
											else if(DI07.B08[0] == 0x03)
											{
												Temp16.B08[0] = ee_factorynum_page;	//厂家编号
												Temp16.B08[1] = ee_factorynum_inpage;
												Code_Flash_Char = (uint08*)FactoryNum;
											}
											else
											{
												Temp16.B08[0] = ee_softbk_page; 	//软件备案号
												Temp16.B08[1] = ee_softbk_inpage;
												Code_Flash_Char = (uint08*)Softbk;
												Temp08 = 8;//8字节
											}
											result = I2C_Read_Eeprom( Temp16.B08[0], Temp16.B08[1], OutBuf+1, Temp08 );
																						
											for( i=0; i<Temp08; i++ )	//如果全部为0xff则采用默认的值
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
										case 0x10://正泰内部版本号										
											memcpy( OutBuf+1, &C_ucSoftVerForFactory[0], 8 );//返回版本信息									
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
				
				case 0x05:	//冻结数据
//					if( DI07.B08[2] > 7 ) break;
						
					k = ReadFreezedRec( DI07.B08[2], DI07.B08[1], DI07.B08[0], OutBuf );
					if( k == 0x00 ) break;
					
					k += 1;
					OutBuf[0] = 0x00;	//结果
					break;
					
				case 0x0E:	//蓝牙内部协议0x0E8000xx
					if( (DI07.B08[2] != 0x80) || (DI07.B08[1] != 0x00) ) break;
						
					switch( DI07.B08[0] )
					{
						case 0x01:	//获取配置参数
							memset(OutBuf+1, 0, 25);
							Bcd2Hex_LS(Comm_Addr.Comm_Id, OutBuf+1, 6);
							OutBuf[6]  = 0xC0;
							
							I2C_Read_Eeprom(ee_bleslamac_page, ee_bleslamac_inpage, OutBuf+7, ee_bleslamac_lenth);//从机MAC地址
							I2C_Read_Eeprom(ee_blerefer_page, ee_blerefer_inpage, OutBuf+25, 1);//Tx_Power
							
							k = 25+1;
							break;
							
						case 0x02:	//蓝牙上报连接状态（不需应答）
							for(i=0; i<5; i++)
							{
								if( (Ble_Connect[i].Ble_A2==Uart[Ch].Buf[14]) && (Ble_Connect[i].Ble_A3==Uart[Ch].Buf[15]) &&
										(Cmp_Bcd_Inv(Ble_Connect[i].Ble_Mac, Uart[Ch].Buf+17, 6) == 0) )	//列表已有设备
								{
									if( Uart[Ch].Buf[16] == 0 )	//断开连接
									{
										memset(&Ble_Connect[i].Ble_A2, 0, 9);	//清相关信息
										memcpy(&Ble_Connect[i].Ble_A2, &Ble_Connect[i+1].Ble_A2, (4-i)*9);
										memset(&Ble_Connect[4].Ble_A2, 0, 9);	//清相关信息
									}
									break;
								}
								else if( Ble_Connect[i].Ble_A2 == 0 )
								{
									memcpy(&Ble_Connect[i].Ble_A2, Uart[Ch].Buf+14, 9);	//保存设备连接状态
									break;
								}
							}

//							Temp08 = 0xff;
//							for(i=0; i<5; i++)
//							{
//								if( Cmp_Bcd_Inv(Ble_Connect[i].Ble_Mac, Uart[Ch].Buf+17, 6) == 0 )	//列表已有该设备
//								{
//									Temp08 = 0xee;
//									if( Uart[Ch].Buf[16] == 0 )
//										memset(&Ble_Connect[i].Ble_A2, 0, 9);	//已断开，清相关信息
//									else 
//										memcpy(&Ble_Connect[i].Ble_A2, Uart[Ch].Buf+14, 9);	//已连接，更新设备连接信息
//									break;
//								}
//								else if( (Ble_Connect[i].Ble_A2 == 0) && Uart[Ch].Buf[16] )
//								{
//									if( Temp08  == 0xff ) Temp08 = i;
//								}
//							}
//							if( Temp08 < 5 )
//								memcpy(&Ble_Connect[Temp08].Ble_A2, Uart[Ch].Buf+14, 9);	//已连接新设备，保存设备连接信息
							
							Uart[Ch].Overtime_Timer = 2;
							return;
							
						case 0x09:	//进入/退出蓝牙检定校表
							k = 1;
							break;
							
						default:
							break;	
						
					}
					
					break;
			
				default: break;
			}

			if( (Uart[Ch].Buf[9] != 0x04) && !ble_inter_flag ) //多数据项组合抄读(EEEEEENN)
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
					Uart[Ch].FrmBuf[ Len++ ] = k+2; //长度
				else
					Uart[Ch].FrmBuf[ Len++ ] = k+3; //长度
				memcpy( Uart[Ch].FrmBuf+Len, DI08.B08, 4 ); //恢复
				Len += 4;
			}
			else
			{
				if( (k == 2) && (OutBuf[0] == 0xFF) ) break;
			}
			
			if( k == 0x00 )
			{
				OutBuf[ k++ ] = 0xFF;
				OutBuf[ k++ ] = 0x02;	//错误信息字ERR：无请求数据
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
			OutBuf[0] = 0x00;	//结果
		}
		break;
				
		case 0x12:	//读取后续帧
			if( Uart[Ch].Flag&B0000_0001 ) break; //通讯地址全99   不支持
			if( Uart[Ch].Buf[9] != 0x05 ) break;	//Len error
			
			switch( DI07.B08[3] )
			{
				case 0x06:	//负荷记录
					if( (((DI07.B08[2] == 0x10) || (DI07.B08[2] == 0x11)) && (DI07.B08[1] && (DI07.B08[1] <= 0x08)))
					||  (( DI07.B08[2] == 0x10) && ((DI07.B08[1] == 0x0C) || (DI07.B08[1] == 0x0D))) )
					{
						k = ReadLoadRec( Ch, Uart[Ch].Buf+8, OutBuf );
						if( k == 0 ) RdLoadPara[Ch][4] = 0;
						else if(RdLoadPara[Ch][4]) Remain = 1;
					}
					break;
					
				default:
					if( Uart[Ch].FrmLen == 0 ) break; //无后续帧
					if( Cmp_Data(DI07.B08, Uart[Ch].DI, 4) != 3 ) break; //数据标识不符，退出
					if( Uart[Ch].Buf[14] != Uart[Ch].Sn ) break; //帧序号不符，退出
					
					if( Uart[Ch].FrmLen <= 195 )
						OutBuf[0] = Uart[Ch].FrmLen;
					else
						OutBuf[0] = 195;
					Uart[Ch].FrmLen -= OutBuf[0];

					memcpy( OutBuf+1, Uart[Ch].FrmBuf+Uart[Ch].FrmOffset, OutBuf[0] ); //填充返回数据

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
					
					OutBuf[++OutBuf[0]] = Uart[Ch].Buf[14]; //帧序号
					
					k = OutBuf[0]+1;
					OutBuf[0] = 0x00;
					break;
			}
			
			if( (k ==0) && ((Mode.Feature1&0x04)==0x04) && ChkBufZero( Report_Data, 5 ) )
			{
				Int2Byte( 0x01150004, DI07.B08 );
				
				//主动上报状态字	NNNNNNNNNNNNNNNNNNNNNNNN	12+N
				k = Ready_Reportdata( OutBuf );
				Reset_Rep_Timer = Calculate_Timer(3);		//启动复位上报状态字定时器
				OutBuf[k++] = Uart[Ch].Buf[14];//返回帧序号
				memcpy( Uart[Ch].Buf+10, DI07.B08, 4 );//返回新的标识
			}
			
			if( k == 0x00 )
			{
				OutBuf[ k++ ] = 0xFF;
				OutBuf[ k++ ] = 0x02;	//错误信息字ERR：无请求数据
			}
			break;

		case 0x13:	//读通信地址, 地址域必须是全AAH
			//……不做编程记录……
			memset( Buf, 0xaa, 6 );
			if( (Cmp_Data( Buf, Uart[Ch].Buf+1, 6 ) !=3)	//非全aa	
				|| (Uart[Ch].Buf[9] != 0x00) )
			{
				Uart[Ch].Overtime_Timer = 2;
				return;
			}

			k = 7;
			Exchange( OutBuf+1, Comm_Addr.Comm_Id, 6 );
			break;

		case 0x15:	//写通信地址, 地址域必须是全AAH
			//……不做编程记录……
			if( ((Uart[Ch].Flag&B0000_0010) != B0000_0010)	//地址域必须是全AAH
				|| (!progenable) 							//编程按键无效,24hour编程禁止有效
				|| (Uart[Ch].Buf[9] != 0x06) )				//数据长度不合法
			{
				Uart[Ch].Overtime_Timer = 2;
				return;
			}
			
			Exchange( Buf, Uart[Ch].Buf+10, 6 );

			result = WriteE2WithBackup( ee_commaddr_page, ee_commaddr_inpage, Buf, ee_commaddr_lenth );	//写入E2PROM
			if( result )
			{
				Uart[Ch].Overtime_Timer = 2;
				return;
			}

			if( Cmp_Data(Comm_Addr.Comm_Id, Buf, 6) != 3 ) Ble_Rst_Judge(Ch);
				
			memcpy( Comm_Addr.Comm_Id, Buf, 8 );

			k = 1;
			break;

		case 0x08:	//广播校时
			//……不做编程记录……
			if( ((Uart[Ch].Flag&B0000_0010) == B0000_0010) || (Uart[Ch].Buf[9] != 0x06) || ((Ch==CHBLE) && (Uart[Ch].Flag&B0000_0011)) ) //不支持索位
			{
				Uart[Ch].Overtime_Timer = 2;
				return;
			}

			result = JudgeClockNoWeek( 0, &Uart[Ch].Buf[10], 6 );
			if( result != 0 ) //
			{
				break; //错误
			}
			
			if( already_setclock_flag == 1 ) break; //今日已校时, 不允许再校时

			if( !clock_error )	//系统时钟正确
			{
				//----- 不允许在00:00:00的±5min内广播校时------
				Buf[0] = 0x00;
				Buf[1] = 0x10;
				Buf[2] = 0x00;
				Temp08 = Cmp_Bcd_Inv( Buf, Sclock.Clockbackup, 3 );
				if( Temp08 == 1 ) break;	//当前时间小于00:05:00
	
				Buf[0] = 0x00;
				Buf[1] = 0x50;
				Buf[2] = 0x23;
				Temp08 = Cmp_Bcd_Inv( Buf, Sclock.Clockbackup, 3 );
				if( Temp08 == 2 ) break;	//当前时间大于23:55:00
				
				//----- 不允许广播校时超±5min分钟------
				result = Judge_Min_Space( Uart[Ch].Buf+10 );
				if( result  == 1 )//不允许广播校时超±10min
				{
					if( G_Clockerr_Times == 0 )
					{
						if( ChkLastclockerrRcdTime() != 1 ) Note_Run_Event(ee_clockerrn_inpage); //时钟故障开始记录(时钟非法)
						G_Clockerr_Times = 1;	//置明文广播校时故障标志
					}
						
					k = 2; 
					OutBuf[0] = 0xFF;
					OutBuf[1] = 0x04;	//Error: bit2密码错误/未授权
					break;
				}
				
				//------ 不允许在结算日的±5min内广播校时 -------
				ReadE2WithBackup( ee_histroyparameter_page, ee_histroyparameter_inpage, Buf, ee_histroyparameter_lenth );	//结算日时间: 日时
				for( i=0; i<9; i++ )
				{
					Buf[6] = 0x00; //结算时间
					Buf[7] = 0x00;
					if( i < 3 )
					{
						memcpy( Buf+8, Buf+2*i, 2 ); //Hour+Day
						Buf[10] = Sclock.Clockbackup[4];
					}
					else
					{
//						if( !BDMODE ) continue; //远程模式
						memcpy( Buf+8, Price.Year_Ladder+3*(i-3), 3 );//Hour+Day+Month
					}
					Buf[11] = Sclock.Clockbackup[5];
					
					result = Judge_Min_Space( Buf+6 );
					if( result == 0 ) break;	//不允许在结算日的±5min内广播校时
				}

				if( result == 0 ) break;
			}

			memcpy( Buf+0, Uart[Ch].Buf+10, 3 );

			if( clock_error ) { Buf[3] = 0x00; }
			else { Buf[3] = Sclock.Clockbackup[6]; }

			memcpy( Buf+4, Uart[Ch].Buf+13, 3 );
			
			Buf[3] = (CalcAbsDay(Buf+2)+6)%7;	//计算周,格式为秒+分+时+周+日+月+年,起始地址周,从日开始计算

			result = Set_Rtc( 0, Buf, 7 );
			if( result != 0x00 ) break; //设置时钟失败

			already_setclock_flag = 1; //
			
			memcpy( Uart[Ch].Buf+10+6, Sclock.Clockbackup, 6 );	//校时前时间(6)(临时保存)
			
			CommSetRtc_Adj();	//设置时钟调整相关数据
			
			memcpy( Eeprom.Buffer, Uart[Ch].Buf+10+6, 6 );		//校时前时间(6)
			memcpy( Eeprom.Buffer+6, Sclock.Clockbackup, 6 );	//校时后时间(6)
			DltoEepromBuf( 12 );					//读正向电量+反向电量(8)
			Four_RpdltoEepromBuf( 12+8 );				//读四象限无功(16)
			Event_Record( ee_gbsclockn_inpage );			//做广播校时记录

			k = 1;
			break;

		case 0x16:	//冻结命令
			//68+表号+68+16+04+mmhhDDMM+CS+16
			if( Uart[Ch].Buf[9] != 0x04 )	//数据域长度错误
			{
				Uart[Ch].Overtime_Timer = 2;
				return;
			}

			Temp08 = 0x00; //冻结时间中99H的个数
			for( n=0; n<4; n++ )
			{
				if( Uart[Ch].Buf[10+n] == 0x99 )
				{
					Temp08++;
				}
				else
				{
					if( Temp08 || JudgeClockNoWeek(1+n, &Uart[Ch].Buf[10+n], 1) ) //前一字节为99H或本字节有误, 则冻结时间错误
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
				case 0x00:	//mmhhDDMM, 普通冻结
				case 0x01:	//99DDhhmm表示以月为周期定时冻结
					if( Uart[Ch].Buf[12] > 0x28 )  break;		//只能是1~28日冻结
				case 0x02:	//9999hhmm表示以日为周期定时冻结
				case 0x03:	//999999mm表示以小时为周期定时冻结
					//整点冻结起始时间(5)＋整点冻结时间间隔(1)＋日冻结时间(2)+ 定时冻结时间(4)+ crc（2）
					I2C_Read_Eeprom44( ee_freezeparameter_page, Buf, ee_freezeparameter_lenth );

					Exchange( Buf+8, Uart[Ch].Buf+10, 4 );

					result = I2C_Write_Eeprom44( ee_freezeparameter_page, Buf, ee_freezeparameter_lenth );
					if( result != 0x00 ) break;

					k = 1;
					break;
					
				case 0x04:	//99999999为瞬时冻结
					//瞬时冻结时间(5)+瞬时冻结正向有功电能数据(5*4)+瞬时冻结反向有功电能数据(5*4)+瞬时冻结变量数据(3)
					Freeze_Dl( ee_realtimefreeze1_page, ee_immedf_inpage );

					k = 1;
					break;
					
				default:
					break;
			}
			break;
			
		case 0x17:	//更改通信速率, 波特率
			//……不做编程记录……

			//Bit7   Bit6     Bit5    Bit4    Bit3    Bit2    Bit1   Bit0
			//38400bps 19200bps 9600bps 4800bps 2400bps 1200bps 600bps 保留
			
			if( Uart[Ch].Flag&B0000_0011 )
			{
				k = 2; 
				OutBuf[0] = 0xFF;
				OutBuf[1] = 0x04;	//Error: bit2密码错误/未授权
				break;
			}
			
			if( Uart[Ch].Buf[9] != 0x01 ) //数据域长度不为1, 错误
			{
				Uart[Ch].Overtime_Timer = 2;
				return;
			}
			
			//0x01:调制型红外光口波特率特征字//0x03/0x04/0x05:通信口1/2/3 波特率特征字
			Temp08 = Ch*2+1;
			if( Ch == CHBLE) Temp08 = 4; 
			Temp08 = Set_Comm_Rate( Temp08, Uart[Ch].Buf[10] );
			if( Temp08 )
			{
				k = 2;
				OutBuf[0] = 0xFF;
				OutBuf[1] = 0x08;	//错误信息字ERR：通信速率不能更改(Bit3)
			}
			else
			{
				k = 2;
				OutBuf[1] = Uart[Ch].Buf[10];	//更改后波特率
			}
			break;

		case 0x19:	//最大需量清零
			k = 2;
			OutBuf[0] = 0xFF;	//Operation result.
			OutBuf[1] = 0x04; //Error: bit2密码错误/未授权
			break;
			
		case 0x1A:	//电表清零, 清空电能表内电能量、冻结量、事件记录、等数据, 电表清零必须记录清零时刻和清零前的电能量
		case 0x1B:	//事件清零, 清空电能表内存储的全部事件记录数据
			//本命令必须与编程键配合使用。命令执行时电能表应保证电表清零事件记录不被清除，并自动保存该事件的相应数据
			//……不做编程记录……
			if( !(Uart[Ch].Flag & B0000_0011) && progenable && (Uart[Ch].Buf[10] == 0x03) )//厂内模式允许直接清零
			{
				Ic_Comm_RxBuf[0] = Uart[Ch].Buf[8];
				Exchange( Ic_Comm_RxBuf+8, Uart[Ch].Buf+18, 4 );	//事件清零标识
			}
			else
			{
				if( (Uart[Ch].Flag & B0000_0011) || (Uart[Ch].Buf[10] != KEYTYPE2) || (identity_prog_flag == 0) || hangup_comm_flag )	//安全认证编程标志 失效
				{
					k = 2;
					OutBuf[0] = 0xFF; //结果
					OutBuf[1] = 0x04; //Error: bit2密码错误/未授权
					break;	//国网电能表只支持98级远程控制
				}
				
				if( (Key_Status == 1) && (Uart[Ch].Buf[8] == 0x1A) ) //电能表清零操作只可以在测试密钥状态下执行
				{
					k = 2;
					OutBuf[0] = 0xFF; //结果
					OutBuf[1] = 0x04; //Error: bit2密码错误/未授权
					break;	//国网电能表只支持98级远程控制
				}
				
				if( Uart[Ch].Buf[8] == 0x1A ) //电表清零
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
			OutBuf[0] = 0xFF; //结果
			OutBuf[1] = 0x04; //Error: bit2密码错误/未授权
			
			//验证通过后按照明文定义的指令执行相应操作
			if( Ic_Comm_RxBuf[0] == 0x1A )
			{
				MeterClear = 0x55aa;	//电表清零
			}
			if( Ic_Comm_RxBuf[0] == 0x1B )
			{
				Inverse( Ic_Comm_RxBuf+8, 4 );	//事件清零标识调序
				memcpy( DI07.B08, Ic_Comm_RxBuf+8, 4 );	//事件清零标识

				if( DI07.B08[0] != 0xFF ) break;
				if( ((DI07.B08[3]&0x7f) == 0x03) && ((DI07.B08[2] == 0x70) || (DI07.B08[2] == 0x10)) && (DI07.B08[1] == 0x01) ) DI07.B08[1] = 0x00;//支持事件清A相电压合格率
//				if( ((DI07.B08[3]&0x7f) == 0x03) && ((DI07.B08[2] == 0x70) || (DI07.B08[2] == 0x10)) && (DI07.B08[1] <= 0x01) )break;//不支持事件清电压合格率
//				if( ((DI07.B08[3]&0x7f) == 0x03) && ((DI07.B08[1] == 0x02) || (DI07.B08[1] == 0x03)) && (DI07.B08[2] == 0xc0) )break;//不支持事件清停电统计
				
				if( Byte2uInt(DI07.B08) == 0xFFFFFFFF ) ClrRecTimes( 0, 0x55 );//清冻结和事件有效指针(除电量相关)
				else
				{
					DI07.B08[3] &= ~0x80;	//支持高精度标识清零
					if( (DI07.B08[3] == 0x10) || (DI07.B08[3] == 0x19) ||(DI07.B08[3] == 0x1D)||(DI07.B08[3] == 0x1E)||(DI07.B08[3] == 0x22)||
					   ((DI07.B08[3] == 0x03)&&((DI07.B08[2] == 0x11)||(DI07.B08[2] == 0x33))))	//拉合闸特殊处理
					{
						if( DI07.B08[3] == 0x22 )
						{
							if( DI07.B08[1] != 0x00 ) break;
						}
						else
						{
							if( DI07.B08[1] != 0xFF ) break;
						}
						
						i = Find_EventTable(DI07.B08+2);		//判断是否找到合法数据标识
					}
					else if( DI07.B08[3] == 0x03 )
					{
						i = Find_EventTable(DI07.B08+1);		//判断是否找到合法数据标识
					}
					else break;

					if( i != EventNum )
					{				
						i += ee_clearn_inpage;
						if( i < ee_powerdownn_inpage ) break; 
						if( i == ee_poweroffn_inpage || i==ee_poweronn_inpage ) i = ee_powerdownn_inpage; //掉电上报事件和上电上报事件与掉电事件同源
						
						ClrRecTimes( i, 0x01 );
					}
					else
					{
						break;
					}
				}
					
				//事件清零记录
				//存储各项数据时倒序，低字节在前，高字节在后
				memcpy( Eeprom.Buffer+6, Uart[Ch].Buf+14, 4 );	//操作者代码(4)
				memcpy( Eeprom.Buffer+10, Ic_Comm_RxBuf+8, 4 ); 	//事件清零数据标识码(4)
				Event_Record( ee_cleareventn_inpage );
			}
			k = 1;
			OutBuf[0] = 0x00;
			break;

		case 0x1C:	//跳合闸、报警、保电	
			if( Uart[Ch].Buf[10] != KEYTYPE2 )	//判断是否为96级密码
			{
				if( (Uart[Ch].Flag & B0000_0011) || (Uart[Ch].Buf[9] != 16) || (Uart[Ch].Buf[10] != 0x03) ||
				    (!progenable && (((Uart[Ch].Buf[18] != 0x1b) && (Uart[Ch].Buf[18] != 0x1c)) || Veri_Psw( Uart[Ch].Buf+10 ))) )//厂内模式允许直接拉合闸或者明文合闸允许/直接合闸
				{
					k = 2;
					OutBuf[0] = 0xFF; //结果
					OutBuf[1] = 0x04; //Error: bit2密码错误/未授权
					break;
				}
				else
				{
					memcpy( Ic_Comm_RxBuf,  Uart[Ch].Buf+18, 8 );//复制2字节数据和6字节有效截止时间
					result = JudgeEndClock();
					if(result)
					{
						k = 2;
						OutBuf[0] = 0xFF; //结果
						OutBuf[1] = 0x04; //Error: bit2密码错误/未授权
						break;
					}
					Temp08 = Ch;
				}
			}
			else
			{
				if( (Uart[Ch].Flag & B0000_0011) || (Ch == CHHW) || ((Ch == CHBLE) && (progenable==0)&&(IR_EnTimer == 0)) || (identity_prog_flag == 0) || hangup_comm_flag )	//安全认证编程标志 失效
				{
					k = 2;
					OutBuf[0] = 0xFF; //结果
					OutBuf[1] = 0x04; //Error: bit2密码错误/未授权
					break;	//国网电能表只支持98级远程控制
				}
                        	
				//P0～P2无效, 无效验证
				//将N1~Nm写入ESAM的控制命令文件进行解密, 解密成功，以解密后对应的明文所定义的命令执行相应的控制操作。
				//远程控制命令：80fb060010+密文；
				//获取远程控制命令的明文：00C00000＋LC（要获取的明文数据长度，为1 字节的十六进制数）；
				//68+表号+68+1C+1C+98000000+00000000+密文+cs+16
				//将密文写入ESAM 08文件解密: 04D6880014+密文
				//N1为控制命令类型，1AH代表跳闸，1BH代表合闸允许，2AH代表报警，2BH代表报警解除，3AH代表保电，3BH代表保电解除。
				//N2保留。
				//N3～N8代表命令有效截止时间，数据格式为ssmmhhDDMMYY。当电表当前时间已经超过这个时间时，该命令将被认为无效，不被执行
				
				Temp08 = Ch+0x20;
			}
			
			//验证通过后按照明文定义的指令执行相应操作
			result = Relay_Ctrl(Temp08);
			if(result)
			{
				k = 2;
				OutBuf[0] = 0xFF; //结果
				OutBuf[1] = 0x04; //Error: bit2密码错误/未授权
			}
			else k = 1;
			
			break;
			
		case 0x1D:	//多功能端子输出控制命令, 无需编程键配合和密码验证, 电能表在使用过程中，发生掉电再上电情况时，不管端子当前输出何种信号均恢复至秒信号输出。
			if( Uart[Ch].Buf[9] != 0x01 )	//数据域长度错误
			{
				Uart[Ch].Overtime_Timer = 2;
				return;
			}
			
			switch( Uart[Ch].Buf[10] )
			{
				case 0x00:	//时钟秒脉冲
				case 0x02:	//时段投切
				case 0x03:	//无功脉冲
				case 0x06:	//有功脉冲
					Outputtype = Uart[Ch].Buf[10];
					reg_veri_flag = 1;
					k = 2;
					OutBuf[1] = Uart[Ch].Buf[10];
					break;
					
				default:
					break;
			}
			break;
			
		//--------------------- 扩展命令区 -------------------------------
		#if(0 == CHINT_Mode)
		case 0x1E://扩展命令			
			if( Uart[Ch].Buf[ 10 ] == 5 )//扩展读长数据ee
			{
				Temp16.B08[0] = Uart[Ch].Buf[ 11 ];		//Di1
				Temp16.B08[1] = Uart[Ch].Buf[ 12 ];		//Di2
				
				Temp08 = 68;
				if( (Uart[Ch].Buf[ 9 ] == 5) && progenable )	//仅厂内支持该命令（读非法地址电表可能会复位）
				{					
					Temp32.B08[0] = Uart[Ch].Buf[ 11 ];		//Di1
					Temp32.B08[1] = Uart[Ch].Buf[ 12 ];		//Di2
					Temp32.B08[2] = Uart[Ch].Buf[ 13 ];
					Temp32.B08[3] = Uart[Ch].Buf[ 14 ];
					
					if( Uart[Ch].Buf[ 14 ] == 0x00 )//表示扩展读flash(0x00000000~0x00080000)
					{
						if(Temp32.B32 + 64>PROGRAMEND1)
						{
							break;
						}
					}
					else if( Uart[Ch].Buf[ 14 ] == 0x20 )	//表示扩展读ram(0x20000000~0x20010000)
					{
						if((Temp32.B32 + 64)>(int)&__heap_limit)
						{
							break;
						}	
					}
					else if( (Uart[Ch].Buf[ 14 ] == 0x40 ) && (Uart[Ch].Buf[ 13] == 0x00 ) )//表示扩展读寄存器AHB(0x40000000~0x40008000)
					{
						if( (Temp32.B32 + 64)>0x40008000 )
						{
							break;
						}
					}
					else if( (Uart[Ch].Buf[ 14 ] == 0x40 ) && (Uart[Ch].Buf[ 13] == 0x01 ) )//表示扩展读寄存器APB(0x40010000~0x40018000)
					{
						if( (Temp32.B32 + 64)>0x40018000 )
						{
							break;
						}
					}
					else if( Uart[Ch].Buf[ 14 ] == 0xe0 )	//表示扩展读ppb(0xe0000000~0xe0100000)
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
				else if( Uart[Ch].Buf[ 13 ] == 0x81 ) //表示扩展读取外部FLASH
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
					memcpy( Uart[Ch].Buf+14+8, Verdate, 24 );//返回版本信息
					Uart[Ch].Buf[14+32] = 0xaa;
					Uart[Ch].Buf[14+33] = clkmode;		//1分频为8M主时钟,2分频为4M主时钟
					Uart[Ch].Buf[14+34] = *(uint08*)0x1FFFFC0E;//0x04 代表404
					Uart[Ch].Buf[14+35] = Correction_Mode;	//0x55-开启电压补偿功能,其他-关闭(目前仅rn8209c支持)
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
					
					if((Temp16.B16==0x0022)||(Temp16.B16==0x0023))	//兼容目前的校表软件
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
				Uart[Ch].Flag |= B0000_1000;//规约处理结束准备发送数据标志
				return;
			}
			break;		
		#endif
			
		#if(1 == CHINT_Mode)		
		case 0x1E://扩展命令			
			if((Uart[Ch].Buf[10] == 0xff) && (Uart[Ch].Buf[11] == 0xff) && (Uart[Ch].Buf[12] == 0xff) && (Uart[Ch].Buf[13] == 0xff))
			{
				if((Uart[Ch].Buf[ 9 ] == 0x09) && (Uart[Ch].Buf[ 14 ] == 0x1A))			//写I_J短接时间
				{					
					for( i=0; i<4; i++ ) //数据标识
					{
						Temp32.B08[i] = Uart[Ch].Buf[ 18-i ];
					}					
					if(COVKEY_N)///*合盖状态不允许设置软I_J有效时间*///
					{
						if(Byte2uInt(Temp32.B08) != 0) break;
					}
					
					if( Key_Status == 1) break;	///*正泰CHINT 陈收 私钥不允许设置*///
						
					if(Byte2uInt(Temp32.B08) > 0xa8c0) break;	//不允许超过720小时
					
					memcpy( Ijtimer_Para.Ijtimer.B08,Temp32.B08, 4 );

					I2C_Write_Eeprom(ee_softij_page, ee_softij_inpage, Ijtimer_Para.Ijtimer.B08, 4);	
					
					k = 1;
					OutBuf[0] = 0x00;
					break;
				}
				else if((Uart[Ch].Buf[ 9 ] == 0x09) && (Uart[Ch].Buf[ 14 ] == 0x1B))			///*读软I_J时间*///
				{
					
					I2C_Read_Eeprom( ee_softij_page, ee_softij_inpage, Uart[Ch].Buf+15, 4);
					k = 10;
					OutBuf[0] = 0x00;
					memcpy(&OutBuf[1], &Uart[Ch].Buf[10], 5 );
					Exchange( &OutBuf[6], &Uart[Ch].Buf[15], 4 );
					break;
				}
				else if( (Uart[Ch].Buf[ 9 ] == 0x0a) && (Uart[Ch].Buf[ 19 ] <= 64) &&( Uart[Ch].Buf[14] < 0x03 ) )	//读取RAM和EE数据
				{
					memcpy(&OutBuf[1], &Uart[Ch].Buf[10], 4);
					
					Temp16.B08[1] = Uart[Ch].Buf[ 15 ];		//低字节
					Temp16.B08[0] = Uart[Ch].Buf[ 16 ];		//高字节
					Temp32.B08[3] = Uart[Ch].Buf[ 15 ];		//Di1
					Temp32.B08[2] = Uart[Ch].Buf[ 16 ];		//Di2
					Temp32.B08[1] = Uart[Ch].Buf[ 17 ];
					Temp32.B08[0] = Uart[Ch].Buf[ 18 ];
					
					/* 读RAM */
					if(Uart[Ch].Buf[14]==0x00)
					{																
//						memcpy(&OutBuf[5], (uint08 xdata *)(Byte2uInt(Temp32.B08)), Uart[Ch].Buf[ 19 ]);
						memcpy(&OutBuf[5], (uint08 *)(Byte2uInt(Temp32.B08)), Uart[Ch].Buf[ 19 ]);
				
						k = Uart[Ch].Buf[ 19 ] + 5;
						OutBuf[0] = 0x00;
					}
					/* 读E2 */
					else if(Uart[Ch].Buf[14]==0x01)
					{												
						if( Byte2uShort(Temp16.B08) < 0x0400 )/*最大地址*/
						{							
//							I2C_Read_Eeprom ( Temp16.B16, 0, &OutBuf[5], Uart[Ch].Buf[19]);
							I2C_Read_Bottom( Byte2uShort(Temp16.B08), 0, &OutBuf[5], Uart[Ch].Buf[19]);											
							k = Uart[Ch].Buf[ 19 ] + 5;
							OutBuf[0] = 0x00;							
						}
					}
					/*读ROM*/
					else if(Uart[Ch].Buf[14]==0x02)
					{	
						memcpy(&OutBuf[5], (unsigned char ecode *)Byte2uInt(Temp32.B08), Uart[Ch].Buf[19] );
						k = Uart[Ch].Buf[ 19 ] + 5;
						OutBuf[0] = 0x00;	
					}
						
				}
//				else if((Uart[Ch].Buf[ 9 ] == 0x09) && (Uart[Ch].Buf[ 14 ] == 0x3B))	///*正泰CHINT 陈收 写负荷开关内置或外置*///
//				{
//					
//					if(Byte2uInt(Ijtimer_Para.Ijtimer.B08) == 0)	///*软I_J有效才允许设置*///
//					{
//						k = 2;
//						OutBuf[0] = 0xFF; //结果
//						OutBuf[1] = 0x04; //Error: bit4密码错误/未授权
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
		#endif  ///*上接#if(1 == CHINT_Mode)*///

		case 0x1F://扩展命令	
			if( (Ch == CHZB) && (Uart[Ch].Buf[ 9 ] == 11) && (Byte2uInt(Uart[Ch].Buf+10) == 0x05070004 ) ) //载波波特率协商
			{	
				if( Uart[Ch].Flag&B0000_0011 )
				{
					k = 2; 
					OutBuf[0] = 0xFF;
					OutBuf[1] = 0x04;	//Error: bit2密码错误/未授权
					break;
				}
				
				Temp08 = Set_Comm_Rate( 0x85, Uart[Ch].Buf[20] ); //载波波特率协商
				if( Temp08 )
				{
					k = 2;
					OutBuf[0] = 0xFF;
					OutBuf[1] = 0x08;	//错误信息字ERR：通信速率不能更改(Bit3)
					break;
				}
							
				if( Cmp_Data( Esam_Para.Zb_Id, Uart[Ch].Buf+14, 6 ) != 3 )
				{
					memcpy( Buf, Esam_Para.Zb_Id, 6 );
					memset( Buf+6, 0xff, 6 );
					
					Inverse( Uart[Ch].Buf+14, 6 );	//保证写入数据ee低字节在前
					UpdateSysPara( 0x40+18, Uart[Ch].Buf+14, 6 ); //更新模块id
					
//					I2C_Write_Eeprom( ee_zbid_bk_page, ee_zbid_bk_inpage, Esam_Para.Zb_Id, ee_zbid_bk_lenth ); //写原载波id备份(通讯抄读专用)
										
					if( Cmp_Data( Buf, Buf+6, 6 ) != 3 ) //原电表通信ID非全ff
					{
						//按照文档需要记录模块更换记录
						Note_Run_Event(ee_commchangen_inpage);	//记录通信模块更换记录
						
						commmodule_open_flag = 0;
						Store_Meterstatus();
						
						Note_Run_Event(ee_commchangen_inpage|0x80);	//记录通信模块更换记录
					}
				}
				
				k = 1;
				break;
			}
			
			#if(0 == CHINT_Mode)
			if( (Ch == CHZB) && (Uart[Ch].Buf[ 10 ]!=0xAF) ) break;	//厂内命令不支持载波通道
			#endif
			
			
			switch( Uart[Ch].Buf[ 10 ] )
			{
				case 0x13:	//初始化指令
					if( (Ch == CHHW) || (Ch == CHBLE) || (!progenable) || ((Cover.Status == 0)&&((Fwdl.Pluse[0].B32>=10000*Meter.Const_H)||(Bkdl.Pluse[0].B32>=10000*Meter.Const_H))) )
					{
						k = 2;
						OutBuf[0] = 0xFF; //结果
						OutBuf[1] = 0x04; //Error: bit4密码错误/未授权
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
					
				case 0x0f:	//软件编程开关控制指令
					#if(1 == CHINT_Mode)	
					if(Byte2uInt(Ijtimer_Para.Ijtimer.B08) == 0)	//软I_J有效才允许设置
					{
						break;
					}
					#endif		
					
					if( Uart[Ch].Buf[9] != 0x03 ) break;//数据长度错误
					
					if( Uart[Ch].Buf[11] == 0xaa )
					{
						Progkey.Timer = 0;	//软件编程禁止
					}
					else if(  Uart[Ch].Buf[11] == 0x55 )
					{
						if( (Key_Status==1) && (esam_error==0) ) break;	//在有esam的情况下私钥不允许设置
						else	
							Progkey.Timer = Uart[Ch].Buf[12];	//软件编程使能
					}
					else if( Uart[Ch].Buf[11] == 0xee ) //读初始化命令执行状态
					{
						k = 9;
						I2C_Read_Eeprom( ee_factoryinit_page, ee_factoryinit_inpage, OutBuf+1, ee_factoryinit_len );
						Inverse( OutBuf+1, 2 );
						
						OutBuf[3] = 0x00; //返回器件密度
						if( FlashID_Comm( Buf ) ) OutBuf[3] = 0xff;	//读flash容量失败
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
						break;		//非法数据
					}
					
					k = 1;
					break;	
			
				case 0x03:
					//设置温度曲线的参数说明：
					//0 高温温度斜率微调 //1 低温温度斜率微调
					//2 高温晶体曲线微调（高温修调二次函数系数）x*0.0001
					//3 低温晶体曲线微调（低温修调二次函数系数）x*0.0001
					//4 常温顶点调校值修正值
					//9 常温25+晶体曲线微调（常温25+修调二次函数系数）x*0.0004 krh
					//10常温25-晶体曲线微调（常温25-修调二次函数系数）x*0.0004 krl
					//9 高温顶点调校值修正值(ppm)(新调校)
					//10低温顶点调校值修正值(ppm)(新调校)
					#if(1 == CHINT_Mode)
					if(Ijtimer_Para.Ijtimer.B32 == 0)	//软I_J有效才设置
					{
						k = 2;
						OutBuf[0] = 0xFF; //结果
						OutBuf[1] = 0x04; //Error: bit4密码错误/未授权
						break;
					}	
					#endif
					if( (Ch == CHHW) || (Ch == CHBLE) ) break;//禁止红外操作
					if( Uart[Ch].Buf[9] != 0x0a ) break;//数据长度错误
					if( (Wr_Ext_Number == 50)&&(!progenable) ) break;
					else if ( Wr_Ext_Number > 50 ) Wr_Ext_Number = 25;
					else Wr_Ext_Number++;
					
					Temperpara_Verify();	//温度系数校验
					memcpy( Buf, Tpara.Offset, ee_temperature_lenth );//复制温度系数
					
					if( Uart[Ch].Buf[19] == 0x00 )//全部更新
					{
						memcpy( Buf+2, Uart[Ch].Buf+16, 3 );
					}
					else if( Uart[Ch].Buf[19] == 0x55 )//更新高温温度系数
					{
						Buf[2]=Uart[Ch].Buf[16];
					}
					else if( Uart[Ch].Buf[19] == 0x5a )//更新低温温度系数
					{
						Buf[3]=Uart[Ch].Buf[17];
					}
					else if( Uart[Ch].Buf[19] == 0xaa )//更新调校值
					{
						Buf[4]=Uart[Ch].Buf[18];
					}
					else if( Uart[Ch].Buf[19] == 0x05 )//更新高温温度系数krh
					{
						Buf[9]=Uart[Ch].Buf[18];
					}
					else if( Uart[Ch].Buf[19] == 0x50 )//更新低温温度系数krl
					{
						Buf[10]=Uart[Ch].Buf[18];
					}									
					else	break;
//					if( (Buf[4]&0x7f) > 8 ) break;	//调校值修正范围为0~8
//					if( (Buf[9]&0x7f) > 50 ) break;	//调校值修正范围为0.0000~0.005(0~50)
//					if( (Buf[10]&0x7f) > 50 ) break;//调校值修正范围为0.0000~0.005(0~50)
					result = WriteE2WithBackup( ee_temperature_page, ee_temperature_inpage, Buf, ee_temperature_lenth );
					if( result ) break;
					memcpy( Tpara.Offset, Buf, ee_temperature_lenth );//更新ram温度系数
					Crc_16Bits_Add2(Tpara.Offset, ee_temperature_lenth ); //CRC计算
					RTC_RT.TempFlag = 0xff;//更新查表数据
					Adcctrl.Timer=8;//立刻启动温度adc
					k = 1;
					break;
					
				case 0x04://读温度ADC等数据
					k = 9;
					if( const_tx_flag == 0x3cc3 ) OutBuf[1] = 0xc3;	//0xc3表示温度调校过
					else	OutBuf[1] = (uint08)(const_tx_flag&0xff);	
					OutBuf[2] = Tpara.RtcTMode;	//读RTC补偿工作模式，0x55:测试模式，0xAA常温查表插值模式，其他：普通模式
					
					if( RTC->ADSIGN&BIT0 )//调校值小于0
					{
						Temp16.B16 = (uint16)((int16)RTC->ADJUST*-1);
					}
					else
					{
						Temp16.B16 = RTC->ADJUST;
					}
					OutBuf[3] = Temp16.B16;
					OutBuf[4] = Temp16.B16>>8;	//实际补偿值
					OutBuf[5] = Temperature_Adc;	//读温度ADC数据
					OutBuf[6] = Temperature_Adc>>8;
					OutBuf[7] = Fun_Para.Temper_M;	//表内温度
					OutBuf[8] = Fun_Para.Temper_M>>8;
					break;

				case 0x07://设置RTC补偿工作模式，0x55:测试模式，0xAA常温查表插值模式，其他：普通模式
//				case 0x0a://写常温顶点调校值（通信调时钟误差）
				case 0xa9://关闭温度补偿（通信调时钟误差，准备测量时钟误差）
				case 0xaa://写常温顶点调校值（通信调时钟误差）(下发2字节日计时误差,-10.0秒~10.0秒,补码)
				case 0x0b://常温温度ADC微调
					//5 常温温度ADC微调
					//6 常温顶点调校值L（通信调时钟误差）
					//7 常温顶点调校值H（通信调时钟误差）
					//8 RTC补偿工作模式，0x55:测试模式，0xAA常温查表插值模式，其他：普通模式
					#if(1 == CHINT_Mode)
					if(Ijtimer_Para.Ijtimer.B32 == 0)	//软I_J有效才设置
					{
						k = 2;
						OutBuf[0] = 0xFF; //结果
						OutBuf[1] = 0x04; //Error: bit4密码错误/未授权
						break;
					}	
					#endif
					
					if( (Ch == CHHW) || (Ch == CHBLE) || (!progenable)  ) break;//禁止红外操作,编程禁止

					Temperpara_Verify();	//温度系数校验
					memcpy( Buf, Tpara.Offset, ee_temperature_lenth );//复制温度系数
					if( Uart[Ch].Buf[ 10 ] == 0x07 )
					{
						if( (Uart[Ch].Buf[9] != 0x02)) break;//数据长度错误,编程禁止
						Buf[8] = Uart[Ch].Buf[11];
						RtcStopProcFlag = 0x00;//打开RTC温度补偿功能
					}
//					else if( Uart[Ch].Buf[ 10 ] == 0x0a )
//					{
//						if( (Uart[Ch].Buf[9] != 0x02)||(const_tx_flag == 0x3cc3) ) break;	//刚编程调校过
//						Buf[5] = Uart[Ch].Buf[11];	
//					}
					else if( Uart[Ch].Buf[ 10 ] == 0xa9 )//关闭温度补偿（通信调时钟误差，准备测量时钟误差）
					{
						if( (Uart[Ch].Buf[9] != 0x01)||(const_tx_flag == 0x3cc3) ) break;	//刚编程调校过
						if( (Tpara.RtcTMode == 0x55)||(Tpara.RtcTMode == 0xAA) ) break;//禁止关闭rtc补偿
						RtcStopProcFlag = 0x55;//关闭RTC温度补偿功能
						Adcctrl.Timer=8;//立刻启动温度adc
						k = 1;
						break;
					}
					else if( Uart[Ch].Buf[ 10 ] == 0xaa )//(下发2字节日计时误差,补码)
					{
						if( (Uart[Ch].Buf[9] != 0x03)||(const_tx_flag == 0x3cc3)||(RtcStopProcFlag!=0x55)) break;	//刚编程调校过
						
						Temp16.B08[0] = Uart[Ch].Buf[ 11 ];
						Temp16.B08[1] = Uart[Ch].Buf[ 12 ];
						if( ((int16)Temp16.B16 > 10000) || ((int16)Temp16.B16 < -10000) ) break;	//限制±10.000秒
						Temp16.B16 = Get_RTCTop_Proc( Temp16.B16 );	//折算顶点调校值
						Buf[6] = Temp16.B08[0];
						Buf[7] = Temp16.B08[1];
						RtcStopProcFlag = 0x00;//打开RTC温度补偿功能
						Buf[4] = 0;//清微调值
						if( Buf[1] == 0 ) Buf[1] = 0x80;
					}
					else	////5 常温温度ADC微调
					{
						if( (Uart[Ch].Buf[9] != 0x02)||((Uart[Ch].Buf[11]&0x7F)>50) ) break;//超出允许调整范围
						Buf[5] = Uart[Ch].Buf[11];	
					}
					result = WriteE2WithBackup( ee_temperature_page, ee_temperature_inpage, Buf, ee_temperature_lenth );
					if( result ) break;	
					
					if( (Uart[Ch].Buf[ 10 ]&0x0f) == 0x0a )//写常温顶点调校值时时间记录
					{
						I2C_Read_Eeprom( ee_rtcadj_time_page, ee_rtcadjtime_inpage, Buf, ee_rtcadjtime_lenth );
						Buf[0]++;//写常温顶点调校值次数加1
						memcpy( Buf+1, Sclock.Clockbackup, 7 );//写常温顶点调校值时时间
						memcpy( Buf+8, &Fun_Para.Temper_M, 2 );//写常温顶点调校值时温度
						Buf[7] = Uart[Ch].Buf[ 10 ];//通讯标识
						I2C_Write_Eeprom( ee_rtcadj_time_page, ee_rtcadjtime_inpage, Buf, ee_rtcadjtime_lenth );		
					}
					
					Tpara.Crc16.B08[0] += 1;
					temperpara_veri_flag = 1;
					RTC_RT.TempFlag = 0xff;//更新查表数据
					Adcctrl.Timer=8;//立刻启动温度adc
					k = 1;
					break;

				case 0x06://修改顶点调校值的偏移量	NNNN	2
//				case 0x06://下发日记时原始误差		NNNN	2	(新调校)	
					#if(1 == CHINT_Mode)
					if(Ijtimer_Para.Ijtimer.B32 == 0)	//软I_J有效才设置
					{
						k = 2;
						OutBuf[0] = 0xFF; //结果
						OutBuf[1] = 0x04; //Error: bit4密码错误/未授权
						break;
					}	
					#endif
					
					if( (Ch == CHHW) || (Ch == CHBLE) ) break;//禁止红外操作
 					if( (Uart[Ch].Buf[9] != 0x03)||(!progenable) ) break;//数据长度错误,编程禁止
 					if( Tpara.RtcTMode!=0x55 ) break;//仅在测试模式下有效
					
					Temp16.B08[0] = Uart[Ch].Buf[11];
					Temp16.B08[1] = Uart[Ch].Buf[12];
				#if( NEWCLOCKADJ == 0 ) //旧标准时钟调校
					if( (((int16)Temp16.B16)<-200)||(((int16)Temp16.B16))>200 ) break;//顶点调校值的偏移量，单位为补偿最小步长，0.238或0.119
				#endif
					RTC_RT.TestTrim = (int16)Temp16.B16;
					RTC_RT.TempFlag = 0xff;//更新查表数据
					Adcctrl.Timer=8;//立刻启动温度adc
					k = 1;
					break;
					
				case 0x08://设置查表插值数据
					#if(1 == CHINT_Mode)
					if(Ijtimer_Para.Ijtimer.B32 == 0)	//软I_J有效才设置
					{
						k = 2;
						OutBuf[0] = 0xFF; //结果
						OutBuf[1] = 0x04; //Error: bit4密码错误/未授权
						break;
					}	
					#endif
					
					if( (Ch == CHHW) || (Ch == CHBLE) ) break;//禁止红外操作
 					if( (Uart[Ch].Buf[9] != 85)||(!progenable) ) break;//数据长度错误,编程禁止
 					if( (Tpara.RtcTMode!=0x55) && (Tpara.RtcTMode!=0xAA) ) break;//仅在测试模式下有效
					
				#if( NEWCLOCKADJ == 0 ) //旧标准时钟调校
					if( const_C_Mode != 0x55 ) break;//仅在测试模式下有效

					//根据温度自动判断写入数据的地址
					//Temp16.B16 = Page
					//i = offset				
					//Temp08 = Len
					if( RTC_RT.TempFlag == 0 )//常温查表
					{
						Temp16.B16 = ee_ptatvalue_page;
						i = ee_ptatvalue_inpage;
						Temp08 = ee_ptatvalue_lenth;
					}
					else if( RTC_RT.TempFlag == 1 )//低温查表
					{
						Temp16.B16 = ee_ptatvalue_lt_page;
						i = ee_ptatvalue_lt_inpage;
						Temp08 = ee_ptatvalue_lt_lenth;
						
						Crc_16Bits_Add2(Uart[Ch].Buf+11, Temp08);
						Crc_16Bits_Add2(Uart[Ch].Buf+11+42, Temp08);
						Temp08 = Temp08+2;//加上CRC的2字节
					}
					else if( RTC_RT.TempFlag == 2 )//高温查表
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
					//根据温度自动判断写入数据的地址
					Temp16.B16 = ee_ptatvalue_page;
					i = ee_ptatvalue_inpage;
					Temp08 = ee_ptatvalue_lenth;
					
					result = I2C_Write_Eeprom( Temp16.B16, i, Uart[Ch].Buf+11, Temp08 );
					result |= I2C_Write_Eeprom( Temp16.B16+1, i, Uart[Ch].Buf+11+42, Temp08 );
			
					if( result != 0x00 ) break;
				#endif
					Fill_RTC_RT_TAdc();
					Fill_RTC_RT_TVal();
				
					Temperpara_Verify();	//温度系数校验
					memcpy( Buf, Tpara.Offset, ee_temperature_lenth );//复制温度系数
					Buf[8] = 0xAA;//下发数据后自动进入查表模式
					result = WriteE2WithBackup( ee_temperature_page, ee_temperature_inpage, Buf, ee_temperature_lenth );
					if( result ) break;	
					Tpara.Crc16.B08[0] += 1;
					temperpara_veri_flag = 1;
					RTC_RT.TempFlag = 0xff;//更新查表数据
					Adcctrl.Timer=8;//立刻启动温度adc
					k = 1;
					break;
				
				case 0x09://读常温顶点调校值（通信调时钟误差）
					k = 5;
					if( const_tx_flag == 0x3cc3 ) OutBuf[1] = 0xc3;	//0xc3表示温度调校过
					else	OutBuf[1] = (uint08)(const_tx_flag&0xff);	
					OutBuf[2] = Tpara.Offset[5];	//常温温度ADC微调
					OutBuf[3] = Tpara.Offset[6];	//常温顶点调校值L
					OutBuf[4] = Tpara.Offset[7];	//常温顶点调校值H
					break;
					
				case 0x14://停电超级电容电压	NNNNNNNN	4
					k = 5;
					memcpy( OutBuf+1, RAMBUF+12, 4 );
					break;	

				case 0x15://程序累加和	NNNNNNNN	4
					k = 5;
					Calculate_Program_Cs( OutBuf+1 );
					Inverse( OutBuf+1, 4 );
					break;
				
				case 0x16://载波复位模式字(扩展)	NN	1
					k = 2;
					OutBuf[1] = Mode.Plc;
					break;
				
				case 0x17://载波复位模式字(扩展)	NN	1
					if( Uart[Ch].Buf[9] != 0x02 ) break;//数据长度错误
					if( Wr_Ext_Number == 50 ) break;
					else if ( Wr_Ext_Number > 50 ) Wr_Ext_Number = 25;
					else Wr_Ext_Number++;
					
					if( Uart[Ch].Buf[11] != Mode.Plc )//发生改变才写数据ee
					{
						result = UpdateSysPara( 0x80+27, Uart[Ch].Buf+11, 1 );
						if( result != 0x00 ) break;
					}						
					k = 1;
					break;	
				
				case 0xAF:	//东软载波：申请地址及报警事件信息
					if( (Uart[Ch].Flag&B0000_0001) && (Uart[Ch].Buf[9] == 0x02) && (Uart[Ch].Buf[11] == 0x02) )	//广播, Len=2
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
		case 0x2E:	///*正泰CHINT 陈收	读计量芯片寄存器*///
			if(Byte2uInt(Ijtimer_Para.Ijtimer.B08) == 0 )
			{
				k = 2;
				OutBuf[0] = 0xFF; //结果
				OutBuf[1] = 0x04; //Error: bit4密码错误/未授权
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
			
		case 0x2F:	///*正泰CHINT 陈收	写计量芯片寄存器*///
			if(Byte2uInt(Ijtimer_Para.Ijtimer.B08) == 0 )
			{
				k = 2;
				OutBuf[0] = 0xFF; //结果
				OutBuf[1] = 0x04; //Error: bit4密码错误/未授权
				break;
			}
			
			result = CommWriteCalData(Ch);
			if(result) break;				
						
			k = 1;
			OutBuf[0] = 0x00;
			break;
		#endif		
		
		case 0x60:	//读计量芯片寄存器	
			if(Uart[Ch].Buf[10] < 0xf0)//读取计量芯片寄存器值
			{
				memset(&Uart[Ch].Buf[11], 0x00, 4);
				result = Comm_Read_Reg(&Uart[Ch].Buf[10]);
				if(result) break;
			}
			else if(Uart[Ch].Buf[10] < 0xf5)//读取U、I1、I2、P、F系数
			{
				result = Uart[Ch].Buf[10] - 0xf0;
				if( result == 2 ) result = 3;				//为了兼容之前的校表软件
				else if(result == 3 ) result = 2;
				Exchange( Uart[Ch].Buf+11, Emu_Para.rate[result].B08, 4 );
			}
			else break;	//非法请求
			
			k = 6;
			memcpy(&OutBuf[1], &Uart[Ch].Buf[10], 5 );
			break;
			
		case 0x61:	//写计量芯片寄存器			
			if(!progenable)
			{
				k = 2;
				OutBuf[0] = 0xFF; //结果
				OutBuf[1] = 0x04; //Error: bit4密码错误/未授权
				break;
			}
			
			if(Uart[Ch].Buf[10] < 0xf0)//写寄存器
			{
				result = Comm_Write_Reg(&Uart[Ch].Buf[10]);
				if(result) break;
			}
			else if(Uart[Ch].Buf[10] < 0xf5)//写U、I1、I2、P、F系数
			{
				result = Uart[Ch].Buf[10] - 0xf0;
				if( result == 2 ) result = 3;
				else if(result == 3 ) result = 2;
				Exchange( Emu_Para.rate[result].B08, Uart[Ch].Buf+11, 4 );
				WriteE2WithBackup( ee_emupara_page, ee_emupara_inpage, Emu_Para.rate[0].B08, ee_emupara_lenth );
			}
			else if(Uart[Ch].Buf[10] == 0xff)//校表初始化命令
			{
				for(i=0; i<4; i++)
				{
					if(Uart[Ch].Buf[11+i] != 0xff) break;
				}
				if(i != 4) break;
				
				Comm_Write_Reg(&Uart[Ch].Buf[10]);
			}
			else break;	//非法请求 
			
			k = 1;
			break;
			
		case 0x91:	//蓝牙应答帧
			if( DI07.B32 == 0x0E800006 )	//应答串口波特率选择
			{
				Ble_Step = 0;
				reg_veri_flag = 1;
			}
			
			if( DI07.B32 == 0x0E800003 )	//应答心跳
			{
				Ble_Step = 0;
			}
			
//			if( DI07.B32 == 0x0E80000A )	//应答配对加密方式
//			{
//				Ble_Step = 0;
//			}
			
			Uart[Ch].Overtime_Timer = 2;
			return;
			
		default:
			k = 2;
			OutBuf[0] = 0xFF;	//Operation result.
			if( Uart[Ch].Buf[8]&0x40 )	//红外通信口
				OutBuf[1] = 0x04; 	//Error: bit4密码错误/未授权
			else
				OutBuf[1] = 0x02;	//数据标识错, 无请求数据
			break;
	}

	if( Uart[Ch].Flag&B0000_0001 )	//地址为广播地址, 不应答
	{
		Uart[Ch].Overtime_Timer = 2;
		return;
	}
	
	Temp08 = 0;
	if( k == 0x00 ) //不发送应答帧
	{
		k=2;
		OutBuf[1]=1;	   //错误信息字ERR：其他错误(Bit0)
		Uart[Ch].Buf[8]|=0x40;		//否认帧
	}
	else
	{
		if(OutBuf[0] == 0x00)	 //确认帧
		{ 	   
		   if((Uart[Ch].Buf[8]==0x03)||(Uart[Ch].Buf[8]==0x11)||(Uart[Ch].Buf[8]==0x12))
		   	Temp08 += 4;
		   	   
		   if((Remain)||
		      (((Uart[Ch].Buf[8] == 0x11) || (Uart[Ch].Buf[8] == 0x12)) && (Byte2uInt(DI07.B08) != 0x01150004) && ((Mode.Feature1&0x04)==0x04)
  			   && ChkBufZero( Report_Data, 5 ))
		     )
		   {
		   		if( ble_inter_flag == 0 ) Uart[Ch].Buf[8]|=0x20;		 //后续帧
		   }
		}
		else
		{
//		  	if( Uart[Ch].Buf[8] == 0x03 )	//安全认证
//		  	{
//				if(hangup_comm_flag)	OutBuf[2] |= 0x01;	//远程安全认证锁住状态位
//		  	}
		  	Uart[Ch].Buf[8]|=0x40;		//否认帧
		}
	}
	
	Uart[Ch].Buf[8]|=0x80;		   //应答帧
	Uart[Ch].Buf[9]=(k-1+Temp08); //len
	memcpy( Uart[Ch].Buf+10+Temp08, OutBuf+1, k );	//搬移数据

//	Uart[Ch].Buf[7] = 0x68;
//	Uart[Ch].Buf[0] = 0x68;
	Exchange( Uart[Ch].Buf+1, Comm_Addr.Comm_Id, 6 );
	for( i=0; i<Uart[Ch].Buf[9]; i++ )
	{
		Uart[Ch].Buf[10+i] += 0x33;
	}	
	Uart[Ch].Buf[i+10]=Cal_ChkSum(Uart[Ch].Buf,Uart[Ch].Buf[9]+10);
	Uart[Ch].Buf[i+11]=0x16;
	
	//蓝牙通讯
	if( Ch == CHBLE )
	{
		if( !ble_inter_flag )	//蓝牙透传，包装一层
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
	Uart[Ch].Flag |= B0000_1000;//规约处理结束准备发送数据标志
	
	if( MeterClear == 0x55aa )	//清零
	{
		Clear_Meter( Ch, OptID.B08 );	//0x1a清零命令或者钱包初始化命令
	}
	else if( MeterClear == 0x88bb )	//电表初始化
	{
		//置位初始化开始
		OutBuf[0] = 0x33;
		OutBuf[1] = 0xcc;
		memcpy( OutBuf+2, Sclock.Clockbackup, 6 );
		I2C_Write_Eeprom( ee_factoryinit_page, ee_factoryinit_inpage, OutBuf, ee_factoryinit_len );
		
		Clear_Meter( Ch, OptID.B08 );
		Factory_Init();
		
		//置位初始化成功
		OutBuf[0] = 0x55;
		OutBuf[1] = 0xaa;
		memcpy( OutBuf+2, Sclock.Clockbackup, 6 );
		I2C_Write_Eeprom( ee_factoryinit_page, ee_factoryinit_inpage, OutBuf, ee_factoryinit_len );
	}
	else if( MeterClear == 0xaa55 )	//密钥更新
	{
		UpdateEsamKey();
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
//上报响应处理（载波通道）
void Report_Response( union B32_B08_2 DI07 )
{
	unsigned char i;
	
	if( (Byte2uInt(DI07.B08)==0x01057003) && (ReportList[1]&B0000_1100) )
	{
		if( 0x55 == BkupReport[0] ) //掉电事件
		{
			Clr_Reportdata(ee_powerdownn_inpage);	//清单项上报状态字和新增次数(有事件记录类)
					
			if( (ReportList[0]&B0000_1100) != B0000_1100 ) ReportList[0] &= B1111_0011;
			ReportList[1] &= B1111_0011;
			BkupReport[0] = 0;
			
			if( (ReportList[1] ==0) ) Uart[CHZB].RptTimer = 0; //如果上报内容还未确认，继续等待; 如果全部确认则清零定时器
		}
	}
	else if( (Byte2uInt(DI07.B08)==0x01150004) && (ReportList[1]&B0011_0000) && (Uart[CHZB].Buf[9]==16) )
	{
		if( 0xaa == BkupReport[0] ) //上报状态
		{
			unsigned char Buf[5];
			if( Uart[CHZB].Buf[14+2]&B1000_0000 ) Uart[CHZB].Buf[14+2] &= B0111_1111;
			if( Uart[CHZB].Buf[14+8]&B0010_0000 ) Uart[CHZB].Buf[14+2] |= B1000_0000;//掉电临时借用存A相断相
			if( Uart[CHZB].Buf[14+2]&B0000_0100 ) Uart[CHZB].Buf[14+2] &= ~B0000_0100;
			if( Uart[CHZB].Buf[14+3]&B0010_0000 ) Uart[CHZB].Buf[14+2] |= B0000_0100;//低电压临时借用存A相欠压
			if( Uart[CHZB].Buf[14+2]&B0000_0010 ) Uart[CHZB].Buf[14+2] &= ~B0000_0010;
			if( Uart[CHZB].Buf[14+3]&B0001_0000 ) Uart[CHZB].Buf[14+2] |= B0000_0010;//高电压临时借用存A相过压
			Buf[0] = Report_Data2[0]&Uart[CHZB].Buf[14+0];
			Buf[1] = Report_Data2[1]&Uart[CHZB].Buf[14+1];
			Buf[2] = Report_Data2[2]&Uart[CHZB].Buf[14+2];
			Buf[3] = Report_Data2[3]&Uart[CHZB].Buf[14+10];
			Buf[4] = Report_Data2[4]&Uart[CHZB].Buf[14+11];
			Xor_Data( Report_Data, Buf, 5 );//保留期间新的上报
			Xor_Data( Report_Data2, Buf, 5 );//上报状态字备份清零
			for( i=0; i<5; i++ ) Clr_Reportnum(i);//清零新增上报次数
			if( ChkBufZero( Report_Data2, 5 ) ) return;//非0,确认失败继续上报
			
//			Xor_Data( Report_Data, Report_Data2, 5 );//保留期间新的上报
//			memset( Report_Data2, 0x00, 5 );//上报状态字备份清零
//			for( i=0; i<5; i++ ) Clr_Reportnum(i);//清零新增上报次数
					
			if( (ReportList[0]&B0011_0000) != B0011_0000 ) ReportList[0] &= B1100_1111;
			ReportList[1] &= B1100_1111;
			BkupReport[0] = 0;
			
			if( (ReportList[1] ==0) ) Uart[CHZB].RptTimer = 0; //如果上报内容还未确认，继续等待; 如果全部确认则清零定时器	
		}
	}
}


//事件主动上报
unsigned char ReportEvent( uint08 repmode )
{
	unsigned char n;

	if( repmode == 0 )
	{
		if( EA_OFF ) return 0;
		if( Relay_Space_Timer ) return 0;
	}

	if( (Mode.Feature1&0x0c)!=0x08 ) ReportList[0] = 0; //主动上报未开启,不上报
	if( 0 == ReportList[0] ) return 0;
	
	for( n=0; n<6; n+=2 )
	{
		unsigned char Ch = CHZB;
		
		if( ReportList[0]&(3<<n) ) //重发次数1~3
		{
			ReportProc( Ch, n );
			break;
		}
	}
	
	return 0;
}


//事件主动上报处理
unsigned char ReportProc( unsigned char Ch, unsigned char Type )
//4-通用事件
{
	unsigned char i, k, Buf[256];
	
	if( Type == 0 || Type == 2 ) //掉电事件
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
		
		//准备掉电记录
		memcpy( Buf+4, Buf+10+1, k ); //复制数据
		
	}
	else
	{
		if( Meter_Run_Timer3 < 60 ) return 0; //上报状态字延时1min
		
		Ready_Reportdata( Buf+3 );	//主动上报状态字	NNNNNNNNNNNNNNNNNNNNNNNN	12+N
		if( ChkBufZero(Buf+3+1,12) == 0 )
		{
			ReportList[0] &= B0000_1111;
			Uart[Ch].RptTimer = 0;
			return 0;
		}
		
		//准备主动上报状态字
		Int2Byte( 0x01150004, Buf );
		k = 12;
	}
	
	if( Uart[Ch].Overtime_Timer ) return 0;//接收超时处理期间不上报
	if( Uart[Ch].Response_Timer ) return 0;//接收完成处理期间不上报
	if( Uart[Ch].S_Overtime_Timer ) return 0;
	Uart[Ch].S_Overtime_Timer= txtimeout_max*10;//发送超时(载波专用),禁止698的接收完成处理防止数据域冲突
	
	ReportList[1] = 0;
	BkupReport[0] = 0;
	if( Type == 0 || Type == 2 ) //掉电事件
	{
		if( Type == 0 )
		{
			if( ReportList[0]&B0000_0011 ) ReportList[0] -= B0000_0001;
				
			//备份上报帧中对象OAD
//			ReportList[1] |= B0000_0011;	//不支持掉电上报的接收
//			BkupReport[0] = 0x55;	
			Meter_Run_Timer1 = 0;	
		}
		else
		{
			if( ReportList[0]&B0000_1100 ) ReportList[0] -= B0000_0100;
				
			//备份上报帧中对象OAD
			ReportList[1] |= B0000_1100;	
			BkupReport[0] = 0x55;
			if( (ReportList[0]&B0000_1100) == B0000_1000 )
			Meter_Run_Timer2 = 0;
		}		
	}
	else
	{
		//备份上报帧中对象OAD
		ReportList[1] |= B0011_0000;
		if( ReportList[0]&B0011_0000 ) ReportList[0] -= B0001_0000;
		BkupReport[0] = 0xaa;
	}
	
	if( Type == 0 )  Uart[Ch].RptTimer = 25*10; //重发周期：25*4.096ms*10 = 1s	掉电上报
	else Uart[Ch].RptTimer = 123*20; //重发周期：123*4.096ms*20 = 10s

	Uart[Ch].TxBuf[8]  = 0x86;		//命令帧
	Uart[Ch].TxBuf[9]  = (k+4);		//len
	Uart[Ch].TxBuf[10] = Buf[0]; 
	Uart[Ch].TxBuf[11] = Buf[1]; 
	Uart[Ch].TxBuf[12] = Buf[2];
	Uart[Ch].TxBuf[13] = Buf[3];
	memcpy( Uart[Ch].TxBuf+14, Buf+4, k );	//搬移数据

	Uart[Ch].TxBuf[7] = 0x68;
	Uart[Ch].TxBuf[0] = 0x68;
	Exchange( Uart[Ch].TxBuf+1, Comm_Addr.Comm_Id, 6 );
	for( i=0; i<Uart[Ch].TxBuf[9]; i++ )
	{
		Uart[Ch].TxBuf[10+i] += 0x33;
	}	
	Uart[Ch].TxBuf[i+10]=Cal_ChkSum(Uart[Ch].TxBuf,Uart[Ch].TxBuf[9]+10);
	Uart[Ch].TxBuf[i+11]=0x16;
	
	Uart[Ch].TxLen  = 1;//开始发送数据
	Uart[Ch].Total_Tx = Uart[Ch].TxBuf[9]+16;
	Uart[Ch].Transfer = 0;
	UART0->TXREG = 0xfe; //载波发送0xfe
	return 0;
}

//计算CS
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

//查询心跳
void Ble_Chk_Heart(uint08 Ch)
{
	uint08 const_comm[16] = { 0x68, 0x00, 0x00, 0xFF, 0xFF, 0xEE, 0xEE, 0x68, 0x11, 0x04, 
														0x03, 0x00, 0x80, 0x0E, 
														0x00, 0x16 };

	memcpy( Uart[Ch].Buf, &const_comm, sizeof(const_comm) );
	
	Ble_Frame_Cs(Ch);
}

//设置配对加密方式
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

////串口波特率选择
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

//蓝牙初始化
void Ble_Init(void)
{	
	uint08 Ch, Temp08=0;
	
	Ch = CHBLE;
	
	if( Uart[Ch].Response_Timer || Uart[Ch].Overtime_Timer ) return;
		
	switch(Ble_Step)
	{
//		case 0:	//串口波特率选择
//			if( Mode.blebps != 0x01 ) Ble_Cfg_Bps(Ch);
//			else Temp08 = 0xff;
//			break;

		case 1:	//查询心跳
			Ble_Chk_Heart(Ch);
			break;
			
//		case 2:	//设置配对加密方式
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

		Uart[Ch].Flag |= B0000_1000;	//规约处理结束准备发送数据标志
		Uart[Ch].Response_Timer = 2; //置响应超时
	}
}
