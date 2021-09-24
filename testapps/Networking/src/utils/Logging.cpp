#include "Logging.h"

auto GetReferenceTime() -> decltype(std::chrono::steady_clock::now())
{
	static auto reference = std::chrono::steady_clock::now();
	return reference;
}
