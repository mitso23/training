/*
 * reverse_array_special_characters.h
 *
 *  Created on: 19 Jun 2018
 *      Author: mitso23
 */

#ifndef REVERSE_ARRAY_SPECIAL_CHARACTERS_H_
#define REVERSE_ARRAY_SPECIAL_CHARACTERS_H_

#include <string.h>

bool normalChar(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >='A' && c<='Z'))
	{
		return true;
	}

	return false;
}

void reverse_array_special_character(char* input)
{
	const auto len = strlen(input);

	char* l = input;
	char* r = input + len - 1;

	while(l < r)
	{
		if (!(normalChar(*l)))
		{
			++l;
			continue;
		}

		if (!normalChar(*r))
		{
			--r;
			continue;
		}

		auto temp = *l;
		*l = *r;
		*r = temp;
		++l;
		--r;
	}
}


#endif /* REVERSE_ARRAY_SPECIAL_CHARACTERS_H_ */
