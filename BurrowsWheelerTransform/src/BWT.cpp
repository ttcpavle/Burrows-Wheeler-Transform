#include "BWT.h"

// takes input text and returns all rotations in vector
static vector<rotation> genRotations(const string& inputText) {
    vector<rotation> rotations;
    rotations.reserve(inputText.size());
    for (int i = 0; i < inputText.size(); i++) {
        rotations.emplace_back(i, &inputText[i]);
    }
    return rotations;
}

// Optimized comparison of rotated strings
static bool lexCompare(const rotation& str1, const rotation& str2, const string& extendedInput, const int len) {
    return extendedInput.compare(str1.rotationIndex, len, extendedInput, str2.rotationIndex, len) < 0;
}

// Optimized function to sort all rotations
static vector<int> sortRotations(vector<rotation>& rotations, const string& inputText) {
    vector<int> indexes;
    indexes.reserve(inputText.size());
    string extendedInput = inputText + inputText;
    int len = inputText.size();

    sort(rotations.begin(), rotations.end(),
        [&extendedInput, len](const rotation& str1, const rotation& str2) {
            return lexCompare(str1, str2, extendedInput, len);
        });

    // Fill indexes with sorted rotation indices
    for (const auto& rot : rotations) {
        indexes.emplace_back(rot.rotationIndex);
    }
    return indexes;
}

// get last column in sorted rotation matrix
static string findLastColumn(const string& inputText, const vector<int>& indexes) {
    string lastChars;
    int len = inputText.size();
    for (int i = 0; i < len; i++) {
        lastChars += inputText[(indexes[i] + len - 1) % len];
    }
    return lastChars;
}

string runLengthEncode(const string& inputText) {
    string rlc;
    string::const_iterator ir;
    int count = 1;

    for (ir = inputText.begin(); ir != inputText.end(); ir++) {
        // if it's the end of string or if next character is different than current, update rlc string
        if (ir + 1 == inputText.end() || *(ir + 1) != *ir) {
            // if count > 1 write the number
            if (count > 1) {
                rlc += to_string(count);
            }  
            rlc += *ir;
            count = 1;
        }
        else {
            // keep counting if character repeats
            count++;
        }
    }
    return rlc;
}

string runLengthDecode(const string& rl_code) {
    string str;
    string::const_iterator ir = rl_code.begin();
    int count = 1;

    while (ir != rl_code.end()) {
        // if character is number write consecutive numbers in string
        if (isdigit(*ir)) {
            string num;
            while (isdigit(*ir) && (ir + 1 != rl_code.end())) {
                num += *ir;
                ir++;
            }
            // convert string to int and assign to count variable
            count = stoi(num);
        }
        // if character is not digit, write it "count" times
        if (!isdigit(*ir)) {
            char ch = *ir;
            str.append(count, ch);
            count = 1; // reset count
        }
        else {
            cerr << "Invalid character in string\n";
            exit(EXIT_FAILURE);
        }
        ir++;
    }
    return str;
}

// encode textual data (string) with Burrows Wheeler Transform
string BWT_encode(const string& inputText) {
    vector<rotation> v = genRotations(inputText);
    vector<int> s = sortRotations(v, inputText);
    string c = findLastColumn(inputText, s);
    c = runLengthEncode(c);
    return c;
}

// decode textual data (string) with Burrows Wheeler Transform
string BWT_decode(const string& encodedText) {

    string firstCol = runLengthDecode(encodedText); // first column (sorted string)
    string lastCol = firstCol;
    sort(firstCol.begin(), firstCol.end());

    string decoded = ""; // string for decoded data
    decoded.reserve(firstCol.size());
    int len = firstCol.size();

    unordered_map<char, int> lastColCharsCount;
    vector<pair<char,int>> lastColVec;
    unordered_map<char, int> firstColCharsCount;
    vector<pair<char,int>> firstColVec;

    unordered_map<string, pair<char,int>> searchWord;

    // pair each character with its ordinal number (for both first and last column) and put resulting pairs in vector
    for (int i = 0; i < len; i++) {
        char currLastChar = lastCol[i];
        pair<char, int> currLastPair = make_pair(currLastChar, ++lastColCharsCount[currLastChar]);
        lastColVec.push_back(currLastPair);
        char currFirstChar = firstCol[i];
        pair<char, int> currFirstPair = make_pair(currFirstChar, ++firstColCharsCount[currFirstChar]);
        firstColVec.push_back(currFirstPair);

        // convert pairs from last column to string and use them as key, and corresponding pair as value
        string newKey = currLastPair.first + to_string(currLastPair.second);
        searchWord[newKey] = currFirstPair;
    }

    // initial key 
    string currKey = string(1, SENTINEL_CHAR) + "1";
    // search through keys and reconstruct original string
    for (int i = 1; i < len; i++) {
        pair<char, int> currPair = searchWord[currKey];
        decoded += currPair.first;
        currKey = currPair.first + to_string(currPair.second);
    }  
    decoded += SENTINEL_CHAR;

    return decoded;
}

string readFile(const char* filename) {
    ifstream in(filename, ios::binary);
    if (in.is_open())
    {
        string contents;
        in.seekg(0, ios::end);
        contents.resize(in.tellg());
        in.seekg(0, ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        if (contents.back() != SENTINEL_CHAR) {
            contents += SENTINEL_CHAR;
        }
        cout << "File read successfully" << endl;
        return(contents);
    }
    cerr << "Couldn't read file:  " << filename << endl;
    exit(EXIT_FAILURE);
}

int writeFile(const char* filename, const string& data) {

    ofstream out(filename, ios::binary);
    if (out.is_open()) {
        int size = data.size();
        out.write(data.c_str(), size);
        out.close();
        cout << "File written successfully" << endl;
        return 0;
    }
    cerr << "Couldn't write file:  " << filename << endl;
    return -1;
}