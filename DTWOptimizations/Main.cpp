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


	int N=1000;

	const int nCols = 2;

	int * nLines = (int*)malloc(N*sizeof(int));


	double ***series;

	if ((series = (double***)malloc(N*sizeof *series)) == NULL) {
		perror("malloc 1");
		return -1;
	}


	ostringstream bla;
	string filename;


	for(int i = 0; i< N; i++){
		bla<<i;

		filename = "especie1/matriz_"+bla.str()+".csv";
		nLines[i] = getNumberOfLines(filename);

		if((series[i] = (double**)malloc(nLines[i]*sizeof*series[i]))==NULL){\
			perror("malloc 2");
			return -2;
		}


		read(filename, series[i], nLines[i], nCols);
		bla.str("");
	}

	double **diff = (double**)malloc(N * sizeof*diff);

	for (int i = 0; i < N; ++i) {
		diff[i]=(double*)malloc(N*sizeof(double));
	}

	clock_t t1,t2;

	t1=clock();

	for(int i = 0; i<N; i++){
		for(int j = 0; j<N; j++){
			diff[i][j] = simpleDTW(series[i],nLines[i],series[j],nLines[j],nCols);
		}
	}

	t2 = clock();

	cout << "\t time: "<< ((float)t2-(float)t1)/1000<< endl;

	/*for(int i = 0; i<N; i++){
		for(int j = 0; j<N; j++){
			cout<<diff[i][j]<<"\t";
		}
		cout<<endl;
	}*/


	/*int N=1000;

	vector<vector<double> > series[N];

	ostringstream bla;

	for(int i = 0; i< N; i++){
		bla<<i;
		read("especie1/matriz_"+bla.str()+".csv", &series[i]);
		bla.str("");
	}


	//double diff[N][N];
	double **diff = (double**)malloc(N * sizeof*diff);

	for (int i = 0; i < N; ++i) {
		diff[i]=(double*)malloc(N*sizeof(double));
	}

	clock_t t1,t2;

	t1=clock();

	for(int i = 0; i<N; i++){
		for(int j = 0; j<N; j++){
			diff[i][j] = simpleDTW(&series[i],&series[j],2);
		}
	}

	t2 = clock();

	cout << "\t time: "<< ((float)t2-(float)t1)/1000<< endl;

	*/


	return 0;
}
