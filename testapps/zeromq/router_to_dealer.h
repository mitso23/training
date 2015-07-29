#ifndef ROUTER_TO_DEALER_H_
#define ROUTER_TO_DEALER_H_

#define _NBR_WORKERS 2

static void *_worker_task(void *args)
{
	void *context = zmq_ctx_new();
	void *worker = zmq_socket(context, ZMQ_DEALER);
	s_set_id(worker); // Set a printable identity
	zmq_connect(worker, (const char*)"tcp://localhost:5671");
	int total = 0;
	while (1)
	{

		// Tell the broker we're ready for work
		s_send(worker, (char*)"Hi Boss 1");

		//We should be able to send another message as well now
		if (s_send(worker, (char*)"Hi Boss 2") < 0)
		{
			printf("Failed to send message \n");
		}

		// Get workload from broker, until finished
		char *workload = s_recv(worker);
		printf("Worker: thread received %s \n", workload);
		int finished = (strcmp(workload, "Fired!") == 0);
		free(workload);
		if (finished)
		{
			printf("Completed: %d tasks\n", total);
			break;
		}
		total++;
		// Do some random work
		s_sleep(randof (500) + 1);
	}

	zmq_close(worker);
	zmq_ctx_destroy(context);
	return NULL;
}

int router_to_dealer()
{
	//Start the worker ahead of time
	int worker_nbr;
	for (worker_nbr = 0; worker_nbr < _NBR_WORKERS; worker_nbr++)
	{
		pthread_t worker;
		pthread_create(&worker, NULL, _worker_task, NULL);
	}

	sleep(1);

	//start the router
	void *context = zmq_ctx_new();
	void *broker = zmq_socket(context, ZMQ_ROUTER);
	zmq_bind(broker, "tcp://*:5671");
	srandom((unsigned) time(NULL));
	std::cout << "started up router " << std::endl;


	// Run for five seconds and then tell workers to end
	int64_t end_time = s_clock() + 5000;
	int workers_fired = 0;
	while (1)
	{
		// Next message gives us least recently used worker
		char *identity = s_recv(broker);
		std::cout << "Router: received from worker id " << (char*)identity << std::endl;
		s_sendmore(broker, identity);
		free(identity);
		char* data= s_recv(broker); // Response from worker
		std::cout << "Router: received data is " << (char*)data << std::endl;

		// Encourage workers until it's time to fire them
		if (s_clock() < end_time)
			s_send(broker, (char*)"Work harder");
		else
		{
			s_send(broker, (char*)"Fired!");
			if (++workers_fired == NBR_WORKERS)
				break;
		}
	}
	zmq_close(broker);
	zmq_ctx_destroy(context);
	return 0;
}

#endif /* ROUTER_TO_DEALER_H_ */
