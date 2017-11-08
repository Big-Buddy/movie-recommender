////Authors
//// Alexandre Pelletier - 27259492
//// Martin Spasov 40000916
//// Loic Huss - 40000298
//#include "indexer.h"
//#include "document_indexer.h"
//#include "document.h"
//#include "Query_Result.h"
//#include "sentence.h"
//#include "sentence_tokenizer.h"
//#include <iostream>
//#include <fstream>
//#include <vector>
//using namespace std;
//
//int main() {
//    document_indexer idx;
//
//    //first, get the index file name (file with all the other filenames in it
//    cout << "Enter filename:" << endl;
//    string filename;
//    cin >> filename;
//    fstream fin(filename.c_str());
//    string docName;
//    vector<document> docVec;
//    int docNumCounter = 0;
//
//    //then, read all these filenames into their own document, and add these documents to docVec
//    while(fin >> docName){
//        document doc(docName, docNumCounter);
//        docVec.push_back(doc);
//        ++docNumCounter;
//    }
//
//    //add all the documents in docVec to the document_indexer, then create a sentence vector out of the document's contents.
//    //then, add this sentence vector to a vector of all sentence vectors.
//    for(vector<document>::iterator docit = docVec.begin(); docit != docVec.end(); ++docit){
//        &*docit >> idx;
//    }
//    //print out the document_indexer for shit n giggles
//    cout << idx;
//
//    return 0;
//}
