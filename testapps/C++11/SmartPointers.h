#ifndef SMARTPOINTERS_H_
#define SMARTPOINTERS_H_
#include <utility>
#include <memory>

void testUniquePointer()
{
	std::unique_ptr<Noisy> ptr1(new Noisy());

	if (ptr1)
	{
		std::cout << "ptr1 has ownership" << std::endl;
	}

	std::unique_ptr<Noisy> ptr2= std::move(ptr1);

	if (ptr2 && !ptr1)
	{
		std::cout << "ptr2 has the ownership" << std::endl;
	}
}

#endif /* SMARTPOINTERS_H_ */
