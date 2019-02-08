#include<iostream>
#include <cmath>

using namespace std;

int main() {
	//Get the margin and size from the user
	int margin, size;
	cout << "Enter margin (greater than 0): ";
	cin >> margin;
	cout << endl << "Enter size (greater than 3): ";
	cin >> size;
	cout << endl;

	//If the size is less than three, we need to quit. No error message was specified
	if (size < 3)
		return 0;

	for (int row = 0; row < margin * 2 + size; row++) {
		for (int col = 0; col < margin * 2 + size; col++) {
			if (row < margin || row >= margin + size) { //If the current row is belongs to the top or bottom margin, just print out a row of periods.
				cout << '.';
			} else if (row == margin || row == margin + size - 1) { //If the current row is one immediately below or above the top and bottom margins, respectively
				if (col < margin || col >= margin + size) //print the left and right margins if the current column is less than margin or greater than margin + size
					cout << '.';
				else //Otherwise, just print the letter Z for the top and bottom of the larger "Z"
					cout << 'Z';
			} else { //If the row is in the middle of the large letter "Z"
				if (col == abs(size + margin * 2 - row) - 1) { //Only print the letter Z if the current column is equal to the absolute value of the entire row length - the
					// current row, minus one (the loops start at 0)
					cout << 'Z';
				} else //Otherwise, just print the period
					cout << '.';
			}
		}
		cout << endl; //End the line every row.
	}
}