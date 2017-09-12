// Final Project Milestone 6
//
// Version 1.0
// Date 04-August-2017
// Author Bokyung Moon(136103165)
// Email: bmoon4@myseneca.ca
// Description
// AidApp.cpp
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include "AidApp.h"


using namespace std;

namespace sict {
	
	//Constructor
	AidApp::AidApp(const char* filename) {

		//Copies filename to filename_ member variable
		strncpy(filename_, filename, 256);
		//Sets all the products_ to nullptr
		for (int i = 0; i < MAX_NO_RECS; i++) {
			product_[i] = nullptr;
		}
		//Sets noOfProducts_ to zero
		noOfProducts_ = 0;
		//Loads the Records (loadRecs())
		loadRecs();
	}
	
	// pause function
	void AidApp::pause() const {
		//if the user hits any other key, the key is ignored
		//Only the ENTER key will terminate this function
		cout << "Press Enter to continue..." << endl;
		cin.ignore(1000, '\n');	
	}

	// menu function
	int AidApp::menu() {
		// for user input
		int selection;
		// menu
		cout << "Disaster Aid Supply Management Program" << endl;
		cout << "1- List products" << endl;
		cout << "2- Display product" << endl;
		cout << "3- Add non-perishable product" << endl;
		cout << "4- Add perishable product" << endl;
		cout << "5- Add to quantity of purchased products" << endl;
		cout << "0- Exit program" << endl;
		cout << "> ";

		cin >> selection;
		// clean the input buffer
		cin.ignore();
		// for user's wrong input
		if (selection > 5 || selection < 0) {
			selection = -1;
		}
		//return the input
		return selection;
	}

	// load record from filestream
	void AidApp::loadRecs() {
		// int for new product's index number
		int idx = 0;
		// char to distinguish types(Perishable/ Non-Perishable)
		char type;
		//Opens the datafile_ for reading
		datafile_.open(filename_, ios::in);
		// I didn't know what 'ios::in and ios::out' are so I found a website to know how to use them
		// blog.naver.com/shimchan2/70009452422

		if (datafile_.is_open()) {

			while (datafile_.get(type)) {

				datafile_.ignore();
				// memory leaks prevention
				//by deleting each Product element pointer in the array
				//before overwriting/replacing the element with a new Product pointer. 
				delete[] product_[idx];
				product_[idx] = nullptr;

				// if type is 'Perishable'
				if (type == 'P') {
					// Dynamically create a AmaPerishable instance
					AmaPerishable* product_new = new AmaPerishable;
					// load data record from datafile_
					product_new->load(datafile_);
					datafile_.ignore();
					// And hold its address in product_ array at index (idx)
					product_[idx] = product_new;
				}
				// if type is Non-Perishable'
				else if (type == 'N') {
					//Dynamically create a AmaProduct instance
					AmaProduct* product_new = new AmaProduct;
					// load data record from datafile_
					product_new->load(datafile_);
					datafile_.ignore();
					// And hold its address in product_ array at index (idx)
					product_[idx] = product_new;
				}
				// if type is neither N nor P
				else {
					//leave it as nullptr
					product_[idx] = nullptr;
				}
				// if either P or N is read
				// add one to index (idx)
				idx++;
			}
		}
		// if the file does not exist, it will create an empty file
		// close the file and exit
		else {
			datafile_.clear();
			datafile_.close();
			datafile_.open(filename_, ios::out);
		}
		// close the file and set noOfProducts_ to index (idx)
		datafile_.close();
		noOfProducts_ = idx;
	}

	// save record
	void AidApp::saveRecs() {
		//open the data file for writing
		datafile_.open(filename_, ios::out);

		//loops through the product_ array up to noOfProducts_
		for (int i = 0; i < noOfProducts_; i++) {
			if (product_[i]->quantity() > 0) {
				// store them in the datafile_
				product_[i]->store(datafile_);
			}
		}
		// closes the file
		datafile_.close();
		// load records again
		loadRecs();
	}

	// list products
	void AidApp::listProducts() const {
		int i;
		double total = 0;
		int flag = 0;
		
		//print
		cout << " Row | SKU    | Product Name       | Cost  | QTY| Unit     |Need| Expiry   " << endl;
		cout << "-----|--------|--------------------|-------|----|----------|----|----------" << endl;
		
		for (i = 0; i < noOfProducts_; i++) {
			//set width 4 space wide
			cout << setfill(' ') << setw(4) << i + 1 << " | ";
			product_[i]->write(cout, true);
			
			//calculate the total cost of the products 
			//in a double value using the operator+= implemented by the Product class
			total += *product_[i];
			cout << endl;
			flag++;
			// When the number of printed items reaches 10 (flag == 10), 
			// it will pause 
			if (flag == 10) {
				pause();
				flag = 0;
			}
		}
		cout << "---------------------------------------------------------------------------" << endl;
		cout.setf(ios::fixed);
		cout.precision(2);
		// prints total cost
		cout << "Total cost of support: $" << total <<endl;
		cout << endl;
		cout.unsetf(ios::fixed);
		cout.precision(6);

	}
	// search product
	int AidApp::SearchProduct(const char* sku)const {
		int idx = -1;
		// checks each of items for the same SKU
		for (int i = 0; i < noOfProducts_; i++) {
			// by using 'strcmp'
			if (strcmp(product_[i]->sku(), sku) == 0) {
				idx = i;
			}
		}
		// return the index (idx) of the found Product in the product_ arrau
		return idx;
	}

	// add quantity
	void AidApp::addQty(const char* sku) {
		// need to search the product's index at first
		int idx = SearchProduct(sku);
		int added = 0;
		// n stands for 'exactly needed' quantity
		// (needed quantity - current quantity)
		int n = (product_[idx]->qtyNeeded() - product_[idx]->quantity());

		// Not found the product
		if (idx == -1) {
			cout << "Not found!" << endl << endl;
		}

		//if found the product
		else{
			// Enter the number of items
			cout << "Please enter the number of purchased items: ";
			cin >> added;
			cin.ignore();
			// if the input is invalid, prints error message
			if (cin.fail()) {
				cout << "Invalid quantity value!" << endl;
			}
			else {
				// if user's input is less than or equal the amount needed (n)
				if (added <= n) {
					// add user's input to product 
					*product_[idx] += added;
				}
				// if user's input is NOT less than or equal the amount needed (n)
				else {
					// only accept the amount required (n) and prints a message to return the extra
					*product_[idx] += n;
					 cout << "Too many items; only " << n << " is needed, please return the extra " << added - n << " items" << endl;
				}
				//save the record and prints "updated"
				saveRecs();
				cout << "Updated!" << endl;
			}
		}
	}
	//add product
	void AidApp::addProduct(bool isPerishable) {
		//Depending on the value of the argument (isPerishable) being true or false,
		// create a AmaPerishable or AmaProduct

		// add to perishable product (the menu number is '4')
		if (isPerishable) {
			// Dynamically create a AmaPerishable instance (temporary)
			AmaPerishable* temp = new AmaPerishable;
			// accept new records from user (read)
			temp->read(cin);

			if (cin.fail()) {
				// if there is an error, display the Product
				temp->write(cout, false);
				cout << endl;
			}
			else {
				//save the user's new addition to product_ array
				product_[noOfProducts_] = temp;
				noOfProducts_++;
				//and save the record
				saveRecs();
				cout << endl;
				cout << "Product added" << endl;
				cout << endl;
			
			}
		}
		// add to Non-perishable product (the menu number is '3')
		else {
			// Dynamically create a AmaProduct instance (temporary)
			AmaProduct* temp = new AmaProduct;
			// accept new records from user (read)
			temp->read(cin);
			
			if (cin.fail()) {
				// if there is an error, display the Product
				temp->write(cout, false);
				cout << endl;
			}
			else {
				//save the user's new addition to product_ array
				product_[noOfProducts_] = temp;
				noOfProducts_++;
				//and save the record
				saveRecs();
				cout << endl;
				cout << "Product added" << endl;
				cout << endl;
		
			}
		}
		// clear the input buffer
	
		cin.clear();
		cin.ignore();
	}

  //run 
  //Display the menu, receive the user¡¯s selection, 
  //and do the action requested (follow with a pause using the pause() function), 
  //and repeat (redisplay the menu¡¦) until the user selects zero to exit. 
  int AidApp::run() {
		int no=0;
		char Tempsku[MAX_SKU_LEN];
		int idx = 0;

		do {
			no = menu();
			cout << endl;
			switch (no) {
			case 0:
				cout << "Goodbye!" << endl;
				break;
			case 1:
				listProducts();
				break;
			case 2:
				idx = -1;
				cout << "Please enter the SKU: ";
				cin >> Tempsku;
				cin.ignore();
				idx = SearchProduct(Tempsku);
				if (idx == -1) {
					cout << "Not found!" << endl << endl;
				}
				else {
					cout << endl;
					product_[idx]->write(cout, false);
					cout << endl <<endl;
				}
				break;
			case 3:
				addProduct(false);
				break;
			case 4:
				addProduct(true);
				break;
			case 5:
				cout << "Please enter the SKU: ";
				cin >> Tempsku;
				cin.ignore();
				addQty(Tempsku);
				break;
			default:
				cout << "===Invalid Selection, try again===" << endl;
				break;
			}
			pause();
		} while (no !=0);
		return no;
	}
}

