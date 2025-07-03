#include "TestObject.h"
#include <iostream>

TestObject::TestObject() :a{}, b{} {}
TestObject::TestObject(int _a, int _b) :a{_a }, b{ _b } {}

void TestObject::TestMethod()
{
	std::cout << "called TestMethod" << std::endl;
}

TestObject::~TestObject()
{
}
