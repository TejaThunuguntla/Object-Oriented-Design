#include "TestProj3.h"


void glblfunc()
{
	std::string gbl;
	gbl = "test global function";
}

void _class4::func5()
{
	try
	{
		size_t size;

		while (size < 10)
		{
			size++;
		}
	}
	catch (int ex)
	{
		std::cout << "exception caught" << ex;
	}
}