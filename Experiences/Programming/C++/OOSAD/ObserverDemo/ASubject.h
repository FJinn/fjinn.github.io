#pragma once

#include "Shop.h"
#include <iostream>
#include <string>
// to store multiple observer etc: football store 11-22 players
#include <vector>

using namespace std;

class ASubject
{
	vector<Shop*> observerList;
	
	public: 
		void Attach(Shop* shop);
		void Detach(Shop* shop);
		void Notify(float price);
};
