#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <cctype> //includes really slow compilation haha

using namespace std;

//wrote this method myself; got some ideas from StackOverflow
vector<string> split_string(const string &splittable,
                           char splitter = ' ') { //splits string into vector by defined character that defaults to ' '
    vector<string> strings;
    stringstream stream(splittable);

    string s;
    while (getline(stream, s, splitter)) {
        strings.push_back(s);
    }
    return strings;
}

bool stringAllDigits(string testString) { //ensures string is all digits
    for (char i : testString) {
        if (!isdigit(i))
            return false;
    }
    return true;
}

int main() {

    string length1;
    double lengths[2] = {}; //should only have 2 lengths anyways
    double difference;
    int counter = 0;

    RESTART: //just in case; nicer for the user not to have the program crash on caught errors

    //cout << "Enter two lengths in feet and inches (separated with a space) in the format \" x' y'' \":" << endl;
    cout << "Enter two lengths in feet and inches (larger first!)" << endl;
    while (getline(cin, length1) && counter < 1) {
        double feet1, feet2, inches1, inches2;
        vector<string> splitLine = split_string(length1);
        if (splitLine.size() != 4) {
            cout << "Illegal input! Ensure there is a space between your feet and inches." << endl;
            goto RESTART;
        }

        /*for (int i = 0; i < splitLine.size(); i++) {
            string str = splitLine[i];
            str.erase(std::remove(str.begin(), str.end(), '\''), str.end());
            splitLine[i] = str;
        }*/ //Not really necessary; std::stod ignores these characters anyways

        if (!isdigit(splitLine[0].at(0)) || !isdigit(splitLine[1].at(
                0)) //ensures all input begins with numbers, has only numbers, except for the last characters, which have to be ' for feet and '' for inches
            || splitLine[0].at(splitLine[0].length() - 1) != '\''
            || splitLine[1].at(splitLine[1].length() - 1) != '\''
            || splitLine[1].at(splitLine[1].length() - 2) != '\''
            || !stringAllDigits(splitLine[0].substr(0, splitLine[0].length() - 1))
            || !stringAllDigits(splitLine[1].substr(0, splitLine[1].length() - 2)) ||
            !isdigit(splitLine[2].at(0)) || !isdigit(splitLine[3].at(
                0)) //ensures all input begins with numbers, has only numbers, except for the last characters, which have to be ' for feet and '' for inches
            || splitLine[2].at(splitLine[2].length() - 1) != '\''
            || splitLine[3].at(splitLine[3].length() - 1) != '\''
            || splitLine[3].at(splitLine[3].length() - 2) != '\''
            || !stringAllDigits(splitLine[2].substr(0, splitLine[2].length() - 1))
            || !stringAllDigits(splitLine[3].substr(0, splitLine[3].length() - 2))) {
            cout << "Please enter a valid input; no letters or extra spaces." << endl;
            goto RESTART;
        }
        try {
            feet1 = stod(splitLine[0]);
            inches1 = stod(splitLine[1]);
            feet2 = stod(splitLine[2]);
            inches2 = stod(splitLine[3]);
        }
        catch (int e) { //not familiar with c++ catches; hopefully if anything escapes the check above double parsing will throw something and we can restart
            cout << "Please enter a valid input; no letters or extra spaces." << endl;
            goto RESTART;
        }

        lengths[0] = (floor(feet1)) * 12 + (feet1 - floor(feet1)) * 12 +
                     inches1; //converts entire length to inches, ensuring any decimals in the feet are account for
        lengths[1] = (floor(feet2)) * 12 + (feet2 - floor(feet2)) * 12 +
                     inches2; //converts entire length to inches, ensuring any decimals in the feet are account for
        counter++;
        if (counter >= 1) break;
    }
    difference = abs(lengths[0] -
                     lengths[1]); //calculates inches total difference; user can enter any value first, larger or smaller
    int feetDiff = abs((int) (difference / 12.0)); //calculates feet difference
    double inchesDiff = abs((int) floor(difference) % (int) 12.0 +
                            (difference - (floor(difference)))); //calculates inches difference without feet
    /*cout << "The difference in inches between the two lengths is: " << difference << "'' " << endl;
    cout << "The difference in feet and inches between the two lengths is: " << feetDiff << "' " << inchesDiff << "''"
         << endl;*/ //fancy printing
    cout << "Difference is " << feetDiff << "' " << inchesDiff << "''" << endl;

    return 0; //it oughtta
}

