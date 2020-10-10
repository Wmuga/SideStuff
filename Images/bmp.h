#include <vector>
#include <string>
#include <cstdlib>
#include <windows.h>
/*
typedef unsigned long DWORD;
typedef unsigned short WORD;

struct BITMAPFILEHEADER
{
    WORD bfType; //4D42 or 424D == BM
    DWORD bfSize; // sizeof(file)
    WORD bfReserved1; // 0
    WORD bfReserved2; // 0
    DWORD bfOffBits; // location of pixels
};

struct BITMAPINFOHEADER
{
    DWORD biSize; //sizeof(BITMAPINFOHEADER)
    long biWidth; //file
    long biHeight; //file
    WORD biPlanes; //always 1
    WORD biBitCount; //bit to 1 pixel, 1(2clr),4(16clr),8(256clr),16(2^16(15)clr),24(2^24 clr)
    DWORD biCompression; //flag BI_RGB = 0
    DWORD biSizeImage; //Image size = Width*Height*biBitCount/8
    long biXPelsPerMeter; //pixels/meter 2795
    long biYPelsPerMeter; //pixels/meter 2795
    DWORD biClrUsed; //always 0 - max possible colors
    DWORD biClrImportant; //always 0 - all are important
};

struct tagRGBQUAD
{
    char rgbBlue;
    char rgbGreen;
    char rgbRed;
    char rgbReserved = 0;
    tagRGBQUAD(std::string hex_color)
    {
        char buffer[2];
        buffer[0]=hex_color[0]; buffer[1]=hex_color[1];
        rgbRed=(char)std::stoi(buffer, nullptr,16);
        buffer[0]=hex_color[2]; buffer[1]=hex_color[3];
        rgbGreen=(char)std::stoi(buffer, nullptr,16);
        buffer[0]=hex_color[4]; buffer[1]=hex_color[5];
        rgbBlue=(char)std::stoi(buffer, nullptr,16);
    }
};
*/

#ifndef bmp

#define bmp = 1

tagRGBQUAD operator+(const tagRGBQUAD&,const tagRGBQUAD&);
tagRGBQUAD operator*(const tagRGBQUAD&,double);

class bmp_reader
{
    FILE* img{};
    BITMAPFILEHEADER bfh{};
    BITMAPINFOHEADER bih{};
    
public:
    void open(char*);
    tagRGBQUAD get_pixel(size_t,size_t);
    BITMAPINFOHEADER get_info_header();
    BITMAPFILEHEADER get_file_header();
    void rclose();
    ~bmp_reader(){rclose();}
};

class bmp_writer
{
    FILE* img{};
    BITMAPFILEHEADER bfh{};
    BITMAPINFOHEADER bih{};

public:
    void create(char*, size_t, size_t, size_t);
    //x,y,color
    void write_pixel(size_t, size_t, tagRGBQUAD,double = 1.0);
    //start - end coords, color
    void write_line(size_t, size_t, size_t, size_t, tagRGBQUAD,double = 1.0);
    //x,y of top-left corner, digit, color
    void write_digit(size_t,size_t,int,tagRGBQUAD,double = 1.0);
    //x,y,r,color ,is hollow
    void write_circle(size_t,size_t,size_t,tagRGBQUAD,bool,double = 1.0);
    //start - end coords
    void flip_horizontal(size_t, size_t, size_t, size_t);
    //start - end coords
    void flip_vertical(size_t, size_t, size_t, size_t);
    //start - end coords
    void flip(size_t, size_t, size_t, size_t);

    void write_gradient_horizontal(size_t, size_t, size_t, size_t,tagRGBQUAD,tagRGBQUAD);
    void write_gradient_vertical(size_t, size_t, size_t, size_t,tagRGBQUAD,tagRGBQUAD);
    void write_gradient(size_t, size_t, size_t, size_t,tagRGBQUAD,tagRGBQUAD);

    //x,y,size_x,size_y,angle in  rad,color
    void write_rectangle(size_t, size_t, size_t, size_t, size_t,tagRGBQUAD,double = 1.0);

    BITMAPINFOHEADER get_info_header();
    BITMAPFILEHEADER get_file_header();

    void wclose();
    ~bmp_writer(){wclose();}

private:
    void swap_pixel(size_t, size_t, size_t, size_t);
    friend tagRGBQUAD bmp_reader::get_pixel(size_t,size_t);
    tagRGBQUAD back_color{0,0,0,0};
};

class bmp_rw:public bmp_reader,public bmp_writer{
};

#endif