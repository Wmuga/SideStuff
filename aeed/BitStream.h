#ifndef BITSTREAM_BITSTREAM_H
#define BITSTREAM_BITSTREAM_H
#include <cstdio>
#include <string>
enum bit {zero=0,one=1};

class bitWriteStream {
    unsigned short BufferedBits;
    unsigned char CurrentBite;

    FILE* CurrentFile;
public:
    bitWriteStream();
    explicit bitWriteStream(const std::string&);
    explicit bitWriteStream(FILE*&);
    bool Open(const std::string&);

    bool Is_open();
    void WriteBit(bit);
    void WriteBits(unsigned int,unsigned int,unsigned int=0);

    void Close();
    ~bitWriteStream();
};

class bitReadStream{
    FILE* CurrentFile;
    unsigned short CurrentOffset;
    unsigned char  CurrentBite;

public:
    bitReadStream();
    explicit bitReadStream(const std::string&);
    explicit bitReadStream(FILE*&);
    bool Open(const std::string&);

    bool Is_open();

    long Tellp();
    int Seek(long,int);
    void SetBitOffset(short);
    int Eof();

    bit ReadBit();
    unsigned int ReadBits(unsigned int);

    void Close();
    ~bitReadStream();
};


#endif //BITSTREAM_BITSTREAM_H
