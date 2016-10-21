#include "Node.h"
#include <iostream>
using namespace std;

Node::Node()
{
	numRes=0;
	for(int i=0;i<MAX_RESISTORS_PER_NODE;i++)
	{
		resIDArray[i]=-1;
	}
}

Node::~Node()
{

}

bool Node::canAddResistor(int rIndex)
{
	if(numRes>=MAX_RESISTORS_PER_NODE) return false;
	for(int i=0;i<MAX_RESISTORS_PER_NODE;i++)
	{
		if(resIDArray[i]==rIndex) return false;
	}
	return true;
}
void Node::removeResistor(int rIndex)
{
	for (int i = 0; i<MAX_RESISTORS_PER_NODE; i++)
	{
		if (resIDArray[i] == rIndex) resIDArray[i]=-1;
	}
	numRes--;
}
void Node::removeAllResistor()
{
	for (int i = 0; i<MAX_RESISTORS_PER_NODE; i++)
	{
		resIDArray[i] = -1;
	}
	numRes = 0;
}
void Node::addResistor (int rIndex)
{
 
	 resIDArray[numRes++]=rIndex;
}

void Node::print (int nodeIndex)
{
	cout<<"Connections at node "<<nodeIndex<<": "<<numRes<<" resistor(s)"<<endl;

}



int Node::getNodeIndex()
{
	return nodeIndex;
}

void Node::setNodeIndex(int nodeIndex)
{
	this->nodeIndex=nodeIndex;
}
