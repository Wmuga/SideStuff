//
// Created by Alex on 31.08.2020.
//

#include "Fraction.h"
#include <cmath>
#include <algorithm>

Fraction::Fraction(const double& numerator_, const double& denominator_):numerator(numerator_),denominator(denominator_) {
    reduce();
}

Fraction::Fraction(const double& source) {
    *this = source;
    reduce();
}

Fraction::Fraction():numerator(0),denominator(1) {
}

Fraction &Fraction::operator=(const double & source) {
    this->numerator = source;
    this->denominator = 1;
    reduce();
    return *this;
}


double Fraction::get() const {
    return numerator/denominator;
}

Fraction operator+(const Fraction & source, double add) {
    return Fraction(source.numerator+add*source.denominator,source.denominator);
}

Fraction operator-(const Fraction & source, double add) {
    return Fraction(source.numerator-add*source.denominator,source.denominator);
}

Fraction operator*(const Fraction & source, double add) {
    return Fraction(source.numerator*add,source.denominator);
}

Fraction operator/(const Fraction & source, double add) {
    return Fraction(source.numerator,source.denominator*add);
}

Fraction operator+(const Fraction & source, const Fraction & add) {
    Fraction newFraction =source+add.get();
    newFraction.reduce();
    return newFraction;
}

Fraction operator*(const Fraction & source, const Fraction & add) {
    Fraction newFraction = source*add.get();
    newFraction.reduce();
    return newFraction;
}

Fraction operator-(const Fraction & source, const Fraction & add) {
    Fraction newFraction = source-add.get();
    newFraction.reduce();
    return newFraction;
}

Fraction operator/(const Fraction & source, const Fraction & add) {
    Fraction newFraction = source/add.get();
    newFraction.reduce();
    return newFraction;
}

void Fraction::reduce() {
    while (
            (numerator != static_cast<double>(static_cast<long int>(numerator))) ||
            (denominator != static_cast<double>(static_cast<long int>(denominator)))
            ) {
        numerator *= 10;
        denominator *= 10;
    }
    auto primes = get_primes(ceil(sqrt(std::min(numerator, denominator))));
    bool changed;
    do {
        changed=false;
        for (const auto &item : primes) {
            if (
                    static_cast<long>(numerator) % static_cast<long>(item) == 0 &&
                    static_cast<long>(denominator) % static_cast<long>(item) == 0
                    ) {
                numerator /= item;
                denominator /= item;
                if (!changed) changed=true;
            }
        }
    }while (changed);
}

std::vector<double> Fraction::get_primes(const long& last_num) {
    std::vector<double> primes = {2,3};
    for (long i = 5;i<last_num;i+=2){
        bool is_prime = true;
        for (const auto& item:primes){
            if (i%static_cast<long>(item)==0){
                is_prime=false;
                break;
            }
        }
        if (is_prime) primes.push_back(static_cast<double>(i));
    }
    return primes;
}

std::ostream &operator<<(std::ostream & os, const Fraction & out){
    os << out.numerator << "/" << out.denominator;
    return os;
}

std::istream &operator>>(std::istream & is, Fraction & in) {
    std::string sin;
    is >> sin;

    std::string numerator,denominator;
    auto slash = std::find(sin.begin(),sin.end(),'/');
    std::copy(sin.begin(),slash,std::back_inserter(numerator));
    std::copy(slash+1,sin.end(),std::back_inserter(denominator));

    in = Fraction(stof(numerator),stof(denominator));

    return is;
}

void Fraction::set(const double & num, const double & den) {
    numerator=num;
    denominator=den;
    reduce();
}

double Fraction::numer() const{
    return numerator;
}

double Fraction::denom() const{
    return denominator;
}

double &Fraction::numer() {
    return numerator;
}

double &Fraction::denom() {
    return denominator;
}

Fraction operator+=(const Fraction & l, const Fraction & r) {
    return l+r;
}

Fraction operator-=(const Fraction & l, const Fraction & r) {
    return l-r;
}

Fraction operator/=(const Fraction & l, const Fraction & r) {
    return l/r;
}

Fraction operator*=(const Fraction & l, const Fraction & r) {
    return l*r;
}

Fraction operator+=(const Fraction & l , const double & r) {
    return l+r;
}

Fraction operator-=(const Fraction & l , const double & r) {
    return l-r;
}

Fraction operator/=(const Fraction & l , const double & r) {
    return l/r;
}

Fraction operator*=(const Fraction & l , const double & r) {
    return l*r;
}

bool operator==(const Fraction & l, const Fraction & r) {
    return (l.numerator==r.numerator && l.denominator==r.denominator);
}

bool operator!=(const Fraction & l, const Fraction & r) {
    return !(l==r);
}

bool operator>(const Fraction & l, const Fraction & r) {
    return l.get()>r.get();
}

bool operator<(const Fraction & l, const Fraction & r) {
    return (!(l>r) && l!=r);
}

bool operator>=(const Fraction & l, const Fraction & r) {
    return (l>r || l==r);
}

bool operator<=(const Fraction & l, const Fraction & r) {
    return (l<r || l==r);
}
