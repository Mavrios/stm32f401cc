/*
 * hled.h
 *
 *  Created on: Mar 24, 2022
 *      Author: Kishk
 */

#ifndef HAL_LED_HLED_H_
#define HAL_LED_HLED_H_
#include <HAL/LED/hLed_cfg.h>

/********************************************* MACROS *********************************************/
#define LED_u8ACTIVE_STATE_LOW	((u8) 1)
#define LED_u8ACTIVE_STATE_HIGH	((u8) 0)


#define LED_u8_STATE_ON			((u8) 1)
#define LED_u8_STATE_OFF		((u8) 0)

/******************************************** TYPEDEF ********************************************/

typedef enum{
	Led_Ok,
	Led_Nok
}Led_tenuErrorStatus;

typedef struct{
	void * Port;
	u16 Pin;
	u8 Active_State;
}Led_Cnfg_t;

/******************************************* PROTOTYPES *******************************************/
/*
 * Function:  Led_init
 * --------------------
 * Led Pins Initialization.
 * *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK Led_tenuErrorStatus ERROR ENUM.
 */
extern Led_tenuErrorStatus Led_init(void);
/*
 * Function:  Led_setState
 * --------------------
 * LED CHANGE STATUS TO BE ON OR OFF
 *
 * Copy_u16LedNum: LED NUMBER TO CHANGE IT'S STATE
 * Copy_u8LedState: DESIRED STATE
 *
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK Led_tenuErrorStatus ERROR ENUM.
 */
extern Led_tenuErrorStatus Led_setState(u16 Copy_u16LedNum , u8 Copy_u8LedState);

/************************************ EXTERN USED VARIABLES *******************************************/
extern const Led_Cnfg_t Leds[];
#endif /* HAL_LED_HLED_H_ */
