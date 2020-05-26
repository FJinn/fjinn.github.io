#include <iostream>
#include <string>
#include "windows.h"

using namespace std;

class USB
{
	public:
		bool IsAvailable()
		{
			return true;
		}
		void Connect()
		{
			cout<<"Connecting via USB"<<endl;
		}
		void Send(string file)
		{
			cout<<file<<" sent."<<endl;
		}
};

class Bluetooth
{
	public:
		bool IsAvailable()
		{
			return false;
		}
		void Connect()
		{
			cout<<"Connecting via Bluetooth"<<endl;
		}
		void Authentication()
		{
			cout<<"Authentication device"<<endl;
		}
		void Send(string file)
		{
			cout<<file<<" sent."<<endl;
		}	
};

// facade
class FileTransfer
{
	public:
		void SendFile(string name)
		{
			USB* usb = new USB();
			Bluetooth* bt = new Bluetooth();
			if(usb->IsAvailable())
			{
				usb->Connect();
				usb->Send(name);
			}
			else if(bt->IsAvailable())
			{
				bt->Connect();
				bt->Authentication();
				bt->Send(name);
			}
			else
			{
				cout<<"Both Transfer methods are not available, file not sent!"<<endl;
			}
			delete usb;
			delete bt;
		}
};

int main()
{
	FileTransfer* ft = new FileTransfer();
	ft->SendFile("Javin's Collection!");
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
