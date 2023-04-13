/*
 * MEF_CALLE_SECUNDARIA.h
 *
 *  Created on: 4 abr. 2023
 *      Author: Rodrigo
 */

#ifndef MEF_CALLE_SECUNDARIA_H_
#define MEF_CALLE_SECUNDARIA_H_

#include <stdbool.h>

//---------ESTADOS DE LA SECUENCIA PRINCIPAL---------------
typedef enum {
	SECUNDARIO_INIT=0,
	RUTA_INTERMITENTE,
	SECUNDARIA,
	SECUNDARIO_INTERMITENTE
} mefCalleSecundariaEnum;

//DEVUELVE FALSE SI DEBE MANTENERSE EN ESTA SUBMEF,
//TRUE SI TERMINO Y TIENE QUE VOLVER A LA MEF MAIN
bool MefCalleSecundaria();

//INIT PARA ASEGURAR QUE EMPIECE EN EL COMIENZO
//DE SU SECUENCIA
void MefCalleSecundaria_init();

void MefCalleSecundaria_periodicTask1ms();

#endif /* MEF_CALLE_SECUNDARIA_H_ */

