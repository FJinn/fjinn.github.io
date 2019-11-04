#include "DefaultHeaderFiles.h"

Player::Player(string n, string g) :  GameObject(n)
{
	gender = g;
}

string Player::getGender()
{
	return gender;
}

void Player::displayGender()
{
	cout<<gender<<endl;
}
