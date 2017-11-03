#include "index_item.h"

index_item::index_item()
    :content(""),item_size(0)
{
}

index_item::~index_item()
{
}

/*!
 * This accessor returns the document's size
 */
size_t index_item::size() const{
	return item_size;
}

/*!
 * This accessor returns the document's content
 */
string index_item::get_content() const{
	return content;
}
