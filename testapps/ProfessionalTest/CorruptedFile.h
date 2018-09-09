#ifndef CORRUPTEDFILE_H_
#define CORRUPTEDFILE_H_

#include <iostream>
#include <stdlib.h>

static int numberOfReadsFromFile = 0;
static int numberOfReadsFromCurruptedFile = 0;

unsigned int NORMAL_FILE_SIZE;
unsigned int CORRUPTED_FILE_SIZE;

int* NormalFile = nullptr;
int* CorruptedFile = nullptr;

int* NormalFileCache = nullptr;

void CreateTestData()
{
	NORMAL_FILE_SIZE = 10000000;
	CORRUPTED_FILE_SIZE = NORMAL_FILE_SIZE/2;

	NormalFile = new int[NORMAL_FILE_SIZE];
	NormalFileCache = new int [NORMAL_FILE_SIZE];
	for(unsigned int i=0; i< NORMAL_FILE_SIZE; ++i)
		NormalFileCache[i] = -1;

	CorruptedFile = new int[CORRUPTED_FILE_SIZE];
	unsigned int numberMissingElements = NORMAL_FILE_SIZE - CORRUPTED_FILE_SIZE;
	unsigned int count = 0;
	unsigned int offset = 0;

	srand(time(NULL));
	for(unsigned int i=0; i< NORMAL_FILE_SIZE; ++i)
	{
		NormalFile[i] = i;

		if (offset >=CORRUPTED_FILE_SIZE)
		{
			continue;
		}
		else
		{
			//Add some randomness
#if 1
			if (count < numberMissingElements)
			{
				if (rand() % 8 < 4)
				{
					++count;
					continue;
				}
			}
#endif
			//std::cout << "Adding " << i << " to corrupted: " << std::endl;
			CorruptedFile[offset++] = i;
		}

	}

}

int BinarySearch(int (*funct)(unsigned int), int _start, int _end, int value)
{
	int start = _start;
	int end = _end;

	while(start <= end)
	{
		int mid = start + (end - start)/2;
		int readValue = funct(mid);

		if (readValue == value)
		{
			return mid;
		}
		else if (value < readValue)
		{
			end = mid - 1;
		}
		else if (value > readValue)
		{
			start = mid + 1;
		}
	}

	return -1;
}

int ReadFromNormalFile(unsigned pos)
{
	if (pos >= NORMAL_FILE_SIZE)
	{
		//std::cerr << "pos greater than file size: " << pos << std::endl;
		return -1;
	}


	if (NormalFileCache[pos] != -1)
	{
		//std::cout << "reading from cache: " << pos << std::endl;
		return NormalFileCache[pos];
	}

	//std::cout << "reading from normal file: " << pos << std::endl;

	++numberOfReadsFromFile;

	auto value = NormalFile[pos];
	NormalFileCache[pos] = value;

	return value;
}

int ReadFromCorruptedFile(unsigned pos)
{
	++numberOfReadsFromCurruptedFile;

	if (pos >= CORRUPTED_FILE_SIZE)
	{
		//std::cerr << "pos is greater than file size: " << pos << std::endl;
		return -1;
	}

	return CorruptedFile[pos];
}

unsigned int findFileSize(int (*funct)(unsigned int))
{
	unsigned int nextLocation = 0xFFFFFFFF;
	unsigned lastAccessibleRead = 0;
	unsigned lastNotAccessibleRead = 0xFFFFFFFF;

	while(1)
	{
		int pos = funct(nextLocation);

		if (pos == -1)
		{
			lastNotAccessibleRead = nextLocation;
			nextLocation = nextLocation / 2;

			//std::cout << "next location is " << nextLocation << std::endl;
		}
		else
		{
			lastAccessibleRead = nextLocation;
			break;
		}
	}

	//std::cout << "last success read: " << lastNotAccessibleRead << " last failed read: " << lastAccessibleRead << std::endl;

	while(lastNotAccessibleRead - lastAccessibleRead !=1)
	{
		nextLocation = (lastNotAccessibleRead - lastAccessibleRead)/2 + lastAccessibleRead;

		//std::cout << "next location is " << nextLocation << " success read: " << lastAccessibleRead << " fail read: " << lastNotAccessibleRead << std::endl;

		int pos = -1;
		if ((pos = funct(nextLocation)) == -1)
		{
			lastNotAccessibleRead = nextLocation;
		}
		else
		{
			lastAccessibleRead = nextLocation;
		}
	}

	return lastAccessibleRead + 1;

}

struct Element
{
	unsigned pos = 0;
	int value = -1;
};

void FindMissingFileContentRec(Element corruptedStart, Element corruptedEnd, int normalStart, int normalEnd, unsigned int& numMissingElements, unsigned int origFileSize)
{

	if (numMissingElements == 0)
	{
		//std::cout << "found all the missing elements";
		return;
	}

	Element corruptedMid;
	corruptedMid.pos = corruptedStart.pos + (corruptedEnd.pos - corruptedStart.pos)/2;

	//std::cout << "searching start: " << corruptedStart.pos << " searching end: " << corruptedEnd.pos << " remaining: " << numMissingElements << " mid: " << corruptedMid.pos << std::endl;

	corruptedStart.value = ReadFromCorruptedFile(corruptedStart.pos);
	corruptedMid.value = ReadFromCorruptedFile(corruptedMid.pos);
	corruptedEnd.value = ReadFromCorruptedFile(corruptedEnd.pos);


	Element startNormal;
	startNormal.pos = BinarySearch(ReadFromNormalFile, normalStart, normalEnd, corruptedStart.value);

	Element midNormal;
	midNormal.pos = BinarySearch(ReadFromNormalFile, normalStart, normalEnd, corruptedMid.value);

	Element endNormal;
	endNormal.pos = BinarySearch(ReadFromNormalFile, normalStart, normalEnd, corruptedEnd.value);

	auto numNormalElementsLeft = midNormal.pos - startNormal.pos;
	auto numNormalElementsRight = endNormal.pos - midNormal.pos;

	auto numCorruptedElementsLeft = corruptedMid.pos - corruptedStart.pos;
	auto numCorruptedElementsRight = corruptedEnd.pos - corruptedMid.pos;

	if ((numNormalElementsLeft - numCorruptedElementsLeft) >= 1)
	{
		if (corruptedMid.pos - corruptedStart.pos == 1)
		{
			for(unsigned int i=startNormal.pos + 1; i< midNormal.pos; ++i)
			{
				//std::cout << "missing element left is " << ReadFromNormalFile(i) << std::endl;
				--numMissingElements;
			}

			if (numMissingElements == 0)
			{
				//std:: cout << "found all missing elements on the left " << std::endl;
				return;
			}
		}
		else
		{
			//std::cout << "number of elements missing on the left: " << numNormalElementsLeft - numCorruptedElementsLeft << std::endl;
			FindMissingFileContentRec(corruptedStart, corruptedMid, startNormal.pos , midNormal.pos, numMissingElements, origFileSize);
		}
	}
	else if (numNormalElementsLeft - numCorruptedElementsLeft == 0)
	{
		//std::cout << "no elements are missing on the left" << std::endl;
	}

	if (numNormalElementsRight - numCorruptedElementsRight >= 1)
	{
		if (corruptedEnd.pos - corruptedMid.pos == 1)
		{
			for(unsigned int i= midNormal.pos + 1; i< endNormal.pos; ++i)
			{
				//std::cout << "missing number right: " << ReadFromNormalFile(i) << std::endl;
				--numMissingElements;
			}

			if (numMissingElements == 0)
			{
				//std:: cout << "found all missing elements on the right " << std::endl;
				return;
			}
		}
		else
		{
			//std::cout << "number of elements missing on the left: " << numNormalElementsRight - numCorruptedElementsRight << std::endl;
			FindMissingFileContentRec(corruptedMid, corruptedEnd, midNormal.pos, endNormal.pos, numMissingElements, origFileSize);
		}
	}
	else if (numNormalElementsRight - numCorruptedElementsRight == 0)
	{
		//std::cout << "no elements are missing on the right" << std::endl;
	}
}

void FindMissingFileContentsOptimized()
{
	unsigned int originalFileSize = findFileSize(ReadFromNormalFile);
	std::cout << "origianlFileSize file size is " << originalFileSize << std::endl;

	unsigned int corruptedFileSize = findFileSize(ReadFromCorruptedFile);
	std::cout << "corruptedFileSize file size is " << corruptedFileSize << std::endl;

	numberOfReadsFromFile = 0;
	numberOfReadsFromCurruptedFile = 0;

	unsigned numberMissingElem = originalFileSize - corruptedFileSize;

	Element corruptedStart;
	corruptedStart.pos = 0;
	corruptedStart.value = ReadFromCorruptedFile(corruptedStart.pos);

	Element corruptedEnd;
	corruptedEnd.pos = corruptedFileSize - 1;
	corruptedEnd.value = ReadFromCorruptedFile(corruptedEnd.pos);


	Element normalStart;
	normalStart.pos = 0;
	normalStart.value = ReadFromNormalFile(normalStart.pos);

	Element normalEnd;
	normalEnd.pos = originalFileSize - 1;
	normalEnd.value = ReadFromNormalFile(normalEnd.pos);

	if (corruptedEnd.pos - corruptedStart.pos == 0)
	{
		corruptedStart.value = ReadFromCorruptedFile(corruptedStart.pos);
		int pos = BinarySearch(ReadFromNormalFile, 0, originalFileSize - 1, corruptedStart.value);

		for(unsigned int i=0; i< originalFileSize; ++i)
		{
			if (i != (unsigned)pos)
			{
				//std::cout << "missing element: " << ReadFromNormalFile(i) << std::endl;
				--numberMissingElem;
			}
		}

		return;
	}


	if (normalStart.value < corruptedStart.value)
	{
		//std::cout << "normal value: " << normalStart.value << " is less than corrupted: " << corruptedStart.value << std::endl;

		for (unsigned int i=0; i< normalEnd.pos; ++i)
		{
			auto normalValue =  ReadFromNormalFile(i);

			if (normalValue < corruptedStart.value)
			{
				//std::cout << "missing element: " << normalValue << std::endl;
				--numberMissingElem;
			}
			else
			{
				break;
			}
		}
	}

	if (corruptedEnd.value < normalEnd.value)
	{
		//std::cout << "normal value: " << normalEnd.value << " is greater than " << corruptedEnd.value << std::endl;

		auto pos = BinarySearch(ReadFromNormalFile, 0, originalFileSize - 1, corruptedEnd.value);

		for (unsigned int i=pos; i< normalEnd.pos; ++i)
		{
			auto normalValue = ReadFromNormalFile(i);
			//std::cout << "missing element: " << normalValue << std::endl;
			--numberMissingElem;
		}
	}

	if (numberMissingElem != 0)
		FindMissingFileContentRec(corruptedStart, corruptedEnd, 0, originalFileSize - 1, numberMissingElem, originalFileSize);

}

#if 0
void FindMissingFileContents()
{
	unsigned int originalFileSize = findFileSize(ReadFromNormalFile);
	std::cout << "origianlFileSize file size is " << originalFileSize << std::endl;

	unsigned int corruptedFileSize = findFileSize(ReadFromCorruptedFile);
	std::cout << "corruptedFileSize file size is " << corruptedFileSize << std::endl;

	unsigned numberMissingElem = originalFileSize - corruptedFileSize;
	unsigned int countMissingElements = 0;

	Element rightCorrupt;
	rightCorrupt.pos = corruptedFileSize - 1;
	Element leftCorrupt;
	leftCorrupt.pos = rightCorrupt.pos - 1;

	Element leftNormal;
	Element rightNormal;

	Element maxNormal;
	maxNormal.pos = originalFileSize - 1;
	maxNormal.value = -1;

	while(countMissingElements < numberMissingElem)
	{
		leftCorrupt.value = ReadFromCorruptedFile(leftCorrupt.pos);
		rightCorrupt.value = ReadFromCorruptedFile(rightCorrupt.pos);

		leftNormal.pos = BinarySearch(ReadFromNormalFile, originalFileSize, leftCorrupt.value);
		leftNormal.value = leftCorrupt.value;

		rightNormal.pos = BinarySearch(ReadFromNormalFile, originalFileSize, rightCorrupt.value);
		rightNormal.value = rightCorrupt.value;


		if (maxNormal.value == -1)
		{
			maxNormal.value = ReadFromNormalFile(maxNormal.pos);

			if (rightCorrupt.value < maxNormal.value)
			{
				std::cout << "right corrupt " << rightCorrupt.value
						<< " is less than max normal: " << maxNormal.value
						<< " missing elements: " << maxNormal.pos - rightCorrupt.pos - 1
						<< std::endl;

				countMissingElements = countMissingElements + (maxNormal.pos - rightCorrupt.pos - 1);

				if (countMissingElements >= numberMissingElem)
				{
					break;
				}
			}
			else
			{
				std::cout << "right corrupt " << rightCorrupt.value << " larger than max " << maxNormal.value << std::endl;
			}
		}

		auto normalDistance = rightNormal.pos - leftNormal.pos - 1;

		std::cout << "distance between " << leftNormal.value << " and: " << rightNormal.value << " is: " << normalDistance << std::endl;
		countMissingElements+= normalDistance;
		rightCorrupt.pos-=1;
		leftCorrupt.pos-=1;
	}
}
#endif

#endif /* CORRUPTEDFILE_H_ */
