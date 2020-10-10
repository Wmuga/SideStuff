//
// Created by Alex on 08.10.2020.
//

#ifndef RLEENC_RLE_H
#define RLEENC_RLE_H


#include <string>
#include <fstream>
/*
 * Header:
 * RLE
 * prev_extention
 * # as start of data
 * DATA
 */

class rle_encoder {
    std::ifstream inFile;
public:
    rle_encoder();
    explicit rle_encoder(const std::string&);

    void encode(const std::string&);

private:
    std::string readBlock();
};


#endif //RLEENC_RLE_H
