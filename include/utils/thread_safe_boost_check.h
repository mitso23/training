#ifndef THREAD_SAFE_BOOST_CHECK_H_
#define THREAD_SAFE_BOOST_CHECK_H_
#include <boost/test/unit_test.hpp>
#include <mutex>

std::mutex gLock;

#define BOOST_THREAD_SAFE_CHECK(X) \
{\
	std::lock_guard<std::mutex> lock(gLock); \
	BOOST_CHECK(X); \
};\

#endif /* THREAD_SAFE_BOOST_CHECK_H_ */
