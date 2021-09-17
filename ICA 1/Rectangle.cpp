#include "Rectangle.h"
#include <cmath>

Rectangle::Rectangle(Rectangle& copy){
	length = copy.length;
	width = copy.width;
}

Rectangle Rectangle::operator+ (const Rectangle& rhs){
	Rectangle temp;
	temp.setLength(length + rhs.length);
	temp.setWidth(width + rhs.width);
	return temp;
}

Rectangle Rectangle::operator- (const Rectangle& rhs){
	Rectangle temp;
	if(length - rhs.length < 0.0 && width - rhs.width > 0.0){
		temp.setLength(0.0);
		temp.setWidth(width - rhs.width);		
	}
	else if(width - rhs.width < 0.0 && length - rhs.length > 0.0){
		temp.setLength(length - rhs.length);
		temp.setWidth(0.0);		
	}
	else{
		temp.setLength(length - rhs.length);
		temp.setWidth(width - rhs.width);
	}
	return temp;
}

Rectangle& Rectangle::operator++ (){
	length += 1.0;
	width += 1.0;
	return *this;
}

Rectangle Rectangle::operator++ (int dummy){
	Rectangle temp(*this);
	operator++();
	return temp;
}

bool Rectangle::operator< (const Rectangle& rhs){
	if((length * width) < (rhs.length * rhs.width)){
		return true;
	}
	return false;
}

bool Rectangle::operator> (const Rectangle& rhs){
	if((length * width) > (rhs.length * rhs.width)){
		return true;
	}
	return false;
}

std::ostream& operator<< (std::ostream& out, const Rectangle& rhs){
	out << "Length: " << rhs.length;
	out << " Width: " << rhs.width;
	return out;
}