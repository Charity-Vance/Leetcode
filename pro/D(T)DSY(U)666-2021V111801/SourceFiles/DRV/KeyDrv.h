/*******************************************************************************************************
**** Copyright��  (c)Copyright 2019,�㽭��̩�����Ǳ��������ι�˾,���ܱ�Ӧ���з�                       
****                            All rights reserved.                                                 
**** FileName:    KeyDrv.c                                                                          
**** Brief:       ��������ͷ�ļ�                                                                      
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

#ifndef   _KEYDRV_H
#define   _KEYDRV_H

/*-------------------------------- H�ļ�ʹ��˵�� -------------------------------------------------------*/
/*
 *  ���ļ��궨���ǰ׺Ϊ:
 *
 */

 
/*----------------< �����ļ� >----------------------------------*/


/*----------------< �궨���� >----------------------------------*/

#define	LCD_DISP_Keydelay_TIME		8	///* ����ȥ��ʱ��40ms *///

#if( METER_TYPE == METER_TYPE_DDSY666 )
	/* I_J�̽ӵ� */
	#define	FACTORYMODE_KEY_INPUT()		GPIO_IOCFG_P5_DIR_I(2)
	#define	FACTORYMODE_KEY_UPON()		GPIO_IOCFG_P5_PUP_O(2)
	#define	FACTORYMODE_KEY_HIGHT		GPIO_IOCFG_P5_STAT_H(2)
	#define	FACTORYMODE_KEY_LOW			GPIO_IOCFG_P5_STAT_L(2)
	/* ���԰��� */
	#define	DISPLAY_KEY_INPUT()			GPIO_IOCFG_P2_DIR_I(2)
	#define	DISPLAY_KEY_UPON()			GPIO_IOCFG_P2_PUP_O(2)
	#define	DISPLAY_KEY_HIGHT			GPIO_IOCFG_P2_STAT_H(2)
	#define	DISPLAY_KEY_LOW				GPIO_IOCFG_P2_STAT_L(2)
#endif


#if( METER_TYPE == METER_TYPE_DTSY666 )
	/* I_J�̽ӵ� */
	#define	FACTORYMODE_KEY_INPUT()		GPIO_IOCFG_P5_DIR_I(2)
	#define	FACTORYMODE_KEY_UPON()		GPIO_IOCFG_P5_PUP_O(2)
	#define	FACTORYMODE_KEY_HIGHT		GPIO_IOCFG_P5_STAT_H(2)
	#define	FACTORYMODE_KEY_LOW			GPIO_IOCFG_P5_STAT_L(2) 
	/* ���԰��� */
	#define	DISPLAY_KEY_INPUT()			GPIO_IOCFG_P1_DIR_I(0)
	#define	DISPLAY_KEY_UPON()			GPIO_IOCFG_P1_PUP_O(0)
	#define	DISPLAY_KEY_HIGHT			GPIO_IOCFG_P1_STAT_H(0)
	#define	DISPLAY_KEY_LOW				GPIO_IOCFG_P1_STAT_L(0)
#endif

#if( METER_TYPE == METER_TYPE_DDSYU666 )// �����û��I-J�̽ӵ�
	/* I_J�̽ӵ� */
	#define	FACTORYMODE_KEY_INPUT()		NOP();//GPIO_IOCFG_P5_DIR_I(2)	//
	#define	FACTORYMODE_KEY_UPON()		NOP();//GPIO_IOCFG_P5_PUP_O(2)
	#define	FACTORYMODE_KEY_HIGHT		NOP();//GPIO_IOCFG_P5_STAT_H(2)
	#define	FACTORYMODE_KEY_LOW			NOP();//GPIO_IOCFG_P5_STAT_L(2)
	/* ���԰��� */
	#define	DISPLAY_KEY_INPUT()			GPIO_IOCFG_P3_DIR_I(2)
	#define	DISPLAY_KEY_UPON()			GPIO_IOCFG_P3_PUP_O(2)
	#define	DISPLAY_KEY_HIGHT			GPIO_IOCFG_P3_STAT_H(2)
	#define	DISPLAY_KEY_LOW				GPIO_IOCFG_P3_STAT_L(2)
#endif
/*----------------< �������� >----------------------------------*/


/*----------------< �������� >----------------------------------*/
extern void DrvKey_FactoryKeyMonitor(void);
extern void DrvKey_DisplayKeyInit(void);
extern void DrvKey_DisplayKeyMonitor(void);





#endif
