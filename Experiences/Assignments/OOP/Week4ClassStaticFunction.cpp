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
		
		static void DisplayCount()
		{
			cout<<count<<" "<<&count<<endl;
		}
		
		Counter()
		{
			count++;
		}
		
		~Counter()
		{
			count--;
		}
};

// Must do global initialization for ALL STATIC variable outside the class to allocate heap memory
int Counter::count = 0;

int main()
{
	Counter::DisplayCount();
	
	Counter c1;
	c1.DisplayCount();
	
	Counter c2;
	c2.DisplayCount();
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
