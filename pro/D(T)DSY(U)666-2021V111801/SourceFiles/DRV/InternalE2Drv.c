/*******************************************************************************************************
**** Copyright��  (c)Copyright 2019,�㽭��̩�����Ǳ��������ι�˾,���ܱ�Ӧ���з�                       
****                            All rights reserved.                                                 
**** FileName:    InternalE2Drv.c                                                                          
**** Brief:       ��E2�����ļ�                                                                    
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
 
 // 79f7021A ��E2��ַ��0000-0FFF ÿ512�ֽ�Ϊһ���������ܹ�8������,���������Ϊ10W�Σ�����ʵ�ʲ��ԣ�������������ȫ�¶ȷ�Χ��
 // ֻ�ܰ�3W�μ���
 /*
 --------------------------XPAGE ˵�� -----------------------------------
 F7H    ��7λ     ��6λ   ��5λ    ��4λ    ��3λ  ��2λ   ��1λ   ��0λ
XPAGE  XPAGE.7  XPAGE.6  XPAGE.5 XPAGE.4 XPAGE.3 XPAGE.2 XPAGE.1 XPAGE.0

λ��� λ����       ˵��
7-4   XPAGE[7:4]   �ڲ���/��̿���ʱ������
3-1   XPAGE[3:1]   ������/��̵Ŀ����ţ� 0000�����0�� �������ơ�
0     XPAGE0       ������/��̵Ĵ洢��Ԫ��λ��ַ

@brief --��EEPROM������ӦXPAGE[3:0]Ϊ0000-0111�Ŀ顣 ��EEPROM�����ķ��ʿ�ͨ��ָ�MOVC A�� @A+DPTR����MOVC A��
@A+PC��ʵ�֣� ע�⣺ ��Ҫ��FACλ��FLASHCON.0�� ��1��
---------------------------IB_OFFSET ˵�� ----------------------------------
EEH         ��7λ       ��6λ       ��5λ       ��4λ       ��3λ        ��2λ        ��1λ       ��0λ
IB_OFFSET  IBS_EOTF.7F IBS_EOTF.6F IBS_EOTF.5F IBS_EOTF.4F IBS_EOTF.3F IBS_EOTF.2F IBS_EOTF.1F IBS_EOTF.0

λ��� λ����           ˵��
7-0    IB_OFFSET[7:0]  ������/��̵Ŀ鵥Ԫ��ַ

@brief -- IB_OFFSET[7:0]��8λ�� ���Ա�ʾ1��������ȫ��256���ֽڵ�ƫ������
 */
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
INT8U Hal_EraseEEPROM(INT16U Dst);
void Hal_EraseFlashSector(INT16U adr, INT8U dat, INT8U sta);
INT8U Hal_ReadEEPROM(INT8U  *Dst, INT16U Src, INT16U Len);
INT8U Hal_ReadFlash_byte(INT16U adr, INT8U sta);
INT8U Hal_WriteEEPROM(INT16U Dst, INT8U  *Src, INT16U Len);
void Hal_WriteFlash_byte(INT16U adr, INT8U dat, INT8U sta);

/*----------------< �������� >----------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ��EEPROMд1���ֽ�
 *
 *  @param    xx :
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

#pragma SAVE
#pragma OT(0)
void Hal_WriteFlash_byte(INT16U adr, INT8U dat, INT8U sta)
{
//	_push_(IEN0);
	EA = 0;
	
	IB_DATA = dat;
	IB_OFFSET = (INT8U)(adr&0xFF);
	XPAGE = (INT8U)(adr>>8);
	FLASHCON = 1;
	

		IB_CON1 = 0x6E;
		IB_CON2 = 0x05;
		IB_CON3 = 0x0A;
		IB_CON4 = 0x09;
	if(sta == FLASH_RW_ENABLE)
	{	
		IB_CON5 = 0x06;
		_nop_();
		_nop_();
		_nop_();
		_nop_();
	}
	
	FLASHCON = 0;
	XPAGE = 0;
	EA = 1;
//	_pop_(IEN0);
}
#pragma RESTORE

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ��EEPROMдָ����������
 *
 *  @param    xx :
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

INT8U Hal_WriteEEPROM(INT16U Dst, INT8U  *Src, INT16U Len)
{
    INT8U xdata Dat;
		/* ��Ҫ���ӵ����ж� */
	PASLO_POWER_SWITCH_ON();
//	#if(METER_TYPE==METER_TYPE_DDSYU666)   //�����͵�ѹ���Ϊ3.00V
		LPDCON2 = ( LPDCON2_LPD2EN  | LPDCON2_LPDS_300 );	// ����͵�ѹ��⣬��LPD2,��ֹLPD3��⣬��ѹ3.00V Լ90%
//	#else
//		LPDCON2 = ( LPDCON2_LPD2EN  | LPDCON2_LPDS_315 );	// ����͵�ѹ��⣬��LPD2,��ֹLPD3��⣬��ѹ3.15V Լ95%
//	#endif
	NOP();
	NOP();
	if ( (LPDCON2 & LPDCON2_LPD2F) == LPDCON2_LPD2F )	///* �����˾�ֱ���˳� *///
	{
		return 0xFF;;
	}  ////xww
	
	if(C_SafeByte!=GStr_Flag.ucWrE2promSafeByte)//��ȫ�������ж�//	
	{
		return 0xFF;
	}

    if ((Dst + Len) > 4096)
    {
        return (0xFF);
    }
    while (Len>0)
    {
        Dat = *Src;
        Hal_WriteFlash_byte(Dst, Dat, FLASH_RW_ENABLE);
        Dst++;
        Src++;
        Len--;
    }
	
    return(0x00);
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ��EEPROM��ȡ1���ֽ�
 *
 *  @param    adr : Ҫ��ȡ�����ݵ�ַ 2�ֽ�
 *  @param    sta : ״̬�����ֽ�
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

INT8U Hal_ReadFlash_byte(INT16U adr, INT8U sta)
{
    INT8U  t_tmp = 0;
	
    if (sta == FLASH_RW_ENABLE)
    {
        //_push_(IEN0);
        EA = 0;
        FLASHCON = 1;
        t_tmp = *((INT8U code*)adr);
        FLASHCON = 0x00;
		EA = 1;
        //_pop_(IEN0);
   }
   
   return t_tmp;
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ��ȡָ��������E2��������
 *
 *  @param    Dst : ���ݴ�Ż���ָ��
 *  @param    Src : Ҫ��ȡ���ݵĵ�ַ
 *  @param    Len : Ҫ��ȡ�����ݳ���
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

INT8U Hal_ReadEEPROM(INT8U  *Dst, INT16U Src, INT16U Len)
{
	/* ��Ҫ���ӵ����ж� */
	PASLO_POWER_SWITCH_ON();
//	#if(METER_TYPE==METER_TYPE_DDSYU666)   //�����͵�ѹ���Ϊ3.00V
		LPDCON2 = ( LPDCON2_LPD2EN  | LPDCON2_LPDS_300 );	// ����͵�ѹ��⣬��LPD2,��ֹLPD3��⣬��ѹ3.00V Լ90%
//	#else
//		LPDCON2 = ( LPDCON2_LPD2EN  | LPDCON2_LPDS_315 );	// ����͵�ѹ��⣬��LPD2,��ֹLPD3��⣬��ѹ3.15V Լ95%
//	#endif
	NOP();
	NOP();
	if ( (LPDCON2 & LPDCON2_LPD2F) == LPDCON2_LPD2F )	///* �����˾�ֱ���˳� *///
	{
		return 0xFF;;
	}  ////xww

    if ((Src + Len) > 4096)
    {
        return 0xFF;
    }

    while (Len > 0)
    {
        *Dst = Hal_ReadFlash_byte(Src, FLASH_RW_ENABLE);
        Dst++;
        Src++;
        Len--;
    }
	
    return 0x00;
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ������E2ָ��ҳ
 *
 *  @param    adr : ��ַ
 *  @param    dat : ���ݣ�ͨ��Ϊ0x00?)
 *  @param    sta : ״̬�����ֽ�
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/

#pragma SAVE
#pragma OT(0)
void Hal_EraseFlashSector(INT16U adr, INT8U dat, INT8U sta)
{
		/* ��Ҫ���ӵ����ж� */
	/* ��Ҫ���ӵ����ж� */
	PASLO_POWER_SWITCH_ON();
//	#if(METER_TYPE==METER_TYPE_DDSYU666)   //�����͵�ѹ���Ϊ3.00V
		LPDCON2 = ( LPDCON2_LPD2EN  | LPDCON2_LPDS_300 );	// ����͵�ѹ��⣬��LPD2,��ֹLPD3��⣬��ѹ3.00V Լ90%
//	#else
//		LPDCON2 = ( LPDCON2_LPD2EN  | LPDCON2_LPDS_315 );	// ����͵�ѹ��⣬��LPD2,��ֹLPD3��⣬��ѹ3.15V Լ95%
//	#endif
	NOP();
	NOP();
	if ( (LPDCON2 & LPDCON2_LPD2F) == LPDCON2_LPD2F )	///* �����˾�ֱ���˳� *///
	{
		return ;
	}  ////xww
	if(C_SafeByte!=GStr_Flag.ucWrE2promSafeByte)//��ȫ�������ж�//	
	{
		return ;
	}
	
//	_push_(IEN0);
	EA = 0;
	IB_DATA = dat;
	IB_OFFSET = (INT8U)(adr&0xFF);
	XPAGE = (INT8U)(adr>>8);
	FLASHCON = 1;
	

		IB_CON1 = 0xE6;
		IB_CON2 = 0x05;
		IB_CON3 = 0x0A;
		IB_CON4 = 0x09;
		
	if (sta == FLASH_RW_ENABLE)
	{		
		IB_CON5 = 0x06;
		_nop_();
		_nop_();
		_nop_();
		_nop_();
	}
	
	FLASHCON = 0;
	XPAGE = 0;
	EA = 1;
//	_pop_(IEN0);
}
#pragma RESTORE

///*------------------------------------------------------------------------------------------------------*/
///**
// *  @brief    ��EEPROM��ȡ1���ֽ�
// *
// *  @param    Dst : ��ַ
// *
// *  @return   xx
// *
// *  @note     xx
// *
// */
///*------------------------------------------------------------------------------------------------------*/

//INT8U Hal_EraseEEPROM(INT16U Dst)
//{
//    if (Dst >= 4096)
//    {
//        return (0xFF);
//    }
//    Hal_EraseFlashSector(Dst, 0x00, FLASH_RW_ENABLE);

//    return (0x00);
//}
