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
#include "timer.h"
#include "CincoEspecies.h"
#include "22Especies.h"
#include "Parallel22.h"

#include "omp.h"

int rodaComVector(int N, bool imprime, int nCols=2){

	//************** declarations **************
	double start, finish, elapsed;

	vector<vector<double> > series[N];
	double **diff;

	ostringstream int2str;

	//************** allocations **************
	diff = (double**)malloc(N * sizeof*diff);

	for (int i = 0; i < N; ++i) {
		diff[i]=(double*)malloc((N-i)*sizeof(double));
	}


	//************** read **************
	for(int i = 0; i< N; i++){
		int2str<<i;
		read("especie1/matriz_"+int2str.str()+".csv", &series[i]);
		int2str.str("");
	}


	//************** DTW **************

	GET_TIME(start);

//#pragma omp parallel for
	for(int i = 0; i<N; i++){
		for(int j = i; j<N; j++){
			diff[i][j-i] = simpleDTW(&series[i],&series[j],nCols);
		}
	}

	GET_TIME(finish);


	//************** time **************
	elapsed = finish - start;

	cout << "\t time: "<< elapsed<< endl;


	//************** output **************
	if(imprime){
		for(int i = 0; i<N; i++){
			for(int j = 0; j<N-i; j++){
				cout<<diff[i][j]<<"\t";
			}
			cout<<endl;
		}
	}


	//************** free **************
	for(int i = 0; i< N; i++){
		free(diff[i]);
	}
	free(diff);

	return 0;

}

int rodaComPointer(int N, bool imprime, int nCols=2){

	//************** declarations **************
	double start, finish, elapsed;
	int * nLines;
	double ***series;

	ostringstream bla;
	string filename;


	//************** allocation **************
	nLines = (int*)malloc(N*sizeof(int));
	if ((series = (double***)malloc(N*sizeof *series)) == NULL) {
		perror("malloc 1");
		return -1;
	}

	double **diff = (double**)malloc(N * sizeof*diff);

	for (int i = 0; i < N; ++i) {
		diff[i]=(double*)malloc((N-i)*sizeof(double));
	}


	//************** read **************
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

	//************** DTW **************
	GET_TIME(start);

//#pragma omp parallel for
	for(int i = 0; i<N; i++){
		for(int j = i; j<N; j++){
			diff[i][j-i] = simpleDTW(series[i],nLines[i],series[j],nLines[j],nCols);
		}
	}

	GET_TIME(finish);

	//************** time **************
	elapsed = finish - start;
	cout << "\t time: "<< elapsed<< endl;

	//************** output **************
	if(imprime){
		for(int i = 0; i<N; i++){
			for(int j = 0; j<N-i; j++){
				cout<<diff[i][j]<<"\t";
			}
			cout<<endl;
		}
	}

	//************** free **************
	for(int i = 0; i< N; i++){
		for (int j = 0; j < nLines[i]; ++j) {
			free(series[i][j]);
		}
		free(series[i]);
		free(diff[i]);
	}
	free(series);
	free(diff);

	return 0;
}

int main(void){

	//int erro = rodaComVector(1000, false, 2);
	//erro += rodaComPointer(1000, false, 2);

	return roda22(true, 2);
	//return master(true,22);
}
