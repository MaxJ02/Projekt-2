#include "header.h"

/*************************************************************************

* interrupts.c: Innehåller avbrottsrutiner

*************************************************************************/
ISR (INT0_vect)
{
	fsm_reset();
	// Resettar tillståndsmaskinen.
}


ISR (INT1_vect) // Stigande flank på pin 3.
{
	fsm_update();
	
	return;
}

ISR (PCINT0_vect)
{
	if (PREVIOUS_BUTTON_PRESSED || NEXT_BUTTON_PRESSED || NEXT_BUTTONX2_PRESSED) // Kollar ifall någon av knapparna är nedtryckt. Om sant, uppdatera. 
	{
		fsm_update();
	}
	
	return;
}
