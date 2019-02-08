#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

string toBinary(int decimal) { //method to convert a decimal to binary
    string binary;
    int quotient = decimal / 2;
    binary += to_string(decimal % 2);
    while (quotient > 0) {
        binary += to_string(quotient % 2);
        quotient /= 2;
    }
    if (binary.length() < 3) //ensures string length is equal to three
        for(int i = 0; i < 3 -binary.length() + 1; i++)
        {
            binary += "0";
        }
    reverse(binary.begin(), binary.end());
    return binary;
}

int main() {
    RESTART:
    cout << "Permissions: ";
    string input;
    cin >> input;
    if (input.length() != 3) { //input needs to be 3 characters long, only
        cout << "Please enter a valid permissions number." << endl;
        goto RESTART;
    }
    for (char i : input) //ensures that an invalid permissions number is not given eg: 849
        if (!(i - '0' >= 0 && i - '0' <= 7)) {
            cout << "Please enter a valid permissions number." << endl;
            goto RESTART;
        }

    string categories[3] = {"User", "Group", "Other"};
    string rwe[3] = {"read", "write", "execute"}; //helpful arrays for output
    int permissions[3][3]; //eg: permissions[1][2] = 1 is "group execute = true"; array stores permissions
    for(int i = 0; i < input.length(); i++)
    {
        string binary = toBinary(input.at(i) - '0');
        for(int j = 0; j < binary.length(); j++)
        {
            permissions[i][j] = binary.at(j) != '1' ? 0 : 1; //interprets the binary and determines the permissions based off of the 0s and 1s
        }
    }

    cout << endl;
    for(int i = 0; i < sizeof(permissions) / sizeof(permissions[0]); i++) //loops through array; unfortunately sizeof gives the number of bytes allocated, so we need to divide by the number of bytes allocated per element of the array to get the array's true length
    {
        cout << categories[i] << ":" << endl;
        for(int j = 0; j < sizeof(permissions[i]) / sizeof(permissions[0][0]); j++)
        {
            cout << rwe[j] << "\t" << permissions[i][j] << endl;
        }
        cout << endl;
    }

    return 0;
}