#include "Node.h"
#include "Driver.h"
#include "LinkedList.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

//g++ main.cpp Node.cpp Driver.cpp LinkedList.cpp -Wall -Wextra -Wuninitialized -pedantic-errors -Wconversion 

/* 
 * Rishabh Vemparala
 * rxv200022
 * CS 2337.02
 */

//Function prototypes of functions defined below main
void readfile1(LinkedList<Driver>&, string&);
void readfile2(LinkedList<Driver>&, string&);
void search(LinkedList<Driver>&, string&);
bool validName(string&);
bool validLine(string&);
double calculateArea(string);

int main(){ 
    LinkedList<Driver> list;    //LinkedList object to be used for the duration of the program (only 1 needed)
    string fileName;    //variable that stores the file name
    cout << "What is the name of the file containing the driver data" << "\n" 
         << "> ";
    cin >> fileName;    //stores the name of the file containing the driver data
    readfile1(list, fileName);  //opens and reads the file and stores it into the list
    cout << fixed << setprecision(2);
    cout << list << endl;   //outputs the linkedlist
    cout << "What is the name of the file containing the commands" << "\n" 
     << "> ";
    cin >> fileName;    //stores the name of the file containing the commands
    readfile2(list, fileName);  //opens and reads the file and ouputs the results of the commands
    return 0;
}  

/*
 * Search method that outputs the result of a search operation
 * takes in the linkedlist as a parameter
 * takes in a string of the item to be searched as searchItem
 */
void search(LinkedList<Driver> &list, string &searchItem){
    Node<Driver>*curr = list.getHead();
    //if the search item is a double, looks for the matching area in the linkedlist
    try{
        stod(searchItem);
        while(curr != NULL){
            if(abs(stod(searchItem)-curr->getData()->getArea()) < 0.0001){
                cout << curr->getData()->getName() << " " << curr->getData()->getArea() << endl;
                return;
            }
            curr = curr->getNext();
        }
        cout << searchItem << " not found\n"<<endl; 
    }
    //if the search item is a string, looks for the matching name in the linkedlist
    catch(invalid_argument&){
        while(curr != NULL){
            if(searchItem == curr->getData()->getName()){
                cout << curr->getData()->getName() << " " << curr->getData()->getArea() << endl;
                return;
            }
            curr = curr->getNext();
        }
        cout << searchItem << " not found\n"<<endl;
    }    
}

/*
 * validName method returns true if the name is valid
 * takes in a string parameter of the name to be checked as name
 */
bool validName(string &name){
    string const VALID_CHARACTERS = "-\' ";
    for(int  i=0; i < (int)name.size(); i++){ 
        if(!isalnum(name.at(i))){
            if(VALID_CHARACTERS.find(name.at(i)) == string::npos){ //If the name contains any invalid characters it returns false
                return false;
            }         
        }
    }
    return true;
}

/*
 * validLine method returns true if the line is valid
 * takes in a string parameter of the line to be checked as line
 */
bool validLine(string &line){
    stringstream ss;
    string temp;
    string first;
    ss.str(line);
    while(ss >> temp){
        if(first.empty()){
            first = temp;
        }
        if(temp.at(0) == ',' || temp.back() == ',' || temp.find(',') == string::npos){
            return false;   //if the coordinate does not have something on either side it returns false
        }
        else{
            for(int i=0; i < (int) temp.size(); i++){
                if(!isdigit(temp.at(i))){
                    if(isalpha(temp.at(i))){
                        return false;   //if there is a letter in the coordinate pair return false
                    }
                    string VALID = ".-,";
                    if(VALID.find(temp.at(i)) == string::npos){
                        return false;   //if there is not a valid character in the coordinate pair return false
                    }
                    if(VALID.find(temp.at(i)) != string::npos){
                        if(temp.substr(0,temp.find(',')).back() == '.' || temp.substr(temp.find(',')+1).back() == '.'){
                            return false;   //if there is a decimal at the end or beginning of the coordinate pair return false
                        }
                        int counter = 0;
                        for(int i=0; i < (int) temp.substr(0,temp.find(',')).size(); i++){
                            if(temp.substr(0,temp.find(','))[i] == '.'){
                                counter++;
                            }
                            if(counter >= 2){
                                return false;   //if there is more than 2 decimal in the left coordinate return false
                            }
                        }
                        counter = 0;
                        for(int i=0; i < (int) temp.substr(temp.find(',')+1).size(); i++){
                            if(temp.substr(temp.find(',')+1)[i] == '.'){
                                counter++;
                            }
                            if(counter >= 2){
                                return false;   //if there is more than 2 decimal in the left coordinate return false
                            }
                        }   
                    }
                }
            }
        }
        try{
            stod(temp);
        }
        catch(std::invalid_argument&){
            return false;   //if the coordinate can't be parsed into an double return false
        }        
    }
    if(first != temp){
        return false;   //if the last coordinate is not the same as the first return false
    }
    return true;    //if none of the things were caught return true
}

/*
 * validCommand method returns true if the command is valid
 * takes in a string parameter of the line to be checked as line
 */
bool validCommand(string &line){
    if(line.find("sort") != string::npos){
        if(line.find("driver") != string::npos  || line.find("area") != string::npos){
            if(line.find("asc") != string::npos  || line.find("des") != string::npos){
                return true;
            }
        }
        return false;   //if sort is found in the line, then there must be either driver/area or asc/dec somewhere in the line
    }
    else{
        try{
            stod(line); //if the line is an integer
            for(int i=0; i < (int) line.size(); i++){
                if(isalpha(line.at(i)) || !isdigit(line.at(i))){
                    if(line.at(i) != '.'){
                        return false;   //if the digit is not alphanumeric then if it's not a decimal return false                        
                    }

                }
            }
            return true;    //return true if nothing was invalid
        }
        catch(std::invalid_argument&){
            return validName(line); //if unable to parse into an integer, return result the valid name function
        }    
    }
}

/*
 * readfile1 method reads the file containing the driver data
 * opens the file from the string parameter filename and
 * stores all the input into the linkedlist parameter which is list
 * ignores invalid lines
 */
void readfile1(LinkedList<Driver> &list, string &fileName){
    string line;
    string name = "";
    ifstream fileInput;
    fileInput.open(fileName);
    if(fileInput.is_open()){
        cout << "file 1 successfully opened" << endl;
        while(!fileInput.eof() && fileInput.good()){
            stringstream ss;
            getline(fileInput, line);
            ss.str(line);
            string temp;
            int spaces = 0;
            while(temp.find(",") == string::npos){
                getline(ss, temp, ' ');
                spaces+=1;
            }
            ss.str(line);
            while(spaces > 1){
                getline(ss, temp, ' ');
                name += temp + " ";
                spaces-=1;
            }
            name = name.substr(0,name.size()-1);
            getline(ss, temp);
            line = temp;
            if(validName(name) && validLine(line)){
                Driver tempDriver(name);
                tempDriver.setArea(calculateArea(line));
                Node<Driver> *node = new Node<Driver>(tempDriver);
                list.append(node);  
            }
            name = "";
        }
    }
    fileInput.close();
}

/*
 * readfile2 method reads the file containing the commands
 * opens the file from the string parameter filename and
 * performs all the valid commands in the file and outputs their results
 * ignore invalid commands
 */
void readfile2(LinkedList<Driver> &list, string &fileName){
    string line;
    ifstream fileInput;
    fileInput.open(fileName);
    if(fileInput.is_open()){
        cout << "file 2 successfully opened" << endl;
        while(!fileInput.eof() && fileInput.good()){
            getline(fileInput, line);
            if(validCommand(line)){
                if(line.find("sort") != string::npos){
                    list.getHead()->getData()->setCompare("area");
                    if(line.find("driver") != string::npos){
                        list.getHead()->getData()->setCompare("name");
                    }
                    if(line.find("asc") != string::npos){
                        list.sort("asc");
                    }
                    else{
                        list.sort("des");
                    }
                    cout << list << endl;
                }
                else{
                    search(list, line);
                } 
            }
  
        }
    }
    fileInput.close();
}

/*
 * helper function for readfile1
 * calculates the areas so that they can be used to create a driver object
 * takes in the line as a string variable line
 * reads the line
 */
double calculateArea(string line){
    double sum = 0.0;
    double x1,x2,y1,y2 = 0.0;
    string temp;
    vector<string> coordinates;
    stringstream spaceRemover(line);
    while(getline(spaceRemover,temp,' ')){
        coordinates.push_back(temp);
    }
    x1 = stod(coordinates[0].substr(0, coordinates[0].find(',')));
    y1 = stod(coordinates[0].substr(coordinates[0].find(',') + 1));
    x2 = stod(coordinates[1].substr(0, coordinates[1].find(',')));
    y2 = stod(coordinates[1].substr(coordinates[1].find(',') + 1));
    sum = (x1+x2) * (y2-y1);
    int i = 1;
    while(coordinates[0] != coordinates[i]){
        x1 = stod(coordinates[i].substr(0, coordinates[i].find(',')));
        y1 = stod(coordinates[i].substr(coordinates[i].find(',') + 1));
        x2 = stod(coordinates[i+1].substr(0, coordinates[i+1].find(',')));
        y2 = stod(coordinates[i+1].substr(coordinates[i+1].find(',') + 1));
        sum += (x1+x2) * (y2-y1);
        ++i;
    }
    return .5 * abs(sum);
}

