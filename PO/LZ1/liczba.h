#pragma once
#include <iostream>
class Wartosc_Liczbowa
{
public:
	virtual double modul() = 0; //wartoœæ bezwzglêdna
	virtual void wypisz(std::ostream& out) = 0;
	virtual ~Wartosc_Liczbowa(){}

	virtual void ExampleOverride()
	{
		std::cout << "This is a ExampleOverride() method from Wartosc_Liczbowa class \n";  
	}
};

class Liczba : public Wartosc_Liczbowa
{
	double re; //czesc rzeczywista
public:
	Liczba operator+(Liczba& right)
	{
		return Liczba(this->re + right.re);
	}
	double modul();
	Liczba(double re);
	~Liczba(void);
	friend std::ostream& operator<< (std::ostream& out, Liczba& l);
	void wypisz(std::ostream& out)
	{
		out << *this;
	}
};