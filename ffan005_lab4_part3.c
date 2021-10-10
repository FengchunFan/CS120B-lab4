#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, } state;

void Tick(){
  switch(state){
  
  }
  
  switch(state){
     
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
