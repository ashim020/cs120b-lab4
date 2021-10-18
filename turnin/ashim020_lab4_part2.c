/*	Author: Andrew Shim
 *  Partner(s) Name: 
 *	Lab Section: 21
 *	Assignment: Lab # 4  Exercise # 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, INIT, INC, DEC, RESET, S1, S2, S3} state;
void Tick() {
    switch(state) {
        case Start:
	    state = INIT;
	    break;
	case S1:
	    if ((PINA & 0x03) == 0x01) {
	        state = S1;
	    }
	    else if ((PINA & 0x03) == 0x02) {
                state = DEC;
	    }
	    else if ((PINA & 0x03) == 0x03) {
		state = RESET;
            }
	    else if ((PINA & 0x03) == 0x00) {
		state = INIT;
	    }
	    break;
	case S2:
	    if ((PINA & 0x03) == 0x01) {
	        state = INC;
	    }
	    else if ((PINA & 0x03) == 0x02) {
                state = S2;
	    }
	    else if ((PINA & 0x03) == 0x03) {
		state = RESET;
            }
	    else if ((PINA & 0x03) == 0x00) {
		state = INIT;
	    }
	    break;
	case S3:
	    if ((PINA & 0x03) == 0x00) {
	        state = INIT;
	    }
	    else {
		state = S3;
	    }
	    break;
	case INC:
	    state = S1;
	    break;
	case DEC:
	    state = S2;
	    break;
	case RESET:
	    state = s3;
	    break;
	default:
	    state = INIT;
	    break;
    }
    switch(state) {
	case INIT:
	    break;
	case INC:
	    if (PORTC < 9) {
                PORTC += 1;
	    }
            break;
	case DEC:
	    if (PORTC > 0) {
		PORTC -= 1;
	    }
	    break;
	case RESET:
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
    DDRC = 0xFF; PORTC = 0x07;
    /* Insert your solution below */
    while (1) {
        Tick();
    }
    return 1;
}
