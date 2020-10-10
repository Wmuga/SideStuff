#include "converter.h"

#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <cstring>

char converter::get_char(const unsigned int & code) {
    return code + ((code<10) ? '0' : 'a' - 10 );
}

int converter::get_code(const char& symbol) {
    return symbol +( (symbol -'0' <10) ? -'0' : -'a'+10);
}

int converter::stoi(const std::string& str_num, const unsigned int& radix) {
    int result = 0;
    for (size_t i=0;i<str_num.size();i++){
        const char& item = str_num[i];
        if (get_code(item)>=radix) throw std::invalid_argument("converter::invalid_radix");
        result+=get_code(item)*pow(radix,str_num.size()-1-i);
    }
    return result;
}

double converter::stod(const std::string& str_num, const unsigned int& radix) {
    double result = 0;
    std::string buffer;
    auto dot = std::find(str_num.begin(),str_num.end(),'.');
    std::copy(str_num.begin(),dot,std::back_inserter(buffer));
    result+=stoi(buffer,radix);
    if (dot!=str_num.end() && dot!=str_num.end()-1){
        buffer="";
        std::copy(dot+1,str_num.end(),std::back_inserter(buffer));
        for (size_t i=0;i<buffer.size();i++){
            const char& item = buffer[i];
            if (get_code(item)>=radix) throw std::invalid_argument("converter::invalid_radix");
            result+=get_code(item)/pow(radix,i+1);
        }
    }
    return result;
}

std::string converter::itos(const int& in, const unsigned int& radix) {
    if (in == 0) return "0";
    char* res = new char[256];
    itoa(std::abs(in), res, radix);
    std::string result = res;
    delete []res;
    if (std::abs(in) != in) result = '-' + result;
    return result;
}

std::string converter::dtos(const double& in, const unsigned int& radix) {
    int iPart = static_cast<int>(in);

    std::string result = itos(iPart, radix);

    if (static_cast<double>(iPart) != in) {
        result += '.';
        double fPart = (in - static_cast<double>(iPart));
        unsigned int count = 0;
        while (fPart!=0 && count!=8) {
            result += get_char(static_cast<int>(fPart * radix));
            fPart = fPart * radix - (double)static_cast<int>(fPart * radix);
            count+=1;
        }
    }
    return result;
}
/*
std::string converter::stos(const std::string& str_num, const unsigned int & cRadix, const unsigned int& nRadix) {

    std::string buffer;
    auto dot = std::find(str_num.begin(),str_num.end(),'.');
    std::copy(str_num.begin(),dot,std::back_inserter(buffer));

    std::string new_str_num = itos(stoi(buffer,cRadix),nRadix);
    if (dot!=str_num.end() && dot!=str_num.end()-1){

        new_str_num +='.';
        buffer="";
        std::copy(dot+1,str_num.end(),std::back_inserter(buffer));

        for (size_t i=0;i<buffer.size();i++){
            const char& item = buffer[i];
            if (get_code(item)>=radix) throw std::invalid_argument("converter::invalid_radix");
            result+=get_code(item)/pow(radix,i+1);
        }
    }
    return new_str_num;
}*/