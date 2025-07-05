#include "SmallObject.h"

namespace MemoryManagement 
{
	SmallObject::SmallObject() {}

	SmallObjectAllocator SmallObject::smallAllocator(MAX_SMALL_OBJECT_SIZE);

	void* SmallObject::operator new(std::size_t size)
	{
		return smallAllocator.Allocate(size);
	}

	void SmallObject::operator delete(void* p, std::size_t size)
	{
		return smallAllocator.Deallocate(p, size);
	}
}