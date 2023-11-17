#include "liczba.h"
#include <iostream>
#include <cmath> // Include the cmath library for the modul function

using namespace std;

Liczba::Liczba(double re)
{
    cout << "Konstruktor Liczba = " << re << "\n";
    this->re = re;
}

Liczba::~Liczba()
{
    cout << "Destruktor Liczba = " << re << "\n"; // Print the value being destructed
}

double Liczba::modul()
{
    return abs(re); // Return the absolute value of the number as its modulus
}

std::ostream& operator<<(std::ostream& out, Liczba& l)
{
    out << "Liczba rzeczywista: " << l.re << "\n";
    return out;
}
