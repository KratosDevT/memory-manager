
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
	std::cout << "Tempo totale 1BILLION allocazioni e deallocazioni con small object: " << duration.count() / 1000.0 << "seconds" << std::endl;
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
	std::cout << "Tempo totale 1BILLION allocazioni e deallocazioni con standard object: " << duration.count() / 1000.0 << "seconds" << std::endl;
}
int main()
{
	int numIterazioni = 1000 * 1000 * 1000;
	TestWithSmallObject(numIterazioni);
	TestWithoutSmallObject(numIterazioni);
}





