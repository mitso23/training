#ifndef PULL_PUSH_PATTERN_H_
#define PULL_PUSH_PATTERN_H_

#include <zhelpers.h>
#include <zmq.hpp>

unsigned numberTasks= 100;

unsigned long long verifySum(unsigned number)
{
	unsigned long long sum= 0;
	for (unsigned int i=0; i< number; ++i)
	{
		sum+= i;
	}

	return sum;
}

// Task ventilator
// Binds PUSH socket to tcp://localhost:5557
// Sends batch of tasks to workers via that socket
int ventilator()
{
	void *context = zmq_ctx_new();

	// Socket to send messages on
	void *sender = zmq_socket(context, ZMQ_PUSH);
	zmq_bind(sender, "tcp://*:5557");

	// Socket to send start of batch message on
	void *sink = zmq_socket(context, ZMQ_PUSH);
	zmq_connect(sink, "tcp://localhost:5558");

	printf("Sending tasks to workers...\n");

	// The first message is "0" and signals start of batch
	//s_send(sink, (char*)"0");

	//NOTE we could possibly sit and wait here waiting for some workers to connect before proceeding
	//If we start straight away then the first worker will get all the traffic

	char string[10];
	for (unsigned task_nbr = 0; task_nbr < numberTasks; task_nbr++)
	{
		sprintf(string, "%d", task_nbr);
		s_send(sender, string);
	}

	sleep(1); // Give 0MQ time to deliver
	zmq_close(sink);
	zmq_close(sender);
	zmq_ctx_destroy(context);
	return 0;

}

// Connects PUSH socket to tcp://localhost:5558
// Sends results to sink via that socket
int  worker(int id)
{
	// Socket to receive messages on
	void *context = zmq_ctx_new();
	void *receiver = zmq_socket(context, ZMQ_PULL);
	zmq_connect(receiver, "tcp://localhost:5557");

	// Socket to send messages to
	void *sender = zmq_socket(context, ZMQ_PUSH);
	zmq_connect(sender, "tcp://localhost:5558");

	// Process tasks forever
	while (1)
	{
		char *string = s_recv(receiver);
		//printf("Worker %d received %s\n", id, string); // Show progress
		fflush (stdout);
		s_send(sender, string); // Send results to sink
	}

	zmq_close(receiver);
	zmq_close(sender);
	zmq_ctx_destroy(context);
	return 0;

}


int sink()
{
	// Prepare our context and socket
	void *context = zmq_ctx_new();
	void *receiver = zmq_socket(context, ZMQ_PULL);
	zmq_bind(receiver, "tcp://*:5558");
	// Wait for start of batch

	//s_recv(receiver);

	// Start our clock now
	int64_t start_time = s_clock();
	unsigned long long sum= 0;

	for (unsigned task_nbr = 0U; task_nbr < numberTasks; ++task_nbr)
	{
		char *string = s_recv(receiver);
		int value=0;
		sscanf(string, "%d", &value);
		sum+=value;
		//printf("SINK: received value %d\n", value);

	}

	// Calculate and report duration of batch
	printf("Total elapsed time: %d msec\n", (int) (s_clock() - start_time));
	printf("Total sum is %llu expected is %llu\n", sum, verifySum(numberTasks));
	zmq_close(receiver);
	zmq_ctx_destroy(context);
	return 0;
}



#endif
