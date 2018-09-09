/*
 * quicksort.h
 *
 *  Created on: 13 Feb 2018
 *      Author: mitso23
 */

#ifndef QUICKSORT_H_
#define QUICKSORT_H_

int partition2(int* arr, int low, int high)
{
	int* current = arr + low;
	int* replace = current;
	int* end = arr + high;
	unsigned int pivot = *end;

	while(current <= end)
	{
		if (*current <= pivot)
		{
			if (current != replace)
			{
				std::swap(*current, *replace);
			}

			++replace;
		}

		++current;
	}

#if 0
	for(unsigned int i=low; i<= high; ++i)
	{
		std::cout << "new data: " << arr[i] << std::endl;
	}

	std::cout << "new pivot location: " << replace - arr - 1 << " value: " << *(replace - 1) << std::endl;
#endif

	//std::cout << "replace is " << *(replace - 1) << std::endl;
	return replace - arr - 1;

}

int partition (int* arr, int low, int high)
{
    // pivot (Element to be placed at right position)
	auto number = low + random()%(high-low);
	std::swap(arr[number], arr[high]);

	auto pivot = arr[high];

    auto i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1],arr[high]);

    return (i);
}

void quicksort_rec(int* arr, int low, int high)
{
	//std::cout << "low: " << low << " high: " << high << std::endl;

	if (low < high)
	{
		auto pivot = partition(arr, low, high);

		quicksort_rec(arr, low, pivot -1);
		quicksort_rec(arr, pivot + 1, high);

	}
}

#if 0
int kthSmallest(int arr[], int l, int r, int k)
{
	if (l < r)
	{
		auto pivot = partition2(arr, l, r);

		if (pivot -l == k - 1)
		{
			return arr[pivot];
		}
		else if (pivol - l > k - 1)
		{
			partition2(arr, l, pivot - 1, k);
		}

		partition2(arr, pivot + 1, k - pivot - l - 1);
	}
}
#endif

void quicksort(int* arr, int size)
{
	quicksort_rec(arr, 0, size - 1);
}


#endif /* QUICKSORT_H_ */
