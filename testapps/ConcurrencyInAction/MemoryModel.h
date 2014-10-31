#include<atomic>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <vector>
#include <assert.h>

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

void testAtomicBool();

void atomicPointers();

void reader_thread();

void writer_thread();


void write_x();

void write_y();

void read_x_then_y();

void read_y_then_x();


void thread_1();

void thread_2();

void thread_3();



void create_x();
void use_x();

void populate_queue();

void consume_queue_items();


struct read_values;

void increment(std::atomic<int>* var_to_inc, read_values* values, const std::string& str);

void read_vals(read_values* values);

void print(read_values* v);

void print2();

#endif /* MEMORYMODEL_H_ */
