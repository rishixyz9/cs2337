/*	
 *	Name: Rishabh, Vemparala
 * 	NetID = rxv200022
 */


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>

using namespace std;

double calculateArea(double arr[20][16][2], int rowIndex){
	double sum;
	int i = 1;

	sum = 1.0 * (arr[rowIndex][0][0]+arr[rowIndex][1][0]) * (arr[rowIndex][1][1] - arr[rowIndex][0][1]);

	while((arr[rowIndex][0][0] != arr[rowIndex][i][0]) || (arr[rowIndex][0][1] != arr[rowIndex][i][1])){
		sum += 1.0 * (0.0 + arr[rowIndex][i+1][0] + arr[rowIndex][i][0]) * (0.0 + arr[rowIndex][i+1][1] - arr[rowIndex][i][1]);
		++i;
	}

	return .5 * abs(sum);
}

void getCoordinates(double arr[20][16][2], string coordinates, int rowIndex){
	string coordinatePair;
	string singleCoordinate;
	stringstream spaceRemover;
	spaceRemover.str(coordinates);
	double value = 0.0;
	int col = 0;
	while(spaceRemover >> coordinatePair){
		value = stod(coordinatePair.substr(0, coordinatePair.find(',')));
		arr[rowIndex][col][0] = value;
		value = stod(coordinatePair.substr(coordinatePair.find(',') + 1));
		arr[rowIndex][col][1] = value;
		++col;
	}
}

/*
 * reads the input from the files and stores it inside its correct spot
 * takes in the fileStream, the name of the file, the 3d array, and an array of driverNames
 */

void readFile(ifstream &fileInput, string fileName, double arr[20][16][2], string driverNames[20]){
	string line;

	//uses the passed ifStream to open up a read only stream to the file with the a name of fileName
	fileInput.open(fileName);
	int i = 0;
	//if there is still valid input the file stream keeps reading the file
	if(fileInput.is_open()){
		cout << "file successfully opened" << endl;
		while(!fileInput.eof() && fileInput.good()){
			//reads until the first space in each line which returns the name of the driver on that line
			getline(fileInput, line, ' ');
			/* 
			 * puts the driver into the array in an index which does not contain anything
			 * this ensures that the drivers are being stored in the order that they were read
			 * by the file stream
			 */
			for(int i = 0; i < 20; ++i){
				if(driverNames[i].empty()){
					driverNames[i] = line;
					break;
				}
			}

			/* 
			 * reads the remaining text on the line that the file already read and stores it in the line variable
			 * all that this should return is the coordinates in string format with the whitespace and character positions
			 * preserved ie: 4,0 1,3 1,0 4,0
			 */ 
			getline(fileInput, line);

			//passes the line with the coordinates into the getCoordinates method with then stores 
			//the coordinates in their correct spots on row i in the 3d array 
			getCoordinates(arr, line, i);

			++i;
		}
	}
	else{
		cout << "unable to open the file" << endl;
	}
	fileInput.close();
}


int main(){

	//creates the necessary arrays and variables
	string fileName;
	string driverNames[20];
	double coordinateArray[20][16][2] = {0.0};

	ifstream fileInput;

	//asks for the fileName so it can then be passed to the readfile method in a few lines
	cout << "What is the name of the file" << endl << "> ";
	cin >> fileName;

	/*
	 * uses the readfile function and the input from the previous 2 lines of code to store the input from the files
	 * stores the integer input into the 3d array coordinateArray 
	 * the first dimension of the 3d array contains a row of coordinates stored in column and x/y format (maximum of 20 rows)
	 * the second dimension of the 3d array contains a column coordinate pairs stored in x/y format (maximum 16 coordinate pairs)
	 * the third dimension of the array contains the x/y coordinates themselves (maximum 2 coordinates)
	 * stores the string input into the array driverNames since the string input is simply the name of the drivers
	 */ 

	readFile(fileInput, fileName, coordinateArray, driverNames);

	/* 
	 * the loop iterates as many times as there is a driver name in the array
	 * ie: if there is not a driver name in an index, the loop breaks and stops
	 * calculating and outputting the areas in order to avoid incorrect output
	 * uses the calculateArea method to calculate the area for each driver
	 * uses the results from the method to output the driver and their respective areas covered
	 * output has 2 decimal places of precision since some areas have floating points, this is done to preserve accuracy when output
	 */
	for(int l = 0; l < 20; ++l){
		if(driverNames[l].empty()){
			break;
		}
		double area = 0.0;	
		area = calculateArea(coordinateArray, l);
		cout << driverNames[l] << "\t";
		cout << fixed << setprecision(2) << area << endl;
	}

	return 0;
}