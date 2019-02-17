
#include "Config.h"
#include "EUSART.h"

void UART_1_Init (int baudrate){
    
    int brg = 0;
    
    TRISCbits.RC6 = 0; //TX1
    TRISCbits.RC7 = 1; //RX1
    
    brg =(int) (_XTAL_FREQ /(4*(baudrate)) -1);
    SPBRG1 = 832;
    SPBRGH1 = 832 >> 8;
    
    TXSTA1bits.TX9 = 0;
    TXSTA1bits.SYNC = 0;
    TXSTA1bits.BRGH = 1;
    TXSTA1bits.TXEN = 1;
    
    RCSTA1bits.CREN = 1;
    RCSTA1bits.RC9 = 0;
    RCSTA1bits.SPEN = 1;
    
    BAUDCON1bits.BRG16 = 1;
    BAUDCON1bits.TXCKP = 0;
    
}

void UART_2_Init (int baudrate){
    
    int brg = 0;
    
    TRISGbits.RG1 = 0; //TX1
    TRISGbits.RG2 = 1; //RX1
    
    brg = (int) (_XTAL_FREQ /(4*(baudrate)) -1);
    SPBRG2 = 832;
    SPBRGH2 = 832 >> 8;
    
    TXSTA2bits.TX9 = 0;
    TXSTA2bits.SYNC = 0;
    TXSTA2bits.BRGH = 1;
    TXSTA2bits.TXEN = 1;
    
    RCSTA2bits.CREN = 1;
    RCSTA2bits.RC9 = 0;
    RCSTA2bits.SPEN = 1;
    
    BAUDCON2bits.BRG16 = 1;
    BAUDCON2bits.TXCKP = 0;
}

void UART_1_Interrupt_Enable (char rxIntEN, char txIntEN){
    if(rxIntEN == 1)
        PIE1bits.RC1IE = 1;
    else
        PIE1bits.RC1IE = 0;
    PIR1bits.RC1IF = 0;
    
    if(txIntEN == 1)
        PIE1bits.TX1IE = 1;
    else
        PIE1bits.TX1IE = 0;
    
    PIR1bits.TX1IF = 0;
}

void UART_2_Interrupt_Enable (char rxIntEN, char txIntEN){
    if(rxIntEN == 1)
        PIE3bits.RC2IE = 1;
    else
        PIE3bits.RC2IE = 0;
    PIR3bits.RC2IF = 0;
    
    if(txIntEN == 1)
        PIE3bits.TX2IE = 1;
    else
        PIE3bits.TX2IE = 0;
    
    PIR3bits.TX2IF = 0;
}

void UART_1_Send(char * ptr){
    while(*ptr != '\0'){
        while(!PIR1bits.TX1IF);
        TXREG1 = *ptr;
        ptr++;
    }
    
}

void UART_2_Send(char * ptr){
    while(*ptr != '\0'){
        while(!PIR3bits.TX2IF);
        TXREG2 = *ptr;
        ptr++;
        //while(!TXSTA2bits.TRMT);
    
    }

}

char UART_1_Receive (void){
    char rx;
    rx = RCREG1;
    return rx;

}

char UART_2_Receive (void){
    char rx;
    rx = RCREG2;
    return rx;
}

void UART_Echo_1_2(void){
    char rx;
    rx = RCREG1;
    TXREG2 = rx;
}
void UART_Echo_2_1(void){
    char rx;
    rx = RCREG1;
    TXREG1 = rx;
}
void Update_Baud(char channel,int baudrate){
    int brg;
    brg =(int) (_XTAL_FREQ /(4*(baudrate)) -1);
    if(channel == 1){
        SPBRG1 = brg;
        SPBRGH1 = brg >> 8;
    }
    if(channel == 2){
        SPBRG2 = brg;
        SPBRGH2 = brg >> 8;
    
    }

}