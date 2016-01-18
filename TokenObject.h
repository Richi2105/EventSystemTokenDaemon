/*
 * TelegramToken.h
 *
 *  Created on: Jan 10, 2016
 *      Author: richard
 */

#ifndef TOKENOBJECT_H_
#define TOKENOBJECT_H_

#include <OS_DEF.h>

#include <Serializeable.h>
#include <constants.h>

#include "FunctionDescription.h"

#include <string>

namespace TokenDaemon {

/**
 * this object is passed to a token daemon to identify the next client in turn and it's function to call
 */
class Token_Object: public Serializeable {
public:
	static const int TOKEN_NEXT = 30;

	/**
	 * initializes a Token_Object with the uid of the next client in turn
	 * @param uid: the Unique Identification Nr of the client in turn
	 * @param func: the (optional) function to be called of the client
	 */
	Token_Object(std::string uid, Function_Description* func_desc = nullptr);
	Token_Object();
	virtual ~Token_Object();

	void setNextClient(std::string uid);
	void setFunction(Function_Description* func_desc);

	char* getNextClient();
	Function_Description* getFunction();

	virtual int getSerializedSize();
	virtual int serialize(void* const data);
	virtual int deserialize(void const * const data);

private:
	int8 nextClient[UNIQUEID_SIZE];
	Function_Description* func_desc;
};

} /* namespace TokenDaemon */

#endif /* TOKENOBJECT_H_ */
