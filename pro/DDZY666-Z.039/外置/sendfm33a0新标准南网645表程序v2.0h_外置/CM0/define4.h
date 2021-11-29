#ifndef	__DEFINE_H__
#define __DEFINE_H__

//定义常量, 常数
#include "bintohex.h"
#include "FM32L0XX.h"

#if   defined (__CC_ARM)  

#define ecode   
#define bdata
#define idata
#define near
#define code    
#define xdata
#define reentrant
#define bit unsigned char
#define huge
#else

#endif

#define	ESAMON			1	  //是否有ESAM：  0:无；1:有

#define	CHINT_Mode 1	///*正泰模式，区别于复旦微原始程序的部分方便比对 1：正泰 0：复旦微*///	

#define CHINT_TemperatureMode 1	///*0 电科院     1  生产*///

//uart 缓冲区顺序定义
#define CHHW	0
#define CH485	1
#define CHZB	2
#define CHBLE	3
#define	CHNum	4

#define	NEWCLOCKADJ	0	  //时钟调校：0:旧标准时钟调校; 1:新时钟调校(采用三次补偿曲线)

//从0x811800开始会保存如下信息
#define HXVAR(object, addr)   (*((object ecode *) (addr)))
#define const_tx_flag  		HXVAR( uint16, 0x1ffffa20 ) //调校标志(0x3cc3为编程调校)
#define const_rtc_adj_top 	HXVAR( int16,  0x1ffffa36 ) //顶点误差ppm,0.01ppm
#define const_temp_TestA 	HXVAR( uint08, 0x1FFFFC90 )	//测试时温度整数位
#define const_temp_TestB 	HXVAR( uint08, 0x1FFFFC91 )	//测试时温度小数位
#define const_adc_Test	 	HXVAR( uint16, 0x1FFFFC92 )	//测试时PTAT ADC值
#define const_rchf_Trim8 	HXVAR( uint32, 0x1FFFFD40 )	//RC8M 校准值
#define const_rchf_Trim16 	HXVAR( uint32, 0x1FFFFD3C )	//RC16M 校准值
#define const_adc_Slope 	HXVAR( uint16, 0x1FFFFC54 )	//ADC斜率，约2.2mV/lsb
#define const_adc_Offset 	HXVAR( int16,  0x1FFFFC56 )	//ADC截距
#define const_ptat_Offset3V	HXVAR( uint08, 0x1FFFFC94 )	//ptat 5v3v差值
#define const_mark404		HXVAR( uint16, 0x1FFFFC0E )	//404标记

#define LCDLEDON	GPIO_ResetBits(GPIOE, GPIO_Pin_2)
#define LCDLEDOFF	GPIO_SetBits(GPIOE, GPIO_Pin_2)
#define LCDLEDTOG	GPIO_ToggleBits(GPIOE, GPIO_Pin_2)

#define SHIDUANCTRL_ON	GPIO_SetBits(GPIOG, GPIO_Pin_6)
#define SHIDUANCTRL_OFF GPIO_ResetBits(GPIOG, GPIO_Pin_6)

#define RELAYON2 	GPIO_SetBits(GPIOD, GPIO_Pin_4)
#define RELAYOFF2 	GPIO_ResetBits(GPIOD, GPIO_Pin_4)
#define RELAYON1 	GPIO_SetBits(GPIOD, GPIO_Pin_5)
#define RELAYOFF1 	GPIO_ResetBits(GPIOD, GPIO_Pin_5)

#define RELAYON3 	GPIO_SetBits(GPIOD, GPIO_Pin_4)		//外置
#define RELAYOFF3 	GPIO_ResetBits(GPIOD, GPIO_Pin_4)	

#define PULSELED_ON	GPIO_ResetBits(GPIOB, GPIO_Pin_6)	//预留	
#define PULSELED_OFF	GPIO_SetBits(GPIOB, GPIO_Pin_6)		//预留
#define PULSELED_TOG	GPIO_ToggleBits(GPIOB, GPIO_Pin_6)	//预留	

#define EVENOUTOFF 	GPIO_ResetBits(GPIOE, GPIO_Pin_5)	//无事件上报
#define EVENOUTON 	GPIO_SetBits(GPIOE, GPIO_Pin_5)		//有事件上报
#define PLC_RST0 	GPIO_ResetBits(GPIOF, GPIO_Pin_5)
#define PLC_RST1 	GPIO_SetBits(GPIOF, GPIO_Pin_5)

#define ESAMVCC_P 	(GPIOD->ODR&GPIO_Pin_7) == GPIO_Pin_7
#define ESAMVCC_N 	(GPIOD->ODR&GPIO_Pin_7) != GPIO_Pin_7
#define ESAMPOWERON	GPIO_ResetBits(GPIOD, GPIO_Pin_7)
#define ESAMPOWEROFF	GPIO_SetBits(GPIOD, GPIO_Pin_7)

#define FLASHVCC_P 	    (GPIOE->ODR&GPIO_Pin_4) == GPIO_Pin_4
#define FLASHVCC_N 	    (GPIOE->ODR&GPIO_Pin_4) != GPIO_Pin_4
#define FLASHPOWERON    GPIO_ResetBits(GPIOE, GPIO_Pin_4)
#define FLASHPOWEROFF   GPIO_SetBits(GPIOE, GPIO_Pin_4)

#define RELAYLEDON	GPIO_ResetBits(GPIOG, GPIO_Pin_8) 
#define RELAYLEDOFF	GPIO_SetBits(GPIOG, GPIO_Pin_8) 
#define R485CTRLS	GPIO_ResetBits(GPIOE, GPIO_Pin_3) 
#define R485CTRLR	GPIO_SetBits(GPIOE, GPIO_Pin_3)

#define SVDCHKPHIG	((ANAC->SVDSIF&ANAC_SVDSIF_SVDO_HIGHER_THAN_SVD) == ANAC_SVDSIF_SVDO_HIGHER_THAN_SVD)//未掉电
#define SVDCHKPLOW	((ANAC->SVDSIF&ANAC_SVDSIF_SVDO_HIGHER_THAN_SVD) != ANAC_SVDSIF_SVDO_HIGHER_THAN_SVD)//掉电

#define RELAYCTRLON	GPIO_SetBits(GPIOB, GPIO_Pin_11)
#define RELAYCTRLOFF	GPIO_ResetBits(GPIOB, GPIO_Pin_11) 
#define EEVCCON 	GPIO_SetBits(GPIOB, GPIO_Pin_11)
#define EEVCCOFF 	GPIO_ResetBits(GPIOB, GPIO_Pin_11) 

#define RELAYTEST_P	(GPIOB->IDR&GPIO_Pin_12) == GPIO_Pin_12
#define RELAYTEST_N	(GPIOB->IDR&GPIO_Pin_12) != GPIO_Pin_12

#define DISKEY_P 	(GPIOD->IDR&GPIO_Pin_6) == GPIO_Pin_6
#define DISKEY_N 	(GPIOD->IDR&GPIO_Pin_6) != GPIO_Pin_6
#define COVKEY_N 	(GPIOB->IDR&GPIO_Pin_5) == GPIO_Pin_5
#define COVKEY_P 	(GPIOB->IDR&GPIO_Pin_5) != GPIO_Pin_5
#define RXHW_P		(GPIOC->IDR&GPIO_Pin_4) == GPIO_Pin_4
#define RXHW_N		(GPIOC->IDR&GPIO_Pin_4) != GPIO_Pin_4

#define ACTIVEP_P	(GPIOB->IDR&GPIO_Pin_4) == GPIO_Pin_4
#define ACTIVEP_N	(GPIOB->IDR&GPIO_Pin_4) != GPIO_Pin_4

#define REACTIVEP_P	(GPIOA->IDR&GPIO_Pin_9) == GPIO_Pin_9
#define REACTIVEP_N	(GPIOA->IDR&GPIO_Pin_9) != GPIO_Pin_9

#define RX485_P		(GPIOB->IDR&GPIO_Pin_2) == GPIO_Pin_2
#define RX485_N		(GPIOB->IDR&GPIO_Pin_2) != GPIO_Pin_2

#define METER_RST1	GPIO_SetBits(GPIOD, GPIO_Pin_1)//计量芯片复位脚
#define METER_RST0	GPIO_ResetBits(GPIOD, GPIO_Pin_1)

#define RST_ESAM_H	GPIO_SetBits(GPIOG, GPIO_Pin_7)
#define RST_ESAM_L	GPIO_ResetBits(GPIOG, GPIO_Pin_7)	

#define BLEVCC_P 	    (GPIOB->ODR&GPIO_Pin_7) == GPIO_Pin_7
#define BLEVCC_N 	    (GPIOB->ODR&GPIO_Pin_7) != GPIO_Pin_7
#define BLEPOWERON		GPIO_ResetBits(GPIOB, GPIO_Pin_7)
#define BLEPOWEROFF		GPIO_SetBits(GPIOB, GPIO_Pin_7)

#define CFOUT_ON		GPIO_SetBits(GPIOG, GPIO_Pin_6)
#define CFOUT_OFF		GPIO_ResetBits(GPIOG, GPIO_Pin_6)

#define COMMMODULE_P 	(GPIOG->IDR&GPIO_Pin_9) == GPIO_Pin_9
#define COMMMODULE_N 	(GPIOG->IDR&GPIO_Pin_9) != GPIO_Pin_9

#define EA_OFF		( Powerd_Flag == 0x12345678 )
#define EA_ON		( Powerd_Flag != 0x12345678 )
//#define EA_OFF	((__get_PRIMASK()&0x00000001) == 0x00000001)
//#define EA_ON		((__get_PRIMASK()&0x00000001) == 0x00000000)

#define LCD_SOFF	((DISP->DISPCTRL & BIT6) != BIT6)
#define LCD_SON		((DISP->DISPCTRL & BIT6) == BIT6)

#define APIE_DISABLE	BTIMER1->BTxIE = 0x00000000;	//使能扩展定时器低位比较发生中断
#define APIE_ENABLE	BTIMER1->BTxIE = 0x00000008;

//;============================EEPROM存储定义==========================================
//------------------自动crc校验区、参数区	
#define		ee_emupara_page			0x00		//计量芯片参数页地址
	#define		ee_emupara_inpage		0
	#define		ee_emupara_lenth		20	
#define		ee_esampara_page		0x00		//esam里报警金额到身份认证时效参数页地址
	#define		ee_esampara_inpage		ee_emupara_inpage+ee_emupara_lenth+2
	#define		ee_esampara_lenth		26	
#define		ee_temperature_page		0x00		//温度补偿系数
	#define		ee_temperature_inpage		ee_esampara_inpage+ee_esampara_lenth+2
	#define		ee_temperature_lenth		11	
				
#define		ee_fwdl_page			0x02		//正向电量数据页地址
	#define		ee_fwdl_inpage			0
	#define		ee_fwdl_lenth			(max_feilvcount+2)*4

//------------------
#define		ee_event_point_page		0x04		//冻结和事件总次数(3)及有效次数(2)页，每页12个对象
	#define		ee_eventpoint_inpage		0x00
	#define		ee_eventpoint_lenth		60
	#define		FreezeNum			12	//冻结记录支持的事件个数
	#define		EventNum			37	//事件记录支持的事件个数
	
	#define		ee_timingf_inpage  		0x01	//定时冻结
	#define		ee_immedf_inpage   		0x02	//瞬时冻结
	#define		ee_agreesqf_inpage 		0x03	//约定冻结, 时区表切换
	#define		ee_agreesdf_inpage 		0x04	//约定冻结, 日时段表切换
	#define		ee_jtsqswith_inpage		0x05	//约定冻结, 阶梯时区切换
	#define		ee_agreejtf_inpage 		0x06	//约定冻结, 阶梯切换
	#define		ee_minuten_inpage		0x07	//分钟冻结
	#define		ee_hourf_inpage    		0x08	//整点冻结
	#define		ee_dayf_inpage     		0x09	//日冻结
	#define		ee_monthn_inpage   		0x0A	//月冻结
	#define		ee_histroyf_inpage 		0x0B	//结算日冻结
	#define		ee_year_inpage   		0x0C	//年结算(预留)

	#define		ee_clearn_inpage		0x0D 	//清零
	#define		ee_cleareventn_inpage		0x0E 	//清事件
	#define		ee_powerdownn_inpage		0x0F 	//掉电
	#define		ee_setclockn_inpage		0x10 	//校时
	#define		ee_covern_inpage		0x11 	//开盖
	#define		ee_maxi_inpage			0x12	//过流
	#define		ee_openrelayn_inpage		0x13	//拉闸
	#define		ee_closerelayn_inpage		0x14	//合闸
	#define		ee_programn_inpage		0x15	//编程
	#define		ee_shiqun_inpage		0x16	//时区表编程
	#define		ee_shiduann_inpage		0x17	//时段表编程
	#define		ee_jieshuann_inpage		0x18	//结算日编程
	#define		ee_keysetn_inpage		0x19	//密钥更新编程
	#define		ee_combn_inpage			0x1A	//组合方式编程
	#define		ee_rp1combn_inpage		0x1B	//无功组合方式1编程
	#define		ee_rp2combn_inpage		0x1C	//无功组合方式2编程
	#define		ee_relayerrn_inpage		0x1D	//负荷开关误动作
	#define		ee_powererrn_inpage		0x1E	//电源异常
	#define		ee_weekdayn_inpage		0x1F	//周休日编程
	#define		ee_batterlow_inpage		0x20	//电池欠压
	#define		ee_jtpricen_inpage		0x21	//阶梯表编程
	#define		ee_clockerrn_inpage		0x22	//时钟故障
	#define		ee_calerrn_inpage		0x23	//计量芯片故障记录
	#define		ee_gbsclockn_inpage		0x24	//广播校时记录(100条)
	#define		ee_nlineerrn_inpage		0x25	//零线电流异常记录
	#define		ee_lostvn_inpage		0x26	//失压记录
	#define		ee_lowervn_inpage		0x27	//低电压事件记录
	#define		ee_highvn_inpage		0x28	//高电压事件记录
	#define		ee_batchangen_inpage		0x29	//电池更换记录
	#define		ee_commerrn_inpage		0x2A	//通讯模块异常记录
	#define		ee_commchangen_inpage		0x2B	//通讯模块更换记录
	#define		ee_poweroffn_inpage		0x2C 	//掉电上报事件记录
	#define		ee_poweronn_inpage		0x2D 	//上电上报事件记录
	#define		ee_dayvolpassn_inpage		0x2E	//日电压合格率
	#define		ee_monvolpassn_inpage		0x2F	//月电压合格率
	#define		ee_monpowerdownn_inpage		0x30	//月停电统计
	#define		ee_yearpowerdownn_inpage	0x31	//年停电统计

#define		ee_shiqu1_page			0x0e		//第一套时区页地址
#define		ee_shiqu2_page			0x0f		//第二套时区页地址
	#define		ee_shiqu_lenth			42
//------------------
#define		ee_commaddr_page		0x0e		//通讯地址页地址
	#define		ee_commaddr_inpage		44
	#define		ee_commaddr_lenth		6
#define		ee_meterconst_page		0x0e		//脉冲常数页地址
	#define		ee_meterconst_inpage		ee_commaddr_inpage+ee_commaddr_lenth+2
	#define		ee_meterconst_lenth		4
#define		ee_jtshiqu1_page		0x10		//当前套阶梯时区表
#define		ee_jtshiqu2_page		0x11		//备用套阶梯时区表
	#define		ee_jtshiqu_inpage		44
	#define		ee_jtshiqu_len			12		
#define		ee_curyearjs_page		0x12		//当前第1~6年结算日
	#define		ee_curyearjs_inpage		44
	#define		ee_curyearjs_len		18
//------------------		
#define		ee_shiduantable1_1_page		0x10		//第一套第1时段表页地址
#define		ee_shiduantable1_2_page		0x11		//第一套第2时段表页地址
#define		ee_shiduantable1_3_page		0x12		//第一套第3时段表页地址
#define		ee_shiduantable1_4_page		0x13		//第一套第4时段表页地址
#define		ee_shiduantable1_5_page		0x14		//第一套第5时段表页地址
#define		ee_shiduantable1_6_page		0x15		//第一套第6时段表页地址
#define		ee_shiduantable1_7_page		0x16		//第一套第7时段表页地址
#define		ee_shiduantable1_8_page		0x17		//第一套第8时段表页地址
#define		ee_shiduantable2_1_page		0x18		//第二套第1时段表页地址
#define		ee_shiduantable2_2_page		0x19		//第二套第2时段表页地址
#define		ee_shiduantable2_3_page		0x1a		//第二套第3时段表页地址
#define		ee_shiduantable2_4_page		0x1b		//第二套第4时段表页地址
#define		ee_shiduantable2_5_page		0x1c		//第二套第5时段表页地址
#define		ee_shiduantable2_6_page		0x1d		//第二套第6时段表页地址
#define		ee_shiduantable2_7_page		0x1e		//第二套第7时段表页地址
#define		ee_shiduantable2_8_page		0x1f		//第二套第8时段表页地址
	#define		ee_shiduantable_lenth		42
//------------------
#define		ee_histroyparameter_page	0x14		//结算时间参数页地址
	#define		ee_histroyparameter_inpage	44
	#define		ee_histroyparameter_lenth	6
#define		ee_feik_number_page		0x14		//时区时段费率阶梯数页地址
	#define		ee_feiknumber_inpage		ee_histroyparameter_inpage+ee_histroyparameter_lenth+2
	#define		ee_feiknumber_lenth		8				
#define		ee_freezeparameter_page		0x16		//冻结时间参数页地址
	#define		ee_freezeparameter_inpage	44
	#define		ee_freezeparameter_lenth	12
	
#if(1 == CHINT_Mode)
	#define		ee_softij_page				0x17	//厂内模式有效时间页地址
	#define		ee_softij_inpage				44
	#define		ee_softij_lenth					4	
	#define		ee_softID_inpage				50 ///*内部ID 2字节*///	
#endif		
	
#define		ee_rtcadj_time_page		0x18		//写常温顶点调校值时时间记录页地址(始终不清)
	#define		ee_rtcadjtime_inpage		44
	#define		ee_rtcadjtime_lenth		10
#define		ee_pre_history_page		0x19		//专门用于上电补存的上一次结算时间页地址
	#define		ee_prehistory_inpage		44
	#define		ee_prehistory_lenth		5	
#define		ee_pre_dayfreeze_page		0x19		//专门用于上电补存的上一次日冻结时间页地址
	#define		ee_predayfreeze_inpage		ee_prehistory_inpage+ee_prehistory_lenth+2
	#define		ee_predayfreeze_lenth		5			
#define		ee_changecontrol_page		0x1a		//时区时段启动控制字页地址
	#define		ee_changecontrol_inpage		44
	#define		ee_changecontrol_lenth		2
#define 	ee_operatorcode_page		0x1a		//操作者代码页地址
	#define		ee_operatorcode_inpage		ee_changecontrol_inpage+ee_changecontrol_lenth+2
	#define		ee_operatorcode_lenth		4	
#define		ee_keystatus_page		0x1b		//密钥状态页地址
	#define		ee_keystatus_inpage		44
	#define		ee_keystatus_lenth		18	
#define		ee_meterstatus1_page		0x1c		//电表状态字1页地址
	#define		ee_meterstatus1_inpage		44
	#define		ee_meterstatus1_lenth		3
#define		ee_keystatus1_page		0x1c		//密钥状态页1地址
	#define		ee_keystatus1_inpage		ee_meterstatus1_inpage+ee_meterstatus1_lenth+2
	#define		ee_keystatus1_lenth		9	
#define		ee_xtlfstop_time_page		0x1d		//晶振停振起始时间页地址
	#define		ee_xtlfstoptime_inpage		44
	#define		ee_xtlfstoptime_lenth		7		
#define		ee_wdt_page			0x1e		//上电复位和看门狗复位次数页地址
	#define		ee_wdt_inpage			44	
	#define		ee_wdt_lenth			12
#define		ee_factoryinit_page		0x1f		//生产初始化标志页
	#define		ee_factoryinit_inpage		44
	#define		ee_factoryinit_len		8		
#define		ee_hardfault_page		0x1f		//hardfault复位时间和次数页地址
	#define		ee_hardfault_inpage		ee_factoryinit_inpage+ee_factoryinit_len+2
	#define		ee_hardfault_lenth		8
	
#define		ee_featureword_page		0x20		//特征模式字页地址
	#define		ee_featureword_inpage		0
	#define		ee_featureword_lenth		32
#define		ee_weekholiday_page		0x20		//周休日和周休日时段表号页地址
	#define		ee_weekholiday_inpage		ee_featureword_inpage+ee_featureword_lenth+2
	#define		ee_weekholiday_lenth		27
	
#define		ee_7051_page			0x22		//计量芯片调校页地址
#define		ee_7051adj_page			0x24		//电压补偿页
#define		ee_reportdata_page		0x26		//停电事件上报数据存储页(状态字1,上报状态字,新增次数和,复位定时器)
	#define		ee_reportdata_lenth		60	
#define		ee_power_down_page		0x27		//掉电页数据页地址
	#define		ee_powerdown_inpage		0
	#define		ee_powerdown_lenth		62
	#define		ee_loadpoint_lenth		5*max_casecount	

#define		ee_starttimer_page		0x28		//时区时段费率电价阶和梯电价启动时间页地址
	#define		ee_starttimer_inpage		0
	#define		ee_starttimer_lenth		20
#define		ee_displaypara_page		0x28		//显示数据页地址
	#define		ee_displaypara_inpage		ee_starttimer_inpage+ee_starttimer_lenth+2		
	#define		ee_displaypara_lenth		29		
//------------------		
#define		ee_ptatvalue_page		0x2a		//查表温度ADC页地址
	#define		ee_ptatvalue_inpage		0
	#define		ee_ptatvalue_lenth		42
#define		ee_trimvalue_page		0x2b		//查表补偿值页地址
	#define		ee_trimvalue_inpage		0
	#define		ee_trimvalue_lenth		42
	
#define		ee_loop_displayitem_page	0x2c		//循环显示项目页地址
#define		ee_key_displayitem_page		0x2d		//按键显示项目页地址
	#define		ee_displayitem_lenth		62	
#define		ee_loop_displayitem_page1 	0x32		//循环显示项目页地址
#define		ee_key_displayitem_page1	0x33		//按键显示项目页地址
	#define		ee_displayitem_inpage1		0		
	#define		ee_displayitem_lenth1		12

#define		ee_vollimit_page		0x32		//电压合格率等相关参数页
	#define		ee_vollimit_inpage		ee_displayitem_inpage1+ee_displayitem_lenth1+2
	#define		ee_vollimit_lenth		26	
#define		ee_password_page		0x32		//03级和04级密码页地址
	#define		ee_password_inpage		ee_vollimit_inpage+ee_vollimit_lenth+2
	#define		ee_password4_inpage		ee_password_inpage+ee_password_lenth+2
	#define		ee_password_lenth		4		

#if(1 == CHINT_Mode) 
#define		ee_7051_page2		0x32		//校表数据页2   4字节GPhs2+2字节crc
   #define  ee_7051_inpage2    ee_password4_inpage + ee_password_lenth + 2   
#endif


#define		ee_rpdl_page			0x34		//四象限无功数据页地址
	#define		ee_rpdl_inpage			0
	#define		ee_rpdl_lenth			(max_feilvcount+1)*4
	
#define		ee_synflash_page		0x3c		//时间回退数据记录页
	#define		ee_synflash_inpage		0
	#define		ee_synflash_len			max_casecount*4+4
#define		ee_validnum_page		0x3d		//分钟冻结起始有效页：依次max_casecount个方案，每个方案：EE起始次数(3)+Flash起始次数(3)
	#define		ee_validnum_inpage		0
	#define		ee_validnum_len			max_casecount*6

#define		ee_monthvolrun_page		0x3f		//日和月电压合格率运行状态
	#define		ee_monthvolrun_inpage		0
	#define		ee_monthvolrun_lenth		60					
	
#define		ee_bkdl_page			0x40		//反向电量数据页地址
	#define		ee_bkdl_inpage			0
	#define		ee_bkdl_lenth			(max_feilvcount+2)*4						
	
//------------------非自动crc校验区
//------------------高低温RTC查表区 前32字节低温+crc，后32字节高温+crc
#if( NEWCLOCKADJ == 0 ) //旧标准时钟调校
#define		ee_ptatvalue_lt_page		0x46		//查表温度ADC页地址，
	#define		ee_ptatvalue_lt_inpage		0
	#define		ee_ptatvalue_lt_lenth		30
#define		ee_ptatvalue_ht_page		0x46		//查表温度ADC页地址，
	#define		ee_ptatvalue_ht_inpage		32
	#define		ee_ptatvalue_ht_lenth		30
#define		ee_trimvalue_lt_page		0x47		//查表补偿值页地址
	#define		ee_trimvalue_lt_inpage		0
	#define		ee_trimvalue_lt_lenth		30
#define		ee_trimvalue_ht_page		0x47		//查表补偿值页地址
	#define		ee_trimvalue_ht_inpage		32
	#define		ee_trimvalue_ht_lenth		30
#else
//预留
#endif

#define		ee_holiday_page			0x42		//节假日时段表页地址,支持60个公共假日(共4页)
#define		ee_holiday_lenth			60

//------------------规格区
#define		ee_zichannum_page		0x48		//资产管理编码页地址
	#define		ee_zichannum_inpage		0
	#define		ee_zichannum_lenth		32
#define		ee_meterpos_page		0x48		//电能表位置信息
	#define		ee_meterpos_inpage		32
	#define		ee_meterpos_lenth		11		
#define		ee_meterdate_page		0x48		//生产日期
	#define		ee_meterdate_inpage		43
	#define		ee_meterdate_lenth		10
#define		ee_softbk_page			0x48		//软件备案号页地址
	#define		ee_softbk_inpage		53
	#define		ee_softbk_lenth			8
	
#define		ee_softver_page			0x49		//软件版本号页地址
	#define		ee_softver_inpage		0
	#define		ee_softver_lenth		32
#define		ee_hardver_page			0x49		//硬件版本号页地址
	#define		ee_hardver_inpage		32
	#define		ee_hardver_lenth		32
#define		ee_factorynum_page		0x4a		//厂家编码页地址
	#define		ee_factorynum_inpage		0
	#define		ee_factorynum_lenth		32
#define		ee_matertype_page		0x4a		//电表型号页地址
	#define		ee_matertype_inpage		32
	#define		ee_matertype_lenth		32				

#define		ee_bleslamac_page		0x4b		//蓝牙从机MAC地址（HEX格式）
	#define		ee_bleslamac_inpage		0
	#define		ee_bleslamac_lenth		18
#define		ee_blerefer_page		0x4b		//蓝牙参数页
	#define		ee_blerefer_inpage		ee_bleslamac_lenth
	#define		ee_blerefer_lenth		13
	#define		ee_blegbtime_inpage		ee_blerefer_inpage+ee_blerefer_lenth
	#define		ee_blegbtime_lenth		2
#define		ee_buymessage_page		0x4c		//售电信息页地址
	#define		ee_buymessage_inpage		0
	#define		ee_buymessage_lenth		24
#define		ee_zbid_bk_page			0x4c		//原载波id备份(通讯抄读专用)页地址
	#define		ee_zbid_bk_inpage		ee_buymessage_inpage+ee_buymessage_lenth
	#define		ee_zbid_bk_lenth		6	
	
//------------------事件记录区1		
#define         ee_maxi_note_page             	0x5e		//电流过载记录页地址
	#define		ee_maxinote_inpage		0
	#define		ee_maxinote_lenth		57	//数据长度57字节		
	
//------------------掉电统计数据	
#define		ee_powerdown_month_page		0x68		//月计量单元掉电事件记录页地址
	#define		ee_powerdownmonth_inpage	0
	#define		ee_powerdownmonth_lenth		8
	#define		max_powerdownmonth_p		36	
#define		ee_powerdown_year_page		0x6d		//年计量单元掉电事件记录页地址
	#define		ee_powerdownyear_inpage		0
	#define		ee_powerdownyear_lenth		8
	#define		max_powerdownyear_p		3

//------------------事件记录区1	
#define		ee_clockerrrecord_page		0x6e		//时钟故障记录
	#define		ee_clockerrrecord_inpage	0
	#define		ee_clockerrrecord_len		60	
#define		ee_nlineerrrecord_page		0x78		//零线电流异常记录
	#define   ee_nlineerrrecord_inpage		0
	#define	  ee_nlineerrrecord_len			60
#define		ee_poweroff_note_page		0x78		//上电上报记录页地址(虚拟)
	#define		ee_poweroffnote_inpage		ee_nlineerrrecord_inpage+ee_nlineerrrecord_len
	#define		ee_poweroffnote_lenth		25
#define		ee_poweron_note_page		0x78		//上电上报记录页地址(虚拟)
	#define		ee_poweronnote_inpage		ee_nlineerrrecord_inpage+ee_nlineerrrecord_len
	#define		ee_poweronnote_lenth		22	
#define         ee_lostv_note_page             	0x82		//失压记录页地址
	#define		ee_lostvnote_inpage		0
	#define		ee_lostvnote_len		61	
#define		ee_opencover_note_page		0x8c		//开盖记录页地址
	#define		ee_opencovernote_inpage		0
	#define		ee_opencovernote_lenth		60	
#define		ee_powerdown_note_page		0x96		//掉电事件记录页地址
	#define		ee_powerdownnote_inpage		0
	#define		ee_powerdownnote_lenth		47		
#define		ee_jieshuanrecord_page		0x96		//结算日编程记录页地址
	#define		ee_jieshuanrecord_inpage	ee_powerdownnote_inpage+ee_powerdownnote_lenth
	#define		ee_jieshuanrecord_lenth		16
#define		ee_setclock_note_page		0xa0		//设置时钟记录页地址
	#define		ee_setclocknote_inpage		0
	#define		ee_setclocknote_lenth		40
#define         ee_lowerv_note_page		0xa0		//低电压事件页地址
	#define		ee_lowervnote_inpage		ee_setclocknote_inpage+ee_setclocknote_lenth
	#define		ee_lowervnote_len		16	
#define         ee_batchange_note_page		0xaa		//时钟电池更换页地址
	#define		ee_batchangenote_inpage		0
	#define		ee_batchangenote_len		28
#define		ee_commerr_note_page		0xaa		//通讯模块异常记录
	#define		ee_commerrnote_inpage		ee_batchangenote_inpage+ee_batchangenote_len
	#define		ee_commerrnote_len		34	
#define		ee_calerr_note_page		0xb4		//计量芯片故障记录
	#define		ee_calerrnote_inpage		0
	#define		ee_calerrnote_len		28
#define		ee_commchange_note_page		0xb4		//通讯模块更换记录
	#define		ee_commchangenote_inpage	ee_calerrnote_inpage+ee_calerrnote_len
	#define		ee_commchangenote_len		28	
#define		ee_cleardl_note_page		0xbe		//清电量事件页地址
	#define		ee_cleardlnote_inpage		0
	#define		ee_cleardlnote_lenth		34
#define		ee_combstatusrecord_page	0xbe		//有功组合状态字记录页地址
	#define		ee_combstatusrecord_inpage	ee_cleardlnote_inpage+ee_cleardlnote_lenth
	#define		ee_combstatusrecord_lenth	11	
#define		ee_rp2combstatusrecord_page	0xbe		//无功组合状态字2记录页地址
	#define	 	ee_rp2combstatusrecord_inpage	ee_combstatusrecord_inpage+ee_combstatusrecord_lenth
	#define	 	ee_rp2combstatusrecord_lenth	11				
#define		ee_closerelay_note_page		0xc8		//合闸事件记录页地址
	#define		ee_closerelaynote_inpage	0
	#define		ee_closerelaynote_lenth		34
#define		ee_batterlow_note_page		0xc8		//电池欠压记录页
	#define		ee_batterlownote_inpage		ee_closerelaynote_inpage+ee_closerelaynote_lenth
	#define		ee_batterlownote_len		22	
#define		ee_openrelay_note_page		0xd2		//断闸事件记录页地址
	#define		ee_openrelaynote_inpage		0		
	#define		ee_openrelaynote_lenth		34
#define		ee_powererr_note_page		0xd2		//电源异常记录页地址
	#define		ee_powererrnote_inpage		ee_openrelaynote_inpage+ee_openrelaynote_lenth
	#define		ee_powererrnote_lenth		20
#define		ee_relayerr_note_page		0xdc		//负荷开关异常记录页地址
	#define		ee_relayerrnote_inpage		0
	#define		ee_relayerrnote_lenth		29
#define		ee_rp1combstatusrecord_page	0xdc		//无功组合状态字1记录页地址
	#define		ee_rp1combstatusrecord_inpage	ee_relayerrnote_inpage+ee_relayerrnote_lenth
	#define		ee_rp1combstatusrecord_lenth	11
#define         ee_highv_note_page		0xdc		//高电压事件页地址
	#define		ee_highvnote_inpage		ee_rp1combstatusrecord_inpage+ee_rp1combstatusrecord_lenth
	#define		ee_highvnote_len		16						
#define		ee_program_note_page		0xe6		//编程事件页地址
	#define		ee_programnote_inpage		0
	#define		ee_programnote_lenth		50
	#define		max_eventrecord_p		10	//事件指针最大值(10次)	
#define		ee_clearevent_note_page		0xe6		//清事件记录页地址
	#define		ee_cleareventknote_inpage	ee_programnote_inpage+ee_programnote_lenth
	#define		ee_cleareventnote_lenth		14
//------------------密钥区
#define		ee_keydata_1_page		0xf0		//编号0 的32字节密钥+编号1 的32字节密钥，依次向下每页2组		

//------------------事件记录区2
#define		ee_gbsetclock_note_page		0x100		//广播设置时钟记录页地址（100条）
	#define		ee_gbsetclocknote_inpage	0
	#define		ee_gbsetclocknote_lenth		36
	#define		max_gbsetclock_p		100	//广播校时最大记录数

//------------------电压合格率记录区		
#define         ee_monvolpass_note_page	        0x122		//月电压合格率页地址
	#define		ee_monvolpassnote_inpage	0
	#define		ee_monvolpassnote_len		(29-2)	//目前645规约定义27字节
	#define		max_monvolpass_p		12	
#define         ee_dayvolpass_note_page	        0x125		//日电压合格率页地址
	#define		ee_dayvolpassnote_inpage	0
	#define		ee_dayvolpassnote_len		29
	#define		max_dayvolpass_p		92
											
//------------------用电量计算区
#define		ee_pre1_histroyusedl_page	0x13d		//上1-25结算历史用电量页地址	
#define		ee_pre1_mhistroyusedl_page	0x13e		//上1-25月历史用电量页地址
	#define		ee_histroyusedl_lenth		100
#define		ee_pre1_yhistroyusedl_page	0x13f		//上1-7年历史用电量页地址	
	#define		ee_yhistroyusedl_lenth		56	
#define		ee_illegalcardnum_page		0x13f		//累计时间(持续时间)页
#define		ee_illegalcardnum_inpage		56
#define		ee_illegalcardnum_len			48

//------------------阶梯参数和阶梯编程记录
#define		ee_jtpricerecord2_page		0x140		//阶梯表编程记录(目前程序实际按照2张记录事件)
	#define		ee_jtpricerecord2_inpage	0	
	#define		ee_jtpricerecord2_len		70		
#define		ee_ladder1_page			0x148		//当前套阶梯表电量/电价，4张表，每页一张表
#define		ee_ladder2_page			0x14c		//备用套阶梯表电量/电价，4张表，每页一张表
	#define		ee_ladder_lenth			70
	
#define		ee_shiqurecord_page		0x140		//时区表编程记录页地址
	#define		ee_shiqurecord_lenth		57
#define		ee_shiduanrecord_page		0x142		//时段表编程记录页地址
	#define		ee_shiduanrecord_lenth		57
#define		ee_jtpricerecord_page		0x144		//阶梯表编程记录(发生时间6和操作者代码4)
	#define		ee_jtpricerecord_inpage		70	
	#define		ee_jtpricerecord_len		10
#define		ee_keysetrecord_page		0x144		//密钥更新记录页
	#define		ee_keysetrecord_inpage		ee_jtpricerecord_inpage+ee_jtpricerecord_len
	#define		ee_keysetrecord_len		15	
#define		ee_week_note_page		0x144		//周休日编程记录
	#define		ee_week_note_inpage		ee_keysetrecord_inpage+ee_keysetrecord_len
	#define		ee_week_note_len		11		
	
//------------------冻结记录区
#define		ee_timingfreeze_dl_page		0x150		//定时冻结数据页地址
	#define		max_timingfreeze_p		60	//约定冻结电量指针最大值(最大60次)
#define		ee_dayfreezedl_page		0x153		//日冻结数据页地址
	#define		max_dayfreeze_p			254	//日冻结电量指针最大值(最大254天), EE只存储最近一条
#define		ee_realtimefreeze1_page		0x156		//瞬时冻结冻结页地址
#define		ee_appointfreeze1_page		0x15f		//时区转换约定冻结页地址
#define		ee_appointfreeze2_page		0x165		//时段转换约定冻结页地址
#define		ee_appointfreeze3_page		0x16b		//阶梯时区转换约定冻结页地址
#define		ee_appointfreeze4_page		0x171		//阶梯转换约定冻结页地址
	#define		ee_freezedl_lenth		(5+max_dl_lenth*6+8)
#define         ee_monthfreeze_page             0x177		//月冻结电量页地址
#define         ee_histroy_dl_page              0x17a		//结算日电量页地址
	#define		ee_histroydl_lenth		(5+max_dl_lenth*6+8)
	#define		max_histroy_p			24	//结算电量指针最大值(最大24次), EE只存储最近一条
//------------------负荷记录区
#define		ee_ploadrec_page		0x17d
	#define		ee_ploadrec1_inpage		0	//时间(5)+电压(2)+电流(3)+频率(2)
	#define		ee_ploadrec1_len		12
	#define		ee_ploadrec2_inpage		ee_ploadrec1_inpage+ee_ploadrec1_len	//时间(5)+有功功率(3)+无功功率(3)
	#define		ee_ploadrec2_len		11
	#define		ee_ploadrec3_inpage		ee_ploadrec2_inpage+ee_ploadrec2_len	//时间(5)+功率因数(2)
	#define		ee_ploadrec3_len		7
	#define		ee_ploadrec4_inpage		ee_ploadrec3_inpage+ee_ploadrec3_len	//时间(5)+正反向总电量(8)+组合无功(4+4)
	#define		ee_ploadrec4_len		21
	#define		ee_ploadrec5_inpage		ee_ploadrec4_inpage+ee_ploadrec4_len	//时间(5)+四象限无功(4×4)
	#define		ee_ploadrec5_len		21
	#define		ee_ploadrec6_inpage		ee_ploadrec5_inpage+ee_ploadrec5_len	//时间(5)+组合有功费率1~4电量(5×4)
	#define		ee_ploadrec6_len		25
	#define		ee_ploadrec_lenth		97
	#define		max_ploadrec_p			365*96	//负荷记录指针最大值(最大35040次), EE只存储最近一条

//------------------整点冻结记录区	
#define         ee_hourfreezedl_page	        0x17e		//整点冻结电量页地址
	#define		ee_hourfreezedl_inpage		0
	#define		ee_hourfreezedl_lenth		13
	#define		max_hourfreeze_p		254	//整点冻结电量指针最大值(254整点), EE只存储最近一条			

//;=============================相关常数定义＝==========================================
#define		maxtimes			6		//最大脉冲倍数,96A时,7个脉冲/s
#define		max_maxholiday			60		//最大公共假日数
#define		ms_timer_delay			115		//460ms时标定时,刷新显示
#define		comm_led_timer_delay		5		//5s通讯指示灯
#define		shiduanctrl_timer_delay		20		//80ms时段改变输出定时器延时
#define		max_shiduancount		14		//最大时段14字节时段表
#define		default_loopdisplaytimer	5		//默认的循显时间5s
#define		default_keydisplaytimer		60		//默认按键显示时间为60s
#define		lcdled_timer_delay		60		//60s背光亮
#define	 	disp_num			42		//显示列表中的项目数
#define		max_casecount			6		//分钟冻结最大支持类
#define		max_feilvcount			12		//最大费率数
#define		max_dl_lenth		((max_feilvcount+1)*4)	//总和费率电量总字节数
#define		max_disploop		((max_feilvcount+1)*13)	//仅支持当前和上1~12月电量显示

#define 	ESAM				0		//esam
#define 	CARD				1		//IC card
#define 	u7816_buf_size			250		//

//;==============================变量类型定义＝============================================
typedef unsigned char	uint08; 		//unsigned 8 bit data
typedef unsigned short	uint16;
typedef	unsigned long int uint32;

typedef signed char	int08; 			//unsigned 8 bit data
typedef signed short	int16;
typedef	signed long int	int32;

typedef union
{
  unsigned char B08;
  struct
  {
    unsigned char bit0:1;
    unsigned char bit1:1;
    unsigned char bit2:1;
    unsigned char bit3:1;
    unsigned char bit4:1;
    unsigned char bit5:1;
    unsigned char bit6:1;
    unsigned char bit7:1;
  }Bit;
}B08_Bit;

union B16_B08_2						//小端存储(51为大端)
{
	unsigned short	B16;
	unsigned char	B08[2];
};

union S16_B08_2						//小端存储(51为大端)
{
	unsigned char	B08[2];
	signed short	S16;
};

union B32_B08_2						//小端存储(51为大端)
{
	unsigned long int B32;
	unsigned char	B08[4];
};

union S32_B08_2						//小端存储(51为大端)
{
	signed long int B32;
	signed char	B08[4];
};

union B64_B08_2						//小端存储(51为大端)
{
	unsigned long long B64;
	unsigned char     B08[8];
};

union S64_B08_2						//小端存储(51为大端)
{
	signed long long S64;
	signed char     B08[8];
};

union B16_B08
{
	unsigned char	B08[2];
  //unsigned int B16;
};

union S16_B08
{
	unsigned char	B08[2];
  //unsigned int S16;
};

union B32_B08
{
	unsigned char	B08[4];
  //unsigned long int B32;
};


struct PLUSE_FRM								//小端存储(51为大端)
{
	union B32_B08_2	Pluse[max_feilvcount+1];	//总和各费率脉冲尾数
	union B32_B08_2	UPluse;				//本月用电量(脉冲数)
	union B16_B08	Crc16;		
};

struct RPLUSE_FRM								//小端存储(51为大端)
{
	union B32_B08_2	Pluse[max_feilvcount+1];	//总和各费率脉冲尾数(四象限无功)
	union B16_B08	Crc16;		
};


struct LOADREC_FRM
{
	unsigned char Point[5*max_casecount]; 			//总次数(3)+待同步数(2)
	union B16_B08_2	Crc16;   			//CRC校验码
};


struct METERCONST_FRM
{
	union B32_B08	Const;				//脉冲常数bcd码,4字节,高字节在前
	union B16_B08 	Crc16;				//CRC校验码
	uint08		Const_H;			//0.01kwh的脉冲数
};

struct PARA_ESAM_FRM
{
	uint08		Current_Ratio[3];		//电流变比
	uint08		Voltage_Ratio[3];		//电压变比
	uint08		Meter_Id[6];			//表号
	uint08		User_Id[6];			//用户号
	uint08		Zb_Id[6];			//模块
	union B16_B08	Identity_Delay;			//身份认证时效
	union B16_B08 	Crc16;				//CRC校验码
};


struct PARA_DISPLAY_FRM
{
	uint08		S_Number;			//显示屏数
	uint08		Loop_Time;			//循显时间
	uint08		Dl_Dot;				//电量小数位数
	uint08		P_Dot;				//功率小数位数
	uint08		K_Number;			//按键显示屏数
	uint08		Temp;				//预留
	uint08		Temp2;				//预留
	uint08		A_Time;				//上电全显时间
	uint08		Lstarttimer[5];			//负荷记录起始时间,内部扩展年,共5字节(年在前)
	union B16_B08	Lspacetimer[8];			//第1~5类负荷记录间隔时间,共16字节(高字节在前)	
	union B16_B08 	Crc16;				//CRC校验码
	uint08		Dl_Dot_Auto;			//电量自适应显示小数位数
};

struct COMM_ADDRESS_FRM
{
	uint08		Comm_Id[6];			//通讯地址
	union B16_B08 	Crc16;				//CRC校验码
};

struct RTC_TRIMA_FRM
{
	uint16		PTAT_Value[21];			//温度ADC
	union B16_B08 	Crc16;				//CRC校验码
};

struct RTC_TRIMV_FRM
{
	int16		Trim_Value[21];			//补偿值
	union B16_B08 	Crc16;				//CRC校验码
};

struct RTC_TRIM_FRM
{
	struct RTC_TRIMA_FRM	TAdc;
	struct RTC_TRIMV_FRM	TVal;
	int16		TestTrim;
	uint08		TempFlag;			//查表表格温度标志 0=常温，1=低温，2=高温
	float		CFixTrim;			//查表中心误差
};

struct STARTTIME_FRM
{
	uint08		Shiqu[5];			//新时区启动时间
	uint08		Shiduan[5];			//新时段表启动时间
	uint08		LadSQ[5];			//阶梯时区切换时间
	uint08		Ladder[5];			//阶梯启动时间
	union B16_B08 	Crc16;				//CRC校验码
};

struct EMU_FRM
{
	union B32_B08_2	rate[5];						//小端存储(51为大端)
	union B16_B08_2	Crc16;				//CRC校验码
};


struct WEEK_FRM
{
	uint08		Status;				//周休日
	uint08		Shiduan_N;			//时段表号(范围0~7)	
	union B16_B08	Freeze[7];			//负荷/定时/瞬时/约定/整点/日冻结/月冻结模式字	
	uint08		Temp[1];			//预留1	
	union B16_B08	Max_I;				//过流事件电流触发下限
	uint08		Max_I_Period;			//过流事件电流延时时间	
	union B32_B08	NLine_I;			//电流触发下限	
	union B16_B08	NLine_Limit;			//电流不平衡率限值
	uint08		NLine_Period;			//延时判定时间	bcd					
	union B16_B08 	Crc16;				//CRC校验码	
};


struct VOLLMT_FRM
{
	union B16_B08	MaxVolLmt;			//合格率电压上限值
	union B16_B08	MinVolLmt;			//合格率电压下限值
	union B16_B08	ChkMaxVol;			//合格率电压考核上限
	union B16_B08	ChkMinVol;			//合格率电压考核下限
	
	union B16_B08	Lost_V_Min;			//失压事件电压触发上限
	union B16_B08	Lost_V_Max;			//失压事件电压恢复下限	
	union B32_B08	Lost_V_I;			//失压事件电流触发下限
	uint08		Lost_V_Period;			//失压事件延时判定时间	bcd
	
	union B16_B08	Lower_V;			//低电压事件电压触发上限
	union B16_B08	Lower_V_Period;			//低电压事件延时判定时间	bcd	
	union B16_B08	High_V;				//高电压事件电压触发上限
	union B16_B08	High_V_Period;			//高电压事件事件延时判定时间	bcd
	
	uint08		Cal_Err_Period;			//计量故障判定延时 bcd
	union B16_B08 	Crc16;				//CRC-16
};

struct VOLPASS_FRM					//该结构体必须是4字节的倍数,否则程序不支持
{
	union B32_B08_2	Total;				//电压监测时间
	union B32_B08_2	HighTime;			//电压超上限时间
	union B32_B08_2	LowTime;			//电压超下限时间
	union B16_B08_2	MaxVol;				//最高电压
	union B16_B08_2	MinVol;				//最低电压
	unsigned char	MaxMoment[4];			//最高电压出现时间
	unsigned char	MinMoment[4];			//最低电压出现时间
	union B32_B08_2	AverVol_Cnt;			//平均电压累计次数
	union B16_B08_2	AverVol;			//平均电压
};


struct PARA_FEATUREWORD_FRM
{
	uint08		Bps[1];				//通信口1
	uint08		Comp_B;				//有功组合字
	uint08		Temp[4];			//预留4
	uint08		Powerd_Period;			//停电事件判断延时 bcd
	uint08		Report_Period;			//主动上报时限(bcd码)单位分钟
	uint08		Feature1;			//特征字1
	uint08		Report[8];			//上报模式字
	uint08		Limit_I[3];			//继电器拉闸控制电流门限值
	uint08		Exp_Timer[6];			//扩展分钟定时bcd码,分别为拉闸延时2,大电流拉闸延时2,红外认证时间1,上报自动复位时间1
	uint08		Wz_Clocerelay;			//继电器合闸允许方式(0x55内置表示自动合闸,0x55外置表示手动合闸)
	uint08		Plc;				//扩展模式字,bit7=1每天20:00复位载波一次(主要针对瑞斯康载波),bit2=1红外遥控器点亮背光,bit1=1欠压点亮背光,bit0=1反向点亮背光
	uint08		Rpcomp[2];			//无功组合字1和2
	uint08		Zbbps;				//载波通信口
	uint08		Chblebps;			//蓝牙通信口(预留)
	union B16_B08 	Crc16;				//CRC校验码
	uint16		Report_Timer;			//主动上报时限(hex码)单位秒
	uint08		Zbbps_Ram;			//载波通信口(协商或者设置的波特率)
};


struct TEMPERATURE_FRM
{
	uint08		Offset[8];			//温度调整系数8字节
	uint08		RtcTMode;			//RTC补偿工作模式，0x55:测试模式，0xAA常温查表插值模式，其他：普通模式
	uint08		krh;				//晶体系数常温修调值
	uint08		krl;
	union B16_B08 	Crc16;				//CRC校验码
};


struct PRICE_FRM
{
	union B32_B08	Ladder_Dl[6];			//当前阶梯电量
	union B32_B08	Ladder[7];			//当前阶梯电价
	uint08		Year_Ladder[18];		//当前年阶梯结算日1~6
	union B16_B08 	Crc16a;				//CRC校验码
	union B32_B08   Current_L;			//当前阶梯电价
//	union B32_B08   Current_F;			//当前费率电价
	union B32_B08   Current;			//当前电价
	union B32_B08   Current_X;			//当前电价乘以变比后电价
	uint08		Ladder_Mode;			//结算模式字,0x00为月结算,0x55为年结算
};

struct TARIFF_FRM
{
	uint08		Table[42];			//当前费率时段表,3*14＝42字节
	union B16_B08 	Crc16;				//CRC校验码
	uint08		Current;			//当前费率(范围0~11)
	uint08		Current_Ladder;			//当前阶梯(范围0~4)
	uint08		Current_N;			//当前时段表号(范围0~7)
	uint08		Period_N;			//当前时段号(范围0~13)
	uint08		CurLad_N;			//当前阶梯表号(范围0~3)
	uint08		Status;				//bit3时区/bit2时段表/bit1费率/bit0阶梯(0:第一套；1:第二套)
		
};


struct ITEM_FRM
{
	uint16		 Display[99];			//显示项目1*62存放在1页,共4页
	union B16_B08 	 Crc16;
};

struct SYS_CLOCK_FRM
{
	uint08   	Clockmain[7];			//系统时钟,[0]秒[1]分[2]时[3]周[4]日[5]月[6]年
	uint08   	Clockbackup[7];			//系统时钟,[0]秒[1]分[2]时[3]日[4]月[5]年[6]周
//	uint08   	Status;				//时钟状态字
};

struct UIP_FRM
{
	union B32_B08_2   U;				//电压xxxxxxx.x				小端存储(51为大端)
	union B32_B08_2   I1;				//电流xxxxx.xxx
	union B32_B08_2   P1;				//有功功率xxxx.xxxx
	union B32_B08_2   I2;				//零线电流xxxxx.xxx	
	union B32_B08_2   P2;				//视在功率xxxx.xxxx
	union B32_B08_2   Cosa;				//功率因数xxxxx.xxx
	union B32_B08_2   Pav;				//一分钟平均功率xxxx.xxxx
	union B32_B08_2   Freq;				//电网频率
	union B32_B08_2   Q1;				//无功功率xxxx.xxxx
	union B32_B08_2   Iav[3];			//一分钟平均电流xxxxx.xxx(保存3分钟)
	union B32_B08_2   Qav;				//一分钟平均无功功率xxxx.xxxx
	union B32_B08_2   Uav;				//一分钟平均电压xxxxxxx.x	
};

struct FUNCTION_FRM
{
	uint16		Temper_M;			//当前电表温度xxx.x
	uint16		Voltage_B;			//当前电池电压xx.xx
	uint16		Voltage_P;			//当前电源电压xx.xx
	uint32		Voltage_B_T;			//电池电压工作时间xxxxxxxx(hex保存)
};

struct TMR_STS_FRM
{
	uint08		Timer;				//定时器
	uint08		Status;				//状态
};

struct TIMER_FRM
{
	uint08		Timer;				//定时器
};

struct STATUS_FRM
{
	uint08		Status;				//状态
};

struct DECIMAL_FRM
{
	uint08		Add;				//脉冲增量
	uint08		Add_Rp;				//无功脉冲增量
	uint08		Status;				//bit4正向脉冲改变,bit5反向脉冲改变,bit0~3四象限无功脉冲改变
};

struct DISPALY_FRM
{
	uint08		Number;				//显示号
	uint08		Timer;				//显示时间
	uint08		Status;				//状态
};

struct EEPROM_FRM
{
	uint08		Buffer[128*3];			//数据ee处理缓冲/lcd显示缓冲复用
	uint08		Status;				//状态字节
};

struct HisEvent_STR
{
	unsigned short 	DI21;	
	unsigned short 	page;
	unsigned char  	offset;
	unsigned char  	len;
	unsigned char  	offset2;
};

struct ADCDATA_FRM
{
	uint16		Buffer[32];			//ADC结果
	uint08		ReadCount;			//计数
};

struct FEIK_FRM
{
	unsigned char Num[8];
	union B16_B08 Crc16;
};

struct TIMER2_FRM
{
	//0零线电流不平衡持续时间(4)
	//1过流持续时间(4)
	//2电池欠压总累计时间(4)
	//3掉电总累计时间(4)
	//4电池工作时间(4) 
	//5失压持续时间(4) 
	//6低压年累计时间(4)
	//7高压年累计时间(4)
	//8月停电累计次数(4)---
	//9月停电累计时间(4)
	//10年停电累计次数(4)---
	//11年停电累计时间(4)
	uint32	Times[12];
};

struct BLEDEVICE_FRM
{
	uint08	Ble_A2;
	uint08	Ble_A3;
	uint08	Ble_Sta;
	uint08	Ble_Mac[6];	//2主+3从
};

//该结构体不要轻易调整
typedef struct
{
//nw
struct  TIMER_FRM	near	Progkey;	//240min编程(停电运行)
struct  STATUS_FRM	near	Cover;	//开盖参数(停电保存) 
uint08			near 	Mac_Err_Times;	//MAC校验失败次数
uint08			near 	G_Clockerr_Times;//明文广播校时记录故障次数
uint08			near 	System_St_Bk;	//系统状态字备份(停电运行)--－－起始地址必须失4的倍数
uint08			near 	Report_Data[5];	//有效上报状态字
uint08			near 	Report_Data2[5];	//有效上报状态字备份
uint08			near 	Report_Num[40];	//事件上报新增次数
uint08			near 	RReport_Status;	//之前已读上报状态允许复位上报状态
uint32			near	Meter_Run_Timer4;//上电总运行时间
uint16			near 	Reset_Rep_Timer;	//复位上报状态字定时器
uint08			near	Password_Err[2];	//密码错误次数
struct	LOADREC_FRM	near	Load;			//负荷指针
uint16			near 	Meter_Run_Timer1;//电表上电运行时间1(时间不足1小时,则掉电后不进行掉电发生上报)
uint16			near 	Meter_Run_Timer2;//电表上电运行时间2(时间不足1小时,则掉电后不进行掉电结束上报)
uint08			near	Wr_Ext_Number;	//内部扩展命令写ee允许次数
struct	PLUSE_FRM	near	Fwdl;		//正向有功脉冲数和校验
struct	PLUSE_FRM	near	Bkdl;		//反向有功脉冲数和校验
struct	RPLUSE_FRM	near	Rpdl[4];	//四象限无功脉冲数和校验
uint08			near	RAMREG0;	//定义特殊寄存器
uint08			near	RAMREG1;	//
uint08			near	RAMREG2;	//
uint08			near	RAMREG3;	//
uint08			near	RAMREG4;	//
uint08			near	RAMREG5;	//
uint08			near	RAMREG6;	//
uint08			near	RAMREG7;	//
uint08			near	RAMREG8;	//
uint08			near	RAMREG9;	//
uint08			near	RAMREG10;	//
uint08			near	RAMREG11;	//
uint08			near	RAMREG12;	//
uint08			near	RAMREG13;
uint08			near	RAMREG14;
uint08			near	RAMREG15;
uint08			near	RAMBUF[32];
}NoInit_t ;

//定义通信超时时间常数
#define txtimeout_max	125				//500ms，串口字符间最大延时
#define rxtimeout_max	125  				//500ms 
#define framedelay_mx	15 				//60ms
//通信缓冲区最大长度定义
#define	utx_buf_size	250				//通信缓冲区最大长度＝220
#define	urx_buf_size	250				//通信缓冲区最大长度＝220
#define frm_buf_size	1000			//多帧通信最大字节数=2048

struct COMMUNICATION_FRM
{
	uint08 Buf[ urx_buf_size ];			//接收缓冲/发送缓冲
	uint08 Len;					//接收长度字节/发生长度
	uint08 Total_Len;				//接收总长度/发送总长度
	uint08 Step;  					//接收步骤
	uint08 Flag;  					//通讯标志
	uint08 Response_Timer;				//通讯响应定时器
	uint08 Overtime_Timer;				//通讯接收或者发生超时定时器
	
	uint08 TxBuf[ urx_buf_size ];   		//发送缓冲
	uint08 TxLen;					//发送长度
	uint08 Total_Tx; 				//发送总长度
	uint16 S_Overtime_Timer;			//发送超时(载波专用)
	uint16 RptTimer;  				//重发计时器
	uint08 Transfer;  				//预留

	uint08 DI[4];       //多帧通信 数据标识
	uint08 Sn;          //多帧通信 序号
	uint16 FrmLen;      //多帧通信 数据长度
	uint16 FrmOffset;   //多帧通信 偏移量
	uint08 FrmBuf[ frm_buf_size ]; //多帧通信 缓冲区, 日时段表编程记录占用最多196+195+195+96=682
};


//------ FLASH 定义 ------
typedef struct
{
	unsigned short DataPage;  //数据ee页地址
	unsigned short Offset;    //数据ee页内偏移
	unsigned short AppPage;   //补充区地址
	unsigned short AppPos;    //补充区内偏移
	unsigned char  Clk[16];
} RtFlash;

typedef struct
{
	unsigned char Result;
	unsigned long Addr;
} FindInf;

typedef struct
{
	struct
	{
		unsigned short Page; //回退的扇区
		unsigned short Len;  //保留的字节数
	}HisRec[max_casecount];
	unsigned long Newptr;     //新增指针
	unsigned short Crc16;     //校验码
} RtRecord;

typedef struct
{
	unsigned char  Dir;   //搬移方向：0x00空闲；0x55当前区到备份区, 0xAA备份区到当前区
	unsigned char  Obj;   //对象+方案号
	unsigned short Page;  //
	unsigned short Offset; //
	unsigned short Len;  //总长度
} MoveRec;

typedef struct
{
	unsigned short TotLen;  //记录总字节数
	unsigned short Depth;   //存储深度
	unsigned long  MaxDepth; //最大存储深度
	unsigned long  CurPoint; //当前记录数
	unsigned short ValPoint; //有效记录数
}RecStore; 

typedef struct
{
	unsigned short Page;    //当前操作的扇区
	unsigned char  RpTimes; //此扇区允许擦除次数
	unsigned char  Enable;  //启动同步标志：0=空闲; 1=启动
}SynRec;


#if(1 == CHINT_Mode)
struct Ijtimer_FRM
{
	union   B32_B08_2		Ijtimer;//厂内模式定时器 	
	union 	B16_B08 	Crc16;	//CRC校验码
};
#endif

#define		FPAGE_SIZE    256L  //页  的字节数
#define		SECTOR_SIZE   4096L //扇区的字节数
#define		SECTOR_NUM    1024   //扇区的总个数(32M位的flash)
#define		FL_NEW_ADDR    0    //新增区域 用于时间回退时，遇到目标区域未更新完毕，新记录暂时存储于此
#define		FL_OLD_ADDR    1    //备份区域 用于时间回退时，更新目标区域数据过程中，历史数据暂时存储区域

#define		FL_SECTOR_RECNUM      (SECTOR_SIZE/ee_freezedl_lenth)	//一个扇区存储的记录条数 4096/325 = 12.6

#define		FL_TIMING_SECTORNUM   ((max_timingfreeze_p+FL_SECTOR_RECNUM-1)/FL_SECTOR_RECNUM+1) //定时冻结  6个扇区
#define		FL_TIMING_ADDR	   2	//定时冻结 Flash存储起始扇区

//------- 负荷记录占用Flash情况 ---------
#define		FL_LOADREC_ADDR	     (FL_TIMING_ADDR+FL_TIMING_SECTORNUM) //负荷记录 Flash存储起始扇区 4+6 = 0x0A
#define		FL_CASE1_RECNUM      (SECTOR_SIZE/ee_ploadrec1_len)  //负荷记录方案1 341
#define		FL_CASE2_RECNUM      (SECTOR_SIZE/ee_ploadrec2_len)  //负荷记录方案2 372
#define		FL_CASE3_RECNUM      (SECTOR_SIZE/ee_ploadrec3_len)  //负荷记录方案3 585
#define		FL_CASE4_RECNUM      (SECTOR_SIZE/ee_ploadrec4_len)  //负荷记录方案4 195
#define		FL_CASE5_RECNUM      (SECTOR_SIZE/ee_ploadrec5_len)  //负荷记录方案5 195
#define		FL_CASE6_RECNUM      (SECTOR_SIZE/ee_ploadrec6_len)  //负荷记录方案6 163
#define		FL_LOADREC1_SECTORNUM  ((max_ploadrec_p+FL_CASE1_RECNUM-1)/FL_CASE1_RECNUM+1)   //104个扇区
#define		FL_LOADREC2_SECTORNUM  ((max_ploadrec_p+FL_CASE2_RECNUM-1)/FL_CASE2_RECNUM+1)   // 96个扇区
#define		FL_LOADREC3_SECTORNUM  ((max_ploadrec_p+FL_CASE3_RECNUM-1)/FL_CASE3_RECNUM+1)   // 61个扇区
#define		FL_LOADREC4_SECTORNUM  ((max_ploadrec_p+FL_CASE4_RECNUM-1)/FL_CASE4_RECNUM+1)   //181个扇区
#define		FL_LOADREC5_SECTORNUM  ((max_ploadrec_p+FL_CASE5_RECNUM-1)/FL_CASE5_RECNUM+1)   //181个扇区 
#define		FL_LOADREC6_SECTORNUM  ((max_ploadrec_p+FL_CASE6_RECNUM-1)/FL_CASE6_RECNUM+1)   //216个扇区 
#define		FL_REC_END_ADDR        (FL_LOADREC1_SECTORNUM+FL_LOADREC2_SECTORNUM+FL_LOADREC3_SECTORNUM+FL_LOADREC4_SECTORNUM+FL_LOADREC5_SECTORNUM+FL_LOADREC6_SECTORNUM)

//------- 整点冻结占用Flash情况 ---------
#define		FL_SECTOR_HOURNUM     (SECTOR_SIZE/ee_hourfreezedl_lenth)	//一个扇区存储的记录条数
#define		FL_HOUR_SECOTRNUM     ((max_hourfreeze_p+FL_SECTOR_HOURNUM-1)/FL_SECTOR_HOURNUM+1)	//整点冻结  2个扇区
#define		FL_HOUR_ADDR          (FL_LOADREC_ADDR+FL_REC_END_ADDR) //整点冻结 Flash存储起始扇区

//------- 日冻结占用Flash情况 ---------
#define		FL_DAY_SECTORNUM      ((max_dayfreeze_p+FL_SECTOR_RECNUM-1)/FL_SECTOR_RECNUM+1)	//日冻结   23个扇区
#define		FL_DAY_ADDR		      (FL_HOUR_ADDR+FL_HOUR_SECOTRNUM) //日冻结   Flash存储起始扇区

//------- 月冻结占用Flash情况 ---------
#define		FL_MONTH_SECTORNUM    ((max_histroy_p+FL_SECTOR_RECNUM-1)/FL_SECTOR_RECNUM+1)	//月冻结    3个扇区
#define		FL_MONTH_ADDR	      (FL_DAY_ADDR+FL_DAY_SECTORNUM) //月冻结   Flash存储起始扇区

//------- 结算冻结占用Flash情况 ---------
#define		FL_HISTORY_SECTORNUM  ((max_histroy_p+FL_SECTOR_RECNUM-1)/FL_SECTOR_RECNUM+1)	//结算冻结  3个扇区
#define		FL_HISTORY_ADDR	      (FL_MONTH_ADDR+FL_MONTH_SECTORNUM) //结算冻结 Flash存储起始扇区
//-------------------------------

#endif




