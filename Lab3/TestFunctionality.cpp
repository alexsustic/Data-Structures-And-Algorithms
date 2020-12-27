#include "TestFunctionality.h"
#include <assert.h>
#include "Bag.h"


void testNewFunctionality() {
	Bag b;
	b.add(5);
	b.add(5);
	b.add(5);
	b.add(1);
	b.add(2);  // TElem "2" has the least frequency (which is 1)
	b.add(3);
	b.add(1);
	b.add(3);
	b.add(3);
	
	assert(b.leastFrequent() == 2);

}