/**

 +-------------+
 | Question  4 |
 +-------------+
 
Category of the question :
    Correct syntax & logical errors

 Objective of the question :
    The following program inputs two integers from the user to be 
    used as the upper and lower bounds for the two loops in the 
    program. The first loop is decrementing by 4 while the second 
    loop is incrementing by 5. The body of the loops will output 
    the product of the two integers and display the results on the 
    screen.

    The program has errors. Please correct the errors so that it can 
    display the desired output.
    
 Correct Sample run 1:
    Enter xLim & yLim ->  12 15
    12  72  132  8  48  88  4  24  44

 Correct Sample run 2:
    Enter xLim & yLim -> 13  18
    13  78  143  208  9  54  99  144  5  30  55  80  1  6  11  16

*********************************************************/

#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    int x, y, m, xLim, yLim;
    
    cout << "Enter xLim & yLim -> ";
    cin >> xLim >> yLim;

    for(x= xLim; x > 0; x-= 4)
    {
	    for(y = 1; y < yLim; y+=5)
	    {
		   	m = x * y;
		    cout << m << "  ";
		}  	
	}

        
    cout << endl << endl;
    system ("pause");
    return 0;
}
