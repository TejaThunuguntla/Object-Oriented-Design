#ifndef TESTSUITE_H
#define TESTSUITE_H

#pragma warning(disable : 4503)

///////////////////////////////////////////////////////////////////////
//  MtrExecutive.h:	 tests the FileManager and Parser components     //
//  Language:        Visual C++ 2015, SP1                            //
//  ver 1.0                                                          //
// Application:  Parallel Dependency, CSE687 - Object Oriented Design//
// Author:		  Teja Thunuguntla, Syracuse University				 //
//				  tthunugu@syr.edu									 //
///////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
* Metric Executive provides functions to test the File Manager and
* Parser components. It takes path and patterns as inputs from console.
* Retrives all the files that match the given pattern and passes
* them to Parser for building an AST

Public Interface:
=================
testFileMgr(path,patterns) - tests the FileMngr component
testParser(string file)	- tests the Parser component including AST

Build Process:
==============
Required files
- FileMngr.h, FileMngr.cpp, MtrAnalysis.h, MtrAnalysis.cpp, Parser.h, Parser.cpp, 
  ActionsAndRules.h, ActionsAndRules.cpp, ConfigureParser.h, AST.h, AST.cpp

Build commands:
===============
- devenv project3.sln

Maintenance History:
====================
ver 1.0 : 12 Mar 16
- first release

*/

#include<vector>
#include <set>
#include <list>
#include <map>
#include <string>
#include <windows.h>
#include <iostream>
#include "../FileMngr/FileMgr.h"
#include "../MetricAnalysis/MtrAnalysis.h"
#include "../Parser/ConfigureParser.h"

class Test
{
public:
	void testFileMgr(std::string path, std::vector<std::string> patterns);
	void testParser(std::string file);
};

#endif 
