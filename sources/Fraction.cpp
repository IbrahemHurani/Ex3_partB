
#include <iostream>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Fraction.hpp"
using namespace std;
namespace ariel
{
    Fraction::Fraction()
    {
        this->numerator = 0;
        this->denominator = 1;
    }
    Fraction::Fraction(float number)
    {
        if (number == 0.0)
        {
            this->numerator = 0;
            this->denominator = 1;
        }

        float temp = number * 1000;
        temp /= 1000;
        int num = round(temp * 1000);
        int den = 1000;

        int res = gcd(num, den);
        this->numerator = num;
        this->denominator = den;
        reduce_F(res);
    }
    Fraction::Fraction(int n, int d)
    {
        if (d == 0)
        {
            throw invalid_argument("the denominator is zero");
        }
        if (n != 0)
        {
            this->numerator = n;
            this->denominator = d;
            int gcd_res = this->gcd(n, d);
            reduce_F(gcd_res);
        }
        else
        {
            this->numerator = n;
            this->denominator = d;
        }
    }
    float take_3digits(float number)
    {
        float r = roundf(number * 1000);
        float ret = r / 1000;
        return ret;
    }
    bool checkOverflow(const Fraction &fraction1, const Fraction &fraction2, char sign)
    {
        switch (sign)
        {
        case '+':
            return ((fraction1.numerator == std::numeric_limits<int>::max() && fraction1.denominator != std::numeric_limits<int>::max()) || (fraction2.denominator == std::numeric_limits<int>::max() && fraction2.denominator != std::numeric_limits<int>::max()) || (fraction1.numerator <= std::numeric_limits<int>::min() + 100) && (fraction2.numerator <= std::numeric_limits<int>::min() + 100));

        case '-':
            return ((fraction1.numerator <= std::numeric_limits<int>::min() + 100 && fraction2.numerator <= std::numeric_limits<int>::min() + 100) || (fraction1.numerator >= std::numeric_limits<int>::max() - 100 && fraction2.numerator <= std::numeric_limits<int>::min() + 100));

        case '*':
            return ((fraction1.numerator == std::numeric_limits<int>::max() && fraction1.denominator != std::numeric_limits<int>::max()) || (fraction1.denominator == std::numeric_limits<int>::max() && fraction2.numerator != std::numeric_limits<int>::max()) || (fraction2.numerator == std::numeric_limits<int>::max() && fraction2.denominator != std::numeric_limits<int>::max()) || (fraction2.denominator == std::numeric_limits<int>::max() && fraction2.denominator != std::numeric_limits<int>::max()));

        case '/':
            return ((fraction1.numerator == std::numeric_limits<int>::max() && fraction1.denominator != std::numeric_limits<int>::max()) || (fraction1.denominator == std::numeric_limits<int>::max() && fraction1.numerator < std::numeric_limits<int>::max() - 100));

        default:
            return false;
        }
    }

    Fraction Fraction::operator+(const Fraction &other)
    {
        if (this->denominator == 0 || other.denominator == 0)
        {
            throw runtime_error("the denominator can't be zero");
        }

        if (checkOverflow(*this, other, '+'))
        {
            throw std::overflow_error("Error: Overflow during addition.");
        }

        Fraction result = Fraction(this->numerator * other.denominator + this->denominator * other.numerator, this->denominator * other.denominator);
        return result;
    }
    Fraction Fraction::operator-(const Fraction &other)
    {
        if (this->denominator == 0 || other.denominator == 0)
        {
            throw runtime_error("the denominator can't be zero");
        }

        if (checkOverflow(*this, other, '-'))
        {
            throw std::overflow_error("Error: Overflow during addition.");
        }

        Fraction result = Fraction(this->numerator * other.denominator - this->denominator * other.numerator, this->denominator * other.denominator);
        return result;
    }
    Fraction Fraction::operator*(const Fraction &other)
    {
        if (this->denominator == 0 || other.denominator == 0)
        {
            throw runtime_error("the denominator can't be zero");
        }

        if (checkOverflow(*this, other, '*'))
        {
            throw std::overflow_error("Error: Overflow during addition.");
        }
        Fraction result = Fraction(this->numerator * other.numerator, this->denominator * other.denominator);
        return result;
    }
    Fraction Fraction::operator/(const Fraction &other)
    {
        if (this->denominator == 0 || other.denominator == 0 || other.numerator == 0)
        {
            throw runtime_error("the denominator can't be zero");
        }

        if (checkOverflow(*this, other, '/'))
        {
            throw std::overflow_error("Error: Overflow during addition.");
        }
        Fraction result = Fraction(this->numerator * other.denominator, this->denominator * other.numerator);
        return result;
    }
    Fraction operator+(float n, const Fraction &other)
    {
        float num = (float)other.numerator / (float)other.denominator + n;
        return Fraction(num);
    }
    Fraction operator-(float n, const Fraction &other)
    {
        float num = (float)other.numerator / (float)other.denominator;
        return Fraction(n - num);
    }
    Fraction operator*(float n, const Fraction &other)
    {
        Fraction temp(n);
        return temp * other;
    }
    Fraction operator/(float n, const Fraction &other)
    {
        Fraction temp(n);
        return temp / other;
    }

    bool Fraction::operator==(const Fraction &other) const
    {
        if (this->numerator == 0 || other.numerator == 0)
        {
            return true;
        }
        float n1 = take_3digits(static_cast<float>(this->numerator) / static_cast<float>(this->denominator));
        float n2 = take_3digits(static_cast<float>(other.numerator) / static_cast<float>(other.denominator));
        return this->numerator == other.numerator && this->denominator == other.denominator || n1 == n2;
    }
    bool Fraction::operator>(const Fraction &other) const
    {
        if ((this->numerator < 0 || this->denominator < 0) && (other.numerator < 0 || other.denominator < 0))
        {
            float n1 = static_cast<float>(this->numerator) / static_cast<float>(this->denominator);
            float n2 = static_cast<float>(other.numerator) / static_cast<float>(other.denominator);
            return n1 > n2;
        }
        return ((this->numerator * other.denominator) > (this->denominator * other.numerator));
    }
    bool Fraction::operator<(const Fraction &other) const
    {
        if ((this->numerator < 0 || this->denominator < 0) && (other.numerator < 0 || other.denominator < 0))
        {
            float n1 = static_cast<float>(this->numerator) / static_cast<float>(this->denominator);
            float n2 = static_cast<float>(other.numerator) / static_cast<float>(other.denominator);
            return n1 < n2;
        }
        return ((this->numerator * other.denominator) < (this->denominator * other.numerator));
    }
    bool Fraction::operator>=(const Fraction &other) const
    {
        return ((this->numerator * other.denominator) >= (this->denominator * other.numerator));
    }
    bool Fraction ::operator<=(const Fraction &other) const
    {
        return ((this->numerator * other.denominator) <= (this->denominator * other.numerator));
    }
    bool operator==(float n, const Fraction &other)
    {
        Fraction t(n);
        return t == other;
    }
    bool operator>(float n, const Fraction &other)
    {
        Fraction t(n);

        return ((t.numerator * other.denominator) > (t.denominator * other.numerator));
    }
    bool operator<(float n, const Fraction &other)
    {
        Fraction t(n);

        return ((t.numerator * other.denominator) < (t.denominator * other.numerator));
    }
    bool operator>=(float n, const Fraction &other)
    {
        Fraction t(n);
        return ((t.numerator * other.denominator) >= (t.denominator * other.numerator));
    }
    bool operator<=(float n, const Fraction &other)
    {
        Fraction t(n);
        return ((t.numerator * other.denominator) <= (t.denominator * other.numerator));
    }

    Fraction Fraction::operator++(int)
    {
        Fraction t(*this);
        numerator += denominator;
        int res_gcd = this->gcd(numerator, denominator);
        reduce_F(res_gcd);
        return t;
    }
    Fraction Fraction::operator--(int)
    {
        Fraction t(*this);
        numerator -= denominator;
        return t;
    }

    Fraction &Fraction::operator++()
    {
        this->numerator += this->denominator;
        return *this;
    }
    Fraction &Fraction::operator--()
    {
        numerator -= denominator;
        return *this;
    }
    ostream &operator<<(ostream &out, const Fraction &other)
    {
        out << other.numerator << "/" << other.denominator;
        return out;
    }

    istream &operator>>(istream &input, Fraction &other)
    {
        int num, den;
        
        input >> num;
        if (input.peek() == EOF)
        {
            throw runtime_error("Error: There is one number");
        }
        input >> den;
        if (den == 0)
        {
            throw runtime_error("Error: Denominator can't be 0");
        }
        if (input.fail())
        {
            input.setstate(std::ios_base::failbit);
        }
        other = Fraction(num, den);
        return input;
    }
    int Fraction::gcd(int n1, int n2)
    {

        if (n2 == 0)
        {
            throw runtime_error("the denominator can't be zero");
        }

        n1 = (n1 < 0) ? (n1 * (-1)) : n1;
        n2 = (n2 < 0) ? (n2 * (-1)) : n2;
        int temp;
        while (n2 != 0)
        {
            temp = n2;
            n2 = n1 % n2;
            n1 = temp;
        }
        return n1;
    }

    int Fraction::reduce_number(int num, int res_gcd)
    {
        num /= res_gcd;
        return num;
    }
    void Fraction::reduce_F(int res_gcd)
    {
        if (this->denominator < 0)
        {
            this->numerator *= (-1);
            this->denominator *= (-1);
        }
        this->numerator /= res_gcd;
        this->denominator /= res_gcd;
    }
    int Fraction::getNumerator()
    {
        return this->numerator;
    }
    int Fraction::getDenominator()
    {
        return this->denominator;
    }
    void Fraction::set_Denominator(int num)
    {
        this->denominator = num;
    }
    void Fraction::set_Numerator(int num)
    {
        this->numerator = num;
    }
}
