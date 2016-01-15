// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

typedef enum
{
    START,
    SIMILAR,
    DIFFERENT

}parsing_state_t;

#include <algorithm>
#include <iterator>
<<<<<<< HEAD
=======
#include <string>
#include <utils/Noisy.h>
#include <sstream>

void reverseSentence(const std::string& str)
{
	std::stringstream data(str);
	std::string word;

	while(data >> word)
	{
		std::string reversedWord;
		std::copy(word.rbegin(), word.rend(), std::back_inserter(reversedWord));
		std::cout << reversedWord << " ";
	}

	std::cout << std::endl;
}
>>>>>>> e01479f144cb4ab7b9f04c2a40a7ef44ca277116

int solution(vector<int> &A) {

    if (A.size() == 0)
    {
        return 0;
    }
    else if (A.size() == 1)
    {
        return A[0];
    }

    std::sort(A.begin(), A.end());
    //std::copy(A.begin(), A.end(), std::ostream_iterator<int>(std::cout));

    parsing_state_t state= START;

    unsigned int i=1;

    for(; i< A.size();++i)
    {
        if (state == START)
        {
            if (A[i] == A[i-1])
            {
                state = SIMILAR;
                continue;
            }
            else
            {
                //std::cout << "found it at " << i << " value: " << A[i] << std::endl;
                return A[i-1];
            }
        }
        else if (state == SIMILAR)
        {
            if (A[i] == A[i-1])
            {
                continue;
            }
            else
            {
                state = START;
                continue;
            }
        }
    }

    if (state == START)
    {
        //std::cout << "END: found it at " << i << " value: " << A[i] << std::endl;
        return A[i-1];
    }

    return -1;

}

#include <unordered_set>

int solution2(vector<int> &A)
{
    std::unordered_set<int> s;

    for(auto it=A.begin(); it!= A.end(); ++it)
    {
        s.insert(*it);
    }

    for(auto it=s.begin(); it!= s.end(); ++it)
    {
        if(s.count(*it) == 1)
        {
            return *it;
        }
    }
}

int solution(int X, int Y, int D)
{
<<<<<<< HEAD
    int count=0;

    if ((Y-D) == X)
    {
    	return 0;
    }
    else if ((Y - D) < X)
    {
        return 1;
    }

    auto distance= Y - X;
    count = distance / D;

    if (count == 0)
    {
        return 1;
    }
    else if (distance % D)
    {
        return ++count;
    }
    else
    {
        return count;
    }
=======
	std::string temp("Hello world");

	reverseSentence(temp);
>>>>>>> e01479f144cb4ab7b9f04c2a40a7ef44ca277116
}
