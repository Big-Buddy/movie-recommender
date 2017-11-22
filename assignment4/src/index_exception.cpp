//
// Created by Spasov on 11/21/2017.
//

#include "index_exception.h"


const std::string index_exception::errorMessage = "An error has occured, the movie you searched for does not exist or is misspelled";


const char *index_exception::what() const noexcept {
    return errorMessage.c_str();
}
