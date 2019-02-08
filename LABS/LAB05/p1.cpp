/*
 * Gregory Mathias
 * This program calculates given a cost and amount, or given a percentage and amount.
 * It can also calculate a bill split.
 * */
#include <iostream>
#include <string>

using namespace std;

int main() {
	string command; //the command the user enters: calc or tip
	double amount, tip; //these are utility variables used in both commands
	int split; //used for if the user wants to split the bill
	string temp; //placeholder string for unwanted values
	char tempc; //placeholder char for unwanted values

	cin >> command;
	if (command == "calc") { //checks the command with the corresponding else if
		cin >> tempc >> amount; //gets the dollar amount, ignoring the dollar sign
		cin >> temp; //gets the next word
		if (temp == "split") { //if the next word is split, do this, otherwise if it is tip, do that
			cin >> split >> temp >> temp >> tip; //get the tip percent, skipping over the unnecessary others
			cout << "pay $" << (amount + amount * (tip / 100)) / split << endl; //print the total amount for the split that each person owes
		} else if (temp == "tip") {
			cin >> tip; //get the tip percent
			cout << "pay $" << (amount + amount * (tip / 100)) << endl; //print the total amount owed, including tip
		}
	} else if (command == "test") {
		cin >> tempc >> tip >> temp >> tempc >> amount; //get the cost of the meal (stored in tip) and the amount you want to pay (stored in amount)
		cout << "tip " << (amount - tip) / tip * 100 << "%" << endl; //print the tip percentage calculated from the amount owed and the amount you are paying
	}
	return 0;
}