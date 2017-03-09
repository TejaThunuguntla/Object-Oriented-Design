/////////////////////////////////////////////////////////////////////
// FileMngr.cpp - find files matching specified patterns           //
//             on a specified path                                 //
// ver 1.0                                                         //
// Application:   Parser component, CSE687 - Object Oriented Design//
// Author:		   Teja Thunuguntla, Syracuse University		   //
// Author:      Jim Fawcett, Syracuse University, CST 4-187        //
//              jfawcett@twcny.rr.com                              //
/////////////////////////////////////////////////////////////////////

#include "FileMgr.h"
#include "../DataStore/DataStore.h"
#include <iostream>

#ifdef TEST_FILEMGR

int main(int argc, char* argv[])
{
	std::cout << "\n  Testing FileMgr";
	std::cout << "\n =================";

	DataStore ds;
	FileMgr fm(argv[1], ds);
	for (int i = 2; i < argc; ++i)
		fm.addPattern(argv[i]);
	//fm.addPattern("*.h");
	//fm.addPattern("*.cpp");
	//fm.addPattern("*.partial");
	fm.search();
	fm.getFiles();

	std::cout << "\n\n  contents of DataStore";
	std::cout << "\n -----------------------";
	for (auto fs : ds)
	{
		std::cout << "\n  " << fs;
	}
	std::cout << "\n\n";
	return 0;
}
#endif