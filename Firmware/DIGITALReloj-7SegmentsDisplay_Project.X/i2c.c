/*******************************************************************************
 *
 *                 i2c Library
 *
 *******************************************************************************
 * FileName:        i2c.c
 * Complier:        XC8 v2.31
 * Author:          Pedro Sánchez Ramírez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Library for i2c use in PIC18
 *******************************************************************************
 *                  MIT License
 * 
 * Copyright (c) 2016 Pedro Sánchez Ramírez
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *******************************************************************************
 * Rev.         Date            Comment
 *  v1.0.0      03/06/2019      Created library.
 *  v1.0.1      28/06/2020      Implementing for second I2C on PIC18F25K22.
 *  v1.0.2      14/04/2020      Suport for I2C on PIC18F46K22
 ******************************************************************************/
#include <xc.h>
#include "i2c.h"
#include "main.h"

//#define _XTAL_FREQ  64000000    // Fosc

/*******************************************************************************
 * Function:        void I2C1_Init(void)
 * Description:     Configure I2C module
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         None
 ******************************************************************************/
void I2C1_Init(void){
    SDA1_DIR = 1 /*I2C_INPUT*/;        
	SCK1_DIR = 1 /*I2C_INPUT*/;	
    SSP1STAT = 0b10000000;		// Slew Rate control is disabled
     /*
   * WCOL:0
   * SSPOV:0
   * SSPEN:1 -> Enables Serial Port & configures the SDA and SCL as serial port pins
   * CKP:0
   * SSPM3:SSPM0:1000 -> I2C Master Mode, clock=FOSC/(4*(SSPADD+1))
   * Ej. FOSC = 64MHZ, and to get a clock of 100Khz => SSPADD = 159u
   */	
	SSP1CON1 = 0b00101000;		// Select and enable I2C in master mode
    SSP1ADD  = ((_XTAL_FREQ/4000)/I2C_SPEED) - 1;	
}

/*******************************************************************************
 * Function:        void I2C2_Init(void)
 * Description:     Configure I2C module
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         None
 ******************************************************************************/
void I2C2_Init(void){	
	SDA2_DIR = I2C_INPUT;        
	SCK2_DIR = I2C_INPUT;	
    SSP2STAT = 0b10000000;		// Slew Rate control is disabled
     /*
   * WCOL:0
   * SSPOV:0
   * SSPEN:1 -> Enables Serial Port & configures the SDA and SCL as serial port pins
   * CKP:0
   * SSPM3:SSPM0:1000 -> I2C Master Mode, clock=FOSC/(4*(SSPADD+1))
   * Ej. FOSC = 64MHZ, and to get a clock of 100Khz => SSPADD = 159u
   */	
	SSP2CON1 = 0b00101000;		// Select and enable I2C in master mode
    SSP2ADD  = ((_XTAL_FREQ/4000)/I2C_SPEED) - 1;	
}

/*******************************************************************************
 * Function:        void I2C_Start(void)
 * Description:     Sends start bit sequence
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         None
 ******************************************************************************/
void I2C1_Start(void){
    SSP1CON2bits.SEN = 1 /*I2C_HIGH*/;			
	while(!PIR1bits.SSP1IF);		
	PIR1bits.SSP1IF = 0 /*I2C_LOW*/;	
}

/*******************************************************************************
 * Function:        void I2C_Start(void)
 * Description:     Sends start bit sequence
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         None
 ******************************************************************************/
void I2C2_Start(void){
	SSP2CON2bits.SEN = I2C_HIGH;			
	while(!PIR3bits.SSP2IF);		
	PIR3bits.SSP2IF = I2C_LOW;	
}

/*******************************************************************************
 * Function:        void I2C_ReStart(void)
 * Description:     Sends restart bit sequence
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         None
 ******************************************************************************/
void I2C1_ReStart(void){
    SSP1CON2bits.RSEN = I2C_HIGH;			
	while(!PIR1bits.SSP1IF);		
	PIR1bits.SSP1IF = I2C_LOW;			
}

/*******************************************************************************
 * Function:        void I2C_ReStart(void)
 * Description:     Sends restart bit sequence
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         None
 ******************************************************************************/
void I2C2_ReStart(void){
	SSP2CON2bits.RSEN = I2C_HIGH;			
	while(!PIR3bits.SSP2IF);		
	PIR3bits.SSP2IF = I2C_LOW;			
}

/*******************************************************************************
 * Function:        void I2C_Stop(void)
 * Description:     Sends stop bit sequence
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         None
 ******************************************************************************/
void I2C1_Stop(void){	
    SSP1CON2bits.PEN = I2C_HIGH;			
	while(!PIR1bits.SSP1IF);		
	PIR1bits.SSP1IF = I2C_LOW;			
}

/*******************************************************************************
 * Function:        void I2C_Stop(void)
 * Description:     Sends stop bit sequence
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         None
 ******************************************************************************/
void I2C2_Stop(void){
	SSP2CON2bits.PEN = 1;			
	while(!PIR3bits.SSP2IF);		
	PIR3bits.SSP2IF = 0;				
}

/*******************************************************************************
 * Function:        void I2C_Send_ACK(void)
 * Description:     Sends ACK bit sequence
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         None
 ******************************************************************************/
void I2C1_Send_ACK(void){	
    SSP1CON2bits.ACKDT = I2C_LOW;			
	SSP1CON2bits.ACKEN = I2C_HIGH;			
	while(!PIR1bits.SSP1IF);		
	PIR1bits.SSP1IF = I2C_LOW;		
}

/*******************************************************************************
 * Function:        void I2C_Send_ACK(void)
 * Description:     Sends ACK bit sequence
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         None
 ******************************************************************************/
void I2C2_Send_ACK(void){
	SSP2CON2bits.ACKDT = I2C_LOW;			
	SSP2CON2bits.ACKEN = I2C_HIGH;			
	while(!PIR3bits.SSP2IF);		
	PIR3bits.SSP2IF = I2C_LOW;			
}

/*******************************************************************************
 * Function:        void I2C_Send_NACK(void)
 * Description:     Sends NACK bit sequence
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         None
 ******************************************************************************/
void I2C1_Send_NACK(void){	
    SSP1CON2bits.ACKDT = I2C_HIGH;			
	SSP1CON2bits.ACKEN = I2C_HIGH;			
	while(!PIR1bits.SSP1IF);		
	PIR1bits.SSP1IF = I2C_LOW;	
}

/*******************************************************************************
 * Function:        void I2C_Send_NACK(void)
 * Description:     Sends NACK bit sequence
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         None
 ******************************************************************************/
void I2C2_Send_NACK(void){
	SSP2CON2bits.ACKDT = I2C_HIGH;			
	SSP2CON2bits.ACKEN = I2C_HIGH;			
	while(!PIR3bits.SSP2IF);		
	PIR3bits.SSP2IF = I2C_LOW;	
}

/*******************************************************************************
 * Function:        unsigned char I2C_Write(unsigned char BYTE)
 * Description:     Transfers one byte
 * Precondition:    None
 * Parameters:      BYTE = Value for slave device
 * Return Values:   Return ACK/NACK from slave
 * Remarks:         None
 ******************************************************************************/
unsigned char I2C1_Send(unsigned char BYTE){
    SSP1BUF = BYTE;                 
	while(!PIR1bits.SSP1IF);		
        PIR1bits.SSP1IF = I2C_LOW;			
	return SSP1CON2bits.ACKSTAT;   
}

/*******************************************************************************
 * Function:        unsigned char I2C_Write(unsigned char BYTE)
 * Description:     Transfers one byte
 * Precondition:    None
 * Parameters:      BYTE = Value for slave device
 * Return Values:   Return ACK/NACK from slave
 * Remarks:         None
 ******************************************************************************/
unsigned char I2C2_Send(unsigned char BYTE){
	SSP2BUF = BYTE;                 
	while(!PIR3bits.SSP2IF);		
	PIR3bits.SSP2IF = I2C_LOW;			
	return SSP2CON2bits.ACKSTAT;    
}

/*******************************************************************************
 * Function:        unsigned char I2C_Read(void)
 * Description:     Reads one byte
 * Precondition:    None
 * Parameters:      None
 * Return Values:   Return received byte
 * Remarks:         None
 ******************************************************************************/
unsigned char I2C1_Read(void){
    SSP1CON2bits.RCEN = I2C_HIGH;			
	while(!PIR1bits.SSP1IF);		
	PIR1bits.SSP1IF = I2C_LOW;			
    return SSP1BUF;   
}

/*******************************************************************************
 * Function:        unsigned char I2C_Read(void)
 * Description:     Reads one byte
 * Precondition:    None
 * Parameters:      None
 * Return Values:   Return received byte
 * Remarks:         None
 ******************************************************************************/
unsigned char I2C2_Read(void){
	SSP2CON2bits.RCEN = I2C_HIGH;			
	while(!PIR3bits.SSP2IF);		
	PIR3bits.SSP2IF = I2C_LOW;			
    return SSP2BUF;      
}


