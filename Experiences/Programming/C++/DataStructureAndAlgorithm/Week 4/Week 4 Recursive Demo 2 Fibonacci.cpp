/*
Fibonacci
0,1,1,2,3,5,8,13,21,34,55,89,144, ...

First n = First n -1  +  First n -2
*/

#include <iostream>
#include "windows.h"
#include <vector>

using namespace std;


int Fibonacci(int x)
{
	if ( x == 0)
	{
		return 0;
	}
	if (x == 1)
	{
		return 1;
	}
	return Fibonacci(x-1) + Fibonacci (x-2);
	
}

int main()
{	
	vector<int> fibonacciList;
	int n, i =0;
	cout<< "Input the number of term for Fibonacci Series: ";
	cin>> n;
	cout<< endl<< "Fibonacci Series is as follow: "<< endl;
	//!    0  n=5
	while (i<n)
	{
		cout<< Fibonacci(i)<< " ";
		i++;
	}
	cout<< endl;
	
	system("PAUSE");
	return 0;
}


