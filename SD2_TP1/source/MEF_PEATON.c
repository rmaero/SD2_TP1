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

//punteros a sensor y carsCrossed
uint8_t* sensor_addr;
uint8_t* carsCrossed_addr;

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
		board_setLed(BOARD_LED_ID_ROJO, BOARD_LED_MSG_OFF);				//LRR OFF
		board_setLed(BOARD_LED_ID_VERDE_SECUNDARIO, BOARD_LED_MSG_OFF);	//LVS OFF
		board_setLed(BOARD_LED_ID_ROJO_SECUNDARIO, BOARD_LED_MSG_ON);	//LRS ON
		if(timer2_==0){
			timer2_=TIMER_200_MS;
			board_setLed(BOARD_LED_ID_VERDE, BOARD_LED_MSG_TOGGLE);		//LVR TOGGLE
		}
		if(timer1_==0){
			timer1_=TIMER_1_MIN;
			mefPeaton=PEATON_SECUNDARIO;
		}
		break;
	case PEATON_SECUNDARIO:
		board_setLed(BOARD_LED_ID_ROJO, BOARD_LED_MSG_ON);				//LRR ON
		board_setLed(BOARD_LED_ID_VERDE, BOARD_LED_MSG_OFF);			//LVR OFF
		board_setLed(BOARD_LED_ID_ROJO_SECUNDARIO, BOARD_LED_MSG_OFF);	//LRS OFF
		board_setLed(BOARD_LED_ID_VERDE_SECUNDARIO, BOARD_LED_MSG_ON);	//LVS ON
		if(key_getPressEv(BOARD_SW_ID_3)){
			*carsCrossed_addr++;
			if(*sensor_addr)
				*sensor_addr--;
		}
		if(timer1_==0){
			timer1_=TIMER_10_SEG;
			timer2_=TIMER_200_MS;
			mefPeaton=PEATON_INTERMITENTE;
		}
		break;
	case PEATON_INTERMITENTE:
		board_setLed(BOARD_LED_ID_VERDE, BOARD_LED_MSG_OFF);			//LVR OFF
		board_setLed(BOARD_LED_ID_ROJO_SECUNDARIO, BOARD_LED_MSG_OFF);	//LRS OFF
		board_setLed(BOARD_LED_ID_VERDE_SECUNDARIO, BOARD_LED_MSG_ON);	//LVS ON
		if(key_getPressEv(BOARD_SW_ID_3)){
			*carsCrossed_addr++;
			if(*sensor_addr)
				*sensor_addr--;
		}
		if(timer2_==0){
			timer2_=TIMER_200_MS;
			board_setLed(BOARD_LED_ID_ROJO, BOARD_LED_MSG_TOGGLE);		//LRR TOGGLE
		}
		if(timer1_==0){
			ret=true;
		}

		break;
	}
	return ret;
}

void MEF_PEATON_INIT(uint8_t* s, uint8_t* c){
	sensor_addr=s;
	carsCrossed_addr=c;
	mefPeaton = PEATON_INIT;
}
void MEF_PEATON_periodicTask1ms(){
	if(timer1_)
		timer1_--;
	if(timer2_)
		timer2_--;
}

