
#include <chrono>
#include <iostream>

#include "TestObject.h"

int main()
{
	auto start = std::chrono::high_resolution_clock::now();

	
	for (size_t i = 0; i < 100000000; i++)
	{
		TestObject* t = new TestObject();
	}

	auto end = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	std::cout << "Tempo totale: " << duration.count() / 1000.0 << "seconds" << std::endl;
}





