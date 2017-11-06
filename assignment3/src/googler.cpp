//Authors
// Martin Spasov 40000916
// Mohamed Omar 40013242
// Loic Huss - 40000298
#include "indexer.h"
#include "document_indexer.h"
#include "document.h"
#include "Query_Result.h"
#include <iostream>
#include <fstream>
using namespace std;


int main(){
	document_indexer idx;
	cout << "Enter filename:" << endl;
	string filename;
	cin >> filename;
	fstream fin(filename.c_str());
	string docName;
	while(fin >> docName){
		document doc(docName);
		doc >> idx;
	}

	cout << idx;

	Query_Result q;
	string query = "";

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
		if(n == -1)
			score = q.query(idx,query);
		else
			score = q.query(idx,query,n);
	}
	return 0;
}
