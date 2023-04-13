/*
 * MEF_SUPER.c
 *
 *  Created on: 12 abr. 2023
 *      Author: rmaero
 */



#include "MEF_SUPER.h"

#include "key.h"
#include "SD2_board.h"

#include "MEF_MAIN.h"
#include "MEF_CALLE_SECUNDARIA.h"
#include "MEF_PEATON.h"

static MefSuperEnum mefSuper = SUPER_INIT;

/*declaradas como unsigned int de 8 bit, si tengo mas de 255 autos
*esperando para cruzar la calle hay un problema mas grave*/
static uint8_t carsWaiting;

//este si podria ser de 32 bit porque a lo largo del dia se acumulan muchos
static uint8_t carsCrossed;

// SUPER MEF, DEFINE A QUE SUB MEF LLAMA
void MefSuper(){
	MefMainReturn ret;
	switch(mefSuper){
		case SUPER_INIT:
			mefSuper=MAIN;
			break;
		case MAIN:
			ret= MefMain();
			if (ret ==TO_PEATON){
				mefSuper=PEATON;
				MefPeaton_init();
			}else if(ret==TO_CALLE_SECUNDARIA){
				mefSuper=CALLE_SECUNDARIA;
				MefCalleSecundaria_init();
			}
			break;
		case PEATON:
			if(MefPeaton())
				mefSuper=MAIN;
			break;
		case CALLE_SECUNDARIA:
			if(MefCalleSecundaria()){
				mefSuper=MAIN;
				MefMain_reset();
			}
			break;
	}
}

//DEFINE A QUE SUB MEF LE DA EL TICK
void MefSuper_periodicTask1ms(){
	if(mefSuper==MAIN)
		MefMain_periodicTask1ms();
	else if(mefSuper==PEATON)
		MefPeaton_periodicTask1ms();
	else if(mefSuper==CALLE_SECUNDARIA)
		MefCalleSecundaria_periodicTask1ms();
}

uint8_t MefSuper_getCarsWaiting(){
	return carsWaiting;
}

void MefSuper_increaseCarsWaiting(){
	carsWaiting++;
}

void MefSuper_decreaseCarsWaiting(){
	if(carsWaiting) //no me gusta pero es para asegurar que no pase a valores negativos
		carsWaiting--;
}

uint8_t MefSuper_getCarsCrossed(){
	return carsCrossed;
}
void MefSuper_increaseCarsCrossed(){
	carsCrossed++;
}
