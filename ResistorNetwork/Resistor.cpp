#include "Resistor.h"
#include <iomanip>

Resistor::Resistor()
{
	this->rIndex=-1;
	this->resistance=0;
}
Resistor::Resistor(int rIndex_,string name_,double resistance_,int endpoints_[2])
{
	this->name=name_;
	this->resistance=resistance_;
	this->rIndex=rIndex_;
	this->endpointNodeIDs[0]=endpoints_[0];
	this->endpointNodeIDs[1]=endpoints_[1];
}

Resistor::~Resistor()
{

}

void Resistor::setIndex(int index)
{
	this->rIndex=index;
}
void Resistor::setName(string name)
{
	this->name=name;
}

string Resistor::getName() const
{
	return name;
}

double Resistor::getResistance() const
{
	return resistance;
}

void Resistor::setResistance (double resistance_)
{
	this->resistance=resistance_;
}

void Resistor::print()
{
	if(rIndex>=0)
	cout<<setfill(' ')<<setw(20)<<left<<name<<"     "<<setfill(' ')<<setw(8)<<right<<std::setprecision(2)<<std::fixed<<resistance<<" Ohms "<<endpointNodeIDs[0]<<" -> "<<endpointNodeIDs[1]<<endl;
}

void Resistor::print(int nodeIndex)
{
	if (rIndex > -1 && (endpointNodeIDs[0] == nodeIndex || endpointNodeIDs[1] == nodeIndex))
	{
		cout << " ";
		print();
	}
}

int Resistor::getRIndex()
{
	return rIndex;
}

