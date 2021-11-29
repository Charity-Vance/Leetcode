/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    TripleDES.H                                                                          
**** Brief:       3Des算法加解密，算法参考校园表算法，涉及到大小端的有所调整                                                                      
**** Author:      peter.he@chint.com                                                                 
**** Version:     V1.0                                                                               
**** Date:        2016-7-14                                                                          
****                                                                                                 
**** note:修改历史记录列表，每条修改记录应包括修改日期、修改者                                          
**** 1.  Author:                                                                                     
****     Version:                                                                                    
****     Date :                                                                                      
**** 2.  Author:                                                                                     
****     Version:                                                                                       
****     Date:
****                                                                                        
****  addtogroup:                                                             
**********************************************************************************************************/

#ifndef   TRIPLEDES_H
#define   TRIPLEDES_H

/*-------------------------------- H文件使用说明 -------------------------------------------------------*/
/*
 *  该文件宏定义的前缀为:
 *
 */

 
/*----------------< 包含文件 >----------------------------------*/


/*----------------< 宏定义区 >----------------------------------*/
#define		RIGHTSHIFT					1		///*  右移 *///
#define		LEFTSHIFT					2		///*  左移 *///
#define		DECRYPTION 					1		///* 解密*///
#define		ENCRYPTION					2		///*  加密 */// 

#define 	C_VirtualEsamNum	24				///* ESAM类型*///
#define 	C_E2Key				0x01            ///* 从E2中读取的密钥.							*///
#define 	C_DisKey			0x02            ///* E2密钥分散后得到的密钥	                	*///
#define 	C_TempKey			0x03            ///* 上位机传进来的密钥（直接使用传进来的密钥）	*///
#define 	C_ComplexKey		0x04            ///* 先将E2密钥分散，得到密钥后进行解密（两步）	*///
#define 	C_RandNum			0x05            ///* 加密随机数的KEY	*///
#define 	C_3DES				0x01            ///* 3DES操作			*///
#define 	C_MAC				0x02            ///* 计算MAC操作		*///
#define 	C_EsamOK			0x0000          ///* 计算MAC操作		*///
#define 	C_EsamErr			0x0001          ///* 计算MAC操作		*///
#define		C_KeyNum00			00				///* 00号密钥  *///
#define		C_KeyNum01			01				///* 01号密钥  *///
#define		C_KeyNumTp			06				///* 临时密钥 *///

#define 	C_9000Num  				  0x9000    	  ///* ESAM返回值*///
#define 	C_6108Num  				  0x6108    	  ///* ESAM返回值*///
/*----------------< 变量声明 >----------------------------------*/


/*----------------< 函数声明 >----------------------------------*/
extern uchar8 Data_MAC( uchar8 *P_ucData, uchar8 V_ucLen, uchar8 *P_ucRand, uchar8 V_ucType );
extern uchar8 TripleDES_DeOrEncryption(uchar8 V_ucKeyNum, uchar8 *P_ucData, uchar8 V_ucLen); 

extern void DES_PC_1(uchar8 *P_ucSorceData);
extern void DES_IP(uchar8 *P_ucSorceData);
extern uchar8 DES_ReplaceMent(uchar8 *P_ucSData,uchar8 V_ucRepMode);
extern void DES_Transposition(uchar8 *P_ucSorceData, uchar8 *P_ucLocattion, uchar8 *P_ucValue, uchar8	V_ucOutLen);
extern void DES_CycLRShifting(uchar8 *P_ucData, uchar8 V_ucMode);
extern void DES_IP_1(uchar8 *P_ucSorceData);
extern void DES_F(uchar8 *P_ucData, uchar8 *P_Key);
extern uchar8 Data_MAC( uchar8 *P_ucData, uchar8 V_ucLen, uchar8 *P_ucRand, uchar8 V_ucType );
extern uchar8 TripleDES_DeOrEncryption(uchar8 V_ucKeyNum, uchar8 *P_ucData, uchar8 V_ucLen);

extern uchar8 Data_MAC( uchar8 *P_ucData, uchar8 V_ucLen, uchar8 *P_ucRand, uchar8 V_ucType );



#endif
