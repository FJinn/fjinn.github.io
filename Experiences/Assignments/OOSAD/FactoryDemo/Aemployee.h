#pragma once
#include <vector>
#include <iostream>
#include "Aitem.h"

using namespace std;

class Aemployee
{
	public:
		vector<Aitem> benefits;
		enum EMP_TYPE
		{
			PROGRAMMER=0,
			ARTIST,
			DESIGNER
		};
		
		void CreateAndBenefit(Aitem benefit);
		void PrintBenefits();
		static Aemployee* CreateEmployee(int choice);
};
