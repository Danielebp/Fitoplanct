/*
 * DTW.cpp
 *
 *  Created on: Jan 20, 2016
 *      Author: Daniele
 */

#include "DTW.h"

float simpleDTW(vector<vector<float> > s, vector<vector<float> > t){
	float custo = 0;
	float result = 0;

	const int size_s = s.size();
	const int size_t = t.size();


	float DTW[size_s+1][size_t+1];

	for(int i =1; i<= size_s; ++i){
		DTW[i][0]= INT_MAX;
	}
	for(int i =1; i<= size_t; ++i){
		DTW[0][i]= INT_MAX;
	}

	DTW[0][0]=0;

	for (int i = 1; i <= size_s; ++i) {
		for (int j = 1; j <= size_t; ++j) {
			custo = distancia(s[i-1],t[j-1]);
			DTW[i][j] = custo + min(DTW[i-1][j], DTW[i][j-1], DTW[i-1][j-1]);
		}
	}

	result = DTW[size_s][size_t];

	return result;
}

