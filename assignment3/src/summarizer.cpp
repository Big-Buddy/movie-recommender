//Authors
// Alexandre Pelletier - 27259492
// Martin Spasov 40000916
// Loic Huss - 40000298
#include "indexer.h"
#include "document_indexer.h"
#include "document.h"
#include "Query_Result.h"
#include "sentence.h"
#include "sentence_tokenizer.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <dirent.h>
#include <cstring>
#include <sstream>

using namespace std;


int main(){
    indexer sentIdx;

    map<string, string> choices;
    choices ["1"] = "a3data/q1.txt";
    choices ["2"] = "a3data/q2.txt";
    choices ["3"] = "a3data/q3.txt";

    map<string, string > documentFiles;
    documentFiles ["1"] = "a3data/q1docs";
    documentFiles ["2"] = "a3data/q2docs";
    documentFiles ["3"] = "a3data/q3docs";

    //first, get the topic input from the user
    bool goodInput = false;
    string fileNum;
    while(!goodInput) {
        cout << "Which topic file would you like to choose? (1-3)" << endl;
        cout << "1 - q1.txt" << endl << "2 - q2.txt" << endl << "3 - q3.txt" << endl;
        cin >> fileNum;
        if (fileNum == "1" || fileNum == "2" || fileNum == "3") {
            goodInput = true;
        }
        else{
            cout << "Please enter a valid choice..." << endl;
        }
    }

    //then, tell the user what he chose
    string topic="", tempString;
    fstream topicInput(choices[fileNum]);
    while(topicInput >> tempString){
        topic += " " + tempString;
    }
    cout << "-----------------------------------------" << endl << endl;
    cout << "The topic you chose : " << endl << topic << endl << endl;
    cout << "-----------------------------------------" << endl;

    //then, read all of the documents that have to do with the user's input
    vector<document> docVec;
    int docNumCounter = 0;
    DIR *documentDirectory;
    struct dirent *entry;
    const char* docSrc = documentFiles[fileNum].c_str();
    //first, make sure docSrc is a proper directory
    if( documentDirectory = opendir(docSrc) ){
        //then, read it into entry until you can't anymore (kinda like while(fin >> str))
        while(entry = readdir(documentDirectory)){
            if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 ){
                string temp = documentFiles[fileNum] + "/" + entry->d_name;
                document doc(temp, docNumCounter);
                docVec.push_back(doc);
                ++docNumCounter;
            }
        }
        closedir(documentDirectory);
    }


    //get all the documents, and turn them into sentences.
    vector<vector<sentence> > sentVecVec;
    vector<sentence> sentVec;
    sentence_tokenizer st;
    //add all the documents in docVec to the document_indexer, then create a sentence vector out of the document's contents.
    //then, add this sentence vector to a vector of all sentence vectors.
    for(vector<document>::iterator docit = docVec.begin(); docit != docVec.end(); ++docit){
        sentVec = st.sentence_tokenize(docit->get_content(), docit->getDocNum());
        sentVecVec.push_back(sentVec);
    }
    //iterate through every single sentence, and add them to the indexer
    for(vector<vector<sentence> >::iterator sentVecIt = sentVecVec.begin(); sentVecIt != sentVecVec.end(); ++sentVecIt){
        for(vector<sentence>::iterator sentIt = sentVecIt->begin(); sentIt != sentVecIt->end(); ++sentIt){
            &*sentIt >> sentIdx;
        }
    }

    //get a number of words that the user wants to have in his new essay.
    bool isNumberInput = false;
    int numWords = 0;
    while(!isNumberInput) {
        cout << "How many words would you like in your essay?" << endl;
        string temp;
        cin >> temp;
        stringstream convertor;
        convertor << temp;
        convertor >> numWords;

        //make sure it's an int
        if(convertor.fail()){
            cout << "Please enter a valid number..." << endl << endl;
        }
        else{
            isNumberInput = true;
        }
    }
    cout << endl << "-----------------------------------------" << endl;


    Query_Result sentQ;
    vector<pair<index_item*, double> > sentenceScore;
    sentenceScore = sentQ.query(sentIdx, topic);

    string newEssay = sentQ.generateEssayFromSentences(numWords);


    cout << endl << "Here is your ~" << numWords << " word essay." << endl << endl << newEssay << endl;

    cout << endl << "Enter anything to exit application" << endl;
    string bye;
    cin >> bye;

	return 0;
}
