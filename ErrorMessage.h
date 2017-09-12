// Final Project Milestone 5
// Version 1.0
// Date	2017-07-25
// Author	Bokyung Moon (136103165)
// Description
// ErrorMessage.h
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
#ifndef ICT_ERRORMESSAGE_H
#define ICT_ERRORMESSAGE_H

#include <iostream>

using namespace std;
namespace sict{

	class ErrorMessage {
		//private member of class ErrorMessage
		char* message_; 
		//public member of class ErrorMessage
	public:
		//constructors
		ErrorMessage(); 
		ErrorMessage(const char* errorMessage); 
		ErrorMessage(const ErrorMessage& em) = delete; 
		//operators
		ErrorMessage& operator=(const ErrorMessage& em) = delete;
		ErrorMessage& operator=(const char* errorMessage);
		//virtual destructor
		virtual ~ErrorMessage();
		//public functions
		void clear(); 
		bool isClear() const; 
		void message(const char* value);
		const char* message() const; 
	};
	//non-member IO operator overloads
	std::ostream& operator << (std::ostream&, const ErrorMessage&);
}

#endif
