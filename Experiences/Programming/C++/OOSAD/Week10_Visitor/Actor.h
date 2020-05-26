#ifndef ACTOR_H
#define ACTOR_H

#include <iostream>
#include <string>
#include "Node.h"
using namespace std;

class Node;

class Actor
{
	public:
		string name;
		Node* mOwner;
		Actor(string n) : name(n), mOwner(NULL){}
};

class ActorVisitor
{
	public:
		virtual void visit(Actor* actor) = 0;
};

#endif
