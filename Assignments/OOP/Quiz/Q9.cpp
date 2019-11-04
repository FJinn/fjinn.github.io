/*
 +--------------+
 | Question  9 |
 +--------------+
 
Category of the question :
    Write a program

 Objective of the question :
    You are to write a program such that after the user has entered
    a line of text with many words separated by spaces, your program
    will display out the number of a, e, i, o and u in the text.

 Correct Sample run 1 :
    Input a line of text: Programming is FUN!
    a -> 1
    e -> 0
    i -> 2
    0 -> 1
    u -> 1

 Correct Sample run 2 :
    Input a line of text: Your Life Is In Your Hand
    a -> 1
    e -> 1
    i -> 3
    0 -> 2
    u -> 2

*********************************************************/
#include <iostream>
#include <string>

using namespace std;

int main()
{
	string sentence;
	cout << "Input a line of text: ";
	getline(cin, sentence);

	int a =0 ,e=0 ,i=0 ,o=0 ,u=0;

	for(int j=0; j<sentence.length(); j++)
	{
		if(sentence[j] == 'a' || sentence[j] == 'A')
		{
			a += 1;
		}
		else if(sentence[j] == 'e' || sentence[j] == 'E')
		{
			e += 1;
		}
		else if(sentence[j] == 'i' || sentence[j] == 'I')
		{
			i += 1;
		}
		else if(sentence[j] == 'o' || sentence[j] == 'O')
		{
			o += 1;
		}
		else if(sentence[j] == 'u' || sentence[j] == 'U')
		{
			u += 1;
		}		
	}
	
	cout << endl;
	cout << "a -> " << a << endl;
	cout << "e -> " << e << endl;
	cout << "i -> " << i << endl;
	cout << "o -> " << o << endl;
	cout << "u -> " << u << endl;
	
    return 0;
}

