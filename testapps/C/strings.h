#ifndef STRINGS_H
#define STRINGS_H

#include <stdio.h>
#include <stdlib.h>

//This will convert the 123\0 to 123 int number
int strToInt(const char* number)
{
	int sum= 0;
	while(*number) { sum= (*number++ - '0') + ((sum << 3) + sum + sum); }
	return sum;
}

int strToIntRecursive(const char* number)
{
	static int sum= 0;

	if (*number != 0)
	{
		sum= (*number++ - '0') + ((sum << 3) + sum + sum);
		strToIntRecursive(number);
	}

	return sum;
}

//So the input will be 123 and we need to print 321
void reverseInt(int* number)
{
	int num= *number;
	int remainder= num;
	int newNumber= 0;

	while(num)
	{
		remainder = num % 10;
		newNumber = newNumber * 10 + remainder;
		num/= 10;

		printf("%d\n", newNumber);
	}

	*number= newNumber;
}

char* reverseWord(char* str)
{
	size_t length= strlen(str);
	if (length == 0)
		return NULL;

	char* start= str;
	char* end= str + length - 1;

	for(unsigned int i=0; i< length/2; ++i)
	{
		char temp= *start;
		*start= *end;
		*end= temp;
		++start;
		--end;
	}

	return str;
}

int str_find(size_t from, const char* str, const char* substr)
{
	size_t substring_len = strlen(substr);
	size_t str_len = strlen(str);

	if (substring_len > str_len)
	{
		return false;
	}

	for(unsigned i=from, j=0; i< str_len; ++i)
	{
		if (str[i] != substr[j])
		{
			j=0;
			continue;
		}

		if (j + 1 == substring_len)
		{
			return i-j;
		}

		++j;
	}

	return -1;
}

char* get_sub_str(const char* str, unsigned start, unsigned end)
{
	unsigned int length= strlen(str);

	if (start >= length || end > length)
	{
		return NULL;
	}
	else if (start > end)
	{
		return NULL;
	}

	unsigned int new_length= end - start;
	char* new_str= (char*)malloc(new_length + 1);

	for(unsigned int i=start, j=0; i< end; ++i)
	{
		new_str[j++]= str[i];
	}

	return new_str;

}

char* get_next_word(unsigned int* start, const char* str, const char* delimiter)
{
	size_t length= strlen(str);

	if (*start < length)
	{
		int index= str_find(*start, str, delimiter);

		if (index == -1)
		{
			char* value= get_sub_str(str, *start, length);
			*start= length;
			return value;
		}
		else
		{
			char* value= get_sub_str(str, *start, (unsigned)index);
			*start= (unsigned)index + 1;
			return value;
		}
	}
	else
	{
		return NULL;
	}
}

//Hello World Dimitrios
void reverseSentence(char* str)
{
	unsigned int length= strlen(str);
	unsigned int next_word_offset= 0;

	while(next_word_offset != length)
	{
		char* word= get_next_word(&next_word_offset, str, " ");
		printf("%s:\n", word);
		free(word);
	}
}

void reverseSentence2(char* str)
{
	char temp[100];
	memset(temp, 0, sizeof(temp));
	unsigned int offset= 0;
	int result = 0;
	unsigned str_len= strlen(str);

	while(((result= sscanf(str + offset, "%s", temp)) == 1) && offset < str_len)
	{
		printf("str: %s\n", temp);
		char* substr_addr= strstr(str + offset, temp);

		if (!substr_addr)
			break;

		offset= strlen(temp) + (substr_addr - str);
	}
}

void find_longest_non_repeative_str(const char* str)
{
	unsigned int counter= 0;
	unsigned int max_counter= 0;
	unsigned int str_len= strlen(str);
	ssize_t ascii_hash[256];
	memset(ascii_hash, -1, sizeof(ascii_hash));

	for(unsigned int i=0; i< str_len;)
	{
		unsigned index= (unsigned)str[i];

		if (ascii_hash[index] == -1)
		{
			printf("unique character is %c, index is %d \n", str[i], i);
			ascii_hash[index]= i;
			++counter;
			++i;
		}
		else
		{
			printf("same character is %c, current index is %d previous index is %d \n", str[i], i, ascii_hash[index]);
			i= ascii_hash[index];
			++i;
			memset(ascii_hash, -1, sizeof(ascii_hash));
			counter= 0;
		}

		if (counter > max_counter)
		{
			max_counter = counter;
		}
	}

	printf("Maximum substring is %u \n",  max_counter);
}

void sort_array_string(const char** arr, size_t numWords)
{
	for(size_t i=0; i< numWords; ++i)
	{
		printf("word at i %d is %s\n", i , arr[i]);
	}
}

void sort_array_string_2(char (*arr)[10], size_t numWords)
{
	for(size_t i=0; i< numWords; ++i)
	{
		printf("word at i %d is %s\n", i , arr[i]);
	}
}

#endif /* STRINGS_H_ */
