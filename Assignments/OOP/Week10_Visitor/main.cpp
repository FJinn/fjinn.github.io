#include <iostream>

#include "windows.h"
#include "Node.h"
#include "Actor.h"

using namespace std;

class PrintHierarchyVisitor : public ActorVisitor
{
	public:
		void visit(Actor* actor)
		{
			Node* parent = actor->mOwner;
			int indentCount = 0;
			while(parent)
			{
				++indentCount;
				parent = parent->getParent();
			}
			for(int i=0; i<indentCount; i++)
			{
				cout<<" ";
			}
			cout<<actor->name<<endl;
		}
};

int main(int argc, char** argv) {
	
	Node* node;
	Actor* actor = new Actor("Javin");
	
	ActorVisitor* printVisitor = new PrintHierarchyVisitor();
	
	/*
	node->AddChild(new node());
	node->AppendActor(actor);
	node->Accept(printVisitor);
	*/
	
	system("PAUSE");
	return 0;
}
