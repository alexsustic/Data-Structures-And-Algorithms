#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"
#include "TestFunctionality.h"

int main(){
    testAll();
	testAllExtended();
	
    std::cout<<"Finished SMM Tests!"<<std::endl;
	
	testFunctionality();
	std::cout << "Functionality test passed succesfully!" << std::endl;
	system("pause");
}
