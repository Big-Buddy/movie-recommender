

#ifndef QUERY_STRING_H_
#define QUERY_STRING_H_
#include "vector"
#include "document.h"
#include "indexer.h"
#include <algorithm>
using namespace std;


class Query_Result{

private:
	//! @brief A private vector of document-double pairs, which tracks the score of several documents.
	/*!
	 * Every document's score is stored as its own document-double pair.
	 * All documents' scores are then added to the score vector.
	 */
	vector<pair<document,double> > score;
public:
	//! @brief The default constructor.
	/*!
	 * Is necessary for compilation.
	 */
	Query_Result(){ }

	~Query_Result(){}

	//! @brief An accessor for the score.
	/*!
	 * @return The score of the query result.
	 */
	const vector<pair<document,double> > & scorevector(){
		return score;
	}

	//! @brief A function to apply a query and return a result.
	/*!
	 * This function first checks if the indexer is normalized. If it is not, throw an error.
	 * It then goes through every document in the indexer, and calculates the weights per document.
	 * Using the weights, it calculates every document's score.
	 * It the prints out the n top scores, and returns all scores.
	 * @tparam size: the size of indexer.
	 * @param idx: The indexer on which the query will be applied
	 * @param s: A string that is to be searched for in the indexer.
	 * @param n: an optional int to delimit the amount of results printed out, default is 10.
	 * @return the score
	 */
	template<int size>
	vector<pair<document,double> > query(indexer<size> & idx,string s,int n = 10){
		score.clear();
		if(!idx.isNormalize())
		throw idx.INDEX_NOT_NORMALIZED;
		tokenizer* t = new tokenizer;
		vector<string> tokens = t->tokenize(s);
		map<string,int> queryfrequency;
		for(int i=0;i<tokens.size();i++){
			if(!idx.getstpw()->operator ()(tokens[i])){
				queryfrequency[tokens[i]]++;
			}

		}
		map<string,double> wtdq;
		map<string,int> dftq;

		for(map<string,int >::const_iterator it = queryfrequency.begin();it != queryfrequency.end();it++){
				string t = it->first;
				int df = 0;
				for(int j=0;j<idx.getTFtd2()[t].size();j++){
					if(idx.getTFtd2()[t][j] > 0)
						df++;
				}
				dftq[t] = df;
			}
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


			for(int i=0;i<size;i++){
				double Wiqij = 0;
				double Wiq = 0;
				double Wij = 0;
				for(map<string, double >::const_iterator it = wtdq.begin();it != wtdq.end();it++){
					if(idx.getWtd()[it->first].size() != 0)
					Wiqij += (it->second * idx.getWtd()[it->first][i]);
					double wiq = it->second;
					Wiq += pow(wiq,2);
					if(idx.getWtd()[it->first].size() != 0)
					Wij += pow(idx.getWtd()[it->first][i],2);
				}
				double sc;
				if(Wiq == 0 || Wij == 0 || Wiqij == 0)
					sc = 0;
				else sc = abs(Wiqij/(sqrt(Wiq)*sqrt(Wij)));
				score.push_back(make_pair(idx[i],sc));
			}

			sort(score.begin(),score.end(), sortpairs);
			cout << endl << "******* Top scoring documents for the query \"" << s << "\"  *********" <<endl;
				for(int i=0;i<n;i++)
					cout << left << setw(20) << score[i].first.name() << right << score[i].second << endl;

			delete t;
			return score;
	}

};

//! @brief Compares two document-double pairs
/*!
 * @param a: the first score pair
 * @param b: the second score pair
 * @return a boolean: whether the a's score is greater than b's
 */
bool sortpairs(const pair<document,double> &a,const pair<document,double> &b){
    return (a.second > b.second);
}


#endif /* QUERY_STRING_H_ */