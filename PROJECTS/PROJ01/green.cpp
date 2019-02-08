/***********************************
 * Gregory Mathias
 * This program takes two files, one with a greenscreen, and one for the background.
 * It then replaces the greenscreen of the first image with the background image.
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

	void gray() {
		int average = (R + G + B) / 3;
		R = average;
		G = average;
		B = average;
	}

	/*inline pixel& operator=(const pixel& pix)
	{
		R = pix.R;
		G = pix.G;
		B = pix.B;
	}*/
};

struct image {
	//This vector is the underlying data structure of pixels,
	//similar to the way in which arrays are the underlying data structure for dynamic lists (usually).
	//Yes, I thought of a 2d array, but the since the size of each image is unknown at compile-time,
	//pointers (maybe double pointers) would be necessary. We aren't making a AAA game, so let's KISS
	//(keep it simple, stupid :)
	vector<vector<pixel>> pixels;

	//This operator works wonders, completely eliminating the need to work with the underlying 2d vector.
	//This operator returns the vector<pixel> (row) specified by the int index.
	vector<pixel>& operator[](int& index) {
		return pixels[index];
	}

	//This is just a useful helper method to get the width of the image by returning the number of elements (columns) in row 0.
	int width() { return pixels[0].size(); }

	//This is just a useful helper method to get the number of rows (height) in an image by returning the size of the underlying 2d vector.
	int height() { return pixels.size(); }
};

const pixel red = {255, 0, 0};
const pixel green = {0, 255, 0};
const pixel blue = {0, 0, 255};

//The return value will never need to change, thus it is const.
//The contents of this method are very simple, thus we can use inline to allow the compiler to replace all calls of this operator with the return line of the function itself.
//We want to see if the two pixels are the same color, thus the equality operator is convenient.
//We aren't modifying either pixel, and we don't need to copy and take up memory, thus the const references.
const inline bool operator==(const pixel& pixel1, const pixel& pixel2) {
	return pixel1.R == pixel2.R && pixel1.G == pixel2.G && pixel1.B == pixel2.B;
}

const inline bool operator!=(const pixel& pixel1, const pixel& pixel2) {
	return !(pixel1 == pixel2);
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
image setupDimensionsAndPixels(fstream& fin, string& fileType, int& width, int& height, int& max_val);

void replacePixelsWithShift(image& foreground, image& background, const pixel& colorToReplace);

void writePPM(image& img, ofstream& fout, const string& file_type, const int& width, const int& height, const int& max_val);

int main() {
	//These lines get the user's choice of foregroundFileName and open a file stream with the inputted file name
	string foregroundFileName, backGroundFileName;

	cout << "Foreground file: ";
	cin >> foregroundFileName;
	fstream finForeground(foregroundFileName);

	cout << "Background file: ";
	cin >> backGroundFileName;
	fstream finBackground(backGroundFileName);

	string outfilename = foregroundFileName.substr(0, foregroundFileName.size() - 4) + backGroundFileName;
	LOG(endl << "Output file: " << outfilename);

	if (!finForeground || !finBackground) {
		LOG("Error: Input file not found");
		return 0;
	}

	//these values store the filetype (P3), width and height of image (X x Y) and maximum color value.
	string fileType;
	int width, height, max_val;

	//See description of the corresponding method
	image foreground = setupDimensionsAndPixels(finForeground, fileType, width, height, max_val);
	image background = setupDimensionsAndPixels(finBackground, fileType, width, height, max_val);
	replacePixelsWithShift(foreground, background, green);

	ofstream fout(outfilename);
	writePPM(foreground, fout, fileType, width, height, max_val);
	LOG("Image saved to " + outfilename);
	return 0;
}

//See description of this method in its declaration.
//fin, file type, width, height, and max_val are all references because we want their original input values modified/used.
image setupDimensionsAndPixels(fstream& fin, string& fileType, int& width, int& height, int& max_val) {
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
	return {pixels}; //Return the new image
}

//This method takes in a 2d vector of pixels, an ofstream, the file type, width, height, and maximum value.
//It prints the necessary information that is a .ppm's file header, then prints out the pixels that makeup the
//contents of the ppm.
void writePPM(image& img, ofstream& fout, const string& file_type, const int& width, const int& height, const int& max_val) {
	fout << file_type << endl << width << ' ' << height << endl << max_val << endl;
	for (int i = 0; i < img.height(); i++) {
		for (auto& pixel : img[i]) {
			fout << pixel;
		}
		fout << endl;
	}
}

void replacePixelsWithShift(image& foreground, image& background, const pixel& colorToReplace) {
	if (foreground.height() != background.height() || foreground.width() != background.width()) {
		LOG("Error: Images have different sizes");
		exit(1);
	}
	for (int i = 0; i < foreground.height(); i++) {
		for (int j = 0; j < foreground.width(); j++) {
			if (foreground[i][j] == colorToReplace)
				foreground[i][j] = background[i][j];
		}
	}
}