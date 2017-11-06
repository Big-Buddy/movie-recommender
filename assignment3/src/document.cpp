#include "document.h"
#include <iostream>
#include <fstream>

/*!
 * The constructor takes a string name, and sets the document's name as that string
 * It then creates a filestream with the string name, and reads its contents into the document's content field
 * It then sets the document's size to the size of content
 */
document::document(string name)
	:filename(name) {
	ifstream fin(filename);
	string new_content;
	while (fin >> new_content) {
		content += new_content + " ";
	}
	content = content.substr(0, content.size() - 1);
	item_size = content.size();
}


document::~document(){ }

/*!
 * The default constructor sets the filename and content to "", and the size to 0
 */
document::document()
	:filename("")
{
}

/*!
 * This accessor returns the document's filename
 */
string document::name() const{
	return filename;
}

/*!
 * This method overloads the operator<<
 * It reads the file's information into the ostream
 */
ostream & operator<<(ostream & os,document & d){
	os << "File name: " << d.filename << "\nFile size: " << d.item_size << " characters.\n File contents:\n" << d.content;
	return os;
}
