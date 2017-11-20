#ifndef QUERY_STRING_H_
#define QUERY_STRING_H_
#include "vector"
#include "document.h"
#include "indexer.h"
#include "index_item.h"
#include "document_indexer.h"
#include "sentence.h"
#include <algorithm>
using namespace std;


class Query_Result{

private:
	//! @brief A private vector of document-double pairs, which tracks the score of several documents.
	/*!
    * Every document's score is stored as its own document-double pair.
    * All documents' scores are then added to the score vector.
    */
	vector<pair<index_item*,double> > score;
public:
	//! @brief The default constructor.
	Query_Result();

	//! @brief The default destructor
	~Query_Result();

	//! @brief An accessor for the score.
	/*!
	 * @return The score of the query result.
	 */
	const vector<pair<index_item*,double> > & scorevector();

	//! @brief A function to apply a query and return a result.
	/*!
	 * @tparam size: the size of indexer.
	 * @param idx: The indexer on which the query will be applied
	 * @param s: A string that is to be searched for in the indexer.
	 * @param n: an optional int to delimit the amount of results printed out, default is 10.
	 * @return the score
	 */
	void query(indexer & idx,string s);

    //! @brief A function to print information about the documents found in indexer.
	/*!
	 * @param idx: the indexer to be used
	 * @param s: the given query
	 * @param n: the top-n documents to be returned
	 * @return the score
	 */
	void printDocResults(document_indexer & idx,string s,int n = 10);

	//! @brief A function to generate an essay from our queried sentences.
	/*!
	 * @param wordCount: the maximum number of words for the essay
	 * @return the score
	 */
	string generateEssayFromSentences(int wordCount) const;

};


#endif /* QUERY_STRING_H_ */
