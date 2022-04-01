/*
 * Switch.h
 *
 *  Created on: Mar 25, 2022
 *      Author: Kishk
 */

#ifndef HAL_SWITCH_SWITCH_H_
#define HAL_SWITCH_SWITCH_H_
#include <HAL/Switch/Switch_cfg.h>


/********************************************* MACROS *********************************************/

#define SWITCH_u8_STATE_PRESSED		((u8) 1)
#define SWITCH_u8_STATE_NOT_PRESSED	((u8) 0)

/******************************************** TYPEDEF ********************************************/
typedef enum{
	Switch_Ok,
	Switch_Nok
}Switch_tenuErrorStatus;

typedef struct{
	void * Port;
	u16 Pin;
	u32 Pull_State;
}Switch_Cnfg_t;
/******************************************* PROTOTYPES *******************************************/
/*
 * Function:  Switch_init
 * --------------------
 * SWITCH Pins Initialization.
 * *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK Switch_tenuErrorStatus ERROR ENUM.
 */

extern Switch_tenuErrorStatus Switch_init(void);
/*
 * Function:  Switch_readState
 * --------------------
 * READ SWITCH CURRENT STATE
 *
 * Copy_u16SwitchNum: SWITCH NUMBER TO READ IT'S STATE
 * Copy_u8SwitchState: POINTER TO RETURN THE SWITCH STATE.
 *
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK Switch_tenuErrorStatus ERROR ENUM.
 */
extern Switch_tenuErrorStatus Switch_readState(u16 Copy_u16SwitchNum , u8 *Copy_u8SwitchState);

/************************************ EXTERN USED VARIABLES *******************************************/
const Switch_Cnfg_t Switchs [NUM_OF_SWITCH];
#endif /* HAL_SWITCH_SWITCH_H_ */
