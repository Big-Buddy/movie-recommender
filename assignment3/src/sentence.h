#ifndef SENTENCE_H
#define SENTENCE_H

#include <vector>
#include "index_item.h"


class sentence : public index_item
{
    public:
        //! @brief A default constructor.
        sentence();

        //! @brief Another constructor.
        /*!  @param s: content of the sentence to be constructed.
        */
        sentence(string s, int p);

        ~sentence();

        //! @brief An accessor for the sentence's position in a document.
        /*!
        * @return An int, the starting position of the sentence.
        */
        int getPos() const;

    private:
        //! @brief A private int: the start position (in characters) of the sentence in a particular document.
        int pos;
};

#endif // SENTENCE_H
