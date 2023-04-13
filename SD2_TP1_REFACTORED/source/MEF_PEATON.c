/*
 * MEF_PEATON.c
 *
 *  Created on: 4 abr. 2023
 *      Author: Rodrigo
 */

#include "SD2_board.h"
#include "key.h"

#include "MEF_PEATON.h"
#include "MEF_SUPER.h"

uint32_t timerSemaforo_Peaton;
uint32_t timerToggle_Peaton;

static mefPeatonEnum mefPeaton=PEATON_INIT;


bool MefPeaton (){
	bool ret=false;
	switch (mefPeaton){
	case PEATON_INIT:
		timerSemaforo_Peaton=TIMER_10_SEG;
		timerToggle_Peaton=TIMER_200_MS;
		mefPeaton=PEATON_RUTA_INTERMITENTE;
		break;
	case PEATON_RUTA_INTERMITENTE:
		board_setLed(LRR, OFF);											//LRR OFF
		board_setLed(LVS, OFF);											//LVS OFF
		board_setLed(LRS, ON);											//LRS ON
		if(key_getPressEv(BOARD_SW_ID_3)){								//SI LLEGA UN AUTO A LA CALLE SECUND. DURANTE EL INTERMITENTE, CONTARLO
			MefSuper_increaseCarsWaiting();
		}
		if(timerToggle_Peaton==0){
			timerToggle_Peaton=TIMER_200_MS;
			board_setLed(LVR, TOGGLE);									//LVR TOGGLE
		}
		if(timerSemaforo_Peaton==0){									//CUANDO TERMINA EL TIEMPO INTERMITENTE, DARLE EL VERDE A CALLE SECUNDARIA
			timerSemaforo_Peaton=TIMER_1_MIN;
			mefPeaton=PEATON_SECUNDARIO;
		}
		break;
	case PEATON_SECUNDARIO:
		board_setLed(LRR, ON);											//LRR ON
		board_setLed(LVR, OFF);											//LVR OFF
		board_setLed(LRS, OFF);											//LRS OFF
		board_setLed(LVS, ON);											//LVS ON
		if(key_getPressEv(BOARD_SW_ID_3)){								//SI PASA UN AUTO, CONTARLO
			MefSuper_increaseCarsCrossed();
			if(MefSuper_getCarsWaiting())								//DESCONTARLO DE LOS AUTOS ESPERANDO, SI HUBIESE
				MefSuper_decreaseCarsWaiting();
		}
		if(timerSemaforo_Peaton==0){
			timerSemaforo_Peaton=TIMER_10_SEG;
			timerToggle_Peaton=TIMER_200_MS;
			mefPeaton=PEATON_INTERMITENTE;
		}
		break;
	case PEATON_INTERMITENTE:
		board_setLed(LVR, OFF);											//LVR OFF
		board_setLed(LRS, OFF);											//LRS OFF
		board_setLed(LVS, ON);											//LVS ON
		if(key_getPressEv(BOARD_SW_ID_3)){								//SI PASA UN AUTO, CONTARLO
			MefSuper_increaseCarsCrossed();
			if(MefSuper_getCarsWaiting())
				MefSuper_decreaseCarsWaiting();							//DESCONTARLO DE LOS AUTOS ESPERANDO, SI HUBIESE
		}
		if(timerToggle_Peaton==0){
			timerToggle_Peaton=TIMER_200_MS;
			board_setLed(LRR, TOGGLE);									//LRR TOGGLE
		}
		if(timerSemaforo_Peaton==0){									//TERMINA EL CILCO, TRANSICIONAR DE VUELTA A LA SUBMEF MAIN
			ret=true;
		}

		break;
	}
	return ret;
}

void MefPeaton_init(){
	mefPeaton = PEATON_INIT;
}
void MefPeaton_periodicTask1ms(){
	if(timerSemaforo_Peaton)
		timerSemaforo_Peaton--;
	if(timerToggle_Peaton)
		timerToggle_Peaton--;
}

