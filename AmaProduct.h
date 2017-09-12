// Final Project Milestone 5
//
// Version 1.0
// Date 19-July-2017
// Author Bokyung Moon(136103165)
// Description
// AmaProduct.h
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#ifndef AMA_PRODUCT_H__
#define AMA_PRODUCT_H__
#include <cstring>
#include "Product.h"
#include "ErrorMessage.h"

namespace sict{

	class AmaProduct:public Product {
		//private members of the class AmaProduct
		private:
			char fileTag_;
			char unit_[11];
		//Protected member
		protected:
			ErrorMessage err_;
		//public members
		public:
			//constructor
			AmaProduct(const char tag='\0');
			//public functions here
			const char* unit()const { return unit_; };
			void unit(const char* value) { strncpy(unit_, value, 10); };
			//inherited four virtual methods
			std::fstream& store(std::fstream& file, bool addNewLine=true)const;
			std::fstream& load(std::fstream& file);
			std::ostream& write(std::ostream& os, bool linear)const;
			std::istream& read(std::istream& is);
	};
}
#endif
