#ifndef MEMORYALLOCATOR_H_
#define MEMORYALLOCATOR_H_

#include <stddef.h>
#include <stdint.h>
#include <memory>
#include <cassert>
#include <iostream>
#include <string.h>

struct MemInfo
{
	size_t start;			// start address of memory (needs to be aligned to register size)
	size_t actualSize;		// size required by client
	size_t allocatedSize;	// allocated size by the library (aligned to register size)
};

std::ostream& operator << (std::ostream& lhs, const MemInfo& rhs)
{
	return lhs << "start: " << rhs.start << " actualSize: " << rhs.actualSize << " allocatedSize: " << rhs.allocatedSize;
}

struct Range
{
	size_t start;
	size_t end;
};

//Since overlapping rectangles are not allowed the comparison is simple
inline bool operator < (const Range& l, const Range& r)
{
    if (l.end < r.start)
    {
        return true;
    }

    return false;
}

//Since overlapping rectangles are not allowed the comparison is simple
inline bool operator > (const Range& l, const Range& r)
{
    if (l.start > r.end)
    {
        return true;
    }

    return false;
}

inline std::ostream& operator << (std::ostream& lhs, const Range& rhs)
{
	return lhs << "start: " << rhs.start << " end: " << rhs.end;
}

inline bool CanMergeRanges(const Range l, const Range m, const Range r)
{
	if (l.end + 1 != m.start)
	{
		return false;
	}

	if (m.end + 1 != r.start)
	{
		return false;
	}

	return true;
}

bool CanMergeRanges(const Range l, const Range r)
{
	if (l.end + 1 == r.start)
	{
		return true;
	}

	return false;
}

static const unsigned int MAGIC_COOKIE = 0xFF00AB01;

typedef unsigned int aligned_t;  ///< the register size that we need to align to

size_t AlignTo(size_t data, unsigned int alignment)
{
	//branch prediction
	if (data % alignment == 0)
	{
		return data;
	}

	auto res = data + alignment;
	return res - (res % alignment);
}

class List
{

public:
	class Node
	{
	public:
		Node(const MemInfo&& meminfo)
			: m_meminfo(meminfo)
			, inUse(true)
		{

		}

		MemInfo m_meminfo;				///< Memory related information
		Node* next = nullptr;			///< pointer to next free/allocated memory chunk
		Node* previous = nullptr;		///< pointer to previous free/allocated memory chunk
		bool inUse = false;				///< If this node is not used then it can be re-used by another component
		static const uint32_t s_magicCookie = MAGIC_COOKIE; 	///< sanity checker
	};

	//This will be used by the allocator::Allocate call to add an allocation node to the beginning of the list
	void AddToStart(Node* node)
	{
		if (!head)
		{
			tail = node;
			head = node;
		}
		else
		{
			head->next = node;
			node->previous = head;
			head = node;
		}
	}

	//[ALLOCATED]->[ALLOCATED(FREE 1)]->[ALLOCATED]->[FREE]->[ALLOCATED (FREE 2)]->[FREE]
	// [FREE 1] -> [FREE 2]  -> LIST
	void AddNext(Node* previous, Node* node)
	{
		//Instruct GCC_BUILTIN that this is highly unlikely to happen
		if (!head)
		{
			tail = node;
			head = node;
		}
		else
		{
			node->next = previous->next;
			previous->next = node;
			node->previous = previous;
		}
	}

	/// NodePrevious->node->NodeNext
	void RemoveNode(Node* node)
	{
		//Branch prediction
		if (node->next)
		{
			node->next->previous = node->previous;
		}

		//Branch prediction
		if (node->previous)
		{
			node->previous->next = node->next;
		}
	}

	//[ALLOCATED]->[ALLOCATED(FREE 2)]->[ALLOCATED]->[FREE]->[ALLOCATED (FREE 1)]->[FREE]
	//[FREE2]->[FREE1] -> LIST
	void AddBefore(Node* next, Node* node)
	{
		//Instruct GCC_BUILTIN that this is highly unlikely to happen to improve branch prediction
		if (!head)
		{
			head = node;
			tail = node;
		}
		else
		{
			node->previous = next->previous;
			node->next = next;
			next->previous = node;
		}
	}

	Node* head = nullptr;
	Node* tail = nullptr;
};

// Caching system
// Store the last allocated Node info so if another allocation start we can start from there to improve caching (or use the first entry of the Allocation list)
// Store the last free Node so we can check if we can return memory from there to improve caching


///Allocator default policy is that Free list is sorted by address so merging is possible (reduce fragmentation) -> user space application ?
/// Alternative policy could be to sort by size, larger block are in the beginning of the list (faster allocation, more fragmentation) -> real time system
class Allocator
{
public:
	/// Maximum amount of memory that we are going to manage
	explicit Allocator(size_t maxSize)
		: m_maxSize(AlignTo(maxSize, sizeof(aligned_t)))
	{
		m_heapAllocatedMemory = new unsigned char[m_maxSize];
		MemInfo info = { 0, m_maxSize, m_maxSize };

		List::Node* node = new List::Node(std::move(info));
		assert(m_maxSize % sizeof(aligned_t) == 0);
		assert(reinterpret_cast<ptrdiff_t>(m_heapAllocatedMemory) % sizeof(aligned_t) == 0);

		m_freeList.head = node;
		m_freeList.tail = node;

		std::cout << "size of hw alignment: " << sizeof(aligned_t) << " size of pointer: " << sizeof(List::Node*) << std::endl;

	}

	/// Memory[0-1000]
	/// FreeList = Free(0, 100) -> Free(200, 400) -> Free(800, 1000)
	/// 1) Client requests 16 bytes of free memory
	/// 2) We go through the free list and find the first chunk (0-17) + 1 byte for the node pointer + 6 bytes alignment
	/// 3) We align this to the register size (0-24),
	/// 4) We create a Node start=0 [0-8 will store the node info for freeing it], actualsize = 16, allocSize = 24
	/// 5) We write to address [0-8] the Node* ptr so we can find it later
	/// 6) Add this Node* to the allocation list to the end
	/// 7) Modify FreeList to be Free(24, 100) or remove it from the list if the entire memory was used
	void* Allocate(size_t size)
	{
		List::Node* currentNodeFromFreeList = m_freeList.head;
		while(1)
		{
			const size_t hwAlignment = AlignTo(size, sizeof(aligned_t));
			const size_t header = AlignTo(sizeof(List::Node*), sizeof(aligned_t));
			const size_t totalSizeRequired = hwAlignment + header;

			std::cout << "size: " << size << " hwAlignment: " << hwAlignment << " header: " << header << " total: " << totalSizeRequired << std::endl;

			if (currentNodeFromFreeList->m_meminfo.allocatedSize >= totalSizeRequired)
			{
				std::cout << "found free memory" << currentNodeFromFreeList->m_meminfo << std::endl;

				MemInfo info = { currentNodeFromFreeList->m_meminfo.start, size, totalSizeRequired };
				List::Node* newAllocationNode = new List::Node(std::move(info));

				std::cout << "Adding a new allocation block: " << info << " block address " << newAllocationNode << std::endl;
				m_allocationList.AddToStart(newAllocationNode);

				memcpy(&m_heapAllocatedMemory[currentNodeFromFreeList->m_meminfo.start], &newAllocationNode, sizeof(List::Node*));

				if (currentNodeFromFreeList->m_meminfo.allocatedSize == totalSizeRequired)
				{
					std::cout << "entire free block was used removing from free list" << std::endl;
					m_freeList.RemoveNode(currentNodeFromFreeList);
				}
				else
				{
					currentNodeFromFreeList->m_meminfo.actualSize-=size;
					currentNodeFromFreeList->m_meminfo.allocatedSize-= totalSizeRequired;
					currentNodeFromFreeList->m_meminfo.start+= totalSizeRequired;
					std::cout << "reducing size of new free block to " << currentNodeFromFreeList->m_meminfo << std::endl;
				}

				auto result = m_heapAllocatedMemory + newAllocationNode->m_meminfo.start + header;

				assert(reinterpret_cast<ptrdiff_t>(result) % sizeof(aligned_t) == 0);
				return result;

			}

			if (currentNodeFromFreeList == m_freeList.tail)
			{
				break;
			}
		}

		std::cerr << "run out of memory " << std::endl;
		return nullptr;
	}

	/// 1) Extract the Node* pointer from the ptr and make sure the magicCookie value is correct  Node(101, 199)
	/// 2) Go through the Freelist to find the appropriate location to insert the Node*
	/// 3) this can be before, after a node or merged with two adjusted to increase the memory
	/// 	3.1) Free(0, 100) -> Free(200, 400) -> Free(800, 1000)
	/// 	3.2) Free(0-400) -> Free(800, 1000)
	/// 4) 3 nodes have been merged to 1 so need to release the other 2
	/// 5) Remove the Node* from the allocation list
	void Free(void* ptr)
	{
		List::Node* node = nullptr;
		const size_t header = AlignTo(sizeof(List::Node*), sizeof(aligned_t));
		ptrdiff_t diff = reinterpret_cast<ptrdiff_t>(static_cast<char*>(ptr) - header);
		assert(diff > 0);

		memcpy(&node, reinterpret_cast<char*>(diff), sizeof(List::Node*));

		assert(node != nullptr);
		assert(node->s_magicCookie == MAGIC_COOKIE);

		std::cout << "freeing memory: " << node->m_meminfo << " from node: " << node << std::endl;

		List::Node* currentNode = m_freeList.head;

		/// Free list: [0-10]  [21-30]
		/// Node: [11-20]
		while(1)
		{
		    Range m = { node->m_meminfo.start,
		                node->m_meminfo.start + node->m_meminfo.allocatedSize - 1
		              };
		    Range l;
		    Range r;

		    List::Node* leftNode = nullptr;
            List::Node* midNode = node;
            List::Node* rightNode = nullptr;

            MemInfo* leftNodeMemInfo = nullptr;
            MemInfo* midNodeMemInfo  = &midNode->m_meminfo;
            MemInfo* rightNodeMemInfo = nullptr;

            // Check if we can we add this after the current node in the free list
		    if (node->m_meminfo.start >= currentNode->m_meminfo.start + currentNode->m_meminfo.allocatedSize)
			{
			    l = Range { currentNode->m_meminfo.start,
			                currentNode->m_meminfo.start + currentNode->m_meminfo.allocatedSize - 1
			              };

			    leftNode = currentNode;
			    leftNodeMemInfo = &leftNode->m_meminfo;
			    rightNode = currentNode->next;

			    if (rightNode)
			    {
			        r = Range { currentNode->next->m_meminfo.start,
			                    currentNode->next->m_meminfo.start + currentNode->next->m_meminfo.allocatedSize - 1
			                  };
			        rightNodeMemInfo = &rightNode->m_meminfo;
			    }

			}
		    // Can we add this before the current node in the free list ?
			else if (node->m_meminfo.start + node->m_meminfo.allocatedSize <= currentNode->m_meminfo.start)
			{
			    r = Range { currentNode->m_meminfo.start,
			                currentNode->m_meminfo.start + currentNode->m_meminfo.allocatedSize - 1
			              };

			    rightNode = currentNode;
			    rightNodeMemInfo = &rightNode->m_meminfo;
			    leftNode = currentNode->previous;

				// Check if we can do a 3 way merge
				if (leftNode)
				{
					l = { currentNode->previous->m_meminfo.start,
					      currentNode->previous->m_meminfo.start + currentNode->previous->m_meminfo.allocatedSize
					    };

					leftNodeMemInfo = &leftNode->m_meminfo;
				}
			}
			else
			{
			    std::cerr << "impossible " << std::endl;
			    exit(1);
			}

		    std::cout << "l: " << l << " r: " << r << " m: " << m << std::endl;

		    if (leftNode && rightNode && CanMergeRanges(l, m, r))
            {
                std::cout << "merging " << l << " with: " << m << " and " << r << std::endl;

                leftNodeMemInfo->allocatedSize+= midNodeMemInfo->allocatedSize;
                leftNodeMemInfo->allocatedSize+= rightNodeMemInfo->allocatedSize;

                leftNodeMemInfo->actualSize+= midNodeMemInfo->actualSize;
                leftNodeMemInfo->actualSize+= rightNodeMemInfo->actualSize;

                m_freeList.RemoveNode(rightNode);

                m_allocationList.RemoveNode(node);
                break;
            }
            else if (rightNode && CanMergeRanges(m, r))
            {
                std::cout << "merging middle " << m << " with right: " << r << std::endl;

                midNodeMemInfo->allocatedSize+= rightNodeMemInfo->allocatedSize;
                midNodeMemInfo->actualSize+= rightNodeMemInfo->actualSize;

                rightNode->m_meminfo = *midNodeMemInfo;

                m_allocationList.RemoveNode(node);
                break;
            }
            else if (leftNode && CanMergeRanges(l, m))
            {
                std::cout << "merging " << l << " with: " << m <<  std::endl;

                leftNodeMemInfo->allocatedSize+= midNodeMemInfo->allocatedSize;
                leftNodeMemInfo->actualSize+= midNodeMemInfo->actualSize;

                m_allocationList.RemoveNode(node);
                break;
            }
            else if (leftNode && m > l)
            {
                std::cout << " adding free block after left: " << l << std::endl;
                m_freeList.AddNext(leftNode, midNode);

                m_allocationList.RemoveNode(node);
                break;
            }
            else if (rightNode && m < r)
            {
                std::cout << " adding free block before right: " << r << std::endl;
                m_freeList.AddBefore(rightNode, midNode);

                m_allocationList.RemoveNode(node);
                break;
            }

			if (currentNode == m_freeList.tail)
			{
			    std::cerr << "error freeing memory" << std::endl;
				exit(1);
			}

			currentNode = currentNode->next;
		}
	}

	~Allocator()
	{
		delete[] m_heapAllocatedMemory;
	}

private:
	unsigned char* m_heapAllocatedMemory = nullptr;
	List m_freeList;
	List m_allocationList;
	size_t m_maxSize;
};

#endif /* MEMORYALLOCATOR_H_ */
