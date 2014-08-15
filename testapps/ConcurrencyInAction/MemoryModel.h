#include<atomic>

#ifndef MEMORYMODEL_H_
#define MEMORYMODEL_H_

class spin_lock_mutex
{
	spin_lock_mutex() :
			m_atomicFlag(ATOMIC_FLAG_INIT)
	{

	}

	void lock()
	{
		while (m_atomicFlag.test_and_set(std::memory_order_acquire));
	}

	void unlock()
	{
		m_atomicFlag.clear(std::memory_order_release);
	}

private:
	std::atomic_flag m_atomicFlag;
};

void testAtomicBool()
{
	std::atomic<bool> flag;
	bool expected= true;
	flag.store(false);

	//if the value of expected is equal to the flag then do the exchange
	flag.compare_exchange_weak(expected, true);

	std::cout << "flag is " << flag.load() << std::endl;
}


void atomicPointers()
{
	class Foo{};
	Foo some_array[5];
	std::atomic<Foo*> p(some_array);

	Foo* x=p.fetch_add(2);
	assert(x==some_array);
	assert(p.load()==&some_array[2]);

	x=(p-=1);
	assert(x==&some_array[1]);

	assert(p.load()==&some_array[1]);
}

//CLASSIC MEMORY RE-ORDER PROBLEM
std::vector<int> data;
std::atomic<bool> data_ready(false);

void reader_thread()
{
	while (!data_ready.load())
	{
		//std::this_thread::sleep(1);
		usleep(100);
	}

	std::cout << "The answer=" << data[0] << "\n";
}

void writer_thread()
{
	//THE FLAG MIGHT BE SET BEFORE PUSHING THE DATA
	data.push_back(42);
	data_ready.store(true);
}

//SEQUENTIAL ORDERING
#if 0
std::atomic<bool> x,y;
std::atomic<int> z;

void write_x()
{
    x.store(true,std::memory_order_seq_cst);
}
void write_y()
{
    y.store(true,std::memory_order_seq_cst);
}
void read_x_then_y()
{
    while(!x.load(std::memory_order_seq_cst));
    if(y.load(std::memory_order_seq_cst))
        ++z;
}
void read_y_then_x()
{
    while(!y.load(std::memory_order_seq_cst));
    if(x.load(std::memory_order_seq_cst))
        ++z;
}
#endif






#endif /* MEMORYMODEL_H_ */
