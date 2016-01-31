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


inline double distancia(double *s, double *t, int numCols){
	double d = 0;
	for (int i = 0; i <numCols ; ++i) {
		d += (s[i]-t[i])*(s[i]-t[i]);
	}
	return sqrt(d);
}


inline  double distancia(vector< double> *s, vector< double> *t, int numCols){
	 double d = 0;

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

inline  double min( double f1,  double f2,  double f3){
	if(f2<f1)f1=f2;
	if(f3<f1)f1=f3;
	return f1;
}

inline  double minMod( double** DTW, int i, int j, int w){

	long double min = DTW[i-1][j-1];
	if(abs(i-1-j)<=w && DTW[i-1][j]<min) min = DTW[i-1][j];
	if(abs(i - (j-1))<=w && DTW[i][j-1]<min)min = DTW[i][j-1];
	return min;
}

//# using float pointer
double simpleDTW( double ** s, const int size_s, double **t, const int size_t, int numCols);

//# using vector
double simpleDTW(vector<vector<double> > *s, vector<vector<double> > *t, int numCols =0);
double windowedDTW(vector<vector<double> > *s, vector<vector<double> > *t, int w);

#endif /* DTW_H_ */
