/*
 * MEF_PEATON.c
 *
 *  Created on: 4 abr. 2023
 *      Author: Rodrigo
 */

#include "SD2_board.h"
#include "key.h"

#include "MEF_PEATON.h"
#include "MEF_MAIN.h"

uint32_t timer1_;
uint32_t timer2_;

static mef_peaton_enum mefPeaton;

//devuelve FALSE si se debe mantener en esta submef, TRUE si debe volver a la mef main
bool MEF_PEATON (){
	bool ret=false;
	switch (mefPeaton){
	case PEATON_INIT:
		timer1_=TIMER_10_SEG;
		timer2_=TIMER_200_MS;
		//board_setLed(BOARD_LED_ID_VERDE, BOARD_LED_MSG_ON);				//LVR ON
		mefPeaton=PEATON_RUTA_INTERMITENTE;
		break;
	case PEATON_RUTA_INTERMITENTE:
		board_setLed(LRR, OFF);											//LRR OFF
		board_setLed(LVS, OFF);											//LVS OFF
		board_setLed(LRS, ON);											//LRS ON
		//TODO: AGREGAR AL DISENIO durante este estado tambien pueden aparecer autos y se deberian acumular en sensor
		if(key_getPressEv(BOARD_SW_ID_3)){
			MEF_MAIN_increaseSensor();
		}
		if(timer2_==0){
			timer2_=TIMER_200_MS;
			board_setLed(LVR, TOGGLE);									//LVR TOGGLE
		}
		if(timer1_==0){
			timer1_=TIMER_1_MIN;
			mefPeaton=PEATON_SECUNDARIO;
		}
		break;
	case PEATON_SECUNDARIO:
		board_setLed(LRR, ON);											//LRR ON
		board_setLed(LVR, OFF);											//LVR OFF
		board_setLed(LRS, OFF);											//LRS OFF
		board_setLed(LVS, ON);											//LVS ON
		if(key_getPressEv(BOARD_SW_ID_3)){								//si paso un auto contarlo
			MEF_MAIN_increaseCarsCrossed();
			if(MEF_MAIN_getSensor())									//y descontarlo de los autos esperando, si hubiese
				MEF_MAIN_decreaseSensor();
		}
		if(timer1_==0){
			timer1_=TIMER_10_SEG;
			timer2_=TIMER_200_MS;
			mefPeaton=PEATON_INTERMITENTE;
		}
		break;
	case PEATON_INTERMITENTE:
		board_setLed(LVR, OFF);											//LVR OFF
		board_setLed(LRS, OFF);											//LRS OFF
		board_setLed(LVS, ON);											//LVS ON
		if(key_getPressEv(BOARD_SW_ID_3)){								//si paso un auto contarlo
			MEF_MAIN_increaseCarsCrossed();
			if(MEF_MAIN_getSensor())
				MEF_MAIN_decreaseSensor();											//y descontarlo de los autos esperando, si hubiese
		}
		if(timer2_==0){
			timer2_=TIMER_200_MS;
			board_setLed(LRR, TOGGLE);									//LRR TOGGLE
		}
		if(timer1_==0){
			ret=true;
		}

		break;
	}
	return ret;
}

void MEF_PEATON_INIT(){
	mefPeaton = PEATON_INIT;
}
void MEF_PEATON_periodicTask1ms(){
	if(timer1_)
		timer1_--;
	if(timer2_)
		timer2_--;
}

