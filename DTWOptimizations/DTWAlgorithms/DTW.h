/*
 * DTW.h
 *
 *  Created on: Jan 20, 2016
 *      Author: Daniele
 */

#ifndef DTW_H_
#define DTW_H_

#include "../Common.h"
#include <climits>
#include <cmath>

inline float distancia(vector<float> *s, vector<float> *t){
	float d = 0;

	for (unsigned int i = 0; i <(*s).size() ; ++i) {
		d += abs((*s)[i]-(*t)[i]);
	}
	return d;
}

inline float min(float f1, float f2, float f3){
	if(f2<f1)f1=f2;
	if(f3<f1)f1=f3;
	return f1;
}

inline float minMod(float** DTW, int i, int j, int w){

	float min = DTW[i-1][j-1];
	if(abs(i-1-j)<=w && DTW[i-1][j]<min) min = DTW[i-1][j];
	if(abs(i - (j-1))<=w && DTW[i][j-1]<min)min = DTW[i][j-1];
	return min;
}

float simpleDTW(vector<vector<float> > *s, vector<vector<float> > *t);

float windowedDTW(vector<vector<float> > *s, vector<vector<float> > *t, int w);

#endif /* DTW_H_ */
