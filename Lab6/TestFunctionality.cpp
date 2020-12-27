#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <assert.h>
#include "iostream"

using namespace std;

bool ascending(TKey c1, TKey c2) {
	if (c1 <= c2) {
		return true;
	}
	else {
		return false;
	}
}

void testFunctionality() {
	SortedMultiMap smm1 = SortedMultiMap(ascending);
	SortedMultiMap smm2 = SortedMultiMap(ascending);
	smm1.add(1, 2);
	smm1.add(1, 3);
	smm1.add(2, 7);
	smm1.add(3, 4);
	smm1.add(3, 6);
	smm2.add(1, 5);
	smm2.add(1, 6);
	smm2.add(2, 7);
	smm2.add(3, 2);
	smm2.add(3, 9);
	assert(smm1.updateValues(smm2) == 2);
	vector <TValue> val1 = smm1.search(1);
	vector <TValue> val3 = smm1.search(3);
	assert(val1[0] == 5);
	assert(val1[1] == 6);
	assert(val3[0] == 2);
	assert(val3[1] == 9);

	
}

