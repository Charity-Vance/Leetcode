/**************************************************************************//**
 * @file     system_FM32L0XX.h
 * @brief    CMSIS Cortex-M# Device Peripheral Access Layer Header File for
 *           Device FM32L0XX
 * @version  V1.00
 * @date     11. November 2016
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


#ifndef SYSTEM_FM32L0XX_H
#define SYSTEM_FM32L0XX_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "FM32L0XX.h"
/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
/* ToDo: add here your necessary defines for device initialization
         following is an example for different system frequencies             */
#define __SYSTEM_CLOCK    (8000000)

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/
// <h> 中断向量偏移

/*
//    <o.0..31> 中断向量偏移地址<0x00000000-0xFFFFFF00:256>
//    <i> 低8bit无效
// </h>
*/
#define VTOR_ADDRESS   0x00000000

/*
   // <h>SCU DEBUG
   //  <q.0> DBG_IWDT_STOP
   //  <q.1> DBG_WWDT_STOP
   //  <q.8> DBG_BT1_STOP
   //  <q.9> DBG_BT2_STOP
   //  <q.10> DBG_ET1_STOP
   //  <q.11> DBG_ET2_STOP
   //  <q.12> DBG_ET3_STOP
   //  <q.13> DBG_ET4_STOP
   
   // </h>
   */
   #define DEF_SCU_MCUDEBUG ((uint32_t)0x00003F03U)


/*
// <h> 电源电压检测配置
*/
/*
// <h>SVD配置
//  <i>使能中断前请确保中断服务程序准备好
//    <o.0..1> SVD间歇使能间隔
//       <0=> 00 : 15.625ms
//       <1=> 01 : 62.5ms
//       <2=> 10 : 256ms
//       <3=> 11 : 1s
//    <o.2> SVD工作模式选择
//       <0=> 0 : 常使能模式
//       <1=> 1 : 间歇使能模式
//    <q.3> 数字滤波使能
//    <o.4..7> SVD报警阈值设置
//       <0=>  0000:SW0  下降 1.800V 上升 1.900V
//       <1=>  0001:SW1  下降 2.014V 上升 2.114V
//       <2=>  0010:SW2  下降 2.229V 上升 2.329V
//       <3=>  0011:SW3  下降 2.443V 上升 2.543V
//       <4=>  0100:SW4  下降 2.657V 上升 2.757V
//       <5=>  0101:SW5  下降 2.871V 上升 2.971V
//       <6=>  0110:SW6  下降 3.086V 上升 3.186V
//       <7=>  0111:SW7  下降 3.300V 上升 3.400V
//       <8=>  1000:SW8  下降 3.514V 上升 3.614V
//       <9=>  1001:SW9  下降 3.729V 上升 3.829V
//       <10=> 1010:SW10 下降 3.943V 上升 4.043V
//       <11=> 1011:SW11 下降 4.157V 上升 4.257V
//       <12=> 1100:SW12 下降 4.371V 上升 4.471V
//       <13=> 1101:SW13 下降 4.586V 上升 4.686V
//       <14=> 1110:SW14 下降 4.800V 上升 4.900V
//       <15=> 1111:SW15 下降 SVS    上升 SVS
//    <q.8> SVD电源恢复中断使能
//    <q.9> SVD电源跌落中断使能
// </h>
*/
#define DEF_SVDCFG ((uint32_t)0x000003BCU)

/*
// <h>SVD控制
//    <q.0> SVD使能
//    <q.8> SVD测试使能
// </h>
*/
#define DEF_SVDCON ((uint32_t)0x00000001U)

/*
// <h>复位配置
//    <q.0> EMC复位使能
//    <q.1> LOCKUP复位使能

// </h>
*/
#define DEF_RSTCFG ((uint32_t)0x00000000U)

/*
// </h> 电源电压配置
*/




//*** <<< end of configuration section >>>    ***

typedef int (*ConditionHook)(void);

extern uint32_t SystemCoreClock;     /*!< System Clock Frequency (Core Clock)  */


/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System and update the SystemCoreClock variable.
 */
extern void SystemInit (void);

/**
 * Update SystemCoreClock variable
 *
 * @param  none
 * @return none
 *
 * @brief  Updates the SystemCoreClock with current core Clock
 *         retrieved from cpu registers.
 */
extern void SystemCoreClockUpdate (void);


extern void TicksDelay(uint32_t ClkNum);

extern void TicksDelayMs(uint32_t ms , ConditionHook Hook);
extern void TicksDelayUs(uint32_t us);

#define DELAY_US      (__SYSTEM_CLOCK/1000000)
#define DELAY_MS      (__SYSTEM_CLOCK/1000)

__inline uint32_t SystemTicksInterval(uint32_t LastTick)
{
  return (LastTick - SysTick->VAL)&0xFFFFFF;
}
__inline uint32_t GetSystemTicks()
{
  return SysTick->VAL;
}
#define Do_DelayStart()  { \
                        uint32_t LastTick = GetSystemTicks();   do {
                        
#define While_DelayMsEnd(Count) }while(SystemTicksInterval(LastTick)<DELAY_MS*Count); \
                      }
                      
#define While_DelayUsEnd(Count) }while(SystemTicksInterval(LastTick)<DELAY_US*Count); \
                      }                      

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_MVCM3_H */
