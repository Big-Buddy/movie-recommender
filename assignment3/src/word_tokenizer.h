#ifndef WORD_TOKENIZER_H_
#define WORD_TOKENIZER_H_
#include <string>
#include <vector>
#include "abstract_tokenizer.h"

using namespace std;

class word_tokenizer : public abstract_tokenizer
{


public:
    //! @brief A default constructor.
	word_tokenizer();

	//! @brief A default destructor.
	~word_tokenizer();

    //! @brief A method to break down a string into a set of strings.
    /*!
     * @param s: the string to be broken down.
     * @return a vector<string>: the set of strings that make up s, minus whitespaces and punctuation.
     */
	vector<string> word_tokenize(string s);
};



#endif /* TOKENIZER_H_ */
