//
// Created by Alex on 03.10.2020.
//

#include "ae_coder.h"
#include <fstream>
#include <iostream>

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
    int code = 0;
    for (const auto& item: symbolArray) dictionary[item] = code++;
}

void ae_encoder::print_file() {
    std::ifstream file_in(in_file_name, std::ios::binary);
    FILE* file_out = fopen(out_file_name.c_str(),"wb");
    if (!file_out) throw std::runtime_error("Can't create file");

    fwrite("AE",2,1,file_out);
    size_t offset = dictionary.size() * sizeof(std::pair<const unsigned char, short>);
    fwrite(&offset, 2, 1, file_out);
    for (const auto& item: dictionary) fwrite(&item,sizeof(item),1,file_out);

    while(!file_in.eof()){
        char symbol[1];
        file_in.read(symbol,1);
        fwrite(&dictionary[symbol[0]],1,1,file_out);
    }

    file_in.close();
    fclose(file_out);
}