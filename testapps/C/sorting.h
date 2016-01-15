#ifndef SORTING_H_
#define SORTING_H_

void bubblesort(int* arr, size_t size)
{
	unsigned int last= size;
	bool swapped = false;
	for(unsigned int j=0; j< size; ++j)
	{
		for(unsigned int i=0; i< (last - 1); ++i)
		{
			if(arr[i] > arr[i + 1])
			{
				unsigned temp= arr[i + 1];
				arr[i + 1]= arr[i];
				arr[i]= temp;

				swapped = true;
			}
		}

		if (!swapped)
			return;

		--last;
	}
}

void selectionsort(int* arr, size_t size)
{
	for(unsigned int j=0; j< (size - 1); ++j)
	{
		unsigned min = j;
		bool swapp= false;

		for(unsigned int i=(j+1); i< size; ++i)
		{
			if(arr[i] < arr[min])
			{
				min= i;
				swapp = true;
			}
		}

		if (swapp)
		{
			unsigned temp= arr[j];
			arr[j] = arr[min];
			arr[min]= temp;
		}
	}
}

// { 1, 8, 2 , 3 , 7 , 4 };
void insertionSort(int* arr, size_t size)
{
	for(unsigned int j=1; j< size; ++j)
	{
		if (arr[j] < arr[j - 1])
		{
			unsigned int temp=  arr[j];

			for (int i = j; i >= 0; --i)
			{
				if (arr[i - 1] > temp)
				{
					arr[i]= arr[i - 1];
				}
				else
				{
					arr[i]= temp;
					break;
				}
			}
		}
	}
}

#endif /* SORTING_H_ */
