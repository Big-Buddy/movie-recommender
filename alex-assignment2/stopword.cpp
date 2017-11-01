#include "stopword.h"

#include <iostream>
#include <fstream>

using namespace std;

stopword::stopword(const string &stopword_file)
{
    //takes as input: a file ending with the
    //.txt extension
    ifstream myReadFile;
    myReadFile.open(stopword_file.c_str());
    string NEW_STOP_WORD;

    if (myReadFile.is_open())
    {
        while (!myReadFile.eof())
        {
            myReadFile >> NEW_STOP_WORD;
            ALL_DA_STOPWORDS.push_back(NEW_STOP_WORD);
        }
    }
}

bool stopword::is_stopword(const string &dictionary_word, const stopword &STOP_IN_THE_NAME_OF_LOVE)
{
    bool remove_it = false;

    for (vector<string>::const_iterator it = STOP_IN_THE_NAME_OF_LOVE.ALL_DA_STOPWORDS.begin();
        it != STOP_IN_THE_NAME_OF_LOVE.ALL_DA_STOPWORDS.end(); ++it)
    {
        if (dictionary_word == *it)
        {
            remove_it = true;
            break;
        }
    }

    return remove_it;
}
