#include "document.h"
#include "dictionary_entry.h"
#include "stopword.h"

#include <iostream>
#include <algorithm>
#include <array>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <stdio.h>
#include <string>
#include <streambuf>
#include <sstream>

using namespace std;


int number_of_documents = 0;
string document_file;


document::document(string n)
{
    // Using Process Function code reads input creates document object, reads content into document object
    total_words = 0;
    name = n;
    content = "";

}

document::document()
{

    name = nullptr;
    total_words = 0;
    content = nullptr;
}

string document::get_name() const
{
    return name;
}


string document::get_content() const
{

    return content;

}

// SIZE FUNCTION
int document::size(document doc)
{
    int tempsize;
   tempsize= content.size();
    return tempsize;
}


string document::formatInput(string &s)
{
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    string result;
    std::remove_copy_if(s.begin(), s.end(),
                        std::back_inserter(result), //Store output
                        std::ptr_fun<int, int>(&std::ispunct)
                        );
    return result;
}

void document::exclude_stop_words(vector<document> &complete_documents,
                                  vector<dictionary_entry> &complete_dictionary)
{
    //iterate over the dictionary
    //--> remove stopwords
    //----> add the occurrences per document to the to_subtract buffer

    stopword to_stop = stopword("stopwords.txt");
    for(vector<dictionary_entry>::iterator dit = complete_dictionary.begin();
        dit != complete_dictionary.end(); )
    {
        if (stopword::is_stopword((dit->word), to_stop))
        {
            vector<int> to_subtract;

            for(vector<int>::iterator countit = (dit->count_per_document).begin();
                countit != (dit->count_per_document).end(); ++countit)
            {
                to_subtract.push_back(*countit);
            }

            for(vector<document>::iterator docit = complete_documents.begin();
                docit != complete_documents.end(); ++docit)
            {
                (docit->total_words) -= to_subtract[distance(complete_documents.begin(), docit)];
            }
            complete_dictionary.erase(dit);
        }
        else
        {
            ++dit;
        }
    }
}

vector<dictionary_entry> document::process_documents(const vector<document> &documents_found)
{
    int document_counter = 0;
    int num_of_documents = documents_found.size();
    vector<dictionary_entry> dictionary;

    for(vector<document>::const_iterator docit = documents_found.begin();
        docit != documents_found.end(); ++docit)
    {
        for(map<string,int>::const_iterator mapit = (docit->words_found).begin();
            mapit != (docit->words_found).end(); ++mapit)
        {
            if (dictionary.empty())
            {
                dictionary.push_back(dictionary_entry((mapit->first)));
                dictionary.back().count_per_document.assign(num_of_documents,0);
                dictionary.back().count_per_document[document_counter] = (mapit->second);
            }
            else
            {
                int foundy_savior_of_this_project = 0;
                bool found = false;
                for(vector<dictionary_entry>::iterator deit = dictionary.begin();
                    deit != dictionary.end(); ++deit)
                {
                    if((deit->word) == (mapit->first))
                    {
                        foundy_savior_of_this_project = distance(dictionary.begin(), deit);
                        found = true;
                        break;
                    }
                }

                if (found)
                {
                    dictionary[foundy_savior_of_this_project].count_per_document[document_counter] = (mapit->second);

                }
                else
                {
                    dictionary.push_back(dictionary_entry((mapit->first)));
                    dictionary.back().count_per_document.assign(num_of_documents,0);
                    dictionary.back().count_per_document[document_counter] = (mapit->second);
                }
            }
        }
        ++document_counter;
    }
    sort(dictionary.begin(), dictionary.end(),
         [](dictionary_entry lhs, dictionary_entry rhs){return lhs.word < rhs.word;});
    return dictionary;
}

void document::print_dictionary(const vector<dictionary_entry> &dictionary_to_print,
                                const vector<document> &documents_to_print)
{
    cout<< setw(15) << left << ("Dictionary")  << " | ";
    for(vector<document>::const_iterator docit = documents_to_print.begin();
        docit != documents_to_print.end(); ++docit)
    {
        cout << setw(15) << left << (docit->name) << " | ";
    }

    cout << endl;

    for(vector<dictionary_entry>::const_iterator dit = dictionary_to_print.begin();
        dit != dictionary_to_print.end(); ++dit)
    {
        //print words and instances per document
        cout << setw(15) << left << (dit->word)<< " | ";
        for (vector<int>::const_iterator countit = (dit->count_per_document).begin();
             countit != (dit->count_per_document).end(); ++countit)
        {
            cout << setw(15) << right << *countit << " | ";
        }
        cout << endl;
    }
    // print totals
    cout<< setw(15) << left << ("Total")  << " | ";
    for (vector<document>::const_iterator docit = documents_to_print.begin();
         docit != documents_to_print.end(); ++docit)
    {
        cout << setw(15)<< right << (docit->total_words)  << " | ";
    }
    cout << endl << endl;
}


vector<document> document::initialize_documents(const string &input_file)
{
    ifstream myReadFile;
    myReadFile.open(input_file.c_str());
    string fileName;
    string inputWord;
   // string inputContent;  // added new line

    vector<document> documentVector;
    if (myReadFile.is_open()) {
        while (!myReadFile.eof()) {
            number_of_documents++;
            myReadFile >> fileName;


            ifstream myReadFile2;
            string newFile(fileName);
            myReadFile2.open(newFile.c_str());
            document newDoc = document(fileName);

            // ADDING IN THE content to the document object

            ifstream t(fileName);   // reading in file
            stringstream buffer;    // create buffer
            buffer << t.rdbuf();    // reading the file into buffer
            newDoc.content =buffer.str(); // assigning the file to content of object


            if(myReadFile2.is_open()){
                while (myReadFile2 >> inputWord) {
                    map<string,int>::const_iterator mapIt;
                    mapIt = newDoc.words_found.find(inputWord);
                    if (!(mapIt == newDoc.words_found.end())) {
                        newDoc.words_found[inputWord]++;
                        newDoc.total_words++;
                    } else {
                        newDoc.words_found.insert(std::pair<string,int>(inputWord,1));
                        newDoc.total_words++;
                    }
                }
            }
            documentVector.push_back(newDoc);
        }
    }

    myReadFile.close();
    return documentVector;
}


