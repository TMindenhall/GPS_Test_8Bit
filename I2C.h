/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#include <xc.h>


void I2C_1_Init(char baudrate);
void I2C_2_Init(char baudrate);
void I2C_1_Write_8(char device_adr,char reg_adr,char value);
void I2C_2_Write_8(char device_adr,char reg_adr,char value);
char I2C_1_Read_8(char device_adr,char reg_adr);
char I2C_2_Read_8(char device_adr,char reg_adr);

