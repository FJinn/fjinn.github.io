#include <iostream>
#include "windows.h"
#include <ctime>

using namespace std;

class RandomNumberGenerator
{
	public:
		const int VALUE_MAX = 1337;
		int value;
		
		RandomNumberGenerator()
		{
		}
		
		void SetValue(int value)
		{
			this->value = value;
		}
		
		inline void SetValueInline(int value)
		{
			this->value = value;
		}
};

int main()
{
	srand(time(NULL));
	RandomNumberGenerator randNum;
	
	clock_t begin;
	clock_t end;
	double elapsedSecs;
	
	begin = clock();
	for(int i=0; i<10000000; i++)
	{
		randNum.SetValue(7777);
	}
	end = clock();
	// timing for this execution
	elapsedSecs = double (end - begin)/CLOCKS_PER_SEC;
	cout<<"Set Value: "<<elapsedSecs<<" "<<CLOCKS_PER_SEC<< endl;
	
	cout<<endl<<endl;
	
	cout<<"With Inline"<<endl;
	begin = clock();
	for(int i=0; i<10000000; i++)
	{
		randNum.SetValueInline(7777);
	}
	end = clock();
	// timing for this execution
	elapsedSecs = double (end - begin)/CLOCKS_PER_SEC;
	cout<<"Set Value: "<<elapsedSecs<<" "<<CLOCKS_PER_SEC<< endl;

	cout<<endl;
	system("PAUSE");
	return 0;
}
