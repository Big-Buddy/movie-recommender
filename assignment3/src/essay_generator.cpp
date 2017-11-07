//
// Created by Spasov on 11/6/2017.
//

#include <algorithm>
#include <iostream>
#include "essay_generator.h"
using namespace std;

essay_generator::~essay_generator() = default;

essay_generator::essay_generator() = default;

string essay_generator::generateEssay(vector<sentence> sentenceList, int numOfWords) const {
    string str;
    vector<sentence> chosenSentences;
    int usedWords = 0;
    for (auto &it : sentenceList) {
       if(it.size() + usedWords <= numOfWords){
           chosenSentences.push_back(it);
           usedWords += it.size();
       }
        if(usedWords == numOfWords)
            break;
    }

    std::sort(chosenSentences.begin(), chosenSentences.end());

    for(auto &it : sentenceList){
        str += it.get_content() + "\n";
    }
    std::cout<<str;
    return str;

}




