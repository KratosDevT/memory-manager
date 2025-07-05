#include "StandardAllocatedObject.h"
#include <iostream>

StandardAllocatedObject::StandardAllocatedObject(){}

StandardAllocatedObject::StandardAllocatedObject(int _a, int _b, int _c) :a{ _a }, b{ _b }, c{ _c } {}

void StandardAllocatedObject::TestMethod()
{
	c = a + b;
}

StandardAllocatedObject::~StandardAllocatedObject()
{

}