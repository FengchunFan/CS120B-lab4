#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Initial, Press, Increment, Decrement, Reset} state;

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
        state = Increment;
      } else if ((PINA & 0x02) == 0x02){
        state = Decrement;
      } else if ((PINA & 0x03) == 0x03){
        state = Reset;
      }
     break;
        
    case Increment:
      if((PINA & 0x01) == 0x01){
        state = Increment;
      } else if ((PINA & 0x02) == 0x02){
        state = Decrement;
      } else if ((PINA & 0x03) == 0x03){
        state = Reset;
      }
     break;
      
    case Decrement:
      if((PINA & 0x02) == 0x02){
        state = Decrement;
      } else if ((PINA & 0x01) == 0x01){
        state = Increment;
      } else if ((PINA & 0x03) == 0x03){
        state = Reset;
      }
     break;
      
    case Reset:
      if((PINA & 0x03) == 0x03){
        state = Reset;
      } else if ((PINA & 0x02) == 0x02){
        state = Decrement;
      } else if ((PINA & 0x01) == 0x01){
        state = Increment;
      }
     break;
      
    default:
      state = Start;
      break;
  }
  
  switch(state){
    case Start:
      PORTC = 0x07;
      break;
      
    case Initial:
      PORTC = 0x07;
      break;
      
    case Press:
      break;
      
    case Increment:
      if(PORTC < 0x08){
        PORTC = PORTC + 0x01;
      }
      break;
      
    case Decrement:
      if(PORTC > 0x00){
        PORTC = PORTC - 0x01;
      }
     break;
      
    case Reset:
      PORTC = 0x00;
      break;
      
    default:
      PORTC = 0x07;
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
