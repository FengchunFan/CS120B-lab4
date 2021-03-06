/*     Author: ffan005
 *  Partner(s) Name:
 *      Lab Section:
 *      Assignment: Lab #  Exercise #
 *      Exercise Description: [optional - include for your own benefit]
 *
 *      I acknowledge all content contained herein, excluding template or example
 *      code, is my own original work.
 */
 
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

// I feel this is very much like #3 in the in-class exercise, and I will borrow the template
enum States {offRelease, onPress, onRelease, offPress, Start} state;

void Tick(){
  switch(state){
   case Start:
    state = offRelease;
    break;
    
   case onPress:
    if((PINA & 0x01) == 0x01){
     state = onPress;
    } else {
     state = onRelease;
    }
    break;
    
   case onRelease:
    if((PINA & 0x01) == 0x01){
     state = offPress;
    } else {
     state = onRelease;
    }
    break;
    
   case offPress:
    if((PINA & 0x01) == 0x01){
     state = offPress;
    } else {
     state = offRelease;
    }
    break;
    
   case offRelease:
    if((PINA & 0x01) == 0x01){
     state = onPress;
    } else {
     state = offRelease;
    }
    break;
  
   default:
    state = Start;
    break;
  }
 
  switch(state){
   case Start:
    PORTB = 0x01;
    break;
     
   case onPress:
    PORTB = 0x02;
    break;
    
   case onRelease:
    PORTB = 0x02;
    break;
    
   case offPress:
    PORTB = 0x01;
    break;
 
   case offRelease:
    PORTB = 0x01;
    break;
    
   default:
    PORTB = 0x01;
    break;
  }
}

int main(void) {
DDRA = 0x00; PORTA = 0xFF;
DDRB = 0xFF; PORTB = 0x00;
  while (1) {
Tick();
}
  return 1;
}
