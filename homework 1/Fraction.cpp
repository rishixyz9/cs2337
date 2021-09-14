#include "Fraction.h"
#include <cmath>
#include <iostream>


Fraction::Fraction(int x){
    numerator = x;
    denominator = 1;
}

Fraction::Fraction(int x, int y){
    numerator = x;
    denominator = y;
}

int Fraction::getGCF(int x, int y){
    if(x < y){
        if(y % x == 0){
            return abs(x);
        }
        else{
            int temp =  y;
            while(x%temp != 0 || y%temp != 0){
                if(temp <= 1){
                    return 1;
                }
                temp -= x;
            }
            return abs(temp);
        }
    }
    else if(x > y){
        getGCF(y,x);
    }
    return abs(x);
}

void Fraction::simplify(){
    if(numerator != 0 && denominator != 0){
        int gcf = getGCF(numerator, denominator);
        setNumerator(numerator/gcf);
        setDenominator(denominator/gcf);
    }
    else{
        setNumerator(0);
        setDenominator(0);
    }
}

Fraction Fraction::operator+ (const Fraction frac){
    Fraction result;
    if(denominator == frac.denominator || (denominator == 0 || frac.denominator == 0)){
        result.numerator = numerator + frac.numerator;
        result.denominator = denominator;
    }
    else{
        result.numerator = denominator * frac.numerator + frac.denominator * numerator;
        result.denominator = denominator * frac.denominator;      
    }
    result.simplify();
    return result;
}

Fraction Fraction::operator- (const Fraction frac){
    Fraction result;
    if(denominator == frac.denominator || (denominator == 0 || frac.denominator == 0)){
        result.numerator = abs(numerator - frac.numerator);
        result.denominator = denominator;
    }
    else{
        result.numerator = abs(frac.denominator * numerator - denominator * frac.numerator);
        result.denominator = denominator * frac.denominator;      
    }
    result.simplify();
    return result;
}

Fraction Fraction::operator* (const Fraction frac){
    Fraction result;
    result.numerator = numerator * frac.numerator;
    result.denominator = denominator * frac.denominator;
    result.simplify();
    return result;
}

Fraction Fraction::operator/ (const Fraction frac){
    Fraction result;
    result.numerator = numerator * frac.denominator;
    result.denominator = denominator * frac.numerator;
    result.simplify();
    return result;
}

bool Fraction::operator< (const Fraction frac){
    if(float(numerator)/float(denominator) < float(frac.numerator)/float(frac.denominator)){
        return true;
    }
    return false;
}

bool Fraction::operator> (const Fraction frac){
    if(float(numerator)/float(denominator) > float(frac.numerator)/float(frac.denominator)){
        return true;
    }
    return false;
}

bool Fraction::operator== (Fraction& frac){
    Fraction temp = Fraction(numerator, denominator);
    temp.simplify();
    frac.simplify();
    if(temp.numerator == frac.numerator && temp.denominator == frac.denominator){
        return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, Fraction frac){
    os << frac.getNumerator() << " / " << frac.getDenominator();
    return os;
}

std::istream& operator>>(std::istream& in, Fraction& frac){
    int temp;
    std::cout << "Enter numerator ";
    in >> temp;
    frac.setNumerator(temp);
    std::cout << "Enter denominator ";
    in >> temp;
    frac.setDenominator(temp);
    frac.simplify();
    return in;
}

