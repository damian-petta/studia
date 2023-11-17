#pragma once
#include <iostream>
using namespace std;
class VectorNd {
	double* _liczby; //pole ze wskaünikiem liczb
	int _wymiar; //wymiar wektora

	friend ostream& operator<<(ostream& left, VectorNd& right);
	friend class VectorOfVectors1;
	friend class VectorOfVectors2;

	void wypisz(std::ostream& out);
	void wypiszV2(std::ostream& out);
public:

	VectorNd()
	{
		this->_liczby = NULL;
		this->_wymiar = 0;
	};

	VectorNd(const double liczby[], int wymiar); //konstruktor

	VectorNd(const VectorNd& oryginal);//konstruktor kopiujπcy

	~VectorNd();		//destruktor

	VectorNd& operator=(const VectorNd& right); //implementacja operatora przypisania

	double getCoef(int index) { //pomocznicza metoda
		return _liczby[index];
	}

	int getDim() { //pomocznicza metoda
		return _wymiar;
	}

	void getCoefs(double liczby[]); //metoda publiczna


	void setVector(istream& in);
	
};

