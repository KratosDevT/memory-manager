#pragma once


class StandardAllocatedObject
{

public:
	int a;
	int b;
	int c;

public:
	StandardAllocatedObject();
	StandardAllocatedObject(int _a, int _b, int _c);
	void TestMethod();
	~StandardAllocatedObject();
};