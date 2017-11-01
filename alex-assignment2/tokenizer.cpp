#include "tokenizer.h"
#include "document.h"

#include <iostream>
#include <fstream>

using namespace std;

vector<document> tokenizer::initialize_documents(const string &input_file)
{
    ifstream myReadFile;
    myReadFile.open(input_file.c_str());
    string fileName;
    string inputWord;
    vector<document> documentVector;
    if (myReadFile.is_open()) {
        while (!myReadFile.eof()) {
            myReadFile >> fileName;
            ifstream myReadFile2;
            string newFile(fileName);
            myReadFile2.open(newFile.c_str());
            document newDoc = document(fileName);
            if (myReadFile2.is_open()) {
                while (myReadFile2 >> inputWord) {
                    map<string,int>::const_iterator mapIt;
                    inputWord = document::formatInput(inputWord);
                    mapIt = newDoc.words_found.find(inputWord);
                    if (!(mapIt == newDoc.words_found.end())) {
                        newDoc.words_found[inputWord]++;
                        newDoc.total_words++;
                    } else {
                        newDoc.words_found.insert(std::pair<string,int>(inputWord,1));
                        newDoc.total_words++;
                    }
                }
            }
        documentVector.push_back(newDoc);
        }
    }

    myReadFile.close();
    return documentVector;

}


