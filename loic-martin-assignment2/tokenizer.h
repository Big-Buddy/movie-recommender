

#ifndef TOKENIZER_H_
#define TOKENIZER_H_
#include <string>
#include <vector>

using namespace std;

class tokenizer{


public:
    //! @brief A default constructor.
	tokenizer();

	~tokenizer();

    //! @brief A method to break down a string into a set of strings.
    /*!
     * @param s: the string to be broken down.
     * @return a vector<string>: the set of strings that make up s, minus whitespaces and punctuation.
     */
	vector<string> tokenize(string s);
};



#endif /* TOKENIZER_H_ */
