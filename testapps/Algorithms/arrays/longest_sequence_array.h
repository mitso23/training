#ifndef LONGEST_SEQUENCE_ARRAY_H_
#define LONGEST_SEQUENCE_ARRAY_H_

#define MAX_HASH_SIZE 1000U

int my_set[MAX_HASH_SIZE];

#include <list>
std::list<int>* my_set2[MAX_HASH_SIZE];

unsigned findStartElement(int* arr, unsigned int size, unsigned int currentIndex)
{
	int value = arr[currentIndex] - 1;

	while(true)
	{
		if (my_set[value] != 0)
		{
			value-= 1;
			continue;
		}
		else
		{
			break;
		}
	}
}

void longest_sequence_array(int* arr, unsigned int size)
{
	memset(my_set, 0, sizeof(my_set));

	//put everything into a my_set
	for(unsigned int i=0; i< size; ++i)
	{
		my_set[arr[i]] = 1;
	}

	unsigned int max = 1;
	for(unsigned int i=0; i< size; ++i)
	{
		std::cout << "current location is " << i << std::endl;

		auto value = findStartElement(arr, size, i);
		unsigned int count = 0;

		while(true)
		{
			if (my_set[value] != 0)
			{
				++count;
				++value;
				continue;
			}
			else
			{
				break;
			}
		}

		if (count > max)
		{
			max = count;
		}
	}

	std::cout << "max value is: " << max << std::endl;
}

void longest_sequence_array_2(int* arr, unsigned int size)
{
	for(unsigned int i=0; i< size; ++i)
	{
		auto value = arr[i];
		my_set2[value] = new std::list<int>();
		my_set2[value]->push_back(value);

		std::cout << "adding value: " << value << " to group " << value << std::endl;

		if (my_set2[value - 1] && my_set2[value + 1])
		{
			std::cout << "value - 1 and value + 1 present" << std::endl;
			for(auto item: *my_set2[value - 1])
			{
				my_set2[value]->push_back(item);
				std::cout << "adding value: " << item << " to group " << value << std::endl;

				my_set2[item] = my_set2[value];
			}

			for(auto item: *my_set2[value + 1])
			{
				my_set2[value]->push_back(item);
				std::cout << "adding value: " << item << " to group " << value << std::endl;
				my_set2[item] = my_set2[value];
			}

			my_set2[value-1] = my_set2[value];
			my_set2[value+1] = my_set2[value];

			std::cout << " finish " << std::endl;
		}
		else if (my_set2[value-1])
		{
			std::cout << "value - 1 present" << std::endl;
			for(auto item: *my_set2[value - 1])
			{
				my_set2[value]->push_back(item);
				std::cout << "adding value: " << item << " to group " << value << std::endl;

				my_set2[item] = my_set2[value];
			}
			my_set2[value-1] = my_set2[value];
			std::cout << " finish " << std::endl;
		}
		else if (my_set2[value + 1])
		{
			std::cout << "value + 1 present" << std::endl;

			for(auto item: *my_set2[value + 1])
			{
				my_set2[value]->push_back(item);
				std::cout << "adding value: " << item << " to group " << value << std::endl;
				my_set2[item] = my_set2[value];
			}

			my_set2[value+1] = my_set2[value];
			std::cout << " finish " << std::endl;
		}
	}

	unsigned max = 1;
	for(unsigned int i=0; i< MAX_HASH_SIZE; ++i)
	{
		if (my_set2[i] != 0 && my_set2[i]->size() > max)
		{
			max = my_set2[i]->size();
		}
	}

	std::cout << "max sequence: " << max << std::endl;
}

#endif /* LONGEST_SEQUENCE_ARRAY_H_ */
