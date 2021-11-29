/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    TYPEDEFINE.H                                                                         
**** Brief:       定义数据类型                                                                      
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

#ifndef   TYPEDEFINE_H
#define   TYPEDEFINE_H

/*-------------------------------- H文件使用说明 -------------------------------------------------------*/
/*
 *  该文件宏定义的前缀为:
 *
 */

 
/*----------------< 包含文件 >----------------------------------*/


/*----------------< 宏定义区 >----------------------------------*/

typedef unsigned 			char	uint8_t;
typedef signed 				char	int8_t;

typedef	unsigned	short	int		uint16_t;
typedef	signed		short	int		int16_t;

typedef	unsigned			long	uint32_t;
typedef	signed				long	int32_t;

typedef unsigned 			char	uchar8;
typedef signed 				char	char8;

typedef	unsigned	short	int		ushort16;
typedef	signed		short	int		short16;

typedef	unsigned			long	ulong32;
typedef	signed				long	long32;  

//typedef	unsigned	long	long	ulong64;  

typedef	unsigned 	char	    	BOOLEAN;            /*  布尔变量 for msp430   */ 
typedef unsigned 	char       		INT8U;              /*  无符号8位整型变量         */
typedef signed   	char       		INT8S;              /*  有符号8位整型变量         */
typedef unsigned 	short 	int 	INT16U;             /*  无符号16位整型变量        */
typedef signed   	short 	int 	INT16S;             /*  有符号16位整型变量        */
typedef unsigned 	long  	int 	INT32U;             /*  无符号32位整型变量        */
typedef signed   	long  	int 	INT32S;             /*  有符号32位整型变量        */ 
typedef float    	           		FP32;               /*  单精度浮点数(32位长度)    */
typedef double   	           		FP64;               /*  双精度浮点数(32位长度)    */
typedef unsigned 	char       		STATUS ;
/*----------------< 变量声明 >----------------------------------*/
typedef union B32_B08
{
	uchar8     B08[4];
	ushort16   B16[2];
	ulong32    B32;
}GU_B32_B08_Type; 


///* INT型(WORD) 布尔变量定义 *///
typedef union 											
{	
	uchar8	BYTE[2];
	struct {
		uchar8 B0 : 1;
		uchar8 B1 : 1;
		uchar8 B2 : 1;
		uchar8 B3 : 1;
		uchar8 B4 : 1;
		uchar8 B5 : 1;
		uchar8 B6 : 1;
		uchar8 B7 : 1;
		uchar8 B8 : 1;
		uchar8 B9 : 1;
		uchar8 B10 : 1;
		uchar8 B11 : 1;
		uchar8 B12 : 1;
		uchar8 B13 : 1;
		uchar8 B14 : 1;
		uchar8 B15 : 1;
	}BIT;
}GU_BoolWordVariable;
/*----------------< 函数声明 >----------------------------------*/






#endif
