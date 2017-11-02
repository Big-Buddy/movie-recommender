

#ifndef INDEXER_H_
#define INDEXER_H_

#include "document.h"
#include "stopwords.h"
#include "tokenizer.h"
#include <vector>
#include <iomanip>
#include <iostream>
#include <map>
#include <math.h>
using namespace std;

template<int size>
class indexer{

private:
	//! @brief A private  int: the number of documents.
	int N;

	//! @brief a private boolean: whether the indexer has been normalized.
	bool normalized;

	//! @brief a private stopwords: the stopwords the indexer should keep track of.
	stopwords *stpw;

	//! @brief a private vector of documents: the list of documents which's score the indexer should keep.
	vector<document> documents;

	//! @brief a private map of string, int: the total number of documents that a token appears in.
	map<string,int> dft;

	//! @brief a private map of string, vector<int>: the token frequency in documents represented by the vector<int>.
	/*!
	 * The string is the token. Every document will have a term frequency, which is stored in the vector<int>.
	 * The first int in the vector will be the first document's frequency, etc...
	 */
	map<string,vector<int> > tftd1;

	//! @brief a private map of string, vector<int>: The same as tftd1, but with stopwords removed.
	map<string,vector<int> > tftd2;

	//! @brief a private map of string, vector<double>: the weight of each token in each document, stored similarly to tftd1 but for weight instead of frequency.
	map<string,vector<double> > wtd;

	//! @brief a private vector int: the total number of words per document, stored similarly to the vector<int> in tftd1.
	vector<int>total1;

	//! @brief a private vector int: the same as total1, but without stopwords.
	vector<int>total2;
public:
	//! @brief a default constructor.
	/*!
	 * Initializes the indexer's N to 0, normalized to false, and stpw to a stopwords ("stopwords.txt").
	 */
	indexer<size>()
	:N(0),normalized(false),stpw(new stopwords("stopwords.txt"))
	{

	}

	~indexer<size>(){
		delete stpw;
	}

	//! @brief an accessor for size.
	/*!
	 * @return the size of the indexer.
	 */
	int indexersize(){
		return size;
	}

	//! @brief an accessor for normalize.
	/*!
	 * @return if the indexer is normalized.
	 */
	bool isNormalize(){
		return normalized;
	}

	//! @brief an accessor for stpw.
	/*!
	 * @return the indexer's stopwords.
	 */
	stopwords* getstpw(){
		return stpw;
	}

	//! @brief an accessor for documents.
	/*!
	 * @return the documents in indexer.
	 */
	vector<document> & getdocuments(){
		return documents;
	}

	//! @brief an accessor for tftd2.
	/*!
	 * @return the indexer's tftd2.
	 */
	map<string,vector<int> > & getTFtd2(){
		return tftd2;
	}

	//! @brief an accessor for wtd.
	/*!
	 * @return the indexer's wtd.
	 */
	map<string,vector<double> > & getWtd(){
		return wtd;
	}

	//! @brief a function which normalizes the indexer.
	/*!
	 * Calculates the frequency of a token (how many documents it appears in).
	 * Then, calculates the weight of a token in each document.
	 */
	void normalize(){
		normalized = true;
		// looping on the filtered tokens and calculating the document frequency for each token
		for(map<string, vector<int> >::const_iterator it = tftd2.begin();it != tftd2.end();it++){
			string t = it->first;
			int df = 0;
			for(int j=0;j<tftd2[t].size();j++){
				if(tftd2[t][j] > 0)
					df++;
			}
			dft[t] = df;
		}

		wtd.clear();
		// looping on the filtered tokens and calculating the document weight wt,d for each token
		for(map<string, vector<int> >::const_iterator it = tftd2.begin();it != tftd2.end();it++){
			string t = it->first;
			for(int j=0;j<tftd2[t].size();j++){
				// formula from assignment
				double s = indexersize();
				double d = dft[t];
				double tf = tftd2[t][j];
				double temp1 = 1+((double)log(tf)/(double)log(10));
				double temp2 = (double)log(s/d)/(double)log(10);
				double Wtd = temp1*temp2;
				if(Wtd == -INFINITY || Wtd == INFINITY || isnan(Wtd))
					wtd[t].push_back(0);
				else
					wtd[t].push_back(Wtd);
			}
		}
	}

	//! @brief an operator[] overload.
	/*!
	 * Gets the indexer's n'th document.
	 * @param n: an int index.
	 * @return the document at index n.
	 */
	const document & operator [](int n){
		return documents[n];
	}

	//! @brief an operator>> overload.
	/*!
	 * Adds a new document to the indexer, then calculates term frequency for that document and normalizes the indexer.
	 * @param d: the document to add to the indexer.
	 * @param idx: the indexer to which we are adding a document.
	 * @return the document d.
	 */
	friend const document & operator >>(document & d,indexer<size> & idx){
		idx.normalized = false; // reading new document so indexer not normalized
		idx.documents.push_back(d); // pushing document to documnet vector
		string cont = d.content(); // string content of document
		int total_1 = 0;
		int total_2 = 0;
		tokenizer* t = new tokenizer;
		vector<string> tokens = t->tokenize(cont); // changing the content of document into tokens

		// same as assignment 1 pushing zeros then incrementing the token
		for(int i=0;i<tokens.size();i++){
			string s = tokens[i];
			if(idx.stpw->operator ()(s)){
			if(idx.tftd1[s].size() == 0){
			for(int i=0;i<size;i++){
					idx.tftd1[s].push_back(0);
				}
			}
			idx.tftd1[s][idx.N]++;
			total_1++;
			}
			else{
				if(idx.tftd1[s].size() == 0){
				for(int i=0;i<size;i++){
						idx.tftd1[s].push_back(0);
					}
				}
				idx.tftd1[s][idx.N]++;

				if(idx.tftd2[s].size() == 0){
				for(int i=0;i<size;i++){
						idx.tftd2[s].push_back(0);
					}
				}
				idx.tftd2[s][idx.N]++;
				total_1++;
				total_2++;
			}
		}
		idx.total1.push_back(total_1);
		idx.total2.push_back(total_2);
		idx.normalize();
		idx.N++; // counter for index of which document is read
		delete t;
		return d;
	}

	//! @brief an operator<< overload
	/*!
	 * Fills an outstream with the document matrices information (term frequency, weight etc.)
	 * @param os: the outstream which will receive the matrix information
	 * @param idx: the indexer from which we take information
	 * @return the outstream with matrix information.
	 */
	friend ostream & operator <<(ostream & os,indexer<size> & idx){
		os << endl << "******* Full Document Matrix version *********" <<endl;
			os << left << setw(20) << "Dictionary";
			for(int i=0;i<size;++i){
				os << right << setw(20) << idx[i].name();
			}
			os << endl;
			for(map<string,vector<int> >::iterator it = idx.tftd1.begin();it != idx.tftd1.end();++it){
				os << left << setw(20) << it->first;
				for(int i=0;i<it->second.size();i++){
					os << right << setw(20) << it->second[i];
				}
				os << endl;
			}
			os << left << setw(20) << "Total";
			for(int i=0;i<idx.total1.size();i++){
				os << right << setw(20) << idx.total1[i];
			}
			os << endl;
			os << endl << "******* Filtered Document Matrix version *********" <<endl;
			os << left << setw(20) << "Dictionary";
			for(int i=0;i<size;++i){
				os << right << setw(20) << idx[i].name();
			}
			os << endl;
			for(map<string,vector<int> >::iterator it = idx.tftd2.begin();it != idx.tftd2.end();++it){
				os << left << setw(20) << it->first;
				for(int i=0;i<it->second.size();i++){
					os << right << setw(20) << it->second[i];
				}
				os << endl;
			}
			os << left << setw(20) << "Total";
			for(int i=0;i<idx.total2.size();i++){
				os << right << setw(20) << idx.total2[i];
			}
			os << endl;
			os << endl << "******* Document Frequency *********" <<endl;
			os << left << setw(20) << "Dictionary" <<  right << setw(20) << "Document Frequency" << endl;
			for(map<string,int >::iterator it = idx.dft.begin();it != idx.dft.end();++it)
			os << left << setw(20) << it->first << right << setw(20) << it->second << endl;

			os << endl << "******* Tf-idf weight *********" <<endl;
			os << left << setw(20) << "Dictionary";
			for(int i=0;i<size;++i){
				os << right << setw(20) << idx[i].name();
			}
			os << endl;
			for(map<string,vector<double> >::iterator it = idx.wtd.begin();it != idx.wtd.end();++it){
				os << left << setw(20) << it->first;
				for(int i=0;i<it->second.size();i++){
					os << right << setw(20) << it->second[i];
				}
				os << endl;
			}

				return os;
	}

	//! @brief an exception to be thrown when attemptin to query an un-normalized indexer.
	enum Exceptions { INDEX_NOT_NORMALIZED };

};

//! @brief Compares two document-double pairs
/*!
 * @param a: the first score pair
 * @param b: the second score pair
 * @return a boolean: whether the a's score is greater than b's
 */
bool sortpairs(const pair<document,double> &a,const pair<document,double> &b);


#endif /* INDEXER_H_ */


