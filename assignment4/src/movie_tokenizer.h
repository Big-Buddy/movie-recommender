#ifndef MOVIE_TOKENIZER_H
#define MOVIE_TOKENIZER_H

#include "abstract_tokenizer.h"
#include "movie.h"

#include <vector>
#include <string>

using namespace std;

class movie_tokenizer : public abstract_tokenizer
{

    public:
    	//! @brief A default constructor.
        movie_tokenizer();

        ~movie_tokenizer();

        //! @brief Reads two files and returns a vector of movies.
        /*!
         * @param META_DATA_FILE: The filename of the file containing the movie meta data.
         * @param DESCRIPTION_FILE: The filename of the file containing the movie descriptions.
         * @return All the movies that have descriptions in the the files.
         */
        vector<movie> movie_tokenize(string META_DATA_FILE, string DESCRIPTION_FILE);
};

#endif // MOVIE_TOKENIZER_H
