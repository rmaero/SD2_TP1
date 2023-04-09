/*
 * MEF_PEATON.h
 *
 *  Created on: 4 abr. 2023
 *      Author: Rodrigo
 */

#ifndef MEF_PEATON_H_
#define MEF_PEATON_H_
#endif /* MEF_PEATON_H_ */

#include <stdbool.h>

typedef enum {
	PEATON_INIT=0,
	PEATON_RUTA_INTERMITENTE,
	PEATON_SECUNDARIO,
	PEATON_INTERMITENTE
} mef_peaton_enum;

bool MEF_PEATON ();

void MEF_PEATON_INIT();

void MEF_PEATON_periodicTask1ms();
