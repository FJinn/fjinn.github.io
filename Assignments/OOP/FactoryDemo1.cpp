#include <iostream>
#include "windows.h"
#include <vector>

using namespace std;

class Stooge
{
	public:
		static Stooge* make_stooge(int choice);
		virtual void slap_stick()=0;
};

class Larry : public Stooge
{
	public:
		void slap_stick()
		{
			cout<<"Human"<<endl;
			cout<<"Weapon List"<<endl;
			cout<<"\t1.Hand Gun"<<endl;
			cout<<"Armor List"<<endl;
			cout<<"\t1.Thick Jacket"<<endl;
		}
};

class Sam : public Stooge
{
	public:
		void slap_stick()
		{
			cout<<"Soldier"<<endl;
			cout<<"Weapon List"<<endl;
			cout<<"\t1.Rifle"<<endl;
			cout<<"Armor List"<<endl;
			cout<<"\t1.Bullet Proof Vest"<<endl;
		}
};

Stooge* Stooge::make_stooge(int choice)
{
	if(choice == 1)
	{
		return new Larry;
	}
	else if(choice == 2)
	{
		return new Sam;
	}
}

int main()
{
	vector<Stooge*> roles;
	int choice;
	
	cout<<"Human(1), Soldier(2): ";
	cin>>choice;
	roles.push_back(Stooge::make_stooge(choice));
	
	for(int i=0; i<roles.size(); i++)
	{
		roles[i]->slap_stick();
	}
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
