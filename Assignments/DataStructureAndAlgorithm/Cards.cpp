#include <iostream>
#include "windows.h"
#include <queue>
#include <cstdlib>
#include <ctime>

using namespace std;

queue < int > myCards;
queue < int > nmyCards;
queue < int > newQ;
queue < int > newQ2;
queue < int > currenth;
queue < int > currenth2;
int input;

struct card
{
	// 4 different type of suits
	string suit[4] { "Spade", "Heart", "Club", "Diamond" };
	int face;
	
} cardArray[52];  //cardArray[4][13];

struct deck
{
	void Fill()
	{
	int a = 0;
	while ( a < 13 ) 
	{
		
		for (int j=0; j<13; j++) // put in suits
		{
			for(int i=0; i<4; i++)
			{
				cardArray[j].suit[i];
				
			}
		}

		for (int s = 0; s < 52; s++) // put in numbers
		{
			if (s % 4 == 0)
			{
				a++;
			}
			cardArray[s].face = a ;
		//	cout << cardArray[s].face << endl;
		}
	}
	}	
	void shuffle() //shuffle
	{
		srand(time(NULL));
		for (int n = 0; n < 52; n++) 
		{
		int p = rand() % 52;
		int tempC;
		cardArray[tempC] = cardArray[n];
		cardArray[n] = cardArray[p];
		cardArray[p] = cardArray[tempC];
		}	
	}
	
	void display( queue <int> C1, queue <int> C2)  //display
	{
		while ( C1.size() > 0 )
		{
			cout << "P1: " << C1.front() << " "<< endl ;
		//	cout << "P2: " << C2.front() << " " << endl;
			C1.pop(); 
		//	C2.pop();
		}
		
		
		while ( C2.size() > 0 )
		{
			
			cout << "P2: " << C2.front() << " " << endl;
		
			C2.pop();
		}
		

		
	}
	
}pdeck;
/*
queue <int> test;
queue <int> test2;
queue <int> test3;
queue <int> test4;
bool isSame = false;
*/
struct player  // deal card to player 1 and 2
{

	void deal()
	{
		for(int de1=0; de1<5; de1++)
		{
			myCards.push(cardArray[de1]);
//			test.push(cardArray[de1].face);
//			test2.push(cardArray[de1].face);
		}
		for (int de2=5; de2<10; de2++)
		{
			nmyCards.push(cardArray[de2]);
//			test3.push(cardArray[de2].face);
//			test4.push(cardArray[de2].face);	
		}
	}
}game;
/*
void compare(queue <int> &x, queue <int> &y, queue <int> &o) // trying to compare by pop the queue, but this method needs too much extra queues to check all element in a queue
{
			while (y.size() != 0 )
			{
				while(x.size() != 0 )
				{
					x.pop();
					if( y.front() == x.front())
					{	
						isSame = true;
						break;	
					}
				}
				if( y.front() == o.front())
					{	
						isSame = true;
						break;	
					}	
				y.pop();			
			}
}
*/
struct cardM  //card management, keep track of the card
{
	void choose ()
	{
		cout << "Current player , please choose your card to play: " << endl;
		cin >> input;  // cin.go can solve the problem which the player enters other than the list, but spent too much time on solving compare(), so no time for this
/*		while (myCards.size() != 0)
		{
			if (myCards.front() != input)
			{
				if (myCards.size() == 0)
				{
					cout<< " Please Enter a number listed." << endl;
					cin>> input;
				}
				myCards.pop();	
			}
			else
			{
				cin>> input;
			}
			
		
		}
			*/
	}
	
	void rcard(queue <int> &x, queue <int> &y, queue <int> &z) // not yet done XXXX same number problem 
	{
		int inisize = x.size();
		if ( x.size() == inisize)  // so this only run when the size of x queue is the previous hand card amount
		{
				while (x.size() > 0 && z.size() == 0 )
			{				
					if (x.front() != input)
					{
						y.push(x.front());
						x.pop();
					}
					else
					{
						x.pop();
					}
			}
		}
		
		while (x.size() == 0 && y.size() != 0) // set card to currenth from new Q
		{
				z.push(y.front());
				y.pop();
		}
		while (z.size() != 0 && y.size() == 0) // set card back to myCards from currenth
		{
				x.push(z.front());
				z.pop();

		}
	}


}p1,p2;

int main()
{
	int result = 0;
	int result2 = 0;
	pdeck.Fill();
	pdeck.shuffle();
	game.deal();
/*	compare(test, test2, myCards);
	compare(test3, test4, nmyCards);	
	while(isSame == true)
	{
		while (myCards.size() != 0)
		{
			myCards.pop();
		}
		while (nmyCards.size() != 0)
		{
			nmyCards.pop();
		}	
		pdeck.shuffle();
		game.deal();
		compare(test, test2, myCards);
		compare(test3, test4, nmyCards);
	}
*/
	pdeck.display(myCards, nmyCards);
	for (int cardr = 5; cardr > 0 ; cardr--)
	{
		p1.choose();
		p1.rcard(myCards, newQ, currenth);
		int p1s = input; // to hold the input
		p2.choose();
		p2.rcard(nmyCards, newQ2, currenth2);
		int p2s = input;
		
		if (p1s > p2s)
		{
			result++;
			cout << "First player wins this round" << endl;
		}
		else if (p1s < p2s)
		{
			result2++;
			cout << "Second player wins this round" << endl;
		}
		else if (p1s == p2s)
		{
			cout << "TIE" << endl;
		}
		
		pdeck.display(myCards, nmyCards);	
	}
	if (result > result2)
	{
		cout<< "First player won with "<< result << " scores" << endl;
	}
	else 
	{
		cout<< "Second player won with "<< result2 << " scores" << endl;
	}


	system("PAUSE");
	return 0;
}
