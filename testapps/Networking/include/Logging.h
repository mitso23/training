#include <chrono>
#include <string.h>
#include <iostream>
#include <mutex>

template<typename T>
void PrintArg(T&& arg)
{
	std::cout << arg << " ";
}

auto GetReferenceTime() -> decltype(std::chrono::steady_clock::now());

template<typename ...Args>
void PrintArgs(Args&& ... args)
{
	static std::mutex m;
	std::lock_guard<std::mutex> l {m};
	auto current = std::chrono::steady_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(current - GetReferenceTime());
	std::cout << "timestamp: " << duration.count() << " ";

	(..., PrintArg(args));
	std::cout << std::endl;
}

#define _FILE_ strrchr (__FILE__, '/') ? strstr(__FILE__, strrchr(__FILE__, '/') + 1) : __FILE__

#define LOGE(args...) PrintArgs("file:", _FILE_, "line:", __LINE__, "function:", __FUNCTION__, args)
#define LOGI(args...) //PrintArgs("file:", _FILE_, "line:", __LINE__, "function:", __FUNCTION__, args)
#define LOGD(args...) //PrintArgs("file:", _FILE_, "line:", __LINE__, "function:", __FUNCTION__, args)