#include <cstring>
#include <type_traits>
#include <iostream>

struct Res
{
	int numSpaces;
	int lastCharacterPos;
};

Res CalculateNumberSpaces(const char data[], int length)
{
	int counter = 0;
	int lastCharacterPos = 0;

	for (auto i = 0U; i <= strlen(data); ++i)
	{
		if (data[i] == ' ')
		{
			++counter;
		}
		else
		{
			lastCharacterPos = i;
		}
	}

	return { counter, lastCharacterPos };
}

//           012345678
//           He is Str
//           0123456789112
//           He%20is%20Str
void ReplaceSpaceString(char data[], int length)
{
	auto res = CalculateNumberSpaces(data, length);
	auto offset = res.numSpaces * 2;
	auto lastCharacter = res.lastCharacterPos;

	for (int pos = lastCharacter; pos >= 0; --pos)
	{
		if (offset == 0)
		{
			break;
		}
		else if (offset + pos >= length)
		{
			return;
		}

		if (data[pos] != ' ')
		{
			data[pos + offset] = data[pos];
		}
		else
		{
			data[pos + offset] = '0';
			data[pos + offset - 1] = '2';
			data[pos + offset - 2] = '%';
			offset = offset - 2;
		}

	}
}

//aabcccccaaa --->  a2b1c5a3
int EncodeString(char ptr[])
{
	auto numberPos = strlen(ptr) - 1;
	auto currentPos = strlen(ptr) - 1;
	auto numElements = 1;
	auto currentChar = ptr[currentPos];

	while (--currentPos >= 0)
	{
		if (ptr[currentPos] == currentChar)
		{
			++numElements;
		}
		else
		{
			ptr[numberPos--] = numElements + '0';
			ptr[numberPos--] = currentChar;
			currentChar = ptr[currentPos];
			numElements = 1;
		}
	}

	ptr[numberPos--] = numElements + '0';
	ptr[numberPos--] = currentChar;

	return numberPos + 1;
}

///abc --> abc
///aaabbcccd --> abcd
//a b c d : b c  c c d
unsigned int RemoveDuplicates(char data[])
{
	auto len = strlen(data);
	if (len == 1)
	{
		return 0;
	}

	auto previousChar = data[0];
	auto replace = 1U;
	auto current = 1U;

	while(current < len)
	{
		if (data[current] == previousChar)
		{
			++current;
		}
		else
		{
			data[replace] = data[current];
			previousChar = data[current];
			++replace;
			++current;
		}
	}

	return replace;
}

// 3 8 7 3 9 1 5 8

// min = 3; max = 3 ; Maxdiff = 0
// max = 9  min = 3; MaxDiff = 6
// min = 1  max = 1; MaxDiff = 6
// min = 1  max = 5  MaxDiff = 6;
// min = 1  max = 8; MaxDiff = 7
unsigned int findMaxStock(unsigned int arr[], unsigned int len)
{
	auto min = arr[0];
	auto max = arr[0];
	auto maxDiff = max - min;

	for(unsigned int i=1; i< len; ++i)
	{
		if(arr[i] <= min)
		{
			min = arr[i];
			max = arr[i];
		}
		else if (arr[i] >= max)
		{
			max = arr[i];
			if ((max - min) > maxDiff)
			{
				maxDiff = max - min;
			}
		}
	}

	return maxDiff;
}

template<unsigned size>
class Stack
{
 public:
	void Push(char c)
	{
		if (numElements <  size)
		{
			return;
		}

		data[numElements++] = c;
	}

	bool IsEmpty()
	{
		return numElements == 0;
	}

	char Pop()
	{
		return data[--numElements];
	}

	unsigned numElements = 0;
	unsigned data[size];
};

bool IsOpening(char c)
{
	return c == '(' || c == '[' || c== '{';
}

bool IsClosing(char c)
{
	return c == ')' || c == ']' || c == '}';
}

bool IsMatching(char l, char r)
{
	if (l == '(' && r == ')')
	{
		return true;
	}
	else if (l == '[' && r == ']')
	{
		return true;
	}
	else if (l == '{' && r == '}')
	{
		return true;
	}

	return false;
}

//([{}()])
template<unsigned size>
bool CheckProperString(char data[], unsigned pos, unsigned len, Stack<size>& st)
{
	if (IsOpening(data[pos]))
	{
		st.Push(data[pos]);
		if (pos < len - 1)
		{
			return CheckProperString(data, pos + 1, len, st);
		}
		else
		{
			return false;
		}
	}
	else if (IsClosing(data[pos]))
	{
		if (st.IsEmpty())
		{
			return false;
		}

		char lastOpening = st.Pop();
		return IsMatching(lastOpening, data[pos]);
	}

	return false;
}


bool CheckRepetition(const char data[], unsigned int offset, unsigned int len)
{
	if (offset + 3 >= len)
	{
		return false;
	}

	if (data[offset] == data[offset+1] && data[offset] == data[offset + 2])
	{
		return true;
	}

	return false;
}

/// ABC -> ABC
/// AAABBBC -> C
/// AAAB -> B
/// ABCCCCBBA => ABBBA => AA
void RemoveThreeConsecutiveChars(char data[])
{
	auto len = strlen(data);
	auto replace = 0U;
	auto current = 1U;

	while(current < len)
	{
		//Check if we need to swap
		if (current - replace >=2)
		{
			int offset = 0;
			if (data[current] == data[replace])
			{
				offset = replace;
			}
			else
			{
				offset = current;
			}

			if (CheckRepetition(data, offset, len))
			{
				//Go to the next character that is different
				char c = data[current];
				offset+= 3;
				current = offset;
				while(current < len)
				{
					if (data[current] == c)
					{
						++current;
					}
					else
					{
						break;
					}
				}
				continue;
			}
			else
			{
				data[replace] = data[current];
				if (replace >=2 && CheckRepetition(data, replace - 2, len))
				{
					replace-= 2;
				}
				else
				{
					++replace;
				}

				++current;

			}
		}
		else
		{
			if (data[current] == data[current - 1])
			{
				++current;
			}
			else
			{
				++current;
				++replace;
			}
		}
	}

	if (current - replace >=2)
	{
		data[replace] = '\0';
	}
}

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

///  {8, 1, 3, 5, 6, 7, 9, 10};
int partition(int* arr, int start, int end)
{
	int partition = end;
	int pivot = arr[partition];
	int replace = start - 1;
	swap(arr[partition], arr[end]);

	for(int i=start; i < end; ++i)
	{
		if (arr[i] < pivot)
		{
			++replace;
			swap(arr[i], arr[replace]);
		}
	}

	swap(arr[end], arr[replace + 1]);
	return replace + 1;
}

void sort(int* arr, int start, int end)
{
	if (start < end)
	{
		int pivot = partition(arr, start, end);

		sort(arr, start, pivot - 1);
		sort(arr, pivot + 1, end);
	}
}

static char freq[10][24];

int __str_cmp(char* str1, char* str2)
{
	while(*str1)
	{
		if (*str1 != *str2)
		{
			return *str1 - *str2;
		}

		++str1;
		++str2;
	}

	return *str1 - *str2;
}

void findNumberOfWords(char words[][10], unsigned N, unsigned M, char output[][10])
{
	for(unsigned int i=0; i< N; ++i)
	{
		for(unsigned int j=0; j< M; ++j)
		{
			freq[i][words[i][j] - 'a']++;
		}
	}

	int lenCounter[N] = { 0 };

	for(int j=0; j< 24; ++j)
	{
		for (unsigned i = 0; i < N; ++i)
		{
			while (freq[i][j] > 0)
			{
				output[i][lenCounter[i]] = j + 'a';
				++lenCounter[i];
				--freq[i][j];
			}
		}
	}

	for(unsigned i=0; i< N; ++i)
	{
		output[i][lenCounter[i]] = '\0';
	}

	unsigned int counter = 0;
	for(unsigned int i=0; i + 1< N; ++i)
	{
		if (lenCounter[i] == lenCounter[i+1])
		{
			if (__str_cmp(output[i], output[i+1]) == 0)
			{
				++counter;
			}
			else
			{
				std::cout << "number of anagrams: " << counter << " word" << words[counter == 0 ? i : i-1] << std::endl;
				counter = 0;
			}
		}
		else
		{
			std::cout << "number of anagrams: " << counter << " word" << words[counter == 0 ? i : i-1] << std::endl;
			counter = 0;
		}

		if ((i + 1 == N) && counter != 0)
		{
			std::cout << "number of anagrams: " << counter << " word" << words[i - 1] << std::endl;
		}
	}
}