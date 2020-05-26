#include <iostream>
#include "windows.h"
#include <ctime>

using namespace std;

class Rectangles
{
	private:
		int width;
		int height;
		
	public:
		Rectangles()
		{
		}
		
		Rectangles(int w, int h)
		{
			width = w;
			height = h;
		}
		
		int Area()
		{
			return width * height;
		}
		
		// return type
		friend Rectangles Duplicate(Rectangles& originalRectangles);
};

//! Rectangles::Rectangles Duplicate(Rectangles& originalRectangles)
Rectangles Duplicate(Rectangles& originalRectangles)
{
	Rectangles duplicateRect;
	duplicateRect.width = originalRectangles.width;
	duplicateRect.height = originalRectangles.height;
	return duplicateRect;
}

int main()
{
	Rectangles originalRect(2,3);
	cout<<originalRect.Area();
	
	Rectangles duplicate = Duplicate(originalRect);
	cout<<"Duplicate Rectangle: "<<duplicate.Area()<<endl;
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
