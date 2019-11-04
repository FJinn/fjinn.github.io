#include "Game.h"

#include <iostream>
#include "windows.h"

int main(int argc, char** argv) {
	
	Game game;
	bool isExit = false;
	game.stadiumCall();
	system("CLS");
	game.setUpStadium();
	game.displayStadium();
	game.teamStrategy();
	game.displayStrategy();
	game.initiatePlayer();

	int subChoice = 0;	
		
	do
	{	system("CLS");
		game.displayStadium();
		cout<<"1. Enter ball position."<<endl;
		cout<<"2. Exit."<<endl;
		cin>>subChoice;
			
		if(subChoice == 1)
		{
			int x;
			int y;
			cout<<endl<<"Please enter Ball x position(Column): ";
			cin>>x;
			cout<<endl<<"Please enter Ball y position(Row): ";
			cin>>y;
			game.setBall(x-1, y-1);
			cout<<endl;
			system("PAUSE");
			game.resetMap(x-1, y-1);
			system("CLS");
			subChoice = 0;
		}
		else if( subChoice ==2)
		{
			isExit = true;
		}

	}while(!isExit);
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
