#ifndef PERMUTATION_H_
#define PERMUTATION_H_

#include <string.h>
#include <deque>

/// abcd pos = 1
///
void rotate(char* str,int size)
{
	int pos = strlen(str) - size;

	//printf("rotating pos: %d \n", pos);
	unsigned temp = str[strlen(str) - 1];

	for(int i=strlen(str) - 1; i >= pos; --i)
	{
		str[i] = str[i - 1];
	}

	str[pos] = temp;

	//printf("result: %s\n", str);
}

//->cat
//-->at print (cat),rotate(ta) print(cta)
//--->t (return)
void permutate(char* str, int size, int level)
{
	++level;

	if (size == 1)
	{
		return;
	}

	for(unsigned int i=0; i< size; ++i)
	{
		//std::cout << "level: " << level << " i: " << i << std::endl;
		permutate(str, size - 1, level);

		if (size == 2)
		{
			printf("%s\n", str);
		}

		rotate(str, size);
	}

	--level;
}

bool isValidEntry(std::deque<char>& d, char value)
{
	for(auto it=d.begin(); it != d.end(); ++it)
	{
		if (*it == value)
		{
			return false;
		}
	}

	return true;
}

void printEntries(std::deque<char>& d)
{
	for(auto it=d.begin(); it != d.end(); ++it)
	{
		std::cout << *it;
	}

	std::cout << std::endl;
}

void permutate2(char* str)
{
	std::deque<char> d;

	for(unsigned int m=0; m< strlen(str); ++m)
	{
		d.push_back(str[m]);

		for(unsigned int j=0; j< strlen(str); ++j)
		{
			//std::cout << "j: " << str[j] << std::endl;
			if (!isValidEntry(d, str[j]))
			{
				continue;
			}
			d.push_back(str[j]);

			for(unsigned int k=0; k < strlen(str); ++k)
			{
				if (!isValidEntry(d, str[k]))
				{
					continue;
				}

				//std::cout << "k: " << str[k] << std::endl;
				d.push_back(str[k]);

				for(unsigned int l=0; l < strlen(str); ++l)
				{
					if (!isValidEntry(d, str[l]))
					{
						continue;
					}

					//std::cout << "l: " << str[l] << std::endl;
					d.push_back(str[l]);
					printEntries(d);
					d.pop_back();
				}

				d.pop_back();
			}

			d.pop_back();
			//std::cout << "starting clean: " << std::endl;
		}

		d.pop_back();
	}
}

#endif /* PERMUTATION_H_ */
