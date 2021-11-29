/**
  ******************************************************************************
  * @file    fm32l0xx_btim.h
  * @author  FM385 Application Team
  * @version V1.0.0
  * @date    13-FEB-2017
  * @brief   This file contains all the functions prototypes for the RCC firmware library.  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FM32L0xx_BTIM_H
#define __FM32L0xx_BTIM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "FM32L0XX.h"
	 
/** @addtogroup FM385_StdPeriph_Driver
  * @{
  */

/** @addtogroup BTIM
  * @{
  */ 

/* Exported constants --------------------------------------------------------*/

/** @defgroup BTIM_Exported_Constants
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  BTIM Init Structure definition  
  */ 

typedef struct
{
  uint32_t RTCSEL1;            /* SLELECT RTC SOUCE 1 */
  uint32_t RTCSEL2;          	/* SLELECT RTC SOUCE 2 */
  uint32_t INSEL1;            	/* SLELECT INNER SOUCE 1 */
  uint32_t INSEL2;             /* SLELECT INNER SOUCE 2 */										   	
  uint32_t EXSEL1;							/* SLELECT EX SOUCE 1 */
	uint32_t EXSEL2;							/* SLELECT EX SOUCE 2 */
	uint32_t GRP1SEL;						/* SLELECT GROUP1 SOUCE */
	uint32_t GRP2SEL;						/* SLELECT GROUP2 SOUCE */
	uint32_t CAPSRC;							/* SLELECT CAPTURE SOUCE */
	uint32_t CNTSRC;							/* SLELECT COUNT SOUCE */
	uint32_t SRCSEL;            	/* SET 1 TO LOW COUNTER */
	uint32_t CNTHSEL;							/* SELECT H COUNT SOURCE */
} BTIM_SRCSelType;

typedef struct
{
  uint32_t CAPONCE;            /* 0-CONTINUOUS 1-ONCE */
  uint32_t CAPCLR;          	 	/* CLR AT CAPTURE */
  uint32_t CAPMOD;            	/* 0-CYCLE 1-PULSE */
} BTIM_CAPInitType;

typedef struct
{
  uint32_t DIREN;            	/* DIR SIGNAL ENABLE */
  uint32_t STDIR;          	 	/* SET DIR */
  uint32_t DIRPO;             	/* 1- REVERSE THE DIR SIGNAL*/										   	
} BTIM_DIRInitType;

typedef struct
{
  uint32_t OUTCNT;             /* SET OUTPUT PULSE WIDTH,0-FFF */										   	
  uint32_t OUTCLR;							/* SET OUTPUT TO 0 */
	uint32_t OUTINV;							/* SET OUTPUT SIGNAL REVERSE */
	uint32_t OUTMOD;							/* 0-PULSE 1-LEVEL */	
	uint32_t OUTSEL;							/* SELECT OUTPUT SOUCE */
	
} BTIM_OUTInitType;


typedef struct
{
//  BTIM_SRCSelType 		BTIM_CLK_SEL_SETTING;            		/* SLELECT CLK SOUCE */
//  BTIM_CAPInitType 		BTIM_CAPTUTE_SETTING;          	 	/* SLELECT CAPTURE SETTIG */
//  BTIM_DIRInitType 	  BTIM_DIR_SETTING;            	 	  /* SLELECT DIR SETTIG*/
//  BTIM_OUTInitType 		BTIM_OUTPUT_SETTING;             	/* SLELECT OUTPUT SETTIG*/	
	
  uint32_t PRESCALE;		
	uint32_t PRESET;		
	uint32_t LOADL;	
	uint32_t LOADH;	
	uint32_t CMPL;
	uint32_t CMPH;
	
	uint32_t MODE;
	uint32_t EDGESEL;			/* 0-POS 1-NEG */
	
} BTIM_InitType;


/**
* @}BTIM_BTxCR1
*/ 
  
/** @defgroup BTIM_BTxCR1_PMW 
  * @{
  */
#define BTIM_BTxCR1_PMW_Pos               								0                                             
#define BTIM_BTxCR1_PMW_Msk               								(0x01UL << BTIM_BTxCR1_PMW_Pos)  
#define BTIM_BTxCR1_PMW_OUTDISABLE       									((uint32_t)0x00000000)
#define BTIM_BTxCR1_PMW_OUTENABLE    		 									((uint32_t)0x00000001)

/** @defgroup BTIM_BTxCR1_CAPONCE
  * @{
  */
#define BTIM_BTxCR1_CAPONCE_Pos               						1                                            
#define BTIM_BTxCR1_CAPONCE_Msk               						(0x01UL << BTIM_BTxCR1_CAPONCE_Pos)
#define BTIM_BTxCR1_CAPONCE_CONTINU              					((uint32_t)0x00000000)
#define BTIM_BTxCR1_CAPONCE_SINGLE           							((uint32_t)0x00000002)

/** @defgroup BTIM_BTxCR1_CAPCLR
  * @{
  */  
#define BTIM_BTxCR1_CAPCLR_Pos 			              				2                                            
#define BTIM_BTxCR1_CAPCLR_Msk               							(0x01UL << BTIM_BTxCR1_CAPCLR_Pos) 
#define BTIM_BTxCR1_CAPCLR_NOTCLR              						((uint32_t)0x00000000)
#define BTIM_BTxCR1_CAPCLR_CLR                						((uint32_t)0x00000004)

/** @defgroup BTIM_BTxCR1_CAPMOD
  * @{
  */  
#define BTIM_BTxCR1_CAPMOD_Pos  		             					3                                            
#define BTIM_BTxCR1_CAPMOD_Msk               							(0x01UL << BTIM_BTxCR1_CAPMOD_Pos) 
#define BTIM_BTxCR1_CAPMOD_CYCLE                					((uint32_t)0x00000000)
#define BTIM_BTxCR1_CAPMOD_PULSE                					((uint32_t)0x01000008)

/** @defgroup BTIM_BTxCR1_EDGESEL
  * @{
  */
#define BTIM_BTxCR1_EDGESEL_Pos               						4                                            
#define BTIM_BTxCR1_EDGESEL_Msk               						(0x01UL << BTIM_BTxCR1_EDGESEL_Pos)  
#define BTIM_BTxCR1_EDGESEL_POS                						((uint32_t)0x00000000)
#define BTIM_BTxCR1_EDGESEL_NEG                						((uint32_t)0x00000010)

/** @defgroup BTIM_BTxCR1_MODE
  * @{
  */ 
#define BTIM_BTxCR1_MODE_Pos               								5                                            
#define BTIM_BTxCR1_MODE_Msk               								(0x01UL << BTIM_BTxCR1_MODE_Pos) 
#define BTIM_BTxCR1_MODE_8BIT_CNT            							((uint32_t)0x00000000)
#define BTIM_BTxCR1_MODE_16BIT_CAP             						((uint32_t)0x00000020)

/** @defgroup BTIM_BTxCR1_CLEN
  * @{
  */ 
#define BTIM_BTxCR1_CLEN_Pos               								6                                            
#define BTIM_BTxCR1_CLEN_Msk              								(0x01UL << BTIM_BTxCR1_CLEN_Pos) 
#define BTIM_BTxCR1_CLEN_DISABLE             							((uint32_t)0x00000000)
#define BTIM_BTxCR1_CLEN_ENABLE              							((uint32_t)0x00000040)


/** @defgroup BTIM_BTxCR1_CHEN
  * @{
  */  
#define BTIM_BTxCR1_CHEN_Pos               								7                                            
#define BTIM_BTxCR1_CHEN_Msk              								(0x01UL << BTIM_BTxCR1_CHEN_Pos) 
#define BTIM_BTxCR1_CHEN_DISABLE         									((uint32_t)0x00000000)
#define BTIM_BTxCR1_CHEN_ENABLE          									((uint32_t)0x00000080)


/**
  * @} BTIM_BTxCR2
  */ 
	
/** @defgroup BTIM_BTxCR2_DIRPO
  * @{
  */  
#define BTIM_BTxCR2_DIRPO_Pos               							0                                            
#define BTIM_BTxCR2_DIRPO_Msk              								(0x01UL << BTIM_BTxCR2_DIRPO_Pos) 
#define BTIM_BTxCR2_DIRPO_EXSIG_NOREVERSE    							((uint32_t)0x00000000)
#define BTIM_BTxCR2_DIRPO_EXSIG_REVERSE      							((uint32_t)0x00000001)

/** @defgroup BTIM_BTxCR2_SRCSEL
  * @{
  */  
#define BTIM_BTxCR2_SRCSEL_Pos               							1                                            
#define BTIM_BTxCR2_SRCSEL_Msk              							(0x01UL << BTIM_BTxCR2_SRCSEL_Pos) 
#define BTIM_BTxCR2_SRCSEL_EXSIG          								((uint32_t)0x00000000)
#define BTIM_BTxCR2_SRCSEL_ALWAYSON           						((uint32_t)0x00000002)

/** @defgroup BTIM_BTxCR2_STDIR
  * @{
  */  
#define BTIM_BTxCR2_STDIR_Pos               							2                                            
#define BTIM_BTxCR2_STDIR_Msk              								(0x01UL << BTIM_BTxCR2_STDIR_Pos) 
#define BTIM_BTxCR2_STDIR_CLRDIR           								((uint32_t)0x00000000)
#define BTIM_BTxCR2_STDIR_SETDIR            							((uint32_t)0x00000004)

/** @defgroup BTIM_BTxCR2_DIREN
  * @{
  */  
#define BTIM_BTxCR2_DIREN_Pos               							3                                            
#define BTIM_BTxCR2_DIREN_Msk              								(0x01UL << BTIM_BTxCR2_DIREN_Pos) 
#define BTIM_BTxCR2_DIREN_DISABLE          								((uint32_t)0x00000000)
#define BTIM_BTxCR2_DIREN_ENABLE           								((uint32_t)0x00000008)

/** @defgroup BTIM_BTxCR2_CNTHSEL
  * @{
  */  
#define BTIM_BTxCR2_CNTHSEL_Pos               						4                                            
#define BTIM_BTxCR2_CNTHSEL_Msk              							(0x03UL << BTIM_BTxCR2_CNTHSEL_Pos) 
#define BTIM_BTxCR2_CNTHSEL_CNTL          								((uint32_t)0x00000000)
#define BTIM_BTxCR2_CNTHSEL_CAPSRC	           						((uint32_t)0x00000010)
#define BTIM_BTxCR2_CNTHSEL_CNTSRC            						((uint32_t)0x00000020)

/** @defgroup BTIM_BTxCR2_SIG1SEL
  * @{
  */  
#define BTIM_BTxCR2_SIG1SEL_Pos               						6                                            
#define BTIM_BTxCR2_SIG1SEL_Msk              							(0x01UL << BTIM_BTxCR2_SIG1SEL_Pos) 
#define BTIM_BTxCR2_SIG1SEL_GROUP2	           						((uint32_t)0x00000000)
#define BTIM_BTxCR2_SIG1SEL_GROUP1            						((uint32_t)0x00000040)


/** @defgroup BTIM_BTxCR2_SIG2SEL
  * @{
  */  
#define BTIM_BTxCR2_SIG2SEL_Pos               						7                                            
#define BTIM_BTxCR2_SIG2SEL_Msk              							(0x01UL << BTIM_BTxCR2_SIG2SEL_Pos) 
#define BTIM_BTxCR2_SIG2SEL_GROUP1           							((uint32_t)0x00000000)
#define BTIM_BTxCR2_SIG2SEL_GROUP2            						((uint32_t)0x00000080)


/**
  * @} BTIM_BTxCFG1
  */ 
	
/** @defgroup BTIM_BTxCFG1_GRP1SEL
  * @{
  */  
#define BTIM_BTxCFG1_GRP1SEL_Pos               						0                                            
#define BTIM_BTxCFG1_GRP1SEL_Msk              						(0x03UL << BTIM_BTxCFG1_GRP1SEL_Pos) 
#define BTIM_BTxCFG1_GRP1SEL_APBCLK           						((uint32_t)0x00000000)
#define BTIM_BTxCFG1_GRP1SEL_RTCOUT1           						((uint32_t)0x00000001)
#define BTIM_BTxCFG1_GRP1SEL_IN_SIG1           						((uint32_t)0x00000002)
#define BTIM_BTxCFG1_GRP1SEL_EX_SIG1           						((uint32_t)0x00000003)

/** @defgroup BTIM_BTxCFG1_GRP2SEL
  * @{
  */  
#define BTIM_BTxCFG1_GRP2SEL_Pos               						2                                            
#define BTIM_BTxCFG1_GRP2SEL_Msk              						(0x03UL << BTIM_BTxCFG1_GRP2SEL_Pos) 
#define BTIM_BTxCFG1_GRP2SEL_APBCLK           						((uint32_t)0x00000000)
#define BTIM_BTxCFG1_GRP2SEL_RTCOUT2           						((uint32_t)0x00000004)
#define BTIM_BTxCFG1_GRP2SEL_IN_SIG2           						((uint32_t)0x00000008)
#define BTIM_BTxCFG1_GRP2SEL_EX_SIG2           						((uint32_t)0x0000000C)

/** @defgroup BTIM_BTxCFG1_RTCSEL1
  * @{
  */  
#define BTIM_BTxCFG1_RTCSEL1_Pos               						4                                            
#define BTIM_BTxCFG1_RTCSEL1_Msk              						(0x03UL << BTIM_BTxCFG1_RTCSEL1_Pos) 
#define BTIM_BTxCFG1_RTCSEL1_XTLF 	           						((uint32_t)0x00000000)
#define BTIM_BTxCFG1_RTCSEL1_RTCSEC           						((uint32_t)0x00000010)
#define BTIM_BTxCFG1_RTCSEL1_RTCMIN           						((uint32_t)0x00000020)
#define BTIM_BTxCFG1_RTCSEL1_LPTIM_OUT         						((uint32_t)0x00000030)

/** @defgroup BTIM_BTxCFG1_RTCSEL2
  * @{
  */  
#define BTIM_BTxCFG1_RTCSEL2_Pos               						6                                            
#define BTIM_BTxCFG1_RTCSEL2_Msk              						(0x03UL << BTIM_BTxCFG1_RTCSEL2_Pos) 
#define BTIM_BTxCFG1_RTCSEL2_XTLF   	        						((uint32_t)0x00000000)
#define BTIM_BTxCFG1_RTCSEL2_RTCSEC           						((uint32_t)0x00000040)
#define BTIM_BTxCFG1_RTCSEL2_RTCMIN            						((uint32_t)0x00000080)
#define BTIM_BTxCFG1_RTCSEL2_LPTIM_OUT           					((uint32_t)0x000000C0)

/**
  * @} BTIM_BTxCFG2
  */ 
	
/** @defgroup BTIM_BTxCFG2_INSEL1
  * @{
  */  
#define BTIM_BTxCFG2_INSEL1_Pos               						0                                            
#define BTIM_BTxCFG2_INSEL1_Msk              							(0x03UL << BTIM_BTxCFG2_INSEL1_Pos) 

#define BTIM_BT1CFG2_INSEL1_UART_RX0          						((uint32_t)0x00000000)
#define BTIM_BT1CFG2_INSEL1_UART_RX1           						((uint32_t)0x00000001)
#define BTIM_BT1CFG2_INSEL1_UART_RX2           						((uint32_t)0x00000002)
#define BTIM_BT1CFG2_INSEL1_RCLP            							((uint32_t)0x00000003)

#define BTIM_BT2CFG2_INSEL1_UART_RX0          						((uint32_t)0x00000000)
#define BTIM_BT2CFG2_INSEL1_UART_RX1           						((uint32_t)0x00000001)
#define BTIM_BT2CFG2_INSEL1_UART_RX2           						((uint32_t)0x00000002)
#define BTIM_BT2CFG2_INSEL1_RCLP            							((uint32_t)0x00000003)

/** @defgroup BTIM_BTxCFG2_INSEL2
  * @{
  */  
#define BTIM_BTxCFG2_INSEL2_Pos               						2                                            
#define BTIM_BTxCFG2_INSEL2_Msk              							(0x03UL << BTIM_BTxCFG2_INSEL2_Pos)

#define BTIM_BT1CFG2_INSEL2_UART_RX3           						((uint32_t)0x00000000)
#define BTIM_BT1CFG2_INSEL2_UART_RX4           						((uint32_t)0x00000004)
#define BTIM_BT1CFG2_INSEL2_UART_RX5           						((uint32_t)0x00000008)
#define BTIM_BT1CFG2_INSEL2_RCLP		           						((uint32_t)0x0000000C)

#define BTIM_BT2CFG2_INSEL2_UART_RX3           						((uint32_t)0x00000000)
#define BTIM_BT2CFG2_INSEL2_UART_RX4           						((uint32_t)0x00000004)
#define BTIM_BT2CFG2_INSEL2_UART_RX5           						((uint32_t)0x00000008)
#define BTIM_BT2CFG2_INSEL2_BT1_OUT	           						((uint32_t)0x0000000C)

/** @defgroup BTIM_BTxCFG2_EXSEL1
  * @{
  */  
#define BTIM_BTxCFG2_EXSEL1_Pos               						4                                            
#define BTIM_BTxCFG2_EXSEL1_Msk              							(0x03UL << BTIM_BTxCFG2_EXSEL1_Pos) 

#define BTIM_BT1CFG2_EXSEL1_BT1_IN0 	           					((uint32_t)0x00000000)
#define BTIM_BT1CFG2_EXSEL1_BT1_IN1           						((uint32_t)0x00000010)
#define BTIM_BT1CFG2_EXSEL1_BT1_IN2          							((uint32_t)0x00000020)
#define BTIM_BT1CFG2_EXSEL1_BT1_IN3         							((uint32_t)0x00000030)

#define BTIM_BT2CFG2_EXSEL1_BT2_IN0 	           					((uint32_t)0x00000000)
#define BTIM_BT2CFG2_EXSEL1_BT2_IN1           						((uint32_t)0x00000010)
#define BTIM_BT2CFG2_EXSEL1_BT2_IN2          							((uint32_t)0x00000020)
#define BTIM_BT2CFG2_EXSEL1_BT2_IN3         							((uint32_t)0x00000030)

/** @defgroup BTIM_BTxCFG2_EXSEL2
  * @{
  */  
#define BTIM_BTxCFG2_EXSEL2_Pos               						6                                            
#define BTIM_BTxCFG2_EXSEL2_Msk              							(0x03UL << BTIM_BTxCFG2_EXSEL2_Pos) 

#define BTIM_BT1CFG2_EXSEL2_BT1_IN0   	      						((uint32_t)0x00000000)
#define BTIM_BT1CFG2_EXSEL2_BT1_IN1           						((uint32_t)0x00000040)
#define BTIM_BT1CFG2_EXSEL2_BT1_IN2            						((uint32_t)0x00000080)
#define BTIM_BT1CFG2_EXSEL2_BT1_IN3           						((uint32_t)0x000000C0)

#define BTIM_BT2CFG2_EXSEL2_BT2_IN0   	      						((uint32_t)0x00000000)
#define BTIM_BT2CFG2_EXSEL2_BT2_IN1           						((uint32_t)0x00000040)
#define BTIM_BT2CFG2_EXSEL2_BT2_IN2            						((uint32_t)0x00000080)
#define BTIM_BT2CFG2_EXSEL2_BT2_IN3           						((uint32_t)0x000000C0)

/**
  * @} BTIM_BTxLOADCR
  */ 
	
/** @defgroup BTIM_BTxLOADCR_LLEN
  * @{
  */  
#define BTIM_BTxLOADCR_LLEN_Pos               						0                                            
#define BTIM_BTxLOADCR_LLEN_Msk              							(0x01UL << BTIM_BTxLOADCR_LLEN_Pos) 
#define BTIM_BTxLOADCR_LLEN_SET			           						((uint32_t)0x00000001)


/** @defgroup BTIM_BTxLOADCR_LHEN
  * @{
  */  
#define BTIM_BTxLOADCR_LHEN_Pos               						4                                            
#define BTIM_BTxLOADCR_LHEN_Msk              							(0x01UL << BTIM_BTxLOADCR_LHEN_Pos) 
#define BTIM_BTxLOADCR_LHEN_SET			           						((uint32_t)0x00000010)

/**
  * @} BTIM_BTxOCR
  */ 
	
/** @defgroup BTIM_BTxOCR_OUTSEL
  * @{
  */  
#define BTIM_BTxOCR_OUTSEL_Pos               							0                                            
#define BTIM_BTxOCR_OUTSEL_Msk              							(0x03UL << BTIM_BTxOCR_OUTSEL_Pos) 
#define BTIM_BTxOCR_OUTSEL_HCMPOUT           							((uint32_t)0x00000000)
#define BTIM_BTxOCR_OUTSEL_LCMPOUT           							((uint32_t)0x00000001)
#define BTIM_BTxOCR_OUTSEL_GROUP1           							((uint32_t)0x00000002)
#define BTIM_BTxOCR_OUTSEL_GROUP2          								((uint32_t)0x00000003)

/** @defgroup BTIM_BTxOCR_OUTMOD
  * @{
  */  
#define BTIM_BTxOCR_OUTMOD_Pos               							2                                            
#define BTIM_BTxOCR_OUTMOD_Msk              							(0x01UL << BTIM_BTxOCR_OUTMOD_Pos) 
#define BTIM_BTxOCR_OUTMOD_PULSE           								((uint32_t)0x00000000)
#define BTIM_BTxOCR_OUTMOD_REVERSE           							((uint32_t)0x00000004)


/** @defgroup BTIM_BTxOCR_OUTINV
  * @{
  */  
#define BTIM_BTxOCR_OUTINV_Pos               							3                                            
#define BTIM_BTxOCR_OUTINV_Msk              							(0x01UL << BTIM_BTxOCR_OUTINV_Pos) 
#define BTIM_BTxOCR_OUTINV_NORMAL 	           						((uint32_t)0x00000000)
#define BTIM_BTxOCR_OUTINV_REVERSE           							((uint32_t)0x00000008)


/** @defgroup BTIM_BTxOCR_OUTCLR
  * @{
  */  
#define BTIM_BTxOCR_OUTCLR_Pos               							4                                            
#define BTIM_BTxOCR_OUTCLR_Msk              							(0x01UL << BTIM_BTxOCR_OUTCLR_Pos) 
#define BTIM_BTxOCR_OUTCLR_CLR   	        								((uint32_t)0x00000010)

/**
  * @} BTIM_BTxIE
  */ 
	
/** @defgroup BTIM_BTxIE_CAPIE
  * @{
  */  
#define BTIM_BTxIE_CAPIE_Pos               								0                                            
#define BTIM_BTxIE_CAPIE_Msk              								(0x01UL << BTIM_BTxIE_CAPIE_Pos) 
#define BTIM_BTxIE_CAPIE_DISABLE           								((uint32_t)0x00000000)
#define BTIM_BTxIE_CAPIE_ENABLE           								((uint32_t)0x00000001)


/** @defgroup BTIM_BTxIE_OVLIE
  * @{
  */  
#define BTIM_BTxIE_OVLIE_Pos               								1                                            
#define BTIM_BTxIE_OVLIE_Msk              								(0x01UL << BTIM_BTxIE_OVLIE_Pos) 
#define BTIM_BTxIE_OVLIE_DISABLE           								((uint32_t)0x00000000)
#define BTIM_BTxIE_OVLIE_ENABLE           								((uint32_t)0x00000002)

/** @defgroup BTIM_BTxIE_OVHIE
  * @{
  */  
#define BTIM_BTxIE_OVHIE_Pos               								2                                            
#define BTIM_BTxIE_OVHIE_Msk              								(0x01UL << BTIM_BTxIE_OVHIE_Pos) 
#define BTIM_BTxIE_OVHIE_DISABLE           								((uint32_t)0x00000000)
#define BTIM_BTxIE_OVHIE_ENABLE           								((uint32_t)0x00000004)

/** @defgroup BTIM_BTxIE_CMPLIE
  * @{
  */  
#define BTIM_BTxIE_CMPLIE_Pos               							3                                            
#define BTIM_BTxIE_CMPLIE_Msk              								(0x01UL << BTIM_BTxIE_CMPLIE_Pos) 
#define BTIM_BTxIE_CMPLIE_DISABLE           							((uint32_t)0x00000000)
#define BTIM_BTxIE_CMPLIE_ENABLE           								((uint32_t)0x00000008)

/** @defgroup BTIM_BTxIE_CMPHIE
  * @{
  */  
#define BTIM_BTxIE_CMPHIE_Pos               							4                                            
#define BTIM_BTxIE_CMPHIE_Msk              								(0x01UL << BTIM_BTxIE_CMPHIE_Pos) 
#define BTIM_BTxIE_CMPHIE_DISABLE           							((uint32_t)0x00000000)
#define BTIM_BTxIE_CMPHIE_ENABLE           								((uint32_t)0x00000010)

/**
  * @} BTIM_BTxIF
  */ 
	
/** @defgroup BTIM_BTxIF_CAPIF
  * @{
  */  
#define BTIM_BTxIF_CAPIF_Pos               								0                                            
#define BTIM_BTxIF_CAPIF_Msk              								(0x01UL << BTIM_BTxIF_CAPIF) 
#define BTIM_BTxIF_CAPIF_RESET           									((uint32_t)0x00000000)
#define BTIM_BTxIF_CAPIF_SET           										((uint32_t)0x00000001)


/** @defgroup BTIM_BTxIF_OVLIF
  * @{
  */  
#define BTIM_BTxIF_OVLIF_Pos               								1                                            
#define BTIM_BTxIF_OVLIF_Msk              								(0x01UL << BTIM_BTxIE_OVLIE_Pos) 
#define BTIM_BTxIF_OVLIF_RESET           									((uint32_t)0x00000000)
#define BTIM_BTxIF_OVLIF_SET           										((uint32_t)0x00000002)

/** @defgroup BTIM_BTxIF_OVHIF
  * @{
  */  
#define BTIM_BTxIF_OVHIF_Pos               								2                                            
#define BTIM_BTxIF_OVHIF_Msk              								(0x01UL << BTIM_BTxIE_OVHIE_Pos) 
#define BTIM_BTxIF_OVHIF_RESET           									((uint32_t)0x00000000)
#define BTIM_BTxIF_OVHIF_SET           										((uint32_t)0x00000004)

/** @defgroup BTIM_BTxIF_CMPLIF
  * @{
  */  
#define BTIM_BTxIF_CMPLIF_Pos               							3                                            
#define BTIM_BTxIF_CMPLIF_Msk              								(0x01UL << BTIM_BTxIE_CMPLIE_Pos) 
#define BTIM_BTxIF_CMPLIF_RESET           								((uint32_t)0x00000000)
#define BTIM_BTxIF_CMPLIF_SET           									((uint32_t)0x00000008)

/** @defgroup BTIM_BTxIF_CMPHIF
  * @{
  */  
#define BTIM_BTxIF_CMPHIF_Pos               							4                                            
#define BTIM_BTxIF_CMPHIF_Msk              								(0x01UL << BTIM_BTxIE_CMPHIE_Pos) 
#define BTIM_BTxIF_CMPHIF_RESET           								((uint32_t)0x00000000)
#define BTIM_BTxIF_CMPHIF_SET           									((uint32_t)0x00000010)

/** @defgroup BTIM_BTxIF_EDGESTA
  * @{
  */  
#define BTIM_BTxIF_EDGESTA_Pos               							5                                            
#define BTIM_BTxIF_EDGESTA_Msk              							(0x01UL << BTIM_BTxIE_CMPHIE_Pos) 
#define BTIM_BTxIF_EDGESTA_POS           									((uint32_t)0x00000000)
#define BTIM_BTxIF_EDGESTA_NEG           									((uint32_t)0x00000010)

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/ 
extern void BTIM_Init_Clk(BTIMER_Type* BTimerX,BTIM_SRCSelType* BTIM_SRCSelStruct);
extern void BTIM_Init_Cap(BTIMER_Type* BTimerX,BTIM_CAPInitType* BTIM_CAPStruct);
extern void BTIM_Init_Dir(BTIMER_Type* BTimerX,BTIM_DIRInitType* BTIM_DIRStruct);
extern void BTIM_Init_Out(BTIMER_Type* BTimerX,BTIM_OUTInitType* BTIM_OUTStruct);
extern void BTIM_Init(BTIMER_Type* BTimerX,BTIM_InitType* BTIM_InitStruct);

extern void BTIM_PRESET(BTIMER_Type* BTimerX,uint32_t BTIM_PRESETBit);	
extern void BTIM_Enable(BTIMER_Type* BTimerX,uint32_t BTIM_ENBit);
extern void BTIM_Disable(BTIMER_Type* BTimerX,uint32_t BTIM_DISENBit);

extern void BTIM_ITEnable(BTIMER_Type* BTimerX,uint16_t EnableBit);
extern void BTIM_ITDisable(BTIMER_Type* BTimerX,uint16_t DisableBit);
extern ITStatus BTIM_GetFlagSta(BTIMER_Type* BTimerX,uint16_t FlagBit);
extern void BTIM_ClrITStatus(BTIMER_Type* BTimerX,uint16_t FlagBit);


#ifdef __cplusplus
}
#endif

#endif /* __FM385_LPTIM_H */



/************************ (C) COPYRIGHT FMSHelectronics *****END OF FILE****/



