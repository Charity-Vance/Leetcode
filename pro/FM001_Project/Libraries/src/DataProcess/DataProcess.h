/****************************************************************************************
Copyright:	ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:	DataProcess.h
Version:	V1
Date:		2014-3-12
Description:
Function List:�ò�����Ҫ�Ƕ���E2��Flash���ݽṹ��DI��ʶ���
				Ϊ�˱���ʹ��E2��ַ��鹤�ߣ����������������ӿո��Tab
****************************************************************************************/
#ifndef __DataProcess_H
#define __DataProcess_H

#include "Public.h"

#pragma pack(1)    /*1�ֽڶ���*/

#define C_CRCLen2                        2                                                                     /*CRC����*/
#define C_CurrDataLen5                   5                                                                     /*Hex��ʽ5�ֽڳ���*/

/**************************�����СΪ2kByte***********************************/
/*****���� �������壬ÿ��669����2007��ʣ��1��41���������ݲ��ù̶�����ƫ��*****/
#define FRAM_BackUp2_Space               0x029D                                                      /*���ݵ�1��������ʼ��ַ*/
#define FRAM_BackUp3_Space               0x053A                                                      /*���ݵ�2��������ʼ��ַ*/
#define FRAM_Remaind_Space               0x07D7                                                      /*ʣ��������ʼ��ַ*/
#define FRAM_Max_Addr                    0x07FF                                                      /*��������ַ*/

/*�������,5�ֽ�hex���ݣ�ÿ�����������2�ֽ�CRC����7���ֽڡ�͸֧��ʣ�����е�ǰ������������󣬽�ϳ���һ���ϵ紦������ַ������йء�*/
/*698����ܲ����޸ķ����磬Ϊ����ԭ��E2��ַ���ò����������ӿ�E2��ַ���ú궨�巽ʽ��ͬʱ���ܺ궨�廹�ǲ���E2Addr��ʽ��ʵ�ʷ�����*/
#define E2Addr_CurrEnergy_St             0x0000                                                      /*��ǰ���ܼ���FRAM��ʼ��ַ*/
#define E2Addr_Pos_Ac_T1_En_Pul_0        (E2Addr_CurrEnergy_St)                                      /*��ǰ�����й�����1����������*/
#define E2Addr_Pos_Ac_T2_En_Pul_0        (E2Addr_Pos_Ac_T1_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*��ǰ�����й�����2����������*/
#define E2Addr_Pos_Ac_T3_En_Pul_0        (E2Addr_Pos_Ac_T2_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*��ǰ�����й�����3����������*/
#define E2Addr_Pos_Ac_T4_En_Pul_0        (E2Addr_Pos_Ac_T3_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*��ǰ�����й�����4����������*/
#define E2Addr_Pos_Ac_T5_En_Pul_0        (E2Addr_Pos_Ac_T4_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*��ǰ�����й�����5����������*/
#define E2Addr_Pos_Ac_T6_En_Pul_0        (E2Addr_Pos_Ac_T5_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*��ǰ�����й�����6����������*/
#define E2Addr_Pos_Ac_T7_En_Pul_0        (E2Addr_Pos_Ac_T6_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*��ǰ�����й�����7����������*/
#define E2Addr_Pos_Ac_T8_En_Pul_0        (E2Addr_Pos_Ac_T7_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*��ǰ�����й�����8����������*/
#define E2Addr_Pos_Ac_T9_En_Pul_0        (E2Addr_Pos_Ac_T8_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*��ǰ�����й�����9����������*/
#define E2Addr_Pos_Ac_T10_En_Pul_0       (E2Addr_Pos_Ac_T9_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*��ǰ�����й�����10����������*/
#define E2Addr_Pos_Ac_T11_En_Pul_0       (E2Addr_Pos_Ac_T10_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ�����й�����11����������*/
#define E2Addr_Pos_Ac_T12_En_Pul_0       (E2Addr_Pos_Ac_T11_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ�����й�����12����������*/

#define E2Addr_Rev_Ac_T1_En_Pul_0        (E2Addr_Pos_Ac_T12_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ�����й�����1����������*/
#define E2Addr_Rev_Ac_T2_En_Pul_0        (E2Addr_Rev_Ac_T1_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*��ǰ�����й�����2����������*/
#define E2Addr_Rev_Ac_T3_En_Pul_0        (E2Addr_Rev_Ac_T2_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*��ǰ�����й�����3����������*/
#define E2Addr_Rev_Ac_T4_En_Pul_0        (E2Addr_Rev_Ac_T3_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*��ǰ�����й�����4����������*/
#define E2Addr_Rev_Ac_T5_En_Pul_0        (E2Addr_Rev_Ac_T4_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*��ǰ�����й�����5����������*/
#define E2Addr_Rev_Ac_T6_En_Pul_0        (E2Addr_Rev_Ac_T5_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*��ǰ�����й�����6����������*/
#define E2Addr_Rev_Ac_T7_En_Pul_0        (E2Addr_Rev_Ac_T6_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*��ǰ�����й�����7����������*/
#define E2Addr_Rev_Ac_T8_En_Pul_0        (E2Addr_Rev_Ac_T7_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*��ǰ�����й�����8����������*/
#define E2Addr_Rev_Ac_T9_En_Pul_0        (E2Addr_Rev_Ac_T8_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*��ǰ�����й�����9����������*/
#define E2Addr_Rev_Ac_T10_En_Pul_0       (E2Addr_Rev_Ac_T9_En_Pul_0+C_CurrDataLen5+C_CRCLen2)        /*��ǰ�����й�����10����������*/
#define E2Addr_Rev_Ac_T11_En_Pul_0       (E2Addr_Rev_Ac_T10_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ�����й�����11����������*/
#define E2Addr_Rev_Ac_T12_En_Pul_0       (E2Addr_Rev_Ac_T11_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ�����й�����12����������*/

#define E2Addr_Qua1_Re_T1_En_Pul_0       (E2Addr_Rev_Ac_T12_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ1�����޹�����1����������*/
#define E2Addr_Qua1_Re_T2_En_Pul_0       (E2Addr_Qua1_Re_T1_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ1�����޹�����2����������*/
#define E2Addr_Qua1_Re_T3_En_Pul_0       (E2Addr_Qua1_Re_T2_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ1�����޹�����3����������*/
#define E2Addr_Qua1_Re_T4_En_Pul_0       (E2Addr_Qua1_Re_T3_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ1�����޹�����4����������*/
#define E2Addr_Qua1_Re_T5_En_Pul_0       (E2Addr_Qua1_Re_T4_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ1�����޹�����5����������*/
#define E2Addr_Qua1_Re_T6_En_Pul_0       (E2Addr_Qua1_Re_T5_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ1�����޹�����6����������*/
#define E2Addr_Qua1_Re_T7_En_Pul_0       (E2Addr_Qua1_Re_T6_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ1�����޹�����7����������*/
#define E2Addr_Qua1_Re_T8_En_Pul_0       (E2Addr_Qua1_Re_T7_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ1�����޹�����8����������*/
#define E2Addr_Qua1_Re_T9_En_Pul_0       (E2Addr_Qua1_Re_T8_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ1�����޹�����9����������*/
#define E2Addr_Qua1_Re_T10_En_Pul_0      (E2Addr_Qua1_Re_T9_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ1�����޹�����10����������*/
#define E2Addr_Qua1_Re_T11_En_Pul_0      (E2Addr_Qua1_Re_T10_En_Pul_0+C_CurrDataLen5+C_CRCLen2)      /*��ǰ1�����޹�����11����������*/
#define E2Addr_Qua1_Re_T12_En_Pul_0      (E2Addr_Qua1_Re_T11_En_Pul_0+C_CurrDataLen5+C_CRCLen2)      /*��ǰ1�����޹�����12����������*/

#define E2Addr_Qua2_Re_T1_En_Pul_0       (E2Addr_Qua1_Re_T12_En_Pul_0+C_CurrDataLen5+C_CRCLen2)      /*��ǰ2�����޹�����1����������*/
#define E2Addr_Qua2_Re_T2_En_Pul_0       (E2Addr_Qua2_Re_T1_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ2�����޹�����2����������*/
#define E2Addr_Qua2_Re_T3_En_Pul_0       (E2Addr_Qua2_Re_T2_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ2�����޹�����3����������*/
#define E2Addr_Qua2_Re_T4_En_Pul_0       (E2Addr_Qua2_Re_T3_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ2�����޹�����4����������*/
#define E2Addr_Qua2_Re_T5_En_Pul_0       (E2Addr_Qua2_Re_T4_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ2�����޹�����5����������*/
#define E2Addr_Qua2_Re_T6_En_Pul_0       (E2Addr_Qua2_Re_T5_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ2�����޹�����6����������*/
#define E2Addr_Qua2_Re_T7_En_Pul_0       (E2Addr_Qua2_Re_T6_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ2�����޹�����7����������*/
#define E2Addr_Qua2_Re_T8_En_Pul_0       (E2Addr_Qua2_Re_T7_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ2�����޹�����8����������*/
#define E2Addr_Qua2_Re_T9_En_Pul_0       (E2Addr_Qua2_Re_T8_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ2�����޹�����9����������*/
#define E2Addr_Qua2_Re_T10_En_Pul_0      (E2Addr_Qua2_Re_T9_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ2�����޹�����10����������*/
#define E2Addr_Qua2_Re_T11_En_Pul_0      (E2Addr_Qua2_Re_T10_En_Pul_0+C_CurrDataLen5+C_CRCLen2)      /*��ǰ2�����޹�����11����������*/
#define E2Addr_Qua2_Re_T12_En_Pul_0      (E2Addr_Qua2_Re_T11_En_Pul_0+C_CurrDataLen5+C_CRCLen2)      /*��ǰ2�����޹�����12����������*/

#define E2Addr_Qua3_Re_T1_En_Pul_0       (E2Addr_Qua2_Re_T12_En_Pul_0+C_CurrDataLen5+C_CRCLen2)      /*��ǰ3�����޹�����1����������*/
#define E2Addr_Qua3_Re_T2_En_Pul_0       (E2Addr_Qua3_Re_T1_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ3�����޹�����2����������*/
#define E2Addr_Qua3_Re_T3_En_Pul_0       (E2Addr_Qua3_Re_T2_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ3�����޹�����3����������*/
#define E2Addr_Qua3_Re_T4_En_Pul_0       (E2Addr_Qua3_Re_T3_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ3�����޹�����4����������*/
#define E2Addr_Qua3_Re_T5_En_Pul_0       (E2Addr_Qua3_Re_T4_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ3�����޹�����5����������*/
#define E2Addr_Qua3_Re_T6_En_Pul_0       (E2Addr_Qua3_Re_T5_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ3�����޹�����6����������*/
#define E2Addr_Qua3_Re_T7_En_Pul_0       (E2Addr_Qua3_Re_T6_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ3�����޹�����7����������*/
#define E2Addr_Qua3_Re_T8_En_Pul_0       (E2Addr_Qua3_Re_T7_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ3�����޹�����8����������*/
#define E2Addr_Qua3_Re_T9_En_Pul_0       (E2Addr_Qua3_Re_T8_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ3�����޹�����9����������*/
#define E2Addr_Qua3_Re_T10_En_Pul_0      (E2Addr_Qua3_Re_T9_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ3�����޹�����10����������*/
#define E2Addr_Qua3_Re_T11_En_Pul_0      (E2Addr_Qua3_Re_T10_En_Pul_0+C_CurrDataLen5+C_CRCLen2)      /*��ǰ3�����޹�����11����������*/
#define E2Addr_Qua3_Re_T12_En_Pul_0      (E2Addr_Qua3_Re_T11_En_Pul_0+C_CurrDataLen5+C_CRCLen2)      /*��ǰ3�����޹�����12����������*/

#define E2Addr_Qua4_Re_T1_En_Pul_0       (E2Addr_Qua3_Re_T12_En_Pul_0+C_CurrDataLen5+C_CRCLen2)      /*��ǰ4�����޹�����1����������*/
#define E2Addr_Qua4_Re_T2_En_Pul_0       (E2Addr_Qua4_Re_T1_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ4�����޹�����2����������*/
#define E2Addr_Qua4_Re_T3_En_Pul_0       (E2Addr_Qua4_Re_T2_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ4�����޹�����3����������*/
#define E2Addr_Qua4_Re_T4_En_Pul_0       (E2Addr_Qua4_Re_T3_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ4�����޹�����4����������*/
#define E2Addr_Qua4_Re_T5_En_Pul_0       (E2Addr_Qua4_Re_T4_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ4�����޹�����5����������*/
#define E2Addr_Qua4_Re_T6_En_Pul_0       (E2Addr_Qua4_Re_T5_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ4�����޹�����6����������*/
#define E2Addr_Qua4_Re_T7_En_Pul_0       (E2Addr_Qua4_Re_T6_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ4�����޹�����7����������*/
#define E2Addr_Qua4_Re_T8_En_Pul_0       (E2Addr_Qua4_Re_T7_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ4�����޹�����8����������*/
#define E2Addr_Qua4_Re_T9_En_Pul_0       (E2Addr_Qua4_Re_T8_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ4�����޹�����9����������*/
#define E2Addr_Qua4_Re_T10_En_Pul_0      (E2Addr_Qua4_Re_T9_En_Pul_0+C_CurrDataLen5+C_CRCLen2)       /*��ǰ4�����޹�����10����������*/
#define E2Addr_Qua4_Re_T11_En_Pul_0      (E2Addr_Qua4_Re_T10_En_Pul_0+C_CurrDataLen5+C_CRCLen2)      /*��ǰ4�����޹�����11����������*/
#define E2Addr_Qua4_Re_T12_En_Pul_0      (E2Addr_Qua4_Re_T11_En_Pul_0+C_CurrDataLen5+C_CRCLen2)      /*��ǰ4�����޹�����12����������*/

#define E2Addr_PosA_Ac_En_Pul_0          (E2Addr_Qua4_Re_T12_En_Pul_0+C_CurrDataLen5+C_CRCLen2)      /*��ǰA�������й�����������*/
#define E2Addr_RevA_Ac_En_Pul_0          (E2Addr_PosA_Ac_En_Pul_0+C_CurrDataLen5+C_CRCLen2)          /*��ǰA�෴���й�����������*/
#define E2Addr_Qua1A_Re_En_Pul_0         (E2Addr_RevA_Ac_En_Pul_0+C_CurrDataLen5+C_CRCLen2)          /*��ǰA��1�����޹�����������*/
#define E2Addr_Qua2A_Re_En_Pul_0         (E2Addr_Qua1A_Re_En_Pul_0+C_CurrDataLen5+C_CRCLen2)         /*��ǰA��2�����޹�����������*/
#define E2Addr_Qua3A_Re_En_Pul_0         (E2Addr_Qua2A_Re_En_Pul_0+C_CurrDataLen5+C_CRCLen2)         /*��ǰA��3�����޹�����������*/
#define E2Addr_Qua4A_Re_En_Pul_0         (E2Addr_Qua3A_Re_En_Pul_0+C_CurrDataLen5+C_CRCLen2)         /*��ǰA��4�����޹�����������*/

#define E2Addr_PosB_Ac_En_Pul_0          (E2Addr_Qua4A_Re_En_Pul_0+C_CurrDataLen5+C_CRCLen2)         /*��ǰB�������й�����������*/
#define E2Addr_RevB_Ac_En_Pul_0          (E2Addr_PosB_Ac_En_Pul_0+C_CurrDataLen5+C_CRCLen2)          /*��ǰB�෴���й�����������*/
#define E2Addr_Qua1B_Re_En_Pul_0         (E2Addr_RevB_Ac_En_Pul_0+C_CurrDataLen5+C_CRCLen2)          /*��ǰB��1�����޹�����������*/
#define E2Addr_Qua2B_Re_En_Pul_0         (E2Addr_Qua1B_Re_En_Pul_0+C_CurrDataLen5+C_CRCLen2)         /*��ǰB��2�����޹�����������*/
#define E2Addr_Qua3B_Re_En_Pul_0         (E2Addr_Qua2B_Re_En_Pul_0+C_CurrDataLen5+C_CRCLen2)         /*��ǰB��3�����޹�����������*/
#define E2Addr_Qua4B_Re_En_Pul_0         (E2Addr_Qua3B_Re_En_Pul_0+C_CurrDataLen5+C_CRCLen2)         /*��ǰB��4�����޹�����������*/

#define E2Addr_PosC_Ac_En_Pul_0          (E2Addr_Qua4B_Re_En_Pul_0+C_CurrDataLen5+C_CRCLen2)         /*��ǰC�������й�����������*/
#define E2Addr_RevC_Ac_En_Pul_0          (E2Addr_PosC_Ac_En_Pul_0+C_CurrDataLen5+C_CRCLen2)          /*��ǰC�෴���й�����������*/
#define E2Addr_Qua1C_Re_En_Pul_0         (E2Addr_RevC_Ac_En_Pul_0+C_CurrDataLen5+C_CRCLen2)          /*��ǰC��1�����޹�����������*/
#define E2Addr_Qua2C_Re_En_Pul_0         (E2Addr_Qua1C_Re_En_Pul_0+C_CurrDataLen5+C_CRCLen2)         /*��ǰC��2�����޹�����������*/
#define E2Addr_Qua3C_Re_En_Pul_0         (E2Addr_Qua2C_Re_En_Pul_0+C_CurrDataLen5+C_CRCLen2)         /*��ǰC��3�����޹�����������*/
#define E2Addr_Qua4C_Re_En_Pul_0         (E2Addr_Qua3C_Re_En_Pul_0+C_CurrDataLen5+C_CRCLen2)         /*��ǰC��4�����޹�����������*/

#define E2Addr_SC_Com_Ac_Tol_En_Pul_0    (E2Addr_Qua4C_Re_En_Pul_0+C_CurrDataLen5+C_CRCLen2)         /*��ǰ��������������й����ۼ��õ���-��������ʽ*/
#define E2Addr_M_Com_Ac_Tol_En_Pul_0     (E2Addr_SC_Com_Ac_Tol_En_Pul_0+C_CurrDataLen5+C_CRCLen2)    /*��ǰ�¶�����й����ۼ��õ���-��������ʽ*/
#define E2Addr_Y_Com_Ac_Tol_En_Pul_0     (E2Addr_M_Com_Ac_Tol_En_Pul_0+C_CurrDataLen5+C_CRCLen2)     /*��ǰ�������������й����ۼ��õ���-��������ʽ*/
#define E2Addr_ChargeBal_Hex_Deal        (E2Addr_Y_Com_Ac_Tol_En_Pul_0+C_CurrDataLen5+C_CRCLen2)     /*��ǰʣ����,���ܴ���ģ��*/
#define E2Addr_OverDraft_Hex_Deal        (E2Addr_ChargeBal_Hex_Deal+C_CurrDataLen5+C_CRCLen2)        /*��ǰ͸֧���,���ܴ���ģ��*/
#define E2Addr_CurrEnergyRam_End         (E2Addr_OverDraft_Hex_Deal+C_CurrDataLen5+C_CRCLen2)        /*��ǰ���ܼ�����RAM E2������ַ*/
/***********��������3�����ݿռ䣬ʣ��Լ40Byte*******************/

/***********���� 1�����壬��40Byte����0x07D7��ʼ****************/
#define FRAMAddr_Enter_LowPower_Time     FRAM_Remaind_Space                                                /*����͹���ʱ�� ��2 CRC*/
#define FRAMAddr_Exit_LowPower_Time      (FRAMAddr_Enter_LowPower_Time+CLEnter_LowPower_Time+C_CRCLen2)    /*�˳��͹���ʱ�� ��2 CRC*/
#define FRAMAddr_SoftI_J_RemainTime      (FRAMAddr_Exit_LowPower_Time+CLExit_LowPower_Time+C_CRCLen2)      /*��IJʣ��ʱ��  2�ֽ�+2CRC*/
#define FRAMAddr_BackTime_OneSec         (FRAMAddr_SoftI_J_RemainTime+CLSoftI_J_RemainTime+C_CRCLen2)      /*����ʱ�䣬ÿ��д���磬������ʱ����  6�ֽ�+2CRC*/
/***********��������1�����ݿռ䣬ʣ��Լ20Byte*******************/



/***********E2��СΪ512kBit��64kByte��ÿҳ64Byte����1024ҳ,E2����ַ0x10000*************/
/***********E2 �������壬ÿ��18k����54k��ʣ��ΪE2 һ������10k****************************/
/**************************�������ݲ��ù̶�����ƫ��288ҳ*********************************/
#define E2_BackUp2_Space                 0x4B00                                                                /*���ݵ�1��������ʼ��ַ*/
#define E2_BackUp3_Space                 0x9600                                                                /*���ݵ�2��������ʼ��ַ*/
#define E2_Remaind_Space                 0xE100                                                                /*ʣ��E2��ʼ��ַ*/
#define E2_Max_Addr                      0xFFFE                                                                /*E2����ַ,Ϊ����ԭ�����ݶ������ֽڣ����������ֵΪ*/

#define E2Addr_SC_Com_Ac_Tol_En_1        0x0000                                                                /*��1��������������й����ۼ��õ���,�������ע��*/
#define E2Addr_SC_Pos_Ac_Tol_En_Pul_1    (E2Addr_SC_Com_Ac_Tol_En_1+CLSC_Com_Ac_Tol_En_1+C_CRCLen2)            /*��1���������������й��ܵ���-��������ʽ��*/
#define E2Addr_SC_Rev_Ac_Tol_En_Pul_1    (E2Addr_SC_Pos_Ac_Tol_En_Pul_1+CLSC_Pos_Ac_Tol_En_Pul_1+C_CRCLen2)    /*��1���������ڷ����й��ܵ���-��������ʽ*/
#define E2Addr_M_Com_Ac_Tol_En_1         (E2Addr_SC_Rev_Ac_Tol_En_Pul_1+CLSC_Rev_Ac_Tol_En_Pul_1+C_CRCLen2)    /*��1�¶�����й����ۼ��õ���*/
#define E2Addr_M_Pos_Ac_Tol_En_Pul_1     (E2Addr_M_Com_Ac_Tol_En_1+CLM_Com_Ac_Tol_En_1+C_CRCLen2)              /*��1�¶������й��ۼƵ���-��������ʽ*/
#define E2Addr_M_Rev_Ac_Tol_En_Pul_1     (E2Addr_M_Pos_Ac_Tol_En_Pul_1+CLM_Pos_Ac_Tol_En_Pul_1+C_CRCLen2)      /*��1�¶ȷ����й��ۼƵ���-��������ʽ*/

/******************����,ÿ��������4�ֽ�����+7�ֽ�ʱ��+2�ֽ�CRC,��13�ֽ�*******************/
#define E2Addr_Pos_Ac_Tol_De_0           (E2Addr_M_Rev_Ac_Tol_En_Pul_1+CLM_Rev_Ac_Tol_En_Pul_1+C_CRCLen2)      /*��ǰ�����й����������������ʱ��*/
#define E2Addr_Pos_Ac_T1_De_0            (E2Addr_Pos_Ac_Tol_De_0+CLPos_Ac_Tol_De_0+C_CRCLen2)                  /*��ǰ�����й�����1�������������ʱ��*/
#define E2Addr_Pos_Ac_T2_De_0            (E2Addr_Pos_Ac_T1_De_0+CLPos_Ac_T1_De_0+C_CRCLen2)                    /*��ǰ�����й�����2�������������ʱ��*/
#define E2Addr_Pos_Ac_T3_De_0            (E2Addr_Pos_Ac_T2_De_0+CLPos_Ac_T2_De_0+C_CRCLen2)                    /*��ǰ�����й�����3�������������ʱ��*/
#define E2Addr_Pos_Ac_T4_De_0            (E2Addr_Pos_Ac_T3_De_0+CLPos_Ac_T3_De_0+C_CRCLen2)                    /*��ǰ�����й�����4�������������ʱ��*/
#define E2Addr_Pos_Ac_T5_De_0            (E2Addr_Pos_Ac_T4_De_0+CLPos_Ac_T4_De_0+C_CRCLen2)                    /*��ǰ�����й�����5�������������ʱ��*/
#define E2Addr_Pos_Ac_T6_De_0            (E2Addr_Pos_Ac_T5_De_0+CLPos_Ac_T5_De_0+C_CRCLen2)                    /*��ǰ�����й�����6�������������ʱ��*/
#define E2Addr_Pos_Ac_T7_De_0            (E2Addr_Pos_Ac_T6_De_0+CLPos_Ac_T6_De_0+C_CRCLen2)                    /*��ǰ�����й�����7�������������ʱ��*/
#define E2Addr_Pos_Ac_T8_De_0            (E2Addr_Pos_Ac_T7_De_0+CLPos_Ac_T7_De_0+C_CRCLen2)                    /*��ǰ�����й�����8�������������ʱ��*/
#define E2Addr_Pos_Ac_T9_De_0            (E2Addr_Pos_Ac_T8_De_0+CLPos_Ac_T8_De_0+C_CRCLen2)                    /*��ǰ�����й�����9�������������ʱ��*/
#define E2Addr_Pos_Ac_T10_De_0           (E2Addr_Pos_Ac_T9_De_0+CLPos_Ac_T9_De_0+C_CRCLen2)                    /*��ǰ�����й�����10�������������ʱ��*/
#define E2Addr_Pos_Ac_T11_De_0           (E2Addr_Pos_Ac_T10_De_0+CLPos_Ac_T10_De_0+C_CRCLen2)                  /*��ǰ�����й�����11�������������ʱ��*/
#define E2Addr_Pos_Ac_T12_De_0           (E2Addr_Pos_Ac_T11_De_0+CLPos_Ac_T11_De_0+C_CRCLen2)                  /*��ǰ�����й�����12�������������ʱ��*/

#define E2Addr_Rev_Ac_Tol_De_0           (E2Addr_Pos_Ac_T12_De_0+CLPos_Ac_T12_De_0+C_CRCLen2)                  /*��ǰ�����й����������������ʱ��*/
#define E2Addr_Rev_Ac_T1_De_0            (E2Addr_Rev_Ac_Tol_De_0+CLRev_Ac_Tol_De_0+C_CRCLen2)                  /*��ǰ�����й�����1�������������ʱ��*/
#define E2Addr_Rev_Ac_T2_De_0            (E2Addr_Rev_Ac_T1_De_0+CLRev_Ac_T1_De_0+C_CRCLen2)                    /*��ǰ�����й�����2�������������ʱ��*/
#define E2Addr_Rev_Ac_T3_De_0            (E2Addr_Rev_Ac_T2_De_0+CLRev_Ac_T2_De_0+C_CRCLen2)                    /*��ǰ�����й�����3�������������ʱ��*/
#define E2Addr_Rev_Ac_T4_De_0            (E2Addr_Rev_Ac_T3_De_0+CLRev_Ac_T3_De_0+C_CRCLen2)                    /*��ǰ�����й�����4�������������ʱ��*/
#define E2Addr_Rev_Ac_T5_De_0            (E2Addr_Rev_Ac_T4_De_0+CLRev_Ac_T4_De_0+C_CRCLen2)                    /*��ǰ�����й�����5�������������ʱ��*/
#define E2Addr_Rev_Ac_T6_De_0            (E2Addr_Rev_Ac_T5_De_0+CLRev_Ac_T5_De_0+C_CRCLen2)                    /*��ǰ�����й�����6�������������ʱ��*/
#define E2Addr_Rev_Ac_T7_De_0            (E2Addr_Rev_Ac_T6_De_0+CLRev_Ac_T6_De_0+C_CRCLen2)                    /*��ǰ�����й�����7�������������ʱ��*/
#define E2Addr_Rev_Ac_T8_De_0            (E2Addr_Rev_Ac_T7_De_0+CLRev_Ac_T7_De_0+C_CRCLen2)                    /*��ǰ�����й�����8�������������ʱ��*/
#define E2Addr_Rev_Ac_T9_De_0            (E2Addr_Rev_Ac_T8_De_0+CLRev_Ac_T8_De_0+C_CRCLen2)                    /*��ǰ�����й�����9�������������ʱ��*/
#define E2Addr_Rev_Ac_T10_De_0           (E2Addr_Rev_Ac_T9_De_0+CLRev_Ac_T9_De_0+C_CRCLen2)                    /*��ǰ�����й�����10�������������ʱ��*/
#define E2Addr_Rev_Ac_T11_De_0           (E2Addr_Rev_Ac_T10_De_0+CLRev_Ac_T10_De_0+C_CRCLen2)                  /*��ǰ�����й�����11�������������ʱ��*/
#define E2Addr_Rev_Ac_T12_De_0           (E2Addr_Rev_Ac_T11_De_0+CLRev_Ac_T11_De_0+C_CRCLen2)                  /*��ǰ�����й�����12�������������ʱ��*/

#define E2Addr_Qua1_Re_Tol_De_0          (E2Addr_Rev_Ac_T12_De_0+CLRev_Ac_T12_De_0+C_CRCLen2)                  /*��ǰ1�����޹����������������ʱ��*/
#define E2Addr_Qua1_Re_T1_De_0           (E2Addr_Qua1_Re_Tol_De_0+CLQua1_Re_Tol_De_0+C_CRCLen2)                /*��ǰ1�����޹�����1�������������ʱ��*/
#define E2Addr_Qua1_Re_T2_De_0           (E2Addr_Qua1_Re_T1_De_0+CLQua1_Re_T1_De_0+C_CRCLen2)                  /*��ǰ1�����޹�����2�������������ʱ��*/
#define E2Addr_Qua1_Re_T3_De_0           (E2Addr_Qua1_Re_T2_De_0+CLQua1_Re_T2_De_0+C_CRCLen2)                  /*��ǰ1�����޹�����3�������������ʱ��*/
#define E2Addr_Qua1_Re_T4_De_0           (E2Addr_Qua1_Re_T3_De_0+CLQua1_Re_T3_De_0+C_CRCLen2)                  /*��ǰ1�����޹�����4�������������ʱ��*/
#define E2Addr_Qua1_Re_T5_De_0           (E2Addr_Qua1_Re_T4_De_0+CLQua1_Re_T4_De_0+C_CRCLen2)                  /*��ǰ1�����޹�����5�������������ʱ��*/
#define E2Addr_Qua1_Re_T6_De_0           (E2Addr_Qua1_Re_T5_De_0+CLQua1_Re_T5_De_0+C_CRCLen2)                  /*��ǰ1�����޹�����6�������������ʱ��*/
#define E2Addr_Qua1_Re_T7_De_0           (E2Addr_Qua1_Re_T6_De_0+CLQua1_Re_T6_De_0+C_CRCLen2)                  /*��ǰ1�����޹�����7�������������ʱ��*/
#define E2Addr_Qua1_Re_T8_De_0           (E2Addr_Qua1_Re_T7_De_0+CLQua1_Re_T7_De_0+C_CRCLen2)                  /*��ǰ1�����޹�����8�������������ʱ��*/
#define E2Addr_Qua1_Re_T9_De_0           (E2Addr_Qua1_Re_T8_De_0+CLQua1_Re_T8_De_0+C_CRCLen2)                  /*��ǰ1�����޹�����9�������������ʱ��*/
#define E2Addr_Qua1_Re_T10_De_0          (E2Addr_Qua1_Re_T9_De_0+CLQua1_Re_T9_De_0+C_CRCLen2)                  /*��ǰ1�����޹�����10�������������ʱ��*/
#define E2Addr_Qua1_Re_T11_De_0          (E2Addr_Qua1_Re_T10_De_0+CLQua1_Re_T10_De_0+C_CRCLen2)                /*��ǰ1�����޹�����11�������������ʱ��*/
#define E2Addr_Qua1_Re_T12_De_0          (E2Addr_Qua1_Re_T11_De_0+CLQua1_Re_T11_De_0+C_CRCLen2)                /*��ǰ1�����޹�����12�������������ʱ��*/

#define E2Addr_Qua2_Re_Tol_De_0          (E2Addr_Qua1_Re_T12_De_0+CLQua1_Re_T12_De_0+C_CRCLen2)                /*��ǰ2�����޹����������������ʱ��*/
#define E2Addr_Qua2_Re_T1_De_0           (E2Addr_Qua2_Re_Tol_De_0+CLQua2_Re_Tol_De_0+C_CRCLen2)                /*��ǰ2�����޹�����1�������������ʱ��*/
#define E2Addr_Qua2_Re_T2_De_0           (E2Addr_Qua2_Re_T1_De_0+CLQua2_Re_T1_De_0+C_CRCLen2)                  /*��ǰ2�����޹�����2�������������ʱ��*/
#define E2Addr_Qua2_Re_T3_De_0           (E2Addr_Qua2_Re_T2_De_0+CLQua2_Re_T2_De_0+C_CRCLen2)                  /*��ǰ2�����޹�����3�������������ʱ��*/
#define E2Addr_Qua2_Re_T4_De_0           (E2Addr_Qua2_Re_T3_De_0+CLQua2_Re_T3_De_0+C_CRCLen2)                  /*��ǰ2�����޹�����4�������������ʱ��*/
#define E2Addr_Qua2_Re_T5_De_0           (E2Addr_Qua2_Re_T4_De_0+CLQua2_Re_T4_De_0+C_CRCLen2)                  /*��ǰ2�����޹�����5�������������ʱ��*/
#define E2Addr_Qua2_Re_T6_De_0           (E2Addr_Qua2_Re_T5_De_0+CLQua2_Re_T5_De_0+C_CRCLen2)                  /*��ǰ2�����޹�����6�������������ʱ��*/
#define E2Addr_Qua2_Re_T7_De_0           (E2Addr_Qua2_Re_T6_De_0+CLQua2_Re_T6_De_0+C_CRCLen2)                  /*��ǰ2�����޹�����7�������������ʱ��*/
#define E2Addr_Qua2_Re_T8_De_0           (E2Addr_Qua2_Re_T7_De_0+CLQua2_Re_T7_De_0+C_CRCLen2)                  /*��ǰ2�����޹�����8�������������ʱ��*/
#define E2Addr_Qua2_Re_T9_De_0           (E2Addr_Qua2_Re_T8_De_0+CLQua2_Re_T8_De_0+C_CRCLen2)                  /*��ǰ2�����޹�����9�������������ʱ��*/
#define E2Addr_Qua2_Re_T10_De_0          (E2Addr_Qua2_Re_T9_De_0+CLQua2_Re_T9_De_0+C_CRCLen2)                  /*��ǰ2�����޹�����10�������������ʱ��*/
#define E2Addr_Qua2_Re_T11_De_0          (E2Addr_Qua2_Re_T10_De_0+CLQua2_Re_T10_De_0+C_CRCLen2)                /*��ǰ2�����޹�����11�������������ʱ��*/
#define E2Addr_Qua2_Re_T12_De_0          (E2Addr_Qua2_Re_T11_De_0+CLQua2_Re_T11_De_0+C_CRCLen2)                /*��ǰ2�����޹�����12�������������ʱ��*/

#define E2Addr_Qua3_Re_Tol_De_0          (E2Addr_Qua2_Re_T12_De_0+CLQua2_Re_T12_De_0+C_CRCLen2)                /*��ǰ3�����޹����������������ʱ��*/
#define E2Addr_Qua3_Re_T1_De_0           (E2Addr_Qua3_Re_Tol_De_0+CLQua3_Re_Tol_De_0+C_CRCLen2)                /*��ǰ3�����޹�����1�������������ʱ��*/
#define E2Addr_Qua3_Re_T2_De_0           (E2Addr_Qua3_Re_T1_De_0+CLQua3_Re_T1_De_0+C_CRCLen2)                  /*��ǰ3�����޹�����2�������������ʱ��*/
#define E2Addr_Qua3_Re_T3_De_0           (E2Addr_Qua3_Re_T2_De_0+CLQua3_Re_T2_De_0+C_CRCLen2)                  /*��ǰ3�����޹�����3�������������ʱ��*/
#define E2Addr_Qua3_Re_T4_De_0           (E2Addr_Qua3_Re_T3_De_0+CLQua3_Re_T3_De_0+C_CRCLen2)                  /*��ǰ3�����޹�����4�������������ʱ��*/
#define E2Addr_Qua3_Re_T5_De_0           (E2Addr_Qua3_Re_T4_De_0+CLQua3_Re_T4_De_0+C_CRCLen2)                  /*��ǰ3�����޹�����5�������������ʱ��*/
#define E2Addr_Qua3_Re_T6_De_0           (E2Addr_Qua3_Re_T5_De_0+CLQua3_Re_T5_De_0+C_CRCLen2)                  /*��ǰ3�����޹�����6�������������ʱ��*/
#define E2Addr_Qua3_Re_T7_De_0           (E2Addr_Qua3_Re_T6_De_0+CLQua3_Re_T6_De_0+C_CRCLen2)                  /*��ǰ3�����޹�����7�������������ʱ��*/
#define E2Addr_Qua3_Re_T8_De_0           (E2Addr_Qua3_Re_T7_De_0+CLQua3_Re_T7_De_0+C_CRCLen2)                  /*��ǰ3�����޹�����8�������������ʱ��*/
#define E2Addr_Qua3_Re_T9_De_0           (E2Addr_Qua3_Re_T8_De_0+CLQua3_Re_T8_De_0+C_CRCLen2)                  /*��ǰ3�����޹�����9�������������ʱ��*/
#define E2Addr_Qua3_Re_T10_De_0          (E2Addr_Qua3_Re_T9_De_0+CLQua3_Re_T9_De_0+C_CRCLen2)                  /*��ǰ3�����޹�����10�������������ʱ��*/
#define E2Addr_Qua3_Re_T11_De_0          (E2Addr_Qua3_Re_T10_De_0+CLQua3_Re_T10_De_0+C_CRCLen2)                /*��ǰ3�����޹�����11�������������ʱ��*/
#define E2Addr_Qua3_Re_T12_De_0          (E2Addr_Qua3_Re_T11_De_0+CLQua3_Re_T11_De_0+C_CRCLen2)                /*��ǰ3�����޹�����12�������������ʱ��*/

#define E2Addr_Qua4_Re_Tol_De_0          (E2Addr_Qua3_Re_T12_De_0+CLQua3_Re_T12_De_0+C_CRCLen2)                /*��ǰ4�����޹����������������ʱ��*/
#define E2Addr_Qua4_Re_T1_De_0           (E2Addr_Qua4_Re_Tol_De_0+CLQua4_Re_Tol_De_0+C_CRCLen2)                /*��ǰ4�����޹�����1�������������ʱ��*/
#define E2Addr_Qua4_Re_T2_De_0           (E2Addr_Qua4_Re_T1_De_0+CLQua4_Re_T1_De_0+C_CRCLen2)                  /*��ǰ4�����޹�����2�������������ʱ��*/
#define E2Addr_Qua4_Re_T3_De_0           (E2Addr_Qua4_Re_T2_De_0+CLQua4_Re_T2_De_0+C_CRCLen2)                  /*��ǰ4�����޹�����3�������������ʱ��*/
#define E2Addr_Qua4_Re_T4_De_0           (E2Addr_Qua4_Re_T3_De_0+CLQua4_Re_T3_De_0+C_CRCLen2)                  /*��ǰ4�����޹�����4�������������ʱ��*/
#define E2Addr_Qua4_Re_T5_De_0           (E2Addr_Qua4_Re_T4_De_0+CLQua4_Re_T4_De_0+C_CRCLen2)                  /*��ǰ4�����޹�����5�������������ʱ��*/
#define E2Addr_Qua4_Re_T6_De_0           (E2Addr_Qua4_Re_T5_De_0+CLQua4_Re_T5_De_0+C_CRCLen2)                  /*��ǰ4�����޹�����6�������������ʱ��*/
#define E2Addr_Qua4_Re_T7_De_0           (E2Addr_Qua4_Re_T6_De_0+CLQua4_Re_T6_De_0+C_CRCLen2)                  /*��ǰ4�����޹�����7�������������ʱ��*/
#define E2Addr_Qua4_Re_T8_De_0           (E2Addr_Qua4_Re_T7_De_0+CLQua4_Re_T7_De_0+C_CRCLen2)                  /*��ǰ4�����޹�����8�������������ʱ��*/
#define E2Addr_Qua4_Re_T9_De_0           (E2Addr_Qua4_Re_T8_De_0+CLQua4_Re_T8_De_0+C_CRCLen2)                  /*��ǰ4�����޹�����9�������������ʱ��*/
#define E2Addr_Qua4_Re_T10_De_0          (E2Addr_Qua4_Re_T9_De_0+CLQua4_Re_T9_De_0+C_CRCLen2)                  /*��ǰ4�����޹�����10�������������ʱ��*/
#define E2Addr_Qua4_Re_T11_De_0          (E2Addr_Qua4_Re_T10_De_0+CLQua4_Re_T10_De_0+C_CRCLen2)                /*��ǰ4�����޹�����11�������������ʱ��*/
#define E2Addr_Qua4_Re_T12_De_0          (E2Addr_Qua4_Re_T11_De_0+CLQua4_Re_T11_De_0+C_CRCLen2)                /*��ǰ4�����޹�����12�������������ʱ��*/

#define E2Addr_PosA_Ac_De_0              (E2Addr_Qua4_Re_T12_De_0+CLQua4_Re_T12_De_0+C_CRCLen2)                /*��ǰA�������й��������������ʱ��*/
#define E2Addr_RevA_Ac_De_0              (E2Addr_PosA_Ac_De_0+CLPosA_Ac_De_0+C_CRCLen2)                        /*��ǰA�෴���й��������������ʱ��*/
#define E2Addr_ComA_Re1_De_0             (E2Addr_RevA_Ac_De_0+CLRevA_Ac_De_0+C_CRCLen2)                        /*��ǰA������޹�1�������������ʱ��*/
#define E2Addr_ComA_Re2_De_0             (E2Addr_ComA_Re1_De_0+CLComA_Re1_De_0+C_CRCLen2)                      /*��ǰA������޹�2�������������ʱ��*/
#define E2Addr_Qua1A_Re_De_0             (E2Addr_ComA_Re2_De_0+CLComA_Re2_De_0+C_CRCLen2)                      /*��ǰA��1�����޹��������������ʱ��*/
#define E2Addr_Qua2A_Re_De_0             (E2Addr_Qua1A_Re_De_0+CLQua1A_Re_De_0+C_CRCLen2)                      /*��ǰA��2�����޹��������������ʱ��*/
#define E2Addr_Qua3A_Re_De_0             (E2Addr_Qua2A_Re_De_0+CLQua2A_Re_De_0+C_CRCLen2)                      /*��ǰA��3�����޹��������������ʱ��*/
#define E2Addr_Qua4A_Re_De_0             (E2Addr_Qua3A_Re_De_0+CLQua3A_Re_De_0+C_CRCLen2)                      /*��ǰA��4�����޹��������������ʱ��*/

#define E2Addr_PosB_Ac_De_0              (E2Addr_Qua4A_Re_De_0+CLQua4A_Re_De_0+C_CRCLen2)                      /*��ǰB�������й��������������ʱ��*/
#define E2Addr_RevB_Ac_De_0              (E2Addr_PosB_Ac_De_0+CLPosB_Ac_De_0+C_CRCLen2)                        /*��ǰB�෴���й��������������ʱ��*/
#define E2Addr_ComB_Re1_De_0             (E2Addr_RevB_Ac_De_0+CLRevB_Ac_De_0+C_CRCLen2)                        /*��ǰB������޹�1�������������ʱ��*/
#define E2Addr_ComB_Re2_De_0             (E2Addr_ComB_Re1_De_0+CLComB_Re1_De_0+C_CRCLen2)                      /*��ǰB������޹�2�������������ʱ��*/
#define E2Addr_Qua1B_Re_De_0             (E2Addr_ComB_Re2_De_0+CLComB_Re2_De_0+C_CRCLen2)                      /*��ǰB��1�����޹��������������ʱ��*/
#define E2Addr_Qua2B_Re_De_0             (E2Addr_Qua1B_Re_De_0+CLQua1B_Re_De_0+C_CRCLen2)                      /*��ǰB��2�����޹��������������ʱ��*/
#define E2Addr_Qua3B_Re_De_0             (E2Addr_Qua2B_Re_De_0+CLQua2B_Re_De_0+C_CRCLen2)                      /*��ǰB��3�����޹��������������ʱ��*/
#define E2Addr_Qua4B_Re_De_0             (E2Addr_Qua3B_Re_De_0+CLQua3B_Re_De_0+C_CRCLen2)                      /*��ǰB��4�����޹��������������ʱ��*/

#define E2Addr_PosC_Ac_De_0              (E2Addr_Qua4B_Re_De_0+CLQua4B_Re_De_0+C_CRCLen2)                      /*��ǰC�������й��������������ʱ��*/
#define E2Addr_RevC_Ac_De_0              (E2Addr_PosC_Ac_De_0+CLPosC_Ac_De_0+C_CRCLen2)                        /*��ǰC�෴���й��������������ʱ��*/
#define E2Addr_ComC_Re1_De_0             (E2Addr_RevC_Ac_De_0+CLRevC_Ac_De_0+C_CRCLen2)                        /*��ǰC������޹�1�������������ʱ��*/
#define E2Addr_ComC_Re2_De_0             (E2Addr_ComC_Re1_De_0+CLComC_Re1_De_0+C_CRCLen2)                      /*��ǰC������޹�2�������������ʱ��*/
#define E2Addr_Qua1C_Re_De_0             (E2Addr_ComC_Re2_De_0+CLComC_Re2_De_0+C_CRCLen2)                      /*��ǰC��1�����޹��������������ʱ��*/
#define E2Addr_Qua2C_Re_De_0             (E2Addr_Qua1C_Re_De_0+CLQua1C_Re_De_0+C_CRCLen2)                      /*��ǰC��2�����޹��������������ʱ��*/
#define E2Addr_Qua3C_Re_De_0             (E2Addr_Qua2C_Re_De_0+CLQua2C_Re_De_0+C_CRCLen2)                      /*��ǰC��3�����޹��������������ʱ��*/
#define E2Addr_Qua4C_Re_De_0             (E2Addr_Qua3C_Re_De_0+CLQua3C_Re_De_0+C_CRCLen2)                      /*��ǰC��4�����޹��������������ʱ��*/
#define E2Addr_De_End                    (E2Addr_Qua4C_Re_De_0+CLQua4C_Re_De_0+C_CRCLen2)                      /*������¼E2������ַ*/

/*******************�������¼�****************************************************/
#define E2Addr_EventNote_StPage1         E2Addr_De_End                                                         /*�¼���¼E2�洢��ʼ��ַ*/

#define E2Addr_All_Loss_Vol_Degree       E2Addr_EventNote_StPage1                                              /*ȫʧѹ�ܴ���*/
#define E2Addr_All_Loss_Vol_Time         (E2Addr_All_Loss_Vol_Degree+CLAll_Loss_Vol_Degree+C_CRCLen2)          /*ȫʧѹ�ۼ�ʱ��*/

#define E2Addr_Aux_Pow_Down_Degree       (E2Addr_All_Loss_Vol_Time+CLAll_Loss_Vol_Time+C_CRCLen2)              /*������Դ�����ܴ���*/
#define E2Addr_Aux_Pow_Down_Time         (E2Addr_Aux_Pow_Down_Degree+CLAux_Pow_Down_Degree+C_CRCLen2)          /*������Դ�������ۼ�ʱ��*/

#define E2Addr_Pow_Down_Degree           (E2Addr_Aux_Pow_Down_Time+CLAux_Pow_Down_Time+C_CRCLen2)              /*�����ܴ���*/
#define	E2Addr_Pow_Down_Time             (E2Addr_Pow_Down_Degree+CLPow_Down_Degree+C_CRCLen2)                  /*�����ۼ�ʱ��*/

#define E2Addr_Pos_Ac_De_Over_Degree     (E2Addr_Pow_Down_Time+CLPow_Down_Time+C_CRCLen2)                      /*�����й����������ܴ���*/
#define E2Addr_Pos_Ac_De_Over_Time       (E2Addr_Pos_Ac_De_Over_Degree+CLPos_Ac_De_Over_Degree+C_CRCLen2)      /*�����й������������ۼ�ʱ��*/

#define E2Addr_Rev_Ac_De_Over_Degree     (E2Addr_Pos_Ac_De_Over_Time+CLPos_Ac_De_Over_Time+C_CRCLen2)          /*�����й����������ܴ���*/
#define E2Addr_Rev_Ac_De_Over_Time       (E2Addr_Rev_Ac_De_Over_Degree+CLRev_Ac_De_Over_Degree+C_CRCLen2)      /*�����й������������ۼ�ʱ��*/

#define E2Addr_Qua1_Re_De_Over_Degree    (E2Addr_Rev_Ac_De_Over_Time+CLRev_Ac_De_Over_Time+C_CRCLen2)          /*1�����޹����������ܴ���*/
#define E2Addr_Qua1_Re_De_Over_Time      (E2Addr_Qua1_Re_De_Over_Degree+CLQua1_Re_De_Over_Degree+C_CRCLen2)    /*1�����޹������������ۼ�ʱ��*/
#define E2Addr_Qua2_Re_De_Over_Degree    (E2Addr_Qua1_Re_De_Over_Time+CLQua1_Re_De_Over_Time+C_CRCLen2)        /*2�����޹����������ܴ���*/
#define E2Addr_Qua2_Re_De_Over_Time      (E2Addr_Qua2_Re_De_Over_Degree+CLQua2_Re_De_Over_Degree+C_CRCLen2)    /*2�����޹������������ۼ�ʱ��*/
#define E2Addr_Qua3_Re_De_Over_Degree    (E2Addr_Qua2_Re_De_Over_Time+CLQua2_Re_De_Over_Time+C_CRCLen2)        /*3�����޹����������ܴ���*/
#define E2Addr_Qua3_Re_De_Over_Time      (E2Addr_Qua3_Re_De_Over_Degree+CLQua3_Re_De_Over_Degree+C_CRCLen2)    /*3�����޹������������ۼ�ʱ��*/
#define E2Addr_Qua4_Re_De_Over_Degree    (E2Addr_Qua3_Re_De_Over_Time+CLQua3_Re_De_Over_Time+C_CRCLen2)        /*4�����޹����������ܴ���*/
#define E2Addr_Qua4_Re_De_Over_Time      (E2Addr_Qua4_Re_De_Over_Degree+CLQua4_Re_De_Over_Degree+C_CRCLen2)    /*4�����޹������������ۼ�ʱ��*/

#define E2Addr_LossA_Vol_Degree          (E2Addr_Qua4_Re_De_Over_Time+CLQua4_Re_De_Over_Time+C_CRCLen2)        /*A��ʧѹ�ܴ���*/
#define E2Addr_LossA_Vol_Time            (E2Addr_LossA_Vol_Degree+CLLossA_Vol_Degree+C_CRCLen2)                /*A��ʧѹ���ۼ�ʱ��*/
#define E2Addr_LossB_Vol_Degree          (E2Addr_LossA_Vol_Time+CLLossA_Vol_Time+C_CRCLen2)                    /*B��ʧѹ�ܴ���*/
#define E2Addr_LossB_Vol_Time            (E2Addr_LossB_Vol_Degree+CLLossB_Vol_Degree+C_CRCLen2)                /*B��ʧѹ���ۼ�ʱ��*/
#define E2Addr_LossC_Vol_Degree          (E2Addr_LossB_Vol_Time+CLLossB_Vol_Time+C_CRCLen2)                    /*C��ʧѹ�ܴ���*/
#define E2Addr_LossC_Vol_Time            (E2Addr_LossC_Vol_Degree+CLLossC_Vol_Degree+C_CRCLen2)                /*C��ʧѹ���ۼ�ʱ��*/

#define E2Addr_LowA_Vol_Degree           (E2Addr_LossC_Vol_Time+CLLossC_Vol_Time+C_CRCLen2)                    /*A��Ƿѹ�ܴ���*/
#define E2Addr_LowA_Vol_Time             (E2Addr_LowA_Vol_Degree+CLLowA_Vol_Degree+C_CRCLen2)                  /*A��Ƿѹ���ۼ�ʱ��*/
#define E2Addr_LowB_Vol_Degree           (E2Addr_LowA_Vol_Time+CLLowA_Vol_Time+C_CRCLen2)                      /*B��Ƿѹ�ܴ���*/
#define E2Addr_LowB_Vol_Time             (E2Addr_LowB_Vol_Degree+CLLowB_Vol_Degree+C_CRCLen2)                  /*B��Ƿѹ���ۼ�ʱ��*/
#define E2Addr_LowC_Vol_Degree           (E2Addr_LowB_Vol_Time+CLLowB_Vol_Time+C_CRCLen2)                      /*C��Ƿѹ�ܴ���*/
#define E2Addr_LowC_Vol_Time             (E2Addr_LowC_Vol_Degree+CLLowC_Vol_Degree+C_CRCLen2)                  /*C��Ƿѹ���ۼ�ʱ��*/

#define E2Addr_OverA_Vol_Degree          (E2Addr_LowC_Vol_Time+CLLowC_Vol_Time+C_CRCLen2)                      /*A���ѹ�ܴ���*/
#define E2Addr_OverA_Vol_Time            (E2Addr_OverA_Vol_Degree+CLOverA_Vol_Degree+C_CRCLen2)                /*A���ѹ���ۼ�ʱ��*/
#define E2Addr_OverB_Vol_Degree          (E2Addr_OverA_Vol_Time+CLOverA_Vol_Time+C_CRCLen2)                    /*B���ѹ�ܴ���*/
#define E2Addr_OverB_Vol_Time            (E2Addr_OverB_Vol_Degree+CLOverB_Vol_Degree+C_CRCLen2)                /*B���ѹ���ۼ�ʱ��*/
#define E2Addr_OverC_Vol_Degree          (E2Addr_OverB_Vol_Time+CLOverB_Vol_Time+C_CRCLen2)                    /*C���ѹ�ܴ���*/
#define E2Addr_OverC_Vol_Time            (E2Addr_OverC_Vol_Degree+CLOverC_Vol_Degree+C_CRCLen2)                /*C���ѹ���ۼ�ʱ��*/

#define E2Addr_BreakA_Vol_Degree         (E2Addr_OverC_Vol_Time+CLOverC_Vol_Time+C_CRCLen2)                    /*A������ܴ���*/
#define E2Addr_BreakA_Vol_Time           (E2Addr_BreakA_Vol_Degree+CLBreakA_Vol_Degree+C_CRCLen2)              /*A��������ۼ�ʱ��*/
#define E2Addr_BreakB_Vol_Degree         (E2Addr_BreakA_Vol_Time+CLBreakA_Vol_Time+C_CRCLen2)                  /*B������ܴ���*/
#define E2Addr_BreakB_Vol_Time           (E2Addr_BreakB_Vol_Degree+CLBreakB_Vol_Degree+C_CRCLen2)              /*B��������ۼ�ʱ��*/
#define E2Addr_BreakC_Vol_Degree         (E2Addr_BreakB_Vol_Time+CLBreakB_Vol_Time+C_CRCLen2)                  /*C������ܴ���*/
#define E2Addr_BreakC_Vol_Time           (E2Addr_BreakC_Vol_Degree+CLBreakC_Vol_Degree+C_CRCLen2)              /*C��������ۼ�ʱ��*/

#define E2Addr_RevPS_Vol_Degree          (E2Addr_BreakC_Vol_Time+CLBreakC_Vol_Time+C_CRCLen2)                  /*��ѹ�������ܴ���*/
#define E2Addr_RevPS_Vol_Time            (E2Addr_RevPS_Vol_Degree+CLRevPS_Vol_Degree+C_CRCLen2)                /*��ѹ���������ۼ�ʱ��*/

#define E2Addr_RevPS_Curr_Degree         (E2Addr_RevPS_Vol_Time+CLRevPS_Vol_Time+C_CRCLen2)                    /*�����������ܴ���*/
#define E2Addr_RevPS_Curr_Time           (E2Addr_RevPS_Curr_Degree+CLRevPS_Curr_Degree+C_CRCLen2)              /*�������������ۼ�ʱ��*/

#define E2Addr_NoBal_Vol_Degree          (E2Addr_RevPS_Curr_Time+CLRevPS_Curr_Time+C_CRCLen2)                  /*��ѹ��ƽ���ܴ���*/
#define E2Addr_NoBal_Vol_Time            (E2Addr_NoBal_Vol_Degree+CLNoBal_Vol_Degree+C_CRCLen2)                /*��ѹ��ƽ�����ۼ�ʱ��*/

#define E2Addr_NoBal_Curr_Degree         (E2Addr_NoBal_Vol_Time+CLNoBal_Vol_Time+C_CRCLen2)                    /*������ƽ���ܴ���*/
#define E2Addr_NoBal_Curr_Time           (E2Addr_NoBal_Curr_Degree+CLNoBal_Curr_Degree+C_CRCLen2)              /*������ƽ�����ۼ�ʱ��*/

#define E2Addr_SevNoBal_Curr_Degree      (E2Addr_NoBal_Curr_Time+CLNoBal_Curr_Time+C_CRCLen2)                  /*�������ز�ƽ���ܴ���*/
#define E2Addr_SevNoBal_Curr_Time        (E2Addr_SevNoBal_Curr_Degree+CLSevNoBal_Curr_Degree+C_CRCLen2)        /*�������ز�ƽ�����ۼ�ʱ��*/

#define E2Addr_LossA_Curr_Degree         (E2Addr_SevNoBal_Curr_Time+CLSevNoBal_Curr_Time+C_CRCLen2)            /*A��ʧ���ܴ���*/
#define E2Addr_LossA_Curr_Time           (E2Addr_LossA_Curr_Degree+CLLossA_Curr_Degree+C_CRCLen2)              /*A��ʧ�����ۼ�ʱ��*/
#define E2Addr_LossB_Curr_Degree         (E2Addr_LossA_Curr_Time+CLLossA_Curr_Time+C_CRCLen2)                  /*B��ʧ���ܴ���*/
#define E2Addr_LossB_Curr_Time           (E2Addr_LossB_Curr_Degree+CLLossB_Curr_Degree+C_CRCLen2)              /*B��ʧ�����ۼ�ʱ��*/
#define E2Addr_LossC_Curr_Degree         (E2Addr_LossB_Curr_Time+CLLossB_Curr_Time+C_CRCLen2)                  /*C��ʧ���ܴ���*/
#define E2Addr_LossC_Curr_Time           (E2Addr_LossC_Curr_Degree+CLLossC_Curr_Degree+C_CRCLen2)              /*C��ʧ�����ۼ�ʱ��*/

#define E2Addr_OverA_Curr_Degree         (E2Addr_LossC_Curr_Time+CLLossC_Curr_Time+C_CRCLen2)                  /*A������ܴ���*/
#define E2Addr_OverA_Curr_Time           (E2Addr_OverA_Curr_Degree+CLOverA_Curr_Degree+C_CRCLen2)              /*A��������ۼ�ʱ��*/
#define E2Addr_OverB_Curr_Degree         (E2Addr_OverA_Curr_Time+CLOverA_Curr_Time+C_CRCLen2)                  /*B������ܴ���*/
#define E2Addr_OverB_Curr_Time           (E2Addr_OverB_Curr_Degree+CLOverB_Curr_Degree+C_CRCLen2)              /*B��������ۼ�ʱ��*/
#define E2Addr_OverC_Curr_Degree         (E2Addr_OverB_Curr_Time+CLOverB_Curr_Time+C_CRCLen2)                  /*C������ܴ���*/
#define E2Addr_OverC_Curr_Time           (E2Addr_OverC_Curr_Degree+CLOverC_Curr_Degree+C_CRCLen2)              /*C��������ۼ�ʱ��*/

#define E2Addr_BreakA_Curr_Degree        (E2Addr_OverC_Curr_Time+CLOverC_Curr_Time+C_CRCLen2)                  /*A������ܴ���*/
#define E2Addr_BreakA_Curr_Time          (E2Addr_BreakA_Curr_Degree+CLBreakA_Curr_Degree+C_CRCLen2)            /*A��������ۼ�ʱ��*/
#define E2Addr_BreakB_Curr_Degree        (E2Addr_BreakA_Curr_Time+CLBreakA_Curr_Time+C_CRCLen2)                /*B������ܴ���*/
#define E2Addr_BreakB_Curr_Time          (E2Addr_BreakB_Curr_Degree+CLBreakB_Curr_Degree+C_CRCLen2)            /*B��������ۼ�ʱ��*/
#define E2Addr_BreakC_Curr_Degree        (E2Addr_BreakB_Curr_Time+CLBreakB_Curr_Time+C_CRCLen2)                /*C������ܴ���*/
#define E2Addr_BreakC_Curr_Time          (E2Addr_BreakC_Curr_Degree+CLBreakC_Curr_Degree+C_CRCLen2)            /*C��������ۼ�ʱ��*/

#define E2Addr_PowerT_Rev_Degree         (E2Addr_BreakC_Curr_Time+CLBreakC_Curr_Time+C_CRCLen2)                /*�ܹ��ʷ����ܴ���*/
#define E2Addr_PowerT_Rev_Time           (E2Addr_PowerT_Rev_Degree+CLPowerT_Rev_Degree+C_CRCLen2)              /*�ܹ��ʷ������ۼ�ʱ��*/
#define E2Addr_PowerA_Rev_Degree         (E2Addr_PowerT_Rev_Time+CLPowerT_Rev_Time+C_CRCLen2)                  /*A�๦�ʷ����ܴ���*/
#define E2Addr_PowerA_Rev_Time           (E2Addr_PowerA_Rev_Degree+CLPowerA_Rev_Degree+C_CRCLen2)              /*A�๦�ʷ������ۼ�ʱ��*/
#define E2Addr_PowerB_Rev_Degree         (E2Addr_PowerA_Rev_Time+CLPowerA_Rev_Time+C_CRCLen2)                  /*B�๦�ʷ����ܴ���*/
#define E2Addr_PowerB_Rev_Time           (E2Addr_PowerB_Rev_Degree+CLPowerB_Rev_Degree+C_CRCLen2)              /*B�๦�ʷ������ۼ�ʱ��*/
#define E2Addr_PowerC_Rev_Degree         (E2Addr_PowerB_Rev_Time+CLPowerB_Rev_Time+C_CRCLen2)                  /*C�๦�ʷ����ܴ���*/
#define E2Addr_PowerC_Rev_Time           (E2Addr_PowerC_Rev_Degree+CLPowerC_Rev_Degree+C_CRCLen2)              /*C�๦�ʷ������ۼ�ʱ��*/

#define E2Addr_OverA_Lo_Degree           (E2Addr_PowerC_Rev_Time+CLPowerC_Rev_Time+C_CRCLen2)                  /*A������ܴ���*/
#define E2Addr_OverA_Lo_Time             (E2Addr_OverA_Lo_Degree+CLOverA_Lo_Degree+C_CRCLen2)                  /*A��������ۼ�ʱ��*/
#define E2Addr_OverB_Lo_Degree           (E2Addr_OverA_Lo_Time+CLOverA_Lo_Time+C_CRCLen2)                      /*B������ܴ���*/
#define E2Addr_OverB_Lo_Time             (E2Addr_OverB_Lo_Degree+CLOverB_Lo_Degree+C_CRCLen2)                  /*B��������ۼ�ʱ��*/
#define E2Addr_OverC_Lo_Degree           (E2Addr_OverB_Lo_Time+CLOverB_Lo_Time+C_CRCLen2)                      /*C������ܴ���*/
#define E2Addr_OverC_Lo_Time             (E2Addr_OverC_Lo_Degree+CLOverC_Lo_Degree+C_CRCLen2)                  /*C��������ۼ�ʱ��*/

#define E2Addr_PFactorT_Over_Degree      (E2Addr_OverC_Lo_Time+CLOverC_Lo_Time+C_CRCLen2)                      /*�ܹ��������������ܴ���*/
#define E2Addr_PFactorT_Over_Time        (E2Addr_PFactorT_Over_Degree+CLPFactorT_Over_Degree+C_CRCLen2)        /*�ܹ����������������ۼ�ʱ��*/
#define E2Addr_PFactorA_Over_Degree      (E2Addr_PFactorT_Over_Time+CLPFactorT_Over_Time+C_CRCLen2)            /*A���������������ܴ���*/
#define E2Addr_PFactorA_Over_Time        (E2Addr_PFactorA_Over_Degree+CLPFactorA_Over_Degree+C_CRCLen2)        /*A�����������������ۼ�ʱ��*/
#define E2Addr_PFactorB_Over_Degree      (E2Addr_PFactorA_Over_Time+CLPFactorA_Over_Time+C_CRCLen2)            /*B���������������ܴ���*/
#define E2Addr_PFactorB_Over_Time        (E2Addr_PFactorB_Over_Degree+CLPFactorB_Over_Degree+C_CRCLen2)        /*B�����������������ۼ�ʱ��*/
#define E2Addr_PFactorC_Over_Degree      (E2Addr_PFactorB_Over_Time+CLPFactorB_Over_Time+C_CRCLen2)            /*C���������������ܴ���*/
#define E2Addr_PFactorC_Over_Time        (E2Addr_PFactorC_Over_Degree+CLPFactorC_Over_Degree+C_CRCLen2)        /*C�����������������ۼ�ʱ��*/

#define E2Addr_NeutralCurrentAbnormal_Degree    (E2Addr_PFactorC_Over_Time+CLPFactorC_Over_Time+C_CRCLen2)     /*���ߵ����쳣�ܴ���*/
#define E2Addr_NeutralCurrentAbnormal_Time      (E2Addr_NeutralCurrentAbnormal_Degree+CLNeutralCurrentAbnormal_Degree+C_CRCLen2)    /*���ߵ����쳣���ۼ�ʱ��*/

/**************�����*******************/
#define E2Addr_De_Clear_Degree           (E2Addr_NeutralCurrentAbnormal_Time+CLNeutralCurrentAbnormal_Time+C_CRCLen2)    /*���������ܴ���*/
#define E2Addr_RelayClose_Degree         (E2Addr_De_Clear_Degree+CLDe_Clear_Degree+C_CRCLen2)                 /*��բ��¼�ܴ���*/
#define E2Addr_Program_Degree            (E2Addr_RelayClose_Degree+CLRelayClose_Degree+C_CRCLen2)             /*��̼�¼�ܴ���*/
#define E2Addr_AdjTime_Degree            (E2Addr_Program_Degree+CLProgram_Degree+C_CRCLen2)                   /*Уʱ��¼�ܴ���*/
#define E2Addr_BroadcastTime_Degree      (E2Addr_AdjTime_Degree+CLAdjTime_Degree+C_CRCLen2)                   /*�㲥Уʱ��¼�ܴ���*/
#define E2Addr_ProgPT_Degree             (E2Addr_BroadcastTime_Degree+CLBroadcastTime_Degree+C_CRCLen2)       /*ʱ�α��̼�¼�ܴ���*/
#define E2Addr_ProgTZ_Degree             (E2Addr_ProgPT_Degree+CLProgPT_Degree+C_CRCLen2)                     /*ʱ�����̼�¼�ܴ���*/
#define E2Addr_ProgWRe_Degree            (E2Addr_ProgTZ_Degree+CLProgTZ_Degree+C_CRCLen2)                     /*�����ձ�̼�¼�ܴ���*/
#define E2Addr_ProgHol_Degree            (E2Addr_ProgWRe_Degree+CLProgWRe_Degree+C_CRCLen2)                   /*�ڼ��ձ�̼�¼�ܴ���*/
#define E2Addr_ProgAcC_Degree            (E2Addr_ProgHol_Degree+CLProgHol_Degree+C_CRCLen2)                   /*�й���Ϸ�ʽ��̼�¼�ܴ���*/
#define E2Addr_ProgReC1_Degree           (E2Addr_ProgAcC_Degree+CLProgAcC_Degree+C_CRCLen2)                   /*�޹���Ϸ�ʽ1��̼�¼�ܴ���*/
#define E2Addr_ProgSettD_Degree          (E2Addr_ProgReC1_Degree+CLProgReC_Degree+C_CRCLen2)                  /*�����ձ�̼�¼�ܴ���*/
#define E2Addr_ProgTPara_Degree          (E2Addr_ProgSettD_Degree+CLProgSettD_Degree+C_CRCLen2)               /*���ʲ������̼�¼�ܴ���*/
#define E2Addr_ProgLad_Degree            (E2Addr_ProgTPara_Degree+CLProgTPara_Degree+C_CRCLen2)               /*���ݱ��̼�¼�ܴ���*/
#define E2Addr_ProgKD_Degree             (E2Addr_ProgLad_Degree+CLProgLad_Degree+C_CRCLen2)                   /*��Կ��̼�¼�ܴ���*/
#define E2Addr_AbnorC_Degree             (E2Addr_ProgKD_Degree+CLProgKD_Degree+C_CRCLen2)                     /*�쳣�忨��¼�ܴ���*/

#define E2Addr_OpenW_Degree              (E2Addr_AbnorC_Degree+CLAbnorC_Degree+C_CRCLen2)                     /*����Ǽ�¼�ܴ���*/
#define E2Addr_OpenW_Time	             (E2Addr_OpenW_Degree+CLOpenW_Degree+C_CRCLen2)                       /*����Ǽ�¼�ۼ�ʱ��*/

#define E2Addr_OpenCW_Degree             (E2Addr_OpenW_Time+CLOpenW_Time+C_CRCLen2)                           /*����ť�Ǽ�¼�ܴ���*/
#define E2Addr_OpenCW_Time               (E2Addr_OpenCW_Degree+CLOpenCW_Degree+C_CRCLen2)                     /*����ť���ۼ�ʱ��*/

#define E2Addr_BuyCurr_Degree            (E2Addr_OpenCW_Time+CLOpenCW_Time+C_CRCLen2)                         /*�����¼�ܴ���*/
#define E2Addr_Return_M_Degree           (E2Addr_BuyCurr_Degree+CLBuyCurr_Degree+C_CRCLen2)                   /*�˷Ѽ�¼�ܴ���*/
#define E2Addr_LawlessC_Degree           (E2Addr_Return_M_Degree+CLReturn_M_Degree+C_CRCLen2)                 /*�Ƿ��忨�ܴ���,���¼���¼*/

#define E2Addr_ConM_Degree               (E2Addr_LawlessC_Degree+CLLawlessC_Degree+C_CRCLen2)                 /*�㶨�ų����ż�¼�ܴ���*/
#define E2Addr_ConM_Time                 (E2Addr_ConM_Degree+CLConM_Degree+C_CRCLen2)                         /*�㶨�ų����ż�¼�ۼ�ʱ��*/

#define E2Addr_RelayFa_Degree            (E2Addr_ConM_Time+CLConM_Time+C_CRCLen2)                             /*���ɿ���������¼�ܴ���*/
#define E2Addr_RelayFa_Time              (E2Addr_RelayFa_Degree+CLRelayFa_Degree+C_CRCLen2)                   /*���ɿ���������¼�ۼ�ʱ��*/

#define E2Addr_PowerFa_Degree            (E2Addr_RelayFa_Time+CLRelayFa_Time+C_CRCLen2)                       /*��Դ�쳣��¼�ܴ���*/
#define E2Addr_PowerFa_Time              (E2Addr_PowerFa_Degree+CLPowerFa_Degree+C_CRCLen2)                   /*��Դ�쳣��¼���ۼ�ʱ��*/

#define E2Addr_MeterFa_Degree            (E2Addr_PowerFa_Time+CLPowerFa_Time+C_CRCLen2)                       /*����оƬ�쳣��¼�ܴ���*/
#define E2Addr_MeterFa_Time              (E2Addr_MeterFa_Degree+CLMeterFa_Degree+C_CRCLen2)                   /*����оƬ�쳣��¼���ۼ�ʱ��*/

#define E2Addr_ClockFa_Degree            (E2Addr_MeterFa_Time+CLMeterFa_Time+C_CRCLen2)                       /*ʱ�ӹ����쳣��¼�ܴ���*/
#define E2Addr_ClockFa_Time              (E2Addr_ClockFa_Degree+CLClockFa_Degree+C_CRCLen2)                   /*ʱ�ӹ����쳣��¼���ۼ�ʱ��*/

#define E2Addr_RelayOpen_Degree          (E2Addr_ClockFa_Time+CLClockFa_Time+C_CRCLen2)                       /*��բ��¼�ܴ���*/

#define E2Addr_Soft_I_J_Prog_Degree      (E2Addr_RelayOpen_Degree+CLRelayOpen_Degree+C_CRCLen2)               /*��IJ��Чʱ�����ܴ���,����Ϊ3�ֽڣ�����д��¼���⴦��*/

#define E2Addr_Even_Clear_Degree         (E2Addr_Soft_I_J_Prog_Degree+CLSoft_I_J_Prog_Degree+C_CRCLen2)       /*�¼������ܴ���,���¼���¼E2�洢�ռ���󣬷����¼���¼����*/

#define E2Addr_EventNote_End_OutTol      E2Addr_Even_Clear_Degree                                             /*�¼���¼E2�洢������ַ,�������¼������ܴ���*/

#define E2Addr_Rec_Meter_Degree          (E2Addr_Even_Clear_Degree+CLEven_Clear_Degree+C_CRCLen2)             /*У���ܴ���������Ϊ3�ֽڣ�����д��¼���⴦��*/

#define E2Addr_EventNote_End             E2Addr_Rec_Meter_Degree                                              /*�¼���¼E2�洢������ַ,������У���¼����*/

#define E2Addr_Tol_Clear_Out_End         (E2Addr_Rec_Meter_Degree+CLRec_Meter_Degree+C_CRCLen2)               /*���峧��ģʽ������ַ*/
#define E2Addr_Tol_Clear_Degree          (E2Addr_Rec_Meter_Degree+CLRec_Meter_Degree+C_CRCLen2)               /*��������ܴ���,��E2������󣬷������峧�ڡ���������*/
#define E2Addr_Tol_Clear_In_End          (E2Addr_Tol_Clear_Degree+CLTol_Clear_Degree+C_CRCLen2)               /*���峧��ģʽ������ַ*/

/**************************************�α���******************************************/
#define E2Addr_Demand_Cycle              (E2Addr_Tol_Clear_Degree+CLTol_Clear_Degree+C_CRCLen2)                    /*�����������*/
#define E2Addr_Sliding_Time              (E2Addr_Demand_Cycle+CLDemand_Cycle+C_CRCLen2)                            /*����ʱ��*/

#define E2Addr_BroadcastTimeOffset_Min   (E2Addr_Sliding_Time+CLSliding_Time+C_CRCLen2)                            /*�㲥Уʱƫ����Сֵ*/
#define E2Addr_BroadcastTimeOffset_Max   (E2Addr_BroadcastTimeOffset_Min+CLBroadcastTimeOffset_Min+C_CRCLen2)      /*�㲥Уʱƫ�����ֵ*/

#define E2Addr_Change_TZ_Time            (E2Addr_BroadcastTimeOffset_Max+CLBroadcastTimeOffset_Max+C_CRCLen2)      /*����ʱ�����л�ʱ��*/
#define E2Addr_Change_PT_Time            (E2Addr_Change_TZ_Time+CLChange_TZ_Time+C_CRCLen2)                        /*������ʱ�α��л�ʱ��*/
#define E2Addr_Change_Rate               (E2Addr_Change_PT_Time+CLChange_PT_Time+C_CRCLen2)                        /*���׷��ʵ���л�ʱ��*/
#define E2Addr_Change_Ladder             (E2Addr_Change_Rate+CLChange_Rate+C_CRCLen2)                              /*���׽��ݵ���л�ʱ��*/

#define E2Addr_Year_Zone_Num             (E2Addr_Change_Ladder+CLChange_Ladder+C_CRCLen2)                          /*��ʱ����*/
#define E2Addr_Day_Table_Num             (E2Addr_Year_Zone_Num+CLYear_Zone_Num+C_CRCLen2)                          /*��ʱ�α���*/
#define E2Addr_Day_Time_Num              (E2Addr_Day_Table_Num+CLDay_Table_Num+C_CRCLen2)                          /*��ʱ����*/
#define E2Addr_Rate_Num                  (E2Addr_Day_Time_Num+CLDay_Time_Num+C_CRCLen2)                            /*������*/
#define E2Addr_Holiday_Num               (E2Addr_Rate_Num+CLRate_Num+C_CRCLen2)                                    /*����������*/

#define E2Addr_Step_Num                  (E2Addr_Holiday_Num+CLHoliday_Num+C_CRCLen2)                              /*������*/

#define E2Addr_Per_Dis_Screen_Time       (E2Addr_Step_Num+CLStep_Num+C_CRCLen2)                                    /*ѭ��ÿ����ʾʱ��*/
#define E2Addr_Auto_Dis_Screen_Num       (E2Addr_Per_Dis_Screen_Time+CLPer_Dis_Screen_Time+C_CRCLen2)              /*ѭ������*/
#define E2Addr_Auto_Dis_Screen_MaxNum    (E2Addr_Auto_Dis_Screen_Num+CLAuto_Dis_Screen_Num+C_CRCLen2)              /*ѭ���������*/

#define E2Addr_Perkey_Dis_Screen_Time    (E2Addr_Auto_Dis_Screen_MaxNum+CLAuto_Dis_Screen_MaxNum+C_CRCLen2)        /*����ÿ����ʾʱ��*/
#define E2Addr_Key_CycDis_Screen_Num     (E2Addr_Perkey_Dis_Screen_Time+CLPerkey_Dis_Screen_Time+C_CRCLen2)        /*��������*/
#define E2Addr_Key_CycDis_Screen_MaxNum  (E2Addr_Key_CycDis_Screen_Num+CLKey_CycDis_Screen_Num+C_CRCLen2)          /*�����������*/

#define E2Addr_PowerOn_Dis_All_Time      (E2Addr_Key_CycDis_Screen_MaxNum+CLKey_CycDis_Screen_MaxNum+C_CRCLen2)    /*�ϵ�ȫ��ʱ��*/
#define E2Addr_BacklightTime             (E2Addr_PowerOn_Dis_All_Time+CLPowerOn_Dis_All_Time+C_CRCLen2)            /*�������ʱ��*/
#define E2Addr_SViewBacklightTime        (E2Addr_BacklightTime+CLBacklightTime+C_CRCLen2)                          /*��ʾ�鿴�������ʱ��*/
#define E2Addr_NEScreenDisplay           (E2Addr_SViewBacklightTime+CLSViewBacklightTime+C_CRCLen2)                /*�޵簴����Ļפ�����ʱ��*/
#define E2Addr_Energy_Decimal_Num        (E2Addr_NEScreenDisplay+CLNEScreenDisplay+C_CRCLen2)                      /*����С��λ��*/
#define E2Addr_Power_Decimal_Num         (E2Addr_Energy_Decimal_Num+CLEnergy_Decimal_Num+C_CRCLen2)                /*��ʾ���ʣ����������С��λ��*/
#define E2Addr_1And2Display              (E2Addr_Power_Decimal_Num+CLPower_Decimal_Num+C_CRCLen2)                  /*Һ���٢���������*/

#define E2Addr_Ratio_Curr_Tran           (E2Addr_1And2Display+CL1And2Display+C_CRCLen2)                      /*�������������*/
#define E2Addr_Ratio_Vol_Tran            (E2Addr_Ratio_Curr_Tran+CLRatio_Curr_Tran+C_CRCLen2)                /*��ѹ���������*/
#define E2Addr_Comm_Address              (E2Addr_Ratio_Vol_Tran+CLRatio_Vol_Tran+C_CRCLen2)                  /*ͨѶ��ַ*/
#define E2Addr_Meter_Num                 (E2Addr_Comm_Address+CLComm_Address+C_CRCLen2)                      /*���*/
#define E2Addr_Manage_Code               (E2Addr_Meter_Num+CLMeter_Num+C_CRCLen2)                            /*�ʲ��������*/
#define E2Addr_Rated_Vol                 (E2Addr_Manage_Code+CLManage_Code+C_CRCLen2)                        /*���ѹ*/
#define E2Addr_Rated_Curr                (E2Addr_Rated_Vol+CLRated_Vol+C_CRCLen2)                            /*�����/��������*/
#define E2Addr_Max_Curr                  (E2Addr_Rated_Curr+CLRated_Curr+C_CRCLen2)                          /*������*/
#define E2Addr_Min_Curr                  (E2Addr_Max_Curr+CLMax_Curr+C_CRCLen2)                              /*��С����*/
#define E2Addr_Turn_Curr                 (E2Addr_Min_Curr+CLMin_Curr+C_CRCLen2)                              /*ת�۵���*/
#define E2Addr_Active_Accur_Deg          (E2Addr_Turn_Curr+CLTurn_Curr+C_CRCLen2)                            /*�й�׼ȷ�ȵȼ�*/
#define E2Addr_Reactive_Accur_Deg        (E2Addr_Active_Accur_Deg+CLActive_Accur_Deg+C_CRCLen2)              /*�޹�׼ȷ�ȵȼ�*/
#define E2Addr_Meter_Ac_Const            (E2Addr_Reactive_Accur_Deg+CLReactive_Accur_Deg+C_CRCLen2)          /*����й�����*/
#define E2Addr_Meter_Re_Const            (E2Addr_Meter_Ac_Const+CLMeter_Ac_Const+C_CRCLen2)                  /*������޹�����*/
#define E2Addr_Meter_Model               (E2Addr_Meter_Re_Const+CLMeter_Re_Const+C_CRCLen2)                  /*����ͺ�*/

/*���Ƿ�����E2һ��*/
#define E2Addr_Prod_Date                 (E2Addr_Meter_Model+CLMeter_Model+C_CRCLen2)                        /*��������*/
#define E2Addr_Prot_Version_Num          (E2Addr_Prod_Date+CLProd_Date+C_CRCLen2)                            /*Э��汾��*/

#define E2Addr_Customer_Num              (E2Addr_Prot_Version_Num+CLProt_Version_Num+C_CRCLen2)              /*�ͻ����*/
#define E2Addr_Meter_Position            (E2Addr_Customer_Num+CLCustomer_Num+C_CRCLen2)                      /*���ܱ�λ����Ϣ:���ȡ�γ�ȡ��߶�*/

#define E2Addr_Active_Com_State          (E2Addr_Meter_Position+CLMeter_Position+C_CRCLen2)                  /*�й����״̬��*/
#define E2Addr_Reactive_Com_State1       (E2Addr_Active_Com_State+CLActive_Com_State+C_CRCLen2)              /*�޹����״̬��1*/
#define E2Addr_Reactive_Com_State2       (E2Addr_Reactive_Com_State1+CLReactive_Com_State1+C_CRCLen2)        /*�޹����״̬��2*/

#define E2Addr_Mod_InFr_Baud             (E2Addr_Reactive_Com_State2+CLReactive_Com_State2+C_CRCLen2)        /*�����ͺ����ڲ�����������*/
#define E2Addr_One485_Baud               (E2Addr_Mod_InFr_Baud+CLMod_InFr_Baud+C_CRCLen2)                    /*1·485������������*/
#define E2Addr_Two485_Baud               (E2Addr_One485_Baud+CLOne485_Baud+C_CRCLen2)                        /*2·485������������*/
#define E2Addr_Modular_Baud              (E2Addr_Two485_Baud+CLTwo485_Baud+C_CRCLen2)                        /*ģ��ͨ��������������*/

#define E2Addr_Week_RestDay              (E2Addr_Modular_Baud+CLModular_Baud+C_CRCLen2)                      /*������������*/
#define E2Addr_Week_RestDay_DTable       (E2Addr_Week_RestDay+CLWeek_RestDay+C_CRCLen2)                      /*�����ղ�ȡ����ʱ�α��*/

#define E2Addr_Settle_Day1               (E2Addr_Week_RestDay_DTable+CLWeek_RestDay_DTable+C_CRCLen2)        /*ÿ�µ�1������*/
#define E2Addr_Settle_Day2               (E2Addr_Settle_Day1+CLSettle_Day1+C_CRCLen2)                        /*ÿ�µ�2������*/
#define E2Addr_Settle_Day3               (E2Addr_Settle_Day2+CLSettle_Day2+C_CRCLen2)                        /*ÿ�µ�3������*/

#define E2Addr_Key_0_Class               (E2Addr_Settle_Day3+CLSettle_Day3+C_CRCLen2)                        /*0������*/
#define E2Addr_Key_1_Class               (E2Addr_Key_0_Class+CLKey_0_Class+C_CRCLen2)                        /*1������*/
#define E2Addr_Key_2_Class               (E2Addr_Key_1_Class+CLKey_1_Class+C_CRCLen2)                        /*2������*/
#define E2Addr_Key_3_Class               (E2Addr_Key_2_Class+CLKey_2_Class+C_CRCLen2)                        /*3������*/
#define E2Addr_Key_4_Class               (E2Addr_Key_3_Class+CLKey_3_Class+C_CRCLen2)                        /*4������*/

#if 0		/*645���������0-4�ܼ���Ӧ����*/
#define E2Addr_Key_5_Class               (E2Addr_Key_4_Class+CLKey_4_Class+C_CRCLen2)                        /*5������*/
#define E2Addr_Key_6_Class               (E2Addr_Key_5_Class+CLKey_5_Class+C_CRCLen2)                        /*6������*/
#define E2Addr_Key_7_Class               (E2Addr_Key_6_Class+CLKey_6_Class+C_CRCLen2)                        /*7������*/
#define E2Addr_Key_8_Class               (E2Addr_Key_7_Class+CLKey_7_Class+C_CRCLen2)                        /*8������*/
#define E2Addr_Key_9_Class               (E2Addr_Key_8_Class+CLKey_8_Class+C_CRCLen2)                        /*9������*/

#define E2Addr_Alam1_Money               (E2Addr_Key_9_Class+CLKey_9_Class+C_CRCLen2)                        /*�������1��ֵ*/
#endif

#define E2Addr_Alam1_Money               (E2Addr_Key_4_Class+CLKey_4_Class+C_CRCLen2)                        /*�������1��ֵ*/
#define E2Addr_Alam2_Money               (E2Addr_Alam1_Money+CLAlam1_Money+C_CRCLen2)                        /*�������2��ֵ*/

#define E2Addr_OverDraft_Money           (E2Addr_Alam2_Money+CLAlam2_Money+C_CRCLen2)                        /*͸֧�����ֵ*/
#define E2Addr_Hoarding_Money            (E2Addr_OverDraft_Money+CLOverDraft_Money+C_CRCLen2)                /*�ڻ������ֵ*/
#define E2Addr_Close_Relay_Money         (E2Addr_Hoarding_Money+CLHoarding_Money+C_CRCLen2)                  /*��բ��������ֵ*/

#define E2Addr_Return_Money              (E2Addr_Close_Relay_Money+CLClose_Relay_Money+C_CRCLen2)            /*�˷ѽ��*/

#define E2Addr_Drive_Report_Mode         (E2Addr_Return_Money+CLReturn_Money+C_CRCLen2)                      /*�����ϱ�ģʽ��*/

//#define E2Addr_Relay_Delay_Time          (E2Addr_Drive_Report_Mode+CLDrive_Report_Mode+C_CRCLen2)          /*��բ��ʱʱ��*/
#define E2Addr_Relay_Open_CurrTreshold   (E2Addr_Drive_Report_Mode+CLDrive_Report_Mode+C_CRCLen2)            /*�̵�����բ���Ƶ�������ֵ*/

#define E2Addr_First_TZone_Data          (E2Addr_Relay_Open_CurrTreshold+CLRelay_Open_CurrTreshold+C_CRCLen2)    /*��һ��ʱ��������*/
#define E2Addr_First_TZone_1PT_Data      (E2Addr_First_TZone_Data+CLFirst_TZone_Data+C_CRCLen2)              /*��һ�׵�1��ʱ�α�����*/
#define E2Addr_First_TZone_2PT_Data      (E2Addr_First_TZone_1PT_Data+CLFirst_TZone_1PT_Data+C_CRCLen2)      /*��һ�׵�2��ʱ�α�����*/
#define E2Addr_First_TZone_3PT_Data      (E2Addr_First_TZone_2PT_Data+CLFirst_TZone_2PT_Data+C_CRCLen2)      /*��һ�׵�3��ʱ�α�����*/
#define E2Addr_First_TZone_4PT_Data      (E2Addr_First_TZone_3PT_Data+CLFirst_TZone_3PT_Data+C_CRCLen2)      /*��һ�׵�4��ʱ�α�����*/
#define E2Addr_First_TZone_5PT_Data      (E2Addr_First_TZone_4PT_Data+CLFirst_TZone_4PT_Data+C_CRCLen2)      /*��һ�׵�5��ʱ�α�����*/
#define E2Addr_First_TZone_6PT_Data      (E2Addr_First_TZone_5PT_Data+CLFirst_TZone_5PT_Data+C_CRCLen2)      /*��һ�׵�6��ʱ�α�����*/
#define E2Addr_First_TZone_7PT_Data      (E2Addr_First_TZone_6PT_Data+CLFirst_TZone_6PT_Data+C_CRCLen2)      /*��һ�׵�7��ʱ�α�����*/
#define E2Addr_First_TZone_8PT_Data      (E2Addr_First_TZone_7PT_Data+CLFirst_TZone_7PT_Data+C_CRCLen2)      /*��һ�׵�8��ʱ�α�����*/

#define E2Addr_Sec_TZone_Data            (E2Addr_First_TZone_8PT_Data+CLFirst_TZone_8PT_Data+C_CRCLen2)      /*�ڶ���ʱ��������*/
#define E2Addr_Sec_TZone_1PT_Data        (E2Addr_Sec_TZone_Data+CLSec_TZone_Data+C_CRCLen2)                  /*�ڶ��׵�1��ʱ�α�����*/
#define E2Addr_Sec_TZone_2PT_Data        (E2Addr_Sec_TZone_1PT_Data+CLSec_TZone_1PT_Data+C_CRCLen2)          /*�ڶ��׵�2��ʱ�α�����*/
#define E2Addr_Sec_TZone_3PT_Data        (E2Addr_Sec_TZone_2PT_Data+CLSec_TZone_2PT_Data+C_CRCLen2)          /*�ڶ��׵�3��ʱ�α�����*/
#define E2Addr_Sec_TZone_4PT_Data        (E2Addr_Sec_TZone_3PT_Data+CLSec_TZone_3PT_Data+C_CRCLen2)          /*�ڶ��׵�4��ʱ�α�����*/
#define E2Addr_Sec_TZone_5PT_Data        (E2Addr_Sec_TZone_4PT_Data+CLSec_TZone_4PT_Data+C_CRCLen2)          /*�ڶ��׵�5��ʱ�α�����*/
#define E2Addr_Sec_TZone_6PT_Data        (E2Addr_Sec_TZone_5PT_Data+CLSec_TZone_5PT_Data+C_CRCLen2)          /*�ڶ��׵�6��ʱ�α�����*/
#define E2Addr_Sec_TZone_7PT_Data        (E2Addr_Sec_TZone_6PT_Data+CLSec_TZone_6PT_Data+C_CRCLen2)          /*�ڶ��׵�7��ʱ�α�����*/
#define E2Addr_Sec_TZone_8PT_Data        (E2Addr_Sec_TZone_7PT_Data+CLSec_TZone_7PT_Data+C_CRCLen2)          /*�ڶ��׵�8��ʱ�α�����*/

#define E2Addr_Current_Rate1_Price       (E2Addr_Sec_TZone_8PT_Data+CLSec_TZone_8PT_Data+C_CRCLen2)          /*��ǰ����1-12���*/
#define E2Addr_Current_Rate2_Price       (E2Addr_Current_Rate1_Price+CLCurrent_Rate1_Price+C_CRCLen2)        /**/
#define E2Addr_Current_Rate3_Price       (E2Addr_Current_Rate2_Price+CLCurrent_Rate2_Price+C_CRCLen2)        /**/
#define E2Addr_Current_Rate4_Price       (E2Addr_Current_Rate3_Price+CLCurrent_Rate3_Price+C_CRCLen2)        /**/
#define E2Addr_Current_Rate5_Price       (E2Addr_Current_Rate4_Price+CLCurrent_Rate4_Price+C_CRCLen2)        /**/
#define E2Addr_Current_Rate6_Price       (E2Addr_Current_Rate5_Price+CLCurrent_Rate5_Price+C_CRCLen2)        /**/
#define E2Addr_Current_Rate7_Price       (E2Addr_Current_Rate6_Price+CLCurrent_Rate6_Price+C_CRCLen2)        /**/
#define E2Addr_Current_Rate8_Price       (E2Addr_Current_Rate7_Price+CLCurrent_Rate7_Price+C_CRCLen2)        /**/
#define E2Addr_Current_Rate9_Price       (E2Addr_Current_Rate8_Price+CLCurrent_Rate8_Price+C_CRCLen2)        /**/
#define E2Addr_Current_Rate10_Price      (E2Addr_Current_Rate9_Price+CLCurrent_Rate9_Price+C_CRCLen2)        /**/
#define E2Addr_Current_Rate11_Price      (E2Addr_Current_Rate10_Price+CLCurrent_Rate10_Price+C_CRCLen2)      /**/
#define E2Addr_Current_Rate12_Price      (E2Addr_Current_Rate11_Price+CLCurrent_Rate11_Price+C_CRCLen2)      /**/

#define E2Addr_BackUp_Rate1_Price        (E2Addr_Current_Rate12_Price+CLCurrent_Rate12_Price+C_CRCLen2)      /*�����׷���1-12���*/
#define E2Addr_BackUp_Rate2_Price        (E2Addr_BackUp_Rate1_Price+CLBackUp_Rate1_Price+C_CRCLen2)          /**/
#define E2Addr_BackUp_Rate3_Price        (E2Addr_BackUp_Rate2_Price+CLBackUp_Rate2_Price+C_CRCLen2)          /**/
#define E2Addr_BackUp_Rate4_Price        (E2Addr_BackUp_Rate3_Price+CLBackUp_Rate3_Price+C_CRCLen2)          /**/
#define E2Addr_BackUp_Rate5_Price        (E2Addr_BackUp_Rate4_Price+CLBackUp_Rate4_Price+C_CRCLen2)          /**/
#define E2Addr_BackUp_Rate6_Price        (E2Addr_BackUp_Rate5_Price+CLBackUp_Rate5_Price+C_CRCLen2)          /**/
#define E2Addr_BackUp_Rate7_Price        (E2Addr_BackUp_Rate6_Price+CLBackUp_Rate6_Price+C_CRCLen2)          /**/
#define E2Addr_BackUp_Rate8_Price        (E2Addr_BackUp_Rate7_Price+CLBackUp_Rate7_Price+C_CRCLen2)          /**/
#define E2Addr_BackUp_Rate9_Price        (E2Addr_BackUp_Rate8_Price+CLBackUp_Rate8_Price+C_CRCLen2)          /**/
#define E2Addr_BackUp_Rate10_Price       (E2Addr_BackUp_Rate9_Price+CLBackUp_Rate9_Price+C_CRCLen2)          /**/
#define E2Addr_BackUp_Rate11_Price       (E2Addr_BackUp_Rate10_Price+CLBackUp_Rate10_Price+C_CRCLen2)        /**/
#define E2Addr_BackUp_Rate12_Price       (E2Addr_BackUp_Rate11_Price+CLBackUp_Rate11_Price+C_CRCLen2)        /**/

#define E2Addr_Current_Ladder_Table      (E2Addr_BackUp_Rate12_Price+CLBackUp_Rate12_Price+C_CRCLen2)        /*��ǰ�׽��ݱ�*/
#define E2Addr_BackUp_Ladder_Table       (E2Addr_Current_Ladder_Table+CLCurrent_Ladder_Table+C_CRCLen2)      /*�����׽��ݱ�*/

#define E2Addr_LossVolage_Vol_UpLim      (E2Addr_BackUp_Ladder_Table+CLBackUp_Ladder_Table+C_CRCLen2)        /*ʧѹ�¼���ѹ��������*/
#define E2Addr_LossVolage_Vol_LowLim     (E2Addr_LossVolage_Vol_UpLim+CLLossVolage_Vol_UpLim+C_CRCLen2)      /*ʧѹ�¼���ѹ�ָ�����*/
#define E2Addr_LossVolage_Curr_LowLim    (E2Addr_LossVolage_Vol_LowLim+CLLossVolage_Vol_LowLim+C_CRCLen2)    /*ʧѹ�¼�������������*/
#define E2Addr_LossVolage_Delay_T        (E2Addr_LossVolage_Curr_LowLim+CLLossVolage_Curr_LowLim+C_CRCLen2)  /*ʧѹ�¼��ж���ʱʱ��*/

#define E2Addr_LowVolage_Vol_UpLim       (E2Addr_LossVolage_Delay_T+CLLossVolage_Delay_T+C_CRCLen2)          /*Ƿѹ�¼���ѹ��������*/
#define E2Addr_LowVolage_Delay_T         (E2Addr_LowVolage_Vol_UpLim+CLLowVolage_Vol_UpLim+C_CRCLen2)        /*Ƿѹ�¼��ж���ʱʱ��*/

#define E2Addr_OverVolage_Vol_LowLim     (E2Addr_LowVolage_Delay_T+CLLowVolage_Delay_T+C_CRCLen2)            /*��ѹ�¼���ѹ��������*/
#define E2Addr_OverVolage_Delay_T        (E2Addr_OverVolage_Vol_LowLim+CLOverVolage_Vol_LowLim+C_CRCLen2)    /*��ѹʱ���ж���ʱʱ��*/

#define E2Addr_BreakVol_Vol_UpLim        (E2Addr_OverVolage_Delay_T+CLOverVolage_Delay_T+C_CRCLen2)          /*�����¼���ѹ��������*/
#define E2Addr_BreakVol_Curr_UpLim       (E2Addr_BreakVol_Vol_UpLim+CLBreakVol_Vol_UpLim+C_CRCLen2)          /*�����¼�������������*/
#define E2Addr_BreakVol_Delay_T          (E2Addr_BreakVol_Curr_UpLim+CLBreakVol_Curr_UpLim+C_CRCLen2)        /*�����¼��ж���ʱʱ��*/

#define E2Addr_NoBal_Vol_Lim             (E2Addr_BreakVol_Delay_T+CLBreakVol_Delay_T+C_CRCLen2)              /*��ѹ��ƽ������ֵ*/
#define E2Addr_NoBal_Vol_Delay_T         (E2Addr_NoBal_Vol_Lim+CLNoBal_Vol_Lim+C_CRCLen2)                    /*��ѹ��ƽ�����ж���ʱʱ��*/

#define E2Addr_NoBal_Curr_Lim            (E2Addr_NoBal_Vol_Delay_T+CLNoBal_Vol_Delay_T+C_CRCLen2)            /*������ƽ������ֵ*/
#define E2Addr_NoBal_Curr_Delay_T        (E2Addr_NoBal_Curr_Lim+CLNoBal_Curr_Lim+C_CRCLen2)                  /*������ƽ�����ж���ʱʱ��*/

#define E2Addr_SeriNoBal_Curr_Lim        (E2Addr_NoBal_Curr_Delay_T+CLNoBal_Curr_Delay_T+C_CRCLen2)          /*�������ز�ƽ������ֵ*/
#define E2Addr_SeriNoBal_Curr_Delay_T    (E2Addr_SeriNoBal_Curr_Lim+CLSeriNoBal_Curr_Lim+C_CRCLen2)          /*�������ز�ƽ�����ж���ʱʱ��*/

#define E2Addr_LossCurr_Vol_LowLim       (E2Addr_SeriNoBal_Curr_Delay_T+CLSeriNoBal_Curr_Delay_T+C_CRCLen2)  /*ʧ���¼���ѹ��������*/
#define E2Addr_LossCurr_Curr_UpLim       (E2Addr_LossCurr_Vol_LowLim+CLLossCurr_Vol_LowLim+C_CRCLen2)        /*ʧ���¼�������������*/
#define E2Addr_LossCurr_Curr_LowLim      (E2Addr_LossCurr_Curr_UpLim+CLLossCurr_Curr_UpLim+C_CRCLen2)        /*ʧ���¼�������������*/
#define E2Addr_LossCurr_Delay_T          (E2Addr_LossCurr_Curr_LowLim+CLLossCurr_Curr_LowLim+C_CRCLen2)      /*ʧ���¼��ж���ʱʱ��*/

#define E2Addr_OverCurr_Curr_LowLim      (E2Addr_LossCurr_Delay_T+CLLossCurr_Delay_T+C_CRCLen2)              /*�����¼�������������*/
#define E2Addr_OverCurr_Delay_T          (E2Addr_OverCurr_Curr_LowLim+CLOverCurr_Curr_LowLim+C_CRCLen2)      /*�����¼��ж���ʱʱ��*/

#define E2Addr_BreakCurr_Vol_LowLim      (E2Addr_OverCurr_Delay_T+CLOverCurr_Delay_T+C_CRCLen2)              /*�����¼���ѹ��������*/
#define E2Addr_BreakCurr_Curr_UpLim      (E2Addr_BreakCurr_Vol_LowLim+CLBreakCurr_Vol_LowLim+C_CRCLen2)      /*�����¼�������������*/
#define E2Addr_BreakCurr_Delay_T         (E2Addr_BreakCurr_Curr_UpLim+CLBreakCurr_Curr_UpLim+C_CRCLen2)      /*�����¼��ж���ʱʱ��*/

#define E2Addr_OverLoad_AcPower_LowLim   (E2Addr_BreakCurr_Delay_T+CLBreakCurr_Delay_T+C_CRCLen2)                /*�����¼��й����ʴ�������*/
#define E2Addr_OverLoad_Delay_T          (E2Addr_OverLoad_AcPower_LowLim+CLOverLoad_AcPower_LowLim+C_CRCLen2)    /*�����¼��ж���ʱʱ��*/

#define E2Addr_PosAcDemandOv_De_LowLim   (E2Addr_OverLoad_Delay_T+CLOverLoad_Delay_T+C_CRCLen2)                  /*�����й����������¼�������������*/
#define E2Addr_PosAcDemandOv_Delay_T     (E2Addr_PosAcDemandOv_De_LowLim+CLPosAcDemandOv_De_LowLim+C_CRCLen2)    /*�����й����������¼��ж���ʱʱ��*/

#define E2Addr_RevAcDemandOv_De_LowLim   (E2Addr_PosAcDemandOv_Delay_T+CLPosAcDemandOv_Delay_T+C_CRCLen2)        /*�����й����������¼������������ޣ�698����*/
#define E2Addr_RevAcDemandOv_Delay_T     (E2Addr_RevAcDemandOv_De_LowLim+CLRevAcDemandOv_De_LowLim+C_CRCLen2)    /*�����й����������¼��ж���ʱʱ�䣬698����*/

#define E2Addr_ReDemandOv_De_LowLim      (E2Addr_RevAcDemandOv_Delay_T+CLRevAcDemandOv_Delay_T+C_CRCLen2)        /*�޹����������¼�������������*/
#define E2Addr_ReDemandOv_Delay_T        (E2Addr_ReDemandOv_De_LowLim+CLReDemandOv_De_LowLim+C_CRCLen2)          /*�޹����������¼��ж���ʱʱ�䣬698����*/

#define E2Addr_PowerFactor_LowLim        (E2Addr_ReDemandOv_Delay_T+CLReDemandOv_Delay_T+C_CRCLen2)              /*�������������޷�ֵ*/
#define E2Addr_PowerFactor_Delay_T       (E2Addr_PowerFactor_LowLim+CLPowerFactor_LowLim+C_CRCLen2)              /*�������س������ж���ʱʱ��*/

#define E2Addr_PowerRev_AcPower_LowLim   (E2Addr_PowerFactor_Delay_T+CLPowerFactor_Delay_T+C_CRCLen2)            /*���ʷ����¼��й����ʴ�������*/
#define E2Addr_PowerRev_Delay_T          (E2Addr_PowerRev_AcPower_LowLim+CLPowerRev_AcPower_LowLim+C_CRCLen2)    /*���ʷ����¼��ж���ʱʱ��*/

#define E2Addr_NeutralUnbalanceRate           (E2Addr_PowerRev_Delay_T+CLPowerRev_Delay_T+C_CRCLen2)                          /*���ߵ����쳣��ƽ������ֵ*/
#define E2Addr_NeutralAbnormal_Curr_LowLim    (E2Addr_NeutralUnbalanceRate+CLNeutralUnbalanceRate+C_CRCLen2)                  /*���ߵ����쳣������������*/
#define E2Addr_NeutralAbnormal_Delay_T        (E2Addr_NeutralAbnormal_Curr_LowLim+CLNeutralAbnormal_Curr_LowLim+C_CRCLen2)    /*���ߵ����쳣�ж��ӳ�ʱ��*/

#define E2Addr_ReversedVoltage_Delay_T        (E2Addr_NeutralAbnormal_Delay_T+CLNeutralAbnormal_Delay_T+C_CRCLen2)            /*��ѹ�������¼��ж���ʱʱ��*/
#define E2Addr_ReversedCurrent_Delay_T        (E2Addr_ReversedVoltage_Delay_T+CLReversedVoltage_Delay_T+C_CRCLen2)            /*�����������¼��ж���ʱʱ��*/
#define E2Addr_PowerOff_Delay_T               (E2Addr_ReversedCurrent_Delay_T+CLReversedVoltage_Delay_T+C_CRCLen2)            /*�����¼��ж���ʱʱ��*/
#define E2Addr_Aux_Pow_Down_Delay_T           (E2Addr_PowerOff_Delay_T+CLPowerOff_Delay_T+C_CRCLen2)                          /*������Դ�����ж���ʱʱ��*/
#define E2Addr_MeterFa_Delay_T                (E2Addr_Aux_Pow_Down_Delay_T+CLAux_Pow_Down_Delay_T+C_CRCLen2)                  /*����оƬ�����ж���ʱʱ��*/
#define E2Addr_ClockFa_Delay_T                (E2Addr_MeterFa_Delay_T+CLMeterFa_Delay_T+C_CRCLen2)                            /*ʱ�ӹ����ж���ʱʱ��*/

#define E2Addr_Volage_Check_UpLim             (E2Addr_ClockFa_Delay_T+CLClockFa_Delay_T+C_CRCLen2)                            /*��ѹ��������*/
#define E2Addr_Volage_Check_LowLim            (E2Addr_Volage_Check_UpLim+CLVolage_Check_UpLim+C_CRCLen2)                      /*��ѹ��������*/
#define E2Addr_Voltage_UpLim                  (E2Addr_Volage_Check_LowLim+CLVolage_Check_LowLim+C_CRCLen2)                    /*��ѹ�ϸ�����*/
#define E2Addr_Voltage_LowLim                 (E2Addr_Voltage_UpLim+CLVoltage_UpLim+C_CRCLen2)                                /*��ѹ�ϸ�����*/

/*********************************************************************************************************************************/
#define E2Addr_Volage_Type               (E2Addr_Voltage_LowLim+CLVoltage_LowLim+C_CRCLen2)                  /*��ѹ���͵����ò��� 24*/
#define E2Addr_Start_Up_Current          (E2Addr_Volage_Type+(CLVolage_Type+C_CRCLen2)*8)                    /*����˲ʱ����ֵ*/
#define E2Addr_Start_Up_Power            (E2Addr_Start_Up_Current+CLStart_Up_Current+C_CRCLen2)              /*����˲ʱ����ֵ*/
#define E2Addr_Volage_Abnor_Vol          (E2Addr_Start_Up_Power+CLStart_Up_Power+C_CRCLen2)                  /*��ѹ�쳣�жϵ�ѹ*/
#define E2Addr_Loss_Volage_Curr          (E2Addr_Volage_Abnor_Vol+CLVolage_Abnor_Vol+C_CRCLen2)              /*ȫʧѹ�����Ȳ���*/
#define E2Addr_Pluse_Most__Lim           (E2Addr_Loss_Volage_Curr+(CLLoss_Volage_Curr+C_CRCLen2)*5)          /*�Ӽ���оƬ�������������ֵ��20141129���ݳ�����1�ֽڸ�Ϊ2�ֽ�*/
#define E2Addr_Curr_Ratio_30A            (E2Addr_Pluse_Most__Lim+CLPluse_Most__Lim+C_CRCLen2)                /*У��30A��Ӧ����Ӧ�������ϵ��*/
#define E2Addr_Pulse_Constant            (E2Addr_Curr_Ratio_30A+CLCurr_Ratio_30A+C_CRCLen2)                  /*���峣��*/
#define E2Addr_SoftIJ_Valid_Time         (E2Addr_Pulse_Constant+CLPulse_Constant+C_CRCLen2)                  /*��IJ��Чʱ��*/
#define E2Addr_Extern_Relay_PulW         (E2Addr_SoftIJ_Valid_Time+CLSoftIJ_Valid_Time+C_CRCLen2)            /*���ü̵��������� 4*/
#define E2Addr_Key_Update_ID             (E2Addr_Extern_Relay_PulW+CLExtern_Relay_PulW+C_CRCLen2)            /*��Կ���µ�1����ʶ���ǲ����ߴ���6*/
#define E2Addr_MeterRunStatic            (E2Addr_Key_Update_ID+CLKey_Update_ID+C_CRCLen2)                    /*��ǰ�����ڵڼ���ʱ����ʱ�α�ʱ������ǰ(�͵�ַ)*/

#define E2Addr_F1_TerUpCommParam         (E2Addr_MeterRunStatic+CLMeterRunStatic+C_CRCLen2)                  /*F1�ն�����ͨ�Ų���*/
#define E2Addr_F3_MainStaCommParam       (E2Addr_F1_TerUpCommParam+CLF1_TerUpCommParam+C_CRCLen2)            /*F3��վͨ�Ų���,28*/
#define E2Addr_F4_SMSCommParam           (E2Addr_F3_MainStaCommParam+CLF3_MainStaCommParam+C_CRCLen2)        /*F4����ͨ�Ų���*/
#define E2Addr_F7_TerminalIPAddr         (E2Addr_F4_SMSCommParam+CLF4_SMSCommParam+C_CRCLen2)                /*F7�ն�IP��ַ��64*/
#define E2Addr_F8_ConnectParam           (E2Addr_F7_TerminalIPAddr+CLF7_TerminalIPAddr+C_CRCLen2)            /*F8 ���Ӳ���*/
#define E2Addr_F16_MoveAPNPassWord       (E2Addr_F8_ConnectParam+CLF8_ConnectParam+C_CRCLen2)                /*F16 �ƶ�APN���룬64*/
#define E2Addr_F89_TerminalAddr          (E2Addr_F16_MoveAPNPassWord+CLF16_MoveAPNPassWord+C_CRCLen2)        /*F89 �ն˵�ַ 10*/

#define E2Addr_Alarm_Status              (E2Addr_F89_TerminalAddr+CLF89_TerminalAddr+C_CRCLen2)              /*����ģʽ�� 14*/
#define E2Addr_Rst_ReportState_Timer     (E2Addr_Alarm_Status+CLAlarm_Status+C_CRCLen2)                      /*�����ϱ��Զ���λʱ��3*/
#define E2Addr_Relay_Open_CurrTimer      (E2Addr_Rst_ReportState_Timer+CLRst_ReportState_Timer+C_CRCLen2)    /*��բ���Ƶ������ޱ�����ʱʱ�� 4*/

#define E2Addr_Relay_RemoteOrder         (E2Addr_Relay_Open_CurrTimer+CLRelay_Open_CurrTimer+C_CRCLen2)       /*Զ�̿������� 5*/
#define E2Addr_Relay_State               (E2Addr_Relay_RemoteOrder+CLRelay_RemoteOrder+C_CRCLen2)             /*�̵���״̬ 5*/
#define E2Addr_Relay_LocalOrder          (E2Addr_Relay_State+CLRelay_State+C_CRCLen2)                         /*���ؿ������� 4*/
#define E2Addr_Soft_I_J_Prog_1           (E2Addr_Relay_LocalOrder+CLRelay_LocalOrder+C_CRCLen2)               /*���볧��ģʽ��̼�¼ 11*/
#define E2Addr_Soft_I_J_Prog_2           (E2Addr_Soft_I_J_Prog_1+CLSoft_I_J_Prog_1+C_CRCLen2)                 /*������ģʽ��̼�¼ 11*/
#define E2Addr_Rec_MeterSequence         (E2Addr_Soft_I_J_Prog_2+CLSoft_I_J_Prog_2+C_CRCLen2)                 /*У�����к� 7*/
#define E2Addr_Rec_MeterPassWord         (E2Addr_Rec_MeterSequence+CLRec_MeterSequence+C_CRCLen2)             /*У������ 6*/
#define E2Addr_Remote_Local_State        (E2Addr_Rec_MeterPassWord+CLRec_MeterPassWord+C_CRCLen2)             /*Զ�̡����ؿ���״̬ 4*/
#define E2Addr_UserCardNo                (E2Addr_Remote_Local_State+CLRemote_Local_State+C_CRCLen2)           /*�����к� 10*/
#define E2Addr_Cloc_Batt_LowState        (E2Addr_UserCardNo+CL_UserCardNo+C_CRCLen2)                          /*ʱ�ӵ��Ƿѹ״̬ 3*/
#define E2Addr_ReadMeter_Batt_LowState   (E2Addr_Cloc_Batt_LowState+CLCloc_Batt_LowState+C_CRCLen2)           /*���ѵ��Ƿѹ״̬ 3*/
#define E2Addr_ESAM_FaultState           (E2Addr_ReadMeter_Batt_LowState+CLReadMeter_Batt_LowState+C_CRCLen2) /*ESAM����״̬ 3*/
#define E2Addr_Clock_FaultState          (E2Addr_ESAM_FaultState+CLESAM_FaultState+C_CRCLen2)                 /*ʱ�ӹ���״̬ 3*/
#define E2Addr_FactoryInMeterNum         (E2Addr_Clock_FaultState+CLClock_FaultState+C_CRCLen2)               /*����ڲ���� 4*/

#define E2Addr_ReportNewAddNum           (E2Addr_FactoryInMeterNum+CLFactoryInMeterNum+C_CRCLen2)             /*�����ϱ�����98��С���޸�*/
#define E2Addr_HaveReportState           (E2Addr_ReportNewAddNum+CLReportNewAddNum+C_CRCLen2)                 /*�������ϱ���־*/

#define E2Addr_AppProInformation         (E2Addr_HaveReportState+CLHaveReportState+C_CRCLen2)                 /*Э��汾��Ϣ*/
#define E2Addr_AppMaxReAPDU              (E2Addr_AppProInformation+CLAppProInformation+C_CRCLen2)             /*������APDU�ߴ�*/
#define E2Addr_AppMaxSeAPDU              (E2Addr_AppMaxReAPDU+CLAppMaxReAPDU+C_CRCLen2)                       /*�����APDU�ߴ�*/
#define E2Addr_AppMaxHandleAPDU          (E2Addr_AppMaxSeAPDU+CLAppMaxSeAPDU+C_CRCLen2)                       /*���ɴ���APDU�ߴ�*/
#define E2Addr_AppProConsistency         (E2Addr_AppMaxHandleAPDU+CLAppMaxHandleAPDU+C_CRCLen2)               /*Э��һ���Կ�*/
#define E2Addr_AppFunConsistency         (E2Addr_AppProConsistency+CLAppProConsistency+C_CRCLen2)             /*����һ���Կ�*/
#define E2Addr_AppStaticTimeout          (E2Addr_AppFunConsistency+CLAppFunConsistency+C_CRCLen2)             /*��̬��ʱʱ��*/

#define E2Addr_AppStaticTimeout_termal   (E2Addr_AppStaticTimeout+CLAppStaticTimeout+C_CRCLen2)               /*�ն˾�̬��ʱʱ��*/
#define E2Addr_ConAutheMechanism         (E2Addr_AppStaticTimeout_termal+CLAppStaticTimeout+C_CRCLen2)        /*������֤����*/
#define E2Addr_SafeModePara              (E2Addr_ConAutheMechanism+CLConAutheMechanism+C_CRCLen2)             /*��ȫģʽ����*/

#define E2Addr_I_Free_OADTabLen_T        (E2Addr_SafeModePara+CLSafeModePara+C_CRCLen2)                      /*˲ʱ����OAD��ű�ʵ�ʳ��ȼ����ڣ�4*/
#define E2Addr_Min_Free_OADTabLen_T      (E2Addr_I_Free_OADTabLen_T+CLI_Free_OADTabLen_T+C_CRCLen2)          /*���Ӷ���OAD��ű�ʵ�ʳ��ȼ����ڣ�4*/
#define E2Addr_H_Free_OADTabLen_T        (E2Addr_Min_Free_OADTabLen_T+CLMin_Free_OADTabLen_T+C_CRCLen2)      /*Сʱ����OAD��ű�ʵ�ʳ��ȼ����ڣ�4*/
#define E2Addr_D_Free_OADTabLen_T        (E2Addr_H_Free_OADTabLen_T+CLH_Free_OADTabLen_T+C_CRCLen2)          /*�ն���OAD��ű�ʵ�ʳ��ȼ����ڣ�4*/
#define E2Addr_Sett_Free_OADTabLen_T     (E2Addr_D_Free_OADTabLen_T+CLD_Free_OADTabLen_T+C_CRCLen2)          /*�����ն���OAD��ű�ʵ�ʳ��ȼ����ڣ�4*/
#define E2Addr_M_Free_OADTabLen_T        (E2Addr_Sett_Free_OADTabLen_T+CLSett_Free_OADTabLen_T+C_CRCLen2)    /*�¶���OAD��ű�ʵ�ʳ��ȼ����ڣ�4*/
#define E2Addr_Y_Free_OADTabLen_T        (E2Addr_M_Free_OADTabLen_T+CLM_Free_OADTabLen_T+C_CRCLen2)          /*�궳��OAD��ű�ʵ�ʳ��ȼ����ڣ�4*/
#define E2Addr_TZ_Free_OADTabLen_T       (E2Addr_Y_Free_OADTabLen_T+CLYSettle_Free_OADTabLen_T+C_CRCLen2)    /*ʱ�����л�����OAD��ű�ʵ�ʳ��ȼ����ڣ�4*/
#define E2Addr_PT_Free_OADTabLen_T       (E2Addr_TZ_Free_OADTabLen_T+CLTZ_Free_OADTabLen_T+C_CRCLen2)        /*��ʱ�α��л�����OAD��ű�ʵ�ʳ��ȼ����ڣ�4*/
#define E2Addr_R_Free_OADTabLen_T        (E2Addr_PT_Free_OADTabLen_T+CLPT_Free_OADTabLen_T+C_CRCLen2)        /*���ʵ���л�����OAD��ű�ʵ�ʳ��ȼ����ڣ�4*/
#define E2Addr_L_Free_OADTabLen_T        (E2Addr_R_Free_OADTabLen_T+CLR_Free_OADTabLen_T+C_CRCLen2)          /*���ݵ���л�����OAD��ű�ʵ�ʳ��ȼ����ڣ�4*/

#define E2Addr_I_Free_OADTab             (E2Addr_L_Free_OADTabLen_T+CLL_Free_OADTabLen_T+C_CRCLen2)          /*˲ʱ����OAD��ű�C_698Free_OADTabLen*/
#define E2Addr_Min_Free_OADTab           (E2Addr_I_Free_OADTab+C_698Free_OADTabLen+C_CRCLen2)                /*���Ӷ���OAD��ű�C_698Free_OADTabLen*/
#define E2Addr_H_Free_OADTab             (E2Addr_Min_Free_OADTab+C_698Free_OADTabLen+C_CRCLen2)              /*Сʱ����OAD��ű�C_698Free_OADTabLen*/
#define E2Addr_D_Free_OADTab             (E2Addr_H_Free_OADTab+C_698Free_OADTabLen+C_CRCLen2)                /*�ն���OAD��ű�C_698Free_OADTabLen*/
#define E2Addr_Sett_Free_OADTab          (E2Addr_D_Free_OADTab+C_698Free_OADTabLen+C_CRCLen2)                /*�����ն���OAD��ű�C_698Free_OADTabLen*/
#define E2Addr_M_Free_OADTab             (E2Addr_Sett_Free_OADTab+C_698Free_OADTabLen+C_CRCLen2)             /*�¶���OAD��ű�C_698Free_OADTabLen,��ַ0x503-0x282=641,ʣ��63*/
#define E2Addr_Y_Free_OADTab             (E2Addr_M_Free_OADTab+C_698Free_OADTabLen+C_CRCLen2)                /*�궳��OAD��ű�C_698Free_OADTabLen,ʵ��Ϊ���ݽ��㶳��*/
#define E2Addr_TZ_Free_OADTab            (E2Addr_Y_Free_OADTab+C_698Free_OADTabLen+C_CRCLen2)                /*ʱ�����л�����OAD��ű�C_698Free_OADTabLen*/
#define E2Addr_PT_Free_OADTab            (E2Addr_TZ_Free_OADTab+C_698Free_OADTabLen+C_CRCLen2)               /*��ʱ�α��л�����OAD��ű�C_698Free_OADTabLen*/
#define E2Addr_R_Free_OADTab             (E2Addr_PT_Free_OADTab+C_698Free_OADTabLen+C_CRCLen2)               /*���ʵ���л�����OAD��ű�C_698Free_OADTabLen*/
#define E2Addr_L_Free_OADTab             (E2Addr_R_Free_OADTab+C_698Free_OADTabLen+C_CRCLen2)                /*���ݵ���л�����OAD��ű�C_698Free_OADTabLen*/

#define E2Addr_D_Free_StartTime          (E2Addr_L_Free_OADTab+C_698Free_OADTabLen+C_CRCLen2)                /*�ն�����ʼ����ʱ�䣬5*/
#define E2Addr_M_Free_StartTime          (E2Addr_D_Free_StartTime+CLD_Free_StartTime+C_CRCLen2)              /*�¶�����ʼ����ʱ�䣬5*/
#define E2Addr_Y_Free_StartTime          (E2Addr_M_Free_StartTime+CLM_Free_StartTime+C_CRCLen2)              /*�궳����ʼ����ʱ�䣬5*/

#define	E2Addr_LossVolage_Report_Mode           (E2Addr_Y_Free_StartTime+CLY_Free_StartTime+C_CRCLen2)            /*ʧѹ�ϱ�ģʽ��*/
#define	E2Addr_LowVolage_Report_Mode            (E2Addr_LossVolage_Report_Mode+CLReport_Mode+C_CRCLen2)           /*Ƿѹ�ϱ�ģʽ��*/
#define	E2Addr_OverVolage_Report_Mode           (E2Addr_LowVolage_Report_Mode+CLReport_Mode+C_CRCLen2)            /*��ѹ�ϱ�ģʽ��*/
#define	E2Addr_BreakVol_Report_Mode             (E2Addr_OverVolage_Report_Mode+CLReport_Mode+C_CRCLen2)           /*�����ϱ�ģʽ��*/
#define	E2Addr_LossCurr_Report_Mode             (E2Addr_BreakVol_Report_Mode+CLReport_Mode+C_CRCLen2)             /*ʧ���ϱ�ģʽ��*/
#define	E2Addr_OverCurr_Report_Mode             (E2Addr_LossCurr_Report_Mode+CLReport_Mode+C_CRCLen2)             /*�����ϱ�ģʽ��*/
#define	E2Addr_BreakCurr_Report_Mode            (E2Addr_OverCurr_Report_Mode+CLReport_Mode+C_CRCLen2)             /*�����ϱ�ģʽ��*/
#define	E2Addr_PowerRev_Report_Mode             (E2Addr_BreakCurr_Report_Mode+CLReport_Mode+C_CRCLen2)            /*���ʷ����ϱ�ģʽ��*/
#define	E2Addr_OverLoad_Report_Mode             (E2Addr_PowerRev_Report_Mode+CLReport_Mode+C_CRCLen2)             /*�����ϱ�ģʽ��*/
#define	E2Addr_PosAcDemandOv_Report_Mode        (E2Addr_OverLoad_Report_Mode+CLReport_Mode+C_CRCLen2)             /*�����й����������¼��ϱ�ģʽ��*/
#define	E2Addr_RevAcDemandOv_Report_Mode        (E2Addr_PosAcDemandOv_Report_Mode+CLReport_Mode+C_CRCLen2)        /*�����й����������¼��ϱ�ģʽ��*/
#define	E2Addr_ReDemandOv_Report_Mode           (E2Addr_RevAcDemandOv_Report_Mode+CLReport_Mode+C_CRCLen2)        /*�޹����������¼��ϱ�ģʽ��*/
#define	E2Addr_PowerFactor_Report_Mode          (E2Addr_ReDemandOv_Report_Mode+CLReport_Mode+C_CRCLen2)           /*���������������¼��ϱ�ģʽ��*/
#define	E2Addr_AllLossVolage_Report_Mode        (E2Addr_PowerFactor_Report_Mode+CLReport_Mode+C_CRCLen2)          /*ȫʧѹ�ϱ�ģʽ��*/
#define	E2Addr_AuxPowDown_Report_Mode           (E2Addr_AllLossVolage_Report_Mode+CLReport_Mode+C_CRCLen2)        /*������Դʧ���ϱ�ģʽ��*/
#define	E2Addr_ReversedVoltage_Report_Mode      (E2Addr_AuxPowDown_Report_Mode+CLReport_Mode+C_CRCLen2)           /*��ѹ�������ϱ�ģʽ��*/
#define	E2Addr_ReversedCurrent_Report_Mode      (E2Addr_ReversedVoltage_Report_Mode+CLReport_Mode+C_CRCLen2)      /*�����������ϱ�ģʽ��*/
#define	E2Addr_PowerOff_Report_Mode             (E2Addr_ReversedCurrent_Report_Mode+CLReport_Mode+C_CRCLen2)      /*�����ϱ�ģʽ��*/
#define	E2Addr_Program_Report_Mode              (E2Addr_PowerOff_Report_Mode+CLReport_Mode+C_CRCLen2)             /*����ϱ�ģʽ��*/
#define	E2Addr_TolClear_Report_Mode             (E2Addr_Program_Report_Mode+CLReport_Mode+C_CRCLen2)              /*��������ϱ�ģʽ��*/
#define	E2Addr_DemandClear_Report_Mode          (E2Addr_TolClear_Report_Mode+CLReport_Mode+C_CRCLen2)             /*���������ϱ�ģʽ��*/
#define	E2Addr_EventClear_Report_Mode           (E2Addr_DemandClear_Report_Mode+CLReport_Mode+C_CRCLen2)          /*�¼������ϱ�ģʽ��*/
#define	E2Addr_AdjTime_Report_Mode              (E2Addr_EventClear_Report_Mode+CLReport_Mode+C_CRCLen2)           /*Уʱ�ϱ�ģʽ��*/
#define	E2Addr_BroadcastTime_Report_Mode        (E2Addr_AdjTime_Report_Mode+CLReport_Mode+C_CRCLen2)              /*�㲥Уʱ�ϱ�ģʽ��*/
#define	E2Addr_ProgPT_Report_Mode               (E2Addr_BroadcastTime_Report_Mode+CLReport_Mode+C_CRCLen2)        /*ʱ�α����ϱ�ģʽ��*/
#define	E2Addr_ProgPZ_Report_Mode               (E2Addr_ProgPT_Report_Mode+CLReport_Mode+C_CRCLen2)               /*ʱ�������ϱ�ģʽ��*/
#define	E2Addr_ProgWRe_Report_Mode              (E2Addr_ProgPZ_Report_Mode+CLReport_Mode+C_CRCLen2)               /*�����ձ���ϱ�ģʽ��*/
#define	E2Addr_ProgSettD_Report_Mode            (E2Addr_ProgWRe_Report_Mode+CLReport_Mode+C_CRCLen2)              /*�����ձ���ϱ�ģʽ��*/
#define	E2Addr_OpenW_Report_Mode                (E2Addr_ProgSettD_Report_Mode+CLReport_Mode+C_CRCLen2)            /*������ϱ�ģʽ��*/
#define	E2Addr_OpenCW_Report_Mode               (E2Addr_OpenW_Report_Mode+CLReport_Mode+C_CRCLen2)                /*����ť���ϱ�ģʽ��*/
#define	E2Addr_NoBalVol_Report_Mode             (E2Addr_OpenCW_Report_Mode+CLReport_Mode+C_CRCLen2)               /*��ѹ��ƽ���ϱ�ģʽ��*/
#define	E2Addr_NoBalCurr_Report_Mode            (E2Addr_NoBalVol_Report_Mode+CLReport_Mode+C_CRCLen2)             /*������ƽ���ϱ�ģʽ��*/
#define	E2Addr_RelayOpen_Report_Mode            (E2Addr_NoBalCurr_Report_Mode+CLReport_Mode+C_CRCLen2)            /*��բ�ϱ�ģʽ��*/
#define	E2Addr_RelayClose_Report_Mode           (E2Addr_RelayOpen_Report_Mode+CLReport_Mode+C_CRCLen2)            /*��բ�ϱ�ģʽ��*/
#define	E2Addr_ProgHol_Report_Mode              (E2Addr_RelayClose_Report_Mode+CLReport_Mode+C_CRCLen2)           /*�ڼ��ձ���ϱ�ģʽ��*/
#define	E2Addr_ProgAcC_Report_Mode              (E2Addr_ProgHol_Report_Mode+CLReport_Mode+C_CRCLen2)              /*�й���Ϸ�ʽ����ϱ�ģʽ��*/
#define	E2Addr_ProgReC_Report_Mode              (E2Addr_ProgAcC_Report_Mode+CLReport_Mode+C_CRCLen2)              /*�޹���Ϸ�ʽ����ϱ�ģʽ��*/
#define	E2Addr_ProgTPara_Report_Mode            (E2Addr_ProgReC_Report_Mode+CLReport_Mode+C_CRCLen2)              /*���ʲ��������ϱ�ģʽ��*/
#define	E2Addr_ProgLad_Report_Mode              (E2Addr_ProgTPara_Report_Mode+CLReport_Mode+C_CRCLen2)            /*���ݱ����ϱ�ģʽ��*/
#define	E2Addr_Key_Update_Report_Mode           (E2Addr_ProgLad_Report_Mode+CLReport_Mode+C_CRCLen2)              /*��Կ�����ϱ�ģʽ��*/
#define	E2Addr_AbnorC_Report_Mode               (E2Addr_Key_Update_Report_Mode+CLReport_Mode+C_CRCLen2)           /*�쳣�忨�ϱ�ģʽ��*/
#define	E2Addr_BuyCurr_Report_Mode              (E2Addr_AbnorC_Report_Mode+CLReport_Mode+C_CRCLen2)               /*�����ϱ�ģʽ��*/
#define	E2Addr_ReturnMoney_Report_Mode          (E2Addr_BuyCurr_Report_Mode+CLReport_Mode+C_CRCLen2)              /*�˷��ϱ�ģʽ��*/
#define	E2Addr_ConMEndEn_Report_Mode            (E2Addr_ReturnMoney_Report_Mode+CLReport_Mode+C_CRCLen2)          /*�㶨�ų������ϱ�ģʽ��*/
#define	E2Addr_RelayFaEndEn_Report_Mode         (E2Addr_ConMEndEn_Report_Mode+CLReport_Mode+C_CRCLen2)            /*���ɿ��������ϱ�ģʽ��*/
#define	E2Addr_PowerFa_EndT_Report_Mode         (E2Addr_RelayFaEndEn_Report_Mode+CLReport_Mode+C_CRCLen2)         /*��Դ�쳣�ϱ�ģʽ��*/
#define	E2Addr_SeriNoBalCurr_Report_Mode        (E2Addr_PowerFa_EndT_Report_Mode+CLReport_Mode+C_CRCLen2)         /*�������ز�ƽ���ϱ�ģʽ��*/
#define	E2Addr_ClockFault_Report_Mode           (E2Addr_SeriNoBalCurr_Report_Mode+CLReport_Mode+C_CRCLen2)        /*ʱ�ӹ����ϱ�ģʽ��*/
#define	E2Addr_MeteringChipFault_Report_Mode    (E2Addr_ClockFault_Report_Mode+CLReport_Mode+C_CRCLen2)           /*����оƬ�����ϱ�ģʽ��*/

#define	E2Addr_LossVolage_Report_Type           (E2Addr_MeteringChipFault_Report_Mode+CLReport_Mode+C_CRCLen2)    /*ʧѹ�ϱ���ʽ*/
#define	E2Addr_LowVolage_Report_Type            (E2Addr_LossVolage_Report_Type+CLReport_Type+C_CRCLen2)           /*Ƿѹ�ϱ���ʽ*/
#define	E2Addr_OverVolage_Report_Type           (E2Addr_LowVolage_Report_Type+CLReport_Type+C_CRCLen2)            /*��ѹ�ϱ���ʽ*/
#define	E2Addr_BreakVol_Report_Type             (E2Addr_OverVolage_Report_Type+CLReport_Type+C_CRCLen2)           /*�����ϱ���ʽ*/
#define	E2Addr_LossCurr_Report_Type             (E2Addr_BreakVol_Report_Type+CLReport_Type+C_CRCLen2)             /*ʧ���ϱ���ʽ*/
#define	E2Addr_OverCurr_Report_Type             (E2Addr_LossCurr_Report_Type+CLReport_Type+C_CRCLen2)             /*�����ϱ���ʽ*/
#define	E2Addr_BreakCurr_Report_Type            (E2Addr_OverCurr_Report_Type+CLReport_Type+C_CRCLen2)             /*�����ϱ���ʽ*/
#define	E2Addr_PowerRev_Report_Type             (E2Addr_BreakCurr_Report_Type+CLReport_Type+C_CRCLen2)            /*���ʷ����ϱ���ʽ*/
#define	E2Addr_OverLoad_Report_Type             (E2Addr_PowerRev_Report_Type+CLReport_Type+C_CRCLen2)             /*�����ϱ���ʽ*/
#define	E2Addr_PosAcDemandOv_Report_Type        (E2Addr_OverLoad_Report_Type+CLReport_Type+C_CRCLen2)             /*�����й����������¼��ϱ���ʽ*/
#define	E2Addr_RevAcDemandOv_Report_Type        (E2Addr_PosAcDemandOv_Report_Type+CLReport_Type+C_CRCLen2)        /*�����й����������¼��ϱ���ʽ*/
#define	E2Addr_ReDemandOv_Report_Type           (E2Addr_RevAcDemandOv_Report_Type+CLReport_Type+C_CRCLen2)        /*�޹����������¼��ϱ���ʽ*/
#define	E2Addr_PowerFactor_Report_Type          (E2Addr_ReDemandOv_Report_Type+CLReport_Type+C_CRCLen2)           /*���������������¼��ϱ���ʽ*/
#define	E2Addr_AllLossVolage_Report_Type        (E2Addr_PowerFactor_Report_Type+CLReport_Type+C_CRCLen2)          /*ȫʧѹ�ϱ���ʽ*/
#define	E2Addr_AuxPowDown_Report_Type           (E2Addr_AllLossVolage_Report_Type+CLReport_Type+C_CRCLen2)        /*������Դʧ���ϱ���ʽ*/
#define	E2Addr_ReversedVoltage_Report_Type      (E2Addr_AuxPowDown_Report_Type+CLReport_Type+C_CRCLen2)           /*��ѹ�������ϱ���ʽ*/
#define	E2Addr_ReversedCurrent_Report_Type      (E2Addr_ReversedVoltage_Report_Type+CLReport_Type+C_CRCLen2)      /*�����������ϱ���ʽ*/
#define	E2Addr_PowerOff_Report_Type             (E2Addr_ReversedCurrent_Report_Type+CLReport_Type+C_CRCLen2)      /*�����ϱ���ʽ*/
#define	E2Addr_Program_Report_Type              (E2Addr_PowerOff_Report_Type+CLReport_Type+C_CRCLen2)             /*����ϱ���ʽ*/
#define	E2Addr_TolClear_Report_Type             (E2Addr_Program_Report_Type+CLReport_Type+C_CRCLen2)              /*��������ϱ���ʽ*/
#define	E2Addr_DemandClear_Report_Type          (E2Addr_TolClear_Report_Type+CLReport_Type+C_CRCLen2)             /*���������ϱ���ʽ*/
#define	E2Addr_EventClear_Report_Type           (E2Addr_DemandClear_Report_Type+CLReport_Type+C_CRCLen2)          /*�¼������ϱ���ʽ*/
#define	E2Addr_AdjTime_Report_Type              (E2Addr_EventClear_Report_Type+CLReport_Type+C_CRCLen2)           /*Уʱ�ϱ���ʽ*/
#define	E2Addr_BroadcastTime_Report_Type        (E2Addr_AdjTime_Report_Type+CLReport_Type+C_CRCLen2)              /*�㲥Уʱ�ϱ���ʽ*/
#define	E2Addr_ProgPT_Report_Type               (E2Addr_BroadcastTime_Report_Type+CLReport_Type+C_CRCLen2)        /*ʱ�α����ϱ���ʽ*/
#define	E2Addr_ProgPZ_Report_Type               (E2Addr_ProgPT_Report_Type+CLReport_Type+C_CRCLen2)               /*ʱ�������ϱ���ʽ*/
#define	E2Addr_ProgWRe_Report_Type              (E2Addr_ProgPZ_Report_Type+CLReport_Type+C_CRCLen2)               /*�����ձ���ϱ���ʽ*/
#define	E2Addr_ProgSettD_Report_Type            (E2Addr_ProgWRe_Report_Type+CLReport_Type+C_CRCLen2)              /*�����ձ���ϱ���ʽ*/
#define	E2Addr_OpenW_Report_Type                (E2Addr_ProgSettD_Report_Type+CLReport_Type+C_CRCLen2)            /*������ϱ���ʽ*/
#define	E2Addr_OpenCW_Report_Type               (E2Addr_OpenW_Report_Type+CLReport_Type+C_CRCLen2)                /*����ť���ϱ���ʽ*/
#define	E2Addr_NoBalVol_Report_Type             (E2Addr_OpenCW_Report_Type+CLReport_Type+C_CRCLen2)               /*��ѹ��ƽ���ϱ���ʽ*/
#define	E2Addr_NoBalCurr_Report_Type            (E2Addr_NoBalVol_Report_Type+CLReport_Type+C_CRCLen2)             /*������ƽ���ϱ���ʽ*/
#define	E2Addr_RelayOpen_Report_Type            (E2Addr_NoBalCurr_Report_Type+CLReport_Type+C_CRCLen2)            /*��բ�ϱ���ʽ*/
#define	E2Addr_RelayClose_Report_Type           (E2Addr_RelayOpen_Report_Type+CLReport_Type+C_CRCLen2)            /*��բ�ϱ���ʽ*/
#define	E2Addr_ProgHol_Report_Type              (E2Addr_RelayClose_Report_Type+CLReport_Type+C_CRCLen2)           /*�ڼ��ձ���ϱ���ʽ*/
#define	E2Addr_ProgAcC_Report_Type              (E2Addr_ProgHol_Report_Type+CLReport_Type+C_CRCLen2)              /*�й���Ϸ�ʽ����ϱ���ʽ*/
#define	E2Addr_ProgReC_Report_Type              (E2Addr_ProgAcC_Report_Type+CLReport_Type+C_CRCLen2)              /*�޹���Ϸ�ʽ����ϱ���ʽ*/
#define	E2Addr_ProgTPara_Report_Type            (E2Addr_ProgReC_Report_Type+CLReport_Type+C_CRCLen2)              /*���ʲ��������ϱ���ʽ*/
#define	E2Addr_ProgLad_Report_Type              (E2Addr_ProgTPara_Report_Type+CLReport_Type+C_CRCLen2)            /*���ݱ����ϱ���ʽ*/
#define	E2Addr_Key_Update_Report_Type           (E2Addr_ProgLad_Report_Type+CLReport_Type+C_CRCLen2)              /*��Կ�����ϱ���ʽ*/
#define	E2Addr_AbnorC_Report_Type               (E2Addr_Key_Update_Report_Type+CLReport_Type+C_CRCLen2)           /*�쳣�忨�ϱ���ʽ*/
#define	E2Addr_BuyCurr_Report_Type              (E2Addr_AbnorC_Report_Type+CLReport_Type+C_CRCLen2)               /*�����ϱ���ʽ*/
#define	E2Addr_ReturnMoney_Report_Type          (E2Addr_BuyCurr_Report_Type+CLReport_Type+C_CRCLen2)              /*�˷��ϱ���ʽ*/
#define	E2Addr_ConMEndEn_Report_Type            (E2Addr_ReturnMoney_Report_Type+CLReport_Type+C_CRCLen2)          /*�㶨�ų������ϱ���ʽ*/
#define	E2Addr_RelayFaEndEn_Report_Type         (E2Addr_ConMEndEn_Report_Type+CLReport_Type+C_CRCLen2)            /*���ɿ��������ϱ���ʽ*/
#define	E2Addr_PowerFa_EndT_Report_Type         (E2Addr_RelayFaEndEn_Report_Type+CLReport_Type+C_CRCLen2)         /*��Դ�쳣�ϱ���ʽ*/
#define	E2Addr_SeriNoBalCurr_Report_Type        (E2Addr_PowerFa_EndT_Report_Type+CLReport_Type+C_CRCLen2)         /*�������ز�ƽ���ϱ���ʽ*/
#define	E2Addr_ClockFault_Report_Type           (E2Addr_SeriNoBalCurr_Report_Type+CLReport_Type+C_CRCLen2)        /*ʱ�ӹ����ϱ���ʽ*/
#define	E2Addr_MeteringChipFault_Report_Type    (E2Addr_ClockFault_Report_Type+CLReport_Type+C_CRCLen2)           /*����оƬ�����ϱ���ʽ*/
#define	E2Addr_Drive_Report_Type                (E2Addr_MeteringChipFault_Report_Type+CLReport_Type+C_CRCLen2)    /*2015�����ϱ���ʽ*/
#define	E2Addr_ABnor_ZeroCurrent_Report_Mode    (E2Addr_Drive_Report_Type+CLReport_Type+C_CRCLen2)                /*2015�����ϱ���ʽ*/
#define	E2Addr_ABnor_ZeroCurrent_Report_Type    (E2Addr_ABnor_ZeroCurrent_Report_Mode+CLReport_Type+C_CRCLen2)    /*���ߵ����쳣�ϱ�ģʽ��*/
#if 0
#define	E2Addr_BroadTimeAbnormal_Report_Mode    (E2Addr_ABnor_ZeroCurrent_Report_Type+CLReport_Type+C_CRCLen2)    /*�㲥Уʱ�쳣�ϱ�ģʽ��*/
#define	E2Addr_BroadTimeAbnormal_Report_Type    (E2Addr_BroadTimeAbnormal_Report_Mode+CLReport_Type+C_CRCLen2)    /*�㲥Уʱ�쳣�ϱ���ʽ*/
#endif
#define	E2Addr_ADD_End                          (E2Addr_ABnor_ZeroCurrent_Report_Type+CLReport_Type+C_CRCLen2)

#define E2Addr_All_Loss_Vol_OADTab              (E2Addr_ABnor_ZeroCurrent_Report_Type+CLReport_Type+C_CRCLen2)    /*ȫʧѹ�����б�*/
#define E2Addr_Aux_Pow_Down_OADTab              (E2Addr_All_Loss_Vol_OADTab+C_698Event_OADTabLen+C_CRCLen2)       /*������Դ����*/
#define E2Addr_Pow_Down_OADTab                  (E2Addr_Aux_Pow_Down_OADTab+C_698Event_OADTabLen+C_CRCLen2)       /*����*/
#define E2Addr_Pos_Ac_De_Over_OADTab            (E2Addr_Pow_Down_OADTab+C_698Event_OADTabLen+C_CRCLen2)           /*�����й����������¼�*/
#define E2Addr_Rev_Ac_De_Over_OADTab            (E2Addr_Pos_Ac_De_Over_OADTab+C_698Event_OADTabLen+C_CRCLen2)     /*�����й����������¼�*/
#define E2Addr_Qua_Re_De_Over_OADTab            (E2Addr_Rev_Ac_De_Over_OADTab+C_698Event_OADTabLen+C_CRCLen2)     /*�޹��й����������¼�*/
#define E2Addr_Loss_Vol_OADTab                  (E2Addr_Qua_Re_De_Over_OADTab+C_698Event_OADTabLen+C_CRCLen2)     /*ʧѹ�����б�*/
#define E2Addr_Low_Vol_OADTab                   (E2Addr_Loss_Vol_OADTab+C_698Event_OADTabLen+C_CRCLen2)           /*Ƿѹ�����б�*/
#define E2Addr_Over_Vol_OADTab                  (E2Addr_Low_Vol_OADTab+C_698Event_OADTabLen+C_CRCLen2)            /*��ѹ�����б�*/
#define E2Addr_Break_Vol_OADTab                 (E2Addr_Over_Vol_OADTab+C_698Event_OADTabLen+C_CRCLen2)           /*��������б�*/
#define E2Addr_RevPS_Vol_OADTab                 (E2Addr_Break_Vol_OADTab+C_698Event_OADTabLen+C_CRCLen2)          /*��ѹ����������б�*/
#define E2Addr_RevPS_Curr_OADTab                (E2Addr_RevPS_Vol_OADTab+C_698Event_OADTabLen+C_CRCLen2)          /*��������������б�*/
#define E2Addr_NoBal_Vol_OADTab                 (E2Addr_RevPS_Curr_OADTab+C_698Event_OADTabLen+C_CRCLen2)         /*��ѹ��ƽ������б�*/
#define E2Addr_NoBal_Curr_OADTab                (E2Addr_NoBal_Vol_OADTab+C_698Event_OADTabLen+C_CRCLen2)          /*������ƽ������б�*/
#define E2Addr_SevNoBal_Curr_OADTab             (E2Addr_NoBal_Curr_OADTab+C_698Event_OADTabLen+C_CRCLen2)         /*�������ز�ƽ������б�*/
#define E2Addr_Loss_Curr_OADTab                 (E2Addr_SevNoBal_Curr_OADTab+C_698Event_OADTabLen+C_CRCLen2)      /*ʧ�������б�*/
#define E2Addr_Over_Curr_OADTab                 (E2Addr_Loss_Curr_OADTab+C_698Event_OADTabLen+C_CRCLen2)          /*���������б�*/
#define E2Addr_Break_Curr_OADTab                (E2Addr_Over_Curr_OADTab+C_698Event_OADTabLen+C_CRCLen2)          /*���������б�*/
#define E2Addr_Power_Rev_OADTab                 (E2Addr_Break_Curr_OADTab+C_698Event_OADTabLen+C_CRCLen2)         /*���ʷ�������б�*/
#define E2Addr_Over_Lo_OADTab                   (E2Addr_Power_Rev_OADTab+C_698Event_OADTabLen+C_CRCLen2)          /*���ع����б�*/
#define E2Addr_Tol_Clear_OADTab                 (E2Addr_Over_Lo_OADTab+C_698Event_OADTabLen+C_CRCLen2)            /*��������б�*/
#define E2Addr_De_Clear_OADTab                  (E2Addr_Tol_Clear_OADTab+C_698Event_OADTabLen+C_CRCLen2)          /*��������б�*/
#define E2Addr_Even_Clear_OADTab                (E2Addr_De_Clear_OADTab+C_698Event_OADTabLen+C_CRCLen2)           /*�¼���������б�*/
#define E2Addr_Program_OADTab                   (E2Addr_Even_Clear_OADTab+C_698Event_OADTabLen+C_CRCLen2)         /*��̼�¼�����б�*/
#define E2Addr_AbnorC_OADTab                    (E2Addr_Program_OADTab+C_698Event_OADTabLen+C_CRCLen2)            /*�쳣�忨��¼�����б�*/
#define E2Addr_OpenW_OADTab                     (E2Addr_AbnorC_OADTab+C_698Event_OADTabLen+C_CRCLen2)             /*����Ǽ�¼�����б�*/
#define E2Addr_OpenCW_OADTab                    (E2Addr_OpenW_OADTab+C_698Event_OADTabLen+C_CRCLen2)              /*����ť�Ǽ�¼�����б�*/
#define E2Addr_BuyCurr_OADTab                   (E2Addr_OpenCW_OADTab+C_698Event_OADTabLen+C_CRCLen2)             /*�����¼�����б�*/
#define E2Addr_Return_M_OADTab                  (E2Addr_BuyCurr_OADTab+C_698Event_OADTabLen+C_CRCLen2)            /*�˷Ѽ�¼�����б�*/
#define E2Addr_ConM_OADTab                      (E2Addr_Return_M_OADTab+C_698Event_OADTabLen+C_CRCLen2)           /*�㶨�ų����Ź����б�*/
#define E2Addr_RelayFa_OADTab                   (E2Addr_ConM_OADTab+C_698Event_OADTabLen+C_CRCLen2)               /*���ɿ������������б�*/
#define E2Addr_PowerFa_OADTab                   (E2Addr_RelayFa_OADTab+C_698Event_OADTabLen+C_CRCLen2)            /*��Դ�쳣�����б�*/
#define E2Addr_RelayOpen_OADTab                 (E2Addr_PowerFa_OADTab+C_698Event_OADTabLen+C_CRCLen2)            /*��բ��¼�����б�*/
#define E2Addr_RelayClose_OADTab                (E2Addr_RelayOpen_OADTab+C_698Event_OADTabLen+C_CRCLen2)          /*��բ��¼�����б�*/
#define E2Addr_PFactorT_Over_OADTab             (E2Addr_RelayClose_OADTab+C_698Event_OADTabLen+C_CRCLen2)         /*�ܹ��ʳ��޹����б�*/
#define E2Addr_AdjTime_OADTab                   (E2Addr_PFactorT_Over_OADTab+C_698Event_OADTabLen+C_CRCLen2)      /*Уʱ�����б�*/
#define E2Addr_BroadcastTime_OADTab             (E2Addr_AdjTime_OADTab+C_698Event_OADTabLen+C_CRCLen2)            /*�㲥Уʱ�����б�*/
#define E2Addr_ProgPT_OADTab                    (E2Addr_BroadcastTime_OADTab+C_698Event_OADTabLen+C_CRCLen2)      /*ʱ�α��̹����б�*/
#define E2Addr_ProgTZ_OADTab                    (E2Addr_ProgPT_OADTab+C_698Event_OADTabLen+C_CRCLen2)             /*ʱ�����̹����б�*/
#define E2Addr_ProgWRe_OADTab                   (E2Addr_ProgTZ_OADTab+C_698Event_OADTabLen+C_CRCLen2)             /*�����ձ�̹����б�*/
#define E2Addr_ProgHol_OADTab                   (E2Addr_ProgWRe_OADTab+C_698Event_OADTabLen+C_CRCLen2)            /*�ڼ��ձ�̹����б�*/
#define E2Addr_ProgAcC_OADTab                   (E2Addr_ProgHol_OADTab+C_698Event_OADTabLen+C_CRCLen2)            /*�й���Ϸ�ʽ��̹����б�*/
#define E2Addr_ProgReC_OADTab                   (E2Addr_ProgAcC_OADTab+C_698Event_OADTabLen+C_CRCLen2)            /*�޹���Ϸ�ʽ��̹����б�*/
#define E2Addr_ProgSettD_OADTab                 (E2Addr_ProgReC_OADTab+C_698Event_OADTabLen+C_CRCLen2)            /*�����ձ�̹����б�*/
#define E2Addr_ProgTPara_OADTab                 (E2Addr_ProgSettD_OADTab+C_698Event_OADTabLen+C_CRCLen2)          /*���ʱ��̹����б�*/
#define E2Addr_ProgLad_OADTab                   (E2Addr_ProgTPara_OADTab+C_698Event_OADTabLen+C_CRCLen2)          /*���ݱ��̹����б�*/
#define E2Addr_ProgKD_OADTab                    (E2Addr_ProgLad_OADTab+C_698Event_OADTabLen+C_CRCLen2)            /*��Կ�����б�*/
#define E2Addr_MeterFa_OADTab                   (E2Addr_ProgKD_OADTab+C_698Event_OADTabLen+C_CRCLen2)             /*����оƬ�����б�*/
#define E2Addr_ClockFa_OADTab                   (E2Addr_MeterFa_OADTab+C_698Event_OADTabLen+C_CRCLen2)            /*ʱ�ӹ����б�*/
#define E2Addr_NeutralCurrentAbnormal_OADTab    (E2Addr_ClockFa_OADTab+C_698Event_OADTabLen+C_CRCLen2)            /*���ߵ����쳣*/

/*˳��Ҫ������������������ݱ�ʶ������InF_Write_Data()����CAll_Loss_Vol_OADTabLen(0x04FE1201) - CClockFa_OADTabLen(0x04FE1230)*/
#define E2Addr_All_Loss_Vol_OADTabLen           (E2Addr_NeutralCurrentAbnormal_OADTab+C_698Event_OADTabLen+C_CRCLen2)     /*ȫʧѹ�����б��ȣ�1*/
#define E2Addr_Aux_Pow_Down_OADTabLen           (E2Addr_All_Loss_Vol_OADTabLen+CLAll_Loss_Vol_OADTabLen+C_CRCLen2)        /*������Դ��������б��ȣ�1*/
#define E2Addr_Pow_Down_OADTabLen               (E2Addr_Aux_Pow_Down_OADTabLen+CLAux_Pow_Down_OADTabLen+C_CRCLen2)        /*��������б��ȣ�1*/
#define E2Addr_Pos_Ac_De_Over_OADTabLen         (E2Addr_Pow_Down_OADTabLen+CLPow_Down_OADTabLen+C_CRCLen2)                /*�����й����������¼���1*/
#define E2Addr_Rev_Ac_De_Over_OADTabLen         (E2Addr_Pos_Ac_De_Over_OADTabLen+CLPos_Ac_De_Over_OADTabLen+C_CRCLen2)    /*�����й����������¼���1*/
#define E2Addr_Qua_Re_De_Over_OADTabLen         (E2Addr_Rev_Ac_De_Over_OADTabLen+CLRev_Ac_De_Over_OADTabLen+C_CRCLen2)    /*�޹����������¼���1*/
#define E2Addr_Loss_Vol_OADTabLen               (E2Addr_Qua_Re_De_Over_OADTabLen+CLQua_Re_De_Over_OADTabLen+C_CRCLen2)    /*ʧѹ��1*/
#define E2Addr_Low_Vol_OADTabLen                (E2Addr_Loss_Vol_OADTabLen+CLLoss_Vol_OADTabLen+C_CRCLen2)                /*Ƿѹ��1*/
#define E2Addr_Over_Vol_OADTabLen               (E2Addr_Low_Vol_OADTabLen+CLLow_Vol_OADTabLen+C_CRCLen2)                  /*��ѹ��1*/
#define E2Addr_Break_Vol_OADTabLen              (E2Addr_Over_Vol_OADTabLen+CLOver_Vol_OADTabLen+C_CRCLen2)                /*���࣬1*/
#define E2Addr_RevPS_Vol_OADTabLen              (E2Addr_Break_Vol_OADTabLen+CLBreak_Vol_OADTabLen+C_CRCLen2)              /*��ѹ������1*/
#define E2Addr_RevPS_Curr_OADTabLen             (E2Addr_RevPS_Vol_OADTabLen+CLRevPS_Vol_OADTabLen+C_CRCLen2)              /*����������1*/
#define E2Addr_NoBal_Vol_OADTabLen              (E2Addr_RevPS_Curr_OADTabLen+CLRevPS_Curr_OADTabLen+C_CRCLen2)            /*��ѹ��ƽ�⣬1*/
#define E2Addr_NoBal_Curr_OADTabLen             (E2Addr_NoBal_Vol_OADTabLen+CLNoBal_Vol_OADTabLen+C_CRCLen2)              /*������ƽ�⣬1*/
#define E2Addr_SevNoBal_Curr_OADTabLen          (E2Addr_NoBal_Curr_OADTabLen+CLNoBal_Curr_OADTabLen+C_CRCLen2)            /*�������ز�ƽ�⣬1*/
#define E2Addr_Loss_Curr_OADTabLen              (E2Addr_SevNoBal_Curr_OADTabLen+CLSevNoBal_Curr_OADTabLen+C_CRCLen2)      /*ʧ����1*/
#define E2Addr_Over_Curr_OADTabLen              (E2Addr_Loss_Curr_OADTabLen+CLLoss_Curr_OADTabLen+C_CRCLen2)              /*������1*/
#define E2Addr_Break_Curr_OADTabLen             (E2Addr_Over_Curr_OADTabLen+CLOver_Curr_OADTabLen+C_CRCLen2)              /*������1*/
#define E2Addr_Power_Rev_OADTabLen              (E2Addr_Break_Curr_OADTabLen+CLBreak_Curr_OADTabLen+C_CRCLen2)            /*���ʷ���1*/
#define E2Addr_Over_Lo_OADTabLen                (E2Addr_Power_Rev_OADTabLen+CLPower_Rev_OADTabLen+C_CRCLen2)              /*���ط���1*/
#define E2Addr_Tol_Clear_OADTabLen              (E2Addr_Over_Lo_OADTabLen+CLOver_Lo_OADTabLen+C_CRCLen2)                  /*���壬1*/
#define E2Addr_De_Clear_OADTabLen               (E2Addr_Tol_Clear_OADTabLen+CLTol_Clear_OADTabLen+C_CRCLen2)              /*���壬1*/
#define E2Addr_Even_Clear_OADTabLen             (E2Addr_De_Clear_OADTabLen+CLDe_Clear_OADTabLen+C_CRCLen2)                /*�¼����㣬1*/
#define E2Addr_Program_OADTabLen                (E2Addr_Even_Clear_OADTabLen+CLEven_Clear_OADTabLen+C_CRCLen2)            /*��̼�¼��1*/
#define E2Addr_AbnorC_OADTabLen                 (E2Addr_Program_OADTabLen+CLProgram_OADTabLen+C_CRCLen2)                  /*�쳣�忨��¼��1*/
#define E2Addr_OpenW_OADTabLen                  (E2Addr_AbnorC_OADTabLen+CLAbnorC_OADTabLen+C_CRCLen2)                    /*����Ǽ�¼��1*/
#define E2Addr_OpenCW_OADTabLen                 (E2Addr_OpenW_OADTabLen+CLOpenW_OADTabLen+C_CRCLen2)                      /*����Ǽ�¼��1*/
#define E2Addr_BuyCurr_OADTabLen                (E2Addr_OpenCW_OADTabLen+CLOpenCW_OADTabLen+C_CRCLen2)                    /*�����¼��1*/
#define E2Addr_Return_M_OADTabLen               (E2Addr_BuyCurr_OADTabLen+CLBuyCurr_OADTabLen+C_CRCLen2)                  /*�˷Ѽ�¼��1*/
#define E2Addr_ConM_OADTabLen                   (E2Addr_Return_M_OADTabLen+CLReturn_M_OADTabLen+C_CRCLen2)                /*�㶨�ų����ż�¼��1*/
#define E2Addr_RelayFa_OADTabLen                (E2Addr_ConM_OADTabLen+CLConM_OADTabLen+C_CRCLen2)                        /*���ɿ���������¼��1*/
#define E2Addr_PowerFa_OADTabLen                (E2Addr_RelayFa_OADTabLen+CLRelayFa_OADTabLen+C_CRCLen2)                  /*��Դ�쳣��¼��1*/
#define E2Addr_RelayOpen_OADTabLen              (E2Addr_PowerFa_OADTabLen+CLPowerFa_OADTabLen+C_CRCLen2)                  /*��բ��¼��1*/
#define E2Addr_RelayClose_OADTabLen             (E2Addr_RelayOpen_OADTabLen+CLRelayOpen_OADTabLen+C_CRCLen2)              /*��բ��¼��1*/
#define E2Addr_PFactorT_Over_OADTabLen          (E2Addr_RelayClose_OADTabLen+CLRelayClose_OADTabLen+C_CRCLen2)            /*�ܹ��ʳ��ޣ�1*/
#define E2Addr_AdjTime_OADTabLen                (E2Addr_PFactorT_Over_OADTabLen+CLPFactorT_Over_OADTabLen+C_CRCLen2)      /*Уʱ��1*/
#define E2Addr_ProgPT_OADTabLen                 (E2Addr_AdjTime_OADTabLen+CLAdjTime_OADTabLen+C_CRCLen2)                  /*ʱ�α�1*/
#define E2Addr_ProgTZ_OADTabLen                 (E2Addr_ProgPT_OADTabLen+CLProgPT_OADTabLen+C_CRCLen2)                    /*ʱ����1*/
#define E2Addr_ProgWRe_OADTabLen                (E2Addr_ProgTZ_OADTabLen+CLProgTZ_OADTabLen+C_CRCLen2)                    /*�����գ�1*/
#define E2Addr_ProgHol_OADTabLen                (E2Addr_ProgWRe_OADTabLen+CLProgWRe_OADTabLen+C_CRCLen2)                  /*�ڼ��գ�1*/
#define E2Addr_ProgAcC_OADTabLen                (E2Addr_ProgHol_OADTabLen+CLProgHol_OADTabLen+C_CRCLen2)                  /*�й���Ϸ�ʽ��1*/
#define E2Addr_ProgReC_OADTabLen                (E2Addr_ProgAcC_OADTabLen+CLProgAcC_OADTabLen+C_CRCLen2)                  /*�޹���Ϸ�ʽ��1*/
#define E2Addr_ProgSettD_OADTabLen              (E2Addr_ProgReC_OADTabLen+CLProgReC_OADTabLen+C_CRCLen2)                  /*�����ձ�̼�¼��1*/
#define E2Addr_ProgTPara_OADTabLen              (E2Addr_ProgSettD_OADTabLen+CLProgSettD_OADTabLen+C_CRCLen2)              /*���ʱ��̼�¼��1*/
#define E2Addr_ProgLad_OADTabLen                (E2Addr_ProgTPara_OADTabLen+CLProgTPara_OADTabLen+C_CRCLen2)              /*���ݱ��̼�¼��1*/
#define E2Addr_ProgKD_OADTabLen                 (E2Addr_ProgLad_OADTabLen+CLProgLad_OADTabLen+C_CRCLen2)                  /*��Կ���±�̼�¼��1*/
#define E2Addr_MeterFa_OADTabLen                (E2Addr_ProgKD_OADTabLen+CLProgKD_OADTabLen+C_CRCLen2)                    /*����оƬ���ϼ�¼��1*/
#define E2Addr_ClockFa_OADTabLen                (E2Addr_MeterFa_OADTabLen+CLMeterFa_OADTabLen+C_CRCLen2)                  /*ʱ�ӹ��ϼ�¼��1*/
#define E2Addr_BroadcastTime_OADTabLen          (E2Addr_ClockFa_OADTabLen+CLClockFa_OADTabLen+C_CRCLen2)                  /*�㲥Уʱ��1*/
#define E2Addr_NeutralCurrentAbnormal_OADTabLen (E2Addr_BroadcastTime_OADTabLen+CLBroadcastTime_OADTabLen+C_CRCLen2)      /*���ߵ����쳣��1*/
#define C_EventOADTabLenNum                     (((E2Addr_NeutralCurrentAbnormal_OADTabLen+CLNeutralCurrentAbnormal_OADTabLen+C_CRCLen2)-E2Addr_All_Loss_Vol_OADTabLen)/(CLRelayClose_OADTabLen+C_CRCLen2))    /*�¼������б��ܸ���*/
/**********˳��Ҫ�������******************************************************************************************/

#define E2Addr_698Key                           (E2Addr_NeutralCurrentAbnormal_OADTabLen+CLNeutralCurrentAbnormal_OADTabLen+C_CRCLen2)    /*698,��֤����*/
#define E2Addr_AllowFollowUpTell                (E2Addr_698Key+CL698Key+C_CRCLen2)                                              /*�Ƿ���������ϱ�1*/
#define E2Addr_AllowAccordUpTell                (E2Addr_AllowFollowUpTell+CLAllowFollowUpTell+C_CRCLen2)                        /*�Ƿ����������ϱ�1*/
#define E2Addr_AllowMasterCall                  (E2Addr_AllowAccordUpTell+CLAllowAccordUpTell+C_CRCLen2)                        /*�Ƿ���������վͨ��1*/
#define E2Addr_UpTellChannel                    (E2Addr_AllowMasterCall+CLAllowMasterCall+C_CRCLen2)                            /*�ϱ�ͨ��12*/
#define E2Addr_BuyCurr_TMoney                   (E2Addr_UpTellChannel+CLUpTellChannel+C_CRCLen2)                                /*�ۼƹ�����4+2,����Ҫ���*/
#define E2Addr__IRAuth_Timer                    (E2Addr_BuyCurr_TMoney+CLBuyCurr_TMoney+C_CRCLen2)                              /*������֤ʱЧ4+2*/
#define E2Addr_ProgReC1                         (E2Addr__IRAuth_Timer+CL_IRAuth_Timer+C_CRCLen2)                                /*����޹�1��̴���4+2*/
#define E2Addr_ProgReC2                         (E2Addr_ProgReC1+CLProgReC1_Degree+C_CRCLen2)                                   /*����޹�2��̴���4+2*/
#define E2Addr_RTC_AdjustTemp                   (E2Addr_ProgReC2+CLProgReC2_Degree+C_CRCLen2)                                   /*RTCУ׼�¶�ֵ8+2����Ȫ����*/
#define E2Addr_RTC_AdjustTemp_End               (E2Addr_RTC_AdjustTemp+CLRTC_AdjustTemp+C_CRCLen2)                              /*RTCУ׼�¶�ֵ8+2����Ȫ����,������ַ*/
#define E2Addr_Batt_Work_Time                   (E2Addr_RTC_AdjustTemp_End)                                                     /*��ع���ʱ�䣬4+2CRC*/

#define E2Addr_LoadProfile_St                   (E2Addr_Batt_Work_Time+CLBatt_Work_Time+C_CRCLen2)
#define E2Addr_LoadP_Flash_Ear                  (E2Addr_LoadProfile_St)                                     /*����һ����¼Flashҳ��ַ����E2��ַ������CRC*/
#define E2Addr_LoadP_Flash_Late                 (E2Addr_LoadP_Flash_Ear+CLFlashAddress+C_CRCLen2)           /*���һ����¼Flashҳ��ַ����E2��ַ������CRC*/
#define E2Addr_Min_Free_Flash_Ear               (E2Addr_LoadP_Flash_Late+CLFlashAddress+C_CRCLen2)          /*����һ����¼Flash���Ե�ַ,1�ֽ����ڵ�����ʶ+��¼����E2��ַ������CRC*/
#define E2Addr_Min_Free_Flash_Late              (E2Addr_Min_Free_Flash_Ear+CLFlashAddress+C_CRCLen2)        /*���һ����¼Flashҳ��ַ����E2��ַ������CRC*/
#define E2Addr_I_Free_Flash_Ear                 (E2Addr_Min_Free_Flash_Late+CLFlashAddress+C_CRCLen2)       /*����һ����¼Flash���Ե�ַ,1�ֽ����ڵ�����ʶ+��¼����E2��ַ������CRC*/
#define E2Addr_I_Free_Flash_Late                (E2Addr_I_Free_Flash_Ear+CLFlashAddress+C_CRCLen2)          /*���һ����¼Flashҳ��ַ����E2��ַ������CRC*/
#define E2Addr_H_Free_Flash_Ear                 (E2Addr_I_Free_Flash_Late+CLFlashAddress+C_CRCLen2)         /*����һ����¼Flash���Ե�ַ,1�ֽ����ڵ�����ʶ+��¼����E2��ַ������CRC*/
#define E2Addr_H_Free_Flash_Late                (E2Addr_H_Free_Flash_Ear+CLFlashAddress+C_CRCLen2)          /*���һ����¼Flashҳ��ַ����E2��ַ������CRC*/
#define E2Addr_D_Free_Flash_Ear                 (E2Addr_H_Free_Flash_Late+CLFlashAddress+C_CRCLen2)         /*����һ����¼Flash���Ե�ַ,1�ֽ����ڵ�����ʶ+��¼����E2��ַ������CRC*/
#define E2Addr_D_Free_Flash_Late                (E2Addr_D_Free_Flash_Ear+CLFlashAddress+C_CRCLen2)          /*���һ����¼Flashҳ��ַ����E2��ַ������CRC*/
#define E2Addr_M_Free_Flash_Ear                 (E2Addr_D_Free_Flash_Late+CLFlashAddress+C_CRCLen2)         /*����һ����¼Flash���Ե�ַ,1�ֽ����ڵ�����ʶ+��¼����E2��ַ������CRC*/
#define E2Addr_M_Free_Flash_Late                (E2Addr_M_Free_Flash_Ear+CLFlashAddress+C_CRCLen2)          /*���һ����¼Flashҳ��ַ����E2��ַ������CRC*/
#define E2Addr_TZ_Free_Flash_Ear                (E2Addr_M_Free_Flash_Late+CLFlashAddress+C_CRCLen2)         /*����һ����¼Flash���Ե�ַ,1�ֽ����ڵ�����ʶ+��¼����E2��ַ������CRC*/
#define E2Addr_TZ_Free_Flash_Late               (E2Addr_TZ_Free_Flash_Ear+CLFlashAddress+C_CRCLen2)         /*���һ����¼Flashҳ��ַ����E2��ַ������CRC*/
#define E2Addr_PT_Free_Flash_Ear                (E2Addr_TZ_Free_Flash_Late+CLFlashAddress+C_CRCLen2)        /*����һ����¼Flash���Ե�ַ,1�ֽ����ڵ�����ʶ+��¼����E2��ַ������CRC*/
#define E2Addr_PT_Free_Flash_Late               (E2Addr_PT_Free_Flash_Ear+CLFlashAddress+C_CRCLen2)         /*���һ����¼Flashҳ��ַ����E2��ַ������CRC*/
#define E2Addr_R_Free_Flash_Ear                 (E2Addr_PT_Free_Flash_Late+CLFlashAddress+C_CRCLen2)        /*����һ����¼Flash���Ե�ַ,1�ֽ����ڵ�����ʶ+��¼����E2��ַ������CRC*/
#define E2Addr_R_Free_Flash_Late                (E2Addr_R_Free_Flash_Ear+CLFlashAddress+C_CRCLen2)          /*���һ����¼Flashҳ��ַ����E2��ַ������CRC*/
#define E2Addr_L_Free_Flash_Ear                 (E2Addr_R_Free_Flash_Late+CLFlashAddress+C_CRCLen2)         /*����һ����¼Flash���Ե�ַ,1�ֽ����ڵ�����ʶ+��¼����E2��ַ������CRC*/
#define E2Addr_L_Free_Flash_Late                (E2Addr_L_Free_Flash_Ear+CLFlashAddress+C_CRCLen2)          /*���һ����¼Flashҳ��ַ����E2��ַ������CRC*/
#define E2Addr_Sett_Free_Flash_Ear              (E2Addr_L_Free_Flash_Late+CLFlashAddress+C_CRCLen2)         /*����һ����¼Flash���Ե�ַ,1�ֽ����ڵ�����ʶ+��¼����E2��ַ������CRC*/
#define E2Addr_Sett_Free_Flash_Late             (E2Addr_Sett_Free_Flash_Ear+CLFlashAddress+C_CRCLen2)       /*���һ����¼Flashҳ��ַ����E2��ַ������CRC*/
#define E2Addr_Y_Free_Flash_Ear                 (E2Addr_Sett_Free_Flash_Late+CLFlashAddress+C_CRCLen2)      /*����һ����¼Flash���Ե�ַ,1�ֽ����ڵ�����ʶ+��¼����E2��ַ������CRC*/
#define E2Addr_Y_Free_Flash_Late                (E2Addr_Y_Free_Flash_Ear+CLFlashAddress+C_CRCLen2)          /*���һ����¼Flashҳ��ַ����E2��ַ������CRC,4+2���ݳ���*/
#define E2Addr_Sett_Freeze_Flash_Ear            (E2Addr_Y_Free_Flash_Late+CLFlashAddress+C_CRCLen2)         /*���һ����¼Flashҳ��ַ����E2��ַ������CRC,4+2���ݳ���*/
#define E2Addr_Sett_Freeze_Flash_Late           (E2Addr_Sett_Freeze_Flash_Ear+CLFlashAddress+C_CRCLen2)     /*���һ����¼Flashҳ��ַ����E2��ַ������CRC,4+2���ݳ���*/

#define E2Addr_SafeModeParaNat3_Num             (E2Addr_Sett_Freeze_Flash_Late+CLFlashAddress+C_CRCLen2)    /*��ȫģʽ����,����3,Ԫ�ظ���������CRC,1+2���ݳ���*/

#define E2Addr_Min_Free_Flash_Ear1              (E2Addr_SafeModeParaNat3_Num+CLSafeModeParaNat3_Num+C_CRCLen2)                        /*���Ӷ���8�ַ�����Flash��¼�洢����������¼Flash��ַ��8*(4+2+4+2),96,���硢��������� CRC*/
#define E2Addr_Min_Free_FlashAddr_Allo          (E2Addr_Min_Free_Flash_Ear1+8*(CLFlashAddress+C_CRCLen2+CLFlashAddress+C_CRCLen2))    /*���Ӷ���8�ַ�����Flash��¼�洢��ַ������ʼ��������ַ��E2��8*(4+4),64+2 CRC*/

/*698����645ʱ����*/
#define E2Addr_Relay_Delay_Time_645             (E2Addr_Min_Free_FlashAddr_Allo+8*(CLFlashAddress+CLFlashAddress)+C_CRCLen2)          /*���ڴ洢645��բ��ʱʱ��2�ֽ�+2�ֽ�CRC*/
#define E2Addr_Drive_Report_Mode_645            (E2Addr_Relay_Delay_Time_645+CLRelay_Delay_Time_645+C_CRCLen2)                        /*���ڴ洢645�����ϱ�ģʽ��8�ֽ�+2�ֽ�CRC*/
#define E2Addr_Meter_Work_Char1_645             (E2Addr_Drive_Report_Mode_645+CLDrive_Report_Mode_645+C_CRCLen2)                      /*���ڴ洢645�������������1 1�ֽ�+2�ֽ�CRC*/
#define E2Addr_ProgPT_CurrentPart_Degree        (E2Addr_Meter_Work_Char1_645+CLMeter_Work_Char1_645+C_CRCLen2)                        /*���ڴ洢645ʱ�α���� 4�ֽ�+2�ֽ�CRC*/
#define E2Addr_ProgTZ_CurrentPart_Degree        (E2Addr_ProgPT_CurrentPart_Degree+CLProgPT_CurrentPart_Degree+C_CRCLen2)              /*���ڴ洢645ʱ������� 4�ֽ�+2�ֽ�CRC*/
#define E2Addr_Program_Degree_645               (E2Addr_ProgTZ_CurrentPart_Degree+CLProgTZ_CurrentPart_Degree+C_CRCLen2)              /*���ڴ洢645��̼�¼���� 3�ֽ�+2�ֽ�CRC*/
#define E2Addr_Meter_Work_Char1                 (E2Addr_Program_Degree_645+CLProgram_Degree_645+C_CRCLen2)                            /*���ڴ洢698�������������1 1�ֽ�+2�ֽ�CRC*/

#define E2Addr_ParaEnd                 			(E2Addr_Meter_Work_Char1+CLMeter_Work_Char1+C_CRCLen2)                           	  /*����*/

/***********����E2�������ݿռ䣬��ʣ����42byte**************/
#if ((E2Addr_ParaEnd > 0x4600)?1:0) /*����������*/
	#error "EEPROM Capacity Exhausted!"
#endif

/****************************************����У������,E2������CRC,Ԥ��2kbyte*******************************************/
#define E2Addr_MeterIC_St                       0x4600                                                                  /*У�����ݴ�E2��ʼ��ַ*/
#define E2Addr_MeterIC_End                      (E2Addr_MeterIC_St+C_MeterICDataNum_T*(C_MeterICE2ResLen+C_CRCLen2))    /*У�����ݴ�E2������ַ*/

/*����΢RTC��У����*/
#define E2Addr_temperatureAddr                  (E2Addr_MeterIC_End)                                                    /*�¶Ȳ���ϵ����E2,11+2 CRC*/
#define E2Addr_ptatvalueAddr                    (E2Addr_temperatureAddr+ee_temperature_lenth+C_CRCLen2)                 /*���²���¶�ADCҳ��ַE2,42+2CRC*/
#define E2Addr_ptatvalue_ltAddr                 (E2Addr_ptatvalueAddr+ee_ptatvalue_lenth+C_CRCLen2)                     /*���²���¶�ADCҳ��ַE2,30+2+2CRC*/
#define E2Addr_ptatvalue_htAddr                 (E2Addr_ptatvalue_ltAddr+ee_ptatvalue_lt_lenth+2+C_CRCLen2)             /*���²���¶�ADCҳ��ַE2,30+2+2CRC*/
#define E2Addr_trimvalueAddr                    (E2Addr_ptatvalue_htAddr+ee_ptatvalue_ht_lenth+2+C_CRCLen2)             /*���²���¶Ȳ���ֵҳ��ַE2,42+2CRC*/
#define E2Addr_trimvalue_ltAddr                 (E2Addr_trimvalueAddr+ee_trimvalue_lenth+C_CRCLen2)                     /*���²���¶Ȳ���ֵҳ��ַE2,30+2+2CRC*/
#define E2Addr_trimvalue_htAddr                 (E2Addr_trimvalue_ltAddr+ee_trimvalue_lt_lenth+2+C_CRCLen2)             /*���²���¶Ȳ���ֵҳ��ַE2,30+2+2CRC*/
#define E2Addr_rtcadj_timeAddr                  (E2Addr_trimvalue_htAddr+ee_trimvalue_ht_lenth+2+C_CRCLen2)             /*д���¶����Уֵʱʱ���¼ҳ��ַ(ʼ�ղ���),10+2CRC*/

#define E2Addr_Odd_Harmonic_AddData1            (E2Addr_rtcadj_timeAddr+ee_rtcadjtime_lenth+C_CRCLen2)                  /*���г������ֵ1,(����:2.8A~4A����),3+2CRC*/
#define E2Addr_Odd_Harmonic_AddData2            (E2Addr_Odd_Harmonic_AddData1+CL_OddHar_AddData1+C_CRCLen2)             /*���г������ֵ2,(����:1.4A~2A����),3+2CRC*/

#define E2Addr_Even_Harmonic_AddData_A0         (E2Addr_Odd_Harmonic_AddData2+CL_OddHar_AddData2+C_CRCLen2)             /*ż��г������ֵ1,(0.5L����),3+2CRC*/
#define E2Addr_Even_Harmonic_AddData_A1         (E2Addr_Even_Harmonic_AddData_A0+CL_EvenHar_AddData_A0+C_CRCLen2)       /*ż��г������ֵ2,(0.5L����),3+2CRC*/
#define E2Addr_Even_Harmonic_AddData_B0         (E2Addr_Even_Harmonic_AddData_A1+CL_EvenHar_AddData_A1+C_CRCLen2)       /*ż��г������ֵ2,(0.5L����),3+2CRC*/
#define E2Addr_Even_Harmonic_AddData_B1         (E2Addr_Even_Harmonic_AddData_B0+CL_EvenHar_AddData_B0+C_CRCLen2)       /*ż��г������ֵ1,(0.5L����),3+2CRC*/
#define E2Addr_Even_Harmonic_AddData_C0         (E2Addr_Even_Harmonic_AddData_B1+CL_EvenHar_AddData_B1+C_CRCLen2)       /*ż��г������ֵ2,(0.5L����),3+2CRC*/
#define E2Addr_Even_Harmonic_AddData_C1         (E2Addr_Even_Harmonic_AddData_C0+CL_EvenHar_AddData_C0+C_CRCLen2)       /*ż��г������ֵ2,(0.5L����),3+2CRC*/
/******************************����E2����У����������ݿռ䣬��ʣ������119byte*******************************/

/****************************************E2 1������,0xD800-FFFE**********************************************/
#define E2Addr_Y_Com_Ac_Tol_En_St               E2_Remaind_Space                                                        /*����������ʼ��ַ*/
#define E2Addr_Y_Com_Ac_Tol_En_1                E2Addr_Y_Com_Ac_Tol_En_St                                               /*��1��������ս���ʱ�估��1�������������й����ۼ��õ���*/
#define E2Addr_Y_Com_Ac_Tol_En_2                (E2Addr_Y_Com_Ac_Tol_En_1+CLY_Com_Ac_Tol_En_1)                          /*��2��������ս���ʱ�估��2�������������й����ۼ��õ���*/
#define E2Addr_Y_Com_Ac_Tol_En_3                (E2Addr_Y_Com_Ac_Tol_En_2+CLY_Com_Ac_Tol_En_2)                          /*��3��������ս���ʱ�估��3�������������й����ۼ��õ���*/
#define E2Addr_Y_Com_Ac_Tol_En_4                (E2Addr_Y_Com_Ac_Tol_En_3+CLY_Com_Ac_Tol_En_3)                          /*��4��������ս���ʱ�估��4�������������й����ۼ��õ���*/
#define E2Addr_Load_Rec_Time_Year               (E2Addr_Y_Com_Ac_Tol_En_4+CLY_Com_Ac_Tol_En_4)                          /*���ɼ�¼��ʼʱ��,YYMMDDhhmm*/
#define E2Addr_Y_Com_Ac_Tol_En_End              E2Addr_Load_Rec_Time_Year                                               /*��������������ַ*/

#define E2Addr_Auto_Dis_1ScreenCode             (E2Addr_Load_Rec_Time_Year+CLLoad_Rec_Time_Year)                        /*�Զ�ѭ����ʾ��1-99����ʾ���룬99*(9+2)=693*/
#define E2Addr_Key_Dis_1ScreenCode              (E2Addr_Auto_Dis_1ScreenCode+99*(CLAuto_Dis_1ScreenCode+C_CRCLen2))     /*����ѭ����ʾ��1-99����ʾ���룬99*(9+2)=693*/

/*�������պ������޸�Ϊ20��*/
#define E2Addr_Holidy_PT_Table1                 (E2Addr_Key_Dis_1ScreenCode+99*(CLKey_Dis_1ScreenCode+C_CRCLen2))       /*��1-20�����������ڼ���ʱ�α��*/
#if 0
#define E2Addr_Holidy_PT_Table_Fa01             (E2Addr_Holidy_PT_Table1)                                               /*��1-20�����������ڼ���ʱ�α��*/
#define E2Addr_Holidy_PT_Table_Fa02             (E2Addr_Holidy_PT_Table_Fa01+CLHolidy_PT_Table_Fa01)                    /*��64-126�����������ڼ���ʱ�α��*/
#define E2Addr_Holidy_PT_Table_Fa03             (E2Addr_Holidy_PT_Table_Fa02+CLHolidy_PT_Table_Fa02)                    /*��127-189�����������ڼ���ʱ�α��*/
#define E2Addr_Holidy_PT_Table_Fa04             (E2Addr_Holidy_PT_Table_Fa03+CLHolidy_PT_Table_Fa03)                    /*��190-252�����������ڼ���ʱ�α��*/
#define E2Addr_Holidy_PT_Table_Fa05             (E2Addr_Holidy_PT_Table_Fa04+CLHolidy_PT_Table_Fa04)                    /*��253-254�����������ڼ���ʱ�α��*/
#endif

#define E2Addr_EquipmentDis                     (E2Addr_Holidy_PT_Table1+CLHolidy_PT_Table1*20)                   /*�豸������32*/

#define E2Addr_Factory_Number                   (E2Addr_EquipmentDis+CLEquipmentDis)                              /*���ұ��*/
#define E2Addr_Factory_Softw_Version            (E2Addr_Factory_Number+CLFactory_Number)                          /*��������汾��*/
#define E2Addr_Factory_Softw_VersionDate        (E2Addr_Factory_Softw_Version+CLFactory_Softw_Version)            /*��������汾���ڣ�6*/
#define E2Addr_Factory_Hardw_Version            (E2Addr_Factory_Softw_VersionDate+CLFactory_Softw_VersionDate)    /*Ӳ���汾��*/
#define E2Addr_Factory_Hardw_VersionDate        (E2Addr_Factory_Hardw_Version+CLFactory_Hardw_Version)            /*����Ӳ���汾����,6*/
#define E2Addr_Factory_ExternSign               (E2Addr_Factory_Hardw_VersionDate+CLFactory_Hardw_VersionDate)    /*������չ��Ϣ,8*/

#if 0	/*����ʹ��*/
#define E2Addr_FactoryInfomation         (E2Addr_SafeModePara+CLSafeModePara+C_CRCLen2)                           /*������Ϣ*/
#endif

#define E2Addr_Meter_CommPro1                   (E2Addr_Factory_ExternSign+CLFactory_ExternSign)                  /*���֧��ͨ��Э��1*/
#define E2Addr_Meter_CommPro2                   (E2Addr_Meter_CommPro1+CLMeter_CommPro1)                          /*���֧��ͨ��Э��2*/

#define E2Addr_Softw_Record_Number              (E2Addr_Meter_CommPro2+CLMeter_CommPro2)                          /*���������*/

#define E2Addr_Control_ExecuteState             (E2Addr_Softw_Record_Number+CLSoftw_Record_Number)                /*��������ִ��״̬�֣�2�ֽ�*/
#define E2Addr_Control_ErrorState               (E2Addr_Control_ExecuteState+CLControl_ExecuteState)              /*�����������״̬�֣�2�ֽ�*/

#define E2Addr_SafeModeParaNat3                 (E2Addr_Control_ErrorState+CLControl_ErrorState)                  /*��ȫģʽ����,����3��CRC��1+50*4*/

#define E2Addr_ClientAddr                       (E2Addr_SafeModeParaNat3+CLSafeModeParaNat3+C_CRCLen2)            /*��ǰ���ӵĿͻ�����ַ 1*/

#define E2NewReportList                         (E2Addr_ClientAddr+CLClientAddr)                                  /*�����ϱ��б�70*2+1+2CRC*/
#define E2Drive_Report_State_New                (E2NewReportList+CLNewReportList+C_CRCLen2)                       /*�����ϱ�״̬��4+32+2CRC*/

#define E2Addr_Clock_FaultTime                  (E2Drive_Report_State_New+CLDrive_Report_State_New+C_CRCLen2)     /*�㲥Уʱ�쳣ʱ�ӹ���ʱ��*/
#define E2Addr_Even_Harmonic_Time               (E2Addr_Clock_FaultTime+CLClock_FaultTime)                        /*ż��г��������ʱ��Ĭ��24h*60min*/
#define E2Addr_CDoubleAgreementFlag             (E2Addr_Even_Harmonic_Time+CL_EvenHar_Time)                       /*�Ƿ�˫Э��ı�־����Ҫ������Э��汾��һ����������*/
/***********����E2 1�����ݿռ䣬��ʣ����1996byte**************/

/*******************Flash��СΪ64MBit��4MByte��ÿҳ4kByte����2048ҳ***********************/
/****************************************��Flash����**************************************/
#define C_OneFlashPage                   0x00001000                                      /*ÿҳFlash��С*/
#define C_TenFlashPage                   0x0000A000
#define C_Flash_Max_Addr                 0x007FFFFF                                      /*Flash����ַ*/

/**********������ܹ�345���ֽڣ�ÿҳFlash 4092/345=11�Σ�12�β��ö�ҳ�洢��0~0x3000��4ҳ**********/
#define SettEn_Data_Len                  345                                             /*����������ݳ���*/
#define FlashStAddr_SettEn               0x00000000                                      /*�������Flash��ҳ��ַ*/
#define FlashEndAddr_SettEn              (FlashStAddr_SettEn+C_OneFlashPage*3)           /*�������Flashβҳ��ַ*/

/*********************�����ս���ʱ����,��4���ֽڣ�ÿҳFlash 4092/4=1023��12�β�����żҳ�洢****6**4~5*******/
#define SettTime_Data_Len                4                                               /*�����ս���ʱ�����ݳ���*/
#define FlashStAddr_SettTime             (FlashEndAddr_SettEn+C_OneFlashPage)            /*�����ս���ʱ��Flash��ҳ��ַ*/
#define FlashEndAddr_SettTime            (FlashStAddr_SettTime+C_OneFlashPage)           /*�����ս���ʱ��Flashβҳ��ַ*/

/*********************698���㶳�ᣬ����ԭ���Ľ�����ܼ���������������Ľ�����ܡ�������������û����****10********/
#define FlashStAddr_Sett_Free            0x00000000                                       /*�������Flash��ҳ��ַ*/
#define FlashEndAddr_Sett_Free           (FlashStAddr_Sett_Free+C_OneFlashPage*9)         /*�������Flashβҳ��ַ*/

/*********************�������¼�***698�¼���¼��Ĭ�Ϲ����б���������ԭ645��¼������*****************************/
/*********************ȫʧѹ��15���ֽڣ�ÿҳFlash 4092/15=272��698��22��10�β�����żҳ�洢********12****10~11*****/
#define All_Loss_Vol_Data_Len            15                                               /*ȫʧѹ���ݳ���*/
#define FlashStAddr_All_Loss_Vol         (FlashEndAddr_Sett_Free+C_OneFlashPage)          /*ȫʧѹFlash��ҳ��ַ*/
#define FlashEndAddr_All_Loss_Vol        (FlashStAddr_All_Loss_Vol+C_OneFlashPage)        /*ȫʧѹFlashβҳ��ַ*/

/*********************������Դ���繲12���ֽڣ�ÿҳFlash 4092/12=341��301110�β�����żҳ�洢****14******12~13*******/
#define Aux_Pow_Down_Data_Len            12                                               /*������Դ�������ݳ���*/
#define FlashStAddr_Aux_Pow_Down         (FlashEndAddr_All_Loss_Vol+C_OneFlashPage)       /*������Դ����Flash��ҳ��ַ*/
#define FlashEndAddr_Aux_Pow_Down        (FlashStAddr_Aux_Pow_Down+C_OneFlashPage)        /*������Դ����Flashβҳ��ַ*/

/*********************��Դ���繲12���ֽڣ�ÿҳFlash 4092/12=341��698��19��10�β�����żҳ�洢*********16****14~15****/
#define Pow_Down_Data_Len                12                                               /*��Դ�������ݳ���*/
#define FlashStAddr_Pow_Down             (FlashEndAddr_Aux_Pow_Down+C_OneFlashPage)       /*��Դ����Flash��ҳ��ַ*/
#define FlashEndAddr_Pow_Down            (FlashStAddr_Pow_Down+C_OneFlashPage*2)          /*��Դ����Flashβҳ��ַ*/

/*********************�������޹�20���ֽڣ�ÿҳFlash 4092/20=204��698��27��10�β�����żҳ�洢*********28********/
#define De_Over_Data_Len                 20                                               /*�����������ݳ���*/
#define FlashStAddr_Pos_Ac_De_Over       (FlashEndAddr_Pow_Down+C_OneFlashPage)           /*�����й���������Flash��ҳ��ַ*/
#define FlashEndAddr_Pos_Ac_De_Over      (FlashStAddr_Pos_Ac_De_Over+C_OneFlashPage)      /*�����й���������Flashβҳ��ַ*/
#define FlashStAddr_Rev_Ac_De_Over       (FlashEndAddr_Pos_Ac_De_Over+C_OneFlashPage)     /*�����й���������Flash��ҳ��ַ*/
#define FlashEndAddr_Rev_Ac_De_Over      (FlashStAddr_Rev_Ac_De_Over+C_OneFlashPage)      /*�����й���������Flashβҳ��ַ*/
#define FlashStAddr_Qua1_Re_De_Over      (FlashEndAddr_Rev_Ac_De_Over+C_OneFlashPage)     /*1�����޹���������Flash��ҳ��ַ*/
#define FlashEndAddr_Qua1_Re_De_Over     (FlashStAddr_Qua1_Re_De_Over+C_OneFlashPage)     /*1�����޹���������Flashβҳ��ַ*/
#define FlashStAddr_Qua2_Re_De_Over      (FlashEndAddr_Qua1_Re_De_Over+C_OneFlashPage)    /*2�����޹���������Flash��ҳ��ַ*/
#define FlashEndAddr_Qua2_Re_De_Over     (FlashStAddr_Qua2_Re_De_Over+C_OneFlashPage)     /*2�����޹���������Flashβҳ��ַ*/
#define FlashStAddr_Qua3_Re_De_Over      (FlashEndAddr_Qua2_Re_De_Over+C_OneFlashPage)    /*3�����޹���������Flash��ҳ��ַ*/
#define FlashEndAddr_Qua3_Re_De_Over     (FlashStAddr_Qua3_Re_De_Over+C_OneFlashPage)     /*3�����޹���������Flashβҳ��ַ*/
#define FlashStAddr_Qua4_Re_De_Over      (FlashEndAddr_Qua3_Re_De_Over+C_OneFlashPage)    /*4�����޹���������Flash��ҳ��ַ*/
#define FlashEndAddr_Qua4_Re_De_Over     (FlashStAddr_Qua4_Re_De_Over+C_OneFlashPage)     /*4�����޹���������Flashβҳ��ַ*/

/*********************ʧѹ��¼��195���ֽڣ�ÿҳFlash 4092/195=20��698��230��4092/230=17��10�β�����żҳ�洢********34*********/
#define Loss_Vol_Data_Len                195                                              /*ʧѹ���ݳ���*/
#define FlashStAddr_LossA_Vol            (FlashEndAddr_Qua4_Re_De_Over+C_OneFlashPage)    /*A��ʧѹFlash��ҳ��ַ*/
#define FlashEndAddr_LossA_Vol           (FlashStAddr_LossA_Vol+C_OneFlashPage)           /*A��ʧѹFlashβҳ��ַ*/
#define FlashStAddr_LossB_Vol            (FlashEndAddr_LossA_Vol+C_OneFlashPage)          /*B��ʧѹFlash��ҳ��ַ*/
#define FlashEndAddr_LossB_Vol           (FlashStAddr_LossB_Vol+C_OneFlashPage)           /*B��ʧѹFlashβҳ��ַ*/
#define FlashStAddr_LossC_Vol            (FlashEndAddr_LossB_Vol+C_OneFlashPage)          /*C��ʧѹFlash��ҳ��ַ*/
#define FlashEndAddr_LossC_Vol           (FlashStAddr_LossC_Vol+C_OneFlashPage)           /*C��ʧѹFlashβҳ��ַ*/

/*********************Ƿѹ��¼��195���ֽڣ�ÿҳFlash 4092/195=20��698��230��4092/230=17��10�β�����żҳ�洢*********40********/
#define Low_Vol_Data_Len                 195                                              /*Ƿѹ���ݳ���*/
#define FlashStAddr_LowA_Vol             (FlashEndAddr_LossC_Vol+C_OneFlashPage)          /*A��ǷѹFlash��ҳ��ַ*/
#define FlashEndAddr_LowA_Vol            (FlashStAddr_LowA_Vol+C_OneFlashPage)            /*A��ǷѹFlashβҳ��ַ*/
#define FlashStAddr_LowB_Vol             (FlashEndAddr_LowA_Vol+C_OneFlashPage)           /*B��ǷѹFlash��ҳ��ַ*/
#define FlashEndAddr_LowB_Vol            (FlashStAddr_LowB_Vol+C_OneFlashPage)            /*B��ǷѹFlashβҳ��ַ*/
#define FlashStAddr_LowC_Vol             (FlashEndAddr_LowB_Vol+C_OneFlashPage)           /*C��ǷѹFlash��ҳ��ַ*/
#define FlashEndAddr_LowC_Vol            (FlashStAddr_LowC_Vol+C_OneFlashPage)            /*C��ǷѹFlashβҳ��ַ*/

/*********************��ѹ��¼��195���ֽڣ�ÿҳFlash 4092/195=20��698��230��4092/230=17��10�β�����żҳ�洢********46*********/
#define Over_Vol_Data_Len                195                                              /*��ѹ���ݳ���*/
#define FlashStAddr_OverA_Vol            (FlashEndAddr_LowC_Vol+C_OneFlashPage)           /*A���ѹFlash��ҳ��ַ*/
#define FlashEndAddr_OverA_Vol           (FlashStAddr_OverA_Vol+C_OneFlashPage)           /*A���ѹFlashβҳ��ַ*/
#define FlashStAddr_OverB_Vol            (FlashEndAddr_OverA_Vol+C_OneFlashPage)          /*B���ѹFlash��ҳ��ַ*/
#define FlashEndAddr_OverB_Vol           (FlashStAddr_OverB_Vol+C_OneFlashPage)           /*B���ѹFlashβҳ��ַ*/
#define FlashStAddr_OverC_Vol            (FlashEndAddr_OverB_Vol+C_OneFlashPage)          /*C���ѹFlash��ҳ��ַ*/
#define FlashEndAddr_OverC_Vol           (FlashStAddr_OverC_Vol+C_OneFlashPage)           /*C���ѹFlashβҳ��ַ*/

/*********************�����¼��195���ֽڣ�ÿҳFlash 4092/195=20��698��230��4092/230=17��10�β�����żҳ�洢*******52**********/
#define Break_Vol_Data_Len               195                                              /*�������ݳ���*/
#define FlashStAddr_BreakA_Vol           (FlashEndAddr_OverC_Vol+C_OneFlashPage)          /*A�����Flash��ҳ��ַ*/
#define FlashEndAddr_BreakA_Vol          (FlashStAddr_BreakA_Vol+C_OneFlashPage)          /*A����ѹFlashβҳ��ַ*/
#define FlashStAddr_BreakB_Vol           (FlashEndAddr_BreakA_Vol+C_OneFlashPage)         /*B�����Flash��ҳ��ַ*/
#define FlashEndAddr_BreakB_Vol          (FlashStAddr_BreakB_Vol+C_OneFlashPage)          /*B�����Flashβҳ��ַ*/
#define FlashStAddr_BreakC_Vol           (FlashEndAddr_BreakB_Vol+C_OneFlashPage)         /*C�����Flash��ҳ��ַ*/
#define FlashEndAddr_BreakC_Vol          (FlashStAddr_BreakC_Vol+C_OneFlashPage)          /*C�����Flashβҳ��ַ*/

/*********************��ѹ������140���ֽڣ�ÿҳFlash 4092/140=29��698��147��10�β�����żҳ�洢*********54********/
#define RevPS_Vol_Data_Len               140                                              /*��ѹ���������ݳ���*/
#define FlashStAddr_RevPS_Vol            (FlashEndAddr_BreakC_Vol+C_OneFlashPage)         /*��ѹ������Flash��ҳ��ַ*/
#define FlashEndAddr_RevPS_Vol           (FlashStAddr_RevPS_Vol+C_OneFlashPage)           /*��ѹ������Flashβҳ��ַ*/

/*********************����������140���ֽڣ�ÿҳFlash 4092/140=29��10�β�����żҳ�洢********56*********/
#define RevPS_Curr_Data_Len              140                                              /*�������������ݳ���*/
#define FlashStAddr_RevPS_Curr           (FlashEndAddr_RevPS_Vol+C_OneFlashPage)          /*����������Flash��ҳ��ַ*/
#define FlashEndAddr_RevPS_Curr          (FlashStAddr_RevPS_Curr+C_OneFlashPage)          /*����������Flashβҳ��ַ*/

/*********************��ѹ��ƽ�⹲143���ֽڣ�ÿҳFlash 4092/143=28��698��150��10�β�����żҳ�洢*********58********/
#define NoBal_Vol_Data_Len               143                                              /*��ѹ��ƽ�����ݳ���*/
#define FlashStAddr_NoBal_Vol            (FlashEndAddr_RevPS_Curr+C_OneFlashPage)         /*��ѹ��ƽ��Flash��ҳ��ַ*/
#define FlashEndAddr_NoBal_Vol           (FlashStAddr_NoBal_Vol+C_OneFlashPage)           /*��ѹ��ƽ��Flashβҳ��ַ*/

/*********************������ƽ�⹲143���ֽڣ�ÿҳFlash 4092/143=28��698��150��10�β�����żҳ�洢********60*********/
#define NoBal_Curr_Data_Len              143                                              /*������ƽ�����ݳ���*/
#define FlashStAddr_NoBal_Curr           (FlashEndAddr_NoBal_Vol+C_OneFlashPage)          /*������ƽ��Flash��ҳ��ַ*/
#define FlashEndAddr_NoBal_Curr          (FlashStAddr_NoBal_Curr+C_OneFlashPage)          /*������ƽ��Flashβҳ��ַ*/

/*********************�������ز�ƽ�⹲143���ֽڣ�ÿҳFlash 4092/143=28��698��150��10�β�����żҳ�洢*****62************/
#define SevNoBal_Curr_Data_Len           143                                              /*�������ز�ƽ�����ݳ���*/
#define FlashStAddr_SevNoBal_Curr        (FlashEndAddr_NoBal_Curr+C_OneFlashPage)         /*�������ز�ƽ��Flash��ҳ��ַ*/
#define FlashEndAddr_SevNoBal_Curr       (FlashStAddr_SevNoBal_Curr+C_OneFlashPage)       /*�������ز�ƽ��Flashβҳ��ַ*/

/*********************ʧ����179���ֽڣ�ÿҳFlash 4092/179=22��698��214��4092/214=19��10�β�����żҳ�洢**********68*******/
#define Loss_Curr_Data_Len               179                                              /*ʧ�����ݳ���*/
#define FlashStAddr_LossA_Curr           (FlashEndAddr_SevNoBal_Curr+C_OneFlashPage)      /*A��ʧ��Flash��ҳ��ַ*/
#define FlashEndAddr_LossA_Curr          (FlashStAddr_LossA_Curr+C_OneFlashPage)          /*A��ʧ��Flashβҳ��ַ*/
#define FlashStAddr_LossB_Curr           (FlashEndAddr_LossA_Curr+C_OneFlashPage)         /*B��ʧ��Flash��ҳ��ַ*/
#define FlashEndAddr_LossB_Curr          (FlashStAddr_LossB_Curr+C_OneFlashPage)          /*B��ʧ��Flashβҳ��ַ*/
#define FlashStAddr_LossC_Curr           (FlashEndAddr_LossB_Curr+C_OneFlashPage)         /*C��ʧ��Flash��ҳ��ַ*/
#define FlashEndAddr_LossC_Curr          (FlashStAddr_LossC_Curr+C_OneFlashPage)          /*C��ʧ��Flashβҳ��ַ*/

/*********************������179���ֽڣ�ÿҳFlash 4092/179=22��698��214��4092/214=19��10�β�����żҳ�洢**********74*******/
#define Over_Curr_Data_Len               179                                              /*�������ݳ���*/
#define FlashStAddr_OverA_Curr           (FlashEndAddr_LossC_Curr+C_OneFlashPage)         /*A�����Flash��ҳ��ַ*/
#define FlashEndAddr_OverA_Curr          (FlashStAddr_OverA_Curr+C_OneFlashPage)          /*A�����Flashβҳ��ַ*/
#define FlashStAddr_OverB_Curr           (FlashEndAddr_OverA_Curr+C_OneFlashPage)         /*B�����Flash��ҳ��ַ*/
#define FlashEndAddr_OverB_Curr          (FlashStAddr_OverB_Curr+C_OneFlashPage)          /*B�����Flashβҳ��ַ*/
#define FlashStAddr_OverC_Curr           (FlashEndAddr_OverB_Curr+C_OneFlashPage)         /*C�����Flash��ҳ��ַ*/
#define FlashEndAddr_OverC_Curr          (FlashStAddr_OverC_Curr+C_OneFlashPage)          /*C�����Flashβҳ��ַ*/

/*********************������179���ֽڣ�ÿҳFlash 4092/179=22��698��214��4092/214=19��10�β�����żҳ�洢*********80********/
#define Break_Curr_Data_Len              179                                              /*�������ݳ���*/
#define FlashStAddr_BreakA_Curr          (FlashEndAddr_OverC_Curr+C_OneFlashPage)         /*A�����Flash��ҳ��ַ*/
#define FlashEndAddr_BreakA_Curr         (FlashStAddr_BreakA_Curr+C_OneFlashPage)         /*A�����Flashβҳ��ַ*/
#define FlashStAddr_BreakB_Curr          (FlashEndAddr_BreakA_Curr+C_OneFlashPage)        /*B�����Flash��ҳ��ַ*/
#define FlashEndAddr_BreakB_Curr         (FlashStAddr_BreakB_Curr+C_OneFlashPage)         /*B�����Flashβҳ��ַ*/
#define FlashStAddr_BreakC_Curr          (FlashEndAddr_BreakB_Curr+C_OneFlashPage)        /*C�����Flash��ҳ��ַ*/
#define FlashEndAddr_BreakC_Curr         (FlashStAddr_BreakC_Curr+C_OneFlashPage)         /*C�����Flashβҳ��ַ*/

/*********************���ʷ���140���ֽڣ�ÿҳFlash 4092/140=29��698��147��4092/147=27��10�β�����żҳ�洢*********86********/
#define Power_Rev_Data_Len               140                                              /*���ʷ������ݳ���*/
#define FlashStAddr_PowerT_Rev           (FlashEndAddr_BreakC_Curr+C_OneFlashPage)        /*�ܹ��ʷ���Flash��ҳ��ַ*/
#define FlashEndAddr_PowerT_Rev          (FlashStAddr_PowerT_Rev+C_OneFlashPage)          /*�ܹ��ʷ���Flashβҳ��ַ*/
#define FlashStAddr_PowerA_Rev           (FlashEndAddr_PowerT_Rev+C_OneFlashPage)         /*A�๦�ʷ���Flash��ҳ��ַ*/
#define FlashEndAddr_PowerA_Rev          (FlashStAddr_PowerA_Rev+C_OneFlashPage)          /*A�๦�ʷ���Flashβҳ��ַ*/
#define FlashStAddr_PowerB_Rev           (FlashEndAddr_PowerA_Rev+C_OneFlashPage)         /*B�๦�ʷ���Flash��ҳ��ַ*/
#define FlashEndAddr_PowerB_Rev          (FlashStAddr_PowerB_Rev+C_OneFlashPage)          /*B�๦�ʷ���Flashβҳ��ַ*/
#define FlashStAddr_PowerC_Rev           (FlashEndAddr_PowerB_Rev+C_OneFlashPage)         /*C�๦�ʷ���Flash��ҳ��ַ*/
#define FlashEndAddr_PowerC_Rev          (FlashStAddr_PowerC_Rev+C_OneFlashPage)          /*C�๦�ʷ���Flashβҳ��ַ*/

/*********************���ع�140���ֽڣ�ÿҳFlash 4092/140=29��698��147��4092/147=27��10�β�����żҳ�洢**********92*******/
#define Over_Lo_Data_Len                 140                                              /*�������ݳ���*/
#define FlashStAddr_OverA_Lo             (FlashEndAddr_PowerC_Rev+C_OneFlashPage)         /*A�����Flash��ҳ��ַ*/
#define FlashEndAddr_OverA_Lo            (FlashStAddr_OverA_Lo+C_OneFlashPage)            /*A�����Flashβҳ��ַ*/
#define FlashStAddr_OverB_Lo             (FlashEndAddr_OverA_Lo+C_OneFlashPage)           /*B�����Flash��ҳ��ַ*/
#define FlashEndAddr_OverB_Lo            (FlashStAddr_OverB_Lo+C_OneFlashPage)            /*B�����Flashβҳ��ַ*/
#define FlashStAddr_OverC_Lo             (FlashEndAddr_OverB_Lo+C_OneFlashPage)           /*C�����Flash��ҳ��ַ*/
#define FlashEndAddr_OverC_Lo            (FlashStAddr_OverC_Lo+C_OneFlashPage)            /*C�����Flashβҳ��ַ*/

/*********************�������������޹�44���ֽڣ�ÿҳFlash 4092/44=93��10�β�����żҳ�洢*******102**********/
#define PFactor_Over_Data_Len            44                                               /*�ܹ����������������ݳ���*/
#define FlashStAddr_PFactorT_Over        (FlashEndAddr_OverC_Lo+C_OneFlashPage)           /*�ܹ�������������Flash��ҳ��ַ*/
#define FlashEndAddr_PFactorT_Over       (FlashStAddr_PFactorT_Over+C_OneFlashPage)       /*�ܹ�������������Flashβҳ��ַ*/
#define FlashStAddr_PFactorA_Over        (FlashEndAddr_PFactorT_Over+C_OneFlashPage)      /*A�๦������������Flash��ҳ��ַ*/
#define FlashEndAddr_PFactorA_Over       (FlashStAddr_PFactorA_Over+C_OneFlashPage)       /*A�๦������������Flashβҳ��ַ*/
#define FlashStAddr_PFactorB_Over        (FlashEndAddr_PFactorA_Over+C_OneFlashPage)      /*B�๦������������Flash��ҳ��ַ*/
#define FlashEndAddr_PFactorB_Over       (FlashStAddr_PFactorB_Over+C_OneFlashPage)       /*B�๦������������Flashβҳ��ַ*/
#define FlashStAddr_PFactorC_Over        (FlashEndAddr_PFactorB_Over+C_OneFlashPage)      /*C�๦������������Flash��ҳ��ַ*/
#define FlashEndAddr_PFactorC_Over       (FlashStAddr_PFactorC_Over+C_OneFlashPage)       /*C�๦������������Flashβҳ��ַ*/

/*********************��ѹ�ϸ��ʹ�108���ֽڣ�ÿҳFlash 4092/108=37��12�β�����żҳ�洢********104*********/
#define Vol_Per_Pass_Data_Len            108                                              /*��ѹ�ϸ������ݳ���*/
#define FlashStAddr_Vol_Per_Pass         (FlashEndAddr_PFactorC_Over+C_OneFlashPage)      /*��ѹ�ϸ���Flash��ҳ��ַ*/
#define FlashEndAddr_Vol_Per_Pass        (FlashStAddr_Vol_Per_Pass+C_OneFlashPage)        /*��ѹ�ϸ���Flashβҳ��ַ*/

/*********************���������¼��202���ֽڣ�ÿҳFlash 4092/202=20��10�β�����żҳ�洢********106*********/
#define De_Clear_Data_Len                202                                              /*���������¼���ݳ���*/
#define FlashStAddr_De_Clear             (FlashEndAddr_Vol_Per_Pass+C_OneFlashPage)       /*���������¼Flash��ҳ��ַ*/
#define FlashEndAddr_De_Clear            (FlashStAddr_De_Clear+C_OneFlashPage)            /*���������¼Flashβҳ��ַ*/

/*********************��բ��¼��34���ֽڣ�ÿҳFlash 4092/34=120��10�β�����żҳ�洢********108*********/
#define RelayClose_Data_Len              34                                               /*��բ��¼���ݳ���*/
#define FlashStAddr_RelayClose           (FlashEndAddr_De_Clear+C_OneFlashPage)           /*��բ��¼Flash��ҳ��ַ*/
#define FlashEndAddr_RelayClose          (FlashStAddr_RelayClose+C_OneFlashPage)          /*��բ��¼Flashβҳ��ַ*/

/*********************��̼�¼��50���ֽڣ�ÿҳFlash 4092/50=91��10�β�����żҳ�洢**********110*******/
#define Program_Data_Len                 50                                               /*��̼�¼���ݳ���*/
#define FlashStAddr_Program              (FlashEndAddr_RelayClose+C_OneFlashPage)         /*��̼�¼Flash��ҳ��ַ*/
#define FlashEndAddr_Program             (FlashStAddr_Program+C_OneFlashPage)             /*��̼�¼Flashβҳ��ַ*/

/*********************Уʱ��¼��16���ֽڣ�ÿҳFlash 4092/16=255��10�β�����żҳ�洢**********112*******/
#define AdjTime_Data_Len                 CLAdjTime_Note_1                                 /*Уʱ��¼���ݳ���*/
#define FlashStAddr_AdjTime              (FlashEndAddr_Program+C_OneFlashPage)            /*Уʱ��¼Flash��ҳ��ַ*/
#define FlashEndAddr_AdjTime             (FlashStAddr_AdjTime+C_OneFlashPage)             /*Уʱ��¼Flashβҳ��ַ*/

/*********************�㲥Уʱ��¼��16���ֽڣ�ÿҳFlash 4092/16=255��100�β��ö�ҳ�洢����ֹ����12�����**********112*******/
#define BroadcastTime_Data_Len           CLBroadcastTime_Note_1                            /*�㲥Уʱ��¼���ݳ���*/
#define FlashStAddr_BroadcastTime        (FlashEndAddr_AdjTime+C_OneFlashPage)             /*�㲥Уʱ��¼Flash��ҳ��ַ*/
#define FlashEndAddr_BroadcastTime       (FlashStAddr_BroadcastTime+C_OneFlashPage*2)      /*�㲥Уʱ��¼Flashβҳ��ַ*/

/*********************ʱ�α��̼�¼��65���ֽڣ�ÿҳFlash 4092/65=62��10�β��ö�ҳ,2ҳ�洢****116***************/
#define ProgPT_Data_Len                  CLProgPT_Note_1                                  /*ʱ�α��̼�¼���ݳ���*/
#define FlashStAddr_ProgPT               (FlashEndAddr_BroadcastTime+C_OneFlashPage)      /*ʱ�α��̼�¼Flash��ҳ��ַ*/
#define FlashEndAddr_ProgPT              (FlashStAddr_ProgPT+C_OneFlashPage)              /*ʱ�α��̼�¼Flashβҳ��ַ*/

/*********************ʱ�����̼�¼��94���ֽڣ�ÿҳFlash 4092/94=43��10�β�����żҳ�洢*******118**********/
#define ProgTZ_Data_Len                  CLProgTZ_Note_1                                  /*ʱ�����̼�¼���ݳ���*/
#define FlashStAddr_ProgTZ               (FlashEndAddr_ProgPT+C_OneFlashPage)             /*ʱ�����̼�¼Flash��ҳ��ַ*/
#define FlashEndAddr_ProgTZ              (FlashStAddr_ProgTZ+C_OneFlashPage)              /*ʱ�����̼�¼Flashβҳ��ַ*/

/*********************�����ձ�̼�¼��11���ֽڣ�ÿҳFlash 4092/11=372��10�β�����żҳ�洢*******120**********/
#define ProgWRe_Data_Len                 CLProgWRe_Note_1                                 /*�����ձ�̼�¼���ݳ���*/
#define FlashStAddr_ProgWRe              (FlashEndAddr_ProgTZ+C_OneFlashPage)             /*�����ձ�̼�¼Flash��ҳ��ַ*/
#define FlashEndAddr_ProgWRe             (FlashStAddr_ProgWRe+C_OneFlashPage)             /*�����ձ�̼�¼Flashβҳ��ַ*/

/*********************�ڼ��ձ�̼�¼��1026���ֽڣ�ÿҳFlash 4092/1026=3��10�β��ö�ҳ,6ҳ�洢*****126**********/
#define ProgHol_Data_Len                 CLProgHol_Note_1                                 /*�ڼ��ձ�̼�¼���ݳ���*/
#define FlashStAddr_ProgHol              (FlashEndAddr_ProgWRe+C_OneFlashPage)            /*�ڼ��ձ�̼�¼Flash��ҳ��ַ*/
#define FlashEndAddr_ProgHol             (FlashStAddr_ProgHol+C_OneFlashPage*5)           /*�ڼ��ձ�̼�¼Flashβҳ��ַ*/

/*********************��Ϸ�ʽ��̼�¼��11���ֽڣ�ÿҳFlash 4092/11=372��10�β�����żҳ�洢*******130**********/
#define ProgCom_Data_Len                 CLProgAcC_Note_1                                 /*��Ϸ�ʽ��̼�¼���ݳ���*/
#define FlashStAddr_ProgAcC              (FlashEndAddr_ProgHol+C_OneFlashPage)            /*�й���Ϸ�ʽ��̼�¼Flash��ҳ��ַ*/
#define FlashEndAddr_ProgAcC             (FlashStAddr_ProgAcC+C_OneFlashPage)             /*�й���Ϸ�ʽ��̼�¼Flashβҳ��ַ*/

#define FlashStAddr_ProgReC1             (FlashEndAddr_ProgAcC+C_OneFlashPage)            /*�޹���Ϸ�ʽ1��̼�¼Flash��ҳ��ַ*/
#define FlashEndAddr_ProgReC1            (FlashStAddr_ProgReC1+C_OneFlashPage)            /*�޹���Ϸ�ʽ1��̼�¼Flashβҳ��ַ*/

/*********************�����ձ�̼�¼��16���ֽڣ�ÿҳFlash 4092/16=255��10�β�����żҳ�洢********132*********/
#define ProgSettD_Data_Len               CLProgSettD_Note_1                               /*�����ձ�̼�¼���ݳ���*/
#define FlashStAddr_ProgSettD            (FlashEndAddr_ProgReC1+C_OneFlashPage)           /*�����ձ�̼�¼Flash��ҳ��ַ*/
#define FlashEndAddr_ProgSettD           (FlashStAddr_ProgSettD+C_OneFlashPage)           /*�����ձ�̼�¼Flashβҳ��ַ*/

/*********************���ʲ�����̼�¼��42���ֽڣ�ÿҳFlash 4092/42=97��10�β�����żҳ�洢*******134**********/
#define ProgTPara_Data_Len               CLProgTPara_Note_1                               /*���ʲ�����̼�¼���ݳ���*/
#define FlashStAddr_ProgTPara            (FlashEndAddr_ProgSettD+C_OneFlashPage)          /*���ʲ�����̼�¼Flash��ҳ��ַ*/
#define FlashEndAddr_ProgTPara           (FlashStAddr_ProgTPara+C_OneFlashPage)           /*���ʲ�����̼�¼Flashβҳ��ַ*/

/*********************���ݱ��̼�¼��138���ֽڣ�ÿҳFlash 4092/138=29��10�β�����żҳ�洢*******136**********/
#define ProgLad_Data_Len                 CLProgLad_Note_1                                 /*���ݱ��̼�¼���ݳ���*/
#define FlashStAddr_ProgLad              (FlashEndAddr_ProgTPara+C_OneFlashPage)          /*���ݱ��̼�¼Flash��ҳ��ַ*/
#define FlashEndAddr_ProgLad             (FlashStAddr_ProgLad+C_OneFlashPage)             /*���ݱ��̼�¼Flashβҳ��ַ*/

/*********************��Կ���¼�¼��15���ֽڣ�ÿҳFlash 4092/15=272��10�β�����żҳ�洢**********138*******/
#define ProgKD_Data_Len                  CLProgKD_Note_1                                  /*��Կ�������ݳ���*/
#define FlashStAddr_ProgKD               (FlashEndAddr_ProgLad+C_OneFlashPage)            /*��Կ���¼�¼Flash��ҳ��ַ*/
#define FlashEndAddr_ProgKD              (FlashStAddr_ProgKD+C_OneFlashPage)              /*��Կ���¼�¼Flashβҳ��ַ*/

/*********************�쳣�忨��¼��36���ֽڣ�ÿҳFlash 4092/36=113��10�β�����żҳ�洢**********140*******/
#define AbnorC_Data_Len                  36                                               /*�쳣�忨��¼���ݳ���*/
#define FlashStAddr_AbnorC               (FlashEndAddr_ProgKD+C_OneFlashPage)             /*�쳣�忨��¼Flash��ҳ��ַ*/
#define FlashEndAddr_AbnorC              (FlashStAddr_AbnorC+C_OneFlashPage)              /*�쳣�忨��¼Flashβҳ��ַ*/

/*********************����Ǽ�¼��60���ֽڣ�ÿҳFlash 4092/60=68��10�β�����żҳ�洢***********142******/
#define OpenW_Data_Len                   60                                               /*����Ǽ�¼���ݳ���*/
#define FlashStAddr_OpenW                (FlashEndAddr_AbnorC+C_OneFlashPage)             /*����Ǽ�¼Flash��ҳ��ַ*/
#define FlashEndAddr_OpenW               (FlashStAddr_OpenW+C_OneFlashPage)               /*����Ǽ�¼Flashβҳ��ַ*/

/*********************����ť�Ǽ�¼��60���ֽڣ�ÿҳFlash 4092/60=68��10�β�����żҳ�洢*********144********/
#define OpenCW_Data_Len                  60                                                 /*����ť�Ǽ�¼���ݳ���*/
#define FlashStAddr_OpenCW               (FlashEndAddr_OpenW+C_OneFlashPage)                /*����ť�Ǽ�¼Flash��ҳ��ַ*/
#define FlashEndAddr_OpenCW              (FlashStAddr_OpenCW+C_OneFlashPage)                /*����ť�Ǽ�¼Flashβҳ��ַ*/

/*********************�����¼��23���ֽڣ�ÿҳFlash 4092/23=177��10�β�����żҳ�洢************146*****/
#define BuyCurr_Data_Len                 23                                                 /*�����¼���ݳ���*/
#define FlashStAddr_BuyCurr              (FlashEndAddr_OpenCW+C_OneFlashPage)               /*�����¼Flash��ҳ��ַ*/
#define FlashEndAddr_BuyCurr             (FlashStAddr_BuyCurr+C_OneFlashPage)               /*�����¼Flashβҳ��ַ*/

/*********************�˷Ѽ�¼��19���ֽڣ�ÿҳFlash 4092/19=215��10�β�����żҳ�洢**********148*******/
#define Return_M_Data_Len                19                                                 /*�˷Ѽ�¼���ݳ���*/
#define FlashStAddr_Return_M             (FlashEndAddr_BuyCurr+C_OneFlashPage)              /*�˷Ѽ�¼Flash��ҳ��ַ*/
#define FlashEndAddr_Return_M            (FlashStAddr_Return_M+C_OneFlashPage)              /*�˷Ѽ�¼Flashβҳ��ַ*/

/*********************�㶨�ų����ż�¼��28���ֽڣ�ÿҳFlash 4092/28=146��10�β�����żҳ�洢*******150**********/
#define ConM_Data_Len                    28                                                 /*�㶨�ų����ż�¼���ݳ���*/
#define FlashStAddr_ConM                 (FlashEndAddr_Return_M+C_OneFlashPage)             /*�㶨�ų����ż�¼Flash��ҳ��ַ*/
#define FlashEndAddr_ConM                (FlashStAddr_ConM+C_OneFlashPage)                  /*�㶨�ų����ż�¼Flashβҳ��ַ*/

/*********************���ɿ���������¼��29���ֽڣ�ÿҳFlash 4092/29=141��10�β�����żҳ�洢******152***********/
#define RelayFa_Data_Len                 29                                                 /*���ɿ���������¼���ݳ���*/
#define FlashStAddr_RelayFa              (FlashEndAddr_ConM+C_OneFlashPage)                 /*���ɿ���������¼Flash��ҳ��ַ*/
#define FlashEndAddr_RelayFa             (FlashStAddr_RelayFa+C_OneFlashPage)                   /*���ɿ���������¼Flashβҳ��ַ*/

/*********************��Դ�쳣��¼��20���ֽڣ�ÿҳFlash 4092/20=204��10�β�����żҳ�洢*********154********/
#define PowerFa_Data_Len                 20                                                 /*��Դ�쳣��¼���ݳ���*/
#define FlashStAddr_PowerFa              (FlashEndAddr_RelayFa+C_OneFlashPage)              /*��Դ�쳣��¼Flash��ҳ��ַ*/
#define FlashEndAddr_PowerFa             (FlashStAddr_PowerFa+C_OneFlashPage)               /*��Դ�쳣��¼Flashβҳ��ַ*/

/*********************��բ��¼��34���ֽڣ�ÿҳFlash 4092/34=120��Ŀǰ698����բ��¼Ĭ������ͬ���Ǽ�¼��10�β�����żҳ�洢*******156**********/
#define RelayOpen_Data_Len               34                                                 /*��բ��¼���ݳ���*/
#define FlashStAddr_RelayOpen            (FlashEndAddr_PowerFa+C_OneFlashPage)              /*��բ��¼Flash��ҳ��ַ*/
#define FlashEndAddr_RelayOpen           (FlashStAddr_RelayOpen+C_OneFlashPage)             /*��բ��¼Flashβҳ��ַ*/

/*********************У���̹�1022���ֽڣ�ÿҳFlash 4092/1022=4��10�β��ö�ҳ�洢��5ҳ********161*********/
#define Rec_Meter_Data_Len               1022                                               /*У���̼�¼���ݳ���*/
#define FlashStAddr_Rec_Meter            (FlashEndAddr_RelayOpen+C_OneFlashPage)            /*У���̼�¼Flash��ҳ��ַ*/
#define FlashEndAddr_Rec_Meter           (FlashStAddr_Rec_Meter+C_OneFlashPage*4)           /*У���̼�¼Flashβҳ��ַ*/

/*********************�¼������¼��14���ֽڣ�ÿҳFlash 4092/14=292��10�β�����żҳ�洢*********163********/
#define Even_Clear_Data_Len              14                                                 /*�¼������¼���ݳ���*/
#define FlashStAddr_Even_Clear           (FlashEndAddr_Rec_Meter+C_OneFlashPage)            /*�¼������¼Flash��ҳ��ַ*/
#define FlashEndAddr_Even_Clear          (FlashStAddr_Even_Clear+C_OneFlashPage)            /*�¼������¼Flashβҳ��ַ*/

/**********************�����¼��106���ֽڣ�ÿҳFlash 4092/106=38��10�β�����żҳ�洢*********165******/
#define Tol_Clear_Data_Len               106                                                /*�����¼���ݳ���*/
#define FlashStAddr_Tol_Clear            (FlashEndAddr_Even_Clear+C_OneFlashPage)           /*�����¼Flash��ҳ��ַ*/
#define FlashEndAddr_Tol_Clear           (FlashStAddr_Tol_Clear+C_OneFlashPage)             /*�����¼Flashβҳ��ַ*/

/**********************����оƬ���ϼ�¼��106���ֽڣ�ÿҳFlash 4092/106=38��10�β�����żҳ�洢*********167******/
#define MeterFa_Data_Len                 106                                                /*����оƬ�������ݳ���*/
#define FlashStAddr_MeterFa              (FlashEndAddr_Tol_Clear+C_OneFlashPage)            /*����оƬ���ϼ�¼Flash��ҳ��ַ*/
#define FlashEndAddr_MeterFa             (FlashStAddr_MeterFa+C_OneFlashPage)               /*����оƬ���ϼ�¼Flashβҳ��ַ*/

/**********************ʱ�ӹ��ϼ�¼��106���ֽڣ�ÿҳFlash 4092/106=38��10�β�����żҳ�洢*********169******/
#define ClockFa_Data_Len                 106                                                /*ʱ�ӹ������ݳ���*/
#define FlashStAddr_ClockFa              (FlashEndAddr_MeterFa+C_OneFlashPage)              /*ʱ�ӹ��ϼ�¼Flash��ҳ��ַ*/
#define FlashEndAddr_ClockFa             (FlashStAddr_ClockFa+C_OneFlashPage)               /*ʱ�ӹ��ϼ�¼Flashβҳ��ַ*/

/**********************���ߵ����쳣��¼��106���ֽڣ�ÿҳFlash 4092/106=38��10�β�����żҳ�洢*********169******/
#define CNeutralCurrentAbnormal_Data_Len       106                                                    /*���ߵ����쳣���ݳ���*/
#define FlashStAddr_NeutralCurrentAbnormal     (FlashEndAddr_ClockFa+C_OneFlashPage)                  /*���ߵ����쳣��¼Flash��ҳ��ַ*/
#define FlashEndAddr_NeutralCurrentAbnormal    (FlashStAddr_NeutralCurrentAbnormal+C_OneFlashPage)    /*���ߵ����쳣��¼Flashβҳ��ַ*/

/*********************************�����࣬1.7�޸�Ϊ���Ƹ��ɼ�¼�洢��ʽ�������·�OAD�洢(�洢Ԥ���ռ�����������Ԥ��)**********************************/
/*********************��ʱ���ᣬ��Ӧ698 ���Ӷ��ᣬ��109���ֽڣ�ÿҳFlash 4092/109=37��96*365=35040�β��ö�ҳ�洢��947ҳ***ʵ����947*1.3+2=1234ҳ********/
#define T_Free_Data_Len                    269                                                     /*��ʱ�����¼���ݳ���*/
#define FlashStAddr_T_Free                 (FlashEndAddr_NeutralCurrentAbnormal+C_OneFlashPage)    /*��ʱ�����¼Flash��ҳ��ַ*/
#define FlashEndAddr_T_Free                (FlashStAddr_T_Free+C_OneFlashPage*1233)                /*��ʱ�����¼Flashβҳ��ַ*/
#define MinFreezeFlashTol                  1234
#define C_MinFreezeNeedNum                 96*365                                                  /*35040��,���Ӷ�����Ҫ��¼����*/

/*********************˲ʱ���Ṳ390���ֽڣ�698��¼Ĭ�ϱ��ͬԭ645�����ÿҳFlash 4092/390=10��3��Ϊ����Ѳ������12��ͳһ�����ö�ҳ�洢��3ҳ*********702********/
#define I_Free_Data_Len                    269                                                /*˲ʱ�����¼���ݳ���*/
#define FlashStAddr_I_Free                 (FlashEndAddr_T_Free+C_OneFlashPage)               /*˲ʱ�����¼Flash��ҳ��ַ*/
#define FlashEndAddr_I_Free                (FlashStAddr_I_Free+C_OneFlashPage*2)              /*˲ʱ�����¼Flashβҳ��ַ*/

/*********************���㶳�� ��Ӧ698Сʱ���ᣬ��13���ֽڣ�698��¼17��ÿҳFlash 4092/13=314��254��Ϊ����Ѳ������12��ͳһ�����ö�ҳ�洢��6ҳ***708********/
#define H_Free_Data_Len                    13                                                 /*˲ʱ�����¼���ݳ���*/
#define FlashStAddr_H_Free                 (FlashEndAddr_I_Free+C_OneFlashPage)               /*˲ʱ�����¼Flash��ҳ��ַ*/
#define FlashEndAddr_H_Free                (FlashStAddr_H_Free+C_OneFlashPage*5)              /*˲ʱ�����¼Flashβҳ��ַ*/

/*********************�ն��Ṳ873���ֽڣ�ÿҳFlash 4092/873=4��365�β��ö�ҳ�洢��365*1.3/4=119+2ҳ*****728*****/
#define D_Free_Data_Len                    377                                                /*�ն����¼���ݳ���*/
#define FlashStAddr_D_Free                 (FlashEndAddr_H_Free+C_OneFlashPage)               /*�ն����¼Flash��ҳ��ַ*/
#define FlashEndAddr_D_Free                (FlashStAddr_D_Free+C_OneFlashPage*120)            /*�ն����¼Flashβҳ��ַ*/

/*********************�¶��Ṳ914���ֽڣ�ÿҳFlash 4092/914=4��24�β��ö�ҳ�洢��24*1.3/4=8+2ҳ***************6*****734*****/
#define D_Free_Data_Len                    377                                                /*�¶����¼���ݳ���*/
#define FlashStAddr_M_Free                 (FlashEndAddr_D_Free+C_OneFlashPage)               /*�¶����¼Flash��ҳ��ַ*/
#define FlashEndAddr_M_Free                (FlashStAddr_M_Free+C_OneFlashPage*9)              /*�¶����¼Flashβҳ��ַ*/

/*********************2��ʱ�����л�Լ����269���ֽڣ�ÿҳFlash 4092/269=15��2�β�����żҳ�洢******4***738********/
#define TZ_Free_Data_Len                   269                                                /*2��ʱ�����л�Լ�������¼���ݳ���*/
#define FlashStAddr_TZ_Free                (FlashEndAddr_M_Free+C_OneFlashPage)               /*2��ʱ�����л�Լ�������¼Flash��ҳ��ַ*/
#define FlashEndAddr_TZ_Free               (FlashStAddr_TZ_Free+C_OneFlashPage*3)             /*2��ʱ�����л�Լ�������¼Flashβҳ��ַ*/

/*********************2����ʱ�α��л�Լ�����Ṳ269���ֽڣ�ÿҳFlash 4092/269=15��2�β�����żҳ�洢*******4**742********/
#define PT_Free_Data_Len                   269                                                /*2����ʱ�α��л�Լ�������¼���ݳ���*/
#define FlashStAddr_PT_Free                (FlashEndAddr_TZ_Free+C_OneFlashPage)              /*2����ʱ�α��л�Լ�������¼Flash��ҳ��ַ*/
#define FlashEndAddr_PT_Free               (FlashStAddr_PT_Free+C_OneFlashPage*3)             /*2����ʱ�α��л�Լ�������¼Flashβҳ��ַ*/

/*********************2�׷��ʵ���л�Լ�����Ṳ269���ֽڣ�ÿҳFlash 4092/269=15��2�β�����żҳ�洢******4***746********/
#define R_Free_Data_Len                    269                                                /*2�׷��ʵ���л�Լ�������¼���ݳ���*/
#define FlashStAddr_R_Free                 (FlashEndAddr_PT_Free+C_OneFlashPage)              /*2�׷��ʵ���л�Լ�������¼Flash��ҳ��ַ*/
#define FlashEndAddr_R_Free                (FlashStAddr_R_Free+C_OneFlashPage*3)              /*2�׷��ʵ���л�Լ�������¼Flashβҳ��ַ*/

/**********************2�׽����л�Լ�����Ṳ269���ֽڣ�ÿҳFlash 4092/269=15��2�β�����żҳ�洢*******4**750********/
#define L_Free_Data_Len                    269                                                /*2�׽����л�Լ�������¼���ݳ���*/
#define FlashStAddr_L_Free                 (FlashEndAddr_R_Free+C_OneFlashPage)               /*2�׽����л�Լ�������¼Flash��ҳ��ַ*/
#define FlashEndAddr_L_Free                (FlashStAddr_L_Free+C_OneFlashPage*3)              /*2�׽����л�Լ�������¼Flashβҳ��ַ*/

/**********************����㶳��698*******10**760*****�����Ϊ���ݽ��㶳��***/
#define FlashStAddr_Y_Free                 (FlashEndAddr_L_Free+C_OneFlashPage)               /*����㶳���¼Flash��ҳ��ַ*/
#define FlashEndAddr_Y_Free                (FlashStAddr_Y_Free+C_OneFlashPage*9)              /*����㶳���¼Flashβҳ��ַ*/

//*********************ɽ��˫Э������,����645Э����ʱ�α�ʱ�����̼�¼**********************************************/
/*********************ʱ�α��̼�¼��682���ֽڣ�ÿҳFlash 4092/682=6��10�β��ö�ҳ�洢,4ҳ*******************/
#define ProgPT_Data_CurrentPart_Len        CLProgPT_CurrentPart_Note_1                        /*ʱ�α��̼�¼���ݳ���*/
#define FlashStAddr_CurrentPart_ProgPT     FlashEndAddr_Y_Free+C_OneFlashPage                 /*ʱ�α��̼�¼Flash��ҳ��ַ*/
#define FlashEndAddr_CurrentPart_ProgPT    FlashStAddr_CurrentPart_ProgPT+C_OneFlashPage*3    /*ʱ�α��̼�¼Flashβҳ��ַ*/

/*********************ʱ�����̼�¼��42���ֽڣ�ÿҳFlash 4092/48=85��10�β�����żҳ�洢*******118**********/
#define ProgTZ_Data_CurrentPart_Len        CLProgTZ_CurrentPart_Note_1                        /*ʱ�����̼�¼���ݳ���*/
#define FlashStAddr_CurrentPart_ProgTZ     FlashEndAddr_CurrentPart_ProgPT+C_OneFlashPage     /*ʱ�����̼�¼Flash��ҳ��ַ*/
#define FlashEndAddr_CurrentPart_ProgTZ    FlashStAddr_CurrentPart_ProgTZ+C_OneFlashPage      /*ʱ�����̼�¼Flashβҳ��ַ*/

/*********************645��̼�¼��50���ֽڣ�ÿҳFlash 4092/50=91��10�β�����żҳ�洢**********110*******/
#define Program_Data_Len_645               CLProgram_Note_1_645                               /*��̼�¼���ݳ���*/
#define FlashStAddr_Program_645            FlashEndAddr_CurrentPart_ProgTZ+C_OneFlashPage     /*��̼�¼Flash��ҳ��ַ*/
#define FlashEndAddr_Program_645           FlashStAddr_Program_645+C_OneFlashPage             /*��̼�¼Flashβҳ��ַ*/

/***********************�ڲ���������*****************************/
#define C_CurrEnergy_Len           ((E2Addr_CurrEnergyRam_End-E2Addr_CurrEnergy_St)/(C_CRCLen2+C_CurrDataLen5))     /*��ǰ���������ݣ�����*/
#define C_CurrEnergy_ByteLen       (C_CRCLen2+C_CurrDataLen5)
#define C_ChargeBal_offset_InGV    ((E2Addr_ChargeBal_Hex_Deal-E2Addr_CurrEnergy_St)/(C_CRCLen2+C_CurrDataLen5))    /*ʣ������RAM��λ��*/

#define C_698Free_Num                 11     /*Ŀǰ698���ᣬ���*/
#define C_698FreeData_SequenceLen4    4      /*����������ų���*/
#define C_698FreeData_DateLen6        7      /*�����������ڳ���YMDhms*/

#define C_698Event_OADTabMaxNum       60     /*�¼�698������ű����֧�ָ���*/
#define C_698Event_OADTabDataType     2      /*�¼�698������ű����ݸ�ʽ��2���ֽڱ�ʾ1������OAD*/

#define C_698Event_OADTabLen          (C_698Event_OADTabMaxNum*C_698Event_OADTabDataType)    /*�¼�698������ű�*/
#define C_698Event_FixOADTabLen       10     /*�¼�698�̶�������ű����֧��10��*/

/*���ݲ���Ҫ���ݣ���RAM���Ե�ַ������ռ������stm32l151xD.icf�ļ��ж��壬ע���ڹ��������У�option-linker-config��ѡ�����ĺ�.icf�ļ�*/
uchar8 GV_CurrEnergyData[C_CurrEnergy_Len][C_CRCLen2+C_CurrDataLen5];    /*RAM ��CRC ��ǰ����������,��E2�洢��Ӧ*/
uchar8 GV_CurrMVolPerPass[4][C_CRCLen2+CLVol_Per_Pass_M];                /*RAM ��CRC ��ǰ��ѹ�ϸ��ʣ��ܡ�ABC*/
uchar8 GV_Voltage_PassTime[C_CRCLen2+CLVol_PassTime_M];                /*RAM ��CRC ��ǰ��ѹ�ϸ��ʵ�ѹ�ϸ�ʱ��*/

/************�α���*************/
uchar8 GV_Date_Time[CLDate_Week_Time];                                       /*ssmmhhwwDDMMYY*/
uchar8 GV_BroadcastTimeOffset_Min[CLBroadcastTimeOffset_Min+C_CRCLen2];      /*�㲥Уʱƫ����Сֵ*/
uchar8 GV_BroadcastTimeOffset_Max[CLBroadcastTimeOffset_Max+C_CRCLen2];      /*�㲥Уʱƫ�����ֵ*/

uchar8 GV_Demand_Cycle[CLDemand_Cycle+C_CRCLen2];                            /*����������ڴ�2 CRC*/
uchar8 GV_Sliding_Time[CLSliding_Time+C_CRCLen2];                            /*����ʱ���2 CRC*/

uchar8 GV_Change_TZ_Time[CLChange_TZ_Time+C_CRCLen2];                        /*����ʱ�����л�ʱ���2 CRC*/
uchar8 GV_Change_PT_Time[CLChange_PT_Time+C_CRCLen2];                        /*������ʱ�α��л�ʱ���2 CRC*/
uchar8 GV_Change_Rate[CLChange_Rate+C_CRCLen2];                              /*���׷��ʵ���л�ʱ���2 CRC*/
uchar8 GV_Change_Ladder[CLChange_Ladder+C_CRCLen2];                          /*���׽��ݵ���л�ʱ���2 CRC*/

uchar8 GV_Year_Zone_Num[CLYear_Zone_Num+C_CRCLen2];                          /*��ʱ���� ��2 CRC*/
uchar8 GV_Day_Table_Num[CLDay_Table_Num+C_CRCLen2];                          /*��ʱ�α��� ��2 CRC*/
uchar8 GV_Day_Time_Num[CLDay_Time_Num+C_CRCLen2];                            /*��ʱ���� ��2 CRC*/
uchar8 GV_Rate_Num[CLRate_Num+C_CRCLen2];                                    /*������ ��2 CRC*/
uchar8 GV_Holiday_Num[CLHoliday_Num+C_CRCLen2];                              /*���������� ��2 CRC*/

uchar8 GV_Step_Num[CLStep_Num+C_CRCLen2];                                    /*������ ��2 CRC*/
#if 0
uchar8 GV_Key_Tol_Num[CLKey_Tol_Num+C_CRCLen2];                              /*��Կ������ ��2 CRC*/
#endif

uchar8 GV_Per_Dis_Screen_Time[CLPer_Dis_Screen_Time+C_CRCLen2];              /*ѭ��ÿ����ʾʱ��*/
uchar8 GV_Auto_Dis_Screen_Num[CLAuto_Dis_Screen_Num+C_CRCLen2];              /*ѭ������*/
uchar8 GV_Auto_Dis_Screen_MaxNum[C_CRCLen2+CLAuto_Dis_Screen_MaxNum];        /*ѭ�������ʾ����*/

uchar8 GV_Perkey_Dis_Screen_Time[C_CRCLen2+CLPerkey_Dis_Screen_Time];        /*����ÿ����ʾʱ��*/
uchar8 GV_Key_CycDis_Screen_Num[CLKey_CycDis_Screen_Num+C_CRCLen2];          /*��������*/
uchar8 GV_Key_CycDis_Screen_MaxNum[C_CRCLen2+CLKey_CycDis_Screen_MaxNum];    /*���������ʾ����*/

uchar8 GV_PowerOn_Dis_All_Time[CLPowerOn_Dis_All_Time+C_CRCLen2];    /*�ϵ�ȫ��ʱ�� ��2 CRC*/
uchar8 GV_BacklightTime[CLBacklightTime+C_CRCLen2];                  /*�������ʱ�� ��2 CRC*/
uchar8 GV_SViewBacklightTime[CLSViewBacklightTime+C_CRCLen2];        /*��ʾ�鿴�������ʱ�� ��2 CRC*/
uchar8 GV_NEScreenDisplay[CLNEScreenDisplay+C_CRCLen2];              /*�޵簴����Ļפ�����ʱ�� ��2 CRC*/
uchar8 GV_Energy_Decimal_Num[CLEnergy_Decimal_Num+C_CRCLen2];        /*����С��λ�� ��2 CRC*/
uchar8 GV_Power_Decimal_Num[CLPower_Decimal_Num+C_CRCLen2];          /*��ʾ���ʣ����������С��λ�� ��2 CRC*/
uchar8 GV_1And2Display[CL1And2Display+C_CRCLen2];                    /*Һ���٢���������,��2 CRC*/

uchar8 GV_Ratio_Curr_Tran[CLRatio_Curr_Tran+C_CRCLen2];              /*������������� ��2 CRC*/
uchar8 GV_Ratio_Vol_Tran[CLRatio_Vol_Tran+C_CRCLen2];                /*��ѹ��������� ��2 CRC*/

uchar8 GV_Meter_Work_State[7][CLMeter_Work_State1];                  /*�������״̬��1-7*/
uchar8 GV_Key_State[CLKey_State+C_CRCLen2];                          /*�������״̬��8����Կ״̬ ��2 CRC*/
uchar8 GV_Active_Com_State[3][CLReactive_Com_State2+C_CRCLen2];      /*���״̬��,��2 CRC*/

uchar8 GV_Mod_InFr_Baud[CLMod_InFr_Baud+C_CRCLen2];                  /*����ʽ����,��2 CRC*/
uchar8 GV_One485_Baud[CLOne485_Baud+C_CRCLen2];                      /*��1·485,��2 CRC*/
uchar8 GV_Two485_Baud[CLTwo485_Baud+C_CRCLen2];                      /*��2·485,��2 CRC*/
uchar8 GV_Modular_Baud[CLModular_Baud+C_CRCLen2];                    /*ģ��ͨ��,��2 CRC*/

uchar8 GV_Week_RestDay[2][CLWeek_RestDay+C_CRCLen2];                 /*������������,��2 CRC*/

uchar8 GV_Alam1_Money[5][CLClose_Relay_Money+C_CRCLen2];             /*�����������ֵ,��2 CRC*/

uchar8 GV_Meter_Work_Char1[CLMeter_Work_Char1+C_CRCLen2];            /*�������������1,��2 CRC*/

uchar8 GV_Comm_Address[CLComm_Address+C_CRCLen2];                    /*ͨ�ŵ�ַCRC,��2 CRC*/

uchar8 GV_GPS_Signal[CLGPS_Signal];                                        /*����ͨѶ���߼��ź�ǿ��ָʾ*/
//uchar8 GV_Relay_Delay_Time[CLRelay_Delay_Time+C_CRCLen2];                /*��բ��ʱʱ��,��2 CRC*/
uchar8 GV_Relay_Open_CurrTreshold[CLRelay_Open_CurrTreshold+C_CRCLen2];    /*�̵�����բ���Ƶ�������ֵ,��2 CRC*/
uchar8 GV_Inset_Card_State[CLInset_Card_State];                            /*�忨״̬��*/

uchar8 GV_Current_Rate_Price[C_MaxRatesNum][CLCurrent_Rate12_Price+C_CRCLen2];    /*��ǰ����1-12���,��2 CRC*/
uchar8 GV_BackUp_Rate_Price[C_MaxRatesNum][CLBackUp_Rate12_Price+C_CRCLen2];      /*�����׷���1-12���,��2 CRC*/
uchar8 GV_Current_Ladder_Table[CLCurrent_Ladder_Table+C_CRCLen2];                 /*��ǰ�׽��ݱ�,��2 CRC*/
uchar8 GV_BackUp_Ladder_Table[CLBackUp_Ladder_Table+C_CRCLen2];                   /*�����׽��ݱ�,��2 CRC*/

uchar8 GV_LossVolage_Vol_UpLim[CLLossVolage_Vol_UpLim+C_CRCLen2];          /*ʧѹ�¼���ѹ��������,��2 CRC*/
uchar8 GV_LossVolage_Vol_LowLim[CLLossVolage_Vol_LowLim+C_CRCLen2];        /*ʧѹ�¼���ѹ�ָ�����,��2 CRC*/
uchar8 GV_LossVolage_Curr_LowLim[CLLossVolage_Curr_LowLim+C_CRCLen2];      /*ʧѹ�¼�������������,��2 CRC*/
uchar8 GV_LossVolage_Delay_T[CLLossVolage_Delay_T+C_CRCLen2];              /*ʧѹ�¼��ж���ʱʱ��,��2 CRC*/

uchar8 GV_LowVolage_Vol_UpLim[CLLowVolage_Vol_UpLim+C_CRCLen2];            /*Ƿѹ�¼���ѹ��������,��2 CRC*/
uchar8 GV_LowVolage_Delay_T[CLLowVolage_Delay_T+C_CRCLen2];                /*Ƿѹ�¼��ж���ʱʱ��,��2 CRC*/

uchar8 GV_OverVolage_Vol_LowLim[CLOverVolage_Vol_LowLim+C_CRCLen2];        /*��ѹ�¼���ѹ��������,��2 CRC*/
uchar8 GV_OverVolage_Delay_T[CLOverVolage_Delay_T+C_CRCLen2];              /*��ѹʱ���ж���ʱʱ��,��2 CRC*/

uchar8 GV_BreakVol_Vol_UpLim[CLBreakVol_Vol_UpLim+C_CRCLen2];              /*�����¼���ѹ��������,��2 CRC*/
uchar8 GV_BreakVol_Curr_UpLim[CLBreakVol_Curr_UpLim+C_CRCLen2];            /*�����¼�������������,��2 CRC*/
uchar8 GV_BreakVol_Delay_T[CLBreakVol_Delay_T+C_CRCLen2];                  /*�����¼��ж���ʱʱ��,��2 CRC*/

uchar8 GV_NoBal_Vol_Lim[CLNoBal_Vol_Lim+C_CRCLen2];                        /*��ѹ��ƽ������ֵ,��2 CRC*/
uchar8 GV_NoBal_Vol_Delay_T[CLNoBal_Vol_Delay_T+C_CRCLen2];                /*��ѹ��ƽ�����ж���ʱʱ��,��2 CRC*/

uchar8 GV_NoBal_Curr_Lim[CLNoBal_Curr_Lim+C_CRCLen2];                      /*������ƽ������ֵ,��2 CRC*/
uchar8 GV_NoBal_Curr_Delay_T[CLNoBal_Curr_Delay_T+C_CRCLen2];              /*������ƽ�����ж���ʱʱ��,��2 CRC*/

uchar8 GV_SeriNoBal_Curr_Lim[CLSeriNoBal_Curr_Lim+C_CRCLen2];              /*�������ز�ƽ������ֵ,��2 CRC*/
uchar8 GV_SeriNoBal_Curr_Delay_T[CLSeriNoBal_Curr_Delay_T+C_CRCLen2];      /*�������ز�ƽ�����ж���ʱʱ��,��2 CRC*/

uchar8 GV_LossCurr_Vol_LowLim[CLLossCurr_Vol_LowLim+C_CRCLen2];            /*ʧ���¼���ѹ��������,��2 CRC*/
uchar8 GV_LossCurr_Curr_UpLim[CLLossCurr_Curr_UpLim+C_CRCLen2];            /*ʧ���¼�������������,��2 CRC*/
uchar8 GV_LossCurr_Curr_LowLim[CLLossCurr_Curr_LowLim+C_CRCLen2];          /*ʧ���¼�������������,��2 CRC*/
uchar8 GV_LossCurr_Delay_T[CLLossCurr_Delay_T+C_CRCLen2];                  /*ʧ���¼��ж���ʱʱ��,��2 CRC*/

uchar8 GV_OverCurr_Curr_LowLim[CLOverCurr_Curr_LowLim+C_CRCLen2];          /*�����¼������������� ,��2 CRC*/
uchar8 GV_OverCurr_Delay_T[CLOverCurr_Delay_T+C_CRCLen2];                  /*�����¼��ж���ʱʱ�� ,��2 CRC*/

uchar8 GV_BreakCurr_Vol_LowLim[CLBreakCurr_Vol_LowLim+C_CRCLen2];          /*�����¼���ѹ�������� ,��2 CRC*/
uchar8 GV_BreakCurr_Curr_UpLim[CLBreakCurr_Curr_UpLim+C_CRCLen2];          /*�����¼������������� ,��2 CRC*/
uchar8 GV_BreakCurr_Delay_T[CLBreakCurr_Delay_T+C_CRCLen2];                /*�����¼��ж���ʱʱ�� ,��2 CRC*/

uchar8 GV_OverLoad_AcPower_LowLim[CLOverLoad_AcPower_LowLim+C_CRCLen2];    /*�����¼��й����ʴ������� ,��2 CRC*/
uchar8 GV_OverLoad_Delay_T[CLOverLoad_Delay_T+C_CRCLen2];                  /*�����¼��ж���ʱʱ��,��2 CRC*/

uchar8 GV_PosAcDemandOv_De_LowLim[CLPosAcDemandOv_De_LowLim+C_CRCLen2];    /*�����й����������¼�������������,��2 CRC*/
uchar8 GV_PosAcDemandOv_Delay_T[CLPosAcDemandOv_Delay_T+C_CRCLen2];        /*�����й����������¼��ж���ʱʱ��,��2 CRC*/

uchar8 GV_RevAcDemandOv_De_LowLim[CLRevAcDemandOv_De_LowLim+C_CRCLen2];    /*�����й����������¼�������������,��2 CRC*/
uchar8 GV_RevAcDemandOv_Delay_T[CLRevAcDemandOv_Delay_T+C_CRCLen2];        /*���������������¼��ж���ʱʱ��,��2 CRC*/

uchar8 GV_ReDemandOv_De_LowLim[CLReDemandOv_De_LowLim+C_CRCLen2];          /*�޹����������¼�������������,��2 CRC*/
uchar8 GV_ReDemandOv_Delay_T[CLReDemandOv_Delay_T+C_CRCLen2];              /*�޹����������¼��ж���ʱʱ��,��2 CRC*/

uchar8 GV_PowerFactor_LowLim[CLPowerFactor_LowLim+C_CRCLen2];              /*�������������޷�ֵ,��2 CRC*/
uchar8 GV_PowerFactor_Delay_T[CLPowerFactor_Delay_T+C_CRCLen2];            /*�������س������ж���ʱʱ��,��2 CRC*/

uchar8 GV_PowerRev_AcPower_LowLim[CLPowerRev_AcPower_LowLim+C_CRCLen2];    /*���ʷ����¼��й����ʴ�������,��2 CRC*/
uchar8 GV_PowerRev_Delay_T[CLPowerRev_Delay_T+C_CRCLen2];                  /*���ʷ����¼��ж���ʱʱ��,��2 CRC*/

uchar8 GV_NeutralUnbalanceRate[CLNeutralUnbalanceRate+C_CRCLen2];                  /*���ߵ����쳣��ƽ������ֵ*/
uchar8 GV_NeutralAbnormal_Curr_LowLim[CLNeutralAbnormal_Curr_LowLim+C_CRCLen2];    /*���ߵ����쳣������������*/
uchar8 GV_NeutralAbnormal_Delay_T[CLNeutralAbnormal_Delay_T+C_CRCLen2];            /*���ߵ����쳣�ж��ӳ�ʱ��*/

uchar8 GV_ReversedVoltage_Delay_T[CLReversedVoltage_Delay_T+C_CRCLen2];            /*��ѹ�������¼��ж���ʱʱ��*/
uchar8 GV_ReversedCurrent_Delay_T[CLReversedCurrent_Delay_T+C_CRCLen2];            /*�����������¼��ж���ʱʱ��*/
uchar8 GV_PowerOff_Delay_T[CLPowerOff_Delay_T+C_CRCLen2];                          /*�����¼��ж���ʱʱ��*/
uchar8 GV_Aux_Pow_Down_Delay_T[CLAux_Pow_Down_Delay_T+C_CRCLen2];                  /*������Դ�����ж���ʱʱ��*/
uchar8 GV_ClockFa_Delay_T[CLClockFa_Delay_T+C_CRCLen2];                            /*ʱ�ӹ����ж���ʱʱ��*/
uchar8 GV_MeterFa_Delay_T[CLMeterFa_Delay_T+C_CRCLen2];                            /*����оƬ�����ж���ʱʱ��*/

uchar8 GV_Voltage_UpLim[CLVoltage_UpLim+C_CRCLen2];                  /*��ѹ����ֵ,��2 CRC*/
uchar8 GV_Voltage_LowLim[CLVoltage_LowLim+C_CRCLen2];                /*��ѹ����ֵ,��2 CRC*/
uchar8 GV_Volage_Check_UpLim[2][CLVolage_Check_LowLim+C_CRCLen2];    /*��ѹ����,��2 CRC*/

uchar8 GV_Volage_Type[8][CLVolage_Type+C_CRCLen2];                   /*��ѹ���͵����ò���,��2 CRC*/
uchar8 GV_Start_Up_Current[CLStart_Up_Current+C_CRCLen2];            /*����˲ʱ����ֵ,��2 CRC*/
uchar8 GV_Start_Up_Power[CLStart_Up_Power+C_CRCLen2];                /*����˲ʱ����ֵ,��2 CRC*/
uchar8 GV_Volage_Abnor_Vol[CLVolage_Abnor_Vol+C_CRCLen2];            /*��ѹ�쳣�жϵ�ѹ,��2 CRC*/
uchar8 GV_Loss_Volage_Curr[5][CLLoss_Volage_Curr+C_CRCLen2];         /*ȫʧѹ��������ز���,��2 CRC*/
uchar8 GV_Pluse_Most__Lim[CLPluse_Most__Lim+C_CRCLen2];              /*�Ӽ���оƬ�������������ֵ,��2 CRC*/
uchar8 GV_Curr_Ratio_30A[CLCurr_Ratio_30A+C_CRCLen2];                /*У��30A��Ӧ����Ӧ�������ϵ��,��2 CRC*/
uchar8 GV_Pulse_Constant[CLPulse_Constant+C_CRCLen2];                /*���峣��,��2 CRC*/
uchar8 GV_SoftIJ_Valid_Time[CLSoftIJ_Valid_Time+C_CRCLen2];          /*��IJ��Чʱ��,��2 CRC*/
uchar8 GV_Extern_Relay_PulW[CLExtern_Relay_PulW+C_CRCLen2];          /*���ü̵���������,��2 CRC*/
uchar8 GV_MeterRunStatic[CLMeterRunStatic+C_CRCLen2];                /*��ǰ�����ڵڼ���ʱ����ʱ�α�ʱ������ǰ���͵�ַ��,��2 CRC*/
uchar8 GV_HardError_State[CLHardError_State];                        /*Ӳ����������״̬��*/
uchar8 GV_Alarm_Status[CLAlarm_Status+C_CRCLen2];                    /*����ģʽ��,��2 CRC*/
uchar8 GV_RTC_AdjustTemp[CLRTC_AdjustTemp+C_CRCLen2];                /*RTCУ׼�¶�ֵ8+2*/
uchar8 GV_Cap_Vol[CLCap_Vol+C_CRCLen2];                              /*�������ݵ�ѹ,��2 CRC*/

uchar8 GV_PhaseA_Volage[3][CLPhaseC_Volage];                         /*��ѹ����*/
uchar8 GV_PhaseA_Curr[3][CLPhaseC_Curr];                             /*��������*/
uchar8 GV_Instant_TolAcPow[4][CLInstantC_AcPow];                     /*˲ʱ�й���������*/
uchar8 GV_Instant_TolRePow[4][CLInstantC_RePow];                     /*˲ʱ�޹���������*/
uchar8 GV_Instant_TolAppaPow[4][CLInstantC_AppaPow];                 /*˲ʱ���ڹ�������*/
uchar8 GV_Tol_PowerFactor[4][CLPhaseC_PowerFactor];                  /*������������*/
uchar8 GV_PhaseA_Angle[3][CLPhaseC_Angle];                           /*�������*/
uchar8 GV_Vector_Current[CLVector_Current];                          /*�������ʸ����*/
uchar8 GV_Zero_Current[CLZero_Current];                              /*���ߵ���*/
uchar8 GV_ElecNet_Freq[CLElecNet_Freq];                              /*����Ƶ��*/
uchar8 GV_OneMin_AcPower[4][CLOneMin_AcPower];                       /*1�����й�ƽ�����ʣ���ABC*/
uchar8 GV_OneMin_RePower[4][CLOneMin_RePower];                       /*1�����޹�ƽ�����ʣ���ABC*/
uchar8 GV_Curr_AcDemand[CLCurr_AcDemand];                            /*��ǰ�й�����*/
uchar8 GV_Curr_ReDemand[CLCurr_ReDemand];                            /*��ǰ�޹�����*/
//uchar8 GV_Curr_AppaDemand[CLCurr_AppaDemand];                      /*��ǰ��������*/
uchar8 GV_Meter_Temp[CLMeter_Temp];                                  /*�����¶�*/
uchar8 GV_Cloc_Batt_Vol[CLCloc_Batt_Vol];                            /*ʱ�ӵ�ص�ѹ*/
uchar8 GV_ReadMeter_Batt_Vol[CLReadMeter_Batt_Vol];                  /*�����ص�ѹ*/
uchar8 GV_Batt_Work_Time[CLBatt_Work_Time+C_CRCLen2];                /*�ڲ���ع���ʱ��  ,��2 CRC*/
uchar8 GV_Curr_Ladder_Price[CLCurr_Ladder_Price];                    /*��ǰ���ݵ��*/
uchar8 GV_Curr_Price[CLCurr_Price];                                  /*��ǰ���*/
uchar8 GV_Curr_Rate_Price[CLCurr_Rate_Price+C_CRCLen2];              /*��ǰ���ʵ��,��2 CRC*/
uchar8 GV_ID_Auth_Remain_Time[CLID_Auth_Remain_Time];                /*�����֤ʱЧʣ��ʱ��*/
uchar8 GV_ID_Auth_T_Remain_Time[CLInfra_Auth_Remain_Time];           /*�ն������֤ʱЧʣ��ʱ��*/
uchar8 GV_ID_Auth_Remain_Time_645[CLID_Auth_Remain_Time_645];        /*645�����֤ʱЧʣ��ʱ��(698����645)*/
uchar8 GV_Infra_Auth_Remain_Time[CLInfra_Auth_Remain_Time];          /*������֤ʱЧʣ��ʱ��*/
uchar8 GV_Infra_Auth_Remain_Time_645[CLInfra_Auth_Remain_Time_645];  /*645������֤ʱЧʣ��ʱ��(698����645)*/

uchar8 GV_SoftI_J_RemainTime[CLSoftI_J_RemainTime];                  /*��IJ��Чʣ��ʱ��*/
uchar8 GV_CurrMon_Vol_Pass_Time[CLCurrMon_Vol_Pass_Time];            /*�����ܵ�ѹ�ϸ�ʱ��*/
uchar8 GV_Curr_Rate_No[CLCurr_Rate_No];                              /*��ǰ���ʺ�*/
uchar8 GV_Curr_Step_No[CLCurr_Step_No];                              /*��ǰ���ݺ�*/
uchar8 GV_CurrA_Phase[3][CLCurrC_Phase];                             /*�������*/
uchar8 GV_VolA_Phase[3][CLVolC_Phase];                               /*��ѹ���*/
uchar8 GV_PhaseA_Curr_4Dig[3][CLPhaseC_Curr_4Dig];                   /*����,4λС��*/
uchar8 GV_Rst_ReportState_Timer[CLRst_ReportState_Timer+C_CRCLen2];  /*�����ϱ��Զ���λʱ�� ��2 CRC*/
uchar8 GV_Relay_Open_CurrTimer[CLRelay_Open_CurrTimer+C_CRCLen2];    /*��բ���Ƶ������ޱ�����ʱʱ��  ��2 CRC*/
uchar8 GV__IRAuth_Timer[CL_IRAuth_Timer+C_CRCLen2];                  /*������֤ʱЧ  ��2 CRC*/
uchar8 GV_Relay_RemoteOrder[CLRelay_RemoteOrder+C_CRCLen2];          /*Զ�̿�������  ��2 CRC*/
uchar8 GV_Relay_State[CLRelay_State+C_CRCLen2];                      /*�̵���״̬  ��2 CRC*/
uchar8 GV_Relay_LocalOrder[CLRelay_LocalOrder+C_CRCLen2];            /*���ؿ������� ��2 CRC*/
uchar8 GV_Remote_Local_State[CLRemote_Local_State+C_CRCLen2];        /*Զ�̡����ؿ���״̬ ��2 CRC*/
uchar8 GV_Drive_Report_Mode[CLDrive_Report_Mode+C_CRCLen2];          /*�����ϱ�ģʽ�� ��2 CRC*/

uchar8 GV_AppProInformation[CLAppProInformation+C_CRCLen2];          /*Э��汾��Ϣ ��2 CRC*/
uchar8 GV_AppMaxReAPDU[CLAppMaxReAPDU+C_CRCLen2];                    /*������APDU�ߴ� ��2 CRC*/
uchar8 GV_AppMaxSeAPDU[CLAppMaxSeAPDU+C_CRCLen2];                    /*�����APDU�ߴ� ��2 CRC*/
uchar8 GV_AppMaxHandleAPDU[CLAppMaxHandleAPDU+C_CRCLen2];            /*���ɴ���APDU�ߴ� ��2 CRC*/
uchar8 GV_AppProConsistency[CLAppProConsistency+C_CRCLen2];          /*Э��һ���Կ� ��2 CRC*/
uchar8 GV_AppFunConsistency[CLAppFunConsistency+C_CRCLen2];          /*����һ���Կ� ��2 CRC*/
uchar8 GV_AppStaticTimeout[CLAppStaticTimeout+C_CRCLen2];            /*��̬��ʱʱ�� ��2 CRC*/

uchar8 GV_AppStaticTimeout_terminal[CLAppStaticTimeout+C_CRCLen2];   /*�ն˾�̬��ʱʱ�� ��2 CRC*/

uchar8 GV_ConAutheMechanism[CLConAutheMechanism+C_CRCLen2];          /*������֤���� ��2 CRC*/
uchar8 GV_SafeModePara[CLSafeModePara+C_CRCLen2];                    /*��ȫģʽ���� ��2 CRC*/

uchar8 GV_LoadWriteNum[CLLoadWriteNum+C_CRCLen2];                             /*���ɼ�¼����*/
uchar8 GV_Free_OADTab[C_698Free_Num][C_698Free_OADTabLen+C_CRCLen2];          /*698 OAD��ű�*/
uchar8 GV_Free_OADTabLen_T[C_698Free_Num][CLI_Free_OADTabLen_T+C_CRCLen2];    /*698 OAD��ű��ȼ�����*/
uchar8 GV_Free_StartTime[3][CLD_Free_StartTime+C_CRCLen2];                    /*698 ������ʼ����ʱ��*/

uchar8 GV_CurrDVolPerPass[4][C_CRCLen2+CLVol_Per_Pass_D];				/*RAM ��CRC ��ǰ�յ�ѹ�ϸ��ʣ���ABC*/

#if 0
uchar8 GV_Voltage_PassTime_D[C_CRCLen2+CLVol_PassTime_D];				/*RAM ��CRC ��ǰ�յ�ѹ�ϸ��ʵ�ѹ�ϸ�ʱ��*/
#endif

uchar8 GV_LossVolage_Report_Mode[C_CRCLen2+CLReport_Mode];				/*ʧѹ�ϱ�ģʽ��*/
uchar8 GV_LowVolage_Report_Mode[C_CRCLen2+CLReport_Mode];				/*Ƿѹ�ϱ�ģʽ��*/
uchar8 GV_OverVolage_Report_Mode[C_CRCLen2+CLReport_Mode];				/*��ѹ�ϱ�ģʽ��*/
uchar8 GV_BreakVol_Report_Mode[C_CRCLen2+CLReport_Mode];				/*�����ϱ�ģʽ��*/
uchar8 GV_LossCurr_Report_Mode[C_CRCLen2+CLReport_Mode];				/*ʧ���ϱ�ģʽ��*/
uchar8 GV_OverCurr_Report_Mode[C_CRCLen2+CLReport_Mode];				/*�����ϱ�ģʽ��*/
uchar8 GV_BreakCurr_Report_Mode[C_CRCLen2+CLReport_Mode];				/*�����ϱ�ģʽ��*/
uchar8 GV_PowerRev_Report_Mode[C_CRCLen2+CLReport_Mode];				/*���ʷ����ϱ�ģʽ��*/
uchar8 GV_OverLoad_Report_Mode[C_CRCLen2+CLReport_Mode];				/*�����ϱ�ģʽ��*/
uchar8 GV_PosAcDemandOv_Report_Mode[C_CRCLen2+CLReport_Mode];			/*�����й����������¼��ϱ�ģʽ��*/
uchar8 GV_RevAcDemandOv_Report_Mode[C_CRCLen2+CLReport_Mode];			/*�����й����������¼��ϱ�ģʽ��*/
uchar8 GV_ReDemandOv_Report_Mode[C_CRCLen2+CLReport_Mode];				/*�޹����������¼��ϱ�ģʽ��*/
uchar8 GV_PowerFactor_Report_Mode[C_CRCLen2+CLReport_Mode];				/*���������������¼��ϱ�ģʽ��*/
uchar8 GV_AllLossVolage_Report_Mode[C_CRCLen2+CLReport_Mode];			/*ȫʧѹ�ϱ�ģʽ��*/
uchar8 GV_AuxPowDown_Report_Mode[C_CRCLen2+CLReport_Mode];				/*������Դʧ���ϱ�ģʽ��*/
uchar8 GV_ReversedVoltage_Report_Mode[C_CRCLen2+CLReport_Mode];			/*��ѹ�������ϱ�ģʽ��*/
uchar8 GV_ReversedCurrent_Report_Mode[C_CRCLen2+CLReport_Mode];			/*�����������ϱ�ģʽ��*/
uchar8 GV_PowerOff_Report_Mode[C_CRCLen2+CLReport_Mode];				/*�����ϱ�ģʽ��*/
uchar8 GV_Program_Report_Mode[C_CRCLen2+CLReport_Mode];					/*����ϱ�ģʽ��*/
uchar8 GV_TolClear_Report_Mode[C_CRCLen2+CLReport_Mode];				/*��������ϱ�ģʽ��*/
uchar8 GV_DemandClear_Report_Mode[C_CRCLen2+CLReport_Mode];				/*���������ϱ�ģʽ��*/
uchar8 GV_EventClear_Report_Mode[C_CRCLen2+CLReport_Mode];				/*�¼������ϱ�ģʽ��*/
uchar8 GV_AdjTime_Report_Mode [C_CRCLen2+CLReport_Mode];				/*Уʱ�ϱ�ģʽ��*/
uchar8 GV_BroadcastTime_Report_Mode [C_CRCLen2+CLReport_Mode];			/*�㲥Уʱ�ϱ�ģʽ��*/
uchar8 GV_ProgPT_Report_Mode[C_CRCLen2+CLReport_Mode];					/*ʱ�α����ϱ�ģʽ��*/
uchar8 GV_ProgPZ_Report_Mode[C_CRCLen2+CLReport_Mode];					/*ʱ�������ϱ�ģʽ��*/
uchar8 GV_ProgWRe_Report_Mode[C_CRCLen2+CLReport_Mode];					/*�����ձ���ϱ�ģʽ��*/
uchar8 GV_ProgSettD_Report_Mode[C_CRCLen2+CLReport_Mode];				/*�����ձ���ϱ�ģʽ��*/
uchar8 GV_OpenW_Report_Mode[C_CRCLen2+CLReport_Mode];					/*������ϱ�ģʽ��*/
uchar8 GV_OpenCW_Report_Mode[C_CRCLen2+CLReport_Mode];					/*����ť���ϱ�ģʽ��*/
uchar8 GV_NoBalVol_Report_Mode[C_CRCLen2+CLReport_Mode];				/*��ѹ��ƽ���ϱ�ģʽ��*/
uchar8 GV_NoBalCurr_Report_Mode[C_CRCLen2+CLReport_Mode];				/*������ƽ���ϱ�ģʽ��*/
uchar8 GV_RelayOpen_Report_Mode[C_CRCLen2+CLReport_Mode];				/*��բ�ϱ�ģʽ��*/
uchar8 GV_RelayClose_Report_Mode[C_CRCLen2+CLReport_Mode];				/*��բ�ϱ�ģʽ��*/
uchar8 GV_ProgHol_Report_Mode[C_CRCLen2+CLReport_Mode];					/*�ڼ��ձ���ϱ�ģʽ��*/
uchar8 GV_ProgAcC_Report_Mode[C_CRCLen2+CLReport_Mode];					/*�й���Ϸ�ʽ����ϱ�ģʽ��*/
uchar8 GV_ProgReC_Report_Mode[C_CRCLen2+CLReport_Mode];					/*�޹���Ϸ�ʽ����ϱ�ģʽ��*/
uchar8 GV_ProgTPara_Report_Mode[C_CRCLen2+CLReport_Mode];				/*���ʲ��������ϱ�ģʽ��*/
uchar8 GV_ProgLad_Report_Mode[C_CRCLen2+CLReport_Mode];					/*���ݱ����ϱ�ģʽ��*/
uchar8 GV_Key_Update_Report_Mode[C_CRCLen2+CLReport_Mode];				/*��Կ�����ϱ�ģʽ��*/
uchar8 GV_AbnorC_Report_Mode[C_CRCLen2+CLReport_Mode];					/*�쳣�忨�ϱ�ģʽ��*/
uchar8 GV_BuyCurr_Report_Mode[C_CRCLen2+CLReport_Mode];					/*�����ϱ�ģʽ��*/
uchar8 GV_ReturnMoney_Report_Mode[C_CRCLen2+CLReport_Mode];				/*�˷��ϱ�ģʽ��*/
uchar8 GV_ConMEndEn_Report_Mode[C_CRCLen2+CLReport_Mode];				/*�㶨�ų������ϱ�ģʽ��*/
uchar8 GV_RelayFaEndEn_Report_Mode[C_CRCLen2+CLReport_Mode];			/*���ɿ��������ϱ�ģʽ��*/
uchar8 GV_PowerFa_EndT_Report_Mode[C_CRCLen2+CLReport_Mode];			/*��Դ�쳣�ϱ�ģʽ��*/
uchar8 GV_SeriNoBalCurr_Report_Mode[C_CRCLen2+CLReport_Mode];			/*�������ز�ƽ���ϱ�ģʽ��*/
uchar8 GV_ClockFault_Report_Mode[C_CRCLen2+CLReport_Mode];				/*ʱ�ӹ����ϱ�ģʽ��*/
uchar8 GV_MeteringChipFault_Report_Mode[C_CRCLen2+CLReport_Mode];		/*����оƬ�����ϱ�ģʽ��*/
uchar8 GV_ABnor_ZeroCurrent_Report_Mode[C_CRCLen2+CLABnor_ZeroCurrent_Report_Mode];		/*���ߵ����쳣�ϱ�ģʽ��*/

uchar8 GV_LossVolage_Report_Type[C_CRCLen2+CLReport_Type];					/*ʧѹ�ϱ���ʽ*/
uchar8 GV_LowVolage_Report_Type[C_CRCLen2+CLReport_Type];					/*Ƿѹ�ϱ���ʽ*/
uchar8 GV_OverVolage_Report_Type[C_CRCLen2+CLReport_Type];					/*��ѹ�ϱ���ʽ*/
uchar8 GV_BreakVol_Report_Type[C_CRCLen2+CLReport_Type];					/*�����ϱ���ʽ*/
uchar8 GV_LossCurr_Report_Type[C_CRCLen2+CLReport_Type];					/*ʧ���ϱ���ʽ*/
uchar8 GV_OverCurr_Report_Type[C_CRCLen2+CLReport_Type];					/*�����ϱ���ʽ*/
uchar8 GV_BreakCurr_Report_Type[C_CRCLen2+CLReport_Type];					/*�����ϱ���ʽ*/
uchar8 GV_PowerRev_Report_Type[C_CRCLen2+CLReport_Type];					/*���ʷ����ϱ���ʽ*/
uchar8 GV_OverLoad_Report_Type[C_CRCLen2+CLReport_Type];					/*�����ϱ���ʽ*/
uchar8 GV_PosAcDemandOv_Report_Type[C_CRCLen2+CLReport_Type];				/*�����й����������¼��ϱ���ʽ*/  //
uchar8 GV_RevAcDemandOv_Report_Type[C_CRCLen2+CLReport_Type];				/*�����й����������¼��ϱ���ʽ*/  //
uchar8 GV_ReDemandOv_Report_Type[C_CRCLen2+CLReport_Type];					/*�޹����������¼��ϱ���ʽ*/
uchar8 GV_PowerFactor_Report_Type[C_CRCLen2+CLReport_Type];					/*���������������¼��ϱ���ʽ*/
uchar8 GV_AllLossVolage_Report_Type[C_CRCLen2+CLReport_Type];				/*ȫʧѹ�ϱ���ʽ*/
uchar8 GV_AuxPowDown_Report_Type[C_CRCLen2+CLReport_Type];					/*������Դʧ���ϱ���ʽ*/
uchar8 GV_ReversedVoltage_Report_Type[C_CRCLen2+CLReport_Type];				/*��ѹ�������ϱ���ʽ*/
uchar8 GV_ReversedCurrent_Report_Type[C_CRCLen2+CLReport_Type];				/*�����������ϱ���ʽ*/
uchar8 GV_PowerOff_Report_Type[C_CRCLen2+CLReport_Type];					/*�����ϱ���ʽ*/
uchar8 GV_Program_Report_Type[C_CRCLen2+CLReport_Type];						/*����ϱ���ʽ*/
uchar8 GV_TolClear_Report_Type[C_CRCLen2+CLReport_Type];					/*��������ϱ���ʽ*/
uchar8 GV_DemandClear_Report_Type[C_CRCLen2+CLReport_Type];					/*���������ϱ���ʽ*/
uchar8 GV_EventClear_Report_Type[C_CRCLen2+CLReport_Type];					/*�¼������ϱ���ʽ*/
uchar8 GV_AdjTime_Report_Type [C_CRCLen2+CLReport_Type];					/*Уʱ�ϱ���ʽ*/
uchar8 GV_BroadcastTime_Report_Type [C_CRCLen2+CLReport_Type];				/*�㲥Уʱ�ϱ���ʽ*/
uchar8 GV_ProgPT_Report_Type[C_CRCLen2+CLReport_Type];						/*ʱ�α����ϱ���ʽ*/
uchar8 GV_ProgPZ_Report_Type[C_CRCLen2+CLReport_Type];						/*ʱ�������ϱ���ʽ*/
uchar8 GV_ProgWRe_Report_Type[C_CRCLen2+CLReport_Type];						/*�����ձ���ϱ���ʽ*/
uchar8 GV_ProgSettD_Report_Type[C_CRCLen2+CLReport_Type];					/*�����ձ���ϱ���ʽ*/
uchar8 GV_OpenW_Report_Type[C_CRCLen2+CLReport_Type];						/*������ϱ���ʽ*/
uchar8 GV_OpenCW_Report_Type[C_CRCLen2+CLReport_Type];						/*����ť���ϱ���ʽ*/
uchar8 GV_NoBalVol_Report_Type[C_CRCLen2+CLReport_Type];					/*��ѹ��ƽ���ϱ���ʽ*/
uchar8 GV_NoBalCurr_Report_Type[C_CRCLen2+CLReport_Type];					/*������ƽ���ϱ���ʽ*/
uchar8 GV_RelayOpen_Report_Type[C_CRCLen2+CLReport_Type];					/*��բ�ϱ���ʽ*/
uchar8 GV_RelayClose_Report_Type[C_CRCLen2+CLReport_Type];					/*��բ�ϱ���ʽ*/
uchar8 GV_ProgHol_Report_Type[C_CRCLen2+CLReport_Type];						/*�ڼ��ձ���ϱ���ʽ*/
uchar8 GV_ProgAcC_Report_Type[C_CRCLen2+CLReport_Type];						/*�й���Ϸ�ʽ����ϱ���ʽ*/
uchar8 GV_ProgReC_Report_Type[C_CRCLen2+CLReport_Type];						/*�޹���Ϸ�ʽ����ϱ���ʽ*/
uchar8 GV_ProgTPara_Report_Type[C_CRCLen2+CLReport_Type];					/*���ʲ��������ϱ���ʽ*/
uchar8 GV_ProgLad_Report_Type[C_CRCLen2+CLReport_Type];						/*���ݱ����ϱ���ʽ*/
uchar8 GV_Key_Update_Report_Type[C_CRCLen2+CLReport_Type];					/*��Կ�����ϱ���ʽ*/
uchar8 GV_AbnorC_Report_Type[C_CRCLen2+CLReport_Type];						/*�쳣�忨�ϱ���ʽ*/
uchar8 GV_BuyCurr_Report_Type[C_CRCLen2+CLReport_Type];						/*�����ϱ���ʽ*/
uchar8 GV_ReturnMoney_Report_Type[C_CRCLen2+CLReport_Type];					/*�˷��ϱ���ʽ*/
uchar8 GV_ConMEndEn_Report_Type[C_CRCLen2+CLReport_Type];					/*�㶨�ų������ϱ���ʽ*/
uchar8 GV_RelayFaEndEn_Report_Type[C_CRCLen2+CLReport_Type];				/*���ɿ��������ϱ���ʽ*/
uchar8 GV_PowerFa_EndT_Report_Type[C_CRCLen2+CLReport_Type];				/*��Դ�쳣�ϱ���ʽ*/
uchar8 GV_SeriNoBalCurr_Report_Type[C_CRCLen2+CLReport_Type];				/*�������ز�ƽ���ϱ���ʽ*/
uchar8 GV_ClockFault_Report_Type[C_CRCLen2+CLReport_Type];					/*ʱ�ӹ����ϱ���ʽ*/
uchar8 GV_MeteringChipFault_Report_Type[C_CRCLen2+CLReport_Type];			/*����оƬ�����ϱ���ʽ*/
uchar8 GV_ABnor_ZeroCurrent_Report_Type[C_CRCLen2+CLReport_Type];			/*���ߵ����쳣�ϱ���ʽ*/
uchar8 GV_Drive_Report_Type[C_CRCLen2+CLReport_Type];						/*�����ϱ���ʽ*/

uchar8 GV_Relay_Delay_Time_645[CLRelay_Delay_Time_645+C_CRCLen2];					/*��բ��ʱʱ��,��2 CRC*/
uchar8 GV_Drive_Report_Mode_645[CLDrive_Report_Mode_645+C_CRCLen2];					/*�����ϱ�ģʽ��,��2 CRC*/
uchar8 GV_Meter_Work_Char1_645[CLMeter_Work_Char1_645+C_CRCLen2];					/*�������������1,��2 CRC*/
uchar8 GV_DisplayBorrowPoint[CLDisplayBorrowPoint+C_CRCLen2];						/*��ʾ��λλ��,��2 CRC*/
uchar8 GV_DisplayBorrowPoint_RecFlag[CLDisplayBorrowPoint_RecFlag+C_CRCLen2];		/*��ʾ��λλ��������־,��2 CRC*/

/************************���ݲ����ڲ���̬����********************************/
uchar8  GV_D_SafeFlag;                                  /*���ݲ��ڲ��ð�ȫ��־����Ѳ������������*/
uchar8  GV_20min_Num;                                   /*20min�ۼӼ�����*/
uchar8  GV_CruiseCheck_FlashNum;                        /*Ѳ��Flash����*/
uchar8  GV_CruiseCheck_RAMNum;                          /*Ѳ��RAM CRC����,��ǰѲ������ֻΪ��ǰ����*/
ulong32 GV_ReadLoadFlashAddr32;                         /*��ȫ�ֱ���������14�淶���ɼ�¼ģ�鳭���ã�����ʼ�����1�γ���ʱΪȫFF����1�γ�����ɺ�����1�����ɼ�¼Flash��ַ*/
ulong32 GV_ReadLoadFlashAddr32Ear;                      /*����14�淶���ɼ�¼ģ�鳭���ã���ʼ��ΪȫFF*/
ulong32 GV_ReadLoadFlashAddr32Late;                     /*����14�淶���ɼ�¼ģ�鳭���ã���ʼ��ΪȫFF*/
uchar8  GV_SecLoadModeNum;                              /*����14�淶���ɼ�¼ģ�鳭���ã����ڼ�¼��1����¼ģʽ����ţ���ʼ��ΪFF*/
uchar8  GV_ReadRecordNum;                               /*���ڼ�¼�����¼��Ӧ�����*/
uchar8  GV_D_ClearSafeFlag;                             /*���ݲ��ڲ������尲ȫ��־����Ѳ������������*/

/*************************���ݽṹ����***************************************/
#define NeedClearDataSign    0x80               /*���������ݱ�־*/
/************���ݴ洢��ʽ��д�����궨��*******645��ʶ������֧��645��ʽ�����ݳ��ȣ������������*********/
#define DT_Ref_E23_RAMCRC             1     /*��E2����CRC���ݼ�RAM��CRC(д��������ʱ����дRAM�����Ÿ���E2����,������ֵ������͸֧ʣ�������ʱ��ǰ�������)*/
#define DT_Ti_E23_RAMCRC              (NeedClearDataSign|2)    /*��E2����CRC���ݼ�RAM��CRC(д��������ʱ��ֻдRAM����ʱдE2����Ҫ�ǵ�ǰ������������)��ע�⣺Ŀǰ698����ɿ�������д���缰RAM������ֻ�ǵ�ǰ���ܵĴ���д����ʱ�ж�д�����ݵĺ����ԡ�ͬʱ��ʾ��������������*/
#define DT_E23                        3     /*��E2����CRC����*/
#define DT_Flash_DI04                 4     /*��Flash�����������ݣ�DI0��4λ��ʾ��������4λ��ʾ��ͬ��ʶ��(��ѯ4������)*/
#define DT_E21                        5     /*��E2һ��*/
#define DT_RAM                        6     /*��RAM����CRC*/
#define DT_RAMCRC                     7     /*��RAM��CRC*/
#define DT_E23_Hex                    8     /*��E2����CRC���ݣ����ݴ洢��ʽΪhex��ʽ(��Ҫ���ۼƴ�������ͨѶ��������ʱ��ת��ΪBCD��ʽ)*/
#define DT_Flash_Tol_DI0_DI1          9     /*��Flash�����������ݣ�����DI0��ʾ������DI1��ʾ�����ʶ��(��ѯ4������)*/
#define DT_RAM_Time_Data              10    /*��RAM����CRC��������ʱ���жϵ����־��*/
#if 0
#define DT_Flash_Tol_DI0_DI2          11    /*11�� Flash�����������ݣ�����DI0��ʾ������DI2��ʾ�����ʶ��(��ѯ4�����ã���������ABC�������ݶ�)*/
#define DT_Flash_Tol_DI0_SettEn       12    /*12��Flash�����������ݣ�����DI0��ʾ����������DI2��DI1�������ƫ�Ƶ�ַ(�����ѯ4������Ҫ�ǽ������������ABC����������)��*/
                                            /*ͬʱ���ݳ��ȼ��������ݣ������Ƿ���6+4(������ʾ),��6+2(����ͨ��)���������⴦��*/
#define DT_Flash_Tol_DI0_SettDe       13    /*13��Flash�����������ݣ�����DI0��ʾ����������DI2��DI1�������ƫ�Ƶ�ַ(�����ѯ4������Ҫ�ǽ�������������ABC����������)��*/
#define DT_Flash_Tol_DI0_W_Sett_En    14    /*14��Flash�����������ݣ�����DI0��ʾ����������ģ��д����ʱһ��д���ݲ㣬���ݲ��ڲ������������������ʱ��ֿ��洢*/
#endif
#define DT_Flash_Tol_DI0              15    /*15�� Flash�����������ݣ�����DI0��ʾ������û�з����ʶ�롣*/
#if 0
#define DT_E23_En                     16    /*16�����������ݣ�����6+2��6+4���ݳ���ʱ���������赥���������ݳ���(����д)���������ݣ������Ƿ���6+4(������ʾ),��6+2(����ͨ��)���������⴦��*/
                                            /*(�б�645���ݳ���Ϊ6+2��������6+4������ʱ���������ݳ��ȵ�����ȡE2��ַ����������1��������������й��ۼ��õ���),д����ʱ�����ݳ����жϵ�����*/
#define DT_E21_En                     17    /*17�����������ݣ�����6+2��6+4���ݳ���ʱ���������赥���������ݳ���(����д)���������ݣ������Ƿ���6+4(������ʾ),��6+2(����ͨ��)���������⴦��,��Ҫ��Դ�E2 1������*/
                                            /*(�б�645���ݳ���Ϊ6+2��������6+4������ʱ���������ݳ��ȵ�����ȡE2��ַ����������1--4��������ս���ʱ�估������������й����ۼ��õ���*/
#endif
#define DT_RAM_DI0                    18    /*18�����ݴ�RAM����CRC�������ݳ��ȡ�����һ��(ͬһDI3-DI1)���б��ʱֻ��DI0���ֵ(,ͬһ���ͣ�������DI0=0��DI0=0Ҫ����)�������ڲ�����*/
                                            /*���ݵ�ַ��DI�ж��Ƿ���ȷ�������Ƶ������״̬��1-7���б��ʱ����Ӧ���ݴ洢��ַ��Ϊ���DI0��Ӧ���ݴ洢��ַ��ע��*/
#define DT_Ref_E23_RAMCRC_DI0         19    /*19��E2����RAM��CRC�����ݳ�������һ��(ͬһDI3-DI1)���б��ʱֻ��DI0���ֵ(������DI0=0��DI0=0Ҫ����)�������ڲ�����*/
                                            /*���ݵ�ַ��DI�ж��Ƿ���ȷ�����������״̬�֣��б��ʱ����Ӧ���ݴ洢��ַ��Ϊ���DI0��Ӧ���ݴ洢��ַ��ע��*/
#define DT_E23_DI0                    20    /*20��E2������E2��ַ˳���У����ݳ�������һ��(ͬһDI3-DI1)���б��ʱֻ��DI0���ֵ(������DI0=0��DI0=0Ҫ����)�������ڲ�����*/
                                            /*���ݵ�ַ��DI�ж��Ƿ���ȷ�������ƽ����ա����룬�б��ʱ����Ӧ���ݴ洢��ַ��Ϊ���DI0��Ӧ���ݴ洢��ַ��ע��*/
#define DT_E21CRC_DI0                 21    /*21��E2һ����CRC�����ݳ�������һ��(ͬһDI3-DI1)���б��ʱֻ��DI0���ֵ(������DI0=0��DI0=0Ҫ����)�������ڲ�����*/
                                            /*���ݵ�ַ��DI�ж��Ƿ���ȷ���������Զ�ѭ����ʾ��1-99����ʾ���룬�б��ʱ����Ӧ���ݴ洢��ַ��Ϊ���DI0��Ӧ���ݴ洢��ַ��ע��*/
#define DT_E21_DI0                    22    /*22��E2һ�������ݳ�������һ��(ͬһDI3-DI1)���б��ʱֻ��DI0���ֵ(������DI0=0��DI0=0Ҫ����)�������ڲ�����*/
                                            /*���ݵ�ַ��DI�ж��Ƿ���ȷ�������Ƶ�1-254�����������ڼ���ʱ�α�ţ��б��ʱ����Ӧ���ݴ洢��ַ��Ϊ���DI0��Ӧ���ݴ洢��ַ��ע��*/
#if 0
#define DT_RAM_DI1_0                  23    /*23�����ݴ�RAM����CRC�������ݳ��ȡ�����һ��(ͬһDI3-DI2��DI0)���б��ʱֻ��DI1���ֵ(,ͬһ����,����DI1=0����������ƫ�Ƶ�ַʱ��Ҫ����)��*/
                                            /*�����ڲ��������ݵ�ַ��DI�ж��Ƿ���ȷ�������Ʋ���˲ʱ���ʣ��б��ʱ����Ӧ���ݴ洢��ַ��Ϊ���DI1��Ӧ���ݴ洢��ַ��ע��*/
#define DT_RAM_DI1                    24    /*24�����ݴ�RAM����CRC�������ݳ��ȡ�����һ��(ͬһDI3-DI2��DI0)���б��ʱֻ��DI1���ֵ(,ͬһ���ͣ�������DI1=0)�������ڲ�����*/
                                            /*���ݵ�ַ��DI�ж��Ƿ���ȷ�������Ƶ�ѹ���ݣ��б��ʱ����Ӧ���ݴ洢��ַ��Ϊ���DI1��Ӧ���ݴ洢��ַ��ע��*/
#define DT_R_Flash_Tol_DI0_DI2_En     25    /*25�� Flash�����������ݣ�����DI0��ʾ������DI2��ʾ�����ʶ��(��ѯ4�����ã�������ABC�������ݶ�)��*/
                                            /*ͬʱ���ݳ��ȼ��������ݣ������Ƿ���6+4(������ʾ),��6+2(����ͨ��)���������⴦��*/
#endif
#define DT_W_Ref_E23_RAMCRC_Te        26    /*26:дE2 RAM���ݣ�д��ʱģ��һ��д�룬���ݲ��ڲ����������ֿ�д���統ǰ�׷��ʵ�����ݿ�*/
#define DT_Flash_Tol_DI0_DI1Max       27    /*27�� Flash�����������ݣ�����DI0��ʾ�������б�2����ʱֻ����1��DI1���ֵ(�����ò���4����ķ�ʽ)���ڲ�������DI��DI���ݴ��ƫ�Ƶ�ַʱ��*/
                                            /*OffsetAddr������ü��㷽ʽ����,Ŀǰֻ��У���¼���ø÷�ʽ,������ʱ��DI1=0��*/
#define DT_Ref_E23_RAMCRC_DI0_2       28    /*28��E2����RAM��CRC�����ݳ�������һ��(ͬһDI3-DI1)���б��ʱֻ��DI0���ֵ(������DI0=0��1,DI0=0,1Ҫ����)�������ڲ�����*/
                                            /*���ݵ�ַ��DI�ж��Ƿ���ȷ��������ȫʧѹ��������������ã��б��ʱ����Ӧ���ݴ洢��ַ(��ѹ�쳣�жϵ�ѹ��ַ)��Ϊ���DI0��Ӧ���ݴ洢��ַ��ע��*/
#define DT_Flash_698EventTab          37    /*��OAD�����б��¼���¼����Flash*/
#define DT_E23_OADTab                 38    /*��E2������������ʱ�ж����ݳ��ȣ����ȡ�ù����б�OAD������д����ʱֻ�ж���󳤶�*/
#define DT_R_Ref_E23_RAMCRC_Lad       39    /*39:дE2 RAM���ݣ����ݱ�д��ʱ֧�ּ���д��������ʱ֧�ַֿ��������ݲ��ڲ���������*/
#define DT_E21CRC_MaxLen              40    /*40��E2һ����CRC��д��ʱ�жϲ�����������ݳ���*/
#if 0
#define DT_E21_DI0_ReadDegree         41    /*41��E2һ�������ݳ�������һ��(ͬһDI3-DI1)���б��ʱֻ��DI0���ֵ(������DI0=0��DI0=0Ҫ����)�������ڲ�����*/
                                            /*���ݵ�ַ��DI�ж��Ƿ���ȷ��������ʱ���ж���Ӧ���������¼��ϱ���񣬶�����ʱ�����ж϶�Ӧ�¼���¼�������б��ʱ����Ӧ���ݴ洢��ַ��Ϊ���DI0��Ӧ���ݴ洢��ַ��ע��*/
#endif
#define DT_FRAM1CRC                   42    /*42������һ����CRC*/
#if 0
#define DT_E23_En_Clear               (DT_E23_En|NeedClearDataSign)    /*16�����������ݣ�����6+2��6+4���ݳ���ʱ���������赥���������ݳ���(����д)���������ݣ������Ƿ���6+4(������ʾ),��6+2(����ͨ��)���������⴦��*/
                                            /*(�б�645���ݳ���Ϊ6+2��������6+4������ʱ���������ݳ��ȵ�����ȡE2��ַ����������1��������������й��ۼ��õ���),д����ʱ�����ݳ����жϵ�����*/
#endif
#define DT_E23_Clear                  (DT_E23|NeedClearDataSign)    /*��E2����CRC����*/

#define C_RAM_Max                     240    /*дE2�����ڲ���󻺴�,���Ȱ���2�ֽ�CRC*/
#define C_Clear_SafeFlag              0
#define C_Flash_EmptyNum              4      /*ÿҳԤ���ձ�־�ֽ���*/
#define C_OneFlash_PageNum            (4096-C_Flash_EmptyNum)    /*ÿҳFlash�ɼ�¼������*/
#define C_Flash_Empty                 0x00   /*��Flash�Ƿ�Ϊ���жϣ�Flash�ײ㷴*/
#define C_Flash_NoEmpty               0xFF   /*дFlash��Ϊ��*/
#define C_Flash_Empty68               0x68   /*дFlashΪ�գ�ÿ�β�����д4��68��ʾ��ҳFlashΪ�գ���68��Ϊ��*/
#define C_LoadProfile_RevMode         1      /*698�����޸�ʱ���־�����ݳ���*/
#if 0
#define C_Wr_LoadProfile_MaxLen       105    /*д���ɼ�¼������ݳ��ȣ�ȫ��¼103���ֽ�*/
#define C_LoadP_CurrVol_Len_Bit0      17     /*��1�ฺ�ɼ�¼��ѹ��������Ƶ�����ݳ���*/
#define C_LoadP_Power_Len_Bit1        24     /*��2�ฺ�ɼ�¼�������ݳ���*/
#define C_LoadP_PowActor_Len_Bit2     8      /*��3�ฺ�ɼ�¼�����������ݳ���*/
#define C_LoadP_TolEn_Len_Bit3        16     /*��4�ฺ�ɼ�¼�С��޹��ܵ������ݳ���*/
#define C_LoadP_QuarEn_Len_Bit4       16     /*��5�ฺ�ɼ�¼�������޹��ܵ������ݳ���*/
#define C_LoadP_CurrDe_Len_Bit5       6      /*��6�ฺ�ɼ�¼��ǰ�������ݳ���*/
#endif
#define C_GV_20min_Num                240    /*5s�ۼӶ�ʱ����20min*/
#define C_GV_19min_50s_Num            238    /*5s�ۼӶ�ʱ����20min*/
#define C_FlashEvenOEEPageNum         12     /*Flash��¼��żҳ��������ѯ����12������ҳ��¼��=12��ʱ�����ѯ������ҳ�����������������*/
#define C_MeterICE2ResLen             3      /*У��Ĵ������ݳ���*/
#define C_RAMRefE2En_MaxPluse         80000  /*20minRAM��������E2��ֵ,��������-�����ݲ����������������ֵ ����*/
#define C_Meter_Work_State1           0xC33C /*�������״̬��1:  Bit1���������㷽ʽ*/
#define C_Meter_Work_State2           0x0077 /*�������״̬��2*/
//#define C_Meter_Work_State3         0x0077 /*�������״̬��3�������ڲ�����*/
#define C_Meter_Work_State4           0x01FF /*�������״̬��4*/
#define C_Meter_Work_State5           0x01FF /*�������״̬��5*/
#define C_Meter_Work_State6           0x01FF /*�������״̬��6*/
#define C_Meter_Work_State7           0x07FF /*�������״̬��7*/
#define C_HardError                   0x01   /*Ӳ����������״̬��*/
#if 0
#define C_WriteAllLoadMode            0x3F   /*���и��ɼ�¼ģʽ��ȫ��3F*/
#define C_RealTimeParaLoadMode        0x01   /*ʵʱ�������ɼ�¼ģʽ��*/
#define C_PowerLoadMode               0x02   /*���ʸ��ɼ�¼ģʽ��*/
#define C_PowerFactorLoadMode         0x04   /*�����������ɼ�¼ģʽ��*/
#define C_ReAcEnergy                  0x08   /*�С��޹��ܵ��ܸ��ɼ�¼ģʽ��*/
#define C_FourQuarterEnLoadMode       0x10   /*4���޵��ܸ��ɼ�¼ģʽ��*/
#define C_DemandLoadMode              0x20   /*�������ɼ�¼ģʽ��*/
#define C_AllLoadModeDataLen          103    /*���ɼ�¼ȫ��¼���ݳ���*/
#define C_LoadEndSign                 0xE5   /*���ɼ�¼������־*/
#endif
#define C_LoadStartSign               0xA0   /*���ɼ�¼��ʼ��־*/
#if 0
#define C_LoadBlockSign               0xAA   /*���ɼ�¼��ָ��־*/
#define C_OneLoadFixedLength          16     /*1�����ɼ�¼�̶����ݳ��ȣ�2A0+1�ֽ���+5ʱ��+6AA+1CS+1E5*/
#define C_OneLoadByteLength           5      /*���ɼ�¼���ֽ�����ʾ�����ݳ��ȣ��ü�¼�ܳ���-�����ݳ���5(2A0+1�ֽ���+1CS+1E5)*/
#define C_OneLoadFlashMemoryLength    1      /*1�����ɼ�¼����Flashʱ���ܳ���ȥ�������ݳ��ȣ��ü�¼�ܳ���-�����ݳ���1(Ŀǰȥ�� 1�ֽ���)*/
#endif
#define C_LoadStartSignLength         0      /*���ɼ�¼��ʼ�볤�ȣ�2A0����ΪYMDhms 698�����¼��ʼΪYMDhms */
#define C_LoadDichotomyFindBefore     0x55   /*��ʾ2�ַ���ʱ����ǰ���ң���Ҫ����ʱ����ǰ����*/
#define C_LoadDichotomyFindAfter      0xAA   /*��ʾ2�ַ���ʱ��������ң���Ҫ���ڳ������ɼ�¼����ʱ��*/

#define C_NiuDebugReadData            0x01   /*���ײ�E2��Flash���ݽӿں����������ã�0x00����������*/
#if 0
#define C_NotNeedRenew                0xFFFF /*����Ҫ����*/
#endif
#define C_NextSign                    0x10   /*����֡��־��Bit4-5:1�к���֡��0û�к���֡*/
#define C_NoNextSign                  0x00   /*����֡��־��Bit4-5:1�к���֡��0û�к���֡*/

#define C_NextSign_Judge              0x30   /*����֡��־��Bit4-5:1�к���֡��0û�к���֡*/

#define C_NextSign_Last               0x40   /*Bit7-6:1����ʾ�������ݰ������1����¼��0����ʾ�������ݲ��������1����¼*/

#define C_698Event_MaxNum100          100    /*�㲥Уʱ�͵�����������100��*/
#define C_698Event_MaxNum             10     /*�¼���������Ŀǰ��10��*/
#define C_698Key_UpdateEvent_MaxNum   2      /*�¼�����������Կ������2�Σ����ݴ��������ж���*/

//***********************************�������֡***************/
#define C_FreezeNextSign              0x02   /*����֡��־��Bit0-1:2�к���֡����2�޺���֡*/
#define C_FreezeNextSignFlag          0x03   /*����֡�ж�λBit0-1*/


/*��ȡ�����й��������жϱ�־*/
#define C_ReadRelated02Energy         0x01   /*��ȡ����02���Ե���*/
#define C_SaveRelated04Energy         0x02   /*�洢����04���Ե���*/
#define C_EnergyPlanSame              0x04   /*���ܷ�������ͬ��*/

//***********************************���̰�ȫ��־***************/
#define	C_DataClearMeterSafeFlag      0x36   /*������尲ȫ�ֽ�ֵ*/
#define	C_DataClearMeterSafeFlag_1    0x06   /**/
#define	C_DataClearMeterSafeFlag_2    0x10   /**/
#define	C_DataClearMeterSafeFlag_3    0x20   /**/

typedef struct
{
	ulong32 V_DI;               /*DI:DI3~DI0���ݱ�ʶ*/
	ulong32 PStr_3TableAddr;    /*��Ӧ3�����ṹ�������ַ����3�����ǽṹ��ʱ��ֱ��Ϊ���ݴ��E2��RAM���Ե�ַ*/
	ushort16 V_LineNum;         /*�кţ���������Ϊ�ṹ������ʱ����ʾ���ݱ�����ݶ�Ӧ�����������������кţ�*/
	                            /*�ǽṹ��ʱ��������Ϊ0*/
	ushort16 V_DataLen;         /*DI3~DI0���ݱ�ʶ��Ӧ�ľ������ݳ���*/
	uchar8 V_WR_MesAuth;        /*WR:����ֽڱ�ʾBit7:��ʾ��Ӧ��ʶ�룬�Ƿ�֧�ֶ���*/
	                            /*1��֧�֣�0����֧��        */
	                            /*Bit0~Bit6����ʾд������Ϣ�ţ���֧�ֶ����Ϣдʱ��������Ϸ�ʽ��ȫ���ʾ��֧��д��*/
	uchar8 V_DT_Type;           /*�����л��ܢ�~13�����ݴ洢����*/
}Str_2Table;

typedef struct
{
	Str_2Table *PV_Str_2Table;  /*�����¼���¼����֡�����ã��������֡����.����Ҫ����¼�2������Ե�ַ**/
	uchar8 V_NextSign;          /*����֡��־����ȫ���ж�*/
	uchar8 V_LastNum;           /*�����¼���¼������¼�ϴζ�ȡ�����ٴΣ��������֡���´μ�������*/
	ushort16 V_CRC16;
}Str_NextEvent;

Str_NextEvent GV_Str_NextEvent;

#define C_NextLoadTime_MaxNum      12    /*�����ն������12��*/
#define C_FreezeImmid_MaxNum       3     /*˲ʱ�������3��*/
#define C_FreezeTimeZone_MaxNum    2     /*�л��������2��*/
#define C_YSettleFreeze_MaxNum     4     /*�����л��������4��*/

uchar8 GV_FreezeLastNum[3];              /*���ڶ����¼������¼�ϴζ�ȡ�����ٴΣ��������֡���´μ�������*/
/*******************************************************�������ṹ�嶨��***********************************************************/
typedef struct
{
	ushort16 V_OffAddr;    /*����1��¼�����з����ʶ��(��������)*/
	                       /*���ڴ�ż�¼�ñ�ʶ���Ӧ������ƫ�Ƶ�ַ������ֵ����������ʶ��*/
	uchar8 V_DI;           /*��������ƫ�Ƶ�ַ��1�����ݱ�ʾ*/
}Str_4Table;

typedef struct
{
	ulong32 V_StaFlashAddr;          /*��ʼҳ��ַ����¼��Flash��ҳ��ַ*/
	ulong32 V_EndFlashAddr;          /*����ҳ��ַ����¼��Flashβҳ��ַ*/
	ulong32 PStr_4TableAddr;         /*4�����ṹ�������ַ*/
	ushort16 V_Num_E2BakeUp1Addr;    /*������E2��1�����ݵ�ַ*/
	ushort16 V_DataToalLen;          /*1����¼�������ܳ���*/
	uchar8  V_Str_4TableLen;         /*4�����ṹ���������ݳ���,��������4����ʱ������Ϊȫ��*/
}Str_3cTable;

typedef struct
{
	ushort16 V_E2BakeUp1Addr;        /*���ݴ��E2��������,��һ���ַ����2��3����ù̶������ַ*/
	uchar8 *V_RamAddr;               /*���ݴ��RAM��ַ*/
	ushort16 V_DataLen;              /*ÿ��������ȣ�������Ŀ������E2���ݻָ�RAM,������CRC����*/
	uchar8 V_DataNum;                /*ÿ�������������������Ŀ������E2���ݻָ�RAM����04FE00��Ŀ�б��DIʱ��û��ȫ�У���ʱ�ĸ���ĿΪ8:01-08*/
}Str_3aTable;

typedef struct
{
	ushort16 V_E2BakeUp1Addr_OADTab;       /*���ݴ��E2��������,��һ���ַ����2��3����ù̶������ַ,����OAD��ű�*/
	ushort16 V_E2BakeUp1Addr_OADTabLen;    /*���ݴ��E2��������,��һ���ַ����2��3����ù̶������ַ,������ű�OAD����*/
//	uchar8 V_DI2;                          /*��ͬ�¼���¼DI2*/
}Str_3eTable;

typedef struct
{
	ulong32 PStr_2TableAddr;     /*2�����ṹ�������ַ**/
	ushort16 V_Str_2TableLen;    /*��Ӧ2����ṹ�����ݳ���*/
	uchar8 V_DI3;                /*���ݱ�ʶ*/
}Str_1Table;

typedef struct
{
	ulong32 V_DI;            /*�¼���¼���ݱ�ʾ*/
	ushort16 V_E2AddrSt;     /*���ݱ�ʶ��ӦE2��ʼ��ַ*/
	ushort16 V_E2AddrEnd;    /*���ݱ�ʶ��ӦE2������ַ*/
	uchar8 V_EventNum;       /*���ݱ�ʾ��ӦEventNum�ţ�ѧ�ƺ궨��*/
}Str_EvenTable;

typedef struct
{
	ulong32 V_StaFlashAddr;     /*��ʼҳ��ַ����¼��Flash��ҳ��ַ*/
	ulong32 V_EndFlashAddr;     /*����ҳ��ַ����¼��Flashβҳ��ַ*/
	ushort16 V_LineNumLen_T;    /*�кţ���ʾ���ݱ�����ݶ�Ӧ�����������������кţ�����OAD���ȡ����ڱ�*/
	ushort16 V_LineNumTab;      /*�кţ���ʾ���ݱ�����ݶ�Ӧ�����������������кţ�������ű�*/
	ushort16 V_E2AddrEar;       /*���ݱ�ʶ��ӦE2��ʼ��ַ*/
	ushort16 V_E2AddrLate;      /*���ݱ�ʶ��ӦE2������ַ*/
	uchar8 V_DI2;               /*����DI2*/
}Str_698FreezeAddrTable;

/************************************4���ֱ�************************************/
#define En_Data_Len           4          /*�����ֽ���������2λС��*/
#if 0
#define En_Data_Len_FF        20         /*ÿ������ֽ���*/
#define De_Data_Len           9          /*�����ֽ���(����ʱ��)������6λС��*/
#define De_Data_Len_FF        45         /*ÿ�������ֽ���*/
#define En_SettEn_BlockLen    276        /*69���������ݣ�6+2��4�ֽ�*/

#define PosA_Ac_En_Off        (5*4*9)    /*����A�������й�����ƫ�Ƶ�ַ*/
#define PosA_Ac_De_Off        (5*9*8)    /*����A�������й��������������ʱ��ƫ�Ƶ�ַ,2+6+YMDhm*/
#define TFree_Off_Len         20         /**ÿ����ʱ�������ݿ鳤��*/
#endif
#define Get_DI0    0x000000FF))          /*4������*/
#define Get_DI1    0x0000FF00)>>8)
#define Get_DI2    0x00FF0000)>>16)
#define Get_DI3    0xFF000000)>>24)
#define Get_OI     0xFFFF0000)>>16)

/*****************�¼���¼���***********************/
/**********��ǰֵ��¼�������ۼ�ʱ�䣬���ݲ��ڲ�ͳһ�������********/
typedef struct
{
	ulong32 V_OAD;                   /*�¼���¼����ǰֵ��¼��OAD*/
	ushort16 V_Num_E2BakeUp1Addr;    /*��ǰֵ��¼���ж�Ӧ�¼���������E2��ַ*/
}Str_EventCurrentTab;

const Str_EventCurrentTab GCStr_EventCurrentTab[]=  /************��ǰ��¼��*************/
{
/*�¼���¼����ǰֵ��¼��OAD                 ��ǰֵ��¼���ж�Ӧ�¼���������E2��ַ*/
	{CTol_Clear_Current,            E2Addr_Tol_Clear_Degree},		/*���嵱ǰֵ��¼���=array ��ǰֵ,�ܴ��������ۼ�ʱ�䣬��������Դ*/
	{CDe_Clear_Current,             E2Addr_De_Clear_Degree},		/*���嵱ǰֵ��¼���=array ��ǰֵ,�ܴ��������ۼ�ʱ�䣬��������Դ*/
	{CEven_Clear_Current,           E2Addr_Even_Clear_Degree},		/*�¼����㵱ǰֵ��¼���=array ��ǰֵ,�ܴ��������ۼ�ʱ�䣬��������Դ*/
	{CProgram_Current,              E2Addr_Program_Degree},			/*��̼�¼��ǰֵ��¼���=array ��ǰֵ,�ܴ��������ۼ�ʱ�䣬��������Դ*/
	{CAdjTime_Current,              E2Addr_AdjTime_Degree},			/*Уʱ��¼��ǰֵ��¼���=array ��ǰֵ,�ܴ��������ۼ�ʱ�䣬��������Դ*/
	{CProgPT_Current,               E2Addr_ProgPT_Degree},			/*ʱ�α��¼��ǰֵ��¼���=array ��ǰֵ,�ܴ��������ۼ�ʱ�䣬��������Դ*/
	{CProgTZ_Current,               E2Addr_ProgTZ_Degree},			/*ʱ�����¼��ǰֵ��¼���=array ��ǰֵ,�ܴ��������ۼ�ʱ�䣬��������Դ*/
	{CProgWRe_Current,              E2Addr_ProgWRe_Degree},			/*�����ձ�̼�¼��ǰֵ��¼���=array ��ǰֵ,�ܴ��������ۼ�ʱ�䣬��������Դ*/
	{CProgHol_Current,              E2Addr_ProgHol_Degree},			/*�ڼ��ձ�̼�¼��ǰֵ��¼���=array ��ǰֵ,�ܴ��������ۼ�ʱ�䣬��������Դ*/
	{CProgAcC_Current,              E2Addr_ProgAcC_Degree},			/*�й���Ϸ�ʽ��̼�¼��ǰֵ��¼���=array ��ǰֵ,�ܴ��������ۼ�ʱ�䣬��������Դ*/
	{CProgSettD_Current,            E2Addr_ProgSettD_Degree},		/*�����ձ�̼�¼��ǰֵ��¼���=array ��ǰֵ,�ܴ��������ۼ�ʱ�䣬��������Դ*/
	{CProgTPara_Current,            E2Addr_ProgTPara_Degree},		/*���ʲ������̼�¼��ǰֵ��¼���=array ��ǰֵ,�ܴ��������ۼ�ʱ�䣬��������Դ*/
	{CProgLad_Current,              E2Addr_ProgLad_Degree},			/*���ݱ��̼�¼��ǰֵ��¼���=array ��ǰֵ,�ܴ��������ۼ�ʱ�䣬��������Դ*/
	{CProgKD_Current,               E2Addr_ProgKD_Degree},			/*��Կ��̼�¼��ǰֵ��¼���=array ��ǰֵ,�ܴ��������ۼ�ʱ�䣬��������Դ*/
	{CAbnorC_Current,               E2Addr_AbnorC_Degree},			/*�쳣�忨��¼��ǰֵ��¼���=array ��ǰֵ,�ܴ��������ۼ�ʱ�䣬��������Դ*/
	{CBuyCurr_Current,              E2Addr_BuyCurr_Degree},			/*�����¼��ǰֵ��¼���=array ��ǰֵ,�ܴ��������ۼ�ʱ�䣬��������Դ*/
	{CReturn_M_Current,             E2Addr_Return_M_Degree},		/*�˷Ѽ�¼��ǰֵ��¼���=array ��ǰֵ,�ܴ��������ۼ�ʱ�䣬��������Դ*/
	{CRelayOpen_Current,            E2Addr_RelayOpen_Degree},		/*��բ��ǰֵ��¼���=array ��ǰֵ,�ܴ��������ۼ�ʱ�䣬��������Դ*/
	{CRelayClose_Current,           E2Addr_RelayClose_Degree},		/*��բ��ǰֵ��¼���=array ��ǰֵ,�ܴ��������ۼ�ʱ�䣬��������Դ*/
	{CBroadcastTime_Current,        E2Addr_BroadcastTime_Degree},	/*�㲥Уʱ��¼��ǰֵ��¼���=array ��ǰֵ,�ܴ��������ۼ�ʱ�䣬��������Դ*/
//	{CBroadTimeAbnormal_Current,    E2Addr_BroadTimeAbnormal_Degree},
};
#define GCStr_EventCurrentTab_Len (sizeof(GCStr_EventCurrentTab)/sizeof(Str_EventCurrentTab))

/**********�������¼��̶������б��Ӧ���ݲ��������ƫ��********/
#define C_EventHPSign          0x80    /*���λΪ1����ʾ��������*/
#define C_EventOutSign         0x7F    /*ȥ�����λ*/
#if 0
#define C_TolTabDataLenSign    1       /*�̶�������OAD�б���Ӧ�����ܳ���*/
#define C_FixTabDataLenSign    2       /*�̶�OAD�б���Ӧ�����ܳ���*/
#define C_TabDataLenSign       3       /*�ɱ�OAD�б���Ӧ�����ܳ���*/
#endif
typedef struct
{
	ulong32 V_OAD;       /*��Ӧ�̶��б�OAD*/
	uchar8 V_DataLen;    /*���ݳ������127,���λΪ1��ʾ����*/
}Str_4aTable;

const Str_4aTable Str_4aTable_AllLossVol[]=  /************ȫʧѹ***CLASS 7*************/
{
	/************ȫʧѹ****************/
/*��Ӧ�̶��б�OAD           ���ݳ������127,���λΪ1��ʾ����*/
	{CEventNum,								(C_EventHPSign|CLEventNum)},
	{CEventHPTime,							(C_EventHPSign|CLEventHPTime)},
	{CEventEndTime,							(CLEventEndTime)},
	{CEventHPSource,						(C_EventHPSign|0x01)},
	{CUpdata_Status,						(C_EventHPSign|0x01)},			/*�¼��ϱ�״̬*/
};
#define Str_4aTable_AllLossVol_Len (sizeof(Str_4aTable_AllLossVol)/sizeof(Str_4aTable))


const Str_4aTable Str_4aTable_De_Over[]=  /************���������¼���Ԫ***CLASS 7*************/
{
/*��Ӧ�̶��б�OAD     					���ݳ������127,���λΪ1��ʾ����*/
	{CEventNum,                   			(C_EventHPSign|CLEventNum)	},
	{CEventHPTime,                			(C_EventHPSign|CLEventHPTime)},
	{CEventEndTime,               			(CLEventEndTime)},
	{CEventHPSource,              			(C_EventHPSign|0x01)},
	{CUpdata_Status,						(C_EventHPSign|0x01)},			/*�¼��ϱ�״̬*/
	{C_OverDemandRenew_Demand,            	(CLCurr_AcDemand)},				/*���������ڼ��������*/
	{C_OverDemandRenew_HapTime,            	(CLDate_Time)},					/*���������ڼ������������ʱ��*/
};
#define Str_4aTable_De_Over_Len  (sizeof(Str_4aTable_De_Over)/sizeof(Str_4aTable))

const Str_4aTable Str_4aTable_Qua_De_Over[]=  /************�޹����������¼���Ԫ***CLASS 24���ݶ�*************/
{
/*��Ӧ�̶��б�OAD               ���ݳ������127,���λΪ1��ʾ����*/
	{CEventNum,                   			(C_EventHPSign|CLEventNum)	},
	{CEventHPTime,                			(C_EventHPSign|CLEventHPTime)},
	{CEventEndTime,               			(CLEventEndTime)},
	{CEventHPSource,              			(C_EventHPSign|0x01)},
	{CUpdata_Status,						(C_EventHPSign|0x01)},			/*�¼��ϱ�״̬*/
	{C_OverDemandRenew_Demand,            	(CLCurr_ReDemand)},				/*���������ڼ��������*/
	{C_OverDemandRenew_HapTime,            	(CLDate_Time)},					/*���������ڼ������������ʱ��*/
};
#define Str_4aTable_Qua_De_Over_Len  (sizeof(Str_4aTable_Qua_De_Over)/sizeof(Str_4aTable))

const Str_4aTable Str_4aTable_Even_Clear[]=  /************�¼������¼��Ԫ***CLASS 7*************/
{
/*��Ӧ�̶��б�OAD                 ���ݳ������127,���λΪ1��ʾ����*/
	{CEventNum,                   			(C_EventHPSign|CLEventNum)	},
	{CEventHPTime,                			(C_EventHPSign|CLEventHPTime)},
	{CEventEndTime,               			(CLEventEndTime)},
	{CEventHPSource,              			(C_EventHPSign|0x01)},
	{CUpdata_Status,						(C_EventHPSign|0x01)},			/*�¼��ϱ�״̬*/
	{CEventClear_OADList,					(C_EventHPSign|CLProgOAD)},		/*��̼�¼OAD�б�*/
};
#define Str_4aTable_Even_Clear_Len  (sizeof(Str_4aTable_Even_Clear)/sizeof(Str_4aTable))

const Str_4aTable Str_4aTable_Prog[]=  /************��̼�¼��Ԫ***CLASS 7*************/
{
/*��Ӧ�̶��б�OAD     					���ݳ������127,���λΪ1��ʾ����*/
	{CEventNum,                   			(C_EventHPSign|CLEventNum)	},
	{CEventHPTime,                			(C_EventHPSign|CLEventHPTime)},
	{CEventEndTime,               			(CLEventEndTime)},
	{CEventHPSource,              			(C_EventHPSign|0x01)},
	{CUpdata_Status,						(C_EventHPSign|0x01)},			/*�¼��ϱ�״̬*/
	{CProgOADGather,              			(CLProgOADGather)},				/*��̼�¼OAD�б�*/
};
#define Str_4aTable_Prog_Len  (sizeof(Str_4aTable_Prog)/sizeof(Str_4aTable))

const Str_4aTable Str_4aTable_AbnorC[]=  /************�쳣�忨��¼***CLASS 7*************/
{
/*��Ӧ�̶��б�OAD     					���ݳ������127,���λΪ1��ʾ����*/
	{CEventNum,                   			(C_EventHPSign|CLEventNum)	},
	{CEventHPTime,                			(C_EventHPSign|CLEventHPTime)},
	{CEventEndTime,               			(CLEventEndTime)},
	{CEventHPSource,              			(C_EventHPSign|0x01)},
	{CUpdata_Status,						(C_EventHPSign|0x01)},								/*�¼��ϱ�״̬*/
	{CAbnormalCard_CareNo,					(C_EventHPSign|CLAbnormalCard_CareNo)},				/*�쳣�忨�����к�*/
	{CAbnormalCard_ErrorStatus,				(C_EventHPSign|CLAbnormalCard_ErrorStatus)},		/*�쳣�忨����״̬��*/
	{CAbnormalCard_OrderHead,				(C_EventHPSign|CLAbnormalCard_OrderHead)},			/*�쳣�忨�忨��������ͷ*/
	{CAbnormalCard_ErrorRespondStatus,		(C_EventHPSign|CLAbnormalCard_ErrorRespondStatus)},	/*�쳣�忨�忨������Ӧ״̬*/
};
#define Str_4aTable_AbnorC_Len  (sizeof(Str_4aTable_AbnorC)/sizeof(Str_4aTable))


const Str_4aTable Str_4aTable_Return_M[]=  /************�˷Ѽ�¼***CLASS 7*************/
{
/*��Ӧ�̶��б�OAD     					���ݳ������127,���λΪ1��ʾ����*/
	{CEventNum,                   			(C_EventHPSign|CLEventNum)	},
	{CEventHPTime,                			(C_EventHPSign|CLEventHPTime)},
	{CEventEndTime,               			(CLEventEndTime)},
	{CEventHPSource,              			(C_EventHPSign|0x01)},
	{CUpdata_Status,						(C_EventHPSign|0x01)},			/*�¼��ϱ�״̬*/
	{CReturnMoney_Charge,					(C_EventHPSign|CLReturn_M_Sum3)},
};
#define Str_4aTable_Return_M_Len  (sizeof(Str_4aTable_Return_M)/sizeof(Str_4aTable))

const Str_4aTable Str_4aTable_ProgPT[]=  /************ʱ�α��̼�¼***CLASS 7*************/
{
	/************ʱ�α��̼�¼****************/
/*��Ӧ�̶��б�OAD     					���ݳ������127,���λΪ1��ʾ����*/
	{CEventNum,                   			(C_EventHPSign|CLEventNum)	},
	{CEventHPTime,                			(C_EventHPSign|CLEventHPTime)},
	{CEventEndTime,               			(CLEventEndTime)},
	{CEventHPSource,              			(C_EventHPSign|0x01)},
	{CUpdata_Status,						(C_EventHPSign|0x01)},						/*�¼��ϱ�״̬*/
	{CRWTimeTable_OAD,              		(C_EventHPSign|CLProgOAD)},					/*ʱ�α���OAD*/
	{CRWTimeTable_ForwardData,				(C_EventHPSign|CLFirst_TZone_1PT_Data)},	/*ʱ�α��̱��ǰ����*/
};
#define Str_4aTable_ProgPT_Len  (sizeof(Str_4aTable_ProgPT)/sizeof(Str_4aTable))

const Str_4aTable Str_4aTable_ProgHol[]=  /************�������ձ�̼�¼***CLASS 7*************/
{
	/************�������ձ�̼�¼****************/
/*��Ӧ�̶��б�OAD     					���ݳ������127,���λΪ1��ʾ����*/
	{CEventNum,                   			(C_EventHPSign|CLEventNum)	},
	{CEventHPTime,                			(C_EventHPSign|CLEventHPTime)},
	{CEventEndTime,               			(CLEventEndTime)},
	{CEventHPSource,              			(C_EventHPSign|0x01)},
	{CUpdata_Status,						(C_EventHPSign|0x01)},					/*�¼��ϱ�״̬*/
	{C_RWHoliday_OAD,              			(C_EventHPSign|CLProgOAD)},				/*�ڼ��ձ��OAD*/
	{CRWHoliday_ForwardData,				(C_EventHPSign|CLHolidy_PT_Table1)},	/*�ڼ��ձ��ǰ�ڼ�������*/
};
#define Str_4aTable_ProgHol_Len  (sizeof(Str_4aTable_ProgHol)/sizeof(Str_4aTable))

const Str_4aTable Str_4aTable_QuaReDeOver[]=  /************�޹��������ޣ�CLASS 24*************/
{
	/************�޹���������****************/
/*��Ӧ�̶��б�OAD     					���ݳ������127,���λΪ1��ʾ����*/
	{CEventNum,                   			(C_EventHPSign|CLEventNum)},
	{CEventHPTime,                			(C_EventHPSign|CLEventHPTime)},
	{CEventEndTime,               			(CLEventEndTime)},
	{CUpdata_Status,						(C_EventHPSign|0x01)},			/*�¼��ϱ�״̬*/
};
#define Str_4aTable_QuaReDeOver_Len  (sizeof(Str_4aTable_QuaReDeOver)/sizeof(Str_4aTable))

typedef struct
{
	ulong32 V_StaFlashAddr;            /*��ʼҳ��ַ����¼��Flash��ҳ��ַ*/
	ulong32 V_EndFlashAddr;            /*����ҳ��ַ����¼��Flashβҳ��ַ*/
	ulong32 PStr_4aTableAddr;          /*4a�����ṹ�������ַ���¼��̶������б�*/
	ushort16 V_TB_E2BakeUp1Addr;       /*�����б��E2��1�����ݵ�ַ*/
	ushort16 V_TBLen_E2BakeUp1Addr;    /*�����и�����E2��1�����ݵ�ַ*/
	ushort16 V_Num_E2BakeUp1Addr;      /*������E2��1�����ݵ�ַ*/
	uchar8 V_Str_4aTableLen;           /*4�����ṹ���������ݳ���,��������4����ʱ������Ϊȫ��*/
}Str_3dEventTable;

const Str_3dEventTable Str_3d698EventTable_Flash[]=
{/*�к� Flash�׵�ַ                             Flashβҳ��ַ                           4a�����ṹ�������ַ                             �¼������б�     ��E2��1�����ݵ�ַ                    �����и�����E2��1�����ݵ�ַ                             ������E2��1�����ݵ�ַ                             4�����ṹ���������ݳ���,��������4����ʱ������Ϊȫ��*/
/*000*/{FlashStAddr_All_Loss_Vol,          FlashEndAddr_All_Loss_Vol,          (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_All_Loss_Vol_OADTab,              E2Addr_All_Loss_Vol_OADTabLen,              E2Addr_All_Loss_Vol_Degree,              Str_4aTable_AllLossVol_Len},
/*001*/{FlashStAddr_Aux_Pow_Down,          FlashEndAddr_Aux_Pow_Down,          (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_Aux_Pow_Down_OADTab,              E2Addr_Aux_Pow_Down_OADTabLen,              E2Addr_Aux_Pow_Down_Degree,              Str_4aTable_AllLossVol_Len},
/*002*/{FlashStAddr_Pow_Down,              FlashEndAddr_Pow_Down,              (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_Pow_Down_OADTab,                  E2Addr_Pow_Down_OADTabLen,                  E2Addr_Pow_Down_Degree,                  Str_4aTable_AllLossVol_Len},
/*003*/{FlashStAddr_Pos_Ac_De_Over,        FlashEndAddr_Pos_Ac_De_Over,        (ulong32)&Str_4aTable_De_Over[0],        E2Addr_Pos_Ac_De_Over_OADTab,            E2Addr_Pos_Ac_De_Over_OADTabLen,            E2Addr_Pos_Ac_De_Over_Degree,            Str_4aTable_De_Over_Len},
/*004*/{FlashStAddr_Rev_Ac_De_Over,        FlashEndAddr_Rev_Ac_De_Over,        (ulong32)&Str_4aTable_De_Over[0],        E2Addr_Rev_Ac_De_Over_OADTab,            E2Addr_Rev_Ac_De_Over_OADTabLen,            E2Addr_Rev_Ac_De_Over_Degree,            Str_4aTable_De_Over_Len},
/*005*/{FlashStAddr_Qua1_Re_De_Over,       FlashEndAddr_Qua1_Re_De_Over,       (ulong32)&Str_4aTable_Qua_De_Over[0],    E2Addr_Qua_Re_De_Over_OADTab,            E2Addr_Qua_Re_De_Over_OADTabLen,            E2Addr_Qua1_Re_De_Over_Degree,           Str_4aTable_Qua_De_Over_Len},
/*006*/{FlashStAddr_Qua2_Re_De_Over,       FlashEndAddr_Qua2_Re_De_Over,       (ulong32)&Str_4aTable_Qua_De_Over[0],    E2Addr_Qua_Re_De_Over_OADTab,            E2Addr_Qua_Re_De_Over_OADTabLen,            E2Addr_Qua2_Re_De_Over_Degree,           Str_4aTable_Qua_De_Over_Len},
/*007*/{FlashStAddr_Qua3_Re_De_Over,       FlashEndAddr_Qua3_Re_De_Over,       (ulong32)&Str_4aTable_Qua_De_Over[0],    E2Addr_Qua_Re_De_Over_OADTab,            E2Addr_Qua_Re_De_Over_OADTabLen,            E2Addr_Qua3_Re_De_Over_Degree,           Str_4aTable_Qua_De_Over_Len},
/*008*/{FlashStAddr_Qua4_Re_De_Over,       FlashEndAddr_Qua4_Re_De_Over,       (ulong32)&Str_4aTable_Qua_De_Over[0],    E2Addr_Qua_Re_De_Over_OADTab,            E2Addr_Qua_Re_De_Over_OADTabLen,            E2Addr_Qua4_Re_De_Over_Degree,           Str_4aTable_Qua_De_Over_Len},
/*009*/{FlashStAddr_LossA_Vol,             FlashEndAddr_LossA_Vol,             (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Loss_Vol_OADTab,                  E2Addr_Loss_Vol_OADTabLen,                  E2Addr_LossA_Vol_Degree,                 Str_4aTable_QuaReDeOver_Len},
/*010*/{FlashStAddr_LossB_Vol,             FlashEndAddr_LossB_Vol,             (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Loss_Vol_OADTab,                  E2Addr_Loss_Vol_OADTabLen,                  E2Addr_LossB_Vol_Degree,                 Str_4aTable_QuaReDeOver_Len},
/*011*/{FlashStAddr_LossC_Vol,             FlashEndAddr_LossC_Vol,             (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Loss_Vol_OADTab,                  E2Addr_Loss_Vol_OADTabLen,                  E2Addr_LossC_Vol_Degree,                 Str_4aTable_QuaReDeOver_Len},
/*012*/{FlashStAddr_LowA_Vol,              FlashEndAddr_LowA_Vol,              (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Low_Vol_OADTab,                   E2Addr_Low_Vol_OADTabLen,                   E2Addr_LowA_Vol_Degree,                  Str_4aTable_QuaReDeOver_Len},
/*013*/{FlashStAddr_LowB_Vol,              FlashEndAddr_LowB_Vol,              (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Low_Vol_OADTab,                   E2Addr_Low_Vol_OADTabLen,                   E2Addr_LowB_Vol_Degree,                  Str_4aTable_QuaReDeOver_Len},
/*014*/{FlashStAddr_LowC_Vol,              FlashEndAddr_LowC_Vol,              (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Low_Vol_OADTab,                   E2Addr_Low_Vol_OADTabLen,                   E2Addr_LowC_Vol_Degree,                  Str_4aTable_QuaReDeOver_Len},
/*015*/{FlashStAddr_OverA_Vol,             FlashEndAddr_OverA_Vol,             (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Over_Vol_OADTab,                  E2Addr_Over_Vol_OADTabLen,                  E2Addr_OverA_Vol_Degree,                 Str_4aTable_QuaReDeOver_Len},
/*016*/{FlashStAddr_OverB_Vol,             FlashEndAddr_OverB_Vol,             (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Over_Vol_OADTab,                  E2Addr_Over_Vol_OADTabLen,                  E2Addr_OverB_Vol_Degree,                 Str_4aTable_QuaReDeOver_Len},
/*017*/{FlashStAddr_OverC_Vol,             FlashEndAddr_OverC_Vol,             (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Over_Vol_OADTab,                  E2Addr_Over_Vol_OADTabLen,                  E2Addr_OverC_Vol_Degree,                 Str_4aTable_QuaReDeOver_Len},
/*018*/{FlashStAddr_BreakA_Vol,            FlashEndAddr_BreakA_Vol,            (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Break_Vol_OADTab,                 E2Addr_Break_Vol_OADTabLen,                 E2Addr_BreakA_Vol_Degree,                Str_4aTable_QuaReDeOver_Len},
/*019*/{FlashStAddr_BreakB_Vol,            FlashEndAddr_BreakB_Vol,            (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Break_Vol_OADTab,                 E2Addr_Break_Vol_OADTabLen,                 E2Addr_BreakB_Vol_Degree,                Str_4aTable_QuaReDeOver_Len},
/*020*/{FlashStAddr_BreakC_Vol,            FlashEndAddr_BreakC_Vol,            (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Break_Vol_OADTab,                 E2Addr_Break_Vol_OADTabLen,                 E2Addr_BreakC_Vol_Degree,                Str_4aTable_QuaReDeOver_Len},
/*021*/{FlashStAddr_RevPS_Vol,             FlashEndAddr_RevPS_Vol,             (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_RevPS_Vol_OADTab,                 E2Addr_RevPS_Vol_OADTabLen,                 E2Addr_RevPS_Vol_Degree,                 Str_4aTable_AllLossVol_Len},
/*022*/{FlashStAddr_RevPS_Curr,            FlashEndAddr_RevPS_Curr,            (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_RevPS_Curr_OADTab,                E2Addr_RevPS_Curr_OADTabLen,                E2Addr_RevPS_Curr_Degree,                Str_4aTable_AllLossVol_Len},
/*023*/{FlashStAddr_NoBal_Vol,             FlashEndAddr_NoBal_Vol,             (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_NoBal_Vol_OADTab,                 E2Addr_NoBal_Vol_OADTabLen,                 E2Addr_NoBal_Vol_Degree,                 Str_4aTable_AllLossVol_Len},
/*024*/{FlashStAddr_NoBal_Curr,            FlashEndAddr_NoBal_Curr,            (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_NoBal_Curr_OADTab,                E2Addr_NoBal_Curr_OADTabLen,                E2Addr_NoBal_Curr_Degree,                Str_4aTable_AllLossVol_Len},
/*025*/{FlashStAddr_SevNoBal_Curr,         FlashEndAddr_SevNoBal_Curr,         (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_SevNoBal_Curr_OADTab,             E2Addr_SevNoBal_Curr_OADTabLen,             E2Addr_SevNoBal_Curr_Degree,             Str_4aTable_AllLossVol_Len},
/*026*/{FlashStAddr_LossA_Curr,            FlashEndAddr_LossA_Curr,            (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Loss_Curr_OADTab,                 E2Addr_Loss_Curr_OADTabLen,                 E2Addr_LossA_Curr_Degree,                Str_4aTable_QuaReDeOver_Len},
/*027*/{FlashStAddr_LossB_Curr,            FlashEndAddr_LossB_Curr,            (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Loss_Curr_OADTab,                 E2Addr_Loss_Curr_OADTabLen,                 E2Addr_LossB_Curr_Degree,                Str_4aTable_QuaReDeOver_Len},
/*028*/{FlashStAddr_LossC_Curr,            FlashEndAddr_LossC_Curr,            (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Loss_Curr_OADTab,                 E2Addr_Loss_Curr_OADTabLen,                 E2Addr_LossC_Curr_Degree,                Str_4aTable_QuaReDeOver_Len},
/*029*/{FlashStAddr_OverA_Curr,            FlashEndAddr_OverA_Curr,            (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Over_Curr_OADTab,                 E2Addr_Over_Curr_OADTabLen,                 E2Addr_OverA_Curr_Degree,                Str_4aTable_QuaReDeOver_Len},
/*030*/{FlashStAddr_OverB_Curr,            FlashEndAddr_OverB_Curr,            (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Over_Curr_OADTab,                 E2Addr_Over_Curr_OADTabLen,                 E2Addr_OverB_Curr_Degree,                Str_4aTable_QuaReDeOver_Len},
/*031*/{FlashStAddr_OverC_Curr,            FlashEndAddr_OverC_Curr,            (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Over_Curr_OADTab,                 E2Addr_Over_Curr_OADTabLen,                 E2Addr_OverC_Curr_Degree,                Str_4aTable_QuaReDeOver_Len},
/*032*/{FlashStAddr_BreakA_Curr,           FlashEndAddr_BreakA_Curr,           (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Break_Curr_OADTab,                E2Addr_Break_Curr_OADTabLen,                E2Addr_BreakA_Curr_Degree,               Str_4aTable_QuaReDeOver_Len},
/*033*/{FlashStAddr_BreakB_Curr,           FlashEndAddr_BreakB_Curr,           (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Break_Curr_OADTab,                E2Addr_Break_Curr_OADTabLen,                E2Addr_BreakB_Curr_Degree,               Str_4aTable_QuaReDeOver_Len},
/*034*/{FlashStAddr_BreakC_Curr,           FlashEndAddr_BreakC_Curr,           (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Break_Curr_OADTab,                E2Addr_Break_Curr_OADTabLen,                E2Addr_BreakC_Curr_Degree,               Str_4aTable_QuaReDeOver_Len},
/*035*/{FlashStAddr_PowerA_Rev,            FlashEndAddr_PowerA_Rev,            (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Power_Rev_OADTab,                 E2Addr_Power_Rev_OADTabLen,                 E2Addr_PowerA_Rev_Degree,                Str_4aTable_QuaReDeOver_Len},
/*036*/{FlashStAddr_PowerB_Rev,            FlashEndAddr_PowerB_Rev,            (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Power_Rev_OADTab,                 E2Addr_Power_Rev_OADTabLen,                 E2Addr_PowerB_Rev_Degree,                Str_4aTable_QuaReDeOver_Len},
/*037*/{FlashStAddr_PowerC_Rev,            FlashEndAddr_PowerC_Rev,            (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Power_Rev_OADTab,                 E2Addr_Power_Rev_OADTabLen,                 E2Addr_PowerC_Rev_Degree,                Str_4aTable_QuaReDeOver_Len},
/*038*/{FlashStAddr_OverA_Lo,              FlashEndAddr_OverA_Lo,              (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Over_Lo_OADTab,                   E2Addr_Over_Lo_OADTabLen,                   E2Addr_OverA_Lo_Degree,                  Str_4aTable_QuaReDeOver_Len},
/*039*/{FlashStAddr_OverB_Lo,              FlashEndAddr_OverB_Lo,              (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Over_Lo_OADTab,                   E2Addr_Over_Lo_OADTabLen,                   E2Addr_OverB_Lo_Degree,                  Str_4aTable_QuaReDeOver_Len},
/*040*/{FlashStAddr_OverC_Lo,              FlashEndAddr_OverC_Lo,              (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Over_Lo_OADTab,                   E2Addr_Over_Lo_OADTabLen,                   E2Addr_OverC_Lo_Degree,                  Str_4aTable_QuaReDeOver_Len},
/*041*/{FlashStAddr_Tol_Clear,             FlashEndAddr_Tol_Clear,             (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_Tol_Clear_OADTab,                 E2Addr_Tol_Clear_OADTabLen,                 E2Addr_Tol_Clear_Degree,                 Str_4aTable_AllLossVol_Len},
/*042*/{FlashStAddr_De_Clear,              FlashEndAddr_De_Clear,              (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_De_Clear_OADTab,                  E2Addr_De_Clear_OADTabLen,                  E2Addr_De_Clear_Degree,                  Str_4aTable_AllLossVol_Len},
/*043*/{FlashStAddr_Even_Clear,            FlashEndAddr_Even_Clear,            (ulong32)&Str_4aTable_Even_Clear[0],     E2Addr_Even_Clear_OADTab,                E2Addr_Even_Clear_OADTabLen,                E2Addr_Even_Clear_Degree,                Str_4aTable_Even_Clear_Len},
/*044*/{FlashStAddr_Program,               FlashEndAddr_Program,               (ulong32)&Str_4aTable_Prog[0],           E2Addr_Program_OADTab,                   E2Addr_Program_OADTabLen,                   E2Addr_Program_Degree,                   Str_4aTable_Prog_Len},
/*045*/{FlashStAddr_AbnorC,                FlashEndAddr_AbnorC,                (ulong32)&Str_4aTable_AbnorC[0],         E2Addr_AbnorC_OADTab,                    E2Addr_AbnorC_OADTabLen,                    E2Addr_AbnorC_Degree,                    Str_4aTable_AbnorC_Len},
/*046*/{FlashStAddr_OpenW,                 FlashEndAddr_OpenW,                 (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_OpenW_OADTab,                     E2Addr_OpenW_OADTabLen,                     E2Addr_OpenW_Degree,                     Str_4aTable_AllLossVol_Len},
/*047*/{FlashStAddr_OpenCW,                FlashEndAddr_OpenCW,                (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_OpenCW_OADTab,                    E2Addr_OpenCW_OADTabLen,                    E2Addr_OpenCW_Degree,                    Str_4aTable_AllLossVol_Len},
/*048*/{FlashStAddr_BuyCurr,               FlashEndAddr_BuyCurr,               (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_BuyCurr_OADTab,                   E2Addr_BuyCurr_OADTabLen,                   E2Addr_BuyCurr_Degree,                   Str_4aTable_AllLossVol_Len},
/*049*/{FlashStAddr_Return_M,              FlashEndAddr_Return_M,              (ulong32)&Str_4aTable_Return_M[0],       E2Addr_Return_M_OADTab,                  E2Addr_Return_M_OADTabLen,                  E2Addr_Return_M_Degree,                  Str_4aTable_Return_M_Len},
/*050*/{FlashStAddr_ConM,                  FlashEndAddr_ConM,                  (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_ConM_OADTab,                      E2Addr_ConM_OADTabLen,                      E2Addr_ConM_Degree,                      Str_4aTable_AllLossVol_Len},
/*051*/{FlashStAddr_RelayFa,               FlashEndAddr_RelayFa,               (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_RelayFa_OADTab,                   E2Addr_RelayFa_OADTabLen,                   E2Addr_RelayFa_Degree,                   Str_4aTable_AllLossVol_Len},
/*052*/{FlashStAddr_PowerFa,               FlashEndAddr_PowerFa,               (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_PowerFa_OADTab,                   E2Addr_PowerFa_OADTabLen,                   E2Addr_PowerFa_Degree,                   Str_4aTable_AllLossVol_Len},
/*053*/{FlashStAddr_RelayOpen,             FlashEndAddr_RelayOpen,             (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_RelayOpen_OADTab,                 E2Addr_RelayOpen_OADTabLen,                 E2Addr_RelayOpen_Degree,                 Str_4aTable_AllLossVol_Len},
/*054*/{FlashStAddr_RelayClose,            FlashEndAddr_RelayClose,            (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_RelayClose_OADTab,                E2Addr_RelayClose_OADTabLen,                E2Addr_RelayClose_Degree,                Str_4aTable_AllLossVol_Len},
#if 0
/*000*/{FlashStAddr_Trend_Rev,             FlashEndAddr_Trend_Rev,             (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Power_Rev_OADTab,                 E2Addr_Power_Rev_OADTabLen,                 E2Addr_Trend_Rev_Degree,                 Str_4aTable_QuaReDeOver_Len},
#endif
/*055*/{FlashStAddr_PFactorT_Over,         FlashEndAddr_PFactorT_Over,         (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_PFactorT_Over_OADTab,             E2Addr_PFactorT_Over_OADTabLen,             E2Addr_PFactorT_Over_Degree,             Str_4aTable_QuaReDeOver_Len},
/*056*/{FlashStAddr_AdjTime,               FlashEndAddr_AdjTime,               (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_AdjTime_OADTab,                   E2Addr_AdjTime_OADTabLen,                   E2Addr_AdjTime_Degree,                   Str_4aTable_AllLossVol_Len},
/*057*/{FlashStAddr_ProgPT,                FlashEndAddr_ProgPT,                (ulong32)&Str_4aTable_ProgPT[0],         E2Addr_ProgPT_OADTab,                    E2Addr_ProgPT_OADTabLen,                    E2Addr_ProgPT_Degree,                    Str_4aTable_ProgPT_Len},
/*058*/{FlashStAddr_ProgTZ,                FlashEndAddr_ProgTZ,                (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_ProgTZ_OADTab,                    E2Addr_ProgTZ_OADTabLen,                    E2Addr_ProgTZ_Degree,                    Str_4aTable_AllLossVol_Len},
/*059*/{FlashStAddr_ProgWRe,               FlashEndAddr_ProgWRe,               (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_ProgWRe_OADTab,                   E2Addr_ProgWRe_OADTabLen,                   E2Addr_ProgWRe_Degree,                   Str_4aTable_AllLossVol_Len},
/*060*/{FlashStAddr_ProgHol,               FlashEndAddr_ProgHol,               (ulong32)&Str_4aTable_ProgHol[0],        E2Addr_ProgHol_OADTab,                   E2Addr_ProgHol_OADTabLen,                   E2Addr_ProgHol_Degree,                   Str_4aTable_ProgHol_Len},
/*061*/{FlashStAddr_ProgAcC,               FlashEndAddr_ProgAcC,               (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_ProgAcC_OADTab,                   E2Addr_ProgAcC_OADTabLen,                   E2Addr_ProgAcC_Degree,                   Str_4aTable_AllLossVol_Len},
/*062*/{FlashStAddr_ProgReC1,              FlashEndAddr_ProgReC1,              (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_ProgReC_OADTab,                   E2Addr_ProgReC_OADTabLen,                   E2Addr_ProgReC1_Degree,                  Str_4aTable_AllLossVol_Len},
/*063*/{FlashStAddr_ProgSettD,             FlashEndAddr_ProgSettD,             (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_ProgSettD_OADTab,                 E2Addr_ProgSettD_OADTabLen,                 E2Addr_ProgSettD_Degree,                 Str_4aTable_AllLossVol_Len},
/*064*/{FlashStAddr_ProgTPara,             FlashEndAddr_ProgTPara,             (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_ProgTPara_OADTab,                 E2Addr_ProgTPara_OADTabLen,                 E2Addr_ProgTPara_Degree,                 Str_4aTable_AllLossVol_Len},
/*065*/{FlashStAddr_ProgLad,               FlashEndAddr_ProgLad,               (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_ProgLad_OADTab,                   E2Addr_ProgLad_OADTabLen,                   E2Addr_ProgLad_Degree,                   Str_4aTable_AllLossVol_Len},
/*066*/{FlashStAddr_ProgKD,                FlashEndAddr_ProgKD,                (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_ProgKD_OADTab,                    E2Addr_ProgKD_OADTabLen,                    E2Addr_ProgKD_Degree,                    Str_4aTable_AllLossVol_Len},
/*067*/{FlashStAddr_MeterFa,               FlashEndAddr_MeterFa,               (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_MeterFa_OADTab,                   E2Addr_MeterFa_OADTabLen,                   E2Addr_MeterFa_Degree,                   Str_4aTable_AllLossVol_Len},
/*068*/{FlashStAddr_ClockFa,               FlashEndAddr_ClockFa,               (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_ClockFa_OADTab,                   E2Addr_ClockFa_OADTabLen,                   E2Addr_ClockFa_Degree,                   Str_4aTable_AllLossVol_Len},
/*069*/{FlashStAddr_BroadcastTime,         FlashEndAddr_BroadcastTime,         (ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_BroadcastTime_OADTab,             E2Addr_BroadcastTime_OADTabLen,             E2Addr_BroadcastTime_Degree,             Str_4aTable_AllLossVol_Len},
/*070*/{FlashStAddr_PowerT_Rev,            FlashEndAddr_PowerT_Rev,            (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_Power_Rev_OADTab,                 E2Addr_Power_Rev_OADTabLen,                 E2Addr_PowerT_Rev_Degree,                Str_4aTable_QuaReDeOver_Len},
/*071*/{FlashStAddr_NeutralCurrentAbnormal,FlashEndAddr_NeutralCurrentAbnormal,(ulong32)&Str_4aTable_AllLossVol[0],     E2Addr_NeutralCurrentAbnormal_OADTab,    E2Addr_NeutralCurrentAbnormal_OADTabLen,    E2Addr_NeutralCurrentAbnormal_Degree,    Str_4aTable_AllLossVol_Len},
/*072*/{FlashStAddr_PFactorA_Over,         FlashEndAddr_PFactorA_Over,         (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_PFactorT_Over_OADTab,             E2Addr_PFactorT_Over_OADTabLen,             E2Addr_PFactorA_Over_Degree,             Str_4aTable_QuaReDeOver_Len},
/*073*/{FlashStAddr_PFactorB_Over,         FlashEndAddr_PFactorB_Over,         (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_PFactorT_Over_OADTab,             E2Addr_PFactorT_Over_OADTabLen,             E2Addr_PFactorB_Over_Degree,             Str_4aTable_QuaReDeOver_Len},
/*074*/{FlashStAddr_PFactorC_Over,         FlashEndAddr_PFactorC_Over,         (ulong32)&Str_4aTable_QuaReDeOver[0],    E2Addr_PFactorT_Over_OADTab,             E2Addr_PFactorT_Over_OADTabLen,             E2Addr_PFactorC_Over_Degree,             Str_4aTable_QuaReDeOver_Len},
};
#define Str_3dTable_Flash_Len  (sizeof(Str_3d698EventTable_Flash)/sizeof(Str_3dEventTable))

#define C_698FixTimeFreeze 4        /*ֻ���꣨���Ϊ���ݽ��㶳�ᣩ���¡��ա�ʱ���ָ��ǣ�ע���±�˳�������ݲ㸲�ǳ����Ӧ*/
const Str_698FreezeAddrTable Str_698FreezeDataTable[]=
{
	/************��������****************/
	/*	Flash�׵�ַ					Flashβ��ַ	����OAD����(����)���к�	������ű��к�	E2��ʼ��ַ						E2������ַ								����DI2*/
	{FlashStAddr_T_Free,		FlashEndAddr_T_Free,		222,	234,	E2Addr_Min_Free_Flash_Ear,		E2Addr_Min_Free_Flash_Late,		(uchar8)((C_RelatedOAD_Min&Get_DI2},
	{FlashStAddr_H_Free,		FlashEndAddr_H_Free,		223,	235,	E2Addr_H_Free_Flash_Ear,		E2Addr_H_Free_Flash_Late,		(uchar8)((C_RelatedOAD_Hour&Get_DI2},
	{FlashStAddr_D_Free,		FlashEndAddr_D_Free,		224,	236,	E2Addr_D_Free_Flash_Ear,		E2Addr_D_Free_Flash_Late,		(uchar8)((C_RelatedOAD_Day&Get_DI2},
	{FlashStAddr_M_Free,		FlashEndAddr_M_Free,		226,	238,	E2Addr_M_Free_Flash_Ear,		E2Addr_M_Free_Flash_Late,		(uchar8)((C_RelatedOAD_Month&Get_DI2},
	{FlashStAddr_Y_Free,		FlashEndAddr_Y_Free,		227,	239,	E2Addr_Y_Free_Flash_Ear,		E2Addr_Y_Free_Flash_Late,		(uchar8)((C_RelatedOAD_YSettle&Get_DI2},/*����Ϊ���ݽ��㶳��*/
	{FlashStAddr_I_Free,		FlashEndAddr_I_Free,		221,	233,	E2Addr_I_Free_Flash_Ear,		E2Addr_I_Free_Flash_Late,		(uchar8)((C_RelatedOAD_Immid&Get_DI2},
	{FlashStAddr_TZ_Free,		FlashEndAddr_TZ_Free,		228,	240,	E2Addr_TZ_Free_Flash_Ear,		E2Addr_TZ_Free_Flash_Late,		(uchar8)((C_RelatedOAD_TimeZone&Get_DI2},
	{FlashStAddr_PT_Free,		FlashEndAddr_PT_Free,		229,	241,	E2Addr_PT_Free_Flash_Ear,		E2Addr_PT_Free_Flash_Late,		(uchar8)((C_RelatedOAD_TimeRegion&Get_DI2},
	{FlashStAddr_R_Free,		FlashEndAddr_R_Free,		230,	242,	E2Addr_R_Free_Flash_Ear,		E2Addr_R_Free_Flash_Late,		(uchar8)((C_RelatedOAD_RateTalbe&Get_DI2},
	{FlashStAddr_L_Free,		FlashEndAddr_L_Free,		231,	243,	E2Addr_L_Free_Flash_Ear,		E2Addr_L_Free_Flash_Late,		(uchar8)((C_RelatedOAD_StepTable&Get_DI2},
	{FlashStAddr_Sett_Free,		FlashEndAddr_Sett_Free,		225,	237,	E2Addr_Sett_Freeze_Flash_Ear,	E2Addr_Sett_Freeze_Flash_Late,	(uchar8)((C_RelatedOAD_Settle&Get_DI2},
};
#define Str_698FreezeDataTable_Len  (sizeof(Str_698FreezeDataTable)/sizeof(Str_698FreezeAddrTable))

const Str_4Table Str_4Table_ProgPT[]=          /************ʱ�α����¼���¼********/
{
	/************ʱ�α����¼���¼********֡���ȿ���Ҫ����*******/
/*ushort16�ñ�ʶ���Ӧ������ƫ�Ƶ�ַ                         uchar8��������ƫ�Ƶ�ַ��1�����ݱ�ʾ*/
	{(0),                                                     (uchar8)((CProgPT_NoteC_1    &Get_DI0},
	{(CLProgPT_NoteC_1),                                      (uchar8)((CProgPT_NoteD_1    &Get_DI0},
	{(CLProgPT_NoteC_1+CLProgPT_NoteD_1),                     (uchar8)((CProgPT_NoteE_1    &Get_DI0},
	{(CLProgPT_NoteC_1+CLProgPT_NoteD_1+CLProgPT_NoteE_1),    (uchar8)((CProgPT_NoteF_1    &Get_DI0},

};
#define Str_4Table_ProgPT_Len  (sizeof(Str_4Table_ProgPT)/sizeof(Str_4Table))

const Str_4Table Str_4Table_Rec_Meter[]=          /**********У���¼********/
{
	/************У���¼���¼********/
/*ushort16�ñ�ʶ���Ӧ������ƫ�Ƶ�ַ         uchar8��������ƫ�Ƶ�ַ��1�����ݱ�ʾ*/
	{(0),    (uchar8)((CRec_Meter_Hp_T_1           &Get_DI1},
	{(6),    (uchar8)((CRec_Meter_Bef1_Data_254    &Get_DI1},
};
#define Str_4Table_Rec_Meter_Len  (sizeof(Str_4Table_Rec_Meter)/sizeof(Str_4Table))

const Str_3aTable Str_3aTable_E23RAM[]=
{/*�к�      ���ݴ��E2��1����ַ                          ���ݴ��RAM��ַ*/
/*000*/{E2Addr_Pos_Ac_T1_En_Pul_0,           &GV_CurrEnergyData[0][0],             C_CurrDataLen5,           1},
/*001*/{E2Addr_Pos_Ac_T2_En_Pul_0,           &GV_CurrEnergyData[1][0],             C_CurrDataLen5,           1},
/*002*/{E2Addr_Pos_Ac_T3_En_Pul_0,           &GV_CurrEnergyData[2][0],             C_CurrDataLen5,           1},
/*003*/{E2Addr_Pos_Ac_T4_En_Pul_0,           &GV_CurrEnergyData[3][0],             C_CurrDataLen5,           1},
/*004*/{E2Addr_Pos_Ac_T5_En_Pul_0,           &GV_CurrEnergyData[4][0],             C_CurrDataLen5,           1},
/*005*/{E2Addr_Pos_Ac_T6_En_Pul_0,           &GV_CurrEnergyData[5][0],             C_CurrDataLen5,           1},
/*006*/{E2Addr_Pos_Ac_T7_En_Pul_0,           &GV_CurrEnergyData[6][0],             C_CurrDataLen5,           1},
/*007*/{E2Addr_Pos_Ac_T8_En_Pul_0,           &GV_CurrEnergyData[7][0],             C_CurrDataLen5,           1},
/*008*/{E2Addr_Pos_Ac_T9_En_Pul_0,           &GV_CurrEnergyData[8][0],             C_CurrDataLen5,           1},
/*009*/{E2Addr_Pos_Ac_T10_En_Pul_0,          &GV_CurrEnergyData[9][0],             C_CurrDataLen5,           1},
/*010*/{E2Addr_Pos_Ac_T11_En_Pul_0,          &GV_CurrEnergyData[10][0],            C_CurrDataLen5,           1},
/*011*/{E2Addr_Pos_Ac_T12_En_Pul_0,          &GV_CurrEnergyData[11][0],            C_CurrDataLen5,           1},

/*012*/{E2Addr_Rev_Ac_T1_En_Pul_0,           &GV_CurrEnergyData[12][0],            C_CurrDataLen5,           1},
/*013*/{E2Addr_Rev_Ac_T2_En_Pul_0,           &GV_CurrEnergyData[13][0],            C_CurrDataLen5,           1},
/*014*/{E2Addr_Rev_Ac_T3_En_Pul_0,           &GV_CurrEnergyData[14][0],            C_CurrDataLen5,           1},
/*015*/{E2Addr_Rev_Ac_T4_En_Pul_0,           &GV_CurrEnergyData[15][0],            C_CurrDataLen5,           1},
/*016*/{E2Addr_Rev_Ac_T5_En_Pul_0,           &GV_CurrEnergyData[16][0],            C_CurrDataLen5,           1},
/*017*/{E2Addr_Rev_Ac_T6_En_Pul_0,           &GV_CurrEnergyData[17][0],            C_CurrDataLen5,           1},
/*018*/{E2Addr_Rev_Ac_T7_En_Pul_0,           &GV_CurrEnergyData[18][0],            C_CurrDataLen5,           1},
/*019*/{E2Addr_Rev_Ac_T8_En_Pul_0,           &GV_CurrEnergyData[19][0],            C_CurrDataLen5,           1},
/*020*/{E2Addr_Rev_Ac_T9_En_Pul_0,           &GV_CurrEnergyData[20][0],            C_CurrDataLen5,           1},
/*021*/{E2Addr_Rev_Ac_T10_En_Pul_0,          &GV_CurrEnergyData[21][0],            C_CurrDataLen5,           1},
/*022*/{E2Addr_Rev_Ac_T11_En_Pul_0,          &GV_CurrEnergyData[22][0],            C_CurrDataLen5,           1},
/*023*/{E2Addr_Rev_Ac_T12_En_Pul_0,          &GV_CurrEnergyData[23][0],            C_CurrDataLen5,           1},

/*024*/{E2Addr_Qua1_Re_T1_En_Pul_0,          &GV_CurrEnergyData[24][0],            C_CurrDataLen5,           1},
/*025*/{E2Addr_Qua1_Re_T2_En_Pul_0,          &GV_CurrEnergyData[25][0],            C_CurrDataLen5,           1},
/*026*/{E2Addr_Qua1_Re_T3_En_Pul_0,          &GV_CurrEnergyData[26][0],            C_CurrDataLen5,           1},
/*027*/{E2Addr_Qua1_Re_T4_En_Pul_0,          &GV_CurrEnergyData[27][0],            C_CurrDataLen5,           1},
/*028*/{E2Addr_Qua1_Re_T5_En_Pul_0,          &GV_CurrEnergyData[28][0],            C_CurrDataLen5,           1},
/*029*/{E2Addr_Qua1_Re_T6_En_Pul_0,          &GV_CurrEnergyData[29][0],            C_CurrDataLen5,           1},
/*030*/{E2Addr_Qua1_Re_T7_En_Pul_0,          &GV_CurrEnergyData[30][0],            C_CurrDataLen5,           1},
/*031*/{E2Addr_Qua1_Re_T8_En_Pul_0,          &GV_CurrEnergyData[31][0],            C_CurrDataLen5,           1},
/*032*/{E2Addr_Qua1_Re_T9_En_Pul_0,          &GV_CurrEnergyData[32][0],            C_CurrDataLen5,           1},
/*033*/{E2Addr_Qua1_Re_T10_En_Pul_0,         &GV_CurrEnergyData[33][0],            C_CurrDataLen5,           1},
/*034*/{E2Addr_Qua1_Re_T11_En_Pul_0,         &GV_CurrEnergyData[34][0],            C_CurrDataLen5,           1},
/*035*/{E2Addr_Qua1_Re_T12_En_Pul_0,         &GV_CurrEnergyData[35][0],            C_CurrDataLen5,           1},

/*036*/{E2Addr_Qua2_Re_T1_En_Pul_0,          &GV_CurrEnergyData[36][0],            C_CurrDataLen5,           1},
/*037*/{E2Addr_Qua2_Re_T2_En_Pul_0,          &GV_CurrEnergyData[37][0],            C_CurrDataLen5,           1},
/*038*/{E2Addr_Qua2_Re_T3_En_Pul_0,          &GV_CurrEnergyData[38][0],            C_CurrDataLen5,           1},
/*039*/{E2Addr_Qua2_Re_T4_En_Pul_0,          &GV_CurrEnergyData[39][0],            C_CurrDataLen5,           1},
/*040*/{E2Addr_Qua2_Re_T5_En_Pul_0,          &GV_CurrEnergyData[40][0],            C_CurrDataLen5,           1},
/*041*/{E2Addr_Qua2_Re_T6_En_Pul_0,          &GV_CurrEnergyData[41][0],            C_CurrDataLen5,           1},
/*042*/{E2Addr_Qua2_Re_T7_En_Pul_0,          &GV_CurrEnergyData[42][0],            C_CurrDataLen5,           1},
/*043*/{E2Addr_Qua2_Re_T8_En_Pul_0,          &GV_CurrEnergyData[43][0],            C_CurrDataLen5,           1},
/*044*/{E2Addr_Qua2_Re_T9_En_Pul_0,          &GV_CurrEnergyData[44][0],            C_CurrDataLen5,           1},
/*045*/{E2Addr_Qua2_Re_T10_En_Pul_0,         &GV_CurrEnergyData[45][0],            C_CurrDataLen5,           1},
/*046*/{E2Addr_Qua2_Re_T11_En_Pul_0,         &GV_CurrEnergyData[46][0],            C_CurrDataLen5,           1},
/*047*/{E2Addr_Qua2_Re_T12_En_Pul_0,         &GV_CurrEnergyData[47][0],            C_CurrDataLen5,           1},

/*048*/{E2Addr_Qua3_Re_T1_En_Pul_0,          &GV_CurrEnergyData[48][0],            C_CurrDataLen5,           1},
/*049*/{E2Addr_Qua3_Re_T2_En_Pul_0,          &GV_CurrEnergyData[49][0],            C_CurrDataLen5,           1},
/*050*/{E2Addr_Qua3_Re_T3_En_Pul_0,          &GV_CurrEnergyData[50][0],            C_CurrDataLen5,           1},
/*051*/{E2Addr_Qua3_Re_T4_En_Pul_0,          &GV_CurrEnergyData[51][0],            C_CurrDataLen5,           1},
/*052*/{E2Addr_Qua3_Re_T5_En_Pul_0,          &GV_CurrEnergyData[52][0],            C_CurrDataLen5,           1},
/*053*/{E2Addr_Qua3_Re_T6_En_Pul_0,          &GV_CurrEnergyData[53][0],            C_CurrDataLen5,           1},
/*054*/{E2Addr_Qua3_Re_T7_En_Pul_0,          &GV_CurrEnergyData[54][0],            C_CurrDataLen5,           1},
/*055*/{E2Addr_Qua3_Re_T8_En_Pul_0,          &GV_CurrEnergyData[55][0],            C_CurrDataLen5,           1},
/*056*/{E2Addr_Qua3_Re_T9_En_Pul_0,          &GV_CurrEnergyData[56][0],            C_CurrDataLen5,           1},
/*057*/{E2Addr_Qua3_Re_T10_En_Pul_0,         &GV_CurrEnergyData[57][0],            C_CurrDataLen5,           1},
/*058*/{E2Addr_Qua3_Re_T11_En_Pul_0,         &GV_CurrEnergyData[58][0],            C_CurrDataLen5,           1},
/*059*/{E2Addr_Qua3_Re_T12_En_Pul_0,         &GV_CurrEnergyData[59][0],            C_CurrDataLen5,           1},

/*060*/{E2Addr_Qua4_Re_T1_En_Pul_0,          &GV_CurrEnergyData[60][0],            C_CurrDataLen5,           1},
/*061*/{E2Addr_Qua4_Re_T2_En_Pul_0,          &GV_CurrEnergyData[61][0],            C_CurrDataLen5,           1},
/*062*/{E2Addr_Qua4_Re_T3_En_Pul_0,          &GV_CurrEnergyData[62][0],            C_CurrDataLen5,           1},
/*063*/{E2Addr_Qua4_Re_T4_En_Pul_0,          &GV_CurrEnergyData[63][0],            C_CurrDataLen5,           1},
/*064*/{E2Addr_Qua4_Re_T5_En_Pul_0,          &GV_CurrEnergyData[64][0],            C_CurrDataLen5,           1},
/*065*/{E2Addr_Qua4_Re_T6_En_Pul_0,          &GV_CurrEnergyData[65][0],            C_CurrDataLen5,           1},
/*066*/{E2Addr_Qua4_Re_T7_En_Pul_0,          &GV_CurrEnergyData[66][0],            C_CurrDataLen5,           1},
/*067*/{E2Addr_Qua4_Re_T8_En_Pul_0,          &GV_CurrEnergyData[67][0],            C_CurrDataLen5,           1},
/*068*/{E2Addr_Qua4_Re_T9_En_Pul_0,          &GV_CurrEnergyData[68][0],            C_CurrDataLen5,           1},
/*069*/{E2Addr_Qua4_Re_T10_En_Pul_0,         &GV_CurrEnergyData[69][0],            C_CurrDataLen5,           1},
/*070*/{E2Addr_Qua4_Re_T11_En_Pul_0,         &GV_CurrEnergyData[70][0],            C_CurrDataLen5,           1},
/*071*/{E2Addr_Qua4_Re_T12_En_Pul_0,         &GV_CurrEnergyData[71][0],            C_CurrDataLen5,           1},

/*072*/{E2Addr_PosA_Ac_En_Pul_0,             &GV_CurrEnergyData[72][0],            C_CurrDataLen5,           1},
/*073*/{E2Addr_RevA_Ac_En_Pul_0,             &GV_CurrEnergyData[73][0],            C_CurrDataLen5,           1},
/*074*/{E2Addr_Qua1A_Re_En_Pul_0,            &GV_CurrEnergyData[74][0],            C_CurrDataLen5,           1},
/*075*/{E2Addr_Qua2A_Re_En_Pul_0,            &GV_CurrEnergyData[75][0],            C_CurrDataLen5,           1},
/*076*/{E2Addr_Qua3A_Re_En_Pul_0,            &GV_CurrEnergyData[76][0],            C_CurrDataLen5,           1},
/*077*/{E2Addr_Qua4A_Re_En_Pul_0,            &GV_CurrEnergyData[77][0],            C_CurrDataLen5,           1},

/*078*/{E2Addr_PosB_Ac_En_Pul_0,             &GV_CurrEnergyData[78][0],            C_CurrDataLen5,           1},
/*079*/{E2Addr_RevB_Ac_En_Pul_0,             &GV_CurrEnergyData[79][0],            C_CurrDataLen5,           1},
/*080*/{E2Addr_Qua1B_Re_En_Pul_0,            &GV_CurrEnergyData[80][0],            C_CurrDataLen5,           1},
/*081*/{E2Addr_Qua2B_Re_En_Pul_0,            &GV_CurrEnergyData[81][0],            C_CurrDataLen5,           1},
/*082*/{E2Addr_Qua3B_Re_En_Pul_0,            &GV_CurrEnergyData[82][0],            C_CurrDataLen5,           1},
/*083*/{E2Addr_Qua4B_Re_En_Pul_0,            &GV_CurrEnergyData[83][0],            C_CurrDataLen5,           1},

/*084*/{E2Addr_PosC_Ac_En_Pul_0,             &GV_CurrEnergyData[84][0],            C_CurrDataLen5,           1},
/*085*/{E2Addr_RevC_Ac_En_Pul_0,             &GV_CurrEnergyData[85][0],            C_CurrDataLen5,           1},
/*086*/{E2Addr_Qua1C_Re_En_Pul_0,            &GV_CurrEnergyData[86][0],            C_CurrDataLen5,           1},
/*087*/{E2Addr_Qua2C_Re_En_Pul_0,            &GV_CurrEnergyData[87][0],            C_CurrDataLen5,           1},
/*088*/{E2Addr_Qua3C_Re_En_Pul_0,            &GV_CurrEnergyData[88][0],            C_CurrDataLen5,           1},
/*089*/{E2Addr_Qua4C_Re_En_Pul_0,            &GV_CurrEnergyData[89][0],            C_CurrDataLen5,           1},

/*090*/{E2Addr_SC_Com_Ac_Tol_En_Pul_0,       &GV_CurrEnergyData[90][0],            C_CurrDataLen5,           1},
/*091*/{E2Addr_M_Com_Ac_Tol_En_Pul_0,        &GV_CurrEnergyData[91][0],            C_CurrDataLen5,           1},
/*092*/{E2Addr_Y_Com_Ac_Tol_En_Pul_0,        &GV_CurrEnergyData[92][0],            C_CurrDataLen5,           1},
/*093*/{E2Addr_ChargeBal_Hex_Deal,           &GV_CurrEnergyData[93][0],            C_CurrDataLen5,           1},
/*094*/{E2Addr_OverDraft_Hex_Deal,           &GV_CurrEnergyData[94][0],            C_CurrDataLen5,           1},

/*095*/{E2Addr_BroadcastTimeOffset_Min,      &GV_BroadcastTimeOffset_Min[0],       CLBroadcastTimeOffset_Min,      1},
/*096*/{E2Addr_BroadcastTimeOffset_Max,      &GV_BroadcastTimeOffset_Max[0],       CLBroadcastTimeOffset_Max,      1},

/*097*/{E2Addr_Demand_Cycle,                 &GV_Demand_Cycle[0],                  CLDemand_Cycle,                 1},
/*098*/{E2Addr_Sliding_Time,                 &GV_Sliding_Time[0],                  CLSliding_Time,                 1},

/*099*/{E2Addr_Change_TZ_Time,               &GV_Change_TZ_Time[0],                CLChange_TZ_Time,               1},
/*100*/{E2Addr_Change_PT_Time,               &GV_Change_PT_Time[0],                CLChange_PT_Time,               1},
/*101*/{E2Addr_Change_Rate,                  &GV_Change_Rate[0],                   CLChange_Rate,                  1},
/*102*/{E2Addr_Change_Ladder,                &GV_Change_Ladder[0],                 CLChange_Ladder,                1},

/*103*/{E2Addr_Year_Zone_Num,                &GV_Year_Zone_Num[0],                 CLYear_Zone_Num,                1},
/*104*/{E2Addr_Day_Table_Num,                &GV_Day_Table_Num[0],                 CLDay_Table_Num,                1},
/*105*/{E2Addr_Day_Time_Num,                 &GV_Day_Time_Num[0],                  CLDay_Time_Num,                 1},
/*106*/{E2Addr_Rate_Num,                     &GV_Rate_Num[0],                      CLRate_Num,                     1},
/*107*/{E2Addr_Holiday_Num,                  &GV_Holiday_Num[0],                   CLHoliday_Num,                  1},
/*108*/{E2Addr_Step_Num,                     &GV_Step_Num[0],                      CLStep_Num,                     1},

/*109*/{E2Addr_Per_Dis_Screen_Time,          &GV_Per_Dis_Screen_Time[0],           CLPer_Dis_Screen_Time,          1},
/*110*/{E2Addr_Auto_Dis_Screen_Num,          &GV_Auto_Dis_Screen_Num[0],           CLAuto_Dis_Screen_Num,          1},
/*111*/{E2Addr_Auto_Dis_Screen_MaxNum,       &GV_Auto_Dis_Screen_MaxNum[0],        CLAuto_Dis_Screen_MaxNum,       1},

/*112*/{E2Addr_Perkey_Dis_Screen_Time,       &GV_Perkey_Dis_Screen_Time[0],        CLPerkey_Dis_Screen_Time,       1},
/*113*/{E2Addr_Key_CycDis_Screen_Num,        &GV_Key_CycDis_Screen_Num[0],         CLKey_CycDis_Screen_Num,        1},
/*114*/{E2Addr_Key_CycDis_Screen_MaxNum,     &GV_Key_CycDis_Screen_MaxNum[0],      CLKey_CycDis_Screen_MaxNum,     1},

/*115*/{E2Addr_PowerOn_Dis_All_Time,         &GV_PowerOn_Dis_All_Time[0],          CLPowerOn_Dis_All_Time,         1},
/*116*/{E2Addr_BacklightTime,                &GV_BacklightTime[0],                 CLBacklightTime,                1},
/*117*/{E2Addr_SViewBacklightTime,           &GV_SViewBacklightTime[0],            CLSViewBacklightTime,           1},
/*118*/{E2Addr_NEScreenDisplay,              &GV_NEScreenDisplay[0],               CLNEScreenDisplay,              1},
/*119*/{E2Addr_Energy_Decimal_Num,           &GV_Energy_Decimal_Num[0],            CLEnergy_Decimal_Num,           1},
/*120*/{E2Addr_Power_Decimal_Num,            &GV_Power_Decimal_Num[0],             CLPower_Decimal_Num,            1},
/*121*/{E2Addr_1And2Display,                 &GV_1And2Display[0],                  CL1And2Display,                 1},

/*122*/{E2Addr_Ratio_Curr_Tran,              &GV_Ratio_Curr_Tran[0],               CLRatio_Curr_Tran,              1},
/*123*/{E2Addr_Ratio_Vol_Tran,               &GV_Ratio_Vol_Tran[0],                CLRatio_Vol_Tran,               1},

/*124*/{E2Addr_Active_Com_State,             &GV_Active_Com_State[0][0],           CLActive_Com_State,             1},
/*125*/{E2Addr_Reactive_Com_State1,          &GV_Active_Com_State[1][0],           CLReactive_Com_State1,          1},
/*126*/{E2Addr_Reactive_Com_State2,          &GV_Active_Com_State[2][0],           CLReactive_Com_State2,          1},

/*127*/{E2Addr_Mod_InFr_Baud,                &GV_Mod_InFr_Baud[0],                 CLMod_InFr_Baud,                1},
/*128*/{E2Addr_One485_Baud  ,                &GV_One485_Baud[0],                   CLOne485_Baud,                  1},
/*129*/{E2Addr_Two485_Baud  ,                &GV_Two485_Baud[0],                   CLTwo485_Baud,                  1},
/*130*/{E2Addr_Modular_Baud ,                &GV_Modular_Baud[0],                  CLModular_Baud,                 1},

/*131*/{E2Addr_Week_RestDay ,                &GV_Week_RestDay[0][0],               CLWeek_RestDay,                 1},
/*132*/{E2Addr_Week_RestDay_DTable,          &GV_Week_RestDay[1][0],               CLWeek_RestDay_DTable,          1},

/*133*/{E2Addr_Alam1_Money,                  &GV_Alam1_Money[0][0],                CLAlam1_Money,                  2},
/*134*/{E2Addr_OverDraft_Money,              &GV_Alam1_Money[2][0],                CLOverDraft_Money,              3},

/*135*/{E2Addr_Comm_Address,                 &GV_Comm_Address[0],                  CLComm_Address,                 1},

/*136*/{E2Addr_Relay_Open_CurrTreshold,      &GV_Relay_Open_CurrTreshold[0],       CLRelay_Open_CurrTreshold,      1},

/*137*/{E2Addr_Current_Rate1_Price,          &GV_Current_Rate_Price[0][0],         CLCurrent_Rate1_Price,          C_MaxRatesNum},
/*138*/{E2Addr_BackUp_Rate1_Price,           &GV_BackUp_Rate_Price[0][0],          CLBackUp_Rate1_Price,           C_MaxRatesNum},
/*139*/{E2Addr_Current_Ladder_Table,         &GV_Current_Ladder_Table[0],          CLCurrent_Ladder_Table,         1},
/*140*/{E2Addr_BackUp_Ladder_Table,          &GV_BackUp_Ladder_Table[0],           CLBackUp_Ladder_Table,          1},

/*141*/{E2Addr_LossVolage_Vol_UpLim,         &GV_LossVolage_Vol_UpLim[0],          CLLossVolage_Vol_UpLim,         1},
/*142*/{E2Addr_LossVolage_Vol_LowLim,        &GV_LossVolage_Vol_LowLim[0],         CLLossVolage_Vol_LowLim,        1},
/*143*/{E2Addr_LossVolage_Curr_LowLim,       &GV_LossVolage_Curr_LowLim[0],        CLLossVolage_Curr_LowLim,       1},
/*144*/{E2Addr_LossVolage_Delay_T,           &GV_LossVolage_Delay_T[0],            CLLossVolage_Delay_T,           1},

/*145*/{E2Addr_LowVolage_Vol_UpLim,          &GV_LowVolage_Vol_UpLim[0],           CLLowVolage_Vol_UpLim,          1},
/*146*/{E2Addr_LowVolage_Delay_T,            &GV_LowVolage_Delay_T[0],             CLLowVolage_Delay_T,            1},

/*147*/{E2Addr_OverVolage_Vol_LowLim,        &GV_OverVolage_Vol_LowLim[0],         CLOverVolage_Vol_LowLim,        1},
/*148*/{E2Addr_OverVolage_Delay_T,           &GV_OverVolage_Delay_T[0],            CLOverVolage_Delay_T,           1},

/*149*/{E2Addr_BreakVol_Vol_UpLim,           &GV_BreakVol_Vol_UpLim[0],            CLBreakVol_Vol_UpLim,           1},
/*150*/{E2Addr_BreakVol_Curr_UpLim,          &GV_BreakVol_Curr_UpLim[0],           CLBreakVol_Curr_UpLim,          1},
/*151*/{E2Addr_BreakVol_Delay_T,             &GV_BreakVol_Delay_T[0],              CLBreakVol_Delay_T,             1},

/*152*/{E2Addr_NoBal_Vol_Lim,                &GV_NoBal_Vol_Lim[0],                 CLNoBal_Vol_Lim,                1},
/*153*/{E2Addr_NoBal_Vol_Delay_T,            &GV_NoBal_Vol_Delay_T[0],             CLNoBal_Vol_Delay_T,            1},

/*154*/{E2Addr_NoBal_Curr_Lim,               &GV_NoBal_Curr_Lim[0],                CLNoBal_Curr_Lim,               1},
/*155*/{E2Addr_NoBal_Curr_Delay_T,           &GV_NoBal_Curr_Delay_T[0],            CLNoBal_Curr_Delay_T,           1},

/*156*/{E2Addr_SeriNoBal_Curr_Lim,           &GV_SeriNoBal_Curr_Lim[0],            CLSeriNoBal_Curr_Lim,           1},
/*157*/{E2Addr_SeriNoBal_Curr_Delay_T,       &GV_SeriNoBal_Curr_Delay_T[0],        CLSeriNoBal_Curr_Delay_T,       1},

/*158*/{E2Addr_LossCurr_Vol_LowLim,          &GV_LossCurr_Vol_LowLim[0],           CLLossCurr_Vol_LowLim,          1},
/*159*/{E2Addr_LossCurr_Curr_UpLim,          &GV_LossCurr_Curr_UpLim[0],           CLLossCurr_Curr_UpLim,          1},
/*160*/{E2Addr_LossCurr_Curr_LowLim,         &GV_LossCurr_Curr_LowLim[0],          CLLossCurr_Curr_LowLim,         1},
/*161*/{E2Addr_LossCurr_Delay_T,             &GV_LossCurr_Delay_T[0],              CLLossCurr_Delay_T,             1},

/*162*/{E2Addr_OverCurr_Curr_LowLim,         &GV_OverCurr_Curr_LowLim[0],          CLOverCurr_Curr_LowLim,         1},
/*163*/{E2Addr_OverCurr_Delay_T,             &GV_OverCurr_Delay_T[0],              CLOverCurr_Delay_T,             1},

/*164*/{E2Addr_BreakCurr_Vol_LowLim,         &GV_BreakCurr_Vol_LowLim[0],          CLBreakCurr_Vol_LowLim,         1},
/*165*/{E2Addr_BreakCurr_Curr_UpLim,         &GV_BreakCurr_Curr_UpLim[0],          CLBreakCurr_Curr_UpLim,         1},
/*166*/{E2Addr_BreakCurr_Delay_T,            &GV_BreakCurr_Delay_T[0],             CLBreakCurr_Delay_T,            1},

/*167*/{E2Addr_OverLoad_AcPower_LowLim,      &GV_OverLoad_AcPower_LowLim[0],       CLOverLoad_AcPower_LowLim,      1},
/*168*/{E2Addr_OverLoad_Delay_T,             &GV_OverLoad_Delay_T[0],              CLOverLoad_Delay_T,             1},

/*169*/{E2Addr_PosAcDemandOv_De_LowLim,      &GV_PosAcDemandOv_De_LowLim[0],       CLPosAcDemandOv_De_LowLim,      1},
/*170*/{E2Addr_PosAcDemandOv_Delay_T,        &GV_PosAcDemandOv_Delay_T[0],         CLPosAcDemandOv_Delay_T,        1},
/*171*/{E2Addr_RevAcDemandOv_De_LowLim,      &GV_RevAcDemandOv_De_LowLim[0],       CLRevAcDemandOv_De_LowLim,      1},
/*172*/{E2Addr_RevAcDemandOv_Delay_T,        &GV_RevAcDemandOv_Delay_T[0],         CLRevAcDemandOv_Delay_T,        1},
/*173*/{E2Addr_ReDemandOv_De_LowLim,         &GV_ReDemandOv_De_LowLim[0],          CLReDemandOv_De_LowLim,         1},
/*174*/{E2Addr_ReDemandOv_Delay_T,           &GV_ReDemandOv_Delay_T[0],            CLReDemandOv_Delay_T,           1},

/*175*/{E2Addr_PowerFactor_LowLim,           &GV_PowerFactor_LowLim[0],            CLPowerFactor_LowLim,           1},
/*176*/{E2Addr_PowerFactor_Delay_T,          &GV_PowerFactor_Delay_T[0],           CLPowerFactor_Delay_T,          1},

/*177*/{E2Addr_PowerRev_AcPower_LowLim,      &GV_PowerRev_AcPower_LowLim[0],       CLPowerRev_AcPower_LowLim,      1},
/*178*/{E2Addr_PowerRev_Delay_T,             &GV_PowerRev_Delay_T[0],              CLPowerRev_Delay_T,             1},

/*179*/{E2Addr_NeutralAbnormal_Curr_LowLim,  &GV_NeutralAbnormal_Curr_LowLim[0],   CLNeutralAbnormal_Curr_LowLim,  1},
/*180*/{E2Addr_NeutralUnbalanceRate,         &GV_NeutralUnbalanceRate[0],          CLNeutralUnbalanceRate,         1},
/*181*/{E2Addr_NeutralAbnormal_Delay_T,      &GV_NeutralAbnormal_Delay_T[0],       CLNeutralAbnormal_Delay_T,      1},

/*182*/{E2Addr_ReversedVoltage_Delay_T,      &GV_ReversedVoltage_Delay_T[0],       CLReversedVoltage_Delay_T,      1},
/*183*/{E2Addr_ReversedCurrent_Delay_T,      &GV_ReversedCurrent_Delay_T[0],       CLReversedCurrent_Delay_T,      1},
/*184*/{E2Addr_PowerOff_Delay_T,             &GV_PowerOff_Delay_T[0],              CLPowerOff_Delay_T,             1},
/*185*/{E2Addr_Aux_Pow_Down_Delay_T,         &GV_Aux_Pow_Down_Delay_T[0],          CLAux_Pow_Down_Delay_T,         1},
/*186*/{E2Addr_ClockFa_Delay_T,              &GV_ClockFa_Delay_T[0],               CLClockFa_Delay_T,              1},
/*187*/{E2Addr_MeterFa_Delay_T,              &GV_MeterFa_Delay_T[0],               CLMeterFa_Delay_T,              1},

/*188*/{E2Addr_Voltage_UpLim,                &GV_Voltage_UpLim[0],                 CLVoltage_UpLim,                1},
/*189*/{E2Addr_Voltage_LowLim,               &GV_Voltage_LowLim[0],                CLVoltage_LowLim,               1},
/*190*/{E2Addr_Volage_Check_UpLim,           &GV_Volage_Check_UpLim[0][0],         CLVolage_Check_UpLim,           2},

/*191*/{E2Addr_Volage_Type,                  &GV_Volage_Type[0][0],                CLVolage_Type,                  8},
/*192*/{E2Addr_Start_Up_Current,             &GV_Start_Up_Current[0],              CLStart_Up_Current,             1},
/*193*/{E2Addr_Start_Up_Power,               &GV_Start_Up_Power[0],                CLStart_Up_Power,               1},
/*194*/{E2Addr_Volage_Abnor_Vol,             &GV_Volage_Abnor_Vol[0],              CLVolage_Abnor_Vol,             1},
/*195*/{E2Addr_Loss_Volage_Curr,             &GV_Loss_Volage_Curr[0][0],           CLLoss_Volage_Curr,             5},
/*196*/{E2Addr_Pluse_Most__Lim,              &GV_Pluse_Most__Lim[0],               CLPluse_Most__Lim,              1},
/*197*/{E2Addr_Curr_Ratio_30A,               &GV_Curr_Ratio_30A[0],                CLCurr_Ratio_30A,               1},
/*198*/{E2Addr_Pulse_Constant,               &GV_Pulse_Constant[0],                CLPulse_Constant,               1},
/*199*/{E2Addr_SoftIJ_Valid_Time,            &GV_SoftIJ_Valid_Time[0],             CLSoftIJ_Valid_Time,            1},
/*200*/{E2Addr_Extern_Relay_PulW,            &GV_Extern_Relay_PulW[0],             CLExtern_Relay_PulW,            1},
/*201*/{E2Addr_MeterRunStatic,               &GV_MeterRunStatic[0],                CLMeterRunStatic,               1},
/*202*/{E2Addr_Alarm_Status,                 &GV_Alarm_Status[0],                  CLAlarm_Status,                 1},
/*203*/{E2Addr_Rst_ReportState_Timer,        &GV_Rst_ReportState_Timer[0],         CLRst_ReportState_Timer,        1},
/*204*/{E2Addr_Relay_Open_CurrTimer,         &GV_Relay_Open_CurrTimer[0],          CLRelay_Open_CurrTimer,         1},
/*205*/{E2Addr__IRAuth_Timer,                &GV__IRAuth_Timer[0],                 CL_IRAuth_Timer,                1},
/*206*/{E2Addr_Relay_RemoteOrder,            &GV_Relay_RemoteOrder[0],             CLRelay_RemoteOrder,            1},
/*207*/{E2Addr_Relay_State,                  &GV_Relay_State[0],                   CLRelay_State,                  1},
/*208*/{E2Addr_Relay_LocalOrder,             &GV_Relay_LocalOrder[0],              CLRelay_LocalOrder,             1},
/*209*/{E2Addr_Remote_Local_State,           &GV_Remote_Local_State[0],            CLRemote_Local_State,           1},
/*210*/{E2Addr_Drive_Report_Mode,            &GV_Drive_Report_Mode[0],             CLDrive_Report_Mode,            1},

/*211*/{E2Addr_AppProInformation,            &GV_AppProInformation[0],             CLAppProInformation,            1},
/*212*/{E2Addr_AppMaxReAPDU,                 &GV_AppMaxReAPDU[0],                  CLAppMaxReAPDU,                 1},
/*213*/{E2Addr_AppMaxSeAPDU,                 &GV_AppMaxSeAPDU[0],                  CLAppMaxSeAPDU,                 1},
/*214*/{E2Addr_AppMaxHandleAPDU,             &GV_AppMaxHandleAPDU[0],              CLAppMaxHandleAPDU,             1},
/*215*/{E2Addr_AppProConsistency,            &GV_AppProConsistency[0],             CLAppProConsistency,            1},
/*216*/{E2Addr_AppFunConsistency,            &GV_AppFunConsistency[0],             CLAppFunConsistency,            1},
/*217*/{E2Addr_AppStaticTimeout,             &GV_AppStaticTimeout[0],              CLAppStaticTimeout,             1},

/*218*/{E2Addr_AppStaticTimeout_termal,      &GV_AppStaticTimeout_terminal[0],     CLAppStaticTimeout,             1},

/*219*/{E2Addr_ConAutheMechanism,            &GV_ConAutheMechanism[0],             CLConAutheMechanism,            1},
/*220*/{E2Addr_SafeModePara,                 &GV_SafeModePara[0],                  CLSafeModePara,                 1},

/*221*/{E2Addr_I_Free_OADTabLen_T,           &GV_Free_OADTabLen_T[0][0],           CLI_Free_OADTabLen_T,           1},
/*222*/{E2Addr_Min_Free_OADTabLen_T,         &GV_Free_OADTabLen_T[1][0],           CLI_Free_OADTabLen_T,           1},
/*223*/{E2Addr_H_Free_OADTabLen_T,           &GV_Free_OADTabLen_T[2][0],           CLI_Free_OADTabLen_T,           1},
/*224*/{E2Addr_D_Free_OADTabLen_T,           &GV_Free_OADTabLen_T[3][0],           CLI_Free_OADTabLen_T,           1},
/*225*/{E2Addr_Sett_Free_OADTabLen_T,        &GV_Free_OADTabLen_T[4][0],           CLI_Free_OADTabLen_T,           1},
/*226*/{E2Addr_M_Free_OADTabLen_T,           &GV_Free_OADTabLen_T[5][0],           CLI_Free_OADTabLen_T,           1},
/*227*/{E2Addr_Y_Free_OADTabLen_T,           &GV_Free_OADTabLen_T[6][0],           CLI_Free_OADTabLen_T,           1},
/*228*/{E2Addr_TZ_Free_OADTabLen_T,          &GV_Free_OADTabLen_T[7][0],           CLI_Free_OADTabLen_T,           1},
/*229*/{E2Addr_PT_Free_OADTabLen_T,          &GV_Free_OADTabLen_T[8][0],           CLI_Free_OADTabLen_T,           1},
/*230*/{E2Addr_R_Free_OADTabLen_T,           &GV_Free_OADTabLen_T[9][0],           CLI_Free_OADTabLen_T,           1},
/*231*/{E2Addr_L_Free_OADTabLen_T,           &GV_Free_OADTabLen_T[10][0],          CLI_Free_OADTabLen_T,           1},
/*232*/{E2Addr_D_Free_StartTime,             &GV_Free_StartTime[0][0],             CLD_Free_StartTime,             3},

/*233*/{E2Addr_I_Free_OADTab,                &GV_Free_OADTab[0][0],                C_698Free_OADTabLen,            1},
/*234*/{E2Addr_Min_Free_OADTab,              &GV_Free_OADTab[1][0],                C_698Free_OADTabLen,            1},
/*235*/{E2Addr_H_Free_OADTab,                &GV_Free_OADTab[2][0],                C_698Free_OADTabLen,            1},
/*236*/{E2Addr_D_Free_OADTab,                &GV_Free_OADTab[3][0],                C_698Free_OADTabLen,            1},
/*237*/{E2Addr_Sett_Free_OADTab,             &GV_Free_OADTab[4][0],                C_698Free_OADTabLen,            1},
/*238*/{E2Addr_M_Free_OADTab,                &GV_Free_OADTab[5][0],                C_698Free_OADTabLen,            1},
/*239*/{E2Addr_Y_Free_OADTab,                &GV_Free_OADTab[6][0],                C_698Free_OADTabLen,            1},
/*240*/{E2Addr_TZ_Free_OADTab,               &GV_Free_OADTab[7][0],                C_698Free_OADTabLen,            1},
/*241*/{E2Addr_PT_Free_OADTab,               &GV_Free_OADTab[8][0],                C_698Free_OADTabLen,            1},
/*242*/{E2Addr_R_Free_OADTab,                &GV_Free_OADTab[9][0],                C_698Free_OADTabLen,            1},
/*243*/{E2Addr_L_Free_OADTab,                &GV_Free_OADTab[10][0],               C_698Free_OADTabLen,            1},

/*244*/{E2Addr_LossVolage_Report_Mode,       &GV_LossVolage_Report_Mode[0],        CLReport_Mode,                  1},
/*245*/{E2Addr_LowVolage_Report_Mode,        &GV_LowVolage_Report_Mode[0],         CLReport_Mode,                  1},
/*246*/{E2Addr_OverVolage_Report_Mode,       &GV_OverVolage_Report_Mode[0],        CLReport_Mode,                  1},
/*247*/{E2Addr_BreakVol_Report_Mode,         &GV_BreakVol_Report_Mode[0],          CLReport_Mode,                  1},
/*248*/{E2Addr_LossCurr_Report_Mode,         &GV_LossCurr_Report_Mode[0],          CLReport_Mode,                  1},
/*249*/{E2Addr_OverCurr_Report_Mode,         &GV_OverCurr_Report_Mode[0],          CLReport_Mode,                  1},
/*250*/{E2Addr_BreakCurr_Report_Mode,        &GV_BreakCurr_Report_Mode[0],         CLReport_Mode,                  1},
/*251*/{E2Addr_PowerRev_Report_Mode,         &GV_PowerRev_Report_Mode[0],          CLReport_Mode,                  1},
/*252*/{E2Addr_OverLoad_Report_Mode,         &GV_OverLoad_Report_Mode[0],          CLReport_Mode,                  1},
/*253*/{E2Addr_PosAcDemandOv_Report_Mode,    &GV_PosAcDemandOv_Report_Mode[0],     CLReport_Mode,                  1},
/*254*/{E2Addr_RevAcDemandOv_Report_Mode,    &GV_RevAcDemandOv_Report_Mode[0],     CLReport_Mode,                  1},
/*255*/{E2Addr_ReDemandOv_Report_Mode,       &GV_ReDemandOv_Report_Mode[0],        CLReport_Mode,                  1},
/*256*/{E2Addr_PowerFactor_Report_Mode,      &GV_PowerFactor_Report_Mode[0],       CLReport_Mode,                  1},
/*257*/{E2Addr_AllLossVolage_Report_Mode,    &GV_AllLossVolage_Report_Mode[0],     CLReport_Mode,                  1},
/*258*/{E2Addr_AuxPowDown_Report_Mode,       &GV_AuxPowDown_Report_Mode[0],        CLReport_Mode,                  1},
/*259*/{E2Addr_ReversedVoltage_Report_Mode,  &GV_ReversedVoltage_Report_Mode[0],   CLReport_Mode,                  1},
/*260*/{E2Addr_ReversedCurrent_Report_Mode,  &GV_ReversedCurrent_Report_Mode[0],   CLReport_Mode,                  1},
/*261*/{E2Addr_PowerOff_Report_Mode,         &GV_PowerOff_Report_Mode[0],          CLReport_Mode,                  1},
/*262*/{E2Addr_Program_Report_Mode,          &GV_Program_Report_Mode[0],           CLReport_Mode,                  1},
/*263*/{E2Addr_TolClear_Report_Mode,         &GV_TolClear_Report_Mode[0],          CLReport_Mode,                  1},
/*264*/{E2Addr_DemandClear_Report_Mode,      &GV_DemandClear_Report_Mode[0],       CLReport_Mode,                  1},
/*265*/{E2Addr_EventClear_Report_Mode,       &GV_EventClear_Report_Mode[0],        CLReport_Mode,                  1},
/*266*/{E2Addr_AdjTime_Report_Mode,          &GV_AdjTime_Report_Mode [0],          CLReport_Mode,                  1},
/*267*/{E2Addr_ProgPT_Report_Mode,           &GV_ProgPT_Report_Mode[0],            CLReport_Mode,                  1},
/*268*/{E2Addr_ProgPZ_Report_Mode,           &GV_ProgPZ_Report_Mode[0],            CLReport_Mode,                  1},
/*269*/{E2Addr_ProgWRe_Report_Mode,          &GV_ProgWRe_Report_Mode[0],           CLReport_Mode,                  1},
/*270*/{E2Addr_ProgSettD_Report_Mode,        &GV_ProgSettD_Report_Mode[0],         CLReport_Mode,                  1},
/*271*/{E2Addr_OpenW_Report_Mode,            &GV_OpenW_Report_Mode[0],             CLReport_Mode,                  1},
/*272*/{E2Addr_OpenCW_Report_Mode,           &GV_OpenCW_Report_Mode[0],            CLReport_Mode,                  1},
/*273*/{E2Addr_NoBalVol_Report_Mode,         &GV_NoBalVol_Report_Mode[0],          CLReport_Mode,                  1},
/*274*/{E2Addr_NoBalCurr_Report_Mode,        &GV_NoBalCurr_Report_Mode[0],         CLReport_Mode,                  1},
/*275*/{E2Addr_RelayOpen_Report_Mode,        &GV_RelayOpen_Report_Mode[0],         CLReport_Mode,                  1},
/*276*/{E2Addr_RelayClose_Report_Mode,       &GV_RelayClose_Report_Mode[0],        CLReport_Mode,                  1},
/*277*/{E2Addr_ProgHol_Report_Mode,          &GV_ProgHol_Report_Mode[0],           CLReport_Mode,                  1},
/*278*/{E2Addr_ProgAcC_Report_Mode,          &GV_ProgAcC_Report_Mode[0],           CLReport_Mode,                  1},
/*279*/{E2Addr_ProgReC_Report_Mode,          &GV_ProgReC_Report_Mode[0],           CLReport_Mode,                  1},
/*280*/{E2Addr_ProgTPara_Report_Mode,        &GV_ProgTPara_Report_Mode[0],         CLReport_Mode,                  1},
/*281*/{E2Addr_ProgLad_Report_Mode,          &GV_ProgLad_Report_Mode[0],           CLReport_Mode,                  1},
/*282*/{E2Addr_Key_Update_Report_Mode,       &GV_Key_Update_Report_Mode[0],        CLReport_Mode,                  1},
/*283*/{E2Addr_AbnorC_Report_Mode,           &GV_AbnorC_Report_Mode[0],            CLReport_Mode,                  1},
/*284*/{E2Addr_BuyCurr_Report_Mode,          &GV_BuyCurr_Report_Mode[0],           CLReport_Mode,                  1},
/*285*/{E2Addr_ReturnMoney_Report_Mode,      &GV_ReturnMoney_Report_Mode[0],       CLReport_Mode,                  1},
/*286*/{E2Addr_ConMEndEn_Report_Mode,        &GV_ConMEndEn_Report_Mode[0],         CLReport_Mode,                  1},
/*287*/{E2Addr_RelayFaEndEn_Report_Mode,     &GV_RelayFaEndEn_Report_Mode[0],      CLReport_Mode,                  1},
/*288*/{E2Addr_PowerFa_EndT_Report_Mode,     &GV_PowerFa_EndT_Report_Mode[0],      CLReport_Mode,                  1},
/*289*/{E2Addr_SeriNoBalCurr_Report_Mode,    &GV_SeriNoBalCurr_Report_Mode[0],     CLReport_Mode,                  1},
/*290*/{E2Addr_ClockFault_Report_Mode,       &GV_ClockFault_Report_Mode[0],        CLReport_Mode,                  1},
/*291*/{E2Addr_MeteringChipFault_Report_Mode,&GV_MeteringChipFault_Report_Mode[0], CLReport_Mode,                  1},
/*292*/{E2Addr_BroadcastTime_Report_Mode,    &GV_BroadcastTime_Report_Mode[0],     CLReport_Mode,                  1},
/*293*/{E2Addr_ABnor_ZeroCurrent_Report_Mode,&GV_ABnor_ZeroCurrent_Report_Mode[0], CLReport_Mode,                  1},/*���ߵ����쳣�ϱ�ģʽ��*/

/*294*/{E2Addr_LossVolage_Report_Type,       &GV_LossVolage_Report_Type[0],        CLReport_Type,                  1},/*ʧѹ�ϱ���ʽ*/
/*295*/{E2Addr_LowVolage_Report_Type,        &GV_LowVolage_Report_Type[0],         CLReport_Type,                  1},/*Ƿѹ�ϱ���ʽ*/
/*296*/{E2Addr_OverVolage_Report_Type,       &GV_OverVolage_Report_Type[0],        CLReport_Type,                  1},/*��ѹ�ϱ���ʽ*/
/*297*/{E2Addr_BreakVol_Report_Type,         &GV_BreakVol_Report_Type[0],          CLReport_Type,                  1},/*�����ϱ���ʽ*/
/*298*/{E2Addr_LossCurr_Report_Type,         &GV_LossCurr_Report_Type[0],          CLReport_Type,                  1},/*ʧ���ϱ���ʽ*/
/*299*/{E2Addr_OverCurr_Report_Type,         &GV_OverCurr_Report_Type[0],          CLReport_Type,                  1},/*�����ϱ���ʽ*/
/*300*/{E2Addr_BreakCurr_Report_Type,        &GV_BreakCurr_Report_Type[0],         CLReport_Type,                  1},/*�����ϱ���ʽ*/
/*301*/{E2Addr_PowerRev_Report_Type,         &GV_PowerRev_Report_Type[0],          CLReport_Type,                  1},/*���ʷ����ϱ���ʽ*/
/*302*/{E2Addr_OverLoad_Report_Type,         &GV_OverLoad_Report_Type[0],          CLReport_Type,                  1},/*�����ϱ���ʽ*/
/*303*/{E2Addr_PosAcDemandOv_Report_Type,    &GV_PosAcDemandOv_Report_Type[0],     CLReport_Type,                  1},/*�����й����������¼��ϱ���ʽ*/
/*304*/{E2Addr_RevAcDemandOv_Report_Type,    &GV_RevAcDemandOv_Report_Type[0],     CLReport_Type,                  1},/*�����й����������¼��ϱ���ʽ*/
/*305*/{E2Addr_ReDemandOv_Report_Type,       &GV_ReDemandOv_Report_Type[0],        CLReport_Type,                  1},/*�޹����������¼��ϱ���ʽ*/
/*306*/{E2Addr_PowerFactor_Report_Type,      &GV_PowerFactor_Report_Type[0],       CLReport_Type,                  1},/*���������������¼��ϱ���ʽ*/
/*307*/{E2Addr_AllLossVolage_Report_Type,    &GV_AllLossVolage_Report_Type[0],     CLReport_Type,                  1},/*ȫʧѹ�ϱ���ʽ*/
/*308*/{E2Addr_AuxPowDown_Report_Type,       &GV_AuxPowDown_Report_Type[0],        CLReport_Type,                  1},/*������Դʧ���ϱ���ʽ*/
/*309*/{E2Addr_ReversedVoltage_Report_Type,  &GV_ReversedVoltage_Report_Type[0],   CLReport_Type,                  1},/*��ѹ�������ϱ���ʽ*/
/*310*/{E2Addr_ReversedCurrent_Report_Type,  &GV_ReversedCurrent_Report_Type[0],   CLReport_Type,                  1},/*�����������ϱ���ʽ*/
/*311*/{E2Addr_PowerOff_Report_Type,         &GV_PowerOff_Report_Type[0],          CLReport_Type,                  1},/*�����ϱ���ʽ*/
/*312*/{E2Addr_Program_Report_Type,          &GV_Program_Report_Type[0],           CLReport_Type,                  1},/*����ϱ���ʽ*/
/*313*/{E2Addr_TolClear_Report_Type,         &GV_TolClear_Report_Type[0],          CLReport_Type,                  1},/*��������ϱ���ʽ*/
/*314*/{E2Addr_DemandClear_Report_Type,      &GV_DemandClear_Report_Type[0],       CLReport_Type,                  1},/*���������ϱ���ʽ*/
/*315*/{E2Addr_EventClear_Report_Type,       &GV_EventClear_Report_Type[0],        CLReport_Type,                  1},/*�¼������ϱ���ʽ*/
/*316*/{E2Addr_AdjTime_Report_Type,          &GV_AdjTime_Report_Type [0],          CLReport_Type,                  1},/*Уʱ�ϱ���ʽ*/
/*317*/{E2Addr_ProgPT_Report_Type,           &GV_ProgPT_Report_Type[0],            CLReport_Type,                  1},/*ʱ�α����ϱ���ʽ*/
/*318*/{E2Addr_ProgPZ_Report_Type,           &GV_ProgPZ_Report_Type[0],            CLReport_Type,                  1},/*ʱ�������ϱ���ʽ*/
/*319*/{E2Addr_ProgWRe_Report_Type,          &GV_ProgWRe_Report_Type[0],           CLReport_Type,                  1},/*�����ձ���ϱ���ʽ*/
/*320*/{E2Addr_ProgSettD_Report_Type,        &GV_ProgSettD_Report_Type[0],         CLReport_Type,                  1},/*�����ձ���ϱ���ʽ*/
/*321*/{E2Addr_OpenW_Report_Type,            &GV_OpenW_Report_Type[0],             CLReport_Type,                  1},/*������ϱ���ʽ*/
/*322*/{E2Addr_OpenCW_Report_Type,           &GV_OpenCW_Report_Type[0],            CLReport_Type,                  1},/*����ť���ϱ���ʽ*/
/*323*/{E2Addr_NoBalVol_Report_Type,         &GV_NoBalVol_Report_Type[0],          CLReport_Type,                  1},/*��ѹ��ƽ���ϱ���ʽ*/
/*324*/{E2Addr_NoBalCurr_Report_Type,        &GV_NoBalCurr_Report_Type[0],         CLReport_Type,                  1},/*������ƽ���ϱ���ʽ*/
/*325*/{E2Addr_RelayOpen_Report_Type,        &GV_RelayOpen_Report_Type[0],         CLReport_Type,                  1},/*��բ�ϱ���ʽ*/
/*326*/{E2Addr_RelayClose_Report_Type,       &GV_RelayClose_Report_Type[0],        CLReport_Type,                  1},/*��բ�ϱ���ʽ*/
/*327*/{E2Addr_ProgHol_Report_Type,          &GV_ProgHol_Report_Type[0],           CLReport_Type,                  1},/*�ڼ��ձ���ϱ���ʽ*/
/*328*/{E2Addr_ProgAcC_Report_Type,          &GV_ProgAcC_Report_Type[0],           CLReport_Type,                  1},/*�й���Ϸ�ʽ����ϱ���ʽ*/
/*329*/{E2Addr_ProgReC_Report_Type,          &GV_ProgReC_Report_Type[0],           CLReport_Type,                  1},/*�޹���Ϸ�ʽ����ϱ���ʽ*/
/*330*/{E2Addr_ProgTPara_Report_Type,        &GV_ProgTPara_Report_Type[0],         CLReport_Type,                  1},/*���ʲ��������ϱ���ʽ*/
/*331*/{E2Addr_ProgLad_Report_Type,          &GV_ProgLad_Report_Type[0],           CLReport_Type,                  1},/*���ݱ����ϱ���ʽ*/
/*332*/{E2Addr_Key_Update_Report_Type,       &GV_Key_Update_Report_Type[0],        CLReport_Type,                  1},/*��Կ�����ϱ���ʽ*/
/*333*/{E2Addr_AbnorC_Report_Type,           &GV_AbnorC_Report_Type[0],            CLReport_Type,                  1},/*�쳣�忨�ϱ���ʽ*/
/*334*/{E2Addr_BuyCurr_Report_Type,          &GV_BuyCurr_Report_Type[0],           CLReport_Type,                  1},/*�����ϱ���ʽ*/
/*335*/{E2Addr_ReturnMoney_Report_Type,      &GV_ReturnMoney_Report_Type[0],       CLReport_Type,                  1},/*�˷��ϱ���ʽ*/
/*336*/{E2Addr_ConMEndEn_Report_Type,        &GV_ConMEndEn_Report_Type[0],         CLReport_Type,                  1},/*�㶨�ų������ϱ���ʽ*/
/*337*/{E2Addr_RelayFaEndEn_Report_Type,     &GV_RelayFaEndEn_Report_Type[0],      CLReport_Type,                  1},/*���ɿ��������ϱ���ʽ*/
/*338*/{E2Addr_PowerFa_EndT_Report_Type,     &GV_PowerFa_EndT_Report_Type[0],      CLReport_Type,                  1},/*��Դ�쳣�ϱ���ʽ*/
/*339*/{E2Addr_SeriNoBalCurr_Report_Type,    &GV_SeriNoBalCurr_Report_Type[0],     CLReport_Type,                  1},/*�������ز�ƽ���ϱ���ʽ*/
/*340*/{E2Addr_ClockFault_Report_Type,       &GV_ClockFault_Report_Type[0],        CLReport_Type,                  1},/*ʱ�ӹ����ϱ���ʽ*/
/*341*/{E2Addr_MeteringChipFault_Report_Type,&GV_MeteringChipFault_Report_Type[0], CLReport_Type,                  1},/*����оƬ�����ϱ���ʽ*/
/*342*/{E2Addr_BroadcastTime_Report_Type,    &GV_BroadcastTime_Report_Type[0],     CLReport_Type,                  1},/*�㲥Уʱ�ϱ���ʽ*/
/*343*/{E2Addr_ABnor_ZeroCurrent_Report_Type,&GV_ABnor_ZeroCurrent_Report_Type[0], CLReport_Type,                  1},/*���ߵ����쳣�ϱ���ʽ*/
/*344*/{E2Addr_Drive_Report_Type,            &GV_Drive_Report_Type[0],             CLReport_Type,                  1}, /*2015�����ϱ���ʽ*/


/*345*/{E2Addr_Relay_Delay_Time_645,         &GV_Relay_Delay_Time_645[0],          CLRelay_Delay_Time_645,         1},
/*346*/{E2Addr_Drive_Report_Mode_645,        &GV_Drive_Report_Mode_645[0],         CLDrive_Report_Mode_645,        1},
/*347*/{E2Addr_Meter_Work_Char1_645,         &GV_Meter_Work_Char1_645[0],          CLMeter_Work_Char1_645,         1},
/*348*/{E2Addr_Meter_Work_Char1,             &GV_Meter_Work_Char1[0],              CLMeter_Work_Char1,             1},

};
#define Str_3aTable_E23RAM_Len  (sizeof(Str_3aTable_E23RAM)/sizeof(Str_3aTable))

#define C_No4TableAllFF    0xFFFFFFFF
const Str_3cTable Str_3cTable_Flash[]=
{/*��¼��Flash��ҳ��ַ       ��¼��Flashβҳ��ַ      4�����ṹ�������ַ,��4��������ʱ��ΪȫFF       ������E2��1�����ݵ�ַ      1����¼�������ܳ���     4�����ṹ���������ݳ���,��������4����ʱ������Ϊȫ��*/
    {FlashStAddr_Rec_Meter,             FlashEndAddr_Rec_Meter,             (ulong32)(&Str_4Table_Rec_Meter[0]),    E2Addr_Rec_Meter_Degree,             Rec_Meter_Data_Len,             Str_4Table_Rec_Meter_Len},
    {FlashStAddr_CurrentPart_ProgPT,    FlashEndAddr_CurrentPart_ProgPT,    (ulong32)(&Str_4Table_ProgPT[0]),       E2Addr_ProgPT_CurrentPart_Degree,    ProgPT_Data_CurrentPart_Len,    Str_4Table_ProgPT_Len},
    {FlashStAddr_CurrentPart_ProgTZ,    FlashEndAddr_CurrentPart_ProgTZ,    C_No4TableAllFF,                        E2Addr_ProgTZ_CurrentPart_Degree,    ProgTZ_Data_CurrentPart_Len,    0},
    {FlashStAddr_Program_645,           FlashEndAddr_Program_645,           C_No4TableAllFF,                        E2Addr_Program_Degree_645,           Program_Data_Len_645,           0},
};
#define Str_3cTable_Flash_Len  (sizeof(Str_3cTable_Flash)/sizeof(Str_3cTable))

const Str_3eTable Str_3eTable_2E2[]=
{/*����OAD��ű�E2��ַ       ������ű�OAD����E2��ַ*/
  {E2Addr_All_Loss_Vol_OADTab,			E2Addr_All_Loss_Vol_OADTabLen},
  {E2Addr_Aux_Pow_Down_OADTab,			E2Addr_Aux_Pow_Down_OADTabLen},
  {E2Addr_Pow_Down_OADTab,				E2Addr_Pow_Down_OADTabLen},
  {E2Addr_Pos_Ac_De_Over_OADTab,		E2Addr_Pos_Ac_De_Over_OADTabLen},
  {E2Addr_Rev_Ac_De_Over_OADTab,		E2Addr_Rev_Ac_De_Over_OADTabLen},
  {E2Addr_Qua_Re_De_Over_OADTab,		E2Addr_Qua_Re_De_Over_OADTabLen},
  {E2Addr_Loss_Vol_OADTab,				E2Addr_Loss_Vol_OADTabLen},
  {E2Addr_Low_Vol_OADTab,				E2Addr_Low_Vol_OADTabLen},
  {E2Addr_Over_Vol_OADTab,				E2Addr_Over_Vol_OADTabLen},
  {E2Addr_Break_Vol_OADTab,				E2Addr_Break_Vol_OADTabLen},
  {E2Addr_RevPS_Vol_OADTab,				E2Addr_RevPS_Vol_OADTabLen},
  {E2Addr_RevPS_Curr_OADTab,			E2Addr_RevPS_Curr_OADTabLen},
  {E2Addr_NoBal_Vol_OADTab,	 			E2Addr_NoBal_Vol_OADTabLen},
  {E2Addr_NoBal_Curr_OADTab,			E2Addr_NoBal_Curr_OADTabLen},
  {E2Addr_SevNoBal_Curr_OADTab,			E2Addr_SevNoBal_Curr_OADTabLen},
  {E2Addr_Loss_Curr_OADTab,				E2Addr_Loss_Curr_OADTabLen},
  {E2Addr_Over_Curr_OADTab,				E2Addr_Over_Curr_OADTabLen},
  {E2Addr_Break_Curr_OADTab,			E2Addr_Break_Curr_OADTabLen},
  {E2Addr_Power_Rev_OADTab,				E2Addr_Power_Rev_OADTabLen},
  {E2Addr_Over_Lo_OADTab,				E2Addr_Over_Lo_OADTabLen},
  {E2Addr_Tol_Clear_OADTab,				E2Addr_Tol_Clear_OADTabLen},
  {E2Addr_De_Clear_OADTab,				E2Addr_De_Clear_OADTabLen},
  {E2Addr_Even_Clear_OADTab,			E2Addr_Even_Clear_OADTabLen},
  {E2Addr_Program_OADTab,				E2Addr_Program_OADTabLen},
  {E2Addr_AbnorC_OADTab,				E2Addr_AbnorC_OADTabLen},
  {E2Addr_OpenW_OADTab,					E2Addr_OpenW_OADTabLen},
  {E2Addr_OpenCW_OADTab,				E2Addr_OpenCW_OADTabLen},
  {E2Addr_BuyCurr_OADTab,				E2Addr_BuyCurr_OADTabLen},
  {E2Addr_Return_M_OADTab,				E2Addr_Return_M_OADTabLen},
  {E2Addr_ConM_OADTab,					E2Addr_ConM_OADTabLen},
  {E2Addr_RelayFa_OADTab,				E2Addr_RelayFa_OADTabLen},
  {E2Addr_PowerFa_OADTab,				E2Addr_PowerFa_OADTabLen},
  {E2Addr_RelayOpen_OADTab,				E2Addr_RelayOpen_OADTabLen},
  {E2Addr_RelayClose_OADTab,			E2Addr_RelayClose_OADTabLen},
  {E2Addr_PFactorT_Over_OADTab,			E2Addr_PFactorT_Over_OADTabLen},
  {E2Addr_AdjTime_OADTab,				E2Addr_AdjTime_OADTabLen},
  {E2Addr_ProgPT_OADTab,				E2Addr_ProgPT_OADTabLen},
  {E2Addr_ProgTZ_OADTab,				E2Addr_ProgTZ_OADTabLen},
  {E2Addr_ProgWRe_OADTab,				E2Addr_ProgWRe_OADTabLen},
  {E2Addr_ProgHol_OADTab,				E2Addr_ProgHol_OADTabLen},
  {E2Addr_ProgAcC_OADTab,				E2Addr_ProgAcC_OADTabLen},
  {E2Addr_ProgReC_OADTab,				E2Addr_ProgReC_OADTabLen},
  {E2Addr_ProgSettD_OADTab,				E2Addr_ProgSettD_OADTabLen},
  {E2Addr_ProgTPara_OADTab,				E2Addr_ProgTPara_OADTabLen},
  {E2Addr_ProgLad_OADTab,				E2Addr_ProgLad_OADTabLen},
  {E2Addr_ProgKD_OADTab,				E2Addr_ProgKD_OADTabLen},
  {E2Addr_MeterFa_OADTab,				E2Addr_MeterFa_OADTabLen},
  {E2Addr_ClockFa_OADTab,				E2Addr_ClockFa_OADTabLen},
  {E2Addr_BroadcastTime_OADTab,			E2Addr_BroadcastTime_OADTabLen},
  {E2Addr_NeutralCurrentAbnormal_OADTab,E2Addr_NeutralCurrentAbnormal_OADTabLen},
//  {E2Addr_BroadTimeAbnormal_OADTab,	E2Addr_BroadTimeAbnormal_OADTabLen},
};
#define Str_3eTable_Flash_Len  (sizeof(Str_3eTable_2E2)/sizeof(Str_3eTable))

/************��ʶ���Ƿ�֧�ֶ�д����ϢдȨ��*************/
#define C_Read_Data                             0x80                                 /**/
#define C_WR_All                                0xFF                                 /*֧������ģ��д��Ŀǰֻ�õ������״̬��*/
#define C_WR_Data                               0x7F
#define C_Only_Read                             0x80                                 /*ֻ֧�ֶ�*/
#define C_No_WR                                 0x00                                 /*����֧�ֶ���Ҳ��֧��д*/
#define C_WR_Msg_PowerNetworkMonitoring         (0x80|C_Msg_PowerNetworkMonitoring)  /*֧�ֶ���ͬʱ֧�ֵ�������ж���Ϣд*/
#define C_W_Msg_PowerNetworkMonitoring          C_Msg_PowerNetworkMonitoring         /*ֻ֧�ֵ�������ж���Ϣд*/

#define C_WR_Msg_Write_PowerNetworkMonitoring   (0x80|C_Msg_Write_PowerNetworkMonitoring)
#define C_W_Msg_Write_PowerNetworkMonitoring    C_Msg_Write_PowerNetworkMonitoring

#define C_WR_Msg_EnergyMetering                 (0x80|C_Msg_EnergyMetering)
#define C_W_Msg_EnergyMetering                  C_Msg_EnergyMetering

#define C_WR_Msg_DemandMetering                 (0x80|C_Msg_DemandMetering)
#define C_W_Msg_DemandMetering                  C_Msg_DemandMetering

#define C_WR_Msg_Communication                  (0x80|C_Msg_Communication)
#define C_W_Msg_Communication                   C_Msg_Communication

#define C_WR_Msg_SettleAccounts                 (0x80|C_Msg_SettleAccounts)
#define C_W_Msg_SettleAccounts                  C_Msg_SettleAccounts

#define C_WR_Msg_Freeze                         (0x80|C_Msg_Freeze)
#define C_W_Msg_Freeze                          C_Msg_Freeze

#define C_WR_Msg_LoadProfile                    (0x80|C_Msg_LoadProfile)
#define C_W_Msg_LoadProfile                     C_Msg_LoadProfile

#define C_WR_Msg_Display                        (0x80|C_Msg_Display)
#define C_W_Msg_Display                         C_Msg_Display

#define C_WR_Msg_Deal_RelayStatus               (0x80|C_Msg_Deal_RelayStatus)
#define C_W_Msg_Deal_RelayStatus                C_Msg_Deal_RelayStatus

#define C_WR_Msg_Deal_MultiRates                (0x80|C_Msg_Deal_MultiRates)
#define C_W_Msg_Deal_MultiRates                 C_Msg_Deal_MultiRates

#define C_WR_Msg_BatteryVoltagleMetering        (0x80|C_Msg_BatteryVoltagleMetering)
#define C_W_Msg_BatteryVoltagleMetering         C_Msg_BatteryVoltagleMetering

#define C_WR_Msg_VoltageQualifiedRateMetering   (0x80|C_Msg_VoltageQualifiedRateMetering)
#define C_W_Msg_VoltageQualifiedRateMetering    C_Msg_VoltageQualifiedRateMetering

#define C_WR_Msg_Dispatch                       (0x80|C_Msg_Dispatch)
#define C_W_Msg_Dispatch                        C_Msg_Dispatch

#define C_WR_Msg_MeterIC                        (0x80|C_Msg_MeterIC)
#define C_W_Msg_MeterIC                         C_Msg_MeterIC

#define C_WR_Msg_Card                           (0x80|C_Msg_Card)
#define C_W_Msg_Card                            C_Msg_Card

#define C_WR_Msg_Esam                           (0x80|C_Msg_Esam)
#define C_W_Msg_Esam                            C_Msg_Esam


/**********�����Ϣ����***************/
#define C_Com_Msg_Star                          80                               /*�����Ϣ�Ŵ�80��ʼ,�������Ϣ������ģ����Ϣ�ţ����ܡݸ�ֵ��������Ϣ�Ų��ܴ�0��ʼ*/
#define C_Msg_PDDF                              C_Com_Msg_Star                   /*�����ϢC_Msg_PowerNetworkMonitoring,C_Msg_Dispatch,C_Msg_Display,C_Msg_Freeze*/
#define C_WR_Msg_PDDF                           (0x80|C_Msg_PDDF)
#define C_W_Msg_PDDF                            C_Msg_PDDF

#define C_Msg_Comm_Card                         (C_Com_Msg_Star+1)               /*�����ϢC_Msg_Communication,C_Msg_Card*/
#define C_WR_Msg_Comm_Card                      (0x80|C_Msg_Comm_Card)
#define C_W_Msg_Comm_Card                       C_Msg_Comm_Card

#define C_Msg_Comm_Dis                          (C_Msg_Comm_Card+1)              /*�����ϢC_Msg_Communication,C_Msg_Dispatch*/
#define C_WR_Msg_Comm_Dis                       (0x80|C_Msg_Comm_Dis)
#define C_W_Msg_Comm_Dis                        C_Msg_Comm_Dis

#define C_Msg_Card_Deal                         (C_Msg_Comm_Dis+1)               /*�����ϢC_Msg_Card,C_Msg_Deal_MultiRates*/
#define C_WR_Msg_Card_Deal                      (0x80|C_Msg_Card_Deal)
#define C_W_Msg_Card_Deal                       C_Msg_Card_Deal

#define C_Msg_En_Deal                           (C_Msg_Card_Deal+1)              /*�����ϢC_Msg_EnergyMetering,C_Msg_Deal_MultiRates*/
#define C_WR_Msg_En_Deal                        (0x80|C_Msg_En_Deal)
#define C_W_Msg_En_Deal                         C_Msg_En_Deal

#define C_Msg_Comm_Deal                         (C_Msg_En_Deal+1)                /*�����ϢC_Msg_Communication,C_Msg_Deal_MultiRates*/
#define C_WR_Msg_Comm_Deal                      (0x80|C_Msg_Comm_Deal)
#define C_W_Msg_Comm_Deal                       C_Msg_Comm_Deal

#define C_Msg_Comm_Deal_Card                    (C_Msg_Comm_Deal+1)              /*�����ϢC_Msg_Communication,C_Msg_Deal_MultiRates,C_Msg_Card*/
#define C_WR_Msg_Comm_Deal_Card                 (0x80|C_Msg_Comm_Deal_Card)
#define C_W_Msg_Comm_Deal_Card                  C_Msg_Comm_Deal_Card

#define C_Msg_Comm_Relay                        (C_Msg_Comm_Deal_Card+1)         /*�����ϢC_Msg_Communication,C_Msg_Deal_RelayStatus*/
#define C_WR_Msg_Comm_Relay                     (0x80|C_Msg_Comm_Relay)
#define C_W_Msg_Comm_Relay                      C_Msg_Comm_Relay


#define C_Com_Msg_Len                           4
const uchar8 GP_Com_Msg[][C_Com_Msg_Len]=
{
	{C_Msg_PowerNetworkMonitoring,    C_Msg_Dispatch,           C_Msg_Display,    C_Msg_Freeze},    /*C_Com_Msg_Star����Ӧ�����Ϣ��80*/
	{C_Msg_Communication,             C_Msg_Card,               0,                0           },
	{C_Msg_Communication,             C_Msg_Dispatch,           0,                0           },
	{C_Msg_Card,                      C_Msg_Deal_MultiRates,    0,                0           },
	{C_Msg_EnergyMetering,            C_Msg_Deal_MultiRates,    0,                0           },
	{C_Msg_Communication,             C_Msg_Deal_MultiRates,    0,                0           },
	{C_Msg_Communication,             C_Msg_Deal_MultiRates,    C_Msg_Card,       0           },
	{C_Msg_Communication,             C_Msg_Deal_RelayStatus,   0,                0           },
};
#define C_Com_Msg_Len_Max (sizeof(GP_Com_Msg)/C_Com_Msg_Len)

/***********��������**************/
const Str_2Table Str_2Table_DIEn[]=
{/*���ݱ�ʾ(���ڵ���ģ���Ϊ������������ģ���Ϊ��ȷ���ܣ���ȡ����ʱ����ģ�鸺������ת��) ��Ӧ������ṹ�������ַ                    Ӧ�������к�  �������ݳ���              ��Ӧ��Ϣ�ż��Ƿ�֧�ֶ�             ��������    */
    {CPos_Ac_T1_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          0,      C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CPos_Ac_T2_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          1,      C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CPos_Ac_T3_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          2,      C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CPos_Ac_T4_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          3,      C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CPos_Ac_T5_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          4,      C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CPos_Ac_T6_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          5,      C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CPos_Ac_T7_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          6,      C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CPos_Ac_T8_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          7,      C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CPos_Ac_T9_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          8,      C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CPos_Ac_T10_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          9,      C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CPos_Ac_T11_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          10,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CPos_Ac_T12_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          11,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},

    {CRev_Ac_T1_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          12,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CRev_Ac_T2_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          13,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CRev_Ac_T3_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          14,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CRev_Ac_T4_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          15,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CRev_Ac_T5_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          16,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CRev_Ac_T6_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          17,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CRev_Ac_T7_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          18,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CRev_Ac_T8_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          19,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CRev_Ac_T9_PreEn_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          20,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CRev_Ac_T10_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          21,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CRev_Ac_T11_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          22,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CRev_Ac_T12_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          23,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},

    {CQua1_Re_T1_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          24,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua1_Re_T2_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          25,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua1_Re_T3_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          26,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua1_Re_T4_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          27,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua1_Re_T5_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          28,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua1_Re_T6_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          29,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua1_Re_T7_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          30,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua1_Re_T8_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          31,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua1_Re_T9_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          32,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua1_Re_T10_PreEn_0,          (ulong32)(&Str_3aTable_E23RAM[0]),          33,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua1_Re_T11_PreEn_0,          (ulong32)(&Str_3aTable_E23RAM[0]),          34,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua1_Re_T12_PreEn_0,          (ulong32)(&Str_3aTable_E23RAM[0]),          35,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},

    {CQua2_Re_T1_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          36,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua2_Re_T2_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          37,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua2_Re_T3_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          38,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua2_Re_T4_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          39,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua2_Re_T5_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          40,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua2_Re_T6_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          41,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua2_Re_T7_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          42,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua2_Re_T8_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          43,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua2_Re_T9_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          44,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua2_Re_T10_PreEn_0,          (ulong32)(&Str_3aTable_E23RAM[0]),          45,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua2_Re_T11_PreEn_0,          (ulong32)(&Str_3aTable_E23RAM[0]),          46,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua2_Re_T12_PreEn_0,          (ulong32)(&Str_3aTable_E23RAM[0]),          47,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},

    {CQua3_Re_T1_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          48,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua3_Re_T2_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          49,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua3_Re_T3_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          50,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua3_Re_T4_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          51,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua3_Re_T5_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          52,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua3_Re_T6_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          53,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua3_Re_T7_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          54,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua3_Re_T8_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          55,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua3_Re_T9_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          56,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua3_Re_T10_PreEn_0,          (ulong32)(&Str_3aTable_E23RAM[0]),          57,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua3_Re_T11_PreEn_0,          (ulong32)(&Str_3aTable_E23RAM[0]),          58,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua3_Re_T12_PreEn_0,          (ulong32)(&Str_3aTable_E23RAM[0]),          59,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},

    {CQua4_Re_T1_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          60,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua4_Re_T2_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          61,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua4_Re_T3_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          62,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua4_Re_T4_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          63,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua4_Re_T5_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          64,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua4_Re_T6_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          65,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua4_Re_T7_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          66,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua4_Re_T8_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          67,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua4_Re_T9_PreEn_0,           (ulong32)(&Str_3aTable_E23RAM[0]),          68,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua4_Re_T10_PreEn_0,          (ulong32)(&Str_3aTable_E23RAM[0]),          69,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua4_Re_T11_PreEn_0,          (ulong32)(&Str_3aTable_E23RAM[0]),          70,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua4_Re_T12_PreEn_0,          (ulong32)(&Str_3aTable_E23RAM[0]),          71,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},

    {CPosA_Ac_PreEn_0,              (ulong32)(&Str_3aTable_E23RAM[0]),          72,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CRevA_Ac_PreEn_0,              (ulong32)(&Str_3aTable_E23RAM[0]),          73,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua1A_Re_PreEn_0,             (ulong32)(&Str_3aTable_E23RAM[0]),          74,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua2A_Re_PreEn_0,             (ulong32)(&Str_3aTable_E23RAM[0]),          75,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua3A_Re_PreEn_0,             (ulong32)(&Str_3aTable_E23RAM[0]),          76,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua4A_Re_PreEn_0,             (ulong32)(&Str_3aTable_E23RAM[0]),          77,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},

    {CPosB_Ac_PreEn_0,              (ulong32)(&Str_3aTable_E23RAM[0]),          78,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CRevB_Ac_PreEn_0,              (ulong32)(&Str_3aTable_E23RAM[0]),          79,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua1B_Re_PreEn_0,             (ulong32)(&Str_3aTable_E23RAM[0]),          80,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua2B_Re_PreEn_0,             (ulong32)(&Str_3aTable_E23RAM[0]),          81,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua3B_Re_PreEn_0,             (ulong32)(&Str_3aTable_E23RAM[0]),          82,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua4B_Re_PreEn_0,             (ulong32)(&Str_3aTable_E23RAM[0]),          83,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},

    {CPosC_Ac_PreEn_0,              (ulong32)(&Str_3aTable_E23RAM[0]),          84,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CRevC_Ac_PreEn_0,              (ulong32)(&Str_3aTable_E23RAM[0]),          85,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua1C_Re_PreEn_0,             (ulong32)(&Str_3aTable_E23RAM[0]),          86,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua2C_Re_PreEn_0,             (ulong32)(&Str_3aTable_E23RAM[0]),          87,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua3C_Re_PreEn_0,             (ulong32)(&Str_3aTable_E23RAM[0]),          88,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CQua4C_Re_PreEn_0,             (ulong32)(&Str_3aTable_E23RAM[0]),          89,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},

#if 0   /*ע������������������ʶ���Ƶ��������*/
    {CM_Com_Ac_Tol_En_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          91,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CY_Com_Ac_Tol_En_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          92,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CChargeBal_Hex_Cent,           (ulong32)(&Str_3aTable_E23RAM[0]),          93,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CChargeBal_Hex_Full,           (ulong32)(&Str_3aTable_E23RAM[0]),          93,     C_CurrDataLen5,            C_W_Msg_EnergyMetering,             DT_Ti_E23_RAMCRC},
    {COverDraft_Hex_Cent,           (ulong32)(&Str_3aTable_E23RAM[0]),          94,     C_CurrDataLen5,            C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {COverDraft_Hex_Full,           (ulong32)(&Str_3aTable_E23RAM[0]),          94,     C_CurrDataLen5,            C_W_Msg_EnergyMetering,             DT_Ti_E23_RAMCRC},
    {CM_Pos_Ac_Tol_En_Pul_1,        (ulong32)(E2Addr_M_Pos_Ac_Tol_En_Pul_1),    0,      C_CurrDataLen5,            C_WR_Msg_SettleAccounts,            DT_E23_Clear},
    {CM_Rev_Ac_Tol_En_Pul_1,        (ulong32)(E2Addr_M_Rev_Ac_Tol_En_Pul_1),    0,      C_CurrDataLen5,            C_WR_Msg_SettleAccounts,            DT_E23_Clear},
#endif
};
#define Str_2Table_DIEn_Len  (sizeof(Str_2Table_DIEn)/sizeof(Str_2Table))

/***********���������**************/
const Str_2Table Str_2Table_DIDe10[]=
{ /* ���ݱ�ʾ                       ��Ӧ������ṹ�������ַ                    Ӧ�������к�  �������ݳ���              ��Ӧ��Ϣ�ż��Ƿ�֧�ֶ�             ��������    */
    {CPos_Ac_Tol_De_0,              (ulong32)(E2Addr_Pos_Ac_Tol_De_0),          0,      (CLPos_Ac_Tol_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CPos_Ac_T1_De_0,               (ulong32)(E2Addr_Pos_Ac_T1_De_0),           0,      (CLPos_Ac_T1_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CPos_Ac_T2_De_0,               (ulong32)(E2Addr_Pos_Ac_T2_De_0),           0,      (CLPos_Ac_T2_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CPos_Ac_T3_De_0,               (ulong32)(E2Addr_Pos_Ac_T3_De_0),           0,      (CLPos_Ac_T3_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CPos_Ac_T4_De_0,               (ulong32)(E2Addr_Pos_Ac_T4_De_0),           0,      (CLPos_Ac_T4_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CPos_Ac_T5_De_0,               (ulong32)(E2Addr_Pos_Ac_T5_De_0),           0,      (CLPos_Ac_T5_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CPos_Ac_T6_De_0,               (ulong32)(E2Addr_Pos_Ac_T6_De_0),           0,      (CLPos_Ac_T6_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CPos_Ac_T7_De_0,               (ulong32)(E2Addr_Pos_Ac_T7_De_0),           0,      (CLPos_Ac_T7_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CPos_Ac_T8_De_0,               (ulong32)(E2Addr_Pos_Ac_T8_De_0),           0,      (CLPos_Ac_T8_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CPos_Ac_T9_De_0,               (ulong32)(E2Addr_Pos_Ac_T9_De_0),           0,      (CLPos_Ac_T9_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CPos_Ac_T10_De_0,              (ulong32)(E2Addr_Pos_Ac_T10_De_0),          0,      (CLPos_Ac_T10_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CPos_Ac_T11_De_0,              (ulong32)(E2Addr_Pos_Ac_T11_De_0),          0,      (CLPos_Ac_T11_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CPos_Ac_T12_De_0,              (ulong32)(E2Addr_Pos_Ac_T12_De_0),          0,      (CLPos_Ac_T12_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},

    {CRev_Ac_Tol_De_0,              (ulong32)(E2Addr_Rev_Ac_Tol_De_0),          0,      (CLRev_Ac_Tol_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CRev_Ac_T1_De_0,               (ulong32)(E2Addr_Rev_Ac_T1_De_0),           0,      (CLRev_Ac_T1_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CRev_Ac_T2_De_0,               (ulong32)(E2Addr_Rev_Ac_T2_De_0),           0,      (CLRev_Ac_T2_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CRev_Ac_T3_De_0,               (ulong32)(E2Addr_Rev_Ac_T3_De_0),           0,      (CLRev_Ac_T3_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CRev_Ac_T4_De_0,               (ulong32)(E2Addr_Rev_Ac_T4_De_0),           0,      (CLRev_Ac_T4_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CRev_Ac_T5_De_0,               (ulong32)(E2Addr_Rev_Ac_T5_De_0),           0,      (CLRev_Ac_T5_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CRev_Ac_T6_De_0,               (ulong32)(E2Addr_Rev_Ac_T6_De_0),           0,      (CLRev_Ac_T6_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CRev_Ac_T7_De_0,               (ulong32)(E2Addr_Rev_Ac_T7_De_0),           0,      (CLRev_Ac_T7_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CRev_Ac_T8_De_0,               (ulong32)(E2Addr_Rev_Ac_T8_De_0),           0,      (CLRev_Ac_T8_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CRev_Ac_T9_De_0,               (ulong32)(E2Addr_Rev_Ac_T9_De_0),           0,      (CLRev_Ac_T9_De_0),             C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CRev_Ac_T10_De_0,              (ulong32)(E2Addr_Rev_Ac_T10_De_0),          0,      (CLRev_Ac_T10_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CRev_Ac_T11_De_0,              (ulong32)(E2Addr_Rev_Ac_T11_De_0),          0,      (CLRev_Ac_T11_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CRev_Ac_T12_De_0,              (ulong32)(E2Addr_Rev_Ac_T12_De_0),          0,      (CLRev_Ac_T12_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},

    {CQua1_Re_Tol_De_0,             (ulong32)(E2Addr_Qua1_Re_Tol_De_0),         0,      (CLQua1_Re_Tol_De_0),           C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua1_Re_T1_De_0,              (ulong32)(E2Addr_Qua1_Re_T1_De_0),          0,      (CLQua1_Re_T1_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua1_Re_T2_De_0,              (ulong32)(E2Addr_Qua1_Re_T2_De_0),          0,      (CLQua1_Re_T2_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua1_Re_T3_De_0,              (ulong32)(E2Addr_Qua1_Re_T3_De_0),          0,      (CLQua1_Re_T3_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua1_Re_T4_De_0,              (ulong32)(E2Addr_Qua1_Re_T4_De_0),          0,      (CLQua1_Re_T4_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua1_Re_T5_De_0,              (ulong32)(E2Addr_Qua1_Re_T5_De_0),          0,      (CLQua1_Re_T5_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua1_Re_T6_De_0,              (ulong32)(E2Addr_Qua1_Re_T6_De_0),          0,      (CLQua1_Re_T6_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua1_Re_T7_De_0,              (ulong32)(E2Addr_Qua1_Re_T7_De_0),          0,      (CLQua1_Re_T7_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua1_Re_T8_De_0,              (ulong32)(E2Addr_Qua1_Re_T8_De_0),          0,      (CLQua1_Re_T8_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua1_Re_T9_De_0,              (ulong32)(E2Addr_Qua1_Re_T9_De_0),          0,      (CLQua1_Re_T9_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua1_Re_T10_De_0,             (ulong32)(E2Addr_Qua1_Re_T10_De_0),         0,      (CLQua1_Re_T10_De_0),           C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua1_Re_T11_De_0,             (ulong32)(E2Addr_Qua1_Re_T11_De_0),         0,      (CLQua1_Re_T11_De_0),           C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua1_Re_T12_De_0,             (ulong32)(E2Addr_Qua1_Re_T12_De_0),         0,      (CLQua1_Re_T12_De_0),           C_WR_Msg_DemandMetering,            DT_E23_Clear},

    {CQua2_Re_Tol_De_0,             (ulong32)(E2Addr_Qua2_Re_Tol_De_0),         0,      (CLQua2_Re_Tol_De_0),           C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua2_Re_T1_De_0,              (ulong32)(E2Addr_Qua2_Re_T1_De_0),          0,      (CLQua2_Re_T1_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua2_Re_T2_De_0,              (ulong32)(E2Addr_Qua2_Re_T2_De_0),          0,      (CLQua2_Re_T2_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua2_Re_T3_De_0,              (ulong32)(E2Addr_Qua2_Re_T3_De_0),          0,      (CLQua2_Re_T3_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua2_Re_T4_De_0,              (ulong32)(E2Addr_Qua2_Re_T4_De_0),          0,      (CLQua2_Re_T4_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua2_Re_T5_De_0,              (ulong32)(E2Addr_Qua2_Re_T5_De_0),          0,      (CLQua2_Re_T5_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua2_Re_T6_De_0,              (ulong32)(E2Addr_Qua2_Re_T6_De_0),          0,      (CLQua2_Re_T6_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua2_Re_T7_De_0,              (ulong32)(E2Addr_Qua2_Re_T7_De_0),          0,      (CLQua2_Re_T7_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua2_Re_T8_De_0,              (ulong32)(E2Addr_Qua2_Re_T8_De_0),          0,      (CLQua2_Re_T8_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua2_Re_T9_De_0,              (ulong32)(E2Addr_Qua2_Re_T9_De_0),          0,      (CLQua2_Re_T9_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua2_Re_T10_De_0,             (ulong32)(E2Addr_Qua2_Re_T10_De_0),         0,      (CLQua2_Re_T10_De_0),           C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua2_Re_T11_De_0,             (ulong32)(E2Addr_Qua2_Re_T11_De_0),         0,      (CLQua2_Re_T11_De_0),           C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua2_Re_T12_De_0,             (ulong32)(E2Addr_Qua2_Re_T12_De_0),         0,      (CLQua2_Re_T12_De_0),           C_WR_Msg_DemandMetering,            DT_E23_Clear},

    {CQua3_Re_Tol_De_0,             (ulong32)(E2Addr_Qua3_Re_Tol_De_0),         0,      (CLQua3_Re_Tol_De_0),           C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua3_Re_T1_De_0,              (ulong32)(E2Addr_Qua3_Re_T1_De_0),          0,      (CLQua3_Re_T1_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua3_Re_T2_De_0,              (ulong32)(E2Addr_Qua3_Re_T2_De_0),          0,      (CLQua3_Re_T2_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua3_Re_T3_De_0,              (ulong32)(E2Addr_Qua3_Re_T3_De_0),          0,      (CLQua3_Re_T3_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua3_Re_T4_De_0,              (ulong32)(E2Addr_Qua3_Re_T4_De_0),          0,      (CLQua3_Re_T4_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua3_Re_T5_De_0,              (ulong32)(E2Addr_Qua3_Re_T5_De_0),          0,      (CLQua3_Re_T5_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua3_Re_T6_De_0,              (ulong32)(E2Addr_Qua3_Re_T6_De_0),          0,      (CLQua3_Re_T6_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua3_Re_T7_De_0,              (ulong32)(E2Addr_Qua3_Re_T7_De_0),          0,      (CLQua3_Re_T7_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua3_Re_T8_De_0,              (ulong32)(E2Addr_Qua3_Re_T8_De_0),          0,      (CLQua3_Re_T8_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua3_Re_T9_De_0,              (ulong32)(E2Addr_Qua3_Re_T9_De_0),          0,      (CLQua3_Re_T9_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua3_Re_T10_De_0,             (ulong32)(E2Addr_Qua3_Re_T10_De_0),         0,      (CLQua3_Re_T10_De_0),           C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua3_Re_T11_De_0,             (ulong32)(E2Addr_Qua3_Re_T11_De_0),         0,      (CLQua3_Re_T11_De_0),           C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua3_Re_T12_De_0,             (ulong32)(E2Addr_Qua3_Re_T12_De_0),         0,      (CLQua3_Re_T12_De_0),           C_WR_Msg_DemandMetering,            DT_E23_Clear},

    {CQua4_Re_Tol_De_0,             (ulong32)(E2Addr_Qua4_Re_Tol_De_0),         0,      (CLQua4_Re_Tol_De_0),           C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua4_Re_T1_De_0,              (ulong32)(E2Addr_Qua4_Re_T1_De_0),          0,      (CLQua4_Re_T1_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua4_Re_T2_De_0,              (ulong32)(E2Addr_Qua4_Re_T2_De_0),          0,      (CLQua4_Re_T2_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua4_Re_T3_De_0,              (ulong32)(E2Addr_Qua4_Re_T3_De_0),          0,      (CLQua4_Re_T3_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua4_Re_T4_De_0,              (ulong32)(E2Addr_Qua4_Re_T4_De_0),          0,      (CLQua4_Re_T4_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua4_Re_T5_De_0,              (ulong32)(E2Addr_Qua4_Re_T5_De_0),          0,      (CLQua4_Re_T5_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua4_Re_T6_De_0,              (ulong32)(E2Addr_Qua4_Re_T6_De_0),          0,      (CLQua4_Re_T6_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua4_Re_T7_De_0,              (ulong32)(E2Addr_Qua4_Re_T7_De_0),          0,      (CLQua4_Re_T7_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua4_Re_T8_De_0,              (ulong32)(E2Addr_Qua4_Re_T8_De_0),          0,      (CLQua4_Re_T8_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua4_Re_T9_De_0,              (ulong32)(E2Addr_Qua4_Re_T9_De_0),          0,      (CLQua4_Re_T9_De_0),            C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua4_Re_T10_De_0,             (ulong32)(E2Addr_Qua4_Re_T10_De_0),         0,      (CLQua4_Re_T10_De_0),           C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua4_Re_T11_De_0,             (ulong32)(E2Addr_Qua4_Re_T11_De_0),         0,      (CLQua4_Re_T11_De_0),           C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua4_Re_T12_De_0,             (ulong32)(E2Addr_Qua4_Re_T12_De_0),         0,      (CLQua4_Re_T12_De_0),           C_WR_Msg_DemandMetering,            DT_E23_Clear},

    {CPosA_Ac_De_0,                 (ulong32)(E2Addr_PosA_Ac_De_0),             0,      (CLPosA_Ac_De_0),               C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CRevA_Ac_De_0,                 (ulong32)(E2Addr_RevA_Ac_De_0),             0,      (CLRevA_Ac_De_0),               C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CComA_Re1_De_0,                (ulong32)(E2Addr_ComA_Re1_De_0),            0,      (CLComA_Re1_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CComA_Re2_De_0,                (ulong32)(E2Addr_ComA_Re2_De_0),            0,      (CLComA_Re2_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua1A_Re_De_0,                (ulong32)(E2Addr_Qua1A_Re_De_0),            0,      (CLQua1A_Re_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua2A_Re_De_0,                (ulong32)(E2Addr_Qua2A_Re_De_0),            0,      (CLQua2A_Re_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua3A_Re_De_0,                (ulong32)(E2Addr_Qua3A_Re_De_0),            0,      (CLQua3A_Re_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua4A_Re_De_0,                (ulong32)(E2Addr_Qua4A_Re_De_0),            0,      (CLQua4A_Re_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},

    {CPosB_Ac_De_0,                 (ulong32)(E2Addr_PosB_Ac_De_0),             0,      (CLPosB_Ac_De_0),               C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CRevB_Ac_De_0,                 (ulong32)(E2Addr_RevB_Ac_De_0),             0,      (CLRevB_Ac_De_0),               C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CComB_Re1_De_0,                (ulong32)(E2Addr_ComB_Re1_De_0),            0,      (CLComB_Re1_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CComB_Re2_De_0,                (ulong32)(E2Addr_ComB_Re2_De_0),            0,      (CLComB_Re2_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua1B_Re_De_0,                (ulong32)(E2Addr_Qua1B_Re_De_0),            0,      (CLQua1B_Re_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua2B_Re_De_0,                (ulong32)(E2Addr_Qua2B_Re_De_0),            0,      (CLQua2B_Re_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua3B_Re_De_0,                (ulong32)(E2Addr_Qua3B_Re_De_0),            0,      (CLQua3B_Re_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua4B_Re_De_0,                (ulong32)(E2Addr_Qua4B_Re_De_0),            0,      (CLQua4B_Re_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},

    {CPosC_Ac_De_0,                 (ulong32)(E2Addr_PosC_Ac_De_0),             0,      (CLPosC_Ac_De_0),               C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CRevC_Ac_De_0,                 (ulong32)(E2Addr_RevC_Ac_De_0),             0,      (CLRevC_Ac_De_0),               C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CComC_Re1_De_0,                (ulong32)(E2Addr_ComC_Re1_De_0),            0,      (CLComC_Re1_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CComC_Re2_De_0,                (ulong32)(E2Addr_ComC_Re2_De_0),            0,      (CLComC_Re2_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua1C_Re_De_0,                (ulong32)(E2Addr_Qua1C_Re_De_0),            0,      (CLQua1C_Re_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua2C_Re_De_0,                (ulong32)(E2Addr_Qua2C_Re_De_0),            0,      (CLQua2C_Re_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua3C_Re_De_0,                (ulong32)(E2Addr_Qua3C_Re_De_0),            0,      (CLQua3C_Re_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},
    {CQua4C_Re_De_0,                (ulong32)(E2Addr_Qua4C_Re_De_0),            0,      (CLQua4C_Re_De_0),              C_WR_Msg_DemandMetering,            DT_E23_Clear},
};
#define Str_2Table_DIDe10_Len  sizeof(Str_2Table_DIDe10)/sizeof(Str_2Table)

/***********������**************/
const Str_2Table Str_2Table_DIEvent20[]=
{ /* ���ݱ�ʾ                       ��Ӧ������ṹ�������ַ                    Ӧ�������к�  �������ݳ���              ��Ӧ��Ϣ�ż��Ƿ�֧�ֶ�             ��������    */

    /*ע�⣺����4������ͨѶ����������������㣬Ϊ�������Ч�ʣ����ڱ��ǰ�棬CY_Com_Ac_Tol_En_0����������4������������*/
    {CChargeBal_Hex_Cent,           (ulong32)(&Str_3aTable_E23RAM[0]),          93,     CLChargeBal_Hex_Deal,           C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {COverDraft_Hex_Cent,           (ulong32)(&Str_3aTable_E23RAM[0]),          94,     CLOverDraft_Hex_Deal,           C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CM_Com_Ac_Tol_En_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          91,     CLM_Com_Ac_Tol_En_Pul_0,        C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},
    {CY_Com_Ac_Tol_En_0,            (ulong32)(&Str_3aTable_E23RAM[0]),          92,     CLY_Com_Ac_Tol_En_Pul_0,        C_WR_Msg_EnergyMetering,            DT_Ti_E23_RAMCRC},

    {CPhaseC_Volage,                (ulong32)(&GV_PhaseA_Volage[0][0]),         0,      CLPhaseC_Volage,                C_WR_Msg_MeterIC,                   DT_RAM_DI0},
    {CPhaseFF_Volage,               (ulong32)(&GV_PhaseA_Volage[0][0]),         0,      CLPhaseFF_Volage,               C_Only_Read,                        DT_RAM},
    {CInstantC_AcPow,               (ulong32)(&GV_Instant_TolAcPow[0][0]),      0,      CLInstantC_AcPow,               C_WR_Msg_MeterIC,                   DT_RAM_DI0},
    {CInstantFF_AcPow,              (ulong32)(&GV_Instant_TolAcPow[0][0]),      0,      CLInstantFF_AcPow,              C_Only_Read,                        DT_RAM},
    {CInstantC_RePow ,              (ulong32)(&GV_Instant_TolRePow[0][0]),      0,      CLInstantC_RePow,               C_WR_Msg_MeterIC,                   DT_RAM_DI0},
    {CInstantFF_RePow,              (ulong32)(&GV_Instant_TolRePow[0][0]),      0,      CLInstantFF_RePow,              C_Only_Read,                        DT_RAM},
    {CInstantC_AppaPow,             (ulong32)(&GV_Instant_TolAppaPow[0][0]),    0,      CLInstantC_AppaPow,             C_WR_Msg_MeterIC,                   DT_RAM_DI0},
    {CInstantFF_AppaPow,            (ulong32)(&GV_Instant_TolAppaPow[0][0]),    0,      CLInstantFF_AppaPow,            C_Only_Read,                        DT_RAM},
    {CPhaseC_PowerFactor,           (ulong32)(&GV_Tol_PowerFactor[0][0]),       0,      CLPhaseC_PowerFactor,           C_WR_Msg_MeterIC,                   DT_RAM_DI0},
    {CPhaseFF_PowerFactor,          (ulong32)(&GV_Tol_PowerFactor[0][0]),       0,      CLPhaseFF_PowerFactor,          C_Only_Read,                        DT_RAM},
    {CPhaseC_Angle,                 (ulong32)(&GV_PhaseA_Angle[0][0]),          0,      CLPhaseC_Angle,                 C_WR_Msg_MeterIC,                   DT_RAM_DI0},
    {CPhaseFF_Angle,                (ulong32)(&GV_PhaseA_Angle[0][0]),          0,      CLPhaseFF_Angle,                C_Only_Read,                        DT_RAM},
    {CZero_Current,                 (ulong32)(&GV_Zero_Current[0]),             0,      CLZero_Current,                 C_WR_Msg_MeterIC,                   DT_RAM},
    {CElecNet_Freq,                 (ulong32)(&GV_ElecNet_Freq[0]),             0,      CLElecNet_Freq,                 C_WR_Msg_MeterIC,                   DT_RAM},
    {CCurr_AcDemand,                (ulong32)(&GV_Curr_AcDemand[0]),            0,      CLCurr_AcDemand,                C_WR_Msg_DemandMetering,            DT_RAM},
    {CCurr_ReDemand,                (ulong32)(&GV_Curr_ReDemand[0]),            0,      CLCurr_ReDemand,                C_WR_Msg_DemandMetering,            DT_RAM},
    {CMeter_Temp,                   (ulong32)(&GV_Meter_Temp[0]),               0,      CLMeter_Temp,                   C_WR_Msg_MeterIC,                   DT_RAM},
    {CCloc_Batt_Vol,                (ulong32)(&GV_Cloc_Batt_Vol[0]),            0,      CLCloc_Batt_Vol,                C_WR_Msg_BatteryVoltagleMetering,   DT_RAM},
    {CReadMeter_Batt_Vol,           (ulong32)(&GV_ReadMeter_Batt_Vol[0]),       0,      CLReadMeter_Batt_Vol,           C_WR_Msg_BatteryVoltagleMetering,   DT_RAM},
    {CBatt_Work_Time,               (ulong32)(E2Addr_Batt_Work_Time),           0,      CLBatt_Work_Time,               C_WR_Msg_Dispatch,                  DT_E23},
    {CCurr_Ladder_Price,            (ulong32)(&GV_Curr_Ladder_Price[0]),        0,      CLCurr_Ladder_Price,            C_WR_Msg_EnergyMetering,            DT_RAM},
    {CCurr_Price,                   (ulong32)(&GV_Curr_Price[0]),               0,      CLCurr_Price,                   C_WR_Msg_EnergyMetering,            DT_RAM},
    {CCurr_Rate_Price,              (ulong32)(&GV_Curr_Rate_Price[0]),          0,      CLCurr_Rate_Price,              C_WR_Msg_En_Deal,                   DT_RAMCRC},
    {CMeter_Work_State7,            (ulong32)(&GV_Meter_Work_State[0][0]),      0,      CLMeter_Work_State7,            C_WR_All,                           DT_RAM_DI0},
    {CControl_ExecuteState,         (ulong32)(E2Addr_Control_ExecuteState),     0,      CLControl_ExecuteState,         C_WR_Msg_Comm_Relay,                DT_E21},
    {CControl_ErrorState,           (ulong32)(E2Addr_Control_ErrorState),       0,      CLControl_ErrorState,           C_WR_Msg_Comm_Relay,                DT_E21},
#if 0
    {CControl_ExecuteStateUn,       (ulong32)(E2Addr_Control_ExecuteStateUn),   0,      CLControl_ExecuteStateUn,       C_WR_Msg_Comm_Relay,                DT_E21},
#endif
    {CVolC_Phase,                   (ulong32)(&GV_VolA_Phase[0][0]),            0,      CLVolC_Phase,                   C_WR_Msg_MeterIC,                   DT_RAM_DI0},
    {CVolFF_Phase,                  (ulong32)(&GV_VolA_Phase[0][0]),            0,      CLVolFF_Phase,                  C_Only_Read,                        DT_RAM},
    {CDrive_Report_Mode,            (ulong32)(&Str_3aTable_E23RAM[0]),          210,    CLDrive_Report_Mode,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CBuyCurr_TMoney,               (ulong32)(E2Addr_BuyCurr_TMoney),           0,      CLBuyCurr_TMoney,               C_WR_Msg_EnergyMetering,            DT_E23},
    {CDrive_Report_State,           (ulong32)(E2Drive_Report_State_New),        0,      CLDrive_Report_State_New,       C_WR_Msg_Communication,             DT_E21},
    {CDrive_Report_Type,            (ulong32)(&Str_3aTable_E23RAM[0]),          344,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CVector_Current ,              (ulong32)(&GV_Vector_Current[0]),           0,      CLVector_Current,               C_WR_Msg_MeterIC,                   DT_RAM},
};
#define Str_2Table_DIEvent20_Len  sizeof(Str_2Table_DIEvent20)/sizeof(Str_2Table)

const Str_2Table Str_2Table_DIEvent21[]=
{ /* ���ݱ�ʾ                       ��Ӧ������ṹ�������ַ                    Ӧ�������к�  �������ݳ���              ��Ӧ��Ϣ�ż��Ƿ�֧�ֶ�                 ��������    */
    {CVolA_Per_Pass_0,              (ulong32)(&GV_CurrMVolPerPass[1][0]),       0,      CLVolA_Per_Pass_M,		C_WR_Msg_VoltageQualifiedRateMetering,DT_RAMCRC},
    {CVolB_Per_Pass_0,              (ulong32)(&GV_CurrMVolPerPass[2][0]),       0,      CLVolB_Per_Pass_M,		C_WR_Msg_VoltageQualifiedRateMetering,DT_RAMCRC},
    {CVolC_Per_Pass_0,              (ulong32)(&GV_CurrMVolPerPass[3][0]),       0,      CLVolC_Per_Pass_M,		C_WR_Msg_VoltageQualifiedRateMetering,DT_RAMCRC},
    {CVolA_Per_Pass_0_Freeze,       (ulong32)(&GV_CurrDVolPerPass[1][0]),       0,      CLVolA_Per_Pass_D,		C_WR_Msg_VoltageQualifiedRateMetering,DT_RAMCRC},
    {CVolB_Per_Pass_0_Freeze,       (ulong32)(&GV_CurrDVolPerPass[2][0]),       0,      CLVolB_Per_Pass_D,		C_WR_Msg_VoltageQualifiedRateMetering,DT_RAMCRC},
    {CVolC_Per_Pass_0_Freeze,       (ulong32)(&GV_CurrDVolPerPass[3][0]),       0,      CLVolC_Per_Pass_D,		C_WR_Msg_VoltageQualifiedRateMetering,DT_RAMCRC},

};
#define Str_2Table_DIEvent21_Len  sizeof(Str_2Table_DIEvent21)/sizeof(Str_2Table)

/***********�¼���**************/
const Str_2Table Str_2Table_DIEvent30[]=
{ /* ���ݱ�ʾ                       ��Ӧ������ṹ�������ַ                    Ӧ�������к�  �������ݳ���              ��Ӧ��Ϣ�ż��Ƿ�֧�ֶ�             ��������    */
    {CLossVolage_Vol_UpLim,         (ulong32)(&Str_3aTable_E23RAM[0]),          141,    CLLossVolage_Vol_UpLim,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CLossVolage_Vol_LowLim,        (ulong32)(&Str_3aTable_E23RAM[0]),          142,    CLLossVolage_Vol_LowLim,        C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CLossVolage_Curr_LowLim,       (ulong32)(&Str_3aTable_E23RAM[0]),          143,    CLLossVolage_Curr_LowLim,       C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CLossVolage_Delay_T,           (ulong32)(&Str_3aTable_E23RAM[0]),          144,    CLLossVolage_Delay_T,           C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CLowVolage_Vol_UpLim,          (ulong32)(&Str_3aTable_E23RAM[0]),          145,    CLLowVolage_Vol_UpLim,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CLowVolage_Delay_T,            (ulong32)(&Str_3aTable_E23RAM[0]),          146,    CLLowVolage_Delay_T,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {COverVolage_Vol_LowLim,        (ulong32)(&Str_3aTable_E23RAM[0]),          147,    CLOverVolage_Vol_LowLim,        C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {COverVolage_Delay_T,           (ulong32)(&Str_3aTable_E23RAM[0]),          148,    CLOverVolage_Delay_T,           C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CBreakVol_Vol_UpLim,           (ulong32)(&Str_3aTable_E23RAM[0]),          149,    CLBreakVol_Vol_UpLim,           C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CBreakVol_Curr_UpLim,          (ulong32)(&Str_3aTable_E23RAM[0]),          150,    CLBreakVol_Curr_UpLim,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CBreakVol_Delay_T,             (ulong32)(&Str_3aTable_E23RAM[0]),          151,    CLBreakVol_Delay_T,             C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CNoBal_Vol_Lim,                (ulong32)(&Str_3aTable_E23RAM[0]),          152,    CLNoBal_Vol_Lim,                C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CNoBal_Vol_Delay_T,            (ulong32)(&Str_3aTable_E23RAM[0]),          153,    CLNoBal_Vol_Delay_T,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CNoBal_Curr_Lim,               (ulong32)(&Str_3aTable_E23RAM[0]),          154,    CLNoBal_Curr_Lim,               C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CNoBal_Curr_Delay_T,           (ulong32)(&Str_3aTable_E23RAM[0]),          155,    CLNoBal_Curr_Delay_T,           C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CSeriNoBal_Curr_Lim,           (ulong32)(&Str_3aTable_E23RAM[0]),          156,    CLSeriNoBal_Curr_Lim,           C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CSeriNoBal_Curr_Delay_T,       (ulong32)(&Str_3aTable_E23RAM[0]),          157,    CLSeriNoBal_Curr_Delay_T,       C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CLossCurr_Vol_LowLim,          (ulong32)(&Str_3aTable_E23RAM[0]),          158,    CLLossCurr_Vol_LowLim,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CLossCurr_Curr_UpLim,          (ulong32)(&Str_3aTable_E23RAM[0]),          159,    CLLossCurr_Curr_UpLim,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CLossCurr_Curr_LowLim,         (ulong32)(&Str_3aTable_E23RAM[0]),          160,    CLLossCurr_Curr_LowLim,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CLossCurr_Delay_T,             (ulong32)(&Str_3aTable_E23RAM[0]),          161,    CLLossCurr_Delay_T,             C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {COverCurr_Curr_LowLim,         (ulong32)(&Str_3aTable_E23RAM[0]),          162,    CLOverCurr_Curr_LowLim,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {COverCurr_Delay_T,             (ulong32)(&Str_3aTable_E23RAM[0]),          163,    CLOverCurr_Delay_T,             C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CBreakCurr_Vol_LowLim,         (ulong32)(&Str_3aTable_E23RAM[0]),          164,    CLBreakCurr_Vol_LowLim,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CBreakCurr_Curr_UpLim,         (ulong32)(&Str_3aTable_E23RAM[0]),          165,    CLBreakCurr_Curr_UpLim,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CBreakCurr_Delay_T,            (ulong32)(&Str_3aTable_E23RAM[0]),          166,    CLBreakCurr_Delay_T,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {COverLoad_AcPower_LowLim,      (ulong32)(&Str_3aTable_E23RAM[0]),          167,    CLOverLoad_AcPower_LowLim,      C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {COverLoad_Delay_T,             (ulong32)(&Str_3aTable_E23RAM[0]),          168,    CLOverLoad_Delay_T,             C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CPosAcDemandOv_De_LowLim,      (ulong32)(&Str_3aTable_E23RAM[0]),          169,    CLPosAcDemandOv_De_LowLim,      C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CPosAcDemandOv_Delay_T,        (ulong32)(&Str_3aTable_E23RAM[0]),          170,    CLPosAcDemandOv_Delay_T,        C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CRevAcDemandOv_De_LowLim,      (ulong32)(&Str_3aTable_E23RAM[0]),          171,    CLRevAcDemandOv_De_LowLim,      C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CRevAcDemandOv_Delay_T,        (ulong32)(&Str_3aTable_E23RAM[0]),          172,    CLRevAcDemandOv_Delay_T,        C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CReDemandOv_De_LowLim,         (ulong32)(&Str_3aTable_E23RAM[0]),          173,    CLReDemandOv_De_LowLim,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CReDemandOv_Delay_T,           (ulong32)(&Str_3aTable_E23RAM[0]),          174,    CLReDemandOv_Delay_T,           C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CPowerFactor_LowLim,           (ulong32)(&Str_3aTable_E23RAM[0]),          175,    CLPowerFactor_LowLim,           C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CPowerFactor_Delay_T,          (ulong32)(&Str_3aTable_E23RAM[0]),          176,    CLPowerFactor_Delay_T,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CPowerRev_AcPower_LowLim,      (ulong32)(&Str_3aTable_E23RAM[0]),          177,    CLPowerRev_AcPower_LowLim,      C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CPowerRev_Delay_T,             (ulong32)(&Str_3aTable_E23RAM[0]),          178,    CLPowerRev_Delay_T,             C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CNeutralAbnormal_Curr_LowLim,  (ulong32)(&Str_3aTable_E23RAM[0]),          179,    CLNeutralAbnormal_Curr_LowLim,  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CNeutralUnbalanceRate,         (ulong32)(&Str_3aTable_E23RAM[0]),          180,    CLNeutralUnbalanceRate,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CNeutralAbnormal_Delay_T,      (ulong32)(&Str_3aTable_E23RAM[0]),          181,    CLNeutralAbnormal_Delay_T,      C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CReversedVoltage_Delay_T,      (ulong32)(&Str_3aTable_E23RAM[0]),          182,    CLReversedVoltage_Delay_T,      C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CReversedCurrent_Delay_T,      (ulong32)(&Str_3aTable_E23RAM[0]),          183,    CLReversedCurrent_Delay_T,      C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CPowerOff_Delay_T,             (ulong32)(&Str_3aTable_E23RAM[0]),          184,    CLPowerOff_Delay_T,             C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CAux_Pow_Down_Delay_T,         (ulong32)(&Str_3aTable_E23RAM[0]),          185,    CLAux_Pow_Down_Delay_T,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CClockFa_Delay_T,              (ulong32)(&Str_3aTable_E23RAM[0]),          186,    CLClockFa_Delay_T,              C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CMeterFa_Delay_T,              (ulong32)(&Str_3aTable_E23RAM[0]),          187,    CLMeterFa_Delay_T,              C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CLossVolage_Report_Mode,       (ulong32)(&Str_3aTable_E23RAM[0]),          244,    CLLossVolage_Report_Mode,       C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CLowVolage_Report_Mode,        (ulong32)(&Str_3aTable_E23RAM[0]),          245,    CLLowVolage_Report_Mode,        C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {COverVolage_Report_Mode,       (ulong32)(&Str_3aTable_E23RAM[0]),          246,    CLOverVolage_Report_Mode,       C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CBreakVol_Report_Mode,         (ulong32)(&Str_3aTable_E23RAM[0]),          247,    CLBreakVol_Report_Mode,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CLossCurr_Report_Mode,         (ulong32)(&Str_3aTable_E23RAM[0]),          248,    CLLossCurr_Report_Mode,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {COverCurr_Report_Mode,         (ulong32)(&Str_3aTable_E23RAM[0]),          249,    CLOverCurr_Report_Mode,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CBreakCurr_Report_Mode,        (ulong32)(&Str_3aTable_E23RAM[0]),          250,    CLBreakCurr_Report_Mode,        C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CPowerRev_Report_Mode,         (ulong32)(&Str_3aTable_E23RAM[0]),          251,    CLPowerRev_Report_Mode,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {COverLoad_Report_Mode,         (ulong32)(&Str_3aTable_E23RAM[0]),          252,    CLOverLoad_Report_Mode,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CPosAcDemandOv_Report_Mode,    (ulong32)(&Str_3aTable_E23RAM[0]),          253,    CLPosAcDemandOv_Report_Mode,    C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CRevAcDemandOv_Report_Mode,    (ulong32)(&Str_3aTable_E23RAM[0]),          254,    CLRevAcDemandOv_Report_Mode,    C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CReDemandOv_Report_Mode,       (ulong32)(&Str_3aTable_E23RAM[0]),          255,    CLReDemandOv_Report_Mode,       C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CPowerFactor_Report_Mode,      (ulong32)(&Str_3aTable_E23RAM[0]),          256,    CLPowerFactor_Report_Mode,      C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CAllLossVolage_Report_Mode,    (ulong32)(&Str_3aTable_E23RAM[0]),          257,    CLAllLossVolage_Report_Mode,    C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CAuxPowDown_Report_Mode,       (ulong32)(&Str_3aTable_E23RAM[0]),          258,    CLAuxPowDown_Report_Mode,       C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CReversedVoltage_Report_Mode,  (ulong32)(&Str_3aTable_E23RAM[0]),          259,    CLReversedVoltage_Report_Mode,  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CReversedCurrent_Report_Mode,  (ulong32)(&Str_3aTable_E23RAM[0]),          260,    CLReversedCurrent_Report_Mode,  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CPowerOff_Report_Mode,         (ulong32)(&Str_3aTable_E23RAM[0]),          261,    CLPowerOff_Report_Mode,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgram_Report_Mode,          (ulong32)(&Str_3aTable_E23RAM[0]),          262,    CLProgram_Report_Mode,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CTolClear_Report_Mode,         (ulong32)(&Str_3aTable_E23RAM[0]),          263,    CLTolClear_Report_Mode,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CDemandClear_Report_Mode,      (ulong32)(&Str_3aTable_E23RAM[0]),          264,    CLDemandClear_Report_Mode,      C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CEventClear_Report_Mode,       (ulong32)(&Str_3aTable_E23RAM[0]),          265,    CLEventClear_Report_Mode,       C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CAdjTime_Report_Mode,          (ulong32)(&Str_3aTable_E23RAM[0]),          266,    CLAdjTime_Report_Mode,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgPT_Report_Mode,           (ulong32)(&Str_3aTable_E23RAM[0]),          267,    CLProgPT_Report_Mode,           C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgPZ_Report_Mode,           (ulong32)(&Str_3aTable_E23RAM[0]),          268,    CLProgPZ_Report_Mode,           C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgWRe_Report_Mode,          (ulong32)(&Str_3aTable_E23RAM[0]),          269,    CLProgWRe_Report_Mode,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgSettD_Report_Mode,        (ulong32)(&Str_3aTable_E23RAM[0]),          270,    CLProgSettD_Report_Mode,        C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {COpenW_Report_Mode,            (ulong32)(&Str_3aTable_E23RAM[0]),          271,    CLOpenW_Report_Mode,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {COpenCW_Report_Mode,           (ulong32)(&Str_3aTable_E23RAM[0]),          272,    CLOpenCW_Report_Mode,           C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CNoBalVol_Report_Mode,         (ulong32)(&Str_3aTable_E23RAM[0]),          273,    CLNoBalVol_Report_Mode,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CNoBalCurr_Report_Mode,        (ulong32)(&Str_3aTable_E23RAM[0]),          274,    CLNoBalCurr_Report_Mode,        C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CRelayOpen_Report_Mode,        (ulong32)(&Str_3aTable_E23RAM[0]),          275,    CLRelayOpen_Report_Mode,        C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CRelayClose_Report_Mode,       (ulong32)(&Str_3aTable_E23RAM[0]),          276,    CLRelayClose_Report_Mode,       C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgHol_Report_Mode,          (ulong32)(&Str_3aTable_E23RAM[0]),          277,    CLProgHol_Report_Mode,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgAcC_Report_Mode,          (ulong32)(&Str_3aTable_E23RAM[0]),          278,    CLProgAcC_Report_Mode,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgReC_Report_Mode,          (ulong32)(&Str_3aTable_E23RAM[0]),          279,    CLProgReC_Report_Mode,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgTPara_Report_Mode,        (ulong32)(&Str_3aTable_E23RAM[0]),          280,    CLProgTPara_Report_Mode,        C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgLad_Report_Mode,          (ulong32)(&Str_3aTable_E23RAM[0]),          281,    CLProgLad_Report_Mode,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CKey_Update_Report_Mode,       (ulong32)(&Str_3aTable_E23RAM[0]),          282,    CLKey_Update_Report_Mode,       C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CAbnorC_Report_Mode,           (ulong32)(&Str_3aTable_E23RAM[0]),          283,    CLAbnorC_Report_Mode,           C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CBuyCurr_Report_Mode,          (ulong32)(&Str_3aTable_E23RAM[0]),          284,    CLBuyCurr_Report_Mode,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CReturnMoney_Report_Mode,      (ulong32)(&Str_3aTable_E23RAM[0]),          285,    CLReturnMoney_Report_Mode,      C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CConMEndEn_Report_Mode,        (ulong32)(&Str_3aTable_E23RAM[0]),          286,    CLConMEndEn_Report_Mode,        C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CRelayFaEndEn_Report_Mode,     (ulong32)(&Str_3aTable_E23RAM[0]),          287,    CLRelayFaEndEn_Report_Mode,     C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CPowerFa_EndT_Report_Mode,     (ulong32)(&Str_3aTable_E23RAM[0]),          288,    CLPowerFa_EndT_Report_Mode,     C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CSeriNoBalCurr_Report_Mode,    (ulong32)(&Str_3aTable_E23RAM[0]),          289,    CLSeriNoBalCurr_Report_Mode,    C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CClockFault_Report_Mode,       (ulong32)(&Str_3aTable_E23RAM[0]),          290,    CLClockFault_Report_Mode,       C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CMeteringChipFault_Report_Mode,(ulong32)(&Str_3aTable_E23RAM[0]),          291,    CLMeteringChipFault_Report_Mode,C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CBroadcastTime_Report_Mode,    (ulong32)(&Str_3aTable_E23RAM[0]),          292,    CLBroadcastTime_Report_Mode,    C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CABnor_ZeroCurrent_Report_Mode,(ulong32)(&Str_3aTable_E23RAM[0]),          293,    CLABnor_ZeroCurrent_Report_Mode,C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CAll_Loss_Vol_Note_1,          (ulong32)(&Str_3d698EventTable_Flash[0]),   0,      CLAll_Loss_Vol_Note_1,          C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CAll_Loss_Vol_OADTab,          (ulong32)(&Str_3eTable_2E2[0]),             0,      C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CAux_Pow_Down_OADTab,          (ulong32)(&Str_3eTable_2E2[0]),             1,      C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CAux_Pow_Down_Note_1,          (ulong32)(&Str_3d698EventTable_Flash[0]),   1,      CLAux_Pow_Down_Note_1,          C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CPow_Down_OADTab,              (ulong32)(&Str_3eTable_2E2[0]),             2,      C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CPow_Down_Note_1,              (ulong32)(&Str_3d698EventTable_Flash[0]),   2,      CLPow_Down_Note_1,              C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CPos_Ac_De_Over_OADTab,        (ulong32)(&Str_3eTable_2E2[0]),             3,      C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CPos_Ac_De_Over_Note_1,        (ulong32)(&Str_3d698EventTable_Flash[0]),   3,      CLPos_Ac_De_Over_Note_1,        C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CRev_Ac_De_Over_OADTab,        (ulong32)(&Str_3eTable_2E2[0]),             4,      C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CRev_Ac_De_Over_Note_1,        (ulong32)(&Str_3d698EventTable_Flash[0]),   4,      CLRev_Ac_De_Over_Note_1,        C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CQua_Re_De_Over_OADTab,        (ulong32)(&Str_3eTable_2E2[0]),             5,      C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CQua1_Re_De_Over_Note_1,       (ulong32)(&Str_3d698EventTable_Flash[0]),   5,      CLQua1_Re_De_Over_Note_1,       C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CQua2_Re_De_Over_Note_1,       (ulong32)(&Str_3d698EventTable_Flash[0]),   6,      CLQua2_Re_De_Over_Note_1,       C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CQua3_Re_De_Over_Note_1,       (ulong32)(&Str_3d698EventTable_Flash[0]),   7,      CLQua3_Re_De_Over_Note_1,       C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CQua4_Re_De_Over_Note_1,       (ulong32)(&Str_3d698EventTable_Flash[0]),   8,      CLQua4_Re_De_Over_Note_1,       C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CLoss_Vol_OADTab,              (ulong32)(&Str_3eTable_2E2[0]),             6,      C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CLossAVol_FF_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   9,      CLLossAVol_FF_1,                C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CLossBVol_FF_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   10,     CLLossBVol_FF_1,                C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CLossCVol_FF_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   11,     CLLossCVol_FF_1,                C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CLow_Vol_OADTab,               (ulong32)(&Str_3eTable_2E2[0]),             7,      C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CLowAVol_FF_1,                 (ulong32)(&Str_3d698EventTable_Flash[0]),   12,     CLLowAVol_FF_1,                 C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CLowBVol_FF_1,                 (ulong32)(&Str_3d698EventTable_Flash[0]),   13,     CLLowBVol_FF_1,                 C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CLowCVol_FF_1,                 (ulong32)(&Str_3d698EventTable_Flash[0]),   14,     CLLowCVol_FF_1,                 C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {COver_Vol_OADTab,              (ulong32)(&Str_3eTable_2E2[0]),             8,      C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {COverAVol_FF_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   15,     CLOverAVol_FF_1,                C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {COverBVol_FF_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   16,     CLOverBVol_FF_1,                C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {COverCVol_FF_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   17,     CLOverCVol_FF_1,                C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CBreak_Vol_OADTab,             (ulong32)(&Str_3eTable_2E2[0]),             9,      C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CBreakAVol_FF_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   18,     CLBreakAVol_FF_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CBreakBVol_FF_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   19,     CLBreakBVol_FF_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CBreakCVol_FF_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   20,     CLBreakCVol_FF_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CRevPS_Vol_OADTab,             (ulong32)(&Str_3eTable_2E2[0]),             10,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CRevPSVol_FF_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   21,     CLRevPSVol_FF_1,                C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CRevPS_Curr_OADTab,            (ulong32)(&Str_3eTable_2E2[0]),             11,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CRevPSCurr_FF_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   22,     CLRevPSCurr_FF_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CNoBal_Vol_OADTab,             (ulong32)(&Str_3eTable_2E2[0]),             12,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CNoBalVol_FF_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   23,     CLNoBalVol_FF_1,                C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CNoBal_Curr_OADTab,            (ulong32)(&Str_3eTable_2E2[0]),             13,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CNoBalCurr_FF_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   24,     CLNoBalCurr_FF_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CSevNoBal_Curr_OADTab,         (ulong32)(&Str_3eTable_2E2[0]),             14,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CSevNoBalCurr_FF_1,            (ulong32)(&Str_3d698EventTable_Flash[0]),   25,     CLSevNoBalCurr_FF_1,            C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CLoss_Curr_OADTab,             (ulong32)(&Str_3eTable_2E2[0]),             15,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CLossACurr_FF_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   26,     CLLossACurr_FF_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CLossBCurr_FF_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   27,     CLLossBCurr_FF_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CLossCCurr_FF_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   28,     CLLossCCurr_FF_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {COver_Curr_OADTab,             (ulong32)(&Str_3eTable_2E2[0]),             16,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {COverACurr_FF_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   29,     CLOverACurr_FF_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {COverBCurr_FF_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   30,     CLOverBCurr_FF_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {COverCCurr_FF_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   31,     CLOverCCurr_FF_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CBreak_Curr_OADTab,            (ulong32)(&Str_3eTable_2E2[0]),             17,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CBreakACurr_FF_1,              (ulong32)(&Str_3d698EventTable_Flash[0]),   32,     CLBreakACurr_FF_1,              C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CBreakBCurr_FF_1,              (ulong32)(&Str_3d698EventTable_Flash[0]),   33,     CLBreakBCurr_FF_1,              C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CBreakCCurr_FF_1,              (ulong32)(&Str_3d698EventTable_Flash[0]),   34,     CLBreakCCurr_FF_1,              C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CPower_Rev_OADTab,             (ulong32)(&Str_3eTable_2E2[0]),             18,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CPowerTRev_FF_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   70,     CLPowerTRev_FF_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CPowerARev_FF_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   35,     CLPowerARev_FF_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CPowerBRev_FF_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   36,     CLPowerBRev_FF_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CPowerCRev_FF_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   37,     CLPowerCRev_FF_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {COver_Lo_OADTab,               (ulong32)(&Str_3eTable_2E2[0]),             19,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {COverALo_FF_1,                 (ulong32)(&Str_3d698EventTable_Flash[0]),   38,     CLOverALo_FF_1,                 C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {COverBLo_FF_1,                 (ulong32)(&Str_3d698EventTable_Flash[0]),   39,     CLOverBLo_FF_1,                 C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {COverCLo_FF_1,                 (ulong32)(&Str_3d698EventTable_Flash[0]),   40,     CLOverCLo_FF_1,                 C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CTol_Clear_OADTab,             (ulong32)(&Str_3eTable_2E2[0]),             20,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CTol_Clear_Note_1,             (ulong32)(&Str_3d698EventTable_Flash[0]),   41,     CLTol_Clear_Note_1,             C_WR_Msg_Communication,             DT_Flash_698EventTab},/*������ʱ�����������*/
    {CDe_Clear_OADTab,              (ulong32)(&Str_3eTable_2E2[0]),             21,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CDe_Clear_Note_1,              (ulong32)(&Str_3d698EventTable_Flash[0]),   42,     CLDe_Clear_Note_1,              C_WR_Msg_Communication,             DT_Flash_698EventTab},/*������ʱ�����������*/
    {CEven_Clear_OADTab,            (ulong32)(&Str_3eTable_2E2[0]),             22,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CEven_Clear_Note_1,            (ulong32)(&Str_3d698EventTable_Flash[0]),   43,     CLEven_Clear_Note_1,            C_WR_Msg_Communication,             DT_Flash_698EventTab},/*������ʱ�����������*/
    {CProgram_OADTab,               (ulong32)(&Str_3eTable_2E2[0]),             23,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CProgram_Note_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   44,     CLProgram_Note_1,               C_WR_Msg_Communication,             DT_Flash_698EventTab},/*������ʱ�����������*/
    {CAbnorC_OADTab,                (ulong32)(&Str_3eTable_2E2[0]),             24,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CAbnorC_Note_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   45,     CLAbnorC_Note_1,                C_WR_Msg_Card,                      DT_Flash_698EventTab},/*������ʱ�����������*/
    {CLawlessC_Degree,              (ulong32)(E2Addr_LawlessC_Degree),          0,      CLLawlessC_Degree,              C_WR_Msg_Card,                      DT_E23},
    {COpenW_OADTab,                 (ulong32)(&Str_3eTable_2E2[0]),             25,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {COpenW_Note_1,                 (ulong32)(&Str_3d698EventTable_Flash[0]),   46,     CLOpenW_Note_1,                 C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {COpenCW_OADTab,                (ulong32)(&Str_3eTable_2E2[0]),             26,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {COpenCW_Note_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   47,     CLOpenCW_Note_1,                C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CBuyCurr_OADTab,               (ulong32)(&Str_3eTable_2E2[0]),             27,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CBuyCurr_FF_Note_1,            (ulong32)(&Str_3d698EventTable_Flash[0]),   48,     CLBuyCurr_FF_Note_1,            C_WR_Msg_Comm_Card,                 DT_Flash_698EventTab},/*������ʱ�����������*/
    {CReturn_M_OADTab,              (ulong32)(&Str_3eTable_2E2[0]),             28,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CReturn_M_Note_1,              (ulong32)(&Str_3d698EventTable_Flash[0]),   49,     CLReturn_M_Note_1,              C_WR_Msg_Communication,             DT_Flash_698EventTab},/*������ʱ�����������*/
    {CConM_OADTab,                  (ulong32)(&Str_3eTable_2E2[0]),             29,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CConM_Note_1,                  (ulong32)(&Str_3d698EventTable_Flash[0]),   50,     CLConM_Note_1,                  C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CRelayFa_OADTab,               (ulong32)(&Str_3eTable_2E2[0]),             30,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CRelayFa_Note_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   51,     CLRelayFa_Note_1,               C_WR_Msg_Deal_RelayStatus,          DT_Flash_698EventTab},/*������ʱ�����������*/
    {CPowerFa_OADTab,               (ulong32)(&Str_3eTable_2E2[0]),             31,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CPowerFa_Note_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   52,     CLPowerFa_Note_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CRelayOpen_OADTab,             (ulong32)(&Str_3eTable_2E2[0]),             32,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CRelayOpen_FF_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   53,     CLRelayOpen_FF_1,               C_WR_Msg_Deal_RelayStatus,          DT_Flash_698EventTab},/*������ʱ�����������*/
    {CRelayClose_OADTab,            (ulong32)(&Str_3eTable_2E2[0]),             33,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CRelayClose_FF_1,              (ulong32)(&Str_3d698EventTable_Flash[0]),   54,     CLRelayClose_FF_1,              C_WR_Msg_Deal_RelayStatus,          DT_Flash_698EventTab},/*������ʱ�����������*/
    {CPFactorT_FF_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   55,     CLPFactorT_FF_1,                C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CPFactorA_FF_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   72,     CLPFactorA_FF_1,                C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CPFactorB_FF_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   73,     CLPFactorB_FF_1,                C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CPFactorC_FF_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   74,     CLPFactorC_FF_1,                C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CPFactorT_Over_OADTab,         (ulong32)(&Str_3eTable_2E2[0]),             34,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CAdjTime_Note_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   56,     CLAdjTime_Note_1,               C_WR_Msg_Communication,             DT_Flash_698EventTab},/*������ʱ�����������*/
    {CAdjTime_OADTab,               (ulong32)(&Str_3eTable_2E2[0]),             35,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CProgPT_Note_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   57,     CLProgPT_Note_1,                C_WR_Msg_Communication,             DT_Flash_698EventTab},/*������ʱ�����������*/
    {CProgPT_OADTab,                (ulong32)(&Str_3eTable_2E2[0]),             36,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CProgTZ_Note_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   58,     CLProgTZ_Note_1,                C_WR_Msg_Communication,             DT_Flash_698EventTab},/*������ʱ�����������*/
    {CProgTZ_OADTab,                (ulong32)(&Str_3eTable_2E2[0]),             37,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CProgWRe_Note_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   59,     CLProgWRe_Note_1,               C_WR_Msg_Communication,             DT_Flash_698EventTab},/*������ʱ�����������*/
    {CProgWRe_OADTab,               (ulong32)(&Str_3eTable_2E2[0]),             38,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CProgHol_Note_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   60,     CLProgHol_Note_1,               C_WR_Msg_Communication,             DT_Flash_698EventTab},/*������ʱ�����������*/
    {CProgHol_OADTab,               (ulong32)(&Str_3eTable_2E2[0]),             39,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CProgAcC_Note_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   61,     CLProgAcC_Note_1,               C_WR_Msg_Communication,             DT_Flash_698EventTab},/*������ʱ�����������*/
    {CProgAcC_OADTab,               (ulong32)(&Str_3eTable_2E2[0]),             40,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CProgReC_Note_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   62,     CLProgReC_Note_1,               C_WR_Msg_Communication,             DT_Flash_698EventTab},/*������ʱ�����������*/
    {CProgReC_OADTab,               (ulong32)(&Str_3eTable_2E2[0]),             41,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CProgSettD_Note_1,             (ulong32)(&Str_3d698EventTable_Flash[0]),   63,     CLProgSettD_Note_1,             C_WR_Msg_Communication,             DT_Flash_698EventTab},/*������ʱ�����������*/
    {CProgSettD_OADTab,             (ulong32)(&Str_3eTable_2E2[0]),             42,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CProgTPara_Note_1,             (ulong32)(&Str_3d698EventTable_Flash[0]),   64,     CLProgTPara_Note_1,             C_WR_Msg_Communication,             DT_Flash_698EventTab},/*������ʱ�����������*/
    {CProgTPara_OADTab,             (ulong32)(&Str_3eTable_2E2[0]),             43,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CProgLad_Note_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   65,     CLProgLad_Note_1,               C_WR_Msg_Communication,             DT_Flash_698EventTab},/*������ʱ�����������*/
    {CProgLad_OADTab,               (ulong32)(&Str_3eTable_2E2[0]),             44,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CProgKD_Note_1,                (ulong32)(&Str_3d698EventTable_Flash[0]),   66,     CLProgKD_Note_1,                C_WR_Msg_Communication,             DT_Flash_698EventTab},/*������ʱ�����������*/
    {CProgKD_OADTab,                (ulong32)(&Str_3eTable_2E2[0]),             45,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CMeterFa_Note_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   67,     CLMeterFa_Note_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CMeterFa_OADTab,               (ulong32)(&Str_3eTable_2E2[0]),             46,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CClockFa_Note_1,               (ulong32)(&Str_3d698EventTable_Flash[0]),   68,     CLClockFa_Note_1,               C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CClockFa_OADTab,               (ulong32)(&Str_3eTable_2E2[0]),             47,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CBroadcastTime_Note_1,         (ulong32)(&Str_3d698EventTable_Flash[0]),   69,     CLBroadcastTime_Note_1,         C_WR_Msg_Communication,             DT_Flash_698EventTab},/*������ʱ�����������*/
    {CBroadcastTime_OADTab,         (ulong32)(&Str_3eTable_2E2[0]),             48,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},
    {CNeutralCurrentAbnormal_Note_1,(ulong32)(&Str_3d698EventTable_Flash[0]),   71,     CLNeutralCurrentAbnormal_Note_1,C_WR_Msg_PowerNetworkMonitoring,    DT_Flash_698EventTab},/*������ʱ�����������*/
    {CNeutralCurrentAbnormal_OADTab,(ulong32)(&Str_3eTable_2E2[0]),             49,     C_698Event_OADTabLen,           C_WR_Msg_Communication,             DT_E23_OADTab},

    {CLossVolage_Report_Type,       (ulong32)(&Str_3aTable_E23RAM[0]),          294,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CLowVolage_Report_Type,        (ulong32)(&Str_3aTable_E23RAM[0]),          295,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {COverVolage_Report_Type,       (ulong32)(&Str_3aTable_E23RAM[0]),          296,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CBreakVol_Report_Type,         (ulong32)(&Str_3aTable_E23RAM[0]),          297,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CLossCurr_Report_Type,         (ulong32)(&Str_3aTable_E23RAM[0]),          298,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {COverCurr_Report_Type,         (ulong32)(&Str_3aTable_E23RAM[0]),          299,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CBreakCurr_Report_Type,        (ulong32)(&Str_3aTable_E23RAM[0]),          300,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CPowerRev_Report_Type,         (ulong32)(&Str_3aTable_E23RAM[0]),          301,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {COverLoad_Report_Type,         (ulong32)(&Str_3aTable_E23RAM[0]),          302,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CPosAcDemandOv_Report_Type,    (ulong32)(&Str_3aTable_E23RAM[0]),          303,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CRevAcDemandOv_Report_Type,    (ulong32)(&Str_3aTable_E23RAM[0]),          304,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CReDemandOv_Report_Type,       (ulong32)(&Str_3aTable_E23RAM[0]),          305,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CPowerFactor_Report_Type,      (ulong32)(&Str_3aTable_E23RAM[0]),          306,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CAllLossVolage_Report_Type,    (ulong32)(&Str_3aTable_E23RAM[0]),          307,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CAuxPowDown_Report_Type,       (ulong32)(&Str_3aTable_E23RAM[0]),          308,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CReversedVoltage_Report_Type,  (ulong32)(&Str_3aTable_E23RAM[0]),          309,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CReversedCurrent_Report_Type,  (ulong32)(&Str_3aTable_E23RAM[0]),          310,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CPowerOff_Report_Type,         (ulong32)(&Str_3aTable_E23RAM[0]),          311,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgram_Report_Type,          (ulong32)(&Str_3aTable_E23RAM[0]),          312,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CTolClear_Report_Type,         (ulong32)(&Str_3aTable_E23RAM[0]),          313,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CDemandClear_Report_Type,      (ulong32)(&Str_3aTable_E23RAM[0]),          314,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CEventClear_Report_Type,       (ulong32)(&Str_3aTable_E23RAM[0]),          315,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CAdjTime_Report_Type,          (ulong32)(&Str_3aTable_E23RAM[0]),          316,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgPT_Report_Type,           (ulong32)(&Str_3aTable_E23RAM[0]),          317,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgPZ_Report_Type,           (ulong32)(&Str_3aTable_E23RAM[0]),          318,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgWRe_Report_Type,          (ulong32)(&Str_3aTable_E23RAM[0]),          319,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgSettD_Report_Type,        (ulong32)(&Str_3aTable_E23RAM[0]),          320,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {COpenW_Report_Type,            (ulong32)(&Str_3aTable_E23RAM[0]),          321,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {COpenCW_Report_Type,           (ulong32)(&Str_3aTable_E23RAM[0]),          322,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CNoBalVol_Report_Type,         (ulong32)(&Str_3aTable_E23RAM[0]),          323,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CNoBalCurr_Report_Type,        (ulong32)(&Str_3aTable_E23RAM[0]),          324,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CRelayOpen_Report_Type,        (ulong32)(&Str_3aTable_E23RAM[0]),          325,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CRelayClose_Report_Type,       (ulong32)(&Str_3aTable_E23RAM[0]),          326,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgHol_Report_Type,          (ulong32)(&Str_3aTable_E23RAM[0]),          327,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgAcC_Report_Type,          (ulong32)(&Str_3aTable_E23RAM[0]),          328,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgReC_Report_Type,          (ulong32)(&Str_3aTable_E23RAM[0]),          329,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgTPara_Report_Type,        (ulong32)(&Str_3aTable_E23RAM[0]),          330,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CProgLad_Report_Type,          (ulong32)(&Str_3aTable_E23RAM[0]),          331,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CKey_Update_Report_Type,       (ulong32)(&Str_3aTable_E23RAM[0]),          332,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CAbnorC_Report_Type,           (ulong32)(&Str_3aTable_E23RAM[0]),          333,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CBuyCurr_Report_Type,          (ulong32)(&Str_3aTable_E23RAM[0]),          334,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CReturnMoney_Report_Type,      (ulong32)(&Str_3aTable_E23RAM[0]),          335,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CConMEndEn_Report_Type,        (ulong32)(&Str_3aTable_E23RAM[0]),          336,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CRelayFaEndEn_Report_Type,     (ulong32)(&Str_3aTable_E23RAM[0]),          337,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CPowerFa_EndT_Report_Type,     (ulong32)(&Str_3aTable_E23RAM[0]),          338,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CSeriNoBalCurr_Report_Type,    (ulong32)(&Str_3aTable_E23RAM[0]),          339,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CClockFault_Report_Type,       (ulong32)(&Str_3aTable_E23RAM[0]),          340,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CMeteringChipFault_Report_Type,(ulong32)(&Str_3aTable_E23RAM[0]),          341,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CBroadcastTime_Report_Type,    (ulong32)(&Str_3aTable_E23RAM[0]),          342,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CABnor_ZeroCurrent_Report_Type,(ulong32)(&Str_3aTable_E23RAM[0]),          343,    CLReport_Type,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
};
#define Str_2Table_DIEvent30_Len  sizeof(Str_2Table_DIEvent30)/sizeof(Str_2Table)

const Str_2Table Str_2Table_DIReport[]=
{ /* ���ݱ�ʾ                       ��Ӧ������ṹ�������ַ                    Ӧ�������к�  �������ݳ���          ��Ӧ��Ϣ�ż��Ƿ�֧�ֶ�     ��������   */
    {CNewReportList,                (ulong32)(E2NewReportList),                 0,      CLNewReportList,            C_WR_Msg_Communication,     DT_E21},
};
#define Str_2Table_DIReport_Len  sizeof(Str_2Table_DIReport)/sizeof(Str_2Table)

/***********�α�����**************/
const Str_2Table Str_2Table_DIParamChild40[]=
{ /* ���ݱ�ʾ                       ��Ӧ������ṹ�������ַ                    ��Ӧ�������к�   �������ݳ���           ��Ӧ��Ϣ�ż��Ƿ�֧�ֶ�              ��������   */
    {CChange_TZ_Time,               (ulong32)(&Str_3aTable_E23RAM[0]),          99,     CLChange_TZ_Time,               C_WR_Msg_Comm_Deal,                 DT_Ref_E23_RAMCRC},
    {CChange_PT_Time,               (ulong32)(&Str_3aTable_E23RAM[0]),          100,    CLChange_PT_Time,               C_WR_Msg_Comm_Deal,                 DT_Ref_E23_RAMCRC},
    {CChange_Rate,                  (ulong32)(&Str_3aTable_E23RAM[0]),          101,    CLChange_Rate,                  C_WR_Msg_Comm_Deal_Card,            DT_Ref_E23_RAMCRC},
    {CChange_Ladder,                (ulong32)(&Str_3aTable_E23RAM[0]),          102,    CLChange_Ladder,                C_WR_Msg_Comm_Deal_Card,            DT_Ref_E23_RAMCRC},

    {CYear_Zone_Num,                (ulong32)(&Str_3aTable_E23RAM[0]),          103,    CLYear_Zone_Num,                C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CDay_Table_Num,                (ulong32)(&Str_3aTable_E23RAM[0]),          104,    CLDay_Table_Num,                C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CDay_Time_Num,                 (ulong32)(&Str_3aTable_E23RAM[0]),          105,    CLDay_Time_Num,                 C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CRate_Num,                     (ulong32)(&Str_3aTable_E23RAM[0]),          106,    CLRate_Num,                     C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CHoliday_Num,                  (ulong32)(&Str_3aTable_E23RAM[0]),          107,    CLHoliday_Num,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CStep_Num,                     (ulong32)(&Str_3aTable_E23RAM[0]),          108,    CLStep_Num,                     C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

#if 0
    {CKey_Tol_Num,                  (ulong32)(&Str_3aTable_E23RAM[0]),          59,     CLKey_Tol_Num,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
#endif
    {CPowerOn_Dis_All_Time,         (ulong32)(&Str_3aTable_E23RAM[0]),          115,    CLPowerOn_Dis_All_Time,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CBacklightTime,                (ulong32)(&Str_3aTable_E23RAM[0]),          116,    CLBacklightTime,                C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*�������ʱ��*/
    {CSViewBacklightTime,           (ulong32)(&Str_3aTable_E23RAM[0]),          117,    CLSViewBacklightTime,           C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*��ʾ�鿴�������ʱ��*/
    {CNEScreenDisplay,              (ulong32)(&Str_3aTable_E23RAM[0]),          118,    CLNEScreenDisplay,              C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*�޵簴����Ļפ�����ʱ��*/
    {CEnergy_Decimal_Num,           (ulong32)(&Str_3aTable_E23RAM[0]),          119,    CLEnergy_Decimal_Num,           C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CPower_Decimal_Num,            (ulong32)(&Str_3aTable_E23RAM[0]),          120,    CLPower_Decimal_Num,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {C1And2Display,                 (ulong32)(&Str_3aTable_E23RAM[0]),          121,    CL1And2Display,                 C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*Һ���٢���������*/

    {CRatio_Curr_Tran,              (ulong32)(&Str_3aTable_E23RAM[0]),          122,    CLRatio_Curr_Tran,              C_WR_Msg_Comm_Card,                 DT_Ref_E23_RAMCRC},
    {CRatio_Vol_Tran,               (ulong32)(&Str_3aTable_E23RAM[0]),          123,    CLRatio_Vol_Tran,               C_WR_Msg_Comm_Card,                 DT_Ref_E23_RAMCRC},

    {CComm_Address,                 (ulong32)(&Str_3aTable_E23RAM[0]),          135,    CLComm_Address,                 C_WR_Msg_Communication,               DT_Ref_E23_RAMCRC},
    {CMeter_Num,                    (ulong32)(E2Addr_Meter_Num),                0,      CLMeter_Num,                    C_WR_Msg_Comm_Card,                 DT_E23},
    {CCustomer_Num,                 (ulong32)(E2Addr_Customer_Num),             0,      CLCustomer_Num,                 C_WR_Msg_Comm_Card,                 DT_E23},
    {CMeter_Position,               (ulong32)(E2Addr_Meter_Position),           0,      CLMeter_Position,               C_WR_Msg_Communication,             DT_E23},

    {CWeek_RestDay,                 (ulong32)(&Str_3aTable_E23RAM[0]),          131,    CLWeek_RestDay ,                C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CWeek_RestDay_DTable,          (ulong32)(&Str_3aTable_E23RAM[0]),          132,    CLWeek_RestDay_DTable,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CAlam2_Money,                  (ulong32)(&Str_3aTable_E23RAM[0]),          133,    CLAlam2_Money,                  C_WR_Msg_Comm_Card,                 DT_Ref_E23_RAMCRC_DI0},
    {CClose_Relay_Money,            (ulong32)(&Str_3aTable_E23RAM[0]),          134,    CLClose_Relay_Money,            C_WR_Msg_Comm_Card,                 DT_Ref_E23_RAMCRC_DI0},

    {CInset_Card_State,             (ulong32)(&GV_Inset_Card_State[0]),         0,      CLInset_Card_State,             C_WR_Msg_Card,                      DT_RAM},

    {CFirst_TZone_Data,             (ulong32)(E2Addr_First_TZone_Data),         0,      CLFirst_TZone_Data,             C_WR_Msg_Comm_Deal_Card,            DT_E23},
    {CFirst_TZone_8PT_Data,         (ulong32)(E2Addr_First_TZone_1PT_Data),     0,      CLFirst_TZone_8PT_Data,         C_WR_Msg_Comm_Deal_Card,            DT_E23_DI0},
    {CSec_TZone_Data,               (ulong32)(E2Addr_Sec_TZone_Data),           0,      CLSec_TZone_Data,               C_WR_Msg_Communication,             DT_E23},
    {CSec_TZone_8PT_Data,           (ulong32)(E2Addr_Sec_TZone_1PT_Data),       0,      CLSec_TZone_8PT_Data,           C_WR_Msg_Communication,             DT_E23_DI0},
    {CHolidy_PT_Table20,            (ulong32)(E2Addr_Holidy_PT_Table1),         0,      CLHolidy_PT_Table1,            	C_WR_Msg_Communication,             DT_E21_DI0},

    {CCurrent_Rate12_Price,         (ulong32)(&Str_3aTable_E23RAM[0]),          137,    CLCurrent_Rate4_Price,          C_Only_Read,                        DT_Ref_E23_RAMCRC_DI0},
    {CCurrent_RateFF_Price,         (ulong32)(&Str_3aTable_E23RAM[0]),          137,    CLCurrent_RateFF_Price,         C_W_Msg_Card_Deal,                  DT_W_Ref_E23_RAMCRC_Te},
    {CBackUp_Rate12_Price,          (ulong32)(&Str_3aTable_E23RAM[0]),          138,    CLBackUp_Rate4_Price,           C_Only_Read,                        DT_Ref_E23_RAMCRC_DI0},
    {CBackUp_RateFF_Price,          (ulong32)(&Str_3aTable_E23RAM[0]),          138,    CLBackUp_RateFF_Price,          C_W_Msg_Comm_Card,                  DT_W_Ref_E23_RAMCRC_Te},

    {CCurrent_Ladder_Table,         (ulong32)(&Str_3aTable_E23RAM[0]),          139,    CLCurrent_Ladder_Table,         C_WR_Msg_Card_Deal,                 DT_Ref_E23_RAMCRC},
    {CCurrent_Ladder_Table_LadNum,  (ulong32)(&Str_3aTable_E23RAM[0]),          139,    CLCurrent_Ladder_Table_LadNum,  C_Only_Read,                        DT_R_Ref_E23_RAMCRC_Lad},
    {CCurrent_Ladder_Table_LadPri,  (ulong32)(&Str_3aTable_E23RAM[0]),          139,    CLCurrent_Ladder_Table_LadPri,  C_Only_Read,                        DT_R_Ref_E23_RAMCRC_Lad},
    {CCurrent_Ladder_Table_LadSett, (ulong32)(&Str_3aTable_E23RAM[0]),          139,    CLCurrent_Ladder_Table_LadSett, C_Only_Read,                        DT_R_Ref_E23_RAMCRC_Lad},

    {CBackUp_Ladder_Table,          (ulong32)(&Str_3aTable_E23RAM[0]),          140,    CLBackUp_Ladder_Table,          C_WR_Msg_Comm_Card,                 DT_Ref_E23_RAMCRC},
    {CBackUp_Ladder_Table_LadNum,   (ulong32)(&Str_3aTable_E23RAM[0]),          140,    CLBackUp_Ladder_Table_LadNum,   C_Only_Read,                        DT_R_Ref_E23_RAMCRC_Lad},
    {CBackUp_Ladder_Table_LadPri,   (ulong32)(&Str_3aTable_E23RAM[0]),          140,    CLBackUp_Ladder_Table_LadPri,   C_Only_Read,                        DT_R_Ref_E23_RAMCRC_Lad},
    {CBackUp_Ladder_Table_LadSett,  (ulong32)(&Str_3aTable_E23RAM[0]),          140,    CLBackUp_Ladder_Table_LadSett,  C_Only_Read,                        DT_R_Ref_E23_RAMCRC_Lad},

    {CVoltage_UpLim,                (ulong32)(&Str_3aTable_E23RAM[0]),          188,    CLVoltage_UpLim  ,              C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CVoltage_LowLim,               (ulong32)(&Str_3aTable_E23RAM[0]),          189,    CLVoltage_LowLim ,              C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CVolage_Check_LowLim,          (ulong32)(&Str_3aTable_E23RAM[0]),          190,    CLVolage_Check_LowLim,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC_DI0},

    {CDate_Time,                    (ulong32)(&GV_Date_Time[0]),                0,      CLDate_Week_Time ,              C_WR_Msg_Comm_Dis,                  DT_RAM_Time_Data},
    {CBroadcastTimeOffset_Min,      (ulong32)(&Str_3aTable_E23RAM[0]),          95,     CLBroadcastTimeOffset_Min,      C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*�㲥Уʱƫ����Сֵ*/
    {CBroadcastTimeOffset_Max,      (ulong32)(&Str_3aTable_E23RAM[0]),          96,     CLBroadcastTimeOffset_Max,      C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*�㲥Уʱƫ�����ֵ*/
};
#define Str_2Table_DIParamChild40_Len  (sizeof(Str_2Table_DIParamChild40)/sizeof(Str_2Table))

const Str_2Table Str_2Table_DIParamChild41[]=
{ /* ���ݱ�ʾ                       ��Ӧ������ṹ�������ַ                    Ӧ�������к�  �������ݳ���              ��Ӧ��Ϣ�ż��Ƿ�֧�ֶ�             ��������    */
    {CDemand_Cycle,                 (ulong32)(&Str_3aTable_E23RAM[0]),          97,     CLDemand_Cycle,                 C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CSliding_Time,                 (ulong32)(&Str_3aTable_E23RAM[0]),          98,     CLSliding_Time,                 C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CManage_Code,                  (ulong32)(E2Addr_Manage_Code),              0,      CLManage_Code,                  C_WR_Msg_Communication,             DT_E23},
    {CRated_Vol,                    (ulong32)(E2Addr_Rated_Vol),                0,      CLRated_Vol,                    C_WR_Msg_Communication,             DT_E23},
    {CRated_Curr,                   (ulong32)(E2Addr_Rated_Curr),               0,      CLRated_Curr,                   C_WR_Msg_Communication,             DT_E23},
    {CMax_Curr,                     (ulong32)(E2Addr_Max_Curr),                 0,      CLMax_Curr,                     C_WR_Msg_Communication,             DT_E23},
    {CMin_Curr,                     (ulong32)(E2Addr_Min_Curr),                 0,      CLMin_Curr,                     C_WR_Msg_Communication,             DT_E23},
    {CTurn_Curr,                    (ulong32)(E2Addr_Turn_Curr),                0,      CLTurn_Curr,                    C_WR_Msg_Communication,             DT_E23},
    {CActive_Accur_Deg,             (ulong32)(E2Addr_Active_Accur_Deg),         0,      CLActive_Accur_Deg,             C_WR_Msg_Communication,             DT_E23},
    {CReactive_Accur_Deg ,          (ulong32)(E2Addr_Reactive_Accur_Deg),       0,      CLReactive_Accur_Deg,           C_WR_Msg_Communication,             DT_E23},
    {CMeter_Ac_Const,               (ulong32)(E2Addr_Meter_Ac_Const),           0,      CLMeter_Ac_Const,               C_WR_Msg_Communication,             DT_E23},
    {CMeter_Re_Const,               (ulong32)(E2Addr_Meter_Re_Const),           0,      CLMeter_Re_Const,               C_WR_Msg_Communication,             DT_E23},
    {CMeter_Model,                  (ulong32)(E2Addr_Meter_Model),              0,      CLMeter_Model,                  C_WR_Msg_Communication,             DT_E23},
    {CActive_Com_State,             (ulong32)(&Str_3aTable_E23RAM[0]),          124,    CLActive_Com_State,             C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CReactive_Com_State1,          (ulong32)(&Str_3aTable_E23RAM[0]),          125,    CLReactive_Com_State1,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CReactive_Com_State2,          (ulong32)(&Str_3aTable_E23RAM[0]),          126,    CLReactive_Com_State2,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CSettle_Day3,                  (ulong32)(E2Addr_Settle_Day1),              0,      CLSettle_Day3,                  C_WR_Msg_Communication,             DT_E23_DI0},
    {CSoftw_Record_Number,          (ulong32)(E2Addr_Softw_Record_Number),      0,      CLSoftw_Record_Number,          C_WR_Msg_Communication,             DT_E21},
    {CMeter_Work_Char1,             (ulong32)(&Str_3aTable_E23RAM[0]),          348,    CLMeter_Work_Char1,             C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
};
#define Str_2Table_DIParamChild41_Len  (sizeof(Str_2Table_DIParamChild41)/sizeof(Str_2Table))

const Str_2Table Str_2Table_DIParamChild43[]=
{ /* ���ݱ�ʾ                       ��Ӧ������ṹ�������ַ                    Ӧ�������к�  �������ݳ���              ��Ӧ��Ϣ�ż��Ƿ�֧�ֶ�             ��������   */
    {CFactory_Softw_Version,        (ulong32)(E2Addr_Factory_Softw_Version),    0,      CLFactory_Softw_Version,        C_WR_Msg_Communication,             DT_E21},
    {CFactory_Hardw_Version,        (ulong32)(E2Addr_Factory_Hardw_Version),    0,      CLFactory_Hardw_Version,        C_WR_Msg_Communication,             DT_E21},
    {CProd_Date,                    (ulong32)(E2Addr_Prod_Date),                0,      CLProd_Date,                    C_WR_Msg_Communication,             DT_E23},
    {CFactory_Number,               (ulong32)(E2Addr_Factory_Number),           0,      CLFactory_Number,               C_WR_Msg_Communication,             DT_E21},
    {CFactory_Softw_VersionDate,    (ulong32)(E2Addr_Factory_Softw_VersionDate),0,      CLFactory_Softw_VersionDate,    C_WR_Msg_Communication,             DT_E21},
    {CFactory_Hardw_VersionDate,    (ulong32)(E2Addr_Factory_Hardw_VersionDate),0,      CLFactory_Hardw_VersionDate,    C_WR_Msg_Communication,             DT_E21},
    {CFactory_ExternSign,           (ulong32)(E2Addr_Factory_ExternSign),       0,      CLFactory_ExternSign,           C_WR_Msg_Communication,             DT_E21},
    {CAllowFollowUpTell,            (ulong32)(E2Addr_AllowFollowUpTell),        0,      CLAllowFollowUpTell,            C_WR_Msg_Communication,             DT_E23},
    {CAllowAccordUpTell,            (ulong32)(E2Addr_AllowAccordUpTell),        0,      CLAllowAccordUpTell,            C_WR_Msg_Communication,             DT_E23},
    {CEquipmentDis,                 (ulong32)(E2Addr_EquipmentDis),             0,      CLEquipmentDis,                 C_WR_Msg_Communication,             DT_E21},
    {CAllowMasterCall,              (ulong32)(E2Addr_AllowMasterCall),          0,      CLAllowMasterCall,              C_WR_Msg_Communication,             DT_E23},
    {CMeter_CommPro2,               (ulong32)(E2Addr_Meter_CommPro1),           0,      CLMeter_CommPro1,               C_WR_Msg_Communication,             DT_E21_DI0},
    {CUpTellChannel,                (ulong32)(E2Addr_UpTellChannel),            0,      CLUpTellChannel,                C_WR_Msg_Communication,             DT_E23},
};
#define Str_2Table_DIParamChild43_Len  (sizeof(Str_2Table_DIParamChild43)/sizeof(Str_2Table))

const Str_2Table Str_2Table_DIParamChild44[]=
{/* ���ݱ�ʾ                        ��Ӧ������ṹ�������ַ                    ��Ӧ�������к� �������ݳ���              ��Ӧ��Ϣ�ż��Ƿ�֧�ֶ�             ��������   */
    {CAppProInformation,            (ulong32)(&Str_3aTable_E23RAM[0]),          211,    CLAppProInformation,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*Э��汾��Ϣ*/
    {CAppMaxReAPDU,                 (ulong32)(&Str_3aTable_E23RAM[0]),          212,    CLAppMaxReAPDU,                 C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*������APDU�ߴ�*/
    {CAppMaxSeAPDU,                 (ulong32)(&Str_3aTable_E23RAM[0]),          213,    CLAppMaxSeAPDU,                 C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*�����APDU�ߴ�*/
    {CAppMaxHandleAPDU,             (ulong32)(&Str_3aTable_E23RAM[0]),          214,    CLAppMaxHandleAPDU,             C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*���ɴ���APDU�ߴ�*/
    {CAppProConsistency,            (ulong32)(&Str_3aTable_E23RAM[0]),          215,    CLAppProConsistency,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*Э��һ���Կ�*/
    {CAppFunConsistency,            (ulong32)(&Str_3aTable_E23RAM[0]),          216,    CLAppFunConsistency,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*����һ���Կ�*/
    {CAppStaticTimeout,             (ulong32)(&Str_3aTable_E23RAM[0]),          217,    CLAppStaticTimeout,             C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*��̬��ʱʱ��*/
    {CAppStaticTimeout_termal,      (ulong32)(&Str_3aTable_E23RAM[0]),          218,    CLAppStaticTimeout,             C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*�ն˾�̬��ʱʱ��*/
    {CConAutheMechanism,            (ulong32)(&Str_3aTable_E23RAM[0]),          219,    CLConAutheMechanism,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*������֤����*/
    {C698Key,                       (ulong32)(E2Addr_698Key),                   0,      CL698Key,                       C_WR_Msg_Communication,             DT_E23},
    {CClientAddr,                   (ulong32)(E2Addr_ClientAddr),               0,      CLClientAddr,                   C_WR_Msg_Communication,             DT_E21},
};
#define Str_2Table_DIParamChild44_Len (sizeof(Str_2Table_DIParamChild44)/sizeof(Str_2Table))

const Str_2Table Str_2Table_DIParamChild45[]=
{ /* ���ݱ�ʾ                   ��Ӧ������ṹ�������ַ                        Ӧ�������к�  �������ݳ���              ��Ӧ��Ϣ�ż��Ƿ�֧�ֶ�             ��������    */
    {CGPS_Signal,                   (ulong32)(&GV_GPS_Signal[0]),               0,      CLGPS_Signal,                   C_WR_Msg_Communication,             DT_RAM},
};
#define Str_2Table_DIParamChild45_Len  (sizeof(Str_2Table_DIParamChild45)/sizeof(Str_2Table))

const Str_2Table Str_2Table_DIParamChild80[]=
{/* ���ݱ�ʾ                        ��Ӧ������ṹ�������ַ                   Ӧ�������к�  �������ݳ���               ��Ӧ��Ϣ�ż��Ƿ�֧�ֶ�             ��������   */
#if 0
    {CRelay_Delay_Time,             (ulong32)(&Str_3aTable_E23RAM[0]),          90,     CLRelay_Delay_Time,             C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
#endif
    {CRelay_Open_CurrTreshold,      (ulong32)(&Str_3aTable_E23RAM[0]),          136,    CLRelay_Open_CurrTreshold,      C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CRelay_Open_CurrTimer,         (ulong32)(&Str_3aTable_E23RAM[0]),          204,    CLRelay_Open_CurrTimer,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
};
#define Str_2Table_DIParamChild80_Len  (sizeof(Str_2Table_DIParamChild80)/sizeof(Str_2Table))

const Str_2Table Str_2Table_DIParameterF1[]=
{ /* ���ݱ�ʾ                       ��Ӧ������ṹ�������ַ                    Ӧ�������к�  �������ݳ���              ��Ӧ��Ϣ�ż��Ƿ�֧�ֶ�             ��������    */
    {CID_Auth_Remain_Time,          (ulong32)(&GV_ID_Auth_Remain_Time[0]),      0,      CLID_Auth_Remain_Time,          C_WR_Msg_Communication,             DT_RAM},
    {CSafeModePara,                 (ulong32)(&Str_3aTable_E23RAM[0]),          220,    CLSafeModePara,                 C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*��ȫģʽ����*/
#if 0
    {CKey_State,                    (ulong32)(&Str_3aTable_E23RAM[0]),          68,     CLKey_State,                    C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
#endif
    {CSafeModeParaNat3,             (ulong32)(E2Addr_SafeModeParaNat3),         0,      CLSafeModeParaNat3,             C_WR_Msg_Communication,             DT_E21CRC_MaxLen},
    {C_IRAuth_Timer,                (ulong32)(&Str_3aTable_E23RAM[0]),          205,    CL_IRAuth_Timer,                C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CInfra_Auth_Remain_Time,       (ulong32)(&GV_Infra_Auth_Remain_Time[0]),   0,      CLInfra_Auth_Remain_Time,       C_WR_Msg_Communication,             DT_RAM},
    {CID_Auth_T_Remain_Time,        (ulong32)(&GV_ID_Auth_T_Remain_Time[0]),    0,      CLInfra_Auth_Remain_Time,       C_WR_Msg_Communication,             DT_RAM},
};
#define Str_2Table_DIParameterF1_Len  sizeof(Str_2Table_DIParameterF1)/sizeof(Str_2Table)

const Str_2Table Str_2Table_DIParamChildF2[]=
{/* ���ݱ�ʾ                        ��Ӧ������ṹ�������ַ                    Ӧ�������к�  �������ݳ���              ��Ӧ��Ϣ�ż��Ƿ�֧�ֶ�             ��������   */
    {COne485_Baud,                  (ulong32)(&Str_3aTable_E23RAM[0]),          128,    CLOne485_Baud,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CTwo485_Baud,                  (ulong32)(&Str_3aTable_E23RAM[0]),          129,    CLTwo485_Baud,                  C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CModular_Baud,                 (ulong32)(&Str_3aTable_E23RAM[0]),          130,    CLModular_Baud,                 C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
};
#define Str_2Table_DIParamChildF2_Len (sizeof(Str_2Table_DIParamChildF2)/sizeof(Str_2Table))

const Str_2Table Str_2Table_DIParamChildF3[]=
{ /* ���ݱ�ʾ                   ��Ӧ������ṹ�������ַ                        ��Ӧ�������к� �������ݳ���             ��Ӧ��Ϣ�ż��Ƿ�֧�ֶ�              ��������    */
    {CAuto_Dis_99ScreenCode,        (ulong32)(E2Addr_Auto_Dis_1ScreenCode),     0,      CLAuto_Dis_99ScreenCode,        C_WR_Msg_Communication,             DT_E21CRC_DI0},
    {CPer_Dis_Screen_Time,          (ulong32)(&Str_3aTable_E23RAM[0]),          109,    CLPer_Dis_Screen_Time,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CAuto_Dis_Screen_Num,          (ulong32)(&Str_3aTable_E23RAM[0]),          110,    CLAuto_Dis_Screen_Num,          C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},

    {CKey_Dis_99ScreenCode,         (ulong32)(E2Addr_Key_Dis_1ScreenCode),      0,      CLKey_Dis_99ScreenCode,         C_WR_Msg_Communication,             DT_E21CRC_DI0},
    {CPerkey_Dis_Screen_Time,       (ulong32)(&Str_3aTable_E23RAM[0]),          112,    CLPerkey_Dis_Screen_Time,       C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CKey_CycDis_Screen_Num,        (ulong32)(&Str_3aTable_E23RAM[0]),          113,    CLKey_CycDis_Screen_Num,        C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
};
#define Str_2Table_DIParamChildF3_Len (sizeof(Str_2Table_DIParamChildF3)/sizeof(Str_2Table))

const Str_2Table Str_2Table_DIParam00[]=
{   /* ���ݱ�ʾ                     ��Ӧ������ṹ�������ַ                   Ӧ�������к�  �������ݳ���              ��Ӧ��Ϣ�ż��Ƿ�֧�ֶ�              ��������   */
    /*645��Լ֧�֣�698��Լ��֧�֣����ɰ���645���ݱ�ʶ����*/
    {CProt_Version_Num,             (ulong32)(E2Addr_Prot_Version_Num),         0,      CLProt_Version_Num,             C_WR_Msg_Communication,             DT_E23},
    {CKey_4_Class,                  (ulong32)(E2Addr_Key_0_Class),              0,      CLKey_4_Class,                  C_WR_Msg_Comm_Dis,                  DT_E23_DI0},
    {CRst_ReportState_Timer,        (ulong32)(&Str_3aTable_E23RAM[0]),          203,    CLRst_ReportState_Timer,        C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
#if 0
    {CTiming_Freeze_Time,           (ulong32)(&Str_3aTable_E23RAM[0]),          89,     CLTiming_Freeze_Time,           C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
#endif
    {CRelay_Delay_Time_645,         (ulong32)(&Str_3aTable_E23RAM[0]),          345,    CLRelay_Delay_Time_645,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CDrive_Report_Mode_645,        (ulong32)(&Str_3aTable_E23RAM[0]),          346,    CLDrive_Report_Mode_645,        C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CMeter_Work_Char1_645,         (ulong32)(&Str_3aTable_E23RAM[0]),          347,    CLMeter_Work_Char1_645,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
};
#define Str_2Table_DIParam00_Len  (sizeof(Str_2Table_DIParam00)/sizeof(Str_2Table))

/***********�α����࣬2����ּ���**************/
typedef struct
{
    ulong32 PStr_2TableParamChildAddr;  /*2����ּ���**/
    ushort16 V_Str_2TableLen;           /*2����ּ���--�ṹ�����ݳ���*/
    uchar8 V_DI2;                       /*���ݱ�ʶDI2*/
}Str_2TableChild;
const Str_2TableChild Str_2Table_DIParamChild[]=
{/* 2����ּ���                                2����ּ���--�ṹ�����ݳ���        V_DI2*/
   {(ulong32)(Str_2Table_DIParam00),            Str_2Table_DIParam00_Len,          0x00},

};
#define Str_2Table_DIParamChild_Len  sizeof(Str_2Table_DIParamChild)/sizeof(Str_2TableChild)

/***********������**************/
const Str_2Table    Str_2Table_DIParameterFF[]=
{
    /*��������*/
    /*ע�⣺����2������ͨѶ����������������㣬Ϊ�������Ч�ʣ����ڱ��ǰ�棬CM_Rev_Ac_Tol_En_Pul_1����������2������������*/
    {CM_Pos_Ac_Tol_En_Pul_1,        (ulong32)(E2Addr_M_Pos_Ac_Tol_En_Pul_1),    0,      CLM_Pos_Ac_Tol_En_Pul_1,        C_WR_Msg_SettleAccounts,            DT_E23_Clear},
    {CM_Rev_Ac_Tol_En_Pul_1,        (ulong32)(E2Addr_M_Rev_Ac_Tol_En_Pul_1),    0,      CLM_Rev_Ac_Tol_En_Pul_1,        C_WR_Msg_SettleAccounts,            DT_E23_Clear},
    {CChargeBal_Hex_Full,           (ulong32)(&Str_3aTable_E23RAM[0]),          93,     CLChargeBal_Hex_Full,           C_WR_Msg_EnergyMetering,             DT_Ti_E23_RAMCRC},
    {COverDraft_Hex_Full,           (ulong32)(&Str_3aTable_E23RAM[0]),          94,     CLOverDraft_Hex_Full,           C_WR_Msg_EnergyMetering,             DT_Ti_E23_RAMCRC},

    /*������*/
    {COneMin_AcPower_C_Pre,         (ulong32)(&GV_OneMin_AcPower[0][0]),        0,      CLOneMin_AcPower,               C_WR_Msg_MeterIC,            		DT_RAM_DI0},
    {COneMin_AcPower_Pre_FF,        (ulong32)(&GV_OneMin_AcPower[0][0]),        0,      CLOneMin_AcPower_FF,            C_Only_Read,                        DT_RAM},
    {COneMin_RePower_C_Pre,         (ulong32)(&GV_OneMin_RePower[0][0]),        0,      CLOneMin_RePower,               C_WR_Msg_MeterIC,            		DT_RAM_DI0},
    {COneMin_RePower_Pre_FF,        (ulong32)(&GV_OneMin_RePower[0][0]),        0,      CLOneMin_RePower_FF,            C_Only_Read,                        DT_RAM},

    {CSoftI_J_RemainTime,           (ulong32)(FRAMAddr_SoftI_J_RemainTime),     0,      CLSoftI_J_RemainTime,           C_WR_Msg_Communication,             DT_FRAM1CRC},
    {CCurrMon_Vol_Pass_Time,        (ulong32)(&GV_CurrMon_Vol_Pass_Time[0]),    0,      CLCurrMon_Vol_Pass_Time,        C_WR_Msg_VoltageQualifiedRateMetering,DT_RAM},
    {CCurr_Rate_No,                 (ulong32)(&GV_Curr_Rate_No[0]),             0,      CLCurr_Rate_No,                 C_WR_Msg_Deal_MultiRates,           DT_RAM},
    {CCurr_Step_No,                 (ulong32)(&GV_Curr_Step_No[0]),             0,      CLCurr_Step_No,                 C_WR_Msg_EnergyMetering,            DT_RAM},
    {CEnter_LowPower_Time,          (ulong32)(FRAMAddr_Enter_LowPower_Time),    0,      CLEnter_LowPower_Time,          C_WR_Msg_Dispatch,                  DT_FRAM1CRC},
    {CExit_LowPower_Time,           (ulong32)(FRAMAddr_Exit_LowPower_Time),     0,      CLExit_LowPower_Time,           C_WR_Msg_Dispatch,                  DT_FRAM1CRC},
    {CCurrC_Phase,                  (ulong32)(&GV_CurrA_Phase[0][0]),           0,      CLCurrC_Phase,                  C_WR_Msg_MeterIC,                   DT_RAM_DI0},
    {CPhaseC_Curr_4Dig,             (ulong32)(&GV_PhaseA_Curr_4Dig[0][0]),      0,      CLPhaseC_Curr_4Dig,             C_WR_Msg_MeterIC,                   DT_RAM_DI0},
    {CPhaseFF_Curr_4Dig,            (ulong32)(&GV_PhaseA_Curr_4Dig[0][0]),      0,      CLPhaseFF_Curr_4Dig,            C_Only_Read,                        DT_RAM},
    {CRemote_Local_State,           (ulong32)(&Str_3aTable_E23RAM[0]),          209,    CLRemote_Local_State,           C_WR_Msg_Comm_Card,                 DT_Ref_E23_RAMCRC},
    {CReadMeter_Batt_LowState,      (ulong32)(E2Addr_Cloc_Batt_LowState),       0,      CLReadMeter_Batt_LowState,      C_WR_Msg_BatteryVoltagleMetering,   DT_E23_DI0},
    {CESAM_FaultState,              (ulong32)(E2Addr_ESAM_FaultState),          0,      CLESAM_FaultState,              C_WR_Msg_Esam,                      DT_E23},
    {CClock_FaultState,             (ulong32)(E2Addr_Clock_FaultState),         0,      CLClock_FaultState,             C_WR_Msg_Dispatch,                  DT_E23},
    {CReportNewAddNum,              (ulong32)(E2Addr_ReportNewAddNum),          0,      CLReportNewAddNum,              C_WR_Msg_Communication,             DT_E23},
    {CHaveReportState,              (ulong32)(E2Addr_HaveReportState),          0,      CLHaveReportState,              C_WR_Msg_Communication,             DT_E23},
    {CCap_Vol,                      (ulong32)(&GV_Cap_Vol[0]),                  0,      CLCap_Vol,                      C_WR_Msg_BatteryVoltagleMetering,   DT_RAM},
    {CID_Auth_Remain_Time_645,      (ulong32)(&GV_ID_Auth_Remain_Time_645[0]),  0,      CLID_Auth_Remain_Time_645,      C_WR_Msg_Communication,             DT_RAM},
    {CInfra_Auth_Remain_Time_645,   (ulong32)(&GV_Infra_Auth_Remain_Time_645[0]),0,     CLInfra_Auth_Remain_Time_645,   C_WR_Msg_Communication,             DT_RAM},
    {CClock_FaultTime,              (ulong32)(E2Addr_Clock_FaultTime),          0,      CLClock_FaultTime,              C_WR_Msg_Communication,             DT_E21},
    {CDoubleAgreementFlag,          (ulong32)(E2Addr_CDoubleAgreementFlag),     0,      CLDoubleAgreementFlag,          C_WR_Msg_Communication,             DT_E21},
    /*�α�����*/
    {CAlarm_Status,                 (ulong32)(&Str_3aTable_E23RAM[0]),          202,    CLAlarm_Status,                 C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CNeutralCurrentAbnormal_OADTabLen,  (ulong32)(E2Addr_All_Loss_Vol_OADTabLen),   0,      CLNeutralCurrentAbnormal_OADTabLen,  C_WR_Msg_Communication,             DT_E23_DI0},
    {CL_Free_OADTabLen_T,           (ulong32)(&Str_3aTable_E23RAM[0]),          221,    CLI_Free_OADTabLen_T,           C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC_DI0},
    {CI_Free_OADTab,                (ulong32)(&Str_3aTable_E23RAM[0]),          233,    C_698Free_OADTabLen,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*��2�������ж����⴦��*/
    {CMin_Free_OADTab,              (ulong32)(&Str_3aTable_E23RAM[0]),          234,    C_698Free_OADTabLen,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*��2�������ж����⴦��*/
    {CH_Free_OADTab,                (ulong32)(&Str_3aTable_E23RAM[0]),          235,    C_698Free_OADTabLen,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*��2�������ж����⴦��*/
    {CD_Free_OADTab,                (ulong32)(&Str_3aTable_E23RAM[0]),          236,    C_698Free_OADTabLen,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*��2�������ж����⴦��*/
    {CSett_Free_OADTab,             (ulong32)(&Str_3aTable_E23RAM[0]),          237,    C_698Free_OADTabLen,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*��2�������ж����⴦��*/
    {CM_Free_OADTab,                (ulong32)(&Str_3aTable_E23RAM[0]),          238,    C_698Free_OADTabLen,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*��2�������ж����⴦��*/
    {CYSettle_Free_OADTab,          (ulong32)(&Str_3aTable_E23RAM[0]),          239,    C_698Free_OADTabLen,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*��2�������ж����⴦��*/
    {CTZ_Free_OADTab,               (ulong32)(&Str_3aTable_E23RAM[0]),          240,    C_698Free_OADTabLen,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*��2�������ж����⴦��*/
    {CPT_Free_OADTab,               (ulong32)(&Str_3aTable_E23RAM[0]),          241,    C_698Free_OADTabLen,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*��2�������ж����⴦��*/
    {CR_Free_OADTab,                (ulong32)(&Str_3aTable_E23RAM[0]),          242,    C_698Free_OADTabLen,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*��2�������ж����⴦��*/
    {CL_Free_OADTab,                (ulong32)(&Str_3aTable_E23RAM[0]),          243,    C_698Free_OADTabLen,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},/*��2�������ж����⴦��*/
    {CZero_Current_Sign,            (ulong32)(&Str_3aTable_E23RAM[0]),          191,    CLZero_Current_Sign,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC_DI0},
    {CStart_Up_Current,             (ulong32)(&Str_3aTable_E23RAM[0]),          192,    CLStart_Up_Current,             C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CStart_Up_Power,               (ulong32)(&Str_3aTable_E23RAM[0]),          193,    CLStart_Up_Power,               C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CVolage_Abnor_Vol,             (ulong32)(&Str_3aTable_E23RAM[0]),          194,    CLVolage_Abnor_Vol,             C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CRelayOpen_Vol__UpLim,         (ulong32)(&Str_3aTable_E23RAM[0]),          195,    CLRelayOpen_Vol__UpLim,         C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC_DI0_2},
    {CPluse_Most__Lim,              (ulong32)(&Str_3aTable_E23RAM[0]),          196,    CLPluse_Most__Lim,              C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CCurr_Ratio_30A,               (ulong32)(&Str_3aTable_E23RAM[0]),          197,    CLCurr_Ratio_30A,               C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CPulse_Constant,               (ulong32)(&Str_3aTable_E23RAM[0]),          198,    CLPulse_Constant,               C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CSoftIJ_Valid_Time,            (ulong32)(&Str_3aTable_E23RAM[0]),          199,    CLSoftIJ_Valid_Time,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CExtern_Relay_PulW,            (ulong32)(&Str_3aTable_E23RAM[0]),          200,    CLExtern_Relay_PulW,            C_WR_Msg_Communication,             DT_Ref_E23_RAMCRC},
    {CKey_Update_ID,                (ulong32)(E2Addr_Key_Update_ID),            0,      CLKey_Update_ID,                C_WR_Msg_Communication,             DT_E23},
#if 0
    {CTemp_Key_State0,              (ulong32)(E2Addr_Temp_Key_State0),          0,      CLTemp_Key_State0,              C_WR_Msg_Communication,             DT_E21},
    {CTemp_Key_State31,             (ulong32)(E2Addr_Temp_Key_State1),          0,      CLTemp_Key_State31,             C_WR_Msg_Communication,             DT_E21_DI0},
    {CTemp_Key_StateFF,             (ulong32)(E2Addr_Temp_Key_State0),          0,      CLTemp_Key_StateFF,             C_WR_Msg_Communication,             DT_E21},
    {CTemp_Key_Save0,               (ulong32)(E2Addr_Temp_Key_Save0),           0,      CLTemp_Key_Save0,               C_WR_Msg_Communication,             DT_E21},
    {CTemp_Key_Save31,              (ulong32)(E2Addr_Temp_Key_Save1),           0,      CLTemp_Key_Save31,              C_WR_Msg_Communication,             DT_E21_DI0},
#endif
    {CMeterRunStatic,               (ulong32)(&Str_3aTable_E23RAM[0]),          201,    CLMeterRunStatic,               C_WR_Msg_Comm_Deal,                 DT_Ref_E23_RAMCRC},
    {CHardError_State,              (ulong32)(&GV_HardError_State[0]),          0,      CLHardError_State,              C_WR_Msg_MeterIC,                   DT_RAM},
    {CF1_TerUpCommParam,            (ulong32)(E2Addr_F1_TerUpCommParam),        0,      CLF1_TerUpCommParam,            C_WR_Msg_Communication,             DT_E23},
    {CF3_MainStaCommParam,          (ulong32)(E2Addr_F3_MainStaCommParam),      0,      CLF3_MainStaCommParam,          C_WR_Msg_Communication,             DT_E23},
    {CF4_SMSCommParam,              (ulong32)(E2Addr_F4_SMSCommParam),          0,      CLF4_SMSCommParam,              C_WR_Msg_Communication,             DT_E23},
    {CF7_TerminalIPAddr,            (ulong32)(E2Addr_F7_TerminalIPAddr),        0,      CLF7_TerminalIPAddr,            C_WR_Msg_Communication,             DT_E23},
    {CF8_ConnectParam,              (ulong32)(E2Addr_F8_ConnectParam),          0,      CLF8_ConnectParam,              C_WR_Msg_Communication,             DT_E23},
    {CF16_MoveAPNPassWord,          (ulong32)(E2Addr_F16_MoveAPNPassWord),      0,      CLF16_MoveAPNPassWord,          C_WR_Msg_Communication,             DT_E23},
    {CF89_TerminalAddr,             (ulong32)(E2Addr_F89_TerminalAddr),         0,      CLF89_TerminalAddr,             C_WR_Msg_Communication,             DT_E23},
    {CRelay_RemoteOrder,            (ulong32)(&Str_3aTable_E23RAM[0]),          206,    CLRelay_RemoteOrder,            C_WR_Msg_Deal_RelayStatus,          DT_Ref_E23_RAMCRC},
    {CRelay_State,                  (ulong32)(&Str_3aTable_E23RAM[0]),          207,    CLRelay_State,                  C_WR_Msg_Deal_RelayStatus,          DT_Ref_E23_RAMCRC},
    {CRelay_LocalOrder,             (ulong32)(&Str_3aTable_E23RAM[0]),          208,    CLRelay_LocalOrder,             C_WR_Msg_Deal_RelayStatus,          DT_Ref_E23_RAMCRC},
    {CRec_MeterSequence,            (ulong32)(E2Addr_Rec_MeterSequence),        0,      CLRec_MeterSequence,            C_WR_Msg_Communication,             DT_E23},
    {CRec_MeterPassWord,            (ulong32)(E2Addr_Rec_MeterPassWord),        0,      CLRec_MeterPassWord,            C_WR_Msg_Communication,             DT_E23},
    {C_UserCardNo,                  (ulong32)(E2Addr_UserCardNo),               0,      CL_UserCardNo,                  C_WR_Msg_Comm_Card,                 DT_E23},
    {CFactoryInMeterNum,            (ulong32)(E2Addr_FactoryInMeterNum),        0,      CLFactoryInMeterNum,            C_WR_Msg_Communication,             DT_E23},
    {CSafeModeParaNat3_Num,         (ulong32)(E2Addr_SafeModeParaNat3_Num),     0,      CLSafeModeParaNat3_Num,         C_WR_Msg_Communication,             DT_E23},
    {CProgReC2_Degree,              (ulong32)(E2Addr_ProgReC1),                 0,      CLProgReC1_Degree,              C_WR_Msg_Communication,             DT_E23_DI0},
    {C_OddHar_AddData1,             (ulong32)(E2Addr_Odd_Harmonic_AddData1),    0,      CL_OddHar_AddData1,             C_WR_Msg_Communication,             DT_E23},
    {C_OddHar_AddData2,             (ulong32)(E2Addr_Odd_Harmonic_AddData2),    0,      CL_OddHar_AddData2,             C_WR_Msg_Communication,             DT_E23},
    {C_EvenHar_AddData_A0,          (ulong32)(E2Addr_Even_Harmonic_AddData_A0), 0,      CL_EvenHar_AddData_A0,          C_WR_Msg_Communication,             DT_E23},
    {C_EvenHar_AddData_A1,          (ulong32)(E2Addr_Even_Harmonic_AddData_A1), 0,      CL_EvenHar_AddData_A1,          C_WR_Msg_Communication,             DT_E23},
    {C_EvenHar_AddData_B0,          (ulong32)(E2Addr_Even_Harmonic_AddData_B0), 0,      CL_EvenHar_AddData_B0,          C_WR_Msg_Communication,             DT_E23},
    {C_EvenHar_AddData_B1,          (ulong32)(E2Addr_Even_Harmonic_AddData_B1), 0,      CL_EvenHar_AddData_B1,          C_WR_Msg_Communication,             DT_E23},
    {C_EvenHar_AddData_C0,          (ulong32)(E2Addr_Even_Harmonic_AddData_C0), 0,      CL_EvenHar_AddData_C0,          C_WR_Msg_Communication,             DT_E23},
    {C_EvenHar_AddData_C1,          (ulong32)(E2Addr_Even_Harmonic_AddData_C1), 0,      CL_EvenHar_AddData_C1,          C_WR_Msg_Communication,             DT_E23},
    {C_EvenHar_Time,                (ulong32)(E2Addr_Even_Harmonic_Time),       0,      CL_EvenHar_Time,                C_WR_Msg_Communication,             DT_E21},
    {CBackTime_OneSec,              (ulong32)(FRAMAddr_BackTime_OneSec),        0,      CLBackTime_OneSec,              C_WR_Msg_Comm_Dis,                  DT_FRAM1CRC},
    {CDisplayBorrowPoint,           (ulong32)(&GV_DisplayBorrowPoint[0]),       0,      CLDisplayBorrowPoint,           C_WR_Msg_Display,                   DT_RAMCRC},
    {CDisplayBorrowPoint_RecFlag,   (ulong32)(&GV_DisplayBorrowPoint_RecFlag[0]),0,     CLDisplayBorrowPoint_RecFlag,   C_WR_Msg_Display,                   DT_RAMCRC},
    /*�¼���*/
    {CLossA_Vol_Degree,             (ulong32)(E2Addr_LossA_Vol_Degree),         0,      CLLossA_Vol_Degree,             C_Only_Read,                        DT_E23_Hex},
    {CLossB_Vol_Degree,             (ulong32)(E2Addr_LossB_Vol_Degree),         0,      CLLossB_Vol_Degree,             C_Only_Read,                        DT_E23_Hex},
    {CLossC_Vol_Degree,             (ulong32)(E2Addr_LossC_Vol_Degree),         0,      CLLossC_Vol_Degree,             C_Only_Read,                        DT_E23_Hex},
    {CLossA_Vol_Time,               (ulong32)(E2Addr_LossA_Vol_Time),           0,      CLLossA_Vol_Time,               C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CLossB_Vol_Time,               (ulong32)(E2Addr_LossB_Vol_Time),           0,      CLLossB_Vol_Time,               C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CLossC_Vol_Time,               (ulong32)(E2Addr_LossC_Vol_Time),           0,      CLLossC_Vol_Time,               C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CLowA_Vol_Degree,              (ulong32)(E2Addr_LowA_Vol_Degree),          0,      CLLowA_Vol_Degree,              C_Only_Read,                        DT_E23_Hex},
    {CLowB_Vol_Degree,              (ulong32)(E2Addr_LowB_Vol_Degree),          0,      CLLowB_Vol_Degree,              C_Only_Read,                        DT_E23_Hex},
    {CLowC_Vol_Degree,              (ulong32)(E2Addr_LowC_Vol_Degree),          0,      CLLowC_Vol_Degree,              C_Only_Read,                        DT_E23_Hex},
    {CLowA_Vol_Time,                (ulong32)(E2Addr_LowA_Vol_Time),            0,      CLLowA_Vol_Time,                C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CLowB_Vol_Time,                (ulong32)(E2Addr_LowB_Vol_Time),            0,      CLLowB_Vol_Time,                C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CLowC_Vol_Time,                (ulong32)(E2Addr_LowC_Vol_Time),            0,      CLLowC_Vol_Time,                C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {COverA_Vol_Degree,             (ulong32)(E2Addr_OverA_Vol_Degree),         0,      CLOverA_Vol_Degree,             C_Only_Read,                        DT_E23_Hex},
    {COverB_Vol_Degree,             (ulong32)(E2Addr_OverB_Vol_Degree),         0,      CLOverB_Vol_Degree,             C_Only_Read,                        DT_E23_Hex},
    {COverC_Vol_Degree,             (ulong32)(E2Addr_OverC_Vol_Degree),         0,      CLOverC_Vol_Degree,             C_Only_Read,                        DT_E23_Hex},
    {COverA_Vol_Time,               (ulong32)(E2Addr_OverA_Vol_Time),           0,      CLOverA_Vol_Time,               C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {COverB_Vol_Time,               (ulong32)(E2Addr_OverB_Vol_Time),           0,      CLOverB_Vol_Time,               C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {COverC_Vol_Time,               (ulong32)(E2Addr_OverC_Vol_Time),           0,      CLOverC_Vol_Time,               C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CBreakA_Vol_Degree,            (ulong32)(E2Addr_BreakA_Vol_Degree),        0,      CLBreakA_Vol_Degree,            C_Only_Read,                        DT_E23_Hex},
    {CBreakB_Vol_Degree,            (ulong32)(E2Addr_BreakB_Vol_Degree),        0,      CLBreakB_Vol_Degree,            C_Only_Read,                        DT_E23_Hex},
    {CBreakC_Vol_Degree,            (ulong32)(E2Addr_BreakC_Vol_Degree),        0,      CLBreakC_Vol_Degree,            C_Only_Read,                        DT_E23_Hex},
    {CBreakA_Vol_Time,              (ulong32)(E2Addr_BreakA_Vol_Time),          0,      CLBreakA_Vol_Time,              C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CBreakB_Vol_Time,              (ulong32)(E2Addr_BreakB_Vol_Time),          0,      CLBreakB_Vol_Time,              C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CBreakC_Vol_Time,              (ulong32)(E2Addr_BreakC_Vol_Time),          0,      CLBreakC_Vol_Time,              C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CLossA_Curr_Degree,            (ulong32)(E2Addr_LossA_Curr_Degree),        0,      CLLossA_Curr_Degree,            C_Only_Read,                        DT_E23_Hex},
    {CLossB_Curr_Degree,            (ulong32)(E2Addr_LossB_Curr_Degree),        0,      CLLossB_Curr_Degree,            C_Only_Read,                        DT_E23_Hex},
    {CLossC_Curr_Degree,            (ulong32)(E2Addr_LossC_Curr_Degree),        0,      CLLossC_Curr_Degree,            C_Only_Read,                        DT_E23_Hex},
    {CLossA_Curr_Time,              (ulong32)(E2Addr_LossA_Curr_Time),          0,      CLLossA_Curr_Time,              C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CLossB_Curr_Time,              (ulong32)(E2Addr_LossB_Curr_Time),          0,      CLLossB_Curr_Time,              C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CLossC_Curr_Time,              (ulong32)(E2Addr_LossC_Curr_Time),          0,      CLLossC_Curr_Time,              C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {COverA_Curr_Degree,            (ulong32)(E2Addr_OverA_Curr_Degree),        0,      CLOverA_Curr_Degree,            C_Only_Read,                        DT_E23_Hex},
    {COverB_Curr_Degree,            (ulong32)(E2Addr_OverB_Curr_Degree),        0,      CLOverB_Curr_Degree,            C_Only_Read,                        DT_E23_Hex},
    {COverC_Curr_Degree,            (ulong32)(E2Addr_OverC_Curr_Degree),        0,      CLOverC_Curr_Degree,            C_Only_Read,                        DT_E23_Hex},
    {COverA_Curr_Time,              (ulong32)(E2Addr_OverA_Curr_Time),          0,      CLOverA_Curr_Time,              C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {COverB_Curr_Time,              (ulong32)(E2Addr_OverB_Curr_Time),          0,      CLOverB_Curr_Time,              C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {COverC_Curr_Time,              (ulong32)(E2Addr_OverC_Curr_Time),          0,      CLOverC_Curr_Time,              C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CBreakA_Curr_Degree,           (ulong32)(E2Addr_BreakA_Curr_Degree),       0,      CLBreakA_Curr_Degree,           C_Only_Read,                        DT_E23_Hex},
    {CBreakB_Curr_Degree,           (ulong32)(E2Addr_BreakB_Curr_Degree),       0,      CLBreakB_Curr_Degree,           C_Only_Read,                        DT_E23_Hex},
    {CBreakC_Curr_Degree,           (ulong32)(E2Addr_BreakC_Curr_Degree),       0,      CLBreakC_Curr_Degree,           C_Only_Read,                        DT_E23_Hex},
    {CBreakA_Curr_Time,             (ulong32)(E2Addr_BreakA_Curr_Time),         0,      CLBreakA_Curr_Time,             C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CBreakB_Curr_Time,             (ulong32)(E2Addr_BreakB_Curr_Time),         0,      CLBreakB_Curr_Time,             C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CBreakC_Curr_Time,             (ulong32)(E2Addr_BreakC_Curr_Time),         0,      CLBreakC_Curr_Time,             C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CPowerT_Rev_Degree,            (ulong32)(E2Addr_PowerT_Rev_Degree),        0,      CLPowerT_Rev_Degree,            C_Only_Read,                        DT_E23_Hex},
    {CPowerA_Rev_Degree,            (ulong32)(E2Addr_PowerA_Rev_Degree),        0,      CLPowerA_Rev_Degree,            C_Only_Read,                        DT_E23_Hex},
    {CPowerB_Rev_Degree,            (ulong32)(E2Addr_PowerB_Rev_Degree),        0,      CLPowerB_Rev_Degree,            C_Only_Read,                        DT_E23_Hex},
    {CPowerC_Rev_Degree,            (ulong32)(E2Addr_PowerC_Rev_Degree),        0,      CLPowerC_Rev_Degree,            C_Only_Read,                        DT_E23_Hex},
    {CPowerT_Rev_Time,              (ulong32)(E2Addr_PowerT_Rev_Time),          0,      CLPowerT_Rev_Time,              C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CPowerA_Rev_Time,              (ulong32)(E2Addr_PowerA_Rev_Time),          0,      CLPowerA_Rev_Time,              C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CPowerB_Rev_Time,              (ulong32)(E2Addr_PowerB_Rev_Time),          0,      CLPowerB_Rev_Time,              C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CPowerC_Rev_Time,              (ulong32)(E2Addr_PowerC_Rev_Time),          0,      CLPowerC_Rev_Time,              C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {COverA_Lo_Degree,              (ulong32)(E2Addr_OverA_Lo_Degree),          0,      CLOverA_Lo_Degree,              C_Only_Read,                        DT_E23_Hex},
    {COverB_Lo_Degree,              (ulong32)(E2Addr_OverB_Lo_Degree),          0,      CLOverB_Lo_Degree,              C_Only_Read,                        DT_E23_Hex},
    {COverC_Lo_Degree,              (ulong32)(E2Addr_OverC_Lo_Degree),          0,      CLOverC_Lo_Degree,              C_Only_Read,                        DT_E23_Hex},
    {COverA_Lo_Time,                (ulong32)(E2Addr_OverA_Lo_Time),            0,      CLOverA_Lo_Time,                C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {COverB_Lo_Time,                (ulong32)(E2Addr_OverB_Lo_Time),            0,      CLOverB_Lo_Time,                C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {COverC_Lo_Time,                (ulong32)(E2Addr_OverC_Lo_Time),            0,      CLOverC_Lo_Time,                C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CPos_Ac_De_Over_Degree,        (ulong32)(E2Addr_Pos_Ac_De_Over_Degree),    0,      CLPos_Ac_De_Over_Degree,        C_Only_Read,                        DT_E23_Hex},
    {CPos_Ac_De_Over_Time,          (ulong32)(E2Addr_Pos_Ac_De_Over_Time),      0,      CLPos_Ac_De_Over_Time,          C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CRev_Ac_De_Over_Degree,        (ulong32)(E2Addr_Rev_Ac_De_Over_Degree),    0,      CLRev_Ac_De_Over_Degree,        C_Only_Read,                        DT_E23_Hex},
    {CRev_Ac_De_Over_Time,          (ulong32)(E2Addr_Rev_Ac_De_Over_Time),      0,      CLRev_Ac_De_Over_Time,          C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CQua1_Re_De_Over_Degree,       (ulong32)(E2Addr_Qua1_Re_De_Over_Degree),   0,      CLQua1_Re_De_Over_Degree,       C_Only_Read,                        DT_E23_Hex},
    {CQua2_Re_De_Over_Degree,       (ulong32)(E2Addr_Qua2_Re_De_Over_Degree),   0,      CLQua2_Re_De_Over_Degree,       C_Only_Read,                        DT_E23_Hex},
    {CQua3_Re_De_Over_Degree,       (ulong32)(E2Addr_Qua3_Re_De_Over_Degree),   0,      CLQua3_Re_De_Over_Degree,       C_Only_Read,                        DT_E23_Hex},
    {CQua4_Re_De_Over_Degree,       (ulong32)(E2Addr_Qua4_Re_De_Over_Degree),   0,      CLQua4_Re_De_Over_Degree,       C_Only_Read,                        DT_E23_Hex},
    {CQua1_Re_De_Over_Time,         (ulong32)(E2Addr_Qua1_Re_De_Over_Time),     0,      CLQua1_Re_De_Over_Time,         C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CQua2_Re_De_Over_Time,         (ulong32)(E2Addr_Qua2_Re_De_Over_Time),     0,      CLQua2_Re_De_Over_Time,         C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CQua3_Re_De_Over_Time,         (ulong32)(E2Addr_Qua3_Re_De_Over_Time),     0,      CLQua3_Re_De_Over_Time,         C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CQua4_Re_De_Over_Time,         (ulong32)(E2Addr_Qua4_Re_De_Over_Time),     0,      CLQua4_Re_De_Over_Time,         C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CAll_Loss_Vol_Degree,          (ulong32)(E2Addr_All_Loss_Vol_Degree),      0,      CLAll_Loss_Vol_Degree,          C_Only_Read,                        DT_E23_Hex},
    {CAll_Loss_Vol_Time,            (ulong32)(E2Addr_All_Loss_Vol_Time),        0,      CLAll_Loss_Vol_Time,            C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CAux_Pow_Down_Degree,          (ulong32)(E2Addr_Aux_Pow_Down_Degree),      0,      CLAux_Pow_Down_Degree,          C_Only_Read,                        DT_E23_Hex},
    {CAux_Pow_Down_Time,            (ulong32)(E2Addr_Aux_Pow_Down_Time),        0,      CLAux_Pow_Down_Time,            C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CRevPS_Vol_Degree,             (ulong32)(E2Addr_RevPS_Vol_Degree),         0,      CLRevPS_Vol_Degree,             C_Only_Read,                        DT_E23_Hex},
    {CRevPS_Vol_Time,               (ulong32)(E2Addr_RevPS_Vol_Time),           0,      CLRevPS_Vol_Time,               C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CRevPS_Curr_Degree,            (ulong32)(E2Addr_RevPS_Curr_Degree),        0,      CLRevPS_Curr_Degree,            C_Only_Read,                        DT_E23_Hex},
    {CRevPS_Curr_Time,              (ulong32)(E2Addr_RevPS_Curr_Time),          0,      CLRevPS_Curr_Time,              C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CPow_Down_Degree,              (ulong32)(E2Addr_Pow_Down_Degree),          0,      CLPow_Down_Degree,              C_Only_Read,                        DT_E23_Hex},
    {CPow_Down_Time,                (ulong32)(E2Addr_Pow_Down_Time),            0,      CLPow_Down_Time,                C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CProgram_Degree,               (ulong32)(E2Addr_Program_Degree),           0,      CLProgram_Degree,               C_Only_Read,                        DT_E23_Hex},
    {CTol_Clear_Degree,             (ulong32)(E2Addr_Tol_Clear_Degree),         0,      CLTol_Clear_Degree,             C_Only_Read,                        DT_E23_Hex},
    {CDe_Clear_Degree,              (ulong32)(E2Addr_De_Clear_Degree),          0,      CLDe_Clear_Degree,              C_Only_Read,                        DT_E23_Hex},
    {CEven_Clear_Degree,            (ulong32)(E2Addr_Even_Clear_Degree),        0,      CLEven_Clear_Degree,            C_Only_Read,                        DT_E23_Hex},
    {CAdjTime_Degree,               (ulong32)(E2Addr_AdjTime_Degree),           0,      CLAdjTime_Degree,               C_Only_Read,                        DT_E23_Hex},
    {CProgPT_Degree,                (ulong32)(E2Addr_ProgPT_Degree),            0,      CLProgPT_Degree,                C_Only_Read,                        DT_E23_Hex},
    {CProgTZ_Degree,                (ulong32)(E2Addr_ProgTZ_Degree),            0,      CLProgTZ_Degree,                C_Only_Read,                        DT_E23_Hex},
    {CProgWRe_Degree,               (ulong32)(E2Addr_ProgWRe_Degree),           0,      CLProgWRe_Degree,               C_Only_Read,                        DT_E23_Hex},
    {CProgSettD_Degree,             (ulong32)(E2Addr_ProgSettD_Degree),         0,      CLProgSettD_Degree,             C_Only_Read,                        DT_E23_Hex},
    {COpenW_Degree,                 (ulong32)(E2Addr_OpenW_Degree),             0,      CLOpenW_Degree,                 C_Only_Read,                        DT_E23_Hex},
    {COpenW_Time,                   (ulong32)(E2Addr_OpenW_Time),               0,      CLOpenW_Time,                   C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {COpenCW_Degree,                (ulong32)(E2Addr_OpenCW_Degree),            0,      CLOpenCW_Degree,                C_Only_Read,                        DT_E23_Hex},
    {COpenCW_Time,                  (ulong32)(E2Addr_OpenCW_Time),              0,      CLOpenCW_Time,                  C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CNoBal_Vol_Degree,             (ulong32)(E2Addr_NoBal_Vol_Degree),         0,      CLNoBal_Vol_Degree,             C_Only_Read,                        DT_E23_Hex},
    {CNoBal_Vol_Time,               (ulong32)(E2Addr_NoBal_Vol_Time),           0,      CLNoBal_Vol_Time,               C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CNoBal_Curr_Degree,            (ulong32)(E2Addr_NoBal_Curr_Degree),        0,      CLNoBal_Curr_Degree,            C_Only_Read,                        DT_E23_Hex},
    {CNoBal_Curr_Time,              (ulong32)(E2Addr_NoBal_Curr_Time),          0,      CLNoBal_Curr_Time,              C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CRelayOpen_Degree,             (ulong32)(E2Addr_RelayOpen_Degree),         0,      CLRelayOpen_Degree,             C_Only_Read,                        DT_E23_Hex},
    {CRelayClose_Degree,            (ulong32)(E2Addr_RelayClose_Degree),        0,      CLRelayClose_Degree,            C_Only_Read,                        DT_E23_Hex},
    {CProgHol_Degree,               (ulong32)(E2Addr_ProgHol_Degree),           0,      CLProgHol_Degree,               C_Only_Read,                        DT_E23_Hex},
    {CProgAcC_Degree,               (ulong32)(E2Addr_ProgAcC_Degree),           0,      CLProgAcC_Degree,               C_Only_Read,                        DT_E23_Hex},
    {CProgReC_Degree,               (ulong32)(E2Addr_ProgReC1_Degree),          0,      CLProgReC_Degree,               C_Only_Read,                        DT_E23_Hex},
    {CProgTPara_Degree,             (ulong32)(E2Addr_ProgTPara_Degree),         0,      CLProgTPara_Degree,             C_Only_Read,                        DT_E23_Hex},
    {CProgLad_Degree,               (ulong32)(E2Addr_ProgLad_Degree),           0,      CLProgLad_Degree,               C_Only_Read,                        DT_E23_Hex},
    {CProgKD_Degree,                (ulong32)(E2Addr_ProgKD_Degree),            0,      CLProgKD_Degree,                C_Only_Read,                        DT_E23_Hex},
    {CAbnorC_Degree,                (ulong32)(E2Addr_AbnorC_Degree),            0,      CLAbnorC_Degree,                C_Only_Read,                        DT_E23_Hex},
    {CBuyCurr_Degree,               (ulong32)(E2Addr_BuyCurr_Degree),           0,      CLBuyCurr_Degree,               C_Only_Read,                        DT_E23_Hex},
    {CReturn_M_Degree,              (ulong32)(E2Addr_Return_M_Degree),          0,      CLReturn_M_Degree,              C_Only_Read,                        DT_E23_Hex},
    {CConM_Degree,                  (ulong32)(E2Addr_ConM_Degree),              0,      CLConM_Degree,                  C_Only_Read,                        DT_E23_Hex},
    {CConM_Time,                    (ulong32)(E2Addr_ConM_Time),                0,      CLConM_Time,                    C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CRelayFa_Degree,               (ulong32)(E2Addr_RelayFa_Degree),           0,      CLRelayFa_Degree,               C_Only_Read,                        DT_E23_Hex},
    {CRelayFa_Time,                 (ulong32)(E2Addr_RelayFa_Time),             0,      CLRelayFa_Time,                 C_WR_Msg_Deal_RelayStatus,          DT_E23},
    {CPowerFa_Degree,               (ulong32)(E2Addr_PowerFa_Degree),           0,      CLPowerFa_Degree,               C_Only_Read,                        DT_E23_Hex},
    {CPowerFa_Time,                 (ulong32)(E2Addr_PowerFa_Time),             0,      CLPowerFa_Time,                 C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CSevNoBal_Curr_Degree,         (ulong32)(E2Addr_SevNoBal_Curr_Degree),     0,      CLSevNoBal_Curr_Degree,         C_Only_Read,                        DT_E23_Hex},
    {CSevNoBal_Curr_Time,           (ulong32)(E2Addr_SevNoBal_Curr_Time),       0,      CLSevNoBal_Curr_Time,           C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CClockFa_Degree,               (ulong32)(E2Addr_ClockFa_Degree),           0,      CLClockFa_Degree,               C_Only_Read,                        DT_E23_Hex},
    {CClockFa_Time,                 (ulong32)(E2Addr_ClockFa_Time),             0,      CLClockFa_Time,                 C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CMeterFa_Degree,               (ulong32)(E2Addr_MeterFa_Degree),           0,      CLMeterFa_Degree,               C_Only_Read,                        DT_E23_Hex},
    {CMeterFa_Time,                 (ulong32)(E2Addr_MeterFa_Time),             0,      CLMeterFa_Time,                 C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CPFactorT_Over_Degree,         (ulong32)(E2Addr_PFactorT_Over_Degree),     0,      CLPFactorT_Over_Degree,         C_Only_Read,                        DT_E23_Hex},
    {CPFactorA_Over_Degree,         (ulong32)(E2Addr_PFactorA_Over_Degree),     0,      CLPFactorA_Over_Degree,         C_Only_Read,                        DT_E23_Hex},
    {CPFactorB_Over_Degree,         (ulong32)(E2Addr_PFactorB_Over_Degree),     0,      CLPFactorB_Over_Degree,         C_Only_Read,                        DT_E23_Hex},
    {CPFactorC_Over_Degree,         (ulong32)(E2Addr_PFactorC_Over_Degree),     0,      CLPFactorC_Over_Degree,         C_Only_Read,                        DT_E23_Hex},
    {CPFactorT_Over_Time,           (ulong32)(E2Addr_PFactorT_Over_Time),       0,      CLPFactorT_Over_Time,           C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CPFactorA_Over_Time,           (ulong32)(E2Addr_PFactorA_Over_Time),       0,      CLPFactorA_Over_Time,           C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CPFactorB_Over_Time,           (ulong32)(E2Addr_PFactorB_Over_Time),       0,      CLPFactorB_Over_Time,           C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CPFactorC_Over_Time,           (ulong32)(E2Addr_PFactorC_Over_Time),       0,      CLPFactorC_Over_Time,           C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CBroadcastTime_Degree,         (ulong32)(E2Addr_BroadcastTime_Degree),     0,      CLBroadcastTime_Degree,         C_Only_Read,                        DT_E23_Hex},
    {CNeutralCurrentAbnormal_Degree,(ulong32)(E2Addr_NeutralCurrentAbnormal_Degree),0,CLNeutralCurrentAbnormal_Degree,  C_Only_Read,                        DT_E23_Hex},
    {CNeutralCurrentAbnormal_Time,  (ulong32)(E2Addr_NeutralCurrentAbnormal_Time),0,    CLNeutralCurrentAbnormal_Time,  C_WR_Msg_PowerNetworkMonitoring,    DT_E23},
    {CSoft_I_J_Prog_1,              (ulong32)(E2Addr_Soft_I_J_Prog_1),          0,      CLSoft_I_J_Prog_1,              C_WR_Msg_Communication,             DT_E23},
    {CSoft_I_J_Prog_2,              (ulong32)(E2Addr_Soft_I_J_Prog_2),          0,      CLSoft_I_J_Prog_2,              C_WR_Msg_Communication,             DT_E23},
    {CRec_Meter_Degree,             (ulong32)(E2Addr_Rec_Meter_Degree),         0,      CLRec_Meter_Degree,             C_Only_Read,                        DT_E23_Hex},
    {CRec_Meter_Hp_T_1,             (ulong32)(&Str_3cTable_Flash[0]),           0,      CLRec_Meter_Hp_T_1,             C_WR_Msg_Communication,             DT_Flash_Tol_DI0_DI1},
    {CRec_Meter_Bef1_Data_254,      (ulong32)(&Str_3cTable_Flash[0]),           0,      CLRec_Meter_Bef1_Data_254,      C_WR_Msg_Communication,             DT_Flash_Tol_DI0_DI1Max},
    {CProgPT_CurrentPart_Degree,    (ulong32)(E2Addr_ProgPT_CurrentPart_Degree),0,      CLProgPT_CurrentPart_Degree,    C_Only_Read,                        DT_E23_Hex},
    {CProgPT_NoteC_1,               (ulong32)(&Str_3cTable_Flash[0]),           1,      CLProgPT_NoteC_1,               C_WR_Msg_Communication,             DT_Flash_DI04},
    {CProgPT_NoteD_1,               (ulong32)(&Str_3cTable_Flash[0]),           1,      CLProgPT_NoteD_1,               C_WR_Msg_Communication,             DT_Flash_DI04},
    {CProgPT_NoteE_1,               (ulong32)(&Str_3cTable_Flash[0]),           1,      CLProgPT_NoteE_1,               C_WR_Msg_Communication,             DT_Flash_DI04},
    {CProgPT_NoteF_1,               (ulong32)(&Str_3cTable_Flash[0]),           1,      CLProgPT_NoteF_1,               C_WR_Msg_Communication,             DT_Flash_DI04},
    {CProgTZ_CurrentPart_Degree,    (ulong32)(E2Addr_ProgTZ_CurrentPart_Degree),0,      CLProgTZ_CurrentPart_Degree,    C_Only_Read,                        DT_E23_Hex},
    {CProgTZ_CurrentPart_Note_1,    (ulong32)(&Str_3cTable_Flash[0]),           2,      CLProgTZ_CurrentPart_Note_1,    C_WR_Msg_Communication,             DT_Flash_DI04},
    {CProgram_Degree_645_2,         (ulong32)(E2Addr_Program_Degree_645),       0,      CLProgram_Degree_645,           C_Only_Read,                        DT_E23_Hex},
    {CProgram_Note_1_645,           (ulong32)(&Str_3cTable_Flash[0]),           3,      CLProgram_Note_1_645,           C_WR_Msg_Comm_Card,                 DT_Flash_Tol_DI0},
};
#define Str_2Table_DIParameterFF_Len  (sizeof(Str_2Table_DIParameterFF)/sizeof(Str_2Table))

const Str_1Table Str_1Table_DI3[]=
{/* 2�����ṹ�������ַ                      ��Ӧ2����ṹ�����ݳ���                  V_DI3*/
	{(ulong32)(Str_2Table_DIEn),                 Str_2Table_DIEn_Len,                     0x00},            /***��������*/
	{(ulong32)(Str_2Table_DIDe10),               Str_2Table_DIDe10_Len,                   0x10},            /***���������****/
	{(ulong32)(Str_2Table_DIEvent20),            Str_2Table_DIEvent20_Len,                0x20},            /***������DI3=20*****/
	{(ulong32)(Str_2Table_DIEvent21),            Str_2Table_DIEvent21_Len,                0x21},            /***������DI3=21*****/
	{(ulong32)(Str_2Table_DIEvent30),            Str_2Table_DIEvent30_Len,                0x30},            /***�¼���DI3=03*****/
	{(ulong32)(Str_2Table_DIReport),             Str_2Table_DIReport_Len,                 0x33},             /***�ϱ���*****/
	{(ulong32)(Str_2Table_DIParamChild40),       Str_2Table_DIParamChild40_Len,           0x40},            /***�α�����698 40*****/
	{(ulong32)(Str_2Table_DIParamChild41),       Str_2Table_DIParamChild41_Len,           0x41},            /***�α�����698 41*****/
	{(ulong32)(Str_2Table_DIParamChild43),       Str_2Table_DIParamChild43_Len,           0x43},            /***�α�����698 43*****/
	{(ulong32)(Str_2Table_DIParamChild44),       Str_2Table_DIParamChild44_Len,           0x44},            /***�α�����698 44*****/
	{(ulong32)(Str_2Table_DIParamChild45),       Str_2Table_DIParamChild45_Len,           0x45},            /***�α�����698 45*****/
	{(ulong32)(Str_2Table_DIParamChild80),       Str_2Table_DIParamChild80_Len,           0x80},            /***�α�����698 80*****/
	{(ulong32)(Str_2Table_DIParameterF1),        Str_2Table_DIParameterF1_Len,            0xF1},            /***�α�����698 F1*****/
	{(ulong32)(Str_2Table_DIParamChildF2),       Str_2Table_DIParamChildF2_Len,           0xF2},            /***�α�����698 F2*****/
	{(ulong32)(Str_2Table_DIParamChildF3),       Str_2Table_DIParamChildF3_Len,           0xF3},            /***�α�����698 F3*****/
	{(ulong32)(Str_2Table_DIParamChild),         Str_2Table_DIParamChild_Len,             0x04},            /***�α�����645 04*****/
	{(ulong32)(Str_2Table_DIParameterFF),        Str_2Table_DIParameterFF_Len,            0xFF}             /*33�����α�����698 FF*/
};
#define Str_1Table_DI3_Len  (sizeof(Str_1Table_DI3)/sizeof(Str_1Table))

/********************************************�¼���¼E2���*******************************************/
#define EventDI    0x000000FF

const Str_EvenTable  Str_EvenTableE2[]=               /*��������������¼���¼������¼(��698�������ڣ��޸Ĺ����б�ʱ����ؼ�¼)������DI1�з����ʶ���¼��������¼�����ʱ�ñ�ʶ��ΪFF���������*/
{/*ulong32 V_DI                          ���ݱ�ʶ��ӦE2��ʼ��ַ ���ݱ�ʶ��ӦE2������ַ �¼��ϱ�����ӦE2��ʼ��ַ		�¼��ϱ�����ӦE2������ַ	 				���ݱ�ʾ��ӦEventNum�ţ�ѧ�ƺ궨��*/
	{(CAll_Loss_Vol|EventDI),              E2Addr_All_Loss_Vol_Degree,        E2Addr_Aux_Pow_Down_Degree,     /*E2Addr_AllLossVolage_Report_Record_1,E2Addr_AuxPowDown_Report_Record_1, 		*/C_TotalVoltageLoseEventNo		},
	{(CAux_Pow_Down|EventDI),              E2Addr_Aux_Pow_Down_Degree,        E2Addr_Pow_Down_Degree    ,     /*E2Addr_AuxPowDown_Report_Record_1,		E2Addr_RevVol_Report_Record_1,		 		*/C_ACPowerFailEventNo			  },
	{(CPow_Down_Degree|EventDI),           E2Addr_Pow_Down_Degree,            E2Addr_Pos_Ac_De_Over_Degree,   /*E2Addr_PowerOff_Report_Record_1,			E2Addr_Program_Report_Record_1,				*/C_PowerfailEventNo				  },
	{(CPos_Ac_De_Over_Note_1|EventDI),     E2Addr_Pos_Ac_De_Over_Degree,      E2Addr_Rev_Ac_De_Over_Degree,   /*E2Addr_AcDemandOv_Report_Record_1,		E2Addr_PosDemandOv_Report_Record_1, 	*/C_OverForwardActiveEventNo  },
	{(CRev_Ac_De_Over_Note_1|EventDI),     E2Addr_Rev_Ac_De_Over_Degree,      E2Addr_Qua1_Re_De_Over_Degree,  /*E2Addr_PosDemandOv_Report_Record_1,	E2Addr_1ReDemandOv_Report_Record_1, 	*/C_OverReverseActiveEventNo  },
	{(CQua1_Re_De_Over_Note_1|EventDI),    E2Addr_Qua1_Re_De_Over_Degree,     E2Addr_Qua2_Re_De_Over_Degree,  /*E2Addr_1ReDemandOv_Report_Record_1,	E2Addr_2ReDemandOv_Report_Record_1, 	*/C_1OverIdleDemandEventNo	  },
	{(CQua2_Re_De_Over_Note_1|EventDI),    E2Addr_Qua2_Re_De_Over_Degree,     E2Addr_Qua3_Re_De_Over_Degree,  /*E2Addr_2ReDemandOv_Report_Record_1,	E2Addr_3ReDemandOv_Report_Record_1, 	*/C_2OverIdleDemandEventNo	  },
	{(CQua3_Re_De_Over_Note_1|EventDI),    E2Addr_Qua3_Re_De_Over_Degree,     E2Addr_Qua4_Re_De_Over_Degree,  /*E2Addr_3ReDemandOv_Report_Record_1,	E2Addr_4ReDemandOv_Report_Record_1, 	*/C_3OverIdleDemandEventNo	  },
	{(CQua4_Re_De_Over_Note_1|EventDI),    E2Addr_Qua4_Re_De_Over_Degree,     E2Addr_LossA_Vol_Degree,        /*E2Addr_4ReDemandOv_Report_Record_1,	E2Addr_PowerFactor_Report_Record_1, 	*/C_4OverIdleDemandEventNo	  },
	{(CLossAVol_FF_1|EventDI),             E2Addr_LossA_Vol_Degree,           E2Addr_LossB_Vol_Degree    ,    /*E2Addr_ALossVolage_Report_Record_1,	E2Addr_BLossVolage_Report_Record_1, 	*/C_AlossvoltageEventNo			  },
	{(CLossBVol_FF_1|EventDI),             E2Addr_LossB_Vol_Degree,           E2Addr_LossC_Vol_Degree,        /*E2Addr_BLossVolage_Report_Record_1,	E2Addr_CLossVolage_Report_Record_1, 	*/C_BlossvoltageEventNo			  },
	{(CLossCVol_FF_1|EventDI),             E2Addr_LossC_Vol_Degree,           E2Addr_LowA_Vol_Degree    ,     /*E2Addr_CLossVolage_Report_Record_1,	E2Addr_ALowVolage_Report_Record_1,		*/C_ClossvoltageEventNo			  },
	{(CLowAVol_FF_1|EventDI),              E2Addr_LowA_Vol_Degree,            E2Addr_LowB_Vol_Degree,         /*E2Addr_ALowVolage_Report_Record_1,		E2Addr_BLowVolage_Report_Record_1,		*/C_ALessvoltageEventNo			  },
	{(CLowBVol_FF_1|EventDI),              E2Addr_LowB_Vol_Degree,            E2Addr_LowC_Vol_Degree    ,     /*E2Addr_BLowVolage_Report_Record_1,		E2Addr_CLowVolage_Report_Record_1, 		*/C_BLessvoltageEventNo			  },
	{(CLowCVol_FF_1|EventDI),              E2Addr_LowC_Vol_Degree,            E2Addr_OverA_Vol_Degree,        /*E2Addr_CLowVolage_Report_Record_1,		E2Addr_AOverVolage_Report_Record_1, 	*/C_CLessvoltageEventNo			  },
	{(COverAVol_FF_1|EventDI),             E2Addr_OverA_Vol_Degree,           E2Addr_OverB_Vol_Degree   ,     /*E2Addr_AOverVolage_Report_Record_1,	E2Addr_BOverVolage_Report_Record_1, 	*/C_AOvervoltageEventNo			  },
	{(COverBVol_FF_1|EventDI),             E2Addr_OverB_Vol_Degree,           E2Addr_OverC_Vol_Degree,        /*E2Addr_BOverVolage_Report_Record_1,	E2Addr_COverVolage_Report_Record_1, 	*/C_BOvervoltageEventNo			  },
	{(COverCVol_FF_1|EventDI),             E2Addr_OverC_Vol_Degree,           E2Addr_BreakA_Vol_Degree    ,   /*E2Addr_COverVolage_Report_Record_1,	E2Addr_ABreakVolage_Report_Record_1,	*/C_COvervoltageEventNo			  },
	{(CBreakAVol_FF_1|EventDI),            E2Addr_BreakA_Vol_Degree,          E2Addr_BreakB_Vol_Degree,       /*E2Addr_ABreakVolage_Report_Record_1,	E2Addr_BBreakVolage_Report_Record_1,	*/C_ALossphaseEventNo				  },
	{(CBreakBVol_FF_1|EventDI),            E2Addr_BreakB_Vol_Degree,          E2Addr_BreakC_Vol_Degree    ,   /*E2Addr_BBreakVolage_Report_Record_1,	E2Addr_CBreakVolage_Report_Record_1,	*/C_BLossphaseEventNo				  },
	{(CBreakCVol_FF_1|EventDI),            E2Addr_BreakC_Vol_Degree,          E2Addr_RevPS_Vol_Degree,        /*E2Addr_CBreakVolage_Report_Record_1,	E2Addr_ALossCurr_Report_Record_1,			*/C_CLossphaseEventNo				  },
	{(CRevPSVol_FF_1|EventDI),             E2Addr_RevPS_Vol_Degree,           E2Addr_RevPS_Curr_Degree    ,   /*E2Addr_RevVol_Report_Record_1,				E2Addr_RevCurr_Report_Record_1,				*/C_ReversephaseVoltageEventNo},
	{(CRevPSCurr_FF_1|EventDI),            E2Addr_RevPS_Curr_Degree,          E2Addr_NoBal_Vol_Degree,        /*E2Addr_RevCurr_Report_Record_1,			E2Addr_PowerOff_Report_Record_1,			*/C_ReversephaseCurrentEventNo},
	{(CNoBalVol_FF_1|EventDI),             E2Addr_NoBal_Vol_Degree,           E2Addr_NoBal_Curr_Degree    ,   /*E2Addr_NoBalVol_Report_Record_1,			E2Addr_NoBalCurr_Report_Record_1,			*/C_UnbanlanceVoltageEventNo	},
	{(CNoBalCurr_FF_1|EventDI),            E2Addr_NoBal_Curr_Degree,          E2Addr_SevNoBal_Curr_Degree,    /*E2Addr_NoBalCurr_Report_Record_1,		E2Addr_RelayOpen_Report_Record_1,			*/C_UnbanlanceCurrentEventNo	},
	{(CSevNoBalCurr_FF_1|EventDI),         E2Addr_SevNoBal_Curr_Degree,       E2Addr_LossA_Curr_Degree,       /*E2Addr_SeriNoBalCurr_Report_Record_1,E2Addr_ClockFault_Report_Record_1,		*/C_SUnbanlanceCurrentEventNo	},
	{(CLossACurr_FF_1|EventDI),            E2Addr_LossA_Curr_Degree,          E2Addr_LossB_Curr_Degree    ,   /*E2Addr_ALossCurr_Report_Record_1,		E2Addr_BLossCurr_Report_Record_1,			*/C_ALosscurrentEventNo			  },
	{(CLossBCurr_FF_1|EventDI),            E2Addr_LossB_Curr_Degree,          E2Addr_LossC_Curr_Degree,       /*E2Addr_BLossCurr_Report_Record_1,		E2Addr_CLossCurr_Report_Record_1,			*/C_BLosscurrentEventNo			  },
	{(CLossCCurr_FF_1|EventDI),            E2Addr_LossC_Curr_Degree,          E2Addr_OverA_Curr_Degree    ,   /*E2Addr_CLossCurr_Report_Record_1,		E2Addr_AOverCurr_Report_Record_1,			*/C_CLosscurrentEventNo			  },
	{(COverACurr_FF_1|EventDI),            E2Addr_OverA_Curr_Degree,          E2Addr_OverB_Curr_Degree,       /*E2Addr_AOverCurr_Report_Record_1,		E2Addr_BOverCurr_Report_Record_1,			*/C_AOvercurrentEventNo			  },
	{(COverBCurr_FF_1|EventDI),            E2Addr_OverB_Curr_Degree,          E2Addr_OverC_Curr_Degree    ,   /*E2Addr_BOverCurr_Report_Record_1,		E2Addr_COverCurr_Report_Record_1,			*/C_BOvercurrentEventNo			  },
	{(COverCCurr_FF_1|EventDI),            E2Addr_OverC_Curr_Degree,          E2Addr_BreakA_Curr_Degree,      /*E2Addr_COverCurr_Report_Record_1,		E2Addr_ABreakCurr_Report_Record_1,		*/C_COvercurrentEventNo			  },
	{(CBreakACurr_FF_1|EventDI),           E2Addr_BreakA_Curr_Degree,         E2Addr_BreakB_Curr_Degree    ,  /*E2Addr_ABreakCurr_Report_Record_1,		E2Addr_BBreakCurr_Report_Record_1,		*/C_AFailcurrentEventNo			  },
	{(CBreakBCurr_FF_1|EventDI),           E2Addr_BreakB_Curr_Degree,         E2Addr_BreakC_Curr_Degree,      /*E2Addr_BBreakCurr_Report_Record_1,		E2Addr_CBreakCurr_Report_Record_1,		*/C_BFailcurrentEventNo			  },
	{(CBreakCCurr_FF_1|EventDI),           E2Addr_BreakC_Curr_Degree,         E2Addr_PowerT_Rev_Degree    ,   /*E2Addr_CBreakCurr_Report_Record_1,		E2Addr_TrendRev_Report_Record_1,	 		*/C_CFailcurrentEventNo			  },
	{(CPowerTRev_FF_1|EventDI),            E2Addr_PowerT_Rev_Degree,          E2Addr_PowerA_Rev_Degree,       /*E2Addr_TTrendRev_Report_Record_1,		E2Addr_ATrendRev_Report_Record_1,			*/C_TReversecurrentEventNo	  },
	{(CPowerARev_FF_1|EventDI),            E2Addr_PowerA_Rev_Degree,          E2Addr_PowerB_Rev_Degree,       /*E2Addr_ATrendRev_Report_Record_1,		E2Addr_BTrendRev_Report_Record_1,			*/C_AReversecurrentEventNo	  },
	{(CPowerBRev_FF_1|EventDI),            E2Addr_PowerB_Rev_Degree,          E2Addr_PowerC_Rev_Degree    ,   /*E2Addr_BTrendRev_Report_Record_1,		E2Addr_CTrendRev_Report_Record_1,			*/C_BReversecurrentEventNo	  },
	{(CPowerCRev_FF_1|EventDI),            E2Addr_PowerC_Rev_Degree,          E2Addr_OverA_Lo_Degree,         /*E2Addr_CTrendRev_Report_Record_1,		E2Addr_AOverLoad_Report_Record_1,			*/C_CReversecurrentEventNo	  },
	{(COverALo_FF_1|EventDI),              E2Addr_OverA_Lo_Degree,            E2Addr_OverB_Lo_Degree    ,     /*E2Addr_AOverLoad_Report_Record_1,		E2Addr_BOverLoad_Report_Record_1,		 	*/C_AOverloadEventNo				  },
	{(COverBLo_FF_1|EventDI),              E2Addr_OverB_Lo_Degree,            E2Addr_OverC_Lo_Degree,         /*E2Addr_BOverLoad_Report_Record_1,		E2Addr_COverLoad_Report_Record_1,		 	*/C_BOverloadEventNo				  },
	{(COverCLo_FF_1|EventDI),              E2Addr_OverC_Lo_Degree,            E2Addr_PFactorT_Over_Degree    ,    /*E2Addr_COverLoad_Report_Record_1,		E2Addr_AcDemandOv_Report_Record_1,	 	*/C_COverloadEventNo				  },
	{(CPFactorT_FF_1|EventDI),             E2Addr_PFactorT_Over_Degree,       E2Addr_PFactorA_Over_Degree,         /*E2Addr_PowerFactor_Report_Record_1,	E2Addr_AllLossVolage_Report_Record_1,	*/C_OverpowerfactEventNo		  },
	{(CPFactorA_FF_1|EventDI),             E2Addr_PFactorA_Over_Degree,       E2Addr_PFactorB_Over_Degree,                                                                                         C_AOverpowerfactEventNo		  },
	{(CPFactorB_FF_1|EventDI),             E2Addr_PFactorB_Over_Degree,       E2Addr_PFactorC_Over_Degree,                                                                                         C_BOverpowerfactEventNo		  },
	{(CPFactorC_FF_1|EventDI),             E2Addr_PFactorC_Over_Degree,       E2Addr_NeutralCurrentAbnormal_Degree,                                                                                          C_COverpowerfactEventNo		  },
	{(COpenW_Degree|EventDI),              E2Addr_OpenW_Degree,               E2Addr_OpenCW_Degree    ,       /*E2Addr_OpenW_Report_Record_1,				E2Addr_OpenCW_Report_Record_1,			 	*/C_OpenMeterCoverEventNo		  },
	{(COpenCW_Degree|EventDI),             E2Addr_OpenCW_Degree,              E2Addr_BuyCurr_Degree,          /*E2Addr_OpenCW_Report_Record_1,				E2Addr_NoBalVol_Report_Record_1,		 	*/C_OpenTerminalCoverEventNo  },
	{(CConM_Degree|EventDI),               E2Addr_ConM_Degree,                E2Addr_RelayFa_Degree    ,      /*E2Addr_ConMEndEn_Report_Record_1,		E2Addr_RelayFaEndEn_Report_Record_1, 	*/C_MagneticCheckEventNo		  },
	{(CPowerFa_Degree|EventDI),            E2Addr_PowerFa_Degree,             E2Addr_MeterFa_Degree,          /*E2Addr_PowerFa_EndT_Report_Record_1,	E2Addr_SeriNoBalCurr_Report_Record_1,	*/C_PowerAbnormalEventNo		  },
	{(CMeterFa|EventDI),			       E2Addr_MeterFa_Degree,             E2Addr_ClockFa_Degree  ,  	/*E2Addr_MeterChipFault_Report_Record_1,        CEventUpTellTable_EndE2Addr,*/          C_MeterFaEventNo			},
	{(CClockFa|EventDI),			       E2Addr_ClockFa_Degree,             E2Addr_RelayOpen_Degree,  	/*E2Addr_ClockFault_Report_Record_1,		E2Addr_MeterChipFault_Report_Record_1,*/ C_ClockFaEventNo			},
	{(CDe_Clear_Degree|EventDI),           E2Addr_De_Clear_Degree,            E2Addr_RelayClose_Degree,       /*E2Addr_DemandClear_Report_Record_1,	E2Addr_EventClear_Report_Record_1,	  */C_DemandClearEventNo  },
	{(CProgram_Degree|EventDI),            E2Addr_Program_Degree,             E2Addr_AdjTime_Degree,          /*E2Addr_Program_Report_Record_1,			E2Addr_TolClear_Report_Record_1,		  */C_ProgramEventNo  },
	{(CAdjTime_Degree|EventDI),            E2Addr_AdjTime_Degree,             E2Addr_BroadcastTime_Degree,           /*E2Addr_AdjTime_Report_Record_1,			E2Addr_ProgPT_Report_Record_1,			  */C_AdjTimeEventNo  },
	{(CProgPT_Degree|EventDI),             E2Addr_ProgPT_Degree,              E2Addr_ProgTZ_Degree,           /*E2Addr_ProgPT_Report_Record_1,				E2Addr_ProgPZ_Report_Record_1,			  */C_ProgPTEventNo  },
	{(CProgTZ_Degree|EventDI),             E2Addr_ProgTZ_Degree,              E2Addr_ProgWRe_Degree,          /*E2Addr_ProgPZ_Report_Record_1,				E2Addr_ProgWRe_Report_Record_1,			  */C_ProgPZEventNo  },
	{(CProgWRe_Degree|EventDI),            E2Addr_ProgWRe_Degree,             E2Addr_ProgHol_Degree,        	 /*E2Addr_ProgWRe_Report_Record_1,			E2Addr_ProgSettD_Report_Record_1,		  */C_ProgWReEventNo  },
	{(CProgHol_Degree|EventDI),            E2Addr_ProgHol_Degree,             E2Addr_ProgAcC_Degree,          /*E2Addr_ProgHol_Report_Record_1,			E2Addr_ProgAcC_Report_Record_1,			  */C_ProgHolEventNo  },
	{(CProgAcC_Degree|EventDI),            E2Addr_ProgAcC_Degree,             E2Addr_ProgReC1_Degree,         /*E2Addr_ProgAcC_Report_Record_1,			E2Addr_ProgReC_Report_Record_1,			  */C_ProgAcCEventNo  },
	{(CProgReC_Degree|EventDI),            E2Addr_ProgReC1_Degree,            E2Addr_ProgSettD_Degree,        /*E2Addr_ProgReC_Report_Record_1,			E2Addr_ProgTPara_Report_Record_1,		  */C_ProgReCEventNo  },
	{(CProgSettD_Degree|EventDI),          E2Addr_ProgSettD_Degree,           E2Addr_ProgTPara_Degree,        /*E2Addr_ProgSettD_Report_Record_1,		E2Addr_OpenW_Report_Record_1,				  */C_ProgSettDEventNo	},
	{(CProgTPara_Degree|EventDI),          E2Addr_ProgTPara_Degree,           E2Addr_ProgLad_Degree,          /*E2Addr_ProgTPara_Report_Record_1,		E2Addr_ProgLad_Report_Record_1,			  */C_ProgTParaEventNo	},
	{(CProgLad_Degree|EventDI),            E2Addr_ProgLad_Degree,             E2Addr_ProgKD_Degree,           /*E2Addr_ProgLad_Report_Record_1,			E2Addr_Key_Update_Report_Record_1,	  */C_ProgLadEventNo	},
	{(CProgKD_Degree|EventDI),             E2Addr_ProgKD_Degree,              E2Addr_AbnorC_Degree,           /*E2Addr_Key_Update_Report_Record_1,		E2Addr_AbnorC_Report_Record_1,			  */C_Key_UpdateEventNo	},
	{(CAbnorC_Degree|EventDI),             E2Addr_AbnorC_Degree,              E2Addr_OpenW_Degree,            /*E2Addr_AbnorC_Report_Record_1,				E2Addr_BuyCurr_Report_Record_1,			  */C_AbnorCEventNo	},
	{(CBuyCurr_FF_Note_1|EventDI),         E2Addr_BuyCurr_Degree,             E2Addr_Return_M_Degree,         /*E2Addr_BuyCurr_Report_Record_1,			E2Addr_ReturnMoney_Report_Record_1,	  */C_BuyCurrEventNo},
	{(CReturn_M_Degree|EventDI),           E2Addr_Return_M_Degree,            E2Addr_LawlessC_Degree,         /*E2Addr_ReturnMoney_Report_Record_1,	E2Addr_ConMEndEn_Report_Record_1,		  */C_ReturnMoneyEventNo },
	{(CRelayFa_Degree|EventDI),            E2Addr_RelayFa_Degree,             E2Addr_PowerFa_Degree    ,      /*E2Addr_RelayFaEndEn_Report_Record_1,	E2Addr_PowerFa_EndT_Report_Record_1,  */C_RelayFaEndEnEventNo  },
	{(CRelayOpen_FF_1|EventDI),            E2Addr_RelayOpen_Degree,           E2Addr_Soft_I_J_Prog_Degree,    /*E2Addr_RelayOpen_Report_Record_1,		E2Addr_RelayClose_Report_Record_1,	  */C_RelayOpenEventNo	},
	{(CRelayClose_FF_1|EventDI),           E2Addr_RelayClose_Degree,          E2Addr_Program_Degree,          /*E2Addr_RelayClose_Report_Record_1,		E2Addr_ProgHol_Report_Record_1,			  */C_RelayCloseEventNo	},
	{(CSoft_I_J_Prog_Degree|EventDI),      E2Addr_Soft_I_J_Prog_1,            E2Addr_Rec_MeterSequence,       /*E2_Max_Addr,				E2_Max_Addr,		 				*/C_SoftIJProgEventNo},
	{(CLawlessC_Degree|EventDI),           E2Addr_LawlessC_Degree,            E2Addr_ConM_Degree,             /*E2_Max_Addr,				E2_Max_Addr,		 				*/C_LawlessCardEventNo},  /*�Ƿ��忨���ܴ��������쳣�忨��¼��������*/
	{(CBroadcastTime_Degree|EventDI), 	   E2Addr_BroadcastTime_Degree,	      E2Addr_ProgPT_Degree,           /*E2Addr_BroadcastTime_Report_Record_1, E2Addr_ProgPT_Report_Record_1,			  */C_BroadcastTimeEventNo  },
	{(CNeutralCurrentAbnormal_Note_1|EventDI), 	E2Addr_NeutralCurrentAbnormal_Degree,	E2Addr_De_Clear_Degree,/*E2Addr_BroadcastTime_Report_Record_1, E2Addr_ProgPT_Report_Record_1,			  */C_NeutralCurrentAbnormalEventNo  },
	{(CTol_Clear_Degree|EventDI), 			    E2Addr_Tol_Clear_Degree,       E2Addr_Tol_Clear_In_End,       /*E2_Max_Addr,				E2_Max_Addr,		 			*/C_TolClearEventNo },		/*698���������޸����塢�¼���������б�ʱ�����Ӧ�¼���¼*/
	{(CEven_Clear_Degree|EventDI),         E2Addr_Even_Clear_Degree,           E2Addr_Rec_Meter_Degree,       /*E2_Max_Addr,				E2_Max_Addr,		 				*/C_EventClearEventNo },
};
#define Str_EvenTableE2_Len  (sizeof(Str_EvenTableE2)/sizeof(Str_EvenTable))/*�ñ�� e2�����ݳ������¼������й�ϵע���¼��������*/

/****************************�ڲ�����*****************************/
uchar8 SF_Find1Table_Data(uchar8  V_Data_Id3,ushort16 * P_Line);
uchar8 SF_Find2Table_DIParamChild(uchar8  V_Data_Id2,ushort16 * P_Line);
uchar8 SF_Find2Table_Data( uchar8  V_WR_Mes,ulong32  V_Data_Id,ushort16 * P_Data_Length,Str_2Table  * PStr_2Table,ushort16 * P_Line,ushort16 V_MaxLine);
uchar8 SF_WriteE2Three(ushort16 V_E2Addr,uchar8 V_DataLen,uchar8 * P_Data);
uchar8 SF_WriteFRAMThree(ushort16 V_E2Addr,uchar8 V_DataLen,uchar8 * P_Data);
uchar8 SF_WriteE2Three698(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 * P_Data);
uchar8 SF_WR_E23_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 * P_Data);
uchar8 SF_WR_E23_RAM_Data698(Str_3aTable * PStr_3aTable_E23RAM,ushort16 V_DataLen,uchar8 * P_Data,uchar8 V_DT_Type,uchar8 V_DI);
uchar8 SF_WR_E23_RAM_EnergyData(Str_3aTable * PStr_3aTable_E23RAM,ushort16 V_3aTable_Line,ushort16 V_DataLen,uchar8 * P_Data,uchar8 V_DT_Type,uchar8 V_DI);
uchar8 SF_WR_E23_RAM_Data(Str_3aTable * PStr_3aTable_E23RAM,ushort16 V_3aTable_Line,ushort16 V_DataLen,uchar8 * P_Data,uchar8 V_DT_Type,uchar8 V_DI);
uchar8 SF_Read_E21CRC_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 * P_Data);
uchar8 SF_Read_FRAM1CRC_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 * P_Data);
uchar8 SF_ReadE2Three(ushort16 V_E2Addr,uchar8 V_DataLen,uchar8 * P_Data);
#if 0
uchar8 SF_ReadFRAMThree1(ushort16 V_E2Addr,uchar8 V_DataLen,uchar8 * P_Data);
#endif
uchar8 SF_ReadFRAMThree(ushort16 V_E2Addr,uchar8 V_DataLen,uchar8 * P_Data);
uchar8 SF_ReadE21(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 * P_Data,uchar8 V_DT_Type,uchar8 V_WR_Mes);
ushort16 SF_GetOffAddr(Str_4Table * PStr_4TableAddr,ulong32 V_Data_Id,uchar8 V_Type,uchar8 V_4Table_Len);
void SF_GetFlashAddr(ulong32 V_NumE2,ulong32 V_StartFlashAddr,ushort16 V_NoteDataLength,ulong32 V_EndFlashAddr,ulong32 * P_ReturnFlashAddr);
uchar8 SF_WriteFlash(ulong32 V_FlashAddr,uchar8 * P_Data,ushort16 V_Data_Length,uchar8 V_EvenSign);
uchar8 SF_WriteFlash_Data(uchar8 * P_Data,ushort16 V_Data_Length,Str_3cTable * PStr_3cTable,ulong32 V_Data_Id,ushort16 V_3cTable_Line,uchar8 V_Type);
uchar8 SF_WR_E21CRC_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 * P_Data);
uchar8 SF_WR_FRAM1CRC_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 * P_Data);
uchar8 SF_WR_E21_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 * P_Data);
uchar8 SF_WR_RAM_Data(uchar8 * P_RamAddr,ushort16 V_DataLen,uchar8 * P_Data,uchar8 V_DT_Type,uchar8 Msg_Num);
uchar8 SF_WR_RAMCRC_Data(uchar8 * P_RamAddr,ushort16 V_DataLen,uchar8 * P_Data);
uchar8 SF_Re_E23_RAM_Data698(Str_3aTable * PStr_3aTable_E23RAM,ushort16 V_DataLen,uchar8 * P_Data);
uchar8 SF_Re_E23_RAM_Data(Str_3aTable * PStr_3aTable_E23RAM,ushort16 V_3aTable_Line,ushort16 V_DataLen,uchar8 * P_Data,uchar8 V_DT_Type,uchar8 V_DI,ulong32 V_Data_Id);
uchar8 SF_Re_E23_Data(ushort16 V_E2Addr,ushort16 V_DataLen,uchar8 * P_Data,uchar8 V_DT_Type,uchar8 V_WR_Mes);
uchar8 SF_ReadFlash_Data(uchar8 * P_Data,ushort16 V_Data_Length,ulong32 Str_3TableAddr,ulong32 V_Data_Id,ushort16 V_3cTable_Line,uchar8 V_Type,uchar8 V_WR_Mes);
uchar8 SF_Re_RAM_Data(uchar8 * P_RamAddr,ushort16 V_DataLen,uchar8 * P_Data,uchar8 V_DT_Type,uchar8 V_DI0);
uchar8 SF_Re_RAMCRC_Data(uchar8 * P_RamAddr,ushort16 V_DataLen,uchar8 * P_Data);
uchar8 SF_Read_Data(ulong32 V_ulData_Id, uchar8 *pV_ucData, ushort16 *pV_usData_Length, uchar8 V_MesNum, ushort16 *pV_usDataEncode);
ushort16 SF_JudgeWriteDataLen( uchar8  V_DI2);
void SF_GetCurrLoadProfileFlashAddr(ushort16 V_Len,ulong32 * V_W_FlashAddr,ushort16 V_E2Addr_LoadP_Flash_Late,ushort16 V_E2Addr_LoadP_Flash_Ear,ulong32 V_FlashStAddr_LoadProfile,ulong32 V_FlashEndAddr_LoadProfile);
#if 0
void SF_EarlistLoadRefresh_E2_FlashLoadProfileMode(ulong32 V_WR_FlashAddr);
#endif
void SF_EarlistLoadProfileFlashAddrAdjust(ushort16 V_E2Addr_LoadP_Flash_Late,ushort16 V_E2Addr_LoadP_Flash_Ear,ulong32 V_FlashStAddr_LoadProfile,ulong32 V_FlashEndAddr_LoadProfile);
#if 0
uchar8 SF_Refresh_E2_FlashLoadProfileMode(ulong32 V_WR_FlashAddr,uchar8 V_Mode);
#endif
uchar8 SF_Write698FreezeData(uchar8 V_DI2Temp, uchar8  Message_Num, uchar8 * 	P_Data, ushort16 V_Data_Length);
void SF_ChageTime_ChageFlashNote(ulong32 V_FlashAddr,uchar8 V_Order,uchar8 V_ProNum);
#if 0
uchar8 SF_GetFlashAddrInE2BlockNum(ulong32 V_WR_FlashAddr);
uchar8 SF_CombOneFlashPageMode(uchar8 * V_Mode,uchar8 V_ModeNum);
void SF_ChageTime_RefreshE2_FlashLoadProfileMode(ulong32 V_FlashAddrLate,uchar8 V_Line,ulong32 V_FlashAddrEar);
#endif
ulong32 SF_GetFixedLoadModeNoteFlashAddr(uchar8 V_ProNum,uchar8 V_Order,ulong32 V_FindFlashAddr);
ulong32 SF_FindOneFlashPageGiveTimeFlashAddr(uchar8 V_ProNum,uchar8 V_Order,ulong32 V_FindFlashAddr,uchar8 * P_FixTime,uchar8 V_LoadDichotomyFindWay);
ulong32 SF_LoadDichotomyFixedFlashData(uchar8 V_ProNum,uchar8 V_Order,uchar8 * P_FixTime,ulong32 V_FlashAddrEar,ulong32 V_FlashAddrLate,uchar8 V_LoadDichotomyFindWay);
ulong32 SF_LoadDichotomyFlashData(uchar8 V_ProNum,uchar8 V_Order,uchar8 * P_FixTime,ulong32 V_FlashAddrEar,ulong32 V_FlashAddrLate,uchar8 V_LoadDichotomyFindWay);
ulong32 SF_FindLoadProfileFlashPage(void);
ushort16 SF_GetMinFreezeNum_OADTab(uchar8 V_ProNum,uchar8 * P_Data,ushort16 V_DataLen);
ushort16 SF_GetFreezeSaveDeep( uchar8  V_DI2Temp);
uchar8 SF_Clear_Engry(uchar8 V_D_SafeFlag);
uchar8 SF_Clear_Event(uchar8 V_D_SafeFlag);
uchar8 SF_Clear_Other(uchar8 V_D_SafeFlag);
uchar8 SF_Clear_Parm(uchar8 V_D_SafeFlag);
uchar8 SF_Clear_Custom(uchar8 V_D_SafeFlag);

ulong32 SF_FindEvenFlashPage(void);
#if 0
uchar8 SF_WriteMeterICData(uchar8 * P_Data,uchar8 V_MeterICData_Num);      /*дУ������*/
#endif
uchar8 SF_AllDataZero_Judge(uchar8 * P_Data,uchar8 V_DataLen);
ulong32 SF_FindMinFreezeFirstVolidOAD(ulong32 * P_Data_Id_OAD);
/******************�ṩ�ⲿ�ӿں���**********************/
uchar8 InF_Write_RecMeterData(uchar8 Msg_Num,uchar8 * P_Data,uchar8 V_Data_Length,uchar8 V_W_Safe_Flag,uchar8 V_Data_Num); 	/*дУ�����ݽӿں���*/
uchar8 InF_Write_Data(uchar8 Msg_Num,ulong32 V_Data_Id,uchar8 * P_Data,ushort16 V_Data_Length,uchar8 V_W_Safe_Flag); 			/*д���ݲ�ӿں���*/
uchar8 InF_Read_RecMeterData(uchar8 V_Data_Num,uchar8 * P_Data,uchar8 * P_Data_Length);                              			/*��У������*/
uchar8 InF_Read_Data(ulong32 V_ulData_Id, uchar8 *pV_ucData, ushort16 *pV_usData_Length, ushort16 *pV_usDataEncode);           /*�����ݲ�ӿں���*/
#if 0
uchar8 InF_Read_Data_For_Dis(ulong32 V_ulData_Id, uchar8 *pV_ucData, ushort16 *pV_usData_Length);                              /*�����ݲ�ӿں���,רΪ��ʾģ���ṩ�ӿں���*/
#endif
void InF_PowerOn_CurrEnergyDeal(void);                        /*�ϵ��������ӿں���,���ȵ���*/
#if 0
void InF_PowerDown_CurrEnergySave(void);                      /*��ǰ����ͣ�籣��ӿں���,Ŀǰ�ݲ����øù���,���ȵ���*/
#endif
void InF_ChangeTime_LoadProfileCover(void);                   /*�޸�ʱ�为�ɼ�¼���ǽӿں���,ͨ�ŵ���*/

void SF_UpdateE2CurrEnergy(void);
uchar8 InF_ReadLoadData(ulong32 V_Data_Id,uchar8 * P_FixTime,uchar8 * P_Data,uchar8 * V_BlockNum,uchar8 * V_Length,uchar8 V_ReadSign);	/**�����ɼ�¼**/
uchar8 InF_Total_Clear(uchar8 Msg_Num,uchar8 V_CurrentState,uchar8 C_Safe_Flag);	/*�������,ͨ�ŵ���*/
uchar8 InF_EventNote_Clear(uchar8 Msg_Num,ulong32 V_Data_Id,uchar8 C_Safe_Flag);	/*�¼���¼����,ͨ�ŵ���*/
uchar8 InF_Demand_Clear(uchar8 Msg_Num,uchar8 C_Safe_Flag);                     	/*��������,ͨ�š��������*/
void Data_CruiseCheck_Message(Str_Msg_Parameter * P_Msg_Parameter);            	/*���ݲ�Ѳ�����򣬵���ÿ5s���������ô�����*/
void InF_Initial_Data(void);            /*��ʼ�����ݲ���������ȵ���*/
uchar8 InF_EventNumFind(ulong32 V_Data_Id);    /*�ṩ�¼���¼�ӿں���*/
uchar8 InF_ReadLastTimeLoadData(ulong32 V_Data_Id,uchar8 * P_FixTime,uchar8 * P_Data,uchar8 * V_BlockNum,uchar8 * V_Length);    /*���ɼ�¼ģ����ϴθ��ɼ�¼�ӿں���*/
uchar8 InF_RecMeterNote_Clear(uchar8 Msg_Num,uchar8 C_Safe_Flag);/*��У���¼*/
uchar8 InF_ReadFreezeData(ulong32 * P_Data_Id_OAD,uchar8 * P_FixTime,uchar8 * P_Data,ushort16 * V_BlockNum,ushort16 * V_Length,ushort16 V_IntervalTime,uchar8 * pV_FreezeTimeBuf,uchar8 V_Mode);
uchar8 InF_ReadEventData(ulong32 * P_Data_Id_OAD,uchar8 * P_FixTime,uchar8 * P_Data,uchar8 * V_NextSign,ushort16 * P_Data_Length,uchar8 V_timeFlash);
void InF_ReadE2_Flash_Data(uchar8  * PV_Data,uchar8 V_Len,uchar8 V_Sign,ulong32 V_Addr);/*��ӵ��Դ���*/
void InF_RAMDataRecoverFromE2(void);/*��ͨ��ģ�鴥�����ã�����E2���ݶ�RAM���ݽ��лָ�*/
uchar8 SF_Read_698SpecialData(ulong32 V_ulData_Id, uchar8 *pV_ucData, ushort16 *pV_usData_Length, ushort16 *pV_usDataEncode);
void SF_EraseCodeFlash_Sector(ulong32 V_ulAddInSector);
void SF_WriteCodeFlash(ulong32 V_ulCodeFlashAdd, uchar8 *pV_ucDataIn, ushort16 V_usDataInLen);
#if 0
void SF_EraseCodeFlash_Block(ulong32 V_ulAddInBlock);
#endif
uchar8 SF_Deal_FF86(ulong32 V_Data_Id,uchar8 * P_Data,ushort16 V_Data_Length);
uchar8 SF_Deal_UpdataFlag(uchar8 V_ucOperationFlag, uchar8 *pV_ucData, ushort16 V_usDataIn_Len);

/******�������̿����ֽṹ��***/
typedef struct
{
	uchar8	ControlFlag[4];	/*�������̿��Ʊ�־�������ݸ�2�ֽ�Ϊ������־��96 87 ����2�ֽ�Ϊ96 88 ��CRC16У��ֵ8A 4A�����ֽ���ǰ��*/
	uchar8	FlowFlag;		/*�������̿���״̬��0��ʾδ��������ģʽ��1��ʾ��������ģʽ����δ�·������汾��Ϣ��2��ʾ֧������*/
	uchar8	OverTimer;		/*�������̿��Ƴ�ʱ��ʱ������ʼֵ0������Ӧ��ȷ������ֵ��ʱ��ʱ����reset��ʱ����ֵ2s��������ֵ10s*/
	uchar8	ucCRC[2];		/*��������CRC*/
}Str_UpdataFlag_Type;
static Str_UpdataFlag_Type SStr_UpdataFlag;		/*�������̿���*/
#define C_Str_UpdataFlag_Len	sizeof(Str_UpdataFlag_Type)
#define C_UpdataFlag_OKFlag		0x96878A4A		/*��־��ȷ����*/

#define C_Updata_Init			0xFF			/*��ʼ״̬*/
#define C_Enter_UpdataFlag		1				/*��������ģʽ*/
#define C_WriteFlag_OK			2				/*�汾�˶���ȷ*/
#define C_ResetFlag_OK			3				/*reset flag*/
#define C_TimerDecrease			4				/*if OverTimer > 0, Timer--*/
#define C_OverTimer_10s			10				/*�������10s��ʱ��*/
#define C_OverTimer_2s			2				/*�������2s��ʱ��*/



#pragma pack()

#endif
