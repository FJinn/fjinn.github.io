#include <iostream>
#include "windows.h"
#include <string>
#include <typeinfo>

using namespace std;

class GeometricObject
{
	protected:
		string color;
	public:
		GeometricObject(string c)
		{
			color = c;
		}
		
		string getColor()
		{
			return color;
		}
		
		virtual void CalArea() = 0;
		
		virtual void CalPerimeter() = 0;
		
};

class Rectangles: public GeometricObject
{
	private:
		int height;
		int width;
	public:
		Rectangles(string c, int h, int w) : GeometricObject(c)
		{
			height =h;
			width = w;
		}
		
		void CalArea()
		{
			cout<<"Area: "<<height*width<<endl;
		}
		
		void CalPerimeter()
		{
			cout<<"Perimeter: "<<(height*2)+(width*2)<<endl;
		}
		
};

class Circles: public GeometricObject
{
	private:
		double radius;
	public:
		Circles(string c, int r) : GeometricObject(c)
		{
			radius = r;
		}
		
		void CalArea()
		{
			cout<<"Area: "<<3.142*(radius*radius)<<endl;
		}
		
		void CalPerimeter()
		{
			cout<<"Perimeter: "<<2*radius*3.142<<endl;
		}
};

int main()
{
	Rectangles* r1 = new Rectangles("Yellow", 5, 7);
	Circles* c1 = new Circles ("Blue", 5);
	
	cout<<"Rectangle" <<endl;
	cout<<"Color: "<<r1->getColor()<<endl;
	r1->CalArea();
	r1->CalPerimeter();
	cout<<endl;
	
	cout<<"Circle"<<endl;
	cout<<"Color: "<<c1->getColor()<<endl;
	c1->CalArea();
	c1->CalPerimeter();
	cout<<endl;
	
	GeometricObject* objectList[2];
	objectList[0] = r1;
	objectList[1] = c1;
	
	
	for(int i=0; i<2; i++)
	{
		if(typeid(*r1) == typeid(*objectList[i]))
		{
			cout<<"Rectangle"<<endl;
		}
		else if (typeid(*c1) == typeid(*objectList[i]))
		{
			cout<<"Circle"<<endl;
		}
		
		cout<<"Color: "<<objectList[i]->getColor()<<endl;
		objectList[i]->CalArea();
		objectList[i]->CalPerimeter();
		cout<<endl;
		
	}
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
