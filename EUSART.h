
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#include <xc.h>
#include "Config.h"



#ifdef _18F87J11

#ifdef _XTAL_FREQ 32000000L

#endif

#endif

void UART_1_Init (int baudrate);
void UART_2_Init (int baudrate);
void UART_1_Interrupt_Enable (char rxIntEN, char txIntEN);
void UART_2_Interrupt_Enable (char rxIntEN, char txIntEN);
void UART_1_Send(char * ptr);
void UART_2_Send(char * ptr);
char UART_1_Receive (void);
char UART_2_Receive (void);
void UART_Echo_1_2(void);
void UART_Echo_2_1(void);
void Update_Baud(char channel,int baudrate);