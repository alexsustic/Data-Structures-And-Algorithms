#include "SortedSetIterator.h"
#include <exception>

using namespace std;



///Complexity: Theta(1)
SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)
{
	this->currentNode = m.head;
}


///Complexity: Theta(1)
void SortedSetIterator::first() {
	
	currentNode = multime.head;
}


///Complexity: Theta(1)
void SortedSetIterator::next() {
	if (currentNode == NULL)
		throw exception("Invalid current node!");
	this->currentNode = currentNode->next;
}



///Complexity: Theta(1)
TElem SortedSetIterator::getCurrent()
{
	if (currentNode == NULL)
		throw exception("Invalid current node!");
	TElem e = currentNode->info;
	return e;

	return NULL_TELEM;
}



///Complexity: Theta(1)
bool SortedSetIterator::valid() const {
	if (currentNode != NULL)
		return true;
	return false;
}