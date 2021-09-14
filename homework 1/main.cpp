#include <iostream>
#include <string>
#include <cmath>
#include "Fraction.h"

using namespace std;

int main(){
	Fraction frac1,frac2;
	frac1.setNumerator(1);
	frac1.setDenominator(4);

	cin >> frac2;


	cout << frac1 + frac2<< endl;
	cout << frac1 - frac2<< endl;
	cout << frac1 * frac2<< endl;
	cout << frac1 / frac2<< endl;

	bool temp = frac1 < frac2;
	cout << temp << endl;

	temp = frac1 > frac2;
	cout << temp << endl;

	temp = frac1 == frac2;
	cout << temp << endl;

	return 0; 
}
