 
///*******************************************************************************************************///
///* Copyright��  (c)Copyright 2016,�㽭��̩�����Ǳ��������ι�˾,���ܵ���з�һ��                        *///
///*                            All rights reserved.                                                     *///
///* FileName:    LibEepromLayout.c                                                                      *///
///* Brief:       E2�ֲ�����						                                                     */// 
///* Author:      ����                                                                                   *///
///* Version:     �汾                                                                                   *///
///* Date:        ����                                                                                   *///
///*                                                                                                     *///
///* note:�޸���ʷ��¼�б�ÿ���޸ļ�¼Ӧ�����޸����ڡ��޸��߼���                                       *///
///* 1.  Author:                                                                                         *///
///*     Version:                                                                                        *///
///*     Date :                                                                                          *///
///* 2.  Author:                                                                                         *///
///*     Version:                                                                                        *///
///*     Date:                                                                                           *///
///*                                                                                                     *///
///*  addtogroup:Template                                                                                *///
///*******************************************************************************************************///

///*-------------------------------- �ļ�����˵�� -------------------------------------------------------*///
///*                                                                                                     *///
///*  ���ļ����к�����ǰ׺ΪTemp_                                                                        *///
///*  �ļ��������Ͷ��⺯��������ļ����ײ���������������Ҫ���ڵ�һ��λ��;                                *///
///*  ����ע�Ͳ��ñ�׼ģ�壬�����ڲ�ע�Ͳ���//;                                                          *///
///*  ����ע�ͽ϶�Ĳ��֣���������һ��ע�ͷ���Ȼ����ϸ˵�������ļ���β��;                                *///
///*                                                                                                     *///
///*-----------------------------------------------------------------------------------------------------*///


///* ע�͸�ʽ��������б�ܼ��Ǻŵķ�ʽ��ע����ע�ͷ�֮���ÿո���� *///
///* ������ƾ�����tab�Ʊ�������ó�ռ4���ո񣩻���ֱ����4���ո�  *///
///*--------------------------------- ͷ�ļ������� ------------------------------------------------------*///
#include "Include.h"

///*--------------------------------- ���������� --------------------------------------------------------*///

const  GStr_EEPROM_MAP EEPROM_MAP_TAB[ ]={
	///* ��ַ����        			�����ַ                      ռE2�ռ� 		         ���ݳ���   	       �Ƿ��CRC	  �Ƿ񱸷� 	*///
	///* ��1ҳ��ʼ 0x0000��ַ��ʱ����*///
	{ LIB_E2P_ENRGY, 				LIB_E2P_ENRGY_Addr, 	        LIB_E2P_ENRGY_Len , 		LIB_E2P_ENRGY_Len,			_TRUE, 		_TRUE,  },		///* ���ܴ洢E2��ַ,�����ܵ��ܣ�4��+�����ܵ��ܣ�4��+crc */// 
	{ LIB_E2P_ENRGY_BAK, 			LIB_E2P_ENRGY_BAK_Addr, 	    LIB_E2P_ENRGY_Len, 		    LIB_E2P_ENRGY_Len,			_TRUE, 		_FALSE, },		///* ���ܴ洢E2��ַ����,�����ܵ��ܣ�4��+�����ܵ��ܣ�4��+crc */// 
	{ LIB_E2P_Money, 			    LIB_E2P_Money_Addr, 		    LIB_E2P_Money_Len, 			LIB_E2P_Money_Len,			_TRUE, 		_TRUE,  },		///* ���洢E2��ַ,ʣ���6��+͸֧��6��+crc */// 
   	{ LIB_E2P_Money_BAK, 			LIB_E2P_Money_BAK_Addr, 	    LIB_E2P_Money_Len, 			LIB_E2P_Money_Len,			_TRUE, 		_FALSE, },		///* ���洢E2��ַ����,ʣ���6��+͸֧��6��+crc *///   
    { LIB_E2P_Price, 			    LIB_E2P_Price_Addr, 		    LIB_E2P_Price_Len, 			LIB_E2P_Price_Len,			_TRUE, 		_TRUE,  },		///* ��۴洢E2��ַ,��ۣ�4��+�ܹ����4��+crc */// 
   	{ LIB_E2P_Price_BAK, 			LIB_E2P_Price_BAK_Addr, 	    LIB_E2P_Price_Len, 			LIB_E2P_Price_Len,			_TRUE, 		_FALSE, },		///* ��۴洢E2��ַ����
	{ LIB_E2P_EMU_CALPARA, 			LIB_E2P_EMU_CALPARA_Addr, 	    LIB_E2P_EMU_CALPARA_Len, 	LIB_E2P_EMU_CALPARA_Len,	_TRUE, 		_TRUE,  },		///* У�����,����+crc *///����Ƶ�ʣ�4��+�й��������棨4��+��λ��У(4)+С�źŵ�У��4��+Ǳ����ֵ��4��+CRC��2��
	{ LIB_E2P_EMU_CALPARA_BAK, 	    LIB_E2P_EMU_CALPARA_BAK_Addr, 	LIB_E2P_EMU_CALPARA_Len, 	LIB_E2P_EMU_CALPARA_Len,	_TRUE, 		_FALSE, },		///* У���������,����+crc *///
	#if(METER_TYPE!=METER_TYPE_DTSY666)
	{ LIB_E2P_EMU_UIPKms 	,		LIB_E2P_EMU_UIPKms_Addr , 	    LIB_E2P_EMU_UIPKms_Len, 	LIB_E2P_EMU_UIPKms_Len,		_TRUE, 		_TRUE,  },		///* ˲ʱ��ϵ��,����+crc *///��ѹϵ����4��+����ϵ����4��+����ϵ����4��+CRC��2��
	{ LIB_E2P_EMU_UIPKms_BAK, 	    LIB_E2P_EMU_UIPKms_BAK_Addr, 	LIB_E2P_EMU_UIPKms_Len, 	LIB_E2P_EMU_UIPKms_Len,		_TRUE, 		_FALSE, },		///* ˲ʱ��ϵ��,����+crc *///��ѹϵ����4��+����ϵ����4��+����ϵ����4��+CRC��2��
	#else
	{ LIB_E2P_EMU_UIPKms 	,		LIB_E2P_EMU_UIPKms_Addr , 	    6, 							LIB_E2P_EMU_UIPKms_Len,		_TRUE, 		_TRUE,  },		///* ˲ʱ��ϵ��,����+crc *///�����ֻ�е���ϵ����4��+CRC��2��
	{ LIB_E2P_EMU_UIPKms_BAK, 	    LIB_E2P_EMU_UIPKms_BAK_Addr, 	6, 							LIB_E2P_EMU_UIPKms_Len,		_TRUE, 		_FALSE, },		///* ˲ʱ��ϵ��,����+crc *///�����ֻ�е���ϵ����4��+CRC��2��
	#endif
	{ LIB_E2P_FUN_CONFIG,			LIB_E2P_FUN_CONFIG_Addr,		LIB_E2P_FUN_CONFIG_Len,		LIB_E2P_FUN_CONFIG_Len,		_TRUE, 		_TRUE,  },		///* �������ã�����������1����������1��+12�ֽ�Ԥ��+CRC��2�� *///
    { LIB_E2P_FUN_CONFIG_BAK,		LIB_E2P_FUN_CONFIG_BAK_Addr,	LIB_E2P_FUN_CONFIG_Len,		LIB_E2P_FUN_CONFIG_Len,		_TRUE, 		_FALSE, },		///* �������ñ��ݣ�����������1����������1��+12�ֽ�Ԥ��+CRC��2�� */// 
	{ LIB_E2P_ENERGY_DECPULSE_FW, 	LIB_E2P_ENERGY_DECPULSE_FW_Addr, LIB_E2P_ENERGY_DECPULSE_FW_Len, 		1,			    _FALSE, 	_FALSE, },		///* С�����������򣩣���13�ֽ�*/// 
	{ LIB_E2P_ENERGY_DECPULSE_BK, 	LIB_E2P_ENERGY_DECPULSE_BK_Addr, LIB_E2P_ENERGY_DECPULSE_BK_Len, 		1,			    _FALSE, 	_FALSE, },		///* С�����������򣩣���13�ֽ�*/// 
    { LIB_E2P_ENERGY_DECPULSE_WS, 	LIB_E2P_ENERGY_DECPULSE_WS_Addr, LIB_E2P_ENERGY_DECPULSE_WS_Len,LIB_E2P_ENERGY_DECPULSE_WS_Len,	_FALSE, 	_FALSE, },		///* ����β�������籣�棬����+���򣬹�4�ֽ� *///
    { LIB_E2P_RUN_STATE        , 	LIB_E2P_RUN_STATE_Addr, 	     LIB_E2P_RUN_STATE_Len, 	LIB_E2P_RUN_STATE_Len,		_TRUE, 	    _FALSE, },		///* ����״̬  1�ֽ�+CRC(2)
	{ LIB_E2P_METER_INFO, 			LIB_E2P_METER_INFO_Addr, 		 LIB_E2P_METER_INFO_Len, 	LIB_E2P_METER_INFO_Len,		_TRUE, 		_FALSE, },		///* �����Ϣ��ͨ�ŵ�ַ(6)�����(6)���ͻ���ţ�6����������������(1)�����������4�����������4��+crc(2) *///
    { LIB_E2P_Money_Para, 	        LIB_E2P_Money_Para_Addr, 		 LIB_E2P_Money_Para_Len, 	LIB_E2P_Money_Para_Len,		_TRUE, 	    _FALSE, },		///* ������Ϣ�� һ��������4��+����������4��+�ڻ������ֵ��4��+͸֧�����ֵ��4���ڻ���4��+���ع��ʣ�3��+CRC��2��*///
    { LIB_E2P_Password, 	        LIB_E2P_Password_Addr,           LIB_E2P_Password_Len, 		LIB_E2P_Password_Len,		_TRUE,      _FALSE, },		///* 00 01 02����3�ֽ�*///
    { LIB_E2P_SecretKey, 	        LIB_E2P_SecretKey_Addr, 		 LIB_E2P_SecretKey_Len, 	LIB_E2P_SecretKey_Len,		_FALSE,     _FALSE, },		///* ��Կ16�ֽ�*///
	{ LIB_E2P_SOFTI_J,				LIB_E2P_SOFTI_J_Addr,		     LIB_E2P_SOFTI_J_Len,		LIB_E2P_SOFTI_J_Len,		_TRUE, 		_FALSE, },		///* ��I_J�洢��ַ4������+2CRC *///
    { LIB_E2P_AvailTimer,           LIB_E2P_AvailTimer_Addr,         LIB_E2P_AvailTimer_Len,    LIB_E2P_AvailTimer_Len,     _FALSE,     _FALSE, },      ///* �����֤��Чʱ��
    { LIB_E2P_EventNumPiont,        LIB_E2P_EventNumPiont_Addr,      LIB_E2P_EventNumPiont_Len, LIB_E2P_EventNumPiont_Len,  _TRUE,      _FALSE, },      ///* �¼���Чָ��  4+CRC��2��
	{ LIB_E2P_EventValidPiont,      LIB_E2P_EventValidPiont_Addr,    LIB_E2P_EventValidPiont_Len,LIB_E2P_EventValidPiont_Len,_TRUE,      _FALSE, },    ///* �¼�ѭ��ָ��  4+CRC��2��
	{ LIB_E2P_EventNum,             LIB_E2P_EventNum_Addr,           LIB_E2P_EventNum_Addr_Len, LIB_E2P_EventNum_Addr_Len ,  _TRUE,      _FALSE, },    ///* �¼�����  4*4+CRC��2��
    { LIB_E2P_Display_Para,			LIB_E2P_Display_Para_Addr,		 LIB_E2P_Display_Para_Len,	LIB_E2P_Display_Para_Len,	_TRUE, 		_FALSE, },		///* �ϵ�ȫ��ʱ�䣨1��+ÿ����ʾʱ�䣨1��+������ʾ������1��+ѭ����ʾ������1��+CRC��2�� *///  
    { LIB_E2P_Display_Table,		LIB_E2P_Display_Table_Addr,		 LIB_E2P_Display_Table_len,	LIB_E2P_Display_Table_len,	_TRUE, 		_FALSE, },		///* ѭ���30��+�����30��+CRC��2��*///  
	{ LIB_E2P_BLE_PARA,				LIB_E2P_BluePara_Addr,			LIB_E2P_BluePara_Len,		LIB_E2P_BluePara_Len,		_TRUE,		_FALSE,	},    ///*?����������23)+crc(2)
};
///*--------------------------------- ���������� --------------------------------------------------------*///


///*--------------------------------- ������ ------------------------------------------------------------*///

///* ���βεĺ�����ʽ:*///
///**********************************************************************///
///* Brief:  �������ܼ�Ҫ����                                           *///
///* Param:  ��ڲ���˵����һ������ռһ��                               *///
///* Return: ��������ֵ��˵��                                           *///
///* Note:   �޸ļ�����˵��                                             *///
///**********************************************************************///


///* ���βεĺ�����ʽ: *///
///**********************************************************************///
///* Brief:  �������ܼ�Ҫ����                                           *///
///* Return: ��������ֵ��˵��                                           *///
///* Note:   �޸ļ�����˵��                                             *///
///**********************************************************************///
//void LibEep_ReadE2Map(void)
//{
//	GStr_E2Map++;
//}




///*--------------------------------- ע������� ---------------------------------------------------------*///

///* ע��1: һЩ���ӵĹ��ܿ���������ע�ͣ���Ҫ��ע�����溯���Ĺ��ܣ�������Ҫ����ÿһ��������һ��ע�������*///

///* ע��2: *///

///*------------------------------------------------------------------------------------------------------*///

