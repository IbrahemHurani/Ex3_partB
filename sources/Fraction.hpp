#ifndef Fraction_HPP
#define Fraction_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <numeric>

using namespace std;
namespace ariel
{

    class Fraction
    {
    private:
        int numerator;
        int denominator;

    public:
        int getNumerator();
        int getDenominator();
        int reduce_number(int num, int res_gcd);
        void reduce_F(int res_gcd);
        void set_Numerator(int num);
        void set_Denominator(int num);
        Fraction();
        Fraction(float );
        Fraction(int , int );
        Fraction operator+(const Fraction &other);
        Fraction operator-(const Fraction &other);
        Fraction operator*(const Fraction &other);
        Fraction operator/(const Fraction &other);
        friend bool checkOverflow(const Fraction &frac1, const Fraction &frac2, char );
        friend float take_3digits(float number);



        friend Fraction operator+(float , const Fraction &other);
        friend Fraction operator-(float , const Fraction &other);
        friend Fraction operator*(float , const Fraction &other);
        friend Fraction operator/(float , const Fraction &other);

        bool operator==(const Fraction &other)const;
        bool operator>(const Fraction &other)const;
        bool operator<(const Fraction &other)const;
        bool operator>=(const Fraction &other)const;
        bool operator<=(const Fraction &other)const;

        friend bool operator==(float n, const Fraction &other);
        friend bool operator>(float n, const Fraction &other);
        friend bool operator<(float n, const Fraction &other);
        friend bool operator>=(float n, const Fraction &other);
        friend bool operator<=(float n, const Fraction &other);

        Fraction operator++(int);
        Fraction operator--(int);

        Fraction &operator++();
        Fraction &operator--();

        friend ostream &operator<<(ostream &out, const Fraction &other);
        friend istream &operator>>(istream &inp, Fraction &other);

        int gcd(int , int );
    };

};

#endif
