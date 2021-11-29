
///*****************************************************************************************///
///*Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     IO.c
///*Version:       V1
///*Date:          2014-3-12
///*Description:   ��������
///*Function List: 
///*****************************************************************************************///
///*History1:      ��1���޸�
///*����1. Date:
///*   	   Author:
///*       Modification:
		///***********************************************///
///*����2. Date:
///*   	   Author:
///*       Modification:
		///*********************************************************************************///
///*History2:      ��2���޸�
///*����1. Date:
///*   	   Author:
///*       Modification:
		///***********************************************///
///*����2. Date:
///*   	   Author:
///*       Modification:
///*****************************************************************************************///

#include "IO.h"
#include "CardDrive.h"
#include "EEPROMDrive.h"
#include "FRAMDrive.h"
//#include "EsamDrive.h"
#include "FlashDrive.h"
#include "LCDDrive.h"
//#include "MeterICDrive.h"
#include "RTCDrive.h"
#include "uart.h"
#include "Public.h"

//static ulong32 SV_ulTemp_GPIO;	///*�ñ����������мĴ����Ķ�->�޸�->д*///



typedef struct
{
	ulong32 portregister;		///*port�ڼĴ���*///
	ulong32 inputmode;			///*����ģʽ*///
	ulong32 outputmode;			///*���ģʽ*///
	ulong32 outputtype;			///*�������:��©������*///
	ulong32 outvalue;			///*���ֵ:��/��*///
}Str_NCIO_Type;

///********macro pcb���********///
//#define	C_Pcb1512			0x01			///*0.2S��������ţ��޷ѿع���*///
//#define	C_Pcb1595       	0x02            ///*���ܱ�������ţ��зѿع��ܣ����غ�Զ�̶���*///
///*����ı�����˰��������տ���,����ͳһ����:����Ϊ��©�����,���ر�������*///
//#if	( C_PcbVersion == C_Pcb1512 )		/*0.2S��*///
//const Str_NCIO_Type Table_NCIO[]=
//{/*�Ĵ�����ַ,����ģʽ,  ���ģʽ,   �������, ��������,  ����͵�ƽ
//	{GPIOA_BASE,BIT7INMODE, BIT7OUTMODE, BIT7OUTPP, BIT7NOPUPD, BIT7RESET},		/*GPIOA.7*///
//	{GPIOB_BASE,BIT8INMODE, BIT8OUTMODE, BIT8OUTPP, BIT8NOPUPD, BIT8RESET},		/*GPIOB.8*///
//	{GPIOB_BASE,BIT9INMODE, BIT9OUTMODE, BIT9OUTPP, BIT9NOPUPD, BIT9RESET},		/*GPIOB.9*///
//	{GPIOB_BASE,BIT10INMODE,BIT10OUTMODE,BIT10OUTPP,BIT10NOPUPD,BIT10RESET},	/*GPIOB.10*///
//	{GPIOC_BASE,BIT0INMODE, BIT0OUTMODE, BIT0OUTPP, BIT0NOPUPD, BIT0RESET},		/*GPIOC.0*///
//	{GPIOC_BASE,BIT1INMODE, BIT1OUTMODE, BIT1OUTPP, BIT1NOPUPD, BIT1RESET},		/*GPIOC.1*///
//	{GPIOC_BASE,BIT12INMODE,BIT12OUTMODE,BIT12OUTPP,BIT12NOPUPD,BIT12RESET},	/*GPIOC.12*///
//	{GPIOC_BASE,BIT13INMODE,BIT13OUTMODE,BIT13OUTPP,BIT13NOPUPD,BIT13RESET},	/*GPIOC.13*///
//	{GPIOC_BASE,BIT14INMODE,BIT14OUTMODE,BIT14OUTPP,BIT14NOPUPD,BIT14RESET},	/*GPIOC.14*///
//	{GPIOC_BASE,BIT15INMODE,BIT15OUTMODE,BIT15OUTPP,BIT15NOPUPD,BIT15RESET},	/*GPIOC.15*///
//	{GPIOD_BASE,BIT2INMODE, BIT2OUTMODE, BIT2OUTPP, BIT2NOPUPD, BIT2RESET}		/*GPIOD.2*///
//};
//#else
const Str_NCIO_Type Table_NCIO[]=
{
//	#if	( C_Meter_Type != C_L_SmartMeter )
//	{GPIOF_BASE,BIT3INMODE, BIT3OUTMODE, BIT3OUTOD,BIT3SET},		///*GPIOF.3*///
//	{GPIOF_BASE,BIT4INMODE, BIT4OUTMODE, BIT4OUTOD,BIT4SET},		///*GPIOF.4*///
//	{GPIOF_BASE,BIT5INMODE, BIT5OUTMODE, BIT5OUTOD,BIT5SET},		///*GPIOF.5*///
//	{GPIOF_BASE,BIT6INMODE, BIT6OUTMODE, BIT6OUTOD,BIT6SET},		///*GPIOF.6*///
//	{GPIOF_BASE,BIT7INMODE, BIT7OUTMODE, BIT7OUTOD,BIT7SET},		///*GPIOF.7*///
//	{GPIOF_BASE,BIT9INMODE, BIT9OUTMODE, BIT9OUTOD,BIT9SET},		///*GPIOF.9*///
//	{GPIOA_BASE,BIT0INMODE, BIT0OUTMODE, BIT0OUTOD,BIT0SET},		///*GPIOa.0*///
//	{GPIOC_BASE,BIT1INMODE, BIT1OUTMODE, BIT1OUTOD,BIT1SET},		///*GPIOC.1*///
//	{GPIOC_BASE,BIT2INMODE, BIT2OUTMODE, BIT2OUTOD,BIT2SET},		///*GPIOC.2*///
//	#endif
//	{GPIOA_BASE,BIT15INMODE, BIT15OUTMODE, BIT15OUTOD,BIT15SET},		///*GPIOa.15*///
//	{GPIOB_BASE,BIT1INMODE, BIT1OUTMODE, BIT1OUTOD,BIT1SET},		///*GPIOB.1*///
//	{GPIOB_BASE,BIT2INMODE, BIT2OUTMODE, BIT2OUTOD,BIT2SET},		///*GPIOB.2*///
	{GPIOE_BASE,BIT2INMODE, BIT2OUTMODE, BIT2OUTOD,BIT2SET},		///*GPIOE.2*///
	{GPIOE_BASE,BIT6INMODE, BIT6OUTMODE, BIT6OUTOD,BIT6SET},		///*GPIOE.6*///
	{GPIOE_BASE,BIT7INMODE, BIT7OUTMODE, BIT7OUTOD,BIT7SET},		///*GPIOE.7*///
	{GPIOG_BASE,BIT4INMODE, BIT4OUTMODE, BIT4OUTOD,BIT4SET},		///*GPIOG.4*///
	{GPIOG_BASE,BIT7INMODE, BIT7OUTMODE, BIT7OUTOD,BIT7SET},		///*GPIOG.7*///
	{GPIOG_BASE,BIT3INMODE, BIT3OUTMODE, BIT3OUTOD,BIT3SET},		///*GPIOG.3*///
	{GPIOD_BASE,BIT2INMODE, BIT2OUTMODE, BIT2OUTOD,BIT2SET},		///*GPIOD.2*///
	{GPIOD_BASE,BIT3INMODE, BIT3OUTMODE, BIT3OUTOD,BIT3SET},		///*GPIOD.3*///
	{GPIOD_BASE,BIT4INMODE, BIT4OUTMODE, BIT4OUTOD,BIT4SET},		///*GPIOD.4*///
	{GPIOD_BASE,BIT5INMODE, BIT5OUTMODE, BIT5OUTOD,BIT5SET},		///*GPIOD.5*///
	{GPIOD_BASE,BIT6INMODE, BIT6OUTMODE, BIT6OUTOD,BIT6SET},		///*GPIOD.6*///
	{GPIOD_BASE,BIT7INMODE, BIT7OUTMODE, BIT7OUTOD,BIT7SET},		///*GPIOD.7*///
	{GPIOD_BASE,BIT8INMODE, BIT8OUTMODE, BIT8OUTOD,BIT8SET},		///*GPIOD.8*///
	{GPIOF_BASE,BIT1INMODE, BIT1OUTMODE, BIT1OUTOD,BIT1SET},		///*GPIOF.1*///
	{GPIOF_BASE,BIT2INMODE, BIT2OUTMODE, BIT2OUTOD,BIT2SET},		///*GPIOF.2*///
	{GPIOC_BASE,BIT15INMODE, BIT15OUTMODE, BIT15OUTOD,BIT15SET},		///*GPIOC.15*///
//	{GPIOE_BASE,BIT9INMODE, BIT9OUTMODE, BIT9OUTOD,BIT9SET},		///*GPIOE.9*///
};
//#endif

#define C_Table_NCIO_Len  (sizeof(Table_NCIO)/sizeof(Str_NCIO_Type))
///**************************************************************************************///
///*����ԭ�ͣ�void DF_InternalRelayHold(void)                                           *///
///*�����������ײ����ü̵������ֺ���                  		                            *///
///*�����������                                                                        *///
///*�����������                                                                        *///
///*���ز�������                                                                        *///
///*����λ�ã�5ms����ӿں���                                                           *///
///*����˵����1��5ms�ӿں�����SV_InternalRelayActTime��ʱ��ʹ�ܵ�����½��е���ʱ��0ʱ��*///
///*          ���øú�������������ʱ��δʹ�ܣ�ֱ�����㣩��    	                    *///
///**************************************************************************************///
void DF_InternalRelayHold(void)
{
	Hold_InternalRelay();
}

/////**************************************************************************************///
/////*����ԭ�ͣ�void DF_ExternalRelayHold(void)                                           *///
/////*�����������ײ����ü̵���������������                                                *///
/////*�����������                                                                        *///
/////*�����������                                                                        *///
/////*���ز�������                                                                        *///
/////*����λ�ã�5ms����ӿں���                                                           *///
/////*����˵����1��5ms�ӿں�����SV_ExternalRelayActTime��ʱ��ʹ�ܵ�����½��е���ʱ��0ʱ��*///
/////*          ���øú�������������ʱ��δʹ�ܣ�ֱ�����㣩��							*///
/////**************************************************************************************///
//void DF_ExternalRelayHold(void)
//{
//	
//}

///**************************************************************************************///
///*����ԭ�ͣ�uchar8 DF_RelayControl(uchar8 C_Act)										*///
///*�����������ײ�̵�����������                                                        *///
///*���������C_On����ʾ�̵����պϣ�C_Off����ʾ�̵����Ͽ���                             *///
///*�����������                                                                        *///
///*���ز�����C_Ok����ȷִ�У�C_Error����ڴ���                                         *///
///*����λ�ã��ú�����InF_RelayAct�ӿں�������                                          *///
///*��    ע��1�����ø���������ʱ��ֻ��Ҫ��ȷ�Ǽ̵����պϻ��ǶϿ�                       *///
///*          2���ڸ����������У��������û������ã���Ϊ���ø��ɿ�������I/O���ߺ�        *///
///*             ���ø��ɿ���I/O���������Ƕ����ģ��໥��Ӱ�죩�������ж�����            *///
///**************************************************************************************///
uchar8 DF_RelayControl(uchar8 C_Act)
{
	uchar8 V_ucTemp = C_Error;	///*����ֵ��Ϊ������ڲ�������ʱ�ŷ��ش���ֻҪ��ڲ�����ȷ�ͷ�����ȷ*///
	
	switch( C_Act )
	{
		///********************************************************///
		case C_On:									///*�̵����պ�*///
		{
			SwitchOn_InternalRelay();
			SwitchOn_ExternalRelay();
			V_ucTemp = C_OK;
			break;
		}
		///********************************************************///
		case C_Off:									///*�̵����Ͽ�*///
		{
			SwitchOff_InternalRelay();
			SwitchOff_ExternalRelay();
			V_ucTemp = C_OK;
			break;
		}
		///********************************************************///
		default:
			;
			break;
		///********************************************************///
	}
	
	return V_ucTemp;
}

///**************************************************************************************///
///*����ԭ�ͣ�uchar8 DF_GetKsyUpStatus_LowPower(void)*///
///*�����������͹����¶�ȡ�Ϸ�������״̬*///
///*�����������*///
///*�����������*///
///*���ز�����C_Valid����ʾ�Ϸ������£�C_Invalid����ʾ�Ϸ���δ����*///
///**************************************************************************************///
uchar8 DF_GetKsyUpStatus_LowPower(void)
{
	if( IO_POWERDOWN->IDR & POWERDOWN_SELECT )
	{
		return C_Valid;		///*Ϊ�߱�ʾ�е�*///
	}
	else
	{
		return C_Invalid;	///*Ϊ�ͱ�ʾ����*///
	}
}
///***********************************************************************************///
///**************************************************************************************///
///*����ԭ�ͣ�uchar8 DF_GetIOStatus_MainPower(void)										*///
///*������������ȡ��Դ������״̬                                                      *///
///*�����������											                            *///
///*�����������                                                                        *///
///*���ز�����C_Valid����ʾ�е磻C_Invalid����ʾ����                                    *///
///**************************************************************************************///
//uchar8 DF_GetIOStatus_MainPower(void)
//{
//	if( IO_POWERDOWN->IDR & POWERDOWN_SELECT )
//	{
//		return C_Valid;		///*Ϊ�߱�ʾ�е�*///
//	}
//	else
//	{
//		return C_Invalid;	///*Ϊ�ͱ�ʾ����*///
//	}
//}
///***********************************************************************************///
///*Function����ȡ�ⲿ������ߵ�״̬
///*Description�������õ��Ŀ���״̬����ȡ������
///*Input��IOName
///*Output����
///*Return��C_Valid��C_Invalid��C_Error
///*											C_Valid			C_Invalid		C_Error*///
///*C_KeyUp          	�Ϸ���          		����    		δ��                   *///
///*C_KeyDown        	�·���                  ����            δ��                   *///
///*C_KeyPrg         	��̼�                  ����            δ��                   *///
///*C_KeyOpenCover   	�����                  �ϸ�            ����                   *///
///*C_KeyOpenTerminal	����β��                �ϸ�            ����                   *///
///*C_CheckAuPower   	������Դ���            ����            δ����                 *///
///*C_CheckMainPower 	����Դ���              ����            δ����                 *///
///*C_Magnetic       	�ų����                �дų�          �޴ų�                 *///
///*C_MeterICIRQ     	����оƬIRQ�ж�         ���ж�          ���ж�                 *///
///*C_RelayStatus    	�̵���״̬���          �̵���ͨ        �Ͽ�                   *///
///*C_ModuleStatus   	ģ�鷢��״ָ̬ʾ        ģ�鷢��        δ����                 *///
///*C_CardStatus     	�忨״̬���            �в忨          �޲忨                 *///
///*C_ExternalRelayStatus   ���ü̵���״̬���  ��ƽ��          ��ƽ��                 *///
///*Calls��
///*Called By��
///*Influence���ú������ж�����ã��������������е���
///*Tips���ú����ڵ��ܱ��е��ʱ����ã����ֿ���ʹ������������Щ����û�йرգ��͹����¼���ʹ�������Ŀ���������ĺ���
///*Others��
///***********************************************************************************///
uchar8 DF_GetIOStatus(uchar8 IOName)
{
	uchar8	V_ucReturn = C_Error;		///*����ֵ��ʼΪ������*///
	switch( IOName )
	{
		///*******************************************************///
		case C_KeyUp:
		{
			//SET_KEYUP_INPUT();
			if( READ_KEYUP == KEYUP_SELECT )
			{
				V_ucReturn = C_Invalid;				///*����Ϊ�߱�ʾ����δ����*///
			}
			else
			{
				V_ucReturn = C_Valid;
			}
			break;
		}
		///*******************************************************///
		case C_KeyDown:
		{
			//SET_KEYDOWN_INPUT();
			if( READ_KEYDOWN == KEYDOWN_SELECT )
			{
				V_ucReturn = C_Invalid;				///*����Ϊ�߱�ʾ����δ����*///
			}
			else
			{
				V_ucReturn = C_Valid;
			}
			break;
		}
		///*******************************************************///
//		case C_KeyPrg:
//		{
//			//SET_KEYPRG_INPUT();
//			if( READ_KEYPRG == KEYPRG_SELECT )
//			{
//				V_ucReturn = C_Invalid;				///*����Ϊ�߱�ʾ����δ����*///
//			}
//			else
//			{
//				V_ucReturn = C_Valid;
//			}
//			break;
//		}
		///*******************************************************///
		case C_KeyOpenCover:
		{
			//SET_KEYOPENCOVER_INPUT();
			if( READ_KEYOPENCOVER == KEYOPENCOVER_SELECT )
			{
				V_ucReturn = C_Valid;				///*����Ϊ�߱�ʾ���ںϸ�״̬*///
			}
			else
			{
				V_ucReturn = C_Invalid;				///*����Ϊ�ͱ�ʾ���ڿ���״̬*///
			}
			break;
		}
		///*******************************************************///
		case C_KeyOpenTerminal:
		{
			//SET_KEYOPENTERMINAL_INPUT();
			if( READ_KEYOPENTERMINAL == KEYOPENTERMINAL_SELECT )
			{
				V_ucReturn = C_Valid;				///*����Ϊ�߱�ʾ���ںϸ�״̬*///
			}
			else
			{
				V_ucReturn = C_Invalid;				///*����Ϊ�ͱ�ʾ���ڿ���״̬*///
			}
			break;
		}
		///*******************************************************///
		case C_CheckAuPower:
		{
			//SET_CHECKAUPOWER_INPUT();
			if( READ_CHECKAUPOWER == CHECKAUPOWER_SELECT )
			{
				V_ucReturn = C_Invalid;				///*����Ϊ�߱�ʾ������Դδ����*///
			}
			else
			{
				V_ucReturn = C_Valid;				///*����Ϊ�ͱ�ʾ����*///
			}
			break;
		}
		///*******************************************************///
		case C_Magnetic:
		{
			//SET_MAGNETICRIGHT_INPUT();
			//SET_MAGNETICRIGHTUP_INPUT();
			//SET_MAGNETICLEFT_INPUT();
			//SET_MAGNETICLEFTUP_INPUT();
			if( 
				(READ_MAGNETICRIGHT == MAGNETICRIGHT_SELECT )
				&&(READ_MAGNETICRIGHTUP == MAGNETICRIGHTUP_SELECT )
				&&(READ_MAGNETICLEFT == MAGNETICLEFT_SELECT )
				&&(READ_MAGNETICLEFTUP == MAGNETICLEFTUP_SELECT ) 
				)
			{
				V_ucReturn = C_Invalid;				///*����ȫ��Ϊ�߱�ʾ�޴ų�����*///
			}
			else
			{
				V_ucReturn = C_Valid;				///*��һ����Ϊ�ͱ�ʾ�дų�����*///
			}
			break;
		}
		///*******************************************************///
//		case C_MeterICIRQ:
//		{
//			//SET_EMETERIRQ_INPUT();
//			if( READ_EMETERIRQ == EMETERIRQ_SELECT )
//			{
//				V_ucReturn = C_Invalid;				///*����Ϊ�߱�ʾ���ж�����*///
//			}
//			else
//			{
//				V_ucReturn = C_Valid;
//			}
//			break;
//		}
		///*******************************************************///
		case C_RelayStatus:
		{
			//SET_RELAYSTATUS_INPUT();
			if( READ_RELAYSTATUS == RELAYSTATUS_SELECT )
			{
				V_ucReturn = C_Valid;				///*����Ϊ�߱�ʾ�̵�����ͨ*///
			}
			else
			{
				V_ucReturn = C_Invalid;
			}
			break;
		}
		///*******************************************************///
		case C_ExternalRelayStatus:
		{
			if( READ_EXTERNALRELAYSTATUS == EXTERNALRELAYSTATUS_SELECT )
			{
				V_ucReturn = C_Valid;				
			}
			else
			{
				V_ucReturn = C_Invalid;         /* 20�淶�����ü̵���������20ms�Ĺ�Ƶ�ܲ��źţ��޹�Ƶ�źű�ʾ�� */
			}
			break;
		}       
		///*******************************************************///
		case C_ModuleStatus:
		{
			//SET_MODULESTATUS_INPUT();
			if( READ_MODULESTATUS == MODULESTATUS_SELECT )
			{
				V_ucReturn = C_Valid;				///*����Ϊ�߱�ʾģ�鴦�ڷ���״̬*///
			}
			else
			{
				V_ucReturn = C_Invalid;				///*����Ϊ�ͱ�ʾģ�鴦�ڲ�����״̬*///
			}
			break;
		}
		///*******************************************************///
		case C_CardStatus:
		{
			//SET_CARDSTATUS_INPUT();
			if(( READ_CARDSTATUS == CARDSTATUS_SELECT )&&( SF_Shut_RealTimeData() == C_OK ))
			{
				V_ucReturn = C_Valid;				///*����Ϊ�߱�ʾ�в忨,�ұ���ʱ�䵽,���������Ч��Ƭ*///
			}
			else
			{
				V_ucReturn = C_Invalid;				///*����Ϊ�ͱ�ʾ�޲忨*///
			}
			break;
		}
		///*******************************************************///
		default:
			;
		break;
		///*******************************************************///
		
	}
	return V_ucReturn;
}

///***********************************************************************************///
///*�����������๦�ܿ�ѡ�����������*///
///***********************************************************************************///
void DF_MultiFunction_SelectSecondPulse(void)
{
	Select_SecondPulseOut();
}

///***********************************************************************************///
///*�����������๦�ܿ�ѡ�������������*///
///***********************************************************************************///
void DF_MultiFunction_SelectDemandPulse(void)
{
	Select_DemandPulseOut();
}

///***********************************************************************************///
///*�����������๦�ܿ�ѡ�������������*///
///***********************************************************************************///
void DF_MultiFunction_SelectRatePulse(void)
{
	Select_RatePulseOut();
}

///***********************************************************************************///
///*�����������๦�ܿڹر�������ܣ����๦�ܿڴ��ڿ���״̬�������κ�����*///
///***********************************************************************************///
void DF_MultiFunction_Close(void)
{
	Close_MultiFunctionOut();
}

///***********************************************************************************///
///*�����������๦�ܿ����������*///
///***********************************************************************************///
void DF_MultiFunction_OutputSecondPulse(void)
{
	MultiFunction_OutputSecondPulse();
}

///***********************************************************************************///
///*�����������๦�ܿ������������*///
///***********************************************************************************///
void DF_MultiFunction_OutputDemandPulse(void)
{
	MultiFunction_OutputDemandPulse();
}

///***********************************************************************************///
///*�����������๦�ܿ����ʱ��Ͷ������*///
///***********************************************************************************///
void DF_MultiFunction_OutputRatePulse(void)
{
	MultiFunction_OutputRatePulse();
}



///***********************************************************************************///
///*����˵��������оƬ��Դ����				    									 *///
///***********************************************************************************///
void DF_SwitchOn_EMeterIcPower(void)
{
	SwitchOn_MeterICPower();
}
void DF_SwitchOff_EMeterIcPower(void)
{
	SwitchOff_MeterICPower();
}
///***********************************************************************************///
///*����˵����LCD��Դ����				    									 *///
///***********************************************************************************///
void DF_SwitchOn_LCDPower(void)
{
	SwitchOn_LCDPower();
}
void DF_SwitchOff_LCDPower(void)
{
	SwitchOff_LCDPower();
}
///***********************************************************************************///
///*����˵����Flash�������Դ����				    									 *///
///***********************************************************************************///
void DF_SwitchOn_FlashPower(void)
{
	SwitchOn_FlashPower();
}
void DF_SwitchOff_FlashPower(void)
{
	SwitchOff_FlashPower();
}

///***********************************************************************************///
///*����˵�����������ݳ����ƴ���			    									 *///
///***********************************************************************************///
void DF_SwitchOn_SuperCapCharge(void)
{
	SuperCapCharge_En();
}
void DF_SwitchOff_SuperCapCharge(void)
{
	SuperCapCharge_Dis();
}

///***********************************************************************************///
///*����˵�����������ݹ������				    									 *///
///***********************************************************************************///
void DF_SwitchOn_SuperCapPower(void)
{
	SwitchOn_SuperCapPower();
}
void DF_SwitchOff_SuperCapPower(void)
{
	SwitchOff_SuperCapPower();
}

///***********************************************************************************///
///*����˵����6V��ط��ۻ�����				    									 *///
///***********************************************************************************///
void DF_SwitchOn_PreventBlunt(void)
{
//	SwitchOn_PreventBlunt();
}
void DF_SwitchOff_PreventBlunt(void)
{
//	SwitchOff_PreventBlunt();
}

/********************************************************************************
����ԭ�ͣ�void DF_SwitchOn_WakeUpPower(void)
         void DF_SwitchOff_WakeUpPower(void)
����������6V��ع�����ƣ�ͣ�绽�ѵ�Դ
�����������
�����������
����λ�ã��͹���
��    ע��
*********************************************************************************/
void DF_SwitchOn_WakeUpPower(void)
{
    SwitchOn_WakeUpPower();
}

void DF_SwitchOff_WakeUpPower(void)
{
	SwitchOff_WakeUpPower();
}
/********************************************************************************
����˵����void DF_SwitchOn_WakeUpPower_NoBatter(void)	
         void DF_SwitchOff_WakeUpPower_NoBatter(void)
����������6V��ع�����ƣ�ͣ�绽�ѵ�Դ,û��ͣ�����ʱ
�����������
�����������
����λ�ã��͹���
��    ע��
*********************************************************************************/
void DF_SwitchOn_WakeUpPower_NoBatter(void)
{
    SwitchOn_WakeUpPower_NoBatter();
}

void DF_SwitchOff_WakeUpPower_NoBatter(void)
{
	SwitchOff_WakeUpPower_NoBatter();
}
///***********************************************************************************///
///*����˵���������ϱ����ƣ�On��ʾ�������ϱ���Off��ʾ�������ϱ�						 *///
///***********************************************************************************///
void DF_SwitchOn_EventOut(void)
{
	EventOut_EN();
}
void DF_SwitchOff_EventOut(void)
{
	EventOut_DIS();
}

///***********************************************************************************///
///*����˵����ģ�����ÿ���															 *///
///***********************************************************************************///
void DF_SwitchOn_ModuleSet(void)
{
	ModuleSet_EN();
}
void DF_SwitchOff_ModuleSet(void)
{
	ModuleSet_DIS();
}

///***********************************************************************************///
///*����˵����ģ�鸴λ����															 *///
///***********************************************************************************///
void DF_SwitchOn_ModuleEn(void)
{
	Module_EN();
}
void DF_SwitchOff_ModuleEn(void)
{
	Module_Reset();
}

///***********************************************************************************///
///*����˵����������յ�Դ����															 *///
///***********************************************************************************///
void DF_SwitchOn_InfrarxPower(void)
{
	SwitchOn_InfrarxPower();
}
void DF_SwitchOff_InfrarxPower(void)
{
	SwitchOff_InfrarxPower();
}

///***********************************************************************************///
///*����˵����������Դ��������															 *///
///***********************************************************************************///
void DF_CHECKAUPOWER_INPUT(void)
{
	if(C_L_SmartMeter!=C_Meter_Type)///*���ر��������Զ�����ܱ�����Դ�����߳�ͻ
	{
		SET_CHECKAUPOWER_INPUT();
	}
}
///***********************************************************************************///
///*����˵��������������						 *///
///***********************************************************************************///
void DF_SwitchOn_Beeper(void)
{
	if(C_L_SmartMeter==C_Meter_Type)///*���طѿط�����
	{
		SwitchOn_Beep();
	}	
}
void DF_SwitchOff_Beeper(void)
{
	if(C_L_SmartMeter==C_Meter_Type)///*���طѿط�����
	{
		SwitchOff_Beep();
	}	
}
void DF_ReversePhase_Beeper(void)			///*������״̬ȡ��*///
{
	ulong32 IO_State;
	IO_State=IO_BEEP->ODR;
	if(C_L_SmartMeter==C_Meter_Type)///*���طѿط�����
	{
		if(IO_State&BEEPSET)
		{
			IO_BEEP->BSRR = BEEPRESET;
		}
		else
		{
			IO_BEEP->BSETH = BEEPSET;
		}		
	}
///	Switch_ReversePhaseBeeper();
}

///***********************************************************************************///
///*����˵�����ر���բָʾ��:���ڵ����ж������բָʾ��						 *///
///***********************************************************************************///
void DF_SwitchOff_TripLed(void)
{
	SwitchOff_TripLed();
}


///***********************************************************************************///
///*����ԭ�ͣ�void DF_ConfigPowerDownInterrupt)    									 *///
///*�����������е��ڼ�������жϿ��ߵ�����       									 *///
///*�����������                                 									 *///
///*�����������                                 									 *///
///*���ز�������                                 									 *///
///*����˵����                                   									 *///
///*���û��ƣ�                                   									 *///
///*��    ע��                                   									 *///
///***********************************************************************************///
void DF_ConfigPowerDownInterrupt(void)
{
	ulong32 SV_ulTemp_GPIO;
	///***********�������жϿ���*************///
	if((ANAC->SVDCON&ANAC_SVDCON_SVDEN_ENABLE)==ANAC_SVDCON_SVDEN_ENABLE)
	{
		ANAC->SVDCON &= (~ANAC_SVDCON_SVDEN_ENABLE);
	}
	SV_ulTemp_GPIO = IO_POWERDOWN->MODER;
	SV_ulTemp_GPIO &= POWERDOWN_IN_MODE;
	SV_ulTemp_GPIO |= POWERDOWN_Ana_MODE;
	IO_POWERDOWN->MODER = SV_ulTemp_GPIO;
	IO_POWERDOWN->INEN |= POWERDOWN_INOn;
	IO_POWERDOWN->PUPDR &= POWERDOWN_NOPUPD;
//	if(!(ANAC->SVDCFG&ANAC_SVDCFG_DFEN_ENABLE))
//	{
//		ANAC->SVDCFG|=ANAC_SVDCFG_DFEN_ENABLE;
//	}
//	if(ANAC->SVDCFG&ANAC_SVDCFG_SVDMOD_INTERVAL)
//	{
//		ANAC->SVDCFG&=(~ANAC_SVDCFG_SVDMOD_INTERVAL);
//	}	
//	if((ANAC->SVDCFG & ANAC_SVDCFG_SVDLVL_SVS)!=ANAC_SVDCFG_SVDLVL_SVS)
//	{
//		ANAC->SVDCFG|=ANAC_SVDCFG_SVDLVL_SVS;
//	}
//	if((ANAC->SVDCFG & ANAC_SVDCFG_PRIE_PFIE_ENABLE)!=ANAC_SVDCFG_PFIE_ENABLE)
//	{
//		ANAC->SVDCFG &= (~ANAC_SVDCFG_PRIE_PFIE_ENABLE);
//		ANAC->SVDCFG|=ANAC_SVDCFG_PFIE_ENABLE;
//	}	
	if(ANAC->SVDCFG !=	0x000002f8)
	{
		ANAC->SVDCFG = 0x000002f8;
	}

	if((ANAC->SVDSIF&0x00000003)!=0)///*���жϱ�־
	{
		ANAC->SVDSIF|=0x00000003;
	}		
	
	NVIC_EnableIRQ(PowerDown_IRQn);							///*�����ж�ʹ��*///
	ANAC->SVDCON |= ANAC_SVDCON_SVDEN_ENABLE;
}

///***********************************************************************************///
///*����ԭ�ͣ�void DF_ConfigNCIO(void)*///
///*�����������ϵ��������յ�IO������*///
///*          �������յĿ���,���ϵ��ֻ����һ��:��������͵�ƽ,���ر�������*///
///***********************************************************************************///
void DF_ConfigNCIO(void)
{
	uchar8 i;
	ulong32 buff;	/*���ڶ�->�޸�->д*///
	
	for(i=0;i<C_Table_NCIO_Len;i++)
	{
		buff = ((GPIOx_Type *)Table_NCIO[i].portregister)->MODER;		/*���*///
		buff &= Table_NCIO[i].inputmode;
		buff |= Table_NCIO[i].outputmode;
		((GPIOx_Type *)Table_NCIO[i].portregister)->MODER = buff;
		
		buff = ((GPIOx_Type *)Table_NCIO[i].portregister)->OTYPER;	/*��©*///
		buff |= Table_NCIO[i].outputtype;
		((GPIOx_Type *)Table_NCIO[i].portregister)->OTYPER = buff;
		
		((GPIOx_Type *)Table_NCIO[i].portregister)->BSETH = Table_NCIO[i].outvalue;	/*�����*///
	}
}

///***********************************************************************************///
///*����ԭ�ͣ�void InF_ConfigIOInPowerON(void)    									 *///
///*�����������ϵ�������ȡ�ͣ�绽�Ѻ�IO������   									 *///
///*�����������                                 									 *///
///*�����������                                 									 *///
///*���ز�������                                 									 *///
///*����˵����                                   									 *///
///*���û��ƣ�                                   									 *///
///*��    ע��                                   									 *///
///***********************************************************************************///
void InF_ConfigIOInPowerON(void)
{
	///*���Ƚ�ϵͳʱ�����ø�port��*///
	if(!(RCC->PERCLKCON1&RCC_PERRCCCON1_PDCCKEN_ON))
	{
		RCC->PERCLKCON1|=RCC_PERRCCCON1_PDCCKEN_ON;
	}
//	IOPACLKENABLE;
//	IOPBCLKENABLE;
//	IOPCCLKENABLE;
//	IOPDCLKENABLE;
//	IOPECLKENABLE;
//	IOPHCLKENABLE;
//	
//	EXTI->EMR = 0x00000000;
//	EXTI->IMR = 0x00000000;
//	EXTI->RTSR = 0x00000000;
//	EXTI->FTSR = 0x00000000;
	///*�ϵ����п���ȫ������һ��*///
	DF_SwitchOff_Beeper();
	InF_InitE2();
	InF_InitFRAM();
	LCD_IO_Init;
	Flash_IO_Init;
	InF_Deactivation_7816_Card();
	SET_CARDSTATUS_INPUT();
	InF_Deactivation_7816_Esam();
	SwitchOn_ExternalRelay();
	Hold_InternalRelay();
	SwitchOff_WarnOut();
	SET_KEYUP_INPUT();
	SET_KEYDOWN_INPUT();
	
//	SET_KEYPRG_INPUT();
//	RTC_IO_Init;
	
	SET_KEYOPENCOVER_INPUT();
	SET_KEYOPENTERMINAL_INPUT();
	DF_CHECKAUPOWER_INPUT();
	SET_MAGNETICRIGHT_INPUT();
	SET_MAGNETICRIGHTUP_INPUT();
	SET_MAGNETICLEFT_INPUT();
	SET_MAGNETICLEFTUP_INPUT();
	SET_RELAYSTATUS_INPUT();
	SET_EXTERNALRELRELAYSTATUS_INPUT();
	SET_MODULESTATUS_INPUT();
	SwitchOff_BackLight();
	SwitchOff_TripLed();
	SwitchOff_SuperCapPower();
	DF_SwitchOn_FlashPower();
//	SwitchOff_WakeUpPower();///*��⵽�е���ٹر�,����Flash��Դ
	//SET_EMETERIRQ_INPUT();	
//	SwitchOff_PreventBlunt();
	Switchon_RELAYFILT();//�̵�����������˲�

	SuperCapCharge_Dis();	
	SF_InfraModulatedSignalConfig();	
	DF_Switch_CardPower(C_Off);
	DF_Switch_CardSck(C_Off);
	DF_Switch_CardEn(C_Off);
	DF_SwitchOff_LCDPower();	
	DF_ConfigNCIO();		///*�������յ�IO*///	
//	SwitchOn_BackLight();
//       uchar8 i;
//       for(i=0;i<200;i++)
//        {
//           __NOP();
//           __NOP();
//           __NOP();
 //          __NOP();  
 //       }
    /*Ŀǰû���õ������߿�©�����*/	
    SwitchOff_MODULE_PWCTL_PowerOff();
    
	DF_ConfigPowerDownInterrupt();
//	SwitchOff_BackLight();
	
	InF_JTagEnable();	///*��J-Tag��������Ϊʹ��*///
}

///************************************************************************///
///*����ԭ��:void InF_JTagEnable(void)
///*��������:��J-Tag��������Ϊʹ��
///*����ʱ��:�ϵ��ʼ������һ�Σ�ͣ�绽�ѵ���һ��
///************************************************************************///
void InF_JTagEnable( void )
{
//	ulong32	i;
//	i = GPIOA->MODER;
//	i &= 0x03ffffff;
//	i |= 0xa8000000;
//	GPIOA->MODER = i;
//	
//	i = GPIOA->PUPDR;
//	i &= 0x03ffffff;
//	i |= 0x64000000;
//	GPIOA->PUPDR = i;
//	
//	i = GPIOA->AFRH;
//	i &= 0x000fffff;
//	GPIOA->AFRH = i;
//	///****************************************************************///
//	i = GPIOB->MODER;
//	i &= 0xfffffc3f;
//	i |= 0x00000280;
//	GPIOB->MODER = i;
//	
//	i = GPIOB->PUPDR;
//	i &= 0xfffffc3f;
//	i |= 0x00000100;
//	GPIOB->PUPDR = i;
//	
//	i = GPIOB->OSPEEDR;
//	i |= 0x000000c0;
//	GPIOB->OSPEEDR = i;
//	
//	i = GPIOB->AFRL;
//	i &= 0xfff00fff;
//	GPIOB->AFRL = i;
}
