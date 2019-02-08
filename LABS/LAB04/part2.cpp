/************************************************
Text File Analyzer (word count, average word count, average sentence length)
Gregory Mathias
************************************************/

#include <iostream>
#include <fstream>
#include <string>

#define LOG(x) std::cout << x << std::endl;

using namespace std;

int main() {
    cout << "Enter a filename: ";
    string filename;
    cin >> filename;
    fstream fin(filename); //open an fstream from the filename the user inputted

    int words = 0, sentences = 0, sentenceLength = 0; //word count, number of sentences, and the length of the current sentence
    double averageWordLength = 0, averageSentenceLength = 0; //average word and sentence length
    string word;

    while (fin >> word) //while there's another word
    {
        words++; //increment total words by one
        sentenceLength++; //increment the words in the current sentence by one
        if (word.find('.') != string::npos || word.find('!') != string::npos ||
            word.find('?') != string::npos) //if the sentence ends at this word
        {
            averageSentenceLength += sentenceLength; //add the current sentence's length to the variable holding their average
            sentenceLength = 0; //the sentence ended, set the next sentence's length to 0
            sentences++; //increment the sentence count by 1
        }
        averageWordLength += word.length(); //add the word length to average word length
    }

    averageWordLength /= words; //divide the average word length by the number of words
    averageSentenceLength /= sentences; //divide the average sentence length by the number of sentences

    LOG("Word count: " << words << "\nAverage word length: " << averageWordLength << "\nAverage sentence length: "
                       << averageSentenceLength); //print it pretty

    return 0;
}