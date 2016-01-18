/*
 * TokenConfig.h
 *
 *  Created on: Jan 11, 2016
 *      Author: richard
 */

#ifndef TOKENCONFIG_H_
#define TOKENCONFIG_H_

#include <OS_DEF.h>

#include <Serializeable.h>
#include <constants.h>

#include <string>

namespace TokenDaemon {

/**
 * this class configures the tokendaemon. The Daemons's name must be known (send via Telegram_Object to tokendaemon's id
 */
class Token_Config: public Serializeable {
public:
	static const int TOKEN_CONFIG;

	/**
	 * initializes Token_Config
	 * @param demux: sets the direction of telegrams through the daemon
	 * 		-false: multiple inputs, one output (multiplex): only the client with fitting UID passed
	 * 		 by a token_Object telegram gets to write to the output
	 * 		 -true: one input, multiple outputs (demultiplex): only the client with fitting UID gets
	 * 		  the telegram sent by input
	 * @param client: the client to which the telegrams will be put through if demux is set to false (multiplex mode)
	 * 				  in demux mode, value of client is ignored
	 */
	Token_Config(bool demux, std::string client = "");

	/**
	 * for initializing as receiving object
	 */
	Token_Config();
	virtual ~Token_Config();

	void setDemultiplexing(bool demux);
	void setOutputClient(std::string outputClient);

	bool isDemultiplexing();
	char* getOutputClient();

	virtual int getSerializedSize();
	virtual int serialize(void* const data);
	virtual int deserialize(void const * const data);

private:
	int8 demux;
	int8 client[UNIQUEID_SIZE];
};

} /* namespace TokenDaemon */

#endif /* TOKENCONFIG_H_ */
