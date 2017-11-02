
#include "stopwords.h"
#include <fstream>

/*!
 * The default constructor does nothing in this case, since we have no use for an empty stopwords object.
 */
stopwords::stopwords() { }

stopwords::~stopwords(){ }

/*!
 * The other constructor takes a string fname and sets it as its filename.
 * It then creates a filestream from the filename, and reads every word in the filestream into the stopword vector.
 */
stopwords::stopwords(string fname)
	:filename(fname)
{
	ifstream fin(filename);
	string words;
	while(fin >> words){
		stopword.push_back(words);
	}

}

/*!
 * The overloaded operator() takes a word, and returns true if the work is in the stopword vector.
 * Else, it returns false;
 */
bool stopwords::operator ()(string word)
{

	for(string w:stopword){
		if(w == word)return true;
	}
	return false;
}


