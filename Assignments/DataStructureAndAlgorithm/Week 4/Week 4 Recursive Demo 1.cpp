#include <iostream>
#include "windows.h"

using namespace std;

void numberFunction(int i)
{
	cout<< "The number is: "<< i << endl;
	i++;
	if (i<10)
	{
		numberFunction(i);
	}
}

int main()
{	
	int i = 0;
	numberFunction(i);
	
	system("PAUSE");
	return 0;
}
