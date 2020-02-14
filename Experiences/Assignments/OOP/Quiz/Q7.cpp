/*
 
 +-------------+
 | Question  7 |
 +-------------+

 Category of the question :
    Write a program

 Objective of the question :
    You are to write a program that will accept 2 integer numbers
    from the user and then display out all the odd integer numbers in 
    between those two integers excluding the two numbers.

 Correct Sample run 1 :
    Input first number -> 5
    Input second number -> 15
    Output : 7 9 11 13

 Correct Sample run 2 :
    Input first number -> 27
    Input second number -> 12
    Output : 25 23 21 19 17 15 13

*********************************************************/
#include <iostream>

using namespace std;

int main()
{
	int usrInput, usrInput2;
	cout<< "Please enter 2 integer numbers: ";
	cin >> usrInput >> usrInput2;
	
	int oddNum, oddNum2;
	if( usrInput%2 != 0)
	{
		oddNum = usrInput;
	}
	else
	{
		oddNum = usrInput + 1;
	}
	
	if( usrInput2%2 != 0)
	{
		oddNum2 = usrInput2;
	}
	else
	{
		oddNum2 = usrInput2 + 1;
	}	
	
	if( oddNum > oddNum2 )
	{
		for(int i = oddNum-2 ; i >= oddNum2; i-=2)
		{
			cout << i << " ";
		}
	}	
	else if( oddNum < oddNum2 )
	{
		for(int i = oddNum+2 ; i < oddNum2; i+=2)
		{
			cout << i << " ";
		}
	}	
	
    return 0;
}

