#include <iostream>
#include "windows.h"

using namespace std;

class Rectangles{
private: 
	int height;
	int width;
	
public:
	Rectangles(int h, int w){
		height = h;
		width = w ;
	}	
	void CalArea(){
		int area = height * width;	
		cout<<"Area: "<<area<<endl;	
	}
	void CalPerimeter();
};

void Rectangles:: CalPerimeter(){
	int perimeter = height * 2 + width * 2;
	cout<<"Perimeter: "<<perimeter<<endl;
}

int main(){
	
	Rectangles r1(5,4);
	r1.CalArea();
	cout<<endl;
	r1.CalPerimeter();
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
