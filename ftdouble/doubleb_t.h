//
// Created by Alex on 24.10.2020.
//

#ifndef FTDOUBLE_DOUBLEB_T_H
#define FTDOUBLE_DOUBLEB_T_H

#include <string>
#include <ostream>

class doubleb_t {
    long exp;
    std::string value;

public:

    doubleb_t();
    explicit doubleb_t(int);
    explicit doubleb_t(const double&);
    explicit doubleb_t(const float&);

    doubleb_t& operator*=(const doubleb_t&);
    doubleb_t& operator/=(const doubleb_t&);
    doubleb_t& operator+=(const doubleb_t&);
    doubleb_t& operator-=(const doubleb_t&);

    friend std::ostream& operator<<(std::ostream&,doubleb_t&);

private:
    void normalize();
};


#endif //FTDOUBLE_DOUBLEB_T_H
