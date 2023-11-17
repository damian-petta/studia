#pragma once
#include <iostream>
#include "VectorNd.h"
#define SIZE_MAXX 1000


class VectorOfVectors1 {
	VectorNd vectors[SIZE_MAXX];
	int size;
public:
	VectorOfVectors1();
	VectorOfVectors1(int size);
	VectorOfVectors1(int size, const VectorNd vectors[]);
	VectorOfVectors1(const VectorOfVectors1&);
	~VectorOfVectors1();
	VectorOfVectors1& operator= (VectorOfVectors1&);
private:
	friend ostream& operator<<(ostream& left, VectorOfVectors1& right);
	friend istream& operator>>(istream& left, VectorOfVectors1& right);
	void print(ostream& out);
	void insert(istream& in);
};