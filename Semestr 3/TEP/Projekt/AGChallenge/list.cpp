#include  "list.h"
#include  "atlstr.h"  //CString
#include  <math.h>
#include  <time.h>

#include <windows.h>




//----------implentation of MyNode---------------------

bool   MyNode::insertObject(void *object)
{
	if  (object != NULL) return false;
  

	object  =  object;
	return true;
}



bool   MyNode::deleteObject()
{
   if  (object ==  NULL)  return false;
   delete  object;
   object  =  NULL;
   return true;
}


void  MyNode::init()
{
	nextNode  =  NULL;
	prevNode  =  NULL;
	
	object  =  NULL;
}



void  MyNode::bye(bool  bDelObject)
{
	if  (bDelObject  ==  true)
	{
		if  (object != NULL)
		{
			deleteObject();
		}//if  (object != NULL)

	}//if  (bDelObject  ==  true)
}




//---------implementatio of MyList---------------------

bool  MyList::add()
{
	MyNode  *pc_new_node  =  NULL;


	pc_new_node  =  new  MyNode;

	if  (pc_new_node == NULL)  return false;//failed to allocate memory for a new node
	pc_new_node->init();  //init of the object (because we most probably don't use the constructors)

	//if the allocate operation was succesful we start to change List settings, so
	// the node is really added and remebered at the end of the list
	capacity++; //we increase the actual number of objects
	
	if  (firstNode == NULL ) //we are adding first node to the list
	{
	    firstNode  =  pc_new_node;
		lastNode   =  pc_new_node;
	
		actualNode  =  lastNode;
		position  =  capacity; // posiotion set to the last node
		
		return true;
	}//if  (firstNode == lastNode == NULL) 
	else  //we are not adding the first node
	{
		lastNode->setNext(pc_new_node);
		pc_new_node->bSetPrev(lastNode);  //inserting the pc_new_node at the end of the chain of nodes
		
		lastNode  =  pc_new_node; //we are always adding at the end of the list

		actualNode  =  lastNode;
		position  =  capacity; // posiotion set to the last node
				
		return true;
	}//else of if (firstNode == lastNode == NULL) 
   return true;

}




bool    MyList::add(void  *pvNewObject)
{
	if  (add()  ==   false)  return false;

	if  (actualNode->insertObject(pvNewObject)  ==  false)  
	{
		deleteActual(false);
		return false;
	}//if  (actualNode->insertObject(pvNewObject)  ==  false)  


	return true;
}



bool   MyList::setPos(long  wantedPosition)
{
	long  l_counter;
	
	if  (wantedPosition  >  capacity)  return  false;
	if  (wantedPosition  <= 0 )  return  false;

	l_counter  =  1;
	actualNode  =  firstNode;


	while (l_counter < wantedPosition)
	{
		actualNode  =  actualNode->getNext();
		l_counter++;
	}//while (l_counter < wantedPosition)
                       
	return true;

}




bool  MyList::sendObjAddress(MyList  *target)
{
	long  li;
	
	first();

	for (li = 0; li < capacity; li++)
	{
		if  ( target->add() ==  false )  return false ;
		if  ( target->getNode()->insertObject(  getNode()->getObject() )  ==  false )  return false;

		next();
	}


	return true;
}





//if deleteObject is true the hold object will be deleted, if not only the node will be destroyed!
bool   MyList::deleteActual(bool   deleteObject)
{
	MyNode  *pc_node_to_delete;

	if (capacity == 0)  return false;

	pc_node_to_delete  =  actualNode;

	//first we have to remove the node from the node chain...
	//...by setting next node->prevNode (if the next node exist's)...
	if  (pc_node_to_delete->getNext() != NULL)
		pc_node_to_delete->getNext()->bSetPrev(pc_node_to_delete->getPrev());
	//...and by setting previous node->nextNode (if the previous node exist's)...
	if  (pc_node_to_delete->getPrev() != NULL)
		pc_node_to_delete->getPrev()->setNext(pc_node_to_delete->getNext());

		
	//if pc_node_to_delete is the first node we must set it...
	if  (pc_node_to_delete == firstNode)
		firstNode  =  pc_node_to_delete->getNext();


	//if pc_node_to_delete is the last node we must set it...
	if  (pc_node_to_delete == lastNode)
		lastNode  =  pc_node_to_delete->getPrev();


	//...now we clean up after the node to delete...
	pc_node_to_delete->bye(deleteObject);


	//...and delete him finally!
	delete  pc_node_to_delete;

	//DONT FORGET WE HAVE 1 OBJECT LESS
	capacity--;

	//and  about setting a new actual position (we will always set it to the begining)
	actualNode  =  firstNode;
	if  (actualNode  ==  NULL)
		position  =  0;
	else
		position  =  1;
   
	return true;
}



bool  MyList::first()
{
	if  (firstNode != NULL)  
	{
		actualNode  =  firstNode;
		position  =  1;
		return true;
	}
	else
		return false;

}



bool   MyList::last()
{
	if  (lastNode != NULL)  
	{
		actualNode  =  lastNode;
		position  =  capacity;
		return true;
	}
	else
		return false;
}




bool  MyList::next()
{
	//if the list is empty we cannot move
	if  (firstNode  ==  NULL)
		return  false;

	//if we are at the end of the list we also cannot move
	if  (actualNode  ==  lastNode)
		return false;

	//if we get into here it means we can move
	actualNode  =  actualNode->getNext();
	position++;
	return true;

}



bool   MyList::prev()
{

    //if the list is empty we cannot move
	if  (firstNode  ==  NULL)
		return  false;

	//if we are at the beginning of the list we also cannot move
	if  (actualNode  ==  firstNode)
		return false;

	//if we get into here it means we can move
	actualNode  =  actualNode->getPrev();
	position--;
	return true;


}





MyList::MyList()
{
	firstNode   =  NULL;
	lastNode    =  NULL;
	actualNode  =  NULL;
	
	capacity  =  0;
	position  =  0;

}


MyList::~MyList()
{
	bye(false);
}

void  MyList::bye(bool  deleteObject)
{
	//sets on the beginning and then deletes all the nodes
	if  (first()  ==  true)
		while(deleteActual(deleteObject) == true) ;

}





