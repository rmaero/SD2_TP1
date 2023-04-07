/*
 * MEF_MAIN.c
 *
 *  Created on: 4 abr. 2023
 *      Author: Rodrigo Maero
 */
#include "SD2_board.h"
#include "key.h"


#include "MEF_MAIN.h"
#include "MEF_PEATON.h"
#include "MEF_CALLE_SECUNDARIA.h"


uint32_t timer1;
uint32_t timer2;
uint8_t sensor;
uint8_t carsCrossed;

static mef_main_enum mefMain = INIT;
static mef_main_enum back;
bool alreadyPressed;

void MEF_MAIN(){

	if(key_getPressEv(BOARD_SW_ID_1)&& !alreadyPressed){
		alreadyPressed=true;
		back=mefMain;
		mefMain=TO_MEF_PEATON;
		MEF_PEATON_INIT(&sensor,&carsCrossed);
	}
	switch(mefMain){
		case INIT:
			mefMain = RUTA;
			timer1=TIMER_2_MIN;
			timer2=0;
			sensor=0;
			carsCrossed=0;
			alreadyPressed=false;
			break;
		case RUTA:
            board_setLed(LRR, OFF);											//LRR OFF
            board_setLed(LVR ,ON);											//LVR ON
            board_setLed(LRS, ON);											//LRS ON
            board_setLed(LVS, OFF);											//LVS OFF
            if(key_getPressEv(BOARD_SW_ID_3))								//SI LLEGA UN AUTO A LA CALLE SECUND. CONTARLA
            	sensor++;
            if(sensor>=3)
            	mefMain=TO_MEF_CALLE_SEC;
            	//TODO AGREGAR UN break; ACA?? PARA QUE SALGA DEL SWITCH Y VAYA DIRECTAMENTE A LA SUBMEF

            if(timer1==0){													//PASO AL PROX ESTADO
            	mefMain=INTERMITENTE1;
            	timer1=TIMER_5_SEG;
            	timer2=TIMER_200_MS;
            }
			break;
		case INTERMITENTE1:
			board_setLed(LRR, OFF);											//LRR OFF
			board_setLed(LRS, ON);											//LRS ON
			board_setLed(LVS, OFF);											//LVS OFF

			if(key_getPressEv(BOARD_SW_ID_3)){ 								//SI LLEGA UN AUTO A LA CALLE SECUND. CONTARLA
				sensor++;
			    if(sensor>=3){
			    	mefMain = TO_MEF_CALLE_SEC;
			    	MEF_CALLE_SECUNDARIA_INIT(&sensor, &carsCrossed); //le paso la direcc de memoria a la submef para que pueda manipular los datos

			    	//TODO AGREGAR UN break; ACA?? PARA QUE SALGA DEL SWITCH Y VAYA DIRECTAMENTE A LA SUBMEF
			    }
			}

			if(timer2==0){
				timer2=TIMER_200_MS;
				board_setLed(LVR, TOGGLE);									//LVR TOGGLE
			}
            if(timer1==0){													//PASO AL PROX ESTADO
            	mefMain=SECUNDARIO;
            	timer1=TIMER_30_SEG;
            }
			break;
		case SECUNDARIO:
			board_setLed(LRR, ON);											//LRR ON
			board_setLed(LVR, OFF);											//LVR OFF
			board_setLed(LRS, OFF);											//LRS OFF
			board_setLed(LVS, ON);											//LVS ON
			if(key_getPressEv(BOARD_SW_ID_3)){ 								//SI UN AUTO CRUZA LA CALLE SECUND.
				carsCrossed++;												//CONTARLO COMO CRUZADO
				sensor--;													//DESCONTARLO DE SENSOR
			}
            if(timer1==0){													//PASO AL PROX ESTADO
            	mefMain=INTERMITENTE2;
            	timer1=TIMER_5_SEG;
            	timer2=TIMER_200_MS;
            }
			break;
		case INTERMITENTE2:
			board_setLed(LRR,ON);											//LRR ON
			board_setLed(LRS, OFF);											//LRS OFF
			board_setLed(LVR, OFF);											//LVR OFF
			if(key_getPressEv(BOARD_SW_ID_3)){ 								//SI UN AUTO CRUZA LA CALLE SECUND.
				carsCrossed++;												//CONTARLO COMO CRUZADO
				sensor--;													//DESCONTARLO DE SENSOR
			}
			if(timer2==0){
				timer2=TIMER_200_MS;
				board_setLed(LVS, TOGGLE); 									//LVS TOGGLE
			}
			if(timer1==0){													//PASO AL PROX ESTADO
				mefMain=RUTA;
				timer1=TIMER_2_MIN;
				alreadyPressed=false;										//devuelvo para que puedan volver a presionar SW1
			}
			break;
		case TO_MEF_PEATON:
			if(MEF_PEATON())
				mefMain=back;												//termino la mef peaton, devuelvo a mefMain con historia
			break;
		case TO_MEF_CALLE_SEC:
			if(MEF_CALLE_SECUNDARIA()){
				mefMain=RUTA;												//termino la mef calle secundaria, devuelvo al mefMain con reset
				//MEF_MAIN_RESET();
				timer1=TIMER_2_MIN;
				timer2=0;
				alreadyPressed=false;
			}
			break;
	}
}

/*
void MEF_MAIN_RESET(){
	mefMain = RUTA;

}

*/
void MEF_MAIN_periodicTask1ms(){
	if(timer1!=0 && (mefMain!=TO_MEF_PEATON)){ 								//freno timers si estoy en la submef peaton
		timer1--;
	}
	if(timer2!=0 && (mefMain!=TO_MEF_PEATON)){
		timer2--;
	}
	if(mefMain==TO_MEF_PEATON)
		MEF_PEATON_periodicTask1ms();
	if(mefMain==TO_MEF_CALLE_SEC)
		MEF_CALLE_SECUNDARIA_periodicTask1ms();
}
