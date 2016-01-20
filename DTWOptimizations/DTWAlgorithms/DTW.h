/*
 * DTW.h
 *
 *  Created on: Jan 20, 2016
 *      Author: Daniele
 */

#ifndef DTW_H_
#define DTW_H_

#include "../Common.h"
#include <climits>
#include <cmath>

inline float distance(vector<float>* s, vector<float>* t){
	float d = 0;
	for (unsigned int i = 0; i < (*s).size(); ++i) {
		d += abs((*s)[i]-(*t)[i]);
	}
	return d;
}

inline float min(float f1, float f2, float f3){
	if(f2<f1)f1=f2;
	if(f3<f1)f1=f3;
	return f1;
}

float simpleDTW(vector<vector<float> > *s, vector<vector<float> > *t);

#endif /* DTW_H_ */
