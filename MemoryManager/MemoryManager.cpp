
#include <iostream>

#include "TestObject.h"

int main()
{
	TestObject* obj = new TestObject();
  
	obj->TestMethod();
	
	delete obj;
}





