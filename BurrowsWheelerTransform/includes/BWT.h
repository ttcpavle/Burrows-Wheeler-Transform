#ifndef BWT_H
#define BWT_H

#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <chrono>

using namespace std;

// you can use symbols such as: #, %, @, !
#define SENTINEL_CHAR '$'

// directory paths:
// INPUT_FILES - /input folder in project directory, used for input files for encoding
// OUTPUT_FILES - /output folder in project directory, used for encoded files
#define FILEPATH(directory, filename) (string(directory) + "/" + filename).c_str()

// Rotation struct is used instead of actually rotating strings
struct rotation {
	const char* suffix;
	int rotationIndex;

	rotation(int rotationIndex, const char* suffix) {
		this->rotationIndex = rotationIndex;
		this->suffix = suffix;
	}
};

// Burrow-s Wheeler Transform
string BWT_encode(const string& str);
string BWT_decode(const string& str);

// Run-Length coding
string runLengthEncode(const string& inputText);
string runLengthDecode(const string& rl_code);

// read/write files
string readFile(const char* filename);
int writeFile(const char* filename, const string& data);

#endif
