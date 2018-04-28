#include <iostream>
#include <cmath>
#include "VectorMath.h"

float VectorMath::angle(float x1, float y1, float x2, float y2){
	if(x2-x1 == 0){
		if(y1 < y2){
			return M_PI;
		}
		else{
			return 0;
		}
	}
	if(x1<x2){
		return atan((y2-y1)/(x2-x1))+(M_PI/2);
	}
	else{
		return atan((y2-y1)/(x2-x1))+(3*M_PI/2);
	}
}
