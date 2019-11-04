#ifndef GAME_H
#define GAME_H

#include "StadiumBuilder.h"
#include "Player.h"
#include "Ball.h"
#include "Team.h"

#include <iostream>

using namespace std;

class Game
{
	public:
		// stadium
		Director director;
		BStadium bStadium;
		AStadium aStadium;
		Stadium* stadium_ptr;
		
		void stadiumCall()
		{
			int choice =0;
			cout<<"Stadium Name"<<endl;
			cout<<"1. A Stadium"<<endl;
			cout<<"2. B Stadium"<<endl;
			cout<<"Choice: ";
			cin>>choice;
			if(choice ==1)
			{
				aStadium.CreateNewStadium();
				director.SetStadiumBuilder(& aStadium);
				director.BuildStadium();
				cout<<"A Stadium!"<<endl;
			}
			else if(choice ==2)
			{
				director.SetStadiumBuilder(& bStadium);
				director.BuildStadium();
				cout<<"B Stadium!"<<endl;
			}
			
			stadium_ptr = director.GetStadiumBuilder();
		}
		
		// Team
		FormationStrategy* formationStrategy = new FormationStrategy();
		FormationStrategy* NPCStrategy= new FormationStrategy();
		
		Team* t1 = new Team(formationStrategy);
		Team* t2 = new Team(NPCStrategy);
		bool hasTeam = false;
		
		void teamStrategy()
		{
			int choice =0;
			cout<<"Pick your team strategy:"<<endl;
			cout<<"1. Offensive"<<endl;
			cout<<"2. Defensive"<<endl;
			cout<<"3. Balance"<<endl;
			cout<<"Choice: ";
			cin>>choice;
			if(choice == 1)
			{
				formationStrategy->setBehaviour(new Offensive());
				NPCStrategy->setBehaviour(new Balance());
			}
			else if(choice == 2)
			{
				formationStrategy->setBehaviour(new Defensive());
				NPCStrategy->setBehaviour(new Offensive());
			}
			else if(choice == 3)
			{
				formationStrategy->setBehaviour(new Balance());
				NPCStrategy->setBehaviour(new Defensive());
			}
			hasTeam = true;
		}
		
		void displayStrategy()
		{
			cout<<"Your team formation: "<<t1->Formation()<<endl;
			cout<<"The formation is: "<<t1->Description()<<endl;
			cout<<"Opposite team formation: "<<t2->Formation()<<endl;
			cout<<"The formation is: "<<t2->Description()<<endl;
		}
		
		// Ball
		FootballState state;
		
		// Player & Referee
//		Referee* referee = new Referee();
		void initiatePlayer()
		{
			//Striker players
			Player* p1 = new Striker(new Decorator(new StartingLineUp()));
			p1->addName("S1");
			Player* p2 = new Striker(new Decorator(new StartingLineUp()));
			p2->addName("S2");
			Player* p3 = new Striker(new Decorator(new StartingLineUp()));
			p3->addName("S3");
			Player* p4 = new Striker(new Decorator(new StartingLineUp()));
			p4->addName("S4");
			Player* p5 = new Striker(new Decorator(new StartingLineUp()));
			p5->addName("S5");
			Player* p6 = new Striker(new Decorator(new StartingLineUp()));
			p6->addName("S6");
			Player* p7 = new Striker(new Decorator(new StartingLineUp()));
			p7->addName("S7");
			Player* p8 = new Striker(new Decorator(new StartingLineUp()));
			p8->addName("S8");
			Player* p9 = new Striker(new Decorator(new StartingLineUp()));
			p9->addName("S9");
			Player* p10 = new Striker(new Decorator(new StartingLineUp()));
			p10->addName("S10");
			
			//MidField Player
			Player* p11 = new MidField(new Decorator(new StartingLineUp()));
			p11->addName("M1");
			Player* p12 = new MidField(new Decorator(new StartingLineUp()));
			p12->addName("M2");
			Player* p13 = new MidField(new Decorator(new StartingLineUp()));
			p13->addName("M3");
			Player* p14 = new MidField(new Decorator(new StartingLineUp()));
			p14->addName("M4");
			Player* p15 = new MidField(new Decorator(new StartingLineUp()));
			p15->addName("M5");
			Player* p16 = new MidField(new Decorator(new StartingLineUp()));
			p16->addName("M6");
			Player* p17 = new MidField(new Decorator(new StartingLineUp()));
			p17->addName("M7");
			Player* p18 = new MidField(new Decorator(new StartingLineUp()));
			p18->addName("M8");
			Player* p19 = new MidField(new Decorator(new StartingLineUp()));
			p19->addName("M9");
			Player* p20 = new MidField(new Decorator(new StartingLineUp()));
			p20->addName("M10");
			
			//Defender Player
			Player* p21 = new Defender(new Decorator(new StartingLineUp()));
			p21->addName("D1");
			Player* p22 = new Defender(new Decorator(new StartingLineUp()));
			p22->addName("D2");
			Player* p23 = new Defender(new Decorator(new StartingLineUp()));
			p23->addName("D3");
			Player* p24 = new Defender(new Decorator(new StartingLineUp()));
			p24->addName("D4");
			Player* p25 = new Defender(new Decorator(new StartingLineUp()));
			p25->addName("D5");
			Player* p26 = new Defender(new Decorator(new StartingLineUp()));
			p26->addName("D6");
			Player* p27 = new Defender(new Decorator(new StartingLineUp()));
			p27->addName("D7");
			Player* p28 = new Defender(new Decorator(new StartingLineUp()));
			p28->addName("D8");
			Player* p29 = new Defender(new Decorator(new StartingLineUp()));
			p29->addName("D9");
			Player* p30 = new Defender(new Decorator(new StartingLineUp()));
			p30->addName("D10");
			
			//GoalKeeper Player
			Player* p31 = new GoalKeeper(new Decorator(new StartingLineUp()));
			p31->addName("G1");
			Player* p32 = new GoalKeeper(new Decorator(new StartingLineUp()));
			p32->addName("G2");
			Player* p33 = new GoalKeeper(new Decorator(new StartingLineUp()));
			p33->addName("G3");
			
			int tempW = stadium_ptr->getTempW();
			int tempH = stadium_ptr->getMiddleY();
			// striker
			if(t1->StrikerNum() == 1)
			{
				p1->setPosition(tempW + 4, tempH);
				t1->AddPlayer(p1);
				state.Attach(p1);
			}
			else if(t1->StrikerNum() == 4)
			{
				p2->setPosition(tempW+4, tempH-3);
				t1->AddPlayer(p2);
				state.Attach(p2);
				p3->setPosition(tempW+4, tempH-1);
				t1->AddPlayer(p3);
				state.Attach(p3);
				p4->setPosition(tempW+4, tempH+1);
				t1->AddPlayer(p4);
				state.Attach(p4);
				p5->setPosition(tempW+4, tempH+3);
				t1->AddPlayer(p5);
				state.Attach(p5);	
			}
			
			if(t2->StrikerNum() == 1)
			{
				p6->setPosition(tempW*3 -4 , tempH);
				t2->AddPlayer(p6);
				state.Attach(p6);	
			}
			else if(t2->StrikerNum() == 4)
			{
				p7->setPosition(tempW*3 -4, tempH-3);
				t2->AddPlayer(p7);
				state.Attach(p7);	
				p8->setPosition(tempW*3 -4, tempH-1);
				t2->AddPlayer(p8);
				state.Attach(p8);	
				p9->setPosition(tempW*3 -4, tempH+1);
				t2->AddPlayer(p9);
				state.Attach(p9);	
				p10->setPosition(tempW*3 -4, tempH+3);
				t2->AddPlayer(p10);	
				state.Attach(p10);	
			}
			
			//midfield
			if(t1->MidNum() == 2)
			{
				p11->setPosition(tempW+2, tempH-2);
				t1->AddPlayer(p11);
				state.Attach(p11);	
				p12->setPosition(tempW+2, tempH+2);
				t1->AddPlayer(p12);
				state.Attach(p12);	
			}
			else if(t1->MidNum() == 3)
			{
				p11->setPosition(tempW+2, tempH-2);
				t1->AddPlayer(p11);
				state.Attach(p11);	
				p12->setPosition(tempW+2, tempH);
				t1->AddPlayer(p12);
				state.Attach(p12);	
				p13->setPosition(tempW+2, tempH+2);
				t1->AddPlayer(p13);
				state.Attach(p13);	
			}
			else if(t1->MidNum() == 4)
			{
				p11->setPosition(tempW+2, tempH-3);
				t1->AddPlayer(p11);
				state.Attach(p11);	
				p12->setPosition(tempW+2, tempH-1);
				t1->AddPlayer(p12);
				state.Attach(p12);	
				p13->setPosition(tempW+2, tempH+1);
				t1->AddPlayer(p13);
				state.Attach(p13);	
				p14->setPosition(tempW+2, tempH+3);
				t1->AddPlayer(p14);
				state.Attach(p14);	
			}
			
			if(t2->MidNum() == 2)
			{
				p16->setPosition(tempW*3 -2, tempH-1);
				t2->AddPlayer(p16);
				state.Attach(p16);
				p17->setPosition(tempW*3 -2, tempH+1);
				t2->AddPlayer(p17);
				state.Attach(p17);
			}
			else if(t2->MidNum() == 3)
			{
				p16->setPosition(tempW*3 -2, tempH-2);
				t2->AddPlayer(p16);
				state.Attach(p16);
				p17->setPosition(tempW*3 -2, tempH);
				t2->AddPlayer(p17);
				state.Attach(p17);
				p18->setPosition(tempW*3 -2, tempH+2);
				t2->AddPlayer(p18);
				state.Attach(p18);
			}
			else if(t2->MidNum() == 4)
			{
				p16->setPosition(tempW*3 -2, tempH-3);
				t2->AddPlayer(p16);
				state.Attach(p16);
				p17->setPosition(tempW*3 -2, tempH-1);
				t2->AddPlayer(p17);
				state.Attach(p17);
				p18->setPosition(tempW*3 -2, tempH+1);
				t2->AddPlayer(p18);
				state.Attach(p18);
				p19->setPosition(tempW*3 -2, tempH+3);
				t2->AddPlayer(p19);
				state.Attach(p19);
			}
			
			//defender
			if(t1->DefenderNum() == 3)
			{
				p21->setPosition(tempW  , tempH-2);
				t1->AddPlayer(p21);
				state.Attach(p21);
				p22->setPosition(tempW  , tempH);
				t1->AddPlayer(p22);
				state.Attach(p22);
				p23->setPosition(tempW  , tempH+2);
				t1->AddPlayer(p23);
				state.Attach(p23);
			}
			else if(t1->DefenderNum() == 4)
			{
				p21->setPosition(tempW  , tempH-3);
				t1->AddPlayer(p21);
				state.Attach(p21);
				p22->setPosition(tempW  , tempH-1);
				t1->AddPlayer(p22);
				state.Attach(p22);
				p23->setPosition(tempW  , tempH+1);
				t1->AddPlayer(p23);
				state.Attach(p23);
				p24->setPosition(tempW  , tempH+3);
				t1->AddPlayer(p24);
				state.Attach(p24);
			}
			else if(t1->DefenderNum() == 5)
			{
				p21->setPosition(tempW , tempH-4);
				t1->AddPlayer(p21);
				state.Attach(p21);
				p22->setPosition(tempW , tempH-2);
				t1->AddPlayer(p22);
				state.Attach(p22);
				p23->setPosition(tempW , tempH);
				t1->AddPlayer(p23);
				state.Attach(p23);
				p24->setPosition(tempW , tempH+2);
				t1->AddPlayer(p24);
				state.Attach(p24);
				p25->setPosition(tempW , tempH+4);
				t1->AddPlayer(p25);
				state.Attach(p25);
			}
			
			if(t2->DefenderNum() == 3)
			{
				p26->setPosition(tempW*3 , tempH-2);
				t2->AddPlayer(p26);
				state.Attach(p26);
				p27->setPosition(tempW*3 , tempH);
				t2->AddPlayer(p27);
				state.Attach(p27);
				p28->setPosition(tempW*3 , tempH-2);
				t2->AddPlayer(p28);
				state.Attach(p28);
			}
			else if(t2->DefenderNum() == 4)
			{
				p26->setPosition(tempW*3 , tempH-3);
				t2->AddPlayer(p26);
				state.Attach(p26);
				p27->setPosition(tempW*3 , tempH-1);
				t2->AddPlayer(p27);
				state.Attach(p27);
				p28->setPosition(tempW*3 , tempH+1);
				t2->AddPlayer(p28);
				state.Attach(p28);
				p29->setPosition(tempW*3 , tempH+3);
				t2->AddPlayer(p29);
				state.Attach(p29);
			}
			else if(t2->DefenderNum() == 5)
			{
				p26->setPosition(tempW*3 , tempH-4);
				t2->AddPlayer(p26);
				state.Attach(p26);
				p27->setPosition(tempW*3 , tempH-2);
				t2->AddPlayer(p27);
				state.Attach(p27);
				p28->setPosition(tempW*3 , tempH);
				t2->AddPlayer(p28);
				state.Attach(p28);
				p29->setPosition(tempW*3 , tempH+2);
				t2->AddPlayer(p29);
				state.Attach(p29);
				p30->setPosition(tempW*3 , tempH+4);
				t2->AddPlayer(p30);
				state.Attach(p30);
			}
			
			p31->setPosition(tempW-2, tempH);
			t1->AddPlayer(p31);
			state.Attach(p31);
			p32->setPosition(tempW*3+2, tempH);
			t2->AddPlayer(p32);
			state.Attach(p32);
			
			// update stadium/map
			setUpStadium();
		
			for(vector<Player*>::const_iterator iter = t1->playerList.begin(); iter != t1->playerList.end(); ++iter)
			{
				if(*iter != 0)
				{
					cout<<"Name: "<<(*iter)->getName()<<endl;
					cout<<(*iter)->getDetails()<<endl;
					cout<<"Position(Row) : "<<(*iter)->getPositionY()+1<<endl;
					cout<<"Position(Column): "<<(*iter)->getPositionX()+1<<endl;
					cout<<"Position representative on map (stadium): "<<stadium_ptr->map[(*iter)->getPositionY()][(*iter)->getPositionX()]<<endl;
				}
			}
			
		//	cout<<endl<<"Referee is: "<< referee->getName()<<endl<<endl;
			displayStadium();
		}
		
		// Ball
		void updatePosition(int x, int y, Stadium* stadium)
		{
			state.updateBallPosition(x, y, stadium);
		}
		
		void setBall(int x, int y)
		{
			stadium_ptr->map[y][x] = " B ";
			cout<<endl;
			displayStadium();
			updatePosition(x, y, stadium_ptr);
		}
		void resetMap(int x, int y)
		{
			stadium_ptr->map[y][x] = " . ";
		}
		
		
		// set up stadium
		void setUpStadium()
		{
			if(!hasTeam)
			{
				stadium_ptr->setUpStadium(0,0,0,0);
			}
			else
			{
				stadium_ptr->setUpStadium(1, t1->DefenderNum(), t1->MidNum(), t1->StrikerNum());
			}
		}
		
		void displayStadium()
		{
			stadium_ptr->displayStadium();
		}
		
};

#endif
