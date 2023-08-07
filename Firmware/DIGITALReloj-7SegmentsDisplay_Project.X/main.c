/*******************************************************************************
 *
 *      Reloj digital - Display 7 segmentos y 74HC595
 *
 *******************************************************************************
 * FileName:        main.c
 * Processor:       PIC18F25K22
 * Complier:        XC8 v2.36
 * Author:          Pedro Sánchez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description: 
 *
 *******************************************************************************
 * Rev.         Date            Comment
 *   v0.0.1     30/07/2023      - Creación y prueba de funcionamiento, se implemento 
 *                                la rutina para iniciazar el RTC y despues mostar los 
 *                                datos en el displays de momento el formato es HH:MM
 ******************************************************************************/

#include "device_config.h" //Config fuses
#include "main.h"

void main(void) {
    SYSTEM_Initialize();
    while(1){
        SYSTEM_Process(); //Show digits
    }
}
