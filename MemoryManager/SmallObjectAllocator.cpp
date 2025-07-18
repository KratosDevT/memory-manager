#include "SmallObjectAllocator.h"
#include <iostream>
#include <cassert>
#include <functional>
#include <algorithm>

namespace MemoryManagement
{
    SmallObjectAllocator::SmallObjectAllocator(std::size_t maxObjectSize)
        : pLastAlloc_(0), pLastDealloc_(0)
        , maxObjectSize_(maxObjectSize)
    {}

    namespace Internal
    { 
        struct CompareFixedAllocatorSize
            : std::binary_function<const FixedAllocator&, std::size_t, bool>
        {
            bool operator()(const FixedAllocator& x, std::size_t numBytes) const
            {
                return x.BlockSize() < numBytes;
            }
        };
    }

    void* SmallObjectAllocator::Allocate(std::size_t numBytes)
    {
        if (numBytes > maxObjectSize_) return malloc(numBytes); 

        if (pLastAlloc_ && pLastAlloc_->BlockSize() == numBytes)
        {
            return pLastAlloc_->Allocate();
        }
        
        Pool::iterator i = std::lower_bound(pool_.begin(), pool_.end(), numBytes,
            Internal::CompareFixedAllocatorSize());
        
        if (i == pool_.end() || i->BlockSize() != numBytes)
        {
            i = pool_.insert(i, FixedAllocator(numBytes));
            pLastDealloc_ = &*pool_.begin();
        }
        pLastAlloc_ = &*i;
        return pLastAlloc_->Allocate();
    }

    void SmallObjectAllocator::Deallocate(void* p, std::size_t numBytes)
    {
        if (numBytes > maxObjectSize_) return free(p);

        if (pLastDealloc_ && pLastDealloc_->BlockSize() == numBytes)
        {
            pLastDealloc_->Deallocate(p);
            return;
        }
      
        Pool::iterator i = std::lower_bound(pool_.begin(), pool_.end(), numBytes,
            Internal::CompareFixedAllocatorSize());
       
        assert(i != pool_.end());
        assert(i->BlockSize() == numBytes);
        pLastDealloc_ = &*i;
        pLastDealloc_->Deallocate(p);
    }
}
