/*
 * CSVManager.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: labproj
 */

#include "CSVManager.h"



void print(vector<vector<long double> > *values){


	for(unsigned int i = 0; i< (*values).size(); ++i){
		for(unsigned int j = 0; j< ((*values)[i]).size(); ++j){
			cout<<(*values)[i][j]<<"\t";
		}
		cout<<endl;
		cout.flush();
	}
}


vector<vector<long double> > *read(string filename, vector<vector<long double> > *output){

	ifstream ifile(filename.c_str());

	vector<long double> tokens;

	string value;
	string temp;

	while ( getline ( ifile, value, '\n' ))
	{
		 stringstream ss(value);

		 while(getline(ss,temp,';')) {
			 long double f = std::atof(temp.c_str());
			 tokens.push_back(f);
		 }

		 (*output).push_back(tokens);
		 tokens.erase(tokens.begin(), tokens.end());
	}

	return output;
};
