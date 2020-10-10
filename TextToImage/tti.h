#ifndef TEXTTOIMAGE
#define TEXTTOIMAGE
#include <vector>

class tti{
public:
    tti();
    void make_lat_text(char *, char *);

    void make_cir_text(unsigned char *, char *);

private:
    void get_font_lat();

    void get_font_cir();

    const char* fonts_file_path = (char *) "..\\fonts\\";
    // use >> or << to fin correct letter
    size_t lat_w_size=0;
    size_t lat_h_size=0;

    size_t cir_w_size=0;
    size_t cir_h_size=0;

    std::vector<std::vector<unsigned int> > cir_letters_array{};
    std::vector<std::vector<unsigned int> > lat_letters_array{};
};

#endif
