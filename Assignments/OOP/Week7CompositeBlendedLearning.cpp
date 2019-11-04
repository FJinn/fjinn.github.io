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
						cout<<"Arrow Bundle of "<<getArrowType()<<": "<<endl;
						for(int j=0; j<aBundle.size(); j++)
						{
							aBundle[j]->printDescription(level);
						}
					}
				}
			}
			
			cout<<"Number of Arrows: "<<aBundle.size()<<". Current Weight: "<<getTotalWeight()<<"g."<<endl;
		}	
};

int main()
{
	// each bundle max:200, fire 20, standard 15
	
	//	ArrowBundle a1("FireArrow", 200);
	//	ArrowBundle a2("StandardArrow", 200);
	
	vector<ArrowBundle*> aB;
	
	//!! if declare in choice == 2, it will call pure virtual function in choice == 3, HAVE NO IDEA WHY.
	FireArrow f("Fire", 20);
	StandardArrow s("Standard", 15);
	
	bool isExit = false;
	int choice = 0;
	do 
	{
		if(choice ==0)
		{
			system("CLS");
			
			cout<<"1. Create Bundle."<<endl;
			cout<<"2. Add Arrow."<<endl; 
			cout<<"3. Check Bundle."<<endl; 
			cout<<"4. Exit."<<endl;
			cout<<"Your Choice: ";
			cin>>choice;
		}
		else if(choice ==1)
		{
			// clear up previous screen
			system("CLS");
			
	//		ArrowBundle a1("FireArrow", 200);
	//		aF = new ArrowBundle(a1.getArrowType(), a1.getArrowWeight());
			
			
			ArrowBundle* aF = new ArrowBundle("FireArrow", 200);
			ArrowBundle* aS = new ArrowBundle("StandardArrow", 200);
			
			int numPick =0;
			cout<<"1. Fire Arrow Bundle"<<endl;
			cout<<"2. Standard Arrow Bundle"<< endl;
			cout<<"Choose which bundle to create: ";
			cin>>num;
				
			system("CLS");		
		
			if(num ==1)
			{
				aB.push_back(aF);
			}
			else if(num ==2)
			{
				aB.push_back(aS);
			}
			
/*			if(aF == NULL)
			{
				aF = new ArrowBundle("FireArrow", 200);
				cout<<"Fire Arrow bundle is created."<<endl;
			}
			else
			{
				cout<<"There is a Fire Arrow Bundle already!"<<endl;
			}
			
			if(aS == NULL)
			{
				aS = new ArrowBundle("StandardArrow", 200);
				cout<<"Standard Arrow bundle is created."<<endl;
			}
			else
			{
				cout<<"There is a Standard Arrow Bundle already!"<<endl;
			}
*/			
			system("Pause");
			
			// back to choice 0 
			choice = 0;
			
		}
		else if(choice ==2)
		{
			// -> 1. fire 2. standard => compare weight
			
			// clear up previous screen
			system("CLS");
			
			if(aF!= NULL || aS != NULL)
			{
				int num =0;
				cout<<"1. Fire Arrow"<<endl;
				cout<<"2. Standard Arrow"<< endl;
				cout<<"Choose which arrow to add into your bundle: ";
				cin>>num;
				
					system("CLS");
			
				if(num ==1)
				{
					if(aF->getTotalWeight() >= 200)
					{
						cout<<"This Fire Bundle has reached it maximum carry weight!"<<endl;
						cout<<"Current weight: "<<aF->getTotalWeight()<<endl;
					}
					else
					{
						aF->AddArrow(&f);
						cout<<"Current weight: "<<aF->getTotalWeight()<<endl;
					}
				}
				else if(num ==2)
				{
					if(aS->getTotalWeight() >= 200)
					{
						cout<<"This Standard Bundle has reached it maximum carry weight!"<<endl;
						cout<<"Current weight: "<<aS->getTotalWeight()<<endl;
						
					}
					else
					{
						aS->AddArrow(&s);
						cout<<"Current weight: "<<aS->getTotalWeight()<<endl;
					}
				}
				system("Pause");
				
				// back to choice 0 
				choice = 0;
			}
			else
			{
				cout<<"There is no bundle."<<endl;
				system("PAUSE");
				choice = 0;
			}
			
		}
		else if(choice ==3)
		{
			// clear up previous screen
			system("CLS");
			
			// -> call print description, display current total weight	
			if(aF != NULL)
			{
				aF->printDescription(1);
				cout<<endl;
			}	
			else
			{
				cout<<"Fire Arrow Bundle is not created!"<<endl;
			}
			
			if(aS != NULL)
			{
				aS->printDescription(1);
				cout<<endl;
			}	
			else
			{
				cout<<"Standard Arrow Bundle is not created!"<<endl;
			}
			
			system("Pause");
			
			// back to choice 0 
			choice = 0;
		}
		else if(choice ==4)
		{
			isExit = true;
		}
		
	}while(!isExit);
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
