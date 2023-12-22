#pragma once


class MyNode
{
public:
	bool insertObject(void *object); //inserts a specified object(actually it's addres) to the node 
	bool deleteObject(); //deallocates the memory of held object(deletes the object)

	void *getObject() { return object; }

	MyNode *getNext() { return nextNode; }
	MyNode *getPrev() { return prevNode; }

	bool setNext(MyNode *next)
	{
		nextNode = next;
		return true;
	}

	bool bSetPrev(MyNode *pcPrev)
	{
		prevNode = pcPrev;
		return true;
	}

	//I don't know if the way you allocate the memory uses constructors and destructors
	//so i created it this way in case you just allocate and free the memory without using constructor and destructor tools
	void init();
	void bye(bool deleteObject);

protected:
	MyNode *nextNode;
	MyNode *prevNode;

	void *object;
};


class MyList
{
public:
	bool add(); //Adds 1 node at the en of the list
	bool add(void *); //Adds 1 object at the end of the list

	bool deleteActual(bool deleteObject); // delete's an actual node and the object it holds

	MyNode *getNode() { return actualNode; } //returns an addres to an actual node
	void *getObject() { return actualNode->getObject(); }
	long getPos() { return position; } //returns a position number of a current node

	long getCapacity() { return capacity; } //returns the current capacity


	bool first(); // moves the actual pointer to the first node
	bool last(); // moves the actual pointer to the last node

	bool next(); // moves the actual pointer to the next node
	bool prev(); // moves the actual pointer to the previous node
	bool setPos(long wantedPosition);
	//moves the actual pointer to the node of a specified numer and returns true if the operation was succesful

	bool sendObjAddress(MyList *target); // this method sends all addresses in the list to the targetted list


	//I don't know if the way you allocate the memory uses constructors and destructors
	//so i created it this way in case you just allocate and free the memory without using constructor and destructor tools
	MyList();
	~MyList();

	void bye(bool deleteObject);

protected:
	MyNode *firstNode;
	MyNode *lastNode;
	MyNode *actualNode;

	long capacity;
	long position;
};
