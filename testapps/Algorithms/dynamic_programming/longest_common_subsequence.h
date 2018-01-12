#ifndef LONGEST_COMMON_SUBSEQUENCE_H_
#define LONGEST_COMMON_SUBSEQUENCE_H_

#include <string.h>

unsigned int longestCommonSubSequence(char* str1, char* str2)
{
	std::cout << "str1: " << str1 << " str2: " << str2 << std::endl;

	if (strlen(str1) == 0 || strlen(str2) == 0)
	{
		return 0;
	}
	else
	{
		unsigned char last1 = str1[strlen(str1) - 1];
		unsigned char last2 = str2[strlen(str2) - 1];

		if (last1 == last2)
		{
			std::cout << " last character the same: " << std::endl;

			str1[strlen(str1) - 1] = '\0';
			str2[strlen(str2) - 1] = '\0';

			return 1 + longestCommonSubSequence(str1, str2);
		}
		else
		{
			std::cout << " last character not the same: " << std::endl;

			char* str1dup = strdup(str1);
			char* str2dup = strdup(str2);

			str1dup[strlen(str1dup) - 1] = '\0';
			str2dup[strlen(str2dup) - 1] = '\0';

			unsigned int max1 = longestCommonSubSequence(str1, str2dup);
			unsigned int max2 = longestCommonSubSequence(str1dup, str2);

			std::cout << " max1: " << max1 << " max2: " << max2 << std::endl;

			return max1 > max2 ? max1 : max2;
		}
	}
}

#endif
