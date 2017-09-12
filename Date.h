// Final Project Milestone 1
//
// Version 1.0
// Date 07-July-2017
// Author Bokyung Moon(136103165)
// Description
// Date.h
//
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
#ifndef SICT_DATE_H__
#define SICT_DATE_H__

#define NO_ERROR 0  
#define CIN_FAILED 1  
#define YEAR_ERROR 2
#define MON_ERROR 3  
#define DAY_ERROR 4 
#include <iostream>

namespace sict{

   class Date {
	   //private member data of class Date
	 private:
		 int value()const; 
		void errCode(int); 
		//public member data of class Date
	public:
		int year_;
		int mon_;
		int day_;
		int readErrorCode_;
	   //constructors
		Date();
		Date(int, int, int);
	   //operators
		bool operator == (const Date& D)const; 
		bool operator != (const Date& D)const; 
		bool operator < (const Date& D)const; 
		bool operator > (const Date& D)const; 
		bool operator <= (const Date& D)const; 
		bool operator >= (const Date& D)const;
	   
		int mdays(int)const; 
		int errCode()const;
		bool bad()const;
		//IO operator overloads
		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr) const;
   };
   //non-member IO operator overloads
   std::istream& operator >> (std::istream& istr, Date& obj);
   std::ostream& operator << (std::ostream& ostr, const Date& obj);
}
#endif