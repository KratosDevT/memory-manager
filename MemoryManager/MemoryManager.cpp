
#include <chrono>
#include <iostream>

#include "CustomAllocatedObject.h"
#include "StandardAllocatedObject.h"
#include "MemoryManager.h"


void TestWithSmallObject(int numIterazioni)
{
	auto start = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i < numIterazioni; i++)
	{
		CustomAllocatedObject* t = new CustomAllocatedObject();
		delete t;
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Tempo totale di " << numIterazioni << " alloc+dealloc SMALL OBJECT ALLOCATOR: " << duration.count() / 1000.000 << " secondi" << std::endl;
}

void TestWithoutSmallObject(int numIterazioni) {

	auto start = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i < numIterazioni; i++)
	{
		StandardAllocatedObject* t = new StandardAllocatedObject();
		delete t;
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Tempo totale di "<< numIterazioni <<" alloc+dealloc con allocatore di sistema : " << duration.count() / 1000.000 << " secondi" << std::endl;
}

int main()
{
	int numIterazioni = 1000 * 1000 * 100;
	TestWithSmallObject(numIterazioni);
	TestWithoutSmallObject(numIterazioni);
}





