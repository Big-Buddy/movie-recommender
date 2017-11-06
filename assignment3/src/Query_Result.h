

#ifndef QUERY_STRING_H_
#define QUERY_STRING_H_
#include "vector"
#include "document.h"
#include "indexer.h"
#include "index_item.h"
#include "document_indexer.h"
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
	vector<pair<index_item*,double> > query(indexer & idx,string s,int n = 10);

	void printDocResults(indexer & idx,string s,int n = 10);

};


#endif /* QUERY_STRING_H_ */