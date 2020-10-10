#ifndef AEED_CONVERTER_H
#define AEED_CONVERTER_H

#include <string>

namespace converter{
    int get_code(const char&);
    char get_char(const unsigned int&);

    int stoi(const std::string&, const unsigned int&);
    double stod(const std::string&, const unsigned int&);

    std::string itos(const int&, const unsigned int&);
    std::string dtos(const double&, const unsigned int&);

    //std::string stos(const std::string&, const unsigned int&, const unsigned int&);
}
#endif //AEED_CONVERTER_H
