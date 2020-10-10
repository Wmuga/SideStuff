//
// Created by Alex on 07.09.2020.
//

#ifndef DOUBLE_R_H
#define DOUBLE_R_H
#include <iostream>

class double_r {
    size_t radix;
    std::string iPart;
    std::string fPart;
    bool isNegative;

public:
    double_r();
    explicit double_r(const std::string&);
    double_r(const std::string&,const size_t&);
    double_r(const double&,const size_t&);

    [[nodiscard]] double get() const;
    void change_radix(const size_t&);
    void convert(const size_t&);

    friend double_r operator+(const double_r&,const double_r&);
    friend double_r operator*(const double_r&,const double_r&);
    friend double_r operator-(const double_r&,const double_r&);
    friend double_r operator/(const double_r&,const double_r&);

    double_r& operator=(const double_r&);
    double_r& operator=(const double&);
    double_r& operator=(const std::pair<std::string,size_t>&);

    friend double_r operator+=(const double_r&,const double_r&);
    friend double_r operator*=(const double_r&,const double_r&);
    friend double_r operator-=(const double_r&,const double_r&);
    friend double_r operator/=(const double_r&,const double_r&);

    friend std::ostream& operator<<(std::ostream&,const double_r&);
    friend std::istream& operator>>(std::istream&,double_r&);

    friend bool operator==(const double_r&, const double_r&);
    friend bool operator!=(const double_r&, const double_r&);
    friend bool operator<(const double_r&, const double_r&);
    friend bool operator>(const double_r&, const double_r&);
    friend bool operator<=(const double_r&, const double_r&);
    friend bool operator>=(const double_r&, const double_r&);

private:
    static int get_code(const char&);
    static char get_char(const int&);
    void split(const std::string&);
    static const std::invalid_argument diff_radix;
    static const std::invalid_argument wrong_input;
    void remove_zeros();
    static void fix(double_r*);
};


#endif //DOUBLE_R_H
