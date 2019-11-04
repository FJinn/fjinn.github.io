#include <iostream>
#include "windows.h"
#include <vector>
#include <ctime>
#include <string>

using namespace std;

class Component
{
	protected:
		string name;
		double salary;
	public:
		Component(string n, double s) : name(n), salary(s)
		{}
		
		string getName()
		{
			return name;
		}
		
		double getSalary()
		{
			return salary;
		}
		
		virtual void printSalary(int level) = 0;
};

//Worker is leaf
class Worker : public Component
{
	public:
		Worker(string name, double salary) : Component(name, salary)
		{}
		
		void printSalary(int level)
		{
			for(int i=0; i<level; i++)
			{
				cout<<"Worker: "<<getName()<<", Salary: RM"<<getSalary()<<endl;
			}
		}
};


//Manager is composite
class Manager : public Component
{
	protected:
		vector<Component*> workerList;
	public:
		Manager(string name, double salary): Component(name, salary)
		{}
		
		void Add(Component* worker)
		{
			workerList.push_back(worker);
		}
		
		void printSalary(int level)
		{
			cout<<"Manager Name: "<<this->getName()<<", Salary: RM"<<this->getSalary()<<endl;
			if(!workerList.empty())
			{
				for(int i=0; i<level; i++)
				{
					cout<<"Worker of "<<getName()<<": "<<endl;
					for(int j=0; j<workerList.size(); j++)
					{
						workerList[j]->printSalary(level);
					}
				}
			}
		}
};

int main()
{
	Manager president("Jonathan", 180000);
	Manager productionManager("Javin", 10000);
	Manager programManager("pohpoh", 20000);
	Manager marketingManager("Darshini",50000);
	Manager accountManager("money",98000);
	
	Worker programmer1("ShengWei", 1000);
	Worker programmer2("Shaun", 2000);	
	
	Worker production1("David", 5000);
	Worker production2("Jason",1);
	
	president.Add(&productionManager);
	president.Add(&programManager);
	president.Add(&marketingManager);
	president.Add(&accountManager);
	
	programManager.Add(&programmer1);
	programManager.Add(&programmer2);
	
	productionManager.Add(&production1);
	productionManager.Add(&production2);
		
	cout<<"The hierarchy of the company: "<<endl;
	president.printSalary(1);
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
