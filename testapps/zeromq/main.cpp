#include "request_reply_pattern.h"
#include "publish_subscribe_pattern.h"
#include "pull_push_pattern.h"
#include "simple_req_router.h"
#include "router_to_req.h"
#include "router_to_dealer.h"
#include "request_broker_reply.h"

#include <iostream>
#include <functional>
#include <thread>
#include <utils/Noisy.h>


void testRequestReplyPattern()
{
	//NOTE: If a client sends a message to the server and the server is not up the message will be stored and send to the client once the
	// the server is up. If a server is re-started the client fails to re-connect
	std::thread client1 { client_request_reply, 1};
	std::thread client2 { client_request_reply, 2};
	sleep(2);
	std::thread server { server_request_reply };

	client1.join();
	client2.join();
	server.join();
}

void testPublishSubscribePatter()
{
	std::thread client1 { receiver};
	std::thread client2 { receiver};
	std::thread client3 { receiver};
	sleep(1);
	std::thread server { publisher };

	client1.join();
	server.join();

	std::cout << "Finished " << std::endl;
}

void testPushPullPattern()
{
	std::thread _ventilator { ventilator };
	std::thread _worker1 { worker, 1 };
	std::thread _worker2 { worker, 2 };
	std::thread _sink { sink };

	_ventilator.join();
	_worker1.join();
	_worker2.join();
	_sink.join();
}

void requestBrokerReplyPatter()
{
	std::thread _request { request_to_router };
	std::thread _broker  { broker_proxy };
	std::thread _reply   { reply_to_dealer };

	_request.join();
	_broker.join();
	_reply.join();
}

int main(int argc, char* argv[])
{
	//testRequestReplyPattern();
	//testPublishSubscribePatter();
	//testPushPullPattern();
	//simple_req_router();
	//router_to_req();
	//router_to_dealer();
	requestBrokerReplyPatter();
}
