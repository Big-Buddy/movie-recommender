#ifndef INDEXER_H_
#define INDEXER_H_

#include "index_item.h"
#include "stopwords.h"
#include "word_tokenizer.h"
#include <vector>
#include <iomanip>
#include <iostream>
#include <map>
#include <math.h>
using namespace std;

class indexer{

protected:
	//! @brief A private  int: the number of index items.
	int N;

	//! @brief a private boolean: whether the indexer has been normalized.
	bool normalized;

	//! @brief a private stopwords: the stopwords the indexer should keep track of.
	stopwords *stpw;

	//! @brief a private vector of documents: the list of documents which's score the indexer should keep.
	vector<index_item*> items;

	//! @brief a private map of string, int: the total number of documents that a token appears in. (Document Frequency)
	map<string,int> dft;

	//! @brief a private map of string, pair<string, int> vector: the token frequency in documents. The pair is document name - weight in that document
	map<string, map<index_item*, int> > tftd1;

	//! @brief a private map of string, pair<string, int> vector: The same as tftd1, but with stopwords removed.
	map<string, map<index_item*, int> > tftd2;

	//! @brief a private map of string, pair<string, double> vector: the weight of each token in each document, stored similarly to tftd1 but for weight instead of frequency.
	map<string, map<index_item*, double> > wtd;

	//! @brief a private pair vector: the total number of words per document, stored similarly to the weight in tftd1.
    map<index_item*, int> total1;

	//! @brief a private pair vector: the same as total1, but without stopwords.
    map<index_item*, int> total2;
public:
	//! @brief a default constructor.
	indexer();

	virtual ~indexer();

	//! @brief an accessor for size.
	/*!
	 * @return the size of the indexer.
	 */
	int getSize();

	//! @brief an accessor for normalize.
	/*!
	 * @return if the indexer is normalized.
	 */
	bool isNormalize();

	//! @brief an accessor for stpw.
	/*!
	 * @return the indexer's stopwords.
	 */
	stopwords* getstpw();

	//! @brief an accessor for documents.
	/*!
	 * @return the documents in indexer.
	 */
	vector<index_item*> & getItems();

    //! @brief an accessor for dft.
    /*!
     * @return the dft of indexer.
     */
    map<string,int> & getDft();

    //! @brief an accessor for tftd1.
    /*!
     * @return the indexer's tftd1.
     */
    map<string, map<index_item*, int> > & getTFtd1();

	//! @brief an accessor for tftd2.
	/*!
	 * @return the indexer's tftd2.
	 */
    map<string, map<index_item*, int> > & getTFtd2();

	//! @brief an accessor for wtd.
	/*!
	 * @return the indexer's wtd.
	 */
    map<string, map<index_item*, double> > & getWtd();

    //! @brief an accessor for total1.
    /*!
     * @return the indexer's total1.
     */
    map<index_item*, int> & getTotal1();

    //! @brief an accessor for total2.
    /*!
     * @return the indexer's total2.
     */
    map<index_item*, int> & getTotal2();

	//! @brief a function which normalizes the indexer.
	void normalize();

	//! @brief an operator[] overload.
	/*!
	 * @param n: an int index.
	 * @return the document at index n.
	 */
	index_item* operator [](int n);


	//! @brief an operator>> overload.
	/*!
	 * @param d: the document to add to the indexer.
	 * @param idx: the indexer to which we are adding a document.
	 * @return the document d.
	 */
	friend index_item & operator >>(index_item * d,indexer & idx);


	//! @brief an exception to be thrown when attemptin to query an un-normalized indexer.
    enum Exceptions { INDEX_NOT_NORMALIZED };

};

//! @brief Compares two document-double pairs
/*!
 * @param a: the first score pair
 * @param b: the second score pair
 * @return a boolean: whether the a's score is greater than b's
 */
bool sortpairs(const pair<index_item,double> &a,const pair<index_item,double> &b);


#endif /* INDEXER_H_ */


