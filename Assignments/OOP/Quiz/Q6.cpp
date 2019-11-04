/*
 +-------------+
 | Question  6 |
 +-------------+

 Category of the question :
    Correct logical errors

 Objective of the question :
    After the user entered a list of 5 numbers, the program will find 
    the smallest number in the list and displayed the index and the 
    value of the smallest number.

    However, there are some logical errors in the program and the 
    program does not produced the desired output.

    What you need to do is to find the errors and correct them so
    that the desired output can be displayed as shown in the
    sample run.

 Correct Sample run 1:
    List elements: 2 43 8 89 50
    Location of smallest element is: 1
    Smallest element in list is:     2

 Correct Sample run 2:
    List elements: 56 34 23 10 30
    Location of smallest element is: 4
    Smallest element in list is:     10
    
*********************************************************/

#include <iostream>
using namespace std;

const int arraySize = 5;
void printArray(const int x[],int sizeX);
int smallestIndex(const int x[],int sizeX);

int main()
{
	int list[arraySize];
	
	cout << "Enter 5 numbers: ";
	for (int i = 0; i < arraySize; i++)
	   cin >> list[i];    
	  
	cout<<"\nList elements: ";					
	printArray(list,arraySize);					
	cout<<endl;										
	
	int index = smallestIndex(list,arraySize);
	cout<<"Location of smallest element is: "
		<< index + 1	<< endl;											
	cout<<"Smallest element in list is:     "
		<< list[index]<< endl << endl;									

    system("PAUSE");
	return 0;
}

int smallestIndex(const int x[],int sizeX)
{
  	int maxIndex = 0; 

	for(int counter = 1; counter < sizeX; counter++)  
	{
	  	if(x[maxIndex] > x[counter])
		{
			maxIndex = counter;
		}
	}
	return maxIndex;
}

void printArray(const int x[],int sizeX)
{
	int counter;

	for(counter = 0; counter < sizeX; counter++)
		cout<<x[counter]<<" ";
}
