#include "VectorOfVectors1.h"


VectorOfVectors1::VectorOfVectors1() {
	std::cout << "I am " << this << " object of VectorOfVectors1 class and I've been initialized by an empty constructor \n";
	this->size = 0;
}

VectorOfVectors1::VectorOfVectors1(int size ) {
	this->size = size;
}

VectorOfVectors1::VectorOfVectors1(int size, const VectorNd vectors[]) { // constructor
	std::cout << "I am " << this << " object of VectorOfVectors1 class and I've been initialized by a normal constructor \n";
	this->size = size;
	for (int i = 0; i < size; i++)
		this->vectors[i] = vectors[i];
}

VectorOfVectors1::~VectorOfVectors1() {
	std::cout << "I am "<<this<<" object of VectorOfVectors1 class and I'm going to be destroyed \n";
}

VectorOfVectors1::VectorOfVectors1(const VectorOfVectors1& orginal) { // copy constructor 
	std::cout << "I am " << this << " object of VectorOfVectors1 class and I've been copied by a copy constructor \n";
	for (int i = 0; i < orginal.size; i++)
		this->vectors[i] = orginal.vectors[i];
	this->size = orginal.size;
}

VectorOfVectors1& VectorOfVectors1::operator=(VectorOfVectors1& right)
{
	std::cout << "We're going to copy-swap thingies to other object \n";
	VectorOfVectors1 tmp(right);
	std::swap(this->size,tmp.size );
	std::swap(this->vectors,tmp.vectors);
	std::cout << "Done \n";
	return *this;
}


void VectorOfVectors1::print(ostream& out = cout) {
	out << "This is a vector array " << this << "\n";
	out << "Size: " << size << "\n";
	out << "Content: " << "\n";
	for (int i = 0; i < size; i++) {
		out << "Vector nr. " << i << " : \n";
		for (int j = 0; j < vectors[i]._wymiar; j++)
			out << "[" << j << "] = \t" << vectors[i]._liczby[j] << endl;
		cout << "\n";
	}

}

void VectorOfVectors1::insert(istream& in = cin) {
	cout << "Enter size: ";
	in >> size;
	for (int i = 0; i < size; i++) {
		cout << endl << "Enter values for vector " << i << ": " << endl;
		this->vectors[i].setVector(in);
	}
}