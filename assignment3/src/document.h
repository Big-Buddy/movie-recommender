#ifndef DOCUMENT_H_
#define DOCUMENT_H_

#include <string>
#include "index_item.h"

class document : public index_item
{

private:
	//! @brief A private string: the document's file name.
	string filename;

public:
	//! @brief A default constructor.
	document();

	~document();

	//! @brief Another constructor.
	/*!  @param filename: filename of the document to be constructed.
	 */
	document(string filename);

	//! @brief An accessor for the document's name.
	/*!
	 * @return A string: name of the document.
	 */
	string name() const;

	//! @brief A friend operator<< overload.
	/*!
	 * Puts document's information into an ostream
	 * @param os: the ostream into which we put document information
	 * @param d: the document which's information we print out
	 * @return an ostream: the contents of document
	 */
	friend ostream & operator<<(ostream & os,document & d);

};




#endif /* DOCUMENT_H_ */
