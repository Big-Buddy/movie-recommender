#include "indexer.h"
#include "document.h"
#include "tokenizer.h"

#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <cmath>

using namespace std;

indexer::indexer(vector<document> docs, vector<dictionary_entry> dic)
{
    complete_documents = docs;
    complete_dictionary = dic;
    normalized = false;
}

int indexer::size()
{
    return complete_documents.size();
}

bool indexer::is_normalized()
{
    return normalized;
}

indexer &operator>>(indexer &index, document &doc)
{
    index.complete_documents.push_back(doc);
    index.normalized = false;
    return index;
}

document indexer::operator[](int i)
{
    return complete_documents[i];
}

map<string,double> indexer::normalize(vector<string> inputQuery)
{
    map<string,double> query_weight;
    for (vector<string>::iterator queryit = inputQuery.begin();
            queryit != inputQuery.end(); ++queryit)
    {
        if (query_weight.count(*queryit))
        {
            query_weight[*queryit] += 1;
        }
        else
        {
            query_weight[*queryit] = 1;
        }
    }
    return query_weight;
}

void indexer::normalize()
{
    for (vector<document>::iterator docit = complete_documents.begin();
            docit != complete_documents.end(); ++docit)
    {
        for (map<string,int>::iterator mapit = (docit->words_found).begin();
            mapit != (docit->words_found).end(); ++mapit)
        {
            int termfreq = (docit->words_found)[mapit->first];
            int docfreq = 0;

            string finder = (mapit->first);
            vector<dictionary_entry>::iterator it = find_if(complete_dictionary.begin(), complete_dictionary.end(),
                                                                                [finder](dictionary_entry const &n)
                                                                                {
                                                                                    return n.word == finder;
                                                                                });

            for (vector<int>::iterator vecit = it->count_per_document.begin();
                vecit != it->count_per_document.end(); ++vecit)
            {
                if (*vecit > 0)
                    docfreq++;
            }

            //cout << (1+log(termfreq))*log(complete_documents.size()/docfreq) << endl;
            mapit->second = (1+log(termfreq))*log(complete_documents.size()/docfreq);
        }
    }

    normalized = true;
}

vector<query_result> indexer::query(const string &the_query, int num_of_results)
{
    normalize();

    if (is_normalized())
    {
        //process the query
        vector<string> QUERY_TOKENS;
        istringstream iss(the_query);
        copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(QUERY_TOKENS));

        map<string,double> NORMALIZED_QUERY = normalize(QUERY_TOKENS);

        vector<query_result> RESULTS;

        for (vector<document>::iterator docit = complete_documents.begin();
            docit != complete_documents.end(); ++docit)
        {
            double score;
            double numerator = 0;
            double denominator1 = 0;
            double denominator2 = 0;

            //calculate numerator
            for (map<string,double>::iterator tokit = NORMALIZED_QUERY.begin();
                tokit != NORMALIZED_QUERY.end(); ++tokit)
            {
                //check if it exists in document
                map<string,int>::iterator it = (docit->words_found).find(tokit->first);
                //if it exists, add value to all three preliminary score buffers
                if (it != (docit->words_found).end())
                {
                    //cout << (tokit->second) << endl;
                    //cout << (docit->words_weight)[tokit->first] << endl;
                    numerator += (tokit->second) * (docit->words_weight)[tokit->first];
                    denominator1 += sqrt(pow((tokit->second),2));
                    denominator2 += sqrt(pow((docit->words_weight)[tokit->first],2));
                    //cout << numerator << endl;
                    //cout << denominator1 << endl;
                    //cout << denominator2 << endl;
                }
            }

            score = numerator/(denominator1*denominator2);
            query_result NEW_RESULT = query_result(*docit, score);
            RESULTS.push_back(NEW_RESULT);
        }


        sort(RESULTS.begin(), RESULTS.end(),
         [](query_result lhs, query_result rhs){return lhs.score > rhs.score;});

         RESULTS.erase(RESULTS.begin()+num_of_results, RESULTS.end());

        return RESULTS;
    }
    else
    {
        throw "This index has not been normalized!";
    }
}

int main()
{
    vector<document> documentVector1 = tokenizer::initialize_documents("input.txt");
    vector<dictionary_entry> dictionaryVector1 = document::process_documents(documentVector1);
    indexer idx = indexer(documentVector1, dictionaryVector1);
    string user_query;
    cout << "Enter your query:" << endl;
    cin >> user_query;
    vector<query_result> GOOGLE_DOT_COM = idx.query(user_query, 1);

    for (vector<query_result>::iterator it = GOOGLE_DOT_COM.begin();
        it != GOOGLE_DOT_COM.end(); ++it)
    {
        cout << "Name: " << (it->get_doc()).get_name() << " Score: " << (it->get_score());
    }

    return 0;
}

//int main()
//{
//    vector<document> documentVector1 = tokenizer::initialize_documents("input.txt");
//    vector<dictionary_entry> dictionaryVector1 = document::process_documents(documentVector1);
//    indexer idx = indexer(documentVector1, dictionaryVector1);
//    document::print_dictionary(dictionaryVector1, documentVector1);
//    document::exclude_stop_words(documentVector1, dictionaryVector1);
//    document::print_dictionary(dictionaryVector1, documentVector1);
//    idx.normalize();
//
//    return 0;
//}
