// Final Project Milestone 5
// Version 1.0
// Date	 2017-07-25
// Author	Bokyung Moon (136103165)
// Description
// ErrorMessage.cpp
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS
#include "ErrorMessage.h"
#include <cstring>

using namespace std;
namespace sict {
	//constructor with no parameter
	ErrorMessage::ErrorMessage(){message_ = nullptr;}

	//constructor with no parameters
	ErrorMessage::ErrorMessage(const char* errorMessage){
		message_ = nullptr;
		message(errorMessage);
	}
	//operator
	ErrorMessage& ErrorMessage::operator=(const char* errorMessage){
		message(errorMessage);
		return *this;
	}
	//destructor of the class
	ErrorMessage::~ErrorMessage(){delete[] message_;}

	 // function for deallocation
	void ErrorMessage::clear(){
		delete[] message_;
		message_ = nullptr;//sets message_ to nullptr.
	}
	// bool function to check whether message_ is nullptr or not
	bool ErrorMessage::isClear() const{
		if (message_ == nullptr) {
			return true;
		}
		return false;
	}
	//Sets the message_ of the ErrorMessage object to a new value 
	void ErrorMessage::message(const char* value){
		clear();
		int length = (int)strlen(value);
		message_ = new char[length + 1];
		strcpy(message_, value);
	}
	// return the message 
	const char* ErrorMessage::message() const {return  message_;}
	//non-member IO operator overloads
	std::ostream& operator <<(std::ostream& ostr, const ErrorMessage& error){
		if (!error.isClear()) {
			ostr << error.message();
		}
		return ostr;
	}
}
