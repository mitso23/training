bool isOpening(char c)
{
    if (c == '(' || c == '[' || c== '{')
    {
        return true;
    }

    return false;
}

bool isClosing(char c)
{
    if (c == ')' || c == ']' || c == '}')
    {
        return true;
    }

    return false;
}

bool isMatch(char l, char r)
{
	return ((l == '(' && r == ')') || (l == '[' && r == ']') || (l == '{' && r == '}'));
}

int findLastOpening(char* str, int hint)
{
    for(int i=hint; i>=0; --i)
    {
    	if (isOpening(str[i]))
		{
    		return i;
		}
    }

    return -1;
}

//(([]{})[])
bool checkParenthesis(char *str)
{
    int currentJ = -1;
    int lastJ = -1;

    for(int i=0; i< strlen(str); ++i)
    {
    	if(isOpening(str[i]))
    	{
    		currentJ = i;
    		printf("i: %d currentJ: %d lastJ: %d  char: %c \n", i, currentJ, lastJ, str[i]);
    	}
    	else if (isClosing(str[i]))
    	{
    		if (i == currentJ + 1)
    		{
    			printf("i: %d currentJ: %d lastJ: %d  char: %c \n", i, currentJ, lastJ, str[i]);

    			if (!isMatch(str[currentJ], str[i]))
    			{
    				printf("mismatch 1 \n");
    				return false;
    			}
    			else
    			{
    				str[i] = '#';
    				str[currentJ] = '#';
    			}
    		}
    		else
    		{
    			int hint = lastJ != -1 ? lastJ : currentJ;

    			lastJ = findLastOpening(str, hint);

    			printf("i: %d currentJ: %d lastJ: %d  hint: %d char: %c \n", i, currentJ, lastJ, hint, str[i]);

    			if (lastJ == -1)
    			{
    				printf("mismatch 2 \n");
    				return false;
    			}

    			if (!isMatch(str[lastJ], str[i]))
    			{
    				return false;
    			}
    			else
    			{
    				str[i] = '#';
    				str[lastJ] = '#';
    			}
    		}
    	}
    }

    printf(str);
}
