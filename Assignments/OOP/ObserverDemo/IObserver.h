#pragma once

class IObserver
{
	public:
		virtual void Update(float price) = 0;
};
