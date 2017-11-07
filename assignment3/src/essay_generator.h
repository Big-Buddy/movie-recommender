//
// Created by Spasov on 11/6/2017.
//

#ifndef SRC_ESSAY_GENERATOR_H
#define SRC_ESSAY_GENERATOR_H


#include "sentence.h"
#include <vector>

class essay_generator {
    public:
        essay_generator();
        ~essay_generator();
        string generateEssay(vector<sentence> sentenceList, int numOfWords) const;

};


#endif //SRC_ESSAY_GENERATOR_H
