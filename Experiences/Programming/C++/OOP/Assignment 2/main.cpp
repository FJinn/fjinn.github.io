#include <iostream>
#include <ctime>
#include "windows.h"
#include "conio_yp.h"
#include <string>
#include "NPCDecorator.h"
#include "CombatInterface.h"
#include "FactoryInterface.h"

using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

const int mapRow = 37;
const int mapCol = 46;
char map[mapRow][mapCol];
bool isExit = false;
int startPosX = 7;
int startPosY = 10;
int mapOffsetX=4;
int mapOffsetY=3;
string password;

// enumeation -> enum : Let user to define custom type
/*enum TYPE
{
	WARRIOR = 0,
	ARCHER,
	MAGE,
	TOTAL
}; */

class Timer
{
	public:
	int initial;
	
	void start()
	{
		initial = clock();
	}
	
	double duration()
	{
		return (clock() - initial) / CLOCKS_PER_SEC;
	}
	
}timer;

class Hero
{
	public:
	char avatar = 'I'; //symbol
	int row = startPosX;
	int column = startPosY;	
	int rowOld;
	int columnOld;
	int health = 100;
	int sanity = 200;
	
	int vision;
	int strength;
	int defense;
	
	int fingers = 10;
	int legs = 2;
	
	struct tool
	{
		bool obtained = false;
		int status = 3;  // 3 times to use, 0 = broken 
	}rustedSaw;

};

Hero player;

#define RustedSaw 83
#define trap 63
#define lantern 42
#define scale 37
#define door 61
#define goal 33
#define hint 64
#define NPC 78
#define enemyA 219

void InitializeMap()
{
	char tempMap[mapRow][mapCol]= {
		{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','.','.','#','.',NPC,'#','.','.','.','.','.','.','#','.','#','.','.','G','#','.','.','.','.','.','.','.','.','.','#','.','#','.','.','.','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','.','.','#','.','.','#','.','#','.','.','#','.','#','.','.','#','.','.','#','.','.','.','.','.','.','.','#','.','.','.','.','.','#','.','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','.','.','#','.','.','#','.','#','.','.','#','.','#','.','.','.','#','.','.','.','#','#','#','.','#','#','#','#','#','#','#','#','#','.','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','.',trap,'#','.','.','#','.','#','.','#','.','.','#','.','.','#','.','#','.','.',trap,'#','.','.','.','.','.','.','.','#','.','.','.','.','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','.','.','#','.','.','#','.','#','.','.','#','.','#','.','.','#','.','.','.','#','.','#','#','.','.','.','.','.','.','.','#','.','#','#','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','.','#','#','.','.','#',lantern,'#','.','.','#','.','#','.','#','.','.','#','#','.','#','.','.','.','.','.','.','.','.','.','#','.','.','.','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','.','.','.','.','.','#','#','#','.','.','#','.','#','.','.','.','#','.','#','.','.','.','.','.','.','.','.','.','.','.','.','#','#','.','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','.','#','#','.','.','#','.','.','.','.','#','.','#','.','#','#','#','L','.','#','.','.','.','.','#','#','#','#','#','.','.','#','.','.','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','.','.','#','.','.','#','.',enemyA,'#','.','#','.','#','.','#','#','#','#','.','#','.','.','.','.','#','.','.','.','#','.','.','#','.','#','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','#','.','#','.','.','.','.','.','#','#','#','.','#','.','.','.','.','#','.','#','.','.','#','#','#','.',trap,'.','#','#','#','#','.','#','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','.','.','#','.','.','.','.','.','#','#','#','#','#','#','#','#','.','#','.','#','.','.','#','#','#','#','#','.','.','.','.','.','.','.','#','#','#','#','#','#'},
		{'$','.','.','.','.',door,'.','#','#','#','#','#','#','.','.','.','.','.',scale,'.','.','.','.','#','.','.','.','.','.','.','.','.','#','#','#','.','.','.','.','.','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','.','#','#','.','.','.','.','.','#','#','#','#','#','#','#','#','.','#','.','.','.','.','.','.','.','.','.','#',hint,'#','.','.','.','.','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','.','#','#','.','.','.','.','.','#','.','.','.','#','#','.','#','.','#','#','#','#','#','#','#','#','.','.','#',trap,'#','.','.','.','.','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','.','.',trap,'.','.','.','.','.','#','.','.','.','#','#','.','#','.','#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','.','#','#','.','.','.','.','.','.','.','.','.','#','.','.','#','.','#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','.','.','#','.','.','.','#','#','.','.','.','.','#','.','.','.','.','#','#','#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','#','.','#','#','#','.','#','#',trap,'.','.','.','#','.','#','#','#','E','.','.','.','.','.','.','.','.','.','G','.','&','.','T','.','.','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','.','.','.','.','.','.','#','#','.','.','.','.','#','.','#','.','#','#','#','.','#','.','.','.','.','.','.','.','.','.','.','.','.','.','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','.','#','#','#','#','.','#','#','.','#','.','.','#','.','#','.','.','.','.','.','#','.','.','.','.','.','.','.','.','.','.','.','.','.','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','.','.','.','.','#','.','.','.','.','#','.','.','#','.','#','.','#','#','#','.','#','.','#','#','#','#','.','.','.','.','.','.','.','.','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','#','#','#','.','#','.','#','.','.','#','#','#','#','.','.','.','.','.','.','#','.','.','#',trap,'.','#','.','.','.','.','.','#','#','#','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','.',RustedSaw,'#','.','#','.','.','.','.','.','.','.','#','.','#','.','.','.','#','.','#','.','.','.','#','.','.','.','#','.',trap,'.','.','.','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','.','.','.','.','#','.','#','.','.','#','#','.','#','.','.','#','#','#','#','.','#','.','#','.','.','#','.','.','.','.','#','.','.','.','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','.','.','.','.','.','.','#','.','.','#','.','.','#','.','.','.','.','S','.','#','.','.','#','.','.','.','.','.','.','.','#','.','.','.','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',door,'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','.','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','.','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','.','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','.','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
		{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',goal,'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}
		
	};
	for(int i=0; i<mapRow;i++)
	{
		for(int j=0; j<mapCol;j++)
		{
			map[i][j] = tempMap[i][j];
		}
	}
}

int visionrange = 3; // vision range
int initialvision = 1; // map display initial point

void ShowMap()
{	
	int a = player.row - initialvision;
	int b = player.column - initialvision;
	
	for(int i=a; i<a+visionrange;i++)
	{
		for(int j=b; j<b+visionrange;j++)
		{	
			gotoxy(mapOffsetX+j,mapOffsetY+i);
			
			if(map[i][j] == '#')
			{
				textcolor(YELLOW);
				cout<<map[i][j];
				textcolor(WHITE);
			}
			else
			{
				textcolor(WHITE);
				cout<<map[i][j];
				textcolor(WHITE);
			}
		}
		cout<<endl;
	}
	gotoxy(mapOffsetX + player.column, mapOffsetY + player.row);
	textcolor(LIGHTGREEN);
	cout<<player.avatar;
	textcolor(WHITE);
	
	// Player Info
	gotoxy(42,3);
	cout<<"Player Info";
	gotoxy(42,4);
	cout<<"============";
	gotoxy(42,5);
	cout<<"Health: "<<player.health;
	gotoxy(42,6);
	cout<<"Sanity Left: "<<player.sanity;
	gotoxy(42,7);
	cout<<"Fingers Left: "<<player.fingers;
	gotoxy(42,8);
	cout<<"Legs Left: "<<player.legs;
	
	gotoxy(mapOffsetX, mapOffsetY + mapRow + 1);
	system("PAUSE");
	system("CLS");
}


void Opening()
{
	
	cout<<"You wake up and find yourself in a shaddy room filled with unpleasant smell." << endl;
	cout<<"Suddenly, you hear a low pitch sound talking to you." << endl;
	
	textcolor(LIGHTRED);
	cout<< endl << "Good day." << endl << "How was your sleep?";
	cout<<"Silence? Great! This is the attitude." << endl;
	cout<<"In your life, you helped a stranger, behaved in a courteous manner." << endl;
	cout<<"But we both know, those are lies." << endl;
	cout<<"You've wearing a disgusting mask in your whole life." << endl << endl;
	cout<<"But fear not, I have prepare a lesson or rather, a game, for you, a chance to reborn as a true human." << endl;
	cout<<"At least, now you can remove the mask." << endl;
	cout<<"Lived as a hypocrite, and die as a human." << endl;
	cout<<"Or you learn the lesson and reborn." << endl;
	cout<<"The choice is in your hand." << endl;
	cout<<"You have 300s to finish the game, before a deadly gas is released in the room." << endl;
	cout<<"All the talks have finished." << endl;
	cout<<"Let's play the game." << endl << endl;
	
	textcolor(WHITE);
	textcolor(GREEN);
	
	cout<<"Bear in mind." << endl;
	cout<<"Clock is ticking with or without your perception."<< endl << endl;
	textcolor(WHITE);
	
	system("PAUSE");
	system("CLS");
}

void equipmentMenu()
{
	FactoryInterface* fI = new FactoryInterface();
	fI->loadList();
	int choice = 0;
	cout<<"Pick ur equipment."<<endl;
	system("PAUSE");
	system("CLS");
	fI->displayItem(1, 1);
	cout<<endl<<"Choose: ";
	cin>>choice;
	fI->chooseItem(choice);
	choice = 0;
	
	system("CLS");
	fI->displayCloth(1,1);
	cout<<endl<<"Choose: ";
	cin>>choice;
	fI->chooseCloth(choice);
	choice = 0;
	
	system("CLS");
	fI->displayTotem(1,1);
	cout<<endl<<"Choose: ";
	cin>>choice;
	fI->chooseTotem(choice);
	choice = 0;
	
	system("CLS");
	fI->displayPants(1,1);
	cout<<endl<<"Choose: ";
	cin>>choice;
	fI->choosePants(choice);
	choice = 0;
	
	system("CLS");
	fI->displayRing(1,1);
	cout<<endl<<"Choose: ";
	cin>>choice;
	fI->chooseRing(choice);
	choice = 0;
	
	system("CLS");
	fI->displayShoes(1,1);
	cout<<endl<<"Choose: ";
	cin>>choice;
	fI->chooseShoes(choice);
	choice = 0;
	
	system("CLS");
	gotoxy(1,1);
	cout<<"Your equipment: "<<endl;
	fI->displayEquipment(1,2);
	
	/*
	1. lighter
	2. cloth
	3. totem
	4. pants
	5. ring
	6. shoes	
	*/
	
	// vision
	player.vision = fI->getNum(1);
	initialvision += player.vision;
	visionrange += player.vision * 2;
	
	// strength -> attack
	player.strength = fI->getNum(3);
	
	// health
	player.health += 20* fI->getNum(5);
	
	// defend
	player.defense += fI->getNum(2) + fI->getNum(4) +fI->getNum(6);
	
	cout<<endl;
	system("PAUSE");
	system("CLS");
}

int point = 0;

void UpdateInput()
{
	// store the old position before input
	player.rowOld = player.row;
	player.columnOld = player.column;
	
	if(GetAsyncKeyState(VK_LEFT))
	{
		if(player.column>1)
		{
			player.column --;
			player.sanity -= point;
		}
	}
	else if(GetAsyncKeyState(VK_RIGHT))
	{
		if(player.column < mapCol-2)
		{
			player.column ++;
			player.sanity -= point;
		}
	}
	else if(GetAsyncKeyState(VK_UP))
	{
		if(player.row >1)
		{
			player.row--;
			player.sanity -= point;
		}
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		if(player.row < mapRow-2)
		{
			player.row++;
			player.sanity -= point;
		}
	}
}
/*
void ShowPlayerInfo()
{
	gotoxy(42,3);
	cout<<"Player Info";
	gotoxy(42,4);
	cout<<"============";
	gotoxy(42,5);
	cout<<"Health: "<<player.health;
	gotoxy(42,6);
	cout<<"Sanity Left: "<<player.sanity;
	gotoxy(42,7);
	cout<<"Fingers Left: "<<player.fingers;
	gotoxy(42,8);
	cout<<"Legs Left: "<<player.legs;
	
}
*/
void ShowTime()
{
	gotoxy(42, 23);
	cout << timer.duration() << "s has passed." << endl;	
}

bool Lantern = false;

void ExecuteLantern()
{
	if(player.rustedSaw.obtained)
	{
		if(player.rustedSaw.status != 0)
		{
			int num = 0;
			gotoxy(mapOffsetX, mapOffsetY+mapRow+8);
			cout << "How many fingers you want to cut off?";
			gotoxy(mapOffsetX, mapOffsetY+mapRow+9);
			cout << "Fingers left: " << player.fingers;
			gotoxy(mapOffsetX, mapOffsetY+mapRow+10);
			cin >> num;
			
			if(player.fingers >= num && player.fingers > 0)
			{
				player.rustedSaw.status--;
				player.fingers -= num;
				visionrange += num;
				initialvision += (num/2);
				point += (10-player.fingers);
			}
			else
			{
				gotoxy(mapOffsetX, mapOffsetY+mapRow+11);
				cout << "You do not have enough fingers or you are just too selfish to give and take.";
				gotoxy(mapOffsetX, mapOffsetY+mapRow+12);
				cout << "Perhaps legs?";
				gotoxy(mapOffsetX, mapOffsetY+mapRow+13);
				cout << "How many to be cut off?";
				gotoxy(mapOffsetX, mapOffsetY+mapRow+14);
				cout << "Legs left: " << player.legs;
				cin >> num;
				
				if(player.legs >= num && player.legs > 0)
				{
					player.rustedSaw.status--;
					player.legs -= num;
					num += 5;
					visionrange += num*2;
					initialvision += num;
					point += (4-player.legs);
				}
				else
				{
					gotoxy(mapOffsetX, mapOffsetY+mapRow+15);
					cout << "You do not have enough legs or you CHOOSE NOT to cut off ANYTHING.";
					player.row = player.rowOld;
					player.column = player.columnOld;
					Lantern = false;
				}
			}
		}
		else
		{
			gotoxy(mapOffsetX, mapOffsetY+mapRow+8);
			cout << "It is broken. The rusted saw cannot be used again.";
			player.row = player.rowOld;
			player.column = player.columnOld;
		}
	}
	else
	{
			gotoxy(mapOffsetX, mapOffsetY+mapRow+8);
			cout << "You cannot do anything.";
			Lantern = false;
	}
	
	if(player.fingers == 0 && player.legs == 0)
	{
		gotoxy(mapOffsetX, mapOffsetY+mapRow+8);
		cout << "You have nothing to offer.";
		Lantern = true;
	}
	
}



void LanternMenu()
{
	gotoxy(mapOffsetX, mapOffsetY+mapRow+1);
	cout<<"It looks like an old-fasion lantern, with a nasty smell comes from the fuel.";
	gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
	cout<<"Seems like it needs extra fuel to be fully lighted up.";
	gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
	cout<<"There is some words written in blood: Give your precious and take the vision.";
	gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
	cout<<"===========";
	gotoxy(mapOffsetX, mapOffsetY+mapRow+5);
	cout<<"1. Do as what the words say";
	gotoxy(mapOffsetX, mapOffsetY+mapRow+6);
	cout<<"2. Ignore";
	gotoxy(mapOffsetX, mapOffsetY+mapRow+7);
	cout<<"Your Choice ";
	int choice;
	cin>>choice;
	if(choice == 1)
	{
		ExecuteLantern();
	}
	else if(choice == 2)
	{
		player.row = player.rowOld;
		player.column = player.columnOld;
	}	
}
 
int numLegs = 0;

void ExecuteScale()
{
	if(player.rustedSaw.obtained)
	{
		if(player.rustedSaw.status != 0)
		{
			int num = 0;
			gotoxy(mapOffsetX, mapOffsetY+mapRow+8);
			cout << "How many fingers you want to cut off?";
			gotoxy(mapOffsetX, mapOffsetY+mapRow+9);
			cout << "Fingers left: " << player.fingers;
			gotoxy(mapOffsetX, mapOffsetY+mapRow+10);
			cin >> num;
			
			if(player.fingers >= num && player.fingers > 0)
			{
				player.rustedSaw.status--;
				gotoxy(mapOffsetX, mapOffsetY+mapRow+11);
				cout << "Nothing happens. Seems like there is not enough weight.";
				player.row = player.rowOld;
				player.column = player.columnOld;
				point += (10-player.fingers);
			}
			else
			{
				gotoxy(mapOffsetX, mapOffsetY+mapRow+11);
				cout << "You do not have enough fingers or you are just too selfish to give and take.";
				gotoxy(mapOffsetX, mapOffsetY+mapRow+12);
				cout << "Perhaps legs?";
				gotoxy(mapOffsetX, mapOffsetY+mapRow+13);
				cout << "How many to be cut off?";
				gotoxy(mapOffsetX, mapOffsetY+mapRow+14);
				cout << "Legs left: " << player.legs;
				cin >> num;
				
				if(player.legs >= num && player.legs > 0)
				{
					player.rustedSaw.status--;
					player.legs -= num;
					numLegs += num;
					if(numLegs < 2)
					{
						gotoxy(mapOffsetX, mapOffsetY+mapRow+15);
						cout << "Nothing happens. Seems like there is not enough weight.";
						player.row = player.rowOld;
						player.column = player.columnOld;
					}
					else
					{
						gotoxy(mapOffsetX, mapOffsetY+mapRow+15);
						cout << "The lock drops and the path is clear.";
					}
					point += (4-player.legs);
				}
				else
				{
					gotoxy(mapOffsetX, mapOffsetY+mapRow+14);
					cout << "You do not have enough legs or you CHOOSE NOT to cut off ANYTHING.";
					player.row = player.rowOld;
					player.column = player.columnOld;
				}
			}
		}
		else
		{
			gotoxy(mapOffsetX, mapOffsetY+mapRow+8);
			cout << "It is broken. The rusted saw cannot be used again.";
			player.row = player.rowOld;
			player.column = player.columnOld;
		}
	}
	
}
 
void ScaleMenu()
{
	gotoxy(mapOffsetX, mapOffsetY+mapRow+1);
	cout<<"It is locked.";
	gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
	cout<<"The lock system seems to connect to a scale right beside the lock.";
	gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
	cout<<"There is 2 words carved on the scale: Equivalent Exchange.";
	gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
	cout<<"===========";
	gotoxy(mapOffsetX, mapOffsetY+mapRow+5);
	cout<<"1. Do as what the words say";
	gotoxy(mapOffsetX, mapOffsetY+mapRow+6);
	cout<<"2. Ignore";
	gotoxy(mapOffsetX, mapOffsetY+mapRow+7);
	cout<<"Your Choice ";
	int choice;
	cin>>choice;
	if(choice == 1)
	{
		ExecuteScale();
	}
	else if(choice == 2)
	{
		player.row = player.rowOld;
		player.column = player.columnOld;
	}	
}

void RustedSawMenu()
{
	gotoxy(mapOffsetX, mapOffsetY+mapRow+1);
	cout<<"There lies a rusted saw.";
	gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
	cout<<"You doubt its functionality.";
	gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
	cout<<"Nonetheless, it may come in useful somewhere.";
	gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
	cout<<"===========";
	gotoxy(mapOffsetX, mapOffsetY+mapRow+5);
	cout<<"1. Take it.";
	gotoxy(mapOffsetX, mapOffsetY+mapRow+6);
	cout<<"2. Leave it";
	gotoxy(mapOffsetX, mapOffsetY+mapRow+7);
	cout<<"Your Choice ";
	int choice;
	cin>>choice;
	if(choice == 1)
	{
		player.rustedSaw.obtained = true;
	}
}

void PasswordMenu()
{
	gotoxy(mapOffsetX, mapOffsetY+mapRow+1);
	cout<<"There is a password lock";
	gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
	cout<<"Please enter ONLY the correct password: ";	
	getline(cin, password);
	
	if(password != "HOPE AND LIFE")
	{
		gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
		cout << "A punishment or rather consequence for the WRONG password.";
		player.health -= player.health/2;
		player.row = player.rowOld;
		player.column = player.columnOld;
	}
}

bool metNPC1 = false;

void NPCMenu()
{
	metNPC1 = true;
	HarmfulNPC* npc1 = new HarmfulNPC(new Decorator(new DeadNPC()));
	npc1->effect();
	int temp = npc1->getHpCount();
	gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
	cout<<npc1->getDesc();
	gotoxy(mapOffsetX, mapOffsetY+mapRow+6);
	cout << "Your sanity is affected by "<< temp<<".";
	player.sanity -= temp;
}

void CombatMenuA()
{
	system("CLS");
	CombatInterface* cs = new CombatInterface();
	cs->getPlayerHealth(player.health);
	cs->getPlayerStat(player.defense, player.strength);
	cs->combatMenu(1,1);
	player.health = cs->playerHealth;
	system("CLS");
}

void CollisionDetection()
{
	if(map[player.row][player.column] == (char)enemyA)
	{
		CombatMenuA();
	}
	if(map[player.row][player.column] == (char)NPC && metNPC1 == false)
	{
		NPCMenu();
	}
	if(map[player.row][player.column] == '#')
	{
		player.row = player.rowOld;
		player.column = player.columnOld;
	}
	if(map[player.row][player.column] == (char)lantern && Lantern == false)
	{
		LanternMenu();
	}
	if(map[player.row][player.column] == (char)scale && numLegs != 2)
	{
		ScaleMenu();
	}
	if(map[player.row][player.column] == (char)RustedSaw && player.rustedSaw.obtained == false)
	{
		RustedSawMenu();
	}
	if(map[player.row][player.column] == (char)trap)
	{
		player.health--;
		gotoxy(mapOffsetX, mapOffsetY+mapRow+1);
		cout << "It is a trap!";
		system("PAUSE");
	}
	if(map[player.row][player.column] == (char)hint)
	{
		gotoxy(mapOffsetX, mapOffsetY+mapRow+1);
		cout << "EFIL";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
		cout << "EPOH";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
		cout << "Learn the lesson.";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
		cout << "CONNECT THE LINK.";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+5);
		cout << "You shall see the truth behind the mirror.";
	}
	if(map[player.row][player.column] == (char)door && password != "HOPE AND LIFE" )
	{
		PasswordMenu();
	}
	if(map[player.row][player.column] == (char)goal)
	{
		gotoxy(mapOffsetX, mapOffsetY+mapRow+1);
		cout << "Congratulations.";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
		cout << "A lesson is given. So is the chance.";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
		cout << "You learned the lesson.";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
		cout << "Enjoy your second life.";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+5);
		cout << "Keep the lesson in mind as there will not be another chance.";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+6);
		system("PAUSE");
		system("CLS");
		gotoxy(40,30);
		cout << "YOU SURVIVED" << endl << endl;
		system("PAUSE");
		isExit = true;
	}	
	if(map[player.row][player.column] == '$')
	{
		gotoxy(mapOffsetX, mapOffsetY+mapRow+1);
		cout << "You just can't learn the lesson. Can you?";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
		cout << "A lesson is given. So is the chance.";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
		cout << "You failed to learn.";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
		system("PAUSE");
		system("CLS");
		gotoxy(40,30);
		cout << "YOU DIED" << endl << endl;
		system("PAUSE");
		isExit = true;
	}	
}

void ShowPlayerAvatar()
{	
		textcolor(BLUE);
		gotoxy(55,6);
		cout<<"  * ";
		gotoxy(55,7);
		cout<<"	|  O";
		gotoxy(55,8);
		cout<<"  | /|\\";
		gotoxy(55,9);
		cout<<"  |  |";
		gotoxy(55,10);
		cout<<"  | / \\";
		textcolor(WHITE);
}

void ConditionCheck()
{
	if(player.health <= 0)
	{
		gotoxy(mapOffsetX, mapOffsetY+mapRow+1);
		cout << "You just can't learn the lesson. Can you?";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
		cout << "A lesson is given. So is the chance.";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
		cout << "You failed to learn.";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
		system("PAUSE");
		system("CLS");
		gotoxy(40,30);
		cout << "YOU DIED" << endl << endl;
		system("PAUSE");
		isExit = true;
	}
	
	if(player.sanity <= 0)
	{
		gotoxy(mapOffsetX, mapOffsetY+mapRow+1);
		cout << "You just can't learn the lesson. Can you?";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
		cout << "A lesson is given. So is the chance.";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
		cout << "You failed to learn.";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
		system("PAUSE");
		system("CLS");
		gotoxy(40,30);
		cout << "YOU DIED" << endl << endl;
		system("PAUSE");
		isExit = true;
	}
	
	if(timer.duration() >= 300)
	{
		gotoxy(mapOffsetX, mapOffsetY+mapRow+1);
		cout << "You just can't learn the lesson. Can you?";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+2);
		cout << "A lesson is given. So is the chance.";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+3);
		cout << "You failed to learn.";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+4);
		cout << "The room is filled up with highly toxic gas.";
		gotoxy(mapOffsetX, mapOffsetY+mapRow+5);
		system("PAUSE");
		system("CLS");
		gotoxy(40,30);
		cout << "YOU DIED" << endl << endl;
		system("PAUSE");
		isExit = true;
	}
}

int main(int argc, char** argv) {
	// game window size
	system("mode con: cols=100 lines=80");
	textcolor(WHITE);
	srand(time(NULL));
	InitializeMap();
	Opening();
//	CombatMenuA();
	equipmentMenu();
	system("CLS");
	timer.start();
	
	do
	{
		ShowTime();
//		ShowPlayerInfo();
		UpdateInput();
		CollisionDetection();
//		ShowPlayerAvatar();
		ShowMap();
		ConditionCheck();

	}while(!isExit);
	return 0;
}
