/*
 * FunctionContainer.h
 *
 *  Created on: Jan 12, 2016
 *      Author: richard
 */

#ifndef FUNCTIONCONTAINER_H_
#define FUNCTIONCONTAINER_H_

#include "FunctionDescription.h"

#include <string>
#include <vector>

namespace TokenDaemon {

class FunctionContainer {
public:
	FunctionContainer();
	virtual ~FunctionContainer();

	int getSize();
	void add(std::string functionDescription);
	std::string getAt(int index);
	int getIndex(std::string functionDescription);

	Function_Description** getAsList();
	void freeList();

private:
	std::vector<std::string> functionList;
	Function_Description** description;
};

} /* namespace TokenDaemon */

#endif /* FUNCTIONCONTAINER_H_ */
