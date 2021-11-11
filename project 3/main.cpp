#include "Node.h"
#include "Tree.h"
#include "Game.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

//g++ main.cpp Node.cpp Tree.cpp Game.cpp -Wall -Wextra -Wuninitialized -pedantic-errors -Wconversion


/*
 * printTreeASC method prints the binary tree in ascending order
 * takes in a node parameter as the starting point
 */
void printTreeASC(Node<Game> *node){
	if (node == nullptr){ 
		return;
	}
	printTreeASC(node->getLeft());
	cout << node << endl;
	printTreeASC(node->getRight());
}

/*
 * printTreeASC method prints the binary tree in descending order
 * takes in a node parameter as the starting point
 */
void printTreeDES(Node<Game> *node){
	if (node == nullptr){ 
		return;
	}
	printTreeDES(node->getRight());
	cout << node << endl;
	printTreeDES(node->getLeft());
}


/*
 * readfile1 method reads the file containing the game data
 * opens the file from the string parameter filename and
 * stores all the input into the Tree parameter which is gameTree
 */
void readfile1(Tree<Game> &gameTree, string &fileName){
    ifstream fileInput;
    fileInput.open(fileName);
    if(fileInput.is_open()){
        cout << "file 1 successfully opened" << endl;
        while(!fileInput.eof() && fileInput.good()){
        	string temp;
        	string gameName;
        	string gameScore;
        	string gameInitials;
        	string gamePlays;
        	//<name>, <high_score>, <initials>, <plays>, $<revenue><newline>
            getline(fileInput, gameName,',');
            getline(fileInput, temp, ' ');
            getline(fileInput, gameScore, ',');
            getline(fileInput, temp, ' ');
            getline(fileInput, gameInitials,',');
            getline(fileInput, temp, ' ');
            getline(fileInput, gamePlays, ',');
            getline(fileInput, temp);
            try{
            	stoi(gameScore);
            }
            catch(invalid_argument&){
            	return;
            }

            Game toInsert(gameName, stoi(gameScore), gameInitials, stoi(gamePlays));
            Node<Game> *node = new Node<Game>(toInsert); //Dynamically create a new node for every game read in the database file
            gameTree.append(node);
        }
    }
    fileInput.close();
}

/*
 * readfile2 method reads the file containing the commands
 * opens the file from the string parameter filename and
 * performs all the commands
 */
void readfile2(Tree<Game> &gameTree, string &fileName){
    ifstream fileInput;
    fileInput.open(fileName);
    if(fileInput.is_open() && fileInput.peek()!=std::ifstream::traits_type::eof()){
        cout << "file 2 successfully opened" << endl;
        cout << fixed << setprecision(2);
        while(!fileInput.eof() && fileInput.good()){
        	int commandNum;
        	fileInput >> commandNum;
        	//command to add a record
        	if(commandNum == 1){
	        	string temp;
	        	string gameName;
	        	string gameScore;
	        	string gameInitials;
	        	string gamePlays;
	        	getline(fileInput, temp, '\"');
	        	getline(fileInput, gameName,'\"');
	        	getline(fileInput, temp, ' ');
	            getline(fileInput, gameScore, ' ');
	            getline(fileInput, gameInitials,' ');
	            getline(fileInput, gamePlays, ' ');
	            getline(fileInput, temp);
                Game toInsert(gameName, stoi(gameScore), gameInitials, stoi(gamePlays));
            	Node<Game> *node = new Node<Game>(toInsert);
            	gameTree.append(node);
            	cout << "RECORD ADDED" << endl;
            	cout << "Name: " << gameName << endl;
            	cout << "High Score: " << gameScore << endl;
            	cout << "Initials: " << gameInitials << endl;
            	cout << "Plays: " << gamePlays << endl;
            	cout << "Revenue: $" << (stoi(gamePlays)*0.25) << endl;
            	cout << endl << endl; 
        	}
        	//command to search for a record
        	else if(commandNum == 2){
        		string nameSearch;
        		string temp;
        		getline(fileInput, temp, ' ');
        		getline(fileInput, nameSearch, '\n');
        		Game toSearch(nameSearch, 0, "", 0);
        		Node<Game> *searchNode = new Node<Game>(toSearch);
        		vector<Node<Game>*> searchResult = gameTree.search(searchNode);
        		//for every result found it prints the result
        		if(!searchResult.empty()){
        			//Node<Game>* x : searchResult
	         		for (int i=0; i < searchResult.size(); i++){
	        			cout << searchResult[i]->getVal().getName() << " FOUND" << endl;
		            	cout << "High Score: " << searchResult[i]->getVal().getHighScore() << endl;
		            	cout << "Initials: " << searchResult[i]->getVal().getInitials() << endl;
		            	cout << "Plays: " << searchResult[i]->getVal().getPlays() << endl;
		            	cout << "Revenue: $" << (searchResult[i]->getVal().getPlays()*0.25) << endl;
		            	cout << endl << endl;
	        		}       			
        		}
        		else{
        			cout << nameSearch << " NOT FOUND" << endl;
        			cout << endl << endl;
        		}
        		delete(searchNode);
        	}
        	//command to search for a record
        	else if(commandNum==3){
	    	    string nameSearch;
	    	    int fieldNum;
	    	    string newVal;
	    		string temp;
	    		string field;
	        	getline(fileInput, temp, '\"');
	        	getline(fileInput, nameSearch,'\"');
	        	fileInput >> fieldNum;
	        	fileInput >> newVal;
	        	Game toSearch(nameSearch, 0, "", 0);
	    		Node<Game> *searchNode = new Node<Game>(toSearch);
	    		Node<Game> *searchResult = gameTree.search(searchNode)[0];
	        	if(fieldNum==1){
	        		Game replace = searchResult->getVal();
	        		replace.setScore(stoi(newVal));
	        		searchResult->setVal(replace);
	        		field = "high score"; 
	        	}
	        	else if(fieldNum==2){
	        		Game replace = searchResult->getVal();
	        		replace.setInitials(newVal);
	        		searchResult->setVal(replace);
	        		field = "initials";
	        	}
	        	else{
	        		Game replace = searchResult->getVal();
	        		replace.setPlays(stoi(newVal));
	        		searchResult->setVal(replace);
	        		field = "plays";
	        	}
	        	cout << nameSearch << " UPDATED" << endl;
	        	cout << "UPDATE TO "<< field << " - VALUE " << newVal << endl;
	        	cout << "High Score: " << searchResult->getVal().getHighScore() << endl;
            	cout << "Initials: " << searchResult->getVal().getInitials() << endl;
            	cout << "Plays: " << searchResult->getVal().getPlays() << endl;
            	cout << "Revenue: $" << (searchResult->getVal().getPlays()*0.25) << endl;
	        	cout << endl << endl;
	        	delete(searchNode);
        	}
        	//command to delete a record
        	//creates dummy node to search for and delete
        	else if(commandNum==4){
        		string nameSearch;
	    	    string newVal;
	    		string temp;
	        	getline(fileInput, temp, ' ');
	        	getline(fileInput, nameSearch,'\n');
	        	Game toSearch(nameSearch, 0, "", 0);
	    		Node<Game> *searchNode = new Node<Game>(toSearch);
	    		Node<Game> *removed = gameTree.removeNode(searchNode);
			    cout << "RECORD DELETED" << endl;
			    cout << "Name: " << nameSearch << endl;
	        	cout << "High Score: " << removed->getVal().getHighScore() << endl;
            	cout << "Initials: " << removed->getVal().getInitials() << endl;
            	cout << "Plays: " << removed->getVal().getPlays() << endl;
            	cout << "Revenue: $" << (removed->getVal().getPlays()*0.25) << endl;
            	cout << endl << endl;
	    		delete(searchNode);	
        	}
        	//command to sort the tree
        	//simply inorder traverses the tree
        	else if(commandNum==5){
        		string sortMethod;
        		fileInput >> sortMethod;
        		if(sortMethod=="asc"){
        			cout << "RECORDS SORTED ASCENDING" << endl;
        			printTreeASC(gameTree.getTree());
        		}
        		else{
        			cout << "RECORDS SORTED DESCENDING" << endl;
        			printTreeDES(gameTree.getTree());
        		}
        		cout << endl << endl;
        		getline(fileInput, sortMethod);
        	}
        	else{
        		return;
        	}
        	commandNum=0;

        }

    }
    fileInput.close();
}

/*
 *	Writes the tree to the file from a starting node
 *	Uses breadth first traversal
 * 	This is the helper method
 */
void writefile(Node<Game> *node, ofstream& fileOutput){
	if(!node){
		return;
	}
	queue<Node<Game>*> q;
	q.push(node);
	while(!q.empty()){
		Node<Game>* n = q.front();
		fileOutput << n << endl;
		q.pop();
		if(n->getLeft()){
		  q.push(n->getLeft());
		}
		if(n->getRight()){
		  q.push(n->getRight());
		}
	}
}

/*
 *	Writes the tree to the file from a starting node
 *	Uses breadth first traversal
 * 	Calls a helper method to traverse and write to the tree
 */
void writefile(Tree<Game> gameTree){
	ofstream fileOutput;
	fileOutput.open("cidercade.dat");
	writefile(gameTree.getTree(), fileOutput);
}	

int main(){
	Tree<Game> gameTree;
	string fileName;
	cout << "database file" << endl;
	cin >> fileName;
	readfile1(gameTree, fileName);
	fileName = "";
	cout << "commands file" << endl;
	cin >> fileName;
	readfile2(gameTree, fileName);
	printTreeASC(gameTree.getTree());
	writefile(gameTree);

	cout << endl << endl;

	writefile(gameTree.getTree());

	return 0;
}