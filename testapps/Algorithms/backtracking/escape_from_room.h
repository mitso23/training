/*
 * escape_from_room.h
 *
 *  Created on: 30 Jul 2017
 *      Author: mitso23
 */

#ifndef ESCAPE_FROM_ROOM_H_
#define ESCAPE_FROM_ROOM_H_

#define MAX_ROOMS 8

struct SrcDst
{
	int src;
	int dst;
};

struct SrcDstVisited
{
	SrcDst srcDst;
	bool visited;
};

struct NextCandidate
{
	SrcDst srcDst;
	unsigned index;
};

SrcDst currentVisitedPath[MAX_ROOMS/2];
SrcDstVisited srcDstVisited[MAX_ROOMS/2];

unsigned maxCount = 1;

bool CanBeTransfered(unsigned int poscurrentVisitedPath, unsigned int sizecurrentVisitedPath, SrcDst srcDst)
{
	//std::cout << "src: " << srcDst.src << " dst: " << srcDst.dst << std::endl;
	for(unsigned int i=poscurrentVisitedPath; i< poscurrentVisitedPath + sizecurrentVisitedPath; ++i)
	{
		//std::cout << "path->src: " << currentVisitedPath[i].src << "path->dst: " << currentVisitedPath[i].dst << std::endl;

		if ((srcDst.src > currentVisitedPath[i].src && srcDst.dst < currentVisitedPath[i].dst) ||
				(srcDst.src < currentVisitedPath[i].src && srcDst.dst > currentVisitedPath[i].dst) ||
				(srcDst.dst == currentVisitedPath[i].src + 1))
		{
			return false;
		}
	}

	return true;
}

bool isAllVisited(unsigned size)
{
	for(unsigned int i=0; i< size; ++i)
	{
		if (srcDstVisited[i].visited == false)
		{
			return false;
		}
	}

	return true;
}

int FindNextAvailableSlot(unsigned int current, unsigned size)
{
	for (unsigned int i = current + 1; i < size; ++i)
	{
		if (srcDstVisited[i].visited == false)
		{
			return i;
		}
	}

	return -1;
}

void FindMinTimeEscape(unsigned int poscurrentVisitedPathStart, unsigned int sizecurrentVisitedPath, unsigned int& count, unsigned int currDst, unsigned int size)
{
	if (isAllVisited(size))
	{
		std::cout << "All Visited" << std::endl;
		srcDstVisited[currDst].visited = false;
		return;
	}

	if (count > maxCount)
	{
		maxCount = count;
	}

	std::cout << "pos: " << poscurrentVisitedPathStart << " size: " << sizecurrentVisitedPath << " index: " << currDst <<
			" src: " << srcDstVisited[currDst].srcDst.src  << " dst: " << srcDstVisited[currDst].srcDst.dst << std::endl;

	//Add current srcDst to the path
	srcDstVisited[currDst].visited = true;
	currentVisitedPath[poscurrentVisitedPathStart + sizecurrentVisitedPath].dst = srcDstVisited[currDst].srcDst.dst;
	currentVisitedPath[poscurrentVisitedPathStart + sizecurrentVisitedPath].src = srcDstVisited[currDst].srcDst.src;
	++sizecurrentVisitedPath;

	// Find all the rooms that can be transfered in one go
	NextCandidate nextCandidates[MAX_ROOMS/2];
	unsigned int j = 0;
	for(unsigned int i =currDst + 1; i< size; ++i)
	{
		bool can = CanBeTransfered(poscurrentVisitedPathStart, sizecurrentVisitedPath, srcDstVisited[i].srcDst);
		if (can)
		{
			std::cout << "next candidate src: " << srcDstVisited[i].srcDst.src  << " dst: " << srcDstVisited[i].srcDst.dst << std::endl;

			nextCandidates[j].srcDst = srcDstVisited[i].srcDst;
			nextCandidates[j].index = i;
			++j;
		}
		else
		{
			std::cout << "not a candidate src: " << srcDstVisited[i].srcDst.src  << " dst: " << srcDstVisited[i].srcDst.dst << std::endl;
		}
	}

	if (j == 0)
	{
		int next = FindNextAvailableSlot(currDst, size);
		std::cout << "0 candidates found next choice: " << next << std::endl;

		if (next != -1)
		{
			++count;
			FindMinTimeEscape(poscurrentVisitedPathStart + sizecurrentVisitedPath, 0, count, next, size);
			--count;
		}
	}
	else
	{
		for(unsigned int i=0; i< j; ++i)
		{
			NextCandidate nextDst = nextCandidates[i];
			FindMinTimeEscape(poscurrentVisitedPathStart, sizecurrentVisitedPath, count, nextDst.index, size);
			srcDstVisited[nextDst.index].visited = false;
		}
	}

	srcDstVisited[currDst].visited = false;
	std::cout << "returning: " << currDst << std::endl;
}

#endif /* ESCAPE_FROM_ROOM_H_ */
