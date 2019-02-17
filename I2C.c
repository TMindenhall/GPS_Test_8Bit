/*
 */


#include "I2C.h"

#ifdef _18F87J11

#endif

#define _XTAL_FREQ 32000000L

void I2C_1_Init(char baudrate) {

    //sspxADD = ((FOSC/4)/baudrate) - 1;
    TRISDbits.RD5 = 1; //SDA2 //FIXME
    TRISDbits.RD6 = 1; //SCL2 //FIXME

    if (baudrate == 100) {
        SSP1STATbits.SMP = 1; //100kHz slew
        SSP1ADD = 79; //100kHz
        SSP1CON1bits.SSPM = 0b1000; //I2C Master mode
        SSP1CON1bits.SSPEN = 1; //Enable MSSP
    }

    if (baudrate == 400) {
        SSP1STATbits.SMP = 0;
        SSP1ADD = 19;
        SSP1CON1bits.SSPM = 0b1000;
        SSP1CON1bits.SSPEN = 1;
    }
}

void I2C_2_Init(char baudrate) {

    //sspxADD = ((FOSC/4)/baudrate) - 1;
    TRISDbits.RD5 = 1;              //SDA2
    TRISDbits.RD6 = 1;              //SCL2

    if (baudrate == 100) {
        SSP2STATbits.SMP = 1;       //100kHz slew
        SSP2ADD = 79;               //100kHz
        SSP2CON1bits.SSPM = 0b1000; //I2C Master mode
        SSP2CON1bits.SSPEN = 1;     //Enable MSSP
    }

    if (baudrate == 400) {
        SSP2STATbits.SMP = 0;       //Highspeed Slew
        SSP2ADD = 19;               //400kHz
        SSP2CON1bits.SSPM = 0b1000; //I2C Master mode
        SSP2CON1bits.SSPEN = 1;     //Enable MSSP
    }
}

void I2C_1_Write_8(char device_adr,char reg_adr,char value){
    char data;
    
    SSP1CON2bits.SEN = 1;                       //Start
    while(SSP1CON2bits.SEN);                    //Wait for start to finish
    data = SSP1BUF;                             //Clear buffer
    SSP1BUF = device_adr;                       //Load the device address
    while(SSP1STATbits.BF || SSP1STATbits.R_W); //Wait till complete
    SSP1BUF = reg_adr;                          //Load the register address
    while(SSP1STATbits.BF || SSP1STATbits.R_W); //Wait till complete
    SSP1BUF = value;                            //Load the new value
    while(SSP1STATbits.BF || SSP1STATbits.R_W); //Wait till complete
    SSP1CON2bits.PEN = 1;                       //Stop
    while(SSP1CON2bits.PEN);                    //Wait till stop
}

void I2C_2_Write_8(char device_adr,char reg_adr,char value){
    char data;
    
    SSP2CON2bits.SEN = 1;                       //Start
    while(SSP2CON2bits.SEN);                    //Wait for start to finish
    data = SSP2BUF;                             //Clear buffer
    SSP2BUF = device_adr;                       //Load the device address
    while(SSP2STATbits.BF || SSP2STATbits.R_W); //Wait till complete
    SSP2BUF = reg_adr;                          //Load the register address
    while(SSP2STATbits.BF || SSP2STATbits.R_W); //Wait till complete
    SSP2BUF = value;                            //Load the new value
    while(SSP2STATbits.BF || SSP2STATbits.R_W); //Wait till complete
    SSP2CON2bits.PEN = 1;                       //Stop
    while(SSP2CON2bits.PEN);                    //Wait till stop
}


char I2C_1_Read_8(char device_adr,char reg_adr) {
    char rx;
    SSP1CON2bits.SEN = 1;                       //Start condition
    while (SSP1CON2bits.SEN == 1);              //Wait for start to finish
    rx = SSP1BUF;                               //Read SSPxBUF to make sure BF is clear
    SSP1BUF = device_adr;                       //address with R/W clear for write
    while (SSP1STATbits.BF || SSP1STATbits.R_W);// wait until write cycle is complete
    SSP1BUF = reg_adr;                          //Send byte
    while (SSP1STATbits.BF || SSP1STATbits.R_W);// wait until write cycle is complete
    SSP1CON2bits.RSEN = 1;                      //repeated Start condition
    while (SSP1CON2bits.RSEN == 1);             //Wait for restart to finish
    rx = SSP1BUF;                               //Make sure buffer is clear
    SSP1BUF = (device_adr + 1);                 //address with R/W set for read
    while (SSP1STATbits.BF || SSP1STATbits.R_W);// wait until write cycle is complete
    SSP1CON2bits.RCEN = 1;                      // enable master for 1 byte reception
    while (!SSP1STATbits.BF);                   // wait until byte received
    rx = SSP1BUF;
    SSP1CON2bits.ACKDT = 1;                     //NACK for last byte.
    SSP1CON2bits.ACKEN = 1;                     //Send ACK/NACK
    while (SSP1CON2bits.ACKEN);
    SSP1CON2bits.PEN = 1;                       //Stop condition
    while (SSP1CON2bits.PEN);                   //Wait for stop to finish

    return rx;
}


char I2C_2_Read_8(char device_adr,char reg_adr) {
    
    char rx;
    SSP2CON2bits.SEN = 1;                       //Start condition
    while (SSP2CON2bits.SEN == 1);              //Wait for start to finish
    rx = SSP2BUF;                               //Read SSPxBUF to make sure BF is clear
    SSP2BUF = device_adr;                       //address with R/W clear for write
    while (SSP2STATbits.BF || SSP2STATbits.R_W);// wait until write cycle is complete
    SSP2BUF = reg_adr;                          //Send byte
    while (SSP2STATbits.BF || SSP2STATbits.R_W);// wait until write cycle is complete
    SSP2CON2bits.RSEN = 1;                      //repeated Start condition
    while (SSP2CON2bits.RSEN == 1);             //Wait for restart to finish
    rx = SSP2BUF;                               //Make sure buffer is clear
    SSP2BUF = (device_adr + 1);                 //address with R/W set for read
    while (SSP2STATbits.BF || SSP2STATbits.R_W);// wait until write cycle is complete
    SSP2CON2bits.RCEN = 1;                      // enable master for 1 byte reception
    while (!SSP2STATbits.BF);                   // wait until byte received
    rx = SSP2BUF;
    SSP2CON2bits.ACKDT = 1;                     //NACK for last byte.  Use a 0 here to ACK
    SSP2CON2bits.ACKEN = 1;                     //Send ACK/NACK
    while (SSP2CON2bits.ACKEN);
    SSP2CON2bits.PEN = 1;                       //Stop condition
    while (SSP2CON2bits.PEN);                   //Wait for stop to finish

    return rx;
}