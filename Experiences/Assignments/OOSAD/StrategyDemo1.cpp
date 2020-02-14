#include <iostream>
#include <string>
#include "windows.h"

using namespace std;

//! abstract class
class SortBehaviour
{
	public:
		virtual void sort() const=0;
};

class SearchBehaviour
{
	public:
		virtual void search() const=0;
};

class Merge : public SortBehaviour
{
	public:
		virtual void sort() const
		{
			cout<<"Merge Sort()" <<endl;
		}
};

class Quick : public SortBehaviour
{
	public:
		virtual void sort() const
		{
			cout<<"Quick Sort()" <<endl;
		}
};

class Heap : public SortBehaviour
{
	public:
		virtual void sort() const
		{
			cout<<"Heap Sort()" <<endl;
		}
};

class BinaryTree : public SearchBehaviour
{
	public:
		virtual void search() const
		{
			cout<<"BinaryTree Search()" <<endl;
		}
};

class HashTable : public SearchBehaviour
{
	public:
		virtual void search() const
		{
			cout<<"HashTable Search()" <<endl;
		}
};

class Sequential : public SearchBehaviour
{
	public:
		virtual void search() const
		{
			cout<<"Sequential Search()" <<endl;
		}
};

class Collection
{
	private:
		SortBehaviour* sortPtr;
		SearchBehaviour* searchPtr;
	public:
		Collection(){}
		
		void setSort(SortBehaviour* s)
		{
			sortPtr = s;
		}
		void setSearch(SearchBehaviour* s)
		{
			searchPtr =s;
		}
		void sort()
		{
			sortPtr->sort();
		}
		void search()
		{
			searchPtr->search();
		}
};

int main()
{
	Merge merge;
	Quick quick;
	Heap heap;
	BinaryTree binaryTree;
	HashTable hashTable;
	Sequential sequential;
	
	cout<<"Collection A: "<<endl;
	Collection ca;
	ca.setSort(&merge);
	ca.setSearch(&binaryTree);
	ca.sort();
	ca.search();
	cout<<endl;
	
	cout<<"Collection B: "<<endl;
	Collection colB;
	colB.setSort(&quick);
	colB.setSearch(&sequential);
	colB.sort();
	colB.search();
	cout<<endl;
	
	cout<<"Collection C: "<<endl;
	Collection cc;
	cc.setSort(&heap);
	cc.setSearch(&hashTable);
	cc.sort();
	cc.search();
	cout<<endl;
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
