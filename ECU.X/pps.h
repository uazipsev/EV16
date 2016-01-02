/**********************************************************************/
/*              Header for Pin Re-Mapping peripheral library functions               */
/*********************************************************************/

//#include "peripheralversion.h"

#ifndef __PPS_H
#define __PPS_H

/*----------------------------------------------------------------------------------------------------*/
/*  Remappable Peripheral Inputs: 																	  */
/*----------------------------------------------------------------------------------------------------*/
#if defined(_PPI_PPS_V2) || defined (_PPI_PPS_V3)
#define IN_PIN_PPS_VSS				0					/* Assign VSS as Input Pin */
#define IN_PIN_PPS_C1OUT			1					/* Assign C1OUT as Input Pin */
#define IN_PIN_PPS_C2OUT			2					/* Assign C2OUT as Input Pin */
#define IN_PIN_PPS_C3OUT			3					/* Assign C3OUT as Input Pin */
#define IN_PIN_PPS_C4OUT			4					/* Assign C4OUT as Input Pin */
#define IN_PIN_PPS_PTGO30			6					/* Assign PTGO30 as Input Pin */
#define IN_PIN_PPS_PTGO31			7					/* Assign PTGO31 as Input Pin */
#define IN_PIN_PPS_FINDX1			8					/* Assign FINDX1 as Input Pin */
#define IN_PIN_PPS_FHOME1			9					/* Assign FHOME1 as Input Pin */
#define IN_PIN_PPS_FINDX2			10					/* Assign FINDX2 as Input Pin */
#define IN_PIN_PPS_FHOME2			11					/* Assign FHOME2 as Input Pin */
#define IN_PIN_PPS_C5OUT            12					/* Assign C5OUT as Input Pin */

#else
#define IN_PIN_PPS_RP0				0					/* Assign RP0 as Input Pin */
#define IN_PIN_PPS_RP1				1					/* Assign RP1 as Input Pin */
#define IN_PIN_PPS_RP2				2					/* Assign RP2 as Input Pin */
#define IN_PIN_PPS_RP3				3					/* Assign RP3 as Input Pin */
#define IN_PIN_PPS_RP4				4					/* Assign RP4 as Input Pin */
#define IN_PIN_PPS_RP5				5					/* Assign RP5 as Input Pin */
#define IN_PIN_PPS_RP6				6					/* Assign RP6 as Input Pin */
#define IN_PIN_PPS_RP7				7					/* Assign RP7 as Input Pin */
#define IN_PIN_PPS_RP8				8					/* Assign RP8 as Input Pin */
#define IN_PIN_PPS_RP9				9					/* Assign RP9 as Input Pin */
#define IN_PIN_PPS_RP10				10					/* Assign RP10 as Input Pin */
#define IN_PIN_PPS_RP11				11					/* Assign RP11 as Input Pin */
#define IN_PIN_PPS_RP12				12					/* Assign RP12 as Input Pin */
#define IN_PIN_PPS_RP13				13					/* Assign RP13 as Input Pin */
#define IN_PIN_PPS_RP14				14					/* Assign RP14 as Input Pin */
#define IN_PIN_PPS_RP15				15					/* Assign RP15 as Input Pin */
#endif

#define IN_PIN_PPS_RP16				16					/* Assign RP16 as Input Pin */
#define IN_PIN_PPS_RP17				17					/* Assign RP17 as Input Pin */
#define IN_PIN_PPS_RP18				18					/* Assign RP18 as Input Pin */
#define IN_PIN_PPS_RP19				19					/* Assign RP19 as Input Pin */
#define IN_PIN_PPS_RP20				20					/* Assign RP20 as Input Pin */
#define IN_PIN_PPS_RP21				21					/* Assign RP21 as Input Pin */
#define IN_PIN_PPS_RP22				22					/* Assign RP22 as Input Pin */
#define IN_PIN_PPS_RP23				23					/* Assign RP23 as Input Pin */

#if defined (_PPI_PPS_V2)
#define IN_PIN_PPS_RPI24			24					/* Assign RPI24 as Input Pin */
#define IN_PIN_PPS_RPI25			25					/* Assign RPI25 as Input Pin */

#define IN_PIN_PPS_RPI27			27					/* Assign RPI27 as Input Pin */
#define IN_PIN_PPS_RPI28			28					/* Assign RPI28 as Input Pin */

#define IN_PIN_PPS_RP30				30					/* Assign RP30 as Input Pin */
#define IN_PIN_PPS_RP31				31					/* Assign RP31 as Input Pin */
#define IN_PIN_PPS_RPI32			32					/* Assign RPI32 as Input Pin */
#define IN_PIN_PPS_RPI33			33					/* Assign RPI33 as Input Pin */
#define IN_PIN_PPS_RPI34			34					/* Assign RPI34 as Input Pin */
#define IN_PIN_PPS_RPI35			35					/* Assign RP35 as Input Pin */
#define IN_PIN_PPS_RPI36			36					/* Assign RP36 as Input Pin */
#define IN_PIN_PPS_RPI37			37					/* Assign RP37 as Input Pin */
#define IN_PIN_PPS_RPI38			38					/* Assign RP38 as Input Pin */
#define IN_PIN_PPS_RPI39			39					/* Assign RP39 as Input Pin */
#define IN_PIN_PPS_RPI40			40					/* Assign RP40 as Input Pin */
#define IN_PIN_PPS_RPI41			41					/* Assign RP41 as Input Pin */
#define IN_PIN_PPS_RPI42			42					/* Assign RP42 as Input Pin */
#define IN_PIN_PPS_RPI43			43					/* Assign RP43 as Input Pin */
#define IN_PIN_PPS_RPI44			44					/* Assign RPI44 as Input Pin */
#define IN_PIN_PPS_RPI45			45					/* Assign RPI45 as Input Pin */
#define IN_PIN_PPS_RPI46			46					/* Assign RPI46 as Input Pin */
#define IN_PIN_PPS_RPI47			47					/* Assign RPI47 as Input Pin */
#define IN_PIN_PPS_RPI49			49					/* Assign RP49 as Input Pin */
#define IN_PIN_PPS_RPI50			50					/* Assign RP50 as Input Pin */
#define IN_PIN_PPS_RPI51			51					/* Assign RPI51 as Input Pin */
#define IN_PIN_PPS_RPI52			52					/* Assign RPI52 as Input Pin */
#define IN_PIN_PPS_RPI53			53					/* Assign RPI53 as Input Pin */
#define IN_PIN_PPS_RP54				54					/* Assign RP54 as Input Pin */
#define IN_PIN_PPS_RP55				55					/* Assign RP55 as Input Pin */
#define IN_PIN_PPS_RP56				56					/* Assign RP56 as Input Pin */
#define IN_PIN_PPS_RP57				57					/* Assign RP57 as Input Pin */
#define IN_PIN_PPS_RPI58			58					/* Assign RPI58 as Input Pin */
#define IN_PIN_PPS_RPI60			60					/* Assign RP60 as Input Pin */
#define IN_PIN_PPS_RPI61			61					/* Assign RP61 as Input Pin */
#define IN_PIN_PPS_RPI62			62					/* Assign RP62 as Input Pin */
#define IN_PIN_PPS_RP63				63					/* Assign RP63 as Input Pin */
#define IN_PIN_PPS_RP64				64					/* Assign RP64 as Input Pin */
#define IN_PIN_PPS_RP65				65					/* Assign RP65 as Input Pin */
#define IN_PIN_PPS_RP66 			66 					/* Assign RP66 as Input Pin */
#define IN_PIN_PPS_RP67				67					/* Assign RP67 as Input Pin */
#define IN_PIN_PPS_RP68				68					/* Assign RP68 as Input Pin */
#define IN_PIN_PPS_RP69				69					/* Assign RP69 as Input Pin */
#define IN_PIN_PPS_RP70				70					/* Assign RP70 as Input Pin */
#define IN_PIN_PPS_RP71				71					/* Assign RP71 as Input Pin */
#define IN_PIN_PPS_RPI72			72					/* Assign RP72 as Input Pin */
#define IN_PIN_PPS_RPI73			73					/* Assign RP73 as Input Pin */
#define IN_PIN_PPS_RPI74			74					/* Assign RP74 as Input Pin */
#define IN_PIN_PPS_RPI75			75					/* Assign RP75 as Input Pin */
#define IN_PIN_PPS_RPI76			76					/* Assign RP76 as Input Pin */
#define IN_PIN_PPS_RPI77			77					/* Assign RP77 as Input Pin */
#define IN_PIN_PPS_RPI78			78					/* Assign RP78 as Input Pin */
#define IN_PIN_PPS_RP79				79					/* Assign RP79 as Input Pin */
#define IN_PIN_PPS_RP80				80					/* Assign RP80 as Input Pin */
#define IN_PIN_PPS_RPI81			81					/* Assign RP81 as Input Pin */
#define IN_PIN_PPS_RP82				82					/* Assign RP82 as Input Pin */
#define IN_PIN_PPS_RPI83			83					/* Assign RP83 as Input Pin */
#define IN_PIN_PPS_RP84				84					/* Assign RP84 as Input Pin */
#define IN_PIN_PPS_RP85				85					/* Assign RP85 as Input Pin */
#define IN_PIN_PPS_RPI86			86					/* Assign RP86 as Input Pin */
#define IN_PIN_PPS_RP87				87					/* Assign RP87 as Input Pin */
#define IN_PIN_PPS_RPI88			88					/* Assign RP88 as Input Pin */
#define IN_PIN_PPS_RPI89			89					/* Assign RP89 as Input Pin */
#define IN_PIN_PPS_RPI94			94					/* Assign RPI94 as Input Pin */
#define IN_PIN_PPS_RPI95			95					/* Assign RPI95 as Input Pin */
#define IN_PIN_PPS_RPI96			96					/* Assign RPI96 as Input Pin */
#define IN_PIN_PPS_RP97				97					/* Assign RP97 as Input Pin */
#define IN_PIN_PPS_RP98				98					/* Assign RP98 as Input Pin */
#define IN_PIN_PPS_RP99				99					/* Assign RP99 as Input Pin */
#define IN_PIN_PPS_RP100			100					/* Assign RP100 as Input Pin */
#define IN_PIN_PPS_RP101			101					/* Assign RP101 as Input Pin */
#define IN_PIN_PPS_RP104			104					/* Assign RP104 as Input Pin */
#define IN_PIN_PPS_RP108			108					/* Assign RP108 as Input Pin */
#define IN_PIN_PPS_RP109			109					/* Assign RP109 as Input Pin */
#define IN_PIN_PPS_RP110			110					/* Assign RP110 as Input Pin */
#define IN_PIN_PPS_RP111			111					/* Assign RP111 as Input Pin */
#define IN_PIN_PPS_RP112			112					/* Assign RP112 as Input Pin */
#define IN_PIN_PPS_RP113			113					/* Assign RP113 as Input Pin */
#define IN_PIN_PPS_RP118			118					/* Assign RP118 as Input Pin */
#define IN_PIN_PPS_RPI119			119					/* Assign RPI119 as Input Pin */
#define IN_PIN_PPS_RP120			120					/* Assign RP120 as Input Pin */
#define IN_PIN_PPS_RPI121			121					/* Assign RPI121 as Input Pin */
#define IN_PIN_PPS_RPI124			124					/* Assign RP124 as Input Pin */
#define IN_PIN_PPS_RP125			125					/* Assign RP125 as Input Pin */
#define IN_PIN_PPS_RP126			126					/* Assign RP126 as Input Pin */
#define IN_PIN_PPS_RP127			127					/* Assign RP127 as Input Pin */

#elif defined (_PPI_PPS_V3) && !defined (_C5EVT)
#define IN_PIN_PPS_RPI24			24					/* Assign RPI24 as Input Pin */
#define IN_PIN_PPS_RPI25			25					/* Assign RPI25 as Input Pin */
#define IN_PIN_PPS_RPI27			27					/* Assign RPI27 as Input Pin */
#define IN_PIN_PPS_RPI28			28					/* Assign RPI28 as Input Pin */
#define IN_PIN_PPS_RPI32			32					/* Assign RPI32 as Input Pin */
#define IN_PIN_PPS_RPI33			33					/* Assign RPI33 as Input Pin */
#define IN_PIN_PPS_RPI34			34					/* Assign RPI34 as Input Pin */
#define IN_PIN_PPS_RP35				35					/* Assign RP35 as Input Pin */
#define IN_PIN_PPS_RP36				36					/* Assign RP36 as Input Pin */
#define IN_PIN_PPS_RP37				37					/* Assign RP37 as Input Pin */
#define IN_PIN_PPS_RP38				38					/* Assign RP38 as Input Pin */
#define IN_PIN_PPS_RP39				39					/* Assign RP39 as Input Pin */
#define IN_PIN_PPS_RP40				40					/* Assign RP40 as Input Pin */
#define IN_PIN_PPS_RP41				41					/* Assign RP41 as Input Pin */
#define IN_PIN_PPS_RP42				42					/* Assign RP42 as Input Pin */
#define IN_PIN_PPS_RP43				43					/* Assign RP43 as Input Pin */
#define IN_PIN_PPS_RPI44			44					/* Assign RPI44 as Input Pin */
#define IN_PIN_PPS_RPI45			45					/* Assign RPI45 as Input Pin */
#define IN_PIN_PPS_RPI46			46					/* Assign RPI46 as Input Pin */
#define IN_PIN_PPS_RPI47			47					/* Assign RPI47 as Input Pin */
#define IN_PIN_PPS_RPI51			51					/* Assign RPI51 as Input Pin */
#define IN_PIN_PPS_RPI52			52					/* Assign RPI52 as Input Pin */
#define IN_PIN_PPS_RPI53			53					/* Assign RPI53 as Input Pin */
#define IN_PIN_PPS_RP54				54					/* Assign RP54 as Input Pin */
#define IN_PIN_PPS_RP55				55					/* Assign RP55 as Input Pin */
#define IN_PIN_PPS_RP56				56					/* Assign RP56 as Input Pin */
#define IN_PIN_PPS_RP57				57					/* Assign RP57 as Input Pin */
#define IN_PIN_PPS_RPI58			58					/* Assign RPI58 as Input Pin */
#define IN_PIN_PPS_RPI94			94					/* Assign RPI94 as Input Pin */
#define IN_PIN_PPS_RPI95			95					/* Assign RPI95 as Input Pin */
#define IN_PIN_PPS_RPI96			96					/* Assign RPI96 as Input Pin */
#define IN_PIN_PPS_RP97				97					/* Assign RP97 as Input Pin */
#define IN_PIN_PPS_RP118			118					/* Assign RP118 as Input Pin */
#define IN_PIN_PPS_RPI119			119					/* Assign RPI119 as Input Pin */
#define IN_PIN_PPS_RP120			120					/* Assign RP120 as Input Pin */
#define IN_PIN_PPS_RPI121			121					/* Assign RPI121 as Input Pin */

#elif defined (_PPI_PPS_V3) && defined (_C5EVT)
#define IN_PIN_PPS_RPI24			24					/* Assign RPI24 as Input Pin */
#define IN_PIN_PPS_RPI25			25					/* Assign RPI25 as Input Pin */
#define IN_PIN_PPS_RPI27			27					/* Assign RPI27 as Input Pin */
#define IN_PIN_PPS_RPI28			28					/* Assign RPI28 as Input Pin */
#define IN_PIN_PPS_RP30				30					/* Assign RP30 as Input Pin */
#define IN_PIN_PPS_RP31				31					/* Assign RP31 as Input Pin */
#define IN_PIN_PPS_RPI32			32					/* Assign RPI32 as Input Pin */
#define IN_PIN_PPS_RPI33			33					/* Assign RPI33 as Input Pin */
#define IN_PIN_PPS_RPI34			34					/* Assign RPI34 as Input Pin */
#define IN_PIN_PPS_RP35				35					/* Assign RP35 as Input Pin */
#define IN_PIN_PPS_RP36				36					/* Assign RP36 as Input Pin */
#define IN_PIN_PPS_RP37				37					/* Assign RP37 as Input Pin */
#define IN_PIN_PPS_RP38				38					/* Assign RP38 as Input Pin */
#define IN_PIN_PPS_RP39				39					/* Assign RP39 as Input Pin */
#define IN_PIN_PPS_RP40				40					/* Assign RP40 as Input Pin */
#define IN_PIN_PPS_RP41				41					/* Assign RP41 as Input Pin */
#define IN_PIN_PPS_RP42				42					/* Assign RP42 as Input Pin */
#define IN_PIN_PPS_RP43				43					/* Assign RP43 as Input Pin */
#define IN_PIN_PPS_RPI44			44					/* Assign RPI44 as Input Pin */
#define IN_PIN_PPS_RPI45			45					/* Assign RPI45 as Input Pin */
#define IN_PIN_PPS_RPI46			46					/* Assign RPI46 as Input Pin */
#define IN_PIN_PPS_RPI47			47					/* Assign RPI47 as Input Pin */
#define IN_PIN_PPS_RP49				49					/* Assign RP49 as Input Pin */
#define IN_PIN_PPS_RP50				50					/* Assign RP50 as Input Pin */
#define IN_PIN_PPS_RPI51			51					/* Assign RPI51 as Input Pin */
#define IN_PIN_PPS_RPI52			52					/* Assign RPI52 as Input Pin */
#define IN_PIN_PPS_RPI53			53					/* Assign RPI53 as Input Pin */
#define IN_PIN_PPS_RP54				54					/* Assign RP54 as Input Pin */
#define IN_PIN_PPS_RP55				55					/* Assign RP55 as Input Pin */
#define IN_PIN_PPS_RP56				56					/* Assign RP56 as Input Pin */
#define IN_PIN_PPS_RP57				57					/* Assign RP57 as Input Pin */
#define IN_PIN_PPS_RPI58			58					/* Assign RPI58 as Input Pin */
#define IN_PIN_PPS_RPI60			60					/* Assign RP60 as Input Pin */
#define IN_PIN_PPS_RPI61			61					/* Assign RP61 as Input Pin */
#define IN_PIN_PPS_RPI63			63					/* Assign RP63 as Input Pin */
#define IN_PIN_PPS_RP69				69					/* Assign RP69 as Input Pin */
#define IN_PIN_PPS_RP70				70					/* Assign RP70 as Input Pin */
#define IN_PIN_PPS_RPI72				72					/* Assign RP72 as Input Pin */
#define IN_PIN_PPS_RPI76				76					/* Assign RP76 as Input Pin */
#define IN_PIN_PPS_RPI77				77					/* Assign RP77 as Input Pin */
#define IN_PIN_PPS_RPI80				80					/* Assign RP80 as Input Pin */
#define IN_PIN_PPS_RP81				81					/* Assign RP81 as Input Pin */
#define IN_PIN_PPS_RPI94			94					/* Assign RPI94 as Input Pin */
#define IN_PIN_PPS_RPI95			95					/* Assign RPI95 as Input Pin */
#define IN_PIN_PPS_RPI96			96					/* Assign RPI96 as Input Pin */
#define IN_PIN_PPS_RPI112			112					/* Assign RP112 as Input Pin */
#define IN_PIN_PPS_RP113			113					/* Assign RP113 as Input Pin */
#define IN_PIN_PPS_RP118			118					/* Assign RP118 as Input Pin */
#define IN_PIN_PPS_RPI119			119					/* Assign RPI119 as Input Pin */
#define IN_PIN_PPS_RP120			120					/* Assign RP120 as Input Pin */
#define IN_PIN_PPS_RPI121			121					/* Assign RPI121 as Input Pin */
#define IN_PIN_PPS_RPI124			124					/* Assign RP124 as Input Pin */
#define IN_PIN_PPS_RP125			125					/* Assign RP125 as Input Pin */
#define IN_PIN_PPS_RP126			126					/* Assign RP126 as Input Pin */
#define IN_PIN_PPS_RP127			127					/* Assign RP127 as Input Pin */

#else
#define IN_PIN_PPS_RP24				24					/* Assign RP24 as Input Pin */
#define IN_PIN_PPS_RP25				25					/* Assign RP25 as Input Pin */
#define IN_PIN_PPS_VSS				31					/* Input Pin tied to Vss */
#endif

#ifdef _PPI_PPS_V4 //#ifdef _PPI_PPS_V2 - gives errors!
#define IN_PIN_PPS_RPI35		IN_PIN_PPS_RP35
#define IN_PIN_PPS_RPI36		IN_PIN_PPS_RP36
#define IN_PIN_PPS_RPI37		IN_PIN_PPS_RP37
#define IN_PIN_PPS_RPI38		IN_PIN_PPS_RP38
#define IN_PIN_PPS_RPI39		IN_PIN_PPS_RP39
#define IN_PIN_PPS_RPI40		IN_PIN_PPS_RP40
#define IN_PIN_PPS_RPI41		IN_PIN_PPS_RP41
#define IN_PIN_PPS_RPI42		IN_PIN_PPS_RP42
#define IN_PIN_PPS_RPI43		IN_PIN_PPS_RP43
#define IN_PIN_PPS_RPI49		IN_PIN_PPS_RP49
#define IN_PIN_PPS_RPI50		IN_PIN_PPS_RP50
#define IN_PIN_PPS_RPI60		IN_PIN_PPS_RP60
#define IN_PIN_PPS_RPI61		IN_PIN_PPS_RP61
#define IN_PIN_PPS_RPI62		IN_PIN_PPS_RP62
#define IN_PIN_PPS_RPI72		IN_PIN_PPS_RP72
#define IN_PIN_PPS_RPI73		IN_PIN_PPS_RP73
#define IN_PIN_PPS_RPI74		IN_PIN_PPS_RP74
#define IN_PIN_PPS_RPI75		IN_PIN_PPS_RP75
#define IN_PIN_PPS_RPI76		IN_PIN_PPS_RP76
#define IN_PIN_PPS_RPI77		IN_PIN_PPS_RP77
#define IN_PIN_PPS_RPI78		IN_PIN_PPS_RP78
#define IN_PIN_PPS_RPI81		IN_PIN_PPS_RP81
#define IN_PIN_PPS_RPI83		IN_PIN_PPS_RP83
#define IN_PIN_PPS_RPI86		IN_PIN_PPS_RP86
#define IN_PIN_PPS_RPI88		IN_PIN_PPS_RP88
#define IN_PIN_PPS_RPI89		IN_PIN_PPS_RP89
#define IN_PIN_PPS_RPI124		IN_PIN_PPS_RP124
#endif

#define IN_FN_PPS_INT1				RPINR0bits.INT1R	/* Assign External Interrupt 1 (INTR1) to the corresponding RPn pin*/
#define IN_FN_PPS_INT2				RPINR1bits.INT2R	/* Assign External Interrupt 2 (INTR2) to the corresponding RPn pin*/


#if defined(_PPI_PPS_V2)|| defined (_PPI_PPS_V3)
#define IN_FN_PPS_INT3				RPINR1bits.INT3R	/* Assign External Interrupt 3 (INTR3) to the corresponding RPn pin*/
#define IN_FN_PPS_INT4				RPINR2bits.INT4R	/* Assign External Interrupt 4 (INTR4) to the corresponding RPn pin*/
#endif

#define IN_FN_PPS_T2CK				RPINR3bits.T2CKR	/* Assign Timer2 External Clock (T2CK) to the corresponding RPn pin*/
#define IN_FN_PPS_T3CK				RPINR3bits.T3CKR	/* Assign Timer3 External Clock (T3CK) to the corresponding RPn pin*/
#define IN_FN_PPS_T4CK				RPINR4bits.T4CKR	/* Assign Timer4 External Clock (T4CK) to the corresponding RPn pin*/
#define IN_FN_PPS_T5CK				RPINR4bits.T5CKR	/* Assign Timer5 External Clock (T5CK) to the corresponding RPn pin*/

#if defined(_PPI_PPS_V2)|| defined (_PPI_PPS_V3)
#define IN_FN_PPS_T6CK				RPINR5bits.T6CKR	/* Assign Timer6 External Clock (T6CK) to the corresponding RPn pin*/
#define IN_FN_PPS_T7CK				RPINR5bits.T7CKR	/* Assign Timer7 External Clock (T7CK) to the corresponding RPn pin*/
#define IN_FN_PPS_T8CK				RPINR6bits.T8CKR	/* Assign Timer8 External Clock (T8CK) to the corresponding RPn pin*/
#define IN_FN_PPS_T9CK				RPINR6bits.T9CKR	/* Assign Timer9 External Clock (T9CK) to the corresponding RPn pin*/
#endif

#define IN_FN_PPS_IC1				RPINR7bits.IC1R		/* Assign Input Capture 1 (IC1) to the corresponding RPn pin*/
#define IN_FN_PPS_IC2				RPINR7bits.IC2R		/* Assign Input Capture 2 (IC2) to the corresponding RPn pin*/


#if defined (_C5EVT)
#define IN_FN_PPS_IC3				RPINR8bits.IC3R		/* Assign Input Capture 3 (IC4) to the corresponding RPn pin*/
#define IN_FN_PPS_IC4				RPINR8bits.IC4R		/* Assign Input Capture 4 (IC4) to the corresponding RPn pin*/
#define IN_FN_PPS_IC5				RPINR9bits.IC5R		/* Assign Input Capture 5 (IC5) to the corresponding RPn pin*/
#define IN_FN_PPS_IC6				RPINR9bits.IC6R		/* Assign Input Capture 6 (IC6) to the corresponding RPn pin*/
#define IN_FN_PPS_SDI1				RPINR20bits.SDI1R	/* Assign SPI1 Data Input (SDI1) to the corresponding RPn pin*/
#define IN_FN_PPS_SCK1				RPINR20bits.SCK1R	/* Assign SPI1 Clock Input (SCK1IN) to the corresponding RPn pin*/
#define IN_FN_PPS_SS1				RPINR21bits.SS1R	/* Assign SPI1 Slave Select Input (SS1IN) to the corresponding RPn pin*/
#define IN_FN_PPS_SDI2				RPINR22bits.SDI2R	/* Assign SPI2 Data Input (SDI2) to the corresponding RPn pin*/
#define IN_FN_PPS_SCK2				RPINR22bits.SCK2R	/* Assign SPI2 Clock Input (SCK2IN) to the corresponding RPn pin*/
#define IN_FN_PPS_SS2				RPINR23bits.SS2R	/* Assign SPI2 Slave Select Input (SS2IN) to the corresponding RPn pin*/

#elif defined (_PPI_PPS_V2) || defined(_PPI_PPS_V3) && !defined (_C5EVT)
#define IN_FN_PPS_IC3				RPINR8bits.IC3R		/* Assign Input Capture 3 (IC4) to the corresponding RPn pin*/
#define IN_FN_PPS_IC4				RPINR8bits.IC4R		/* Assign Input Capture 4 (IC4) to the corresponding RPn pin*/
#define IN_FN_PPS_SDI1				RPINR20bits.SDI1R	/* Assign SPI1 Data Input (SDI1) to the corresponding RPn pin*/
#define IN_FN_PPS_SCK1				RPINR20bits.SCK1R	/* Assign SPI1 Clock Input (SCK1IN) to the corresponding RPn pin*/
#define IN_FN_PPS_SS1				RPINR21bits.SS1R	/* Assign SPI1 Slave Select Input (SS1IN) to the corresponding RPn pin*/
#define IN_FN_PPS_SDI2				RPINR22bits.SDI2R	/* Assign SPI2 Data Input (SDI2) to the corresponding RPn pin*/
#define IN_FN_PPS_SCK2				RPINR22bits.SCK2R	/* Assign SPI2 Clock Input (SCK2IN) to the corresponding RPn pin*/
#define IN_FN_PPS_SS2				RPINR23bits.SS2R	/* Assign SPI2 Slave Select Input (SS2IN) to the corresponding RPn pin*/

#endif



#define IN_FN_PPS_IC7				RPINR10bits.IC7R	/* Assign Input Capture 7 (IC7) to the corresponding RPn pin*/
#define IN_FN_PPS_IC8				RPINR10bits.IC8R	/* Assign Input Capture 8 (IC8) to the corresponding RPn pin*/

#define IN_FN_PPS_OCFA				RPINR11bits.OCFAR	/* Assign Output Capture A (OCFA) to the corresponding RPn pin*/

#if defined(_PPI_PPS_V2)|| defined (_PPI_PPS_V3)
#define IN_FN_PPS_OCFB				RPINR11bits.OCFBR	/* Assign Output Capture B (OCFB) to the corresponding RPn pin*/
#endif

#if defined(_PPI_PPS_V2)|| defined (_PPI_PPS_V3)
#define IN_FN_PPS_FLT1				RPINR12bits.FLT1R	/* Assign PWM1 Fault (FLT1) to the corresponding RPn pin*/
#define IN_FN_PPS_FLT2				RPINR12bits.FLT2R	/* Assign PWM2 Fault (FLT2) to the corresponding RPn pin*/
#define IN_FN_PPS_FLT3				RPINR13bits.FLT3R	/* Assign PWM3 Fault (FLT3) to the corresponding RPn pin*/
#define IN_FN_PPS_FLT4				RPINR13bits.FLT4R	/* Assign PWM4 Fault (FLT4) to the corresponding RPn pin*/
#else
#define IN_FN_PPS_FLTA1				RPINR12bits.FLTA1R	/* Assign PWM1 Fault (FLTA1) to the corresponding RPn pin*/
#define IN_FN_PPS_FLTA2				RPINR13bits.FLTA2R	/* Assign PWM2 Fault (FLTA2) to the corresponding RPn pin*/
#endif

#define IN_FN_PPS_QEA1				RPINR14bits.QEA1R	/* Assign A (QEA) to the corresponding pin*/
#define IN_FN_PPS_QEB1				RPINR14bits.QEB1R	/* Assign B (QEB) to the corresponding pin*/
#define IN_FN_PPS_QEI1				RPINR15bits.INDX1R	/* Assign QEI INDEX (INDX) to the corresponding RPn pin*/

#if defined(_PPI_PPS_V2)|| defined (_PPI_PPS_V3)
#define IN_FN_PPS_QEH1				RPINR15bits.HOME1R	/* Assign QEI HOME to the corresponding RPn pin*/
#endif

#define IN_FN_PPS_QEA2				RPINR16bits.QEA2R	/* Assign A (QEA) to the corresponding pin*/
#define IN_FN_PPS_QEB2				RPINR16bits.QEB2R	/* Assign B (QEB) to the corresponding pin*/
#define IN_FN_PPS_QEI2				RPINR17bits.INDX2R	/* Assign QEI INDEX (INDX) to the corresponding RPn pin*/

#if defined(_PPI_PPS_V2)|| defined (_PPI_PPS_V3)
#define IN_FN_PPS_QEH2				RPINR17bits.HOME2R	/* Assign QEI HOME to the corresponding RPn pin*/
#endif

#define IN_FN_PPS_U1RX				RPINR18bits.U1RXR	/* Assign UART1 Receive (U1RX) to the corresponding RPn pin*/
#define IN_FN_PPS_U1CTS				RPINR18bits.U1CTSR	/* Assign UART1 Clear to Send (U1CTS) to the corresponding RPn pin*/
#define IN_FN_PPS_U2RX				RPINR19bits.U2RXR	/* Assign UART2 Receive (U2RX) to the corresponding RPn pin*/
#define IN_FN_PPS_U2CTS				RPINR19bits.U2CTSR	/* Assign UART2 Clear to Send (U2CTS) to the corresponding RPn pin*/

#define IN_FN_PPS_SDI1				RPINR20bits.SDI1R	/* Assign SPI1 Data Input (SDI1) to the corresponding RPn pin*/
#define IN_FN_PPS_SCK1				RPINR20bits.SCK1R	/* Assign SPI1 Clock Input (SCK1IN) to the corresponding RPn pin*/
#define IN_FN_PPS_SS1				RPINR21bits.SS1R	/* Assign SPI1 Slave Select Input (SS1IN) to the corresponding RPn pin*/
#define IN_FN_PPS_SDI2				RPINR22bits.SDI2R	/* Assign SPI2 Data Input (SDI2) to the corresponding RPn pin*/
#define IN_FN_PPS_SCK2				RPINR22bits.SCK2R	/* Assign SPI2 Clock Input (SCK2IN) to the corresponding RPn pin*/
#define IN_FN_PPS_SS2				RPINR23bits.SS2R	/* Assign SPI2 Slave Select Input (SS2IN) to the corresponding RPn pin*/

#define IN_FN_PPS_CSDI				RPINR24bits.CSDIR	/* Assign DCI Serial Data Input (CSDIN) to the corresponding RPn pin*/
#define IN_FN_PPS_CSCK				RPINR24bits.CSCKR	/* Assign DCI Serial Clock Input (CSCKIN) to the corresponding RPn pin*/
#define IN_FN_PPS_COFS				RPINR25bits.COFSR	/* Assign DCI Frame Sync Input (COFSIN) to the corresponding RPn pin*/

#define IN_FN_PPS_C1RX				RPINR26bits.C1RXR	/* Assign ECAN1 Receive Input (C1RX) to the corresponding RPn pin*/

#if defined(_PPI_PPS_V2)|| defined (_PPI_PPS_V3)
#define IN_FN_PPS_C2RX				RPINR26bits.C2RXR	/* Assign ECAN2 Receive Input (C2RX) to the corresponding RPn pin*/
#define IN_FN_PPS_U3RX				RPINR27bits.U3RXR		/* Assign UART3 Receive (U3RX) to the corresponding RPn pin*/
#define IN_FN_PPS_U3CTS				RPINR27bits.U3CTSR	/* Assign UART3 Clear to Send (U3CTS) to the corresponding RPn pin*/
#define IN_FN_PPS_U4RX				RPINR28bits.U4RXR		/* Assign UART4 Receive (U4RX) to the corresponding RPn pin*/
#define IN_FN_PPS_U4CTS				RPINR28bits.U4CTSR	/* Assign UART4 Clear to Send (U4CTS) to the corresponding RPn pin*/
#define IN_FN_PPS_SDI3				RPINR29bits.SDI3R		/* Assign SPI3 Data Input (SDI3) to the corresponding RPn pin*/
#define IN_FN_PPS_SCK3				RPINR29bits.SCK3R		/* Assign SPI3 Clock Input (SCK3IN) to the corresponding RPn pin*/
#define IN_FN_PPS_SS3				RPINR30bits.SS3R		/* Assign SPI3 Slave Select Input (SS3IN) to the corresponding RPn pin*/
#define IN_FN_PPS_SDI4				RPINR31bits.SDI4R		/* Assign SPI4 Data Input (SDI4) to the corresponding RPn pin*/
#define IN_FN_PPS_SCK4				RPINR31bits.SCK4R		/* Assign SPI4 Clock Input (SCK4IN) to the corresponding RPn pin*/
#define IN_FN_PPS_SS4				RPINR32bits.SS4R		/* Assign SPI4 Slave Select Input (SS4IN) to the corresponding RPn pin*/
#define IN_FN_PPS_IC9				RPINR33bits.IC9R		/* Assign Input Capture 9 (IC9) to the corresponding RPn pin*/
#define IN_FN_PPS_IC10				RPINR33bits.IC10R		/* Assign Input Capture 10 (IC10) to the corresponding RPn pin*/
#define IN_FN_PPS_IC11				RPINR34bits.IC11R		/* Assign Input Capture 11 (IC11) to the corresponding RPn pin*/
#define IN_FN_PPS_IC12				RPINR34bits.IC12R		/* Assign Input Capture 12 (IC12) to the corresponding RPn pin*/
#define IN_FN_PPS_IC13				RPINR35bits.IC13R		/* Assign Input Capture 13 (IC13) to the corresponding RPn pin*/
#define IN_FN_PPS_IC14				RPINR35bits.IC14R		/* Assign Input Capture 14 (IC14) to the corresponding RPn pin*/
#define IN_FN_PPS_IC15				RPINR36bits.IC15R		/* Assign Input Capture 15 (IC15) to the corresponding RPn pin*/
#define IN_FN_PPS_IC16				RPINR36bits.IC16R		/* Assign Input Capture 16 (IC16) to the corresponding RPn pin*/
#define IN_FN_PPS_OCFC				RPINR37bits.OCFCR		/* Assign Output Capture C (OCFC) to the corresponding RPn pin*/
#define IN_FN_PPS_SYNCI1			RPINR37bits.SYNCI1R	/* Assign PWM Sync Input 1 (SYNCI1) to the corresponding RPn pin*/
#define IN_FN_PPS_SYNCI2			RPINR38bits.SYNCI2R	/* Assign PWM Sync Input 2 (SYNCI2) to the corresponding RPn pin*/
#define IN_FN_PPS_DTCMP1			RPINR38bits.DTCMP1R	/* Assign PWM Dead Time Compensation 1 (DTCMP1) to the corresponding RPn pin*/
#define IN_FN_PPS_DTCMP2			RPINR39bits.DTCMP2R	/* Assign PWM Dead Time Compensation 2 (DTCMP2) to the corresponding RPn pin*/
#define IN_FN_PPS_DTCMP3			RPINR39bits.DTCMP3R	/* Assign PWM Dead Time Compensation 3 (DTCMP3) to the corresponding RPn pin*/
#define IN_FN_PPS_DTCMP4			RPINR40bits.DTCMP4R	/* Assign PWM Dead Time Compensation 4 (DTCMP4) to the corresponding RPn pin*/
#define IN_FN_PPS_DTCMP5			RPINR40bits.DTCMP5R	/* Assign PWM Dead Time Compensation 5 (DTCMP5) to the corresponding RPn pin*/
#define IN_FN_PPS_DTCMP6			RPINR41bits.DTCMP6R	/* Assign PWM Dead Time Compensation 6 (DTCMP6) to the corresponding RPn pin*/
#define IN_FN_PPS_DTCMP7			RPINR41bits.DTCMP7R	/* Assign PWM Dead Time Compensation 7 (DTCMP7) to the corresponding RPn pin*/
#define IN_FN_PPS_FLT5				RPINR42bits.FLT5R		/* Assign PWM5 Fault (FLT5) to the corresponding RPn pin*/
#define IN_FN_PPS_FLT6				RPINR42bits.FLT6R		/* Assign PWM6 Fault (FLT6) to the corresponding RPn pin*/
#define IN_FN_PPS_FLT7				RPINR43bits.FLT7R		/* Assign PWM7 Fault (FLT7) to the corresponding RPn pin*/


#endif
			

#define iPPSInput(fn,pin)			fn=pin
#define PPSInput(fn,pin)			iPPSInput(fn,pin)

/*----------------------------------------------------------------------------------------------------*/
/*  Remappable Peripheral Outputs: 																	  */
/*----------------------------------------------------------------------------------------------------*/

#define OUT_FN_PPS_NULL				0x0000				/* RPn tied to default port pin */

#if defined(_PPI_PPS_V2) 
#define OUT_FN_PPS_U1TX				0x0001				/* RPn tied to UART1 Transmit */
#define OUT_FN_PPS_U1RTS			0x0002				/* RPn tied to UART1 Ready To Send */
#define OUT_FN_PPS_U2TX				0x0003				/* RPn tied to UART2 Transmit */
#define OUT_FN_PPS_U2RTS			0x0004				/* RPn tied to UART2 Ready To Send */
#define OUT_FN_PPS_SDO1				0x0005				/* RPn tied to SPI1 Data Output */
#define OUT_FN_PPS_SCK1				0x0006				/* RPn tied to SPI1 Clock Output */
#define OUT_FN_PPS_SS1				0x0007				/* RPn tied to SPI1 Slave Select Output */
#define OUT_FN_PPS_CSDO				0x000B				/* RPn tied to DCI Serial Data Output*/
#define OUT_FN_PPS_CSCKOUT			0x000C				/* RPn tied to DCI Serial Clock Output*/
#define OUT_FN_PPS_COFSOUT			0x000D				/* RPn tied to DCI Frame Sync Output*/
#define OUT_FN_PPS_C1TX				0x000E				/* RPn tied to ECAN1 Transmit */
#define OUT_FN_PPS_C2TX				0x000F				/* RPn tied to ECAN2 Transmit */
#define OUT_FN_PPS_OC1				0x0010				/* RPn tied to Output Compare 1 */
#define OUT_FN_PPS_OC2				0x0011				/* RPn tied to Output Compare 2 */
#define OUT_FN_PPS_OC3				0x0012				/* RPn tied to Output Compare 3 */
#define OUT_FN_PPS_OC4				0x0013				/* RPn tied to Output Compare 4 */
#define OUT_FN_PPS_OC5				0x0014				/* RPn tied to Output Compare 5 */
#define OUT_FN_PPS_OC6				0x0015				/* RPn tied to Output Compare 6 */
#define OUT_FN_PPS_OC7				0x0016				/* RPn tied to Output Compare 7 */
#define OUT_FN_PPS_OC8				0x0017				/* RPn tied to Output Compare 8 */
#define OUT_FN_PPS_C1OUT			0x0018				/* RPn tied to Comparator1 Output */
#define OUT_FN_PPS_C2OUT			0x0019				/* RPn tied to Comparator2 Output */
#define OUT_FN_PPS_C3OUT			0x001A				/* RPn tied to Comparator3 Output */
#define OUT_FN_PPS_U3TX				0x001B				/* RPn tied to UART3 Transmit */
#define OUT_FN_PPS_U3RTS			0x001C				/* RPn tied to UART3 Ready To Send */
#define OUT_FN_PPS_U4TX				0x001D				/* RPn tied to UART4 Transmit */
#define OUT_FN_PPS_U4RTS			0x001E				/* RPn tied to UART4 Ready To Send */
#define OUT_FN_PPS_SDO3				0x001F				/* RPn tied to SPI3 Data Output */
#define OUT_FN_PPS_SCK3				0x0020				/* RPn tied to SPI3 Clock Output */
#define OUT_FN_PPS_SS3				0x0021				/* RPn tied to SPI3 Slave Select Output */
#define OUT_FN_PPS_SDO4				0x0022				/* RPn tied to SPI4 Data Output */
#define OUT_FN_PPS_SCK4				0x0023				/* RPn tied to SPI4 Clock Output */
#define OUT_FN_PPS_SS4				0x0024				/* RPn tied to SPI4 Slave Select Output */
#define OUT_FN_PPS_OC9				0x0025				/* RPn tied to Output Compare 9 */
#define OUT_FN_PPS_OC10				0x0026				/* RPn tied to Output Compare 10 */
#define OUT_FN_PPS_OC11				0x0027				/* RPn tied to Output Compare 11 */
#define OUT_FN_PPS_OC12				0x0028				/* RPn tied to Output Compare 12 */
#define OUT_FN_PPS_OC13				0x0029				/* RPn tied to Output Compare 13 */
#define OUT_FN_PPS_OC14				0x002A				/* RPn tied to Output Compare 14 */
#define OUT_FN_PPS_OC15				0x002B				/* RPn tied to Output Compare 15 */
#define OUT_FN_PPS_OC16				0x002C				/* RPn tied to Output Compare 16 */
#define OUT_FN_PPS_SYNCO1			0x002D				/* RPn tied to Output SYNCO1 */
#define OUT_FN_PPS_SYNCO2			0x002E				/* RPn tied to Output SYNCO2 */
#define OUT_FN_PPS_QEI1CCMP			0x002F				/* RPn tied to Output QEI1CCMP */
#define OUT_FN_PPS_QEI2CCMP			0x0030				/* RPn tied to Output QEI2CCMP */
#define OUT_FN_PPS_REFCLKO			0x0031				/* RPn tied to Output REFCLKO */

#elif defined (_PPI_PPS_V3) && !defined (_C5EVT)
#define OUT_FN_PPS_U1TX				0x0001				/* RPn tied to UART1 Transmit */
#define OUT_FN_PPS_U2TX				0x0003				/* RPn tied to UART2 Transmit */
#define OUT_FN_PPS_SDO2				0x0008				/* RPn tied to SPI2 Data Output */
#define OUT_FN_PPS_SCK2				0x0009				/* RPn tied to SPI2 Clock Output */
#define OUT_FN_PPS_SS2				0x000A				/* RPn tied to SPI2 Slave Select Output */
#define OUT_FN_PPS_C1TX				0x000E				/* RPn tied to ECAN1 Transmit */
#define OUT_FN_PPS_OC1				0x0010				/* RPn tied to Output Compare 1 */
#define OUT_FN_PPS_OC2				0x0011				/* RPn tied to Output Compare 2 */
#define OUT_FN_PPS_OC3				0x0012				/* RPn tied to Output Compare 3 */
#define OUT_FN_PPS_OC4				0x0013				/* RPn tied to Output Compare 4 */
#define OUT_FN_PPS_C1OUT			0x0018				/* RPn tied to Comparator1 Output */
#define OUT_FN_PPS_C2OUT			0x0019				/* RPn tied to Comparator2 Output */
#define OUT_FN_PPS_C3OUT			0x001A				/* RPn tied to Comparator3 Output */
#define OUT_FN_PPS_SYNCO1			0x002D				/* RPn tied to Output SYNCO1 */
#define OUT_FN_PPS_QEI1CCMP			0x002F				/* RPn tied to Output QEI1CCMP */
#define OUT_FN_PPS_REFCLKO			0x0031				/* RPn tied to Output REFCLKO */
#define OUT_FN_PPS_C4OUT			0x0032				/* RPn tied to Comparator4 Output */

#elif defined (__PPI_PPS_V3) && defined (_C5EVT)
#define OUT_FN_PPS_U1TX				0x0001				/* RPn tied to UART1 Transmit */
#define OUT_FN_PPS_U2TX				0x0003				/* RPn tied to UART2 Transmit */
#define OUT_FN_PPS_SDO2				0x0008				/* RPn tied to SPI2 Data Output */
#define OUT_FN_PPS_SCK2				0x0009				/* RPn tied to SPI2 Clock Output */
#define OUT_FN_PPS_SS2				0x000A				/* RPn tied to SPI2 Slave Select Output */
#define OUT_FN_PPS_CSDO				0x000B				/* RPn tied to DCI Serial Data Output*/
#define OUT_FN_PPS_CSCKOUT			0x000C				/* RPn tied to DCI Serial Clock Output*/
#define OUT_FN_PPS_COFSOUT			0x000D				/* RPn tied to DCI Frame Sync Output*/
#define OUT_FN_PPS_C1TX				0x000E				/* RPn tied to ECAN1 Transmit */
#define OUT_FN_PPS_C2TX				0x000F				/* RPn tied to ECAN2 Transmit */
#define OUT_FN_PPS_OC1				0x0010				/* RPn tied to Output Compare 1 */
#define OUT_FN_PPS_OC2				0x0011				/* RPn tied to Output Compare 2 */
#define OUT_FN_PPS_OC3				0x0012				/* RPn tied to Output Compare 3 */
#define OUT_FN_PPS_OC4				0x0013				/* RPn tied to Output Compare 4 */
#define OUT_FN_PPS_OC5				0x0014				/* RPn tied to Output Compare 5 */
#define OUT_FN_PPS_OC6				0x0015				/* RPn tied to Output Compare 6 */
#define OUT_FN_PPS_OC7				0x0016				/* RPn tied to Output Compare 7 */
#define OUT_FN_PPS_OC8				0x0017				/* RPn tied to Output Compare 8 */
#define OUT_FN_PPS_C1OUT			0x0018				/* RPn tied to Comparator1 Output */
#define OUT_FN_PPS_C2OUT			0x0019				/* RPn tied to Comparator2 Output */
#define OUT_FN_PPS_C3OUT			0x001A				/* RPn tied to Comparator3 Output */
#define OUT_FN_PPS_U3TX				0x001B				/* RPn tied to UART3 Transmit */
#define OUT_FN_PPS_U3RTS			0x001C				/* RPn tied to UART3 Ready To Send */
#define OUT_FN_PPS_U4TX				0x001D				/* RPn tied to UART4 Transmit */
#define OUT_FN_PPS_U4RTS			0x001E				/* RPn tied to UART4 Ready To Send */
#define OUT_FN_PPS_SDO3				0x001F				/* RPn tied to SPI3 Data Output */
#define OUT_FN_PPS_SCK3				0x0020				/* RPn tied to SPI3 Clock Output */
#define OUT_FN_PPS_SS3				0x0021				/* RPn tied to SPI3 Slave Select Output */
#define OUT_FN_PPS_SYNCO1			0x002D				/* RPn tied to Output SYNCO1 */
#define OUT_FN_PPS_SYNCO2			0x002E				/* RPn tied to Output SYNCO2 */
#define OUT_FN_PPS_QEI1CCMP			0x002F				/* RPn tied to Output QEI1CCMP */
#define OUT_FN_PPS_QEI2CCMP			0x0030				/* RPn tied to Output QEI2CCMP */
#define OUT_FN_PPS_REFCLKO			0x0031				/* RPn tied to Output REFCLKO */
#define OUT_FN_PPS_C4OUT			0x0032				/* RPn tied to Comparator4 Output */
#define OUT_FN_PPS_C5OUT			0x0033				/* RPn tied to Comparator5 Output */

#else
#define OUT_FN_PPS_C1OUT			0x0001				/* RPn tied to Comparator1 Output */
#define OUT_FN_PPS_C2OUT			0x0002				/* RPn tied to Comparator2 Output */
#define OUT_FN_PPS_U1TX				0x0003				/* RPn tied to UART1 Transmit */
#define OUT_FN_PPS_U1RTS			0x0004				/* RPn tied to UART1 Ready To Send */
#define OUT_FN_PPS_U2TX				0x0005				/* RPn tied to UART2 Transmit */
#define OUT_FN_PPS_U2RTS			0x0006				/* RPn tied to UART2 Ready To Send */
#define OUT_FN_PPS_SDO1				0x0007				/* RPn tied to SPI1 Data Output */
#define OUT_FN_PPS_SCK1				0x0008				/* RPn tied to SPI1 Clock Output */
#define OUT_FN_PPS_SS1				0x0009				/* RPn tied to SPI1 Slave Select Output */
#define OUT_FN_PPS_SDO2				0x000A				/* RPn tied to SPI2 Data Output */
#define OUT_FN_PPS_SCK2				0x000B				/* RPn tied to SPI2 Clock Output */
#define OUT_FN_PPS_SS2				0x000C				/* RPn tied to SPI2 Slave Select Output */
#define OUT_FN_PPS_CSDO				0x000D				/* RPn tied to DCI Serial Data Output*/
#define OUT_FN_PPS_CSCKOUT			0x000E				/* RPn tied to DCI Serial Clock Output*/
#define OUT_FN_PPS_COFSOUT			0x000F				/* RPn tied to DCI Frame Sync Output*/
#define OUT_FN_PPS_C1TX				0x0010				/* RPn tied to ECAN1 Transmit */
#define OUT_FN_PPS_OC1				0x0012				/* RPn tied to Output Compare 1 */
#define OUT_FN_PPS_OC2				0x0013				/* RPn tied to Output Compare 2 */
#define OUT_FN_PPS_OC3				0x0014				/* RPn tied to Output Compare 3 */
#define OUT_FN_PPS_OC4				0x0015				/* RPn tied to Output Compare 4 */
#define OUT_FN_PPS_UPDN1			0x001A				/* RPn tied to QEI1 UPDN Output */
#define OUT_FN_PPS_UPDN2			0x001B				/* RPn tied to QEI2 UPDN Output */
#endif

#if defined(_PPI_PPS_V2)
#define OUT_PIN_PPS_RP64			RPOR0bits.RP64R		/* Assign RP64 as Output Pin */
#define OUT_PIN_PPS_RP65			RPOR0bits.RP65R		/* Assign RP65 as Output Pin */
#define OUT_PIN_PPS_RP66			RPOR1bits.RP66R		/* Assign RP66 as Output Pin */
#define OUT_PIN_PPS_RP67			RPOR1bits.RP67R		/* Assign RP67 as Output Pin */
#define OUT_PIN_PPS_RP68			RPOR2bits.RP68R		/* Assign RP68 as Output Pin */
#define OUT_PIN_PPS_RP69			RPOR2bits.RP69R		/* Assign RP69 as Output Pin */
#define OUT_PIN_PPS_RP70			RPOR3bits.RP70R		/* Assign RP70 as Output Pin */
#define OUT_PIN_PPS_RP71			RPOR3bits.RP71R		/* Assign RP71 as Output Pin */
#define OUT_PIN_PPS_RP79			RPOR4bits.RP79R		/* Assign RP79 as Output Pin */
#define OUT_PIN_PPS_RP80			RPOR4bits.RP80R		/* Assign RP80 as Output Pin */
#define OUT_PIN_PPS_RP82			RPOR5bits.RP82R		/* Assign RP82 as Output Pin */
#define OUT_PIN_PPS_RP84			RPOR5bits.RP84R		/* Assign RP84 as Output Pin */
#define OUT_PIN_PPS_RP85			RPOR6bits.RP85R		/* Assign RP85 as Output Pin */
#define OUT_PIN_PPS_RP87			RPOR6bits.RP87R		/* Assign RP87 as Output Pin */
#define OUT_PIN_PPS_RP96			RPOR7bits.RP96R		/* Assign RP96 as Output Pin */
#define OUT_PIN_PPS_RP97			RPOR7bits.RP97R		/* Assign RP97 as Output Pin */
#define OUT_PIN_PPS_RP98			RPOR8bits.RP98R		/* Assign RP98 as Output Pin */
#define OUT_PIN_PPS_RP99			RPOR8bits.RP99R		/* Assign RP99 as Output Pin */
#define OUT_PIN_PPS_RP100			RPOR9bits.RP100R		/* Assign RP100 as Output Pin */
#define OUT_PIN_PPS_RP101			RPOR9bits.RP101R		/* Assign RP101 as Output Pin */
#define OUT_PIN_PPS_RP102			RPOR10bits.RP102R		/* Assign RP102 as Output Pin */
#define OUT_PIN_PPS_RP103			RPOR10bits.RP103R		/* Assign RP103 as Output Pin */
#define OUT_PIN_PPS_RP104			RPOR11bits.RP104R		/* Assign RP104 as Output Pin */
#define OUT_PIN_PPS_RP108			RPOR11bits.RP108R		/* Assign RP108 as Output Pin */
#define OUT_PIN_PPS_RP109			RPOR12bits.RP109R		/* Assign RP109 as Output Pin */
#define OUT_PIN_PPS_RP112			RPOR12bits.RP112R		/* Assign RP112 as Output Pin */
#define OUT_PIN_PPS_RP113			RPOR13bits.RP113R		/* Assign RP113 as Output Pin */
#define OUT_PIN_PPS_RP118			RPOR13bits.RP118R		/* Assign RP118 as Output Pin */
#define OUT_PIN_PPS_RP120			RPOR14bits.RP120R		/* Assign RP120 as Output Pin */
#define OUT_PIN_PPS_RP125			RPOR14bits.RP125R		/* Assign RP125 as Output Pin */
#define OUT_PIN_PPS_RP126			RPOR15bits.RP126R		/* Assign RP126 as Output Pin */
#define OUT_PIN_PPS_RP127			RPOR15bits.RP127R		/* Assign RP127 as Output Pin */

#endif

#define OUT_PIN_PPS_RP20			RPOR0bits.RP20R		/* Assign RP20 as Output Pin */
#define OUT_PIN_PPS_RP35			RPOR0bits.RP35R		/* Assign RP35 as Output Pin */
#define OUT_PIN_PPS_RP36			RPOR1bits.RP36R		/* Assign RP36 as Output Pin */
#define OUT_PIN_PPS_RP37			RPOR1bits.RP37R		/* Assign RP37 as Output Pin */
#define OUT_PIN_PPS_RP38			RPOR2bits.RP38R		/* Assign RP38 as Output Pin */
#define OUT_PIN_PPS_RP39			RPOR2bits.RP39R		/* Assign RP39 as Output Pin */
#define OUT_PIN_PPS_RP40			RPOR3bits.RP40R		/* Assign RP40 as Output Pin */
#define OUT_PIN_PPS_RP41			RPOR3bits.RP41R		/* Assign RP41 as Output Pin */
#define OUT_PIN_PPS_RP42			RPOR4bits.RP42R		/* Assign RP42 as Output Pin */
#define OUT_PIN_PPS_RP43			RPOR4bits.RP43R		/* Assign RP43 as Output Pin */
#define OUT_PIN_PPS_RP54			RPOR5bits.RP54R		/* Assign RP54 as Output Pin */
#define OUT_PIN_PPS_RP55			RPOR5bits.RP55R		/* Assign RP55 as Output Pin */
#define OUT_PIN_PPS_RP56			RPOR6bits.RP56R		/* Assign RP56 as Output Pin */
#define OUT_PIN_PPS_RP57			RPOR6bits.RP57R		/* Assign RP57 as Output Pin */
#define OUT_PIN_PPS_RP97			RPOR7bits.RP97R		/* Assign RP97 as Output Pin */
#define OUT_PIN_PPS_RP118			RPOR8bits.RP118R		/* Assign RP118 as Output Pin */
#define OUT_PIN_PPS_RP120			RPOR9bits.RP120R		/* Assign RP120 as Output Pin */

#if defined (_C5EVT) && defined (_PPI_PPS_V3)

#define OUT_PIN_PPS_RP20			RPOR0bits.RP20R		/* Assign RP20 as Output Pin */
#define OUT_PIN_PPS_RP35			RPOR0bits.RP35R		/* Assign RP35 as Output Pin */
#define OUT_PIN_PPS_RP36			RPOR1bits.RP36R		/* Assign RP36 as Output Pin */
#define OUT_PIN_PPS_RP37			RPOR1bits.RP37R		/* Assign RP37 as Output Pin */
#define OUT_PIN_PPS_RP38			RPOR2bits.RP38R		/* Assign RP38 as Output Pin */
#define OUT_PIN_PPS_RP39			RPOR2bits.RP39R		/* Assign RP39 as Output Pin */
#define OUT_PIN_PPS_RP40			RPOR3bits.RP40R		/* Assign RP40 as Output Pin */
#define OUT_PIN_PPS_RP41			RPOR3bits.RP41R		/* Assign RP41 as Output Pin */
#define OUT_PIN_PPS_RP42			RPOR4bits.RP42R		/* Assign RP42 as Output Pin */
#define OUT_PIN_PPS_RP43			RPOR4bits.RP43R		/* Assign RP43 as Output Pin */
#define OUT_PIN_PPS_RP48			RPOR5bits.RP48R		/* Assign RP48 as Output Pin */
#define OUT_PIN_PPS_RP49			RPOR5bits.RP49R		/* Assign RP49 as Output Pin */
#define OUT_PIN_PPS_RP54			RPOR6bits.RP54R		/* Assign RP54 as Output Pin */
#define OUT_PIN_PPS_RP55			RPOR6bits.RP55R		/* Assign RP55 as Output Pin */
#define OUT_PIN_PPS_RP56			RPOR7bits.RP56R		/* Assign RP56 as Output Pin */
#define OUT_PIN_PPS_RP57			RPOR7bits.RP57R		/* Assign RP57 as Output Pin */
#define OUT_PIN_PPS_RP69			RPOR8bits.RP69R		/* Assign RP69 as Output Pin */
#define OUT_PIN_PPS_RP70			RPOR8bits.RP70R		/* Assign RP70 as Output Pin */
#define OUT_PIN_PPS_RP81			RPOR9bits.RP81R		/* Assign RP81 as Output Pin */
#define OUT_PIN_PPS_RP97			RPOR9bits.RP97R		/* Assign RP97 as Output Pin */
#define OUT_PIN_PPS_RP113			RPOR10bits.RP113R		/* Assign RP113 as Output Pin */
#define OUT_PIN_PPS_RP118			RPOR10bits.RP118R		/* Assign RP118 as Output Pin */
#define OUT_PIN_PPS_RP120			RPOR11bits.RP120R		/* Assign RP120 as Output Pin */
#define OUT_PIN_PPS_RP125			RPOR11bits.RP125R		/* Assign RP125 as Output Pin */
#define OUT_PIN_PPS_RP126			RPOR12bits.RP126R		/* Assign RP126 as Output Pin */
#define OUT_PIN_PPS_RP127			RPOR12bits.RP127R		/* Assign RP127 as Output Pin */

#else
#define OUT_PIN_PPS_RP0				RPOR0bits.RP0R		/* Assign RP0 as Output Pin */
#define OUT_PIN_PPS_RP1				RPOR0bits.RP1R		/* Assign RP1 as Output Pin */
#define OUT_PIN_PPS_RP2				RPOR1bits.RP2R		/* Assign RP2 as Output Pin */
#define OUT_PIN_PPS_RP3				RPOR1bits.RP3R		/* Assign RP3 as Output Pin */
#define OUT_PIN_PPS_RP4				RPOR2bits.RP4R		/* Assign RP4 as Output Pin */
#define OUT_PIN_PPS_RP5				RPOR2bits.RP5R		/* Assign RP5 as Output Pin */
#define OUT_PIN_PPS_RP6				RPOR3bits.RP6R		/* Assign RP6 as Output Pin */
#define OUT_PIN_PPS_RP7				RPOR3bits.RP7R		/* Assign RP7 as Output Pin */
#define OUT_PIN_PPS_RP8				RPOR4bits.RP8R		/* Assign RP8 as Output Pin */
#define OUT_PIN_PPS_RP9				RPOR4bits.RP9R		/* Assign RP9 as Output Pin */
#define OUT_PIN_PPS_RP10			RPOR5bits.RP10R		/* Assign RP10 as Output Pin */
#define OUT_PIN_PPS_RP11			RPOR5bits.RP11R		/* Assign RP11 as Output Pin */
#define OUT_PIN_PPS_RP12			RPOR6bits.RP12R		/* Assign RP12 as Output Pin */
#define OUT_PIN_PPS_RP13			RPOR6bits.RP13R		/* Assign RP13 as Output Pin */
#define OUT_PIN_PPS_RP14			RPOR7bits.RP14R		/* Assign RP14 as Output Pin */
#define OUT_PIN_PPS_RP15			RPOR7bits.RP15R		/* Assign RP15 as Output Pin */
#define OUT_PIN_PPS_RP16			RPOR8bits.RP16R		/* Assign RP16 as Output Pin */
#define OUT_PIN_PPS_RP17			RPOR8bits.RP17R		/* Assign RP17 as Output Pin */
#define OUT_PIN_PPS_RP18			RPOR9bits.RP18R		/* Assign RP18 as Output Pin */
#define OUT_PIN_PPS_RP19			RPOR9bits.RP19R		/* Assign RP19 as Output Pin */
#define OUT_PIN_PPS_RP20			RPOR10bits.RP20R		/* Assign RP20 as Output Pin */
#define OUT_PIN_PPS_RP21			RPOR10bits.RP21R		/* Assign RP21 as Output Pin */
#define OUT_PIN_PPS_RP22			RPOR11bits.RP22R		/* Assign RP22 as Output Pin */
#define OUT_PIN_PPS_RP23			RPOR11bits.RP23R		/* Assign RP23 as Output Pin */
#define OUT_PIN_PPS_RP24			RPOR12bits.RP24R		/* Assign RP24 as Output Pin */
#define OUT_PIN_PPS_RP25			RPOR12bits.RP25R		/* Assign RP25 as Output Pin */

#endif

#define iPPSOutput(pin,fn)           pin=fn
#define PPSOutput(fn,pin)            iPPSOutput(pin,fn)
/*----------------------------------------------------------------------------------------------------*/

#define  PPSUnLock                   __builtin_write_OSCCONL(OSCCON & 0xbf) 
#define  PPSLock                     __builtin_write_OSCCONL(OSCCON | 0x40)

#endif /*__PPS_H */




