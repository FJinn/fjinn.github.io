#include <iostream>
#include "windows.h"
#include <vector>
#include <ctime>
#include <string>

using namespace std;

class Arrow
{
	protected:
		string arrowType;
		int arrowWeight;
	public:
		Arrow(string name, int weight) : arrowType(name), arrowWeight(weight)
		{}
		
		virtual void printDescription(int level) =0;
		
		string getArrowType()
		{
			return arrowType;
		}
		
		int getArrowWeight()
		{
			return arrowWeight;
		}
};

class FireArrow: public Arrow
{
	public:
		FireArrow(string name, int weight) : Arrow(name, weight)
		{}
		
		void printDescription(int level)
		{
			for(int i=0; i<level; i++)
			{
				cout<<"Type: "<<getArrowType()<<". Weight: "<<getArrowWeight()<<"g."<<endl;
			}
		}
};

class StandardArrow: public Arrow
{
	public:
		StandardArrow(string name, int weight) : Arrow(name, weight)
		{}
		
		void printDescription(int level)
		{
			for(int i=0; i<level; i++)
			{
				cout<<"Type: "<<getArrowType()<<". Weight: "<<getArrowWeight()<<"g."<<endl;
			}
		}	
};

class ArrowBundle: public Arrow
{
	protected:
		vector<Arrow*> aBundle;
	public:
		ArrowBundle(string name, int weight) : Arrow(name, weight)
		{}
	
		void AddArrow(Arrow* arrow)
		{
			aBundle.push_back(arrow);
		}
		
		int getTotalWeight()
		{
			int totalWeight = 0;
			for(int i=0; i<aBundle.size(); i++)
			{
				totalWeight += aBundle[i]->getArrowWeight();
			}
			return totalWeight;
		}
		
		void printDescription(int level)
		{
			for(int i=0; i<level; i++)
			{
				cout<<"Icon Name: "<<this->getArrowType()<<". Weight: "<<this->getArrowWeight()<<"g."<<endl;
				if(!aBundle.empty())
				{
					for(int i=0; i<level; i++)
					{
						cout<<"Arrow of "<<getArrowType()<<": "<<endl;
						for(int j=0; j<aBundle.size(); j++)
						{
							aBundle[j]->printDescription(level);
						}
					}
				}
			}
			
		//	cout<<endl<<"Number of Arrows: "<<getTotalWeight()/20<<". Current Weight: "<<getTotalWeight()<<"g."<<endl;
		}	
};

int main()
{
	// each bundle max:200, fire 20, standard 15
	
	ArrowBundle a1("FireArrow", 500);
	ArrowBundle a2("StandardArrow", 300);
	
	FireArrow f1("Fire 1", 50);
	FireArrow f2("Fire 2", 80);
				
	a1.AddArrow(&f1);
	a1.AddArrow(&f2);
				
	StandardArrow s1("Standard 1", 10);
	StandardArrow s2("Standard 2", 15);
				
	a2.AddArrow(&s1);
	a2.AddArrow(&s2);
		
	a1.printDescription(1);
	cout<<endl;
	a2.printDescription(1);
	cout<<endl;
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
