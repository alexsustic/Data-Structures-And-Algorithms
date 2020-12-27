#pragma once
#include "Set.h"

class SetIterator
{
	//DO NOT CHANGE THIS PART
	friend class Set;
private:

	//DO NOT CHANGE THIS PART
	const Set& set;
	SetIterator(const Set& s);
	Node** hashTable;
	int currentPosition;
	Node* currentNode;    
	int startingPosition;  /// the position of the slot containing the first non-null node in the list

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
};