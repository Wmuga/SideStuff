#include "resizer.h"
#include <iostream>
#include <algorithm>
#include <fstream>

void resizer::resize(char* img_in, char* img_out,size_t new_width,size_t new_height)
{
    bmp_reader fin;
    fin.open(img_in);
    size_t s_width = fin.get_info_header().biWidth,s_height = fin.get_info_header().biHeight;
    size_t bit_count = fin.get_info_header().biBitCount;
    bmp_writer fout;
    fout.create(img_out,new_width,new_height,bit_count);
    double step_x = (double)s_width/(double)new_width;
    double step_y = (double)s_height/(double)new_height;
    std::clog << step_x << " " << step_y;
    size_t y=0;
    double j=0;
    while(y<new_height)
    {
        size_t x=0;
        double i=0;
        while(x<new_width)
        {
            fout.write_pixel((size_t)x, (size_t)y, fin.get_pixel((size_t)i, (size_t)j));
            x++;
            i+=step_x; if (i>s_width) i = s_width-1;
        }
        y++;
        j+=step_y; if (j>s_height) j = s_height-1;
    }
    fin.rclose();
}

void resizer::increase_width_smart(char* img_in, char* img_out)
{
    bmp_reader fin;
    fin.open(img_in);
    size_t s_width = fin.get_info_header().biWidth,s_height = fin.get_info_header().biHeight;
    size_t bit_count = fin.get_info_header().biBitCount;
    bmp_writer fout;
    fout.create(img_out,s_width*2,s_height,bit_count);
    for (size_t j=0;j<s_height;j++) fout.write_pixel(0,j,fin.get_pixel(0,j));
    for (size_t j=0;j<s_height;j++) {
        size_t i1=2;
        for (size_t i = 1; i < s_width; i++)
        {
            fout.write_pixel(i1,j,fin.get_pixel(i,j));
            tagRGBQUAD new_color{0,0,0,0};
            new_color.rgbBlue = fin.get_pixel(i-1,j).rgbBlue/2+fin.get_pixel(i,j).rgbBlue/2;
            new_color.rgbRed = fin.get_pixel(i-1,j).rgbRed/2+fin.get_pixel(i,j).rgbRed/2;
            new_color.rgbGreen = fin.get_pixel(i-1,j).rgbGreen/2+fin.get_pixel(i,j).rgbGreen/2;
            new_color.rgbReserved = fin.get_pixel(i-1,j).rgbReserved/2+fin.get_pixel(i,j).rgbReserved/2;
            fout.write_pixel(i1-1,j,new_color);
            i1+=2;
        }
    }
    fin.rclose();
    fout.wclose();
}

void resizer::increase_height_smart(char* img_in, char* img_out)
{
    bmp_reader fin;
    fin.open(img_in);
    size_t s_width = fin.get_info_header().biWidth,s_height = fin.get_info_header().biHeight;
    size_t bit_count = fin.get_info_header().biBitCount;
    bmp_writer fout;
    fout.create(img_out,s_width,s_height*2,bit_count);
    for (size_t i = 1; i < s_width; i++) fout.write_pixel(i,0,fin.get_pixel(i,0));
    for (size_t i = 0; i < s_width; i++) {
        size_t j1=2;
        for (size_t j=1;j<s_height;j++)
        {
            fout.write_pixel(i,j1,fin.get_pixel(i,j));
            tagRGBQUAD new_color{0,0,0,0};
            new_color.rgbBlue = fin.get_pixel(i,j-1).rgbBlue/2+fin.get_pixel(i,j).rgbBlue/2;
            new_color.rgbRed = fin.get_pixel(i,j-1).rgbRed/2+fin.get_pixel(i,j).rgbRed/2;
            new_color.rgbGreen = fin.get_pixel(i,j-1).rgbGreen/2+fin.get_pixel(i,j).rgbGreen/2;
            new_color.rgbReserved = fin.get_pixel(i,j-1).rgbReserved/2+fin.get_pixel(i,j).rgbReserved/2;
            fout.write_pixel(i,j1-1,new_color);
            j1+=2;
        }
    }
    fin.rclose();
    fout.wclose();
}

void resizer::increase_smart(char *img_in, char *img_out) {
    increase_width_smart(img_in, (char *) "buffer.bmp");
    increase_height_smart((char *) "buffer.bmp", img_out);
    remove((char *) "buffer.bmp");
}

void resizer::add_lines(char* img,size_t new_x,size_t new_y)
{
    bmp_reader fin;
    fin.open(img);
    bmp_writer fout;
    fout.create((char*)"buffer\\buffer",fin.get_info_header().biWidth+new_x,fin.get_info_header().biHeight+new_y,fin.get_info_header().biBitCount);
    for (size_t j=0;j<fin.get_info_header().biHeight;j++) {
        for (size_t i = 0; i < fin.get_info_header().biWidth; i++) fout.write_pixel(i, j, fin.get_pixel(i, j));
    }
    fin.rclose();
    fout.wclose();
    remove(img);
    rename((char*)"buffer\\buffer",img);
}


void resizer::liquid_resize(char* img_in, char* img_out,int add_count) {
    remove(img_out);
    std::ifstream src(img_in, std::ios::binary);
    std::ofstream dst(img_out, std::ios::binary);
    dst << src.rdbuf();
    src.close();
    dst.close();

    add_lines(img_out,add_count,0);

    bmp_rw fout;
    fout.open(img_out);
    get_energy_pallet(fout);

    bmp_writer pallet_out;
    pallet_out.create((char*)"buffer\\pallet.bmp",fout.get_info_header().biWidth-add_count,fout.get_info_header().biHeight,24);
    draw_energy_pallet(pallet_out,fout.get_info_header().biWidth-add_count,fout.get_info_header().biHeight);
    pallet_out.wclose();

    get_paths_array(fout.get_info_header().biWidth-add_count,fout.get_info_header().biHeight);
    get_path(fout.get_info_header().biWidth-add_count,fout.get_info_header().biHeight,add_count);
    std::sort(line_coords.begin(),line_coords.end(),[](std::vector<std::pair<int,int> > v1,std::vector<std::pair<int,int> > v2){
        return v1[0].first>v2[0].first;
    });

    for (size_t added_x=0;added_x<add_count;added_x++) {
        std::clog << "\rcolumn:" << added_x;
        for (size_t j = fout.get_info_header().biHeight; j >0 ; j--) {
            for (size_t i = 0; i < fout.get_info_header().biWidth; i++)
            {
                std::pair<int,int> _pair = std::make_pair(i,j-1);
                std::vector<std::pair<int,int> > line = line_coords[added_x];
                if (line[fout.get_info_header().biHeight-j]==_pair)
                {
                    //if (j==fout.get_info_header().biHeight) std::clog << i << " " << j-1 << "\n";
                   //fout.push_with_new(i+added_x,j-1,{255,255,255,0});
                   fout.push_with_new(i,j-1,fout.get_pixel(i,j-1));
                }
            }
        }
    }
    fout.close();
}

void resizer::get_energy_pallet(bmp_rw& fin) {
    for (size_t i=0;i<fin.get_info_header().biWidth-1;i++)
    {
        std::vector<int> energy_line;
        for (size_t j=0;j<fin.get_info_header().biHeight-1;j++)
        {
            tagRGBQUAD current_color = fin.get_pixel(i,j);
            tagRGBQUAD down_color = fin.get_pixel(i,j+1);
            tagRGBQUAD next_color = fin.get_pixel(i+1,j);
            energy_line.push_back(
                            std::abs(current_color.rgbRed-down_color.rgbRed)/8+std::abs(current_color.rgbRed-next_color.rgbRed)/8+
                            std::abs(current_color.rgbBlue-down_color.rgbBlue)/8+std::abs(current_color.rgbBlue-next_color.rgbBlue)/8+
                            std::abs(current_color.rgbGreen-down_color.rgbGreen)/8+std::abs(current_color.rgbGreen-next_color.rgbGreen)/8
                    );
        }
        tagRGBQUAD current_color = fin.get_pixel(i,fin.get_info_header().biHeight-1);
        tagRGBQUAD next_color = fin.get_pixel(i+1,fin.get_info_header().biHeight-1);
        energy_line.push_back(
                std::abs(current_color.rgbRed-next_color.rgbRed)/8+
                std::abs(current_color.rgbBlue-next_color.rgbBlue)/8+
                std::abs(current_color.rgbGreen-next_color.rgbGreen)/8
        );
        energy_array.push_back(energy_line);
    }
    std::vector<int> energy_line;
    for (size_t j=0;j<fin.get_info_header().biHeight-1;j++)
    {
        tagRGBQUAD current_color = fin.get_pixel(fin.get_info_header().biWidth-1,fin.get_info_header().biHeight-2);
        tagRGBQUAD down_color = fin.get_pixel(fin.get_info_header().biWidth-1,fin.get_info_header().biHeight-1);
        energy_line.push_back(
                std::abs(current_color.rgbRed-down_color.rgbRed)/8+
                std::abs(current_color.rgbBlue-down_color.rgbBlue)/8+
                std::abs(current_color.rgbGreen-down_color.rgbGreen)/8
        );
    }
    energy_line.push_back(0);
    energy_array.push_back(energy_line);

}

void resizer::draw_energy_pallet(bmp_writer& fout,size_t s_width, size_t s_height) {
    for (size_t i=0;i<s_width;i++)
    {
        for (size_t j=0;j<s_height;j++)
        {
            tagRGBQUAD _color {0,0,0,0};
            _color.rgbBlue = 255-energy_array[i][j];
            _color.rgbRed = 255-energy_array[i][j];
            _color.rgbGreen = 255-energy_array[i][j];
            fout.write_pixel(i,j,_color);
        }
    }
}

void resizer::get_paths_array(size_t xmax, size_t ymax) {
    std::vector<int> energy_line_zero;
    for (size_t i=0;i<xmax;i++) energy_line_zero.push_back(energy_array[0][i]);
    energy_path_array.push_back(energy_line_zero);
    for (size_t j=1;j<ymax;j++)
    {
        std::vector<int> energy_line;
        energy_line.push_back(energy_array[0][j-1]+energy_array[1][j-1]+energy_array[0][j]);
        for (size_t i=1;i<xmax-1;i++) energy_line.push_back(energy_array[i-1][j-1]+energy_array[i][j-1]+energy_array[i+1][j-1]+energy_array[i][j]);
        energy_line.push_back(energy_array[xmax-1-1][j-1]+energy_array[xmax-1][j-1]+energy_array[xmax-1][j]);
        energy_path_array.push_back(energy_line);
    }
}

void resizer::get_path(size_t xmax, size_t ymax,size_t count) {
    transpose(xmax,ymax);
    for (size_t it = 0; it < count; it++) {
        std::vector<std::pair<int, int> > line_coord;
        for (size_t j = ymax; j != 0; j--) {
            auto buffer = energy_array[j-1];
            std::sort(buffer.begin(),buffer.end(),[](int a,int b){return a>b;});
            auto value= buffer[0];
            int x; for (size_t i=0;i<xmax;i++) if (energy_array[j-1][i]==value) x=i;
            std::pair<int, int> dot{x, j - 1};
            if (j == ymax) {
                for (size_t i = 0; i < xmax; i++) {
                    if (energy_path_array[j - 1][dot.first] > energy_path_array[j - 1][i] && energy_path_array[j - 1][i] != 0) {
                        if (!line_coords.empty()) {
                            bool is_unique = true;
                            for (auto lines: line_coords) {
                                if (lines[0].first-2 == i || lines[0].first-1 == i || lines[0].first == i || lines[0].first+1 == i || lines[0].first+2 == i) {
                                    is_unique = false;
                                    break;
                                }
                            }
                            if (is_unique) dot.first = i;
                        } else {
                            dot.first = i;
                        }
                    }
                }
            } else {
                size_t start_pos = line_coord[ymax - j - 1].first == 0 ? 0 : line_coord[ymax - j - 1].first - 1;
                size_t end_pos = line_coord[ymax - j - 1].first == xmax - 1 ? xmax - 1 : line_coord[ymax - j - 1].first + 1;
                dot.first = end_pos;
                for (size_t i = start_pos; i <= end_pos; i++) {
                    if (energy_path_array[j - 1][dot.first] > energy_path_array[j - 1][i] &&
                        energy_path_array[j - 1][i] != 0) {
                       // dot.first = i;
                        bool is_unique = true;
                        for (auto lines: line_coords) {
                            if (lines[0].first-2 == i || lines[0].first-1 == i || lines[0].first == i || lines[0].first+1 == i || lines[0].first+2 == i) {
                                is_unique = false;
                                break;
                            }
                        }
                        if (is_unique) dot.first = i;
                    }
                }
            }
            line_coord.push_back(dot);
        }
        line_coords.push_back(line_coord);
    }
    transpose(ymax,xmax);
}

void resizer::transpose(size_t mx,size_t my){
    std::vector<std::vector<int> > array_temp{};
    for (size_t j=0;j<my;j++)
    {
        std::vector<int> new_line{};
        for (size_t i=0;i<mx;i++)
            new_line.push_back(energy_array[i][j]);
        array_temp.push_back(new_line);
    }
    this->energy_array=array_temp;
}