/*
 * File:   main.c
 * Author: Tom
 *
 * Created on December 30, 2018, 12:31 PM
 */
#include <stdio.h>
#include "Config.h"
#include "EUSART.h"
#include "Timer.h"

void InitPins(void);

char rxBuffer[20];
volatile int txCount;
volatile int rxCount;
int i;
char tmrUpdate;
char txStr[] = "HelloWorld\n";
char pmtkStr[] = "$PMTK251,38400*27\r\n";

void main(void) {
    
    tmrUpdate = 0;
    txCount = rxCount = 0;
    
    System_Init();
    
    UART_1_Init (9600);
    UART_2_Init (9600);
    UART_1_Interrupt_Enable (1, 0);
    UART_2_Interrupt_Enable (1, 0);
    Interrupts_Init();
    Timer_0_Init();
    Timer_0_Reset();
    Timer_0_Interrupt_Enable();
    InitPins();
    
    
    Timer_0_Start();
    //AS FOLLOWS:
    //TX2/RX2 ---> GPS
    //TX1/RX1 ---> Serial Monitor
    sprintf(pmtkStr,"$PMTK251,38400*27\r\n\0");
    __delay_ms(1000);
    UART_1_Send(pmtkStr);
    UART_2_Send(pmtkStr);
   __delay_ms(10);
    while(1){
        
        if(tmrUpdate){
            LATDbits.LATD0 ^= 1;
            Timer_0_Reset();
            tmrUpdate = 0;
        }
    }
}

void InitPins(void){
    LATD = 0; //LED's are outputs
    TRISD = 0; //Turn off all LED's
}

void __interrupt() ISR(void){
    //Heartbeat
    if(INTCONbits.T0IE && INTCONbits.TMR0IF){
        tmrUpdate = 1;
        INTCONbits.TMR0IF = 0;
    }
    if(PIE1bits.RC1IE && PIR1bits.RC1IF){
        //UART_Echo_1_2();
        rxBuffer[rxCount] = RCREG1;
        TXREG2 = rxBuffer[rxCount];
        PIR1bits.RC1IF = 0;
    }
    if(PIE3bits.RC2IE && PIR3bits.RC2IF){
        rxBuffer[rxCount] = RCREG2;
        TXREG1 = rxBuffer[rxCount];
        PIR3bits.RC2IF = 0;
    }


}

