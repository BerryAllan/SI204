#include <iostream>
#include <cmath>
#include <string>

using namespace std;

bool stringAllBinary(string testString) { //ensures string is all 1s and 0s
    for (char i : testString) {
        if (i != '0' && i != '1')
            return false;
    }
    return true;
}

int main() {
    RESTART:
    cout << "Enter a 4-bit binary number: ";
    string input;
    cin >> input; //gets user input for a binary number

    if (!stringAllBinary(input)) {
        cout << "Please ensure your input is only 0s and 1s." << endl;
        goto RESTART;
    }

    int sum = 0;
    unsigned long counter = input.length();
    for (char i : input) {
        counter--;
        sum += (i - '0') * (pow(2,
                                counter)); //converts each 0 and one to an integer, and based on its position (counter), it raises 2 to counter and adds that value to the overall sum
    }
    cout << "In decimal " << input << " = " << sum << endl; //prints pretty

    return 0;
}