/************************************************
Determines number of adults and children from properly formatted text file.
Gregory Mathias
************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#define LOG(x) std::cout << (x) << std::endl; //This macro alleviates the pain of typing this out every time.

struct date;
using namespace std;

vector<string> split_string(const string& splittable, char splitter = ' '); //Splits string into vector by defined character that defaults to ' '
bool is_leap_year(int& year); //Determines if the given year is a leap year

int month_days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; //These are the days per month for jan, feb, etc.. in order; used for calculating the total number of days in a given date

struct date //this struct is just a simple way of keeping track of days, months, and years
{
	int day, month, year;

	int to_int() const
	{
		int days = 0;
		for (int i = 0; i < month; i++)
			days += month_days[i]; //This accounts for the differing number of days per month.
		for (int i = 0; i < year; i++)
			days += is_leap_year(i) ? 366 : 365; //Instead of just multiplying year by 365, this accounts for leap years as well.
		return days + day;
	}

	bool is_adult(date& cutoff_date) const
	{
		return this->to_int() <= cutoff_date.to_int(); //Just does a simple comparison of the this date with another.
	}
};

int main()
{
	string filename;
	int adults_total;
	int children_total = adults_total = 0; //these two ints keep track of the total children and adults
	std::cout << "Filename: ";
	cin >> filename; //gets the file name that the user wants to input
	fstream fin(filename); //opens the file with the filename the user inputted

	if (fin) //if the file exists
	{
		string line;
		date cutoff_date = { 27, 9, 2000 }; //this is the given cutoff date
		while (getline(fin, line))
		{
			vector<string> name_and_date = split_string(line); //split the line by a space (should be of size two, corresponding to name and date)
			
			if (name_and_date.size() != 2) //something's wrong with this line, skip
				continue;

			vector<string> dateSplit = split_string(name_and_date[1], '/'); //split the date by the backslash, should be month, day, year (size 3)
			if (dateSplit.size() != 3) //something's wrong with this date, skip
				continue;
			//stoi parses an int from a string
			const int year_in_line = stoi(dateSplit[2]) <= 19 ? stoi(dateSplit[2]) + 2000 : stoi(dateSplit[2]) + 1900; //this checks if the year is less than 19; if so, it must be part of the 2000s; if not, we're back to the 1900s
			date bday = {stoi(dateSplit[1]), stoi(dateSplit[0]), year_in_line}; //this just takes the month, day, and year of the given birthday and puts it into a nice new date struct
			bday.is_adult(cutoff_date) ? adults_total++ : children_total++; //add one to children or adults depending on if the bday meets the cutoff
		}
	}
	else
	{
		LOG("File not found!"); //give an error message if the file does not exist
		return 1;
	}

	LOG(std::to_string(adults_total) + " adults and " + std::to_string(children_total) + " children"); //prints out adults and children totals; to_string is just a nice standard library function to convert and int to a string
	return 0;
}

// wrote this method myself; got some ideas from StackOverflow
vector<string> split_string(const string& splittable, const char splitter) //the string to split, along with the character to split it by
{
	vector<string> strings; //this is the vector of strings which will store the separate, split strings as a dynamic array
	stringstream stream(splittable); //declares a string stream

	string str;
	while (getline(stream, str, splitter))
		//str is a temporary storage value for the string; as the stream moves along, if it encounters any characters matching splitter, it will execute the code below, and then loop back again, repeating the process until the end of the splittable string
	{
		if (!str.empty()) //ignores consecutive spaces
			strings.push_back(str); //adds str to the vector strings
	}
	return strings;
}

bool is_leap_year(int& year)
{
	return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0); //If the given year is divisible by 4 and (not divisible by 100 or divisible by 400), return true; otherwise false. 
}