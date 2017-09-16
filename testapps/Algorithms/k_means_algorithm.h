/*
 * k_means_algorithm.h
 *
 *  Created on: 4 Sep 2017
 *      Author: mitso23
 */

#ifndef K_MEANS_ALGORITHM_H_
#define K_MEANS_ALGORITHM_H_

#define K_MEANS_PICTURE_SIZE 5
#define K_MEANS_MAX_GROUPS 4
int KMeansPicture[K_MEANS_PICTURE_SIZE][K_MEANS_PICTURE_SIZE] = {
																	{ 50, 50, 50, 20, 20 },
																	{ 50, 50, 12, 20, 20},
																	{ 50, 40, 50, 20, 20 },
																	{ 30, 30, 10, 30, 30 },
																	{ 30, 30, 30, 9, 30 }
																};

struct KMeansCoordinate
{
	int x;
	int y;
	int data;
};

struct Group
{
	KMeansCoordinate data[K_MEANS_PICTURE_SIZE*K_MEANS_PICTURE_SIZE];
	unsigned int index;
	unsigned int mean;
	unsigned int numElements;
};

Group KMeansGroups[K_MEANS_MAX_GROUPS];

int calculateNewMean(Group* group, int newElement)
{
	group->mean = (group->mean*group->numElements + newElement)/(group->numElements + 1);
	++group->numElements;
}

int calculateDistance(int a, int b)
{
	return (b-a)*(b-a);
}

void printGroups(unsigned int size)
{
	for(unsigned int i=0; i< size; ++i)
	{
		std::cout << "group: " << i << std::endl;
		for(unsigned int count=0; count <= KMeansGroups[i].index; ++count)
		{
			std::cout << "data: " << KMeansGroups[i].data[count].data << " x: " << KMeansGroups[i].data[count].x << " y: " << KMeansGroups[i].data[count].y << std::endl;
		}

		std::cout << std::endl;
	}
}

void partition(KMeansCoordinate* groups, unsigned int size)
{
	// push the initial groups
	for(unsigned int i=0; i< size; ++i)
	{
		KMeansGroups[i].index = 0;

		KMeansGroups[i].data[KMeansGroups[i].index].data = groups[i].data;
		KMeansGroups[i].data[KMeansGroups[i].index].x = groups[i].x;
		KMeansGroups[i].data[KMeansGroups[i].index].y = groups[i].y;

		KMeansGroups[i].mean = groups[i].data;
		KMeansGroups[i].numElements = 1;

	}

	for(unsigned int j=0; j< K_MEANS_PICTURE_SIZE; ++j)
	{
		for(unsigned int i=0; i< K_MEANS_PICTURE_SIZE; ++i)
		{
			int minDistance = 0xFFFF;
			int groupIndex = 0;

			for(unsigned int g= 0; g< size; ++g)
			{
				auto distance = calculateDistance(KMeansPicture[j][i], KMeansGroups[g].mean);
				if (distance < minDistance)
				{
					minDistance = distance;
					groupIndex = g;
				}
			}


			KMeansGroups[groupIndex].data[++KMeansGroups[groupIndex].index].data = KMeansPicture[j][i];
			KMeansGroups[groupIndex].data[KMeansGroups[groupIndex].index].x = i;
			KMeansGroups[groupIndex].data[KMeansGroups[groupIndex].index].y = j;

			++KMeansGroups[groupIndex].numElements;
			calculateNewMean(&KMeansGroups[groupIndex], KMeansPicture[j][i]);
		}
	}
}


#endif /* K_MEANS_ALGORITHM_H_ */
