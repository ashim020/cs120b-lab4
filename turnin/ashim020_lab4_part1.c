/*	Author: Andrew Shim
 *  Partner(s) Name: 
 *	Lab Section: 21
 *	Assignment: Lab # 4  Exercise # 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, ON_PRESS, ON_RELEASE, OFF_PRESS, OFF_RELEASE} state;
void Tick() {
    switch(state) {
        case Start:
	    state = ON_PRESS;
	    PORTB = 0x01;
	    break;
	case ON_PRESS:
	    state = A0 ? ON_PRESS : ON_RELEASE;
	    break;
	case ON_RELEASE:
	    if (PINA) {
	        state = OFF_PRESS;
		PORTB = 0x02;
	    } else {
	        state = ON_RELEASE;
	    }
	    break;
	case OFF_PRESS:
	    state = A0 ? OFF_PRESS : OFF_RELEASE;
	    break;
	case OFF_RELEASE:
	    if (PINA) {
                state = ON_PRESS;
		PORTB = 0x01;
	    } else {
		state = OFF_RELEASE;
	    }
	    break;
	default:
	    state = Start;
	    break;
    }
    switch(state) {
	default:
            break;
    }
}
	    
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    while (1) {
        Tick();
    }
    return 1;
}
