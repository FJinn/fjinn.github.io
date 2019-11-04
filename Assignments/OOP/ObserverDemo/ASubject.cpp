#include "ASubject.h"
#include <algorithm>

void ASubject::Attach(Shop* shop)
{
	observerList.push_back(shop);
}

void ASubject::Detach(Shop* shop)
{
	observerList.erase(remove(observerList.begin(), observerList.end(),shop), observerList.end());
}

void ASubject::Notify(float price)
{
	// similar to for (int i=0									; i<10						; i++)
	for(vector<Shop*>::const_iterator iter = observerList.begin(); iter != observerList.end(); ++iter)
	{
		if(*iter != 0)
		{
			(*iter)->Update(price);
		}
	}
}
