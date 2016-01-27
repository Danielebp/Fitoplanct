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

inline long double distancia(vector<long double> *s, vector<long double> *t, int numCols){
	long double d = 0;

	if(numCols==0)numCols=(*s).size();

	for (int i = 0; i <numCols ; ++i) {
		d += ((*s)[i]-(*t)[i])*((*s)[i]-(*t)[i]);
	}
	return sqrt(d);
	/*for (unsigned int i = 0; i <numCols ; ++i) {
			d += abs((*s)[i]-(*t)[i]);
	}
	return d;*/
}

inline long double min(long double f1, long double f2, long double f3){
	if(f2<f1)f1=f2;
	if(f3<f1)f1=f3;
	return f1;
}

inline long double minMod(long double** DTW, int i, int j, int w){

	long double min = DTW[i-1][j-1];
	if(abs(i-1-j)<=w && DTW[i-1][j]<min) min = DTW[i-1][j];
	if(abs(i - (j-1))<=w && DTW[i][j-1]<min)min = DTW[i][j-1];
	return min;
}

long double simpleDTW(vector<vector<long double> > *s, vector<vector<long double> > *t, int numCols =0);

long double windowedDTW(vector<vector<long double> > *s, vector<vector<long double> > *t, int w);

#endif /* DTW_H_ */
