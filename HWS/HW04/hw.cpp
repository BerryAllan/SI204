#include <iostream>
#include <string>

using namespace std;

string wordToLower(string input) {
    string output;
    for (char i : input) {
        output += (char)(i + 32);
    }
    return output;
}

//ideas from: https://www.geeksforgeeks.org/conversion-whole-string-uppercase-lowercase-using-stl-c/
int main() {
    cout << "Input a 3-letter word in uppercase letters: ";
    string word;
    cin >> word;
    word = wordToLower(word);
    cout << "Output: " << word << endl;
    return 0;
}