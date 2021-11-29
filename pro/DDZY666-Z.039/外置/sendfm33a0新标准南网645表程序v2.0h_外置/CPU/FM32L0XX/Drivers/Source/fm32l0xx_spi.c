/**
  ******************************************************************************
  * @file    fm32l0xx_spi.c
  * @author  
  * @version V0.0.1
  * @date    04-JAN-2017
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of SPI:           
  *           
  ******************************************************************************  
  */ 

/* Includes ------------------------------------------------------------------*/
#include "FM32L0XX.h" 


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup SPI_Private_Functions
  * @{
  */ 
	
/** @defgroup HSPI_MASTER_Init
  * @{
  */ 
void HSPI_MASTER_Init(HSPI_MASTER_InitType* HSPI_MASTER_InitStruct)
{
	HSPI->SPICR1 &= ~SPI_SPICR1_DELAY_Msk; 
	HSPI->SPICR1 |= HSPI_MASTER_InitStruct->DELAY_CFG;
	
	HSPI->SPICR1 &= ~SPI_SPICR1_WAIT_Msk; 
	HSPI->SPICR1 |= HSPI_MASTER_InitStruct->WAIT;
	
	HSPI->SPICR1 &= ~SPI_SPICR1_BAUD_RATE_Msk; 
	HSPI->SPICR1 |= HSPI_MASTER_InitStruct->BAUD_RATE;

	HSPI->SPICR1 &= ~SPI_SPICR1_LSBF_Msk; 
	HSPI->SPICR1 |= HSPI_MASTER_InitStruct->LSBF;
	
	HSPI->SPICR1 &= ~SPI_SPICR1_CPHOL_Msk; 
	HSPI->SPICR1 |= HSPI_MASTER_InitStruct->CPHOL;
	
	HSPI->SPICR1 &= ~SPI_SPICR1_CPHA_Msk; 
	HSPI->SPICR1 |= HSPI_MASTER_InitStruct->CPHA;
	
	HSPI->SPICR2 &= ~SPI_SPICR2_SSNM_Msk; 
	HSPI->SPICR2 |= HSPI_MASTER_InitStruct->SSNM;
	
	HSPI->SPICR2 &= ~SPI_SPICR2_SSNSEN_Msk; 
	HSPI->SPICR2 |= HSPI_MASTER_InitStruct->SSNSEN;
	
	HSPI->SPICR1 &= ~SPI_SPICR1_MM_Msk; 
	HSPI->SPICR1 |= SPI_SPICR1_MM_MASTER;
	
}

/** @defgroup HSPI_SLAVE_Init
  * @{
  */ 
void HSPI_SLAVE_Init(HSPI_SLAVE_InitType* HSPI_SLAVE_InitStruct)
{
	HSPI->SPICR1 &= ~SPI_SPICR1_DELAY_Msk; 
	HSPI->SPICR1 |= HSPI_SLAVE_InitStruct->DELAY_CFG;

	HSPI->SPICR1 &= ~SPI_SPICR1_LSBF_Msk; 
	HSPI->SPICR1 |= HSPI_SLAVE_InitStruct->LSBF;
	
	HSPI->SPICR1 &= ~SPI_SPICR1_CPHOL_Msk; 
	HSPI->SPICR1 |= HSPI_SLAVE_InitStruct->CPHOL;
	
	HSPI->SPICR1 &= ~SPI_SPICR1_CPHA_Msk; 
	HSPI->SPICR1 |= HSPI_SLAVE_InitStruct->CPHA;
	
	HSPI->SPICR2 &= ~SPI_SPICR2_FLTEN_Msk; 
	HSPI->SPICR2 |= HSPI_SLAVE_InitStruct->FLTEN;
	
	HSPI->SPICR1 &= ~SPI_SPICR1_MM_Msk; 
	HSPI->SPICR1 |= SPI_SPICR1_MM_SLAVE;
	
}

/** @defgroup SPI_MASTER_Init
  * @{
  */ 
void SPI_MASTER_Init(SPI_Type* SPIx,SPI_MASTER_InitType* SPI_MASTER_InitStruct)
{
	SPIx->SPICR1 &= ~SPI_SPICR1_MSPA_Msk; 
	SPIx->SPICR1 |= SPI_MASTER_InitStruct->MSPA;
	
	SPIx->SPICR1 &= ~SPI_SPICR1_WAIT_Msk; 
	SPIx->SPICR1 |= SPI_MASTER_InitStruct->WAIT;
	
	SPIx->SPICR1 &= ~SPI_SPICR1_BAUD_RATE_Msk; 
	SPIx->SPICR1 |= SPI_MASTER_InitStruct->BAUD_RATE;

	SPIx->SPICR1 &= ~SPI_SPICR1_LSBF_Msk; 
	SPIx->SPICR1 |= SPI_MASTER_InitStruct->LSBF;
	
	SPIx->SPICR1 &= ~SPI_SPICR1_CPHOL_Msk; 
	SPIx->SPICR1 |= SPI_MASTER_InitStruct->CPHOL;
	
	SPIx->SPICR1 &= ~SPI_SPICR1_CPHA_Msk; 
	SPIx->SPICR1 |= SPI_MASTER_InitStruct->CPHA;
	
	SPIx->SPICR2 &= ~SPI_SPICR2_SSNM_Msk; 
	SPIx->SPICR2 |= SPI_MASTER_InitStruct->SSNM;
	
	SPIx->SPICR2 &= ~SPI_SPICR2_SSNSEN_Msk; 
	SPIx->SPICR2 |= SPI_MASTER_InitStruct->SSNSEN;
	
	SPIx->SPICR1 &= ~SPI_SPICR1_MM_Msk; 
	SPIx->SPICR1 |= SPI_SPICR1_MM_MASTER;
	
}

/** @defgroup HSPI_SLAVE_Init
  * @{
  */ 
void SPI_SLAVE_Init(SPI_Type* SPIx,SPI_SLAVE_InitType* SPI_SLAVE_InitStruct)
{
	SPIx->SPICR1 &= ~SPI_SPICR1_SSPA_Msk; 
	SPIx->SPICR1 |= SPI_SLAVE_InitStruct->SSPA;

	SPIx->SPICR1 &= ~SPI_SPICR1_LSBF_Msk; 
	SPIx->SPICR1 |= SPI_SLAVE_InitStruct->LSBF;
	
	SPIx->SPICR1 &= ~SPI_SPICR1_CPHOL_Msk; 
	SPIx->SPICR1 |= SPI_SLAVE_InitStruct->CPHOL;
	
	SPIx->SPICR1 &= ~SPI_SPICR1_CPHA_Msk; 
	SPIx->SPICR1 |= SPI_SLAVE_InitStruct->CPHA;
	
	SPIx->SPICR2 &= ~SPI_SPICR2_FLTEN_Msk; 
	SPIx->SPICR2 |= SPI_SLAVE_InitStruct->FLTEN;
	
	SPIx->SPICR1 &= ~SPI_SPICR1_MM_Msk; 
	SPIx->SPICR1 |= SPI_SPICR1_MM_SLAVE;
	
}

/** @defgroup SPI_GetFlagSta
  * @{
  */
ITStatus SPI_GetFlagSta(SPI_Type* SPIx,uint32_t FlagBit)
{
	ITStatus bitstatus = RESET;  
	
	if ((SPIx->SPISTA & FlagBit)== RESET)
	{
			bitstatus = RESET;
	}
	else
	{
			bitstatus = SET;
	}
	return bitstatus; 

}

/** @defgroup SPI_GetFlagSta
  * @{
  */

void SPI_ClrITStatus(SPI_Type* SPIx,uint32_t SPI_IT)
{
	SPIx->SPICR3 |= SPI_IT;	
}


/** @defgroup SPI_ReceiveData
  * @{
  */ 

uint32_t SPI_ReceiveData(SPI_Type* SPIx)
{
 
  /* Return the data in the SPIRXF register */
  return SPIx->SPIRXF;
}

/** @defgroup SPI_SendData
  * @{
  */ 

void SPI_SendData(SPI_Type* SPIx, uint32_t Data)
{
  
  /* Write in the SPITXF register the data to be sent */
  SPIx->SPITXF = Data;
}




/******END OF FILE****/

