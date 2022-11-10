#ifndef HEADER_H_
#define HEADER_H_

/* Klockfrekvens*/
#define F_CPU 16000000UL /* 16 MHz. */

/* Inkluderingsdirektiv: */
#include <avr/io.h>    
#include <avr/interrupt.h>
#include <util/delay.h>    



#define LED1 0 /* Lysdiod 1 ansluten till pin 8 / PORTB0. */
#define LED2 1 /* Lysdiod 2 ansluten till pin 9 / PORTB1. */
#define LED3 2 /* Lysdiod 3 ansluten till pin 10 / PORTB2. */



#define LED1_ON PORTB |= (1 << LED1) /* Tänder lysdiod 1. */
#define LED2_ON PORTB |= (1 << LED2) /* Tänder lysdiod 2. */
#define LED3_ON PORTB |= (1 << LED3) /* Tänder lysdiod 3. */



#define LED1_OFF PORTB &= ~(1 << LED1) /* Släcker lysdiod 1. */
#define LED2_OFF PORTB &= ~(1 << LED2) /* Släcker lysdiod 2. */
#define LED3_OFF PORTB &= ~(1 << LED3) /* Släcker lysdiod 3. */



#define LEDS_ON PORTB |= (1 << LED1) | (1 << LED2) | (1 << LED3) /* Tänder alla lysdioderna */
#define LEDS_OFF PORTB &= ~((1 << LED1) | (1 << LED2) | (1 << LED3)) /* Släcker alla lysdioderna */

#define RESET_BUTTON 2 /* Reset-knapp ansluten till pin 2 / PORTD2. */
#define PREVIOUS_BUTTONX2 3/* Knapp för byte till för byte av tillstånd, två steg bakåt. Ansluten till pin 3 / PORTD3 */
#define PREVIOUS_BUTTON 3 /* Knapp för byte till föregående tillstånd ansluten till pin 11 / PORTB3. */
#define NEXT_BUTTON 4   /* Knapp för byte till nästa tillstånd ansluten till pin 12 / PORTB4. */
#define NEXT_BUTTONX2 5 /* Knapp för byte till nästa tillstånd två steg frammåt, ansluten till pin 13 / PORTB5 */

#define RESET_BUTTON_PRESSED (PIND & (1 << RESET_BUTTON))       /* Indikerar nedtryckning av reset-knappen. */
#define PREVIOUS_BUTTON_PRESSED (PINB & (1 << PREVIOUS_BUTTON)) /* Indikerar byte till föregående tillstånd. */
#define PREVIOUS_BUTTONX2_PRESSED (PIND & (1 << PREVIOUS_BUTTONX2)) /* Indikerar byte till föregående tillstånd två steg bakåt. */
#define NEXT_BUTTON_PRESSED (PINB & (1 << NEXT_BUTTON))         /* Indikerar byte till nästa tillstånd */
#define NEXT_BUTTONX2_PRESSED (PINB & (1 << NEXT_BUTTONX2)) /* Indikerar byte till nästa tillstånd två steg frammåt */

typedef enum { false, true } bool; //Bool = Datatyp för lagring av true eller false. 

/******************************************************************
* enum state: Datatyp för lagring av lysdiodernas tillstånd.
********************************************************************/
enum state { STATE_OFF, STATE_SLOW, STATE_MEDIUM, STATE_FAST, STATE_ON};

void setup(void); //Initierar mikrodatorn vid start.//
void fsm_reset(void); //Reset funktion
void fsm_update(void); //Uppdateringsfunktion som uppdaterar state.
void fsm_set_output(const uint16_t blink_speed_ms); //Sätter output efter aktuellt state (blink_speed_ms = Lysdiodernas blinkhastighet vid blinkning.)

#endif /* HEADER_H_ */
