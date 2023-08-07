/*******************************************************************************
 *
 *                 i2c Library
 *
 *******************************************************************************
 * FileName:        i2c.h
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
 ******************************************************************************/

#ifndef I2C_H
#define	I2C_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <xc.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
    
/*********** G E N E R A L   D E F I N E S ************************************/
#define I2C_INPUT   1
#define I2C_LOW     0
#define I2C_HIGH    1
#define I2C_SPEED	100         // Define i2c speed kbps
    
/*********** P O R T   D E F I N E S ******************************************/
#define SDA1        LATCbits.LATC4             // Data pin for i2c
#define SCK1        LATCbits.LATC3				// Clock pin for i2c
#define SDA1_DIR    TRISCbits.RC4   // Data pin direction
#define SCK1_DIR	TRISCbits.RC3	// Clock pin direction
  
#if defined _18F46K22
    #define SDA2        RD1				// Data pin for i2c
    #define SCK2        RD0				// Clock pin for i2c
    #define SDA2_DIR    TRISDbits.RD1   // Data pin direction
    #define SCK2_DIR	TRISDbits.RD0	// Clock pin direction  
#elif defined _18F25K22
    #define SDA2        RB2				// Data pin for i2c
    #define SCK2        RB1				// Clock pin for i2c
    #define SDA2_DIR    TRISBbits.RB2   // Data pin direction
    #define SCK2_DIR	TRISBbits.RB1	// Clock pin direction  
#endif


/*********** P R O T O T Y P E S **********************************************/
void I2C1_Init(void);
void I2C1_Start(void);
void I2C1_ReStart(void);
void I2C1_Stop(void);
void I2C1_Send_ACK(void);
void I2C1_Send_NACK(void);
unsigned char I2C1_Send(unsigned char BYTE);
unsigned char I2C1_Read(void);

void I2C2_Init(void);
void I2C2_Start(void);
void I2C2_ReStart(void);
void I2C2_Stop(void);
void I2C2_Send_ACK(void);
void I2C2_Send_NACK(void);
unsigned char I2C2_Send(unsigned char BYTE);
unsigned char I2C2_Read(void);

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

