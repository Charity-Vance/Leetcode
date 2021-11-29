
///*****************************************************************************************///
///*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     
///*Version:       V1
///*Date:          2014-3-12
///*Description:   
///*Function List: 
///*****************************************************************************************///
#ifndef	__LCDDrive_H
#define	__LCDDrive_H


#include "Public.h"
#include "IO.h"
#include "Timer.h"




//static ulong32	SV_LCD_SFRBuff;	///*该变量用于所有寄存器的读->修改->写*///
#define	C_StartTime_3s			6		///*500ms基准*///
#define	C_FixTime_500ms			1		///*500ms基准*///

#define	C_LCD_MostSignificantBit			0x80		///*最高有效位*///
#define C_LCD_Max_StopTimes					20			///*发stop时最多次数*///
#define	C_LCD_BitLen						8			///*I2C传输数据的数据长度：1字节*///
#define	C_LCD_DataLen						35			///*每片LCD驱动的RAM长度*///
#define	C_LCD_Data_Zero						0x00		///*数据区填“00”*///
#define	C_LCD_Data_Full						0xff		///*数据区填“ff”*///
#define C_LCD_DataTruthTableLen				16			///*真值表长度*///
#define C_LCD_BuffAddrLen					20			///*20个数字对应的缓冲区偏移地址表格长度*///
#define C_LCD_BuffAddrLen2					5			//增加的数据缓存区域
///*以下是HT16C22的宏定义*///
#define	C_LCD_HT16C22_SlaveAddr_Write		0x7e		///*写LCD的从地址*///
#define	C_LCD_HT16C22_SlaveAddr_Read		0x7f		///*读LCD的从地址*///

#define	C_LCD_HT16C22_CMD_Mode_On			0x9c		///*LCD驱动工作*///
#define	C_LCD_HT16C22_CMD_Mode_Off			0x80		///*LCD驱动停止工作*///

#define	C_LCD_HT16C22_CMD_BlinkingOff		0xc0		///*blinking off*///

#define	C_LCD_HT16C22_CMD_IVA				0x70		///*LCD驱动工作*///
#define	C_LCD_HT16C22_DataStartAddr			0x00		///*LCD数据起始地址*///

///*以下是BU9792的宏定义*///
#define	C_LCD_BU9792_SlaveAddr_Write		0x7c		///*写LCD的从地址*///
#define	C_LCD_BU9792_SlaveAddr_Read			0x7d

#define	C_LCD_BU9792_CMD_ICSet_RESETOff		0xF6		///*LCD驱动软件复位，显示关闭*///
#define	C_LCD_BU9792_CMD_ICSet_ModeOn			0xF5		///*LCD驱动工作，显示打开*///

#define	C_LCD_BU9792_CMD_EVRSET						0xc1		///*The relationship of electrical volume register (EVR) setting and V0 voltage 4.839V
//#define	C_LCD_BU9792_CMD_Blink				0xf0		///*LCD驱动blink设置*///
#define	C_LCD_BU9792_CMD_APCTL						0xf8		///*LCD驱动亮点设置*///
#define	C_LCD_BU9792_CMD_LCDON						0xF5		///*LCD驱动工作*///
#define	C_LCD_BU9792_CMD_LCDOFF						0xF4		///*LCD驱动停止*///
#define	C_LCD_BU9792_DataStartAddr				0x00		///*LCD数据起始地址*///
#define	C_LCD_BU9792_CMD_DISCTL						0xe6		///*LCD刷新频率及工作模式*///
#define	C_LCD_BU9792_CMD_REG2							0xa4		///*LCD工作状态寄存器*///
#define	C_LCD_BU9792_CheckData						0x6c		///*注意：寄存器0x24固定校验值，该值与上述寄存器设置有关系。设置不同，该值也不同。		

#define	C_DotNumber							95		///*辅助字符Dot数量*///
#define	C_Column							0x04		///*列数量*///
///*传入的数据缓冲区,对应虚拟缓存*///
///*偏移地址*///
///*地址的位地址*///
/////////////////////////////////////
#define C_DataBuff_DP10		10						///*	DP10	*///
#define C_DataBit_DP10		0x80
#define C_DataBuff_DP11		10						///*	DP11	*///
#define C_DataBit_DP11		0x40
#define C_DataBuff_DP12		10						///*	DP12	*///
#define C_DataBit_DP12		0x20
#define C_DataBuff_Q		10						///*	Q	*///
#define C_DataBit_Q			0x10
/////////////////////////////////////

///*象限传入的是象限号*///
#define C_DataBuff_Q4			10						///*	Q4	*///
#define C_DataBit_Q4			0x08
//#define C_DataBit_Q4			0x04
#define C_DataBuff_Q3			10						///*	Q3	*///
#define C_DataBit_Q3			0x04
//#define C_DataBit_Q3			0x03
#define C_DataBuff_Q2			10						///*	Q2	*///
#define C_DataBit_Q2			0x02
#define C_DataBuff_Q1			10						///*	Q1	*///
#define C_DataBit_Q1			0x01
/////////////////////////////////////
#define C_DataBuff_S56			11					    ///*	S56	*///
#define C_DataBit_S56			0x80
#define C_DataBuff_S67			11					    ///*	S67	*///
#define C_DataBit_S67			0x40

/////////////////////////////////////
#define C_DataBuff_S80			12						///*	S80	*///
#define C_DataBit_S80			0x80
#define C_DataBuff_S81			12						///*	S81	*///
#define C_DataBit_S81			0x40
#define C_DataBuff_S82			12						///*	S82	*///
#define C_DataBit_S82			0x20
#define C_DataBuff_S83			12						///*	S83	*///
#define C_DataBit_S83			0x10
#define C_DataBuff_S79			12						///*	S79	*///
#define C_DataBit_S79			0x08
#define C_DataBuff_S84			12						///*	S84	*///
#define C_DataBit_S84			0x04
#define C_DataBuff_S85			12						///*	S85	*///
#define C_DataBit_S85			0x02
#define C_DataBuff_S86			12						///*	S86	*///
#define C_DataBit_S86			0x01
/////////////////////////////////////
#define C_DataBuff_S87			13						///*	S87	*///
#define C_DataBit_S87			0x80
#define C_DataBuff_S88			13						///*	S88	*///
#define C_DataBit_S88			0x40
#define C_DataBuff_S89			13						//*		S89 *///
#define C_DataBit_S89			0x20
#define C_DataBuff_S90			13						///*	S90 *///
#define C_DataBit_S90			0x10
#define C_DataBuff_S91			13						///*	S91	*///
#define C_DataBit_S91			0x08
#define C_DataBuff_S95			13						///*	S95	*///
#define C_DataBit_S95			0x01
/////////////////////////////////////
#define C_DataBuff_S96			14						///*	S96
#define C_DataBit_S96			0x80
#define C_DataBuff_S97			14						///*	S97	
#define C_DataBit_S97			0x40
#define C_DataBuff_S98			14						///*	S98
#define C_DataBit_S98			0x10
#define C_DataBuff_S76			14						///*	S76	
#define C_DataBit_S76			0x08
#define C_DataBuff_S77			14						///*	S77
#define C_DataBit_S77			0x04
#define C_DataBuff_S92			14						///*	S92
#define C_DataBit_S92			0x02
#define C_DataBuff_S93			14						///*	S93
#define C_DataBit_S93			0x01
/////////////////////////////////////
#define C_DataBuff_S64			15						///*	S64	*///
#define C_DataBit_S64			0x80
#define C_DataBuff_S65			15						///*	S65	*///
#define C_DataBit_S65			0x40
#define C_DataBuff_S66			15						///*	S66	*///
#define C_DataBit_S66			0x20
#define C_DataBuff_S94			15						///*	S94	*///
#define C_DataBit_S94			0x10
#define C_DataBuff_S68			15						///*	S68	*///
#define C_DataBit_S68			0x08
#define C_DataBuff_S69			15						///*	S69	*///
#define C_DataBit_S69			0x04
#define C_DataBuff_S70			15						///*	S70	*///
#define C_DataBit_S70			0x02
#define C_DataBuff_S71			15						///*	S71	*///
#define C_DataBit_S71			0x01
/////////////////////////////////////
#define C_DataBuff_S72			16						///*	S72	*///
#define C_DataBit_S72			0x80
#define C_DataBuff_S73			16						///*	S73	*///
#define C_DataBit_S73			0x40
/////////////////////////////////////
#define C_DataBuff_S6			17						///*	S6	*///
#define C_DataBit_S6			0x80
#define C_DataBuff_S7			17						///*	S7	*///
#define C_DataBit_S7			0x40
#define C_DataBuff_S9			17						///*	S9	*///
#define C_DataBit_S9			0x20
#define C_DataBuff_S10			17						///*	S10	*///
#define C_DataBit_S10			0x10
#define C_DataBuff_S11			17						///*	S11	*///
#define C_DataBit_S11			0x08
#define C_DataBuff_S12			17						///*	S12	*///
#define C_DataBit_S12			0x04
#define C_DataBuff_S13			17						///*	S13	*///
#define C_DataBit_S13			0x02
#define C_DataBuff_S14			17						///*	S14	*///
#define C_DataBit_S14			0x01
/////////////////////////////////////
#define C_DataBuff_S15			18						///*	S15	*///
#define C_DataBit_S15			0x80
#define C_DataBuff_S16			18						///*	S16	*///
#define C_DataBit_S16			0x40
#define C_DataBuff_S20			18						///*	S20	*///
#define C_DataBit_S20			0x20
#define C_DataBuff_S21			18						///*	S21	*///
#define C_DataBit_S21			0x10
#define C_DataBuff_S22			18						///*	S22	*///
#define C_DataBit_S22			0x08
/////////////////////////////////////
#define C_DataBuff_S29			19						///*	S29	*///
#define C_DataBit_S29			0x80
#define C_DataBuff_S30			19						///*	S30	*///
#define C_DataBit_S30			0x40
#define C_DataBuff_S31			19						///*	S31	*///
#define C_DataBit_S31			0x20
#define C_DataBuff_S32			19						///*	S32	*///
#define C_DataBit_S32			0x10
#define C_DataBuff_S33			19						///*	S33	*///
#define C_DataBit_S33			0x08
#define C_DataBuff_S34			19						///*	S34	*///
#define C_DataBit_S34			0x04
#define C_DataBuff_S35			19						///*	S35	*///
#define C_DataBit_S35			0x02
#define C_DataBuff_S36			19						///*	S36	*///
#define C_DataBit_S36			0x01
/////////////////////////////////////
#define C_DataBuff_S37			20						///*	S37	*///
#define C_DataBit_S37			0x80
#define C_DataBuff_S38			20						///*	S38	*///
#define C_DataBit_S38			0x40
#define C_DataBuff_S39			20						///*	S39	*///
#define C_DataBit_S39			0x20
#define C_DataBuff_S40			20						///*	S40	*///
#define C_DataBit_S40			0x10
#define C_DataBuff_S41			20						///*	S41	*///
#define C_DataBit_S41			0x08
#define C_DataBuff_S42			20						///*	S42	*///
#define C_DataBit_S42			0x04
#define C_DataBuff_S43			20						///*	S43	*///
#define C_DataBit_S43			0x02
#define C_DataBuff_S44			20						///*	S44	*///
#define C_DataBit_S44			0x01
/////////////////////////////////////
#define C_DataBuff_S45			21						///*	S45	*///
#define C_DataBit_S45			0x80
#define C_DataBuff_S46			21						///*	S46	*///
#define C_DataBit_S46			0x40
#define C_DataBuff_S47			21						///*	S47	*///
#define C_DataBit_S47			0x20
#define C_DataBuff_S48			21						///*	S48	*///
#define C_DataBit_S48			0x10

#define C_DataBuff_S18			21					    ///*	S18	*///
#define C_DataBit_S18			0x08
#define C_DataBuff_S17			21					    ///*	S17	*///
#define C_DataBit_S17			0x04
#define C_DataBuff_S19			21					    ///*	S19	*///
#define C_DataBit_S19			0x01
/////////////////////////////////////
#define C_DataBuff_S74			22						///*	S74	*///
#define C_DataBit_S74			0x80
#define C_DataBuff_S75			22						///*	S75	*///
#define C_DataBit_S75			0x40
#define C_DataBuff_S53			22						///*	S53	*///
#define C_DataBit_S53			0x20
#define C_DataBuff_S57			22						///*	S57	*///
#define C_DataBit_S57			0x04
#define C_DataBuff_DP8			22						///*	DP8	*///
#define C_DataBit_DP8			0x01
/////////////////////////////////////
#define C_DataBuff_S58			23						///*	S58 *///
#define C_DataBit_S58			0x80
#define C_DataBuff_S59			23						///*	S59	*///
#define C_DataBit_S59			0x20
#define C_DataBuff_S61			23						///*	S61	*///
#define C_DataBit_S61			0x10
#define C_DataBuff_S60			23						///*	S60	*///
#define C_DataBit_S60			0x08
#define C_DataBuff_S62			23						///*	S62	*///
#define C_DataBit_S62			0x04
#define C_DataBuff_S63			23						///*	S63	*///
#define C_DataBit_S63			0x01
/////////////////////////////////////
#define C_DataBuff_DP1			24						///*	DP1	*///
#define C_DataBit_DP1			0x40
#define C_DataBuff_DP2			24						///*	DP2	*///
#define C_DataBit_DP2			0x20
#define C_DataBuff_DP5			24						///*	DP5	*///
#define C_DataBit_DP5			0x10
#define C_DataBuff_DP3			24					    ///*	DP3	*///
#define C_DataBit_DP3			0x08
#define C_DataBuff_DP4			24						///*	DP4 COL1*///
#define C_DataBit_DP4			0x04
#define C_DataBuff_DP6			24						///*	DP6		*///
#define C_DataBit_DP6			0x02
#define C_DataBuff_DP7			24						///*	DP7		*///
#define C_DataBit_DP7			0x01
/////////////////////////////////////

///*显示的缓冲区,显示驱动芯片buff，对应液晶真值表*///
///*偏移地址*///
///*地址的位地址*///
//////////////////////////////////////
#define C_DispBuff_DP10			3						///*	DP10 *///
#define C_DispBit_DP10          0x01
#define C_DispBuff_DP11			7						///*	DP11 *///
#define C_DispBit_DP11			0x01                               
#define C_DispBuff_DP12			11						///*	DP12 *///
#define C_DispBit_DP12			0x01
                                
#define C_DispBuff_Q			33                      ///*	Q	 *///
#define C_DispBit_Q				0x20
//////////////////////////////////////
#define C_DispBuff_Q4			33						///*	Q4	*///
#define C_DispBit_Q4			0x10                                  
#define C_DispBuff_Q3			34						///*	Q3	*///
#define C_DispBit_Q3			0x20                                    
#define C_DispBuff_Q2			34						///*	Q2	*///
#define C_DispBit_Q2			0x40                                    
#define C_DispBuff_Q1			33						///*	Q1	*///
#define C_DispBit_Q1			0x40                                   
/////////////////////////////////////
#define C_DispBuff_S56			11						///*	S56	*///
#define C_DispBit_S56			0x10                                      
#define C_DispBuff_S67			8						///*	S67	*///
#define C_DispBit_S67			0x40 

/////////////////////////////////////
#define C_DispBuff_S80			6						///*	S80	*///
#define C_DispBit_S80			0x10                                    
#define C_DispBuff_S81			6						///*	S81	*///
#define C_DispBit_S81			0x20                                    
#define C_DispBuff_S82			6						///*	S82	*///
#define C_DispBit_S82			0x40                                    
#define C_DispBuff_S83			6						///*	S83	*///
#define C_DispBit_S83			0x80                                   
#define C_DispBuff_S79			5						///*	S79	*///
#define C_DispBit_S79			0x01                                    
#define C_DispBuff_S84			7						///*	S84	*///
#define C_DispBit_S84			0x80                                    
#define C_DispBuff_S85			7						///*	S85	*///
#define C_DispBit_S85			0x40                                    
#define C_DispBuff_S86			7						///*	S86	*///
#define C_DispBit_S86			0x20                                    
/////////////////////////////////////
#define C_DispBuff_S87			7						///*	S87	*///
#define C_DispBit_S87			0x10                                    
#define C_DispBuff_S88			15						///*	S88	*///
#define C_DispBit_S88			0x01                                    
#define C_DispBuff_S89			15						//*		S89 *///
#define C_DispBit_S89			0x10                                    
#define C_DispBuff_S90			15						///*	S90 *///
#define C_DispBit_S90			0x20                                    
#define C_DispBuff_S91			15						///*	S91	*///
#define C_DispBit_S91			0x40                                    
#define C_DispBuff_S95			11						///*	S95	*///
#define C_DispBit_S95			0x80                                    
/////////////////////////////////////
#define C_DispBuff_S96			11						///*	S96
#define C_DispBit_S96			0x40                                    
#define C_DispBuff_S97			11						///*	S97	
#define C_DispBit_S97			0x20                                    
#define C_DispBuff_S98			9						///*	S98
#define C_DispBit_S98			0x80                                    
#define C_DispBuff_S76			8						///*	S76	
#define C_DispBit_S76			0x10                                    
#define C_DispBuff_S77			8						///*	S77
#define C_DispBit_S77			0x20                                    
#define C_DispBuff_S92			15						///*	S92
#define C_DispBit_S92			0x80                                    
#define C_DispBuff_S93			13						///*	S93
#define C_DispBit_S93			0x80                                    
/////////////////////////////////////
#define C_DispBuff_S64			14						///*	S64	*///
#define C_DispBit_S64			0x80                                    
#define C_DispBuff_S65			14						///*	S65	*///
#define C_DispBit_S65			0x40                                  
#define C_DispBuff_S66			14						///*	S66	*///
#define C_DispBit_S66			0x20                                    
#define C_DispBuff_S94			13						///*	S94	*///
#define C_DispBit_S94			0x01                                   
#define C_DispBuff_S68			14						///*	S68	*///
#define C_DispBit_S68			0x10                                    
#define C_DispBuff_S69			13						///*	S69	*///
#define C_DispBit_S69			0x10                                    
#define C_DispBuff_S70			13						///*	S70	*///
#define C_DispBit_S70			0x20                                    
#define C_DispBuff_S71			13						///*	S71	*///
#define C_DispBit_S71			0x40                                    
/////////////////////////////////////
#define C_DispBuff_S72			12						///*	S72	*///
#define C_DispBit_S72			0x80                                    
#define C_DispBuff_S73			12						///*	S73	*///
#define C_DispBit_S73			0x40                                    
/////////////////////////////////////
#define C_DispBuff_S6			32						///*	S6	*//
#define C_DispBit_S6			0x80                                    
#define C_DispBuff_S7			32						///*	S7	*///
#define C_DispBit_S7			0x40                                    
#define C_DispBuff_S9			29						///*	S9	*///
#define C_DispBit_S9			0x40                                    
#define C_DispBuff_S10			29						///*	S10	*///
#define C_DispBit_S10			0x80                                    
#define C_DispBuff_S11			28						///*	S11	*///
#define C_DispBit_S11			0x80                                    
#define C_DispBuff_S12			28						///*	S12	*///
#define C_DispBit_S12			0x40                                    
#define C_DispBuff_S13			27						///*	S13	*///
#define C_DispBit_S13			0x40                                    
#define C_DispBuff_S14			27						///*	S14	*///
#define C_DispBit_S14			0x80                                  
/////////////////////////////////////
#define C_DispBuff_S15			26						///*	S15	*///
#define C_DispBit_S15			0x80                                    
#define C_DispBuff_S16			26						///*	S16	*///
#define C_DispBit_S16			0x40                                    
#define C_DispBuff_S20			24						///*	S20	*///
#define C_DispBit_S20			0x40                                    
#define C_DispBuff_S21			23						///*	S21	*///
#define C_DispBit_S21			0x40                                    
#define C_DispBuff_S22			23						///*	S22	*///
#define C_DispBit_S22			0x80                                    
/////////////////////////////////////
#define C_DispBuff_S29			32						///*	S29	*///
#define C_DispBit_S29			0x20                                   
#define C_DispBuff_S30			32						///*	S30	*///
#define C_DispBit_S30			0x10                                    
#define C_DispBuff_S31			29						///*	S31	*///
#define C_DispBit_S31			0x10                                                                      
#define C_DispBuff_S32			29						///*	S32	*///
#define C_DispBit_S32			0x20                                    
#define C_DispBuff_S33			28						///*	S33	*///
#define C_DispBit_S33			0x20                                    
#define C_DispBuff_S34			28						///*	S34	*///
#define C_DispBit_S34			0x10                                    
#define C_DispBuff_S35			27						///*	S35	*///
#define C_DispBit_S35			0x10                                    
#define C_DispBuff_S36			27						///*	S36	*///
#define C_DispBit_S36			0x20                                   
/////////////////////////////////////
#define C_DispBuff_S37			26						///*	S37	*///
#define C_DispBit_S37			0x20
#define C_DispBuff_S38			25						///*	S38	*///
#define C_DispBit_S38			0x10
#define C_DispBuff_S39			25						///*	S39	*///
#define C_DispBit_S39			0x20
#define C_DispBuff_S40			24						///*	S40	*///
#define C_DispBit_S40			0x20 
#define C_DispBuff_S41			24						///*	S41	*///
#define C_DispBit_S41			0x10                                    
#define C_DispBuff_S42			23						///*	S42	*///
#define C_DispBit_S42			0x10                                                                       
#define C_DispBuff_S43		23						///*	S43	*///
#define C_DispBit_S43			0x20                                    
#define C_DispBuff_S44		22						///*	S44	*///
#define C_DispBit_S44			0x20
                                    
/////////////////////////////////////
#define C_DispBuff_S45		22						///*	S45	*///
#define C_DispBit_S45			0x10                                    
#define C_DispBuff_S46		21						///*	S46	*///
#define C_DispBit_S46			0x10                                    
#define C_DispBuff_S47		21						///*	S47	*///
#define C_DispBit_S47			0x20                                    
#define C_DispBuff_S48		21						///*	S48	*///
#define C_DispBit_S48			0x40              

#define C_DispBuff_S17			25						///*	S17	*///
#define C_DispBit_S17			0x40                                      
#define C_DispBuff_S18			25						///*	S18	*///
#define C_DispBit_S18			0x80 
#define C_DispBuff_S19			24						///*	S19	*///
#define C_DispBit_S19			0x80 
/////////////////////////////////////
#define C_DispBuff_S74		12						///*	S74	*///
#define C_DispBit_S74			0x10                                    
#define C_DispBuff_S75		12						///*	S75	*///
#define C_DispBit_S75			0x20                                    
#define C_DispBuff_S53		34						///*	S53	*///
#define C_DispBit_S53			0x10                                    
#define C_DispBuff_S57		18						///*	S57	*///
#define C_DispBit_S57			0x10                                    
#define C_DispBuff_DP8		19						///*	DP8	*///
#define C_DispBit_DP8			0x01                                    
/////////////////////////////////////
#define C_DispBuff_S58		18						///*	S58 *///
#define C_DispBit_S58			0x04                                    
#define C_DispBuff_S59		18						///*	S59	*///
#define C_DispBit_S59			0x08                                    
#define C_DispBuff_S61		18						///*	S61	*///
#define C_DispBit_S61			0x40                                    
#define C_DispBuff_S60		18						///*	S60	*///
#define C_DispBit_S60			0x20                                    
#define C_DispBuff_S62		18						///*	S62	*///
#define C_DispBit_S62			0x01                                    
#define C_DispBuff_S63		18						///*	S63	*///
#define C_DispBit_S63			0x02                                    
/////////////////////////////////////
#define C_DispBuff_DP1		29						///*	DP1	*///
#define C_DispBit_DP1			0x01                                    
#define C_DispBuff_DP2		27						///*	DP2	*///
#define C_DispBit_DP2			0x01                                
#define C_DispBuff_DP5		23						///*	DP5	*///
#define C_DispBit_DP5			0x01 
#define C_DispBuff_DP3		25					    ///*	DP3	*///
#define C_DispBit_DP3			0x01                                                                       
#define C_DispBuff_DP4		31						///*	DP4 COL1*///
#define C_DispBit_DP4			0x01                                    
#define C_DispBuff_DP6		21						///*	DP6		*///
#define C_DispBit_DP6			0x01                                    
#define C_DispBuff_DP7		33						///*	DP7		*///
#define C_DispBit_DP7			0x01                                    
/////////////////////////////////////
#define C_DispData3ABC_Addr	    1						///* 数字3的对应真值表地址
#define C_DispData3DEGF_Addr	0               
#define C_DispData3KillZero		0xF1

#define C_DispData4ABC_Addr		33						///* 数字4的对应真值表地址
#define C_DispData4DEGF_Addr	34	
#define C_DispData4KillZero		0xF1

#define C_DispData5ABC_Addr		31						///* 数字5的对应真值表地址
#define C_DispData5DEGF_Addr	32
#define C_DispData5KillZero		0xF1

#define C_DispData6ABC_Addr		29						///* 数字6的对应真值表地址
#define C_DispData6DEGF_Addr	30	
#define C_DispData6KillZero		0xF1

#define C_DispData7ABC_Addr		27						///* 数字7对应真值表地址
#define C_DispData7DEGF_Addr	28
#define C_DispData7KillZero		0xF1

#define C_DispData8ABC_Addr		25						///* 数字8对应真值表地址
#define C_DispData8DEGF_Addr	26
#define C_DispData8KillZero	    0xF1

#define C_DispData9ABC_Addr		23						///* 数字9对应真值表地址
#define C_DispData9DEGF_Addr	24
#define C_DispData9KillZero		0xF1

#define C_DispData10ABC_Addr	21						///* 数字10对应真值表地址
#define C_DispData10DEGF_Addr	22
#define C_DispData10KillZero    0xF1

#define C_DispData11ABC_Addr	19						///* 数字11对应真值表地址
#define C_DispData11DEGF_Addr	20
#define C_DispData11KillZero	0xF1

#define C_DispData12ABC_Addr	17						///* 数字12对应真值表地址
#define C_DispData12DEGF_Addr	16
#define C_DispData12KillZero	0xF1

#define C_DispData13ABC_Addr	1						///* 数字13对应真值表地址
#define C_DispData13DEGF_Addr	0
#define C_DispData13KillZero	0x8F

#define C_DispData14ABC_Addr	3						///* 数字14对应真值表地址
#define C_DispData14DEGF_Addr	2
#define C_DispData14KillZero	0xF1

#define C_DispData15ABC_Addr	5						///* 数字15对应真值表地址
#define C_DispData15DEGF_Addr	4
#define C_DispData15KillZero	0xF1

#define C_DispData16ABC_Addr	7						///* 数字16对应真值表地址
#define C_DispData16DEGF_Addr	6
#define C_DispData16KillZero	0xF1

#define C_DispData17ABC_Addr	9						///* 数字17对应真值表地址
#define C_DispData17DEGF_Addr	8
#define C_DispData17KillZero	0xF1

#define C_DispData18ABC_Addr	11						///* 数字18对应真值表地址
#define C_DispData18DEGF_Addr	10
#define C_DispData18KillZero	0xF1

#define C_DispData19ABC_Addr	13						///* 数字19对应真值表地址
#define C_DispData19DEGF_Addr	12
#define C_DispData19KillZero	0xF1

#define C_DispData20ABC_Addr	15						///* 数字20对应真值表地址
#define C_DispData20DEGF_Addr	14
#define C_DispData20KillZero	0xF1

#define C_DispData23ABC_Addr	3						///* 数字23对应真值表地址
#define C_DispData23DEGF_Addr	2
#define C_DispData23KillZero	0x8F

#define C_DispData24ABC_Addr	5						///* 数字24对应真值表地址
#define C_DispData24DEGF_Addr	4
#define C_DispData24KillZero	0x8F
////////////////////////////////////// 



#define	C_KillZeroTotalNumber	   20				   ///* 插卡动态显示时灭零数字最多达到20个	*///
#define	C_Column_KillZero		   3
#define	C_KillZeroNumberNoCardIn   9                   ///* 不插卡条件下灭零最多9个，正常循显、键显只将主显示区的数字灭零 *///

//#define	C_KillZeroNumber		9						///* 灭零的最多个数：7个	*///


#define C_DispBuff_1P			30						///*	1P	*///
#define C_DispBit_1P			0x10
#define C_DispBuff_1ABC         30
#define C_DispBuff_1DEGF        31 

#define C_DispBuff_2P			21						///*	2P	*///
#define C_DispBit_2P			0x80
#define C_DispBuff_2ABC         19
#define C_DispBuff_2DEGF        20 

#define C_DispBuff_21ABC        9                     //21ABC
#define C_DispBuff_21DEGF       10                     //21DEGF

#define C_DispBuff_22P			8						///*	22P	*///
#define C_DispBit_22P			0x80
#define C_DispBuff_22ABC        17
#define C_DispBuff_22DEGF       16 

#define	C_Special_Number_Len	1						///*需要处理的特殊数字的个数*///
#define C_DispNumber1Buff		29						///*数字1高低4位需要颠倒，所在的缓冲区偏移地址*///

//#define C_Special_Number_Len	4					///*需要处理的特殊数字的个数*///
//#define C_DispNumber1Buff		31						///*数字1高低4位需要颠倒，所在的缓冲区偏移地址*///
//#define C_DispNumber2Buff		19						///*数字1高低4位需要颠倒，所在的缓冲区偏移地址*///
//#define C_DispNumber21Buff	9						///*数字1高低4位需要颠倒，所在的缓冲区偏移地址*///
//#define C_DispNumber22Buff	17						///*数字1高低4位需要颠倒，所在的缓冲区偏移地址*///

///*io 口线操作的宏定义*///
///*****************************************************************************************///
///*下半部分LCD驱动*///
///*******************************************************************///
#define LCD_IO_Init				{IO_LCDSCL->MODER &= LCDSCL_IN_MODE;\
								IO_LCDSCL->INEN |= LCDSCL_INOn;\
							IO_LCDSDA->MODER &= LCDSDA_IN_MODE;\
							IO_LCDSDA->INEN |= LCDSDA_INOn;}
								
#define LCD_Set_Scl_Input		{IO_LCDSCL->MODER &= LCDSCL_IN_MODE;\
								IO_LCDSCL->INEN |= LCDSCL_INOn;\
								IO_LCDSCL->PUPDR &= LCDSCL_NOPUPD;}

#define LCD_Set_Scl_Output		{ulong32 SV_LCD_SFRBuff;\
								SV_LCD_SFRBuff = IO_LCDSCL->MODER;\
								SV_LCD_SFRBuff &= LCDSCL_IN_MODE;\
								SV_LCD_SFRBuff |= LCDSCL_OUT_MODE;\
								IO_LCDSCL->MODER = SV_LCD_SFRBuff;\
								IO_LCDSCL->OTYPER |= LCDSCL_OUTPUT_OD;}

#define LCD_Scl_Output_0		{IO_LCDSCL->BSRR = LCDSCLRESET;}

#define LCD_Scl_Output_1		{IO_LCDSCL->BSETH = LCDSCLSET;}
///*******************************************************************///
#define LCD_Set_Sda_Input		{IO_LCDSDA->MODER &= LCDSDA_IN_MODE;\
								IO_LCDSDA->INEN |= LCDSDA_INOn;\
								IO_LCDSDA->PUPDR &= LCDSDA_NOPUPD;}

#define LCD_Set_Sda_Output		{IO_LCDSDA->MODER |= LCDSDA_OUT_MODE;\
								IO_LCDSDA->OTYPER |= LCDSDA_OUTPUT_OD;}

#define LCD_Sda_Output_0		{IO_LCDSDA->BSRR = LCDSDARESET;}

#define LCD_Sda_Output_1		{IO_LCDSDA->BSETH = LCDSDASET;}

#define	LCD_Read_Sda			(IO_LCDSDA->IDR & LCDSDASET)
#endif
