//
// Created by Alex on 08.10.2020.
//

#include "rle.h"
#include <algorithm>

rle_encoder::rle_encoder() = default;

rle_encoder::rle_encoder(const std::string& filename) {
    encode(filename);
}

void rle_encoder::encode(const std::string & filename) {
    auto dot_position = std::find(filename.begin(),filename.end(),'.');
    std::string out_filename,prev_expansion;
    std::copy(filename.begin(),dot_position,std::back_inserter(out_filename));
    std::copy(dot_position,filename.end(),std::back_inserter(prev_expansion));
    out_filename+=".rle";

    std::ofstream outFile(out_filename,std::ios::binary);
    inFile.open(filename,std::ios::binary);

    if (!(inFile.is_open() || outFile.is_open())) throw std::invalid_argument("rle_unable_to_open_or_create_file");

    outFile.write("RLE",3);

    char* prExpansion = prev_expansion.data();
    outFile.write(prExpansion,prev_expansion.size());
    delete []prExpansion;

    outFile.write("#",1);

    outFile.flush();
    do{
        std::string charBlock = readBlock();
        if (charBlock.size()>2) charBlock = std::to_string(charBlock.size())+charBlock[0];
        char* outData = charBlock.data();
        outFile.write(outData, charBlock.size());
        delete []outData;
        outFile.flush();
    }while(!inFile.eof());

    inFile.close();
    outFile.close();
}

std::string rle_encoder::readBlock() {
    std::string charBlock;
    char currentChar;
    inFile.read(&currentChar,1);
    do{
        charBlock+=currentChar;
        inFile.read(&currentChar,1);
    }while(currentChar==charBlock[charBlock.size()-1] && !inFile.eof());
    inFile.putback(currentChar);
    return charBlock;
}

