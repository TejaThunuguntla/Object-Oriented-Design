#ifndef TEST2
#define TEST2

#include "TestProj1.h"

using namespace _Namespace;

struct _struct : public _class1
{
	std::string str = "this is string";
};

class _class3 : public _class2
{
	enum fruits { apple, coco };

	void func3();
	int func4()
	{
		return 1;
	}

private:
	int var;
};


#endif
