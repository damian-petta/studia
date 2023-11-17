#pragma once
#include "liczba.h"

class OverrideVSOverload : public Wartosc_Liczbowa
{
public:
	OverrideVSOverload() {
		OverloadedExample(5);
		OverloadedExample(5,7);
		ExampleOverride();
	}

	void OverloadedExample(int x) {
		std::cout << "OverloadedExample with one int param \n";
	}
	void OverloadedExample(int x, int y) {
		std::cout << "OverloadedExample with two int params \n To overload a method you need to create another method with the same name but with diffrent params \n ";
	}

	void ExampleOverride() override
	{
		std::cout << "This is a overrided ExampleOverride() method from OverrideVSOverload class \n To override a method you need to create a method in derived class with the same name like in base class \n";
	}


	double modul() override {
		
		return 0;  
	}

	void wypisz(std::ostream& out) override {

	}

};