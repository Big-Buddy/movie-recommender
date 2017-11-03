#ifndef SENTENCE_TOKENIZER_H
#define SENTENCE_TOKENIZER_H

#include <vector>
#include <string>
#include <abstract_tokenizer.h>

using namespace std;

class sentence_tokenizer : public abstract_tokenizer
{
    public:
        //! @brief A default constructor.
        sentence_tokenizer();

        ~sentence_tokenizer();

        //! @brief A method to break down a string into a set of strings.
        /*!
        * @param s: the string to be broken down.
        * @return a vector<string>: the set of strings that make up s, split into sentences based on full stops (.).
        */
        vector<string> sentence_tokenize(string s); //vector of sentences?
};

#endif // SENTENCE_TOKENIZER_H
