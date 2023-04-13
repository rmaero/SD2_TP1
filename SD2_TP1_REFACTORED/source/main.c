/*AUTHOR: RODRIGO MAERO - 2023
 *
 * DSI FCEIA UNR - Sistemas Digitales 2
 *
 **/

/*==================[inclusions]=============================================*/
// Project Included Files
#include "SD2_board.h"
#include "key.h"

#include "MEF_SUPER.h"
/*==================[macros and definitions]=================================*/


/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/


/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
int main(void)
{
	// Se inicializan funciones de la placa
	board_init();

	// Inicializa keyboard
	key_init();

	/* inicializa interrupción de systick cada 1 ms */
	SysTick_Config(SystemCoreClock / 1000U);

	while(1)
    {
    	MefSuper();
    }
}

void SysTick_Handler(void)
{
    key_periodicTask1ms();
    MefSuper_periodicTask1ms();
}

/*==================[end of file]============================================*/


