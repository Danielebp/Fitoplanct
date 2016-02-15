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




int roda22(bool imprime, int nCols=2){

	//************** declarations **************
	double start, finish, elapsed;
	int nEsp = 1;
	int ** nLines;
	double ****series;

	string locations[nEsp];
	int nFiles[nEsp];

	locations[0]="Especies/especie1/";
	/*locations[1]="Especies/especie2/";
	locations[2]="Especies/especie3/";
	locations[3]="Especies/especie4/";
	locations[4]="Especies/especie5/";
	locations[5]="Especies/especie6/";
	locations[6]="Especies/especie7/";
	locations[7]="Especies/especie8/";
	locations[8]="Especies/especie9/";
	locations[9]="Especies/especie10/";
	locations[10]="Especies/especie11/";
	locations[11]="Especies/especie12/";
	locations[12]="Especies/especie13/";
	locations[13]="Especies/especie14/";
	locations[14]="Especies/especie15/";
	locations[15]="Especies/especie16/";
	locations[16]="Especies/especie17/";
	locations[17]="Especies/especie18/";
	locations[18]="Especies/especie19/";
	locations[19]="Especies/especie20/";
	locations[20]="Especies/especie21/";
	locations[21]="Especies/especie22/";*/

	nFiles[0]=1000;
	/*nFiles[1]=1000;
	nFiles[2]=800;
	nFiles[3]=1600;
	nFiles[4]=1000;
	nFiles[5]=1000;
	nFiles[6]=1000;
	nFiles[7]=1000;
	nFiles[8]=1000;
	nFiles[9]=1000;
	nFiles[10]=2000;
	nFiles[11]=2000;
	nFiles[12]=2000;
	nFiles[13]=2000;
	nFiles[14]=2000;
	nFiles[15]=2000;
	nFiles[16]=2000;
	nFiles[17]=2000;
	nFiles[18]=2000;
	nFiles[19]=2000;
	nFiles[20]=2000;
	nFiles[21]=2000;*/

	ostringstream bla;
	string filename;


	//************** allocation **************
	nLines = (int**)malloc(nEsp*sizeof*nLines);
	series = (double****)malloc(nEsp*sizeof *series);

	for (int i = 0; i < nEsp; ++i) {
		//cout<<i<<endl;
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
		for (int t = s; t < nEsp; ++t) {
			//cout<<"file_"<<s<<"_"<<t<<endl;
			for (int i = 0; i < nFiles[s]; ++i) {
				//criar um processo para cada for desse?
				for (int j = 0; j < nFiles[t]; ++j) {
					//cout<<simpleDTW(series[s][i],nLines[s][i],series[t][j],nLines[t][j],nCols)<<",";
					printf("\"%.3f\"",simpleDTW(series[s][i],nLines[s][i],series[t][j],nLines[t][j],nCols));
					if(j<nFiles[t]-1)printf("\,");
				}
			cout<<endl;
			}
			//cout<<endl<<endl;
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


