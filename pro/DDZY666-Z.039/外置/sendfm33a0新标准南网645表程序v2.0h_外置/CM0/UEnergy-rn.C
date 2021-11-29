#include "ex_func.h"
#include "ex_var.h"
#include "FM32L0XX.h"  
#include <string.h>
#include <stdio.h>
#include <math.h>

/*********************************************/
#define	SPIWrite				0x80
#define	SPIRead					0x00

#define METER_Uk				0x2700
#define METER_I1k				0x724b
#define METER_I2k				0x7253
#define METER_Pk				0xe84c00

#define	chk_reg_num				13			//校验寄存器数
#define	ee_7051_lenth				chk_reg_num*4		//
#define ee_8209cself_inpage      		ee_7051_lenth+4		//硬件自热
#define ee_8209cself_len         		4
#define	defstep					7			//默认调整步数(6步)
#define	ee_7051adj_inpage			0
#define	ee_7051adj_lenth			2*(defstep-1)

#define heatstep                16	//自热补偿步数（16步）
#define ee_7051self_inpage      14
#define ee_7051self_len         3*heatstep
#define CORRECTION 1							//条件编译:1支持电压改变误差修正,0不支持

//********************************************//初始化默认的寄存器值
const union B32_B08_2 code Dl_Cpu_Init[chk_reg_num]=
{
	0x03006000,
	0x05000000,
	0x07000000,
	0x0a000000,
	0x0e000000,
	0x0f000000,
	0x02100000,
	0x00164300,	//0x16-4800,0x2e-2400; 43:锰铜接入, 40互感器接入
	0x01000300,
	0x17000000,
	0x09FFE800,
	0x0c000000,
	0x04006000,
};
/********************************************/
float		Pav_Temp;	//计算1分钟平均功率
float		Iav_Temp;	//计算1分钟平均电流
float		Qav_Temp;	//计算1分钟平均功率(无功)
float		Uav_Temp;	//计算1分钟平均电压
uint08		Pav_Cnt;
uint08		Iav_Cnt;
uint08		Qav_Cnt;
uint08		Uav_Cnt;
uint08		Back_Num;	//反向电量判断计数
uint08		Back_NumQ;	//反向电量判断计数(无功)
uint08 	  	Back_NumN;	//零线电流反向判断计数
uint32		Power_Bk;	//功率备份

#if( CORRECTION == 1 )	//打开计量误差修正
union B16_B08_2	Cal_Adj[defstep];//计量误差修正
unsigned char	AStep,AStep_Bk;	//计量误差修正步骤
uint08		StepDetCnt;	//计量误差修正步骤检测

//--- 自热补偿 ---
typedef struct 
{
	uint08 time[heatstep];
	union B16_B08_2 gp1[heatstep];
	uint08 Crc16[2];
}MeasureOffset1_TYPE;

MeasureOffset1_TYPE SelfHeat;

unsigned int SelfHeatTime; //自热累计时间, 秒
unsigned char SelfStep, SelfStep_Bk;
unsigned char SelfDetCnt, SelfICnt;
#endif

struct
{
	union B32_B08_2 GP1;		//03H PStart 有功启动功率寄存器
	union B32_B08_2 RGPQA;		//05H L线功率增益校正
	union B32_B08_2 RPhsA;		//07H L线相位校正
	union B32_B08_2 RAPOSA;		//0AH L线有功功率偏置校正
	union B32_B08_2 RIARMSOS;	//0EH L线电流有效值偏置补偿
	union B32_B08_2 RIBRMSOS;	//0FH N线电流有效值偏置补偿
	union B32_B08_2 RHFConst;	//02H 脉冲频率寄存器
	union B32_B08_2 RSYSCON;	//00H 系统控制寄存器
	union B32_B08_2 REMUCON;	//01H 计量控制寄存器
	union B32_B08_2 REMUCON2;	//17H 计量控制寄存器2
	union B32_B08_2 RQPhsCal;	//09H 无功相位补偿
	union B32_B08_2 RRPOSA;		//0CH L线无功功率偏置校正
	union B32_B08_2 RDStart;	//04H 无功潜动寄存器
	union B16_B08_2 Crc16;		//2字节校验和
}Att7051_Calib;

/*********************************************
计量芯片寄存器
*********************************************/
#define	IARMS			0x22
#define	IBRMS			0x23
#define	URMS			0x24
#define	Freq_U			0x25
#define	PowerPA			0x26
#define	PowerPB			0x27
#define	PowerPQ			0x28
#define	EmuStatus		0x2d

//校表参数
#define	HFConst			0x02
#define	PStart			0x03
#define	GPQA 			0x05
#define	GPQB 			0x06
#define	PHSA			0x07
#define	PHSB			0x08
#define	APOSA			0x0a
#define	APOSB			0x0b
#define	IARMSOS			0x0e
#define	IBRMSOS			0x0f
#define	IBGain			0x10

#define QPhsCal			0x09
#define	RPOSA				0x0C
#define	DStart			0x04

#define	SYSCON			0x00
#define	EMUCON			0x01
/********************************************************/
unsigned char UartReadByte(void)		//读一字节寄存器
{
//	unsigned char Temp08;
	Do_DelayStart();//10ms延时判断
	{
		if(UART4->RXFIFOSTA&B0000_0001) 
    		{
    	  		if(UART4->RXSTA&B0000_1110)
    	  		{
    	    			break;
    	 		}
    	 		return( UART4->RXREG );
    		}
	}While_DelayMsEnd(10*clkmode);
	return(0);
}

void UartWriteByte(uint08 Buf)	//写一字节寄存器
{
	UART4->TXREG = Buf;
  	Do_DelayStart();	//10ms延时判断
	{
		if( (UART_common->UARTIF&0x0100)==0x0100 ) break;	
	}While_DelayMsEnd(10*clkmode);
  
	return;
}

void EmuRegOp( unsigned char OpMode, unsigned char *OpData,  unsigned char Len)	//读写寄存器控制
{
	unsigned char i;
	UART4->RXSTA &=(~B0000_1110) ;
	UartWriteByte(OpData[0]);		//写寄存器地址
	
	for(i = 1; i < Len; i++)
	{
		if(OpMode == SPIRead)		//Read
		{
			OpData[i] = UartReadByte();
		}
		else
		{
			UartWriteByte(OpData[i]);
		}
	}
}

extern unsigned char  Cal_ChkSum(unsigned char *Buf,unsigned char Len);
/********************************************************/
//OpMode:操作类型: Write(0x80); Read(0x00)
//OpData:操作的寄存器地址: 高字节在前,低字节在后,按实际字节数读写
/********************************************************/
unsigned char ATT7051SPIOp(	unsigned char OpMode, unsigned char *OpData)
{
	unsigned char i, r, addr;
	unsigned char TempBuf[6];
	unsigned char UartBuf[6];
	
	if     (OpData[3] <= 0x06) r = 2+1;
	else if(OpData[3] <= 0x08) r = 1+1;
	else if(OpData[3] <= 0x21) r = 2+1;
	else if(OpData[3] <= 0x24) r = 3+1;	
	else if(OpData[3] == 0x25) r = 2+1;
	else if(OpData[3] <= 0x28) r = 4+1;
	else if(OpData[3] <= 0x2d) r = 3+1;
	else if(OpData[3] <= 0x43) r = 1+1;
	else if(OpData[3] == 0x44) r = 4+1;
	else if(OpData[3] == 0x45) r = 2+1;
	else if(OpData[3] == 0x50) r = 2+1;
	else if(OpData[3] == 0x51) r = 2+1;
	else if(OpData[3] == 0xEA) r = 1+1;
	else r = 3+1;

	if( OpMode == SPIWrite )  Exchange(UartBuf, OpData, 4);		//变成高字节在前,即地址在前
	else
	{
		memset(UartBuf, 0x00, 4);
		UartBuf[0] = OpData[3];					//寄存器地址
	}
	addr = UartBuf[0];
	
	if(OpMode == SPIWrite)
	{
		UartBuf[0] = addr|OpMode;
		UartBuf[r] = ~Cal_ChkSum(UartBuf, r);
	}
	r++;	//增加一字节校验码
	
 	for(i = 0; i<5; i++)
 	{
 		if( EA_OFF ) return 1;				//掉电不处理,程序直接返回
		Clear_Wdt();
//		{RXSTA3= 0;RXSTA3= B0101_0000;}			//8位数据,偶校验,RXEN=1
		
		EmuRegOp( OpMode, UartBuf, r);
		if(addr == 0xea) return 0;
		
		if(OpMode == SPIRead)
		{
			if( UartBuf[r-1] != ((~Cal_ChkSum(UartBuf, r-1))&0xFF) )  continue;	//校验和错，重新读
			memset(UartBuf+r-1,0,6-(r-1));
			if( (addr == PowerPA) || (addr == PowerPB) || (addr == PowerPQ) ) Exchange(OpData, UartBuf+1, 4);	//功率数据中不包括地址
			else
			{
				Exchange(OpData, UartBuf, 4);	//转换成小端数据,即地址在后
			}
			return 0;
		}
		else
		{
			TempBuf[0] = addr;
			EmuRegOp( SPIRead, TempBuf, r);//读取比较

			if( Cmp_Data(UartBuf+1,TempBuf+1,r-2) == 3 ) return 0;//读写成功
		}
	}
	return 1;			//读写失败
}
/**********************************************************/
void Cal_Pav(void)
{
	union B32_B08_2 S1_Temp;	
	
	if( Pav_Cnt )
	{
		S1_Temp.B32 = Pav_Temp/(float)Pav_Cnt;		//计算平均功率
		Hex2Bcd_SS(S1_Temp.B08, Emu_Data.Pav.B08, 4);
		
		Pav_Temp = 0;
		Pav_Cnt = 0;
	}
	
	if( Iav_Cnt )
	{
		S1_Temp.B32 = Iav_Temp/(float)Iav_Cnt;		//计算平均电流
		Emu_Data.Iav[2].B32 = Emu_Data.Iav[1].B32;
		Emu_Data.Iav[1].B32 = Emu_Data.Iav[0].B32;
		Hex2Bcd_SS(S1_Temp.B08, Emu_Data.Iav[0].B08, 4);
		
		Iav_Temp = 0;
		Iav_Cnt = 0;
	}
	
	if( Qav_Cnt )
	{
		S1_Temp.B32 = Qav_Temp/(float)Qav_Cnt;		//计算平均功率(无功)
		Hex2Bcd_SS(S1_Temp.B08, Emu_Data.Qav.B08, 4);
		
		Qav_Temp = 0;
		Qav_Cnt = 0;
	}
	
	if( Uav_Cnt )
	{
		S1_Temp.B32 = Uav_Temp/(float)Uav_Cnt;		//计算平均电压
		Hex2Bcd_SS(S1_Temp.B08, Emu_Data.Uav.B08, 4);
		
		Uav_Temp = 0;
		Uav_Cnt = 0;
	}
}
/**********************************************************/
//CH=0xe5,写允许
//CH=0xdc,写禁止
//CH=0x5a,选择通道A
//CH=0xa5,选择通道B
void ATT7051WRPRO( unsigned char CH)
{
	union B32_B08_2 SPIOpData;
	
	SPIOpData.B32 = 0xea000000;
	
	if((CH == 0x5a) || (CH == 0xa5))	//通道选择 
	{		
		SPIOpData.B08[2] = 0xe5;				//写允许
		ATT7051SPIOp(SPIWrite,SPIOpData.B08);
		
		SPIOpData.B08[2] = CH;
		ATT7051SPIOp(SPIWrite,SPIOpData.B08);
		
		SPIOpData.B08[2] = 0xdc;				//写禁止
		ATT7051SPIOp(SPIWrite,SPIOpData.B08);
	}
	else
	{
		SPIOpData.B08[2] = CH;
		ATT7051SPIOp(SPIWrite,SPIOpData.B08);
	}	
}

/**********************************************************/
unsigned char Read_UIPF( unsigned char num, unsigned char *RtBuf )
{
	unsigned char i, SPIOpResult;
	union B32_B08_2 SPIOpData;
	const uint08 code RegAddr[6]={URMS,IARMS,PowerPA,IBRMS,Freq_U,PowerPQ};
	
	for(i=0; i<num; i++)
	{
		SPIOpData.B08[3] = RegAddr[i];
		SPIOpResult = ATT7051SPIOp(SPIRead,SPIOpData.B08);
		if(SPIOpResult) return (0x81+i);
		
		if( (i == 2) || (i == 5) )
		{
			if(SPIOpData.B08[3] & B1000_0000)	//功率符号位
			{
				SPIOpData.B32 = (~SPIOpData.B32) + 1;
			}
		}
		else
		{
			if(SPIOpData.B08[2] & B1000_0000) SPIOpData.B32 = 0;	//电压、电流寄存器特殊处理
			SPIOpData.B08[3] = 0;	//地址清0
		}
		
		memcpy(RtBuf+4*i, SPIOpData.B08, 4);
	}
	
	return 0x00;
}
/**********************************************************/
void Read_UIP(void)					//读取计量芯片UIP参数
{
	union B32_B08_2 RegData[9],SPIOpData; //U, I1, P1, I2, F
	unsigned char SPIOpResult, i, j, P_flag;
	
	read_back_flag = 0;
	
	//---计量芯片故障事件处理---
	SPIOpData.B08[3] = 0x7f;	//读rn8209的设备id
	ATT7051SPIOp(SPIRead,SPIOpData.B08);
	if( SPIOpData.B32 != Def_Device_Id )
	{	
		if( (EmuErrCnt >= Bcd_To_Hex(VolLimit.Cal_Err_Period)) && (EmuErrCnt >= 10) )
		{
			if( cal_err_flag == 0 ) Note_Run_Event(ee_calerrn_inpage); //计量芯片故障记录起始时间
			cal_err_flag = 1;
			
			//无计量芯片存在
			dl_back_flag = 0;
			dl_back_flag2 = 0;
			dln_back_flag = 0;
			Pav_Temp = 0;
			Pav_Cnt = 0;
			Iav_Temp = 0;
			Iav_Cnt = 0;
			Qav_Temp = 0;
			Qav_Cnt = 0;
			Uav_Temp = 0;
			Uav_Cnt = 0;
			memset( Emu_Data.I1.B08, 0x00, 56-4 );
			Emu_Data.U.B32 = 0x100; //通信故障时，默认为10V
			Emu_Data.Cosa.B32 =0x1000;
			Emu_Data.Freq.B32 =0x5000;
//			check_7051_flag1 = 1;	//重新初始化计量芯片
		}
		else EmuErrCnt++;
		PowerDetCnt0 = 0;
		return;
	}
	else
	{
		if( EmuErrCnt == 0 )
		{
			if( cal_err_flag ) Note_Run_Event( ee_calerrn_inpage|0x80 ); //计量芯片故障记录结束
			cal_err_flag = 0;
		}
		else EmuErrCnt = 0;
	}
	
	if( Sclock.Clockmain[0] == 0 ) Cal_Pav();			//每分钟计算一次平均功率
	
	//------读计量状态
	SPIOpData.B08[3] = EmuStatus;
	SPIOpResult = ATT7051SPIOp(SPIRead,SPIOpData.B08);
	if(SPIOpResult==0) P_flag = SPIOpData.B08[2];
	else P_flag = 0xff;
		
	//读取时时参数(U, I1, P1, I2, F, PQ)
	if(read_uip_flag1)
	{
		SPIOpResult = Read_UIPF( 6, RegData[0].B08 );
		j = 9;	
		RegData[7].B32 = RegData[4].B32;	//转存用于后面的频率计算
		RegData[8].B32 = RegData[5].B32;	//转存用于后面的无功计算
	}
	else
	{
		SPIOpResult = Read_UIPF( 1, RegData[0].B08 );
		j = 1;
	}
	
	if(SPIOpResult==0x81)	//读电压错误
	{
		PowerDetCnt0 = 0;
		read_uip_flag1 = 0;
		return;
	}
	else
	{
		if(SPIOpResult>0x81)	j = 1;//读其他数据错误, 仅进行电压计算处理
		Adj_Clk_Timer_S = Adjclk_timer_delay_s;	//重新启动定时8M时钟调校功能		
	}

	for( i=0; i<j; i++ )
	{
		switch(i)
		{
			case 0:	//U
				RegData[i].B32 = RegData[i].B32*10/Emu_Para.rate[i].B32;
				Uav_Temp += RegData[0].B32;	//累计每分钟平均电压值
				Uav_Cnt ++;
				break;
				
			case 1:	//IA,IB
			case 3:
				RegData[i].B32 = RegData[i].B32*1000.0/Emu_Para.rate[i].B32;
				if( i == 1 )
				{
					if((P_flag & B0000_1000)==0) 
					{
						Iav_Temp += RegData[1].B32;	//累计每分钟平均电流值
					}
					Iav_Cnt ++;
				}
				break;
			
			case 2:	//P1
				RegData[i].B32 = RegData[i].B32*10000.0/Emu_Para.rate[i].B32;				
				break;
				
			case 4:	//Ps
				RegData[i].B32 = RegData[0].B32*RegData[1].B32/1000;
				break;
				
			case 5:	//Cosa
				if(RegData[4].B32)
				{
					RegData[i].B32 = RegData[2].B32*1000.0/RegData[4].B32;
				}
				else 
					RegData[i].B32 = 1000;
				break;
				
			case 6:	//PAV
				if((P_flag & B0000_1000) == 0)
				{
					Pav_Temp += RegData[2].B32;	//累计每分钟平均功率值
				}
				Pav_Cnt ++;
				break;
				
			case 7:	//Freq
				RegData[i].B32 = 44744312.5/(RegData[i].B32>>8);//3579545*100/8/RegData[7].B32;
				break;
				
			case 8:	//PQ	
				RegData[i].B32 = RegData[i].B32*10000.0/Emu_Para.rate[2].B32;
				if((P_flag & B0001_0000)==0) 
				{
					Qav_Temp += RegData[i].B32;	//累计每分钟平均电流值
				}
				Qav_Cnt ++;
				break;
				
			default:
				break;
		}
		
		if( i != 6 ) Hex2Bcd_SS(RegData[i].B08, Emu_Data.U.B08+4*i, 4);
	}

	if( (Emu_Data.U.B32 < Def_Relay_ActL) || (Emu_Data.U.B32 > Def_Relay_ActH) ) below_70u_flag = 1;
	else
	{
		if( below_70u_flag ) run_alarm_flag = 1;	//电压恢复70%及时动作继电器
		below_70u_flag = 0;
	}
	
	//异常处理
	if(Emu_Data.U.B32 > 0x4500) Emu_Data.U.B32 = 0;		//电压>450V为异常	
	if(Emu_Data.I1.B32 > 0x160000) Emu_Data.I1.B32 = 0;//电流>160A为异常
	if((Emu_Data.I2.B32 > 0x160000)||(Emu_Data.I2.B32 < Def_Shielding_I2)) Emu_Data.I2.B32 = 0;//电流>160A为异常
	if(Emu_Data.Cosa.B32 > 0x0980)	{Emu_Data.Cosa.B32 =0x1000; Emu_Data.Q1.B32 = 0;}
	
//	if(read_uip_flag1==0)
	{
		//每2秒检测一次计量芯片是否复位
		SPIOpData.B08[3] = HFConst;
		ATT7051SPIOp(SPIRead,SPIOpData.B08);
		if((SPIOpData.B32 != Att7051_Calib.RHFConst.B32) && (Att7051_Calib.RHFConst.B32 != 0xffffffff))
		{
			check_7051_flag1 = 1;	//重新初始化计量芯片
		}
		
		if( SelfStep == 0 )
		{
			SPIOpData.B08[3] = GPQA;
			ATT7051SPIOp(SPIRead,SPIOpData.B08);
			if((SPIOpData.B32 != Att7051_Calib.RGPQA.B32) && (Att7051_Calib.RGPQA.B32 != 0xffffffff))
			{
				check_7051_flag1 = 1;	//重新初始化计量芯片
			}		
		}
	}
	read_uip_flag1 = 0;	
	
	if( P_flag != 0xff )
	{
		//反向电流的判断
		SPIOpData.B08[3] = PowerPA;
		SPIOpResult = ATT7051SPIOp(SPIRead,SPIOpData.B08);
		if(SPIOpResult == 0)
		{	
			if( ((P_flag & B0000_1000)==0) && (SPIOpData.B08[3] & B1000_0000) )//判断是否大于启动功率同时功率符号位为1
			{
				if(Back_Num < 2) Back_Num++;
				else
				{
					if( dl_back_flag == 0 )
					{
						Emu_Data.Pav.B32 = 0;
						Pav_Cnt = 0;
						Pav_Temp = 0;
					}
					dl_back_flag = 1;	//反向
				}	
			}
			else
			{
				Back_Num = 0;
				if( dl_back_flag == 1 )
				{
					Emu_Data.Pav.B32 = 0;
					Pav_Cnt = 0;
					Pav_Temp = 0;
				}
				dl_back_flag = 0;		//正向 
			}
		}
		
		//无功反向电流的判断
		SPIOpData.B08[3] = PowerPQ;
		SPIOpResult = ATT7051SPIOp(SPIRead,SPIOpData.B08);
		if(SPIOpResult == 0)
		{	
			if( ((P_flag & B0001_0000)==0) && (SPIOpData.B08[3] & B1000_0000) )//判断是否大于启动功率同时功率符号位为1
			{
				if(Back_NumQ < 2) Back_NumQ++;
				else
				{
					if( dl_back_flag2 == 0 )
					{
						Emu_Data.Qav.B32 = 0;
						Qav_Cnt = 0;
						Qav_Temp = 0;
					}
					dl_back_flag2 = 1;	//无功反向
				}	
			}
			else
			{
				Back_NumQ = 0;
				if( dl_back_flag2 == 1 )
				{
					Emu_Data.Qav.B32 = 0;
					Qav_Cnt = 0;
					Qav_Temp = 0;
				}
				dl_back_flag2 = 0;		//无功正向 
			}
		}
	
		//------通道选择:只计A通道
		if(P_flag & B0010_0000)
		{
			ATT7051WRPRO(0x5a);		//选择A
		}
		
		//------启动功率判断
		if(P_flag & B0000_1000)
		{
			if( (Emu_Data.Cosa.B32 >= Def_Shielding_Cos) || (Emu_Data.I1.B32 < Def_Shielding_I1) )
			{
				Emu_Data.I1.B32 = 0;
				Emu_Data.P2.B32 = 0;
				Emu_Data.Cosa.B32 = 0x1000;
			}
			Emu_Data.P1.B32 = 0;
			power_zero_flag = 1;	//置功率等于0标志
		}
		else	power_zero_flag = 0;	//清功率等于0标志
			
		if(P_flag & B0001_0000)
		{
			Emu_Data.Q1.B32 = 0;
		}
	}

	if(Emu_Data.P1.B32 == 0) power_zero_flag = 1;	//置功率等于0标志
	
	//零线电流反向判断
	SPIOpData.B08[3] = PowerPB;
	SPIOpResult = ATT7051SPIOp(SPIRead,SPIOpData.B08);
	if(SPIOpResult == 0)
	{
		if( Emu_Data.I2.B32 && (SPIOpData.B08[3] & B1000_0000) )//判断是否有电流同时功率符号位为1
		{
			if(Back_NumN < 2) Back_NumN++;
			else dln_back_flag = 1;	//反向
		}
		else
		{
			Back_NumN = 0;
			dln_back_flag = 0;		//正向 
		}
	}
}

/**********************************************************/
//1	上一次掉电有结束时间则允许新的掉电记录开始
//0	上一次掉电结束时间为0则允许记录掉电结束
unsigned char ChkPdRcdTime(void)
{
	unsigned char Temp08, BufA[ee_powerdownnote_lenth];
	
	if( RdRecTimes(ee_powerdownn_inpage) )
	{
		Temp08 = Read_Event_Point(ee_powerdownn_inpage);
		I2C_Read_Eeprom( ee_powerdown_note_page+Temp08, ee_powerdownnote_inpage, BufA, ee_powerdownnote_lenth );	//时间   
		return( ChkBufZero(BufA+6,6) ); 
	}
	else
	{
		return 1;
	}
}
/**********************************************************/
void Judge_Uip_Data(void)
{
	union B32_B08_2 SPIOpData;
	union B16_B08_2 Temp16;
#if( CORRECTION == 1 )	//打开计量误差修正	
	unsigned char inpage=0, offset=0;
#endif
//	if( Relay_Mode != 0x55 )//内置继电器
	{
		//拉闸过载判断
		Exchange( SPIOpData.B08, Mode.Limit_I, 3 );//XXX.XXX
		SPIOpData.B08[3] = 0;
		if( (Emu_Data.I1.B32 > SPIOpData.B32) && SPIOpData.B32 )
		{
			if( Current_Over_Count >= Defcurrovercount )
			{
				if( over_xxx_flag == 0 ) CurrentTimer = Calculate_Timer(1);
				over_xxx_flag = 1;	//拉闸电流超标志
			}
			else Current_Over_Count++;
		}
		else
		{
			if( SPIOpData.B32 == 0 ) Current_Over_Count = 0;
			if( Current_Over_Count == 0 )
			{
				CurrentTimer = 0;
				if( over_xxx_flag ) run_alarm_flag = 1;
				over_xxx_flag = 0;
			}
			else Current_Over_Count--;
		}
	}
//	else
//	{
//		over_xxx_flag = 0;	//清拉闸电流超标志
//		relay_delay_flag = 0;	//清大电流延时跳闸标志
//	}

	//过流记录
	SPIOpData.B08[0] = 0;
	Exchange( SPIOpData.B08+1, Week_Holiday.Max_I.B08, 2 );//XXX.X
	SPIOpData.B08[3] = 0;
	if( (Emu_Data.I1.B32 > SPIOpData.B32) && SPIOpData.B32 )//判断电流是否到大于触发下限
	{
		if( Current_Over_Count2 >= Bcd_To_Hex(Week_Holiday.Max_I_Period) )
		{
			if( load_over_flag==0 ) Note_Run_Event(ee_maxi_inpage);//记录电流过载事件(开始)	
			load_over_flag = 1;
		}
		else Current_Over_Count2++;
	}
	else
	{
		if( SPIOpData.B32 == 0 ) Current_Over_Count2 = 0;
		if( Current_Over_Count2 == 0 )
		{
			if( load_over_flag ) Note_Run_Event(ee_maxi_inpage|0x80);//记录电流过载事件(结束)
			load_over_flag = 0;
		}
		else Current_Over_Count2--;
	}
	
	//失压记录
	if( (Emu_Data.U.B32 < Byte2Short( VolLimit.Lost_V_Min.B08)) && Byte2Short( VolLimit.Lost_V_Min.B08) && ((Emu_Data.I1.B32<<4) > Byte2uInt( VolLimit.Lost_V_I.B08)) ) 
	{
		if( Current_Over_Count3 >= Bcd_To_Hex(VolLimit.Lost_V_Period) )
		{
			if( lost_v_flag==0 ) Note_Run_Event(ee_lostvn_inpage);//记录失压事件(开始)	
			lost_v_flag = 1;
		}
		else Current_Over_Count3++;
	}
	else if( (Emu_Data.U.B32 > Byte2Short( VolLimit.Lost_V_Max.B08)) || (Byte2Short( VolLimit.Lost_V_Min.B08) == 0) || ((Emu_Data.I1.B32<<4) <= Byte2uInt( VolLimit.Lost_V_I.B08)) )
	{
		if( Byte2Short( VolLimit.Lost_V_Min.B08) == 0 ) Current_Over_Count3 = 0;
		if( Current_Over_Count3 == 0 )
		{
			if( lost_v_flag ) Note_Run_Event(ee_lostvn_inpage|0x80);//记录失压事件(结束)
			lost_v_flag = 0;
		}
		else Current_Over_Count3--;
	}
	if( lost_v_flag && Emu_Data.I1.B32 ) //每秒平均电流(用于计算失压的安时数)
	{
		Bcd2Hex_SS( Emu_Data.I1.B08, SPIOpData.B08, 4 );
		if( Lost_Aver_I == 0 ) Lost_Aver_I = SPIOpData.B32;
		else Lost_Aver_I = (SPIOpData.B32+Lost_Aver_I)/2;
	}
	
	//低电压事件
	if( (Emu_Data.Uav.B32 == 0) && (Sclock.Clockmain[0] == 0x59) && (lower_v_event_flag||high_v_event_flag) ) Emu_Data.Uav.B32 = Emu_Data.U.B32;
	if( (Emu_Data.Uav.B32 < Byte2Short( VolLimit.Lower_V.B08)) && Byte2Short( VolLimit.Lower_V.B08) ) 
	{
//		if( Current_Over_Count4 >= 5 )
		{
			lower_v_flag = 1;//置低电压标志
		}
//		else Current_Over_Count4++;
	}
	else if( Emu_Data.Uav.B32 > Byte2Short( VolLimit.Lower_V.B08) )
	{
		if( Byte2Short( VolLimit.Lower_V.B08) == 0 ) Current_Over_Count4 = 0;
		if( Current_Over_Count4 == 0 )
		{
			lower_v_flag = 0;//清低电压标志
		}
		else Current_Over_Count4--;
	}
	
	if( lower_v_event_flag == 0 )
	{
		if( lower_v_flag )
	 	{
	 		Bcd2Hex_LS( VolLimit.Lower_V_Period.B08, Temp16.B08, 2 ); //低电压事件延时判定时间
	 		if( (Current_Over_Count41 >= Temp16.B16) && (Sclock.Clockbackup[1] || Sclock.Clockbackup[2] || Sclock.Clockbackup[3]>0x01 || Sclock.Clockbackup[4]>0x01) )//发生时间非xx年1月1日0点0分
			{
//				memcpy( Eeprom.Buffer+6, Emu_Data.U.B08, 2 );	//电压xxx.x
				Note_Run_Event(ee_lowervn_inpage);//记录低电压事件(开始)	
				lower_v_event_flag = 1;
				Store_Meterstatus();
//				Keeptime.Times[6] = Current_Over_Count41; //赋初值
				Current_Over_Count41 = 0;
			}
	 	}
	 }
	
	//高电压事件
	if( (Emu_Data.Uav.B32 > Byte2Short( VolLimit.High_V.B08)) && Byte2Short( VolLimit.High_V.B08) ) 
	{
//		if( Current_Over_Count5 >= 5 )
		{
			high_v_flag = 1;//置高电压标志
		}
//		else Current_Over_Count5++;
	}
	else if( Emu_Data.Uav.B32 < Byte2Short( VolLimit.High_V.B08) )
	{
		if( Byte2Short( VolLimit.High_V.B08) == 0 ) Current_Over_Count5 = 0;
		if( Current_Over_Count5 == 0 )
		{
			high_v_flag = 0;//清高电压标志
		}
		else Current_Over_Count5--;
	}
	
	if( high_v_event_flag == 0 )
	{
		if( high_v_flag )
	 	{
	 		Bcd2Hex_LS( VolLimit.High_V_Period.B08, Temp16.B08, 2 ); //高电压事件延时判定时间
	 		if( (Current_Over_Count51 >= Temp16.B16) && (Sclock.Clockbackup[1] || Sclock.Clockbackup[2] || Sclock.Clockbackup[3]>0x01 || Sclock.Clockbackup[4]>0x01) )//发生时间非xx年1月1日0点0分
			{
//				memcpy( Eeprom.Buffer+6, Emu_Data.U.B08, 2 );	//电压xxx.x
				Note_Run_Event(ee_highvn_inpage);//记录高压事件(开始)	
				high_v_event_flag = 1;
				Store_Meterstatus();
//				Keeptime.Times[7] = Current_Over_Count51; //赋初值
				Current_Over_Count51 = 0;
			}
	 	}
	 }
	
	//零线电流异常记录
	if( (((Emu_Data.I1.B32<<4) > Byte2uInt(Week_Holiday.NLine_I.B08)) || ((Emu_Data.I2.B32<<4) > Byte2uInt(Week_Holiday.NLine_I.B08))) && Byte2uShort(Week_Holiday.NLine_Limit.B08) )
	{
		union B32_B08_2 Hex_I1, Hex_I2;
		
		Exchange( Hex_I1.B08, Emu_Data.I1.B08, 4 );
		Bcd2Hex( Hex_I1.B08, Hex_I1.B08, 4 );
		Inverse( Hex_I1.B08, 4 );
		
		Exchange( Hex_I2.B08, Emu_Data.I2.B08, 4 );
		Bcd2Hex( Hex_I2.B08, Hex_I2.B08, 4 );
		Inverse( Hex_I2.B08, 4 );
		
		if( Hex_I1.B32 > Hex_I2.B32 )
		{
			SPIOpData.B32 = ((float)(Hex_I1.B32-Hex_I2.B32)/Hex_I1.B32)*10000;
		}
		else if( Hex_I1.B32 < Hex_I2.B32 )
		{
			SPIOpData.B32 = ((float)(Hex_I2.B32-Hex_I1.B32)/Hex_I2.B32)*10000;
		}
		else
		{
			SPIOpData.B32 = 0;
		}
		
		Bcd2Hex_LS( Week_Holiday.NLine_Limit.B08, Temp16.B08, 2 );//零线电流不平衡限值
		if( SPIOpData.B32 > Temp16.B16 )
			SPIOpData.B32 = 1;
		else
			SPIOpData.B32 = 0;
	}
	else
	{
		SPIOpData.B32 = 0;
	}
	
	if( SPIOpData.B32 )
	{
		if( Nline_Err_Count >= Bcd_To_Hex(Week_Holiday.NLine_Period) )
		{
			if( nline_err_flag == 0 ) Note_Run_Event( ee_nlineerrn_inpage ); //零线电流异常事件(开始)	
			nline_err_flag = 1;
		}
		else Nline_Err_Count++;	
	}
	else
	{
		if( Nline_Err_Count == 0 )
		{
			if( nline_err_flag ) Note_Run_Event( ee_nlineerrn_inpage|0x80 ); //零线电流异常事件(结束)
			nline_err_flag = 0;
		}
		else Nline_Err_Count--;
	}	
	
	//60%Un掉电记录
//	if( (Emu_Data.U.B32 < Defaultpdvoltage) && (Emu_Data.I1.B32 < Defaultpdcurrent) )
	if( (Emu_Data.U.B32 < Defaultpdvoltage) )
	{
//		if( Voltage_Low_Count >= Display_Para.PwrDnDelay )	//检测去抖
		if( (Voltage_Low_Count >= Bcd_To_Hex(Mode.Powerd_Period)) && (Voltage_Low_Count >= 3) )
		{
			if( below_60u_flag == 0 )
			{
				Note_Run_Event( ee_powerdownn_inpage ); //掉电事件起始记录
			}
			below_60u_flag = 1;
		}
		else
		{
			Voltage_Low_Count++;
		}
	}
	else
	{
		if( Voltage_Low_Count == 0 )
		{
			if( below_60u_flag )
			{
				if( ChkPdRcdTime() == 0 )
				{
					Note_Run_Event( ee_powerdownn_inpage|0x80 ); //掉电事件结束记录
					Set_Reportdata(2*8+7);	//临时借用存A相断相
				}
			}
			below_60u_flag = 0;
		}
		else 
		{
			if( Voltage_Low_Count>Deflowvoltagecount ) Voltage_Low_Count = Deflowvoltagecount;
			Voltage_Low_Count--;
		}
	}
	
	//0.7Un~1.2Un时,检测电源异常/继电器
	if( (Emu_Data.U.B32 >= Def_Relay_Det) && (Emu_Data.U.B32 <= 0x2680)  )	
	{
		if(PowerDetCnt0 < 4) PowerDetCnt0++;
	}
	else
	{
		PowerDetCnt0 = 0;
	}
	
	//电源异常检测
	if( Emu_Data.U.B32 > 0x2860  )	
	{
		if(PowerDetCnt1 < 10) PowerDetCnt1++;
	}
	else
	{
		if(PowerDetCnt1) PowerDetCnt1--;
	}
	
	//电压是否连续8s小于170V
	if( Emu_Data.U.B32 < Def_Relay_Det  )	
	{
		if(PowerDetCnt2 < 8) PowerDetCnt2++;

	}
	else
	{
		if(PowerDetCnt2) PowerDetCnt2--;
	}
	
	//异常处理(关闭脉冲计量)
	if( Emu_Data.U.B32 < Defendenergyvoltage )
	{
		if(PowerDetCnt3 < 3) PowerDetCnt3++;
		else
		{
			Disable_Pulse();	//关闭计量
		}
	}
	else
	{
		PowerDetCnt3 = 0;
		Enable_Pulse();	//打开计量		
	}
	
	VolPassRate(); //每秒钟累计时间和监测当前电压

#if( CORRECTION == 1 )	//打开计量误差修正	
	if( (Emu_Data.U.B32 >= 0x2600) && (Emu_Data.U.B32  <= 0x2700) ) offset = 1;				//120%
	else if( (Emu_Data.U.B32 >= 0x2390) && (Emu_Data.U.B32  <= 0x2450) )  offset = 2;	//110%
	else if( (Emu_Data.U.B32 >= 0x1950) && (Emu_Data.U.B32  <= 0x2010) )  offset = 3;	//90%
	else if( (Emu_Data.U.B32 >= 0x1500) && (Emu_Data.U.B32  <= 0x1600) )  offset = 4;	//70%

	if( (Emu_Data.I1.B32 >= 0x90) && (Emu_Data.I1.B32 <= 0x750) )  //判断电流范围 
	{    
		if( (Emu_Data.Cosa.B32 > 0x0400)&&(Emu_Data.Cosa.B32 < 0x0600) )//判断功率因数是否为0.5L
		{
			if( offset == 1 ) inpage = 5; 
			else if( offset == 4 ) inpage = 6; 
		}
		else if(Emu_Data.Cosa.B32 > 0x0900)
		{
			inpage = offset; 
		}
	}

	if( Correction_Mode == 0x55 )
	{
		if( inpage != AStep_Bk )
		{
			AStep_Bk = inpage;
			StepDetCnt = 0;
			if( inpage == 0	)            //当不在补偿范围之内时  立即恢复
			{
				AStep = AStep_Bk;
				check_7051_flag1 = 1;	
				StepDetCnt = 5;
			}
		}
		else
		{
			if( StepDetCnt > 3 ) 
			{
				if( StepDetCnt == 4 )
				{          
					AStep = AStep_Bk;
					check_7051_flag1 = 1;	//重新初始化计量芯片	
					StepDetCnt++;
				}
			}
			else StepDetCnt++;
		}      
	}
	else 
	{
		AStep = 0;
		AStep_Bk = 0;
	}        
	
	//--- 自热补偿 ---
	if( Emu_Data.I1.B32 < Def_SelfHeat_I ) //要求是60A，由于台体存在电流波动, 改成59A。
	{
		if( SelfICnt < Def_SelfHeat_Cancel ) SelfICnt++; //电流变小后累计60s才退出自热补偿
		else SelfHeatTime = 0;
	}
	else
	{
		if( SelfICnt ) SelfICnt--;
		if(	SelfHeatTime < 130*60-1 )	SelfHeatTime++;
	}
	
	for( inpage=0; inpage<heatstep; inpage++ )
	{
		if( SelfHeatTime < SelfHeat.time[inpage]*60L ) break;
	}
	
	if( inpage && (SelfHeat.time[inpage-1] == 0) ) inpage = 0; //容错处理：时间值为零，采用默认值
	
	if( Correction_Mode == 0x55 )
	{
		if( inpage != SelfStep_Bk )
		{
			SelfStep_Bk = inpage;
			SelfDetCnt = 0;
			if( inpage == 0	)            //当不在补偿范围之内时  立即恢复
			{
				SelfStep = SelfStep_Bk;
				check_7051_flag1 = 1;	
				SelfDetCnt = 5;
			}
		}
		else
		{
			if( SelfDetCnt > 3 ) 
			{
				if( SelfDetCnt == 4 )
				{
					SelfStep = SelfStep_Bk;
					check_7051_flag1 = 1;	//重新初始化计量芯片	
					SelfDetCnt++;
				}
			}
			else SelfDetCnt++;
		}
	}
	else
	{
		SelfStep = 0;
		SelfStep_Bk = 0;
	}
#endif		
}
/**********************************************************/
#if( CORRECTION == 1 )	//打开计量误差修正
unsigned long int Calculate_Adj( unsigned char offset )
{	
	union B32_B08_2 Temp32;
	unsigned long int *Ptr32;
	
	Ptr32 = &(Att7051_Calib.GP1.B32);
	Temp32.B32 = Ptr32[offset];
	
	if( AStep && (AStep<defstep) )
	{
		if( offset==3 ) //L线有功功率偏置校准
		{
			Temp32.B08[3] = APOSA;
			Temp32.B08[2] = Cal_Adj[AStep-1].B08[1];
			Temp32.B08[1] = Cal_Adj[AStep-1].B08[0];
			Temp32.B08[0] = 0;
		}
	}

	if( SelfStep && (SelfStep<=heatstep) )
	{
		if( offset == 1 ) //L线功率增益校正
		{
			Temp32.B08[3] = GPQA;
			Temp32.B08[2] = SelfHeat.gp1[SelfStep-1].B08[1];
			Temp32.B08[1] = SelfHeat.gp1[SelfStep-1].B08[0];
			Temp32.B08[0] = 0;
		}
	}
	
	return(Temp32.B32);
}
#endif	
/**********************************************************/
void Emu_Para_Verify()			//计量芯片UIP系数校验
{
	if(Verify_para( ee_emupara_page, ee_emupara_inpage, Emu_Para.rate[0].B08, ee_emupara_lenth ))
	{
		Emu_Para.rate[0].B32 = METER_Uk+Uoffset;
		Emu_Para.rate[1].B32 = METER_I1k;
		Emu_Para.rate[2].B32 = METER_Pk;
		Emu_Para.rate[3].B32 = METER_I2k;
	}
}
/**********************************************************/
void Emu_Reg_Verify()				//计量芯片寄存器校验
{
	#if( CORRECTION == 1 )	//打开计量误差修正
	unsigned char k;
	#endif
	
	if( Verify_para( ee_7051_page, 0, Att7051_Calib.GP1.B08, ee_7051_lenth ) || (ChkBufZero( Att7051_Calib.GP1.B08, ee_7051_lenth ) == 0) ) //校验错误或者数据全0
	{
		memcpy(Att7051_Calib.GP1.B08, Dl_Cpu_Init, ee_7051_lenth);
	}
	
	#if( CORRECTION == 1 )	//打开计量误差修正
	if( Correction_Mode == 0x55 )
	{
		if( Verify_para( ee_7051adj_page, ee_7051adj_inpage, Cal_Adj[0].B08, ee_7051adj_lenth ) 
			|| (ChkBufZero( Cal_Adj[0].B08, ee_7051adj_lenth+2 ) == 0) ) //crc错误或者数据全0
		{
			for(k=0; k<6; k++)
			{
				Cal_Adj[k].B08[0] = Att7051_Calib.RAPOSA.B08[1];
				Cal_Adj[k].B08[1] = Att7051_Calib.RAPOSA.B08[2];
			}
		}

		if( Verify_para( ee_7051adj_page, ee_7051self_inpage, &SelfHeat.time[0], ee_7051self_len ) 
			|| (ChkBufZero( &SelfHeat.time[0], ee_7051self_len+2 ) == 0) ) //crc错误或者数据全0
		{
			for(k=0; k<heatstep; k++)
			{
				SelfHeat.time[k] = 130;
				SelfHeat.gp1[k].B08[0] = Att7051_Calib.RGPQA.B08[1];
				SelfHeat.gp1[k].B08[1] = Att7051_Calib.RGPQA.B08[2];
			}
		}
	}
	#endif
}
/**********************************************************/
void Backup_Para_7051()			//校表系数备份处理
{
	WriteE2WithBackup( ee_7051_page, 0, Att7051_Calib.GP1.B08, ee_7051_lenth );	//写主和备份数据
	check_7051_flag1 = 1;
}
/**********************************************************/
void Init_Meter_Chip(void)	//初始化计量芯片
{
//	METER_RST0;				//RST=0,计量芯片复位
//	Delay_Initial(4);			//延时20ms
//	METER_RST1;				//RST=1
//	Delay_Initial(4);			//延时20ms

	AT7051_Flag = 0x0f;
	ATT7051_Check();			//校验寄存器
	Read_UIP();				//读瞬时UIP值
	BTIMER1->BTxIF |= 0xFF;;		//防止上电误产生脉冲
	dl_back_flag = 0;			//默认正向电量
	dl_back_flag2 = 0;			//默认反向电量
	dln_back_flag = 0;
	Emu_Data.Iav[0].B32 = 0xffffffff;	//平均电流默认非法
	Emu_Data.Iav[1].B32 = 0xffffffff;	//平均电流默认非法
	Emu_Data.Iav[2].B32 = 0xffffffff;	//平均电流默认非法
}

extern const uint08 ecode Rn8209c_Mode;
/**********************************************************/
void ATT7051_Check(void)		//计量芯片寄存器校验
{
	union B32_B08_2 SPIOpData, Temp32;
	unsigned char i, SPIOpResult, Buf[6];
	unsigned long int *Ptr32;
	
	if(check_7051_flag1)
	{
		Emu_Reg_Verify();		//计量芯片寄存器校验
		Emu_Para_Verify();		//U I P系数校验

		Clear_Wdt();
		
		Ptr32 = &(Att7051_Calib.GP1.B32);
		for(i=0; i<chk_reg_num; i++)			//设置调教寄存器
		{
			if((Ptr32[i] & 0x00ffffff) != 0x00ffffff)
			{
				SPIOpData.B08[3] = Att7051_Calib.GP1.B08[i*4+3];
				SPIOpResult = ATT7051SPIOp(SPIRead,SPIOpData.B08);	//先读取寄存器的值
				if(SPIOpResult) continue;				//失败，不影响后面寄存器的校验
				
			#if( CORRECTION == 1 )	//打开计量误差修正
				if( Correction_Mode == 0x55 ) Temp32.B32 = Calculate_Adj(i);
				else Temp32.B32 = Ptr32[i];
			#else
				Temp32.B32 = Ptr32[i];
			#endif
				if(SPIOpData.B32 != Temp32.B32)
				{
					if( (i==7)&&(SPIOpData.B08[3]==0x00)&&(SPIOpData.B08[1]==0x43) ) continue;
					ATT7051WRPRO(0xe5);			//开写保护
					ATT7051SPIOp(SPIWrite,Temp32.B08);
					ATT7051WRPRO(0xdc);
				}
				
			}
		}
		
		for(i=0; i<4; i++)				//设置调教寄存器(保证0x13~0x16寄存器始终为0)
		{
			SPIOpData.B08[3] = 0x13+i;
			SPIOpResult = ATT7051SPIOp(SPIRead,SPIOpData.B08);
			if(SPIOpResult==0)
			{
				if( SPIOpData.B08[1] || SPIOpData.B08[2] )
				{
					SPIOpData.B08[2] = 0x00;
					SPIOpData.B08[1] = 0x00;
					SPIOpData.B08[0] = 0x00;
					ATT7051WRPRO(0xe5);			//开写保护
					ATT7051SPIOp(SPIWrite,SPIOpData.B08);
					ATT7051WRPRO(0xdc);
				}
			}
		}
		
		check_7051_flag1 = 0;
		
		//温度曲线自热补偿
		if( Rn8209c_Mode != 0x55 ) return;	//非补偿模式，不做校验
			
		SPIOpResult = ReadE2WithBackup( ee_7051_page, ee_8209cself_inpage, Buf, 4 );//返回4+2
		memcpy( Temp32.B08, Buf, 4 );
		if( SPIOpResult || 
			 ( Temp32.B08[3]!=0x51) || 
			 ((Temp32.B08[2]<0x3e) || (Temp32.B08[2]>0x46)) ||
			 ((Temp32.B08[1]<0x40) || (Temp32.B08[1]>0x48)) ) return;
		
		SPIOpData.B08[3] = 0x50;
		SPIOpResult = ATT7051SPIOp(SPIRead,SPIOpData.B08);
		if(SPIOpResult) return;

		SPIOpData.B08[3] = 0x51;
		if(SPIOpData.B32 != Temp32.B32)
		{
			ATT7051WRPRO(0xe5);	//使能写操作
			ATT7051WRPRO(0x02);	//进入TRIM调试模式
			ATT7051WRPRO(0xba);
			ATT7051WRPRO(0x7f);
			ATT7051WRPRO(0x5c);
			
			ATT7051SPIOp(SPIWrite, Temp32.B08);	//修改TRIM值
			
			ATT7051WRPRO(0xdc);	//关闭写操作
		}
	}
}

/**********************************************************/
//取6次平均值
unsigned long int Get_Aver(unsigned char Reg_Addr)
{
	union B32_B08_2 Temp_B32, Temp_B32_1, SPIOpData;
	unsigned char i, Cnt, Num;
	
	if( (Reg_Addr == PowerPA) || (Reg_Addr == PowerPQ) ) Num = 2;
	else Num = 6;
	
	Temp_B32.B32 = 0;
	Cnt = 0;
	for(i=0; i<Num; i++)
	{
		SPIOpData.B08[3] = Reg_Addr;
		ATT7051SPIOp(SPIRead,SPIOpData.B08);
			
		Temp_B32_1.B32 = SPIOpData.B32;	//Temp_B32_1暂存第一次读取的值
		
		SPIOpData.B08[3] = Reg_Addr;
		ATT7051SPIOp(SPIRead,SPIOpData.B08);//再读一次
			
		if(Temp_B32_1.B32 != SPIOpData.B32)//两次读取的不一样,丢掉
		{
			SPIOpData.B32 = 0;
		}
		else if((Reg_Addr == PowerPA) || (Reg_Addr == PowerPQ))
		{
			if(SPIOpData.B08[3] & B1000_0000) //最高位为1做零处理
			{
				SPIOpData.B32 = (~SPIOpData.B32) + 1;
			}
			Cnt++;
		}
		else if(SPIOpData.B08[2] & B1000_0000) //最高位为1做零处理(电流非法)
		{
			SPIOpData.B32 = 0;
		}
		else
		{
			SPIOpData.B08[3] = 0;
			Cnt++;
		}
			
		Temp_B32.B32 += SPIOpData.B32;
		
		Delay_Initial(100);	//延时500ms
	}
	if( Cnt == 0 ) Cnt = 1;
	SPIOpData.B32 = Temp_B32.B32/Cnt;
	
	return (SPIOpData.B32);
}
/**********************************************************/
//计算误差
float Get_Err_Data(unsigned char *Buf, unsigned char CF_f)
{
	union B32_B08_2 K1, K2, K3, SPIOpData;
	unsigned char SPIOpResult, i;
	float Err_Data;
	
	Bcd2Hex_LS(&Buf[8], K3.B08, 4);		//功率	
	
	K2.B32 = 0;
	for(i=0; i<CF_f; i++)
	{
		SPIOpData.B08[3] = PowerPA;
		if((Buf[12]==0x55) && (Buf[13]==0x55)) SPIOpData.B08[3] = PowerPQ;
		SPIOpResult = ATT7051SPIOp(SPIRead,SPIOpData.B08);
		if(SPIOpResult) return (0xff);
			
		if(SPIOpData.B08[3] & B1000_0000)
		{
			SPIOpData.B32 = (~SPIOpData.B32) + 1;
		}
		K2.B32 += SPIOpData.B32;
		
		Delay_Initial(66);	//延时330ms
	}
	SPIOpData.B32 = K2.B32/CF_f;
	Power_Bk = SPIOpData.B32;	//功率备份(小信号校表使用)
	
	K1.B32 = ((float)SPIOpData.B32/Emu_Para.rate[2].B32)*1000000;//计算出实际功率值
	
	Err_Data = ((float)K1.B32 - K3.B32)/K3.B32;	
	return(Err_Data);
}
/**********************************************************/
//电压、电流、功率系数计算
unsigned char UIP_K(unsigned char *Buf)
{
	union B32_B08_2 SPIOpData;
	unsigned char i;
	union B32_B08_2 RegData[3];
	union B32_B08_2 K1[3];
	
	for(i=0; i<3; i++)
	{
		Bcd2Hex_LS(&Buf[i*4], K1[i].B08, 4);
	}
	Read_UIPF( 3, RegData[0].B08 );
	
	Emu_Para.rate[0].B32 = RegData[0].B32*1000/K1[0].B32;		//电压系数
	Emu_Para.rate[1].B32 = RegData[1].B32*1000/K1[1].B32;		//电流A系数

	SPIOpData.B32 = RegData[2].B32*3/1000;			//防潜动阈值 = 0.3%*P
	SPIOpData.B08[3] = PStart;
	SPIOpData.B08[0] = 0;
	Att7051_Calib.GP1.B32 = SPIOpData.B32;
	SPIOpData.B08[3] = DStart;
	Att7051_Calib.RDStart.B32 = SPIOpData.B32;
	
	WriteE2WithBackup( ee_emupara_page, ee_emupara_inpage, Emu_Para.rate[0].B08, ee_emupara_lenth );
	return 0;
}
/**********************************************************/
//零线电流系数(220V,10A,1.0)
unsigned char Ib_K(unsigned char *Buf)
{
	union B32_B08_2 K1;
	union B32_B08_2 SPIOpData;	
	unsigned char SPIOpResult;
	
	Bcd2Hex_LS(&Buf[4], K1.B08, 4);
	
	SPIOpData.B08[3] = IBRMS;
	SPIOpResult = ATT7051SPIOp(SPIRead,SPIOpData.B08);
	if(SPIOpResult) return 1;
	SPIOpData.B08[3] = 0;
	Emu_Para.rate[3].B32 = SPIOpData.B32*1000/K1.B32;		//IB系数
	
	WriteE2WithBackup( ee_emupara_page, ee_emupara_inpage, Emu_Para.rate[0].B08, ee_emupara_lenth );
	return 0;
}
/**********************************************************/
//有效值增益校正(100%Ib,1.0)
unsigned char Gain_Adjust(unsigned char *Buf)
{
	union B32_B08_2 SPIOpData,K1,K2,K3;
	unsigned char SPIOpResult;
	float Err_Data,S1,S2;
	
	SPIOpData.B08[3] = HFConst;		
	SPIOpResult = ATT7051SPIOp(SPIRead,SPIOpData.B08);
	if(SPIOpResult) return 1;
	SPIOpData.B32 = (SPIOpData.B32/256)&0x0000ffff;
	Bcd2Hex_LS( Meter.Const.B08, K1.B08, 4 );//脉冲常数转换成hex
	Emu_Para.rate[2].B32 = (float)SPIOpData.B32*K1.B32*1.3330128;//功率系数
	
	memcpy(K3.B08, &Buf[12], 4);
	if( K3.B32 != 0x99999999 )
	{
		Err_Data = Get_Err_Data(Buf, 3);//计算误差
	}
	else				//合并校表
	{
		//计算1.0有功功率误差
		Bcd2Hex_LS(Buf, K1.B08, 4);	//电压
		Bcd2Hex_LS(Buf+4, K2.B08, 4);	//电流
		K1.B32 = (float)K1.B32*K2.B32/1000;//6位小数的视在功率(理论值)
        	
		S1 = Get_Aver(PowerPA);
		S2 = Get_Aver(PowerPQ);
		
		S2 = S1*S1+S2*S2;	//S^2 = PA^2+PQ^2
		S2 = sqrt(S2);
		
		Err_Data = (S2/Emu_Para.rate[2].B32);
		K2.B32 = Err_Data*1000000.0;//计算出实际功率值
        	
		Err_Data = ((float)K2.B32 - K1.B32)/K1.B32;
	}
	
	Err_Data = -Err_Data/(1+Err_Data);
		
	if(Err_Data >= 0) SPIOpData.B32 = 32768*Err_Data;
	else SPIOpData.B32 = 65536 + 32768*Err_Data;
	
	SPIOpData.B32 = SPIOpData.B32*256;
	SPIOpData.B08[3] = GPQA;
	ATT7051WRPRO(0xe5);		//开写保护
	SPIOpResult = ATT7051SPIOp(SPIWrite,SPIOpData.B08);
	ATT7051WRPRO(0xdc);
	if(SPIOpResult) return 1;
	Att7051_Calib.RGPQA.B32 = SPIOpData.B32;
		
	Delay_Initial(100);	//延时500ms
	Delay_Initial(100);	//延时500ms
		
	UIP_K(Buf);		//电压电流系数校正	
	
	if( K3.B32 == 0x99999999 )	//合并校表
	{
		Att7051_Calib.GP1.B32 = Att7051_Calib.GP1.B32*2;	//启动阀值乘以2
		Att7051_Calib.GP1.B08[3]=PStart;

		Att7051_Calib.RDStart.B32 = Att7051_Calib.GP1.B32;
		Att7051_Calib.RDStart.B08[3]=DStart;
	}
	return 0;	
}

/**********************************************************/
//无功相位校正(100%Ib,0.5L)
unsigned char QPH_Adjust(unsigned char *Buf)
{
	union B32_B08_2 SPIOpData;
	float Err_Data;

	Err_Data = Get_Err_Data(Buf, 3);//计算误差
	
	Err_Data = Err_Data/(1+Err_Data);
	
	if(Err_Data >0)	SPIOpData.B32 = Err_Data*0.5774*32768;
	else	SPIOpData.B32 = 65536 + Err_Data*0.5774*32768;
	
	SPIOpData.B08[3] = QPhsCal;
	SPIOpData.B08[2] = SPIOpData.B08[1];
	SPIOpData.B08[1] = SPIOpData.B08[0];
	SPIOpData.B08[0] = 0;
	Att7051_Calib.RQPhsCal.B32 = SPIOpData.B32;
	
	return 0;
}

/**********************************************************/
//相位校正(100%Ib,0.5L)
unsigned char PH_Adjust(unsigned char *Buf)
{
	union B32_B08_2 SPIOpData;
	float Err_Data;

	Err_Data = Get_Err_Data(Buf, 3);//计算误差
	
	Err_Data = Err_Data/1.732;
	Err_Data = (-Err_Data)*180/3.1416;
	
	SPIOpData.B32 = 512 + Err_Data/0.01;
	if(SPIOpData.B08[0]&0x01)	Att7051_Calib.REMUCON2.B32 = 0x17010000;
	else	Att7051_Calib.REMUCON2.B32 = 0x17000000;
	SPIOpData.B32 = SPIOpData.B32>>1;
	
	SPIOpData.B08[3] = PHSA;
	SPIOpData.B08[2] = SPIOpData.B08[0];
	SPIOpData.B08[1] = 0;
	SPIOpData.B08[0] = 0;
	Att7051_Calib.RPhsA.B32 = SPIOpData.B32;
	
	return 0;
}
/**********************************************************/
//有功功率偏置修正(5%Ib,1.0)
unsigned char Offset_Adjust(unsigned char *Buf)
{
	union B32_B08_2 SPIOpData;
	unsigned char SPIOpResult;
	float Err_Data, K1;

	Err_Data = Get_Err_Data(Buf, 20);
	
	SPIOpData.B08[3] = GPQA;
	SPIOpResult = ATT7051SPIOp(SPIRead,SPIOpData.B08);
	if(SPIOpResult) return 1;
		
	SPIOpData.B32 = (SPIOpData.B32/256)&0x0000ffff;

	if(SPIOpData.B08[1] & B1000_0000)//有功增益系数为负值
	{
		K1 = 1+((float)SPIOpData.B32-65536)/32768;
	}
	else
	{
		K1 = 1+(float)SPIOpData.B32/32768;
	}
	
	K1 = Power_Bk/K1;
			
	if(Err_Data >= 0) 
	{
		SPIOpData.B32 = K1*(Err_Data/(Err_Data+1));
		SPIOpData.B32 = (~SPIOpData.B32) +1;//误差为正
	}
	else SPIOpData.B32 = K1*(-Err_Data/(Err_Data+1));
	
	SPIOpData.B32 = SPIOpData.B32*256;
	
	SPIOpData.B08[3] = APOSA;
	Att7051_Calib.RAPOSA.B32 = SPIOpData.B32;
	return 0;
}
/**********************************************************/
//电流A/B有效值偏置修正(220V,I=0,1.0)
unsigned char IxRMSOS_Adjust(unsigned char CH)
{
	union B32_B08_2 SPIOpData;
	
	if(CH == 1) SPIOpData.B32 = Get_Aver(IARMS);
	else SPIOpData.B32 = Get_Aver(IBRMS);

	SPIOpData.B32 = SPIOpData.B32*SPIOpData.B32;		//平方

	SPIOpData.B32 = ~SPIOpData.B32+1;
	SPIOpData.B08[0] = 0;					//取中间4位

	if(CH == 1)
	{
		SPIOpData.B08[3] = IARMSOS;
		Att7051_Calib.RIARMSOS.B32 = SPIOpData.B32;
	}
	else
	{
		SPIOpData.B08[3] = IBRMSOS;
		Att7051_Calib.RIBRMSOS.B32 = SPIOpData.B32;
	}
	return 0;
}
/**********************************************************/
//校表操作
/**********************************************************/
unsigned char Check_Err_Pro(unsigned char Ch, unsigned char DI0)
{
	unsigned char result, k;
	
	k = 0;
	switch( DI0 )
	{
		case 0x01://初始化
			if((Uart[Ch].Buf[ 9] != 0x07) || (Uart[Ch].Buf[11] != 0xfc)) break; 
			
			memcpy(Att7051_Calib.GP1.B08, Dl_Cpu_Init, chk_reg_num*4);
			Att7051_Calib.RHFConst.B08[2] = Uart[Ch].Buf[14];		//HFConst的值
			Att7051_Calib.RHFConst.B08[1] = Uart[Ch].Buf[13];
			
			#if( CORRECTION == 1 )	//打开计量误差修正
			memset( Cal_Adj[0].B08, 0x00, ee_7051adj_lenth );//误差修正参数清零
			WriteE2WithBackup( ee_7051adj_page, ee_7051adj_inpage, Cal_Adj[0].B08, ee_7051adj_lenth );//带crc写主数据和备份数据
			#endif
			
			k = 1;
			break;
		
		case 0xc0://空载校正(L)
			result = IxRMSOS_Adjust(1);		//电流通道A有效值调整
			if(result) break;
			result = IxRMSOS_Adjust(2);		//电流通道B有效值调整
			if(result) break;
			
			k = 1;
			break;
			
		case 0x11://100%Ib，1.0(L)
			result = Gain_Adjust(Uart[Ch].Buf+11);	//有效值增益校正
			if(result) break;
			
			k = 1;
			break;
			
		case 0x15://100%Ib，0.5L(L)
			if((Uart[Ch].Buf[23]==0x55) && (Uart[Ch].Buf[24]==0x55))
			{
				result = QPH_Adjust(Uart[Ch].Buf+11);	//无功相位校正
			}
			else
			{
				result = PH_Adjust(Uart[Ch].Buf+11);	//有功相位校正
			}
			if(result) break;

			k = 1;
			break;
			
		case 0x16://100%Ib，0.5L(L)
			memset(Uart[Ch].Buf+23, 0x99, 4);	//无功功率默认0x99999999
			result = Gain_Adjust(Uart[Ch].Buf+11);	//有效值增益校正
			if(result) break;
			
			result = PH_Adjust(Uart[Ch].Buf+11);	//相位校正
			if(result) break;

			k = 1;
			break;
			
		case 0x31://5%Ib，1.0(L)
			result = Offset_Adjust(Uart[Ch].Buf+11);//有功功率偏置修正
			if(result) break;
				
			#if( CORRECTION == 1 )	//打开计量误差修正
			for(k=0; k<6; k++)
			{
				Cal_Adj[k].B08[0] = Att7051_Calib.RAPOSA.B08[1];
				Cal_Adj[k].B08[1] = Att7051_Calib.RAPOSA.B08[2];
			}
			WriteE2WithBackup( ee_7051adj_page, ee_7051adj_inpage, Cal_Adj[0].B08, ee_7051adj_lenth );//带crc写主数据和备份数据
			#endif
			
			k = 1;
			break;
		
		case 0x51://100%Ib，1.0(N)
			result = Ib_K(Uart[Ch].Buf+11);		//零线电流系数
			if(result) break;

			k = 1;
			break;
			
		default: break;
	}
	
	if( k == 1 ) 
	{
		#if( CORRECTION == 1 )	//打开计量误差修正
		if( (DI0==0x01) || (DI0==0x11) || (DI0==0x16) )
		{
			for(k=0; k<heatstep; k++)
			{
				SelfHeat.time[k] = 130;
				SelfHeat.gp1[k].B08[0] = Att7051_Calib.RGPQA.B08[1];
				SelfHeat.gp1[k].B08[1] = Att7051_Calib.RGPQA.B08[2];
			}
			WriteE2WithBackup( ee_7051adj_page, ee_7051self_inpage, &SelfHeat.time[0], ee_7051self_len );//带crc写主数据和备份数据
		}
		#endif
		
		Backup_Para_7051();//校表系数备份处理
		return 0;
	}
	else return 1;
}

/**********************************************************/
//通讯读一个寄存器
unsigned char Comm_Read_Reg(unsigned char *Buf)
{
	unsigned char result;
	uint8_t Temp[4];
	memset(Temp,0,4);
	#if( CORRECTION == 1 )	//打开计量误差修正
	if( (Buf[0] >= 0xA1) && (Buf[0] <= 0xA6))
	{       
		Exchange(&Buf[1], Cal_Adj[Buf[0]-0xA1].B08, 2);
		Buf[3] = 0x00;
		return 0;
	}

	if( (Buf[0] >= 0xB1) && (Buf[0] < 0xB1+heatstep) )
	{
		Buf[1] = SelfHeat.time[Buf[0]-0xB1];
		Exchange(&Buf[2], SelfHeat.gp1[Buf[0]-0xB1].B08, 2);
		return 0;
	}
	#endif
	
	if( (Buf[0] == PowerPA) || (Buf[0] == PowerPB) || (Buf[0] == PowerPQ)) 
	{
		Temp[3]=Buf[0];
		result = ATT7051SPIOp(SPIRead, Temp);
		if(result) return 1;
		Exchange( Buf+1,Temp, 4 );
	}
	else
	{
		Temp[3] = *Buf;
		result = ATT7051SPIOp(SPIRead, Temp);
		if(result) return 1;
		Exchange( Buf,Temp, 4 );
	}

	return 0;
}
//通讯写一个寄存器
unsigned char Comm_Write_Reg(unsigned char *Buf)
{
	unsigned char i;
	uint8_t temp[4];
	memset(temp,0,4);
	if(Buf[0] == 0xff)	//校表初始化操作
	{
		memcpy(Att7051_Calib.GP1.B08, Dl_Cpu_Init, chk_reg_num*4);
		Backup_Para_7051();//校表系数备份处理
		
		#if( CORRECTION == 1 )	//打开计量误差修正
		memset( Cal_Adj[0].B08, 0x00, ee_7051adj_lenth );//误差修正参数清零
		WriteE2WithBackup( ee_7051adj_page, ee_7051adj_inpage, Cal_Adj[0].B08, ee_7051adj_lenth );//带crc写主数据和备份数据

		for(i=0; i<heatstep; i++)
		{
			SelfHeat.time[i] = 130;
			SelfHeat.gp1[i].B08[0] = Att7051_Calib.RGPQA.B08[1];
			SelfHeat.gp1[i].B08[1] = Att7051_Calib.RGPQA.B08[2];
		}
		WriteE2WithBackup( ee_7051adj_page, ee_7051self_inpage, &SelfHeat.time[0], ee_7051self_len );
		#endif
	}
	else			//写寄存器操作
	{
		for(i=0; i<chk_reg_num; i++)
		{
			if(Buf[0] == Dl_Cpu_Init[i].B08[3]) 
			{
				Exchange( &(Att7051_Calib.GP1.B08[i*4]), Buf, 4 );
				Backup_Para_7051();
				return 0;
			}
		}
		
		#if( CORRECTION == 1 )	//打开计量误差修正	
		if((Buf[0] >= 0xA1) && (Buf[0] <= 0xA6))	//写补偿寄存器的值
		{
			Exchange( Cal_Adj[0].B08+(Buf[0]-0xA1)*2, Buf+1, 2 );
			WriteE2WithBackup( ee_7051adj_page, ee_7051adj_inpage, Cal_Adj[0].B08, ee_7051adj_lenth );//带crc写主数据和备份数据
			
			check_7051_flag1 = 1;
			return 0;
		}
		
		if( (Buf[0] >= 0xB1) && (Buf[0] < 0xB1+heatstep) )
		{
			SelfHeat.time[Buf[0]-0xB1] = Buf[1];
			Exchange( SelfHeat.gp1[Buf[0]-0xB1].B08, Buf+2, 2 );
			WriteE2WithBackup( ee_7051adj_page, ee_7051self_inpage, &SelfHeat.time[0], ee_7051self_len );

			check_7051_flag1 = 1;
			return 0;
		}
		#endif
		
		if( (Rn8209c_Mode == 0x55) && (Buf[0]==0x51) )
		{
			Inverse(Buf, 4);
			WriteE2WithBackup( ee_7051_page, ee_8209cself_inpage, Buf, 4 );
			
			check_7051_flag1 = 1;
			return 0;
		}
		
		Exchange(temp,Buf,4);
		ATT7051WRPRO(0xe5);
		ATT7051SPIOp(SPIWrite, temp);	//其它50H以后寄存器可写，但不保存到EE
		ATT7051WRPRO(0xdc);
	}
	return 0;
}


/**********************************************************/
