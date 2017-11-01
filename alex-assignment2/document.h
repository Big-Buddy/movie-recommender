#ifndef DOCUMENT_H_INCLUDED
#define DOCUMENT_H_INCLUDED

#include "dictionary_entry.h"

#include <vector>
#include <map>
#include <string>
#include <algorithm>


class document
{
    friend class tokenizer;
    friend class indexer;


public:
    //constructor & destructor

    document(std::string n);
    document();

    //    //getters and setters
    //    int get_totals_words();
    //    map<string,int> get_words_found();
    //    string get_name();
    //    void set_totals_words();
    //    void set_words_found();
    //    void set_name();


    static std::vector<document> initialize_documents(const std::string &input_file);
    static std::vector<dictionary_entry> process_documents(const std::vector<document> &documents_found);
    static void exclude_stop_words(std::vector<document> &complete_documents,
                                   std::vector<dictionary_entry> &complete_dictionary);
    static void print_dictionary(const std::vector<dictionary_entry> &dictionary_to_print,
                                 const std::vector<document> &documents_to_print);
    static std::string formatInput(std::string &s);

    int size(document doc);

    //getters and setters

    friend class dictionary_entry;

public:

    //getters

    std::string  get_content() const;
    std::string get_word() const;
    int get_count() const;
    std::string get_name() const;


private:
    std::vector<int> count_per_document;
    std::string word;
    int total_words;
    std::string name;
    std::string content;
    std::map<std::string,int> words_found;
    std::map<std::string,double> words_weight;
};

std::string formatInput(std::string &s);

#endif
