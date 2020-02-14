#include <iostream>
#include <ctime>
#include "windows.h"

using namespace std;

class RandomNumberGenerator
{
public:
		const int VALUE_MAX = 10;
		int value;
		
		RandomNumberGenerator()
		{
			value = rand();
			if(value>VALUE_MAX)
			{
				value = VALUE_MAX;
			}
			cout<<value<<endl;
		}
};

int main()
{
	srand(time(NULL));
	RandomNumberGenerator randGen;
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
