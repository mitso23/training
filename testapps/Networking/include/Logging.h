#include <chrono>
#include <string.h>
#include <iostream>

template<typename T>
void PrintArg(T&& arg)
{
	std::cout << arg << " ";
}

template<typename ...Args>
void PrintArgs(Args&& ... args)
{
	static auto begin =  std::chrono::steady_clock::now();
	auto current = std::chrono::steady_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(current - begin);
	std::cout << "timestamp: " << duration.count() << " ";

	(..., PrintArg(args));
	std::cout << std::endl;
}

#define _FILE_ strrchr (__FILE__, '/') ? strstr(__FILE__, strrchr(__FILE__, '/') + 1) : __FILE__

#define LOGE(args...) PrintArgs("file:", _FILE_, "line:", __LINE__, "function:", __FUNCTION__, args)
#define LOGI(args...) PrintArgs("file:", _FILE_, "line:", __LINE__, "function:", __FUNCTION__, args)
#define LOGD(args...) PrintArgs("file:", _FILE_, "line:", __LINE__, "function:", __FUNCTION__, args)