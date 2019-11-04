#include <iostream>
#include <queue>
#include <stack>
#include "windows.h"

using namespace std;

stack<char> myStack;
queue<char> myQueue;

int main()
{
    string strInput;
    bool isPalindrome = true;
    cout<< "Enter words: "<< endl;
    getline(cin,strInput);

    for(int i=0; i<strInput.length();i++ )
    {
        myStack.push(strInput[i]);
        myQueue.push(strInput[i]);
    }

    while(myStack.size()>0)
    {
     if(myStack.top()!=myQueue.front())
     {
         isPalindrome = false;
         break;

     }
     myStack.pop();
     myQueue.pop();
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

