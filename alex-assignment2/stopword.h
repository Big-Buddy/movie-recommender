#ifndef STOPWORD_H_INCLUDED
#define STOPWORD_H_INCLUDED

#include <string>
#include <vector>

class stopword
{
    friend class document;
    //add more friend classes as necessary
public:
    stopword();
    stopword(const std::string &stopword_file);
    static bool is_stopword(const std::string &dictionary_word, const stopword &STOP_IN_THE_NAME_OF_LOVE);
private:
    std::vector<std::string> ALL_DA_STOPWORDS;
};

#endif
