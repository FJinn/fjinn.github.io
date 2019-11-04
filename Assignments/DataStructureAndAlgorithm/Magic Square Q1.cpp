#include <iostream>
#include "windows.h"
#include <ctime>

using namespace std;

bool isMS = true;		
int array[4][4];
int* a = &array[0][0];

void Initialize(int array[][4])  
{
	int num = 1;
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
//			Re:
//				int num = rand()%16 +1;  // random number
				array[i][j] = num;	// put inside array
				num++;
			
/*				// following is checking if there is same number(num). But it wont work, something wrong here
				for(int m=0; m<4; m++)
				{
					for(int n=0; n<4; n++)
					{
						if(num == array[m][n])
						{
							if(m!=i && n!=j)
							{
								goto Re;	
							}
						}		
					}
				}
				*/
		}
	}		
}	
	
void shuffle(int* a)
{
	for(int i=0; i<16; i++)
	{
		int b = rand()%16;
		int t = a[i];
		a[i] = a[b];
		a[b] = t;
	}
	
}
	
void check(int array[][4])
{
	//! horizontal
	int sum;
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{	
			sum += array[i][j];
			
		}
		if(sum != 34)
		{
			isMS = false;
		}
		sum = 0;
	}
	
	//! vertical
	sum = 0;
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{	
			sum += array[j][i];
		}
		if(sum != 34)
		{
			isMS = false;
		}	
		sum = 0;
	}	
	
	//!diagonally (going down)
	sum = 0;
	for(int i=0; i<4; i++)
	{	
		sum += array[i][i];		
	}
	if(sum != 34)
	{
		isMS = false;
	}
	//!diagonally (going up)
	sum = 0;	
	sum = array[3][0] + array[2][1] + array[1][2] + array[0][3];
	if(sum != 34)
	{
		isMS = false;
	}	
}

int main()
{
	srand(time(NULL));
	Initialize(array);
	shuffle(a);
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			cout << array[i][j] << " ";
		}
		cout << endl;
	}

	check(array);
	if(isMS == true)
	{
		cout << "YAY! It is a magic square!" << endl;
	}
	else
	{
		cout << "It is NOT a magic square..." << endl;
	}
	
	cout << endl;
	system("PAUSE");
	return 0;
}
