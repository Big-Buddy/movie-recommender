#include "tokenizer.h"
#include "stopwords.h"
#include <algorithm>
#include <sstream>
#include <iterator>

/*!
 * Is necessary for compilation.
 */
tokenizer::tokenizer(){ }

tokenizer::~tokenizer(){ }

/*!
 * The tokenize method takes a string s, and first breaks it into an vector by dividing words by whitespace.
 * It then takes every string in the vector, makes it lowercase and removes any punctuation. (i.e. 'i-e.F' would become 'ief').
 * It then adds the new string to a new vector.
 * Finally, it returns the new vector of lowercase words with no punctuation.
 */
vector<string> tokenizer::tokenize(string s)
{
	vector<string> temp;
	vector<string> tokens;
	stopwords stpw("stopwords.txt");
	istringstream iss(s);
	// splitting by whitespace and pushing to array temp
	copy(istream_iterator<string>(iss),istream_iterator<string>(),back_inserter(temp));
	for(int i=0;i<temp.size();i++){
		string s = temp[i];
		// to lowercase
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		// if the word is stop word push it as it is.
		if(stpw(s))
			tokens.push_back(s);
		// else remove punctuation
		else {
			string result;
			// remove punctuation
			remove_copy_if(s.begin(), s.end(),back_inserter(result), ptr_fun<int, int>(&std::ispunct));
			tokens.push_back(result);
		}
	}
	return tokens;

}


