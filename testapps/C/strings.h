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
void reverse(int* number)
{
	int num= *number;
	int remainder= num;
	int newNumber= 0;
	int i= 1;

	while(num)
	{
		remainder = num % 10;
		newNumber+= (remainder * i);
		num= num / 10;
		i*= 10;

		printf("%d\n", newNumber);
	}

	*number= newNumber;
}

//abcdf -> //fdcba
void reverseString(char* str)
{
	char* end= str + strlen(str) - 1;
	char* start= str;

	for(;end != start; --end, ++start)
	{
		char temp= *end;
		*end= *start;
		*start= temp;
	}
}

//abcdf -? abddf
void removeCharacter(char* str, unsigned index)
{
	for(unsigned int i=index; i< (strlen(str) - 1); ++i)
	{
		str[i]= str[i + 1];
	}

	str[strlen(str) - 1] = '\0';
}

//Dimitrios -> Dimtros
void removeDuplicatesNoStorage1(char* str)
{
	char* pos = NULL;
	for(unsigned int i=0; i< strlen(str);)
	{
		if ((pos = strchr(str + i + 1, str[i])))
		{
			removeCharacter(str, (unsigned) (pos - str));
			printf("duplicated character %c \n", str[i]);
			continue;
		}
		else
		{
			++i;
		}
	}
}

// DI Mi SI DO
// Count how many spaces
// Shift number of spaces * 3
void replaceSpaceWithPercent20(char* str)
{
	unsigned int str_len= strlen(str);
	unsigned int numSpaces= 0;
	char* str_end= str + str_len - 1;

	for(unsigned int i=0; i< str_len; ++i)
	{
		if(str[i] == ' ')
			numSpaces++;
	}

	char* str_new_end= str_end + numSpaces*3;
	*(str_new_end + 1)= '\0';

	while(str_end != str)
	{
		if(*str_end != ' ')
		{
			*str_new_end--= *str_end--;
		}
		else
		{
			*str_new_end--= '0';
			*str_new_end--= '2';
			*str_new_end--= '%';
			--str_end;
		}
	}

	printf("%s\n", str);

}

#endif /* STRINGS_H_ */
