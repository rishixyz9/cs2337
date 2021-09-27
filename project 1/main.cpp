#include "Complex.h"
#include "Real.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

/* 
 * Rishabh Vemparala
 * rxv200022
 * CS 2337.02
 */

//Function prototypes for functions used in main
void readLine(string, string[]);

bool isValidOperand(string);
bool isValidOperator(string, string);

//Function prototypes for functions which will be used to carry out operations
void addition(Real*, Real*);
void subtraction(Real*, Real*);
void multiplication(Real*, Real*);
void division(Real*, Real*);
bool equals(Real*, Real*);
bool lessThan(Real*, Real*);
bool greaterThan(Real*, Real*);

Complex parseOperand(string);


int main(){
	string const VALID_OPERATORS = " + - * / < > = ";

	/*
	 * Operands array contains the parsed data from the file input in string format
	 * The first element in the array contains the left hand side operand before the operator
	 * The 2nd element contains the operator in the expression
	 * The 3rd element contains the the right hand side operand after the operator
	 */
	string operands[3];
	string fileName;
	string line;

	/*
	 * Asks the user for the name of the file to be read and stores it in 
	 * the fileName variable
	 */

	cout << "What is the file name?" << endl
		 << "> ";
	cin >> fileName;

	/*
	 * Opens the file if it is a valid filename 
	 */

	ifstream fileInput;
	fileInput.open(fileName);

	if(fileInput.is_open()){
		cout << "file successfully opened" << endl;
		while(!fileInput.eof() && fileInput.good()){
			//Reads each line and puts it into the operands array
			getline(fileInput, line);
			readLine(line, operands);


		    /*
		 	 * Validates if both operands are valid
	 		 * If valid, Carries out the calculations specified by the 2nd index in the operands array 
	 		 * Ignores the line if any of the elements in the operands array is invalid
	 		 */
			if(isValidOperand(operands[0]) && isValidOperand(operands[2]) && isValidOperator(operands[1], VALID_OPERATORS)){
				Real* operand1;
				Real* operand2;

				/*
				 * Dynamically creates a complex or real object depending on if there is an i in the string
				 * Does this for both operands in the array
				 */
				if(operands[0].back() == 'i'){
					operand1 = new Complex(parseOperand(operands[0]).getReal(), parseOperand(operands[0]).getImaginary());
				}
				else{
					operand1 = new Real(parseOperand(operands[0]).getReal());
				}
				if(operands[2].back() == 'i'){
					operand2 = new Complex(parseOperand(operands[2]).getReal(), parseOperand(operands[2]).getImaginary());
				}
				else{
					operand2 = new Real(parseOperand(operands[2]).getReal());
				}

				/*
				 * Outputs the results of the calculations of the expression
				 * Uses the 2nd element of the operands array to decide which operation to use
				 * ie. if '+' is located in the 2nd element, the addition function would be carried out
				 */
				cout << fixed << setprecision(2);
				cout << operands[0] << " " << operands[1] << " " << operands[2] << "\t";
				if(operands[1] == "+"){
					addition(operand1, operand2);
				}
				if(operands[1] == "-"){
					subtraction(operand1, operand2);
				}
				if(operands[1] == "*"){
					multiplication(operand1, operand2);
				}
				if(operands[1] == "/"){
					division(operand1, operand2);
				}
				if(operands[1] == "<"){
					if(lessThan(operand1, operand2)){
						cout << "true" << endl;
					}
					else{
						cout << "false" << endl;
					}
				}
				if(operands[1] == ">"){
					if(greaterThan(operand1, operand2)){
						cout << "true" << endl;
					}
					else{
						cout << "false" << endl;
					}
				}
				if(operands[1] == "="){
					if(equals(operand1, operand2)){
						cout << "true" << endl;
					}
					else{
						cout << "false" << endl;
					}
				}
				/* 
				 * Deletes the dynamically created object as to not waste memory 
				 * between each iteration of the loop and after the loop has finished
				 */
				delete operand1;
				delete operand2;
			}
			
			
		}
	}
	return 0;
}

/*
 * Reads a line from the file and parses the input into an array size 3 (operand array)
 * Reads until the first space to get the first operand
 * Reads until the next space to get the operator
 * Reads until the end of the line to get the last operand
 */
void readLine(string line, string arr[3]){
	stringstream spaceRemover;
	spaceRemover.str(line);
	getline(spaceRemover, arr[0],' ');
	getline(spaceRemover, arr[1],' ');
	getline(spaceRemover, arr[2]);
}

/*
 * Validates if the operand is valid 
 * Returns true if the input is valid and false otherwise
 */
bool isValidOperand(string operand){
	stringstream stringReader;
	stringReader.str(operand);
	double num1;
	string num2;
	bool validOperand = true;
	/*
	 * Reads the operand if there is an i at the end 
	 * if the operand has any invalid characters or extra decimal places then it would return false
	 */
	if(operand.back() == 'i'){ 
		if(stringReader >> num1){
			if(stringReader >> num2){
				size_t minus = num2.find('-');
				size_t plus = num2.find('+');
				validOperand = false;
				if(minus != string::npos || plus != string::npos || num2 == "i"){
					validOperand = true;
				}
				int counter = 0;
				int i=0;
				while(num2[i]){
					if(num2[i] == '.'){
						counter++;
					}
					if(counter >= 2){
						validOperand = false;
						break;
					}
					i++;
				}					
			}
		}
		else{
			validOperand = false;
		}		
	}
	/*
	 * Reads the operand if there is not an i at the end of the operand
	 * if the operand can read after the first double, then it returns false
	 * ie. a real number of 6.231 would return true where as 6.231.67 would return false
	 */
	else{
		stringReader >> num1;
		if(stringReader >> num2){
			validOperand = false;		
		}
	}	
	return validOperand;		
}

/*
 * Returns true if the input operator is a valid operator
 * Returns false otherwise
 * takes in the string operator and a constant string of valid operators
 * if the operator is not found in the const string it returns false
 */
bool isValidOperator(string operators, string VALID_OPERATORS){
	size_t found = VALID_OPERATORS.find(operators);
	return found != string::npos;
}


/*
 * Reads a string and parses it into a complex number object
 * if it sees an i in the string, it initializes the imaginary and real attributes
 * otherwise, it initializes only the real attributes
 */
Complex parseOperand(string operand){
	stringstream objectParser;
	objectParser.str(operand);
	double first;
	double second;
	Complex temp;
	objectParser >> first;
	if(operand.back() == 'i'){
		temp.setImaginary(1.0);
		if(first != 0.0){
			temp.setImaginary(first);
		}
		if(objectParser >> second){
			temp.setReal(first);
			temp.setImaginary(second);
		}
		return temp;
	}
	else{
		temp.setReal(first);
		return temp;
	}
}

/*
 * Carries out the addition function and directly outputs it to the console
 * Dynamically casts the input to figure out how to add the variables passed in
 * Takes in 2 real number pointers
 * if the result of the dynamic cast is a nullptr that means it is a real number
 */
void addition(Real* operand1, Real* operand2){
	Complex* lhs = dynamic_cast<Complex*>(operand1);
	Complex* rhs = dynamic_cast<Complex*>(operand2);
	if(lhs == nullptr){
		if(rhs == nullptr){
			Real temp(operand1->getReal() + operand2->getReal());
			cout << temp << endl;
		}
		else{
			Complex temp(operand1->getReal() + operand2->getReal(), rhs->getImaginary());
			cout << temp << endl;
		}
	}
	else{
		if(rhs == nullptr){
			Complex temp(lhs->getReal() + operand2->getReal(), lhs->getImaginary());
			cout << temp << endl;
		}
		else{
			Complex temp(lhs->getReal() + rhs->getReal(), lhs->getImaginary() + rhs->getImaginary());
			cout << temp << endl;
		}
	}
}

/*
 * Carries out the subtraction function and directly outputs it to the console
 * Dynamically casts the input to figure out how to add the variables passed in
 * Takes in 2 real number pointers
 * if the result of the dynamic cast is a nullptr that means it is a real number
 */
void subtraction(Real* operand1, Real* operand2){
	Complex* lhs = dynamic_cast<Complex*>(operand1);
	Complex* rhs = dynamic_cast<Complex*>(operand2);
	if(lhs == nullptr){
		if(rhs == nullptr){
			Real temp(operand1->getReal() - operand2->getReal());
			cout << temp << endl;
		}
		else{
			Complex temp(operand1->getReal() - operand2->getReal(), 0.0-rhs->getImaginary());
			cout << temp << endl;
		}
	}
	else{
		if(rhs == nullptr){
			Complex temp(lhs->getReal() - operand2->getReal(), 0.0-lhs->getImaginary());
			cout << temp << endl;
		}
		else{
			Complex temp(lhs->getReal() - rhs->getReal(), lhs->getImaginary() - rhs->getImaginary());
			cout << temp << endl;
		}
	}
}

/*
 * Carries out the multiplication function and directly outputs it to the console
 * Dynamically casts the input to figure out how to add the variables passed in
 * Takes in 2 real number pointers
 * if the result of the dynamic cast is a nullptr that means it is a real number
 */
void multiplication(Real* operand1, Real* operand2){
	Complex* lhs = dynamic_cast<Complex*>(operand1);
	Complex* rhs = dynamic_cast<Complex*>(operand2);
	if(lhs == nullptr){
		if(rhs == nullptr){
			Real result(operand1->getReal() * operand2->getReal());
			cout << result << endl;
		}
		else{
			Complex result(operand1->getReal() * rhs->getReal(), operand1->getReal() * rhs->getImaginary());
			cout << result << endl;
		}
	}
	else{
		if(rhs == nullptr){
			Complex result(lhs->getReal() * operand2->getReal(), lhs->getImaginary() * operand2->getReal());
			cout << result << endl;
		}
		else{
			Complex result((lhs->getReal() * rhs->getReal()) - (lhs->getImaginary() * rhs->getImaginary()),
				(lhs->getReal() * rhs->getImaginary()) + (lhs->getImaginary() * rhs->getReal()));
			cout << result << endl;
		}
	}
}

/*
 * Carries out the division function and directly outputs it to the console
 * Dynamically casts the input to figure out how to add the variables passed in
 * Takes in 2 real number pointers
 * if the result of the dynamic cast is a nullptr that means it is a real number
 */
void division(Real* operand1, Real* operand2){
	Complex* lhs = dynamic_cast<Complex*>(operand1);
	Complex* rhs = dynamic_cast<Complex*>(operand2);
	if(lhs == nullptr){
		if(rhs == nullptr){
			Real result(operand1->getReal() / operand2->getReal());
			cout << result << endl;
		}
		else{
			Complex result((operand1->getReal() * rhs->getReal()) / (rhs->getReal() * rhs->getReal() + rhs->getImaginary() * rhs->getImaginary())
				, (operand1->getReal() * -rhs->getImaginary()) / (rhs->getReal() * rhs->getReal() + rhs->getImaginary() * rhs->getImaginary()));
			cout << result << endl;
		}
	}
	else{
		if(rhs == nullptr){
			Complex result(lhs->getReal() / operand2->getReal(), lhs->getImaginary() / operand2->getReal());
			cout << result << endl;
		}
		else{
			Complex result(((lhs->getReal() * rhs->getReal()) + (lhs->getImaginary() * rhs->getImaginary()))
							/ (rhs->getReal() * rhs->getReal() + rhs->getImaginary() * rhs->getImaginary()),
							((lhs->getImaginary() * rhs->getReal()) - (lhs->getReal() * rhs->getImaginary()))
							/ (rhs->getReal() * rhs->getReal() + rhs->getImaginary() * rhs->getImaginary()));
			cout << result << endl;
		}
	}
}

/*
 * Carries out the equals function and returns true or false
 * Dynamically casts the input to figure out how to add the variables passed in
 * Takes in 2 real number pointers
 * if the result of the dynamic cast is a nullptr that means it is a real number
 */
bool equals(Real* operand1, Real* operand2){
	Complex* lhs = dynamic_cast<Complex*>(operand1);
	Complex* rhs = dynamic_cast<Complex*>(operand2);
	if(lhs == nullptr){
		if(rhs == nullptr){
			return (*operand1 == *operand2);
		}
		else{
			return (*rhs == *operand1);
		}
	}
	else{
		if(rhs == nullptr){
			return (*lhs == *operand2);
		}
		else{
			return (*lhs == *rhs);
		}
	}	
}

/*
 * Carries out the less than function and returns true or false
 * Dynamically casts the input to figure out how to add the variables passed in
 * Takes in 2 real number pointers
 * if the result of the dynamic cast is a nullptr that means it is a real number
 */
bool lessThan(Real* operand1, Real* operand2){
	Complex* lhs = dynamic_cast<Complex*>(operand1);
	Complex* rhs = dynamic_cast<Complex*>(operand2);
	if(lhs == nullptr){
		if(rhs == nullptr){
			return (*operand1 < *operand2);
		}
		else{
			return (*rhs > *operand1);
		}
	}
	else{
		if(rhs == nullptr){
			return (*lhs < *operand2);
		}
		else{
			return (*lhs < *rhs);
		}
	}
}

/*
 * Carries out the greater than function and returns true or false
 * Dynamically casts the input to figure out how to add the variables passed in
 * Takes in 2 real number pointers
 * if the result of the dynamic cast is a nullptr that means it is a real number
 */
bool greaterThan(Real* operand1, Real* operand2){
	Complex* lhs = dynamic_cast<Complex*>(operand1);
	Complex* rhs = dynamic_cast<Complex*>(operand2);
	if(lhs == nullptr){
		if(rhs == nullptr){
			return (*operand1 > *operand2);
		}
		else{
			return (*rhs < *operand1);
		}
	}
	else{
		if(rhs == nullptr){
			return (*lhs > *operand2);
		}
		else{
			return (*lhs > *rhs);
		}
	}
}