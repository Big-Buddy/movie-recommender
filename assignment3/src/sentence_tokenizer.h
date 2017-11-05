#ifndef SENTENCE_TOKENIZER_H
#define SENTENCE_TOKENIZER_H

#include <vector>
#include <string>
#include "abstract_tokenizer.h"

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
        * @return a vector<string>: the set of strings that make up s, split into sentences based on punctuation and grammar.
        */
        vector<string> sentence_tokenize(const string &s); //vector of sentences?

        //! @brief A method to check if a char is .
        /*!
        * @param c: the char to be tested.
        * @return a bool: the truth value that is determined by testing the char c.
        */
        bool is_end(const char &c);
};

#endif // SENTENCE_TOKENIZER_H
