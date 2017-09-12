// Final Project Milestone 5
//
// Version 1.0
// Date 19-July-2017
// Author Bokyung Moon(136103165)
// Description
// Product.cpp
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include "Product.h"
#include "general.h"

using namespace std;
namespace sict{
	//No argument Constructor
	//sets the Product to a safe recognizable empty state. 
	Product::Product() {
		sku_[0] = '\0';
		name_ = nullptr;
		price_ = 0;
		taxed_ = false;
		quantity_ = 0;
		qtyNeeded_ = 0;
	}
	//copy constructor
	Product::Product(const Product& copy) {
		quantity_ = copy.quantity_;
		qtyNeeded_ = copy.qtyNeeded_;
		price_ = copy.price_;
		taxed_ = copy.taxed_;
		strncpy(sku_, copy.sku_, MAX_SKU_LEN + 1);
		name_ = new char[strlen(copy.name_) + 1];
		strcpy(name_, copy.name_);
	}
	//assigning operator
	Product& Product::operator = (const Product& P) {
		if (this != &P) {
			quantity_ = P.quantity_;
			price_ = P.price_;
			taxed_ = P.taxed_;
			qtyNeeded_ = P.qtyNeeded_;
			strncpy(sku_, P.sku_, MAX_SKU_LEN + 1);
		
			delete[] name_;
			
			if (P.name_ != nullptr) {
				name_ = new char[strlen(P.name_) + 1];
				strcpy(name_, P.name_);
			}
			else
				name_ = nullptr;
		}
		return *this;
	}
	//5 argument Constructor
	Product::Product(const char* sku, const char* name, double price, int qtyNeed, bool taxed) {
		strncpy(sku_, sku, (MAX_SKU_LEN + 1));
		name_ = new char[strlen(name) + 1];
		strcpy(name_, name);
		quantity_ = 0;
		price_ = price;
		qtyNeeded_ = qtyNeed;
		taxed_ = taxed;
	}
	//destructor
	Product::~Product() {
		delete[] name_;
		name_ = nullptr;
	}
	
	//Void Setters
	void Product::sku(char* sku) {
		strncpy(sku_, sku, MAX_SKU_LEN);
		sku[MAX_SKU_LEN] = '\0';
	}
	void Product::price(double price) {price_ = price;}
	void Product::name(char* name) {
		name_ = new char[strlen(name) + 1];
		strncpy(name_, name, (strlen(name) + 1));
	}
	void Product::taxed(bool taxed) {taxed_ = taxed;}
	void Product::quantity(int quantity) {quantity_ = quantity;}
	void Product::qtyNeeded(int qtyNeeded) {qtyNeeded_ = qtyNeeded;}

	//Getters
	const char* Product::sku() const {return sku_;}
	double Product::price() const {return price_;}
	const char* Product::name()  const {return name_;}
	bool Product::taxed() const {return taxed_;}
	int Product::quantity() const {return quantity_;}
	int Product::qtyNeeded() const {return qtyNeeded_;}
	double Product::cost() const {
		double cost;
		if (taxed_ == true)
			cost = (price_ + (price_*TAX));
		else
			cost = price_;
		return cost;
	}
	//isEmpty return true if the Product is in a safe empty state. 
	bool Product::isEmpty() const {
		return (name_ == nullptr && sku_[0]=='\0' && price_ == 0 && quantity_ == 0 && qtyNeeded_ ==0 && taxed_ == false);
	}

	//Member Operators
	bool Product::operator == (const char* sku) const {
		if (strcmp(sku_, sku) == 0)
			return true;
		else
			return false;
	}
	
	//non-member operator which receives int and return integer
	int Product::operator += (int qty) {
		int result;
		result = quantity_ + qty;
		this->quantity_ = result;
		return result;
	}
	//non-member operator which receives an integer and returns an integer
	int Product::operator -= (int qty) {
		int result;
		result = quantity_ - qty;
		this->quantity_ = result;
		return result;
	}

	//non-member operator which receives a double reference value as left operand 
	//and a constant Product reference as right operand and returns a double value
	double operator += (double& d, const Product& p) {
		d += (p.cost() * p.quantity());
		return d;
	}
	//non-member IO operator overloads
	std::ostream& operator << (std::ostream& os, const Product& obj) {
		obj.write(os, true);
		return os;
	}
	//non-member IO operator overloads
	std::istream& operator >> (std::istream& is, Product& obj) {
		obj.read(is);
		return is;
	}
}


