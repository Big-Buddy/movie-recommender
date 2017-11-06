#include "document_indexer.h"
#include <vector>
#include <iomanip>
#include <iostream>
#include <map>
#include <math.h>

using namespace std;

/*!
 * Initializes the indexer's N to 0, normalized to false, and stpw to a stopwords ("stopwords.txt").
 */
document_indexer::document_indexer():indexer()
{}

document_indexer::~document_indexer(){
}


index_item* document_indexer::operator [](string name){
    for(vector<index_item*>::iterator itemsIt = getItems().begin(); itemsIt != getItems().end(); ++itemsIt){
        document *doc = dynamic_cast<document*>(*itemsIt);
        if(doc->name() == name){
            return doc;
        }
    }
}

vector<string> document_indexer::getDocumentNames(){
    vector<string> names;

    for(vector<index_item*>::const_iterator itemsIt = getItems().begin(); itemsIt != getItems().end(); ++itemsIt){
        document *doc = dynamic_cast<document*>(*itemsIt);

        string docName = doc->name();
        names.push_back(docName);
    }
    return names;
}

/*!
 * Fills an outstream with the document matrices information (term frequency, weight etc.)
 */
ostream & operator <<(ostream & os,document_indexer & idx) {
    os << endl << "******* Full Document Matrix version *********" << endl;
    os << left << setw(20) << "Dictionary";
    int size = idx.getSize();


    vector<string> documentNames = idx.getDocumentNames();

    //first, print the names row
    for(vector<index_item*>::iterator itemIt = idx.getItems().begin(); itemIt != idx.getItems().end(); ++itemIt){
        document *doc = dynamic_cast<document*>(*itemIt);

        os << right << setw(20) << doc->name();
    }
    os << endl;

    //then, print the term frequency by document
    for(map<string, map<index_item*, int> >::const_iterator termIterator = idx.getTFtd1().begin(); termIterator != idx.getTFtd1().end(); ++termIterator){
        string term = termIterator->first;
        map<index_item*, int> itemFreq = termIterator->second;
        //print the term
        os << left << setw(20) << term;

        //print each document's frequency for the given term
        for(vector<index_item*>::const_iterator itemIt = idx.getItems().begin(); itemIt != idx.getItems().end(); ++itemIt){
            int freq;
            if(isnan(itemFreq[*itemIt])){
                freq = 0;
            }else{
                freq = itemFreq[*itemIt];
            }
            os << right << setw(20) << freq;
        }

        //then, new line for the next term.
        os << endl;
    }

    //After printing the frequencies, print the total number of words in each document
    os << left << setw(20) << "Total";
    for(map<index_item*, int>::const_iterator totalIterator = idx.getTotal1().begin(); totalIterator!= idx.getTotal1().end(); ++totalIterator){
        os << right << setw(20) << totalIterator->second;
    }

    os << endl;
    os << endl << "******* Filtered Document Matrix version *********" << endl;
    os << left << setw(20) << "Dictionary";

    for(vector<index_item*>::iterator itemIt = idx.getItems().begin(); itemIt != idx.getItems().end(); ++itemIt){
        document *doc = dynamic_cast<document*>(*itemIt);

        os << right << setw(20) << doc->name();
    }
    os << endl;

    for(map<string, map<index_item*, int> >::const_iterator termIterator = idx.getTFtd2().begin(); termIterator != idx.getTFtd2().end(); ++termIterator){
        string term = termIterator->first;
        map<index_item*, int> itemFreq = termIterator->second;

        //print the term
        os << left << setw(20) << term;

        //print each document's frequency for the given term
        for(vector<index_item*>::const_iterator itemIt = idx.getItems().begin(); itemIt != idx.getItems().end(); ++itemIt){
            int freq;
            if(isnan(itemFreq[*itemIt])){
                freq = 0;
            }else{
                freq = itemFreq[*itemIt];
            }
            os << right << setw(20) << freq;
        }

        //then, new line for the next term.
        os << endl;
    }


    os << left << setw(20) << "Total";
    for(map<index_item*, int>::const_iterator totalIterator = idx.getTotal2().begin(); totalIterator!= idx.getTotal2().end(); ++totalIterator){
        os << right << setw(20) << totalIterator->second;
    }
    os << endl;


    os << endl << "******* Document Frequency *********" << endl;
    os << left << setw(20) << "Dictionary" << right << setw(20) << "Document Frequency" << endl;
    for (map<string, int>::const_iterator it = idx.getDft().begin(); it != idx.getDft().end(); ++it) {
        string word = it->first;
        int frequency = it->second;

        os << left << setw(20) << word << right << setw(20) << frequency << endl;
    }

    os << endl << "******* Tf-idf weight *********" << endl;
    os << left << setw(20) << "Dictionary";
    for(vector<index_item*>::iterator itemIt = idx.getItems().begin(); itemIt != idx.getItems().end(); ++itemIt){
        document *doc = dynamic_cast<document*>(*itemIt);

        os << right << setw(20) << doc->name();
    }
    os << endl;

    for (map<string, map<index_item*, double> >::const_iterator it = idx.getWtd().begin(); it != idx.getWtd().end(); ++it) {
        string term = it->first;
        map<index_item*, double> docWeight = it->second;

        os << left << setw(20) << term;

        //print each document's weight for the given term
        for(vector<index_item*>::const_iterator itemIt = idx.getItems().begin(); itemIt != idx.getItems().end(); ++itemIt){
            double weight;
            if(isnan(docWeight[*itemIt])){
                weight = 0;
            }else{
                weight = docWeight[*itemIt];
            }
            os << right << setw(20) << weight;
        }

        os << endl;
    }

    return os;
}


