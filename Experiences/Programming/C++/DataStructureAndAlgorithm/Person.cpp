#include <iostream>
#include "windows.h"
#include <sstream>


using namespace std;


struct Identity 
{
	string name;
	int age;
	string hairC;
	string race;
} Person[3];



int main()
{
	int n;
	string a;
	
	for ( n=0; n<3; n++)
	{
	cout<< "Please enter your name: " << endl;
	getline(cin, Person[n].name);
	cout<< "Please Enter your hair colour: "<< endl;
	getline(cin, Person[n].hairC);
	cout<< "Please Enter your age: " << endl;
	getline(cin, a);
	stringstream (a) >> Person[n].age;
	 
	cout<< "Please Enter your race: " << endl;
	getline(cin, Person[n].race);

	cout<< "Name: ";
	cout<< Person[n].name << endl;
	cout<< "Hair Color: ";
	cout<< Person[n].hairC << endl;
	cout<< "Age: ";
	cout<< Person[n].age << endl;
	cout<< "Race: ";
	cout<< Person[n].race << endl;

	}	
	
/*	cout<< Person[n].name << endl;
	cout<< Person[n].hairC << endl;
	cout<< Person[n].age << endl;
	cout<< Person[n].race << endl;
	*/
	system("Pause");
	return 0;
}
