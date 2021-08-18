#include "RTPStreaming.h"
#include "Logging.h"

#include <thread>

void NanoSleep(struct timespec& tp)
{
	tp.tv_nsec+= 2*1000*1000;
	while(tp.tv_nsec > 999*1000*1000)
	{
		tp.tv_sec+=1;
		tp.tv_nsec-= 1000*1000*1000;
	}

	//LOGE("seconds", tp.tv_sec, "nanoseconds", tp.tv_nsec);
	clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &tp, NULL);
}

int main(int argc, char* argv[])
{
	RTPStreaming streaming{"enx00000000141d", 8433};

#if 0
	sched_param p;
	p.__sched_priority = 19;
	pthread_setschedparam(pthread_self(), SCHED_FIFO, &p);


	struct timespec tp;
	if (clock_gettime(CLOCK_MONOTONIC, &tp) != 0)
	{
		LOGE("Failed");
		return - 1;
	}

	LOGE("start");
	int correct = 0;
	int wrong = 0;
	std::chrono::milliseconds diff{0};
	for(int i=0; i< 10000; ++i)
	{
		//std::this_thread::sleep_for(std::chrono::milliseconds { 1 });

		auto start = std::chrono::steady_clock::now();
		NanoSleep(tp);

		auto end = std::chrono::steady_clock::now();
		auto l = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		if (l.count() != 2)
		{
			//LOGE("error", l.count());
			++wrong;
		}
		else
		{
			++correct;
		}

		diff+= l;

	}

	LOGE("end", diff.count(), "correct", correct, "wrong", wrong);
#endif
}


