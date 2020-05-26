#include <iostream>
#include <queue>
#include <stack>
#include "windows.h"

using namespace std;

stack<char> myStack; //only can store integer value


int main()
{
    string strInput;
    bool isPalindrome = true;
    int j = 0;
    cout<< "Enter words: "<< endl;
    getline(cin,strInput);

    for(int i=0; i<strInput.length();i++ )
    {
        myStack.push(strInput[i]);
    }

    while(myStack.size()>0)
    {
     if(myStack.top()!=strInput[j])
     {
         isPalindrome = false;
         break;

     }
     myStack.pop();
     j++;
    }

    if(isPalindrome)
    {
        cout<< "The "<< strInput<< " is a palindrome" << endl;
    }
    else
    {
        cout<< "The "<< strInput<< " is not a palindrome" << endl;
    }

    system("PAUSE");
    return 0;
}
