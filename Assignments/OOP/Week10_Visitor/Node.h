#ifndef NODE_H
#define NODE_H

#include "Actor.h"
#include <vector>

using namespace std;

class Node
{
	protected:
		vector<Node*> mChildren;
		Node* mParent;
		vector<Actor*> mActor;
	public:
		Node() : mParent(NULL){}
		
		void AddChild(Node* node);
		void AppendActor(Actor* actor);
		inline Node* getParent()
		{
			return mParent;
		}
		
		virtual void Accept(ActorVisitor* visitor) = 0;
};

#endif
