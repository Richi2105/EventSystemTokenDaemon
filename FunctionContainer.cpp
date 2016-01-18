/*
 * FunctionContainer.cpp
 *
 *  Created on: Jan 12, 2016
 *      Author: richard
 */

#include "FunctionContainer.h"

namespace TokenDaemon {

FunctionContainer::FunctionContainer() {
	this->description = nullptr;
}

FunctionContainer::~FunctionContainer() {
}

int FunctionContainer::getSize()
{
	return this->functionList.size();
}

void FunctionContainer::add(std::string functionDescription)
{
	this->functionList.push_back(functionDescription);
}

std::string FunctionContainer::getAt(int index)
{
	return this->functionList.at(index);
}

int FunctionContainer::getIndex(std::string functionDescription)
{
	int i = 0;
	for (std::string desc : this->functionList)
	{
		if (functionDescription.compare(desc) == 0)
			return i;
		i += 1;
	}
	return -1;
}

Function_Description** FunctionContainer::getAsList()
{
	this->description = (Function_Description**) realloc((void*)this->description, sizeof(Function_Description*) * this->functionList.size());
	Function_Description** data = this->description;
	for (std::string desc : this->functionList)
	{
		*data = new Function_Description(desc);
#ifdef DEBUG_OUT
		printf("%s\n", (*data)->getFunctionDescription());
#endif //DEBUG_OUT
		data++;
	}

	return this->description;
}

void FunctionContainer::freeList()
{
	Function_Description** data = this->description;
	for (int i=0; i<this->functionList.size(); i+=1)
	{
		delete *data;
		data++;
	}
	free(this->description);
}

} /* namespace TokenDaemon */
