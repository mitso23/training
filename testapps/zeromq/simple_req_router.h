#ifndef SIMPLER_REQ_ROUTER_H_
#define SIMPLER_REQ_ROUTER_H_


#include <zhelpers.h>
#include <zmq.hpp>

void simple_req_router()
{
	void *context = zmq_ctx_new();
	void *sink = zmq_socket(context, ZMQ_ROUTER);
	zmq_bind(sink, "inproc://example");

	// First allow 0MQ to set the identity
	void *anonymous = zmq_socket(context, ZMQ_REQ);
	zmq_connect(anonymous, "inproc://example");
	s_send(anonymous, "ROUTER uses a generated UUID");
	s_dump(sink);

	// Then set the identity ourselves
	void *identified = zmq_socket(context, ZMQ_REQ);
	zmq_setsockopt(identified, ZMQ_IDENTITY, "PEER2", 5);
	zmq_connect(identified, "inproc://example");
	s_send(identified, "ROUTER socket uses REQ's socket identity");
	s_dump(sink);

	zmq_close(sink);
	zmq_close(anonymous);

	zmq_close(identified);
	zmq_ctx_destroy(context);

}

#endif /* SIMPLER_REQ_ROUTER_H_ */
