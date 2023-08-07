/* 
 * File:   isr_manager.h
 * Author: mrchu
 *
 * Created on 6 de agosto de 2023, 06:19 PM
 */

#ifndef ISR_MANAGER_H
#define	ISR_MANAGER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
bool TMR0_OVR_FLAG = false;    

void ISR_Initialize(void);
void ISR_Close(void);


#ifdef	__cplusplus
}
#endif

#endif	/* ISR_MANAGER_H */

