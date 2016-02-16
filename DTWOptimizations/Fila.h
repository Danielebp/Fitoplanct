/*
 * Fila.h
 *
 *  Created on: Feb 16, 2016
 *      Author: labproj
 */

#ifndef FILA_H_
#define FILA_H_

//cria a estrutura de elem da fila
typedef struct {
   int s, d;
} q_elem;

class Fila {
private:
	q_elem* Buffer;
	const int N;
	int count;
	int in;
	int out;
public:
	Fila();

	Fila(int n){
		N = n;
		Buffer = malloc(N*sizeof*q_elem);
	}

	virtual ~Fila();

	void Insere (int item) {
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

	int Retira (void) {
		int item;
		pthread_mutex_lock(&mutex);
		while(count == 0) {
			pthread_cond_wait(&cond_cons, &mutex);
		}
		item = Buffer[out];
		Buffer[out] = 0;
		out = (out + 1) % N;
		count--;
		pthread_cond_signal(&cond_prod);
		pthread_mutex_unlock(&mutex);
		return item;
	}

};

#endif /* FILA_H_ */
