#ifndef SRC_MOVIE_INDEXER_H
#define SRC_MOVIE_INDEXER_H

#include "indexer.h"
#include "movie.h"

class movie_indexer: public indexer {

public:
    //! @brief a default constructor.
    movie_indexer();

    ~movie_indexer();

    //! @brief An operator[] overload.
    /*!
     * @param name: the name of the movies to return
     * @return the document with filename name
     */
    vector<movie*> operator [](string name);

    //! @brief an operator[] overload.
    /*!
     * @param n: an int index.
     * @return the movie at index n.
     */
    index_item* operator [](int n);
};


#endif //SRC_MOVIE_INDEXER_H
