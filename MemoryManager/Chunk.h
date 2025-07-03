#pragma once
#include <iostream>

namespace MemoryManagement
{
	// Chunk cointains and manages a chunk of memory consisting of an integral number of fixed-size objects.
	// Chunk contains logic that allows you to allocate and deallocate memory blocks.
	// When there are no more blocks available in the chunk, the allocation function fails returning zero.   
	// for efficiency reasons Chunk does not define constructors, destructors, or assignment operator.
	// This could be hurts efficiency at upper levels where we store Chunk objects in a vector
	struct Chunk
	{
		unsigned char* pData_;
		unsigned char firstAvailableBlock_, blocksAvailable_; // this means the Chunk cannot have more than 255 blocks if sizeof(char)=8bit

		void Init(std::size_t blockSize, unsigned char blocks); //initialize the blockSize and the number of blocks of this Chunk
		void* Allocate(std::size_t blockSize); //allocates a block, the block size is known at a superior level, put here is a waste of time and space
		void Deallocate(void* p, std::size_t blockSize); //deallocates a block
		void Reset(std::size_t blockSize, unsigned char blocks);
		void Release(); // release the allocated memory (physics memory)
	};
}