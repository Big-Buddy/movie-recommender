#include "sentence_tokenizer.h"
#include <sstream>
#include <iostream>
#include <iterator>

typedef vector<string>::iterator string_it;
#define SPECIAL_END_SYMBOL "~!~"

/*!
 * The default constructor.
 */
sentence_tokenizer::sentence_tokenizer()
{
}

sentence_tokenizer::~sentence_tokenizer()
{
}

/*!
 * The sentence_tokenize method takes a string s, and first breaks it into tokens by splitting words by whitespace.
 * It then takes every string in the vector, and begins adding them together to form a sentence.
 * If the end of a sentence is detected. We store what is currently on the accumulator and reset the accumulator
 * We continue iterating until we have exhausted all the tokens.
 * Finally, it returns the new vector of sentences.
 */
vector<sentence> sentence_tokenizer::sentence_tokenize(const string &s, int docNum)
{
    //string s is passed and we store it and make a vector of string
    string content = s;
    cout << s << endl;
    vector<string> temp_buffer;
    vector<sentence> result_buffer;
    //begin tokenizing and splitting
    istringstream iss(s);
    copy(istream_iterator<string>(iss),istream_iterator<string>(),back_inserter(temp_buffer));
    //INSERT SPECIAL_END_SYMBOL
    temp_buffer.push_back(SPECIAL_END_SYMBOL);

    string temp_string = "";
    int position = 0;
    int temp_position = 0;
    for(string_it sit = temp_buffer.begin();
        sit != temp_buffer.end(); ++sit)
    {
        if (*sit == SPECIAL_END_SYMBOL)
        {
            break;
        }
        //if token ends in "." or "!" or "?" perform check
        if (is_end(sit->at((sit->length())-1)))
        {
            if (!isAbbreviation(*sit, temp_buffer[distance(temp_buffer.begin(), sit)+1]))
            {
                temp_string += *sit;
                result_buffer.push_back(sentence(temp_string, position, docNum));
                temp_string = "";
                temp_position += sit->length() + 1;
                position = temp_position;
            } else
            {
                temp_string += (*sit + " ");
                temp_position += sit->length() + 1;
            }
        } else
        {
            temp_string += (*sit + " ");
            temp_position += sit->length() + 1;
        }
    }

    return result_buffer;
}

/*!
 * Tests a char input to see whether it matches certain characters.
 */
bool sentence_tokenizer::is_end(const char &c)
{
    bool test = false;

    if (c == '.' || c == '!' || c == '?')
    {
        test = true;
    }

    return test;
}

bool sentence_tokenizer::isAbbreviation(const string &first, const string &second)
{
    bool is_abbreviated = false;

    if (first.at(first.length()-1) != '.')
    {
        return false;
    }

    if (islower(second.at(0)))
    {
        is_abbreviated = true;
    }

    cout << first << " " << first.length() << endl;
    if (isupper(first.at(0)) && isupper(second.at(0)) && (first.length() <= 4))
    {
        is_abbreviated = true;
    }

    return is_abbreviated;
}
