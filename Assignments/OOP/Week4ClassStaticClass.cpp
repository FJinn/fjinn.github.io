#include <iostream>
#include <ctime>
#include "windows.h"

using namespace std;

static class Counter
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
} counter; // declaring a static instance of the class

static Counter counter2;

// Must do global initialization for ALL STATIC variable outside the class to allocate heap memory
int Counter::count = 0;

int main()
{	
	Counter::DisplayCount();
	cout<<&counter<<endl;
	
	Counter c1;
	Counter::DisplayCount();
	cout<<&c1<<endl;
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
