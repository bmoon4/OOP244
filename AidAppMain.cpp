// Final Project Milestone 6
//
// Version 1.0
// Date 04-August-2017
// Author Bokyung Moon(136103165)
// Email: bmoon4@myseneca.ca
// Description
// AidAppMain.cpp
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#include <iostream>
#include "AidApp.h"

using namespace std;
// main function to run AidApp
int main(void) {
	sict::AidApp start("aidapp.txt");
	start.run();
}