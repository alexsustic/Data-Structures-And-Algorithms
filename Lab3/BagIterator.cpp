#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;

///Complexity: Theta(1)
BagIterator::BagIterator(const Bag& c) : bag(c)
{
	this->bag_nodes = c.nodes;   /// the list of nodes
	this->currentElement = c.head;    /// the head of the list (not necessary 0)
	this->frequency = 0;          /// frequency used for iterating the nodes(used for next function)
}

///Complexity: Theta(1)
void BagIterator::first() {
	/// we reinitialize the currentElement with the header of the list of nodes
	this->currentElement = bag.head;
}



///Complexity: Theta(1)
void BagIterator::next() {

	/// if the current element(head) is -1,it means that the list is empty or we reached
	/// the end of the list
	if (this->currentElement == -1)
		throw exception("Invalid current node!");

	/// we don't get to the next node, until we don't parse all the elements from a node
	/// using frequency
	if (frequency == bag_nodes[currentElement].frequence - 1)
	{
		this->currentElement = this->bag_nodes[currentElement].next;
		this->frequency = 0;
	}
	else
		this->frequency += 1;
}



///Complexity: Theta(1)
bool BagIterator::valid() const {
	/// if the current element(head) is -1,it means that the list is empty
	/// so the bag iterator is not valid
	if (this->currentElement != -1)
		return true;
	return false;
}



///Complexity: Theta(1)
TElem BagIterator::getCurrent() const
{
	/// if the current element(head) is -1,it means that the list is empty
	/// it means that we have no element to return (exception)
	if (this->currentElement != -1)
		return this->bag_nodes[currentElement].info;
	else
		throw exception("Invalid current element!");
	return NULL_TELEM
}
