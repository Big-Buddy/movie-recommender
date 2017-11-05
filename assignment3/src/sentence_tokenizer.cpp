#include "sentence_tokenizer.h"
#include <sstream>
#include <iterator>

typedef vector<string>::iterator string_it;

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
vector<string> sentence_tokenizer::sentence_tokenize(const string &s)
{
    //string s is passed and we store it and make a vector of string
    string content = s;
    vector<string> temp_buffer;
    vector<string> result_buffer;
    //begin tokenizing and splitting
    istringstream iss(s);
    copy(istream_iterator<string>(iss),istream_iterator<string>(),back_inserter(temp_buffer));

    string temp_string = "";
    for(string_it sit = temp_buffer.begin();
        sit != temp_buffer.end(); ++sit)
    {
        //if token ends in "." or "!" or "?" perform check
        if (is_end(sit->at((sit->length())-1)))
        {
            //WE ASSUME GENERALLY THAT: an abbreviation cannot be followed by a token with its first character in upper case
            //ex: exec. John BAD --- Dr. John GOOD
            //add the sentence to our container and set it back to empty string
            auto test = sit;
            if ((test+1) != temp_buffer.end() &&
                isupper((temp_buffer[distance(temp_buffer.begin(),sit)+1]).at(0)))
            {
                temp_string += *sit;
                result_buffer.push_back(temp_string);
                temp_string = "";
            } else
            {
                temp_string += *sit;
            }
        } else
        {
            temp_string += *sit;
        }
    }

    //if the last "sentence" of string s (the string that was passed) does not have a full-stop at the end we simply take it as is and add it to result_buffer
    if (temp_string != "")
    {
        result_buffer.push_back(temp_string);
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
