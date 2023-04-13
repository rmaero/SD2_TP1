/*
 * MEF_MAIN.h
 *
 *  Created on: 4 abr. 2023
 *      Author: Rodrigo
 */

#ifndef MEF_MAIN_H_
#define MEF_MAIN_H_
//---------ESTADOS DE LA SECUENCIA PRINCIPAL---------------
	typedef enum {
		INIT=0,
		RUTA,
		INTERMITENTE1,
		SECUNDARIO,
		INTERMITENTE2,
	} MefMainEnum;

/*----------POSIBLES DEVOLUCIONES DE ESTA SUBMEF PARA QUE
------------LA SUPER MEF DEFINA SI HAY TRANSICION--------*/

	typedef enum {
		NO_RETURN,
		TO_PEATON,
		TO_CALLE_SECUNDARIA
	}MefMainReturn;

//-----------------FUNCIONES---------------------------------
//LLAMADA A LA MEF
	MefMainReturn MefMain();
//RESET PARA ARRANCAR DE CERO DESPUES DE CALLE SECUNDARIA
	void MefMain_reset();
//LLAMADA AL TICK
	void MefMain_periodicTask1ms();

#endif /* MEF_MAIN_H_ */
