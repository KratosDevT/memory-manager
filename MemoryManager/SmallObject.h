#pragma once

#include <cstddef>
#include "SmallObjectAllocator.h"

namespace MemoryManagement
{
	// SmallObject overlaods operator new and operator delete and passes the allocation/deallocation requests to SmallObjectAllocator.
	// This way, you make your objects benefit from specialized allocation by simply deriving them from SmallObject.
    class SmallObject
    {

    public:
        static SmallObjectAllocator smallAllocator;
        
    public:
        static void* operator new(std::size_t size); // Static storage duration means that the variable resides in the same place in memory through the lifetime of the program.
        static void operator delete(void* p, std::size_t size);
        virtual ~SmallObject() {};
    };
    
}