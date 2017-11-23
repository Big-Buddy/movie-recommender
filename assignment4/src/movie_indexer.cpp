#include <algorithm>
#include "movie_indexer.h"

/*!
 * Initializes the indexer's N to 0, normalized to false, and stpw to a stopwords ("stopwords.txt").
 */
movie_indexer::movie_indexer():indexer() {}

movie_indexer::~movie_indexer() {}

/*!
 * Iterates through all items, and returns the movie with title name
 */
vector<movie*> movie_indexer::operator [](string name){
    vector<movie*> movVec;
    try {
        for(vector<index_item*>::iterator itemsIt = getItems().begin(); itemsIt != getItems().end(); ++itemsIt){
            movie *mov = dynamic_cast<movie*>(*itemsIt);
            string movName = mov->get_name();
            transform(movName.begin(), movName.end(), movName.begin(), ::tolower);
            transform(name.begin(), name.end(), name.begin(), ::tolower);

            if(movName.find(name) != string::npos){
                movVec.push_back(mov);
            }
        }
    }catch (std::out_of_range ex){
        cout<< ex.what() << endl;
        exit(1);
    }

    return movVec;
}

/*!
 * Gets the indexer's n'th document.
 */
index_item* movie_indexer::operator [](int n){
    return items[n];
}
