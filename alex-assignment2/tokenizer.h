#ifndef TOKENIZER_H_INCLUDED
#define TOKENIZER_H_INCLUDED

#include "document.h"

#include <vector>
#include <string>

class tokenizer
{
public:
    static std::vector<document> initialize_documents(const std::string &input_file);

private:

};

#endif
