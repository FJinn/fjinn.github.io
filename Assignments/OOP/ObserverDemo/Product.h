#pragma once 
#include "ASubject.h"

class Product : public ASubject
{
	public:
		void ChangePrice(float price);
};
