#include <iostream>
#include "windows.h"

using namespace std;

void tower(int, char, char, char);
int i=0;

int main()
{
	int num;	
	cout<< "Enter number of disks: ";
	cin>> num;
	cout<< "The sequence of moves involved in the Tower of Hanoi are: "<< endl;
	tower(num, 'A','C','B');
	cout<< endl<< endl;
	cout<< "The total moves for "<< num<< " disks: "<< i<< endl<< endl;
	system("PAUSE");
	return 0;
}

void tower( int num, char frompeg, char topeg, char auxpeg)
{
	if( num == 1)
	{
		cout<< endl<< " move disk 1 from peg " << frompeg<< " to peg " << topeg;
		i++;
		return;
	}
	tower(num-1, frompeg, auxpeg, topeg);
	cout << endl<<  " move disk "<< num << " from peg "<< frompeg<< " to peg "<< topeg;
	i++;
	tower(num-1, auxpeg, topeg, frompeg);
}
