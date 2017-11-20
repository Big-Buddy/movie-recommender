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
         *   @param p: the position of the sentence in the string.
         *   @param docNum: the number of the document from which the string originates.
        */
        sentence(string s, int p, int docNum);

        //! @brief The default destructor
        ~sentence();

        //! @brief An accessor for the sentence's position in a document.
        /*!
        * @return An int, the starting position of the sentence.
        */
        int getPos() const;

        //! @brief An accessor for the sentence's document number.
        /*!
        * @return An int, the document number.
        */
        int getParentDocNum() const;

        //! @brief a default < operator
        /*!
        * @param other: a sentence to compare *this* to
        * @return a boolean. Whether other is greater than *this*
        */
        bool operator<(const sentence & other);
    private:
        //! @brief A private int: the start position (in characters) of the sentence in a particular document.
        int pos;

        //! @brief A private int: the sentence's document number (creates a link between sentences and documents. will be used for essay generation)
        int parentDocNum;
};

#endif // SENTENCE_H
