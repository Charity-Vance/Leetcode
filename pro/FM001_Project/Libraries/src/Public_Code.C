//************************************************************************///
//*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
//*File name:     Public.C
//*Author:        
//*Version:       V1
//*Date:          2018-3-26
//*Description:   此文件是公共宏的声明
//*Function List: 
//*History:       修改日期、修改者、修改内容简述
//*1. Date:
//*   Author:
//*   Modification:
//*2. Date:
//*   Author:
//*   Modification:
//************************************************************************///
/*一、包含头文件*/
#include "Public.h"
#include "Public_Code.h"
/*二、宏定义*/

/*三、常量定义*/
const CodeLenOf698Table_T Str_CodeLenOf698Table[]=
{
	{C_null					,0},
	{C_bool					,1},
	{C_double_long			,4},
	{C_double_long_unsigned	,4},
	{C_integer				,1},
	{C_long					,2},
	{C_unsigned				,1},
	{C_long_unsigned		,2},	
	{C_long64				,8},
	{C_long64_unsigned		,8},
	{C_enum					,1},
	{C_float32				,4},
	{C_float64				,8},
	{C_date_time			,10},	
	{C_date					,5},
	{C_time					,3},
	{C_date_time_s			,7},
	{C_OI					,2},
	{C_OAD					,4},
	{C_OMD					,4},
	{C_TI					,3},
	{C_TSA					,17},
	{C_MAC					,4},
	{C_Scaler_Unit			,2},
//	{C_CSD					,10},
	{C_COMDCB				,5},
};

const CodeInside_To_698_T C_Str_CodeInside_To_698_Table[]=
{
	{C_Code_Array_1,		C_array},
//	{C_Code_Array_2,		C_array},
//	{C_Code_Array_3,		C_array},
//	{C_Code_Array_4,		C_array},
//	{C_Code_Array_5,		C_array},
	{C_Code_Structure_1,	C_structure},
//	{C_Code_Structure_2,	C_structure},
//	{C_Code_Structure_3,	C_structure},
//	{C_Code_Structure_4,	C_structure},
//	{C_Code_Structure_5,	C_structure},
	{C_Code_Bitstring,		C_bit_string},    
	{C_Code_Bitstring1,		C_bit_string}, 
	{C_Code_Bitstring2,		C_bit_string}, 
	{C_Code_Bitstring3,		C_bit_string}, 
	{C_Code_Bitstring4,		C_bit_string}, 
	{C_Code_Bitstring5,		C_bit_string}, 
	{C_Code_Bitstring6,		C_bit_string}, 
	{C_Code_Bitstring7,		C_bit_string}, 
	{C_Code_Bitstring8,		C_bit_string}, 
	{C_Code_Bitstring9,		C_bit_string}, 
	{C_Code_BitstringA,		C_bit_string}, 
	{C_Code_BitstringB,		C_bit_string}, 
	{C_Code_BitstringC,		C_bit_string}, 
	{C_Code_BitstringD,		C_bit_string}, 
	{C_Code_BitstringE,		C_bit_string}, 
	{C_Code_BitstringF,		C_bit_string}, 
	{C_Code_Visiblestring,	C_visible_string},
	{C_Code_Octetstring0 ,	C_octet_string},	
	{C_Code_Octetstring1 ,	C_octet_string},	
	{C_Code_Octetstring2 ,	C_octet_string},	
	{C_Code_Octetstring3 ,	C_octet_string},	
	{C_Code_Octetstring4 ,	C_octet_string},	
	{C_Code_Octetstring5 ,	C_octet_string},	
	{C_Code_Octetstring6 ,	C_octet_string},	
	{C_Code_Octetstring7 ,	C_octet_string},	
	{C_Code_Octetstring8 ,	C_octet_string},
}; 



/*----------------------------------------------底层索引对应编码---------------------------------------------------------------*/

/*---------------------------用于数组-------------------------------------------------*/
const ushort16 C_Array_ulong32[1]={C_us_double_long_unsigned};
const ushort16 C_Array_long32[1]={C_us_double_long};
const ushort16 C_Array_ulong64[1]={C_us_long64_unsigned};
const ushort16 C_Array_long64[1]={C_us_long64};
const ushort16 C_Array_ushort16[1]={C_us_long_unsigned};
const ushort16 C_Array_short16[1]={C_us_long};
const ushort16 C_Array_OAD[1]={C_us_OAD}; 
const ushort16 C_Array_OMD[1]={C_us_OMD}; 
const ushort16 C_Array_OI[1]={C_us_OI}; 
const ushort16 C_Array_enum[1]={C_us_enum}; 
const ushort16 C_Array_Vstring16[1]={C_Code_Complex|C_Code_Visiblestring|16}; 
const ushort16 C_Array_Security_Mode[1]={C_Code_Complex|C_Code_Structure_1|C_CodeID_F10103_1}; 
const ushort16 C_Array_Octetstring256[1]={C_Code_Complex|C_Code_Octetstring1|0};  
const ushort16 C_Array_Octetstring6[1]={C_Code_Complex|C_Code_Octetstring0|6}; 

const ushort16 C_Array_Bitstring_16[1]={C_Code_Complex|C_Code_Bitstring|0x10};
const ushort16 C_Array_Bitstring_71[1]={C_Code_Complex|C_Code_Bitstring|0x47};
const ushort16 C_Array_30000A_2[1]={C_Code_Complex|C_Code_Structure_1|C_CodeID_30000A_1};
const ushort16 C_Array_30000E_2[1]={C_Code_Complex|C_Code_Structure_1|C_CodeID_30000E_1};
const ushort16 C_Array_300907_3[1]={C_Code_Complex|C_Code_Structure_1|C_CodeID_300907_2};
const ushort16 C_Array_30090A_3[1]={C_Code_Complex|C_Code_Structure_1|C_CodeID_30090A_2};

#if(C_PhaseType == C_Phase_3)
const ushort16 C_Array_302307_3[1]={C_Code_Complex|C_Code_Structure_1|C_CodeID_302307_2};
const ushort16 C_Array_30230A_3[1]={C_Code_Complex|C_Code_Structure_1|C_CodeID_30230A_2};
#endif
const ushort16 C_Array_401602_3[1]={C_Code_Complex|C_Code_Array_1|C_CodeID_401402_2};
const ushort16 C_Array_401102_2[1]={C_Code_Complex|C_Code_Structure_1|C_CodeID_401102_1};
const ushort16 C_Array_401402_2[1]={C_Code_Complex|C_Code_Structure_1|C_CodeID_401402_1};
const ushort16 C_Array_401A02_2_1[1]={C_Code_Complex|C_Code_Structure_1|C_CodeID_401402_1};
const ushort16 C_Array_F30002_2[1]={C_Code_Complex|C_Code_Structure_1|C_CodeID_F30002_1};

const ushort16 C_Array_F20502_2[1]={C_Code_Complex|C_Code_Structure_1|C_CodeID_F20502_1};
const ushort16 C_Array_F20902_2[1]={C_Code_Complex|C_Code_Structure_1|C_CodeID_F20902_1};
const ushort16 C_Array_F20B02_3[1]={C_Code_Complex|C_Code_Structure_1|C_CodeID_F20B02_2};
const ushort16 C_Array_F20B04_2[1]={C_Code_Complex|C_Code_Structure_1|C_CodeID_F20B04_1};
const ushort16 C_Array_F20B05_4[1]={C_Code_Complex|C_Code_Structure_1|C_CodeID_F20B05_3};
const ushort16 C_Array_F20B05_2[1]={C_Code_Complex|C_Code_Structure_1|C_CodeID_F20B02_1};
const ushort16 C_Array_F20B06_2[1]={C_Code_Complex|C_Code_Structure_1|C_CodeID_F20B06_1};

const ushort16 C_Array_F20D02_2[1]={C_Code_Complex|C_Code_Structure_1|C_CodeID_F20D02_1};
const ushort16 C_Array_F20E02_2[1]={C_Code_Complex|C_Code_Structure_1|C_CodeID_F20E02_1};

const ushort16 C_Array_411602_2[1]={C_Code_Complex|C_Code_Structure_1|C_CodeID_F30004_1};
#if(C_PhaseType == C_Phase_3)
const ushort16 C_Array_101002_2[1]={C_Code_Complex|C_Code_Structure_1|C_CodeID_101002_1};
const ushort16 C_Array_103002_2[1]={C_Code_Complex|C_Code_Structure_1|C_CodeID_103002_1};
#endif
const ushort16 C_Array_500002_2[1]={C_Code_Complex|C_Code_Structure_1|C_CodeID_500002_1};
const ushort16 C_Array_800081_2[1]={C_Code_Complex|C_Code_Structure_1|C_CodeID_800081_1};
const ushort16 C_Array_800082_2[1]={C_Code_Complex|C_Code_Structure_1|C_CodeID_800082_1};
const ushort16 C_Array_800083_2[1]={C_Code_Complex|C_Code_Structure_1|C_CodeID_800083_1};
const ushort16 C_Array_FFEv4_2[1]={C_Code_Complex|C_Code_Array_1|C_CodeID_202902_1};
const ushort16 C_Array_500205_2[1]={C_Code_Complex|C_Code_Structure_1|C_CodeID_500205_1};

const ushort16 C_Array_F30202_2[1]={C_Code_Complex|C_Code_Structure_1|C_CodeID_F30202_2};

const ushort16 C_Array_403102_2[1]={C_Code_Complex|C_Code_Structure_1|C_CodeID_403102_1};

const ushort16 C_Array_uchar8[1]={C_us_unsigned};

const ushort16 C_Array_Octetstring8[1]={C_Code_Complex|C_Code_Octetstring0|8}; 
/*----------------------------用于结构体-----------------------------------------------------------*/


const ushort16 C_Struct_203102_2[2]={C_Code_Complex|C_Code_Structure_1|C_CodeID_213102_1,C_Code_Complex|C_Code_Structure_1|C_CodeID_213102_1};

const ushort16 C_Struct_300907_2[2]={C_us_null,C_Code_Complex|C_Code_Structure_1|C_CodeID_30000A_1};
const ushort16 C_Struct_30090A_2[2]={C_us_null,C_Code_Complex|C_Code_Structure_1|C_CodeID_30000E_1};
const ushort16 C_Struct_30000E_1[2]={C_us_date_time_s,C_us_date_time_s};
const ushort16 C_Struct_300E06_1[1]={C_us_unsigned};
#if(C_PhaseType == C_Phase_3)
const ushort16 C_Struct_302307_2[2]={C_us_enum,C_Code_Complex|C_Code_Structure_1|C_CodeID_30000A_1};
const ushort16 C_Struct_30230A_2[2]={C_us_enum,C_Code_Complex|C_Code_Structure_1|C_CodeID_30000E_1};
const ushort16 C_Struct_300906_1[2]={C_us_double_long_unsigned,C_us_unsigned};
const ushort16 C_Struct_300105_1[2]={C_us_long_unsigned,C_us_unsigned};
const ushort16 C_Struct_101002_1[2]={C_us_double_long_unsigned,C_us_date_time_s};
const ushort16 C_Struct_103002_1[2]={C_us_double_long,C_us_date_time_s};
const ushort16 C_Struct_300305_1[3]={C_us_long_unsigned,C_us_double_long,C_us_unsigned};

const ushort16 C_Struct_300003_1[4]={C_us_long_unsigned,C_us_long_unsigned,C_us_long_unsigned,C_us_long_unsigned};

const ushort16 C_Struct_300005_1[4]={C_us_long_unsigned,C_us_long_unsigned,C_us_double_long,C_us_unsigned};
const ushort16 C_Struct_30000D_1[4]={C_us_double_long_unsigned,C_us_double_long_unsigned,C_us_date_time_s,C_us_date_time_s};
const ushort16 C_Struct_300405_1[4]={C_us_long_unsigned,C_us_double_long,C_us_double_long,C_us_unsigned};
#endif
const ushort16 C_Struct_F30002_1[2]={C_us_CSD,C_us_unsigned};
const ushort16 C_Struct_401102_1[2]={C_us_date,C_us_unsigned};
const ushort16 C_Struct_202C02_1[2]={C_us_double_long_unsigned,C_us_double_long_unsigned};
//const ushort16 C_Struct_401E02_1[2]={C_us_double_long_unsigned,C_us_double_long_unsigned};

const ushort16 C_Struct_800002_1[2]={C_us_double_long_unsigned,C_us_long_unsigned};

const ushort16 C_Struct_300505_1[2]={C_us_double_long,C_us_unsigned};
const ushort16 C_Struct_300C06_1[2]={C_us_long,C_us_unsigned};

const ushort16 C_Struct_F30004_1[2]={C_us_unsigned,C_us_unsigned};
const ushort16 C_Struct_F10103_1[2]={C_us_OI,C_us_long_unsigned};
const ushort16 C_Struct_800082_1[2]={C_us_OAD,C_us_enum};

const ushort16 C_Struct_401F02_1[3]={C_us_double_long_unsigned,C_us_double_long_unsigned,C_us_double_long_unsigned};
const ushort16 C_Struct_401402_1[3]={C_us_unsigned,C_us_unsigned,C_us_unsigned};

const ushort16 C_Struct_400402_2[3]={C_Code_Complex|C_Code_Structure_1|C_CodeID_400402_1,C_Code_Complex|C_Code_Structure_1|C_CodeID_400402_1,C_us_double_long_unsigned};
const ushort16 C_Struct_F20902_1[3]={C_Code_Complex|C_Code_Visiblestring|8,C_us_COMDCB,C_us_null};
const ushort16 C_Struct_F20B02_2[4]={C_us_unsigned,C_Code_Complex|C_Code_Structure_1|C_CodeID_F20B02_1,C_Code_Complex|C_Code_Visiblestring|6,C_us_enum};
const ushort16 C_Struct_F20B02_1[2]={C_Code_Complex|C_Code_Visiblestring|16,C_Code_Complex|C_Code_Octetstring0|6};
const ushort16 C_Struct_F20B04_1[2]={C_Code_Complex|C_Code_Octetstring0|6,C_Code_Complex|C_Code_Octetstring0|32};
const ushort16 C_Struct_F20B05_3[3]={C_us_OAD,C_Code_Complex|C_Code_Array_1|C_CodeID_F20B05_2_2,C_Code_Complex|C_Code_Array_1|C_CodeID_F20B05_2_1};
const ushort16 C_Struct_F20B06_1[4]={C_us_OAD,C_us_enum,C_us_long_unsigned,C_us_long_unsigned};

const ushort16 C_Struct_F20D02_1[2]={C_Code_Complex|C_Code_Visiblestring|4,C_us_COMDCB};
const ushort16 C_Struct_F20E02_1[2]={C_Code_Complex|C_Code_Visiblestring|4,C_us_COMDCB};

const ushort16 C_Struct_500002_1[3]={C_us_long_unsigned,C_us_OAD,C_us_long_unsigned};
const ushort16 C_Struct_F30005_1[3]={C_us_CSD,C_us_unsigned,C_us_long_unsigned};
const ushort16 C_Struct_800083_1[3]={C_us_OAD,C_us_enum,C_Code_Complex|C_Code_Visiblestring|8};

#if(C_PhaseType == C_Phase_3)	/*分相事件当前记录数，单相表只有A相*/
const ushort16 C_Struct_300103_1[4]={C_us_null,C_us_long_unsigned,C_us_long_unsigned,C_us_long_unsigned};
#else
const ushort16 C_Struct_300103_1[4]={C_us_null,C_us_long_unsigned,C_us_null,C_us_null};
#endif

const ushort16 C_Struct_400402_1[4]={C_us_enum,C_us_unsigned,C_us_unsigned,C_us_unsigned};
const ushort16 C_Struct_F20502_1[4]={C_Code_Complex|C_Code_Visiblestring|1,C_us_enum,C_us_enum,C_us_enum};
const ushort16 C_Struct_800081_1[4]={C_us_OAD,C_us_unsigned,C_us_long_unsigned,C_us_bool};

const ushort16 C_Struct_203102_1[5]={C_us_double_long_unsigned,C_us_long_unsigned,C_us_long_unsigned,C_us_double_long_unsigned,C_us_double_long_unsigned};
const ushort16 C_Struct_400C02_1[5]={C_us_unsigned,C_us_unsigned,C_us_unsigned,C_us_unsigned,C_us_unsigned};
const ushort16 C_Struct_F0010A_1[5]={C_us_unsigned,C_us_unsigned,C_us_double_long_unsigned,C_us_double_long_unsigned,C_us_long_unsigned};


const ushort16 C_Struct_430003_1[6]={C_Code_Complex|C_Code_Visiblestring|4,C_Code_Complex|C_Code_Visiblestring|4,C_Code_Complex|C_Code_Visiblestring|6,C_Code_Complex|C_Code_Visiblestring|4,C_Code_Complex|C_Code_Visiblestring|6,C_Code_Complex|C_Code_Visiblestring|8};


const ushort16 C_Struct_400702_1[7]={C_us_unsigned,C_us_long_unsigned,C_us_long_unsigned,C_us_long_unsigned,C_us_unsigned,C_us_unsigned,C_us_unsigned};

const ushort16 C_Struct_440003_1[7]={C_us_long_unsigned,C_us_long_unsigned,C_us_long_unsigned,C_us_long_unsigned,C_Code_Complex|C_Code_Bitstring|64,C_Code_Complex|C_Code_Bitstring|128,C_us_double_long_unsigned};

const ushort16 C_Struct_404002_1[3]={C_Code_Complex|C_Code_Octetstring0|6,C_Code_Complex|C_Code_Visiblestring|16,C_Code_Complex|C_Code_Visiblestring|6};
const ushort16 C_Struct_404402_1[2]={C_Code_Complex|C_Code_Octetstring0|3,C_Code_Complex|C_Code_Octetstring0|3};

const ushort16 C_Struct_303206_1[3]={C_us_long,C_us_long,C_us_unsigned};
const ushort16 C_Struct_301F06_1[4]={C_Code_Complex|C_Code_Bitstring|0x10,C_us_long,C_us_long,C_us_unsigned};//跳闸
//const ushort16 C_Struct_303306_1[3]={C_us_long,C_us_long,C_us_unsigned};
const ushort16 C_Struct_303506_1[3]={C_us_long_unsigned,C_us_double_long_unsigned,C_us_unsigned};


/*记录单元内部编码架构*/
//const ushort16 C_Struct_330102_1[5]={C_us_double_long_unsigned,C_us_date_time_s,C_us_date_time_s,C_us_enum,C_us_null};
const ushort16 C_Struct_330202_2[6]={C_us_double_long_unsigned,C_us_date_time_s,C_us_date_time_s,C_us_enum,C_us_null,C_Code_Complex|C_Code_Array_1|C_CodeID_330202_1};
#if(C_PhaseType == C_Phase_3)
const ushort16 C_Struct_330802_1[7]={C_us_double_long_unsigned,C_us_date_time_s,C_us_date_time_s,C_us_enum,C_us_null,C_us_double_long_unsigned,C_us_date_time_s};
#endif
const ushort16 C_Struct_330C02_2[6]={C_us_double_long_unsigned,C_us_date_time_s,C_us_date_time_s,C_us_enum,C_us_null,C_Code_Complex|C_Code_Array_1|C_CodeID_330C02_1};
const ushort16 C_Struct_331002_1[9]={C_us_double_long_unsigned,C_us_date_time_s,C_us_date_time_s,C_us_enum,C_us_null,C_Code_Complex|C_Code_Octetstring0|8,C_us_unsigned,C_Code_Complex|C_Code_Octetstring0|5,C_us_long_unsigned};
const ushort16 C_Struct_331102_1[6]={C_us_double_long_unsigned,C_us_date_time_s,C_us_date_time_s,C_us_enum,C_us_null,C_us_double_long_unsigned};
const ushort16 C_Struct_331402_2[7]={C_us_double_long_unsigned,C_us_date_time_s,C_us_date_time_s,C_us_enum,C_us_null,C_us_OAD,C_Code_Complex|C_Code_Array_1|C_CodeID_401402_2};
const ushort16 C_Struct_331502_2[7]={C_us_double_long_unsigned,C_us_date_time_s,C_us_date_time_s,C_us_enum,C_us_null,C_us_OAD,C_Code_Complex|C_Code_Structure_1|C_CodeID_401102_1};

const ushort16 C_Struct_331202_1[10]={C_us_double_long_unsigned,C_us_date_time_s,C_us_date_time_s,C_OAD,C_us_null,C_Code_Complex|C_Code_Octetstring0|0,C_Code_Complex|C_Code_Visiblestring|32,C_Code_Complex|C_Code_Visiblestring|32,C_us_unsigned,C_us_unsigned};

//const ushort16 C_Struct_260003_2[3]={C_Code_Complex|C_Code_Visiblestring|32,C_Code_Complex|C_Code_Structure_1|C_CodeID_260003_1,C_Code_Complex|C_Code_Octetstring0|10};
//const ushort16 C_Struct_260003_1[5]={C_Code_Complex|C_Code_Visiblestring|4,C_Code_Complex|C_Code_Visiblestring|32,C_Code_Complex|C_Code_Visiblestring|6,C_Code_Complex|C_Code_Visiblestring|32,C_Code_Complex|C_Code_Visiblestring|6};

const ushort16 C_Struct_500205_1[3]={C_us_long_unsigned,C_us_OAD,C_us_double_long_unsigned};

const ushort16 C_Struct_F30202_2[6]={C_us_long_unsigned,C_us_long_unsigned,C_us_long_unsigned,C_us_long_unsigned,C_Code_Complex|C_Code_Array_1|C_CodeID_F30202_1,C_us_enum};
const ushort16 C_Struct_F30203_1[3]={C_us_enum,C_us_enum,C_us_unsigned};

const ushort16 C_Struct_480004_2[8]={C_us_long,C_us_unsigned,C_us_unsigned,C_Code_Complex|C_Code_Array_1|C_CodeID_480004_1,C_Code_Complex|C_Code_Array_1|C_CodeID_480004_1,C_Code_Complex|C_Code_Array_1|C_CodeID_480004_1,C_us_double_long};

const ushort16 C_Struct_403102_1[4]={C_Code_Complex|C_Code_Visiblestring|CLFactory_Softw_Version_4031,C_us_unsigned,C_Code_Complex|C_Code_Bitstring|16,C_Code_Complex|C_Code_Octetstring0|16};

/*----------------------------------------------复杂类型编码对应结构表格---------------------------------------------------------------*/											
const CodePara_T C_Str_Table_Code_Array_1[]=
{
/*-------下级数据table指针------数据最大长度----------------------------对应698编码--------索引个数-----------------*/
#if(C_RateFun_Enable == 1)
	{&C_Array_long32[0],			4*5,								C_array,			5},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_000002_1  */
	{&C_Array_ulong32[0],			4*5,								C_array,			5},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_001002_1  */		
	{&C_Array_long64[0],			8*5,								C_array,			5},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_000004_1  */
	{&C_Array_ulong64[0],			8*5,								C_array,			5},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_001004_1  */
#else
	{&C_Array_long32[0],			4*1,								C_array,			1},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_000002_1  */
	{&C_Array_ulong32[0],			4*1,								C_array,			1},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_001002_1  */		
	{&C_Array_long64[0],			8*1,								C_array,			1},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_000004_1  */
	{&C_Array_ulong64[0],			8*1,								C_array,			1},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_001004_1  */
#endif
	{&C_Array_ulong32[0],			4*1,								C_array,			1},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_021002_1  */	
	{&C_Array_ulong64[0],			8*1,								C_array,			1},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_022004_1  */	

	#if(C_PhaseType == C_Phase_3)
	{&C_Array_ulong32[0],			4*1,								C_array,			1},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_001102_1  */	
	{&C_Array_ulong64[0],			8*1,								C_array,			1},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_001104_1  */	
	
	{&C_Array_long32[0],			4*1,								C_array,			1},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_003102_1  */	
	{&C_Array_long64[0],			8*1,								C_array,			1},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_003104_1  */	
#if(C_RateFun_Enable == 1)	
	{&C_Array_101002_2[0],			5*11,								C_array,			5},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_101002_2  */
#else
	{&C_Array_101002_2[0],			1*11,								C_array,			1},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_101002_2  */
#endif
	{&C_Array_101002_2[0],			1*11,								C_array,			1},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_101102_2  */

#if(C_RateFun_Enable == 1)		
	{&C_Array_103002_2[0],			5*11,								C_array,			5},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_103002_2  */
#else
	{&C_Array_103002_2[0],			1*11,								C_array,			1},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_103002_2  */
#endif
	{&C_Array_103002_2[0],			1*11,								C_array,			1},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_103102_2  */
	/*三相表是总、A、B、C，单相是总、A*/	
	{&C_Array_ushort16[0],			2*3,								C_array,			3},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_200002_1  */   
	{&C_Array_long32[0],			4*3,								C_array,			3},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_200102_1  */     
	{&C_Array_long32[0],			4*4,								C_array,			4},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_200402_1  */
	#else
	{&C_Array_ushort16[0],			2*1,								C_array,			1},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_200002_1  */   
	{&C_Array_long32[0],			4*1,								C_array,			1},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_200102_1  */     	
	{&C_Array_long32[0],			4*2,								C_array,			2},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_200402_1  */
	#endif
	{&C_Array_long64[0],			8*4,								C_array,			4},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_200404_1  */
	#if(C_PhaseType == C_Phase_3)	/*三相表是总、A、B、C，单相是总、A*/
	{&C_Array_short16[0],			2*4,								C_array,			4},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_200A02_1  */
	#else
	{&C_Array_short16[0],			2*2,								C_array,			2},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_200A02_1  */	
	#endif
	{&C_Array_short16[0],		    2*4,								C_array,			4},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_201004_1  */

	{&C_Array_Bitstring_16[0],		2*7,								C_array,			7},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_201402_1  */
	{&C_Array_ulong32[0],			4*4,								C_array,			4},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_202902_1  */	
	{&C_Array_OAD[0],				4*60,								C_array,			60},	/*C_Code_Complex|C_Code_Array_1|C_CodeID_300002_1*/
	{&C_Array_OI[0],				2*60,								C_array,			60},	/*C_Code_Complex|C_Code_Array_1|C_CodeID_332003_1*/		
	
    {&C_Array_30000A_2[0],			8*4,			    				C_array,			4},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_30000A_2*/	
	{&C_Array_30000E_2[0],			14*4,								C_array,			4},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_30000E_2*/
	{&C_Array_ulong32[0],			4*9,								C_array,			9},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_3000_Custom_1*/
	{&C_Array_300907_3[0],			8,									C_array,			1},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_300907_3*/
#if(C_PhaseType == C_Phase_3)	
    {&C_Array_302307_3[0],			9*2,								C_array,			2},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_302307_3*/
	{&C_Array_30230A_3[0],			15*2,								C_array,			2},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_30230A_3*/
#endif	
    {&C_Array_30090A_3[0],			14,									C_array,			1},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_30090A_3*/
	{&C_Array_ulong32[0],			4*3,								C_array,			3},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_3009_Custom_1*/	
    
	{C_Array_Octetstring6,			6*1,								C_array,			1},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_400502_1*/
	{&C_Array_401102_2[0],			6*254,								C_array,			254},	/*C_Code_Complex|C_Code_Array_1|C_CodeID_401102_2*/
	{&C_Array_401402_2[0],			3*14,								C_array,			14},	/*C_Code_Complex|C_Code_Array_1|C_CodeID_401402_2*/
	{&C_Array_401602_3[0],			42*8,								C_array,			8},		/*C_Code_Complex|C_Code_Array_2|C_CodeID_401602_3*/
	{&C_Array_401602_3[0],			42*1,								C_array,			1},		/*不定长编码：0xC000|C_Code_Array_1|C_CodeID_401602_3_1*/
	{&C_Array_401602_3[0],			42*2,								C_array,			2},		/*不定长编码：0xC000|C_Code_Array_1|C_CodeID_401602_3_2*/
	{&C_Array_401602_3[0],			42*3,								C_array,			3},		/*不定长编码：0xC000|C_Code_Array_1|C_CodeID_401602_3_3*/
	{&C_Array_401602_3[0],			42*4,								C_array,			4},		/*不定长编码：0xC000|C_Code_Array_1|C_CodeID_401602_3_4*/
	{&C_Array_401602_3[0],			42*5,								C_array,			5},		/*不定长编码：0xC000|C_Code_Array_1|C_CodeID_401602_3_5*/
	{&C_Array_401602_3[0],			42*6,								C_array,			6},		/*不定长编码：0xC000|C_Code_Array_1|C_CodeID_401602_3_6*/
	{&C_Array_401602_3[0],			42*7,								C_array,			7},		/*不定长编码：0xC000|C_Code_Array_1|C_CodeID_401602_3_7*/
	{&C_Array_401602_3[0],			42*8,								C_array,			8},		/*不定长编码：0xC000|C_Code_Array_1|C_CodeID_401602_3_8*/
	{&C_Array_411602_2[0],			3*2,								C_array,			3},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_411602_2*/

	{&C_Array_OI[0],				2*8,								C_array,			8},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_430005_1*/
	{&C_Array_Vstring16[0],			16*3,								C_array,			3},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_430006_1*/
	{&C_Array_OAD[0],				4*6,								C_array,			6},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_43000A_1*/
	{&C_Array_Security_Mode[0],		4*32,								C_array,			32},	/*C_Code_Complex|C_Code_Array_1|C_CodeID_F10103_2*/

	{&C_Array_F20502_2[0],			4,									C_array,			1},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_F20502_2*/
	{&C_Array_enum[0],				1,									C_array,			1},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_F20702_1*/
	{&C_Array_F20902_2[0],			13,									C_array,			1},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_F20902_2*/

    {&C_Array_F20B02_3[0],			30,									C_array,			1},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_F20B02_3*/
    {&C_Array_F20B04_2[0],			114,								C_array,			3},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_F20B04_2*/
    {&C_Array_F20B05_4[0],			114,								C_array,			1},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_F20B05_4*/
    {&C_Array_F20B05_2[0],		    44,								    C_array,			2},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_F20B05_2_2*/
    {&C_Array_F20B05_2[0],		    66,								    C_array,			3},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_F20B05_2_1*/ 
    {&C_Array_F20B06_2[0],		    9,								    C_array,			1},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_F20B06_2*/
 
    {&C_Array_F20D02_2[0],			9,									C_array,			1},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_F20D02_2*/
    {&C_Array_F20E02_2[0],			9,									C_array,			1},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_F20E02_2*/

	{&C_Array_F30002_2[0],			(8+1)*99,							C_array,			99},	/*C_Code_Complex|C_Code_Array_1|C_CodeID_F30002_2*/	
	{&C_Array_OAD[0],				4*10,								C_array,			10},	/*C_Code_Complex|C_Code_Array_1|C_CodeID_330202_1*/
	{&C_Array_OMD[0],				4*1,								C_array,			1},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_330C02_1*/
	{&C_Array_500002_2[0],			8*C_FreezeMAXRelatedOAD,			C_array,			C_FreezeMAXRelatedOAD},	/*C_Code_Complex|C_Code_Array_1|C_CodeID_500002_2*/
	{&C_Array_800081_2[0],			8*1,								C_array,			1},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_800081_2*/	
	{&C_Array_800082_2[0],			5*1,								C_array,			1},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_800082_2*/	
	{&C_Array_800083_2[0],			13*1,								C_array,			1},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_800083_2*/	
#if(C_PhaseType == C_Phase_3)	
	{&C_Array_30000A_2[0],			8*4,			    				C_array,			4},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_30000A_2*/	
	{&C_Array_30000E_2[0],			14*4,								C_array,			4},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_30000E_2*/
#endif	
	
	{&C_Array_Octetstring256[0],	256*128,							C_array,			128},	/*C_Code_Complex|C_Code_Array_1|C_CodeID_FFOU1_1*/   
	{&C_Array_Octetstring256[0],	256*16,								C_array,			16},	/*C_Code_Complex|C_Code_Array_1|C_CodeID_FFOU2_1*/
	{&C_Array_FFEv4_2[0],			16*12,								C_array,			12},	/*C_Code_Complex|C_Code_Array_1|C_CodeID_FFEv4_2*/
	{&C_Array_OAD[0],				4*60,								C_array,			60},	/*C_Code_Complex|C_Code_Array_1|C_CodeID_FFST05_2 该内部编码支持按索引读 */

	{&C_Array_500205_2[0],			8*96,								C_array,			96},	/*C_Code_Complex|C_Code_Array_1|C_CodeID_500002_2*/
	
	{&C_Array_Octetstring6[0],		6*3,			                    C_array,			3},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_404102_1 */

 #if(C_PhaseType == C_Phase_3)
 	{&C_Array_short16[0],			2*7,								C_array,			7},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_204302_1  */	
 #else
	{&C_Array_short16[0],			2*4,								C_array,			4},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_204302_1  */	
#endif

 #if(C_PhaseType == C_Phase_3)
    {&C_Array_short16[0],			2*4,								C_array,			4},
#else
    {&C_Array_short16[0],			2*2,								C_array,			2},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_204402_1  */	
#endif
	{&C_Array_F30202_2[0],			9+639,								C_array,			1},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_F30202_3  */	
	
    
    {&C_Array_Bitstring_71[0],		9*71,								C_array,			71},	/*C_Code_Complex|C_Code_Array_1|C_CodeID_F30202_1  */	
	
    {&C_Array_short16[0],			2*21,								C_array,			21},	/*C_Code_Complex|C_Code_Array_1|C_CodeID_200D02_1  */

#if(C_PhaseType == C_Phase_3)	
	{&C_Array_ulong32[0],			4*3,								C_array,			3}, 	/*C_Code_Complex|C_Code_Array_1|C_CodeID_480004_1  */	
#else
	{&C_Array_ulong32[0],			4*1,								C_array,			1}, 	/*C_Code_Complex|C_Code_Array_1|C_CodeID_480004_1  */	
#endif
    {&C_Array_403102_2[0],			CLFactory_Softw_Version_4031*10,	C_array,			10},	/*C_Code_Complex|C_Code_Array_1|C_CodeID_403102_2  */

	{&C_Array_uchar8[0],			4*1,								C_array,			4},	/*C_Code_Complex|C_Code_Array_1|C_CodeID_FF0607_1 该内部编码支持按索引读 */
    {&C_Array_uchar8[0],			255*1,								C_array,			255},	/*C_Code_Complex|C_Code_Array_1|C_CodeID_FF1707_1 */
	{&C_Array_Octetstring8[0],		8*16,								C_array,			16},		/*C_Code_Complex|C_Code_Array_1|C_CodeID_F10010_1*/

};

//const CodePara_T C_Str_Table_Code_Array_2[]=
//{
///*-------下级数据table指针------数据最大长度-------对应698编码--------索引个数-----------------*/	
//
//	{&C_Array_F30002_2[0],		(8+1)*99,			C_array,			99},						/*C_Code_Complex|C_Code_Array_2|C_CodeID_F30002_2*/	
//};

//const CodePara_T C_Str_Table_Code_Array_3[]=
//{
///*-------下级数据table指针------数据最大长度-------对应698编码--------索引个数-----------------*/
//	{0x00000000,		6*255,			C_array,			255},							/*C_Code_Complex|C_Code_Array_3|C_CodeID_401102_2*/
//};
const CodePara_T C_Str_Table_Code_Structure_1[]=
{
/*-------下级数据table指针------数据最大长度-------对应698编码--------索引个数-----------------*/
    #if(C_PhaseType == C_Phase_3)
	{&C_Struct_101002_1[0],		11,				C_structure,			2},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_101002_1*/	
	{&C_Struct_103002_1[0],		11,				C_structure,			2},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_103002_1*/	
    #endif
	{&C_Struct_202C02_1[0],		8,				C_structure,			2},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_202C02_1*/	
    {&C_Struct_203102_2[0],		32,				C_structure,			2},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_213102_2*/	
	{&C_Struct_203102_1[0],		16,				C_structure,			5},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_213102_1*/	
    #if(C_PhaseType == C_Phase_3)
	{&C_Struct_300003_1[0],		8,				C_structure,			4},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_300003_1*/	
	/*分相事件当前记录数，单相表只有A相*/
	{&C_Struct_300103_1[0],		6,				C_structure,			4},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_300103_1*/	
	#else
	{&C_Struct_300103_1[0],		2,				C_structure,			4},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_300103_1*/	
	#endif
#if(C_PhaseType == C_Phase_3)
	{&C_Struct_300005_1[0],		9,				C_structure,			4},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_300005_1*/	
	{&C_Struct_30000D_1[0],		22,				C_structure,			4},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_30000D_1*/	
	{&C_Struct_300105_1[0],		3,				C_structure,			2},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_300105_1*/	
	{&C_Struct_300906_1[0],		5,				C_structure,			2},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_300906_1*/	
	{&C_Struct_302307_2[0],		9,				C_structure,			2},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_302307_2*/
	{&C_Struct_30230A_2[0],		15,				C_structure,			2},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_30230A_2*/
	{&C_Struct_300305_1[0],		7,				C_structure,			3},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_300305_1*/
	{&C_Struct_300405_1[0],		11,				C_structure,			4},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_300405_1*/
#endif    
    {&C_Struct_300E06_1[0],		1,				C_structure,			1},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_300E06_1*/	
    {&C_Struct_202C02_1[0],		8,				C_structure,			2},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_30000A_1*/
    {&C_Struct_30000E_1[0],		14,				C_structure,			2},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_30000E_1*/
    {&C_Struct_300907_2[0],		8,				C_structure,			2},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_300907_2*/
    {&C_Struct_30090A_2[0],		14,				C_structure,			2},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_30090A_2*/
	{&C_Struct_300505_1[0],		5,				C_structure,			2},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_300505_1*/
	{&C_Struct_300C06_1[0],		3,				C_structure,			2},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_300C06_1*/
	{&C_Struct_400402_2[0],		12,				C_structure,			3},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_400402_2*/
	{&C_Struct_400402_1[0],		4,				C_structure,			4},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_400402_1*/
	{&C_Struct_400702_1[0],		10,				C_structure,			7},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_400702_1*/
	{&C_Struct_400C02_1[0],		5,				C_structure,			5},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_400C02_1*/		
	{&C_Struct_401102_1[0],		6,				C_structure,			2},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_401102_1*/	
	{&C_Struct_401402_1[0],		3,				C_structure,			3},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_401402_1*/	

	{&C_Struct_401F02_1[0],		12,				C_structure,			3},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_401F02_1*/	

	{&C_Struct_430003_1[0],		32,				C_structure,			6},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_430003_1*/	
	{&C_Struct_440003_1[0],		36,				C_structure,			7},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_440003_1*/	
	{&C_Struct_800002_1[0],		6,				C_structure,			2},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_800002_1*/	
	{&C_Struct_F10103_1[0],		4,				C_structure,			2},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_F10103_1*/	
	
    {&C_Struct_F20502_1[0],		4,				C_structure,			4},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_F20502_1*/	
	{&C_Struct_F20902_1[0],		13,				C_structure,			3},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_F20902_1*/		

    {&C_Struct_F20B02_2[0],		30,				C_structure,			4},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_F20B02_2*/	
    {&C_Struct_F20B02_1[0],		22,				C_structure,			2},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_F20B02_1*/	
    {&C_Struct_F20B04_1[0],		38,				C_structure,			2},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_F20B04_1*/	
    {&C_Struct_F20B05_3[0],		114,			C_structure,			3},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_F20B05_3*/	
    {&C_Struct_F20B06_1[0],		9,			    C_structure,			4},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_F20B06_1*/	
    
    {&C_Struct_F20D02_1[0],		9,				C_structure,			2},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_F20D02_1*/	
    {&C_Struct_F20E02_1[0],		9,				C_structure,			2},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_F20E02_1*/			

	{&C_Struct_F30002_1[0],		8+1,			C_structure,			2},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_F30002_1*/	
	{&C_Struct_F30005_1[0],		8+1+2,			C_structure,			3},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_F30005_1*/		
	{&C_Struct_F30004_1[0],		2,				C_structure,			2},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_F30004_1*/		
	{&C_Struct_330202_2[0],		19+40,				C_structure,		6},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_330202_2*/	
#if(C_PhaseType == C_Phase_3)	
	{&C_Struct_330802_1[0],		19+11,				C_structure,		7},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_330802_1*/	
#endif	
	{&C_Struct_330C02_2[0],		19+4,				C_structure,		6},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_330C02_2*/	
	{&C_Struct_331002_1[0],		19+16,				C_structure,		9},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_331002_1*/	
	{&C_Struct_331102_1[0],		19+4,				C_structure,		6},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_331102_1*/		
	{&C_Struct_331402_2[0],		19+4+42,			C_structure,		7},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_331402_2*/		
	{&C_Struct_331502_2[0],		19+4+6,				C_structure,		7},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_331502_2*/		

	{&C_Struct_331202_1[0],		22+2,				C_structure,		10},	/*C_Code_Complex|C_Code_Structure_1|C_CodeID_331202_1*/		

	{&C_Struct_500002_1[0],		2+4+2,				C_structure,		3},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_500002_1*/	
	{&C_Struct_F0010A_1[0],		1+1+4+4+2,			C_structure,		5},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_F0010A_1*/	
	{&C_Struct_800081_1[0],		4+1+2+1,			C_structure,		4},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_800081_1*/	
	{&C_Struct_800082_1[0],		4+1,				C_structure,		2},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_800082_1*/	
	{&C_Struct_800083_1[0],		4+1+8,				C_structure,		3},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_800083_1*/	

//	{&C_Struct_404002_1[0],		6+16+6,				C_structure,		3},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_404002_1*/	
	{&C_Struct_404402_1[0],		6,				    C_structure,		2},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_404402_1*/	

// 	{&C_Struct_260003_2[0],		32+80+6,			C_structure,		3},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_260003_2*/	
//    {&C_Struct_260003_1[0],		80,			        C_structure,		5},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_260003_1*/	

    {&C_Struct_303206_1[0],		5,			        C_structure,		3},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_303206_1*/	
    {&C_Struct_301F06_1[0],		7,			        C_structure,		4},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_301F06_1*/	
//   {&C_Struct_303306_1[0],		5,			        C_structure,		3},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_303306_1*/	
    {&C_Struct_303506_1[0],		7,			        C_structure,		3},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_303406_1*/	

	{&C_Struct_500205_1[0],		2+4+4,				C_structure,		3},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_500205_1*/	

    {&C_Struct_F30202_2[0],		9+639,				C_structure,		6},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_F30202_2*/	
    {&C_Struct_F30203_1[0],		3,				    C_structure,		3},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_F30203_1*/	

#if(C_PhaseType == C_Phase_3)	
    {&C_Struct_480004_2[0],		44,				    C_structure,		7},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_412002_2,NILM模块配置参数*/	
#else
	{&C_Struct_480004_2[0], 	20,					C_structure,		7}, 	/*C_Code_Complex|C_Code_Structure_1|C_CodeID_412002_2,NILM模块配置参数*/	
#endif
    
    {&C_Struct_403102_1[0],		CLFactory_Softw_Version_4031,		C_structure,		4},		/*C_Code_Complex|C_Code_Structure_1|C_CodeID_403102_1*/	
    
};


/*----------------------------------------------复杂编码值对应的表格---------------------------------------------------------------*/			
const CodeID_To_TablePara_T C_Str_CodeID_To_Table[]=
{
	{C_Str_Table_Code_Array_1,		C_Code_Array_1},
	{C_Str_Table_Code_Structure_1,	C_Code_Structure_1},
};										
/*四、变量定义*/


/*五、函数声明*/
uchar8  PF_RecordCValue_Coding_To_698_3000(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen);
uchar8  PF_RecordTimeSta_Coding_To_698_3000(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen);

/***********************************************************************
Function: PF_uchar8_Set_BitValue
Description:数据位置1或者清零
Input:    pDataIn 数据指针
			V_ucBitNum bit位数
			V_ucBitValue 1：置1；0：清零
	   
Output:	 
return:
Others:					                                                     
Author:
全局变量：						      
注意点：   
              
**********************************************************************/
void PF_uchar8_Set_BitValue(uchar8 *pDataIn,uchar8 V_ucBitNum,uchar8 V_ucBitValue)
{
	uchar8 V_ucDatabuf;	

	if(V_ucBitNum > 7)
	{
		V_ucBitNum = 0;
	}
	
	V_ucDatabuf = 1;
	V_ucDatabuf = (uchar8)(V_ucDatabuf<<V_ucBitNum);
	if(V_ucBitValue)
	{		
		*pDataIn |= V_ucDatabuf;
	}
	else
	{
		*pDataIn &= (~V_ucDatabuf);
	}	
	return;
}

/***********************************************************************
Function: PF_Mirroring_Bitstring
Description:bitstring 数据镜像处理
Input: V_ucDataIn 目标数据
Output:
Others:					                                                     
Author:
全局变量：						      
注意点：                             
**********************************************************************/
uchar8 PF_Mirroring_Byte(uchar8 V_ucDataIn)
{
	uchar8 i;
	uchar8 V_ReturnValue = 0;
	for(i=0;i<8;i++)
	{
		if(V_ucDataIn&0x01)	
		{
			PF_uchar8_Set_BitValue(&V_ReturnValue,7-i,1);
		}
		V_ucDataIn = V_ucDataIn >> 1;
	}
	
	return V_ReturnValue;
}

/***********************************************************************
Function: PF_Mirroring_Bitstring
Description:bitstring 数据镜像处理
Input: pBitstring 指针
		V_usByteNum pBitstring 的字节数
Output:
Others:					                                                     
Author:
全局变量：						      
注意点：                             
**********************************************************************/
void PF_Mirroring_Bitstring(uchar8 *pBitstring,ushort16 V_usByteNum)
{
	ushort16 i;
	uchar8 V_ucDatabuf;
	
	for(i=0;i<V_usByteNum/2;i++)
	{
		V_ucDatabuf = pBitstring[i];
		pBitstring[i] = pBitstring[V_usByteNum-1-i];
		pBitstring[V_usByteNum-1-i] = V_ucDatabuf;
	}
	
	for(i=0;i<V_usByteNum;i++)
	{
		pBitstring[i] = PF_Mirroring_Byte(pBitstring[i]);
	}	
}


/*****************************************************************************************************************
*Function:uchar8 PF_Is_ArrayBuff_Value                     
*Description:	判断数组值是否为一个指定值          										                    
*Input:  pDataIn 数组指针
		 V_ucValue 指定值
		 V_ucLen 数组长度                    
*Output:  无                                          								                            
*Return:	C_True | C_False
*Calls:																					                        
*Called By:																				                        
*Influence:																				                        
*Author:	G.G																				                        
*Tips:                                                                               	                        
*Others:																					                        
******************************************************************************************************************/
uchar8 PF_Is_ArrayBuff_Value(uchar8 *pDataIn,uchar8 V_ucValue,uchar8 V_ucLen)
{
	uchar8 V_ucReturnValue = C_True;
    uchar8 i;
	
	for(i=0;i<V_ucLen;i++)
	{
		if(pDataIn[i] != V_ucValue )
		{
			V_ucReturnValue = C_Flase;
			break;
		}
	}	
	return V_ucReturnValue;
}

/***********************************************************************
Function: ushort16 PF_CodeIDS_TO_DataLen(uchar8 V_ucCodeIDNum,uchar8 *p_ucDataIn)
Description:根据内部编码计算该编码对应的数据长度
Input:     uchar8 V_ucCodeIDNum,内部编码个数
			uchar8 *p_ucDataIn，内部编码数据指针
Output:		
return： ushort16返回长度值
Others:					                                                     
Author:
全局变量：						      
注意点：             
1、内部编码是ushort16，但这里的入参是用uchar8 *传递进来的。             
**********************************************************************/
ushort16 PF_CodeIDS_TO_DataLen(uchar8 V_ucCodeIDNum,uchar8 *p_ucDataIn)
{
	ushort16 V_usReturnValue = 0;
	ushort16 V_usDataLen;
	uchar8 i;
	for(i=0;i<V_ucCodeIDNum;i++)
	{
		PF_CodeID_TO_DataLen(PF_Buffer2ToLong16_698(&p_ucDataIn[i*2]),&V_usDataLen);
		V_usReturnValue += V_usDataLen;
	}
	
	return V_usReturnValue;
}

/***********************************************************************
Function: ushort16 PF_CodeID_TO_DataLen(ushort16 v_usCodeID)
Description:根据内部编码计算该编码对应的数据长度
Input:     ushort16 v_usCodeID:内部编码值
Output:		ushort16 *p_usDataLen 编码对应数据长度
return： #define		C_CodeOfTable					0x68		表格里的编码
		#define		C_CodeOfString					0x86		string类型的编码
		#define		C_CodeOfSimple					0x55		简单类型的编码
		#define		C_CodeErr						0xAA		错误的的编码
Others:					                                                     
Author:
全局变量：						      
注意点：                          
**********************************************************************/
uchar8 PF_CodeID_TO_DataLen(ushort16 v_usCodeID,ushort16 *p_usDataLen)
{
	uchar8 V_ucReturnValue = C_CodeErr;	/*初始值为越界*/
	ushort16 V_usDataLen=0;

    uchar8 V_ucTableNum = 0;;
    
    V_ucReturnValue = PF_CodeID_TO_TableNum(v_usCodeID,&V_ucTableNum);
    if(C_CodeOfTable == V_ucReturnValue)
    {/*表格能查到的编码，总长度从表格中获得*/
    	V_usDataLen = C_Str_CodeID_To_Table[V_ucTableNum].pstr_CodeTable[(uchar8)v_usCodeID].MaxDataLen;
    }
    else if(C_CodeOfString == V_ucReturnValue)
    {/*是复杂类型但表格查不到，可能是字串，长度可以计算得到*/
    	switch(v_usCodeID&C_Code_AndNum)
		{
			case C_Code_Bitstring:	/*bit-string类型*/					
				V_usDataLen = (uchar8)v_usCodeID;	
				V_usDataLen =(V_usDataLen-1)/8 + 1;				
				break;
			case C_Code_Bitstring1:	/*bit-string类型*/	
			case C_Code_Bitstring2:	/*bit-string类型*/
			case C_Code_Bitstring3:	/*bit-string类型*/
			case C_Code_Bitstring4:	/*bit-string类型*/
			case C_Code_Bitstring5:	/*bit-string类型*/			
			case C_Code_Bitstring6:	/*bit-string类型*/
			case C_Code_Bitstring7:	/*bit-string类型*/
			case C_Code_Bitstring8:	/*bit-string类型*/
			case C_Code_Bitstring9:	/*bit-string类型*/
			case C_Code_BitstringA:	/*bit-string类型*/
			case C_Code_BitstringB:	/*bit-string类型*/
			case C_Code_BitstringC:	/*bit-string类型*/			
			case C_Code_BitstringD:	/*bit-string类型*/
			case C_Code_BitstringE:	/*bit-string类型*/	
			case C_Code_BitstringF:	/*bit-string类型*/					
				V_usDataLen = ((v_usCodeID&C_Code_AndNum)-C_Code_Bitstring1) + 256 + (uchar8)v_usCodeID;
				V_usDataLen =(V_usDataLen-1)/8 + 1;
				break;	
			case C_Code_Visiblestring:	/*Visible-string类型*/
			case C_Code_Octetstring0:	/*Octet-string类型SIZE（0-255）*/
				V_usDataLen = (uchar8)v_usCodeID;				
				break;	
			case C_Code_Octetstring1:	/*Octet-string类型SIZE（256-2303）*/
			case C_Code_Octetstring2:	
			case C_Code_Octetstring3:	
			case C_Code_Octetstring4:	
			case C_Code_Octetstring5:	
			case C_Code_Octetstring6:	
			case C_Code_Octetstring7:	
			case C_Code_Octetstring8:				
				V_usDataLen = ((v_usCodeID&C_Code_AndNum)-C_Code_Octetstring1) +256 + (uchar8)v_usCodeID;				
				break;				
			default:
				break;
		}    	
    }
    else if(C_CodeOfSimple == V_ucReturnValue)
    {/*以上都不是，那就是简单类型的*/
		V_usDataLen = PF_Get_Code698_Len((uchar8)v_usCodeID);		
    }
    *p_usDataLen = V_usDataLen;
    return V_ucReturnValue;
}
/***********************************************************************
Function: 
Description:根据内部编码取底层编码
Input:     ushort16 v_usCodeID:内部编码值
			ushort16 *p_usBottomCodebuff:底层编码缓存指针
			ushort16 *p_usBottomCodebuffLen：缓存指针的最大长度
Output:		ushort16 *p_usBottomCodebuffLen：缓存指针的实际长度，上级是数据长度固定为2
return： #define		C_CodeOfTable					0x68		表格里的编码
		#define		C_CodeOfString					0x86		string类型的编码
		#define		C_CodeOfSimple					0x55		简单类型的编码
		#define		C_CodeErr						0xAA		错误的的编码

Others:					                                                     
Author:
全局变量：						      
注意点：                          
**********************************************************************/
uchar8 PF_CodeID_TO_BottomCode(ushort16 v_usCodeID,ushort16 *p_usBottomCodebuff,ushort16 *p_usBottomCodebuffLen)
{
	uchar8 V_ucTableNumStatus = C_CodeErr;
    uchar8 V_ucTableNum = 0;
	ushort16 V_usBottomLenbuf;
    
    V_ucTableNumStatus = PF_CodeID_TO_TableNum(v_usCodeID,&V_ucTableNum);
    if(C_CodeOfTable == V_ucTableNumStatus)
    {
		V_usBottomLenbuf = 2*((ushort16)C_Str_CodeID_To_Table[V_ucTableNum].pstr_CodeTable[(uchar8)v_usCodeID].MaxIndex);
		if(C_array == C_Str_CodeID_To_Table[V_ucTableNum].pstr_CodeTable[(uchar8)v_usCodeID].DataType)
		{/*如果是数组，底层编码其实都是同一个值*/
			*p_usBottomCodebuffLen = 2;
			p_usBottomCodebuff[0] = C_Str_CodeID_To_Table[V_ucTableNum].pstr_CodeTable[(uchar8)v_usCodeID].p_usBottomCode[0];
		}
		else if((*p_usBottomCodebuffLen) >= V_usBottomLenbuf)
		{
			*p_usBottomCodebuffLen = V_usBottomLenbuf;
//			PF_CopyDataShorts((ushort16 *)C_Str_CodeID_To_Table[V_ucTableNum].pstr_CodeTable[(uchar8)v_usCodeID].p_usBottomCode,&p_usBottomCodebuff[0],*p_usBottomCodebuffLen);
			
			memcpy(&p_usBottomCodebuff[0],C_Str_CodeID_To_Table[V_ucTableNum].pstr_CodeTable[(uchar8)v_usCodeID].p_usBottomCode,*p_usBottomCodebuffLen);
    	}    	
    	else
    	{
    		V_ucTableNumStatus = C_CodeErr;	/*缓存给的长度不够，直接报错误编码返回*/
    	}
    }	
	return V_ucTableNumStatus;
}

/***********************************************************************
Function: uchar8 PF_Get_MaxIndex(ushort16 v_usCodeID)
Description:根据内部编码取取对应属性的最大索引个数
Input:     ushort16 v_usCodeID:内部编码值
Output:
return： 
Others:					                                                     
Author:
全局变量：						      
注意点：                          
**********************************************************************/
uchar8 PF_Get_MaxIndex(ushort16 v_usCodeID)
{
	uchar8 V_ucTableNumStatus = C_CodeErr;
    uchar8 V_ucTableNum = 0;
	uchar8 V_MaxIndeNum=1;    
    V_ucTableNumStatus = PF_CodeID_TO_TableNum(v_usCodeID,&V_ucTableNum);
    if(C_CodeOfTable == V_ucTableNumStatus)
    {
		V_MaxIndeNum =C_Str_CodeID_To_Table[V_ucTableNum].pstr_CodeTable[(uchar8)v_usCodeID].MaxIndex;
	}
	return V_MaxIndeNum;
}
/***********************************************************************
Function: uchar8 PF_CodeID_TO_TableNum(ushort16 v_usCodeID,uchar8 *p_ucTableNum)
Description:根据内部编码取所在表格行号
Input:     ushort16 v_usCodeID：内部编码值
Output:		uchar8 *p_ucTableNum：对应表格行数
return：#define		C_CodeOfTable					0x68		表格里的编码
		#define		C_CodeOfString					0x86		string类型的编码
		#define		C_CodeOfSimple					0x55		简单类型的编码
		#define		C_CodeErr						0xAA		错误的的编码
Others:					                                                     
Author:
全局变量：						      
注意点：                          
**********************************************************************/
uchar8 PF_CodeID_TO_TableNum(ushort16 v_usCodeID,uchar8 *p_ucTableNum)
{
	uchar8 i;
	uchar8 V_ucReturnValue = C_CodeErr;	/*初始值为错误的的编码*/
	if(v_usCodeID&C_Code_Complex)/*复杂类型数据*/
	{		
		for(i=0;i<(sizeof(C_Str_CodeID_To_Table)/sizeof(CodeID_To_TablePara_T));i++)
		{
			if((v_usCodeID&C_Code_AndNum) == C_Str_CodeID_To_Table[i].CodeID)/*通过复杂编码类型查找相应表格*/
			{	
				break;
			}				
		}
		if(i<(sizeof(C_Str_CodeID_To_Table)/sizeof(CodeID_To_TablePara_T)))
		{
			V_ucReturnValue = C_CodeOfTable;
			*p_ucTableNum = i;
		}
		else
		{
			V_ucReturnValue = C_CodeOfString;
		}
	}
	else	
	{
		
		V_ucReturnValue = C_CodeOfSimple;
	}
		
	return V_ucReturnValue;	
}

/***********************************************************************
Function: uchar8 PF_Data_Decode_TO_698(uchar8 *SourceAddr,uchar8 *DerictAddr)
Description:将698格式数据转换为原始数据不带任何格式
Input:     uchar8 *SourceAddr,带698格式数据的地址指针
		    ushort16 *pv_usSourceLen：*SourceAddr对应数据长度        
		    ushort16 *pv_usDerictLen:*DerictAddr对应缓存指针的最长长度
Output:		uchar8 *DerictAddr,原始数据不带任何格式的地址指针，格式为data
			ushort16 *pv_usDerictLen：*DerictAddr对应数据实际长度
return：
Others:					                                                     
Author:
全局变量：						      
注意点：                          
**********************************************************************/
//uchar8 PF_Data_Encode_TO_Inside(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
//{
//	
//}


/***********************************************************************
Function: PF_DataLen_TO_A_XDR(ushort16 v_usDataLen,uchar8 *DerictAddr)
Description:通过String的长度来得到长度域
Input:     ushort16 &p_usDataLen,String的长度
Output:		uchar8 *DerictAddr 长度域地址指针
return：	长度域字节数
Others:					                                                     
Author:
全局变量：						      
注意点：                          
**********************************************************************/
uchar8 PF_DataLen_TO_A_XDR(ushort16 v_usDataLen,uchar8 *DerictAddr)
{
	uchar8 V_ucReturnValue=0;

	if(v_usDataLen<128)
	{
		DerictAddr[0] = (uchar8)v_usDataLen;
		V_ucReturnValue = 1;
	}
	else if(v_usDataLen<256)
	{
		DerictAddr[0] = 0x81;
		DerictAddr[1] = (uchar8)v_usDataLen;
		V_ucReturnValue = 2;
	}
	else
	{
		DerictAddr[0] = 0x82;
		DerictAddr[1] = (uchar8)(v_usDataLen>>8);
		DerictAddr[2] = (uchar8)v_usDataLen;
		V_ucReturnValue = 3;
	}
	
	return V_ucReturnValue;
}
/***********************************************************************
Function: uchar8 PF_CodeInside_To_698(ushort16 V_usCodeInside)
Description:内部编码转为698编码值
Input:     ushort16 V_usCodeInside
Output:		
return：	698编码值
Others:					                                                     
Author:
全局变量：						      
注意点：                          
**********************************************************************/
uchar8 PF_CodeInside_To_698(ushort16 V_usCodeInside)
{
	uchar8 i;
	uchar8 V_ucReturnValue = 0x00;
	
	if(V_usCodeInside&C_Code_Complex)
	{	
		V_usCodeInside &=C_Code_AndNum;
		for(i=0;i<sizeof(C_Str_CodeInside_To_698_Table)/sizeof(CodeInside_To_698_T);i++)
		{
			if(C_Str_CodeInside_To_698_Table[i].C_enumNum == V_usCodeInside)
			{
				V_ucReturnValue = C_Str_CodeInside_To_698_Table[i].Code_698;
				break;	
			}		
		}	
	}
	else
	{
		V_ucReturnValue = (uchar8)V_usCodeInside;
	}
	return V_ucReturnValue;
}
/***********************************************************************
Function: uchar8 PF_JudgeBottomData(ushort16 *p_usBottomDataBuff,uchar8 V_ucIndexNum)
Description:判断底层编码数组里是否存在需要再次查表的编码值
Input:     ushort16 *p_usBottomDataBuff：底层编码数组指针
			ushort16 V_usIndexNum			：底层编码数组个数
Output:		
return：#define		C_CodeOfTable					0x68	有下级嵌套编码
		#define		C_CodeOfSimple					0x55	无下级嵌套编码
Others:	                                                     
Author:
全局变量：						      
注意点：                          
**********************************************************************/
uchar8 PF_JudgeBottomData(ushort16 *p_usBottomDataBuff,ushort16 V_usIndexNum)
{
	uchar8 i;
	uchar8 V_ucTableNum = 0;
	uchar8 V_ucReturnValue;
	
	for(i=0;i<V_usIndexNum;i++)
	{
		V_ucReturnValue = PF_CodeID_TO_TableNum(p_usBottomDataBuff[i],&V_ucTableNum);
		if(C_CodeOfTable == V_ucReturnValue)
		{
			break;
		}
	}
	if(C_CodeOfTable!=V_ucReturnValue)	
	{
		V_ucReturnValue = C_CodeOfSimple;
	}
	return V_ucReturnValue;
}

/***********************************************************************
Function: PF_Get_Code698_Struct(ushort16 v_usCodeID,Code_Code698_Level_T *pstr_Code698_Level)
Description:获得698线性编码格式
Input:     ushort16 v_usCodeID,   内部编码值
		   Code_Code698_Level_T *pstr_Code698_Level	线性编码格式结构体指针
Output:		
return：C_Code_OK 是线性结构
		C_CodeErr 不是线性结构
Others:	    
typedef struct
{ 	    
    uchar8 LevelNum;					编码嵌套等级
    uchar8  CodeID_HighLevel[12];  		高嵌套级的698编码值
    uchar8 CodeID_Bottom_Num;			最底层数据分项个数
    ushort16 Len_Of_Bottom698Data[16];	最底层数据分项数据长度遍历
    ushort16 Len_Of_BottomCode[16];    	最底层数据分项698编码长度遍历 
    uchar8 Data_Of_BottomCode[64];		最底层数据分项698编码遍历  
}Code_Code698_Level_T;                                               
Author:
全局变量：						      
注意点：                          
**********************************************************************/
uchar8 PF_Get_Code698_Struct(ushort16 v_usCodeID,Code_Code698_Level_T *pstr_Code698_Level)
{
	uchar8 i;
	uchar8 V_ucTableNum = 0;
	uchar8 V_ucReturnValue;
	ushort16 V_usBottomCodebuffLen;
	ushort16 V_usBottomCodebuff[16];
	ushort16 V_ucDataOffset;
	uchar8 V_ucAXlen;
	uchar8 V_ucStructOver = C_Starting;
	uchar8 V_ucCyclicNum;
	ushort16 V_usA_XDRLen;

	pstr_Code698_Level->LevelNum = 0;
	for(i=0;i<6;i++)
	{
		V_ucReturnValue = PF_CodeID_TO_TableNum(v_usCodeID,&V_ucTableNum);		/*查询内部编码的类型及表格行号*/
		if( C_CodeOfTable == V_ucReturnValue)
		{
			V_usBottomCodebuffLen = sizeof(V_usBottomCodebuff);
			PF_CodeID_TO_BottomCode(v_usCodeID,&V_usBottomCodebuff[0],&V_usBottomCodebuffLen);/*取本级编码对应的底层编码值*/	
			
//			PF_CopyDataBytes(&pstr_Code698_Level->CodeID_HighLevel[0],&pstr_Code698_Level->CodeID_HighLevel[2], pstr_Code698_Level->LevelNum*2);	/*高嵌套级的698编码值保存*/				
			memmove(&pstr_Code698_Level->CodeID_HighLevel[2],&pstr_Code698_Level->CodeID_HighLevel[0], pstr_Code698_Level->LevelNum*2);	/*高嵌套级的698编码值保存*/	
			pstr_Code698_Level->CodeID_HighLevel[0] = C_Str_CodeID_To_Table[V_ucTableNum].pstr_CodeTable[(uchar8)v_usCodeID].DataType;
			pstr_Code698_Level->CodeID_HighLevel[1] = C_Str_CodeID_To_Table[V_ucTableNum].pstr_CodeTable[(uchar8)v_usCodeID].MaxIndex;	
			
			pstr_Code698_Level->CodeID_Bottom_Num = C_Str_CodeID_To_Table[V_ucTableNum].pstr_CodeTable[(uchar8)v_usCodeID].MaxIndex;	/*本级编码对应底层数据分项个数*/
			pstr_Code698_Level->LevelNum++;																								/*线性结构嵌套等级+1*/
                        
			if(C_CodeOfSimple == PF_JudgeBottomData(&V_usBottomCodebuff[0],V_usBottomCodebuffLen/2 ))/*底层里全部都是可以直接编码的，线性结束*/
			{
				V_ucReturnValue = C_Code_OK;
				V_ucStructOver = C_Ending;
			}
			else
			{
				if(C_structure == pstr_Code698_Level->CodeID_HighLevel[0])/*如果本级是结构体，且底层存在复杂类型，该高级编码不是线性结构*/
				{
					V_ucReturnValue = C_CodeErr;/*不是线性编码格式*/
					V_ucStructOver = C_Ending;
				}
				else
				{					
					v_usCodeID = V_usBottomCodebuff[0];	/*是数组，继续查下去*/
				}				
			}
		}
		else
		{
			V_usBottomCodebuff[0] = v_usCodeID;/*这是一个可以直接使用的编码值*/
			pstr_Code698_Level->LevelNum = 0;	/*嵌套等级为0级*/
			pstr_Code698_Level->CodeID_Bottom_Num = 1;/*数据分项个数为1*/
			V_ucReturnValue = C_Code_OK;
			V_ucStructOver = C_Ending;
		}
		if(C_Ending == V_ucStructOver)
		{
			break;
		}
	}
	
	if(C_Code_OK == V_ucReturnValue)/*如果前面查完是一个完整的线性结构编码，那么要对最底层的数据构造进行解释*/
	{
		if((C_array == pstr_Code698_Level->CodeID_HighLevel[0])	/*1级嵌套是数组，或只有0级嵌套，分项数据个数为1*/
			||(0 == pstr_Code698_Level->LevelNum))
		{
			V_ucCyclicNum = 1;
		}	
		else
		{
			V_ucCyclicNum = pstr_Code698_Level->CodeID_Bottom_Num;/*分项个数为索引个数*/
		}	
		
		V_ucDataOffset = 0;
		for(i=0;i<V_ucCyclicNum;i++)
		{
			V_ucReturnValue = PF_CodeID_TO_DataLen(V_usBottomCodebuff[i],&pstr_Code698_Level->Len_Of_Bottom698Data[i]);/*取纯数据的长度*/
			V_ucAXlen = 0;
			if(C_CodeOfString == V_ucReturnValue)
			{/*string编码，可以直接解码*/			
				pstr_Code698_Level->Data_Of_BottomCode[V_ucDataOffset]=PF_CodeInside_To_698(V_usBottomCodebuff[i]);/*698编码*/
				
				V_usA_XDRLen = pstr_Code698_Level->Len_Of_Bottom698Data[i];
				if(C_bit_string == pstr_Code698_Level->Data_Of_BottomCode[V_ucDataOffset])	/*如果是位串，这里的长度实际是位数*/			
				{
					if((V_usBottomCodebuff[i]&0x3F00) == C_Code_Bitstring)
					{
						V_usA_XDRLen = (uchar8)V_usBottomCodebuff[i];	
					}
					else
					{
						V_usA_XDRLen = ((V_usBottomCodebuff[i]&C_Code_AndNum)-C_Code_Bitstring1) + 256 + (uchar8)V_usBottomCodebuff[i];
					}
				}
				
				V_ucAXlen = PF_DataLen_TO_A_XDR(V_usA_XDRLen,&pstr_Code698_Level->Data_Of_BottomCode[V_ucDataOffset + 1]);/*string类型的构造解释*/
			}
			else if(C_CodeOfSimple == V_ucReturnValue)
			{/*简单的编码，可以直接解码*/		
				pstr_Code698_Level->Data_Of_BottomCode[V_ucDataOffset]=(uchar8)V_usBottomCodebuff[i];/*698编码*/	
			}
			pstr_Code698_Level->Len_Of_BottomCode[i] = 1 + V_ucAXlen;
			V_ucDataOffset = V_ucDataOffset + pstr_Code698_Level->Len_Of_BottomCode[i] ;	/*解码后698格式数据缓存偏移重新计算*/
		}
		V_ucReturnValue = C_Code_OK;
	}	
	return V_ucReturnValue;	
}

/***********************************************************************
Function: uchar8 PF_Get_Code698_Struct_Data(Code_Code698_Level_T vstr_Code698_Level,uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
Description:获得698线性编码格式
Input:     Code_Code698_Level_T *pstr_Code698_Level	线性编码格式结构体指针
		   uchar8 *SourceAddr：	源数据指针
		   ushort16 *pv_usSourceLen：	源数据长度
		   uchar8 *DerictAddr：	目标数据缓存指针
		   ushort16 *pv_usDerictLen：目标数据缓存给定最大长度
Output:		ushort16 *pv_usDerictLen：目标数据缓存真实最大长度		
return：C_Code_OK:执行成功 C_Code_OverStep：提供缓存不足
Others:	    
typedef struct
{ 	    
    uchar8 LevelNum;					编码嵌套等级
    uchar8  CodeID_HighLevel[12];  		高嵌套级的698编码值
    uchar8 CodeID_Bottom_Num;			最底层数据分项个数
    ushort16 Len_Of_Bottom698Data[16];	最底层数据分项数据长度遍历
    ushort16 Len_Of_BottomCode[16];    	最底层数据分项698编码长度遍历 
    uchar8 Data_Of_BottomCode[64];		最底层数据分项698编码遍历  
}Code_Code698_Level_T;                                                   
Author:
全局变量：						      
注意点：                          
**********************************************************************/
uchar8 PF_Get_Code698_Struct_Data(Code_Code698_Level_T *pStr_Code698_Level,uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
{
	uchar8 V_ucReturnValue=C_Code_OverStep;
	uchar8 i,V_ucCyclicNum;
    ushort16 V_usCode698_Struct_Len;

 	
	if(pStr_Code698_Level->LevelNum<6)/*嵌套等级最多允许5级*/
	{
		V_usCode698_Struct_Len = PF_Get_Code698_Struct_Len(*pStr_Code698_Level,pStr_Code698_Level->LevelNum);
		if(*pv_usDerictLen >= V_usCode698_Struct_Len)/*编码后数据长度比缓存长度要大，返回越界错*/
	    {	
			V_ucCyclicNum = pStr_Code698_Level->LevelNum;
			for(i=0;i<=V_ucCyclicNum;i++)
			{
				V_ucReturnValue = PF_Get_Code698_Struct_BottomData(pStr_Code698_Level,&SourceAddr[0],&pv_usSourceLen[0],&DerictAddr[0],&pv_usDerictLen[0]);/*组织最底层698数据*/
				if(V_ucReturnValue !=C_Code_OK)
				{
					break;
				}
				PF_Get_Code698_Struct_DropLevel(pStr_Code698_Level);/*嵌套降级*/			
				pv_usSourceLen[0] = pv_usDerictLen[0];
			}
		}
		else
	    {
	    	V_ucReturnValue = C_Code_OverStep;	/*数据长度不对都是越界*/
	    }
	}
	
	return V_ucReturnValue;
}
/***********************************************************************
Function: uchar8 PF_Get_Code698_Struct_Data(Code_Code698_Level_T vstr_Code698_Level,uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
Description:获得698线性编码格式
Input:     Code_Code698_Level_T *pstr_Code698_Level	线性编码格式结构体指针
		   uchar8 *SourceAddr：	源数据指针
		   ushort16 *pv_usSourceLen：	源数据长度
		   uchar8 *DerictAddr：	目标数据缓存指针
		   ushort16 *pv_usDerictLen：目标数据缓存给定最大长度
Output:		ushort16 *pv_usDerictLen：目标数据缓存真实最大长度		
return：C_Code_OK 成功
		C_Code_OverStep 目标数据缓存不够，数据越界
Others:	    
typedef struct
{ 	    
    uchar8 LevelNum;					编码嵌套等级
    uchar8  CodeID_HighLevel[12];  		高嵌套级的698编码值
    uchar8 CodeID_Bottom_Num;			最底层数据分项个数
    ushort16 Len_Of_Bottom698Data[16];	最底层数据分项数据长度遍历
    ushort16 Len_Of_BottomCode[16];    	最底层数据分项698编码长度遍历 
    uchar8 Data_Of_BottomCode[64];		最底层数据分项698编码遍历  
}Code_Code698_Level_T;                                                
Author:
全局变量：						      
注意点：                          
**********************************************************************/
uchar8 PF_Get_Code698_Struct_BottomData(Code_Code698_Level_T *pstr_Code698_Level,uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
{
	ushort16 V_usBottomDatalen,V_usAllDatalen;
	uchar8 V_ucReturnValue;
	ushort16 V_usCyclicNum,i,j;
	ushort16 V_usDtaOffset,V_usSourceOffset;
	ushort16 V_usDatabuf,V_usDatabuf2;
	
	if(pstr_Code698_Level->LevelNum)
	{
    	V_usBottomDatalen = 0;/*取最底层数据长度*/    	
    	if(C_array == pstr_Code698_Level->CodeID_HighLevel[0])
    	{
    		V_usBottomDatalen = (ushort16)(pstr_Code698_Level->CodeID_Bottom_Num*pstr_Code698_Level->Len_Of_Bottom698Data[0]);
    	}
    	else
    	{
    		for(i=0;i<pstr_Code698_Level->CodeID_Bottom_Num;i++)
			{
				V_usBottomDatalen += pstr_Code698_Level->Len_Of_Bottom698Data[i];
			}
    	}
		
		V_usAllDatalen = V_usBottomDatalen;/*计算对应源数据总长度*/
		for(i=1;i<pstr_Code698_Level->LevelNum;i++)
		{
			V_usAllDatalen = (ushort16)(V_usAllDatalen * (ushort16)(pstr_Code698_Level->CodeID_HighLevel[i*2+1]));
		}
		
		if(V_usAllDatalen <= *pv_usSourceLen)
		{
			V_usCyclicNum = V_usAllDatalen/V_usBottomDatalen;
			V_usDtaOffset = 0;
			V_usSourceOffset = 0;			
			for(j=0;j<V_usCyclicNum;j++)/*遍历一遍数据，加上最底层的698编码值*/
			{
				V_usDatabuf = 0;
				for(i=0;i<pstr_Code698_Level->CodeID_Bottom_Num;i++)/*从源数据中取一组底层数据*/
				{
					if(C_array == pstr_Code698_Level->CodeID_HighLevel[0])
					{
						V_usDatabuf2=0;
						V_usDatabuf = 0;
					}
					else
					{
						V_usDatabuf2 = i;
					}					

					memcpy(&DerictAddr[V_usDtaOffset],&pstr_Code698_Level->Data_Of_BottomCode[V_usDatabuf],pstr_Code698_Level->Len_Of_BottomCode[V_usDatabuf2]); /*先取698编码*/
					V_usDtaOffset += pstr_Code698_Level->Len_Of_BottomCode[V_usDatabuf2];										
					memcpy(&DerictAddr[V_usDtaOffset],&SourceAddr[V_usSourceOffset],pstr_Code698_Level->Len_Of_Bottom698Data[V_usDatabuf2]); /*再取数据*/
					if(pstr_Code698_Level->Data_Of_BottomCode[V_usDatabuf] == C_bit_string)	/*bitstring要按编码协议进行镜像处理*/
					{
						PF_Mirroring_Bitstring(&DerictAddr[V_usDtaOffset],pstr_Code698_Level->Len_Of_Bottom698Data[V_usDatabuf2]);
					}
					V_usDatabuf += pstr_Code698_Level->Len_Of_BottomCode[V_usDatabuf2];	
					V_usDtaOffset += pstr_Code698_Level->Len_Of_Bottom698Data[V_usDatabuf2];		
					V_usSourceOffset += pstr_Code698_Level->Len_Of_Bottom698Data[V_usDatabuf2];	

				}				
			}
			memcpy(&SourceAddr[0],&DerictAddr[0],V_usDtaOffset);/*将数据拷贝到目标数据缓存中*/
			*pv_usDerictLen = V_usDtaOffset;
			V_ucReturnValue = C_Code_OK;
			
		}
		else
		{
			V_ucReturnValue = C_Code_OverStep;	/*数据长度不对都是越界*/
		}	
	}
	else
	{	
		V_usAllDatalen = pstr_Code698_Level->Len_Of_Bottom698Data[0];/*计算对应源数据总长度*/			
		if(V_usAllDatalen <= *pv_usSourceLen)
		{				
			V_usDtaOffset = 0;
			memcpy(&DerictAddr[0],&pstr_Code698_Level->Data_Of_BottomCode[0],pstr_Code698_Level->Len_Of_BottomCode[0]); /*先取698编码*/
			V_usDtaOffset += pstr_Code698_Level->Len_Of_BottomCode[0];
			memcpy(&DerictAddr[V_usDtaOffset],&SourceAddr[0],pstr_Code698_Level->Len_Of_Bottom698Data[0]); /*再取数据*/
			if(pstr_Code698_Level->Data_Of_BottomCode[0] == C_bit_string)	/*bitstring要按编码协议进行镜像处理*/
			{
				PF_Mirroring_Bitstring(&DerictAddr[V_usDtaOffset],pstr_Code698_Level->Len_Of_Bottom698Data[0]);
			}
			V_usDtaOffset += pstr_Code698_Level->Len_Of_Bottom698Data[0];		
			*pv_usDerictLen = V_usDtaOffset;
			V_ucReturnValue = C_Code_OK;
		}
		else
		{
			V_ucReturnValue = C_Code_OverStep;	/*数据长度不对都是越界*/
		}
	}
	return V_ucReturnValue;
}

/***********************************************************************
Function: uchar8 PF_Get_Code698_Len(uchar8 V_ucCode698)
Description:获得698编码对应的数据长度
Input: 		V_ucCode698 698编码
Output:		
return：长度，0表示复杂类型不能直接计算长度
Others:	    
                                          
Author:
全局变量：						      
注意点：                          
**********************************************************************/
uchar8 PF_Get_Code698_Len(uchar8 V_ucCode698)
{
	uchar8 i;
	uchar8 V_usDataLen = 0;
	
	for(i=0;i<(sizeof(Str_CodeLenOf698Table)/sizeof(CodeLenOf698Table_T));i++)
	{
		if(V_ucCode698 == Str_CodeLenOf698Table[i].CodeOf698Type)
		{				
			V_usDataLen = Str_CodeLenOf698Table[i].DataLenOf698Type;
			break;
		}
	}
	return V_usDataLen;
}

/***********************************************************************
Function: uchar8 PF_Get_Code698_And_Data_Len(uchar8 V_ucCode698)
Description:获得698编码及其对应数据长度之和
Input: 		V_ucCode698 698编码
Output:		
return：长度，0表示复杂类型不能直接计算长度
Others:	    
                                          
Author:
全局变量：						      
注意点：                          
**********************************************************************/
uchar8 PF_Get_Code698_And_Data_Len(uchar8 V_ucCode698)
{
	uchar8 i;
	uchar8 V_usDataLen = 0;
	
	for(i=0;i<(sizeof(Str_CodeLenOf698Table)/sizeof(CodeLenOf698Table_T));i++)
	{
		if(V_ucCode698 == Str_CodeLenOf698Table[i].CodeOf698Type)
		{				
			V_usDataLen = Str_CodeLenOf698Table[i].DataLenOf698Type + 1;
			break;
		}
	}
	return V_usDataLen;
}
/***********************************************************************
Function: ushort PF_Get_Code698_Struct_Len(Code_Code698_Level_T vstr_Code698_Level)
Description:获得698线性编码格式编码后总数据长度
Input: 		   Code_Code698_Level_T *pstr_Code698_Level	线性编码格式结构体指针
Output:		
return：
Others:	    
typedef struct
{ 	    
    uchar8 LevelNum;					编码嵌套等级
    uchar8  CodeID_HighLevel[12];  		高嵌套级的698编码值
    uchar8 CodeID_Bottom_Num;			最底层数据分项个数
    ushort16 Len_Of_Bottom698Data[16];	最底层数据分项数据长度遍历
    ushort16 Len_Of_BottomCode[16];    	最底层数据分项698编码长度遍历 
    uchar8 Data_Of_BottomCode[64];		最底层数据分项698编码遍历  
}Code_Code698_Level_T;                                                
Author:
全局变量：						      
注意点：                          
**********************************************************************/
ushort16 PF_Get_Code698_Struct_Len(Code_Code698_Level_T vstr_Code698_Level,uchar8 v_ucCodeLevel)
{
	uchar8 i;
	ushort16 V_usReturnLen=0;
	
	if(vstr_Code698_Level.LevelNum < v_ucCodeLevel)
	{
		V_usReturnLen=0;
	}	
	else if(vstr_Code698_Level.LevelNum)
	{/*有嵌套等级*/		
		if(C_array == vstr_Code698_Level.CodeID_HighLevel[0])
		{
			V_usReturnLen = (ushort16)((vstr_Code698_Level.Len_Of_Bottom698Data[0] + vstr_Code698_Level.Len_Of_BottomCode[0])*vstr_Code698_Level.CodeID_Bottom_Num);
		}
		else
		{
			for(i=0;i<vstr_Code698_Level.CodeID_Bottom_Num;i++)
			{
				V_usReturnLen += vstr_Code698_Level.Len_Of_Bottom698Data[i];
				V_usReturnLen += vstr_Code698_Level.Len_Of_BottomCode[i];
			}		
		}
		if(v_ucCodeLevel)
		{			
			if(vstr_Code698_Level.LevelNum<6)/*默认线性结构最多嵌套5级，出现6级计算会出错，不管*/
			{
				vstr_Code698_Level.CodeID_HighLevel[vstr_Code698_Level.LevelNum*2+1]=0x01;
			}
			for(i=1;i<=v_ucCodeLevel;i++)
			{				
				V_usReturnLen =(ushort16)((V_usReturnLen + 2)*vstr_Code698_Level.CodeID_HighLevel[i*2+1]);
			}
		}		
	}
	else
	{
		V_usReturnLen = vstr_Code698_Level.Len_Of_Bottom698Data[0] + vstr_Code698_Level.Len_Of_BottomCode[0];/*嵌套等级为0，直接算长度就好了*/
	}
    return V_usReturnLen;	
}

/***********************************************************************
Function: ushort PF_Get_Code698_Struct_Len(Code_Code698_Level_T vstr_Code698_Level)
Description:698线性编码格式嵌套等级降一级
Input:    Code_Code698_Level_T *pstr_Code698_Level	线性编码格式结构体指针
Output:		
return：
Others:	    
typedef struct
{ 	    
    uchar8 LevelNum;					编码嵌套等级
    uchar8  CodeID_HighLevel[12];  		高嵌套级的698编码值
    uchar8 CodeID_Bottom_Num;			最底层数据分项个数
    ushort16 Len_Of_Bottom698Data[16];	最底层数据分项数据长度遍历
    ushort16 Len_Of_BottomCode[16];    	最底层数据分项698编码长度遍历 
    uchar8 Data_Of_BottomCode[64];		最底层数据分项698编码遍历  
}Code_Code698_Level_T;                                                
Author:
全局变量：						      
注意点：                          
**********************************************************************/
void PF_Get_Code698_Struct_DropLevel(Code_Code698_Level_T *pstr_Code698_Level)
{	
	if(pstr_Code698_Level->LevelNum)
	{	
		pstr_Code698_Level->Len_Of_Bottom698Data[0] = PF_Get_Code698_Struct_Len(*pstr_Code698_Level,0);/*原0级数据长度为现在的新的底层数据长度*/
		pstr_Code698_Level->Len_Of_BottomCode[0] = 2;/*新的底层编码长度默认为2*/	
		
		memcpy(&pstr_Code698_Level->Data_Of_BottomCode[0],&pstr_Code698_Level->CodeID_HighLevel[0],2); /*移动1级编码到底层编码缓存中*/
		memmove(&pstr_Code698_Level->CodeID_HighLevel[0],&pstr_Code698_Level->CodeID_HighLevel[2],(pstr_Code698_Level->LevelNum*2)-2); /*将原1级编码推出高级编码区*/	
		pstr_Code698_Level->LevelNum--;				/*嵌套等级降级*/
		pstr_Code698_Level->CodeID_Bottom_Num=pstr_Code698_Level->CodeID_HighLevel[1];	/*底层分项个数为1级编码索引个数*/
	}
}

/***********************************************************************
Function: PF_Get_Code698_Data(uchar8 * p_CodeID,uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
Description:将一组带内部编码的数据转换为带698格式编码的数据
Input:   	uchar8 * p_CodeID  内部编码指针
			uchar8 *SourceAddr,待解码数据的地址指针，格式为 data
		    ushort16 *pv_usSourceLen：*SourceAddr对应数据长度        
		    ushort16 *pv_usDerictLen:*DerictAddr对应缓存指针的最长长度
Output:		uchar8 *DerictAddr,解码完成后的数据地址指针，格式为data（698编码加数据） 
			ushort16 *pv_usDerictLen：*DerictAddr对应数据实际长度	
return：C_Code_OK:执行成功 C_Code_OverStep：提供缓存不足
Others:	    
typedef struct
{ 	    
    uchar8 LevelNum;					编码嵌套等级
    uchar8  CodeID_HighLevel[12];  		高嵌套级的698编码值
    uchar8 CodeID_Bottom_Num;			最底层数据分项个数
    ushort16 Len_Of_Bottom698Data[16];	最底层数据分项数据长度遍历
    ushort16 Len_Of_BottomCode[16];    	最底层数据分项698编码长度遍历 
    uchar8 Data_Of_BottomCode[64];		最底层数据分项698编码遍历  
}Code_Code698_Level_T;                                                   
Author:
全局变量：						      
注意点：     
1、本函数支持        SourceAddr和         DerictAddr为同一个值    
**********************************************************************/
uchar8 PF_Get_Code698_Data(uchar8 * p_CodeID,uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
{
	Code_Code698_Level_T VStr_Code698_Level;
	uchar8 V_ucReturnValue=C_Code_OverStep;
    ushort16 V_usCodeID;
    ushort16 V_usSourceLen = *pv_usSourceLen;
    uchar8 V_ucSourceDataBuff[2048];    
    uchar8 V_ucSrcData_bak[2048];
    
    ushort16 V_usCodeIDBuff[10];	/*待编码内部编码值*/
    ushort16 i,j,V_usCodeIDBuffLen,V_usCodeIDBuffLen1;	/*待编码内部编码数据长度*/
    ushort16 V_usDecodeOffset=0;
	ushort16 V_usDerictOffset=0,V_usDerictLen = *pv_usDerictLen;
	uchar8 V_ucTableNum;
	
	memcpy(&V_ucSrcData_bak[0],&SourceAddr[0],V_usSourceLen);
    memcpy(&V_ucSourceDataBuff[0],&SourceAddr[0],V_usSourceLen);
    V_usCodeID = PF_Buffer2ToLong16_698(&p_CodeID[0]);  
    switch(V_usCodeID)
    {
    	case (C_Code_Complex|C_Code_Array_1|C_CodeID_F30002_2):	/**/
    		V_ucReturnValue = PF_CSDArray_Coding_To_698(&V_ucSourceDataBuff[0], pv_usSourceLen,&DerictAddr[0], pv_usDerictLen); 
    		break;
    	case (C_Code_Complex|C_Code_Structure_1|C_CodeID_F30002_1):
    		V_ucReturnValue = PF_CSD_Coding_To_698(&V_ucSourceDataBuff[0], pv_usSourceLen,&DerictAddr[0], pv_usDerictLen);
    		break;
    	case (C_Code_Complex|C_Code_Structure_1|C_CodeID_F30005_1):
    		V_ucReturnValue = PF_F30005_1_Coding_To_698(&V_ucSourceDataBuff[0], pv_usSourceLen,&DerictAddr[0], pv_usDerictLen);
    		break;	    		
    	case C_us_TI:
    		V_ucReturnValue = PF_TI_Coding_To_698(&V_ucSourceDataBuff[0], pv_usSourceLen,&DerictAddr[0], pv_usDerictLen); 
    		break;
    	case (C_Code_Complex|C_Code_Array_1|C_CodeID_30000A_2):
    		V_ucReturnValue = PF_RecordCValue_Coding_To_698(&V_ucSourceDataBuff[0], pv_usSourceLen,&DerictAddr[0], pv_usDerictLen);
    		break;
    	case (C_Code_Complex|C_Code_Array_1|C_CodeID_30000E_2):
    		V_ucReturnValue = PF_RecordTimeSta_Coding_To_698(&V_ucSourceDataBuff[0], pv_usSourceLen,&DerictAddr[0], pv_usDerictLen); 
    		break;
    	case (C_Code_Complex|C_Code_Structure_1|C_CodeID_30000E_1):
    		V_ucReturnValue = PF_RecordTimeStaBottom_Coding_To_698(&V_ucSourceDataBuff[0], pv_usSourceLen,&DerictAddr[0], pv_usDerictLen); 
    		break;  
    	case C_Code_Complex|C_Code_Array_1|C_CodeID_30090A_3:
    		DerictAddr[0] = C_array;
    		DerictAddr[1] = 1;
    		V_usDerictLen = *pv_usDerictLen - 2;
    		V_ucReturnValue = PF_RecordTimeStaid7_Coding_To_698(&V_ucSourceDataBuff[0], pv_usSourceLen,&DerictAddr[2], &V_usDerictLen);
    		*pv_usDerictLen = V_usDerictLen + 2;    	
    		break;		  
    	case C_Code_Complex|C_Code_Structure_1|C_CodeID_30090A_2:
    		V_ucReturnValue = PF_RecordTimeStaid7_Coding_To_698(&V_ucSourceDataBuff[0], pv_usSourceLen,&DerictAddr[0], pv_usDerictLen);
    		break;	
    	case C_Code_Complex|C_Code_Array_1|C_CodeID_300907_3:
    		V_ucReturnValue = PF_RecordCValueid7_Coding_To_698(&V_ucSourceDataBuff[0], pv_usSourceLen,&DerictAddr[0], pv_usDerictLen);
    		break;	    
#if(C_PhaseType == C_Phase_3)              
    	case (C_Code_Complex|C_Code_Array_1|C_CodeID_30000A_3):
    		V_ucReturnValue = PF_RecordCValue_Coding_To_698_3000(&V_ucSourceDataBuff[0], pv_usSourceLen,&DerictAddr[0], pv_usDerictLen);
    		break;
    	case (C_Code_Complex|C_Code_Array_1|C_CodeID_30000E_3):
    		V_ucReturnValue = PF_RecordTimeSta_Coding_To_698_3000(&V_ucSourceDataBuff[0], pv_usSourceLen,&DerictAddr[0], pv_usDerictLen); 
    		break;

    	case C_Code_Complex|C_Code_Structure_1|C_CodeID_30230A_2:	
    		V_ucReturnValue = PF_C_CodeID_30230A_2_Coding_To_698(&V_ucSourceDataBuff[0], pv_usSourceLen,&DerictAddr[0], pv_usDerictLen);
    		break;
    	case C_Code_Complex|C_Code_Array_1|C_CodeID_30230A_3:   
    		DerictAddr[0] = C_array;
    		DerictAddr[1] = 2;	
    		V_usDerictOffset = 2;
    		V_usDerictLen = *pv_usDerictLen - V_usDerictOffset;    		
    		V_ucReturnValue = PF_C_CodeID_30230A_2_Coding_To_698(&V_ucSourceDataBuff[0], pv_usSourceLen,&DerictAddr[V_usDerictOffset], &V_usDerictLen);
    		if(V_ucReturnValue == C_OK_DAR)
    		{
    			V_usDerictOffset += V_usDerictLen;
    			V_usDerictLen = *pv_usDerictLen - V_usDerictOffset;
    			V_ucReturnValue = PF_C_CodeID_30230A_2_Coding_To_698(&V_ucSourceDataBuff[15], pv_usSourceLen,&DerictAddr[V_usDerictOffset], &V_usDerictLen);
    			if(V_ucReturnValue == C_OK_DAR)
    			{
    				*pv_usDerictLen = V_usDerictOffset+V_usDerictLen;
    			}
    		}    		
    		break;
    	case C_Code_Complex|C_Code_Array_1|C_CodeID_302307_3:    		
    		V_ucReturnValue = PF_C_CodeID_302307_3_Coding_To_698(&V_ucSourceDataBuff[0], pv_usSourceLen,&DerictAddr[0], pv_usDerictLen);
    		break; 
#endif
    	case  C_Code_Complex|C_Code_Array_1|C_CodeID_401102_2:
    		V_ucReturnValue = PF_C_CodeID_401102_Coding_To_698(&V_ucSourceDataBuff[0], pv_usSourceLen,&DerictAddr[0], pv_usDerictLen);
    		break;   	    	   	
    	case  C_Code_Complex|C_Code_Array_1|C_CodeID_330202_1:
    		V_ucReturnValue = PF_C_CodeID_330202_Coding_To_698(&V_ucSourceDataBuff[0], pv_usSourceLen,&DerictAddr[0], pv_usDerictLen);
    		break;	    
#if(C_PhaseType == C_Phase_3)
    	case  C_Code_Complex|C_Code_Array_1|C_CodeID_101002_2:	/*有功需量编码*/
    	case  C_Code_Complex|C_Code_Array_1|C_CodeID_101102_2:	
    		V_ucReturnValue = PF_C_CodeID_1010_Coding_To_698(&V_ucSourceDataBuff[0], pv_usSourceLen,&DerictAddr[0], pv_usDerictLen);
    		break;		
    	case  C_Code_Complex|C_Code_Array_1|C_CodeID_103002_2:	/*组合无功需量编码*/
    	case  C_Code_Complex|C_Code_Array_1|C_CodeID_103102_2:	
    		V_ucReturnValue = PF_C_CodeID_1030_Coding_To_698(&V_ucSourceDataBuff[0], pv_usSourceLen,&DerictAddr[0], pv_usDerictLen);
    		break;
#endif    	
        case C_Code_Complex|C_Code_Array_1|C_CodeID_F30202_3:            
            V_ucReturnValue = PF_C_CodeID_F30202_Coding_To_698(&V_ucSourceDataBuff[0], pv_usSourceLen,&DerictAddr[0], pv_usDerictLen);
    		break;    
        case C_Code_Complex|C_Code_Array_1|C_CodeID_F20B05_4: 
            DerictAddr[0] = C_array;
    		DerictAddr[1] = 1;
    		V_usDerictLen = *pv_usDerictLen - 2;
            V_ucReturnValue = PF_C_CodeID_F20B05_Coding_To_698(&V_ucSourceDataBuff[0], pv_usSourceLen,&DerictAddr[2], &V_usDerictLen);
    		*pv_usDerictLen = V_usDerictLen + 2;  
            break;
        case C_Code_Complex|C_Code_Structure_1|C_CodeID_F20B05_3:     
            V_ucReturnValue = PF_C_CodeID_F20B05_Coding_To_698(&V_ucSourceDataBuff[0], pv_usSourceLen,&DerictAddr[0], pv_usDerictLen);
    		break; 
    	default:
    		if(C_Code_OK == PF_Get_Code698_Struct( V_usCodeID,&VStr_Code698_Level))/*如果是线性结构的，采用线性编码方式*/
		    {
		    	PF_Get_Code698_ChangeLen(&VStr_Code698_Level,V_usSourceLen);	
		    	V_ucReturnValue =PF_Get_Code698_Struct_Data(&VStr_Code698_Level,&V_ucSourceDataBuff[0],&V_usSourceLen,&DerictAddr[0],&pv_usDerictLen[0]);			    
		    }
		    else
		    {
		    	PF_CodeID_TO_TableNum(V_usCodeID,&V_ucTableNum);
		    	V_usCodeIDBuffLen = sizeof(V_usCodeIDBuff);
				PF_CodeID_TO_BottomCode(V_usCodeID,&V_usCodeIDBuff[0],&V_usCodeIDBuffLen);/*先取内部编码的底层编码值*/	
				DerictAddr[0] = C_Str_CodeID_To_Table[V_ucTableNum].pstr_CodeTable[(uchar8)V_usCodeID].DataType;	
				DerictAddr[1] = C_Str_CodeID_To_Table[V_ucTableNum].pstr_CodeTable[(uchar8)V_usCodeID].MaxIndex;		
				V_usDecodeOffset=0;
			    V_usDerictOffset=2;	 
				for(i=0;i<V_usCodeIDBuffLen/2;i++)
				{		
					V_usCodeID = V_usCodeIDBuff[i];	
					if(C_Code_OK == PF_Get_Code698_Struct(V_usCodeID,&VStr_Code698_Level))
                    {
                        PF_CodeID_TO_DataLen(V_usCodeIDBuff[i],&V_usSourceLen);	
						memcpy(&V_ucSourceDataBuff[0],&V_ucSrcData_bak[V_usDecodeOffset],V_usSourceLen);
						V_ucReturnValue =PF_Get_Code698_Struct_Data(&VStr_Code698_Level,&V_ucSourceDataBuff[0],&V_usSourceLen,&DerictAddr[V_usDerictOffset],&pv_usDerictLen[0]);
						if(V_ucReturnValue == C_Code_OK)
						{
							PF_CodeID_TO_DataLen(V_usCodeIDBuff[i],&V_usSourceLen);	
							V_usDecodeOffset += V_usSourceLen;
							V_usDerictOffset +=(*pv_usDerictLen);
							*pv_usDerictLen = V_usDerictLen - V_usDerictOffset;
						}
						else
						{
							break;
						}
                    }
                    else
                    {                        
                        PF_CodeID_TO_TableNum(V_usCodeID,&V_ucTableNum);
                        V_usCodeIDBuffLen1 = sizeof(V_usCodeIDBuff);
                        PF_CodeID_TO_BottomCode(V_usCodeID,&V_usCodeIDBuff[0],&V_usCodeIDBuffLen1);/*先取内部编码的底层编码值*/	
                        DerictAddr[2] = C_Str_CodeID_To_Table[V_ucTableNum].pstr_CodeTable[(uchar8)V_usCodeID].DataType;	
                        DerictAddr[3] = C_Str_CodeID_To_Table[V_ucTableNum].pstr_CodeTable[(uchar8)V_usCodeID].MaxIndex;		
                        V_usDecodeOffset=0;
                        V_usDerictOffset=4;
                        for(j=0;j<V_usCodeIDBuffLen1/2;j++)
                        {
                            PF_Get_Code698_Struct( V_usCodeIDBuff[j],&VStr_Code698_Level);
                            PF_CodeID_TO_DataLen(V_usCodeIDBuff[j],&V_usSourceLen);	
                            memcpy(&V_ucSourceDataBuff[0],&V_ucSrcData_bak[V_usDecodeOffset],V_usSourceLen);
                            V_ucReturnValue =PF_Get_Code698_Struct_Data(&VStr_Code698_Level,&V_ucSourceDataBuff[0],&V_usSourceLen,&DerictAddr[V_usDerictOffset],&pv_usDerictLen[0]);
                            if(V_ucReturnValue == C_Code_OK)
                            {
                                PF_CodeID_TO_DataLen(V_usCodeIDBuff[j],&V_usSourceLen);	
                                V_usDecodeOffset += V_usSourceLen;
                                V_usDerictOffset +=(*pv_usDerictLen);
                                *pv_usDerictLen = V_usDerictLen - V_usDerictOffset;
                            }
                            else
                            {
                                break;
                            }
                        }						
                    }
					
				}
				if(V_ucReturnValue == C_Code_OK)
				{
					*pv_usDerictLen = V_usDerictOffset;
				}
		    }
    		break;
    }
    return V_ucReturnValue;
}
/***********************************************************************
Function: uchar8 PF_Get_Code698_ChangeLen(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
Description:通过数据长度和线性编码的比对来重新计算底层索引个数
Input:     Code_Code698_Level_T *pstr_Code698_Level,
			ushort16 v_usCodeID
Output:		Code_Code698_Level_T *pstr_Code698_Level,
return：
Others:	    
typedef struct
{ 	    
    uchar8 LevelNum;					编码嵌套等级
    uchar8  CodeID_HighLevel[12];  		高嵌套级的698编码值
    uchar8 CodeID_Bottom_Num;			最底层数据分项个数
    ushort16 Len_Of_Bottom698Data[16];	最底层数据分项数据长度遍历
    ushort16 Len_Of_BottomCode[16];    	最底层数据分项698编码长度遍历 
    uchar8 Data_Of_BottomCode[64];		最底层数据分项698编码遍历  
}Code_Code698_Level_T;                                                   
Author:
全局变量：						      
注意点：                          
**********************************************************************/
void PF_Get_Code698_ChangeLen(Code_Code698_Level_T *pstr_Code698_Level,ushort16 v_usDataLen)
{
	uchar8 i;
	ushort16 v_usBottomLen;
	uchar8 v_ucBottomNum;
	
	if(pstr_Code698_Level->LevelNum == 0)
	{
		if((C_visible_string == pstr_Code698_Level->Data_Of_BottomCode[0])/**/
			||(C_octet_string == pstr_Code698_Level->Data_Of_BottomCode[0])/**/)			
		{
			if(v_usDataLen < pstr_Code698_Level->Data_Of_BottomCode[1])
			{
				pstr_Code698_Level->Data_Of_BottomCode[1] = v_usDataLen;
				pstr_Code698_Level->Len_Of_Bottom698Data[0] = v_usDataLen;
			}
		}
	}
	else if(pstr_Code698_Level->LevelNum == 1)
	{
		if(C_array == pstr_Code698_Level->CodeID_HighLevel[0])/*1级嵌套数组格式长度允许自由*/
		{
			v_usBottomLen = pstr_Code698_Level->Len_Of_Bottom698Data[0];
			v_ucBottomNum = (uchar8)(v_usDataLen/v_usBottomLen);
			if(v_ucBottomNum == 0)	/*数组个数为0，该嵌套级别需要编码为null*/
			{
				PF_Init_Code698_Level_T(pstr_Code698_Level);	/*初始化编码线性结构体*/
			}
			else if(v_ucBottomNum < pstr_Code698_Level->CodeID_HighLevel[1])
			{
				pstr_Code698_Level->CodeID_HighLevel[1] = v_ucBottomNum;
				pstr_Code698_Level->CodeID_Bottom_Num = v_ucBottomNum;
			}
		}
	}
	else if((pstr_Code698_Level->LevelNum == 2)&&(C_array == pstr_Code698_Level->CodeID_HighLevel[2]))
	{
		if(C_array != pstr_Code698_Level->CodeID_HighLevel[0])/*2级是C_array，1级为其他允许变长*/
		{
			v_usBottomLen = 0;
			for(i=0;i<pstr_Code698_Level->CodeID_Bottom_Num;i++)
			{
				v_usBottomLen +=pstr_Code698_Level->Len_Of_Bottom698Data[i];
			}
			
			v_ucBottomNum = (uchar8)(v_usDataLen/v_usBottomLen);
			
			if(v_ucBottomNum == 0)	/*数组个数为0，该嵌套级别需要编码为null*/
			{
				PF_Init_Code698_Level_T(pstr_Code698_Level);	/*初始化编码线性结构体*/
			}
			if(v_ucBottomNum < pstr_Code698_Level->CodeID_HighLevel[3])
			{
				pstr_Code698_Level->CodeID_HighLevel[3] = v_ucBottomNum;
			}
		}
	}
	else if((pstr_Code698_Level->LevelNum == 3)&&(C_array == pstr_Code698_Level->CodeID_HighLevel[4]))
	{
		v_usDataLen = v_usDataLen/pstr_Code698_Level->CodeID_HighLevel[5];
		v_usBottomLen = 0;
		for(i=0;i<pstr_Code698_Level->CodeID_Bottom_Num;i++)
		{
			v_usBottomLen +=pstr_Code698_Level->Len_Of_Bottom698Data[i];
		}
		
		v_ucBottomNum = (uchar8)(v_usDataLen/v_usBottomLen);
		
		if(v_ucBottomNum == 0)	/*数组个数为0，该嵌套级别需要编码为null*/
		{
			PF_Init_Code698_Level_T(pstr_Code698_Level);	/*初始化编码线性结构体*/
		}
		if(v_ucBottomNum < pstr_Code698_Level->CodeID_HighLevel[3])
		{
			pstr_Code698_Level->CodeID_HighLevel[3] = v_ucBottomNum;
		}
	}
}

/***********************************************************************
Function: uchar8  PF_TI_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
Description:显示列表内部编码到698编码处理函数
Input:     uchar8 *SourceAddr,				源数据
			ushort16 *pv_usSourceLen,		源数据长度
			uchar8 *DerictAddr,				目标缓存
			ushort16 *pv_usDerictLen		目标缓存长度
Output:		ushort16 *pv_usDerictLen 		编码后数据实际长度
return：C_Code_OK:执行成功 C_Code_OverStep：提供缓存不足
Others:	    
                                                  
Author:
全局变量：						      
注意点：                          
**********************************************************************/
uchar8  PF_TI_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
{
	uchar8 V_ucReturnValue=C_Code_OverStep;
	
	if((*pv_usSourceLen == 3)&&(*pv_usDerictLen >=6))
	{
		DerictAddr[0] = C_TI;
		DerictAddr[1] = C_enum;/*枚举*/
		DerictAddr[2] = SourceAddr[0];/**/
		DerictAddr[3] = C_long_unsigned;/**/
		DerictAddr[4] = SourceAddr[1];/**/
		DerictAddr[5] = SourceAddr[2];/**/
		*pv_usDerictLen = 0;
	}
	return V_ucReturnValue;
}
/***********************************************************************
Function: PF_RecordCValue_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
Description:事件记录当前值记录表编码
Input:     uchar8 *SourceAddr,				源数据
			ushort16 *pv_usSourceLen,		源数据长度
			uchar8 *DerictAddr,				目标缓存
			ushort16 *pv_usDerictLen		目标缓存长度
Output:		ushort16 *pv_usDerictLen 		编码后数据实际长度
return：C_Code_OK:执行成功 C_Code_OverStep：提供缓存不足
Others:	    
                                                  
Author:
全局变量：						      
注意点：                          
**********************************************************************/
uchar8  PF_RecordCValue_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
{
	uchar8 V_ucReturnValue=C_Code_OverStep;
	#if(C_PhaseType == C_Phase_3)	/*分相事件当前值记录表，单相表只有A相*/
	uchar8 i;
	
	if(C_Equal == PF_Is_ArrayBuff_Value(SourceAddr,0xFF,8))/*前8个字节为全FF的，数组第一个元素编码为Null*/
	{
		if(*pv_usDerictLen >=39)
		{
			*pv_usDerictLen = 39;
			DerictAddr[0] = C_array;
			DerictAddr[1] = 4;
			DerictAddr[2] = C_null;
			for(i=0;i<3;i++)
			{
				DerictAddr[3+12*i] = C_structure;
				DerictAddr[4+12*i] = 2;
				DerictAddr[5+12*i] = C_double_long_unsigned;
				memcpy(&DerictAddr[6+12*i],&SourceAddr[8+8*i],4);	
				DerictAddr[10+12*i] = C_double_long_unsigned;
				memcpy(&DerictAddr[11+12*i],&SourceAddr[12+8*i],4);						
			}
			V_ucReturnValue = C_Code_OK;	
		}
	}
	else if(*pv_usDerictLen >=50)
	{
		*pv_usDerictLen = 50;
		DerictAddr[0] = C_array;
		DerictAddr[1] = 4;
		for(i=0;i<4;i++)
		{
			DerictAddr[2+12*i] = C_structure;
			DerictAddr[3+12*i] = 2;
			DerictAddr[4+12*i] = C_double_long_unsigned;
			memcpy(&DerictAddr[5+12*i],&SourceAddr[8*i],4);	
			DerictAddr[9+12*i] = C_double_long_unsigned;
			memcpy(&DerictAddr[10+12*i],&SourceAddr[4+8*i],4);						
		}
        V_ucReturnValue = C_Code_OK;
	}
	#else
	if(*pv_usDerictLen >=17)
	{
		*pv_usDerictLen = 17;
		DerictAddr[0] = C_array;
		DerictAddr[1] = 4;
		DerictAddr[2] = C_null;
		DerictAddr[3] = C_structure;
		DerictAddr[4] = 2;
		DerictAddr[5] = C_double_long_unsigned;
		memcpy(&DerictAddr[6],&SourceAddr[8],4);	
		DerictAddr[10] = C_double_long_unsigned;
		memcpy(&DerictAddr[11],&SourceAddr[12],4);	
		DerictAddr[15] = C_null;
		DerictAddr[16] = C_null;
		V_ucReturnValue = C_Code_OK;	
	}
	#endif
	
	return V_ucReturnValue;
}



/***********************************************************************
Function: PF_C_CodeID_30230A_2_Coding_To_698
Input:     uchar8 *SourceAddr,				源数据
			ushort16 *pv_usSourceLen,		源数据长度
			uchar8 *DerictAddr,				目标缓存
			ushort16 *pv_usDerictLen		目标缓存长度
Output:		ushort16 *pv_usDerictLen 		编码后数据实际长度
return：C_Code_OK:执行成功 C_Code_OverStep：提供缓存不足
Others:	    
                                                  
Author:
全局变量：						      
注意点：                          
**********************************************************************/
uchar8  PF_C_CodeID_302307_3_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
{
	uchar8 V_ucReturnValue=C_Code_OverStep;
	
	if(*pv_usDerictLen >= 30)
	{
		DerictAddr[0] = C_array;
		DerictAddr[1] = 2;
		
		DerictAddr[2] = C_structure;
		DerictAddr[3] = 2;
		DerictAddr[4] = C_enum;		
		DerictAddr[5] = SourceAddr[0];	
		DerictAddr[6] = C_structure;
		DerictAddr[7] = 2;	
		DerictAddr[8] = C_double_long_unsigned;
		memcpy(&DerictAddr[9],&SourceAddr[1],4);
		DerictAddr[13] = C_double_long_unsigned;
		memcpy(&DerictAddr[14],&SourceAddr[5],4);
		
		DerictAddr[18] = C_structure;
		DerictAddr[19] = 2;
		DerictAddr[20] = C_enum;		
		DerictAddr[21] = SourceAddr[9];	
		DerictAddr[22] = C_structure;
		DerictAddr[23] = 2;		
		DerictAddr[24] = C_double_long_unsigned;
		memcpy(&DerictAddr[25],&SourceAddr[10],4);
		DerictAddr[29] = C_double_long_unsigned;
		memcpy(&DerictAddr[30],&SourceAddr[14],4);
		*pv_usDerictLen = 34;
		V_ucReturnValue = C_Code_OK;
	}
	return V_ucReturnValue;
}





/***********************************************************************
Function: PF_C_CodeID_1010_Coding_To_698
Input:     uchar8 *SourceAddr,				源数据
			ushort16 *pv_usSourceLen,		源数据长度
			uchar8 *DerictAddr,				目标缓存
			ushort16 *pv_usDerictLen		目标缓存长度
Output:		ushort16 *pv_usDerictLen 		编码后数据实际长度
return：C_Code_OK:执行成功 C_Code_OverStep：提供缓存不足
Others:	    
                                                  
Author:
全局变量：						      
注意点：                          
**********************************************************************/
uchar8  PF_C_CodeID_1030_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
{
	uchar8 V_ucReturnValue=C_Code_OverStep;
	uchar8 i;
	uchar8 V_ucNum;
	uchar8 V_ucDataLen;
	uchar8 V_ucOffset;
	
	if((*pv_usSourceLen == 11)||(*pv_usSourceLen == 55))
	{
		V_ucNum = (*pv_usSourceLen)/11;			/*计算数据有几组*/
		
		if(C_True == PF_Is_ArrayBuff_Value(SourceAddr,0xFF,*pv_usSourceLen))
		{
			DerictAddr[0] = C_null;
			V_ucDataLen = 1;
		}
		else
		{
			DerictAddr[0] = C_array;
			DerictAddr[1] = V_ucNum; 
			V_ucDataLen = 2 + 15*V_ucNum;
			for(i=0;i<V_ucNum;i++)
			{
				V_ucOffset = 2+i*15;
				DerictAddr[V_ucOffset] = C_structure;
				DerictAddr[V_ucOffset+1] = 2;
				DerictAddr[V_ucOffset+2] = C_double_long;
				memcpy(&DerictAddr[V_ucOffset+3],&SourceAddr[11*i],4);
				DerictAddr[V_ucOffset + 7] = C_date_time_s;
				memcpy(&DerictAddr[V_ucOffset+8],&SourceAddr[11*i + 4],7);				
			}
		}
		
		*pv_usDerictLen = V_ucDataLen;
		V_ucReturnValue = C_Code_OK;
	}
	return V_ucReturnValue;
}
/***********************************************************************
Function: PF_C_CodeID_1010_Coding_To_698
Input:     uchar8 *SourceAddr,				源数据
			ushort16 *pv_usSourceLen,		源数据长度
			uchar8 *DerictAddr,				目标缓存
			ushort16 *pv_usDerictLen		目标缓存长度
Output:		ushort16 *pv_usDerictLen 		编码后数据实际长度
return：C_Code_OK:执行成功 C_Code_OverStep：提供缓存不足
Others:	    
                                                  
Author:
全局变量：						      
注意点：                          
**********************************************************************/
uchar8  PF_C_CodeID_1010_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
{
	uchar8 V_ucReturnValue=C_Code_OverStep;
	uchar8 i;
	uchar8 V_ucNum;
	uchar8 V_ucDataLen;
	uchar8 V_ucOffset;
	
	if((*pv_usSourceLen == 11)||(*pv_usSourceLen == 55))
	{
		V_ucNum = (*pv_usSourceLen)/11;			/*计算数据有几组*/
		
		if(C_True == PF_Is_ArrayBuff_Value(SourceAddr,0xFF,*pv_usSourceLen))
		{
			DerictAddr[0] = C_null;
			V_ucDataLen = 1;
		}
		else
		{
			DerictAddr[0] = C_array;
			DerictAddr[1] = V_ucNum; 
			V_ucDataLen = 2 + 15*V_ucNum;
			for(i=0;i<V_ucNum;i++)
			{
				V_ucOffset = 2+i*15;
				DerictAddr[V_ucOffset] = C_structure;
				DerictAddr[V_ucOffset+1] = 2;
				DerictAddr[V_ucOffset+2] = C_double_long_unsigned;
				memcpy(&DerictAddr[V_ucOffset+3],&SourceAddr[11*i],4);
				DerictAddr[V_ucOffset + 7] = C_date_time_s;
				memcpy(&DerictAddr[V_ucOffset+8],&SourceAddr[11*i + 4],7);				
			}
		}
		
		*pv_usDerictLen = V_ucDataLen;
		V_ucReturnValue = C_Code_OK;
	}
	return V_ucReturnValue;
}
/***********************************************************************
Function: PF_C_CodeID_330202_Coding_To_698
Input:     uchar8 *SourceAddr,				源数据
			ushort16 *pv_usSourceLen,		源数据长度
			uchar8 *DerictAddr,				目标缓存
			ushort16 *pv_usDerictLen		目标缓存长度
Output:		ushort16 *pv_usDerictLen 		编码后数据实际长度
return：C_Code_OK:执行成功 C_Code_OverStep：提供缓存不足
Others:	    
                                                  
Author:
全局变量：						      
注意点：                          
**********************************************************************/
uchar8  PF_C_CodeID_330202_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
{
	uchar8 V_ucReturnValue=C_Code_OverStep;
	uchar8 i;
	uchar8 V_ucOADNum;
	uchar8 V_ucDataLen;
	
	V_ucOADNum = 10;
	for(i=0;i<10;i++)
	{
		if((PF_Is_ArrayBuff_Value(&SourceAddr[4*i],0xFF,4) == C_True)
            ||(PF_Is_ArrayBuff_Value(&SourceAddr[4*i],0x00,4) == C_True))
		{			
			V_ucOADNum = i;
			break;
		}
	}
	
	V_ucDataLen = 2+V_ucOADNum*5;
	
	if(V_ucDataLen <= *pv_usDerictLen)
	{
		DerictAddr[0] = C_array;
		DerictAddr[1] = V_ucOADNum;
		for(i=0;i<V_ucOADNum;i++)
		{
			DerictAddr[2+5*i] = C_OAD;
			memcpy(&DerictAddr[3+5*i] ,&SourceAddr[4*i],4);
		}
		*pv_usDerictLen = V_ucDataLen;
		V_ucReturnValue = C_Code_OK;
	}
	return V_ucReturnValue;
}
/***********************************************************************
Function: PF_C_CodeID_401102_Coding_To_698
Input:     uchar8 *SourceAddr,				源数据
			ushort16 *pv_usSourceLen,		源数据长度
			uchar8 *DerictAddr,				目标缓存
			ushort16 *pv_usDerictLen		目标缓存长度
Output:		ushort16 *pv_usDerictLen 		编码后数据实际长度
return：C_Code_OK:执行成功 C_Code_OverStep：提供缓存不足
Others:	    
                                                  
Author:
全局变量：						      
注意点：                          
**********************************************************************/
uchar8  PF_C_CodeID_401102_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
{
	uchar8 V_ucReturnValue=C_Code_OverStep;
	uchar8 V_ucHolidayNum;
	uchar8 V_ucResponseNum;
	ushort16 V_usOffset;
	uchar8 i;
	
	//lint -e(734)
	V_ucHolidayNum = (uchar8)(*pv_usSourceLen/6);	/*计算数据源的假日个数*/			
	
	if(*pv_usDerictLen <= 1272)/*计算缓存可以最多保存多少个假日个数*/
	{		
		V_ucResponseNum = (uchar8)(((*pv_usDerictLen)- 2)/10);/*127个以下*/
	}
	else
	{
		V_ucResponseNum = (uchar8)(((*pv_usDerictLen)- 3)/10);/*128个以上*/
	}	
	
	V_ucHolidayNum = ((V_ucHolidayNum <= V_ucResponseNum)? V_ucHolidayNum:V_ucResponseNum);	/*公共节假日一个APDU能回多少就回多少*/
	if(V_ucHolidayNum)	
	{
		DerictAddr[0] = C_array;
		if(V_ucHolidayNum<128)
		{		
			DerictAddr[1] = V_ucHolidayNum;
			V_usOffset = 2;
		}
		else
		{
			DerictAddr[1] = 0x81;
			DerictAddr[2] = V_ucHolidayNum;
			V_usOffset = 3;
		}
		
		for(i=0;i<V_ucHolidayNum;i++)
		{
			if(C_True == PF_Is_ArrayBuff_Value(&SourceAddr[6*i],0x00,5))	/*年月日周均为0，进行数据修正*/
			{				
				memset(&SourceAddr[6*i],0xFF,5);	
				SourceAddr[6*i + 5] = 0x01;			
			}
			
			DerictAddr[V_usOffset]  = C_structure;
			DerictAddr[V_usOffset+1] = 2;
			DerictAddr[V_usOffset+2] = C_date;
			memcpy(&DerictAddr[V_usOffset+3],&SourceAddr[6*i],5);
			DerictAddr[V_usOffset+8] = C_unsigned;
			DerictAddr[V_usOffset+9] = SourceAddr[6*i+5];
			V_usOffset +=10;
		}
		*pv_usDerictLen = V_usOffset;
		V_ucReturnValue = C_Code_OK;
	}
    else
    {
    	DerictAddr[0] = C_null;
    	*pv_usDerictLen = 1;
    	V_ucReturnValue = C_Code_OK;
    }
	return V_ucReturnValue;
}
/***********************************************************************
Function: PF_C_CodeID_30230A_2_Coding_To_698
Input:     uchar8 *SourceAddr,				源数据
			ushort16 *pv_usSourceLen,		源数据长度
			uchar8 *DerictAddr,				目标缓存
			ushort16 *pv_usDerictLen		目标缓存长度
Output:		ushort16 *pv_usDerictLen 		编码后数据实际长度
return：C_Code_OK:执行成功 C_Code_OverStep：提供缓存不足
Others:	    
                                                  
Author:
全局变量：						      
注意点：                          
**********************************************************************/
uchar8  PF_C_CodeID_30230A_2_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
{
	uchar8 V_ucReturnValue=C_Code_OverStep;
	
	if(*pv_usDerictLen >= 15)
	{
		DerictAddr[0] = C_structure;
		DerictAddr[1] = 2;
		DerictAddr[2] = C_enum;		
		DerictAddr[3] = SourceAddr[0];
		
		if(C_True == PF_Is_ArrayBuff_Value(&SourceAddr[1],0x00,7))	
		{
			DerictAddr[4] = C_null;
			*pv_usDerictLen = 5;			
		}
		else
		{
			DerictAddr[4] = C_structure;
			DerictAddr[5] = 2;
			DerictAddr[6] = C_date_time_s;
			memcpy(&DerictAddr[7],&SourceAddr[1],7);
			DerictAddr[14] = C_null;
			*pv_usDerictLen = 15;
		}
		V_ucReturnValue = C_Code_OK;
	}
	return V_ucReturnValue;
}
/***********************************************************************
Function: PF_RecordCValueid7_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
Description:事件记录当前值记录表编码
Input:     uchar8 *SourceAddr,				源数据
			ushort16 *pv_usSourceLen,		源数据长度
			uchar8 *DerictAddr,				目标缓存
			ushort16 *pv_usDerictLen		目标缓存长度
Output:		ushort16 *pv_usDerictLen 		编码后数据实际长度
return：C_Code_OK:执行成功 C_Code_OverStep：提供缓存不足
Others:	    
                                                  
Author:
全局变量：						      
注意点：                          
**********************************************************************/
uchar8  PF_RecordCValueid7_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
{
	uchar8 V_ucReturnValue=C_Code_OverStep;
	
	if(*pv_usDerictLen >= 17)
	{
		DerictAddr[0] = C_array;
		DerictAddr[1] = 1;
		DerictAddr[2] = C_structure;
		DerictAddr[3] = 2;
		DerictAddr[4] = C_null;
		DerictAddr[5] = C_structure;
		DerictAddr[6] = 2;
		DerictAddr[7] = C_double_long_unsigned;
		memcpy(&DerictAddr[8],&SourceAddr[0],4);
		if(*pv_usSourceLen == 4)
		{
			DerictAddr[12] = C_null;
			*pv_usDerictLen = 13;
		}
		else
		{
			DerictAddr[12] = C_double_long_unsigned;
			memcpy(&DerictAddr[13],&SourceAddr[4],4);
			*pv_usDerictLen = 17;
		}
			
		V_ucReturnValue = C_Code_OK;
	}
	return V_ucReturnValue;
}
/***********************************************************************
Function: PF_RecordTimeSta_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
Description:时间状态编码
Input:     uchar8 *SourceAddr,				源数据
			ushort16 *pv_usSourceLen,		源数据长度
			uchar8 *DerictAddr,				目标缓存
			ushort16 *pv_usDerictLen		目标缓存长度
Output:		ushort16 *pv_usDerictLen 		编码后数据实际长度
return：C_Code_OK:执行成功 C_Code_OverStep：提供缓存不足
Others:	    
                                                  
Author:
全局变量：						      
注意点：                          
**********************************************************************/
uchar8  PF_RecordTimeSta_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
{
	uchar8 V_ucReturnValue=C_Code_OverStep;
	ushort16 V_usMaxLenbuf;	 		
	#if(C_PhaseType == C_Phase_3)	/*分相事件当前值记录表，单相表只有A相*/
	uchar8 i;
	ushort16 V_usOffset;
	
	if(C_Equal == PF_Is_ArrayBuff_Value(SourceAddr,0xFF,14))/*前14个字节为全FF的，数组第一个元素编码为Null*/
	{		
		DerictAddr[0] = C_array;
		DerictAddr[1] = 4;
		DerictAddr[2] = C_null;
		V_usOffset = 3;			
		for(i=0;i<3;i++)
		{
			V_usMaxLenbuf = (*pv_usDerictLen)-V_usOffset;
			V_ucReturnValue = PF_RecordTimeStaBottom_Coding_To_698(&SourceAddr[14+14*i],C_Null_Ptr,&DerictAddr[V_usOffset],&V_usMaxLenbuf);
			if(V_ucReturnValue != C_Code_OK)
			{
				break;
			}
			V_usOffset	+=	V_usMaxLenbuf;		
		}		
	}
	else 
	{
		DerictAddr[0] = C_array;
		DerictAddr[1] = 4;
		V_usOffset = 2;	
		for(i=0;i<4;i++)
		{
			V_usMaxLenbuf = (*pv_usDerictLen)-V_usOffset;
			V_ucReturnValue = PF_RecordTimeStaBottom_Coding_To_698(&SourceAddr[14*i],C_Null_Ptr,&DerictAddr[V_usOffset],&V_usMaxLenbuf);
			if(V_ucReturnValue != C_Code_OK)
			{
				break;
			}
			V_usOffset	+=	V_usMaxLenbuf;					
		}
	}
	if(V_ucReturnValue == C_Code_OK)
	{
		*pv_usDerictLen = V_usOffset;
	}
	#else
	DerictAddr[0] = C_array;
	DerictAddr[1] = 4;
	DerictAddr[2] = C_null;
	V_usMaxLenbuf = (*pv_usDerictLen)-5;
	V_ucReturnValue = PF_RecordTimeStaBottom_Coding_To_698(&SourceAddr[14],C_Null_Ptr,&DerictAddr[3],&V_usMaxLenbuf);	
	if(V_ucReturnValue == C_Code_OK)
	{
		DerictAddr[V_usMaxLenbuf + 3] = C_null;
		DerictAddr[V_usMaxLenbuf + 4] = C_null;
		*pv_usDerictLen = V_usMaxLenbuf + 5;
	}	
	#endif
	
	return V_ucReturnValue;
}
/***********************************************************************
Function: PF_RecordTimeStaBottom_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
Description:时间状态编码
Input:     uchar8 *SourceAddr,				源数据
			ushort16 *pv_usSourceLen,		源数据长度
			uchar8 *DerictAddr,				目标缓存
			ushort16 *pv_usDerictLen		目标缓存长度
Output:		ushort16 *pv_usDerictLen 		编码后数据实际长度
return：C_Code_OK:执行成功 C_Code_OverStep：提供缓存不足
Others:	    
                                                  
Author:
全局变量：						      
注意点：                          
**********************************************************************/
uchar8  PF_RecordTimeStaBottom_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
{
	uchar8 V_ucReturnValue=C_Code_OverStep;
	uchar8 V_ucDerictBuff[18];
	uchar8 V_ucOffset;
	
	
	V_ucDerictBuff[0] = C_structure;
	V_ucDerictBuff[1] = 2;
	V_ucOffset = 2;
	if(C_Equal == PF_Is_ArrayBuff_Value(&SourceAddr[0],0x00,7))
	{
		V_ucDerictBuff[V_ucOffset] = C_null;
		V_ucOffset++;
	}
	else
	{
		V_ucDerictBuff[V_ucOffset] = C_date_time_s;
		V_ucOffset++;
		memcpy(&V_ucDerictBuff[V_ucOffset],&SourceAddr[0],7);
		V_ucOffset +=7;
	}
	
	if(C_Equal == PF_Is_ArrayBuff_Value(&SourceAddr[7],0x00,7))
	{
		V_ucDerictBuff[V_ucOffset] = C_null;
		V_ucOffset++;
	}
	else
	{
		V_ucDerictBuff[V_ucOffset] = C_date_time_s;
		V_ucOffset++;
		memcpy(&V_ucDerictBuff[V_ucOffset],&SourceAddr[7],7);
		V_ucOffset +=7;
	}
	if(V_ucOffset <= *pv_usDerictLen)
	{
		*pv_usDerictLen = V_ucOffset;
		memcpy(DerictAddr,V_ucDerictBuff,V_ucOffset);		
		V_ucReturnValue = C_Code_OK;
	}
	return V_ucReturnValue;
}

/***********************************************************************
Function: PF_RecordTimeStaid7_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
Description:时间状态编码
Input:     uchar8 *SourceAddr,				源数据
			ushort16 *pv_usSourceLen,		源数据长度
			uchar8 *DerictAddr,				目标缓存
			ushort16 *pv_usDerictLen		目标缓存长度
Output:		ushort16 *pv_usDerictLen 		编码后数据实际长度
return：C_Code_OK:执行成功 C_Code_OverStep：提供缓存不足
Others:	    
                                                  
Author:
全局变量：						      
注意点：                          
**********************************************************************/
uchar8  PF_RecordTimeStaid7_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
{
	uchar8 V_ucReturnValue=C_Code_OverStep;
	ushort16 V_usOffset;
	ushort16 V_usMaxLenbuf;	 	
	
	DerictAddr[0] = C_structure;
	DerictAddr[1] = 2;
	DerictAddr[2] = C_null;
	V_usOffset = 3;
	V_usMaxLenbuf = (*pv_usDerictLen)-V_usOffset;
	V_ucReturnValue = PF_RecordTimeStaBottom_Coding_To_698(&SourceAddr[0],C_Null_Ptr,&DerictAddr[V_usOffset],&V_usMaxLenbuf);
	if(V_ucReturnValue == C_Code_OK)
	{
		*pv_usDerictLen = V_usOffset + V_usMaxLenbuf;
	}	
	return V_ucReturnValue;
}



/***********************************************************************
Function: PF_F30005_1_Coding_To_698
Description:显示列表内部编码到698编码处理函数
Input:     uchar8 *SourceAddr,				源数据
			ushort16 *pv_usSourceLen,		源数据长度
			uchar8 *DerictAddr,				目标缓存
			ushort16 *pv_usDerictLen		目标缓存长度
Output:		ushort16 *pv_usDerictLen 		编码后数据实际长度
return：C_Code_OK:执行成功 C_Code_OverStep：提供缓存不足
Others:	    
                                                  
Author:
全局变量：						      
注意点：                          
**********************************************************************/
uchar8  PF_F30005_1_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
{
	uchar8 V_ucReturnValue=C_Code_OverStep;
	
	if(*pv_usSourceLen == 11)
	{
		
		DerictAddr[0] = 0x02;/*结构体*/
		DerictAddr[1] = 0x03;/*元素个数为2*/
		DerictAddr[2] = C_CSD;
		if(0xFFFFFFFF == PF_Buffer4ToUlong32_698(&SourceAddr[4]))
		{
			if(*pv_usDerictLen >=13)
			{			
				DerictAddr[3] = 0x00;				/*OAD*/
				memcpy(&DerictAddr[4],&SourceAddr[0],4); /*再取数据*/
				DerictAddr[8] = C_unsigned;			
				DerictAddr[9] = SourceAddr[8];
				DerictAddr[10] = C_long_unsigned;			
				DerictAddr[11] = SourceAddr[9];
				DerictAddr[12] = SourceAddr[10];				
				*pv_usDerictLen = 13;
				V_ucReturnValue = C_Code_OK;
			}
		}
		else
		{
			if(*pv_usDerictLen >=18)
			{
				DerictAddr[3] = 0x01;		/*ROAD*/
				memcpy(&DerictAddr[4],&SourceAddr[0],4);
				DerictAddr[8] = 0x01;		/*OAD*/
				memcpy(&DerictAddr[9],&SourceAddr[4],4);
				DerictAddr[13] = C_unsigned;
				DerictAddr[14] = SourceAddr[8];	
				DerictAddr[15] = C_long_unsigned;			
				DerictAddr[16] = SourceAddr[9];
				DerictAddr[17] = SourceAddr[10];
				*pv_usDerictLen = 18;
				V_ucReturnValue = C_Code_OK;
			}			
		}		
	}
	return V_ucReturnValue;
}
/***********************************************************************
Function: uchar8  PF_CSD_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
Description:显示列表内部编码到698编码处理函数
Input:     uchar8 *SourceAddr,				源数据
			ushort16 *pv_usSourceLen,		源数据长度
			uchar8 *DerictAddr,				目标缓存
			ushort16 *pv_usDerictLen		目标缓存长度
Output:		ushort16 *pv_usDerictLen 		编码后数据实际长度
return：C_Code_OK:执行成功 C_Code_OverStep：提供缓存不足
Others:	    
                                                  
Author:
全局变量：						      
注意点：                          
**********************************************************************/
uchar8  PF_CSD_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
{
	uchar8 V_ucReturnValue=C_Code_OverStep;
	
	if(*pv_usSourceLen == 9)
	{
		
		DerictAddr[0] = 0x02;/*结构体*/
		DerictAddr[1] = 0x02;/*元素个数为2*/
		DerictAddr[2] = C_CSD;
		if(0xFFFFFFFF == PF_Buffer4ToUlong32_698(&SourceAddr[4]))
		{
			if(*pv_usDerictLen >=10)
			{			
				DerictAddr[3] = 0x00;				/*OAD*/
				memcpy(&DerictAddr[4],&SourceAddr[0],4); /*再取数据*/
				DerictAddr[8] = C_unsigned;			
				DerictAddr[9] = SourceAddr[8];
				*pv_usDerictLen = 10;
				V_ucReturnValue = C_Code_OK;
			}
		}
		else
		{
			if(*pv_usDerictLen >=15)
			{
				DerictAddr[3] = 0x01;		/*ROAD*/
				memcpy(&DerictAddr[4],&SourceAddr[0],4);
				DerictAddr[8] = 0x01;		/*OAD*/
				memcpy(&DerictAddr[9],&SourceAddr[4],4);
				DerictAddr[13] = C_unsigned;
				DerictAddr[14] = SourceAddr[8];	
				*pv_usDerictLen = 15;
				V_ucReturnValue = C_Code_OK;
			}			
		}		
	}
	return V_ucReturnValue;
}
/***********************************************************************
Function: uchar8 PF_CSDArray_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
Description:显示列表内部编码到698编码处理函数
Input:     uchar8 *SourceAddr,				源数据
			ushort16 *pv_usSourceLen,		源数据长度
			uchar8 *DerictAddr,				目标缓存
			ushort16 *pv_usDerictLen		目标缓存长度
Output:		ushort16 *pv_usDerictLen 		编码后数据实际长度
return：C_Code_OK:执行成功 C_Code_OverStep：提供缓存不足
Others:	    
                                                  
Author:
全局变量：						      
注意点：                          
**********************************************************************/
uchar8 PF_CSDArray_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
{
	uchar8 V_ucReturnValue=C_Code_OverStep;
	uchar8 i,V_ucNum;
	ushort16 V_usOffset;
	ushort16 V_usDerictLenBuf = *pv_usDerictLen;
	ushort16 V_usSourceLenBuf = 9;
	
	V_ucNum = (uchar8)(*pv_usSourceLen/9);
	if(V_ucNum <= 99)
	{
		DerictAddr[0]=1;		/*数组*/
		DerictAddr[1]=V_ucNum;	/*元素个数*/
		V_usOffset =2;
		for(i=0;i<V_ucNum;i++)
		{
			V_ucReturnValue = PF_CSD_Coding_To_698(&SourceAddr[9*i],&V_usSourceLenBuf,&DerictAddr[V_usOffset],&V_usDerictLenBuf);
			if(C_Code_OK == V_ucReturnValue)
			{
				V_usOffset += V_usDerictLenBuf;
				V_usDerictLenBuf = *pv_usDerictLen - V_usOffset;
			}
			else
			{
				break;
			}			
		}
		if(C_Code_OK == V_ucReturnValue)
		{
			*pv_usDerictLen = V_usOffset;
		}
	}
	return V_ucReturnValue;
}


/***********************************************************************
Function: uchar8 PF_C_CodeID_F30202_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
Description:图像显示内部编码到698编码处理函数
Input:     uchar8 *SourceAddr,				源数据
			ushort16 *pv_usSourceLen,		源数据长度
			uchar8 *DerictAddr,				目标缓存
			ushort16 *pv_usDerictLen		目标缓存长度
Output:		ushort16 *pv_usDerictLen 		编码后数据实际长度
return：C_Code_OK:执行成功 C_Code_OverStep：提供缓存不足
Others:	    
                                                  
Author:
全局变量：						      
注意点：                          
**********************************************************************/
uchar8 PF_C_CodeID_F30202_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
{
    ushort16 V_RowDotNum,V_ColumnDotNum;        
    ushort16 V_usOffset=0,V_DataInOffset=0;
    uchar8 V_BitToCharSize,i;
    uchar8 V_ucReturnValue=C_Code_OverStep;
    
    V_RowDotNum = PF_Buffer2ToLong16_698(&SourceAddr[4]);/*行像素数*/
    V_ColumnDotNum = PF_Buffer2ToLong16_698(&SourceAddr[6]);/*列像素数*/
    
    V_BitToCharSize = (V_RowDotNum-1)/8+1;
    
    DerictAddr[V_usOffset++]=0x01;
    DerictAddr[V_usOffset++]=0x01;
    DerictAddr[V_usOffset++]=0x02;
    DerictAddr[V_usOffset++]=0x06;
    
    for(i=0;i<4;i++)
    {
        DerictAddr[V_usOffset++]=0x12;
        DerictAddr[V_usOffset++]=SourceAddr[V_DataInOffset++];
        DerictAddr[V_usOffset++]=SourceAddr[V_DataInOffset++];
    }
    
    DerictAddr[V_usOffset++]=0x01;
    DerictAddr[V_usOffset++]=(uchar8)V_ColumnDotNum;
    
    for(i=0;i<((uchar8)V_ColumnDotNum);i++)
    {
        DerictAddr[V_usOffset++]=0x04;
        DerictAddr[V_usOffset++]=V_RowDotNum;
        memcpy(&DerictAddr[V_usOffset],&SourceAddr[V_DataInOffset],V_BitToCharSize);
        V_usOffset += V_BitToCharSize;
        V_DataInOffset += V_BitToCharSize;
    }
    
    DerictAddr[V_usOffset++]=0x16;
    DerictAddr[V_usOffset++]=SourceAddr[V_DataInOffset++];
    
    if(*pv_usDerictLen > V_usOffset)
    {
        *pv_usDerictLen = V_usOffset;
        V_ucReturnValue = C_Code_OK;
    }
    return V_ucReturnValue;
}
/***********************************************************************
Function: uchar8 PF_C_CodeID_F20B05_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
Description:蓝牙连接信息内部编码到698编码处理函数
Input:     uchar8 *SourceAddr,				源数据
			ushort16 *pv_usSourceLen,		源数据长度
			uchar8 *DerictAddr,				目标缓存
			ushort16 *pv_usDerictLen		目标缓存长度
Output:		ushort16 *pv_usDerictLen 		编码后数据实际长度
return：C_Code_OK:执行成功 C_Code_OverStep：提供缓存不足
Others:	    
                                                  
Author:
全局变量：						      
注意点：                          
**********************************************************************/
uchar8 PF_C_CodeID_F20B05_Coding_To_698(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
{
      ushort16 V_DataInOffset=0,V_DataOffset=0;
      uchar8 V_DataBuff[6]={0};
      uchar8 i;
      uchar8 V_ConnectFlag=0,V_MaseterNum=0,V_SlaveNum=0;
      uchar8 V_ucReturnValue=C_Code_OverStep;
      
//      DerictAddr[V_DataOffset++]=0x01;
//      DerictAddr[V_DataOffset++]=0x01;
      
      DerictAddr[V_DataOffset++]=0x02;
      DerictAddr[V_DataOffset++]=0x03;
      
      DerictAddr[V_DataOffset++]=0x51;
      /*端口号*/
      memcpy(&DerictAddr[V_DataOffset],&SourceAddr[V_DataInOffset],4);
      V_DataOffset+=4;
      V_DataInOffset+=4;
      
      for(i=0;i<5;i++)
      {
          if(PF_Campare_Data(&SourceAddr[V_DataInOffset+16+i*22],V_DataBuff,6)!=C_Equal)
          {
              V_ConnectFlag |= (1<<i);
          }      
      }
      
      if(V_ConnectFlag&0x03)
      {
          DerictAddr[V_DataOffset++]=0x01;
          
          for(i=0;i<2;i++)
          {
              if(V_ConnectFlag&(1<<i))   
              {
                  V_MaseterNum++;
              }
          }
          
          DerictAddr[V_DataOffset++]=V_MaseterNum;
          
          
          for(i=0;i<2;i++)
          {
            if(V_ConnectFlag&(1<<i))
            {
                DerictAddr[V_DataOffset++]=0x02;
                DerictAddr[V_DataOffset++]=0x02;
                DerictAddr[V_DataOffset++]=0x0A;
                DerictAddr[V_DataOffset++]=0x10;
                memcpy(&DerictAddr[V_DataOffset],&SourceAddr[V_DataInOffset+i*22],16);
                V_DataOffset += 16;
                
                DerictAddr[V_DataOffset++]=0x09;
                DerictAddr[V_DataOffset++]=0x06;
                memcpy(&DerictAddr[V_DataOffset],&SourceAddr[V_DataInOffset+i*22 +16],6);                
                
                V_DataOffset += 6;
            }
          }               
      }
      else
      {
          DerictAddr[V_DataOffset++]=0x00;
      }
      
      if(V_ConnectFlag&0x1C)
      {
          DerictAddr[V_DataOffset++]=0x01;
          
          for(i=2;i<5;i++)
          {
              if(V_ConnectFlag&(1<<i))   
              {
                  V_SlaveNum++;
              }
          }
          
          DerictAddr[V_DataOffset++]=V_SlaveNum;
          
          
          for(i=2;i<5;i++)
          {
            if(V_ConnectFlag&(1<<i))
            {
                DerictAddr[V_DataOffset++]=0x02;
                DerictAddr[V_DataOffset++]=0x02;
                
                DerictAddr[V_DataOffset++]=0x0A;
                DerictAddr[V_DataOffset++]=0x10;
                memcpy(&DerictAddr[V_DataOffset],&SourceAddr[V_DataInOffset+i*22],16);
                V_DataOffset += 16;
                
                DerictAddr[V_DataOffset++]=0x09;
                DerictAddr[V_DataOffset++]=0x06;
                memcpy(&DerictAddr[V_DataOffset],&SourceAddr[V_DataInOffset+i*22 +16],6);                
                
                V_DataOffset += 6;
            }
          }          
      }
      else
      {
          DerictAddr[V_DataOffset++]=0x00;
      }
      
      if(*pv_usDerictLen > V_DataOffset)
      {
          *pv_usDerictLen = V_DataOffset;
          V_ucReturnValue = C_Code_OK;
      }
      return V_ucReturnValue;
}
/***********************************************************************
Function: uchar8 PF_Init_Code698_Level_T
Description:初始化编码线性结构体
Input:     Code_Code698_Level_T *pstr_Code698_Level,
Output:		Code_Code698_Level_T *pstr_Code698_Level,
return：
Others:	    
typedef struct
{ 	    
    uchar8 LevelNum;					编码嵌套等级
    uchar8  CodeID_HighLevel[12];  		高嵌套级的698编码值
    uchar8 CodeID_Bottom_Num;			最底层数据分项个数
    ushort16 Len_Of_Bottom698Data[16];	最底层数据分项数据长度遍历
    ushort16 Len_Of_BottomCode[16];    	最底层数据分项698编码长度遍历 
    uchar8 Data_Of_BottomCode[64];		最底层数据分项698编码遍历  
}Code_Code698_Level_T;                                                   
Author:
全局变量：						      
注意点：                          
**********************************************************************/
void PF_Init_Code698_Level_T(Code_Code698_Level_T *pstr_Code698_Level)
{
	pstr_Code698_Level->LevelNum = 0;
	pstr_Code698_Level->CodeID_HighLevel[0] = 0;
	pstr_Code698_Level->CodeID_Bottom_Num = 1;
	pstr_Code698_Level->Len_Of_Bottom698Data[0] = 0;
	pstr_Code698_Level->Len_Of_BottomCode[0] = 2;
	pstr_Code698_Level->Data_Of_BottomCode[0] = C_array;
	pstr_Code698_Level->Data_Of_BottomCode[1] = C_null;
}

/***********************************************************************
Function: PF_Is_date_time_s_Null
Description:判断1
Input:     Code_Code698_Level_T *pstr_Code698_Level,
Output:		Code_Code698_Level_T *pstr_Code698_Level,
return：
Others:	    
typedef struct
{ 	    
    uchar8 LevelNum;					编码嵌套等级
    uchar8  CodeID_HighLevel[12];  		高嵌套级的698编码值
    uchar8 CodeID_Bottom_Num;			最底层数据分项个数
    ushort16 Len_Of_Bottom698Data[16];	最底层数据分项数据长度遍历
    ushort16 Len_Of_BottomCode[16];    	最底层数据分项698编码长度遍历 
    uchar8 Data_Of_BottomCode[64];		最底层数据分项698编码遍历  
}Code_Code698_Level_T;                                                   
Author:
全局变量：						      
注意点：                          
**********************************************************************/
uchar8 PF_Is_date_time_s_Null(uchar8 V_uc698CodeID,uchar8 *pDataIn)
{
	uchar8 V_ReturnValue = C_Flase;
	
	if(V_uc698CodeID == C_date_time_s)
	{
		V_ReturnValue = PF_Is_ArrayBuff_Value(pDataIn,0x00,7);				
	}	
	return V_ReturnValue;
}
///***********************************************************************
//Function: ushort16 PF_Get_Code698S_And_Data_Len(uchar8 *pV_ucDataBuf)
//Description:获取基本类型数据长度
//Input	:pV_ucDataBuf指向数据类型所在buffer地址
//Output:无
//return:数据长度，包括698编码
//Others:
//Author:
//Global Variable:
//Tips：
//**********************************************************************/
ushort16 PF_Get_Code698S_And_Data_Len(uchar8 *pV_ucDataBuf)
{
	ushort16 V_ucDataLen=0; 
	
	V_ucDataLen = PF_Get_Code698_And_Data_Len(pV_ucDataBuf[0]);
	if(V_ucDataLen == 0)
	{
		if(pV_ucDataBuf[0] == 0x5B)	//CSD数据类型
		{
			if(pV_ucDataBuf[1] == 0x00)	//OAD
			{
				V_ucDataLen = 6;
			}
			else if(pV_ucDataBuf[1] == 0x01)	//ROAD
			{
				V_ucDataLen = pV_ucDataBuf[6];	//去OAD个数
				V_ucDataLen *= 4;				//乘以OAD长度
				V_ucDataLen += 7;				//加上类型、记录OAD及关联OAD的个数的字节数
			}
			else 
			{
				//不需要进行处理
			}
		}
	}
	return V_ucDataLen;
}
///***********************************************************************
//Function: uchar8 PF_Get_698Encoded_DataAndLen(ushort16 *pV_usDataLen,uchar8 *pV_ucADPUBuf,uchar8 *pV_ucData,ushort16 *pV_usADPUDeal_Len)
//Description:获取698编码格式数据长度及数据
//Input	:pV_ucADPUBuf指向APDU数据首地址,pV_usDataLen指向存放数据长度缓存地址，pV_ucData指向存放纯数据缓存地址
//		pV_usADPUDeal_Len指向存放处理过的APDU长度缓存地址
//Output:*pV_usDataLen指向存放数据长度，*pV_ucData指向存放纯数据*
//		*pV_usADPUDeal_Len指向存放处理过的APDU长度*
//return:	返回数据长度，0表示数据类型不合法
//Others:
//Author:
//Global Variable:
//Tips：
//**********************************************************************/
uchar8 PF_Get_698Encoded_DataAndLen(ushort16 *pV_usDataLen,uchar8 *pV_ucADPUBuf,uchar8 *pV_ucData,ushort16 *pV_usADPUDeal_Len)
{
	uchar8 V_ucReturnFlag = C_OK;
	uchar8 V_ucBasicDataLen;
	
	V_ucBasicDataLen = PF_Get_Code698S_And_Data_Len(&pV_ucADPUBuf[0]);
	if(V_ucBasicDataLen == 0) 	//复杂类型
	{
		*pV_usDataLen = PF_Get_ComplexDataLen_Data(&pV_ucADPUBuf[0],pV_ucData,pV_usADPUDeal_Len);
		/*if(*pV_usDataLen == 0)
		{
			V_ucReturnFlag = C_ServerError_DAR;		//APDU异常，直接异常应答
		}*/
	}
	else		//简单类型
	{
		*pV_usADPUDeal_Len = V_ucBasicDataLen;
		*pV_usDataLen = V_ucBasicDataLen - 1;
		memcpy(pV_ucData,&pV_ucADPUBuf[1],*pV_usDataLen);		//将数据复制到制定buffer
	}
	return V_ucReturnFlag;
}

///***********************************************************************
//Function: ushort16 PF_Get_ComplexDataLen_Data(u0char8 *pV_ucADPUBuf,uchar8 *pV_ucData,ushort16 *pV_usADPUDeal_Len)
//Description:获取698编码格式数据，数据长度及APDU总长度
//Input	:pV_ucADPUBuf指向APDU数据首地址,pV_ucData纯数据首地址，pV_usADPUDeal_Len为APDU长度，
//Output:*pV_ucData纯数据，*pV_usADPUDeal_Len为处理的APDU的长度
//return:	返回数据长度,不包含数据类型，0表示数据类型不合法
//Others:
//Author:
//Global Variable:
//Tips：
//**********************************************************************/
ushort16 PF_Get_ComplexDataLen_Data(uchar8 *pV_ucADPUBuf,uchar8 *pV_ucData,ushort16 *pV_usADPUDeal_Len)
{
	uchar8 i;
	ushort16 V_FieldLen,V_usOff = 0,V_Temp1,V_Len,V_No,V_No2,V_No3,V_No4;
	*pV_usADPUDeal_Len = 0;

	switch(pV_ucADPUBuf[0])
	{
		case C_array:
		case C_structure:
		{
			(*pV_usADPUDeal_Len) = 1;
			(*pV_usADPUDeal_Len) += PF_Decode_LenOffset(&pV_ucADPUBuf[*pV_usADPUDeal_Len],&V_No);	//取数组个数
			for(i=0;i<V_No;i++)
			{
				V_Temp1 = PF_Get_Code698S_And_Data_Len(&pV_ucADPUBuf[*pV_usADPUDeal_Len]);
				if(V_Temp1 != 0)
				{
//					memcpy(&pV_ucData[*pV_usADPUDeal_Len],&pV_ucADPUBuf[*pV_usADPUDeal_Len+1],V_Temp1-1);
//					(*pV_usADPUDeal_Len) += V_Temp1;
//					V_usOff += (V_Temp1-1);
					PF_Save_ComplexDataLen_Data(pV_ucADPUBuf,pV_ucData,pV_usADPUDeal_Len,&V_usOff,V_Temp1);
				}
				else  if((pV_ucADPUBuf[*pV_usADPUDeal_Len] == C_array)||(pV_ucADPUBuf[*pV_usADPUDeal_Len] == C_structure))	//说明是结构体或者数组
				{
					uchar8 i_i;
					(*pV_usADPUDeal_Len)++;
					(*pV_usADPUDeal_Len) += PF_Decode_LenOffset(&pV_ucADPUBuf[*pV_usADPUDeal_Len],&V_No2);	//取数组个数
					for(i_i=0;i_i<V_No2;i_i++)
					{
						V_Temp1 = PF_Get_Code698S_And_Data_Len(&pV_ucADPUBuf[*pV_usADPUDeal_Len]);
						if(V_Temp1 != 0)
						{
//							memcpy(&pV_ucData[V_usOff],&pV_ucADPUBuf[*pV_usADPUDeal_Len+1],V_Temp1-1);
//							(*pV_usADPUDeal_Len)+= V_Temp1;
//							V_usOff += (V_Temp1-1);
							PF_Save_ComplexDataLen_Data(pV_ucADPUBuf,pV_ucData,pV_usADPUDeal_Len,&V_usOff,V_Temp1);
						}
						else if((pV_ucADPUBuf[*pV_usADPUDeal_Len] == C_array)||(pV_ucADPUBuf[*pV_usADPUDeal_Len] == C_structure))	//说明是结构体或者数组
						{
							uchar8 i_ii;
							(*pV_usADPUDeal_Len)++;
							(*pV_usADPUDeal_Len) += PF_Decode_LenOffset(&pV_ucADPUBuf[*pV_usADPUDeal_Len],&V_No3);	//取数组个数
							for(i_ii=0;i_ii<V_No3;i_ii++)
							{
								V_Temp1 = PF_Get_Code698S_And_Data_Len(&pV_ucADPUBuf[*pV_usADPUDeal_Len]);
								if(V_Temp1 != 0)
								{
									PF_Save_ComplexDataLen_Data(pV_ucADPUBuf,pV_ucData,pV_usADPUDeal_Len,&V_usOff,V_Temp1);
								}
								else if((pV_ucADPUBuf[*pV_usADPUDeal_Len] == C_array)||(pV_ucADPUBuf[*pV_usADPUDeal_Len] == C_structure))	//说明是结构体或者数组
								{
									uchar8 i_iii;
									(*pV_usADPUDeal_Len)++;
									(*pV_usADPUDeal_Len) += PF_Decode_LenOffset(&pV_ucADPUBuf[*pV_usADPUDeal_Len],&V_No4);	//取数组个数
									for(i_iii=0;i_iii<V_No4;i_iii++)
									{
										V_Temp1 = PF_Get_Code698S_And_Data_Len(&pV_ucADPUBuf[*pV_usADPUDeal_Len]);
										if(V_Temp1 != 0)
										{
											PF_Save_ComplexDataLen_Data(pV_ucADPUBuf,pV_ucData,pV_usADPUDeal_Len,&V_usOff,V_Temp1);
										}
										else 	///*最多解析4级嵌套*///
										{
											V_usOff = 0;
											break;
										}
									}
								}
								else
								{
									if((pV_ucADPUBuf[*pV_usADPUDeal_Len] == C_octet_string)			//目前数组中包含octet-string类型的数据
									   ||(pV_ucADPUBuf[*pV_usADPUDeal_Len] == C_visible_string))	
									{
										(*pV_usADPUDeal_Len)++;
										V_Temp1 = PF_Decode_LenOffset(&pV_ucADPUBuf[*pV_usADPUDeal_Len],&V_FieldLen);	///*格式：类型+长度+数据*///
										(*pV_usADPUDeal_Len) += V_Temp1;
										memcpy(&pV_ucData[V_usOff],&pV_ucADPUBuf[*pV_usADPUDeal_Len],V_FieldLen);
										(*pV_usADPUDeal_Len) += V_FieldLen;
										V_usOff += V_FieldLen;
									}
									else  if(pV_ucADPUBuf[*pV_usADPUDeal_Len] == C_bit_string)
									{
										(*pV_usADPUDeal_Len)++;
										V_Temp1 = PF_Decode_LenOffset(&pV_ucADPUBuf[*pV_usADPUDeal_Len],&V_FieldLen);	///*格式：类型+长度+数据*///
										(*pV_usADPUDeal_Len) += V_Temp1;
										V_FieldLen = (V_FieldLen-1)/8+1;
										memcpy(&pV_ucData[V_usOff],&pV_ucADPUBuf[*pV_usADPUDeal_Len],V_FieldLen);
										V_usOff += V_FieldLen;
										(*pV_usADPUDeal_Len) += V_FieldLen;
									}
									else
									{
										V_usOff = 0;
									}
								}
							}
						}
						else
						{
							if((pV_ucADPUBuf[*pV_usADPUDeal_Len] == C_octet_string)			//目前数组中包含octet-string类型的数据
							   ||(pV_ucADPUBuf[*pV_usADPUDeal_Len] == C_visible_string))	
							{
								(*pV_usADPUDeal_Len)++;
								V_Temp1 = PF_Decode_LenOffset(&pV_ucADPUBuf[*pV_usADPUDeal_Len],&V_FieldLen);	///*格式：类型+长度+数据*///
								(*pV_usADPUDeal_Len) += V_Temp1;
								memcpy(&pV_ucData[V_usOff],&pV_ucADPUBuf[*pV_usADPUDeal_Len],V_FieldLen);
								(*pV_usADPUDeal_Len) += V_FieldLen;
								V_usOff += V_FieldLen;
							}
							else  if(pV_ucADPUBuf[*pV_usADPUDeal_Len] == C_bit_string)
							{
								(*pV_usADPUDeal_Len)++;
								V_Temp1 = PF_Decode_LenOffset(&pV_ucADPUBuf[*pV_usADPUDeal_Len],&V_FieldLen);	///*格式：类型+长度+数据*///
								(*pV_usADPUDeal_Len) += V_Temp1;
								V_FieldLen = (V_FieldLen-1)/8+1;
								memcpy(&pV_ucData[V_usOff],&pV_ucADPUBuf[*pV_usADPUDeal_Len],V_FieldLen);
                                PF_Mirroring_Bitstring(&pV_ucData[V_usOff],V_FieldLen);
								V_usOff += V_FieldLen;
								(*pV_usADPUDeal_Len) += V_FieldLen;
							}
							else
							{
								V_usOff = 0;
							}
						}
					}
				}
				else
				{
					if((pV_ucADPUBuf[*pV_usADPUDeal_Len] == C_octet_string)			//目前数组中包含octet-string类型的数据
					   ||(pV_ucADPUBuf[*pV_usADPUDeal_Len] == C_visible_string))	
					{
						(*pV_usADPUDeal_Len)++;
						V_Temp1 = PF_Decode_LenOffset(&pV_ucADPUBuf[*pV_usADPUDeal_Len],&V_FieldLen);	///*格式：类型+长度+数据*///
						(*pV_usADPUDeal_Len) += V_Temp1;
						memcpy(&pV_ucData[V_usOff],&pV_ucADPUBuf[*pV_usADPUDeal_Len],V_FieldLen);
						(*pV_usADPUDeal_Len) += V_FieldLen;
						V_usOff += V_FieldLen;
					}
					else  if(pV_ucADPUBuf[*pV_usADPUDeal_Len] == C_bit_string)
					{
						(*pV_usADPUDeal_Len)++;
						V_Temp1 = PF_Decode_LenOffset(&pV_ucADPUBuf[*pV_usADPUDeal_Len],&V_FieldLen);	///*格式：类型+长度+数据*///
						(*pV_usADPUDeal_Len) += V_Temp1;
						V_FieldLen = (V_FieldLen-1)/8+1;
						memcpy(&pV_ucData[V_usOff],&pV_ucADPUBuf[*pV_usADPUDeal_Len],V_FieldLen);
                        PF_Mirroring_Bitstring(&pV_ucData[V_usOff],V_FieldLen);
						V_usOff += V_FieldLen;
						(*pV_usADPUDeal_Len) += V_FieldLen;
					}
					else
					{
						V_usOff = 0;
					}
				}
			}
			V_Len = V_usOff;
		}
		break;
		case C_bit_string:
			(*pV_usADPUDeal_Len)++;
			V_FieldLen=PF_Decode_LenOffset(&pV_ucADPUBuf[*pV_usADPUDeal_Len],&V_Len);	///*格式：类型+长度+数据*///
			V_Temp1=(V_Len-1)/8+1;
			(*pV_usADPUDeal_Len) += V_FieldLen;			
			memcpy(&pV_ucData[V_usOff],&pV_ucADPUBuf[*pV_usADPUDeal_Len],V_Temp1);
            PF_Mirroring_Bitstring(&pV_ucData[V_usOff],V_Temp1);
			(*pV_usADPUDeal_Len) += V_Temp1;
			V_Len = V_Temp1;
		break;
		case C_octet_string:
		case C_visible_string:
		case C_UTF8_string:
			V_usOff=PF_Decode_LenOffset(&pV_ucADPUBuf[1],&V_FieldLen)+1;	///*格式：类型+长度+数据*///
			*pV_usADPUDeal_Len=V_usOff+V_FieldLen;
			memcpy(&pV_ucData[0],&pV_ucADPUBuf[V_usOff],V_FieldLen);
			V_Len = V_FieldLen;
		break;
		case C_ROAD:											///*格式：OAD+Array(OAD)*///
			V_FieldLen=PF_Decode_LenOffset(&pV_ucADPUBuf[4],&V_usOff);
			V_Len=V_usOff*4+(V_FieldLen+4);
		break;
		case C_RCSD:
		{
			if(pV_ucADPUBuf[0])
			{
				V_Len=1;
			}
			else
			{
				if(pV_ucADPUBuf[1] == 0)								///*选择是0AD还是ROAD*///
				{
					V_Len=5;
				}
				else
				{
					V_usOff=PF_Decode_LenOffset(&pV_ucADPUBuf[6],&V_FieldLen);
					V_Len=V_usOff*4+(V_FieldLen+6);
				}
				V_Len=V_Len*(pV_ucADPUBuf[0]);
			}
		}
		break;
		case C_CSD:
			if(pV_ucADPUBuf[0] == 0)								///*选择是0AD还是ROAD*///
			{
				V_Len=5;
			}
			else
			{
				V_usOff=PF_Decode_LenOffset(&pV_ucADPUBuf[5],&V_FieldLen);
				V_Len=V_usOff*4+(V_FieldLen+5);
			}
		break;
		default:

		break;
	}

	return V_Len;
}

/***********************************************************************
Function: uchar8 PF_Decode_LenOffset(uchar8 *pV_Buffer,ushort16 *pV_usDataLen)
Description:获取不定长数据长度及长度所占字节数
Input	:   pV_Buffer长度起始地址，pV_usDataLen数据实际长度地址
Output:	*pV_usDataLen为实际数据长度
return:	长度编码所占字节数,返回字节为0表示数据有误
Others:
Author:
Global Variable:
Tips：
**********************************************************************/
uchar8 PF_Decode_LenOffset(uchar8 *pV_Buffer,ushort16 *pV_usDataLen)
{
	uchar8 V_ucLen = 0;

	*pV_usDataLen = 0;
	if((pV_Buffer[0]&0x80) == 0x80)			//复杂长度编码
	{
		V_ucLen = (pV_Buffer[0]&0x7F);
		if(V_ucLen == 1)					//数据长度为1字节
		{
			*pV_usDataLen = pV_Buffer[1];
			V_ucLen++;
		}
		else if(V_ucLen == 2)				//数据长度为2字节
		{
			*pV_usDataLen = pV_Buffer[1];
			*pV_usDataLen = (*pV_usDataLen)<<8;
			*pV_usDataLen |= pV_Buffer[2];
			V_ucLen++;
		}
		else 	//其他长度情况认为错误，返回长度0，同时数据长度也是0
		{

		}
	}
	else
	{
		*pV_usDataLen = pV_Buffer[0];
		V_ucLen = 1;
	}
	return V_ucLen;
}
///***********************************************************************
//Function: void PF_Save_ComplexDataLen_Data(uchar8 *pV_ucADPUBuf,uchar8 *pV_ucData,ushort16 *pV_usADPUDeal_Len,ushort16 *pV_usOff,ushort16 V_usDataLen)
//Description:保存数据
//Input	:pV_ucADPUBuf指向APDU数据首地址,pV_ucData纯数据首地址，pV_usADPUDeal_Len为APDU长度，
//		pV_usOff为pV_ucData中数据偏移，V_usDataLen为数据长度
//Output:*pV_ucData纯数据，*pV_usADPUDeal_Len为处理的APDU的长度
//return:	返回数据长度,不包含数据类型，0表示数据类型不合法
//Others:
//Author:
//Global Variable:
//Tips：
//**********************************************************************/
void PF_Save_ComplexDataLen_Data(uchar8 *pV_ucADPUBuf,uchar8 *pV_ucData,ushort16 *pV_usADPUDeal_Len,ushort16 *pV_usOff,ushort16 V_usDataLen)
{
	memcpy(&pV_ucData[(*pV_usOff)],&pV_ucADPUBuf[*pV_usADPUDeal_Len+1],V_usDataLen-1);
	if(pV_ucADPUBuf[*pV_usADPUDeal_Len] == C_CSD)	//数据为显示列表
	{
		if(pV_ucADPUBuf[*pV_usADPUDeal_Len+1] == 0x00)
		{
			memcpy(&pV_ucData[(*pV_usOff)],&pV_ucADPUBuf[*pV_usADPUDeal_Len+2],V_usDataLen-2);
			(*pV_usOff) += (V_usDataLen-2);
			memset(&pV_ucData[(*pV_usOff)],0xFF,V_usDataLen-2);
			(*pV_usOff) += (V_usDataLen-2);
		}
		else if(pV_ucADPUBuf[*pV_usADPUDeal_Len+1] == 0x01)
		{
			memcpy(&pV_ucData[(*pV_usOff)],&pV_ucADPUBuf[*pV_usADPUDeal_Len+2],4);
			(*pV_usOff) += 4;
			memcpy(&pV_ucData[(*pV_usOff)],&pV_ucADPUBuf[*pV_usADPUDeal_Len+7],V_usDataLen-7);
			(*pV_usOff) += (V_usDataLen-7);
		}
	}
	else 
	{
		(*pV_usOff) += (V_usDataLen-1);
	}
	(*pV_usADPUDeal_Len) += V_usDataLen;
}

/***********************************************************************
Function: PF_RecordCValue_Coding_To_698_3000(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
Description:事件记录当前值记录表编码
Input:     uchar8 *SourceAddr,				源数据
			ushort16 *pv_usSourceLen,		源数据长度
			uchar8 *DerictAddr,				目标缓存
			ushort16 *pv_usDerictLen		目标缓存长度
Output:		ushort16 *pv_usDerictLen 		编码后数据实际长度
return：C_Code_OK:执行成功 C_Code_OverStep：提供缓存不足
Others:	    
                                                  
Author:
全局变量：						      
注意点：                          
**********************************************************************/
uchar8  PF_RecordCValue_Coding_To_698_3000(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
{
	uchar8 V_ucReturnValue=C_Code_OverStep;
	uchar8 i;
	
	if(*pv_usDerictLen >=39)
	{
		*pv_usDerictLen = 39;
		DerictAddr[0] = C_array;
		DerictAddr[1] = 4;
		DerictAddr[2] = C_null;
		for(i=0;i<3;i++)
		{
			DerictAddr[3+12*i] = C_structure;
			DerictAddr[4+12*i] = 2;
			DerictAddr[5+12*i] = C_double_long_unsigned;
			memcpy(&DerictAddr[6+12*i],&SourceAddr[8+8*i],4);	
			DerictAddr[10+12*i] = C_double_long_unsigned;
			memcpy(&DerictAddr[11+12*i],&SourceAddr[12+8*i],4);						
		}
		V_ucReturnValue = C_Code_OK;	
	}
	
	return V_ucReturnValue;
}

/***********************************************************************
Function: PF_RecordTimeSta_Coding_To_698_3000(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
Description:时间状态编码
Input:     uchar8 *SourceAddr,				源数据
			ushort16 *pv_usSourceLen,		源数据长度
			uchar8 *DerictAddr,				目标缓存
			ushort16 *pv_usDerictLen		目标缓存长度
Output:		ushort16 *pv_usDerictLen 		编码后数据实际长度
return：C_Code_OK:执行成功 C_Code_OverStep：提供缓存不足
Others:	    
                                                  
Author:
全局变量：						      
注意点：                          
**********************************************************************/
uchar8  PF_RecordTimeSta_Coding_To_698_3000(uchar8 *SourceAddr,ushort16 *pv_usSourceLen,uchar8 *DerictAddr,ushort16 *pv_usDerictLen)
{
	uchar8 V_ucReturnValue=C_Code_OverStep;
	ushort16 V_usMaxLenbuf;	 	
	uchar8 i;
	ushort16 V_usOffset;
	
	DerictAddr[0] = C_array;
	DerictAddr[1] = 4;
	DerictAddr[2] = C_null;
	V_usOffset = 3;			
	
	for(i=0;i<3;i++)
	{
		V_usMaxLenbuf = (*pv_usDerictLen)-V_usOffset;
		V_ucReturnValue = PF_RecordTimeStaBottom_Coding_To_698(&SourceAddr[14+14*i],C_Null_Ptr,&DerictAddr[V_usOffset],&V_usMaxLenbuf);
		if(V_ucReturnValue != C_Code_OK)
		{
			break;
		}
		V_usOffset	+=	V_usMaxLenbuf;		
	}
	*pv_usDerictLen = V_usOffset;
	return V_ucReturnValue;
}


