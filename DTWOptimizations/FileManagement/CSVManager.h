/*
 * CSVManager.h
 *
 *  Created on: Jan 18, 2016
 *      Author: labproj
 */

#ifndef CSVMANAGER_H_
#define CSVMANAGER_H_

#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
#include<cstdlib>

using namespace std;


class CSVManager {

public:

	ifstream ifile;

	CSVManager(string filename);
	virtual ~CSVManager();

	void print();

	vector<vector<float> > read();
};

#endif /* CSVMANAGER_H_ */
