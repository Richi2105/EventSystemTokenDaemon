/*
 * TokenConfig.cpp
 *
 *  Created on: Jan 11, 2016
 *      Author: richard
 */

#include "TokenConfig.h"

namespace TokenDaemon {

const int Token_Config::TOKEN_CONFIG = 31;

Token_Config::Token_Config(bool demux, std::string client) {
	memset(this->client, 0, UNIQUEID_SIZE);
	memcpy(this->client, client.c_str(), UNIQUEID_SIZE < client.size() ? UNIQUEID_SIZE : client.size());

	if (demux)
		this->demux = 1;
	else
		this->demux = 0;
}

Token_Config::Token_Config()
{
	memset(this->client, 0, UNIQUEID_SIZE);
	this->demux = 0;
}

Token_Config::~Token_Config() {
	// TODO Auto-generated destructor stub
}

void Token_Config::setDemultiplexing(bool demux)
{
	if (demux)
		this->demux = 1;
	else
		this->demux = 0;
}
void Token_Config::setOutputClient(std::string outputClient)
{
	memset(this->client, 0, UNIQUEID_SIZE);
	memcpy(this->client, outputClient.c_str(), UNIQUEID_SIZE < outputClient.size() ? UNIQUEID_SIZE : outputClient.size());
}

bool Token_Config::isDemultiplexing()
{
	if (this->demux == 0)
		return false;
	else
		return true;
}

char* Token_Config::getOutputClient()
{
	return this->client;
}

int Token_Config::getSerializedSize()
{
	int size = 0;
	size += sizeof(this->demux);
	size += sizeof(this->client[0]) * UNIQUEID_SIZE;
	return size;
}
int Token_Config::serialize(void* const data)
{
	MEMUNIT* data2 = (MEMUNIT*)data;
	packData(data2, this->demux);
	packNData(data2, this->client, UNIQUEID_SIZE);
	return this->getSerializedSize();
}
int Token_Config::deserialize(void const * const data)
{
	const MEMUNIT* data2 = (MEMUNIT*)data;
	unpackData(data2, this->demux);
	unpackNData(data2, this->client, UNIQUEID_SIZE);
	return this->getSerializedSize();
}

} /* namespace TokenDaemonObject */
