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
		elementCount[index] = 0;
		capacity[index] = INIT_CAPACITY;
	}

	zero  = new Patient[INIT_CAPACITY];
	one   = new Patient[INIT_CAPACITY];
	two   = new Patient[INIT_CAPACITY];
	three = new Patient[INIT_CAPACITY];
	four  = new Patient[INIT_CAPACITY];
	five  = new Patient[INIT_CAPACITY];
	six   = new Patient[INIT_CAPACITY];
	seven = new Patient[INIT_CAPACITY];
	eight = new Patient[INIT_CAPACITY];
	nine  = new Patient[INIT_CAPACITY];

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

// Deconstructor
List::~List(){
	/**
	for(int i; i < 10; i++)
	{
		delete[] elementPtr[i];
	}**/
}

// Description: Doubles the array size.
//				firstDigit is the first number in the careCard
// Postcondition: Array size is doubled.
void List::resize(int firstDigit)
{
	capacity[firstDigit] = capacity[firstDigit] * 2;
	cout << "Capacity " << capacity[firstDigit] << endl;
	Patient * temp = new Patient[capacity[firstDigit]];

	memcpy(temp, elementPtr[firstDigit], elementCount[firstDigit] * sizeof(Patient));
	delete [] elementPtr[firstDigit];
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
	Patient *temp;													//Temp is used to hold on to the array so we can search through it
	Patient compare;												//Used to compare object in array with our target
	bool wasInserted = false;
	int firstDigit = firstCareCardNum(newElement);
	cout <<"first digit is... " << firstDigit << endl;

	temp = elementPtr[firstDigit];

	//Check to see if the array is full
	if(elementCount[firstDigit] == capacity[firstDigit])
	{
		cout<< "it is full" << endl;
		resize(firstDigit);
	}
	cout << "E count " << elementCount[firstDigit] << "capacity: "<< capacity[firstDigit] << endl;
	if(elementCount == 0)		//Only for an empty list
    {
    	elementPtr[firstDigit][0] = newElement;		//We stick the emelent at the begining
    	elementCount[firstDigit]++;
    	//cout << "added one " << getElementCount() << endl;
    }
    else
    {
    	for(int index = elementCount[firstDigit] - 1; index >= 0; index--)	//We cycle through the list to find where the elemet should be
    	{
    		//cout << "In loop " << i << endl;
    		compare = temp[index];
    		if(compare.operator>(newElement))
    		{
    			//cout << "temp: " << temp.getCareCard() << "and i+1 is " << i+1 << endl; 
    			temp[index + 1] = compare;
    		}
    		else 			//When we find a place where element is nolonger the smaller than current we insert
    		{
    			//cout << "done" <<endl;
    			temp[index+1] = newElement;
    			index = 0;
    			wasInserted = true; //Switch if insert is commite dones happen when we make it to the end of list
    		}
    	}
	    if(!wasInserted)
	    {
	    	temp[0] = newElement;
	    }
    	elementCount[firstDigit]++;
    }

	cout << "Capacity : " << capacity[firstDigit] << "and Element Count is: " << elementCount[firstDigit] << endl;
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
// *Dunno if it works yet. DELETE COMMENT BEFORE SUBMISSION
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
