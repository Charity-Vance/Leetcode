/**
  ******************************************************************************
  * @file    fm32l0xx_gpio.h
  * @author  FM385 Application Team
  * @version V1.0.0
  * @date    20-SETP-2016
  * @brief   This file contains all the functions prototypes for the RCC firmware library.  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FM32L0xx_GPIO_H
#define __FM32L0xx_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "FM32L0XX.h"
	 
/** @addtogroup FM385_StdPeriph_Driver
  * @{
  */

/** @addtogroup GPIO
  * @{
  */
	 
/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  GPIO Configuration Mode enumeration 
  */   
typedef enum
{ 
  GPIO_Mode_IN   	= 0x00, /*!< GPIO Input Mode */
  GPIO_Mode_OUT  	= 0x01, /*!< GPIO Output Mode */
  GPIO_Mode_DIG   = 0x02, /*!< GPIO Alternate function Mode */
  GPIO_Mode_ANA   = 0x03  /*!< GPIO Analog Mode */
}GPIOMode_TypeDef;

/** 
  * @brief  GPIO Output type enumeration 
  */  
typedef enum
{ 
  GPIO_OType_PP = 0x00,
  GPIO_OType_OD = 0x01
}GPIOOType_TypeDef;


/** 
  * @brief  GPIO Configuration PullUp enumeration 
  */ 
typedef enum
{ 
  GPIO_PuPd_NOPULL = 0x00,
  GPIO_PuPd_UP     = 0x01 
}GPIOPu_TypeDef;

/** 
  * @brief  GPIO Configuration PullUp enumeration 
  */ 
typedef enum
{ 
  GPIO_In_DIS = 0x00,
  GPIO_In_EN     = 0x01 
}GPIOIn_TypeDef;


/** 
  * @brief   GPIO Init structure definition  
  */ 
typedef struct
{
  uint32_t GPIO_Pin;              
  GPIOMode_TypeDef GPIO_Mode;
  GPIOOType_TypeDef GPIO_OType;   
  GPIOPu_TypeDef GPIO_Pu; 
	GPIOIn_TypeDef	GPIO_In;	
}GPIO_InitTypeDef;


/** 
  * @brief  GPIO Bit SET and Bit RESET enumeration 
  */ 
typedef enum
{ 
  Bit_RESET = 0,
  Bit_SET
}BitAction;
/* Exported constants --------------------------------------------------------*/

/** @defgroup GPIO_Exported_Constants
  * @{
  */
	 
/**
* @}
*/ 


/** @defgroup GPIO_pins_define 
  * @{
  */ 
#define GPIO_Pin_0                 ((uint32_t)0x00000001)  /* Pin 0 selected */
#define GPIO_Pin_1                 ((uint32_t)0x00000002)  /* Pin 1 selected */
#define GPIO_Pin_2                 ((uint32_t)0x00000004)  /* Pin 2 selected */
#define GPIO_Pin_3                 ((uint32_t)0x00000008)  /* Pin 3 selected */
#define GPIO_Pin_4                 ((uint32_t)0x00000010)  /* Pin 4 selected */
#define GPIO_Pin_5                 ((uint32_t)0x00000020)  /* Pin 5 selected */
#define GPIO_Pin_6                 ((uint32_t)0x00000040)  /* Pin 6 selected */
#define GPIO_Pin_7                 ((uint32_t)0x00000080)  /* Pin 7 selected */
#define GPIO_Pin_8                 ((uint32_t)0x00000100)  /* Pin 8 selected */
#define GPIO_Pin_9                 ((uint32_t)0x00000200)  /* Pin 9 selected */
#define GPIO_Pin_10                ((uint32_t)0x00000400)  /* Pin 10 selected */
#define GPIO_Pin_11                ((uint32_t)0x00000800)  /* Pin 11 selected */
#define GPIO_Pin_12                ((uint32_t)0x00001000)  /* Pin 12 selected */
#define GPIO_Pin_13                ((uint32_t)0x00002000)  /* Pin 13 selected */
#define GPIO_Pin_14                ((uint32_t)0x00004000)  /* Pin 14 selected */
#define GPIO_Pin_15                ((uint32_t)0x00008000)  /* Pin 15 selected */


/** @defgroup GPIO_FCR_define 
  * @{
  */ 
#define GPIO_FCR_Msk	             ((uint32_t)0x00000003)
#define GPIO_FCR_GPIOIN            ((uint32_t)0x00000000)  /* GPIO INPUT selected */
#define GPIO_FCR_GPIOOUT           ((uint32_t)0x00000001)  /* GPIO OUTPUT selected */
#define GPIO_FCR_DIGITAL           ((uint32_t)0x00000002)  /* DIGITAL FUNCTION selected */
#define GPIO_FCR_ANALOG            ((uint32_t)0x00000003)  /* ANALOG FUNCTION selected */


/** @defgroup GPIO_EXTI_define 
  * @{
  */ 
#define GPIO_EXTI_RISING            ((uint32_t)0x00000000)  /* RISING EDGE TRIGER selected */
#define GPIO_EXTI_FALLING           ((uint32_t)0x00000001)  /* falling edge triger selected */
#define GPIO_EXTI_BOTH           		((uint32_t)0x00000002)  /* DIGITAL FUNCTION selected */
#define GPIO_EXTI_NONE            	((uint32_t)0x00000003)  /* ANALOG FUNCTION selected */

/** @defgroup GPIO_FOUTSEL_define 
  * @{
  */ 
#define GPIO_FOUTSEL_XTLF           ((uint32_t)0x00000000)  /* FOUT XTLF selected */
#define GPIO_FOUTSEL_RCLP           ((uint32_t)0x00000001)  /* FOUT RCLP selected */
#define GPIO_FOUTSEL_RCHF64      		((uint32_t)0x00000002)  /* FOUT RCHF/64 selected */
#define GPIO_FOUTSEL_LSCLK         	((uint32_t)0x00000003)  /* FOUT LSCLK selected */
#define GPIO_FOUTSEL_AHBCLK64       ((uint32_t)0x00000004)  /* FOUT AHBCLK/64 selected */
#define GPIO_FOUTSEL_RTCTM          ((uint32_t)0x00000005)  /* FOUT RTCTM selected */
#define GPIO_FOUTSEL_PLLO64         ((uint32_t)0x00000006)  /* FOUT PLLO/64 selected */
#define GPIO_FOUTSEL_RTCCLK64Hz    	((uint32_t)0x00000007)  /* FOUT RTCCLK64Hz selected */
#define GPIO_FOUTSEL_APBCLK64       ((uint32_t)0x00000008)  /* FOUT APBCLK/64 selected */
#define GPIO_FOUTSEL_LCDBC          ((uint32_t)0x00000009)  /* FOUT LCD Booster Clock selected */
#define GPIO_FOUTSEL_RCOSC64     		((uint32_t)0x0000000A)  /* FOUT LVMOS-Monitor-RCOSC/64 selected */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
extern void GPIO_Init(GPIOx_Type* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
extern void GPIO_Get_InitParam(GPIOx_Type* GPIOx, uint32_t GPIO_Pin, GPIO_InitTypeDef* GPIO_InitStruct);
extern void GPIO_ResetBits(GPIOx_Type* GPIOx, uint32_t GPIO_Pin);
extern void GPIO_SetBits(GPIOx_Type* GPIOx, uint32_t GPIO_Pin);
extern void GPIO_ToggleBits(GPIOx_Type* GPIOx, uint32_t GPIO_Pin);
extern void GPIO_Write(GPIOx_Type* GPIOx, uint32_t PortVal);




#ifdef __cplusplus
}
#endif

#endif /* __FM32L0xx_GPIO_H */



/************************ (C) COPYRIGHT FMSHelectronics *****END OF FILE****/



