#include "Set.h"
#include "SetIterator.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include <stack>
#include <iostream>
#include "TestFunctionality.h"
using namespace std;




int main() {

	testAll();
	testAllExtended();
	testFunctionality();
	cout << "New functionality succesfully passed the test !" << endl;
	cout << "That's all!" << endl;
	system("pause");

}