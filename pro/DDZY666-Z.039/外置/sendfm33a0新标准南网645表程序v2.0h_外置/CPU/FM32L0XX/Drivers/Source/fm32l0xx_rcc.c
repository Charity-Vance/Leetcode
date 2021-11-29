/**
  ******************************************************************************
  * @file    fm32l0xx_rcc.c
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

/** @defgroup RCC 
  * @brief RCC driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup RCC_Private_Functions
  * @{
  */
	
/** 
 *  Returns the frequencies of different on chip clocks; SYSCLK, HCLK, 
 *         PCLK1 and PCLK2. 
 *
 */

void RCC_GetClocksFreq(RCC_ClocksType* RCC_Clocks)
{
  uint32_t tmp = 0,tmp_value = 0;

	/* Compute RCHF, PLL clocks frequencies ------------------------*/

  /* Get RCHF FSEL */
  tmp = RCC->RCHFCON & RCC_RCHFCON_FSEL_Msk;
  tmp = tmp >> RCC_RCHFCON_FSEL_Pos;  
  /* RCHF clock frequency */
  RCC_Clocks->RCHF_Frequency = __RCHF_INITIAL_CLOCK * (tmp+1);

  /* Get Pll CLK souce */
  tmp = RCC->PLLCON & RCC_PLLCON_PLLINSEL_Msk;
  tmp = tmp >> RCC_PLLCON_PLLINSEL_Pos;
	switch(tmp)
	{
		case 0x01: //01:RCLP
			tmp_value = __RCLP_CLOCK;
			break;
		case 0x02: //10:RCHF/256
			tmp_value = RCC_Clocks->RCHF_Frequency/256;
			break;
		default: //00/11:XTLF
			tmp_value = __XTLF_CLOCK;
			break;
		
	}
	
	tmp = RCC->PLLCON & RCC_PLLCON_PLLDB_Msk;
  tmp = tmp >> RCC_PLLCON_PLLDB_Pos;
	tmp = tmp * (tmp_value+1);
	
  RCC_Clocks->PLL_Frequency = tmp;
  
  /* Get SYSCLK source -------------------------------------------------------*/
  tmp = RCC->SYSRCCSEL & RCC_SYSRCCSEL_SYSRCCSEL_Msk;
	tmp = tmp >> RCC_SYSRCCSEL_SYSRCCSEL_Pos;
  switch (tmp)
  {
    case 0x00:  /* RCHF used as system clock source */
      RCC_Clocks->SYSCLK_Frequency = RCC_Clocks->RCHF_Frequency;
      break;
    case 0x01:  /* RCLP used as system clock  source */
      RCC_Clocks->SYSCLK_Frequency = __RCLP_CLOCK;
      break;
    case 0x02:  /* LSCLK used as system clock  source */
			RCC_Clocks->SYSCLK_Frequency = __XTLF_CLOCK;
      break;
		case 0x03:  /* PLL used as system clock  source */
			RCC_Clocks->SYSCLK_Frequency = RCC_Clocks->PLL_Frequency;
      break;
    default:
      RCC_Clocks->SYSCLK_Frequency = RCC_Clocks->RCHF_Frequency;
      break;
  }
	
	/* Compute AHB, APB clocks frequencies ------------------------*/

  /* Get AHB PRES */
  tmp = RCC->SYSRCCSEL & RCC_SYSRCCSEL_AHBPRES_Msk;
  tmp = tmp >> RCC_SYSRCCSEL_AHBPRES_Pos;  
  /* AHB clock frequency */
	switch(tmp)
	{
		case 0x04: //100:DIV2
			RCC_Clocks->AHBCLK_Frequency = RCC_Clocks->SYSCLK_Frequency/2;
			break;
		case 0x05: //101:DIV4
			RCC_Clocks->AHBCLK_Frequency = RCC_Clocks->SYSCLK_Frequency/4;
			break;
		case 0x06: //110:DIV8
			RCC_Clocks->AHBCLK_Frequency = RCC_Clocks->SYSCLK_Frequency/8;
			break;
		case 0x07: //111:DIV16
			RCC_Clocks->AHBCLK_Frequency = RCC_Clocks->SYSCLK_Frequency/16;
			break;
	  default: //0XX:DIV1
      RCC_Clocks->AHBCLK_Frequency = RCC_Clocks->SYSCLK_Frequency;
      break;
	}



  /* Get APB PRES */
  tmp = RCC->SYSRCCSEL & RCC_SYSRCCSEL_APBPRES_Msk;
  tmp = tmp >> RCC_SYSRCCSEL_APBPRES_Pos; 
  /* APB clock frequency */
	switch(tmp)
	{
		case 0x04: //100:DIV2
			RCC_Clocks->APBCLK_Frequency = RCC_Clocks->AHBCLK_Frequency/2;
			break;
		case 0x05: //101:DIV4
			RCC_Clocks->APBCLK_Frequency = RCC_Clocks->AHBCLK_Frequency/4;
			break;
		case 0x06: //110:DIV8
			RCC_Clocks->APBCLK_Frequency = RCC_Clocks->AHBCLK_Frequency/8;
			break;
		case 0x07: //111:DIV16
			RCC_Clocks->APBCLK_Frequency = RCC_Clocks->AHBCLK_Frequency/16;
			break;
	  default: //0XX:DIV1
      RCC_Clocks->APBCLK_Frequency = RCC_Clocks->AHBCLK_Frequency;
      break;
	}

}

/** 
 *  reset RCC register to initial state
 *
 */
void RCC_DeInit(void)
{
  /* Reset SYSRCCSEL register prescalers selection */
  RCC->SYSRCCSEL = (uint32_t)0x02000000;

  /* Reset RCHFCON register */
  RCC->RCHFCON = (uint32_t)0x00000001;

  /* Reset RCHFTRIM register*/
  RCC->RCHFTRIM = (uint32_t)0x00000040;

  /* Reset PLLCON register */
  RCC->PLLCON = (uint32_t)0x01F30000;

  /* Reset RCLPTRIM register */
  RCC->RCLPTRIM = (uint32_t)0x00000008;

  /* Reset XTLFIPW register */
  RCC->XTLFIPW = (uint32_t)0x00000000;
 
  /* Reset PERRCCCON1 register */
  RCC->PERRCCCON1 = (uint32_t)0x00000000;

  /* Reset PERRCCCON2 register */
  RCC->PERRCCCON2 = (uint32_t)0x00070000;

  /* Reset PERRCCCON3 register */
  RCC->PERRCCCON3 = (uint32_t)0x00000000; 
	
	 /* Reset PERRCCCON4 register */
  RCC->PERRCCCON4 = (uint32_t)0x00000000;
	
	/* Reset MPRIL register */
	RCC->MPRIL = (uint32_t)0x00000000;
	
}

void RCC_init(void)
{


}

/**
  * @brief  Configures the RCHF //internal High Speed oscillator (HSE).
	*	@{ RCC_RCHF_FSEL_Config(RCC_FSEL_8M);
  */
void RCC_RCHF_FSEL_Config(uint32_t fsel_set)
{
	/*RESET FSEL bits */ 
	RCC->RCHFCON &= ~RCC_RCHFCON_FSEL_Msk;
	
	/* Set the new FSEL configuration ------------------------------------------*/
	RCC->RCHFCON |= fsel_set;
}

void RCC_RCHFTRIM_Config(uint32_t rchftrim_data)
{
	/*RESET RCHFTRIM bits */ 
	RCC->RCHFTRIM &= ~RCC_RCHFTRIM_RCHFTRIM_Msk;
	
	/* Set the new RCHFTRIM configuration ------------------------------------------*/
	RCC->RCHFTRIM |= rchftrim_data;
}

void RCC_RCHF_enable(void)
{
	RCC->RCHFCON &= ~RCC_RCHFCON_RCHFEN_Msk;
	RCC->RCHFCON |= RCC_RCHFCON_RCHFEN_ON;
}

void RCC_RCHF_disable(void)
{
	RCC->RCHFCON &= ~RCC_RCHFCON_RCHFEN_Msk;
	RCC->RCHFCON |= RCC_RCHFCON_RCHFEN_OFF;
}

void RCC_PERIPH_clk_enable(Periph_Type periph_num)
{
		switch(periph_num)
		{
				//PERRCCCON1 SETTING
				case SCU_num:
					RCC->PERRCCCON1 |= RCC_PERRCCCON1_SCUCKEN_ON;
				break;				
				case PMU_num:
					RCC->PERRCCCON1 |= RCC_PERRCCCON1_PMURCCEN_ON;
				break;				
				case RTC_num:
					RCC->PERRCCCON1 |= RCC_PERRCCCON1_RTCRCCEN_ON;
				break;				
				case LPTRC_num:
					RCC->PERRCCCON1 |= RCC_PERRCCCON1_LPTRCCEN_ON;
				break;
				case LPTFC_num:
					RCC->PERRCCCON1 |= RCC_PERRCCCON1_LPTFCCEN_ON;
				break;
				case IWDT_num:
					RCC->PERRCCCON1 |= RCC_PERRCCCON1_IWDTCKEN_ON;
				break;
				case ANA_num:
					RCC->PERRCCCON1 |= RCC_PERRCCCON1_ANACKEN_ON;
				break;
				case PDC_num:
					RCC->PERRCCCON1 |= RCC_PERRCCCON1_PDCCKEN_ON;
				break;	
				case EXTI0_num:
					RCC->PERRCCCON1 |= RCC_PERRCCCON1_EXTICKEN0_ON;
				break;
				case EXTI1_num:
					RCC->PERRCCCON1 |= RCC_PERRCCCON1_EXTICKEN1_ON;
				break;				
				case EXTI2_num:
					RCC->PERRCCCON1 |= RCC_PERRCCCON1_EXTICKEN2_ON;
				break;	
				case DCU_num:
					RCC->PERRCCCON1 |= RCC_PERRCCCON1_DCUCKEN_ON;
				break;	
				
				
				//PERRCCCON2 SETTING
				case CRC_num:
					RCC->PERRCCCON2 |= RCC_PERRCCCON2_CRCCKE_ON;
				break;
				case RNG_num:
					RCC->PERRCCCON2 |= RCC_PERRCCCON2_RNGCKE_ON;
				break;
				case ADC_num:
					RCC->PERRCCCON2 |= RCC_PERRCCCON2_ADCCKE_ON;
				break;
				case LCD_num:
					RCC->PERRCCCON2 |= RCC_PERRCCCON2_LCDCKE_ON;
				break;
				case DMA_num:
					RCC->PERRCCCON2 |= RCC_PERRCCCON2_DMACKE_ON;
				break;
				case FLS_num:
					RCC->PERRCCCON2 |= RCC_PERRCCCON2_FLSCKE_ON;
				break;
				case AES_num:
					RCC->PERRCCCON2 |= RCC_PERRCCCON2_AESCKE_ON;
				break;
				case RAMBIST_num:
					RCC->PERRCCCON2 |= RCC_PERRCCCON2_RAMBISTCKE_ON;
				break;
				case WWDT_num:
					RCC->PERRCCCON2 |= RCC_PERRCCCON2_WWDTCKE_ON;
				break;
				
				
				//PERRCCCON3 SETTING
				case HSPI_num:
					RCC->PERRCCCON2 |= RCC_PERRCCCON3_HSPICKE_ON;
				break;
				case SPI1_num:
					RCC->PERRCCCON2 |= RCC_PERRCCCON3_SPI1CKE_ON;
				break;
				case SPI2_num:
					RCC->PERRCCCON2 |= RCC_PERRCCCON3_SPI2CKE_ON;
				break;
				case UART0_num:
					RCC->PERRCCCON2 |= RCC_PERRCCCON3_UART0CKE_ON;
				break;
				case UART1_num:
					RCC->PERRCCCON2 |= RCC_PERRCCCON3_UART1CKE_ON;
				break;
				case UART2_num:
					RCC->PERRCCCON2 |= RCC_PERRCCCON3_UART2CKE_ON;
				break;
				case UART3_num:
					RCC->PERRCCCON2 |= RCC_PERRCCCON3_UART3CKE_ON;
				break;
				case UART4_num:
					RCC->PERRCCCON2 |= RCC_PERRCCCON3_UART4CKE_ON;
				break;
				case UART5_num:
					RCC->PERRCCCON2 |= RCC_PERRCCCON3_UART5CKE_ON;
				break;
				case UART_COM_num:
					RCC->PERRCCCON2 |= RCC_PERRCCCON3_UARTCCKE_ON;
				break;					
				case USART0_num:
					RCC->PERRCCCON2 |= RCC_PERRCCCON3_USART0CKE_ON;
				break;
				case USART1_num:
					RCC->PERRCCCON2 |= RCC_PERRCCCON3_USART1CKE_ON;
				break;
				case I2C_num:
					RCC->PERRCCCON2 |= RCC_PERRCCCON3_I2CCKE_ON;
				break;
				
				//PERRCCCON4 SETTING
				case BT12_num:
					RCC->PERRCCCON2 |= RCC_PERRCCCON4_BT12CKE_ON;
				break;
				case BT34_num:
					RCC->PERRCCCON2 |= RCC_PERRCCCON4_BT34CKE_ON;
				break;
				case ET1_num:
					RCC->PERRCCCON2 |= RCC_PERRCCCON4_ET1CKE_ON;
				break;
				case ET2_num:
					RCC->PERRCCCON2 |= RCC_PERRCCCON4_ET2CKE_ON;
				break;
				case ET3_num:
					RCC->PERRCCCON2 |= RCC_PERRCCCON4_ET3CKE_ON;
				break;
				case ET4_num:
					RCC->PERRCCCON2 |= RCC_PERRCCCON4_ET4CKE_ON;
				break;
								
				default:
				break;
		}
}



void RCC_PERIPH_clk_disable(Periph_Type periph_num)
{
		switch(periph_num)
		{
				//PERRCCCON1 SETTING
				case SCU_num:
					RCC->PERRCCCON1 &= ~RCC_PERRCCCON1_SCUCKEN_ON;
				break;				
				case PMU_num:
					RCC->PERRCCCON1 &= ~RCC_PERRCCCON1_PMURCCEN_ON;
				break;				
				case RTC_num:
					RCC->PERRCCCON1 &= ~RCC_PERRCCCON1_RTCRCCEN_ON;
				break;				
				case LPTRC_num:
					RCC->PERRCCCON1 &= ~RCC_PERRCCCON1_LPTRCCEN_ON;
				break;
				case LPTFC_num:
					RCC->PERRCCCON1 &= ~RCC_PERRCCCON1_LPTFCCEN_ON;
				break;
				case IWDT_num:
					RCC->PERRCCCON1 &= ~RCC_PERRCCCON1_IWDTCKEN_ON;
				break;
				case ANA_num:
					RCC->PERRCCCON1 &= ~RCC_PERRCCCON1_ANACKEN_ON;
				break;
				case PDC_num:
					RCC->PERRCCCON1 &= ~RCC_PERRCCCON1_PDCCKEN_ON;
				break;
				case EXTI0_num:
					RCC->PERRCCCON1 &= ~RCC_PERRCCCON1_EXTICKEN0_ON;
				break;
				case EXTI1_num:
					RCC->PERRCCCON1 &= ~RCC_PERRCCCON1_EXTICKEN1_ON;
				break;				
				case EXTI2_num:
					RCC->PERRCCCON1 &= ~RCC_PERRCCCON1_EXTICKEN2_ON;
				break;	
				case DCU_num:
					RCC->PERRCCCON1 &= ~RCC_PERRCCCON1_DCUCKEN_ON;
				break;	
				
				//PERRCCCON2 SETTING
				case CRC_num:
					RCC->PERRCCCON2 &= ~RCC_PERRCCCON2_CRCCKE_ON;
				break;
				case RNG_num:
					RCC->PERRCCCON2 &= ~RCC_PERRCCCON2_RNGCKE_ON;
				break;
				case ADC_num:
					RCC->PERRCCCON2 &= ~RCC_PERRCCCON2_ADCCKE_ON;
				break;
				case LCD_num:
					RCC->PERRCCCON2 &= ~RCC_PERRCCCON2_LCDCKE_ON;
				break;
				case DMA_num:
					RCC->PERRCCCON2 &= ~RCC_PERRCCCON2_DMACKE_ON;
				break;
				case FLS_num:
					RCC->PERRCCCON2 &= ~RCC_PERRCCCON2_FLSCKE_ON;
				break;
				case AES_num:
					RCC->PERRCCCON2 &= ~RCC_PERRCCCON2_AESCKE_ON;
				break;
				
				//PERRCCCON3 SETTING
				case HSPI_num:
					RCC->PERRCCCON2 &= ~RCC_PERRCCCON3_HSPICKE_ON;
				break;
				case SPI1_num:
					RCC->PERRCCCON2 &= ~RCC_PERRCCCON3_SPI1CKE_ON;
				break;
				case SPI2_num:
					RCC->PERRCCCON2 &= ~RCC_PERRCCCON3_SPI2CKE_ON;
				break;
				case UART0_num:
					RCC->PERRCCCON2 &= ~RCC_PERRCCCON3_UART0CKE_ON;
				break;
				case UART1_num:
					RCC->PERRCCCON2 &= ~RCC_PERRCCCON3_UART1CKE_ON;
				break;
				case UART2_num:
					RCC->PERRCCCON2 &= ~RCC_PERRCCCON3_UART2CKE_ON;
				break;
				case UART3_num:
					RCC->PERRCCCON2 &= ~RCC_PERRCCCON3_UART3CKE_ON;
				break;
				case UART4_num:
					RCC->PERRCCCON2 &= ~RCC_PERRCCCON3_UART4CKE_ON;
				break;
				case UART5_num:
					RCC->PERRCCCON2 &= ~RCC_PERRCCCON3_UART5CKE_ON;
				break;
				case USART0_num:
					RCC->PERRCCCON2 &= ~RCC_PERRCCCON3_USART0CKE_ON;
				break;
				case USART1_num:
					RCC->PERRCCCON2 &= ~RCC_PERRCCCON3_USART1CKE_ON;
				break;
				case I2C_num:
					RCC->PERRCCCON2 &= ~RCC_PERRCCCON3_I2CCKE_ON;
				break;
				
				//PERRCCCON3 SETTING
				case BT12_num:
					RCC->PERRCCCON2 &= ~RCC_PERRCCCON4_BT12CKE_ON;
				break;
				case BT34_num:
					RCC->PERRCCCON2 &= ~RCC_PERRCCCON4_BT34CKE_ON;
				break;
				case ET1_num:
					RCC->PERRCCCON2 &= ~RCC_PERRCCCON4_ET1CKE_ON;
				break;
				case ET2_num:
					RCC->PERRCCCON2 &= ~RCC_PERRCCCON4_ET2CKE_ON;
				break;
				case ET3_num:
					RCC->PERRCCCON2 &= ~RCC_PERRCCCON4_ET3CKE_ON;
				break;
				case ET4_num:
					RCC->PERRCCCON2 &= ~RCC_PERRCCCON4_ET4CKE_ON;
				break;
								
				default:
				break;
		}
}


void RCC_PERIPH_clk_set(Periph_Type periph_num,FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		RCC_PERIPH_clk_enable(periph_num);
	}
	else
	{
		RCC_PERIPH_clk_disable(periph_num);
	}

}


/******END OF FILE****/



