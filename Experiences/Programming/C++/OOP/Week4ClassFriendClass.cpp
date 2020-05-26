#include <iostream>
#include "windows.h"
#include <ctime>

using namespace std;

// class header without class body
class Square;

class Rectangles
{
	private:
		int height;
		int width;
		
	public:
		Rectangles()
		{
		}	
		
		Rectangles(int h, int w)
		{
			height = h;
			width = w;
		}
		
		int Area()
		{
			return width * height;
		}
		
		void Convert (Square square);
};

class Square
{
	friend class Rectangles;
	
	private:
		int side;
	public:
		Square(int value)
		{
			side = value;
		} 
};

void Rectangles::Convert(Square square)
{
	width = square.side;
	height = square.side;
}

int main()
{
	Square s1(4);
	Rectangles rect;
	rect.Convert(s1);
	cout<<"Rectangle Area: "<<rect.Area()<<endl;
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
