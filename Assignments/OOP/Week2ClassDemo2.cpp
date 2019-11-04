#include <iostream>
#include <string>
#include "windows.h"

using namespace std;

class Player{
public:
	string type;
	int health;
	
	//! special method for object creation -> constructor
	//! constructor name == class name, no return type
	Player(string t, int h){
		type = t;
		health = h;
	}	
	
	Player(int h){
		type = "Human";
		health = h;		
	}
	
	// destructor
	~Player(){
		
	}
	
	void Disaplay(){
		cout<<"Player type: "<<type<<endl;
		cout<<"Player health: "<<health<<endl;
	}
	
};

int main(){

	Player p1("Warrior", 150);
	Player p2(100);
	
	cout<<"Player 1"<<endl;
	p1.Disaplay();
	cout<<"Player 2"<<endl;
	p2.Disaplay();
	
	cout<<endl;
	system("PAUSE");
	return 0;
}

