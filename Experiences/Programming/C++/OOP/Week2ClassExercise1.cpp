/*
class name -> Enemy

class Property/attribute ==> 4

class implementation/methods ==> 3

in main methods
	-> display enemy stat
	-> able to update the attribute by calling the class method

*/

#include <iostream>
#include <string>
#include "windows.h"

using namespace std;

class Enemy{
	
public:
	int experience;
	int level;
	int attackPower;
	int health;

	void displayStat(){
		cout<<"Enemy Experience: "<<experience<<endl;
		cout<<"Enemy Level: "<<level<<endl;
		cout<<"Enemy Attack Power: "<<attackPower<<endl;
		cout<<"Enemy Health: "<<health<<endl;
	}
	
	void updateHealth(int h){
		if(h>100){
			health = 100;
		}else{
			health = h;		
		}
	}
	
	void updateLevel(){
		if(experience>10){
			level++;
			experience -= 10;
		}
	}
	
};

int main(){
	
	Enemy e1;
	e1.health = 100;
	e1.attackPower = 10;
	e1.level = 1;
	e1.experience = 0;
	
	e1.displayStat();
	
	cout<<endl<<endl;
	cout<<"Update"<<endl;
	cout<<"==========="<<endl;
	
	e1.updateHealth(200);
	e1.experience = 12;
	e1.updateLevel();
	
	e1.displayStat();

	
	cout<<endl;
	system("PAUSE");
	return 0;
}
