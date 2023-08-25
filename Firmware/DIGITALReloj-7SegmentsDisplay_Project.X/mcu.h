/* 
 * File:   mcu.h
 * Author: MrChunckuee
 *
 * Created on 1 de marzo de 2023, 11:47 PM
 */

#ifndef MCU_H
#define	MCU_H

#ifdef	__cplusplus
extern "C" {
#endif


#include <xc.h>
    
uint8_t displayMode = 0;

enum {showTime = 0, showDate};
    
/*********** P R O T O T Y P E S **********************************************/
void SYSTEM_Initialize(void);
void SYSTEM_Process(void);
void MCU_Initialize(void);
void OSCILLATOR_Initialize(void);
void IO_LEDPrintChar(uint8_t LEDCHAR);
void IO_LEDHello(void);
void TMR0_Initialize(void);
void RTC_Initialize(void);

void MCU_SetModeDisplay(void);
void MCU_SetOutDisplay(void);
void UpdateDateToDisplay(unsigned char* pDateArray);
void UpdateTimeToDisplay(unsigned char* pTimeArray);



#ifdef	__cplusplus
}
#endif

#endif	/* MCU_H */

