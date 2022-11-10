#include "header.h"

/********************************************************************************
* fsm.c: Filen Innehåller funktionaliteten för implementering av tillståndsmaskinen för
*        styrning av de tre lysdioderna. Det används pekare vid passering av 
*        blinkhastigheten (blink_speed_ms) för att direkt kunna avbryta en blinkning ifall 
*        aktuellt tillstånd övergår från blinkande till annat tillstånd.
*        Detta istället för att den ska blinka klart innan den byter tillstånd.
*        Fördröjningstiden som refereras till nollställs när detta sker, vilket
*        resulterar i att kvarvarande fördröjningstid sätts till 0. 
********************************************************************************/





//Statiska funktioner
static void leds_blink(const volatile uint16_t* leds_blink);
static void delay_ms(const volatile uint16_t* delay_time_ms);



//statiska datamedlemmar
static enum state state = STATE_OFF;
static uint16_t speed_ms = 0;


//Återstället lysdioderna till startläget, alltså släckta.
void fsm_reset(void)
{
	state = STATE_OFF;
	LEDS_OFF;
	speed_ms = 0;
	return;
}


/**************************************************************************************************
Uppdaterar tillståndsmaskinen Uppdaterar tillståndsmaskinen efter nuvarande tillstånd samt
*              vilken knapp som trycks ned. För att avbryta eventuell
*              blinkning så nollställs lysdiodernas blinkhastighet temporärt
*              när det aktuella tillståndet går från blinkande till något annat tillstånd.
*              Tillståndsmaskinens utsignaler uppdateras innan funktionen avslutas.
*************************************************************************************************/

void fsm_update(void)
{
	switch (state)
	{
		case STATE_OFF:
		{
			if      (NEXT_BUTTON_PRESSED)  state = STATE_SLOW;
			else if (NEXT_BUTTONX2_PRESSED)  state = STATE_MEDIUM;
			else if (PREVIOUS_BUTTON_PRESSED) state = STATE_ON;
			else if (PREVIOUS_BUTTONX2_PRESSED) state = STATE_FAST;
			break;
		}
		case STATE_SLOW:
		{
			if      (NEXT_BUTTON_PRESSED)  state = STATE_MEDIUM;
			else if (NEXT_BUTTONX2_PRESSED)  state = STATE_FAST;
			else if (PREVIOUS_BUTTON) state = STATE_OFF;
			else if (PREVIOUS_BUTTONX2_PRESSED) state = STATE_ON;
			break;
		}
		case STATE_MEDIUM:
		{
			if      (NEXT_BUTTON_PRESSED)  state = STATE_FAST;
			else if (NEXT_BUTTONX2_PRESSED)  state = STATE_ON;
			else if (PREVIOUS_BUTTON) state = STATE_SLOW;
			else if (PREVIOUS_BUTTONX2_PRESSED) state = STATE_OFF;
			break;
		}
		case STATE_FAST:
		{
			if      (NEXT_BUTTON_PRESSED)  state = STATE_ON;
			else if (NEXT_BUTTONX2_PRESSED)  state = STATE_OFF;
			else if (PREVIOUS_BUTTON) state = STATE_MEDIUM;
			else if (PREVIOUS_BUTTONX2_PRESSED) state = STATE_SLOW;
			break;
		}
		case STATE_ON:
		{
			if      (NEXT_BUTTON_PRESSED)  state = STATE_OFF;
			else if (NEXT_BUTTONX2_PRESSED)  state = STATE_SLOW;
			else if (PREVIOUS_BUTTON) state = STATE_FAST;
			else if (PREVIOUS_BUTTONX2_PRESSED) state = STATE_MEDIUM;
			break;
		}
		
		default:
		{
			fsm_reset();
			break;
		}
	}
	return;
}


//  Uppdaterar tillståndsmaskinens utsignaler utefter aktuellt tillstånd.

void fsm_set_output(const uint16_t blink_speed_ms)
{
	if (state == STATE_OFF)
	{
		LEDS_OFF;
	}
	else if (state == STATE_SLOW)
	{
		speed_ms = 500;
		leds_blink(&speed_ms);
	}
	else if (state == STATE_MEDIUM)
	{
		speed_ms = 250;
		leds_blink(&speed_ms);
	}
	else if (state == STATE_FAST)
	{
		speed_ms = 50;
		leds_blink(&speed_ms);
	}
	else if (state == STATE_ON)
	{
		LEDS_ON;
	}
	
	else
	{
		fsm_reset();
	}
	return;
}


/********************************************************************************
* leds_blink: En funktion som gör att lysdioderna blinkar i en slinga med den angivna blinkhastigheten.
*             Blinkhastigheten refereras till via en pekare för att direkt kunna
*             uppdateras, tex för att avbrytas, vilket sker genom
*             att värdet på den passerade adressen nollställs.
*
*             - blink_speed_ms: En pekare till blinkhastigheten som mäts i enheten ms.
********************************************************************************/



static void leds_blink(const volatile uint16_t* blink_speed_ms)
{
	LEDS_OFF;
	LED1_ON;
	delay_ms(blink_speed_ms);

	LED1_OFF;
	LED2_ON;
	delay_ms(blink_speed_ms);

	LED2_OFF;
	LED3_ON;
	delay_ms(blink_speed_ms);

	LED3_OFF;
	return;
}

/********************************************************************************
* delay_ms: Skapar en fördröjning mätt i millisekunder. Fördröjningstiden
*           refereras till via en pekare för att direkt kunna uppdateras,
*           tex för att avbrytas.
*
*           - delay_time_ms: Pekare till fördröjningstiden mätt i ms.
********************************************************************************/

static void delay_ms(const volatile uint16_t* delay_time_ms)
{
	for (uint16_t i = 0; i < *delay_time_ms; ++i)
	{
		_delay_ms(1);
	}

	return;
}
