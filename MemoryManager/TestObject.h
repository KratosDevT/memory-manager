#pragma once
#include "SmallObject.h"

class TestObject : public MemoryManagement::SmallObject
{

public:
	int a;
	int b;

public:
	TestObject();
	TestObject(int _a, int _b);
	void TestMethod();
	~TestObject() override;
};