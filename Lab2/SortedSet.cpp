#include "SortedSet.h"
#include "SortedSetIterator.h"


/// Complexity: Theta(1)
SortedSet::SortedSet(Relation r) {
	this->relation = r;
	this->head = nullptr;
	this->setSize = 0;

}



/// Complexity: O(setSize-1)
bool SortedSet::add(TComp elem) {

	///create the node we want to add
	SLLNode* newNode = new SLLNode;
	newNode->info = elem;
	newNode->next = nullptr;
	

	if (this->head == nullptr)
	{
		///if the set is empty

		this->head = newNode;
		this->setSize++;
		return true;
	}

	else {

		///if the set is not empty

		if (this->head->info == elem)
		  /// we check if the element alredy exists in the head node
			return false;

		if (this->relation(elem, this->head->info) == true) {
			/// if the element is less then the info from the head node

			newNode->next = this->head;
			this->head = newNode;
			this->setSize++;
			return true;
		}
		else {

			/// if the element is greater than the info from the head node
			SLLNode* currentNode;
			currentNode = this->head;
			while (currentNode->next != nullptr && this->relation(currentNode->next->info, elem) == true)
			{
				/// we parse each node until we find the node that respects the condition from above
				if (currentNode->info == elem)
					///we check if the element already exists in some node, while parsing process
					return false;
				currentNode = currentNode->next;
			}
			if (currentNode->info == elem)
				/// we check if the element alredy exists in the last node remained
				return false;
			newNode->next = currentNode->next;
			currentNode->next = newNode;
			this->setSize++;
			return true;

		}

	}
	return false;
}




///Complexity: O(setSize)
bool SortedSet::remove(TComp elem) {
	if (search(elem) == true)
	{
		/// if the element exists in the set

		if (this->head->info == elem)
		{
			/// if we want to remove the element from head node
			SLLNode* nextNodeAfterHead;
			nextNodeAfterHead = this->head->next;
			delete this->head;
			this->head = nextNodeAfterHead;
			this->setSize--;
			return true;
		}
		else {
			/// if we want to remove the element from a different node than the head
			SLLNode* currentNode;
			SLLNode* previousNode=new SLLNode; ///we use this in orded to reconnect nodes after deleting one
			currentNode = this->head;

			while (currentNode != nullptr)
			{
				///we parse all the nodes in order to find that one containing elem and delete it
				if (currentNode->info == elem)
				{
					previousNode->next = currentNode->next;
					delete currentNode;
					this->setSize--;
					return true;
				}
				previousNode = currentNode;
				currentNode = currentNode->next;
			}
		}
	}
	return false;
}



///Complexity: O(setSize)
bool SortedSet::search(TComp elem) const {
	if (this->setSize == 0)
		///if the set is empty then we do not have elements to search
		return false;

	SLLNode* currentNode;
	currentNode = this->head;
	while (currentNode != nullptr)
	{
		///we parse all the nodes in order to find that one containg elem
		if (currentNode->info == elem)
			return true;
		currentNode = currentNode->next;
	}
	return false;
}




///Complexity: Theta(1)
int SortedSet::size() const {
	return this->setSize;
}



///Complexity: Theta(1)
bool SortedSet::isEmpty() const {
	if (this->setSize==0)
		return true;
	return false;
}




///Complexity: Theta(1)
SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}



///Complexity: O(setSize)
SortedSet::~SortedSet() {
	SLLNode* currentNode;
	while (this->head != nullptr)
	{  ///we deallocate all the nodes
		currentNode = this->head;
		this->head = this->head->next;
		delete currentNode;
	}
}

