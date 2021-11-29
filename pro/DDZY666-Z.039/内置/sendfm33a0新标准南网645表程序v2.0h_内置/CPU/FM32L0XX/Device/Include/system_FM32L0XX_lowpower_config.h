
#ifndef __SYSTEM_FM3XX_LOWPOWER_H
#define __SYSTEM_FM3XX_LOWPOWER_H

#ifdef __cplusplus
 extern "C" {
#endif 



/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/

/*
// <h> 电源方案和功耗管理
*/
// <h> 低功耗控制及状态

/*
//    <o.0..1> 运行模式

//       <0=> Active mode
//       <1=> LPRUN mode
//       <2=> Sleep mode
//       <3=> Stop mode
//    <q.7> PD Domain Discharge Enable(进入Stop之前将此位置1)
//    <o.8> CoreVoltageScaling配置
//       <0=> 0：低功耗模式下不使能内核电压调整
//       <1=> 1：低功耗模式下内核电压降低到1.2V
//      <i> 该位仅在Sleep/DeepSleep/Stop下起作用
//    <o.9> DeepSleep控制寄存器
//       <0=> 0：常规Sleep模式
//       <1=> 1：DeepSleep模式使能，下关闭Vref，如果DSLPRAM_EXT=1则切断RAM1和RAM2电源
//      <i> 注意:在Sleep下，如果置位了SLPDP位即为DeepSleep模式；
//      <i> 注意:该位仅在Sleep下有效
//    <o.10> DeepSleep模式下RAM1和RAM2数据保持配置位
//       <0=> 0：DeepSleep下保持RAM1和RAM2电源
//       <1=> 1：DeepSleep下关闭RAM1和RAM2电源
//      <i> 注意:该位仅在DeepSleep模式下有效
//    <o.16..17> LDO15使能标志
//       <0=> 00：无效
//       <2=> 10：LDO15使能
//      <i> 注意:该位仅在DeepSleep模式下有效
// </h>
*/

#define DEF_LPMCSR_LOWPOWER   ((uint32_t)0x00000000U) /*!<   */

// <h> 低功耗运行状态错误中断使能
/*
//    <q.0> LPRUN错误中断使能
// </h>
*/

#define DEF_LPREIE_LOWPOWER   ((uint32_t)0x00000000U) /*!<   */

// <h> 唤醒时间控制
/*
//    <o.0..1> 唤醒时间
//       <0=> 00：2us
//       <1=> 01：4us
//       <2=> 10：8us
//       <3=> 11：16us
//  <i>DeepSleep/Stop唤醒时，从BG使能到开启LDO并开始读取Flash的时间间隔
//  <i>（模式时间假设系统时钟为8MHz，如果唤醒后使用512KHz，则下述时间要乘16）
// </h>
*/

#define DEF_LPREIE_LOWPOWER   ((uint32_t)0x00000000U) /*!<   */
/*
// </h>
*/

/*
// <h> 时钟配置
*/
/*
// <h> 系统时钟配置
*/

/*
//    <o.0..1> 系统时钟源选择

//       <0=> RCHF:内部高速环振 (8M,16M,24M,32M)
         
//       <1=> RCLP:内部低频低功耗环振（32K/512K）
//       <2=> LSCLK:外部低速时钟（32768）
//       <3=> PLL:倍频时钟
//    <o.8..10> AHB时钟分频选择 
//       <0=> 0xx：不分频
//       <4=> 100：2分频
//       <5=> 101：4分频
//       <6=> 110：8分频
//       <7=> 111：16分频
//    <o.16..18> APB时钟分频选择 
//       <0=> 0xx：不分频
//       <4=> 100：2分频
//       <5=> 101：4分频
//       <6=> 110：8分频
//       <7=> 111：16分频
//       <i>APB时钟通过AHB时钟分频
//    <o.24> EXTI中断采样时钟选择 
//       <0=> 0：外部引脚中断使用AHBCLK采样
//       <1=> 1：外部引脚中断使用LSCLK采样
//       <i>建议：  在关闭所有EXTI中断的情况下设置，设置完成后再使能EXTI中断
//    <o.25> Sleep/DeepSleep模式下EXTI采样设置 
//       <0=> 0：Sleep/DeepSleep模式下禁止外部引脚中断采样（将无法产生EXTI中断）
//       <1=> 1：Sleep/DeepSleep模式下使能外部引脚中断采样（采样时钟为LSCLK）
//    <o.26> 休眠唤醒后默认时钟选择 
//       <0=> 0：唤醒后使用RCHF 8MHz
//       <1=> 1：唤醒后使用RCLP 512KHz
//    <o.31> Sleep/Stop模式下禁止RCLP，仅在无晶体配置下有效
//       <0=> 0：休眠模式下保持RCLP开启
//       <1=> 1：休眠模式下关闭RCLP
//    <i> 无晶体方案中，在休眠模式下关闭RCLP，RTC、IWDT、SVD间歇工作模式都将无法使用，芯片只能通过NWKUPx引脚异步唤醒，或者使用LPTIM的外部时钟计数方式唤醒。
// </h>
*/

#define DEF_SYSCLKSEL_LOWPOWER   ((uint32_t)0x80040700U) /*!<   */



/*
// <h> RCHF时钟配置
//    <e.0> 使能内部高速时钟
//    <o.16..17> 内部高速时钟选择 [Hz]
//       <0=> 8MHz
//       <1=> 16MHz
//       <2=> 24MHz
//       <3=> 32MHz
//    <i> 内部高速时钟
//    <i> 唤醒默认: 8MHz
//    <i> 出厂调校常温+/-0.5% 
//    </e>
// </h>
*/

#define DEF_RCHF_SEL_LOWPOWER      ((uint32_t)0x00030001U) /*!< 片内高频时钟频率倍频选择 */
#define DEF_RCHF_VALUE_LOWPOWER    ((uint32_t)8000000*(((DEF_RCHF_SEL>>16)&0X3)+1)) /*!< 片内高频时钟频率 */

/*
// <h> PLL时钟配置
//    <e.0> 使能PLL
//    <o.1..2> PLL输入选择寄存器
//       <0=> XTLF
//       <1=> RCLP
//       <2=> RCHF/256
//       <3=> XTLF
//    <o.16..25>  PLL倍频比(0-1023) <0-1023>
//    </e>
// </h>
*/
#define DEF_PLLCON_LOWPOWER ((uint32_t)0x00000003U)
/*
// <h> RCLP时钟控制
//    <o.0> 使能RCLP
//       <0=> RCLP开启
//       <1=> RCLP处于关闭状态
//    <i>【注1】唤醒时，异步开启
//    <i>【注2】有晶振产品XTLF停振时，异步开启
//    <i>【注3】非Sleep/Stop时，常开
//    <i>【注4】进Sleep/Stop，根据LPM_RCLPOFF寄存器决定开关
//    <i>【注5】 Sleep/Stop 时，若为无晶振产品，且LPM_RCLPOFF为1，则当TESTN/NRSTN引脚为低时，开启RCLP
//    <i>【注6】Sleep/Stop 时，对有晶振产品，若LPM_RCLPOFF和PMU.XTOFF均为1，则当TESTN/NRSTN引脚为低时，开启RCLP
//    <i>【注7】Sleep/Stop 时，对有晶振产品，若LPM_RCLPOFF为1，PMU.XTOFF为0，则当TESTN/NRSTN引脚为低时，依然保持RCLP关闭 

//    <o.16> RCLP高速输出使能
//       <0=> RCLP高速（512K）输出
//       <1=> RCLP低速（32K）输出
//    <i>【注1】唤醒时，异步置位为512K
// </h>
*/
#define DEF_RCLPCON_LOWPOWER ((uint32_t)0x00000000U)

/*
// <h> XTLF振荡强度配置
//    <o.0..2> XTLF工作电流选择
//       <0=> 000 : 450 nA
//       <1=> 001 : 400 nA
//       <2=> 010 : 350 nA
//       <3=> 011 : 300 nA
//       <4=> 100 : 250 nA(推荐)
//       <5=> 101 : 200 nA(推荐)
//       <6=> 110 : 150 nA
//       <7=> 111 : 100 nA
//      <i>电流越大表示振荡强度越高
// </h>
*/
#define DEF_XTLFIPW_LOWPOWER ((uint32_t)0x00000004U)

// <h>外设时钟控制
/*
// <h>外设时钟控制1
//    <q.0> LPTIM总线时钟使能
//    <q.1> RTC总线时钟使能
//    <q.2> PMU总线时钟使能
//    <q.3> SVD工作时钟使能
// </h>
*/
#define DEF_PERCLKCON1_LOWPOWER ((uint32_t)0x00000003U)
/*
// <h>外设时钟控制2
//    <q.0> CRC时钟使能
//    <q.1> RNG时钟使能
//    <q.2> ADC时钟使能
//    <q.3> LCD时钟使能
//    <q.4> DMA时钟使能
//    <q.5> FLSC（Flash擦写控制器）时钟使能
//    <q.6> AES时钟使能
//    <o.16..18> ADC工作时钟选择
//       <0=> 000 : RCHF
//       <1=> 001 : RCHF/2
//       <2=> 010 : RCHF/4
//       <3=> 011 : RCHF/8
//       <4=> 100 : RCHF/16
//       <5=> 101 : RCHF/32
//       <6=> 110 : RCHF/64
//       <7=> 111 : RCLP

// </h>
*/
#define DEF_PERCLKCON2_LOWPOWER ((uint32_t)0x00000003U)

/*
// <h>外设时钟控制3
//    <q.0> SPI0时钟使能
//    <q.1> SPI1时钟使能
//    <q.2> SPI2时钟使能
//    <q.8> UART0时钟使能
//    <q.9> UART1时钟使能
//    <q.10> UART2时钟使能
//    <q.11> UART3时钟使能
//    <q.12> UART4时钟使能
//    <q.13> UART5时钟使能
//    <q.16> USART0时钟使能
//    <q.17> USART1时钟使能
//    <q.24> I2C时钟使能
// </h>
*/
#define DEF_PERCLKCON3_LOWPOWER ((uint32_t)0x00000003U)

/*
// <h>外设时钟控制4
//    <q.0> BT12时钟使能
//    <q.1> BT34时钟使能
//    <q.2> ET1时钟使能
//    <q.3> ET2时钟使能
//    <q.4> ET3时钟使能
//    <q.5> ET4时钟使能
// </h>
*/
#define DEF_PERCLKCON4_LOWPOWER ((uint32_t)0x00000000U)


/*
// <h>AHB Master控制寄存器
//    <o.0> PortA时钟使能
//       <0=> DMA优先
//       <1=> CPU优先
//    <i>【注1】该寄存器和其它寄存器地址不连续
//    <i>【注2】该寄存器被改写时，将会拉低1拍HREADYOUT给BUSMATRIX

// </h>
*/
#define DEF_AHB_MASTER_LOWPOWER ((uint32_t)0x00000000U)
// </h>

// </h>

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
#define DEF_SVDCFG_LOWPOWER ((uint32_t)0x00000000U)

/*
// <h>SVD控制
//    <q.0> SVD使能
//    <q.8> SVD测试使能
// </h>
*/
#define DEF_SVDCON_LOWPOWER ((uint32_t)0x00000000U)


/*
// <h>复位配置
//    <q.0> EMC复位使能
//    <q.1> LOCKUP复位使能

// </h>
*/
#define DEF_RSTCFG_LOWPOWER ((uint32_t)0x00000000U)

/*
// </h> 电源电压配置
*/
/*
// <h> GPIO控制
*/
  /*
  // <h>GPIO输入使能
  */
    /*
    // <h>GPIOA
    //  <q.0> PIN0
    //  <q.1> PIN1
    //  <q.2> PIN2
    //  <q.3> PIN3
    //  <q.4> PIN4
    //  <q.5> PIN5
    //  <q.6> PIN6
    //  <q.7> PIN7
    //  <q.8> PIN8
    //  <q.9> PIN9
    //  <q.10> PIN10
    //  <q.11> PIN11
    //  <q.12> PIN12
    //  <q.13> PIN13
    //  <q.14> PIN14
    //  <q.15> PIN15
    // </h>
    */
    #define DEF_PAINEN_LOWPOWER ((uint32_t)0x00000003U)
    /*
    // <h>GPIOB
    //  <q.0> PIN0
    //  <q.1> PIN1
    //  <q.2> PIN2
    //  <q.3> PIN3
    //  <q.4> PIN4
    //  <q.5> PIN5
    //  <q.6> PIN6
    //  <q.7> PIN7
    //  <q.8> PIN8
    //  <q.9> PIN9
    //  <q.10> PIN10
    //  <q.11> PIN11
    //  <q.12> PIN12
    //  <q.13> PIN13
    //  <q.14> PIN14
    //  <q.15> PIN15
    // </h>
    */
    #define DEF_PBINEN_LOWPOWER ((uint32_t)0x00000000U)
    /*
    // <h>GPIOC
    //  <q.0> PIN0
    //  <q.1> PIN1
    //  <q.2> PIN2
    //  <q.3> PIN3
    //  <q.4> PIN4
    //  <q.5> PIN5
    //  <q.6> PIN6
    //  <q.7> PIN7
    //  <q.8> PIN8
    //  <q.9> PIN9
    //  <q.10> PIN10
    //  <q.11> PIN11
    //  <q.12> PIN12
    //  <q.13> PIN13
    //  <q.14> PIN14
    //  <q.15> PIN15
    // </h>
    */
    #define DEF_PCINEN_LOWPOWER ((uint32_t)0x00000000U)
    /*
    // <h>GPIOD
    //  <q.0> PIN0
    //  <q.1> PIN1
    //  <q.2> PIN2
    //  <q.3> PIN3
    //  <q.4> PIN4
    //  <q.5> PIN5
    //  <q.6> PIN6
    //  <q.7> PIN7
    //  <q.8> PIN8
    //  <q.9> PIN9
    //  <q.10> PIN10
    //  <q.11> PIN11
    //  <q.12> PIN12
    //  <q.13> PIN13
    //  <q.14> PIN14
    //  <q.15> PIN15
    // </h>
    */
    #define DEF_PDINEN_LOWPOWER ((uint32_t)0x00000000U)
    /*
    // <h>GPIOE
    //  <q.0> PIN0
    //  <q.1> PIN1
    //  <q.2> PIN2
    //  <q.3> PIN3
    //  <q.4> PIN4
    //  <q.5> PIN5
    //  <q.6> PIN6
    //  <q.7> PIN7
    //  <q.8> PIN8
    //  <q.9> PIN9
    //  <q.10> PIN10
    //  <q.11> PIN11
    //  <q.12> PIN12
    //  <q.13> PIN13
    //  <q.14> PIN14
    //  <q.15> PIN15
    // </h>
    */
    #define DEF_PEINEN_LOWPOWER ((uint32_t)0x00000000U)
    /*
    // <h>GPIOF
    //  <q.0> PIN0
    //  <q.1> PIN1
    //  <q.2> PIN2
    //  <q.3> PIN3
    //  <q.4> PIN4
    //  <q.5> PIN5
    //  <q.6> PIN6
    //  <q.7> PIN7
    //  <q.8> PIN8
    //  <q.9> PIN9
    //  <q.10> PIN10
    //  <q.11> PIN11
    //  <q.12> PIN12
    //  <q.13> PIN13
    //  <q.14> PIN14
    //  <q.15> PIN15
    // </h>
    */
    #define DEF_PFINEN_LOWPOWER ((uint32_t)0x00000000U)
    /*
    // <h>GPIOG
    //  <q.0> PIN0
    //  <q.1> PIN1
    //  <q.2> PIN2
    //  <q.3> PIN3
    //  <q.4> PIN4
    //  <q.5> PIN5
    //  <q.6> PIN6
    //  <q.7> PIN7
    //  <q.8> PIN8
    //  <q.9> PIN9
    //  <q.10> PIN10
    //  <q.11> PIN11
    //  <q.12> PIN12
    //  <q.13> PIN13
    //  <q.14> PIN14
    //  <q.15> PIN15
    // </h>
    */
    #define DEF_PGINEN_LOWPOWER ((uint32_t)0x00000000U)
    
    
  /*
  // </h>
  */
  /*
  // <h>GPIO上拉使能
  */
    /*
    // <h>GPIOA
    //  <q.0> PIN0
    //  <q.1> PIN1
    //  <q.2> PIN2
    //  <q.3> PIN3
    //  <q.4> PIN4
    //  <q.5> PIN5
    //  <q.6> PIN6
    //  <q.7> PIN7
    //  <q.8> PIN8
    //  <q.9> PIN9
    //  <q.10> PIN10
    //  <q.11> PIN11
    //  <q.12> PIN12
    //  <q.13> PIN13
    //  <q.14> PIN14
    //  <q.15> PIN15
    // </h>
    */
    #define DEF_PAPUEN_LOWPOWER ((uint32_t)0x00000000U)
    /*
    // <h>GPIOB
    //  <q.0> PIN0
    //  <q.1> PIN1
    //  <q.2> PIN2
    //  <q.3> PIN3
    //  <q.4> PIN4
    //  <q.5> PIN5
    //  <q.6> PIN6
    //  <q.7> PIN7
    //  <q.8> PIN8
    //  <q.9> PIN9
    //  <q.10> PIN10
    //  <q.11> PIN11
    //  <q.12> PIN12
    //  <q.13> PIN13
    //  <q.14> PIN14
    //  <q.15> PIN15
    // </h>
    */
    #define DEF_PBPUEN_LOWPOWER ((uint32_t)0x00000000U)
    /*
    // <h>GPIOC
    //  <q.0> PIN0
    //  <q.1> PIN1
    //  <q.2> PIN2
    //  <q.3> PIN3
    //  <q.4> PIN4
    //  <q.5> PIN5
    //  <q.6> PIN6
    //  <q.7> PIN7
    //  <q.8> PIN8
    //  <q.9> PIN9
    //  <q.10> PIN10
    //  <q.11> PIN11
    //  <q.12> PIN12
    //  <q.13> PIN13
    //  <q.14> PIN14
    //  <q.15> PIN15
    // </h>
    */
    #define DEF_PCPUEN_LOWPOWER ((uint32_t)0x00000000U)
    /*
    // <h>GPIOD
    //  <q.0> PIN0
    //  <q.1> PIN1
    //  <q.2> PIN2
    //  <q.3> PIN3
    //  <q.4> PIN4
    //  <q.5> PIN5
    //  <q.6> PIN6
    //  <q.7> PIN7
    //  <q.8> PIN8
    //  <q.9> PIN9
    //  <q.10> PIN10
    //  <q.11> PIN11
    //  <q.12> PIN12
    //  <q.13> PIN13
    //  <q.14> PIN14
    //  <q.15> PIN15
    // </h>
    */
    #define DEF_PDPUEN_LOWPOWER ((uint32_t)0x00000000U)
    /*
    // <h>GPIOE
    //  <q.0> PIN0
    //  <q.1> PIN1
    //  <q.2> PIN2
    //  <q.3> PIN3
    //  <q.4> PIN4
    //  <q.5> PIN5
    //  <q.6> PIN6
    //  <q.7> PIN7
    //  <q.8> PIN8
    //  <q.9> PIN9
    //  <q.10> PIN10
    //  <q.11> PIN11
    //  <q.12> PIN12
    //  <q.13> PIN13
    //  <q.14> PIN14
    //  <q.15> PIN15
    // </h>
    */
    #define DEF_PEPUEN_LOWPOWER ((uint32_t)0x00000000U)
    /*
    // <h>GPIOF
    //  <q.0> PIN0
    //  <q.1> PIN1
    //  <q.2> PIN2
    //  <q.3> PIN3
    //  <q.4> PIN4
    //  <q.5> PIN5
    //  <q.6> PIN6
    //  <q.7> PIN7
    //  <q.8> PIN8
    //  <q.9> PIN9
    //  <q.10> PIN10
    //  <q.11> PIN11
    //  <q.12> PIN12
    //  <q.13> PIN13
    //  <q.14> PIN14
    //  <q.15> PIN15
    // </h>
    */
    #define DEF_PFPUEN_LOWPOWER ((uint32_t)0x00000000U)
    /*
    // <h>GPIOG
    //  <q.0> PIN0
    //  <q.1> PIN1
    //  <q.2> PIN2
    //  <q.3> PIN3
    //  <q.4> PIN4
    //  <q.5> PIN5
    //  <q.6> PIN6
    //  <q.7> PIN7
    //  <q.8> PIN8
    //  <q.9> PIN9
    //  <q.10> PIN10
    //  <q.11> PIN11
    //  <q.12> PIN12
    //  <q.13> PIN13
    //  <q.14> PIN14
    //  <q.15> PIN15
    // </h>
    */
    #define DEF_PGPUEN_LOWPOWER ((uint32_t)0x00000000U)
    
    
  /*
  // </h>
  */
  /*
  // <h>GPIO开漏使能
  */
    /*
    // <h>GPIOA
    //  <q.0> PIN0
    //  <q.1> PIN1
    //  <q.2> PIN2
    //  <q.3> PIN3
    //  <q.4> PIN4
    //  <q.5> PIN5
    //  <q.6> PIN6
    //  <q.7> PIN7
    //  <q.8> PIN8
    //  <q.9> PIN9
    //  <q.10> PIN10
    //  <q.11> PIN11
    //  <q.12> PIN12
    //  <q.13> PIN13
    //  <q.14> PIN14
    //  <q.15> PIN15
    // </h>
    */
    #define DEF_PAODEN_LOWPOWER ((uint32_t)0x00000000U)
    /*
    // <h>GPIOB
    //  <q.0> PIN0
    //  <q.1> PIN1
    //  <q.2> PIN2
    //  <q.3> PIN3
    //  <q.4> PIN4
    //  <q.5> PIN5
    //  <q.6> PIN6
    //  <q.7> PIN7
    //  <q.8> PIN8
    //  <q.9> PIN9
    //  <q.10> PIN10
    //  <q.11> PIN11
    //  <q.12> PIN12
    //  <q.13> PIN13
    //  <q.14> PIN14
    //  <q.15> PIN15
    // </h>
    */
    #define DEF_PBODEN_LOWPOWER ((uint32_t)0x00000000U)
    /*
    // <h>GPIOC
    //  <q.0> PIN0
    //  <q.1> PIN1
    //  <q.2> PIN2
    //  <q.3> PIN3
    //  <q.4> PIN4
    //  <q.5> PIN5
    //  <q.6> PIN6
    //  <q.7> PIN7
    //  <q.8> PIN8
    //  <q.9> PIN9
    //  <q.10> PIN10
    //  <q.11> PIN11
    //  <q.12> PIN12
    //  <q.13> PIN13
    //  <q.14> PIN14
    //  <q.15> PIN15
    // </h>
    */
    #define DEF_PCODEN_LOWPOWER ((uint32_t)0x00000000U)
    /*
    // <h>GPIOD
    //  <q.0> PIN0
    //  <q.1> PIN1
    //  <q.2> PIN2
    //  <q.3> PIN3
    //  <q.4> PIN4
    //  <q.5> PIN5
    //  <q.6> PIN6
    //  <q.7> PIN7
    //  <q.8> PIN8
    //  <q.9> PIN9
    //  <q.10> PIN10
    //  <q.11> PIN11
    //  <q.12> PIN12
    //  <q.13> PIN13
    //  <q.14> PIN14
    //  <q.15> PIN15
    // </h>
    */
    #define DEF_PDODEN_LOWPOWER ((uint32_t)0x00000000U)
    /*
    // <h>GPIOE
    //  <q.0> PIN0
    //  <q.1> PIN1
    //  <q.2> PIN2
    //  <q.3> PIN3
    //  <q.4> PIN4
    //  <q.5> PIN5
    //  <q.6> PIN6
    //  <q.7> PIN7
    //  <q.8> PIN8
    //  <q.9> PIN9
    //  <q.10> PIN10
    //  <q.11> PIN11
    //  <q.12> PIN12
    //  <q.13> PIN13
    //  <q.14> PIN14
    //  <q.15> PIN15
    // </h>
    */
    #define DEF_PEODEN_LOWPOWER ((uint32_t)0x00000000U)
    /*
    // <h>GPIOF
    //  <q.0> PIN0
    //  <q.1> PIN1
    //  <q.2> PIN2
    //  <q.3> PIN3
    //  <q.4> PIN4
    //  <q.5> PIN5
    //  <q.6> PIN6
    //  <q.7> PIN7
    //  <q.8> PIN8
    //  <q.9> PIN9
    //  <q.10> PIN10
    //  <q.11> PIN11
    //  <q.12> PIN12
    //  <q.13> PIN13
    //  <q.14> PIN14
    //  <q.15> PIN15
    // </h>
    */
    #define DEF_PFODEN_LOWPOWER ((uint32_t)0x00000000U)
    /*
    // <h>GPIOG
    //  <q.0> PIN0
    //  <q.1> PIN1
    //  <q.2> PIN2
    //  <q.3> PIN3
    //  <q.4> PIN4
    //  <q.5> PIN5
    //  <q.6> PIN6
    //  <q.7> PIN7
    //  <q.8> PIN8
    //  <q.9> PIN9
    //  <q.10> PIN10
    //  <q.11> PIN11
    //  <q.12> PIN12
    //  <q.13> PIN13
    //  <q.14> PIN14
    //  <q.15> PIN15
    // </h>
    */
    #define DEF_PGODEN_LOWPOWER ((uint32_t)0x00000000U)
    
    
  /*
  // </h>
  */
  /*
  // <h>GPIO功能选择使能
  */
    /*
    // <h>GPIOA
    //  <o.0..1> PIN0  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：COM0
    //  <o.2..3> PIN1  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：COM1
    //  <o.4..5> PIN2  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：COM2
    //  <o.6..7> PIN3  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：COM3
    //  <o.8..9> PIN4  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：COM4/SEG40
    //  <o.10..11> PIN5  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：COM5/SEG41
    //  <o.12..13> PIN6  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：COM6/SEG42
    //  <o.14..15> PIN7  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：COM7/SEG43
    //  <o.16..17> PIN8  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：BT1_IN2
    //    <3=> 11：SEG0
    //  <o.18..19> PIN9  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：BT2_IN2
    //    <3=> 11：SEG1
    //  <o.20..21> PIN10  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：BT2_OUT
    //    <3=> 11：SEG2
    //  <o.22..24> PIN11  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：LPTI
    //    <3=> 11：SEG3
    //  <o.24..25> PIN12  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：LPTO
    //    <3=> 11：SEG4
    //  <o.26..27> PIN13  
    //    <0=> 00：GPIO输入(NWKUP4)
    //    <1=> 01：GPIO输出
    //    <2=> 10：LPTRG
    //    <3=> 11：SEG5
    //  <o.28..29> PIN14  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：SCL
    //    <3=> 11：模拟功能
    //  <o.30..31> PIN15  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：SDA
    //    <3=> 11：模拟功能
    // </h>
    */
    #define DEF_PAFCR_LOWPOWER ((uint32_t)0x00000000U)
    /*
    // <h>GPIOB
    //  <o.0..1> PIN0  
    //    <0=> 00：GPIO输入(NWKUP1)
    //    <1=> 01：GPIO输出
    //    <2=> 10：UART1_RX
    //    <3=> 11：模拟功能
    //  <o.2..3> PIN1  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：UART1_TX
    //    <3=> 11：模拟功能
    //  <o.4..5> PIN2  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：UART2_RX
    //    <3=> 11：模拟功能
    //  <o.6..7> PIN3  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：UART2_TX
    //    <3=> 11：模拟功能
    //  <o.8..9> PIN4  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：BT1_IN0
    //    <3=> 11：SEG6
    //  <o.10..11> PIN5  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：BT2_IN0
    //    <3=> 11：SEG7
    //  <o.12..13> PIN6  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：BT1_OUT
    //    <3=> 11：SEG8
    //  <o.14..15> PIN7  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：ET1_IN0
    //    <3=> 11：SEG9
    //  <o.16..17> PIN8  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：ET2_IN0
    //    <3=> 11：SEG10
    //  <o.18..19> PIN9  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：ET3_IN0
    //    <3=> 11：SEG11
    //  <o.20..21> PIN10  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：ET4_IN0
    //    <3=> 11：SEG12
    //  <o.22..24> PIN11  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：ET1_OUT
    //    <3=> 11：SEG13
    //  <o.24..25> PIN12  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：SPI1_SSN
    //    <3=> 11：SEG14
    //  <o.26..27> PIN13  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：SPI1_SCK
    //    <3=> 11：SEG15
    //  <o.28..29> PIN14  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：SPI1_MISO
    //    <3=> 11：SEG16
    //  <o.30..31> PIN15  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：SPI1_MOSI
    //    <3=> 11：SEG17
    // </h>
    */
    #define DEF_PBFCR_LOWPOWER ((uint32_t)0x00000000U)
    /*
    // <h>GPIOC
    //  <o.0..1> PIN0  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：U7816CLK0
    //    <3=> 11：SEG24
    //  <o.2..3> PIN1  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：U7816IO0
    //    <3=> 11：SEG25
    //  <o.4..5> PIN2  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：U7816CLK1
    //    <3=> 11：SEG26
    //  <o.6..7> PIN3  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：U7816IO1
    //    <3=> 11：SEG27
    //  <o.8..9> PIN4  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：UART5_RX
    //    <3=> 11：SEG28
    //  <o.10..11> PIN5  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：UART5_TX
    //    <3=> 11：SEG29
    //  <o.12..13> PIN6  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：SPI1_SSN
    //    <3=> 11：SEG30
    //  <o.14..15> PIN7  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：SPI1_SCK
    //    <3=> 11：SEG31
    //  <o.16..17> PIN8  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：SPI1_MISO
    //    <3=> 11：SEG32
    //  <o.18..19> PIN9  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：SPI1_MOSI
    //    <3=> 11：SEG33
    //  <o.20..21> PIN10  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：UART3_RX
    //    <3=> 11：SEG34
    //  <o.22..24> PIN11  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：UART3_TX
    //    <3=> 11：SEG35
    //  <o.24..25> PIN12  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：ADC_IN5
    //    <3=> 11：SEG36
    //  <o.26..27> PIN13  
    //    <0=> 00：GPIO输入(NWKUP2)
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：SEG37/ADC_IN6
    //  <o.28..29> PIN14  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：SEG38/ACMP1_INN0
    //  <o.30..31> PIN15  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：SEG39/ACMP1_INP0
    // </h>
    */
    #define DEF_PCFCR_LOWPOWER ((uint32_t)0x00000000U)
    /*
    // <h>GPIOD
    //  <o.0..1> PIN0  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：UART4_RX
    //    <3=> 11：ADC_IN3
    //  <o.2..3> PIN1  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：UART4_TX
    //    <3=> 11：ADC_IN4
    //  <o.4..5> PIN2  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：SPI2_SSN
    //    <3=> 11：SEG20
    //  <o.6..7> PIN3  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：SPI2_SCK
    //    <3=> 11：SEG21
    //  <o.8..9> PIN4  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：SPI2_MISO
    //    <3=> 11：SEG22
    //  <o.10..11> PIN5  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：SPI2_MOSI
    //    <3=> 11：SEG23
    //  <o.12..13> PIN6  
    //    <0=> 00：GPIO输入(NWKUP7)
    //    <1=> 01：GPIO输出
    //    <2=> 10：ET3_IN1
    //    <3=> 11：模拟功能
    //  <o.14..15> PIN7  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：ET4_IN1
    //    <3=> 11：ADC_IN1
    //  <o.16..17> PIN8  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：ET3_OUT
    //    <3=> 11：ADC_IN2
    //  <o.18..19> PIN9  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：UART4_RX
    //    <3=> 11：模拟功能
    //  <o.20..21> PIN10  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：UART4_TX
    //    <3=> 11：模拟功能
    //  <o.22..24> PIN11  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：模拟功能
    //  <o.24..25> PIN12  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：模拟功能
    //  <o.26..27> PIN13  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：模拟功能
    //  <o.28..29> PIN14  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：模拟功能
    //  <o.30..31> PIN15  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：模拟功能
    // </h>
    */
    #define DEF_PDFCR_LOWPOWER ((uint32_t)0x00000000U)
    /*
    // <h>GPIOE
    //  <o.0..1> PIN0  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：模拟功能
    //  <o.2..3> PIN1  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：模拟功能
    //  <o.4..5> PIN2  
    //    <0=> 00：GPIO输入(NWKUP5)
    //    <1=> 01：GPIO输出
    //    <2=> 10：ET1_IN1
    //    <3=> 11：模拟功能
    //  <o.6..7> PIN3  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：UART1_RX
    //    <3=> 11：ACMP1_INN1/SEG18
    //  <o.8..9> PIN4  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：UART1_TX
    //    <3=> 11：ACMP1_INP1/SEG19
    //  <o.10..11> PIN5  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：SCL
    //    <3=> 11：模拟功能
    //  <o.12..13> PIN6  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：SDA
    //    <3=> 11：模拟功能
    //  <o.14..15> PIN7  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：ET2_IN2
    //    <3=> 11：VCIN1
    //  <o.16..17> PIN8  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：LPTO
    //    <3=> 11：VCIN2
    //  <o.18..19> PIN9  
    //    <0=> 00：GPIO输入(NWKUP6)
    //    <1=> 01：GPIO输出
    //    <2=> 10：RMAP3
    //    <3=> 11：模拟功能
    //  <o.20..21> PIN10  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：模拟功能
    //  <o.22..24> PIN11  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：模拟功能
    //  <o.24..25> PIN12  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：模拟功能
    //  <o.26..27> PIN13  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：模拟功能
    //  <o.28..29> PIN14  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：模拟功能
    //  <o.30..31> PIN15  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：模拟功能
    // </h>
    */
    #define DEF_PEFCR_LOWPOWER ((uint32_t)0x00000000U)
    /*
    // <h>GPIOF
    //  <o.0..1> PIN0  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：ET2_OUT
    //    <3=> 11：ACMP0_INN1
    //  <o.2..3> PIN1  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：RMAP2
    //    <3=> 11：ACMP0_INP1
    //  <o.4..5> PIN2  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：VLCD(ANTST)
    //  <o.6..7> PIN3  
    //    <0=> 00：GPIO输入(BOOT0)
    //    <1=> 01：GPIO输出
    //    <2=> 10：UART0_RX
    //    <3=> 11：模拟功能
    //  <o.8..9> PIN4  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：UART0_TX
    //    <3=> 11：模拟功能
    //  <o.10..11> PIN5  
    //    <0=> 00：GPIO输入(NWKUP0)
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：ACMP0_INN0
    //  <o.12..13> PIN6  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：ACMP0_INP0
    //  <o.14..15> PIN7  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：ADC_IN7
    //  <o.16..17> PIN8  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：ADC_IN8
    //  <o.18..19> PIN9  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：BT1_IN1
    //    <3=> 11：模拟功能
    //  <o.20..21> PIN10  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：BT2_IN1
    //    <3=> 11：模拟功能
    //  <o.22..24> PIN11  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：RMAP1
    //    <3=> 11：模拟功能
    //  <o.24..25> PIN12  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：模拟功能
    //  <o.26..27> PIN13  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：模拟功能
    //  <o.28..29> PIN14  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：模拟功能
    //  <o.30..31> PIN15  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：模拟功能
    // </h>
    */
    #define DEF_PFFCR_LOWPOWER ((uint32_t)0x00000000U)
    /*
    // <h>GPIOG
    //  <o.0..1> PIN0  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：模拟功能
    //  <o.2..3> PIN1  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：模拟功能
    //  <o.4..5> PIN2  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：U7816CLK0
    //    <3=> 11：ACMP0_INP2
    //  <o.6..7> PIN3  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：U7816IO0
    //    <3=> 11：ACMP0_INP3
    //  <o.8..9> PIN4  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：ET1_IN2
    //    <3=> 11：模拟功能
    //  <o.10..11> PIN5  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：ET2_IN2
    //    <3=> 11：模拟功能
    //  <o.12..13> PIN6  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：FOUT
    //    <3=> 11：模拟功能
    //  <o.14..15> PIN7  
    //    <0=> 00：GPIO输入(NWKUP3)
    //    <1=> 01：GPIO输出
    //    <2=> 10：ET4_OUT
    //    <3=> 11：模拟功能
    //  <o.16..17> PIN8  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：模拟功能
    //  <o.18..19> PIN9  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：模拟功能
    //  <o.20..21> PIN10  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：模拟功能
    //  <o.22..24> PIN11  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：数字特殊功能
    //    <3=> 11：模拟功能
    //  <o.24..25> PIN12  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：SPI0_MOSI
    //    <3=> 11：VDISP0
    //  <o.26..27> PIN13  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：SPI0_MISO
    //    <3=> 11：VDISP1
    //  <o.28..29> PIN14  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：SPI0_SCK
    //    <3=> 11：VDISP2
    //  <o.30..31> PIN15  
    //    <0=> 00：GPIO输入
    //    <1=> 01：GPIO输出
    //    <2=> 10：SPI0_SSN
    //    <3=> 11：VDISP3
    // </h>
    */
    #define DEF_PGFCR_LOWPOWER ((uint32_t)0x00000000U)
    
    
  /*
  // </h>
  */
  /*
  // <h>GPIO输出(选中置位)
  */
    /*
    // <h>GPIOA
    //  <q.0> PIN0
    //  <q.1> PIN1
    //  <q.2> PIN2
    //  <q.3> PIN3
    //  <q.4> PIN4
    //  <q.5> PIN5
    //  <q.6> PIN6
    //  <q.7> PIN7
    //  <q.8> PIN8
    //  <q.9> PIN9
    //  <q.10> PIN10
    //  <q.11> PIN11
    //  <q.12> PIN12
    //  <q.13> PIN13
    //  <q.14> PIN14
    //  <q.15> PIN15
    // </h>
    */
    #define DEF_PAOUT_LOWPOWER ((uint32_t)0x00000000U)
    /*
    // <h>GPIOB
    //  <q.0> PIN0
    //  <q.1> PIN1
    //  <q.2> PIN2
    //  <q.3> PIN3
    //  <q.4> PIN4
    //  <q.5> PIN5
    //  <q.6> PIN6
    //  <q.7> PIN7
    //  <q.8> PIN8
    //  <q.9> PIN9
    //  <q.10> PIN10
    //  <q.11> PIN11
    //  <q.12> PIN12
    //  <q.13> PIN13
    //  <q.14> PIN14
    //  <q.15> PIN15
    // </h>
    */
    #define DEF_PBOUT_LOWPOWER ((uint32_t)0x00000000U)
    /*
    // <h>GPIOC
    //  <q.0> PIN0
    //  <q.1> PIN1
    //  <q.2> PIN2
    //  <q.3> PIN3
    //  <q.4> PIN4
    //  <q.5> PIN5
    //  <q.6> PIN6
    //  <q.7> PIN7
    //  <q.8> PIN8
    //  <q.9> PIN9
    //  <q.10> PIN10
    //  <q.11> PIN11
    //  <q.12> PIN12
    //  <q.13> PIN13
    //  <q.14> PIN14
    //  <q.15> PIN15
    // </h>
    */
    #define DEF_PCOUT_LOWPOWER ((uint32_t)0x00000000U)
    /*
    // <h>GPIOD
    //  <q.0> PIN0
    //  <q.1> PIN1
    //  <q.2> PIN2
    //  <q.3> PIN3
    //  <q.4> PIN4
    //  <q.5> PIN5
    //  <q.6> PIN6
    //  <q.7> PIN7
    //  <q.8> PIN8
    //  <q.9> PIN9
    //  <q.10> PIN10
    //  <q.11> PIN11
    //  <q.12> PIN12
    //  <q.13> PIN13
    //  <q.14> PIN14
    //  <q.15> PIN15
    // </h>
    */
    #define DEF_PDOUT_LOWPOWER ((uint32_t)0x00000000U)
    /*
    // <h>GPIOE
    //  <q.0> PIN0
    //  <q.1> PIN1
    //  <q.2> PIN2
    //  <q.3> PIN3
    //  <q.4> PIN4
    //  <q.5> PIN5
    //  <q.6> PIN6
    //  <q.7> PIN7
    //  <q.8> PIN8
    //  <q.9> PIN9
    //  <q.10> PIN10
    //  <q.11> PIN11
    //  <q.12> PIN12
    //  <q.13> PIN13
    //  <q.14> PIN14
    //  <q.15> PIN15
    // </h>
    */
    #define DEF_PEOUT_LOWPOWER ((uint32_t)0x00000000U)
    /*
    // <h>GPIOF
    //  <q.0> PIN0
    //  <q.1> PIN1
    //  <q.2> PIN2
    //  <q.3> PIN3
    //  <q.4> PIN4
    //  <q.5> PIN5
    //  <q.6> PIN6
    //  <q.7> PIN7
    //  <q.8> PIN8
    //  <q.9> PIN9
    //  <q.10> PIN10
    //  <q.11> PIN11
    //  <q.12> PIN12
    //  <q.13> PIN13
    //  <q.14> PIN14
    //  <q.15> PIN15
    // </h>
    */
    #define DEF_PFOUT_LOWPOWER ((uint32_t)0x00000000U)
    /*
    // <h>GPIOG
    //  <q.0> PIN0
    //  <q.1> PIN1
    //  <q.2> PIN2
    //  <q.3> PIN3
    //  <q.4> PIN4
    //  <q.5> PIN5
    //  <q.6> PIN6
    //  <q.7> PIN7
    //  <q.8> PIN8
    //  <q.9> PIN9
    //  <q.10> PIN10
    //  <q.11> PIN11
    //  <q.12> PIN12
    //  <q.13> PIN13
    //  <q.14> PIN14
    //  <q.15> PIN15
    // </h>
    */
    #define DEF_PGOUT_LOWPOWER ((uint32_t)0x00000000U)
    
    
  /*
  // </h>
  */
  /*
  // <h>GPIO外部中断管脚选择及配置
  */
    /*
    // <h>EXTI0 NVIC 45
    //  <o.0..1> EXTI0.0 输入管脚选择 
    //    <0=> 00：PA0
    //    <1=> 01：PA8
    //    <2=> 10：PB0
    //    <3=> 11：PB8
    //  <o.16..17> EXTI0.0 边缘触发选择
    //    <0=> 00：rising
    //    <1=> 01：falling
    //    <2=> 10：both
    //    <3=> 11：disable
    //  <o.2..3> EXTI0.1 输入管脚选择 
    //    <0=> 00：PA1
    //    <1=> 01：PA9
    //    <2=> 10：PB1
    //    <3=> 11：PB9
    //  <o.18..19> EXTI0.1 边缘触发选择
    //    <0=> 00：rising
    //    <1=> 01：falling
    //    <2=> 10：both
    //    <3=> 11：disable
    //  <o.4..5> EXTI0.2 输入管脚选择 
    //    <0=> 00：PA2
    //    <1=> 01：PA10
    //    <2=> 10：PB2
    //    <3=> 11：PB10
    //  <o.20..21> EXTI0.2 边缘触发选择
    //    <0=> 00：rising
    //    <1=> 01：falling
    //    <2=> 10：both
    //    <3=> 11：disable
    //  <o.6..7> EXTI0.3 输入管脚选择 
    //    <0=> 00：PA3
    //    <1=> 01：PA11
    //    <2=> 10：PB3
    //    <3=> 11：PB11
    //  <o.22..23> EXTI0.3 边缘触发选择
    //    <0=> 00：rising
    //    <1=> 01：falling
    //    <2=> 10：both
    //    <3=> 11：disable
    //  <o.8..9> EXTI0.4 输入管脚选择 
    //    <0=> 00：PA4
    //    <1=> 01：PA12
    //    <2=> 10：PB4
    //    <3=> 11：PB12
    //  <o.24..25> EXTI0.4 边缘触发选择
    //    <0=> 00：rising
    //    <1=> 01：falling
    //    <2=> 10：both
    //    <3=> 11：disable
    //  <o.10..11> EXTI0.5 输入管脚选择 
    //    <0=> 00：PA5
    //    <1=> 01：PA13
    //    <2=> 10：PB5
    //    <3=> 11：PB13
    //  <o.26..27> EXTI0.5 边缘触发选择
    //    <0=> 00：rising
    //    <1=> 01：falling
    //    <2=> 10：both
    //    <3=> 11：disable
    //  <o.12..13> EXTI0.6 输入管脚选择 
    //    <0=> 00：PA6
    //    <1=> 01：PA14
    //    <2=> 10：PB6
    //    <3=> 11：PB14
    //  <o.28..29> EXTI0.6 边缘触发选择
    //    <0=> 00：rising
    //    <1=> 01：falling
    //    <2=> 10：both
    //    <3=> 11：disable
    //  <o.14..15> EXTI0.7 输入管脚选择 
    //    <0=> 00：PA7
    //    <1=> 01：PA15
    //    <2=> 10：PB7
    //    <3=> 11：PB15
    //  <o.30..31> EXTI0.7 边缘触发选择
    //    <0=> 00：rising
    //    <1=> 01：falling
    //    <2=> 10：both
    //    <3=> 11：disable
    // </h>
    */
    #define DEF_EXTI0SEL_LOWPOWER ((uint32_t)0xFFFF0001U)
    /*
    // <h>EXTI1 NVIC 46
    //  <o.0..1> EXTI1.0 输入管脚选择 
    //    <0=> 00：PC0
    //    <1=> 01：PC8
    //    <2=> 10：PD0
    //    <3=> 11：PD8
    //  <o.16..17> EXTI1.0 边缘触发选择
    //    <0=> 00：rising
    //    <1=> 01：falling
    //    <2=> 10：both
    //    <3=> 11：disable
    //  <o.2..3> EXTI1.1 输入管脚选择 
    //    <0=> 00：PC1
    //    <1=> 01：PC9
    //    <2=> 10：PD1
    //    <3=> 11：PD9
    //  <o.18..19> EXTI1.1 边缘触发选择
    //    <0=> 00：rising
    //    <1=> 01：falling
    //    <2=> 10：both
    //    <3=> 11：disable
    //  <o.4..5> EXTI1.2 输入管脚选择 
    //    <0=> 00：PC2
    //    <1=> 01：PC10
    //    <2=> 10：PD2
    //    <3=> 11：PD10
    //  <o.20..21> EXTI1.2 边缘触发选择
    //    <0=> 00：rising
    //    <1=> 01：falling
    //    <2=> 10：both
    //    <3=> 11：disable
    //  <o.6..7> EXTI1.3 输入管脚选择 
    //    <0=> 00：PC3
    //    <1=> 01：PC11
    //    <2=> 10：PD3
    //    <3=> 11：PG3
    //  <o.22..23> EXTI1.3 边缘触发选择
    //    <0=> 00：rising
    //    <1=> 01：falling
    //    <2=> 10：both
    //    <3=> 11：disable
    //  <o.8..9> EXTI1.4 输入管脚选择 
    //    <0=> 00：PC4
    //    <1=> 01：PC12
    //    <2=> 10：PD4
    //    <3=> 11：PG5
    //  <o.24..25> EXTI1.4 边缘触发选择
    //    <0=> 00：rising
    //    <1=> 01：falling
    //    <2=> 10：both
    //    <3=> 11：disable
    //  <o.10..11> EXTI1.5 输入管脚选择 
    //    <0=> 00：PC5
    //    <1=> 01：PC13
    //    <2=> 10：PD5
    //    <3=> 11：PG6
    //  <o.26..27> EXTI1.5 边缘触发选择
    //    <0=> 00：rising
    //    <1=> 01：falling
    //    <2=> 10：both
    //    <3=> 11：disable
    //  <o.12..13> EXTI1.6 输入管脚选择 
    //    <0=> 00：PC6
    //    <1=> 01：PC14
    //    <2=> 10：PD6
    //    <3=> 11：PG7
    //  <o.28..29> EXTI1.6 边缘触发选择
    //    <0=> 00：rising
    //    <1=> 01：falling
    //    <2=> 10：both
    //    <3=> 11：disable
    //  <o.14..15> EXTI1.7 输入管脚选择 
    //    <0=> 00：PC7
    //    <1=> 01：PC15
    //    <2=> 10：PD7
    //    <3=> 11：PG8
    //  <o.30..31> EXTI1.7 边缘触发选择
    //    <0=> 00：rising
    //    <1=> 01：falling
    //    <2=> 10：both
    //    <3=> 11：disable
    // </h>
    */
    #define DEF_EXTI1SEL_LOWPOWER ((uint32_t)0xFFFF0000U)
    /*
    // <h>EXTI2 NVIC 47
    //  <o.0> EXTI2.0 输入管脚选择 
    //    <0=> 00：PE2
    //    <1=> 01：PF0
    //  <o.16..17> EXTI2.0 边缘触发选择
    //    <0=> 00：rising
    //    <1=> 01：falling
    //    <2=> 10：both
    //    <3=> 11：disable
    //  <o.1> EXTI2.1 输入管脚选择 
    //    <0=> 00：PE3
    //    <1=> 01：PF1
    //  <o.18..19> EXTI2.1 边缘触发选择
    //    <0=> 00：rising
    //    <1=> 01：falling
    //    <2=> 10：both
    //    <3=> 11：disable
    //  <o.2> EXTI2.2 输入管脚选择 
    //    <0=> 00：PE4
    //    <1=> 01：PF2
    //  <o.20..21> EXTI2.2 边缘触发选择
    //    <0=> 00：rising
    //    <1=> 01：falling
    //    <2=> 10：both
    //    <3=> 11：disable
    //  <o.3> EXTI2.3 输入管脚选择 
    //    <0=> 00：PE5
    //    <1=> 01：PF3
    //  <o.22..23> EXTI2.3 边缘触发选择
    //    <0=> 00：rising
    //    <1=> 01：falling
    //    <2=> 10：both
    //    <3=> 11：disable
    //  <o.4..5> EXTI2.4 输入管脚选择 
    //    <0=> 00：PE6
    //    <1=> 01：PF4
    //    <2=> 10：PF8
    //    <3=> 11：PF8
    //  <o.24..25> EXTI2.4 边缘触发选择
    //    <0=> 00：rising
    //    <1=> 01：falling
    //    <2=> 10：both
    //    <3=> 11：disable
    //  <o.6..7> EXTI2.5 输入管脚选择 
    //    <0=> 00：PE7
    //    <1=> 01：PF5
    //    <2=> 10：PF9
    //    <3=> 11：PF9
    //  <o.26..27> EXTI2.5 边缘触发选择
    //    <0=> 00：rising
    //    <1=> 01：falling
    //    <2=> 10：both
    //    <3=> 11：disable
    //  <o.8..9> EXTI2.6 输入管脚选择 
    //    <0=> 00：PE8
    //    <1=> 01：PF6
    //    <2=> 10：PF10
    //    <3=> 11：PF10
    //  <o.28..29> EXTI2.6 边缘触发选择
    //    <0=> 00：rising
    //    <1=> 01：falling
    //    <2=> 10：both
    //    <3=> 11：disable
    //  <o.10..11> EXTI2.7 输入管脚选择 
    //    <0=> 00：PE9
    //    <1=> 01：PF7
    //    <2=> 10：PF11
    //    <3=> 11：PF11
    //  <o.30..31> EXTI2.7 边缘触发选择
    //    <0=> 00：rising
    //    <1=> 01：falling
    //    <2=> 10：both
    //    <3=> 11：disable
    // </h>
    */
    #define DEF_EXTI2SEL_LOWPOWER ((uint32_t)0xFFFF0000U)
  /*
  // </h>
  */
  /*
  // <h>remap配置
  */
  //  <o.0> Remap1(PF11)选择信号 
  //    <0=> 0：FOUT
  //    <1=> 1：LPTO
  //  <o.8..9> Remap2(PF1)选择信号 
  //    <0=> 000: UART0_RX输入
  //    <1=> 001: UART1_RX输入
  //    <2=> 010: UART2_RX输入
  //    <3=> 011: LPTI输入
  //    <4=> 100:LPTO输出
  //    <5=> 101:FOUT输出
  //    <6=> 110：0
  //    <7=> 111：0
  //  <o.16..17> Remap3(PE9)选择信号
  //    <0=> 00：UART3_RX输入
  //    <1=> 01：UART4_RX输入
  //    <2=> 10：UART5_RX输入
  //    <3=> 11：LPTI输入
  // </h>
    
    #define DEF_REMAPSEL_LOWPOWER ((uint32_t)0x00000000U)
  /*
  // <h>强驱动配置
  */
  //  <q.0> PE2强驱动使能 
  //  <q.1> PG6强驱动使能 
  // </h>
    
    #define DEF_HDSEL_LOWPOWER ((uint32_t)0x00000000U)
/*
// </h>
*/
//*** <<< end of configuration section >>>    ***

    extern void SystemInit_LowPower(void);
    extern void SystemCoreClockUpdate_LowPower(void);


#ifdef __cplusplus
}
#endif

#endif 

/**
  * @}
  */
  
/**
  * @}
  */  
/************************ (C) COPYRIGHT FMSH *****END OF FILE****/
