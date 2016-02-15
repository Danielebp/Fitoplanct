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

#include "omp.h"




int rodaCinco(bool imprime, int nCols=2){

	//************** declarations **************
	double start, finish, elapsed;
	int nEsp = 5;
	int ** nLines;
	double ****series;

	string locations[nEsp];
	int nFiles[nEsp];

	locations[0]="Especies/especie1/";
	locations[1]="Especies/especie2/";
	locations[2]="Especies/especie3/";
	locations[3]="Especies/especie5/";
	locations[4]="Especies/especie11/";

	nFiles[0]=1000;
	nFiles[1]=1000;
	nFiles[2]=800;
	nFiles[3]=1000;
	nFiles[4]=2000;

	ostringstream bla;
	string filename;


	//************** allocation **************
	nLines = (int**)malloc(nEsp*sizeof*nLines);
	series = (double****)malloc(nEsp*sizeof *series);

	for (int i = 0; i < nEsp; ++i) {
		nLines[i] = (int*)malloc(nFiles[i]*sizeof*nLines[i]);
		series[i] = (double***)malloc(nFiles[i]*sizeof *series[i]);
	}


	/*double **diff = (double**)malloc(N * sizeof*diff);

	for (int i = 0; i < N; ++i) {
		diff[i]=(double*)malloc((N-i)*sizeof(double));
	}*/



	//************** read **************
	for (int i = 0; i < nEsp; ++i) {
		for (int j = 0; j < nFiles[i]; ++j) {
			bla<<j;

			filename = locations[i]+"matriz_"+bla.str()+".csv";
			nLines[i][j] = getNumberOfLines(filename);

			series[i][j] = (double**)malloc(nLines[i][j]*sizeof*series[i][j]);

			read(filename, series[i][j], nLines[i][j], nCols);

			bla.str("");
		}

	}


	//************** DTW **************

	GET_TIME(start);

	for (int s = 0; s < nEsp; ++s) {
		for (int i = 0; i < nFiles[s]; ++i) {
			for (int t = s; t < nEsp; ++t) {
				//criar um processo para cada for desse?
				for (int j = 0; j < nFiles[t]; ++j) {
					simpleDTW(series[s][i],nLines[s][i],series[t][j],nLines[t][j],nCols);
				}
			}
		}
		free(series[s]);
		free(nLines[s]);
	}


	GET_TIME(finish);

	//************** time **************
	elapsed = finish - start;
	cout << "\t time: "<< elapsed<< endl;

	//************** output **************
	/*if(imprime){
		for(int i = 0; i<N; i++){
			for(int j = 0; j<N-i; j++){
				cout<<diff[i][j]<<"\t";
			}
			cout<<endl;
		}
	}*/

	//************** free **************

	free(series);
	free(nLines);

	return 0;
}


