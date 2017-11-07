#include "indexer.h"
#include "document_indexer.h"
#include "document.h"
#include "Query_Result.h"
#include "sentence.h"
#include "sentence_tokenizer.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


int main(){
	document_indexer idx;
    indexer sentIdx;

    //first, get the index file name (file with all the other filenames in it
	cout << "Enter filename:" << endl;
	string filename;
	cin >> filename;
	fstream fin(filename.c_str());
	string docName;
    vector<document> docVec;
    int docNumCounter = 0;

    //then, read all these filenames into their own document, and add these documents to docVec
	while(fin >> docName){
		document doc(docName, docNumCounter);
        docVec.push_back(doc);
        ++docNumCounter;
	}

    vector<vector<sentence> > sentVecVec;
    vector<sentence> sentVec;
    sentence_tokenizer st;
    //add all the documents in docVec to the document_indexer, then create a sentence vector out of the document's contents.
    //then, add this sentence vector to a vector of all sentence vectors.
    for(vector<document>::iterator docit = docVec.begin(); docit != docVec.end(); ++docit){
        &*docit >> idx;

        sentVec = st.sentence_tokenize(docit->get_content(), docit->getDocNum());
        sentVecVec.push_back(sentVec);
    }

    //iterate through every single sentence, and add them to the indexer
    for(vector<vector<sentence> >::iterator sentVecIt = sentVecVec.begin(); sentVecIt != sentVecVec.end(); ++sentVecIt){
        for(vector<sentence>::iterator sentIt = sentVecIt->begin(); sentIt != sentVecIt->end(); ++sentIt){
            &*sentIt >> sentIdx;
        }
    }

    //print out the document_indexer for shit n giggles
	cout << idx;

	Query_Result q;
	string query = "";
	Query_Result sentQ;

	while(true){
        //ask the user for the query he wishes to search for
		cout << "\nEnter the query you want to search for or -1 to exit:" << endl;
		cin.ignore();
		getline(cin, query);
		if(query == "-1")
            break;

        //(for printing scores): ask the user how many scores he wants to print (will print the top n scores)
		cout << "Enter the number of documents for the top queries or -1 to skip:" << endl;
		int n;
		cin >> n;
		vector<pair<index_item*, double> > score;
		vector<pair<index_item*, double> > sentenceScore;

        //calculate the scores. I guess we don't really need to store them anywhere, since they're stored in query_result.score anyways, but it's whatever.
        score = q.query(idx, query);
        sentenceScore = sentQ.query(sentIdx, query);

        //depending on user input, print either the top n scores, or all of them (only does this for document_indexer, as indexer has no name, and thus cannot do this.
		if(n == -1) {
			q.printDocResults(idx, query);
        }
		else {
			q.printDocResults(idx, query, n);
		}

        string test = sentQ.generateEssayFromSentences(50);
        cout << endl << test << endl;
	}
	return 0;
}
