/*
 +-------------+
 | Question  2 |
 +-------------+
 
Category of the question :
    Correct syntax errors

 Objective of the question :
    The following program should input three integers from the user,
    and then update the smallest number to the sum of all the three 
    numbers.
    
    The program has errors. Please correct the errors so that it can 
    display the desired output.
    
 Correct Sample run 1:
    Enter 3 integers -> 2  10  7
    19  10  7
    
 Correct Sample run 2:
    Enter 3 integers -> 3  -11  10
    3  2  10
    
 Correct Sample run 3:
    Enter 3 integers -> 7  4  0
    7  4  11

*********************************************************/

#include <iostream>
#include <cstdlib>

using namespace std;

void mystery(int& a, int& b, int& c);

int main()
{
    int x, y, z;
    
    cout << "Enter 3 integers -> ";
    cin>>x>>y>>z;
    
    mystery(x, y, z);

    cout <<x<<"  "<<y<<"  "<<z<<endl;
    system ("pause");
    return 0;
}

void mystery(int& a, int& b, int& c)
{
    if(a<b && a<c)
        a = a+b+c;
    else if(b<a && b<c)        
        b = a+b+c;
    else if(c<a && c<b)        
        c = a+b+c;
}
