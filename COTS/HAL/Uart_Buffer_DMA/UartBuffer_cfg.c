/*
 * UartBuffer_cfg.c
 *
 *  Created on: Apr 10, 2022
 *      Author: Kishk
 */

#include <SERVICES/Bit_utils.h>
#include <SERVICES/Std_types.h>
#include <HAL/Uart_Buffer/UartBuffer.h>
#include <HAL/Uart_Buffer/UartBuffer_cfg.h>
#include <MCAL/Uart/Uart.h>



const UartBuffer_Cfg_t UartBuffer_Configurations[NUM_OF_UART]={
		[UART1]={
				.Uart_pvChannel= UART_pvUART1,
				.Uart_u16BaudRate=9600,
				.Uart_u16OverSamplingMode=UART_u16OVERSAMPLING_BY_16
		}
};
