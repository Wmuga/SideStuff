//
// Created by Alex on 04.11.2020.
//

#include "BitStream.h"

bitWriteStream::bitWriteStream(): CurrentBite(0), BufferedBits(0), CurrentFile(nullptr) {

}

bitWriteStream::bitWriteStream(const std::string& filename): CurrentBite(0), BufferedBits(0), CurrentFile(nullptr) {
    Open(filename);
}

bitWriteStream::bitWriteStream(FILE*& OpenedFile): CurrentBite(0), BufferedBits(0), CurrentFile(OpenedFile) {
}

bool bitWriteStream::Open(const std::string& filename) {
    CurrentFile = fopen(filename.c_str(), "w+b");
    return Is_open();
}

bool bitWriteStream::Is_open() {
    return CurrentFile!=nullptr;
}

void bitWriteStream::WriteBit(bit newBit) {
    CurrentBite<<=1u;
    CurrentBite+=static_cast<short>(newBit);
    BufferedBits++;
    if (BufferedBits == 8){
        fwrite(&CurrentBite, 1, 1, CurrentFile);
        CurrentBite=0;
        BufferedBits=0;
    }
}

void bitWriteStream::WriteBits(unsigned int bitSequence,unsigned int count,unsigned int offset) {
    unsigned int shift = (sizeof(int)*8-count);
    bitSequence<<=shift;
    while (count--) {
        bit CurrentBit = static_cast<bit>((bitSequence>>(sizeof(int)*8-1))&1u);
        WriteBit(CurrentBit);
        bitSequence<<=1u;
    }
}

void bitWriteStream::Close() {
    while (BufferedBits) WriteBit(static_cast<bit>(0));
    fclose(CurrentFile);
    CurrentFile= nullptr;
}

bitWriteStream::~bitWriteStream() {
    if (Is_open()) Close();
}

/*
 * ------------------------------------------
 */
bitReadStream::bitReadStream():CurrentBite(0),CurrentFile(nullptr),CurrentOffset(0) {

}

bitReadStream::bitReadStream(const std::string& filename):CurrentBite(0),CurrentFile(nullptr),CurrentOffset(0) {
    Open(filename);
}

bitReadStream::bitReadStream(FILE *& openedFile):CurrentBite(0),CurrentFile(openedFile),CurrentOffset(0) {

}

bool bitReadStream::Open(const std::string& filename) {
    CurrentFile = fopen(filename.c_str(), "r+b");
    return Is_open();
}

bool bitReadStream::Is_open() {
    return CurrentFile!= nullptr;
}

void bitReadStream::Close() {
    fclose(CurrentFile);
}

bitReadStream::~bitReadStream() {
    if (Is_open()) Close();
}

long bitReadStream::Tellp() {
    return ftell(CurrentFile);
}

int bitReadStream::Seek(long offset, int origin) {
    return fseek(CurrentFile,offset,origin);
}

void bitReadStream::SetBitOffset(short bitOffset) {
    CurrentOffset= bitOffset&7;
}

bit bitReadStream::ReadBit() {
    if(!CurrentOffset) fread(&CurrentBite,1,1,CurrentFile);
    bit ReadBit = static_cast<bit>((CurrentBite>>(7u-CurrentOffset))&1u);
    CurrentOffset=(CurrentOffset+1)%8;
    return ReadBit;
}

unsigned int bitReadStream::ReadBits(unsigned int BitCount) {
    unsigned int BitSequence = 0;
    while(BitCount--) BitSequence=(BitSequence<<1u)+static_cast<unsigned int>(ReadBit());
    return BitSequence;
}

int bitReadStream::Eof() {
    char buffer;
    fread(&buffer,1,1,CurrentFile);
    if (feof(CurrentFile)) return (feof(CurrentFile)&&!CurrentOffset);
    fseek(CurrentFile,-1,SEEK_CUR);
    return false;
}
