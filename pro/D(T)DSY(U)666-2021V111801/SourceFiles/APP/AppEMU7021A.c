/*******************************************************************************************************
**** Copyright��  (c)Copyright 2019,�㽭��̩�����Ǳ��������ι�˾,���ܱ�Ӧ���з�                       
****                            All rights reserved.                                                 
**** FileName:    AppEMU7021A.c                                                                         
**** Brief:       ����ģ��                                                                     
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

#if ( METER_TYPE != METER_TYPE_DTSY666)
/*----------------< �궨���� >----------------------------------*/

#define	C_EPDAT_EMUCFG3  0x000000E8u
#define	C_EPDAT_EMUCFG2  0x00000C84u
#define	C_EPDAT_EMUCFG1  0x00A000C1u
#define	C_EPDAT_EMUCFG0  0x00000035u
/*----------------< �������� >----------------------------------*/
EMU_EPADR_Type code EMU_EPADR_INIT_TAB[] = {
	// ��ַ                       ����
// 	{ C_EPADR_EMUCFG0,         0x00000035 },     // 30H EMUCFG0    3 EMU�������üĴ���0  �̶�32K����ѹͨ�����棺2���� ����ͨ��1����16�����򿪵�ѹ�͵���ͨ��1ADC
// 	{ C_EPADR_EMUCFG1,         0x00A000C1 },     // 31H EMUCFG1    3 EMU�������üĴ���1  �͵�ƽ��Ч����PF����������й�/�޹��ۼ�ʹ�ܣ��ۼ�ģ����ʹ��
//	{ C_EPADR_EMUCFG2,         0x00000C84 },     // 32H EMUCFG2    3 EMU�������üĴ���2  Ĭ��ֵ
//	{ C_EPADR_EMUCFG3,         0x000000E8 },     // 33H EMUCFG3    2 EMU�������üĴ���3  Ĭ��ֵ
	
//	{ C_EPADR_W1GAIN ,         0x00000000 },     // 34H W1GAIN     RW 2 ͨ��1��������Ĵ��� ***
//	{ C_EPADR_P1CAL  ,         0x00000000 },     // 35H P1CAL      RW 2 ͨ��1��ѹ������λ�����Ĵ��� ***
    { C_EPADR_W2GAIN ,         0x00000000 },     // 36H W2GAIN     RW 2 ͨ��2��������Ĵ���
    { C_EPADR_P2CAL  ,         0x00000000 },     // 37H P2CAL      RW 2 ͨ��2��ѹ������λ�����Ĵ���
    { C_EPADR_I2GAIN ,         0x00000000 },     // 38H I2GAIN     RW 2 ͨ��2������������
//	{ C_EPADR_WATT1OS,         0x00000000 },	 // 39H WATT1OS    RW 3 ͨ��1�й�����ƫ�� ***
    { C_EPADR_WATT2OS,         0x00000000 },     // 3AH WATT2OS    RW 3 ͨ��2�й�����ƫ��
	{ C_EPADR_VAR1OS ,         0x00000000 },	 // 3BH VAR1OS     RW 3 ͨ��1�޹�����ƫ��
	{ C_EPADR_VAR2OS ,         0x00000000 },     // 3CH VAR2OS     RW 3 ͨ��2�޹�����ƫ��
	{ C_EPADR_IRMS1OS,         0x00FD2700 },     // 3DH IRMS1OS    RW 3 ͨ��1������Чֵƫ��   //������ƫ�� �̶�дΪFD2700��ƫ��Ϊ16mA��
    { C_EPADR_IRMS2OS,         0x00000000 },     // 3EH IRMS2OS    RW 3 ͨ��2������Чֵƫ��
	{ C_EPADR_VRMSOS ,         0x00000000 },     // 3FH VRMSOS     RW 3 ��ѹ��Чֵƫ��
    { C_EPADR_ADCOSI1,         0x00000000 },     // 40H ADCOSI1    RW 2 ����ͨ��1 ADCƫ������
    { C_EPADR_ADCOSI2,         0x00000000 },     // 41H ADCOSI2    RW 2 ����ͨ��2 ADCƫ������
    { C_EPADR_ADCOSU ,         0x00000000 },     // 42H ADCOSU     RW 2 ��ѹͨ��ADCƫ������
//	{ C_EPADR_SPTSP  ,         0x0000001B },	 // 43H SPTSP      RW 2 �й������������üĴ��� ***
	{ C_EPADR_SPTSQ  ,         0x0000001B },     // 44H SPTSQ      RW 2 �޹������������üĴ���
    { C_EPADR_VCONST ,         0x00000000 },     // 45H VCONST     RW 3 �����ߵ�ѹ�̶�ֵ
    { C_EPADR_SAGTHR ,         0x00000000 },     // 46H SAGTHR     RW 2 ʧѹ��������
    { C_EPADR_SAGCNT ,         0x00000180 },     // 47H SAGCNT     RW 2 ʧѹ��������
//	{ C_EPADR_ICONT  ,         0x00000080 },	 // 48H ICONT      RW 2 �������Ƶ������ ***
//	{ C_EPADR_PCNT   ,         0x00000000 },     // 49H PCNT       RW 2 �����й��������
//	{ C_EPADR_QCNT   ,         0x00000000 },     // 4AH QCNT       RW 2 �����޹��������
	{ C_EPADR_SUMSAMPS  ,      0x000001ff },     // 4BH SUMSAMPS   RW 2 �����������üĴ���
//	{ C_EPADR_APCONST   ,      0x00000000 },     // 4CH APCONST    R  3 �й����ʳ������üĴ���
//	{ C_EPADR_RPCONST   ,      0x00000000 },     // 4DH RPCONST    R  3 �޹����ʳ������üĴ���
// 	{ C_EPADR_PCNT_CONST,      0x00000000 },     // 4EH PCNT_CONST RW 2 �����й������������
// 	{ C_EPADR_QCNT_CONST,      0x00000000 },     // 4FH QCNT_CONST RW 2 �����޹������������
	{ C_EPADR_DIMTHR    ,      0x00000000 },     // 50H DIMTHR     RW 3 DIMMER �жϷ�ֵ����
	{ C_EPADR_DIMCNT    ,      0x00000004 },     // 51H DIMCNT     RW 1 DIMMER���������ֵ
	{ C_EPADR_SAMPCON   ,      0x00000000 },     // 52H SAMPCON    RW 1 EMU���β������üĴ���
	{ C_EPADR_RMTCON    ,      0x00000000 },     // @7021A�޹أ����ó�Ĭ�ϼ���
	{ C_EPADR_RMTVREFS  ,      0x00000000 },     // @7021A�޹أ����ó�Ĭ�ϼ���
	{ C_EPADR_RMTVREFR  ,      0x00000000 },     // @7021A�޹أ����ó�Ĭ�ϼ���
	{ C_EPADR_RMTPCALP  ,      0x00000000 },     // @7021A�޹أ����ó�Ĭ�ϼ���
	{ C_EPADR_RMTFLAG   ,      0x00000000 },     // @7021A�޹أ����ó�Ĭ�ϼ���
	{ C_EPADR_HPFEFFB   ,      0x00800000 },     // 5AH HPFEFFB   RW  3 ��ͨϵ��B
	{ C_EPADR_HPFEFFA   ,      0x007FF547 },     // 5BH HPFEFFA   RW  3 ��ͨϵ��A
	{ C_EPADR_LPFEFFB   ,      0x0000055D },     // 60H LPFEFFB   RW  3 ��ͨϵ��B
	{ C_EPADR_LPFEFFA   ,      0x007FF546 },     // 61H LPFEFFA   RW  3 ��ͨϵ��A
	
	#if ( METER_TYPE == METER_TYPE_DDSY666)
	{ C_EPADR_ULPCTRL,         0x00000000 },     // 62H ULPCTRL   RW  2 ���͹������ã�����DIMMER���޹��Ƿ�����
	{ C_EPADR_ICONT1 ,         0x00000080 },     // 7CH ICONT1    RW  2 �ڶ�·�������Ƶ������
	{ C_EPADR_EMUCFG4,         0x00000000 },     // 7DH EMUCFG4   RW  2 EMU�������üĴ���4
	#endif
	
	#if ( METER_TYPE == METER_TYPE_DDSYU666)	 // ������õ���7019������Ĵ�����������0x007FF546
	{ C_EPADR_ULPCTRL,         0x00000000 },     // 62H ULPCTRL   RW  2 ���͹������ã�����DIMMER���޹��Ƿ�����
	{ C_EPADR_ICONT1 ,         0x00000080 },     // 7CH ICONT1    RW  2 �ڶ�·�������Ƶ������
	{ C_EPADR_EMUCFG4,         0x00000000 },     // 7DH EMUCFG4   RW  2 EMU�������üĴ���4
	#endif
	
// 	{ C_EPADR_AERY1H ,         0x00000000 },     // 70H AERY1H    R   3 ͨ��1�й������ۼ�ֵ��λ
// 	{ C_EPADR_RERY1H ,         0x00000000 },     // 71H RERY1H    R   3 ͨ��1�޹������ۼ�ֵ��λ  
// 	{ C_EPADR_AERY1M ,         0x00000000 },     // 72H AERY1M    R   3 ͨ��1�й������ۼ�ֵ��λ
// 	{ C_EPADR_RERY1M ,         0x00000000 },     // 73H RERY1M    R   3 ͨ��1�޹������ۼ�ֵ��λ
// 	{ C_EPADR_AERY1L ,         0x00000000 },     // 74H AERY1L    R   2 ͨ��1�й������ۼ�ֵ��λ
// 	{ C_EPADR_RERY1L ,         0x00000000 },     // 75H RERY1L    R   2 ͨ��1�޹������ۼ�ֵ��λ
// 	{ C_EPADR_AERY2H ,         0x00000000 },     // 76H AERY2H    R   3 ͨ��2�й������ۼ�ֵ��λ
// 	{ C_EPADR_RERY2H ,         0x00000000 },     // 77H RERY2H    R   3 ͨ��2�޹������ۼ�ֵ��λ
// 	{ C_EPADR_AERY2M ,         0x00000000 },     // 78H AERY2M    R   3 ͨ��2�й������ۼ�ֵ��λ
// 	{ C_EPADR_RERY2M ,         0x00000000 },     // 79H RERY2M    R   3 ͨ��2�޹������ۼ�ֵ��λ
// 	{ C_EPADR_AERY2L ,         0x00000000 },     // 7AH AERY2L    R   2 ͨ��2�й������ۼ�ֵ��λ
// 	{ C_EPADR_RERY2L ,         0x00000000 },     // 7BH RERY2L    R   2 ͨ��2�޹������ۼ�ֵ��λ
};
#define	 EMU_EPADR_INIT_TAB_INDEX	( sizeof( EMU_EPADR_INIT_TAB ) / EMU_EPADR_Type_LEN )


// У�������ʼ��,��У�����һһ��Ӧ
EMU_EPADR_Type code EMU_CALPARA_DEF_TAB[] = {
	{ C_EPADR_ICONT,			0x00000182 },
	{ C_EPADR_W1GAIN,			0x00000000 },
	{ C_EPADR_P1CAL,			0x00000000 },
	{ C_EPADR_WATT1OS,			0x00000000 },
	{ C_EPADR_SPTSP,			0x0000001b },
};
#define	 EMU_CALPARA_DEF_TAB_INDEX	( sizeof( EMU_CALPARA_DEF_TAB ) / EMU_EPADR_Type_LEN )

// �����
EMU_EPADR_Type code EMU_CFG0_3_DEF_TAB[] = {
	{ C_EPADR_EMUCFG0,			C_EPDAT_EMUCFG0 },
	{ C_EPADR_EMUCFG1,			C_EPDAT_EMUCFG1 },
	{ C_EPADR_EMUCFG2,			C_EPDAT_EMUCFG2 },
	{ C_EPADR_EMUCFG3,			C_EPDAT_EMUCFG3 }, 
};
#define	 EMU_CFG0_3_DEF_TAB_INDEX	( sizeof( EMU_CFG0_3_DEF_TAB ) / EMU_EPADR_Type_LEN )

// У����
EMU_COMM_CAL_TAB_Type code EMU_COMM_EMUC_TAB[]={
	{ 0x00,		C_EPADR_W1GAIN 		},
	{ 0x09,		C_EPADR_P1CAL		},
	{ 0x0D,		C_EPADR_WATT1OS		}, 
};
#define	EMU_COMM_EMUC_TAB_INDEX	(sizeof(EMU_COMM_EMUC_TAB) / EMU_COMM_CAL_TAB_Type_LEN)

uchar8  code C_ucUIPREG_TAB[] ={C_ECADR_VRms, C_ECADR_APWRA1, C_ECADR_I1Rms, C_ECADR_RPWRA1, C_ECADR_FREQ };	// ��ѹ�����ʣ�����, �޹���Ƶ�ʼĴ���
	#define C_ucUIPREG_TAB_Index	sizeof(C_ucUIPREG_TAB)

ushort16  code C_usUIP_KMS_DEF_VAL_TAB[]={0x1bd3, 0x0000, 0x0000 };	// ��ѹ�����ʣ�����ϵ��Ĭ��ֵ
	#define C_usUIP_KMS_DEF_VAL_TAB_Index	(sizeof(C_usUIP_KMS_DEF_VAL_TAB) / 2)

/*----------------< �������� >----------------------------------*/
EMU_CALPARA_Type	Str_EmuCalPara;		// У�����
EMU_UIPKms_Type		Str_UIPKmsPara;		// ˲ʱ��ϵ��
/*----------------< �������� >----------------------------------*/

static INT32U 	ApiEMU_Read_ECADR(INT8U xdata address);
static void 	ApiEMU_Write_ECADR(INT8U xdata address, INT32U xdata Data) ;
static void     ApiEMU_SetStartVal(void); 
static uchar8   ApiEMU_SetUIPKms(void);
static uchar8   ApiEMU_CheckCalParaCRC( void );
static uchar8   ApiEMU_CheckKmsParaCRC( void );

void 	ApiEMU_EMUInit( void );
void	ApiEMU_EMUParaCheck( void );
uchar8	ApiEMU_UpdateUIP(void);
ulong32 ApiEMU_ReadEmuReg( ushort16 v_usRegAddress );
void    ApiEMU_WriteEmuReg( ushort16 v_usRegAddress, ulong32 v_ulRegData );
void 	ApiEMU_CommStartCal( uchar8 v_ucChID );
void    ApiEMU_CommEndCal( uchar8 v_ucChID );
uchar8  ApiEMU_CommErrCal( uchar8 v_ucChID );
uchar8  ApiEMU_GetDirP(void);
void 	ApiEMU_DisOrEnable(uchar8 ucWorkMode);
/*----------------< �������� >----------------------------------*/
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    д������ؼĴ����������ڼ��Ѱַ�ļĴ�����
 *
 *  @param    address : �Ĵ�����ַ
 *  @param    Data : Ҫд�����ݣ�32λ
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void ApiEMU_Write_ECADR(INT8U xdata address, INT32U xdata Data) 
{
    typedef union
    {
        INT32U u32_ChangeData;
        INT8U ChangeDataTb[4];
    }TypeUn_ChangeData;
	
    TypeUn_ChangeData xdata Un_ChangeData;
	
    Un_ChangeData.u32_ChangeData = Data;
//    GV_u16WatchDogTMR =1000;
    EADR = 0;
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
	LibPub_Delay10xus(6);
    EA = 0;
    EDTAH = Un_ChangeData.ChangeDataTb[1];
    EDTAM = Un_ChangeData.ChangeDataTb[2];
    EDTAL = Un_ChangeData.ChangeDataTb[3];
    NOP();NOP();NOP();
    NOP();NOP();NOP();
    NOP();NOP();NOP();
    NOP();NOP();NOP();
    NOP();NOP();NOP();
    NOP();NOP();NOP();
    NOP();NOP();NOP();
    NOP();NOP();NOP();
    EADR = (address|0x80);
	LibPub_Delay10xus(6);
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
    EA = 1;
//    NOP();NOP();NOP();
//    NOP();NOP();NOP();	
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ��������ؼĴ����������ڼ��Ѱַ�ļĴ�����
 *
 *  @param    address : �Ĵ�����ַ
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
INT32U ApiEMU_Read_ECADR(INT8U xdata address) 
{
	INT32U xdata V_u32ReadData;
	
    typedef union
    {
        INT32U u32_ChangeData;
        INT8U ChangeDataTb[4];
    }TypeUn_ChangeData;
    TypeUn_ChangeData xdata Un_ChangeData;
	
//    GV_u16WatchDogTMR =1000;
    V_u32ReadData = 0;
    EA = 0;
    EADR = (address&0x7F);
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
	LibPub_Delay10xus(6);
    Un_ChangeData.u32_ChangeData = 0;
    Un_ChangeData.ChangeDataTb[1] = EDTAH;
    Un_ChangeData.ChangeDataTb[2] = EDTAM; 
    Un_ChangeData.ChangeDataTb[3] = EDTAL;
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
//     NOP();NOP();NOP();
    EA = 1;
    V_u32ReadData = Un_ChangeData.u32_ChangeData;
	return (V_u32ReadData);
}


/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ʹ��/�رռ���ģ��
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
 
void ApiEMU_DisOrEnable(uchar8 v_ucWorkMode)
{
	if( EMU_ENABLE == v_ucWorkMode )	// ʹ�ܼ���ģ��
	{
		EMUSR |=  EMUSR_DSPEN;
	}
	else	// �رռ���ģ��
	{
		EMUSR = 0x00;
		EMUIE = 0x00;
		EMUIF = 0x00;
		IEN1 &= ~IEN1_EEMU;
	}
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ����ģ���ʼ��
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void ApiEMU_EMUInit( void )
{
	uchar8 V_ucCnti=0;
	
	ApiEMU_DisOrEnable( EMU_DISENABLE );
	
	// @brief ������ EMUSR Ϊ 60H: ����ģ���ֹ��ϵͳʱ��ѡ��PLL��������ֱ�־
	EMUSR = 0x60;
	EMUIE = 0x00;
	EMUIF = 0x00;
	IEN1 &= ~IEN1_EEMU;
	
	// @brief ��������ǰ�ε�Դ���� PWRCON2 ����Ϊ 0X80 
	PWRCON2 |= PWRCON2_LDO28ON;
	
	// @brief ����VREF����EMUCFG3 ����Ϊ0x0000E8
	ApiEMU_Write_ECADR( C_EPADR_EMUCFG3, C_EPDAT_EMUCFG3);
	
	// @brief �ȴ�1MS
	LibPub_DelayNms(5);
	
	// @brief ���� ADC,PGA ���������� CHOP Ƶ�ʣ�EMUCFG2 ��������Ϊ 0x000C84
	ApiEMU_Write_ECADR( C_EPADR_EMUCFG2, C_EPDAT_EMUCFG2);	
	
	// @brief ���ü��������������� W1GAIN,P1CAL��W1ATTOS �ȣ��ָ�����������	
	for( V_ucCnti = 0; V_ucCnti<EMU_EPADR_INIT_TAB_INDEX; V_ucCnti++ )	/* �̶��������ã��������Է�װ�ɺ�����checkʱҲ������ */
	{
		ApiEMU_Write_ECADR( EMU_EPADR_INIT_TAB[V_ucCnti].ucEmuAddr, EMU_EPADR_INIT_TAB[V_ucCnti].ulEmuRegData);
	}
	
	/* ���Ӵ�E2�ָ�У�����ݴ��� */
	LibPub_ReadDataFromE2prom( LIB_E2P_EMU_CALPARA, 0, (uchar8*)&Str_EmuCalPara.ulaCalPara[0] );
	for( V_ucCnti = 0; V_ucCnti<EMU_CALPARA_DEF_TAB_INDEX; V_ucCnti++ )	
	{
		ApiEMU_Write_ECADR ( EMU_CALPARA_DEF_TAB[V_ucCnti].ucEmuAddr, Str_EmuCalPara.ulaCalPara[V_ucCnti] );
	}
	
	// @brief �_������ ADC ������횱��C�࿪��VREF �g�� 60mS��������ʱ100ms
	LibPub_DelayNms(100);	
	
	// @brief ���� ADC&PGA��EMUCFG0 ����Ϊ 0x000037 �߾���ģʽ����ѹͨ��2�����桢����ͨ��16�����桢�򿪵�ѹ����ͨ��ADC
	ApiEMU_Write_ECADR( C_EPADR_EMUCFG0, C_EPDAT_EMUCFG0);	/* ͨ��2������ */
	

	// @brief ���� EMUSR����������Ϊ 0XE0������
	ApiEMU_DisOrEnable( EMU_ENABLE );
	
	// @brief ���� EMUCFG1 �͵�ƽ��Ч��b23)�������й����������21�����򿪸�ͨ�˲�������90ms
	ApiEMU_Write_ECADR( C_EPADR_EMUCFG1, C_EPDAT_EMUCFG1);
	
	// @brief ��ʱ500ms	
	LibPub_DelayNms(500);
	
	EMUIF = 0x00;
	EMUIE = EMUIE_PFIE; // ����ֻ����PF�жϣ����Բ��ø�ֵ���������жϹر�
	IEN1 |= IEN1_EEMU;
	
}
/*--------------------------------- ע������� ---------------------------------------------------------*/
/**
 *  ע��1:������ؼĴ���������Ӧ�������²������ã���ӱFAQ�ĵ�Ҫ��: 
 A.  �� EMUSR �O�Þ� 0x60; 
 B.  ��������ģ��ǰ�˵�Դ���� PWRCON2 ����Ϊ 0X80 
 C.  ���� VREF���� EMUCFG3 ����Ϊ 0x000000E8 
 D.  �ȴ� 1MS 
 E.  ���� ADC,PGA ���������� CHOP Ƶ�ʣ�EMUCFG2 ��������Ϊ 0x000C84,�͹��ĵ���
     ����Ϊ 0x00098C 
 F.  ���ü��������������� W1GAIN,P1CAL��W1ATTOS ��
 G.  ���� ADC&PGA��EMUCFG0 ����Ϊ 0x000037���͹���ģʽ����Ϊ 0X100037�������
     ����Ҫֻ�_�z· ADC�����������EҲ�Ǳ�횵ġ��_������ ADC ������횱��C�࿪��
     VREF �g�� 60mS��
 H.  ���ÿ�����Ӧ�� ADC ͨ�����رղ��õ�ͨ������if necessary��
 I.  ���� EMUSR����������Ϊ 0XE0��
 J.  ���� EMUCFG1 
 K.  �ȴ� 500ms  
 L.  ���� EMUIE,ʹ���й������޹��������
 */
/**
 *  ע��2:
 *
 */
/**
 * @}
 */
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    �����������,ֻҪ�мĴ������ԣ���ֱ�Ӹ�λһ�£���������
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void ApiEMU_EMUParaCheck( void )
{
	uchar8   V_ucResult = _FAILED;
	uchar8   V_ucCnti;
	ushort16 V_usRegAddress = 0;
	ulong32  V_ulRegData;
	
	do{

		/* �ȼ��һ�����üĴ���  */
		for( V_ucCnti = 0; V_ucCnti<EMU_CFG0_3_DEF_TAB_INDEX; V_ucCnti++ )
		{
			V_usRegAddress = EMU_CFG0_3_DEF_TAB[V_ucCnti].ucEmuAddr;
			V_ulRegData = ApiEMU_ReadEmuReg( V_usRegAddress );
			if( EMU_CFG0_3_DEF_TAB[V_ucCnti].ulEmuRegData != V_ulRegData )
			{
				break;
			}
		}
		if( V_ucCnti < EMU_CFG0_3_DEF_TAB_INDEX ) break;
		
		/* ���һ�¹̶�ֵ */
		for( V_ucCnti = 0; V_ucCnti<EMU_EPADR_INIT_TAB_INDEX; V_ucCnti++ )
		{
			V_usRegAddress = EMU_EPADR_INIT_TAB[V_ucCnti].ucEmuAddr;
			V_ulRegData = ApiEMU_ReadEmuReg( V_usRegAddress );
			if( EMU_EPADR_INIT_TAB[V_ucCnti].ulEmuRegData != V_ulRegData )
			{
				break;
			}
		}
		if( V_ucCnti < EMU_EPADR_INIT_TAB_INDEX ) break;
		
		/* ���һ��У������ */
		if ( _FAILED == ApiEMU_CheckCalParaCRC( ) )///* ���˾�ֱ���˳�����ʼ��һ�¼���оƬ������break���˳�do while ѭ�� */// 
		{
			 break;		
		}
		
		for( V_ucCnti = 0; V_ucCnti<EMU_CALPARA_DEF_TAB_INDEX; V_ucCnti++ )
		{
			V_usRegAddress = EMU_CALPARA_DEF_TAB[V_ucCnti].ucEmuAddr;
			V_ulRegData = ApiEMU_ReadEmuReg( V_usRegAddress );
			
			if( Str_EmuCalPara.ulaCalPara[V_ucCnti] != V_ulRegData )
			{
				break;
			}
		}
		if( V_ucCnti < EMU_CALPARA_DEF_TAB_INDEX ) break;
		
		V_ucResult = _SUCCESS;  
		
	}while(0);
	
	/* ����д��ֱ�ӳ�ʼ��оƬ */
	if(( _FAILED == V_ucResult )&&(0==GStr_Flag.ucPowerOnFlag))
	{
		ApiEMU_EMUInit();
	}
	
	// У��ϵ������У��һ��
	ApiEMU_CheckKmsParaCRC();
	
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ���¼���˲ʱ��
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
uchar8 ApiEMU_UpdateUIP(void)
{
	uchar8   V_ucCnt_i;
	ulong32  V_ulaRegData[C_ucUIPREG_TAB_Index];
//	ulong32  V_ulRegData=0;
	ulong32  V_ulTemp;
//	FP32	 V_fPowerP,V_fPowerQ,V_fPowerS;
	
	FP64	 V_fPowerQ,V_fPowerS;	
	
	ApiEMU_CheckKmsParaCRC();		// У��һ��ϵ������
	
	//---------------------------------------------------------------------------
	// �ȶ�һ��ԭʼֵ
	for( V_ucCnt_i=0; V_ucCnt_i<C_ucUIPREG_TAB_Index; V_ucCnt_i++ )
	{
		V_ulaRegData[V_ucCnt_i] = ApiEMU_ReadEmuReg( C_ucUIPREG_TAB[V_ucCnt_i] ) ;
	}
 	// ��ʼ����˲ʱ��
	// 1. ��ѹ 
	//---------------------------------------------------------------------------
	if( Str_UIPKmsPara.ulaKmsuip[0] != 0 )
	{
		GStr_UIPGroup.ulVoltage[0] = 10.0 * V_ulaRegData[0] / Str_UIPKmsPara.ulaKmsuip[0];
	}
	else
	{
		GStr_UIPGroup.ulVoltage[0] = 0;
	}
	 V_ulTemp=GStr_UIPGroup.ulVoltage[0]*10;
	 LibPub_HEXtoBCDBytes(V_ulTemp,&GStr_UIPDisplay.ucVoltageA[0],4);///ת��ΪBCD������ʾ ��λС��
	 LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulVoltage[0],&GStr_UIPDisplay.ucCOMMVoltageA[0],4);///ת��ΪBCD����ͨ��
	
	//	 LibPub_Buffer4ToUlong32( uchar8 *p_ucBytesBuffer )
	// 2. ����
	//---------------------------------------------------------------------------
	if( Str_UIPKmsPara.ulaKmsuip[1] != 0 )
	{
		if( V_ulaRegData[1] & 0x00800000 )
		{
			V_ulaRegData[1] = ~(V_ulaRegData[1] | 0xFF000000) + 1;
		}
		GStr_UIPGroup.ulPower[0] =  1000.0 * V_ulaRegData[1] / Str_UIPKmsPara.ulaKmsuip[1] ;
	} 
	
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulPower[0],&GStr_UIPDisplay.ucPower[0],4);///ת��ΪBCD����ͨ�ź���ʾ
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulPower[0],&GStr_UIPDisplay.ucPowerA[0],4);//������ܹ��ʵ���A�๦��
	
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucPower[0],&GStr_UIPDisplay.ucCOMMPower[0],4);///����ͨ��
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucPowerA[0],&GStr_UIPDisplay.ucCOMMPowerA[0],4);///����ͨ��
	
	// 3. ����
	//---------------------------------------------------------------------------
	if( Str_UIPKmsPara.ulaKmsuip[2] != 0 )
	{
		GStr_UIPGroup.ulCurrent[0] = 1000.0 * V_ulaRegData[2] / Str_UIPKmsPara.ulaKmsuip[2] ;
	}
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulCurrent[0],&GStr_UIPDisplay.ucCurrentA[0],4);///ת��ΪBCD����ͨ�ź���ʾ
	
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucCurrentA[0],&GStr_UIPDisplay.ucCOMMCurrentA[0],4);///����ͨ��

	
	// 4. ��������x.xxx �й�����/���ڹ��ʣ����ڹ���=sqrt( �й�����ƽ��+�޹�����ƽ��)
	//---------------------------------------------------------------------------
	if( V_ulaRegData[3] & 0x00800000 )
	{
		V_ulaRegData[3] = ~(V_ulaRegData[3] | 0xFF000000) + 1;
	}
	V_fPowerS = V_ulaRegData[1];
	V_fPowerS = V_fPowerS * V_fPowerS;
	
	V_fPowerQ = V_ulaRegData[3];
	V_fPowerQ = V_fPowerQ * V_fPowerQ;
	
	V_fPowerS = V_fPowerS + V_fPowerQ;	// S = sqrt(P*P+Q*Q)
	V_fPowerS = sqrt(V_fPowerS);
	 
	if( V_ulaRegData[1] != 0 )
	{
		GStr_UIPGroup.ulFactory[0] = ( V_ulaRegData[1]*1000 ) / V_fPowerS;
	}
	else
	{
		GStr_UIPGroup.ulFactory[0] = 1000;
	}
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulFactory[0],&GStr_UIPDisplay.ucFactory[0],4);///ת��ΪBCD����ͨ�ź���ʾ
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulFactory[0],&GStr_UIPDisplay.ucFactoryA[0],4);//������ܹ�����������A�๦��
	
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucFactory[0],&GStr_UIPDisplay.ucCOMMFactory[0],4);///����ͨ��
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucFactoryA[0],&GStr_UIPDisplay.ucCOMMFactoryA[0],4);///����ͨ��
	
	
	// 5. Ƶ�� xx.xx
	//---------------------------------------------------------------------------
	if( V_ulaRegData[4] != 0 )
	{
		GStr_UIPGroup.ulFrequency = 245760000.0 / V_ulaRegData[4];
	}
	else
	{
		GStr_UIPGroup.ulFrequency = 5000;
	}
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulFrequency,&GStr_UIPDisplay.ucFrequency[0],4);
	
	//#if ( METER_TYPE == METER_TYPE_DDSYU666)
	//if(_TRUE==ApiEMU_GetDirP())
	//#else
	if(_FALSE==ApiEMU_GetDirP())
	//#endif
	{  
		GStr_Flag.ucRunState1 |=F_RUN_POWER_REVERSE;  //�ù��ʷ����־
		GStr_UIPDisplay.ucCOMMFactory[2] |=0x80;///���򣬵������ʹ����������λ��1
		GStr_UIPDisplay.ucCOMMFactoryA[2] |=0x80;///���򣬵������ʹ����������λ��1
		GStr_UIPDisplay.ucCOMMPower[1] |=0x80;///����  �������λ��1
		GStr_UIPDisplay.ucCOMMPowerA[1] |=0x80;///���� A�๦�����λ��1
		GStr_UIPDisplay.ucCOMMCurrent[1]|=0x80;///���� �������λ��1
		GStr_UIPDisplay.ucCOMMCurrentA[1]|=0x80;///����A��������λ��1
	}
	else
	{
		GStr_Flag.ucRunState1 &=~F_RUN_POWER_REVERSE; //�幦�ʷ����־
	}
		
	// 6. �ж��Ƿ�Ǳ��
	//---------------------------------------------------------------------------
	if( (EMUSR & EMUSR_NoPLd ) && (EMUSR & EMUSR_NoQLd ) )	// �й����޹�ͬʱǱ��״̬�£���������
	{
		// �����͹����ڳ��ڲ����㣬��������
		//----------------------------------------------------------------------
		if( (GStr_Flag.ucMeterMode & F_FACTORY_MODE)!= F_FACTORY_MODE )	
		{
			LibPub_MemSetBytes( &GStr_UIPDisplay.ucCurrentA[0], 0x00, 4 );
			LibPub_MemSetBytes( &GStr_UIPDisplay.ucPower[0], 0x00, 4 );
			LibPub_MemSetBytes( &GStr_UIPDisplay.ucPowerA[0], 0x00, 4 );
			
			LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMCurrentA[0], 0x00, 4 );    //����
			LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMPower[0], 0x00, 4 );
			LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMPowerA[0], 0x00, 4 );

			
		}
		// ֻҪ��Ǳ������������Ĭ��1�����ʷ���Ĭ������
		//----------------------------------------------------------------------
		LibPub_MemSetBytes( &GStr_UIPDisplay.ucFactory[0], 0x00, 4 );
		LibPub_MemSetBytes( &GStr_UIPDisplay.ucFactoryA[0], 0x00, 4 );
		
		LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMFactory[0], 0x00, 4 );
		LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMFactoryA[0], 0x00, 4 );		
		
		GStr_UIPDisplay.ucFactory[2]  = 0x10;
		GStr_UIPDisplay.ucFactoryA[2] = 0x10;
		
		GStr_Flag.ucRunState1 &=~F_RUN_POWER_REVERSE; //�幦�ʷ����־
	}
	
	
	//---------------------------------------------------------------------------
	
	return(_SUCCESS);
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ������оƬ�Ĵ�����ַ
 *
 *  @param    v_usRegAddress : �Ĵ�����ַ
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
ulong32 ApiEMU_ReadEmuReg( ushort16 v_usRegAddress )
{
	uchar8 V_ucRegAddress;
	
	V_ucRegAddress = (uchar8)v_usRegAddress; 
	return(ApiEMU_Read_ECADR( V_ucRegAddress ) );
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    д����оƬ�Ĵ���
 *
 *  @param    v_usRegAddress : �Ĵ�����ַ
 *  @param    v_ulRegData : Ҫд������
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void ApiEMU_WriteEmuReg( ushort16 v_usRegAddress, ulong32 v_ulRegData )
{
	uchar8 V_ucRegAddress;
	uchar8 V_ucCnt_i;
	
	V_ucRegAddress = (uchar8)v_usRegAddress;
	ApiEMU_Write_ECADR ( V_ucRegAddress, v_ulRegData );
	
	if (V_ucRegAddress == C_EPADR_W2GAIN)
	{
		ApiEMU_Write_ECADR ( C_EPADR_W2GAIN, v_ulRegData ); 
	}
	
	/* ���д����У��Ĵ�����Ҫ��һ��E2 */
	for ( V_ucCnt_i=0; V_ucCnt_i<EMU_CALPARA_DEF_TAB_INDEX; V_ucCnt_i++ )
	{
		if( EMU_CALPARA_DEF_TAB[V_ucCnt_i].ucEmuAddr == V_ucRegAddress  )
		{ 
			Str_EmuCalPara.ulaCalPara[V_ucCnt_i] = v_ulRegData;
			LibPub_WriteDataToE2prom( LIB_E2P_EMU_CALPARA, 0, (uchar8*)&Str_EmuCalPara.ulaCalPara[0] );
			break;
		}
	}
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ��У��
 *
 *  @param    v_usRegAddress : �Ĵ�����ַ
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void ApiEMU_CommStartCal( uchar8 v_ucChID )
{
	uchar8  V_ucCnt_i;
	ulong32 V_ulRegData;
	
	///* ���� *///
	V_ulRegData  = (ulong32)Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+3] << 24;
	V_ulRegData |= (ulong32)Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+2] << 16;
	V_ulRegData |= (ulong32)Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+1] << 8;
	V_ulRegData |= (ulong32)Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+0];
	
	V_ucCnt_i = EMU_CALPARA_DEF_TAB_INDEX;
	/* �ȳ�ʼ��һ��У��Ĵ��� */
	//---------------------------------------------------------------------------
	for ( V_ucCnt_i=0; V_ucCnt_i<EMU_CALPARA_DEF_TAB_INDEX; V_ucCnt_i++ )
	{
		ApiEMU_WriteEmuReg( EMU_CALPARA_DEF_TAB[V_ucCnt_i].ucEmuAddr, EMU_CALPARA_DEF_TAB[V_ucCnt_i].ulEmuRegData);  
	}
	
	/* дһ��UIPϵ�� */
	//---------------------------------------------------------------------------
	for ( V_ucCnt_i=0; V_ucCnt_i<C_usUIP_KMS_DEF_VAL_TAB_Index; V_ucCnt_i++ )
	{
		Str_UIPKmsPara.ulaKmsuip[V_ucCnt_i] = C_usUIP_KMS_DEF_VAL_TAB[V_ucCnt_i];
	}
	LibPub_WriteDataToE2prom( LIB_E2P_EMU_UIPKms, 0, (uchar8*)&Str_UIPKmsPara.ulaKmsuip[0] );
	
	
	/* дһ��У���� */
	//---------------------------------------------------------------------------
	ApiEMU_WriteEmuReg( C_EPADR_ICONT, V_ulRegData ); 
	
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ����У��
 *
 *  @param    v_ucChID : �Ĵ�����ַ
 *
 *  @return   xx
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
void ApiEMU_CommEndCal( uchar8 v_ucChID )
{
	uchar8 V_ucTemp;
	
	V_ucTemp = v_ucChID;
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ��У���
 *
 *  @param    v_ucChID : �Ĵ�����ַ
 *
 *  @return   �ɹ���_SUCCESS��ʧ�ܣ�_FAILED
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
uchar8 ApiEMU_CommErrCal( uchar8 v_ucChID )
{
	uchar8   V_ucResult = _SUCCESS,V_ucCnt_i;
	uchar8   V_ucRegAddress;		// �Ĵ�����ַ
	ulong32  V_ulRegData;
	
	do{
		
		if( 0x00 != Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0] )	///* ��֧��DI0==00 *///
		{
			V_ucResult = _FAILED; 
			break;  // ����do-whileѭ��
		} 
		
		///* ׼������ *///
		//---------------------------------------------------------------------------
		V_ulRegData  = (ulong32)Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+3] << 24;
		V_ulRegData |= (ulong32)Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+2] << 16;
		V_ulRegData |= (ulong32)Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+1] << 8;
		V_ulRegData |= (ulong32)Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+0];
		
		//---------------------------------------------------------------------------
		///* DI1:0x00 1.0L 100%Ib �й���������У�� ��Ӧ�Ĵ��� 0c *///
		///* DI1:0x09 0.5L 100%Ib ��λУ��  ��Ӧ�Ĵ��� 18*///
		///* DI1:0x0D 1.0L 5%Ib ����offsetУ��  ��Ӧ�Ĵ��� 78*///
		switch( Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+1] )
		{
			case 0x00:
			case 0x09:
			case 0x0D:
			{
				for ( V_ucCnt_i=0; V_ucCnt_i<EMU_COMM_EMUC_TAB_INDEX; V_ucCnt_i++ )
				{
					if( EMU_COMM_EMUC_TAB[V_ucCnt_i].ucCommDI1 == Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+1] )
					{
						V_ucRegAddress = EMU_COMM_EMUC_TAB[V_ucCnt_i].ucEmuAddr; 
						ApiEMU_WriteEmuReg( V_ucRegAddress, V_ulRegData );  
						break;
					}
				}
			}break;
			
			case 0x11:	///* ������ЧֵУ����Уһ��ϵ�� *///
			{ 
				// ����һ��Ǳ����ֵ
				ApiEMU_SetStartVal(); 
				
				// Уһ��ϵ��
				ApiEMU_SetUIPKms();
				
			}break;
			
			default:break;
		} 
	}while(0);
	
	//---------------------------------------------------------------------------
	return( V_ucResult );
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ����Ǳ����ֵ
 *
 *  @return   None
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
static void ApiEMU_SetStartVal(void)
{
	ulong32  V_ulRegData;
	
	V_ulRegData = ApiEMU_ReadEmuReg( C_ECADR_APWRA1 );	///* APWR1 Ϊ˲ʱ�й����ʣ������й����ܵ��ۼӣ���һ���Ĳ�����APWRA1 Ϊƽ���й����ʣ��Ƚ��ȶ� *///
	
	#if ( METER_TYPE == METER_TYPE_DDSYU666 )
	if( V_ulRegData & 0x00800000 )	//���������߷���������Ĺ���Ҫ���෴����
	{
		V_ulRegData = ~(V_ulRegData | 0xFF000000) + 1;
	}
	#endif
	V_ulRegData =  ( V_ulRegData*3 ) / 1000 ;			///* ��1������������75%����Ǳ����ֵ *///
	
	ApiEMU_WriteEmuReg( C_EPADR_SPTSP, V_ulRegData ); 
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    У˲ʱ��ϵ��
 *
 *  @return   None
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
uchar8 C_ucCurrentTab[]={ 10,15,25,50,100,150,200};

static uchar8 ApiEMU_SetUIPKms(void)
{
	ulong32  V_ulRegData;
	do
	{	 
		//---------------------------------------------------------------------------
		// KmsU  ��ѹ��Чֵ��ʽ XXX.X 
		V_ulRegData = ApiEMU_ReadEmuReg( C_ECADR_VRms );	///*   *///
		Str_UIPKmsPara.ulaKmsuip[0] =   V_ulRegData / 220.0; 
		
		//---------------------------------------------------------------------------
		// KmsP ������Чֵ��ʽ XX.XXXX 
		V_ulRegData = ApiEMU_ReadEmuReg( C_ECADR_APWRA1 );	///* APWR1 Ϊ˲ʱ�й����ʣ������й����ܵ��ۼӣ���һ���Ĳ�����APWRA1 Ϊƽ���й����ʣ��Ƚ��ȶ� *///
		
		#if ( METER_TYPE == METER_TYPE_DDSYU666 )
		if( V_ulRegData & 0x00800000 )
		{
			V_ulRegData = ~(V_ulRegData | 0xFF000000) + 1;
		}
		#endif
		Str_UIPKmsPara.ulaKmsuip[1] =   V_ulRegData / ((C_ucCurrentTab[GStr_FunConfigPara.ucFunCurrentVal]*220.0)/1000.0);
		
		//---------------------------------------------------------------------------
		// KmsI1 ������Чֵ��ʽ XXX.XXX
		V_ulRegData = ApiEMU_ReadEmuReg( C_ECADR_I1Rms );	///*   */// 
		Str_UIPKmsPara.ulaKmsuip[2] =   V_ulRegData / ( C_ucCurrentTab[GStr_FunConfigPara.ucFunCurrentVal] / 10.0 ); 
		
		//---------------------------------------------------------------------------
		LibPub_WriteDataToE2prom( LIB_E2P_EMU_UIPKms, 0, (uchar8*)&Str_UIPKmsPara.ulaKmsuip[0] );
		
	}while(0);
	
	//---------------------------------------------------------------------------
	return _SUCCESS;
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ��ȡ���ʷ���
 *
 *  @return   _FALSE������  _TRUE������
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
uchar8 ApiEMU_GetDirP(void)
{
	ulong32  V_ulRegData;
	  
	V_ulRegData = ApiEMU_ReadEmuReg( C_ECADR_APWRA1 );	///*   */// 
	
	if( V_ulRegData & 0x00800000 )
	{
		#if ( METER_TYPE == METER_TYPE_DDSY666 )
		return _FALSE;	// ����
		#else
		return _TRUE;	//���������߷�������������ʵ��Ϊ����
		#endif
	}
	#if ( METER_TYPE == METER_TYPE_DDSY666 )
	return _TRUE;		// ����
	#else
	return _FALSE;
	#endif
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    У��У�����CRC�Ƿ���ȷ
 *
 *  @return   _FALSE:������ȷ  _TRUE�����ݴ���
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
static uchar8 ApiEMU_CheckCalParaCRC( void )
{
	if ( _TRUE != LibPub_CrcCheck( (uchar8*)&Str_EmuCalPara.ulaCalPara[0], EMU_CALPARA_Type_LEN-2, Str_EmuCalPara.usCRC16 ) )
	{
		LibPub_ReadDataFromE2prom( LIB_E2P_EMU_CALPARA, 0, (uchar8*)&Str_EmuCalPara.ulaCalPara[0] );
		return _FAILED;
	}
	
	return _SUCCESS;
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    У��У�����CRC�Ƿ���ȷ
 *
 *  @return   _FALSE:������ȷ  _TRUE�����ݴ���
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
static uchar8 ApiEMU_CheckKmsParaCRC( void )
{
	if ( _TRUE != LibPub_CrcCheck( (uchar8*)&Str_UIPKmsPara.ulaKmsuip[0], EMU_UIPKms_Type_LEN-2, Str_UIPKmsPara.usCRC16 ) )
	{
		LibPub_ReadDataFromE2prom( LIB_E2P_EMU_UIPKms, 0, (uchar8*)&Str_UIPKmsPara.ulaKmsuip[0] );
		return _FAILED;
	}
	
	return _SUCCESS;
}

#endif 
