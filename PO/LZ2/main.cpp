#include <iostream>
#include <fstream>
#include "VectorNd.h"
#include "VectorOfVectors1.h"
#include "VectorOfVectors2.h"
using namespace std;



ostream& operator<<(ostream& left, VectorNd& right) {
	right.wypisz(left);
	return left;
}

istream& operator>>(istream& left, VectorOfVectors1& right) {
	right.insert(left);
	return left;
}

ostream& operator<<(ostream& left, VectorOfVectors1& right) {
	right.print(left);
	return left;
}

istream& operator>>(istream& left, VectorOfVectors2& right) {
	right.insert(left);
	return left;
}

ostream& operator<<(ostream& left, VectorOfVectors2& right) {
	right.print(left);
	return left;
}




int main() {

	// ZAD 1
	cout << "\n\n VectorOfVectors1 \n \n";
	double values_for_vector_1_1[] = { 11, 2, 8 };
	double values_for_vector_1_2[] = { 13, 43, 12 };
	double values_for_vector_1_3[] = { 7, 5, 112 };
	VectorNd vector1_1(values_for_vector_1_1, 3);
	VectorNd vector1_2(values_for_vector_1_2, 3);
	VectorNd vector1_3(values_for_vector_1_3, 3);
	VectorNd array_1[3] = { vector1_1, vector1_2, vector1_3 };
	VectorOfVectors1 vector_array_1_1(3, array_1);
	VectorOfVectors1 vector_array_1_2(vector_array_1_1);
	
	
	// ZAD 3
	VectorOfVectors1 vector_array_1_3;
	vector_array_1_3  = vector_array_1_1;
	cout << vector_array_1_3;
	// 


	cout << "\n\n VectorOfVectors2 \n \n";
	double values_for_vector_2_1[] = { 11, 2, 8 };
	double values_for_vector_2_2[] = { 13, 43, 12 };
	double values_for_vector_2_3[] = { 7, 5, 112 };
	VectorNd vector2_1(values_for_vector_1_1, 3);
	VectorNd vector2_2(values_for_vector_1_2, 3);
	VectorNd vector2_3(values_for_vector_1_3, 3);
	VectorNd array_2[3] = { vector1_1, vector1_2, vector1_3 };
	VectorOfVectors2 vector_array_2_1(3, array_2);
	VectorOfVectors2 vector_array_2_2(vector_array_2_1);

	// ZAD 3
	VectorOfVectors2 vector_array_2_3;
	vector_array_2_3 = vector_array_2_1;
	cout << vector_array_2_3;
	//

	//


	// ZAD 2
	VectorOfVectors1 vector_array_export_to_file;
	VectorOfVectors1 vector_array_import_to_file;
	cout << vector_array_export_to_file;
	cin >> vector_array_export_to_file;
	cout << vector_array_export_to_file;
	ofstream output1("output1.txt");
	output1 << vector_array_export_to_file;
	output1.close();

	ifstream input1("input1.txt");
	input1 >> vector_array_import_to_file;
	cout << vector_array_import_to_file;
	input1.close();


	VectorOfVectors2 vector_array_export_to_file_2;
	VectorOfVectors2 vector_array_import_to_file_2;
	cout << vector_array_export_to_file_2;
	cin >> vector_array_export_to_file_2;
	cout << vector_array_export_to_file_2;
	ofstream output2("output1.txt");
	output2 << vector_array_export_to_file_2;
	output2.close();

	ifstream input2("input1.txt");
	input2 >> vector_array_import_to_file_2;
	cout << vector_array_import_to_file_2;
	input2.close();
	
	//

	return 0;
};

