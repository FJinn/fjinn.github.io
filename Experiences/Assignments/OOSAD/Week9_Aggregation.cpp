#include <iostream>
#include "windows.h"
#include <string>

using namespace std;

class Employee
{
private:
	char* myName_p;	
	
public:
	Employee(char* name)
	{
		cout<<"Employee::ctor"<<endl;
		myName_p = new char(sizeof(strlen(name)));
		myName_p = name;
	}
	
	~Employee()
	{
		cout<<"Employee::dtor"<<endl;
		delete(myName_p);
	}	
	
	char* display()
	{
		return myName_p;
	}
};

class Company
{
	private:
		char* name;
		Employee* myEmp_p;
		
	public:
		Company(char* compName, Employee* emp)
		{
			cout<<"Company::ctor"<<endl;
			name = new char(sizeof(strlen(compName)));
			name = compName;
			myEmp_p = emp;
		}
		
		~Company()
		{
			cout<<"Company::dtor"<<endl;
			myEmp_p = NULL;
		}
};

int main()
{
	cout<<"Example of Aggregation Relationship"<<endl<<endl;
	cout<<"-----------------------------------"<<endl;
	cout<<"Here, an Employee-Javin works for Company-RM"<<endl;
	Employee emp("Javin");
	Company comp("RM", &emp);
	// remove the company object
	comp.~Company();
	cout<<"At this point, Company RM gets deleted"<<endl;
	cout<<endl<<"But Employee: " <<emp.display();
	cout<<" is still ALIVE!"<<endl;
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
