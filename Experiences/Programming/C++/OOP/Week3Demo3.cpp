#include <iostream>
#include "windows.h"
#include <ctime>

using namespace std;

class Player{
private:
	string name;
	int score;
public:
	Player();
	Player(string n, int s);
	void Display();		
};

void Player::Display(){
	cout<<"Name: "<<name<<endl;
	cout<<"Score: "<<score<<endl;
}

Player::Player(){
	name = "";
	score = 0;
}

Player::Player(string n, int s){
	name = n;
	score = s;
}

int main(){
	srand(time(NULL));
	int randNum = rand()%100+1;
	int guessNum = 0;
	int counter = 0;
	bool isExit = false;
	int option = 0;
	
	Player* p;
	Player* playerList[5];
	string name;
	int number = 0;
		
	do{
		cout<<"Please Enter a Number (1-100): ";
		cin>> guessNum;
		counter++;
		if(guessNum > randNum){
			cout<<guessNum<<" more than random number."<<endl;
		}else if(guessNum < randNum){
			cout<<guessNum<<" less than random number."<<endl;
		}else if(guessNum == randNum){
			cout<<"Bingo."<<endl;
			cout<<"Please enter name: ";
			cin>>name;
			p = new Player(name, counter);
			//! store the player details to the player list
			if(number < 5){
				playerList[number] = p;
				number++;
				
				cout<<"1. Continue."<<endl;
				cout<<"2. Exit."<<endl;
				cin>>option;
				if(option==1){
					randNum = rand()% 100+1;
					counter = 0;
				}
				else if(option==2){
					isExit = true;				
				}
				
			}else{
				cout<<"Reach Max Player Number! Exiting..."<<endl;
				isExit = true;
			}
			

		}
		system("PAUSE");
		system("CLS");
	}while(!isExit);
	
	for(int i=0;i < 5; i++){
		playerList[i]->Display();
	}

	cout<<endl;
	system("PAUSE");
	return 0;
}
