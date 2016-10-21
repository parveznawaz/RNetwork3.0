#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include "Rparser.h"

using namespace std;

Rparser::Rparser()
{
	MAX_NODE_NUMBER = 0;
	maxResistors = 0;
}
Rparser::~Rparser()
{
	if (nodes != NULL && MAX_NODE_NUMBER>0)
	{
		delete[] nodes;
	}
	if (resistors != NULL && maxResistors>0)
	{
		delete[] resistors;
	}
}

int Rparser::findResistor(string name)
{
	for(int i=0;i<maxResistors;i++)
	{
		if(resistors[i].getName()==name)
			return i;
	}
	return -1;
}

int Rparser::insertR(stringstream & getInput)
{
	string line, resistorName, extraArg;
	double resistorValue;
	int nodeID1=0, nodeID2=0, temp1=0;



	//Error checking for resistor Name
	getInput >> resistorName;
	if (getInput.eof()) {
		cout << "Error: too few arguments" << endl;
		
		return 0;
	}
	else if (resistorName == "all") {
		cout << "Error: resistor name cannot be keyword \"all\"" << endl;
		
		return 0;
	}
	else if (getInput.eof()) {
		cout << "Error: too few arguments" << endl;
		
		return 0;
	}
	//**************************************************************************
	//Error checking for resistor value
	getInput >> resistorValue;
	if (getInput.eof()) {
		cout << "Error: too few arguments" << endl;
		
		return 0;
	}
	else if (getInput.fail()) {
		cout << "Error: invalid argument" << endl;
		
		return 0;
	}
	else if (getInput.peek() != ' ' && !getInput.eof()) {
		cout << "Error: invalid argument" << endl;
		
		return 0;
	}
	else if (resistorValue < 0) {
		cout << "Error: negative resistance" << endl;
		
		return 0;
	}

	//**************************************************************************
	//Error checking for node 1
	getInput >> nodeID1;
	if (getInput.eof()) {
		cout << "Error: too few arguments" << endl;
		
		return 0;

	}
	else if (getInput.fail() && (getInput.peek() != ' ' || getInput.peek() != '\n' || getInput.peek() != '\t')) {
		cout << "Error: invalid argument" << endl;
		
		return 0;
	}
	else if (!getInput.eof() && (getInput.peek() != ' ' /*|| getInput.peek() != '\n' || getInput.peek() != '\t')*/)) {
		cout << "Error: invalid argument" << endl;
		
		return 0;
	}
	else if (nodeID1 >= MAX_NODE_NUMBER || nodeID1 < MIN_NODE_NUMBER) {
		cout << "Error: node " << nodeID1 << " is out of permitted range "<<MIN_NODE_NUMBER<<"-"<<MAX_NODE_NUMBER-1 << endl;
		
		return 0;
	}


	//*****************************************************************************    
	//Error checking for node 2
	temp1 = nodeID2;
	getInput >> nodeID2;
	if (getInput.eof() && temp1 == nodeID2) {
		cout << "Error: too few arguments " << endl;
		
		return 0;
	}
	else if (getInput.fail()) {
		cout << "Error: invalid argument" << endl;
		
		return 0;
	}
	else if (getInput.peek() != ' ' && getInput.peek() != '\n' && getInput.peek() != '\t' && !getInput.eof()) {
		cout << "Error: invalid argument" << endl;
		
		return 0;
	}
	else if (nodeID2 >= MAX_NODE_NUMBER || nodeID2 < MIN_NODE_NUMBER) {
		cout << "Error: node " << nodeID2 << " is out of permitted range "<<MIN_NODE_NUMBER<<"-"<<MAX_NODE_NUMBER-1 << endl;
		
		return 0;
	}
	else if (nodeID1 == nodeID2) {
		cout << "Error: both terminals of resistor connect to node 2" << endl;
		
		return 0;
	}
	else {
		getInput >> extraArg;
		if (!getInput.fail()) {
			cout << "Error: too many arguments" << endl;
			
			return 0;
		}
		else {
			if (resCount == maxResistors)
			{
				cout << "Error: resistor array is full" << endl;
			}
			else if (findResistor(resistorName) != -1)
			{
				cout << "Error: resistor " << resistorName << " already exists" << endl;
			}
			else if (!nodes[nodeID1].canAddResistor(resCount) || !nodes[nodeID2].canAddResistor(resCount))
			{
				cout << "Error: node is full" << endl;
			}
			else
			{
				cout << "Inserted: resistor " << resistorName << " " << setprecision(2) << fixed << resistorValue << " Ohms " << nodeID1 << " -> " << nodeID2 << endl;
				int endpoints[2];
				endpoints[0] = nodeID1;
				endpoints[1] = nodeID2;
				resistors[resCount] = Resistor(resCount, resistorName, resistorValue, endpoints);
				nodes[nodeID1].addResistor(resCount);
				nodes[nodeID2].addResistor(resCount);
				resCount++;
			}						
			return 0;
		}
	}
	
	return 0;
}

int Rparser::printR(stringstream & getInput) {
	string resistorName, extraArg;
	//bool yes = true;
	getInput >> resistorName;
	if (getInput.eof() && (getInput.peek() == ' ' && getInput.peek() == '\n' && getInput.peek() == '\t')) {
		cout << "Error: too few arguments" << endl;
		
	}
	else {
		
			getInput >> extraArg;
			if (resistorName == "all" && getInput.fail()) {
				/*cout << "Print: all resistors" << endl;
				*/
				cout << "Print:" << endl;
				for (int i = 0; i < maxResistors; i++)
				{
					resistors[i].print();
				}
				return 0;
			}
			else if ((!resistorName.empty()) && getInput.fail()) {
				int rIndex = findResistor(resistorName);
				if (rIndex>-1)
				{
					cout << "Print:" << endl;
					resistors[rIndex].print();
				}
				else
				{
					cout << "Error: resistor " << resistorName << " not found" << endl;
				}
				return 0;

			}
			else if (resistorName != "all") {
				cout << "Error: invalid argument" << endl;				
				return 0;
			}
			else if (!getInput.fail()) {
				cout << "Error: too many arguments" << endl;
				
				return 0;
			}
			else {
				cout << "Error: too few arguments" << endl;
				
				return 0;
			}		

	}
	return 0;
}


int Rparser::getAvailableResistorIndex()
{
	for(int i=0;i<maxResistors;i++)
	{
		if(resistors[i].getRIndex()==-1)
			return i;
	}
	return -1;
}

int Rparser::printNode(stringstream & getInput) {
	int nodeID=0, temp=0;
	string all, extraArg1, extraArg2;
	bool yes = true;
	bool yes1 = true;


	temp = nodeID;
	if (yes) {

		getInput >> nodeID;
		if (!getInput.fail()) {

			if (getInput.eof() && temp == nodeID) {
				cout << "Error: too few arguments " << endl;			
				return 0;
			}
			else if (getInput.fail()) {
				cout << "Error: invalid argument" << endl;				
				return 0;
			}
			else if (getInput.peek() != ' ' && getInput.peek() != '\n' && getInput.peek() != '\t' && !getInput.eof()) {
				cout << "Error: invalid argument" << endl;				
				return 0;
			}
			else if (nodeID > MAX_NODE_NUMBER || nodeID < MIN_NODE_NUMBER) {
				cout << "Error: node " << nodeID << " is out of permitted range "<<MIN_NODE_NUMBER<<"-"<<MAX_NODE_NUMBER << endl;				
				return 0;
			}
			else {
				getInput >> extraArg1;
				if (!getInput.fail()) {
					cout << "Error: too many arguments" << endl;
					
					return 0;
				}
				else {
					cout << "Print:" << endl;					
					if (nodeID>0 && nodeID <= MAX_NODE_NUMBER)
					{
						nodes[nodeID].print(nodeID);
						for (int i = 0; i < maxResistors; i++)
						{
						
							resistors[i].print(nodeID);
						}
					}
					return 0;
				}
			}

		}
		else {
			getInput.clear();
			getInput >> all;
			if (yes1) {
				getInput >> extraArg2;
				if (all == "all" && getInput.fail()) {
					cout << "Print:" << endl;
					for (int i = 0; i < MAX_NODE_NUMBER; i++)
					{
						nodes[i].print(i);
						for (int j = 0; j < maxResistors; j++)
						{
							resistors[j].print(i);
						}
					}
					return 0;
				}
				else if (all.empty()) {
					cout << "Error: too few arguments" << endl;					
					return 0;
				}
				else if (all != "all") {
					cout << "Error: invalid argument" << endl;					
					return 0;
				}
				else if (!getInput.fail()) {
					cout << "Error: too many arguments" << endl;					
					return 0;
				}
			}
		}

	}

	cout << "Error: too few arguments" << endl;
	

	return 0;
}

int Rparser::modifyR(stringstream & getInput) {
	string resistorName, line, extraArg;
	double resistorValue=0, temp=0;

	//Error checking for resistor name
	getInput >> resistorName;
	if (resistorName == "all") {
		cout << "Error: resistor name cannot be keyword \"all\" " << endl;		
		return 0;
	}
	else if (getInput.eof() && (getInput.peek() == ' ' || getInput.peek() == '\n' || getInput.peek() == '\t')) {
		cout << "Error: too few arguments" << endl;
		
		return 0;
	}


	//*****************************************************************************    
	//Error checking for resistor value
	temp = resistorValue;
	getInput >> resistorValue;

	if (getInput.eof() && temp == resistorValue) {
		cout << "Error: too few arguments" << endl;
		
		return 0;
	}
	else if (getInput.fail()) {
		cout << "Error: invalid argument" << endl;
		
		return 0;
	}
	else if (!getInput.eof() && !getInput.good() && (getInput.peek() != ' ' || getInput.peek() != '\n' || getInput.peek() != '\t')) {
		cout << "Error: invalid argument" << endl;
		
		return 0;
	}
	else if (resistorValue < 0) {
		cout << "Error: negative resistance" << endl;
		
		return 0;
	}
	else if (getInput.fail() && !getInput.eof() && (getInput.peek() != ' ' || getInput.peek() != '\n' || getInput.peek() != '\t')) {
		cout << "Error: invalid argument" << endl;
		
		return 0;
	}
	//else if ((getInput.peek() != '\n' || getInput.peek() != ' ' || getInput.peek() != '\t') && !getInput.eof()) {
	//	cout << "Error: too many arguments" << endl;
	//	
	//	return 0;
	//}
	else {
		getInput >> extraArg;
		if (!getInput.fail()) {
			cout << "Error: too many arguments" << endl;
			
			return 0;
		}
		else {
			int resistorIndex = findResistor(resistorName);
			if (resistorIndex != -1)
			{
				cout << "Modified: resistor " << resistorName << " from " << resistors[resistorIndex].getResistance() << " Ohms to " << resistorValue << " Ohms" << endl;
				resistors[resistorIndex].setResistance(resistorValue);
			}
			else
			{
				cout << "Error: resistor " << resistorName << " not found" << endl;
			}
			return 0;
		}
	}


	
	return 0;
}
int Rparser::deleteR(stringstream & getInput) {
	string resistorName, extraArg;
	getInput >> resistorName;
	if (getInput.eof() && (getInput.peek() == ' ' && getInput.peek() == '\n' && getInput.peek() == '\t')) {
		cout << "Error: too few arguments" << endl;
		
	}
	else {

		
			getInput >> extraArg;
			if (resistorName == "all" && getInput.fail()) {
				
				for (int i = 0; i < MAX_NODE_NUMBER; i++)
				{
					nodes[i].removeAllResistor();
				}
				for (int i = 0; i<maxResistors; i++)
				{
					resistors[i].setName("");
					resistors[i].setResistance(0.0);
					resistors[i].setIndex(-1);					
				}
				resCount = 0;
				cout << "Deleted: all resistors" << endl;
				return 0;
			}
			else if ((!resistorName.empty()) && getInput.fail()) {
				
				int resistorIndex = findResistor(resistorName);
				if (resistorIndex == -1)
					cout << "Error: resistor " << resistorName << " not found" << endl;
				else
				{
					cout << "Deleted: resistor " << resistorName << endl;
					for (int i = 0; i < MAX_NODE_NUMBER; i++)
					{
						nodes[i].removeResistor(resistorIndex);
					}
					resistors[resistorIndex].setName("");
					resistors[resistorIndex].setResistance(0.0);
					resistors[resistorIndex].setIndex(-1);
					resCount--;
				}
				return 0;

			}
			else if (resistorName != "all" && !resistorName.empty()) {
				cout << "Error: invalid argument" << endl;
				
				return 0;
			}
			else if (!getInput.fail()) {
				cout << "Error: too many arguments" << endl;
				
				return 0;
			}
			else {
				cout << "Error: too few arguments" << endl;
				
				return 0;
			}

	}
	return 0;
}

int Rparser::maxVal(stringstream & getInput)
{

	string line, extraArg;
	int numOfR = -1, numOfN = -1,temp=-1;

	//*****************************************************************************    
	//Error checking for number of nodeValue value
	
	getInput >> numOfN;

	if (getInput.eof() && temp==numOfN ) {
		cout << "Error: too few arguments" << endl;

		return 0;
	}
	else if (getInput.fail()) {
		cout << "Error: invalid argument" << endl;

		return 0;
	}
	else if (!getInput.eof() && !getInput.good() && (getInput.peek() != ' ' || getInput.peek() != '\n' || getInput.peek() != '\t')) {
		cout << "Error: invalid argument" << endl;

		return 0;
	}
	else if (numOfN <= 0) {
		cout << "Error: maxVal arguments must be greater than 0" << endl;

		return 0;
	}
	else if (getInput.fail() && !getInput.eof() && (getInput.peek() != ' ' || getInput.peek() != '\n' || getInput.peek() != '\t')) {
		cout << "Error: invalid argument" << endl;

		return 0;
	}
	
	//*****************************************************************************    
	//Error checking for number of resistor value
	
	getInput >> numOfR;

	if (getInput.eof() && temp == numOfR) {
		cout << "Error: too few arguments" << endl;

		return 0;
	}
	else if (getInput.fail()) {
		cout << "Error: invalid argument" << endl;

		return 0;
	}
	else if (!getInput.eof() && !getInput.good() && (getInput.peek() != ' ' || getInput.peek() != '\n' || getInput.peek() != '\t')) {
		cout << "Error: invalid argument" << endl;

		return 0;
	}
	else if (numOfR <= 0) {
		cout << "Error: maxVal arguments must be greater than 0" << endl;

		return 0;
	}
	else if (getInput.fail() && !getInput.eof() && (getInput.peek() != ' ' || getInput.peek() != '\n' || getInput.peek() != '\t')) {
		cout << "Error: invalid argument" << endl;

		return 0;
	}
	
	/*******************************************************************************************************************/
	else {
		getInput >> extraArg;
		if (!getInput.fail()) {
			cout << "Error: too many arguments" << endl;

			return 0;
		}
		else {
			if (resistors != NULL && maxResistors>0) delete[] resistors;
			if (resistors != NULL && MAX_NODE_NUMBER>0) delete[] nodes;
		
			resistors = NULL;
			nodes = NULL;
			MAX_NODE_NUMBER = 0;
			maxResistors = 0;
			resCount = 0;

			MAX_NODE_NUMBER = numOfN;
			MAX_NODE_NUMBER = MAX_NODE_NUMBER + 1;
			maxResistors = numOfR;
			resistors = new Resistor[maxResistors];
			nodes = new Node[MAX_NODE_NUMBER];
			for (int i = MIN_NODE_NUMBER; i<MAX_NODE_NUMBER; i++)
			{
				nodes[i].setNodeIndex(i);
			}
			cout << "New network: max node number is " << MAX_NODE_NUMBER - 1 << "; max resistors is " << maxResistors << endl;
			return 0;
		}
	}



	return 0;
}
void Rparser::getInput()
{
	string line,command;
	cout << ">";
	//cout << ">maxVal ";
	while (getline(cin, line))
	{
		//if (MAX_NODE_NUMBER < 1 || maxResistors < 1)
		//{
		//	//cout << ">maxVal ";
		//	//getline(cin, line);
		//	//if (cin.eof()) break;
		//	stringstream lineStream(line);
		//	maxVal(lineStream);			
		//}
		//else
		{


			stringstream lineStream(line);
			lineStream >> command;

			if (command == "maxVal")
			{
				maxVal(lineStream);
			}
			else
			{
				if (command == "insertR")
				{
					insertR(lineStream);
				}
				else if (command == "printR")
				{
					printR(lineStream);
				}
				else if (command == "printNode")
				{
					printNode(lineStream);
				}
				else if (command == "modifyR")
				{
					modifyR(lineStream);
				}
				else if (command == "deleteR")
				{
					deleteR(lineStream);
				}
				else
				{
					cout << "Wrong command" << endl;
				}
			}
		}
	//if (MAX_NODE_NUMBER == 0 && maxResistors == 0)
	//	cout << ">maxVal ";
	//else
			cout << ">";
	};
	cin.clear();
}
