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

int findLastClosing(char* str, int hint)
{
    for(int i=hint; i>=0; --i)
    {

    }
}

//(([]{})[])
bool checkParenthesis(char *str)
{

    int currentJ = -1;
    int lastJ = -1;

    for(int i=0; i< strlen(str); ++i)
    {

    }

}
