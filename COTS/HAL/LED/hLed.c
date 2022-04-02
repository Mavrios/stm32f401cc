/*
 * Led.c
 *
 *  Created on: Mar 24, 2022
 *      Author: Kishk
 */


#include <SERVICES/Std_types.h>
#include <SERVICES/Bit_utils.h>

#include <HAL/LED/hLed.h>
#include <HAL/LED/hLed_cfg.h>
#include <MCAL/GPIO/Gpio.h>
#include <MCAL/RCC/RCC.h>


#define RCC_ENABLE_PERI()			switch((u32)Leds[Loc_u8Iterator].Port){\
		case (u32) GPIO_pvPORTA:\
			RCC_GPIOEN|= RCC_u32AHB1_GPIOA;\
			break;\
		case (u32) GPIO_pvPORTB:\
			RCC_GPIOEN|= RCC_u32AHB1_GPIOB;\
			break;\
		case (u32) GPIO_pvPORTC:\
			RCC_GPIOEN|= RCC_u32AHB1_GPIOC;\
			break;\
		case (u32) GPIO_pvPORTD:\
			RCC_GPIOEN|= RCC_u32AHB1_GPIOD;\
			break;\
		case (u32) GPIO_pvPORTE:\
			RCC_GPIOEN|= RCC_u32AHB1_GPIOE;\
			break;\
		case (u32) GPIO_pvPORTH:\
			RCC_GPIOEN|= RCC_u32AHB1_GPIOH;\
			break;\
		}

/*
 * Function:  Led_init
 * --------------------
 * Led Pins Initialization.
 * *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK Led_tenuErrorStatus ERROR ENUM.
 */
extern Led_tenuErrorStatus Led_init(void)
{
	/*DECLARE RETURN ERROR STATUS VARIABLE*/
	Led_tenuErrorStatus Loc_enuReturnStatus = Led_Ok;
	/*DECLARE ITERATOR FOR LOOPS*/
	u8 Loc_u8Iterator;
	/*DECLARE MASK TO BE USED FOR RCC*/
	u32 RCC_GPIOEN	= 0;
	/*DECLARE STRUCT TO SET PIN CONFIGS*/
	GpioPinCfg_t Loc_strCfg;
	/*SET PIN CONFIGS*/
	Loc_strCfg.GPIO_u32Mode=GPIO_u32MODE_OUTPUT_PP;
	Loc_strCfg.GPIO_u32Speed=GPIO_u8SPEED_VERY_HIGH;

	/*LOOP TO CHECK USED GPIO TO ENABLE THEIR CLK*/
	for(Loc_u8Iterator = 0 ; Loc_u8Iterator< NUM_OF_LEDS ; Loc_u8Iterator++)
	{
		/*SWITCH CASE TO GET THE MASK*/
		RCC_ENABLE_PERI();
	}
	/*ENABLE CLK FOR USED GPIO*/
	RCC_enuEnablePeripheralClk(RCC_u8AHB1_BUS,RCC_GPIOEN);
	/*LOOP TO SET LED PINS CONFIGURATIONS*/
	for(Loc_u8Iterator = 0 ; Loc_u8Iterator< NUM_OF_LEDS ; Loc_u8Iterator++)
	{
		Loc_strCfg.GPIO_pvPort  = Leds[Loc_u8Iterator].Port;
		Loc_strCfg.GPIO_u16Pin  = Leds[Loc_u8Iterator].Pin;
		Gpio_enuInit(&Loc_strCfg);
	}
	/*RETURN THE ERROR STATUS*/
	return Loc_enuReturnStatus;
}

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

extern Led_tenuErrorStatus Led_setState(u16 Copy_u16LedNum , u8 Copy_u8LedState)
{
	/*DECLARE RETURN ERROR VARIABLE*/
	Led_tenuErrorStatus Loc_enuReturnStatus = Led_Ok;
	/*STRUCT TO SET LED CONFIGURATIONS*/
	GpioPinCfg_t Loc_strCfg;
	Loc_strCfg.GPIO_pvPort  = Leds[Copy_u16LedNum].Port;
	Loc_strCfg.GPIO_u16Pin  = Leds[Copy_u16LedNum].Pin;
	Gpio_setPinValue(&Loc_strCfg , Copy_u8LedState ^ Leds[Copy_u16LedNum].Active_State);
	return Loc_enuReturnStatus;
}
