#include "dictionary_entry.h"


using namespace std;

dictionary_entry::dictionary_entry(string w)
{
    word = w;
}

string dictionary_entry::get_word() const
{
    return word;
}
