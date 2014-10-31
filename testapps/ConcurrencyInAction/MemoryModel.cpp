/*
 * MemoryModel.cpp
 *
 *  Created on: Sep 13, 2014
 *      Author: dimitrios
 */

#include "MemoryModel.h"

void testAtomicBool()
{
	std::atomic<bool> flag;
	bool expected = true;
	flag.store(false);

	//if the value of expected is equal to the flag then do the exchange
	flag.compare_exchange_weak(expected, true);

	std::cout << "flag is " << flag.load() << std::endl;
}

void atomicPointers()
{
	class Foo
	{
	};
	Foo some_array[5];
	std::atomic<Foo*> p(some_array);

	Foo* x = p.fetch_add(2);
	assert(x == some_array);
	assert(p.load() == &some_array[2]);

	x = (p -= 1);
	assert(x == &some_array[1]);

	assert(p.load() == &some_array[1]);
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

//SEQUENTIAL ORDERING (z will be either 1 or 2 but never 0 with secuential memory access but can be zero with relaxed!!!!!)
//SEQUENTIAL ORDERING means that all threads see the same order of value updates eg x->y or y->x
std::atomic<bool> x, y;
std::atomic<int> z;
#define X_Y_MEMORY_ORDER std::memory_order_relaxed

void write_x()
{
	x.store(true, X_Y_MEMORY_ORDER);
}
void write_y()
{
	y.store(true, X_Y_MEMORY_ORDER);
}
void read_x_then_y()
{
	while (!x.load(X_Y_MEMORY_ORDER));
	if(y.load(X_Y_MEMORY_ORDER))
	++z;
}

void read_y_then_x()
{
	while (!y.load(X_Y_MEMORY_ORDER));
	if(x.load(X_Y_MEMORY_ORDER))
	++z;
}

//AQUIRE RELESE doesn't guarantee global ordering but guarantees that acquire happens after release
std::atomic<int> atomic_data[5];
std::atomic<bool> sync1(false), sync2(false);

void thread_1()
{
	atomic_data[0].store(42, std::memory_order_relaxed);
	atomic_data[1].store(97, std::memory_order_relaxed);
	atomic_data[2].store(17, std::memory_order_relaxed);
	atomic_data[3].store(-141, std::memory_order_relaxed);
	atomic_data[4].store(2003, std::memory_order_relaxed);
	sync1.store(true, std::memory_order_release);//The last store guaranteed to be this one
}

void thread_2()
{
	while (!sync1.load(std::memory_order_acquire))
		;

	sync2.store(true, std::memory_order_release);
}

void thread_3()
{
	while (!sync2.load(std::memory_order_acquire))
		;

	assert(atomic_data[0].load(std::memory_order_relaxed) == 42);
	assert(atomic_data[1].load(std::memory_order_relaxed) == 97);
	assert(atomic_data[2].load(std::memory_order_relaxed) == 17);
	assert(atomic_data[3].load(std::memory_order_relaxed) == -141);
	assert(atomic_data[4].load(std::memory_order_relaxed) == 2003);
}

struct X
{
	int i;
	std::string s;
};

std::atomic<X*> pp;
std::atomic<int> aa;

void create_x()
{
	X* x = new X;
	x->i = 42;
	x->s = "hello";
	aa.store(99, std::memory_order_relaxed);
	pp.store(x, std::memory_order_release);
}

void use_x()
{
	X *x;
	while (!(x = pp.load(std::memory_order_consume)))
		usleep(1000);

	assert(x->i == 42);
	assert(x->s == "hello");

	assert(aa.load(std::memory_order_relaxed) == 99);
}

std::vector<int> queue_data;
std::atomic<int> count;

void populate_queue()
{
	unsigned const number_of_items = 20;
	queue_data.clear();
	for (unsigned i = 0; i < number_of_items; ++i)
	{
		queue_data.push_back(i);
	}

	count.store(number_of_items, std::memory_order_release);
	std::cout << "pop" << std::endl;
}

void consume_queue_items()
{
	while (true)
	{
		int item_index;
		if ((item_index = count.fetch_sub(1, std::memory_order_acquire)) <= 0)
		{
			usleep(100);
			continue;
		}

		//queue_data[item_index]

		std::cout << "t: " << std::this_thread::get_id() << " v: " << item_index << std::endl;
		std::this_thread::yield();

	}

}

#if 0
std::atomic<int> x(0), y(0), z(0);
std::atomic<bool> go(false);

unsigned const loop_count = 10;
struct read_values
{
	int x, y, z;
};
read_values values1[loop_count];
read_values values2[loop_count];
read_values values3[loop_count];
read_values values4[loop_count];
read_values values5[loop_count];

#define MEMORY_MODEL_TEST1 std::memory_order_seq_cst
void increment(std::atomic<int>* var_to_inc, read_values* values, const std::string& str)
{
	while (!go)
	std::this_thread::yield();

	for (unsigned i = 0; i < loop_count; ++i)
	{
		values[i].x = x.load(MEMORY_MODEL_TEST1);
		values[i].y = y.load(MEMORY_MODEL_TEST1);
		values[i].z = z.load(MEMORY_MODEL_TEST1);

		var_to_inc->store(i + 1, MEMORY_MODEL_TEST1);
		std::cout << "Incrementing: " << str << std::endl;
		std::this_thread::yield();
	}
}
void read_vals(read_values* values)
{

	while (!go)
	std::this_thread::yield();
	for (unsigned i = 0; i < loop_count; ++i)
	{
		values[i].x = x.load(MEMORY_MODEL_TEST1);
		values[i].y = y.load(MEMORY_MODEL_TEST1);
		values[i].z = z.load(MEMORY_MODEL_TEST1);
		std::this_thread::yield();
	}
}

void print(read_values* v)
{
	for (unsigned i = 0; i < loop_count; ++i)
	{
		if (i)
		std::cout << ",";
		std::cout << "(" << v[i].x << "," << v[i].y << "," << v[i].z << ")";
	}
	std::cout << std::endl;
}

#endif

