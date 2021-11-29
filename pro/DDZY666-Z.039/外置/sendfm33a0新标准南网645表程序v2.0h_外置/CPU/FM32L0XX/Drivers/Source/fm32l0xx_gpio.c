/**
  ******************************************************************************
  * @file    FM385_gpio.c
  * @author  FM385 Application Team
  * @version V1.0.0
  * @date    21-SEPT-2016
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the clock control (RCC) peripheral:
  *           + Internal/external clocks, PLL, CSS and MCO configuration
  *           + System, AHB and APB busses clocks configuration
  *           + Peripheral clocks configuration
  *           + Interrupts and flags management
  *
*/

/* Includes ------------------------------------------------------------------*/
#include "FM32L0XX.h" 


/** @addtogroup fm385_StdPeriph_Driver
  * @{
  */

/** @defgroup GPIO 
  * @brief GPIO driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup GPIO_Private_Functions
  * @{
  */ 
  
/**
  * @brief  Initializes the GPIOx peripheral according to the specified parameters in the GPIO_InitStruct.
  * @param  GPIOx: where x can be (A..K) to select the GPIO peripheral for STM32F405xx/407xx and STM32F415xx/417xx devices
  *                      x can be (A..I) to select the GPIO peripheral for STM32F42xxx/43xxx devices.
  *                      x can be (A, B, C, D and H) to select the GPIO peripheral for STM32F401xx devices.   
  * @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure that contains
  *         the configuration information for the specified GPIO peripheral.
  * @retval None
  */
  
void GPIO_Init(GPIOx_Type* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
	uint32_t pinpos = 0x00,pinbit = 0x00,currentpin =0x00;

	
	for (pinpos = 0x00; pinpos < 0x10; pinpos++)
	{
   	pinbit = ((uint32_t)0x01) <<pinpos;
		currentpin = (GPIO_InitStruct->GPIO_Pin) & pinbit;
			
		if (currentpin == pinbit)
		{
			GPIOx->INEN &= ~pinbit;
			GPIOx->INEN |= (GPIO_InitStruct->GPIO_In)<<pinpos;
			
			GPIOx->PUEN &= ~pinbit;
			GPIOx->PUEN |= (GPIO_InitStruct->GPIO_Pu)<<pinpos;

			GPIOx->ODEN &= ~pinbit;
			GPIOx->ODEN |= (GPIO_InitStruct->GPIO_OType)<<pinpos;

			pinbit = (GPIO_FCR_Msk) <<(pinpos*2);
			GPIOx->FCR &= ~pinbit;
			GPIOx->FCR |= (GPIO_InitStruct->GPIO_Mode)<<(pinpos*2);

		}
 }
}	

void GPIO_Get_InitParam(GPIOx_Type* GPIOx, uint32_t GPIO_Pin, GPIO_InitTypeDef* GPIO_InitStruct)
{
    uint32_t pinbit = 0x00;
    uint32_t i,temp;

	for (i = 0x00; i < 0x10; i++)
	{
		pinbit = GPIO_Pin & (1<<i);
		if(pinbit > 0) break;                                              
	}
	
	if(i < 0x10)
	{
		pinbit = i;
		GPIO_InitStruct->GPIO_Pin = GPIO_Pin;
		
		temp = (GPIOx->INEN&GPIO_Pin)>>pinbit; 
		if(temp == (uint32_t)GPIO_In_EN)
		{                                         
			GPIO_InitStruct->GPIO_In = GPIO_In_EN;
		}
		else
		{
			GPIO_InitStruct->GPIO_In = GPIO_In_DIS;
		}   
		
		temp = (GPIOx->PUEN&GPIO_Pin)>>pinbit;                                    
		if(temp == (uint32_t)GPIO_PuPd_UP)
		{                                         
			GPIO_InitStruct->GPIO_Pu = GPIO_PuPd_UP;
		}
		else
		{
			GPIO_InitStruct->GPIO_Pu = GPIO_PuPd_NOPULL;
		}   
		
		temp = (GPIOx->ODEN&GPIO_Pin)>>pinbit;                                   
		if(temp == (uint32_t)GPIO_OType_OD)
		{                                         
			GPIO_InitStruct->GPIO_OType = GPIO_OType_OD;
		}
		else
		{
			GPIO_InitStruct->GPIO_OType = GPIO_OType_PP;
		}  
		
		temp = (GPIOx->FCR>>(pinbit*2))&0x00000003;                                    
		if(temp == (uint32_t)GPIO_Mode_IN)
		{                                         
			GPIO_InitStruct->GPIO_Mode = GPIO_Mode_IN;
		}
		else if(temp == (uint32_t)GPIO_Mode_OUT)
		{
			GPIO_InitStruct->GPIO_Mode = GPIO_Mode_OUT;
		}
		else if(temp == (uint32_t)GPIO_Mode_DIG)
		{                                         
			GPIO_InitStruct->GPIO_Mode = GPIO_Mode_DIG;
		}
		else
		{
			GPIO_InitStruct->GPIO_Mode = GPIO_Mode_ANA;
		} 
	}  
}

void GPIO_ResetBits(GPIOx_Type* GPIOx, uint32_t GPIO_Pin)
{

  GPIOx->BRESETL = GPIO_Pin;
}

void GPIO_SetBits(GPIOx_Type* GPIOx, uint32_t GPIO_Pin)
{

  GPIOx->BSETH = GPIO_Pin;
}

void GPIO_ToggleBits(GPIOx_Type* GPIOx, uint32_t GPIO_Pin)
{
  GPIOx->ODR ^= GPIO_Pin;
}

uint32_t GPIO_ReadInputData(GPIOx_Type* GPIOx)
{

  return ((uint32_t)GPIOx->IDR);
}


uint8_t GPIO_ReadInputDataBit(GPIOx_Type* GPIOx, uint32_t GPIO_Pin)
{
  uint8_t bitstatus = 0x00;

  if ((GPIOx->IDR & GPIO_Pin) != (uint32_t)Bit_RESET)
  {
    bitstatus = (uint8_t)Bit_SET;
  }
  else
  {
    bitstatus = (uint8_t)Bit_RESET;
  }
  return bitstatus;
}

uint32_t GPIO_ReadOutputData(GPIOx_Type* GPIOx)
{

  return ((uint32_t)GPIOx->ODR);
}

uint8_t GPIO_ReadOutputDataBit(GPIOx_Type* GPIOx, uint32_t GPIO_Pin)
{
  uint8_t bitstatus = 0x00;

  if (((GPIOx->ODR) & GPIO_Pin) != (uint32_t)Bit_RESET)
  {
    bitstatus = (uint8_t)Bit_SET;
  }
  else
  {
    bitstatus = (uint8_t)Bit_RESET;
  }
  return bitstatus;
}

void GPIO_Write(GPIOx_Type* GPIOx, uint32_t PortVal)
{
  GPIOx->ODR = PortVal;
}

void GPIO_WriteBit(GPIOx_Type* GPIOx, uint32_t GPIO_Pin, BitAction BitVal)
{

  if (BitVal != Bit_RESET)
  {
    GPIOx->BSETH = GPIO_Pin;
  }
  else
  {
    GPIOx->BRESETL = GPIO_Pin ;
  }
}


/******END OF FILE****/



