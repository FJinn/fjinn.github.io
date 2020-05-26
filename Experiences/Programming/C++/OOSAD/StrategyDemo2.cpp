#include <iostream>
#include <string>
#include "windows.h"

using namespace std;

class QuackBehaviour
{
	public:
		virtual void quack() = 0;
};

class FlyBehaviour
{
	public:
		virtual void fly() = 0;
};

class Quack : public QuackBehaviour
{
	public:
		void quack()
		{
			cout<<"Javin says: Quack Quack"<<endl;
		}
};

class MuteQuack : public QuackBehaviour
{
	public:
		void quack()
		{
			cout<<"Javin says: MuteQuack"<<endl;
		}
};

class FlyWithWing : public FlyBehaviour
{
	public:
		void fly()
		{
			cout<<"Javin fly to the sky"<<endl;
		}
};

class FlyNoWay : public FlyBehaviour
{
	public:
		void fly()
		{
			cout<<"Javin can't fly, cause don't have wing"<<endl;
		}	
};

class FlyWithRocket : public FlyBehaviour
{
	public:
		void fly()
		{
			cout<<"Javin flt with rocket to the moon because of forever alone"<<endl;
		}	
};

class Duck
{
	public:
		QuackBehaviour* qb;
		FlyBehaviour* fb;
		
		void performQuack()
		{
			qb->quack();
		}
		void performFly()
		{
			fb->fly();
		}
		
		void setQuackBehaviour(QuackBehaviour* q)
		{
			cout<<"Changing Quack Behaviour"<<endl;
			qb = q;
		}
		void setFlyBehaviour(FlyBehaviour* f)
		{
			cout<<"Changing Fly Behaviour"<<endl;
			fb = f;
		}
		
		void floatAround()
		{
			cout<<"Javin ........"<<endl;
		}
		virtual void display() = 0;
};

class Javin : public Duck
{
	public:
		Javin()
		{
			qb = new Quack();
			fb = new FlyWithWing();
		}		
		void display()
		{
			cout<<"Javin is a real D..."<<endl;
		}
};

class Poh : public Duck
{
	public:
		Poh()
		{
			qb = new MuteQuack();
			fb = new FlyNoWay();
		}		
		void display()
		{
			cout<<"Poh is a FAKE D..."<<endl;
		}
};


class Quan : public Duck
{
	public:
		Quan()
		{
			qb = new Quack();
			fb = new FlyWithRocket();
		}		
		void display()
		{
			cout<<"Quan is a SUPER REAL D..."<<endl;
		}
};

int main()
{
	Duck* d1 = new Javin();
	d1->display();
	d1->performFly();
	d1->performQuack();
	cout<<endl;
	
	d1->setQuackBehaviour(new MuteQuack());
	d1->setFlyBehaviour(new FlyNoWay());
	cout<<endl;
	
	d1->performFly();
	d1->performQuack();
	cout<<endl;
	
	Duck* d2 = new Poh();
	d2->display();
	d2->performFly();
	d2->performQuack();
	
	Duck* d3 = new Quan();
	d3->display();
	d3->performFly();
	d3->performQuack();	
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
