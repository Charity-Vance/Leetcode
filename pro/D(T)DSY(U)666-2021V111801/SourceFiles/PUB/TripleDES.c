

///*######################################################################*///
///* 头文件包含  *///
#include "..\SourceFiles\PUB\Include.h"

/*########################################################################################################
3DES使用说明：
	为了和南网复旦微程序一至，在编写该程序时，对部分标准部件做了修改。
	1. S盒和S盒的算法：S盒标准的是一个4行16列的表格，但是复旦微做成了一个64字节的数组，另外算法方面
	   原标准算法是取数据两段的各一位组成查盒子的行，中间4位查盒子的列，复旦微的算法则是直接用6位数
	   据查64字节的数组。
	2. IP-1置换算法。复旦微将该算法的表格做了修改，具体如下：
		40	8	48	16	56	24	64	32
		39	7	47	15	55	23	63	31
		38	6	46	14	54	22	62	30
		37	5	45	13	53	21	61	29
		36	4	44	12	52	20	60	28
		35	3	43	11	51	19	59	27
		34	2	42	10	50	18	58	26
		33	1	41	9	49	17	57	25 
		此为标准IP-1置换表，复旦微修改后变成
		8	40	16	48	24	56	32	64
		7	39	15	47	23	55	31	63
		6	38	14	46	22	54	30	62
		5	37	13	45	21	53	29	61
		4	36	12	44	20	52	28	60
		3	35	11	43	19	51	27	59
		2	34	10	42	18	50	26	58
		1	33	9	41	17	49	25	57
	3. 虽然做了上述的修改，但是加密结果和标准的3DES结果是一致的
########################################################################################################*/

///*######################################################################*///
///* 函数声明 *///
void DES_PC_1(uchar8 *P_ucSorceData);
void DES_IP(uchar8 *P_ucSorceData);
uchar8 DES_ReplaceMent(uchar8 *P_ucSData,uchar8 V_ucRepMode);
void DES_Transposition(uchar8 *P_ucSorceData, uchar8 *P_ucLocattion, uchar8 *P_ucValue, uchar8	V_ucOutLen);
void DES_CycLRShifting(uchar8 *P_ucData, uchar8 V_ucMode);
void DES_IP_1(uchar8 *P_ucSorceData);
void DES_F(uchar8 *P_ucData, uchar8 *P_Key);
uchar8 Data_MAC( uchar8 *P_ucData, uchar8 V_ucLen, uchar8 *P_ucRand, uchar8 V_ucType );
uchar8 TripleDES_DeOrEncryption(uchar8 V_ucKeyNum, uchar8 *P_ucData, uchar8 V_ucLen);

uchar8 Data_MAC( uchar8 *P_ucData, uchar8 V_ucLen, uchar8 *P_ucRand, uchar8 V_ucType );



///* 函数声明结束 *///
/* 加密算法相关表格 */
///*######################################################################*///
// PC_1密钥置换表格
const	uchar8	code	GT_ucPC_1Location[56]={
	7,	6,	5,	4,	3,	2,	1,	0,
	7,	6,	5,	4,	3,	2,	1,	0,
	7,	6,	5,	4,	3,	2,	1,	0,
	7,	6,	5,	4,	7,	6,	5,	4,
	3,	2,	1,	0,	7,	6,	5,	4,
	3,	2,	1,	0,	7,	6,	5,	4,
	3,	2,	1,	0,	3,	2,	1,	0
};

const	uchar8	code	GT_ucPC_1Value[56]={
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 
	0x10, 0x10, 0x10, 0x10, 0x02, 0x02, 0x02, 0x02, 
	0x02, 0x02, 0x02, 0x02, 0x04, 0x04, 0x04, 0x04,
	0x04, 0x04, 0x04, 0x04,	0x08, 0x08, 0x08, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x10, 0x10, 0x10, 0x10
};	
// PC2:将56位输入压缩置换成48为输出
const	uchar8	code	GT_ucPC_2Location[48]={
	1,	2,	1,	2,	0,	0,	0,	3,
	1,	0,	2,	1, 	2, 	2,	1,	0,
	3,	0,	1,	0, 	3, 	2,	1,	0,
	5,	6,	3,	4, 	5, 	6,	3,	4,
	6,	5,	4,	5, 	5, 	6,	4,	6,
	4,	6,	5,	5, 	6, 	4,	3,	3
};
const	uchar8	code	GT_ucPC_2Value[48]={
	0x04, 0x80, 0x20, 0x01, 0x80 , 0x08, 0x20, 0x10,
	0x02, 0x04, 0x08, 0x40, 0x02 , 0x20, 0x10, 0x10,
	0x40, 0x01, 0x01, 0x02, 0x20 , 0x10, 0x08, 0x40,
	0x80, 0x10, 0x02, 0x08, 0x02 , 0x02, 0x04, 0x01,
	0x20, 0x08, 0x80, 0x01, 0x10 , 0x80, 0x02, 0x01,
	0x40, 0x08, 0x04, 0x40, 0x40 , 0x10, 0x08, 0x01
};
/*循环左/右移*/
const	uchar8	code	GT_ucShiftTable[16] = {
	1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
};

// E盒 将32输入扩展为48位输出
const uchar8 code GT_ucEBoxValue[]={
	0x01,	0x80,	0x40,	0x20,	0x10,	0x08,	0x10,	0x08,
	0x04,	0x02,	0x01,	0x80,	0x01,	0x80,	0x40,	0x20,
	0x10,	0x08,	0x10,	0x08,	0x04,	0x02,	0x01,	0x80,
	0x01,	0x80,	0x40,	0x20,	0x10,	0x08,	0x10,	0x08,
	0x04,	0x02,	0x01,	0x80,	0x01,	0x80,	0x40,	0x20,
	0x10,	0x08,	0x10,	0x08,	0x04,	0x02,	0x01,	0x80
};
const uchar8 code GT_ucEBoxLocation[]={
	3,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	1,	0,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	2,
	1,	2,	2,	2,	2,	2,	2,	2,
	2,	2,	2,	3,	2,	3,	3,	3,
	3,	3,	3,	3,	3,	3,	3,	0
};
// P盒 将32输入置换成32为输出
const uchar8 code GT_ucPBoxValue[]={
	0x01,	0x02,	0x10,	0x08,	0x08,	0x10,	0x10,	0x80,
	0x80,	0x02,	0x02,	0x40,	0x08,	0x40,	0x02,	0x40,
	0x40,	0x01,	0x01,	0x04,	0x01,	0x20,	0x20,	0x80,
	0x20,	0x08,	0x04,	0x04,	0x04,	0x20,	0x10,	0x80,
};
const uchar8 code GT_ucPBoxLocation[]={
	1,	0,	2,	2,	3,	1,	3,	2,
	0,	1,	2,	3,	0,	2,	3,	1,
	0,	0,	2,	1,	3,	3,	0,	1,
	2,	1,	3,	0,	2,	1,	0,	3,
};
/* S盒 */
/* 复旦微的S盒 */
const uchar8 code GT_ucSBox[8][64]={
	/* S1 */
	{	0xe0,0x00,0x40,0xf0,0xd0,0x70,0x10,0x40,
		0x20,0xe0,0xf0,0x20,0xb0,0xd0,0x80,0x10,
		0x30,0xa0,0xa0,0x60,0x60,0xc0,0xc0,0xb0,
		0x50,0x90,0x90,0x50,0x00,0x30,0x70,0x80,
		0x40,0xf0,0x10,0xc0,0xe0,0x80,0x80,0x20,
		0xd0,0x40,0x60,0x90,0x20,0x10,0xb0,0x70,
		0xf0,0x50,0xc0,0xb0,0x90,0x30,0x70,0xe0,
		0x30,0xa0,0xa0,0x00,0x50,0x60,0x00,0xd0},
	/* S2 */
	{  15,3,1,13,8,4,14,7,
	   6,15,11,2,3,8,4,14,
	   9,12,7,0,2,1,13,10,
	   12,6,0,9,5,11,10,5,
	   0,13,14,8,7,10,11,1,
	   10,3,4,15,13,4,1,2,
	   5,11,8,6,12,7,6,12,
	   9,0,3,5,2,14,15,9},
	 /* S3 */
	{  0xa0,0xd0,0x00,0x70,0x90,0x00,0xe0,0x90,
	   0x60,0x30,0x30,0x40,0xf0,0x60,0x50,0xa0,
	   0x10,0x20,0xd0,0x80,0xc0,0x50,0x70,0xe0,
	   0xb0,0xc0,0x40,0xb0,0x20,0xf0,0x80,0x10,
	   0xd0,0x10,0x60,0xa0,0x40,0xd0,0x90,0x00,
	   0x80,0x60,0xf0,0x90,0x30,0x80,0x00,0x70,
	   0xb0,0x40,0x10,0xf0,0x20,0xe0,0xc0,0x30,
	   0x50,0xb0,0xa0,0x50,0xe0,0x20,0x70,0xc0},
	 /* S4 */
	{  7,13,13,8,14,11,3,5,
	   0,6,6,15,9,0,10,3,
	   1,4,2,7,8,2,5,12,
	   11,1,12,10,4,14,15,9,
	   10,3,6,15,9,0,0,6,
	   12,10,11,1,7,13,13,8,
	   15,9,1,4,3,5,14,11,
	   5,12,2,7,8,2,4,14 },

	 /* S5 */
   {   0x20,0xe0,0xc0,0xb0,0x40,0x20,0x10,0xc0,
	   0x70,0x40,0xa0,0x70,0xb0,0xd0,0x60,0x10,
	   0x80,0x50,0x50,0x00,0x30,0xf0,0xf0,0xa0,
	   0xd0,0x30,0x00,0x90,0xe0,0x80,0x90,0x60,
	   0x40,0xb0,0x20,0x80,0x10,0xc0,0xb0,0x70,
	   0xa0,0x10,0xd0,0xe0,0x70,0x20,0x80,0xd0,
	   0xf0,0x60,0x90,0xf0,0xc0,0x00,0x50,0x90,
	   0x60,0xa0,0x30,0x40,0x00,0x50,0xe0,0x30},

	 /* S6 */
	{  12,10,1,15,10,4,15,2,
	   9,7,2,12,6,9,8,5,
	   0,6,13,1,3,13,4,14,
	   14,0,7,11,5,3,11,8,
	   9,4,14,3,15,2,5,12,
	   2,9,8,5,12,15,3,10,
	   7,11,0,14,4,1,10,7,
	   1,6,13,0,11,8,6,13},

	 /* S7 */
	{  0x40,0xd0,0xb0,0x00,0x20,0xb0,0xe0,0x70,
	   0xf0,0x40,0x00,0x90,0x80,0x10,0xd0,0xa0,
	   0x30,0xe0,0xc0,0x30,0x90,0x50,0x70,0xc0,
	   0x50,0x20,0xa0,0xf0,0x60,0x80,0x10,0x60,
	   0x10,0x60,0x40,0xb0,0xb0,0xd0,0xd0,0x80,
	   0xc0,0x10,0x30,0x40,0x70,0xa0,0xe0,0x70,
	   0xa0,0x90,0xf0,0x50,0x60,0x00,0x80,0xf0,
	   0x00,0xe0,0x50,0x20,0x90,0x30,0x20,0xc0},

	 /* S8*/ 
	{  13,1,2,15,8,13,4,8,
	   6,10,15,3,11,7,1,4,
	   10,12,9,5,3,6,14,11,
	   5,0,0,14,12,9,7,2,
	   7,2,11,1,4,14,1,7,
	   9,4,12,10,14,8,2,13,
	   0,15,6,12,10,9,13,0,
	   15,3,3,5,5,6,8,11 },   
};


/*----------------< 变量定义 >----------------------------------*/
uchar8      bdata 	GV_bDesRepbit;
uchar8      xdata GA_ucDesTata[8];				    ///* 3des加密数据 *///
uchar8		xdata  GA_ucDesKey[16];					///* 3des加密key *///
uchar8		xdata GA_uc7816CommBuffer[250];			///* 7816通信缓存数据*/// 

/*----------------< 函数声明 >----------------------------------*/
// 私有函数声明
static void DES_PC_1(uchar8 *P_ucSorceData);
static void DES_IP(uchar8 *P_ucSorceData);
static uchar8 DES_ReplaceMent(uchar8 *P_ucSData,uchar8 V_ucRepMode);
static void DES_Transposition(uchar8 *P_ucSorceData, uchar8 *P_ucLocattion, uchar8 *P_ucValue, uchar8	V_ucOutLen);
static void DES_CycLRShifting(uchar8 *P_ucData, uchar8 V_ucMode);
static void DES_IP_1(uchar8 *P_ucSorceData);
static void DES_F(uchar8 *P_ucData, uchar8 *P_Key);
 
// 公有函数声明
uchar8 Data_MAC( uchar8 *P_ucData, uchar8 V_ucLen, uchar8 *P_ucRand, uchar8 V_ucType );
uchar8 TripleDES_DeOrEncryption(uchar8 V_ucKeyNum, uchar8 *P_ucData, uchar8 V_ucLen); 


/*----------------< 函数定义 >----------------------------------*/

///*============================================================================================*///
///* Function:   	DES_ReplaceMent
///* Description:	通用置换函数
///* Calls: 
///* Called By:  	
///* Input:        	需要置换的数据和替换的元素
///* Output:
///* Return:		返回置换后的一字节
///* Others:		不会改变原始数据，只有规律一样的数据才可以调用，例如要置换数组a[8]每个元素的最低位
///*				组成一个字节且a[7]的最低位为新字节的最高位，则可以调用此函数
///*============================================================================================*///
uchar8 DES_ReplaceMent(uchar8 *P_ucSData,uchar8 V_ucRepMode)
{
	uchar8 V_ucCnti,V_ucDesRepbit;
	
	V_ucDesRepbit = 0;
	for(V_ucCnti=8; V_ucCnti>0; V_ucCnti--)
	{
		V_ucDesRepbit <<= 1;
		if( P_ucSData[V_ucCnti-1] & V_ucRepMode )V_ucDesRepbit++;
	}
	
	return(V_ucDesRepbit);
}
///*============================================================================================*///
///* Function:   	DES_IP
///* Description:	数据初始置换函数IP，输入8字节，输出8字节
///* Calls: 
///* Called By:  	
///* Input:        	8字节待置换数据
///* Output:		置换后的8字节数据
///* Return:		none
///* Others:		
///*============================================================================================*///
void DES_IP(uchar8 *P_ucSorceData)
{
	uchar8 V_ucCnti,V_ucTempData;
	uchar8 V_ucTemp[8];
	
	V_ucTempData = 0x40;
	for ( V_ucCnti=0; V_ucCnti<8; V_ucCnti++ )
	{
		if(4==V_ucCnti) V_ucTempData = 0x80;

		V_ucTemp[ V_ucCnti ] = DES_ReplaceMent( P_ucSorceData, V_ucTempData );

		V_ucTempData >>= 2;
	} 
	
	LibPub_MemCopyBytes( &V_ucTemp[0], P_ucSorceData, 8 );
}
///*============================================================================================*///
///* Function:   	DES_PC_1
///* Description:	密钥置换函数PC-1
///* Calls: 
///* Called By:  	
///* Input:        	8字节待置换数据
///* Output:		置换后的8字节数据
///* Return:		none
///* Others:		
///*============================================================================================*///
void DES_PC_1(uchar8 *P_ucSorceData)
{	
	DES_Transposition( P_ucSorceData, &GT_ucPC_1Location[0], &GT_ucPC_1Value[0], 7);
}
///*============================================================================================*///
///* Function:   	DES_Transposition
///* Description:	置换查表
///* Calls: 
///* Called By:  	
///* Input:        	待查表数据，数据位置，位置对应的值，输出数据长度
///* Output:		查表组合后的数据
///* Return:		none
///* Others:		
///*============================================================================================*///
//PC1 :56-->56
//PC2 :56-->48
//EBox:32-->48
//PBox:32-->32
//这里的长度是输出长度
void DES_Transposition(uchar8 *P_ucSorceData, uchar8 *P_ucLocattion, uchar8 *P_ucValue, uchar8	V_ucOutLen)
{
	uchar8 i;
	uchar8  V_ucTemp[8];
	
	GV_bDesRepbit = 0;
	for(i=1; i<(V_ucOutLen*8)+1; i++)
	{
		GV_bDesRepbit <<= 1;
		if( P_ucSorceData[P_ucLocattion[i-1]] & P_ucValue[i-1]) GV_bDesRepbit++;		
		if(( i % 8 )==0)
		{
			V_ucTemp[(i/8)-1] = GV_bDesRepbit;
			GV_bDesRepbit = 0;
		}		
	}
	LibPub_MemCopyBytes(&V_ucTemp[0], P_ucSorceData, V_ucOutLen);	 
}
///*============================================================================================*///
///* Function:   	DES_CycLRShifting
///* Description:	循环移位
///* Calls: 
///* Called By:  	
///* Input:        	要移位的数据(56bit)，移位模式(左移或右移)
///* Output:		移位后的数据
///* Return:		none
///* Others:		将输入的56bti数据分左半部和右半部分别做循环移位运算
///*============================================================================================*///
//循环左移，将56位输入左28位和右28位各循环左移一位
//输入56位7字节，输出56位四字节
void DES_CycLRShifting(uchar8 *P_ucData, uchar8 V_ucMode)
{
	GU_B32_B08_Type V_unTemp32[2];
	
	
	/* 左半部分循环左/右移1位*/
	V_unTemp32[0].B08[0] = P_ucData[0];
	V_unTemp32[0].B08[1] = P_ucData[1];
	V_unTemp32[0].B08[2] = P_ucData[2];
	V_unTemp32[0].B08[3] = (P_ucData[3]&0xf0);
	if(LEFTSHIFT == V_ucMode)
	{
		V_unTemp32[0].B32 <<= 1;
		if(P_ucData[0]&0x80) V_unTemp32[0].B08[3] |= B0001_0000;
	}
	else
	{
		V_unTemp32[0].B32 >>= 1;
		V_unTemp32[0].B08[3] &= 0xf0;
		if(P_ucData[3]&0x10) V_unTemp32[0].B08[0] |= B1000_0000;	
	}
	
	/* 右半部分左/右移一位 */	
	V_unTemp32[1].B08[0] = (P_ucData[3]&0x0f);
	V_unTemp32[1].B08[1] = P_ucData[4];
	V_unTemp32[1].B08[2] = P_ucData[5];
	V_unTemp32[1].B08[3] = P_ucData[6];
	if(LEFTSHIFT == V_ucMode)
	{
		V_unTemp32[1].B32 <<= 1;
		V_unTemp32[1].B08[0] &= 0x0f;
		if(P_ucData[3]&0x08) V_unTemp32[1].B08[3] |= B0000_0001;
	}
	else
	{
		V_unTemp32[1].B32 >>= 1;
		if(P_ucData[6]&0x01) V_unTemp32[1].B08[0] |= B0000_1000;
	}

	/* 两部分再合起来 */
	V_unTemp32[0].B08[3] |= V_unTemp32[1].B08[0] ;
	V_unTemp32[1].B08[0]  = V_unTemp32[1].B08[1] ;
	V_unTemp32[1].B08[1]  = V_unTemp32[1].B08[2] ;
	V_unTemp32[1].B08[2]  = V_unTemp32[1].B08[3] ;

   	LibPub_MemCopyBytes(&V_unTemp32[0].B08[0], P_ucData, 7);
}
///*============================================================================================*///
///* Function:   	DES_IP_1
///* Description:	末置换函数IP-1
///* Calls: 
///* Called By:  	
///* Input:        	待置换的数据
///* Output:		置换后的数据
///* Return:		none
///* Others:		复旦微的IP-1置换和标准3des是不一样的
///*============================================================================================*///
void DES_IP_1(uchar8 *P_ucSorceData)
{
	uchar8 i,n;
	uchar8 V_ucTemp[8];
	WDT_Clr();
	
	n = 0x01;
	
	V_ucTemp[7] = P_ucSorceData[0];
	V_ucTemp[6] = P_ucSorceData[4];
	V_ucTemp[5] = P_ucSorceData[1];
	V_ucTemp[4] = P_ucSorceData[5];
	V_ucTemp[3] = P_ucSorceData[2];
	V_ucTemp[2] = P_ucSorceData[6];
	V_ucTemp[1] = P_ucSorceData[3];
	V_ucTemp[0] = P_ucSorceData[7];
	for(i=0;i<8;i++)
	{
		P_ucSorceData[i] = DES_ReplaceMent(&V_ucTemp[0], n);
		n <<= 1;
	}
	WDT_Clr();
}
///*============================================================================================*///
///* Function:   	DES_F
///* Description:	F函数
///* Calls: 
///* Called By:  	
///* Input:        	32位数据和48位密钥
///* Output:		运算后的数据
///* Return:		none
///* Others:		复旦微的IP-1置换和标准3des是不一样的
///*============================================================================================*///
/**/
void DES_F(uchar8 *P_ucData, uchar8 *P_Key)
{
	uchar8 i;
	uchar8 V_ucTempData[8],V_ucTempSData[4];

	LibPub_MemCopyBytes(P_ucData+4, &V_ucTempData[0], 4);
	/* ① 数据右半部分通过过扩展置换E进行置换32-->48 */
	DES_Transposition(&V_ucTempData[0], &GT_ucEBoxLocation[0], &GT_ucEBoxValue[0], 6);

	/* ② 将上一步置换出来的结果与48位的密钥进行异或运算 */
	for(i=0; i<6; i++)
	{
		V_ucTempData[i] ^= P_Key[i];	
	}

	/* ③ 将上一步得到的结果进行S盒运算，输出32字节 复旦微算法66高低开(每取6位作为输出的高低字节） */
	for(i=0;i<2;i++)
	{
		GV_bDesRepbit = ((V_ucTempData[i*3+0]<<4)&0x3f) |(V_ucTempData[i*3+1]>>4);
		V_ucTempSData[i*2+0] = GT_ucSBox[i*4+0][V_ucTempData[i*3+0]>>2] | GT_ucSBox[i*4+1][GV_bDesRepbit];
		
		GV_bDesRepbit = ((V_ucTempData[i*3+1]<<2)&0x3f) | (V_ucTempData[i*3+2]>>6);
		V_ucTempSData[i*2+1] = GT_ucSBox[i*4+2][GV_bDesRepbit] | GT_ucSBox[i*4+3][V_ucTempData[i*3+2]&0x3f];		
	}
	
	/* ④ 将上一步的运算结果经过P盒置换后得到一个32位的输出 32-->32*/
	DES_Transposition(&V_ucTempSData[0], &GT_ucPBoxLocation[0], &GT_ucPBoxValue[0], 4);
	/* ⑤ P盒置换的结果与左半部分做异或运算，结果再左右两部分交换*/
	for(i=0; i<4; i++)
	{
		GV_bDesRepbit = P_ucData[4+i];
		P_ucData[4+i]   = V_ucTempSData[i]^P_ucData[i];
		P_ucData[i] = GV_bDesRepbit;	
	}

}
///*============================================================================================*///
///* Function:   	DES_DeOrEncryption
///* Description:	加解密des函数
///* Calls: 
///* Called By:  	
///* Input:        	64位数据和64位密钥及加解密模式
///* Output:		加解密后的数据
///* Return:		none
///* Others:		
///*============================================================================================*///
/*32位数据和48位密钥*/
/* V_ucMode；加密还是解密，加密为2，解密为1） */
/* P_ucData：加解密的数据 P_Key：加解密的密码 */
void DES_DeOrEncryption(uchar8 *P_ucData, uchar8 *P_Key, uchar8 V_ucMode)
//void DES_DeOrEncryption(uchar8 V_ucKeyNum, uchar8 *P_ucData, uchar8 V_ucMode)
{
	uchar8 i,j;
	uchar8	V_ucTempBuff[8],V_ucTempKey[8];
		/* 根据密钥编号读取对应的密钥 */

	/* 先暂时存一下密钥 */
	LibPub_MemCopyBytes(P_Key, &V_ucTempKey[0], 8);	
	
	/* ① 数据做初始IP置换 */
	DES_IP(P_ucData);

	/* ② 密钥做PC1置换 */
	DES_PC_1(&V_ucTempKey[0]);


	for(i=0; i<16; i++)
	{
		/* ③ 密钥循环左/右移 */
		for(j=0; j<GT_ucShiftTable[i]; j++)
		{
			if( (DECRYPTION==V_ucMode) && (0 == i) ) break;
			DES_CycLRShifting(&V_ucTempKey[0],V_ucMode);
		} 
		/* ④ PC2密钥压缩置换 */
		LibPub_MemCopyBytes(&V_ucTempKey[0], &V_ucTempBuff[0], 8);

		DES_Transposition(&V_ucTempBuff[0], &GT_ucPC_2Location[0], &GT_ucPC_2Value[0], 6);
		/* ⑤ F函数 */
		DES_F(P_ucData, &V_ucTempBuff[0]);
		WDT_Clr();
	}

 	/* ⑥ IP-1置换 */
	DES_IP_1(P_ucData);
}
///*============================================================================================*///
///* Function:   	TripleDES_DeOrEncryption
///* Description:	3DES加解密函数
///* Calls: 
///* Called By:  	
///* Input:        	密钥编号(根据对应的密钥编号读出对应的密钥)和64位密钥及加解密模式
///* Output:		加解密后的数据
///* Return:		none
///* Others:		
///*============================================================================================*///
uchar8 TripleDES_DeOrEncryption(uchar8 V_ucKeyNum, uchar8 *P_ucData, uchar8 V_ucMode)
{
 	uchar8 V_ucMode1, V_ucMode2; 
		
	/* 根据密钥编号读取对应的密钥 */
    if (C_KeyNumTp!=V_ucKeyNum) ///* 如果不是临时密钥，需要通过密钥号从E2中读取 *///
	{
		if( C_ERR == LibPub_ReadDataFromE2prom(LIB_E2P_SecretKey, 0, &GA_ucDesKey[0]) )
		{
			return(C_ERR);
		}
	} 
	
	/* 选择加解密模式 */  
	if( ENCRYPTION == V_ucMode )
	{
		V_ucMode1 = ENCRYPTION;
		V_ucMode2 = DECRYPTION;
	}
	else
	{
		V_ucMode1 = DECRYPTION;
		V_ucMode2 = ENCRYPTION;
	}
	/* 进行加解密算法 */
	DES_DeOrEncryption(&P_ucData[0], &GA_ucDesKey[0], V_ucMode1);	/* 左密钥 */

	DES_DeOrEncryption(&P_ucData[0], &GA_ucDesKey[8], V_ucMode2);	/* 右密钥 */

	DES_DeOrEncryption(&P_ucData[0], &GA_ucDesKey[0], V_ucMode1);	/* 左密钥 */
	
	return(C_OK);
}


///*============================================================================================*///
///* Function:   	Data_Mac
///* Description:	MAC计算函数，根据传递的参数类型判定是否需要MAC比对
///* Calls: 
///* Called By:  	
///* Input:        	*P_ucDataBuff要计算或比对的数据指针。V_ucLen数据长度，
///*				V_ucType类型0：仅计算MAC；1：计算MAC后还需要比对是否正确
///* Output:		
///* Return:		如果类型是比对MAC，则比对成功则返回C_OK,失败返回C_ERR，如果是仅计算MAC，则返回C_OK
///* Others:		1. 数据长度不要超过100
///*============================================================================================*///
uchar8 Data_MAC( uchar8 *P_ucData, uchar8 V_ucLen, uchar8 *P_ucRand, uchar8 V_ucType )
{
	uchar8 i,j,k;
	uchar8 *P_ucTempBuff;
	
	if ( V_ucLen>100 ) return(C_ERR);						///* 如果数据长度大于100，直接退出 *///
	P_ucTempBuff = GA_uc7816CommBuffer+120;
	
	///* 取4字节随机数后补00000000 */// 
	LibPub_MemCopyBytes ( P_ucRand, &GA_ucDesTata[0], 8);
	if( C_ERR == LibPub_ReadDataFromE2prom(LIB_E2P_SecretKey, 0, &GA_ucDesKey[0]) )
	{ return(C_ERR); }
 
	///* 先把数据缓存一下 *///
 	LibPub_MemCopyBytes (P_ucData, P_ucTempBuff, V_ucLen);
	P_ucTempBuff[V_ucLen] = 0x80;	///* 补齐数据 8000....00*///
	LibPub_MemSetBytes ( P_ucTempBuff+V_ucLen+1, 0x00, 7 );
	j = (V_ucLen/8)+1;
	
	///* D1与初始值异或一下 *///
	for ( k = 0; k < 8; k++ )
	{
		GA_ucDesTata[k] ^= P_ucTempBuff[k];
	}  
	for ( i = 0; i < (j-1); i++ )
	{
		///* 使用5号进行DES加密生成密文 *///
		DES_DeOrEncryption (&GA_ucDesTata[0], &GA_ucDesKey[0], ENCRYPTION);
		for ( k = 0; k < 8; k++ )
		{
			GA_ucDesTata[k] ^= P_ucTempBuff[(i+1)*8+k];	///* 密文与BLOCK2-BLOCKL 异或 *///
		}
	}
 	
	///* 再使用0号密钥对异或后的结果进行一次加密,加密结果的左4字节作为MAC *///
 	TripleDES_DeOrEncryption( C_KeyNum00, &GA_ucDesTata[0], ENCRYPTION);
 
	///* 如果要比对MAC，这里比对一下 *///
	if ( V_ucType==1 )
	{
		if ( C_Equal == LibPub_CompareData ( &GA_ucDesTata[0], P_ucData+V_ucLen, 4,CMP_MODE_HIGHT) )
		{ return(C_OK);  }
		else
		{ return(C_ERR); }
	}
	
	return(C_OK);
}


