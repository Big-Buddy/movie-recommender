

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

	const index_item & operator [](string name);
};

#endif /* _DOCUMENT_INDEXER_H_ */


