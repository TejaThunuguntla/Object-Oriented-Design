///////////////////////////////////////////////////////////////////////
//  MtrExecutive.h:	 tests the FileManager and Parser components     //
//  Language:        Visual C++ 2015, SP1                            //
//  ver 1.0                                                          //
// Application:  Parallel Dependency, CSE687 - Object Oriented Design//
// Author:		  Teja Thunuguntla, Syracuse University				 //
//				  tthunugu@syr.edu									 //
///////////////////////////////////////////////////////////////////////

#include "MtrExecutive.h"
#ifdef  TEST_MTEx

int main(int argc, char* argv[])
{
	std::vector<std::string>  patterns;
	Test tst;
	if (argc > 1)
	{
		for (int i = 2; i < argc; i++)
			patterns.push_back(argv[i]);
		tst.testFileMgr(argv[1], patterns);
	}
	else
		std::cout << "Wrong path or patterns.! ";
	return 0;
}


#endif //  TEST_MTEx

