#include <iostream>
#include "windows.h"

using namespace std;

int size;

int start(int &x, int &y)
{
	x = (size)/2;
	y = 0;
	return x, y;
}

int main()
{
	cout << "What is the Magic Square size (N X N)?" << endl;
	cin >> size;
	
	int x, y;
	
	int array[size][size];

	for(int i=0; i<size; i++) // zero -> Initialize
	{
		for(int j=0; j<size; j++)
		{
			array[i][j] = 0;
		}
	}
	
	start(x, y);
	array[y][x] = 1;
	for(int i=2; i<=size*size; i++)
	{
		if(array[y][x] == array[0][size-1]) // check if it is top right corner
		{
			y = y+1;
		}	
		else if(y == 0) // check yBorder
		{
			y = size-1;
			x = x+1;
		}
		else if(array[y-1][x+1] == 0) // normal movement
		{
			y = y-1;
			if(x == size-1) // check xBorder
			{
				x = 0;
			}
			else
			{
				x = x+1;			
			}
		}
		else if(array[y-1][x+1] != 0)
		{
			// check xBorder 
			if(x == size-1)
			{	
				x = 0;
				y = y-1;
			}
			else // move down
			{	
				y = y+1;	
			}
		}
	
		array[y][x] = i; // insert number
	}
	
	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			cout << " " << array[i][j] << " ";
		}
		cout << endl;
	}

	int sum = 0; // horizontal
	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{	
			sum += array[i][j];
		}
		cout << i+1 << " Horizontal line's total: " << sum << endl;
		sum = 0;
	}
	
	//! vertical
	sum = 0;
	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{	
			sum += array[j][i];
		}
		cout << i+1 << " Vertical line's total: " << sum << endl;
		sum = 0;
	}	
	
	//!diagonally (going down)
	sum = 0;
	for(int i=0; i<size; i++)
	{	
		sum += array[i][i];		
	}
	cout << "Diagonally(down) line's total: " << sum << endl;

	//!diagonally (going up)
	sum = 0;
	int j = 0;
	for(int i=size-1; i>=0; i--)
	{	
		sum += array[i][j];	
		j++;
	}
	cout << "Diagonally(down) line's total: " << sum << endl;	
	
	
	cout << endl;
	system("PAUSE");
	return 0;
}
