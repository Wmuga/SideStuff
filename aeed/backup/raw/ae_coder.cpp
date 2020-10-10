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
    std::ofstream file_out(out_file_name, std::ios::binary);
    if (!file_out.is_open()) throw std::runtime_error("Can't create file");
    while(!file_in.eof()){
        char symbol[1];
        file_in.read(symbol,1);
        char code = dictionary[symbol[0]];
        file_out.write(&code,1);
    }
}
