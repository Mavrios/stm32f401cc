/*
 * Systick.c
 *
 *  Created on: Mar 29, 2022
 *      Author: Kishk
 */



#include <SERVICES/Std_types.h>
#include <SERVICES/Bit_utils.h>
#include <SERVICES/stm32f401cc.h>
#include <MCAL/Systick/Systick.h>
#include <MCAL/Systick/Systick_cfg.h>
#include <MCAL/Systick/Systick_prv.h>

static SystickISR CallBack = NULL;
extern void
SysTick_Handler (void);

/*
 * Function:  Systick_Init
 * --------------------
 * INITIALIZE SYSTICK TIMER WITH DESIRED TIME IN MS
 *
 *  Copy_u32TimeMs: DESIRED TIME IN MILLISECOND MAXIMUM BASED ON THE CLK
 *
 */
void Systick_Init(u32 Copy_u32TimeMs)
{
#if SYSTICK_u32CLK_SRC == SYSTICK_u32AHB_DIV_BY_1
	/*CALCULATE HOW MANY TICK TO GET 1 MILLI*/
	u32 Loc_u32Clk = (SYSTICK_u32SYS_CLK / SYSTICK_u32AHB_DIV_BY_1) / SYSTICK_u32MILLI_SEC;
#elif SYSTICK_u32CLK_SRC == SYSTICK_u32AHB_DIV_BY_8
	u32 Loc_u32Clk = (SYSTICK_u32SYS_CLK / SYSTICK_u32AHB_CFG_DIV_BY_8) / SYSTICK_u32MILLI_SEC;
#endif
	/*ASSIGN THE VALUE INTO LOAD REGISTER*/
	SYSTICK->STK_LOAD = Copy_u32TimeMs * Loc_u32Clk;
	/*RESET STK VAL*/
	SYSTICK->STK_VAL  = SYSTICK_u32RESET ;
	/*CFG THE SYSTICK BASED IN PRE-BUILD CFG*/
	SYSTICK->STK_CTRL = SYSTICK_u32CLK_SRC;
}

/*
 * Function:  Systick_vidSetCallBack
 * --------------------
 * INITIALIZE SYSTICK TIMER ISR FUNCTIONS
 *
 *  Add_pfCallBackFunction: ADDRESS OF THE FUNCTION TO BE CALLED WHEN SYSTICK TIMER FINISHED
 *
 *	return: ERROR STATUS TO CHECK THE ERROR STATUS CHECK ENUM ABOVE
 */
Systick_tenuErrorStatus Systick_vidSetCallBack(SystickISR Add_pfCallBackFunction)
{
	Systick_tenuErrorStatus Loc_enuReturnStatus = Systick_enuOk;
	/*VALIDATE ON THE ADDRESS*/
	if(Add_pfCallBackFunction != NULL)
	{
		/*SAVE THE ADDRESS OF CALLBACK FUNCTION*/
		CallBack = Add_pfCallBackFunction;
	}
	else
	{
		Loc_enuReturnStatus = Systick_enuNullPointer;
	}

	return Loc_enuReturnStatus;
}

/*
 * Function:  Systick_vidStart
 * --------------------
 * START SYSTICK TIMER COUNTING
 * *
 */

void Systick_vidStart(void)
{
	SYSTICK->STK_CTRL |= SYSTICK_u32ON;
}

/*
 * Function:  SysTick_Handler
 * --------------------
 * ISR FUNCTIONS
 * *
 */
void __attribute__ ((section(".after_vectors"),weak))
SysTick_Handler (void)
{
	/*VALIDATE ON THE POINTER*/
	if(CallBack != NULL)
		/*CALL THE F TO P*/
		CallBack();
}
