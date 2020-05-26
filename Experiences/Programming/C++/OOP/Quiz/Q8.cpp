/*
 +-------------+
 | Question  8 |
 +-------------+
 
Category of the question :
    Write a program

 Objective of the question :
    Write a program to prompt the user for an integer number and then 
    draw a diamond shape on the screen. The number input will 
    determine the length of each side of the diamond, as shown in 
    the following sample outputs.

 Correct Sample run 1:                   Correct Sample run 2:
    Enter an integer -> 6                   Enter an integer -> 3

         *                                    *
        ***                                  ***
       *****                                *****
      *******                                ***
     *********                                *
    ***********
     *********
      *******
       *****
        ***
         *

*********************************************************/

#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
	int a;
	int b;
	cout<< "Enter an integer -> ";
	int n;
	cin>> n;
	n = n*2;
	a = n/2 ;
	b = 0;

	
	for(int i=0; i< a ; i++) 
	{
		for (int j= i; j<a ; j++) 
		{
			cout<<" ";
		}
		for (int k=0; k<=i*2; k++) 
		{
			cout<<"*";
		}
		cout<<endl;
	}
	
	for(int i=1 ; i<= a ; i++)  
	{
		for (int j=0; j<=i-b; j++) 
		{
			cout<<" ";
		}
		for (int k= 1; k<= 2*(a-i+b)-1 ; k++) 
		{
			cout<<"*";
		}
		cout<<endl;
	}
	
	
    system ("pause");
    return 0;
}

