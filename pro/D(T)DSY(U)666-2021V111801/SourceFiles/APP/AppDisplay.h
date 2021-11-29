/*******************************************************************************************************
**** Copyright��  (c)Copyright 2019,�㽭��̩�����Ǳ��������ι�˾,���ܱ�Ӧ���з�                       
****                            All rights reserved.                                                 
**** FileName:    AppDisplay.h                                                                          
**** Brief:       ��ʾģ��                                                                      
**** Author:      peter.he@chint.com                                                                 
**** Version:     V1.0                                                                               
**** Date:        2019��3��14��                                                                         
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

#ifndef   _APPDISPLAY_H
#define   _APPDISPLAY_H

/*-------------------------------- H�ļ�ʹ��˵�� -------------------------------------------------------*/
/*
 *  ���ļ��궨���ǰ׺Ϊ:
 *
 */

 
/*----------------< �����ļ� >----------------------------------*/


/*----------------< �궨���� >----------------------------------*/
#if( METER_TYPE == METER_TYPE_DDSY666 )
	#define  LCDLEDON()  		{ GPIO_IOCFG_P9_DIR_O(1);GPIO_IOCFG_P9_SET_0(1); } // �������  
	#define  LCDLEDOFF()  		{ GPIO_IOCFG_P9_DIR_O(1);GPIO_IOCFG_P9_SET_1(1); } // ���ⲻ����  
	#define  RELAYLEDON()  		{ GPIO_IOCFG_P1_DIR_O(3);GPIO_IOCFG_P1_SET_0(3); } // �����Ƶ���  
	#define  RELAYLEDOFF()  	{ GPIO_IOCFG_P1_DIR_O(3);GPIO_IOCFG_P1_SET_1(3); } // �����Ʋ�����  
#endif

#if( METER_TYPE == METER_TYPE_DTSY666 )
	#define  LCDLEDON()  		{ GPIO_IOCFG_P9_DIR_O(1);GPIO_IOCFG_P9_SET_0(1); } // �������  
	#define  LCDLEDOFF()  		{ GPIO_IOCFG_P9_DIR_O(1);GPIO_IOCFG_P9_SET_1(1); } // ���ⲻ����  
	#define  RELAYLEDON()  		{ GPIO_IOCFG_P1_DIR_O(3);GPIO_IOCFG_P1_SET_0(3); } // �����Ƶ���  
	#define  RELAYLEDOFF()  	{ GPIO_IOCFG_P1_DIR_O(3);GPIO_IOCFG_P1_SET_1(3); } // �����Ʋ�����  
#endif
	
#if( METER_TYPE == METER_TYPE_DDSYU666 )
	#define  LCDLEDON()  		{ GPIO_IOCFG_P0_DIR_O(1);GPIO_IOCFG_P0_SET_1(1); } // �������  
	#define  LCDLEDOFF()  		{ GPIO_IOCFG_P0_DIR_O(1);GPIO_IOCFG_P0_SET_0(1); } // ���ⲻ����  
	#define  RELAYLEDON()  		{ GPIO_IOCFG_P0_DIR_O(7);GPIO_IOCFG_P0_SET_1(7); } // �����Ƶ���  
	#define  RELAYLEDOFF()  	{ GPIO_IOCFG_P0_DIR_O(7);GPIO_IOCFG_P0_SET_0(7); } // �����Ʋ�����  
#endif
/*----------------< �������� >----------------------------------*/

/*----------------< �������� >----------------------------------*/
extern void ApiDisp_DisplayTask(void);
extern uchar8 ApiGet_Lcd_Num(ulong32 DataId,uchar8 ScreenNum);
extern ulong32 ApiGet_Lcd_ID(uchar8 v_LcdNum);
void LCDDrv_DispRamUpdata(void);
void LCDDrv_SetLcdBuff( uchar8 v_ucVal );
extern void APiDisp_LcdledControl();





#endif
