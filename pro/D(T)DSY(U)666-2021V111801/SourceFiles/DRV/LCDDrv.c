/*******************************************************************************************************
**** Copyright��  (c)Copyright 2019,�㽭��̩�����Ǳ��������ι�˾,���ܱ�Ӧ���з�                       
****                            All rights reserved.                                                 
**** FileName:    LCDDrv.c                                                                          
**** Brief:       LCD�����ļ�                                                                     
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

#include "..\SourceFiles\PUB\Include.h"
/*----------------< �궨���� >----------------------------------*/


/*----------------< �������� >----------------------------------*/


/*----------------< �������� >----------------------------------*/

/*----------------< �������� >----------------------------------*/
static void LCDDrv_SgeComConfig(void);
static void LCDDrv_SetLcdBuff( uchar8 v_ucVal );
static void LCDDrv_PwOnRegCfg(void);
//static void LCDDrv_DispRamUpdata(void);

void LCDDrv_Init( uchar8 v_ucPowerStatus );
/*----------------< �������� >----------------------------------*/

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    LCD��ʼ�����ϵ�����µ�
 *
 *  @param    xx :
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

void LCDDrv_Init( uchar8 v_ucPowerStatus )
{
	
	switch( v_ucPowerStatus )
	{
		case POWER_ON:		// �ϵ�״̬LCD��ʼ��
		{
			LCD_OFF()				// �ر���ʾģ��
			LCDDrv_PwOnRegCfg();	// ���üĴ���
			LCDDrv_SgeComConfig(); 	// ����IO
			LCDDrv_SetLcdBuff(0xFF);// ��������
			LCD_ON();				// ����ʾģ��
			RELAYLEDON();///Һ��������ͬʱ������բ��
			LCDLEDON();
		    
			

		}break;
		
		case POWER_OFF:		// ����״̬LCD��ʼ��
		{
			LCD_OFF()				// �ر���ʾģ��
			LCDDrv_PwOnRegCfg();	// ���üĴ���
			LCDDrv_SgeComConfig(); 	// ����IO
			LCDDrv_SetLcdBuff(0x00);// ��������
			
		}break;
		
		default:break;
	} 
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ���������ó�LCD��ʾ����
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void LCDDrv_SgeComConfig(void)
{
#if( METER_TYPE == METER_TYPE_DDSY666 )
	P4SS = P4SS_P4S7 | P4SS_P4S6 | P4SS_P4S5 | P4SS_P4S4;
	P5SS = P5SS_P5S1 | P5SS_P5S0; 
	P6SS = P6SS_P6S7 | P6SS_P6S6 | P6SS_P6S5 | P6SS_P6S4 | P6SS_P6S3 | P6SS_P6S2 | P6SS_P6S1; 
	P7SS = P7SS_P7S0; 
//	P8SS = P8SS_P8S7 | P8SS_P8S6; 
	P9SS = P9SS_P9S7 | P9SS_P9S6 | P9SS_P9S5 | P9SS_P9S4 | P9SS_P9S3 | P9SS_P9S2; // COM���߶���
#endif
	
#if( METER_TYPE == METER_TYPE_DTSY666 )
	P4SS = P4SS_P4S7 | P4SS_P4S6 | P4SS_P4S5 | P4SS_P4S4;
	P5SS = P5SS_P5S1 | P5SS_P5S0; 
	P6SS = P6SS_P6S7 | P6SS_P6S6 | P6SS_P6S5 | P6SS_P6S4 | P6SS_P6S3 | P6SS_P6S2 | P6SS_P6S1; 
	P7SS = P7SS_P7S0; 
//	P8SS = P8SS_P8S7 | P8SS_P8S6; 
	P9SS = P9SS_P9S7 | P9SS_P9S6 | P9SS_P9S5 | P9SS_P9S4 | P9SS_P9S3 | P9SS_P9S2; // COM���߶���
#endif
	
#if( METER_TYPE == METER_TYPE_DDSYU666 )
	P4SS = P4SS_P4S7 | P4SS_P4S6 | P4SS_P4S5 | P4SS_P4S4;
	P5SS = P5SS_P5S7 | P5SS_P5S6 | P5SS_P5S5 | P5SS_P5S4 | P5SS_P5S3 | P5SS_P5S2; 
//	P6SS = P6SS_P6S7 | P6SS_P6S6 | P6SS_P6S5 | P6SS_P6S4 | P6SS_P6S3 | P6SS_P6S2 | P6SS_P6S1; 
	P7SS = P7SS_P7S7 | P7SS_P7S6 | P7SS_P7S5 ; 
//	P8SS = P8SS_P8S7 | P8SS_P8S6; 
	P9SS = P9SS_P9S7 | P9SS_P9S6 | P9SS_P9S5 | P9SS_P9S4 | P9SS_P9S3 | P9SS_P9S2; // COM���߶���	
#endif
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    LCD�������
 *
 *  @param    v_ucVal : Ҫ��������
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void LCDDrv_SetLcdBuff( uchar8 v_ucVal )
{ 
	uchar8 V_ucCnti;
	
	for( V_ucCnti=0; V_ucCnti<40; V_ucCnti++ )
	{
		GStr_DisplayPara.ucLCDDrvDispBuf[V_ucCnti] = v_ucVal;
	}
	
	LCDDrv_DispRamUpdata();
	
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ����LCD���ܼĴ���
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void LCDDrv_PwOnRegCfg(void)
{ 
	if( (LCDCON1 & LCDCON1_DBP_ALL) != LCDCON1_D16_B13_P9 ) // 1/6 DUTY 1/3 BIAS
	{ 
		LCDCON1 &= LCDCON1_DBP_CLR;
		LCDCON1 |= LCDCON1_D16_B13_P9;
	}	
	
	if( (LCDCON1 & LCDCON1_VOUT_ALL) != LCDCON1_VOUT1000 ) // VLCD = 1.000 VOUT
	{ 
		LCDCON1 &= LCDCON1_VOUT_CLR;
		LCDCON1 |= LCDCON1_VOUT1000;
	}	
	
	if( (LCDCON2 & LCDCON2_MOD_ALL) != LCDCON2_MOD60k )	// 010�� ��ͳģʽ��ƫ�õ����ܺ�Ϊ60k
	{ 
		LCDCON2 &= LCDCON2_MOD_CLR;
		LCDCON2 |= LCDCON2_MOD60k;
	}
	
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ����ʾ����д����ʾ�Ĵ���
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void LCDDrv_DispRamUpdata(void)
{
	uchar8 xdata *P_ucLcdBuf = 0x2500;
	uchar8 V_ucCnti;
	
	for ( V_ucCnti = 0; V_ucCnti<40; V_ucCnti++ )
	{
		P_ucLcdBuf[V_ucCnti] = GStr_DisplayPara.ucLCDDrvDispBuf[V_ucCnti];
		GStr_DisplayPara.ucLCDDrvDispBuf[V_ucCnti] = 0;
	}
} 


