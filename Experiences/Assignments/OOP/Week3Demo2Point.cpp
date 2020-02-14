#include <iostream>
#include <cmath>
#include <string>
#include "windows.h"

using namespace std;

class Point{
private: 
	float x;
	float y;
	
public:
	
	Point(float x, float y){
		this->x = x;
		this->y = y;
	}
	
	float distanceFromOrigin(Point p);
	void Display();
};

float Point::distanceFromOrigin(Point p){
	return sqrt(pow(p.x - x ,2)+pow(p.y - y,2));
	
}

void Point::Display(){
	cout<<"Point x: "<<x<<", Point y: "<<y<<endl;
}

int main(){
	
	Point p1(3,5);
	Point p2(8,9);
	
	float distance = p1.distanceFromOrigin(p2);
	p1.Display();
	cout<<endl;
	p2.Display();
	cout<<endl;	
	cout<<"Distance for two points is: "<<distance<<endl;

	cout<<endl;
	system("PAUSE");
	return 0;
}
