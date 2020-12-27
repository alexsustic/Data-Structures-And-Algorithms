#include "Set.h"
#include "SetITerator.h"
#include <iostream>

using namespace std;

/// Constructor
/// Complexity: best case = worst case = average case
/// Overall complexity is : Theta(m), where m is the lenght of the list (how many slots have the list)    

Set::Set() {
	this->capacity = 5;
	this->numberKeys = 0;
	Node** nodes = new Node*[5];
	for (int i = 0; i < this->capacity; i++)
		nodes[i] = NULL;   /// we initialize all the elements of the list with NULL at first
	this->hashTable = nodes;
	
}

/// Function used for hashing (DIVIDE METHOD), help avoiding most of the collisions
/// Complexity: best case = worst case = average case
/// Overall complexity: Theta(1)
TElem Set::hash_function(TElem elem) const{
	int poz = elem % this->capacity;
	return poz;
  }


/// Complexity: -best case (when there are no elements) : Theta(1)
///             -worst case (when all the nodes are in a single linked list) : Theta(n), where n is the number of elements
///             -average case : Theta(1 + a), where a = number of elements / number of list slots
/// It has the same complexity as Search function given the fact that we use it here, and in rest, we use linear complexity
bool Set::add(TElem elem) {
	bool negative = false; /// boolean variable used for converting from positive to negative when needed

	
	if (((this->numberKeys+1)/(float)this->capacity) > 0.7)
	{
		///if the load factor is greater than 0.7, we allocate more memory 
		resize();
	}

	if (search(elem))
	{
		///we search for the element, is it exists, we return false
		return false;
	}

	if (elem < 0)
	{
		
		negative = true;
		elem = -elem;
	}

	Node* newNode = new Node;
	if (!negative)
		newNode->key = elem;
	else
		newNode->key = -elem;

	int position = this->hash_function(elem);
	if (this->hashTable[position] == NULL)
	{
		/// is the slot is empty, we add a new node
		newNode->next = NULL;
		this->hashTable[position] = newNode;
		this->numberKeys += 1;
	}
	else {
		/// if the slot is not empty, we add a node to the begining and we chain it with the rest nodes
		newNode->next = this->hashTable[position];
		this->hashTable[position] = newNode;
		this->numberKeys += 1;
	}

	return true;
}

/// Complexity : -best case (when there are no elements in the list OR the element is the first in the linked list) : Theta(1)
///              -worst case (when all the elements are in a single linked list, and the element is the last one): Theta(n)
///              -average case : Theta(1 + a), where a = number of elements / number of list slots
bool Set::remove(TElem elem) {
	bool negative = false;

	if (this->numberKeys == 0)
		/// if there are no elements, we return false
		return false;

	if (elem < 0)
	{
		negative = true;
		elem = -elem;
	}

	int position = this->hash_function(elem);
	if (negative)
		elem = -elem;
	if (this->hashTable[position] != NULL)
	{
		/// if the slot is not empty
	      if (this->hashTable[position]->key == elem)
			{
			  /// if the first node from the slot contains the element
				this->hashTable[position] = this->hashTable[position]->next;
				this->numberKeys -= 1;
				return true;
			}
		  else
			{
				Node* node = this->hashTable[position];
				while (node->next != NULL)
				{
					if (node->next->key == elem)
					{
					
						if (node->next->next != NULL)
						{
							///if the element is not at the begining or at the end of the slot
							node->next = node->next->next;
						}
						else
						{
							/// if the element is at the end of the slot
							node->next = NULL;
						}
						this->numberKeys -= 1;
						return true;
					}
					node = node->next;

				}
			}
	}
	return false;
}


///Complexity : -best case (when there are no elements) : Theta(1)
///             -worst case (when all the nodes are in a single linked list) : Theta(n), where n is the number of elements
///             -average case : Theta(1 + a), where a = number of elements / number of list slots
bool Set::search(TElem elem) const {

	bool negative = false;
	if (this->numberKeys == 0)
		/// if there are no elements, we return false
		return false;
	if (elem < 0)
	{
		negative = true;
		elem = -elem;
	}
	int position = this->hash_function(elem);

	if (negative)
		elem = -elem;
	if (this->hashTable[position] != NULL)
	{
		/// is the slot is not empty, we parse all the nodes from it until we find the one containing the element
		Node* node = this->hashTable[position];
		while (node != NULL)
		{
			if (node->key == elem)
				return true;
			node = node->next;
		}
	}
	return false;
}


///Complexity: - best case = worst case = average case
///Overall complexity is : Theta(n*m), where n- the number of existing elements
///                                  , where m- the number of the list slots 
void Set::resize() {
	///we create a copy of the old hash table
	Node** copy = new Node* [this->capacity];
	copy = this->hashTable;  
	this->capacity = this->capacity * 2;
	this->numberKeys = 0;

	///we create a new hash table, allocating more memory
	Node** nodes = new Node*[this->capacity];
	for (int i = 0; i < this->capacity; i++)
		nodes[i] = NULL;
	this->hashTable = nodes;

	/// we add all the elements from the old hash table to the new one
	for (int i=0; i<this->capacity/2;i++)
		if (copy[i] != NULL)
		{
			Node* node = copy[i];
			while (node != NULL)
			{
				add(node->key);
				node = node->next;
			}
		}

	///we deallocate the copy
	for (int i = 0; i < this->capacity/2; i++)
		delete[] copy[i];
	delete[] copy;
}

///Complexity: - best case = worst case = average case
///Overall Complexity: Theta(1)
int Set::size() const {
	
	return this->numberKeys;
}

///Complexity: - best case = worst case = average case
///Overall Complexity: Theta(1)
bool Set::isEmpty() const {
	if (this->numberKeys == 0)
		return true;
	return false;
}

///Complexity: - best case = worst case = average case
///Overall Complexity: Theta(m) - where m is the number of the list slots 
Set::~Set() {
	for (int i = 0; i < this->capacity; i++)
		delete[] this->hashTable[i];
	delete[] this->hashTable;
}

///Complexity: - best case = worst case = average case
///Overall Complexity: Theta(1)
SetIterator Set::iterator() const {
	return SetIterator(*this);
}



///Complexity: - best case (s is an empty set) : Theta(1)
///            - worst case (both sets have only a single linked list on the last slot): 
///                    Theta(m) + Theta(n1)*(Theta(n2) + Theta(m)) = Theta ([n2 +m]*n1 + m )
///                               , where m is the number of slots from the parameter set
///                               , where n2 is the number of elements from parameter set
///                               , where n1 is the number of the elements of the set from which we remove keys
///            - average case : Theta(m) + Theta(n1)*( Theta(1+a) + Theta(m)) = Theta([1+m+a]*n1+m)
///                               , where a = number of elements / number of list slots from the first set
int Set::difference(const Set& s) {

	int nr_of_removed_elements = 0;
	SetIterator it = s.iterator(); /// Theta(m)
	while (it.valid())
	{
		TElem e = it.getCurrent();
		if (search(e))
		{
			this->remove(e);   ///Theta(n)
			nr_of_removed_elements += 1;
		}
		it.next();  /// Theta(m)

	}
    return nr_of_removed_elements;
}

