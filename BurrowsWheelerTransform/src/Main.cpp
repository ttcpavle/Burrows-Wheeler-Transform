#include "BWT.h"
#include "config.h"

int main() {

    // read from file
    string original = readFile(FILEPATH(INPUT_FILES, "loremipsum.txt"));

    // encode
	auto start_encode = chrono::high_resolution_clock::now();
    cout << "encoding started...\n";
    string encoded = BWT_encode(original);
    cout << "encoding ended\n";
    auto end_encode = chrono::high_resolution_clock::now();
    
    // decode
    auto start_decode = chrono::high_resolution_clock::now();
    cout << "decoding started...\n";
    string decoded = BWT_decode(encoded);
    cout << "decoding ended\n";
    auto end_decode = chrono::high_resolution_clock::now();

    // display to compare
    cout << "\nOriginal: " + original << endl;
    cout << "\nEncoded:  " + encoded << endl;
    cout << "\nDecoded:  " + decoded << endl;

    // stats
	cout << "\nSTATS:----------------" << endl;

	int originalSize = original.size();
	int encodedSize = encoded.size();
    cout << "Original length: " << originalSize << endl;
    cout << "Encoded length:  " << encodedSize << endl;

	float compressRate = ((float)encodedSize / originalSize) * 100;
	cout << "Compress rate:   " << compressRate << "%" << endl;

    auto encode_duration = chrono::duration_cast<chrono::milliseconds>(end_encode - start_encode);
    auto decode_duration = chrono::duration_cast<chrono::milliseconds>(end_decode - start_decode);

    cout << "Encoding time: " << encode_duration.count() << " ms" << endl;
    cout << "Decoding time: " << decode_duration.count() << " ms" << endl;

    // output file
    writeFile(FILEPATH(OUTPUT_FILES, "loremipsum_encoded.txt"), encoded);

    // to improve: make it possible to encode text multiple times (sentinel character must be different for different
    // layers of encoding)
	return 0;
}