/*
 * MEF_PEATON.h
 *
 *  Created on: 4 abr. 2023
 *      Author: Rodrigo
 */

#ifndef MEF_PEATON_H_
#define MEF_PEATON_H_


#include <stdbool.h>
//---------ESTADOS DE LA SECUENCIA PRINCIPAL---------------
typedef enum {
	PEATON_INIT=0,
	PEATON_RUTA_INTERMITENTE,
	PEATON_SECUNDARIO,
	PEATON_INTERMITENTE
} mefPeatonEnum;

//DEVUELVE FALSE SI SE DEBE MANTENER EN ESTA SUBMEF
//TRUE SI DEBE TRANSICIONAR, VOLVIENDO A LA MEF MAIN
bool MefPeaton ();

//INIT PARA ASEGURAR QUE EMPIECE EN EL COMIENZO
//DE SU SECUENCIA
void MefPeaton_init();

void MefPeaton_periodicTask1ms();


#endif /* MEF_PEATON_H_ */
