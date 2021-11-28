/*
 * API_uart.c
 *
 *  Created on: 22 nov. 2021
 *      Author: luis
 */
#include "API_uart.h"
#include "stdio.h"
#include "stdbool.h"

UART_HandleTypeDef UartHandle;

bool_t uartInit()
{ char buffer[100];
  // inicialización buffer de caracteres//
  uint8_t i;
  for(i=0;i<sizeof(buffer);i++)
  	  	  {buffer[i]=NULL;}
  // FIN inicialización buffer de caracteres//

  UartHandle.Instance        = USARTx;
  UartHandle.Init.BaudRate   = 9600;
  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits   = UART_STOPBITS_1;
  UartHandle.Init.Parity     = UART_PARITY_ODD;
  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode       = UART_MODE_TX_RX;
  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

  if(HAL_UART_Init(&UartHandle) != HAL_OK)
  {
    /* Initialization Error */
	  return false;
  }
  else{ sprintf(buffer,"\n\rvelocidad de transmision %ld,8 bits de palabras, %ld bits de stop\n\r",UartHandle.Init.BaudRate,UART_STOPBITS_1);
        HAL_UART_Transmit(&UartHandle,buffer,sizeof(buffer)/sizeof(char),0xFFFF);
	    return true;
      }
}

void uartSendString(uint8_t *pstring,uint16_t size)
{  uint8_t index, count=0;
for(index=0;*(pstring + index)!=0; index ++)
{count++;}

	HAL_UART_Transmit(&UartHandle,pstring,size,0xFFFF);

}

