#ifndef INDEXER_H_INCLUDED
#define INDEXER_H_INCLUDED

#include "query_result.h"
#include "document.h"
#include "dictionary_entry.h"

#include <vector>
#include <string>

class indexer
{

public:
    indexer(std::vector<document> docs, std::vector<dictionary_entry> dic);
    std::vector<query_result> query(const std::string &the_query, int num_of_results = 10);
    void normalize();
    std::map<std::string,double> normalize(std::vector<std::string>);
    bool is_normalized();
    document operator[](int i);
    friend indexer &operator>>(indexer &index, document &doc);
    int size();
private:
    std::vector<document> complete_documents;
    std::vector<dictionary_entry> complete_dictionary;
    bool normalized;
};

#endif
