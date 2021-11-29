//************************************************************************///
//*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
//*File name:     Public_Code.h
//*Author:        
//*Version:       V1
//*Date:          2018-3-26
//*Description:   此文件是内部编码结构解析查表
//*Function List: 
//*History:       修改日期、修改者、修改内容简述
//*1. Date:
//*   Author:
//*   Modification:
//*2. Date:
//*   Author:
//*   Modification:
//************************************************************************///
#ifndef	__Public_Code_H
#define	__Public_Code_H


/*包含头文件*/
#include "Public.h"

///********macro 返回值********///
#define		C_Code_OK						0x00		/*成功*/
#define		C_CodeOfTable					0x68		/*表格里的编码*/
#define		C_CodeOfString					0x86		/*string类型的编码*/
#define		C_CodeOfSimple					0x55		/*简单类型的编码*/
#define		C_CodeOfCSD						0x5A		/*CSD的编码*/
#define		C_CodeErr						0xAA		/*错误的的编码*/
#define		C_Code_OverStep					C_OverStep_DAR		/*越界*/

#define		C_Starting						0x86	/*开始*/
#define		C_Ending						0x68	/*结束*/
#define     C_ServerError_DAR			254	///* 服务异常 *///

///***************数据类型定义**************///
#define		C_us_null						0x0000
#define		C_us_bool						0x0003
#define		C_us_double_long				0x0005
#define		C_us_double_long_unsigned		0x0006
#define		C_us_integer					0x000F
#define		C_us_long						0x0010
#define		C_us_unsigned					0x0011
#define		C_us_long_unsigned				0x0012
#define		C_us_long64						0x0014
#define		C_us_long64_unsigned			0x0015
#define		C_us_enum						0x0016
#define		C_us_float32					0x0017
#define		C_us_float64					0x0018
#define		C_us_date_time					0x0019
#define		C_us_date						0x001A
#define		C_us_time						0x001B
#define		C_us_date_time_s				0x001C
#define		C_us_OI							0x0050
#define		C_us_OAD						0x0051
#define		C_us_ROAD						0x0052
#define		C_us_OMD						0x0053
#define		C_us_TI							0x0054
#define		C_us_TSA						0x0055
#define		C_us_MAC						0x0056
#define		C_us_RN							0x0057
#define		C_us_Region						0x0058
#define		C_us_Scaler_Unit				0x0059
#define		C_us_RSD						0x005A
#define		C_us_CSD						0x005B
#define		C_us_MS							0x005C
#define		C_us_SID						0x005D
#define		C_us_SID_MAC					0x005E
#define		C_us_COMDCB						0x005F
#define		C_us_RCSD						0x0060
#define		C_us_Default					0x00FF	/*有参数，编码不确定*/


#define		C_null						0
#define		C_array						1
#define		C_structure					2
#define		C_bool						3
#define		C_bit_string				4
#define		C_double_long				5
#define		C_double_long_unsigned		6
#define		C_octet_string				9
#define		C_visible_string			10
#define		C_UTF8_string				12
#define		C_integer					15
#define		C_long						16
#define		C_unsigned					17
#define		C_long_unsigned				18
#define		C_long64					20
#define		C_long64_unsigned			21
#define		C_enum						22
#define		C_float32					23
#define		C_float64					24
#define		C_date_time					25
#define		C_date						26
#define		C_time						27
#define		C_date_time_s				28
#define		C_OI						80
#define		C_OAD						81
#define		C_ROAD						82
#define		C_OMD						83
#define		C_TI						84
#define		C_TSA						85
#define		C_MAC						86
#define		C_RN						87
#define		C_Region					88
#define		C_Scaler_Unit				89
#define		C_RSD						90
#define		C_CSD						91
#define		C_MS						92
#define		C_SID						93
#define		C_SID_MAC					94
#define		C_COMDCB					95
#define		C_RCSD						96

#define		C_Null_Ptr					0x0000
/***************简单数据类型长度，对于不定长数据定义为0**************/
#define		CL_null						1
#define		CL_array					0
#define		CL_structure				0
#define		CL_bool						1
#define		CL_bit_string				0
#define		CL_double_long				4
#define		CL_double_long_unsigned		4
#define		CL_octet_string				0
#define		CL_visible_string			0
#define		CL_UTF8_string				0
#define		CL_integer					1
#define		CL_long						2
#define		CL_unsigned					1
#define		CL_long_unsigned			2
#define		CL_long64					8
#define		CL_long64_unsigned			8
#define		CL_enum						1
#define		CL_float32					4
#define		CL_float64					8
#define		CL_date_time				10
#define		CL_date						5
#define		CL_time						3
#define		CL_date_time_s				7
#define		CL_OI						2
#define		CL_OAD						4
#define		CL_ROAD						0
#define		CL_OMD						4
#define		CL_TI						3
#define		CL_TSA						0
#define		CL_MAC						0
#define		CL_RN						0
#define		CL_Region					0
#define		CL_Scaler_Unit				2
#define		CL_RSD						0
#define		CL_CSD						5
#define		CL_MS						0
#define		CL_SID						0
#define		CL_SID_MAC					0
#define		CL_COMDCB					5
#define		CL_RCSD						0

#define		CL_CSD_1					0		/*用于特殊类型编码，code编码时特殊处理*/
#define		CL_COMDCB_1					0		/*用于特殊类型编码，code编码时特殊处理*/

typedef enum
{
	C_Code_Array_1 			= 0x0100,	/*数组类型1*/
//	C_Code_Array_2 			= 0x0500,	/*数组类型2*/
//	C_Code_Array_3 			= 0x0600,	/*数组类型3*/
//	C_Code_Array_4 			= 0x0700,	/*数组类型4*/
//	C_Code_Array_5			= 0x0800,	/*数组类型5*/
	C_Code_Structure_1 		= 0x0200,	/*结构体类型1*/
//	C_Code_Structure_2 		= 0x0F00,	/*结构体类型2*/
//	C_Code_Structure_3 		= 0x1000,	/*结构体类型3*/
//	C_Code_Structure_4 		= 0x1100,	/*结构体类型4*/
//	C_Code_Structure_5 		= 0x1200,	/*结构体类型5*/
	C_Code_Bitstring		= 0x0400,	/*bit-string类型*/	
	C_Code_Visiblestring	= 0x0A00,	/*Visible-string类型*/
	C_Code_Octetstring0		= 0x0900,	/*Octet-string类型SIZE（0-255）*/
	C_Code_Octetstring1		= 0x1D00,	/*Octet-string类型SIZE（256-511）*/
	C_Code_Octetstring2		= 0x1E00,	/*Octet-string类型SIZE（512-767）*/
	C_Code_Octetstring3		= 0x1F00,	/*Octet-string类型SIZE（768-1023）*/
	C_Code_Octetstring4		= 0x2000,	/*Octet-string类型SIZE（1024-1279）*/
	C_Code_Octetstring5		= 0x2100,	/*Octet-string类型SIZE（1280-1535）*/
	C_Code_Octetstring6		= 0x2200,	/*Octet-string类型SIZE（1536-1791）*/
	C_Code_Octetstring7		= 0x2300,	/*Octet-string类型SIZE（1792-2047）*/
	C_Code_Octetstring8		= 0x2400,	/*Octet-string类型SIZE（2048-2303）*/
	C_Code_Bitstring1		= 0x3000,	/*bit-string类型size   256*1 + (0-255)bit*/
	C_Code_Bitstring2		= 0x3100,	/*bit-string类型size   256*2 + (0-255)bit*/
	C_Code_Bitstring3		= 0x3200,	/*bit-string类型size   256*3 + (0-255)bit*/
	C_Code_Bitstring4		= 0x3300,	/*bit-string类型size   256*4 + (0-255)bit*/
	C_Code_Bitstring5		= 0x3400,	/*bit-string类型size   256*5 + (0-255)bit*/
	C_Code_Bitstring6		= 0x3500,	/*bit-string类型size   256*6 + (0-255)bit*/
	C_Code_Bitstring7		= 0x3600,	/*bit-string类型size   256*7 + (0-255)bit*/
	C_Code_Bitstring8		= 0x3700,	/*bit-string类型size   256*8 + (0-255)bit*/
	C_Code_Bitstring9		= 0x3800,	/*bit-string类型size   256*9 + (0-255)bit*/
	C_Code_BitstringA		= 0x3900,	/*bit-string类型size   256*10 + (0-255)bit*/
	C_Code_BitstringB		= 0x3A00,	/*bit-string类型size   256*11 + (0-255)bit*/
	C_Code_BitstringC		= 0x3B00,	/*bit-string类型size   256*12 + (0-255)bit*/
	C_Code_BitstringD		= 0x3C00,	/*bit-string类型size   256*13 + (0-255)bit*/
	C_Code_BitstringE		= 0x3D00,	/*bit-string类型size   256*14 + (0-255)bit*/
	C_Code_BitstringF		= 0x3E00,	/*bit-string类型size   256*15 + (0-255)bit*/		
	C_Code_AndNum			= 0x3F00,	/*运算宏 ushort16 & C_Code_AndNum */
	C_Code_Complex			= 0x8000,	/*复杂的编码*/
	C_Code_ChangeLen		= 0x4000,	/*长度变化的编码*/
}CodeTypePara;

/*----------------------------------------------编码枚举值---------------------------------------------------------------*/
/*Array_1表格枚举阵列,该枚举顺序需要与编码表格C_Str_Table_Code_Array_1顺序一致，否则编码出错*/
typedef enum
{
	C_CodeID_000002_1,
	C_CodeID_001002_1,
	C_CodeID_000004_1,
	C_CodeID_001004_1,   
	C_CodeID_021002_1,
	C_CodeID_021004_1,
#if(C_PhaseType == C_Phase_3)    
	C_CodeID_001102_1,
	C_CodeID_001104_1,
	C_CodeID_003102_1,
	C_CodeID_003104_1,
	C_CodeID_101002_2,
	C_CodeID_101102_2,
	C_CodeID_103002_2,
	C_CodeID_103102_2,
#endif
	C_CodeID_200002_1,
	C_CodeID_200102_1,
	C_CodeID_200402_1,
	C_CodeID_200404_1,
	C_CodeID_200A02_1,
    C_CodeID_201004_1,
	C_CodeID_201402_1,
	C_CodeID_202902_1,	
	C_CodeID_300002_1,	
	C_CodeID_332003_1,
	C_CodeID_30000A_2,
	C_CodeID_30000E_2,
	C_CodeID_3000_Custom_1,
	C_CodeID_300907_3,
#if(C_PhaseType == C_Phase_3)
	C_CodeID_302307_3,
    C_CodeID_30230A_3,
#endif
	C_CodeID_30090A_3,
	C_CodeID_3009_Custom_1,
	C_CodeID_400502_1,
	C_CodeID_401102_2,
	C_CodeID_401402_2,
	C_CodeID_401602_3,
	C_CodeID_401602_3_1,
	C_CodeID_401602_3_2,
	C_CodeID_401602_3_3,
	C_CodeID_401602_3_4,
	C_CodeID_401602_3_5,
	C_CodeID_401602_3_6,
	C_CodeID_401602_3_7,
	C_CodeID_401602_3_8,	
	C_CodeID_411602_2,

	C_CodeID_430005_1,
	C_CodeID_430006_1,
	C_CodeID_43000A_1,
	C_CodeID_F10103_2,

	C_CodeID_F20502_2,
	C_CodeID_F20702_1,
	C_CodeID_F20902_2,

    C_CodeID_F20B02_3,
    C_CodeID_F20B04_2,
    C_CodeID_F20B05_4,
    C_CodeID_F20B05_2_2,
    C_CodeID_F20B05_2_1,
    C_CodeID_F20B06_2,

    C_CodeID_F20D02_2,
    C_CodeID_F20E02_2,
    
	C_CodeID_F30002_2,
	C_CodeID_330202_1,
	C_CodeID_330C02_1,
	C_CodeID_500002_2,
	C_CodeID_800081_2,
	C_CodeID_800082_2,
	C_CodeID_800083_2,
#if(C_PhaseType == C_Phase_3)	
	C_CodeID_30000A_3,
	C_CodeID_30000E_3,
#endif	
	C_CodeID_FFOU1_1,
	C_CodeID_FFOU2_1,
	C_CodeID_FFEv4_2,
	C_CodeID_FFST05_2,
	
    C_CodeID_500205_2,
    
	C_CodeID_404102_1,
    C_CodeID_204302_1,
    C_CodeID_204402_1,
    C_CodeID_F30202_3,
    C_CodeID_F30202_1,

    
    C_CodeID_200D02_1,
    
	C_CodeID_480004_1,		//NILM模块配置参数
 
    C_CodeID_403102_2,		//逻辑地址列表
    
    C_CodeID_FF0607_1,	//模块逻辑地址列表
    C_CodeID_FF1707_1,
    C_CodeID_F10010_1,	//ESAM白名单
	E_Array_1_ErrNum,
}CodeID_Array_1Para;

/*Structure_1表格枚举阵列*/
typedef enum
{
 #if(C_PhaseType == C_Phase_3)
	C_CodeID_101002_1,
	C_CodeID_103002_1,
#endif
	C_CodeID_202C02_1,
	C_CodeID_213102_2,
	C_CodeID_213102_1,		
#if(C_PhaseType == C_Phase_3)	
	C_CodeID_300003_1,
#endif
	C_CodeID_300103_1,
#if(C_PhaseType == C_Phase_3)
	C_CodeID_300005_1,
	C_CodeID_30000D_1,
	C_CodeID_300105_1,
	C_CodeID_300906_1,
	C_CodeID_302307_2,
	C_CodeID_30230A_2,
	C_CodeID_300305_1,
	C_CodeID_300405_1,
#endif 
    C_CodeID_300E06_1,
    C_CodeID_30000A_1,
    C_CodeID_30000E_1,
    C_CodeID_300907_2,
    C_CodeID_30090A_2,
	C_CodeID_300505_1,
	C_CodeID_300C06_1,
	C_CodeID_400402_2,
	C_CodeID_400402_1,
	C_CodeID_400702_1,
	C_CodeID_400C02_1,
	C_CodeID_401102_1,
	C_CodeID_401402_1,	
  
	C_CodeID_401F02_1,
	C_CodeID_430003_1,
	C_CodeID_440003_1,
	C_CodeID_800002_1,
	C_CodeID_F10103_1,

	C_CodeID_F20502_1,
	C_CodeID_F20902_1,	
  
    C_CodeID_F20B02_2,	
    C_CodeID_F20B02_1,
    
    C_CodeID_F20B04_1,
    C_CodeID_F20B05_3,
    C_CodeID_F20B06_1,

    C_CodeID_F20D02_1,	
    C_CodeID_F20E02_1,	
    
	C_CodeID_F30002_1,
	C_CodeID_F30005_1,
	C_CodeID_F30004_1,
	C_CodeID_330202_2,
#if(C_PhaseType == C_Phase_3)
	C_CodeID_330802_1,
#endif
	C_CodeID_330C02_2,
	C_CodeID_331002_1,
	C_CodeID_331102_1,
	C_CodeID_331402_2,
	C_CodeID_331502_2,		

	C_CodeID_331202_1,
	
	C_CodeID_500002_1,
	C_CodeID_F0010A_1,
	C_CodeID_800081_1,
	C_CodeID_800082_1,
	C_CodeID_800083_1,

//    C_CodeID_404002_1,
    C_CodeID_404402_1,

    C_CodeID_303206_1,
    C_CodeID_301F06_1,
    C_CodeID_303506_1,
    
    C_CodeID_500205_1,
    C_CodeID_F30202_2,
    C_CodeID_F30203_1,


    C_CodeID_480004_2,		//NILM模块配置参数

	C_CodeID_403102_1,		//逻辑地址列表
	E_Structure_1_ErrNum,
}CodeID_Structure_1Para;

/*四、变量定义*/
typedef struct
{ 	    
    uchar8  CodeOf698Type;  			/*698编码值*/
    uchar8  DataLenOf698Type;			/*该编码对应数据长度*/
}CodeLenOf698Table_T;

typedef struct
{ 	
	CodeTypePara C_enumNum;
	uchar8 Code_698;
}CodeInside_To_698_T;	    //编码枚举映射结构体

typedef struct
{ 	
	const ushort16 *p_usBottomCode;  //下级内容
	ushort16 MaxDataLen;//最大数据长度 
	uchar8 DataType;//对应698协议的数据类型
    uchar8 MaxIndex;//最大元素个数 
}CodePara_T;	    //编码枚举映射结构体

typedef struct
{ 	
	const CodePara_T *pstr_CodeTable;
	ushort16 CodeID;
}CodeID_To_TablePara_T;	    //编码枚举映射结构体

//typedef struct
//{ 	    
//    ushort16 CodeIDBuff[500];				/*内部编码组*/
//    ushort16 CodeIDBuffLen;					/*CodeIDBuff[]数组长度*/
//    uchar8  SourceDatabuff[2048];  			/*待解码源数据*/
//    ushort16 SourceLen;						/*待解码源数据长度*/
//    uchar8  DerictDatabuff[2148];			/*解码后698格式数据*/
//    ushort16 DerictLen;						/*解码后698格式数据总长度*/
//}Code_Decode_Data_T;

typedef struct
{ 	    
    uchar8 LevelNum;					/*编码嵌套等级*/
    uchar8  CodeID_HighLevel[12];  		/*高嵌套级的698编码值*/
    uchar8 CodeID_Bottom_Num;			/*最底层数据分项个数*/
    ushort16 Len_Of_Bottom698Data[16];	/*最底层数据分项数据长度遍历*/
    ushort16 Len_Of_BottomCode[16];    	/*最底层数据分项698编码长度遍历*/   
    uchar8 Data_Of_BottomCode[64];		/*最底层数据分项698编码遍历*/   
}Code_Code698_Level_T;



/*变量声明*/



/*函数声明*/
extern uchar8 PF_Get_Code698_Data(uchar8 * p_CodeID,uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen);
extern ushort16 PF_CodeIDS_TO_DataLen(uchar8 V_ucCodeIDNum,uchar8 *p_ucDataIn);
extern uchar8 PF_CodeID_TO_DataLen(ushort16 v_usCodeID,ushort16 *p_usDataLen);
extern uchar8 PF_CodeID_TO_BottomCode(ushort16 v_usCodeID,ushort16 *p_usBottomCodebuff,ushort16 *p_usBottomCodebuffLen);
extern uchar8 PF_CodeID_TO_TableNum(ushort16 v_usCodeID,uchar8 *p_ucTableNum);
extern uchar8 PF_DataLen_TO_A_XDR(ushort16 v_usDataLen,uchar8 *DerictAddr);
extern uchar8 PF_CodeInside_To_698(ushort16 V_usCodeInside);
extern uchar8 PF_JudgeBottomData(ushort16 *p_usBottomDataBuff,ushort16 V_usIndexNum);
extern uchar8 PF_Get_Code698_Struct(ushort16 v_usCodeID,Code_Code698_Level_T *pstr_Code698_Level);
extern uchar8 PF_Get_Code698_Struct_Data(Code_Code698_Level_T *pStr_Code698_Level,uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen);
extern uchar8 PF_Get_Code698_Struct_BottomData(Code_Code698_Level_T *pstr_Code698_Level,uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen);
extern ushort16 PF_Get_Code698_Struct_Len(Code_Code698_Level_T vstr_Code698_Level,uchar8 v_ucCodeLevel);
extern uchar8 PF_Get_Code698_Len(uchar8 V_ucCode698);
extern void PF_Get_Code698_Struct_DropLevel(Code_Code698_Level_T *pstr_Code698_Level);
extern void PF_Get_Code698_ChangeLen(Code_Code698_Level_T *pstr_Code698_Level,ushort16 v_usDataLen);
extern uchar8 PF_Get_MaxIndex(ushort16 v_usCodeID);
extern uchar8 PF_CSD_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen);
extern uchar8 PF_CSDArray_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen);
extern uchar8 PF_Get_Code698_And_Data_Len(uchar8 V_ucCode698);
extern uchar8 PF_TI_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen);
extern void PF_Init_Code698_Level_T(Code_Code698_Level_T *pstr_Code698_Level);
extern uchar8  PF_RecordCValue_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen);
extern uchar8  PF_RecordTimeSta_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen);
extern uchar8  PF_RecordTimeStaBottom_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen);
extern uchar8  PF_RecordTimeStaid7_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen);
extern uchar8  PF_RecordCValueid7_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen);
extern uchar8 PF_Is_date_time_s_Null(uchar8 V_uc698CodeID,uchar8 *pDataIn);
extern uchar8  PF_C_CodeID_30230A_2_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen);
extern uchar8  PF_C_CodeID_302307_3_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen);
extern ushort16 PF_Get_Code698S_And_Data_Len(uchar8 *pV_ucDataBuf);
extern uchar8 PF_Get_698Encoded_DataAndLen(ushort16 *pV_usDataLen,uchar8 *pV_ucADPUBuf,uchar8 *pV_ucData,ushort16 *pV_usADPUDeal_Len);
extern ushort16 PF_Get_ComplexDataLen_Data(uchar8 *pV_ucADPUBuf,uchar8 *pV_ucData,ushort16 *pV_usADPUDeal_Len);
extern uchar8 PF_Decode_LenOffset(uchar8 *pV_Buffer,ushort16 *pV_usDataLen);
extern void PF_Save_ComplexDataLen_Data(uchar8 *pV_ucADPUBuf,uchar8 *pV_ucData,ushort16 *pV_usADPUDeal_Len,ushort16 *pV_usOff,ushort16 V_usDataLen);
extern uchar8  PF_C_CodeID_401102_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen);
extern uchar8  PF_F30005_1_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen);
extern uchar8  PF_C_CodeID_330202_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen);
extern uchar8  PF_C_CodeID_1010_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen);
extern uchar8  PF_C_CodeID_1030_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen);
extern uchar8 PF_C_CodeID_F30202_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen);
extern uchar8 PF_C_CodeID_F20B05_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen);





#endif
