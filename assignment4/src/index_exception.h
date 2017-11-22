//
// Created by Spasov on 11/21/2017.
//

#ifndef SRC_INDEX_EXCEPTION_H
#define SRC_INDEX_EXCEPTION_H


#include <exception>
#include <string>

class index_exception : public std::exception{
private:
    //! @brief The string that represents the error message
    const static std::string errorMessage;

public:
    //! @brief Overlaading the virtual function what() so that it returns the error message.
    const char* what() const noexcept override ;

};


#endif //SRC_INDEX_EXCEPTION_H
