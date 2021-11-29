/*******************************************************************************************************
**** Copyright��  (c)Copyright 2019,�㽭��̩�����Ǳ��������ι�˾,���ܱ�Ӧ���з�                       
****                            All rights reserved.                                                 
**** FileName:    AppEMU7021A.h                                                                          
**** Brief:       ����ģ��                                                                      
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

#ifndef   _APPEMU7021A_H
#define   _APPEMU7021A_H

#if ( METER_TYPE != METER_TYPE_DTSY666 )
/*-------------------------------- H�ļ�ʹ��˵�� -------------------------------------------------------*/
/*
 *  ���ļ��궨���ǰ׺Ϊ:
 *
 */

 
/*----------------< �����ļ� >----------------------------------*/


/*----------------< �궨���� >----------------------------------*/




// �����Ĵ������� ���Ѱַ�Ĵ���
// ���������Ĵ���
// ���������Ĵ�����FREQ�ⶼΪֻ���Ĵ����� ֻ��ͨ��EADR��EDTAH/EDTAM/EDTAL�Ĵ�����Ӷ�ȡ��
#define		C_ECADR_I1DTA 			0x00
#define		C_ECADR_I2DTA 			0x01
#define		C_ECADR_VDTA  			0x02
#define		C_ECADR_APWR1  			0x03
#define		C_ECADR_RPWR1 			0x04
#define		C_ECADR_APWR2 			0x05
#define		C_ECADR_RPWR2 			0x06
#define		C_ECADR_AERY  			0x07
#define		C_ECADR_RERY  			0x08
#define		C_ECADR_FREQ			0x09
#define		C_ECADR_I1Rms 			0x0A
#define		C_ECADR_I2Rms  			0x0B
#define		C_ECADR_VRms  			0x0C
#define		C_ECADR_WPA				0x0D
#define		C_ECADR_VARPA 			0x0E
#define		C_ECADR_APWRA1			0x0F
#define		C_ECADR_RPWRA1			0x10
#define		C_ECADR_APWRA2 			0x11
#define		C_ECADR_RPWRA2 			0x12
#define		C_ECADR_AERYL  			0x13
#define		C_ECADR_RERYL  			0x14
#define		C_ECADR_VDTAMAX 		0x15
#define		C_ECADR_AERY_CONSTH 	0x16
#define		C_ECADR_RERY_CONSTH  	0x17
#define		C_ECADR_AERY_CONSTL 	0x18
#define		C_ECADR_RERY_CONSTL  	0x19
#define		C_ECADR_WPA_CONST		0x1A
#define		C_ECADR_VARPA_CONST 	0x1B
#define		C_ECADR_RMPATWR 		0x1C
#define		C_ECADR_RMTQPWR 		0x1D
#define		C_ECADR_RMTIRMS 		0x1E
#define		C_ECADR_RMTVRMS 		0x1F
#define		C_ECADR_APWRA1L 		0x20
#define		C_ECADR_RPWRA1L 		0x21
#define		C_ECADR_APWRA2L 		0x22
#define		C_ECADR_RPWRA2L 		0x23
#define		C_ECADR_APWR1L 			0x24
#define		C_ECADR_RPWR1L 			0x25
#define		C_ECADR_APWR2L 			0x26
#define		C_ECADR_RPWR2L 			0x27

// ���������Ĵ��� 
#define		  C_EPADR_EMUCFG0       0x30			// 30H EMUCFG0 3 EMU�������üĴ���0
#define     C_EPADR_EMUCFG1       0x31			// 31H EMUCFG1 3 EMU�������üĴ���1
#define     C_EPADR_EMUCFG2       0x32			// 32H EMUCFG2 3 EMU�������üĴ���2
#define     C_EPADR_EMUCFG3       0x33			// 33H EMUCFG3 2 EMU�������üĴ���3
#define     C_EPADR_W1GAIN        0x34			// 34H W1GAIN     2 ͨ��1��������Ĵ��� (�й��޹�ʹ��ͬһ��)
#define     C_EPADR_P1CAL         0x35			// 35H P1CAL      2 ͨ��1��ѹ������λ�����Ĵ���
#define     C_EPADR_W2GAIN        0x36			// 36H W2GAIN     2 ͨ��2��������Ĵ��� (�й��޹�ʹ��ͬһ��)
#define     C_EPADR_P2CAL         0x37			// 37H P2CAL      2 ͨ��2��ѹ������λ�����Ĵ���
#define     C_EPADR_I2GAIN        0x38			// 38H I2GAIN     2 ͨ��2�����������üĴ���
#define     C_EPADR_WATT1OS       0x39			// 39H WATT1OS    3 ͨ��1�й�����ƫ��
#define     C_EPADR_WATT2OS       0x3A			// 3AH WATT2OS    3 ͨ��2�й�����ƫ��
#define     C_EPADR_VAR1OS        0x3B			// 3BH VAR1OS     3 ͨ��1�޹�����ƫ��
#define     C_EPADR_VAR2OS        0x3C			// 3CH VAR2OS     3 ͨ��2�޹�����ƫ��
#define     C_EPADR_IRMS1OS       0x3D			// 3DH IRMS1OS    3 ͨ��1������Чֵƫ��
#define     C_EPADR_IRMS2OS       0x3E			// 3EH IRMS2OS    3 ͨ��2������Чֵƫ��
#define     C_EPADR_VRMSOS        0x3F			// 3FH VRMSOS     3 ��ѹ��Чֵƫ��
#define     C_EPADR_ADCOSI1       0x40			// 40H ADCOSI1    2 ����ͨ��1 ADCƫ������SH79F7021A 
#define     C_EPADR_ADCOSI2       0x41			// 41H ADCOSI2    2 ����ͨ��1 ADCƫ������
#define     C_EPADR_ADCOSU        0x42			// 42H ADCOSU     2 ��ѹͨ�� ADCƫ������
#define     C_EPADR_SPTSP         0x43			// 43H SPTSP      2 �й������������üĴ���
#define     C_EPADR_SPTSQ         0x44			// 44H SPTSQ      2 �޹������������üĴ���
#define     C_EPADR_VCONST        0x45			// 45H VCONST     3 �����ߵ�ѹ�̶�ֵ
#define     C_EPADR_SAGTHR        0x46			// 46H SAGTHR     2 ʧѹ��������
#define     C_EPADR_SAGCNT        0x47			// 47H SAGCNT     2 ʧѹ��������
#define     C_EPADR_ICONT         0x48			// 48H ICONT      2 �������Ƶ������
#define     C_EPADR_PCNT          0x49			// 49H PCNT       2 �����й���������� �����Ʋ����ʾ�з���ֵ
#define     C_EPADR_QCNT          0x4A			// 4AH QCNT       2 �����޹���������� �����Ʋ����ʾ�з���ֵ
#define     C_EPADR_SUMSAMPS      0x4B			// 4BH SUMSAMPS   2 �����������üĴ���
#define     C_EPADR_APCONST       0x4C			// 4CH APCONST    3 �й����ʳ������üĴ���
#define     C_EPADR_RPCONST       0x4D			// 4DH RPCONST    3 �޹����ʳ������üĴ���
#define     C_EPADR_PCNT_CONST    0x4E			// 4EH PCNT_CONST 2 �����й�������������� �����Ʋ����ʾ�з���ֵ
#define     C_EPADR_QCNT_CONST    0x4F			// 4FH QCNT_CONST 2 �����޹�������������� �����Ʋ����ʾ�з���ֵ
#define     C_EPADR_DIMTHR        0x50			// 50H DIMTHR     3 DIMMER�жϷ�ֵ����
#define     C_EPADR_DIMCNT        0x51			// 51H DIMCNT     1 DIMMER���������ֵ
#define     C_EPADR_SAMPCON       0x52			// 52H SAMPCON    1 ���β������üĴ���								
#define     C_EPADR_RMTCON        0x53			// 
#define     C_EPADR_RMTVREFS      0x54			// 
#define     C_EPADR_RMTVREFR      0x55			// 
#define     C_EPADR_RMTPCALP      0x56			// 
#define     C_EPADR_RMTFLAG       0x57			// 
#define     C_EPADR_HPFEFFB       0x5A			// 5AH HPFEFFB 3 ��ͨϵ��B
#define     C_EPADR_HPFEFFA       0x5B			// 5BH HPFEFFA 3 ��ͨϵ��A
#define     C_EPADR_LPFEFFB       0x60			// 60H LPFEFFB 3 ��ͨϵ��B
#define     C_EPADR_LPFEFFA       0x61			// 61H LPFEFFA 3 ��ͨϵ��A
#define     C_EPADR_ULPCTRL       0x62			// 62H ULPCTRL 2 ���͹������ã�����DIMMER���޹��Ƿ�����
#define     C_EPADR_AERY1H        0x70			// 70H AERY1H  3 ͨ��1�й������ۼ�ֵ��λ
#define     C_EPADR_RERY1H        0x71			// 71H RERY1H  3 ͨ��1�޹������ۼ�ֵ��λ  
#define     C_EPADR_AERY1M        0x72			// 72H AERY1M  3 ͨ��1�й������ۼ�ֵ��λ
#define		C_EPADR_RERY1M        0x73			// 73H RERY1M  3 ͨ��1�޹������ۼ�ֵ��λ
#define		C_EPADR_AERY1L        0x74			// 74H AERY1L  2 ͨ��1�й������ۼ�ֵ��λ
#define		C_EPADR_RERY1L        0x75			// 75H RERY1L  2 ͨ��1�޹������ۼ�ֵ��λ
#define		C_EPADR_AERY2H        0x76			// 76H AERY2H  3 ͨ��2�й������ۼ�ֵ��λ
#define		C_EPADR_RERY2H        0x77			// 77H RERY2H  3 ͨ��2�޹������ۼ�ֵ��λ
#define		C_EPADR_AERY2M        0x78			// 78H AERY2M  3 ͨ��2�й������ۼ�ֵ��λ
#define		C_EPADR_RERY2M        0x79			// 79H RERY2M  3 ͨ��2�޹������ۼ�ֵ��λ
#define		C_EPADR_AERY2L        0x7A			// 7AH AERY2L  2 ͨ��2�й������ۼ�ֵ��λ
#define		C_EPADR_RERY2L        0x7B			// 7BH RERY2L  2 ͨ��2�޹������ۼ�ֵ��λ
#define		C_EPADR_ICONT1        0x7C			// 7CH ICONT1  2 �ڶ�·�������Ƶ������
#define		C_EPADR_EMUCFG4       0x7D			// 7DH EMUCFG4 2 EMU�������üĴ���4

 
//#define		C_EPADR_EMUCFG0_DATA	( EMUCFG0_APGAI_16 | EMUCFG0_ADCUON | EMUCFG0_ADCI1ON ) // �̶�32K����ѹͨ�����棺2���� ����ͨ��1����16�����򿪵�ѹ�͵���ͨ��1ADC
//#define		C_EPADR_EMUCFG1_DATA	( EMUCFG1_POL | EMUCFG1_PFEN | EMUCFG1_QRUN | EMUCFG1_PRUN | EMUCFG1_Cmodeen ) //�͵�ƽ��Ч����PF����������й�/�޹��ۼ�ʹ�ܣ��ۼ�ģ����ʹ��
//#define		C_EPADR_EMUCFG2_DATA	( 


/*----------------< �������� >----------------------------------*/
typedef	struct{
	uchar8		ucEmuAddr;			///* У�������ַ *///
	ulong32		ulEmuRegData;		///* ��Ӧֵ *///
}EMU_EPADR_Type;
#define	EMU_EPADR_Type_LEN		sizeof( EMU_EPADR_Type )

typedef	struct{	/* ע��Ҫ��EMU_CALPARA_DEF_TAB���˳��Ҫһһ��Ӧ */
	ulong32		ulaCalPara[5];
// 	ulong32		ulICONST;			///* �������Ƶ�ʣ��൱����ȪоƬ��HFCONST *///
// 	ulong32		ulW1GAIN;			///* ͨ��1�й����������У�Ĵ��� *///
// 	ulong32		ulP1CAL;			///* ͨ��1��λ��У�Ĵ��� *///	
// 	ulong32		ulWATT1OS;			///* ͨ��1С�źŵ�У�Ĵ��� */// 
// 	ulong32		ulSPTSP;			///* Ǳ����ֵ */// 
	ushort16	usCRC16;			///* У�� *///
}EMU_CALPARA_Type;
#define	EMU_CALPARA_Type_LEN		sizeof( EMU_CALPARA_Type )

typedef	struct{
	ulong32     ulaKmsuip[3];
// 	ulong32		ulKmsU;				///* ��ѹ��Чֵϵ�� *///
// 	ulong32		ulKmsP;				///* ������Чֵϵ�� *///	
// 	ulong32		ulKmsI;				///* ������Чֵϵ�� *///
	ushort16	usCRC16;			///* У�� *///
}EMU_UIPKms_Type;
#define	EMU_UIPKms_Type_LEN		sizeof( EMU_UIPKms_Type )

typedef	struct{
	uchar8		ucCommDI1;			///* ��ӦDI1 *///
	uchar8		ucEmuAddr;			///* ��Ӧ��ַ *///
}EMU_COMM_CAL_TAB_Type;
#define	EMU_COMM_CAL_TAB_Type_LEN		sizeof( EMU_COMM_CAL_TAB_Type )
/*----------------< �������� >----------------------------------*/
// extern INT32U  ApiEMU_Read_ECADR(INT8U xdata address);
// extern void    ApiEMU_Write_ECADR(INT8U xdata address, INT32U xdata Data) ;
extern ulong32 ApiEMU_ReadEmuReg( ushort16 v_usRegAddress );
extern void    ApiEMU_WriteEmuReg( ushort16 v_usRegAddress, ulong32 v_ulRegData );
extern void    ApiEMU_CommStartCal( uchar8 v_ucChID );
extern void    ApiEMU_CommEndCal( uchar8 v_ucChID );
extern uchar8  ApiEMU_CommErrCal( uchar8 v_ucChID );
extern void    ApiEMU_EMUInit( void );
extern void	   ApiEMU_EMUParaCheck( void );
extern uchar8  ApiEMU_UpdateUIP(void);
extern uchar8  ApiEMU_GetDirP(void);
extern void ApiEMU_DisOrEnable(uchar8 v_ucWorkMode);


#endif 


#endif
