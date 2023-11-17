#include "VectorNd.h"
using namespace std;

VectorNd::VectorNd(const double liczby[], int wymiar) { //konstruktor
	_liczby = new double[wymiar];
	_wymiar = wymiar;
	for (int i = 0; i < _wymiar; i++)
		_liczby[i] = liczby[i];
}

VectorNd::VectorNd(const VectorNd& oryginal) { //konstruktor kopiuj¹cy
	//cout << "\nKonstruktor kopiujacy wywolany\n";
	_liczby = new double[oryginal._wymiar];
	_wymiar = oryginal._wymiar;
	for (int i = 0; i < _wymiar; i++)
		_liczby[i] = oryginal._liczby[i];
}

VectorNd::~VectorNd() {			//destruktor
	//cout << "zwalniam pamiec pod adresem: " << this << endl;
	delete[] _liczby;
}

VectorNd& VectorNd::operator=(const VectorNd& right) { //implementacja operatora przypisania
	if (_wymiar != right._wymiar) { //gdy zgodne wymiary nie potrzeba realokowaæ pamiêci
		delete[] _liczby;
		_liczby = new double[right._wymiar]; //alokacja pamiêci dla nowego wymiaru
		_wymiar = right._wymiar;
	}
	for (int i = 0; i < _wymiar; i++)
		_liczby[i] = right._liczby[i];
	return *this;
}

void VectorNd::getCoefs(double liczby[]) { //metoda publiczna
	for (int i = 0; i < _wymiar; i++)
		liczby[i] = _liczby[i];
}

void VectorNd :: wypisz(ostream& out = cout) {
	out << "|-------------------------BEGIN------------------------------ | " << endl;
	out << "Jestem wektorem pod adresem: " << this << endl;
	out << "Mój wymiar to: " << _wymiar << endl;
	out << "A elementy:" << endl;
	for (int i = 0; i < _wymiar; i++)
		out << "[" << i << "] = \t" << _liczby[i] << endl;
	out << "|--------------------------END------------------------------- | " << endl;
}

void VectorNd::wypiszV2(ostream& out = cout) {
	out << "|----------BEGIN------------------------------|" << endl;
	out << "Jestem wektorem pod adresem: " << this << endl;

	out << "Mój wymiar to: " << _wymiar << endl;
	out << "A elementy:" << endl;
	for (int i = 0; i < _wymiar; i++)
		out << "[" << i << "] = \t" << getCoef(i) << endl;
	out << "|-----------END-------------------------------|" << endl;


}

void VectorNd::setVector(istream& in = cin) {
	cout << "Size of Vector: ";
	in >> _wymiar;
	_liczby = new double[_wymiar];
	for (int i = 0; i < _wymiar; i++) {
		cout << "Set coefs nr" << i << ": ";
		in >> _liczby[i];
	}
}