#include <iostream>
#include "windows.h"
#include <string>

using namespace std;

class House;

class Room
{
	private:
		House* myHse_p;
		char* name_p;
	public:
		Room(){}
		Room(House* hse, char* myName)
		{
			cout<<"Room::ctor"<<endl;
			myHse_p = hse;
			if(myHse_p != NULL)
			{
				name_p = new char(sizeof(strlen(myName)));
				name_p = myName;
			}
			else
			{
				cout<<"Oops, House itself is not created yet..."<<endl;
			}
		}
		
		~Room()
		{
			cout<<"Room::dtor"<<endl;
			myHse_p = NULL;
			delete(name_p);
		}
		
		static void createRoom(Room* (&room), House* hse, char* name)
		{
			room = new Room(hse, name);
		}
		
		void disp()
		{
			cout<<name_p<<endl;
		}
		static void initList_v(Room* (&roomList_p)[3])
		{
			roomList_p[3] = new Room[3];
		}
};

class House
{
	private:
		char* name_p;
		Room* roomList_p[3];
	public:
		House(char* myName)
		{
			cout<<"House::ctor"<<endl;
			name_p = new char(sizeof(strlen(myName)));
			name_p = myName;
			Room::initList_v(roomList_p);
			Room* myRoom;
			Room::createRoom(myRoom, this, "Kitchen");
			roomList_p[0] = myRoom;
			Room::createRoom(myRoom, this, "Bedroom");
			roomList_p[1] = myRoom;
			Room::createRoom(myRoom, this, "Toilet");
			roomList_p[2] = myRoom;
		}
		~House()
		{
			cout<<"Room::dtor"<<endl;
			unsigned int i;
			cout<<"Delete all the Rooms"<<endl;
			for(i=0; i<3; i++)
			{
				if(roomList_p[i] != NULL)
				{
					delete roomList_p[i];
				}
			}
			delete[] roomList_p;
			delete name_p;
		}
		
		void disp()
		{
			cout<<endl<<endl<<"Name of the House: "<<name_p<<endl;
			if(roomList_p != NULL)
			{
				unsigned int i=0;
				cout<<endl<<endl<<"Rooms details..."<<endl;
				for(i=0; i<3; i++)
				{
					if(roomList_p[i] != NULL)
					{
						roomList_p[i]->disp();
					}
					cout<<endl<<endl;
				}
			}
		}
};

int main()
{
	cout<<"Example of Composite Relationship"<<endl;
	cout<<"---------------------------------"<<endl;
	House hse("Javin House");
	cout<<endl<<"house Detail..."<<endl;
	hse.disp();
	
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
