#include "document.h"
#include "dictionary_entry.h"
#include "indexer.h"
#include "query_result.h"

using namespace std;

//int main()
//{
//    vector<document> documentVector1 = tokenizer::initialize_documents("input.txt");
//    vector<dictionary_entry> dictionaryVector1 = document::process_documents(documentVector1);
//    indexer idx = indexer(documentVector1, dictionaryVector1);
//    string user_query;
//    cout << "Enter your query:" << endl;
//    cin >> user_query;
//    vector<query_result> GOOGLE_DOT_COM = idx.query(user_query);
//
//    return 0;
//}
