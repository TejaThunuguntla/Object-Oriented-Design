#include "PDepExec.h"

///////////////////////////////////////////////////////////////////////
// PDepExec.h - Test Executive for Project - 3 Parallel Dependency	 //
///////////////////////////////////////////////////////////////////////
// ver 1.0															 //
// Application:  Parallel Dependency, CSE687 - Object Oriented Design//
// Author:		  Teja Thunuguntla, Syracuse University				 //
//				  tthunugu@syr.edu									 //
///////////////////////////////////////////////////////////////////////

void DependencyExec::testFile(std::string path, std::vector<std::string> patterns)
{
	std::cout << "Given Path : " << path << "\n";
	std::cout << "============" << "\n";

	std::cout << "Given Patterns : ";
	for (auto str : patterns)
		std::cout << str << "  ";
	std::cout << "\n" << "================" << "\n \n";

	Task tasks(path, patterns);
}

#ifdef TEST_PDE

int main(int argc, char* argv[])
{
	std::vector<std::string> patterns;
	DependencyExec dExec;
	std::string path;
	if (argc > 1)
	{
		 path = argv[1];

		for (int i = 2; i < argc; i++) 
		{
			patterns.push_back(argv[i]);
		}
	
		dExec.testFile(argv[1], patterns);
	}
	else
		std::cout << "Wrong path or patterns.! ";

	return 0;
}

#endif
