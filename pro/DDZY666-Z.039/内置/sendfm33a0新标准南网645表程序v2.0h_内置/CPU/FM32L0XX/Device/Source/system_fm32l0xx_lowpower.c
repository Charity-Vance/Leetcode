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
#include "system_fm32l0xx_lowpower_config.h"
#include "system_fm32l0xx.h"

void SystemInit_LowPower (void)
{ 
    RCC->RCHFCON = DEF_RCHF_SEL_LOWPOWER ;
    RCC->PLLCON = DEF_PLLCON_LOWPOWER;
    RCC->RCLPCON = DEF_RCLPCON_LOWPOWER;
    if((DEF_SYSCLKSEL_LOWPOWER&3)==3)//Ñ¡ÔñPLL
    {
      while((RCC->PLLCON&(1<<7))==0);
    }
    RCC->SYSRCCSEL = DEF_SYSCLKSEL_LOWPOWER ;
    RCC->XTLFIPW  = DEF_XTLFIPW_LOWPOWER ;
    RCC->PERRCCCON1 = DEF_PERCLKCON1_LOWPOWER;
    RCC->PERRCCCON2 = DEF_PERCLKCON2_LOWPOWER;  
    RCC->PERRCCCON3 = DEF_PERCLKCON3_LOWPOWER;  
    RCC->PERRCCCON4 = DEF_PERCLKCON4_LOWPOWER;
    RCC->MPRIL = DEF_AHB_MASTER_LOWPOWER ;
    SCB->VTOR = VTOR_ADDRESS;
    ANAC->SVDCON = 0 ;
    ANAC->SVDCFG = DEF_SVDCFG_LOWPOWER;
    ANAC->SVDSIF = ANAC->SVDSIF;
    ANAC->SVDCON = DEF_SVDCON_LOWPOWER ;
    RCC->RSTCFG = DEF_RSTCFG_LOWPOWER;
    GPIOA->INEN = DEF_PAINEN_LOWPOWER ;
    GPIOB->INEN = DEF_PBINEN_LOWPOWER ;
    GPIOC->INEN = DEF_PCINEN_LOWPOWER ;
    GPIOD->INEN = DEF_PDINEN_LOWPOWER ;
    GPIOE->INEN = DEF_PEINEN_LOWPOWER ;
    GPIOF->INEN = DEF_PFINEN_LOWPOWER ;
    GPIOG->INEN = DEF_PGINEN_LOWPOWER ;
    GPIOA->PUEN = DEF_PAPUEN_LOWPOWER;
    GPIOB->PUEN = DEF_PBPUEN_LOWPOWER;
    GPIOC->PUEN = DEF_PCPUEN_LOWPOWER;
    GPIOD->PUEN = DEF_PDPUEN_LOWPOWER;
    GPIOE->PUEN = DEF_PEPUEN_LOWPOWER;
    GPIOF->PUEN = DEF_PFPUEN_LOWPOWER;
    GPIOG->PUEN = DEF_PGPUEN_LOWPOWER;
    GPIOA->ODEN = DEF_PAODEN_LOWPOWER;
    GPIOB->ODEN = DEF_PBODEN_LOWPOWER;
    GPIOC->ODEN = DEF_PCODEN_LOWPOWER;
    GPIOD->ODEN = DEF_PDODEN_LOWPOWER;
    GPIOE->ODEN = DEF_PEODEN_LOWPOWER;
    GPIOF->ODEN = DEF_PFODEN_LOWPOWER;
    GPIOG->ODEN = DEF_PGODEN_LOWPOWER;
    GPIOA->FCR = DEF_PAFCR_LOWPOWER;
    GPIOB->FCR = DEF_PBFCR_LOWPOWER;
    GPIOC->FCR = DEF_PCFCR_LOWPOWER;
    GPIOD->FCR = DEF_PDFCR_LOWPOWER;
    GPIOE->FCR = DEF_PEFCR_LOWPOWER;
    GPIOF->FCR = DEF_PFFCR_LOWPOWER;
    GPIOG->FCR = DEF_PGFCR_LOWPOWER;
    GPIOA->ODR = DEF_PAOUT_LOWPOWER;
    GPIOB->ODR = DEF_PBOUT_LOWPOWER;
    GPIOC->ODR = DEF_PCOUT_LOWPOWER;
    GPIOD->ODR = DEF_PDOUT_LOWPOWER;
    GPIOE->ODR = DEF_PEOUT_LOWPOWER;
    GPIOF->ODR = DEF_PFOUT_LOWPOWER;
    GPIOG->ODR = DEF_PGOUT_LOWPOWER;
    GPIO_common->EXTI0_SEL = DEF_EXTI0SEL_LOWPOWER ;
    GPIO_common->EXTI1_SEL = DEF_EXTI1SEL_LOWPOWER ;
    GPIO_common->EXTI2_SEL = DEF_EXTI2SEL_LOWPOWER ;
    //GPIO_common->REMAP.REMAP = DEF_REMAPSEL_LOWPOWER;
    GPIO_common->HDSEL = DEF_HDSEL_LOWPOWER ;
  }



void SystemCoreClockUpdate_LowPower (void)
{
  
}



/************************ (C) COPYRIGHT FMSH *****END OF FILE****/

