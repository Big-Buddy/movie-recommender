#ifndef MOVIE_H
#define MOVIE_H

#include <string>

#include "index_item.h"

using namespace std;

class movie : public index_item
{
    public:
        movie();
        ~movie();
        movie(int i, string n, string r_d);

        int get_id();

        void set_content(string c);

    private:
        int id;
        string name;
        string release_date;
};

#endif // MOVIE_H
