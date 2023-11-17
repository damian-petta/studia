#include "VectorOfVectors2.h"

VectorOfVectors2::VectorOfVectors2() {
	this->size = 0;
	this->vectors = nullptr;
	std::cout << "I am " << this << " object of VectorOfVectors2 class and I've been initialized by an empty constructor \n";
}


VectorOfVectors2::VectorOfVectors2(int size, const VectorNd vectors[]) {
	std::cout << "I am " << this << " object of VectorOfVectors2 class and I've been initialized by a normal constructor \n";
	this->size = size;
	this->vectors = new VectorNd[size];
	for (int i = 0; i < size; i++)
		this->vectors[i] = vectors[i];
}

VectorOfVectors2::~VectorOfVectors2() {
	std::cout << "I am " << this << " object of VectorOfVectors2 class and I'm going to be destroyed \n";
	delete[] vectors;
}

VectorOfVectors2::VectorOfVectors2(const VectorOfVectors2& orginal)
{
	std::cout << "I am " << this << " object of VectorOfVectors2 class and I've been copied by a copy constructor \n";
	vectors = new VectorNd[orginal.size];
	for (int i = 0; i < orginal.size; i++)
		this->vectors[i] = orginal.vectors[i];
	this->size = orginal.size;
}

VectorOfVectors2& VectorOfVectors2::operator=(const VectorOfVectors2& right)
{
	std::cout << "We're going to copy-swap thingies to other object \n";
	VectorOfVectors2 tmp(right);
	std::swap(this->size, tmp.size);
	std::swap(this->vectors, tmp.vectors);
	std::cout << "Done \n";
	return *this;
}


void VectorOfVectors2::print(ostream& out = cout) {
	out << "This is a vector array " << this << "\n";
	out << "Size: " << size << "\n";
	out << "Content: " << "\n";
	for (int i = 0; i < size; i++) {
		out << "Vector nr." << i << ": \n";
		for (int j = 0; j < vectors[i]._wymiar; j++)
			out << "[" << j << "] = \t" << vectors[i]._liczby[j] << endl;
		cout << "\n";
	}

}

void VectorOfVectors2::insert(istream& in = cin) {
	cout << "Enter size: ";
	in >> size;
	this->vectors = new VectorNd[size];
	for (int i = 0; i < size; i++) {
		cout << endl << "Enter values for vector " << i << ": " << endl;
		this->vectors[i].setVector(in);
	}
}