#include "sentence.h"
#include <sstream>
#include <iterator>

/*!
 * The default constructor sets the content to "", the size to 0, and the pos to 0
 */
sentence::sentence()
    :pos(0)
{
}

sentence::~sentence()
{
}

/*!
 * The constructor takes a string s, and sets the sentence's content to that string
 * It also takes int p, and sets the sentence's supposed position in a document to that int
 * It then splits the content of the sentence based on white spaces and sets the size of the sentence to the number of tokens that were split
 */
sentence::sentence(string s, int p, int docNum)
{
    content = s;
    pos = p;
    parentDocNum = docNum;
    istringstream iss(content);
    vector<string> tokens;
    copy(istream_iterator<string>(iss),istream_iterator<string>(),back_inserter(tokens));
    item_size = tokens.size();
}

/*!
 * This accessor returns the sentence's position in the document
 */
int sentence::getPos() const
{
    return pos;
}

/*!
 * This accessor returns the sentence's parent document number
 */
int sentence::getParentDocNum() const {
    return parentDocNum;
}

bool sentence::operator<(const sentence &other) {
    if(this->getParentDocNum() > other.getParentDocNum())
        return false;
    else if(this->getParentDocNum() < other.getParentDocNum())
        return true;
    else{
        if(this->getPos() < other.getPos())
            return true;
        else
            return false;

    }
}
