/*
 * List.cpp
 * 
 * Class Description: A value-oriented List data collection ADT.
 * Class Invariant: Data collection with the following characteristics:
 *                   - Each element is unique (no duplicates).
 *                   - It is sorted by ascending sort order of its elements.
 *                   - Its data structure is expandable: when full, it expands to accommodate 
 *                     new insertion. This is done unbeknown to the client code.
 *
 * Last modified on: June, 2017
 * Author: Vicky Lau, Jacky Tse
 */

#include <string>
#include "Patient.h"
#include "List.h"

using namespace std;

// Default constructor
List::List(){
	int index;

	for( index=0; index<10; index++ ){		
		elementCount[index] = 0;
		capacity[index] = MIN_CAPACITY;
	}
	zero  = new Patient[MIN_CAPACITY];
	one   = new Patient[MIN_CAPACITY];
	two   = new Patient[MIN_CAPACITY];
	three = new Patient[MIN_CAPACITY];
	four  = new Patient[MIN_CAPACITY];
	five  = new Patient[MIN_CAPACITY];
	six   = new Patient[MIN_CAPACITY];
	seven = new Patient[MIN_CAPACITY];
	eight = new Patient[MIN_CAPACITY];
	nine  = new Patient[MIN_CAPACITY];

	elementPtr[0] = zero;
	elementPtr[1] = one;
	elementPtr[2] = two;
	elementPtr[3] = three;
	elementPtr[4] = four;
	elementPtr[5] = five;
	elementPtr[6] = six;
	elementPtr[7] = seven;
	elementPtr[8] = eight;
	elementPtr[9] = nine;
}

// Description: Returns the total element count currently stored in List.
int List::getElementCount() const{
	int index;
	int total;

	for( index=0; index<10; index++ ){
		total += elementCount[index];
	}
	return total;
}

// Description: Insert an element.
//              When "this" List is full, its data structure is expanded to accommodate 
//              a new element. This is done unbeknown to the client code.
//              If the insertion is successful, true is returned otherwise, false is returned.
// Precondition: newElement must not already be in data collection.  
// Postcondition: newElement inserted and the appropriate elementCount has been incremented.	
bool List::insert(const Patient& newElement){
	return true;
}

// Description: Remove an element. 
//              If the removal is successful, true is returned otherwise, false is returned.
// Postcondition: toBeRemoved is removed, the appropriate elementCount has been decremented.	
bool List::remove( const Patient& toBeRemoved ){
	return true;
}
	
// Description: Remove all elements.
void List::removeAll(){

}
   
// Description: Search for target element and returns a pointer to it if found,
//              otherwise, returns NULL.
Patient* List::search(const Patient& target){
	Patient *temp;													//Temp is used to hold on to the array so we can search through it
	int firstDigit = (target.getCareCard())[0];						//We Pull the first value out

	temp = elementPtr[firstDigit];									//Temp will hold onto the array of element ptr

	Patient compare;												//Used to compare object in array with out target

	for(int index = 0; index < elementCount[firstDigit]; index++)	//We cycle through the entire array based on element count
	{
		compare = temp[index];										//Update compare with the next object
		if(compare.operator==(target)) 								//If we find a match 
		{
			return(&temp[index]);									//We return object that we found
		}
	}
	return(NULL);													//Target Not Found
}
   
// Description: Prints all n elements stored in List in sort order and does so in O(n).
void List::printList(){

}

// End of List.cpp
