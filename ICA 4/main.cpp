/*
 *	Rishabh Vemparala (rxv200022)
 *  Joe Larock (jbl180002)
 * 	Rithvik Senthilkumar (RXS200105)
 */

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <list>

using namespace std;

//g++ main.cpp -Wall -Wextra -Wuninitialized -pedantic-errors -Wconversion 

int getOrder(char temp){
	if(temp == '^'){
		return 3;
	}
	if(temp == '*' || temp == '/'){
		return 2;
	}
	if(temp == '+' || temp == '-'){
		return 1;
	}
	return 0;
}

int main(){

	string infix;
	string postfix="";
	string fileName;
	list<char> operators;
	// ^  = 3
	// */ = 2
	// +- = 1
	// () = 0

	cout << "type the file name" << endl;
	cout << "> ";
	getline(cin, fileName);
	ifstream fileInput(fileName);
	ofstream fileOutput("postfix.txt");
	if(fileInput.is_open()){
		cout << "file successfully opened" << endl;
		while(!fileInput.eof() && fileInput.good()){
			getline(fileInput, infix);
			stringstream ss(infix);
			char temp;
			while(ss >> temp){
				try{
					string newString(1,temp);
					stoi(newString);
					postfix += temp;
				}
				catch(invalid_argument&){
					if(temp == '('){
						operators.push_front('(');				
					}
					else if(temp == ')'){
						while(operators.front() != '('){
							postfix += operators.front();			
							operators.pop_front();
						}
						operators.pop_front();
					}
					else{
						int order = getOrder(temp);
						while(!operators.empty() && order <= getOrder(operators.front())){
							postfix += operators.front();
							operators.pop_front();
						}
						operators.push_front(temp);
					}
				}
			}
			while(!operators.empty()){
				postfix += operators.front();			
				operators.pop_front();
			}

			fileOutput << postfix << endl;
			postfix = "";
		}
	}

	return 0;
}