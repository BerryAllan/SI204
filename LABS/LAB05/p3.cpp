/*
 * Gregory Mathias
 * This program is a little game for the user. The user enters a board file,
 * then a number corresponding to a column on the board. If the column is clear
 * of death traps, the user won. Otherwise, the program tells them where they died.
 * */
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct board { //this struct stores the underlying data structure of a 2d vector containing characters
	vector<vector<char>> board; //the characters
	int width; //the width and height of the board
	int height;

	vector<char>& operator[](int index) { //makes accessing the characters a simple double bracket call
		return board[index];
	}
};

board constructBoard(ifstream& fin); //a method that constructs a board given filestream

int main() {
	string filename;
	cin >> filename;
	ifstream fin(filename);
	if (!fin) { //get the user's board from the filename they enter; if it doesn't exist, print error message and exit
		cout << "File not found!" << endl;
		return 1;
	}

	board mainBoard = constructBoard(fin); //this is the board that the user is playing on
	cout << "Enter position between 1 and " << mainBoard.width << ": ";
	int userPos;
	cin >> userPos; //gets the user's guess for the clear path through the board
	if (userPos > mainBoard.width || userPos < 1) { //if the user enters an incorrect space on the board, give error message and exit
		cout << "Invalid position!" << endl;
		return 0;
	}
	userPos--; //subtract one from the userPos since array accessors count starting from 0
	for (int i = 0; i < mainBoard.height; i++) { //loop through each row of the board
		if (mainBoard[i][userPos] == 'X') { //if the column in the current row contains a death trap ('X'), print where they died and exit
			cout << "You died on step " << (i + 1) << endl;
			return 0;
		}
	}
	cout << "You survived!" << endl; //if the user makes it through the whole board, they survived; congratulate them,
}

board constructBoard(ifstream& fin) {
	string temp; //placeholder string while reading input
	int width, height = 0;
	fin >> temp >> temp >> width; //gets the board width from the file, ignoring unecessary characters
	string line; //temporary line holder
	vector<vector<char>> mainBoard; //this will be the underlying data structure for our board
	while (getline(fin, line)) { //reads the file line by line
		if (line[0] != '@') //if the line doesn't start with an @ sign, it doesn't belong to the board
			continue;
		line = line.substr(1, width); //remove the @ signs at the beginning and end of each line
		vector<char> row; //this is a row of characters
		for (char c : line) { //for every character in the line, add it to the row vector
			row.push_back(c);
		}
		mainBoard.push_back(row); //add the row vector to the board vector, after it has finished populating
		height++; //height is determined by the number of lines in the file
	}

	return {mainBoard, width, height}; //return the board struct with its necessary data values
}