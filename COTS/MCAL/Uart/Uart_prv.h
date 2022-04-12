/*
 * Uart_prv.h
 *
 *  Created on: Apr 10, 2022
 *      Author: Kishk
 */

#ifndef MCAL_UART_UART_PRV_H_
#define MCAL_UART_UART_PRV_H_

#define UART_u8NUM_OF_INTERRUPTS			((u8)  0x03)

#define UART_u16CLR_OVERSAMPLING			((u16) 0x7FFF)
#define UART_u16VALIDATE_OVERSAMPLING			((u16) 0x7FFF)

#define UART_u16CLR_DATALENGTH			((u16) 0xEFFF)
#define UART_u16VALIDATE_DATALENGTH			((u16) 0xEFFF)


#define UART_u16CR1_CLRMSK				((u16) 0xB0EC)

#define UART_u16CR2_CLRMSK				((u16) 0xCFFF)


#define UART_u16ENABLE					((u16) 0x2000)

#define UART_u16BAUDRATE_VALIDATE		((u16) 0xFFF7)


#define UART_u16DR_VALIDATE				0xFE00

#define UART_u16SU_TXE					((u16) 0x0080)
#define UART_u16SU_TC					((u16) 0x0040)

#define UART_u16CLEAR_TC					((u16) 0xFFBF)


#define UART_USART1						0
#define UART_USART2						1
#define UART_USART6						2
#endif /* MCAL_UART_UART_PRV_H_ */
