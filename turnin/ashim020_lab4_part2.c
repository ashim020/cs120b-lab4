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

enum States {Start, BOTH_OFF, ONE_ON, TO_ONE_ON, TWO_ON, TO_TWO_ON, BOTH_ON} state;
void Tick() {
    switch(state) {
        case Start:
	    state = BOTH_OFF;
	    break;
	case BOTH_OFF:
	    if ((PINA & 0x01) == 0x01) {
	        state = TO_ONE_ON;
	    }
	    else if ((PINA & 0x02) == 0x02) {
                state = TO_TWO_ON;
	    }
	    else if ((PINA & 0x03) == 0x03) {
		state = BOTH_ON;
            }
	    else {
		state = BOTH_OFF;
	    }
	    break;
	case ONE_ON:
	    if ((PINA & 0x01) == 0x01) {
	        state = ONE_ON;
	    } else {
	        state = BOTH_OFF;
	    }
	    break;
	case TO_ONE_ON:
	    state = ONE_ON;
	    break;
	case TWO_ON:
	    if ((PINA & 0x02) == 0x02) {
                state = TWO_ON;
	    } else {
	        state = BOTH_OFF;
	    }
	    break;
	case TO_TWO_ON:
	    state = TWO_ON;
	    break;
	case BOTH_ON:
	    if ((PINA & 0x03) == 0x03) {
	        state = BOTH_ON;
	    } else {
		state = BOTH_OFF;
            }
	    break;
	default:
	    state = Start;
	    break;
    }
    switch(state) {
	case Start:
	    PORTC = 0x07;
	    break;
	case TO_ONE_ON:
	    if (PORTC < 9) {
                PORTC += 1;
	    }
            break;
	case TO_TWO_ON:
	    if (PORTC > 0) {
		PORTC -= 1;
	    }
	    break;
	case BOTH_ON:
	    PORTC = 0x00;
	    break;
	default:
	    PORTC = 0x07;
	    break;
    }
}
	    
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
    while (1) {
        Tick();
    }
    return 1;
}
