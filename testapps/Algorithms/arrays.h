#ifndef TESTAPPS_ALGORITHMS_ARRAYS_H_
#define TESTAPPS_ALGORITHMS_ARRAYS_H_

/// 1 2 3  			1 4 6		  6   4	  1
//  4 5 6  ---->>> 	2 5 7  --->   7	  5   2
//  6 7 8 			3 6 8		  8	  6	  3

/// 1  2  3   4
//  5  6  7   8
//  9  10 11 12
//  13 14 15 16

// 1 (j, i) -> 3 (i, 2 - j) -> 8 (2-j, 2 - i)  6(2 - j, i)
void rotateMatrix90(int matrix[][4], size_t length)
{
	unsigned top_j= 3;
	unsigned top_i= 3;
	unsigned bottom_j= 0;
	unsigned bottom_i= 0;

	unsigned int i= bottom_i;
	unsigned int j= bottom_j;
	unsigned k_max= (top_j - bottom_j)/ 2;

	for(unsigned int k=0; k<= k_max; ++k)
	{
		unsigned l_max= (top_i - bottom_i);

		for(unsigned l=0; l< l_max; ++l)
		{
			unsigned top_left = matrix[j][i];

			//copy top_left to top_right
			unsigned top_right = matrix[i][3 - j];
			matrix[i][3 - j] = matrix[j][i];

			//copy top_right to bottom_right
			unsigned bottom_right = matrix[3 - j][3 - i];
			matrix[3 - j][3 - i] = top_right;

			//copy bottom_right to bottom_left
			unsigned bottom_left = matrix[3 - i][j];
			matrix[3 - i][j] = bottom_right;

			//copy bottom_right to top_left
			matrix[j][i] = bottom_left;

			printf(
					"l_max= %u i= %u j= %u top_left= %u , top_right= %u , bottom_right= %u , bottom_left= %u \n",
					l_max, i, j, top_left, top_right, bottom_right, bottom_left);

			++i;
		}

		i= ++bottom_i;
		j= ++bottom_j;
		--top_i;
		--top_j;
	}
}




#endif /* TESTAPPS_ALGORITHMS_ARRAYS_H_ */
