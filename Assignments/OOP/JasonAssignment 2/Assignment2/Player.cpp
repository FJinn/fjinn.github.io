#include "DefaultHeaderFiles.h"

using namespace std;

Player::Player(string g)
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
