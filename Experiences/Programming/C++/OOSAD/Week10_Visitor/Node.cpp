#include "Node.h"

void Node::AddChild(Node* node)
{
	if(node->mParent)
	{
		return;
	}
	mChildren.push_back(node);
	node->mParent = this;
}

void Node::AppendActor(Actor* actor)
{
	if(actor->mOwner)
	{
		return;
	}
	mActor.push_back(actor);
	actor->mOwner = this;
}

void Node::Accept(ActorVisitor* visitor)
{
	for(int i=0; i<mActor.size(); i++)
	{
		visitor->visit(mActor[i]);
	}
	int count = mChildren.size();
	
	for(int i=0; i<count; i++)
	{
		mChildren[i]->Accept(visitor);
	}
}
