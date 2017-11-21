#ifndef MOVIE_H
#define MOVIE_H

#include <string>

#include "index_item.h"
#include <iomanip>
#include <iostream>

using namespace std;

class movie : public index_item
{
    public:
        movie();
        ~movie();
        movie(int i, string n, string r_d);

        int get_id();

        string get_name();

        void set_content(string c);

        //! @brief an operator<< overload
        /*!
         * @param os: the outstream which will receive the matrix information
         * @param mov: the movie from which we take information
         * @return the outstream with matrix information.
         */
        friend ostream & operator <<(ostream & os, movie & mov);

    private:
        int id;
        string name;
        string release_date;
};

#endif // MOVIE_H
