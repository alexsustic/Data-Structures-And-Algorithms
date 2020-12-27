#include "TestFunctionality.h"
#include <assert.h>
void testFunctionality() {
	Set p1;
	Set p2;

	p1.add(1);
	p1.add(2); // must be removed
	p1.add(4);
	p1.add(5); // must be removed
	p1.add(8); // must be removed

	p2.add(2);
	p2.add(5);
	p2.add(8);

	/// so, 3 elements must be removed
	assert(p1.difference(p2) == 3);

}