#include "complex.h"
#include "OverrideVSOverload.h"
#include "liczba.h"
#include <iostream>

int main() {


    // ZAD 1
    // Create Complex object usign pointer
    std::cout << "Complex number\n";
    Complex* complexPtr = new Complex(3.0, 4.0);
    complexPtr->wypisz(std::cout);

    Complex* anotherComplexPtr = new Complex(1.0, 2.0);

    // Use the overloaded + operator to add complexPtr and anotherComplexPtr
    Complex resultPtr = *complexPtr + *anotherComplexPtr;
    resultPtr.wypisz(std::cout);

    delete complexPtr;
    delete anotherComplexPtr;

    // Create a Complex object as a local variable
    Complex complexLocal(5.0, 6.0);
    complexLocal.wypisz(std::cout);

    // Create another Complex object as a local variable
    Complex anotherComplexLocal(2.0, 3.0);

    // Use the overloaded + operator to add complexLocal and anotherComplexLocal
    Complex resultLocal = complexLocal + anotherComplexLocal;
    resultLocal.wypisz(std::cout);
    std::cout << "----------------------------------\n";
    std::cout << "Real number\n";

    Liczba* realPtr = new Liczba(-12);
    realPtr->wypisz(std::cout);
    std::cout<<"Modulo z liczby rzeczywistej" << realPtr->modul()<<"\n";
    delete realPtr;

    Liczba realLocal(14);


    // ZAD 2
    const int arraySize = 2;
    Wartosc_Liczbowa* customNumbersArray[arraySize];
    customNumbersArray[0] = new Liczba(5.0);       
    customNumbersArray[1] = new Complex(6.0, 4.0);    


    for (int i = 0; i < arraySize; i++) {
        std::cout << "Modul obiektu " << i << ": " << customNumbersArray[i]->modul() << std::endl;
    }
    for (int i = 0; i < arraySize; i++) {
        delete customNumbersArray[i];
    }


    // ZAD 3
    OverrideVSOverload x;

    return 0;
}
