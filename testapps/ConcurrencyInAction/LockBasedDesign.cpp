#include "LockBasedDesign.h"

Threadsafe_queue<int> threadSafeQueue;
FineGrainLockQueue<int> fineGrainLockQueue;

void producer_thread()
{
	for(int i=0; i< 100000; ++i)
	{
#if 0
		threadSafeQueue.push(std::make_shared<int>(i));
#else
		fineGrainLockQueue.push(i);
#endif
	}
}

void consumer_thread()
{
	while (true)
	{

#if 0
		auto value= threadSafeQueue.wait_pop();
#else
		auto value= 0;
		fineGrainLockQueue.wait_pop(value);

#endif
		std::cout << " received value " << value << std::endl;

		if (value == 100000 - 1)
		{
			break;
		}

	}

}
