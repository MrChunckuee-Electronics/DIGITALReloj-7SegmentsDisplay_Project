/*******************************************************************************
 *
 *      Driver para control de 7 segmentos usando el 74HC595
 *
 *******************************************************************************
 * Rev.:        v1.0.0         
 * Date:        02/03/2023
 * Author:      Pedro Sánchez (MrChunckuee)  http://mrchunckuee.blogspot.com/     
 * Description: - Creación de la libreria y prueba de las funciones implementadas 
 *                por @Cyb3rn0id https://www.settorezero.com/wordpress/pilotare-display-led-7-segmenti-mediante-74hc595-esempio-con-pic-e-arduino/
 *******************************************************************************
 * Rev.:        v1.0.1         
 * Date:        24/06/2023
 * Author:      Pedro Sánchez (MrChunckuee)   
 * Description: Adapatacion para soportar 4 digitos de display
 ******************************************************************************/

#include "main.h"


/*******************************************************************************
 * Function:        void DISPLAY_Set(uint8_t D1, uint8_t D2, uint8_t D3, uint8_t D4, uint8_t D3, uint8_t D4)
 * Description:     Carga los valores al array que controla todo el modulo de displays, 
 *                  esta pensado para un maximo de 6 digitos.
 * Precondition:    Asiganar el valor correcto a la variable NUMBERS_OF_DISPLAYS en Display7seg_74HC595.h
 * Parameters:      Los parametros recibidos son el valor independiente de cada digito,
 *                  el orden de estos es de izquierda a derecha.
 *                  D1 | D2 | D3 | D4 | D5 | D6
 * Return Values:   None
 * Remarks:         Ejemplo de uso, si quieres mostrar 5E en los displays
 *                  Tenemos que NUMBERS_OF_DISPLAYS = 6
 *                  Entonces debes DISPLAY_set(1,2,3,4,5,6);
 ******************************************************************************/
void DISPLAY_Set(uint8_t D1, uint8_t D2, uint8_t D3, uint8_t D4, uint8_t D5, uint8_t D6){
    
    switch (displayMode){
        case showTime:
            if(dotsEnable){
                display_values[5] = digits[D1];
                display_values[4] = (digits[D2])&((uint8_t)~SEG_P);
                display_values[3] = (~digits[D3])|((uint8_t)SEG_P); //cathode display
                display_values[2] = (~digits[D4])|((uint8_t)SEG_P); //cathode display
                display_values[1] = (digits[D5])&((uint8_t)~SEG_P);
                display_values[0] = digits[D6];
            }
            else{
                display_values[5] = digits[D1];
                display_values[4] = digits[D2];
                display_values[3] = ~digits[D3];    //cathode display
                display_values[2] = ~digits[D4];    //cathode display
                display_values[1] = digits[D5];
                display_values[0] = digits[D6];
            }
            break;
        case showDate:
            display_values[5] = digits[D1];
            display_values[4] = (digits[D2])&((uint8_t)~SEG_P);
            display_values[3] = ~digits[D3];                    //cathode display
            display_values[2] = (~digits[D4])|((uint8_t)SEG_P); //cathode display
            display_values[1] = digits[D5];
            display_values[0] = digits[D6];
            break;
        default:
            break;
    }
    
    
    DISPLAY_Update();
}

/*******************************************************************************
 * Function:        void DISPLAY_Reset(void)
 * Description:     Clean all displays.
 * Precondition:    None
 * Parameters:      None
 * Return Values:   None
 * Remarks:         
 ******************************************************************************/
void DISPLAY_Reset(void){
    DISPLAY_Set(DIG_OFF, DIG_OFF, DIG_OFF, DIG_OFF, DIG_OFF, DIG_OFF); 
}
 
/*******************************************************************************
 * Function:        void DISPLAY_Write(uint8_t num)
 * Description:     Writes an unsigned integer to display.
 * Precondition:    None
 * Parameters:      uint8_t num
 * Return Values:   None
 * Remarks:         
 ******************************************************************************/
void DISPLAY_Write(uint16_t num){
    uint8_t digit1=DIG_OFF;
    uint8_t digit2=DIG_OFF;
    uint8_t digit3=DIG_OFF;
    uint8_t digit4=DIG_OFF;
    uint8_t digit5=DIG_OFF;
    uint8_t digit6=DIG_OFF;
    
    if (num<10){
        digit4 = (uint8_t)(num);
    }
    else if (num<100){
        digit4 = (uint8_t)(num%10);
        digit3 = (uint8_t)(num/10);  
    }
    else if (num<1000){
        digit4 = (uint8_t)(num%10);
        digit3 = (uint8_t)((num%100)/10);
        digit2 = (uint8_t)(num/100);  
    }
    else {
        digit4 = (uint8_t)(num%10);
        digit3 = (uint8_t)((num%100)/10);
        digit2 = (uint8_t)((num%1000)/100);
        digit1 = (uint8_t)(num/1000);
    }
  DISPLAY_Set(digit1, digit2, digit3, digit4, digit5, digit6);
  }

/*******************************************************************************
 * Function:        void Driver_74HC595_shiftOut(uint8_t data)
 * Description:     Transfer datas from array in ram to shift registers
 * Precondition:    Need set value in "display_values" array
 * Parameters:      none
 * Return Values:   None
 * Remarks:         
 ******************************************************************************/
void DISPLAY_Update(void){ 
    if((NUMBERS_OF_DISPLAYS % 2) == 0){
        for (int8_t i=0; i<NUMBERS_OF_DISPLAYS; i++){
            DRIVER_74HC595_ShiftOut(display_values[i]);
        }
    }
    else{
        for (int8_t i=0; i<=NUMBERS_OF_DISPLAYS; i++){
            DRIVER_74HC595_ShiftOut(display_values[i]);
        }
    }
    // strobe signal on latch pin 
    LAT_74HC595_SetHigh();
    LAT_74HC595_SetLow();
  }

/*******************************************************************************
 * Function:        void DRIVER_74HC595_ShiftOut(uint8_t data)
 * Description:     Transmit an integer one bit at time, from MSB to LSB
 * Precondition:    None
 * Parameters:      uint8_t data
 * Return Values:   None
 * Remarks:         
 ******************************************************************************/
void DRIVER_74HC595_ShiftOut(uint8_t data){
    // scan bits from left to right
    for (uint8_t i=0; i<8; i++){
        if (data & (0x80>>i)){
            DATA_74HC595_SetHigh();
            }
        else{
            DATA_74HC595_SetLow();
            }
        // clock strobe
        CLK_74HC595_SetHigh();
        CLK_74HC595_SetLow();
    }
}