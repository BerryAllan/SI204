/*
 * Gregory Mathias
 * This program, given a text file in a specific format giving tax
 * bracket details, outputs to the user their bracket and how much
 * taxes they owe.
 * */
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
	char tempc; //placeholder char
	double percent, beginbracket, endbracket; //the tax percentage, the start and end of the tax bracket
	string filename, temp; //the filename and a placeholde string
	int income; //the user's income amount

	cin >> filename >> tempc >> income; //get the tax bracket file and the user's income amount, ignoring the dollar sign

	ifstream fin(filename);

	if(!fin) //if the file doesn't exist, print error and exit
	{
		cout << "File not found!" << endl;
		return 1;
	}

	while (fin >> percent >> tempc >> tempc >> beginbracket >> temp >> tempc >> endbracket) { //this gets each line, assigning the correct values to percent, beginbrackt, and
		// endbrack, all ignoring the unecessary string and characters
		if (beginbracket < income && income < endbracket) { //if the user's income falls into the current bracket
			cout << percent << "% This is you! You owe $" << (income * (percent / 100)) << endl; //print the taxes they owe pretty
		} else { //otherwise ignore it, print a message that the bracket is not yours
			cout << percent << "% This is not you!" << endl;
		}
	}
	return 0;

}