#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) : rel{r}, capacity{1}, rootPos{-1}, treeLength{0}, firstEmptyPos{0}
{
	lefts = new int[capacity];
	rights = new int[capacity];
	nodes = new Node * [capacity];
	for (int i = 0; i < capacity - 1; i++)
	{
		nodes[i]->key = NULL_KVALUE; ///nodes that have nullkvalue as key act as nextPos list
		lefts[i] = i + 1; 
		rights[i] = -1;
	}
	lefts[capacity - 1] = -1;
}
//Th(capacity)

void SortedMultiMap::resizeTree()
{
	int* newNextPos = new int[capacity * 2];
	int* newLefts = new int[capacity * 2];
	int* newRights = new int[capacity * 2];
	Node** newNodes = new Node * [capacity * 2];
	for (int i = 0; i < capacity; i++)
	{
		newLefts[i] = lefts[i];
		newRights[i] = rights[i];
		newNodes[i] = nodes[i];
	}
	for (int i = capacity; i < capacity * 2 - 1; i++)
	{
		//newNodes[i]->key = NULL_KVALUE;
		newLefts[i] = i+1;
		newRights[i] = -1;
	}
	newLefts[capacity * 2 - 1] = -1;
	newRights[capacity * 2 - 1] = -1;

	delete[] nodes;
	delete[] lefts;
	delete[] rights;

	nodes = newNodes;
	lefts = newLefts;
	rights = newRights;

	firstEmptyPos = capacity;
	capacity = capacity * 2;
}
//Th(capacity)


void SortedMultiMap::add(TKey c, TValue v) {

	if (treeLength == 0)
	{
		createNode(firstEmptyPos, c, v);
		rootPos = firstEmptyPos;
		firstEmptyPos = lefts[firstEmptyPos];
		lefts[rootPos] = -1;
		rights[rootPos] = -1;

		treeLength++;
		return;
	}

	int currentPos = rootPos;
	int prevPos = -1;
	while (currentPos != -1)
	{
		if (nodes[currentPos]->key == c)
			break;
		else if (rel(nodes[currentPos]->key, c) == true) //current node  is "smaller" go right
		{
			prevPos = currentPos;
			currentPos = rights[currentPos];
		}
		else if (rel(nodes[currentPos]->key, c) == false)///search for an empty pos/existing pos
		{
			prevPos = currentPos;
			currentPos = lefts[currentPos];
		}
	}
	if (currentPos != -1) //if the key already exists
	{
		if (nodes[currentPos]->length == nodes[currentPos]->capacity)
			resizeValues(nodes[currentPos]);
		nodes[currentPos]->values[nodes[currentPos]->length] = v;
		nodes[currentPos]->length++;
		treeLength++;
	}
	if (currentPos == -1) // if the key does not exist we must add it
	{
		if (firstEmptyPos == -1)
			resizeTree();

		currentPos = firstEmptyPos;
		createNode(currentPos, c, v);

		if (rel(nodes[prevPos]->key, c) == true) // previus node is "smaller" than the one we are adding, so add to the right
			rights[prevPos] = currentPos;
		else
			lefts[prevPos] = currentPos;

		firstEmptyPos = lefts[currentPos];
		lefts[currentPos] = -1;
		rights[currentPos] = -1;
		treeLength++;
	}
}
//BC: Th(log2n) if it adds a new value for the root
//AC: Th(log2n)
//WC: Th(n) if it adds a new node, for example add a new node with the smallest value to a degenerated tree on the left


vector<TValue> SortedMultiMap::search(TKey c) const {

	if (treeLength == 0)
		return vector<TValue>();

	int currentPos = rootPos;
	while (currentPos != -1)
	{
		if (nodes[currentPos]->key == c)
			break;
		else if (rel(nodes[currentPos]->key, c) == true)
			currentPos = rights[currentPos];
		else if (rel(nodes[currentPos]->key, c) == false)
			currentPos = lefts[currentPos];
	}
	if (currentPos == -1)
		return vector<TValue>();
	else if (currentPos != -1)
	{
		vector<TValue> values;
		for (int i = 0; i < nodes[currentPos]->length; i++)
		{
			values.push_back(nodes[currentPos]->values[i]);
		}
		return values;
	}
}
//BC : Th(1), to find the first value in the root
//AC : Theta(log2n)
//WC : Th(n), to find the last element for the lowest node
 
bool SortedMultiMap::remove(TKey c, TValue v) {
	if (treeLength == 0)
		return false;
	if (treeLength == 1 && nodes[rootPos]->values[0] == v)
	{
		nodes[rootPos]->length--;
		delete[] nodes[rootPos]->values;
		lefts[rootPos] = firstEmptyPos;
		firstEmptyPos = rootPos;
		rootPos = -1;
		treeLength--;
		return true;
	}
	if (treeLength == 1 && nodes[rootPos]->values[0] != v)
		return false;

	int currentPos = rootPos;
	int prevPos = -1;
	while (currentPos != -1)
	{
		if (nodes[currentPos]->key == c)
			break;
		else if (rel(nodes[currentPos]->key, c) == true)
		{
			prevPos = currentPos;
			currentPos = rights[currentPos];
		}
		else if (rel(nodes[currentPos]->key, c) == false)
		{
			prevPos = currentPos;
			currentPos = lefts[currentPos];
		}
	} //find if the key exists
	if (currentPos == -1)
		return false; //key does not exists
	else //key exists
	{
		if (nodes[currentPos]->length > 1) //if there is more than 1 value
			return findAndRemoveFromValues(currentPos, v);

		else
		{
			if (nodes[currentPos]->values[0] != v) //correct key but incorrect value
				return false;
			else                                   //correct key and correct value
			{
				if ((lefts[currentPos] == -1) && (rights[currentPos] == -1)) //leaf
				{
					removeLeaf(currentPos, prevPos);
					lefts[currentPos] = firstEmptyPos;
					firstEmptyPos = currentPos;
					treeLength--;
					return true;
				}
				if ((lefts[currentPos] == -1) || (rights[currentPos] == -1)) //only 1 side descendants
				{
					removeNodeWithOneDescendant(currentPos, prevPos);
					lefts[currentPos] = firstEmptyPos;
					firstEmptyPos = currentPos;
					rights[currentPos] = -1;
					treeLength--;
					return true;
				}
				if ((lefts[currentPos] != -1) && (rights[currentPos] != -1))
				{
					int nodeToReplace = currentPos;
					while (lefts[currentPos] != -1) //find the smallest node on the right subtree
					{
						prevPos = currentPos;
						currentPos = lefts[currentPos];
					}
					nodes[nodeToReplace]->key = nodes[currentPos]->key;
					nodes[nodeToReplace]->length = nodes[currentPos]->length;
					nodes[nodeToReplace]->capacity = nodes[currentPos]->capacity; 
					delete[] nodes[nodeToReplace]->values;
					nodes[nodeToReplace]->values = new TValue[nodes[currentPos]->capacity]; //replace values
					for (int i = 0; i < nodes[nodeToReplace]->length; i++)
					{
						nodes[nodeToReplace]->values[i] = nodes[currentPos]->values[i];
					}
					//replace all data
					if ((lefts[currentPos] == -1) && (rights[currentPos] == -1)) //leaf
					{
						removeLeaf(currentPos, prevPos);
						lefts[currentPos] = firstEmptyPos;
						firstEmptyPos = currentPos;
						treeLength--;
						return true;
					}
					else
					{
						removeNodeWithOneDescendant(currentPos, prevPos);
						lefts[currentPos] = firstEmptyPos;
						firstEmptyPos = currentPos;
						rights[currentPos] = -1;
						treeLength--;
						return true;
					}

				}
			}
		}
	}
	//key does not exist
	return false;
}
//BC: TH(1), one example would be if the tree lenght is 0
//WC: Th(n), the height of the tree is reached
//AC: Th(log2n)
int SortedMultiMap::size() const {
	return treeLength;
}
//Th(1)

bool SortedMultiMap::isEmpty() const {
	return (treeLength == 0);
}
//Th(1)

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

//Th(1)




SortedMultiMap::~SortedMultiMap()
{
	SMMIterator it = iterator();
	while (it.valid())
	{
		if (it.currentValuePos == it.map.nodes[it.currentPos]->length)
		{
			delete[] it.map.nodes[it.currentPos]->values;
		}
		it.next();
	}
	delete[] nodes;
	delete[] lefts;
	delete[] rights;
}
//approx Th(nrOfValues)

void SortedMultiMap::createNode(int Pos, TKey c, TValue v)
{
	nodes[Pos] = new Node;
	nodes[Pos]->capacity = 4;
	nodes[Pos]->length = 1;

	nodes[Pos]->key = c;
	nodes[Pos]->values = new TValue[nodes[Pos]->capacity];
	nodes[Pos]->values[0] = v;
}

bool SortedMultiMap::findAndRemoveFromValues(int Pos, TValue v)
{
	int currentValPos = 0;
	while (currentValPos < nodes[Pos]->length)
	{
		if (nodes[Pos]->values[currentValPos] == v)
			break;
		currentValPos++;
	}
	if (currentValPos == nodes[Pos]->length) //not found
		return false;
	else
	{
		for (int i = currentValPos; i < nodes[Pos]->length - 1; i++)
			nodes[Pos]->values[i] = nodes[Pos]->values[i + 1];
		nodes[Pos]->length--;
		treeLength--;
		return true;
	}

}

void SortedMultiMap::removeLeaf(int leafPos, int parentPos) //lefts and rights of deleted node do not change
{
	if (lefts[parentPos] == leafPos) //leaf is left child
	{
		delete[] nodes[leafPos]->values;
		lefts[parentPos] = -1;
	}
	else
	{
		delete[] nodes[leafPos]->values;
		rights[parentPos] = -1;
	}
}

void SortedMultiMap::removeNodeWithOneDescendant(int nodePos, int parentPos) //lefts and rights of deleted node do not change
{
	if (parentPos != -1)
	{
		if (lefts[parentPos] = nodePos) //node is left child
		{
			if (rights[nodePos] == -1) //node has only left descendants
			{
				delete[] nodes[nodePos]->values;
				nodes[nodePos]->length = 0;
				lefts[parentPos] = lefts[nodePos];
			}
			else if (lefts[nodePos] == -1) //node has only right descendants
			{
				delete[] nodes[nodePos]->values;
				nodes[nodePos]->length = 0;
				lefts[parentPos] = rights[nodePos];
			}
		}
		else  //node is right child
		{
			if (rights[nodePos] == -1) //node has only left descendants
			{
				delete[] nodes[nodePos]->values;
				nodes[nodePos]->length = 0;
				rights[parentPos] = lefts[nodePos];
			}
			else if (lefts[nodePos] == -1) //node has only right descendants
			{
				delete[] nodes[nodePos]->values;
				nodes[nodePos]->length = 0;
				rights[parentPos] = rights[nodePos];
			}
		}
	}
	else //remove root
	{
		if (lefts[nodePos] == -1) //root has only right descendants
		{
			delete[] nodes[nodePos];
			nodes[nodePos]->length = 0;
			rootPos = rights[nodePos];
		}
		else if (rights[nodePos] == -1) //root has only right descendants
		{
			delete[] nodes[nodePos];
			nodes[nodePos]->length = 0;
			rootPos = lefts[nodePos];
		}
	}
}


void resizeValues(Node* node)
{
	node->capacity = node->capacity * 2;
	TValue* temp = new TValue[node->capacity];
	for (int i = 0; i < node->length; i++)
		temp[i] = node->values[i];
	delete[] node->values;
	node->values = temp;
}


/// BC : Th(1) , the second map is empty
/// WC/AC : [Th(h2) + th(nrOfValuesh2)] * (th(h1) + th(h2))
/// in average case h2= log in base 2of nrOfValues, and simillar in case of h1
/// and worst case h1 = nrOfValues1 , h2=nrOfValues2
int SortedMultiMap::updateValues(SortedMultiMap& sm) {
	int nr = 0;
	int i = 0;
	int ok = 0;
	TKey prev = -1;
	SMMIterator it(sm);
	while (it.valid())
	{
		TElem elem = it.getCurrent();
		vector <TValue> val = search(elem.first);
		if (val.size() != 0)
		{
			if (elem.first != prev ) {
				i = 0;
				if (ok == 1) {
					nr++;
					ok = 0;
				}

			}
			int currentPos = rootPos;
			while (currentPos != -1)
			{
				if (nodes[currentPos]->key > elem.first)
					break;

				if (nodes[currentPos]->key == elem.first)
				{
					if (nodes[currentPos]->values[i] != elem.second) {
						nodes[currentPos]->values[i] = elem.second;
						ok = 1;
						prev = nodes[currentPos]->key;
						
					}

					i++;
					break;
				}
				else if (rel(nodes[currentPos]->key, elem.first) == true)
					currentPos = rights[currentPos];
				else if (rel(nodes[currentPos]->key, elem.first) == false)
					currentPos = lefts[currentPos];
				

			}

			
		}
		it.next();
	}
	if (ok == 1)
		nr++;
	return nr;
}






