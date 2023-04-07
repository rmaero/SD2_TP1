/*
 * MEF_MAIN.h
 *
 *  Created on: 4 abr. 2023
 *      Author: Rodrigo
 */

#ifndef MEF_MAIN_H_
#define MEF_MAIN_H_

#endif /* MEF_MAIN_H_ */

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

void MEF_MAIN();

//void MEF_MAIN_RESET();

void MEF_MAIN_periodicTask1ms();

typedef enum {
	INIT=0,
	RUTA,
	INTERMITENTE1,
	SECUNDARIO,
	INTERMITENTE2,

	TO_MEF_PEATON,
	TO_MEF_CALLE_SEC
} mef_main_enum;


