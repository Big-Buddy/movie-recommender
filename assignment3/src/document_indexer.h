

#ifndef _DOCUMENT_INDEXER_H_
#define _DOCUMENT_INDEXER_H_

#include "indexer.h"
#include "index_item.h"
#include "stopwords.h"
#include "word_tokenizer.h"
#include "document.h"
#include <vector>
#include <iomanip>
#include <iostream>
#include <map>
#include <math.h>
using namespace std;

class document_indexer: public indexer {

public:
	//! @brief a default constructor.
	document_indexer();

	~document_indexer();

	//!@brief gets the documents names
	/*!
     * @return the names of the documents in indexer
     */
	vector<string> getDocumentNames();

	index_item* operator [](string name);

	//! @brief an operator<< overload
	/*!
	 * @param os: the outstream which will receive the matrix information
	 * @param idx: the indexer from which we take information
	 * @return the outstream with matrix information.
	 */
	friend ostream & operator <<(ostream & os, document_indexer & idx);
};

#endif /* _DOCUMENT_INDEXER_H_ */


