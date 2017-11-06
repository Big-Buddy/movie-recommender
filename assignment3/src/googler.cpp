//Authors
// Martin Spasov 40000916
// Mohamed Omar 40013242
// Loic Huss - 40000298
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
	cout << "Enter filename:" << endl;
	string filename;
	cin >> filename;
	fstream fin(filename.c_str());
	string docName;
    vector<document> docVec;
    int docNumCounter = 0;
	while(fin >> docName){
		document doc(docName, docNumCounter);
        docVec.push_back(doc);
        ++docNumCounter;
	}

    vector<vector<sentence> > sentVecVec;
    vector<sentence> sentVec;
    sentence_tokenizer st;
    for(vector<document>::iterator docit = docVec.begin(); docit != docVec.end(); ++docit){
        &*docit >> idx;
        sentVec = st.sentence_tokenize(docit->get_content(), docit->getDocNum());
        sentVecVec.push_back(sentVec);
    }

    for(vector<vector<sentence> >::iterator sentVecIt = sentVecVec.begin(); sentVecIt != sentVecVec.end(); ++sentVecIt){
        for(vector<sentence>::iterator sentIt = sentVecIt->begin(); sentIt != sentVecIt->end(); ++sentIt){
            &*sentIt >> sentIdx;
        }
    }

	cout << idx;

	Query_Result q;
	string query = "";
	Query_Result sentQ;

	while(true){
		cout << "\nEnter the query you want to search for or -1 to exit:" << endl;
		cin.ignore();
		getline(cin, query);
		if(query == "-1")
            break;
		cout << "Enter the number of documents for the top queries or -1 to skip:" << endl;
		int n;
		cin >> n;
		vector<pair<index_item*, double> > score;
		vector<pair<index_item*, double> > sentenceScore;
		if(n == -1) {
            score = q.query(idx, query);
			q.printDocResults(idx, query);
			sentenceScore = sentQ.query(sentIdx, query);
        }
		else {
            score = q.query(idx, query, n);
			q.printDocResults(idx, query, n);
			sentenceScore = sentQ.query(sentIdx, query, n);
		}
	}
	return 0;
}
