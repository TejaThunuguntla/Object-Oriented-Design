#include "TestProj1.h"

using namespace _Namespace;

void globalfunc()
{
	std::string str;
	str = "this is a global func";
	return;
}

void _class1::func1()
{
	_class2 c2("class2 constructor");

	if (str > 0)
	{
		std::cout << "in Test func1";
	}
	else
	{
		c2.func2();
		std::cout << "Test func1";
	}
}

std::string _class2::func2()
{
	val = "in func2";
	return val;
}