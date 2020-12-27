#pragma once
//DO NOT INCLUDE SETITERATOR

//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111
#define NIL null_ptr
typedef int TElem;
class SetIterator;

typedef struct Node {
    TElem key;
    Node* next;
};

class Set {
    //DO NOT CHANGE THIS PART
    friend class SetIterator;

private:
    Node** hashTable;
    int capacity;
    int numberKeys;

public:
    
    //implicit constructor
    Set();

    //adds an element to the set
    //returns true if the element was added, false otherwise (if the element was already in the set and it was not added)
    bool add(TElem e);

    //removes an element from the set
    //returns true if e was removed, false otherwise
    bool remove(TElem e);

    //checks whether an element belongs to the set or not
    bool search(TElem elem) const;

    //returns the number of elements;
    int size() const;

    //check whether the set is empty or not;
    bool isEmpty() const;

    //return an iterator for the set
    SetIterator iterator() const;

    // destructor
    ~Set();

  //  TElem hash_function(TElem elem);
    TElem hash_function(TElem elem) const;
    void resize();
    int difference(const Set& s);


};





