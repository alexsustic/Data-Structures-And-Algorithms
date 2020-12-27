#include "Bag.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
#include "TestFunctionality.h"
#include <iostream>

using namespace std;

int main() {

	testAll();
	cout << "Short tests over" << endl;

	testAllExtended();
	cout << "All test over" << endl; 

	testNewFunctionality();
	cout << "New functionality test passed succesfully ! \n";

}