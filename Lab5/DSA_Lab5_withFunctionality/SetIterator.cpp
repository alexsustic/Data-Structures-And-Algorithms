#include "SetIterator.h"
#include "Set.h"
#include <exception>

///Complexity - best case(when there are elements on slot 0): Theta(1)
///           - worst case(when there is an only single linked list in the last slot) : Theta(m)
///           - average : Theta(m) 
///Overall Complexity : O(m) - where m is the number of list slots
SetIterator::SetIterator(const Set& m) : set(m)
{
	this->hashTable = m.hashTable;
	this->currentPosition = 0;
	while (currentPosition < m.capacity && m.hashTable[this->currentPosition] == nullptr)
		this->currentPosition += 1;
	this->startingPosition = this->currentPosition;
	if (this->currentPosition < m.capacity)
		this->currentNode = m.hashTable[this->currentPosition];
	else
		this->currentNode = nullptr;
}


/// Complexity: - best case = worst case = average case
/// Overall Complexity: Theta(1)
void SetIterator::first() {
	this->currentPosition = this->startingPosition;
	if (currentPosition < set.capacity)
		this->currentNode = this->hashTable[currentPosition];
	else
		this->currentNode = nullptr;
}

/// Complexity: - best case (when the current position is at the end of the list) : Theta(1)
///             - worst case(when there is an only single linked list in the last slot) : Theta(m)
///             - average : Theta(m), where m is the number of list slots
///Overall Complexity : O(m) - where m is the number of list slots
void SetIterator::next() {
	if (this->currentPosition < set.capacity) {
		if (this->currentNode != nullptr)
		{
			if (this->currentNode->next != nullptr)
				this->currentNode = this->currentNode->next;
			else
			{
				this->currentPosition += 1;
				this->currentNode = this->hashTable[currentPosition];
				while (currentPosition < set.capacity && this->currentNode == nullptr)
				{
					this->currentPosition += 1;
					this->currentNode = this->hashTable[currentPosition];
				}
			}
		}
		else
		{
			while (currentPosition < set.capacity && this->currentNode == nullptr)
			{
				this->currentPosition += 1;
				this->currentNode = this->hashTable[currentPosition];
			}
		}
	}
	else
		throw std::exception("No more elements to iterate!");
}


/// Complexity: - best case = worst case = average case
/// Overall Complexity: Theta(1)
TElem SetIterator::getCurrent()
{
	if (this->currentPosition == set.capacity)
		throw std::exception("There are no more elements");
	if (this->currentPosition < set.capacity && this->currentNode!=nullptr)
		return this->currentNode->key;
	return NULL_TELEM;
}


/// Complexity: - best case = worst case = average case
/// Overall Complexity: Theta(1)
bool SetIterator::valid() const {
	if (this->currentPosition < set.capacity)
		return true;
	return false;
}


