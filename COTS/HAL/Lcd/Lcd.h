/*
 * Lcd.h
 *
 *  Created on: Apr 2, 2022
 *      Author: Kishk
 */

#ifndef LCD_H_
#define LCD_H_

#include <HAL/Lcd/Lcd_cfg.h>
/******************************************** TYPEDEF *********************************************/
typedef struct{
	void * Lcd_pvPort;
	u16    Lcd_u16Pin;
}Lcd_tstrCfg;

typedef enum{
	Lcd_enuOk,
	Lcd_enuBusy,
	Lcd_enuGpioInitError,
	Lcd_enuRccInitError,
	Lcd_enuErrorNullPointer,
	Lcd_enuErrorSize
}Lcd_tenuErrorStatus;
/******************************************** MACROS **********************************************/
#define LCD_u8RS		0
#define LCD_u8RW		1
#define LCD_u8EN		2
#define LCD_u8D0		3
#define LCD_u8D1		4
#define LCD_u8D2		5
#define LCD_u8D3		6
#define LCD_u8D4		7
#define LCD_u8D5		8
#define LCD_u8D6		9
#define LCD_u8D7		10


#define LCD_u8ROW_00		((u8) 0x80)
#define LCD_u8ROW_01		((u8) 0xC0)

#define LCD_u8COL_00		((u8) 0x00)
#define LCD_u8COL_01		((u8) 0x01)
#define LCD_u8COL_02		((u8) 0x02)
#define LCD_u8COL_03		((u8) 0x03)
#define LCD_u8COL_04		((u8) 0x04)
#define LCD_u8COL_05		((u8) 0x05)
#define LCD_u8COL_06		((u8) 0x06)
#define LCD_u8COL_07		((u8) 0x07)
#define LCD_u8COL_08		((u8) 0x08)
#define LCD_u8COL_09		((u8) 0x09)
#define LCD_u8COL_10		((u8) 0x0A)
#define LCD_u8COL_11		((u8) 0x0B)
#define LCD_u8COL_12		((u8) 0x0C)
#define LCD_u8COL_13		((u8) 0x0D)
#define LCD_u8COL_14		((u8) 0x0E)
#define LCD_u8COL_15		((u8) 0x0F)

/******************************************* PROTOTYPES *******************************************/
/*
 * Function:  Lcd_vidInit (ASYNCHRONOUS FUNCTION)
 * --------------------
 * INITIALIZE THE LCD PINS AND PUT THE STATE TO BE START
 *
 *	return: AN ERROR STATUS FROM ENUM Lcd_tenuErrorStatus.
 */
Lcd_tenuErrorStatus Lcd_enuInit(void);
/*
 * Function:  Lcd_vidTask
 * --------------------
 * THE TASK FUNCTION TO BE SET IN THE SCHEDULER
 *
 */
void Lcd_vidTask(void);
/*
 * Function:  Lcd_writeStringZCopy (ASYNCHRONOUS FUNCTION)
 * --------------------
 * WRITE AN STRING IN SPECIFIC POSITION IN THE LCD WITH ZERO COPY
 * CAUTION: DON'T EDIT PASSED BUFFER UNTIL THIS FUNCTION FINISH IT'S JOB
 *
 *	Add_pu8Str: POINTER TO THE REQUIRED STRING TO BE WRITTEN.
 *	Copy_u8PosX: DESIRED POSITION X OPTIONS (LCD_u8ROW_00 - LCD_u8ROW_01)
 *	Copy_u8PosY: DESIRED POSITION Y OPTIONS (LCD_u8COL_xx)
 *
 *	return: AN ERROR STATUS FROM ENUM Lcd_tenuErrorStatus.
 */
Lcd_tenuErrorStatus Lcd_writeStringZCopy(Buffer_t * Add_pstrBuffer , u8 Copy_u8PosX , u8 Copy_u8PosY );
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
Lcd_tenuErrorStatus Lcd_writeString(Buffer_t * Add_pstrBuffer , u8 Copy_u8PosX , u8 Copy_u8PosY );

/*
 * Function:  Lcd_ClearLcd (ASYNCHRONOUS FUNCTION)
 * --------------------
 *	CLEAR ALL DATA DISPLAYED IN LCD
 *
 *
 *	return: AN ERROR STATUS FROM ENUM Lcd_tenuErrorStatus.
 */
Lcd_tenuErrorStatus Lcd_ClearLcd(void);

/*EXTERN THE PIN CONFIGURATION FROM CFG FILE*/
extern const Lcd_tstrCfg LcdPinCfg[];
#endif /* LCD_H_ */
