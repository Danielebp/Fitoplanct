/*
 * DTW.cpp
 *
 *  Created on: Jan 20, 2016
 *      Author: Daniele
 */

#include "DTW.h"

float simpleDTW(vector<vector<float> > *s, vector<vector<float> > *t){
	float custo = 0;

	const int size_s = (*s).size();
	const int size_t = (*t).size();

	int DTW[size_s+1][size_t+1];

	for(int i =1; i<= size_s; ++i){
		DTW[i][0]= INT_MAX;
	}
	for(int i =1; i<= size_t; ++i){
		DTW[0][i]= INT_MAX;
	}

	DTW[0][0]=0;

	for (int i = 0; i < size_s; ++i) {
		for (int j = 0; j < size_t; ++j) {
			custo = distance(&(s[i]),&(t[i]));
			DTW[i][j] = custo + min(DTW[i-1][j], DTW[i][j-1], DTW[i-1][j-1]);
		}
	}


	return DTW[size_s][size_t];
	//return 0;
}

