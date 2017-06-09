/*
 * WICPS.cpp
 * 
 * Description: Models a walk-in clinic patient system
 *				Maintains the information of the patients which can be added,
 *				edited, or deleted
 *				Data isn't saved after the program is exited
 *
 * Last modified on: May 29, 2017
 * Author: Vicky Lau, Jacky Tse
 */

#include <string>
#include <iostream>
#include <sstream>	// For stringstream to convert from string to integer
#include "List.h"
#include "Patient.h"

using namespace std;

// Description: Checks if the string only contains integers
bool isDigit( string aString ){
	int index = 0;

	while( aString[index] != 0 ){
		if( aString[index] < '0' || aString[index] > '9' ){
			return false;
		}

		index++;
	}

	return true;
}

// Description: Returns true if the string is 10 digits
bool isTenDigits( string aString ){
	int count = 0;

	while( aString[count] != 0 ){
		count++;
	}

	if( count == 10 && isDigit( aString ) ){
		return true;
	}

	return false;
}

// Description: Prompts user for desired action.
//				Loops until an integer from 1 to arrSize-1 is entered.
//				Each of those integers correspond to a avaliable option.
// Precondition: arr[0] is a prompt.
//				 The rest of the array elements are options.
// Postcondition: returns an integer from 1 to arrSize-1
int optionPrompt( string arr[], int arrSize ){
	int input = 0;
	string strInput;
	int index;

	cout << endl;
	cout << "-----" << endl;
	cout << arr[0] << endl;

	// Prints all the options
	for( index = 1; index < arrSize; index++ ){
		cout << "   " << index << ") " << arr[index] << endl;
	}
		
	cout << endl;
	cout << " Please enter an option number: ";

	// Continues prompting user until an indicated integer is entered
	while( input < 1 || input >= arrSize ){
		getline( cin, strInput );

		// Converts the string strInput to integer input
		// if strInput only consists of integers
		if( isDigit( strInput ) ){
			stringstream convert(strInput);
			if( !(convert >> input) ){
				input = 0;
			}
		}
		else{
			input = 0;
		}

		if( input < 1 || input >= arrSize ){
			cout << " Invalid entry. Please enter a number from 1-" << arrSize-1 
			     << ": ";
		}
	}

	cout << endl;

	return input;
}

// Description: Prompts the user for a care card number.
string careCardPrompt(){
	string aCareCard;

	cout << " Please enter the patient's CareCard Number: ";
	getline( cin, aCareCard );

	return aCareCard;
}


int main(void){
	int 	mainInput 	  = 0;
	int 	modiInput 	  = 0;
	string	strInput	  = "";
	string	initPrompt[8] = {	"What would you like to do?",
								"Enter a new patient",
								"Remove a patient",
								"Search for a patient",
								"Modify a patient's record",
								"See list of patients",
								"Remove all patients",
								"Exit system" };
	string  modiPrompt[7] = {	"What would you like to modify?",
								"Name",
								"Address",
								"Phone Number",
								"E-Mail",
								"All of the above",
								"Cancel" };
	List 	list;
	Patient entry;
	Patient *entryPtr;

	const int ADD 		 = 1;
	const int REMOVE 	 = 2;
	const int SEARCH 	 = 3;
	const int MODIFY 	 = 4;
	const int PRINT 	 = 5;
	const int REMOVE_ALL = 6;
	const int QUIT 		 = 7;

	const int MOD_NAME 	  = 1;
	const int MOD_ADDRESS = 2;
	const int MOD_PHONE   = 3;
	const int MOD_EMAIL   = 4;
	const int MOD_ALL 	  = 5;

	cout << endl;
	cout << "******* Welcome to the Walk-In Clinic Patient System *******" << endl;

	while( mainInput != QUIT ){
		mainInput = optionPrompt( initPrompt, 8 );

		// Add a patient
		if( mainInput == ADD ){ 
			cout << "Adding a Patient:" << endl;

			strInput = careCardPrompt();

			//if( isTenDigits( strInput ) && !inList( list, strInput ) ){
			if( isTenDigits( strInput ) ){
				entry = Patient( strInput );

				if( list.search( entry ) == NULL && list.insert( entry ) ){
					cout << " Patient " << entry.getCareCard() 
					     << " has been successfully added." << endl;
				}
				else{
					cout << " Error. Patient was not added." << endl;
				}
			}
			else{
				cout << " Error. The CareCard " << strInput<< " is invalid." << endl;
			}
			
		}

		// Remove a patient
		else if( mainInput == REMOVE ){ 
			cout << "Removing a Patient:" << endl;
				strInput = careCardPrompt();

				if( isTenDigits( strInput ) ){
					entry = Patient( strInput );

					if( list.search( entry ) != NULL && list.remove(entry) ){
						cout << " Patient " << strInput 
						     << " has been successfully removed." << endl;
					}
					else{
						cout << " Error. The patient was not removed." << endl;
					}
				}
				else{
					cout << " Error. The CareCard " << strInput<< " is invalid." << endl;
				}
		}

		// Search for a patient
		else if( mainInput == SEARCH ){ 
			cout << "Searching for a Patient:" << endl;
				strInput = careCardPrompt();

				if( isTenDigits( strInput ) ){
					entry = Patient( strInput );
					entryPtr = list.search( entry );

					if( entryPtr != NULL ){
						entry = *entryPtr;

						cout << " ";

						entry.printPatient();
					}
					else{
						cout << " Error. Patient not found." << endl;
					}
				}
				else{
					cout << " Error. The CareCard " << strInput<< " is invalid." << endl;
				}		
		}

		// Modify a Patient
		else if( mainInput == MODIFY ){ 
			cout << "Modifying a Patient:" << endl;
				strInput = careCardPrompt();

				if( isTenDigits( strInput ) ){
					entry = Patient( strInput );
					entryPtr = list.search( entry );

					if( entryPtr == NULL ){
						cout << " Error. Patient not found.";
					}
					else{
						modiInput = optionPrompt( modiPrompt, 7 );

						// Modify name
						if( modiInput == MOD_ALL || modiInput == MOD_NAME ){
							cout << "  New name: ";
							getline( cin, strInput );

							entryPtr->setName( strInput );
						}
			
						// Modify address
						if( modiInput == MOD_ALL || modiInput == MOD_ADDRESS ){ 
							cout << "  New address: ";
							getline( cin, strInput );

							entryPtr->setAddress( strInput );
						}
			
						// Modify phone
						if( modiInput == MOD_ALL || modiInput == MOD_PHONE ){ 
							cout << "  New phone number: ";
							getline( cin, strInput );

							entryPtr->setPhone( strInput );
						}
			
						// Modify email
						if( modiInput == MOD_ALL || modiInput == MOD_EMAIL ){ 
							cout << "  New e-mail: ";
							getline( cin, strInput );

							entryPtr->setEmail( strInput );
						}
					}	
				}
				else{
					cout << " Error. The CareCard " << strInput<< " is invalid." << endl;
				}
		}

		// Prints a list of patients
		else if( mainInput == PRINT ){ 
			cout << "List of Patients:" << endl;
			list.printList();
		}

		// Removes all patients
		else if( mainInput == REMOVE_ALL ){
			cout << "Removing all Patient:" << endl;

			list.removeAll();

			cout << " All records of patients have been deleted." << endl;
			}			
		}

	cout << endl;
	cout << "Thank you for using the Walk-In Clinic Patient System!" << endl;
	cout << endl;

	return 0;
}

// End of WICPS.cpp