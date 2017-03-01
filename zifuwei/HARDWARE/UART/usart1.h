#ifndef __USART1_H
#define	__USART1_H

#include "stm32f10x.h"
#include <stdio.h>

//#define USART_REC_LEN  			200  	//定义最大接收字节数 200
//extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节

void USART3_Config(void);
void UART3Test(void);
#endif /* __USART1_H */
