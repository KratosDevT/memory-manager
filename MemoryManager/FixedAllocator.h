#pragma once


namespace MemoryManagement
{
	// FixedAllocator contains an array of Chunks and manages them.
	// Whenever a request for memory comes and all existing Chunk are occupied, 
	// FixedAllocator creates a new Chunk and appends it to the array. Then satisfy the request.
	class FixedAllocator 
	{

	};

}