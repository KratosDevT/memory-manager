#pragma once
#include <cstddef>
#include <vector>
#include "Chunk.h"

#ifndef MAX_SMALL_OBJECT_SIZE
#define MAX_SMALL_OBJECT_SIZE 64
#endif

namespace MemoryManagement
{
	// FixedAllocator contains an array of Chunks and manages them.
	// Whenever a request for memory comes and all existing Chunk are occupied, 
	// FixedAllocator creates a new Chunk and appends it to the array. Then satisfy the request.
	class FixedAllocator 
	{

	private:
		std::size_t  blockSize_;
		unsigned char numBlocks_;
		typedef std::vector<Chunk> Chunks;
		Chunks chunks_;
		Chunk* allocChunk_;
		Chunk* deallocChunk_;

		// For ensuring proper copy semantics
		mutable const FixedAllocator* prev_;
		mutable const FixedAllocator* next_;

		// Internal functions        
		void DoDeallocate(void* p);
		Chunk* VicinityFind(void* p);

	public:
		// Create a FixedAllocator able to manage blocks of 'blockSize' size
		FixedAllocator(std::size_t  blockSize_ = 0);
		FixedAllocator(const FixedAllocator&);
		FixedAllocator& operator=(const FixedAllocator& rhs);
		~FixedAllocator();

		void Swap(FixedAllocator& rhs);

		void* Allocate();
		void Deallocate(void* p);

		std::size_t BlockSize() const
		{
			return blockSize_;
		};
	};

}