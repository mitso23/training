#ifndef TESTQUEUE_H_
#define TESTQUEUE_H_

DECLARE_QUEUE_TYPE(int)
DECLARE_QUEUE(int,myqueue)
DECLARE_QUEUE_FUNCTIONS(int)


void addElementsTest()
{
	for(int i=0; i< 5; ++i)
	{
		queue_push_back(&myqueue, i);
	}
}

void displayElementsTest()
{
	while(!queue_is_empty(&myqueue))
	{
		int value;
		queue_pop_back(&myqueue, &value);

		std::cout << "data is: " << value << std::endl;
	}
}


#endif /* TESTQUEUE_H_ */
