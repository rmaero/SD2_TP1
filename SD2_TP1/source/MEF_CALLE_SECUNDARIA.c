/*
 * MEF_CALLE_SECUNDARIA.c
 *
 *  Created on: 4 abr. 2023
 *      Author: Rodrigo Maero
 */

#include "SD2_board.h"
#include "key.h"

#include "MEF_CALLE_SECUNDARIA.h"
#include "MEF_MAIN.h"

uint8_t* sensorAddr;
uint8_t* carsCrossedAddr;
uint32_t timer_1;
uint32_t timer_2;

static mef_calle_secundaria_enum mefCalleSecundaria;

bool MEF_CALLE_SECUNDARIA(){
	bool ret=false;

	switch(mefCalleSecundaria){
	case SECUNDARIO_INIT:
		timer_1=TIMER_5_SEG;
		timer_2=TIMER_200_MS;
		mefCalleSecundaria=RUTA_INTERMITENTE;
		break;
	case RUTA_INTERMITENTE:
		board_setLed(LRR, OFF);											//LRR OFF
		board_setLed(LRS, ON);											//LRS ON
		board_setLed(LVS, OFF);											//LVS OFF
		if(timer_2==0){
			timer_2=TIMER_200_MS;
			board_setLed(LVR, TOGGLE);									//LVR TOGGLE
		}
		if(timer_1==0){
			mefCalleSecundaria=CALLE_SECUNDARIA;
		}

		break;
	case CALLE_SECUNDARIA:
		board_setLed(LRR, ON);											//LRR ON
		board_setLed(LVR, OFF);											//LVR OFF
		board_setLed(LRS, OFF);											//LRS OFF
		board_setLed(LVS, ON);											//LVS ON
		if(key_getPressEv(BOARD_SW_ID_3)){
			*sensorAddr--; 												//resto 1 unidad al valor guardado en la direccion "sensorAddr"
			*carsCrossedAddr++;											//sumo 1 unidad al valor guardado en la direccion "carsCrossedAddr"
		}
		if(*sensorAddr==0){
			timer_1=TIMER_5_SEG;
			timer_2=TIMER_200_MS;
			mefCalleSecundaria=SECUNDARIO_INTERMITENTE;
		}
		break;
	case SECUNDARIO_INTERMITENTE:
		board_setLed(LRR, ON);											//LRR ON
		board_setLed(LVR, OFF);											//LVR OFF
		board_setLed(LRS, OFF);											//LRS OFF
		if(key_getPressEv(BOARD_SW_ID_3)){
					*sensorAddr--; 										//resto 1 unidad al valor guardado en la direccion "sensorAddr"
					*carsCrossedAddr++;									//sumo 1 unidad al valor guardado en la direccion "carsCrossedAddr"
				}
		if(timer_2==0){
			timer_2=TIMER_200_MS;
			board_setLed(LVS, TOGGLE);									//LVS TOGGLE
		}
		if(timer_1==0){
			ret=true;
		}
		break;
	}
	return ret;
}

//Debo pasarle la direcc de memoria de sensors y carsCrossed asi la submef puede manipular estos datos
void MEF_CALLE_SECUNDARIA_INIT(uint8_t* s, uint8_t* c){
	sensorAddr = s;
	carsCrossedAddr = c;
	mefCalleSecundaria=SECUNDARIO_INIT;
}

void MEF_CALLE_SECUNDARIA_periodicTask1ms(){
	if(timer_1)
		timer_1--;
	if(timer_2)
		timer_2--;
}
