/*******************************************************************************************************
**** Copyright��  (c)Copyright 2019,�㽭��̩�����Ǳ��������ι�˾,���ܱ�Ӧ���з�                       
****                            All rights reserved.                                                 
**** FileName:    KeyDrv.c                                                                          
**** Brief:       ���������ļ�                                                                      
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
void DrvKey_FactoryKeyInit(void);
void DrvKey_DisplayKeyInit(void);

void DrvKey_FactoryKeyMonitor(void);
void DrvKey_DisplayKeyMonitor(void);
/*----------------< �������� >----------------------------------*/


/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ����ģʽ�̽ӵ��ʼ������Ҫ���ö̽ӵ�������������߹���
 *
 *  @return   NONE
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void DrvKey_FactoryKeyInit(void)
{
	FACTORYMODE_KEY_INPUT();	// ���ó�����
	FACTORYMODE_KEY_UPON();		// ����������
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ���԰�����ʼ������Ҫ�������԰���������������߹���
 *
 *  @return   NONE
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void DrvKey_DisplayKeyInit(void)
{
	DISPLAY_KEY_INPUT();	// ���ó�����
	DISPLAY_KEY_UPON();		// ����������
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ����ģʽ��ѯ
 *
 *  @return   NONE
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

void DrvKey_FactoryKeyMonitor(void)
{
	// @brief    ����һ�¿���
	DrvKey_FactoryKeyInit();
	#if( METER_TYPE == METER_TYPE_DDSYU666 )
	{  
		GStr_Flag.ucFactoryKey |=  F_KEY_ACKTION_DOWN; // �����û��I_J�̽ӵ㣬ֱ����Ϊ�Ϳ���ͨ�����������
	}
	#else
	{	
		///*ֱ���жϿ���
		if(FACTORYMODE_KEY_LOW)
		{
			GStr_Counter.ucFactoryMode_Cnt++;
			if(GStr_Counter.ucFactoryMode_Cnt>=250)
			{
				GStr_Counter.ucFactoryMode_Cnt=0;
				GStr_Flag.ucFactoryKey |=  F_KEY_ACKTION_DOWN; 	
			}
		}
		else
		{
			GStr_Counter.ucFactoryMode_Cnt=0;
			GStr_Flag.ucFactoryKey &=  ~F_KEY_ACKTION_DOWN;
		}
	}
	#endif
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ���԰�����ѯ
 *
 *  @return   NONE
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void DrvKey_DisplayKeyMonitor(void)
{
	// @brief    ����һ�¿���
	DrvKey_DisplayKeyInit();  

	// @brief    ���һ�¿���״̬
	if( F_KEY_STATUS_IDLE & GStr_Flag.ucDispKey )	// �������״̬�ǿ���
	{
		if( DISPLAY_KEY_LOW )	// �������£�״̬�ı�
		{
			GStr_Flag.ucDispKey |= F_KEY_ACKTION_DOWN;
			GStr_Flag.ucDispKey &= (~F_KEY_STATUS_IDLE);
			GStr_DisplayPara.ucKeydelaytimer = 0;
		}  
	}
	else if( F_KEY_ACKTION_DOWN & GStr_Flag.ucDispKey )
	{
		if( DISPLAY_KEY_LOW )	// ��ʼҪ����,����ʱ����LCD_DISP_Keydelay_TIME����
		{
			GStr_DisplayPara.ucKeydelaytimer++;
			if( LCD_DISP_Keydelay_TIME <= GStr_DisplayPara.ucKeydelaytimer )
			{
				GStr_Flag.ucDispKey |= F_KEY_STATUS_TRUE;
				GStr_Flag.ucDispKey &= (~F_KEY_ACKTION_DOWN);
				
				GStr_DisplayPara.ucKeydelaytimer = 0;
				GStr_Flag.ucDisp |= F_DISP_KEYDISP;					// ���밴������
				GStr_DisplayPara.ulDisptimer = LCD_DISP_Key_TIME*2/LCD_UPTATA_TIME;	// ������ʾ����ʱ��
				GStr_DisplayPara.ucBackLightTime = LCD_DISP_Key_TIME/LCD_UPTATA_TIME;	// ������ʾ����ʱ��
				
				if( GStr_DisplayPara.ucFirstKeyDisp == 0 )			// ��һ��ѭ����ʾ,�ӵ�һ����ʼ��ʾ
				{
					GStr_DisplayPara.ucDispNum = 0 ;
					GStr_DisplayPara.ucFirstKeyDisp = 0x68;			// �ǵ�һ�ΰ�����ʾ��־
				}
				else                                 				// ���ǵ�һ�ΰ�����ʾ����ʾ���ż�1
				{
					GStr_DisplayPara.ucDispNum++;
					if( GStr_DisplayPara.ucDispNum >= GStr_DisplayPara.ucKeyDispNum )
					{
						GStr_DisplayPara.ucDispNum = 0;
					}
				}		
			}
		}
		else
		{
			GStr_DisplayPara.ucKeydelaytimer = 0;
			GStr_Flag.ucDispKey = F_KEY_STATUS_IDLE;
		}
		
	}
	else if( F_KEY_STATUS_TRUE & GStr_Flag.ucDispKey )
	{
		if( DISPLAY_KEY_HIGHT )
		{
			GStr_DisplayPara.ucKeydelaytimer = 0;
			GStr_Flag.ucDispKey = F_KEY_STATUS_IDLE;
		}
	}
	else
	{
		GStr_DisplayPara.ucKeydelaytimer=0;
		GStr_Flag.ucDispKey = F_KEY_STATUS_IDLE;
	}
	
}


