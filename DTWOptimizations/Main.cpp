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


int main(void){


	//return roda22(true, 2);
	return rodaTrain(true,2);
	//return rodaTest(true,2);
	pthread_exit(NULL);
}
