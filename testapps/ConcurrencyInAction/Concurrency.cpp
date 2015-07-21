#include "ManagingThreads.h"
#include "SharingDataThreads.h"
#include "Synchronization.h"
#include "MemoryModel.h"
#include "LockBasedDesign.h"
#include "DesigningConcurrentCode.h"

#include <algorithms/quicksort.h>
#include <libbase/random_generator.h>

#include <map>
#include <utils/utils.h>

int main()
{
	//NOTE: new way of initializing
	//std::thread t {backGroundTask()};
	//t.join();
	//std::thread t { testArgument, 1, "Hello" };
	//t.join();

	//NOTE: destructor of Noisy will be called when thread is terminated
	//scopeTest();
	//std::cout << "Sleeping" << std::endl;
	//sleep(6);
	//std::cout << "Done" << std::endl;
	//NOTE: You must pass it by reference otherwise it will get a reference of the internal copy that the thread gets
	//int x= 1;
	//std::thread t{testArgumentByReference, 1, std::ref(x)};
	//NOTE: A thread is a non copyable object so you have to move it to pass ownership
	//f2(std::move(ts));
	//NOTE: Implicit move
	//f2(std::thread {backGroundTask()});

	//NOTE: Use move semantics to transfer thread ownership
	//scoped_thread thread(std::move(std::thread(Noisy())));


	//NOTE: First the back Ground Task destructor will be called
	//Then we are joining the thread
	//std::thread t { backGroundTask() };
	//thread_guard { t };
	//throw 2;

#if 0

	for(int i=0; i< 1600; ++i)
	{
		stack.push(i);

	}

	while(stack.empty())
	{
		std::cout << stack.topPop() << std::endl;
	}
#endif

#if 0
	std::vector<int> vec= { 1, 1, 1, 1, 1, 1, 1, 1} ;
	int skata= 0;

	typedef std::vector<int>::iterator it;

	parallel_accumulate<it, int> acc;
	acc(vec.begin(), vec.end(), skata);
#endif

#if 0
	std::thread::id masterThread;
	masterThread= std::this_thread::get_id();
	std::cout << "Master Thread is " << masterThread << " this thread id " << std::this_thread::get_id() << std::endl;
#endif

	//scoped_thread consumerThread { std::move(std::thread(data_preparation_thread)) };
	//scoped_thread producerThread { std::move(std::thread(data_processing_thread)) };

	//workerThread2();

	//scoped_thread gui{ std::move(std::thread(guiThread)) };
	//auto future= postGUIThread(find_the_answer_to_ltuae);
	//future.get();

	//scoped_thread thread { std::move(std::thread(setPromise))};
	//scoped_thread thread2 { std::move(std::thread(getFuture))};

#if 0
	std::list<int> data{ 1, 2, 3, 6, 5 };
	sequential_quick_sort(data);

	for (auto it = data.begin(); it != data.end(); ++it)
	{
		std::cout << *it << std::endl;
	}
#endif

	//testAtomicBool();

#if 0
	extern std::atomic<bool> x,y;
	extern std::atomic<int> z;
	x=false;
	y=false;
	z=0;
	std::thread a(write_x);
	std::thread b(write_y);
	std::thread c(read_x_then_y);
	std::thread d(read_y_then_x);
	a.join();
	b.join();
	c.join();
	d.join();

	//std::cout << "z:" << z.load() << std::endl;
	return z.load() != 0 ? 0 : 1;
	assert(z.load()!=0);
#endif

#if 0
	scoped_thread t1{ std::move(std::thread(thread_1)) };
	scoped_thread t2{ std::move(std::thread(thread_2)) };
	scoped_thread t3{ std::move(std::thread(thread_3)) };
#endif

#if 0
	scoped_thread t1{ std::move(std::thread(create_x)) };
	scoped_thread t2{ std::move(std::thread(use_x)) };
#endif

#if 0
	scoped_thread t1{ std::move(std::thread(populate_queue)) };
	scoped_thread t2{ std::move(std::thread(consume_queue_items)) };
	scoped_thread t3{ std::move(std::thread(consume_queue_items)) };
	//scoped_thread t4{ std::move(std::thread(consume_queue_items)) };
#endif

#if 0
	extern std::atomic<int> x, y, z;
	extern std::atomic<bool> go;

	unsigned int const loop_count= 10;

	extern read_values values1[loop_count];
	extern read_values values2[loop_count];
	extern read_values values3[loop_count];
	extern read_values values4[loop_count];
	extern read_values values5[loop_count];

	std::thread t1(increment,&x,values1, "x");
	std::thread t2(increment,&y,values2, "y");
	std::thread t3(increment,&z,values3, "z");
	std::thread t4(read_vals,values4);
	std::thread t5(read_vals,values5);
	go=true;

	t5.join();
	t4.join();
	t3.join();
	t2.join();
	t1.join();

	print(values1);
	print(values2);
	print(values3);
	print(values4);
	print(values5);
#endif

#if 0
	scoped_thread t1(std::move(std::thread(producer_thread)));
	scoped_thread t2(std::move(std::thread(consumer_thread)));
#endif

#if 0
	{
		scoped_thread t2(std::move(std::thread(hash_insert_thread)));
	}


	scoped_thread t2(std::move(std::thread(hash_lookup_thread)));
	scoped_thread t3(std::move(std::thread(hash_lookup_thread)));
#endif


	//A parallel accumulate function
#if 0
	std::vector<int> vec= { 1, 2, 3, 4 ,5 ,6, 7 };
	typedef struct parallel_accumulate<typename std::vector<int>::iterator, int> parallel_int;

	parallel_int parallel_accumulate;
	int result= parallel_accumulate(vec.begin(), vec.end());
	std::cout << "Result is " << result << std::endl;
#endif

	std::vector<int> vec;
	unsigned const int size= 500000;
	vec.reserve(size);
	RandomGenerator gen(size);

	for (unsigned int i=0; i< size; ++i)
	{
		//auto randomValue= gen.generate();
		vec.push_back((i % 100));
	}

	//print_cont(vec);
	quickSort(vec, 0, vec.size() - 1);
	//print_cont(vec);
}


