/*
 * File:   mcu.c
 * Author: MrChunckuee
 *
 * Created on 1 de marzo de 2023, 11:48 PM
 */

#include "main.h"

uint8_t tmr0_counterMs = 0;
uint8_t mSeconds = 0, Seconds = 0;
uint8_t dotsCounter = 0;
uint8_t timeToDisplay[7]; // Displays time in HH:MM:SS AM/PM format
uint8_t dateToDisplay[7]; // Displays Date in DD:MM:YY @ Day format

/*******************************************************************************
 * Function:        void SYSTEM_Initialize(void)
 * Description:     Funcion de inicializacion.
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         Inicializa las funciones correspondientes para que el sitema 
 *                  comience de forma adecuada.
 ******************************************************************************/
void SYSTEM_Initialize(void){
    MCU_Initialize();
    OSCILLATOR_Initialize();
    TMR0_Initialize();
    I2C1_Init();	// Initialize i2c pins	
    DISPLAY_Reset(); //Clear displays
    __delay_ms(10);
    //RTC_Initialize(); // Initialize RTC values
    ISR_Initialize();
}

/*******************************************************************************
 * Function:        void SYSTEM_Process(void)
 * Description:     Funcion de procesos.
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         
 ******************************************************************************/
void SYSTEM_Process(void){
    if(TMR0_OVR_FLAG == true){
        tmr0_counterMs++;
        if(tmr0_counterMs>99){
            tmr0_counterMs = 0;
            MCU_SetModeDisplay();
            MCU_SetOutDisplay();
        }
        TMR0_OVR_FLAG = false;
    }    
}

/*******************************************************************************
 * Function:        void MCU_Initialize(void)
 * Description:     Inicializa puertos 
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         
 ******************************************************************************/
void MCU_Initialize(void){
    //Puertos digitales
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    
    //Puertos como salida
    TRISA = 0x00;
    TRISB = 0x00;
    TRISC = 0x00;
    
    //Limpiamos puertos
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    
}

/*******************************************************************************
 * Function:        void OSCILLATOR_Initialize(void)
 * Description:     Configuracion de oscilador
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         
 ******************************************************************************/
void OSCILLATOR_Initialize(void){
    //Configura oscilador interno a 16MHz
    OSCCONbits.IRCF=0b111; //El ciclo de instruccion es de 0.25 us
}

void TMR0_Initialize(void){
    //Configuración del TMR0 = 1mS
    T0CONbits.TMR0ON = 1; //TMR0 On
    T0CONbits.T08BIT = 0; //16 bits
    T0CONbits.T0CS = 0;
    T0CONbits.T0SE = 0;
    T0CONbits.PSA = 0;
    T0CONbits.T0PS = 0b000; // Prescaler = 2
//    TMR0H = 0xF8;
//    TMR0L = 0x30;
    WRITETIMER0(0xF830);
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;
    INTCON2bits.TMR0IP = 1;
}

void RTC_Initialize(void){
    // Set initial time
	Set_DS1307_RTC_Time(AM_Time, 12, 12, 0);	// Set time 11:30:00 PM
	// Set initial date
	Set_DS1307_RTC_Date(20, 8, 23, Sunday); 	// Set 25-07-2017 @ Tuesday
}

void MCU_SetModeDisplay(void){
    mSeconds++;
    if(mSeconds>9){
        mSeconds = 0;
        Seconds ++;
        if(Seconds >59)
            Seconds = 0;
        switch(Seconds){
            case 0:
                displayMode = showTime;
                break;
            case 49:
                displayMode = showDate;
                break;
            default:
                break;
        }
    }
}

void MCU_SetOutDisplay(void){
    switch (displayMode){
        case showTime:
            dotsCounter++;
            if(dotsCounter>9){
                dotsCounter = 0;
                dotsEnable ^= true;
            }
            UpdateTimeToDisplay(Get_DS1307_RTC_Time());
            break;
        case showDate:
            UpdateDateToDisplay(Get_DS1307_RTC_Date());
            break;
        default:
            break;
    }
}

void UpdateTimeToDisplay(unsigned char* pTimeArray){   // Displays time in HH:MM:SS AM/PM format  
    // Display Hour
    timeToDisplay[0] = pTimeArray[2]/10; 
    timeToDisplay[1] = pTimeArray[2]%10;
	//Display Minutes
    timeToDisplay[2] = pTimeArray[1]/10; 
    timeToDisplay[3] = pTimeArray[1]%10;
    //Display Seconds
    timeToDisplay[4] = pTimeArray[0]/10; 
    timeToDisplay[5] = pTimeArray[0]%10;
    // Display mode
//	switch(pTimeArray[3]){
//        case AM_Time:   LCD_Putrs("AM", 9, 0);  break;
//        case PM_Time:   LCD_Putrs("PM", 9, 0);  break;
//        default:        LCD_Putrs('H', 9, 0);   break;
//	}
   DISPLAY_Set(timeToDisplay[0], timeToDisplay[1], timeToDisplay[2], timeToDisplay[3], timeToDisplay[4], timeToDisplay[5]);
}

void UpdateDateToDisplay( unsigned char* pDateArray ){   // Displays Date in DD:MM:YY @ Day format
	// Display Date
    dateToDisplay[0] = pDateArray[1]/10; 
    dateToDisplay[1] = pDateArray[1]%10; 
    //Display Month
    dateToDisplay[2] = pDateArray[2]/10; 
    dateToDisplay[3] = pDateArray[2]%10; 
	//Display Year
    dateToDisplay[4] = pDateArray[3]/10; 
    dateToDisplay[5] = pDateArray[3]%10; 
	// Display Day
//	switch(pDateArray[0]){
//        case Monday:	LCD_Putrs("MON", 9, 1);	break;
//        case Tuesday:	LCD_Putrs("TUE", 9, 1);	break;
//        case Wednesday:	LCD_Putrs("WED", 9, 1);	break;
//        case Thursday:	LCD_Putrs("THU", 9, 1);	break;
//        case Friday:	LCD_Putrs("FRI", 9, 1);	break;
//        case Saturday:	LCD_Putrs("SAT", 9, 1);	break;
//        case Sunday:	LCD_Putrs("SUN", 9, 1);	break;
//        default:        LCD_Putrs("???", 9, 1);	break;
//	}
    DISPLAY_Set(dateToDisplay[0], dateToDisplay[1], dateToDisplay[2], dateToDisplay[3], dateToDisplay[4], dateToDisplay[5]);
}