/*
 * Switch.c
 *
 *  Created on: Mar 25, 2022
 *      Author: Kishk
 */

#include <SERVICES/Std_types.h>
#include <SERVICES/Bit_utils.h>
#include <MCAL/RCC.h>
#include <MCAL/Gpio.h>
#include <HAL/Switch/Switch.h>

#define RCC_ENABLE_PERI()			switch((u32)Switchs[Loc_u8Iterator].Port){\
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
 * Function:  Switch_init
 * --------------------
 * SWITCH Pins Initialization.
 * *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK Switch_tenuErrorStatus ERROR ENUM.
 */
extern Switch_tenuErrorStatus Switch_init(void)
{
	/*DEFINE ERROR STATUS FOR RETURN*/
	Switch_tenuErrorStatus Loc_enuReturnStatus = Switch_Ok;
	/*DECLARE ITER FOR LOOP USE*/
	u8 Loc_u8Iterator;
	/*DECLARE GPIO CNFG STRUCT*/
	GpioPinCfg_t Loc_strCfg;
	/*DECLARE VARIABLE TO SAVE USED PORTS TO EN THEIR CLK*/
	u32 RCC_GPIOEN	= 0;
	Loc_strCfg.GPIO_u32Speed=GPIO_u8SPEED_VERY_HIGH;

	/*LOOP TO CHECK USED GPIO TO ENABLE THEIR CLK*/
	for(Loc_u8Iterator = 0 ; Loc_u8Iterator<NUM_OF_SWITCH ; Loc_u8Iterator++)
	{
		/*SWITCH CASE TO GET THE MASK*/
		RCC_ENABLE_PERI();
	}
	/*ENABLE CLK FOR USED GPIO*/
	RCC_enuEnablePeripheralClk(RCC_u8AHB1_BUS,RCC_GPIOEN);
	/*LOOP TO SET SWITCH PINS CONFIGURATIONS*/
	for(Loc_u8Iterator = 0 ; Loc_u8Iterator< NUM_OF_SWITCH ; Loc_u8Iterator++)
	{
		Loc_strCfg.GPIO_u32Mode = Switchs[Loc_u8Iterator].Pull_State;
		Loc_strCfg.GPIO_pvPort  = Switchs[Loc_u8Iterator].Port;
		Loc_strCfg.GPIO_u16Pin  = Switchs[Loc_u8Iterator].Pin;
		Gpio_enuInit(&Loc_strCfg);
	}
	return Loc_enuReturnStatus;
}

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

extern Switch_tenuErrorStatus Switch_readState(u16 Copy_u16SwitchNum , u8 *Copy_u8SwitchState)
{
	/*DEFINE ERROR STATUS FOR RETURN*/
	Switch_tenuErrorStatus Loc_enuReturnStatus = Switch_Ok;
	/*DECLARE GPIO CNFG STRUCT*/
	GpioPinCfg_t Loc_strCfg;
	/*DECLARE VARIABLE TO STORE THE PIN VALUE*/
	u32 Loc_u32Result = 0;
	/*SET SWITCH CNFG*/
	Loc_strCfg.GPIO_pvPort  = Switchs[Copy_u16SwitchNum].Port;
	Loc_strCfg.GPIO_u16Pin  = Switchs[Copy_u16SwitchNum].Pin;
	/*READ PIN VALUE*/
	Gpio_ReadPinValue(&Loc_strCfg , &Loc_u32Result);
	if(Switchs[Copy_u16SwitchNum].Pull_State == GPIO_u32MODE_INPUT_PU)
	{
		*Copy_u8SwitchState = (u8) !Loc_u32Result;
	}
	else
	{
		*Copy_u8SwitchState = (u8) Loc_u32Result;
	}
	return Loc_enuReturnStatus;
}
