/**
  ******************************************************************************
  * @file    system_stm32l0xx.c
  * @author  MCD Application Team
  * @version V1.7.0
  * @date    31-May-2016
  * @brief   CMSIS Cortex-M0+ Device Peripheral Access Layer System Source File.
  *
  *   This file provides two functions and one global variable to be called from 
  *   user application:
  *      - SystemInit(): This function is called at startup just after reset and 
  *                      before branch to main program. This call is made inside
  *                      the "startup_stm32l0xx.s" file.
  *
  *      - SystemCoreClock variable: Contains the core clock (HCLK), it can be used
  *                                  by the user application to setup the SysTick 
  *                                  timer or configure other parameters.
  *                                     
  *      - SystemCoreClockUpdate(): Updates the variable SystemCoreClock and must
  *                                 be called whenever the core clock is changed
  *                                 during program execution.
  *
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32l0xx_system
  * @{
  */  
  
/** @addtogroup STM32L0xx_System_Private_Includes
  * @{
  */

#include "fm32l0xx.h"
#include "system_fm32l0xx_active_config.h"
#include "system_fm32l0xx.h"

void SystemInit_Active (void)
{ 
  RCC->RCHFCON = DEF_RCHF_SEL_ACTIVE ;
  RCC->PLLCON = DEF_PLLCON_ACTIVE;
  RCC->RCLPCON = DEF_RCLPCON_ACTIVE;
  if((DEF_SYSCLKSEL_ACTIVE&3)==3)//Ñ¡ÔñPLL
  {
    while((RCC->PLLCON&(1<<7))==0);
  }
  RCC->SYSRCCSEL = DEF_SYSCLKSEL_ACTIVE ;
  RCC->XTLFIPW  = DEF_XTLFIPW_ACTIVE ;
  RCC->PERRCCCON1 = DEF_PERCLKCON1_ACTIVE;
  RCC->PERRCCCON2 = DEF_PERCLKCON2_ACTIVE;  
  RCC->PERRCCCON3 = DEF_PERCLKCON3_ACTIVE;  
  RCC->PERRCCCON4 = DEF_PERCLKCON4_ACTIVE;
  RCC->MPRIL = DEF_AHB_MASTER_ACTIVE ;
  SCB->VTOR = VTOR_ADDRESS;
  ANAC->SVDCON = 0 ;
  ANAC->SVDCFG = DEF_SVDCFG_ACTIVE;
  ANAC->SVDSIF = ANAC->SVDSIF;
  ANAC->SVDCON = DEF_SVDCON_ACTIVE ;
  RCC->RSTCFG = DEF_RSTCFG_ACTIVE;
  GPIOA->INEN = DEF_PAINEN_ACTIVE ;
  GPIOB->INEN = DEF_PBINEN_ACTIVE ;
  GPIOC->INEN = DEF_PCINEN_ACTIVE ;
  GPIOD->INEN = DEF_PDINEN_ACTIVE ;
  GPIOE->INEN = DEF_PEINEN_ACTIVE ;
  GPIOF->INEN = DEF_PFINEN_ACTIVE ;
  GPIOG->INEN = DEF_PGINEN_ACTIVE ;
  GPIOA->PUEN = DEF_PAPUEN_ACTIVE;
  GPIOB->PUEN = DEF_PBPUEN_ACTIVE;
  GPIOC->PUEN = DEF_PCPUEN_ACTIVE;
  GPIOD->PUEN = DEF_PDPUEN_ACTIVE;
  GPIOE->PUEN = DEF_PEPUEN_ACTIVE;
  GPIOF->PUEN = DEF_PFPUEN_ACTIVE;
  GPIOG->PUEN = DEF_PGPUEN_ACTIVE;
  GPIOA->ODEN = DEF_PAODEN_ACTIVE;
  GPIOB->ODEN = DEF_PBODEN_ACTIVE;
  GPIOC->ODEN = DEF_PCODEN_ACTIVE;
  GPIOD->ODEN = DEF_PDODEN_ACTIVE;
  GPIOE->ODEN = DEF_PEODEN_ACTIVE;
  GPIOF->ODEN = DEF_PFODEN_ACTIVE;
  GPIOG->ODEN = DEF_PGODEN_ACTIVE;
  GPIOA->FCR = DEF_PAFCR_ACTIVE;
  GPIOB->FCR = DEF_PBFCR_ACTIVE;
  GPIOC->FCR = DEF_PCFCR_ACTIVE;
  GPIOD->FCR = DEF_PDFCR_ACTIVE;
  GPIOE->FCR = DEF_PEFCR_ACTIVE;
  GPIOF->FCR = DEF_PFFCR_ACTIVE;
  GPIOG->FCR = DEF_PGFCR_ACTIVE;
  GPIOA->ODR = DEF_PAOUT_ACTIVE;
  GPIOB->ODR = DEF_PBOUT_ACTIVE;
  GPIOC->ODR = DEF_PCOUT_ACTIVE;
  GPIOD->ODR = DEF_PDOUT_ACTIVE;
  GPIOE->ODR = DEF_PEOUT_ACTIVE;
  GPIOF->ODR = DEF_PFOUT_ACTIVE;
  GPIOG->ODR = DEF_PGOUT_ACTIVE;
  GPIO_common->EXTI0_SEL = DEF_EXTI0SEL_ACTIVE ;
  GPIO_common->EXTI1_SEL = DEF_EXTI1SEL_ACTIVE ;
  GPIO_common->EXTI2_SEL = DEF_EXTI2SEL_ACTIVE ;
  //GPIO_common->REMAP.REMAP = DEF_REMAPSEL_ACTIVE;
  GPIO_common->HDSEL = DEF_HDSEL_ACTIVE ;
}


void SystemCoreClockUpdate_Active (void)
{
  
}


/************************ (C) COPYRIGHT FMSH *****END OF FILE****/
