/*
 * Main.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: labproj
 */


#include "FileManagement/CSVManager.h"

int main(void){
	CSVManager csv0("matriz_0.csv");
	CSVManager csv1("matriz_1.csv");

	vector<vector<float> > serie0 = csv0.read();
	vector<vector<float> > serie1 = csv1.read();




}
