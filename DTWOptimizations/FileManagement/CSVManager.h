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

void print(vector<vector<long double> > *values);
vector<vector<long double> > *read(string filename, vector<vector<long double> > *output);


#endif /* CSVMANAGER_H_ */
