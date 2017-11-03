//Authors
// Martin Spasov 40000916
// Mohamed Omar 40013242
// Loic Huss - 40000298
#include "indexer.h"
#include "document.h"
#include "Query_Result.h"
#include <iostream>
#include <fstream>
using namespace std;


int main(){
	const int size = 3;
	indexer<size>* idx = new indexer<size>;
	cout << "Enter filename:" << endl;
	string filename;
	cin >> filename;
	fstream fin(filename.c_str());
	for(int i=0;i<size;i++){
		string d;
		fin >> d;
		document* doc = new document(d);
		*doc >> *idx;
		delete doc;
	}
	cout << *idx;
	Query_Result* q = new Query_Result;
	string query = "";

	while(true){
		cout << "\nEnter query you want to search for or -1 to exit:" << endl;
		cin.ignore();
		getline(cin, query);
		if(query == "-1")break;
		cout << "Enter number of documents for the top queries or -1 to skip:" << endl;
		int n;
		cin >> n;
		if(n == -1)
		q->query(*idx,query);
		else
		q->query(*idx,query,n);
	}
	delete q;
	delete idx;
	return 0;
}
