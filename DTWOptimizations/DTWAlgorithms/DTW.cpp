/*
 * DTW.cpp
 *
 *  Created on: Jan 20, 2016
 *      Author: Daniele
 */

#include "DTW.h"

float simpleDTW(vector<vector<float> > *s, vector<vector<float> > *t){
	float custo = 0;
	float result = 0;

	const int size_s = (*s).size();
	const int size_t = (*t).size();


	float DTW[size_s+1][size_t+1];

	for(int i =1; i<= size_s; ++i){
		DTW[i][0]= INT_MAX;
	}
	for(int i =1; i<= size_t; ++i){
		DTW[0][i]= INT_MAX;
	}

	DTW[0][0]=0;
	float distancias[size_s][size_t];

	for (int i = 0; i < size_s; ++i) {
		for (int j = 0; j < size_t; ++j) {
			distancias[i][j]=0;
			for(int k = 0; k< 2; k++){
				distancias[i][j] += abs((*s)[i][k] - (*t)[j][k]);
			}
			//cout<<distancias[i][j]<<"\t";
		}
		//cout<<endl;
	}
	//cout<<endl<<endl;


	for (int i = 1; i <= size_s; ++i) {
		for (int j = 1; j <= size_t; ++j) {
			//custo = distancia(&((*s)[i-1]),&((*t)[j-1]));
			custo = distancias[i-1][j-1];
			DTW[i][j] = custo + min(DTW[i-1][j], DTW[i][j-1], DTW[i-1][j-1]);
		}
	}

	result = DTW[size_s][size_t];

	return result;
}

float windowedDTW(vector<vector<float> > *s, vector<vector<float> > *t, int w){
	float custo = 0;
	float result = 0;

	const int size_s = (*s).size();
	const int size_t = (*t).size();

	if(abs(size_s-size_t)>w){
		cout<<"Window size should be at least |m-n|"<<endl;
		return -1;
	}

	//float DTW[size_s+1][size_t+1];
	cin>>custo;
	float **DTW = (float**)malloc(sizeof(float*)*(size_s+1));
	for(int i =1; i<= size_s; ++i){
		DTW[i] = (float*)malloc(sizeof(float)*(size_t+1));
		DTW[i][0]= INT_MAX;
	}
	for(int i =1; i<= size_t; ++i){
		DTW[0][i]= INT_MAX;
	}

	DTW[0][0]=0;

	for (int i = 1; i <= size_s; ++i) {
		for (int j = 1; j <= size_t; ++j) {
			if(abs(i-j)<=w){
				custo = distancia(&((*s)[i-1]),&((*t)[j-1]));
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
