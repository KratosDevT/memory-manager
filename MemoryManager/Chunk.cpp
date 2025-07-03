#include "Chunk.h"
#include <cassert>

namespace MemoryManagement
{
	// Initializes a chunk object
	void Chunk::Init(std::size_t blockSize, unsigned char blocks)
	{
		assert(blockSize > 0);
		assert(blocks > 0);

		// Overflow check
		assert((blockSize * blocks) / blockSize == blocks);

		pData_ = static_cast<unsigned char*>(malloc(blockSize * blocks)); //better use delete and new?
		//pData_ = new unsigned char[blockSize * blocks];

		Reset(blockSize, blocks);
	}

	// Clears an already allocated chunk
	void Chunk::Reset(std::size_t blockSize, unsigned char blocks)
	{
		assert(blockSize > 0);
		assert(blocks > 0);
		// Overflow check
		assert((blockSize * blocks) / blockSize == blocks);

		firstAvailableBlock_ = 0;
		blocksAvailable_ = blocks;

		unsigned char i = 0;
		unsigned char* pIter = pData_;
		for (; i != blocks; pIter += blockSize)
		{
			*pIter = ++i;
		}
	}

	void Chunk::Release()
	{
		free(pData_); //better use delete and new?
		//delete[] pData_;
	}

	// Allocates a block from a chunk
	void* Chunk::Allocate(std::size_t blockSize) 
	{
		if (!blocksAvailable_) return 0;

		assert((firstAvailableBlock_ * blockSize) / blockSize == firstAvailableBlock_);

		unsigned char* pResult = pData_ + (firstAvailableBlock_ * blockSize);
		firstAvailableBlock_ = *pResult;
		--blocksAvailable_;

		return pResult;
	}

	// Dellocates a block from a chunk
	void Chunk::Deallocate(void* p, std::size_t blockSize)
	{
		assert(p >= pData_);//pointer check

		unsigned char* toRelease = static_cast<unsigned char*>(p);//needed to use pointer math
		
		assert((toRelease - pData_) % blockSize == 0);//alignment check

		*toRelease = firstAvailableBlock_;
		firstAvailableBlock_ = static_cast<unsigned char>((toRelease - pData_) / blockSize);

		assert(firstAvailableBlock_ == ((toRelease - pData_) / blockSize));//truncation check

		++blocksAvailable_;
	}
}
