#include "indexer.h"
#include <vector>
#include <iomanip>
#include <iostream>
#include <map>
#include <cmath>

using namespace std;

/*!
 * Initializes the indexer's N to 0, normalized to false, and stpw to a stopwords ("stopwords.txt").
 */
indexer::indexer()
:N(0),normalized(false),stpw(new stopwords("stopwords.txt"))
{

}

indexer::~indexer(){
	delete stpw;
}

/*!
 * a function to return the size of the indexer
 */
int indexer::getSize(){
	return N;
}

/*!
 * Checks if the indexer is normalized
 */
bool indexer::isNormalize(){
	return normalized;
}

stopwords* indexer::getstpw(){
	return stpw;
}

map<string,int> & indexer::getDft(){
	return dft;
};

vector<index_item*> & indexer::getItems(){
	return items;
}

map<string, map<index_item*, int> > & indexer::getTFtd1(){
	return tftd1;
}

map<string, map<index_item*, int> > & indexer::getTFtd2(){
	return tftd2;
}

map<string, map<index_item*, double> > & indexer::getWtd(){
	return wtd;
}

map<index_item*, int> & indexer::getTotal1(){
	return total1;
};

map<index_item*, int> & indexer::getTotal2(){
	return total2;
};

/*!
 * Calculates the frequency of a token (how many documents it appears in).
 * Then, calculates the weight of a token in each document.
 */
void indexer::normalize(){
	normalized = true;
	// looping on the filtered tokens and calculating the document frequency for each token

	for(map<string, map<index_item*, int> >::const_iterator it = tftd2.begin();it != tftd2.end();it++){
        //the word we're looking for
		string term = it->first;
		int df = 0;

        //the documents and their term frequency
        map<index_item*, int> documentFrequency = it -> second;

        for(map<index_item*, int>::const_iterator documentIterator = documentFrequency.begin(); documentIterator != documentFrequency.end(); ++documentIterator){
            int frequency = documentIterator->second;
            if(frequency > 0)
                ++df;
        }

		dft[term] = df;
	}

	wtd.clear();
	// looping on the filtered tokens and calculating the document weight wt,d for each token
	for(map<string, map<index_item*, int> >::const_iterator it = tftd2.begin();it != tftd2.end();it++){
		string term = it->first;
        map<index_item*, int> termFrequencies = it -> second;
        for(map<index_item*, int>::const_iterator documentIterator = termFrequencies.begin(); documentIterator != termFrequencies.end(); documentIterator++){
            index_item* item = documentIterator->first;
            int termFreq = documentIterator->second;

            double size = getSize();
            double docFreq = dft[term];

            double weight = (1 + log(termFreq)) * (log(size/docFreq));

            //do not add weight if it's not a number
            if(weight == -INFINITY || weight == INFINITY || isnan(weight)){
                wtd[term][item] = 0;
            } else {
                wtd[term][item] = weight;
            }
        }
	}
}

/*!
 * Gets the indexer's n'th document.
 */
index_item* indexer::operator [](int n){
	return items[n];
}

/*!
 * Adds a new document to the indexer, then calculates term frequency for that document and normalizes the indexer.
 */
index_item & operator >>(index_item * item, indexer & idx){
	idx.normalized = false; // reading new item so indexer not normalized
	idx.items.push_back(item); // pushing item to documnet vector
	string cont = item->get_content(); // string content of document
	int total_1 = 0;
	int total_2 = 0;
	word_tokenizer t;
	vector<string> tokens = t.word_tokenize(cont); // changing the content of document into tokens

	for(int i=0;i<tokens.size();i++){
		string s = tokens[i];

        //if the token is not a stopword, count it in tftd2
		if(!idx.stpw->operator ()(s)) {
            idx.tftd2[s][item]++;
            total_2++;
		}
        idx.tftd1[s][item]++;
        total_1++;
	}
	idx.total1[item] = total_1;
	idx.total2[item]= total_2;
	idx.N++; // counter for index of which document is read
	return *item;
}




