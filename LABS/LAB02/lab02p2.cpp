#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

bool stringAllDigits(string testString) { //ensures string is all digits
    for (char i : testString) {
        if (!isdigit(i))
            return false;
    }
    return true;
}

int main() {
    RESTART:
    cout << "Enter a number between 0 and 15: ";
    string input;
    cin >> input;
    if (!stringAllDigits(input)) //ensures user input is safe
    {
        cout << "Please ensure your input is a number." << endl;
        goto RESTART;
    }

    int decimal = stoi(input); //converts input to integer
    string binary;

    int quotient = decimal / 2; //converts decimal integer to binary using the rules of / 2 and % 2
    binary += to_string(decimal % 2);
    while (quotient > 0)
    {
        binary += to_string(quotient % 2);
        quotient /= 2;
    }
    reverse(binary.begin(), binary.end());
    if (binary.length() < 4)
        for(int i = 0; i < 4 - binary.length() + 2; i++)
        {
            binary = "0" + binary;
        }
    cout << input << " in binary is " << binary << endl; //prints results nicely

    return 0;
}