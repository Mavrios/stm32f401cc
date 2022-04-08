/*
 * Lcd.c
 *
 *  Created on: Apr 2, 2022
 *      Author: Kishk
 */

#include <SERVICES/Std_types.h>
#include <SERVICES/Bit_utils.h>
#include <MCAL/RCC/RCC.h>
#include <MCAL/GPIO/Gpio.h>
#include <HAL/Lcd/Lcd.h>
#include <HAL/Lcd/Lcd_prv.h>

/******************************************* MACRIOS *******************************************/
#define RCC_ENABLE_PERI()			switch((u32)LcdPinCfg[Loc_u8Iterator].Lcd_pvPort){\
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

#define LCD_WRITE_DATA_BUS(Data)			Gpio_setPinPortValue(LcdPinCfg[LCD_u8RW].Lcd_pvPort ,LcdPinCfg[LCD_u8RW].Lcd_u16Pin  ,GPIO_u32LOW);\
			Gpio_setPinPortValue(LcdPinCfg[LCD_u8EN].Lcd_pvPort ,LcdPinCfg[LCD_u8EN].Lcd_u16Pin   ,GPIO_u32HIGH);\
		for(Loc_u8Iter = LCD_u8D0 ; Loc_u8Iter<=LCD_u8D7 ; Loc_u8Iter++)\
		{\
					Gpio_setPinPortValue(LcdPinCfg[Loc_u8Iter].Lcd_pvPort,LcdPinCfg[Loc_u8Iter].Lcd_u16Pin , GET_BIT(Data,(Loc_u8Iter-LCD_u8D0)));\
		}

/******************************************* TYPEDEF *******************************************/
typedef enum {
	Lcd_enuStart,
	Lcd_enuFunctionSet,
	Lcd_enuDisplayCtrl,
	Lcd_enuDisplayClr,
	Lcd_enuModeSet,
	Lcd_enuDone,

} Lcd_tenuInitState;

typedef enum {
	Lcd_enuNoReq, Lcd_enuWrite, Lcd_enuClear,
} Lcd_tenuRequestState;

/******************************************* VARIABLE *******************************************/
static u8 Lcd_u8InitState;
static u8 Lcd_u8Request;
static Buffer_t * Lcd_Buffer;
static u8 Position;
/******************************************* PROTOTYPES *******************************************/
/*
 * Function:  Lcd_WriteProcess
 * --------------------
 * FUNCTION TO BE CALLED IN THE TASK SCHEDULER FOR WRITING IN LCD
 *
 */
static void Lcd_WriteProcess(void);
/*
 * Function:  Lcd_ClearProcess
 * --------------------
 * FUNCTION TO BE CALLED IN THE TASK SCHEDULER FOR CLEAR LCD
 *
 */
static void Lcd_ClearProcess(void);
/*
 * Function:  InitProcess
 * --------------------
 * FUNCTION TO BE CALLED IN THE TASK SCHEDULER FOR INITIALIZATION PROCESS
 *
 */
static void InitProcess(void);

/*
 * Function:  Lcd_vidInit (ASYNCHRONOUS FUNCTION)
 * --------------------
 * INITIALIZE THE LCD PINS AND PUT THE STATE TO BE START
 *
 *	return: AN ERROR STATUS FROM ENUM Lcd_tenuErrorStatus.
 */

Lcd_tenuErrorStatus Lcd_enuInit(void) {

	/*DECLARE ITERATOR TO BE USED IN LOOPS*/
	u8 Loc_u8Iterator = LCD_ZERO;
	/*DECLARE AN ERROR STATUS TO CHECK GPIO AND RCC AND FOR RETURN STATUS*/
	Lcd_tenuErrorStatus Loc_enuReturnStatus = Lcd_enuOk;
	GpioErrorStatus_t Loc_enuGpioErrorChecker = Gpio_enuOk;
	RCC_tenuErrorStatus Loc_enuRccChecker;
	/*DECLARE STRUCT TO SET PIN CONFIGS*/
	GpioPinCfg_t Loc_strCfg;
	/*SET PIN CONFIGS*/
	Loc_strCfg.GPIO_u32Mode = GPIO_u32MODE_OUTPUT_PP;
	Loc_strCfg.GPIO_u32Speed = GPIO_u8SPEED_VERY_HIGH;
	/*VARIABLE TO SAVE MASKS OF USED GPIO PERIPHERALS*/
	u32 RCC_GPIOEN = LCD_ZERO;
	/*LOOP TO CHECK THE USED GPIO PERIPHERALS*/
	for (Loc_u8Iterator = 0; Loc_u8Iterator <= LCD_u8D7; Loc_u8Iterator++) {
		RCC_ENABLE_PERI() ;
	}
	/*ENABLE THE PERIPHERAL CLK FOR USED GPIO'S ONLY*/
	Loc_enuRccChecker = RCC_enuEnablePeripheralClk(RCC_u8AHB1_BUS, RCC_GPIOEN);
	/*LOOP TO CONFIGURE THE LCD PINS*/
	for (Loc_u8Iterator = 0;
			Loc_u8Iterator <= LCD_u8D7 && Loc_enuGpioErrorChecker == Gpio_enuOk;
			Loc_u8Iterator++) {
		Loc_strCfg.GPIO_pvPort = LcdPinCfg[Loc_u8Iterator].Lcd_pvPort;
		Loc_strCfg.GPIO_u16Pin = LcdPinCfg[Loc_u8Iterator].Lcd_u16Pin;
		Loc_enuGpioErrorChecker = Gpio_enuInit(&Loc_strCfg);
	}
	/*CHECK THE RETURN STATUS OF THE RCC*/
	if (Loc_enuRccChecker != RCC_enuOk) {
		Loc_enuReturnStatus = Lcd_enuRccInitError;
	}
	/*CHECK THE RETURN STATUS OF THE GPIO*/
	else if (Loc_enuGpioErrorChecker != Gpio_enuOk) {
		Loc_enuReturnStatus = Lcd_enuGpioInitError;
	} else {
		/*IF EVERYTHING IS OK PUT THE INIT STATE TO BE START*/
		Lcd_u8InitState = Lcd_enuStart;
	}
	/*RETURN ERROR STATUS*/
	return Loc_enuReturnStatus;
}

/*
 * Function:  Lcd_vidTask
 * --------------------
 * THE TASK FUNCTION TO BE SET IN THE SCHEDULER
 *
 */
void Lcd_vidTask(void) {
	/*CHECK IF THE LCD PROCESS WAS NOT DONE*/
	if (Lcd_u8InitState != Lcd_enuDone) {
		/*START THE INIT PROCESS*/
		InitProcess();
	} else {
		/*CHECK THE REQUESTS*/
		switch (Lcd_u8Request) {
		case Lcd_enuWrite:
			Lcd_WriteProcess();

			break;
		case Lcd_enuClear:
			Lcd_ClearProcess();
			break;
		}
	}
}
/*
 * Function:  Lcd_writeString (ASYNCHRONOUS FUNCTION)
 * --------------------
 * WRITE AN STRING IN SPECIFIC POSITION IN THE LCD
 *
 *	Add_pstrBuffer: POINTER TO THE REQUIRED BUFFER TO BE WRITTEN.
 *	Copy_u8PosX: DESIRED POSITION X OPTIONS (LCD_u8ROW_00 - LCD_u8ROW_01)
 *	Copy_u8PosY: DESIRED POSITION Y OPTIONS (LCD_u8COL_xx)
 *
 *	return: AN ERROR STATUS FROM ENUM Lcd_tenuErrorStatus.
 */
Lcd_tenuErrorStatus Lcd_writeStringZCopy(Buffer_t * Add_pstrBuffer,
		u8 Copy_u8PosX, u8 Copy_u8PosY) {
	/*VARIABLE TO RETURN ERROR STATUS*/
	Lcd_tenuErrorStatus Loc_enuReturnStatus = Lcd_enuOk;
	/*VARIFY THE POINTER TO STRING*/
	if (Add_pstrBuffer == NULL) {
		Loc_enuReturnStatus = Lcd_enuErrorNullPointer;
	} else {
		/*CHECK IF THE LCD HAS NO REQUESTS*/
		if (Lcd_u8Request == Lcd_enuNoReq) {
			/*WRITE AN WRITING REQUESTER*/
			Lcd_u8Request = Lcd_enuWrite;
			/*SAVE THE STRING */
			Lcd_Buffer = Add_pstrBuffer;
			/*SAVE THE REQUIRED POSITION*/
			Position = (u8) (Copy_u8PosX + Copy_u8PosY);
			/*CLEAR INDEX*/
			Add_pstrBuffer->Used = LCD_ZERO;
		} else {
			/*IF THE LCD BUSY ASSIGN BUSY TO RETURN STATUS*/
			Loc_enuReturnStatus = Lcd_enuBusy;
		}
	}
	/*RETURN ERROR STATUS*/
	return Loc_enuReturnStatus;
}

/*
 * Function:  Lcd_writeString (ASYNCHRONOUS FUNCTION)
 * --------------------
 * WRITE AN STRING IN SPECIFIC POSITION IN THE LCD WITH TAKING COPY OF THE BUFFER
 *
 *	Add_pu8Str: POINTER TO THE REQUIRED STRING TO BE WRITTEN.
 *	Copy_u8PosX: DESIRED POSITION X OPTIONS (LCD_u8ROW_00 - LCD_u8ROW_01)
 *	Copy_u8PosY: DESIRED POSITION Y OPTIONS (LCD_u8COL_xx)
 *
 *	return: AN ERROR STATUS FROM ENUM Lcd_tenuErrorStatus.
 */
Lcd_tenuErrorStatus Lcd_writeString(Buffer_t * Add_pstrBuffer, u8 Copy_u8PosX,
		u8 Copy_u8PosY) {
	/*VARIABLE TO RETURN ERROR STATUS*/
	Lcd_tenuErrorStatus Loc_enuReturnStatus = Lcd_enuOk;
	static Buffer_t Copy_Buffer;
	u8 Loc_u8Iterator;
	static u8 Temp_String[LCD_MAXIMUM_SIZE];
	/*VARIFY THE POINTER TO STRING*/
	if (Add_pstrBuffer == NULL) {
		Loc_enuReturnStatus = Lcd_enuErrorNullPointer;
	}
	if (Add_pstrBuffer->Size > LCD_MAXIMUM_SIZE) {
		Loc_enuReturnStatus = Lcd_enuErrorSize;

	} else {
		/*CHECK IF THE LCD HAS NO REQUESTS*/
		if (Lcd_u8Request == Lcd_enuNoReq) {
			/*WRITE AN WRITING REQUESTER*/
			Lcd_u8Request = Lcd_enuWrite;
			/*SAVE THE STRING */
			for (Loc_u8Iterator = LCD_ZERO;
					Loc_u8Iterator < Add_pstrBuffer->Size; Loc_u8Iterator++) {
				Temp_String[Loc_u8Iterator] =
						Add_pstrBuffer->Data[Loc_u8Iterator];
			}
			Copy_Buffer.Data = Temp_String;
			Copy_Buffer.Size = Add_pstrBuffer->Size;
			Lcd_Buffer = &Copy_Buffer;
			/*SAVE THE REQUIRED POSITION*/
			Position = (u8) (Copy_u8PosX + Copy_u8PosY);
			/*CLEAR INDEX*/
			Add_pstrBuffer->Used = LCD_ZERO;
		} else {
			/*IF THE LCD BUSY ASSIGN BUSY TO RETURN STATUS*/
			Loc_enuReturnStatus = Lcd_enuBusy;
		}
	}
	/*RETURN ERROR STATUS*/
	return Loc_enuReturnStatus;
}

/*
 * Function:  Lcd_ClearLcd (ASYNCHRONOUS FUNCTION)
 * --------------------
 *	CLEAR ALL DATA DISPLAYED IN LCD
 *
 *
 *	return: AN ERROR STATUS FROM ENUM Lcd_tenuErrorStatus.
 */
Lcd_tenuErrorStatus Lcd_ClearLcd(void) {
	/*VARIABLE TO RETURN ERROR STATUS*/
	Lcd_tenuErrorStatus Loc_enuReturnStatus = Lcd_enuOk;
	/*CHECK IF THE LCD HAS NO REQUESTS*/
	if (Lcd_u8Request == Lcd_enuNoReq) {
		/*WRITE AN Clear REQUESTER*/
		Lcd_u8Request = Lcd_enuClear;
	} else {
		/*IF THE LCD BUSY ASSIGN BUSY TO RETURN STATUS*/
		Loc_enuReturnStatus = Lcd_enuBusy;
	}
	/*RETURN ERROR STATUS*/
	return Loc_enuReturnStatus;
}

/*
 * Function:  Lcd_WriteProcess
 * --------------------
 * FUNCTION TO BE CALLED TO WRITE IN THE LCD
 *
 */
static void Lcd_WriteProcess(void) {
	/*ITERATOR TO BE USED IN LCD WRITE DATA BUS*/
	u8 Loc_u8Iter;
	/*TIMEMS TO TIME IN MS JOINED THE FUNC*/
	static u8 TimeMs;
	/*SWITCH ON THE TIME*/
	switch (TimeMs) {
	case LCD_TIME_TO_GOTOXY:
		Gpio_setPinPortValue(LcdPinCfg[LCD_u8RS].Lcd_pvPort,
				LcdPinCfg[LCD_u8RS].Lcd_u16Pin, GPIO_u32LOW);
		LCD_WRITE_DATA_BUS(Position)
		;
		TimeMs = (u8) (TimeMs + LCD_TICK_TIME_MS);
		break;
	case LCD_TIME_TO_XY_SEND_DATA:
		Gpio_setPinPortValue(LcdPinCfg[LCD_u8EN].Lcd_pvPort,
				LcdPinCfg[LCD_u8EN].Lcd_u16Pin, GPIO_u32LOW);
		TimeMs = (u8) (TimeMs + LCD_TICK_TIME_MS);
		break;
	case LCD_TIME_TO_SEND_CHAR:
		if (Lcd_Buffer->Used != Lcd_Buffer->Size) {
			Gpio_setPinPortValue(LcdPinCfg[LCD_u8RS].Lcd_pvPort,
					LcdPinCfg[LCD_u8RS].Lcd_u16Pin, GPIO_u32HIGH);
			LCD_WRITE_DATA_BUS(Lcd_Buffer->Data[Lcd_Buffer->Used]);
			Lcd_Buffer->Used++;
		} else {
			Lcd_u8Request = Lcd_enuNoReq;
		}
		TimeMs = (u8) (TimeMs + LCD_TICK_TIME_MS);
		break;

	case LCD_TIME_TO_CHAR_SEND_DATA:
		TimeMs = LCD_TIME_TO_SEND_CHAR;
		Gpio_setPinPortValue(LcdPinCfg[LCD_u8EN].Lcd_pvPort,
				LcdPinCfg[LCD_u8EN].Lcd_u16Pin, GPIO_u32LOW);
		break;
	default:
		TimeMs++;
		break;
	}

}


/*
 * Function:  Lcd_ClearProcess
 * --------------------
 * FUNCTION TO BE CALLED IN THE TASK SCHEDULER FOR CLEAR LCD
 *
 */
static void Lcd_ClearProcess(void)
{
	/*ITERATOR TO BE USED IN LCD WRITE DATA BUS*/
	u8 Loc_u8Iter;
	/*TIMEMS TO TIME IN MS JOINED THE FUNC*/
	static u8 TimeMs;
	if (TimeMs == 0) {
		Gpio_setPinPortValue(LcdPinCfg[LCD_u8RS].Lcd_pvPort,
				LcdPinCfg[LCD_u8RS].Lcd_u16Pin, GPIO_u32LOW);
		LCD_WRITE_DATA_BUS(LCD_DISPLAY_CLR);
	}
	else if (TimeMs == 1) {
		Gpio_setPinPortValue(LcdPinCfg[LCD_u8EN].Lcd_pvPort,
				LcdPinCfg[LCD_u8EN].Lcd_u16Pin, GPIO_u32LOW);
	}
	else if(TimeMs == 2)
	{
		TimeMs = 0;
		Lcd_u8Request = Lcd_enuNoReq;
	}
	TimeMs++;

}

/*
 * Function:  InitProcess
 * --------------------
 * FUNCTION TO BE CALLED TO INITIALIZE THE LCD
 *
 */
static void InitProcess(void) {
	/*ITERATOR TO BE USED IN LCD WRITE DATA BUS*/
	u8 Loc_u8Iter;
	/*TIMEMS TO TIME IN MS JOINED THE FUNC*/
	static u8 TimeMs;
	/*SWITCH ON THE Lcd_u8InitState*/
	switch (Lcd_u8InitState) {
	case Lcd_enuStart:
		TimeMs++;
		if (TimeMs == LCD_WAIT_TO_BE_STABLE) {
			Lcd_u8InitState++;
			TimeMs = 0;
		}
		break;
	case Lcd_enuFunctionSet:
		TimeMs++;
		if (TimeMs == 1) {
			Gpio_setPinPortValue(LcdPinCfg[LCD_u8RS].Lcd_pvPort,
					LcdPinCfg[LCD_u8RS].Lcd_u16Pin, GPIO_u32LOW);
			LCD_WRITE_DATA_BUS(LCD_FUNCTION_SET);
		}
		if (TimeMs == 2) {
			Gpio_setPinPortValue(LcdPinCfg[LCD_u8EN].Lcd_pvPort,
					LcdPinCfg[LCD_u8EN].Lcd_u16Pin, GPIO_u32LOW);
			Lcd_u8InitState++;
			TimeMs = 0;
		}
		break;
	case Lcd_enuDisplayCtrl:
		TimeMs++;
		if (TimeMs == 1) {
			Gpio_setPinPortValue(LcdPinCfg[LCD_u8RS].Lcd_pvPort,
					LcdPinCfg[LCD_u8RS].Lcd_u16Pin, GPIO_u32LOW);
			LCD_WRITE_DATA_BUS(LCD_DISPLAY_CTRL);
		}
		if (TimeMs == 2) {
			Gpio_setPinPortValue(LcdPinCfg[LCD_u8EN].Lcd_pvPort,
					LcdPinCfg[LCD_u8EN].Lcd_u16Pin, GPIO_u32LOW);
			Lcd_u8InitState++;
			TimeMs = 0;
		}
		break;
	case Lcd_enuDisplayClr:
		TimeMs++;
		if (TimeMs == 1) {
			Gpio_setPinPortValue(LcdPinCfg[LCD_u8RS].Lcd_pvPort,
					LcdPinCfg[LCD_u8RS].Lcd_u16Pin, GPIO_u32LOW);
			LCD_WRITE_DATA_BUS(LCD_DISPLAY_CLR);
		}
		else if (TimeMs == 2) {
			Gpio_setPinPortValue(LcdPinCfg[LCD_u8EN].Lcd_pvPort,
					LcdPinCfg[LCD_u8EN].Lcd_u16Pin, GPIO_u32LOW);
		}
		else if(TimeMs == 3)
		{
			Lcd_u8InitState++;
			TimeMs = 0;
		}

		break;
	case Lcd_enuModeSet:
		TimeMs++;
		if (TimeMs == 2) {
			Gpio_setPinPortValue(LcdPinCfg[LCD_u8RS].Lcd_pvPort,
					LcdPinCfg[LCD_u8RS].Lcd_u16Pin, GPIO_u32LOW);
			LCD_WRITE_DATA_BUS(LCD_MODE_SET);
		} else if (TimeMs == 3) {
			Gpio_setPinPortValue(LcdPinCfg[LCD_u8EN].Lcd_pvPort,
					LcdPinCfg[LCD_u8EN].Lcd_u16Pin, GPIO_u32LOW);
			Lcd_u8InitState++;
			TimeMs = 0;
		}
		break;
	}

}
