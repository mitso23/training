/*
 * matching_brackets.h
 *
 *  Created on: 23 Apr 2017
 *      Author: mitso23
 */

#ifndef MATCHING_BRACKETS_H_
#define MATCHING_BRACKETS_H_

#define STACK_SIZE 100

struct c_stack
{
	unsigned char data[STACK_SIZE];
	int index = -1;
};

void push(struct c_stack* stack, unsigned char data)
{
	if (stack->index >= STACK_SIZE)
	{
		return;
	}

	stack->data[++stack->index] = data;
}

unsigned char pop(struct c_stack* stack)
{
	if (stack->index == -1)
	{
		return 0xFF;
	}

	return stack->data[stack->index--];
}


// (())()
const char *match(const char *str)
{
        if( *str == '\0' || *str == ')' || *str == '}' || *str == ']') { return str; }

        if( *str == '(' )
        {
                const char *closer = match(++str);
                if( *closer == ')' )
                {
                        return match(++closer);
                }

                return str - 1;
        }
        else if (*str == '{')
        {
			const char *closer = match(++str);
			if (*closer == '}')
			{
				return match(++closer);
			}

			return str - 1;
        }
        else if (*str == '[')
		{
			const char *closer = match(++str);
			if (*closer == ']')
			{
				return match(++closer);
			}

			return str - 1;
		}

        return match(++str);
}


bool check_parenthesis(const char* str)
{
	c_stack stack;

	while(*str)
	{
		if (*str == '{' || *str == '[' || *str == '(')
		{
			//std::cout << "pushing: " << *str << std::endl;
			push(&stack, *str);
		}
		else
		{
			unsigned char c = pop(&stack);

			//std::cout << "pop: " << c << std::endl;

			if (c == 0xFF)
			{
				std::cout << "stack empty: " << std::endl;
				return false;
			}

			if ((*str == '}' && c != '{') || (*str == ']' && c != '[') || (*str == ')' && c != '('))
			{
				std::cout << "mismatch, expected: " << *str << " got: " << c << std::endl;
				return false;
			}
		}

		++str;
	}

	if (stack.index != -1)
	{
		std::cout << "stack was not empty in the end: " << std::endl;
		return false;
	}

	return true;
}


#endif /* MATCHING_BRACKETS_H_ */
