// Final Project Milestone 4
//
// Version 1.0
// Date 19-July-2017
// Author Bokyung Moon(136103165)
// Description
// Product.h
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////


#ifndef SICT_PRODUCT_H_
#define SICT_PRODUCT_H_
#include "general.h"
#include "Streamable.h"

namespace sict {
	// class Product derived from the class Streamable(Abstract class)
	class Product : public Streamable {
	//private members
	private:
		char sku_[MAX_SKU_LEN + 1];
		char* name_;
		double price_;
		bool taxed_;
		int quantity_;
		int qtyNeeded_; 
	//public members
	public:
		//constructors
		Product();
		Product(const char* sku, const char* name, double price=0.0, int qtyNeed =0, bool taxed = true);
		Product(const Product& P);
		//Assigning operator
		Product& operator= (const Product& P);
		// virtual destructor
		virtual ~Product();
		//public functions
		void sku(char* sku);
		void price(double price);
		void name(char* name);
		void taxed(bool taxed = false);
		void quantity(int quantity);
		void qtyNeeded(int qtyNeeded);
		const char* sku() const;
		double price() const;
		const char* name() const;
		bool taxed() const;
		int quantity() const;
		int qtyNeeded() const;
		double cost() const;
		bool isEmpty() const;
		//operators overloads
		bool operator == (const char* sku) const;
		int operator += (int qty);
		int operator -= (int qty); 
	};
	//non-member operator overload
	double operator += (double& d, const Product& p);
	//non-member IO operator overloads
	std::istream& operator>>(std::istream& is, Product& obj);
	std::ostream& operator<<(std::ostream& os, const Product& obj);

}
#endif