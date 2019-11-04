#include <string>
#include <iostream>
#include "windows.h"

#include "Player.h"
#include "Team.h"
#include "Stadium.h"

using namespace std;

int main(int argc, char** argv) {
	
	bool isExit = false;
	Player* tempPlayer = NULL;
	Team* team[2];
	Stadium* stadium;
	
	do
	{
		int option = 0;
		cout<<"1. Team Creation"<<endl;
		cout<<"2. Display Team"<<endl;
		cout<<"3. Stadium Selection"<<endl;
		cout<<"4. Display Game Detail"<<endl;
		cout<<"5. Start Game"<<endl;
		cout<<"99. Exit"<<endl;
		cin>>option;
		string role = "";
		int num =0;
		
		if(option == 1)
		{
			for(int i=0; i<2; i++)
			{
				string tName="";
				cout<<"Enter Team Name: ";
				cin>>tName;
				team[i] = new Team(tName);
				cout<<"Player Selection: "<<endl;
				for(int j=0; j<2; j++)
				{
					cout<<"Please enter Player Number: ";
					cin>>num;
					cout<<"Please select role: Defender, Attacker, MidField, GoalKeeper, Substitute"<<endl;
					cin>>role;
					
					tempPlayer = new Player(num, role);
					team[i]->AddPlayer(tempPlayer);
				}
			}
		}
		else if(option == 2)
		{
			for(int i=0; i<2;i++)
			{
				team[i]->DisplayTeam();
			}
		}
		else if(option == 3)
		{
			int selection = 0;
			cout<<"1. Stadium Melawati"<<endl;
			cout<<"2. Stadium Bukit Jalil"<<endl;
			cin>>selection;
			if(selection == 1)
			{
				stadium = new Stadium("Stadium Melawati");
			}
			else if(selection == 2)
			{
				stadium = new Stadium("Stadium Bukit Jalil");
			}
			
			for(int i=0; i<2; i++)
			{
				stadium->teams[i] = team[i];
			}
		}
		else if(option == 4)
		{
			stadium->DisplayName();
		}
		else if(option == 5)
		{
			
		}
		else if(option == 99)
		{
			isExit = true;
		}
		
		system("PAUSE");
		system("CLS");
	}while(!isExit);
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
