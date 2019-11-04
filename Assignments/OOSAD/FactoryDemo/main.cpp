#include <iostream>
#include "Aemployee.h"
#include "windows.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;

int main(int argc, char** argv) {
	
	Aemployee* emp = Aemployee::CreateEmployee(1);
	cout<<"Receivable for Programmer"<<endl;
	emp->PrintBenefits();
	cout<<endl;
	
	system("PAUSE");
	return 0;
}
