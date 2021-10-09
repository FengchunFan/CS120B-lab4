#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Initial, Press, Increment,Temp1, Decrement, Temp2, Reset} state;


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
        state = Temp1;
      } else if ((PINA & 0x02) == 0x02){
        state = Temp2;
      } else if ((PINA & 0x03) == 0x03){
        state = Reset;
      }
     break;
        
    /*case Increment:
      if((PINA & 0x01) == 0x01){
        state = Temp1;
      } else {
        state = Press;
      }
     break;
      
    case Decrement:
      if((PINA & 0x02) == 0x02){
        state = Temp2;
      } else {
        state = Press;
      } 
     break;
      
    case Reset:
      if((PINA & 0x03) == 0x03){
        state = Reset;
      } else {
        state = Press;
      }
     break;
      
    case Temp1:
      state = Increment;
      break;
      
    case Temp2:
      state = Decrement;
      break;
      */
      
    case Temp1:
      state = Press;
    case Temp2:
      state = Press;
    case Reset:
      state = Press;
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
      
    case Temp1:
      if(PORTC < 0x08){
        PORTC = PORTC + 0x01;
      }
      break;
      
    case Temp2:
      if(PORTC > 0x00){
        PORTC = PORTC - 0x01;
      }
     break;
      
    case Reset:
      PORTC = 0x00;
      break;
    
   /* case Increment:
      break;
      
    case Decrement:
      break;
      */
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
