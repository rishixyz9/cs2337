#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include "Real.h"

class Complex: public Real{
private:
    double imaginaryValue;

public:
    Complex():Real() {imaginaryValue = 0.0;}
    Complex(double x):Real(x) {imaginaryValue = 0.0;}
    Complex(double x, double y):Real(x) {imaginaryValue = y;} 
    double getImaginary(){return imaginaryValue;}
    void setImaginary(double x) {imaginaryValue = x;}

    friend std::ostream& operator<< (std::ostream&, Complex&);

    virtual bool operator==(Real&);
    bool operator<(Real&);
    bool operator>(Real&);
};


#endif