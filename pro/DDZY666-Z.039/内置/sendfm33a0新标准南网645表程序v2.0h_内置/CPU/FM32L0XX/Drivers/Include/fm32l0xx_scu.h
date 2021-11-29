/**
  ******************************************************************************
  * @file    fm32l0xx_scu.h
  * @author  FM385 Application Team
  * @version V1.0.0
  * @date    13-MARCH-2017
  * @brief   This file contains all the functions prototypes for the SCU & DCU firmware library.  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FM32L0xx_SCU_H
#define __FM32L0xx_SCU_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "FM32L0XX.h"
	 
/** @addtogroup FM385_StdPeriph_Driver
  * @{
  */

/** @addtogroup SCU
  * @{
  */ 

/* Exported constants --------------------------------------------------------*/

/** @defgroup SCU_Exported_Constants
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  SCU Init Structure definition  
  */ 



/**
* @}SCU_SYSCON
*/ 
  
/** @defgroup SCU_SYSCON_MODE
  * @{
  */
#define SCU_SYSCON_MODE_Pos               								0                                             
#define SCU_SYSCON_MODE_Msk               								(0x03UL << SCU_SYSCON_MODE_Pos)  
#define SCU_SYSCON_MODE_User0			       									((uint32_t)0x00000000)
#define SCU_SYSCON_MODE_Manu		    		 									((uint32_t)0x00000001)
#define SCU_SYSCON_MODE_User			       									((uint32_t)0x00000002)
#define SCU_SYSCON_MODE_Org		    		 										((uint32_t)0x00000003)

/** @defgroup SCU_SYSCON_FLSCFG
  * @{
  */
#define SCU_SYSCON_FLSCFG_Pos               							2                                             
#define SCU_SYSCON_FLSCFG_Msk               							(0x03UL << SCU_SYSCON_FLSCFG_Pos)  
#define SCU_SYSCON_FLSCFG_512k			       								((uint32_t)0x00000000)
#define SCU_SYSCON_FLSCFG_384k		    		 								((uint32_t)0x00000004)
#define SCU_SYSCON_FLSCFG_256k			       								((uint32_t)0x00000008)
#define SCU_SYSCON_FLSCFG_192k	    		 									((uint32_t)0x0000000C)

/** @defgroup SCU_SYSCON_RAMCFG
  * @{
  */
#define SCU_SYSCON_RAMCFG_Pos               							4                                             
#define SCU_SYSCON_RAMCFG_Msk               							(0x03UL << SCU_SYSCON_RAMCFG_Pos)  
#define SCU_SYSCON_RAMCFG_64k			       									((uint32_t)0x00000000)
#define SCU_SYSCON_RAMCFG_48k		    		 									((uint32_t)0x00000010)
#define SCU_SYSCON_RAMCFG_32k			       									((uint32_t)0x00000020)
#define SCU_SYSCON_RAMCFG_16k	    		 										((uint32_t)0x00000030)

/** @defgroup SCU_SYSCON_CRYSLESS
  * @{
  */
#define SCU_SYSCON_CRYSLESS_Pos              							6                                             
#define SCU_SYSCON_CRYSLESS_Msk              							(0x01UL << SCU_SYSCON_CRYSLESS_Pos)  
#define SCU_SYSCON_CRYSLESS_CLR		     										((uint32_t)0x00000000)
#define SCU_SYSCON_CRYSLESS_SET		 												((uint32_t)0x00000040)
	
/** @defgroup SCU_SYSCON_CRYSLESS_B
  * @{
  */
#define SCU_SYSCON_CRYSLESS_B_Pos            							7                                             
#define SCU_SYSCON_CRYSLESS_B_Msk            							(0x01UL << SCU_SYSCON_CRYSLESS_B_Pos)  
#define SCU_SYSCON_CRYSLESS_B_CLR	    										((uint32_t)0x00000000)
#define SCU_SYSCON_CRYSLESS_B_SET													((uint32_t)0x00000080)

/** @defgroup SCU_SYSCON_RDPROTFAIL
  * @{
  */
#define SCU_SYSCON_RDPROTFAIL_Pos              						30                                             
#define SCU_SYSCON_RDPROTFAIL_Msk              						(0x01UL << SCU_SYSCON_RDPROTFAIL_Pos)  
#define SCU_SYSCON_RDPROTFAIL_PASS	     									((uint32_t)0x00000000)
#define SCU_SYSCON_RDPROTFAIL_FAIL	 											((uint32_t)0x40000000)
	
/** @defgroup SCU_SYSCON_VERIFAIL
  * @{
  */
#define SCU_SYSCON_VERIFAIL_Pos            								31                                             
#define SCU_SYSCON_VERIFAIL_Msk            								(0x01UL << SCU_SYSCON_VERIFAIL_Pos)  
#define SCU_SYSCON_VERIFAIL_CLR	    											((uint32_t)0x00000000)
#define SCU_SYSCON_VERIFAIL_SET														((uint32_t)0x80000000)

/**
* @}SCU_DBGCFG
*/ 
  
/** @defgroup SCU_DBGCFG_IWDT_STOP
  * @{
  */
#define SCU_DBGCFG_IWDT_STOP_Pos               						0                                             
#define SCU_DBGCFG_IWDT_STOP_Msk               						(0x01UL << SCU_DBGCFG_IWDT_STOP_Pos)  
#define SCU_DBGCFG_IWDT_STOP_Run			       							((uint32_t)0x00000000)
#define SCU_DBGCFG_IWDT_STOP_Stop		    		 							((uint32_t)0x00000001)

/** @defgroup SCU_DBGCFG_WWDT_STOP
  * @{
  */
#define SCU_DBGCFG_WWDT_STOP_Pos               						1                                             
#define SCU_DBGCFG_WWDT_STOP_Msk               						(0x01UL << SCU_DBGCFG_WWDT_STOP_Pos)  
#define SCU_DBGCFG_WWDT_STOP_Run			       							((uint32_t)0x00000000)
#define SCU_DBGCFG_WWDT_STOP_Stop		    		 							((uint32_t)0x00000002)

/** @defgroup SCU_DBGCFG_BT1_STOP
  * @{
  */
#define SCU_DBGCFG_BT1_STOP_Pos               						8                                             
#define SCU_DBGCFG_BT1_STOP_Msk               						(0x01UL << SCU_DBGCFG_BT1_STOP_Pos)  
#define SCU_DBGCFG_BT1_STOP_Run			       								((uint32_t)0x00000000)
#define SCU_DBGCFG_BT1_STOP_Stop		    		 							((uint32_t)0x00000100)

/** @defgroup SCU_DBGCFG_BT2_STOP
  * @{
  */
#define SCU_DBGCFG_BT2_STOP_Pos               						9                                             
#define SCU_DBGCFG_BT2_STOP_Msk               						(0x01UL << SCU_DBGCFG_BT2_STOP_Pos)  
#define SCU_DBGCFG_BT2_STOP_Run			       								((uint32_t)0x00000000)
#define SCU_DBGCFG_BT2_STOP_Stop		    		 							((uint32_t)0x00000200)

/** @defgroup SCU_DBGCFG_ET1_STOP
  * @{
  */
#define SCU_DBGCFG_ET1_STOP_Pos               						10                                             
#define SCU_DBGCFG_ET1_STOP_Msk               						(0x01UL << SCU_DBGCFG_ET1_STOP_Pos)  
#define SCU_DBGCFG_ET1_STOP_Run			       								((uint32_t)0x00000000)
#define SCU_DBGCFG_ET1_STOP_Stop		    		 							((uint32_t)0x00000400)

/** @defgroup SCU_DBGCFG_ET2_STOP
  * @{
  */
#define SCU_DBGCFG_ET2_STOP_Pos               						11                                             
#define SCU_DBGCFG_ET2_STOP_Msk               						(0x01UL << SCU_DBGCFG_ET2_STOP_Pos)  
#define SCU_DBGCFG_ET2_STOP_Run			       								((uint32_t)0x00000000)
#define SCU_DBGCFG_ET2_STOP_Stop		    		 							((uint32_t)0x00000800)

/** @defgroup SCU_DBGCFG_ET3_STOP
  * @{
  */
#define SCU_DBGCFG_ET3_STOP_Pos               						12                                             
#define SCU_DBGCFG_ET3_STOP_Msk               						(0x01UL << SCU_DBGCFG_ET3_STOP_Pos)  
#define SCU_DBGCFG_ET3_STOP_Run			       								((uint32_t)0x00000000)
#define SCU_DBGCFG_ET3_STOP_Stop		    		 							((uint32_t)0x00001000)

/** @defgroup SCU_DBGCFG_ET4_STOP
  * @{
  */
#define SCU_DBGCFG_ET4_STOP_Pos               						13                                             
#define SCU_DBGCFG_ET4_STOP_Msk               						(0x01UL << SCU_DBGCFG_ET4_STOP_Pos)  
#define SCU_DBGCFG_ET4_STOP_Run			       								((uint32_t)0x00000000)
#define SCU_DBGCFG_ET4_STOP_Stop		    		 							((uint32_t)0x00002000)


/**
* @}SCU_HDFFLAG
*/ 

/** @defgroup SCU_HDFFLAG_HDF_REQUEST_FLAG
  * @{
  */
#define SCU_HDFFLAG_HDF_REQUEST_FLAG_Pos           				0                                             
#define SCU_HDFFLAG_HDF_REQUEST_FLAG_Msk           				(0x01UL << SCU_HDFFLAG_HDF_REQUEST_FLAG_Pos)  
#define SCU_HDFFLAG_HDF_REQUEST_FLAG_Clr	      					((uint32_t)0x00000000)
#define SCU_HDFFLAG_HDF_REQUEST_FLAG_Set		 		 					((uint32_t)0x00000001)

/** @defgroup SCU_HDFFLAG_SPECIAL_OP_FLAG
  * @{
  */
#define SCU_HDFFLAG_SPECIAL_OP_FLAG_Pos           				1                                             
#define SCU_HDFFLAG_SPECIAL_OP_FLAG_Msk           				(0x01UL << SCU_HDFFLAG_SPECIAL_OP_FLAG_Pos)  
#define SCU_HDFFLAG_SPECIAL_OP_FLAG_Clr	      						((uint32_t)0x00000000)
#define SCU_HDFFLAG_SPECIAL_OP_FLAG_Set		 		 						((uint32_t)0x00000002)

/** @defgroup SCU_HDFFLAG_TBIT_FLAG
  * @{
  */
#define SCU_HDFFLAG_TBIT_FLAG_Pos           							2                                             
#define SCU_HDFFLAG_TBIT_FLAG_Msk           							(0x01UL << SCU_HDFFLAG_TBIT_FLAG_Pos)  
#define SCU_HDFFLAG_TBIT_FLAG_Thumb	      								((uint32_t)0x00000000)
#define SCU_HDFFLAG_TBIT_FLAG_ARM		 		 									((uint32_t)0x00000004)

/** @defgroup SCU_HDFFLAG_BKPT_FLAG
  * @{
  */
#define SCU_HDFFLAG_BKPT_FLAG_Pos           							3                                             
#define SCU_HDFFLAG_BKPT_FLAG_Msk           							(0x01UL << SCU_HDFFLAG_BKPT_FLAG_Pos)  
#define SCU_HDFFLAG_BKPT_FLAG_Clr	      									((uint32_t)0x00000000)
#define SCU_HDFFLAG_BKPT_FLAG_Set	 		 										((uint32_t)0x00000008)

/** @defgroup SCU_HDFFLAG_SVCUNDEF_FLAG
  * @{
  */
#define SCU_HDFFLAG_SVCUNDEF_FLAG_Pos           					4                                             
#define SCU_HDFFLAG_SVCUNDEF_FLAG_Msk           					(0x01UL << SCU_HDFFLAG_SVCUNDEF_FLAG_Pos)  
#define SCU_HDFFLAG_SVCUNDEF_FLAG_Clr	      							((uint32_t)0x00000000)
#define SCU_HDFFLAG_SVCUNDEF_FLAG_Set	 		 								((uint32_t)0x00000010)

/** @defgroup SCU_HDFFLAG_DABORT_RESP_FLAG
  * @{
  */
#define SCU_HDFFLAG_DABORT_RESP_FLAG_Pos           				5                                             
#define SCU_HDFFLAG_DABORT_RESP_FLAG_Msk           				(0x01UL << SCU_HDFFLAG_DABORT_RESP_FLAG_Pos)  
#define SCU_HDFFLAG_DABORT_RESP_FLAG_Clr	      					((uint32_t)0x00000000)
#define SCU_HDFFLAG_DABORT_RESP_FLAG_Set	 		 						((uint32_t)0x00000020)

/** @defgroup SCU_HDFFLAG_DABORT_ADDR_FLAG
  * @{
  */
#define SCU_HDFFLAG_DABORT_ADDR_FLAG_Pos           				6                                             
#define SCU_HDFFLAG_DABORT_ADDR_FLAG_Msk           				(0x01UL << SCU_HDFFLAG_DABORT_ADDR_FLAG_Pos)  
#define SCU_HDFFLAG_DABORT_ADDR_FLAG_Clr	      					((uint32_t)0x00000000)
#define SCU_HDFFLAG_DABORT_ADDR_FLAG_Set	 		 						((uint32_t)0x00000040)

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/ 
extern FlagStatus SCU_Get_VERIFAIL(void);
extern void SCU_Set_DBGCFG(uint32_t set_bit);
extern void SCU_Clr_DBGCFG(uint32_t clr_bit);


#ifdef __cplusplus
}
#endif

#endif /* __FM385_LPTIM_H */



/************************ (C) COPYRIGHT FMSHelectronics *****END OF FILE****/



