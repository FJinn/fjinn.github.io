#include <iostream>

using namespace std;

//! super class/ base class / parent class
class Polygon
{
	protected:
		int height;
		int width;
		
	public:
		void SetDimension(int w, int h)
		{
			height = h;
			width = w;
		}
};
// subclass / child class
class Rectangles : public Polygon
{	
	public:
		Rectangles()
		{}
		int GetArea()
		{
			return height*width;
		}	
};

class Triangles : public Polygon
{
	public:
		Triangles()
		{}
		int GetArea()
		{
			return (height*width)/2;
		}
};

int main()
{
	Rectangles rect;
	Triangles tri;
	rect.SetDimension(4,5);
	tri.SetDimension(4,5);
	
	cout<<"Rectangle area: "<<rect.GetArea()<<endl;
	cout<<"Triangle area: "<<tri.GetArea()<<endl;
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
