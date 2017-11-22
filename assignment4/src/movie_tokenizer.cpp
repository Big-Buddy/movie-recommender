#include "movie_tokenizer.h"
#include <fstream>
#include <sstream>
#include <map>
#include <iterator>

movie_tokenizer::movie_tokenizer()
{
}

movie_tokenizer::~movie_tokenizer()
{
}

vector<movie> movie_tokenizer::movie_tokenize(string META_DATA_FILE, string DESCRIPTION_FILE)
{
    vector<movie> movie_collection;

    //tokenize the meta data
    const char* meta_data_Src = META_DATA_FILE.c_str();
    ifstream metadata_fs(meta_data_Src);
    if(!metadata_fs)
        throw std::runtime_error("Could not Load Metadata File");
    map <int, pair<string, string>> id_to_metadata;

    string m_line;
    //begin reading metadata file
    while (getline(metadata_fs,m_line))
    {
        if (!m_line.empty())
        {
            //tokenize the line based on whitespaces
            istringstream iss(m_line);
            vector<string> temp_buffer;
            string tsv_token;
            while(getline(iss, tsv_token, '\t'))
            {
                temp_buffer.push_back(tsv_token);
            }
            //id @ temp_buffer[0], name @ temp_buffer[2], release date @ temp_buffer[3]
            //create movie object without its content
            movie temp_movie(stoi(temp_buffer[0]), temp_buffer[2], temp_buffer[3]);
            //add it to the movie_collection
            movie_collection.push_back(temp_movie);
        }
    }

    //tokenize the descriptions
    const char* description_Src = DESCRIPTION_FILE.c_str();
    ifstream description_fs(description_Src);
    map<int, string> id_to_description;

    string d_line;
    //begin reading description file
    while (getline(description_fs,d_line))
    {
        int id;
        string description;
        //get id
        id = stoi(d_line.substr(0, d_line.find("\t")));
        //get the description
        description = d_line.substr(d_line.find("\t"), d_line.length()-1);
        //insert the id-description pair into map
        id_to_description.insert(pair<int,string>(id, description));
    }

    int movie_count = 0;
    //join them based on ID
    //iterate over movie_collection
    //at each iteration look for a match in the map, if it matches add the description to the object
    //else delete the movie from the collection?
    for (vector<movie>::iterator it = movie_collection.begin();
            it != movie_collection.end();)
        {
            string temp_content;
            auto finder = id_to_description.find(it->get_id());
            if (finder != id_to_description.end())
            {
                temp_content = finder->second;
                it->set_content(temp_content);
                ++it;
            }
            else
            {
                movie_collection.erase(it);
            }
        }

    return movie_collection;
}
