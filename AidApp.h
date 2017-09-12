// Final Project Milestone 6
//
// Version 1.0
// Date 04-August-2017
// Author Bokyung Moon(136103165)
// Email: bmoon4@myseneca.ca
// Description
// AidApp.h
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS
#ifndef ICT_AIDAPP_H__
#define ICT_AIDAPP_H__

#include "Product.h"
#include "AmaPerishable.h"
#include "AmaProduct.h"

namespace sict {
	//AidApp class
	class AidApp {

	private:
		// holds the name of the text file used to store the product information
		char filename_[256];
		// an array of Product pointers
		Product* product_[MAX_NO_RECS];
		// an fstream instance used to create and access a file
		fstream datafile_;
		// number of Products pointed to by the product_ array
		int noOfProducts_;

		//private functions
		void pause() const;
		int menu();
		void loadRecs();
		void saveRecs();
		void listProducts() const;
		int SearchProduct(const char* sku)const;
		void addQty(const char* sku);
		void addProduct(bool isPerishable);

		// copy and assignment prevention
		AidApp(const AidApp& app) = delete;
		AidApp& operator=(const AidApp& app) = delete;

	public:
		//a function to display the menu 
		int run();
		//the constructor
		AidApp(const char* filename);
	};
}
#endif