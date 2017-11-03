#ifndef INDEX_ITEM_H
#define INDEX_ITEM_H

#include <string>

using namespace std;

class index_item
{
    public:
        //! @brief A default constructor.
        index_item();

        virtual ~index_item() = 0;

        //! @brief An accessor for the item's size.
        /*!
        * @return A size_t: the size of the item.
        */
        size_t size() const;

        //! @brief An accessor for the item's content.
        /*!
        * @return A string: the content of the item.
        */
        string get_content() const;

    protected:

        //! @brief A private string: the item's content.
        size_t item_size;

        //! @brief a private size_t: the item's size.
        string content;
};

#endif // INDEX_ITEM_H
