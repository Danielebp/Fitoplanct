/*
 * CSVManager.h
 *
 *  Created on: Jan 18, 2016
 *      Author: labproj
 */

#ifndef CSVMANAGER_H_
#define CSVMANAGER_H_

#include "../Common.h"
#include<sstream>
#include<fstream>

void print(vector<vector<double> > *values);
vector<vector<double> > *read(string filename, vector<vector<double> > *output);

int getNumberOfCols(string filename);
int getNumberOfLines(string filename);
double** read(string filename, double **output, int nLines, int nCols);
void print(double **values, int nLines, int nCols);

#endif /* CSVMANAGER_H_ */
