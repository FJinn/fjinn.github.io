#include <iostream>
#include "Vehicle.h"
#include "Car.h"
#include "Bus.h"

using namespace std;

int main(int argc, char** argv) {
	
	Vehicle v1("AAA1234", "Blue");
	
	cout<<v1.Display()<<endl;
	
	Car* c1 = new Car("BBB4321", "Blue", "Company Type");
	cout<<c1->Display()<<endl;
	
	Bus* b1 =new Bus("BUS123", "Yellow", "Valid");
	cout<<b1->Display()<<endl;
	
	cout<<endl<<"Display from Vehicle Array"<<endl;
	Vehicle* vList[2];
	vList[0] = c1;
	vList[1] = b1;
	
	for(int i=0; i<2; i++)
	{
		cout<<vList[i]->Display()<<endl;
	}
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
