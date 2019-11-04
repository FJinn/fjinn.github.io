#include <iostream>
#include "windows.h"
#include "HeroFactory.h"

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	
	int choice = -1;
	cout<<"Warrior = 1, Archer = 2, Mage = 3"<<endl;
	cin>>choice;
	HeroFactory* hero = HeroFactory::CreateHero(choice);
	hero->PrintStatus();
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
