#include <iostream>
#include <ctgmath>
#include <algorithm>
#include <string>

/*
#include <memory>
#include <fstream>*/

using namespace std;

/*std::string exec(const char *cmd) { // https://stackoverflow.com/questions/478898/how-do-i-execute-a-command-and-get-output-of-command-within-c-using-posix
    std::array<char, 128> buffer; //declares array for buffer of output
    std::string result; //stores the result of the command
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"),
                                                  pclose); //declares a unique pointer to the pipe, which is opened with popen with the parameters being the command
    if (!pipe) { //catches failure of pipe opening
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) !=
           nullptr) { //gets the output of the command that the pipe is returning and appends it to the string result
        result += buffer.data();
    }
    return result; //returns all output of the command-line command
}*/

//This is the only relevant method for the simple way of doing things as presented in the lesson.
int toDecimal(string input) { //returns an integer of the decimal value of a binary input as the parameter
    int sum = 0;
    input.erase(remove(input.begin(), input.end(), ' '),
                input.end()); //trim the string; will mess up the return value bad if there's an extra space or something
    unsigned long counter = input.length();
    for (char i : input) { //this part just converts the binary to decimal in the same way that lab02p1 does
        counter--;
        sum += (i - '0') * pow(2, counter);
    }
    return sum;
}

void convertBinaryNumbers(
        string &input); //Put method signature up here while I thought about recursion, but then I thought again. Recursion is too tricky haha, but I figured it's probably better practice to leave method signatures up here anyways

int main() {
/* Guess I can't do it this elegant way because the submit system won't support it with standard libraries :(
    RESTART:

    cout << "Please enter an equation (each value separated by spaces): " << endl;
    string input;

    while (getline(cin, input)) {

        input.erase(remove(input.begin(), input.end(), '='), input.end()); //we don't need an equals sign at the end
        input.erase(remove(input.begin(), input.end(), 'd'), input.end()); //we don't need to specify decimals since c++ is doing the math for us
        input.erase(remove(input.begin(), input.end(), 'D'), input.end());
        convertBinaryNumbers(input); //convert all the binary numbers to decimal inside the user input
        input.erase(remove(input.begin(), input.end(), 'b'), input.end()); //don't know how, but there might be some extra 'b's in there; can't be too careful
        input.erase(remove(input.begin(), input.end(), 'B'), input.end());

        ofstream outfile("temp.cpp"); //so I came up with this idea myself: why should I do the math when c++ can do math for me? I understand the concepts of string parsing and conversion;
        outfile << "#include <iostream>\n" << //once the user input is in decimal form, I can just write to a temporary c++ file that writes the output of the math equation, compile and run it, and catch the output, which is the answer
                "using namespace std;\n" <<
                "int main() {\n" <<
                //"double output = " << input << ";" <<
                "cout << ((double)" << input << ") << endl;\n" <<
                "}" << std::endl;
        outfile.close(); //saves the temporary c++ program

        cout << exec("g++ -o temp temp.cpp") << endl; //runs the command to compile the temp program, printing any errors that might arise from compilation to the user; could give hints as to an invalid equation
        cout << exec("./temp") << endl; //prints the result of the math equation the user entered

        remove("temp.cpp"); //deletes the temporary c++ source file
        remove("temp"); //deletes the temporary c++ program
        break; //we only need 1 line of user input
    }*/

    //This is the way to fulfill the submit system and lesson's requirements
    string num1, num2, sign; //Have two variables to store the numbers, and a sign holder string
    int num1Int = 0; //These will be assigned later according to their parsing
    int num2Int = 0;
    cin >> num1 >> sign;
    if (num1[0] == 'B') {
        num1 = num1.substr(1, num1.length() - 1); //This cuts out the letter in front, used elsewhere
        num1Int = toDecimal(num1); //Converts the binary string to a decimal, assigns it the num1Int
    } else if (num1[0] == 'D') {
        num1 = num1.substr(1, num1.length() - 1); //Just cut off the preceding letter and
        num1Int = stoi(num1); //parse the string to an integer
    }

    if (sign[0] == '=') //If there is no addition sign and an equals sign instead, we can assume the user entered just a number they wanted to convert to decimal; skip the rest
        goto END; //Gotos are ugly, but they work for primitive programs

    cin >> num2;
    //Repeats the same process as before, but for num2 and num2Int
    if (num2[0] == 'B') {
        num2 = num2.substr(1, num2.length() - 1);
        num2Int = toDecimal(num2);
    } else if (num2[0] == 'D') {
        num2 = num2.substr(1, num2.length() - 1);
        num2Int = stoi(num2);
    }

    END:
    cout << (num1Int + num2Int) << endl; //Adds num1Int and num2Int, and displays the values.
    return 0;
}

void convertBinaryNumbers(
        string &input) { //manipulating references instead of returning new strings and assigning to the original input is less memory costly
    for (int i = 0; i < input.length(); i++) {
        if (input.at(i) == 'b' || input.at(i) == 'B') { //if something starts with a "b" or "B", we know it is binary
            int strBegin = i + 1;

            for (int j = strBegin; j <
                                   input.length(); j++) { //second loop finds last occurence of a "0" or "1" to get full binary number (not limited to 4 digits)

                if ((input.at(j) != '1' && input.at(j) != '0') || j == input.length() - 1) {
                    int strEnd = j == input.length() ? j : j +
                                                           1; //if we're at the end of the input, we don't want to pass out of bounds parameters to the erase and substr functions
                    int lastBin = strEnd - strBegin; //length of binary number
                    string binary = input.substr(strBegin, lastBin); //this is the full binary number
                    input.erase(input.begin() + (strBegin - 1)); //erase the 'b' or 'B'
                    strBegin -= 1; //since we erase the 'b' or 'B', we need to subtract one from the begin integer
                    input.erase(strBegin, lastBin); //erase the binary digits
                    input.insert(strBegin, (to_string(toDecimal(binary)) +
                                            " ")); //insert the decimal value of the binary, and a space for prettiness when debugging this program
                    break;
                }

            }
        }
    }
}

