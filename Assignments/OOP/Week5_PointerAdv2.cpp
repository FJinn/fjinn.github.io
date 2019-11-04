#include <iostream>
#include "windows.h"

using namespace std;

int main()
{
	const int ARRAY_SIZE = 3;
	//! int* x -> x pointer only allow to store int variable address
	//! int** x -> x only allow to store int pointer
	int** p;
	
	p = new int* [ARRAY_SIZE];
	
	for(int i=0; i<ARRAY_SIZE; i++)
	{
		p[i] = new int[ARRAY_SIZE];
		for(int j=0; j<ARRAY_SIZE; j++)
		{
			p[i][j] = i*ARRAY_SIZE+j+1;
			cout << p[i][j]<< " | ";
		}
		cout<<endl;
	}
	
	cout<<endl<<&p<<endl<<endl;
	
	for(int i=0;i<ARRAY_SIZE; i++)
	{
		cout<<&p[i]<<endl;
	}
	
	cout<<endl<<"XXXXXXXXXXXXXXXX"<<endl<<endl;
	
	for(int i=0;i<ARRAY_SIZE; i++)
	{
		for(int j=0; j<ARRAY_SIZE; j++)
		{
			cout << &p[i][j]<< " | ";
		}
		cout<<endl;
	}
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
