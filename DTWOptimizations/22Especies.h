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
#include <stdio.h>
#include <iomanip>



int roda22(bool imprime, int nCols=2){

	//************** declarations **************
	double start, finish, elapsed;
	int nEsp = 5;
	int ** nLines;
	double ****series;

	FILE * fp;

	string locations[nEsp];
	int nFiles[nEsp];

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


	string result;
	string line;
	double diff;

	GET_TIME(start);

	for (int s = 0; s < nEsp; ++s) {
		streamer.str("");
		streamer<<(s+1);
		filename = "result_"+streamer.str()+"_";

		for (int t = s; t < nEsp; ++t) {
			streamer.str("");
			streamer<<(t+1);

			result = filename+streamer.str()+ ".csv";

			fp = fopen (result.c_str(), "w+");

			for (int i = 0; i < nFiles[s]; ++i) {
				line = "";
				for (int j = 0; j < nFiles[t]; ++j) {

					diff = simpleDTW(series[s][i],nLines[s][i],series[t][j],nLines[t][j],nCols);
					streamer.str("");
					streamer << fixed << setprecision(3) <<(diff);

					line = line + "\"" + streamer.str() + "\"";
					if(j<nFiles[t]-1)line = line + "\,";
					else line = line + "\n";
				}
				fprintf(fp, line.c_str());
			}
			fclose(fp);
		}
		free(series[s]);
		free(nLines[s]);
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


