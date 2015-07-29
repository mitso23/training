#ifndef REQUEST_BROKER_REPLY_H_
#define REQUEST_BROKER_REPLY_H_

#include <zhelpers.h>
#include <zmq.hpp>

int request_to_router()
{
	void *context = zmq_ctx_new();
	// Socket to talk to server
	void *requester = zmq_socket(context, ZMQ_REQ);
	zmq_connect(requester, "tcp://localhost:5559");
	int request_nbr;

	for (request_nbr = 0; request_nbr != 10; request_nbr++)
	{
		s_send(requester, (const char*)"Hello");
		char *string = s_recv(requester);
		printf("Received reply %d [%s]\n", request_nbr, string);
		free(string);
	}

	zmq_close(requester);
	zmq_ctx_destroy(context);
	return 0;

}

int broker_proxy()
{
	void *context = zmq_ctx_new ();

	 // Socket facing clients
	 void *frontend = zmq_socket (context, ZMQ_ROUTER);
	 int rc = zmq_bind (frontend, "tcp://*:5559");
	 assert (rc == 0);

	 // Socket facing services
	 void *backend = zmq_socket (context, ZMQ_DEALER);
	 rc = zmq_bind (backend, "tcp://*:5560");
	 assert (rc == 0);

	 // Start the proxy
	 zmq_proxy (frontend, backend, NULL);

	 // We never get here...
	 zmq_close (frontend);
	 zmq_close (backend);
	 zmq_ctx_destroy (context);
	 return 0;

}

int reply_to_dealer()
{
	void *context = zmq_ctx_new();

	// Socket to talk to clients
	void *responder = zmq_socket(context, ZMQ_REP);
	zmq_connect(responder, "tcp://localhost:5560");

	while (1)
	{
		// Wait for next request from client
		char *string = s_recv(responder);
		printf("Received request: [%s]\n", string);
		free(string);
		// Do some 'work'
		sleep(1);
		// Send reply back to client
		s_send(responder, (const char*)"World");
	}

	// We never get here, but clean up anyhow
	zmq_close(responder);
	zmq_ctx_destroy(context);
	return 0;
}

#endif
