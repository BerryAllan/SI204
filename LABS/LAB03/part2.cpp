/************************************************
Currency Converter (including US and Canada $$)
Gregory Mathias
************************************************/

#include <iostream>
#include <string>

using namespace std;

void wordToLower(string &word);

double eurosToPounds(double euros);

double eurosToDollars(double euros);

double eurosToCanadaDollars(double euros);

double poundsToEuros(double pounds);

double poundsToDollars(double pounds);

double poundsToCanadaDollars(double pounds);

double dollarsToEuros(double dollars);

double dollarsToPounds(double dollars);

double dollarsToCanadaDollars(double dollars);

double canadaDollarsToEuros(double canadaDollars);

double canadaDollarsToPounds(double canadaDollars);

double canadaDollarsToDollars(double canadaDollars);

int main() {
    string currencyFrom, currencyTo, temp1, temp2, temp3, temp4; //temps purpose defined below
    double amount;

    cin >> temp1 >> amount >> currencyFrom >> temp2; //temp1&2 stores the words "convert" and "to"

    wordToLower(temp2);
    if (temp2 == "us" || temp2 == "canadian") { //if the word after currency from is "us" or "canadian"
        cin >> temp3 >> currencyTo >> temp4; //understand that temp2 is essential and write "to" to temp3 and continue on
        currencyFrom += temp2; //stores new currency as "dollarsus" or "dollarscanadian"
    } else {
        cin >> currencyTo >> temp4;
    }
    wordToLower(temp4);
    if (temp4 == "us" || temp4 == "canadian") { //if the last word in the sentence is "us" or "canadian"
        currencyTo += temp4; //stores new currency as "dollarsus" or "dollarscanadian"
    }
    wordToLower(currencyFrom);
    wordToLower(currencyTo); //these are so the user doesn't need to capitalize

    //Simply checks each possible case for conversion, and outputs the conversion based on the user input
    if (currencyFrom == currencyTo) { //checks if the currencies are the same
        cout << amount << endl;
    } else if (currencyFrom == "euros") {
        if (currencyTo == "pounds")
            cout << eurosToPounds(amount) << endl;
        else if (currencyTo == "dollarsus")
            cout << eurosToDollars(amount) << endl;
        else if (currencyTo == "dollarscanadian")
            cout << eurosToCanadaDollars(amount) << endl;
    } else if (currencyFrom == "pounds") {
        if (currencyTo == "euros")
            cout << poundsToEuros(amount) << endl;
        else if (currencyTo == "dollarsus")
            cout << poundsToDollars(amount) << endl;
        else if (currencyTo == "dollarscanadian")
            cout << poundsToCanadaDollars(amount) << endl;
    } else if (currencyFrom == "dollarsus") {
        if (currencyTo == "euros")
            cout << dollarsToEuros(amount) << endl;
        else if (currencyTo == "pounds")
            cout << dollarsToPounds(amount) << endl;
        else if (currencyTo == "dollarscanadian")
            cout << dollarsToCanadaDollars(amount) << endl;
    } else if (currencyFrom == "dollarscanadian") {
        if (currencyTo == "euros")
            cout << canadaDollarsToEuros(amount) << endl;
        else if (currencyTo == "pounds")
            cout << canadaDollarsToPounds(amount) << endl;
        else if (currencyTo == "dollarsus")
            cout << canadaDollarsToDollars(amount) << endl;
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
    return ((1.0 / 0.8886) * euros) * 0.7446;
}

double eurosToDollars(double euros) {
    return ((1.0 / 0.8886) * euros);
}

double eurosToCanadaDollars(double euros) {
    return ((1.0 / 0.8886) * euros) * 1.2841;
}

double poundsToEuros(double pounds) {
    return ((1.0 / 0.7446) * pounds) * 0.8886;
}

double poundsToDollars(double pounds) {
    return ((1.0 / 0.8886) * pounds);
}

double poundsToCanadaDollars(double pounds) {
    return ((1.0 / 0.7446) * pounds) * 1.2841;
}

double dollarsToEuros(double dollars) {
    return dollars * 0.8886;
}

double dollarsToPounds(double dollars) {
    return dollars * 0.7446;
}

double dollarsToCanadaDollars(double dollars) {
    return dollars * 1.2841;
}

double canadaDollarsToEuros(double canadaDollars) {
    return ((1.0 / 1.2841) * canadaDollars) * 0.8886;
}

double canadaDollarsToPounds(double canadaDollars) {
    return ((1.0 / 1.2841) * canadaDollars) * 0.7446;
}

double canadaDollarsToDollars(double canadaDollars) {
    return ((1.0 / 1.2841) * canadaDollars);
}
