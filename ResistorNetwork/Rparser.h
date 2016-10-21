#include "Node.h"
#include "Resistor.h"


#ifndef RPARSER_H_
#define RPARSER_H_

/*
#define  MAX_NODE_NUMBER 5000
#define  MAX_RESISTOR_NUMBER 5000
*/

using namespace std;

class Rparser {
private:
	Node * nodes;
	Resistor * resistors;
	//int numberOfUsedResistors;
	//int numberOfUsedNodes;
	//int maxNodes;
	int maxResistors;
	int getAvailableResistorIndex();
	int findResistor(string name);
	int MIN_NODE_NUMBER;
	int MAX_NODE_NUMBER;
	int resCount;
	int insertR(stringstream& getInput);
	int printR(stringstream & getInput);
	int printNode(stringstream & getInput);
	int modifyR(stringstream & getInput);
	int deleteR(stringstream & getInput);
	int maxVal(stringstream & getInput);
public:
	Rparser();
	Rparser(const Rparser& orig);
	virtual ~Rparser();
	void getInput();
};



#endif /* RPARSER_H_ */
