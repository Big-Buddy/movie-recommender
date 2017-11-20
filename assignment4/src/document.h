#ifndef DOCUMENT_H_
#define DOCUMENT_H_

#include <string>
#include "index_item.h"

class document : public index_item
{

private:
	//! @brief A private string: the document's file name.
	string filename;

	//! @brief A private int: a document number (cheapo identifier, mainly used for sentences)
	int docNum;

public:
	//! @brief A default constructor.
	document();


	//! @brief A default destructor.
	~document();

	//! @brief Another constructor.
	/*!  @param filename: filename of the document to be constructed.
	 *   @param num: docNum of the document to be constructed.
	 */
	document(string name, int num);

	//! @brief An accessor for the document's name.
	/*!
	 * @return A string: name of the document.
	 */
	string name() const;

	//! @brief An accessor for the document's number.
	/*!
	 * @return An int: docNum of the document.
	 */
	int getDocNum() const;

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
