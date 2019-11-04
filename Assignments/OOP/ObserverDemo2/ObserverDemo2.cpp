#include <iostream>
#include <vector>
#include "windows.h"

// no concrete subject, DivObserver/ModObserver = concrete Observer

using namespace std;

class Subject
{
	vector<class Observer*> views;
	int value;
	
	public:
		void Attach(Observer* obs)
		{
			views.push_back(obs);
		}
		
		void SetValue(int val)
		{
			value = val;
			Notify();
		}
		
		int GetValue()
		{
			return value;
		}
		
		void Notify();
};

class Observer
{
	Subject* model;
	int denom;
	
	public:
		Observer(Subject* mod, int div)
		{
			model = mod;
			denom = div;
			model->Attach(this);			
		}
		
		virtual void update() = 0;
	
	protected:
		Subject* GetSubject()
		{
			return model;
		}
		int GetDivisor()
		{
			return denom;
		}
};

void Subject::Notify()
{
	for(int i=0; i<views.size(); i++)
	{
		views[i]->update();
	}
}

class DivObserver : public Observer
{
	public: 
	DivObserver(Subject* mod, int div) : Observer(mod, div)
	{}
	
	void update()
	{
		int v = GetSubject()->GetValue(), d = GetDivisor();
		cout<<v<<" div "<<d<<" is "<< v/d<<endl;
	}
};

class ModObserver : public Observer
{
	public: 
	ModObserver(Subject* mod, int div) : Observer(mod, div)
	{}
	
	void update()
	{
		int v = GetSubject()->GetValue(), d = GetDivisor();
		cout<<v<<" mod "<<d<<" is "<< v%d<<endl;
	}
};

int main()
{
	Subject subject;
	DivObserver divObs1(&subject, 4);
	DivObserver disObs2(&subject, 3);
	ModObserver disObs3(&subject, 3);
	subject.SetValue(14);
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
