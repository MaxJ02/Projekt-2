/**************************************************************************************
* Projekt 2: Implementeringen av en tillståndsmaskin innehållande tre lysdioder samt 5 
*             knappar där lysdioderna kan anta 5 olika tillstånd.
*             - STATE_OFF : Alla lysdioder hålls släckta.
*             - STATE_SLOW: Alla tre lysdioderna blinkar i en slinga var 500e ms.
*             - STATE_MEDIUM : Alla tre lysdioderna blinkar i en slinga var 250e ms.
*             - STATE_FAST: Alla tre lysdioderna blinkar i en slinga var 50e ms.
*             - STATE_ON  : Alla lysdioder hålls tända.
*
*             När någon av tryckknapparna blir nedtryckta skall ett avbrott
*             genereras, där tillståndsmaskinens tillstånd uppdateras, antingen
*             framåt eller bakåt 1-2 steg (eller släckning via reset), beroende
*             på vilken tryckknapp som trycktes ned. När detta sker så skall
*             lysdiodernas tillstånd förändras.
*****************************************************************************************/
/****************************************************************************************
* main.c: Vi anropar setup och sätter output via fsm_set_output. Vi returnerar ingenting.
*****************************************************************************************/



#include "header.h"

int main(void)
{
    setup();
	
	while (true)
	{
	 fsm_set_output(100);	
	}
	
	return 0;
}
