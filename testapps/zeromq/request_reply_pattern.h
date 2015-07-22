#ifndef REQUEST_REPLY_PATTERN_H
#define REQUEST_REPLY_PATTERN_H

#include <zhelpers.h>
#include <zmq.hpp>
#include <unistd.h>
#include <iostream>

//THE PATTERN
// 1) The client connects to the server
// 2) The client sends a message (request)
// 3) The server receives the request and sends a reply back

int server_request_reply()
{
	zmq::context_t context(1);
	zmq::socket_t socket(context, ZMQ_REP);

	socket.bind("tcp://*:5555");

	for(int i=0; i< 20; ++i)
	{
		zmq::message_t request;
		// Wait for next request from client
		socket.recv(&request);
		std::cout << "Server: Received " << (char*)request.data() << std::endl;

		sleep(1);

		// Send reply back to client
		zmq::message_t reply(request.size());
		memcpy((void *) reply.data(), request.data(), request.size());
		socket.send(reply);
	}

	return 0;
}


int client_request_reply(int clientId)
{
	printf("Client: Connecting to hello world server...\n");
	void *context = zmq_ctx_new();
	void *requester = zmq_socket(context, ZMQ_REQ);

	if (zmq_connect(requester, "tcp://localhost:5555") < 0)
	{
		printf("Client failed to connect \n");
	}

	int request_nbr;
	for (request_nbr = 0; request_nbr != 10; request_nbr++)
	{
		char buffer[10];
		char sendbuffer[10];

		sprintf(sendbuffer, "Hello%d", request_nbr);
		printf("Client%d: Sending %s %d...\n", clientId, sendbuffer, request_nbr);

		if (zmq_send(requester, sendbuffer, strlen(sendbuffer) + 1, 0) < 0)
		{
			printf("Client Failed to send \n");
		}

		//sending a second message would fail as the patter expects only one message
#if 0
		//
		if (zmq_send(requester, sendbuffer, strlen(sendbuffer) + 1, 0) < 0)
		{
			printf("Client Failed to send \n");
		}
#endif
		if (zmq_recv(requester, buffer, 10, 0) < 0)
		{
			printf("Client Failed to receive \n");
		}

		printf("Client %d: Received %s\n", clientId, buffer);
	}

	zmq_close(requester);
	zmq_ctx_destroy(context);

	return 0;
}

#endif /* REQUEST_REPLY_PATTERN_H_ */
