/*
 * File:   isr_manager.c
 * Author: mrchu
 *
 * Created on 6 de agosto de 2023, 06:19 PM
 */


#include "main.h"

/*******************************************************************************
 * Function:        void ISR_Init(void)
 * Description:     Habilita prioridad de interrupcion y las habilita
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:
 ******************************************************************************/
void ISR_Initialize(void){
    RCONbits.IPEN=1;      //Interrupt Priority Enable bit, Enable priority level on interrupt
    INTCONbits.GIEL=1;
    INTCONbits.GIEH=1;
}

/*******************************************************************************
 * Function:        void ISR_Close(void)
 * Description:     Deshabilita las interrupciones
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:
 ******************************************************************************/
void ISR_Close(void){
    INTCONbits.GIEL = 0;
    INTCONbits.GIEH = 0;
}

/*******************************************************************************
 * Function:        void __interrupt(high_priority) INTERRUPT_HighManager(void)
 * Description:     Rutina de atencion para las interripciones de alta prioridad
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:
 ******************************************************************************/
void __interrupt(high_priority) INTERRUPT_HighManager(void){
    if(INTCONbits.TMR0IE && INTCONbits.TMR0IF){
        INTCONbits.TMR0IF = 0;
        TMR0_OVR_FLAG = true;
        WRITETIMER0(0xF830);
    }
}

/*******************************************************************************
 * Function:        void __interrupt(low_priority) INTERRUPT_LowManager(void)
 * Description:     Rutina de atencion para las interripciones de baja prioridad
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:
 ******************************************************************************/
void __interrupt(low_priority) INTERRUPT_LowManager(void){

}
