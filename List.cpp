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
#include <iostream>
#include <cstring>
#include "Patient.h"
#include "List.h"

using namespace std;

// Default constructor
List::List(){
	int index;

	for( index=0; index<10; index++ ){
		elementPtr[index] = new Patient[INIT_CAPACITY];	
		elementCount[index] = 0;
		capacity[index] = INIT_CAPACITY;
	}
}

// Deconstructor
List::~List(){
	/*
	for(int index; index < 10; index++)
	{
		delete [] elementPtr[index];
	}
	*/
}

// Description: Doubles the array size.
//				firstDigit is the first number in the careCard
// Postcondition: Array size is doubled.
void List::resize(int firstDigit)
{
	capacity[firstDigit] = capacity[firstDigit] * 2;
	cout << "Capacity " << capacity[firstDigit] << endl;
	Patient * temp = new Patient[capacity[firstDigit]];

	int index;

	for( index = 0; index < elementCount[firstDigit]; index++ ){
		cout << "before resize: " << elementPtr[firstDigit][index].getCareCard() << endl;
	}

	copy(elementPtr[firstDigit], elementPtr[firstDigit] + capacity[firstDigit]/2, temp);

	delete [] elementPtr[firstDigit];

	for( index = 0; index < elementCount[firstDigit]; index++ ){
		cout << "after resize: " << temp[index].getCareCard() << endl;
	}

	elementPtr[firstDigit] = temp;

}

// Description: Gets the first digit of the Patients' care card number and returns it
int List::firstCareCardNum(const Patient& target)
{
	int digit = (target.getCareCard())[0];
	return(digit - 48);
}

// Description: Returns the total element count currently stored in List.
int List::getElementCount() const
{
	int index;
	int total;

	for( index=0; index<10; index++ ){
		total += elementCount[index];
	}

	return (total);
}

// Description: Insert an element.
//              When "this" List is full, its data structure is expanded to accommodate 
//              a new element. This is done unbeknown to the client code.
//              If the insertion is successful, true is returned otherwise, false is returned.
// Precondition: newElement must not already be in data collection.  
// Postcondition: newElement inserted and the appropriate elementCount has been incremented.	
bool List::insert(const Patient& newElement)
{
	Patient temp;
	
	int firstDigit = firstCareCardNum(newElement);
	int index = elementCount[firstDigit];

	//Check to see if the array is full and needs to be increased
	if(elementCount[firstDigit] == capacity[firstDigit]){
		resize(firstDigit);
	}

	(elementPtr[firstDigit])[index] = newElement;
	elementCount[firstDigit]++;

	// Keeps the array sorted
	while( index > 0 && elementPtr[firstDigit][index-1].operator>(elementPtr[firstDigit][index]) ){
    		temp = (elementPtr[firstDigit])[index];
    		(elementPtr[firstDigit])[index] = (elementPtr[firstDigit])[index-1];
    		(elementPtr[firstDigit])[index-1] = temp;

    		index--;
    }

	return true;
}

// Description: Remove an element. 
//              If the removal is successful, true is returned otherwise, false is returned.
// Postcondition: toBeRemoved is removed, the appropriate elementCount has been decremented.	
bool List::remove( const Patient& toBeRemoved ){
	return true;
}
	
// Description: Remove all elements.
void List::removeAll()
{
	int index;

	for( index = 0; index < 10; index++ ){		
		elementCount[index] = 0;
	}
}
   
// Description: Search for target element and returns a pointer to it if found,
//              otherwise, returns NULL.
Patient* List::search(const Patient& target)
{
	//cout << "1 ";
	Patient *temp;													//Temp is used to hold on to the array so we can search through it
	//cout << "2 ";
	int firstDigit = firstCareCardNum(target);						//Getting the first digit and storing it
	//cout << "3 ";
	temp = elementPtr[firstDigit];									//Temp will hold onto the array of element ptr
	//cout << "4 ";
	Patient compare;												//Used to compare object in array with our target
	//cout << "5 ";
	for(int index = 0; index < elementCount[firstDigit]; index++)	//We cycle through the entire array based on element count
	{
		compare = temp[index];										//Update compare with the next object
		if(compare.operator==(target)) 								//If we find a match 
		{
			return(&temp[index]);									//We return object that we found
		}
	}
	//cout << "6 ";
	return(NULL);													//Target Not Found
}
   
// Description: Prints all n elements stored in List in sort order and does so in O(n).
void List::printList()
{
	int index;
	int index2;

	for( index=0; index<10; index++ ){
		for( index2 = 0; index2 < elementCount[index]; index2++ ){
			(elementPtr[index] + index2)->printPatient();
		}
	}
}

// End of List.cpp