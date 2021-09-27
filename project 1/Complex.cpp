#include "Complex.h"
#include <iostream>
#include <math.h>

std::ostream& operator<< (std::ostream& out, Complex& complexNum){
	if(complexNum.getReal() != 0.0){
		out << complexNum.getReal();
		if(complexNum.imaginaryValue > 0.0){
			out << "+" << complexNum.imaginaryValue << "i";
		}
		else if(complexNum.imaginaryValue < 0.0){
			out << complexNum.imaginaryValue << "i";
		}
	}

	else{
		if(complexNum.imaginaryValue != 0.0){
			out << complexNum.imaginaryValue << "i";
		}
		else{
			out << complexNum.getReal();
		}
	}
	return out;
}

bool Complex::operator==(Real& rhs){
	Complex* cref = dynamic_cast<Complex*>(&rhs);
	if(cref == nullptr){
		if(this->getReal() == rhs.getReal() && this->imaginaryValue == 0.0){
			return true;
		}
	}
	else if(this->getReal() == cref->getReal() && this->imaginaryValue == cref->imaginaryValue){
		return true;
	}
	return false;
}

bool Complex::operator<(Real& rhs){
	Complex* cref = dynamic_cast<Complex*>(&rhs);
	if(cref == nullptr){
		return sqrt(pow(this->getReal(),2) + pow(this->imaginaryValue,2)) < rhs.getReal();
	}
	else if(pow(this->getReal(),2) + pow(this->imaginaryValue,2) < pow(cref->getReal(),2) + pow(cref->imaginaryValue,2)){
		return true;
	}
	return false;
}

bool Complex::operator>(Real& rhs){
	Complex* cref = dynamic_cast<Complex*>(&rhs);
	if(cref == nullptr){
		return sqrt(pow(this->getReal(),2) + pow(this->imaginaryValue,2)) > rhs.getReal();
	}
	else if(pow(this->getReal(),2) + pow(this->imaginaryValue,2) > pow(cref->getReal(),2) + pow(cref->imaginaryValue,2)){
		return true;
	}
	return false;
}