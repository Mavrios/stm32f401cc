/*
 * Hsched.h
 *
 *  Created on: Apr 2, 2022
 *      Author: Kishk
 */

#ifndef HSCHED_H_
#define HSCHED_H_

/******************************************** TYPEDEF *********************************************/
typedef void (*Sched_Callback)(void);

typedef struct{
	Sched_Callback Cbf;
	u32 cyclicTimeMs;
}Sched_tstrRunnable;

typedef enum
{
	Sched_enuOk,
	Sched_enuErrorPeriority,
}Sched_tenuErrorStatus;

/******************************************* PROTOTYPES *******************************************/
/*
 * Function:  Sched_vidInit
 * --------------------
 * INITIALIZE SCHEDULER
 *
 *
 */
void Sched_vidInit(void);
/*
 * Function:  Sched_strregisterRunnable
 * --------------------
 * STORE SPECIFIC RUNNABLE BASED ON THE PERIORITY
 *
 *  Add_pstrRunnable: POINTER TO STRUCT HAS CALLBACKFUNC AND CYCLICKTIMEMS
 *  Copy_u32Priority: DESIERED PERIORITY
 *  NOTE: CAN NOT HAVE TO RUNNABLE WITH SAME PERIORITY
 *
 *	return: Sched_tenuErrorStatus TO CHECK ERROR TYPES CHECK ENUM
 */
Sched_tenuErrorStatus Sched_strregisterRunnable(Sched_tstrRunnable * Add_pstrRunnable, u32 Copy_u32Priority);
/*
 * Function:  Sched_vidInit
 * --------------------
 * START SCHEDULER
 *
 */
void Sched_vidStart(void);

#endif /* HSCHED_H_ */
