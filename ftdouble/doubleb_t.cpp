//
// Created by Alex on 24.10.2020.
//

#include "doubleb_t.h"
#include <algorithm>
#include <cmath>

void doubleb_t::normalize() {
    while(*value.rbegin()=='0' && value!="0"){
        exp++;
        value.pop_back();
    }
}

doubleb_t::doubleb_t() {
    exp=0;
    value="0";
}

doubleb_t::doubleb_t(int i) {
    exp=0;
    value = std::to_string(i);
    normalize();
}

doubleb_t::doubleb_t(const double& val) {
    exp=0;
    std::string s_val = std::to_string(val);
    long buffer_exp = 0;
    for (auto i=std::find(s_val.begin(),s_val.end(),'.')+1;i<s_val.end();i++) buffer_exp--;
    s_val.erase(std::find(s_val.begin(),s_val.end(),'.'));
    *this = doubleb_t(std::stoi(s_val));
    exp += buffer_exp;
}

doubleb_t::doubleb_t(const float& val) {
    exp=0;
    *this = doubleb_t((double)val);
}


std::ostream& operator<<(std::ostream& os,doubleb_t& d){
    std::string v = d.value;
    while (v.size()-1<std::abs(d.exp)){
        if (d.exp<0) v.insert(v.begin(),'0');
        else v.push_back('0');
    }
    if (d.exp<0) v.insert(v.begin()+(d.exp+v.size()),'.');
    os<<v;
    return os;
}

doubleb_t& doubleb_t::operator*=(const doubleb_t& v) {
    exp*=v.exp;
    return *this;
}
