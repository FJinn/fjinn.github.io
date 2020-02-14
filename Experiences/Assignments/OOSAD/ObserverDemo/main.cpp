#include <iostream>
#include "ASubject.h"
#include "Shop.h"
#include "Product.h"
#include "IObserver.h"
#include "windows.h"

using namespace std;

int main(int argc, char** argv) {
	
	Product chocolate;
	Shop shop1("Darshini");
	Shop shop2("Jonathan");
	
	chocolate.Attach(&shop1);
	chocolate.Attach(&shop2);
	
	chocolate.Notify(25.5f);
	
	chocolate.Detach(&shop2);
	
	chocolate.Notify(65.5f);
	
	cout << endl;
	system("PAUSE");
	return 0;
}
