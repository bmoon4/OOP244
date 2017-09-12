// Final Project Milestone 4
// Version 1.0
// Date	2017-07-16
// Author	Bokyung Moon(136103165)
//
// For you final test before submission:
//      DO NOT MODIFY THIS FILE IN ANY WAY
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
#ifndef SICT_STREAMABLE_H__
#define SICT_STREAMABLE_H__
#include <iostream>
#include <fstream>

using namespace std;
namespace sict{
  //Abstract class
  class Streamable{
	public:
		//pure virual functions
		virtual std::fstream& store(std::fstream& file, bool addNewLine = true) const = 0;    
		virtual std::fstream& load(std::fstream& file) = 0;
		virtual std::ostream& write(std::ostream& os, bool linear)const = 0;
		virtual std::istream& read(std::istream& is) = 0;
  };
  
}


#endif
