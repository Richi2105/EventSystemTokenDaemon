/*
 * TelegramToken.cpp
 *
 *  Created on: Jan 10, 2016
 *      Author: richard
 */

#include "TokenObject.h"

namespace TokenDaemon {

//const int Token_Object::TOKEN_NEXT = 30;

Token_Object::Token_Object(std::string uid, Function_Description* func_desc) {
	memset(this->nextClient, 0, UNIQUEID_SIZE);
	memcpy(this->nextClient, uid.c_str(), UNIQUEID_SIZE < uid.size() ? UNIQUEID_SIZE : uid.size());

	if (func_desc == nullptr)
		this->func_desc = new Function_Description("NULL");
	else
		this->func_desc = func_desc;
}

Token_Object::Token_Object()
{
	memset(this->nextClient, 0, UNIQUEID_SIZE);
	this->func_desc = new Function_Description("NULL");
}

Token_Object::~Token_Object() {
	// TODO Auto-generated destructor stub
}

void Token_Object::setNextClient(std::string uid)
{
	memset(this->nextClient, 0, UNIQUEID_SIZE);
	memcpy(this->nextClient, uid.c_str(), UNIQUEID_SIZE < uid.size() ? UNIQUEID_SIZE : uid.size());
}

void Token_Object::setFunction(Function_Description* func_desc)
{
	this->func_desc = func_desc;
}

char* Token_Object::getNextClient()
{
	return this->nextClient;
}

Function_Description* Token_Object::getFunction()
{
	return this->func_desc;
}

int Token_Object::getSerializedSize()
{
	int size = 0;
	size += sizeof(this->nextClient[0]) * UNIQUEID_SIZE;
	size += sizeof(*this->func_desc);
	return size;
}
int Token_Object::serialize(void* const data)
{
	MEMUNIT* data2 = (MEMUNIT*)data;
	packNData(data2, this->nextClient, UNIQUEID_SIZE);
	data2 += this->func_desc->serialize(data2);
	return this->getSerializedSize();
}
int Token_Object::deserialize(void const * const data)
{
	const MEMUNIT* data2 = (MEMUNIT*)data;
	unpackNData(data2, this->nextClient, UNIQUEID_SIZE);
	data2 += this->func_desc->deserialize(data2);
	return this->getSerializedSize();
}

} /* namespace TokenDaemon */
