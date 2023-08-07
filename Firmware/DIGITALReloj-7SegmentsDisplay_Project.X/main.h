/* 
 * File:   main.h
 * Author: MrChunckuee
 *
 * Created on 1 de marzo de 2023, 11:44 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif


/*********** I N C L U D E S **************************************************/
#include <xc.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "mcu.h"
#include "Display7seg_74HC595.h"
#include "ds1307.h"
#include "i2c.h"
#include "isr_manager.h"
    
/*********** G E N E R A L     D E F I N E S **********************************/
#define _XTAL_FREQ        16000000
#define Delay_ms(x)       __delay_ms(x)
    
/*********** P O R T   D E F I N E S ******************************************/
#define pinCtrlOutput_LED2      LATCbits.LATC2
#define pinCtrlOutput_LED3      LATCbits.LATC3
#define pinCtrlOutput_LED4      LATCbits.LATC4
#define pinCtrlOutput_LED5      LATCbits.LATC5

#define LED2_Status_SetHigh()   do { pinCtrlOutput_LED2 = true; } while(0)
#define LED2_Status_SetLow()    do { pinCtrlOutput_LED2 = false; } while(0)
#define LED2_Status_Toggle()    do { pinCtrlOutput_LED2 = ~pinCtrlOutput_LED2; } while(0)
    
#define LED3_Status_SetHigh()   do { pinCtrlOutput_LED3 = true; } while(0)
#define LED3_Status_SetLow()    do { pinCtrlOutput_LED3 = false; } while(0)
#define LED3_Status_Toggle()    do { pinCtrlOutput_LED3 = ~pinCtrlOutput_LED3; } while(0)
    
#define LED4_Status_SetHigh()   do { pinCtrlOutput_LED4 = true; } while(0)
#define LED4_Status_SetLow()    do { pinCtrlOutput_LED4 = false; } while(0)
#define LED4_Status_Toggle()    do { pinCtrlOutput_LED4 = ~pinCtrlOutput_LED4; } while(0)
    
#define LED5_Status_SetHigh()   do { pinCtrlOutput_LED5 = true; } while(0)
#define LED5_Status_SetLow()    do { pinCtrlOutput_LED5 = false; } while(0)
#define LED5_Status_Toggle()    do { pinCtrlOutput_LED5 = ~pinCtrlOutput_LED5; } while(0)
    
    

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

