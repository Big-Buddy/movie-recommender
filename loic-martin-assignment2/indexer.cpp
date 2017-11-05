#include "indexer.h"
#include <vector>
#include <iomanip>
#include <iostream>
#include <map>
#include <math.h>

using namespace std;

/*!
 * Initializes the indexer's N to 0, normalized to false, and stpw to a stopwords ("stopwords.txt").
 */
indexer::indexer()
:N(0),normalized(false),stpw(new stopwords("stopwords.txt"))
{

}

indexer::indexer(int size): N(size), normalized(false),stpw(new stopwords("stopwords.txt")) {}

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

vector<document> & indexer::getdocuments(){
	return documents;
}

vector<string> indexer::getDocumentNames(){
    vector<string> names;
    for(vector<document>::const_iterator documentsIterator = documents.begin(); documentsIterator != documents.end(); ++documentsIterator){
        string docName = documentsIterator->name();
        names.push_back(docName);
    }
    return names;
}

map<string, map<string, int> > & indexer::getTFtd2(){
	return tftd2;
}

map<string, map<string, double> > & indexer::getWtd(){
	return wtd;
}

/*!
 * Calculates the frequency of a token (how many documents it appears in).
 * Then, calculates the weight of a token in each document.
 */
void indexer::normalize(){
	normalized = true;
	// looping on the filtered tokens and calculating the document frequency for each token

	for(map<string, map<string, int> >::const_iterator it = tftd2.begin();it != tftd2.end();it++){
        //the word we're looking for
		string term = it->first;
		int df = 0;

        //the documents and their term frequency
        map<string, int> documentFrequency = it -> second;

        for(map<string, int>::const_iterator documentIterator = documentFrequency.begin(); documentIterator != documentFrequency.end(); ++documentIterator){
            int frequency = documentIterator->second;
            if(frequency > 0)
                ++df;
        }

		dft[term] = df;
	}

	wtd.clear();
	// looping on the filtered tokens and calculating the document weight wt,d for each token
	for(map<string, map<string, int> >::const_iterator it = tftd2.begin();it != tftd2.end();it++){
		string term = it->first;
        map<string, int> termFrequencies = it -> second;
        for(map<string, int>::const_iterator documentIterator = termFrequencies.begin(); documentIterator != termFrequencies.end(); documentIterator++){
            string docName = documentIterator->first;
            int termFreq = documentIterator->second;

            double size = getSize();
            double docFreq = dft[term];

            double weight = (1 + log(termFreq)) * (log(size/docFreq));

            //do not add weight if it's not a number
            if(weight == -INFINITY || weight == INFINITY || isnan(weight)){
                wtd[term][docName] = 0;
            } else {
                wtd[term][docName] = weight;
            }
        }
	}
}

/*!
 * Gets the indexer's n'th document.
 */
const document & indexer::operator [](int n){
	return documents[n];
}

/*!
 * Adds a new document to the indexer, then calculates term frequency for that document and normalizes the indexer.
 */
friend const document & indexer::operator >>(document & d,indexer & idx){
	idx.normalized = false; // reading new document so indexer not normalized
	idx.documents.push_back(d); // pushing document to documnet vector
	string cont = d.content(); // string content of document
	int total_1 = 0;
	int total_2 = 0;
	tokenizer* t = new tokenizer;
	vector<string> tokens = t->tokenize(cont); // changing the content of document into tokens
    string docName = d.name();
    vector<string> docNames = idx.getDocumentNames();

	for(int i=0;i<tokens.size();i++){
		string s = tokens[i];

        //first, add the token to every document's frequency. this will make things easier later on.
        for(vector<string>::const_iterator docNamesIt = docNames.begin(); docNamesIt != docNames.end(); ++docNamesIt){

            if(idx.tftd1[s].find(*docNamesIt) == idx.tftd1[s].end()){
                idx.tftd1[s][*docNamesIt] = 0;
            }
            if(!idx.stpw->operator ()(s)){
                if(idx.tftd2[s].find(*docNamesIt) == idx.tftd2[s].end()){
                    idx.tftd2[s][*docNamesIt] = 0;
                }
            }
        }

        //if the token is not a stopword, count it in tftd2
		if(!idx.stpw->operator ()(s)) {
            idx.tftd2[s][docName]++;
            total_2++;
		}
        idx.tftd1[s][docName]++;
        total_1++;
	}
	idx.total1[docName] = total_1;
	idx.total2[docName]= total_2;
	idx.normalize();
	idx.N++; // counter for index of which document is read
	delete t;
	return d;
}

/*!
 * Fills an outstream with the document matrices information (term frequency, weight etc.)
 */
friend ostream & indexer::operator <<(ostream & os,indexer & idx) {
    os << endl << "******* Full Document Matrix version *********" << endl;
    os << left << setw(20) << "Dictionary";
    int size = idx.getSize();

    //first, print the names row
    for (int i = 0; i < size; ++i) {
        os << right << setw(20) << idx[i].name();
    }
    os << endl;

    //then, print the term frequency by document
    for(map<string, map<string, int> >::const_iterator termIterator = idx.tftd1.begin(); termIterator != idx.tftd1.(); ++termIterator){
        string term = termIterator->first;
        map<string, int> docFrequency = termIterator->second;

        //print each document's frequency for the given term
        for(map<string, int>::const_iterator docIterator = docFrequency.begin(); docIterator!= docFrequency.end(); ++docIterator){
            int freq = docIterator->second;
            os << right << setw(20) << freq;
        }

        //then, new line for the next term.
        os << endl;
    }

    //After printing the frequencies, print the total number of words in each document
    os << left << setw(20) << "Total";
    for(map<string, int>::const_iterator totalIterator = idx.total1.begin(); totalIterator!= idx.total1.end(); ++totalIterator){
        os << right << setw(20) << totalIterator->second;
    }

    os << endl;
    os << endl << "******* Filtered Document Matrix version *********" << endl;
    os << left << setw(20) << "Dictionary";
    for (int i = 0; i < size; ++i) {
        os << right << setw(20) << idx[i].name();
    }
    os << endl;

    for(map<string, map<string, int> >::const_iterator termIterator = idx.tftd2.begin(); termIterator != idx.tftd2.(); ++termIterator){
        string term = termIterator->first;
        map<string, int> docFrequency = termIterator->second;

        //print each document's frequency for the given term
        for(map<string, int>::const_iterator docIterator = docFrequency.begin(); docIterator!= docFrequency.end(); ++docIterator){
            int freq = docIterator->second;
            os << right << setw(20) << freq;
        }

        //then, new line for the next term.
        os << endl;
    }


    os << left << setw(20) << "Total";
    for(map<string, int>::const_iterator totalIterator = idx.total2.begin(); totalIterator!= idx.total2.end(); ++totalIterator){
        os << right << setw(20) << totalIterator->second;
    }
    os << endl;


    os << endl << "******* Document Frequency *********" << endl;
    os << left << setw(20) << "Dictionary" << right << setw(20) << "Document Frequency" << endl;
    for (map<string, int>::iterator it = idx.dft.begin(); it != idx.dft.end(); ++it)
        os << left << setw(20) << it->first << right << setw(20) << it->second << endl;

    os << endl << "******* Tf-idf weight *********" << endl;
    os << left << setw(20) << "Dictionary";
    for (int i = 0; i < size; ++i) {
        os << right << setw(20) << idx[i].name();
    }
    os << endl;

    for (map<string, map<string, double> >::const_iterator it = idx.wtd.begin(); it != idx.wtd.end(); ++it) {
        string term = it->first;
        map<string, double> docWeight = it->second;

        os << left << setw(20) << term;
        for(map<string, double>::const_iterator weightIt = docWeight.begin(); weightIt != docWeight.end(); ++weightIt ){
            double weight = weightIt->second;
            os << right << setw(20) << weight;
        }
        os << endl;
    }

    return os;
}


