/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    AppDisplay.c                                                                         
**** Brief:       显示模块                                                                     
**** Author:      peter.he@chint.com                                                                 
**** Version:     V1.0                                                                               
**** Date:        2016-7-14                                                                          
****                                                                                                 
**** note:修改历史记录列表，每条修改记录应包括修改日期、修改者                                          
**** 1.  Author:                                                                                     
****     Version:                                                                                    
****     Date :                                                                                      
**** 2.  Author:                                                                                     
****     Version:                                                                                       
****     Date:
****                                                                                        
****  addtogroup:Library                                                             
**********************************************************************************************************/

/*--------------------------------- 文件功能说明 -------------------------------------------------------*/
/*
 *  该文件所有函数的前缀为xxxx_
 *  文件主函数和对外函数需放在文件的首部，并且主函数需要放在第一个位置;
 *  函数注释采用标准模板，函数内部注释采用//;
 *  对于注释较多的部分，可以增加一个注释符，然后详细说明放在文件的尾部;
 *--------------------------------- 文件功能说明 -------------------------------------------------------*/
 
/**有形参的函数格式:*/
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    xx任务处理函数
 *
 *  @param    xx :
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
/**无形参的函数格式:*/
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    上电所有口线配置成初始状态，后面可根据需要开启和配置
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
 
/*----------------< 包含文件 >----------------------------------*/

#include "..\SourceFiles\PUB\Include.h "
#define    DRV_LCD_8_MSK__A   _BIT0
#define    DRV_LCD_8_MSK__B   _BIT1
#define    DRV_LCD_8_MSK__C   _BIT2

#define    DRV_LCD_8_MSK__D   _BIT3
#define    DRV_LCD_8_MSK__E   _BIT4
#define    DRV_LCD_8_MSK__F   _BIT5
#define    DRV_LCD_8_MSK__G   _BIT6

#define    DRV_LCD_8_MSK    \
          (DRV_LCD_8_MSK__A | DRV_LCD_8_MSK__B | DRV_LCD_8_MSK__C | DRV_LCD_8_MSK__D | DRV_LCD_8_MSK__E | DRV_LCD_8_MSK__F | DRV_LCD_8_MSK__G)
uchar8 const LCD_Char_Table[][2]={
	{ '0' , DRV_LCD_8_MSK__A | DRV_LCD_8_MSK__B | DRV_LCD_8_MSK__C | DRV_LCD_8_MSK__D | DRV_LCD_8_MSK__E | DRV_LCD_8_MSK__F   },
	{ '1' , DRV_LCD_8_MSK__B | DRV_LCD_8_MSK__C                                                                               },
	{ '2' , DRV_LCD_8_MSK__A | DRV_LCD_8_MSK__B | DRV_LCD_8_MSK__G | DRV_LCD_8_MSK__E | DRV_LCD_8_MSK__D                      },
	{ '3' , DRV_LCD_8_MSK__A | DRV_LCD_8_MSK__B | DRV_LCD_8_MSK__G | DRV_LCD_8_MSK__C | DRV_LCD_8_MSK__D                      },
	{ '4' , DRV_LCD_8_MSK__F | DRV_LCD_8_MSK__G | DRV_LCD_8_MSK__B | DRV_LCD_8_MSK__C                                         },
	{ '5' , DRV_LCD_8_MSK__A | DRV_LCD_8_MSK__F | DRV_LCD_8_MSK__G | DRV_LCD_8_MSK__C | DRV_LCD_8_MSK__D                      },
	{ '6' , DRV_LCD_8_MSK__A | DRV_LCD_8_MSK__F | DRV_LCD_8_MSK__E | DRV_LCD_8_MSK__D | DRV_LCD_8_MSK__C | DRV_LCD_8_MSK__G   },
	{ '7' , DRV_LCD_8_MSK__A | DRV_LCD_8_MSK__B | DRV_LCD_8_MSK__C                                                            },
	{ '8' , DRV_LCD_8_MSK                                                                                                     },
	{ '9' , DRV_LCD_8_MSK__G | DRV_LCD_8_MSK__F | DRV_LCD_8_MSK__A | DRV_LCD_8_MSK__B | DRV_LCD_8_MSK__C | DRV_LCD_8_MSK__D   },
	{ 'A' , DRV_LCD_8_MSK__A | DRV_LCD_8_MSK__B | DRV_LCD_8_MSK__C | DRV_LCD_8_MSK__E | DRV_LCD_8_MSK__F | DRV_LCD_8_MSK__G   },
	{ 'B' , DRV_LCD_8_MSK__C | DRV_LCD_8_MSK__D | DRV_LCD_8_MSK__E | DRV_LCD_8_MSK__F | DRV_LCD_8_MSK__G                      },
	{ 'C' , DRV_LCD_8_MSK__A | DRV_LCD_8_MSK__D | DRV_LCD_8_MSK__E | DRV_LCD_8_MSK__F                                         },
	{ 'U' , DRV_LCD_8_MSK__B | DRV_LCD_8_MSK__C | DRV_LCD_8_MSK__D | DRV_LCD_8_MSK__E | DRV_LCD_8_MSK__F                      },
	{ 'I' , DRV_LCD_8_MSK__E | DRV_LCD_8_MSK__F                                                                               },
	{ 'P' , DRV_LCD_8_MSK__A | DRV_LCD_8_MSK__B | DRV_LCD_8_MSK__E | DRV_LCD_8_MSK__F | DRV_LCD_8_MSK__G                      },
	{ 'F' , DRV_LCD_8_MSK__A | DRV_LCD_8_MSK__E | DRV_LCD_8_MSK__F | DRV_LCD_8_MSK__G                                         },
	{ 'O' , DRV_LCD_8_MSK__A | DRV_LCD_8_MSK__B | DRV_LCD_8_MSK__C | DRV_LCD_8_MSK__D | DRV_LCD_8_MSK__E | DRV_LCD_8_MSK__F   },
	#if(METER_TYPE==METER_TYPE_DDSYU666)
	{ 't' , DRV_LCD_8_MSK__F | DRV_LCD_8_MSK__E | DRV_LCD_8_MSK__G | DRV_LCD_8_MSK__D 										  },
	{ 'z' , DRV_LCD_8_MSK__A | DRV_LCD_8_MSK__G | DRV_LCD_8_MSK__D 	  				 										  },   //导轨表的透支，用三杠代替
	#endif
};
#define	LCD_CHAR_TABLE_ROWS	(sizeof(LCD_Char_Table)/2)

 
/*----------------< 变量定义 >----------------------------------*/
typedef struct	
{        
	ulong32   				ID;			///* 固定字符 *///    
    uchar8*   				Addr;		///* 数据地址 *///  
	uchar8                  Len;		///* 显示数据长度 *///
	uchar8                  Dots;		///* 小数位数，FF表示位数可变 *///
	uchar8                  StartPos;	///* 开始显示位置 *///
}GStr_Disp_Type;
#if(METER_TYPE==METER_TYPE_DDSYU666)
/*----------------< 宏定义区 >----------------------------------*/
#define disp_dangqian  		{ GStr_DisplayPara.ucLCDDrvDispBuf[24-1] |= _BIT5; }
#define disp_zheng    		{ GStr_DisplayPara.ucLCDDrvDispBuf[24-1] |= _BIT4; }
#define disp_fan     		{ GStr_DisplayPara.ucLCDDrvDispBuf[23-1] |= _BIT4; }
#define disp_xiang    		NOP() 
#define disp_dianliang      NOP() 
#define disp_dianjia        NOP() 
#define disp_shijian        { GStr_DisplayPara.ucLCDDrvDispBuf[ 3-1] |= _BIT5; }
#define disp_yu_e           { GStr_DisplayPara.ucLCDDrvDispBuf[ 6-1] |= _BIT5; }
#define disp_touzhi  		NOP()
#define disp_tongxinfu      { GStr_DisplayPara.ucLCDDrvDispBuf[ 7-1] |= _BIT4; }
#define disp_fanxiangfu     NOP() 
#define disp_bianchengfu    { GStr_DisplayPara.ucLCDDrvDispBuf[ 3-1] |= _BIT5; }   //新增，密钥符号。显示为TIME  
#define disp_qinggoudian    { GStr_DisplayPara.ucLCDDrvDispBuf[ 7-1] |= _BIT5; }
#define disp_lazha          { GStr_DisplayPara.ucLCDDrvDispBuf[ 6-1] |= _BIT4; }
#define disp_touzhifu       { GStr_DisplayPara.ucLCDDrvDispBuf[23-1] |= _BIT5; }// 暂时显示T表示透支
#define disp_tunji          NOP()
#define disp_yuan           { GStr_DisplayPara.ucLCDDrvDispBuf[ 5-1] |= _BIT5; }
#define disp_kWh            { GStr_DisplayPara.ucLCDDrvDispBuf[ 5-1] |= _BIT4; GStr_DisplayPara.ucLCDDrvDispBuf[ 4-1] |= (_BIT4|_BIT2|_BIT1); }
#define disp_shijian2       { GStr_DisplayPara.ucLCDDrvDispBuf[40-1] |= _BIT0; }            //小数点P2
#define disp_Dot4           { GStr_DisplayPara.ucLCDDrvDispBuf[38-1] |= _BIT0; }            //小数点P3
#define disp_Dot3           { GStr_DisplayPara.ucLCDDrvDispBuf[ 3-1] |= _BIT0; }            //小数点P5   时间点4
#define disp_Dot2           { GStr_DisplayPara.ucLCDDrvDispBuf[ 7-1] |= _BIT0; }            //小数点P6
#define disp_shijian1       { GStr_DisplayPara.ucLCDDrvDispBuf[40-1] |= _BIT4; }            //小数点P1
#define disp_shijian3       { GStr_DisplayPara.ucLCDDrvDispBuf[ 3-1] |= _BIT4; }          //小数点P4
//#define disp_U              { GStr_DisplayPara.ucLCDDrvDispBuf[ 8-1] |= _BIT4; }            //U 标志
//#define disp_I              { GStr_DisplayPara.ucLCDDrvDispBuf[ 8-1] |= _BIT5; }            //I 标志
#define disp_V              { GStr_DisplayPara.ucLCDDrvDispBuf[ 4-1] |= _BIT1; }
#define disp_I              { GStr_DisplayPara.ucLCDDrvDispBuf[ 4-1] |= _BIT3; }
#define disp_kW             { GStr_DisplayPara.ucLCDDrvDispBuf[ 5-1] |= _BIT4; GStr_DisplayPara.ucLCDDrvDispBuf[ 4-1] |= (_BIT2|_BIT1); }

/*----------------< 常量定义 >----------------------------------*/
 
#define	MAIN_DISP_AREA_NUM_MAX	7	// 主数据区数字数量
const unsigned char code LCD_SEG_CHAR_NUM1[MAIN_DISP_AREA_NUM_MAX][7]=
{
	{ 37, 38, 38, 39, 22, 22, 39 },	// 第1个数字ABCDEFG对应的seg	// 小数字 无
//	{  1,  1,  1,  1,  1,  1,  1 },	// 第2个数字ABCDEFG对应的seg 这里其实是缓冲区对应的地址偏移//无
	{ 24, 23, 23, 24, 24, 24, 23 },	// 第3个数字ABCDEFG对应的seg
	{ 22, 40, 40, 22, 22, 22, 40 },	// 第4个数字ABCDEFG对应的seg
	{ 39, 38, 38, 39, 39, 39, 38 },	// 第5个数字ABCDEFG对应的seg
	{ 37,  3,  3, 37, 37, 37,  3 },	// 第6个数字ABCDEFG对应的seg
	{  8,  7,  7, 8 ,  8,  8,  7 },	// 第7个数字ABCDEFG对应的seg
	{  6,  5,  5, 6 ,  6,  6,  5 },	// 第8个数字ABCDEFG对应的seg 
};
const unsigned char code LCD_COM_CHAR_NUM1[MAIN_DISP_AREA_NUM_MAX][7]=
{
	{  5,  5,  4,  4,  4,  5,  5 },	// 第1个数字ABCDEFG对应的com	// 小数字 无
//	{  3,  3,  1,  0,  1,  2,  2 },	// 第2个数字ABCDEFG对应的com	该数码管的SEG脚未焊接，不显示
	{  3,  3,  1,  0,  1,  2,  2 },	// 第3个数字ABCDEFG对应的com
	{  3,  3,  1,  0,  1,  2,  2 },	// 第4个数字ABCDEFG对应的com
	{  3,  3,  1,  0,  1,  2,  2 },	// 第5个数字ABCDEFG对应的com
	{  3,  3,  1,  0,  1,  2,  2 },	// 第6个数字ABCDEFG对应的com
	{  3,  3,  1,  0,  1,  2,  2 },	// 第7个数字ABCDEFG对应的com
	{  3,  3,  1,  0,  1,  2,  2 },	// 第8个数字ABCDEFG对应的com
};
static  GStr_Disp_Type code Disp_Table[]=
{
	{0x00000000,		&GStr_Energy.ucaFw_Energy[0]  ,        4,	2,	1, },   ///* 0当前电量	
	{0x00010000,		&GStr_Energy.ucaFw_Energy[0]  ,        4,	2,	1, },   ///* 1当前正向电量
	{0x00020000,		&GStr_Energy.ucaBk_Energy[0]  ,        4,	2,	1, },   ///* 2当前反向电量             
	{0x04000401,		&GStr_MeterIFO.ucaCommAddr[0] ,        3,	0,	2, },   ///* 3通信地址高4	
	{0x04000401,		&GStr_MeterIFO.ucaCommAddr[3] ,        3,	0,	2, },   ///* 4通信地址低8
	{0x04000402,		&GStr_MeterIFO.ucaMeterID[0]  ,        3,	0,	2, },   ///* 5表号高4
	{0x04000402,		&GStr_MeterIFO.ucaMeterID[3]  ,        3,	0,	2, },   ///* 6表号低8
	{0x0400040E,		&GStr_MeterIFO. ucaUserID[0]  ,        3,	0,	2, },   ///* 7客户编号高4                    
	{0x0400040E,		&GStr_MeterIFO. ucaUserID[3]  ,        3,	0,	2, },   ///* 8客户编号低8
	{0x02800020,	    &GStr_PRICE.ucaPrice[0]       ,        4,	4,	1, },	///* 9电价                       
	{0x00900200,		&GStr_Money.ucaRemainMoney[0] ,        4,	2,	1, },	///* 10余额                       
	{0x00900201,	    &GStr_Money.ucaTickMoney[0]   ,        4,	2,	1, },	///* 11透支金额      
	{0x04001001,	    &GStr_MoneyPara.ucaAlarmMoneyL1[0]   , 4,	2,	1, },	///* 12报警金额1
    {0x04001002,	    &GStr_MoneyPara.ucaAlarmMoneyL2[0]   , 4,	2,	1, },	///* 13报警金额2
    {0x04090B01,        &GStr_MoneyPara.ucaOverLoadVal[0],     3,	4,	3, },   ///* 14过载功率
	{0x02010100,		&GStr_UIPDisplay.ucVoltageA[1],        3,	2,	3, },   ///* 15A相电压
	{0x02020100,		&GStr_UIPDisplay.ucCurrentA[1],        3,	3,	3, },   ///* 16A相电流
	{0x02030000,		&GStr_UIPDisplay.ucPower[1],           3,	4,	3, },   ///* 17总有功功率
	{0x02030100,		&GStr_UIPDisplay.ucPowerA[1],          3,	4,	3, },   ///* 18A相有功功率,	
	{0x02060000,		&GStr_UIPDisplay.ucFactory[2],         2,	3,	5, },   ///* 19总功率因数
	{0x02060100,		&GStr_UIPDisplay.ucFactoryA[2],        2,	3,	5, },   ///* 20A相功率因数,	
	{0x02800002,        &GStr_UIPDisplay.ucFrequency[2],       2,	2,	5, },   ///* 21A电网频率,	
	{0x04000409,        &GStr_UIPDisplay.ucMeterConst[0],      3,	0, 	3, },   ///* 22 有功常数
#if(METER_TYPE==METER_TYPE_DTSY666)
    {0x02010200,        &GStr_UIPDisplay.ucVoltageB[1],        3,   2,  3, },   ///* 22B相电压,	
	{0x02010300,		&GStr_UIPDisplay.ucVoltageC[1],        3,   2,  3, },   ///* 23C相电压,		
	{0x02020200,        &GStr_UIPDisplay.ucCurrentB[1],        3,   3,  3, },   ///* 24B相电流,	
	{0x02020300,		&GStr_UIPDisplay.ucCurrentC[1],        3,   3,  3, },   ///* 25C相电流,			
	{0x02030200,		&GStr_UIPDisplay.ucPowerB[1]  ,        3,   4,  3, },   ///* 26B相有功功率
	{0x02030300,		&GStr_UIPDisplay.ucPowerC[1]  ,        3,   4,  3, },   ///* 27C相有功功率,	
	{0x02060200,		&GStr_UIPDisplay.ucFactoryB[2],        2,   3,  5, },   ///* 28B功率因数
	{0x02060300,		&GStr_UIPDisplay.ucFactoryC[2],        2,   3,  5, },   ///* 29C相功率因数,
#endif

	{0xFFFFFFFF,		0,                                     0,   0,  0, },	///* 全显  始终在最后一项
};
//#if(METER_TYPE==METER_TYPE_DTSY666)
//	#define   DispMaxNum           31   ///* 目前31屏，后续扩展
//#else
	#define   DispMaxNum           sizeof(Disp_Table)/sizeof(GStr_Disp_Type)   ///* 目前23屏，后续扩展
//#endif
	
	
#endif

#if( (METER_TYPE==METER_TYPE_DDSY666) || ( METER_TYPE==METER_TYPE_DTSY666 ) )
/*----------------< 宏定义区 >----------------------------------*/
#define disp_dangqian  		( GStr_DisplayPara.ucLCDDrvDispBuf[1]  |= _BIT5 )
#define disp_zheng    		( GStr_DisplayPara.ucLCDDrvDispBuf[0]  |= _BIT5 )
#define disp_fan     		( GStr_DisplayPara.ucLCDDrvDispBuf[36] |= _BIT5 )
#define disp_xiang    		( GStr_DisplayPara.ucLCDDrvDispBuf[37] |= _BIT5 )
#define disp_dianliang      ( GStr_DisplayPara.ucLCDDrvDispBuf[39] |= _BIT5 )
#define disp_dianjia        ( GStr_DisplayPara.ucLCDDrvDispBuf[15] |= _BIT5 )
#define disp_shijian        ( GStr_DisplayPara.ucLCDDrvDispBuf[14] |= _BIT5 )
#define disp_yu_e           ( GStr_DisplayPara.ucLCDDrvDispBuf[11] |= _BIT5 )
#define disp_touzhi  		( GStr_DisplayPara.ucLCDDrvDispBuf[10] |= _BIT5 )
#define disp_tongxinfu      ( GStr_DisplayPara.ucLCDDrvDispBuf[1]  |= _BIT1 )
#define disp_fanxiangfu     ( GStr_DisplayPara.ucLCDDrvDispBuf[0]  |= _BIT0 )
#define disp_bianchengfu    ( GStr_DisplayPara.ucLCDDrvDispBuf[36] |= _BIT1 )
#define disp_qinggoudian    ( GStr_DisplayPara.ucLCDDrvDispBuf[37] |= _BIT0 )
#define disp_lazha          ( GStr_DisplayPara.ucLCDDrvDispBuf[38] |= _BIT1 )
#define disp_touzhifu       ( GStr_DisplayPara.ucLCDDrvDispBuf[38] |= _BIT0 )
#define disp_tunji          ( GStr_DisplayPara.ucLCDDrvDispBuf[39] |= _BIT0 )
#define disp_yuan           ( GStr_DisplayPara.ucLCDDrvDispBuf[16] |= _BIT0 )
#define disp_kWh            ( GStr_DisplayPara.ucLCDDrvDispBuf[9]  |= _BIT5 )
#define disp_shijian2       ( GStr_DisplayPara.ucLCDDrvDispBuf[16] |= _BIT1 )            //小数点P2
#define disp_Dot4           ( GStr_DisplayPara.ucLCDDrvDispBuf[14] |= _BIT1 )            //小数点P3
#define disp_Dot3           ( GStr_DisplayPara.ucLCDDrvDispBuf[12] |= _BIT1 )            //小数点P5   时间点4
#define disp_Dot2           ( GStr_DisplayPara.ucLCDDrvDispBuf[10] |= _BIT1 )            //小数点P6
#define disp_shijian1       ( GStr_DisplayPara.ucLCDDrvDispBuf[16] |= _BIT5 )            //小数点P1
#define disp_shijian3       ( GStr_DisplayPara.ucLCDDrvDispBuf[12] |= _BIT5 )            //小数点P4




/*----------------< 常量定义 >----------------------------------*/

#define	MAIN_DISP_AREA_NUM_MAX	8
const unsigned char code LCD_SEG_CHAR_NUM1[MAIN_DISP_AREA_NUM_MAX][7]=
{
	{  1,  1,  1,  1,  2,  2,  2 },	// 第1个数字ABCDEFG对应的seg 这里其实是缓冲区对应的地址偏移
	{ 38, 38, 38, 38, 37, 37, 37 },	// 第2个数字ABCDEFG对应的seg
	{ 40, 40, 40, 40, 39, 39, 39 },	// 第3个数字ABCDEFG对应的seg
	{ 16, 16, 16, 16, 17, 17, 17 },	// 第4个数字ABCDEFG对应的seg
	{ 14, 14, 14, 14, 15, 15, 15 },	// 第5个数字ABCDEFG对应的seg
	{ 12, 12, 12, 12, 13, 13, 13 },	// 第6个数字ABCDEFG对应的seg
	{ 10, 10, 10, 10, 11, 11, 11 },	// 第7个数字ABCDEFG对应的seg
	{ 10, 16, 15, 14, 13, 11, 12 },	// 第8个数字ABCDEFG对应的seg 
};
const unsigned char code LCD_COM_CHAR_NUM1[MAIN_DISP_AREA_NUM_MAX][7]=
{
	{  4,  3,  2,  1,  2,  4,  3 },	// 第1个数字ABCDEFG对应的com
	{  4,  3,  2,  1,  2,  4,  3 },	// 第2个数字ABCDEFG对应的com
	{  4,  3,  2,  1,  2,  4,  3 },	// 第3个数字ABCDEFG对应的com
	{  4,  3,  2,  1,  2,  4,  3 },	// 第4个数字ABCDEFG对应的com
	{  4,  3,  2,  1,  2,  4,  3 },	// 第5个数字ABCDEFG对应的com
	{  4,  3,  2,  1,  2,  4,  3 },	// 第6个数字ABCDEFG对应的com
	{  4,  3,  2,  1,  2,  4,  3 },	// 第7个数字ABCDEFG对应的com
	{  0,  0,  0,  0,  0,  0,  0 },	// 第8个数字ABCDEFG对应的com
};

/*----------------< 变量定义 >----------------------------------*/ 
static  GStr_Disp_Type code Disp_Table[]=
{
	{0x00000000,		&GStr_Energy.ucaFw_Energy[0]  ,        4,	2, 	1, },   ///* 0当前电量	
	{0x00010000,		&GStr_Energy.ucaFw_Energy[0]  ,        4,	2, 	1, },   ///* 1当前正向电量
	{0x00020000,		&GStr_Energy.ucaBk_Energy[0]  ,        4,	2, 	1, },   ///* 2当前反向电量             
	{0x04000401,		&GStr_MeterIFO.ucaCommAddr[0] ,        2,	0, 	5, },   ///* 3通信地址高4	
	{0x04000401,		&GStr_MeterIFO.ucaCommAddr[2] ,        4,	0, 	1, },   ///* 4通信地址低8
	{0x04000402,		&GStr_MeterIFO.ucaMeterID[0]  ,        2,	0, 	5, },   ///* 5表号高4
	{0x04000402,		&GStr_MeterIFO.ucaMeterID[2]  ,        4,	0, 	1, },   ///* 6表号低8
	{0x0400040E,		&GStr_MeterIFO. ucaUserID[0]  ,        2,	0, 	5, },   ///* 7客户编号高4                    
	{0x0400040E,		&GStr_MeterIFO. ucaUserID[2]  ,        4,	0, 	1, },   ///* 8客户编号低8
	{0x02800020,	    &GStr_PRICE.ucaPrice[0]       ,        4,	4, 	1, },	///* 9电价                       
	{0x00900200,		&GStr_Money.ucaRemainMoney[0] ,        4,	2, 	1, },   ///* 10余额                       
	{0x00900201,	    &GStr_Money.ucaTickMoney[0]   ,        4,	2, 	1, },	///* 11透支金额      
	{0x04001001,	    &GStr_MoneyPara.ucaAlarmMoneyL1[0]   , 4,	2, 	1, },	///* 12报警金额1
    {0x04001002,	    &GStr_MoneyPara.ucaAlarmMoneyL2[0]   , 4,	2, 	1, },	///* 13报警金额2
    {0x04090B01,        &GStr_MoneyPara.ucaOverLoadVal[0],     3,	4, 	3, },   ///* 14过载功率
	{0x02010100,		&GStr_UIPDisplay.ucVoltageA[1],        3,	2, 	3, },   ///* 15A相电压
	{0x02020100,		&GStr_UIPDisplay.ucCurrentA[1],        3,	3, 	3, },   ///* 16A相电流
	{0x02030000,		&GStr_UIPDisplay.ucPower[1],           3,	4, 	3, },   ///* 17总有功功率
	{0x02030100,		&GStr_UIPDisplay.ucPowerA[1],          3,	4, 	3, },   ///* 18A相有功功率,	
	{0x02060000,		&GStr_UIPDisplay.ucFactory[2],         2,	3, 	5, },   ///* 19总功率因数
	{0x02060100,		&GStr_UIPDisplay.ucFactoryA[2],        2,	3, 	5, },   ///* 20A相功率因数,	
	{0x02800002,        &GStr_UIPDisplay.ucFrequency[2],       2,	2, 	5, },   ///* 21A电网评率,	
	{0x04000409,        &GStr_UIPDisplay.ucMeterConst[0],      3,	0, 	3, },   ///* 22有功常数
#if(METER_TYPE==METER_TYPE_DTSY666)
    {0x02010200,        &GStr_UIPDisplay.ucVoltageB[1],        3,   2,  3, },   ///* 22B相电压,	
	{0x02010300,		&GStr_UIPDisplay.ucVoltageC[1],        3,   2,  3, },   ///* 23C相电压,		
	{0x02020200,        &GStr_UIPDisplay.ucCurrentB[1],        3,   3,  3, },   ///* 24B相电流,	
	{0x02020300,		&GStr_UIPDisplay.ucCurrentC[1],        3,   3,  3, },   ///* 25C相电流,			
	{0x02030200,		&GStr_UIPDisplay.ucPowerB[1]  ,        3,   4,  3, },   ///* 26B相有功功率
	{0x02030300,		&GStr_UIPDisplay.ucPowerC[1]  ,        3,   4,  3, },   ///* 27C相有功功率,	
	{0x02060200,		&GStr_UIPDisplay.ucFactoryB[2],        2,   3,  5, },   ///* 28B功率因数
	{0x02060300,		&GStr_UIPDisplay.ucFactoryC[2],        2,   3,  5, },   ///* 29C相功率因数,
#endif
	{0xFFFFFFFF,		0,                                     0,   0,  0, },	///* 全显  始终在最后一项
};

#define   DispMaxNum           sizeof(Disp_Table)/sizeof(GStr_Disp_Type)   ///* 目前23屏，后续扩展

	
#endif
/*----------------< 函数声明 >----------------------------------*/
void ApiDisp_DisplayTask(void);
uchar8 ApiGet_Lcd_Num(ulong32 DataId,uchar8 ScreenNum);
ulong32 ApiGet_Lcd_ID(uchar8 v_LcdNum);
static void ApiDisplay_NumData( unsigned char Num, unsigned char show );
static void ApiDisp_ShowNum(uchar8 ShowStartPos,uchar8 len, uchar8* Show, uchar8 v_ucDots);
static void APiDisp_Const(uchar8 Dispcnt);
void APiDisp_LcdledControl();
/*----------------< 函数定义 >----------------------------------*/
uchar8 ApiGet_Lcd_Num(ulong32 DataId,uchar8 ScreenNum)
{
	uchar8 i,v_LcdNum;
	for(i=1;i<(DispMaxNum+1);i++)///没有序号0，第一屏为序号1，返回0为不支持该标识
	{
		if(DataId==Disp_Table[i-1].ID)
		{
			if((DataId==0x04000401)||(DataId==0x04000402)||(DataId==0x0400040E))
			{
				if(ScreenNum==0) 
				{
					v_LcdNum=i;
				}
				else
				{
					v_LcdNum=(i+1);
				}
			}
			else 
			{
				v_LcdNum=i;
			}
			return v_LcdNum;
		}
	}
    return 0x00;///不支持显示
}

ulong32 ApiGet_Lcd_ID(uchar8 v_LcdNum)
{
	ulong32 V_ulDI3DI2DI1DI0;
    if(v_LcdNum>=DispMaxNum)
	{
		V_ulDI3DI2DI1DI0=0x00000000;///别的值显示当前正向总
		return V_ulDI3DI2DI1DI0;
	}
	V_ulDI3DI2DI1DI0=Disp_Table[v_LcdNum].ID;

	return V_ulDI3DI2DI1DI0;
}

void ApiDisplay_NumData( unsigned char v_ucNumPos, unsigned char v_ucShowChar )
{
	unsigned char V_ucCnti,V_ucCntj, V_ucResult, V_ucTemp08, V_ucPosBit,V_ucCombit; 
	
	if( MAIN_DISP_AREA_NUM_MAX < v_ucNumPos ) return;

	
	 for( V_ucCntj=0; V_ucCntj<LCD_CHAR_TABLE_ROWS; V_ucCntj++ )
	 {
		 if( v_ucShowChar == LCD_Char_Table[V_ucCntj][0] )
		 {
			V_ucResult =  LCD_Char_Table[V_ucCntj][1];
			break;
		 }
	 }
	if( LCD_CHAR_TABLE_ROWS <= V_ucCntj ) return;
	 
	V_ucTemp08 = 1;	
	for( V_ucCnti=0 ; V_ucCnti<7; V_ucCnti++ )
	{  
		V_ucCombit = LCD_COM_CHAR_NUM1[v_ucNumPos-1][V_ucCnti]; 	// 找到ABCDEFG对应的com
		V_ucPosBit = LCD_SEG_CHAR_NUM1[v_ucNumPos-1][V_ucCnti]-1;	// 找到ABCDEFG对应的seg 
		
		V_ucCombit = ( 0x01<<V_ucCombit );
		if( (V_ucResult & V_ucTemp08) ) 
		{
			GStr_DisplayPara.ucLCDDrvDispBuf[V_ucPosBit] |= V_ucCombit;
		} 
		V_ucTemp08 <<= 1;
	} 
}
void ApiDisp_ShowNum(uchar8 ShowStartPos, uchar8 len, uchar8* Show, uchar8 v_ucDots)
{
	unsigned char i, k, j;

	j = len*2-v_ucDots;	//0位小数
	
	k = 0;
	if( GStr_DisplayPara.ucDisp_0_flag)///
	{
		for( i=0; i<len; i++ )
		{
			if(((((*(Show+i))>>4)&0x0F) == 0) && (k == 0)&&((2*(i+1)-1)<j))   ///* 第i个字节的高位要小于整数的位数，有效整数只有一位且为0，不灭零
			{
				ShowStartPos++;//首位为0不显示
			}
			else
			{
				k=1;
				ApiDisplay_NumData( ShowStartPos++, (((*(Show+i))>>4)&0x0F)+0x30 ); 
			}
			
			if(((((*(Show+i))>>0)&0x0F) == 0) && (k == 0)&& ((2*(i+1))<j)) ShowStartPos++;///* 第i个字节的低位要小于整数的位数，有效整数只有一位且为0，不灭零
			else
			{
				k=1;
				ApiDisplay_NumData( ShowStartPos++, (((*(Show+i))>>0)&0x0F)+0x30 ); 
            }
         }			
	}
	else
	{
		for( i=0; i<len; i++ )
		{
			ApiDisplay_NumData( ShowStartPos++, (((*(Show+i))>>4)&0x0F)+0x30 );
			ApiDisplay_NumData( ShowStartPos++, (((*(Show+i))>>0)&0x0F)+0x30 );
		}
    }
}

void APiDisp_Const(uchar8 Dispcnt)
{
	uchar8 V_ucDots=0;
    LibPub_MemSetBytes( GStr_DisplayPara.ucLCDDrvDispBuf, 0x00, 40 );
	///*缓存清零
	GStr_DisplayPara.ucDisp_0_flag=0;///消零标志清0

	if((DispMaxNum-1)==Dispcnt)
	{
		LibPub_MemSetBytes( GStr_DisplayPara.ucLCDDrvDispBuf, 0xFF, 40 );
		return;
	}
    switch (Dispcnt)
	{
		case 0://当前总电量
		{
			disp_dangqian;
			disp_dianliang;
		    disp_kWh;
		    disp_Dot2;
		    GStr_DisplayPara.ucDisp_0_flag=1;
		}break;
		case 1://当前正向电量
		{
			#if(METER_TYPE!=METER_TYPE_DDSYU666)
			disp_dangqian;
			#endif
			disp_zheng;
			disp_xiang;
			disp_dianliang;
			disp_kWh;
		    disp_Dot2;
		    GStr_DisplayPara.ucDisp_0_flag=1;
		}break;  
		case 2://当前反向电量
		{
			#if(METER_TYPE!=METER_TYPE_DDSYU666)
			disp_dangqian;
			#endif
			disp_fan;
			disp_xiang;
			disp_dianliang;
			disp_kWh;
		    disp_Dot2;
		    GStr_DisplayPara.ucDisp_0_flag=1;
		}break;  
		

		
		case 9: ///电价
		{
			disp_dianjia;
		    disp_Dot4;
		    disp_yuan;
			GStr_DisplayPara.ucDisp_0_flag=1;
		}break;
		
        case 10:   ///剩余金额
		{
			disp_yu_e;
		    disp_Dot2;
		    disp_yuan;
			GStr_DisplayPara.ucDisp_0_flag=1;
		}	break;

        case 11:  ///透支金额
		{
			#if(METER_TYPE==METER_TYPE_DDSYU666)
			ApiDisplay_NumData( 1, 'z' );               ///显示透支	 T+三
			disp_touzhifu;
			#endif
			disp_touzhi;
		    disp_Dot2;
		    disp_yuan;
			GStr_DisplayPara.ucDisp_0_flag=1;
		}break;
		
		case 12:///报警金额1   
		{
			disp_Dot2;
			disp_yuan;
			GStr_DisplayPara.ucDisp_0_flag=1;
		}break;
		
		case 13:///报警金额2
		{
			disp_Dot2;
			disp_yuan;
			GStr_DisplayPara.ucDisp_0_flag=1;
		}break;
		
		case 14:///过载功率
		{
			ApiDisplay_NumData( 1, 'O' );///显示OP
			ApiDisplay_NumData( 2, 'P' );
			disp_Dot4;
			GStr_DisplayPara.ucDisp_0_flag=1;
			
		}break;
		
		case 15:///A相电压 
		#if(METER_TYPE==METER_TYPE_DTSY666)
		case 23:///B相电压
		case 24://C相电压	
		#endif
		{
			#if(METER_TYPE==METER_TYPE_DDSYU666)
	        disp_V;
			ApiDisplay_NumData( 2, 'U' ); ///显示U
			#else
			ApiDisplay_NumData( 1, 'U' ); ///显示U
			if(Dispcnt==15)
			{
				ApiDisplay_NumData( 2, 'A' ); ///显示A
			}
			#endif
			#if(METER_TYPE==METER_TYPE_DTSY666)
			else if(Dispcnt==23)
			{
				ApiDisplay_NumData( 2, 'B' ); ///显示B
			}
			else 
			{
				ApiDisplay_NumData( 2, 'C' ); ///显示C
			}	
			#endif
			disp_Dot2;
			
			GStr_DisplayPara.ucDisp_0_flag=1;
			
		}break;
		
		case 16:///A相电流
		#if(METER_TYPE==METER_TYPE_DTSY666)	
		case 25://B相电流
		case 26://C相电流	
		#endif
		{
			#if(METER_TYPE==METER_TYPE_DDSYU666)
	        disp_I;
			ApiDisplay_NumData( 2, 'I' ); ///显示U
			#else
			ApiDisplay_NumData( 1, 'I' ); ///显示I
			if(Dispcnt==16)
			{
				ApiDisplay_NumData( 2, 'A' ); ///显示A
			}
			#endif
			#if(METER_TYPE==METER_TYPE_DTSY666)	
			else if(Dispcnt==25)//B相电流
			{
				ApiDisplay_NumData( 2, 'B' ); ///显示B
			}
			else
			{
				ApiDisplay_NumData( 2, 'C' ); ///显示C
			}
			#endif
			disp_Dot3;
			
			GStr_DisplayPara.ucDisp_0_flag=1;
			
		}break;
		
		case 17:///总有功功率
		case 18:///A有功功率
		#if(METER_TYPE==METER_TYPE_DTSY666)		
		case 27://B相功率
		case 28://C相功率	
		#endif
		{
			#if(METER_TYPE==METER_TYPE_DDSYU666)
	        disp_kW;
			ApiDisplay_NumData( 2, 'P' ); ///显示U
			#else
			ApiDisplay_NumData( 1, 'P' ); ///显示P
			if(Dispcnt==18)
			{
				ApiDisplay_NumData( 2, 'A' ); ///显示A	
			}
			#endif
			#if(METER_TYPE==METER_TYPE_DTSY666)	
			else if(Dispcnt==27)///B相功率
			{
				ApiDisplay_NumData( 2, 'B' ); ///显示B	
			}
			else if(Dispcnt==28)///C相功率
			{
				ApiDisplay_NumData( 2, 'C' ); ///显示C
			}
			#endif
			disp_Dot4;
			GStr_DisplayPara.ucDisp_0_flag=1;
			
		}break;
		
		case 19:///总功率因数
		case 20:///A功率因数
		#if(METER_TYPE==METER_TYPE_DTSY666)			
		case 29://B相功率因数
		case 30://C相功率因数	
		#endif
		{
			#if(METER_TYPE==METER_TYPE_DDSYU666)
			ApiDisplay_NumData( 2, 'F' ); ///显示U
			ApiDisplay_NumData( 3, 't' ); ///显示U
			#else
			if(Dispcnt==20)
			{
				ApiDisplay_NumData( 2, 'A' ); ///显示A
			}
			#endif
			#if(METER_TYPE==METER_TYPE_DTSY666)		
			else if(Dispcnt==29)
			{
				ApiDisplay_NumData( 2, 'B' ); ///显示B
			}
			else if(Dispcnt==30)
			{
				ApiDisplay_NumData( 2, 'C' ); ///显示C
			}
			#endif
			disp_Dot3;
			GStr_DisplayPara.ucDisp_0_flag=1;
		}break;
		
		case 21:///频率
		{
			#if(METER_TYPE==METER_TYPE_DDSYU666)
			ApiDisplay_NumData( 2, 'F' ); ///显示U
			#else
			ApiDisplay_NumData( 1, 'F' ); ///显示F
			#endif
			disp_Dot2;
			GStr_DisplayPara.ucDisp_0_flag=1;
		}break;
		
		case 22:///有功常数
		{
			GStr_DisplayPara.ucDisp_0_flag=1;
		}break;
		
		

		default:
		break;
    }
	V_ucDots = Disp_Table[Dispcnt].Dots;
	#if(METER_TYPE!=METER_TYPE_DDSYU666)     //单三相数字显示，
	ApiDisp_ShowNum( Disp_Table[Dispcnt].StartPos, Disp_Table[Dispcnt].Len, Disp_Table[Dispcnt].Addr, V_ucDots);
	#else  //导轨表显示放在APiDisp_Dynamic
	if(F_FACTORY_MODE==(GStr_Flag.ucMeterMode&F_FACTORY_MODE))
	{
		if(GStr_DisplayPara.usDispCnt%2)  //数据闪烁
		{
	      ApiDisp_ShowNum( Disp_Table[Dispcnt].StartPos, Disp_Table[Dispcnt].Len, Disp_Table[Dispcnt].Addr, V_ucDots);
		}
	}
	else	///* 厂外导轨表数据常显
	{
		ApiDisp_ShowNum( Disp_Table[Dispcnt].StartPos, Disp_Table[Dispcnt].Len, Disp_Table[Dispcnt].Addr, V_ucDots);
		if(!(GStr_Flag.ucRunState2&F_RUN_EsamKeyFlag))///公钥，厂外密钥判断  
		{
				disp_bianchengfu;
		}
	}  
	#endif
}

void APiDisp_Dynamic(void)
{
	GStr_DisplayPara.usDispCnt++;
	
	#if(METER_TYPE!=METER_TYPE_DDSYU666)   //导轨表没有硬ij按钮，
	if((F_FACTORY_MODE==(GStr_Flag.ucMeterMode&F_FACTORY_MODE))||(F_KEY_ACKTION_DOWN==(GStr_Flag.ucFactoryKey&F_KEY_ACKTION_DOWN)))
	///* 硬IJ短接或者软IJ有效闪烁显示编程符号
	{
		if(GStr_DisplayPara.usDispCnt%2)
		{
			disp_bianchengfu;
		}
	}///厂内闪烁显示编程符号
	else
	{
			if(!(GStr_Flag.ucRunState2&F_RUN_EsamKeyFlag))///公钥
			{
					disp_bianchengfu;
			}
	}
	#endif
	
	if(GStr_Flag.ucRunState1 &F_RUN_POWER_REVERSE)
	{
		disp_fanxiangfu;
	}
	if (_TRUE == LibPub_GetDiffTime( GStr_DisplayPara.ucDisp_tongxin_Time, LibPub_GetTimerBeat(), 5000))
	{
//		GStr_DisplayPara.ucDisp_tongxin_Time=0;
		GStr_DisplayPara.ucDisp_tongxin_Flag=0x00;
	}
	if(0x55==GStr_DisplayPara.ucDisp_tongxin_Flag)
	{

		if(GStr_DisplayPara.usDispCnt%2)
		{
			disp_tongxinfu;			
		}
	}
	if( (0x00==GStr_DisplayPara.ucDisp_tongxin_Flag) && (BLE_STAT_CONNECTED==GStr_Flag.ucBLESTATFlag) )
	{
		disp_tongxinfu;
	}	
	if(GStr_Flag.ucRunState2&F_RUN_RELAY_STATE)
	{  	
		  disp_lazha;
	}
  if((GStr_Flag.ucRunState1 &F_RUN_L1_ALRAM)||(GStr_Flag.ucRunState1 &F_RUN_L2_ALRAM)||(GStr_Flag.ucRunState1&F_RUN_REMAIND_ZERO))
	{///1级报警、2级报警和剩余金额为0时，请购电闪烁
			if(GStr_DisplayPara.usDispCnt%2)
			{

				disp_qinggoudian;///请购电闪烁
				
			}
	}
	if(GStr_Flag.ucRunState1 &F_RUN_OVER_DRAFT)
	{///透支后透支和请购电常显
			disp_touzhifu;///透支
			disp_qinggoudian;///请购电常显
	}
	
	if((GStr_Counter.ucPasswordErr_Cnt[0]>=3)||(GStr_Counter.ucPasswordErr_Cnt[1]>=3)||
		(GStr_Counter.ucPasswordErr_Cnt[2]>=3)||(GStr_Flag.ucRunState2&F_RUN_INTAUTH_MACNumErrFlag))
	{///密码错3次或者身份认证挂起
			if(GStr_DisplayPara.usDispCnt%2)
			{
					disp_kWh;///闪烁kWh
			}
//			else
//			{
//				 GStr_DisplayPara.ucLCDDrvDispBuf[9]  &= ~_BIT5 ;///清掉kwh的缓存
//			}
	
	}
	


}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    背光控制
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void APiDisp_LcdledControl()	//背光控制
{
	if( GStr_DisplayPara.ucBackLightTime != 0 ) GStr_DisplayPara.ucBackLightTime--;

    if( GStr_Flag.ucRunState1& B0011_1111 )///功率反向不点亮背光，通信报警和一二级报警透支过零过载功率反向等点亮背光
	{
		LCDLEDON();
	}
	
	else if( GStr_DisplayPara.ucBackLightTime !=0 ) 
	{
		LCDLEDON();
	}
	else
	{
		LCDLEDOFF();
	}
	if( GStr_DisplayPara.ucRelayLEDTime != 0 ) GStr_DisplayPara.ucRelayLEDTime--;
	if(GStr_DisplayPara.ucRelayLEDTime)
	{
		RELAYLEDON();
	}
	else if( GStr_Flag.ucRunState2&F_RUN_RELAY_STATE )
	{

		RELAYLEDON();
	}
	else
	{
		RELAYLEDOFF();
	}		
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    刷新显示任务
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void ApiDisp_DisplayTask(void)
{
	uchar8 Dispcnt;
	

	
 // @brief  如果掉电，就直接退出，不刷新
	/* 需要增加掉电判断 */
	if ( (GStr_Flag.ucSystem & F_PWON)==0 )	///* 掉电了就直接退出 *///
	{
		return;
	}

	// 500ms刷新一次显示
	if ( _TRUE == LibPub_GetDiffTime( GStr_DisplayPara.ulDispUpdataTime, LibPub_GetTimerBeat(), LCD_UPTATA_TIME) )
	{
		GStr_DisplayPara.ulDispUpdataTime =  LibPub_GetTimerBeat();
		GStr_Flag.ucDisp |= F_DISP_UPDATA;			// 置显示刷新标志 
		
		GStr_DisplayPara.ulDisptimer--;
		if(GStr_DisplayPara.ulDisptimer==0)
		{
		    GStr_DisplayPara.ulDisptimer = GStr_DisplayPara.ucDispDurTime*1000/LCD_UPTATA_TIME;///置显示时间为循显时间，转换为ms
			GStr_DisplayPara.ucDispNum++;
			
			if( (GStr_Flag.ucDisp & F_DISP_KEYDISP) || (GStr_Flag.ucDisp & F_DISP_COM_DIASP) || ( GStr_Flag.ucDisp & F_DISP_DISPALL ) )
			{
				GStr_DisplayPara.ucFirstKeyDisp = 0;		// 按键循环显示时间到，下次按键显示重新第一屏显示
				GStr_Flag.ucDisp = 0;///*显示时间到清掉所有的显示标志，置循环显示标志
				GStr_Flag.ucDisp |= F_DISP_AUTODISP;	// 按键循环显示时间到，开始循环显示，从第一屏开始
				GStr_DisplayPara.ucDispNum = 0;
            }
		}
		
		if(GStr_Flag.ucDisp & F_DISP_KEYDISP)	// 按键显示
		{
			Dispcnt = GStr_DisplayPara.ucKeyDisptable[GStr_DisplayPara.ucDispNum];
		} 
		else if(GStr_Flag.ucDisp & F_DISP_COM_DIASP)	// 通信显示
		{
			Dispcnt=GStr_DisplayPara.ucDispNum;	// 映射具体显示内容 
		} 
		else if(GStr_Flag.ucDisp & F_DISP_DISPALL)	// 全显
		{
			LCDDrv_SetLcdBuff(0xFF);
			return;
		} 
		else if(GStr_Flag.ucDisp & F_DISP_AUTODISP) // 自动循环显示
		{
			if(GStr_DisplayPara.ucDispNum>=GStr_DisplayPara.ucAutoDispNum)
			{
				GStr_DisplayPara.ucDispNum=0;
			}
			Dispcnt=GStr_DisplayPara.ucAutoDisptable[GStr_DisplayPara.ucDispNum];	
		}	
		
		// 准备显示数据
		if(Dispcnt>=DispMaxNum)
		{
			Dispcnt=0;
		}
		APiDisp_Const(Dispcnt);
		APiDisp_Dynamic();
		LCDDrv_DispRamUpdata();	
	}
}