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
		{

		}

		MemInfo m_meminfo;				                        ///< Memory related information
		Node* next = nullptr;			                        ///< pointer to next free/allocated memory chunk
		Node* previous = nullptr;		                        ///< pointer to previous free/allocated memory chunk
		static const uint32_t s_magicCookie = MAGIC_COOKIE; 	///< sanity checker
	};

	//This will be used by the allocator::Allocate call to add an allocation node to the beginning of the list
	void AddToStart(Node* node)
	{
		if (!head)
		{
			head = node;
		}
		else
		{
			node->next = head;
			head->previous = node;
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

		if (node->next)
		{
			node->next->previous = node->previous;
		}

		if (node->previous)
		{
			node->previous->next = node->next;
		}

		if (node == head)
		{
		    head = node->next;
		}

		node->next = nullptr;
		node->previous = nullptr;
	}

	//[ALLOCATED]->[ALLOCATED(FREE 2)]->[ALLOCATED]->[FREE]->[ALLOCATED (FREE 1)]->[FREE]
	//[FREE2]->[FREE1] -> LIST
	void AddBefore(Node* next, Node* node)
	{
		//Instruct GCC_BUILTIN that this is highly unlikely to happen to improve branch prediction
		if (!head)
		{
			head = node;
		}
		else
		{

			node->previous = next->previous;
            node->next = next;
            next->previous = node;

            if (next == head)
            {
                head = node;
            }
		}
	}

	Node* head = nullptr;
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

		while(currentNodeFromFreeList)
		{
			const size_t hwAlignment = AlignTo(size, sizeof(aligned_t));
			const size_t header = AlignTo(sizeof(List::Node*), sizeof(aligned_t));
			const size_t totalSizeRequired = hwAlignment + header;

			std::cout << "size: " << size << " aligning size to HW: " << hwAlignment << " header: " << header << " total: " << totalSizeRequired << std::endl;

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
			else
			{
			    std::cout << "trying next block: " << std::endl;
			    currentNodeFromFreeList = currentNodeFromFreeList->next;
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
		List::Node* nodeToBeFreed = nullptr;
		const size_t header = AlignTo(sizeof(List::Node*), sizeof(aligned_t));
		ptrdiff_t diff = reinterpret_cast<ptrdiff_t>(static_cast<char*>(ptr) - header);
		assert(diff > 0);

		memcpy(&nodeToBeFreed, reinterpret_cast<char*>(diff), sizeof(List::Node*));

		assert(nodeToBeFreed != nullptr);
		assert(nodeToBeFreed->s_magicCookie == MAGIC_COOKIE);

		std::cout << "freeing memory: " << nodeToBeFreed->m_meminfo << " from node: " << nodeToBeFreed << std::endl;

		List::Node* currentNodeFreeList = m_freeList.head;

		/// Free list: [0-10]  [21-30]
		/// Node: [11-20]
		while(currentNodeFreeList)
		{
		    Range m = { nodeToBeFreed->m_meminfo.start,
		                nodeToBeFreed->m_meminfo.start + nodeToBeFreed->m_meminfo.allocatedSize - 1
		              };
		    Range l;
		    Range r;

		    List::Node* leftNode = nullptr;
            List::Node* midNode = nodeToBeFreed;
            List::Node* rightNode = nullptr;

            MemInfo* leftNodeMemInfo = nullptr;
            MemInfo* midNodeMemInfo  = &midNode->m_meminfo;
            MemInfo* rightNodeMemInfo = nullptr;

            // Check if we can we add this after the current node in the free list
		    if (nodeToBeFreed->m_meminfo.start >= currentNodeFreeList->m_meminfo.start + currentNodeFreeList->m_meminfo.allocatedSize)
			{
			    l = Range { currentNodeFreeList->m_meminfo.start,
			                currentNodeFreeList->m_meminfo.start + currentNodeFreeList->m_meminfo.allocatedSize - 1
			              };

			    leftNode = currentNodeFreeList;
			    leftNodeMemInfo = &leftNode->m_meminfo;
			    rightNode = currentNodeFreeList->next;

			    if (rightNode)
			    {
			        r = Range { currentNodeFreeList->next->m_meminfo.start,
			                    currentNodeFreeList->next->m_meminfo.start + currentNodeFreeList->next->m_meminfo.allocatedSize - 1
			                  };
			        rightNodeMemInfo = &rightNode->m_meminfo;
			    }

			}
		    // Can we add this before the current node in the free list ?
			else if (nodeToBeFreed->m_meminfo.start + nodeToBeFreed->m_meminfo.allocatedSize <= currentNodeFreeList->m_meminfo.start)
			{
			    r = Range { currentNodeFreeList->m_meminfo.start,
			                currentNodeFreeList->m_meminfo.start + currentNodeFreeList->m_meminfo.allocatedSize - 1
			              };

			    rightNode = currentNodeFreeList;
			    rightNodeMemInfo = &rightNode->m_meminfo;
			    leftNode = currentNodeFreeList->previous;

				// Check if we can do a 3 way merge
				if (leftNode)
				{
					l = { currentNodeFreeList->previous->m_meminfo.start,
					      currentNodeFreeList->previous->m_meminfo.start + currentNodeFreeList->previous->m_meminfo.allocatedSize
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
		        m_allocationList.RemoveNode(nodeToBeFreed);

                std::cout << "merging " << l << " with: " << m << " and " << r << std::endl;

                leftNodeMemInfo->allocatedSize+= midNodeMemInfo->allocatedSize;
                leftNodeMemInfo->allocatedSize+= rightNodeMemInfo->allocatedSize;

                leftNodeMemInfo->actualSize+= midNodeMemInfo->actualSize;
                leftNodeMemInfo->actualSize+= rightNodeMemInfo->actualSize;

                m_freeList.RemoveNode(rightNode);

                return;
            }
            else if (rightNode && CanMergeRanges(m, r))
            {
                m_allocationList.RemoveNode(nodeToBeFreed);

                std::cout << "merging middle " << m << " with right: " << r << std::endl;

                midNodeMemInfo->allocatedSize+= rightNodeMemInfo->allocatedSize;
                midNodeMemInfo->actualSize+= rightNodeMemInfo->actualSize;

                rightNode->m_meminfo = *midNodeMemInfo;

                return;
            }
            else if (leftNode && CanMergeRanges(l, m))
            {
                m_allocationList.RemoveNode(nodeToBeFreed);

                std::cout << "merging left " << l << " with middle: " << m <<  std::endl;

                leftNodeMemInfo->allocatedSize+= midNodeMemInfo->allocatedSize;
                leftNodeMemInfo->actualSize+= midNodeMemInfo->actualSize;


                return;
            }
            else if (leftNode && m > l)
            {
                m_allocationList.RemoveNode(nodeToBeFreed);

                std::cout << " adding free block after left: " << l << std::endl;
                m_freeList.AddNext(leftNode, midNode);

                return;
            }
            else if (rightNode && m < r)
            {
                m_allocationList.RemoveNode(nodeToBeFreed);

                std::cout << " adding free block before right: " << r << std::endl;
                m_freeList.AddBefore(rightNode, midNode);

                return;
            }

		    currentNodeFreeList = currentNodeFreeList->next;

			if (!currentNodeFreeList)
			{
			    std::cerr << "error freeing memory" << std::endl;
				exit(1);
			}
		}

		//If we are here it means that the free list was empty [everything was already allocated]
	    m_allocationList.RemoveNode(nodeToBeFreed);
		m_freeList.AddToStart(nodeToBeFreed);
	}

	~Allocator()
	{
		delete[] m_heapAllocatedMemory;
	}

	size_t GetFreeSize()
	{
	    auto current = m_freeList.head;
	    size_t freeSize = 0;

	    while(current)
	    {
	        freeSize+= current->m_meminfo.allocatedSize;
	        current = current->next;

	        if (!current)
	        {
	            break;
	        }
	    }

	    std::cout << "amount of free space is " << freeSize << std::endl;

	    return freeSize;
	}

	size_t GetAllocatedSize()
	{
	    auto current = m_allocationList.head;
	    size_t allocatedSize = 0;

	    while(current)
	    {
	        allocatedSize+= current->m_meminfo.allocatedSize;
	        current = current->next;

	        if (!current)
	        {
	            break;
	        }
	    }

	    std::cout << "amount of allocated memory is " << allocatedSize << std::endl;

	    return allocatedSize;
	}

private:
	unsigned char* m_heapAllocatedMemory = nullptr;
	List m_freeList;
	List m_allocationList;
	size_t m_maxSize;
};


// available memory is [0-15] and make sure the entire one is used and we have 0 memory
void TestOneFullAllocation()
{
    Allocator allocator(16);

    if (allocator.GetFreeSize() != 16)
    {
        std::cerr << "error" << std::endl;
        exit(-1);
    }

    auto ptr = allocator.Allocate(7);

    if (allocator.GetAllocatedSize() != 16)
    {
        std::cerr << "error " << std::endl;
        exit(-1);
    }

    if (allocator.GetFreeSize() != 0)
    {
        std::cerr << "error" << std::endl;
        exit(-1);
    }

    allocator.Free(ptr);

    if (allocator.GetFreeSize() != 16)
    {
        std::cerr << "error" << std::endl;
        exit(-1);
    }

    if (allocator.GetAllocatedSize() != 0)
    {
       std::cerr << "error " << std::endl;
       exit(-1);
    }
}

//[0-31] Allocation
// Allocate 8 ptr1
//      ** Free one list start 16, 31
//      ** alloc1[0-15]
// Allocate 8 ptr2
//      ** Free list is empty
//      ** alloc2[16,31]->alloc1[0-15]

// Free 8 ptr1
//      ** free list one entry [0-15]

// Free 8 ptr2
//      ** free list one entry merge with previous [0-31]
void TestTwoBackToBackAllocationsFreeInOrder()
{
    Allocator allocator(32);

    auto ptr1 = allocator.Allocate(7);

    if (allocator.GetFreeSize() != 16)
    {
       std::cerr << "error" << std::endl;
       exit(-1);
    }

    if (allocator.GetAllocatedSize() != 16)
    {
       std::cerr << "error " << std::endl;
       exit(-1);
    }

    auto ptr2 = allocator.Allocate(7);

    if (allocator.GetFreeSize() != 0)
    {
        std::cerr << "error" << std::endl;
        exit(-1);
    }

    if (allocator.GetAllocatedSize() != 32)
    {
        std::cerr << "error " << std::endl;
        exit(-1);
    }

    allocator.Free(ptr1);

    if (allocator.GetFreeSize() != 16)
    {
      std::cerr << "error" << std::endl;
      exit(-1);
    }

    if (allocator.GetAllocatedSize() != 16)
    {
      std::cerr << "error " << std::endl;
      exit(-1);
    }

    allocator.Free(ptr2);
    if (allocator.GetFreeSize() != 32)
    {
      std::cerr << "error" << std::endl;
      exit(-1);
    }

    if (allocator.GetAllocatedSize() != 0)
    {
      std::cerr << "error " << std::endl;
      exit(-1);
    }
}


//[0-31] Allocation
// Allocate 8 ptr1
//      ** Free one list start 16, 31
//      ** alloc1[0-15]
// Allocate 8 ptr2
//      ** Free list is empty
//      ** alloc2[16,31]->alloc1[0-15]

// Free 8 ptr2
//      ** free list one entry [16-31]
//      ** allocator one entry [0-15]

// Free 8 ptr1
//      ** free list one entry merge with previous [0-31]
//      ** allocator list should be empty
void TestTwoBackToBackAllocationsFreeOutOfOrder()
{
    Allocator allocator(32);

    auto ptr1 = allocator.Allocate(7);

    if (allocator.GetFreeSize() != 16)
    {
       std::cerr << "error" << std::endl;
       exit(-1);
    }

    if (allocator.GetAllocatedSize() != 16)
    {
       std::cerr << "error " << std::endl;
       exit(-1);
    }

    auto ptr2 = allocator.Allocate(7);

    if (allocator.GetFreeSize() != 0)
    {
        std::cerr << "error" << std::endl;
        exit(-1);
    }

    if (allocator.GetAllocatedSize() != 32)
    {
        std::cerr << "error " << std::endl;
        exit(-1);
    }

    allocator.Free(ptr2);

    if (allocator.GetFreeSize() != 16)
    {
      std::cerr << "error" << std::endl;
      exit(-1);
    }

    if (allocator.GetAllocatedSize() != 16)
    {
      std::cerr << "error " << std::endl;
      exit(-1);
    }

    allocator.Free(ptr1);
    if (allocator.GetFreeSize() != 32)
    {
      std::cerr << "error" << std::endl;
      exit(-1);
    }

    if (allocator.GetAllocatedSize() != 0)
    {
      std::cerr << "error " << std::endl;
      exit(-1);
    }
}

//[0-128] Allocation
// Allocate 8 ptr1  [1]
//      ** Free one list start 16, 128
//      ** alloc1[0-15]
// Allocate 8 ptr2   [2]
//      ** Free one list start [32-128]
//      ** alloc2[16,31]->alloc1[0-15]

// Allocate 8 ptr3 [3]
//     ** Free one list start[48-128]
//     ** alloc3[32-47]->alloc2[16-31]->alloc1[0,15]

// Free 8 ptr2 [4]
//      ** free list one entry [16-31]->[48-128]
//      ** alloc3[32-47]->alloc1[0-15]

// Allocate 16 ptr4 [5]
//      ** free list two entries [16-31]->[72-128]
//      ** alloc4[48-71]->alloc3[32-47]->alloc1[0-15]

// Free ptr4 [6]
//      ** free list two entries [16-31]->[48-128]
//      ** alloc3[32-47]->alloc1[0-15]

// Free ptr3 [7]
//      ** free list one entry [16-128]
//      ** alloc1[0-15]

// Free ptr1 [7]
//      ** free list one entry[0-128]
//      ** list is empty

void TestMultipleAllocationsFrees()
{
    Allocator allocator(128);

    // [1]
    auto ptr1 = allocator.Allocate(8);

    if (allocator.GetFreeSize() != 112)
    {
        std::cerr << "error" << std::endl;
        exit(-1);
    }

    if (allocator.GetAllocatedSize() != 16)
    {
        std::cerr << "error " << std::endl;
        exit(-1);
    }

    //[2]
    auto ptr2 = allocator.Allocate(8);

    if (allocator.GetFreeSize() != 96)
    {
        std::cerr << "error" << std::endl;
        exit(-1);
    }

    if (allocator.GetAllocatedSize() != 32)
    {
        std::cerr << "error " << std::endl;
        exit(-1);
    }

    // [3]
    auto ptr3 = allocator.Allocate(8);

    if (allocator.GetFreeSize() != 80)
    {
        std::cerr << "error" << std::endl;
        exit(-1);
    }

    if (allocator.GetAllocatedSize() != 48)
    {
        std::cerr << "error " << std::endl;
        exit(-1);
    }

    // [4]
    allocator.Free(ptr2);

    if (allocator.GetFreeSize() != 96)
    {
        std::cerr << "error" << std::endl;
        exit(-1);
    }

    if (allocator.GetAllocatedSize() != 32)
    {
        std::cerr << "error " << std::endl;
        exit(-1);
    }

    // [5]
    auto ptr4 = allocator.Allocate(16);

    if (allocator.GetFreeSize() != 72)
    {
        std::cerr << "error" << std::endl;
        exit(-1);
    }

    if (allocator.GetAllocatedSize() != 56)
    {
        std::cerr << "error " << std::endl;
        exit(-1);
    }

    // [6]
    allocator.Free(ptr4);

    if (allocator.GetFreeSize() != 96)
    {
        std::cerr << "error" << std::endl;
        exit(-1);
    }

    if (allocator.GetAllocatedSize() != 32)
    {
        std::cerr << "error " << std::endl;
        exit(-1);
    }

    allocator.Free(ptr3);

    if (allocator.GetFreeSize() != 112)
    {
        std::cerr << "error" << std::endl;
        exit(-1);
    }

    if (allocator.GetAllocatedSize() != 16)
    {
        std::cerr << "error " << std::endl;
        exit(-1);
    }

    // [7]
    allocator.Free(ptr1);

    if (allocator.GetFreeSize() != 128)
    {
        std::cerr << "error" << std::endl;
        exit(-1);
    }

    if (allocator.GetAllocatedSize() != 0)
    {
        std::cerr << "error " << std::endl;
        exit(-1);
    }
}

#endif /* MEMORYALLOCATOR_H_ */
