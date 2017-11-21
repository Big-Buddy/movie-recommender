#include "query_result.h"
#include "word_tokenizer.h"
#include <algorithm>
#include <vector>
using namespace std;

/*!
 * Is necessary for compilation.
 */
Query_Result::Query_Result(){ }

Query_Result::~Query_Result(){}

const vector<pair<index_item*,double> > & Query_Result::scorevector(){
    return score;
}

/*!
 * This function first checks if the indexer is normalized. If it is not, throw an error.
 * It then goes through every document in the indexer, and calculates the weights per document.
 * Using the weights, it calculates every document's score.
 * It the prints out the n top scores, and returns all scores.
 */
void Query_Result::query(indexer & idx,string s) {
    score.clear();
    int size = idx.getSize();

    if(!idx.isNormalize())
        throw idx.INDEX_NOT_NORMALIZED;
    word_tokenizer t;
    vector<string> tokens = t.word_tokenize(s);
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

        for(map<index_item*, int>::const_iterator docIt = idx.getTFtd2()[term].begin(); docIt !=  idx.getTFtd2()[term].end(); ++docIt){
            int frequency = docIt->second;
            if(frequency > 0)
                ++df;
        }

        dftq[term] = df;
    }

    //then, get the weight of the query's terms in the query
    for(map<string,int >::const_iterator it = queryfrequency.begin();it != queryfrequency.end();it++){
        string term = it->first;
        double s = size;
        double d = dftq[term];
        double tf = queryfrequency[term];
        double temp1 = 1+((double)log(tf)/(double)log(10));
        double temp2 = (double)log(s/d)/(double)log(10);
        double Wtd = temp1*temp2;
        if(Wtd == -INFINITY || Wtd == INFINITY || isnan(Wtd))
            wtdq[term] = 0;
        else
            wtdq[term] = Wtd;

    }

    for(vector<index_item*>::const_iterator itemsIt = idx.getItems().begin(); itemsIt != idx.getItems().end(); ++itemsIt){
        double Wiqij = 0;  //sum of the weight of term i in query * weight of term i in documents
        double Wiq = 0;  //square root of the sum of the weights of term i in query squared
        double Wij = 0;  //square root of the sum of the weights of term i in documents squared

        for(map<string, double >::const_iterator it = wtdq.begin();it != wtdq.end();it++){
            string term = it->first;
            double weightInQuery = it->second;
            double weightInDocument = idx.getWtd()[term][*itemsIt];

            Wiqij += weightInDocument * weightInQuery;
            Wiq += pow(weightInQuery,2);
            Wij += pow(weightInDocument,2);
        }

        double docScore;
        if(Wiq == 0 || Wij == 0)
            docScore = 0;
        else
            docScore = (Wiqij / (sqrt(Wiq) * sqrt(Wij)));

        score.push_back(make_pair(*itemsIt, docScore));
    }

    sort(score.begin(),score.end(), []( pair<index_item*,double>& a, pair<index_item*,double>& b) { return a.second > b.second; } );
}

/*!
 * This function prints the items contained in the index as documents. Printing out the name of the document and its score.
 */
void Query_Result::printDocResults(document_indexer & idx,string s,int n){
    int size = idx.getSize();
    cout << endl << "******* Top scoring documents for the query \"" << s << "\"  *********" <<endl;
    int end = min(n, size);

    for(int i=0;i<end;i++) {
        vector<index_item*> & test = idx.getItems();

        index_item* item = idx[i];

        document *doc = dynamic_cast<document*>(item);

        cout << left << setw(20) << doc->name() << right << score[i].second << endl;
    }
}

/*!
 * This function gets the top N items in the score.
 */
vector<index_item*> Query_Result::getTopNResults(int n, index_item* itemToFilter){
    vector<index_item *> results;
    int counter = 0;
    for(vector<pair<index_item*,double> >::iterator scoresIt = score.begin(); scoresIt != score.end(); ++scoresIt){
        if(counter >= n){
            break;
        }
        index_item* item = scoresIt->first;
            results.push_back(item);
            ++counter;
        }
    }

    return results;
}



/*!
 * This function generates an essay from the contents of the score vector<pair>.
 * The sentences that score contains are evaluated based on their word length to see if they are suitable given the requested number of words.
 * If successful the sentence is placed in the chosenSentences vector and then sorted by position.
 * The "essay" is then returned as a string.
 */
string Query_Result::generateEssayFromSentences(int wordCount) const {
    string str;
    vector<sentence*> chosenSentences;
    int usedWords = 0;

    for(vector<pair<index_item*, double> >::const_iterator scoreIterator = score.begin(); scoreIterator!= score.end(); ++scoreIterator){

        sentence *item = dynamic_cast<sentence*>(scoreIterator->first);
        if ((item->size() + usedWords) <= wordCount)
        {
            usedWords += item->size();
            chosenSentences.push_back(item);
        }
    }

    if (!chosenSentences.empty())
    {
        sort(chosenSentences.begin(), chosenSentences.end());

        for(vector<sentence*>::iterator sentenceIt = chosenSentences.begin(); sentenceIt!=chosenSentences.end(); ++sentenceIt){
            str += (*sentenceIt)->get_content() + "\n";
        }
    } else
    {
        str = "Cannot generate an essay with so few words. Please increase your desired word count for the essay.";
    }

    return str;
}
