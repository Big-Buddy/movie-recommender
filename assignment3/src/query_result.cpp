#include "query_Result.h"
#include "word_tokenizer.h"
#include <algorithm>
#include <vector>
using namespace std;

/*!
 * Is necessary for compilation.
 */
Query_Result::Query_Result(){ }

Query_Result::~Query_Result(){}

const vector<pair<document,double> > & Query_Result::scorevector(){
    return score;
}

/*!
 * This function first checks if the indexer is normalized. If it is not, throw an error.
 * It then goes through every document in the indexer, and calculates the weights per document.
 * Using the weights, it calculates every document's score.
 * It the prints out the n top scores, and returns all scores.
 */
vector<pair<document,double> > Query_Result::query(indexer & idx,string s,int n) {
    score.clear();
    int size = idx.getSize();

    if(!idx.isNormalize())
        throw idx.INDEX_NOT_NORMALIZED;
    word_tokenizer* t = new word_tokenizer;
    vector<string> tokens = t->word_tokenize(s);
    map<string,int> queryfrequency;

    //get the term frequency of every word in the query
    for(int i=0;i<tokens.size();i++){
        if(!idx.getstpw()->operator ()(tokens[i])){
            queryfrequency[tokens[i]]++;
        }
    }

    map<string,double> wtdq;
    map<string,int> dftq;

    //then, get the document frequency of the query words in the indexer's documents
    for(map<string,int >::const_iterator it = queryfrequency.begin();it != queryfrequency.end();it++){
        string term = it->first;
        int df = 0;

        for(map<string, int>::const_iterator docIt = idx.getTFtd2()[term].begin(); docIt !=  idx.getTFtd2()[term].end(); ++docIt){
            int frequency = docIt->second;
            if(frequency > 0)
                ++df;
        }

        dftq[term] = df;
    }

    //then, get the weight of the query's terms in the query
    for(map<string,int >::const_iterator it = queryfrequency.begin();it != queryfrequency.end();it++){
        string t = it->first;
        double s = size;
        double d = dftq[t];
        double tf = queryfrequency[t];
        double temp1 = 1+((double)log(tf)/(double)log(10));
        double temp2 = (double)log(s/d)/(double)log(10);
        double Wtd = temp1*temp2;
        if(Wtd == -INFINITY || Wtd == INFINITY || isnan(Wtd))
            wtdq[t] = 0;
        else
            wtdq[t] = Wtd;

    }

    //using those, calculate the score
    vector<string> documentNames = idx.getDocumentNames();

    for(vector<string>::const_iterator namesIt = documentNames.begin(); namesIt != documentNames.end(); ++namesIt){
        string docName = *namesIt;
        double Wiqij = 0;  //sum of the weight of term i in query * weight of term i in documents
        double Wiq = 0;  //square root of the sum of the weights of term i in query squared
        double Wij = 0;  //square root of the sum of the weights of term i in documents squared

        for(map<string, double >::const_iterator it = wtdq.begin();it != wtdq.end();it++){
            string term = it->first;
            double weightInQuery = it->second;
            double weightInDocument = idx.getWtd()[term][docName];

            Wiqij += weightInDocument * weightInQuery;
            Wiq += pow(weightInQuery,2);
            Wij += pow(weightInDocument,2);
        }

        double docScore;
        if(Wiq == 0 || Wij == 0)
            docScore = 0;
        else
            docScore = (Wiqij / (sqrt(Wiq) * sqrt(Wij)));

        score.push_back(make_pair(idx[docName], docScore));
    }

    sort(score.begin(),score.end(), sortpairs);
    cout << endl << "******* Top scoring documents for the query \"" << s << "\"  *********" <<endl;
    for(int i=0;i<n;i++)
        cout << left << setw(20) << score[i].first.name() << right << score[i].second << endl;

    delete t;
    return score;
}


bool sortpairs(const pair<document,double> &a,const pair<document,double> &b){
    return (a.second > b.second);
}