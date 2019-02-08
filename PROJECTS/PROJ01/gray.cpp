/***********************************
 * Gregory Mathias
 * This program takes in a .ppm file and outputs its grayscale equivalent.
 **********************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

//This macro makes printing so much easier. It's simply a preprocessor command for the compiler to replace all calls of LOG(x) with its correlating cout function
#define LOG(x) std::cout << x << std::endl;

using namespace std;

//This struct provides great abstraction for a "pixel"
struct pixel {
	int R, G, B;

	//This method takes the r, g, and b values of this pixel, averages them, and sets each to the average.
	void gray() {
		int average = (R + G + B) / 3;
		R = average;
		G = average;
		B = average;
	}
};

//We don't need this now, but we will come green screen time.
//The return value will never need to change, thus it is const.
//The contents of this method are very simple, thus we can use inline to allow the compiler to replace all calls of this operator with the return line of the function itself.
//We want to see if the two pixels are the same color, thus the equality operator is convenient.
//We aren't modifying either pixel, and we don't need to copy and take up memory, thus the const references.
const inline bool operator==(const pixel& pixel1, const pixel& pixel2) {
	return pixel1.R == pixel2.R && pixel1.G == pixel2.G && pixel1.B == pixel2.B;
}

//This is just an easier way to print pixels by overloading the << operator; it handles a lot of the dirty work, just like the LOG(x) macro
//The return value is an ostream reference because we do not need to copy it; same with the ostream parameter and the const pixel parameter.
ostream& operator<<(ostream& out, const pixel& pixel) {
	return out << pixel.R << ' ' << pixel.G << ' ' << pixel.B << ' ';
}

//This function creates a vector of strings by splitting it via the given character; default splitting character is space.
vector<string> split_string(const string& splittable, char splitter = ' ');

//This function does the necessary dirty work for our needs in this particular project, setting file type, width, height, maximum value,
//and returning a two-dimensional vector array of pixel structs. Yes, I thought about a normal 2d array, but since the width and height
//of the ppm are not known at compile time, this would require (more) complex code and various pointers to implement. Possible, but
//we aren't making a AAA game.
vector<vector<pixel>> setupDimensionsAndPixels(fstream& fin, string& fileType, int& width, int& height, int& max_val);

//See implementation comments.
void grayScalePixels(vector<vector<pixel>>& pixels);

//See implementation comments.
void writePPM(vector<vector<pixel>>& pixels, ofstream& fout, const string& file_type, const int& width, const int& height, const int& max_val);

int main() {
	//These lines get the user's choice of infilename and open a file stream with the inputted file name
	string infilename;
	cout << "Input file: ";
	cin >> infilename;
	fstream fin(infilename);
	string outfilename = infilename.empty() ? "output.ppm" : "gray" + infilename;
	LOG(endl << "Output file: " << outfilename);

	if (!fin) {
		LOG("Error: Input file not found");
		return 0;
	}

	//these values store the filetype (P3), width and height of image (X x Y) and maximum color value.
	string fileType;
	int width, height, max_val;

	//See description of the corresponding method
	vector<vector<pixel>> pixels = setupDimensionsAndPixels(fin, fileType, width, height, max_val);

	//Creates an ofstream to write to the correct file name, grasyscales the image, and write the new image to the correct ppm
	ofstream fout(outfilename);
	grayScalePixels(pixels);
	writePPM(pixels, fout, fileType, width, height, max_val);

	//Inform the user as to where the new, grayscaled image is saved.
	LOG("Image saved to " + outfilename);
	return 0;
}

//See description of this method in its declaration.
//fin, file type, width, height, and max_val are all references because we want their original input values modified/used.
vector<vector<pixel>> setupDimensionsAndPixels(fstream& fin, string& fileType, int& width, int& height, int& max_val) {
	//This sets the file type, width, height, and max value according to standard PPM format
	fin >> fileType;
	fin >> width;
	fin >> height;
	fin >> max_val;

	int red, green, blue; //Temporary value holding the current "word" in the file as fin iterates through it
	vector<vector<pixel>> pixels(height, vector<pixel>(width)); //Initialize a 2d vector of pixels with dimensions corresponding to the image's width and height
	int rowCounter = -1, columnCounter = 0; //Row counter equals -1 because the check for columnCounter % width will increment it by one automatically.
	while (fin >> red >> green >> blue) { //These fins simply get the next three numbers, which should come in sets of three, corresponding to r, g, and b.
		if (columnCounter % width == 0) { //This checks if the columnCounter has equalled the width of the image, and it resets it to 0 and increments the rowCounter
			columnCounter = 0;
			rowCounter++;
		}
		pixels[rowCounter][columnCounter] = {red, green, blue}; //Set the current row and height value in pixels to the red, green, and blue values they correspond to.
		columnCounter++; //Increment the column counter by one

	}
	return pixels; //Return the 2d vector
}

//This method grayscales every pixel in the 2d vector; see pixel.gray()
void grayScalePixels(vector<vector<pixel>>& pixels) {
	for (auto& row : pixels) { //auto& just creates a reference to every vector<pixel> in pixels; auto is easier to type and is also flexible for easy type resolution.
		for (auto& pix : row) { //auto& here does the same as above, but instead is a reference to every pixel in each vector<pixel> that represents a row.
			pix.gray();
		}
	}
}

//This method takes in a 2d vector of pixels, an ofstream, the file type, width, height, and maximum value.
//It prints the necessary information that is a .ppm's file header, then prints out the pixels that makeup the
//contents of the ppm.
void writePPM(vector<vector<pixel>>& pixels, ofstream& fout, const string& file_type, const int& width, const int& height, const int& max_val) {
	fout << file_type << endl << width << ' ' << height << endl << max_val << endl;
	for (auto& row : pixels) {
		for (auto& pixel : row) {
			fout << pixel;
		}
		fout << endl;
	}
}