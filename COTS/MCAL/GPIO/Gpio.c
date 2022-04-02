/*
 * Gpio.c
 *
 *  Created on: Mar 14, 2022
 *      Author: Kishk
 */

#include <SERVICES/Std_types.h>
#include <SERVICES/Bit_utils.h>
#include <SERVICES/stm32f401cc.h>
#include <MCAL/GPIO/Gpio.h>
#include <MCAL/GPIO/Gpio_prv.h>

/*
 * Function:  Gpio_enuInit
 * --------------------
 * INITIALIZE PIN CONFIGURATION
 *
 *  Add_strGpioCfg: DESIRED CONFIGURATION --> CONFIGURATIONS -->(GPIO_u64Mode - GPIO_u64Pull - GPIO_u64Speed)
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK GpioErrorStatus_t ERROR ABOVE.
 */
GpioErrorStatus_t Gpio_enuInit(GpioPinCfg_t * Add_strGpioCfg) {
	/*DECALRE VARAIBLE TO STORE PIN AND PORT*/
	u32 Loc_TmpMdOdPr;
	u8 Loc_u8Iterator = GPIO_ZERO;
	GPIO_RegDef_t * Loc_AddPort = Add_strGpioCfg->GPIO_pvPort;

	/*DEFINE RETURN ERROR STATUS ENUM VARIABLE*/
	GpioErrorStatus_t Loc_enuReturnError = Gpio_enuOk;
	/*CHECK IF THE ADDRESS OF CFG IS NULL*/
	if (Add_strGpioCfg == NULL) {
		Loc_enuReturnError = Gpio_enuErrorNullPointer;
	} else {
		for (Loc_u8Iterator = GPIO_ZERO; Loc_u8Iterator <= GPIO_u8_PINS;
				Loc_u8Iterator++) {
			if (Add_strGpioCfg->GPIO_u16Pin
					& (GPIO_PIN_MSK << Loc_u8Iterator)) {

				/*APPLY MSK TO GET THE MODE*/
				Loc_TmpMdOdPr = Add_strGpioCfg->GPIO_u32Mode & GPIO_MODE_MSK;
				/*SET THE MODE WITH DESIRED VALUE*/
				Loc_AddPort->GPIOx_MODER &= ~(GPIO_u32MODE_CLR_MSK
						<< (Loc_u8Iterator * GPIO_u8DOUBLE_BIT));
				Loc_AddPort->GPIOx_MODER |= Loc_TmpMdOdPr
						<< (Loc_u8Iterator * GPIO_u8DOUBLE_BIT);
				/*APPLY MSK TO GET THE OTY*/
				Loc_TmpMdOdPr = (Add_strGpioCfg->GPIO_u32Mode & GPIO_OTY_MSK)
						>> GPIO_OTY_SHFT;
				/*SET THE OTY WITH DESIRED VALUE*/
				Loc_AddPort->GPIOx_OTYPER &= (u32) ~(GPIO_u8PP_OD
						<< Loc_u8Iterator);
				Loc_AddPort->GPIOx_OTYPER |= Loc_TmpMdOdPr << Loc_u8Iterator;
				/*APPLY MSK TO GET THE PULL UP AND PULL DOWN RESISTOR*/
				Loc_TmpMdOdPr = (Add_strGpioCfg->GPIO_u32Mode & GPIO_PUPDR_MSK)
						>> GPIO_PUPD_SHFT;
				/*SET THE PUPD WITH DESIRED VALUE*/
				Loc_AddPort->GPIOx_PUPDR &= (u32) ~(GPIO_u8PULL_CLR_MSK
						<< (Loc_u8Iterator * GPIO_u8DOUBLE_BIT));
				Loc_AddPort->GPIOx_PUPDR |= Loc_TmpMdOdPr
						<< (Loc_u8Iterator * GPIO_u8DOUBLE_BIT);
				/*SET THE SPEED WITH DESIRED VALUE*/
				Loc_AddPort->GPIOx_OSPEEDR &= (u32) ~(GPIO_u8SPEED_CLR_MSK
						<< (Loc_u8Iterator * GPIO_u8DOUBLE_BIT));
				Loc_AddPort->GPIOx_OSPEEDR |= (u32) (GPIO_u8SPEED_CLR_MSK
						<< (Loc_u8Iterator * GPIO_u8DOUBLE_BIT));
			}
		}

	}
	return Loc_enuReturnError;
}

/*
 * Function:  Gpio_setPinValue
 * --------------------
 * SETTING PIN VALUE WITH HIGH OR LOW
 *
 *  Add_strGpioCfg: DESIRED CONFIGURATION
 *  Copy_u8Value : DESIRED VALUE ( GPIO_u32LOW - GPIO_u32HIGH )
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK GpioErrorStatus_t ERROR ABOVE.
 */
GpioErrorStatus_t Gpio_setPinValue(GpioPinCfg_t * Add_strGpioCfg,
		u32 Copy_u8Value) {
	/*DECALRE VARAIBLE TO STORE PIN AND PORT*/
	GPIO_RegDef_t * Loc_AddPort = Add_strGpioCfg->GPIO_pvPort;
	/*DEFINE RETURN ERROR STATUS ENUM VARIABLE*/
	GpioErrorStatus_t Loc_enuReturnError = Gpio_enuOk;
	/*STORE PIN AND PORT*/
	/*CHECK IF THE ADDRESS OF CFG IS NULL*/
	if (Add_strGpioCfg == NULL) {
		Loc_enuReturnError = Gpio_enuErrorNullPointer;
	} else {

		/*SWITCH TO DESIRED VALUE*/
		switch (Copy_u8Value) {
		case GPIO_u32LOW:
			/*ASSIGN PIN TO LOW*/
			Loc_AddPort->GPIOx_BSRR = (u32) (Add_strGpioCfg->GPIO_u16Pin
					<< (GPIO_u8VALUE_RST_MSK));
			break;

		case GPIO_u32HIGH:
			/*ASSIGN PIN TO HIGH*/
			Loc_AddPort->GPIOx_BSRR = Add_strGpioCfg->GPIO_u16Pin;
			break;
			/*ELSE ASSIGN ERROR*/
		default:
			Loc_enuReturnError = Gpio_enuErrorValue;
			break;

		}

	}
	return Loc_enuReturnError;
}
/*
 * Function:  Gpio_setPinPortValue
 * --------------------
 * SETTING PIN VALUE WITH HIGH OR LOW
 *
 *  Copy_u8Port: DESIRED PORT (GPIO_u8PORTA - GPIO_u8PORTB - GPIO_u8PORTC - GPIO_u8PORTD - GPIO_u8PORTE - GPIO_u8PORTH)
 *  Copy_u8Pin : DESIRED PIN START FROM GPIO_u8PIN_00 --> GPIO_u8PIN_15
 *  Copy_u8Value : DESIRED VALUE ( GPIO_u32LOW - GPIO_u32HIGH )
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK GpioErrorStatus_t ERROR ABOVE.
 */
GpioErrorStatus_t Gpio_setPinPortValue(void * GPIO_pvPort, u16 Copy_u16Pin,
		u32 Copy_u8Value) {
	GPIO_RegDef_t * Loc_AddPort = GPIO_pvPort; /*DEFINE RETURN ERROR STATUS ENUM VARIABLE*/
	/*DEFINE RETURN ERROR STATUS ENUM VARIABLE*/
	GpioErrorStatus_t Loc_enuReturnError = Gpio_enuOk;
	/*SWITCH TO DESIRED VALUE*/
	switch (Copy_u8Value) {
	case GPIO_u32LOW:
		/*ASSIGN PIN TO LOW*/
		Loc_AddPort->GPIOx_BSRR = (u32) (Copy_u16Pin << (GPIO_u8VALUE_RST_MSK));
		break;

	case GPIO_u32HIGH:
		/*ASSIGN PIN TO HIGH*/
		Loc_AddPort->GPIOx_BSRR = (Copy_u16Pin);

		break;
		/*ELSE ASSIGN ERROR*/
	default:
		Loc_enuReturnError = Gpio_enuErrorValue;
		break;

	}

	return Loc_enuReturnError;
}
/*
 * Function:  Gpio_ReadPinValue
 * --------------------
 * READ PIN VALUE HIGH OR LOW
 *
 *  Add_strGpioCfg: PIN CONFIGURATION
 *  Add_pu32Value : ADDRESS OF VARIABLE WILL SET THE RESULT ON THIS ADDRESS
 *  WILL RETURN GPIO_u32LOW OR GPIO_u32HIGH
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK GpioErrorStatus_t ERROR ABOVE.
 */
GpioErrorStatus_t Gpio_ReadPinValue(GpioPinCfg_t * Add_strGpioCfg,
		pu32 Add_pu32Value) {
	/*DECALRE VARAIBLE TO STORE PIN AND PORT*/
	GPIO_RegDef_t * Loc_AddPort = Add_strGpioCfg->GPIO_pvPort;

	/*DEFINE RETURN ERROR STATUS ENUM VARIABLE*/
	GpioErrorStatus_t Loc_enuReturnError = Gpio_enuOk;
	/*CHECK IF THE ENTERED MODE ADDRESS WITH NULL*/
	if (Add_strGpioCfg == NULL || Add_pu32Value == NULL) {
		Loc_enuReturnError = Gpio_enuErrorNullPointer;
	} else {
		if (Loc_AddPort->GPIOx_IDR & Add_strGpioCfg->GPIO_u16Pin) {
			/*ASSIGN THE RESULT TO THE PASSED ADDRESS*/
			*Add_pu32Value = GPIO_u32HIGH;
		} else {
			/*ASSIGN THE RESULT TO THE PASSED ADDRESS*/
			*Add_pu32Value = GPIO_u32LOW;
		}

	}
	return Loc_enuReturnError;
}

/*
 * Function:  Gpio_ReadPinPortValue
 * --------------------
 * READ PIN VALUE HIGH OR LOW
 *
 *  Copy_u8Port: DESIRED PORT (GPIO_u8PORTA - GPIO_u8PORTB - GPIO_u8PORTC - GPIO_u8PORTD - GPIO_u8PORTE - GPIO_u8PORTH)
 *  Copy_u8Pin : DESIRED PIN START FROM GPIO_u8PIN_00 --> GPIO_u8PIN_15
 *  Add_pu32Value : ADDRESS OF VARIABLE WILL SET THE RESULT ON THIS ADDRESS
 *  WILL RETURN GPIO_u32LOW OR GPIO_u32HIGH
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK GpioErrorStatus_t ERROR ABOVE.
 */
GpioErrorStatus_t Gpio_ReadPinPortValue(void * GPIO_pvPort, u16 Copy_u16Pin,
		pu32 Add_pu32Value) {
	/*DEFINE AN LOCAL ARR TO EZ ACCESS GPIO REGISTER BASED ON PORT INDEX*/
	GPIO_RegDef_t * Loc_AddPort = GPIO_pvPort;

	/*DEFINE RETURN ERROR STATUS ENUM VARIABLE*/
	GpioErrorStatus_t Loc_enuReturnError = Gpio_enuOk;

	/*CHECK IF THE ENTERED ADDRESS IS NULL*/
	if (Add_pu32Value == NULL) {
		Loc_enuReturnError = Gpio_enuErrorNullPointer;
	} else {
		/*ASSIGN THE RESULT TO THE PASSED ADDRESS*/
		if (Loc_AddPort->GPIOx_IDR & Copy_u16Pin) {
			/*ASSIGN THE RESULT TO THE PASSED ADDRESS*/
			*Add_pu32Value = GPIO_u32HIGH;
		} else {
			/*ASSIGN THE RESULT TO THE PASSED ADDRESS*/
			*Add_pu32Value = GPIO_u32LOW;
		}
	}
	return Loc_enuReturnError;
}
/*
 * Function:  Gpio_SetAlternateFunc
 * --------------------
 * SELECT THE DESIRED ALTERNATE FUNCTION SPECIFIC PIN
 *
 *  Add_strGpioCfg: PIN CONFIGURATION
 *  Copy_pu32Function : THE DESIRED ALTERERNATE FUNCTION --> OPTIONS -->
 *  START FROM GPIO_u8ALTERNATE_FUNC_00 --> GPIO_u8ALTERNATE_FUNC_15.
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK GpioErrorStatus_t ERROR ABOVE.
 */
GpioErrorStatus_t Gpio_SetAlternateFunc(GpioPinCfg_t * Add_strGpioCfg,
		u8 Copy_u8Function) {
	/*DECALRE VARAIBLE TO STORE PIN */
	u8 Loc_u8Iterator;
	GPIO_RegDef_t * Loc_AddPort = Add_strGpioCfg->GPIO_pvPort;

	/*DEFINE RETURN ERROR STATUS ENUM VARIABLE*/
	GpioErrorStatus_t Loc_enuReturnError = Gpio_enuOk;

	/*CHECK IF THE ADDRESS IS NULL*/
	if (Add_strGpioCfg == NULL) {
		Loc_enuReturnError = Gpio_enuErrorNullPointer;
	} else {
		for (Loc_u8Iterator = GPIO_ZERO; Loc_u8Iterator <= GPIO_u8_PINS;
				Loc_u8Iterator++) {
			if (Add_strGpioCfg->GPIO_u16Pin
					& (GPIO_PIN_MSK << Loc_u8Iterator)) {
				/*CHECK IF THE PIN IN L REGISTER*/
				if (Loc_u8Iterator <= GPIO_u8LPINS_MSK) {
					Loc_AddPort->GPIOx_AFRL &= (u32) ~(GPIO_u8ALTERNATE_CLR_MSK
							<< (Loc_u8Iterator * GPIO_u8QUADRO_BIT));
					Loc_AddPort->GPIOx_AFRL |= (u32) (Copy_u8Function
							<< (Loc_u8Iterator * GPIO_u8QUADRO_BIT));
				} else if (Loc_u8Iterator > GPIO_u8LPINS_MSK) {

					Loc_AddPort->GPIOx_AFRH &= (u32) ~(GPIO_u8ALTERNATE_CLR_MSK
							<< ((Loc_u8Iterator - 8) * GPIO_u8QUADRO_BIT));
					Loc_AddPort->GPIOx_AFRH |= (u32) (Copy_u8Function
							<< ((Loc_u8Iterator - 8) * GPIO_u8QUADRO_BIT));
				}

			}
		}
	}

	return Loc_enuReturnError;
}

/*
 * Function:  Gpio_SetAlternateFunc
 * --------------------
 * SELECT THE DESIRED ALTERNATE FUNCTION SPECIFIC PIN
 *
 *  Copy_u8Port: DESIRED PORT (GPIO_u8PORTA - GPIO_u8PORTB - GPIO_u8PORTC - GPIO_u8PORTD - GPIO_u8PORTE - GPIO_u8PORTH)
 *  Copy_u8Pin : DESIRED PIN START FROM GPIO_u8PIN_00 --> GPIO_u8PIN_15
 *  Copy_pu32Function : THE DESIRED ALTERERNATE FUNCTION --> OPTIONS -->
 *  START FROM GPIO_u8ALTERNATE_FUNC_00 --> GPIO_u8ALTERNATE_FUNC_15.
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK GpioErrorStatus_t ERROR ABOVE.
 */

GpioErrorStatus_t Gpio_SetAlternateFuncPort(void * GPIO_pvPort, u16 Copy_u16Pin,
		u8 Copy_pu32Function) {
	/*DECALRE VARAIBLE TO STORE PIN */
	u8 Loc_u8Iterator;
	GPIO_RegDef_t * Loc_AddPort = GPIO_pvPort;

	/*DEFINE RETURN ERROR STATUS ENUM VARIABLE*/
	GpioErrorStatus_t Loc_enuReturnError = Gpio_enuOk;

	/*CHECK IF THE ADDRESS IS NULL*/
	if (GPIO_pvPort == NULL) {
		Loc_enuReturnError = Gpio_enuErrorNullPointer;
	} else {
		for (Loc_u8Iterator = GPIO_ZERO; Loc_u8Iterator <= GPIO_u8_PINS;
				Loc_u8Iterator++) {
			if (Copy_u16Pin & (GPIO_PIN_MSK << Loc_u8Iterator)) {
				/*CHECK IF THE PIN IN L REGISTER*/
				if (Loc_u8Iterator <= GPIO_u8LPINS_MSK) {
					/*SWITCH IN ALTERANATE FUNCTION TO MAKE SURE IT'S VALID*/
					Loc_AddPort->GPIOx_AFRL &=(u32) ~(GPIO_u8ALTERNATE_CLR_MSK
							<< (Loc_u8Iterator * GPIO_u8QUADRO_BIT));
					Loc_AddPort->GPIOx_AFRL |= (u32) (Copy_pu32Function
							<< (Loc_u8Iterator * GPIO_u8QUADRO_BIT));
				} else if (Loc_u8Iterator <= GPIO_u8LPINS_MSK) {
					Loc_AddPort->GPIOx_AFRH &= (u32) ~(GPIO_u8ALTERNATE_CLR_MSK
							<< (Loc_u8Iterator * GPIO_u8QUADRO_BIT));
					Loc_AddPort->GPIOx_AFRH |= (u32) (Copy_pu32Function
							<< (Loc_u8Iterator * GPIO_u8QUADRO_BIT));
				}

			}
		}
	}

	return Loc_enuReturnError;
}
