#pragma once // Add include guards to prevent multiple inclusion
#include "liczba.h"
#include <ostream>

class Complex : public Wartosc_Liczbowa
{
protected:
    double re;
    double im; // czesc urojona
public:
    ~Complex(void);
    Complex(double re = 0, double im = 0);
    Complex operator+(const Complex& other); // Pass the other object by reference
    friend std::ostream& operator<<(std::ostream& out, const Complex& l);
    double modul();
    void wypisz(std::ostream& out)
    {
        out << *this;
    }
};