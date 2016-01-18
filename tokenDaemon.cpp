/*
 * tokenDaemon.cpp
 *
 *  Created on: Jan 10, 2016
 *      Author: richard
 */


#include <EventSystemClient.h>
#include <Logging/LoggerAdapter.h>

#include "TokenObject.h"
#include "TokenConfig.h"

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string>

using namespace EventSystem;
using namespace TokenDaemon;

struct iomux_argument{
	char* tokenName;
};

void* iomux(void* arg)
{
	struct iomux_argument* argument = (struct iomux_argument*) arg;
	bool initialized = false;
	bool direction;	/* true: demux, false: mux */
	char* outputID;
	char* inputID;

	EventSystemClient* esc = new EventSystemClient(argument->tokenName);
	esc->connectToMaster();
	esc->startReceiving();
	LoggerAdapter::initLoggerAdapter(esc);

	void* data = malloc(4096);

	Telegram t("");
	Telegram_Object objTelegram;

	while (true)
	{
		int bytes = esc->receive(data, false);
		t.deserialize(data);

		if (t.getType() == Token_Object::TOKEN_NEXT)
		{
			if (initialized)
			{
				Token_Object* to = new Token_Object();
				objTelegram.deserialize(data, to);

				if (direction)
					outputID = strdup(to->getNextClient());
				else
					inputID = strdup(to->getNextClient());

				objTelegram.setIdentifier(to->getNextClient());
				esc->send(&objTelegram);

				std::string logmessage = "Token: Next Client is ";
				logmessage  += to->getNextClient();
				LoggerAdapter::log(Log::INFO, logmessage);
				delete to;
			}
			else
			{
				LoggerAdapter::log(Log::SEVERE, "Client Sending stuff, Token still not initialized");
			}
		}
		else if (t.getType() == Token_Config::TOKEN_CONFIG)
		{
			if (!initialized)
			{
				Token_Config* tc = new Token_Config();
				objTelegram.deserialize(data, tc);
				direction = tc->isDemultiplexing();
				if (direction)
				{
					inputID = strdup(argument->tokenName);
					/* outputID is defined by Token_next telegram */
				}
				else
				{
					outputID = strdup(tc->getOutputClient());
					/* inputID is defined by Token_next telegram */
				}
				initialized = true;
				delete tc;
				LoggerAdapter::log(Log::INFO, "Token: initialized");
			}
			else
				LoggerAdapter::log(Log::SEVERE, "someone tried to configure Token, is already initialized");

		}

		else
		{
			if (!initialized)
				LoggerAdapter::log(Log::SEVERE, "Client Sending stuff, Token still not initialized");
			else
			{
				if (direction)	//demultiplex
				{
					t.setUniqueDestination(true);
					t.setIdentifier(outputID);
					t.serialize(data);
					esc->send(data, bytes);
				}
				else
				{
					if (strcmp(t.getSourceID(), inputID) == 0)
					{
						t.setUniqueDestination(true);
						t.setIdentifier(outputID);
						t.serialize(data);
						esc->send(data, bytes);
					}
					else
					{
						std::string logmessage = "Client ";
						logmessage += t.getSourceID();
						logmessage += " which hasn't the token tries to send";
						LoggerAdapter::log(Log::INFO, logmessage);
					}
				}
			}
		}
	}

	free(data);
	return (void*) 0;

}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("Usage: tokenDaemon <tokenID1> <tokenID2> ...\n");
		return -1;
	}
	else
	{
		struct iomux_argument* args = (struct iomux_argument*)malloc(sizeof(struct iomux_argument) * (argc -1));
		pthread_t* threads = (pthread_t*)malloc(sizeof(pthread_t) * (argc -1));
		for (int i=1; i<argc; i+=1)
		{
			((struct iomux_argument*) args)->tokenName = argv[i];
			pthread_create(threads, NULL, iomux, args);
			args ++;
			threads ++;
		}
		while (true)
			sleep(1000);
	}

}


