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

enum States {Start, Initial, Press, Increment, Decrement, Temp1, Temp2, Reset} state;

void Tick() {
	switch(state) {
		case Start:
			state = Initial;
			break;
      
		case Initial:
			state = Press;
			break;
      
		case Init:
			if ((PINA & 0x01) == 0x01) {
        state = Temp1;
      }
			else if ((PINA & 0x02) == 0x02) {
				state = Temp2;
			}
			else if ((PINA & 0x03) == 0x03) {
        state = Reset;
                        }
			break;
      
		case Increment:
			if ((PINA & 0x01) == 0x01) {
        state = Increment;
      }else {
        state = Press;
      }
      break;
	
		case Decrement:
      if ((PINA & 0x02) == 0x02) {
      state = Decrement;
      } else {
      state = Press;
      }
      break;
    
    case Reset:
			if ((PINA & 0x03) == 0x03) {
				state = Reset;
			}
			else {
				state = Press;
			}
			break;
      
		case Temp1:
			state = Increment;
			break;
		case Temp2:
			state = Decrement;
			break;
			
		default:
			state = Start;
			break;
	}
  
	switch(state) {
		case Start:
			PORTC = 0x07;
			break;
      
		case Initial:
			PORTC = 0x07;
			break;
      
		case Press:
			break;
      
		case Increment:
			break;
      
		case Decrement:
			break;
      
         
		case Reset:
			PORTC = 0x00;
			break;
      
		case Temp1:
			if (PORTC < 0x08) {
        PORTC = PORTC + 1;
			}
      break;
      
		case Temp2:
			if (PORTC > 0x00) { 
        PORTC = PORTC - 1;
			}
     break;
   
		default:
			PORTC = 0x07;
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
    /* Insert your solution below */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    while (1) {
	Tick();
    }
    return 1;
}
