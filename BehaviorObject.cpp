/*
 * BehaviorObject.cpp
 *
 *  Created on: Jan 13, 2016
 *      Author: richard
 */

#include "BehaviorObject.h"

namespace TokenDaemon {

//const int Behavior_Object::BEHAVIOR = 35;

Behavior_Object::Behavior_Object(std::string tokenID, std::string uid_onCancel, std::string uid_onSuccess, Function_Description* func_onCancel, Function_Description* func_onSuccess)
{
	memset(this->tokenAddress, 0, UNIQUEID_SIZE);
	memcpy(this->tokenAddress, tokenID.c_str(), UNIQUEID_SIZE < tokenID.size() ? UNIQUEID_SIZE : tokenID.size());

	memset(this->on_Cancel_uid, 0, UNIQUEID_SIZE);
	memcpy(this->on_Cancel_uid, uid_onCancel.c_str(), UNIQUEID_SIZE < uid_onCancel.size() ? UNIQUEID_SIZE : uid_onCancel.size());

	memset(this->on_Success_uid, 0, UNIQUEID_SIZE);
	memcpy(this->on_Success_uid, uid_onSuccess.c_str(), UNIQUEID_SIZE < uid_onSuccess.size() ? UNIQUEID_SIZE : uid_onSuccess.size());

	this->on_Cancel = func_onCancel;
	this->on_Success = func_onSuccess;
}

Behavior_Object::Behavior_Object() {
	memset(this->on_Cancel_uid, 0, UNIQUEID_SIZE);
	memset(this->on_Success_uid, 0, UNIQUEID_SIZE);
	memset(this->tokenAddress, 0, UNIQUEID_SIZE);

	this->on_Cancel = new Function_Description();
	this->on_Success = new Function_Description();
}

Behavior_Object::~Behavior_Object() {
	// TODO Auto-generated destructor stub
}


char* Behavior_Object::getUID_onSuccess()
{
	return this->on_Success_uid;
}
char* Behavior_Object::getUID_onCancel()
{
	return this->on_Cancel_uid;
}
char* Behavior_Object::getTokenID()
{
	return this->tokenAddress;
}

Function_Description* Behavior_Object::getFunc_onSuccess()
{
	return this->on_Success;
}
Function_Description* Behavior_Object::getFunc_onCancel()
{
	return this->on_Cancel;
}

int Behavior_Object::getSerializedSize()
{
	int size = 0;
	size += sizeof(this->on_Cancel_uid[0]) * UNIQUEID_SIZE;
	size += sizeof(this->on_Success_uid[0]) * UNIQUEID_SIZE;
	size += sizeof(this->tokenAddress[0]) * UNIQUEID_SIZE;
	size += this->on_Cancel->getSerializedSize();
	size += this->on_Success->getSerializedSize();
	return size;
}
int Behavior_Object::serialize(void* const data)
{
	MEMUNIT* data2 = (MEMUNIT*)data;
	packNData(data2, this->on_Cancel_uid, UNIQUEID_SIZE);
	packNData(data2, this->on_Success_uid, UNIQUEID_SIZE);
	packNData(data2, this->tokenAddress, UNIQUEID_SIZE);

	data2 += this->on_Cancel->serialize(data2);
	data2 += this->on_Success->serialize(data2);
	return this->getSerializedSize();
}
int Behavior_Object::deserialize(void const * const data)
{
	const MEMUNIT* data2 = (MEMUNIT*)data;
	unpackNData(data2, this->on_Cancel_uid, UNIQUEID_SIZE);
	unpackNData(data2, this->on_Success_uid, UNIQUEID_SIZE);
	unpackNData(data2, this->tokenAddress, UNIQUEID_SIZE);

	data2 += this->on_Cancel->deserialize(data2);
	data2 += this->on_Success->deserialize(data2);
	return this->getSerializedSize();
}

} /* namespace TokenDaemon */
