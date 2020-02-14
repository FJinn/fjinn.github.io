#include <iostream>
#include <ctime>
#include "Hero.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	
	bool isExit = false;
	srand(time(NULL));
	int num = 0;
//	num = rand()%10+11;
	Hero h1(100,1,10);
//	num = rand()%10+11;
	Hero h2(100,1,10);
	
	cout<<"Battle Simulation"<<endl;
	do{
		num = rand()% 10+11;
		h1.SetDamage(num);
		num = rand()% 10+11;
		h2.SetDamage(num);
			
		if(h1.GetHealth()>0 && h2.GetHealth()>0){
			cout<<"Hero 1 attacks Hero 2"<<endl;
			h1.Attack(h2);
			cout<<"Hero 1: "<<h1.GetHealth()<<endl;
			cout<<"Hero 2: "<<h2.GetHealth()<<endl;
			cout<<"---------------------"<<endl;
			cout<<"Hero 2 attacks Hero 1"<<endl;
			h2.Attack(h1);
			cout<<"Hero 1: "<<h1.GetHealth()<<endl;
			cout<<"Hero 2: "<<h2.GetHealth()<<endl;
		}
		else{
			if(h1.GetHealth()>h2.GetHealth()){
				cout<<"Hero 1, WIN!"<<endl;
			}
			else{
				cout<<"Hero 2, WIN!"<<endl;
			}
			isExit = true;
		}
		
	}
	while(!isExit);
	
	cout<<endl;
	system("PAUSE");	
	return 0;
}
