#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

class Fraction
{
private:
    int numerator;
    int denominator;

public:
    Fraction(){numerator=0; denominator=0;}
    Fraction(int); 
    Fraction(int, int);


    int getNumerator() {return numerator;}
    int getDenominator() {return denominator;}

    int getGCF(int, int);

    void setNumerator(int x) {numerator = x;}
    void setDenominator(int y) {denominator = y;}

    void simplify();

    Fraction operator+ (const Fraction);
    Fraction operator- (const Fraction);
    Fraction operator* (const Fraction);
    Fraction operator/ (const Fraction);

    bool operator< (const Fraction);
    bool operator> (const Fraction);
    bool operator== (Fraction&);

    friend std::ostream& operator<< (std::ostream& os, Fraction frac);
    friend std::istream& operator>> (std::istream& in, Fraction& frac);

};


#endif