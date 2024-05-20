#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long int int64;


// Function to convert the hash value
// of a given string
void SHA512_padding(string inputString)
{
    

    string binaryString;

    // Traverse the string S
    for (int i = 0; i < inputString.size(); ++i) {

        // Add the character to stream
        binaryString += bitset<8>(inputString[i]).to_string();
    }

    // Stores string of size 1024
    string finalString;

    // Stores the string in the
    finalString = binaryString;

    // Stores the length of string
    int stringLength = finalString.length();
    int paddedLength;

    // Find remainder string length
    int remainder = finalString.length() % 1024;

    // If remainder is less than 896
    if (1024 - 128 >= remainder) {
        paddedLength = 1024 - remainder;
    }

    // If remainder is greater than 896
    else if (1024 - 128 < remainder) {
        paddedLength = 2048 - remainder;
    }

    // Append 1 to string
    if(paddedLength != 128)
        finalString += "1";

    // Append paddedLength-129 zeros
    // in the string
    for (int y = 0; y < paddedLength - 129; y++) {
        finalString += "0";
    }

    // Stores the binary representation
    // of string length
    string lengthbits
        = bitset<128>(stringLength).to_string();

    // Append the lengthbits to string
    finalString += lengthbits;

    cout << "Previous string length : " << binaryString.size() << endl;
    cout << "Padded string length :   " << finalString.size() << endl;
    cout << "Padded bits :" << finalString << endl;

}

string readFromFile(const std::string& filename) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Error: Unable to open file!" << endl;
        return "";
    }

    string result;
    string line;
    while (getline(inputFile, line)) {
        result += line + '\n';
    }

    inputFile.close();
    return result;
}


int main()
{
    // Input
    string S = readFromFile("SHA_input.txt");

    // Function Call
    SHA512_padding(S);
    return 0;
}
