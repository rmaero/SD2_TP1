/*
 * MEF_SUPER.h
 *
 *  Created on: 12 abr. 2023
 *      Author: rmaero
 */

#ifndef MEF_SUPER_H_
#define MEF_SUPER_H_
#include "stdint.h"

//-----------------DEFINICIONES GLOBALES-------------------------
#define TIMER_2_MIN 	120000
#define TIMER_1_MIN		60000
#define TIMER_30_SEG	30000
#define TIMER_10_SEG	10000
#define TIMER_5_SEG 	5000
#define TIMER_200_MS 	200

#define LRR BOARD_LED_ID_ROJO
#define LVR BOARD_LED_ID_VERDE
#define LRS BOARD_LED_ID_ROJO_SECUNDARIO
#define LVS BOARD_LED_ID_VERDE_SECUNDARIO

#define ON 		BOARD_LED_MSG_ON
#define OFF 	BOARD_LED_MSG_OFF
#define TOGGLE 	BOARD_LED_MSG_TOGGLE

//------------------ESTADOS MEF SUPER--------------------------
typedef enum {
	SUPER_INIT,
	MAIN,
	PEATON,
	CALLE_SECUNDARIA
}MefSuperEnum;

//-----------------FUNCIONES---------------------------------
//LLAMADA A LA MEF
void MefSuper();
//LLAMADA AL TICK
void MefSuper_periodicTask1ms();

//DEVUELVE CANT DE AUTOS ESPERANDO EN CALLE SECUNDARIA
uint8_t MefSuper_getCarsWaiting();
//AUMENTA Y DISMINUYE AUTOS ESPERANDO EN CALLE SECUNDARIA
void MefSuper_increaseCarsWaiting();
void MefSuper_decreaseCarsWaiting();

//DEVUELVE CANT DE AUTOS QUE CRUZARON LA CALLE SECUNDARIA
uint8_t MefSuper_getCarsCrossed();
//AUMENTA CANT DE AUTOS QUE CRUZARON LA CALLE SECUNDARIA
void MefSuper_increaseCarsCrossed();

#endif /* MEF_SUPER_H_ */
