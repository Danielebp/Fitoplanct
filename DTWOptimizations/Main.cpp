/*
 * Main.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: labproj
 */


#include "FileManagement/CSVManager.h"
#include "DTWAlgorithms/DTW.h"

int main(void){


	vector<vector<float> > serie0 = read("matriz_0.csv");
	vector<vector<float> > serie1 = read("matriz_1.csv");


	float diff = simpleDTW(serie0,serie1);

	cout << diff << endl;



	return 0;
}
