#include "ParallelDA.h"

///////////////////////////////////////////////////////////////////////
// ParallelDA.h - runs dependency analysis asynchronously			 //
///////////////////////////////////////////////////////////////////////																	 //
// ver 1.0															 //
// Application:  Parallel Dependency, CSE687 - Object Oriented Design//
// Author:		  Teja Thunuguntla, Syracuse University				 //
//				  tthunugu@syr.edu									 //
///////////////////////////////////////////////////////////////////////

#ifdef TEST_PDA

void main()
{
	TypeTable TypTbl;
	ProcessWorkItem<std::string> Threadpool(4);

	Threadpool.start();

	std::string path = "E:\Teja\Syracuse University\OOD\Project1";
	std::vector<std::string> pattrns;

	pattrns.push_back("*.h");
	pattrns.push_back("*.cpp");

	ParallelDA PDA(&Threadpool, &TypTbl);
	PDA.getLamda(&path, pattrns);
}

#endif // TEST_PDA