#define BOOST_TEST_MODULE stringtest
#define BOOST_TEST_DYN_LINK 1
#include <containers/thread_safe_hash.h>
#include <containers/thread_safe_list.h>
#include <containers/lock_free_stack.h>
#include <utils/thread_safe_boost_check.h>
#include <containers/thread_safe_queue.h>
#include <thread>

BOOST_AUTO_TEST_SUITE (thread_safe_cont_suite) // name of the test suite is stringtest

threadsafe_lookup_table<unsigned, unsigned> hash;
FineGrainLockQueue<unsigned> queue;
lock_free_stack<unsigned> stack;

void addElementsQueue(unsigned int start, unsigned end)
{
	for(auto i=start; i<= end; i++)
	{
		queue.push(i);
	}
}

void readElementsQueue(unsigned int start, unsigned end)
{
	for(auto i=start; i<= end; i++)
	{
		unsigned int data;
		queue.wait_pop(data);

		BOOST_CHECK(data == i);
	}
}

void addElementsStack(unsigned int start, unsigned end)
{
	for(auto i=start; i<= end; ++i)
	{
		stack.push(i);
	}
}

void readElementsStack(unsigned int start, unsigned end)
{
	for(auto i=end; ; --i)
	{
		unsigned int data;
		while(!stack.pop(data));

		BOOST_CHECK((data <=end && data >=start));

		if (i == 0)
		{
			break;
		}
	}
}

void addToHashTableThread(unsigned numItems, unsigned start)
{
	for(auto i=start; i< start + numItems; ++i)
	{
		hash.add_or_update_mapping(i, i);
	}
}

BOOST_AUTO_TEST_CASE (thread_safe_hash)
{
	std::thread t1 { addToHashTableThread, 1000, 0 };
	t1.join();
	std::thread t2 { addToHashTableThread, 1000, 1000 };
	t2.join();

	BOOST_THREAD_SAFE_CHECK(hash.get_size() == 2000);

	for(unsigned int i=0; i< 2000; ++i)
	{
		BOOST_CHECK(hash.value_for(i, 0xFFFFFFFF) != 0xFFFFFFFF);
	}

	for(unsigned int i=0; i< 2000; ++i)
	{
		hash.remove_mapping(i);
	}

	BOOST_THREAD_SAFE_CHECK(hash.get_size() == 0);
}

BOOST_AUTO_TEST_CASE(thread_safe_list)
{
	int count= 5;
	threadsafe_list<int> list;
	list.push_front(1);
	list.push_front(2);
	list.push_front(3);
	list.push_front(4);
	list.push_front(5);

	//iterate through
	list.for_each([&](std::shared_ptr<int> data)
	{
		BOOST_CHECK(*data == count--);
	});

	//Find an element
	{
		auto result = list.find_first_if([](std::shared_ptr<int> data)
		{
			if(*data == 5)
			{
				return true;
			}
			else
			{
				return false;
			}
		});

		BOOST_CHECK(result);
	}

	//Remove an element
	{
		bool result = list.remove_if([](std::shared_ptr<int> data)
		{
			if(*data == 5)
			{
				return true;
			}
			else
			{
				return false;
			}
		});

		BOOST_CHECK(result);
	}
}

BOOST_AUTO_TEST_CASE(lock_free_stack)
{
	std::thread t1 { addElementsStack,  0, 1000};
	std::thread t2 { readElementsStack, 0, 1000};

	t1.join();
	t2.join();
}

BOOST_AUTO_TEST_CASE(thread_safe_queue)
{
	std::thread t1 { addElementsQueue, 0, 1000 };
	std::thread t2 { readElementsQueue, 0, 1000 };

	t1.join();
	t2.join();
}

BOOST_AUTO_TEST_SUITE_END( )
