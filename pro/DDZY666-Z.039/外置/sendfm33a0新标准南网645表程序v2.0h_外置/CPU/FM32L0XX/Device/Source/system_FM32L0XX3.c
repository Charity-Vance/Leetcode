/**************************************************************************//**
 * @file     system_<Device>.c
 * @brief    CMSIS Cortex-M# Device Peripheral Access Layer Source File for
 *           Device <Device>
 * @version  V3.10
 * @date     23. November 2012
 *
 * @note
 *
 ******************************************************************************/
/* Copyright (c) 2012 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/


#include <stdint.h>
#include <stdio.h>
#include "FM32L0XX.h"


/*----------------------------------------------------------------------------
  DEFINES
 *----------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------
  Clock Variable definitions
 *----------------------------------------------------------------------------*/
/* ToDo: initialize SystemCoreClock with the system core clock frequency value
         achieved after system intitialization.
         This means system core clock frequency after call to SystemInit()    */
uint32_t SystemCoreClock = __SYSTEM_CLOCK;  /*!< System Clock Frequency (Core Clock)*/


void TicksDelay(uint32_t ClkNum)
{
  uint32_t last = SysTick->VAL;
  if(ClkNum>0xF00000)
  {
    ClkNum = 0xF00000;
  }
  while(((last - SysTick->VAL)&0xFFFFFFUL ) <ClkNum);
}
void TicksDelayMs(uint32_t ms , ConditionHook Hook)
{
  uint32_t ClkNum;
  ClkNum = (__SYSTEM_CLOCK/1000) ;
  for(;ms>0;ms--)
  {
    if(Hook!=NULL)
    {
      if(Hook()) return ;
    }
    TicksDelay(ClkNum);
  }
}
void TicksDelayUs(uint32_t us)
{
  uint32_t ClkNum;
  if(us>100000)//²»´óÓÚ100ms
  {
    us = 100000;
  }
  ClkNum = us*(__SYSTEM_CLOCK/1000000) ;
  TicksDelay(ClkNum);
}

/*----------------------------------------------------------------------------
  Clock functions
 *----------------------------------------------------------------------------*/
void SystemCoreClockUpdate (void)            /* Get Core Clock Frequency      */
{
/* ToDo: add code to calculate the system frequency based upon the current
         register settings.
         This function can be used to retrieve the system core clock frequeny
         after user changed register sittings.                                */
  SystemCoreClock = __SYSTEM_CLOCK;
  //return;
}

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System.
 */
extern uint8_t __heap_base;
extern uint8_t __heap_limit;
extern uint8_t Wwdt_Lcd_Ctrl;
extern uint32_t HardFault_Flag;
extern uint32_t Powerd_Flag;
extern int main(void);
void SystemInit (void)
{
/* ToDo: add code to initialize the system
         do not use global variables because this function is called before
         reaching pre-main. RW section maybe overwritten afterwards.          */
  SystemCoreClock = __SYSTEM_CLOCK;
  //return;
  //memset((uint8_t*)0x20000100,0,&__heap_limit - 0x20000100);
  SysTick_Config(0x1000000UL);
  
  if( (RCC->RSTFLAG == 0x00000004) && (Powerd_Flag!=0x87654321) && (Wwdt_Lcd_Ctrl == 0x55) )
	{
		HardFault_Flag=0x11223344;
		main();
	}
}


