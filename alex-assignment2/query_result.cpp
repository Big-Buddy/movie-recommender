#include "query_result.h"

using namespace std;

query_result::query_result(document &da_doc, double &da_score)
                            :doc(da_doc)
{
    doc = da_doc;
    score = da_score;
}

document query_result::get_doc()
{
    return doc;
}
double query_result::get_score()
{
    return score;
}
