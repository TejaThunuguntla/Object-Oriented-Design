#ifndef TEST_H
#define TEST_H

#include <iostream>

namespace _Namespace
{
	void globalfunc();

	class _class2
	{
	public:
		_class2(std::string cons)
		{
			std::cout << "in class2 constructor" << "\n";
		}
		std::string func2();
	private:
		std::string val;
	};

	class _class1 : public _class2
	{	
	public:
		typedef _class2 alias2;
		void func1();
	private:
		size_t str;

	};
}

#endif
