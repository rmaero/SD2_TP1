/*
 * MEF_CALLE_SECUNDARIA.h
 *
 *  Created on: 4 abr. 2023
 *      Author: Rodrigo
 */

#ifndef MEF_CALLE_SECUNDARIA_H_
#define MEF_CALLE_SECUNDARIA_H_
#endif /* MEF_CALLE_SECUNDARIA_H_ */

#include <stdbool.h>

typedef enum {
	SECUNDARIO_INIT=0,
	RUTA_INTERMITENTE,
	CALLE_SECUNDARIA,
	SECUNDARIO_INTERMITENTE
} mef_calle_secundaria_enum;

bool MEF_CALLE_SECUNDARIA();

void MEF_CALLE_SECUNDARIA_INIT(uint8_t* s, uint8_t* c);

void MEF_CALLE_SECUNDARIA_periodicTask1ms();

