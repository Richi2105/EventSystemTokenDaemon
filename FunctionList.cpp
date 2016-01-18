/*
 * FunctionRequest.cpp
 *
 *  Created on: Jan 12, 2016
 *      Author: richard
 */

#include "FunctionList.h"

namespace TokenDaemon {

const int Function_List::REQUEST_ANSWER = 33;

Function_List::Function_List(std::string uid, int numberOfFunctions, Function_Description** descriptions) {
	memset(this->uid, 0, UNIQUEID_SIZE);
	memcpy(this->uid, uid.c_str(), UNIQUEID_SIZE < uid.size() ? UNIQUEID_SIZE : uid.size());

	this->count = (int8) numberOfFunctions;
	this->descriptions = descriptions;
}

Function_List::Function_List()
{
	memset(this->uid, 0, UNIQUEID_SIZE);

	this->count = 0;
	this->descriptions = nullptr;
}

Function_List::~Function_List() {
	// TODO Auto-generated destructor stub
}

char* Function_List::getUID()
{
	return this->uid;
}

Function_Description* Function_List::getFunctionDescription(int nr)
{
	if (nr < this->count)
	{
		printf("Function_List::getFunctionDescription(): %s\n", (*(this->descriptions + nr))->getFunctionDescription());
		return *(this->descriptions + nr);
	}
	else
		return nullptr;
}

int Function_List::getCount()
{
	return this->count;
}

int Function_List::getSerializedSize()
{
	printf("Function_List::getSerializedSize()\n");
	int size = 0;
	size += sizeof(this->uid[0]) * UNIQUEID_SIZE;
	size += sizeof(this->count);
	for (int i=0; i<this->count; i+=1)
		size += this->getFunctionDescription(i)->getSerializedSize();
//	size += (this->descriptions[0])->getSerializedSize() * this->count;

#ifdef DEBUG_OUT
	printf("Function_List::getSerializedSize(): %d\n", size);
#endif //DEBUG_OUT
	return size;
}
int Function_List::serialize(void* const data)
{
	printf("Function_List::serialize()\n");
	MEMUNIT* data2 = (MEMUNIT*)data;
	packNData(data2, this->uid, UNIQUEID_SIZE);
	packData(data2, this->count);

	printf("Function_List::serialize(), data3 init\n");
//	Function_Description* data3 = this->descriptions;
	for (int i=0; i<this->count; i+=1)
	{
		printf("i = %d\n", i);
//		data2 += (this->descriptions + i)->serialize(data2);
		data2 += (this->descriptions[i])->serialize(data2);
/*		data2 += data3->serialize(data2);
		data3++;
*/
	}
	printf("Function_List::serialize(), for loop\n");
	return this->getSerializedSize();
}
int Function_List::deserialize(void const * const data)
{
	const MEMUNIT* data2 = (MEMUNIT*)data;
	unpackNData(data2, this->uid, UNIQUEID_SIZE);
	unpackData(data2, this->count);

	this->descriptions = (Function_Description**)malloc(sizeof(Function_Description*)*this->count);
//	Function_Description* data3 = new Function_Description();
	for (int i=0; i<this->count; i+=1)
	{
		(this->descriptions[i]) = new Function_Description();
		data2 += (this->descriptions[i])->deserialize(data2);
	}
	return this->getSerializedSize();
}

} /* namespace TokenDaemon */
