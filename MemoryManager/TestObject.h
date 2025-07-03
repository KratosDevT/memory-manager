#pragma once
#include "SmallObject.h"

class TestObject : public MemoryManagement::SmallObject
{

public:
	int a;
	int b;
	int c;

public:
	TestObject();
	TestObject(int _a, int _b, int _c);
	void TestMethod();
	~TestObject() override;
};