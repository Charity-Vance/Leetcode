/*******************************************************************************
Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
File name:     Display.h
Version:       V1
Author:        
Date:          2014-3-12
Description:   
---------------------------------------------------------------------------------
History1:      第1次修改
内容1. Date:   20211021
   	   Author: lx
       Modification:
	   ---------------------------------------------------------------------------
内容2. Date:
   	   Author:
       Modification:
----------------------------------------------------------------------------------
History2:      第2次修改
内容1. Date:
   	   Author:
       Modification:
	   ---------------------------------------------------------------------------
内容2. Date:
   	   Author:
       Modification:
******************************************************************************/
#ifndef	__Display_H
#define	__Display_H

#include "Public.h"

#pragma pack(1)                     /*1字节对齐*/

/*****************************状态字符显示虚拟缓存bit位宏定义,与虚拟缓存表格一一对应*****************************************/
#define	CBit_AxisSign			      0x10			/*坐标轴          */
#define	CBit_Q1Sign			          0x01			/*1象限显示符号   */
#define	CBit_Q2Sign			          0x02			/*2象限显示符号   */
#define	CBit_Q3Sign			          0x04			/*3象限显示符号   */
#define	CBit_Q4Sign			          0x08			/*4象限显示符号   */
#define	CBit_Step1Sign			      0x01			/*阶梯1           */
#define	CBit_Step2Sign			      0x02			/*阶梯2           */
#define	CBit_Step3Sign			      0x04			/*阶梯3           */
#define	CBit_Step4Sign			      0x08			/*阶梯4           */
#define	CBit_Rate1Sign			      0x10			/*费率1           */
#define	CBit_Rate2Sign			      0x20			/*费率2           */
#define	CBit_Rate3Sign			      0x40			/*费率3           */
#define	CBit_Rate4Sign			      0x80			/*费率4           */
#define	CBit_LSign			          0x80			/*阶梯符号L       */
#define	CBit_TSign			          0x40			/*费率符号S       */
#define	CBit_GPRSSign			      0x08			/*天线符号        */
#define	CBit_GPRSSignalSign1		  0x80			/*信号强度1       */
#define	CBit_GPRSSignalSign2		  0xC0			/*信号强度2,显示包括信号强度1*/
#define	CBit_GPRSSignalSign3		  0xE0			/*信号强度3       */
#define	CBit_GPRSSignalSign4		  0xF0			/*信号强度4       */
#define	CBit_ModuleComSign			  0x04			/*模块通信符号    */
#define	CBit_ComSign			      0x02			/*通信电话符号    */
#define	CBit_ComChannel1Sign		  0x01			/*通道1符号       */
#define	CBit_ComChannel2Sign		  0x80			/*通道2符号       */
#define	CBit_ProgramEnableSign		  0x40			/*编程有效        */
#define	CBit_HoldUpSign			      0x20			/*身份认证挂起    */
#define	CBit_PublicKeySign		  	  0x10			/*公钥标志        */
#define	CBit_AlarmSign			      0x08			/*报警标志        */
#define	CBit_ReadCardSign		  	  0x04			/*“读卡”标志	  */
#define	CBit_DoingSign			      0x02			/*“中”标志	  */
#define	CBit_SuccessSign		      0x01			/*成功            */
#define	CBit_FailSign			      0x80			/*失败            */
#define	CBit_PurchaseSign			  0x40			/*请购电          */
#define	CBit_OverdrawSign			  0x20			/*透支            */
#define	CBit_RealayOpenSign			  0x10			/*拉闸            */
#define	CBit_UaSign			          0x80			/*Ua              */
#define	CBit_UbSign			          0x40			/*Ub              */
#define	CBit_UcSign			          0x20			/*Uc              */
#define	CBit_NegativePhaseSign		  0x10			/*逆相序          */
#define	CBit_IaNegativeSign			  0x08			/*Ia电流前“-”   */
#define	CBit_IaSign			          0x04			/*Ia              */
#define	CBit_IbNegativeSign			  0x02			/*Ib电流前“-”   */
#define	CBit_IbSign			          0x01			/*Ib              */
#define	CBit_IcNegativeSign			  0x80			/*Ic电流前“-”   */
#define	CBit_IcSign			          0x40			/*Ic              */
#define	CBit_TimeTable1Sign			  0x08			/*第一套时段表    */
#define	CBit_TimeTable2Sign			  0x04			/*第二套时段表    */
#define	CBit_RTCBatterySign			  0x02			/*时钟电池欠压    */
#define	CBit_PowerBatterySign		  0x01			/*停抄电池欠压    */
#define	CBit_HoardingSign			  0x10			/*超囤积标志      */
#define	CBit_CurrentStep			  0x80			/*当前套阶梯      */
#define	CBit_BakStep			      0x40			/*备用套阶梯有效符号*/
/*******************************小数点宏定义,根据显示缓存位 *******************/
/*****显示缓存，与虚拟显示表格缓存对应*****/
#define C_OneDot8P                  0x01
#define C_TwoDot7P                  0x02
#define C_ThreeDot6P                0x10
#define C_FourDot5P                 0x08
#define C_FiveDot4P                 0x20
#define C_SixDot3P                  0x40
#define C_SevenDot2P                0x80
#define C_CoL1Dot                   0x04
#define C_CoL2Dot                   0x01
/***显示序号，列辅助汉字表格用*，其中0--7表示0-7位小数点******/
#define C_CoL15PDot                 8     /*XXXX:XXXX*/
#define C_CoL25P3P7PDot             9     /*XX.XX.XX:XX*/
#define C_CoL27PDot                 10    /*XXXXXX：XX*/ 
#define C_CoL2CoL15P7PDot           11    /*XXXX：XX：XX*/
#define C_CoL2CoL15P3P7PDot         12    /*XX.XX:XX:XX*/   
#define C_5P7PDot                   13    /*XXXX.XX.XX*/ 
#define C_CoL15P7PDot               14    /*XXXX：XX.XX*/  
#define C_5P3P7PDot                 15    /*XX.XX.XX.XX*/
/*****************************显示单位宏定义********************************/
/*********显示缓存，与虚拟显示表格缓存对应************/
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
/*********显示序号，列辅助汉字表格用*******/
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

#define C_DisCurr                   0x80      /*“当前”显示*/
#define C_DisLast                   0x40      /*“上”显示*/
#define C_DisLossVol                0x06      /*“失压”显示*/
#define C_DisLossCurr               0x05      /*“失流”显示*/
#define C_DisAPhase                 0x80      /*“A”显示*/
#define C_DisB                      0x40      /*“B”显示*/
#define C_DisC                      0x20      /*“C”显示*/
#define C_DisNegativeSign           0x20      /*数据区"-"显示*/
#define C_DisFanXiang               0x0A      /*"反向"显示*/ 
#define C_DisMonth                  0x20      /*“月”显示*/
#define C_DisE                      0xE0      /*"E0"显示*/
#define C_DisR                      0x01      /*"r"显示?*/
#define C_DisHenggang               0x01      /*"-"显示?*/  
/****************************其他宏定义****************************************/
#define C_ALLScreenDisplay         0x01           /*全屏显示*/
#define C_CheckDisplay             0x02           /*液晶查看*/
#define C_KeyDisplay               0x03           /*按键显示*/
#define C_AutoDisplay              0x04           /*自动轮显*/
#define C_CardAbnormalDisplay      0x05           /*插卡异常显示*/
#define C_AlwaysDisplayNiu         0xFFFF         /*常显*/
#define C_TwinkleDisplayNiu        0xFFFE         /*闪烁*/
#define C_NotDisplayNiu            0x0000         /*不显*/
/*#define C_AlwaysDisplayBit         0xC0*/       /*常显,用于消息参数解析,Public 中已定义*/
/*#define C_TwinkleDisplayBit        0x40*/       /*闪烁*/
/*#define C_NotDisplayBit            0x00*/       /*不显*/

#define C_DefaultDisplayTime5s     10                  /*5s:500ms基准单位,默认显示时间*/
#define C_Display60s               120                 /*60s*/ 
#define C_Display30s               60                  /*30s*/
#define C_Display10s               20                  /*10s*/
 
#define C_DefaultDisDi             CPos_Ac_Tol_En_0    /*默认显示，正向有功总电能*/ 
#define C_DefaultDisDiRelated      0xFFFFFFFF    

#define C_DefaultDisScreenNum      1                  /*默认显示屏数*/ 

#define C_ALLScreenDisplayDi       0xFFFFFFFF     /*初始化全屏状态DI*/
#define C_DisplayDataByte          29             /*显示缓存字节数*/
#define C_RAM_Max                  250            /*用于存放读数据最大缓存*/  

#define C_ProgHolScreenNum91       48                                    /*节假日0-48屏显示分割*/
#define C_ProgHolScreenNumA1       (C_ProgHolScreenNum91+48)             /*50-99屏显示分割*/
#define C_ProgHolScreenNumB1       (C_ProgHolScreenNumA1+48)            
#define C_ProgHolScreenNumC1       (C_ProgHolScreenNumB1+48)            
#define C_ProgHolScreenNumD1       (C_ProgHolScreenNumC1+48)            
#define C_ProgHolScreenNumE1       (C_ProgHolScreenNumD1+16)            
            
#define C_ProgPTScreenNumC1        58                                    /*时段表0-58屏显示分割*/
#define C_ProgPTScreenNumD1        (C_ProgPTScreenNumC1+56)              /*59-114屏显示分割*/
#define C_ProgPTScreenNumE1        (C_ProgPTScreenNumD1+56)             
#define C_ProgPTScreenNumF1        (C_ProgPTScreenNumE1+56)   

#define C_ChinaeseLineUnit         5     /*汉字表格结构体，单位是第6列，0-5*/          
#define C_ChinaeseLineDot          6     /*汉字表格结构体，小数点是第7列，0-6*/          
#define C_ChinaLineDataLenKillZero 7     /*汉字表格结构体，第8列，低4位表示该显示对应的数据长度，高4位表示灭零特点0-7*/          
#define C_ChinaeseLineDataOffSet   8     /*汉字表格结构体，第9列，表示数据偏移*/ 

#define C_GetChinaDataLenBit0x07   0x07 /*取汉字表格结构体，第8列，低3位表示该显示对应的数据长度，第3位，表示是否需要符号位处理 */          
#define C_NeedSignBit0x08          0x08 /*汉字表格结构体，第8列，第3位表示该显示对应的数据，是否需要符号位处理,0x08表示需要符号位 */         


#define C_PreScreenDisDataLen      5     /*每屏主数据显示数据最大长度字节数,正常4个字节，电量小数位可设置，该为最大5个字节 */

#define C_ParameterMaxLen          40    /*消息传递参数最大缓存，可能需要修改，最大只能放10个PT(4字节参数)*/
#define C_CardDis                  0xAA  /*插卡显示状态*/
#define C_NoCardDis                0x55  /*非插卡显示状态*/
#define C_TimingInitSignTime10min  1200  /*以上电500ms为基本节拍，每10min刷新1次状态字符数据源，增加可靠性*/
#define C_ShutBackLEDTime5s        10    /*以上电500ms为基本节拍*/
#define C_MoneySign                0x55  /*插卡前2s显示*/
/*#define C_Baud600                  0x02*/   /*public中已定义*/
/*#define C_Baud1200                 0x04*/
/*#define C_Baud2400                 0x08*/
/*#define C_Baud4800                 0x10*/
/*#define C_Baud9600                 0x20*/
/*#define C_Baud19200                0x40*/
/*00默认按照数据长度hex转BCD，10不需要转，20单字节转，40表示时间整个转，高2字节单独转*/
/*#define C_NeedDataChange             0x80*/   /*698中需量发生时间格式与645不同，年显示2字节，秒补一个字节0x00*/ 
#define C_NeedDataChange             0x40   /*高两字节单独转，其他字节单独转*/   
#define C_NeedSingleByteChange       0x20   /*单字节hex转bcd*/  
#define C_NoNeedChange               0x10   /*不需要转换*/  

#define C_DisRelatedOffset             0x04   /*关联列表偏移*/  
#define C_DisScreenNumOffset           0x08   /*显示屏数偏移*/  

#define C_MainDataEn_offset0           0      /*主显示数据第1字节*/ 
#define C_MainDataEn_offset1           1      /*主显示数据第2字节*/ 
#define C_MainDataEn_offset2           2      /*主显示数据第3字节*/ 
#define C_MainDataEn_offset3           3      /*主显示数据第4字节*/
#define C_MainDataEn_offset4           4      /*主显示数据第4字节*/

#define C_EnBorrowPoint_Flag_1         0x9999999999       /*借位显示判断标志，大于999999.9999，借1位*/
#define C_EnBorrowPoint_Flag_2         0x99999999999      /*借位显示判断标志，大于9999999.9999，借2位*/
#define C_EnBorrowPoint_Flag_3         0x999999999999     /*借位显示判断标志，大于99999999.9999，借3位*/
#define C_EnBorrowPoint_Flag_4         0x9999999999999    /*借位显示判断标志，大于999999999.9999，借4位*/

#define C_EnBorrowPoint_0               0               /*借位位数，小于等于999999.9999，借0位*/
#define C_EnBorrowPoint_1               1               /*借位位数，大于999999.9999，借1位*/
#define C_EnBorrowPoint_2               2               /*借位位数，大于9999999.9999，借2位*/
#define C_EnBorrowPoint_3               3               /*借位位数，大于99999999.9999，借3位*/
#define C_EnBorrowPoint_4               4               /*借位位数，大于99999999.9999，借4位*/

#define C_PreEnDisPoint                 4               /*精确电能显示小数位数*/

#define C_RecordNum_offset             9      /*显示buffer[9],1P、数字1，上XX月中的“XX”*/

#define C_EngyRate18_offset            25     /*显示电能费率中18在真值表中的位置buffer25*/
#define C_Ladder8_offset               26     /*显示L8中8在真值表中的位置buffer25*/  
#define C_Rate18_offset                27     /*显示T18中18在真值表中的位置buffer27 */ 
#define C_MainDataHig_offset           28     /*显示最高两位数据在真值表buffer28*/  


/**********************************私有全局变量********************************************************************/
uchar8  GV_ucDisplayData[C_DisplayDataByte];          /*显示缓存*///
uchar8  GV_KillZeroNum;                               /*全局变量表示灭零数,FF表示为异常代码显示*/
uchar8  GV_PowerOffAutoDisScreenNum;                  /*自动循显屏数，只是低功耗时用，避免低功耗时重复读数据层*/
ushort16  GV_usPowerOffAutoDisScreenTime;             /*自动循显每屏显示时间，只是低功耗时用，避免低功耗时重复读数据层*///
uchar8  GV_PowerOffDisState;                          /*低功耗时，当前显示状态，供低功耗调度获取，初始化为显示,低功耗循显结束，设置为不显*/
uchar8  GV_CardDisSign;                               /*插卡显示标志，初始化为非插卡显示状态0x55(有电、没电初始化)；当显示消息源为card时，置该标志为0xAA，表示插卡显示状态*/
/*uchar8  testniu; */                                 /*此时，显示做到底掉底层显示，然后该标志设置为0x55，非插卡显示状态*/
uchar8  GV_CardAbnDisplayNum;                         /*插卡异常显示号*/                        
ushort16 GV_TimingInitSignTime;                       /*定时刷新状态字符数据源定时器，定时到刷新，增加可靠性，在InF_Display_Init初始化函数中置0，在SF_PowerOnDisplay500msTimer函数中++判断*/                        
uchar8  GV_ShutBackLEDTime;                           /*上电闭锁背光定时器，上电5s内背光点亮(不判断电源电压，上电5s后，背光点亮，才判断电源电压)*/                        
/*uchar8  GV_PowerOnChangeScreenFlag;*/                   /*换屏标志，初始化为0，在上电500ms函数中换屏定时器GV_Str_DisplayFlag.SV_usDisplayTimer为0时设置为55*/
uchar8  GV_RemainMoney[2][CLChargeBal_BCD];           /*用于购电前剩余、透支金额两秒显示  当该标志为55时，调用硬件初始化LCD驱动接口函数，重新配置驱动寄存器，防止死锁(即有电情况下，换屏时初始化液晶驱动)*/
/*uchar8  GV_DispAllScreenMode; */                        /*全显模式*/
typedef struct
{
    ushort16 Time;/*Time：表示显示时间；*/
    uchar8 Type;  /*Type：显示字符与显示方式合用同一个字节，该字节的高两位表示显示方式*/
                  /*(01:闪烁；00：关闭；11常显,组合命令，当显示时间为0xFFFF时，表示常显，*/
                  /*有具体时间值时，显示时间按具体时间)，第6位表示表示显示字符内容(LED、继电器输出也作为一个字符)；*/
}Str_DisplayStatus;/*插卡异常显示借用该结构体,Type表示错误类型，BCD格式*/


typedef  struct
{
	 ushort16 Timer;	        /*显示时间,FFFF表示常显,FFFE表示闪烁*/
	 uchar8 SourceNo;	        /*源消息号*/  
}Str_DisplaySignMesNum;		    /*显示状态字符结构体 */

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
   ulong32 PStr_DisplaySignMesNum;       /*该字符对应显示状态字符结构体Str_DisplaySignMesNum地址，可能是数组*/
   uchar8 Str_DisplaySignMesNumLen;      /*Str_DisplaySignMesNum长度*/
   uchar8 StateNum;	                     /*状态显示通用字符定义*/                      
   uchar8 * PDisplyBuff;                 /*该字符对应虚拟缓存地址，当对应为背光、指示灯、报警继电器等变量状态时，该变量不处理初始化为空C_NULL*/                  
	 uchar8 DisplyBuffBit;               /*该字符对应虚拟缓存所对应数据位*/                
}Str_DisplaySign;		                 /*通用状态字符显示结构体*/    
 
const Str_DisplaySign  GV_Str_DisplaySign[]=
{ /*ulong32 PStr_DisplaySignMesNum                           uchar8Str_DisplaySignMesNum长度    uchar8状态显示通用字符定义  uchar8 *该字符对应虚拟缓存地址 uchar8该字符对应虚拟缓存所对应数据位*/
  {(ulong32)(&GV_Str_DisplaySignMesNum_AxisSign[0]),          GV_Str_DisplaySignMesNum_AxisSignLen,          C_AxisSign,          &GV_ucDisplayData[10],         CBit_AxisSign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_Q1Sign[0]),            GV_Str_DisplaySignMesNum_Q1SignLen,            C_Q1Sign,            &GV_ucDisplayData[10],         CBit_Q1Sign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_Q2Sign[0]),            GV_Str_DisplaySignMesNum_Q2SignLen,            C_Q2Sign,            &GV_ucDisplayData[10],         CBit_Q2Sign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_Q3Sign[0]),            GV_Str_DisplaySignMesNum_Q3SignLen,            C_Q3Sign,            &GV_ucDisplayData[10],         CBit_Q3Sign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_Q4Sign[0]),            GV_Str_DisplaySignMesNum_Q4SignLen,            C_Q4Sign,            &GV_ucDisplayData[10],         CBit_Q4Sign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_LSign[0]),             GV_Str_DisplaySignMesNum_LSignLen,             C_LSign,             &GV_ucDisplayData[11],         CBit_LSign},
  {(ulong32)(&GV_Str_DisplaySignMesNum_TSign[0]),             GV_Str_DisplaySignMesNum_TSignLen,             C_TSign,             &GV_ucDisplayData[11],         CBit_TSign},
  {(ulong32)(&GV_Str_DisplaySignMesNum_GPRSSign[0]),          GV_Str_DisplaySignMesNum_GPRSSignLen,          C_GPRSSign,          &GV_ucDisplayData[12],         CBit_GPRSSign},         
  {(ulong32)(&GV_Str_DisplaySignMesNum_GPRSSignalSign1[0]),   GV_Str_DisplaySignMesNum_GPRSSignalSign1Len,   C_GPRSSignalSign1,   &GV_ucDisplayData[12],         CBit_GPRSSignalSign1},         ///*GPRS 信号强度*///
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
   ulong32 LocalMeterDI;       /*本地表独有标识码*/
   uchar8  CompByteNum;        /*上面标识码，比较字节数，从高位开始*/
}Str_LocalMeterDI;		         /*本地标识码独有结构体*/    

const Str_LocalMeterDI GV_Str_LocalMeterDI[]=           /*本地表特有标识码*/
{
	 {CChargeBal_Hex_Cent,   0x03},               /*当前剩余金额BCD格式、当前透支金额BCD格式*/
	 {COverDraft_Hex_Cent,   0x03},               /*当前剩余金额BCD格式、当前透支金额BCD格式*/
	 {CProgTPara_Note_1,     0x03},               /*费率参数表编程记录*/
	 {CProgLad_Note_1,       0x03},               /*阶梯表编程记录*/
	 {CAbnorC_Note_1,        0x03},               /*异常插卡记录*/ 
	 {CLawlessC_Degree,      0x03},               /*非法插卡总次数*/
	 {CBuyCurr_T_1,          0x02},               /*购电记录*/ 
	 {CReturn_M_Note_1,      0x02},               /*退费记录*/
	 {CChange_Rate,          0x04},               /*两套费率电价切换时间*/
	 {CChange_Ladder,        0x04},               /*两套阶梯电价切换时间*/ 
	 {CStep_Num,             0x04},               /*阶梯数*/
	 {CAlam1_Money,          0x03},               /*报警金额1限值...退费金额*/
	 {CInset_Card_State,     0x04},               /*插卡状态字*/
	 {CCurrent_Rate1_Price,  0x03},               /*当前费率电价*/
	 {CBackUp_Rate1_Price,   0x03},               /*备用套费率电价*/
	 {CCurrent_Ladder_Table, 0x03},               /*当前套阶梯表*/
	 {CBackUp_Ladder_Table,  0x03},               /*备用套阶梯表*/
	 {CCurr_Ladder_Price,    0x04},               /*当前阶梯电价*/
	 {CCurr_Price,           0x04},               /*当前电价*/
	 {CCurr_Rate_Price,      0x04},               /*当前费率电价*/
	 
};
#define GV_LocalMeterDI_Len (sizeof(GV_Str_LocalMeterDI)/sizeof(Str_LocalMeterDI)) 
    
typedef  struct
{
   ulong32 CodeID;	                 /*显示标识码*/
   ulong32 Related_CodeID;	         /*关联OAD标识码*/
   ulong32 P_ChieseTableNo;	         /*显示表格号，辅助汉字表格,不同类型数据,为一个结构体数组,*/
                                     /*该处为某一类结构体地址,数据类型定义为结构体数组地址*/
   ushort16 SV_usDisplayTimer;       /*每屏切换时间,切换时间，减到零后，再采用数据层更新最新显示时间。*/
   ushort16 ChieseTableLineNo;	     /*表格内行号,该类结构体,该标识码显示屏对应该类辅助汉字表格结构体,具体的行号.*/
   ushort16 SV_DisplayDataOff;       /*该标识码分屏显示时，显示序号对应显示数据在该标识码中对应数据的数据偏移，第0偏移都为0，第1屏数据偏移为第1屏的数据长度*/
   uchar8  SV_ucDisplayMode;	     /*显示模式：全显、液晶查看、按键显示、自动轮显*/
   uchar8  Screen;	                 /*显示标识码中对应的屏数,当前显示第几屏,即循显、键显第几屏*/
   uchar8  ParaNum;	                 /*数据标示中序号,显示参数中的序号,该标识码对应第几屏 */
   uchar8  ParityTimer;              /*奇偶性定时器*/
}Str_DisplayFlag;		             /*显示标志*/

Str_DisplayFlag GV_Str_DisplayFlag;

#define C_NoOffset          0xFF    /*该标识码对应的数据偏移地址,对于分屏数据,当显示序号对应高低部分,与数据层数据*/
                                    /*相反时(数据层数据存储低字节在前),需列该偏移,如日期时间\表号\通信地址等。*/
                                    /*不需要特殊处理的数据,由程序计算，该字节为FF。*/                                    
                                    
#define C_ChineseSignLen    9
const uchar8 GV_ChineseSignEn[][C_ChineseSignLen]=     /*电能  全列*/
{	
	{0x00,   0xE0,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功总电能	*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率1		*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率2		*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率3		*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率4		*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率5		*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率6 	*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率7 	*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率8 	*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率9 	*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率10	*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率11	*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率12	*/

	{0x00,   0xE0,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功总精确电能        */
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率1精确电能		*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率2精确电能		*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率3精确电能		*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率4精确电能		*/	
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率5精确电能		*/	
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率6精确电能		*/	
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率7精确电能		*/	
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率8精确电能		*/	
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率9精确电能		*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率10精确电能	*/	
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率11精确电能	*/	
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率12精确电能	*/	

	{0x00,   0xE0,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功总脉冲尾数        */
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率1脉冲尾数		*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率2脉冲尾数		*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率3脉冲尾数		*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率4脉冲尾数		*/	
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率5脉冲尾数		*/	
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率6脉冲尾数		*/	
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率7脉冲尾数		*/	
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率8脉冲尾数		*/	
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率9脉冲尾数		*/
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率10脉冲尾数	*/	
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率11脉冲尾数	*/	
	{0x00,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合有功费率12脉冲尾数	*/	

	
	{0x06,   0xE0,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*正向有功总电能	*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*正向有功费率1		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*正向有功费率2		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*正向有功费率3		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*正向有功费率4		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*正向有功费率5		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*正向有功费率6   	*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*正向有功费率7   	*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*正向有功费率8   	*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*正向有功费率9   	*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*正向有功费率10  	*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*正向有功费率11  	*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*正向有功费率12  	*/

	{0x06,   0xE0,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*正向有功总精确电能*///
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*正向有功费率1精确电能		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*正向有功费率2精确电能		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*正向有功费率3精确电能		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*正向有功费率4精确电能		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*正向有功费率5精确电能		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*正向有功费率6精确电能		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*正向有功费率7精确电能		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*正向有功费率8精确电能		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*正向有功费率9精确电能		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*正向有功费率10精确电能	*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*正向有功费率11精确电能	*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*正向有功费率12精确电能	*/

	{0x06,   0xE0,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*正向有功总脉冲尾数		*/  
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*正向有功费率1脉冲尾数		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*正向有功费率2脉冲尾数		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*正向有功费率3脉冲尾数		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*正向有功费率4脉冲尾数		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*正向有功费率5脉冲尾数		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*正向有功费率6脉冲尾数		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*正向有功费率7脉冲尾数		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*正向有功费率8脉冲尾数		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*正向有功费率9脉冲尾数		*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*正向有功费率10脉冲尾数  	*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*正向有功费率11脉冲尾数  	*/
	{0x06,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*正向有功费率12脉冲尾数  	*/


	{0x06,   0xC0,  0x80,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*A正向有功电能	*/
	{0x06,   0xC0,  0x80,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*A正向有功电能 精确电能*/
	{0x06,   0xC0,  0x80,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*A正向有功电能 脉冲尾数*/
		
	{0x06,   0xC0,  0x40,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*B正向有功电能	*/
	{0x06,   0xC0,  0x40,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*B正向有功电能 精确电能*/	
	{0x06,   0xC0,  0x40,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*B正向有功电能 脉冲尾数*/	
	
	
	{0x06,   0xC0,  0x20,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*C正向有功电能*/
	{0x06,   0xC0,  0x20,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*C正向有功电能 精确电能*/	
	{0x06,   0xC0,  0x20,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*C正向有功电能 脉冲尾数*/	
	
	{0x0A,   0xE0,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*反向有功总电能	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*反向有功费率1		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*反向有功费率2		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*反向有功费率3		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*反向有功费率4		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*反向有功费率5		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*反向有功费率6   	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*反向有功费率7   	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*反向有功费率8   	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*反向有功费率9   	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*反向有功费率10  	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*反向有功费率11  	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*反向有功费率12  	*/

	{0x0A,   0xE0,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*反向有功总精确电能		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*反向有功费率1精确电能		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*反向有功费率2精确电能		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*反向有功费率3精确电能		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*反向有功费率4精确电能		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*反向有功费率5精确电能		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*反向有功费率6精确电能   	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*反向有功费率7精确电能   	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*反向有功费率8精确电能   	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*反向有功费率9精确电能   	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*反向有功费率10精确电能  	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*反向有功费率11精确电能  	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*反向有功费率12精确电能  	*/

	{0x0A,   0xE0,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*反向有功总脉冲尾数		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*反向有功费率1脉冲尾数		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*反向有功费率2脉冲尾数		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*反向有功费率3脉冲尾数		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*反向有功费率4脉冲尾数		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*反向有功费率5脉冲尾数		*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*反向有功费率6脉冲尾数   	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*反向有功费率7脉冲尾数   	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*反向有功费率8脉冲尾数   	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*反向有功费率9脉冲尾数   	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*反向有功费率10脉冲尾数  	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*反向有功费率11脉冲尾数  	*/
	{0x0A,   0xD8,  0x00,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*反向有功费率12脉冲尾数  	*/

	{0x0A,   0xC0,  0x80,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*A反向有功电能	*/
	{0x0A,   0xC0,  0x80,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*A反向有功电能 精确电能*/	
	{0x0A,   0xC0,  0x80,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*A反向有功电能 脉冲尾数*/	
	
	{0x0A,   0xC0,  0x40,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*B反向有功电能	*/
	{0x0A,   0xC0,  0x40,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*B反向有功电能 精确电能*/	
	{0x0A,   0xC0,  0x40,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*B反向有功电能 脉冲尾数*/	
	
	{0x0A,   0xC0,  0x20,  0x60,  0x00,  C_DiskWhNum,      0x00,                 0x05,    C_NoOffset},	/*C反向有功电能	*/	
	{0x0A,   0xC0,  0x20,  0x60,  0x00,  C_DiskWhNum,      0x04,                 0x05,    C_NoOffset},	/*C反向有功电能 精确电能*/	
	{0x0A,   0xC0,  0x20,  0x60,  0x00,  C_DiskWhNum,      0x06,                 0x05,    C_NoOffset},	/*C反向有功电能 脉冲尾数*/	
	
    
	{0x11,   0x60,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1总电能		*/
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率1		*/
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率2		*/
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率3		*/
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率4		*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率5		*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率6  		*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率7  		*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率8  		*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率9  		*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率10 		*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率11 		*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率12 		*/ 

	{0x11,   0x60,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1总精确电能		*/
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率1精确电能	*/
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率2精确电能	*/
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率3精确电能	*/
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率4精确电能	*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率5精确电能	*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率6精确电能  	*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率7精确电能  	*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率8精确电能  	*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率9精确电能  	*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率10精确电能	*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率11精确电能	*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率12精确电能	*/ 

	{0x11,   0x60,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1总脉冲尾数		*/
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率1脉冲尾数	*/
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率2脉冲尾数	*/
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率3脉冲尾数	*/
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率4脉冲尾数	*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率5脉冲尾数	*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率6脉冲尾数  	*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率7脉冲尾数  	*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率8脉冲尾数  	*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率9脉冲尾数  	*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率10脉冲尾数	*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率11脉冲尾数	*/ 
	{0x11,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功1费率12脉冲尾数	*/ 

	{0x11,   0x40,  0x80,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*A组合无功1电能	  */
	{0x11,   0x40,  0x80,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*A组合无功1电能 精确电能*/
	{0x11,   0x40,  0x80,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*A组合无功1电能 脉冲尾数*/
	
	{0x11,   0x40,  0x40,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*B组合无功1电能	  */	
	{0x11,   0x40,  0x40,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*B组合无功1电能 精确电能*/ 
	{0x11,   0x40,  0x40,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*B组合无功1电能 脉冲尾数*/ 
	
	{0x11,   0x40,  0x20,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*C组合无功1电能	  */	
	{0x11,   0x40,  0x20,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*C组合无功1电能 精确电能*/
	{0x11,   0x40,  0x20,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*C组合无功1电能 脉冲尾数*/
	
	
	{0x11,   0x60,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2总电能		*/
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率1		*/
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率2		*/
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率3		*/
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率4		*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率5		*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率6  	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率7  	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率8  	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率9  	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率10 	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率11 	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率12 	*/  

	{0x11,   0x60,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2总精确电能		*/
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率1	精确电能	*/
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率2	精确电能	*/
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率3	精确电能	*/
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率4	精确电能	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率5	精确电能	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率6  精确电能	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率7  精确电能	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率8  精确电能	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率9  精确电能	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率10 精确电能	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率11 精确电能	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率12 精确电能	*/  

	{0x11,   0x60,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2总脉冲尾数		*/
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率1	脉冲尾数	*/
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率2	脉冲尾数	*/
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率3	脉冲尾数	*/
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率4	脉冲尾数	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率5	脉冲尾数	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率6  脉冲尾数	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率7  脉冲尾数	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率8  脉冲尾数	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率9  脉冲尾数	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率10 脉冲尾数	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率11 脉冲尾数	*/  
	{0x11,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*组合无功2费率12 脉冲尾数	*/  
	
	{0x11,   0x40,  0x80,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*A组合无功2电能	  */
	{0x11,   0x40,  0x80,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*A反向有功电能 精确电能*/ 
	{0x11,   0x40,  0x80,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*A反向有功电能 脉冲尾数*/ 
	
	{0x11,   0x40,  0x40,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*B组合无功2电能	  */	
	{0x11,   0x40,  0x40,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*B反向有功电能 精确电能*/	
	{0x11,   0x40,  0x40,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*B反向有功电能 脉冲尾数*/	
	
	{0x11,   0x40,  0x20,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*C组合无功2电能	  */	
	{0x11,   0x40,  0x20,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*C反向有功电能 精确电能*/
	{0x11,   0x40,  0x20,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*C反向有功电能 脉冲尾数*/
	
	{0x01,   0x60,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*一象限无功总电能	*/
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*一象限无功费率1		*/
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*一象限无功费率2		*/
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*一象限无功费率3		*/
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*一象限无功费率4		*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*一象限无功费率5	 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*一象限无功费率6  	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*一象限无功费率7  	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*一象限无功费率8  	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*一象限无功费率9  	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*一象限无功费率10 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*一象限无功费率11 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*一象限无功费率12 	*/   

	{0x01,   0x60,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*一象限无功总精确电能	*/
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*一象限无功费率1	精确电能	*/
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*一象限无功费率2	精确电能	*/
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*一象限无功费率3	精确电能	*/
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*一象限无功费率4	精确电能	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*一象限无功费率5	精确电能 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*一象限无功费率6 精确电能 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*一象限无功费率7 精确电能 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*一象限无功费率8 精确电能 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*一象限无功费率9 精确电能 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*一象限无功费率10精确电能 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*一象限无功费率11精确电能 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*一象限无功费率12精确电能 	*/   

	{0x01,   0x60,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*一象限无功总脉冲尾数	*/
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*一象限无功费率1	脉冲尾数	*/
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*一象限无功费率2	脉冲尾数	*/
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*一象限无功费率3	脉冲尾数	*/
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*一象限无功费率4	脉冲尾数	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*一象限无功费率5	脉冲尾数 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*一象限无功费率6 脉冲尾数 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*一象限无功费率7 脉冲尾数 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*一象限无功费率8 脉冲尾数 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*一象限无功费率9 脉冲尾数 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*一象限无功费率10脉冲尾数 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*一象限无功费率11脉冲尾数 	*/   
	{0x01,   0x58,  0x00,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*一象限无功费率12脉冲尾数 	*/   
	
	{0x01,   0x40,  0x80,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*A一象限无功电能	  */	
	{0x01,   0x40,  0x80,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*A一象限无功电能	 精确电能*/
	{0x01,   0x40,  0x80,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*A一象限无功电能	 脉冲尾数*/
	
	{0x01,   0x40,  0x40,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*B一象限无功电能	  */
	{0x01,   0x40,  0x40,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*B一象限无功电能	 精确电能*/
	{0x01,   0x40,  0x40,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*B一象限无功电能	 脉冲尾数*/

	{0x01,   0x40,  0x20,  0x60,  0x08,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*C一象限无功电能	  */
	{0x01,   0x40,  0x20,  0x60,  0x08,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*C一象限无功电能	 精确电能*/
	{0x01,   0x40,  0x20,  0x60,  0x08,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*C一象限无功电能	 脉冲尾数*/
	

	{0x01,   0x60,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*二象限无功总电能	*/
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*二象限无功费率1		*/
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*二象限无功费率2		*/
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*二象限无功费率3		*/
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*二象限无功费率4		*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*二象限无功费率5	 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*二象限无功费率6  	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*二象限无功费率7  	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*二象限无功费率8  	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*二象限无功费率9  	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*二象限无功费率10 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*二象限无功费率11 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*二象限无功费率12 	*/ 

	{0x01,   0x60,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*二象限无功总精确电能	*/
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*二象限无功费率1	精确电能	*/
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*二象限无功费率2	精确电能	*/
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*二象限无功费率3	精确电能	*/
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*二象限无功费率4	精确电能	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*二象限无功费率5	精确电能 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*二象限无功费率6 精确电能 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*二象限无功费率7 精确电能 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*二象限无功费率8 精确电能 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*二象限无功费率9 精确电能 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*二象限无功费率10精确电能 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*二象限无功费率11精确电能 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*二象限无功费率12精确电能 	*/ 

	{0x01,   0x60,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*二象限无功总脉冲尾数	*/
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*二象限无功费率1	脉冲尾数	*/
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*二象限无功费率2	脉冲尾数	*/
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*二象限无功费率3	脉冲尾数	*/
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*二象限无功费率4	脉冲尾数	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*二象限无功费率5	脉冲尾数 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*二象限无功费率6 脉冲尾数 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*二象限无功费率7 脉冲尾数 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*二象限无功费率8 脉冲尾数 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*二象限无功费率9 脉冲尾数 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*二象限无功费率10脉冲尾数 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*二象限无功费率11脉冲尾数 	*/ 
	{0x01,   0x58,  0x00,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*二象限无功费率12脉冲尾数 	*/ 
	
	{0x01,   0x40,  0x80,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*A二象限无功电能	  */
	{0x01,   0x40,  0x80,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*A一象限无功电能	 精确电能*/
	{0x01,   0x40,  0x80,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*A一象限无功电能	 脉冲尾数*/

	
	{0x01,   0x40,  0x40,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*B二象限无功电能	  */
	{0x01,   0x40,  0x40,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*B一象限无功电能	 精确电能*/
	{0x01,   0x40,  0x40,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*B一象限无功电能	 脉冲尾数*/

	{0x01,   0x40,  0x20,  0x60,  0x04,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*C二象限无功电能	  */
	{0x01,   0x40,  0x20,  0x60,  0x04,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*C一象限无功电能	 精确电能*/
	{0x01,   0x40,  0x20,  0x60,  0x04,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*C一象限无功电能	 脉冲尾数*/
	

	{0x01,   0x60,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*三象限无功总电能  */
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*三象限无功费率1		*/  
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*三象限无功费率2		*/  
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*三象限无功费率3		*/  
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*三象限无功费率4		*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*三象限无功费率5	 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*三象限无功费率6  	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*三象限无功费率7  	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*三象限无功费率8  	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*三象限无功费率9  	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*三象限无功费率10 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*三象限无功费率11 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*三象限无功费率12 	*/

	{0x01,   0x60,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*三象限无功总精确电能  */
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*三象限无功费率1	精确电能	*/  
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*三象限无功费率2	精确电能	*/  
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*三象限无功费率3	精确电能	*/  
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*三象限无功费率4	精确电能	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*三象限无功费率5	精确电能 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*三象限无功费率6 精确电能 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*三象限无功费率7 精确电能 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*三象限无功费率8 精确电能 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*三象限无功费率9 精确电能 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*三象限无功费率10精确电能 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*三象限无功费率11精确电能 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*三象限无功费率12精确电能 	*/

	{0x01,   0x60,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*三象限无功总脉冲尾数  */
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*三象限无功费率1	脉冲尾数	*/  
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*三象限无功费率2	脉冲尾数	*/  
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*三象限无功费率3	脉冲尾数	*/  
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*三象限无功费率4	脉冲尾数	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*三象限无功费率5	脉冲尾数 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*三象限无功费率6 脉冲尾数 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*三象限无功费率7 脉冲尾数 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*三象限无功费率8 脉冲尾数 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*三象限无功费率9 脉冲尾数 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*三象限无功费率10脉冲尾数 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*三象限无功费率11脉冲尾数 	*/
	{0x01,   0x58,  0x00,  0x60,  0x0C,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*三象限无功费率12脉冲尾数 	*/
	
	{0x01,   0x40,  0x80,  0x60,  0x0C,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*A三象限无功电能	  */
	{0x01,   0x40,  0x80,  0x60,  0x0C,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*A一象限无功电能	 精确电能*/
	{0x01,   0x40,  0x80,  0x60,  0x0C,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*A一象限无功电能	 脉冲尾数*/
	
	{0x01,   0x40,  0x40,  0x60,  0x0C,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*B三象限无功电能	  */
	{0x01,   0x40,  0x40,  0x60,  0x0C,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*B一象限无功电能	 精确电能*/
	{0x01,   0x40,  0x40,  0x60,  0x0C,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*B一象限无功电能	 脉冲尾数*/
	
	{0x01,   0x40,  0x20,  0x60,  0x0C,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*C三象限无功电能	  */	
	{0x01,   0x40,  0x20,  0x60,  0x0C,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*C一象限无功电能	 精确电能*/
	{0x01,   0x40,  0x20,  0x60,  0x0C,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*C一象限无功电能	 脉冲尾数*/

	{0x01,   0x60,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*四象限无功总电能  */
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*四象限无功费率1		*/  
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*四象限无功费率2		*/  
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*四象限无功费率3		*/  
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*四象限无功费率4		*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*四象限无功费率5	 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*四象限无功费率6  	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*四象限无功费率7  	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*四象限无功费率8  	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*四象限无功费率9  	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*四象限无功费率10 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*四象限无功费率11 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*四象限无功费率12 	*/

	{0x01,   0x60,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*四象限无功总精确电能  */
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*四象限无功费率1	精确电能	*/  
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*四象限无功费率2	精确电能	*/  
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*四象限无功费率3	精确电能	*/  
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*四象限无功费率4	精确电能	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*四象限无功费率5	精确电能 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*四象限无功费率6 精确电能 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*四象限无功费率7 精确电能 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*四象限无功费率8 精确电能 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*四象限无功费率9 精确电能 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*四象限无功费率10精确电能 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*四象限无功费率11精确电能 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*四象限无功费率12精确电能 	*/

	{0x01,   0x60,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*四象限无功总脉冲尾数  */
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*四象限无功费率1	脉冲尾数*/  
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*四象限无功费率2	脉冲尾数	*/  
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*四象限无功费率3	脉冲尾数	*/  
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*四象限无功费率4	脉冲尾数	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*四象限无功费率5	脉冲尾数 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*四象限无功费率6 脉冲尾数 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*四象限无功费率7 脉冲尾数 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*四象限无功费率8 脉冲尾数 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*四象限无功费率9 脉冲尾数 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*四象限无功费率10脉冲尾数 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*四象限无功费率11脉冲尾数 	*/
	{0x01,   0x58,  0x00,  0x60,  0x09,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*四象限无功费率12脉冲尾数 	*/
	                                                                                                                                 
	{0x01,   0x40,  0x80,  0x60,  0x09,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*A四象限无功电能	  */	
	{0x01,   0x40,  0x80,  0x60,  0x09,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*A一象限无功电能	 精确电能*/
	{0x01,   0x40,  0x80,  0x60,  0x09,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*A一象限无功电能	 脉冲尾数*/
	
	{0x01,   0x40,  0x40,  0x60,  0x09,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*B四象限无功电能	  */	
	{0x01,   0x40,  0x40,  0x60,  0x09,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*B一象限无功电能	 精确电能*/
	{0x01,   0x40,  0x40,  0x60,  0x09,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*B一象限无功电能	 脉冲尾数*/
	
	{0x01,   0x40,  0x20,  0x60,  0x09,  C_DiskvarhNum,    0x00,                 0x05,    C_NoOffset},	/*C四象限无功电能	  */	
	{0x01,   0x40,  0x20,  0x60,  0x09,  C_DiskvarhNum,    0x04,                 0x05,    C_NoOffset},	/*C一象限无功电能	 精确电能*/
	{0x01,   0x40,  0x20,  0x60,  0x09,  C_DiskvarhNum,    0x06,                 0x05,    C_NoOffset},	/*C一象限无功电能	 脉冲尾数*/
};
#define GV_ChineseSignEn_Len (sizeof(GV_ChineseSignEn)/C_ChineseSignLen) 

const uchar8 GV_ChineseSignDe[][C_ChineseSignLen]=     /*需量  全列*/
{	
	{0x06,   0xE0,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*正向有功总    */
	{0x06,   0xE0,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          */
	{0x06,   0xE0,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          */
	{0x06,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*正向有功费率1	*/
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          */
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          */
	{0x06,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*正向有功费率2	*/
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          */
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          */
	{0x06,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*正向有功费率3	*/
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          */
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          */
	{0x06,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*正向有功费率4	*/ 
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          */
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          */
	{0x06,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*正向有功费率5	*/ 
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          */
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          */
	{0x06,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*正向有功费率6	*/ 
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          */
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          */
	{0x06,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*正向有功费率7	*/ 
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          */
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          */
	{0x06,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*正向有功费率8	*/ 
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          */
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          */
	{0x06,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*正向有功费率9	*/ 
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          */
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          */
	{0x06,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*正向有功费率10*/ 
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          */
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          */
	{0x06,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*正向有功费率11*/ 
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          */
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          */
	{0x06,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*正向有功费率12*/ 	
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          */
	{0x06,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          */
	
	{0x0A,   0xE0,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*反向有功总    */
	{0x0A,   0xE0,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          */
	{0x0A,   0xE0,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*反向有功费率1	*/
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*反向有功费率2	*/
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*反向有功费率3	*/
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*反向有功费率4	*/
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*反向有功费率5	*/
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*反向有功费率6	*/
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*反向有功费率7	*/
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*反向有功费率8	*/
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*反向有功费率9	*/
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*反向有功费率10*/
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*反向有功费率11*/
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*反向有功费率12*/
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          */
	{0x0A,   0xD8,  0x00,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          */
	
	{0x11,   0x60,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*组合无功1总   */    
	{0x11,   0x60,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x11,   0x60,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*组合无功1费率1*/
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*组合无功1费率2*/
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*组合无功1费率3*/
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*组合无功1费率4*/	
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*组合无功1费率5*/	
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*组合无功1费率6*/	
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*组合无功1费率7*/	
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*组合无功1费率8*/	
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*组合无功1费率9*/	
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*组合无功1费率10*/	
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*组合无功1费率11*/	
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*组合无功1费率12*/	
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	
	{0x11,   0x60,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*组合无功2总	*/
	{0x11,   0x60,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x11,   0x60,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*组合无功2费率1*/
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*组合无功2费率2*/
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*组合无功2费率3*/
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*组合无功2费率4*/     	
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*组合无功2费率5*/     	
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*组合无功2费率6*/     	
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*组合无功2费率7*/     	
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*组合无功2费率8*/     	
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*组合无功2费率9*/     	
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*组合无功2费率10*/     	
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*组合无功2费率11*/     	
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/            
	{0x11,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*组合无功2费率12*/     	
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x11,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	
	{0x01,   0x60,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*一象限无功总	        */
	{0x01,   0x60,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x60,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*一象限无功费率1		*/
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*一象限无功费率2		*/
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*一象限无功费率3		*/
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*一象限无功费率4		*/	
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*一象限无功费率5		*/	
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*一象限无功费率6		*/	
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*一象限无功费率7		*/	
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*一象限无功费率8		*/	
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*一象限无功费率9		*/	
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*一象限无功费率10		*/	
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*一象限无功费率11		*/	
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*一象限无功费率12		*/	
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	
	{0x01,   0x60,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*二象限无功总	        */
	{0x01,   0x60,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x60,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*二象限无功费率1		*/
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*二象限无功费率2		*/
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*二象限无功费率3		*/
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*二象限无功费率4		*/ 	
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*二象限无功费率5		*/ 	
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*二象限无功费率6		*/ 	
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*二象限无功费率7		*/ 	
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*二象限无功费率8		*/ 	
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*二象限无功费率9		*/ 	
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*二象限无功费率10	    */ 	
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*二象限无功费率11	    */ 	
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*二象限无功费率12	    */ 	
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	
	{0x01,   0x60,  0x00,  0xA0,  0x0C,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*三象限无功总          */
	{0x01,   0x60,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x60,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x0C,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*三象限无功费率1		*/  
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x0C,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*三象限无功费率2		*/  
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x0C,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*三象限无功费率3		*/  
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x0C,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*三象限无功费率4		*/  	                                                                                               
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x0C,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*三象限无功费率5		*/  	                                                                                               
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x0C,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*三象限无功费率6		*/  	                                                                                               
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x0C,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*三象限无功费率7		*/  	                                                                                               
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x0C,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*三象限无功费率8		*/  	                                                                                               
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x0C,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*三象限无功费率9		*/  	                                                                                               
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x0C,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*三象限无功费率10	    */  	                                                                                               
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x0C,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*三象限无功费率11	    */  	                                                                                               
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x0C,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*三象限无功费率12	    */  	                                                                                               
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x6C,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	
	{0x01,   0x60,  0x00,  0xA0,  0x09,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*四象限无功总电能      */
	{0x01,   0x60,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x60,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x09,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*四象限无功费率1		*/  
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x09,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*四象限无功费率2		*/  
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x09,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*四象限无功费率3		*/  
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x09,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*四象限无功费率4		*/   	
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x09,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*四象限无功费率5		*/   	
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x09,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*四象限无功费率6		*/   	
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x09,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*四象限无功费率7		*/   	
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x09,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*四象限无功费率8		*/   	
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x09,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*四象限无功费率9		*/   	
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x09,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*四象限无功费率10	    */   	
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x09,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*四象限无功费率11	    */   	
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间            	    */
	{0x01,   0x58,  0x00,  0xA0,  0x09,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*四象限无功费率12	    */   	
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x58,  0x00,  0xA0,  0x69,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	
	{0x06,   0xC0,  0x80,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*A正向有功		        */	
	{0x06,   0xC0,  0x80,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x06,   0xC0,  0x80,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x0A,   0xC0,  0x80,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*A反向有功		        */	
	{0x0A,   0xC0,  0x80,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x0A,   0xC0,  0x80,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x11,   0x40,  0x80,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*A组合无功1	*/	
	{0x11,   0x40,  0x80,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x11,   0x40,  0x80,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x11,   0x40,  0x80,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*A组合无功2	*/	
	{0x11,   0x40,  0x80,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x11,   0x40,  0x80,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x01,   0x40,  0x80,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*A一象限无功	        */	
	{0x01,   0x40,  0x80,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x40,  0x80,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x01,   0x40,  0x80,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*A二象限无功	        */	
	{0x01,   0x40,  0x80,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x40,  0x80,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x01,   0x40,  0x80,  0xA0,  0x0C,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*A三象限无功	        */	
	{0x01,   0x40,  0x80,  0xA0,  0x6C,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x40,  0x80,  0xA0,  0x6C,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x01,   0x40,  0x80,  0xA0,  0x09,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*A四象限无功	        */	
	{0x01,   0x40,  0x80,  0xA0,  0x69,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x40,  0x80,  0xA0,  0x69,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x06,   0xC0,  0x40,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*B正向有功		        */	
	{0x06,   0xC0,  0x40,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x06,   0xC0,  0x40,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x0A,   0xC0,  0x40,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*B反向有功		        */	
	{0x0A,   0xC0,  0x40,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x0A,   0xC0,  0x40,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x11,   0x40,  0x40,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*B组合无功1	  */	
	{0x11,   0x40,  0x40,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x11,   0x40,  0x40,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x11,   0x40,  0x40,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*B组合无功2	  */	
	{0x11,   0x40,  0x40,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x11,   0x40,  0x40,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x01,   0x40,  0x40,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*B一象限无功	        */	
	{0x01,   0x40,  0x40,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x40,  0x40,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x01,   0x40,  0x40,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*B二象限无功	        */	
	{0x01,   0x40,  0x40,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x40,  0x40,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x01,   0x40,  0x40,  0xA0,  0x0C,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*B三象限无功	        */	
	{0x01,   0x40,  0x40,  0xA0,  0x6C,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x40,  0x40,  0xA0,  0x6C,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x01,   0x40,  0x40,  0xA0,  0x09,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*B四象限无功	        */	
	{0x01,   0x40,  0x40,  0xA0,  0x69,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x40,  0x40,  0xA0,  0x69,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x06,   0xC0,  0x20,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*C正向有功		        */	
	{0x06,   0xC0,  0x20,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x06,   0xC0,  0x20,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x0A,   0xC0,  0x20,  0xA0,  0x00,  C_DiskWNum,                            0x00,                 0x04,     C_NoOffset},	/*C反向有功		        */	
	{0x0A,   0xC0,  0x20,  0xA0,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x0A,   0xC0,  0x20,  0xA0,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x11,   0x40,  0x20,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*C组合无功1	  */	
	{0x11,   0x40,  0x20,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x11,   0x40,  0x20,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x11,   0x40,  0x20,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 (0x04+C_NeedSignBit0x08),     C_NoOffset},	/*C组合无功2	  */	
	{0x11,   0x40,  0x20,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x11,   0x40,  0x20,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x01,   0x40,  0x20,  0xA0,  0x08,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*C一象限无功	        */	
	{0x01,   0x40,  0x20,  0xA0,  0x68,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x40,  0x20,  0xA0,  0x68,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x01,   0x40,  0x20,  0xA0,  0x04,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*C二象限无功           */	
	{0x01,   0x40,  0x20,  0xA0,  0x64,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x40,  0x20,  0xA0,  0x64,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x01,   0x40,  0x20,  0xA0,  0x0C,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*C三象限无功	        */	
	{0x01,   0x40,  0x20,  0xA0,  0x6C,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x40,  0x20,  0xA0,  0x6C,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
	{0x01,   0x40,  0x20,  0xA0,  0x09,  C_DiskvarNum,                          0x00,                 0x04,     C_NoOffset},	/*C四象限无功           */	
	{0x01,   0x40,  0x20,  0xA0,  0x69,  C_DisNo+C_NeedDataChange,              C_5P7PDot,            0xA4,     0x07      },	/*日期          		*/
	{0x01,   0x40,  0x20,  0xA0,  0x69,  C_DisNo+C_NeedSingleByteChange,        C_CoL27PDot,          0xC2,     0x05      },	/*时间          		*/
};
#define GV_ChineseSignDe_Len (sizeof(GV_ChineseSignDe)/C_ChineseSignLen) 

const uchar8 GV_ChineseSignFr[][C_ChineseSignLen]=     /*冻结 全列*/
{	
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo+C_NeedDataChange,          C_5P7PDot,            0xA4,    0x02      },	/*日期 */
};                                                                                 
#define GV_ChineseSignFr_Len (sizeof(GV_ChineseSignFr)/C_ChineseSignLen)           


const uchar8 GV_ChineseSignPort[][C_ChineseSignLen]=     /*输入输出接口*/
{	
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo+C_NoNeedChange,          0x00,                 0x23,     0},	/*第1路485*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo+C_NoNeedChange,          0x00,                 0x23,     0},	/*第1路485*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo+C_NoNeedChange,          0x00,                 0x23,     0},	/*第2路485*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo+C_NoNeedChange,          0x00,                 0x23,     0},	/*第2路485*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo+C_NoNeedChange,          0x00,                 0x23,     0},	/*载波*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo+C_NoNeedChange,          0x00,                 0x23,     0},	/*载波*/

};
#define GV_ChineseSignPort_Len (sizeof(GV_ChineseSignPort)/C_ChineseSignLen)           

const uchar8 GV_ChineseSignEv30[][C_ChineseSignLen]=     /*事件记录10  */
{	
/*失压事件*/
	{0x00,   0x00,  0x00,  0x42,  0x00,  C_DisVNum,        0x01,                 0x42,     C_NoOffset},	/*失压事件电压触发上限*/
	{0x00,   0x00,  0x00,  0x42,  0x00,  C_DisVNum,        0x01,                 0x42,     C_NoOffset},	/*失压事件电压恢复下限*/
	{0x00,   0x00,  0x00,  0x41,  0x00,  C_DisANum,        0x04,                 0x24,     C_NoOffset},	/*失压事件电流触发上限*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*失压事件判断延时时间*/
	{0x00,   0x20,  0x00,  0x06,  0x00,  C_DisNo,          0,                    0x04,     C_NoOffset},	/*总失压总次数*/
	{0x00,   0x20,  0x00,  0x06,  0x60,  C_DisNo,          0,                    0x04,     0x04},	    /*总失压总累计时间	*/
	{0x00,   0x20,  0x80,  0x06,  0x00,  C_DisNo,          0,                    0x04,     C_NoOffset},	/*A失压总次数*/
	{0x00,   0x20,  0x80,  0x06,  0x60,  C_DisNo,          0,                    0x04,     0x04},	    /*A失压总累计时间	*/
	{0x00,   0x20,  0x40,  0x06,  0x00,  C_DisNo,          0,                    0x04,     C_NoOffset},	/*B失压总次数*/
	{0x00,   0x20,  0x40,  0x06,  0x60,  C_DisNo,          0,                    0x04,     0x04},	    /*B失压总累计时间	*/
	{0x00,   0x20,  0x20,  0x06,  0x00,  C_DisNo,          0,                    0x04,     C_NoOffset},	/*C失压总次数*/
	{0x00,   0x20,  0x20,  0x06,  0x60,  C_DisNo,          0,                    0x04,     0x04},	    /*C失压总累计时间	*/
	{0x00,   0x20,  0x00,  0x06,  0x00,  C_DisNo,          0,                    0x04,     C_NoOffset},	/*失压总次数*/
	{0x00,   0x20,  0x00,  0x06,  0x60,  C_DisNo,          0,                    0x04,     C_NoOffset},	/*失压总累计时间	*/
	{0x40,   0x00,  0x00,  0x06,  0x60,  C_DisNo+C_NeedDataChange,               C_5P7PDot,            0xA4,    0x03      },	/*最近1次失压发生日期*/
	{0x40,   0x00,  0x00,  0x06,  0x60,  C_DisNo+C_NeedSingleByteChange,         C_CoL2CoL15P7PDot,    0xA3,    0x00      },	/*最近1次失压发生时间*/
	{0x40,   0x00,  0x00,  0x06,  0x60,  C_DisNo+C_NeedDataChange,               C_5P7PDot,            0xA4,    0x03      },	/*最近1次失压结束日期*/
	{0x40,   0x00,  0x00,  0x06,  0x60,  C_DisNo+C_NeedSingleByteChange,         C_CoL2CoL15P7PDot,    0xA3,    0x00      },	/*最近1次失压结束时间*/
	{0x40,   0x20,  0x00,  0x06,  0x60,  C_DisNo+C_NeedDataChange,               C_5P7PDot,            0xA4,    0x03      },	/*最近1次失压发生日期*/
	{0x40,   0x20,  0x00,  0x06,  0x60,  C_DisNo+C_NeedSingleByteChange,         C_CoL2CoL15P7PDot,    0xA3,    0         },	/*最近1次失压发生时间*/
	{0x40,   0x20,  0x00,  0x06,  0x60,  C_DisNo+C_NeedDataChange,               C_5P7PDot,            0xA4,    0x0A      },	/*最近1次失压结束日期*/
	{0x40,   0x20,  0x00,  0x06,  0x60,  C_DisNo+C_NeedSingleByteChange,         C_CoL2CoL15P7PDot,    0xA3,    0x07      },	/*最近1次失压结束时间*/
	{0x40,   0x00,  0x80,  0x06,  0x60,  C_DisNo+C_NeedDataChange,               C_5P7PDot,            0xA4,    0x03      },	/*A最近1次失压发生日期*/
	{0x40,   0x00,  0x80,  0x06,  0x60,  C_DisNo+C_NeedSingleByteChange,         C_CoL2CoL15P7PDot,    0xA3,    0         },	/*A最近1次失压发生时间*/
	{0x40,   0x00,  0x80,  0x06,  0x60,  C_DisNo+C_NeedDataChange,               C_5P7PDot,            0xA4,    0x0A      },	/*A最近1次失压结束日期*/
	{0x40,   0x00,  0x80,  0x06,  0x60,  C_DisNo+C_NeedSingleByteChange,         C_CoL2CoL15P7PDot,    0xA3,    0x07      },	/*A最近1次失压结束时间*/
	{0x40,   0x00,  0x40,  0x06,  0x60,  C_DisNo+C_NeedDataChange,               C_5P7PDot,            0xA4,    0x03      },	/*B最近1次失压发生日期*/
	{0x40,   0x00,  0x40,  0x06,  0x60,  C_DisNo+C_NeedSingleByteChange,         C_CoL2CoL15P7PDot,    0xA3,    0         },	/*B最近1次失压发生时间*/
	{0x40,   0x00,  0x40,  0x06,  0x60,  C_DisNo+C_NeedDataChange,               C_5P7PDot,            0xA4,    0x0A      },	/*B最近1次失压结束日期*/
	{0x40,   0x00,  0x40,  0x06,  0x60,  C_DisNo+C_NeedSingleByteChange,         C_CoL2CoL15P7PDot,    0xA3,    0x07      },	/*B最近1次失压结束时间*/
	{0x40,   0x00,  0x20,  0x06,  0x60,  C_DisNo+C_NeedDataChange,               C_5P7PDot,            0xA4,    0x03      },	/*C最近1次失压发生日期*/
	{0x40,   0x00,  0x20,  0x06,  0x60,  C_DisNo+C_NeedSingleByteChange,         C_CoL2CoL15P7PDot,    0xA3,    0         },	/*C最近1次失压发生时间*/
	{0x40,   0x00,  0x20,  0x06,  0x60,  C_DisNo+C_NeedDataChange,               C_5P7PDot,            0xA4,    0x0A      },	/*C最近1次失压结束日期*/
	{0x40,   0x00,  0x20,  0x06,  0x60,  C_DisNo+C_NeedSingleByteChange,         C_CoL2CoL15P7PDot,    0xA3,    0x07      },	/*C最近1次失压结束时间*/
/*欠压事件*/
	{0x00,   0x00,  0x00,  0x42,  0x00,  C_DisVNum,        0x01,                 0x42,     C_NoOffset},	/*欠压事件电压触发上限*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*欠压事件判断延时时间*/
	/*{0x00,   0x20,  0x00,  0x06,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},*/	/*总失压总次数*/
	/*{0x00,   0x20,  0x00,  0x06,  0x60,  C_DisNo,          0,                    0x04,    0x04},*/	/*总失压总累计时间	*/
	{0x00,   0x00,  0x80,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*A失压总次数*/
	{0x00,   0x00,  0x80,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*A失压总累计时间	*/
	{0x00,   0x00,  0x40,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*B失压总次数*/
	{0x00,   0x00,  0x40,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*B失压总累计时间	*/
	{0x00,   0x00,  0x20,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*C失压总次数*/
	{0x00,   0x00,  0x20,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*C失压总累计时间	*/
/*过压事件*/
	{0x00,   0x00,  0x00,  0x42,  0x00,  C_DisVNum,        0x01,                 0x42,     C_NoOffset},	/*过压事件电压触发下限*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*过压时间判断延时时间*/
	/*{0x00,   0x20,  0x00,  0x06,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},*/	/*总过压总次数*/
	/*{0x00,   0x20,  0x00,  0x06,  0x60,  C_DisNo,          0,                    0x04,    C_NoOffset},*/	/*总过压总累计时间	*/
	{0x00,   0x00,  0x80,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*A过压总次数*/
	{0x00,   0x00,  0x80,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*A过压总累计时间	*/
	{0x00,   0x00,  0x40,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*B过压总次数*/
	{0x00,   0x00,  0x40,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*B过压总累计时间	*/
	{0x00,   0x00,  0x20,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*C过压总次数*/
	{0x00,   0x00,  0x20,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*C过压总累计时间	*/
/*断相事件*/
	{0x00,   0x00,  0x00,  0x42,  0x00,  C_DisVNum,        0x01,                 0x42,     C_NoOffset},	/*断相事件电压触发上限*/
	{0x00,   0x00,  0x00,  0x41,  0x00,  C_DisANum,        0x04,                 0x24,     C_NoOffset},	/*断相事件电流触发上限*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*断相事件判定延时时间*/
	/*{0x00,   0x20,  0x00,  0x06,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},*/	/*总过压总次数*/
	/*{0x00,   0x20,  0x00,  0x06,  0x60,  C_DisNo,          0,                    0x04,    0x04},*/	/*总过压总累计时间	*/
	{0x00,   0x00,  0x80,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*A过压总次数*/
	{0x00,   0x00,  0x80,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*A过压总累计时间	*/
	{0x00,   0x00,  0x40,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*B过压总次数*/
	{0x00,   0x00,  0x40,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*B过压总累计时间	*/
	{0x00,   0x00,  0x20,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*C过压总次数*/
	{0x00,   0x00,  0x20,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*C过压总累计时间	*/
/*失流事件*/
	{0x00,   0x00,  0x00,  0x42,  0x00,  C_DisVNum,        0x01,                 0x42,     C_NoOffset},	/*失流事件电压触发下限*/
	{0x00,   0x00,  0x00,  0x41,  0x00,  C_DisANum,        0x04,                 0x24,     C_NoOffset},	/*失流事件电流触发上限*/
	{0x00,   0x00,  0x00,  0x41,  0x00,  C_DisANum,        0x04,                 0x24,     C_NoOffset},	/*失流事件电流触发下限*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*失流事件判定延时时间*/
	/*{0x00,   0x20,  0x00,  0x06,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},*/	/*总失流总次数*/
	/*{0x00,   0x20,  0x00,  0x06,  0x60,  C_DisNo,          0,                    0x04,    0x04},*/	/*总失流总累计时间	*/
	{0x00,   0x00,  0x80,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*A失流总次数*/
	{0x00,   0x00,  0x80,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*A失流总累计时间	*/
	{0x00,   0x00,  0x40,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*B失流总次数*/
	{0x00,   0x00,  0x40,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*B失流总累计时间	*/
	{0x00,   0x00,  0x20,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*C失流总次数*/
	{0x00,   0x00,  0x20,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*C失流总累计时间	*/
/*过流事件*/
	{0x00,   0x00,  0x00,  0x41,  0x00,  C_DisANum,        0x04,                 0x44,     C_NoOffset},	/*过流事件电流触发下限*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*过流事件判定延时时间*/
	/*{0x00,   0x20,  0x00,  0x06,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},*/	/*总失流总次数*/
	/*{0x00,   0x20,  0x00,  0x06,  0x60,  C_DisNo,          0,                    0x04,    0x04},*/	/*总失流总累计时间	*/
	{0x00,   0x00,  0x80,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*A失流总次数*/
	{0x00,   0x00,  0x80,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*A失流总累计时间	*/
	{0x00,   0x00,  0x40,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*B失流总次数*/
	{0x00,   0x00,  0x40,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*B失流总累计时间	*/
	{0x00,   0x00,  0x20,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*C失流总次数*/
	{0x00,   0x00,  0x20,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*C失流总累计时间	*/
/*断流事件*/
	{0x00,   0x00,  0x00,  0x42,  0x00,  C_DisVNum,        0x01,                 0x42,     C_NoOffset},	/*断流事件电压触发下限*/
	{0x00,   0x00,  0x00,  0x41,  0x00,  C_DisANum,        0x04,                 0x24,     C_NoOffset},	/*断流事件电流触发下限*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*断流事件判定延时时间*/
	/*{0x00,   0x20,  0x00,  0x06,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},*/	/*总失流总次数*/
	/*{0x00,   0x20,  0x00,  0x06,  0x60,  C_DisNo,          0,                    0x04,    0x04},*/	/*总失流总累计时间	*/
	{0x00,   0x00,  0x80,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*A失流总次数*/
	{0x00,   0x00,  0x80,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*A失流总累计时间	*/
	{0x00,   0x00,  0x40,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*B失流总次数*/
	{0x00,   0x00,  0x40,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*B失流总累计时间	*/
	{0x00,   0x00,  0x20,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*C失流总次数*/
	{0x00,   0x00,  0x20,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*C失流总累计时间	*/
/*功率反向事件*/
	{0x00,   0xC0,  0x00,  0x00,  0x80,  C_DiskWNum,       0x04,                 0x23,     C_NoOffset},	/*功率反向事件有功功率触发下限*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*功率反向事件判定延时时间*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*总累计时间	*/
	{0x00,   0x00,	0x80,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*A总次数*/
	{0x00,   0x00,	0x80,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*A总累计时间	*/
	{0x00,   0x00,	0x40,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*B总次数*/
	{0x00,   0x00,	0x40,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*B总累计时间	*/
	{0x00,   0x00,	0x20,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*C总次数*/
	{0x00,   0x00,	0x20,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*C总累计时间	*/
/*过载事件*/
	{0x00,   0xC0,  0x00,  0x00,  0x80,  C_DisWNum,        0x01,                 0x24,     C_NoOffset},	/*过载事件有功功率触发下限*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*过载事件判定延时时间*/
	/*{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x23,    C_NoOffset},*/	/*总总次数*/
	/*{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},*/	/*总总累计时间	*/
	{0x00,  0x00,  0x80,  0x00,  0x00,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*A总次数*/
	{0x00,  0x00,  0x80,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*A总累计时间	*/
	{0x00,  0x00,  0x40,  0x00,  0x00,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*B总次数*/
	{0x00,  0x00,  0x40,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*B总累计时间	*/
	{0x00,  0x00,  0x20,  0x00,  0x00,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*C总次数*/
	{0x00,  0x00,  0x20,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*C总累计时间	*/
/*正向有功需量超限事件*/
	{0x00,   0xC0,  0x00,  0xA0,  0x00,  C_DiskWNum,       0x04,                 0x24,     C_NoOffset},	/*正向有功需量超限事件需量触发下限*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*需量超限事件判定延时时间*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x01,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*反向有功需量超限事件*/
	{0x00,   0xC0,  0x00,  0xA0,  0x00,  C_DiskWNum,       0x04,                 0x24,     C_NoOffset},	/*反向有功需量超限事件需量触发下限*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*需量超限事件判定延时时间*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x01,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*无功需量超限事件*/
	{0x01,   0x40,  0x00,  0xA0,  0x00,  C_DiskvarNum,     0x04,                 0x24,     C_NoOffset},	/*无功需量超限事件需量触发下限*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*需量超限事件判定延时时间*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*1次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*1累计时间	*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*2次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*2累计时间	*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*3次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*3累计时间	*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    C_NoOffset},	/*4次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x04},	/*4累计时间	*/
/*功率因数超限事件*/
	{0x00,   0x20,  0x0C,  0x00,  0x00,  C_DisNo,          0x01,                 0x42,     C_NoOffset},	/*功率因数超下限阀值*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*功率因素超下限判定延时时间*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*全失压事件*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*辅助电源掉电事件*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*判定延时时间*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*电压逆向序掉电事件*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*判定延时时间*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*电流逆向序掉电事件*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*判定延时时间*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*掉电事件*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*判定延时时间*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*编程事件*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*清零事件*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*需量清零事件*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*事件清零*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*校时事件*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*时段表编程事件*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*时区表编程事件*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*周休日编程事件*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*结算日编程事件*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*开盖事件*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*开端扭盖事件*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*电压不平衡事件*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,          0x02,                 0x42,     C_NoOffset},	/*电压不平衡率限值*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*电压不平衡率判定延时时间*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*电流不平衡事件*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,          0x02,                 0xC2,     C_NoOffset},	/*电流不平衡率限值*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*电流不平衡率判定延时时间*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*跳闸事件*/
	{0x00,   0x20,  0x00, 0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00, 0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00, 0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*合闸事件*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*节假日事件*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*有功组合方式编程事件*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*无功组合方式编程事件*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*费率表编程事件*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*阶梯表编程事件*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*密钥更新事件*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*异常插卡事件*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*购电记录事件*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*退费事件*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*磁场干扰事件*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*判定延时时间*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*负荷开关误动作*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*判定延时时间*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*电源异常事件*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*判定延时时间*/
	{0x00,   0x20,  0x00, 0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00, 0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00, 0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*电流严重不平衡事件*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,          0x02,                 0xC2,     C_NoOffset},	/*电流严重不平衡率限值*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*电流严重不平衡率判定延时时间*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间	*/
/*时钟故障事件*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*判定延时时间*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00,  0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间*/
/*计量芯片故障事件*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,          0x00,                 0xE1,     C_NoOffset},	/*判定延时时间*/
	{0x00,   0x20,  0x00, 0x00,  0x00,  C_DisNo,          0,                    0xE1,    C_NoOffset},	/*事件发生源*/
	{0x00,   0x20,  0x00, 0x00,  0x00,  C_DisNo,          0,                    0x04,    0x01},	/*总总次数*/
	{0x00,   0x20,  0x00, 0x00,  0x60,  C_DisNo,          0,                    0x04,    0x05},	/*总总累计时间*/
};
#define GV_ChineseSignEv30_Len (sizeof(GV_ChineseSignEv30)/C_ChineseSignLen) 
                                                                                 
const uchar8 GV_ChineseSignPa[][C_ChineseSignLen]=     /*参变量*/           
{	                                                                               
	{0x80,   0x00,  0x00,  0x00,  0x60,  (C_DisNo + C_NeedDataChange),          C_5P7PDot,            0xA4,     0x03},	        /*日期YYYYMMDD*/
	{0x80,   0x00,  0x00,  0x00,  0x60,  (C_DisNo + C_NeedSingleByteChange),    C_CoL2CoL15P7PDot,    0xA3,     0x00},	        /*时间*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo+C_NoNeedChange,                0x00,                 0xC2,     0x04},	        /*通讯地址--表号*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo+C_NoNeedChange,                0x00,                 0x84,     0x00},	        /*通讯地址--表号*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo+C_NoNeedChange,                0x00,                 0xC2,     0x04},	        /*表号*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo+C_NoNeedChange,                0x00,                 0x84,     0x00},	        /*表号*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo+C_NoNeedChange,                0x00,                 0xC2,     0x04},	        /*客户编号*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo+C_NoNeedChange,                0x00,                 0x84,     0x00},	        /*客户编号*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0x61,     C_NoOffset},	/*经度(方位)*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0x61,     0x01},	        /*经度(度)*/	
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0x61,     0x02},	        /*经度(分)*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0x61,     0x03},	        /*经度(秒)*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0x61,     C_NoOffset},	/*纬度*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0x61,     0x01},	        /*纬度*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0x61,     0x02},	        /*纬度*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0x61,     0x03},	        /*纬度*/

	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0x04,     C_NoOffset},	/*高度*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},	/*上电全显时间*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},	/*背光点亮时间*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},    /*显示查看背光点亮时间*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},    /*无电按键屏幕驻留最大时间*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},	/*电能小数位数*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},	/*功率小数位数*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},	/*液晶①②字样意义*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  (C_DisNo + C_NeedDataChange),          C_5P7PDot,            0xA4,     0x03      },	/*两套时区表切换时间 YYMMDD*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  (C_DisNo + C_NeedSingleByteChange),    C_CoL2CoL15P7PDot,    0xA3,     0x01      },	/*时间   hhmmss    		*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  (C_DisNo + C_NeedDataChange),          C_5P7PDot,            0xA4,     0x03      },	/*两套日时段表切换时间 YYMMDD*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  (C_DisNo + C_NeedSingleByteChange),    C_CoL2CoL15P7PDot,    0xA3,     0x01      },	/*时间   hhmmss    		*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  (C_DisNo + C_NeedDataChange),          C_5P7PDot,            0xA4,     0x03      },	/*两套费率电价切换时间 YYMMDD*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  (C_DisNo + C_NeedSingleByteChange),    C_CoL2CoL15P7PDot,    0xA3,     0x01      },	/*时间   hhmmss    		*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  (C_DisNo + C_NeedDataChange),          C_5P7PDot,            0xA4,     0x03      },	/*两套阶梯电价切换时间 YYMMDD*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  (C_DisNo + C_NeedSingleByteChange),    C_CoL2CoL15P7PDot,    0xA3,     0x01      },	/*时间   hhmmss    		*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},	/*年时区数*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},	/*日时段表数数*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},	/*日时段数*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},	/*费率数*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xC2,     C_NoOffset},	/*公共假日数*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},	/*阶梯数*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},	/*密钥总条数*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  (C_DisNo+C_NeedDataChange),            C_CoL25P3P7PDot,	  0x84,     C_NoOffset},	/*第1-254公共假日日期及日时段表号  YY.MM.DD:NN*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},	/*周休日特征字*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},	/*周休日采取的日时段表号*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  (C_DisNo+C_NeedSingleByteChange),      C_5P7PDot,            0xA3,     C_NoOffset},	/*第1-14时区起始日期及日时段表号,只列第1屏，同时第2套借用*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  (C_DisNo+C_NeedSingleByteChange),      C_5P7PDot,            0xA3,     C_NoOffset},	/*第2套*/
	{0x00,   0x00,  0x00,  0x00,  0x50,  (C_DisNo+C_NeedSingleByteChange),      C_CoL15P7PDot,        0xA3,     C_NoOffset},	/*第1-14时段起始时间级费率号,只列第1屏，第2-8日借用，同时第2套借用*/
	{0x00,   0x00,  0x00,  0x00,  0x50,  (C_DisNo+C_NeedSingleByteChange),      C_CoL15P7PDot,        0xA3,     C_NoOffset},	/*第2套*/
	{0x80,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*当前费率1电价*/
	{0x80,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*当前费率2电价*/
	{0x80,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*当前费率3电价*/
	{0x80,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*当前费率4电价*/
	{0x80,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*当前费率5电价*/
	{0x80,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*当前费率6电价*/
	{0x80,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*当前费率7电价*/
	{0x80,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*当前费率8电价*/
	{0x80,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*当前费率10电价*/ 
	{0x80,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*当前费率11电价*/ 
	{0x80,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*当前费率12电价*/ 
	{0x80,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*当前费率13电价*/ 
	
	{0x00,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*备用套费率1电价*/
	{0x00,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*备用套费率2电价*/
	{0x00,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*备用套费率3电价*/
	{0x00,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*备用套费率4电价*/  
	{0x00,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*备用套费率5电价*/  
	{0x00,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*备用套费率6电价*/  
	{0x00,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*备用套费率7电价*/  
	{0x00,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*备用套费率8电价*/  
	{0x00,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*备用套费率9电价*/  
	{0x00,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*备用套费率10电价*/  
	{0x00,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*备用套费率11电价*/ 
	{0x00,   0x18,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*备用套费率12电价*/  
                            
	{0x00,   0x00,  0x02,  0x60,  0x00,  C_DiskWhNum,                           0x02,                 0x04,     C_NoOffset},	/*当前套阶梯值1*/
	{0x00,   0x00,  0x02,  0x60,  0x00,  C_DiskWhNum,                           0x02,                 0x04,     C_NoOffset},	/*当前套阶梯值2*/
	{0x00,   0x00,  0x02,  0x60,  0x00,  C_DiskWhNum,                           0x02,                 0x04,     C_NoOffset},	/*当前套阶梯值3*/
	{0x00,   0x00,  0x02,  0x60,  0x00,  C_DiskWhNum,                           0x02,                 0x04,     C_NoOffset},	/*当前套阶梯值4*/
	{0x00,   0x00,  0x02,  0x60,  0x00,  C_DiskWhNum,                           0x02,                 0x04,     C_NoOffset},	/*当前套阶梯值5*/
	{0x00,   0x00,  0x02,  0x60,  0x00,  C_DiskWhNum,                           0x02,                 0x04,     C_NoOffset},	/*当前套阶梯值6*/
	{0x00,   0x00,  0x02,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*当前套阶梯电价1*/
	{0x00,   0x00,  0x02,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*当前套阶梯电价2*/
	{0x00,   0x00,  0x02,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*当前套阶梯电价3*/
	{0x00,   0x00,  0x02,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*当前套阶梯电价4*/
	{0x00,   0x00,  0x02,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*当前套阶梯电价5*/
	{0x00,   0x00,  0x02,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*当前套阶梯电价6*/
	{0x00,   0x00,  0x02,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*当前套阶梯电价7*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  (C_DisNo+C_NeedSingleByteChange),      C_5P7PDot,            0xA3,     C_NoOffset},	/*当前套年1结算日*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  (C_DisNo+C_NeedSingleByteChange),      C_5P7PDot,            0xA3,     C_NoOffset},	/*当前套年2结算日*/	
	{0x00,   0x00,  0x00,  0x00,  0x00,  (C_DisNo+C_NeedSingleByteChange),      C_5P7PDot,            0xA3,     C_NoOffset},	/*当前套年3结算日*/	
	{0x00,   0x00,  0x00,  0x00,  0x00,  (C_DisNo+C_NeedSingleByteChange),      C_5P7PDot,            0xA3,     C_NoOffset},	/*当前套年4结算日*/
	{0x00,   0x00,  0x02,  0x60,  0x00,  C_DiskWhNum,                           0x02,                 0x04,     C_NoOffset},	/*备用套阶梯值1*/
	{0x00,   0x00,  0x02,  0x60,  0x00,  C_DiskWhNum,                           0x02,                 0x04,     C_NoOffset},	/*备用套阶梯值2*/
	{0x00,   0x00,  0x02,  0x60,  0x00,  C_DiskWhNum,                           0x02,                 0x04,     C_NoOffset},	/*备用套阶梯值3*/
	{0x00,   0x00,  0x02,  0x60,  0x00,  C_DiskWhNum,                           0x02,                 0x04,     C_NoOffset},	/*备用套阶梯值4*/
	{0x00,   0x00,  0x02,  0x60,  0x00,  C_DiskWhNum,                           0x02,                 0x04,     C_NoOffset},	/*备用套阶梯值5*/
	{0x00,   0x00,  0x02,  0x60,  0x00,  C_DiskWhNum,                           0x02,                 0x04,     C_NoOffset},	/*备用套阶梯值6*/
	{0x00,   0x00,  0x02,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*备用套阶梯电价1*/
	{0x00,   0x00,  0x02,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*备用套阶梯电价2*/
	{0x00,   0x00,  0x02,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*备用套阶梯电价3*/
	{0x00,   0x00,  0x02,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*备用套阶梯电价4*/
	{0x00,   0x00,  0x02,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*备用套阶梯电价5*/
	{0x00,   0x00,  0x02,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*备用套阶梯电价6*/
	{0x00,   0x00,  0x02,  0x48,  0x00,  C_DisYuanNum,                          0x04,                 0x04,     C_NoOffset},	/*备用套阶梯电价7*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               C_5P7PDot,            0xA3,     C_NoOffset},	/*备用套年1结算日*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               C_5P7PDot,            0xA3,     C_NoOffset},	/*备用套年2结算日*/	
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               C_5P7PDot,            0xA3,     C_NoOffset},	/*备用套年3结算日*/	
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               C_5P7PDot,            0xA3,     C_NoOffset},	/*备用套年4结算日*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x02,                 0xA4,     C_NoOffset},	/*电流互感器变比*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x02,                 0xA4,     C_NoOffset},	/*电压互感器变比*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisYuanNum,                          0x02,                 0x04,     C_NoOffset},	/*报警金额1限值*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisYuanNum,                          0x02,                 0x04,     C_NoOffset},	/*报警金额2限值*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisYuanNum,                          0x02,                 0x04,     C_NoOffset},	/*透支限值*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisYuanNum,                          0x02,                 0x04,     C_NoOffset},	/*囤积金额1限值*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisYuanNum,                          0x02,                 0x04,     C_NoOffset},	/*合闸允许金额限值*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0xC2,     C_NoOffset},	/*插卡状态字*/
	{0x00,   0x00,  0x00,  0x42,  0x00,  C_DisVNum,                             0x01,                 0x42,     C_NoOffset},	/*电压考核上限*/
	{0x00,   0x00,  0x00,  0x42,  0x00,  C_DisVNum,                             0x01,                 0x42,     C_NoOffset},	/*电压考核下限*/
	{0x00,   0x00,  0x00,  0x42,  0x00,  C_DisVNum,                             0x01,                 0x42,     C_NoOffset},	/*电压上限值*/
	{0x00,   0x00,  0x00,  0x42,  0x00,  C_DisVNum,                             0x01,                 0x42,     C_NoOffset},	/*电压下限值*/
};
#define GV_ChineseSignPa_Len ( sizeof(GV_ChineseSignPa) / C_ChineseSignLen ) 


const uchar8 GV_ChineseSignPa_1[][C_ChineseSignLen]=     /*参变量*/            
{	                                                                               
	{0x00,   0x00,  0x00,  0xA0,  0x00,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},	/*最大需量周期*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,                               0x00,                 0xE1,     C_NoOffset},	/*滑差时间  	*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  (C_DisNo+C_NoNeedChange),              0x00,                 0xC2,     C_NoOffset},	/*校表脉冲宽度*/
	{0x00,   0xC0,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0x04,     C_NoOffset},	/*电表有功常数*/
	{0x01,   0x40,  0x00,  0x00,  0x00,  C_DisNo,                               0x00,                 0x04,     C_NoOffset},	/*电表无功常数*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  (C_DisNo+C_NoNeedChange),              0x00,                 0xE1,     C_NoOffset},	/*电表运行特征字1*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  (C_DisNo+C_NoNeedChange),              0x00,                 0xE1,     C_NoOffset},	/*有功组合状态字*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  (C_DisNo+C_NoNeedChange),              0x00,                 0xE1,     C_NoOffset},	/*无功组合1状态字*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  (C_DisNo+C_NoNeedChange),              0x00,                 0xE1,     C_NoOffset},	/*无功组合2状态字*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  (C_DisNo+C_NeedSingleByteChange),      0x02,                 0xC2,     C_NoOffset},	/*结算日1*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  (C_DisNo+C_NeedSingleByteChange),      0x02,                 0xC2,     C_NoOffset},	/*结算日2*/	
	{0x00,   0x00,  0x00,  0x00,  0x00,  (C_DisNo+C_NeedSingleByteChange),      0x02,                 0xC2,     C_NoOffset},	/*结算日3*/
};
#define GV_ChineseSignPa_1_Len (sizeof(GV_ChineseSignPa_1)/C_ChineseSignLen) 


const uchar8 GV_ChineseSignVi[][C_ChineseSignLen]=     /*变量*/
{	
	{0x00,   0x00,  0x80,  0x42,  0x00,  C_DisVNum,                             0x01,                  0x42,    C_NoOffset},	/*A相电压*/
	{0x00,   0x00,  0x40,  0x42,  0x00,  C_DisVNum,                             0x01,                  0x42,    C_NoOffset},	/*B相电压*/
	{0x00,   0x00,  0x20,  0x42,  0x00,  C_DisVNum,                             0x01,                  0x42,    C_NoOffset},	/*C相电压*/
	{0x00,   0x00,  0x80,  0x41,  0x00,  C_DisANum,                             0x03,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*A相电流*/ 
	{0x00,   0x00,  0x40,  0x41,  0x00,  C_DisANum,                             0x03,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*B相电流*/ 
	{0x00,   0x00,  0x20,  0x41,  0x00,  C_DisANum,                             0x03,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*C相电流*/
	{0x00,   0x00,  0x10,  0x41,  0x00,  C_DisANum,                             0x03,                  0x23,    C_NoOffset},	/*零线电流*/	
	{0x00,   0x00,  0x84,  0x00,  0x00,  C_DisNo,                               0x01,                  0x42,    C_NoOffset},	/*A相Ua相角*/
	{0x00,   0x00,  0x44,  0x00,  0x00,  C_DisNo,                               0x01,                  0x42,    C_NoOffset},	/*B相Ub相角*/
	{0x00,   0x00,  0x24,  0x00,  0x00,  C_DisNo,                               0x01,                  0x42,    C_NoOffset},	/*C相Uc相角*/
	{0x00,   0x00,  0x84,  0x00,  0x00,  C_DisNo,                               0x01,                  0x42,    C_NoOffset},	/*A相UaIa相角*/
	{0x00,   0x00,  0x44,  0x00,  0x00,  C_DisNo,                               0x01,                  0x42,    C_NoOffset},	/*B相UbIb相角*/
	{0x00,   0x00,  0x24,  0x00,  0x00,  C_DisNo,                               0x01,                  0x42,    C_NoOffset},	/*C相UcIc相角*/
	{0x00,   0xE0,  0x00,  0x00,  0x80,  C_DiskWNum,                            0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*瞬时总有功功率*/
	{0x00,   0xC0,  0x80,  0x00,  0x80,  C_DiskWNum,                            0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*A相瞬时有功功率*/
	{0x00,   0xC0,  0x40,  0x00,  0x80,  C_DiskWNum,                            0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*B相瞬时有功功率*/
	{0x00,   0xC0,  0x20,  0x00,  0x80,  C_DiskWNum,                            0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*C相瞬时有功功率*/
	{0x01,   0x60,  0x00,  0x00,  0x80,  C_DiskvarNum,                          0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*瞬时总无功功率*/
	{0x01,   0x40,  0x80,  0x00,  0x80,  C_DiskvarNum,                          0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*A相瞬时无功功率*/
	{0x01,   0x40,  0x40,  0x00,  0x80,  C_DiskvarNum,                          0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*B相瞬时无功功率*/
	{0x01,   0x40,  0x20,  0x00,  0x80,  C_DiskvarNum,                          0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*C相瞬时无功功率*/
	{0x00,   0x20,  0x00,  0x00,  0x80,  C_DiskVANum,                           0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*瞬时总视在功率*/
	{0x00,   0x00,  0x80,  0x00,  0x80,  C_DiskVANum,                           0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*A相瞬时视在功率*/
	{0x00,   0x00,  0x40,  0x00,  0x80,  C_DiskVANum,                           0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*B相瞬时视在功率*/
	{0x00,   0x00,  0x20,  0x00,  0x80,  C_DiskVANum,                           0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*C相瞬时视在功率*/
	{0x00,   0xE0,  0x00,  0x00,  0x80,  C_DiskWNum,                            0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*1分钟有功总平均功率*/
	{0x00,   0xC0,  0x80,  0x00,  0x80,  C_DiskWNum,		                    0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},    /*A相1分钟有功平均功率*/
	{0x00,   0xC0,  0x40,  0x00,  0x80,  C_DiskWNum,       	                    0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},    /*B相1分钟有功平均功率*/
	{0x00,   0xC0,  0x20,  0x00,  0x80,  C_DiskWNum,       	                    0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},    /*C相1分钟有功平均功率*/
	{0x01,   0x60,  0x00,  0x00,  0x80,  C_DiskvarNum,                          0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},    /*1分钟无功总平均功率*/
	{0x01,   0x40,  0x80,  0x00,  0x80,  C_DiskvarNum,		                    0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},    /*A相1分钟无功平均功率*/
	{0x01,   0x40,  0x40,  0x00,  0x80,  C_DiskvarNum,                          0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},    /*B相1分钟无功平均功率*/
	{0x01,   0x40,  0x20,  0x00,  0x80,  C_DiskvarNum,                          0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},    /*C相1分钟无功平均功率*/

	{0x00,   0x20,  0x0C,  0x00,  0x00,  C_DisNo,                               0x03,                  (0x42+C_NeedSignBit0x08),     C_NoOffset},	/*总功率因数*/
	{0x00,   0x00,  0x8C,  0x00,  0x00,  C_DisNo,                               0x03,                  (0x42+C_NeedSignBit0x08),     C_NoOffset},	/*A相功率因数*/
	{0x00,   0x00,  0x4C,  0x00,  0x00,  C_DisNo,                               0x03,                  (0x42+C_NeedSignBit0x08),     C_NoOffset},	/*B相功率因数*/
	{0x00,   0x00,  0x2C,  0x00,  0x00,  C_DisNo,                               0x03,                  (0x42+C_NeedSignBit0x08),     C_NoOffset},	/*C相功率因数*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x02,                  0x42,                         C_NoOffset},	/*电网频率*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x01,                  (0x42+C_NeedSignBit0x08),     C_NoOffset},	/*表内温度*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisVNum,                             0x02,                  0x42,                         C_NoOffset},	/*时钟电池电压*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisVNum,                             0x02,                  0x42,                         C_NoOffset},	/*停抄电池电压*/
	{0x00,   0x00,  0x00,  0x00,  0x60,  C_DisNo,                               0x00,                  0x04,                         C_NoOffset},	/*内部电池工作时间*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  (C_DisNo+C_NoNeedChange),              0x00,                  0xC2,                          C_NoOffset},	/*电表运行状态字1-7*/
	{0x80,   0xC0,  0x00,  0xA0,  0x00,  C_DiskWNum,                            0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*当前有功需量*/
	{0x81,   0x40,  0x00,  0xA0,  0x00,  C_DiskvarNum,                          0x04,                  (0x23+C_NeedSignBit0x08),    C_NoOffset},	/*当前无功需量*/
	/*{0x80,   0x00,  0x00,  0xA0,  0x00,  C_DiskVANum,                           0x04,                  0x23,    C_NoOffset},*/	/*当前视在需量*/
	{0x80,   0x00,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                  0x04,    C_NoOffset},	/*当前电价*/
	{0x80,   0x00,  0x00,  0x48,  0x00,  C_DisYuanNum,                          0x04,                  0x04,    C_NoOffset},	/*当前费率电价*/
	{0x80,   0x00,  0x02,  0x48,  0x00,  C_DisYuanNum,                          0x04,                  0x04,    C_NoOffset},	/*当前阶梯电价*/
	{0x80,   0x00,  0x00,  0x00,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,             0xA4,     0x03      },	/*事件发生日期  YYYYMMDD */
	{0x80,   0x00,  0x00,  0x00,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL2CoL15P7PDot,     0xA3,     0x00      },	/*事件发生时间   hhmmss  */
	{0x80,   0x00,  0x00,  0x00,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,             0xA4,     0x03      },	/*事件结束日期   YYMMDD  */
	{0x80,   0x00,  0x00,  0x00,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL2CoL15P7PDot,     0xA3,     0x00      },	/*事件结束时间 */
	{0x80,   0x00,  0x00,  0x00,  0x60,  C_DisNo+C_NeedDataChange,              C_5P7PDot,             0xA4,     0x03      },	/*数据冻结日期   YYMMDD  */
	{0x80,   0x00,  0x00,  0x00,  0x60,  C_DisNo+C_NeedSingleByteChange,        C_CoL2CoL15P7PDot,     0xA3,     0x00      },	/*数据冻结时间 */
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0,                     0x04,    C_NoOffset},	/*事件记录序号*/ 
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0,                     0x04,    C_NoOffset},	/*冻结记录序号*/ 
	{0x40,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x02,                  0x23,     C_NoOffset},	/*电压不平衡率*/	
	{0x40,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0x02,                  0x23,     C_NoOffset},	/*电流不平衡率*/	
	{0x00,   0x20,  0x00,  0x00,  0x00,  C_DisAhNum,                            0x02,                  0x04,    C_NoOffset},	/*总安时数*/	
	{0x00,   0x00,  0x80,  0x00,  0x00,  C_DisAhNum,                            0x02,                  0x04,    C_NoOffset},	/*A相安时数*/	
	{0x00,   0x00,  0x40,  0x00,  0x00,  C_DisAhNum,                            0x02,                  0x04,    C_NoOffset},	/*B相安时数*/	
	{0x00,   0x00,  0x20,  0x00,  0x00,  C_DisAhNum,                            0x02,                  0x04,    C_NoOffset},	/*C相安时数*/
	{0x00,   0x00,  0x01,  0x50,  0x00,  C_DisYuanNum,                          0x02,                  0x04,    C_NoOffset},	/*钱包文件(剩余金额)*/
	{0x00,   0x00,  0x00,  0x00,  0x00,  C_DisNo,                               0,                     0x04,    C_NoOffset},	/*钱包文件(购电次数)*/
	{0x00,   0x00,  0x00,  0x50,  0x00,  C_DisYuanNum,                          0x02,                  0x04,    C_NoOffset},	/*当前透支金额*/	
	{0x00,   0x00,  0x00,  0x50,  0x00,  C_DisYuanNum,                          0x02,                  0x04,    C_NoOffset},    /*累计购电金额*/
	{0xA0,   0x00,  0x00,  0x60,  0x00,  C_DiskWhNum,                           0x00,                  (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*月度组合有功总累计用电量*/	
	{0x80,   0x00,  0x02,  0x60,  0x00,  C_DiskWhNum,                           0x00,                  (0x05+C_NeedSignBit0x08),    C_NoOffset},	/*结算周期内组合有功总累计用电量*/
                                                         
};
#define GV_ChineseSignVi_Len (sizeof(GV_ChineseSignVi)/C_ChineseSignLen) 

const uchar8 GV_ChineseSignVi_1[][C_ChineseSignLen]=     /*变量*/
{
	{0x00,   0x00,  0x80,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*A电压合格率，电压检测时间	*/
	{0x00,   0x00,  0x80,  0x00,  0x00,  C_DisNo,          0x02,                 0x23,    C_NoOffset},	/*A电压合格率	*/
	{0x00,   0x00,  0x80,  0x00,  0x00,  C_DisNo,          0x02,                 0x23,    C_NoOffset},	/*A电压合格率	*/
	{0x00,   0x00,  0x80,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*A电压超上限时间	*/
	{0x00,   0x00,  0x80,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*A电压超下限时间	*/                                                         
	{0x00,   0x00,  0x80,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*A电压合格率，电压检测时间	*/
	{0x00,   0x00,  0x80,  0x00,  0x00,  C_DisNo,          0x02,                 0x23,    C_NoOffset},	/*A电压合格率	*/
	{0x00,   0x00,  0x80,  0x00,  0x00,  C_DisNo,          0x02,                 0x23,    C_NoOffset},	/*A电压合格率	*/
	{0x00,   0x00,  0x80,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*A电压超上限时间	*/
	{0x00,   0x00,  0x80,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*A电压超下限时间	*/                                                         
	{0x00,   0x00,  0x40,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*B电压合格率，电压检测时间	*/
	{0x00,   0x00,  0x40,  0x00,  0x00,  C_DisNo,          0x02,                 0x23,    C_NoOffset},	/*B电压合格率	*/
	{0x00,   0x00,  0x40,  0x00,  0x00,  C_DisNo,          0x02,                 0x23,    C_NoOffset},	/*B电压合格率	*/
	{0x00,   0x00,  0x40,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*B电压超上限时间	*/
	{0x00,   0x00,  0x40,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*B电压超下限时间	*/                                                         
	{0x00,   0x00,  0x40,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*B电压合格率，电压检测时间	*/
	{0x00,   0x00,  0x40,  0x00,  0x00,  C_DisNo,          0x02,                 0x23,    C_NoOffset},	/*B电压合格率	*/
	{0x00,   0x00,  0x40,  0x00,  0x00,  C_DisNo,          0x02,                 0x23,    C_NoOffset},	/*B电压合格率	*/
	{0x00,   0x00,  0x40,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*B电压超上限时间	*/
	{0x00,   0x00,  0x40,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*B电压超下限时间	*/                                                         
	{0x00,   0x00,  0x20,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*C电压合格率，电压检测时间	*/
	{0x00,   0x00,  0x20,  0x00,  0x00,  C_DisNo,          0x02,                 0x23,    C_NoOffset},	/*C电压合格率	*/
	{0x00,   0x00,  0x20,  0x00,  0x00,  C_DisNo,          0x02,                 0x23,    C_NoOffset},	/*C电压合格率	*/
	{0x00,   0x00,  0x20,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*C电压超上限时间	*/
	{0x00,   0x00,  0x20,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*C电压超下限时间	*/                                                         
	{0x00,   0x00,  0x20,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*C电压合格率，电压检测时间	*/
	{0x00,   0x00,  0x20,  0x00,  0x00,  C_DisNo,          0x02,                 0x23,    C_NoOffset},	/*C电压合格率	*/
	{0x00,   0x00,  0x20,  0x00,  0x00,  C_DisNo,          0x02,                 0x23,    C_NoOffset},	/*C电压合格率	*/
	{0x00,   0x00,  0x20,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*C电压超上限时间	*/
	{0x00,   0x00,  0x20,  0x00,  0x60,  C_DisNo,          0,                    0x23,    C_NoOffset},	/*C电压超下限时间	*/                                                         

};
#define GV_ChineseSignVi_1_Len (sizeof(GV_ChineseSignVi_1)/C_ChineseSignLen) 



typedef  struct
{
	  uchar8 DI1;                            /*DI1*/
	  uchar8 DI0Max;						 /*当多次时为DI0最大取值，不是多次时为645 DI0具体值*/
	  uchar8 MaxDisplayScreen;			     /*该类标识码对应最大显示屏数，标识码屏数判断采用该变量*/ 
	  uchar8 DI0Character;                   /*DI0数据特征*/
	  /*uchar8 TureDisplayScreen;*/			 /*该类标识码实际显示屏数，有的是汉字表格借用,完全借用则为0，汉字表格偏移采用该变量*/
}Str_DisplayDI1_0Table;				         /*显示标识码1_0结构体，1级表*/

/***********取不同值，表示DI0不同处理方式。****************/
#define C_DI0_0EqualMany       0x01     /*01：表示00与01标识码(包括多次)显示辅助汉字相同。如电量、需量、电压合格率记录等。只列DI0最大值*/
#define C_DI0_0NoEqualMany     0x02     /*02：表示00与01(包括多次)不同显示辅助汉字不同，事件记录类。列DI0最大值及DI0=00；*/
#define C_DI0_Out0_Many        0x03     /*03：(多次)，不支持DI0==00；冻结类，只列DI0最大值*/
#define C_DI0_OutMany          0x04     /*04：不支持多次(DI0不同，显示辅助汉字也不同)，所有DI0标识码全列出，如参变量类、变量类 */
/*#define C_DI0_Out0_Many         0x05*/     /*05：失压记录数据，DI2=0，特殊处理，同时只列最近1次失压发生时刻*/
#define C_DI0_Out0_ManyBorr    20
#define C_DI0_Out0_ManyBorr_0  20     /*20：(多次)，不支持DI0==00,辅助汉字表格完全借用，如类似功率超限、失压、失流类数据，计算辅助显示表格时，该显示屏为20-20=0*/
#define C_DI0_Out0_ManyBorr_4  24     /*24：(多次)，不支持DI0==00,辅助汉字表格没有全列，只列前24-20=4屏，如时段表、时区表、节假日等，计算辅助显示表格时，该显示屏为24-20=4*/
#define C_DI0_Out0_ManyBorr_6  26     /*26：(多次)，不支持DI0==00,辅助汉字表格没有全列，只列前26-20=6屏，如阶梯表编程记录等，计算辅助显示表格时，该显示屏为26-20=6*/
#define C_DI0_Out0_ManyBorr_1  21     /*21：(多次)，不支持DI0==00,辅助汉字表格没有全列，只列前21-20=1屏，如日时段表等，计算辅助显示表格时，该显示屏为21-20=1*/
#define C_DI0_Out0_ManyBorr_2  22     /*22：(多次)，不支持DI0==00,辅助汉字表格没有全列，只列前22-20=2屏，如公共假日表，该显示屏为22-20=2*/

#define C_DI0_OutManyBorr      40
#define C_DI0_OutManyBorr_0    40     /*40：不支持多次(DI0不同，显示辅助汉字也不同)，辅助汉字表格完全借用，如有功组合*/
                                      /*状态字编程总次数等，计算辅助显示表格时，该显示屏为C_DI0_OutManyBorr_0-C_DI0_OutManyBorr=0*/
#define C_DI0_OutManyBorr_1    41     /*41：不支持多次(DI0不同，显示辅助汉字也不同)，辅助汉字表格没有全列，如时区表*/
                                      /*计算辅助显示表格时，该显示屏为C_DI0_OutManyBorr_1-C_DI0_OutManyBorr=1*/
#define C_DI0_OutManyBorr_3    43     /*43：不支持多次(DI0不同，显示辅助汉字也不同)，辅助汉字表格没有全列，如阶梯表*/
                                      /*计算辅助显示表格时，该显示屏为C_DI0_OutManyBorr_3-C_DI0_OutManyBorr=3*/

#define C_DI0_0EqualManyBorr   60
#define C_DI0_0EqualManyBorr_0 60     /*60：(多次)，支持DI0==00,辅助汉字表格完全借用，电压合格率记录，计算辅助显示表格时，该显示屏为60-60=0*/


const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableEn0[]=        /*DI2=0,同DI2=0--08*/
{	/*uchar8 DI1        uchar8 DI0Max     uchar8 最大显示屏数   uchar8 DI0Character*/ 
	{0x02,                0x01,                 0x01,              C_DI0_OutMany},         /*总*/
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

	{0x04,                0x01,                 0x01,              C_DI0_OutMany},         /*总*/
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

	{0x06,                0x01,                 0x01,              C_DI0_OutMany},         /*总*/
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

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableEn15[]=        /*DI2=15,同DI2=15--44*/
{	/*uchar8 DI1        uchar8 DI0Max     uchar8 最大显示屏数   uchar8 DI0Character*/ 
	{0x02,                0x01,                 0x01,              C_DI0_OutMany},         
	{0x04,                0x01,                 0x01,              C_DI0_OutMany},         
	{0x06,                0x01,                 0x01,              C_DI0_OutMany},         

};
#define GV_Str_DisplayDI1_0TableEn15Len (sizeof(GV_Str_DisplayDI1_0TableEn15)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableDe0[]=        /*DI2=0,同DI2=0--08*/
{	/*uchar8 DI1        uchar8 DI0Max     uchar8 最大显示屏数   uchar8 DI0Character*/
	{0x02,                0x01,                 0x03,             C_DI0_OutMany},         /*总*/
	{0x02,                0x02,                 0x03,             C_DI0_OutMany},         /*费率1*/
	{0x02,                0x03,                 0x03,             C_DI0_OutMany},         /*费率2*/
	{0x02,                0x04,                 0x03,             C_DI0_OutMany},         /*费率3*/
	{0x02,                0x05,                 0x03,             C_DI0_OutMany},         /*费率4*/
	{0x02,                0x06,                 0x03,             C_DI0_OutMany},         /*费率5*/
	{0x02,                0x07,                 0x03,             C_DI0_OutMany},         /*费率6*/
	{0x02,                0x08,                 0x03,             C_DI0_OutMany},         /*费率7*/
	{0x02,                0x09,                 0x03,             C_DI0_OutMany},         /*费率8*/
	{0x02,                0x0A,                 0x03,             C_DI0_OutMany},         /*费率9*/
	{0x02,                0x0B,                 0x03,             C_DI0_OutMany},         /*费率10*/
	{0x02,                0x0C,                 0x03,             C_DI0_OutMany},         /*费率11*/
	{0x02,                0x0D,                 0x03,             C_DI0_OutMany},         /*费率12*/

};
#define GV_Str_DisplayDI1_0TableDe0Len (sizeof(GV_Str_DisplayDI1_0TableDe0)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableDe15[]=        /*DI2=15,同DI2=15--44*/
{	/*uchar8 DI1        uchar8 DI0Max    uchar8 最大显示屏数   uchar8 DI0Character*/ 
	{0x02,                0x01,                 0x03,             C_DI0_OutMany},         
};
#define GV_Str_DisplayDI1_0TableDe15Len (sizeof(GV_Str_DisplayDI1_0TableDe15)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableFr0[]=        /*DI2=00*/
{	/*uchar8 DI1        uchar8 DI0Max   uchar8 最大显示屏数   uchar8 DI0Character*/
	{0x02,                0x3C,               0x02,              C_DI0_Out0_ManyBorr_0},	  	           
};
#define GV_Str_DisplayDI1_0TableFr0Len (sizeof(GV_Str_DisplayDI1_0TableFr0)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableFr1[]=        /*DI2=01*/
{	/*uchar8 DI1        uchar8 DI0Max   uchar8 最大显示屏数   uchar8 DI0Character*/
	{0x00,                0x3,               0x00,              C_DI0_Out0_ManyBorr_0},	  	           
};
#define GV_Str_DisplayDI1_0TableFr1Len (sizeof(GV_Str_DisplayDI1_0TableFr1)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableFr2[]=        /*DI2=02*/
{	/*uchar8 DI1        uchar8 DI0Max   uchar8 最大显示屏数   uchar8 DI0Character*/
	{0x02,                0xFF,               0x00,              C_DI0_Out0_ManyBorr_0},
	  	           
};
#define GV_Str_DisplayDI1_0TableFr2Len (sizeof(GV_Str_DisplayDI1_0TableFr2)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableFr3[]=        /*DI2=03*/
{	/*uchar8 DI1        uchar8 DI0Max   uchar8 最大显示屏数   uchar8 DI0Character*/
	{0x02,                0xFE,               0x00,              C_DI0_Out0_ManyBorr_0},
};
#define GV_Str_DisplayDI1_0TableFr3Len (sizeof(GV_Str_DisplayDI1_0TableFr3)/sizeof(Str_DisplayDI1_0Table)) 
const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableFr4[]=        /*DI2=04*/
{	/*uchar8 DI1        uchar8 DI0Max   uchar8 最大显示屏数   uchar8 DI0Character*/ 
	{0x02,               0xFF,               0x02,              C_DI0_Out0_ManyBorr_0},
};
#define GV_Str_DisplayDI1_0TableFr4Len (sizeof(GV_Str_DisplayDI1_0TableFr4)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableFr5[]=        /*DI2=04*/
{	/*uchar8 DI1        uchar8 DI0Max   uchar8 最大显示屏数   uchar8 DI0Character*/ 
	{0x02,               12,               0x02,              C_DI0_Out0_ManyBorr_0},
};
#define GV_Str_DisplayDI1_0TableFr5Len (sizeof(GV_Str_DisplayDI1_0TableFr5)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableFr6[]=        /*DI2=06*/
{   /*uchar8 DI1        uchar8 DI0Max   uchar8 最大显示屏数   uchar8 DI0Character*/
	{0x02,               24,               0x02,              C_DI0_Out0_ManyBorr_0},
};
#define GV_Str_DisplayDI1_0TableFr6Len (sizeof(GV_Str_DisplayDI1_0TableFr6)/sizeof(Str_DisplayDI1_0Table)) 
const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableFr7[]=        /*DI2=04*/
{	/*uchar8 DI1        uchar8 DI0Max   uchar8 最大显示屏数   uchar8 DI0Character*/ 
	{0x02,               4,               0x02,              C_DI0_Out0_ManyBorr_0},
};
#define GV_Str_DisplayDI1_0TableFr7Len (sizeof(GV_Str_DisplayDI1_0TableFr7)/sizeof(Str_DisplayDI1_0Table)) 



const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableFr8[]=        /*DI2=08*/
{	/*uchar8 DI1        uchar8 DI0Max   uchar8 最大显示屏数   uchar8 DI0Character*/
	{0x02,                02,               0x02,              C_DI0_Out0_ManyBorr_0},
	  	           
};
#define GV_Str_DisplayDI1_0TableFr8Len (sizeof(GV_Str_DisplayDI1_0TableFr8)/sizeof(Str_DisplayDI1_0Table)) 


const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TablePort0[]=        /*DI2=00*/
{	/*uchar8 DI1        uchar8 DI0Max   uchar8 最大显示屏数   uchar8 DI0Character*/
	{0x02,                0x01,               0x02,              C_DI0_OutMany},	  	           
	{0x02,                0x02,               0x02,              C_DI0_OutMany},	  	           
};
#define GV_Str_DisplayDI1_0TablePort0Len (sizeof(GV_Str_DisplayDI1_0TablePort0)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TablePort9[]=        /*DI2=00*/
{	/*uchar8 DI1        uchar8 DI0Max   uchar8 最大显示屏数   uchar8 DI0Character*/
	{0x02,                0x01,               0x02,              C_DI0_OutMany},	  	             	           
};
#define GV_Str_DisplayDI1_0TablePort9Len (sizeof(GV_Str_DisplayDI1_0TablePort9)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableEv00[]=        /*DI2=05*/
{	/*uchar8 DI1        uchar8 DI0Max  uchar8 最大显示屏数   uchar8 DI0Character*/   
	{0x05,                0x01,              0x01,              C_DI0_OutMany},/*触发上线*/
	{0x05,                0x02,              0x01,              C_DI0_OutMany},
	{0x05,                0x03,              0x01,              C_DI0_OutMany},
	{0x05,                0x04,              0x01,              C_DI0_OutMany},/*延时时间*/
	{0x0A,                0x01,              0x02,              C_DI0_OutMany},/*总累计次数和时间*/
	{0x0A,                0x02,              0x02,              C_DI0_OutMany},/*A累计次数和时间*/
	{0x0A,                0x03,              0x02,              C_DI0_OutMany},/*B累计次数和时间*/
	{0x0A,                0x04,              0x02,              C_DI0_OutMany},/*C累计次数和时间*/
	{0x06,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*总失压记录*/	
	{0x07,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*A失压记录*/
	{0x08,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*B失压记录*/
	{0x09,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*C失压记录*/
	{0x0D,                0x01,              0x01,              C_DI0_OutMany},/*事件发生总次数*/
	{0x0D,                0x02,              0x01,              C_DI0_OutMany},/*事件总累计时间*/
	{0x0D,                0x03,              0x02,              C_DI0_OutMany},/*最近一次失压发生时间*/
	{0x0D,                0x04,              0x02,              C_DI0_OutMany},/*最近一次失压结束时间*/		
	{0x0E,                0x01,              0x04,              C_DI0_OutMany},/*总最近一次发生结束时间*/
	{0x0E,                0x02,              0x04,              C_DI0_OutMany},/*A最近一次发生结束时间*/
	{0x0E,                0x03,              0x04,              C_DI0_OutMany},/*B最近一次发生结束时间*/
	{0x0E,                0x04,              0x04,              C_DI0_OutMany},/*C最近一次发生结束时间*/
};
#define GV_Str_DisplayDI1_0TableEv00Len (sizeof(GV_Str_DisplayDI1_0TableEv00)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableEv01[]=        /*DI2=01*/
{	/*uchar8 DI1        uchar8 DI0Max  uchar8 最大显示屏数   uchar8 DI0Character*/   
	{0x05,                0x01,              0x01,              C_DI0_OutMany},/*触发上线*/
	{0x05,                0x02,              0x01,              C_DI0_OutMany},/*判定延时时间*/
/*	{0x0A,                0x01,              0x02,              C_DI0_OutMany},*/ /*总累计次数和时间*/
	{0x0A,                0x02,              0x02,              C_DI0_OutMany},/*A累计次数和时间*/
	{0x0A,                0x03,              0x02,              C_DI0_OutMany},/*B累计次数和时间*/
	{0x0A,                0x04,              0x02,              C_DI0_OutMany},/*C累计次数和时间*/
/*	{0x06,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},*/ /*总欠压记录*/	
	{0x07,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*A欠压记录*/
	{0x08,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*B欠压记录*/
	{0x09,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*C欠压记录*/
};
#define GV_Str_DisplayDI1_0TableEv01Len (sizeof(GV_Str_DisplayDI1_0TableEv01)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableEv03[]=        /*DI2=05*/
{/*uchar8 DI1        uchar8 DI0Max  uchar8 最大显示屏数   uchar8 DI0Character*/   
	{0x05,                0x01,              0x01,              C_DI0_OutMany},/*触发上线*/
	{0x05,                0x02,              0x01,              C_DI0_OutMany},/*触发上限*/
	{0x05,                0x03,              0x01,              C_DI0_OutMany},/*判定延时时间*/
/*	{0x0A,                0x01,              0x02,              C_DI0_OutMany},*/ /*总累计次数和时间*/
	{0x0A,                0x02,              0x02,              C_DI0_OutMany},/*A累计次数和时间*/
	{0x0A,                0x03,              0x02,              C_DI0_OutMany},/*B累计次数和时间*/
	{0x0A,                0x04,              0x02,              C_DI0_OutMany},/*C累计次数和时间*/
/*	{0x06,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},*/ /*总记录*/	
	{0x07,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*A记录*/
	{0x08,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*B记录*/
	{0x09,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*C记录*/
};
#define GV_Str_DisplayDI1_0TableEv03Len (sizeof(GV_Str_DisplayDI1_0TableEv03)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableEv07[]=        /*DI2=05*/
{	/*uchar8 DI1        uchar8 DI0Max  uchar8 最大显示屏数   uchar8 DI0Character*/   
	{0x05,                0x01,              0x01,              C_DI0_OutMany},/*触发上线*/
	{0x05,                0x02,              0x01,              C_DI0_OutMany},/*判定延时时间*/
	{0x0A,                0x01,              0x02,              C_DI0_OutMany},/*总累计次数和时间*/
	{0x0A,                0x02,              0x02,              C_DI0_OutMany},/*A累计次数和时间*/
	{0x0A,                0x03,              0x02,              C_DI0_OutMany},/*B累计次数和时间*/
	{0x0A,                0x04,              0x02,              C_DI0_OutMany},/*C累计次数和时间*/
	{0x06,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*总潮流反向记录*/	
	{0x07,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*A潮流反向记录*/
	{0x08,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*B潮流反向记录*/
	{0x09,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*C潮流反向记录*/
};
#define GV_Str_DisplayDI1_0TableEv07Len (sizeof(GV_Str_DisplayDI1_0TableEv07)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableEv04[]=        /*DI2=05*/
{	/*uchar8 DI1        uchar8 DI0Max  uchar8 最大显示屏数   uchar8 DI0Character*/   
	{0x05,                0x01,              0x01,              C_DI0_OutMany},/*电压触发上线*/
	{0x05,                0x02,              0x01,              C_DI0_OutMany},/*电流触发上限*/
	{0x05,                0x03,              0x01,              C_DI0_OutMany},/*电流触发下限*/
	{0x05,                0x04,              0x01,              C_DI0_OutMany},/*判定延时时间*/
	/*{0x0A,                0x01,              0x02,              C_DI0_OutMany},*/ /*总累计次数和时间*/
	{0x0A,                0x02,              0x02,              C_DI0_OutMany},/*A累计次数和时间*/
	{0x0A,                0x03,              0x02,              C_DI0_OutMany},/*B累计次数和时间*/
	{0x0A,                0x04,              0x02,              C_DI0_OutMany},/*C累计次数和时间*/
	/*{0x06,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},*/ /*总记录*/	
	{0x07,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*A记录*/
	{0x08,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*B记录*/
	{0x09,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*C记录*/
};
#define GV_Str_DisplayDI1_0TableEv04Len (sizeof(GV_Str_DisplayDI1_0TableEv04)/sizeof(Str_DisplayDI1_0Table)) 


const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableEv09[]=        /*正向有功需量超限*/
{	/*uchar8 DI1        uchar8 DI0Max  uchar8 最大显示屏数   uchar8 DI0Character*/   
	{0x06,                0x01,              0x01,              C_DI0_OutMany},/*触发下线*/
	{0x06,                0x02,              0x01,              C_DI0_OutMany},/*延时时间*/
	{0x07,                0x00,              0x03,              C_DI0_OutMany},/*累计次数和时间*/
	{0x02,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*总记录	*/
};
#define GV_Str_DisplayDI1_0TableEv09Len (sizeof(GV_Str_DisplayDI1_0TableEv09)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableEv0B[]=        /*无功需量超限*/
{	/*uchar8 DI1        uchar8 DI0Max  uchar8 最大显示屏数   uchar8 DI0Character*/   
	{0x05,                0x01,              0x01,              C_DI0_OutMany},/*电压触发上线*/
	{0x05,                0x02,              0x01,              C_DI0_OutMany},
	{0x0A,                0x01,              0x02,              C_DI0_OutMany},/*1累计次数和时间*/
	{0x0A,                0x02,              0x02,              C_DI0_OutMany},/*2累计次数和时间*/
	{0x0A,                0x03,              0x02,              C_DI0_OutMany},/*3累计次数和时间*/
	{0x0A,                0x04,              0x02,              C_DI0_OutMany},/*4累计次数和时间*/
	{0x06,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*1象限记录*/
	{0x07,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*2象限记录*/
	{0x08,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*3象限记录*/
	{0x09,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*4象限记录*/
};
#define GV_Str_DisplayDI1_0TableEv0BLen (sizeof(GV_Str_DisplayDI1_0TableEv0B)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableEv0D[]=        /*全失压*/
{	/*uchar8 DI1        uchar8 DI0Max  uchar8 最大显示屏数   uchar8 DI0Character*/   
	{0x07,                0x00,              0x03,              C_DI0_OutMany},/*累计次数和时间*/
	{0x02,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*总记录*/	
};
#define GV_Str_DisplayDI1_0TableEv0DLen (sizeof(GV_Str_DisplayDI1_0TableEv0D)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableEv0E[]=        /*辅助电源掉电*/
{	/*uchar8 DI1        uchar8 DI0Max  uchar8 最大显示屏数   uchar8 DI0Character*/   
	  {0x06,                0x01,              0x01,              C_DI0_OutMany},/*延时时间*/
	{0x07,                0x00,              0x03,              C_DI0_OutMany},/*累计次数和时间*/
	{0x02,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*总记录*/	
};
#define GV_Str_DisplayDI1_0TableEv0ELen (sizeof(GV_Str_DisplayDI1_0TableEv0E)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TableEv12[]=        /*电能表编程事件*/
{	/*uchar8 DI1        uchar8 DI0Max  uchar8 最大显示屏数   uchar8 DI0Character*/   
	{0x07,                0x00,              0x03,              C_DI0_OutMany},/*累计次数和时间*/
	{0x02,                0x0A,              0x00,              C_DI0_Out0_ManyBorr_0},/*总记录*/	
};
#define GV_Str_DisplayDI1_0TableEv12Len (sizeof(GV_Str_DisplayDI1_0TableEv12)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TablePa00[]=        /*DI2=00*/
{	/*uchar8 DI1        uchar8 DI0Max          uchar8 最大显示屏数   uchar8 DI0Character */
	{0x02,                0x00,                      0x02,              C_DI0_OutMany},	 
};
#define GV_Str_DisplayDI1_0TablePa00Len (sizeof(GV_Str_DisplayDI1_0TablePa00)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TablePa04[]=        /*DI2=00*/
{	/*uchar8 DI1        uchar8 DI0Max          uchar8 最大显示屏数   uchar8 DI0Character*/ 
	{0x02,                0x01,                      0x04,              C_DI0_OutMany},
	{0x02,                0x02,                      0x04,              C_DI0_OutMany},
	{0x02,                0x03,                      0x01,              C_DI0_OutMany},
};
#define GV_Str_DisplayDI1_0TablePa04Len (sizeof(GV_Str_DisplayDI1_0TablePa04)/sizeof(Str_DisplayDI1_0Table)) 


const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TablePa07[]=        /*DI2=00*/
{	/*uchar8 DI1        uchar8 DI0Max          uchar8 最大显示屏数   uchar8 DI0Character */
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
{	/*uchar8 DI1        uchar8 DI0Max          uchar8 最大显示屏数   uchar8 DI0Character */
	{0x02,                0x01,                      0x01,              C_DI0_OutMany},	 
	{0x02,                0x02,                      0x01,              C_DI0_OutMany},	 
	{0x02,                0x03,                      0x01,              C_DI0_OutMany},	 
	{0x02,                0x04,                      0x01,              C_DI0_OutMany},	 
	{0x02,                0x05,                      0x01,              C_DI0_OutMany},	 

};
#define GV_Str_DisplayDI1_0TablePa0CLen (sizeof(GV_Str_DisplayDI1_0TablePa0C)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TablePa0D[]=        /*DI2=00*/
{	/*uchar8 DI1        uchar8 DI0Max          uchar8 最大显示屏数   uchar8 DI0Character*/ 
	{0x02,                0x00,                      0x01,              C_DI0_OutMany},	 
};
#define GV_Str_DisplayDI1_0TablePa0DLen (sizeof(GV_Str_DisplayDI1_0TablePa0D)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TablePa11[]=        /*公共假日表*/
{	/*uchar8 DI1        uchar8 DI0Max   uchar8 最大显示屏数   uchar8 DI0Character*/  
	{0x02,                0xFE,               0x01,               C_DI0_Out0_ManyBorr_1},
};
#define GV_Str_DisplayDI1_0TablePa11Len (sizeof(GV_Str_DisplayDI1_0TablePa11)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TablePa14[]=        /*时区表*/
{	/*uchar8 DI1        uchar8 DI0Max   uchar8 最大显示屏数   uchar8 DI0Character*/     
	{0x02,                0x0E,               1,                C_DI0_Out0_ManyBorr_1  },

};
#define GV_Str_DisplayDI1_0TablePa14Len (sizeof(GV_Str_DisplayDI1_0TablePa14)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TablePa16[]=        /*日时段表*/
{	/*uchar8 DI1        uchar8 DI0Max   uchar8 最大显示屏数   uchar8 DI0Character */    
	{0x02,                0x08,               14,                C_DI0_Out0_ManyBorr_1  },

};
#define GV_Str_DisplayDI1_0TablePa16Len (sizeof(GV_Str_DisplayDI1_0TablePa16)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TablePa18[]=        /*DI2=05 费率1-12电价*/
{	/*uchar8 DI1        uchar8 DI0Max    uchar8 最大显示屏数   uchar8 DI0Character*/ 
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

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TablePa1A[]=        /*DI2=06 阶梯表*/
{	/*uchar8 DI1        uchar8 DI0Max    uchar8 最大显示屏数   uchar8 DI0Character*/ 
	{0x02,                0x01,                6,               C_DI0_OutMany},
	{0x02,                0x02,                7,               C_DI0_OutMany},  
	{0x02,                0x03,                4,               C_DI0_OutMany},
};
#define GV_Str_DisplayDI1_0TablePa1ALen (sizeof(GV_Str_DisplayDI1_0TablePa1A)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TablePa1E[]=        /*DI2=1e 报警金额限值*/
{	/*uchar8 DI1        uchar8 DI0Max    uchar8 最大显示屏数   uchar8 DI0Character*/ 
	{0x02,                0x01,                0x01,               C_DI0_OutMany},
	{0x02,                0x02,                0x01,               C_DI0_OutMany},
};
#define GV_Str_DisplayDI1_0TablePa1ELen (sizeof(GV_Str_DisplayDI1_0TablePa1E)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TablePa1F[]=        /*DI2=1e 报警金额限值*/
{	/*uchar8 DI1        uchar8 DI0Max    uchar8 最大显示屏数   uchar8 DI0Character*/ 
	{0x02,                0x01,                0x01,               C_DI0_OutMany},
	{0x02,                0x02,                0x01,               C_DI0_OutMany},
	{0x02,                0x03,                0x01,               C_DI0_OutMany},

};
#define GV_Str_DisplayDI1_0TablePa1FLen (sizeof(GV_Str_DisplayDI1_0TablePa1F)/sizeof(Str_DisplayDI1_0Table)) 
const Str_DisplayDI1_0Table GV_Str_DisplayDI1_0TablePa30[]=        /*DI2=05 费率1-4电价*/
{	/*uchar8 DI1        uchar8 DI0Max    uchar8 最大显示屏数   uchar8 DI0Character*/ 
	{0x02,                0x01,                0x01,               C_DI0_OutMany},
	{0x02,                0x02,                0x01,               C_DI0_OutMany},
	{0x02,                0x03,                0x01,               C_DI0_OutMany},
	{0x02,                0x04,                0x01,               C_DI0_OutMany},
};
#define GV_Str_DisplayDI1_0TablePa30Len (sizeof(GV_Str_DisplayDI1_0TablePa30)/sizeof(Str_DisplayDI1_0Table)) 


const Str_DisplayDI1_0Table GV_Str_DisplayDI2TableVi00[]=        /*DI2=01*/
{	/*uchar8 DI1        uchar8 DI0Max          uchar8 最大显示屏数   uchar8 DI0Character*/ 
	{0x02,                0x01,                      0x01,              C_DI0_OutMany},
	{0x02,                0x02,                      0x01,              C_DI0_OutMany},
	{0x02,                0x03,                      0x01,              C_DI0_OutMany},
};
#define GV_Str_DisplayDI2TableVi00Len (sizeof(GV_Str_DisplayDI2TableVi00)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI2TableVi01[]=        /*DI2=01*/
{	/*uchar8 DI1        uchar8 DI0Max          uchar8 最大显示屏数   uchar8 DI0Character*/ 
	{0x02,                0x01,                      0x01,              C_DI0_OutMany},
	{0x02,                0x02,                      0x01,              C_DI0_OutMany},
	{0x02,                0x03,                      0x01,              C_DI0_OutMany},
	{0x04,                0x00,                      0x01,              C_DI0_OutMany},
};
#define GV_Str_DisplayDI2TableVi01Len (sizeof(GV_Str_DisplayDI2TableVi01)/sizeof(Str_DisplayDI1_0Table)) 


const Str_DisplayDI1_0Table GV_Str_DisplayDI2TableVi03[]=        /*DI2=03*/
{	/*uchar8 DI1        uchar8 DI0Max          uchar8 最大显示屏数   uchar8 DI0Character*/
	{0x02,                0x01,                      0x01,              C_DI0_OutMany}, 
	{0x02,                0x02,                      0x01,              C_DI0_OutMany},
	{0x02,                0x03,                      0x01,              C_DI0_OutMany},
	{0x02,                0x04,                      0x01,              C_DI0_OutMany},
};
#define GV_Str_DisplayDI2TableVi03Len (sizeof(GV_Str_DisplayDI2TableVi03)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI2TableVi07[]=        /*DI2=03*/
{	/*uchar8 DI1        uchar8 DI0Max          uchar8 最大显示屏数   uchar8 DI0Character*/
	{0x02,                0x00,                      0x01,              C_DI0_OutMany}, 
};
#define GV_Str_DisplayDI2TableVi07Len (sizeof(GV_Str_DisplayDI2TableVi07)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI2TableVi14[]=        /*DI2=03*/
{	/*uchar8 DI1        uchar8 DI0Max          uchar8 最大显示屏数   uchar8 DI0Character*/
	{0x02,                0x07,                      0x01,              C_DI0_Out0_ManyBorr_1}, 			
};
#define GV_Str_DisplayDI2TableVi14Len (sizeof(GV_Str_DisplayDI2TableVi14)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI2TableVi1E[]=        /*DI2=03*/
{	/*uchar8 DI1        uchar8 DI0Max          uchar8 最大显示屏数   uchar8 DI0Character*/
	{0x02,                0x00,                      0x02,              C_DI0_OutMany}, 			
	/*{0x02,                0x02,                      0x01,              C_DI0_OutMany}, */			

};
#define GV_Str_DisplayDI2TableVi1ELen (sizeof(GV_Str_DisplayDI2TableVi1E)/sizeof(Str_DisplayDI1_0Table)) 

const Str_DisplayDI1_0Table GV_Str_DisplayDI2TableVi2c[]=        /*DI2=03*/
{	/*uchar8 DI1        uchar8 DI0Max          uchar8 最大显示屏数   uchar8 DI0Character*/
	{0x02,                0x01,                      0x01,              C_DI0_OutMany}, 			
	{0x02,                0x02,                      0x01,              C_DI0_OutMany}, 			
};
#define GV_Str_DisplayDI2TableVi2cLen (sizeof(GV_Str_DisplayDI2TableVi2c)/sizeof(Str_DisplayDI1_0Table)) 
const Str_DisplayDI1_0Table GV_Str_DisplayDI2TableVi31[]=        /*DI2=03*/
{	/*uchar8 DI1        uchar8 DI0Max          uchar8 最大显示屏数   uchar8 DI0Character*/
	{0x02,                0x01,                      0x05,              C_DI0_OutMany}, 			
	{0x02,                0x02,                      0x05,              C_DI0_OutMany}, 			
};
#define GV_Str_DisplayDI2TableVi31Len (sizeof(GV_Str_DisplayDI2TableVi31)/sizeof(Str_DisplayDI1_0Table)) 


const Str_DisplayDI1_0Table GV_Str_DisplayDI2TableVi25[]=        /*DI2=03*/
{	/*uchar8 DI1        uchar8 DI0Max          uchar8 最大显示屏数   uchar8 DI0Character*/
	{0x02,                0x00,                      0x02,              C_DI0_OutMany}, 			

};
#define GV_Str_DisplayDI2TableVi25Len (sizeof(GV_Str_DisplayDI2TableVi25)/sizeof(Str_DisplayDI1_0Table)) 


typedef  struct
{
	  ulong32 PDI1_0Table;	                 /*对应DI1、DI0表格地址*/
	  uchar8 DI2;						     /*DI2*/
	  uchar8 DI1_0TableLen;			         /*DI1、DI0表格长度*/ 
}Str_DisplayDI2Table;				         /*显示标识码2结构体，2级表*/

const Str_DisplayDI2Table GV_Str_DisplayDI2TableEn[]=    /*电量类*/
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

const Str_DisplayDI2Table GV_Str_DisplayDI2TableDe[]=      /*需量类*/
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

const Str_DisplayDI2Table GV_Str_DisplayDI2TableFr[]=          /*冻结类*///
{	/*ulong32 PDI1_0Table                     uchar8 DI2        uchar8 DI1_0TableLen*/
	{(ulong32)(GV_Str_DisplayDI1_0TableFr0),       0x00,         GV_Str_DisplayDI1_0TableFr0Len}, /*瞬时冻结*/
	/*{(ulong32)(GV_Str_DisplayDI1_0TableFr1),       0x01,         GV_Str_DisplayDI1_0TableFr1Len},*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TableFr2),       0x02,         GV_Str_DisplayDI1_0TableFr2Len}, /*分钟冻结*/
	{(ulong32)(GV_Str_DisplayDI1_0TableFr3),       0x03,         GV_Str_DisplayDI1_0TableFr3Len}, /*小时冻结*/
	{(ulong32)(GV_Str_DisplayDI1_0TableFr4),       0x04,         GV_Str_DisplayDI1_0TableFr4Len}, /*日冻结*/
	{(ulong32)(GV_Str_DisplayDI1_0TableFr5),       0x05,         GV_Str_DisplayDI1_0TableFr5Len}, /*结算日冻结*/
	{(ulong32)(GV_Str_DisplayDI1_0TableFr6),       0x06,         GV_Str_DisplayDI1_0TableFr6Len}, /*月冻结*/
	{(ulong32)(GV_Str_DisplayDI1_0TableFr7),       0x07,         GV_Str_DisplayDI1_0TableFr7Len}, /*年冻结*/
	{(ulong32)(GV_Str_DisplayDI1_0TableFr8),       0x08,         GV_Str_DisplayDI1_0TableFr8Len}, /*切换冻结*/
	{(ulong32)(GV_Str_DisplayDI1_0TableFr8),       0x09,         GV_Str_DisplayDI1_0TableFr8Len}, /*切换冻结*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TableFr8),       0x0A,         GV_Str_DisplayDI1_0TableFr8Len}, /*切换冻结*/
	{(ulong32)(GV_Str_DisplayDI1_0TableFr8),       0x0B,         GV_Str_DisplayDI1_0TableFr8Len}, /*切换冻结*/
	{(ulong32)(GV_Str_DisplayDI1_0TableFr8),       0x11,         GV_Str_DisplayDI1_0TableFr8Len}, /*阶梯结算冻结*/
};
#define GV_Str_DisplayDI2TableFr_Len (sizeof(GV_Str_DisplayDI2TableFr)/sizeof(Str_DisplayDI2Table)) 

const Str_DisplayDI2Table GV_Str_DisplayDI2TablePort[]=          /*输入输出设备*/
{	/*ulong32 PDI1_0Table                     		uchar8 DI2     uchar8 DI1_0TableLen*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePort0),      0x01,        GV_Str_DisplayDI1_0TablePort0Len}, /*RS485*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePort9),      0x09,        GV_Str_DisplayDI1_0TablePort9Len}, /*模块*/
};
#define GV_Str_DisplayDI2TablePort_Len ( sizeof( GV_Str_DisplayDI2TablePort ) / sizeof( Str_DisplayDI2Table ) ) 


const Str_DisplayDI2Table GV_Str_DisplayDI2TableEv30[]=          /*03事件类*/
{	/*ulong32 PDI1_0Table                     uchar8 DI2        uchar8 DI1_0TableLen*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv00),       0x00,         GV_Str_DisplayDI1_0TableEv00Len},/*失压事件*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TableEv01),       0x01,         GV_Str_DisplayDI1_0TableEv01Len},/*欠压事件*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TableEv01),       0x02,         GV_Str_DisplayDI1_0TableEv01Len},/*过压事件*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TableEv03),       0x03,         GV_Str_DisplayDI1_0TableEv03Len},/*断相事件*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TableEv04),       0x04,         GV_Str_DisplayDI1_0TableEv04Len},/*失流事件*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TableEv01),       0x05,         GV_Str_DisplayDI1_0TableEv01Len},/*过流事件*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TableEv03),       0x06,         GV_Str_DisplayDI1_0TableEv03Len},/*断流事件*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TableEv07),       0x07,         GV_Str_DisplayDI1_0TableEv07Len},/*功率反向事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv01),       0x08,         GV_Str_DisplayDI1_0TableEv01Len},/*过载事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv09),       0x09,         GV_Str_DisplayDI1_0TableEv09Len},/*正向有功需量超限*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv09),       0x0A,         GV_Str_DisplayDI1_0TableEv09Len},/*反向有功需量超限*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv0B),       0x0B,         GV_Str_DisplayDI1_0TableEv0BLen},/*无功需量超限*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv09),       0x0C,         GV_Str_DisplayDI1_0TableEv09Len},/*功率因数超下限*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv0D),       0x0D,         GV_Str_DisplayDI1_0TableEv0DLen},/*全失压事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv0E),       0x0E,         GV_Str_DisplayDI1_0TableEv0ELen},/*辅助电源掉电事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv0E),       0x0F,         GV_Str_DisplayDI1_0TableEv0ELen},/*电压逆向序事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv0E),       0x10,         GV_Str_DisplayDI1_0TableEv0ELen},/*电流逆向序事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv0E),       0x11,         GV_Str_DisplayDI1_0TableEv0ELen},/*掉电事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x12,         GV_Str_DisplayDI1_0TableEv12Len},/*编程事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x13,         GV_Str_DisplayDI1_0TableEv12Len},/*清零事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x14,         GV_Str_DisplayDI1_0TableEv12Len},/*需量清零事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x15,         GV_Str_DisplayDI1_0TableEv12Len},/*事件清零事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x16,         GV_Str_DisplayDI1_0TableEv12Len},/*校时事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x17,         GV_Str_DisplayDI1_0TableEv12Len},/*时段表编程事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x18,         GV_Str_DisplayDI1_0TableEv12Len},/*时区表编程事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x19,         GV_Str_DisplayDI1_0TableEv12Len},/*周休日编程事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x1A,         GV_Str_DisplayDI1_0TableEv12Len},/*结算日编程事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x1B,         GV_Str_DisplayDI1_0TableEv12Len},/*开盖事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x1C,         GV_Str_DisplayDI1_0TableEv12Len},/*开端扭盖事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv09),       0x1D,         GV_Str_DisplayDI1_0TableEv09Len},/*电压不平衡事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv09),       0x1E,         GV_Str_DisplayDI1_0TableEv09Len},/*电流不平衡事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x1F,         GV_Str_DisplayDI1_0TableEv12Len},/*跳闸事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x20,         GV_Str_DisplayDI1_0TableEv12Len},/*合闸事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x21,         GV_Str_DisplayDI1_0TableEv12Len},/*节假日编程事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x22,         GV_Str_DisplayDI1_0TableEv12Len},/*有功组合方式编程事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x23,         GV_Str_DisplayDI1_0TableEv12Len},/*无功组合方式编程事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x24,         GV_Str_DisplayDI1_0TableEv12Len},/*费率表变成事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x25,         GV_Str_DisplayDI1_0TableEv12Len},/*阶梯表编程事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x26,         GV_Str_DisplayDI1_0TableEv12Len},/*密钥更新事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x27,         GV_Str_DisplayDI1_0TableEv12Len},/*异常插卡事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x28,         GV_Str_DisplayDI1_0TableEv12Len},/*购电事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv12),       0x29,         GV_Str_DisplayDI1_0TableEv12Len},/*退费事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv0E),       0x2A,         GV_Str_DisplayDI1_0TableEv0ELen},/*磁场干扰事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv0E),       0x2B,         GV_Str_DisplayDI1_0TableEv0ELen},/*负荷开关误动作事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv0E),       0x2C,         GV_Str_DisplayDI1_0TableEv0ELen},/*电源异常事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv09),       0x2D,         GV_Str_DisplayDI1_0TableEv09Len},/*电流严重不平衡事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv0E),       0x2E,         GV_Str_DisplayDI1_0TableEv0ELen},/*时钟故障事件*/
	{(ulong32)(GV_Str_DisplayDI1_0TableEv0E),       0x2F,         GV_Str_DisplayDI1_0TableEv0ELen},/*电能表计量芯片故障事件*/
	/*{(ulong32)(GV_Str_DisplayDI1_0TableEv0E),       0x30,         GV_Str_DisplayDI1_0TableEv0ELen},*/ /*通信模块变更事件*/
};
#define GV_Str_DisplayDI2TableEv30_Len (sizeof(GV_Str_DisplayDI2TableEv30)/sizeof(Str_DisplayDI2Table)) 

const Str_DisplayDI2Table GV_Str_DisplayDI2TablePa[]=          /*参变量*/
{    /*ulong32 PDI1_0Table                          uchar8 DI2        uchar8 DI1_0TableLen*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa00),         0x00,         GV_Str_DisplayDI1_0TablePa00Len},    /*日期时间*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TablePa00),         0x01,         GV_Str_DisplayDI1_0TablePa00Len},    /*通信地址*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TablePa00),         0x02,         GV_Str_DisplayDI1_0TablePa00Len},    /*表号*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa00),         0x03,         GV_Str_DisplayDI1_0TablePa00Len},    /*客户编号*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TablePa04),         0x04,         GV_Str_DisplayDI1_0TablePa04Len},    /*设备地理位置*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa07),         0x07,         GV_Str_DisplayDI1_0TablePa07Len},    
	{(ulong32)(GV_Str_DisplayDI1_0TablePa00),         0x08,         GV_Str_DisplayDI1_0TablePa00Len},    /*切换时间*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TablePa00),         0x09,         GV_Str_DisplayDI1_0TablePa00Len},    /*切换时间*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TablePa00),         0x0A,         GV_Str_DisplayDI1_0TablePa00Len},    /*切换时间*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TablePa00),         0x0B,         GV_Str_DisplayDI1_0TablePa00Len},    /*切换时间*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0C),         0x0C,         GV_Str_DisplayDI1_0TablePa0CLen},    /*时区时段数*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0D),         0x0D,         GV_Str_DisplayDI1_0TablePa0DLen},    /*阶梯数*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0D),         0x0F,         GV_Str_DisplayDI1_0TablePa0DLen},    /*密钥总条数*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa11),         0x11,         GV_Str_DisplayDI1_0TablePa11Len},    /*公共假日表*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0D),         0x12,         GV_Str_DisplayDI1_0TablePa0DLen},    /*周休日特征字*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0D),         0x13,         GV_Str_DisplayDI1_0TablePa0DLen},    /*周休日采用的日时段表号*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa14),         0x14,         GV_Str_DisplayDI1_0TablePa14Len},    /*当前套时区表*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa14),         0x15,         GV_Str_DisplayDI1_0TablePa14Len},    /*备用套时区表*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa16),         0x16,         GV_Str_DisplayDI1_0TablePa16Len},    /*当前套日时段表*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa16),         0x17,         GV_Str_DisplayDI1_0TablePa16Len},    /*备用套日时段表*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa18),         0x18,         GV_Str_DisplayDI1_0TablePa18Len},    /*当前套费率电价*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa18),         0x19,         GV_Str_DisplayDI1_0TablePa18Len},    /*备用套费率电价*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa1A),         0x1A,         GV_Str_DisplayDI1_0TablePa1ALen},    /*当前套阶梯电价*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa1A),         0x1B,         GV_Str_DisplayDI1_0TablePa1ALen},    /*备用套阶梯电价*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0D),         0x1C,         GV_Str_DisplayDI1_0TablePa0DLen},    /*电流互感器变比*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0D),         0x1D,         GV_Str_DisplayDI1_0TablePa0DLen},    /*电压互感器变比*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TablePa1E),         0x1E,         GV_Str_DisplayDI1_0TablePa1ELen},    /*报警金额限制*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa1F),         0x1F,         GV_Str_DisplayDI1_0TablePa1FLen},    /*其他金额限制*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0D),         0x22,         GV_Str_DisplayDI1_0TablePa0DLen},    /*插卡状态字*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa30),         0x30,         GV_Str_DisplayDI1_0TablePa30Len},    /*电压合格率参数*/ 
};
#define GV_Str_DisplayDI2TablePa_Len ( sizeof(GV_Str_DisplayDI2TablePa) / sizeof(Str_DisplayDI2Table) ) 

const Str_DisplayDI2Table GV_Str_DisplayDI2TablePa_1[]=          /*参变量*/
{	/*ulong32 PDI1_0Table                          uchar8 DI2        uchar8 DI1_0TableLen*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0D),         0x00,         GV_Str_DisplayDI1_0TablePa0DLen},/*最大需量周期*/ 
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0D),         0x01,         GV_Str_DisplayDI1_0TablePa0DLen},/*滑差时间*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0D),         0x02,         GV_Str_DisplayDI1_0TablePa0DLen},/*校表脉冲宽度*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0D),         0x09,         GV_Str_DisplayDI1_0TablePa0DLen},/*有功常数*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0D),         0x0A,         GV_Str_DisplayDI1_0TablePa0DLen},/*无功常数*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0D),         0x10,         GV_Str_DisplayDI1_0TablePa0DLen},/*无功常数*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0D),         0x12,         GV_Str_DisplayDI1_0TablePa0DLen},/*无功常数*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0D),         0x13,         GV_Str_DisplayDI1_0TablePa0DLen},/*无功常数*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa0D),         0x14,         GV_Str_DisplayDI1_0TablePa0DLen},/*无功常数*/
	{(ulong32)(GV_Str_DisplayDI1_0TablePa1F),         0x16,         GV_Str_DisplayDI1_0TablePa1FLen},/*无功常数*/
};
#define GV_Str_DisplayDI2TablePa_1_Len (sizeof(GV_Str_DisplayDI2TablePa_1)/sizeof(Str_DisplayDI2Table)) 


const Str_DisplayDI2Table GV_Str_DisplayDI2TableVi[]=          /*变量*/
{	/*ulong32 PDI1_0Table                          uchar8 DI2        uchar8 DI1_0TableLen*/
	{(ulong32)(GV_Str_DisplayDI2TableVi00),         0x00,         GV_Str_DisplayDI2TableVi00Len}, /*电压*/
	{(ulong32)(GV_Str_DisplayDI2TableVi01),         0x01,         GV_Str_DisplayDI2TableVi01Len}, /*电流*/
	{(ulong32)(GV_Str_DisplayDI2TableVi00),         0x02,         GV_Str_DisplayDI2TableVi00Len}, /*电压相角*/
	{(ulong32)(GV_Str_DisplayDI2TableVi00),         0x03,         GV_Str_DisplayDI2TableVi00Len}, 
	{(ulong32)(GV_Str_DisplayDI2TableVi03),         0x04,         GV_Str_DisplayDI2TableVi03Len}, 
	{(ulong32)(GV_Str_DisplayDI2TableVi03),         0x05,         GV_Str_DisplayDI2TableVi03Len}, 
	{(ulong32)(GV_Str_DisplayDI2TableVi03),         0x06,         GV_Str_DisplayDI2TableVi03Len}, 
	{(ulong32)(GV_Str_DisplayDI2TableVi03),         0x07,         GV_Str_DisplayDI2TableVi03Len},/*一分钟有功平均功率 */
	{(ulong32)(GV_Str_DisplayDI2TableVi03),         0x08,         GV_Str_DisplayDI2TableVi03Len},/*一分钟无功平均功率*/ 
	{(ulong32)(GV_Str_DisplayDI2TableVi03),         0x0A,         GV_Str_DisplayDI2TableVi03Len},/*功率因数 */
	{(ulong32)(GV_Str_DisplayDI2TableVi07),         0x0F,         GV_Str_DisplayDI2TableVi07Len},/*电网频率 */
	{(ulong32)(GV_Str_DisplayDI2TableVi07),         0x10,         GV_Str_DisplayDI2TableVi07Len},/*表内温度 */
	{(ulong32)(GV_Str_DisplayDI2TableVi07),         0x11,         GV_Str_DisplayDI2TableVi07Len},/*时钟电池电压 */
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
	{(ulong32)(GV_Str_DisplayDI2TableVi07),         0x26,         GV_Str_DisplayDI2TableVi07Len}, /*电压不平衡*/
	{(ulong32)(GV_Str_DisplayDI2TableVi07),         0x27,         GV_Str_DisplayDI2TableVi07Len}, /*电流不平衡*/
	{(ulong32)(GV_Str_DisplayDI2TableVi03),         0x29,         GV_Str_DisplayDI2TableVi03Len}, 
	{(ulong32)(GV_Str_DisplayDI2TableVi2c),         0x2C,         GV_Str_DisplayDI2TableVi2cLen}, /*钱包文件*/
	{(ulong32)(GV_Str_DisplayDI2TableVi07),         0x2D,         GV_Str_DisplayDI2TableVi07Len}, 
	{(ulong32)(GV_Str_DisplayDI2TableVi07),         0x2E,         GV_Str_DisplayDI2TableVi07Len}, 
	{(ulong32)(GV_Str_DisplayDI2TableVi07),         0x31,         GV_Str_DisplayDI2TableVi07Len}, 
	{(ulong32)(GV_Str_DisplayDI2TableVi07),         0x32,         GV_Str_DisplayDI2TableVi07Len}, 
};
#define GV_Str_DisplayDI2TableVi_Len (sizeof(GV_Str_DisplayDI2TableVi)/sizeof(Str_DisplayDI2Table)) 

const Str_DisplayDI2Table GV_Str_DisplayDI2TableVi_1[]=          /*变量*/
{	/*ulong32 PDI1_0Table                          uchar8 DI2        uchar8 DI1_0TableLen*/
	{(ulong32)(GV_Str_DisplayDI2TableVi31),         0x31,         GV_Str_DisplayDI2TableVi31Len}, /*当月A相电压合格率*/
	{(ulong32)(GV_Str_DisplayDI2TableVi31),         0x32,         GV_Str_DisplayDI2TableVi31Len}, /*当月B相电压合格率*/
	{(ulong32)(GV_Str_DisplayDI2TableVi31),         0x33,         GV_Str_DisplayDI2TableVi31Len}, /*当月C相电压合格率*/
};
#define GV_Str_DisplayDI2TableVi_1_Len (sizeof(GV_Str_DisplayDI2TableVi_1)/sizeof(Str_DisplayDI2Table)) 



typedef  struct 
{
	  ulong32 PDI2Table;	             /*对应DI2表格地址*/
	  ulong32 P_ChieseTable;             /*DI3对应辅助汉字表格地址*/
	  ushort16 ChieseTableLen;           /*汉字表格对应最大数据长度，判断是否越界用*/ 
	  uchar8 DI3;						 /*DI3*/
	  uchar8 DI2TableLen;			     /*DI2表格长度*/
}Str_DisplayDI3Table;				     /*显示标识码3结构体，3级表*/


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

/*************************函数定义***************************/
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
                       
