#ifndef REAL_H
#define REAL_H

#include <iostream>

class Real{
private:
    double realValue;

public:
    Real(){realValue = 0.0;}
    Real(double x){realValue = x;}
    double getReal(){return realValue;}
    void setReal(double x){realValue = x;}

    friend std::ostream& operator<< (std::ostream&, const Real&);

    virtual bool operator==(const Real&);
    virtual bool operator<(const Real&);
    virtual bool operator>(const Real&);

    virtual ~Real(){};
};


#endif