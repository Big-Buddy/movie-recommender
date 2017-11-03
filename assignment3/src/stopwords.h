

#ifndef STOPWORDS_H_
#define STOPWORDS_H_

#include <vector>
#include <string>
using namespace std;

class stopwords{

private:
	//! @brief A private string: the stopwords' file name.
	string filename;

	//! @brief A private vector<string>: a vector of stopword strings.
	vector<string> stopword;
public:
	//! @brief A default constructor.
	stopwords();

	~stopwords();

	//! @brief Anoter constructor.
	/*!
	 * @param filename: the filename of the stopwords to be constructed.
	 */
	stopwords(string filename);

	//! @brief an operator() overlead.
	/*!
	 * @param word: the work to check if it is a stopword or not.
	 * @return a boolean: whether or not the word input is a stopword.
	 */
	bool operator ()(string word);

};


#endif /* STOPWORDS_H_ */
