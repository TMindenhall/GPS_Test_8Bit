
#include "Timer.h"
#include "Config.h"


#ifdef _XTAL_FREQ 32000000L
#define PRESCALER 6
#endif


void Timer_0_Init(void){
    
    TMR0L = 0;
    TMR0H = 0; 
    T0CONbits.TMR0ON = 0;
    T0CONbits.T08BIT = 0;
    T0CONbits.T0CS = 0;
    T0CONbits.T0SE = 1;
    T0CONbits.PSA = 0;
    T0CONbits.T0PS = PRESCALER;
}
void Timer_0_Start(void){
    T0CONbits.TMR0ON = 1;
}

void Timer_0_Stop(void){
    T0CONbits.TMR0ON = 0;
}

void Timer_0_Reset(void){
    TMR0L = 0;
    TMR0H = 0;
}

void Timer_0_Interrupt_Enable(void){
    INTCONbits.T0IE = 1;
    INTCONbits.T0IF = 0;


}