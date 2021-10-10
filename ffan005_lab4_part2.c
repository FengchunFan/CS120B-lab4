/*     Author: ffan005
 *  Partner(s) Name:
 *      Lab Section:
 *      Assignment: Lab #  Exercise #
 *      Exercise Description: [optional - include for your own benefit]
 *
 *      I acknowledge all content contained herein, excluding template or example
 *      code, is my own original work.
 */
//After continuly failing half of the tests, I got some help from the TA
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Initial, Press, Increment, Decrement, Reset, Incre, Decre} state;

void Tick(){
  switch(state){
    case Start:
      state = Initial;
      break;
      
    case Initial:
      state = Press;
      break;
      
    case Press:
      if((PINA & 0x01) == 0x01){
        state = Incre;
      } else if ((PINA & 0x02) == 0x02){
        state = Decre;
      } else if ((PINA & 0x03) == 0x03){
        state = Reset;
      }
     break;
        
    case Increment:
      if((PINA & 0x01) == 0x01){
        state = Increment;
      } else if ((PINA & 0x02) == 0x02){
        state = Decre;
      } else if ((PINA & 0x03) == 0x03){
        state = Reset;
      }
     break;
      
    case Decrement:
      if((PINA & 0x02) == 0x02){
        state = Decrement;
      } else if ((PINA & 0x01) == 0x01){
        state = Incre;
      } else if ((PINA & 0x03) == 0x03){
        state = Reset;
      }
     break;
      
    case Reset:
      if((PINA & 0x03) == 0x03){
        state = Reset;
      } else if ((PINA & 0x02) == 0x02){
        state = Decre;
      } else if ((PINA & 0x01) == 0x01){
        state = Incre;
      }
     break;
    
    case Incre:
      state = Increment;
      break;
      
    case Decre:
      state = Decrement;
      break;
      
    default:
      state = Start;
      break;
  }
  
  switch(state){
    case Start:
      break;
      
    case Initial:
      PORTC = 0x07;
      break;
      
    case Press:
      break;
      
    case Incre:
      if(PORTC <= 0x09){
        PORTC = PORTC + 1;
      } 
      break;
      
    case Decre:
      if(PORTC > 0x00){
        PORTC = PORTC - 1;
      }
     break;
      
    case Increment:
      break;
      
    case Decrement:
      break;
      
    case Reset:
      PORTC = 0x00;
      break;
      
    default:
      break;
  }
}

int main(void){
DDRA = 0x00; PORTA = 0xFF;
DDRC = 0xFF; PORTC = 0x00;
  while (1) {
Tick();
}
  return 1;
}
