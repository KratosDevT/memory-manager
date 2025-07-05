
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

void StressMAssiveSMOATest(int iterations) {

	std::vector<CustomAllocatedObject*> objects;
	objects.reserve(iterations);

	auto start = std::chrono::high_resolution_clock::now();

	// Allocazione massiva
	for (int i = 0; i < iterations; ++i) {
		objects.push_back(new CustomAllocatedObject());
	}

	// Deallocazione massiva
	for (auto* obj : objects) {
		delete obj;
	}

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << "Alloc-Dealloc Massiva di " << iterations << " iterazioni con SMALL OBJECT ALLOCATOR : " << duration.count() / 1000000.000000 << " secondi" << std::endl;
}

void StressDefAllocMassiveTest(int iterations) {

	std::vector<StandardAllocatedObject*> objects;
	objects.reserve(iterations);

	auto start = std::chrono::high_resolution_clock::now();

	// Allocazione massiva
	for (int i = 0; i < iterations; ++i) {
		objects.push_back(new StandardAllocatedObject());
	}

	// Deallocazione massiva
	for (auto* obj : objects) {
		delete obj;
	}

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << "Alloc-Dealloc Massiva di " << iterations << " iterazioni con system allocator : " << duration.count() / 1000000.000000 << " secondi" << std::endl;
}

int main()
{
	int ordine = 1000 * 1000;
	int numIterazioni =  1 * ordine;
	TestWithSmallObject(numIterazioni);
	TestWithoutSmallObject(numIterazioni);

	StressDefAllocMassiveTest(numIterazioni);
	StressMAssiveSMOATest(numIterazioni);
}





