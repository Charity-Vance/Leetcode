
///*****************************************************************************************///
///*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     MCUConfig.h
///*Version:       V1
///*Date:          2017-9-19
///*Description:   
///*Function List: 
///*****************************************************************************************///
#ifndef	__MCUConfig_H
#define	__MCUConfig_H


#define	IWDG_R_WR_EN		0x00005555
#define	IWDG_EN				0x0000CCCC
#define	IWDG_FEED			0x12345A5A
#define	IWDG_PR_DIV8		0x00000001
#define	IWDG_PR_DIV16		0x00000002
#define	IWDG_PR_DIV32		0x00000003
#define	IWDG_PR_DIV256		0x00000007
///*因为LRC振荡频率在13k-60k之间,标准为32k,因此狗叫采用60k来算*///
///*这样能够保证不提前狗叫*///
#define	IWDG_RLR			469

#define	FeedWatchDog()		{IWDT->IWDTSERV = IWDG_FEED;}		///*喂狗，看门狗理论时间8s，范围澹(18.4--4)+12，64ms * (1+SET[7:0])*///

#endif
