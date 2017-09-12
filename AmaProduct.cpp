// Final Project Milestone 5
//
// Version 1.0
// Date 19-July-2017
// Author Bokyung Moon(136103165)
// Description
// AmaProduct.cpp
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS
#include "AmaProduct.h"
#include "ErrorMessage.h"
#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>

#define MAX_NAME_LEN 200
#define T_SKU sku(temp_sku)
#define T_NAME name(temp_name)
#define T_UNIT unit(temp_unit)
#define T_TAXED taxed(temp_taxed)
#define T_PRICE price(temp_price)
#define T_QUANTITY quantity(temp_quantity)
#define T_QTYNEEDED qtyNeeded(temp_qtyNeeded)
#define FAILBIT setstate(ios::failbit) //  I havent' learn setstate(ios::failbit) yet so I studied it from this website
									   // http://itguru.tistory.com/179

using namespace std;
namespace sict{
	//constructor 
	AmaProduct::AmaProduct(const char tag) { 
		if (tag != '\0')
			fileTag_ = 'P';
		else
			fileTag_ = 'N'; //default is 'N'
	}
	//Virtual method implementations
	//Using the operator<< of ostream first writes the fileTag_ member variable 
	//and a comma into the file argument, then without any formatting or spaces writes 
	//all the member variables of Product, comma separated
	std::fstream& AmaProduct::store(std::fstream& file, bool addNewLine)const {
		if(addNewLine)
			file << fileTag_ << "," << sku() << "," << name() << "," << price() << "," << taxed() << "," << quantity() << "," << unit() << "," << qtyNeeded() << endl;
		else
			file << fileTag_ << "," << sku() << "," << name() << "," << price() << "," << taxed() << "," << quantity() << "," << unit() << "," << qtyNeeded();
		return file;
	}
	//Virtual method implementations
	//Using the operator>>, ignore and getline methods of istream, 
	//AmaProduct reads all the comma separated fields form the current record in the file and sets the member variables using the setter methods
	std::fstream& AmaProduct::load(std::fstream& file){
		char temp_sku[MAX_SKU_LEN + 1];
		char temp_name[MAX_NAME_LEN];
		double temp_price = 0;
		bool temp_taxed = 0;
		int temp_quantity = 0;
	    char temp_unit[11];
		int temp_qtyNeeded = 0;

		file.getline(temp_sku, MAX_SKU_LEN, ',');
		file.getline(temp_name, MAX_NAME_LEN, ',');
		file >> temp_price;
		file.ignore(1, ',');
		file >> temp_taxed;
		file.ignore(1, ',');
		file >> temp_quantity;
		file.ignore(1, ',');
		file.getline(temp_unit, 10, ',');
		file >> temp_qtyNeeded;
		T_SKU;T_NAME;T_TAXED;T_PRICE;T_QUANTITY;T_UNIT;T_QTYNEEDED;
		return file;
	}
	//Virtual method implementations
	//If the err_ member variable is not clear, 
	//It simply prints the err_ using ostr and returns os. 
	//If the err_ member variable is clear (No Error) then depending on the value of linear,
	//write(), prints the Product in different formats
	std::ostream& AmaProduct::write(std::ostream& os, bool linear)const {
		if (err_.isClear() == false) {
			os << err_;
		}
		else {
			if (linear) {
				os << std::setfill(' ') << left << setw(MAX_SKU_LEN) << sku() << "|" 
					<< setw(20) << name() << "|" 
					<< right << setw(7) << fixed << setprecision(2) << cost() << "|"
					<< right << setw(4) << quantity()<<"|" 
					<< left << setw(10) << unit() << "|"
					<< right << setw(4) << qtyNeeded() << "|";
			}
			else {
				os << "Sku: " << sku() << endl;
				os << "Name: " << name() << endl;
				os << "Price: " << price() << endl;
				if (taxed()) {
					os << "Price after tax: " << cost() << endl;
				}
				else if(!taxed()) {
					os << "Price after tax: N/A" << endl;
				}
				os << "Quantity On Hand: " << quantity() <<" "<<unit() << endl;
				os << "Quantity Needed: " << qtyNeeded();
			}
		}
		return os;
	}
	//Virtual method implementations
	//Receives the values using istream (the is argument) 
	//
	std::istream& AmaProduct::read(std::istream& is) {
		err_.clear();
		char temp_sku[MAX_SKU_LEN + 1];
		char temp_name[MAX_NAME_LEN];
		char temp_unit[20];
		double temp_price = 0;
		char temp_tax;
		bool temp_taxed = 0;
		int temp_quantity = 0;
		int temp_qtyNeeded = 0;

		//if is is in a fail state, then the function exits doing nothing other than returning is.
		cout << "Sku: ";
		is >> temp_sku;
		if (is.fail()){ 
			is.FAILBIT; 
		}
		else if (!is.fail()) {
			cout << "Name: ";
			is >> temp_name;
			cin.ignore();

			if (is.fail()) {
				is.FAILBIT;
			}
			else if (!is.fail()) {
				cout << "Unit: ";
				cin.getline(temp_unit,19,'\n');

				if (is.fail()) {
					err_.message("Invalid Unit Entry");
					is.FAILBIT;
				}
				else if (!is.fail()) {
					cout << "Taxed? (y/n): ";
					is >> temp_tax;
					cin.ignore();

					if (is.fail() || (temp_tax != 'Y' && temp_tax != 'y' && temp_tax != 'N' && temp_tax != 'n')) {
						err_.message("Only (Y)es or (N)o are acceptable"); //error message!
						is.FAILBIT;
					}
					else if (!is.fail()) {
						if (temp_tax == 'Y' || temp_tax == 'y') {
							temp_taxed = true;
						}
						else if (temp_tax == 'N' || temp_tax == 'n') {
							temp_taxed = false;
						}
							cout << "Price: ";
							is >> temp_price;

							if (is.fail()){
								err_.message("Invalid Price Entry"); //error message!
								is.FAILBIT;
							}
							else if (!is.fail()) {
								cout << "Quantity On hand: ";
								is >> temp_quantity;

								if (is.fail()) {
									err_.message("Invalid Quantity Entry");//error message!
									is.FAILBIT;
								}
								else if (!is.fail()) {
									cout << "Quantity Needed: ";
									is >> temp_qtyNeeded;
									
									if (is.fail()) {
										err_.message("Invalid Quantity Needed Entry");//error message!
										is.FAILBIT;
									}
									else if (!is.fail()) {
									    T_SKU;T_NAME;T_UNIT;T_TAXED;T_PRICE;T_QUANTITY;T_QTYNEEDED;
									}
							    }
						    }
					    }		
				    }
			    }
		   }
		return is; //return the is argument
	}
}
