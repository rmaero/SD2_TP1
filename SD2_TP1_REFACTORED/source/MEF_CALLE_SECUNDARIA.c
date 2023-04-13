/*
 * MEF_CALLE_SECUNDARIA.c
 *
 *  Created on: 4 abr. 2023
 *      Author: Rodrigo Maero
 */

#include "SD2_board.h"
#include "key.h"

#include "MEF_CALLE_SECUNDARIA.h"
#include "MEF_SUPER.h"

uint32_t timerSemaforo_CalleSecundaria;
uint32_t timerToggle_CalleSecundaria;

static mefCalleSecundariaEnum mefCalleSecundaria=SECUNDARIO_INIT;

bool MefCalleSecundaria(){
	bool ret=false;

	switch(mefCalleSecundaria){
		case SECUNDARIO_INIT:
			timerSemaforo_CalleSecundaria=TIMER_5_SEG;
			timerToggle_CalleSecundaria=TIMER_200_MS;
			mefCalleSecundaria=RUTA_INTERMITENTE;
			break;
		case RUTA_INTERMITENTE:
			board_setLed(LRR, OFF);											//LRR OFF
			board_setLed(LRS, ON);											//LRS ON
			board_setLed(LVS, OFF);											//LVS OFF
			if(key_getPressEv(BOARD_SW_ID_3)){
				MefSuper_increaseCarsWaiting();
			}
			if(timerToggle_CalleSecundaria==0){
				timerToggle_CalleSecundaria=TIMER_200_MS;
				board_setLed(LVR, TOGGLE);									//LVR TOGGLE
			}
			if(timerSemaforo_CalleSecundaria==0){							//LE DOY VERDE A LA CALLE SECUNDARIA
				mefCalleSecundaria=SECUNDARIA;
			}
			break;
		case SECUNDARIA:
			board_setLed(LRR, ON);											//LRR ON
			board_setLed(LVR, OFF);											//LVR OFF
			board_setLed(LRS, OFF);											//LRS OFF
			board_setLed(LVS, ON);											//LVS ON
			if(key_getPressEv(BOARD_SW_ID_3)){								//SI PASA UN AUTO,
				MefSuper_decreaseCarsWaiting(); 							//RESTARLO DE LOS AUTOS ESPERANDO
				//^ ESTE ES POTENCIALMENTE PELIGROSO, PODRIA DEJAR EN NEGATIVO?
				//NO DEBERIA PORQUE EL PROX IF LO CAPTURA ANTES DE PASAR A NEGATIVO

				MefSuper_increaseCarsCrossed();								//SUMARLO A LOS AUTOS QUE CRUZAN
			}
			if(MefSuper_getCarsWaiting()==0){
				timerSemaforo_CalleSecundaria=TIMER_5_SEG;
				timerToggle_CalleSecundaria=TIMER_200_MS;
				mefCalleSecundaria=SECUNDARIO_INTERMITENTE;
			}
			break;
		case SECUNDARIO_INTERMITENTE:
			board_setLed(LRR, ON);											//LRR ON
			board_setLed(LVR, OFF);											//LVR OFF
			board_setLed(LRS, OFF);											//LRS OFF
			if(key_getPressEv(BOARD_SW_ID_3)){								//SI PASA UN AUTO,
				MefSuper_increaseCarsCrossed();								//SUMARLO A LOS AUTOS QUE CRUZAN
			}
			if(timerToggle_CalleSecundaria==0){
				timerToggle_CalleSecundaria=TIMER_200_MS;
				board_setLed(LVS, TOGGLE);									//LVS TOGGLE
			}
			if(timerSemaforo_CalleSecundaria==0){							//SI TERMINA EL CICLO, DAR TRANSICION A LA SUPERMEF
				ret=true;
			}
			break;
		}
	return ret;
}

void MefCalleSecundaria_init(){
	mefCalleSecundaria=SECUNDARIO_INIT;
}

void MefCalleSecundaria_periodicTask1ms(){
	if(timerSemaforo_CalleSecundaria)
		timerSemaforo_CalleSecundaria--;
	if(timerToggle_CalleSecundaria)
		timerToggle_CalleSecundaria--;
}
