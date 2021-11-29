/*******************************************************************************************************
**** Copyright��  (c)Copyright 2019,�㽭��̩�����Ǳ��������ι�˾,���ܱ�Ӧ���з�                       
****                            All rights reserved.                                                 
**** FileName:    AppDisplay.c                                                                         
**** Brief:       ��ʾģ��                                                                     
**** Author:      peter.he@chint.com                                                                 
**** Version:     V1.0                                                                               
**** Date:        2016-7-14                                                                          
****                                                                                                 
**** note:�޸���ʷ��¼�б�ÿ���޸ļ�¼Ӧ�����޸����ڡ��޸���                                          
**** 1.  Author:                                                                                     
****     Version:                                                                                    
****     Date :                                                                                      
**** 2.  Author:                                                                                     
****     Version:                                                                                       
****     Date:
****                                                                                        
****  addtogroup:Library                                                             
**********************************************************************************************************/

/*--------------------------------- �ļ�����˵�� -------------------------------------------------------*/
/*
 *  ���ļ����к�����ǰ׺Ϊxxxx_
 *  �ļ��������Ͷ��⺯��������ļ����ײ���������������Ҫ���ڵ�һ��λ��;
 *  ����ע�Ͳ��ñ�׼ģ�壬�����ڲ�ע�Ͳ���//;
 *  ����ע�ͽ϶�Ĳ��֣���������һ��ע�ͷ���Ȼ����ϸ˵�������ļ���β��;
 *--------------------------------- �ļ�����˵�� -------------------------------------------------------*/
 
/**���βεĺ�����ʽ:*/
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    xx��������
 *
 *  @param    xx :
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
/**���βεĺ�����ʽ:*/
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    �ϵ����п������óɳ�ʼ״̬������ɸ�����Ҫ����������
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
 
/*----------------< �����ļ� >----------------------------------*/

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
	{ 'z' , DRV_LCD_8_MSK__A | DRV_LCD_8_MSK__G | DRV_LCD_8_MSK__D 	  				 										  },   //������͸֧�������ܴ���
	#endif
};
#define	LCD_CHAR_TABLE_ROWS	(sizeof(LCD_Char_Table)/2)

 
/*----------------< �������� >----------------------------------*/
typedef struct	
{        
	ulong32   				ID;			///* �̶��ַ� *///    
    uchar8*   				Addr;		///* ���ݵ�ַ *///  
	uchar8                  Len;		///* ��ʾ���ݳ��� *///
	uchar8                  Dots;		///* С��λ����FF��ʾλ���ɱ� *///
	uchar8                  StartPos;	///* ��ʼ��ʾλ�� *///
}GStr_Disp_Type;
#if(METER_TYPE==METER_TYPE_DDSYU666)
/*----------------< �궨���� >----------------------------------*/
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
#define disp_bianchengfu    { GStr_DisplayPara.ucLCDDrvDispBuf[ 3-1] |= _BIT5; }   //��������Կ���š���ʾΪTIME  
#define disp_qinggoudian    { GStr_DisplayPara.ucLCDDrvDispBuf[ 7-1] |= _BIT5; }
#define disp_lazha          { GStr_DisplayPara.ucLCDDrvDispBuf[ 6-1] |= _BIT4; }
#define disp_touzhifu       { GStr_DisplayPara.ucLCDDrvDispBuf[23-1] |= _BIT5; }// ��ʱ��ʾT��ʾ͸֧
#define disp_tunji          NOP()
#define disp_yuan           { GStr_DisplayPara.ucLCDDrvDispBuf[ 5-1] |= _BIT5; }
#define disp_kWh            { GStr_DisplayPara.ucLCDDrvDispBuf[ 5-1] |= _BIT4; GStr_DisplayPara.ucLCDDrvDispBuf[ 4-1] |= (_BIT4|_BIT2|_BIT1); }
#define disp_shijian2       { GStr_DisplayPara.ucLCDDrvDispBuf[40-1] |= _BIT0; }            //С����P2
#define disp_Dot4           { GStr_DisplayPara.ucLCDDrvDispBuf[38-1] |= _BIT0; }            //С����P3
#define disp_Dot3           { GStr_DisplayPara.ucLCDDrvDispBuf[ 3-1] |= _BIT0; }            //С����P5   ʱ���4
#define disp_Dot2           { GStr_DisplayPara.ucLCDDrvDispBuf[ 7-1] |= _BIT0; }            //С����P6
#define disp_shijian1       { GStr_DisplayPara.ucLCDDrvDispBuf[40-1] |= _BIT4; }            //С����P1
#define disp_shijian3       { GStr_DisplayPara.ucLCDDrvDispBuf[ 3-1] |= _BIT4; }          //С����P4
//#define disp_U              { GStr_DisplayPara.ucLCDDrvDispBuf[ 8-1] |= _BIT4; }            //U ��־
//#define disp_I              { GStr_DisplayPara.ucLCDDrvDispBuf[ 8-1] |= _BIT5; }            //I ��־
#define disp_V              { GStr_DisplayPara.ucLCDDrvDispBuf[ 4-1] |= _BIT1; }
#define disp_I              { GStr_DisplayPara.ucLCDDrvDispBuf[ 4-1] |= _BIT3; }
#define disp_kW             { GStr_DisplayPara.ucLCDDrvDispBuf[ 5-1] |= _BIT4; GStr_DisplayPara.ucLCDDrvDispBuf[ 4-1] |= (_BIT2|_BIT1); }

/*----------------< �������� >----------------------------------*/
 
#define	MAIN_DISP_AREA_NUM_MAX	7	// ����������������
const unsigned char code LCD_SEG_CHAR_NUM1[MAIN_DISP_AREA_NUM_MAX][7]=
{
	{ 37, 38, 38, 39, 22, 22, 39 },	// ��1������ABCDEFG��Ӧ��seg	// С���� ��
//	{  1,  1,  1,  1,  1,  1,  1 },	// ��2������ABCDEFG��Ӧ��seg ������ʵ�ǻ�������Ӧ�ĵ�ַƫ��//��
	{ 24, 23, 23, 24, 24, 24, 23 },	// ��3������ABCDEFG��Ӧ��seg
	{ 22, 40, 40, 22, 22, 22, 40 },	// ��4������ABCDEFG��Ӧ��seg
	{ 39, 38, 38, 39, 39, 39, 38 },	// ��5������ABCDEFG��Ӧ��seg
	{ 37,  3,  3, 37, 37, 37,  3 },	// ��6������ABCDEFG��Ӧ��seg
	{  8,  7,  7, 8 ,  8,  8,  7 },	// ��7������ABCDEFG��Ӧ��seg
	{  6,  5,  5, 6 ,  6,  6,  5 },	// ��8������ABCDEFG��Ӧ��seg 
};
const unsigned char code LCD_COM_CHAR_NUM1[MAIN_DISP_AREA_NUM_MAX][7]=
{
	{  5,  5,  4,  4,  4,  5,  5 },	// ��1������ABCDEFG��Ӧ��com	// С���� ��
//	{  3,  3,  1,  0,  1,  2,  2 },	// ��2������ABCDEFG��Ӧ��com	������ܵ�SEG��δ���ӣ�����ʾ
	{  3,  3,  1,  0,  1,  2,  2 },	// ��3������ABCDEFG��Ӧ��com
	{  3,  3,  1,  0,  1,  2,  2 },	// ��4������ABCDEFG��Ӧ��com
	{  3,  3,  1,  0,  1,  2,  2 },	// ��5������ABCDEFG��Ӧ��com
	{  3,  3,  1,  0,  1,  2,  2 },	// ��6������ABCDEFG��Ӧ��com
	{  3,  3,  1,  0,  1,  2,  2 },	// ��7������ABCDEFG��Ӧ��com
	{  3,  3,  1,  0,  1,  2,  2 },	// ��8������ABCDEFG��Ӧ��com
};
static  GStr_Disp_Type code Disp_Table[]=
{
	{0x00000000,		&GStr_Energy.ucaFw_Energy[0]  ,        4,	2,	1, },   ///* 0��ǰ����	
	{0x00010000,		&GStr_Energy.ucaFw_Energy[0]  ,        4,	2,	1, },   ///* 1��ǰ�������
	{0x00020000,		&GStr_Energy.ucaBk_Energy[0]  ,        4,	2,	1, },   ///* 2��ǰ�������             
	{0x04000401,		&GStr_MeterIFO.ucaCommAddr[0] ,        3,	0,	2, },   ///* 3ͨ�ŵ�ַ��4	
	{0x04000401,		&GStr_MeterIFO.ucaCommAddr[3] ,        3,	0,	2, },   ///* 4ͨ�ŵ�ַ��8
	{0x04000402,		&GStr_MeterIFO.ucaMeterID[0]  ,        3,	0,	2, },   ///* 5��Ÿ�4
	{0x04000402,		&GStr_MeterIFO.ucaMeterID[3]  ,        3,	0,	2, },   ///* 6��ŵ�8
	{0x0400040E,		&GStr_MeterIFO. ucaUserID[0]  ,        3,	0,	2, },   ///* 7�ͻ���Ÿ�4                    
	{0x0400040E,		&GStr_MeterIFO. ucaUserID[3]  ,        3,	0,	2, },   ///* 8�ͻ���ŵ�8
	{0x02800020,	    &GStr_PRICE.ucaPrice[0]       ,        4,	4,	1, },	///* 9���                       
	{0x00900200,		&GStr_Money.ucaRemainMoney[0] ,        4,	2,	1, },	///* 10���                       
	{0x00900201,	    &GStr_Money.ucaTickMoney[0]   ,        4,	2,	1, },	///* 11͸֧���      
	{0x04001001,	    &GStr_MoneyPara.ucaAlarmMoneyL1[0]   , 4,	2,	1, },	///* 12�������1
    {0x04001002,	    &GStr_MoneyPara.ucaAlarmMoneyL2[0]   , 4,	2,	1, },	///* 13�������2
    {0x04090B01,        &GStr_MoneyPara.ucaOverLoadVal[0],     3,	4,	3, },   ///* 14���ع���
	{0x02010100,		&GStr_UIPDisplay.ucVoltageA[1],        3,	2,	3, },   ///* 15A���ѹ
	{0x02020100,		&GStr_UIPDisplay.ucCurrentA[1],        3,	3,	3, },   ///* 16A�����
	{0x02030000,		&GStr_UIPDisplay.ucPower[1],           3,	4,	3, },   ///* 17���й�����
	{0x02030100,		&GStr_UIPDisplay.ucPowerA[1],          3,	4,	3, },   ///* 18A���й�����,	
	{0x02060000,		&GStr_UIPDisplay.ucFactory[2],         2,	3,	5, },   ///* 19�ܹ�������
	{0x02060100,		&GStr_UIPDisplay.ucFactoryA[2],        2,	3,	5, },   ///* 20A�๦������,	
	{0x02800002,        &GStr_UIPDisplay.ucFrequency[2],       2,	2,	5, },   ///* 21A����Ƶ��,	
	{0x04000409,        &GStr_UIPDisplay.ucMeterConst[0],      3,	0, 	3, },   ///* 22 �й�����
#if(METER_TYPE==METER_TYPE_DTSY666)
    {0x02010200,        &GStr_UIPDisplay.ucVoltageB[1],        3,   2,  3, },   ///* 22B���ѹ,	
	{0x02010300,		&GStr_UIPDisplay.ucVoltageC[1],        3,   2,  3, },   ///* 23C���ѹ,		
	{0x02020200,        &GStr_UIPDisplay.ucCurrentB[1],        3,   3,  3, },   ///* 24B�����,	
	{0x02020300,		&GStr_UIPDisplay.ucCurrentC[1],        3,   3,  3, },   ///* 25C�����,			
	{0x02030200,		&GStr_UIPDisplay.ucPowerB[1]  ,        3,   4,  3, },   ///* 26B���й�����
	{0x02030300,		&GStr_UIPDisplay.ucPowerC[1]  ,        3,   4,  3, },   ///* 27C���й�����,	
	{0x02060200,		&GStr_UIPDisplay.ucFactoryB[2],        2,   3,  5, },   ///* 28B��������
	{0x02060300,		&GStr_UIPDisplay.ucFactoryC[2],        2,   3,  5, },   ///* 29C�๦������,
#endif

	{0xFFFFFFFF,		0,                                     0,   0,  0, },	///* ȫ��  ʼ�������һ��
};
//#if(METER_TYPE==METER_TYPE_DTSY666)
//	#define   DispMaxNum           31   ///* Ŀǰ31����������չ
//#else
	#define   DispMaxNum           sizeof(Disp_Table)/sizeof(GStr_Disp_Type)   ///* Ŀǰ23����������չ
//#endif
	
	
#endif

#if( (METER_TYPE==METER_TYPE_DDSY666) || ( METER_TYPE==METER_TYPE_DTSY666 ) )
/*----------------< �궨���� >----------------------------------*/
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
#define disp_shijian2       ( GStr_DisplayPara.ucLCDDrvDispBuf[16] |= _BIT1 )            //С����P2
#define disp_Dot4           ( GStr_DisplayPara.ucLCDDrvDispBuf[14] |= _BIT1 )            //С����P3
#define disp_Dot3           ( GStr_DisplayPara.ucLCDDrvDispBuf[12] |= _BIT1 )            //С����P5   ʱ���4
#define disp_Dot2           ( GStr_DisplayPara.ucLCDDrvDispBuf[10] |= _BIT1 )            //С����P6
#define disp_shijian1       ( GStr_DisplayPara.ucLCDDrvDispBuf[16] |= _BIT5 )            //С����P1
#define disp_shijian3       ( GStr_DisplayPara.ucLCDDrvDispBuf[12] |= _BIT5 )            //С����P4




/*----------------< �������� >----------------------------------*/

#define	MAIN_DISP_AREA_NUM_MAX	8
const unsigned char code LCD_SEG_CHAR_NUM1[MAIN_DISP_AREA_NUM_MAX][7]=
{
	{  1,  1,  1,  1,  2,  2,  2 },	// ��1������ABCDEFG��Ӧ��seg ������ʵ�ǻ�������Ӧ�ĵ�ַƫ��
	{ 38, 38, 38, 38, 37, 37, 37 },	// ��2������ABCDEFG��Ӧ��seg
	{ 40, 40, 40, 40, 39, 39, 39 },	// ��3������ABCDEFG��Ӧ��seg
	{ 16, 16, 16, 16, 17, 17, 17 },	// ��4������ABCDEFG��Ӧ��seg
	{ 14, 14, 14, 14, 15, 15, 15 },	// ��5������ABCDEFG��Ӧ��seg
	{ 12, 12, 12, 12, 13, 13, 13 },	// ��6������ABCDEFG��Ӧ��seg
	{ 10, 10, 10, 10, 11, 11, 11 },	// ��7������ABCDEFG��Ӧ��seg
	{ 10, 16, 15, 14, 13, 11, 12 },	// ��8������ABCDEFG��Ӧ��seg 
};
const unsigned char code LCD_COM_CHAR_NUM1[MAIN_DISP_AREA_NUM_MAX][7]=
{
	{  4,  3,  2,  1,  2,  4,  3 },	// ��1������ABCDEFG��Ӧ��com
	{  4,  3,  2,  1,  2,  4,  3 },	// ��2������ABCDEFG��Ӧ��com
	{  4,  3,  2,  1,  2,  4,  3 },	// ��3������ABCDEFG��Ӧ��com
	{  4,  3,  2,  1,  2,  4,  3 },	// ��4������ABCDEFG��Ӧ��com
	{  4,  3,  2,  1,  2,  4,  3 },	// ��5������ABCDEFG��Ӧ��com
	{  4,  3,  2,  1,  2,  4,  3 },	// ��6������ABCDEFG��Ӧ��com
	{  4,  3,  2,  1,  2,  4,  3 },	// ��7������ABCDEFG��Ӧ��com
	{  0,  0,  0,  0,  0,  0,  0 },	// ��8������ABCDEFG��Ӧ��com
};

/*----------------< �������� >----------------------------------*/ 
static  GStr_Disp_Type code Disp_Table[]=
{
	{0x00000000,		&GStr_Energy.ucaFw_Energy[0]  ,        4,	2, 	1, },   ///* 0��ǰ����	
	{0x00010000,		&GStr_Energy.ucaFw_Energy[0]  ,        4,	2, 	1, },   ///* 1��ǰ�������
	{0x00020000,		&GStr_Energy.ucaBk_Energy[0]  ,        4,	2, 	1, },   ///* 2��ǰ�������             
	{0x04000401,		&GStr_MeterIFO.ucaCommAddr[0] ,        2,	0, 	5, },   ///* 3ͨ�ŵ�ַ��4	
	{0x04000401,		&GStr_MeterIFO.ucaCommAddr[2] ,        4,	0, 	1, },   ///* 4ͨ�ŵ�ַ��8
	{0x04000402,		&GStr_MeterIFO.ucaMeterID[0]  ,        2,	0, 	5, },   ///* 5��Ÿ�4
	{0x04000402,		&GStr_MeterIFO.ucaMeterID[2]  ,        4,	0, 	1, },   ///* 6��ŵ�8
	{0x0400040E,		&GStr_MeterIFO. ucaUserID[0]  ,        2,	0, 	5, },   ///* 7�ͻ���Ÿ�4                    
	{0x0400040E,		&GStr_MeterIFO. ucaUserID[2]  ,        4,	0, 	1, },   ///* 8�ͻ���ŵ�8
	{0x02800020,	    &GStr_PRICE.ucaPrice[0]       ,        4,	4, 	1, },	///* 9���                       
	{0x00900200,		&GStr_Money.ucaRemainMoney[0] ,        4,	2, 	1, },   ///* 10���                       
	{0x00900201,	    &GStr_Money.ucaTickMoney[0]   ,        4,	2, 	1, },	///* 11͸֧���      
	{0x04001001,	    &GStr_MoneyPara.ucaAlarmMoneyL1[0]   , 4,	2, 	1, },	///* 12�������1
    {0x04001002,	    &GStr_MoneyPara.ucaAlarmMoneyL2[0]   , 4,	2, 	1, },	///* 13�������2
    {0x04090B01,        &GStr_MoneyPara.ucaOverLoadVal[0],     3,	4, 	3, },   ///* 14���ع���
	{0x02010100,		&GStr_UIPDisplay.ucVoltageA[1],        3,	2, 	3, },   ///* 15A���ѹ
	{0x02020100,		&GStr_UIPDisplay.ucCurrentA[1],        3,	3, 	3, },   ///* 16A�����
	{0x02030000,		&GStr_UIPDisplay.ucPower[1],           3,	4, 	3, },   ///* 17���й�����
	{0x02030100,		&GStr_UIPDisplay.ucPowerA[1],          3,	4, 	3, },   ///* 18A���й�����,	
	{0x02060000,		&GStr_UIPDisplay.ucFactory[2],         2,	3, 	5, },   ///* 19�ܹ�������
	{0x02060100,		&GStr_UIPDisplay.ucFactoryA[2],        2,	3, 	5, },   ///* 20A�๦������,	
	{0x02800002,        &GStr_UIPDisplay.ucFrequency[2],       2,	2, 	5, },   ///* 21A��������,	
	{0x04000409,        &GStr_UIPDisplay.ucMeterConst[0],      3,	0, 	3, },   ///* 22�й�����
#if(METER_TYPE==METER_TYPE_DTSY666)
    {0x02010200,        &GStr_UIPDisplay.ucVoltageB[1],        3,   2,  3, },   ///* 22B���ѹ,	
	{0x02010300,		&GStr_UIPDisplay.ucVoltageC[1],        3,   2,  3, },   ///* 23C���ѹ,		
	{0x02020200,        &GStr_UIPDisplay.ucCurrentB[1],        3,   3,  3, },   ///* 24B�����,	
	{0x02020300,		&GStr_UIPDisplay.ucCurrentC[1],        3,   3,  3, },   ///* 25C�����,			
	{0x02030200,		&GStr_UIPDisplay.ucPowerB[1]  ,        3,   4,  3, },   ///* 26B���й�����
	{0x02030300,		&GStr_UIPDisplay.ucPowerC[1]  ,        3,   4,  3, },   ///* 27C���й�����,	
	{0x02060200,		&GStr_UIPDisplay.ucFactoryB[2],        2,   3,  5, },   ///* 28B��������
	{0x02060300,		&GStr_UIPDisplay.ucFactoryC[2],        2,   3,  5, },   ///* 29C�๦������,
#endif
	{0xFFFFFFFF,		0,                                     0,   0,  0, },	///* ȫ��  ʼ�������һ��
};

#define   DispMaxNum           sizeof(Disp_Table)/sizeof(GStr_Disp_Type)   ///* Ŀǰ23����������չ

	
#endif
/*----------------< �������� >----------------------------------*/
void ApiDisp_DisplayTask(void);
uchar8 ApiGet_Lcd_Num(ulong32 DataId,uchar8 ScreenNum);
ulong32 ApiGet_Lcd_ID(uchar8 v_LcdNum);
static void ApiDisplay_NumData( unsigned char Num, unsigned char show );
static void ApiDisp_ShowNum(uchar8 ShowStartPos,uchar8 len, uchar8* Show, uchar8 v_ucDots);
static void APiDisp_Const(uchar8 Dispcnt);
void APiDisp_LcdledControl();
/*----------------< �������� >----------------------------------*/
uchar8 ApiGet_Lcd_Num(ulong32 DataId,uchar8 ScreenNum)
{
	uchar8 i,v_LcdNum;
	for(i=1;i<(DispMaxNum+1);i++)///û�����0����һ��Ϊ���1������0Ϊ��֧�ָñ�ʶ
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
    return 0x00;///��֧����ʾ
}

ulong32 ApiGet_Lcd_ID(uchar8 v_LcdNum)
{
	ulong32 V_ulDI3DI2DI1DI0;
    if(v_LcdNum>=DispMaxNum)
	{
		V_ulDI3DI2DI1DI0=0x00000000;///���ֵ��ʾ��ǰ������
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
		V_ucCombit = LCD_COM_CHAR_NUM1[v_ucNumPos-1][V_ucCnti]; 	// �ҵ�ABCDEFG��Ӧ��com
		V_ucPosBit = LCD_SEG_CHAR_NUM1[v_ucNumPos-1][V_ucCnti]-1;	// �ҵ�ABCDEFG��Ӧ��seg 
		
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

	j = len*2-v_ucDots;	//0λС��
	
	k = 0;
	if( GStr_DisplayPara.ucDisp_0_flag)///
	{
		for( i=0; i<len; i++ )
		{
			if(((((*(Show+i))>>4)&0x0F) == 0) && (k == 0)&&((2*(i+1)-1)<j))   ///* ��i���ֽڵĸ�λҪС��������λ������Ч����ֻ��һλ��Ϊ0��������
			{
				ShowStartPos++;//��λΪ0����ʾ
			}
			else
			{
				k=1;
				ApiDisplay_NumData( ShowStartPos++, (((*(Show+i))>>4)&0x0F)+0x30 ); 
			}
			
			if(((((*(Show+i))>>0)&0x0F) == 0) && (k == 0)&& ((2*(i+1))<j)) ShowStartPos++;///* ��i���ֽڵĵ�λҪС��������λ������Ч����ֻ��һλ��Ϊ0��������
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
	///*��������
	GStr_DisplayPara.ucDisp_0_flag=0;///�����־��0

	if((DispMaxNum-1)==Dispcnt)
	{
		LibPub_MemSetBytes( GStr_DisplayPara.ucLCDDrvDispBuf, 0xFF, 40 );
		return;
	}
    switch (Dispcnt)
	{
		case 0://��ǰ�ܵ���
		{
			disp_dangqian;
			disp_dianliang;
		    disp_kWh;
		    disp_Dot2;
		    GStr_DisplayPara.ucDisp_0_flag=1;
		}break;
		case 1://��ǰ�������
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
		case 2://��ǰ�������
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
		

		
		case 9: ///���
		{
			disp_dianjia;
		    disp_Dot4;
		    disp_yuan;
			GStr_DisplayPara.ucDisp_0_flag=1;
		}break;
		
        case 10:   ///ʣ����
		{
			disp_yu_e;
		    disp_Dot2;
		    disp_yuan;
			GStr_DisplayPara.ucDisp_0_flag=1;
		}	break;

        case 11:  ///͸֧���
		{
			#if(METER_TYPE==METER_TYPE_DDSYU666)
			ApiDisplay_NumData( 1, 'z' );               ///��ʾ͸֧	 T+��
			disp_touzhifu;
			#endif
			disp_touzhi;
		    disp_Dot2;
		    disp_yuan;
			GStr_DisplayPara.ucDisp_0_flag=1;
		}break;
		
		case 12:///�������1   
		{
			disp_Dot2;
			disp_yuan;
			GStr_DisplayPara.ucDisp_0_flag=1;
		}break;
		
		case 13:///�������2
		{
			disp_Dot2;
			disp_yuan;
			GStr_DisplayPara.ucDisp_0_flag=1;
		}break;
		
		case 14:///���ع���
		{
			ApiDisplay_NumData( 1, 'O' );///��ʾOP
			ApiDisplay_NumData( 2, 'P' );
			disp_Dot4;
			GStr_DisplayPara.ucDisp_0_flag=1;
			
		}break;
		
		case 15:///A���ѹ 
		#if(METER_TYPE==METER_TYPE_DTSY666)
		case 23:///B���ѹ
		case 24://C���ѹ	
		#endif
		{
			#if(METER_TYPE==METER_TYPE_DDSYU666)
	        disp_V;
			ApiDisplay_NumData( 2, 'U' ); ///��ʾU
			#else
			ApiDisplay_NumData( 1, 'U' ); ///��ʾU
			if(Dispcnt==15)
			{
				ApiDisplay_NumData( 2, 'A' ); ///��ʾA
			}
			#endif
			#if(METER_TYPE==METER_TYPE_DTSY666)
			else if(Dispcnt==23)
			{
				ApiDisplay_NumData( 2, 'B' ); ///��ʾB
			}
			else 
			{
				ApiDisplay_NumData( 2, 'C' ); ///��ʾC
			}	
			#endif
			disp_Dot2;
			
			GStr_DisplayPara.ucDisp_0_flag=1;
			
		}break;
		
		case 16:///A�����
		#if(METER_TYPE==METER_TYPE_DTSY666)	
		case 25://B�����
		case 26://C�����	
		#endif
		{
			#if(METER_TYPE==METER_TYPE_DDSYU666)
	        disp_I;
			ApiDisplay_NumData( 2, 'I' ); ///��ʾU
			#else
			ApiDisplay_NumData( 1, 'I' ); ///��ʾI
			if(Dispcnt==16)
			{
				ApiDisplay_NumData( 2, 'A' ); ///��ʾA
			}
			#endif
			#if(METER_TYPE==METER_TYPE_DTSY666)	
			else if(Dispcnt==25)//B�����
			{
				ApiDisplay_NumData( 2, 'B' ); ///��ʾB
			}
			else
			{
				ApiDisplay_NumData( 2, 'C' ); ///��ʾC
			}
			#endif
			disp_Dot3;
			
			GStr_DisplayPara.ucDisp_0_flag=1;
			
		}break;
		
		case 17:///���й�����
		case 18:///A�й�����
		#if(METER_TYPE==METER_TYPE_DTSY666)		
		case 27://B�๦��
		case 28://C�๦��	
		#endif
		{
			#if(METER_TYPE==METER_TYPE_DDSYU666)
	        disp_kW;
			ApiDisplay_NumData( 2, 'P' ); ///��ʾU
			#else
			ApiDisplay_NumData( 1, 'P' ); ///��ʾP
			if(Dispcnt==18)
			{
				ApiDisplay_NumData( 2, 'A' ); ///��ʾA	
			}
			#endif
			#if(METER_TYPE==METER_TYPE_DTSY666)	
			else if(Dispcnt==27)///B�๦��
			{
				ApiDisplay_NumData( 2, 'B' ); ///��ʾB	
			}
			else if(Dispcnt==28)///C�๦��
			{
				ApiDisplay_NumData( 2, 'C' ); ///��ʾC
			}
			#endif
			disp_Dot4;
			GStr_DisplayPara.ucDisp_0_flag=1;
			
		}break;
		
		case 19:///�ܹ�������
		case 20:///A��������
		#if(METER_TYPE==METER_TYPE_DTSY666)			
		case 29://B�๦������
		case 30://C�๦������	
		#endif
		{
			#if(METER_TYPE==METER_TYPE_DDSYU666)
			ApiDisplay_NumData( 2, 'F' ); ///��ʾU
			ApiDisplay_NumData( 3, 't' ); ///��ʾU
			#else
			if(Dispcnt==20)
			{
				ApiDisplay_NumData( 2, 'A' ); ///��ʾA
			}
			#endif
			#if(METER_TYPE==METER_TYPE_DTSY666)		
			else if(Dispcnt==29)
			{
				ApiDisplay_NumData( 2, 'B' ); ///��ʾB
			}
			else if(Dispcnt==30)
			{
				ApiDisplay_NumData( 2, 'C' ); ///��ʾC
			}
			#endif
			disp_Dot3;
			GStr_DisplayPara.ucDisp_0_flag=1;
		}break;
		
		case 21:///Ƶ��
		{
			#if(METER_TYPE==METER_TYPE_DDSYU666)
			ApiDisplay_NumData( 2, 'F' ); ///��ʾU
			#else
			ApiDisplay_NumData( 1, 'F' ); ///��ʾF
			#endif
			disp_Dot2;
			GStr_DisplayPara.ucDisp_0_flag=1;
		}break;
		
		case 22:///�й�����
		{
			GStr_DisplayPara.ucDisp_0_flag=1;
		}break;
		
		

		default:
		break;
    }
	V_ucDots = Disp_Table[Dispcnt].Dots;
	#if(METER_TYPE!=METER_TYPE_DDSYU666)     //������������ʾ��
	ApiDisp_ShowNum( Disp_Table[Dispcnt].StartPos, Disp_Table[Dispcnt].Len, Disp_Table[Dispcnt].Addr, V_ucDots);
	#else  //�������ʾ����APiDisp_Dynamic
	if(F_FACTORY_MODE==(GStr_Flag.ucMeterMode&F_FACTORY_MODE))
	{
		if(GStr_DisplayPara.usDispCnt%2)  //������˸
		{
	      ApiDisp_ShowNum( Disp_Table[Dispcnt].StartPos, Disp_Table[Dispcnt].Len, Disp_Table[Dispcnt].Addr, V_ucDots);
		}
	}
	else	///* ���⵼������ݳ���
	{
		ApiDisp_ShowNum( Disp_Table[Dispcnt].StartPos, Disp_Table[Dispcnt].Len, Disp_Table[Dispcnt].Addr, V_ucDots);
		if(!(GStr_Flag.ucRunState2&F_RUN_EsamKeyFlag))///��Կ��������Կ�ж�  
		{
				disp_bianchengfu;
		}
	}  
	#endif
}

void APiDisp_Dynamic(void)
{
	GStr_DisplayPara.usDispCnt++;
	
	#if(METER_TYPE!=METER_TYPE_DDSYU666)   //�����û��Ӳij��ť��
	if((F_FACTORY_MODE==(GStr_Flag.ucMeterMode&F_FACTORY_MODE))||(F_KEY_ACKTION_DOWN==(GStr_Flag.ucFactoryKey&F_KEY_ACKTION_DOWN)))
	///* ӲIJ�̽ӻ�����IJ��Ч��˸��ʾ��̷���
	{
		if(GStr_DisplayPara.usDispCnt%2)
		{
			disp_bianchengfu;
		}
	}///������˸��ʾ��̷���
	else
	{
			if(!(GStr_Flag.ucRunState2&F_RUN_EsamKeyFlag))///��Կ
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
	{///1��������2��������ʣ����Ϊ0ʱ���빺����˸
			if(GStr_DisplayPara.usDispCnt%2)
			{

				disp_qinggoudian;///�빺����˸
				
			}
	}
	if(GStr_Flag.ucRunState1 &F_RUN_OVER_DRAFT)
	{///͸֧��͸֧���빺�糣��
			disp_touzhifu;///͸֧
			disp_qinggoudian;///�빺�糣��
	}
	
	if((GStr_Counter.ucPasswordErr_Cnt[0]>=3)||(GStr_Counter.ucPasswordErr_Cnt[1]>=3)||
		(GStr_Counter.ucPasswordErr_Cnt[2]>=3)||(GStr_Flag.ucRunState2&F_RUN_INTAUTH_MACNumErrFlag))
	{///�����3�λ��������֤����
			if(GStr_DisplayPara.usDispCnt%2)
			{
					disp_kWh;///��˸kWh
			}
//			else
//			{
//				 GStr_DisplayPara.ucLCDDrvDispBuf[9]  &= ~_BIT5 ;///���kwh�Ļ���
//			}
	
	}
	


}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    �������
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void APiDisp_LcdledControl()	//�������
{
	if( GStr_DisplayPara.ucBackLightTime != 0 ) GStr_DisplayPara.ucBackLightTime--;

    if( GStr_Flag.ucRunState1& B0011_1111 )///���ʷ��򲻵������⣬ͨ�ű�����һ��������͸֧������ع��ʷ���ȵ�������
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
 *  @brief    ˢ����ʾ����
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
	

	
 // @brief  ������磬��ֱ���˳�����ˢ��
	/* ��Ҫ���ӵ����ж� */
	if ( (GStr_Flag.ucSystem & F_PWON)==0 )	///* �����˾�ֱ���˳� *///
	{
		return;
	}

	// 500msˢ��һ����ʾ
	if ( _TRUE == LibPub_GetDiffTime( GStr_DisplayPara.ulDispUpdataTime, LibPub_GetTimerBeat(), LCD_UPTATA_TIME) )
	{
		GStr_DisplayPara.ulDispUpdataTime =  LibPub_GetTimerBeat();
		GStr_Flag.ucDisp |= F_DISP_UPDATA;			// ����ʾˢ�±�־ 
		
		GStr_DisplayPara.ulDisptimer--;
		if(GStr_DisplayPara.ulDisptimer==0)
		{
		    GStr_DisplayPara.ulDisptimer = GStr_DisplayPara.ucDispDurTime*1000/LCD_UPTATA_TIME;///����ʾʱ��Ϊѭ��ʱ�䣬ת��Ϊms
			GStr_DisplayPara.ucDispNum++;
			
			if( (GStr_Flag.ucDisp & F_DISP_KEYDISP) || (GStr_Flag.ucDisp & F_DISP_COM_DIASP) || ( GStr_Flag.ucDisp & F_DISP_DISPALL ) )
			{
				GStr_DisplayPara.ucFirstKeyDisp = 0;		// ����ѭ����ʾʱ�䵽���´ΰ�����ʾ���µ�һ����ʾ
				GStr_Flag.ucDisp = 0;///*��ʾʱ�䵽������е���ʾ��־����ѭ����ʾ��־
				GStr_Flag.ucDisp |= F_DISP_AUTODISP;	// ����ѭ����ʾʱ�䵽����ʼѭ����ʾ���ӵ�һ����ʼ
				GStr_DisplayPara.ucDispNum = 0;
            }
		}
		
		if(GStr_Flag.ucDisp & F_DISP_KEYDISP)	// ������ʾ
		{
			Dispcnt = GStr_DisplayPara.ucKeyDisptable[GStr_DisplayPara.ucDispNum];
		} 
		else if(GStr_Flag.ucDisp & F_DISP_COM_DIASP)	// ͨ����ʾ
		{
			Dispcnt=GStr_DisplayPara.ucDispNum;	// ӳ�������ʾ���� 
		} 
		else if(GStr_Flag.ucDisp & F_DISP_DISPALL)	// ȫ��
		{
			LCDDrv_SetLcdBuff(0xFF);
			return;
		} 
		else if(GStr_Flag.ucDisp & F_DISP_AUTODISP) // �Զ�ѭ����ʾ
		{
			if(GStr_DisplayPara.ucDispNum>=GStr_DisplayPara.ucAutoDispNum)
			{
				GStr_DisplayPara.ucDispNum=0;
			}
			Dispcnt=GStr_DisplayPara.ucAutoDisptable[GStr_DisplayPara.ucDispNum];	
		}	
		
		// ׼����ʾ����
		if(Dispcnt>=DispMaxNum)
		{
			Dispcnt=0;
		}
		APiDisp_Const(Dispcnt);
		APiDisp_Dynamic();
		LCDDrv_DispRamUpdata();	
	}
}