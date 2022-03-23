/*
 * RCC.h
 *
 *  Created on: Mar 7, 2022
 *      Author: Kishk
 */

#ifndef RCC_H_
#define RCC_H_

/********************************************* MACROS *********************************************/
#define RCC_u8HSI_CLOCK 				0
#define RCC_u8HSE_CLOCK 				1
#define RCC_u8PLL_CLOCK 				2

#define RCC_u8CLK_OFF					((u8) 0)
#define RCC_u8CLK_ON					((u8) 1)

#define RCC_u8CLK_RDY					((u8) 0x01)
#define RCC_u8CLK_NOTRDY				((u8) 0x00)

#define RCC_u8BYPASS_ON					((u8) 0)
#define RCC_u8BYPASS_OFF				((u8) 1)

#define RCC_u8RCC_u8CLK_SECURITY_ON		((u8) 0)
#define RCC_u8CLK_SECURITY_OFF			((u8) 1)

#define RCC_u8DIVISION_BY_2 			((u8) 0)
#define RCC_u8DIVISION_BY_4 			((u8) 1)
#define RCC_u8DIVISION_BY_6 			((u8) 2)
#define RCC_u8DIVISION_BY_8 			((u8) 3)

#define RCC_u32APB1_NOT_DIVIDED			0xFFFFE3FF
#define RCC_u32APB1_DIV_BY_2			0x00001000
#define RCC_u32APB1_DIV_BY_4			0x00001400
#define RCC_u32APB1_DIV_BY_8			0x00001800
#define RCC_u32APB1_DIV_BY_16			0x00001C00

#define RCC_u32APB2_NOT_DIVIDED			0xFFFF1FFF
#define RCC_u32APB2_DIV_BY_2			0x00008000
#define RCC_u32APB2_DIV_BY_4			0x0000A000
#define RCC_u32APB2_DIV_BY_8			0x0000C000
#define RCC_u32APB2_DIV_BY_16			0x0000E000

#define RCC_u32AHB_NOT_DIVIDED			0xFFFFFF0F
#define RCC_u32AHB_DIV_BY_2				0x00000080
#define RCC_u32AHB_DIV_BY_4			    0x00000090
#define RCC_u32AHB_DIV_BY_8			    0x000000A0
#define RCC_u32AHB_DIV_BY_16			0x000000B0
#define RCC_u32AHB_DIV_BY_64			0x000000C0
#define RCC_u32AHB_DIV_BY_128			0x000000D0
#define RCC_u32AHB_DIV_BY_256			0x000000E0
#define RCC_u32AHB_DIV_BY_512			0x000000F0

#define RCC_u8APB1_BUS					((u8) 0)
#define RCC_u8APB2_BUS					((u8) 1)
#define RCC_u8AHB1_BUS					((u8) 2)
#define RCC_u8AHB2_BUS					((u8) 3)

#define RCC_u32AHB1_GPIOA				0x00000001
#define RCC_u32AHB1_GPIOB				0x00000002
#define RCC_u32AHB1_GPIOC				0x00000004
#define RCC_u32AHB1_GPIOD				0x00000008
#define RCC_u32AHB1_GPIOE				0x00000010
#define RCC_u32AHB1_GPIOH				0x00000080
#define RCC_u32AHB1_CRC					0x00001000
#define RCC_u32AHB1_DMA1				0x00200000
#define RCC_u32AHB1_DMA2				0x00400000

#define RCC_u32AHB2_OTGFS				0x00000080

#define RCC_u32APB1_TIM2				0x00000001
#define RCC_u32APB1_TIM3				0x00000002
#define RCC_u32APB1_TIM4				0x00000004
#define RCC_u32APB1_TIM5				0x00000008
#define RCC_u32APB1_WWDG				0x00000800
#define RCC_u32APB1_SPI2				0x00004000
#define RCC_u32APB1_SPI3				0x00008000
#define RCC_u32APB1_USART2				0x00020000
#define RCC_u32APB1_I2C1				0x00200000
#define RCC_u32APB1_I2C2				0x00400000
#define RCC_u32APB1_I2C3				0x00800000
#define RCC_u32APB1_PWR					0x10000000


#define RCC_u32APB2_TIM1				0x00000001
#define RCC_u32APB2_USART1				0x00000010
#define RCC_u32APB2_USART6				0x00000020
#define RCC_u32APB2_ADC1				0x00000100
#define RCC_u32APB2_SDIO				0x00000800
#define RCC_u32APB2_SPI1				0x00001000
#define RCC_u32APB2_SPI4				0x00002000
#define RCC_u32APB2_SYSCF				0x00004000
#define RCC_u32APB2_TIM9				0x00010000
#define RCC_u32APB2_TIM10				0x00020000
#define RCC_u32APB2_TIM11				0x00040000


/******************************************** TYPEDEF ********************************************/
typedef enum{
	RCC_enuOk = 0,
	RCC_enuErrorClock,
	RCC_enuErrorClkNotRdy,
	RCC_enuErrorContrlStatus,
	RCC_enuErrorSelectedSysClk,
	RCC_enuErrorNullPointer,
	RCC_enuErrorPLLOn,
	RCC_enuErrorMFactor,
	RCC_enuErrorNFactor,
	RCC_enuErrorPLLP,
	RCC_enuErrorPLLQ,
	RCC_enuErrorBus,
	RCC_enuErrorTimedOut,
	RCC_enuErrorBusPrescaler,
	RCC_enuErrorSelectedPllClk
}RCC_tenuErrorStatus;

typedef enum{
	RCC_enuPDivBy2,
	RCC_enuPDivBy4,
	RCC_enuPDivBy6,
	RCC_enuPDivBy8,
}RCC_tenuPLL_P;

typedef enum{
	RCC_enuQDivBy2 = 2,
	RCC_enuQDivBy3,
	RCC_enuQDivBy4,
	RCC_enuQDivBy5,
	RCC_enuQDivBy6,
	RCC_enuQDivBy7,
	RCC_enuQDivBy8,
	RCC_enuQDivBy9,
	RCC_enuQDivBy10,
	RCC_enuQDivBy11,
	RCC_enuQDivBy12,
	RCC_enuQDivBy13,
	RCC_enuQDivBy14,
	RCC_enuQDivBy15,
}RCC_tenuPLL_Q;


typedef struct{
	u32				RCC_u32DivisionFactor_M;
	RCC_tenuPLL_P	RCC_enuPLL_P;
	RCC_tenuPLL_Q	RCC_enuPLL_Q;
	u16				RCC_u16MultiplyFactor_N;
	u8				RCC_u8SourceClock;
}RCC_tstrPllCfg;

/******************************************* PROTOTYPES *******************************************/

/*
 * Function:  RCC_enuControlSysClock
 * --------------------
 * SELECT THE SYSTEM CLK
 *
 *  Copy_u8Clock: DESIRED CLK --> OPTIONS -->(RCC_u8HSI_CLOCK - RCC_u8HSE_CLOCK - RCC_u8PLL_CLOCK)
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK RCC_tenuErrorStatus ERROR ABOVE.
 */
RCC_tenuErrorStatus RCC_enuControlSysClock(u8 Copy_u8Clock);
/*
 * Function:  RCC_enuControlClock
 * --------------------
 * CONTROL THE CLK (ON - OFF)
 *
 *  Copy_u8Clock: DESIRED CLK --> OPTIONS -->(RCC_u8HSI_CLOCK - RCC_u8HSE_CLOCK - RCC_u8PLL_CLOCK)
 *	Copy_u8Status: DESIRED STATE --> OPTIONS --> (RCC_u8CLK_OFF - RCC_u8CLK_ON)
 *
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK RCC_tenuErrorStatus ERROR ABOVE.
 */
RCC_tenuErrorStatus RCC_enuControlClock(u8 Copy_u8Clock ,u8 Copy_u8Status);
/*
 * Function:  RCC_enuGetClockRdyStatus
 * --------------------
 * CHECK THE CLK STATUS IF IT'S RDY OR NOT!
 *
 *  Copy_u8Clock: DESIRED CLK --> OPTIONS -->(RCC_u8HSI_CLOCK - RCC_u8HSE_CLOCK - RCC_u8PLL_CLOCK)
 *	Add_pu8RtrnRdyStatus: ADDRESS OF VARIABLE WITH TYPE (u8) TO STORE THE RESULT IN THIS ADDRESS
 *
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK RCC_tenuErrorStatus ERROR ABOVE.
 */
RCC_tenuErrorStatus RCC_enuGetClockRdyStatus(u8 Copy_u8Clock , pu8 Add_pu8RtrnRdyStatus);
/*
 * Function:  RCC_enuConfigurePLL
 * --------------------
 * CONFIGURE PLL CLOCK
 * RESTRICTIONS : (THE PLL SHOULD BE OFF).
 *
 *  Copy_strCfg(STRUCT): STRUCT CONTAIN ALL DESIRED OPTIONS:-
 *
 *  --> Copy_strCfg.RCC_u32DivisionFactor_M: (SHOULD NOT EXCEED "63 DECIMAL")
 *  Caution: The software has to set these bits correctly to ensure that the VCO input frequency
 *	ranges from 1 to 2 MHz. It is recommended to select a frequency of 2 MHz to limit PLL jitter
 *
 *	--> Copy_strCfg.RCC_u16MultiplyFactor_N: (SHOULD NOT EXCEED "432 DECIMAL")
 *	The software has to set these bits correctly to ensure that the VCO output
 * 	frequency is between 192 and 432 MHz.
 *
 * 	-->Copy_strCfg.RCC_enuPLL_P:	ENUM OF TYPE (RCC_tenuPLL_P) MUST CHOOSE ONE OF ENUM OPTIONS.
 *
 * 	-->Copy_strCfg.RCC_u8SourceClock: DESIRED CLK --> OPTIONS -->
 * 	(RCC_u8HSI_CLOCK - RCC_u8HSE_CLOCK - RCC_u8PLL_CLOCK)
 *
 * 	-->Copy_strCfg.RCC_enuPLL_Q:	ENUM OF TYPE (RCC_tenuPLL_Q) MUST CHOOSE ONE OF ENUM OPTIONS.
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK RCC_tenuErrorStatus ERROR ABOVE.
 */
RCC_tenuErrorStatus RCC_enuConfigurePLL(RCC_tstrPllCfg Copy_strCfg);
/*
 * Function:  RCC_enuControlBusPrescaler
 * --------------------
 * CONFIGURE BUS PRESCALER
 *
 *  Copy_u32Prescaler: DESIRED CLK --> OPTIONS -->
 *  (RCC_u32APB1_DIV_BY_x - RCC_u32APB2_DIV_BY_x - RCC_u32AHB_DIV_BY_x) "REPLACE X WITH DESIERED OPTION
 *	(RCC_u32APB1_NOT_DIVIDED  - RCC_u32APB2_NOT_DIVIDED - RCC_u32AHB_NOT_DIVIDED)
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK RCC_tenuErrorStatus ERROR ABOVE.
 */
RCC_tenuErrorStatus RCC_enuControlBusPrescaler(u32 Copy_u32Prescaler);
/*
 * Function:  RCC_enuEnablePeripheralClk
 * --------------------
 * ENABLE PERIPHERAL SPECIFIC PERIPHERAL CLK
 *
 *  Copy_u8Bus: DESIRED CLK --> OPTIONS --> (RCC_u8APB1_BUS - RCC_u8APB2_BUS - RCC_u8AHB_BUS)
 *	Copy_u32Peripheral: DESIRED PERIPHERAL OPTIONS -->
 *	(RCC_u32AHB1_xxxx - RCC_u32AHB2_xxxx - RCC_u32APB1_xxxx - RCC_u32APB2_xxxx)
 *
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK RCC_tenuErrorStatus ERROR ABOVE.
 */
RCC_tenuErrorStatus RCC_enuEnablePeripheralClk(u8 Copy_u8Bus , u32 Copy_u32Peripheral);
/*
 * Function:  RCC_enuDisablePeripheralClk
 * --------------------
 * DISABLE PERIPHERAL SPECIFIC PERIPHERAL CLK
 *
 *  Copy_u8Bus: DESIRED CLK --> OPTIONS --> (RCC_u8APB1_BUS - RCC_u8APB2_BUS - RCC_u8AHB_BUS)
 *	Copy_u32Peripheral: DESIRED PERIPHERAL OPTIONS -->
 *	(RCC_u32AHB1_xxxx - RCC_u32AHB2_xxxx - RCC_u32APB1_xxxx - RCC_u32APB2_xxxx)
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK RCC_tenuErrorStatus ERROR ABOVE.
 */
RCC_tenuErrorStatus RCC_enuDisablePeripheralClk(u8 Copy_u8Bus , u32 Copy_u32Peripheral);

#endif /* RCC_H_ */
