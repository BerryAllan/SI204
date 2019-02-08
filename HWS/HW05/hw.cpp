#include <iostream>
#include <string>

using namespace std;

bool stringAllDigits(string testString) { //ensures string is all digits
    for (char i : testString) {
        if (!isdigit(i))
            return false;
    }
    return true;
}

//ideas from: https://www.geeksforgeeks.org/conversion-whole-string-uppercase-lowercase-using-stl-c/
int main()
{
    RESTART:
    cout << "Enter year: ";
    string year;
    cin >> year;
    if (!stringAllDigits(year))
    {
        cout << endl << "Invalid input; please try again." << endl;
        goto RESTART;
    }
    int intYear = stoi(year);
    bool isLeapYear = intYear % 4 == 0 && (intYear % 100 != 0 || intYear % 400 == 0);
    string isOrIsnt = isLeapYear ? "Is" : "Is Not";
    cout << isOrIsnt << " Leap Year" << endl;
    return 0;
}