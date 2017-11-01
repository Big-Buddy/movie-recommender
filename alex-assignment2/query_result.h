#ifndef QUERY_RESULT_H_INCLUDED
#define QUERY_RESULT_H_INCLUDED

#include "document.h"

class query_result
{
    friend class indexer;
public:
    query_result(document &da_doc, double &da_score);
    document get_doc();
    double get_score();
private:
    document doc;
    double score;
};

#endif
