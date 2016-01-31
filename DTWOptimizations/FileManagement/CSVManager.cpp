/*
 * CSVManager.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: labproj
 */

#include "CSVManager.h"



void print(vector<vector<double> > *values){


	for(unsigned int i = 0; i< (*values).size(); ++i){
		for(unsigned int j = 0; j< ((*values)[i]).size(); ++j){
			cout<<(*values)[i][j]<<"\t";
		}
		cout<<endl;
		cout.flush();
	}
}


vector<vector<double> > *read(string filename, vector<vector<double> > *output){

	ifstream ifile(filename.c_str());

	vector<double> tokens;

	string value;
	string temp;

	while ( getline ( ifile, value, '\n' ))
	{
		 stringstream ss(value);

		 while(getline(ss,temp,';')) {
			 double f = std::atof(temp.c_str());
			 tokens.push_back(f);
		 }

		 (*output).push_back(tokens);
		 tokens.erase(tokens.begin(), tokens.end());
	}
	ifile.close();

	return output;
}


int getNumberOfLines(string filename){
	ifstream ifile(filename.c_str());

	int n =0;
	string line;
	while ( getline ( ifile, line, '\n' ))
	{
		++n;
	}
	ifile.close();
	return n;
}
int getNumberOfCols(string filename){
	ifstream ifile(filename.c_str());

	int n =0;
	string value;
	while ( getline ( ifile, value, ';' ))
	{
		++n;
	}
	ifile.close();
	return n;
}

double** read(string filename, double **output, int nLines, int nCols){

	ifstream ifile(filename.c_str());

	string temp;


	for(int i=0; i<nLines; ++i){
		if((output[i] = (double*)malloc(nCols * sizeof(double)))==NULL){
			perror("malloc 3");
			return NULL;
		}



		getline ( ifile, temp, '\n' );
		stringstream ss(temp);

		for(int j=0; j<nCols; ++j){
			getline(ss,temp,';');
			output[i][j] = std::atof(temp.c_str());
		 }

	}
	ifile.close();

	return output;
}

void print(double **values, int nLines, int nCols){


	for(int i = 0; i< nLines; ++i){
		for(int j = 0; j< nCols; ++j){
			cout<<values[i][j]<<"\t";
		}
		cout<<endl;
		cout.flush();
	}
}
