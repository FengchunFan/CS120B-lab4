#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Check, Locked, Step1, Step2, Unlock} state;

void Tick(){
  switch(state){
    case Start:
      state = Check;
      break;
      
    case Check:
       if((PINA & 0x80) == 0x80){
        state = Locked;
       } else if ((PINA & 0x07) == 0x04){ //if only # pressed
        state = Step1;
       } else {
        state = Check;
       }
      break;
      
    case Locked:
      if((PINA & 0x80) == 0x80){
        state = Locked;
      } else {
        state = Check;
      }
      break;
      
    case Step1: // anohter # pressed
      if((PINA & 0x07) == 0x04){
        state = Step2;
      } else if ((PINA & 0x80) == 0x80){
        state = Locked;
      } else {
        state = Step1;
      }
      break;
      
     case Step2: // Y pressed
      if((PINA & 0x07) == 0x02){
        state = Unlock;
      } else if ((PINA & 0x80) == 0x80){
        state = Locked;
      } else {
        state = Step2;
      }
      break;
    
    case Unlock:
      if((PINA & 0x80) == 0x80){
        state = Locked;
      } else {
        state = check;
      }
      break;
      
    default:
      state = Start;
      break;
  }
  
  switch(state){
    case Start:
      PORTB = 0x00;
      break;
      
    case Check:
      break;
    
    case Locked:
      PORTB = 0x00;
      break;
      
    case Step1:
      break;
     
    case Step2:
      break;
      
    case Unlock:
      PORTB = 0x01;
      break;
     
    default:
      break;
  }
}

int main(void){
DDRA = 0x00; PORTA = 0xFF;
DDRB = 0xFF; PORTB = 0x00;
  while (1) {
Tick();
}
  return 1;
}
