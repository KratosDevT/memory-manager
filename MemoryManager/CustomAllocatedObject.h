#pragma once
#include "SmallObject.h"

class CustomAllocatedObject : public MemoryManagement::SmallObject
{

public:
	int a;
	int b;
	int c;

public:
	CustomAllocatedObject();
	CustomAllocatedObject(int _a, int _b, int _c);
	void TestMethod();
	~CustomAllocatedObject() override;
};