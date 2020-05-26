#include <iostream>
#include "windows.h"

using namespace std;

int main()
{
	int a = 10;
	int b = 20;
	//! p is a int pointer -> only store int variable address
	int* p;

	cout<<"Value of a: "<<a<<endl;
	cout<<"Value of b: "<<b<<endl;
	cout<<"Value of p: "<<p<<endl;
	
	p = &a;
	
	cout<<endl<<"After code, p = &a"<<endl;
	cout<<"Value of a: "<<a<<". Address of a: "<<&a<<endl;
	cout<<"Value of b: "<<b<<". Address of b: "<<&b<<endl;
	cout<<"Value of where p points to: "<<*p<<", value of p: "<<p<<", address of p: "<<&p<<endl;
	
	p = &b;
	
	cout<<endl<<"After code, p = &b"<<endl;
	cout<<"Value of a: "<<a<<". Address of a: "<<&a<<endl;
	cout<<"Value of b: "<<b<<". Address of b: "<<&b<<endl;
	cout<<"Value of where p points to: "<<*p<<", value of p: "<<p<<", address of p: "<<&p<<endl;
	
	*p += 10;
	
	cout<<endl<<"After code, p = &b"<<endl;
	cout<<"Value of a: "<<a<<". Address of a: "<<&a<<endl;
	cout<<"Value of b: "<<b<<". Address of b: "<<&b<<endl;
	cout<<"Value of where p points to: "<<*p<<", value of p: "<<p<<", address of p: "<<&p<<endl;
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
