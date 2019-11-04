#ifndef _BEHAVIOUR_H
#define _BEHAVIOUR_H

class Behaviour
{
	public:
		virtual void behaviour(string n) = 0;
};

class Attack : public Behaviour
{
	public:
		void behaviour(string n)
		{
			cout<<n<<" is an Attack Mode"<<endl;
		}	
};

class Defence : public Behaviour
{
	public:
		void behaviour(string n)
		{
			cout<<n<<" is an Defence Mode"<<endl;
		}
};

#endif
