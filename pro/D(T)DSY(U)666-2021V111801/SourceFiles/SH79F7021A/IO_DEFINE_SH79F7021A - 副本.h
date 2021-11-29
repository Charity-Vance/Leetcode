/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    IO_DEFINE_SH79F7021A.h                                                                          
**** Brief:       SH79F7021A IO资源定义头文件                                                                  
**** Author:      peter.he@chint.com                                                                 
**** Version:     V1.0                                                                               
**** Date:        2019年3月14日                                                                         
****                                                                                                 
**** note:修改历史记录列表，每条修改记录应包括修改日期、修改者                                          
**** 1.  Author:                                                                                     
****     Version:                                                                                    
****     Date :                                                                                      
**** 2.  Author:                                                                                     
****     Version:                                                                                       
****     Date:
****                                                                                        
****  addtogroup:Library                                                             
**********************************************************************************************************/

#ifndef   IO_DEFINE_SH79F7021A_H
#define   IO_DEFINE_SH79F7021A_H

/*-------------------------------- H文件使用说明 -------------------------------------------------------*/
/*
 *  该文件宏定义的前缀为:
 *
 */

 
/*----------------< 包含文件 >----------------------------------*/
#include "..\SourceFiles\SH79F7021A\SH79F7021A.h"
//#include "..\SourceFiles\SH79F7021A\SH79F7021AE.h"
/*----------------< 宏定义区 >----------------------------------*/
// 管脚定义
/*
47个双向I/O端口也能共享作为第二或第三种特殊功能。 共享优先级按照外部最高内部最低的规则。
在引脚配置图中引脚最外边标注功能享有最高优先级， 最里边标注功能享有最低优先级。 这意味着一个引脚已经使用较高
优先级功能（如果被允许的话） ， 就不能用作较低优先级功能， 即使较低优先级功能被允许。 只有较高优先级功能由硬件或软
件关闭后， 相应的引脚才能用作较低优先级功能。 上拉电阻也由相同规则控制。
当允许端口复用为其它功能时， 用户可以修改PxCR﹑ PxPCR（x = 0-9） ， 但在复用的其它功能被禁止前， 这些操作不会
影响端口状态。
当允许端口复用为其它功能时， 任何对端口的读写操作只会影响到数据寄存器的值， 端口引脚值保持不变， 直到复用的其
它功能关闭。
如有疑问，请参考技术手册
*/
/* 
* @brief  GPIO管脚定义 具体管脚对应寄存器的位置
*/
#define GPIO_Pin_0		((uchar8 )0x01)     /*!< Pin 0 selected    */
#define GPIO_Pin_1		((uchar8 )0x02)     /*!< Pin 1 selected    */
#define GPIO_Pin_2		((uchar8 )0x04)     /*!< Pin 2 selected    */
#define GPIO_Pin_3		((uchar8 )0x08)     /*!< Pin 3 selected    */
#define GPIO_Pin_4		((uchar8 )0x10)     /*!< Pin 4 selected    */
#define GPIO_Pin_5		((uchar8 )0x20)     /*!< Pin 5 selected    */
#define GPIO_Pin_6		((uchar8 )0x40)     /*!< Pin 6 selected    */
#define GPIO_Pin_7		((uchar8 )0x80)     /*!< Pin 7 selected    */

#define	GPIO_BIT(x)		(1<<x)				///* 找到对应IO口的位置,将对应位配置成1 *///
#define	GPIO_BIT_(x)	(0xff^GPIO_BIT(x))	///* 将对应位置的io配置成0对应的功能 *///
/* 
* @brief  GPIO管脚输入输出配置
* @brief  复位值0
* @brief  0:输入
* @brief  1:输出
*/
/*
* @brief P0口 总共4根口线 p0.1/2/3/7
* @brief P1口 总共3根口线 p1.0/3/4
* @brief P2口 总共3根口线 p2.2/6/7
* @brief P3口 总共3根口线 p3.0/1/4/5/6(数据手册中寄存器有误（3），以封装图为准（5），
* @brief P4口 总共4根口线 p4.4/5/6/7
* @brief P5口 总共8根口线 p5.0/1/2/3/4/5/6/7
* @brief P6口 总共7根口线 p6.1/2/3/4/5/6/7
* @brief P7口 总共5根口线 p7.0/1/5/ 数据手册寄存器里显示有5个，但实际封装只有3个
* @brief P8口 总共2根口线 p8.6/7
* @brief P9口 总共8根口线 p9.0/1/2/3/4/5/6/7
*/
#define GPIO_IOCFG_P0_DIR_O(X)		do{  if( (P0CR & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P0CR |= GPIO_BIT(X); } }while(0);	// 配置成输出
#define GPIO_IOCFG_P0_DIR_I(X)		do{  if( (P0CR | GPIO_BIT(X)) != 0  ) { P0CR &= GPIO_BIT_(X); } }while(0);			// 配置成输输入

#define GPIO_IOCFG_P1_DIR_O(X)		do{  if( (P1CR & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P1CR |= GPIO_BIT(X); } }while(0);
#define GPIO_IOCFG_P1_DIR_I(X)		do{  if( (P1CR | GPIO_BIT(X)) != 0  ) { P1CR &= GPIO_BIT_(X); } }while(0);		// 

#define GPIO_IOCFG_P2_DIR_O(X)		do{  if( (P2CR & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P2CR |= GPIO_BIT(X); } }while(0);		// 
#define GPIO_IOCFG_P2_DIR_I(X)		do{  if( (P2CR | GPIO_BIT(X)) != 0  ) { P2CR &= GPIO_BIT_(X); } }while(0);			// 

#define GPIO_IOCFG_P3_DIR_O(X)		do{  if( (P3CR & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P3CR |= GPIO_BIT(X); } }while(0);
#define GPIO_IOCFG_P3_DIR_I(X)		do{  if( (P3CR | GPIO_BIT(X)) != 0  ) { P3CR &= GPIO_BIT_(X); } }while(0);			// 

#define GPIO_IOCFG_P4_DIR_O(X)		do{  if( (P4CR & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P4CR |= GPIO_BIT(X); } }while(0);
#define GPIO_IOCFG_P4_DIR_I(X)		do{  if( (P4CR | GPIO_BIT(X)) != 0  ) { P4CR &= GPIO_BIT_(X); } }while(0);			// 

#define GPIO_IOCFG_P5_DIR_O(X)		do{  if( (P5CR & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P5CR |= GPIO_BIT(X); } }while(0);
#define GPIO_IOCFG_P5_DIR_I(X)		do{  if( (P5CR | GPIO_BIT(X)) != 0  ) { P5CR &= GPIO_BIT_(X); } }while(0);			// 

#define GPIO_IOCFG_P6_DIR_O(X)		do{  if( (P6CR & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P6CR |= GPIO_BIT(X); } }while(0);
#define GPIO_IOCFG_P6_DIR_I(X)		do{  if( (P6CR | GPIO_BIT(X)) != 0  ) { P6CR &= GPIO_BIT_(X); } }while(0);			// 

#define GPIO_IOCFG_P7_DIR_O(X)		do{  if( (P7CR & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P7CR |= GPIO_BIT(X); } }while(0);
#define GPIO_IOCFG_P7_DIR_I(X)		do{  if( (P7CR | GPIO_BIT(X)) != 0  ) { P7CR &= GPIO_BIT_(X); } }while(0);			// 

#define GPIO_IOCFG_P8_DIR_O(X)		do{  if( (P8CR & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P8CR |= GPIO_BIT(X); } }while(0);
#define GPIO_IOCFG_P8_DIR_I(X)		do{  if( (P8CR | GPIO_BIT(X)) != 0  ) { P8CR &= GPIO_BIT_(X); } }while(0);			// 

#define GPIO_IOCFG_P9_DIR_O(X)		do{  if( (P9CR & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P9CR |= GPIO_BIT(X); } }while(0);
#define GPIO_IOCFG_P9_DIR_I(X)		do{  if( (P9CR | GPIO_BIT(X)) != 0  ) { P9CR &= GPIO_BIT_(X); } }while(0);			// 

#define GPIO_IOCFG_PX_DIR_O(X,Y)	( GPIO_IOCFG_P##X##_DIR_O(Y) )
#define GPIO_IOCFG_PX_DIR_I(X,Y)	( GPIO_IOCFG_P##X##_DIR_I(Y) )




/* 
* @brief  GPIO管脚上拉电阻开关配置
* @brief  复位值0
* @brief  0:关闭
* @brief  1:开启
*/
/*
* @brief P0口 总共4根口线 p0.1/2/3/7
* @brief P1口 总共3根口线 p1.0/3/4
* @brief P2口 总共3根口线 p2.2/6/7
* @brief P3口 总共3根口线 p3.0/1/4/5/6(数据手册中寄存器有误（3），以封装图为准（5），
* @brief P4口 总共4根口线 p4.4/5/6/7
* @brief P5口 总共8根口线 p5.0/1/2/3/4/5/6/7
* @brief P6口 总共7根口线 p6.1/2/3/4/5/6/7
* @brief P7口 总共5根口线 p7.0/1/5/ 数据手册寄存器里显示有5个，但实际封装只有3个
* @brief P8口 总共2根口线 p8.6/7
* @brief P9口 总共8根口线 p9.0/1/2/3/4/5/6/7
*/
#define GPIO_IOCFG_P0_PUP_O(X)		do{  if( (P0PCR & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P0PCR |= GPIO_BIT(X); } }while(0);	// 开启 on
#define GPIO_IOCFG_P0_PUP_F(X)		do{  if( (P0PCR | GPIO_BIT(X)) != 0  ) { P0PCR &= GPIO_BIT_(X); } }while(0);		// 关闭 off

#define GPIO_IOCFG_P1_PUP_O(X)		do{  if( (P1PCR & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P1PCR |= GPIO_BIT(X); } }while(0);	//
#define GPIO_IOCFG_P1_PUP_F(X)		do{  if( (P1PCR | GPIO_BIT(X)) != 0  ) { P1PCR &= GPIO_BIT_(X); } }while(0);		//

#define GPIO_IOCFG_P2_PUP_O(X)		do{  if( (P2PCR & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P2PCR |= GPIO_BIT(X); } }while(0);		//
#define GPIO_IOCFG_P2_PUP_F(X)		do{  if( (P2PCR | GPIO_BIT(X)) != 0  ) { P2PCR &= GPIO_BIT_(X); } }while(0);	//

#define GPIO_IOCFG_P3_PUP_O(X)		do{  if( (P3PCR & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P3PCR |= GPIO_BIT(X); } }while(0);		//
#define GPIO_IOCFG_P3_PUP_F(X)		do{  if( (P3PCR | GPIO_BIT(X)) != 0  ) { P3PCR &= GPIO_BIT_(X); } }while(0);		//

#define GPIO_IOCFG_P4_PUP_O(X)		do{  if( (P4PCR & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P4PCR |= GPIO_BIT(X); } }while(0);		//
#define GPIO_IOCFG_P4_PUP_F(X)		do{  if( (P4PCR | GPIO_BIT(X)) != 0  ) { P4PCR &= GPIO_BIT_(X); } }while(0);		//

#define GPIO_IOCFG_P5_PUP_O(X)		do{  if( (P5PCR & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P5PCR |= GPIO_BIT(X); } }while(0);	//
#define GPIO_IOCFG_P5_PUP_F(X)		do{  if( (P5PCR | GPIO_BIT(X)) != 0  ) { P5PCR &= GPIO_BIT_(X); } }while(0);		//

#define GPIO_IOCFG_P6_PUP_O(X)		do{  if( (P6PCR & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P6PCR |= GPIO_BIT(X); } }while(0);		//
#define GPIO_IOCFG_P6_PUP_F(X)		do{  if( (P6PCR | GPIO_BIT(X)) != 0  ) { P6PCR &= GPIO_BIT_(X); } }while(0);		//

#define GPIO_IOCFG_P7_PUP_O(X)		do{  if( (P7PCR & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P7PCR |= GPIO_BIT(X); } }while(0);	//
#define GPIO_IOCFG_P7_PUP_F(X)		do{  if( (P7PCR | GPIO_BIT(X)) != 0  ) { P7PCR &= GPIO_BIT_(X); } }while(0);		//

#define GPIO_IOCFG_P8_PUP_O(X)		do{  if( (P8PCR & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P8PCR |= GPIO_BIT(X); } }while(0);		//
#define GPIO_IOCFG_P8_PUP_F(X)		do{  if( (P8PCR | GPIO_BIT(X)) != 0  ) { P8PCR &= GPIO_BIT_(X); } }while(0);		//

#define GPIO_IOCFG_P9_PUP_O(X)		do{  if( (P9PCR & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P9PCR |= GPIO_BIT(X); } }while(0);		//
#define GPIO_IOCFG_P9_PUP_F(X)		do{  if( (P9PCR | GPIO_BIT(X)) != 0  ) { P9PCR &= GPIO_BIT_(X); } }while(0);		//

#define GPIO_IOCFG_PX_PUP_O(X,Y)		( GPIO_IOCFG_P##X##_PUP_O(Y) )
#define GPIO_IOCFG_PX_PUP_F(X,Y)		( GPIO_IOCFG_P##X##_PUP_F(Y) )


/* 
* @brief  GPIO管脚端口输出电平控制
* @brief  复位值0
*/
/*
* @brief P0口 总共4根口线 p0.1/2/3/7
* @brief P1口 总共3根口线 p1.0/3/4
* @brief P2口 总共3根口线 p2.2/6/7
* @brief P3口 总共3根口线 p3.0/1/4/5/6(数据手册中寄存器有误（3），以封装图为准（5），
* @brief P4口 总共4根口线 p4.4/5/6/7
* @brief P5口 总共8根口线 p5.0/1/2/3/4/5/6/7
* @brief P6口 总共7根口线 p6.1/2/3/4/5/6/7
* @brief P7口 总共5根口线 p7.0/1/5/ 数据手册寄存器里显示有5个，但实际封装只有3个
* @brief P8口 总共2根口线 p8.6/7
* @brief P9口 总共8根口线 p9.0/1/2/3/4/5/6/7
*/
#define GPIO_IOCFG_P0_SET_1(X)		( P0 |= GPIO_BIT(X)  )		// 输出1
#define GPIO_IOCFG_P0_SET_0(X)		( P0 &= GPIO_BIT_(X)  )		// 输出0
#define GPIO_IOCFG_P1_SET_1(X)		( P1 |= GPIO_BIT(X)  )		//
#define GPIO_IOCFG_P1_SET_0(X)		( P1 &= GPIO_BIT_(X)  )		//
#define GPIO_IOCFG_P2_SET_1(X)		( P2 |= GPIO_BIT(X)  )		//
#define GPIO_IOCFG_P2_SET_0(X)		( P2 &= GPIO_BIT_(X)  )		//
#define GPIO_IOCFG_P3_SET_1(X)		( P3 |= GPIO_BIT(X)  )		//
#define GPIO_IOCFG_P3_SET_0(X)		( P3 &= GPIO_BIT_(X)  )		//
#define GPIO_IOCFG_P4_SET_1(X)		( P4 |= GPIO_BIT(X)  )		//
#define GPIO_IOCFG_P4_SET_0(X)		( P4 &= GPIO_BIT_(X)  )		//
#define GPIO_IOCFG_P5_SET_1(X)		( P5 |= GPIO_BIT(X)  )		//
#define GPIO_IOCFG_P5_SET_0(X)		( P5 &= GPIO_BIT_(X)  )		//
#define GPIO_IOCFG_P6_SET_1(X)		( P6 |= GPIO_BIT(X)  )		//
#define GPIO_IOCFG_P6_SET_0(X)		( P6 &= GPIO_BIT_(X)  )		//
#define GPIO_IOCFG_P7_SET_1(X)		( P7 |= GPIO_BIT(X)  )		//
#define GPIO_IOCFG_P7_SET_0(X)		( P7 &= GPIO_BIT_(X)  )		//
#define GPIO_IOCFG_P8_SET_1(X)		( P8 |= GPIO_BIT(X)  )		//
#define GPIO_IOCFG_P8_SET_0(X)		( P8 &= GPIO_BIT_(X)  )		//
#define GPIO_IOCFG_P9_SET_1(X)		( P9 |= GPIO_BIT(X)  )		//
#define GPIO_IOCFG_P9_SET_0(X)		( P9 &= GPIO_BIT_(X)  )		//

#define GPIO_IOCFG_PX_SET_1(X,Y)	( GPIO_IOCFG_P##X##_SET_1(Y) )
#define GPIO_IOCFG_PX_SET_0(X,Y)	( GPIO_IOCFG_P##X##_SET_0(Y) )

/* 
* @brief 读取口线状态 
* @brief  0:L
* @brief  1:H
*/
#define GPIO_IOCFG_P1_STAT_H(X)		( (P1 & GPIO_BIT(X)) == GPIO_BIT(X) )
#define GPIO_IOCFG_P1_STAT_L(X)		( (P1 & GPIO_BIT(X)) != GPIO_BIT(X) )

#define GPIO_IOCFG_P2_STAT_H(X)		( (P2 & GPIO_BIT(X)) == GPIO_BIT(X) )
#define GPIO_IOCFG_P2_STAT_L(X)		( (P2 & GPIO_BIT(X)) != GPIO_BIT(X) )

#define GPIO_IOCFG_P3_STAT_H(X)		( (P3 & GPIO_BIT(X)) == GPIO_BIT(X) )
#define GPIO_IOCFG_P3_STAT_L(X)		( (P3 & GPIO_BIT(X)) != GPIO_BIT(X) )

#define GPIO_IOCFG_P4_STAT_H(X)		( (P4 & GPIO_BIT(X)) == GPIO_BIT(X) )
#define GPIO_IOCFG_P4_STAT_L(X)		( (P4 & GPIO_BIT(X)) != GPIO_BIT(X) )

#define GPIO_IOCFG_P5_STAT_H(X)		( (P5 & GPIO_BIT(X)) == GPIO_BIT(X) )
#define GPIO_IOCFG_P5_STAT_L(X)		( (P5 & GPIO_BIT(X)) != GPIO_BIT(X) )

#define GPIO_IOCFG_P6_STAT_H(X)		( (P6 & GPIO_BIT(X)) == GPIO_BIT(X) )
#define GPIO_IOCFG_P6_STAT_L(X)		( (P6 & GPIO_BIT(X)) != GPIO_BIT(X) )

#define GPIO_IOCFG_P7_STAT_H(X)		( (P7 & GPIO_BIT(X)) == GPIO_BIT(X) )
#define GPIO_IOCFG_P7_STAT_L(X)		( (P7 & GPIO_BIT(X)) != GPIO_BIT(X) )

#define GPIO_IOCFG_P8_STAT_H(X)		( (P8 & GPIO_BIT(X)) == GPIO_BIT(X) )
#define GPIO_IOCFG_P8_STAT_L(X)		( (P8 & GPIO_BIT(X)) != GPIO_BIT(X) )

#define GPIO_IOCFG_P9_STAT_H(X)		( (P9 & GPIO_BIT(X)) == GPIO_BIT(X) )
#define GPIO_IOCFG_P9_STAT_L(X)		( (P9 & GPIO_BIT(X)) != GPIO_BIT(X) ) 


#define GPIO_IOCFG_PX_STAT_H(X,Y)	( GPIO_IOCFG_P##X##_STAT_H(Y) )
#define GPIO_IOCFG_PX_STAT_L(X,Y)	( GPIO_IOCFG_P##X##_STAT_L(Y) )

/* 
* @brief  GPIO管脚端口输出模式选择寄存器，仅P0P2P3有此功能
* @brief  0： 引脚输出模式为N沟道开漏输出（复位值）
* @brief  1： 引脚输出模式为CMOS挽推输出
*/
/*
* @brief P0口 总共4根口线 p0.1/2/3/7 
* @brief P2口 总共3根口线 p2.2/6/7
* @brief P3口 总共3根口线 p3.0/1/4/5/6 
*/
#define GPIO_IOCFG_P0_OUT_C(X)		do{  if( (P0OS & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P0OS |= GPIO_BIT(X); } }while(0);		// 引脚输出模式为CMOS挽推输出
#define GPIO_IOCFG_P0_OUT_N(X)		do{  if( (P0OS | GPIO_BIT(X)) != 0  ) { P0OS &= GPIO_BIT_(X); } }while(0);		// 引脚输出模式为N沟道开漏输出（复位值）

#define GPIO_IOCFG_P2_OUT_C(X)		do{  if( (P2OS & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P2OS |= GPIO_BIT(X); } }while(0);	//
#define GPIO_IOCFG_P2_OUT_N(X)		do{  if( (P2OS | GPIO_BIT(X)) != 0  ) { P2OS &= GPIO_BIT_(X); } }while(0);		//

#define GPIO_IOCFG_P3_OUT_C(X)		do{  if( (P3OS & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P3OS |= GPIO_BIT(X); } }while(0);	//
#define GPIO_IOCFG_P3_OUT_N(X)		do{  if( (P3OS | GPIO_BIT(X)) != 0  ) { P3OS &= GPIO_BIT_(X); } }while(0);		//

#define GPIO_IOCFG_PX_OUT_N(X,Y)		( GPIO_IOCFG_P##X##_OUT_N(Y) )
#define GPIO_IOCFG_PX_OUT_C(X,Y)		( GPIO_IOCFG_P##X##_OUT_C(Y) )

/* 
* @brief  GPIO管脚端口输出能力选择寄存器，仅P0P1P2有此功能
* @brief  端口输出高能力减弱模式选择 仅P0/P2
          0： 引脚输出模式正常高电平
          1： 引脚输出模式减弱高电平
* @brief  端口输出低能力减弱模式选择 仅P1
          0： 引脚输出模式正常低电平
          1： 引脚输出模式减弱低电平   
* @brief  应用说明: 
         输出高减弱后的驱动能力等价与该IO口开漏输出+5K上拉电阻， 可以用于IIC通讯口， 节省外部上拉电阻； 输出低减弱
         后的驱动能力等价与该IO口输出低时候串联了一个1K电阻， 可以用于一些LED灯的驱动电路， 节省限流电阻                
*/
// 端口输出高能力减弱模式选择
//P0/P2
#define GPIO_IOCFG_P0_OUTH_NORMAL(X)		do{  if( (P0DRVH & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P0DRVH |= GPIO_BIT(X); } }while(0);	// 引脚输出模式减弱高电平
#define GPIO_IOCFG_P0_OUTH_WEAKEN(X)		do{  if( (P0DRVH | GPIO_BIT(X)) != 0  ) { P0DRVH &= GPIO_BIT_(X); } }while(0);			// 引脚输出模式正常高电平 复位值0

#define GPIO_IOCFG_P2_OUTH_NORMAL(X)		do{  if( (P2DRVH & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P2DRVH |= GPIO_BIT(X); } }while(0);	// 引脚输出模式减弱高电平
#define GPIO_IOCFG_P2_OUTH_WEAKEN(X)		do{  if( (P2DRVH | GPIO_BIT(X)) != 0  ) { P2DRVH &= GPIO_BIT_(X); } }while(0);			// 引脚输出模式正常高电平 复位值0

#define GPIO_IOCFG_PX_OUTH_NORMAL(X,Y)		( GPIO_IOCFG_P##X##_OUTH_NORMAL(Y) )
#define GPIO_IOCFG_PX_OUTH_WEAKEN(X,Y)		( GPIO_IOCFG_P##X##_OUTH_WEAKEN(Y) )

//P1
#define GPIO_IOCFG_P1_OUTL_NORMAL(X)		do{  if( (P1DRVL & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P1DRVL |= GPIO_BIT(X); } }while(0);	// 引脚输出模式减弱高电平
#define GPIO_IOCFG_P1_OUTL_WEAKEN(X)		do{  if( (P1DRVL | GPIO_BIT(X)) != 0  ) { P1DRVL &= GPIO_BIT_(X); } }while(0);			// 引脚输出模式正常高电平 复位值0

#define GPIO_IOCFG_PX_OUTL_NORMAL(X,Y)		( GPIO_IOCFG_P##X##_OUTL_NORMAL(Y) )
#define GPIO_IOCFG_PX_OUTL_WEAKEN(X,Y)		( GPIO_IOCFG_P##X##_OUTL_WEAKEN(Y) )

/* 
* @brief  GPIO管脚端口输入上拉模式选择寄存器，仅P0/P2有此功能
* @brief  端口输入上拉模式选择
          0： 引脚输入上拉正常模式 复位值0
          1： 引脚输入上拉切换模式，
          该控制位只在对应端口上拉电阻使能后有效， 上拉电阻的阻值， 取决于输入的电平，
          如果输入的是高电平， 上拉电阻为正常上拉电阻(30K)+弱驱动上拉电阻（1M） ,如果
          输入电平是低电平， 上拉电阻为弱上拉电阻(1M)
* @brief  应用说明: 
          端口上拉电阻切换模式可用于按键输入应用场合， 节省外部上拉1M电阻， 同时高电平时上拉能力较强， 可克服外部
          环境变化， 如湿度引起的漏电导致的按键误按         
*/          
#define GPIO_IOCFG_P0_PUPM_NORMAL(X)		do{  if( (P0PHM & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P0PHM |= GPIO_BIT(X); } }while(0);	// 引脚输入上拉切换模式
#define GPIO_IOCFG_P0_PUPM_SWITCH(X)		do{  if( (P0PHM | GPIO_BIT(X)) != 0  ) { P0PHM &= GPIO_BIT_(X); } }while(0);			// 引脚输入上拉正常模式 复位值0

#define GPIO_IOCFG_P2_PUPM_NORMAL(X)		do{  if( (P2PHM & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P2PHM |= GPIO_BIT(X); } }while(0);	// 引脚输入上拉切换模式
#define GPIO_IOCFG_P2_PUPM_SWITCH(X)		do{  if( (P2PHM | GPIO_BIT(X)) != 0  ) { P2PHM &= GPIO_BIT_(X); } }while(0);			// 引脚输入上拉正常模式 复位值0

#define GPIO_IOCFG_PX_PUPM_NORMAL(X,Y)		( GPIO_IOCFG_P##X##_PUPM_NORMAL(Y) )
#define GPIO_IOCFG_PX_PUPM_SWITCH(X,Y)		( GPIO_IOCFG_P##X##_PUPM_SWITCH(Y) )


/* 
* @brief  GPIO管脚端口数据来源选择寄存器，仅P0/P2有此功能
* @brief  端口输入选择寄存器
          0： 输出状态下， 读取PORT寄存器时， 返回PORT数据寄存器值 复位值0
          1： 输出状态下， 读取PORT寄存器时， 返回PORT 口电平        
*/ 
#define GPIO_IOCFG_P0_INM_LEVEL(X)		do{  if( (P0INM & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P0INM |= GPIO_BIT(X); } }while(0);	// 输出状态下， 读取PORT寄存器时， 返回PORT 口电平  
#define GPIO_IOCFG_P0_INM_DATA(X)		do{  if( (P0INM | GPIO_BIT(X)) != 0  ) { P0INM &= GPIO_BIT_(X); } }while(0);			// 输出状态下， 读取PORT寄存器时， 返回PORT数据寄存器值 复位值0

#define GPIO_IOCFG_P2_INM_LEVEL(X)		do{  if( (P2INM & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P2INM |= GPIO_BIT(X); } }while(0);	//
#define GPIO_IOCFG_P2_INM_DATA(X)		do{  if( (P2INM | GPIO_BIT(X)) != 0  ) { P2INM &= GPIO_BIT_(X); } }while(0);			//

#define GPIO_IOCFG_PX_INM_LEVEL(X,Y)	( GPIO_IOCFG_P##X##_INM_LEVEL(Y) )
#define GPIO_IOCFG_PX_INM_DATA(X,Y)		( GPIO_IOCFG_P##X##_INM_DATA(Y) )
/*----------------< 变量声明 >----------------------------------*/


/*----------------< 函数声明 >----------------------------------*/






#endif
