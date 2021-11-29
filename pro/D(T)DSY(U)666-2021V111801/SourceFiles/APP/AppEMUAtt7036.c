/*******************************************************************************************************
**** Copyright��  (c)Copyright 2019,�㽭��̩�����Ǳ��������ι�˾,���ܱ�Ӧ���з�                       
****                            All rights reserved.                                                 
**** FileName:    AppEMUAtt7036.c                                                                          
**** Brief:       7036����оƬ�ļ�                                                                    
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
 *  ���ļ����к�����ǰ׺ΪApiEMU_
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
#if ( METER_TYPE == METER_TYPE_DTSY666)
/*----------------< �궨���� >----------------------------------*/

#define chk_reg_num  	28
#define const_reg_num 	11
#define C_ClearVoltage   50///��ѹ����5V����
/*----------------< �������� >----------------------------------*/
uchar8 xdata GA_EmuRegData[TRIPEMU_CALPARA_Type_LEN];

const ulong32 code Dl_Cpu_Init[chk_reg_num]=
{
	0x37007FFF,///��λ����0
	0x60000000,///��λ����1   ///ǰ��4��Ϊ��������
	0x36000030,///�𶯹��ʷ�ֵ����
	0x1E000050,///HFCONST
	
	0x04000000,///A���й���������
	0x05000000,///B
	0x06000000,///C
	0x07000000,///A���޹���������
	0x08000000,///B
	0x09000000,///C
	0x0A000000,///A�����ڹ�������
	0x0B000000,///B
	0x0C000000,///C
	0x0D000000,///A����λУ��0
	0x0E000000,///B
	0x0F000000,///C
	0x10000000,///A����λУ��1
	0x11000000,///B
	0x12000000,///C
	0x17000000,///A���ѹ����
	0x18000000,///B���ѹ����
	0x19000000,///C���ѹ����
	0x1A000000,///A���������
	0x1B000000,///B���������
	0x1C000000,///C���������
	0x61000000,///A����λУ��2
	0x62000000,///B����λУ��2
	0x63000000,///C����λУ��2
};

const ulong32 code Const_Cpu_Init[const_reg_num]=
{
	0x0100B97E  ,///ģʽ��ؿ���
	0x0300F884,	 ///EMUģ����ƼĴ���
	0x31003427,	 ///��·ģ����ƼĴ���
	0x02000100, ///ADC����ѡ��
	0x1F000000,///ʧѹ��ֵѡ��
	0x1D000160,///�𶯵�������
	0x27000007,///A�������ЧֵoffsetУ��
	0x28000007,///B�������ЧֵoffsetУ��?
	0x29000007,///C�������ЧֵoffsetУ��
	0x70000000,///EMUCFG
	0x33003300,///���峣������
	
};

///�������ݼĴ���
const uchar8 Str_EnergyRegADDr[]=
{
	C_ActiveEnergy_TReg,
	C_ActiveEnergy_AReg,
	C_ActiveEnergy_BReg,
	C_ActiveEnergy_CReg,
	C_ReativeEnergy_TReg,
	C_ReativeEnergy_AReg,
	C_ReativeEnergy_BReg,
	C_ReativeEnergy_CReg,
	C_ApparentEnergy_TReg,
	C_ApparentEnergy_AReg,
	C_ApparentEnergy_BReg,
	C_ApparentEnergy_CReg
};
///˲ʱ�����ݼĴ���
const uchar8 Str_RmsRegADDr[]=
{
	C_rPa,		//A���й�����0
	C_rPb,		//B���й�����1
	C_rPc,		//C���й�����2
	C_rPt,		//�����й�����3
	C_UaRms	,   //A���ѹ��Чֵ4
	C_UbRms	,   //B���ѹ��Чֵ5
    C_UcRms	,   //C���ѹ��Чֵ6
	C_UtRms	,	//�����ѹ��Чֵ����7
	C_IaRms	,	//A�������Чֵ8
	C_IbRms	,	//B�������Чֵ9
	C_IcRms	,	//C�������Чֵ10
	C_ItRms	,	//���������Чֵ11
	C_Pfa	,	//A�๦������12
	C_Pfb	,	//B�๦������13
	C_Pfc	,	//C�๦������14
	C_Pft	,	//���๦������15
	C_Freq	,	//��Ƶ��16
};	

#define C_ucUIPREG_TAB_Index  sizeof(Str_RmsRegADDr)
	        
///У����
EMU_COMM_TRIPCAL_TAB_Type code EMU_COMM_TRIPEMUC_TAB[]={   ////�ɶ�д
	{ 0x00,		{C_PGainA    	,   C_PGainB 		,C_PGainC		}	,	},  ///�й���������У��
	{ 0x01,		{C_QGainA   	,   C_QGainB 		,C_QGainC		}	,	},  ///�޹���������У��
	{ 0x02,		{C_SGainA    	,   C_SGainB 		,C_SGainC		}	,	},  ///���ڹ�������У��
	{ 0x04,		{C_UGainA    	,   C_UGainB 		,C_UGainC		}	,	},  ///��ѹ����У��
	{ 0x06,		{C_IGainA    	,   C_IGainB 		,C_IGainC		}	,	},  ///��������У��
	{ 0x08,		{C_PhSregApq0   ,   C_PhSregBpq0 	,C_PhSregCpq0	}	,	},  ///�������λУ��
	{ 0x09,		{C_PhSregApq1   ,   C_PhSregBpq1 	,C_PhSregCpq1	}	,	},  ///�е�����λУ��
	{ 0x0A,		{C_PhSregApq2   ,   C_PhSregBpq2 	,C_PhSregCpq2	}	,	},  ///С������λУ��	
};

EMU_Read_TRIPCAL_TAB_Type code EMU_READ_TRIPEMUC_TAB[]={   ////ֻ��
	{ 0x03,		{	C_rPa    	,   C_rPb 		,C_rPc		,C_rPt  	},	},  ///����
	{ 0x05,		{	C_UaRms   	,   C_UbRms 	,C_UcRms	,C_UtRms	},	},  ///��ѹ
	{ 0x07,		{	C_IaRms    	,   C_IbRms 	,C_IcRms	,C_ItRms	},	},  ///����
	
};

/*----------------< �������� >----------------------------------*/

TRIPEMU_CALPARA_Type	Str_TRIPEmuCalPara;		// У�����

TRIPEMU_UIPKms_Type		Str_TRIPUIPKmsPara;		// ˲ʱ��ϵ��
/*----------------< �������� >----------------------------------*/
static uchar8 AppEMU_TripCheckCalParaCRC( void );
static void AppEMU_ClearCalReg_MeterIC(void);

void  ApiEMU_EMUInit();
uchar8 AppEMU_TripReadEmuReg( uchar8 v_ucChID );
void ApiEMU_CommEndCal( uchar8 v_ucChID );
uchar8 ApiEMU_CommErrCal( uchar8 v_ucChID );
void ApiEMU_CommStartCal(v_ucChID);
void AppEMU_TRipCommSetReg( uchar8 v_ucChID );
void AppEMU_WriteOneReg_MeterIC(uchar8 *P_Data,uchar8 V_RegAddr);
void AppEMU_WriteRegToEE(uchar8 *P_Data,uchar8 V_RegAddr);
void  ApiEMU_EMUParaCheck();
void ApiEMU_DisOrEnable(uchar8 v_ucWorkMode);
	
void Hal_EraseFlashSector(INT16U adr, INT8U dat, INT8U sta);
INT8U Hal_ReadEEPROM(INT8U  *Dst, INT16U Src, INT16U Len);
INT8U Hal_WriteEEPROM(INT16U Dst, INT8U  *Src, INT16U Len);
/*----------------< �������� >----------------------------------*/

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
		SPIDrv_Eable_MeterIC();
	}
	else	// �رռ���ģ��
	{
		SPIDrv_Disable_MeterIC();
	}
}

///*****************************************************************************************///
///*����ԭ�ͣ�void SPIDrv_WriteEnable_MeterIC(void)
///*��������������оƬдʹ��
///*�����������
///*�����������
///*���ز�������
///*����˵��������оƬдʹ����Ҫ�ǶԼ���оƬC9����Ĵ������в�����д��0x000000Ϊдʧ�ܣ�д��0x00005AΪдʹ��
///*���û��ƣ�
///*��    ע��
///*****************************************************************************************///
void AppEMU_WriteEnable_MeterIC(void)
{
	uchar8 V_Data[4],i;
	ulong32 V_EnWriteData;
	V_EnWriteData=0xC900005A;	//дʹ��ֱ��д��0xC900005A���ֽ�Ϊ����Ĵ�����ַ,�����ֽ�Ϊд������
	SPIDrv_Eable_MeterIC();
	LibPub_Ulong32ToBuffer4(&V_Data[0],V_EnWriteData);///��ת��Ϊ��ˣ�Ҫ��дC9��data0
	for(i=4;i>0;i--)
	{
		SPIDrv_SendBtye(V_Data[4-i]);
	}
	SPIDrv_Disable_MeterIC();
}
///*****************************************************************************************///
///*����ԭ�ͣ�void SPIDrv_WriteDisable_MeterIC(void)
///*��������������оƬдʧ��
///*�����������
///*�����������
///*���ز�������
///*����˵��������оƬдʹ����Ҫ�ǶԼ���оƬC9����Ĵ������в�����д��0x000000Ϊдʧ�ܣ�д��0x00005AΪдʹ��
///*���û��ƣ�
///*��    ע��
///*****************************************************************************************///
void AppEMU_WriteDisable_MeterIC(void)
{
	uchar8 V_Data[4],i;
	ulong32 V_DisWriteData;
	V_DisWriteData=0xC9000000;	//дʧ��ֱ��д��0xc9000000���ֽ�Ϊ����Ĵ�����ַ,�����ֽ�Ϊд������
	SPIDrv_Eable_MeterIC();
	LibPub_Ulong32ToBuffer4(&V_Data[0],V_DisWriteData);///��ת��Ϊ��ˣ�����дdata0
	for(i=0;i<4;i++)
	{
		SPIDrv_SendBtye(V_Data[i]);
	}
	SPIDrv_Disable_MeterIC();
}

///*****************************************************************************************///
///*����ԭ�ͣ�void SPIDrv_ReadDataModeSet(uchar8 V_Data)
///*����������ѡ�����оƬ�Ĵ�����ȡ����:��ȡ���������Ĵ����Ͷ�ȡУ������Ĵ���
///*���������00=��ȡ�������ݼĴ�����01=��ȡУ������Ĵ���
///*�����������
///*���ز�������
///*����˵������ȡ����оƬ�Ĵ������ú�����ͨ����������Ĵ���C6Ϊ0x000000��ȡ���������Ĵ�����Ϊ0x00005A��ȡУ������Ĵ���
///*���û��ƣ�
///*��    ע��
///*****************************************************************************************///
void AppEMU_ReadDataModeSet(uchar8 V_ModeData)
{
	uchar8 V_Data[4],i;
	ulong32 V_EnWriteData;
	if(V_ModeData==C_MeterPara)
	{
		V_EnWriteData=0xC6000000;	//����оƬ����Ϊ��ȡ(����)�������ֽ�Ϊ�Ĵ�����ַ�������ֽ�Ϊд������
	}
	else
	{
		V_EnWriteData=0xC600005A;	//����оƬ����Ϊ��ȡ(У��)�������ֽ�Ϊ�Ĵ�����ַ�������ֽ�Ϊд������
	}
	SPIDrv_Eable_MeterIC();		//CSʹ�ܼ���оƬ
	LibPub_Ulong32ToBuffer4(&V_Data[0],V_EnWriteData);
	for(i=4;i>0;i--)
	{
		SPIDrv_SendBtye(V_Data[4-i]);
	}
	SPIDrv_Disable_MeterIC();	//CSʧ�ܼ���оƬ
}
///*****************************************************************************************///
///*����ԭ�ͣ�void SPI_ReadOneReg_MeterIC(uchar8 V_usRegAddr, uchar8* P_Data)
///*�����������Ӽ���оƬ���������Ĵ����ж�ȡ���ֽ�����
///*���������
///*		uchar8 V_usRegAddr��Ԥ��ȡ����оƬ�Ĵ�����ַ
///*		uchar8* P_Data������ת��ָ��
///*		uchar8 V_MeaORCal  00:��ȡ���������Ĵ���   01:��ȡУ������Ĵ���
///*��������� uchar8* P_Data����ָ���д洢V_usRegAddr��ַ�µ����ֽ�����(7038оƬ��ȡ�ļ�������Ϊ���ֽ���Ч��У�����Ϊ���ֽ���Ч)
///*���ز�������ȡ�ɹ�C_OK
///*����˵����
///*���û��ƣ�
///*��    ע��
///*****************************************************************************************///
void AppEMU_ReadOneReg_MeterIC(uchar8 V_usRegAddr, uchar8* P_Data,uchar8 V_MeaORCal)
{
	AppEMU_ReadDataModeSet(V_MeaORCal);	
	SPIDrv_Eable_MeterIC();
	SPIDrv_SendBtye(V_usRegAddr&0x7F);
	LibPub_Delay2us();
	*P_Data=SPIDrv_ReceiveByte();
	*(P_Data+1)=SPIDrv_ReceiveByte();
	*(P_Data+2)=SPIDrv_ReceiveByte();
	SPIDrv_Disable_MeterIC();
}

///*****************************************************************************************///
///*����ԭ�ͣ�uchar8 SPIDrv_WriteOneReg_MeterIC(uchar8 *P_Data,uchar8 V_RegAddr)
///*���������������ֽ�����д�����оƬ�Ĵ���ָ����ַ(��������дУ������Ĵ���)
///*���������
///*		uchar8 *P_Data��Ԥд������ָ��
///*		uchar8 V_RegAddr������оƬ�Ĵ�����ַ
///*�����������37
///*���ز�����
///*		C_OK��д��ɹ�
///*����˵����ͨ��дһ�ֽ����ݣ�д�뽫��ַ����ַ������λҪ��1��Ȼ�����3��дһ�ֽ����ݣ����Ӹ��ֽڵ����ֽڽ�3�ֽ�����д�����оƬ
///*���û��ƣ�
///*��    ע��
///*****************************************************************************************///
void AppEMU_WriteOneReg_MeterIC(uchar8 *P_Data,uchar8 V_RegAddr)
{
	uchar8 V_Data[3],i;
	V_Data[0]=*P_Data;
	V_Data[1]=*(P_Data+1);
	V_Data[2]=*(P_Data+2);
	AppEMU_WriteEnable_MeterIC();
	SPIDrv_Eable_MeterIC();
	SPIDrv_SendBtye(V_RegAddr|0x80);	//��ַ������λ��1��д������
	for(i=3;i>0;i--)
	{
		SPIDrv_SendBtye(V_Data[3-i]);
	}
	SPIDrv_Disable_MeterIC();
	AppEMU_WriteDisable_MeterIC();
}
///*****************************************************************************************///
///*����ԭ�ͣ�uchar8 AppEMU_WriteRegToEE(uchar8 *P_Data,uchar8 V_RegAddr)
///*���������������ֽ�����д����EE(��������дУ������Ĵ���)
///*���������
///*		uchar8 *P_Data��Ԥд������ָ��
///*		uchar8 V_RegAddr������оƬ�Ĵ�����ַ
///*�����������37
///*���ز�����
///*		C_OK��д��ɹ�
///*����˵����ͨ��дһ�ֽ����ݣ�д�뽫��ַ����ַ������λҪ��1��Ȼ�����3��дһ�ֽ����ݣ����Ӹ��ֽڵ����ֽڽ�3�ֽ�����д�����оƬ
///*���û��ƣ�
///*��    ע��
///*****************************************************************************************///
void AppEMU_WriteRegToEE(uchar8 *P_Data,uchar8 V_RegAddr)
{
	uchar8 V_Data[3],i,V_WriteData[4];
	V_Data[0]=*P_Data;
	V_Data[1]=*(P_Data+1);
	V_Data[2]=*(P_Data+2);
	GStr_Flag.ucWrE2promSafeByte|=C_SafeByte_Step1;
	for ( i=0; i<chk_reg_num; i++ )
	{
		LibPub_Ulong32ToBuffer4(V_WriteData, Dl_Cpu_Init[i]);
		if( V_WriteData[0] == V_RegAddr  )
		{ 
			GStr_Flag.ucWrE2promSafeByte|=C_SafeByte_Step2;
			V_WriteData[0] = V_RegAddr;
			LibPub_MemCopyBytes(V_Data, &V_WriteData[1] ,3);
			Hal_ReadEEPROM(GA_EmuRegData,CAddr_EMU_CALPARA_Note,TRIPEMU_CALPARA_Type_LEN);
			LibPub_MemCopyBytes(V_WriteData,&GA_EmuRegData[4*i],4);
			
			LibPub_MemCopyBytes(&GA_EmuRegData[0],(uchar8*)&Str_TRIPEmuCalPara.ulaCalPara[0],TRIPEMU_CALPARA_Type_LEN-2);
			Str_TRIPEmuCalPara.usCRC16=LibPub_CRC16_CCITT((uchar8*) &Str_TRIPEmuCalPara.ulaCalPara[0], TRIPEMU_CALPARA_Type_LEN-2);
			////����RAM
			GStr_Flag.ucWrE2promSafeByte|=C_SafeByte_Step3;
			Hal_EraseFlashSector(CAddr_EMU_CALPARA_Note, 0x00, FLASH_RW_ENABLE);///������EE��У������
			Hal_EraseFlashSector(CAddr_EMU_CALPARA_BAK_Note, 0x00, FLASH_RW_ENABLE);

			Hal_WriteEEPROM(CAddr_EMU_CALPARA_Note, (uchar8*)&Str_TRIPEmuCalPara.ulaCalPara[0], TRIPEMU_CALPARA_Type_LEN);
			Hal_WriteEEPROM(CAddr_EMU_CALPARA_BAK_Note, (uchar8*)&Str_TRIPEmuCalPara.ulaCalPara[0], TRIPEMU_CALPARA_Type_LEN);///����д����EE
			GStr_Flag.ucWrE2promSafeByte=C_SafeByte_Step0;
			break;
		}
	}
}
///***********************************************************************************///
///*����ԭ�ͣ�void SPIDrv_ClearCalReg_MeterIC(void)
///*�������������У��Ĵ���
///*�����������
///*�����������
///*���ز�������
///*����˵����
///*���û��ƣ�
///*��    ע��
///***********************************************************************************///
static void AppEMU_ClearCalReg_MeterIC(void)
{
	uchar8 V_Addr,V_WriteData[4];
	uchar8 i;
	LibPub_MemSetBytes(V_WriteData,0,4);	
	V_Addr=0xC3;
	AppEMU_WriteOneReg_MeterIC(V_WriteData,V_Addr);//0xC3��ַд��000000,��ʼ������оƬУ��Ĵ�����ֵ
	LibPub_DelayNms(25);
	LibPub_DelayNms(25);
	SPIDrv_ENSPIMode();
	SPIDrv_Eable_MeterIC();
	
	for(i=0;i<const_reg_num;i++)
	{
		LibPub_Ulong32ToBuffer4(V_WriteData, Const_Cpu_Init[i]);
		V_Addr=V_WriteData[0];
		AppEMU_WriteOneReg_MeterIC(&V_WriteData[1],V_Addr);	
	}
}

///*****************************************************************************************///
///*����ԭ�ͣ�void SPIDrv_ClearEnergyData_MeterIC(void)
///*���������������оƬ���ܼĴ���
///*�����������
///*�����������
///*���ز�������
///*����˵����ͨ����ȡ����оƬ�ĵ��ܼĴ���������������ܼĴ�����Ŀ�ģ�����оƬ����Ϊ������
///*���û��ƣ�
///*��    ע��
///*****************************************************************************************///
void AppEMU_ClearEnergyData_MeterIC(void)
{
	uchar8 i,V_Data[3];
	for(i=0;i<sizeof(Str_EnergyRegADDr);i++)
	{
		AppEMU_ReadOneReg_MeterIC(Str_EnergyRegADDr[i], V_Data,0x00);
	}
}
///*****************************************************************************************///
///*����ԭ�ͣ�void SPIDrv_SoftwareRESET_MeterIC(void)
///*����������ͨ����λRESET�ܽţ���λ����оƬ�������������оƬ�������ݼĴ���
///*�����������
///*�����������
///*���ز�������
///*����˵��
///*���û��ƣ�
///*��    ע��
///*****************************************************************************************///
void AppEMU_SoftwareRESET_MeterIC(void)
{
	uchar8 V_Addr,V_WriteData[4];
	LibPub_MemSetBytes(V_WriteData,0,4);	
	V_Addr=0xD3;
	AppEMU_WriteOneReg_MeterIC(V_WriteData,V_Addr);//0xD3��ַд��000000
	LibPub_DelayNms(1);
	SPIDrv_ENSPIMode();		
	AppEMU_ClearCalReg_MeterIC();
}

///*****************************************************************************************///
///*����ԭ�ͣ�void  AppEMU_EMUPara_Check(void)
///*����������У�����Ч��
///*���������
///*�����������
///*���ز�������
///*����˵����
///*���û��ƣ�
///*��    ע��
///*****************************************************************************************///
void  ApiEMU_EMUParaCheck()
{
	uchar8   V_ucResult = _FAILED;
	uchar8   V_ucCnti,V_Addr,V_ReadData[4],V_WriteData[4];
	
	do{

		/* �ȼ��̶�ֵ  */
		for( V_ucCnti = 0; V_ucCnti<const_reg_num; V_ucCnti++ )
		{
			LibPub_Ulong32ToBuffer4(V_WriteData, Const_Cpu_Init[V_ucCnti]);
			V_Addr=V_WriteData[0];
			AppEMU_ReadOneReg_MeterIC(V_Addr, &V_ReadData[1],C_EMUPara);
			
			if( C_Equal!=LibPub_CompareData(&V_ReadData[1], &V_WriteData[1], 3,CMP_MODE_HIGHT) )
			{
				break;
			}
		}
		if( V_ucCnti < const_reg_num ) break;
		
		/* ���һ��У������ */
		if ( _FAILED == AppEMU_TripCheckCalParaCRC() )///* ���˾�ֱ���˳�����ʼ��һ�¼���оƬ������break���˳�do while ѭ�� */// 
		{
			 break;		
		}
		
		for( V_ucCnti = 0; V_ucCnti<chk_reg_num; V_ucCnti++ )
		{
			LibPub_Ulong32ToBuffer4(V_WriteData, Str_TRIPEmuCalPara.ulaCalPara[V_ucCnti]);
			V_Addr=V_WriteData[0];
			AppEMU_ReadOneReg_MeterIC(V_Addr, &V_ReadData[1],C_EMUPara);
				
			if( C_Equal!=LibPub_CompareData(&V_ReadData[1], &V_WriteData[1], 3,CMP_MODE_HIGHT) )
			{
				break;
			}
		}
		if( V_ucCnti < chk_reg_num ) break;
		
		V_ucResult = _SUCCESS;  
		
	}while(0);
	
	/* ����д��ֱ�ӳ�ʼ��оƬ */
	if(( _FAILED == V_ucResult )&&(0==GStr_Flag.ucPowerOnFlag))
	{
		ApiEMU_EMUInit();
	}
	
//	// У��ϵ������У��һ��
//	ApiEMU_CheckKmsParaCRC();
}
///*****************************************************************************************///
///*����ԭ�ͣ�void  SPIDrv_Initial_MeterIC (void)
///*������������ʼ������оƬ�����ü���оƬ���Ĵ���
///*���������
///*�����������
///*���ز�������
///*����˵����
///*���û��ƣ�
///*��    ע��
///*****************************************************************************************///
void  ApiEMU_EMUInit()
{
	uchar8 V_CalRegData[3],i,V_Addr,V_WriteData[4];
	ushort16 V_Data;
	
	EMUSR &= ~EMUSR_DSPEN;
	IEN1 &= ~IEN1_EEMU;///�ر�SOC������Ԫ
	
	AppEMU_SoftwareRESET_MeterIC();

	 Hal_ReadEEPROM((uchar8*)&Str_TRIPEmuCalPara.ulaCalPara[0],CAddr_EMU_CALPARA_Note,TRIPEMU_CALPARA_Type_LEN);
	 if(_TRUE!=LibPub_CrcCheck((uchar8*)&Str_TRIPEmuCalPara.ulaCalPara[0],TRIPEMU_CALPARA_Type_LEN-2,Str_TRIPEmuCalPara.usCRC16))
	 {
		 Hal_ReadEEPROM((uchar8*)&Str_TRIPEmuCalPara.ulaCalPara[0],CAddr_EMU_CALPARA_BAK_Note,TRIPEMU_CALPARA_Type_LEN);///������
		 {
			 if(_TRUE!=LibPub_CrcCheck((uchar8*)&Str_TRIPEmuCalPara.ulaCalPara[0],TRIPEMU_CALPARA_Type_LEN-2,Str_TRIPEmuCalPara.usCRC16))
			 {	
				for(i=0;i<chk_reg_num;i++)
				{
					Str_TRIPEmuCalPara.ulaCalPara[i]=Dl_Cpu_Init[i];///��EE�����ݴ�ȡĬ��ֵ
				}	
			 }	 
		 }
	 }

	AppEMU_ClearCalReg_MeterIC();		//�����оƬУ������Ĵ���,˳��д��һ�¹̶�ֵ
	
	LibPub_MemSetBytes(V_CalRegData,0,3);
	V_Data=C_EMUCfg&0x0FFF;	//���üĴ���
	LibPub_Ushort16ToBuffer2(&V_CalRegData[1],V_Data);
	AppEMU_WriteOneReg_MeterIC(V_CalRegData,C_EMUCfg_Reg);
	
	for(i=0;i<chk_reg_num;i++)
	{
		LibPub_Ulong32ToBuffer4(V_WriteData, Str_TRIPEmuCalPara.ulaCalPara[i]);
		V_Addr=V_WriteData[0];
		AppEMU_WriteOneReg_MeterIC(&V_WriteData[1],V_Addr);
	}
	
	LibPub_MemSetBytes(V_CalRegData,0,3);
	V_Data=C_EMUCfg;	//���üĴ���
	LibPub_Ushort16ToBuffer2(&V_CalRegData[1],V_Data);
	AppEMU_WriteOneReg_MeterIC(V_CalRegData,C_EMUCfg_Reg);
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
static uchar8 AppEMU_TripCheckCalParaCRC( void )
{
	if ( _TRUE != LibPub_CrcCheck( (uchar8*)&Str_TRIPEmuCalPara.ulaCalPara[0], TRIPEMU_CALPARA_Type_LEN-2, Str_TRIPEmuCalPara.usCRC16 ) )
	{
		 Hal_ReadEEPROM((uchar8*)&Str_TRIPEmuCalPara.ulaCalPara[0],CAddr_EMU_CALPARA_Note,TRIPEMU_CALPARA_Type_LEN);
		 if(_TRUE!=LibPub_CrcCheck((uchar8*)&Str_TRIPEmuCalPara.ulaCalPara[0],TRIPEMU_CALPARA_Type_LEN-2,Str_TRIPEmuCalPara.usCRC16))
		 {
			 Hal_ReadEEPROM((uchar8*)&Str_TRIPEmuCalPara.ulaCalPara[0],CAddr_EMU_CALPARA_BAK_Note,TRIPEMU_CALPARA_Type_LEN);///������
			 {
				 if(_TRUE!=LibPub_CrcCheck((uchar8*)&Str_TRIPEmuCalPara.ulaCalPara[0],TRIPEMU_CALPARA_Type_LEN-2,Str_TRIPEmuCalPara.usCRC16))
				 {	
					return _FAILED;
				 }	 
			 }
		 }

	}

	return _SUCCESS;
}

///*------------------------------------------------------------------------------------------------------*/
///**
// *  @brief    У��ϵ��CRC�Ƿ���ȷ
// *
// *  @return   _FALSE:������ȷ  _TRUE�����ݴ���
// *
// *  @note     xx
// *
// */
///*------------------------------------------------------------------------------------------------------*/
//static uchar8 AppEMU_TripCheckKmsParaCRC( void )
//{
//	if ( _TRUE != LibPub_CrcCheck( (uchar8*)&Str_TRIPUIPKmsPara.ulaKmsuip, TRIPEMU_UIPKms_Type_LEN-2, Str_TRIPUIPKmsPara.usCRC16 ))
//	{
//		LibPub_ReadDataFromE2prom( LIB_E2P_EMU_UIPKms, 0, (uchar8*)&Str_TRIPUIPKmsPara.ulaKmsuip);
//		return _FAILED;
//	}
//	
//	return _SUCCESS;
//}
///*------------------------------------------------------------------------------------------------------*/
///**
// *  @brief    ��У��
// *
// *  @return   
// *
// *  @note     xx
// *///��Ҫ�ǳ�ʼ��У��Ĵ���
// */
///*------------------------------------------------------------------------------------------------------*/
void ApiEMU_CommStartCal(v_ucChID)
{
	uchar8 V_Addr,V_WriteData[4],i;

	GStr_Flag.ucWrE2promSafeByte|=C_SafeByte_Step1;
	
	LibPub_MemSetBytes( GA_EmuRegData, 0, TRIPEMU_CALPARA_Type_LEN );
	
	AppEMU_ClearCalReg_MeterIC();///��У��Ĵ���
	
	GStr_Flag.ucWrE2promSafeByte|=C_SafeByte_Step2;
	for( i=0;i<chk_reg_num;i++ )///У��Ĵ���дĬ��ֵ
	{
		LibPub_Ulong32ToBuffer4(V_WriteData, Dl_Cpu_Init[i]);
		V_Addr=V_WriteData[0];
		AppEMU_WriteOneReg_MeterIC(&V_WriteData[1],V_Addr);
	}
		GStr_Flag.ucWrE2promSafeByte|=C_SafeByte_Step3;
	Hal_EraseFlashSector(CAddr_EMU_CALPARA_Note, 0x00, FLASH_RW_ENABLE);///������EE��У������
	Hal_EraseFlashSector(CAddr_EMU_CALPARA_BAK_Note, 0x00, FLASH_RW_ENABLE);
	
	Hal_WriteEEPROM(CAddr_EMU_CALPARA_Note, (uchar8*)&Dl_Cpu_Init[0], TRIPEMU_CALPARA_Type_LEN);
	Hal_WriteEEPROM(CAddr_EMU_CALPARA_BAK_Note, (uchar8*)&Dl_Cpu_Init[0], TRIPEMU_CALPARA_Type_LEN);///����д����EE
	GStr_Flag.ucWrE2promSafeByte =C_SafeByte_Step0;
//	LibPub_MemCopyBytes((uchar8*) &Dl_Cpu_Init[0], (uchar8*) &Str_TRIPEmuCalPara.ulaCalPara[0], chk_reg_num*4);
//	Str_TRIPEmuCalPara.usCRC16=LibPub_CRC16_CCITT((uchar8*) &Str_TRIPEmuCalPara.ulaCalPara[0], chk_reg_num*4);
}
///*------------------------------------------------------------------------------------------------------*/
///**
// *  @brief   ��������
// *
// *  @return   
// *
// *  @note     xx
// *///��Ҫ�������üĴ�����д��HFCONST
// */
///*------------------------------------------------------------------------------------------------------*/
void AppEMU_TRipCommSetReg( uchar8 v_ucChID )
{
	uchar8 V_WriteData[4];
	
//	Hal_EraseFlashSector(CAddr_EMU_CALPARA_Note, 0x00, FLASH_RW_ENABLE);///������EE��У������
//	Hal_EraseFlashSector(CAddr_EMU_CALPARA_BAK_Note, 0x00, FLASH_RW_ENABLE);	
	V_WriteData[0]=0x37;  ///��λ����0
	V_WriteData[1]=0;
	V_WriteData[2]=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+41];
	V_WriteData[3]=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+40];
	AppEMU_WriteRegToEE(&V_WriteData[1],V_WriteData[0]);///У�������EE
	AppEMU_WriteOneReg_MeterIC(&V_WriteData[1],V_WriteData[0]);
//	LibPub_MemCopyBytes(V_WriteData, GA_EmuRegData, 4);
	
	V_WriteData[0]=0x60;  ///��λ����1
	V_WriteData[1]=0;
	V_WriteData[2]=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+45];
	V_WriteData[3]=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+44];
	AppEMU_WriteRegToEE(&V_WriteData[1],V_WriteData[0]);	
	AppEMU_WriteOneReg_MeterIC(&V_WriteData[1],V_WriteData[0]);
//	LibPub_MemCopyBytes(V_WriteData, &GA_EmuRegData[4], 4);
	
	V_WriteData[0]=0x36;  ///�𶯹�������
	V_WriteData[1]=0;
	V_WriteData[2]=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+21];
	V_WriteData[3]=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+20];
	AppEMU_WriteRegToEE(&V_WriteData[1],V_WriteData[0]);
	AppEMU_WriteOneReg_MeterIC(&V_WriteData[1],V_WriteData[0]);	
//	LibPub_MemCopyBytes(V_WriteData, &GA_EmuRegData[8], 4);
	
	V_WriteData[0]=0x1E;  ///HFCONST
	V_WriteData[1]=0;
	V_WriteData[2]=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+5];
	V_WriteData[3]=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+4];
	AppEMU_WriteRegToEE(&V_WriteData[1],V_WriteData[0]);
	AppEMU_WriteOneReg_MeterIC(&V_WriteData[1],V_WriteData[0]);

//	LibPub_MemCopyBytes(V_WriteData, &GA_EmuRegData[12], 4);
	
//	Hal_WriteEEPROM(CAddr_EMU_CALPARA_Note, GA_EmuRegData, TRIPEMU_CALPARA_Type_LEN);
//	Hal_WriteEEPROM(CAddr_EMU_CALPARA_BAK_Note, GA_EmuRegData, TRIPEMU_CALPARA_Type_LEN);///����д����EE
	
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
	uchar8   V_ucResult = _SUCCESS,i,j;
	uchar8   V_ucRegAddress;		// �Ĵ�����ַ
	uchar8 	 V_WriteData[3][4];
	
	do{
		
		if(( 0x02 <Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0] )	
			&&(0xFF !=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0]))///* ��֧��DI0==00\01\02\FF *///
		{
			V_ucResult = _FAILED; 
			break;  // ����do-whileѭ��
		} 
		
		///* ׼������ *///
		//---------------------------------------------------------------------------
		LibPub_MemExchangeBytes(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W], &V_WriteData[0][0], 4);
		if(0xFF ==Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0])
		{
			LibPub_MemExchangeBytes(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+4],&V_WriteData[1][0], 4);
			LibPub_MemExchangeBytes(&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_D0_W+8],&V_WriteData[2][0], 4);
		}
		//---------------------------------------------------------------------------
		///* DI1:0x00 1.0L 100%Ib �й���������У�� ��Ӧ�Ĵ��� 0c *///
		///* DI1:0x09 0.5L 100%Ib ��λУ��  ��Ӧ�Ĵ��� 18*///
		///* DI1:0x0D 1.0L 5%Ib ����offsetУ��  ��Ӧ�Ĵ��� 78*///
		for( i=0;i<(sizeof(EMU_COMM_TRIPEMUC_TAB)/sizeof(EMU_COMM_TRIPCAL_TAB_Type));i++)
		{
			if(EMU_COMM_TRIPEMUC_TAB[i].ucCommDI1==(Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+1]))
			{
				if(0xFF !=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0])
				{
					V_ucRegAddress=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0];
					V_ucRegAddress=EMU_COMM_TRIPEMUC_TAB[i].ucEmuAddr[V_ucRegAddress];
					AppEMU_WriteRegToEE(&V_WriteData[0][1],V_ucRegAddress);	
					AppEMU_WriteOneReg_MeterIC(&V_WriteData[0][1],V_ucRegAddress);
					V_WriteData[0][0]=V_ucRegAddress;
				}
				else
				{
					for(j=0;j<3;j++)
					{
						V_ucRegAddress=EMU_COMM_TRIPEMUC_TAB[i].ucEmuAddr[j];
						AppEMU_WriteRegToEE(&V_WriteData[j][1],V_ucRegAddress);						
						AppEMU_WriteOneReg_MeterIC(&V_WriteData[j][1],V_ucRegAddress);
						V_WriteData[i][0]=V_ucRegAddress;
					}
				}
				break;
			}
		
		}
			
//			case 0x11:	///* ������ЧֵУ����Уһ��ϵ�� *///
//			{ 
//				// ����һ��Ǳ����ֵ
//				ApiEMU_SetStartVal(); 
//				
//				// Уһ��ϵ��
//				ApiEMU_SetUIPKms();
//				
//			}break;
			
//			default:break;
//		} 
	}while(0);
	
	//---------------------------------------------------------------------------
	return( V_ucResult );
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
	
	AppEMU_ClearEnergyData_MeterIC();
	
	V_ucTemp = v_ucChID;
}

/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ���Ĵ���
 *
 *  @param    v_ucChID : �Ĵ�����ַ
 *
 *  @return   �ɹ���_SUCCESS��ʧ�ܣ�_FAILED
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
uchar8 AppEMU_TripReadEmuReg( uchar8 v_ucChID )
{
	uchar8   V_ucResult = _SUCCESS,i,j;
	uchar8   V_ucRegAddress;		// �Ĵ�����ַ
	uchar8   V_ReadData[4];
	
	if( 0x01 ==Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+2] )	///0x8001XXXX
	{
		for( i=0;i<(sizeof(EMU_COMM_TRIPEMUC_TAB)/sizeof(EMU_COMM_TRIPCAL_TAB_Type));i++)
		{
			if(EMU_COMM_TRIPEMUC_TAB[i].ucCommDI1==(Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+1]))///˵����У�����
			{
				if(0xFF !=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0])
				{
					V_ucRegAddress=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0];
					V_ucRegAddress=EMU_COMM_TRIPEMUC_TAB[i].ucEmuAddr[V_ucRegAddress];
					AppEMU_ReadOneReg_MeterIC(V_ucRegAddress, &V_ReadData[1],C_EMUPara);
					V_ReadData[0]=0;
					LibPub_MemExchangeBytes(V_ReadData,&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+4], 4);
				}
				else
				{
					for(j=0;j<3;j++)
					{
						V_ucRegAddress=EMU_COMM_TRIPEMUC_TAB[i].ucEmuAddr[j];
						AppEMU_ReadOneReg_MeterIC(V_ucRegAddress, &V_ReadData[1],C_EMUPara);
						V_ReadData[0]=0;
						LibPub_MemExchangeBytes(V_ReadData,&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+4*(j+1)], 4);
					}
				}
				return( V_ucResult );
			}
		}
		for( i=0;i<(sizeof(EMU_READ_TRIPEMUC_TAB)/sizeof(EMU_COMM_TRIPCAL_TAB_Type));i++)///˵��������������
		{
			if(EMU_READ_TRIPEMUC_TAB[i].ucCommDI1==(Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+1]))///˵������Чֵ����
			{
				if(0xFF !=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0])
				{
					V_ucRegAddress=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0];
					V_ucRegAddress=EMU_READ_TRIPEMUC_TAB[i].ucEmuAddr[V_ucRegAddress];
					AppEMU_ReadOneReg_MeterIC(V_ucRegAddress, &V_ReadData[1],C_MeterPara);
					V_ReadData[0]=0;
					LibPub_MemExchangeBytes(V_ReadData,&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+4], 4);
				}
				else
				{
					for(j=0;j<4;j++)////�������������࣬������Ҫ��4���Ĵ���
					{
						V_ucRegAddress=EMU_READ_TRIPEMUC_TAB[i].ucEmuAddr[j];
						AppEMU_ReadOneReg_MeterIC(V_ucRegAddress, &V_ReadData[1],C_MeterPara);
						V_ReadData[0]=0;
						LibPub_MemExchangeBytes(V_ReadData,&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+4*(j+1)], 4);
					}
				}
				return( V_ucResult );
			}
		}
		V_ucResult = _FAILED;
		return( V_ucResult );  ///���Ǳ��������ݣ��ش�
	}
	
	if( 0x03 ==Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+2] )	///0x8003XXXX //��ָ����ַ��������
	{
		if(0x00!=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+1] )
		{
			V_ucResult = _FAILED; 
			return( V_ucResult );
		}
		V_ucRegAddress=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0];
		AppEMU_ReadOneReg_MeterIC(V_ucRegAddress, &V_ReadData[1],C_MeterPara);
		V_ReadData[0]=0;
		LibPub_MemExchangeBytes(V_ReadData,&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+4], 4);
		return( V_ucResult );
	}
	if( 0x04 ==Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+2] )	///0x8003XXXX //��ָ����ַУ�����
	{
		if(0x00!=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0+1] )
		{
			V_ucResult = _FAILED; 
			return( V_ucResult );
		}
		V_ucRegAddress=Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_DI0];
		AppEMU_ReadOneReg_MeterIC(V_ucRegAddress, &V_ReadData[1],C_EMUPara);
		V_ReadData[0]=0;
		LibPub_MemExchangeBytes(V_ReadData,&Gstr_UartComm[v_ucChID].ucaCommTXBuff[API_DLT645_1STDATA+4], 4);
		return( V_ucResult );
	}
	
	V_ucResult = _FAILED; 
	return( V_ucResult );///�����ǻش�
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ����˲ʱ��
 *
 *  @param    v_ucChID : �Ĵ�����ַ
 *
 *  @return   �ɹ���_SUCCESS��ʧ�ܣ�_FAILED
 *
 *  @note     xx
 *
 */
/*------------------------------------------------------------------------------------------------------*/
ushort16 C_ucCurrentTab[]={ 10,15,25,50,100,150,200,300 };

uchar8 ApiEMU_UpdateUIP(void)
{
	uchar8 i;
	uchar8   V_ucaRegData[C_ucUIPREG_TAB_Index][4];
	ulong32  V_ulaRegData[C_ucUIPREG_TAB_Index];
	ulong32  V_ulTemp[4],V_ulKms1,V_ulKms2;
	uchar8   V_ucaReverseData[3];
	uchar8   V_ucaReverseFlag_A,V_ucaReverseFlag_B,V_ucaReverseFlag_C;
	V_ucaReverseFlag_A=0;
	V_ucaReverseFlag_B=0;
	V_ucaReverseFlag_C=0;
	
	
	Str_TRIPUIPKmsPara.ulaKmsuip=3000/C_ucCurrentTab[GStr_FunConfigPara.ucFunCurrentVal];////����ϵ���̶�Ϊ30/Ib,�˴�Ϊ300/Ib
//	AppEMU_TripCheckKmsParaCRC();///У��һ�µ���ϵ��
	
	for( i=0;i<C_ucUIPREG_TAB_Index;i++ )
	{
		AppEMU_ReadOneReg_MeterIC(Str_RmsRegADDr[i], &V_ucaRegData[i][1],C_MeterPara);
		V_ucaRegData[i][0]=0;///��λΪ0
		V_ulaRegData[i]=LibPub_Buffer4ToUlong32( &V_ucaRegData[i][0] );
	}
	
	///��ʼ����˲ʱ��
	///��ѹ  ʵ��ֵΪ�Ĵ���ֵVrms/2^13
	GStr_UIPGroup.ulVoltage[0] = 10.0*V_ulaRegData[4] /8192;        ///A���ѹ
	GStr_UIPGroup.ulVoltage[1] = 10.0*V_ulaRegData[5] /8192;        ///B���ѹ
	GStr_UIPGroup.ulVoltage[2] = 10.0*V_ulaRegData[6] /8192;        ///C���ѹ
	GStr_UIPGroup.ulVoltage[3] = 10.0*V_ulaRegData[7] /4096;        ///�����ѹ
	
	for(i=0;i<4;i++)
	{
		////��ѹ����  ����ѹС��5Vʱ������
		if( GStr_UIPGroup.ulVoltage[i] < C_ClearVoltage )
		{
			GStr_UIPGroup.ulVoltage[i]=0;
		}
		V_ulTemp[i]=GStr_UIPGroup.ulVoltage[i]*10;	
	}
	///A��
	LibPub_HEXtoBCDBytes(V_ulTemp[0],&GStr_UIPDisplay.ucVoltageA[0],4);///ת��ΪBCD������ʾ ��λС��
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulVoltage[0],&GStr_UIPDisplay.ucCOMMVoltageA[0],4);///ת��ΪBCD����ͨ��
	///B��
	LibPub_HEXtoBCDBytes(V_ulTemp[1],&GStr_UIPDisplay.ucVoltageB[0],4);///ת��ΪBCD������ʾ ��λС��
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulVoltage[1],&GStr_UIPDisplay.ucCOMMVoltageB[0],4);///ת��ΪBCD����ͨ��
	///C��
	LibPub_HEXtoBCDBytes(V_ulTemp[2],&GStr_UIPDisplay.ucVoltageC[0],4);///ת��ΪBCD������ʾ ��λС��
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulVoltage[2],&GStr_UIPDisplay.ucCOMMVoltageC[0],4);///ת��ΪBCD����ͨ��
	///����
	LibPub_HEXtoBCDBytes(V_ulTemp[3],&GStr_UIPDisplay.ucVoltage[0],4);///ת��ΪBCD������ʾ ��λС��
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulVoltage[3],&GStr_UIPDisplay.ucCOMMVoltage[0],4);///ת��ΪBCD����ͨ��
	
	///����   ʵ��ֵΪ�Ĵ���ֵ(Vrms/2^13)/N
	GStr_UIPGroup.ulCurrent[0] = 1000.0*V_ulaRegData[8] /8192*10/Str_TRIPUIPKmsPara.ulaKmsuip;        ///A�����
	GStr_UIPGroup.ulCurrent[1] = 1000.0*V_ulaRegData[9] /8192*10/Str_TRIPUIPKmsPara.ulaKmsuip;        ///B�����
	GStr_UIPGroup.ulCurrent[2] = 1000.0*V_ulaRegData[10] /8192*10/Str_TRIPUIPKmsPara.ulaKmsuip;        ///C�����
	GStr_UIPGroup.ulCurrent[3] = 1000.0*V_ulaRegData[11] /4096*10/Str_TRIPUIPKmsPara.ulaKmsuip;        ///�������
	
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulCurrent[0],&GStr_UIPDisplay.ucCurrentA[0],4);///ת��ΪBCD������ʾ
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulCurrent[1],&GStr_UIPDisplay.ucCurrentB[0],4);///ת��ΪBCD������ʾ
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulCurrent[2],&GStr_UIPDisplay.ucCurrentC[0],4);///ת��ΪBCD������ʾ
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulCurrent[3],&GStr_UIPDisplay.ucCurrent[0],4);///ת��ΪBCD������ʾ
	
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucCurrentA[0],&GStr_UIPDisplay.ucCOMMCurrentA[0],4);///����ͨ��
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucCurrentB[0],&GStr_UIPDisplay.ucCOMMCurrentB[0],4);///����ͨ��
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucCurrentC[0],&GStr_UIPDisplay.ucCOMMCurrentC[0],4);///����ͨ��
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucCurrent[0],&GStr_UIPDisplay.ucCOMMCurrent[0],4);///����ͨ��
	
	///����
	///�Ĵ���ֵΪX����X>2^23  XX=X-2^24,����XX=X   ����ʵ��ֵΪXXX=XX*K    ����ʵ��ֵΪXXX=XX*2*K
	///K=2.592*10^10/(HFCONST*EC*2^23)   ��λΪW
	V_ulKms1=(Str_TRIPEmuCalPara.ulaCalPara[3]&0x00FFFFFF)*GStr_FunConfigPara.ucFunMeterConst*83886.08;
	///							   HFCONST					* ���峣���İٷ�֮һ*2^23	
	V_ulKms2=2592000;
	for(i=0;i<4;i++)
	{
		if(V_ulaRegData[i]>8388608)
		{
			V_ulTemp[i]=16777216-V_ulaRegData[i];   ////����
		}
		else
		{
			V_ulTemp[i]=V_ulaRegData[i];
		}
		if(i!=3)
		{
			GStr_UIPGroup.ulPower[i]=10.0*V_ulTemp[i]*V_ulKms2/V_ulKms1;///���๦��///��λΪW�л�ΪkW����λС��
		}
		else
		{
			GStr_UIPGroup.ulPower[i]=10.0*V_ulTemp[i]*V_ulKms2/V_ulKms1*2;///���๦��
		}	
	}
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulPower[0],&GStr_UIPDisplay.ucPowerA[0],4);///ת��ΪBCD������ʾ
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulPower[1],&GStr_UIPDisplay.ucPowerB[0],4);///ת��ΪBCD������ʾ
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulPower[2],&GStr_UIPDisplay.ucPowerC[0],4);///ת��ΪBCD������ʾ
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulPower[3],&GStr_UIPDisplay.ucPower[0],4);///ת��ΪBCD������ʾ
	
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucPowerA[0],&GStr_UIPDisplay.ucCOMMPowerA[0],4);///����ͨ��
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucPowerB[0],&GStr_UIPDisplay.ucCOMMPowerB[0],4);///����ͨ��
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucPowerC[0],&GStr_UIPDisplay.ucCOMMPowerC[0],4);///����ͨ��
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucPower[0],&GStr_UIPDisplay.ucCOMMPower[0],4);///����ͨ��
	
	///��������
	///�Ĵ���ֵΪX����X>2^23  XX=X-2^24,����XX=X   ʵ�ʹ�������pf=XX/2^23
	for(i=0;i<4;i++)
	{
		if(V_ulaRegData[12+i]>8388608)
		{
			V_ulTemp[i]=16777216-V_ulaRegData[12+i];   ////��������
		}
		else
		{
			V_ulTemp[i]=V_ulaRegData[12+i];
		}
		GStr_UIPGroup.ulFactory[i]=100.0*V_ulTemp[i]/8388608*10;
	}
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulFactory[0],&GStr_UIPDisplay.ucFactoryA[0],4);///ת��ΪBCD����ͨ�ź���ʾ
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulFactory[1],&GStr_UIPDisplay.ucFactoryB[0],4);///ת��ΪBCD����ͨ�ź���ʾ
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulFactory[2],&GStr_UIPDisplay.ucFactoryC[0],4);///ת��ΪBCD����ͨ�ź���ʾ
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulFactory[3],&GStr_UIPDisplay.ucFactory[0],4);///ת��ΪBCD����ͨ�ź���ʾ
	
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucFactoryA[0],&GStr_UIPDisplay.ucCOMMFactoryA[0],4);///����ͨ��
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucFactoryB[0],&GStr_UIPDisplay.ucCOMMFactoryB[0],4);///����ͨ��
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucFactoryC[0],&GStr_UIPDisplay.ucCOMMFactoryC[0],4);///����ͨ��
	LibPub_MemCopyBytes(&GStr_UIPDisplay.ucFactory[0],&GStr_UIPDisplay.ucCOMMFactory[0],4);///����ͨ��
	
	///Ƶ��
	///�Ĵ���ֵΪX   freq=X/2^13
	V_ulTemp[0]=V_ulaRegData[16];
	GStr_UIPGroup.ulFrequency=100.0*V_ulTemp[0]/8192;
	LibPub_HEXtoBCDBytes(GStr_UIPGroup.ulFrequency,&GStr_UIPDisplay.ucFrequency[0],4);///ת��ΪBCD����ͨ�ź���ʾ
	
	AppEMU_ReadOneReg_MeterIC(C_Psign, &V_ucaReverseData[0],C_MeterPara);//�����ʷ���Ĵ���
	if(V_ucaReverseData[2]&0x01)
	{
		V_ucaReverseFlag_A=1;
		GStr_UIPDisplay.ucCOMMFactoryA[2] |=0x80;///A�෴�򣬵�ѹ�������ʹ����������λ��1
		GStr_UIPDisplay.ucCOMMPowerA[1] |=0x80;///A�෴�򣬵�ѹ�������ʹ����������λ��1
		GStr_UIPDisplay.ucCOMMCurrentA[1]|=0x80;///A�෴�򣬵�ѹ�������ʹ����������λ��1
	}
	if(V_ucaReverseData[2]&0x02)
	{
		V_ucaReverseFlag_B=1;
		GStr_UIPDisplay.ucCOMMFactoryB[2] |=0x80;///B�෴�򣬵�ѹ�������ʹ����������λ��1
		GStr_UIPDisplay.ucCOMMPowerB[1] |=0x80;///B�෴�򣬵�ѹ�������ʹ����������λ��1
		GStr_UIPDisplay.ucCOMMCurrentB[1]|=0x80;///B�෴�򣬵�ѹ�������ʹ����������λ��1
	}
	if(V_ucaReverseData[2]&0x04)
	{
		V_ucaReverseFlag_C=1;
		GStr_UIPDisplay.ucCOMMFactoryC[2] |=0x80;///C�෴�򣬵�ѹ�������ʹ����������λ��1
		GStr_UIPDisplay.ucCOMMPowerC[1] |=0x80;///C�෴�򣬵�ѹ�������ʹ����������λ��1
		GStr_UIPDisplay.ucCOMMCurrentC[1]|=0x80;///C�෴�򣬵�ѹ�������ʹ����������λ��1
	}
	if(V_ucaReverseData[2]&0x08)
	{
		GStr_UIPDisplay.ucCOMMFactory[2] |=0x80;///���෴�򣬵�ѹ�������ʹ����������λ��1
		GStr_UIPDisplay.ucCOMMPower[1] |=0x80;///���෴�򣬵�ѹ�������ʹ����������λ��1
		GStr_UIPDisplay.ucCOMMCurrent[1]|=0x80;///���෴�򣬵�ѹ�������ʹ����������λ��1
	}
	
	// 6. �ж��Ƿ�Ǳ��
	//---------------------------------------------------------------------------
	AppEMU_ReadOneReg_MeterIC(C_EmuState, &V_ucaReverseData[0],C_MeterPara);//����־�Ĵ���
	// �����͹����ڳ��ڲ����㣬��������
	if(V_ucaReverseData[1]&0x02)///A��Ǳ��  
	{
		if( (GStr_Flag.ucMeterMode & F_FACTORY_MODE)!= F_FACTORY_MODE )	
		{
			if(GStr_UIPGroup.ulCurrent[0]<=(2*(100*C_ucCurrentTab[GStr_FunConfigPara.ucFunCurrentVal])/1000))
			{
				LibPub_MemSetBytes( &GStr_UIPDisplay.ucCurrentA[0], 0x00, 4 );
				LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMCurrentA[0],0x00,4);
			}
			LibPub_MemSetBytes( &GStr_UIPDisplay.ucPowerA[0], 0x00, 4 );
			LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMPowerA[0],0x00,4);
		}
		LibPub_MemSetBytes( &GStr_UIPDisplay.ucFactoryA[0], 0x00, 4 );
		LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMFactoryA[0], 0x00, 4 );
		GStr_UIPDisplay.ucFactoryA[2] = 0x10;
		GStr_UIPDisplay.ucCOMMFactoryA[2] = 0x10;
		V_ucaReverseFlag_A=0;///��A�෴���־
	}
	if(V_ucaReverseData[1]&0x04)///B��Ǳ��  
	{
		if( (GStr_Flag.ucMeterMode & F_FACTORY_MODE)!= F_FACTORY_MODE )	
		{
			if(GStr_UIPGroup.ulCurrent[1]<=(2*(100*C_ucCurrentTab[GStr_FunConfigPara.ucFunCurrentVal])/1000))
			{
				LibPub_MemSetBytes( &GStr_UIPDisplay.ucCurrentB[0], 0x00, 4 );
				LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMCurrentB[0],0x00,4);
			}
			LibPub_MemSetBytes( &GStr_UIPDisplay.ucPowerB[0], 0x00, 4 );
			LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMPowerB[0],0x00,4);
		}
		LibPub_MemSetBytes( &GStr_UIPDisplay.ucFactoryB[0], 0x00, 4 );
		LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMFactoryB[0], 0x00, 4 );
		GStr_UIPDisplay.ucFactoryB[2] = 0x10;
		GStr_UIPDisplay.ucCOMMFactoryB[2] = 0x10;
		V_ucaReverseFlag_B=0;///��B�෴���־
	}
	if(V_ucaReverseData[1]&0x08)///C��Ǳ��  
	{
		if( (GStr_Flag.ucMeterMode & F_FACTORY_MODE)!= F_FACTORY_MODE )	
		{
			if(GStr_UIPGroup.ulCurrent[2]<=(2*(100*C_ucCurrentTab[GStr_FunConfigPara.ucFunCurrentVal])/1000))
			{
				LibPub_MemSetBytes( &GStr_UIPDisplay.ucCurrentC[0], 0x00, 4 );
				LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMCurrentC[0],0x00,4);
			}
			LibPub_MemSetBytes( &GStr_UIPDisplay.ucPowerC[0], 0x00, 4 );
			LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMPowerC[0],0x00,4);
		}
		LibPub_MemSetBytes( &GStr_UIPDisplay.ucFactoryC[0], 0x00, 4 );
		LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMFactoryC[0], 0x00, 4 );
		GStr_UIPDisplay.ucFactoryC[2] = 0x10;
		GStr_UIPDisplay.ucCOMMFactoryC[2] = 0x10;
		V_ucaReverseFlag_C=0;///��C�෴���־
	}
	if((V_ucaReverseData[1]&0x02)&&(V_ucaReverseData[1]&0x04)&&(V_ucaReverseData[1]&0x08))///A\B\C�඼Ǳ��  
	{
		if( (GStr_Flag.ucMeterMode & F_FACTORY_MODE)!= F_FACTORY_MODE )	
		{
			if(GStr_UIPGroup.ulCurrent[3]<=(6*(100*C_ucCurrentTab[GStr_FunConfigPara.ucFunCurrentVal])/1000))
			{
				LibPub_MemSetBytes( &GStr_UIPDisplay.ucCurrent[0], 0x00, 4 );
				LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMCurrent[0],0x00,4);
			}
			LibPub_MemSetBytes( &GStr_UIPDisplay.ucPower[0], 0x00, 4 );
			LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMPower[0],0x00,4);
		}
		LibPub_MemSetBytes( &GStr_UIPDisplay.ucFactory[0], 0x00, 4 );
		LibPub_MemSetBytes( &GStr_UIPDisplay.ucCOMMFactory[0], 0x00, 4 );
		GStr_UIPDisplay.ucFactory[2] = 0x10;
		GStr_UIPDisplay.ucCOMMFactory[2] = 0x10;
	}
		
	if((V_ucaReverseFlag_A)||(V_ucaReverseFlag_B)||(V_ucaReverseFlag_C))
	{
		GStr_Flag.ucRunState1 |=F_RUN_POWER_REVERSE;  //�ù��ʷ����־
	}
	else
	{
		GStr_Flag.ucRunState1 &=~F_RUN_POWER_REVERSE; //�幦�ʷ����־
	}
//---------------------------------------------------------------------------
	
	return(_SUCCESS);
}
/*------------------------------------------------------------------------------------------------------*/
/**
 *  @brief    ��ȡ���ʷ���
 *
 *  @return   _FALSE������  _TRUE������
 *
 *  @note     xx///�ú���ֻ�����ж����������壬�ú���ķ���Ϊ׼
 *
 */
/*------------------------------------------------------------------------------------------------------*/
uchar8  ApiEMU_GetDirP(void)
{
	uchar8 V_ucaRegData[3];
	
	AppEMU_ReadOneReg_MeterIC(C_Psign, &V_ucaRegData[0],C_MeterPara);//�����ʷ���Ĵ���
	
	if(V_ucaRegData[2]&0x08)/// ���෴��
	{
		return _FALSE;
	}
	return _TRUE;
}

#endif
