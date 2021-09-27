#include "Real.h"
#include <iostream>

std::ostream& operator<< (std::ostream& out, const Real& realNum){
	out << realNum.realValue;
	return out;
}

bool Real::operator==(const Real& realNum){
	if(realValue == realNum.realValue){
		return true;
	}
	return false;
}

bool Real::operator<(const Real& realNum){
	if((realNum.realValue - realValue) > 0.001){
		return true;
	}
	return false;
}

bool Real::operator>(const Real& realNum){
	if((realNum.realValue - realValue) < -0.001){
		return true;
	}
	return false;
}




