#include "Rectangle.h"
#include <cmath>
#include <iostream>

using namespace std;

int main(){
	Rectangle rect1(2.0,2.0);
	Rectangle rect2(rect1);

	rect2.setWidth(3.0);
	rect2.setLength(3.0);

	cout << rect1 + rect2 << endl;
	cout << rect1 - rect2 << endl;
	cout << rect1++ << endl;
	cout << ++rect2 << endl;
	cout << "rect1: " << rect1 << endl;
	cout << "rect2: " << rect2 << endl;
	cout << (rect1 < rect2) << endl;
	cout << (rect1 > rect2) << endl;
	cout << "area of rect1: " << (rect1.getLength()*rect1.getWidth()) << endl 
		 << "area of rect2: " << (rect2.getLength()*rect2.getWidth()) << endl;

	return 0;
}




