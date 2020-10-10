//
// Created by Alex on 03.10.2020.
//

#include "ae_coder.h"
#include <fstream>
#include <iostream>
#include <cmath>

ae_encoder::ae_encoder(std::string& in, std::string& out): in_file_name(in), out_file_name(out) {
    get_file();
    set_dictionary();
    print_file();
}

void ae_encoder::get_file() {
    std::ifstream file_in(in_file_name, std::ios::binary);
    if (!file_in.is_open()) throw std::runtime_error("No such file");
    while (!file_in.eof()){
        char symbol[1];
        file_in.read(symbol,1);
        symbolArray.emplace(symbol[0]);
    }
    file_in.close();
}

void ae_encoder::set_dictionary() {
    int code = 1;
    for (const auto& item: symbolArray) dictionary[item] = code++;
}

void ae_encoder::print_file() {
    FILE* file_in  = fopen(in_file_name.c_str(),"rb");
    FILE* file_out = fopen(out_file_name.c_str(),"wb");
    if (!file_out) throw std::runtime_error("Can't create file");

    double current_power = log(dictionary.size()+1)/log(2);
    short current_radix = (current_power==(int)current_power) ? dictionary.size()+1 : pow(2,(int)current_power+1);

    fwrite("AE",2,1,file_out);
    size_t offset = dictionary.size() * sizeof(std::pair<const unsigned char, short>);
    fwrite(&offset, 2, 1, file_out);
    for (const auto& item: dictionary) fwrite(&item,sizeof(item),1,file_out);

    while(!feof(file_in)){
        char* str = (char*)malloc(1024);

        fread(str,1,1024,file_in);
        std::string word = str;
        free(str);

        ustring new_word;
        for (const auto& item: word) new_word += static_cast<char>(dictionary.at(item));

        while (new_word.size()<1024) new_word += static_cast<char>(dictionary.at(0));

        ustring converted_word = converter::raw_convert(new_word,current_radix,256);
        for (const auto& symb : converted_word) std::clog << static_cast<int>(symb) << " ";
        std::clog << std::endl;
        fwrite(new_word.c_str(),new_word.size(),1,file_out);
    }

    fclose(file_in);
    fclose(file_out);
}

char converter::get_char(const unsigned int & code) {
    return code + ((code<10) ? '0' : 'A' - 10 );
}

int converter::get_code(const char& symbol) {
    return symbol +( (symbol -'0' <10) ? -'0' : -'A'+10);
}

std::string converter::convert(const std::string& prev, const short& pRadix, const short& nRadix) {
    std::string new_num;
    long long value=0;
    for (size_t i=0;i<prev.size();i++)
        value+=get_code(prev[i])*static_cast<int>(pow(pRadix,prev.size()-1-i));
    while(value){
        new_num.push_back(get_char(value%nRadix));
        value/=nRadix;
    }
    return new_num;
}

ustring converter::raw_convert(const ustring& prev, const short& pRadix, const short& nRadix){
    ustring new_num;
    unsigned long long value=0;
    for (size_t i=0;i<prev.size();i++)
    {
        int code = prev[i];
        int power = static_cast<int>(pow(pRadix,prev.size()-1-i));
        value += (long long)code * (long long)power;
    }
    while(value){
        new_num.insert(new_num.begin(),static_cast<char>(value%static_cast<int>(nRadix)));
        value/=static_cast<int>(nRadix);
    }
    return new_num;
}

std::ostream& operator<<(std::ostream& os,const ustring& str){
    for (const unsigned char& item : str) os << item;
    return os;
}