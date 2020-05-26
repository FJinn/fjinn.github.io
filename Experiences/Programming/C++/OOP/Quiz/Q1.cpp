/**
 +-------------+
 | Question  1 |
 +-------------+

 Category of the question :
    Correct syntax errors

 Objective of the question :
    After the user has entered the information for my car and your car,
    it will compared both cars and decide which is the better buy.

    However, if you try to compile the program, you will realize
    that the program below contains syntax errors.

    What you need to do is to find the errors and correct them so
    that the desired output can be displayed as shown in the
    sample run.

 Correct Sample run 1:
    ********* My Car ********
    Input Power: 1500
    input Price: 90000
    ********* Your Car ********
    Input Power: 1600
    input Price: 85000
    
    Output: Your car is a better buy!!!
    
Correct Sample run 2:
    ********* My Car ********
    Input Power: 1600
    input Price: 58000
    ********* Your Car ********
    Input Power: 1300
    input Price: 62000

    Output: My car is a better buy!!!    
*********************************************************/

#include <iostream>
using namespace std;

struct Car {
    int ccPower;
    double Price;
};

int main()
{ 
    Car myCar, yourCar;
    
    cout << "********* My Car ********" << endl;
    cout << " Input Power: ";
    cin >> myCar.ccPower; 
    cout << " Input Price: ";
    cin >> myCar.Price; 
         
    cout << "********* Your Car ********" << endl;
    cout << " Input Power: ";
    cin >> yourCar.ccPower; 
    cout << " Input Price: ";
    cin >> yourCar.Price; 

    cout << "\nOutput: ";             
    if (myCar.ccPower > yourCar.ccPower && myCar.Price < yourCar.Price)
        cout << "My car is a better buy!!!" << endl;
    else if (myCar.ccPower < yourCar.ccPower && myCar.Price > yourCar.Price)
        cout << "Your car is a better buy!!!" << endl;             

    system("PAUSE");     
    return 0;
}

