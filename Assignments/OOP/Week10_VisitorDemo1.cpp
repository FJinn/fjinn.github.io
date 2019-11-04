#include <iostream>
#include "windows.h"
#include <ctime>
#include <vector>
#include <string>

using namespace std;

//! AI Behaviour
class VisitorInterface;

//! abstract class
//! NPC
class ElementInterface
{
	public:
		virtual string getName() = 0;
		virtual void accept(VisitorInterface* object) = 0;
};

//! abstract class
class VisitorInterface
{
	public:
		virtual void visit(ElementInterface* object) = 0;
};

//! Enemy AI
class ConcreteElement1 : public ElementInterface
{
	public:
		string getName()
		{
			return "Concrete Element 1";
		}
		
		void accept(VisitorInterface* object)
		{
			object->visit(this);			
		}
};

//! Helper AI
class ConcreteElement2 : public ElementInterface
{
	public:
		string getName()
		{
			return "Concrete Element 2";
		}
		
		void accept(VisitorInterface* object)
		{
			object->visit(this);			
		}
};

//! collide with passive object
class ConcreteVisitor1 : public VisitorInterface
{
	public:
		void visit(ElementInterface* object)
		{
			cout<<"Visited "<< object->getName()<<" using Concrete Visitor 1"<<endl;
		}
};

//! collide with active object
class ConcreteVisitor2 : public VisitorInterface
{
	public:
		void visit(ElementInterface* object)
		{
			cout<<"Visited "<< object->getName()<<" using Concrete Visitor 2"<<endl;
		}
};

int main()
{
	vector<ElementInterface*> elementList1;
	elementList1.push_back(new ConcreteElement1());
	elementList1.push_back(new ConcreteElement2());
	
	VisitorInterface* visitor1 = new ConcreteVisitor1();
	VisitorInterface* visitor2 = new ConcreteVisitor2();
	
	while(!elementList1.empty())
	{
		ElementInterface* backElementPtr = elementList1.back();
		backElementPtr->accept(visitor1);
		elementList1.pop_back();
	}
	
	system("PAUSE");
	return 0;
	
}
