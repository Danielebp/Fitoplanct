/*
 * DTW.cpp
 *
 *  Created on: Jan 20, 2016
 *      Author: Daniele
 */

#include "DTW.h"

//# using float pointer

double simpleDTW( double ** s, const int size_s, double **t, const int size_t, int numCols){
	long double custo = 0;
	long double result = 0;


	double DTW[size_s+1][size_t+1];

	for(int i =1; i<= size_s; ++i){
		DTW[i][0]= INT_MAX;
	}
	for(int i =1; i<= size_t; ++i){
		DTW[0][i]= INT_MAX;
	}

	DTW[0][0]=0;

	for (int i = 1; i <= size_s; ++i) {
		for (int j = 1; j <= size_t; ++j) {
			custo = distancia(s[i-1],t[j-1], numCols);
			DTW[i][j] = custo + min(DTW[i-1][j], DTW[i][j-1], DTW[i-1][j-1]);
		}
	}

	result = DTW[size_s][size_t];

	return result;
}



//# using vector

double simpleDTW(vector<vector<double> > *s, vector<vector<double> > *t, int numCols){
	double custo = 0;
	double result = 0;

	const int size_s = (*s).size();
	const int size_t = (*t).size();


	double DTW[size_s+1][size_t+1];

	for(int i =1; i<= size_s; ++i){
		DTW[i][0]= INT_MAX;
	}
	for(int i =1; i<= size_t; ++i){
		DTW[0][i]= INT_MAX;
	}

	DTW[0][0]=0;

	for (int i = 1; i <= size_s; ++i) {
		for (int j = 1; j <= size_t; ++j) {
			custo = distancia(&((*s)[i-1]),&((*t)[j-1]), numCols);
			//custo = distancias[i-1][j-1];
			//cout<<custo<<"\t";
			DTW[i][j] = custo + min(DTW[i-1][j], DTW[i][j-1], DTW[i-1][j-1]);
		}
		//cout<<endl;
	}

	result = DTW[size_s][size_t];

	return result;
}

double windowedDTW(vector<vector<double> > *s, vector<vector<double> > *t, int w){
	double custo = 0;
	double result = 0;

	const int size_s = (*s).size();
	const int size_t = (*t).size();

	if(abs(size_s-size_t)>w){
		cout<<"Window size should be at least |m-n|"<<endl;
		return -1;
	}

	//float DTW[size_s+1][size_t+1];
	cin>>custo;
	double **DTW = (double**)malloc(sizeof(double*)*(size_s+1));
	for(int i =1; i<= size_s; ++i){
		DTW[i] = (double*)malloc(sizeof(double)*(size_t+1));
		DTW[i][0]= INT_MAX;
	}
	for(int i =1; i<= size_t; ++i){
		DTW[0][i]= INT_MAX;
	}

	DTW[0][0]=0;

	for (int i = 1; i <= size_s; ++i) {
		for (int j = 1; j <= size_t; ++j) {
			if(abs(i-j)<=w){
				custo = distancia(&((*s)[i-1]),&((*t)[j-1]),0);
				DTW[i][j] = custo + minMod(DTW, i, j, w);
			}
		}
	}
	result = DTW[size_s][size_t];
	for(int i =1; i<= size_s; ++i){
		free(DTW[i]);
	}
	free(DTW);

	return result;
}
