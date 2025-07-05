#pragma once
#include <cstddef>
#include <vector>
#include "FixedAllocator.h"

namespace MemoryManagement
{
	// SmallObjectAllocator provides general allocation and deallocation functions.
	// SmallObjectAllocator holds several FixedAllocator objects, each specialized for allocating objects of one specific size.
	// SmallObjectAllocator dispatches memory allocation requests to one FixedAllocator or to default ::operator new if the size requested is too large.
	class SmallObjectAllocator 
	{

	public:
		SmallObjectAllocator();
		SmallObjectAllocator(std::size_t defaultChunkSize, std::size_t maxObjectSize);

		void* Allocate(std::size_t numBytes);
		void Deallocate(void* p, std::size_t numBytes);
	
	private:

		SmallObjectAllocator(const SmallObjectAllocator&);
		//SmallObjectAllocator& operator=(const SmallObjectAllocator&);

		typedef std::vector<FixedAllocator> Pool;
		Pool pool_;
		FixedAllocator* pLastAlloc_;
		FixedAllocator* pLastDealloc_;
		std::size_t defaultChunkSize_;
		std::size_t maxObjectSize_;
	};

}