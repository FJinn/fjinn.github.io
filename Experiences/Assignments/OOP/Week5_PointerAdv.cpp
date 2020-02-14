#include <iostream>
#include "windows.h"

using namespace std;

int main()
{
	const int ARRAY_SIZE = 3;
	int array[ARRAY_SIZE];
	
	for(int i=0; i<ARRAY_SIZE; i++)
	{
		array[i] = 100+i;
		cout<<"array["<<i<<"] : "<<array[i]<<" "<< &array[i]<<endl;
	}
	
	int* p = &array[0];
	
	cout<<endl<<"After code, int* p = &array[0]" <<endl;
	cout<<"*p: "<<*p<<" p: "<<p<<" &p: "<<&p<<endl;
	
	p++;
	cout<<endl<<"After code, int* p = &array[0]" <<endl;
	cout<<"*p: "<<*p<<" p: "<<p<<" &p: "<<&p<<endl;
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
