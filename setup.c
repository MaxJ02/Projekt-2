#include "header.h"

/***************************************************************************
* setup.c: Filen innehåller alla programmets initieringsrutiner.
****************************************************************************/




//Statiska funktioner
static inline void init_ports(void);
static inline void init_interrupts(void);



//Setup initierar mikrodatorn vid starten. 


void setup(void)
{
	init_ports();
	init_interrupts();
	return;
}


/**************************************************************************
* init_ports: Sätter lysdiodernas pins till utportar och sätter knapparnas
  pins till aktiva inportar där signalen alltid blir antingen 0 eller 1.
***************************************************************************/

static inline void init_ports(void)
{
	DDRB = (1 << LED1) | (1 << LED2) | (1 << LED3);
	PORTB = (1 << PREVIOUS_BUTTON) | (1 << NEXT_BUTTON) | (1 << NEXT_BUTTONX2);
	PORTD = (1 << RESET_BUTTON) | (1 << PREVIOUS_BUTTONX2);
	return;
}


/************************************************************************
* init_interrupts: Aktiverar avbrott på pinsen 2 - 3 som ligger
*på PORTD2 - PORTD3 samt pin 11 - 13 som ligger på PORTB3 - PORTB5.
*************************************************************************/

static inline void init_interrupts(void)
{
	asm("SEI");
	PCICR = (1 << PCIE0); // Aktiverar avbrott på I/O-port B (PIN 8 – 13)
	PCMSK0 = (1 << PREVIOUS_BUTTON) | (1 << NEXT_BUTTON) | (1 << NEXT_BUTTONX2); // Aktiverar avbrott på PORTB3 - PORTB5 (PIN 11 - 13).
	
	EICRA = (1 << ISC10) | (1 << ISC11) | (1 << ISC01); // Ställer in flanker, sätter dock inte på dem.
	EIMSK = (1 << INT1) | (1 << INT0); //Aktiverar abrotten på pin 2 - 3 (PORTB3 och PORTB5)
	return;
}
