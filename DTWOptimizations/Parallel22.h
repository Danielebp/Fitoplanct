/*
 * Main.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: labproj
 */


#include <string>
#include <sstream>
#include <ctime>
#include <stdio.h>
#include <iomanip>
#include <pthread.h>

#include "FileManagement/CSVManager.h"
#include "DTWAlgorithms/DTW.h"
#include "timer.h"
#include "Fila.h"


#define NTHREADS  4


// variaveis globais
const int nEsp = 5;
int nCols = 2;
int ** nLines;
double ****series;
int nFiles[nEsp];
Fila* pares;


//funcao dos workers
void *workerF (void *arg) {

  q_elem elem;
  ostringstream streamer;
  string filename;
  string result;
  string line;
  FILE * fp;
  float diff;


  while(1){

  elem = pares->Retira();
  if(elem.s<0) break;

  streamer.str("");
  streamer<<(elem.s+1);
  filename = "result_"+streamer.str()+"_";

  streamer.str("");
  streamer<<(elem.t+1);

  result = filename+streamer.str()+ ".csv";

  fp = fopen (result.c_str(), "w+");


  for (int i = 0; i < nFiles[elem.s]; ++i) {
	  line = "";
	  for (int j = 0; j < nFiles[elem.t]; ++j) {

		  diff = simpleDTW(series[elem.s][i],nLines[elem.s][i],series[elem.t][j],nLines[elem.t][j],nCols);
		  streamer.str("");
		  streamer << fixed << setprecision(3) <<(diff);

		  line = line + "\"" + streamer.str() + "\"";
		  if(j<nFiles[elem.t]-1)line = line + "\,";
		  else line = line + "\n";
	  }
	  fprintf(fp, line.c_str());
  }
  fclose(fp);

  }

  pthread_exit(NULL);
}



int master(bool imprime, int nColunas=2){

	nCols = nColunas;
	//************** declarations **************
	double start, finish, elapsed;

	pthread_t threads[NTHREADS];

	string locations[nEsp];

	switch (nEsp) {
		case 22:
			locations[21]="Especies/especie22/";
			nFiles[21]=2000;
		case 21:
			locations[20]="Especies/especie21/";
			nFiles[20]=2000;
		case 20:
			locations[19]="Especies/especie20/";
			nFiles[19]=2000;
		case 19:
			locations[18]="Especies/especie19/";
			nFiles[18]=2000;
		case 18:
			locations[17]="Especies/especie18/";
			nFiles[17]=2000;
		case 17:
			locations[16]="Especies/especie17/";
			nFiles[16]=2000;
		case 16:
			locations[15]="Especies/especie16/";
			nFiles[15]=2000;
		case 15:
			locations[14]="Especies/especie15/";
			nFiles[14]=2000;
		case 14:
			locations[13]="Especies/especie14/";
			nFiles[13]=2000;
		case 13:
			locations[12]="Especies/especie13/";
			nFiles[12]=2000;
		case 12:
			locations[11]="Especies/especie12/";
			nFiles[11]=2000;
		case 11:
			locations[10]="Especies/especie11/";
			nFiles[10]=2000;
		case 10:
			locations[9]="Especies/especie10/";
			nFiles[9]=1000;
		case 9:
			locations[8]="Especies/especie9/";
			nFiles[8]=1000;
		case 8:
			locations[7]="Especies/especie8/";
			nFiles[7]=1000;
		case 7:
			locations[6]="Especies/especie7/";
			nFiles[6]=1000;
		case 6:
			locations[5]="Especies/especie6/";
			nFiles[5]=1000;
		case 5:
			locations[4]="Especies/especie5/";
			nFiles[4]=1000;
		case 4:
			locations[3]="Especies/especie4/";
			nFiles[3]=1600;
		case 3:
			locations[2]="Especies/especie3/";
			nFiles[2]=800;
		case 2:
			locations[1]="Especies/especie2/";
			nFiles[1]=1000;
		case 1:
			locations[0]="Especies/especie1/";
			nFiles[0]=1000;
			break;
		default:
			break;
	}


	ostringstream streamer;
	string filename;


	//************** allocation **************
	nLines = (int**)malloc(nEsp*sizeof*nLines);
	series = (double****)malloc(nEsp*sizeof *series);

	for (int i = 0; i < nEsp; ++i) {
		nLines[i] = (int*)malloc(nFiles[i]*sizeof*nLines[i]);
		series[i] = (double***)malloc(nFiles[i]*sizeof *series[i]);
	}


	//************** read **************
	for (int i = 0; i < nEsp; ++i) {
		for (int j = 0; j < nFiles[i]; ++j) {
			streamer<<j;

			filename = locations[i]+"matriz_"+streamer.str()+".csv";
			nLines[i][j] = getNumberOfLines(filename);

			series[i][j] = (double**)malloc(nLines[i][j]*sizeof*series[i][j]);

			read(filename, series[i][j], nLines[i][j], nCols);

			streamer.str("");
		}

	}


	//************** DTW **************

	int N=1;
	for (int i = nEsp; i > 0; --i) {
		N *= i;
	}

	pares = new Fila(N);
	q_elem elem;

	for (int i = 0; i < NTHREADS; ++i) {
			pthread_create(&threads[i], NULL, workerF, NULL);
	}

	GET_TIME(start);

	for (int s = 0; s < nEsp; ++s) {
		for (int t = s; t < nEsp; ++t) {
			elem.s=s;
			elem.t=t;
			pares->Insere(elem);
		}
	}

	for (int i = 0; i < NTHREADS; ++i) {
		elem.s=-1;
		elem.t=-1;
		pares->Insere(elem);
	}

	for (int i = 0; i < NTHREADS; i++) {
		pthread_join(threads[i], NULL);
	}

	GET_TIME(finish);

	//************** time **************
	elapsed = finish - start;
	cout << "\t time: "<< elapsed<< endl;

	//************** free **************

	free(series);
	free(nLines);

	return 0;
}


