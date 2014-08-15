#include "ManagingThreads.h"
#include "SharingDataThreads.h"
#include "Synchronization.h"
#include "MemoryModel.h"

int main()
{
	//NOTE: new way of initializing
	//std::thread t {backGroundTask()};
	//t.join();
	//std::thread t { testArgument, 1, "Hello" };
	//t.join();

	//NOTE: destructor of Noisy will be called when thread is terminated
	//scopeTest();
	//sleep(6);

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
	my_stack<int> stack;

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

	assert(z.load()!=0);
#endif


}


