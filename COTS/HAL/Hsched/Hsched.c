/*
 * Hsched.c
 *
 *  Created on: Apr 2, 2022
 *      Author: Kishk
 */

#include <SERVICES/Std_types.h>
#include <SERVICES/Bit_utils.h>
#include <MCAL/Systick/Systick.h>
#include <HAL/Hsched/Hsched.h>
#include <HAL/Hsched/Hsched_cfg.h>
#include <HAL/Hsched/Hsched_prv.h>


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
Sched_tenuErrorStatus Sched_strregisterRunnable(Sched_tstrRunnable * Add_pstrRunnable, u32 Copy_u32Priority)
{
	/*DECLARE AN RETURN ERROR STATUS WITH INIT OK VALUE*/
	Sched_tenuErrorStatus Loc_enuReturnStatus	=	Sched_enuOk;
	/*CHECK IF THIS INDEX HAS NOT RUNNABLE*/
	if(Tasks[Copy_u32Priority] == NULL)
	{
		/*ADD THE RUNNABLE IN THE TASKS SCHED*/
		Tasks[Copy_u32Priority] = Add_pstrRunnable;
	}
	else
	{
		/*RETURN ERROR IF THERE'S AND PERIORITY IN THIS IDX*/
		Loc_enuReturnStatus = Sched_enuErrorPeriority;
	}
	/*RETURN THE ERROR STATUS*/
	return Loc_enuReturnStatus;
}

/*
 * Function:  Sched_vidInit
 * --------------------
 * INITIALIZE SCHEDULER
 *
 *
 */
void Sched_vidInit(void)
{
	/*INIT SYSTICK TIMER WITH DESIRED TICK IN MS*/
	Systick_Init(HSCHED_TICK_MS);
	/*INIT THE CALLBACK FUNCTION TO BE CALLED IN AFTER EVERY CYCLE*/
	Systick_vidSetCallBack(vidSched);

}

/*
 * Function:  Sched_vidInit
 * --------------------
 * START SCHEDULER
 *
 */
void Sched_vidStart(void)
{
	/*START THE SYSTICK*/
	Systick_vidStart();
	/*INFINITE LOOP*/
	while(HSCHED_TRUE);
}


/*
 * Function:  vidSched
 * --------------------
 * SYSTICK CALLBACK FUNCTION AFTER EVERY CYCLE FINISH
 * MAIN PURPOSE CALL THE TASK FUNCTIONS BASED ON THE PERIORITY
 *
 */
static void vidSched(void)
{
	/*DECLARE AN IDX ITER FOR THE LOOP*/
	u32 Loc_u32Idx;
	/*TIME TO BE SAVE STORY OF THE CYCLICK*/
	static volatile u32 timeMs;
	/*INCREMENT THE COUNTER BASED ON TICK*/
	if((u64) timeMs + HSCHED_TICK_MS > HSCHED_MAXIMUM_TIMEMS)
	{
		timeMs = HSCHED_TICK_MS;
	}
	else{
	timeMs+=HSCHED_TICK_MS;
	}
	/*LOOP TO CHECK WHICH TASK NEEDED TO BE EXECUTED*/
	for(Loc_u32Idx = HSCHED_ZERO ; Loc_u32Idx < HSCHED_MAXIMUM ; Loc_u32Idx++)
	{
		/*CHECK IF THE CURRENT INDEX NOT EQUAL NULL*/
		if(Tasks[Loc_u32Idx] != NULL)
		{
			/*CHECK IF THE CURRENT TIME COULD BE EXECUTE*/
			if(timeMs % Tasks[Loc_u32Idx]->cyclicTimeMs == HSCHED_ZERO)
			{
				/*CALL THE TASK CBF*/
				(Tasks[Loc_u32Idx]->Cbf)();
			}
		}
	}

}
