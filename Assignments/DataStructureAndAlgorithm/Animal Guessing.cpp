#include <iostream>
#include <string>
#include <queue>
#include "windows.h"

using namespace std;

const int level = 4; 
int i; // a value to indicate current level
int c = level; // level counter for the post order traversal during tree map creation 
queue <string> ques; 

class Question
{
public:
	string q;
	Question* y;
	Question* n;
};

class BinaryTree
{
public:
	Question* root;
	BinaryTree()
	{
		root = NULL;
	}
	// create basic tree map with levels-- 
	// pros:  it will always same for left and right side-- 
	// cons: cannot create a single or more slots for certain area, as it creates entire level
	void Build(Question* &question)  
	{
		if(i<level)
		{
			question = new Question;
			question->n = NULL;
			question->y = NULL;		
			i++;
			c--;				
		}
		if(!question && i>=level)
		{
			return;			
		}
		Build(question->n);
		i = i-c;
		Build(question->y);
		c++;
	}
		
	// Insert question
	// Postorder
	void Insert(Question* &question, queue <string> &s) 
	{
			if(!question)
			return;							
			Insert(question->n, s);
			Insert(question->y, s);
			question->q = s.front();
			s.pop();	
	}	
	// for tree map testing 	
	void Display(Question* question) 
	{
		if(!question) 
		return;
		Display(question->n);
		Display(question->y);
		cout << question->q << endl;		
	}
};

int main()
{
	ques.push("You are NOT lying, are you?");
	ques.push("YEAH! I am correct!");
	ques.push("Is it a cat?");
	ques.push("You are NOT lying, are you?");
	ques.push("YEAH! I am correct!");
	ques.push("It is a dog?");
	ques.push("Does it bark?");
	ques.push("You are NOT lying, are you?");
	ques.push("YEAH! I am correct!");
	ques.push("It is a not a fish?");
	ques.push("You are NOT lying, are you?");
	ques.push("YEAH! I am correct!");
	ques.push("It is a fish?");
	ques.push("Does it live in water?");
	ques.push("Is it not a pet?");    // root

	BinaryTree* bt = new BinaryTree();
	bt->Build(bt->root);
	bt->Insert(bt->root, ques);
	
	char answer;
	
	while (bt->root)
	{
		cout<< bt->root->q << endl;
		if (bt->root->n && bt->root->y)
		{
			cout << endl << "Is that a Y (yes) or N (no)?" << endl << "Please Enter your answer as Y or N" << endl;	
		}
		else
		{
			cout << "Press any key to quit" << endl;
			bt->root = NULL; 
		}
		cin >> answer;
		cout << endl;
		if (answer == 'y' || answer == 'Y')
		{
			bt->root = bt->root->y;
		}
		else if (answer == 'n' || answer == 'N')
		{
			bt->root = bt->root->n;
		}
	}
		

	
	cout << endl;
	system("PAUSE");
	return 0;
}
