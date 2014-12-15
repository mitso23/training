#include "LockBasedDesign.h"

Threadsafe_queue<int> threadSafeQueue;
FineGrainLockQueue<int> fineGrainLockQueue;

#define NUM_ITEMS 10

void producer_thread()
{
	for(int i=0; i< NUM_ITEMS; ++i)
	{
		 //std::this_thread::sleep_for(std::chrono::seconds(1));
#if 0
		threadSafeQueue.push(std::make_shared<int>(i));
#else
		fineGrainLockQueue.push(i);
#endif
	}

	std::cout << "Finished pushing items" << std::endl;
}

void consumer_thread()
{
	//std::this_thread::sleep_for(std::chrono::seconds(1));
	while (true)
	{
#if 0
		auto value= threadSafeQueue.wait_pop();
#else
		auto value= 0;
		fineGrainLockQueue.wait_pop(value);
#endif
		//std::cout << " received value " << *value << std::endl;

		if (value == NUM_ITEMS - 1)
		{
			break;
		}
	}
}

#define NUM_ELEMENTS_HASH_TABLE 10
threadsafe_lookup_table<int, int> table(NUM_ELEMENTS_HASH_TABLE);
thread_safe_map<int,int> table2;
#define USE_OPTIMISED_HASH

void hash_lookup_thread()
{
	RandomGenerator generator(NUM_ELEMENTS_HASH_TABLE);
	int randomNumber = generator.generate();

	for (int i = 0; i < NUM_ELEMENTS_HASH_TABLE; ++i)
	{
		int default_value = -1;
#ifdef USE_OPTIMISED_HASH
		table.value_for(randomNumber, default_value);
#else
		table2.value_for(randomNumber, default_value);
#endif

	}

	std::cout << "Finished lookup" << std::endl;
}

void hash_insert_thread()
{
	for (int i = 0; i < NUM_ELEMENTS_HASH_TABLE; ++i)
	{
#ifdef USE_OPTIMISED_HASH
		table.add_or_update_mapping(i, i * 2);
#else
		table2.add_or_update_mapping(i, i * 2);
#endif
	}

	std::cout << "Finished inserting" << std::endl;
}
