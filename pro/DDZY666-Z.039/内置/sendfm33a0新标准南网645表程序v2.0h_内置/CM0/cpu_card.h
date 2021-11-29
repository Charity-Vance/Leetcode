/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/

/*
// <h> USART0
*/
// <h> 7816通道控制寄存器

/*
//    <o.0> 通道弱上拉使能控制位

//       <0=> 弱上拉无效
//       <1=> 弱上拉有效
//    <o.1> 通道强上拉使能控制位

//       <0=> 强上拉无效
//       <1=> 强上拉有效
//    <o.2> 通道数据发送强上拉电阻自动有效控制位

//       <0=> 数据发送时上拉电阻自动有效功能禁止，上拉电阻由HPUEN，LPUEN控制
//       <1=> 数据发送时上拉电阻自动有效，接收态上拉电阻无效
//    <o.3> 时钟CLK输出使能控制位

//       <0=> 时钟输出禁止
//       <1=> 时钟输出使能
//    <o.4> 通道接收使能控制位

//       <0=> 通道接收禁止，不可接收数据，并关断输入端口
//       <1=> 通道接收使能，可接收数据
//    <o.5> 通道发送使能控制位

//       <0=> 通道发送禁止，不可发送数据，并关断输出端口
//       <1=> 通道发送使能，可发送数据
// </h>
*/

#define DEF_USART0CTRL   ((uint32_t)0x00000006U) /*!< */
// <h> 7816帧格式控制寄存器

/*
//    <o.0> 传输次序，编码方式选择

//       <0=> 正向编码，先收发LSB
//       <1=> 反向编码，先收发MSB
//    <o.1> 接收数据奇偶校验错的处理方式选择

//       <0=> 奇偶校验错，不自动发送ERROR SIGNAL
//       <1=> 奇偶校验错，根据T=0协议自动回发ERROR SIGNAL。
//    <o.2> 缓发送数据奇偶校验错的处理方式选择

//       <0=> 收到Error signal时不进行自动回发
//       <1=> 收到奇偶校验出错标志（error signal），根据T＝0协议自动进行回发。
//    <o.3> Guard Time长度控制位（发送时严格按照协议2etu）
//       <0=> Guard time为2 etu
//       <1=> Guard time为1 etu

//    <o.4..5> 奇偶校验类型选择
//       <0=> Even
//       <1=> Odd
//       <2=> Always 1
//       <3=> 不校验处理
//    <o.6> 控制接收数据奇偶校验出错时自动重发次数

//       <0=> 1次
//       <1=> 3次
//    <o.7> BGT（block guard time）控制位。

//       <0=> BGT禁止，不插入Block guard time(22 etu);
//       <1=> BGT使能，插入Block guard time(22 etu);

//    <o.8> ERROR SIGNAL后GUARDTIME宽度选择（仅在发送时有效）

//       <0=> ERROR SIGNAL后GUARDTIME为2~2.5ETU。
//       <1=> ERROR SIGNAL后GUARDTIME为1~1.5ETU。
//    <o.9..10> ERROR SIGNAL宽度选择。

//       <0=> ERROR SIGNAL宽度为2ETU;
//       <1=> ERROR SIGNAL宽度为2ETU;
//       <2=> ERROR SIGNAL宽度为1.5ETU;
//       <3=> ERROR SIGNAL宽度为1ETU;
// </h>
*/

#define DEF_USART0FRC   ((uint32_t)0x00000286U) /*!< */

// <h> 7816 EGT配置寄存器

/*
//    <o.0..7> EGT设置<0-255>
//  <i> 发送时插入的EGT时间（以ETU为单位）
// </h>
*/

#define DEF_USART0EGT   ((uint32_t)0x00000000U) /*!< */
// <h> 7816 工作时钟分频寄存器

/*
//    <o.0..4> 分频设置<0-31>
//  <i> U7816时钟输出分频控制寄存器，控制7816工作时钟分频数。
//  <i> U7816工作时钟与APBCLK的分频关系：
//  <i> F7816=FAPBCLK/(CLKDIV+1)
//  <i> 特殊情况：CLK_DIV设置成0或1时，F7816=FAPBCLK/2
//  <i> 注：7816协议规定的工作时钟范围是1~5MHZ。

// </h>
*/

#define DEF_USART0CLKDIV   ((uint32_t)0x00000001U) /*!< */
// <h> 7816 预分频控制寄存器

/*
//    <o.0..11> 预分频设置<0-4095>
//  <i> U7816预分频控制寄存器，控制7816通信分频比（波特率）
//  <i> Baud ＝ F7816/(PDIV ＋ 1)


// </h>
*/

#define DEF_USART0CLKPDIV   ((uint32_t)0x00000173U) /*!< */
// <h> 7816 中断使能寄存器

/*
//    <q.0> 数据接收中断使能位
//    <q.1> 数据发送中断使能位
//    <q.2> 线路状态中断使能
// </h>
*/

#define DEF_USART0IE   ((uint32_t)0x00000000U) /*!< */

/*
// </h>
*/

//*** <<< end of configuration section >>>    ***

//USART_Type *USART0;

#define DEF_USART0RX_EN       B0001_0000
#define DEF_USART0TX_EN       B0010_0000
#define DEF_USART0CLK_EN      B0000_1000

#define	U7816CTRL0				USART0->U7816CTRL	//7816通道0端口控制寄存器
#define	U7816FRMCTRL0			    	USART0->U7816FRC	//7816帧格式控制寄存器0
#define	U7816EGTCTRL0			    	USART0->U7816EGT	//7816 EGT配置寄存器
#define	U7816CLKDIV0				USART0->U7816CLKDIV	//7816工作时钟分频控制寄存器
#define	U7816PREDIV0				USART0->U7816PDIV	//7816预分频控制寄存器
#define	U7816RXBUF0				USART0->U7816RXBUF	//7816数据接收缓冲寄存器
#define	U7816TXBUF0				USART0->U7816TXBUF	//7816数据发送缓冲寄存器
#define	U7816INTEN0				USART0->U7816IE		//7816中断使能寄存器
#define	U7816PRIMARYSTATUS0			USART0->U7816IF		//7816主状态寄存器
#define	U7816ERRSTATUS0			  	USART0->U7816ERR	//7816错误信息寄存器
#define	U7816SECONDSTATUS0		  	USART0->U7816STA	//7816次状态寄存器

#define	U7816CTRL1				USART1->U7816CTRL	//7816通道0端口控制寄存器
#define	U7816FRMCTRL1			    	USART1->U7816FRC	//7816帧格式控制寄存器0
#define	U7816EGTCTRL1			    	USART1->U7816EGT	//7816 EGT配置寄存器
#define	U7816CLKDIV1				USART1->U7816CLKDIV	//7816工作时钟分频控制寄存器
#define	U7816PREDIV1				USART1->U7816PDIV	//7816预分频控制寄存器
#define	U7816RXBUF1				USART1->U7816RXBUF	//7816数据接收缓冲寄存器
#define	U7816TXBUF1				USART1->U7816TXBUF	//7816数据发送缓冲寄存器
#define	U7816INTEN1				USART1->U7816IE		//7816中断使能寄存器
#define	U7816PRIMARYSTATUS1			USART1->U7816IF		//7816主状态寄存器
#define	U7816ERRSTATUS1			  	USART1->U7816ERR	//7816错误信息寄存器
#define	U7816SECONDSTATUS1		 	USART1->U7816STA	//7816次状态寄存器

//-------------- CPU ---------------------------
#define		OK_CARD_PROC		0	//卡片操作成功
#define		IC_VLOW_ERR		1	//表计电压过低176V(80%Un)
#define		IC_ESAM_RDWR_ERR	2	//操作ESAM错误
#define		IC_ESAM_RST_ERR		3	//ESAM复位错误
#define		IC_IC_RST_ERR		4	//卡片复位错误:反插卡或插铁片
#define		IC_AUTH_ERR		5	//身份认证错误(通信成功但密文不匹配)
#define		IC_EXAUTH_ERR		6	//外部身份认证错误(通信成功但认证不通过)
#define		IC_NOFX_ERR		7	//未发行的卡片(读卡片时返回6B00)
#define		IC_TYPE_ERR		8	//卡类型错误
#define		IC_KER_ERR		9	//卡片操作未授权：密钥状态不为公钥是插参数预制卡
#define		IC_MAC_ERR		10	//MAC校验错误(6988)
#define		IC_ID_ERR		11	//表号不一致
#define		IC_HUHAO_ERR		12	//客户编号不一致
#define		IC_SERIAL_ERR		13	//卡序号不一致
#define		IC_FORMAT_ERR		14	//卡片文件格式不合法
#define		IC_NOOPEN_ERR		15	//购电卡插入未开户电表
#define		IC_NOOPEN2_ERR		16	//补卡插入未开户电表
#define		IC_TIMES_ERR		17	//购电次数错误
#define		IC_NONULL_ERR		18	//用户卡返写信息文件不为空
#define		IC_NOIN_ERR		19	//操作卡片通讯错误(读写卡片失败)
#define		IC_PREIC_ERR		20	//提前拔卡
#define		IC_OVERMAX_ERR		21	//剩余金额超囤积
//-------------- CPU end -----------------------
