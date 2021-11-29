/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    AppEMUAtt7036.c                                                                          
**** Brief:       7036计量芯片相关头文件                                                                      
**** Author:      peter.he@chint.com                                                                 
**** Version:     V1.0                                                                               
**** Date:        2019年3月14日                                                                         
****                                                                                                 
**** note:修改历史记录列表，每条修改记录应包括修改日期、修改者                                          
**** 1.  Author:                                                                                     
****     Version:                                                                                    
****     Date :                                                                                      
**** 2.  Author:                                                                                     
****     Version:                                                                                       
****     Date:
****                                                                                        
****  addtogroup:Library                                                             
**********************************************************************************************************/

#ifndef   _APPEMUATT7036_H
#define   _APPEMUATT7036_H
#if ( METER_TYPE == METER_TYPE_DTSY666 )
/*-------------------------------- H文件使用说明 -------------------------------------------------------*/
/*
 *  该文件宏定义的前缀为:
 *
 */

 
/*----------------< 包含文件 >----------------------------------*/


/*----------------< 宏定义区 >----------------------------------*/
#define Pulse_Out_Disable()  GPIO_IOCFG_P1_DIR_O(4);GPIO_IOCFG_P1_SET_1(4)
#define Pulse_Out_Enable()	 GPIO_IOCFG_P1_DIR_O(4);GPIO_IOCFG_P1_SET_0(4)
#define C_PulseWidth          80


#define C_EMUCfg				 0xF884
#define	C_ModeCfg_Reg  			 0x01
#define	C_ModuleCFG_Reg 		 0x31
#define C_EMUCfg_Reg 			 0x03
#define C_PGACtrl_Reg 			 0x02
#define C_HFDouble_Reg 			 0x33
#define C_FailVoltage_Reg		 0x1F
#define C_Istarup_Reg 			 0x1D
#define C_IoffsetA_Reg 			 0x2D
#define C_IoffsetB_Reg 			 0x2E
#define C_IoffsetC_Reg 			 0x2F
#define C_EMCfg_Reg 			 0x70
#define	C_ActiveEnergy_TReg  	 0x21
#define	C_ActiveEnergy_AReg   	 0x1E
#define	C_ActiveEnergy_BReg  	 0x1F
#define C_ActiveEnergy_CReg   	 0x20
#define	C_ReativeEnergy_TReg 	 0x25
#define	C_ReativeEnergy_AReg  	 0x22
#define	C_ReativeEnergy_BReg 	 0x23
#define	C_ReativeEnergy_CReg 	 0x24
#define	C_ApparentEnergy_TReg	 0x38
#define	C_ApparentEnergy_AReg	 0x35
#define	C_ApparentEnergy_BReg	 0x36
#define	C_ApparentEnergy_CReg	 0x37
#define C_PFlag_Reg 			 0x2C

#define C_MeterPara              0x00		///计量参数
#define C_EMUPara                0x01		///校表参数

#define C_PGainA	 			 0x04		//A相有功功率增益
#define C_PGainB	 			 0x05		//B相有功功率增益
#define C_PGainC	 			 0x06		//C相有功功率增益

#define C_QGainA	 			 0x07		//A相无功率增益
#define C_QGainB	 			 0x08       //B相无功率增益
#define C_QGainC	 			 0x09       //C相无功率增益

#define C_SGainA	 			 0x0A		//A相视在率增益
#define C_SGainB	 			 0x0B       //B相视在率增益
#define C_SGainC	 			 0x0C       //C相视在率增益

#define C_UGainA	 			 0x17		//A相电压增益
#define C_UGainB	 			 0x18		//B相电压增益
#define C_UGainC	 			 0x19		//C相电压增益

#define C_IGainA	 			 0x1A		//A相电流增益
#define C_IGainB	 			 0x1B		//B相电流增益
#define C_IGainC	 			 0x1C		//C相电流增益

#define C_PhSregApq0	 		 0x0D		//A相大电流相位校正
#define C_PhSregBpq0	 		 0x0E		//B相大电流相位校正
#define C_PhSregCpq0	 		 0x0F		//C相大电流相位校正

#define C_PhSregApq1	 		 0x10		//A相中电流相位校正
#define C_PhSregBpq1	 		 0x11		//B相中电流相位校正
#define C_PhSregCpq1	 		 0x12		//C相中电流相位校正

#define C_PhSregApq2	 		 0x61		//A相小电流相位校正
#define C_PhSregBpq2	 		 0x62		//B相小电流相位校正
#define C_PhSregCpq2	 		 0x63		//C相小电流相位校正

#define C_rPa	 				 0x01		//A相有功功率
#define C_rPb	 				 0x02		//B相有功功率
#define C_rPc	 				 0x03		//C相有功功率
#define C_rPt	 				 0x04		//合相有功功率

#define C_UaRms	 				 0x0D		//A相电压有效值
#define C_UbRms	 				 0x0E		//B相电压有效值
#define C_UcRms	 				 0x0F		//C相电压有效值
#define C_UtRms	 				 0x2B		//合相电压有效值

#define C_IaRms	 				 0x10		//A相电流有效值
#define C_IbRms	 				 0x11		//B相电流有效值
#define C_IcRms	 				 0x12		//C相电流有效值
#define C_ItRms	 				 0x13		//合相电流有效值

#define C_Pfa	 				 0x14		//A相功率因数
#define C_Pfb	 				 0x15		//B相功率因数
#define C_Pfc	 				 0x16		//C相功率因数
#define C_Pft	 				 0x17		//合相功率因数

#define C_Freq	 				 0x1C		//线频率

#define C_Psign                  0x3D       ///功率反向寄存器
#define C_EmuState               0x2C      ///功率反向寄存器

#define  CAddr_EMU_CALPARA_Note    0x0C00u///三相表的校表数据保存在类EE中
	#define RegDataNum    3///每个寄存器数据长度
	
#define  CAddr_EMU_CALPARA_BAK_Note    0x0D00u////备份


/*----------------< 变量声明 >----------------------------------*/
typedef	struct{	/* 注意要和Dl_Cpu_Init表格顺序要一一对应 */
	ulong32		ulaCalPara[28];
	///相位区域0
	///相位区域1
	///起动功率阀值设置
	///HFCONST
	
	///A相有功功率增益
	///B
	///C
	///A相无功功率增益
	///B
	///C
	///A相视在功率增益
	///B
	///C
	///A相相位校正0
	///B
	///C
	///A相相位校正1
	///B
	///C
	///A相电压增益
	///B相电压增益
	///C相电压增益
	///A相电流增益
	///B相电流增益
	///C相电流增益
	///A相相位校正1
	///B相相位校正1
	///C相相位校正1
	ushort16	usCRC16;			///* 校验 *///
}TRIPEMU_CALPARA_Type;
#define	TRIPEMU_CALPARA_Type_LEN		sizeof( TRIPEMU_CALPARA_Type )

extern uchar8 xdata GA_EmuRegData[TRIPEMU_CALPARA_Type_LEN];
typedef	struct{
	ulong32     ulaKmsuip;///只存电流系数
// 	ulong32		ulKmsI;				///* 电流有效值系数 *///
	ushort16	usCRC16;			///* 校验 *///
}TRIPEMU_UIPKms_Type;
#define	TRIPEMU_UIPKms_Type_LEN		sizeof( TRIPEMU_UIPKms_Type )

typedef	struct{
	uchar8		ucCommDI1;			///* 对应DI1 *///
	uchar8		ucEmuAddr[3];			///* 对应地址 */
}EMU_COMM_TRIPCAL_TAB_Type;

typedef	struct{
	uchar8		ucCommDI1;			///* 对应DI1 *///
	uchar8		ucEmuAddr[4];			///* 对应地址 */带合相
}EMU_Read_TRIPCAL_TAB_Type;


/*----------------< 函数声明 >----------------------------------*/
extern void  ApiEMU_EMUInit();
extern uchar8 AppEMU_TripReadEmuReg( uchar8 v_ucChID );
extern void ApiEMU_CommEndCal( uchar8 v_ucChID );
extern uchar8 ApiEMU_CommErrCal( uchar8 v_ucChID );
extern void ApiEMU_CommStartCal(v_ucChID);
extern void AppEMU_TRipCommSetReg( uchar8 v_ucChID );
extern void AppEMU_WriteOneReg_MeterIC(uchar8 *P_Data,uchar8 V_RegAddr);
extern void AppEMU_WriteRegToEE(uchar8 *P_Data,uchar8 V_RegAddr);
extern void AppEMU_ReadOneReg_MeterIC(uchar8 V_usRegAddr, uchar8* P_Data,uchar8 V_MeaORCal);
extern void  ApiEMU_EMUParaCheck();
extern void ApiEMU_DisOrEnable(uchar8 v_ucWorkMode);
extern uchar8 ApiEMU_GetDirP(void);
extern uchar8 ApiEMU_UpdateUIP(void);
#endif


#endif
