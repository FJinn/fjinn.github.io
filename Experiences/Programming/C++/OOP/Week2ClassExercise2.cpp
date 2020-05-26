/*
	Hero Class
	-> type
	-> health
	-> damage
	
	Hero Method
	-> constructor (3 paarameters)
	-> Display()
	-> set and get method
	
	Monster Class
	-> health
	-> damage
	
	Monster Method
	-> constructor (2 parameters)
	-> Display()
	-> set and get method
	
	int main()
	-> create 1 hero objective, 1 monster object
	-> create battle simulation
	->turn base -> either one's health == 0 -> stop the gameplay
	
*/

#include <iostream>
#include <string>
#include "windows.h"

using namespace std;

bool onBattle;

class Hero{
private:
	string type;
	int health;
	int damage;
	
public:	
	Hero(string t, int h, int d){
		type = t;
		health = h;
		damage = d;
	}	
	
	// destructor
	~Hero(){
		
	}
	
	//! set -> update the private attribute/property
	void setHealth(int h){
		health -= h;
	}
	void setDamage(int d){
		damage = d;
	}

	
	//! get -> retrieve the updated value from private attribute/property
	int getHealth(){
		return health;
	}
	int getDamage(){
		return damage;
	}
	
	void Display(){
		cout<<"Hero type: "<<type<<endl;
		cout<<"Hero health: "<<health<<endl;
		cout<<"Hero damage: "<<damage<<endl;
	}
	
};

class Monster{
private:
	int health;
	int damage;
	
public:	
	Monster(int h, int d){
		health = h;
		damage = d;
	}	
	
	// destructor
	~Monster(){
		
	}
	
	//! set -> update the private attribute/property
	void setHealth(int h){
		health -= h;
	}
	void setDamage(int d){
		damage = d;
	}

	
	//! get -> retrieve the updated value from private attribute/property
	int getHealth(){
		return health;
	}
	int getDamage(){
		return damage;
	}
	
	void Disaplay(){
		cout<<"Monster health: "<<health<<endl;
		cout<<"Monster damage: "<<damage<<endl;
	}
	
};

int main(){
	
	Hero h1("Warrior",100 , 10);
	Monster m1(100, 5);
	
	cout<<"Hero Stat"<<endl;
	h1.Display();
	cout<<"================"<<endl;
	cout<<"Monster Stat"<<endl;
	m1.Disaplay();
	
	cout<<"================"<<endl;
	cout<<"Battle Start"<<endl;
	cout<<"================"<<endl;
	
	onBattle = true;
	
	int i = 0;
	
	do{
		i++;
		cout<<endl<<"Turn "<<i<<endl;
		cout<<"================"<<endl;
		if(h1.getHealth() > 0){
			cout<<"Hero's attack turn."<<endl;
			cout<<"Hero deal "<<h1.getDamage()<<" damage to monster."<<endl<<endl;
			m1.setHealth(h1.getDamage());
			cout<<"Monster's remaining health: "<<m1.getHealth()<<endl;
		}
		if(m1.getHealth() > 0){
			cout<<"================"<<endl;
			cout<<"Monster's attack turn."<<endl;
			cout<<"Monster deal "<<m1.getDamage()<<" damage to hero."<<endl<<endl;
			h1.setHealth(m1.getDamage());
			cout<<"Hero's remaining health: "<<h1.getHealth()<<endl;	
		}
		
		if(h1.getHealth() > m1.getHealth()){
			cout<<"Hero wins!"<<endl;
		}else if(m1.getHealth() > h1.getHealth()){
			cout<<"Monster wins!"<<endl;
		}
			
		if(h1.getHealth() <= 0 || m1.getHealth() <= 0)
		{
			onBattle = false;
		}
		
	}while(onBattle);
	
	cout<<endl;
	system("PAUSE");
	return 0;
}

