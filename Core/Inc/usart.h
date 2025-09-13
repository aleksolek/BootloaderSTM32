#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f3xx_ll_usart.h"

#define CMD_UART USART2
#define DEBUG_UART USART3

void UART_CMD_Init(void);
void USART_DEBUG_Init(void);
void UART_putChar(const USART_TypeDef *USARTx, char ch);

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

