#include "FixedAllocator.h"
#include <cassert>

namespace MemoryManagement
{

	FixedAllocator::FixedAllocator(std::size_t blockSize)
		: blockSize_(blockSize)
		, allocChunk_(0)
		, deallocChunk_(0)
	{
		assert(blockSize_ > 0);

		prev_ = next_ = this;

		std::size_t numBlocks = DEFAULT_CHUNK_SIZE / blockSize;
		if (numBlocks > UCHAR_MAX) numBlocks = UCHAR_MAX;
		else if (numBlocks == 0) numBlocks = 8 * blockSize;//???

		numBlocks_ = static_cast<unsigned char>(numBlocks);
		assert(numBlocks_ == numBlocks);
	}

	FixedAllocator::FixedAllocator(const FixedAllocator& rhs)
		: blockSize_(rhs.blockSize_)
		, numBlocks_(rhs.numBlocks_)
		, chunks_(rhs.chunks_)
	{
		prev_ = &rhs;
		next_ = rhs.next_;
		rhs.next_->prev_ = this;
		rhs.next_ = this;

		allocChunk_ = rhs.allocChunk_
			? &chunks_.front() + (rhs.allocChunk_ - &rhs.chunks_.front())
			: 0;

		deallocChunk_ = rhs.deallocChunk_
			? &chunks_.front() + (rhs.deallocChunk_ - &rhs.chunks_.front())
			: 0;
	}

	FixedAllocator& FixedAllocator::operator=(const FixedAllocator& rhs)
	{
		FixedAllocator copy(rhs);
		copy.Swap(*this);
		return *this;
	}

	FixedAllocator::~FixedAllocator()
	{
		if (prev_ != this)
		{
			prev_->next_ = next_;
			next_->prev_ = prev_;
			return;
		}

		assert(prev_ == next_);
		Chunks::iterator i = chunks_.begin();
		for (; i != chunks_.end(); ++i)
		{
			assert(i->blocksAvailable_ == numBlocks_);
			i->Release();
		}
	}

	void FixedAllocator::Swap(FixedAllocator& rhs)
	{
		using namespace std;

		swap(blockSize_, rhs.blockSize_);
		swap(numBlocks_, rhs.numBlocks_);
		chunks_.swap(rhs.chunks_);
		swap(allocChunk_, rhs.allocChunk_);
		swap(deallocChunk_, rhs.deallocChunk_);
	}

	void* FixedAllocator::Allocate()
	{
		if (allocChunk_ == 0 || allocChunk_->blocksAvailable_ == 0)
		{
			Chunks::iterator i = chunks_.begin();
			for (;; ++i)
			{
				if (i == chunks_.end()) 
				{
					chunks_.reserve(chunks_.size() + 1);
					Chunk newChunk;
					newChunk.Init(blockSize_, numBlocks_);
					chunks_.push_back(newChunk);
					allocChunk_ = &chunks_.back();
					deallocChunk_ = &chunks_.back();
					break;
				}

				if (i->blocksAvailable_ > 0)
				{
					allocChunk_ = &*i;
					break;
				}
			}
		}

		assert(allocChunk_ != 0);
		assert(allocChunk_->blocksAvailable_ > 0);

		return allocChunk_->Allocate(blockSize_);
	}

	void FixedAllocator::Deallocate(void* p)
	{
		assert(!chunks_.empty());
		assert(&chunks_.front() <= deallocChunk_);
		assert(&chunks_.back() >= deallocChunk_);

		deallocChunk_ = VicinityFind(p);
		assert(deallocChunk_);

		DoDeallocate(p);
	}

	Chunk* FixedAllocator::VicinityFind(void* p)
	{
		assert(!chunks_.empty());
		assert(deallocChunk_);

		const std::size_t chunkLength = numBlocks_ * blockSize_;

		Chunk* lo = deallocChunk_;
		Chunk* hi = deallocChunk_ + 1;
		Chunk* loBound = &chunks_.front();
		Chunk* hiBound = &chunks_.back() + 1;

		// Special case: deallocChunk_ is the last in the array
		if (hi == hiBound) hi = 0;

		for (;;)
		{
			if (lo)
			{
				if (p >= lo->pData_ && p < lo->pData_ + chunkLength)
				{
					return lo;
				}
				if (lo == loBound) lo = 0;
				else --lo;
			}

			if (hi)
			{
				if (p >= hi->pData_ && p < hi->pData_ + chunkLength)
				{
					return hi;
				}
				if (++hi == hiBound) hi = 0;
			}
		}
		assert(false);
		return 0;
	}

	void FixedAllocator::DoDeallocate(void* p)
	{
		assert(deallocChunk_->pData_ <= p);
		assert(deallocChunk_->pData_ + numBlocks_ * blockSize_ > p);

		// call into the chunk, will adjust the inner list but won't release memory
		deallocChunk_->Deallocate(p, blockSize_);

		if (deallocChunk_->blocksAvailable_ == numBlocks_)
		{
			// deallocChunk_ is completely free, should we release it? 

			Chunk& lastChunk = chunks_.back();

			if (&lastChunk == deallocChunk_)
			{
				// check if we have two last chunks empty

				if (chunks_.size() > 1 &&
					deallocChunk_[-1].blocksAvailable_ == numBlocks_)
				{
					// Two free chunks, discard the last one
					lastChunk.Release();
					chunks_.pop_back();
					allocChunk_ = deallocChunk_ = &chunks_.front();
				}
				return;
			}

			if (lastChunk.blocksAvailable_ == numBlocks_)
			{
				// Two free blocks, discard one
				lastChunk.Release();
				chunks_.pop_back();
				allocChunk_ = deallocChunk_;
			}
			else
			{
				// move the empty chunk to the end
				std::swap(*deallocChunk_, lastChunk);
				allocChunk_ = &chunks_.back();
			}
		}
	}
}

