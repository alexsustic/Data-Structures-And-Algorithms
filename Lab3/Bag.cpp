#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>

using namespace std;



/// Complexity: Theta(1)
Bag::Bag() {
	DLLANode** nodes = new DLLANode*[10];   ///dynamic allocation
	this->nodes = nodes;      /// the list of nodes
	this->head = -1;         /// the position of the first node , initially set to -1
	this->tail = NULL;       /// the position of the last node , initially set to NULL
	this->dimension = 0;     /// number of the elements from each node
	this->firstEmpty = -1;  /// it retains the position of the last node removed
}





/// n - size of the list
///Overall complexity: O(n)
///Best Case: Theta(1) - when the the list is empty
///Worst Case: Theta(n) - when we have to add an inexistent element
///Average Case: Theta(n)
void Bag::add(TElem elem) {
	DLLANode newNode;
	newNode.info = elem;
	newNode.next = NULL;
	newNode.previous = NULL;
	newNode.frequence = 0;

	if (this->dimension == this->capacity)
		/// if we do not have enough space, we allocate more memory
		resize();

	if (this->dimension == 0)
	{
		/// if the list is empty, we consider the position 0 , the starting position
		this->nodes[0] = newNode;
		this->nodes[0].previous = -1;
		this->nodes[0].next = -1;
		this->nodes[0].frequence += 1;
		this->head = 0;
		this->tail = 0;
		this->dimension += 1;
		
	}
	else {
		/// if the list is not empty
		int existence = -1;
		for (int i = this->head; i!= -1; i= nodes[i].next)
		{
			/// we parse all the elements to find if the element already exists
			if (nodes[i].info == elem)
			{
				nodes[i].frequence += 1;
				existence = 0;
				this->dimension += 1;
			}
			
		}
		if (existence == -1)
		{   /// if it is an unique element we are going to check the following
			

			if (this->firstEmpty != -1)
			{
				/// if there are some empty spaces in the list, we will fill them with the new node
				int previous = nodes[firstEmpty].previous;
				this->dimension += 1;
				nodes[firstEmpty] = newNode;
				nodes[firstEmpty].frequence += 1;
				nodes[firstEmpty].previous = tail;
				nodes[firstEmpty].next = -1;
				this->tail = firstEmpty;
				this->firstEmpty = previous;
				nodes[this->firstEmpty].next = -1;

			}
			else {
				/// if there aren't, we will add the new node created to the end of the list
				this->dimension += 1;
				nodes[this->dimension - 1] = newNode;
				nodes[this->dimension - 1].frequence += 1;
				nodes[this->dimension - 1].previous = tail;
				nodes[this->dimension - 1].next = -1;
				nodes[tail].next = this->dimension - 1;
				this->tail = this->dimension-1;
			}
		}
	}
	
}






/// n - size of the list
///Overall complexity: O(n)
///Best Case: Tetha(1) -when the list is empty or we have to remove the head\tail
///Worst Case: Tetha(n) - when we have to remove the last but one element because we are going to parse almost the whole list
///Average Case: Tetha(n)
bool Bag::remove(TElem elem) {

	
	if (isEmpty())
		/// we check if the list is empty in order to avoid any other useless operations
		return false;

	if (nodes[head].info == elem)
	{
		/// we check if the element we want to remove is the header of the list
		if (nodes[head].frequence == 1)
		{
			/// if the element is unique
			int next = nodes[head].next;
			
			if (this->firstEmpty != -1) {
				/// we check if there are some free spaces and
				/// we will link the node of the element with the rest of the free spaces if so
				nodes[head].previous = firstEmpty;

				nodes[head].next = -1;
				nodes[firstEmpty].next = head;
				this->firstEmpty =head;
				
				
			}
			else
			{
				/// if there aren't any free spaces, we create one (the node of the element)
				this->firstEmpty = head;
				nodes[firstEmpty].previous = -1;
				nodes[firstEmpty].next = -1;
				
			}
			
			if (this->dimension != 1)
			{
				/// if we have more elements than one , we reinitialize the head with the position of the next node 
				this->head = next;
				nodes[this->head].previous = -1;
				this->dimension -= 1;
			}
			else
			{
				/// if there is only one element remained, we reinitialize the head and the free spaces(no more use) with -1
				this->head = -1;
				this->dimension -= 1;
				this->firstEmpty = -1;
			}
			
		}
		else
		{
			/// if the header have a frequency greater than 1, we just decrease it by 1
			nodes[head].frequence -= 1;
			this->dimension -= 1;
			
		}
		
		return true;
	}
	
	else if (nodes[tail].info == elem)
	{
		/// if the element is placed at the end of the list (tail)
		
		if (nodes[tail].frequence == 1)
		{
			/// if we have an unique element
			nodes[nodes[tail].previous].next = -1;
			int copy_tail = nodes[tail].previous;
			if (this->firstEmpty != NULL)
			{
				nodes[tail].previous = firstEmpty;
				nodes[firstEmpty].next = tail;
				nodes[tail].next = -1;
				this->firstEmpty = tail;
			}
			else
			{
				this->firstEmpty = tail;
				nodes[firstEmpty].previous = -1;
				nodes[firstEmpty].next = -1;
			}
			
			tail = copy_tail;
			this->dimension -= 1;
		}
		else
		{
			/// if it is not unique, we just decrease the frequency by 1
			nodes[tail].frequence -= 1;
			this->dimension -= 1;
		}
		return true;
	}
	else {
		/// if the element is somewhere in the list (not at the begining or at the end)
		int copy_head = this->head;
		while (copy_head != -1)
		{
			if (nodes[copy_head].info == elem)
			{
				if (nodes[copy_head].frequence == 1) {
					/// if it is an unique element
					/// we link the neighbours of the removed node between them
					
					nodes[nodes[copy_head].previous].next = nodes[copy_head].next;
					nodes[nodes[copy_head].next].previous = nodes[copy_head].previous;
					if (this->firstEmpty != NULL)
					{
						///     if there are some empty spaces
						//////  we link the removed node to the free spaces
						nodes[copy_head].previous = firstEmpty;
						nodes[firstEmpty].next = copy_head;
						nodes[copy_head].next = -1;
						this->firstEmpty = copy_head;
					}
					else
					{
						/// if there aren't any free spaces we create one
						this->firstEmpty = copy_head;
						nodes[firstEmpty].previous = -1;
						nodes[firstEmpty].next = -1;
					}
					this->dimension -= 1;
				}
				else {
					/// if it is not an unique element we just decrease the frequency
					nodes[copy_head].frequence -= 1;
					this->dimension -= 1;
				}
				return true;
			}
			copy_head = nodes[copy_head].next;
		}
	}
	return false;
}






/// n - size of the list
///Overall complexity: O(n)
///Best Case: Theta(1) - when we have an empty list and the header is set to -1
///Worst Case: Theta(n) - when we have to search an element which is the last in the list
///Average Case: Theta(n)
bool Bag::search(TElem elem) const {
	/// we parse the list of nodes, until we find the element we are looking for
	int copy_head = this->head;
	while (copy_head != -1) {
		if (nodes[copy_head].info == elem)
			return true;
		copy_head = nodes[copy_head].next;
	}
	return false;
}





/// n - size of the list
///Overall complexity: O(n)
///Best Case: Theta(1) - when we have an empty list and the header is set to -1
///Worst Case: Theta(n) - when we have to find the occurrences of an element which is the last in the list
///Average Case: Theta(n)
int Bag::nrOccurrences(TElem elem) const {
	/// we parse all the nodes until we reach the element we want to find
	/// and return its frequency
	int copy_head = this->head;
	while (copy_head != -1) {
		if (nodes[copy_head].info == elem)
			return nodes[copy_head].frequence;
		copy_head = nodes[copy_head].next;
	}
	return 0;
}






///Complexity: Theta(1)
///Best Case = Worst Case = Average Case
int Bag::size() const {
	
	return this->dimension;
}





/// Complexity: Theta(1)
/// Best Case = Worst Case = Average Case
bool Bag::isEmpty() const {
	/// we check if the dimension of the list is 0
	if (this->dimension == 0)
		return 1;
	return 0;
}




/// Complexity: Theta(1)
/// Best Case = Worst Case = Average Case
BagIterator Bag::iterator() const {
	return BagIterator(*this);
}




/// Complexity: Theta(n)
void Bag::resize() {

	/// this function is used for allocating more space if needed
	this->capacity += 50;
	DLLANode* new_nodes = new  DLLANode[this->capacity];
	int copy_head = this->head;
	
	while (copy_head != -1) {
		new_nodes[copy_head] = nodes[copy_head];
		copy_head = nodes[copy_head].next;
	}
	delete[] this->nodes;
	this->nodes = new_nodes;
	
}

/// Overall complexity : O(n)
/// Best Case: Theta(1) - when the is list empty / the head of the array has frequency 1
/// Worst Case: Theta(n) - when there are no elements with frequency 1, so the list is parsed completely
/// Average Case: Theta(n)
TElem Bag::leastFrequent() const{

	int minimum_frequency = 999999;
	int position = -1;
	int copy_head = this->head;

	if (this->dimension == 0)
		/// if the list is empty, returns NULL TElement
		return NULL_TELEM;

	while (copy_head != -1)
	{
		if (nodes[copy_head].frequence == 1)
		{
			/// if we found one element with frequency 1, we return it
			return nodes[copy_head].info;
		}
		else if (nodes[copy_head].frequence < minimum_frequency)
		{
			/// else, for each element with a different frequency
			/// we compare it with the minimum and we retain the position if it's smaller
			minimum_frequency = nodes[copy_head].frequence;
			position = copy_head;
			
		}
		copy_head = nodes[copy_head].next;
	}

	return nodes[position].info;

}


/// Complexity: Theta(1)
Bag::~Bag() {
	///deallocate the list of nodes
	delete[] this->nodes;
}

