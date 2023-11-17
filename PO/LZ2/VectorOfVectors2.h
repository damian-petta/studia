#pragma once
#include <iostream>
#include "VectorNd.h"


class VectorOfVectors2 {
	VectorNd *vectors;
	int size;
public:
	VectorOfVectors2();
	VectorOfVectors2(int size);
	VectorOfVectors2(int size, const VectorNd vectors[]);
	VectorOfVectors2(const VectorOfVectors2& oryginal);
	~VectorOfVectors2();

	VectorOfVectors2& operator= (const VectorOfVectors2&);
	
private:
	friend ostream& operator<<(ostream& left, VectorOfVectors2& right);
	friend istream& operator>>(istream& left, VectorOfVectors2& right);
	void print(ostream& out);
	void insert(istream& in);
};