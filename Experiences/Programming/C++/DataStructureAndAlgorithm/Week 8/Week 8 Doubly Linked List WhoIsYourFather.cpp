#include <iostream>
#include "windows.h"
#include <ctime>
#include <string>

using namespace std;

class Person
{
	public:
		string name;
		Person* father; // previous
		Person* son; // next
		
		void SetFather(Person* father) // set the prev pointer (from the new node)
		{
			this->father = father;
		}
		
		void SetSon(Person* son) // getting the last node next pointer, point to new node
		{
			this->son = son;
		}
		
		Person* WhoIsYourFather() //getFather()
		{
			return father;
		}
		void AddSon(string name) // create new node
		{
			Person* son = new Person();
			son->name = name;
			this->SetSon(son);
			son->SetFather(this);
			son->son = NULL;
		}
};

void DisplayAllHierarchy(Person* person)
{
	cout << person->name << endl;
	if (person->son != NULL)
	{
		DisplayAllHierarchy(person->son);
	}
}

int main()
{
	Person* skywalker = new Person();
	skywalker->name = "Anakin Skywalker";
	skywalker->AddSon("Luke Skywalker");
	skywalker->son->AddSon("Ben Skywalker");
	skywalker->son->son->AddSon("Javin Skywalker");
//	DisplayAllHierarchy(skywalker);
	cout << skywalker->son->father->son->son->WhoIsYourFather()->son->father->father->son->son->son->name;
	
	cout << endl;
	system("PAUSE");
	return 0;
}
