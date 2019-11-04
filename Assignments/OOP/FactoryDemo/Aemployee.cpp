#include "Aemployee.h"
#include "Aitem.h"
#include "Employee.h"

Aemployee* Aemployee::CreateEmployee(int choice)
{
	if(choice == 1)
	{
		return new Programmer();
	}
	else if(choice == 2)
	{
		return new Artist();
	}
	else if(choice == 3)
	{
		return new Designer();
	}
}

void Aemployee::CreateAndBenefit(Aitem benefit)
{
	benefits.push_back(benefit);
}

void Aemployee::PrintBenefits()
{
	for(int i=0; i<benefits.size(); i++)
	{
		cout<<benefits[i].getName()<<endl;
	}
}
