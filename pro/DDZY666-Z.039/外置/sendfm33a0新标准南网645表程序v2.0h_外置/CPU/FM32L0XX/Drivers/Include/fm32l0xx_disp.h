/**
  ******************************************************************************
  * @file    fm32l0xx_disp.h
  * @author  FM385 Application Team
  * @version V1.0.0
  * @date    8-MAR-2017
  * @brief   This file contains all the functions prototypes for the DISP firmware library.  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FM32L0xx_DISP_H
#define __FM32L0xx_DISP_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "FM32L0XX.h"
	 
/** @addtogroup FM385_StdPeriph_Driver
  * @{
  */

/** @addtogroup DISP
  * @{
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup DISP_Exported_Constants
  * @{
  */
  
	 
/* Exported types ------------------------------------------------------------*/


//typedef enum {
//	SEGEN0 = 0,	SEGEN1	=	1,	SEGEN2 = 2,	SEGEN3 = 3,	SEGEN4 = 4,	SEGEN5 = 5,
//	SEGEN6 = 6,	SEGEN7 = 7,	SEGEN8 = 8,	SEGEN9 = 9,	SEGEN10 = 10,	SEGEN11 = 11,
//	SEGEN12 = 12,	SEGEN13 = 13,	SEGEN14 = 14,	SEGEN5 = 15,	SEGEN16 = 16,
//	SEGEN7 = 17,	SEGEN18 = 18,	SEGEN19 = 19,	SEGEN20 = 20,	SEGEN1 = 21,	
//	SEGEN22 = 22,	SEGEN23 = 23,	SEGEN4 = 24,	SEGEN5 = 25,	SEGEN26 = 26,	SEGEN27 = 27,
//	SEGEN28 = 28,		SEGEN29 = 29,	SEGEN0 = 30,	SEGEN1 = 31,	
//}DISP_SEG_EN0;

//typedef enum {
//	SEGEN0 = 0,	SEGEN1	=	1,	SEGEN2 = 2,	SEGEN3 = 3,	SEGEN4 = 4,	SEGEN5 = 5,
//	SEGEN6 = 6,	SEGEN7 = 7,	SEGEN8 = 8,	SEGEN9 = 9,	SEGEN10 = 10,	SEGEN11 = 11,
//}DISP_SEG_EN1;





/**
* @}DISP_DISPCTRL
*/ 
  
/** @defgroup DISP_DISPCTRL_DISPMD 
  * @{
  */
#define DISP_DISPCTRL_DISPMD_Pos		               			0                                             
#define DISP_DISPCTRL_DISPMD_Msk               					(0x01UL << DISP_DISPCTRL_DISPMD_Pos)  
#define DISP_DISPCTRL_DISPMD_DISABLE     								((uint32_t)0x00000000)
#define DISP_DISPCTRL_DISPMD_ENABLE     								((uint32_t)0x00000001)

/** @defgroup DISP_DISPCTRL_TEST 
  * @{
  */
#define DISP_DISPCTRL_TEST_Pos		               				1                                             
#define DISP_DISPCTRL_TEST_Msk               						(0x01UL << DISP_DISPCTRL_TEST_Pos)  
#define DISP_DISPCTRL_TEST_DISABLE     									((uint32_t)0x00000000)
#define DISP_DISPCTRL_TEST_ENABLE     									((uint32_t)0x00000002)

/** @defgroup DISP_DISPCTRL_FLICK 
  * @{
  */
#define DISP_DISPCTRL_FLICK_Pos		               				2                                             
#define DISP_DISPCTRL_FLICK_Msk               					(0x01UL << DISP_DISPCTRL_FLICK_Pos)  
#define DISP_DISPCTRL_FLICK_DISABLE     								((uint32_t)0x00000000)
#define DISP_DISPCTRL_FLICK_ENABLE     									((uint32_t)0x00000004)

/** @defgroup DISP_DISPCTRL_LCDEN 
  * @{
  */
#define DISP_DISPCTRL_LCDEN_Pos		               				6                                             
#define DISP_DISPCTRL_LCDEN_Msk               					(0x01UL << DISP_DISPCTRL_LCDEN_Pos)  
#define DISP_DISPCTRL_LCDEN_DISABLE     								((uint32_t)0x00000000)
#define DISP_DISPCTRL_LCDEN_ENABLE     									((uint32_t)0x00000040)

/** @defgroup DISP_DISPCTRL_ANTIPOLAR
  * @{
  */
#define DISP_DISPCTRL_ANTIPOLAR_Pos		               		7                                             
#define DISP_DISPCTRL_ANTIPOLAR_Msk               			(0x01UL << DISP_DISPCTRL_ANTIPOLAR_Pos)  
#define DISP_DISPCTRL_ANTIPOLAR_DISABLE     						((uint32_t)0x00000000)
#define DISP_DISPCTRL_ANTIPOLAR_ENABLE     							((uint32_t)0x00000080)


/**
* @}DISP_LCDTEST
*/ 
  
/** @defgroup DISP_LCDTEST_TESTEN
  * @{
  */
#define DISP_LCDTEST_TESTEN_Pos		               				0                                             
#define DISP_LCDTEST_TESTEN_Msk               					(0x01UL << DISP_LCDTEST_TESTEN_Pos)  
#define DISP_LCDTEST_TESTEN_DISABLE     								((uint32_t)0x00000000)
#define DISP_LCDTEST_TESTEN_ENABLE     									((uint32_t)0x00000001)

/** @defgroup DISP_LCDTEST_LCCTRL
  * @{
  */
#define DISP_LCDTEST_LCCTRL_Pos		               				7                                             
#define DISP_LCDTEST_LCCTRL_Msk               					(0x01UL << DISP_LCDTEST_LCCTRL_Pos)  
#define DISP_LCDTEST_LCCTRL_DISABLE     								((uint32_t)0x00000000)
#define DISP_LCDTEST_LCCTRL_ENABLE     									((uint32_t)0x00000080)


/**
* @}DISP_DISPIE
*/ 
  
/** @defgroup DISP_DISPIE_DOFFIE
  * @{
  */
#define DISP_DISPIE_DOFFIE_Pos		               				0                                             
#define DISP_DISPIE_DOFFIE_Msk               						(0x01UL << DISP_DISPIE_DOFFIE_Pos)  
#define DISP_DISPIE_DOFFIE_DISABLE     									((uint32_t)0x00000000)
#define DISP_DISPIE_DOFFIE_ENABLE     									((uint32_t)0x00000001)

/** @defgroup DISP_DISPIE_DONIE
  * @{
  */
#define DISP_DISPIE_DONIE_Pos		               					1                                             
#define DISP_DISPIE_DONIE_Msk               						(0x01UL << DISP_DISPIE_DONIE_Pos)  
#define DISP_DISPIE_DONIE_DISABLE     									((uint32_t)0x00000000)
#define DISP_DISPIE_DONIE_ENABLE     										((uint32_t)0x00000002)


/**
* @}DISP_DISPIF
*/ 
  
/** @defgroup DISP_DISPIF_DOFFIF
  * @{
  */
#define DISP_DISPIF_DOFFIF_Pos		               				0                                             
#define DISP_DISPIF_DOFFIF_Msk               						(0x01UL << DISP_DISPIF_DOFFIF_Pos)  
#define DISP_DISPIF_DOFFIF_NORMAL    										((uint32_t)0x00000000)
#define DISP_DISPIF_DOFFIF_OFF    											((uint32_t)0x00000001)

/** @defgroup DISP_DISPIF_DONIF
  * @{
  */
#define DISP_DISPIF_DONIF_Pos		               					1                                             
#define DISP_DISPIF_DONIF_Msk               						(0x01UL << DISP_DISPIF_DONIF_Pos)  
#define DISP_DISPIF_DONIF_NORMAL    										((uint32_t)0x00000000)
#define DISP_DISPIF_DONIF_ON      											((uint32_t)0x00000002)


/**
* @}DISP_LCDSET
*/ 
  
/** @defgroup DISP_LCDSET_LMUX
  * @{
  */
#define DISP_LCDSET_LMUX_Pos		               					0                                             
#define DISP_LCDSET_LMUX_Msk               							(0x03UL << DISP_LCDSET_LMUX_Pos)  
#define DISP_LCDSET_LMUX_4_COM    											((uint32_t)0x00000000)
#define DISP_LCDSET_LMUX_6_COM     							  			((uint32_t)0x00000001)

/** @defgroup DISP_LCDSET_WFT
  * @{
  */
#define DISP_LCDSET_WFT_Pos		               						2                                             
#define DISP_LCDSET_WFT_Msk               							(0x01UL << DISP_LCDSET_WFT_Pos)  
#define DISP_LCDSET_WFT_TYPE_A    											((uint32_t)0x00000000)
#define DISP_LCDSET_WFT_TYPE_B     											((uint32_t)0x00000004)

/** @defgroup DISP_LCDSET_VLCD
  * @{
  */
#define DISP_LCDSET_VLCD_Pos		               					3                                             
#define DISP_LCDSET_VLCD_Msk               							(0x01UL << DISP_LCDSET_VLCD_Pos)  
#define DISP_LCDSET_VLCD_FROM_INSIDE   									((uint32_t)0x00000000)
#define DISP_LCDSET_VLCD_FROM_OUTSIDE										((uint32_t)0x00000008)

/** @defgroup DISP_LCDSET_BIASMD
  * @{
  */
#define DISP_LCDSET_BIASMD_Pos		               				4                                             
#define DISP_LCDSET_BIASMD_Msk               						(0x01UL << DISP_LCDSET_BIASMD_Pos)  
#define DISP_LCDSET_BIASMD_1DIV4_BIAS   								((uint32_t)0x00000000)
#define DISP_LCDSET_BIASMD_1DIV3_BIAS										((uint32_t)0x00000010)


/**
* @}DISP_LCDDRV
*/ 
  
/** @defgroup DISP_LCDDRV_ENMODE
  * @{
  */
#define DISP_LCDDRV_ENMODE_Pos		               				0                                             
#define DISP_LCDDRV_ENMODE_Msk               						(0x01UL << DISP_LCDDRV_ENMODE_Pos)  
#define DISP_LCDDRV_ENMODE_COUT		  										((uint32_t)0x00000000)
#define DISP_LCDDRV_ENMODE_RIN    							  			((uint32_t)0x00000001)

/** @defgroup DISP_LCDDRV_IC_CTRL
  * @{
  */
#define DISP_LCDDRV_IC_CTRL_Pos		               				1                                             
#define DISP_LCDDRV_IC_CTRL_Msk               					(0x03UL << DISP_LCDDRV_IC_CTRL_Pos)  
#define DISP_LCDDRV_IC_CTRL_LARGEST		  								((uint32_t)0x00000000)
#define DISP_LCDDRV_IC_CTRL_LARGER   							  		((uint32_t)0x00000002)
#define DISP_LCDDRV_IC_CTRL_SMALLER		  								((uint32_t)0x00000004)
#define DISP_LCDDRV_IC_CTRL_SMALLEST   							  	((uint32_t)0x00000006)

/** @defgroup DISP_LCDDRV_SC_CTRL
  * @{
  */
#define DISP_LCDDRV_SC_CTRL_Pos		               				3                                             
#define DISP_LCDDRV_SC_CTRL_Msk               					(0x03UL << DISP_LCDDRV_SC_CTRL_Pos)  
#define DISP_LCDDRV_SC_CTRL_DRIVE_1Time				  				((uint32_t)0x00000000)
#define DISP_LCDDRV_SC_CTRL_DRIVE_2Times   							((uint32_t)0x00000008)
#define DISP_LCDDRV_SC_CTRL_DRIVE_4Times		  					((uint32_t)0x00000010)
#define DISP_LCDDRV_SC_CTRL_DRIVE_Multi_Times 			 		((uint32_t)0x00000018)

/** @defgroup DISP_LCDDRV_SCFSEL
  * @{
  */
#define DISP_LCDDRV_SCFSEL_Pos		               				5                                             
#define DISP_LCDDRV_SCFSEL_Msk               						(0x07UL << DISP_LCDDRV_SCFSEL_Pos)  
#define DISP_LCDDRV_SCFSEL_Other				  							((uint32_t)0x00000000)
#define DISP_LCDDRV_SCFSEL_DIV_8   											((uint32_t)0x00000020)
#define DISP_LCDDRV_SCFSEL_DIV_16				  							((uint32_t)0x00000040)
#define DISP_LCDDRV_SCFSEL_DIV_32			 							 	 	((uint32_t)0x00000060)
#define DISP_LCDDRV_SCFSEL_DIV_64  											((uint32_t)0x00000080)
#define DISP_LCDDRV_SCFSEL_DIV_128			  							((uint32_t)0x000000A0)
#define DISP_LCDDRV_SCFSEL_DIV_256			 							 	((uint32_t)0x000000C0)
#define DISP_LCDDRV_SCFSEL_DIV_512			 							 	((uint32_t)0x000000E0)


/**
* @}DISP_COM_EN
*/ 
  
/** @defgroup DISP_COM_EN_COMEN0
  * @{
  */
#define DISP_COM_EN_COMEN0_Pos		               				0                                             
#define DISP_COM_EN_COMEN0_Msk               						(0x03UL << DISP_COM_EN_COMEN0_Pos)  
#define DISP_COM_EN_COMEN0_DISABLE    									((uint32_t)0x00000000)
#define DISP_COM_EN_COMEN0_ENABLE    						  			((uint32_t)0x00000001)

/** @defgroup DISP_COM_EN_COMEN1
  * @{
  */
#define DISP_COM_EN_COMEN1_Pos		               				1                                             
#define DISP_COM_EN_COMEN1_Msk               						(0x03UL << DISP_COM_EN_COMEN1_Pos)  
#define DISP_COM_EN_COMEN1_DISABLE    									((uint32_t)0x00000000)
#define DISP_COM_EN_COMEN1_ENABLE    						  			((uint32_t)0x00000002)

/** @defgroup DISP_COM_EN_COMEN2
  * @{
  */
#define DISP_COM_EN_COMEN2_Pos		               				2                                             
#define DISP_COM_EN_COMEN2_Msk               						(0x03UL << DISP_COM_EN_COMEN2_Pos)  
#define DISP_COM_EN_COMEN2_DISABLE    									((uint32_t)0x00000000)
#define DISP_COM_EN_COMEN2_ENABLE    						  			((uint32_t)0x00000004)

/** @defgroup DISP_COM_EN_COMEN3
  * @{
  */
#define DISP_COM_EN_COMEN3_Pos		               				3                                             
#define DISP_COM_EN_COMEN3_Msk               						(0x03UL << DISP_COM_EN_COMEN3_Pos)  
#define DISP_COM_EN_COMEN3_DISABLE    									((uint32_t)0x00000000)
#define DISP_COM_EN_COMEN3_ENABLE    						  			((uint32_t)0x00000008)


/**
* @}DISP_SEG_EN0
*/ 
  
/** @defgroup DISP_SEG_EN0_SEGEN0
  * @{
  */
#define DISP_SEG_EN0_SEGEN0_Pos		               				0                                             
#define DISP_SEG_EN0_SEGEN0_Msk               					(0x01UL << DISP_SEG_EN0_SEGEN0_Pos)  
#define DISP_SEG_EN0_SEGEN0_DISABLE    									((uint32_t)0x00000000)
#define DISP_SEG_EN0_SEGEN0_ENABLE    						  		((uint32_t)0x00000001)

/** @defgroup DISP_SEG_EN0_SEGEN1
  * @{
  */
#define DISP_SEG_EN0_SEGEN1_Pos		               				1                                             
#define DISP_SEG_EN0_SEGEN1_Msk               					(0x01UL << DISP_SEG_EN0_SEGEN1_Pos)  
#define DISP_SEG_EN0_SEGEN1_DISABLE    									((uint32_t)0x00000000)
#define DISP_SEG_EN0_SEGEN1_ENABLE    						  		((uint32_t)0x00000002)

/** @defgroup DISP_SEG_EN0_SEGEN2
  * @{
  */
#define DISP_SEG_EN0_SEGEN2_Pos		               				2                                             
#define DISP_SEG_EN0_SEGEN2_Msk               					(0x01UL << DISP_SEG_EN0_SEGEN2_Pos)  
#define DISP_SEG_EN0_SEGEN2_DISABLE    									((uint32_t)0x00000000)
#define DISP_SEG_EN0_SEGEN2_ENABLE    						  		((uint32_t)0x00000004)

/** @defgroup DISP_SEG_EN0_SEGEN3
  * @{
  */
#define DISP_SEG_EN0_SEGEN3_Pos		               				3                                             
#define DISP_SEG_EN0_SEGEN3_Msk               					(0x01UL << DISP_SEG_EN0_SEGEN3_Pos)  
#define DISP_SEG_EN0_SEGEN3_DISABLE    									((uint32_t)0x00000000)
#define DISP_SEG_EN0_SEGEN3_ENABLE    						  		((uint32_t)0x00000008)

/** @defgroup DISP_SEG_EN0_SEGEN4
  * @{
  */
#define DISP_SEG_EN0_SEGEN4_Pos		               				4                                            
#define DISP_SEG_EN0_SEGEN4_Msk               					(0x01UL << DISP_SEG_EN0_SEGEN4_Pos)  
#define DISP_SEG_EN0_SEGEN4_DISABLE    									((uint32_t)0x00000000)
#define DISP_SEG_EN0_SEGEN4_ENABLE    						  		((uint32_t)0x00000010)

/** @defgroup DISP_SEG_EN0_SEGEN5
  * @{
  */
#define DISP_SEG_EN0_SEGEN5_Pos		               				5                                            
#define DISP_SEG_EN0_SEGEN5_Msk               					(0x01UL << DISP_SEG_EN0_SEGEN5_Pos)  
#define DISP_SEG_EN0_SEGEN5_DISABLE    									((uint32_t)0x00000000)
#define DISP_SEG_EN0_SEGEN5_ENABLE    						  		((uint32_t)0x00000020)

/** @defgroup DISP_SEG_EN0_SEGEN6
  * @{
  */
#define DISP_SEG_EN0_SEGEN6_Pos		               				6                                            
#define DISP_SEG_EN0_SEGEN6_Msk               					(0x01UL << DISP_SEG_EN0_SEGEN6_Pos)  
#define DISP_SEG_EN0_SEGEN6_DISABLE    									((uint32_t)0x00000000)
#define DISP_SEG_EN0_SEGEN6_ENABLE    						  		((uint32_t)0x00000040)

/** @defgroup DISP_SEG_EN0_SEGEN7
  * @{
  */
#define DISP_SEG_EN0_SEGEN7_Pos		               				7                                            
#define DISP_SEG_EN0_SEGEN7_Msk               					(0x01UL << DISP_SEG_EN0_SEGEN7_Pos)  
#define DISP_SEG_EN0_SEGEN7_DISABLE    									((uint32_t)0x00000000)
#define DISP_SEG_EN0_SEGEN7_ENABLE    						  		((uint32_t)0x00000080)

/** @defgroup DISP_SEG_EN0_SEGEN8
  * @{
  */
#define DISP_SEG_EN0_SEGEN8_Pos		               				8                                            
#define DISP_SEG_EN0_SEGEN8_Msk               					(0x01UL << DISP_SEG_EN0_SEGEN8_Pos)  
#define DISP_SEG_EN0_SEGEN8_DISABLE    									((uint32_t)0x00000000)
#define DISP_SEG_EN0_SEGEN8_ENABLE    						  		((uint32_t)0x00000100)

/** @defgroup DISP_SEG_EN0_SEGEN9
  * @{
  */
#define DISP_SEG_EN0_SEGEN9_Pos		               				9                                            
#define DISP_SEG_EN0_SEGEN9_Msk               					(0x01UL << DISP_SEG_EN0_SEGEN9_Pos)  
#define DISP_SEG_EN0_SEGEN9_DISABLE    									((uint32_t)0x00000000)
#define DISP_SEG_EN0_SEGEN9_ENABLE    						  		((uint32_t)0x00000200)

/** @defgroup DISP_SEG_EN0_SEGEN10
  * @{
  */
#define DISP_SEG_EN0_SEGEN10_Pos		               			10                                            
#define DISP_SEG_EN0_SEGEN10_Msk               					(0x01UL << DISP_SEG_EN0_SEGEN10_Pos)  
#define DISP_SEG_EN0_SEGEN10_DISABLE    								((uint32_t)0x00000000)
#define DISP_SEG_EN0_SEGEN10_ENABLE    						  		((uint32_t)0x00000400)

/** @defgroup DISP_SEG_EN0_SEGEN11
  * @{
  */
#define DISP_SEG_EN0_SEGEN11_Pos		               			11                                            
#define DISP_SEG_EN0_SEGEN11_Msk               					(0x01UL << DISP_SEG_EN0_SEGEN11_Pos)  
#define DISP_SEG_EN0_SEGEN11_DISABLE    								((uint32_t)0x00000000)
#define DISP_SEG_EN0_SEGEN11_ENABLE    						  		((uint32_t)0x00000800)

/** @defgroup DISP_SEG_EN0_SEGEN12
  * @{
  */
#define DISP_SEG_EN0_SEGEN12_Pos		               			12                                            
#define DISP_SEG_EN0_SEGEN12_Msk               					(0x01UL << DISP_SEG_EN0_SEGEN12_Pos)  
#define DISP_SEG_EN0_SEGEN12_DISABLE    								((uint32_t)0x00000000)
#define DISP_SEG_EN0_SEGEN12_ENABLE    						  		((uint32_t)0x00001000)

/** @defgroup DISP_SEG_EN0_SEGEN13
  * @{
  */
#define DISP_SEG_EN0_SEGEN13_Pos		               			13                                            
#define DISP_SEG_EN0_SEGEN13_Msk               					(0x01UL << DISP_SEG_EN0_SEGEN13_Pos)  
#define DISP_SEG_EN0_SEGEN13_DISABLE    								((uint32_t)0x00000000)
#define DISP_SEG_EN0_SEGEN13_ENABLE    						  		((uint32_t)0x00002000)

/** @defgroup DISP_SEG_EN0_SEGEN14
  * @{
  */
#define DISP_SEG_EN0_SEGEN14_Pos		               			14                                            
#define DISP_SEG_EN0_SEGEN14_Msk               					(0x01UL << DISP_SEG_EN0_SEGEN14_Pos)  
#define DISP_SEG_EN0_SEGEN14_DISABLE    								((uint32_t)0x00000000)
#define DISP_SEG_EN0_SEGEN14_ENABLE    						  		((uint32_t)0x00004000)

/** @defgroup DISP_SEG_EN0_SEGEN15
  * @{
  */
#define DISP_SEG_EN0_SEGEN15_Pos		               			15                                            
#define DISP_SEG_EN0_SEGEN15_Msk               					(0x01UL << DISP_SEG_EN0_SEGEN15_Pos)  
#define DISP_SEG_EN0_SEGEN15_DISABLE    								((uint32_t)0x00000000)
#define DISP_SEG_EN0_SEGEN15_ENABLE    						  		((uint32_t)0x00008000)

/** @defgroup DISP_SEG_EN0_SEGEN16
  * @{
  */
#define DISP_SEG_EN0_SEGEN16_Pos		               			16                                            
#define DISP_SEG_EN0_SEGEN16_Msk               					(0x01UL << DISP_SEG_EN0_SEGEN16_Pos)  
#define DISP_SEG_EN0_SEGEN16_DISABLE    								((uint32_t)0x00000000)
#define DISP_SEG_EN0_SEGEN16_ENABLE    						  		((uint32_t)0x00010000)

/** @defgroup DISP_SEG_EN0_SEGEN17
  * @{
  */
#define DISP_SEG_EN0_SEGEN17_Pos		               			17                                            
#define DISP_SEG_EN0_SEGEN17_Msk               					(0x01UL << DISP_SEG_EN0_SEGEN17_Pos)  
#define DISP_SEG_EN0_SEGEN17_DISABLE    								((uint32_t)0x00000000)
#define DISP_SEG_EN0_SEGEN17_ENABLE    						  		((uint32_t)0x00020000)

/** @defgroup DISP_SEG_EN0_SEGEN18
  * @{
  */
#define DISP_SEG_EN0_SEGEN18_Pos		               			18                                            
#define DISP_SEG_EN0_SEGEN18_Msk               					(0x01UL << DISP_SEG_EN0_SEGEN18_Pos)  
#define DISP_SEG_EN0_SEGEN18_DISABLE    								((uint32_t)0x00000000)
#define DISP_SEG_EN0_SEGEN18_ENABLE    						  		((uint32_t)0x00040000)

/** @defgroup DISP_SEG_EN0_SEGEN19
  * @{
  */
#define DISP_SEG_EN0_SEGEN19_Pos		               			19                                            
#define DISP_SEG_EN0_SEGEN19_Msk               					(0x01UL << DISP_SEG_EN0_SEGEN19_Pos)  
#define DISP_SEG_EN0_SEGEN19_DISABLE    								((uint32_t)0x00000000)
#define DISP_SEG_EN0_SEGEN19_ENABLE    						  		((uint32_t)0x00080000)

/** @defgroup DISP_SEG_EN0_SEGEN20
  * @{
  */
#define DISP_SEG_EN0_SEGEN20_Pos		               			20                                            
#define DISP_SEG_EN0_SEGEN20_Msk               					(0x01UL << DISP_SEG_EN0_SEGEN20_Pos)  
#define DISP_SEG_EN0_SEGEN20_DISABLE    								((uint32_t)0x00000000)
#define DISP_SEG_EN0_SEGEN20_ENABLE    						  		((uint32_t)0x00100000)

/** @defgroup DISP_SEG_EN0_SEGEN21
  * @{
  */
#define DISP_SEG_EN0_SEGEN21_Pos		               			21                                            
#define DISP_SEG_EN0_SEGEN21_Msk               					(0x01UL << DISP_SEG_EN0_SEGEN21_Pos)  
#define DISP_SEG_EN0_SEGEN21_DISABLE    								((uint32_t)0x00000000)
#define DISP_SEG_EN0_SEGEN21_ENABLE    						  		((uint32_t)0x00200000)

/** @defgroup DISP_SEG_EN0_SEGEN22
  * @{
  */
#define DISP_SEG_EN0_SEGEN22_Pos		               			22                                            
#define DISP_SEG_EN0_SEGEN22_Msk               					(0x01UL << DISP_SEG_EN0_SEGEN22_Pos)  
#define DISP_SEG_EN0_SEGEN22_DISABLE    								((uint32_t)0x00000000)
#define DISP_SEG_EN0_SEGEN22_ENABLE    						  		((uint32_t)0x00400000)

/** @defgroup DISP_SEG_EN0_SEGEN23
  * @{
  */
#define DISP_SEG_EN0_SEGEN23_Pos		               			23                                            
#define DISP_SEG_EN0_SEGEN23_Msk               					(0x01UL << DISP_SEG_EN0_SEGEN23_Pos)  
#define DISP_SEG_EN0_SEGEN23_DISABLE    								((uint32_t)0x00000000)
#define DISP_SEG_EN0_SEGEN23_ENABLE    						  		((uint32_t)0x00800000)

/** @defgroup DISP_SEG_EN0_SEGEN24
  * @{
  */
#define DISP_SEG_EN0_SEGEN24_Pos		               			24                                            
#define DISP_SEG_EN0_SEGEN24_Msk               					(0x01UL << DISP_SEG_EN0_SEGEN24_Pos)  
#define DISP_SEG_EN0_SEGEN24_DISABLE    								((uint32_t)0x00000000)
#define DISP_SEG_EN0_SEGEN24_ENABLE    						  		((uint32_t)0x01000000)

/** @defgroup DISP_SEG_EN0_SEGEN25
  * @{
  */
#define DISP_SEG_EN0_SEGEN25_Pos		               			25                                            
#define DISP_SEG_EN0_SEGEN25_Msk               					(0x01UL << DISP_SEG_EN0_SEGEN25_Pos)  
#define DISP_SEG_EN0_SEGEN25_DISABLE    								((uint32_t)0x00000000)
#define DISP_SEG_EN0_SEGEN25_ENABLE    						  		((uint32_t)0x02000000)

/** @defgroup DISP_SEG_EN0_SEGEN26
  * @{
  */
#define DISP_SEG_EN0_SEGEN26_Pos		               			26                                            
#define DISP_SEG_EN0_SEGEN26_Msk               					(0x01UL << DISP_SEG_EN0_SEGEN26_Pos)  
#define DISP_SEG_EN0_SEGEN26_DISABLE    								((uint32_t)0x00000000)
#define DISP_SEG_EN0_SEGEN26_ENABLE    						  		((uint32_t)0x04000000)

/** @defgroup DISP_SEG_EN0_SEGEN27
  * @{
  */
#define DISP_SEG_EN0_SEGEN27_Pos		               			27                                            
#define DISP_SEG_EN0_SEGEN27_Msk               					(0x01UL << DISP_SEG_EN0_SEGEN27_Pos)  
#define DISP_SEG_EN0_SEGEN27_DISABLE    								((uint32_t)0x00000000)
#define DISP_SEG_EN0_SEGEN27_ENABLE    						  		((uint32_t)0x08000000)

/** @defgroup DISP_SEG_EN0_SEGEN28
  * @{
  */
#define DISP_SEG_EN0_SEGEN28_Pos		               			28                                            
#define DISP_SEG_EN0_SEGEN28_Msk               					(0x01UL << DISP_SEG_EN0_SEGEN28_Pos)  
#define DISP_SEG_EN0_SEGEN28_DISABLE    								((uint32_t)0x00000000)
#define DISP_SEG_EN0_SEGEN28_ENABLE    						  		((uint32_t)0x10000000)

/** @defgroup DISP_SEG_EN0_SEGEN29
  * @{
  */
#define DISP_SEG_EN0_SEGEN29_Pos		               			29                                            
#define DISP_SEG_EN0_SEGEN29_Msk               					(0x01UL << DISP_SEG_EN0_SEGEN29_Pos)  
#define DISP_SEG_EN0_SEGEN29_DISABLE    								((uint32_t)0x00000000)
#define DISP_SEG_EN0_SEGEN29_ENABLE    						  		((uint32_t)0x20000000)

/** @defgroup DISP_SEG_EN0_SEGEN30
  * @{
  */
#define DISP_SEG_EN0_SEGEN30_Pos		               			30                                            
#define DISP_SEG_EN0_SEGEN30_Msk               					(0x01UL << DISP_SEG_EN0_SEGEN30_Pos)  
#define DISP_SEG_EN0_SEGEN30_DISABLE    								((uint32_t)0x00000000)
#define DISP_SEG_EN0_SEGEN30_ENABLE    						  		((uint32_t)0x40000000)

/** @defgroup DISP_SEG_EN0_SEGEN31
  * @{
  */
#define DISP_SEG_EN0_SEGEN31_Pos		               			31                                            
#define DISP_SEG_EN0_SEGEN31_Msk               					(0x01UL << DISP_SEG_EN0_SEGEN31_Pos)  
#define DISP_SEG_EN0_SEGEN31_DISABLE    								((uint32_t)0x00000000)
#define DISP_SEG_EN0_SEGEN31_ENABLE    						  		((uint32_t)0x80000000)


/**
* @}DISP_SEG_EN1
*/ 
  
/** @defgroup DISP_SEG_EN1_SEGEN0
  * @{
  */
#define DISP_SEG_EN1_SEGEN0_Pos		               				0                                             
#define DISP_SEG_EN1_SEGEN0_Msk               					(0x01UL << DISP_SEG_EN1_SEGEN0_Pos)  
#define DISP_SEG_EN1_SEGEN0_DISABLE    									((uint32_t)0x00000000)
#define DISP_SEG_EN1_SEGEN0_ENABLE    						  		((uint32_t)0x00000001)

/** @defgroup DISP_SEG_EN1_SEGEN1
  * @{
  */
#define DISP_SEG_EN1_SEGEN1_Pos		               				1                                             
#define DISP_SEG_EN1_SEGEN1_Msk               					(0x01UL << DISP_SEG_EN1_SEGEN1_Pos)  
#define DISP_SEG_EN1_SEGEN1_DISABLE    									((uint32_t)0x00000000)
#define DISP_SEG_EN1_SEGEN1_ENABLE    						  		((uint32_t)0x00000002)

/** @defgroup DISP_SEG_EN1_SEGEN2
  * @{
  */
#define DISP_SEG_EN1_SEGEN2_Pos		               				2                                             
#define DISP_SEG_EN1_SEGEN2_Msk               					(0x01UL << DISP_SEG_EN1_SEGEN2_Pos)  
#define DISP_SEG_EN1_SEGEN2_DISABLE    									((uint32_t)0x00000000)
#define DISP_SEG_EN1_SEGEN2_ENABLE    						  		((uint32_t)0x00000004)

/** @defgroup DISP_SEG_EN1_SEGEN3
  * @{
  */
#define DISP_SEG_EN1_SEGEN3_Pos		               				3                                             
#define DISP_SEG_EN1_SEGEN3_Msk               					(0x01UL << DISP_SEG_EN1_SEGEN3_Pos)  
#define DISP_SEG_EN1_SEGEN3_DISABLE    									((uint32_t)0x00000000)
#define DISP_SEG_EN1_SEGEN3_ENABLE    						  		((uint32_t)0x00000008)

/** @defgroup DISP_SEG_EN1_SEGEN4
  * @{
  */
#define DISP_SEG_EN1_SEGEN4_Pos		               				4                                            
#define DISP_SEG_EN1_SEGEN4_Msk               					(0x01UL << DISP_SEG_EN1_SEGEN4_Pos)  
#define DISP_SEG_EN1_SEGEN4_DISABLE    									((uint32_t)0x00000000)
#define DISP_SEG_EN1_SEGEN4_ENABLE    						  		((uint32_t)0x00000010)

/** @defgroup DISP_SEG_EN1_SEGEN5
  * @{
  */
#define DISP_SEG_EN1_SEGEN5_Pos		               				5                                            
#define DISP_SEG_EN1_SEGEN5_Msk               					(0x01UL << DISP_SEG_EN1_SEGEN5_Pos)  
#define DISP_SEG_EN1_SEGEN5_DISABLE    									((uint32_t)0x00000000)
#define DISP_SEG_EN1_SEGEN5_ENABLE    						  		((uint32_t)0x00000020)

/** @defgroup DISP_SEG_EN1_SEGEN6
  * @{
  */
#define DISP_SEG_EN1_SEGEN6_Pos		               				6                                            
#define DISP_SEG_EN1_SEGEN6_Msk               					(0x01UL << DISP_SEG_EN1_SEGEN6_Pos)  
#define DISP_SEG_EN1_SEGEN6_DISABLE    									((uint32_t)0x00000000)
#define DISP_SEG_EN1_SEGEN6_ENABLE    						  		((uint32_t)0x00000040)

/** @defgroup DISP_SEG_EN1_SEGEN7
  * @{
  */
#define DISP_SEG_EN1_SEGEN7_Pos		               				7                                            
#define DISP_SEG_EN1_SEGEN7_Msk               					(0x01UL << DISP_SEG_EN1_SEGEN7_Pos)  
#define DISP_SEG_EN1_SEGEN7_DISABLE    									((uint32_t)0x00000000)
#define DISP_SEG_EN1_SEGEN7_ENABLE    						  		((uint32_t)0x00000080)

/** @defgroup DISP_SEG_EN1_SEGEN8
  * @{
  */
#define DISP_SEG_EN1_SEGEN8_Pos		               				8                                            
#define DISP_SEG_EN1_SEGEN8_Msk               					(0x01UL << DISP_SEG_EN1_SEGEN8_Pos)  
#define DISP_SEG_EN1_SEGEN8_DISABLE    									((uint32_t)0x00000000)
#define DISP_SEG_EN1_SEGEN8_ENABLE    						  		((uint32_t)0x00000100)

/** @defgroup DISP_SEG_EN1_SEGEN9
  * @{
  */
#define DISP_SEG_EN1_SEGEN9_Pos		               				9                                            
#define DISP_SEG_EN1_SEGEN9_Msk               					(0x01UL << DISP_SEG_EN1_SEGEN9_Pos)  
#define DISP_SEG_EN1_SEGEN9_DISABLE    									((uint32_t)0x00000000)
#define DISP_SEG_EN1_SEGEN9_ENABLE    						  		((uint32_t)0x00000200)

/** @defgroup DISP_SEG_EN1_SEGEN10
  * @{
  */
#define DISP_SEG_EN1_SEGEN10_Pos		               			10                                            
#define DISP_SEG_EN1_SEGEN10_Msk               					(0x01UL << DISP_SEG_EN1_SEGEN10_Pos)  
#define DISP_SEG_EN1_SEGEN10_DISABLE    								((uint32_t)0x00000000)
#define DISP_SEG_EN1_SEGEN10_ENABLE    						  		((uint32_t)0x00000400)

/** @defgroup DISP_SEG_EN1_SEGEN11
  * @{
  */
#define DISP_SEG_EN1_SEGEN11_Pos		               			11                                            
#define DISP_SEG_EN1_SEGEN11_Msk               					(0x01UL << DISP_SEG_EN1_SEGEN11_Pos)  
#define DISP_SEG_EN1_SEGEN11_DISABLE    								((uint32_t)0x00000000)
#define DISP_SEG_EN1_SEGEN11_ENABLE    						  		((uint32_t)0x00000800)









#ifdef __cplusplus
}
#endif

#endif /* __FM32L0xx_DISP_H */



/************************ (C) COPYRIGHT FMSHelectronics *****END OF FILE****/



