#include "SmallObjectAllocator.h"
#include <iostream>


namespace MemoryManagement
{
    SmallObjectAllocator::SmallObjectAllocator() {};

    void* SmallObjectAllocator::Allocate(std::size_t byteSize)
    {
        std::cout << "Allocate" << std::endl;
        return std::malloc(byteSize);
    }

    void SmallObjectAllocator::Deallocate(void* p, std::size_t byteSize)
    {
        std::cout << "Deallocate" << std::endl;
        std::free(p);
    }
}
