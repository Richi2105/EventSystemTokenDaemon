/*
 * FunctionRequest.h
 *
 *  Created on: Jan 12, 2016
 *      Author: richard
 */

#ifndef FUNCTIONLIST_H_
#define FUNCTIONLIST_H_

#include <Serializeable.h>
#include <constants.h>

#include "FunctionDescription.h"

#include <string>

namespace TokenDaemon {

/**
 * class for sending a list of functions (actually strings) to someone
 */
class Function_List: public Serializeable {
public:
	const static int REQUEST_ANSWER;

	Function_List(std::string uid, int numberOfFunctions, Function_Description** descriptions);
	Function_List();
	virtual ~Function_List();

	char* getUID();
	Function_Description* getFunctionDescription(int nr);
	int getCount();

	virtual int getSerializedSize();
	virtual int serialize(void* const data);
	virtual int deserialize(void const * const data);

private:
	char uid[UNIQUEID_SIZE];
	Function_Description** descriptions;
	int8 count;
};

} /* namespace TokenDaemon */

#endif /* FUNCTIONLIST_H_ */
