#include "AllHeaderFiles.h"

using namespace std;

int enemySpawnTimer = 0;

void DrawBoundary()
{
	textcolor(WHITE);
	for(int i=BOUNDARY_LEFT; i<=BOUNDARY_RIGHT;i++)
	{
		gotoxy(i, BOUNDARY_TOP);
		cout<<(char)205;
		gotoxy(i, BOUNDARY_BOTTOM);
		cout<<(char)205;
	}
	
	// vertical
	for(int i=BOUNDARY_TOP +1; i<=BOUNDARY_BOTTOM;i++)
	{
		gotoxy(BOUNDARY_LEFT, i);
		cout<<(char)186;
		gotoxy(BOUNDARY_RIGHT, i);
		cout<<(char)186;
	}
	
	gotoxy(BOUNDARY_RIGHT, BOUNDARY_TOP);
	cout<<(char)187;
	gotoxy(BOUNDARY_LEFT, BOUNDARY_TOP);
	cout<<(char)201;
	gotoxy(BOUNDARY_RIGHT, BOUNDARY_BOTTOM);
	cout<<(char)188;
	gotoxy(BOUNDARY_LEFT, BOUNDARY_BOTTOM);
	cout<<(char)200;
}

void DrawHUD(Player &player)
{
	textcolor(WHITE);
	gotoxy(BOUNDARY_LEFT, BOUNDARY_BOTTOM + 2);
	cout<<"Health : " <<player.health << " ";
	if(player.health >= 80 )
	{
		textcolor(GREEN);
	}
	else if (player.health < 80 && player.health >= 40)
	{
		textcolor(YELLOW);
	}
	else if(player.health < 40 )
	{
		textcolor(RED);
	}
	
	int num = 10;
	
	if(player.health%10 == 0)
	{
		num = (player.health/10);
	}
	
	for(int i=0; i<10; i++)
	{
		if(i< num)
		{
			cout<<(char)219;
		}
		else
		{
			cout<<" ";
		}
	}
	
	textcolor(WHITE);
	gotoxy(BOUNDARY_LEFT, BOUNDARY_BOTTOM + 3);
	cout<<"Score : " <<player.score<< "           Life: " << player.life;
}
// x, y-> position  height , width -> size of the sprite
bool RectangleIntersect(int obj1_x, int obj1_y, int obj1_height, int obj1_width, 
						int obj2_x, int obj2_y, int obj2_height, int obj2_width)
{
	if(obj1_x > obj2_x + obj2_width || 
	   obj1_x + obj1_width < obj2_x ||
	   obj1_y > obj2_y + obj2_height ||
	   obj1_y + obj1_height < obj2_y )
	{
		return false;	
	}
	return true;
}

void EnemyOverLappingCheck(Enemy& enemy, vector<Enemy> &enemyList)
{
	bool isOverLapping;
	do
	{
		isOverLapping = false;
	
		if(enemy.enemyType == ENEMY03 || enemy.enemyType == ENEMY04)
		{
			enemy.x = rand()%(BOUNDARY_RIGHT - BOUNDARY_LEFT-enemy.column) + BOUNDARY_LEFT + 1;
			enemy.y = BOUNDARY_TOP + rand()%10 +enemy.row ;
		}
		else
		{
			enemy.x = rand()%(BOUNDARY_RIGHT - BOUNDARY_LEFT-enemy.column)+ BOUNDARY_LEFT + 1;
			enemy.y = -1 * rand()%10;
		}
		
		for(int i=0; i<enemyList.size(); i++)
		{
			if(RectangleIntersect(enemy.x, enemy.y, enemy.row, enemy.column,
		                      enemyList[i].x, enemyList[i].y, enemyList[i].row, enemyList[i].column))
			{
				isOverLapping = true;  
				break;                 	
			}
		}
		
	}while(isOverLapping);
}

void SpawnEnemy(vector<Enemy>& enemyList)
{
	enemySpawnTimer++;
	if(enemyList.size() <= MAX_ENEMY)
	{
		if(enemySpawnTimer>ENEMY_SPAWN_DURATION)
		{
			int numberOfEnemyToSpawn = rand()%MAX_ENEMY;
			
			for(int i=0; i<numberOfEnemyToSpawn; i++)
			{
				int randEnemyType = rand()%TOTAL_ENEMY_TYPE;
				
				Enemy newEnemy((ENEMY_TYPE)randEnemyType);
				
				//! randomly assign the spawn location for the enemy ( randomly set x and y)
				//                         55       -    5        -     3    =53   +    5     + 1  = 59
				/*	
				newEnemy.x = rand()%(BOUNDARY_RIGHT - BOUNDARY_LEFT-newEnemy.column)+ BOUNDARY_LEFT + 1;
				newEnemy.y = -1 * rand()%10;
				*/
				EnemyOverLappingCheck(newEnemy, enemyList);
				enemyList.push_back(newEnemy);
			}
			enemySpawnTimer = 0;
		}
	}
}

void SpawnItem(vector<Item>& itemList, Enemy& enemy)
{
	if(itemList.size() <= 3)
	{
		int randItemType = rand()%TOTAL_ITEM_TYPE;
			
		Item newItem((ITEM_TYPE)randItemType);
				
				//! randomly assign the spawn location for the enemy ( randomly set x and y)
				//                         55       -    5        -     3    =53   +    5     + 1  = 59
				/*	
				newEnemy.x = rand()%(BOUNDARY_RIGHT - BOUNDARY_LEFT-newEnemy.column)+ BOUNDARY_LEFT + 1;
				newEnemy.y = -1 * rand()%10;
				*/
		newItem.x = enemy.x;
		newItem.y = enemy.y;
		itemList.push_back(newItem);
	}
}

void CollisionCheck(Player &player, vector<Enemy> &enemyList, vector<Item>& itemList)
{
	// player vs enemy
	for(int i=0; i<enemyList.size(); i++)
	{
		if(RectangleIntersect(player.x, player.y, player.row, player.column,
		                      enemyList[i].x, enemyList[i].y, enemyList[i].row, enemyList[i].column) && enemyList[i].isAlive)
		{
			player.health--;
			player.score += enemyList[i].killScore;
			enemyList[i].isAlive = false;    
			enemyList[i].DrawTrail();                  	
		}
	}
	
	// bullet vs enemy
	for(int i=0; i<enemyList.size(); i++)
	{
		for(int j=0; j<player.bulletList.size(); j++)
		{
			if(RectangleIntersect(player.bulletList[j].x, player.bulletList[j].y, player.bulletList[j].row, player.bulletList[j].column,
		                      enemyList[i].x, enemyList[i].y, enemyList[i].row, enemyList[i].column) && enemyList[i].isAlive)
			{
				player.score += enemyList[i].killScore;    
				enemyList[i].DrawTrail();
				SpawnItem(itemList, enemyList[i]);
				enemyList[i].isAlive = false;
				player.bulletList[j].DrawTrail();                  	
			}
		}
	}
	
	// bullet vs player
	for(int i=0; i<enemyList.size(); i++)
	{
		for(int j=0; j<enemyList[i].bulletList.size(); j++)
		{
			if(RectangleIntersect(player.x, player.y, player.row, player.column,
		                      enemyList[i].bulletList[j].x, enemyList[i].bulletList[j].y, enemyList[i].bulletList[j].row, enemyList[i].bulletList[j].column) && enemyList[i].isAlive)
			{
				player.health--;
				enemyList[i].bulletList[j].DrawTrail();                  	
			}
		}
	}
	
	// item vs enemy
	for(int i=0; i<enemyList.size(); i++)
	{
		for(int j=0; j<itemList.size(); j++)
		{
			if(RectangleIntersect(itemList[j].x, itemList[j].y, itemList[j].row, itemList[j].column,
		                      enemyList[i].x, enemyList[i].y, enemyList[i].row, enemyList[i].column) && enemyList[i].isAlive)
			{  
				itemList[j].DrawTrail();   
				itemList[j].isAlive = false;               	
			}
		}
	}	
	
	// item vs player
	for(int i=0; i<itemList.size(); i++)
	{
		if(RectangleIntersect(itemList[i].x, itemList[i].y, itemList[i].row, itemList[i].column,
	                  		  player.x, player.y, player.row, player.column) && itemList[i].isAlive)
		{  
			if(itemList[i].itemType == HEALTH_PACK)
			{
				player.health += 10;
			}
			else
			{
				player.type = itemList[i].bulletType;
				player.shootDelayDuration += itemList[i].shootDelayDuration;
			}
			
			itemList[i].DrawTrail();   
			itemList[i].isAlive = false;               	
		}
	}
}

int main(int argc, char** argv) {
	
	system("mode con: cols=58 lines=44");
		
	int num;
	cout<<"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"<<endl;
	cout<<"                     ALIEN INVASION                   "<<endl;
	cout<<"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
	
	cout<<"              Arrow Key to move."<<endl;
	cout<<"              Space Key to shoot."<<endl;
	cout<<"              Esc Key to quit."<<endl;
	
	cout<<endl<<endl<<endl<<endl<<endl<<endl<<"1. Play."<<endl;
	cout<<"Your choice: ";
	cin >> num;
	system("CLS");
	
	srand(time(NULL));
	DrawBoundary();
	hideCursor();
	char button;
	
	Player player;
	player.type = STRAIGHT;
	vector<Enemy> enemyList;
	vector<Item> itemList;

	
	if(num == 1)
	{
		do
		{
			if(player.life > 0)
			{
				player.Update();
				player.Draw();
				
				// enemy update
				// enemy draw
				for(int i=0; i<enemyList.size(); i++)
				{
					enemyList[i].Update();
					enemyList[i].enableShooting = true;
					
					if(enemyList[i].isAlive == false)
					{
						Enemy enemyA = enemyList[i];
						vector<Enemy> temp;
						if(enemyList[i].bulletList.size() == 0)
						{
							for(int j=enemyList.size()-1; j>-1; j--)
							{
								if(j != i)
								{	
									temp.push_back(enemyList.back());
								}
								enemyList.pop_back();
							}
							enemyList = temp;
							i = 0;	
						}
		//				enemyList.erase(enemyList.begin() + i);
					}
					else
					{
						enemyList[i].Draw();
					}
					// print out variable to check
				//	gotoxy(BOUNDARY_LEFT, BOUNDARY_BOTTOM + 4);
			//		cout<<enemyList.size();
		//			gotoxy(BOUNDARY_LEFT, BOUNDARY_BOTTOM + 4 +i);
	//				cout<<" " <<itemList.size();
				}
		
				CollisionCheck(player, enemyList, itemList);
				
				for(int k=0; k<itemList.size(); k++)
				{
					if(itemList[k].isAlive == false)
					{
						Item item = itemList[k];
						vector<Item> temp;
						for(int l=itemList.size()-1; l>-1; l--)
						{
							if(l != k)
							{	
								temp.push_back(itemList.back());
							}
							itemList.pop_back();
						}
						itemList = temp;
						k = 0;	
					}
					else
					{
						itemList[k].Draw();
					}
				}
				
				// creating enemy
				SpawnEnemy(enemyList);
				DrawHUD(player);
			}
			else
			{
				gotoxy(BOUNDARY_LEFT + 10, BOUNDARY_BOTTOM + 4 );
				cout << "YOU HAVE NO LIFE LEFT!";
				gotoxy(BOUNDARY_LEFT + 10, BOUNDARY_BOTTOM + 5 );
				cout << "YOU LOSE!!";
				button = 27;
			}
			
			
			if(GetAsyncKeyState(VK_ESCAPE))
			{
				button = 27;
			}
			
			Sleep(20);
		}while(button != 27);
	}
	else
	{
		cout<<"EXITING!"<<endl;
	}	
	
	cout<<endl;
	gotoxy(1, BOUNDARY_BOTTOM+2);
	system("PAUSE");
	return 0;
}
