// Final Project Milestone 5
//
// Version 1.0
// Date 19-July-2017
// Author Bokyung Moon(136103165)
// Description
// AmaPerishable.cpp
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "AmaPerishable.h"
#define EXPIRY_ERR expiry_.errCode()
#define FAILBIT setstate(ios::failbit)

using namespace std;
namespace sict {
	
	//Virtual method implementations 
	//Calls the parent’s store passing the file and “false?as arguments and then writes a comma 
	//and the expiry date into the file. If the addNewLine argument is true, 
	//it will write a newline into the file.  
	std::fstream& AmaPerishable::store(std::fstream& file, bool addNewLine)const {
		AmaProduct::store(file, false);
		file << "," << expiry_ <<endl;
		return file;
	}
	//Virtual method implementations
	//Calls the parent’s load passing the file as the argument 
	//and then calls the read method of the expiry_ object passing the file 
	//as the argument and then ignores one character 
	std::fstream& AmaPerishable::load(std::fstream& file) {
		AmaProduct::load(file);
		file.ignore();
		file >> expiry_;
		return file;
	}
	//Virtual method implementations
	//Calls the write of the parent passing os and linear as arguments. 
	//Then if err_ is clear and product is not empty
	std::ostream& AmaPerishable::write(std::ostream& os, bool linear)const {
		AmaProduct::write(os, linear);
		if (err_.isClear()) {
			if (linear)
				os << expiry_;
			else
				os << endl << "Expiry date: " << expiry_;
				
		}
		return os;
	}
	//Virtual method implementations
	//It will call parent’s read passing is as argument. 
	std::istream& AmaPerishable::read(std::istream& is) {
		AmaProduct::read(is);

		if (err_.isClear()) {
			cout << "Expiry date (YYYY/MM/DD): ";
			expiry_.read(is);
		}
		if (EXPIRY_ERR == 1) {
			err_.message("Invalid Date Entry");
			is.FAILBIT;
		}
		else if (EXPIRY_ERR == 2) {
			err_.message("Invalid Year in Date Entry");
			is.FAILBIT;
		}
		else if (EXPIRY_ERR == 3) {
			err_.message("Invalid Month in Date Entry");
			is.FAILBIT;
		}
		else if (EXPIRY_ERR == 4) {
			err_.message("Invalid Day in Date Entry");
			is.FAILBIT;
		}
		return is;
	}
}
