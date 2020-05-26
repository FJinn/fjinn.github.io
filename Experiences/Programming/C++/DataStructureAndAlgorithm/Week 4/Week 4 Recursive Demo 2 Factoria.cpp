#include <iostream>
#include "windows.h"

using namespace std;
//! function header declaration
int factorial(int n);

int main()
{	
	int n;
	cout << "Enter a positive integer: ";
	cin>> n;
	cout << "Factorial of "<< n << " = "<< factorial(n)<< endl;

	system("PAUSE");
	return 0;
}

int factorial(int n)
{	//! 3
	if(n>1)
	{	//!3				3-1=2
		//!2				2-1=1
		//!1				
		return n* factorial(n-1);
	}
	else
	{
		return 1;
	}
}
