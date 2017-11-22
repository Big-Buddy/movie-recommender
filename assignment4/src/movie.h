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
        //! @brief A default constructor.
        movie();

        ~movie();

        //! @brief Parameterized constructor.
        /*!
         * @param i: ID of the movie.
         * @param n: Name of the movie.
         * @param r_d: Release date of the movie.
         */
        movie(int i, string n, string r_d);

        //! @brief Accessor for the id attribute.
        /*!
         * @return The id.
         */
        int get_id();

        //! @brief Accessor for the name attribute.
        /*!
         * @return The name.
         */
        string get_name();

        //! @brief Mutator for the content attribute.
        /*!
         * @param c: New content for the movie.
         */
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
