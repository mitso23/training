#ifndef PUBLISH_SUBSCRIBE_PATTERN_H_
#define PUBLISH_SUBSCRIBE_PATTERN_H_

#include <zhelpers.h>
#include <zmq.hpp>

int publisher()
{
	// Prepare our context and publisher
	void *context = zmq_ctx_new();
	void *publisher = zmq_socket(context, ZMQ_PUB);
	int rc = zmq_bind(publisher, "tcp://*:5556");
	assert(rc == 0);
	rc = zmq_bind(publisher, "ipc://weather.ipc");
	assert(rc == 0);
	// Initialize random number generator
	srandom((unsigned) time(NULL));

	while (1)
	{
		// Get values that will fool the boss
		int zipcode=10001, temperature=0, relhumidity=0;

		// Send message to all subscribers
		char update[20];
		sprintf(update, "%05d %d %d ", zipcode, temperature, relhumidity);
		s_send (publisher, update);
		std::cout << "publishing:" << update << std::endl;
		sleep(1);

	}

	zmq_close(publisher);
	zmq_ctx_destroy(context);
	return 0;

}

int receiver()
{
	// Socket to talk to server
	printf("Collecting updates from weather server...\n");

	void *context = zmq_ctx_new();
	void *subscriber = zmq_socket(context, ZMQ_SUB);

	int rc = zmq_connect(subscriber, "tcp://localhost:5556");
	assert(rc == 0);

	//Register to receive everything
	rc = zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, "", 0);
	assert(rc == 0);

	// Process 100 updates
	int update_nbr;
	long total_temp = 0;
	for (update_nbr = 0; update_nbr < 100; update_nbr++)
	{

		char *string = s_recv (subscriber);
		int zipcode, temperature, relhumidity;
		sscanf(string, "%d %d %d", &zipcode, &temperature, &relhumidity);
		std::cout << "receiving " << string << std::endl;
		total_temp += temperature;
	}

	return 0;
}

#endif
