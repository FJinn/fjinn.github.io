#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "windows.h"

using namespace std;

class Resource
{
	public:
		int value;
		
		Resource()
		{
			value = 0;
		}
		
		void reset()
		{
			value = 0;
		}
		
		int getValue()
		{
			return value;
		}
		
		void setValue(int number)
		{
			value = number;
		}
};

class ObjectPool
{
	private:
		vector<Resource*> resources;
		static ObjectPool* instance;
		ObjectPool(){}
	
	public:
		static ObjectPool* getInstance()
		{
			if(instance == 0)
			{
				instance = new ObjectPool;
			}
			return instance;
		}
		
		Resource* getResource()
		{
			if(resources.empty())
			{
				cout<<"Creating new"<<endl;
				return new Resource;
			}
			else
			{
				cout<<"Reusing existing"<<endl;
				Resource* resource = resources.back();
				resources.pop_back();
				return resource;
			}
		}
		
		void returnResource(Resource* object)
		{
			object->reset();
			resources.push_back(object);
		}
};

ObjectPool* ObjectPool::instance = 0;

int main()
{
	ObjectPool* pool = ObjectPool::getInstance();
	Resource* one;
	Resource* two;
	
	one = pool->getResource();
	one->setValue(10);
	cout<<"one = "<<one->getValue()<<" ["<<one<<"]"<<endl;
	
	two = pool->getResource();
	two->setValue(20);
	cout<<"two = "<<two->getValue()<<" ["<<two<<"]"<<endl;
	
	pool->returnResource(one);
	pool->returnResource(two);
	
	one = pool->getResource();
	cout<<"one = "<<one->getValue()<<" ["<<one<<"]"<<endl;
	
	two = pool->getResource();
	cout<<"two = "<<two->getValue()<<" ["<<two<<"]"<<endl;
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
