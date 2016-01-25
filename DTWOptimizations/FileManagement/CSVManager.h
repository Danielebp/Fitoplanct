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

void print(vector<vector<float> > *values);
vector<vector<float> > *read(string filename, vector<vector<float> > *output);


#endif /* CSVMANAGER_H_ */
