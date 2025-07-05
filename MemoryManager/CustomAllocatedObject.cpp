#include "CustomAllocatedObject.h"
#include <iostream>

CustomAllocatedObject::CustomAllocatedObject(){}

CustomAllocatedObject::CustomAllocatedObject(int _a, int _b, int _c) :a{_a }, b{ _b }, c{ _c } {}

void CustomAllocatedObject::TestMethod()
{
	c = a + b;
}

CustomAllocatedObject::~CustomAllocatedObject()
{

}


