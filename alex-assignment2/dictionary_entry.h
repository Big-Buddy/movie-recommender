#ifndef DICTIONARY_ENTRY_H_INCLUDED
#define DICTIONARY_ENTRY_H_INCLUDED

#include <vector>
#include <map>
#include <string>


class dictionary_entry
{
    friend class document;
    friend class indexer;
public:
    //constructor & destructor
    dictionary_entry(std::string w);
//    //getters
    std::string get_word() const;
//    int* get_count_per_document();
//
//    //setters
//    void set_word();
//    void set_count_per_document();
private:
    std::vector<int> count_per_document;
    std::string word;
};

#endif
