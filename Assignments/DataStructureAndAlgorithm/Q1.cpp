#include <iostream>
#include <queue>
#include <stack>
#include "windows.h"

using namespace std;

stack<char> myStack; //only can store intiger value

/*
void DisplayStack(stack<char>tempStack) //for-loop only suitable for arrays
{
    cout<<"============================="<<endl;
    if(tempStack.empty())
    {
        cout<<"Stack is empty!"<<endl;
    }
    else
    {
        while(tempStack.size()>0)
        {
            cout<<tempStack.top()<<endl;
            tempStack.pop();
        }
    }
    cout<<"============================="<<endl;

}

void ClearStack(stack<string> &realStack)
{
    while(!realStack.empty())
    {
        realStack.pop();
    }
}

void ReverseStack(stack<string> &realStack, stack<string> tempStack)
{
    ClearStack(realStack);
    while(!tempStack.empty())
    {
        realStack.push(tempStack.top());
        tempStack.pop();
    }

}
*/
int main()
{
   string strInput;
   cout<< "enter a word: ";
   getline(cin, strInput);
   /*
               o   i  r  a  m
   strInput    0   1  2  3  4  strInput.length()  ->5


   */


   //! store all the char from the input one by one
   for(int i=0; i<strInput.length();i++)
   {
       //! push the char from the word to myStack)
       myStack.push(strInput[i]);
   }
    while(myStack.size()>0)
    {
         cout<< myStack.top();
         myStack.pop();
    }
    cout<<endl;


    system("PAUSE");
    return 0;
}
