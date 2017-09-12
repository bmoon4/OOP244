// Final Project Milestone 5
//
// Version 1.0
// Date 25-July-2017
// Author Bokyung Moon(136103165)
// Description
// AmaPerishable.h
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////


#define _CRT_SECURE_NO_WARNINGS
#ifndef AMA_PERISHABLE_H_
#define AMA_PERISHABLE_H_

#include <iostream>
#include "ErrorMessage.h"
#include "AmaProduct.h"
#include "Streamable.h"
#include "Date.h"

namespace sict{

	class AmaPerishable : public AmaProduct {
		//private members of the class AmaPerishable
		private:
			Date expiry_;
		//public members
		public:
			//constructor
			AmaPerishable(const char P='P') :AmaProduct(P){};
			//public functions
			const Date& expiry()const { return expiry_; };
			void expiry(const Date& value) {expiry_ = value;}
			//inherited four virtual methods of the AmaProduct
			std::fstream& store(std::fstream& file, bool addNewLine=true)const;
			std::fstream& load(std::fstream& file);
			std::ostream& write(std::ostream& os, bool linear)const;
			std::istream& read(std::istream& is);
    };
}

#endif
