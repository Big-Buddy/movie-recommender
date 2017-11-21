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
        movie_tokenizer();
        ~movie_tokenizer();

        vector<movie> movie_tokenize(string META_DATA_FILE, string DESCRIPTION_FILE);
};

#endif // MOVIE_TOKENIZER_H
