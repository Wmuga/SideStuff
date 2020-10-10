//
// Created by Alex on 31.08.2020.
//

#ifndef FRACTION_FRACTION_H
#define FRACTION_FRACTION_H
#include <iostream>
#include <vector>

class Fraction {
    double numerator;
    double denominator;
public:
    Fraction(const double&,const double&);
    explicit Fraction(const double&);
    Fraction();

    Fraction& operator=(const double&);

    friend Fraction operator+(const Fraction&,const Fraction&);
    friend Fraction operator*(const Fraction&,const Fraction&);
    friend Fraction operator-(const Fraction&,const Fraction&);
    friend Fraction operator/(const Fraction&,const Fraction&);

    friend Fraction operator+(const Fraction&,double);
    friend Fraction operator-(const Fraction&,double);
    friend Fraction operator*(const Fraction&,double);
    friend Fraction operator/(const Fraction&,double);

    friend std::ostream& operator<<(std::ostream&,const Fraction&);
    friend std::istream& operator>>(std::istream&,Fraction&);

    friend Fraction operator+=(const Fraction&,const Fraction&);
    friend Fraction operator-=(const Fraction&,const Fraction&);
    friend Fraction operator/=(const Fraction&,const Fraction&);
    friend Fraction operator*=(const Fraction&,const Fraction&);

    friend Fraction operator+=(const Fraction&,const double&);
    friend Fraction operator-=(const Fraction&,const double&);
    friend Fraction operator/=(const Fraction&,const double&);
    friend Fraction operator*=(const Fraction&,const double&);

    friend bool operator==(const Fraction&,const Fraction&);
    friend bool operator!=(const Fraction&,const Fraction&);
    friend bool operator>(const Fraction&,const Fraction&);
    friend bool operator<(const Fraction&,const Fraction&);
    friend bool operator>=(const Fraction&,const Fraction&);
    friend bool operator<=(const Fraction&,const Fraction&);

    [[nodiscard]] double get() const;
    void set(const double&,const double&);

    [[nodiscard]] double numer() const;
    [[nodiscard]] double denom() const;
    double& numer();
    double& denom();

private:
    void reduce();
    static std::vector<double> get_primes(const long&);
};


#endif //FRACTION_FRACTION_H
