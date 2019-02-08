/************************************************
Currency Converter
Gregory Mathias
************************************************/

#include <iostream>
#include <string>

using namespace std;

void wordToLower(string &word);

double eurosToPounds(double euros);

double eurosToDollars(double euros);

double poundsToEuros(double pounds);

double poundsToDollars(double pounds);

double dollarsToEuros(double dollars);

double dollarsToPounds(double dollars);

int main() {
    string temp1, currencyFrom, currencyTo, temp2;
    double amount;

    cin >> temp1 >> amount >> currencyFrom >> temp2 >> currencyTo; //temps potentially store the words "convert" and "to"
    wordToLower(currencyFrom);
    wordToLower(currencyTo); //these are so the user doesn't need to capitalize

    //Simply checks each possible case for conversion, and outputs the conversion based on the user input
    if (currencyFrom == currencyTo) { //checks if the two currencies are the same
        cout << amount << endl;
    } else if (currencyFrom == "euros") {
        if (currencyTo == "pounds")
            cout << eurosToPounds(amount) << endl;
        else if (currencyTo == "dollars")
            cout << eurosToDollars(amount) << endl;
    } else if (currencyFrom == "pounds") {
        if (currencyTo == "euros")
            cout << poundsToEuros(amount) << endl;
        else if (currencyTo == "dollars")
            cout << poundsToDollars(amount) << endl;
    } else if (currencyFrom == "dollars") {
        if (currencyTo == "euros")
            cout << dollarsToEuros(amount) << endl;
        else if (currencyTo == "pounds")
            cout << dollarsToPounds(amount) << endl;
    }
    return 0; //Program was successful

}

//Conversion method from previous homework
void wordToLower(string &input) {
    for (int i = 0; i < input.length(); i++) {
        if (isupper(input[i]))
            input[i] = (char) (input[i] + 32);
    }
}

//These helper methods do all the conversions (as stated by their name) with simple algebra.
double eurosToPounds(double euros) {
    return ((1 / 0.8886) * euros) * 0.7446;
}

double eurosToDollars(double euros) {
    return ((1 / 0.8886) * euros);
}

double poundsToEuros(double pounds) {
    return ((1 / 0.7446) * pounds) * 0.8886;
}

double poundsToDollars(double pounds) {
    return ((1 / 0.8886) * pounds);
}

double dollarsToEuros(double dollars) {
    return dollars * 0.8886;
}

double dollarsToPounds(double dollars) {
    return dollars * 0.7446;
}
