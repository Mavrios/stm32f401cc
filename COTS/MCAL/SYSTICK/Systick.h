/*
 * Systick.h
 *
 *  Created on: Mar 29, 2022
 *      Author: Kishk
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

/******************************************** TYPEDEF *********************************************/

typedef void (*SystickISR) (void);

typedef enum{
	Systick_enuOk,
	Systick_enuNullPointer
}Systick_tenuErrorStatus;

/******************************************** MACROS **********************************************/
#define SYSTICK_u32AHB_DIV_BY_1			0x06
#define SYSTICK_u32AHB_DIV_BY_8			0x02


/******************************************* PROTOTYPES *******************************************/

/*
 * Function:  Systick_Init
 * --------------------
 * INITIALIZE SYSTICK TIMER WITH DESIRED TIME IN MS
 *
 *  Copy_u32TimeMs: DESIRED TIME IN MILLISECOND MAXIMUM BASED ON THE CLK
 *
 */
void Systick_Init(u32 Copy_u32TimeMs);
/*
 * Function:  Systick_vidSetCallBack
 * --------------------
 * INITIALIZE SYSTICK TIMER ISR FUNCTIONS
 *
 *  Add_pfCallBackFunction: ADDRESS OF THE FUNCTION TO BE CALLED WHEN SYSTICK TIMER FINISHED
 *
 *	return: ERROR STATUS TO CHECK THE ERROR STATUS CHECK ENUM ABOVE
 */
Systick_tenuErrorStatus Systick_vidSetCallBack(SystickISR Add_pfCallBackFunction);
/*
 * Function:  Systick_vidStart
 * --------------------
 * START SYSTICK TIMER COUNTING
 * *
 */
void Systick_vidStart(void);



#endif /* SYSTICK_H_ */
