/*
 * BehaviorObject.h
 *
 *  Created on: Jan 13, 2016
 *      Author: richard
 */

#ifndef BEHAVIOROBJECT_H_
#define BEHAVIOROBJECT_H_

#include "FunctionDescription.h"

#include <OS_DEF.h>

#include <Serializeable.h>
#include <constants.h>

#include <string>

namespace TokenDaemon {

class Behavior_Object: public Serializeable {
public:
	const static int BEHAVIOR = 35;

	Behavior_Object(std::string tokenID, std::string uid_onCancel, std::string uid_onSuccess, Function_Description* func_onCancel, Function_Description* func_onSuccess);
	Behavior_Object();

	char* getUID_onSuccess();
	char* getUID_onCancel();

	char* getTokenID();

	Function_Description* getFunc_onSuccess();
	Function_Description* getFunc_onCancel();

	virtual ~Behavior_Object();

	virtual int getSerializedSize();
	virtual int serialize(void* const data);
	virtual int deserialize(void const * const data);

private:
	int8 on_Cancel_uid[UNIQUEID_SIZE];
	int8 on_Success_uid[UNIQUEID_SIZE];

	int8 tokenAddress[UNIQUEID_SIZE];

	Function_Description* on_Cancel;
	Function_Description* on_Success;

};

} /* namespace TokenDaemon */

#endif /* BEHAVIOROBJECT_H_ */
