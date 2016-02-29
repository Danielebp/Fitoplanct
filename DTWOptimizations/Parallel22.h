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


#define NTHREADS  20


// variaveis globais
const int nEsp = 22;
int nCols = 2;
int ** nLines;
int ** nLinesTest;
double ****series;
double ****seriesTest;
int nFiles[nEsp];
int nFilesTest[nEsp];
Fila* pares;


//funcao dos workers
void *workerF (void * tid) {

  int id = * (int *) tid;
  free(tid);

  q_elem elem;
  ostringstream streamer;
  string filename;
  string result;
  string line;
  FILE * fp;
  double diff;

  //cout<<"thread: "<<id<<endl;


  while(1){

  elem = pares->Retira();
  if(elem.s<0) break;

  streamer.str("");
  streamer<<(elem.s+1);
  filename = "./trainResult/result_"+streamer.str()+"_";

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

  if(id>0){
	  pthread_exit(NULL);
  }

}

int rodaTrain(bool imprime, int nColunas=2){

	nCols = nColunas;
	//************** declarations **************
	double start, finish, elapsed;

	pthread_t threads[NTHREADS-1];
	int *tid ;

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

	int N=0;
	for (int i = nEsp; i > 0; --i) {
		N += i;
	}

	pares = new Fila(N);
	q_elem elem;
	
	GET_TIME(start);

	for (int i = 0; i < NTHREADS-1; ++i) {
		tid = (int*)malloc(sizeof(int)); if(tid==NULL) { printf("--ERRO: malloc()\n"); exit(-1); }
		*tid = i+1;
		pthread_create(&threads[i], NULL, workerF, (void*)tid);
	}

	//GET_TIME(start);


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
	tid = (int*)malloc(sizeof(int)); if(tid==NULL) { printf("--ERRO: malloc()\n"); exit(-1); }
	*tid = 0;
	workerF(tid);

	for (int i = 0; i < NTHREADS-1; i++) {
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


//funcao dos workers
void *workerTest (void * tid) {

  int id = * (int *) tid;
  free(tid);

  q_elem elem;
  ostringstream streamer;
  string filename;
  string result;
  string line;
  FILE * fp;
  double diff;

  //cout<<"thread: "<<id<<endl;


  while(1){

  elem = pares->Retira();
  if(elem.s<0) break;

  streamer.str("");
  streamer<<(elem.s+1);
  filename = "./testResult/test_result_"+streamer.str()+"_";

  streamer.str("");
  streamer<<(elem.t+1);

  result = filename+streamer.str()+ ".csv";

  fp = fopen (result.c_str(), "w+");


  for (int i = 0; i < nFilesTest[elem.s]; ++i) {
	  line = "";
	  for (int j = 0; j < nFiles[elem.t]; ++j) {

		  diff = simpleDTW(seriesTest[elem.s][i],nLinesTest[elem.s][i],series[elem.t][j],nLines[elem.t][j],nCols);
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

  if(id>0){
	  pthread_exit(NULL);
  }

}

int rodaTest(bool imprime, int nColunas=2){

	nCols = nColunas;
	//************** declarations **************
	double start, finish, elapsed;

	pthread_t threads[NTHREADS-1];
	int *tid ;

	string locations[nEsp];
	string locationsTest[nEsp];

	switch (nEsp) {
		case 22:
			locations[21]="Especies/especie22/";
			nFiles[21]=2000;
			locationsTest[21]="TestSet/especie22/";
			nFilesTest[21]=200;
		case 21:
			locations[20]="Especies/especie21/";
			nFiles[20]=2000;
			locationsTest[20]="TestSet/especie21/";
			nFilesTest[20]=200;
		case 20:
			locations[19]="Especies/especie20/";
			nFiles[19]=2000;
			locationsTest[19]="TestSet/especie20/";
			nFilesTest[19]=200;
		case 19:
			locations[18]="Especies/especie19/";
			nFiles[18]=2000;
			locationsTest[18]="TestSet/especie19/";
			nFilesTest[18]=200;
		case 18:
			locations[17]="Especies/especie18/";
			nFiles[17]=2000;
			locationsTest[17]="TestSet/especie18/";
			nFilesTest[17]=200;
		case 17:
			locations[16]="Especies/especie17/";
			nFiles[16]=2000;
			locationsTest[16]="TestSet/especie17/";
			nFilesTest[16]=200;
		case 16:
			locations[15]="Especies/especie16/";
			nFiles[15]=2000;
			locationsTest[15]="TestSet/especie16/";
			nFilesTest[15]=200;
		case 15:
			locations[14]="Especies/especie15/";
			nFiles[14]=2000;
			locationsTest[14]="TestSet/especie15/";
			nFilesTest[14]=200;
		case 14:
			locations[13]="Especies/especie14/";
			nFiles[13]=2000;
			locationsTest[13]="TestSet/especie14/";
			nFilesTest[13]=200;
		case 13:
			locations[12]="Especies/especie13/";
			nFiles[12]=2000;
			locationsTest[12]="TestSet/especie13/";
			nFilesTest[12]=200;
		case 12:
			locations[11]="Especies/especie12/";
			nFiles[11]=2000;
			locationsTest[11]="TestSet/especie12/";
			nFilesTest[11]=200;
		case 11:
			locations[10]="Especies/especie11/";
			nFiles[10]=2000;
			locationsTest[10]="TestSet/especie11/";
			nFilesTest[10]=200;
		case 10:
			locations[9]="Especies/especie10/";
			nFiles[9]=1000;
			locationsTest[9]="TestSet/especie10/";
			nFilesTest[9]=369;
		case 9:
			locations[8]="Especies/especie9/";
			nFiles[8]=1000;
			locationsTest[8]="TestSet/especie9/";
			nFilesTest[8]=369;
		case 8:
			locations[7]="Especies/especie8/";
			nFiles[7]=1000;
			locationsTest[7]="TestSet/especie8/";
			nFilesTest[7]=369;
		case 7:
			locations[6]="Especies/especie7/";
			nFiles[6]=1000;
			locationsTest[6]="TestSet/especie7/";
			nFilesTest[6]=369;
		case 6:
			locations[5]="Especies/especie6/";
			nFiles[5]=1000;
			locationsTest[5]="TestSet/especie6/";
			nFilesTest[5]=369;
		case 5:
			locations[4]="Especies/especie5/";
			nFiles[4]=1000;
			locationsTest[4]="TestSet/especie5/";
			nFilesTest[4]=445;
		case 4:
			locations[3]="Especies/especie4/";
			nFiles[3]=1600;
			locationsTest[3]="TestSet/especie4/";
			nFilesTest[3]=397;
		case 3:
			locations[2]="Especies/especie3/";
			nFiles[2]=800;
			locationsTest[2]="TestSet/especie3/";
			nFilesTest[2]=236;
		case 2:
			locations[1]="Especies/especie2/";
			nFiles[1]=1000;
			locationsTest[1]="TestSet/especie2/";
			nFilesTest[1]=247;
		case 1:
			locations[0]="Especies/especie1/";
			nFiles[0]=1000;
			locationsTest[0]="TestSet/especie1/";
			nFilesTest[0]=456;
			break;
		default:
			break;
	}


	ostringstream streamer;
	string filename;



	//************** allocation **************
	nLines = (int**)malloc(nEsp*sizeof*nLines);
	series = (double****)malloc(nEsp*sizeof *series);
	nLinesTest = (int**)malloc(nEsp*sizeof*nLinesTest);
	seriesTest = (double****)malloc(nEsp*sizeof *seriesTest);

	for (int i = 0; i < nEsp; ++i) {
		nLines[i] = (int*)malloc(nFiles[i]*sizeof*nLines[i]);
		series[i] = (double***)malloc(nFiles[i]*sizeof *series[i]);
		nLinesTest[i] = (int*)malloc(nFilesTest[i]*sizeof*nLinesTest[i]);
		seriesTest[i] = (double***)malloc(nFilesTest[i]*sizeof *seriesTest[i]);
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
		for (int j = 0; j < nFilesTest[i]; ++j) {
			streamer<<j;

			filename = locationsTest[i]+"matriz_"+streamer.str()+".csv";
			nLinesTest[i][j] = getNumberOfLines(filename);

			seriesTest[i][j] = (double**)malloc(nLinesTest[i][j]*sizeof*seriesTest[i][j]);

			read(filename, seriesTest[i][j], nLinesTest[i][j], nCols);

			streamer.str("");
		}

	}


	//************** DTW **************

	int N=0;
	for (int i = nEsp; i > 0; --i) {
		N += i;
	}

	pares = new Fila(N);
	q_elem elem;

	GET_TIME(start);

	for (int i = 0; i < NTHREADS-1; ++i) {
		tid = (int*)malloc(sizeof(int)); if(tid==NULL) { printf("--ERRO: malloc()\n"); exit(-1); }
		*tid = i+1;
		pthread_create(&threads[i], NULL, workerTest, (void*)tid);
	}

	//GET_TIME(start);


	for (int s = 0; s < nEsp; ++s) {
		for (int t = 0; t < nEsp; ++t) {
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
	tid = (int*)malloc(sizeof(int)); if(tid==NULL) { printf("--ERRO: malloc()\n"); exit(-1); }
	*tid = 0;
	workerTest(tid);

	for (int i = 0; i < NTHREADS-1; i++) {
		pthread_join(threads[i], NULL);
	}

	GET_TIME(finish);

	//************** time **************
	elapsed = finish - start;
	cout << "\t time: "<< elapsed<< endl;

	//************** free **************

	free(series);
	free(nLines);
	free(seriesTest);
	free(nLinesTest);

	return 0;
}


