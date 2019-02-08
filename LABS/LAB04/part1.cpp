/************************************************
Text File Analyzer (word count, average word count)
Gregory Mathias
************************************************/

#include <iostream>
#include <fstream>
#include <string>

#define LOG(x) std::cout << x << std::endl; //simple macro for easy output

using namespace std;

int main()
{
	cout << "Enter a filename: ";
	string filename;
	cin >> filename;
	fstream fin(filename); //gets a filename from the user, creates an fstream from the filename

	int words = 0; //stores # of words
	double averageLength = 0; //average length of the words
	string word; //temporary variable for each word

	while(fin >> word) //while there are words
	{
		words++; //increment the word count by one
		averageLength += word.length(); //add the word length to average word length
	}

	averageLength /= words; //divide the average length by the number of words

	LOG("Word count: " << words << "\nAverage word length: " << averageLength); //print it pretty
	
	return 0;
}
