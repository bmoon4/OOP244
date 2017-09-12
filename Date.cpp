// Final Project Milestone 1
//
// Version 1.0
// Date 07-July-2017
// Author Bokyung Moon(136103165)
// Description
// Date.cpp
//
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////


#include <iostream>
#include <iomanip>
#include <ctime>
#include "Date.h"
#include "general.h"

using namespace std;
namespace sict{
	//Constructors
	Date::Date() {
		year_ = 0;
		day_ = 0;
		mon_ = 0;
		readErrorCode_ = NO_ERROR;
	}
	//constructor with 3 arguments
	Date::Date(int year, int mon, int day) {
		year_ = year;
		mon_ = mon;
		day_ = day;
		readErrorCode_ = NO_ERROR;
	}

	//Private Member functions
	int Date::value()const { return year_ * 372 + mon_ * 31 + day_;}

	void Date::errCode(int errorCode) { readErrorCode_ = errorCode;}

	//Public member-functions and operators
	bool Date::operator == (const Date& D)const { return this->value() == D.value();}
	bool Date::operator != (const Date& D)const { return this->value() != D.value();}
	bool Date::operator < (const Date& D)const { return this->value() <  D.value();}
	bool Date::operator > (const Date& D)const { return this->value() >  D.value();}
	bool Date::operator <= (const Date& D)const { return this->value() <= D.value();}
	bool Date::operator >= (const Date& D)const { return this->value() >= D.value();}

	int Date::mdays(int mon)const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		mon = mon_ >= 1 && mon_ <= 12 ? mon_ : 13;
		mon--;
		return days[mon] + int((mon == 1)*((year_ % 4 == 0) && (year_ % 100 != 0)) || (year_ % 400 == 0));
	}
  
	//Accessor or getter member functions:
	int Date::errCode() const { return readErrorCode_;}
	
	bool Date::bad()const {
		bool result = false;
		if (readErrorCode_ != NO_ERROR)
			result = true;
		return result;
	}

   //IO member-funtions
   std::istream& Date::read(std::istream& istr) {
	   istr >> year_;
	   istr.ignore(1, '\n');
	   istr >> mon_;
	   istr.ignore(1, '\n');
	   istr >> day_;

	   if (!(istr.fail())) {
		   if (year_ < MIN_YEAR || year_ > MAX_YEAR) {
			   errCode(YEAR_ERROR);
		   }
		   else if (mon_ < 1 || mon_ > 12) {
			   errCode(MON_ERROR);
		   }
		   else if (day_ < 1 || day_ > mdays(mon_)) {
			   errCode(DAY_ERROR);
		   }
		   else
			   errCode(NO_ERROR);
	   }
	   else
		   errCode(CIN_FAILED);
	   
	   return istr;
   }
   ////member IO operator overload
   std::ostream& Date::write(std::ostream& ostr) const {
	   ostr << year_;
	   if (mon_ >= 10) { ostr << "/" << mon_;}
	   else { ostr << "/" << setw(2) << setfill('0') << mon_;}
	   if (day_ >= 10) { ostr << "/" << day_;}
	   else{ ostr << "/" << setw(2) << setfill('0') << day_;}
	   return ostr;
   }

  //Non-member IO operator overloads
   std::istream& operator >> (std::istream& istr, Date& obj) {
	   obj.read(istr);
	   return istr;
   }
   std::ostream& operator << (std::ostream& ostr, const Date& obj) {
	   obj.write(ostr);
	   return ostr;
   }
}
