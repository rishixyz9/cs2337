#include "Document.h"
#include "File.h"
#include "EMail.h"
#include <string>
#include <iostream>


/*
 * Rishabh Vemparala rxv200022
 * Collin Tran ctt200001	
 */
using namespace std;


bool containsKeyword(const Document& doc, string keyword){
	size_t found = doc.getDoc().find(keyword);
	if(found != string::npos){
		return true;
	}
	return false;
}

int main(){
	Document doc("hello im bob");
	EMail myEmail("hello im bob", "bob", "joe", "business");
	File myFile("hello im bob", "c:/", "bob.txt");

	cout << containsKeyword(doc, "hello") << endl;
	cout << containsKeyword(myEmail, "joe") << endl;
	cout << containsKeyword(myFile, "bob") << endl;

	cout << doc << endl;
	cout << endl;
	cout << myEmail << endl;
	cout << endl;
	cout << myFile << endl;


	return 0;
}