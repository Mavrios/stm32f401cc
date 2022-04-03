/*
 * Lcd_prv.h
 *
 *  Created on: Apr 2, 2022
 *      Author: Kishk
 */

#ifndef LCD_PRV_H_
#define LCD_PRV_H_

#define LCD_ZERO					0



#define LCD_FUNCTION_SET			0b00111000
#define LCD_DISPLAY_CTRL			0b00001100
#define LCD_DISPLAY_CLR				0b00000001
#define LCD_MODE_SET				0b00000110
#define LCD_WAIT_TO_BE_STABLE		50

#define LCD_TIME_TO_GOTOXY			10
#define LCD_TIME_TO_XY_SEND_DATA	11
#define LCD_TIME_TO_SEND_CHAR		12
#define LCD_TIME_TO_CHAR_SEND_DATA	13
#endif /* LCD_PRV_H_ */
