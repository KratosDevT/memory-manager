#pragma once
#include <cstddef>

namespace MemoryManagement
{
	// SmallObjectAllocator provides general allocation and deallocation functions.
	// SmallObjectAllocator holds several FixedAllocator objects, each specialized for allocating objects of one specific size.
	// SmallObjectAllocator dispatches memory allocation requests to one FixedAllocator or to default ::operator new if the size requested is too large.
	class SmallObjectAllocator 
	{

	public:
		SmallObjectAllocator();
		void* Allocate(std::size_t byteSize);
		void Deallocate(void* p, std::size_t byteSize);
	};

}