#include "SmallObject.h"

namespace MemoryManagement 
{
	SmallObjectAllocator SmallObject::smallAllocator;

	SmallObject::SmallObject()
	{
	}

	void* SmallObject::operator new(std::size_t size)
	{
		return smallAllocator.Allocate(size);
	}

	void SmallObject::operator delete(void* p, std::size_t size)
	{
		return smallAllocator.Deallocate(p, size);
	}
}