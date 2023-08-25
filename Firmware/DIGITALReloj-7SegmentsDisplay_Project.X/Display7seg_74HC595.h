/* 
 * File:   Display7seg_74HC595.h
 * Author: mrchu
 *
 * Created on 6 de marzo de 2023, 11:22 PM
 */

#ifndef DISPLAY7SEG_74HC595_H
#define	DISPLAY7SEG_74HC595_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    
uint8_t NUMBERS_OF_DISPLAYS     =   6;
bool dotsEnable = false;
    
/*********** P I N O U T  *  D E F I N E S ************************************/
#define pin_SRCLK_74HC595   LATBbits.LATB2  //Pin 11 (SRCLK)
#define pin_RCLK_74HC595    LATBbits.LATB1  //Pin 12 (RCLK)
#define pin_SER_74HC595     LATBbits.LATB0  //Pin 14 (SER)
    
#define CLK_74HC595_SetHigh()   do { pin_SRCLK_74HC595 = true; } while(0)
#define CLK_74HC595_SetLow()    do { pin_SRCLK_74HC595 = false; } while(0)
    
#define LAT_74HC595_SetHigh()   do { pin_RCLK_74HC595 = true; } while(0)
#define LAT_74HC595_SetLow()    do { pin_RCLK_74HC595 = false; } while(0)
    
#define DATA_74HC595_SetHigh()   do { pin_SER_74HC595 = true; } while(0)
#define DATA_74HC595_SetLow()    do { pin_SER_74HC595 = false; } while(0)
    
/*********** D I S P L A Y S  *  D E F I N E S ********************************/  

// display segments as attached on shift registers bits
// data is MSB to LSB
#define SEG_A 0b00010000  
#define SEG_B 0b00001000  
#define SEG_C 0b00000001
#define SEG_D 0b00000100 
#define SEG_E 0b00000010  
#define SEG_F 0b01000000 
#define SEG_G 0b10000000  
#define SEG_P 0b00100000  // decimal point

// digits definition
// I've put ~ because display used is common anode, so 1=segment off and 0=segment on
uint8_t digits[]={          //  index value=digit showed on display
    (uint8_t)~(SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F),           //  0=0
    (uint8_t)~(SEG_B|SEG_C),                                   //  1=1
    (uint8_t)~(SEG_A|SEG_B|SEG_D|SEG_E|SEG_G),                 //  2=2
    (uint8_t)~(SEG_A|SEG_B|SEG_C|SEG_D|SEG_G),                 //  3=3
    (uint8_t)~(SEG_B|SEG_C|SEG_F|SEG_G),                       //  4=4
    (uint8_t)~(SEG_A|SEG_C|SEG_D|SEG_F|SEG_G),                 //  5=5
    (uint8_t)~(SEG_A|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G),           //  6=6
    (uint8_t)~(SEG_A|SEG_B|SEG_C),                             //  7=7
    (uint8_t)~(SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G),     //  8=8
    (uint8_t)~(SEG_A|SEG_B|SEG_C|SEG_D|SEG_F|SEG_G),           //  9=9
    (uint8_t)~(SEG_A|SEG_B|SEG_C|SEG_E|SEG_F|SEG_G),           // 10=A
    (uint8_t)~(SEG_C|SEG_D|SEG_E|SEG_F|SEG_G),                 // 11=b
    (uint8_t)~(SEG_A|SEG_D|SEG_E|SEG_F),                       // 12=C
    (uint8_t)~(SEG_B|SEG_C|SEG_D|SEG_E|SEG_G),                 // 13=d
    (uint8_t)~(SEG_A|SEG_D|SEG_E|SEG_F|SEG_G),                 // 14=E
    (uint8_t)~(SEG_A|SEG_E|SEG_F|SEG_G),                       // 15=F
    (uint8_t)~(0)                                              // 16=all segments OFF
    };

// mnemonic to array index for non-numbers
#define DIG_A       10
#define DIG_B       11
#define DIG_C       12
#define DIG_D       13
#define DIG_E       14
#define DIG_F       15
#define DIG_OFF     16

// digits in ram
uint8_t display_values[7];

/*********** P R O T O T Y P E S **********************************************/
void DISPLAY_Set(uint8_t D1, uint8_t D2, uint8_t D3, uint8_t D4, uint8_t D5, uint8_t D6);
void DISPLAY_Reset(void);
void DISPLAY_Write(uint16_t num);
void DISPLAY_Update(void);
void DRIVER_74HC595_ShiftOut(uint8_t data);

#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY7SEG_74HC595_H */

