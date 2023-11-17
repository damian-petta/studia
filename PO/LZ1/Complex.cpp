#include "complex.h"
#include <iostream>
#include <cmath>

using namespace std;

Complex::Complex(double re, double im)
{
    cout << "Konstruktor liczby zespolonej = " << re << "+" << im <<"i"<< "\n";
    this->re = re;
    this->im = im;
}

Complex Complex::operator+(const Complex& other) {
    return Complex(this->re + other.re, this->im + other.im); // Corrected the operator+ implementation
}


Complex::~Complex()
{
    cout << "Destruktor liczby zespolonej = " << re << "+" << im << "i" << "\n";
}

double Complex::modul()
{
    return sqrt(re * re + im * im); // Calculate the modulus correctly
}

std::ostream& operator<<(std::ostream& out, const Complex& l)
{
    out << "Liczba zespolona: " << l.re << " + " << l.im << "i" << "\n"; // Added space and "i" for the imaginary part
    return out;
}