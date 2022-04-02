/*
 * Gpio.h
 *
 *  Created on: Mar 14, 2022
 *      Author: Kishk
 */

#ifndef MCAL_GPIO_H_
#define MCAL_GPIO_H_
/*******************************************  TYPEDEF  ****************************************************/
typedef struct{
	u32 GPIO_u32Mode;
	u32	GPIO_u32Speed;
	void *	GPIO_pvPort;
	u16	GPIO_u16Pin;
}GpioPinCfg_t;

typedef enum{
	Gpio_enuOk,
	Gpio_enuErrorPin,
	Gpio_enuErrorPort,
	Gpio_enuErrorMode,
	Gpio_enuErrorPull,
	Gpio_enuErrorSpeed,
	Gpio_enuErrorDirection,
	Gpio_enuErrorNullPointer,
	Gpio_enuErrorAlternateFunction,
	Gpio_enuErrorValue
}GpioErrorStatus_t;

/*******************************************  MACROS  ****************************************************/
#define	GPIO_u16PIN_00				((u16) 0x0001)
#define	GPIO_u16PIN_01				((u16) 0x0002)
#define	GPIO_u16PIN_02				((u16) 0x0004)
#define	GPIO_u16PIN_03				((u16) 0x0008)
#define	GPIO_u16PIN_04				((u16) 0x0010)
#define	GPIO_u16PIN_05				((u16) 0x0020)
#define	GPIO_u16PIN_06				((u16) 0x0040)
#define	GPIO_u16PIN_07				((u16) 0x0080)
#define	GPIO_u16PIN_08				((u16) 0x0100)
#define	GPIO_u16PIN_09				((u16) 0x0200)
#define	GPIO_u16PIN_10				((u16) 0x0400)
#define	GPIO_u16PIN_11				((u16) 0x0800)
#define	GPIO_u16PIN_12				((u16) 0x1000)
#define	GPIO_u16PIN_13				((u16) 0x2000)
#define	GPIO_u16PIN_14				((u16) 0x4000)
#define	GPIO_u16PIN_15				((u16) 0x8000)

#define GPIO_pvPORTA				((void *) 0x40020000)
#define GPIO_pvPORTB				((void *) 0x40020400)
#define GPIO_pvPORTC				((void *) 0x40020800)
#define GPIO_pvPORTD				((void *) 0x40020C00)
#define GPIO_pvPORTE				((void *) 0x40021000)
#define GPIO_pvPORTH				((void *) 0x40021C00)


#define GPIO_u32MODE_OUTPUT_PP		((u32) 0x00000001)
#define GPIO_u32MODE_OUTPUT_PP_PU	((u32) 0x00000101)
#define GPIO_u32MODE_OUTPUT_PP_PD	((u32) 0x00000201)
#define GPIO_u32MODE_OUTPUT_OD		((u32) 0x00000011)
#define GPIO_u32MODE_OUTPUT_OD_PU	((u32) 0x00000111)
#define GPIO_u32MODE_OUTPUT_OD_PD	((u32) 0x00000211)

#define GPIO_u32MODE_INPUT			((u32) 0x00000000)
#define GPIO_u32MODE_INPUT_PU		((u32) 0x00000100)
#define GPIO_u32MODE_INPUT_PD		((u32) 0x00000200)

#define GPIO_u32MODE_AF_PP			((u32) 0x00000002)
#define GPIO_u32MODE_AF_PP_PU		((u32) 0x00000102)
#define GPIO_u32MODE_AF_PP_PD		((u32) 0x00000202)
#define GPIO_u32MODE_AF_OD			((u32) 0x00000012)
#define GPIO_u32MODE_AF_OD_PU		((u32) 0x00000112)
#define GPIO_u32MODE_AF_OD_PD		((u32) 0x00000212)

#define GPIO_u32MODE_ANALOG			((u32) 0x00000003)

#define GPIO_u8PULL_OFF				((u8) 0x00)
#define GPIO_u8PULL_UP				((u8) 0x01)
#define GPIO_u8PULL_DOWN			((u8) 0x02)

#define GPIO_u8SPEED_LOW			((u8) 0x00)
#define GPIO_u8SPEED_MID			((u8) 0x01)
#define GPIO_u8SPEED_HIGH			((u8) 0x02)
#define GPIO_u8SPEED_VERY_HIGH		((u8) 0x03)

#define GPIO_u32LOW					((u8) 0x00)
#define GPIO_u32HIGH				((u8) 0x01)

#define GPIO_u8ALTERNATE_FUNC_00		((u8) 0x00)
#define GPIO_u8ALTERNATE_FUNC_01		((u8) 0x01)
#define GPIO_u8ALTERNATE_FUNC_02		((u8) 0x02)
#define GPIO_u8ALTERNATE_FUNC_03		((u8) 0x03)
#define GPIO_u8ALTERNATE_FUNC_04		((u8) 0x04)
#define GPIO_u8ALTERNATE_FUNC_05		((u8) 0x05)
#define GPIO_u8ALTERNATE_FUNC_06		((u8) 0x06)
#define GPIO_u8ALTERNATE_FUNC_07		((u8) 0x07)
#define GPIO_u8ALTERNATE_FUNC_08		((u8) 0x08)
#define GPIO_u8ALTERNATE_FUNC_09		((u8) 0x09)
#define GPIO_u8ALTERNATE_FUNC_10		((u8) 0x0A)
#define GPIO_u8ALTERNATE_FUNC_11		((u8) 0x0B)
#define GPIO_u8ALTERNATE_FUNC_12		((u8) 0x0C)
#define GPIO_u8ALTERNATE_FUNC_13		((u8) 0x0D)
#define GPIO_u8ALTERNATE_FUNC_14		((u8) 0x0E)
#define GPIO_u8ALTERNATE_FUNC_15		((u8) 0x0F)

/********************************************** PROTOTYPES ***************************************************/
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
GpioErrorStatus_t Gpio_enuInit(GpioPinCfg_t * Add_strGpioCfg);
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
GpioErrorStatus_t Gpio_setPinValue(GpioPinCfg_t * Add_strGpioCfg, u32 Copy_u8Value);
/*
 * Function:  Gpio_setPinPortValue
 * --------------------
 * SETTING PIN VALUE WITH HIGH OR LOW
 *
 *  Copy_pvPort: DESIRED PORT (GPIO_u8PORTA - GPIO_u8PORTB - GPIO_u8PORTC - GPIO_u8PORTD - GPIO_u8PORTE - GPIO_u8PORTH)
 *  Copy_u16Pin : DESIRED PIN START FROM GPIO_u8PIN_00 --> GPIO_u8PIN_15
 *  Copy_u8Value : DESIRED VALUE ( GPIO_u32LOW - GPIO_u32HIGH )
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK GpioErrorStatus_t ERROR ABOVE.
 */
GpioErrorStatus_t Gpio_setPinPortValue(void * GPIO_pvPort, u16 Copy_u16Pin , u32 Copy_u8Value);
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
GpioErrorStatus_t Gpio_ReadPinValue(GpioPinCfg_t * Add_strGpioCfg, pu32 Add_pu32Value);
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
GpioErrorStatus_t Gpio_ReadPinPortValue(void * GPIO_pvPort, u16 Copy_u16Pin, pu32 Add_pu32Value);
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
GpioErrorStatus_t Gpio_SetAlternateFunc(GpioPinCfg_t * Add_strGpioCfg, u8 Copy_pu32Function);
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
GpioErrorStatus_t Gpio_SetAlternateFuncPort(void * GPIO_pvPort, u16 Copy_u16Pin, u8 Copy_pu32Function);
#endif /* MCAL_GPIO_H_ */
