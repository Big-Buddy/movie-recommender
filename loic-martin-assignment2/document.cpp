#include "document.h"
#include <iostream>
#include <fstream>

/*!
 * The constructor takes a string name, and sets the document's name as that string
 * It then creates a filestream with the string name, and reads its contents into the document's filecontent
 * It then sets the document's size to the size of filecontent
 */
document::document(string name)
	:filename(name)
{
		ifstream fin(filename);
		string content;
		while(fin >> content){
			filecontent += content + " ";
		}
		filecontent = filecontent.substr(0,filecontent.size()-1);
		filesize = filecontent.size();

}


document::~document(){ }

/*!
 * The default constrocur sets the filename and content to "", and the size to 0
 */
document::document()
	:filename(""),filecontent(""),filesize(0)
{

}

/*!
 * This accessor returns the document's filename
 */
string document::name() const{
	return filename;
}

/*!
 * This accessor returns the document's size
 */
size_t document::size() const{
	return filesize;
}

/*!
 * This accessor returns the document's content
 */
string document::content() const{
	return filecontent;
}

/*!
 * This method overloads the operator<<
 * It reads the file's information into the ostream
 */
ostream & operator<<(ostream & os,document & d){
	os << "File name: " << d.filename << "\nFile size: " << d.filesize << " characters.\n File contents:\n" << d.filecontent;
	return os;
}
