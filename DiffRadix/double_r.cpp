//
// Created by Alex on 07.09.2020.
//

#include "double_r.h"
#include <stdexcept>
#include <cmath>

const std::invalid_argument double_r::diff_radix  = std::invalid_argument("Different radix");
const std::invalid_argument double_r::wrong_input = std::invalid_argument("wrong input");

double_r::double_r():radix(0),isNegative(false) {

}

double_r::double_r(const std::string& in) {
    std::string buffer = in;
    isNegative = false;
    if (in[0]=='-'){
        isNegative = true;
        buffer = buffer.substr(1, buffer.size() - 1);
    }
    radix = 2;
    for (const char& item: buffer){
        int code = get_code(item);
        if (radix<=code) radix = code+1;
    }
    split(buffer);
}

double_r::double_r(const std::string& in, const size_t& r):radix(r) {
    if (in[0]=='-'){
        isNegative=true;
        split(in.substr(1,in.size()-1));
    }
    else{
        isNegative = false;
        split(in);
    }
}

double_r::double_r(const double& in, const size_t& r):radix(r) {
    for (const char& c : std::to_string(in)){
        if (c!='.' && c!='-'){
            if ((c-'0')>=r) throw wrong_input;
        }
    }
    isNegative = in != std::abs(in);
    iPart = std::to_string(static_cast<int>(std::abs(in)));
    fPart = std::to_string(std::abs(in)-(double) static_cast<int>(std::abs(in)));
    fPart = fPart.substr(2,fPart.size()-2);
    remove_zeros();
}

void double_r::split(const std::string& in) {
    bool isI = true;
    for (const char& c : in){
        if (c=='.') isI=false;
        else {
            if ( !(isdigit(c) || isalpha(c)) || get_code(c)>radix) throw wrong_input;
            isI ? iPart += tolower(c) : fPart += tolower(c) ;
        }
    }
}

std::ostream &operator<<(std::ostream& os, const double_r& source) {
    if (source.isNegative && !source.iPart.empty()) os << "-";
    if (source.iPart.empty()) os << "0";
    else{
        os << source.iPart;
        if (!source.fPart.empty()) os << "." << source.fPart;
    }
    return os;
}

double_r& double_r::operator=(const double& in) {
    *this = double_r(in,10);
    return *this;
}

double_r& double_r::operator=(const double_r& in) {
    this->iPart=in.iPart;
    this->fPart=in.fPart;
    this->isNegative=in.isNegative;
    this->radix=in.radix;
    return *this;
}

void double_r::remove_zeros() {
    while(*(iPart.begin()) =='0') iPart=iPart.substr(1,iPart.size()-1);
    while(*(fPart.rbegin())=='0') fPart.pop_back();
}

double_r &double_r::operator=(const std::pair<std::string, size_t>& in) {
    *this = double_r(in.first,in.second);
    return *this;
}

void double_r::change_radix(const size_t& r) {
    for (const char& c : iPart){
        if (c>=r) {
            convert(r);
            break;
        }
    }
    for (const char& c : fPart){
        if (c>=r) {
            convert(r);
            break;
        }
    }
    radix=r;
}

void double_r::convert(const size_t& r) {
    double in = this->get();
    radix=r;
    if (in != 0) {
        char buffer[256];
        itoa(std::abs(static_cast<int>(in)), buffer, radix);
        isNegative = in!=std::abs(in);
        iPart = buffer;
        fPart = "";
        double fract = in - (double) static_cast<int>(in);
        while (static_cast<int>(fract * 10)) {
            int cur = static_cast<int>(fract * radix);
            if (cur >= 10) cur = cur - '0' + 'a';
            fPart += (static_cast<char>(cur) + '0');
            fract = fract * radix - (double) static_cast<int>(fract * radix);
        }
    }
    else{
        isNegative=false;
        iPart="0";
        fPart="";
    }
}


std::istream &operator>>(std::istream& is, double_r& in) {
    return is;
}

double double_r::get() const{
    double result = 0;
    for (size_t i=0;i<iPart.size();i++){
        double cur = static_cast<double>(get_code(iPart[iPart.size()-1-i]));
        result+=cur*pow(radix,i);
    }
    for (size_t i=0;i<fPart.size();i++){
        double cur = static_cast<double>(get_code(*(fPart.begin()+i)));
        result+=cur/pow(radix,i+1);
    }
    return (isNegative) ? -1*result : result;
}

double_r operator+(const double_r& l, const double_r& r) {

    if (r.radix!=l.radix) throw double_r::diff_radix;

    if (r.isNegative && !l.isNegative) {
        double_r r1 = r;
        r1.isNegative = false;
        return l-r1;
    }
    if (l.isNegative && !r.isNegative) {
        double_r l1 = l;
        l1.isNegative=false;
        double_r result = r-l1;
        result.isNegative=!result.isNegative;
        return result;
    }

    if (l.isNegative && r.isNegative){
        double_r r1=r,l1=l;
        r1.isNegative=false;
        l1.isNegative=false;
        double_r res = l1+r1;
        res.isNegative=true;
        return res;
    }

    double_r res;
    res.isNegative=false;
    res.radix=l.radix;

    size_t min_length = std::min(l.fPart.size(),r.fPart.size());
    std::string strMin = (l.fPart.size()<r.fPart.size()) ? l.fPart : r.fPart;
    std::string strMax = (l.fPart.size()<r.fPart.size()) ? r.fPart : l.fPart;
    std::string strPartsBuffer;
    if (strMin.size()!=strMax.size()) std::copy(strMax.begin()+min_length,strMax.end(),std::back_inserter(strPartsBuffer));

    for (size_t i= min_length;i>0;i--)
        res.fPart.insert(res.fPart.begin(),double_r::get_char(double_r::get_code(l.fPart[i-1])+double_r::get_code(r.fPart[i-1])));

    res.fPart+=strPartsBuffer;

    min_length = std::min(l.iPart.size(),r.iPart.size());
    strMin = (l.iPart.size()<r.iPart.size()) ? l.iPart : r.iPart;
    strMax = (l.iPart.size()<r.iPart.size()) ? r.iPart : l.iPart;
    strPartsBuffer="";
    if (strMin.size()!=strMax.size()) std::copy(strMax.begin(),strMax.end()-min_length,std::back_inserter(strPartsBuffer));

    for (size_t i =0; i < min_length;i++)
        res.iPart.insert(res.iPart.begin(),double_r::get_char(double_r::get_code(l.iPart[l.iPart.size()-1-i])+double_r::get_code(r.iPart[r.iPart.size()-1-i])));

    res.iPart = strPartsBuffer+res.iPart;
    double_r::fix(&res);

    return res;
}

double_r operator*(const double_r &, const double_r &) {
    return double_r();
}

double_r operator-(const double_r& l, const double_r& r) {
    if (l.radix!=r.radix) throw double_r::diff_radix;
    if (l==r) {
        double_r res;
        res.radix = l.radix;
        return res;
    }
    if (l<r) {
        double_r res = r-l;
        res.isNegative=true;
        return res;
    }
    double_r res = l;

    res.iPart[0]=double_r::get_char(double_r::get_code(res.iPart[0])-1);

    for (auto i = res.iPart.begin()+1;i<res.iPart.end();i++)
        *i = double_r::get_char(double_r::get_code(*i)+static_cast<int>(res.radix-1));

    for (auto i = res.fPart.begin();i<res.fPart.end()-1;i++)
        *i = double_r::get_char(double_r::get_code(*i)+static_cast<int>(res.radix-1));

    *(res.fPart.end()-1) = double_r::get_char(
            double_r::get_code(*(res.fPart.end()-1))
                    +static_cast<int>(res.radix));

    size_t min_length = std::min(l.iPart.size(),r.iPart.size());
    for (size_t i=0;i<min_length;i++) {
        int res_c = double_r::get_code(*(res.iPart.rbegin() + i));
        int r_c = double_r::get_code(*(r.iPart.rbegin() + i));
        *(res.iPart.rbegin() + i) = double_r::get_char(
                 res_c-r_c
                );
    }

    min_length = std::min(l.fPart.size(),r.fPart.size());
    for (size_t i=0;i<min_length;i++){
        int res_c = double_r::get_code(*(res.fPart.begin() + i));
        int r_c = double_r::get_code(*(r.fPart.begin() + i));
        *(res.fPart.begin() + i) = double_r::get_char(
                res_c-r_c
        );
    }

    double_r::fix(&res);
    return res;
}

double_r operator/(const double_r &, const double_r &) {
    return double_r();
}

int double_r::get_code(const char& c) {
    int code = c - '0';
    if (code>9) code =tolower(code + '0') - 'a'+10;
    return code;
}

char double_r::get_char(const int& i) {
    return static_cast<char>( (i<10) ? i+'0' : i-10+'a');
}

void double_r::fix(double_r* value) {
    const size_t& rdx = value->radix;
    int transp_num = 0;
    for (auto i = value->fPart.rbegin();i<value->fPart.rend();i++){
        int cur_code = get_code(*i)+transp_num;
        transp_num=0;
        if (cur_code>=rdx){
            transp_num= cur_code/static_cast<int>(rdx);
            cur_code%=static_cast<int>(rdx);
        }
        *i = get_char(cur_code);
    }
    for (auto i = value->iPart.rbegin();i<value->iPart.rend();i++){
        int cur_code = get_code(*i)+transp_num;
        transp_num=0;
        if (cur_code>=rdx){
            transp_num= cur_code/static_cast<int>(rdx);
            cur_code%=static_cast<int>(rdx);
        }
        *i = get_char(cur_code);
    }
    if (transp_num) value->iPart =get_char(transp_num)+value->iPart;
    (*value).remove_zeros();
}

bool operator==(const double_r& l, const double_r& r) {
    return l.get()==r.get();
}

bool operator!=(const double_r& l, const double_r& r) {
    return !(l==r);
}

bool operator<(const double_r& l, const double_r& r) {
    return l.get()<r.get();
}

bool operator>(const double_r& l, const double_r& r) {
    return l.get()>r.get();
}

bool operator<=(const double_r& l, const double_r& r) {
    return l.get()<=r.get();
}

bool operator>=(const double_r& l, const double_r& r) {
    return l.get()>=r.get();
}
