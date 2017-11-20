#ifndef MOVIE_H
#define MOVIE_H

#include <string>

using namespace std;

class movie
{
    public:
        movie();
        ~movie();
        movie(int i, string n, string r_d);

    private:
        int id;
        string name;
        string release_date;
};

#endif // MOVIE_H
