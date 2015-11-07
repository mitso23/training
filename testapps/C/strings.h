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

#endif /* STRINGS_H_ */
