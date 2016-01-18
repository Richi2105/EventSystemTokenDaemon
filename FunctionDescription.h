/*
 * FunctionDescription.h
 *
 *  Created on: Jan 12, 2016
 *      Author: richard
 */

#ifndef FUNCTIONDESCRIPTION_H_
#define FUNCTIONDESCRIPTION_H_

#include <Serializeable.h>
#include <constants.h>

#include <string>

namespace TokenDaemon {

class Function_Description: public Serializeable {
public:
	Function_Description(std::string func_desc);
	Function_Description();
	virtual ~Function_Description();

	char* getFunctionDescription();
	void setFunctionDescription(std::string func_desc);

	virtual int getSerializedSize();
	virtual int serialize(void* const data);
	virtual int deserialize(void const * const data);

private:
	int8 func_desc[FUNCTIONDESCRIPTION_SIZE];
};

} /* namespace TokenDaemon */

#endif /* FUNCTIONDESCRIPTION_H_ */
