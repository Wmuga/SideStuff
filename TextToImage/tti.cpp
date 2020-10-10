#include "tti.h"
#include "bmp.h"
#include <cmath>


tti::tti() {
    get_font_lat();
    get_font_cir();
}

void tti::get_font_lat() {
    //opening file
    bmp_reader fin;
    char* in_name = new char[256];
    sprintf(in_name,"%sletters_lat.bmp",fonts_file_path);
    fin.open(in_name);

    tti::lat_w_size = (fin.get_info_header().biWidth+1)/26;
    tti::lat_h_size = fin.get_info_header().biHeight;

    for (size_t j=0;j<tti::lat_h_size;j++)  { std::vector<unsigned int> line;
        for (size_t i=0;i<tti::lat_w_size;i++) line.push_back(1);
        tti::lat_letters_array.push_back(line);
    }

    for (size_t j=0;j<lat_h_size;j++)  {
        for (size_t i=0;i<lat_w_size;i++)
        {
            for (size_t ch = 26; ch > 0; ch--) {
                tti::lat_letters_array[j][i] *= 2;
                if (fin.get_pixel(i + (ch - 1) * 6, j).rgbRed == 0) tti::lat_letters_array[j][i]++;
            }
        }
    }

    fin.rclose();
    delete []in_name;
}

void tti::get_font_cir() {
    //opening file
    bmp_reader fin;
    char* in_name = new char[256];
    sprintf(in_name,"%sletters_cir.bmp",fonts_file_path);
    fin.open(in_name);

    tti::cir_w_size = (fin.get_info_header().biWidth+1)/26-1;
    tti::cir_h_size = fin.get_info_header().biHeight;

    for (size_t j=0;j<tti::cir_h_size;j++)  { std::vector<unsigned int> line;
        for (size_t i=0;i<tti::lat_w_size;i++) line.push_back(1);
        tti::cir_letters_array.push_back(line);
    }

    for (size_t j=0;j<cir_h_size;j++)  {
        for (size_t i=0;i<cir_w_size;i++)
        {
            for (size_t ch = 26; ch > 0; ch--) {
                tti::cir_letters_array[j][i] *= 2;
                if (fin.get_pixel(i + (ch - 1) * 6, j).rgbRed == 0) tti::cir_letters_array[j][i]++;
            }
        }
    }

    fin.rclose();
    delete []in_name;
}

void tti::make_lat_text(char *text, char *filename) {
    size_t count = strlen(text);
    bmp_writer text_out;

    text_out.create(filename,(lat_w_size+1)*count+1,lat_h_size+2,24);
    for (size_t ch=0;ch<count;ch++)
    {
        for (size_t j=0;j<lat_h_size;j++)
        {
            for (size_t i=0;i<lat_w_size;i++)
            {
                unsigned int num = lat_letters_array[j][i];
                if (text[ch]!=' ' && (size_t)(num/pow(2,(text[ch]-'a')))%2==1)
                    text_out.write_pixel(1+i+ch*(lat_w_size+1),j+1,{255,255,255,0});
            }
        }
    }
    text_out.wclose();
}