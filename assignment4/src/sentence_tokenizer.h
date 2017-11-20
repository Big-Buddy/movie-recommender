#ifndef SENTENCE_TOKENIZER_H
#define SENTENCE_TOKENIZER_H

#include <vector>
#include <string>
#include "abstract_tokenizer.h"
#include "sentence.h"

using namespace std;

class sentence_tokenizer : public abstract_tokenizer
{
    public:
        //! @brief A default constructor.
        sentence_tokenizer();

        //! @brief A default destructor.
        ~sentence_tokenizer();

        //! @brief A method to break down a string into a set of strings.
        /*!
        * @param s: the string to be broken down.
        * @param docNum: the doc number of the string s (parentDocNum of sentence)
        * @return a vector<string>: the set of strings that make up s, split into sentences based on punctuation and grammar.
        */
        vector<sentence> sentence_tokenize(const string &s, int docNum); //vector of sentences?

        //! @brief A method to check if a char is either "?" OR "." OR "!".
        /*!
        * @param c: the char to be tested.
        * @return a bool: the truth value that is determined by testing the char c.
        */
        bool is_end(const char &c);

        //! @brief A method to check if a string is an abbreviation.
        /*!
        * @param first: the string to be tested.
        * @param second: This is the string which appears after first, it is used in the detection of abbreviations
        * @return a bool: the truth value that is determined by testing the string first.
        */
        bool isAbbreviation(const string &first, const string &second);
};

#endif // SENTENCE_TOKENIZER_H
