#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Initial, Press, Increment, Decrement, Reset} state;

void Tick(){
  switch(state){
    case Start:
      state = Initial;
      PORTC = 0x07;
      break;
      
    case Initial:
      state = Press;
      PORTC = 0x07;
      break;
      
    case Press:
      if((PINA & 0x01) == 0x01){
        state = Increment;
        if(PORTC < 0x08){
        PORTC = PORTC + 0x01;
      }
      } else if ((PINA & 0x02) == 0x02){
        state = Decrement;
        if(PORTC > 0x00){
        PORTC = PORTC - 0x01;
      }
      } else if ((PINA & 0x03) == 0x03){
        state = Reset;
        PORTC = 0x00;
      }
     break;
        
    case Increment:
      if((PINA & 0x01) == 0x01){
        state = Increment;
        if(PORTC < 0x08){
        PORTC = PORTC + 0x01;
      }
      } else if ((PINA & 0x02) == 0x02){
        state = Decrement;
        if(PORTC > 0x00){
        PORTC = PORTC - 0x01;
      }
      } else if ((PINA & 0x03) == 0x03){
        state = Reset;
        PORTC = 0x00;
      }
     break;
      
    case Decrement:
      if((PINA & 0x02) == 0x02){
        state = Decrement;
        if(PORTC > 0x00){
        PORTC = PORTC - 0x01;
      }
      } else if ((PINA & 0x01) == 0x01){
        state = Increment;
        if(PORTC < 0x08){
        PORTC = PORTC + 0x01;
      }
      } else if ((PINA & 0x03) == 0x03){
        state = Reset;
        PORTC = 0x00;
      }
     break;
      
    case Reset:
      if((PINA & 0x03) == 0x03){
        state = Reset;
        PORTC = 0x00;
      } else if ((PINA & 0x02) == 0x02){
        state = Decrement;
        if(PORTC > 0x00){
        PORTC = PORTC - 0x01;
      }
      } else if ((PINA & 0x01) == 0x01){
        state = Increment;
        if(PORTC < 0x08){
        PORTC = PORTC + 0x01;
      }
      }
     break;
      
    default:
      state = Start;
      break;
  }
  
  switch(state){
  
}

int main(void){
DDRA = 0x00; PORTA = 0xFF;
DDRC = 0xFF; PORTC = 0x00;
  while (1) {
Tick();
}
  return 1;
}
