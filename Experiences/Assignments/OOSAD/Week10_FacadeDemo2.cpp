#include <iostream>
#include <string>
#include "windows.h"

using namespace std;

class Customer
{
	private:
		string name;
	
	public:
		Customer(string n): name(n)
		{}
		
		string GetName()
		{
			return name;
		}
};

class Bank
{
	public:
		bool HasSufficientSaving(Customer c, int amount)
		{
			cout<<"Check Bank for "<<c.GetName()<<endl;
			if(amount<20000)
			{
				return false;
			}
			return true;
		}
};

class Credit
{
	public:
		bool HasGoodCredit(Customer c, int amount)
		{
			cout<<"Check credit for "<<c.GetName()<<endl;
			return true;
		}
};

class Loan
{
	public:
		bool HasGoodLoan(Customer c, int amount)
		{
			cout<<"Check Loan for "<<c.GetName()<<endl;
			return true;
		}
};

//! facade class
class Mortgage
{
	protected:
		Bank theBank;
		Credit theCredit;
		Loan theLoan;
	public:
		bool isEligible(Customer cust, int amount)
		{
			cout<<cust.GetName()<<", applied for a loan, amount: "<<amount<<endl;
			bool eligible = true;
			eligible = theBank.HasSufficientSaving(cust, amount);
			if(eligible)
			{
				eligible = theCredit.HasGoodCredit(cust, amount);
			}
			if(eligible)
			{
				eligible = theLoan.HasGoodLoan(cust, amount);
			}
			return eligible;
		}
};

int main()
{
	Mortgage theMortgage;
	Customer theCustomer("Javin");
	bool eligible = theMortgage.isEligible(theCustomer, 15000);
	cout<<endl<<theCustomer.GetName()<<" has been "<<(eligible?"Approved" :"Rejected");
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
