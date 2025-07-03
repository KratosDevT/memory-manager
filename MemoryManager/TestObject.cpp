#include "TestObject.h"
#include <iostream>

TestObject::TestObject() :a{}, b{} {}
TestObject::TestObject(int _a, int _b, int _c) :a{_a }, b{ _b }, c{ _c } {}

void TestObject::TestMethod()
{
	/*std::cout << "TestObject " << "[ a = " << a << ", b = " << b<< " ]";
	std::cout << std::endl;*/
	c = a + b;
}

TestObject::~TestObject()
{

}


