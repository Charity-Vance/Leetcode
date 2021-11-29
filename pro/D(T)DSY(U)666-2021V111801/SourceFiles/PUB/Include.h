/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    include.h                                                                          
**** Brief:       通用包含头文件                                                                      
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

#ifndef   INCLUDE_H
#define   INCLUDE_H

/*-------------------------------- H文件使用说明 -------------------------------------------------------*/
/*
 *  该文件宏定义的前缀为:
 *
 */

 
/*----------------< 包含文件 >----------------------------------*/
#include <intrins.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "..\SourceFiles\SH79F7021A\SH79F7021A.h" 
#include "..\SourceFiles\SH79F7021A\IO_DEFINE_SH79F7021A.h"

#include "..\SourceFiles\PUB\TypeDefine.h"
#include "..\SourceFiles\PUB\ComDefine.h"
#include "..\SourceFiles\PUB\Interrupt.h"
#include "..\SourceFiles\PUB\RamDefine.h "
#include "..\SourceFiles\PUB\LibPublic.h "
#include "..\SourceFiles\PUB\LibEepromLayout.h "
#include "..\SourceFiles\PUB\TripleDES.h "

#include "..\SourceFiles\APP\AppEMU7021A.h "
#include "..\SourceFiles\APP\AppComm.h "
#include "..\SourceFiles\APP\AppPowerOn.h"
#include "..\SourceFiles\APP\AppPowerOff.h"
#include "..\SourceFiles\APP\AppDLT645.h "
#include "..\SourceFiles\APP\AppDisplay.h "
#include "..\SourceFiles\APP\AppMonitor.h "
#include "..\SourceFiles\APP\AppMeasure.h "
#include "..\SourceFiles\APP\AppEMUAtt7036.h "
#include "..\SourceFiles\APP\AppMoney.h "
#include "..\SourceFiles\APP\AppRelayControl.h "
#include "..\SourceFiles\APP\AppVirtualEsam.h "
#include "..\SourceFiles\APP\AppEvent.h "


#include "..\SourceFiles\DRV\BLEDrv.h "
#include "..\SourceFiles\DRV\LCDDrv.h "
#include "..\SourceFiles\DRV\InternalE2Drv.h "
#include "..\SourceFiles\DRV\KeyDrv.h "
#include "..\SourceFiles\DRV\SPIDrv.h "
#include "..\SourceFiles\DRV\IICDrv.h "
#include "..\SourceFiles\DRV\RelayDrv.h "


/*----------------< 宏定义区 >----------------------------------*/


/*----------------< 变量声明 >----------------------------------*/


/*----------------< 函数声明 >----------------------------------*/





#endif
