/*
 * Main.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: labproj
 */


#include "FileManagement/CSVManager.h"
#include "DTWAlgorithms/DTW.h"
#include <string>
#include <sstream>
#include <ctime>

int main(void){


	const int N=10;

	vector<vector<long double> > series[N];

	ostringstream bla;

	for(int i = 0; i< N; i++){
		bla<<i;
		read("especie1/matriz_"+bla.str()+".csv", &series[i]);
		bla.str("");
	}


	float diff[N][N];

	clock_t t1,t2;

	t1=clock();

	for(int i = 0; i<N; i++){
		for(int j = 0; j<N; j++){
			diff[i][j] = simpleDTW(&series[i],&series[j],2);
		}
	}

	t2 = clock();

	cout << "\t time: "<< ((float)t2-(float)t1)/1000<< endl;

	for(int i = 0; i<N; i++){
		for(int j = 0; j<N; j++){
			cout<<diff[i][j]<<"\t";
		}
		cout<<endl;
	}


	return 0;
}
