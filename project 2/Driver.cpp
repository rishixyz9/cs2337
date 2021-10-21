#include "Driver.h"
#include <string>
#include <iostream>

std::string Driver::compare = "area";	//sets the default comparison to area

/* 
 * Driver overloaded constructor
 * Takes in a driver object to copy
 * sets the new objects data the same as the passed in object
 */
Driver::Driver(Driver& copyDriver){
	name = copyDriver.name;
	area = copyDriver.area;
}

/*
 * Overloaded comparison operator
 * Allows for the nodes to be compared
 * What is being compared is based off the compare static variable
 */
bool Driver::operator< (const Driver& rhs){
	if(compare == "area"){
		if(area < rhs.area){
			return true;
		}
		return false;
	}
	else{
		if(name < rhs.name){
			return true;
		}
		return false;
	}

}

/*
 * Overloaded comparison operator
 * Allows for the nodes to be compared
 * What is being compared is based off the compare static variable
 */
bool Driver::operator> (const Driver& rhs){
	if(compare == "area"){
		if(area > rhs.area){
			return true;
		}
		return false;
	}
	else{
		if(name > rhs.name){
			return true;
		}
		return false;
	}

}

/*
 * Overloaded insertion operator
 * Allows for simple output of the driver
 */
std::ostream& operator<< (std::ostream& out, const Driver& driver){
	out <<driver.name <<'\t';
	out <<driver.area;
	return out;
}