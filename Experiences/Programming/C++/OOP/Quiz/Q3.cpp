/****
 +-------------+
 | Question  3 |
 +-------------+
 
Category of the question :
    Correct logical errors

 Objective of the question :
    The following program should input two sentences from the user 
    and then display the exact sentences on the screen.

    The program has errors. Please correct the errors so that it can 
    display the desired output.
    
 Correct Sample run 1:
    Enter a sentence -> First trial.
    First trial.
    Enter a sentence -> Hello, people!
    Hello, people!
    
*********************************************************/

#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
  string sentence1, sentence2;

  cout << "Enter a sentence -> ";
  getline(cin, sentence1);
  cout << sentence1;
  cout << "\n\nEnter a sentence -> ";
  getline(cin, sentence2);
  cout << sentence2;
 
  cout << endl << endl;
  system ("pause");
  return 0;
}

