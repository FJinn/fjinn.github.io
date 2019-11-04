#include <iostream>
#include <ctime>
#include "windows.h"

using namespace std;

class Counter
{
	public: 
		// Declaring static variable
		static int count;
		int value;
		
		Counter()
		{
			count++;
			value = rand();
		}
		
		~Counter()
		{
			count--;
		}
};

// Must do global initialization for ALL STATIC variable outside the class to allocate heap memory
int Counter::count = 0;

int main()
{	// Counter c;
	// c.count
	srand(time(NULL));
	cout<<"Counter::count -> "<<&Counter::count<<endl;
	
	Counter counter;
	cout<<"counter.count -> "<<counter.count<<"  "<<&counter.count;
	cout<<"  counter.value -> "<<counter.value<<"  "<<&counter.value<<endl;
	
	Counter counter2;
	cout<<"counter2.count -> "<<counter2.count<<"  "<<&counter2.count;
	cout<<"  counter2.value -> "<<counter2.value<<"  "<<&counter2.value<<endl;
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
