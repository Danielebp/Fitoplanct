/*
 * Fila.h
 *
 *  Created on: Feb 16, 2016
 *      Author: labproj
 */

#ifndef FILA_H_
#define FILA_H_

#include <string>
#include <sstream>
#include <ctime>
#include <stdio.h>
#include <iomanip>
#include <pthread.h>
#include "Common.h"


//cria a estrutura de elem da fila
typedef struct {
   int s, t;
} q_elem;

class Fila {
private:
	q_elem* Buffer;
	int N;
	int count;
	int in;
	int out;
	pthread_mutex_t mutex;
	pthread_cond_t cond_prod;
	pthread_cond_t cond_cons;
public:
	Fila();

	Fila(int n){
		N = n;
		Buffer = (q_elem*)malloc(N*sizeof(q_elem));
		count=0;
		in=0;
		out=0;

		pthread_mutex_init(&mutex, NULL);
		pthread_cond_init (&cond_prod, NULL);
		pthread_cond_init (&cond_cons, NULL);
	}

	virtual ~Fila();

	void Insere (q_elem item) {
		pthread_mutex_lock(&mutex);
		while(count == N) {
			pthread_cond_wait(&cond_prod, &mutex);
		}
		Buffer[in] = item;
		in = (in + 1) % N;
		count++;
		pthread_cond_signal(&cond_cons);
		pthread_mutex_unlock(&mutex);
	}

	q_elem Retira (void) {
		q_elem item;
		pthread_mutex_lock(&mutex);
		while(count == 0) {
			pthread_cond_wait(&cond_cons, &mutex);
		}
		item = Buffer[out];
		//Buffer[out] = ;
		out = (out + 1) % N;
		count--;
		pthread_cond_signal(&cond_prod);
		pthread_mutex_unlock(&mutex);
		return item;
	}

};

#endif /* FILA_H_ */
