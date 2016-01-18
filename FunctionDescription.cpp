/*
 * FunctionDescription.cpp
 *
 *  Created on: Jan 12, 2016
 *      Author: richard
 */

#include "FunctionDescription.h"

namespace TokenDaemon {

Function_Description::Function_Description(std::string func_desc) {
	memset(this->func_desc, 0, FUNCTIONDESCRIPTION_SIZE);
	memcpy(this->func_desc, func_desc.c_str(), FUNCTIONDESCRIPTION_SIZE < func_desc.size() ? FUNCTIONDESCRIPTION_SIZE : func_desc.size());
}

Function_Description::Function_Description()
{
	memset(this->func_desc, 0, FUNCTIONDESCRIPTION_SIZE);
}

Function_Description::~Function_Description() {
	// TODO Auto-generated destructor stub
}

char* Function_Description::getFunctionDescription()
{
	return this->func_desc;
}

void Function_Description::setFunctionDescription(std::string func_desc)
{
	memset(this->func_desc, 0, FUNCTIONDESCRIPTION_SIZE);
	memcpy(this->func_desc, func_desc.c_str(), FUNCTIONDESCRIPTION_SIZE < func_desc.size() ? FUNCTIONDESCRIPTION_SIZE : func_desc.size());
}

int Function_Description::getSerializedSize()
{
	printf("Function_Description::getSerializedSize()\n");
	int size = 0;
	size += sizeof(this->func_desc[0]) * FUNCTIONDESCRIPTION_SIZE;
	return size;
}
int Function_Description::serialize(void* const data)
{
	MEMUNIT* data2 = (MEMUNIT*)data;
	packNData(data2, this->func_desc, FUNCTIONDESCRIPTION_SIZE);
	return this->getSerializedSize();
}
int Function_Description::deserialize(void const * const data)
{
	const MEMUNIT* data2 = (MEMUNIT*)data;
	unpackNData(data2, this->func_desc, FUNCTIONDESCRIPTION_SIZE);
	return this->getSerializedSize();
}

} /* namespace TokenDaemon */
