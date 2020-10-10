//
// Created by Alex on 03.10.2020.
//

#ifndef AEED_AE_CODER_H
#define AEED_AE_CODER_H
#include <set>
#include <map>
#include <fstream>

typedef std::basic_string<unsigned char> ustring;

std::ostream& operator<<(std::ostream&,const ustring&);


class ae_encoder {
    std::map<unsigned char,short> dictionary;
    std::set<unsigned char> symbolArray;

    std::string& in_file_name;
    std::string& out_file_name;
public:
    ae_encoder(std::string&,std::string&);
private:
    void get_file();
    void set_dictionary();
    void print_file();
};
/*
class ae_decoder {
private:
    friend std::string convert(const std::string&,const short&,const short&);
};
*/


namespace converter{
    int get_code(const char&);
    char get_char(const unsigned int&);


    std::string convert(const std::string&,const short&,const short&);

    ustring raw_convert(const ustring&,const short&,const short&);
}

#endif //AEED_AE_CODER_H
