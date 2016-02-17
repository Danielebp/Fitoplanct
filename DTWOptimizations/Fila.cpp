/*
 * Fila.cpp
 *
 *  Created on: Feb 16, 2016
 *      Author: labproj
 */

#include "Fila.h"

Fila::Fila() {
	// TODO Auto-generated constructor stub

}

Fila::~Fila() {
	free(Buffer);
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond_prod);
	pthread_cond_destroy(&cond_cons);
}

