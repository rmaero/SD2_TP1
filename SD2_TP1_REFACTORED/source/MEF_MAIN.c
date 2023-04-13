/*
 * MEF_MAIN.c
 *
 *  Created on: 4 abr. 2023
 *      Author: Rodrigo Maero
 */
#include "SD2_board.h"
#include "key.h"


#include "MEF_MAIN.h"
#include "MEF_SUPER.h"


uint32_t timerSemaforo;
uint32_t timerToggle;

static MefMainEnum mefMain = INIT;

//flag para determinar si ya se presiono el boton del peaton
//dentro del ciclo normal, una vez que se reinicia el ciclo
//limpio la bandera
bool alreadyPressed;

MefMainReturn MefMain(){
	MefMainReturn r = NO_RETURN;
	//si se presiona el boton y no fue presionado ya en este ciclo, transicionar a MEF PEATON
	if(key_getPressEv(BOARD_SW_ID_1)&& !alreadyPressed){
		alreadyPressed=true;
		r = TO_PEATON;
	}
	switch(mefMain){
		case INIT:
			mefMain = RUTA;
			timerSemaforo=TIMER_2_MIN;
			timerToggle=0;
			alreadyPressed=false;
			break;
		case RUTA:
            board_setLed(LRR, OFF);											//LRR OFF
            board_setLed(LVR ,ON);											//LVR ON
            board_setLed(LRS, ON);											//LRS ON
            board_setLed(LVS, OFF);											//LVS OFF
            if(key_getPressEv(BOARD_SW_ID_3))								//SI LLEGA UN AUTO A LA CALLE SECUND. CONTARLO
            	MefSuper_increaseCarsWaiting();
            if(MefSuper_getCarsWaiting()>=3){
            	r=TO_CALLE_SECUNDARIA;
            }
            if(timerSemaforo==0){											//PASO AL PROX ESTADO
            	mefMain=INTERMITENTE1;
            	timerSemaforo=TIMER_5_SEG;
            	timerToggle=TIMER_200_MS;
            }
			break;
		case INTERMITENTE1:
			board_setLed(LRR, OFF);											//LRR OFF
			board_setLed(LRS, ON);											//LRS ON
			board_setLed(LVS, OFF);											//LVS OFF

			if(key_getPressEv(BOARD_SW_ID_3)){ 								//SI LLEGA UN AUTO A LA CALLE SECUND. CONTARLA
				MefSuper_increaseCarsWaiting();
			    if(MefSuper_getCarsWaiting()>=3){
			    	r = TO_CALLE_SECUNDARIA;
			    }
			}

			if(timerToggle==0){
				timerToggle=TIMER_200_MS;
				board_setLed(LVR, TOGGLE);									//LVR TOGGLE
			}
            if(timerSemaforo==0){													//PASO AL PROX ESTADO
            	mefMain=SECUNDARIO;
            	timerSemaforo=TIMER_30_SEG;
            }
			break;
		case SECUNDARIO:
			board_setLed(LRR, ON);											//LRR ON
			board_setLed(LVR, OFF);											//LVR OFF
			board_setLed(LRS, OFF);											//LRS OFF
			board_setLed(LVS, ON);											//LVS ON
			if(key_getPressEv(BOARD_SW_ID_3)){ 								//SI UN AUTO CRUZA LA CALLE SECUND.
				MefSuper_increaseCarsCrossed();								//CONTARLO COMO CRUZADO
				MefSuper_decreaseCarsWaiting();								//DESCONTARLO DE SENSOR
			}
            if(timerSemaforo==0){											//PASO AL PROX ESTADO
            	mefMain=INTERMITENTE2;
            	timerSemaforo=TIMER_5_SEG;
            	timerToggle=TIMER_200_MS;
            }
			break;
		case INTERMITENTE2:
			board_setLed(LRR,ON);											//LRR ON
			board_setLed(LRS, OFF);											//LRS OFF
			board_setLed(LVR, OFF);											//LVR OFF
			if(key_getPressEv(BOARD_SW_ID_3)){ 								//SI UN AUTO CRUZA LA CALLE SECUND.
				MefSuper_increaseCarsCrossed();
				MefSuper_decreaseCarsWaiting();
			}
			if(timerToggle==0){
				timerToggle=TIMER_200_MS;
				board_setLed(LVS, TOGGLE); 									//LVS TOGGLE
			}
			if(timerSemaforo==0){											//VUELVO AL INICIO DEL CICLO
				mefMain=RUTA;
				timerSemaforo=TIMER_2_MIN;
				alreadyPressed=false;										//LIBERO FLAG PARA QUE VUELVAN A PRESIONAR SW1
			}
			break;
	}
	return r;
}


void MefMain_reset(){
	mefMain=INIT;
}
void MefMain_periodicTask1ms(){
	if(timerSemaforo)
		timerSemaforo--;

	if(timerToggle)
		timerToggle--;
}


