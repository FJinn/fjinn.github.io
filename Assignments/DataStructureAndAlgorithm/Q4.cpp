#include <iostream>
#include <queue>
#include <stack>
#include "windows.h"

using namespace std;

queue<char> myQueue;
queue<char> myQueue2;

int main()
{
	int a;
	int b;
    string strInput;
    bool isSame = true;
    cout<< "Enter words: "<< endl;
    getline(cin,strInput);
	a = strInput.length();
	b = a/2;
	
	if (a%2 != 0)
	{
		isSame = false;
	}

	
    for(int i=0; i<strInput.length();i++ )
    {
        myQueue.push(strInput[i]);
        myQueue2.push(strInput[i]);
    }
    
    while ( myQueue2.size() > 0)
    {
		myQueue2.pop();
    	if ( myQueue2.size() == b )
    	{
    		break;
		}
    	
	}
    	
    
    while (myQueue2.size() <= b && myQueue2.size() !=0)
    {
    	if (myQueue.front() != myQueue2.front())
    	{
    		isSame = false;
    		break;
		}
		myQueue.pop();
		myQueue2.pop();
	}
    

    
    
/*
    while(myQueue2.size()>0)
    {
     if(myQueue2.front()!=myQueue.back())
     {
         isSame = false;
         break;

     }
     myQueue2.pop();
     myQueue.pop();
    }
*/
    if(isSame)
    {
        cout<< "The first half and second half of "<< strInput<< " is same" << endl;
    }
    else
    {
        cout<< "It is not same " << endl;
    }

    system("PAUSE");
    return 0;
}

