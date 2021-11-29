/*******************************************************************************************************
**** Copyright��  (c)Copyright 2019,�㽭��̩�����Ǳ��������ι�˾,���ܱ�Ӧ���з�                       
****                            All rights reserved.                                                 
**** FileName:    IO_DEFINE_SH79F7021A.h                                                                          
**** Brief:       SH79F7021A IO��Դ����ͷ�ļ�                                                                  
**** Author:      peter.he@chint.com                                                                 
**** Version:     V1.0                                                                               
**** Date:        2019��3��14��                                                                         
****                                                                                                 
**** note:�޸���ʷ��¼�б�ÿ���޸ļ�¼Ӧ�����޸����ڡ��޸���                                          
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

/*-------------------------------- H�ļ�ʹ��˵�� -------------------------------------------------------*/
/*
 *  ���ļ��궨���ǰ׺Ϊ:
 *
 */

 
/*----------------< �����ļ� >----------------------------------*/
#include "..\SourceFiles\SH79F7021A\SH79F7021A.h"
//#include "..\SourceFiles\SH79F7021A\SH79F7021AE.h"
/*----------------< �궨���� >----------------------------------*/
// �ܽŶ���
/*
47��˫��I/O�˿�Ҳ�ܹ�����Ϊ�ڶ�����������⹦�ܡ� �������ȼ������ⲿ����ڲ���͵Ĺ���
����������ͼ����������߱�ע��������������ȼ��� ����߱�ע��������������ȼ��� ����ζ��һ�������Ѿ�ʹ�ýϸ�
���ȼ����ܣ����������Ļ��� �� �Ͳ��������ϵ����ȼ����ܣ� ��ʹ�ϵ����ȼ����ܱ����� ֻ�нϸ����ȼ�������Ӳ������
���رպ� ��Ӧ�����Ų��������ϵ����ȼ����ܡ� ��������Ҳ����ͬ������ơ�
������˿ڸ���Ϊ��������ʱ�� �û������޸�PxCR�p PxPCR��x = 0-9�� �� ���ڸ��õ��������ܱ���ֹǰ�� ��Щ��������
Ӱ��˿�״̬��
������˿ڸ���Ϊ��������ʱ�� �κζԶ˿ڵĶ�д����ֻ��Ӱ�쵽���ݼĴ�����ֵ�� �˿�����ֵ���ֲ��䣬 ֱ�����õ���
�����ܹرա�
�������ʣ���ο������ֲ�
*/
/* 
* @brief  GPIO�ܽŶ��� ����ܽŶ�Ӧ�Ĵ�����λ��
*/
#define GPIO_Pin_0		((uchar8 )0x01)     /*!< Pin 0 selected    */
#define GPIO_Pin_1		((uchar8 )0x02)     /*!< Pin 1 selected    */
#define GPIO_Pin_2		((uchar8 )0x04)     /*!< Pin 2 selected    */
#define GPIO_Pin_3		((uchar8 )0x08)     /*!< Pin 3 selected    */
#define GPIO_Pin_4		((uchar8 )0x10)     /*!< Pin 4 selected    */
#define GPIO_Pin_5		((uchar8 )0x20)     /*!< Pin 5 selected    */
#define GPIO_Pin_6		((uchar8 )0x40)     /*!< Pin 6 selected    */
#define GPIO_Pin_7		((uchar8 )0x80)     /*!< Pin 7 selected    */

#define	GPIO_BIT(x)		(1<<x)				///* �ҵ���ӦIO�ڵ�λ��,����Ӧλ���ó�1 *///
#define	GPIO_BIT_(x)	(0xff^GPIO_BIT(x))	///* ����Ӧλ�õ�io���ó�0��Ӧ�Ĺ��� *///
/* 
* @brief  GPIO�ܽ������������
* @brief  ��λֵ0
* @brief  0:����
* @brief  1:���
*/
/*
* @brief P0�� �ܹ�4������ p0.1/2/3/7
* @brief P1�� �ܹ�3������ p1.0/3/4
* @brief P2�� �ܹ�3������ p2.2/6/7
* @brief P3�� �ܹ�3������ p3.0/1/4/5/6(�����ֲ��мĴ�������3�����Է�װͼΪ׼��5����
* @brief P4�� �ܹ�4������ p4.4/5/6/7
* @brief P5�� �ܹ�8������ p5.0/1/2/3/4/5/6/7
* @brief P6�� �ܹ�7������ p6.1/2/3/4/5/6/7
* @brief P7�� �ܹ�5������ p7.0/1/5/ �����ֲ�Ĵ�������ʾ��5������ʵ�ʷ�װֻ��3��
* @brief P8�� �ܹ�2������ p8.6/7
* @brief P9�� �ܹ�8������ p9.0/1/2/3/4/5/6/7
*/
#define GPIO_IOCFG_P0_DIR_O(X)		do{  if( (P0CR & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P0CR |= GPIO_BIT(X); } }while(0);	// ���ó����
#define GPIO_IOCFG_P0_DIR_I(X)		do{  if( (P0CR | GPIO_BIT(X)) != 0  ) { P0CR &= GPIO_BIT_(X); } }while(0);			// ���ó�������

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
* @brief  GPIO�ܽ��������迪������
* @brief  ��λֵ0
* @brief  0:�ر�
* @brief  1:����
*/
/*
* @brief P0�� �ܹ�4������ p0.1/2/3/7
* @brief P1�� �ܹ�3������ p1.0/3/4
* @brief P2�� �ܹ�3������ p2.2/6/7
* @brief P3�� �ܹ�3������ p3.0/1/4/5/6(�����ֲ��мĴ�������3�����Է�װͼΪ׼��5����
* @brief P4�� �ܹ�4������ p4.4/5/6/7
* @brief P5�� �ܹ�8������ p5.0/1/2/3/4/5/6/7
* @brief P6�� �ܹ�7������ p6.1/2/3/4/5/6/7
* @brief P7�� �ܹ�5������ p7.0/1/5/ �����ֲ�Ĵ�������ʾ��5������ʵ�ʷ�װֻ��3��
* @brief P8�� �ܹ�2������ p8.6/7
* @brief P9�� �ܹ�8������ p9.0/1/2/3/4/5/6/7
*/
#define GPIO_IOCFG_P0_PUP_O(X)		do{  if( (P0PCR & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P0PCR |= GPIO_BIT(X); } }while(0);	// ���� on
#define GPIO_IOCFG_P0_PUP_F(X)		do{  if( (P0PCR | GPIO_BIT(X)) != 0  ) { P0PCR &= GPIO_BIT_(X); } }while(0);		// �ر� off

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
* @brief  GPIO�ܽŶ˿������ƽ����
* @brief  ��λֵ0
*/
/*
* @brief P0�� �ܹ�4������ p0.1/2/3/7
* @brief P1�� �ܹ�3������ p1.0/3/4
* @brief P2�� �ܹ�3������ p2.2/6/7
* @brief P3�� �ܹ�3������ p3.0/1/4/5/6(�����ֲ��мĴ�������3�����Է�װͼΪ׼��5����
* @brief P4�� �ܹ�4������ p4.4/5/6/7
* @brief P5�� �ܹ�8������ p5.0/1/2/3/4/5/6/7
* @brief P6�� �ܹ�7������ p6.1/2/3/4/5/6/7
* @brief P7�� �ܹ�5������ p7.0/1/5/ �����ֲ�Ĵ�������ʾ��5������ʵ�ʷ�װֻ��3��
* @brief P8�� �ܹ�2������ p8.6/7
* @brief P9�� �ܹ�8������ p9.0/1/2/3/4/5/6/7
*/
#define GPIO_IOCFG_P0_SET_1(X)		( P0 |= GPIO_BIT(X)  )		// ���1
#define GPIO_IOCFG_P0_SET_0(X)		( P0 &= GPIO_BIT_(X)  )		// ���0
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
* @brief ��ȡ����״̬ 
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
* @brief  GPIO�ܽŶ˿����ģʽѡ��Ĵ�������P0P2P3�д˹���
* @brief  0�� �������ģʽΪN������©�������λֵ��
* @brief  1�� �������ģʽΪCMOS�������
*/
/*
* @brief P0�� �ܹ�4������ p0.1/2/3/7 
* @brief P2�� �ܹ�3������ p2.2/6/7
* @brief P3�� �ܹ�3������ p3.0/1/4/5/6 
*/
#define GPIO_IOCFG_P0_OUT_C(X)		do{  if( (P0OS & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P0OS |= GPIO_BIT(X); } }while(0);		// �������ģʽΪCMOS�������
#define GPIO_IOCFG_P0_OUT_N(X)		do{  if( (P0OS | GPIO_BIT(X)) != 0  ) { P0OS &= GPIO_BIT_(X); } }while(0);		// �������ģʽΪN������©�������λֵ��

#define GPIO_IOCFG_P2_OUT_C(X)		do{  if( (P2OS & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P2OS |= GPIO_BIT(X); } }while(0);	//
#define GPIO_IOCFG_P2_OUT_N(X)		do{  if( (P2OS | GPIO_BIT(X)) != 0  ) { P2OS &= GPIO_BIT_(X); } }while(0);		//

#define GPIO_IOCFG_P3_OUT_C(X)		do{  if( (P3OS & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P3OS |= GPIO_BIT(X); } }while(0);	//
#define GPIO_IOCFG_P3_OUT_N(X)		do{  if( (P3OS | GPIO_BIT(X)) != 0  ) { P3OS &= GPIO_BIT_(X); } }while(0);		//

#define GPIO_IOCFG_PX_OUT_N(X,Y)		( GPIO_IOCFG_P##X##_OUT_N(Y) )
#define GPIO_IOCFG_PX_OUT_C(X,Y)		( GPIO_IOCFG_P##X##_OUT_C(Y) )

/* 
* @brief  GPIO�ܽŶ˿��������ѡ��Ĵ�������P0P1P2�д˹���
* @brief  �˿��������������ģʽѡ�� ��P0/P2
          0�� �������ģʽ�����ߵ�ƽ
          1�� �������ģʽ�����ߵ�ƽ
* @brief  �˿��������������ģʽѡ�� ��P1
          0�� �������ģʽ�����͵�ƽ
          1�� �������ģʽ�����͵�ƽ   
* @brief  Ӧ��˵��: 
         ����߼���������������ȼ����IO�ڿ�©���+5K�������裬 ��������IICͨѶ�ڣ� ��ʡ�ⲿ�������裻 ����ͼ���
         ������������ȼ����IO�������ʱ������һ��1K���裬 ��������һЩLED�Ƶ�������·�� ��ʡ��������                
*/
// �˿��������������ģʽѡ��
//P0/P2
#define GPIO_IOCFG_P0_OUTH_NORMAL(X)		do{  if( (P0DRVH & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P0DRVH |= GPIO_BIT(X); } }while(0);	// �������ģʽ�����ߵ�ƽ
#define GPIO_IOCFG_P0_OUTH_WEAKEN(X)		do{  if( (P0DRVH | GPIO_BIT(X)) != 0  ) { P0DRVH &= GPIO_BIT_(X); } }while(0);			// �������ģʽ�����ߵ�ƽ ��λֵ0

#define GPIO_IOCFG_P2_OUTH_NORMAL(X)		do{  if( (P2DRVH & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P2DRVH |= GPIO_BIT(X); } }while(0);	// �������ģʽ�����ߵ�ƽ
#define GPIO_IOCFG_P2_OUTH_WEAKEN(X)		do{  if( (P2DRVH | GPIO_BIT(X)) != 0  ) { P2DRVH &= GPIO_BIT_(X); } }while(0);			// �������ģʽ�����ߵ�ƽ ��λֵ0

#define GPIO_IOCFG_PX_OUTH_NORMAL(X,Y)		( GPIO_IOCFG_P##X##_OUTH_NORMAL(Y) )
#define GPIO_IOCFG_PX_OUTH_WEAKEN(X,Y)		( GPIO_IOCFG_P##X##_OUTH_WEAKEN(Y) )

//P1
#define GPIO_IOCFG_P1_OUTL_NORMAL(X)		do{  if( (P1DRVL & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P1DRVL |= GPIO_BIT(X); } }while(0);	// �������ģʽ�����ߵ�ƽ
#define GPIO_IOCFG_P1_OUTL_WEAKEN(X)		do{  if( (P1DRVL | GPIO_BIT(X)) != 0  ) { P1DRVL &= GPIO_BIT_(X); } }while(0);			// �������ģʽ�����ߵ�ƽ ��λֵ0

#define GPIO_IOCFG_PX_OUTL_NORMAL(X,Y)		( GPIO_IOCFG_P##X##_OUTL_NORMAL(Y) )
#define GPIO_IOCFG_PX_OUTL_WEAKEN(X,Y)		( GPIO_IOCFG_P##X##_OUTL_WEAKEN(Y) )

/* 
* @brief  GPIO�ܽŶ˿���������ģʽѡ��Ĵ�������P0/P2�д˹���
* @brief  �˿���������ģʽѡ��
          0�� ����������������ģʽ ��λֵ0
          1�� �������������л�ģʽ��
          �ÿ���λֻ�ڶ�Ӧ�˿���������ʹ�ܺ���Ч�� �����������ֵ�� ȡ��������ĵ�ƽ��
          ���������Ǹߵ�ƽ�� ��������Ϊ������������(30K)+�������������裨1M�� ,���
          �����ƽ�ǵ͵�ƽ�� ��������Ϊ����������(1M)
* @brief  Ӧ��˵��: 
          �˿����������л�ģʽ�����ڰ�������Ӧ�ó��ϣ� ��ʡ�ⲿ����1M���裬 ͬʱ�ߵ�ƽʱ����������ǿ�� �ɿ˷��ⲿ
          �����仯�� ��ʪ�������©�絼�µİ�����         
*/          
#define GPIO_IOCFG_P0_PUPM_NORMAL(X)		do{  if( (P0PHM & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P0PHM |= GPIO_BIT(X); } }while(0);	// �������������л�ģʽ
#define GPIO_IOCFG_P0_PUPM_SWITCH(X)		do{  if( (P0PHM | GPIO_BIT(X)) != 0  ) { P0PHM &= GPIO_BIT_(X); } }while(0);			// ����������������ģʽ ��λֵ0

#define GPIO_IOCFG_P2_PUPM_NORMAL(X)		do{  if( (P2PHM & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P2PHM |= GPIO_BIT(X); } }while(0);	// �������������л�ģʽ
#define GPIO_IOCFG_P2_PUPM_SWITCH(X)		do{  if( (P2PHM | GPIO_BIT(X)) != 0  ) { P2PHM &= GPIO_BIT_(X); } }while(0);			// ����������������ģʽ ��λֵ0

#define GPIO_IOCFG_PX_PUPM_NORMAL(X,Y)		( GPIO_IOCFG_P##X##_PUPM_NORMAL(Y) )
#define GPIO_IOCFG_PX_PUPM_SWITCH(X,Y)		( GPIO_IOCFG_P##X##_PUPM_SWITCH(Y) )


/* 
* @brief  GPIO�ܽŶ˿�������Դѡ��Ĵ�������P0/P2�д˹���
* @brief  �˿�����ѡ��Ĵ���
          0�� ���״̬�£� ��ȡPORT�Ĵ���ʱ�� ����PORT���ݼĴ���ֵ ��λֵ0
          1�� ���״̬�£� ��ȡPORT�Ĵ���ʱ�� ����PORT �ڵ�ƽ        
*/ 
#define GPIO_IOCFG_P0_INM_LEVEL(X)		do{  if( (P0INM & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P0INM |= GPIO_BIT(X); } }while(0);	// ���״̬�£� ��ȡPORT�Ĵ���ʱ�� ����PORT �ڵ�ƽ  
#define GPIO_IOCFG_P0_INM_DATA(X)		do{  if( (P0INM | GPIO_BIT(X)) != 0  ) { P0INM &= GPIO_BIT_(X); } }while(0);			// ���״̬�£� ��ȡPORT�Ĵ���ʱ�� ����PORT���ݼĴ���ֵ ��λֵ0

#define GPIO_IOCFG_P2_INM_LEVEL(X)		do{  if( (P2INM & GPIO_BIT(X)) != GPIO_BIT(X)  ) { P2INM |= GPIO_BIT(X); } }while(0);	//
#define GPIO_IOCFG_P2_INM_DATA(X)		do{  if( (P2INM | GPIO_BIT(X)) != 0  ) { P2INM &= GPIO_BIT_(X); } }while(0);			//

#define GPIO_IOCFG_PX_INM_LEVEL(X,Y)	( GPIO_IOCFG_P##X##_INM_LEVEL(Y) )
#define GPIO_IOCFG_PX_INM_DATA(X,Y)		( GPIO_IOCFG_P##X##_INM_DATA(Y) )
/*----------------< �������� >----------------------------------*/


/*----------------< �������� >----------------------------------*/






#endif
