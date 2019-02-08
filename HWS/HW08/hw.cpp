/************************************************
Grade Calculator, from text file
Gregory Mathias
************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

vector<string> split_string(const string& splittable, char splitter = ' '); //splits string into vector by defined character that defaults to ' '

int main()
{
	string filename, best_student;
	const double hw_weight = 0.2;
	const double quiz_weight = 0.2;
	const double exam_weight = 0.6;

	std::cout << "Filename: ";
	cin >> filename; //gets the file name that the user wants to input
	fstream fin(filename); //opens the file with the filename the user inputted
	map<string, double> student_grades;
	//Maps are dictionaries in other languages. This one stores the students name as a key and their grade as the key's corresponding value

	if (fin) //if the file exists
	{
		string line;
		double highest_grade = 0; //double keeps track of the highest average grade

		while (getline(fin, line)) //reads the file line by line
		{
			vector<string> split_line = split_string(line); //splits the line of text by spaces
			if (split_line.size() < 4) //if there are more columns than expected, the text file is of incorrect format
			{
				std::cout << "The input file is incorrectly formatted." << endl;
				break;
			}
			if (split_line[0] == "NAME" && split_line[1] == "HW" && split_line[2] == "QUIZ" && split_line[3] == "EXAM")
				//skip any line that contains the headers for the column, presumably the first line
				continue;

			//This is the math for calculating the students' grades.
			student_grades[split_line[0]] = stod(split_line[1]) * hw_weight + stod(split_line[2]) * quiz_weight + stod(split_line[3]) * exam_weight;
			//multiply each of the student's grades for hw, quizzes, and exams by their respective weight constant, then assign that value to student_grades, with the key to the value being the student's name

			if (student_grades[split_line[0]] > highest_grade) //if the student has the highest average grade so far
			{
				highest_grade = student_grades[split_line[0]]; //reassign the highest_grade value
				best_student = split_line[0]; //rename the best_student string to the current student's name
			}
		}

		for (map<string, double>::value_type const& pair : student_grades) //loops through the student_grades map, getting each value_type
		{
			std::cout << pair.first << '\t' << pair.second << endl;
			//prints each key (pair.first) (the student's name) with its value (pair.second) (their grade)
		}
	}
	else
		std::cout << "File is missing or does not exist. Please use a correct file" << endl; //give error message if the file does not exist

	std::cout << "The best student is " << best_student << '.' << endl; //prints out the best student's name
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
