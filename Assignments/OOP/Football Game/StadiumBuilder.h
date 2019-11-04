#ifndef STADIUM_BUILDER_H
#define STADIUM_BUILDER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Stadium
{
	private:
		int width;
		int height;
		int audienceNumber;
		string ballName;
		int tempW = width/4;
		int tempH = height/4;
		
	public:
		string map[40][40];
		
		void SetWidth(int w)
		{
			width = w;
		}
		
		int getTempW()
		{
			return tempW;
		}
		
		int getMiddleY()
		{
			return height/2;
		}
		
		void SetHeight(int h)
		{
			height = h;
		}
		
		void SetAudienceNumber(int aN)
		{
			audienceNumber = aN;
		}
		
		void SetBallName(string name)
		{
			ballName = name;
		}
		
		void setUpStadium(int w, int x, int y, int z);
		void displayStadium();
};

void Stadium::setUpStadium(int w, int x, int y, int z)
{	
	tempW = width/4;
	tempH = height/4;

	for(int i=0; i<height; i++)
	{
		for(int j=0; j<width; j++)
		{
			if(w == 0 && x == 0 && y == 0 && z == 0)
			{
				if((j>=tempW-audienceNumber && j<= audienceNumber+tempW*3 )&& (i>=tempH-2 && i<=1+tempH*3))
				{
					map[i][j] = " . ";
				}
				else
				{
					map[i][j] = " A ";
				}
			}
			// offensive player
			else if(w == 1 && x == 3 && y == 3 && z == 4)
			{
				map[height/2][tempW-2] = "G1 ";
				
				map[(height/2)-2][tempW ] = "P1 ";
				map[height/2][tempW ] = "P2 ";
				map[(height/2)+2][tempW ] = "P3 ";
				
				map[(height/2)-2][tempW +2] = "P4 ";
				map[height/2][tempW +2] = "P5 ";
				map[(height/2)+2][tempW +2] = "P6 ";
				
				map[(height/2)-3][tempW +4] = "P7 ";
				map[(height/2)-1][tempW +4] = "P8 ";
				map[(height/2)+1][tempW +4] = "P9 ";
				map[(height/2)+3][tempW +4] = "P10";
				
				// enemy
				map[height/2][tempW*3 +2] = "G2 ";
				
				map[(height/2)-3][tempW*3 ] = "E1 ";
				map[(height/2)-1][tempW*3 ] = "E2 ";
				map[(height/2)+1][tempW*3 ] = "E3 ";
				map[(height/2)+3][tempW*3 ] = "E4 ";
				
				map[(height/2)-2][tempW*3 -2] = "E5 ";
				map[(height/2)+2][tempW*3 -2] = "E6 ";
				
				map[(height/2)-3][tempW*3 -4] = "E7 ";
				map[(height/2)-1][tempW*3 -4] = "E8 ";
				map[(height/2)+1][tempW*3 -4] = "E9 ";
				map[(height/2)+3][tempW*3 -4] = "E10";
			}
			// defensive player
			else if(w == 1 && x == 5 && y == 4 && z == 1)
			{
				map[height/2][tempW-2 ] = "G1 ";
				
				map[(height/2)-4][tempW ] = "P1 ";
				map[(height/2)-2][tempW ] = "P2 ";
				map[height/2][tempW] = "P3 ";
				map[(height/2)+2][tempW ] = "P4 ";
				map[(height/2)+4][tempW ] = "P5 ";
				
				map[(height/2)-3][tempW +2] = "P6 ";
				map[(height/2)-1][tempW +2] = "P7 ";
				map[(height/2)+1][tempW +2] = "P8 ";
				map[(height/2)+3][tempW +2] = "P9 ";
				
				map[(height/2)][tempW +4] = "P10";
				
				// enemy
				map[height/2][tempW*3 +2] = "G2 ";
				
				map[(height/2)-2][tempW*3 ] = "E1 ";
				map[height/2][tempW*3 ] = "E2 ";
				map[(height/2)+2][tempW*3 ] = "E3 ";
				
				map[(height/2)-2][tempW*3 -2] = "E4 ";
				map[height/2][tempW*3 -2] = "E5 ";
				map[(height/2)+2][tempW*3 -2] = "E6 ";
				
				map[(height/2)-3][tempW*3 -4] = "E7 ";
				map[(height/2)-1][tempW*3 -4] = "E8 ";
				map[(height/2)+1][tempW*3 -4] = "E9 ";
				map[(height/2)+3][tempW*3 -4] = "E10";
			}
			// balance player
			else if(w == 1 && x == 4 && y == 2 && z == 4)
			{
				map[height/2][tempW -2 ] = "G1 ";
				
				map[(height/2)-3][tempW ] = "P1 ";
				map[(height/2)-1][tempW ] = "P2 ";
				map[(height/2)+1][tempW ] = "P3 ";
				map[(height/2)+3][tempW ] = "P4 ";
				
				map[(height/2)-2][tempW +2] = "P5 ";
				map[(height/2)+2][tempW +2] = "P6 ";
				
				map[(height/2)-3][tempW +4] = "P7 ";
				map[(height/2)-1][tempW +4] = "P8 ";
				map[(height/2)+1][tempW +4] = "P9 ";
				map[(height/2)+3][tempW +4] = "P10 ";
				
				// enemy
				map[height/2][tempW*3 +2] = "G2 ";
				
				map[(height/2)-4][tempW*3 ] = "E1 ";
				map[(height/2)-2][tempW*3 ] = "E2 ";
				map[height/2][tempW*3 ] = "E3 ";
				map[(height/2)+2][tempW*3 ] = "E4 ";
				map[(height/2)+4][tempW*3 ] = "E5 ";
				
				map[(height/2)-3][tempW*3 -2] = "E6 ";
				map[(height/2)-1][tempW*3 -2] = "E7 ";
				map[(height/2)-1][tempW*3 -2] = "E8 ";
				map[(height/2)+3][tempW*3 -2] = "E9 ";
				
				map[(height/2)][tempW*3 -4] = "E10";
			}
		}
	}
}

void Stadium::displayStadium()
{
	for(int i=0; i<height; i++)
	{
		for(int j=0; j<width; j++)
		{
			cout<<map[i][j];
		}
		cout<<endl;
	}
}

class StadiumBuilder
{
	protected:
		Stadium* stadium;
		
	public:
		Stadium* GetStadium()
		{
			return stadium;
		}
		
		void CreateNewStadium()
		{
			stadium = new Stadium;
		}
		
		virtual void BuilderWidth() = 0;
		virtual void BuilderHeight() = 0;
		virtual void BuilderAudienceNumber() = 0;
		virtual void BuilderBallName() = 0;
};

class AStadium : public StadiumBuilder
{
	public:
		
		void BuilderWidth()
		{
			stadium->SetWidth(20);
		}
		
		void BuilderHeight()
		{
			stadium->SetHeight(12);
		}
		
		void BuilderAudienceNumber()
		{
			stadium->SetAudienceNumber(3);
		}
		
		void BuilderBallName()
		{
			stadium->SetBallName("ABall");
		}
		
};

class BStadium : public StadiumBuilder
{
	public:
		
		void BuilderWidth()
		{
			stadium->SetWidth(40);
		}
		
		void BuilderHeight()
		{
			stadium->SetHeight(20);
		}
		
		void BuilderAudienceNumber()
		{
			stadium->SetAudienceNumber(6);
		}
		
		void BuilderBallName()
		{
			stadium->SetBallName("BBall");
		}
		
};

class Director
{
	private:
		StadiumBuilder* stadiumBuilder;
		
	public:
		void SetStadiumBuilder(StadiumBuilder* sb)
		{
			stadiumBuilder = sb;
		}
		
		Stadium* GetStadiumBuilder()
		{
			return stadiumBuilder->GetStadium();
		}
		
		void BuildStadium()
		{
			stadiumBuilder->CreateNewStadium();
			stadiumBuilder->BuilderWidth();
			stadiumBuilder->BuilderHeight();
			stadiumBuilder->BuilderAudienceNumber();
			stadiumBuilder->BuilderBallName();
		}
};

#endif

