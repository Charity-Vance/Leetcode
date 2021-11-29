/*******************************************************************************
Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     Display.h
Version:       V1
Author:        
Date:          2014-3-12
Description:   
---------------------------------------------------------------------------------
History1:      ��1���޸�
����1. Date:   20211021
   	   Author: lx
       Modification:
	   ---------------------------------------------------------------------------
����2. Date:
   	   Author:
       Modification:
----------------------------------------------------------------------------------
History2:      ��2���޸�
����1. Date:
   	   Author:
       Modification:
	   ---------------------------------------------------------------------------
����2. Date:
   	   Author:
       Modification:
******************************************************************************/
#ifndef	__Display_H
#define	__Display_H

#include "Public.h"

#pragma pack(1)                     /*1�ֽڶ���*/

/*****************************״̬�ַ���ʾ���⻺��bitλ�궨��,�����⻺����һһ��Ӧ*****************************************/
#define	CBit_AxisSign			      0x10			/*������          */
#define	CBit_Q1Sign			          0x01			/*1������ʾ����   */
#define	CBit_Q2Sign			          0x02			/*2������ʾ����   */
#define	CBit_Q3Sign			          0x04			/*3������ʾ����   */
#define	CBit_Q4Sign			          0x08			/*4������ʾ����   */
#define	CBit_Step1Sign			      0x01			/*����1           */
#define	CBit_Step2Sign			      0x02			/*����2           */
#define	CBit_Step3Sign			      0x04			/*����3           */
#define	CBit_Step4Sign			      0x08			/*����4           */
#define	CBit_Rate1Sign			      0x10			/*����1           */
#define	CBit_Rate2Sign			      0x20			/*����2           */
#define	CBit_Rate3Sign			      0x40			/*����3           */
#define	CBit_Rate4Sign			      0x80			/*����4           */
#define	CBit_LSign			          0x80			/*���ݷ���L       */
#define	CBit_TSign			          0x40			/*���ʷ���S       */
#define	CBit_GPRSSign			      0x08			/*���߷���        */
#define	CBit_GPRSSignalSign1		  0x80			/*�ź�ǿ��1       */
#define	CBit_GPRSSignalSign2		  0xC0			/*�ź�ǿ��2,��ʾ�����ź�ǿ��1*/
#define	CBit_GPRSSignalSign3		  0xE0			/*�ź�ǿ��3       */
#define	CBit_GPRSSignalSign4		  0xF0			/*�ź�ǿ��4       */
#define	CBit_ModuleComSign			  0x04			/*ģ��ͨ�ŷ���    */
#define	CBit_ComSign			      0x02			/*ͨ�ŵ绰����    */
#define	CBit_ComChannel1Sign		  0x01			/*ͨ��1����       */
#define	CBit_ComChannel2Sign		  0x80			/*ͨ��2����       */
#define	CBit_ProgramEnableSign		  0x40			/*�����Ч        */
#define	CBit_HoldUpSign			      0x20			/*�����֤����    */
#define	CBit_PublicKeySign		  	  0x10			/*��Կ��־        */
#define	CBit_AlarmSign			      0x08			/*������־        */
#define	CBit_ReadCardSign		  	  0x04			/*����������־	  */
#define	CBit_DoingSign			      0x02			/*���С���־	  */
#define	CBit_SuccessSign		      0x01			/*�ɹ�            */
#define	CBit_FailSign			      0x80			/*ʧ��            */
#define	CBit_PurchaseSign			  0x40			/*�빺��          */
#define	CBit_OverdrawSign			  0x20			/*͸֧            */
#define	CBit_RealayOpenSign			  0x10			/*��բ            */
#define	CBit_UaSign			          0x80			/*Ua              */
#define	CBit_UbSign			          0x40			/*Ub              */
#define	CBit_UcSign			          0x20			/*Uc              */
#define	CBit_NegativePhaseSign		  0x10			/*������          */
#define	CBit_IaNegativeSign			  0x08			/*Ia����ǰ��-��   */
#define	CBit_IaSign			          0x04			/*Ia              */
#define	CBit_IbNegativeSign			  0x02			/*Ib����ǰ��-��   */
#define	CBit_IbSign			          0x01			/*Ib              */
#define	CBit_IcNegativeSign			  0x80			/*Ic����ǰ��-��   */
#define	CBit_IcSign			          0x40			/*Ic              */
#define	CBit_TimeTable1Sign			  0x08			/*��һ��ʱ�α�    */
#define	CBit_TimeTable2Sign			  0x04			/*�ڶ���ʱ�α�    */
#define	CBit_RTCBatterySign			  0x02			/*ʱ�ӵ��Ƿѹ    */
#define	CBit_PowerBatterySign		  0x01			/*ͣ�����Ƿѹ    */
#define	CBit_HoardingSign			  0x10			/*���ڻ���־      */
#define	CBit_CurrentStep			  0x80			/*��ǰ�׽���      */
#define	CBit_BakStep			      0x40			/*�����׽�����Ч����*/
/*******************************С����궨��,������ʾ����λ *******************/
/*****��ʾ���棬��������ʾ��񻺴��Ӧ*****/
#define C_OneDot8P                  0x01
#define C_TwoDot7P                  0x02
#define C_ThreeDot6P                0x10
#define C_FourDot5P                 0x08
#define C_FiveDot4P                 0x20
#define C_SixDot3P                  0x40
#define C_SevenDot2P                0x80
#define C_CoL1Dot                   0x04
#define C_CoL2Dot                   0x01
/***��ʾ��ţ��и������ֱ����*������0--7��ʾ0-7λС����******/
#define C_CoL15PDot                 8     /*XXXX:XXXX*/
#define C_CoL25P3P7PDot             9     /*XX.XX.XX:XX*/
#define C_CoL27PDot                 10    /*XXXXXX��XX*/ 
#define C_CoL2CoL15P7PDot           11    /*XXXX��XX��XX*/
#define C_CoL2CoL15P3P7PDot         12    /*XX.XX:XX:XX*/   
#define C_5P7PDot                   13    /*XXXX.XX.XX*/ 
#define C_CoL15P7PDot               14    /*XXXX��XX.XX*/  
#define C_5P3P7PDot                 15    /*XX.XX.XX.XX*/
/*****************************��ʾ��λ�궨��********************************/
/*********��ʾ���棬��������ʾ��񻺴��Ӧ************/
#define C_DisW                      0x60
#define C_DiskW                     0xE0
#define C_DiskWh                    0xF0
#define C_Disvar                    0x02
#define C_Diskvar                   0x06
#define C_Diskvarh                  0x07
#define C_DisV                      0x20
#define C_DisA                      0x08
#define C_DisVA                     0x48
#define C_DiskVA                    0xA8
#define C_DisYuan                   0x04
#define C_DisWanYuan                0x0C
#define C_DiskVAh                   0xB8
#define C_DisAh                     0x18
/*********��ʾ��ţ��и������ֱ����*******/
#define C_DisNo                     0
#define C_DiskWNum                  1
#define C_DiskWhNum                 2
#define C_DiskvarNum                3
#define C_DiskvarhNum               4
#define C_DisVNum                   5
#define C_DisANum                   6
#define C_DiskVANum                 7
#define C_DisYuanNum                8
#define C_DisWanYuanNum             9
#define C_DisAhNum                  10
#define C_DiskVAhNum                11
#define C_DisYuankwhNum             12
#define C_DisVANum                  13
#define C_DisWNum                   14
#define C_DisvarNum                 15

#define C_DisCurr                   0x80      /*����ǰ����ʾ*/
#define C_DisLast                   0x40      /*���ϡ���ʾ*/
#define C_DisLossVol                0x06      /*��ʧѹ����ʾ*/
#define C_DisLossCurr               0x05      /*��ʧ������ʾ*/
#define C_DisAPhase                 0x80      /*��A����ʾ*/
#define C_DisB                      0x40      /*��B����ʾ*/
#define C_DisC                      0x20      /*��C����ʾ*/
#define C_DisNegativeSign           0x20      /*������"-"��ʾ*/
#define C_DisFanXiang               0x0A      /*"����"��ʾ*/ 
#define C_DisMonth                  0x20      /*���¡���ʾ*/
#define C_DisE                      0xE0      /*"E0"��ʾ*/
#define C_DisR                      0x01      /*"r"��ʾ?*/
#define C_DisHenggang               0x01      /*"-"��ʾ?*/  
/****************************�����궨��****************************************/
#define C_ALLScreenDisplay         0x01           /*ȫ����ʾ*/
#define C_CheckDisplay             0x02           /*Һ���鿴*/
#define C_KeyDisplay               0x03           /*������ʾ*/
#define C_AutoDisplay              0x04           /*�Զ�����*/
#define C_CardAbnormalDisplay      0x05           /*�忨�쳣��ʾ*/
#define C_AlwaysDisplayNiu         0xFFFF         /*����*/
#define C_TwinkleDisplayNiu        0xFFFE         /*��˸*/
#define C_NotDisplayNiu            0x0000         /*����*/
/*#define C_AlwaysDisplayBit         0xC0*/       /*����,������Ϣ��������,Public ���Ѷ���*/
/*#define C_TwinkleDisplayBit        0x40*/       /*��˸*/
/*#define C_NotDisplayBit            0x00*/       /*����*/

#define C_DefaultDisplayTime5s     10                  /*5s:500ms��׼��λ,Ĭ����ʾʱ��*/
#define C_Display60s               120                 /*60s*/ 
#define C_Display30s               60                  /*30s*/
#define C_Display10s               20                  /*10s*/
 
#define C_DefaultDisDi             CPos_Ac_Tol_En_0    /*Ĭ����ʾ�������й��ܵ���*/ 
#define C_DefaultDisDiRelated      0xFFFFFFFF    

#define C_DefaultDisScreenNum      1                  /*Ĭ����ʾ����*/ 

#define C_ALLScreenDisplayDi       0xFFFFFFFF     /*��ʼ��ȫ��״̬DI*/
#define C_DisplayDataByte          29             /*��ʾ�����ֽ���*/
#define C_RAM_Max                  250            /*���ڴ�Ŷ�������󻺴�*/  

#define C_ProgHolScreenNum91       48                                    /*�ڼ���0-48����ʾ�ָ�*/
#define C_ProgHolScreenNumA1       (C_ProgHolScreenNum91+48)             /*50-99����ʾ�ָ�*/
#define C_ProgHolScreenNumB1       (C_ProgHolScreenNumA1+48)            
#define C_ProgHolScreenNumC1       (C_ProgHolScreenNumB1+48)            
#define C_ProgHolScreenNumD1       (C_ProgHolScreenNumC1+48)            
#define C_ProgHolScreenNumE1       (C_ProgHolScreenNumD1+16)            
            
#define C_ProgPTScreenNumC1        58                                    /*ʱ�α�0-58����ʾ�ָ�*/
#define C_ProgPTScreenNumD1        (C_ProgPTScreenNumC1+56)              /*59-114����ʾ�ָ�*/
#define C_ProgPTScreenNumE1        (C_ProgPTScreenNumD1+56)             
#define C_ProgPTScreenNumF1        (C_ProgPTScreenNumE1+56)   

#define C_ChinaeseLineUnit         5     /*���ֱ��ṹ�壬��λ�ǵ�6�У�0-5*/          
#define C_ChinaeseLineDot          6     /*���ֱ��ṹ�壬С�����ǵ�7�У�0-6*/          
#define C_ChinaLineDataLenKillZero 7     /*���ֱ��ṹ�壬��8�У���4λ��ʾ����ʾ��Ӧ�����ݳ��ȣ���4λ��ʾ�����ص�0-7*/          
#define C_ChinaeseLineDataOffSet   8     /*���ֱ��ṹ�壬��9�У���ʾ����ƫ��*/ 

#define C_GetChinaDataLenBit0x07   0x07 /*ȡ���ֱ��ṹ�壬��8�У���3λ��ʾ����ʾ��Ӧ�����ݳ��ȣ���3λ����ʾ�Ƿ���Ҫ����λ���� */          
#define C_NeedSignBit0x08          0x08 /*���ֱ��ṹ�壬��8�У���3λ��ʾ����ʾ��Ӧ�����ݣ��Ƿ���Ҫ����λ����,0x08��ʾ��Ҫ����λ */         


#define C_PreScreenDisDataLen      5     /*ÿ����������ʾ������󳤶��ֽ���,����4���ֽڣ�����С��λ�����ã���Ϊ���5���ֽ� */

#define C_ParameterMaxLen          40    /*��Ϣ���ݲ�����󻺴棬������Ҫ�޸ģ����ֻ�ܷ�10��PT(4�ֽڲ���)*/
#define C_CardDis                  0xAA  /*�忨��ʾ״̬*/
#define C_NoCardDis                0x55  /*�ǲ忨��ʾ״̬*/
#define C_TimingInitSignTime10min  1200  /*���ϵ�500msΪ�������ģ�ÿ10minˢ��1��״̬�ַ�����Դ�����ӿɿ���*/
#define C_ShutBackLEDTime5s        10    /*���ϵ�500msΪ��������*/
#define C_MoneySign                0x55  /*�忨ǰ2s��ʾ*/
/*#define C_Baud600                  0x02*/   /*public���Ѷ���*/
/*#define C_Baud1200                 0x04*/
/*#define C_Baud2400                 0x08*/
/*#define C_Baud4800                 0x10*/
/*#define C_Baud9600                 0x20*/
/*#define C_Baud19200                0x40*/
/*00Ĭ�ϰ������ݳ���hexתBCD��10����Ҫת��20���ֽ�ת��40��ʾʱ������ת����2�ֽڵ���ת*/
/*#define C_NeedDataChange             0x80*/   /*698����������ʱ���ʽ��645��ͬ������ʾ2�ֽڣ��벹һ���ֽ�0x00*/ 
#define C_NeedDataChange             0x40   /*�����ֽڵ���ת�������ֽڵ���ת*/   
#define C_NeedSingleByteChange       0x20   /*���ֽ�hexתbcd*/  
#define C_NoNeedChange               0x10   /*����Ҫת��*/  

#define C_DisRelatedOffset             0x04   /*�����б�ƫ��*/  
#define C_DisScreenNumOffset           0x08   /*��ʾ����ƫ��*/  

#define C_MainDataEn_offset0           0      /*����ʾ���ݵ�1�ֽ�*/ 
#define C_MainDataEn_offset1           1      /*����ʾ���ݵ�2�ֽ�*/ 
#define C_MainDataEn_offset2           2      /*����ʾ���ݵ�3�ֽ�*/ 
#define C_MainDataEn_offset3           3      /*����ʾ���ݵ�4�ֽ�*/
#define C_MainDataEn_offset4           4      /*����ʾ���ݵ�4�ֽ�*/

#define C_EnBorrowPoint_Flag_1         0x9999999999       /*��λ��ʾ�жϱ�־������999999.9999����1λ*/
#define C_EnBorrowPoint_Flag_2         0x99999999999      /*��λ��ʾ�жϱ�־������9999999.9999����2λ*/
#define C_EnBorrowPoint_Flag_3         0x999999999999     /*��λ��ʾ�жϱ�־������99999999.9999����3λ*/
#define C_EnBorrowPoint_Flag_4         0x9999999999999    /*��λ��ʾ�жϱ�־������999999999.9999����4λ*/

#define C_EnBorrowPoint_0               0               /*��λλ����С�ڵ���999999.9999����0λ*/
#define C_EnBorrowPoint_1               1               /*��λλ��������999999.9999����1λ*/
#define C_EnBorrowPoint_2               2               /*��λλ��������9999999.9999����2λ*/
#define C_EnBorrowPoint_3               3               /*��λλ��������99999999.9999����3λ*/
#define C_EnBorrowPoint_4               4               /*��λλ��������99999999.9999����4λ*/

#define C_PreEnDisPoint                 4               /*��ȷ������ʾС��λ��*/

#define C_RecordNum_offset             9      /*��ʾbuffer[9],1P������1����XX���еġ�XX��*/

#define C_EngyRate18_offset            25     /*��ʾ���ܷ�����18����ֵ���е�λ��buffer25*/
#define C_Ladder8_offset               26     /*��ʾL8��8����ֵ���е�λ��buffer25*/  
#define C_Rate18_offset                27     /*��ʾT18��18����ֵ���е�λ��buffer27 */ 
#define C_MainDataHig_offset           28     /*��ʾ�����λ��������ֵ��buffer28*/  


/**********************************˽��ȫ�ֱ���********************************************************************/
uchar8  GV_ucDisplayData[C_DisplayDataByte];          /*��ʾ����*///
uchar8  GV_KillZeroNum;                               /*ȫ�ֱ�����ʾ������,FF��ʾΪ�쳣������ʾ*/
uchar8  GV_PowerOffAutoDisScreenNum;                  /*�Զ�ѭ��������ֻ�ǵ͹���ʱ�ã�����͹���ʱ�ظ������ݲ�*/
ushort16  GV_usPowerOffAutoDisScreenTime;             /*�Զ�ѭ��ÿ����ʾʱ�䣬ֻ�ǵ͹���ʱ�ã�����͹���ʱ�ظ������ݲ�*///
uchar8  GV_PowerOffDisState;                          /*�͹���ʱ����ǰ��ʾ״̬�����͹��ĵ��Ȼ�ȡ����ʼ��Ϊ��ʾ,�͹���ѭ�Խ���������Ϊ����*/
uchar8  GV_CardDisSign;                               /*�忨��ʾ��־����ʼ��Ϊ�ǲ忨��ʾ״̬0x55(�е硢û���ʼ��)������ʾ��ϢԴΪcardʱ���øñ�־Ϊ0xAA����ʾ�忨��ʾ״̬*/
/*uchar8  testniu; */                                 /*��ʱ����ʾ�����׵��ײ���ʾ��Ȼ��ñ�־����Ϊ0x55���ǲ忨��ʾ״̬*/
uchar8  GV_CardAbnDisplayNum;                         /*�忨�쳣��ʾ��*/                        
ushort16 GV_TimingInitSignTime;                       /*��ʱˢ��״̬�ַ�����Դ��ʱ������ʱ��ˢ�£����ӿɿ��ԣ���InF_Display_Init��ʼ����������0����SF_PowerOnDisplay500msTimer������++�ж�*/                        
uchar8  GV_ShutBackLEDTime;                           /*�ϵ�������ⶨʱ�����ϵ�5s�ڱ������(���жϵ�Դ��ѹ���ϵ�5s�󣬱�����������жϵ�Դ��ѹ)*/                        
/*uchar8  GV_PowerOnChangeScreenFlag;*/                   /*������־����ʼ��Ϊ0�����ϵ�500ms�����л�����ʱ��GV_Str_DisplayFlag.SV_usDisplayTimerΪ0ʱ����Ϊ55*/
uchar8  GV_RemainMoney[2][CLChargeBal_BCD];           /*���ڹ���ǰʣ�ࡢ͸֧���������ʾ  ���ñ�־Ϊ55ʱ������Ӳ����ʼ��LCD�����ӿں������������������Ĵ�������ֹ����(���е�����£�����ʱ��ʼ��Һ������)*/
/*uchar8  GV_DispAllScreenMode; */                        /*ȫ��ģʽ*/
typedef struct
{
    ushort16 Time;/*Time����ʾ��ʾʱ�䣻*/
    uchar8 Type;  /*Type����ʾ�ַ�����ʾ��ʽ����ͬһ���ֽڣ����ֽڵĸ���λ��ʾ��ʾ��ʽ*/
                  /*(01:��˸��00���رգ�11����,����������ʾʱ��Ϊ0xFFFFʱ����ʾ���ԣ�*/
                  /*�о���ʱ��ֵʱ����ʾʱ�䰴����ʱ��)����6λ��ʾ��ʾ��ʾ�ַ�����(LED���̵������Ҳ��Ϊһ���ַ�)��*/
}Str_DisplayStatus;/*�忨�쳣��ʾ���øýṹ��,Type��ʾ�������ͣ�BCD��ʽ*/


typedef  struct
{
	 ushort16 Timer;	        /*��ʾʱ��,FFFF��ʾ����,FFFE��ʾ��˸*/
	 uchar8 SourceNo;	        /*Դ��Ϣ��*/  
}Str_DisplaySignMesNum;		    /*��ʾ״̬�ַ��ṹ�� */

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_AxisSign[1];
#define GV_Str_DisplaySignMesNum_AxisSignLen  (sizeof(GV_Str_DisplaySignMesNum_AxisSign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_Q1Sign[1];
#define GV_Str_DisplaySignMesNum_Q1SignLen  (sizeof(GV_Str_DisplaySignMesNum_Q1Sign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_Q2Sign[1];
#define GV_Str_DisplaySignMesNum_Q2SignLen  (sizeof(GV_Str_DisplaySignMesNum_Q2Sign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_Q3Sign[1];
#define GV_Str_DisplaySignMesNum_Q3SignLen  (sizeof(GV_Str_DisplaySignMesNum_Q3Sign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_Q4Sign[1];
#define GV_Str_DisplaySignMesNum_Q4SignLen  (sizeof(GV_Str_DisplaySignMesNum_Q4Sign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_Step1Sign[1];
#define GV_Str_DisplaySignMesNum_Step1SignLen  (sizeof(GV_Str_DisplaySignMesNum_Step1Sign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_Step2Sign[1];
#define GV_Str_DisplaySignMesNum_Step2SignLen  (sizeof(GV_Str_DisplaySignMesNum_Step2Sign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_Step3Sign[1];
#define GV_Str_DisplaySignMesNum_Step3SignLen  (sizeof(GV_Str_DisplaySignMesNum_Step3Sign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_Step4Sign[1];
#define GV_Str_DisplaySignMesNum_Step4SignLen  (sizeof(GV_Str_DisplaySignMesNum_Step4Sign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_Rate1Sign[1];
#define GV_Str_DisplaySignMesNum_Rate1SignLen  (sizeof(GV_Str_DisplaySignMesNum_Rate1Sign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_Rate2Sign[1];
#define GV_Str_DisplaySignMesNum_Rate2SignLen  (sizeof(GV_Str_DisplaySignMesNum_Rate2Sign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_Rate3Sign[1];
#define GV_Str_DisplaySignMesNum_Rate3SignLen  (sizeof(GV_Str_DisplaySignMesNum_Rate3Sign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_Rate4Sign[1];
#define GV_Str_DisplaySignMesNum_Rate4SignLen  (sizeof(GV_Str_DisplaySignMesNum_Rate4Sign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_LSign[1];
#define GV_Str_DisplaySignMesNum_LSignLen  (sizeof(GV_Str_DisplaySignMesNum_LSign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_TSign[1];
#define GV_Str_DisplaySignMesNum_TSignLen  (sizeof(GV_Str_DisplaySignMesNum_TSign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_GPRSSign[1];
#define GV_Str_DisplaySignMesNum_GPRSSignLen  (sizeof(GV_Str_DisplaySignMesNum_GPRSSign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_GPRSSignalSign1[1];
#define GV_Str_DisplaySignMesNum_GPRSSignalSign1Len  (sizeof(GV_Str_DisplaySignMesNum_GPRSSignalSign1)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_GPRSSignalSign2[1];
#define GV_Str_DisplaySignMesNum_GPRSSignalSign2Len  (sizeof(GV_Str_DisplaySignMesNum_GPRSSignalSign2)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_GPRSSignalSign3[1];
#define GV_Str_DisplaySignMesNum_GPRSSignalSign3Len  (sizeof(GV_Str_DisplaySignMesNum_GPRSSignalSign3)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_GPRSSignalSign4[1];
#define GV_Str_DisplaySignMesNum_GPRSSignalSign4Len  (sizeof(GV_Str_DisplaySignMesNum_GPRSSignalSign4)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_ModuleComSign[1];
#define GV_Str_DisplaySignMesNum_ModuleComSignLen  (sizeof(GV_Str_DisplaySignMesNum_ModuleComSign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_ComSign[1];
#define GV_Str_DisplaySignMesNum_ComSignLen  (sizeof(GV_Str_DisplaySignMesNum_ComSign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_ComChannel1Sign[1];
#define GV_Str_DisplaySignMesNum_ComChannel1SignLen  (sizeof(GV_Str_DisplaySignMesNum_ComChannel1Sign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_ComChannel2Sign[1];
#define GV_Str_DisplaySignMesNum_ComChannel2SignLen  (sizeof(GV_Str_DisplaySignMesNum_ComChannel2Sign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_ProgramEnableSign[1];
#define GV_Str_DisplaySignMesNum_ProgramEnableSignLen  (sizeof(GV_Str_DisplaySignMesNum_ProgramEnableSign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_HoldUpSign[1];
#define GV_Str_DisplaySignMesNum_HoldUpSignLen  (sizeof(GV_Str_DisplaySignMesNum_HoldUpSign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_PublicKeySign[1];
#define GV_Str_DisplaySignMesNum_PublicKeySignLen  (sizeof(GV_Str_DisplaySignMesNum_PublicKeySign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_AlarmSign[3];
#define GV_Str_DisplaySignMesNum_AlarmSignLen  (sizeof(GV_Str_DisplaySignMesNum_AlarmSign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_ReadCardSign[1];
#define GV_Str_DisplaySignMesNum_ReadCardSignLen  (sizeof(GV_Str_DisplaySignMesNum_ReadCardSign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_DoingSign[1];
#define GV_Str_DisplaySignMesNum_DoingSignLen  (sizeof(GV_Str_DisplaySignMesNum_DoingSign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_SuccessSign[1];
#define GV_Str_DisplaySignMesNum_SuccessSignLen  (sizeof(GV_Str_DisplaySignMesNum_SuccessSign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_FailSign[1];
#define GV_Str_DisplaySignMesNum_FailSignLen  (sizeof(GV_Str_DisplaySignMesNum_FailSign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_PurchaseSign[3];
#define GV_Str_DisplaySignMesNum_PurchaseSignLen  (sizeof(GV_Str_DisplaySignMesNum_PurchaseSign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_OverdrawSign[1];
#define GV_Str_DisplaySignMesNum_OverdrawSignLen  (sizeof(GV_Str_DisplaySignMesNum_OverdrawSign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_RealayOpenSign[1];
#define GV_Str_DisplaySignMesNum_RealayOpenSignLen  (sizeof(GV_Str_DisplaySignMesNum_RealayOpenSign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_UaSign[2];
#define GV_Str_DisplaySignMesNum_UaSignLen  (sizeof(GV_Str_DisplaySignMesNum_UaSign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_UbSign[2];
#define GV_Str_DisplaySignMesNum_UbSignLen  (sizeof(GV_Str_DisplaySignMesNum_UbSign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_UcSign[2];
#define GV_Str_DisplaySignMesNum_UcSignLen  (sizeof(GV_Str_DisplaySignMesNum_UcSign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_NegativePhaseSign[1];
#define GV_Str_DisplaySignMesNum_NegativePhaseSignLen  (sizeof(GV_Str_DisplaySignMesNum_NegativePhaseSign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_IaNegativeSign[2];
#define GV_Str_DisplaySignMesNum_IaNegativeSignLen  (sizeof(GV_Str_DisplaySignMesNum_IaNegativeSign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_IaSign[2];
#define GV_Str_DisplaySignMesNum_IaSignLen  (sizeof(GV_Str_DisplaySignMesNum_IaSign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_IbNegativeSign[2];
#define GV_Str_DisplaySignMesNum_IbNegativeSignLen  (sizeof(GV_Str_DisplaySignMesNum_IbNegativeSign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_IbSign[2];
#define GV_Str_DisplaySignMesNum_IbSignLen  (sizeof(GV_Str_DisplaySignMesNum_IbSign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_IcNegativeSign[2];
#define GV_Str_DisplaySignMesNum_IcNegativeSignLen  (sizeof(GV_Str_DisplaySignMesNum_IcNegativeSign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_IcSign[2];
#define GV_Str_DisplaySignMesNum_IcSignLen  (sizeof(GV_Str_DisplaySignMesNum_IcSign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_TimeTable1Sign[1];
#define GV_Str_DisplaySignMesNum_TimeTable1SignLen  (sizeof(GV_Str_DisplaySignMesNum_TimeTable1Sign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_TimeTable2Sign[1];
#define GV_Str_DisplaySignMesNum_TimeTable2SignLen  (sizeof(GV_Str_DisplaySignMesNum_TimeTable2Sign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_RTCBatterySign[1];
#define GV_Str_DisplaySignMesNum_RTCBatterySignLen  (sizeof(GV_Str_DisplaySignMesNum_RTCBatterySign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_PowerBatterySign[1];
#define GV_Str_DisplaySignMesNum_PowerBatterySignLen  (sizeof(GV_Str_DisplaySignMesNum_PowerBatterySign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_HoardingSign[2];
#define GV_Str_DisplaySignMesNum_HoardingSignLen  (sizeof(GV_Str_DisplaySignMesNum_HoardingSign)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_CurrentStep[1];
#define GV_Str_DisplaySignMesNum_CurrentStepLen  (sizeof(GV_Str_DisplaySignMesNum_CurrentStep)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_BakStep[1];
#define GV_Str_DisplaySignMesNum_BakStepLen  (sizeof(GV_Str_DisplaySignMesNum_BakStep)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_BackLED[6];
#define GV_Str_DisplaySignMesNum_BackLEDLen  (sizeof(GV_Str_DisplaySignMesNum_BackLED)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_WarnOutPut[4];
#define GV_Str_DisplaySignMesNum_WarnOutPutLen  (sizeof(GV_Str_DisplaySignMesNum_WarnOutPut)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_Beeper[4];
#define GV_Str_DisplaySignMesNum_BeeperLen  (sizeof(GV_Str_DisplaySignMesNum_Beeper)/sizeof(Str_DisplaySignMesNum))

Str_DisplaySignMesNum  GV_Str_DisplaySignMesNum_RelayStatusLED[3];
#define GV_Str_DisplaySignMesNum_RelayStatusLEDLen  (sizeof(GV_Str_DisplaySignMesNum_RelayStatusLED)/sizeof(Str_DisplaySignMesNum))


typedef  struct                                                               
{                                                                          
   ulong32 PStr_DisplaySignMesNum;       /*���ַ���Ӧ��ʾ״̬�ַ��ṹ��Str_DisplaySignMesNum��ַ������������*/
   uchar8 Str_DisplaySignMesNumLen;      /*Str_DisplaySignMesNum����*/
   uchar8 StateNum;	                     /*״̬��ʾͨ���ַ�����*/                      
   uchar8 * PDisplyBuff;                 /*���ַ���Ӧ���⻺���ַ������ӦΪ���⡢ָʾ�ơ������̵����ȱ���״̬ʱ���ñ����������ʼ��Ϊ��C_NULL*/                  
	 uchar8 DisplyBuffBit;               /*���ַ���Ӧ���⻺������Ӧ����λ*/                
}Str_DisplaySign;		                 /*ͨ��״̬�ַ���ʾ�ṹ��*/    
 
const Str_DisplaySign  GV_Str_DisplaySign[]=
{ /*ulong32 PStr_DisplaySignMesNum                           uchar8Str_DisplaySignMesNum����    uchar8״̬��ʾͨ���ַ�����  uchar8 *���ַ���Ӧ���⻺���ַ uchar8���ַ���Ӧ���⻺������Ӧ����λ*/
  {(ulong32)(&GV_Str_DisplaySignMesNum_AxisSign[0]),          GV_Str_DisplaySignMesNum_AxisSignLen,          C_AxisSign,          &GV_ucDisplayData[10],         CBit_AxisSign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_Q1Sign[0]),            GV_Str_DisplaySignMesNum_Q1SignLen,            C_Q1Sign,            &GV_ucDisplayData[10],         CBit_Q1Sign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_Q2Sign[0]),            GV_Str_DisplaySignMesNum_Q2SignLen,            C_Q2Sign,            &GV_ucDisplayData[10],         CBit_Q2Sign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_Q3Sign[0]),            GV_Str_DisplaySignMesNum_Q3SignLen,            C_Q3Sign,            &GV_ucDisplayData[10],         CBit_Q3Sign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_Q4Sign[0]),            GV_Str_DisplaySignMesNum_Q4SignLen,            C_Q4Sign,            &GV_ucDisplayData[10],         CBit_Q4Sign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_LSign[0]),             GV_Str_DisplaySignMesNum_LSignLen,             C_LSign,             &GV_ucDisplayData[11],         CBit_LSign},
  {(ulong32)(&GV_Str_DisplaySignMesNum_TSign[0]),             GV_Str_DisplaySignMesNum_TSignLen,             C_TSign,             &GV_ucDisplayData[11],         CBit_TSign},
  {(ulong32)(&GV_Str_DisplaySignMesNum_GPRSSign[0]),          GV_Str_DisplaySignMesNum_GPRSSignLen,          C_GPRSSign,          &GV_ucDisplayData[12],         CBit_GPRSSign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_GPRSSignalSign1[0]),   GV_Str_DisplaySignMesNum_GPRSSignalSign1Len,   C_GPRSSignalSign1,   &GV_ucDisplayData[12],         CBit_GPRSSignalSign1},         ///*GPRS �ź�ǿ��*///
  {(ulong32)(&GV_Str_DisplaySignMesNum_GPRSSignalSign2[0]),   GV_Str_DisplaySignMesNum_GPRSSignalSign2Len,   C_GPRSSignalSign2,   &GV_ucDisplayData[12],         (CBit_GPRSSignalSign2|CBit_GPRSSignalSign1)},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_GPRSSignalSign3[0]),   GV_Str_DisplaySignMesNum_GPRSSignalSign3Len,   C_GPRSSignalSign3,   &GV_ucDisplayData[12],         (CBit_GPRSSignalSign3|CBit_GPRSSignalSign2|CBit_GPRSSignalSign1)},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_GPRSSignalSign4[0]),   GV_Str_DisplaySignMesNum_GPRSSignalSign4Len,   C_GPRSSignalSign4,   &GV_ucDisplayData[12],         (CBit_GPRSSignalSign4|CBit_GPRSSignalSign3|CBit_GPRSSignalSign2|CBit_GPRSSignalSign1)},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_ModuleComSign[0]),     GV_Str_DisplaySignMesNum_ModuleComSignLen,     C_ModuleComSign,     &GV_ucDisplayData[12],         CBit_ModuleComSign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_ComSign[0]),           GV_Str_DisplaySignMesNum_ComSignLen,           C_ComSign,           &GV_ucDisplayData[12],         CBit_ComSign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_ComChannel1Sign[0]),   GV_Str_DisplaySignMesNum_ComChannel1SignLen,   C_ComChannel1Sign,   &GV_ucDisplayData[12],         CBit_ComChannel1Sign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_ComChannel2Sign[0]),   GV_Str_DisplaySignMesNum_ComChannel2SignLen,   C_ComChannel2Sign,   &GV_ucDisplayData[13],         CBit_ComChannel2Sign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_ProgramEnableSign[0]), GV_Str_DisplaySignMesNum_ProgramEnableSignLen, C_ProgramEnableSign, &GV_ucDisplayData[13],         CBit_ProgramEnableSign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_HoldUpSign[0]),        GV_Str_DisplaySignMesNum_HoldUpSignLen,        C_HoldUpSign,        &GV_ucDisplayData[13],         CBit_HoldUpSign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_PublicKeySign[0]),     GV_Str_DisplaySignMesNum_PublicKeySignLen,     C_PublicKeySign,     &GV_ucDisplayData[13],         CBit_PublicKeySign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_AlarmSign[0]),         GV_Str_DisplaySignMesNum_AlarmSignLen,         C_AlarmSign,         &GV_ucDisplayData[13],         CBit_AlarmSign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_ReadCardSign[0]),      GV_Str_DisplaySignMesNum_ReadCardSignLen,      C_ReadCardSign,      &GV_ucDisplayData[13],         CBit_ReadCardSign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_DoingSign[0]),         GV_Str_DisplaySignMesNum_DoingSignLen,         C_DoingSign,         &GV_ucDisplayData[13],         CBit_DoingSign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_SuccessSign[0]),       GV_Str_DisplaySignMesNum_SuccessSignLen,       C_SuccessSign,       &GV_ucDisplayData[13],         CBit_SuccessSign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_FailSign[0]),          GV_Str_DisplaySignMesNum_FailSignLen,          C_FailSign,          &GV_ucDisplayData[14],         CBit_FailSign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_PurchaseSign[0]),      GV_Str_DisplaySignMesNum_PurchaseSignLen,      C_PurchaseSign,      &GV_ucDisplayData[14],         CBit_PurchaseSign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_OverdrawSign[0]),      GV_Str_DisplaySignMesNum_OverdrawSignLen,      C_OverdrawSign,      &GV_ucDisplayData[14],         CBit_OverdrawSign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_RealayOpenSign[0]),    GV_Str_DisplaySignMesNum_RealayOpenSignLen,    C_RealayOpenSign,    &GV_ucDisplayData[14],         CBit_RealayOpenSign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_UaSign[0]),            GV_Str_DisplaySignMesNum_UaSignLen,            C_UaSign,            &GV_ucDisplayData[15],         CBit_UaSign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_UbSign[0]),            GV_Str_DisplaySignMesNum_UbSignLen,            C_UbSign,            &GV_ucDisplayData[15],         CBit_UbSign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_UcSign[0]),            GV_Str_DisplaySignMesNum_UcSignLen,            C_UcSign,            &GV_ucDisplayData[15],         CBit_UcSign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_NegativePhaseSign[0]), GV_Str_DisplaySignMesNum_NegativePhaseSignLen, C_NegativePhaseSign, &GV_ucDisplayData[15],         CBit_NegativePhaseSign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_IaNegativeSign[0]),    GV_Str_DisplaySignMesNum_IaNegativeSignLen,    C_IaNegativeSign,    &GV_ucDisplayData[15],         CBit_IaNegativeSign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_IaSign[0]),            GV_Str_DisplaySignMesNum_IaSignLen,            C_IaSign,            &GV_ucDisplayData[15],         CBit_IaSign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_IbNegativeSign[0]),    GV_Str_DisplaySignMesNum_IbNegativeSignLen,    C_IbNegativeSign,    &GV_ucDisplayData[15],         CBit_IbNegativeSign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_IbSign[0]),            GV_Str_DisplaySignMesNum_IbSignLen,            C_IbSign,            &GV_ucDisplayData[15],         CBit_IbSign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_IcNegativeSign[0]),    GV_Str_DisplaySignMesNum_IcNegativeSignLen,    C_IcNegativeSign,    &GV_ucDisplayData[16],         CBit_IcNegativeSign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_IcSign[0]),            GV_Str_DisplaySignMesNum_IcSignLen,            C_IcSign,            &GV_ucDisplayData[16],         CBit_IcSign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_TimeTable1Sign[0]),    GV_Str_DisplaySignMesNum_TimeTable1SignLen,    C_TimeTable1Sign,    &GV_ucDisplayData[14],         CBit_TimeTable1Sign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_TimeTable2Sign[0]),    GV_Str_DisplaySignMesNum_TimeTable2SignLen,    C_TimeTable2Sign,    &GV_ucDisplayData[14],         CBit_TimeTable2Sign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_RTCBatterySign[0]),    GV_Str_DisplaySignMesNum_RTCBatterySignLen,    C_RTCBatterySign,    &GV_ucDisplayData[14],         CBit_RTCBatterySign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_PowerBatterySign[0]),  GV_Str_DisplaySignMesNum_PowerBatterySignLen,  C_PowerBatterySign,  &GV_ucDisplayData[14],         CBit_PowerBatterySign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_HoardingSign[0]),      GV_Str_DisplaySignMesNum_HoardingSignLen,      C_HoardingSign,      &GV_ucDisplayData[22],         CBit_HoardingSign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_CurrentStep[0]),       GV_Str_DisplaySignMesNum_CurrentStepLen,       C_CurrentStep,       &GV_ucDisplayData[22],         CBit_CurrentStep},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_BakStep[0]),           GV_Str_DisplaySignMesNum_BakStepLen,           C_BakStep,           &GV_ucDisplayData[22],         CBit_BakStep},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_BackLED[0]),           GV_Str_DisplaySignMesNum_BackLEDLen,           C_BackLED,           C_NULL,                        0x00},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_WarnOutPut[0]),        GV_Str_DisplaySignMesNum_WarnOutPutLen,        C_WarnOutPut,        C_NULL,                        0x00},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_Beeper[0]),            GV_Str_DisplaySignMesNum_BeeperLen,            C_Beeper,            C_NULL,                        0x00},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_RelayStatusLED[0]),    GV_Str_DisplaySignMesNum_RelayStatusLEDLen,    C_RelayStatusLED,    C_NULL,                        0x00},         

};
#define GV_Str_DisplaySignLen  (sizeof(GV_Str_DisplaySign)/sizeof(Str_DisplaySign))

typedef  struct                                                               
{                                                                          
   ulong32 LocalMeterDI;       /*���ر���б�ʶ��*/
   uchar8  CompByteNum;        /*�����ʶ�룬�Ƚ��ֽ������Ӹ�λ��ʼ*/
}Str_LocalMeterDI;		         /*���ر�ʶ����нṹ��*/    

const Str_LocalMeterDI GV_Str_LocalMeterDI[]=           /*���ر����б�ʶ��*/
{
	 {CChargeBal_Hex_Cent,   0x03},               /*��ǰʣ����BCD��ʽ����ǰ͸֧���BCD��ʽ*/
	 {COverDraft_Hex_Cent,   0x03},               /*��ǰʣ����BCD��ʽ����ǰ͸֧���BCD��ʽ*/
	 {CProgTPara_Note_1,     0x03},               /*���ʲ������̼�¼*/
	 {CProgLad_Note_1,       0x03},               /*���ݱ��̼�¼*/
	 {CAbnorC_Note_1,        0x03},               /*�쳣�忨��¼*/ 
	 {CLawlessC_Degree,      0x03},               /*�Ƿ��忨�ܴ���*/
	 {CBuyCurr_T_1,          0x02},               /*�����¼*/ 
	 {CReturn_M_Note_1,      0x02},               /*�˷Ѽ�¼*/
	 {CChange_Rate,          0x04},               /*���׷��ʵ���л�ʱ��*/
	 {CChange_Ladder,        0x04},               /*���׽��ݵ���л�ʱ��*/ 
	 {CStep_Num,             0x04},               /*������*/
	 {CAlam1_Money,          0x03},               /*�������1��ֵ...�˷ѽ��*/
	 {CInset_Card_State,     0x04},               /*�忨״̬��*/
	 {CCurrent_Rate1_Price,  0x03},               /*��ǰ���ʵ��*/
	 {CBackUp_Rate1_Price,   0x03},               /*�����׷��ʵ��*/
	 {CCurrent_Ladder_Table, 0x03},               /*��ǰ�׽��ݱ�*/
	 {CBackUp_Ladder_Table,  0x03},               /*�����׽��ݱ�*/
	 {CCurr_Ladder_Price,    0x04},               /*��ǰ���ݵ��*/
	 {CCurr_Price,           0x04},               /*��ǰ���*/
	 {CCurr_Rate_Price,      0x04},               /*��ǰ���ʵ��*/
	 
};
#define GV_LocalMeterDI_Len (sizeof(GV_Str_LocalMeterDI)/sizeof(Str_LocalMeterDI)) 
    
typedef  struct
{
   ulong32 CodeID;	                 /*��ʾ��ʶ��*/
   ulong32 Related_CodeID;	         /*����OAD��ʶ��*/
   ulong32 P_ChieseTableNo;	         /*��ʾ���ţ��������ֱ��,��ͬ��������,Ϊһ���ṹ������,*/
                                     /*�ô�Ϊĳһ��ṹ���ַ,�������Ͷ���Ϊ�ṹ�������ַ*/
   ushort16 SV_usDisplayTimer;       /*ÿ���л�ʱ��,�л�ʱ�䣬��������ٲ������ݲ����������ʾʱ�䡣*/
   ushort16 ChieseTableLineNo;	     /*������к�,����ṹ��,�ñ�ʶ����ʾ����Ӧ���ศ�����ֱ��ṹ��,������к�.*/
   ushort16 SV_DisplayDataOff;       /*�ñ�ʶ�������ʾʱ����ʾ��Ŷ�Ӧ��ʾ�����ڸñ�ʶ���ж�Ӧ���ݵ�����ƫ�ƣ���0ƫ�ƶ�Ϊ0����1������ƫ��Ϊ��1�������ݳ���*/
   uchar8  SV_ucDisplayMode;	     /*��ʾģʽ��ȫ�ԡ�Һ���鿴��������ʾ���Զ�����*/
   uchar8  Screen;	                 /*��ʾ��ʶ���ж�Ӧ������,��ǰ��ʾ�ڼ���,��ѭ�ԡ����Եڼ���*/
   uchar8  ParaNum;	                 /*���ݱ�ʾ�����,��ʾ�����е����,�ñ�ʶ���Ӧ�ڼ��� */
   uchar8  ParityTimer;              /*��ż�Զ�ʱ��*/
}Str_DisplayFlag;		             /*��ʾ��־*/

Str_DisplayFlag GV_Str_DisplayFlag;

#define C_NoOffset          0xFF    /*�ñ�ʶ���Ӧ������ƫ�Ƶ�ַ,���ڷ�������,����ʾ��Ŷ�Ӧ�ߵͲ���,�����ݲ�����*/
                                    /*�෴ʱ(���ݲ����ݴ洢���ֽ���ǰ),���и�ƫ��,������ʱ��\���\ͨ�ŵ�ַ�ȡ�*/
                                    /*����Ҫ���⴦�������,�ɳ�����㣬���ֽ�ΪFF��*/                                    
                                    
#define C_ChineseSignLen    9
const uchar8 GV_ChineseSignEn[][C_ChineseSignLen]=     /*����  ȫ��*/
{	
	{0x00,   0xE0,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й��ܵ���	*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����1		*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����2		*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����3		*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����4		*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����5		*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����6 	*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����7 	*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����8 	*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����9 	*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����10	*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����11	*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����12	*/

	{0x00,   0xE0,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й��ܾ�ȷ����        */
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����1��ȷ����		*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����2��ȷ����		*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����3��ȷ����		*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����4��ȷ����		*/	
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����5��ȷ����		*/	
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����6��ȷ����		*/	
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����7��ȷ����		*/	
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����8��ȷ����		*/	
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����9��ȷ����		*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����10��ȷ����	*/	
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����11��ȷ����	*/	
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����12��ȷ����	*/	

	{0x00,   0xE0,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�������β��        */
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����1����β��		*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����2����β��		*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����3����β��		*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����4����β��		*/	
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����5����β��		*/	
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����6����β��		*/	
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����7����β��		*/	
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����8����β��		*/	
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����9����β��		*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����10����β��	*/	
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����11����β��	*/	
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����й�����12����β��	*/	

	
	{0x06,   0xE0,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*�����й��ܵ���	*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*�����й�����1		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*�����й�����2		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*�����й�����3		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*�����й�����4		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*�����й�����5		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*�����й�����6   	*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*�����й�����7   	*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*�����й�����8   	*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*�����й�����9   	*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*�����й�����10  	*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*�����й�����11  	*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*�����й�����12  	*/

	{0x06,   0xE0,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*�����й��ܾ�ȷ����*///
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*�����й�����1��ȷ����		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*�����й�����2��ȷ����		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*�����й�����3��ȷ����		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*�����й�����4��ȷ����		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*�����й�����5��ȷ����		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*�����й�����6��ȷ����		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*�����й�����7��ȷ����		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*�����й�����8��ȷ����		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*�����й�����9��ȷ����		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*�����й�����10��ȷ����	*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*�����й�����11��ȷ����	*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*�����й�����12��ȷ����	*/

	{0x06,   0xE0,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*�����й�������β��		*/  
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*�����й�����1����β��		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*�����й�����2����β��		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*�����й�����3����β��		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*�����й�����4����β��		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*�����й�����5����β��		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*�����й�����6����β��		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*�����й�����7����β��		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*�����й�����8����β��		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*�����й�����9����β��		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*�����й�����10����β��  	*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*�����й�����11����β��  	*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*�����й�����12����β��  	*/


	{0x06,   0xC0,  0x80,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*A�����й�����	*/
	{0x06,   0xC0,  0x80,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*A�����й����� ��ȷ����*/
	{0x06,   0xC0,  0x80,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*A�����й����� ����β��*/
		
	{0x06,   0xC0,  0x40,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*B�����й�����	*/
	{0x06,   0xC0,  0x40,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*B�����й����� ��ȷ����*/	
	{0x06,   0xC0,  0x40,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*B�����й����� ����β��*/	
	
	
	{0x06,   0xC0,  0x20,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*C�����й�����*/
	{0x06,   0xC0,  0x20,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*C�����й����� ��ȷ����*/	
	{0x06,   0xC0,  0x20,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*C�����й����� ����β��*/	
	
	{0x0A,   0xE0,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*�����й��ܵ���	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*�����й�����1		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*�����й�����2		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*�����й�����3		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*�����й�����4		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*�����й�����5		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*�����й�����6   	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*�����й�����7   	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*�����й�����8   	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*�����й�����9   	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*�����й�����10  	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*�����й�����11  	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*�����й�����12  	*/

	{0x0A,   0xE0,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*�����й��ܾ�ȷ����		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*�����й�����1��ȷ����		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*�����й�����2��ȷ����		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*�����й�����3��ȷ����		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*�����й�����4��ȷ����		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*�����й�����5��ȷ����		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*�����й�����6��ȷ����   	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*�����й�����7��ȷ����   	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*�����й�����8��ȷ����   	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*�����й�����9��ȷ����   	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*�����й�����10��ȷ����  	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*�����й�����11��ȷ����  	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*�����й�����12��ȷ����  	*/

	{0x0A,   0xE0,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*�����й�������β��		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*�����й�����1����β��		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*�����й�����2����β��		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*�����й�����3����β��		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*�����й�����4����β��		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*�����й�����5����β��		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*�����й�����6����β��   	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*�����й�����7����β��   	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*�����й�����8����β��   	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*�����й�����9����β��   	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*�����й�����10����β��  	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*�����й�����11����β��  	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*�����й�����12����β��  	*/

	{0x0A,   0xC0,  0x80,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*A�����й�����	*/
	{0x0A,   0xC0,  0x80,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*A�����й����� ��ȷ����*/	
	{0x0A,   0xC0,  0x80,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*A�����й����� ����β��*/	
	
	{0x0A,   0xC0,  0x40,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*B�����й�����	*/
	{0x0A,   0xC0,  0x40,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*B�����й����� ��ȷ����*/	
	{0x0A,   0xC0,  0x40,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*B�����й����� ����β��*/	
	
	{0x0A,   0xC0,  0x20,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*C�����й�����	*/	
	{0x0A,   0xC0,  0x20,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*C�����й����� ��ȷ����*/	
	{0x0A,   0xC0,  0x20,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*C�����й����� ����β��*/	
	
    
	{0x11,   0x60,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1�ܵ���		*/
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����1		*/
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����2		*/
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����3		*/
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����4		*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����5		*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����6  		*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����7  		*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����8  		*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����9  		*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����10 		*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����11 		*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����12 		*/ 

	{0x11,   0x60,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1�ܾ�ȷ����		*/
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����1��ȷ����	*/
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����2��ȷ����	*/
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����3��ȷ����	*/
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����4��ȷ����	*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����5��ȷ����	*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����6��ȷ����  	*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����7��ȷ����  	*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����8��ȷ����  	*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����9��ȷ����  	*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����10��ȷ����	*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����11��ȷ����	*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����12��ȷ����	*/ 

	{0x11,   0x60,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1������β��		*/
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����1����β��	*/
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����2����β��	*/
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����3����β��	*/
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����4����β��	*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����5����β��	*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����6����β��  	*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����7����β��  	*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����8����β��  	*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����9����β��  	*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����10����β��	*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����11����β��	*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�1����12����β��	*/ 

	{0x11,   0x40,  0x80,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*A����޹�1����	  */
	{0x11,   0x40,  0x80,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*A����޹�1���� ��ȷ����*/
	{0x11,   0x40,  0x80,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*A����޹�1���� ����β��*/
	
	{0x11,   0x40,  0x40,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*B����޹�1����	  */	
	{0x11,   0x40,  0x40,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*B����޹�1���� ��ȷ����*/ 
	{0x11,   0x40,  0x40,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*B����޹�1���� ����β��*/ 
	
	{0x11,   0x40,  0x20,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*C����޹�1����	  */	
	{0x11,   0x40,  0x20,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*C����޹�1���� ��ȷ����*/
	{0x11,   0x40,  0x20,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*C����޹�1���� ����β��*/
	
	
	{0x11,   0x60,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2�ܵ���		*/
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����1		*/
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����2		*/
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����3		*/
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����4		*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����5		*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����6  	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����7  	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����8  	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����9  	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����10 	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����11 	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����12 	*/  

	{0x11,   0x60,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2�ܾ�ȷ����		*/
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����1	��ȷ����	*/
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����2	��ȷ����	*/
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����3	��ȷ����	*/
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����4	��ȷ����	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����5	��ȷ����	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����6  ��ȷ����	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����7  ��ȷ����	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����8  ��ȷ����	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����9  ��ȷ����	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����10 ��ȷ����	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����11 ��ȷ����	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����12 ��ȷ����	*/  

	{0x11,   0x60,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2������β��		*/
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����1	����β��	*/
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����2	����β��	*/
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����3	����β��	*/
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����4	����β��	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����5	����β��	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����6  ����β��	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����7  ����β��	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����8  ����β��	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����9  ����β��	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����10 ����β��	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����11 ����β��	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*����޹�2����12 ����β��	*/  
	
	{0x11,   0x40,  0x80,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*A����޹�2����	  */
	{0x11,   0x40,  0x80,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*A�����й����� ��ȷ����*/ 
	{0x11,   0x40,  0x80,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*A�����й����� ����β��*/ 
	
	{0x11,   0x40,  0x40,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*B����޹�2����	  */	
	{0x11,   0x40,  0x40,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*B�����й����� ��ȷ����*/	
	{0x11,   0x40,  0x40,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*B�����й����� ����β��*/	
	
	{0x11,   0x40,  0x20,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*C����޹�2����	  */	
	{0x11,   0x40,  0x20,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*C�����й����� ��ȷ����*/
	{0x11,   0x40,  0x20,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*C�����й����� ����β��*/
	
	{0x01,   0x60,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*һ�����޹��ܵ���	*/
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*һ�����޹�����1		*/
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*һ�����޹�����2		*/
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*һ�����޹�����3		*/
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*һ�����޹�����4		*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*һ�����޹�����5	 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*һ�����޹�����6  	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*һ�����޹�����7  	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*һ�����޹�����8  	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*һ�����޹�����9  	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*һ�����޹�����10 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*һ�����޹�����11 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*һ�����޹�����12 	*/   

	{0x01,   0x60,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*һ�����޹��ܾ�ȷ����	*/
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*һ�����޹�����1	��ȷ����	*/
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*һ�����޹�����2	��ȷ����	*/
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*һ�����޹�����3	��ȷ����	*/
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*һ�����޹�����4	��ȷ����	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*һ�����޹�����5	��ȷ���� 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*һ�����޹�����6 ��ȷ���� 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*һ�����޹�����7 ��ȷ���� 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*һ�����޹�����8 ��ȷ���� 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*һ�����޹�����9 ��ȷ���� 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*һ�����޹�����10��ȷ���� 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*һ�����޹�����11��ȷ���� 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*һ�����޹�����12��ȷ���� 	*/   

	{0x01,   0x60,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*һ�����޹�������β��	*/
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*һ�����޹�����1	����β��	*/
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*һ�����޹�����2	����β��	*/
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*һ�����޹�����3	����β��	*/
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*һ�����޹�����4	����β��	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*һ�����޹�����5	����β�� 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*һ�����޹�����6 ����β�� 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*һ�����޹�����7 ����β�� 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*һ�����޹�����8 ����β�� 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*һ�����޹�����9 ����β�� 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*һ�����޹�����10����β�� 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*һ�����޹�����11����β�� 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*һ�����޹�����12����β�� 	*/   
	
	{0x01,   0x40,  0x80,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*Aһ�����޹�����	  */	
	{0x01,   0x40,  0x80,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*Aһ�����޹�����	 ��ȷ����*/
	{0x01,   0x40,  0x80,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*Aһ�����޹�����	 ����β��*/
	
	{0x01,   0x40,  0x40,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*Bһ�����޹�����	  */
	{0x01,   0x40,  0x40,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*Bһ�����޹�����	 ��ȷ����*/
	{0x01,   0x40,  0x40,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*Bһ�����޹�����	 ����β��*/

	{0x01,   0x40,  0x20,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*Cһ�����޹�����	  */
	{0x01,   0x40,  0x20,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*Cһ�����޹�����	 ��ȷ����*/
	{0x01,   0x40,  0x20,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*Cһ�����޹�����	 ����β��*/
	

	{0x01,   0x60,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹��ܵ���	*/
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����1		*/
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����2		*/
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����3		*/
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����4		*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����5	 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����6  	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����7  	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����8  	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����9  	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����10 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����11 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����12 	*/ 

	{0x01,   0x60,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹��ܾ�ȷ����	*/
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����1	��ȷ����	*/
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����2	��ȷ����	*/
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����3	��ȷ����	*/
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����4	��ȷ����	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����5	��ȷ���� 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����6 ��ȷ���� 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����7 ��ȷ���� 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����8 ��ȷ���� 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����9 ��ȷ���� 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����10��ȷ���� 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����11��ȷ���� 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����12��ȷ���� 	*/ 

	{0x01,   0x60,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�������β��	*/
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����1	����β��	*/
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����2	����β��	*/
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����3	����β��	*/
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����4	����β��	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����5	����β�� 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����6 ����β�� 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����7 ����β�� 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����8 ����β�� 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����9 ����β�� 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����10����β�� 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����11����β�� 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����12����β�� 	*/ 
	
	{0x01,   0x40,  0x80,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*A�������޹�����	  */
	{0x01,   0x40,  0x80,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*Aһ�����޹�����	 ��ȷ����*/
	{0x01,   0x40,  0x80,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*Aһ�����޹�����	 ����β��*/

	
	{0x01,   0x40,  0x40,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*B�������޹�����	  */
	{0x01,   0x40,  0x40,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*Bһ�����޹�����	 ��ȷ����*/
	{0x01,   0x40,  0x40,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*Bһ�����޹�����	 ����β��*/

	{0x01,   0x40,  0x20,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*C�������޹�����	  */
	{0x01,   0x40,  0x20,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*Cһ�����޹�����	 ��ȷ����*/
	{0x01,   0x40,  0x20,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*Cһ�����޹�����	 ����β��*/
	

	{0x01,   0x60,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹��ܵ���  */
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����1		*/  
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����2		*/  
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����3		*/  
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����4		*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����5	 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����6  	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����7  	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����8  	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����9  	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����10 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����11 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����12 	*/

	{0x01,   0x60,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹��ܾ�ȷ����  */
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����1	��ȷ����	*/  
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����2	��ȷ����	*/  
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����3	��ȷ����	*/  
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����4	��ȷ����	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����5	��ȷ���� 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����6 ��ȷ���� 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����7 ��ȷ���� 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����8 ��ȷ���� 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����9 ��ȷ���� 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����10��ȷ���� 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����11��ȷ���� 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����12��ȷ���� 	*/

	{0x01,   0x60,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�������β��  */
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����1	����β��	*/  
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����2	����β��	*/  
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����3	����β��	*/  
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����4	����β��	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����5	����β�� 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����6 ����β�� 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����7 ����β�� 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����8 ����β�� 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����9 ����β�� 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����10����β�� 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����11����β�� 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����12����β�� 	*/
	
	{0x01,   0x40,  0x80,  0x60,  0x0C,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*A�������޹�����	  */
	{0x01,   0x40,  0x80,  0x60,  0x0C,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*Aһ�����޹�����	 ��ȷ����*/
	{0x01,   0x40,  0x80,  0x60,  0x0C,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*Aһ�����޹�����	 ����β��*/
	
	{0x01,   0x40,  0x40,  0x60,  0x0C,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*B�������޹�����	  */
	{0x01,   0x40,  0x40,  0x60,  0x0C,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*Bһ�����޹�����	 ��ȷ����*/
	{0x01,   0x40,  0x40,  0x60,  0x0C,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*Bһ�����޹�����	 ����β��*/
	
	{0x01,   0x40,  0x20,  0x60,  0x0C,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*C�������޹�����	  */	
	{0x01,   0x40,  0x20,  0x60,  0x0C,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*Cһ�����޹�����	 ��ȷ����*/
	{0x01,   0x40,  0x20,  0x60,  0x0C,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*Cһ�����޹�����	 ����β��*/

	{0x01,   0x60,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹��ܵ���  */
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����1		*/  
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����2		*/  
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����3		*/  
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����4		*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����5	 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����6  	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����7  	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����8  	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����9  	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����10 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����11 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*�������޹�����12 	*/

	{0x01,   0x60,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹��ܾ�ȷ����  */
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����1	��ȷ����	*/  
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����2	��ȷ����	*/  
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����3	��ȷ����	*/  
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����4	��ȷ����	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����5	��ȷ���� 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����6 ��ȷ���� 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����7 ��ȷ���� 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����8 ��ȷ���� 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����9 ��ȷ���� 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����10��ȷ���� 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����11��ȷ���� 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*�������޹�����12��ȷ���� 	*/

	{0x01,   0x60,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�������β��  */
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����1	����β��*/  
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����2	����β��	*/  
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����3	����β��	*/  
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����4	����β��	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����5	����β�� 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����6 ����β�� 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����7 ����β�� 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����8 ����β�� 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����9 ����β�� 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����10����β�� 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����11����β�� 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*�������޹�����12����β�� 	*/
	                                                                                                                                 
	{0x01,   0x40,  0x80,  0x60,  0x09,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*A�������޹�����	  */	
	{0x01,   0x40,  0x80,  0x60,  0x09,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*Aһ�����޹�����	 ��ȷ����*/
	{0x01,   0x40,  0x80,  0x60,  0x09,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*Aһ�����޹�����	 ����β��*/
	
	{0x01,   0x40,  0x40,  0x60,  0x09,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*B�������޹�����	  */	
	{0x01,   0x40,  0x40,  0x60,  0x09,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*Bһ�����޹�����	 ��ȷ����*/
	{0x01,   0x40,  0x40,  0x60,  0x09,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*Bһ�����޹�����	 ����β��*/
	
	{0x01,   0x40,  0x20,  0x60,  0x09,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*C�������޹�����	  */	
	{0x01,   0x40,  0x20,  0x60,  0x09,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*Cһ�����޹�����	 ��ȷ����*/
	{0x01,   0x40,  0x20,  0x60,  0x09,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*Cһ�����޹�����	 ����β��*/
};
#define GV_ChineseSignEn_Len (sizeof(GV_ChineseSignEn)/C_ChineseSignLen) 

const uchar8 GV_ChineseSignDe[][C_ChineseSignLen]=     /*����  ȫ��*/
{	
	{0x06,   0xE0,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*�����й���    */
	{0x06,   0xE0,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          */
	{0x06,   0xE0,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          */
	{0x06,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*�����й�����1	*/
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          */
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          */
	{0x06,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*�����й�����2	*/
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          */
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          */
	{0x06,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*�����й�����3	*/
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          */
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          */
	{0x06,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*�����й�����4	*/ 
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          */
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          */
	{0x06,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*�����й�����5	*/ 
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          */
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          */
	{0x06,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*�����й�����6	*/ 
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          */
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          */
	{0x06,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*�����й�����7	*/ 
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          */
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          */
	{0x06,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*�����й�����8	*/ 
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          */
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          */
	{0x06,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*�����й�����9	*/ 
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          */
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          */
	{0x06,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*�����й�����10*/ 
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          */
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          */
	{0x06,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*�����й�����11*/ 
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          */
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          */
	{0x06,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*�����й�����12*/ 	
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          */
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          */
	
	{0x0A,   0xE0,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*�����й���    */
	{0x0A,   0xE0,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          */
	{0x0A,   0xE0,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*�����й�����1	*/
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*�����й�����2	*/
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*�����й�����3	*/
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*�����й�����4	*/
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*�����й�����5	*/
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*�����й�����6	*/
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*�����й�����7	*/
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*�����й�����8	*/
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*�����й�����9	*/
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*�����й�����10*/
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*�����й�����11*/
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*�����й�����12*/
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          */
	
	{0x11,   0x60,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*����޹�1��   */    
	{0x11,   0x60,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x11,   0x60,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*����޹�1����1*/
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*����޹�1����2*/
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*����޹�1����3*/
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*����޹�1����4*/	
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*����޹�1����5*/	
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*����޹�1����6*/	
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*����޹�1����7*/	
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*����޹�1����8*/	
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*����޹�1����9*/	
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*����޹�1����10*/	
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*����޹�1����11*/	
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*����޹�1����12*/	
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	
	{0x11,   0x60,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*����޹�2��	*/
	{0x11,   0x60,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x11,   0x60,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*����޹�2����1*/
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*����޹�2����2*/
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*����޹�2����3*/
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*����޹�2����4*/     	
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*����޹�2����5*/     	
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*����޹�2����6*/     	
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*����޹�2����7*/     	
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*����޹�2����8*/     	
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*����޹�2����9*/     	
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*����޹�2����10*/     	
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*����޹�2����11*/     	
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*����޹�2����12*/     	
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	
	{0x01,   0x60,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*һ�����޹���	        */
	{0x01,   0x60,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x60,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*һ�����޹�����1		*/
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*һ�����޹�����2		*/
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*һ�����޹�����3		*/
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*һ�����޹�����4		*/	
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*һ�����޹�����5		*/	
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*һ�����޹�����6		*/	
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*һ�����޹�����7		*/	
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*һ�����޹�����8		*/	
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*һ�����޹�����9		*/	
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*һ�����޹�����10		*/	
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*һ�����޹�����11		*/	
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*һ�����޹�����12		*/	
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	
	{0x01,   0x60,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹���	        */
	{0x01,   0x60,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x60,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����1		*/
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����2		*/
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����3		*/
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����4		*/ 	
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����5		*/ 	
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����6		*/ 	
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����7		*/ 	
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����8		*/ 	
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����9		*/ 	
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����10	    */ 	
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����11	    */ 	
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����12	    */ 	
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	
	{0x01,   0x60,  0x00,  0xA0,  0x0C,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹���          */
	{0x01,   0x60,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x60,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x0C,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����1		*/  
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x0C,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����2		*/  
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x0C,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����3		*/  
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x0C,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����4		*/  	                                                                                               
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x0C,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����5		*/  	                                                                                               
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x0C,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����6		*/  	                                                                                               
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x0C,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����7		*/  	                                                                                               
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x0C,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����8		*/  	                                                                                               
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x0C,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����9		*/  	                                                                                               
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x0C,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����10	    */  	                                                                                               
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x0C,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����11	    */  	                                                                                               
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x0C,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����12	    */  	                                                                                               
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	
	{0x01,   0x60,  0x00,  0xA0,  0x09,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹��ܵ���      */
	{0x01,   0x60,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x60,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x09,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����1		*/  
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x09,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����2		*/  
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x09,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����3		*/  
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x09,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����4		*/   	
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x09,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����5		*/   	
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x09,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����6		*/   	
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x09,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����7		*/   	
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x09,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����8		*/   	
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x09,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����9		*/   	
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x09,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����10	    */   	
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x09,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����11	    */   	
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x09,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*�������޹�����12	    */   	
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	
	{0x06,   0xC0,  0x80,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*A�����й�		        */	
	{0x06,   0xC0,  0x80,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x06,   0xC0,  0x80,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x0A,   0xC0,  0x80,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*A�����й�		        */	
	{0x0A,   0xC0,  0x80,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x0A,   0xC0,  0x80,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x11,   0x40,  0x80,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*A����޹�1	*/	
	{0x11,   0x40,  0x80,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x11,   0x40,  0x80,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x11,   0x40,  0x80,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*A����޹�2	*/	
	{0x11,   0x40,  0x80,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x11,   0x40,  0x80,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x01,   0x40,  0x80,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*Aһ�����޹�	        */	
	{0x01,   0x40,  0x80,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x40,  0x80,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x01,   0x40,  0x80,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*A�������޹�	        */	
	{0x01,   0x40,  0x80,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x40,  0x80,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x01,   0x40,  0x80,  0xA0,  0x0C,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*A�������޹�	        */	
	{0x01,   0x40,  0x80,  0xA0,  0x6C,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x40,  0x80,  0xA0,  0x6C,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x01,   0x40,  0x80,  0xA0,  0x09,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*A�������޹�	        */	
	{0x01,   0x40,  0x80,  0xA0,  0x69,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x40,  0x80,  0xA0,  0x69,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x06,   0xC0,  0x40,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*B�����й�		        */	
	{0x06,   0xC0,  0x40,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x06,   0xC0,  0x40,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x0A,   0xC0,  0x40,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*B�����й�		        */	
	{0x0A,   0xC0,  0x40,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x0A,   0xC0,  0x40,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x11,   0x40,  0x40,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*B����޹�1	  */	
	{0x11,   0x40,  0x40,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x11,   0x40,  0x40,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x11,   0x40,  0x40,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*B����޹�2	  */	
	{0x11,   0x40,  0x40,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x11,   0x40,  0x40,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x01,   0x40,  0x40,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*Bһ�����޹�	        */	
	{0x01,   0x40,  0x40,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x40,  0x40,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x01,   0x40,  0x40,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*B�������޹�	        */	
	{0x01,   0x40,  0x40,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x40,  0x40,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x01,   0x40,  0x40,  0xA0,  0x0C,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*B�������޹�	        */	
	{0x01,   0x40,  0x40,  0xA0,  0x6C,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x40,  0x40,  0xA0,  0x6C,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x01,   0x40,  0x40,  0xA0,  0x09,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*B�������޹�	        */	
	{0x01,   0x40,  0x40,  0xA0,  0x69,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x40,  0x40,  0xA0,  0x69,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x06,   0xC0,  0x20,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*C�����й�		        */	
	{0x06,   0xC0,  0x20,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x06,   0xC0,  0x20,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x0A,   0xC0,  0x20,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*C�����й�		        */	
	{0x0A,   0xC0,  0x20,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x0A,   0xC0,  0x20,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x11,   0x40,  0x20,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*C����޹�1	  */	
	{0x11,   0x40,  0x20,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x11,   0x40,  0x20,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x11,   0x40,  0x20,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*C����޹�2	  */	
	{0x11,   0x40,  0x20,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x11,   0x40,  0x20,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x01,   0x40,  0x20,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*Cһ�����޹�	        */	
	{0x01,   0x40,  0x20,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x40,  0x20,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x01,   0x40,  0x20,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*C�������޹�           */	
	{0x01,   0x40,  0x20,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x40,  0x20,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x01,   0x40,  0x20,  0xA0,  0x0C,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*C�������޹�	        */	
	{0x01,   0x40,  0x20,  0xA0,  0x6C,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x40,  0x20,  0xA0,  0x6C,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
	{0x01,   0x40,  0x20,  0xA0,  0x09,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*C�������޹�           */	
	{0x01,   0x40,  0x20,  0xA0,  0x69,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*����          		*/
	{0x01,   0x40,  0x20,  0xA0,  0x69,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*ʱ��          		*/
};
#define GV_ChineseSignDe_Len (sizeof(GV_ChineseSignDe)/C_ChineseSignLen) 

const uchar8 GV_ChineseSignFr[][C_ChineseSignLen]=     /*���� ȫ��*/
{	
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo+C_NeedDataChange,          C_5P7PDot,            0xA4,    0x02      },	/*���� */
};                                                                                 
#define GV_ChineseSignFr_Len (sizeof(GV_ChineseSignFr)/C_ChineseSignLen)           


const uchar8 GV_ChineseSignPort[][C_ChineseSignLen]=     /*��������ӿ�*/
{	
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo+C_NoNeedChange,          0x00,                 0x23,     0},	/*��1·485*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo+C_NoNeedChange,          0x00,                 0x23,     0},	/*��1·485*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo+C_NoNeedChange,          0x00,                 0x23,     0},	/*��2·485*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo+C_NoNeedChange,          0x00,                 0x23,     0},	/*��2·485*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo+C_NoNeedChange,          0x00,                 0x23,     0},	/*�ز�*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo+C_NoNeedChange,          0x00,                 0x23,     0},	/*�ز�*/

};
#define GV_ChineseSignPort_Len (sizeof(GV_ChineseSignPort)/C_ChineseSignLen)           

const uchar8 GV_ChineseSignEv30[][C_ChineseSignLen]=     /*�¼���¼10  */
{	
/*ʧѹ�¼�*/
	{0x00,   0x00,  0x00,  0x42,  0x00,  C_DisVNum,        0x01,                 0x42,     C_NoOffset},	/*ʧѹ�¼���ѹ��������*/
	{0x00,   0x00,  0x00,  0x42,  0x00,  C_DisVNum,        0x01,                 0x42,     C_NoOffset},	/*ʧѹ�¼���ѹ�ָ�����*/
	{0x00,   0x00,  0x00,  0x41,  0x00,  C_DisANum,        0x04,                 0x24,     C_NoOffset},	/*ʧѹ�¼�������������*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*ʧѹ�¼��ж���ʱʱ��*/
	{0x00,   0x20,  0x00,  0x06,  0x00,  C_DisNo,          0,                    0x04,     C_NoOffset},	/*��ʧѹ�ܴ���*/
	{0x00,   0x20,  0x00,  0x06,  0x60,  C_DisNo,          0,                    0x04,     0x04},	    /*��ʧѹ���ۼ�ʱ��	*/
	{0x00,   0x20,  0x80,  0x06,  0x00,  C_DisNo,          0,                    0x04,     C_NoOffset},	/*Aʧѹ�ܴ���*/
	{0x00,   0x20,  0x80,  0x06,  0x60,  C_DisNo,          0,                    0x04,     0x04},	    /*Aʧѹ���ۼ�ʱ��	*/
	{0x00,   0x20,  0x40,  0x06,  0x00,  C_DisNo,          0,                    0x04,     C_NoOffset},	/*Bʧѹ�ܴ���*/
	{0x00,   0x20,  0x40,  0x06,  0x60,  C_DisNo,          0,                    0x04,     0x04},	    /*Bʧѹ���ۼ�ʱ��	*/
	{0x00,   0x20,  0x20,  0x06,  0x00,  C_DisNo,          0,                    0x04,     C_NoOffset},	/*Cʧѹ�ܴ���*/
	{0x00,   0x20,  0x20,  0x06,  0x60,  C_DisNo,          0,                    0x04,     0x04},	    /*Cʧѹ���ۼ�ʱ��	*/
	{0x00,   0x20,  0x00,  0x06,  0x00,  C_DisNo,          0,                    0x04,     C_NoOffset},	/*ʧѹ�ܴ���*/
	{0x00,   0x20,  0x00,  0x06,  0x60,  C_DisNo,          0,                    0x04,     C_NoOffset},	/*ʧѹ���ۼ�ʱ��	*/
	{0x40,   0x00,  0x00,  0x06,  0x60,  C_DisNo+C_NeedDataChange,               C_5P7PDot,            0xA4,    0x03      },	/*���1��ʧѹ��������*/
	{0x40,   0x00,  0x00,  0x06,  0x60,  C_DisNo+C_NeedSingleByteChange,         C_CoL2CoL15P7PDot,    0xA3,    0x00      },	/*���1��ʧѹ����ʱ��*/
	{0x40,   0x00,  0x00,  0x06,  0x60,  C_DisNo+C_NeedDataChange,               C_5P7PDot,            0xA4,    0x03      },	/*���1��ʧѹ��������*/
	{0x40,   0x00,  0x00,  0x06,  0x60,  C_DisNo+C_NeedSingleByteChange,         C_CoL2CoL15P7PDot,    0xA3,    0x00      },	/*���1��ʧѹ����ʱ��*/
	{0x40,   0x20,  0x00,  0x06,  0x60,  C_DisNo+C_NeedDataChange,               C_5P7PDot,            0xA4,    0x03      },	/*���1��ʧѹ��������*/
	{0x40,   0x20,  0x00,  0x06,  0x60,  C_DisNo+C_NeedSingleByteChange,         C_CoL2CoL15P7PDot,    0xA3,    0         },	/*���1��ʧѹ����ʱ��*/
	{0x40,   0x20,  0x00,  0x06,  0x60,  C_DisNo+C_NeedDataChange,               C_5P7PDot,            0xA4,    0x0A      },	/*���1��ʧѹ��������*/
	{0x40,   0x20,  0x00,  0x06,  0x60,  C_DisNo+C_NeedSingleByteChange,         C_CoL2CoL15P7PDot,    0xA3,    0x07      },	/*���1��ʧѹ����ʱ��*/
	{0x40,   0x00,  0x80,  0x06,  0x60,  C_DisNo+C_NeedDataChange,               C_5P7PDot,            0xA4,    0x03      },	/*A���1��ʧѹ��������*/
	{0x40,   0x00,  0x80,  0x06,  0x60,  C_DisNo+C_NeedSingleByteChange,         C_CoL2CoL15P7PDot,    0xA3,    0         },	/*A���1��ʧѹ����ʱ��*/
	{0x40,   0x00,  0x80,  0x06,  0x60,  C_DisNo+C_NeedDataChange,               C_5P7PDot,            0xA4,    0x0A      },	/*A���1��ʧѹ��������*/
	{0x40,   0x00,  0x80,  0x06,  0x60,  C_DisNo+C_NeedSingleByteChange,         C_CoL2CoL15P7PDot,    0xA3,    0x07      },	/*A���1��ʧѹ����ʱ��*/
	{0x40,   0x00,  0x40,  0x06,  0x60,  C_DisNo+C_NeedDataChange,               C_5P7PDot,            0xA4,    0x03      },	/*B���1��ʧѹ��������*/
	{0x40,   0x00,  0x40,  0x06,  0x60,  C_DisNo+C_NeedSingleByteChange,         C_CoL2CoL15P7PDot,    0xA3,    0         },	/*B���1��ʧѹ����ʱ��*/
	{0x40,   0x00,  0x40,  0x06,  0x60,  C_DisNo+C_NeedDataChange,               C_5P7PDot,            0xA4,    0x0A      },	/*B���1��ʧѹ��������*/
	{0x40,   0x00,  0x40,  0x06,  0x60,  C_DisNo+C_NeedSingleByteChange,         C_CoL2CoL15P7PDot,    0xA3,    0x07      },	/*B���1��ʧѹ����ʱ��*/
	{0x40,   0x00,  0x20,  0x06,  0x60,  C_DisNo+C_NeedDataChange,               C_5P7PDot,            0xA4,    0x03      },	/*C���1��ʧѹ��������*/
	{0x40,   0x00,  0x20,  0x06,  0x60,  C_DisNo+C_NeedSingleByteChange,         C_CoL2CoL15P7PDot,    0xA3,    0         },	/*C���1��ʧѹ����ʱ��*/
	{0x40,   0x00,  0x20,  0x06,  0x60,  C_DisNo+C_NeedDataChange,               C_5P7PDot,            0xA4,    0x0A      },	/*C���1��ʧѹ��������*/
	{0x40,   0x00,  0x20,  0x06,  0x60,  C_DisNo+C_NeedSingleByteChange,         C_CoL2CoL15P7PDot,    0xA3,    0x07      },	/*C���1��ʧѹ����ʱ��*/
/*Ƿѹ�¼�*/
	{0x00,   0x00,  0x00,  0x42,  0x00,  C_DisVNum,        0x01,                 0x42,     C_NoOffset},	/*Ƿѹ�¼���ѹ��������*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*Ƿѹ�¼��ж���ʱʱ��*/
	/*{0x00,   0x20,  0x00,  0x06,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},*/	/*��ʧѹ�ܴ���*/
	/*{0x00,   0x20,  0x00,  0x06,  0x60,  C_DisNo,          0,                    0x04,    0x04},*/	/*��ʧѹ���ۼ�ʱ��	*/
	{0x00,   0x00,  0x80,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*Aʧѹ�ܴ���*/
	{0x00,   0x00,  0x80,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*Aʧѹ���ۼ�ʱ��	*/
	{0x00,   0x00,  0x40,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*Bʧѹ�ܴ���*/
	{0x00,   0x00,  0x40,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*Bʧѹ���ۼ�ʱ��	*/
	{0x00,   0x00,  0x20,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*Cʧѹ�ܴ���*/
	{0x00,   0x00,  0x20,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*Cʧѹ���ۼ�ʱ��	*/
/*��ѹ�¼�*/
	{0x00,   0x00,  0x00,  0x42,  0x00,  C_DisVNum,        0x01,                 0x42,     C_NoOffset},	/*��ѹ�¼���ѹ��������*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*��ѹʱ���ж���ʱʱ��*/
	/*{0x00,   0x20,  0x00,  0x06,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},*/	/*�ܹ�ѹ�ܴ���*/
	/*{0x00,   0x20,  0x00,  0x06,  0x60,  C_DisNo,          0,                    0x04,    C_NoOffset},*/	/*�ܹ�ѹ���ۼ�ʱ��	*/
	{0x00,   0x00,  0x80,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*A��ѹ�ܴ���*/
	{0x00,   0x00,  0x80,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*A��ѹ���ۼ�ʱ��	*/
	{0x00,   0x00,  0x40,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*B��ѹ�ܴ���*/
	{0x00,   0x00,  0x40,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*B��ѹ���ۼ�ʱ��	*/
	{0x00,   0x00,  0x20,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*C��ѹ�ܴ���*/
	{0x00,   0x00,  0x20,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*C��ѹ���ۼ�ʱ��	*/
/*�����¼�*/
	{0x00,   0x00,  0x00,  0x42,  0x00,  C_DisVNum,        0x01,                 0x42,     C_NoOffset},	/*�����¼���ѹ��������*/
	{0x00,   0x00,  0x00,  0x41,  0x00,  C_DisANum,        0x04,                 0x24,     C_NoOffset},	/*�����¼�������������*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*�����¼��ж���ʱʱ��*/
	/*{0x00,   0x20,  0x00,  0x06,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},*/	/*�ܹ�ѹ�ܴ���*/
	/*{0x00,   0x20,  0x00,  0x06,  0x60,  C_DisNo,          0,                    0x04,    0x04},*/	/*�ܹ�ѹ���ۼ�ʱ��	*/
	{0x00,   0x00,  0x80,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*A��ѹ�ܴ���*/
	{0x00,   0x00,  0x80,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*A��ѹ���ۼ�ʱ��	*/
	{0x00,   0x00,  0x40,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*B��ѹ�ܴ���*/
	{0x00,   0x00,  0x40,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*B��ѹ���ۼ�ʱ��	*/
	{0x00,   0x00,  0x20,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*C��ѹ�ܴ���*/
	{0x00,   0x00,  0x20,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*C��ѹ���ۼ�ʱ��	*/
/*ʧ���¼�*/
	{0x00,   0x00,  0x00,  0x42,  0x00,  C_DisVNum,        0x01,                 0x42,     C_NoOffset},	/*ʧ���¼���ѹ��������*/
	{0x00,   0x00,  0x00,  0x41,  0x00,  C_DisANum,        0x04,                 0x24,     C_NoOffset},	/*ʧ���¼�������������*/
	{0x00,   0x00,  0x00,  0x41,  0x00,  C_DisANum,        0x04,                 0x24,     C_NoOffset},	/*ʧ���¼�������������*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*ʧ���¼��ж���ʱʱ��*/
	/*{0x00,   0x20,  0x00,  0x06,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},*/	/*��ʧ���ܴ���*/
	/*{0x00,   0x20,  0x00,  0x06,  0x60,  C_DisNo,          0,                    0x04,    0x04},*/	/*��ʧ�����ۼ�ʱ��	*/
	{0x00,   0x00,  0x80,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*Aʧ���ܴ���*/
	{0x00,   0x00,  0x80,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*Aʧ�����ۼ�ʱ��	*/
	{0x00,   0x00,  0x40,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*Bʧ���ܴ���*/
	{0x00,   0x00,  0x40,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*Bʧ�����ۼ�ʱ��	*/
	{0x00,   0x00,  0x20,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*Cʧ���ܴ���*/
	{0x00,   0x00,  0x20,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*Cʧ�����ۼ�ʱ��	*/
/*�����¼�*/
	{0x00,   0x00,  0x00,  0x41,  0x00,  C_DisANum,        0x04,                 0x44,     C_NoOffset},	/*�����¼�������������*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*�����¼��ж���ʱʱ��*/
	/*{0x00,   0x20,  0x00,  0x06,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},*/	/*��ʧ���ܴ���*/
	/*{0x00,   0x20,  0x00,  0x06,  0x60,  C_DisNo,          0,                    0x04,    0x04},*/	/*��ʧ�����ۼ�ʱ��	*/
	{0x00,   0x00,  0x80,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*Aʧ���ܴ���*/
	{0x00,   0x00,  0x80,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*Aʧ�����ۼ�ʱ��	*/
	{0x00,   0x00,  0x40,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*Bʧ���ܴ���*/
	{0x00,   0x00,  0x40,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*Bʧ�����ۼ�ʱ��	*/
	{0x00,   0x00,  0x20,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*Cʧ���ܴ���*/
	{0x00,   0x00,  0x20,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*Cʧ�����ۼ�ʱ��	*/
/*�����¼�*/
	{0x00,   0x00,  0x00,  0x42,  0x00,  C_DisVNum,        0x01,                 0x42,     C_NoOffset},	/*�����¼���ѹ��������*/
	{0x00,   0x00,  0x00,  0x41,  0x00,  C_DisANum,        0x04,                 0x24,     C_NoOffset},	/*�����¼�������������*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*�����¼��ж���ʱʱ��*/
	/*{0x00,   0x20,  0x00,  0x06,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},*/	/*��ʧ���ܴ���*/
	/*{0x00,   0x20,  0x00,  0x06,  0x60,  C_DisNo,          0,                    0x04,    0x04},*/	/*��ʧ�����ۼ�ʱ��	*/
	{0x00,   0x00,  0x80,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*Aʧ���ܴ���*/
	{0x00,   0x00,  0x80,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*Aʧ�����ۼ�ʱ��	*/
	{0x00,   0x00,  0x40,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*Bʧ���ܴ���*/
	{0x00,   0x00,  0x40,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*Bʧ�����ۼ�ʱ��	*/
	{0x00,   0x00,  0x20,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*Cʧ���ܴ���*/
	{0x00,   0x00,  0x20,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*Cʧ�����ۼ�ʱ��	*/
/*���ʷ����¼�*/
	{0x00,   0xC0,  0x00,  0x00,  0x80,  C_DiskWNum,       0x04,                 0x23,     C_NoOffset},	/*���ʷ����¼��й����ʴ�������*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*���ʷ����¼��ж���ʱʱ��*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*�ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*���ۼ�ʱ��	*/
	{0x00,   0x00,	0x80,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*A�ܴ���*/
	{0x00,   0x00,	0x80,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*A���ۼ�ʱ��	*/
	{0x00,   0x00,	0x40,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*B�ܴ���*/
	{0x00,   0x00,	0x40,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*B���ۼ�ʱ��	*/
	{0x00,   0x00,	0x20,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*C�ܴ���*/
	{0x00,   0x00,	0x20,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*C���ۼ�ʱ��	*/
/*�����¼�*/
	{0x00,   0xC0,  0x00,  0x00,  0x80,  C_DisWNum,        0x01,                 0x24,     C_NoOffset},	/*�����¼��й����ʴ�������*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*�����¼��ж���ʱʱ��*/
	/*{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x23,    C_NoOffset},*/	/*���ܴ���*/
	/*{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},*/	/*�����ۼ�ʱ��	*/
	{0x00,  0x00,  0x80,  0x00,  0x00,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*A�ܴ���*/
	{0x00,  0x00,  0x80,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*A���ۼ�ʱ��	*/
	{0x00,  0x00,  0x40,  0x00,  0x00,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*B�ܴ���*/
	{0x00,  0x00,  0x40,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*B���ۼ�ʱ��	*/
	{0x00,  0x00,  0x20,  0x00,  0x00,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*C�ܴ���*/
	{0x00,  0x00,  0x20,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*C���ۼ�ʱ��	*/
/*�����й����������¼�*/
	{0x00,   0xC0,  0x00,  0xA0,  0x00,  C_DiskWNum,       0x04,                 0x24,     C_NoOffset},	/*�����й����������¼�������������*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*���������¼��ж���ʱʱ��*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x01,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*�����й����������¼�*/
	{0x00,   0xC0,  0x00,  0xA0,  0x00,  C_DiskWNum,       0x04,                 0x24,     C_NoOffset},	/*�����й����������¼�������������*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*���������¼��ж���ʱʱ��*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x01,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*�޹����������¼�*/
	{0x01,   0x40,  0x00,  0xA0,  0x00,  C_DiskvarNum,     0x04,                 0x24,     C_NoOffset},	/*�޹����������¼�������������*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*���������¼��ж���ʱʱ��*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*1����*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*1�ۼ�ʱ��	*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*2����*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*2�ۼ�ʱ��	*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*3����*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*3�ۼ�ʱ��	*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*4����*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*4�ۼ�ʱ��	*/
/*�������������¼�*/
	{0x00,   0x20,  0x0C,  0x00,  0x00,  C_DisNo,          0x01,                 0x42,     C_NoOffset},	/*�������������޷�ֵ*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*�������س������ж���ʱʱ��*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*ȫʧѹ�¼�*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*������Դ�����¼�*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*�ж���ʱʱ��*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*��ѹ����������¼�*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*�ж���ʱʱ��*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*��������������¼�*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*�ж���ʱʱ��*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*�����¼�*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*�ж���ʱʱ��*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*����¼�*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*�����¼�*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*���������¼�*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*�¼�����*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*Уʱ�¼�*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*ʱ�α����¼�*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*ʱ�������¼�*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*�����ձ���¼�*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*�����ձ���¼�*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*�����¼�*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*����Ť���¼�*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*��ѹ��ƽ���¼�*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,          0x02,                 0x42,     C_NoOffset},	/*��ѹ��ƽ������ֵ*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*��ѹ��ƽ�����ж���ʱʱ��*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*������ƽ���¼�*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,          0x02,                 0xC2,     C_NoOffset},	/*������ƽ������ֵ*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*������ƽ�����ж���ʱʱ��*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*��բ�¼�*/
	{0x00,   0x20,  0x00, 0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00, 0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00, 0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*��բ�¼�*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*�ڼ����¼�*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*�й���Ϸ�ʽ����¼�*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*�޹���Ϸ�ʽ����¼�*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*���ʱ����¼�*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*���ݱ����¼�*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*��Կ�����¼�*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*�쳣�忨�¼�*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*�����¼�¼�*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*�˷��¼�*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*�ų������¼�*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*�ж���ʱʱ��*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*���ɿ�������*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*�ж���ʱʱ��*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*��Դ�쳣�¼�*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*�ж���ʱʱ��*/
	{0x00,   0x20,  0x00, 0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00, 0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00, 0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*�������ز�ƽ���¼�*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,          0x02,                 0xC2,     C_NoOffset},	/*�������ز�ƽ������ֵ*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*�������ز�ƽ�����ж���ʱʱ��*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��	*/
/*ʱ�ӹ����¼�*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*�ж���ʱʱ��*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��*/
/*����оƬ�����¼�*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*�ж���ʱʱ��*/
	{0x00,   0x20,  0x00, 0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*�¼�����Դ*/
	{0x00,   0x20,  0x00, 0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*���ܴ���*/
	{0x00,   0x20,  0x00, 0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*�����ۼ�ʱ��*/
};
#define GV_ChineseSignEv30_Len (sizeof(GV_ChineseSignEv30)/C_ChineseSignLen) 
                                                                                 
const uchar8 GV_ChineseSignPa[][C_ChineseSignLen]=     /*�α���*/           
{	                                                                               
	{0x80,   0x00,  0x00,  0x00,  0x60,  (C_DisNo + C_NeedDataChange),          C_5P7PDot,            0xA4,     0x03},	        /*����YYYYMMDD*/
	{0x80,   0x00,  0x00,  0x00,  0x60,  (C_DisNo + C_NeedSingleByteChange),    C_CoL2CoL15P7PDot,    0xA3,     0x00},	        /*ʱ��*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo+C_NoNeedChange,                0x00,                 0xC2,     0x04},	        /*ͨѶ��ַ--���*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo+C_NoNeedChange,                0x00,                 0x84,     0x00},	        /*ͨѶ��ַ--���*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo+C_NoNeedChange,                0x00,                 0xC2,     0x04},	        /*���*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo+C_NoNeedChange,                0x00,                 0x84,     0x00},	        /*���*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo+C_NoNeedChange,                0x00,                 0xC2,     0x04},	        /*�ͻ����*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo+C_NoNeedChange,                0x00,                 0x84,     0x00},	        /*�ͻ����*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0x61,     C_NoOffset},	/*����(��λ)*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0x61,     0x01},	        /*����(��)*/	
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0x61,     0x02},	        /*����(��)*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0x61,     0x03},	        /*����(��)*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0x61,     C_NoOffset},	/*γ��*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0x61,     0x01},	        /*γ��*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0x61,     0x02},	        /*γ��*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0x61,     0x03},	        /*γ��*/

	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0x04,     C_NoOffset},	/*�߶�*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},	/*�ϵ�ȫ��ʱ��*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},	/*�������ʱ��*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},    /*��ʾ�鿴�������ʱ��*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},    /*�޵簴����Ļפ�����ʱ��*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},	/*����С��λ��*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},	/*����С��λ��*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},	/*Һ���٢���������*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  (C_DisNo + C_NeedDataChange),          C_5P7PDot,            0xA4,     0x03      },	/*����ʱ�����л�ʱ�� YYMMDD*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  (C_DisNo + C_NeedSingleByteChange),    C_CoL2CoL15P7PDot,    0xA3,     0x01      },	/*ʱ��   hhmmss    		*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  (C_DisNo + C_NeedDataChange),          C_5P7PDot,            0xA4,     0x03      },	/*������ʱ�α��л�ʱ�� YYMMDD*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  (C_DisNo + C_NeedSingleByteChange),    C_CoL2CoL15P7PDot,    0xA3,     0x01      },	/*ʱ��   hhmmss    		*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  (C_DisNo + C_NeedDataChange),          C_5P7PDot,            0xA4,     0x03      },	/*���׷��ʵ���л�ʱ�� YYMMDD*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  (C_DisNo + C_NeedSingleByteChange),    C_CoL2CoL15P7PDot,    0xA3,     0x01      },	/*ʱ��   hhmmss    		*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  (C_DisNo + C_NeedDataChange),          C_5P7PDot,            0xA4,     0x03      },	/*���׽��ݵ���л�ʱ�� YYMMDD*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  (C_DisNo + C_NeedSingleByteChange),    C_CoL2CoL15P7PDot,    0xA3,     0x01      },	/*ʱ��   hhmmss    		*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},	/*��ʱ����*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},	/*��ʱ�α�����*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},	/*��ʱ����*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},	/*������*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xC2,     C_NoOffset},	/*����������*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},	/*������*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},	/*��Կ������*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  (C_DisNo+C_NeedDataChange),            C_CoL25P3P7PDot,	  0x84,     C_NoOffset},	/*��1-254�����������ڼ���ʱ�α��  YY.MM.DD:NN*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},	/*������������*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},	/*�����ղ�ȡ����ʱ�α��*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  (C_DisNo+C_NeedSingleByteChange),      C_5P7PDot,            0xA3,     C_NoOffset},	/*��1-14ʱ����ʼ���ڼ���ʱ�α��,ֻ�е�1����ͬʱ��2�׽���*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  (C_DisNo+C_NeedSingleByteChange),      C_5P7PDot,            0xA3,     C_NoOffset},	/*��2��*/
	{0x00,   0x00,  0x00,  0x00,  0x50,  (C_DisNo+C_NeedSingleByteChange),      C_CoL15P7PDot,        0xA3,     C_NoOffset},	/*��1-14ʱ����ʼʱ�伶���ʺ�,ֻ�е�1������2-8�ս��ã�ͬʱ��2�׽���*/
	{0x00,   0x00,  0x00,  0x00,  0x50,  (C_DisNo+C_NeedSingleByteChange),      C_CoL15P7PDot,        0xA3,     C_NoOffset},	/*��2��*/
	{0x80,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*��ǰ����1���*/
	{0x80,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*��ǰ����2���*/
	{0x80,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*��ǰ����3���*/
	{0x80,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*��ǰ����4���*/
	{0x80,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*��ǰ����5���*/
	{0x80,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*��ǰ����6���*/
	{0x80,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*��ǰ����7���*/
	{0x80,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*��ǰ����8���*/
	{0x80,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*��ǰ����10���*/ 
	{0x80,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*��ǰ����11���*/ 
	{0x80,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*��ǰ����12���*/ 
	{0x80,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*��ǰ����13���*/ 
	
	{0x00,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*�����׷���1���*/
	{0x00,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*�����׷���2���*/
	{0x00,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*�����׷���3���*/
	{0x00,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*�����׷���4���*/  
	{0x00,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*�����׷���5���*/  
	{0x00,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*�����׷���6���*/  
	{0x00,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*�����׷���7���*/  
	{0x00,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*�����׷���8���*/  
	{0x00,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*�����׷���9���*/  
	{0x00,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*�����׷���10���*/  
	{0x00,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*�����׷���11���*/ 
	{0x00,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*�����׷���12���*/  
                            
	{0x00,   0x00,  0x02,  0x60,  0x00,  C_DiskWhNum,                           0x02,                 0x04,     C_NoOffset},	/*��ǰ�׽���ֵ1*/
	{0x00,   0x00,  0x02,  0x60,  0x00,  C_DiskWhNum,                           0x02,                 0x04,     C_NoOffset},	/*��ǰ�׽���ֵ2*/
	{0x00,   0x00,  0x02,  0x60,  0x00,  C_DiskWhNum,                           0x02,                 0x04,     C_NoOffset},	/*��ǰ�׽���ֵ3*/
	{0x00,   0x00,  0x02,  0x60,  0x00,  C_DiskWhNum,                           0x02,                 0x04,     C_NoOffset},	/*��ǰ�׽���ֵ4*/
	{0x00,   0x00,  0x02,  0x60,  0x00,  C_DiskWhNum,                           0x02,                 0x04,     C_NoOffset},	/*��ǰ�׽���ֵ5*/
	{0x00,   0x00,  0x02,  0x60,  0x00,  C_DiskWhNum,                           0x02,                 0x04,     C_NoOffset},	/*��ǰ�׽���ֵ6*/
	{0x00,   0x00,  0x02,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*��ǰ�׽��ݵ��1*/
	{0x00,   0x00,  0x02,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*��ǰ�׽��ݵ��2*/
	{0x00,   0x00,  0x02,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*��ǰ�׽��ݵ��3*/
	{0x00,   0x00,  0x02,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*��ǰ�׽��ݵ��4*/
	{0x00,   0x00,  0x02,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*��ǰ�׽��ݵ��5*/
	{0x00,   0x00,  0x02,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*��ǰ�׽��ݵ��6*/
	{0x00,   0x00,  0x02,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*��ǰ�׽��ݵ��7*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  (C_DisNo+C_NeedSingleByteChange),      C_5P7PDot,            0xA3,     C_NoOffset},	/*��ǰ����1������*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  (C_DisNo+C_NeedSingleByteChange),      C_5P7PDot,            0xA3,     C_NoOffset},	/*��ǰ����2������*/	
	{0x00,   0x00,  0x00,  0x00,  0x00,  (C_DisNo+C_NeedSingleByteChange),      C_5P7PDot,            0xA3,     C_NoOffset},	/*��ǰ����3������*/	
	{0x00,   0x00,  0x00,  0x00,  0x00,  (C_DisNo+C_NeedSingleByteChange),      C_5P7PDot,            0xA3,     C_NoOffset},	/*��ǰ����4������*/
	{0x00,   0x00,  0x02,  0x60,  0x00,  C_DiskWhNum,                           0x02,                 0x04,     C_NoOffset},	/*�����׽���ֵ1*/
	{0x00,   0x00,  0x02,  0x60,  0x00,  C_DiskWhNum,                           0x02,                 0x04,     C_NoOffset},	/*�����׽���ֵ2*/
	{0x00,   0x00,  0x02,  0x60,  0x00,  C_DiskWhNum,                           0x02,                 0x04,     C_NoOffset},	/*�����׽���ֵ3*/
	{0x00,   0x00,  0x02,  0x60,  0x00,  C_DiskWhNum,                           0x02,                 0x04,     C_NoOffset},	/*�����׽���ֵ4*/
	{0x00,   0x00,  0x02,  0x60,  0x00,  C_DiskWhNum,                           0x02,                 0x04,     C_NoOffset},	/*�����׽���ֵ5*/
	{0x00,   0x00,  0x02,  0x60,  0x00,  C_DiskWhNum,                           0x02,                 0x04,     C_NoOffset},	/*�����׽���ֵ6*/
	{0x00,   0x00,  0x02,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*�����׽��ݵ��1*/
	{0x00,   0x00,  0x02,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*�����׽��ݵ��2*/
	{0x00,   0x00,  0x02,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*�����׽��ݵ��3*/
	{0x00,   0x00,  0x02,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*�����׽��ݵ��4*/
	{0x00,   0x00,  0x02,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*�����׽��ݵ��5*/
	{0x00,   0x00,  0x02,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*�����׽��ݵ��6*/
	{0x00,   0x00,  0x02,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*�����׽��ݵ��7*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               C_5P7PDot,            0xA3,     C_NoOffset},	/*��������1������*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               C_5P7PDot,            0xA3,     C_NoOffset},	/*��������2������*/	
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               C_5P7PDot,            0xA3,     C_NoOffset},	/*��������3������*/	
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               C_5P7PDot,            0xA3,     C_NoOffset},	/*��������4������*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x02,                 0xA4,     C_NoOffset},	/*�������������*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x02,                 0xA4,     C_NoOffset},	/*��ѹ���������*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisYuanNum,                          0x02,                 0x04,     C_NoOffset},	/*�������1��ֵ*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisYuanNum,                          0x02,                 0x04,     C_NoOffset},	/*�������2��ֵ*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisYuanNum,                          0x02,                 0x04,     C_NoOffset},	/*͸֧��ֵ*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisYuanNum,                          0x02,                 0x04,     C_NoOffset},	/*�ڻ����1��ֵ*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisYuanNum,                          0x02,                 0x04,     C_NoOffset},	/*��բ��������ֵ*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xC2,     C_NoOffset},	/*�忨״̬��*/
	{0x00,   0x00,  0x00,  0x42,  0x00,  C_DisVNum,                             0x01,                 0x42,     C_NoOffset},	/*��ѹ��������*/
	{0x00,   0x00,  0x00,  0x42,  0x00,  C_DisVNum,                             0x01,                 0x42,     C_NoOffset},	/*��ѹ��������*/
	{0x00,   0x00,  0x00,  0x42,  0x00,  C_DisVNum,                             0x01,                 0x42,     C_NoOffset},	/*��ѹ����ֵ*/
	{0x00,   0x00,  0x00,  0x42,  0x00,  C_DisVNum,                             0x01,                 0x42,     C_NoOffset},	/*��ѹ����ֵ*/
};
#define GV_ChineseSignPa_Len ( sizeof(GV_ChineseSignPa) / C_ChineseSignLen ) 


const uchar8 GV_ChineseSignPa_1[][C_ChineseSignLen]=     /*�α���*/            
{	                                                                               
	{0x00,   0x00,  0x00,  0xA0,  0x00,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},	/*�����������*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},	/*����ʱ��  	*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  (C_DisNo+C_NoNeedChange),              0x00,                 0xC2,     C_NoOffset},	/*У��������*/
	{0x00,   0xC0,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0x04,     C_NoOffset},	/*����й�����*/
	{0x01,   0x40,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0x04,     C_NoOffset},	/*����޹�����*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  (C_DisNo+C_NoNeedChange),              0x00,                 0xE1,     C_NoOffset},	/*�������������1*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  (C_DisNo+C_NoNeedChange),              0x00,                 0xE1,     C_NoOffset},	/*�й����״̬��*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  (C_DisNo+C_NoNeedChange),              0x00,                 0xE1,     C_NoOffset},	/*�޹����1״̬��*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  (C_DisNo+C_NoNeedChange),              0x00,                 0xE1,     C_NoOffset},	/*�޹����2״̬��*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  (C_DisNo+C_NeedSingleByteChange),      0x02,                 0xC2,     C_NoOffset},	/*������1*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  (C_DisNo+C_NeedSingleByteChange),      0x02,                 0xC2,     C_NoOffset},	/*������2*/	
	{0x00,   0x00,  0x00,  0x00,  0x00,  (C_DisNo+C_NeedSingleByteChange),      0x02,                 0xC2,     C_NoOffset},	/*������3*/
};
#define GV_ChineseSignPa_1_Len (sizeof(GV_ChineseSignPa_1)/C_ChineseSignLen) 


const uchar8 GV_ChineseSignVi[][C_ChineseSignLen]=     /*����*/
{	
	{0x00,   0x00,  0x80,  0x42,  0x00,  C_DisVNum,                             0x01,                  0x42,    C_NoOffset},	/*A���ѹ*/
	{0x00,   0x00,  0x40,  0x42,  0x00,  C_DisVNum,                             0x01,                  0x42,    C_NoOffset},	/*B���ѹ*/
	{0x00,   0x00,  0x20,  0x42,  0x00,  C_DisVNum,                             0x01,                  0x42,    C_NoOffset},	/*C���ѹ*/
	{0x00,   0x00,  0x80,  0x41,  0x00,  C_DisANum,                             0x03,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*A�����*/ 
	{0x00,   0x00,  0x40,  0x41,  0x00,  C_DisANum,                             0x03,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*B�����*/ 
	{0x00,   0x00,  0x20,  0x41,  0x00,  C_DisANum,                             0x03,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*C�����*/
	{0x00,   0x00,  0x10,  0x41,  0x00,  C_DisANum,                             0x03,                  0x23,    C_NoOffset},	/*���ߵ���*/	
	{0x00,   0x00,  0x84,  0x00,  0x00,  C_DisNo,                               0x01,                  0x42,    C_NoOffset},	/*A��Ua���*/
	{0x00,   0x00,  0x44,  0x00,  0x00,  C_DisNo,                               0x01,                  0x42,    C_NoOffset},	/*B��Ub���*/
	{0x00,   0x00,  0x24,  0x00,  0x00,  C_DisNo,                               0x01,                  0x42,    C_NoOffset},	/*C��Uc���*/
	{0x00,   0x00,  0x84,  0x00,  0x00,  C_DisNo,                               0x01,                  0x42,    C_NoOffset},	/*A��UaIa���*/
	{0x00,   0x00,  0x44,  0x00,  0x00,  C_DisNo,                               0x01,                  0x42,    C_NoOffset},	/*B��UbIb���*/
	{0x00,   0x00,  0x24,  0x00,  0x00,  C_DisNo,                               0x01,                  0x42,    C_NoOffset},	/*C��UcIc���*/
	{0x00,   0xE0,  0x00,  0x00,  0x80,  C_DiskWNum,                            0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*˲ʱ���й�����*/
	{0x00,   0xC0,  0x80,  0x00,  0x80,  C_DiskWNum,                            0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*A��˲ʱ�й�����*/
	{0x00,   0xC0,  0x40,  0x00,  0x80,  C_DiskWNum,                            0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*B��˲ʱ�й�����*/
	{0x00,   0xC0,  0x20,  0x00,  0x80,  C_DiskWNum,                            0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*C��˲ʱ�й�����*/
	{0x01,   0x60,  0x00,  0x00,  0x80,  C_DiskvarNum,                          0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*˲ʱ���޹�����*/
	{0x01,   0x40,  0x80,  0x00,  0x80,  C_DiskvarNum,                          0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*A��˲ʱ�޹�����*/
	{0x01,   0x40,  0x40,  0x00,  0x80,  C_DiskvarNum,                          0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*B��˲ʱ�޹�����*/
	{0x01,   0x40,  0x20,  0x00,  0x80,  C_DiskvarNum,                          0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*C��˲ʱ�޹�����*/
	{0x00,   0x20,  0x00,  0x00,  0x80,  C_DiskVANum,                           0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*˲ʱ�����ڹ���*/
	{0x00,   0x00,  0x80,  0x00,  0x80,  C_DiskVANum,                           0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*A��˲ʱ���ڹ���*/
	{0x00,   0x00,  0x40,  0x00,  0x80,  C_DiskVANum,                           0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*B��˲ʱ���ڹ���*/
	{0x00,   0x00,  0x20,  0x00,  0x80,  C_DiskVANum,                           0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*C��˲ʱ���ڹ���*/
	{0x00,   0xE0,  0x00,  0x00,  0x80,  C_DiskWNum,                            0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*1�����й���ƽ������*/
	{0x00,   0xC0,  0x80,  0x00,  0x80,  C_DiskWNum,		                    0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},    /*A��1�����й�ƽ������*/
	{0x00,   0xC0,  0x40,  0x00,  0x80,  C_DiskWNum,       	                    0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},    /*B��1�����й�ƽ������*/
	{0x00,   0xC0,  0x20,  0x00,  0x80,  C_DiskWNum,       	                    0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},    /*C��1�����й�ƽ������*/
	{0x01,   0x60,  0x00,  0x00,  0x80,  C_DiskvarNum,                          0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},    /*1�����޹���ƽ������*/
	{0x01,   0x40,  0x80,  0x00,  0x80,  C_DiskvarNum,		                    0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},    /*A��1�����޹�ƽ������*/
	{0x01,   0x40,  0x40,  0x00,  0x80,  C_DiskvarNum,                          0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},    /*B��1�����޹�ƽ������*/
	{0x01,   0x40,  0x20,  0x00,  0x80,  C_DiskvarNum,                          0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},    /*C��1�����޹�ƽ������*/

	{0x00,   0x20,  0x0C,  0x00,  0x00,  C_DisNo,                               0x03,                  (0x42+C_NeedSignBit0x08),     C_NoOffset},	/*�ܹ�������*/
	{0x00,   0x00,  0x8C,  0x00,  0x00,  C_DisNo,                               0x03,                  (0x42+C_NeedSignBit0x08),     C_NoOffset},	/*A�๦������*/
	{0x00,   0x00,  0x4C,  0x00,  0x00,  C_DisNo,                               0x03,                  (0x42+C_NeedSignBit0x08),     C_NoOffset},	/*B�๦������*/
	{0x00,   0x00,  0x2C,  0x00,  0x00,  C_DisNo,                               0x03,                  (0x42+C_NeedSignBit0x08),     C_NoOffset},	/*C�๦������*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x02,                  0x42,                         C_NoOffset},	/*����Ƶ��*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x01,                  (0x42+C_NeedSignBit0x08),     C_NoOffset},	/*�����¶�*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisVNum,                             0x02,                  0x42,                         C_NoOffset},	/*ʱ�ӵ�ص�ѹ*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisVNum,                             0x02,                  0x42,                         C_NoOffset},	/*ͣ����ص�ѹ*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,                               0x00,                  0x04,                         C_NoOffset},	/*�ڲ���ع���ʱ��*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  (C_DisNo+C_NoNeedChange),              0x00,                  0xC2,                          C_NoOffset},	/*�������״̬��1-7*/
	{0x80,   0xC0,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*��ǰ�й�����*/
	{0x81,   0x40,  0x00,  0xA0,  0x00,  C_DiskvarNum,                          0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*��ǰ�޹�����*/
	/*{0x80,   0x00,  0x00,  0xA0,  0x00,  C_DiskVANum,                           0x04,                  0x23,    C_NoOffset},*/	/*��ǰ��������*/
	{0x80,   0x00,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                  0x04,    C_NoOffset},	/*��ǰ���*/
	{0x80,   0x00,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                  0x04,    C_NoOffset},	/*��ǰ���ʵ��*/
	{0x80,   0x00,  0x02,  0x48,  0x00,  C_DisYuanNum,                          0x04,                  0x04,    C_NoOffset},	/*��ǰ���ݵ��*/
	{0x80,   0x00,  0x00,  0x00,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,             0xA4,     0x03      },	/*�¼���������  YYYYMMDD */
	{0x80,   0x00,  0x00,  0x00,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL2CoL15P7PDot,     0xA3,     0x00      },	/*�¼�����ʱ��   hhmmss  */
	{0x80,   0x00,  0x00,  0x00,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,             0xA4,     0x03      },	/*�¼���������   YYMMDD  */
	{0x80,   0x00,  0x00,  0x00,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL2CoL15P7PDot,     0xA3,     0x00      },	/*�¼�����ʱ�� */
	{0x80,   0x00,  0x00,  0x00,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,             0xA4,     0x03      },	/*���ݶ�������   YYMMDD  */
	{0x80,   0x00,  0x00,  0x00,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL2CoL15P7PDot,     0xA3,     0x00      },	/*���ݶ���ʱ�� */
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0,                     0x04,    C_NoOffset},	/*�¼���¼���*/ 
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0,                     0x04,    C_NoOffset},	/*�����¼���*/ 
	{0x40,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x02,                  0x23,     C_NoOffset},	/*��ѹ��ƽ����*/	
	{0x40,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x02,                  0x23,     C_NoOffset},	/*������ƽ����*/	
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisAhNum,                            0x02,                  0x04,    C_NoOffset},	/*�ܰ�ʱ��*/	
	{0x00,   0x00,  0x80,  0x00,  0x00,  C_DisAhNum,                            0x02,                  0x04,    C_NoOffset},	/*A�లʱ��*/	
	{0x00,   0x00,  0x40,  0x00,  0x00,  C_DisAhNum,                            0x02,                  0x04,    C_NoOffset},	/*B�లʱ��*/	
	{0x00,   0x00,  0x20,  0x00,  0x00,  C_DisAhNum,                            0x02,                  0x04,    C_NoOffset},	/*C�లʱ��*/
	{0x00,   0x00,  0x01,  0x50,  0x00,  C_DisYuanNum,                          0x02,                  0x04,    C_NoOffset},	/*Ǯ���ļ�(ʣ����)*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0,                     0x04,    C_NoOffset},	/*Ǯ���ļ�(�������)*/
	{0x00,   0x00,  0x00,  0x50,  0x00,  C_DisYuanNum,                          0x02,                  0x04,    C_NoOffset},	/*��ǰ͸֧���*/	
	{0x00,   0x00,  0x00,  0x50,  0x00,  C_DisYuanNum,                          0x02,                  0x04,    C_NoOffset},    /*�ۼƹ�����*/
	{0xA0,   0x00,  0x00,  0x60,  0x00,  C_DiskWhNum,                           0x00,                  (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*�¶�����й����ۼ��õ���*/	
	{0x80,   0x00,  0x02,  0x60,  0x00,  C_DiskWhNum,                           0x00,                  (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*��������������й����ۼ��õ���*/
                                                         
};
#define GV_ChineseSignVi_Len (sizeof(GV_ChineseSignVi)/C_ChineseSignLen) 

const uchar8 GV_ChineseSignVi_1[][C_ChineseSignLen]=     /*����*/
{
	{0x00,   0x00,  0x80,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*A��ѹ�ϸ��ʣ���ѹ���ʱ��	*/
	{0x00,   0x00,  0x80,  0x00,  0x00,  C_DisNo,          0x02,                 0x23,    C_NoOffset},	/*A��ѹ�ϸ���	*/
	{0x00,   0x00,  0x80,  0x00,  0x00,  C_DisNo,          0x02,                 0x23,    C_NoOffset},	/*A��ѹ�ϸ���	*/
	{0x00,   0x00,  0x80,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*A��ѹ������ʱ��	*/
	{0x00,   0x00,  0x80,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*A��ѹ������ʱ��	*/                                                         
	{0x00,   0x00,  0x80,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*A��ѹ�ϸ��ʣ���ѹ���ʱ��	*/
	{0x00,   0x00,  0x80,  0x00,  0x00,  C_DisNo,          0x02,                 0x23,    C_NoOffset},	/*A��ѹ�ϸ���	*/
	{0x00,   0x00,  0x80,  0x00,  0x00,  C_DisNo,          0x02,                 0x23,    C_NoOffset},	/*A��ѹ�ϸ���	*/
	{0x00,   0x00,  0x80,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*A��ѹ������ʱ��	*/
	{0x00,   0x00,  0x80,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*A��ѹ������ʱ��	*/                                                         
	{0x00,   0x00,  0x40,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*B��ѹ�ϸ��ʣ���ѹ���ʱ��	*/
	{0x00,   0x00,  0x40,  0x00,  0x00,  C_DisNo,          0x02,                 0x23,    C_NoOffset},	/*B��ѹ�ϸ���	*/
	{0x00,   0x00,  0x40,  0x00,  0x00,  C_DisNo,          0x02,                 0x23,    C_NoOffset},	/*B��ѹ�ϸ���	*/
	{0x00,   0x00,  0x40,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*B��ѹ������ʱ��	*/
	{0x00,   0x00,  0x40,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*B��ѹ������ʱ��	*/                                                         
	{0x00,   0x00,  0x40,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*B��ѹ�ϸ��ʣ���ѹ���ʱ��	*/
	{0x00,   0x00,  0x40,  0x00,  0x00,  C_DisNo,          0x02,                 0x23,    C_NoOffset},	/*B��ѹ�ϸ���	*/
	{0x00,   0x00,  0x40,  0x00,  0x00,  C_DisNo,          0x02,                 0x23,    C_NoOffset},	/*B��ѹ�ϸ���	*/
	{0x00,   0x00,  0x40,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*B��ѹ������ʱ��	*/
	{0x00,   0x00,  0x40,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*B��ѹ������ʱ��	*/                                                         
	{0x00,   0x00,  0x20,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*C��ѹ�ϸ��ʣ���ѹ���ʱ��	*/
	{0x00,   0x00,  0x20,  0x00,  0x00,  C_DisNo,          0x02,                 0x23,    C_NoOffset},	/*C��ѹ�ϸ���	*/
	{0x00,   0x00,  0x20,  0x00,  0x00,  C_DisNo,          0x02,                 0x23,    C_NoOffset},	/*C��ѹ�ϸ���	*/
	{0x00,   0x00,  0x20,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*C��ѹ������ʱ��	*/
	{0x00,   0x00,  0x20,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*C��ѹ������ʱ��	*/                                                         
	{0x00,   0x00,  0x20,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*C��ѹ�ϸ��ʣ���ѹ���ʱ��	*/
	{0x00,   0x00,  0x20,  0x00,  0x00,  C_DisNo,          0x02,                 0x23,    C_NoOffset},	/*C��ѹ�ϸ���	*/
	{0x00,   0x00,  0x20,  0x00,  0x00,  C_DisNo,          0x02,                 0x23,    C_NoOffset},	/*C��ѹ�ϸ���	*/
	{0x00,   0x00,  0x20,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*C��ѹ������ʱ��	*/
	{0x00,   0x00,  0x20,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*C��ѹ������ʱ��	*/                                                         

};
#define GV_ChineseSignVi_1_Len (sizeof(GV_ChineseSignVi_1)/C_ChineseSignLen) 



typedef  struct
{
	  uchar8 DI1;                            /*DI1*/
	  uchar8 DI0Max;						 /*�����ʱΪDI0���ȡֵ�����Ƕ��ʱΪ645 DI0����ֵ*/
	  uchar8 MaxDisplayScreen;			     /*�����ʶ���Ӧ�����ʾ��������ʶ�������жϲ��øñ���*/ 
	  uchar8 DI0Character;                   /*DI0��������*/
	  /*uchar8 TureDisplayScreen;*/			 /*�����ʶ��ʵ����ʾ�������е��Ǻ��ֱ�����,��ȫ������Ϊ0�����ֱ��ƫ�Ʋ��øñ���*/
}Str_DisplayDI1_0Table;				         /*��ʾ��ʶ��1_0�ṹ�壬1����*/

/***********ȡ��ֵͬ����ʾDI0��ͬ����ʽ��****************/
#define C_DI0_0EqualMany       0x01     /*01����ʾ00��01��ʶ��(�������)��ʾ����������ͬ�����������������ѹ�ϸ��ʼ�¼�ȡ�ֻ��DI0���ֵ*/
#define C_DI0_0NoEqualMany     0x02     /*02����ʾ00��01(�������)��ͬ��ʾ�������ֲ�ͬ���¼���¼�ࡣ��DI0���ֵ��DI0=00��*/
#define C_DI0_Out0_Many        0x03     /*03��(���)����֧��DI0==00�������ֻ࣬��DI0���ֵ*/
#define C_DI0_OutMany          0x04     /*04����֧�ֶ��(DI0��ͬ����ʾ��������Ҳ��ͬ)������DI0��ʶ��ȫ�г�����α����ࡢ������ */
/*#define C_DI0_Out0_Many         0x05*/     /*05��ʧѹ��¼���ݣ�DI2=0�����⴦��ͬʱֻ�����1��ʧѹ����ʱ��*/
#define C_DI0_Out0_ManyBorr    20
#define C_DI0_Out0_ManyBorr_0  20     /*20��(���)����֧��DI0==00,�������ֱ����ȫ���ã������ƹ��ʳ��ޡ�ʧѹ��ʧ�������ݣ����㸨����ʾ���ʱ������ʾ��Ϊ20-20=0*/
#define C_DI0_Out0_ManyBorr_4  24     /*24��(���)����֧��DI0==00,�������ֱ��û��ȫ�У�ֻ��ǰ24-20=4������ʱ�α�ʱ�����ڼ��յȣ����㸨����ʾ���ʱ������ʾ��Ϊ24-20=4*/
#define C_DI0_Out0_ManyBorr_6  26     /*26��(���)����֧��DI0==00,�������ֱ��û��ȫ�У�ֻ��ǰ26-20=6��������ݱ��̼�¼�ȣ����㸨����ʾ���ʱ������ʾ��Ϊ26-20=6*/
#define C_DI0_Out0_ManyBorr_1  21     /*21��(���)����֧��DI0==00,�������ֱ��û��ȫ�У�ֻ��ǰ21-20=1��������ʱ�α�ȣ����㸨����ʾ���ʱ������ʾ��Ϊ21-20=1*/
#define C_DI0_Out0_ManyBorr_2  22     /*22��(���)����֧��DI0==00,�������ֱ��û��ȫ�У�ֻ��ǰ22-20=2�����繫�����ձ�����ʾ��Ϊ22-20=2*/

#define C_DI0_OutManyBorr      40
#define C_DI0_OutManyBorr_0    40     /*40����֧�ֶ��(DI0��ͬ����ʾ��������Ҳ��ͬ)���������ֱ����ȫ���ã����й����*/
                                      /*״̬�ֱ���ܴ����ȣ����㸨����ʾ���ʱ������ʾ��ΪC_DI0_OutManyBorr_0-C_DI0_OutManyBorr=0*/
#define C_DI0_OutManyBorr_1    41     /*41����֧�ֶ��(DI0��ͬ����ʾ��������Ҳ��ͬ)���������ֱ��û��ȫ�У���ʱ����*/
                                      /*���㸨����ʾ���ʱ������ʾ��ΪC_DI0_OutManyBorr_1-C_DI0_OutManyBorr=1*/
#define C_DI0_OutManyBorr_3    43     /*43����֧�ֶ��(DI0��ͬ����ʾ��������Ҳ��ͬ)���������ֱ��û��ȫ�У�����ݱ�*/
                                      /*���㸨����ʾ���ʱ������ʾ��ΪC_DI0_OutManyBorr_3-C_DI0_OutManyBorr=3*/

#define C_DI0_0EqualManyBorr   60
#define C_DI0_0EqualManyBorr_0 60     /*60��(���)��֧��DI0==00,�������ֱ����ȫ���ã���ѹ�ϸ��ʼ�¼�����㸨����ʾ���ʱ������ʾ��Ϊ60-60=0*/


const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableEn0[]=        /*DI2=0,ͬDI2=0--08*/
{	/*uchar8 DI1        uchar8 DI0Max     uchar8 �����ʾ����   uchar8 DI0Character*/ 
	{0x02,                0x01,                 0x01,              C_DI0_OutMany},         /*��*/
	{0x02,                0x02,                 0x01,              C_DI0_OutMany},         /*1*/
	{0x02,                0x03,                 0x01,              C_DI0_OutMany},         /*2*/
	{0x02,                0x04,                 0x01,              C_DI0_OutMany},         /*3*/
	{0x02,                0x05,                 0x01,              C_DI0_OutMany},         /*4*/
	{0x02,                0x06,                 0x01,              C_DI0_OutMany},         /*5*/
	{0x02,                0x07,                 0x01,              C_DI0_OutMany},         /*6*/
	{0x02,                0x08,                 0x01,              C_DI0_OutMany},         /*7*/
	{0x02,                0x09,                 0x01,              C_DI0_OutMany},         /*8*/
	{0x02,                0x0A,                 0x01,              C_DI0_OutMany},         /*9*/
	{0x02,                0x0B,                 0x01,              C_DI0_OutMany},         /*10*/
	{0x02,                0x0C,                 0x01,              C_DI0_OutMany},         /*11*/
	{0x02,                0x0D,                 0x01,              C_DI0_OutMany},         /*12*/

	{0x04,                0x01,                 0x01,              C_DI0_OutMany},         /*��*/
	{0x04,                0x02,                 0x01,              C_DI0_OutMany},         /*1*/
	{0x04,                0x03,                 0x01,              C_DI0_OutMany},         /*2*/
	{0x04,                0x04,                 0x01,              C_DI0_OutMany},         /*3*/
	{0x04,                0x05,                 0x01,              C_DI0_OutMany},         /*4*/
	{0x04,                0x06,                 0x01,              C_DI0_OutMany},         /*5*/  
	{0x04,                0x07,                 0x01,              C_DI0_OutMany},         /*6*/  
	{0x04,                0x08,                 0x01,              C_DI0_OutMany},         /*7*/  
	{0x04,                0x09,                 0x01,              C_DI0_OutMany},         /*8*/  
	{0x04,                0x0A,                 0x01,              C_DI0_OutMany},         /*9*/  
	{0x04,                0x0B,                 0x01,              C_DI0_OutMany},         /*10*/
	{0x04,                0x0C,                 0x01,              C_DI0_OutMany},         /*11*/
	{0x04,                0x0D,                 0x01,              C_DI0_OutMany},         /*12*/

	{0x06,                0x01,                 0x01,              C_DI0_OutMany},         /*��*/
	{0x06,                0x02,                 0x01,              C_DI0_OutMany},         /*1*/
	{0x06,                0x03,                 0x01,              C_DI0_OutMany},         /*2*/
	{0x06,                0x04,                 0x01,              C_DI0_OutMany},         /*3*/
	{0x06,                0x05,                 0x01,              C_DI0_OutMany},         /*4*/
	{0x06,                0x06,                 0x01,              C_DI0_OutMany},         /*5*/  
	{0x06,                0x07,                 0x01,              C_DI0_OutMany},         /*6*/  
	{0x06,                0x08,                 0x01,              C_DI0_OutMany},         /*7*/  
	{0x06,                0x09,                 0x01,              C_DI0_OutMany},         /*8*/  
	{0x06,                0x0A,                 0x01,              C_DI0_OutMany},         /*9*/  
	{0x06,                0x0B,                 0x01,              C_DI0_OutMany},         /*10*/
	{0x06,                0x0C,                 0x01,              C_DI0_OutMany},         /*11*/
	{0x06,                0x0D,                 0x01,              C_DI0_OutMany},         /*12*/
};
#define GV_Str_DisplayDI1_0TableEn0Len (sizeof(GV_Str_DisplayDI1_0TableEn0)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableEn15[]=        /*DI2=15,ͬDI2=15--44*/
{	/*uchar8 DI1        uchar8 DI0Max     uchar8 �����ʾ����   uchar8 DI0Character*/ 
	{0x02,                0x01,                 0x01,              C_DI0_OutMany},         
	{0x04,                0x01,                 0x01,              C_DI0_OutMany},         
	{0x06,                0x01,                 0x01,              C_DI0_OutMany},         

};
#define GV_Str_DisplayDI1_0TableEn15Len (sizeof(GV_Str_DisplayDI1_0TableEn15)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableDe0[]=        /*DI2=0,ͬDI2=0--08*/
{	/*uchar8 DI1        uchar8 DI0Max     uchar8 �����ʾ����   uchar8 DI0Character*/
	{0x02,                0x01,                 0x03,             C_DI0_OutMany},         /*��*/
	{0x02,                0x02,                 0x03,             C_DI0_OutMany},         /*����1*/
	{0x02,                0x03,                 0x03,             C_DI0_OutMany},         /*����2*/
	{0x02,                0x04,                 0x03,             C_DI0_OutMany},         /*����3*/
	{0x02,                0x05,                 0x03,             C_DI0_OutMany},         /*����4*/
	{0x02,                0x06,                 0x03,             C_DI0_OutMany},         /*����5*/
	{0x02,                0x07,                 0x03,             C_DI0_OutMany},         /*����6*/
	{0x02,                0x08,                 0x03,             C_DI0_OutMany},         /*����7*/
	{0x02,                0x09,                 0x03,             C_DI0_OutMany},         /*����8*/
	{0x02,                0x0A,                 0x03,             C_DI0_OutMany},         /*����9*/
	{0x02,                0x0B,                 0x03,             C_DI0_OutMany},         /*����10*/
	{0x02,                0x0C,                 0x03,             C_DI0_OutMany},         /*����11*/
	{0x02,                0x0D,                 0x03,             C_DI0_OutMany},         /*����12*/

};
#define GV_Str_DisplayDI1_0TableDe0Len (sizeof(GV_Str_DisplayDI1_0TableDe0)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableDe15[]=        /*DI2=15,ͬDI2=15--44*/
{	/*uchar8 DI1        uchar8 DI0Max    uchar8 �����ʾ����   uchar8 DI0Character*/ 
	{0x02,                0x01,                 0x03,             C_DI0_OutMany},         
};
#define GV_Str_DisplayDI1_0TableDe15Len (sizeof(GV_Str_DisplayDI1_0TableDe15)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableFr0[]=        /*DI2=00*/
{	/*uchar8 DI1        uchar8 DI0Max   uchar8 �����ʾ����   uchar8 DI0Character*/
	{0x02,                0x3C,               0x02,              C_DI0_Out0_ManyBorr_0},	  	           
};
#define GV_Str_DisplayDI1_0TableFr0Len (sizeof(GV_Str_DisplayDI1_0TableFr0)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableFr1[]=        /*DI2=01*/
{	/*uchar8 DI1        uchar8 DI0Max   uchar8 �����ʾ����   uchar8 DI0Character*/
	{0x00,                0x3,               0x00,              C_DI0_Out0_ManyBorr_0},	  	           
};
#define GV_Str_DisplayDI1_0TableFr1Len (sizeof(GV_Str_DisplayDI1_0TableFr1)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableFr2[]=        /*DI2=02*/
{	/*uchar8 DI1        uchar8 DI0Max   uchar8 �����ʾ����   uchar8 DI0Character*/
	{0x02,                0xFF,               0x00,              C_DI0_Out0_ManyBorr_0},
	  	           
};
#define GV_Str_DisplayDI1_0TableFr2Len (sizeof(GV_Str_DisplayDI1_0TableFr2)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableFr3[]=        /*DI2=03*/
{	/*uchar8 DI1        uchar8 DI0Max   uchar8 �����ʾ����   uchar8 DI0Character*/
	{0x02,                0xFE,               0x00,              C_DI0_Out0_ManyBorr_0},
};
#define GV_Str_DisplayDI1_0TableFr3Len (sizeof(GV_Str_DisplayDI1_0TableFr3)/sizeof(Str_DisplayDI1_0Table)) 
const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableFr4[]=        /*DI2=04*/
{	/*uchar8 DI1        uchar8 DI0Max   uchar8 �����ʾ����   uchar8 DI0Character*/ 
	{0x02,               0xFF,               0x02,              C_DI0_Out0_ManyBorr_0},
};
#define GV_Str_DisplayDI1_0TableFr4Len (sizeof(GV_Str_DisplayDI1_0TableFr4)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableFr5[]=        /*DI2=04*/
{	/*uchar8 DI1        uchar8 DI0Max   uchar8 �����ʾ����   uchar8 DI0Character*/ 
	{0x02,               12,               0x02,              C_DI0_Out0_ManyBorr_0},
};
#define GV_Str_DisplayDI1_0TableFr5Len (sizeof(GV_Str_DisplayDI1_0TableFr5)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableFr6[]=        /*DI2=06*/
{   /*uchar8 DI1        uchar8 DI0Max   uchar8 �����ʾ����   uchar8 DI0Character*/
	{0x02,               24,               0x02,              C_DI0_Out0_ManyBorr_0},
};
#define GV_Str_DisplayDI1_0TableFr6Len (sizeof(GV_Str_DisplayDI1_0TableFr6)/sizeof(Str_DisplayDI1_0Table)) 
const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableFr7[]=        /*DI2=04*/
{	/*uchar8 DI1        uchar8 DI0Max   uchar8 �����ʾ����   uchar8 DI0Character*/ 
	{0x02,               4,               0x02,              C_DI0_Out0_ManyBorr_0},
};
#define GV_Str_DisplayDI1_0TableFr7Len (sizeof(GV_Str_DisplayDI1_0TableFr7)/sizeof(Str_DisplayDI1_0Table)) 



const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableFr8[]=        /*DI2=08*/
{	/*uchar8 DI1        uchar8 DI0Max   uchar8 �����ʾ����   uchar8 DI0Character*/
	{0x02,                02,               0x02,              C_DI0_Out0_ManyBorr_0},
	  	           
};
#define GV_Str_DisplayDI1_0TableFr8Len (sizeof(GV_Str_DisplayDI1_0TableFr8)/sizeof(Str_DisplayDI1_0Table)) 


const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TablePort0[]=        /*DI2=00*/
{	/*uchar8 DI1        uchar8 DI0Max   uchar8 �����ʾ����   uchar8 DI0Character*/
	{0x02,                0x01,               0x02,              C_DI0_OutMany},	  	           
	{0x02,                0x02,               0x02,              C_DI0_OutMany},	  	           
};
#define GV_Str_DisplayDI1_0TablePort0Len (sizeof(GV_Str_DisplayDI1_0TablePort0)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TablePort9[]=        /*DI2=00*/
{	/*uchar8 DI1        uchar8 DI0Max   uchar8 �����ʾ����   uchar8 DI0Character*/
	{0x02,                0x01,               0x02,              C_DI0_OutMany},	  	             	           
};
#define GV_Str_DisplayDI1_0TablePort9Len (sizeof(GV_Str_DisplayDI1_0TablePort9)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableEv00[]=        /*DI2=05*/
{	/*uchar8 DI1        uchar8 DI0Max  uchar8 �����ʾ����   uchar8 DI0Character*/   
	{0x05,                0x01,              0x01,              C_DI0_OutMany},/*��������*/
	{0x05,                0x02,              0x01,              C_DI0_OutMany},
	{0x05,                0x03,              0x01,              C_DI0_OutMany},
	{0x05,                0x04,              0x01,              C_DI0_OutMany},/*��ʱʱ��*/
	{0x0A,                0x01,              0x02,              C_DI0_OutMany},/*���ۼƴ�����ʱ��*/
	{0x0A,                0x02,              0x02,              C_DI0_OutMany},/*A�ۼƴ�����ʱ��*/
	{0x0A,                0x03,              0x02,              C_DI0_OutMany},/*B�ۼƴ�����ʱ��*/
	{0x0A,                0x04,              0x02,              C_DI0_OutMany},/*C�ۼƴ�����ʱ��*/
	{0x06,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*��ʧѹ��¼*/	
	{0x07,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*Aʧѹ��¼*/
	{0x08,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*Bʧѹ��¼*/
	{0x09,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*Cʧѹ��¼*/
	{0x0D,                0x01,              0x01,              C_DI0_OutMany},/*�¼������ܴ���*/
	{0x0D,                0x02,              0x01,              C_DI0_OutMany},/*�¼����ۼ�ʱ��*/
	{0x0D,                0x03,              0x02,              C_DI0_OutMany},/*���һ��ʧѹ����ʱ��*/
	{0x0D,                0x04,              0x02,              C_DI0_OutMany},/*���һ��ʧѹ����ʱ��*/		
	{0x0E,                0x01,              0x04,              C_DI0_OutMany},/*�����һ�η�������ʱ��*/
	{0x0E,                0x02,              0x04,              C_DI0_OutMany},/*A���һ�η�������ʱ��*/
	{0x0E,                0x03,              0x04,              C_DI0_OutMany},/*B���һ�η�������ʱ��*/
	{0x0E,                0x04,              0x04,              C_DI0_OutMany},/*C���һ�η�������ʱ��*/
};
#define GV_Str_DisplayDI1_0TableEv00Len (sizeof(GV_Str_DisplayDI1_0TableEv00)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableEv01[]=        /*DI2=01*/
{	/*uchar8 DI1        uchar8 DI0Max  uchar8 �����ʾ����   uchar8 DI0Character*/   
	{0x05,                0x01,              0x01,              C_DI0_OutMany},/*��������*/
	{0x05,                0x02,              0x01,              C_DI0_OutMany},/*�ж���ʱʱ��*/
/*	{0x0A,                0x01,              0x02,              C_DI0_OutMany},*/ /*���ۼƴ�����ʱ��*/
	{0x0A,                0x02,              0x02,              C_DI0_OutMany},/*A�ۼƴ�����ʱ��*/
	{0x0A,                0x03,              0x02,              C_DI0_OutMany},/*B�ۼƴ�����ʱ��*/
	{0x0A,                0x04,              0x02,              C_DI0_OutMany},/*C�ۼƴ�����ʱ��*/
/*	{0x06,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},*/ /*��Ƿѹ��¼*/	
	{0x07,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*AǷѹ��¼*/
	{0x08,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*BǷѹ��¼*/
	{0x09,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*CǷѹ��¼*/
};
#define GV_Str_DisplayDI1_0TableEv01Len (sizeof(GV_Str_DisplayDI1_0TableEv01)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableEv03[]=        /*DI2=05*/
{/*uchar8 DI1        uchar8 DI0Max  uchar8 �����ʾ����   uchar8 DI0Character*/   
	{0x05,                0x01,              0x01,              C_DI0_OutMany},/*��������*/
	{0x05,                0x02,              0x01,              C_DI0_OutMany},/*��������*/
	{0x05,                0x03,              0x01,              C_DI0_OutMany},/*�ж���ʱʱ��*/
/*	{0x0A,                0x01,              0x02,              C_DI0_OutMany},*/ /*���ۼƴ�����ʱ��*/
	{0x0A,                0x02,              0x02,              C_DI0_OutMany},/*A�ۼƴ�����ʱ��*/
	{0x0A,                0x03,              0x02,              C_DI0_OutMany},/*B�ۼƴ�����ʱ��*/
	{0x0A,                0x04,              0x02,              C_DI0_OutMany},/*C�ۼƴ�����ʱ��*/
/*	{0x06,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},*/ /*�ܼ�¼*/	
	{0x07,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*A��¼*/
	{0x08,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*B��¼*/
	{0x09,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*C��¼*/
};
#define GV_Str_DisplayDI1_0TableEv03Len (sizeof(GV_Str_DisplayDI1_0TableEv03)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableEv07[]=        /*DI2=05*/
{	/*uchar8 DI1        uchar8 DI0Max  uchar8 �����ʾ����   uchar8 DI0Character*/   
	{0x05,                0x01,              0x01,              C_DI0_OutMany},/*��������*/
	{0x05,                0x02,              0x01,              C_DI0_OutMany},/*�ж���ʱʱ��*/
	{0x0A,                0x01,              0x02,              C_DI0_OutMany},/*���ۼƴ�����ʱ��*/
	{0x0A,                0x02,              0x02,              C_DI0_OutMany},/*A�ۼƴ�����ʱ��*/
	{0x0A,                0x03,              0x02,              C_DI0_OutMany},/*B�ۼƴ�����ʱ��*/
	{0x0A,                0x04,              0x02,              C_DI0_OutMany},/*C�ۼƴ�����ʱ��*/
	{0x06,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*�ܳ��������¼*/	
	{0x07,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*A���������¼*/
	{0x08,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*B���������¼*/
	{0x09,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*C���������¼*/
};
#define GV_Str_DisplayDI1_0TableEv07Len (sizeof(GV_Str_DisplayDI1_0TableEv07)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableEv04[]=        /*DI2=05*/
{	/*uchar8 DI1        uchar8 DI0Max  uchar8 �����ʾ����   uchar8 DI0Character*/   
	{0x05,                0x01,              0x01,              C_DI0_OutMany},/*��ѹ��������*/
	{0x05,                0x02,              0x01,              C_DI0_OutMany},/*������������*/
	{0x05,                0x03,              0x01,              C_DI0_OutMany},/*������������*/
	{0x05,                0x04,              0x01,              C_DI0_OutMany},/*�ж���ʱʱ��*/
	/*{0x0A,                0x01,              0x02,              C_DI0_OutMany},*/ /*���ۼƴ�����ʱ��*/
	{0x0A,                0x02,              0x02,              C_DI0_OutMany},/*A�ۼƴ�����ʱ��*/
	{0x0A,                0x03,              0x02,              C_DI0_OutMany},/*B�ۼƴ�����ʱ��*/
	{0x0A,                0x04,              0x02,              C_DI0_OutMany},/*C�ۼƴ�����ʱ��*/
	/*{0x06,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},*/ /*�ܼ�¼*/	
	{0x07,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*A��¼*/
	{0x08,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*B��¼*/
	{0x09,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*C��¼*/
};
#define GV_Str_DisplayDI1_0TableEv04Len (sizeof(GV_Str_DisplayDI1_0TableEv04)/sizeof(Str_DisplayDI1_0Table)) 


const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableEv09[]=        /*�����й���������*/
{	/*uchar8 DI1        uchar8 DI0Max  uchar8 �����ʾ����   uchar8 DI0Character*/   
	{0x06,                0x01,              0x01,              C_DI0_OutMany},/*��������*/
	{0x06,                0x02,              0x01,              C_DI0_OutMany},/*��ʱʱ��*/
	{0x07,                0x00,              0x03,              C_DI0_OutMany},/*�ۼƴ�����ʱ��*/
	{0x02,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*�ܼ�¼	*/
};
#define GV_Str_DisplayDI1_0TableEv09Len (sizeof(GV_Str_DisplayDI1_0TableEv09)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableEv0B[]=        /*�޹���������*/
{	/*uchar8 DI1        uchar8 DI0Max  uchar8 �����ʾ����   uchar8 DI0Character*/   
	{0x05,                0x01,              0x01,              C_DI0_OutMany},/*��ѹ��������*/
	{0x05,                0x02,              0x01,              C_DI0_OutMany},
	{0x0A,                0x01,              0x02,              C_DI0_OutMany},/*1�ۼƴ�����ʱ��*/
	{0x0A,                0x02,              0x02,              C_DI0_OutMany},/*2�ۼƴ�����ʱ��*/
	{0x0A,                0x03,              0x02,              C_DI0_OutMany},/*3�ۼƴ�����ʱ��*/
	{0x0A,                0x04,              0x02,              C_DI0_OutMany},/*4�ۼƴ�����ʱ��*/
	{0x06,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*1���޼�¼*/
	{0x07,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*2���޼�¼*/
	{0x08,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*3���޼�¼*/
	{0x09,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*4���޼�¼*/
};
#define GV_Str_DisplayDI1_0TableEv0BLen (sizeof(GV_Str_DisplayDI1_0TableEv0B)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableEv0D[]=        /*ȫʧѹ*/
{	/*uchar8 DI1        uchar8 DI0Max  uchar8 �����ʾ����   uchar8 DI0Character*/   
	{0x07,                0x00,              0x03,              C_DI0_OutMany},/*�ۼƴ�����ʱ��*/
	{0x02,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*�ܼ�¼*/	
};
#define GV_Str_DisplayDI1_0TableEv0DLen (sizeof(GV_Str_DisplayDI1_0TableEv0D)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableEv0E[]=        /*������Դ����*/
{	/*uchar8 DI1        uchar8 DI0Max  uchar8 �����ʾ����   uchar8 DI0Character*/   
	  {0x06,                0x01,              0x01,              C_DI0_OutMany},/*��ʱʱ��*/
	{0x07,                0x00,              0x03,              C_DI0_OutMany},/*�ۼƴ�����ʱ��*/
	{0x02,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*�ܼ�¼*/	
};
#define GV_Str_DisplayDI1_0TableEv0ELen (sizeof(GV_Str_DisplayDI1_0TableEv0E)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableEv12[]=        /*���ܱ����¼�*/
{	/*uchar8 DI1        uchar8 DI0Max  uchar8 �����ʾ����   uchar8 DI0Character*/   
	{0x07,                0x00,              0x03,              C_DI0_OutMany},/*�ۼƴ�����ʱ��*/
	{0x02,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*�ܼ�¼*/	
};
#define GV_Str_DisplayDI1_0TableEv12Len (sizeof(GV_Str_DisplayDI1_0TableEv12)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TablePa00[]=        /*DI2=00*/
{	/*uchar8 DI1        uchar8 DI0Max          uchar8 �����ʾ����   uchar8 DI0Character */
	{0x02,                0x00,                      0x02,              C_DI0_OutMany},	 
};
#define GV_Str_DisplayDI1_0TablePa00Len (sizeof(GV_Str_DisplayDI1_0TablePa00)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TablePa04[]=        /*DI2=00*/
{	/*uchar8 DI1        uchar8 DI0Max          uchar8 �����ʾ����   uchar8 DI0Character*/ 
	{0x02,                0x01,                      0x04,              C_DI0_OutMany},
	{0x02,                0x02,                      0x04,              C_DI0_OutMany},
	{0x02,                0x03,                      0x01,              C_DI0_OutMany},
};
#define GV_Str_DisplayDI1_0TablePa04Len (sizeof(GV_Str_DisplayDI1_0TablePa04)/sizeof(Str_DisplayDI1_0Table)) 


const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TablePa07[]=        /*DI2=00*/
{	/*uchar8 DI1        uchar8 DI0Max          uchar8 �����ʾ����   uchar8 DI0Character */
	{0x02,                0x01,                      0x01,              C_DI0_OutMany},
	{0x02,                0x02,                      0x01,              C_DI0_OutMany},	 
	{0x02,                0x03,                      0x01,              C_DI0_OutMany},	 
	{0x02,                0x04,                      0x01,              C_DI0_OutMany},	 
	{0x02,                0x05,                      0x01,              C_DI0_OutMany},	 
	{0x02,                0x06,                      0x01,              C_DI0_OutMany},	 
	{0x02,                0x07,                      0x01,              C_DI0_OutMany},	 

};
#define GV_Str_DisplayDI1_0TablePa07Len (sizeof(GV_Str_DisplayDI1_0TablePa07)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TablePa0C[]=        /*DI2=00*/
{	/*uchar8 DI1        uchar8 DI0Max          uchar8 �����ʾ����   uchar8 DI0Character */
	{0x02,                0x01,                      0x01,              C_DI0_OutMany},	 
	{0x02,                0x02,                      0x01,              C_DI0_OutMany},	 
	{0x02,                0x03,                      0x01,              C_DI0_OutMany},	 
	{0x02,                0x04,                      0x01,              C_DI0_OutMany},	 
	{0x02,                0x05,                      0x01,              C_DI0_OutMany},	 

};
#define GV_Str_DisplayDI1_0TablePa0CLen (sizeof(GV_Str_DisplayDI1_0TablePa0C)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TablePa0D[]=        /*DI2=00*/
{	/*uchar8 DI1        uchar8 DI0Max          uchar8 �����ʾ����   uchar8 DI0Character*/ 
	{0x02,                0x00,                      0x01,              C_DI0_OutMany},	 
};
#define GV_Str_DisplayDI1_0TablePa0DLen (sizeof(GV_Str_DisplayDI1_0TablePa0D)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TablePa11[]=        /*�������ձ�*/
{	/*uchar8 DI1        uchar8 DI0Max   uchar8 �����ʾ����   uchar8 DI0Character*/  
	{0x02,                0xFE,               0x01,               C_DI0_Out0_ManyBorr_1},
};
#define GV_Str_DisplayDI1_0TablePa11Len (sizeof(GV_Str_DisplayDI1_0TablePa11)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TablePa14[]=        /*ʱ����*/
{	/*uchar8 DI1        uchar8 DI0Max   uchar8 �����ʾ����   uchar8 DI0Character*/     
	{0x02,                0x0E,               1,                C_DI0_Out0_ManyBorr_1  },

};
#define GV_Str_DisplayDI1_0TablePa14Len (sizeof(GV_Str_DisplayDI1_0TablePa14)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TablePa16[]=        /*��ʱ�α�*/
{	/*uchar8 DI1        uchar8 DI0Max   uchar8 �����ʾ����   uchar8 DI0Character */    
	{0x02,                0x08,               14,                C_DI0_Out0_ManyBorr_1  },

};
#define GV_Str_DisplayDI1_0TablePa16Len (sizeof(GV_Str_DisplayDI1_0TablePa16)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TablePa18[]=        /*DI2=05 ����1-12���*/
{	/*uchar8 DI1        uchar8 DI0Max    uchar8 �����ʾ����   uchar8 DI0Character*/ 
	{0x02,                0x01,                0x01,               C_DI0_OutMany},
	{0x02,                0x02,                0x01,               C_DI0_OutMany},
	{0x02,                0x03,                0x01,               C_DI0_OutMany},
	{0x02,                0x04,                0x01,               C_DI0_OutMany},
	{0x02,                0x05,                0x01,               C_DI0_OutMany},
	{0x02,                0x06,                0x01,               C_DI0_OutMany},
	{0x02,                0x07,                0x01,               C_DI0_OutMany},
	{0x02,                0x08,                0x01,               C_DI0_OutMany},
	{0x02,                0x09,                0x01,               C_DI0_OutMany},
	{0x02,                0x0A,                0x01,               C_DI0_OutMany},
	{0x02,                0x0B,                0x01,               C_DI0_OutMany},
	{0x02,                0x0C,                0x01,               C_DI0_OutMany},

};
#define GV_Str_DisplayDI1_0TablePa18Len (sizeof(GV_Str_DisplayDI1_0TablePa18)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TablePa1A[]=        /*DI2=06 ���ݱ�*/
{	/*uchar8 DI1        uchar8 DI0Max    uchar8 �����ʾ����   uchar8 DI0Character*/ 
	{0x02,                0x01,                6,               C_DI0_OutMany},
	{0x02,                0x02,                7,               C_DI0_OutMany},  
	{0x02,                0x03,                4,               C_DI0_OutMany},
};
#define GV_Str_DisplayDI1_0TablePa1ALen (sizeof(GV_Str_DisplayDI1_0TablePa1A)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TablePa1E[]=        /*DI2=1e ���������ֵ*/
{	/*uchar8 DI1        uchar8 DI0Max    uchar8 �����ʾ����   uchar8 DI0Character*/ 
	{0x02,                0x01,                0x01,               C_DI0_OutMany},
	{0x02,                0x02,                0x01,               C_DI0_OutMany},
};
#define GV_Str_DisplayDI1_0TablePa1ELen (sizeof(GV_Str_DisplayDI1_0TablePa1E)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TablePa1F[]=        /*DI2=1e ���������ֵ*/
{	/*uchar8 DI1        uchar8 DI0Max    uchar8 �����ʾ����   uchar8 DI0Character*/ 
	{0x02,                0x01,                0x01,               C_DI0_OutMany},
	{0x02,                0x02,                0x01,               C_DI0_OutMany},
	{0x02,                0x03,                0x01,               C_DI0_OutMany},

};
#define GV_Str_DisplayDI1_0TablePa1FLen (sizeof(GV_Str_DisplayDI1_0TablePa1F)/sizeof(Str_DisplayDI1_0Table)) 
const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TablePa30[]=        /*DI2=05 ����1-4���*/
{	/*uchar8 DI1        uchar8 DI0Max    uchar8 �����ʾ����   uchar8 DI0Character*/ 
	{0x02,                0x01,                0x01,               C_DI0_OutMany},
	{0x02,                0x02,                0x01,               C_DI0_OutMany},
	{0x02,                0x03,                0x01,               C_DI0_OutMany},
	{0x02,                0x04,                0x01,               C_DI0_OutMany},
};
#define GV_Str_DisplayDI1_0TablePa30Len (sizeof(GV_Str_DisplayDI1_0TablePa30)/sizeof(Str_DisplayDI1_0Table)) 


const Str_DisplayDI1_0Table GV_Str_DisplayDI2TableVi00[]=        /*DI2=01*/
{	/*uchar8 DI1        uchar8 DI0Max          uchar8 �����ʾ����   uchar8 DI0Character*/ 
	{0x02,                0x01,                      0x01,              C_DI0_OutMany},
	{0x02,                0x02,                      0x01,              C_DI0_OutMany},
	{0x02,                0x03,                      0x01,              C_DI0_OutMany},
};
#define GV_Str_DisplayDI2TableVi00Len (sizeof(GV_Str_DisplayDI2TableVi00)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI2TableVi01[]=        /*DI2=01*/
{	/*uchar8 DI1        uchar8 DI0Max          uchar8 �����ʾ����   uchar8 DI0Character*/ 
	{0x02,                0x01,                      0x01,              C_DI0_OutMany},
	{0x02,                0x02,                      0x01,              C_DI0_OutMany},
	{0x02,                0x03,                      0x01,              C_DI0_OutMany},
	{0x04,                0x00,                      0x01,              C_DI0_OutMany},
};
#define GV_Str_DisplayDI2TableVi01Len (sizeof(GV_Str_DisplayDI2TableVi01)/sizeof(Str_DisplayDI1_0Table)) 


const Str_DisplayDI1_0Table GV_Str_DisplayDI2TableVi03[]=        /*DI2=03*/
{	/*uchar8 DI1        uchar8 DI0Max          uchar8 �����ʾ����   uchar8 DI0Character*/
	{0x02,                0x01,                      0x01,              C_DI0_OutMany}, 
	{0x02,                0x02,                      0x01,              C_DI0_OutMany},
	{0x02,                0x03,                      0x01,              C_DI0_OutMany},
	{0x02,                0x04,                      0x01,              C_DI0_OutMany},
};
#define GV_Str_DisplayDI2TableVi03Len (sizeof(GV_Str_DisplayDI2TableVi03)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI2TableVi07[]=        /*DI2=03*/
{	/*uchar8 DI1        uchar8 DI0Max          uchar8 �����ʾ����   uchar8 DI0Character*/
	{0x02,                0x00,                      0x01,              C_DI0_OutMany}, 
};
#define GV_Str_DisplayDI2TableVi07Len (sizeof(GV_Str_DisplayDI2TableVi07)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI2TableVi14[]=        /*DI2=03*/
{	/*uchar8 DI1        uchar8 DI0Max          uchar8 �����ʾ����   uchar8 DI0Character*/
	{0x02,                0x07,                      0x01,              C_DI0_Out0_ManyBorr_1}, 			
};
#define GV_Str_DisplayDI2TableVi14Len (sizeof(GV_Str_DisplayDI2TableVi14)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI2TableVi1E[]=        /*DI2=03*/
{	/*uchar8 DI1        uchar8 DI0Max          uchar8 �����ʾ����   uchar8 DI0Character*/
	{0x02,                0x00,                      0x02,              C_DI0_OutMany}, 			
	/*{0x02,                0x02,                      0x01,              C_DI0_OutMany}, */			

};
#define GV_Str_DisplayDI2TableVi1ELen (sizeof(GV_Str_DisplayDI2TableVi1E)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI2TableVi2c[]=        /*DI2=03*/
{	/*uchar8 DI1        uchar8 DI0Max          uchar8 �����ʾ����   uchar8 DI0Character*/
	{0x02,                0x01,                      0x01,              C_DI0_OutMany}, 			
	{0x02,                0x02,                      0x01,              C_DI0_OutMany}, 			
};
#define GV_Str_DisplayDI2TableVi2cLen (sizeof(GV_Str_DisplayDI2TableVi2c)/sizeof(Str_DisplayDI1_0Table)) 
const Str_DisplayDI1_0Table GV_Str_DisplayDI2TableVi31[]=        /*DI2=03*/
{	/*uchar8 DI1        uchar8 DI0Max          uchar8 �����ʾ����   uchar8 DI0Character*/
	{0x02,                0x01,                      0x05,              C_DI0_OutMany}, 			
	{0x02,                0x02,                      0x05,              C_DI0_OutMany}, 			
};
#define GV_Str_DisplayDI2TableVi31Len (sizeof(GV_Str_DisplayDI2TableVi31)/sizeof(Str_DisplayDI1_0Table)) 


const Str_DisplayDI1_0Table GV_Str_DisplayDI2TableVi25[]=        /*DI2=03*/
{	/*uchar8 DI1        uchar8 DI0Max          uchar8 �����ʾ����   uchar8 DI0Character*/
	{0x02,                0x00,                      0x02,              C_DI0_OutMany}, 			

};
#define GV_Str_DisplayDI2TableVi25Len (sizeof(GV_Str_DisplayDI2TableVi25)/sizeof(Str_DisplayDI1_0Table)) 


typedef  struct
{
	  ulong32 PDI1_0Table;	                 /*��ӦDI1��DI0����ַ*/
	  uchar8 DI2;						     /*DI2*/
	  uchar8 DI1_0TableLen;			         /*DI1��DI0��񳤶�*/ 
}Str_DisplayDI2Table;				         /*��ʾ��ʶ��2�ṹ�壬2����*/

const Str_DisplayDI2Table GV_Str_DisplayDI2TableEn[]=    /*������*/
{	/*ulong32 PDI1_0Table                     uchar8 DI2        uchar8 DI1_0TableLen*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEn0),       0x00,         GV_Str_DisplayDI1_0TableEn0Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableEn0),       0x10,         GV_Str_DisplayDI1_0TableEn0Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableEn15),      0x11,         GV_Str_DisplayDI1_0TableEn15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableEn15),      0x12,         GV_Str_DisplayDI1_0TableEn15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableEn15),      0x13,         GV_Str_DisplayDI1_0TableEn15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableEn0),       0x20,         GV_Str_DisplayDI1_0TableEn0Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableEn15),      0x21,         GV_Str_DisplayDI1_0TableEn15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableEn15),      0x22,         GV_Str_DisplayDI1_0TableEn15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableEn15),      0x23,         GV_Str_DisplayDI1_0TableEn15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableEn0),       0x30,         GV_Str_DisplayDI1_0TableEn0Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableEn15),      0x31,         GV_Str_DisplayDI1_0TableEn15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableEn15),      0x32,         GV_Str_DisplayDI1_0TableEn15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableEn15),      0x33,         GV_Str_DisplayDI1_0TableEn15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableEn0),       0x40,         GV_Str_DisplayDI1_0TableEn0Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableEn15),      0x41,         GV_Str_DisplayDI1_0TableEn15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableEn15),      0x42,         GV_Str_DisplayDI1_0TableEn15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableEn15),      0x43,         GV_Str_DisplayDI1_0TableEn15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableEn0),       0x50,         GV_Str_DisplayDI1_0TableEn0Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableEn15),      0x51,         GV_Str_DisplayDI1_0TableEn15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableEn15),      0x52,         GV_Str_DisplayDI1_0TableEn15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableEn15),      0x53,         GV_Str_DisplayDI1_0TableEn15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableEn0),       0x60,         GV_Str_DisplayDI1_0TableEn0Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableEn15),      0x61,         GV_Str_DisplayDI1_0TableEn15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableEn15),      0x62,         GV_Str_DisplayDI1_0TableEn15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableEn15),      0x63,         GV_Str_DisplayDI1_0TableEn15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableEn0),       0x70,         GV_Str_DisplayDI1_0TableEn0Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableEn15),      0x71,         GV_Str_DisplayDI1_0TableEn15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableEn15),      0x72,         GV_Str_DisplayDI1_0TableEn15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableEn15),      0x73,         GV_Str_DisplayDI1_0TableEn15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableEn0),       0x80,         GV_Str_DisplayDI1_0TableEn0Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableEn15),      0x81,         GV_Str_DisplayDI1_0TableEn15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableEn15),      0x82,         GV_Str_DisplayDI1_0TableEn15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableEn15),      0x83,         GV_Str_DisplayDI1_0TableEn15Len},
};
#define GV_Str_DisplayDI2TableEn_Len (sizeof(GV_Str_DisplayDI2TableEn)/sizeof(Str_DisplayDI2Table)) 

const Str_DisplayDI2Table GV_Str_DisplayDI2TableDe[]=      /*������*/
{	/*ulong32 PDI1_0Table                     uchar8 DI2        uchar8 DI1_0TableLen*/
	{(ulong32)(GV_Str_DisplayDI1_0TableDe0),       0x10,         GV_Str_DisplayDI1_0TableDe0Len}, 
	{(ulong32)(GV_Str_DisplayDI1_0TableDe0),       0x20,         GV_Str_DisplayDI1_0TableDe0Len}, 
	{(ulong32)(GV_Str_DisplayDI1_0TableDe0),       0x30,         GV_Str_DisplayDI1_0TableDe0Len}, 
	{(ulong32)(GV_Str_DisplayDI1_0TableDe0),       0x40,         GV_Str_DisplayDI1_0TableDe0Len}, 
	{(ulong32)(GV_Str_DisplayDI1_0TableDe0),       0x50,         GV_Str_DisplayDI1_0TableDe0Len}, 
	{(ulong32)(GV_Str_DisplayDI1_0TableDe0),       0x60,         GV_Str_DisplayDI1_0TableDe0Len}, 
	{(ulong32)(GV_Str_DisplayDI1_0TableDe0),       0x70,         GV_Str_DisplayDI1_0TableDe0Len}, 
	{(ulong32)(GV_Str_DisplayDI1_0TableDe0),       0x80,         GV_Str_DisplayDI1_0TableDe0Len}, 
	{(ulong32)(GV_Str_DisplayDI1_0TableDe15),      0x11,         GV_Str_DisplayDI1_0TableDe15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableDe15),      0x21,         GV_Str_DisplayDI1_0TableDe15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableDe15),      0x31,         GV_Str_DisplayDI1_0TableDe15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableDe15),      0x41,         GV_Str_DisplayDI1_0TableDe15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableDe15),      0x51,         GV_Str_DisplayDI1_0TableDe15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableDe15),      0x61,         GV_Str_DisplayDI1_0TableDe15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableDe15),      0x71,         GV_Str_DisplayDI1_0TableDe15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableDe15),      0x81,         GV_Str_DisplayDI1_0TableDe15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableDe15),      0x12,         GV_Str_DisplayDI1_0TableDe15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableDe15),      0x22,         GV_Str_DisplayDI1_0TableDe15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableDe15),      0x32,         GV_Str_DisplayDI1_0TableDe15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableDe15),      0x42,         GV_Str_DisplayDI1_0TableDe15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableDe15),      0x52,         GV_Str_DisplayDI1_0TableDe15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableDe15),      0x62,         GV_Str_DisplayDI1_0TableDe15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableDe15),      0x72,         GV_Str_DisplayDI1_0TableDe15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableDe15),      0x82,         GV_Str_DisplayDI1_0TableDe15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableDe15),      0x13,         GV_Str_DisplayDI1_0TableDe15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableDe15),      0x23,         GV_Str_DisplayDI1_0TableDe15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableDe15),      0x33,         GV_Str_DisplayDI1_0TableDe15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableDe15),      0x43,         GV_Str_DisplayDI1_0TableDe15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableDe15),      0x53,         GV_Str_DisplayDI1_0TableDe15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableDe15),      0x63,         GV_Str_DisplayDI1_0TableDe15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableDe15),      0x73,         GV_Str_DisplayDI1_0TableDe15Len},
	{(ulong32)(GV_Str_DisplayDI1_0TableDe15),      0x83,         GV_Str_DisplayDI1_0TableDe15Len},

};
#define GV_Str_DisplayDI2TableDe_Len (sizeof(GV_Str_DisplayDI2TableDe)/sizeof(Str_DisplayDI2Table)) 

const Str_DisplayDI2Table GV_Str_DisplayDI2TableFr[]=          /*������*///
{	/*ulong32 PDI1_0Table                     uchar8 DI2        uchar8 DI1_0TableLen*/
	{(ulong32)(GV_Str_DisplayDI1_0TableFr0),       0x00,         GV_Str_DisplayDI1_0TableFr0Len}, /*˲ʱ����*/
	/*{(ulong32)(GV_Str_DisplayDI1_0TableFr1),       0x01,         GV_Str_DisplayDI1_0TableFr1Len},*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TableFr2),       0x02,         GV_Str_DisplayDI1_0TableFr2Len}, /*���Ӷ���*/
	{(ulong32)(GV_Str_DisplayDI1_0TableFr3),       0x03,         GV_Str_DisplayDI1_0TableFr3Len}, /*Сʱ����*/
	{(ulong32)(GV_Str_DisplayDI1_0TableFr4),       0x04,         GV_Str_DisplayDI1_0TableFr4Len}, /*�ն���*/
	{(ulong32)(GV_Str_DisplayDI1_0TableFr5),       0x05,         GV_Str_DisplayDI1_0TableFr5Len}, /*�����ն���*/
	{(ulong32)(GV_Str_DisplayDI1_0TableFr6),       0x06,         GV_Str_DisplayDI1_0TableFr6Len}, /*�¶���*/
	{(ulong32)(GV_Str_DisplayDI1_0TableFr7),       0x07,         GV_Str_DisplayDI1_0TableFr7Len}, /*�궳��*/
	{(ulong32)(GV_Str_DisplayDI1_0TableFr8),       0x08,         GV_Str_DisplayDI1_0TableFr8Len}, /*�л�����*/
	{(ulong32)(GV_Str_DisplayDI1_0TableFr8),       0x09,         GV_Str_DisplayDI1_0TableFr8Len}, /*�л�����*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TableFr8),       0x0A,         GV_Str_DisplayDI1_0TableFr8Len}, /*�л�����*/
	{(ulong32)(GV_Str_DisplayDI1_0TableFr8),       0x0B,         GV_Str_DisplayDI1_0TableFr8Len}, /*�л�����*/
	{(ulong32)(GV_Str_DisplayDI1_0TableFr8),       0x11,         GV_Str_DisplayDI1_0TableFr8Len}, /*���ݽ��㶳��*/
};
#define GV_Str_DisplayDI2TableFr_Len (sizeof(GV_Str_DisplayDI2TableFr)/sizeof(Str_DisplayDI2Table)) 

const Str_DisplayDI2Table GV_Str_DisplayDI2TablePort[]=          /*��������豸*/
{	/*ulong32 PDI1_0Table                     		uchar8 DI2     uchar8 DI1_0TableLen*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePort0),      0x01,        GV_Str_DisplayDI1_0TablePort0Len}, /*RS485*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePort9),      0x09,        GV_Str_DisplayDI1_0TablePort9Len}, /*ģ��*/
};
#define GV_Str_DisplayDI2TablePort_Len ( sizeof( GV_Str_DisplayDI2TablePort ) / sizeof( Str_DisplayDI2Table ) ) 


const Str_DisplayDI2Table GV_Str_DisplayDI2TableEv30[]=          /*03�¼���*/
{	/*ulong32 PDI1_0Table                     uchar8 DI2        uchar8 DI1_0TableLen*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv00),       0x00,         GV_Str_DisplayDI1_0TableEv00Len},/*ʧѹ�¼�*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TableEv01),       0x01,         GV_Str_DisplayDI1_0TableEv01Len},/*Ƿѹ�¼�*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TableEv01),       0x02,         GV_Str_DisplayDI1_0TableEv01Len},/*��ѹ�¼�*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TableEv03),       0x03,         GV_Str_DisplayDI1_0TableEv03Len},/*�����¼�*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TableEv04),       0x04,         GV_Str_DisplayDI1_0TableEv04Len},/*ʧ���¼�*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TableEv01),       0x05,         GV_Str_DisplayDI1_0TableEv01Len},/*�����¼�*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TableEv03),       0x06,         GV_Str_DisplayDI1_0TableEv03Len},/*�����¼�*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TableEv07),       0x07,         GV_Str_DisplayDI1_0TableEv07Len},/*���ʷ����¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv01),       0x08,         GV_Str_DisplayDI1_0TableEv01Len},/*�����¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv09),       0x09,         GV_Str_DisplayDI1_0TableEv09Len},/*�����й���������*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv09),       0x0A,         GV_Str_DisplayDI1_0TableEv09Len},/*�����й���������*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv0B),       0x0B,         GV_Str_DisplayDI1_0TableEv0BLen},/*�޹���������*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv09),       0x0C,         GV_Str_DisplayDI1_0TableEv09Len},/*��������������*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv0D),       0x0D,         GV_Str_DisplayDI1_0TableEv0DLen},/*ȫʧѹ�¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv0E),       0x0E,         GV_Str_DisplayDI1_0TableEv0ELen},/*������Դ�����¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv0E),       0x0F,         GV_Str_DisplayDI1_0TableEv0ELen},/*��ѹ�������¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv0E),       0x10,         GV_Str_DisplayDI1_0TableEv0ELen},/*�����������¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv0E),       0x11,         GV_Str_DisplayDI1_0TableEv0ELen},/*�����¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x12,         GV_Str_DisplayDI1_0TableEv12Len},/*����¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x13,         GV_Str_DisplayDI1_0TableEv12Len},/*�����¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x14,         GV_Str_DisplayDI1_0TableEv12Len},/*���������¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x15,         GV_Str_DisplayDI1_0TableEv12Len},/*�¼������¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x16,         GV_Str_DisplayDI1_0TableEv12Len},/*Уʱ�¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x17,         GV_Str_DisplayDI1_0TableEv12Len},/*ʱ�α����¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x18,         GV_Str_DisplayDI1_0TableEv12Len},/*ʱ�������¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x19,         GV_Str_DisplayDI1_0TableEv12Len},/*�����ձ���¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x1A,         GV_Str_DisplayDI1_0TableEv12Len},/*�����ձ���¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x1B,         GV_Str_DisplayDI1_0TableEv12Len},/*�����¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x1C,         GV_Str_DisplayDI1_0TableEv12Len},/*����Ť���¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv09),       0x1D,         GV_Str_DisplayDI1_0TableEv09Len},/*��ѹ��ƽ���¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv09),       0x1E,         GV_Str_DisplayDI1_0TableEv09Len},/*������ƽ���¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x1F,         GV_Str_DisplayDI1_0TableEv12Len},/*��բ�¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x20,         GV_Str_DisplayDI1_0TableEv12Len},/*��բ�¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x21,         GV_Str_DisplayDI1_0TableEv12Len},/*�ڼ��ձ���¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x22,         GV_Str_DisplayDI1_0TableEv12Len},/*�й���Ϸ�ʽ����¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x23,         GV_Str_DisplayDI1_0TableEv12Len},/*�޹���Ϸ�ʽ����¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x24,         GV_Str_DisplayDI1_0TableEv12Len},/*���ʱ����¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x25,         GV_Str_DisplayDI1_0TableEv12Len},/*���ݱ����¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x26,         GV_Str_DisplayDI1_0TableEv12Len},/*��Կ�����¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x27,         GV_Str_DisplayDI1_0TableEv12Len},/*�쳣�忨�¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x28,         GV_Str_DisplayDI1_0TableEv12Len},/*�����¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x29,         GV_Str_DisplayDI1_0TableEv12Len},/*�˷��¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv0E),       0x2A,         GV_Str_DisplayDI1_0TableEv0ELen},/*�ų������¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv0E),       0x2B,         GV_Str_DisplayDI1_0TableEv0ELen},/*���ɿ��������¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv0E),       0x2C,         GV_Str_DisplayDI1_0TableEv0ELen},/*��Դ�쳣�¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv09),       0x2D,         GV_Str_DisplayDI1_0TableEv09Len},/*�������ز�ƽ���¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv0E),       0x2E,         GV_Str_DisplayDI1_0TableEv0ELen},/*ʱ�ӹ����¼�*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv0E),       0x2F,         GV_Str_DisplayDI1_0TableEv0ELen},/*���ܱ����оƬ�����¼�*/
	/*{(ulong32)(GV_Str_DisplayDI1_0TableEv0E),       0x30,         GV_Str_DisplayDI1_0TableEv0ELen},*/ /*ͨ��ģ�����¼�*/
};
#define GV_Str_DisplayDI2TableEv30_Len (sizeof(GV_Str_DisplayDI2TableEv30)/sizeof(Str_DisplayDI2Table)) 

const Str_DisplayDI2Table GV_Str_DisplayDI2TablePa[]=          /*�α���*/
{    /*ulong32 PDI1_0Table                          uchar8 DI2        uchar8 DI1_0TableLen*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa00),         0x00,         GV_Str_DisplayDI1_0TablePa00Len},    /*����ʱ��*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TablePa00),         0x01,         GV_Str_DisplayDI1_0TablePa00Len},    /*ͨ�ŵ�ַ*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TablePa00),         0x02,         GV_Str_DisplayDI1_0TablePa00Len},    /*���*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa00),         0x03,         GV_Str_DisplayDI1_0TablePa00Len},    /*�ͻ����*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TablePa04),         0x04,         GV_Str_DisplayDI1_0TablePa04Len},    /*�豸����λ��*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa07),         0x07,         GV_Str_DisplayDI1_0TablePa07Len},    
	{(ulong32)(GV_Str_DisplayDI1_0TablePa00),         0x08,         GV_Str_DisplayDI1_0TablePa00Len},    /*�л�ʱ��*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TablePa00),         0x09,         GV_Str_DisplayDI1_0TablePa00Len},    /*�л�ʱ��*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TablePa00),         0x0A,         GV_Str_DisplayDI1_0TablePa00Len},    /*�л�ʱ��*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TablePa00),         0x0B,         GV_Str_DisplayDI1_0TablePa00Len},    /*�л�ʱ��*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0C),         0x0C,         GV_Str_DisplayDI1_0TablePa0CLen},    /*ʱ��ʱ����*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0D),         0x0D,         GV_Str_DisplayDI1_0TablePa0DLen},    /*������*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0D),         0x0F,         GV_Str_DisplayDI1_0TablePa0DLen},    /*��Կ������*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa11),         0x11,         GV_Str_DisplayDI1_0TablePa11Len},    /*�������ձ�*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0D),         0x12,         GV_Str_DisplayDI1_0TablePa0DLen},    /*������������*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0D),         0x13,         GV_Str_DisplayDI1_0TablePa0DLen},    /*�����ղ��õ���ʱ�α��*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa14),         0x14,         GV_Str_DisplayDI1_0TablePa14Len},    /*��ǰ��ʱ����*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa14),         0x15,         GV_Str_DisplayDI1_0TablePa14Len},    /*������ʱ����*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa16),         0x16,         GV_Str_DisplayDI1_0TablePa16Len},    /*��ǰ����ʱ�α�*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa16),         0x17,         GV_Str_DisplayDI1_0TablePa16Len},    /*��������ʱ�α�*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa18),         0x18,         GV_Str_DisplayDI1_0TablePa18Len},    /*��ǰ�׷��ʵ��*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa18),         0x19,         GV_Str_DisplayDI1_0TablePa18Len},    /*�����׷��ʵ��*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa1A),         0x1A,         GV_Str_DisplayDI1_0TablePa1ALen},    /*��ǰ�׽��ݵ��*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa1A),         0x1B,         GV_Str_DisplayDI1_0TablePa1ALen},    /*�����׽��ݵ��*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0D),         0x1C,         GV_Str_DisplayDI1_0TablePa0DLen},    /*�������������*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0D),         0x1D,         GV_Str_DisplayDI1_0TablePa0DLen},    /*��ѹ���������*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TablePa1E),         0x1E,         GV_Str_DisplayDI1_0TablePa1ELen},    /*�����������*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa1F),         0x1F,         GV_Str_DisplayDI1_0TablePa1FLen},    /*�����������*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0D),         0x22,         GV_Str_DisplayDI1_0TablePa0DLen},    /*�忨״̬��*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa30),         0x30,         GV_Str_DisplayDI1_0TablePa30Len},    /*��ѹ�ϸ��ʲ���*/ 
};
#define GV_Str_DisplayDI2TablePa_Len ( sizeof(GV_Str_DisplayDI2TablePa) / sizeof(Str_DisplayDI2Table) ) 

const Str_DisplayDI2Table GV_Str_DisplayDI2TablePa_1[]=          /*�α���*/
{	/*ulong32 PDI1_0Table                          uchar8 DI2        uchar8 DI1_0TableLen*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0D),         0x00,         GV_Str_DisplayDI1_0TablePa0DLen},/*�����������*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0D),         0x01,         GV_Str_DisplayDI1_0TablePa0DLen},/*����ʱ��*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0D),         0x02,         GV_Str_DisplayDI1_0TablePa0DLen},/*У��������*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0D),         0x09,         GV_Str_DisplayDI1_0TablePa0DLen},/*�й�����*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0D),         0x0A,         GV_Str_DisplayDI1_0TablePa0DLen},/*�޹�����*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0D),         0x10,         GV_Str_DisplayDI1_0TablePa0DLen},/*�޹�����*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0D),         0x12,         GV_Str_DisplayDI1_0TablePa0DLen},/*�޹�����*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0D),         0x13,         GV_Str_DisplayDI1_0TablePa0DLen},/*�޹�����*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0D),         0x14,         GV_Str_DisplayDI1_0TablePa0DLen},/*�޹�����*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa1F),         0x16,         GV_Str_DisplayDI1_0TablePa1FLen},/*�޹�����*/
};
#define GV_Str_DisplayDI2TablePa_1_Len (sizeof(GV_Str_DisplayDI2TablePa_1)/sizeof(Str_DisplayDI2Table)) 


const Str_DisplayDI2Table GV_Str_DisplayDI2TableVi[]=          /*����*/
{	/*ulong32 PDI1_0Table                          uchar8 DI2        uchar8 DI1_0TableLen*/
	{(ulong32)(GV_Str_DisplayDI2TableVi00),         0x00,         GV_Str_DisplayDI2TableVi00Len}, /*��ѹ*/
	{(ulong32)(GV_Str_DisplayDI2TableVi01),         0x01,         GV_Str_DisplayDI2TableVi01Len}, /*����*/
	{(ulong32)(GV_Str_DisplayDI2TableVi00),         0x02,         GV_Str_DisplayDI2TableVi00Len}, /*��ѹ���*/
	{(ulong32)(GV_Str_DisplayDI2TableVi00),         0x03,         GV_Str_DisplayDI2TableVi00Len}, 
	{(ulong32)(GV_Str_DisplayDI2TableVi03),         0x04,         GV_Str_DisplayDI2TableVi03Len}, 
	{(ulong32)(GV_Str_DisplayDI2TableVi03),         0x05,         GV_Str_DisplayDI2TableVi03Len}, 
	{(ulong32)(GV_Str_DisplayDI2TableVi03),         0x06,         GV_Str_DisplayDI2TableVi03Len}, 
	{(ulong32)(GV_Str_DisplayDI2TableVi03),         0x07,         GV_Str_DisplayDI2TableVi03Len},/*һ�����й�ƽ������ */
	{(ulong32)(GV_Str_DisplayDI2TableVi03),         0x08,         GV_Str_DisplayDI2TableVi03Len},/*һ�����޹�ƽ������*/ 
	{(ulong32)(GV_Str_DisplayDI2TableVi03),         0x0A,         GV_Str_DisplayDI2TableVi03Len},/*�������� */
	{(ulong32)(GV_Str_DisplayDI2TableVi07),         0x0F,         GV_Str_DisplayDI2TableVi07Len},/*����Ƶ�� */
	{(ulong32)(GV_Str_DisplayDI2TableVi07),         0x10,         GV_Str_DisplayDI2TableVi07Len},/*�����¶� */
	{(ulong32)(GV_Str_DisplayDI2TableVi07),         0x11,         GV_Str_DisplayDI2TableVi07Len},/*ʱ�ӵ�ص�ѹ */
	{(ulong32)(GV_Str_DisplayDI2TableVi07),         0x12,         GV_Str_DisplayDI2TableVi07Len}, 
	{(ulong32)(GV_Str_DisplayDI2TableVi07),         0x13,         GV_Str_DisplayDI2TableVi07Len}, 
	{(ulong32)(GV_Str_DisplayDI2TableVi14),         0x14,         GV_Str_DisplayDI2TableVi14Len}, 
	{(ulong32)(GV_Str_DisplayDI2TableVi07),         0x17,         GV_Str_DisplayDI2TableVi07Len}, 
	{(ulong32)(GV_Str_DisplayDI2TableVi07),         0x18,         GV_Str_DisplayDI2TableVi07Len}, 
	{(ulong32)(GV_Str_DisplayDI2TableVi07),         0x1A,         GV_Str_DisplayDI2TableVi07Len}, 
	{(ulong32)(GV_Str_DisplayDI2TableVi07),         0x1B,         GV_Str_DisplayDI2TableVi07Len}, 
	{(ulong32)(GV_Str_DisplayDI2TableVi07),         0x1C,         GV_Str_DisplayDI2TableVi07Len}, 
	{(ulong32)(GV_Str_DisplayDI2TableVi1E),         0x1E,         GV_Str_DisplayDI2TableVi1ELen}, 
	{(ulong32)(GV_Str_DisplayDI2TableVi1E),         0x20,         GV_Str_DisplayDI2TableVi1ELen}, 
	{(ulong32)(GV_Str_DisplayDI2TableVi1E),         0x21,         GV_Str_DisplayDI2TableVi1ELen}, 
	{(ulong32)(GV_Str_DisplayDI2TableVi07),         0x22,         GV_Str_DisplayDI2TableVi07Len}, 
	{(ulong32)(GV_Str_DisplayDI2TableVi07),         0x23,         GV_Str_DisplayDI2TableVi07Len}, 
	/*{(ulong32)(GV_Str_DisplayDI2TableVi25),         0x25,         GV_Str_DisplayDI2TableVi25Len},*/ 
	{(ulong32)(GV_Str_DisplayDI2TableVi07),         0x26,         GV_Str_DisplayDI2TableVi07Len}, /*��ѹ��ƽ��*/
	{(ulong32)(GV_Str_DisplayDI2TableVi07),         0x27,         GV_Str_DisplayDI2TableVi07Len}, /*������ƽ��*/
	{(ulong32)(GV_Str_DisplayDI2TableVi03),         0x29,         GV_Str_DisplayDI2TableVi03Len}, 
	{(ulong32)(GV_Str_DisplayDI2TableVi2c),         0x2C,         GV_Str_DisplayDI2TableVi2cLen}, /*Ǯ���ļ�*/
	{(ulong32)(GV_Str_DisplayDI2TableVi07),         0x2D,         GV_Str_DisplayDI2TableVi07Len}, 
	{(ulong32)(GV_Str_DisplayDI2TableVi07),         0x2E,         GV_Str_DisplayDI2TableVi07Len}, 
	{(ulong32)(GV_Str_DisplayDI2TableVi07),         0x31,         GV_Str_DisplayDI2TableVi07Len}, 
	{(ulong32)(GV_Str_DisplayDI2TableVi07),         0x32,         GV_Str_DisplayDI2TableVi07Len}, 
};
#define GV_Str_DisplayDI2TableVi_Len (sizeof(GV_Str_DisplayDI2TableVi)/sizeof(Str_DisplayDI2Table)) 

const Str_DisplayDI2Table GV_Str_DisplayDI2TableVi_1[]=          /*����*/
{	/*ulong32 PDI1_0Table                          uchar8 DI2        uchar8 DI1_0TableLen*/
	{(ulong32)(GV_Str_DisplayDI2TableVi31),         0x31,         GV_Str_DisplayDI2TableVi31Len}, /*����A���ѹ�ϸ���*/
	{(ulong32)(GV_Str_DisplayDI2TableVi31),         0x32,         GV_Str_DisplayDI2TableVi31Len}, /*����B���ѹ�ϸ���*/
	{(ulong32)(GV_Str_DisplayDI2TableVi31),         0x33,         GV_Str_DisplayDI2TableVi31Len}, /*����C���ѹ�ϸ���*/
};
#define GV_Str_DisplayDI2TableVi_1_Len (sizeof(GV_Str_DisplayDI2TableVi_1)/sizeof(Str_DisplayDI2Table)) 



typedef  struct 
{
	  ulong32 PDI2Table;	             /*��ӦDI2����ַ*/
	  ulong32 P_ChieseTable;             /*DI3��Ӧ�������ֱ���ַ*/
	  ushort16 ChieseTableLen;           /*���ֱ���Ӧ������ݳ��ȣ��ж��Ƿ�Խ����*/ 
	  uchar8 DI3;						 /*DI3*/
	  uchar8 DI2TableLen;			     /*DI2��񳤶�*/
}Str_DisplayDI3Table;				     /*��ʾ��ʶ��3�ṹ�壬3����*/


const Str_DisplayDI3Table GV_Str_DisplayDI3Table[]=
{	/*PDI2Table                                  P_ChieseTable                       ChieseTableLen                DI3       DI2TableLen*/        
	{(ulong32)(&GV_Str_DisplayDI2TableEn[0]),   (ulong32)(&GV_ChineseSignEn[0]),     GV_ChineseSignEn_Len,         0x00,     GV_Str_DisplayDI2TableEn_Len},
	{(ulong32)(&GV_Str_DisplayDI2TableDe[0]),   (ulong32)(&GV_ChineseSignDe[0]),     GV_ChineseSignDe_Len,         0x10,     GV_Str_DisplayDI2TableDe_Len},
	{(ulong32)(&GV_Str_DisplayDI2TableVi[0]), 	(ulong32)(&GV_ChineseSignVi[0]),     GV_ChineseSignVi_Len,         0x20,     GV_Str_DisplayDI2TableVi_Len},
	{(ulong32)(&GV_Str_DisplayDI2TableVi_1[0]), (ulong32)(&GV_ChineseSignVi_1[0]),   GV_ChineseSignVi_1_Len,       0x21,     GV_Str_DisplayDI2TableVi_1_Len},
	{(ulong32)(&GV_Str_DisplayDI2TableEv30[0]), (ulong32)(&GV_ChineseSignEv30[0]),   GV_ChineseSignEv30_Len,       0x30,     GV_Str_DisplayDI2TableEv30_Len},
	{(ulong32)(&GV_Str_DisplayDI2TablePa[0]), 	(ulong32)(&GV_ChineseSignPa[0]),     GV_ChineseSignPa_Len,         0x40,     GV_Str_DisplayDI2TablePa_Len},
	{(ulong32)(&GV_Str_DisplayDI2TablePa_1[0]), (ulong32)(&GV_ChineseSignPa_1[0]),   GV_ChineseSignPa_1_Len,       0x41,     GV_Str_DisplayDI2TablePa_1_Len},
	{(ulong32)(&GV_Str_DisplayDI2TableFr[0]),   (ulong32)(&GV_ChineseSignFr[0]),     GV_ChineseSignFr_Len,         0x50,     GV_Str_DisplayDI2TableFr_Len},
	{(ulong32)(&GV_Str_DisplayDI2TablePort[0]), (ulong32)(&GV_ChineseSignPort[0]),   GV_ChineseSignPort_Len,       0xF2,     GV_Str_DisplayDI2TablePort_Len},
	
};
#define GV_Str_DisplayDI3TableLen ( sizeof(GV_Str_DisplayDI3Table) / sizeof(Str_DisplayDI3Table) ) 

/*************************��������***************************/
/*uchar8 InF_Display_JudgeIDActive(ulong32 V_ulCodeID,ulong32 V_ulRelatedCodeID,uchar8 V_ucScreenNum);*/ 
void SF_FindDisChieseTableNo_General( Str_DisplayDI3Table Str_DisplayDI3Table, ulong32 V_ulCodeDi );
void SF_FindDisChieseTableNo( void );  
void SF_DisplaySignMessage( Str_DisplayStatus *pV_ucBuffer, uchar8 V_ucSourceMesNum );
void SF_DotDisplayDeal( uchar8 V_ucDot );
void SF_KillZeroDeal( uchar8 *pV_ucDisData, uchar8 V_ucDot );
void SF_DisplayUnit( uchar8 V_ucDisUnit );
void SF_DisplayChinaese( void );
void SF_DisplayDI( void );
void SF_CheckDisplay( ulong32 V_ulDi, ulong32 V_ulRelated_CodeID, uchar8 V_ucDisScreenNum, ushort16 V_usTimer );
void SF_KillZeroDealPreEn( uchar8 *pV_ucDisData, uchar8 V_ucDot );
uchar8 SF_FindDisChieseScreenLen( uchar8 V_ucScreenMaxNum, uchar8 V_ucDICharacter );

void SF_GetDisplayData( uchar8 *pV_ucDisplayData );
uchar8 SF_EnDePointAdjust( uchar8 *pV_ucDisplayData );
void SF_DisplayDataSignDeal( uchar8 *pV_ucDisBuff );
void SF_DisplyMainData( uchar8 V_ucMoneySign );
/*void SF_OutStateDisly(void);*/
void SF_StateDisVolageLimt( uchar8 V_ucStateNum );
void SF_WranRelayAction( void );
void SF_DisplayStateSign( void );
void SF_DisAllData( void );
void SF_ClearDisplyBuff( void );
void SF_PowerOffDisplay500msTimer( void );
void SF_TimingFreshSignMesNum( void );
void SF_PowerOnDisplay500msTimer( void );
void SF_DisplyKey( uchar8 V_ucKeyType );
void SF_CardAbnormalDisDeal( Str_DisplayStatus *pV_ucBuffer );
void SF_DisplayCardAbnormal( void );

/*uchar8 InF_GetPowerOffDisplayState(void);*/  
/*void InF_Display_Init(void);*/
/*void InF_Display_WakeUpInit(void);*/
void InF_Display_ForCard( void );
/*void InF_Display_Message(Str_Msg_Parameter * P_Msg_Parameter);*/

extern uchar8 PF_HextoBCDOneBytes( uchar8 V_ucData );
extern uchar8 SF_JugeDemadFF( uchar8 *P_DemandData, uchar8 V_ucLen );
#if(0)
void SF_ReadDispBuff( uchar8 *pV_ucdatabuff );
#endif
uchar8  SF_ReadDispMode( void );
void SF_DisLTData( void );
void SF_DisplayBorrowPoint_Rectify( void );
void SF_DisplayRealatedOAD_RateJudge( ulong32 V_ulOAD, uchar8 *pV_ucData, ushort16 *pV_usDataLen );
void SF_DisplayData_LastPulseDeal( uchar8 *pV_ucDisplayData );
uchar8 SF_EnBorrowPoint( ulong32 V_ulOAD, uchar8 *pV_ucDisplayData );
void SF_DispDataChange( uchar8 *pV_ucDispHexBuff, uchar8 *pV_ucDispBcdBuff, uchar8 V_ucHexDataLen, uchar8 V_ucBcdDataLen, uchar8 V_ucSign, uchar8 V_ucType );
#pragma pack()

#endif
                       
