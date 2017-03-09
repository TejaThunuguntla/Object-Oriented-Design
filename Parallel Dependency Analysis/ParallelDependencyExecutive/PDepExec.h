#ifndef PDEPEXEC_H
#define PDEPEXEC_H

#pragma warning(disable : 4503)

///////////////////////////////////////////////////////////////////////
// PDepExec.h - Test Executive for Project - 3 Parallel Dependency	 //
///////////////////////////////////////////////////////////////////////	
// ver 1.0															 //
// Application:  Parallel Dependency, CSE687 - Object Oriented Design//
// Author:		  Teja Thunuguntla, Syracuse University				 //
//				  tthunugu@syr.edu									 //
///////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
* This package is the Test executive for Project 3 Parallel Dependency

Public Interface:
=================
* testFile() - sends the arguments to task package

Build Process:
==============
Required files
- Task.h, Task.cpp

Build commands:
===============
- devenv project3.sln

Maintenance History:
====================
ver 1.0 : 06 Apr 16
- first release

*/

#include "../Tasks/Task.h"
#include <vector>

class DependencyExec
{
public:
	void testFile(std::string path, std::vector<std::string> patterns);
};

#endif