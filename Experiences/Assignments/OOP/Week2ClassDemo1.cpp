#include <iostream>
#include <string>
#include "windows.h"

using namespace std;

class Human{  // struct human { };
	//Class definition
	// attribute/ property
	
public:
		int age;
		string name;
		int weight;
		int height;
	
	// Class Implementation	
		void DisplayHumanDetail(){
			cout<<"Name: "<<name<<endl;
			cout<<"Age: "<<age<<endl;
			cout<<"Weight: "<<weight<<endl;
			cout<<"Height: "<<height<<endl;
		}
	
};

int main(){
	
	//! Define human object
	//! similar to variable declaration
	//! result;
	Human h1;
	//! access and modified the h1 object propety/attribute
	h1.name = "David";
	h1.age = 18;
	h1.weight = 70;
	h1.height = 178;
	h1.DisplayHumanDetail();
	
	cout<<endl;
	system("PAUSE");
	return 0;
}

