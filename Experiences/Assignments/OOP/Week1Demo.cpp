#include <iostream>
#include <string>

using namespace std;

struct Player
{
	string name;
	string type;
	int health;
	int power;
	
	void Initialize()
	{
		name = "P1";
		type = "warrior";
		health = 100;
		 power = 10;
	}
};

int main()
{
	//two struct items
	Player p1;
	Player p2;
	
	//! two item created
	p1.Initialize();
	p2.Initialize();
	
	cout << "Player 1" << endl;
	cout << "Name: " << p1.name << endl;
	cout << "Type: " << p1.type << endl;
	cout << "Health: " <<p1.health << endl;
	cout << "Power: " << p1.power << endl << endl;
	
	p2.health = 200;
	p2.power = 5;
	
	cout << "Player 2" << endl;
	cout << "Name: " << p2.name << endl;
	cout << "Type: " << p2.type << endl;
	cout << "Health: " <<p2.health << endl;
	cout << "Power: " << p2.power << endl << endl;
	
	cout << endl;
	system("PASUE");
	return 0;
}
