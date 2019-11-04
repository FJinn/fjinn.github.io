/**
 +-------------+
 | Question  5 |
 +-------------+
 
Category of the question :
    Correct syntax & logical errors

 Objective of the question :
    The following program should input a word (maximum 30 characters) 
    from the user and then displays the word in reverse order with a 
    trailing '-' for each character, and there should be no leading 
    spaces.

    The program has errors. Please correct the errors so that it can 
    display the desired output.
    
 Correct Sample run 1:
    Enter a word -> Highland
    Reverse order: d-n-a-l-h-g-i-H-

 Correct Sample run 2:
    Enter a word -> Menu
    Reverse order: u-n-e-M-

*********************************************************/

#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

int main()
{
    char word[31];
    
    cout << "Enter a word -> ";
    cin >> word;
    int length = sizeof(word);
    cout << "Reverse order: ";

    for(int i = strlen(word) - 1; i >= 0 ; i--)
    {
	   	cout << word[i];
	    cout << "-";
	}
    
    
    cout << endl << endl;
    
    system ("pause");
    return 0;
}
